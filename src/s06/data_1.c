/* s06 data 0x8011EC34-0x80127800: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s06_types.h"
#include "script.h"
#include "scripts.h"
#include "sounds.h"

extern void cam_track_b_setup();
extern void cam_track_get();
extern void cam_track_init();
extern void cam_track_set_active();
extern void cam_track_set_on();
extern void cam_track_setup();
extern void cam_track_slot_get();
extern u8 d_8012D3AC[];
extern u8 d_8012D3B8[];
extern u8 d_8012D3C4[];
extern u8 d_8012D3D0[];
extern u8 d_8012D3DC[];
extern u8 d_80132FFC[];
extern u8 d_8013303C[];
extern u8 d_801330BC[];
extern u8 d_801331BC[];
extern u8 d_801333BC[];
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern u8 model_base_slot[];
extern void obj_area_update();
extern void obj_attach_default();
extern void obj_call_hook();
extern void obj_fire_both_sides();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_release_check();
extern void obj_script_jump_if_far();
extern void obj_sound_loop_start();
extern void obj_sound_loop_stop();
extern void obj_trail_emit();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void ramp_start_script();
extern void script_case_match();
extern void script_cursor_advance();
extern void script_cursor_advance_alt();
extern void script_jump_if_far();
extern void script_jump_if_near();
extern void script_jump_if_near_alt();
extern void script_jump_if_op_eq();
extern void script_jump_indexed();
extern void script_load_table_entry();
extern void script_op_jump();
extern void script_read_u16();
extern void script_turn_to_player();
extern void script_turn_to_player_jump();
extern void sound_start_held();
extern void sound_stop_held();
extern u8 str_com_dat_fac[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_main_data[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_sdw_obj_vx1[];
extern u8 str_sdw_tp0_clt[];
extern u8 str_sdw_tp0_xs3[];
extern u8 str_tg_disp_clt[];
extern u8 str_tg_disp_grc[];
extern u8 str_tg_disp_so3[];
extern u8 str_tst_obj2_vx1[];
extern u8 str_tst_obj_vx1[];
extern u8 str_tst_spr_clt[];
extern u8 str_tst_spr_grc[];
extern u8 str_tst_spr_so3[];
extern u8 str_tst_tp0_clt[];
extern u8 str_tst_tp0_xs3[];
extern u8 str_tst_tp1_clt[];
extern u8 str_tst_tp1_xs3[];
extern u8 str_tst_tp2_xs3[];
extern void stream_read_halfword();
extern u8 text_packets[];
extern void text_slot_setup();
extern void track_set_enabled();
extern void track_setup();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_80125F32[];
extern u8 D_80127626[];
extern u8 cos_table[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 d_801201AE[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 flow_angle[];
extern u8 gun_hit_effect_table[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 view_sincos[];
extern s16 enemy_child_hit_factors[];
extern SoundVolume enemy_part_sound_entry[];
extern Keyframe obj_trail_keys[8];
extern ScriptCallEntry enemy_part_call_table[10];
extern s16 semi_truck_mech_m6_boss_idle[];
extern s16 semi_truck_mech_m6_boss_ready[];
extern s16 semi_truck_mech_m6_boss_wait_go[];
extern s16 semi_truck_mech_m6_boss_walk_start[];
extern s16 semi_truck_mech_m6_boss_walk_branch[];
extern s16 semi_truck_mech_m6_boss_walk_left_wait[];
extern s16 semi_truck_mech_m6_boss_walk_left_trail[];
extern s16 semi_truck_mech_m6_boss_walk_left_settle[];
extern s16 semi_truck_mech_m6_boss_walk_left_exit[];
extern s16 semi_truck_mech_m6_boss_walk_right_begin[];
extern s16 semi_truck_mech_m6_boss_walk_right_wait[];
extern s16 semi_truck_mech_m6_boss_walk_right_trail[];
extern s16 semi_truck_mech_m6_boss_walk_right_settle[];
extern s16 semi_truck_mech_m6_boss_walk_right_exit[];
extern s16 semi_truck_mech_m6_boss_walk_loop[];
extern s16 semi_truck_mech_m6_boss_walk_to_right[];
extern s16 *enemy_child_part_jump_table[16];
extern s16 semi_truck_mech_m6_boss_anim_idle[];
extern s16 semi_truck_mech_m6_boss_anim_wake[];
extern s16 semi_truck_mech_m6_boss_anim_ready_hold[];
extern s16 semi_truck_mech_m6_boss_anim_walk_a[];
extern s16 semi_truck_mech_m6_boss_anim_walk_a_end[];
extern s16 semi_truck_mech_m6_boss_anim_walk_b[];
extern s16 semi_truck_mech_m6_boss_anim_walk_b_end[];
extern s16 semi_truck_mech_m6_boss_anim_walk_a_fast[];
extern s16 semi_truck_mech_m6_boss_anim_walk_a_fast_end[];
extern s16 semi_truck_mech_m6_boss_anim_walk_b_fast[];
extern s16 semi_truck_mech_m6_boss_anim_walk_b_fast_end[];
extern s16 *enemy_child_part_script_table[];
extern s16 *D_8011F0D8[];
extern StateEntry enemy_part_states[7];
extern s16 part_hit_factors[];
extern SoundVolume D_8011F124[];
extern Keyframe side_shot_keyframes[13];
extern ScriptCallEntry D_8011F160[14];
extern s16 enemy_part_child_deploy[];
extern s16 enemy_part_child_await_trigger[];
extern s16 enemy_part_child_attach[];
extern s16 enemy_part_child_fire_start[];
extern s16 enemy_part_child_fire_loop[];
extern s16 enemy_part_child_fire_burst[];
extern s16 enemy_part_child_fire_end[];
extern s16 enemy_part_child_fire_restart[];
extern s16 enemy_part_child_cooldown[];
extern s16 *enemy_part_child_jump_table[9];
extern s16 enemy_part_child_anim_hold[];
extern s16 enemy_part_child_anim_deploy[];
extern s16 enemy_part_child_anim_idle[];
extern s16 enemy_part_child_anim_fire[];
extern s16 *enemy_part_child_script_table[];
extern s16 *D_8011F2E0[];
extern StateEntry D_8011F2E4[5];
extern s16 obj_hit_mask_weights[];
extern s32 span_table_base[17];
extern s32 span_source_table[41];
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern u16 ratan_tbl[];
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_80124788[];
extern u16 inv_sqrt_table[];
extern s32 vblank_task_handle;
extern s16 video_mode_id;
extern s16 debug_cam_speed_table[][2];
extern s32 pause_prev_work_area;
extern s16 tint_scale_r;
extern s16 tint_scale_g;
extern s16 tint_scale_b;
extern s16 tint_add_r;
extern s16 tint_add_g;
extern s16 tint_add_b;
extern LensFlare lens_flare_table[];
extern s32 colour_table_default[];
extern s32 clamp_table_default[];
extern s32 slope_table_default[];
extern s16 clip_index_stream[];
extern s32 d_8011D744[];
extern s32 d_8011D768[];
extern s32 d_8011D778[];
extern s32 sound_initialized;
extern s32 engine_initialized;
extern s32 stage_saved_flag;
extern u8 debug_menu_text_rows[];
extern u8 font_bitmap[];
extern s16 font_clut[4];
extern s32 text_origin_x;
extern s32 text_origin_y;
extern s32 text_cursor_x;
extern s32 text_cursor_y;
extern void *text_packet_cur;
extern s16 text_packet_index;
extern s32 font_page_x;
extern s32 font_page_y;
extern s32 font_y_offset;
extern s32 font_semi_trans_flag;
extern s32 texpage_current;
extern u32 d_8011DCD4[];
extern RECT font_tex_window;
extern void (*handler_fn_table[])(s32, s32);
extern void (*clear_handler_table[])(s32, s32);
extern void *(*part_record_resolve_table[])(u32);
extern void (*part_cmd_table[])(PartSlot *, s32 *, s32);
extern s32 name_table_base;
extern s32 pause_blocked_flag;
extern u32 screenshot_name_ptr;
extern char digits4_out_ptr[];
extern s32 screenshot_counter;
extern ScreenSize stage_screen_default;
extern s32 d_8011DD70;
extern s16 spark_red_table[];
extern s16 spark_green_table[];
extern s16 shake_table[];
extern s32 pose_joint_indices[2][5];
extern u32 d_8011DDE8[];
extern VECTOR spark_point_table[5];
extern s32 ptr_table_len;
extern s32 ptr_table_mark;
extern s32 solid_slot_next;
extern s32 solid_grid_parity;
extern s16 solid_count;
extern s16 collide_mode;
extern s32 grid_origin_x;
extern s32 grid_origin_y;
extern s32 grid_origin_z;
extern s32 solid_active_count;
extern u32 solid_masks[];
extern Node *obj_list_cursor;
extern void (*actor_hook)();
extern ObjHandlerFn obj_state_handlers[];
extern ObjHandlerFn obj_state_steps[];
extern ObjHandlerFn obj_state_steps_b[];
extern s16 obj_free_count;
extern u16 obj_serial;
extern s16 obj_pending_count;
extern Object *obj_pending;
extern u8 *test_sprite_names[];
extern ScanEntry d_8011DF24;
extern u8 *message_sprite_names[];
extern ScanEntry d_8011DF48;
extern u8 *target_display_names[];
extern ScanEntry d_8011DF6C;
extern ModelBlockRef d_8011DF84[];
extern ModelBlockRef d_8011DF94[];
extern ModelBlockRef d_8011DFA4[];
extern ModelBlockRange d_8011DFB4;
extern ModelBlockRange d_8011DFBC[];
extern ModelBlock fuchikoma_model_block;
extern u8 *d_8011DFF0[];
extern ScanEntry d_8011DFF8;
extern ModelBlockRef d_8011E010[];
extern ModelBlockRef d_8011E020[];
extern ModelBlockRef d_8011E030[];
extern ModelBlockRange d_8011E040;
extern ModelBlockRange d_8011E048;
extern ModelBlockRange d_8011E050[];
extern s16 d_8011E060[];
extern ModelBlock shadow_model_block;
extern ScanEntry d_8011E08C;
extern ModelBlockRef d_8011E0A4[];
extern ModelBlockRef d_8011E0BC[];
extern ModelBlockRef d_8011E0DC[];
extern ModelBlockRange d_8011E0F4[];
extern ModelBlockRange d_8011E174[];
extern ModelBlockRange d_8011E194[];
extern s16 d_8011E1B4[];
extern ModelBlock d_8011E1C8;
extern ScanEntry d_8011E1EC;
extern ScanItem ptr_entry_table[];
extern ResourceRoot rec_root;
extern KeyConfig key_configs[5];
extern u16 palette_colours[32];
extern u16 stage_clut[16];
extern LampColour lamp_table[];
extern s16 d_8011E3C0[];
extern s32 number_divisors[7];
extern RecTemplate grenade_burst_templates[];
extern u32 d_8011E454[];
extern s32 d_8011E460;
extern s32 d_8011E464;
extern u32 d_8011E468;
extern s32 *player_model_id_ptr;
extern u32 D_8012590C[];
extern TrailOffset trail_offsets[];
extern u32 fx_style_table[24];
extern s16 d_8011E510[];
extern s16 *fx_glow_tables[];
extern s32 fx_depth_thresholds[];
extern s32 alloc_owner;
extern s32 sound_release_caller;
extern s32 sound_release_reason;
extern u16 vram_image_b[];
extern u16 vram_image_a[128];
extern u16 clut_image[256];
extern u32 D_80125F2C;
extern u16 texture_image[];
extern u16 stage_image_width;
extern u16 stage_image_height;
extern u32 stage_image_pixels[];
extern s32 heap_top;
extern s32 heap2_top;
extern s32 model_pchr_saved;
extern s32 cam_rec_request;
extern s32 cam_fade_dir;
extern s32 cam_fade_ramp;
extern s32 loop_sound_handle;
extern s32 cam_bounce_offset;
extern s32 last_flow_state;
extern s32 loop_sound_saved_mode;
extern s32 grid_flagged_count;
extern s32 alert_flag;
extern s32 turn_flag;
extern s32 orbit_flag;
extern s32 mission_enemies_left;
extern s32 cam_timer;
extern u32 mission_state;
extern u32 eng_mode;
extern s32 msg_text_id;
extern s32 cam_side_blend;
extern s32 cam_ramp_b;
extern s32 msg_fade;
extern s32 cam_spin_step;
extern s32 cam_angle_acc;
extern s16 msg_pos_x;
extern s16 msg_pos_y;
extern s32 d_8011FEE4;
extern s32 timer_warn_shown;
extern s32 part_loop_sound_handle;
extern s16 script_index[2];
extern s16 D_801273B0;
extern s32 obj_sound_loop_handle;
extern s32 sound_held_handle;
extern s32 giant_robot_systems_active;
extern s32 frame_work_area;
extern s16 tile_pos_count;
extern s16 first_frame_flag;
extern s16 frame_rec_index;
extern s16 frame_buf_parity;
extern s16 screen_rect_x;
extern s16 screen_rect_y;
extern s16 frame_ot_depth;
extern u8 *arena_base;
extern s32 arena_size;
extern s16 debug_cam_flag;
extern s16 debug_cam_pan_x;
extern s16 debug_cam_pan_y;
extern s16 debug_cam_speed_index;
extern s32 cam_pair_count;
extern u8 *arena_top_ptr;
extern s16 cam_fade_level;
extern s16 cam_fade_r;
extern s16 cam_fade_g;
extern s16 cam_fade_b;
extern s32 pause_state;
extern u16 anim_clock;
extern u16 anim_clock_rate[];
extern u8 tex_tint_rgb;
extern u8 tex_pal0_g;
extern u16 tex_pal0_b;
extern s32 tex_has_transparent;
extern s32 light_env_tex_flag;
extern s32 tex_loaded_flag;
extern s32 model_slot_count;
extern s32 model_atlas_y;
extern s32 model_atlas_x;
extern s32 clut_count;
extern s32 model_slot_width;
extern s32 model_slot_height;
extern s32 *block_map_buf;
extern s32 *texel_mask_buf;
extern u8 *clut_used_flags;
extern s32 last_env_colour_a;
extern s32 last_env_colour_b;
extern s32 last_env_colour_c;
extern s32 saved_pchr_count;
extern s32 saved_clut_count;
extern s32 saved_model_count;
extern s32 saved_atlas_y;
extern s32 saved_atlas_x;
extern s32 d_8011FFE4;
extern u32 D_80127474;
extern s32 ring32_index;
extern s32 scene_model_count;
extern s32 cyl_tex_table;
extern s32 d_8011FFF8;
extern s32 cyl_scale;
extern s16 vec3_x;
extern s16 vec3_y;
extern s16 vec3_z;
extern s16 vec3_pad;
extern s32 d_80120008;
extern s32 img_upload_active;
extern s32 light_data_base;
extern s32 interp_enabled_flag;
extern s32 interp_record_count;
extern s32 interp1c_count;
extern s32 interp2c_count;
extern s32 interp38_count;
extern s32 interp38b_count;
extern s32 scratch_saved_slot_count;
extern s32 scratch_saved_top;
extern s32 scratch_slot_count;
extern s32 rec_count;
extern s32 rec_pos_total;
extern s32 aobj_entry_count;
extern s32 max_apex_count;
extern s32 max_poly_count;
extern s32 max_unit_count;
extern s32 square_count;
extern s32 poly_count;
extern s32 stage_offset_x;
extern s32 stage_offset_y;
extern s32 colour_table_ptr;
extern s32 clamp_table_ptr;
extern s32 slope_table_ptr;
extern s32 d_8012006C;
extern s32 player_last_flags;
extern s16 player_pos_x;
extern s16 player_pos_y;
extern s16 player_pos_z;
extern s32 player_clamp_box;
extern s32 player_vertical_blocked;
extern u32 D_80127510;
extern s32 pause_flag;
extern s32 cell_cursor_step1;
extern s32 cell_cursor_step2;
extern s32 cell_cursor_step1_saved;
extern s32 cell_cursor_step2_saved;
extern s32 frames_pending;
extern s32 pal_accum;
extern s32 step_abort;
extern s32 stage_heap_mark;
extern s32 area_sound_requested;
extern s32 pause_cooldown;
extern s32 area_sound_index;
extern s32 area_load_next;
extern s32 area_load_timer;
extern s32 area_load_duration;
extern s32 area_fade_rate;
extern s32 bg_load_pending;
extern u32 bg_buffer;
extern s32 bg_load_size;
extern char *bg_load_name;
extern char *bg_load_file;
extern s32 end_ramp;
extern s32 end_ramp_rate;
extern s32 debug_menu_cursor;
extern s32 debug_menu_enabled;
extern s32 part_time;
extern s32 part_timer_on;
extern s32 part_pose_base;
extern s32 part_offset;
extern s32 part_fade_handler;
extern s32 part_slot_count;
extern s32 str_queue_count;
extern s32 stage_queue_count;
extern s32 stage_data_ptr;
extern NameEntry *name_table_root;
extern NameEntry *name_table_cwd;
extern s32 player_pose_base;
extern s32 player_coll_part;
extern s32 hit_spark_pchr;
extern s32 beam_model_base;
extern s32 player_glow_level;
extern s32 player_glow_step;
extern s32 player_death_fade;
extern s32 player_death_blend;
extern s32 player_death_spark_timer;
extern s32 player_death_frames;
extern s32 player_exit_timer;
extern s32 player_walk_phase;
extern s32 player_walk_meter;
extern s32 player_strafe_meter;
extern s32 player_air_blend;
extern s32 player_rise_phase;
extern s32 player_fall_blend;
extern s32 player_land_blend;
extern s32 player_charge_blend;
extern s32 player_charge_phase;
extern s32 beam_countdown;
extern s32 player_ground_y;
extern s32 player_charge_timer;
extern s32 target_hit_steps;
extern s32 fire_hold_steps;
extern s32 missile_delay;
extern s32 missiles_left;
extern s32 player_shake_index;
extern s32 player_fade_level;
extern s32 cooldown_18c;
extern s32 idle_steps;
extern s32 cooldown_194;
extern s16 view_nudge[2];
extern s32 cooldown_19c;
extern s32 player_held;
extern s32 player_pressed;
extern s32 player_input_skip;
extern Flow flow;
extern s32 pending_turn;
extern s32 flow_max;
extern s32 flow_ramp;
extern s32 flow_step;
extern s32 pitch_recenter;
extern s32 charge_sound_handle;
extern s32 move_sound_handle;
extern s32 charge_hum_a;
extern s32 charge_hum_b;
extern s32 player_step_phase;
extern s32 player_step_flag;
extern s32 contact_20_steps;
extern s32 jump_latch;
extern s32 player_run_timer;
extern s32 moving;
extern s32 move_speed;
extern u32 player_status;
extern s32 timer_count;
extern s32 beam_timer_next;
extern s32 timer_first;
extern s32 d_80120204;
extern s32 view_cache_flags;
extern s16 d_8012020C;
extern u16 d_8012020E;
extern u16 d_80120210;
extern s32 fade_free_count;
extern s32 grid_block;
extern s32 grid_entry_total;
extern GridEntry *grid_entries;
extern s32 hook_range_hi;
extern s32 hook_range_lo;
extern s32 grid_camera_phase;
extern s32 grid_active_flag;
extern s32 hit_ext_flag;
extern s32 effect_base;
extern u8 fades_head[];
extern u8 fades_free[];
extern s32 mission_active;
extern s32 mission_elapsed;
extern s32 mission_timer;
extern s32 mission_limit;
extern s32 player_score;
extern s32 player_shield;
extern s32 grenade_count;
extern s32 kill_count;
extern s32 mission_total;
extern s32 mission_count;
extern s32 mission_score;
extern s32 stage_end;
extern s32 stage_flags;
extern s32 stage_ready_flag;
extern s32 key_config_index;
extern s32 d_80120280;
extern s32 d_80120284;
extern s32 spark_model_base;
extern s32 track_base;
extern s32 shield_gauge;
extern s32 shield_prev;
extern s32 pulse_phase;
extern s32 alert_level;
extern s32 alert_count;
extern s32 shade_angle;
extern s32 cam_fade_amount;
extern s32 view_split_amount;
extern s32 meter_a_level;
extern s32 meter_b_level;
extern s32 hud_gfx_base;
extern s32 stage_end_state;
extern s32 meter_a_rate;
extern s32 meter_b_rate;
extern s32 meter_run_flag;
extern s32 message_shown_flag;
extern s32 req_queue_count;
extern s32 d_801202D4;
extern s32 draw_enabled;
extern s32 area_warnings_flag;
extern s32 msg_queue_length;
extern s32 msg_write_index;
extern s32 msg_read_index;
extern s32 msg_scroll_timer;
extern s32 msg_wait_timer;
extern u8 *msg_text_ptr;
extern s32 hud_on_flag;
extern s32 msg_enabled;
extern s16 hud_view_x;
extern s16 hud_view_y;
extern s16 hud_view_w;
extern s16 hud_view_h;
extern s32 pause_menu_angle;
extern s32 pause_menu_choice;
extern s32 pause_menu_cursor;
extern s32 pause_menu_cursor_prev;
extern s32 mission_result_slide_x;
extern s32 mission_result_base_y;
extern s32 mission_result_zoom;
extern s32 mission_result_zoom_slow;
extern s32 screen_fade_alpha;
extern s32 view_scale;
extern s32 dim_level_b;
extern s32 result_time_bonus;
extern s32 result_shield_bonus;
extern s32 result_grenade_bonus;
extern s32 result_total;
extern s32 result_score;
extern s32 result_hitrate;
extern s32 result_kill_count;
extern s32 result_class;
extern s32 result_rank_place;
extern s32 mission_result_exit_flag;
extern s32 stage_transition_flag;
extern s32 ui_item_free_count;
extern s32 meter_start_time;
extern s32 meter_end_time;
extern s32 gauge_max;
extern s32 gauge_value;

s16 enemy_child_hit_factors[8] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
};

SoundVolume enemy_part_sound_entry[1] = {
    {0x30A4, 0x1000},
};

Keyframe obj_trail_keys[8] = {
    {4, 0x1A1}, {4, 0x1A2}, {4, 0x1A0}, {4, 0x1A1}, {4, 0x1A0}, {4, 0x1A1}, {4, 0x1A2}, {-1, 0x1A3},
};

ScriptCallEntry enemy_part_call_table[10] = {
    {NULL, 0},
    {script_cursor_advance_alt, 0},
    {script_jump_if_near, 0},
    {script_jump_if_far, 0},
    {script_turn_to_player, 0},
    {script_jump_if_op_eq, 0},
    {stream_read_halfword, 0},
    {script_load_table_entry, 0},
    {obj_trail_emit, 0},
    {script_op_jump, 0},
};

struct SemiTruckMechM6BossScripts {
    s16 idle[6];
    s16 ready[2];
    s16 wait_go[8];
    s16 walk_start[4];
    s16 walk_branch[12];
    s16 walk_left_wait[8];
    s16 walk_left_trail[2];
    s16 walk_left_settle[8];
    s16 walk_left_exit[2];
    s16 walk_right_begin[12];
    s16 walk_right_wait[8];
    s16 walk_right_trail[2];
    s16 walk_right_settle[8];
    s16 walk_right_exit[2];
    s16 walk_loop[4];
    s16 walk_to_right[4];
    s16 *table[16];
} semi_truck_mech_m6_boss_scripts = {
    /* idle */ {
        NEXT_STATE(ENEMY_CHILD_PART_STATE_IDLE),
        WAIT(64),
        JUMP(SEMI_TRUCK_MECH_M6_BOSS_READY),
    },
    /* ready */ {
        NEXT_STATE(ENEMY_CHILD_PART_STATE_READY),
    },
    /* wait_go */ {
        WAIT(1),
        ENEMY_CHILD_PART_JUMP_IF_OP_EQ, -1, SEMI_TRUCK_MECH_M6_BOSS_WALK_START,
        JUMP(SEMI_TRUCK_MECH_M6_BOSS_WAIT_GO),
    },
    /* walk_start */ {
        WAIT(1),
        JUMP(SEMI_TRUCK_MECH_M6_BOSS_WALK_LOOP),
    },
    /* walk_branch */ {
        NEXT_STATE(ENEMY_CHILD_PART_STATE_WAIT_GO),
        WAIT(1),
        NEXT_STATE(ENEMY_CHILD_PART_STATE_WALK_START),
        ENEMY_CHILD_PART_JUMP, 1750, SEMI_TRUCK_MECH_M6_BOSS_WALK_LEFT_WAIT,
        NEXT_STATE(ENEMY_CHILD_PART_STATE_WALK_LEFT_SETTLE),
    },
    /* walk_left_wait */ {
        WAIT(1),
        ENEMY_CHILD_PART_JUMP_IF_OP_EQ, -1, SEMI_TRUCK_MECH_M6_BOSS_WALK_LEFT_TRAIL,
        JUMP(SEMI_TRUCK_MECH_M6_BOSS_WALK_LEFT_WAIT),
    },
    /* walk_left_trail */ {
        ENEMY_CHILD_PART_TRAIL_EMIT, -160,
    },
    /* walk_left_settle */ {
        WAIT(1),
        ENEMY_CHILD_PART_JUMP_IF_OP_EQ, -1, SEMI_TRUCK_MECH_M6_BOSS_WALK_LEFT_EXIT,
        JUMP(SEMI_TRUCK_MECH_M6_BOSS_WALK_LEFT_SETTLE),
    },
    /* walk_left_exit */ {
        ENEMY_CHILD_PART_LOAD_TABLE_ENTRY,
    },
    /* walk_right_begin */ {
        NEXT_STATE(ENEMY_CHILD_PART_STATE_WAIT_GO),
        WAIT(1),
        NEXT_STATE(ENEMY_CHILD_PART_STATE_WALK_LEFT),
        ENEMY_CHILD_PART_JUMP, 1750, SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_WAIT,
        NEXT_STATE(ENEMY_CHILD_PART_STATE_WALK_RIGHT),
    },
    /* walk_right_wait */ {
        WAIT(1),
        ENEMY_CHILD_PART_JUMP_IF_OP_EQ, -1, SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_TRAIL,
        JUMP(SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_WAIT),
    },
    /* walk_right_trail */ {
        ENEMY_CHILD_PART_TRAIL_EMIT, 160,
    },
    /* walk_right_settle */ {
        WAIT(1),
        ENEMY_CHILD_PART_JUMP_IF_OP_EQ, -1, SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_EXIT,
        JUMP(SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_SETTLE),
    },
    /* walk_right_exit */ {
        ENEMY_CHILD_PART_LOAD_TABLE_ENTRY,
    },
    /* walk_loop */ {
        ENEMY_CHILD_PART_STREAM_READ_HALFWORD, 15,
        JUMP(SEMI_TRUCK_MECH_M6_BOSS_WALK_BRANCH),
    },
    /* walk_to_right */ {
        ENEMY_CHILD_PART_STREAM_READ_HALFWORD, 14,
        JUMP(SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_BEGIN),
    },
    /* table */ {
        semi_truck_mech_m6_boss_scripts.idle, semi_truck_mech_m6_boss_scripts.ready, semi_truck_mech_m6_boss_scripts.wait_go, semi_truck_mech_m6_boss_scripts.walk_start, semi_truck_mech_m6_boss_scripts.walk_branch, semi_truck_mech_m6_boss_scripts.walk_left_wait,
        semi_truck_mech_m6_boss_scripts.walk_left_trail, semi_truck_mech_m6_boss_scripts.walk_left_settle, semi_truck_mech_m6_boss_scripts.walk_left_exit, semi_truck_mech_m6_boss_scripts.walk_right_begin, semi_truck_mech_m6_boss_scripts.walk_right_wait, semi_truck_mech_m6_boss_scripts.walk_right_trail,
        semi_truck_mech_m6_boss_scripts.walk_right_settle, semi_truck_mech_m6_boss_scripts.walk_right_exit, semi_truck_mech_m6_boss_scripts.walk_loop, semi_truck_mech_m6_boss_scripts.walk_to_right,
    },
};

