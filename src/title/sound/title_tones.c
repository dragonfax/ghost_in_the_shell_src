/* title_tones: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

u32 title_bios_error_msg[7] RODATA = {
    0x80010000, 0x534F4942, 0x7265563A, 0x6E6F6973, 0x72724520, 0x0D2E726F,
    0x00000000,
};

extern u32 title_tone_words[];
extern TitleRestartEntry title_tone_table[26];
extern s32 title_seq_delay;
extern void (*slot_0A3)(s32 arg);
extern void (*slot_0A1)(s32, s32, s32);
extern s32 (*slot_read_file)(u8 *name, void *dest, s32 mode);
extern s32 (*slot_tone_volume)(s32);
/* Loads VAB\TITLE.VAB, opens it (slot_0A3, slot_0A1), then fills the 26 title
 * sound entries from the packed words at title_tone_words: tone id, volume (a third
 * for entries 15-16), bits 8-15 and the loop flag. */
void title_tones_load(void) {
    s32 size;
    u32 i;
    u32 *src;
    u32 word;
    s32 id;
    s16 volume;
    TitleRestartEntry *entry;

    do {
        size = slot_read_file((u8 *)"VAB\\TITLE.VAB", (void *)card_work_buf, 0);
    } while (size < 0);
    src = title_tone_words;
    slot_0A3(1);
    i = 0;
    slot_0A1(1, card_work_buf, 0);
    entry = title_tone_table;
    card_work_buf += size;
    do {
        word = *src;
        id = ((word & 3) << 24) | ((word >> 20) & 0x700) | ((word >> 24) & 0xF);
        entry->volume = volume = slot_tone_volume(id);
        if (i - 15 < 2) {
            entry->volume = volume / 3;
        }
        i++;
        entry->unk_22 = (word >> 8) & 0xFF;
        entry[-1].next_tone = id;
        entry->loop_flag = word >> 31;
        entry++;
        src++;
    } while (i < 26);
    title_seq_delay = title_video_is_pal() == 0 ? 0x708 : 0x5DC;
}

SVC_HEADER_CONSTS(tones);

extern TitleRestartEntry title_tone_table[26];
void title_seq_start(void);
/* Service calls and the 0x8001070C reset (twice), then clears the 26
 * entries of title_tone_table (id = -1) and starts the title sequence. */
void title_restart_entries(void) {
    void (**gfx_reset)(s32) = (void (**)(s32))0x8001070C;
    u32 count;
    u32 index;
    TitleRestartEntry *entry;

    slot_0B3();
    slot_0BD();
    (*gfx_reset)(0);
    (*gfx_reset)(0);
    count = 0;
    index = 0;
    do {
        count++;
        entry = &title_tone_table[index];
        entry->unk_1A = 0;
        entry->unk_1E = 0;
        entry->id = -1;
        index++;
    } while (count < 26);
    title_seq_start();
}

extern void (*slot_0B3)(void); /* service slot, called first */
extern void (*slot_0A3)(s32 arg); /* service slot, called with 1 */
/* Calls the service at slot_0B3, then the one at slot_0A3 with 1. */
void title_stop_services(void) {
    slot_0B3();
    slot_0A3(1);
}

extern TitleEntry2C title_entries[];
/* Packed list of up to 3 slot ids, one per byte, 0xFF = end of entry */
void title_entries_reset(u32 slot_ids) {
    u32 ids;
    u32 i;
    TitleEntry2C *slot;
    s32 id;

    ids = slot_ids;
    i = 0;
    do {
        id = ids & 0xFF;
        if (id != 0xFF) {
            slot = &title_entries[id];
            slot->alloc_retries = 8;
            slot->fade_level = 0x1000;
            slot->fade_step = 0;
            slot->fade_state = 2;
            slot->volume = slot->base_volume;
            slot->unk_18 = slot->default_value;
        }
        i++;
        ids >>= 8;
    } while (i < 3);
}

