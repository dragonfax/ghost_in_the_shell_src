/* stage_round: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Draws a flat line (code 0x52) from (x, y) scaled into view `view`, width w, clipped to the view, then a
 * draw-mode primitive after it. */
void draw_view_hline(s32 x, s32 y, s32 w, s32 colour0, s32 colour1, s32 view) {
    ViewDrawFields *v = (ViewDrawFields *)&views[view];
    s32 x0, y0, x1;
    s32 sx, sy, ox, oy, clip_w, clip_h;
    u8 *line;
    u8 *mode;
    u32 *ot;
    WorkArea *work;

    sx = v->scale_x;
    sy = v->scale_y;
    ox = v->origin_x;
    oy = v->origin_y;
    x0 = x * sx / 0x1000 + ox;
    y0 = y * sy / 0x1000 + oy;
    x1 = (x + w) * sx / 0x1000 + ox;
    clip_w = v->clip_w;
    clip_h = v->clip_h;
    if (y0 < 0 || y0 > clip_h) {
        return;
    }
    x0 = MAX(MIN(x0, clip_w), 0);
    x1 = MAX(MIN(x1, clip_w), 0);

    work = work_area_ptr;
    line = work->packet;
    work->packet = line + 0x14;
    line[3] = 4;
    *(s16 *)(line + 8) = x0;
    *(s16 *)(line + 0xA) = y0;
    *(s16 *)(line + 0x10) = x1;
    *(s16 *)(line + 0x12) = y0;
    *(s32 *)(line + 4) = colour0;
    *(s32 *)(line + 0xC) = colour1;
    line[7] = 0x52;
    ot = v->ot;
    addPrim(ot, line);
    mode = work->packet;
    work->packet = mode + 0xC;
    fn_800B6DB4(mode, 0, 1, 0x20, 0);
    addPrim(ot, mode);
}

void spark_model_base_set(s32 value) {
    spark_model_base = value;
}

void track_base_set(s32 value) {
    track_base = value;
}

void stage_image_load(void) {
    s16 rect[4];
    s16 *rect_ptr;
    s32 width;
    s32 height;
    s32 rounded_width;
    u8 *buf;

    buf = arena_top();
    rect_ptr = rect;
    width = swap16(stage_image_width);
    height = swap16(stage_image_height);
    pack_4bpp(width, 0x20, 0x20, 0, stage_image_pixels, buf);
    rounded_width = width;
    if (rounded_width < 0) {
        rounded_width += 3;
    }
    rect_ptr[0] = 0x30;
    rect_ptr[1] = 0x120;
    rect_ptr[2] = rounded_width >> 2;
    rect_ptr[3] = height;
    svc_load_image(rect_ptr, buf);
    svc_draw_sync(0);
    rect_ptr[0] = 0x70;
    rect_ptr[1] = 0x120;
    rect_ptr[2] = 0x10;
    rect_ptr[3] = 1;
    svc_load_image(rect_ptr, stage_clut);
    svc_draw_sync(0);
}

/* Splits each of the 32 colours in d_8011E0F4 into shifted 5-bit fields. */
void palette_expand(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        u16 color = palette_colours[i];

        palette_expanded[i].r = (color & 0x1F) << 7;
        palette_expanded[i].g = (color << 2) & 0xF80;
        palette_expanded[i].b = (color >> 3) & 0xF80;
    }
}

void engine_palette_setup(void) {
    palette_expand();
    spark_model_base = 0;
    track_base = 0;
    hud_gfx_base = *(s32 *)(get_ptr_entry_word2(4) + 8);
    fn_8010016C();
    fn_800FE278();
}

/* Sets up the render state of view `view` (its camera `cam`) for record `rec`. */
void view_setup(s32 view, s32 cam, s32 rec) {
    rec_set_colour(rec, 0, 0, 0, 0);
    rec_set_colour(rec, 1, 0, 0, 0);
    rec_set_colour(rec, 2, 0, 0, 0);
    rec_set_point(rec, 0, 0, 0);
    rec_set_vec(rec, 0x1000, 0x1000, 0x1000);
    rec_set_tex_flag(rec, 0);
    rec_set_on(rec, 0);
    rec_set_flag(rec, 0);
    light_set_dir_from_angles(rec, 0, -0x200, -0x222);
    light_set_dir_from_angles(rec, 1, 0x200, 0x1C7);
    light_set_dir_from_angles(rec, 2, 0x200, 0);
    rec_set_part(rec, 0, 0xA00, 0xA00, 0xA00);
    rec_set_part(rec, 1, 0x600, 0x600, 0x600);
    rec_set_part(rec, 2, 0, 0, 0);
    rec_set_part(rec, 3, 0x600, 0x600, 0x600);
    rec_set_part(rec, 4, 0x1000, 0x1000, 0x1000);
    rec_set_part(rec, 5, 0x1000, 0x1000, 0x1000);
    rec_set_part(rec, 6, 0x1000, 0x1000, 0x1000);
    view_set_on(view, 0);
    view_set_parent(view, 0);
    view_set_depth(view, 0);
    view_set_camera(view, cam);
    view_set_colour(view, 0, 0, 0, 0);
    view_set_colour_b(view, 0, 0, 0, 0);
    view_set_colour_c(view, 0, 0, 0, 0);
    cam_set_rec(cam, rec);
    cam_set_rot(cam, 0, 0, 0);
    cam_set_scale(cam, 0x01000000 / video_scale(), 0x1000);
}