struct SemiTruckMechM6BossAnims {
    s16 idle[4];
    s16 wake[68];
    s16 ready_hold[4];
    s16 walk_a[40];
    s16 walk_a_end[36];
    s16 walk_b[40];
    s16 walk_b_end[36];
    s16 walk_a_fast[40];
    s16 walk_a_fast_end[36];
    s16 walk_b_fast[40];
    s16 walk_b_fast_end[36];
    s16 *table[11];
} semi_truck_mech_m6_boss_anims = {
    /* idle */ {
        STEP(2, 129),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_IDLE),
    },
    /* wake */ {
        SOUND(0),
        STEP(2, 129),
        STEP(2, 130),
        STEP(2, 131),
        STEP(2, 132),
        STEP(2, 133),
        STEP(2, 134),
        STEP(2, 135),
        STEP(2, 136),
        STEP(2, 137),
        STEP(2, 138),
        STEP(2, 139),
        STEP(2, 140),
        STEP(2, 141),
        STEP(2, 142),
        STEP(2, 143),
        STEP(2, 144),
        STEP(2, 145),
        STEP(2, 146),
        STEP(2, 147),
        STEP(2, 148),
        STEP(2, 149),
        STEP(2, 150),
        STEP(2, 151),
        STEP(2, 152),
        STEP(2, 153),
        STEP(2, 154),
        STEP(2, 155),
        STEP(2, 156),
        STEP(2, 157),
        STEP(2, 158),
        STEP(2, 159),
        STEP(2, 160),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_READY_HOLD),
    },
    /* ready_hold */ {
        STEP(2, 160),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_READY_HOLD),
    },
    /* walk_a */ {
        STEP(1, 160),
        STEP(1, 161),
        STEP(1, 162),
        STEP(1, 163),
        STEP(1, 164),
        STEP(1, 165),
        STEP(1, 166),
        STEP(1, 167),
        STEP(1, 168),
        STEP(1, 169),
        STEP(1, 170),
        STEP(1, 171),
        STEP(1, 172),
        STEP(1, 173),
        STEP(1, 174),
        STEP(1, 175),
        STEP(1, 176),
        STEP(1, 177),
        STEP(1, 178),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_A_END),
    },
    /* walk_a_end */ {
        STEP(1, 179),
        STEP(1, 180),
        STEP(1, 181),
        STEP(1, 182),
        STEP(1, 183),
        STEP(1, 184),
        STEP(1, 185),
        STEP(1, 186),
        STEP(1, 187),
        STEP(1, 188),
        STEP(1, 189),
        STEP(1, 190),
        STEP(1, 191),
        STEP(1, 192),
        STEP(1, 193),
        STEP(1, 194),
        STEP(1, 195),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_READY_HOLD),
    },
    /* walk_b */ {
        STEP(1, 208),
        STEP(1, 209),
        STEP(1, 210),
        STEP(1, 211),
        STEP(1, 212),
        STEP(1, 213),
        STEP(1, 214),
        STEP(1, 215),
        STEP(1, 216),
        STEP(1, 217),
        STEP(1, 218),
        STEP(1, 219),
        STEP(1, 220),
        STEP(1, 221),
        STEP(1, 222),
        STEP(1, 223),
        STEP(1, 224),
        STEP(1, 225),
        STEP(1, 226),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_B_END),
    },
    /* walk_b_end */ {
        STEP(1, 227),
        STEP(1, 228),
        STEP(1, 229),
        STEP(1, 230),
        STEP(1, 231),
        STEP(1, 232),
        STEP(1, 233),
        STEP(1, 234),
        STEP(1, 235),
        STEP(1, 236),
        STEP(1, 237),
        STEP(1, 238),
        STEP(1, 239),
        STEP(1, 240),
        STEP(1, 241),
        STEP(1, 242),
        STEP(1, 243),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_READY_HOLD),
    },
    /* walk_a_fast */ {
        STEP(0, 160),
        STEP(0, 161),
        STEP(0, 162),
        STEP(0, 163),
        STEP(0, 164),
        STEP(0, 165),
        STEP(0, 166),
        STEP(0, 167),
        STEP(0, 168),
        STEP(0, 169),
        STEP(0, 170),
        STEP(0, 171),
        STEP(0, 172),
        STEP(0, 173),
        STEP(0, 174),
        STEP(0, 175),
        STEP(0, 176),
        STEP(0, 177),
        STEP(0, 178),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_A_FAST_END),
    },
    /* walk_a_fast_end */ {
        STEP(0, 179),
        STEP(0, 180),
        STEP(0, 181),
        STEP(0, 182),
        STEP(0, 183),
        STEP(0, 184),
        STEP(0, 185),
        STEP(0, 186),
        STEP(0, 187),
        STEP(0, 188),
        STEP(0, 189),
        STEP(0, 190),
        STEP(0, 191),
        STEP(0, 192),
        STEP(0, 193),
        STEP(0, 194),
        STEP(0, 195),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_READY_HOLD),
    },
    /* walk_b_fast */ {
        STEP(0, 208),
        STEP(0, 209),
        STEP(0, 210),
        STEP(0, 211),
        STEP(0, 212),
        STEP(0, 213),
        STEP(0, 214),
        STEP(0, 215),
        STEP(0, 216),
        STEP(0, 217),
        STEP(0, 218),
        STEP(0, 219),
        STEP(0, 220),
        STEP(0, 221),
        STEP(0, 222),
        STEP(0, 223),
        STEP(0, 224),
        STEP(0, 225),
        STEP(0, 226),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_B_FAST_END),
    },
    /* walk_b_fast_end */ {
        STEP(0, 227),
        STEP(0, 228),
        STEP(0, 229),
        STEP(0, 230),
        STEP(0, 231),
        STEP(0, 232),
        STEP(0, 233),
        STEP(0, 234),
        STEP(0, 235),
        STEP(0, 236),
        STEP(0, 237),
        STEP(0, 238),
        STEP(0, 239),
        STEP(0, 240),
        STEP(0, 241),
        STEP(0, 242),
        STEP(0, 243),
        GOTO(SEMI_TRUCK_MECH_M6_BOSS_ANIM_READY_HOLD),
    },
    /* table */ {
        semi_truck_mech_m6_boss_anims.idle, semi_truck_mech_m6_boss_anims.wake, semi_truck_mech_m6_boss_anims.ready_hold, semi_truck_mech_m6_boss_anims.walk_a, semi_truck_mech_m6_boss_anims.walk_a_end, semi_truck_mech_m6_boss_anims.walk_b,
        semi_truck_mech_m6_boss_anims.walk_b_end, semi_truck_mech_m6_boss_anims.walk_a_fast, semi_truck_mech_m6_boss_anims.walk_a_fast_end, semi_truck_mech_m6_boss_anims.walk_b_fast, semi_truck_mech_m6_boss_anims.walk_b_fast_end,
    },
};