extern s32 title_seq_enabled;
void title_entries_reset_to(u32 packed_ids, s16 value) {
    u32 i;
    s32 id;
    TitleEntry2C *entry;

    if (title_seq_enabled == 1) {
        for (i = 0; i < 3; i++) {
            id = packed_ids & 0xFF;
            if (id != 0xFF) {
                entry = &title_entries[id];
                entry->volume = entry->base_volume;
                entry->alloc_retries = 8;
                entry->fade_level = 0x1000;
                entry->fade_step = 0;
                entry->unk_18 = value;
                entry->fade_state = 2;
            }
            packed_ids >>= 8;
        }
    }
}

extern s32 (*slot_snd_alloc_channel)(s32 *block);
/* Packed list of up to 3 slot ids, one per byte, 0xFF = end of entry.
 * Resets each entry and asks the sound system for a channel. */
void title_entries_start(u32 slot_ids) {
    u32 ids;
    u32 i;
    TitleEntry2C *entry;
    s32 id;

    ids = slot_ids;
    i = 0;
    do {
        id = ids & 0xFF;
        if (id != 0xFF) {
            entry = &title_entries[id];
            entry->fade_level = 0x1000;
            *(s32 *)entry = 0x147;
            entry->fade_step = 0;
            entry->volume = entry->base_volume;
            entry->unk_18 = entry->default_value;
            entry->sound_channel = slot_snd_alloc_channel((s32 *)entry);
            entry->fade_state = 0;
        }
        i++;
        ids >>= 8;
    } while (i < 3);
}

void title_entries_ramp(u32 packed, s32 arg1) {
    u32 i;
    s32 idx;
    s32 quot;
    TitleEntry2C *e;

    i = 0;
    do {
        idx = packed & 0xFF;
        if (idx != 0xFF) {
            e = &title_entries[idx];
            if (arg1 >= 0) {
                quot = 0x1000 / arg1;
                e->volume = 0;
                e->unk_18 = e->default_value;
                e->fade_step = quot;
                e->fade_level = quot;
                if (e->sound_channel < 0) {
                    e->alloc_retries = 8;
                    e->fade_state = 2;
                }
            } else {
                e->fade_step = 0x1000 / arg1;
            }
        }
        packed = packed >> 8;
        i++;
    } while (i < 3);
}

void title_entries_fade_out(u32 packed) {
    title_entries_ramp(packed, -0x10);
}

extern s32 (*slot_0B0)(s32 *block);
extern void (*slot_sound_key_on)(s32 *block);
void title_seq_update(void);
/* Per-frame update of the 26 title sound entries: fade volume, start channels. */
void title_sound_update(void) {
    TitleEntry2C *e;
    u32 i;
    s32 (*alloc)(s32 *);

    e = title_entries;
    for (i = 0; i < 0x1A; i++, e++) {
        switch (e->fade_state) {
        case 1:
            if (slot_0B0((s32 *)e) != e->sound_channel) {
                e->sound_channel = -1;
                e->fade_state = 0;
            } else {
                *(s32 *)e = 0x66;
                e->volume = (e->base_volume * e->fade_level) / 0x1000;
                slot_snd_alloc_channel((s32 *)e);
                if (e->fade_step != 0) {
                    e->fade_level += e->fade_step;
                    if (e->fade_step < 0 && e->fade_level < 0) {
                        e->fade_state = 0;
                        e->fade_level = 0;
                        slot_sound_key_on((s32 *)e);
                        e->sound_channel = -1;
                    } else if (e->fade_step > 0 && e->fade_level > 0x1000) {
                        e->fade_level = 0x1000;
                        e->fade_step = 0;
                    }
                }
            }
            break;
        case 0:
            break;
        case 2:
            alloc = slot_snd_alloc_channel;
            *(s32 *)e = 0x167;
            e->sound_channel = alloc((s32 *)e);
            if (e->sound_channel >= 0) {
                e->fade_state = 1;
            } else {
                e->alloc_retries--;
                if (e->alloc_retries < 0) {
                    e->fade_state = 0;
                }
            }
            break;
        }
    }
    title_seq_update();
}

extern s32 D_80116CA4;
extern s32 title_seq_delay;
extern s32 title_seq_state;
void title_seq_set_enabled(s32 arg);
void title_seq_start(void) {
    title_seq_state = 0;
    D_80116CA4 = title_seq_delay;
    title_seq_set_enabled(1);
}

/* Same code as tex_upload_set_flag (s01). */
void title_seq_set_enabled(s32 arg0) {
    title_seq_enabled = arg0;
}