void round_reset(void) {
    message_shown_flag = 0;
    stage_round_state = 0;
    d_8012D3F8 = 0;
    stage_end_state = 0;
    meter_b_rate = 0;
    meter_a_rate = 0;
    meter_b_level = 0;
    meter_a_level = 0;
    meter_run_flag = 1;
    shield_gauge = 0;
    shield_prev = get_shield();
    alert_level = 0;
    alert_count = 0;
    pulse_phase = 0;
    shade_angle = 0;
    if (untimed_part()) {
        view_setup(1, 1, 1);
        cam_set_pos(1, 0, 0, -0x1CC);
    }
    area_setup();
    cam_init();
    pause_menu_setup();
    view_reset();
    req_state_reset();
    meter_reset();
    rec_table_reset();
}

s32 area_part_available(void) {
    s32 area;
    s32 part;
    void *p;

    area = get_area();
    part = area % 3;
    if (part == 0) {
        return 1;
    }
    if (part == 2) {
        return 0;
    }
    set_area((area / 3) * 3 + ((part + 1) % 3));
    p = get_area_entry();
    set_area(area);
    return p != NULL;
}

char str_tst_spr_so3[12] RODATA = "tst_spr.so3";

char str_tst_spr_grc[12] RODATA = "tst_spr.grc";

char str_tst_spr_clt[12] RODATA = "tst_spr.clt";

char str_msgspr_so3[12] RODATA = "msgspr.so3";

char str_msgspr_grc[12] RODATA = "msgspr.grc";

char str_msgspr_clt[12] RODATA = "msgspr.clt";

char str_tg_disp_so3[12] RODATA = "tg_disp.so3";

char str_tg_disp_grc[12] RODATA = "tg_disp.grc";

char str_tg_disp_clt[12] RODATA = "tg_disp.clt";

char str_fc_tp0_clt[12] RODATA = "fc_tp0.clt";

char str_fc_obj_vx1[12] RODATA = "fc_obj.vx1";

char str_fc_tp0_xs3[12] RODATA = "fc_tp0.xs3";

char str_fc_objcb4[12] RODATA = "fc_obj.cb4";

char str_sdw_tp0_clt[12] RODATA = "sdw_tp0.clt";

char str_sdw_obj_vx1[12] RODATA = "sdw_obj.vx1";

char str_sdw_tp0_xs3[12] RODATA = "sdw_tp0.xs3";

char str_tst_tp1_clt[12] RODATA = "tst_tp1.clt";

char str_tst_tp0_clt[12] RODATA = "tst_tp0.clt";

char str_tst_tp2_xs3[12] RODATA = "tst_tp2.xs3";

char str_tst_tp1_xs3[12] RODATA = "tst_tp1.xs3";

char str_tst_tp0_xs3[12] RODATA = "tst_tp0.xs3";

char str_tst_obj2_vx1[16] RODATA = "tst_obj2.vx1";

char str_tst_obj_vx1[12] RODATA = "tst_obj.vx1";

char str_main_data[16] RODATA = "..\\main\\data\\";

char str_com_dat_fac[12] RODATA = "com_dat.fac";

