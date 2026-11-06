/* sound_mode: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

extern void (*slot_0AE)(s32);
void apply_sound_mode(void) {
    u8 mode = title_shared_state_get()->unk_24;

    switch (mode) {
    case 0:
        slot_0AE(0);
        break;
    case 1:
        slot_0AE(1);
        break;
    case 2:
        slot_0AE(2);
        break;
    }
}

extern s32 title_fade_state;
extern s32 title_pad_prev;
void title_pad_reset(void) {
    title_fade_state = 0;
    title_pad_prev = title_input_mask();
}

extern void (*slot_0AB)(s32);
extern s32 (*slot_0A9)(void);
extern s32 title_fade_level;
void title_set_fade_level(s32 arg0);
void title_entries_start(u32 slot_ids);
s32 title_fade_out_step(void) {
    s32 pad;
    s32 pressed;

    pad = read_pad(0);
    if (title_pad_prev == 0 && (pad & title_input_mask()) != 0) {
        pressed = 1;
    } else {
        pressed = 0;
    }
    title_pad_prev = pad;
    switch (title_fade_state) {
    case 0:
        title_fade_level = 0x1000;
        if (pressed == 1) {
            slot_0AB(0x20);
            title_entries_start(0x1FFFF);
            title_fade_state = pressed;
        }
        return 0;
    case 1:
        title_fade_level -= 0x200;
        title_fade_level = MAX(MIN(title_fade_level, 0x1000), 0);
        title_set_fade_level(title_fade_level);
        if (title_fade_level <= 0) {
            if (slot_0A9() == 0) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

void movie_params_init(MovieParams *params, s32 value) {
    Pad3dSoundInfo *src;
    u8 *buf0;
    u8 *buf1;
    u8 *buf2;

    buf0 = prim_buf_start;
    buf1 = buf0 + 0x10000;
    buf2 = buf1 + 0x10000;
    src = title_shared_state_get();
    do { } while (0);
    params->unk_20 = 0x1E;
    params->buf2 = buf2;
    buf2 += 0x6000;
    params->height = 0xC0;
    params->unk_1C = value;
    params->buf0 = buf0;
    params->buf1 = buf1;
    params->buf2_end = buf2;
    params->unk_08 = 0;
    params->unk_0C = 0;
    params->unk_10 = 0;
    params->width = 0x100;
    params->head = src->unk_18;
    params->unk_34 = 0;
    params->rgb24 = 1;
}

extern s32 *(*slot_00A)(s32);
extern void (*slot_set_disp_mask)(s32 mask);
void title_set_intensity(s32 value);
extern void title_pad_reset(void);
extern void play_movie(s32 name, MovieParams *params, s32 (*abort_fn)(void));
extern s32 title_fade_out_step(void);
s32 title_movie_play(s32 entry_id) {
    MovieParams movie_buf;
    s16 rect[4];
    void (**gfx_reset)(s32);
    void (**clear_fn)(s16 *, s32, s32, s32);
    void (**sync_fn)(s32);
    s32 *movie_info;

    slot_0B3();
    slot_0BD();
    gfx_reset = (void (**)(s32))0x8001070C;
    (*gfx_reset)(0);
    (*gfx_reset)(0);
    movie_info = slot_00A(entry_id);
    if (movie_info == NULL) {
        return 0;
    }
    movie_params_init(&movie_buf, movie_info[0]);
    sync_fn = (void (**)(s32))0x80010728;
    (*sync_fn)(0);
    title_pad_reset();
    title_set_intensity(0x80);
    title_set_fade_level(0x1000);
    if (movie_info[0] != 0) {
        play_movie(movie_info[1], &movie_buf, title_fade_out_step);
    }
    (*gfx_reset)(0);
    slot_set_disp_mask(0);
    (*sync_fn)(0);
    clear_fn = (void (**)(s16 *, s32, s32, s32))0x80010724;
    rect[0] = 0;
    rect[1] = 0;
    rect[2] = 0x400;
    rect[3] = 0xF0;
    (*clear_fn)(rect, 0, 0, 0);
    (*sync_fn)(0);
    rect[0] = 0;
    rect[1] = 0xF0;
    rect[2] = 0x2FF;
    rect[3] = 0x110;
    (*clear_fn)(rect, 0, 0, 0);
    (*sync_fn)(0);
    (*gfx_reset)(0);
    slot_141();
    return 1;
}
