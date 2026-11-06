/* loader_screen: one of loader's own original source files (scripts/objmap.py); part of src/loader/main.c's unit, included there. */

extern s32 joy_button_mask;
/* Same code as set_area (s01). */
void joy_set_button_mask(s32 value) {
    joy_button_mask = value;
}

extern s32 joy_ring_enabled;
/* Same code as pursue_flag_set (s01). */
void joy_set_ring_enabled(s32 arg0) {
    joy_ring_enabled = arg0;
}

extern s32 joy_ring_enabled;
extern volatile s32 joy_ring_head;
extern s32 joy_ring[];
s32 loader_read_pad(s32 a);
void joy_record_sample(void) {
    s32 i, r;

    if (joy_ring_enabled == 1) {
        r = loader_read_pad(0);
        i = joy_ring_head;
        joy_ring_head = i + 1;
        joy_ring[i] = r;
        joy_ring_head &= 0x1FF;
    }
}

extern s32 joy_ring_enabled;
extern volatile s32 joy_ring_tail;
extern s32 joy_button_mask;
extern s32 joy_ring[];
s32 joy_read_next(void) {
    s32 i;
    s32 word;
    s32 mask;

    if (joy_ring_enabled != 1) {
        return 0;
    }
    i = joy_ring_tail;
    word = joy_ring[i];
    mask = joy_button_mask;
    joy_ring_tail = i + 1;
    joy_ring_tail &= 0x1FF;
    return word & mask;
}

extern s32 joy_ring[];
void joy_ring_clear(void) {
    s32 i;
    s32 *p;

    p = joy_ring;
    i = 0x1FF;
    do {
        *p = 0;
        i -= 1;
        p += 1;
    } while (i >= 0);
}

extern s32 joy_repeat_count;
extern s32 joy_repeat_first;
extern s32 joy_repeat_interval;
extern volatile s32 joy_prev_pressed;
extern volatile s32 joy_latched_buttons;
extern volatile s32 joy_ring_head;
extern s32 joy_repeat_armed;
extern volatile s32 joy_buttons_masked;
void joy_mark_init_done(void);
void joy_init(void) {
    joy_button_mask = -1;
    joy_ring_clear();
    joy_prev_pressed = 0;
    joy_buttons_masked = 0;
    joy_repeat_first = 12;
    joy_repeat_interval = 5;
    joy_repeat_count = 12;
    joy_latched_buttons = 0;
    joy_latched_buttons = 0;
    joy_ring_head = 0;
    joy_ring_tail = 0;
    joy_repeat_armed = 1;
    joy_mark_init_done();
    joy_ring_enabled = 1;
}

void joy_reset(void) {
    joy_button_mask = -1;
    joy_ring_clear();
    joy_prev_pressed = 0;
    joy_buttons_masked = 0;
    joy_repeat_first = 12;
    joy_repeat_interval = 5;
    joy_repeat_count = 12;
    joy_latched_buttons = 0;
    joy_latched_buttons = 0;
    joy_ring_head = 0;
    joy_ring_tail = 0;
    joy_repeat_armed = 1;
    joy_ring_enabled = 1;
}

extern s32 joy_repeat_first;
extern volatile s32 joy_latched_buttons;
extern volatile s32 joy_prev_pressed;
extern s32 joy_repeat_armed;
extern s32 joy_repeat_count;
void joy_repeat_reset(void) {
    joy_latched_buttons = 0;
    joy_prev_pressed = -1;
    joy_repeat_armed = 0;
    joy_repeat_count = joy_repeat_first;
}

extern volatile s32 joy_buttons;
extern s32 joy_button_mask;
s32 joy_get_buttons(void) {
    return joy_buttons & joy_button_mask;
}

/* Same code as joy_get_buttons (loader). */
s32 joy_get_masked_buttons(void) {
    return joy_latched_buttons & joy_button_mask;
}

extern s32 joy_repeat_interval;
/* Returns joy_latched_buttons & joy_button_mask when joy_repeat_count and joy_repeat_interval differ, else 0. */
s32 joy_repeat_fired(void) {
    s32 result;

    if (joy_repeat_count != joy_repeat_interval) {
        result = joy_latched_buttons & joy_button_mask;
    } else {
        result = 0;
    }
    return result;
}

s32 joy_frame_update(void) {
    joy_buttons = joy_read_next();
    joy_buttons_masked = joy_buttons & 0xF8E0;
    if (joy_repeat_armed == 0) {
        joy_repeat_count = joy_repeat_first;
    }
    if (joy_buttons_masked & joy_prev_pressed) {
        joy_prev_pressed = joy_buttons_masked;
        joy_repeat_count -= 1;
        if (joy_repeat_count != 0) {
            joy_latched_buttons = 0;
            return joy_latched_buttons & joy_button_mask;
        }
        joy_repeat_count = joy_repeat_interval;
    } else {
        joy_repeat_armed = 1;
        joy_repeat_count = joy_repeat_first;
    }
    joy_prev_pressed = joy_buttons_masked;
    joy_latched_buttons = joy_buttons_masked;
    if (joy_repeat_armed == 1) {
        return joy_buttons_masked & joy_button_mask;
    }
    return 0;
}

extern void (*slot_set_disp_mask)(s32 mask);
extern void (*slot_clear_image)(Rect *rect, s32 r, s32 g, s32 b);
extern void SetGeomOffset(s32 x, s32 y);
extern void SetGeomScreen(s32 h);
extern u8 svc_table[];
void loader_screen_reset(void) {
    Rect rect = {0, 0, 0x3FF, 0x1FF};

    slot_set_disp_mask(0);
    slot_clear_image(&rect, 0, 0, 0);
    (*(void (**)(s32))0x80010728)(0);
    SetGeomOffset(0, 0);
    SetGeomScreen(0x100);
    (*(void (**)(s32))0x80010728)(0);
    gte_set(VZ0, 0);
    gte_set(VZ1, 0);
    gte_set(VZ2, 0);
}

SVC_HEADER_CONSTS(screen_a);
SVC_HEADER_CONSTS(screen_b);

void RotMatrix(u16 *rot, void *m);
void ScaleMatrix(void *m, void *scale);
void SetRotMatrix(void *m);
void TransMatrix(void *m, void *trans);
void SetTransMatrix(void *m);
extern s32 loader_rot_zero_flag;
void loader_set_matrices(u16 *rot, void *trans, void *scale) {
    RotMatrix(rot, (void *)0x1F800000);
    if (scale != 0) {
        ScaleMatrix((void *)0x1F800000, scale);
    }
    SetRotMatrix((void *)0x1F800000);
    TransMatrix((void *)0x1F800000, trans);
    SetTransMatrix((void *)0x1F800000);
    if (((rot[0] | rot[1] | rot[2]) & 0xFFF) == 0) {
        loader_rot_zero_flag = 1;
    } else {
        loader_rot_zero_flag = 0;
    }
}

/* Same code as svc_remove_frame_task (s01). */
void loader_set_disp_mask(s32 mask) {
    slot_set_disp_mask(mask);
}

extern u32 *(*slot_ClearOTag)(s32 ot, s32 n);
/* Same code as title_ot_clear (title). */
u32 *loader_ot_clear(s32 ot, s32 n) {
    return slot_ClearOTag(ot, n);
}

extern s32 (*slot_draw_sync)(s32 mode);
/* Same code as loader_wait_frames (loader). */
s32 loader_draw_sync(s32 mode) {
    return slot_draw_sync(mode);
}

extern s32 (*slot_LoadImage)(Rect *rect, void *data);
/* Same code as title_load_image (title). */
s32 loader_load_image_rect(Rect *rect, void *data) {
    return slot_LoadImage(rect, data);
}

extern s32 (*slot_StoreImage)(RECT *rect, u32 *p);
/* Same code as svc_remove_frame_task (s01). */
s32 loader_store_image(RECT *rect, u32 *p) {
    return slot_StoreImage(rect, p);
}

/* Same code as clear_image (title). */
void loader_clear_image(void *rect, s32 r, s32 g, s32 b) {
    slot_clear_image(rect, r & 0xFF, g & 0xFF, b & 0xFF);
}

extern s32 (*slot_MoveImage)(RECT *rect, s32 x, s32 y);
/* Same code as svc_remove_frame_task (s01). */
s32 loader_move_image(RECT *rect, s32 x, s32 y) {
    return slot_MoveImage(rect, x, y);
}

extern s32 (*slot_1C3)(s32 handle);
/* Same code as svc_remove_frame_task (s01). */
s32 loader_wait_frames(s32 handle) {
    return slot_1C3(handle);
}

extern void (*slot_put_disp_env)(void *buf);
/* Same code as svc_remove_frame_task (s01). */
void loader_put_disp_env(void *buf) {
    slot_put_disp_env(buf);
}

extern void *(*slot_1C2)(void *env);
/* Forwards its draw env (the title draw context's draw_env) to slot 0x1C2 unchanged. */
void *loader_put_draw_env(void *env) {
    return slot_1C2(env);
}

extern void (*slot_DrawOTag)(s32 handle);
/* Same code as svc_remove_frame_task (s01). */
void loader_draw_otag(s32 handle) {
    slot_DrawOTag(handle);
}

extern s32 joy_init_done_flag;

void joy_mark_init_done(void) {
    if (joy_init_done_flag == 0) {
        joy_init_done_flag = 1;
    }
}

extern s32 (*slot_read_pad)(s32 mode);
s32 loader_read_pad(s32 a) {
    return slot_read_pad(0);
}

extern s32 (*slot_add_frame_task)(void (*fn)(void), s32 period);
extern s32 loader_task_handle;
/* Same code as add_vblank_task (title). */
void loader_add_task(void (*task)(void)) {
    loader_task_handle = slot_add_frame_task(task, 0);
}

extern s32 loader_task_handle;
extern void (*slot_remove_frame_task)(s32); /* service slot: remove a frame task */
/* Removes the frame task held in loader_task_handle (if any) and clears the handle. */
void loader_remove_task(void) {
    if (loader_task_handle != -1) {
        slot_remove_frame_task(loader_task_handle);
    }
    loader_task_handle = 0;
}

extern void (*slot_SetDrawMode)(s32 prim, s32 a1, s32 a2, s32 a3, RECT *a4);
void loader_set_draw_mode(s32 prim, s32 a1, s32 a2, s32 a3, RECT *a4) {
    slot_SetDrawMode(prim, a1, a2, a3, a4);
}

extern void (*slot_1DA)(MovieDispEnv *, s32, s32, s32, s32);
void loader_set_disp_env(void *buf, s32 x, s32 y, s32 w, s32 h) {
    slot_1DA(buf, x, y, w, h);
}

extern void (*slot_1D9)(MovieDispEnv *, s32, s32, s32, s32);
/* Same code as loader_set_disp_env (loader). */
void loader_set_draw_env(void *buf, s32 x, s32 y, s32 w, s32 h) {
    slot_1D9(buf, x, y, w, h);
}

s32 rsin(s32 angle);
/* Returns rsin(angle) clamped to [-0xFFE, 0xFFE]. */
s32 loader_rsin_clamped(s32 angle) {
    s32 value = rsin(angle);
    s32 result;

    if (value >= -0xFFE) {
        if (value < 0xFFF) {
            result = value;
        } else {
            result = 0xFFE;
        }
    } else {
        result = -0xFFE;
    }
    return result;
}

s32 rcos(s32 angle);
/* Same code as loader_rsin_clamped (loader). */
s32 loader_cos_clamped(s32 angle) {
    s32 value = rcos(angle);
    s32 result;

    if (value >= -0xFFE) {
        if (value < 0xFFF) {
            result = value;
        } else {
            result = 0xFFE;
        }
    } else {
        result = -0xFFE;
    }
    return result;
}