void stage_round_run(void) {
    /* state[0] is the current slot, state[1..8] the resume labels, state[9..16] the frame counters */
    s32 *state = &stage_round_state;
    s32 unused[2];

    if (state[1 + state[0]] != 0) {
        goto *(void *)state[1 + state[0]];
    }
    set_stage_flags(get_stage_flags() | 0x10);
    cam_fade_amount = 0;
    view_split_amount = 0;
    meter_b_level = 0;
    meter_a_level = 0;
    meter_b_rate = 0;
    meter_a_rate = 0;
    state[1 + state[0]] = (s32)&&grow;
    return;
grow:
    cam_fade_amount += 0xAA;
    if (cam_fade_amount >= 0x1000) {
        cam_fade_amount = 0x1000;
    }
    cam_offset_set(0, 0, 0);
    cam_fade_set(cam_fade_amount);
    view_split_amount += 0x2A;
    if (view_split_amount < 0x400) {
        return;
    }
    view_split_amount = 0x400;
    state[1 + state[0]] = (s32)&&wait1;
    return;
wait1:
    state[0] = (state[0] + 1) & 7;
    state[1 + state[0]] = (s32)&&wait1b;
    meter_a_rate = 0x40;
    state[9 + state[0]] = 0xF;
wait1b:
    if (--state[9 + state[0]] >= 0) {
        return;
    }
    *(volatile s32 *)state = (state[0] - 1) & 7;
    state[0] = (state[0] + 1) & 7;
    state[1 + state[0]] = (s32)&&wait2;
    meter_b_rate = 0x40;
    state[9 + state[0]] = 0xF;
wait2:
    if (--state[9 + state[0]] >= 0) {
        return;
    }
    state[0] = (((state[0] - 1) & 7) + 1) & 7;
    state[1 + state[0]] = (s32)&&wait3;
    state[9 + state[0]] = 7;
wait3:
    if (--state[9 + state[0]] >= 0) {
        return;
    }
    state[0] = (state[0] - 1) & 7;
    if (message_shown_flag == 0) {
        static const char mission_msg[] = "Pursue your mission";
        show_line((s32)mission_msg);
    }
    set_stage_flags(get_stage_flags() & ~0x10);
    state[1 + state[0]] = (s32)&&check;
    return;
check:
    stage_end_state = get_stage_end();
    switch (stage_end_state) {
    case 2:
        if (!player_controls_enabled()) {
            return;
        }
        set_stage_flags(get_stage_flags() | 0x10);
        if (area_part_available()) {
            set_mission_active(0);
            set_d_801202C8(0);
            set_stage_flags(get_stage_flags() | 0x12);
            state[1 + state[0]] = (s32)&&idle;
idle:
            return;
        }
        /* fall through */
    case 3:
        break;
    default:
        return;
    }
    set_mission_active(0);
    set_stage_flags(get_stage_flags() | 8);
    cam_offset_set(0, 0, 0);
    cam_fade_set(0x1000);
    state[1 + state[0]] = (s32)&&done;
done:
    stage_frame_update();
}

extern const s32 sincos_table_ro[] __asm__("rcossin_tbl");
void stage_view_split_setup(void) {
    s32 sine;
    s32 screen_w;
    s32 screen_h;
    s32 height;
    s32 width;
    s32 y;

    sine = *(const s16 *)&sincos_table_ro[view_split_amount & 0xFFF];
    screen_h = stage_screen_h;
    screen_w = stage_screen_w;
    height = (screen_h * sine) >> 12;
    width = (screen_w * sine) >> 12;
    if (stage_end_state == 0) {
        set_view_offset(0, (screen_w - width) / 2, (screen_h - height) / 2);
        view_set_clip_size(0, width, height);
    }
    view_set_on(1, 1);
    view_set_size(1, screen_w, 0x49);
    view_set_pivot(1, 0xD1, 0x26);
    fn_800C94D8(1, 0, 0);
    height = *(s16 *)&rcossin_tbl[meter_a_level & 0xFFF] * 0x49;
    y = (0x16D000 - height) / 0x2000;
    if (meter_a_level == 0x400) {
        y -= 2;
    }
    set_view_offset(1, 0, y);
    y = height / 0x1000;
    view_set_clip_size(1, screen_w, y);
}

/* Raises two levels at their rates while on (b also needs msg_scroll_started), else lowers them by 0x80.
 * Plays sound 0x850 when b fills up and calls gauge_reset when it runs out. */
void meters_update(void) {
    s32 prev;

    meter_a_level = meter_run_flag != 0 ? meter_a_level + meter_a_rate : meter_a_level - 0x80;
    meter_a_level = MAX(MIN(meter_a_level, 0x400), 0);

    prev = meter_b_level;
    if (meter_run_flag != 0 && msg_scroll_started() != 0) {
        meter_b_level += meter_b_rate;
        if (prev < 0x400 && meter_b_level >= 0x400) {
            sound_start(SND_BEEP | SND_VOICE_FLAG, 0x40, 0, 0);
        }
    } else {
        meter_b_level -= 0x80;
    }
    meter_b_level = MAX(MIN(meter_b_level, 0x400), 0);
    if (prev > 0 && meter_b_level == 0) {
        gauge_reset();
    }
}

void set_d_801202C8(s32 value) {
    meter_run_flag = value;
}

s32 get_meter_run_flag(void) {
    return meter_run_flag;
}

void alert_add(s32 amount) {
    alert_count += amount;
}

s32 alert_level_get(void) {
    return alert_level;
}
