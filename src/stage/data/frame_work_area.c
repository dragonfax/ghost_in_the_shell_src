/* Data shared by s01, s03, s04, s05, s06, s07, s08, s09, s10, s11, s12, s13 (29 objects): scripts/stage_data.py. */

s32 frame_work_area = 0;

s16 tile_pos_count = 0;

s16 first_frame_flag = 0;

s16 frame_rec_index = 0;

s16 frame_buf_parity = 0;

s16 screen_rect_x = 0;

s16 screen_rect_y = 0;

s16 frame_ot_depth = 0;

u8 *arena_base = NULL;

s32 arena_size = 0;

s16 debug_cam_flag = 0;

s16 debug_cam_pan_x = 0;

s16 debug_cam_pan_y = 0;

s16 debug_cam_speed_index = 0;

s32 cam_pair_count = 0;

u8 *arena_top_ptr = NULL;

s16 cam_fade_level = 0;

s16 cam_fade_r = 0;

s16 cam_fade_g = 0;

s16 cam_fade_b = 0;

s32 pause_state = 0;

u16 anim_clock = 0;

u16 anim_clock_rate[2] = {
    0x0000, 0x0000,
};

u8 tex_tint_rgb = 0x00;

u8 tex_pal0_g = 0x00;

u16 tex_pal0_b = 0x0000;

s32 tex_has_transparent = 0;

s32 light_env_tex_flag = 0;

s32 tex_loaded_flag = 0;