extern TitleEntry2C title_entries[];
/* Checks the low three bytes of `key` (least significant first); 0xFF bytes
 * are skipped. Returns 1 if any table entry's word at +8 is non-negative. */
s32 title_entries_any_active(u32 key) {
    s32 found;
    u32 i;
    s32 *entry;

    i = 0;
    do {
        if ((key & 0xFF) != 0xFF) {
            entry = (s32 *)((u8 *)title_entries + (key & 0xFF) * 0x2C);
            if (entry[2] >= 0) {
                found = 1;
                return found;
            }
        }
        i += 1;
        key = key >> 8;
    } while (i < 3);
    return 0;
}

/* Returns 1 if either of two packed key codes passes title_entries_any_active's table check. */
s32 title_seq_any_active(void) {
    s32 firstKeyFound;
    s32 secondKeyFound;

    firstKeyFound = title_entries_any_active(0xD0EFF);
    secondKeyFound = title_entries_any_active(0x1112FF);
    if (firstKeyFound == 1 || secondKeyFound == 1) {
        return 1;
    }
    return 0;
}

void title_seq_fade_in(s32 arg0);
void title_seq_fade_out(s32 arg0);
/* Per-frame title sequencer. Does nothing unless title_seq_enabled is set.
 * State 1 counts D_80116CA4 down; at zero it arms state 2 with a 0x3C-frame
 * pulse. State 2 re-arms the pulse (8) while title_seq_any_active reports no hit. */
void title_seq_update(void) {
    s32 frames_left;

    if (title_seq_enabled != 0) {
        switch (title_seq_state) {
        case 1:
            frames_left = D_80116CA4 - 1;
            D_80116CA4 = frames_left;
            if (frames_left == 0) {
                title_seq_fade_out(0x3C);
                title_seq_state = 2;
                return;
            }
            break;
        case 2:
            if (title_seq_any_active() == 0) {
                title_seq_fade_in(8);
            }
            break;
        case 0:
            break;
        }
    }
}

extern s32 D_80116CA4;
extern s32 title_seq_delay;
extern s32 title_seq_state;

void title_seq_fade_in(s32 arg0) {
    title_entries_ramp(0xD0EFF, arg0);
    title_entries_ramp(0x1112FF, arg0);
    title_seq_state = 1;
    D_80116CA4 = title_seq_delay;
}

void title_seq_fade_out(s32 arg0) {
    s32 temp_s0;

    temp_s0 = -arg0;
    title_entries_ramp(0xD0EFF, temp_s0);
    title_entries_ramp(0x1112FF, temp_s0);
}

extern TitleEntry2C title_entries[];
void title_entries_set_rate(s32 divisor) {
    TitleEntry2C *entry;
    s32 index;

    entry = title_entries;
    index = 0;
    do {
        if (index != 1) {
            entry->fade_step = -0x1000 / divisor;
        }
        index += 1;
        entry += 1;
    } while ((u32) index < 0x1A);
}

void title_entries_set_value(u32 ids, u32 value) {
    TitleEntry2C *slot;
    s32 i = 0;

    do {
        u32 id = ids & 0xFF;
        if (id != 0xFF) {
            slot = &title_entries[id];
            if (slot->sound_channel >= 0) {
                slot->unk_18 = value & 0xFF;
            }
        }
        i += 1;
        ids >>= 8;
    } while ((u32) i < 3);
}

extern u8 movie_quant_base[];
extern u8 movie_table_b[64];
extern u8 movie_dct_env[];
void movie_tables_init(void) {
    mem_copy(0x40, movie_quant_base, movie_dct_env);
    mem_copy(0x40, movie_table_b, movie_dct_env + 0x40);
    /* The original passes (count, dst) to mem_fill(dst, count, value): the "count" is an
       address (negative as s32), so the fill never runs. */
    mem_fill((s8 *)0x80, (s32)(movie_dct_env + 0x80), 0);
}