s16 *D_8011F0D8[1] = {
    semi_truck_mech_m6_boss_idle,
};

StateEntry enemy_part_states[7] = {
    {0, SEMI_TRUCK_MECH_M6_BOSS_ANIM_IDLE, 0},
    {0, SEMI_TRUCK_MECH_M6_BOSS_ANIM_WAKE, 0},
    {0, SEMI_TRUCK_MECH_M6_BOSS_ANIM_READY_HOLD, 0},
    {0, SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_A, 0},
    {0, SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_B, 0},
    {0, SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_A_FAST, 0},
    {0, SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_B_FAST, 0},
};

s16 part_hit_factors[8] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
};

SoundVolume D_8011F124[1] = {
    {0x30A4, 0x1000},
};

Keyframe side_shot_keyframes[13] = {
    {1, 0x1B0}, {1, 0x1B1}, {1, 0x1B2}, {1, 0x1B3}, {1, 0x1B4}, {1, 0x1B5}, {1, 0x1B6}, {1, 0x1B7},
    {1, 0x1B8}, {1, 0x1B9}, {1, 0x1BA}, {1, 0x1BB}, {-1, 0x1BC},
};

ScriptCallEntry D_8011F160[14] = {
    {NULL, 0},
    {script_cursor_advance, 0},
    {script_jump_if_near_alt, 0},
    {obj_script_jump_if_far, 0},
    {script_turn_to_player_jump, 0},
    {script_case_match, 0},
    {script_read_u16, 0},
    {script_jump_indexed, 0},
    {obj_fire_both_sides, 0},
    {obj_attach_default, 0},
    {obj_sound_loop_start, 0},
    {obj_sound_loop_stop, 0},
    {sound_start_held, 0},
    {sound_stop_held, 0},
};