extern s32 (*slot_GetVideoMode)(void);
/* Same code as title_remove_frame_task (title). */
s32 loader_get_video_mode(void) {
    return slot_GetVideoMode();
}

/* Same code as str_copy (boot). */
void loader_str_copy(u8 *src, u8 *dst) {
    u8 c;

    while ((c = *src++) != 0) {
        *dst++ = c;
    }
    *dst = 0;
}

/* Concatenates two NUL-terminated strings into dst (dst must have room). */
void loader_str_cat(u8 *first, u8 *second, u8 *dst) {
    u8 c;

    while ((c = *first++) != 0) {
        *dst++ = c;
    }
    while ((c = *second++) != 0) {
        *dst++ = c;
    }
    *dst = 0;
}

/* Copies a NUL-terminated string, upper-casing ASCII letters. */
void loader_str_copy_upper(u8 *src, u8 *dst) {
    u8 c;

    while ((c = *src++) != 0) {
        if ((u32)(c - 'a') < 26) {
            c &= 0xDF;
        }
        *dst++ = c;
    }
    *dst = 0;
}

/* Same code as to_upper (boot). */
u8 loader_to_upper(u8 c) {
    u8 r = c;
    if ((u8)(c - 0x61) < 0x1A) {
        r = c & 0xDF;
    }
    return r;
}

/* Compares len bytes of lhs and rhs; returns 1 if they are all equal, else 0. */
s32 loader_mem_equal(s32 len, u8 *lhs, u8 *rhs) {
    s32 equal = 1;

    while (len > 0) {
        if (equal != 1) {
            break;
        }
        if (*lhs != *rhs) {
            equal = 0;
        }
        lhs++;
        len--;
        rhs++;
    }
    return equal;
}

void loader_copy_bytes(s32 arg0, u8 *arg1, u8 *arg2) {
    s32 var_a0;
    u8 *var_a1;
    u8 *var_a2;
    u8 temp_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    if (var_a0 > 0) {
        do {
            temp_v0 = *var_a1;
            var_a1 += 1;
            var_a0 -= 1;
            *var_a2 = temp_v0;
            var_a2 += 1;
        } while (var_a0 > 0);
    }
}

/* Same code as mem_set (boot). */
void loader_mem_set(s8 *arg0, s32 arg1, s8 arg2) {
    s32 var_a1;
    s8 *var_a0;

    var_a0 = arg0;
    var_a1 = arg1;
    if (var_a1 > 0) {
        do {
            *var_a0 = arg2;
            var_a1 -= 1;
            var_a0 += 1;
        } while (var_a1 > 0);
    }
}

/* Same code as str_length (s01). */
s32 loader_str_len(u8 *str) {
    s32 len = 0;

    while (*str++ != 0) {
        len++;
    }
    return len;
}

/* Same code as round_up (boot). */
s32 loader_round_up(s32 value, s32 align) {
    s32 biased = value - 1;
    return (biased + align) / align * align;
}

/* Same code as clamp_value (boot). */
s32 loader_clamp_value(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a1;

    var_a1 = arg1;
    if (arg0 >= var_a1) {
        var_a1 = arg2;
        if (arg2 >= arg0) {
            var_a1 = arg0;
        }
    }
    return var_a1;
}

/* Reads a 4-byte value from src, most significant byte first (src[3] down to src[0]). */
s32 loader_read_be32(u8 *src) {
    s32 value;
    s32 i;
    u8 *p;
    s32 byte;

    value = 0;
    p = src + 3;
    i = 3;
    do {
        value = value << 8;
        byte = *p;
        p -= 1;
        i -= 1;
        value += byte;
    } while (i >= 0);
    return value;
}

// Reads a little-endian u16 from a byte pointer.
s32 loader_read_le16(u8 *bytes) {
    s32 high = bytes[1];
    s32 value = bytes[0];
    high <<= 8;
    value |= high;
    return value;
}

extern u32 loader_decimal_places[];
/* Same code as u32_to_decimal (boot). */
void loader_u32_to_decimal(u32 val, s8 *out) {
    s32 digit;
    u32 *pow;
    u32 place;

    pow = loader_decimal_places;
    if (*pow != 0) {
        do {
            place = *pow;
            digit = 0;
            if (val >= place) {
                do {
                    val -= place;
                    digit += 1;
                } while (val >= place);
                *out = digit + '0';
            } else {
                *out = '0';
            }
            pow += 1;
            out += 1;
        } while (*pow != 0);
    }
    *out = 0;
}

extern s32 loader_fade_state;
/* Same code as sway_disable (s01). */
void loader_fade_reset(void) {
    loader_fade_state = 0;
}

extern s32 loader_fade_state;
extern LoaderSndReq loader_snd_channel;
extern s32 (*slot_snd_alloc_channel)(LoaderSndReq *block);
extern void (*slot_0AB)(s32);
extern s32 (*slot_0A9)(void);
s32 loader_sector_size(void);
void loader_set_fade_volume(s32 arg0);
s32 loader_fade_out_step(void) {
    /* $gp-relative scratch word at 0x44($gp) holds the countdown timer */
    register volatile s32 *gp_vars asm("$28");
    s32 ok;
    s32 timer;
    s32 clamped;

    ok = loader_read_pad(0);
    ok &= loader_sector_size();
    switch (loader_fade_state) {
    case 0:
        gp_vars[0x11] = 0x1000;
        if (ok != 0) {
            slot_snd_alloc_channel(&loader_snd_channel);
            slot_0AB(0x20);
            loader_fade_state = 1;
        }
        return 0;
    case 1:
        timer = gp_vars[0x11] - 0x200;
        gp_vars[0x11] = timer;
        clamped = timer < 0 ? 0 : (timer > 0x1000 ? 0x1000 : timer);
        gp_vars[0x11] = clamped;
        loader_set_fade_volume(clamped);
        if (gp_vars[0x11] <= 0) {
            if (slot_0A9() == 0) {
                return 1;
            }
        }
        return 0;
    default:
        return 0;
    }
}

void loader_copy_shared_header();
void loader_job_init(LoaderJob *job, s32 arg1) {
    job->unk_20 = 0x28;
    job->unk_24 = 0x80040000;
    job->unk_28 = 0x80050000;
    job->unk_2C = 0x80060000;
    job->unk_18 = 0xC0;
    job->unk_1C = arg1;
    job->unk_30 = 0x80066000;
    job->disp_x = 0;
    job->disp_y = 0;
    job->screen_x = 0;
    job->unk_14 = 0x100;
    loader_copy_shared_header();
    job->unk_34 = 0;
    job->is_rgb24 = 1;
}

extern s32 *(*slot_00A)(void);
extern s32 (*slot_draw_sync)(s32 mode);
extern void (*slot_141)(void);
extern void (*slot_0AA)(s32);
void loader_fade_reset(void);
void loader_set_level(s32 value);
void loader_movie_play(s32 entry, LoaderJob *job, s32 (*callback)(void));
void loader_show_entry(s32 unused, s32 mode) {
    LoaderJob job;
    Rect rect;
    s32 *entry;

    rect.x = 0;
    rect.y = 0;
    rect.w = 0x3FF;
    rect.h = 0x1FF;

    entry = slot_00A();
    if (entry != NULL) {
        loader_job_init(&job, entry[0]);
        slot_clear_image(&rect, 0, 0, 0);
        slot_draw_sync(0);
        loader_fade_reset();
        loader_set_level(0x80);
        loader_set_fade_volume(0x1000);
        if (entry[0] != 0) {
            printf("Movie Filename:%s\n", entry[1]);
            if (mode == 1) {
                loader_movie_play(entry[1], &job, loader_fade_out_step);
            } else {
                loader_movie_play(entry[1], &job, NULL);
            }
        }
        (*(void (**)(s32))0x8001070C)(0);
        (*(void (**)(s32))0x80010710)(0);
        slot_clear_image(&rect, 0, 0, 0);
        slot_draw_sync(0);
        (*(void (**)(s32))0x8001070C)(0);
        (*(void (**)(s32))0x80010710)(1);
        slot_141();
        slot_0AA(0);
    }
}

/* The objects after this one: their service header constants. The third one also has gte.h's RCS id, packed
 * right after the message's NUL: that object wasn't built with cc1's word alignment of char arrays, so its two
 * strings are one array here. */
SVC_HEADER_CONSTS(entry_a);
SVC_HEADER_CONSTS(entry_b);
static void **const svc_table_entry_c = (void **)0x80010000;
static const char bios_version_error_and_gte_h_rcsid_entry_c[] =
    "BIOS:Version Error.\r\0"
    "$Header: /auto/bigbird/cvs/PS-X/src/gte/gte.h,v 1.2 1994/06/28 05:27:21 oka Exp $";
SVC_HEADER_CONSTS(entry_d);
SVC_HEADER_CONSTS(entry_e);

extern LoaderToneVol loader_tone_volume;
extern s32 (*slot_tone_volume)(s32); /* service slot: VAB tone volume */
void loader_read_tone_volume(void) {
    loader_tone_volume.volume = slot_tone_volume(0x401);
}

extern Raw256 loader_fade_table;
extern u8 fade_lut_lo[];
extern u8 fade_lut_hi[];
void loader_fade_tables_reset(void) {
    loader_copy_bytes(0x40, fade_lut_lo, loader_fade_table.b);
    loader_copy_bytes(0x40, fade_lut_hi, loader_fade_table.b + 0x40);
    loader_mem_set((s8 *)0x80, (s32)(loader_fade_table.b + 0x80), 0);
}

extern Raw256 loader_fade_table;
extern u8 fade_lut_lo[];
extern void (*slot_DecDCTPutEnv)(void *env);
void loader_set_fade_table(s32 scale) {
    Raw256 buf;
    u8 *src;
    u8 *lo;
    u8 *hi;
    s32 i;
    s32 v;
    s32 c;
    s32 t;

    buf = loader_fade_table;
    if (scale != 0x80) {
        src = fade_lut_lo;
        lo = buf.b;
        hi = buf.b + 0x40;
        i = 0;
        do {
            v = *src++;
            if (v >= 0x10) {
                v = v * scale;
                t = v;
                if (v < 0) {
                    t = v + 0x7F;
                }
                v = t >> 7;
                if (v >= 2) {
                    c = 0xFF;
                    if (v < 0x100) {
                        c = v;
                    }
                } else {
                    c = 2;
                }
                v = c;
            }
            *lo++ = v;
            *hi++ = v;
            i++;
        } while (i < 0x40);
    }
    slot_DecDCTPutEnv(&buf);
}