extern void (*slot_DecDCTPutEnv)(void *env);
/* Builds a DCT environment with both quant tables scaled by scale/128. */
void title_quant_scale(s32 scale) {
    DctEnv env;
    u8 *src;
    u8 *luma;
    u8 *chroma;
    s32 i;
    s32 q;
    s32 scaled;
    u8 out;

    env = *(DctEnv *)movie_dct_env;
    if (scale != 0x80) {
        src = movie_quant_base;
        luma = env.b;
        chroma = env.b + 0x40;
        for (i = 0; i < 0x40; i++) {
            q = *src++;
            if (q >= 0x10) {
                q = q * scale;
                scaled = q / 128;
                {
                    register s32 clamped asm("$2") = MAX(MIN(scaled, 0xFF), 2);
                    q = clamped;
                }
            }
            out = q;
            *luma++ = out;
            *chroma++ = out;
        }
    }
    slot_DecDCTPutEnv(&env);
}

extern s32 movie_rgb24_flag;
void title_screen_setup_init(TitleScreenSetup *out, TitleScreenParams *in) {
    out->unk_00 = in->unk_24;
    out->unk_04 = in->unk_28;
    out->unk_08 = 0;
    out->unk_0C = in->unk_2C;
    out->unk_20 = 0;
    out->unk_2C = 0;
    if (movie_rgb24_flag == 1) {
        out->disp.x = in->dispX;
        out->disp.y = in->dispY;
        out->disp.w = 960;
        out->disp.h = 240;
        out->screen.x = in->screenX;
        out->screen.y = in->screenY;
        out->screen.w = 960;
        out->screen.h = 240;
        out->clip.x = in->dispX;
        out->clip.y = in->dispY;
        out->clip.w = 24;
        out->clip.h = 240;
    } else {
        out->disp.x = in->dispX;
        out->disp.y = in->dispY;
        out->disp.w = 640;
        out->disp.h = 240;
        out->screen.x = in->screenX;
        out->screen.y = in->screenY;
        out->screen.w = 640;
        out->screen.h = 240;
        out->clip.x = in->dispX;
        out->clip.y = in->dispY;
        out->clip.w = 16;
        out->clip.h = 240;
    }
}

extern s32 (*slot_14C)(s32, s32, s32, s32);
s32 movie_stream_start(s32 a, s32 b) {
    return slot_14C(a, b, 0x10000, 0);
}

extern void (*slot_120)(s32);
extern void (*slot_DecDCToutCallback)(s32);
extern void (*slot_14B)(void *);
extern s32 movie_done_flag;
extern s32 D_800BE474;
extern s32 D_80116CF4;
s32 movie_start(s32 ctx, struct TitleSrc *src, s32 dec_arg, s32 cmd_mode) {
    struct TitleCmd cmd;

    slot_120(0);
    movie_done_flag = 0;
    D_800BE474 = 0;
    slot_DecDCToutCallback(dec_arg);
    cmd.unk_00 = src->unk_30;
    cmd.unk_08 = src->unk_20;
    cmd.unk_0C = 0xA;
    cmd.unk_10 = 0;
    cmd.total_size = src->unk_1C;
    cmd.unk_04 = cmd_mode;
    D_80116CF4 = cmd.total_size;
    slot_14B(&cmd);
    return movie_stream_start(ctx, src->unk_18);
}

extern s32 (*slot_14D)(void *, void *, s32);
extern void *movie_frame_data;
extern u32 movie_frame_size;
extern s32 movie_rgb24_flag;
extern s32 movie_frame_w;
extern s32 movie_frame_h;
s32 movie_read_frame(DctBufPair *pair) {
    MovieFrameHeader *hdr;
    s32 *data;
    s32 ret;
    u32 size;

    do {
        ret = slot_14D(&hdr, &data, ret);
    } while (ret == 0);
    if (ret < 0) {
        return -1;
    }
    movie_frame_data = data;
    if (data[0] != hdr->key0) {
        return 0;
    }
    if (data[1] != hdr->key1) {
        return 0;
    }
    if (movie_frame_w != hdr->w || movie_frame_h != hdr->h) {
        movie_frame_w = hdr->w;
        movie_frame_h = hdr->h;
    }
    if (movie_rgb24_flag == 1) {
        pair->width_a = pair->width_b = movie_frame_w * 3 / 2;
    } else {
        pair->width_a = pair->width_b = movie_frame_w;
    }
    pair->height_c = pair->height_a = pair->height_b = movie_frame_h;
    size = hdr->size;
    movie_frame_size = size;
    if (size >= D_80116CF4) {
        movie_done_flag = 1;
    }
    return ret;
}