struct EnemyPartChildScripts {
    s16 deploy[6];
    s16 await_trigger[8];
    s16 attach[4];
    s16 fire_start[8];
    s16 fire_loop[8];
    s16 fire_burst[4];
    s16 fire_end[6];
    s16 fire_restart[4];
    s16 cooldown[4];
    s16 *table[9];
} enemy_part_child_scripts = {
    /* deploy */ {
        NEXT_STATE(ENEMY_PART_CHILD_STATE_STOWED),
        WAIT(32),
        NEXT_STATE(ENEMY_PART_CHILD_STATE_DEPLOY),
    },
    /* await_trigger */ {
        WAIT(1),
        ENEMY_PART_CHILD_CASE_MATCH, -1, ENEMY_PART_CHILD_ATTACH,
        JUMP(ENEMY_PART_CHILD_AWAIT_TRIGGER),
    },
    /* attach */ {
        ENEMY_PART_CHILD_ATTACH_DEFAULT,
        ENEMY_PART_CHILD_SOUND_START_HELD,
        JUMP(ENEMY_PART_CHILD_FIRE_RESTART),
    },
    /* fire_start */ {
        ENEMY_PART_CHILD_SOUND_LOOP_START,
        NEXT_STATE(ENEMY_PART_CHILD_STATE_FIRE),
        WAIT(1),
        SET_COUNTER(8),
    },
    /* fire_loop */ {
        WAIT(1),
        ENEMY_PART_CHILD_CASE_MATCH, -1, ENEMY_PART_CHILD_FIRE_BURST,
        JUMP(ENEMY_PART_CHILD_FIRE_LOOP),
    },
    /* fire_burst */ {
        ENEMY_PART_CHILD_FIRE_BOTH_SIDES,
        LOOP(ENEMY_PART_CHILD_FIRE_LOOP),
    },
    /* fire_end */ {
        NEXT_STATE(ENEMY_PART_CHILD_STATE_IDLE),
        ENEMY_PART_CHILD_SOUND_LOOP_STOP,
        JUMP(ENEMY_PART_CHILD_COOLDOWN),
    },
    /* fire_restart */ {
        WAIT(1),
        JUMP(ENEMY_PART_CHILD_FIRE_START),
    },
    /* cooldown */ {
        WAIT(64),
        JUMP(ENEMY_PART_CHILD_FIRE_RESTART),
    },
    /* table */ {
        enemy_part_child_scripts.deploy, enemy_part_child_scripts.await_trigger, enemy_part_child_scripts.attach, enemy_part_child_scripts.fire_start, enemy_part_child_scripts.fire_loop, enemy_part_child_scripts.fire_burst,
        enemy_part_child_scripts.fire_end, enemy_part_child_scripts.fire_restart, enemy_part_child_scripts.cooldown,
    },
};

