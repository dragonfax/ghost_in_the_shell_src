/* complete: one of complete's own original source files (scripts/objmap.py); part of src/complete/main.c's unit, included there. */

void screen_wipe_open_step(s32 arg0) {
    s32 temp_s0;
    s32 temp_s0_2;

    temp_s0 = arg0 * 4;
    screen_restore_row(temp_s0);
    screen_restore_row(temp_s0 | 1);
    temp_s0_2 = (0x78 - arg0) * 4;
    screen_restore_row(temp_s0_2 | 2);
    screen_restore_row(temp_s0_2 | 3);
}

void disp_fill_black_rows(s32 y);

void screen_wipe_close_step(s32 arg0) {
    disp_fill_black_rows(arg0 * 4);
    disp_draw_sync(0);
    disp_fill_black_rows(((0x78 - arg0) * 4) | 2);
    disp_draw_sync(0);
}

void rect_set_fraction(CompleteRect *rect, s32 amount);
void disp_setup_960x480(void);
void disp_setup_320x240(void);
void sound_play_request(u32 arg0);
void screen_blank(void);
void disp_pal_adjust_y(void *obj);
extern void (*slot_0B3)(void);
extern s32 (*slot_0A5)(void);
extern s32 (*slot_0A9)(void);
void func_80100B80(void);
void func_80100A24(void);
void func_80100624(void);
void disp_env_set_default(void *buf, s32 x, s32 y, s32 w, s32 h);
void func_80100B04(void *p);
void disp_put_env(void *draw_env);
void func_80100A54(u32 arg0);
s32 wipe_frame_wait(s32 handle);
s32 pad_read(void);
void func_8010078C(void);
void func_80100AC8(void);
void complete_image_show(void) {
    CompleteDispEnv disp;
    s32 i;
    s32 j;

    func_80100B80();
    func_80100A24();
    (*(void (**)(s32))0x80010290)(0);
    (*(void (**)(s32))0x800102A0)(0);
    slot_0B3();
    (*(void (**)(s32))0x800102A8)(1);
    (*(void (**)(s32))0x800102A8)(1);
    (*(void (**)(s32))0x80010290)(0x3FFF);
    (*(void (**)(s32))0x800102A0)(0x3900);
    while (slot_0A5() != 0) {
    }
    while (slot_0A9() != 0) {
    }
    i = 0;
    disp_setup_960x480();
    disp_env_set_default(&disp, 0, 0, 0x3C0, 0x1E0);
    disp.isinter = 1;
    disp.isrgb24 = 1;
    rect_set_fraction((CompleteRect *)&disp, 0x1000);
    disp_pal_adjust_y(&disp);
    disp_put_env(&disp);
    sound_play_request(0x886);
    for (j = 1; i < 0x3D; i++, j += 2) {
        screen_wipe_open_step(i * 2);
        screen_wipe_open_step(j);
        wipe_frame_wait(0);
    }
    i = 0;
    while (1) {
        if (pad_read() & 0x800) {
            sound_play_request(0x841);
            i = 0;
            break;
        }
        wipe_frame_wait(0);
        i++;
        if (i >= 0x1C20) {
            i = 0;
            break;
        }
    }
    j = 1;
    do {
        screen_wipe_close_step(i * 2);
        screen_wipe_close_step(j);
        wipe_frame_wait(0);
        i++;
        j += 2;
    } while (i < 0x3C);
    disp_setup_320x240();
    screen_blank();
}

extern s32 screen_wipe_row_table[272];
s32 screen_wipe_row_order(s32 lo, s32 hi, s32 count);
s32 screen_wipe_row_order(s32 lo, s32 hi, s32 count) {
    s32 mid;
    s32 next;

    if (lo < hi) {
        mid = (lo + hi) / 2;
        if (mid < hi && lo < mid) {
            screen_wipe_row_table[count] = mid;
            count++;
            next = screen_wipe_row_order(mid, hi, count);
            if (count == next) {
                return count;
            }
            next = screen_wipe_row_order(lo, mid, next);
            return next;
        }
    }
    return count;
}

extern s32 screen_wipe_row_table[272];
s32 screen_wipe_row_order(s32 lo, s32 hi, s32 count);
void screen_wipe_setup(void) {
    screen_wipe_row_table[0] = 0;
    screen_wipe_row_table[1] = 0x30;
    screen_wipe_row_order(0, 0x30, 2);
}