extern s32 movie_fade_level;

void title_set_fade_level(s32 arg0) {
    movie_fade_level = arg0;
}

extern s32 (*slot_LoadImage)(ClutRect *rect, u16 *data);
void title_image_load(ClutRect *src, void *data) {
    ClutRect rect;
    s32 full_strips;
    s32 rem_h;
    s32 blocks;
    s32 rest;
    s32 stride_units;
    s32 row_stride;
    s32 y;
    s32 i;

    if (movie_fade_level == 0x1000) {
        slot_LoadImage(src, data);
        return;
    }
    *(Unaligned8 *) &rect = *(Unaligned8 *) src;
    full_strips = rect.h / 8;
    rem_h = src->h - full_strips * 8;
    blocks = (full_strips * movie_fade_level) / 0x1000;
    i = 0;
    rest = full_strips - blocks;
    stride_units = full_strips * 2;
    row_stride = rect.w * stride_units;
    y = src->y;
    for (i = 0; i < 8; i++) {
        if (blocks > 0) {
            rect.h = blocks;
            rect.y = y;
            slot_LoadImage(&rect, data);
            data = (u8 *) data + row_stride;
        }
        if (full_strips != blocks) {
            rect.h = rest;
            rect.y += blocks;
            slot_clear_image(&rect, 0, 0, 0);
        }
        y += full_strips;
    }
    if (rem_h != 0) {
        rect.h = rem_h;
        rect.y = y;
        slot_clear_image(&rect, 0, 0, 0);
    }
}

extern TitleSwap movie_swap;
extern void *movie_out_buf;
extern u16 movie_strip_step;
extern s16 movie_strip_height;
extern s32 (*slot_151)(void);
extern void (*slot_150)(void);
extern s32 (*slot_draw_sync)(s32 mode);
extern void DecDCTout(void *addr, s32 size);
/* Per-frame swap step: waits on the two slots, advances the image's x by the
 * step, and while x is inside the current entry's span decodes a strip. Once
 * past the span it flips the toggle, marks busy and loads the other entry's x/y. */
void movie_out_callback(void) {
    TitleSwap *swap;
    s32 toggle;

    swap = &movie_swap;
    if (slot_151()) {
        slot_150();
    }
    slot_draw_sync(0);
    title_image_load((ClutRect *) &swap->x, movie_out_buf);
    swap->x += movie_strip_step;
    if (swap->x < swap->entries[swap->toggle][0] + swap->entries[swap->toggle][2]) {
        DecDCTout(movie_out_buf, (s16) movie_strip_step * movie_strip_height / 2);
    } else {
        swap->busy = 1;
        toggle = (swap->toggle ^ 1) != 0;
        swap->toggle = toggle;
        swap->x = swap->entries[toggle][0];
        swap->y = swap->entries[toggle][1];
    }
}

extern void (*slot_14F)(void);
void movie_stop(void) {
    slot_14F();
    movie_done_flag = 1;
}

void DecDCTvlc(void *src, void *dst);
extern void *movie_frame_data;
extern void (*slot_14E)(s32);
s32 movie_decode_frame(DctBufPair *pair) {
    s32 result;
    s32 next;

    do {
        result = movie_read_frame(pair);
    } while (result == 0);
    next = pair->active != 1;
    pair->active = next;
    DecDCTvlc(movie_frame_data, pair->buf[next]);
    slot_14E(result);
    return 1;
}

/* Waits out a countdown (0x01000000 iterations), then flips the toggle and copies
 * the selected entry's two halfwords into x/y. Clears the busy flag on exit. */
void movie_mdec_wait(TitleSwap *swap) {
    volatile s32 countdown;
    s32 busy;
    s32 toggle;

    busy = swap->busy;

    countdown = 0x01000000;
    if (busy == 0) {
        do {
            countdown = countdown - 1;
            if (countdown == 0) {
                swap->busy = 1;
                toggle = swap->toggle == 0;
                swap->toggle = toggle;
                swap->x = swap->entries[toggle][0];
                swap->y = swap->entries[toggle][1];
            }
        } while (swap->busy == 0);
    }
    swap->busy = 0;
}