struct EnemyPartChildAnims {
    s16 hold[4];
    s16 deploy[44];
    s16 idle[4];
    s16 fire[6];
    s16 *table[4];
} enemy_part_child_anims = {
    /* hold */ {
        STEP(2, 257),
        GOTO(ENEMY_PART_CHILD_ANIM_HOLD),
    },
    /* deploy */ {
        SOUND(0),
        STEP(2, 257),
        STEP(2, 258),
        STEP(2, 259),
        STEP(2, 260),
        STEP(2, 261),
        STEP(2, 262),
        STEP(2, 263),
        STEP(2, 264),
        STEP(2, 265),
        STEP(2, 266),
        STEP(2, 267),
        STEP(2, 268),
        STEP(2, 269),
        STEP(2, 270),
        STEP(2, 271),
        STEP(2, 272),
        STEP(2, 273),
        STEP(2, 274),
        STEP(2, 275),
        STEP(2, 276),
        GOTO(ENEMY_PART_CHILD_ANIM_IDLE),
    },
    /* idle */ {
        STEP(2, 280),
        GOTO(ENEMY_PART_CHILD_ANIM_IDLE),
    },
    /* fire */ {
        STEP(4, 280),
        STEP(4, 281),
        GOTO(ENEMY_PART_CHILD_ANIM_FIRE),
    },
    /* table */ {
        enemy_part_child_anims.hold, enemy_part_child_anims.deploy, enemy_part_child_anims.idle, enemy_part_child_anims.fire,
    },
};