s32 disp_load_image(RECT *rect, s32 data);
void screen_copy_row(s32 buf, s32 y) {
    RECT rect;

    if (y < 0x1E0) {
        rect.x = 0;
        rect.y = y;
        rect.w = 0x3C0;
        rect.h = 1;
        disp_load_image(&rect, buf + y * 0x780);
    }
}

extern s32 screen_buf_ptr;

void screen_restore_row(s32 arg0) {
    screen_copy_row(screen_buf_ptr, arg0);
}

s32 disp_clear_image(RECT *rect, s32 r, s32 g, s32 b);
void disp_fill_black_rows(s32 y) {
    RECT rect;

    if (y < 0x1E0) {
        rect.w = 0x3C0;
        rect.y = y;
        rect.x = 0;
        rect.h = 2;
        disp_clear_image(&rect, 0, 0, 0);
    }
}

/* Upload the 48x32 tile at (x / 2, y) of the saved screen buffer to VRAM. */
static inline void screen_load_tile(s32 x, s32 y) {
    RECT rect;
    RECT unused;
    register s32 base asm("$6");

    rect.x = x >> 1;
    rect.y = y;
    rect.w = 0x30;
    rect.h = 0x20;
    base = screen_buf_ptr;
    disp_load_image(&rect, base + (x + y * 0x780));
}

void screen_load_tile_cell(s32 tx, s32 ty) {
    tx <<= 5;
    ty <<= 5;
    screen_load_tile(tx * 3, ty);
}

void screen_wipe_copy_row_pair(s32 index) {
    s32 row;
    s32 col;
    s32 y;

    row = index / 48;
    col = index % 48;
    __asm__("" : "=r"(row) : "0"(row));
    index = screen_wipe_row_table[col];
    y = (row * 48 + index) * 2;
    screen_copy_row(screen_buf_ptr, y);
    screen_copy_row(screen_buf_ptr, y | 1);
}

void disp_set_mask(s32 mask);
void rect_set_fraction(CompleteRect *rect, s32 amount) {
    s32 w;
    s32 h;

    if (amount == 0) {
        disp_set_mask(0);
        return;
    }
    disp_set_mask(1);
    w = amount / 16;
    h = amount * 240 / 4096;
    rect->x = 0;
    rect->y = 0;
    rect->w = w;
    rect->h = h;
}

extern s32 complete_image_block;

void func_801008C4(s32 unused);
s32 wipe_frame_wait(s32 handle);
void disp_env_set_default(void *buf, s32 x, s32 y, s32 w, s32 h);
void draw_env_set_default(void *buf, s32 x, s32 y, s32 w, s32 h);
void disp_put_env(void *draw_env);
void *draw_put_env(void *env);
/* Sets up the display and draw environments (960x480 area), then clears the
   framebuffer with three rect fills and points screen_buf_ptr at complete_image_block. */
void disp_setup_960x480(void) {
    RECT rect;
    CompleteDrawEnv draw;
    CompleteDispEnv disp;

    rect.w = 0x3FF;
    rect.x = 0;
    rect.y = 0;
    rect.h = 0x1FF;
    func_801008C4(0);
    wipe_frame_wait(0);
    disp_set_mask(0);
    disp_env_set_default(&disp, 0, 0, 0x3C0, 0x1E0);
    draw_env_set_default(&draw, 0, 0, 0x3C0, 0x1E0);
    disp.isinter = 1;
    disp.isrgb24 = 1;
    draw.isbg = 0;
    draw.dtd = 0;
    draw.dfe = 1;
    disp_put_env(&disp);
    draw_put_env(&draw);
    disp_clear_image(&rect, 0, 0, 0);
    disp_draw_sync(0);
    wipe_frame_wait(0);
    disp_clear_image(&rect, 0, 0, 0);
    disp_draw_sync(0);
    wipe_frame_wait(0);
    disp_clear_image(&rect, 0, 0, 0);
    disp_draw_sync(0);
    wipe_frame_wait(0);
    rect.w = 0x3C0;
    rect.h = 0x1E0;
    rect.x = 0;
    rect.y = 0;
    screen_buf_ptr = (s32)&complete_image_block;
    disp_draw_sync(0);
    wipe_frame_wait(0);
}