/* Same code as svc_remove_frame_task (s01). */
void func_800BBD7C(void) {
    slot_14F();
}

extern s32 movie_quant_scale;
/* Stores value clamped to 0..255. */
void title_set_intensity(s32 value) {
    value = MAX(MIN(value, 0xFF), 0);
    movie_quant_scale = value;
}

extern s32 movie_rgb24_flag;
extern u32 movie_frame_size;
extern CdlLOC movie_file_pos;
extern TitleSwap movie_swap;
extern s32 movie_quant_scale;
extern s32 movie_swap_active;
extern void *movie_out_buf;
extern u16 movie_strip_step;
extern s16 movie_strip_height;
extern s32 movie_done_flag;

extern void (*slot_1C3)(s32);
extern void (*slot_set_disp_mask)(s32 mask);
extern s32 (*slot_154)(CdlFILE *, s32);
extern void (*slot_DecDCTin)(void *, s32);
extern void (*slot_DecDCTout)(void *, s32);
extern void (*slot_1DA)(MovieDispEnv *, s32, s32, s32, s32);
extern void (*slot_put_disp_env)(MovieDispEnv *);

void func_800BBD7C(void);

/* Plays a movie file: finds it on the disc, starts the stream and decodes
 * frame after frame, flipping the display between the two buffers, until
 * the stream ends (0) or abort_fn returns 1 (1). -1: file not found,
 * 3: the stream didn't start. */
s32 movie_play_loop(s32 name, MovieParams *params, s32 (*abort_fn)(void)) {
    MovieDispEnv env;
    CdlFILE file;
    s32 mode;
    s32 rgb24;
    s32 side;

    rgb24 = params->rgb24;
    if (rgb24 == 1) {
        movie_rgb24_flag = rgb24;
    } else {
        movie_rgb24_flag = 0;
    }
    mode = 2;
    if (movie_rgb24_flag == 1) {
        mode = 3;
    }
    movie_frame_size = 0;
    slot_1C3(0);
    slot_set_disp_mask(0);
    if (slot_154(&file, name) == 0) {
        return -1;
    }
    movie_file_pos = file.pos;
    title_screen_setup_init((TitleScreenSetup *)&movie_swap, (TitleScreenParams *)params);
    if (movie_start((s32)&movie_file_pos, (TitleSrc *)params, (s32)movie_out_callback,
                    (s32)movie_stop) == 0) {
        return 3;
    }
    movie_decode_frame((DctBufPair *)&movie_swap);
    for (;;) {
        title_quant_scale(movie_quant_scale);
        slot_DecDCTin(((DctBufPair *)&movie_swap)->buf[movie_swap_active], mode);
        slot_DecDCTout(movie_out_buf, (s16)movie_strip_step * movie_strip_height / 2);
        movie_decode_frame((DctBufPair *)&movie_swap);
        if (movie_done_flag == 1) {
            func_800BBD7C();
            return 0;
        }
        movie_mdec_wait(&movie_swap);
        if (abort_fn != NULL && abort_fn() == 1) {
            func_800BBD7C();
            return 1;
        }
        side = (movie_swap.toggle != 1);
        slot_1DA(&env, movie_swap.entries[side][0], movie_swap.entries[side][1],
                 movie_swap.entries[side][2], movie_swap.entries[side][3]);
        slot_1C3(0);
        env.screen = params->head;
        env.isrgb24 = movie_rgb24_flag;
        if (movie_rgb24_flag == 1) {
            env.disp_w = env.disp_w * 2 / 3;
        } else {
            env.disp_w = env.disp_w;
        }
        slot_put_disp_env(&env);
        slot_set_disp_mask(1);
    }
}

extern s32 movie_play_loop(s32 name, MovieParams *params, s32 (*abort_fn)(void));
extern void (*slot_0AA)(s32);
extern s32 (*slot_draw_sync)(s32 mode);
void play_movie(s32 name, MovieParams *params, s32 (*abort_fn)(void)) {
    s32 frame_pad[2]; /* original frame is 8 bytes larger; keeps 0x28 */

    movie_tables_init();
    slot_144();
    slot_141();
    slot_0AA(0);
    slot_draw_sync(0);
    movie_play_loop(name, params, abort_fn);
}