s16 *D_8011F2E0[1] = {
    enemy_part_child_deploy,
};

StateEntry D_8011F2E4[5] = {
    {0, ENEMY_PART_CHILD_ANIM_HOLD, 0},
    {0, ENEMY_PART_CHILD_ANIM_DEPLOY, 0},
    {0, ENEMY_PART_CHILD_ANIM_IDLE, 0},
    {0, ENEMY_PART_CHILD_ANIM_FIRE, 0},
    {0, ENEMY_PART_CHILD_ANIM_IDLE, 0},
};

s16 obj_hit_mask_weights[8] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
};

s32 span_table_base[17] = {
    4, 0x9006000, 0x6000, 0x9000000, 0, 0x6C07680,
    0x7680, 0x6C00000, 0, 0x9003C00, 0x3C00, 0x9000000,
    0, 0x6C02400, 0x2400, 0x6C00000, 0,
};

s32 span_source_table[41] = {
    0x15, (s32)0xFC4C0001, (s32)0xFFCA0000, (s32)0xF4E40001, (s32)0xFFCA0000, (s32)0xED7C0001,
    (s32)0xFFCA0000, (s32)0xE77C0000, (s32)0xFFA60000, (s32)0xE17C0000, (s32)0xFFA60000, (s32)0xDB7C0000,
    (s32)0xFFA60000, (s32)0xD57C0000, (s32)0xFFA60000, (s32)0xCF7C0000, (s32)0xFFA60000, (s32)0xC97C0000,
    (s32)0xFFA60000, (s32)0xC37C0000, (s32)0xFFA60000, (s32)0xBD7C0000, (s32)0xFFA60000, (s32)0xB77C0000,
    (s32)0xFFA60000, (s32)0xB17C0000, (s32)0xFFA60000, (s32)0xAB7C0000, (s32)0xFFA60000, (s32)0xA57C0000,
    (s32)0xFFA60000, (s32)0x9F7C0000, (s32)0xFFA60000, (s32)0x997C0000, (s32)0xFFA60000, (s32)0x937C0000,
    (s32)0xFFA60000, (s32)0x8D7C0000, (s32)0xFFA60000, (s32)0x877C0000, (s32)0xFFA60000,
};

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

#include "../stage/data/ratan_tbl.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_80124788[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/video_mode_id.c"

#include "../stage/data/tint_scale_r.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_8012590C[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_80125F2C = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

#include "../stage/data/model_pchr_saved.c"

s32 cam_rec_request = 0;

s32 cam_fade_dir = 0;

s32 cam_fade_ramp = 0;

s32 loop_sound_handle = 0;

s32 cam_bounce_offset = 0;

s32 last_flow_state = 0;

s32 loop_sound_saved_mode = 0;

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

s32 part_loop_sound_handle = 0;

s16 script_index[2] = {
    0, 0,
};

s16 D_801273B0 = 0;

s32 obj_sound_loop_handle = 0;

s32 sound_held_handle = 0;

#include "../stage/data/giant_robot_systems_active.c"

#include "../stage/data/frame_work_area.c"

#include "../stage/data/model_slot_count.c"

u32 D_80127474 = 0x00000000;

#include "../stage/data/ring32_index.c"

#include "../stage/data/vec3_x.c"

#include "../stage/data/vec3_y.c"

#include "../stage/data/vec3_z.c"

#include "../stage/data/vec3_pad.c"

#include "../stage/data/d_80120008.c"

#include "../stage/data/img_upload_active.c"

#include "../stage/data/light_data_base.c"

#include "../stage/data/interp_enabled_flag.c"

#include "../stage/data/interp_record_count.c"

#include "../stage/data/interp1c_count.c"

#include "../stage/data/interp2c_count.c"

#include "../stage/data/interp38_count.c"

#include "../stage/data/interp38b_count.c"

#include "../stage/data/scratch_saved_slot_count.c"

#include "../stage/data/scratch_saved_top.c"

#include "../stage/data/scratch_slot_count.c"

#include "../stage/data/rec_count.c"

#include "../stage/data/rec_pos_total.c"

#include "../stage/data/aobj_entry_count.c"

#include "../stage/data/max_apex_count.c"

#include "../stage/data/max_poly_count.c"

#include "../stage/data/max_unit_count.c"

#include "../stage/data/square_count.c"

#include "../stage/data/poly_count.c"

#include "../stage/data/stage_offset_x.c"

#include "../stage/data/stage_offset_y.c"

#include "../stage/data/colour_table_ptr.c"

#include "../stage/data/clamp_table_ptr.c"

#include "../stage/data/slope_table_ptr.c"

#include "../stage/data/d_8012006C.c"

#include "../stage/data/player_last_flags.c"

#include "../stage/data/player_pos_x.c"

#include "../stage/data/player_pos_y.c"

#include "../stage/data/player_pos_z.c"

#include "../stage/data/player_clamp_box.c"

#include "../stage/data/player_vertical_blocked.c"

u32 D_80127510 = 0x00000000;

#include "../stage/data/pause_flag.c"

#include "../stage/data/cell_cursor_step1.c"

#include "../stage/data/cell_cursor_step2.c"

#include "../stage/data/cell_cursor_step1_saved.c"

#include "../stage/data/cell_cursor_step2_saved.c"

#include "../stage/data/frames_pending.c"

#include "../stage/data/pal_accum.c"

#include "../stage/data/step_abort.c"

#include "../stage/data/stage_heap_mark.c"

#include "../stage/data/area_sound_requested.c"

#include "../stage/data/pause_cooldown.c"

#include "../stage/data/area_sound_index.c"

#include "../stage/data/area_load_next.c"

#include "../stage/data/area_load_timer.c"

#include "../stage/data/area_load_duration.c"

#include "../stage/data/area_fade_rate.c"

#include "../stage/data/bg_load_pending.c"

#include "../stage/data/bg_buffer.c"

#include "../stage/data/bg_load_size.c"

#include "../stage/data/bg_load_name.c"

#include "../stage/data/bg_load_file.c"

#include "../stage/data/end_ramp.c"

#include "../stage/data/end_ramp_rate.c"

#include "../stage/data/debug_menu_cursor.c"

#include "../stage/data/debug_menu_enabled.c"

#include "../stage/data/part_time.c"

#include "../stage/data/part_timer_on.c"

#include "../stage/data/part_pose_base.c"