s32 wipe_frame_wait(s32 handle);
void disp_env_set_default(void *buf, s32 x, s32 y, s32 w, s32 h);
void draw_env_set_default(void *buf, s32 x, s32 y, s32 w, s32 h);
void disp_put_env(void *draw_env);
void *draw_put_env(void *env);
void disp_setup_320x240(void) {
    RECT rect;
    CompleteDrawEnv draw;
    CompleteDispEnv disp;

    rect.w = 0x3FF;
    rect.x = 0;
    rect.y = 0;
    rect.h = 0x1FF;
    wipe_frame_wait(0);
    disp_set_mask(0);
    disp_env_set_default(&disp, 0, 0, 0x140, 0xF0);
    draw_env_set_default(&draw, 0, 0, 0x140, 0xF0);
    disp.isinter = 0;
    disp.isrgb24 = 0;
    draw.isbg = 0;
    draw.dtd = 0;
    draw.dfe = 1;
    disp_put_env(&disp);
    draw_put_env(&draw);
    disp_clear_image(&rect, 0, 0, 0);
    wipe_frame_wait(0);
    disp_clear_image(&rect, 0, 0, 0);
    wipe_frame_wait(0);
    disp_clear_image(&rect, 0, 0, 0);
    wipe_frame_wait(0);
}

extern void (*slot_set_disp_mask)(s32 mask);
/* Same code as loader_wait_frames (loader). */
void disp_set_mask(s32 mask) {
    slot_set_disp_mask(mask);
}

void func_801008C4(s32 unused) {
}

extern s32 (*slot_1C3)(s32 handle);
/* Same code as svc_remove_frame_task (s01). */
s32 wipe_frame_wait(s32 handle) {
    return slot_1C3(handle);
}

extern s32 (*slot_draw_sync)(s32 mode);
/* Same code as title_draw_sync (title). */
s32 disp_draw_sync(s32 mode) {
    return slot_draw_sync(mode);
}

extern void (*slot_1DA)(MovieDispEnv *, s32, s32, s32, s32);
/* Same code as func_800E1404 (loader). */
void disp_env_set_default(void *buf, s32 x, s32 y, s32 w, s32 h) {
    slot_1DA(buf, x, y, w, h);
}

extern void (*slot_1D9)(MovieDispEnv *, s32, s32, s32, s32);
/* Same code as func_800E1404 (loader). */
void draw_env_set_default(void *buf, s32 x, s32 y, s32 w, s32 h) {
    slot_1D9(buf, x, y, w, h);
}

extern void (*slot_put_disp_env)(void *draw_env);
/* Same code as func_800A1A10 (title). */
void disp_put_env(void *draw_env) {
    slot_put_disp_env(draw_env);
}

extern void *(*slot_1C2)(void *env);
/* Forwards its draw env (the title draw context's draw_env) to slot 0x1C2 unchanged. */
void *draw_put_env(void *env) {
    return slot_1C2(env);
}

extern s32 (*slot_LoadImage)(RECT *rect, s32 data);
/* Same code as func_800A1A38 (title). */
s32 disp_load_image(RECT *rect, s32 data) {
    return slot_LoadImage(rect, data);
}

extern s32 (*slot_clear_image)(RECT *rect, s32 r, s32 g, s32 b);
/* Same code as title_set_disp_mask (title). */
s32 disp_clear_image(RECT *rect, s32 r, s32 g, s32 b) {
    return slot_clear_image(rect, r, g, b);
}

void func_80100A24(void) {
}

extern s32 (*slot_read_pad)(s32 mode);
s32 pad_read(void) {
    return slot_read_pad(0);
}

extern s32 (*slot_tone_volume)(s32);
extern s32 (*slot_snd_alloc_channel)(SndAllocBlock *block);
extern SndAllocBlock sound_request;
/* arg0 packs a sound request: bit 12 -> bit 24, bits 8-14 -> bits 8-14, low nibble kept. */
void sound_play_request(u32 arg0) {
    s32 *volume = &sound_request.volume;

    *volume = slot_tone_volume(((((arg0 >> 12) & 1) << 24) + ((arg0 << 4) & 0x7F00)) | (arg0 & 0xF));
    sound_request.tone = arg0;
    slot_snd_alloc_channel(&sound_request);
}

extern void (*slot_006)(s32 arg);
extern void (*slot_set_disp_mask)(s32 mask);
/* Calls the two hook pointers, each with argument 0. */
void screen_blank(void) {
    slot_006(0);
    slot_set_disp_mask(0);
}

extern s32 (*slot_GetVideoMode)(void);
void disp_pal_adjust_y(void *obj) {
    if (slot_GetVideoMode() != 0) {
        ((u16 *) obj)[5] += 0x18;
    }
}