extern s32 loader_movie_rgb24_flag;
/* Same code as title_screen_setup_init (title). */
void title_screen_setup(TitleScreenSetup *out, TitleScreenParams *in) {
    out->unk_00 = in->unk_24;
    out->unk_04 = in->unk_28;
    out->unk_08 = 0;
    out->unk_0C = in->unk_2C;
    out->unk_20 = 0;
    out->unk_2C = 0;
    if (loader_movie_rgb24_flag == 1) {
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
/* Same code as movie_stream_start (title). */
s32 loader_movie_stream_start(s32 a, s32 b) {
    return slot_14C(a, b, 0x10000, 0);
}

extern void (*slot_120)(s32);
extern void (*slot_DecDCToutCallback)(s32);
extern s32 loader_movie_done_flag;
extern s32 D_800E81A0;
extern void (*slot_14B)(void *);
extern s32 movie_total_size;
/* Same code as movie_start (title). */
s32 loader_movie_start(s32 ctx, struct TitleSrc *src, s32 dec_arg, s32 cmd_mode) {
    struct TitleCmd cmd;

    slot_120(0);
    loader_movie_done_flag = 0;
    D_800E81A0 = 0;
    slot_DecDCToutCallback(dec_arg);
    cmd.unk_00 = src->unk_30;
    cmd.unk_08 = src->unk_20;
    cmd.unk_0C = 0xA;
    cmd.unk_10 = 0;
    cmd.total_size = src->unk_1C;
    cmd.unk_04 = cmd_mode;
    movie_total_size = cmd.total_size;
    slot_14B(&cmd);
    return loader_movie_stream_start(ctx, src->unk_18);
}

extern s32 (*slot_14D)(void *, void *, s32);
extern void *loader_movie_frame_data;
extern u32 loader_movie_frame_size;
extern s32 loader_movie_frame_w;
extern s32 loader_movie_frame_h;
s32 loader_movie_read_header(DctBufPair *pair) {
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
    loader_movie_frame_data = data;
    if (data[0] != hdr->key0) {
        return 0;
    }
    if (data[1] != hdr->key1) {
        return 0;
    }
    if (loader_movie_frame_w != hdr->w || loader_movie_frame_h != hdr->h) {
        loader_movie_frame_w = hdr->w;
        loader_movie_frame_h = hdr->h;
    }
    if (loader_movie_rgb24_flag == 1) {
        pair->width_a = pair->width_b = loader_movie_frame_w * 3 / 2;
    } else {
        pair->width_a = pair->width_b = loader_movie_frame_w;
    }
    pair->height_c = pair->height_a = pair->height_b = loader_movie_frame_h;
    size = hdr->size;
    loader_movie_frame_size = size;
    if (size >= movie_total_size) {
        loader_movie_done_flag = 1;
    }
    return ret;
}

extern s32 loader_fade_volume;

void loader_set_fade_volume(s32 arg0) {
    loader_fade_volume = arg0;
}

void loader_load_image_faded(Rect *src, void *data) {
    Rect rect;
    s32 full_strips;
    s32 rem_h;
    s32 blocks;
    s32 rest;
    s32 stride_units;
    s32 row_stride;
    s32 y;
    s32 i;

    if (loader_fade_volume == 0x1000) {
        slot_LoadImage(src, data);
        return;
    }
    *(UnalignedPair *) &rect = *(UnalignedPair *) src;
    full_strips = rect.h / 8;
    rem_h = src->h - full_strips * 8;
    blocks = (full_strips * loader_fade_volume) / 0x1000;
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
extern TitleSwap movie_dct_pair;
extern s32 movie_dct_active;
extern void *loader_movie_out_buf;
extern u16 movie_out_width;
extern s16 movie_out_height;
extern s32 (*slot_151)(void);
extern void (*slot_150)(void);
extern void DecDCTout(void *addr, s32 size);

void loader_movie_step(void) {
    TitleSwap *swap;
    s32 toggle;

    swap = &movie_dct_pair;
    if (slot_151()) {
        slot_150();
    }
    slot_draw_sync(0);
    loader_load_image_faded((Rect *)&swap->x, loader_movie_out_buf);
    swap->x += movie_out_width;
    if (swap->x < swap->entries[swap->toggle][0] + swap->entries[swap->toggle][2]) {
        DecDCTout(loader_movie_out_buf, (s16) movie_out_width * movie_out_height / 2);
    } else {
        swap->busy = 1;
        toggle = (swap->toggle ^ 1) != 0;
        swap->toggle = toggle;
        swap->x = swap->entries[toggle][0];
        swap->y = swap->entries[toggle][1];
    }
}

extern void (*slot_14F)(void);
extern s32 loader_movie_done_flag;
/* Same code as movie_stop (title). */
void loader_movie_stop(void) {
    slot_14F();
    loader_movie_done_flag = 1;
}

s32 loader_movie_read_header(DctBufPair *pair);
extern void *loader_movie_frame_data;
void DecDCTvlc(void *src, void *dst);
extern void (*slot_14E)(s32);
/* Same code as movie_decode_frame (title). */
s32 loader_movie_decode_frame(DctBufPair *pair) {
    s32 result;
    s32 next;

    do {
        result = loader_movie_read_header(pair);
    } while (result == 0);
    next = pair->active != 1;
    pair->active = next;
    DecDCTvlc(loader_movie_frame_data, pair->buf[next]);
    slot_14E(result);
    return 1;
}

/* Waits out a countdown (0x01000000 iterations), then flips the toggle and copies
 * the selected entry's two halfwords into x/y. Clears the busy flag on exit. */
void title_swap_flip(TitleSwap *swap) {
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

extern void (*slot_14F)(void);
/* Same code as svc_remove_frame_task (s01). */
void loader_remove_frame_task(void) {
    slot_14F();
}

extern s32 loader_fade_level;
/* stores value clamped to 0..0xFF */
void loader_set_level(s32 value) {
    s32 clamped;

    if (value >= 0) {
        clamped = 0xFF;
        if (value < 0x100) {
            clamped = value;
        }
    } else {
        clamped = 0;
    }
    loader_fade_level = clamped;
}

extern CdlLOC loader_movie_file_pos;
extern TitleSwap movie_dct_pair;
extern s32 movie_dct_active;
extern void *loader_movie_out_buf;
extern u16 movie_out_width;
extern s16 movie_out_height;
extern s32 (*slot_151)(void);
extern void (*slot_150)(void);
extern void DecDCTout(void *addr, s32 size);
extern s32 (*slot_154)(CdlFILE *, s32);
extern void (*slot_DecDCTin)(void *, s32);
extern void (*slot_DecDCTout)(void *, s32);
extern void (*slot_put_disp_env)(void *buf);
void loader_movie_step(void);
/* Same code as movie_play_loop (title). */
s32 loader_movie_run(s32 entry, LoaderJob *job, s32 (*callback)(void)) {
    MovieDispEnv env;
    CdlFILE file;
    s32 mode;
    s32 rgb24;
    s32 side;

    rgb24 = job->is_rgb24;
    if (rgb24 == 1) {
        loader_movie_rgb24_flag = rgb24;
    } else {
        loader_movie_rgb24_flag = 0;
    }
    mode = 2;
    if (loader_movie_rgb24_flag == 1) {
        mode = 3;
    }
    loader_movie_frame_size = 0;
    slot_1C3(0);
    slot_set_disp_mask(0);
    if (slot_154(&file, entry) == 0) {
        return -1;
    }
    loader_movie_file_pos = file.pos;
    title_screen_setup((TitleScreenSetup *)&movie_dct_pair, (TitleScreenParams *)job);
    if (loader_movie_start((s32)&loader_movie_file_pos, (TitleSrc *)job, (s32)loader_movie_step,
                           (s32)loader_movie_stop) == 0) {
        return 3;
    }
    loader_movie_decode_frame((DctBufPair *)&movie_dct_pair);
    for (;;) {
        loader_set_fade_table(loader_fade_level);
        slot_DecDCTin(((DctBufPair *)&movie_dct_pair)->buf[movie_dct_active], mode);
        slot_DecDCTout(loader_movie_out_buf, (s16)movie_out_width * movie_out_height / 2);
        loader_movie_decode_frame((DctBufPair *)&movie_dct_pair);
        if (loader_movie_done_flag == 1) {
            loader_remove_frame_task();
            return 0;
        }
        title_swap_flip(&movie_dct_pair);
        if (callback != NULL && callback() == 1) {
            loader_remove_frame_task();
            return 1;
        }
        side = (movie_dct_pair.toggle != 1);
        slot_1DA(&env, movie_dct_pair.entries[side][0], movie_dct_pair.entries[side][1],
                 movie_dct_pair.entries[side][2], movie_dct_pair.entries[side][3]);
        slot_1C3(0);
        env.screen = job->head;
        env.isrgb24 = loader_movie_rgb24_flag;
        if (loader_movie_rgb24_flag == 1) {
            env.disp_w = env.disp_w * 2 / 3;
        } else {
            env.disp_w = env.disp_w;
        }
        slot_put_disp_env(&env);
        slot_set_disp_mask(1);
    }
}

extern s32 (*slot_144)(void);
void loader_fade_tables_reset(void);
s32 loader_movie_run(s32 entry, LoaderJob *job, s32 (*callback)(void));
void loader_movie_play(s32 entry, LoaderJob *job, s32 (*callback)(void)) {
    s32 frame_pad[2]; /* original frame is 8 bytes larger; keeps 0x28 */

    loader_fade_tables_reset();
    slot_144();
    slot_141();
    slot_0AA(0);
    slot_draw_sync(0);
    loader_movie_run(entry, job, callback);
}

extern LoaderCtx *(*slot_shared_state)(void);
/* Returns the loader context's unk_04, clamped to 0..11 (negative gives 0). */
s32 loader_get_special_code(void) {
    s32 value = slot_shared_state()->special_code;
    s32 result;

    if (value >= 0) {
        result = 11;
        if (value < 12) {
            result = value;
        }
    } else {
        result = 0;
    }
    return result;
}

extern LoaderCtx *(*slot_shared_state)(void); /* service slot: returns the loader context */
s32 loader_get_sector_size(void) {
    slot_shared_state();
    return 0x800;
}

void loader_copy_shared_header(void *dst) {
    *(UnalignedPair *)dst = *(UnalignedPair *)((u8 *)slot_shared_state() + 0x18);
}

/* Sets the loader context's flag at index. */
void loader_set_flag(s32 index) {
    slot_shared_state()->flags[index] = 1;
}

s32 loader_is_ready(void) {
    return slot_shared_state()->unk_26 == 0;
}

s32 loader_sector_size(void) {
    return loader_get_sector_size();
}

s32 loader_get_special_event(void) {
    return loader_get_special_code();
}

extern s32 (*slot_get_exec_code)();

s32 loader_get_exec_event(void) {
    return slot_get_exec_code() - 0xA;
}

s32 loader_get_event(void) {
    s32 first_result;

    first_result = loader_get_special_event();
    if (first_result != 0) {
        return first_result + 0xC;
    }
    return loader_get_exec_event();
}

extern s32 (*slot_004)();

s32 loader_get_bank_offset(void) {
    return (slot_004() != 0) << 5;
}

s32 loader_get_dev_mode(void) {
    return slot_shared_state()->dev_mode;
}

/* Stores value in the loader context's word at 0xCC. */
void loader_set_shared_cc(s32 value) {
    slot_shared_state()->unk_CC = value;
}

/* Returns the word at offset 0xD0 of the shared loader state
 * (LoaderCtx has no field there yet). */
s32 loader_get_status(void) {
    return *(s32 *)((u8 *)slot_shared_state() + 0xD0);
}

INCLUDE_ASM("../asm/loader/nonmatchings/main", func_800E2AE4);

#ifdef NON_MATCHING
/* Returns the data word at func_800E2AE4. C companion of hand-written asm (not compiled): the word's address is built in $at (lui/addiu), then lw into $v0. */
extern u32 func_800E2AE4;

u32 func_800E2AE8(void) {
    return func_800E2AE4;
}
#else
INCLUDE_ASM("../src/loader/asm", func_800E2AE8);
#endif

#ifdef NON_MATCHING
/* Texture page id from page mode tp, blend abr and VRAM position (x, y). C companion of hand-written asm (not compiled): the asm builds each field in $at with no temporaries. */
u16 func_800E2AFC(s32 tp, s32 abr, s32 x, s32 y) {
    return ((tp << 7) & 0x180) | ((abr << 5) & 0x60) | ((y & 0x100) >> 4) | ((x & 0x3C0) >> 6);
}
#else
INCLUDE_ASM("../src/loader/asm", func_800E2AFC);
#endif

extern s32 sprite_set_next;
extern s32 loaded_image_count;
extern s32 sprite_slot_next;
extern s32 sprite_set_table;
extern s32 D_80150568;
void loader_clear_tables(void) {
    s32 i;

    i = 0;
    sprite_set_next = 0;
    loaded_image_count = 0;
    sprite_slot_next = 0;
    do {
        *(s32 *)((u8 *)&sprite_set_table + i) = 0;
        *(s32 *)((u8 *)&D_80150568 + i) = 0;
        i += 8;
    } while (i < 0x4000);
}

s32 loader_draw_sync(s32 mode);
/* Uploads `count` 4x8 VRAM tiles of 0x40 bytes each from `src` into the next
   free slots (sprite_slot_next): 30 columns x 30 rows per page, pages alternating
   between y 8 and y 264, every second page 128 further right from x 0x304.
   Returns the new slot count. */
s32 loader_alloc_sprite_slots(u8 *src, s32 count) {
    Rect rect;
    s32 slot, col, row, half_page, page_parity, page;

    slot = sprite_slot_next;
    rect.w = 4;
    rect.h = 8;
    sprite_slot_next = slot + count;
    loader_draw_sync(0);
    if (slot < sprite_slot_next) {
        do {
            col = slot % 30;
            row = slot / 30;
            page = slot / 1800;
            rect.x = col * 4 + (page << 7) + 0x304;
            half_page = slot / 900;
            page_parity = half_page - page * 2;
            rect.y = (row - half_page * 30) * 8 + (page_parity << 8) + 8;
            loader_load_image_rect(&rect, src);
            src += 0x40;
            loader_draw_sync(0);
            slot++;
        } while (slot < sprite_slot_next);
    }
    return sprite_slot_next;
}

/* Registers the sprite sets of a blob in the table at sprite_set_table, starting at
 * slot sprite_set_next, and fills each sprite's UV and texture page from its cell
 * number plus `cell_base` (30x30 cells of 8x8 per 256x256 page, pages from
 * VRAM x=768). Returns the first slot used, or -1 when the table is full. */
s32 loader_register_sprite_sets(s32 *blob, s32 cell_base) {
    s32 i;
    LoaderSpriteSet *slot;
    s32 first;
    s32 count;

    first = sprite_set_next;
    count = *blob++;
    slot = (LoaderSpriteSet *)&sprite_set_table + first;
    if (count == 0) {
        return first;
    }
    for (i = 0; i < count; i++, sprite_set_next++, slot++) {
        if (*blob++ != 0) {
            s32 groups = *blob++;
            s32 g;
            slot->data = blob;
            slot->count = groups;
            for (g = 0; g < groups; g++) {
                s32 n = *blob++;
                s32 j;
                n *= 3;
                for (j = 0; j < n; j++) {
                    blob++;
                }
                n = *blob++;
                for (j = 0; j < n; j++) {
                    s32 page_x;
                    u32 cell = (((LoaderSprite *)blob)->cell & 0xFFF) + cell_base;
                    u32 page;
                    s32 tpage;
                    page_x = (cell / 1800) * 128 + 0x300;
                    page = cell / 900;
                    getTPageAsm(tpage, 1, 0, page_x, (page & 1) << 8);
                    ((LoaderSprite *)blob)->tpage = tpage;
                    ((LoaderSprite *)blob)->uv =
                        (((cell % 30) << 11) + 0x800) | (((cell / 30) - page * 30) * 8 + 8);
                    blob += 3;
                }
            }
            if (sprite_set_next >= 0x800) {
                return -1;
            }
        }
    }
    return first;
}

extern s32 sprite_set_next;
void loader_set_limit(s32 value) {
    if (value < 0x7FF) {
        sprite_set_next = value;
    }
}

extern LoaderImageRec loader_heap_end[];

s32 loader_draw_sync(s32 mode);
s32 loader_image_register(s16 *rect, s32 mode, s32 unk_a2, s32 unk_a3, u8 *next) {
    Rect r;
    s32 index = loaded_image_count;
    s32 shift;
    s32 tpage;
    s32 page_x;
    s32 page_y;

    if (index >= 64) {
        return -1;
    }
    if (mode >= 3) {
        mode = 2;
    }
    r.x = rect[0];
    r.y = rect[1];
    shift = 2 - mode;
    r.w = rect[2] >> shift;
    r.h = rect[3];
    page_x = r.x / 64;
    page_y = r.y / 256;
    getTPageAsm(tpage, mode, 0, page_x * 64, page_y * 256);
    loader_heap_end[index].tpage = tpage;
    loader_heap_end[index].u0 = (s16)(r.x % 64) << shift;
    loader_heap_end[loaded_image_count].v0 = r.y % 256;
    loader_heap_end[loaded_image_count].u1 =
        loader_heap_end[loaded_image_count].u0 + (u8)rect[2];
    loader_heap_end[loaded_image_count].v1 =
        loader_heap_end[loaded_image_count].v0 + (u8)rect[3];
    loader_heap_end[loaded_image_count].width = unk_a2;
    loader_heap_end[loaded_image_count].height = unk_a3;
    loader_load_image_rect(&r, next);
    loader_draw_sync(0);
    loaded_image_count++;
    return index;
}

s32 loader_image_register(s16 *rect, s32 mode, s32 unk_a2, s32 unk_a3, u8 *next);
/* Builds an s16 rect {x, y, w, h}: x and y are arguments, w and h are
 * big-endian 16-bit words at data+4 and data+6 (field meaning unverified).
 * Passes the rect and the stream position after it (data+8) to loader_image_register. */
s32 loader_load_image(s16 x, s16 y, s32 unk_a2, s32 unk_a3, u8 *data) {
    s16 rect[4];
    s32 hi;
    s32 lo;

    rect[0] = x;
    rect[1] = y;
    data += 4;
    hi = *data++;
    lo = *data++;
    lo |= hi << 8;
    rect[2] = lo;
    hi = *data++;
    lo = *data++;
    lo |= hi << 8;
    rect[3] = lo;
    return loader_image_register(rect, 1, unk_a2, unk_a3, data);
}

u32 *func_800E3170(s32 addr, s32 count) {
    return loader_ot_clear(addr, count);
}

extern s32 loader_disp_x;
extern s32 loader_disp_y;
extern s32 loader_display_mode;
extern s32 loader_display_step;
s32 loader_draw_sync(s32 mode);
s32 loader_wait_frames(s32 handle);
void loader_set_disp_mask(s32 mask);
void loader_put_disp_env(void *buf);
void *loader_put_draw_env(void *env);
void loader_draw_otag(s32 handle);
void loader_display_update(s32 src_env, s32 buf_b, s32 arg_c) {
    DisplayEnv env;
    DisplayEnv *show;
    s32 x, y, clamped_x, clamped_y;

    if (loader_display_mode == 1) {
        env.raw = ((DisplayEnv *)src_env)->raw;
        x = loader_disp_x;
        if (x >= 0) {
            clamped_x = 0x17F;
            if (x < 0x180) {
                clamped_x = x;
            }
        } else {
            clamped_x = 0;
        }
        loader_disp_x = clamped_x;
        y = loader_disp_y;
        if (y >= 0) {
            clamped_y = 0x110;
            if (y < 0x111) {
                clamped_y = y;
            }
        } else {
            clamped_y = 0;
        }
        loader_disp_y = clamped_y;
        env.f.disp_x = loader_disp_x;
        env.f.disp_y = loader_disp_y;
        env.f.disp_w = 0x280;
        env.f.disp_h = 0xF0;
        env.f.screen_x = 0;
        env.f.screen_y = 0;
        env.f.screen_w = 0x100;
        env.f.screen_h = 0xF0;
        loader_draw_sync(0);
        loader_wait_frames(0);
        show = &env;
    } else {
        loader_draw_sync(0);
        loader_wait_frames(0);
        if (loader_display_step == 2) {
            loader_set_disp_mask(1);
        } else {
            loader_set_disp_mask(0);
            loader_display_step += 1;
        }
        show = (DisplayEnv *)src_env;
    }
    loader_put_disp_env(show);
    loader_put_draw_env((void *)buf_b);
    loader_draw_otag(arg_c);
}

/* GTE block with interrupts off: IR0 = ir0, IR1..IR3 loaded from the three pointers, GPF0, then the
 * FLAG read is discarded and MAC1..MAC3 stored back through the same pointers. The Status register is
 * saved in $at across the block (interrupts off = IEc cleared), so the save and restore are asm. */
void loader_gte_scale(s32 ir0, s32 *ir1, s32 *ir2, s32 *ir3) {
    cop0_irq_off_at();
    gte_set(IR0, ir0);
    gte_load(IR1, ir1, 0);
    gte_load(IR2, ir2, 0);
    gte_load(IR3, ir3, 0);
    gte_nop();
    gte_gpf0_b();
    gte_flag_discard();
    gte_store(MAC1, ir1, 0);
    gte_store(MAC2, ir2, 0);
    gte_store(MAC3, ir3, 0);
    cop0_irq_restore_at();
}

extern RECT loader_draw_mode_window_zero;
void loader_set_draw_mode(s32 prim, s32 a1, s32 a2, s32 a3, RECT *a4);
/* Sets up the next primitive from the current draw buffer and links it into OT entry ot_index. */
void loader_ot_insert_prim(s32 ot_index, s32 arg1) {
    LoaderDrawBuf *buf = (LoaderDrawBuf *)loader_buf_current();
    u8 *prim = buf->prim_next;
    u8 *entry;

    loader_set_draw_mode((s32)prim, 0, 1, arg1 & 0xFFFF, &loader_draw_mode_window_zero);
    entry = (u8 *)(ot_index * 4) + (u32)buf + 0x70; /* &buf->ot[ot_index] */
    mips_nop();
    addPrim(entry, prim);
    do {
        buf->prim_next += 0xC;
    } while (0);
}

extern s32 draw_buf_index;
extern u16 clut_ids[][2];
extern RECT loader_draw_mode_window;
/* Draws image `index` of the loader_heap_end table at (x, y) as a textured quad with the current page
 * of clut set `clut`, grey at the brightness, semi-transparent when semi is set, and links it and a
 * draw-mode primitive into OT entry ot_index. */
void loader_draw_image(s32 index, s32 x, s32 y, s32 ot_index, s32 clut, s32 semi) {
    LoaderDrawBuf *buf = (LoaderDrawBuf *)loader_buf_current();
    u8 *entry = (u8 *)(ot_index * 4) + (u32)buf; /* &buf->ot[ot_index] */
    /* the scratchpad position and the link pointer in the registers the original gives them (s6, s0) */
    register volatile s16 *pos asm("$22") = (volatile s16 *)0x1F800000;
    LoaderPolyFT4 *poly;
    register u8 *p asm("$16");
    LoaderImageRec *rec;
    u16 clut_id;
    u32 color;
    s32 u_left, v_top, u_right, v_bottom;

    entry += 0x70;
    pos[0] = x;
    pos[1] = y;
    poly = (LoaderPolyFT4 *)buf->prim_next;
    clut_id = clut_ids[clut][draw_buf_index];
    color = (loader_brightness << 16 | loader_brightness << 8 | loader_brightness) << 8;
    p = (u8 *)poly;
    if (index < loaded_image_count) {
        rec = &loader_heap_end[index];
        setPolyFT4Asm(p);
        setRGBWord(p, color);
        if (semi) {
            p[7] |= 2;
        }
        poly->clut = clut_id;
        poly->tpage = rec->tpage;
        /* the record's (u0, v0) and (u1, v1) byte pairs, read as halfwords */
        u_left = *(u16 *)&rec->u0;
        u_right = *(u16 *)&rec->u1;
        v_top = u_left >> 8;
        u_left &= 0xFF;
        v_bottom = u_right >> 8;
        u_right &= 0xFF;
        *(u16 *)&poly->u0 = u_left | (v_top << 8);
        *(u16 *)&poly->u1 = u_right | (v_top << 8);
        *(u16 *)&poly->u2 = u_left | (v_bottom << 8);
        *(u16 *)&poly->u3 = u_right | (v_bottom << 8);
        poly->x0 = pos[0];
        poly->y0 = pos[1];
        poly->x1 = pos[0] + rec->width;
        poly->y1 = pos[1];
        poly->x2 = pos[0];
        poly->y2 = pos[1] + rec->height;
        poly->x3 = pos[0] + rec->width;
        poly->y3 = pos[1] + rec->height;
        mips_nop();
        addPrim(entry, p);
        p = (u8 *)(poly + 1);
        loader_set_draw_mode((s32)p, 0, 1, 0, &loader_draw_mode_window);
        mips_nop();
        addPrim(entry, p);
        p = (u8 *)(poly + 1) + 0xC;
    }
    buf->prim_next = p;
}

s32 loader_prim_projected(s32 a0, s16 *pos, s16 *out, s32 a3, u16 a4, s32 a5);
/* Packs x/y into a local pair and forwards to loader_prim_projected. */
void loader_prim_projected_xy(s32 a0, s16 x, s16 y, s32 a3, u16 a4, s32 a5) {
    s16 pos[2];
    s16 out[2];

    pos[0] = x;
    pos[1] = y;
    loader_prim_projected(a0, pos, out, a3, a4, a5);
}

extern u16 clut_ids[][2];
s32 loader_draw_sync(s32 mode);
/* Uploads a 256x1 rect at y = 0xF0 + (x mod 16); stores y << 6 in
   clut_ids at the slot index. */
void loader_upload_clut(u16 *clut, s32 x) {
    Rect rect;
    s32 rounded;
    s32 slot;
    s32 y;

    slot = x;
    rounded = slot;
    if (slot < 0) {
        rounded = slot + 0xF;
    }
    slot = slot - ((rounded >> 4) * 0x10);
    y = slot + 0xF0;
    rect.x = 0;
    rect.y = y;
    rect.w = 0x100;
    rect.h = 1;
    loader_load_image_rect(&rect, clut);
    loader_draw_sync(0);
    clut_ids[slot][0] = y << 6;
}

extern s32 draw_buf_index;
void loader_set_enabled(s32 enable) {
    if (enable == 0) {
        draw_buf_index = 0;
    } else {
        draw_buf_index = 1;
    }
}

/* Same code as sys_get_gamemode (boot). */
s32 loader_draw_buf_index(void) {
    return draw_buf_index;
}

extern s32 loader_prim_translated(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern RECT loader_draw_mode_window;
/* Builds sprite/glyph `id` at (x, y) with the current page of clut set `clut` into the draw buffer's
   next primitive and links it into OT entry ot_index. */
void loader_draw_sprite(s32 id, s32 x, s32 y, s32 ot_index, s32 clut, s32 a5) {
    LoaderDrawBuf *buf = (LoaderDrawBuf *)loader_buf_current();
    u8 *prim;
    u8 *entry;
    u8 *node;
    s32 ot_offset;

    *(s16 *)0x1F800000 = x;
    *(s16 *)0x1F800002 = y;
    ot_offset = (ot_index << 2) + 0x70; /* offset of buf->ot[ot_index] */
    prim = (u8 *)loader_prim_translated(id, 0x1F800000, (s32)buf + ot_offset, *(s32 *)&buf->prim_next,
                               clut_ids[clut][draw_buf_index], a5);
    do {
        __asm__ volatile("" : "=r"(node) : "0"(prim));
        buf->prim_next = prim;
        loader_set_draw_mode((s32)prim, 0, 1, 0, &loader_draw_mode_window);
    } while (0);
    entry = (u8 *)(ot_index * 4) + (u32)buf + 0x70; /* &buf->ot[ot_index] */
    mips_nop();
    addPrim(entry, node);
    node = prim + 0xC;
    buf->prim_next = node;
}

s32 loader_prim_projected_wide(s32 a0, s16 *pos, s16 *out, s32 a3, u16 a4, s32 a5);
/* Draws one primitive from the current draw buffer: the loader_prim_projected / loader_prim_projected_wide
   sprite builder (chosen by loader_rot_zero_flag) writes the next primitive at buf->prim_next, then
   it is linked into OT entry ot_index. Same pattern as loader_draw_sprite. */
void loader_draw_prim(s32 ctx, s32 x, s32 y, s32 ot_index, s32 clut, s32 a5) {
    LoaderDrawBuf *buf;
    s32 prim;
    register u8 *entry asm("$4"); /* pinned to a0, as the original keeps it */

    buf = (LoaderDrawBuf *)loader_buf_current();
    *(s16 *)0x1F800000 = x;
    *(s16 *)0x1F800002 = y;
    if (loader_rot_zero_flag == 0) {
        buf->prim_next = (u8 *)loader_prim_projected(ctx, (s16 *)0x1F800000, (s16 *)&buf->ot[ot_index], (s32)buf->prim_next, clut_ids[clut][draw_buf_index], a5);
    } else {
        buf->prim_next = (u8 *)loader_prim_projected_wide(ctx, (s16 *)0x1F800000, (s16 *)&buf->ot[ot_index], (s32)buf->prim_next, clut_ids[clut][draw_buf_index], a5);
    }
    prim = (s32)buf->prim_next;
    loader_set_draw_mode(prim, 0, 1, 0, &loader_draw_mode_window);
    entry = (u8 *)(ot_index * 4) + (u32)buf + 0x70;
    mips_nop();
    addPrim(entry, prim);
    buf->prim_next = (u8 *)prim + 0xC;
}

extern s32 loader_brightness;
s32 loader_set_brightness(s32 value) {
    s32 previous = loader_brightness;
    s32 clamped;

    if (value >= 0) {
        clamped = 0xFF;
        if (value < 0x100) {
            clamped = value;
        }
    } else {
        clamped = 0;
    }
    loader_brightness = clamped;
    return previous;
}

/* Same code as fn_800BF3D8 (s01). */
s32 loader_get_brightness(void) {
    return loader_brightness;
}

/* Draws the VRAM rectangle rect (x, y, w, h in VRAM units) as textured quads at screen (x, y) with CLUT
 * clut, 128 pixels wide each, grey at the brightness, semi-transparent with blend mode semi - 1 when semi
 * is set, and links them and a draw-mode primitive into OT entry ot_index. */
void loader_draw_vram_rect(s16 *rect, s32 x, s32 y, s32 ot_index, s32 clut, s32 semi) {
    LoaderDrawBuf *buf = (LoaderDrawBuf *)loader_buf_current();
    u8 *entry;
    LoaderPolyFT4 *p;
    s32 tx, ty, w, h;
    /* ty for getTPage, and the tpage, in the registers the original's allocation gave them ($t3, $t4) */
    register s32 tpage_y asm("$11");
    register s32 tpage asm("$12");
    s32 u, v;
    u16 clut_id;
    s32 bright;
    u32 rgb;

    tx = rect[0];
    w = rect[2];
    p = (LoaderPolyFT4 *)buf->prim_next;
    entry = (u8 *)(ot_index * 4) + (u32)buf;
    entry += 0x70;
    ty = rect[1];
    clut_id = clut_ids[clut][draw_buf_index];
    bright = loader_brightness;
    rgb = ((bright << 16) | (bright << 8) | bright) << 8;
    h = rect[3];
    u = (tx % 64) << 1;
    v = ty % 256;
    tpage_y = ty;
    if (semi) {
        tpage = getTPageV1(1, semi - 1, tx, tpage_y);
        while (w > 128) {
            setPolyFT4Asm(p);
            p->code |= 2;
            setRGBWord(p, rgb);
            p->x0 = x;
            p->y0 = y;
            p->x1 = x + 128;
            p->y1 = y;
            p->x2 = x;
            p->y2 = y + h;
            p->x3 = x + 128;
            p->y3 = y + h;
            p->u0 = u;
            p->v0 = v;
            p->u1 = u + 128;
            p->v1 = v;
            p->u2 = u;
            p->v2 = v + h;
            p->u3 = u + 128;
            p->v3 = v + h;
            p->tpage = tpage;
            p->clut = clut_id;
            mips_nop();
            addPrim(entry, p);
            p++;
            tx += 64;
            x += 128;
            tpage = getTPageV1(1, semi - 1, tx, tpage_y);
            w -= 128;
        }
        setPolyFT4Asm(p);
        p->code |= 2;
    } else {
        tpage = getTPageV1(1, 0, tx, tpage_y);
        while (w > 128) {
            setPolyFT4Asm(p);
            setRGBWord(p, rgb);
            p->x0 = x;
            p->y0 = y;
            p->x1 = x + 128;
            p->y1 = y;
            p->x2 = x;
            p->y2 = y + h;
            p->x3 = x + 128;
            p->y3 = y + h;
            p->u0 = u;
            p->v0 = v;
            p->u1 = u + 128;
            p->v1 = v;
            p->u2 = u;
            p->v2 = v + h;
            p->u3 = u + 128;
            p->v3 = v + h;
            p->tpage = tpage;
            p->clut = clut_id;
            mips_nop();
            addPrim(entry, p);
            p++;
            tx += 64;
            x += 128;
            tpage = getTPageV1(1, 0, tx, tpage_y);
            w -= 128;
        }
        setPolyFT4Asm(p);
    }
    setRGBWord(p, rgb);
    p->x0 = x;
    p->y0 = y;
    p->x1 = x + w;
    p->y1 = y;
    p->x2 = x;
    p->y2 = y + h;
    p->x3 = x + w;
    p->y3 = y + h;
    p->u0 = u;
    p->v0 = v;
    p->u1 = u + w;
    p->v1 = v;
    p->u2 = u;
    p->v2 = v + h;
    p->u3 = u + w;
    p->v3 = v + h;
    p->tpage = tpage;
    p->clut = clut_id;
    mips_nop();
    addPrim(entry, p);
    p++;
    {
        register u8 *arg asm("$4") = (u8 *)p; /* set before the call's other arguments */
        u8 *mode;

        loader_set_draw_mode((s32)arg, 0, 1, 0, &loader_draw_mode_window);
        mode = (u8 *)p;
        FAKE_OPAQUE(mode); /* the original links a copy of p ($a0), not p itself */
        mips_nop();
        addPrim(entry, mode);
    }
    p = (LoaderPolyFT4 *)((LoaderDrMode *)p + 1);
    buf->prim_next = (u8 *)p;
}

/* Like loader_draw_vram_rect, but the quads are h pixels high on screen whatever the VRAM rectangle's
 * height: draws the VRAM rectangle rect (x, y, w, h in VRAM units) as textured quads at screen (x, y)
 * with CLUT clut, 128 pixels wide each, grey at the brightness, semi-transparent with blend mode
 * semi - 1 when semi is set, and links them and a draw-mode primitive into OT entry ot_index. */
void loader_draw_vram_rect_h(s16 *rect, s32 x, s32 y, s32 h, s32 ot_index, s32 clut, s32 semi) {
    LoaderDrawBuf *buf = (LoaderDrawBuf *)loader_buf_current();
    RECT dst; /* the screen rectangle; only its fields' s16 truncation is used */
    u8 *entry;
    LoaderPolyFT4 *p;
    s32 tex_h;
    s32 dst_x, dst_y, dst_h;
    s32 tex_x, tex_y, w;
    /* the tpage, in the register the original's allocation gave it ($t2) */
    register s32 tpage asm("$10");
    s32 u;
    s32 v, v_end;
    u16 clut_id;
    s32 bright;
    u32 rgb;

    dst.h = h;
    dst.x = x;
    dst.y = y;
    tex_x = rect[0];
    w = rect[2];
    p = (LoaderPolyFT4 *)buf->prim_next;
    entry = (u8 *)(ot_index * 4) + (u32)buf;
    entry += 0x70;
    tex_y = rect[1];
    dst_x = dst.x;
    clut_id = clut_ids[clut][draw_buf_index];
    dst_h = dst.h;
    bright = loader_brightness;
    rgb = ((bright << 16) | (bright << 8) | bright) << 8;
    dst_y = dst.y;
    tex_h = rect[3];
    u = (tex_x % 64) << 1;
    v = tex_y % 256;
    if (semi) {
        tpage = getTPageV1(1, semi - 1, tex_x, tex_y);
    } else {
        tpage = getTPageV1(1, 0, tex_x, tex_y);
    }
    while (w > 128) {
        setPolyFT4Asm(p);
        if (semi) {
            p->code |= 2;
        }
        setRGBWord(p, rgb);
        p->x0 = dst_x;
        p->y0 = dst_y;
        p->x1 = dst_x + 128;
        p->y1 = dst_y;
        p->x2 = dst_x;
        p->y2 = dst_y + dst_h;
        p->x3 = dst_x + 128;
        p->y3 = dst_y + dst_h;
        p->u0 = u;
        p->v0 = v;
        p->u1 = u + 128;
        p->v1 = v;
        p->u2 = u;
        p->v2 = v + tex_h;
        p->u3 = u + 128;
        p->v3 = v + tex_h;
        p->tpage = tpage;
        p->clut = clut_id;
        mips_nop();
        addPrim(entry, p);
        p++;
        tex_x += 64;
        dst_x += 128;
        if (semi) {
            s32 abr = semi - 1;
            tpage = getTPageV1(1, abr, tex_x, tex_y);
        } else {
            tpage = getTPageV1(1, 0, tex_x, tex_y);
        }
        w -= 128;
    }
    setPolyFT4Asm(p);
    if (semi) {
        p->code |= 2;
    }
    setRGBWord(p, rgb);
    p->x0 = dst_x;
    p->y0 = dst_y;
    p->x1 = dst_x + w;
    p->y1 = dst_y;
    p->x2 = dst_x;
    p->y2 = dst_y + dst_h;
    p->x3 = dst_x + w;
    p->y3 = dst_y + dst_h;
    v_end = v + tex_h;
    p->u0 = u;
    p->v0 = v;
    p->u1 = u + w;
    p->v1 = v;
    p->u2 = u;
    p->v2 = v_end;
    p->u3 = u + w;
    p->v3 = v_end;
    p->tpage = tpage;
    p->clut = clut_id;
    mips_nop();
    addPrim(entry, p);
    p++;
    {
        register u8 *arg asm("$4") = (u8 *)p; /* set before the call's other arguments */
        u8 *mode;

        loader_set_draw_mode((s32)arg, 0, 1, 0, &loader_draw_mode_window);
        mode = (u8 *)p;
        FAKE_OPAQUE(mode); /* the original links a copy of p ($a0), not p itself */
        mips_nop();
        addPrim(entry, mode);
    }
    p = (LoaderPolyFT4 *)((LoaderDrMode *)p + 1);
    buf->prim_next = (u8 *)p;
}

/* Draws a flat rectangle in colour (r, g, b) scaled by the brightness, semi-transparent with blend mode
 * semi - 1 when semi is set, and links it and its draw-mode primitive into OT entry ot_index. */
void loader_draw_rect(s16 *rect, s32 r, s32 g, s32 b, s32 ot_index, s32 semi) {
    LoaderDrawBuf *buf = (LoaderDrawBuf *)loader_buf_current();
    LoaderTilePrim *prim;
    u8 *mode;
    register u8 *next asm("$4"); /* the primitive pointer, kept in $a0 as the call's argument */
    u32 *entry;
    s32 tpage;
    s32 cr, cg, cb;

    do {
    } while (0); /* an empty block the original's register allocation needs */
    {
        register s32 *pr asm("$6") = &r;
        register s32 *pg asm("$5") = &g;
        register s32 *pb asm("$4") = &b;
        register s32 bright asm("$2") = loader_brightness;
        /* IR0 = brightness, IR1..IR3 = r, g, b, GPF0, MAC1..MAC3 back, with interrupts off */
        cop0_irq_off_at();
        gte_set(IR0, bright);
        gte_load(IR1, pr, 0);
        gte_load(IR2, pg, 0);
        gte_load(IR3, pb, 0);
        gte_nop();
        gte_gpf0_b();
        gte_flag_discard();
        gte_store(MAC1, pr, 0);
        gte_store(MAC2, pg, 0);
        gte_store(MAC3, pb, 0);
        cop0_irq_restore_at();
    }
    r /= 128;
    g /= 128;
    b /= 128;
    r = r < 0 ? 0 : (r > 0xFF ? 0xFF : r);
    g = g < 0 ? 0 : (g > 0xFF ? 0xFF : g);
    cb = b < 0 ? 0 : (b > 0xFF ? 0xFF : b);

    prim = (LoaderTilePrim *)buf->prim_next;
    cr = r;
    cg = g;
    __asm__ volatile(""); /* keeps the store of b after the loads of r and g */
    b = cb;
    prim->code = 0x60;
    prim->len = 3;
    prim->x = rect[0];
    prim->y = rect[1];
    entry = (u32 *)(ot_index * 4 + (u32)buf);
    entry += 0x70 / 4;
    prim->w = rect[2];
    prim->h = rect[3];
    if (semi) {
        prim->code |= 2;
    }
    prim->r = cr;
    prim->g = cg;
    prim->b = cb;
    mips_nop();
    do {
        addPrim(entry, prim);
    } while (0);
    next = (u8 *)(prim + 1);
    mode = next;
    if (semi) {
        getTPageAsm(tpage, 0, semi - 1, 0, 0);
        loader_set_draw_mode((s32)next, 0, 1, tpage, 0);
    } else {
        getTPageAsm(tpage, 0, 0, 0, 0);
        loader_set_draw_mode((s32)next, 0, 1, tpage, 0);
    }
    mips_nop();
    addPrim(entry, mode);
    next = mode + 0xC;
    buf->prim_next = next;
}

void loader_set_disp_env(void *buf, s32 x, s32 y, s32 w, s32 h);
void loader_set_draw_env(void *buf, s32 x, s32 y, s32 w, s32 h);
s32 loader_wait_frames(s32 handle);
void loader_set_disp_mask(s32 mask);
void loader_put_disp_env(void *buf);
void *loader_put_draw_env(void *env);
void loader_clear_image(void *rect, s32 r, s32 g, s32 b);
void screen_reset(void) {
    Rect rect;
    u8 draw_env[0x60];
    u8 disp_env[0x18];

    rect.w = 0x3FF;
    rect.x = 0;
    rect.y = 0;
    rect.h = 0x1FF;
    loader_set_disp_env(disp_env, 0, 0, 0x100, 0xF0);
    loader_set_draw_env(draw_env, 0, 0, 0x100, 0xF0);
    loader_wait_frames(0);
    loader_set_disp_mask(0);
    loader_put_disp_env(disp_env);
    loader_put_draw_env(draw_env);
    loader_clear_image(&rect, 0, 0, 0);
    loader_draw_sync(0);
    loader_wait_frames(0);
    loader_clear_tables();
}

/* hand-written: RTPT primitive routine whose tail loader_prim_projected_wide/loader_prim_translated share (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* LoaderSpriteSet: data = u32 n_tri; n_tri * 3 vertex words (s16 x, s16 y); u32 n_quad; n_quad * 3 words
   (4 vertex indices, flip bits << 14 in the halfword at +4, v | u << 8 | tpage << 16); count = blocks. */
typedef enum { SPRITE_PROJECT, SPRITE_TRANSLATE } SpriteVertexMode;

/* sprite_set_table is declared below as s32 (its first word): used here as the array it is. */
extern s32 sprite_set_next;
extern s32 sprite_set_table;
/* Pseudo-intrinsic: SXY of one vertex word through RTPT (the asm projects three at a time). */
u32 gte_rtps_xy(u32 vxy);

/* Shared body of loader_prim_projected / loader_prim_projected_wide / loader_prim_translated: builds the textured quads (POLY_FT4,
   0x28 bytes) of sprite set `set` at `prim`, culls those off screen, chains each into the OT slot `ot`
   and returns the next free primitive address.
   pos is the (x, y) screen origin (GTE OFX/OFY in the RTPT variants). uv_hi/uv_flip_hi are the far UV
   offsets of an unflipped / flipped quad (7 and 0 for the 8x8 variant, 8 and -1 for the 493C one). */
static u8 *loader_sprite_prims(s32 set, s16 *pos, u32 *ot, u8 *prim, u16 clut, s32 semi_trans,
                               SpriteVertexMode mode, s32 uv_hi, s32 uv_flip_hi) {
    u32 vtx[256]; /* scratchpad 0x1F800000: screen XY per vertex index */
    u32 brightness = (u32)loader_brightness & 0xFF;
    u32 link = *ot & 0xFFFFFF; /* previous OT head; prims are chained in front of it */
    u8 code = 0x2C | (semi_trans ? 2 : 0);
    u16 abr = semi_trans ? ((semi_trans - 1) & 3) << 5 : 0;
    LoaderSpriteSet *ss;
    u32 *p;
    s32 blk, n, i;

    if (set >= sprite_set_next) {
        return prim;
    }
    ss = &((LoaderSpriteSet *)&sprite_set_table)[set];
    p = (u32 *)ss->data;
    for (blk = ss->count; blk != 0; blk--) {
        n = *p++; /* vertex triples */
        for (i = 0; i < n * 3; i++) {
            if (mode == SPRITE_PROJECT) {
                /* RTPT: three vertices at once, VZ = 0, rotation from the GTE, OFX/OFY = pos */
                vtx[i] = gte_rtps_xy(p[i]); /* pseudo: GTE-projected SXY of vertex word p[i] */
            } else {
                /* plain 2D move: low half += x, high half += y, no carry between them */
                vtx[i] = ((p[i] + pos[0]) & 0xFFFF) | ((p[i] + ((u32)(s32)pos[1] << 16)) & 0xFFFF0000);
            }
        }
        p += n * 3;
        n = *p++; /* quads */
        for (; n != 0; n--, p += 3) {
            u32 idx = p[0];        /* 4 vertex indices, one per byte */
            u32 uvw = p[2];        /* v | u << 8 | tpage << 16 */
            u32 flip = (p[1] & 0xFFFF) >> 14; /* 0 none, 1 flip U, 2 flip V, 3 both */
            u32 xy0 = vtx[idx & 0xFF], xy1 = vtx[(idx >> 8) & 0xFF];
            u32 xy2 = vtx[(idx >> 16) & 0xFF], xy3 = vtx[idx >> 24];
            u32 sum = xy0 + xy1 + xy2 + xy3 + 0x20;
            s32 u = (uvw >> 8) & 0xFF, v = uvw & 0xFF, u0, u1, v0, v1;
            LoaderPolyFT4 *q = (LoaderPolyFT4 *)prim;

            if ((sum & 0xFFFF) > 0x540 || ((sum >> 16) + 0x20) & 0xFC00) {
                continue; /* off screen */
            }
            u0 = u; u1 = u + uv_hi;
            v0 = v; v1 = v + uv_hi;
            if (flip & 1) { u0 = u + 7; u1 = u + uv_flip_hi; }
            if (flip & 2) { v0 = v + 7; v1 = v + uv_flip_hi; }
            q->len = 9;
            q->code = code;
            q->r = q->g = q->b = brightness;
            *(u32 *)&q->x0 = xy0; *(u32 *)&q->x1 = xy1; *(u32 *)&q->x2 = xy2; *(u32 *)&q->x3 = xy3;
            q->u0 = u0; q->v0 = v0; q->clut = clut;
            q->u1 = u1; q->v1 = v0; q->tpage = (uvw >> 16) | abr;
            q->u2 = u0; q->v2 = v1;
            q->u3 = u1; q->v3 = v1;
            ((LoaderPrimTag *)q)->addr = link;
            link = (u32)prim; /* next quad links to this one */
            prim += 0x28;
        }
    }
    *ot = (*ot & 0xFF000000) | link;
    return prim;
}
#endif

#ifdef NON_MATCHING
/* Sprite-set quad builder, GTE-projected vertices, 8x8 UV span. C companion of hand-written asm (not compiled):
   uses $at/$t0-$t9 as storage and the CP2 pipeline (next RTPT's inputs loaded inside the loop); the other
   two builders copy its prologue and loop, and their empty-set exit jumps into this one's epilogue. */
s32 loader_prim_projected(s32 set, s16 *pos, s16 *ot, s32 prim, u16 clut, s32 semi_trans) {
    return (s32)loader_sprite_prims(set, pos, (u32 *)ot, (u8 *)prim, clut, semi_trans, SPRITE_PROJECT, 7, 0);
}
#else
INCLUDE_ASM("../src/loader/asm", loader_prim_projected);
#endif

/* hand-written: branches into loader_prim_projected's tail (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* Same as loader_prim_projected with UVs one texel wider (u + 8, flipped u - 1). C companion of hand-written asm (not
   compiled): a copy of loader_prim_projected whose empty-set exit branches into loader_prim_projected's epilogue. */
s32 loader_prim_projected_wide(s32 set, s16 *pos, s16 *ot, s32 prim, u16 clut, s32 semi_trans) {
    return (s32)loader_sprite_prims(set, pos, (u32 *)ot, (u8 *)prim, clut, semi_trans, SPRITE_PROJECT, 8, -1);
}
#else
INCLUDE_ASM("../src/loader/asm", loader_prim_projected_wide);
#endif

/* hand-written: branches into loader_prim_projected's tail (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* Same quad builder with plain 2D vertices: each vertex word is moved by pos instead of GTE-projected (UV span
   as loader_prim_projected_wide). C companion of hand-written asm (not compiled): reads pos into $t2/$t3 as GTE OFX/OFY
   and adds in registers; its empty-set exit branches into loader_prim_projected's epilogue. */
s32 loader_prim_translated(s32 set, s32 pos, s32 ot, s32 prim, s32 clut, s32 semi_trans) {
    return (s32)loader_sprite_prims(set, (s16 *)pos, (u32 *)ot, (u8 *)prim, (u16)clut, semi_trans, SPRITE_TRANSLATE, 8, -1);
}
#else
INCLUDE_ASM("../src/loader/asm", loader_prim_translated);
#endif

extern s32 D_8019468C;
extern s16 D_8019466E;
extern s16 D_8019467E;
extern s32 D_80194668;
extern LoaderSlot loader_slot_pool[];
extern s32 D_801070E8;
extern s32 *loader_list_sentinel;
extern s32 **loader_list_head;
extern s32 D_801070E4;
void loader_slots_init(void) {
    s32 i;
    s32 off;
    s32 *p;
    s32 **q;
    s16 one;

    i = 0;
    one = 1;
    off = 0;
    do {
        *(s32 *)((u8 *)&D_8019468C + off) = 0;
        *(s16 *)((u8 *)&D_8019466E + off) = one;
        *(s16 *)((u8 *)&D_8019467E + off) = one;
        *(s32 *)((u8 *)&D_80194668 + off) = 0;
        *(s32 *)((u8 *)&loader_slot_pool + off) = 0;
        off += 0x6C;
    } while (++i < 0x40);
    p = &D_801070E8;
    q = &loader_list_sentinel;
    *p = 0;
    loader_list_head = q;
    *q = p;
    D_801070E4 = 0;
}

extern s32 loader_free_slot_count;
/* Same code as get_key_count (s01). */
s32 loader_released_count(void) {
    return loader_free_slot_count;
}

/* Same code as arena_top (s04). */
void *loader_node_list_head(void) {
    return loader_list_head;
}

/* Same code as arena_top (s01). */
void *loader_node_list_sentinel(void) {
    return loader_list_sentinel;
}

/* Links node 'n' into the list right after 'at'. */
void node_insert_after(Node *at, Node *n) {
    Node *old_next;

    old_next = at->next;
    at->next = n;
    n->prev = at;
    n->next = old_next;
    old_next->prev = n;
}

/* Link `node` into the list directly after `after`. */
void dlist_insert_after(DListNode *after, DListNode *node) {
    DListNode *next = after->next;

    after->next = node;
    node->prev = after;
    node->next = next;
    next->prev = node;
}

void dlist_remove(Node *node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
}

extern s32 loader_free_slot_count;
/* Takes the first free slot of the 64 (unk_28 != 1), links it after the
   list head loader_list_sentinel and marks it in use; NULL when none is free. */
void *slot_alloc(void) {
    s32 i;
    LoaderSlot *slot;

    if (loader_free_slot_count != 0) {
        for (i = 0; i < 0x40; i++) {
            if (loader_slot_pool[i].in_use != 1) {
                break;
            }
        }
        if (i != 0x40) {
            slot = &loader_slot_pool[i];
            loader_free_slot_count -= 1;
            node_insert_after((Node *)&loader_list_sentinel, &slot->node);
            loader_slot_pool[i].unk_0A = 1;
            loader_slot_pool[i].unk_1A = 1;
            loader_slot_pool[i].unk_14 = 0;
            loader_slot_pool[i].unk_24 = 0;
            loader_slot_pool[i].in_use = 1;
            return slot;
        }
    }
    return NULL;
}

extern s32 loader_free_slot_count;
/* Resets a slot's fields, unlinks it from its list and counts the call in loader_free_slot_count. */
void slot_release(LoaderSlot *slot) {
    slot->in_use = 0;
    slot->unk_0A = 1;
    slot->unk_1A = 1;
    slot->unk_14 = 0;
    slot->unk_24 = 0;
    dlist_remove(&slot->node);
    loader_free_slot_count += 1;
}

extern void *loader_node_list_head(void);
void loader_run_callbacks2(void) {
    LoaderNode *node;

    node = loader_node_list_head();
    if (node != NULL) {
        do {
            if (node->state == 1 && node->flags2 == 0) {
                if (node->callback2 != NULL) {
                    node->callback2(&node->unk_18, node);
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}

void loader_run_callbacks(void) {
    LoaderNode *node;

    node = loader_node_list_head();
    if (node != NULL) {
        do {
            if (node->state == 1 && node->flags == 0) {
                if (node->callback != NULL) {
                    node->callback(&node->unk_18, node);
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}

extern u8 loader_heap_base[];
extern u8 *loader_heap_top;
void loader_slots_init(void);
/* Points the allocator top at the pool at loader_heap_base, sets the 0x3F counter, then runs the setup at loader_slots_init. */
void loader_pool_init(void) {
    loader_heap_top = loader_heap_base;
    loader_free_slot_count = 0x3F;
    loader_slots_init();
}

extern u8 *loader_heap_top;
/* Bump allocator: returns the old heap top and advances it, or NULL if the
   new top would reach the end of the heap. */
u8 *heap_alloc(s32 size) {
    u8 *old = loader_heap_top;
    u8 *new_top = old + size;

    if (new_top >= (u8 *)loader_heap_end) {
        return NULL;
    }
    loader_heap_top = new_top;
    return old;
}

/* Same code as arena_top (s12). */
void *loader_get_heap_top(void) {
    return loader_heap_top;
}

/* Sets the bump allocator's top to new_top and returns the previous top. */
u8 *loader_set_heap_top(u8 *new_top) {
    u8 *old = loader_heap_top;

    loader_heap_top = new_top;
    return old;
}

extern LoaderSndReq loader_sound_request;
extern s32 (*slot_snd_alloc_channel)(LoaderSndReq *block); /* service slot: sound request block */
void sound_alloc_channel(void) {
    slot_snd_alloc_channel(&loader_sound_request);
}

extern LoaderSndReq loader_sound_request_alt;
/* Same code as sound_alloc_channel (loader). */
void sound_alloc_channel_alt(void) {
    slot_snd_alloc_channel(&loader_sound_request_alt);
}

extern void sound_alloc_channel_alt(void);
/* Per-frame update of a loader node. Waits until its counter (unk_2C) passes
 * 0x140 or its owner's owner field is 2, then releases the node and marks the
 * owner done. Counter 0x40 triggers sound_alloc_channel_alt. */
void loader_node_update(void *unused, LoaderNode *node) {
    s32 state = node->unk_2C;

    if (state < 0x141 && ((LoaderNode *)node->owner)->owner != 2) {
        node->unk_2C = state + 4;
    } else {
        ((LoaderNode *)node->owner)->owner = 1;
        slot_release((LoaderSlot *)node);
    }
    if (node->unk_2C == 0x40) {
        sound_alloc_channel_alt();
    }
}


s32 func_800E2AFC(s32 a0, s32 a1, s32 a2, s32 a3);
/* Draws the cursor marker at x = node->unk_2C: a gouraud quad (dark/white bands),
   then a black triangle and a black quad covering the right side, linked into OT 1. */
void loader_cursor_draw(void *unused, LoaderNode *node) {
    LoaderDrawBuf *buf = (LoaderDrawBuf *)loader_buf_current();
    LoaderPolyG4 *g4;
    LoaderPolyF3 *f3;
    LoaderPolyF4 *f4;

    g4 = (LoaderPolyG4 *)buf->prim_next;
    g4->tag.len = 8;
    g4->code = 0x3A;
    g4->x3 = g4->x0 = node->unk_2C;
    g4->x1 = node->unk_2C + 0x30;
    g4->x2 = node->unk_2C - 0x30;
    g4->y0 = 0x58;
    g4->y1 = 0x58;
    g4->y2 = 0x84;
    g4->y3 = 0x84;
    g4->r0 = 2; g4->g0 = 2; g4->b0 = 2;
    g4->r1 = 0xFF; g4->g1 = 0xFF; g4->b1 = 0xFF;
    g4->r2 = 2; g4->g2 = 2; g4->b2 = 2;
    g4->r3 = 0xFF; g4->g3 = 0xFF; g4->b3 = 0xFF;
    g4->tag.addr = ((LoaderPrimTag *)&buf->ot[1])->addr;
    ((LoaderPrimTag *)&buf->ot[1])->addr = (u32)g4;
    buf->prim_next += sizeof(LoaderPolyG4);

    f3 = (LoaderPolyF3 *)buf->prim_next;
    f3->tag.len = 4;
    f3->code = 0x20;
    f3->x1 = node->unk_2C;
    f3->x2 = f3->x0 = node->unk_2C + 0x30;
    f3->y0 = 0x58;
    f3->y1 = f3->y2 = 0x84;
    f3->r0 = 0; f3->g0 = 0; f3->b0 = 0;
    f3->tag.addr = ((LoaderPrimTag *)&buf->ot[1])->addr;
    ((LoaderPrimTag *)&buf->ot[1])->addr = (u32)f3;
    buf->prim_next += sizeof(LoaderPolyF3);

    f4 = (LoaderPolyF4 *)buf->prim_next;
    f4->tag.len = 5;
    f4->code = 0x28;
    f4->x2 = f4->x0 = node->unk_2C + 0x30;
    f4->x3 = f4->x1 = 0x100;
    f4->y1 = f4->y0 = 0x58;
    f4->y3 = f4->y2 = 0x84;
    f4->r0 = 0; f4->g0 = 0; f4->b0 = 0;
    f4->tag.addr = ((LoaderPrimTag *)&buf->ot[1])->addr;
    ((LoaderPrimTag *)&buf->ot[1])->addr = (u32)f4;
    buf->prim_next += sizeof(LoaderPolyF4);

    loader_ot_insert_prim(1, func_800E2AFC(0, 2, 0, 0));
}

void loader_node_init(LoaderNode *node, s32 owner) {
    node->owner = owner;
    node->unk_2C = 0;
}

/* Loader task callback: the first argument is unused. Once the source's
 * counter is 2, it counts the entry's own counter up to 0x21, then stops the
 * loader and releases the slot. */
void loader_entry_update(void *unused, LoaderEntry *entry) {
    if (entry->source->unk_30 == 2) {
        entry->char_index++;
        if (entry->char_index >= 0x21) {
            loader_request_stop();
            slot_release((LoaderSlot *)entry);
        }
    }
}

s32 func_800E2AFC(s32 a0, s32 a1, s32 a2, s32 a3);
void loader_draw_fade_quad(s32 a0, LoaderDrawObj *obj) {
    LoaderDrawBuf *buf;
    LoaderSprt *sprt;
    s32 tpage;
    s32 i;
    s32 row;
    s32 col;
    u32 link;

    if (obj->task->state == 2) {
        buf = (LoaderDrawBuf *)loader_buf_current();
        sprt = (LoaderSprt *)buf->prim_next;
        tpage = func_800E2AFC(2, 1, buf->unk_0, buf->unk_2);
        for (i = 0; i < 4;) {
            ((u8 *)&sprt->tag)[3] = 4;
            sprt->code = 0x66;
            row = (i / 2) * 2;
            col = i++ - row;
            sprt->x = col * 2 - 1;
            sprt->y = row - 1;
            sprt->w = 0xFF;
            sprt->h = 0xEF;
            sprt->u = 0;
            sprt->v = 0;
            sprt->r = 0x22;
            sprt->g = 0x22;
            sprt->b = 0x22;
            link = buf->ot[1] & 0xFFFFFF;
            sprt->tag = (sprt->tag & 0xFF000000) | (link & 0xFFFFFF);
            buf->ot[1] = (buf->ot[1] & 0xFF000000) | ((u32)sprt & 0xFFFFFF);
            sprt++;
        }
        buf->prim_next += 0x50;
        loader_ot_insert_prim(1, tpage & 0xFFFF);
    }
}

void loader_state_init(LoaderState *state, s32 value) {
    state->unk_2C = value;
    state->char_count = 0;
}

void loader_state_reset(LoaderState *s) {
    s->text_y = 0x8C;
    s->text_x = s->text_start_x;
}

/* Maps a character code (from '0' up) to a table index; returns 0x10 when out of range. */
s32 font_glyph_index(s32 ch) {
    s32 index;
    s32 in_range;
    s32 result;

    index = ch - 0x30;
    in_range = index < 0x2D;
    if (index < 0) {
        return 0x10;
    }
    result = 0x10;
    if (in_range) {
        result = index;
    }
    return result;
}

extern u8 font_glyph_widths[];
s32 font_glyph_width(s32 ch) {
    return font_glyph_widths[font_glyph_index(ch)];
}

void loader_draw_sprite(s32 id, s32 x, s32 y, s32 ot_index, s32 clut, s32 a5);
extern s32 font_glyph_offsets[];
void font_draw_char(s32 arg0, s32 arg1, s32 arg2) {
    s32 index;

    index = font_glyph_index(arg2 & 0xFF) & 0xFF;
    loader_draw_sprite(index, arg0, arg1 + font_glyph_offsets[index], 0, 0, 0);
}

s32 font_text_width(u8 *arg0) {
    s32 temp_v0;
    s32 var_s1;
    u8 *var_s0;
    u8 var_a0;

    var_s0 = arg0;
    var_a0 = *var_s0;
    var_s1 = 0;
    if (var_a0 != 0) {
        do {
            var_s0 += 1;
            temp_v0 = font_glyph_width(var_a0);
            var_a0 = *var_s0;
            var_s1 += temp_v0;
        } while (var_a0 != 0);
    }
    return var_s1;
}

s32 loader_get_video_mode(void);
s32 video_speed_scale(void) {
    if (loader_get_video_mode() != 0) {
        return 0x4CC;
    }
    return 0x400;
}

s32 video_speed_scale_q11(void) {
    if (loader_get_video_mode() != 0) {
        return 0x999;
    }
    return 0x800;
}

s32 loader_hold_frames(void) {
    s32 ready = loader_get_video_mode();
    if (ready != 0) {
        return 0xC;
    }
    return 0x10;
}

void loader_text_run(s16 *state_arg, LoaderEntry *entry_arg) {
    LoaderEntry *entry = entry_arg;
    s16 *state = state_arg;
    u8 *ch;
    s32 done;

    s32 current = *state;

again:
    switch (current) {
    case 0:
        if (entry->source->unk_30 != 1) {
            return;
        }
        *state = 1;
        current = 1;
        goto again;
    case 1:
        ch = entry->name;
        ch += entry->char_index;
        entry->step_accum += video_speed_scale_q11();
        if (entry->step_accum > 0x1000) {
            if (*ch != 0) {
                entry->char_index++;
                sound_alloc_channel();
            } else {
                entry->phase = (entry->phase + video_speed_scale()) % 0xFFF;
                entry->hold_counter++;
                if (loader_is_finished() && loader_hold_frames() < entry->hold_counter) {
                    *state = 2;
                }
            }
            entry->step_accum -= 0x1000;
        }
        done = loader_read_pad(0);
        done &= loader_sector_size();
        if (done) {
            loader_set_shared_cc(1);
        }
        if (loader_is_finished() && done) {
            *state = 2;
        }
        break;
    case 2:
        entry->source->unk_30 = 2;
        slot_release((LoaderSlot *)entry);
        break;
    }
}

s32 loader_get_brightness(void);
void loader_state_reset(LoaderState *s);
void font_draw_char(s32 x, s32 y, s32 ch);
void loader_entry_draw(s32 unused, LoaderState *s) {
    s32 frames;
    s32 count;
    s32 x;
    s32 y;
    u8 ch;
    u8 *text;

    frames = loader_get_brightness();
    loader_set_brightness((frames * 4) / 5);
    text = s->text;
    loader_state_reset(s);
    x = s->text_x;
    count = s->char_count;
    y = s->text_y;
    if (count > 0) {
        do {
            ch = *text;
            text++;
            font_draw_char(x, y, ch);
            count--;
            x += font_glyph_width(ch);
        } while (count > 0);
    }
    if (s->char_count != 0 && *s->text != 0 && s->unk_48 < 0x801) {
        font_draw_char(x, y, 0x3C);
    }
    loader_set_brightness(frames);
}

void loader_entry_init(LoaderEntry *entry, LoaderSource *source) {
    entry->source = source;
    entry->char_index = 0;
    entry->step_accum = 0;
    entry->name = source->name_info->text;
    entry->text_x = (0xFA - font_text_width(entry->name)) / 2;
    entry->phase = 0x800;
    entry->hold_counter = 0;
}

/* Loader task update: state 0 becomes 1, then unk_2C grows by 0x2B33 until it
 * passes 0x9FFFF, which moves the state to 2. In state 2 the owner check
 * releases the slot. */
void loader_ramp_update(s16 *state, LoaderNode *node) {
    s16 st = *state;

    switch (st) {
    case 0:
        *state = 1;
        /* fall through */
    case 1:
        if (node->unk_2C <= 0x9FFFF) {
            node->unk_2C += 0x2B33;
        } else {
            *state = 2;
        }
        break;
    case 2:
        if (node->owner == st) {
            slot_release((struct LoaderSlot *)node);
        }
        break;
    }
}

s32 loader_get_brightness(void);
void loader_draw_pair(void *unused, LoaderNode *node) {
    LoaderPair *pair;
    LoaderPair *pair2;
    s32 saved;
    s32 y;

    saved = loader_get_brightness();
    loader_set_brightness(node->unk_2C >> 12);

    pair = (LoaderPair *)node->pair;
    y = 0x5C;
    if (pair->second != -1) {
        y = 0x58;
    }
    loader_draw_sprite(pair->first, 0x7C, y, 0, 0, 0);

    pair2 = (LoaderPair *)node->pair;
    if (pair2->second != -1) {
        loader_draw_sprite(pair2->second, 0x7C, y + 0xC, 0, 0, 0);
    }
    loader_set_brightness(saved);
}

extern void *slot_alloc(void);
void loader_node_update(void *unused, LoaderNode *node);
void loader_entry_update(void *unused, LoaderEntry *entry);
void loader_cursor_draw();  /* a function reached by pointer */
void loader_draw_fade_quad(s32 a0, LoaderDrawObj *obj);  /* a function reached by pointer */
void loader_entry_draw();  /* a function reached by pointer */
void loader_text_run(s16 *state_arg, LoaderEntry *entry_arg);
/* Sets up the three loader tasks of this stage: each one takes the next pool
 * object and runs its setup with the owner (task) as argument. */
void loader_setup_tasks(LoaderTask *task, s32 arg) {
    LoaderTask *sub;
    LoaderNode *node = (LoaderNode *)task;

    node->unk_2C = 0;
    node->pair = arg;
    node->owner = 0;
    sub = slot_alloc();
    if (sub != NULL) {
        sub->update = loader_node_update;
        sub->unk_0A = 0;
        sub->unk_08 = 0;
        sub->unk_24 = &loader_cursor_draw;
        sub->unk_1A = 0;
        sub->unk_18 = 0;
        loader_node_init((LoaderNode *)sub, (s32)task);
        sub = slot_alloc();
        if (sub != NULL) {
            sub->update = loader_entry_update;
            sub->unk_0A = 0;
            sub->unk_08 = 0;
            sub->unk_24 = &loader_draw_fade_quad;
            sub->unk_1A = 0;
            sub->unk_18 = 0;
            loader_state_init((LoaderState *)sub, (s32)task);
            sub = slot_alloc();
            if (sub != NULL) {
                sub->update = loader_text_run;
                sub->unk_0A = 0;
                sub->unk_08 = 0;
                sub->unk_24 = &loader_entry_draw;
                sub->unk_1A = 0;
                sub->unk_18 = 0;
                loader_entry_init((LoaderEntry *)sub, (LoaderSource *)task);
            }
        }
    }
}

extern void *slot_alloc(void);
void loader_ramp_update(s16 *state, LoaderNode *node);
void loader_draw_pair();  /* a function reached by pointer */
extern void loader_setup_tasks(LoaderTask *task, s32 arg);
extern LoaderToneVol loader_tone_volume_a;
extern LoaderToneVol loader_tone_volume_b;
/* Allocates a loader task, sets it up and reads two tone volumes through the
 * service slot at 0x800102F0 (slot_tone_volume). */
void loader_init(s32 arg) {
    LoaderTask *task = slot_alloc();
    s32 (**slot)(s32);

    if (task != NULL) {
        task->update = (void (*)(void))loader_ramp_update;
        task->unk_0A = 0;
        task->unk_08 = 0;
        task->unk_24 = &loader_draw_pair;
        task->unk_1A = 0;
        task->unk_18 = 0;
        loader_setup_tasks(task, arg);
        slot = (s32 (**)(s32))0x800102F0;
        loader_tone_volume_a.volume = (*slot)(0x805);
        loader_tone_volume_b.volume = (*slot)(0x806);
    }
}