#include "../stage/data/part_offset.c"

#include "../stage/data/part_fade_handler.c"

#include "../stage/data/part_slot_count.c"

#include "../stage/data/str_queue_count.c"

#include "../stage/data/stage_queue_count.c"

#include "../stage/data/stage_data_ptr.c"

#include "../stage/data/name_table_root.c"

#include "../stage/data/name_table_cwd.c"

#include "../stage/data/player_pose_base.c"

#include "../stage/data/player_coll_part.c"

#include "../stage/data/hit_spark_pchr.c"

#include "../stage/data/beam_model_base.c"

#include "../stage/data/player_glow_level.c"

#include "../stage/data/player_glow_step.c"

#include "../stage/data/player_death_fade.c"

#include "../stage/data/player_death_blend.c"

#include "../stage/data/player_death_spark_timer.c"

#include "../stage/data/player_death_frames.c"

#include "../stage/data/player_exit_timer.c"

#include "../stage/data/player_walk_phase.c"

#include "../stage/data/player_walk_meter.c"

#include "../stage/data/player_strafe_meter.c"

#include "../stage/data/player_air_blend.c"

#include "../stage/data/player_rise_phase.c"

#include "../stage/data/player_fall_blend.c"

#include "../stage/data/player_land_blend.c"

#include "../stage/data/player_charge_blend.c"

#include "../stage/data/player_charge_phase.c"

#include "../stage/data/beam_countdown.c"

#include "../stage/data/player_ground_y.c"

#include "../stage/data/player_charge_timer.c"

#include "../stage/data/target_hit_steps.c"

#include "../stage/data/fire_hold_steps.c"

#include "../stage/data/missile_delay.c"

#include "../stage/data/missiles_left.c"

#include "../stage/data/player_shake_index.c"

#include "../stage/data/player_fade_level.c"

#include "../stage/data/cooldown_18c.c"

#include "../stage/data/idle_steps.c"

#include "../stage/data/cooldown_194.c"

#include "../stage/data/view_nudge.c"

#include "../stage/data/cooldown_19c.c"

#include "../stage/data/player_held.c"

#include "../stage/data/player_pressed.c"

#include "../stage/data/player_input_skip.c"

#include "../stage/data/flow.c"

#include "../stage/data/pending_turn.c"

#include "../stage/data/flow_max.c"

#include "../stage/data/flow_ramp.c"

#include "../stage/data/flow_step.c"

#include "../stage/data/pitch_recenter.c"

#include "../stage/data/charge_sound_handle.c"

#include "../stage/data/move_sound_handle.c"

#include "../stage/data/charge_hum_a.c"

#include "../stage/data/charge_hum_b.c"

#include "../stage/data/player_step_phase.c"

#include "../stage/data/player_step_flag.c"

#include "../stage/data/contact_20_steps.c"

#include "../stage/data/jump_latch.c"

#include "../stage/data/player_run_timer.c"

#include "../stage/data/moving.c"

#include "../stage/data/move_speed.c"

#include "../stage/data/player_status.c"

#include "../stage/data/timer_count.c"

#include "../stage/data/beam_timer_next.c"

#include "../stage/data/timer_first.c"

#include "../stage/data/d_80120204.c"

#include "../stage/data/view_cache_flags.c"

#include "../stage/data/d_8012020C.c"

#include "../stage/data/d_8012020E.c"

#include "../stage/data/d_80120210.c"

#include "../stage/data/fade_free_count.c"

#include "../stage/data/grid_block.c"

#include "../stage/data/grid_entry_total.c"

#include "../stage/data/grid_entries.c"

#include "../stage/data/hook_range_hi.c"

#include "../stage/data/hook_range_lo.c"

#include "../stage/data/grid_camera_phase.c"

#include "../stage/data/grid_active_flag.c"

#include "../stage/data/hit_ext_flag.c"

#include "../stage/data/effect_base.c"

#include "../stage/data/fades_head.c"

#include "../stage/data/fades_free.c"

#include "../stage/data/mission_active.c"

#include "../stage/data/mission_elapsed.c"

#include "../stage/data/mission_timer.c"

#include "../stage/data/mission_limit.c"

#include "../stage/data/player_score.c"

#include "../stage/data/player_shield.c"

#include "../stage/data/grenade_count.c"

#include "../stage/data/kill_count.c"

#include "../stage/data/mission_total.c"

#include "../stage/data/mission_count.c"

#include "../stage/data/mission_score.c"

#include "../stage/data/stage_end.c"

#include "../stage/data/stage_flags.c"

#include "../stage/data/stage_ready_flag.c"

#include "../stage/data/key_config_index.c"

#include "../stage/data/d_80120280.c"

#include "../stage/data/d_80120284.c"

#include "../stage/data/spark_model_base.c"

#include "../stage/data/track_base.c"

#include "../stage/data/shield_gauge.c"

#include "../stage/data/shield_prev.c"

#include "../stage/data/pulse_phase.c"

#include "../stage/data/alert_level.c"

#include "../stage/data/alert_count.c"

#include "../stage/data/shade_angle.c"

#include "../stage/data/cam_fade_amount.c"

#include "../stage/data/view_split_amount.c"

#include "../stage/data/meter_a_level.c"

#include "../stage/data/meter_b_level.c"

#include "../stage/data/hud_gfx_base.c"

#include "../stage/data/stage_end_state.c"

#include "../stage/data/meter_a_rate.c"

#include "../stage/data/meter_b_rate.c"

#include "../stage/data/meter_run_flag.c"

#include "../stage/data/message_shown_flag.c"

#include "../stage/data/req_queue_count.c"

#include "../stage/data/d_801202D4.c"

#include "../stage/data/draw_enabled.c"

#include "../stage/data/area_warnings_flag.c"

#include "../stage/data/msg_queue_length.c"

#include "../stage/data/msg_write_index.c"

#include "../stage/data/msg_read_index.c"

#include "../stage/data/msg_scroll_timer.c"

#include "../stage/data/msg_wait_timer.c"

#include "../stage/data/msg_text_ptr.c"

#include "../stage/data/hud_on_flag.c"

#include "../stage/data/msg_enabled.c"

#include "../stage/data/hud_view_x.c"

#include "../stage/data/hud_view_y.c"

#include "../stage/data/hud_view_w.c"

#include "../stage/data/hud_view_h.c"

#include "../stage/data/pause_menu_angle.c"

#include "../stage/data/pause_menu_choice.c"

#include "../stage/data/pause_menu_cursor.c"

#include "../stage/data/pause_menu_cursor_prev.c"

#include "../stage/data/mission_result_slide_x.c"

#include "../stage/data/mission_result_base_y.c"

#include "../stage/data/mission_result_zoom.c"

#include "../stage/data/mission_result_zoom_slow.c"

#include "../stage/data/screen_fade_alpha.c"

#include "../stage/data/view_scale.c"

#include "../stage/data/dim_level_b.c"

#include "../stage/data/result_time_bonus.c"

#include "../stage/data/result_shield_bonus.c"

#include "../stage/data/result_grenade_bonus.c"

#include "../stage/data/result_total.c"

#include "../stage/data/result_score.c"

#include "../stage/data/result_hitrate.c"

#include "../stage/data/result_kill_count.c"

#include "../stage/data/result_class.c"

#include "../stage/data/result_rank_place.c"

#include "../stage/data/mission_result_exit_flag.c"

#include "../stage/data/stage_transition_flag.c"

#include "../stage/data/ui_item_free_count.c"

#include "../stage/data/meter_start_time.c"

#include "../stage/data/meter_end_time.c"

#include "../stage/data/gauge_max.c"

#include "../stage/data/gauge_value.c"

/* labels inside the objects above */
__asm__(".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl D_80125F32\n.set D_80125F32, texture_image+0x2\n"
        ".globl sincos_deg90\n.set sincos_deg90, rcossin_tbl+0x1000\n"
        ".globl view_sincos\n.set view_sincos, rcossin_tbl+0x2000\n"
        ".globl sincos_deg270\n.set sincos_deg270, rcossin_tbl+0x3000\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n"
        ".globl D_80127626\n.set D_80127626, view_nudge+0x2\n"
        ".globl d_801201AE\n.set d_801201AE, flow+0x2\n"
        ".globl flow_angle\n.set flow_angle, flow+0x4\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl semi_truck_mech_m6_boss_idle\n.set semi_truck_mech_m6_boss_idle, semi_truck_mech_m6_boss_scripts+0x0\n"
        ".globl semi_truck_mech_m6_boss_ready\n.set semi_truck_mech_m6_boss_ready, semi_truck_mech_m6_boss_scripts+0xC\n"
        ".globl semi_truck_mech_m6_boss_wait_go\n.set semi_truck_mech_m6_boss_wait_go, semi_truck_mech_m6_boss_scripts+0x10\n"
        ".globl semi_truck_mech_m6_boss_walk_start\n.set semi_truck_mech_m6_boss_walk_start, semi_truck_mech_m6_boss_scripts+0x20\n"
        ".globl semi_truck_mech_m6_boss_walk_branch\n.set semi_truck_mech_m6_boss_walk_branch, semi_truck_mech_m6_boss_scripts+0x28\n"
        ".globl semi_truck_mech_m6_boss_walk_left_wait\n.set semi_truck_mech_m6_boss_walk_left_wait, semi_truck_mech_m6_boss_scripts+0x40\n"
        ".globl semi_truck_mech_m6_boss_walk_left_trail\n.set semi_truck_mech_m6_boss_walk_left_trail, semi_truck_mech_m6_boss_scripts+0x50\n"
        ".globl semi_truck_mech_m6_boss_walk_left_settle\n.set semi_truck_mech_m6_boss_walk_left_settle, semi_truck_mech_m6_boss_scripts+0x54\n"
        ".globl semi_truck_mech_m6_boss_walk_left_exit\n.set semi_truck_mech_m6_boss_walk_left_exit, semi_truck_mech_m6_boss_scripts+0x64\n"
        ".globl semi_truck_mech_m6_boss_walk_right_begin\n.set semi_truck_mech_m6_boss_walk_right_begin, semi_truck_mech_m6_boss_scripts+0x68\n"
        ".globl semi_truck_mech_m6_boss_walk_right_wait\n.set semi_truck_mech_m6_boss_walk_right_wait, semi_truck_mech_m6_boss_scripts+0x80\n"
        ".globl semi_truck_mech_m6_boss_walk_right_trail\n.set semi_truck_mech_m6_boss_walk_right_trail, semi_truck_mech_m6_boss_scripts+0x90\n"
        ".globl semi_truck_mech_m6_boss_walk_right_settle\n.set semi_truck_mech_m6_boss_walk_right_settle, semi_truck_mech_m6_boss_scripts+0x94\n"
        ".globl semi_truck_mech_m6_boss_walk_right_exit\n.set semi_truck_mech_m6_boss_walk_right_exit, semi_truck_mech_m6_boss_scripts+0xA4\n"
        ".globl semi_truck_mech_m6_boss_walk_loop\n.set semi_truck_mech_m6_boss_walk_loop, semi_truck_mech_m6_boss_scripts+0xA8\n"
        ".globl semi_truck_mech_m6_boss_walk_to_right\n.set semi_truck_mech_m6_boss_walk_to_right, semi_truck_mech_m6_boss_scripts+0xB0\n"
        ".globl enemy_child_part_jump_table\n.set enemy_child_part_jump_table, semi_truck_mech_m6_boss_scripts+0xB8\n"
        ".globl semi_truck_mech_m6_boss_anim_idle\n.set semi_truck_mech_m6_boss_anim_idle, semi_truck_mech_m6_boss_anims+0x0\n"
        ".globl semi_truck_mech_m6_boss_anim_wake\n.set semi_truck_mech_m6_boss_anim_wake, semi_truck_mech_m6_boss_anims+0x8\n"
        ".globl semi_truck_mech_m6_boss_anim_ready_hold\n.set semi_truck_mech_m6_boss_anim_ready_hold, semi_truck_mech_m6_boss_anims+0x90\n"
        ".globl semi_truck_mech_m6_boss_anim_walk_a\n.set semi_truck_mech_m6_boss_anim_walk_a, semi_truck_mech_m6_boss_anims+0x98\n"
        ".globl semi_truck_mech_m6_boss_anim_walk_a_end\n.set semi_truck_mech_m6_boss_anim_walk_a_end, semi_truck_mech_m6_boss_anims+0xE8\n"
        ".globl semi_truck_mech_m6_boss_anim_walk_b\n.set semi_truck_mech_m6_boss_anim_walk_b, semi_truck_mech_m6_boss_anims+0x130\n"
        ".globl semi_truck_mech_m6_boss_anim_walk_b_end\n.set semi_truck_mech_m6_boss_anim_walk_b_end, semi_truck_mech_m6_boss_anims+0x180\n"
        ".globl semi_truck_mech_m6_boss_anim_walk_a_fast\n.set semi_truck_mech_m6_boss_anim_walk_a_fast, semi_truck_mech_m6_boss_anims+0x1C8\n"
        ".globl semi_truck_mech_m6_boss_anim_walk_a_fast_end\n.set semi_truck_mech_m6_boss_anim_walk_a_fast_end, semi_truck_mech_m6_boss_anims+0x218\n"
        ".globl semi_truck_mech_m6_boss_anim_walk_b_fast\n.set semi_truck_mech_m6_boss_anim_walk_b_fast, semi_truck_mech_m6_boss_anims+0x260\n"
        ".globl semi_truck_mech_m6_boss_anim_walk_b_fast_end\n.set semi_truck_mech_m6_boss_anim_walk_b_fast_end, semi_truck_mech_m6_boss_anims+0x2B0\n"
        ".globl enemy_child_part_script_table\n.set enemy_child_part_script_table, semi_truck_mech_m6_boss_anims+0x2F8\n"
        ".globl enemy_part_child_deploy\n.set enemy_part_child_deploy, enemy_part_child_scripts+0x0\n"
        ".globl enemy_part_child_await_trigger\n.set enemy_part_child_await_trigger, enemy_part_child_scripts+0xC\n"
        ".globl enemy_part_child_attach\n.set enemy_part_child_attach, enemy_part_child_scripts+0x1C\n"
        ".globl enemy_part_child_fire_start\n.set enemy_part_child_fire_start, enemy_part_child_scripts+0x24\n"
        ".globl enemy_part_child_fire_loop\n.set enemy_part_child_fire_loop, enemy_part_child_scripts+0x34\n"
        ".globl enemy_part_child_fire_burst\n.set enemy_part_child_fire_burst, enemy_part_child_scripts+0x44\n"
        ".globl enemy_part_child_fire_end\n.set enemy_part_child_fire_end, enemy_part_child_scripts+0x4C\n"
        ".globl enemy_part_child_fire_restart\n.set enemy_part_child_fire_restart, enemy_part_child_scripts+0x58\n"
        ".globl enemy_part_child_cooldown\n.set enemy_part_child_cooldown, enemy_part_child_scripts+0x60\n"
        ".globl enemy_part_child_jump_table\n.set enemy_part_child_jump_table, enemy_part_child_scripts+0x68\n"
        ".globl enemy_part_child_anim_hold\n.set enemy_part_child_anim_hold, enemy_part_child_anims+0x0\n"
        ".globl enemy_part_child_anim_deploy\n.set enemy_part_child_anim_deploy, enemy_part_child_anims+0x8\n"
        ".globl enemy_part_child_anim_idle\n.set enemy_part_child_anim_idle, enemy_part_child_anims+0x60\n"
        ".globl enemy_part_child_anim_fire\n.set enemy_part_child_anim_fire, enemy_part_child_anims+0x68\n"
        ".globl enemy_part_child_script_table\n.set enemy_part_child_script_table, enemy_part_child_anims+0x74\n");
