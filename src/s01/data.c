/* s01 data 0x80116C60-0x80120000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s01_types.h"
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
extern void enemy_alert_update();
extern void enemy_fly_aim();
extern void enemy_fly_approach();
extern void enemy_fly_move();
extern void enemy_fly_spin();
extern void enemy_move_or_wait();
extern void enemy_shoot_update();
extern void enemy_wait_switch();
extern void enemy_walk_step();
extern u8 file_arka_ch0_cb4[];
extern u8 file_arka_ch0_clt[];
extern u8 file_arka_ch0_vx1[];
extern u8 file_arka_tp0_clt[];
extern u8 file_arka_tp0_xs3[];
extern u8 file_bos1_ch0_cb4[];
extern u8 file_bos1_ch0_clt[];
extern u8 file_bos1_ch0_vx1[];
extern u8 file_bos1_ch1_cb4[];
extern u8 file_bos1_ch1_vx1[];
extern u8 file_bos1_tp0_clt[];
extern u8 file_bos1_tp0_xs3[];
extern u8 file_bos1_tp1_clt[];
extern u8 file_bos1_tp1_xs3[];
extern u8 file_msgs_spr_clt[];
extern u8 file_msgs_spr_grc[];
extern u8 file_msgs_spr_so3[];
extern u8 file_msub_ch0_cb4[];
extern u8 file_msub_ch0_clt[];
extern u8 file_msub_ch0_vx1[];
extern u8 file_msub_tp0_clt[];
extern u8 file_msub_tp0_xs3[];
extern u8 file_mth1_ch0_cb4[];
extern u8 file_mth1_ch0_clt[];
extern u8 file_mth1_ch0_vx1[];
extern u8 file_mth1_tp0_clt[];
extern u8 file_mth1_tp0_xs3[];
extern u8 file_ohel_ch0_cb4[];
extern u8 file_ohel_ch0_clt[];
extern u8 file_ohel_ch0_vx1[];
extern u8 file_ohel_tp0_clt[];
extern u8 file_ohel_tp0_xs3[];
extern u8 file_ohel_tp1_clt[];
extern u8 file_ohel_tp1_xs3[];
extern void flyer_retreat();
extern void flyer_wander();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void func_800BF598();
extern void func_800C02FC();
extern void giant_robot_fx_start();
extern void giant_robot_fx_stop();
extern void giant_robot_reset_scale();
extern void giant_robot_side_fx();
extern void giant_robot_sounds_start();
extern void giant_robot_spawn();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void helicopter_spawn();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void key_code_exit_doors_spawn();
extern void keyholder_fuchikoma_spawn();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void obj_aim_at_player();
extern void obj_aim_jitter_placement();
extern void obj_aim_jittered();
extern void obj_area_update();
extern void obj_attack_player();
extern void obj_call_hook();
extern void obj_countdown_step();
extern void obj_face_player();
extern void obj_fire_shot();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_jump_if_player_near();
extern void obj_loop_anim_start();
extern void obj_play_fade_sound();
extern void obj_read_s32();
extern void obj_release_check();
extern void obj_roll_random();
extern void obj_script_jump_if_equal();
extern void obj_script_jump_if_far();
extern void obj_script_jump_if_outside();
extern void obj_script_jump_if_roll_le();
extern void obj_script_loop();
extern void obj_script_read_u16_var();
extern void obj_script_set_selector();
extern void obj_script_set_var();
extern void obj_script_set_var_rand();
extern void obj_script_skip_operand();
extern void obj_set_next_state();
extern void obj_settle_offset();
extern void obj_speed_approach();
extern void obj_sway_start();
extern void params_reset();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void ramp_start_script();
extern void rocket_fuchikoma_spawn();
extern void script_branch_on_flag();
extern void script_case_match();
extern void script_counter_inc();
extern void script_jump_by_player_view();
extern void script_jump_if_below();
extern void script_jump_if_beyond_radius();
extern void script_jump_if_counter_eq();
extern void script_jump_if_counter_ge();
extern void script_jump_if_facing_player_in_radius();
extern void script_jump_if_not_below_speed();
extern void script_jump_if_player_in_radius();
extern void script_jump_if_player_low();
extern void script_jump_if_rand_le();
extern void script_jump_near();
extern void script_jump_near_corner();
extern void script_jump_near_player();
extern void script_jump_table_match();
extern void script_op_clear_flag();
extern void script_op_flag_set();
extern void script_op_jump_clear_flag();
extern void script_op_jump_if_vy_nonneg();
extern void script_op_jump_table_if_player_far();
extern void script_op_set_target();
extern void script_op_set_vy();
extern void script_op_set_yaw_rate();
extern void script_op_sound_loop_start();
extern void script_op_sound_loop_stop();
extern void script_op_state_stop();
extern void script_op_sway_reset();
extern void script_read_long();
extern void script_read_speed_long();
extern void script_set_enemy_var();
extern void script_set_flag();
extern void script_set_turn_mode();
extern void script_turn_to_player_jump();
extern void script_value_queue_push();
extern void smg_soldier_spawn();
extern void sound_zones_init();
extern void stage_init_pursue();
extern u8 str_b01_dat_fac[];
extern u8 str_b01_ene_fac[];
extern u8 str_b01_joy_bin[];
extern u8 str_b11_apdea3[];
extern u8 str_b11_cnf_bcf[];
extern u8 str_bay_apdea3[];
extern u8 str_bay_cnf_bcf[];
extern u8 str_bay_joy_bin[];
extern u8 str_com_dat_fac[];
extern u8 str_enemy_arka_data[];
extern u8 str_enemy_bos1_data[];
extern u8 str_enemy_ctl1_data[];
extern u8 str_enemy_dor1_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_msub_data[];
extern u8 str_enemy_mth1_data[];
extern u8 str_enemy_ohel_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_m01_dat_fac[];
extern u8 str_m01_joy_bin[];
extern u8 str_m11_cnf_bcf[];
extern u8 str_main_data[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_s01_boss[];
extern u8 str_s01_dat_fac[];
extern u8 str_s01_ene_fac[];
extern u8 str_s01_miss[];
extern u8 str_s01_stage[];
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
extern u8 text_packets[];
extern void text_slot_setup();
extern void track_set_enabled();
extern void track_setup();
extern void value_queue_pop();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_80117781[];
extern u8 D_80117782[];
extern u8 D_80117783[];
extern u8 D_8011EA96[];
extern u8 cos_table[];
extern u8 d_80117788[];
extern u8 d_8011778C[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 fade_colour_x_to[];
extern u8 fade_colour_y_to[];
extern u8 gun_hit_effect_table[];
extern u8 smg_soldier_hit_script[];
extern ScanItem D_80116C60[];
extern AreaEntry d_80116CA0;
extern AreaEntry d_80116CC8;
extern ScanItem D_80116CF0[];
extern AreaEntry d_80116D08;
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern s32 keyholder_asset[];
extern ModelBlockRef D_80116E08[];
extern ModelBlockRef D_80116E20[];
extern ModelBlockRef D_80116E30[];
extern ModelBlock D_80116E40;
extern u8 *D_80116E64[];
extern ScanEntry keyholder_scan_entry;
extern s16 enemy_fuchikoma_key_code_holder_anim_idle[];
extern s16 enemy_fuchikoma_key_code_holder_anim_walk[];
extern s16 *keyholder_fuchikoma_data[2];
extern s16 enemy_fuchikoma_key_code_holder_start[];
extern s16 enemy_fuchikoma_key_code_holder_patrol_start[];
extern s16 enemy_fuchikoma_key_code_holder_patrol_scan[];
extern s16 enemy_fuchikoma_key_code_holder_aim[];
extern s16 enemy_fuchikoma_key_code_holder_fire_start[];
extern s16 enemy_fuchikoma_key_code_holder_fire_burst[];
extern s16 enemy_fuchikoma_key_code_holder_fire_loop[];
extern s16 *keyholder_script[];
extern s16 *D_80116F4C;
extern ScriptCallEntry D_80116F50[];
extern s16 fuchikoma_burst_offsets[];
extern StateEntry D_80116F9C[];
extern s16 snd_wave_offset_table[];
extern s32 smg_soldier_asset[];
extern ModelBlockRef d_80116FBC[];
extern ModelBlockRef d_80116FD4[];
extern ModelBlockRef d_80116FE4[];
extern ModelBlockRange d_80116FF4[];
extern ModelBlockRange d_80117004[];
extern ModelBlock d_80117014;
extern u8 *msub_file_table[];
extern ScanEntry d_80117040;
extern SoundVolume smg_soldier_sounds[];
extern s16 smg_soldier_anim_idle[];
extern s16 smg_soldier_anim_idle_alt[];
extern s16 smg_soldier_anim_walk_start[];
extern s16 smg_soldier_anim_walk[];
extern s16 smg_soldier_anim_run_start[];
extern s16 smg_soldier_anim_run[];
extern s16 smg_soldier_anim_aim[];
extern s16 smg_soldier_anim_hold[];
extern s16 smg_soldier_anim_hit[];
extern s16 *smg_soldier_data[9];
extern s16 smg_soldier_idle[];
extern s16 smg_soldier_idle_pause[];
extern s16 smg_soldier_idle_cycle[];
extern s16 smg_soldier_patrol[];
extern s16 smg_soldier_patrol_cycle[];
extern s16 smg_soldier_patrol_wait[];
extern s16 smg_soldier_hold[];
extern s16 smg_soldier_hold_pause[];
extern s16 smg_soldier_hold_cycle[];
extern s16 smg_soldier_walk[];
extern s16 smg_soldier_walk_step[];
extern s16 smg_soldier_walk_cycle[];
extern s16 smg_soldier_walk_pause[];
extern s16 smg_soldier_walk_pause_cycle[];
extern s16 *smg_soldier_jump_table[];
extern s16 *smg_soldier_script[];
extern StateEntry smg_soldier_states[];
extern s32 rocket_fuchikoma_asset[];
extern ModelBlockRef d_801173E4[];
extern ModelBlockRef d_801173FC[];
extern ModelBlockRef d_8011740C[];
extern ModelBlock d_8011741C;
extern u8 *d_80117440[];
extern ScanEntry d_80117448;
extern SoundVolume rocket_fuchikoma_sounds[];
extern s16 rocket_fuchikoma_anim_idle[];
extern s16 rocket_fuchikoma_anim_fly[];
extern s16 rocket_fuchikoma_anim_detonate[];
extern s16 rocket_fuchikoma_anim_detonate_hold[];
extern s16 *rocket_fuchikoma_data[];
extern s16 rocket_fuchikoma_idle[];
extern s16 rocket_fuchikoma_reset[];
extern s16 rocket_fuchikoma_settle[];
extern s16 rocket_fuchikoma_ready[];
extern s16 rocket_fuchikoma_aim_start[];
extern s16 grenade_fuchikoma_seek[];
extern s16 rocket_fuchikoma_approach[];
extern s16 grenade_fuchikoma_track[];
extern s16 rocket_fuchikoma_close_in[];
extern s16 rocket_fuchikoma_brake[];
extern s16 grenade_fuchikoma_wait_stop[];
extern s16 rocket_fuchikoma_fire_wait[];
extern s16 rocket_fuchikoma_fire_start[];
extern s16 grenade_fuchikoma_detonate_wait[];
extern s16 rocket_fuchikoma_reposition[];
extern s16 rocket_fuchikoma_reposition_face[];
extern s16 *rocket_fuchikoma_jump_table[];
extern s16 *rocket_fuchikoma_script_pos[];
extern ScriptCallEntry script_call_table[];
extern s16 spawn_offset_x_table[];
extern s16 spawn_offset_y_table[];
extern s16 spawn_offset_z_table[];
extern StateEntry rocket_fuchikoma_state_table[];
extern s32 helicopter_asset_slot[3];
extern ModelBlockRef d_801176C4[];
extern ModelBlockRef d_801176E4[];
extern ModelBlockRef d_801176FC[];
extern ModelBlock d_8011770C;
extern u8 *d_80117730[];
extern ScanEntry helicopter_scan_entry;
extern s16 helicopter_script[];
extern u32 helicopter_data;
extern GunSetup shot_twin_desc;
extern FxRecordParams ripple_fx_params;
extern FxRecordParams fx_send_rec34_params_a;
extern FxRecordParams fx_send_rec34_params_b;
extern RecTemplate fx_send_template_a;
extern RecTemplate fx_send_template_b;
extern s16 helicopter_idle[];
extern s16 helicopter_pick_state[];
extern s16 helicopter_patrol[];
extern s16 helicopter_patrol_far[];
extern s16 helicopter_spin[];
extern s16 helicopter_aim[];
extern s16 helicopter_approach[];
extern s16 helicopter_cooldown[];
extern s16 helicopter_cooling[];
extern s16 helicopter_cooldown_end[];
extern s16 *helicopter_label_table[];
extern s16 *helicopter_script_entry;
extern ScriptCallEntry d_801178BC[];
extern StateEntry helicopter_slot_table[];
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *enemy_msgs_files[];
extern ScanEntry enemy_msgs_entry;
extern s32 place_asset[];
extern ScanEntry enemy_ctl1_entry;
extern LightData data_base_area;
extern VECTOR sound_slot_points[];
extern s32 enemy_dor1_asset[];
extern ScanEntry enemy_dor1_entry;
extern s32 giant_robot_asset[];
extern ModelBlockRef D_80117A50[];
extern ModelBlockRef D_80117A70[];
extern ModelBlockRef D_80117A88[];
extern ModelBlockRange D_80117AA0[];
extern ModelBlockRange D_80117AE0;
extern ModelBlock D_80117AE8;
extern u8 *D_80117B0C[];
extern ScanEntry enemy_bos1_entry;
extern SoundVolume D_80117B30[];
extern s16 giant_robot_m1_boss_anim_stand[];
extern s16 giant_robot_m1_boss_anim_walk_start[];
extern s16 giant_robot_m1_boss_anim_walk[];
extern s16 giant_robot_m1_boss_anim_walk_stop[];
extern s16 giant_robot_m1_boss_anim_idle[];
extern s16 giant_robot_m1_boss_anim_idle_hold[];
extern s16 giant_robot_m1_boss_anim_settle[];
extern s16 giant_robot_m1_boss_anim_dormant[];
extern s16 giant_robot_m1_boss_anim_rise[];
extern s16 giant_robot_m1_boss_anim_charge_ramp[];
extern s16 giant_robot_m1_boss_anim_charge_hold[];
extern s16 giant_robot_m1_boss_anim_release[];
extern s16 giant_robot_m1_boss_anim_release_hold[];
extern s16 giant_robot_m1_boss_anim_return[];
extern s16 *giant_robot_data[14];
extern GunSetup giant_robot_side_shot_setup;
extern s32 giant_robot_damage_scale;
extern ScriptCallEntry giant_robot_call_table[42];
extern s16 giant_robot_m1_boss_intro[];
extern s16 giant_robot_m1_boss_intro_wait[];
extern s16 giant_robot_m1_boss_intro_engage[];
extern s16 giant_robot_m1_boss_idle_enter[];
extern s16 giant_robot_m1_boss_idle[];
extern s16 giant_robot_m1_boss_idle_wait[];
extern s16 giant_robot_m1_boss_attack_choice[];
extern s16 giant_robot_m1_boss_sweep_pos[];
extern s16 giant_robot_m1_boss_fire_burst[];
extern s16 giant_robot_m1_boss_fire_loop[];
extern s16 giant_robot_m1_boss_sweep_neg[];
extern s16 giant_robot_m1_boss_sweep_neg_burst[];
extern s16 giant_robot_m1_boss_sweep_neg_burst_loop[];
extern s16 giant_robot_m1_boss_sweep_pos_again[];
extern s16 giant_robot_m1_boss_sweep_pos_again_burst[];
extern s16 giant_robot_m1_boss_sweep_pos_again_burst_loop[];
extern s16 giant_robot_m1_boss_sweep_neg_again[];
extern s16 giant_robot_m1_boss_sweep_neg_again_burst[];
extern s16 giant_robot_m1_boss_sweep_neg_again_burst_loop[];
extern s16 giant_robot_m1_boss_sweep_pos_long[];
extern s16 giant_robot_m1_boss_sweep_pos_long_burst[];
extern s16 giant_robot_m1_boss_sweep_pos_long_burst_loop[];
extern s16 giant_robot_m1_boss_sweep_neg_short[];
extern s16 giant_robot_m1_boss_sweep_neg_short_burst[];
extern s16 giant_robot_m1_boss_sweep_neg_short_burst_loop[];
extern s16 giant_robot_m1_boss_sweep_stop[];
extern s16 giant_robot_m1_boss_sweep_done[];
extern s16 giant_robot_m1_boss_wait_done[];
extern s16 giant_robot_m1_boss_sweep_return[];
extern s16 giant_robot_m1_boss_barrage_enter[];
extern s16 giant_robot_m1_boss_barrage_start[];
extern s16 giant_robot_m1_boss_barrage_charge[];
extern s16 giant_robot_m1_boss_barrage_release[];
extern s16 giant_robot_m1_boss_barrage_sway[];
extern s16 giant_robot_m1_boss_barrage_hold[];
extern s16 giant_robot_m1_boss_barrage_hold_wait[];
extern s16 giant_robot_m1_boss_barrage_end[];
extern s16 giant_robot_m1_boss_barrage_reset[];
extern s16 giant_robot_m1_boss_barrage_cooldown[];
extern s16 giant_robot_m1_boss_retreat[];
extern s16 giant_robot_m1_boss_retreat_wait[];
extern s16 giant_robot_m1_boss_retreat_stop[];
extern s16 giant_robot_m1_boss_retreat_stop_wait[];
extern s16 giant_robot_m1_boss_retreat_walk[];
extern s16 giant_robot_m1_boss_retreat_end[];
extern s16 giant_robot_m1_boss_pause_resume[];
extern s16 giant_robot_m1_boss_halt_wait[];
extern s16 giant_robot_m1_boss_halt[];
extern s16 giant_robot_m1_boss_pause_clear_wait[];
extern s16 giant_robot_m1_boss_pause_clear[];
extern s16 giant_robot_m1_boss_fade_wait[];
extern s16 giant_robot_m1_boss_side_fx_start[];
extern s16 giant_robot_m1_boss_side_fx[];
extern s16 giant_robot_m1_boss_side_fx_return[];
extern s16 giant_robot_m1_boss_pause_retreat_enter[];
extern s16 giant_robot_m1_boss_pause_then_retreat[];
extern s16 giant_robot_m1_boss_pause[];
extern s16 giant_robot_m1_boss_pause_end[];
extern s16 giant_robot_m1_boss_pause_return[];
extern s16 giant_robot_m1_boss_fx_retreat_enter[];
extern s16 giant_robot_m1_boss_fx_then_retreat[];
extern s16 giant_robot_m1_boss_fx_pause[];
extern s16 giant_robot_m1_boss_pause_then_resume[];
extern s16 giant_robot_m1_boss_resume_return[];
extern s16 giant_robot_m1_boss_wobble_enter[];
extern s16 giant_robot_m1_boss_wobble[];
extern s16 giant_robot_m1_boss_wobble_neg[];
extern s16 giant_robot_m1_boss_wobble_pos[];
extern s16 giant_robot_m1_boss_wobble_end[];
extern s16 giant_robot_m1_boss_side_fx_enter[];
extern s16 giant_robot_m1_boss_side_fx_then_next[];
extern s16 giant_robot_m1_boss_next_action[];
extern s16 giant_robot_m1_boss_next_return[];
extern s16 giant_robot_m1_boss_turn_enter[];
extern s16 giant_robot_m1_boss_turn_check[];
extern s16 giant_robot_m1_boss_turn_choice[];
extern s16 giant_robot_m1_boss_pick_idle_or_attack[];
extern s16 giant_robot_m1_boss_return_after_pick[];
extern s16 giant_robot_m1_boss_turn_pick_enter[];
extern s16 giant_robot_m1_boss_turn_pick[];
extern s16 giant_robot_m1_boss_pick_turn[];
extern s16 giant_robot_m1_boss_return_after_turn[];
extern s16 giant_robot_m1_boss_engage_barrage[];
extern s16 giant_robot_m1_boss_pick_retreat[];
extern s16 giant_robot_m1_boss_pick_by_distance[];
extern s16 *giant_robot_link_data[];
extern s16 *D_80118570;
extern StateEntry D_80118574[];
extern s16 giant_robot_hit_factors[];
extern s16 giant_robot_sound_data_a[];
extern s16 giant_robot_sound_data_b[];
extern s32 giant_robot_sound_handle_a;
extern s32 giant_robot_sound_handle_b;
extern s16 fade_colour_y_from[][2];
extern s16 fade_colour_x_from[][2];
extern Keyframe shot_burst_keys[];
extern s16 obj_target_pchr_table[];
extern s32 obj_target_index;
extern s32 giant_robot_on_flag;
extern Keyframe giant_robot_sound_keys_start[3];
extern Keyframe giant_robot_sound_keys_end[5];
extern RecTemplate fade_red_fx_template;
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern u16 d_8011876C[];
extern u16 rcossin_tbl[];
extern u32 sincos_deg90[];
extern u32 view_sincos[];
extern u32 sincos_deg270[];
extern u32 rocket_fuchikoma_asset_s10[];
extern u32 rocket_fuchikoma_jump_table_s10[];
extern s32 vblank_task_handle;
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_8011D310[];
extern u16 d_8011D324[];
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
extern u32 D_8011E470[];
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
extern u32 D_8011EA90;
extern u16 texture_image[];
extern u16 stage_image_width;
extern u16 stage_image_height;
extern u32 stage_image_pixels[];
extern s32 heap_top;
extern s32 heap2_top;
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
extern s32 key_codes_acquired;
extern s32 key_codes_complete_flag;
extern s32 stage_exit_flag;
extern s32 warehouse_hint_timer;
extern s32 ambient_sound_timer;
extern s32 D_8011FF00;
extern s32 value_queue_index;
extern s32 giant_robot_systems_active;
extern s32 giant_robot_aim_result;
extern s32 giant_robot_aim_x;
extern s32 giant_robot_aim_y;
extern s32 giant_robot_aim_z;
extern s32 giant_robot_fx_timer;
extern s32 giant_robot_fx_active;
extern Object *giant_robot_fx_owner;
extern s32 fade_amount;
extern s32 fade_dir;
extern Next800C5620 *fade_red_obj;
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
extern u32 D_8011FFE8;
extern s32 ring32_index;
extern s32 scene_model_count;
extern s32 cyl_tex_table;
extern s32 d_8011FFF8;
extern s32 cyl_scale;

ScanItem D_80116C60[8] = {
    {&keyholder_scan_entry, str_enemy_arka_data},
    {&d_80117040, str_enemy_msub_data},
    {&d_80117448, str_enemy_mth1_data},
    {&helicopter_scan_entry, str_enemy_ohel_data},
    {&enemy_msgs_entry, str_enemy_msgs_data},
    {&enemy_dor1_entry, str_enemy_dor1_data},
    {&enemy_ctl1_entry, str_enemy_ctl1_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116CA0 = {str_s01_stage, str_bay_cnf_bcf, str_bay_apdea3, str_bay_joy_bin, str_s01_dat_fac, str_s01_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0x400, D_80116C60};

AreaEntry d_80116CC8 = {str_s01_miss, str_m11_cnf_bcf, NULL, str_m01_joy_bin, str_m01_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

ScanItem D_80116CF0[3] = {
    {&enemy_bos1_entry, str_enemy_bos1_data},
    {&enemy_msgs_entry, str_enemy_msgs_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116D08 = {str_s01_boss, str_b11_cnf_bcf, str_b11_apdea3, str_b01_joy_bin, str_b01_dat_fac, str_b01_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, D_80116CF0};

#include "../stage/data/area_entry_table.c"

#include "../stage/data/debug_name_buf.c"

s32 keyholder_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_80116E08[3] = {
    {(s32)file_arka_ch0_clt, 0, 0},
    {(s32)file_arka_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80116E20[2] = {
    {(s32)file_arka_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_80116E30[2] = {
    {(s32)file_arka_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock D_80116E40 = {(s32)D_80116E08, (s32)D_80116E30, (s32)D_80116E20, 0, 0, 0, 0, 0, 0};

u8 *D_80116E64[2] = {
    file_arka_ch0_cb4, NULL,
};

ScanEntry keyholder_scan_entry = {{0, (s32)keyholder_fuchikoma_spawn}, keyholder_asset, (s32)&D_80116E40, (s32)D_80116E64, 0};

struct EnemyFuchikomaKeyCodeHolderAnims {
    s16 idle[4];
    s16 walk[26];
    s16 *table[2];
} enemy_fuchikoma_key_code_holder_anims = {
    /* idle */ {
        STEP(8, 12),
        GOTO(ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_ANIM_IDLE),
    },
    /* walk */ {
        STEP(3, 3),
        STEP(3, 4),
        STEP(3, 5),
        STEP(3, 6),
        SET_F8(15),
        STEP(3, 7),
        STEP(3, 8),
        STEP(3, 9),
        STEP(3, 10),
        STEP(3, 1),
        SET_F8(15),
        STEP(3, 2),
        GOTO(ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_ANIM_WALK),
    },
    /* table */ {
        enemy_fuchikoma_key_code_holder_anims.idle, enemy_fuchikoma_key_code_holder_anims.walk,
    },
};

struct EnemyFuchikomaKeyCodeHolderScripts {
    s16 start[2];
    s16 patrol_start[6];
    s16 patrol_scan[10];
    s16 aim[16];
    s16 fire_start[8];
    s16 fire_burst[2];
    s16 fire_loop[8];
    s16 *table[7];
    s16 *D_80116F4C;
} enemy_fuchikoma_key_code_holder_scripts = {
    /* start */ {
        JUMP(ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_PATROL_START),
    },
    /* patrol_start */ {
        NEXT_STATE(KEYHOLDER_FUCHIKOMA_STATE_ALERT),
        SET_COUNTER(60),
        KEYHOLDER_FUCHIKOMA_AIM_JITTER_PLACEMENT,
    },
    /* patrol_scan */ {
        WAIT(1),
        KEYHOLDER_FUCHIKOMA_JUMP_IF_PLAYER_IN_RADIUS, 2400, 3000, ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_AIM,
        LOOP(ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_PATROL_SCAN),
        JUMP(ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_PATROL_START),
    },
    /* aim */ {
        WAIT(1),
        KEYHOLDER_FUCHIKOMA_AIM_AT_PLAYER,
        KEYHOLDER_FUCHIKOMA_JUMP_IF_OUTSIDE, 3000, ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_PATROL_START,
        WAIT(1),
        KEYHOLDER_FUCHIKOMA_JUMP_BY_PLAYER_VIEW, 2400, 128, ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_FIRE_START, ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_AIM,
        JUMP(ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_PATROL_START),
    },
    /* fire_start */ {
        WAIT(1),
        KEYHOLDER_FUCHIKOMA_JUMP_NEAR_CORNER, 1024, ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_FIRE_BURST,
        JUMP(ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_AIM),
    },
    /* fire_burst */ {
        KEYHOLDER_FUCHIKOMA_SET_SELECTOR, 1,
    },
    /* fire_loop */ {
        WAIT(1),
        KEYHOLDER_FUCHIKOMA_AIM_AT_PLAYER,
        KEYHOLDER_FUCHIKOMA_JUMP_TABLE_MATCH, 0, ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_AIM,
        JUMP(ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_FIRE_LOOP),
    },
    /* table */ {
        enemy_fuchikoma_key_code_holder_scripts.start, enemy_fuchikoma_key_code_holder_scripts.patrol_start, enemy_fuchikoma_key_code_holder_scripts.patrol_scan, enemy_fuchikoma_key_code_holder_scripts.aim, enemy_fuchikoma_key_code_holder_scripts.fire_start, enemy_fuchikoma_key_code_holder_scripts.fire_burst,
        enemy_fuchikoma_key_code_holder_scripts.fire_loop,
    },
    /* D_80116F4C */ enemy_fuchikoma_key_code_holder_scripts.start,
};

ScriptCallEntry D_80116F50[9] = {
    {NULL, 0},
    {script_jump_near_corner, 0},
    {obj_aim_jitter_placement, 0},
    {obj_aim_at_player, 0},
    {obj_script_jump_if_outside, 0},
    {script_jump_if_player_in_radius, 0},
    {script_jump_by_player_view, 0},
    {obj_script_set_selector, 0},
    {script_jump_table_match, 0},
};

s16 fuchikoma_burst_offsets[2] = {
    -0x23, 0x23,
};

StateEntry D_80116F9C[2] = {
    {0, ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_ANIM_IDLE, 0},
    {(u32)enemy_alert_update, ENEMY_FUCHIKOMA_KEY_CODE_HOLDER_ANIM_WALK, 0},
};

s16 snd_wave_offset_table[2] = {
    -0x23, 0x23,
};

#include "../stage/data/smg_soldier_asset.c"

ModelBlockRef d_80116FBC[3] = {
    {(s32)file_msub_ch0_clt, 0, 0},
    {(s32)file_msub_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef d_80116FD4[2] = {
    {(s32)file_msub_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef d_80116FE4[2] = {
    {(s32)file_msub_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange d_80116FF4[2] = {
    {0, 0x64, 0x1666, 0}, {-1, 0, 0, 0},
};

ModelBlockRange d_80117004[2] = {
    {0, 0, 0x400, 0x64}, {-1, 0, 0, 0},
};

ModelBlock d_80117014 = {(s32)d_80116FBC, (s32)d_80116FE4, (s32)d_80116FD4, (s32)d_80117004, 0, 0, (s32)d_80116FF4, 0, 0};

#include "../stage/data/msub_file_table.c"

#include "../stage/data/smg_soldier_sounds.c"

#include "../stage/data/rocket_fuchikoma_asset.c"

#include "../stage/data/script_call_table.c"

#include "../stage/data/rocket_fuchikoma_state_table.c"

#include "../stage/data/helicopter_asset_slot.c"

#include "../stage/data/d_801176C4.c"

#include "../stage/data/helicopter_scan_entry.c"

#include "../stage/data/shot_twin_desc.c"

#include "../stage/data/fx_send_rec34_params_b.c"

#include "../stage/data/helicopter_scripts.c"

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

#include "../stage/data/enemy_msgs_files.c"

#include "../stage/data/enemy_msgs_entry.c"

#include "../stage/data/place_asset.c"

ScanEntry enemy_ctl1_entry = {{(s32)func_800BF598, (s32)stage_init_pursue}, place_asset, 0, 0, 0};

LightData data_base_area = {1, {{0, -0x140, -0x380, 0, -0x1400}}};

VECTOR sound_slot_points[4] = {
    {-0x2580, 0, -0x300C, 0}, {0x2EE0, 0, -0x300C, 0}, {-0x1F40, 0, -0x2FDA, 0}, {-0x1F40, 0, 0x2EE0, 0},
};

s32 enemy_dor1_asset[3] = {
    -1, -1, -1,
};

ScanEntry enemy_dor1_entry = {{(s32)sound_zones_init, (s32)key_code_exit_doors_spawn}, enemy_dor1_asset, 0, 0, 0};

s32 giant_robot_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_80117A50[4] = {
    {(s32)file_bos1_ch0_clt, 0, 0},
    {(s32)file_bos1_tp0_clt, 0, 0},
    {(s32)file_bos1_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80117A70[3] = {
    {(s32)file_bos1_tp0_xs3, 1, 0},
    {(s32)file_bos1_tp1_xs3, 2, 0},
    {0, 0, 0},
};

ModelBlockRef D_80117A88[3] = {
    {(s32)file_bos1_ch0_vx1, 0, 0},
    {(s32)file_bos1_ch1_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_80117AA0[8] = {
    {0xB7, 0xB8, 0x2000, 0}, {0xBA, 0xBB, 0x2000, 0}, {0xC1, 0xC4, 0x1000, 0}, {0xC5, 0xC6, 0x2000, 0},
    {0xD1, 0xD1, 0x2000, 0}, {0xD2, 0xD4, 0x2000, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0},
};

ModelBlockRange D_80117AE0 = {-1, -1, -1, 0};

ModelBlock D_80117AE8 = {(s32)D_80117A50, (s32)D_80117A88, (s32)D_80117A70, 0, (s32)D_80117AA0, (s32)&D_80117AE0, 0, 0, 0};

u8 *D_80117B0C[3] = {
    file_bos1_ch0_cb4, file_bos1_ch1_cb4, NULL,
};

ScanEntry enemy_bos1_entry = {{(s32)giant_robot_sounds_start, (s32)giant_robot_spawn}, giant_robot_asset, (s32)&D_80117AE8, (s32)D_80117B0C, 0};

SoundVolume D_80117B30[2] = {
    {0x5000, 0x1000}, {0x5001, 0x1000},
};

struct GiantRobotM1BossAnims {
    s16 stand[6];
    s16 walk_start[6];
    s16 walk[56];
    s16 walk_stop[6];
    s16 idle[104];
    s16 idle_hold[4];
    s16 settle[6];
    s16 dormant[4];
    s16 rise[66];
    s16 charge_ramp[26];
    s16 charge_hold[4];
    s16 release[16];
    s16 release_hold[4];
    s16 anim_return[16];
    s16 *table[14];
} giant_robot_m1_boss_anims = {
    /* stand */ {
        STEP(4, 31),
        STEP(4, 31),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_STAND),
    },
    /* walk_start */ {
        STEP(4, 31),
        STEP(32, 38),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_WALK),
    },
    /* walk */ {
        STEP(1, 38),
        STEP(1, 39),
        STEP(1, 40),
        STEP(1, 41),
        STEP(1, 42),
        STEP(1, 43),
        STEP(1, 44),
        SOUND(1),
        STEP(1, 45),
        STEP(1, 46),
        STEP(1, 47),
        STEP(1, 48),
        STEP(1, 49),
        STEP(1, 50),
        STEP(1, 51),
        STEP(1, 52),
        STEP(1, 53),
        STEP(1, 54),
        STEP(1, 55),
        STEP(1, 56),
        STEP(1, 32),
        SOUND(1),
        STEP(1, 33),
        STEP(1, 34),
        STEP(1, 35),
        STEP(1, 36),
        STEP(1, 37),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_WALK),
    },
    /* walk_stop */ {
        STEP(1, 38),
        STEP(32, 31),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_STAND),
    },
    /* idle */ {
        STEP(2, 64),
        STEP(2, 65),
        STEP(2, 66),
        STEP(2, 67),
        STEP(2, 68),
        STEP(2, 69),
        STEP(2, 70),
        STEP(2, 71),
        STEP(2, 72),
        STEP(2, 73),
        STEP(2, 74),
        STEP(2, 75),
        STEP(2, 76),
        STEP(2, 77),
        STEP(2, 78),
        STEP(2, 79),
        STEP(2, 80),
        STEP(2, 81),
        STEP(2, 82),
        STEP(2, 83),
        STEP(2, 84),
        STEP(2, 85),
        STEP(2, 86),
        STEP(2, 87),
        STEP(2, 88),
        STEP(2, 89),
        STEP(2, 90),
        STEP(2, 91),
        STEP(2, 92),
        STEP(2, 93),
        STEP(2, 94),
        STEP(2, 95),
        STEP(2, 96),
        STEP(2, 97),
        STEP(2, 98),
        STEP(2, 99),
        STEP(2, 100),
        STEP(2, 101),
        STEP(2, 102),
        STEP(2, 103),
        STEP(2, 104),
        STEP(2, 105),
        STEP(2, 106),
        STEP(2, 107),
        STEP(2, 108),
        STEP(2, 109),
        STEP(2, 110),
        STEP(2, 111),
        STEP(2, 112),
        STEP(2, 113),
        STEP(2, 114),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_IDLE_HOLD),
    },
    /* idle_hold */ {
        STEP(2, 114),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_IDLE_HOLD),
    },
    /* settle */ {
        STEP(32, 114),
        STEP(32, 31),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_STAND),
    },
    /* dormant */ {
        STEP(4, 1),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_DORMANT),
    },
    /* rise */ {
        SOUND(0),
        STEP(4, 1),
        STEP(4, 2),
        STEP(4, 3),
        STEP(4, 4),
        STEP(4, 5),
        STEP(4, 6),
        STEP(4, 7),
        STEP(4, 8),
        STEP(4, 9),
        STEP(4, 10),
        STEP(4, 11),
        STEP(4, 12),
        STEP(4, 13),
        STEP(4, 14),
        STEP(4, 15),
        STEP(4, 16),
        STEP(4, 17),
        STEP(4, 18),
        STEP(4, 19),
        STEP(4, 20),
        STEP(4, 21),
        STEP(4, 22),
        STEP(4, 23),
        STEP(4, 24),
        STEP(4, 25),
        STEP(4, 26),
        STEP(4, 27),
        STEP(4, 28),
        STEP(4, 29),
        STEP(4, 30),
        STEP(4, 31),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_STAND),
    },
    /* charge_ramp */ {
        STEP(6, 129),
        STEP(6, 130),
        STEP(6, 131),
        STEP(6, 132),
        STEP(6, 133),
        STEP(6, 134),
        STEP(6, 135),
        STEP(6, 136),
        STEP(6, 137),
        STEP(6, 138),
        STEP(6, 139),
        STEP(6, 140),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_CHARGE_HOLD),
    },
    /* charge_hold */ {
        STEP(6, 140),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_CHARGE_HOLD),
    },
    /* release */ {
        STEP(2, 140),
        STEP(2, 141),
        STEP(2, 142),
        STEP(2, 143),
        STEP(2, 144),
        STEP(2, 145),
        STEP(2, 146),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_RELEASE_HOLD),
    },
    /* release_hold */ {
        STEP(2, 147),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_RELEASE_HOLD),
    },
    /* anim_return */ {
        STEP(6, 148),
        STEP(6, 149),
        STEP(6, 150),
        STEP(6, 151),
        STEP(6, 152),
        STEP(6, 153),
        STEP(6, 154),
        GOTO(GIANT_ROBOT_M1_BOSS_ANIM_STAND),
    },
    /* table */ {
        giant_robot_m1_boss_anims.stand, giant_robot_m1_boss_anims.walk_start, giant_robot_m1_boss_anims.walk, giant_robot_m1_boss_anims.walk_stop, giant_robot_m1_boss_anims.idle, giant_robot_m1_boss_anims.idle_hold,
        giant_robot_m1_boss_anims.settle, giant_robot_m1_boss_anims.dormant, giant_robot_m1_boss_anims.rise, giant_robot_m1_boss_anims.charge_ramp, giant_robot_m1_boss_anims.charge_hold, giant_robot_m1_boss_anims.release,
        giant_robot_m1_boss_anims.release_hold, giant_robot_m1_boss_anims.anim_return,
    },
};

GunSetup giant_robot_side_shot_setup = {0xE000, 0x32000, 0x800, 0xC, 0, 0xC, 0x78, 0x12, 0x12, 0x2D, 7, 6, 0xF, 0x1E, 0x51};

s32 giant_robot_damage_scale = 0;

ScriptCallEntry giant_robot_call_table[42] = {
    {NULL, 0},
    {obj_script_skip_operand, 0},
    {func_800C02FC, 0},
    {obj_script_jump_if_far, 0},
    {script_turn_to_player_jump, 0},
    {script_case_match, 0},
    {obj_script_read_u16_var, 0},
    {script_op_set_vy, 0},
    {script_op_jump_if_vy_nonneg, 0},
    {script_value_queue_push, 0},
    {value_queue_pop, 0},
    {obj_script_set_var, 0},
    {obj_script_set_var_rand, 0},
    {obj_script_loop, 0},
    {obj_attack_player, 0},
    {obj_roll_random, 0},
    {obj_script_jump_if_roll_le, 0},
    {obj_script_jump_if_equal, 0},
    {script_set_enemy_var, 0},
    {obj_play_fade_sound, 0},
    {obj_sway_start, 0},
    {script_op_sway_reset, 0},
    {script_op_sound_loop_start, 0},
    {script_op_sound_loop_stop, 0},
    {script_op_flag_set, 0},
    {script_op_clear_flag, 0},
    {script_op_set_yaw_rate, 0},
    {obj_fire_shot, 0},
    {obj_loop_anim_start, 0},
    {script_op_state_stop, 0},
    {script_op_set_target, 0},
    {giant_robot_fx_start, 0},
    {giant_robot_fx_stop, 0},
    {giant_robot_side_fx, 0},
    {script_jump_if_below, 0},
    {script_counter_inc, 0},
    {script_jump_if_counter_eq, 0},
    {script_jump_if_counter_ge, 0},
    {script_set_flag, 0},
    {giant_robot_reset_scale, 0},
    {script_jump_if_player_low, 0},
    {script_jump_if_rand_le, 0},
};

struct GiantRobotM1BossScripts {
    s16 intro[22];
    s16 intro_wait[8];
    s16 intro_engage[8];
    s16 idle_enter[2];
    s16 idle[12];
    s16 idle_wait[8];
    s16 attack_choice[6];
    s16 sweep_pos[4];
    s16 fire_burst[4];
    s16 fire_loop[2];
    s16 sweep_neg[4];
    s16 sweep_neg_burst[4];
    s16 sweep_neg_burst_loop[2];
    s16 sweep_pos_again[4];
    s16 sweep_pos_again_burst[4];
    s16 sweep_pos_again_burst_loop[4];
    s16 sweep_neg_again[4];
    s16 sweep_neg_again_burst[4];
    s16 sweep_neg_again_burst_loop[2];
    s16 sweep_pos_long[4];
    s16 sweep_pos_long_burst[4];
    s16 sweep_pos_long_burst_loop[2];
    s16 sweep_neg_short[4];
    s16 sweep_neg_short_burst[4];
    s16 sweep_neg_short_burst_loop[4];
    s16 sweep_stop[4];
    s16 sweep_done[6];
    s16 wait_done[8];
    s16 sweep_return[2];
    s16 barrage_enter[2];
    s16 barrage_start[16];
    s16 barrage_charge[6];
    s16 barrage_release[8];
    s16 barrage_sway[10];
    s16 barrage_hold[6];
    s16 barrage_hold_wait[8];
    s16 barrage_end[4];
    s16 barrage_reset[4];
    s16 barrage_cooldown[8];
    s16 retreat[6];
    s16 retreat_wait[8];
    s16 retreat_stop[10];
    s16 retreat_stop_wait[8];
    s16 retreat_walk[6];
    s16 retreat_end[4];
    s16 pause_resume[6];
    s16 halt_wait[8];
    s16 halt[10];
    s16 pause_clear_wait[8];
    s16 pause_clear[4];
    s16 fade_wait[6];
    s16 side_fx_start[2];
    s16 side_fx[6];
    s16 side_fx_return[2];
    s16 pause_retreat_enter[2];
    s16 pause_then_retreat[4];
    s16 pause[2];
    s16 pause_end[4];
    s16 pause_return[2];
    s16 fx_retreat_enter[2];
    s16 fx_then_retreat[4];
    s16 fx_pause[4];
    s16 pause_then_resume[4];
    s16 resume_return[2];
    s16 wobble_enter[2];
    s16 wobble[6];
    s16 wobble_neg[62];
    s16 wobble_pos[62];
    s16 wobble_end[4];
    s16 side_fx_enter[2];
    s16 side_fx_then_next[4];
    s16 next_action[14];
    s16 next_return[2];
    s16 turn_enter[2];
    s16 turn_check[12];
    s16 turn_choice[12];
    s16 pick_idle_or_attack[10];
    s16 return_after_pick[2];
    s16 turn_pick_enter[2];
    s16 turn_pick[14];
    s16 pick_turn[16];
    s16 return_after_turn[2];
    s16 engage_barrage[4];
    s16 pick_retreat[4];
    s16 pick_by_distance[10];
    s16 *table[85];
    s16 *D_80118570;
} giant_robot_m1_boss_scripts = {
    /* intro */ {
        GIANT_ROBOT_SET_VAR, 0, 0,
        GIANT_ROBOT_SET_VAR, 1, 0,
        GIANT_ROBOT_SET_VAR, 2, 0,
        GIANT_ROBOT_READ_U16_VAR, 0,
        NEXT_STATE(GIANT_ROBOT_STATE_SWEEP_POS),
        WAIT(60),
        NEXT_STATE(GIANT_ROBOT_STATE_FIRE_BURST),
        GIANT_ROBOT_PLAY_FADE_SOUND, 0,
        JUMP(GIANT_ROBOT_M1_BOSS_INTRO_WAIT),
    },
    /* intro_wait */ {
        WAIT(1),
        GIANT_ROBOT_CASE_MATCH, -1, GIANT_ROBOT_M1_BOSS_INTRO_ENGAGE,
        JUMP(GIANT_ROBOT_M1_BOSS_INTRO_WAIT),
    },
    /* intro_engage */ {
        GIANT_ROBOT_SET_FLAG, 1,
        GIANT_ROBOT_RESET_SCALE,
        GIANT_ROBOT_SET_VAR, 1, 1,
        JUMP(GIANT_ROBOT_M1_BOSS_ENGAGE_BARRAGE),
    },
    /* idle_enter */ {
        JUMP(GIANT_ROBOT_M1_BOSS_IDLE),
    },
    /* idle */ {
        GIANT_ROBOT_SET_TARGET, 640,
        GIANT_ROBOT_READ_U16_VAR, 0,
        WANDER(0),
        SET_SPEED(0),
        NEXT_STATE(GIANT_ROBOT_STATE_IDLE),
        GIANT_ROBOT_LOOP_ANIM_START,
    },
    /* idle_wait */ {
        WAIT(1),
        GIANT_ROBOT_CASE_MATCH, -1, GIANT_ROBOT_M1_BOSS_ATTACK_CHOICE,
        JUMP(GIANT_ROBOT_M1_BOSS_IDLE_WAIT),
    },
    /* attack_choice */ {
        GIANT_ROBOT_JUMP_IF_RAND_LE, 2048, GIANT_ROBOT_M1_BOSS_SWEEP_POS,
        JUMP(GIANT_ROBOT_M1_BOSS_SWEEP_NEG_AGAIN),
    },
    /* sweep_pos */ {
        SET_COUNTER(8),
        GIANT_ROBOT_SET_YAW_RATE, 6,
    },
    /* fire_burst */ {
        GIANT_ROBOT_FIRE_SHOT,
        WAIT(8),
    },
    /* fire_loop */ {
        LOOP(GIANT_ROBOT_M1_BOSS_FIRE_BURST),
    },
    /* sweep_neg */ {
        SET_COUNTER(16),
        GIANT_ROBOT_SET_YAW_RATE, -6,
    },
    /* sweep_neg_burst */ {
        GIANT_ROBOT_FIRE_SHOT,
        WAIT(8),
    },
    /* sweep_neg_burst_loop */ {
        LOOP(GIANT_ROBOT_M1_BOSS_SWEEP_NEG_BURST),
    },
    /* sweep_pos_again */ {
        SET_COUNTER(8),
        GIANT_ROBOT_SET_YAW_RATE, 6,
    },
    /* sweep_pos_again_burst */ {
        GIANT_ROBOT_FIRE_SHOT,
        WAIT(8),
    },
    /* sweep_pos_again_burst_loop */ {
        LOOP(GIANT_ROBOT_M1_BOSS_SWEEP_POS_AGAIN_BURST),
        JUMP(GIANT_ROBOT_M1_BOSS_SWEEP_STOP),
    },
    /* sweep_neg_again */ {
        SET_COUNTER(8),
        GIANT_ROBOT_SET_YAW_RATE, -6,
    },
    /* sweep_neg_again_burst */ {
        GIANT_ROBOT_FIRE_SHOT,
        WAIT(8),
    },
    /* sweep_neg_again_burst_loop */ {
        LOOP(GIANT_ROBOT_M1_BOSS_SWEEP_NEG_AGAIN_BURST),
    },
    /* sweep_pos_long */ {
        SET_COUNTER(16),
        GIANT_ROBOT_SET_YAW_RATE, 6,
    },
    /* sweep_pos_long_burst */ {
        GIANT_ROBOT_FIRE_SHOT,
        WAIT(8),
    },
    /* sweep_pos_long_burst_loop */ {
        LOOP(GIANT_ROBOT_M1_BOSS_SWEEP_POS_LONG_BURST),
    },
    /* sweep_neg_short */ {
        SET_COUNTER(8),
        GIANT_ROBOT_SET_YAW_RATE, -6,
    },
    /* sweep_neg_short_burst */ {
        GIANT_ROBOT_FIRE_SHOT,
        WAIT(8),
    },
    /* sweep_neg_short_burst_loop */ {
        LOOP(GIANT_ROBOT_M1_BOSS_SWEEP_NEG_SHORT_BURST),
        JUMP(GIANT_ROBOT_M1_BOSS_SWEEP_STOP),
    },
    /* sweep_stop */ {
        GIANT_ROBOT_SET_YAW_RATE, 0,
        JUMP(GIANT_ROBOT_M1_BOSS_SWEEP_DONE),
    },
    /* sweep_done */ {
        GIANT_ROBOT_STATE_STOP,
        NEXT_STATE(GIANT_ROBOT_STATE_ATTACK_CHOICE),
        GIANT_ROBOT_SET_TARGET, -1,
    },
    /* wait_done */ {
        WAIT(1),
        GIANT_ROBOT_CASE_MATCH, -1, GIANT_ROBOT_M1_BOSS_SWEEP_RETURN,
        JUMP(GIANT_ROBOT_M1_BOSS_WAIT_DONE),
    },
    /* sweep_return */ {
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* barrage_enter */ {
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_START),
    },
    /* barrage_start */ {
        GIANT_ROBOT_SET_TARGET, 512,
        NEXT_STATE(GIANT_ROBOT_STATE_BARRAGE),
        GIANT_ROBOT_READ_U16_VAR, 0,
        WANDER(0),
        SET_SPEED(0),
        GIANT_ROBOT_SOUND_LOOP_START,
        GIANT_ROBOT_FLAG_SET,
        SET_COUNTER(64),
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_CHARGE),
    },
    /* barrage_charge */ {
        WAIT(1),
        LOOP(GIANT_ROBOT_M1_BOSS_BARRAGE_CHARGE),
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_RELEASE),
    },
    /* barrage_release */ {
        GIANT_ROBOT_CLEAR_FLAG,
        WAIT(64),
        GIANT_ROBOT_SWAY_START,
        NEXT_STATE(GIANT_ROBOT_STATE_BARRAGE_FIRE),
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_SWAY),
    },
    /* barrage_sway */ {
        WAIT(32),
        GIANT_ROBOT_ROLL_RANDOM,
        GIANT_ROBOT_SET_YAW_RATE, -16,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 2048, GIANT_ROBOT_M1_BOSS_BARRAGE_HOLD,
        GIANT_ROBOT_SET_YAW_RATE, 16,
    },
    /* barrage_hold */ {
        WAIT(256),
        GIANT_ROBOT_SET_YAW_RATE, 0,
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_HOLD_WAIT),
    },
    /* barrage_hold_wait */ {
        WAIT(1),
        GIANT_ROBOT_CASE_MATCH, -1, GIANT_ROBOT_M1_BOSS_BARRAGE_END,
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_HOLD_WAIT),
    },
    /* barrage_end */ {
        NEXT_STATE(GIANT_ROBOT_STATE_BARRAGE_SWEEP),
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_RESET),
    },
    /* barrage_reset */ {
        GIANT_ROBOT_SWAY_RESET,
        GIANT_ROBOT_SOUND_LOOP_STOP,
        SET_COUNTER(60),
    },
    /* barrage_cooldown */ {
        WAIT(1),
        LOOP(GIANT_ROBOT_M1_BOSS_BARRAGE_COOLDOWN),
        GIANT_ROBOT_SET_TARGET, -1,
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* retreat */ {
        GIANT_ROBOT_PLAY_FADE_SOUND, 1,
        GIANT_ROBOT_JUMP_IF_COUNTER_EQ, 0, 1, GIANT_ROBOT_M1_BOSS_RETREAT_END,
    },
    /* retreat_wait */ {
        WAIT(1),
        GIANT_ROBOT_CASE_MATCH, -1, GIANT_ROBOT_M1_BOSS_RETREAT_STOP,
        JUMP(GIANT_ROBOT_M1_BOSS_RETREAT_WAIT),
    },
    /* retreat_stop */ {
        GIANT_ROBOT_READ_U16_VAR, 0,
        WANDER(0),
        SET_SPEED(0),
        NEXT_STATE(GIANT_ROBOT_STATE_AWAIT_CYCLE),
        JUMP(GIANT_ROBOT_M1_BOSS_RETREAT_STOP_WAIT),
    },
    /* retreat_stop_wait */ {
        WAIT(1),
        GIANT_ROBOT_CASE_MATCH, -1, GIANT_ROBOT_M1_BOSS_RETREAT_WALK,
        JUMP(GIANT_ROBOT_M1_BOSS_RETREAT_STOP_WAIT),
    },
    /* retreat_walk */ {
        GIANT_ROBOT_READ_U16_VAR, 12,
        WANDER(0),
        SET_SPEED(6),
    },
    /* retreat_end */ {
        GIANT_ROBOT_SET_VAR, 0, 1,
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* pause_resume */ {
        GIANT_ROBOT_PLAY_FADE_SOUND, 0,
        GIANT_ROBOT_JUMP_IF_COUNTER_EQ, 0, 0, GIANT_ROBOT_M1_BOSS_PAUSE_CLEAR,
    },
    /* halt_wait */ {
        WAIT(1),
        GIANT_ROBOT_CASE_MATCH, -1, GIANT_ROBOT_M1_BOSS_HALT,
        JUMP(GIANT_ROBOT_M1_BOSS_HALT_WAIT),
    },
    /* halt */ {
        NEXT_STATE(GIANT_ROBOT_STATE_HALT),
        GIANT_ROBOT_READ_U16_VAR, 0,
        WANDER(0),
        SET_SPEED(0),
        JUMP(GIANT_ROBOT_M1_BOSS_PAUSE_CLEAR_WAIT),
    },
    /* pause_clear_wait */ {
        WAIT(1),
        GIANT_ROBOT_CASE_MATCH, -1, GIANT_ROBOT_M1_BOSS_PAUSE_CLEAR,
        JUMP(GIANT_ROBOT_M1_BOSS_PAUSE_CLEAR_WAIT),
    },
    /* pause_clear */ {
        GIANT_ROBOT_SET_VAR, 0, 0,
    },
    /* fade_wait */ {
        WAIT(1),
        GIANT_ROBOT_JUMP_IF_BELOW, 1, GIANT_ROBOT_M1_BOSS_FADE_WAIT,
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* side_fx_start */ {
        SET_COUNTER(2),
    },
    /* side_fx */ {
        GIANT_ROBOT_SIDE_FX,
        WAIT(64),
        LOOP(GIANT_ROBOT_M1_BOSS_SIDE_FX),
    },
    /* side_fx_return */ {
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* pause_retreat_enter */ {
        JUMP(GIANT_ROBOT_M1_BOSS_PAUSE_THEN_RETREAT),
    },
    /* pause_then_retreat */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 56,
        JUMP(GIANT_ROBOT_M1_BOSS_RETREAT),
    },
    /* pause */ {
        WAIT(180),
    },
    /* pause_end */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 58,
        JUMP(GIANT_ROBOT_M1_BOSS_PAUSE_RESUME),
    },
    /* pause_return */ {
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* fx_retreat_enter */ {
        JUMP(GIANT_ROBOT_M1_BOSS_FX_THEN_RETREAT),
    },
    /* fx_then_retreat */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 61,
        JUMP(GIANT_ROBOT_M1_BOSS_RETREAT),
    },
    /* fx_pause */ {
        GIANT_ROBOT_FX_START,
        WAIT(180),
        GIANT_ROBOT_FX_STOP,
    },
    /* pause_then_resume */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 63,
        JUMP(GIANT_ROBOT_M1_BOSS_PAUSE_RESUME),
    },
    /* resume_return */ {
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* wobble_enter */ {
        JUMP(GIANT_ROBOT_M1_BOSS_WOBBLE),
    },
    /* wobble */ {
        GIANT_ROBOT_FX_START,
        GIANT_ROBOT_JUMP_IF_RAND_LE, 2048, GIANT_ROBOT_M1_BOSS_WOBBLE_NEG,
        JUMP(GIANT_ROBOT_M1_BOSS_WOBBLE_POS),
    },
    /* wobble_neg */ {
        GIANT_ROBOT_SET_YAW_RATE, -2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, -4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, -8,
        WAIT(40),
        GIANT_ROBOT_SET_YAW_RATE, -4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, -2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, 2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, 4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, 8,
        WAIT(88),
        GIANT_ROBOT_SET_YAW_RATE, 4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, 2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, -2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, -4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, -8,
        WAIT(40),
        GIANT_ROBOT_SET_YAW_RATE, -4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, -2,
        WAIT(8),
        JUMP(GIANT_ROBOT_M1_BOSS_WOBBLE_END),
    },
    /* wobble_pos */ {
        GIANT_ROBOT_SET_YAW_RATE, 2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, 4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, 8,
        WAIT(40),
        GIANT_ROBOT_SET_YAW_RATE, 4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, 2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, -2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, -4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, -8,
        WAIT(88),
        GIANT_ROBOT_SET_YAW_RATE, -4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, -2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, 2,
        WAIT(8),
        GIANT_ROBOT_SET_YAW_RATE, 4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, 8,
        WAIT(40),
        GIANT_ROBOT_SET_YAW_RATE, 4,
        WAIT(4),
        GIANT_ROBOT_SET_YAW_RATE, 2,
        WAIT(8),
        JUMP(GIANT_ROBOT_M1_BOSS_WOBBLE_END),
    },
    /* wobble_end */ {
        GIANT_ROBOT_SET_YAW_RATE, 0,
        GIANT_ROBOT_FX_STOP,
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* side_fx_enter */ {
        JUMP(GIANT_ROBOT_M1_BOSS_SIDE_FX_THEN_NEXT),
    },
    /* side_fx_then_next */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 71,
        JUMP(GIANT_ROBOT_M1_BOSS_SIDE_FX_START),
    },
    /* next_action */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 72,
        GIANT_ROBOT_ROLL_RANDOM,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 1024, GIANT_ROBOT_M1_BOSS_FX_RETREAT_ENTER,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 2048, GIANT_ROBOT_M1_BOSS_PAUSE_RETREAT_ENTER,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 3072, GIANT_ROBOT_M1_BOSS_IDLE_ENTER,
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_ENTER),
    },
    /* next_return */ {
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* turn_enter */ {
        JUMP(GIANT_ROBOT_M1_BOSS_TURN_CHECK),
    },
    /* turn_check */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 75,
        GIANT_ROBOT_TURN_TO_PLAYER_JUMP, 682, GIANT_ROBOT_M1_BOSS_PICK_IDLE_OR_ATTACK,
        GIANT_ROBOT_ROLL_RANDOM,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 2048, GIANT_ROBOT_M1_BOSS_SIDE_FX_START,
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_ENTER),
    },
    /* turn_choice */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 77,
        GIANT_ROBOT_ROLL_RANDOM,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 2048, GIANT_ROBOT_M1_BOSS_WOBBLE_ENTER,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 3072, GIANT_ROBOT_M1_BOSS_BARRAGE_ENTER,
        JUMP(GIANT_ROBOT_M1_BOSS_FX_RETREAT_ENTER),
    },
    /* pick_idle_or_attack */ {
        GIANT_ROBOT_ROLL_RANDOM,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 512, GIANT_ROBOT_M1_BOSS_WOBBLE_ENTER,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 1024, GIANT_ROBOT_M1_BOSS_BARRAGE_ENTER,
        JUMP(GIANT_ROBOT_M1_BOSS_IDLE_ENTER),
    },
    /* return_after_pick */ {
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* turn_pick_enter */ {
        JUMP(GIANT_ROBOT_M1_BOSS_TURN_PICK),
    },
    /* turn_pick */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 80,
        GIANT_ROBOT_TURN_TO_PLAYER_JUMP, 682, GIANT_ROBOT_M1_BOSS_FX_RETREAT_ENTER,
        GIANT_ROBOT_ROLL_RANDOM,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 1365, GIANT_ROBOT_M1_BOSS_SIDE_FX_START,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 2730, GIANT_ROBOT_M1_BOSS_FX_RETREAT_ENTER,
        JUMP(GIANT_ROBOT_M1_BOSS_PAUSE_RETREAT_ENTER),
    },
    /* pick_turn */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 81,
        GIANT_ROBOT_ROLL_RANDOM,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 1024, GIANT_ROBOT_M1_BOSS_SIDE_FX_START,
        GIANT_ROBOT_TURN_TO_PLAYER_JUMP, 682, GIANT_ROBOT_M1_BOSS_IDLE_ENTER,
        GIANT_ROBOT_ROLL_RANDOM,
        GIANT_ROBOT_JUMP_IF_ROLL_LE, 1365, GIANT_ROBOT_M1_BOSS_SIDE_FX_START,
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_ENTER),
    },
    /* return_after_turn */ {
        GIANT_ROBOT_VALUE_QUEUE_POP,
    },
    /* engage_barrage */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 83,
        JUMP(GIANT_ROBOT_M1_BOSS_BARRAGE_ENTER),
    },
    /* pick_retreat */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 84,
        JUMP(GIANT_ROBOT_M1_BOSS_PAUSE_RETREAT_ENTER),
    },
    /* pick_by_distance */ {
        GIANT_ROBOT_VALUE_QUEUE_PUSH, 84,
        GIANT_ROBOT_JUMP_IF_PLAYER_LOW, GIANT_ROBOT_M1_BOSS_SIDE_FX_ENTER,
        GIANT_ROBOT_FUNC_800C02FC, 2500, GIANT_ROBOT_M1_BOSS_TURN_ENTER,
        JUMP(GIANT_ROBOT_M1_BOSS_TURN_PICK_ENTER),
    },
    /* table */ {
        giant_robot_m1_boss_scripts.intro, giant_robot_m1_boss_scripts.intro_wait, giant_robot_m1_boss_scripts.intro_engage, giant_robot_m1_boss_scripts.idle_enter, giant_robot_m1_boss_scripts.idle, giant_robot_m1_boss_scripts.idle_wait,
        giant_robot_m1_boss_scripts.attack_choice, giant_robot_m1_boss_scripts.sweep_pos, giant_robot_m1_boss_scripts.fire_burst, giant_robot_m1_boss_scripts.fire_loop, giant_robot_m1_boss_scripts.sweep_neg, giant_robot_m1_boss_scripts.sweep_neg_burst,
        giant_robot_m1_boss_scripts.sweep_neg_burst_loop, giant_robot_m1_boss_scripts.sweep_pos_again, giant_robot_m1_boss_scripts.sweep_pos_again_burst, giant_robot_m1_boss_scripts.sweep_pos_again_burst_loop, giant_robot_m1_boss_scripts.sweep_neg_again, giant_robot_m1_boss_scripts.sweep_neg_again_burst,
        giant_robot_m1_boss_scripts.sweep_neg_again_burst_loop, giant_robot_m1_boss_scripts.sweep_pos_long, giant_robot_m1_boss_scripts.sweep_pos_long_burst, giant_robot_m1_boss_scripts.sweep_pos_long_burst_loop, giant_robot_m1_boss_scripts.sweep_neg_short, giant_robot_m1_boss_scripts.sweep_neg_short_burst,
        giant_robot_m1_boss_scripts.sweep_neg_short_burst_loop, giant_robot_m1_boss_scripts.sweep_stop, giant_robot_m1_boss_scripts.sweep_done, giant_robot_m1_boss_scripts.wait_done, giant_robot_m1_boss_scripts.sweep_return, giant_robot_m1_boss_scripts.barrage_enter,
        giant_robot_m1_boss_scripts.barrage_start, giant_robot_m1_boss_scripts.barrage_charge, giant_robot_m1_boss_scripts.barrage_release, giant_robot_m1_boss_scripts.barrage_sway, giant_robot_m1_boss_scripts.barrage_hold, giant_robot_m1_boss_scripts.barrage_hold_wait,
        giant_robot_m1_boss_scripts.barrage_end, giant_robot_m1_boss_scripts.barrage_reset, giant_robot_m1_boss_scripts.barrage_cooldown, giant_robot_m1_boss_scripts.retreat, giant_robot_m1_boss_scripts.retreat_wait, giant_robot_m1_boss_scripts.retreat_stop,
        giant_robot_m1_boss_scripts.retreat_stop_wait, giant_robot_m1_boss_scripts.retreat_walk, giant_robot_m1_boss_scripts.retreat_end, giant_robot_m1_boss_scripts.pause_resume, giant_robot_m1_boss_scripts.halt_wait, giant_robot_m1_boss_scripts.halt,
        giant_robot_m1_boss_scripts.pause_clear_wait, giant_robot_m1_boss_scripts.pause_clear, giant_robot_m1_boss_scripts.fade_wait, giant_robot_m1_boss_scripts.side_fx_start, giant_robot_m1_boss_scripts.side_fx, giant_robot_m1_boss_scripts.side_fx_return,
        giant_robot_m1_boss_scripts.pause_retreat_enter, giant_robot_m1_boss_scripts.pause_then_retreat, giant_robot_m1_boss_scripts.pause, giant_robot_m1_boss_scripts.pause_end, giant_robot_m1_boss_scripts.pause_return, giant_robot_m1_boss_scripts.fx_retreat_enter,
        giant_robot_m1_boss_scripts.fx_then_retreat, giant_robot_m1_boss_scripts.fx_pause, giant_robot_m1_boss_scripts.pause_then_resume, giant_robot_m1_boss_scripts.resume_return, giant_robot_m1_boss_scripts.wobble_enter, giant_robot_m1_boss_scripts.wobble,
        giant_robot_m1_boss_scripts.wobble_neg, giant_robot_m1_boss_scripts.wobble_pos, giant_robot_m1_boss_scripts.wobble_end, giant_robot_m1_boss_scripts.side_fx_enter, giant_robot_m1_boss_scripts.side_fx_then_next, giant_robot_m1_boss_scripts.next_action,
        giant_robot_m1_boss_scripts.next_return, giant_robot_m1_boss_scripts.turn_enter, giant_robot_m1_boss_scripts.turn_check, giant_robot_m1_boss_scripts.turn_choice, giant_robot_m1_boss_scripts.pick_idle_or_attack, giant_robot_m1_boss_scripts.return_after_pick,
        giant_robot_m1_boss_scripts.turn_pick_enter, giant_robot_m1_boss_scripts.turn_pick, giant_robot_m1_boss_scripts.pick_turn, giant_robot_m1_boss_scripts.return_after_turn, giant_robot_m1_boss_scripts.engage_barrage, giant_robot_m1_boss_scripts.pick_retreat,
        giant_robot_m1_boss_scripts.pick_by_distance,
    },
    /* D_80118570 */ giant_robot_m1_boss_scripts.intro,
};

StateEntry D_80118574[13] = {
    {0, GIANT_ROBOT_M1_BOSS_ANIM_STAND, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_DORMANT, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_RISE, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_WALK, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_WALK_START, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_WALK_STOP, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_IDLE, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_SETTLE, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_STAND, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_STAND, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_CHARGE_RAMP, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_RELEASE, 0},
    {0, GIANT_ROBOT_M1_BOSS_ANIM_RETURN, 0},
};

s16 giant_robot_hit_factors[8] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
};

s16 giant_robot_sound_data_a[24] = {
    1, 0, 0, 0x40, 0x20, 0x40, 0, 0x40,
    0x20, 0x10, 4, 0, 0, 4, 2, 0,
    0, 0, 1, 0x100, 4, -1, 0, 0,
};

s16 giant_robot_sound_data_b[32] = {
    1, 0, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40,
    0x20, 0x10, 4, 0x20, 1, 4, 2, 0,
    0, 0, 1, 0x40, 4, -1, 4, 2,
    0, 0, 0, 1, 0x100, 4, -1, 0,
};

s32 giant_robot_sound_handle_a = -1;

s32 giant_robot_sound_handle_b = -1;

s16 fade_colour_y_from[8][2] = {
    {0x1000, 0x800}, {0x800, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
    {0, 0x800}, {0x800, 0x1000},
};

s16 fade_colour_x_from[12][2] = {
    {0x1000, 0x1000}, {0x1000, 0x1000}, {0x1000, 0xC00}, {0xC00, 0x800}, {0x800, 0x400}, {0x400, 0},
    {0, 0}, {0, 0}, {4, 0xC1}, {4, 0xC2}, {4, 0xC3}, {-1, 0xC4},
};

Keyframe shot_burst_keys[2] = {
    {0x10, 0xC6}, {-1, 0xC5},
};

s16 obj_target_pchr_table[20] = {
    0xB0, 0xB5, 0, 0, 0xB7, 0xB8, 0, 0,
    0xBA, 0xBB, 0, 0, 0xA0, 0xA2, 0, 0,
    -1, -1, 0, 0,
};

s32 obj_target_index = -1;

#include "../stage/data/giant_robot_on_flag.c"

Keyframe giant_robot_sound_keys_start[3] = {
    {0x20, 0xB0}, {0x20, 0xB1}, {-1, 0xB2},
};

Keyframe giant_robot_sound_keys_end[5] = {
    {0x20, 0xB3}, {0x20, 0xB4}, {-1, 0xB5}, {8, 0xA4}, {-1, 0xA3},
};

#include "../stage/data/fade_red_fx_template.c"

#include "../stage/data/fx_owner_template_a.c"

#include "../stage/data/d_8011876C.c"

u16 rcossin_tbl[2048] = {
    0x0000, 0x1000, 0x0006, 0x1000, 0x000D, 0x1000, 0x0013, 0x1000,
    0x0019, 0x1000, 0x001F, 0x1000, 0x0026, 0x1000, 0x002C, 0x1000,
    0x0032, 0x1000, 0x0039, 0x1000, 0x003F, 0x0FFF, 0x0045, 0x0FFF,
    0x004B, 0x0FFF, 0x0052, 0x0FFF, 0x0058, 0x0FFF, 0x005E, 0x0FFF,
    0x0065, 0x0FFF, 0x006B, 0x0FFE, 0x0071, 0x0FFE, 0x0077, 0x0FFE,
    0x007E, 0x0FFE, 0x0084, 0x0FFE, 0x008A, 0x0FFD, 0x0090, 0x0FFD,
    0x0097, 0x0FFD, 0x009D, 0x0FFD, 0x00A3, 0x0FFC, 0x00AA, 0x0FFC,
    0x00B0, 0x0FFC, 0x00B6, 0x0FFC, 0x00BC, 0x0FFB, 0x00C3, 0x0FFB,
    0x00C9, 0x0FFB, 0x00CF, 0x0FFA, 0x00D6, 0x0FFA, 0x00DC, 0x0FFA,
    0x00E2, 0x0FF9, 0x00E8, 0x0FF9, 0x00EF, 0x0FF9, 0x00F5, 0x0FF8,
    0x00FB, 0x0FF8, 0x0101, 0x0FF8, 0x0108, 0x0FF7, 0x010E, 0x0FF7,
    0x0114, 0x0FF6, 0x011B, 0x0FF6, 0x0121, 0x0FF5, 0x0127, 0x0FF5,
    0x012D, 0x0FF4, 0x0134, 0x0FF4, 0x013A, 0x0FF3, 0x0140, 0x0FF3,
    0x0146, 0x0FF2, 0x014D, 0x0FF2, 0x0153, 0x0FF1, 0x0159, 0x0FF1,
    0x015F, 0x0FF0, 0x0166, 0x0FF0, 0x016C, 0x0FEF, 0x0172, 0x0FEF,
    0x0178, 0x0FEE, 0x017F, 0x0FED, 0x0185, 0x0FED, 0x018B, 0x0FEC,
    0x0191, 0x0FEC, 0x0198, 0x0FEB, 0x019E, 0x0FEA, 0x01A4, 0x0FEA,
    0x01AA, 0x0FE9, 0x01B1, 0x0FE8, 0x01B7, 0x0FE8, 0x01BD, 0x0FE7,
    0x01C3, 0x0FE6, 0x01CA, 0x0FE6, 0x01D0, 0x0FE5, 0x01D6, 0x0FE4,
    0x01DC, 0x0FE3, 0x01E3, 0x0FE3, 0x01E9, 0x0FE2, 0x01EF, 0x0FE1,
    0x01F5, 0x0FE0, 0x01FC, 0x0FE0, 0x0202, 0x0FDF, 0x0208, 0x0FDE,
    0x020E, 0x0FDD, 0x0215, 0x0FDC, 0x021B, 0x0FDC, 0x0221, 0x0FDB,
    0x0227, 0x0FDA, 0x022D, 0x0FD9, 0x0234, 0x0FD8, 0x023A, 0x0FD7,
    0x0240, 0x0FD6, 0x0246, 0x0FD5, 0x024D, 0x0FD5, 0x0253, 0x0FD4,
    0x0259, 0x0FD3, 0x025F, 0x0FD2, 0x0265, 0x0FD1, 0x026C, 0x0FD0,
    0x0272, 0x0FCF, 0x0278, 0x0FCE, 0x027E, 0x0FCD, 0x0284, 0x0FCC,
    0x028B, 0x0FCB, 0x0291, 0x0FCA, 0x0297, 0x0FC9, 0x029D, 0x0FC8,
    0x02A3, 0x0FC7, 0x02AA, 0x0FC6, 0x02B0, 0x0FC5, 0x02B6, 0x0FC4,
    0x02BC, 0x0FC3, 0x02C2, 0x0FC2, 0x02C9, 0x0FC0, 0x02CF, 0x0FBF,
    0x02D5, 0x0FBE, 0x02DB, 0x0FBD, 0x02E1, 0x0FBC, 0x02E8, 0x0FBB,
    0x02EE, 0x0FBA, 0x02F4, 0x0FB8, 0x02FA, 0x0FB7, 0x0300, 0x0FB6,
    0x0306, 0x0FB5, 0x030D, 0x0FB4, 0x0313, 0x0FB3, 0x0319, 0x0FB1,
    0x031F, 0x0FB0, 0x0325, 0x0FAF, 0x032B, 0x0FAE, 0x0332, 0x0FAC,
    0x0338, 0x0FAB, 0x033E, 0x0FAA, 0x0344, 0x0FA8, 0x034A, 0x0FA7,
    0x0350, 0x0FA6, 0x0356, 0x0FA5, 0x035D, 0x0FA3, 0x0363, 0x0FA2,
    0x0369, 0x0FA1, 0x036F, 0x0F9F, 0x0375, 0x0F9E, 0x037B, 0x0F9C,
    0x0381, 0x0F9B, 0x0388, 0x0F9A, 0x038E, 0x0F98, 0x0394, 0x0F97,
    0x039A, 0x0F95, 0x03A0, 0x0F94, 0x03A6, 0x0F93, 0x03AC, 0x0F91,
    0x03B2, 0x0F90, 0x03B9, 0x0F8E, 0x03BF, 0x0F8D, 0x03C5, 0x0F8B,
    0x03CB, 0x0F8A, 0x03D1, 0x0F88, 0x03D7, 0x0F87, 0x03DD, 0x0F85,
    0x03E3, 0x0F84, 0x03E9, 0x0F82, 0x03EF, 0x0F81, 0x03F6, 0x0F7F,
    0x03FC, 0x0F7D, 0x0402, 0x0F7C, 0x0408, 0x0F7A, 0x040E, 0x0F79,
    0x0414, 0x0F77, 0x041A, 0x0F76, 0x0420, 0x0F74, 0x0426, 0x0F72,
    0x042C, 0x0F71, 0x0432, 0x0F6F, 0x0438, 0x0F6D, 0x043E, 0x0F6C,
    0x0444, 0x0F6A, 0x044B, 0x0F68, 0x0451, 0x0F67, 0x0457, 0x0F65,
    0x045D, 0x0F63, 0x0463, 0x0F61, 0x0469, 0x0F60, 0x046F, 0x0F5E,
    0x0475, 0x0F5C, 0x047B, 0x0F5A, 0x0481, 0x0F59, 0x0487, 0x0F57,
    0x048D, 0x0F55, 0x0493, 0x0F53, 0x0499, 0x0F51, 0x049F, 0x0F50,
    0x04A5, 0x0F4E, 0x04AB, 0x0F4C, 0x04B1, 0x0F4A, 0x04B7, 0x0F48,
    0x04BD, 0x0F46, 0x04C3, 0x0F45, 0x04C9, 0x0F43, 0x04CF, 0x0F41,
    0x04D5, 0x0F3F, 0x04DB, 0x0F3D, 0x04E1, 0x0F3B, 0x04E7, 0x0F39,
    0x04ED, 0x0F37, 0x04F3, 0x0F35, 0x04F9, 0x0F33, 0x04FF, 0x0F31,
    0x0505, 0x0F2F, 0x050B, 0x0F2D, 0x0511, 0x0F2B, 0x0517, 0x0F29,
    0x051D, 0x0F27, 0x0523, 0x0F25, 0x0529, 0x0F23, 0x052F, 0x0F21,
    0x0534, 0x0F1F, 0x053A, 0x0F1D, 0x0540, 0x0F1B, 0x0546, 0x0F19,
    0x054C, 0x0F17, 0x0552, 0x0F15, 0x0558, 0x0F13, 0x055E, 0x0F11,
    0x0564, 0x0F0E, 0x056A, 0x0F0C, 0x0570, 0x0F0A, 0x0576, 0x0F08,
    0x057C, 0x0F06, 0x0581, 0x0F04, 0x0587, 0x0F02, 0x058D, 0x0EFF,
    0x0593, 0x0EFD, 0x0599, 0x0EFB, 0x059F, 0x0EF9, 0x05A5, 0x0EF7,
    0x05AB, 0x0EF4, 0x05B1, 0x0EF2, 0x05B6, 0x0EF0, 0x05BC, 0x0EEE,
    0x05C2, 0x0EEB, 0x05C8, 0x0EE9, 0x05CE, 0x0EE7, 0x05D4, 0x0EE4,
    0x05DA, 0x0EE2, 0x05DF, 0x0EE0, 0x05E5, 0x0EDD, 0x05EB, 0x0EDB,
    0x05F1, 0x0ED9, 0x05F7, 0x0ED6, 0x05FD, 0x0ED4, 0x0602, 0x0ED2,
    0x0608, 0x0ECF, 0x060E, 0x0ECD, 0x0614, 0x0ECB, 0x061A, 0x0EC8,
    0x061F, 0x0EC6, 0x0625, 0x0EC3, 0x062B, 0x0EC1, 0x0631, 0x0EBF,
    0x0637, 0x0EBC, 0x063C, 0x0EBA, 0x0642, 0x0EB7, 0x0648, 0x0EB5,
    0x064E, 0x0EB2, 0x0654, 0x0EB0, 0x0659, 0x0EAD, 0x065F, 0x0EAB,
    0x0665, 0x0EA8, 0x066B, 0x0EA6, 0x0670, 0x0EA3, 0x0676, 0x0EA1,
    0x067C, 0x0E9E, 0x0682, 0x0E9B, 0x0687, 0x0E99, 0x068D, 0x0E96,
    0x0693, 0x0E94, 0x0699, 0x0E91, 0x069E, 0x0E8F, 0x06A4, 0x0E8C,
    0x06AA, 0x0E89, 0x06AF, 0x0E87, 0x06B5, 0x0E84, 0x06BB, 0x0E81,
    0x06C1, 0x0E7F, 0x06C6, 0x0E7C, 0x06CC, 0x0E79, 0x06D2, 0x0E77,
    0x06D7, 0x0E74, 0x06DD, 0x0E71, 0x06E3, 0x0E6F, 0x06E8, 0x0E6C,
    0x06EE, 0x0E69, 0x06F4, 0x0E66, 0x06F9, 0x0E64, 0x06FF, 0x0E61,
    0x0705, 0x0E5E, 0x070A, 0x0E5B, 0x0710, 0x0E59, 0x0715, 0x0E56,
    0x071B, 0x0E53, 0x0721, 0x0E50, 0x0726, 0x0E4D, 0x072C, 0x0E4B,
    0x0732, 0x0E48, 0x0737, 0x0E45, 0x073D, 0x0E42, 0x0742, 0x0E3F,
    0x0748, 0x0E3C, 0x074E, 0x0E3A, 0x0753, 0x0E37, 0x0759, 0x0E34,
    0x075E, 0x0E31, 0x0764, 0x0E2E, 0x076A, 0x0E2B, 0x076F, 0x0E28,
    0x0775, 0x0E25, 0x077A, 0x0E22, 0x0780, 0x0E1F, 0x0785, 0x0E1C,
    0x078B, 0x0E19, 0x0790, 0x0E16, 0x0796, 0x0E13, 0x079B, 0x0E10,
    0x07A1, 0x0E0D, 0x07A6, 0x0E0A, 0x07AC, 0x0E07, 0x07B2, 0x0E04,
    0x07B7, 0x0E01, 0x07BD, 0x0DFE, 0x07C2, 0x0DFB, 0x07C8, 0x0DF8,
    0x07CD, 0x0DF5, 0x07D2, 0x0DF2, 0x07D8, 0x0DEF, 0x07DD, 0x0DEC,
    0x07E3, 0x0DE9, 0x07E8, 0x0DE6, 0x07EE, 0x0DE3, 0x07F3, 0x0DDF,
    0x07F9, 0x0DDC, 0x07FE, 0x0DD9, 0x0804, 0x0DD6, 0x0809, 0x0DD3,
    0x080E, 0x0DD0, 0x0814, 0x0DCC, 0x0819, 0x0DC9, 0x081F, 0x0DC6,
    0x0824, 0x0DC3, 0x082A, 0x0DC0, 0x082F, 0x0DBC, 0x0834, 0x0DB9,
    0x083A, 0x0DB6, 0x083F, 0x0DB3, 0x0845, 0x0DB0, 0x084A, 0x0DAC,
    0x084F, 0x0DA9, 0x0855, 0x0DA6, 0x085A, 0x0DA2, 0x085F, 0x0D9F,
    0x0865, 0x0D9C, 0x086A, 0x0D99, 0x086F, 0x0D95, 0x0875, 0x0D92,
    0x087A, 0x0D8F, 0x087F, 0x0D8B, 0x0885, 0x0D88, 0x088A, 0x0D85,
    0x088F, 0x0D81, 0x0895, 0x0D7E, 0x089A, 0x0D7A, 0x089F, 0x0D77,
    0x08A5, 0x0D74, 0x08AA, 0x0D70, 0x08AF, 0x0D6D, 0x08B4, 0x0D69,
    0x08BA, 0x0D66, 0x08BF, 0x0D62, 0x08C4, 0x0D5F, 0x08C9, 0x0D5C,
    0x08CF, 0x0D58, 0x08D4, 0x0D55, 0x08D9, 0x0D51, 0x08DE, 0x0D4E,
    0x08E4, 0x0D4A, 0x08E9, 0x0D47, 0x08EE, 0x0D43, 0x08F3, 0x0D40,
    0x08F8, 0x0D3C, 0x08FE, 0x0D39, 0x0903, 0x0D35, 0x0908, 0x0D32,
    0x090D, 0x0D2E, 0x0912, 0x0D2A, 0x0918, 0x0D27, 0x091D, 0x0D23,
    0x0922, 0x0D20, 0x0927, 0x0D1C, 0x092C, 0x0D18, 0x0931, 0x0D15,
    0x0937, 0x0D11, 0x093C, 0x0D0E, 0x0941, 0x0D0A, 0x0946, 0x0D06,
    0x094B, 0x0D03, 0x0950, 0x0CFF, 0x0955, 0x0CFB, 0x095A, 0x0CF8,
    0x095F, 0x0CF4, 0x0965, 0x0CF0, 0x096A, 0x0CED, 0x096F, 0x0CE9,
    0x0974, 0x0CE5, 0x0979, 0x0CE1, 0x097E, 0x0CDE, 0x0983, 0x0CDA,
    0x0988, 0x0CD6, 0x098D, 0x0CD2, 0x0992, 0x0CCF, 0x0997, 0x0CCB,
    0x099C, 0x0CC7, 0x09A1, 0x0CC3, 0x09A6, 0x0CC0, 0x09AB, 0x0CBC,
    0x09B0, 0x0CB8, 0x09B5, 0x0CB4, 0x09BA, 0x0CB0, 0x09BF, 0x0CAC,
    0x09C4, 0x0CA9, 0x09C9, 0x0CA5, 0x09CE, 0x0CA1, 0x09D3, 0x0C9D,
    0x09D8, 0x0C99, 0x09DD, 0x0C95, 0x09E2, 0x0C91, 0x09E7, 0x0C8E,
    0x09EC, 0x0C8A, 0x09F1, 0x0C86, 0x09F6, 0x0C82, 0x09FB, 0x0C7E,
    0x09FF, 0x0C7A, 0x0A04, 0x0C76, 0x0A09, 0x0C72, 0x0A0E, 0x0C6E,
    0x0A13, 0x0C6A, 0x0A18, 0x0C66, 0x0A1D, 0x0C62, 0x0A22, 0x0C5E,
    0x0A26, 0x0C5A, 0x0A2B, 0x0C56, 0x0A30, 0x0C52, 0x0A35, 0x0C4E,
    0x0A3A, 0x0C4A, 0x0A3F, 0x0C46, 0x0A44, 0x0C42, 0x0A48, 0x0C3E,
    0x0A4D, 0x0C3A, 0x0A52, 0x0C36, 0x0A57, 0x0C32, 0x0A5C, 0x0C2E,
    0x0A60, 0x0C2A, 0x0A65, 0x0C26, 0x0A6A, 0x0C22, 0x0A6F, 0x0C1E,
    0x0A73, 0x0C19, 0x0A78, 0x0C15, 0x0A7D, 0x0C11, 0x0A82, 0x0C0D,
    0x0A86, 0x0C09, 0x0A8B, 0x0C05, 0x0A90, 0x0C01, 0x0A95, 0x0BFC,
    0x0A99, 0x0BF8, 0x0A9E, 0x0BF4, 0x0AA3, 0x0BF0, 0x0AA7, 0x0BEC,
    0x0AAC, 0x0BE8, 0x0AB1, 0x0BE3, 0x0AB5, 0x0BDF, 0x0ABA, 0x0BDB,
    0x0ABF, 0x0BD7, 0x0AC3, 0x0BD2, 0x0AC8, 0x0BCE, 0x0ACD, 0x0BCA,
    0x0AD1, 0x0BC6, 0x0AD6, 0x0BC1, 0x0ADB, 0x0BBD, 0x0ADF, 0x0BB9,
    0x0AE4, 0x0BB5, 0x0AE8, 0x0BB0, 0x0AED, 0x0BAC, 0x0AF2, 0x0BA8,
    0x0AF6, 0x0BA3, 0x0AFB, 0x0B9F, 0x0AFF, 0x0B9B, 0x0B04, 0x0B97,
    0x0B08, 0x0B92, 0x0B0D, 0x0B8E, 0x0B11, 0x0B89, 0x0B16, 0x0B85,
    0x0B1B, 0x0B81, 0x0B1F, 0x0B7C, 0x0B24, 0x0B78, 0x0B28, 0x0B74,
    0x0B2D, 0x0B6F, 0x0B31, 0x0B6B, 0x0B36, 0x0B66, 0x0B3A, 0x0B62,
    0x0B3E, 0x0B5E, 0x0B43, 0x0B59, 0x0B47, 0x0B55, 0x0B4C, 0x0B50,
    0x0B50, 0x0B4C, 0x0B55, 0x0B47, 0x0B59, 0x0B43, 0x0B5E, 0x0B3E,
    0x0B62, 0x0B3A, 0x0B66, 0x0B36, 0x0B6B, 0x0B31, 0x0B6F, 0x0B2D,
    0x0B74, 0x0B28, 0x0B78, 0x0B24, 0x0B7C, 0x0B1F, 0x0B81, 0x0B1B,
    0x0B85, 0x0B16, 0x0B89, 0x0B11, 0x0B8E, 0x0B0D, 0x0B92, 0x0B08,
    0x0B97, 0x0B04, 0x0B9B, 0x0AFF, 0x0B9F, 0x0AFB, 0x0BA3, 0x0AF6,
    0x0BA8, 0x0AF2, 0x0BAC, 0x0AED, 0x0BB0, 0x0AE8, 0x0BB5, 0x0AE4,
    0x0BB9, 0x0ADF, 0x0BBD, 0x0ADB, 0x0BC1, 0x0AD6, 0x0BC6, 0x0AD1,
    0x0BCA, 0x0ACD, 0x0BCE, 0x0AC8, 0x0BD2, 0x0AC3, 0x0BD7, 0x0ABF,
    0x0BDB, 0x0ABA, 0x0BDF, 0x0AB5, 0x0BE3, 0x0AB1, 0x0BE8, 0x0AAC,
    0x0BEC, 0x0AA7, 0x0BF0, 0x0AA3, 0x0BF4, 0x0A9E, 0x0BF8, 0x0A99,
    0x0BFC, 0x0A95, 0x0C01, 0x0A90, 0x0C05, 0x0A8B, 0x0C09, 0x0A86,
    0x0C0D, 0x0A82, 0x0C11, 0x0A7D, 0x0C15, 0x0A78, 0x0C19, 0x0A73,
    0x0C1E, 0x0A6F, 0x0C22, 0x0A6A, 0x0C26, 0x0A65, 0x0C2A, 0x0A60,
    0x0C2E, 0x0A5C, 0x0C32, 0x0A57, 0x0C36, 0x0A52, 0x0C3A, 0x0A4D,
    0x0C3E, 0x0A48, 0x0C42, 0x0A44, 0x0C46, 0x0A3F, 0x0C4A, 0x0A3A,
    0x0C4E, 0x0A35, 0x0C52, 0x0A30, 0x0C56, 0x0A2B, 0x0C5A, 0x0A26,
    0x0C5E, 0x0A22, 0x0C62, 0x0A1D, 0x0C66, 0x0A18, 0x0C6A, 0x0A13,
    0x0C6E, 0x0A0E, 0x0C72, 0x0A09, 0x0C76, 0x0A04, 0x0C7A, 0x09FF,
    0x0C7E, 0x09FB, 0x0C82, 0x09F6, 0x0C86, 0x09F1, 0x0C8A, 0x09EC,
    0x0C8E, 0x09E7, 0x0C91, 0x09E2, 0x0C95, 0x09DD, 0x0C99, 0x09D8,
    0x0C9D, 0x09D3, 0x0CA1, 0x09CE, 0x0CA5, 0x09C9, 0x0CA9, 0x09C4,
    0x0CAC, 0x09BF, 0x0CB0, 0x09BA, 0x0CB4, 0x09B5, 0x0CB8, 0x09B0,
    0x0CBC, 0x09AB, 0x0CC0, 0x09A6, 0x0CC3, 0x09A1, 0x0CC7, 0x099C,
    0x0CCB, 0x0997, 0x0CCF, 0x0992, 0x0CD2, 0x098D, 0x0CD6, 0x0988,
    0x0CDA, 0x0983, 0x0CDE, 0x097E, 0x0CE1, 0x0979, 0x0CE5, 0x0974,
    0x0CE9, 0x096F, 0x0CED, 0x096A, 0x0CF0, 0x0965, 0x0CF4, 0x095F,
    0x0CF8, 0x095A, 0x0CFB, 0x0955, 0x0CFF, 0x0950, 0x0D03, 0x094B,
    0x0D06, 0x0946, 0x0D0A, 0x0941, 0x0D0E, 0x093C, 0x0D11, 0x0937,
    0x0D15, 0x0931, 0x0D18, 0x092C, 0x0D1C, 0x0927, 0x0D20, 0x0922,
    0x0D23, 0x091D, 0x0D27, 0x0918, 0x0D2A, 0x0912, 0x0D2E, 0x090D,
    0x0D32, 0x0908, 0x0D35, 0x0903, 0x0D39, 0x08FE, 0x0D3C, 0x08F8,
    0x0D40, 0x08F3, 0x0D43, 0x08EE, 0x0D47, 0x08E9, 0x0D4A, 0x08E4,
    0x0D4E, 0x08DE, 0x0D51, 0x08D9, 0x0D55, 0x08D4, 0x0D58, 0x08CF,
    0x0D5C, 0x08C9, 0x0D5F, 0x08C4, 0x0D62, 0x08BF, 0x0D66, 0x08BA,
    0x0D69, 0x08B4, 0x0D6D, 0x08AF, 0x0D70, 0x08AA, 0x0D74, 0x08A5,
    0x0D77, 0x089F, 0x0D7A, 0x089A, 0x0D7E, 0x0895, 0x0D81, 0x088F,
    0x0D85, 0x088A, 0x0D88, 0x0885, 0x0D8B, 0x087F, 0x0D8F, 0x087A,
    0x0D92, 0x0875, 0x0D95, 0x086F, 0x0D99, 0x086A, 0x0D9C, 0x0865,
    0x0D9F, 0x085F, 0x0DA2, 0x085A, 0x0DA6, 0x0855, 0x0DA9, 0x084F,
    0x0DAC, 0x084A, 0x0DB0, 0x0845, 0x0DB3, 0x083F, 0x0DB6, 0x083A,
    0x0DB9, 0x0834, 0x0DBC, 0x082F, 0x0DC0, 0x082A, 0x0DC3, 0x0824,
    0x0DC6, 0x081F, 0x0DC9, 0x0819, 0x0DCC, 0x0814, 0x0DD0, 0x080E,
    0x0DD3, 0x0809, 0x0DD6, 0x0804, 0x0DD9, 0x07FE, 0x0DDC, 0x07F9,
    0x0DDF, 0x07F3, 0x0DE3, 0x07EE, 0x0DE6, 0x07E8, 0x0DE9, 0x07E3,
    0x0DEC, 0x07DD, 0x0DEF, 0x07D8, 0x0DF2, 0x07D2, 0x0DF5, 0x07CD,
    0x0DF8, 0x07C8, 0x0DFB, 0x07C2, 0x0DFE, 0x07BD, 0x0E01, 0x07B7,
    0x0E04, 0x07B2, 0x0E07, 0x07AC, 0x0E0A, 0x07A6, 0x0E0D, 0x07A1,
    0x0E10, 0x079B, 0x0E13, 0x0796, 0x0E16, 0x0790, 0x0E19, 0x078B,
    0x0E1C, 0x0785, 0x0E1F, 0x0780, 0x0E22, 0x077A, 0x0E25, 0x0775,
    0x0E28, 0x076F, 0x0E2B, 0x076A, 0x0E2E, 0x0764, 0x0E31, 0x075E,
    0x0E34, 0x0759, 0x0E37, 0x0753, 0x0E3A, 0x074E, 0x0E3C, 0x0748,
    0x0E3F, 0x0742, 0x0E42, 0x073D, 0x0E45, 0x0737, 0x0E48, 0x0732,
    0x0E4B, 0x072C, 0x0E4D, 0x0726, 0x0E50, 0x0721, 0x0E53, 0x071B,
    0x0E56, 0x0715, 0x0E59, 0x0710, 0x0E5B, 0x070A, 0x0E5E, 0x0705,
    0x0E61, 0x06FF, 0x0E64, 0x06F9, 0x0E66, 0x06F4, 0x0E69, 0x06EE,
    0x0E6C, 0x06E8, 0x0E6F, 0x06E3, 0x0E71, 0x06DD, 0x0E74, 0x06D7,
    0x0E77, 0x06D2, 0x0E79, 0x06CC, 0x0E7C, 0x06C6, 0x0E7F, 0x06C1,
    0x0E81, 0x06BB, 0x0E84, 0x06B5, 0x0E87, 0x06AF, 0x0E89, 0x06AA,
    0x0E8C, 0x06A4, 0x0E8F, 0x069E, 0x0E91, 0x0699, 0x0E94, 0x0693,
    0x0E96, 0x068D, 0x0E99, 0x0687, 0x0E9B, 0x0682, 0x0E9E, 0x067C,
    0x0EA1, 0x0676, 0x0EA3, 0x0670, 0x0EA6, 0x066B, 0x0EA8, 0x0665,
    0x0EAB, 0x065F, 0x0EAD, 0x0659, 0x0EB0, 0x0654, 0x0EB2, 0x064E,
    0x0EB5, 0x0648, 0x0EB7, 0x0642, 0x0EBA, 0x063C, 0x0EBC, 0x0637,
    0x0EBF, 0x0631, 0x0EC1, 0x062B, 0x0EC3, 0x0625, 0x0EC6, 0x061F,
    0x0EC8, 0x061A, 0x0ECB, 0x0614, 0x0ECD, 0x060E, 0x0ECF, 0x0608,
    0x0ED2, 0x0602, 0x0ED4, 0x05FD, 0x0ED6, 0x05F7, 0x0ED9, 0x05F1,
    0x0EDB, 0x05EB, 0x0EDD, 0x05E5, 0x0EE0, 0x05DF, 0x0EE2, 0x05DA,
    0x0EE4, 0x05D4, 0x0EE7, 0x05CE, 0x0EE9, 0x05C8, 0x0EEB, 0x05C2,
    0x0EEE, 0x05BC, 0x0EF0, 0x05B6, 0x0EF2, 0x05B1, 0x0EF4, 0x05AB,
    0x0EF7, 0x05A5, 0x0EF9, 0x059F, 0x0EFB, 0x0599, 0x0EFD, 0x0593,
    0x0EFF, 0x058D, 0x0F02, 0x0587, 0x0F04, 0x0581, 0x0F06, 0x057C,
    0x0F08, 0x0576, 0x0F0A, 0x0570, 0x0F0C, 0x056A, 0x0F0E, 0x0564,
    0x0F11, 0x055E, 0x0F13, 0x0558, 0x0F15, 0x0552, 0x0F17, 0x054C,
    0x0F19, 0x0546, 0x0F1B, 0x0540, 0x0F1D, 0x053A, 0x0F1F, 0x0534,
    0x0F21, 0x052F, 0x0F23, 0x0529, 0x0F25, 0x0523, 0x0F27, 0x051D,
    0x0F29, 0x0517, 0x0F2B, 0x0511, 0x0F2D, 0x050B, 0x0F2F, 0x0505,
    0x0F31, 0x04FF, 0x0F33, 0x04F9, 0x0F35, 0x04F3, 0x0F37, 0x04ED,
    0x0F39, 0x04E7, 0x0F3B, 0x04E1, 0x0F3D, 0x04DB, 0x0F3F, 0x04D5,
    0x0F41, 0x04CF, 0x0F43, 0x04C9, 0x0F45, 0x04C3, 0x0F46, 0x04BD,
    0x0F48, 0x04B7, 0x0F4A, 0x04B1, 0x0F4C, 0x04AB, 0x0F4E, 0x04A5,
    0x0F50, 0x049F, 0x0F51, 0x0499, 0x0F53, 0x0493, 0x0F55, 0x048D,
    0x0F57, 0x0487, 0x0F59, 0x0481, 0x0F5A, 0x047B, 0x0F5C, 0x0475,
    0x0F5E, 0x046F, 0x0F60, 0x0469, 0x0F61, 0x0463, 0x0F63, 0x045D,
    0x0F65, 0x0457, 0x0F67, 0x0451, 0x0F68, 0x044B, 0x0F6A, 0x0444,
    0x0F6C, 0x043E, 0x0F6D, 0x0438, 0x0F6F, 0x0432, 0x0F71, 0x042C,
    0x0F72, 0x0426, 0x0F74, 0x0420, 0x0F76, 0x041A, 0x0F77, 0x0414,
    0x0F79, 0x040E, 0x0F7A, 0x0408, 0x0F7C, 0x0402, 0x0F7D, 0x03FC,
    0x0F7F, 0x03F6, 0x0F81, 0x03EF, 0x0F82, 0x03E9, 0x0F84, 0x03E3,
    0x0F85, 0x03DD, 0x0F87, 0x03D7, 0x0F88, 0x03D1, 0x0F8A, 0x03CB,
    0x0F8B, 0x03C5, 0x0F8D, 0x03BF, 0x0F8E, 0x03B9, 0x0F90, 0x03B2,
    0x0F91, 0x03AC, 0x0F93, 0x03A6, 0x0F94, 0x03A0, 0x0F95, 0x039A,
    0x0F97, 0x0394, 0x0F98, 0x038E, 0x0F9A, 0x0388, 0x0F9B, 0x0381,
    0x0F9C, 0x037B, 0x0F9E, 0x0375, 0x0F9F, 0x036F, 0x0FA1, 0x0369,
    0x0FA2, 0x0363, 0x0FA3, 0x035D, 0x0FA5, 0x0356, 0x0FA6, 0x0350,
    0x0FA7, 0x034A, 0x0FA8, 0x0344, 0x0FAA, 0x033E, 0x0FAB, 0x0338,
    0x0FAC, 0x0332, 0x0FAE, 0x032B, 0x0FAF, 0x0325, 0x0FB0, 0x031F,
    0x0FB1, 0x0319, 0x0FB3, 0x0313, 0x0FB4, 0x030D, 0x0FB5, 0x0306,
    0x0FB6, 0x0300, 0x0FB7, 0x02FA, 0x0FB8, 0x02F4, 0x0FBA, 0x02EE,
    0x0FBB, 0x02E8, 0x0FBC, 0x02E1, 0x0FBD, 0x02DB, 0x0FBE, 0x02D5,
    0x0FBF, 0x02CF, 0x0FC0, 0x02C9, 0x0FC2, 0x02C2, 0x0FC3, 0x02BC,
    0x0FC4, 0x02B6, 0x0FC5, 0x02B0, 0x0FC6, 0x02AA, 0x0FC7, 0x02A3,
    0x0FC8, 0x029D, 0x0FC9, 0x0297, 0x0FCA, 0x0291, 0x0FCB, 0x028B,
    0x0FCC, 0x0284, 0x0FCD, 0x027E, 0x0FCE, 0x0278, 0x0FCF, 0x0272,
    0x0FD0, 0x026C, 0x0FD1, 0x0265, 0x0FD2, 0x025F, 0x0FD3, 0x0259,
    0x0FD4, 0x0253, 0x0FD5, 0x024D, 0x0FD5, 0x0246, 0x0FD6, 0x0240,
    0x0FD7, 0x023A, 0x0FD8, 0x0234, 0x0FD9, 0x022D, 0x0FDA, 0x0227,
    0x0FDB, 0x0221, 0x0FDC, 0x021B, 0x0FDC, 0x0215, 0x0FDD, 0x020E,
    0x0FDE, 0x0208, 0x0FDF, 0x0202, 0x0FE0, 0x01FC, 0x0FE0, 0x01F5,
    0x0FE1, 0x01EF, 0x0FE2, 0x01E9, 0x0FE3, 0x01E3, 0x0FE3, 0x01DC,
    0x0FE4, 0x01D6, 0x0FE5, 0x01D0, 0x0FE6, 0x01CA, 0x0FE6, 0x01C3,
    0x0FE7, 0x01BD, 0x0FE8, 0x01B7, 0x0FE8, 0x01B1, 0x0FE9, 0x01AA,
    0x0FEA, 0x01A4, 0x0FEA, 0x019E, 0x0FEB, 0x0198, 0x0FEC, 0x0191,
    0x0FEC, 0x018B, 0x0FED, 0x0185, 0x0FED, 0x017F, 0x0FEE, 0x0178,
    0x0FEF, 0x0172, 0x0FEF, 0x016C, 0x0FF0, 0x0166, 0x0FF0, 0x015F,
    0x0FF1, 0x0159, 0x0FF1, 0x0153, 0x0FF2, 0x014D, 0x0FF2, 0x0146,
    0x0FF3, 0x0140, 0x0FF3, 0x013A, 0x0FF4, 0x0134, 0x0FF4, 0x012D,
    0x0FF5, 0x0127, 0x0FF5, 0x0121, 0x0FF6, 0x011B, 0x0FF6, 0x0114,
    0x0FF7, 0x010E, 0x0FF7, 0x0108, 0x0FF8, 0x0101, 0x0FF8, 0x00FB,
    0x0FF8, 0x00F5, 0x0FF9, 0x00EF, 0x0FF9, 0x00E8, 0x0FF9, 0x00E2,
    0x0FFA, 0x00DC, 0x0FFA, 0x00D6, 0x0FFA, 0x00CF, 0x0FFB, 0x00C9,
    0x0FFB, 0x00C3, 0x0FFB, 0x00BC, 0x0FFC, 0x00B6, 0x0FFC, 0x00B0,
    0x0FFC, 0x00AA, 0x0FFC, 0x00A3, 0x0FFD, 0x009D, 0x0FFD, 0x0097,
    0x0FFD, 0x0090, 0x0FFD, 0x008A, 0x0FFE, 0x0084, 0x0FFE, 0x007E,
    0x0FFE, 0x0077, 0x0FFE, 0x0071, 0x0FFE, 0x006B, 0x0FFF, 0x0065,
    0x0FFF, 0x005E, 0x0FFF, 0x0058, 0x0FFF, 0x0052, 0x0FFF, 0x004B,
    0x0FFF, 0x0045, 0x0FFF, 0x003F, 0x1000, 0x0039, 0x1000, 0x0032,
    0x1000, 0x002C, 0x1000, 0x0026, 0x1000, 0x001F, 0x1000, 0x0019,
    0x1000, 0x0013, 0x1000, 0x000D, 0x1000, 0x0006, 0x1000, 0x0000,
};

u32 sincos_deg90[1024] = {
    0x1000, 0xFFFA1000, 0xFFF31000, 0xFFED1000, 0xFFE71000, 0xFFE11000,
    0xFFDA1000, 0xFFD41000, 0xFFCE1000, 0xFFC71000, 0xFFC10FFF, 0xFFBB0FFF,
    0xFFB50FFF, 0xFFAE0FFF, 0xFFA80FFF, 0xFFA20FFF, 0xFF9B0FFF, 0xFF950FFE,
    0xFF8F0FFE, 0xFF890FFE, 0xFF820FFE, 0xFF7C0FFE, 0xFF760FFD, 0xFF700FFD,
    0xFF690FFD, 0xFF630FFD, 0xFF5D0FFC, 0xFF560FFC, 0xFF500FFC, 0xFF4A0FFC,
    0xFF440FFB, 0xFF3D0FFB, 0xFF370FFB, 0xFF310FFA, 0xFF2A0FFA, 0xFF240FFA,
    0xFF1E0FF9, 0xFF180FF9, 0xFF110FF9, 0xFF0B0FF8, 0xFF050FF8, 0xFEFF0FF8,
    0xFEF80FF7, 0xFEF20FF7, 0xFEEC0FF6, 0xFEE50FF6, 0xFEDF0FF5, 0xFED90FF5,
    0xFED30FF4, 0xFECC0FF4, 0xFEC60FF3, 0xFEC00FF3, 0xFEBA0FF2, 0xFEB30FF2,
    0xFEAD0FF1, 0xFEA70FF1, 0xFEA10FF0, 0xFE9A0FF0, 0xFE940FEF, 0xFE8E0FEF,
    0xFE880FEE, 0xFE810FED, 0xFE7B0FED, 0xFE750FEC, 0xFE6F0FEC, 0xFE680FEB,
    0xFE620FEA, 0xFE5C0FEA, 0xFE560FE9, 0xFE4F0FE8, 0xFE490FE8, 0xFE430FE7,
    0xFE3D0FE6, 0xFE360FE6, 0xFE300FE5, 0xFE2A0FE4, 0xFE240FE3, 0xFE1D0FE3,
    0xFE170FE2, 0xFE110FE1, 0xFE0B0FE0, 0xFE040FE0, 0xFDFE0FDF, 0xFDF80FDE,
    0xFDF20FDD, 0xFDEB0FDC, 0xFDE50FDC, 0xFDDF0FDB, 0xFDD90FDA, 0xFDD30FD9,
    0xFDCC0FD8, 0xFDC60FD7, 0xFDC00FD6, 0xFDBA0FD5, 0xFDB30FD5, 0xFDAD0FD4,
    0xFDA70FD3, 0xFDA10FD2, 0xFD9B0FD1, 0xFD940FD0, 0xFD8E0FCF, 0xFD880FCE,
    0xFD820FCD, 0xFD7C0FCC, 0xFD750FCB, 0xFD6F0FCA, 0xFD690FC9, 0xFD630FC8,
    0xFD5D0FC7, 0xFD560FC6, 0xFD500FC5, 0xFD4A0FC4, 0xFD440FC3, 0xFD3E0FC2,
    0xFD370FC0, 0xFD310FBF, 0xFD2B0FBE, 0xFD250FBD, 0xFD1F0FBC, 0xFD180FBB,
    0xFD120FBA, 0xFD0C0FB8, 0xFD060FB7, 0xFD000FB6, 0xFCFA0FB5, 0xFCF30FB4,
    0xFCED0FB3, 0xFCE70FB1, 0xFCE10FB0, 0xFCDB0FAF, 0xFCD50FAE, 0xFCCE0FAC,
    0xFCC80FAB, 0xFCC20FAA, 0xFCBC0FA8, 0xFCB60FA7, 0xFCB00FA6, 0xFCAA0FA5,
    0xFCA30FA3, 0xFC9D0FA2, 0xFC970FA1, 0xFC910F9F, 0xFC8B0F9E, 0xFC850F9C,
    0xFC7F0F9B, 0xFC780F9A, 0xFC720F98, 0xFC6C0F97, 0xFC660F95, 0xFC600F94,
    0xFC5A0F93, 0xFC540F91, 0xFC4E0F90, 0xFC470F8E, 0xFC410F8D, 0xFC3B0F8B,
    0xFC350F8A, 0xFC2F0F88, 0xFC290F87, 0xFC230F85, 0xFC1D0F84, 0xFC170F82,
    0xFC110F81, 0xFC0A0F7F, 0xFC040F7D, 0xFBFE0F7C, 0xFBF80F7A, 0xFBF20F79,
    0xFBEC0F77, 0xFBE60F76, 0xFBE00F74, 0xFBDA0F72, 0xFBD40F71, 0xFBCE0F6F,
    0xFBC80F6D, 0xFBC20F6C, 0xFBBC0F6A, 0xFBB50F68, 0xFBAF0F67, 0xFBA90F65,
    0xFBA30F63, 0xFB9D0F61, 0xFB970F60, 0xFB910F5E, 0xFB8B0F5C, 0xFB850F5A,
    0xFB7F0F59, 0xFB790F57, 0xFB730F55, 0xFB6D0F53, 0xFB670F51, 0xFB610F50,
    0xFB5B0F4E, 0xFB550F4C, 0xFB4F0F4A, 0xFB490F48, 0xFB430F46, 0xFB3D0F45,
    0xFB370F43, 0xFB310F41, 0xFB2B0F3F, 0xFB250F3D, 0xFB1F0F3B, 0xFB190F39,
    0xFB130F37, 0xFB0D0F35, 0xFB070F33, 0xFB010F31, 0xFAFB0F2F, 0xFAF50F2D,
    0xFAEF0F2B, 0xFAE90F29, 0xFAE30F27, 0xFADD0F25, 0xFAD70F23, 0xFAD10F21,
    0xFACC0F1F, 0xFAC60F1D, 0xFAC00F1B, 0xFABA0F19, 0xFAB40F17, 0xFAAE0F15,
    0xFAA80F13, 0xFAA20F11, 0xFA9C0F0E, 0xFA960F0C, 0xFA900F0A, 0xFA8A0F08,
    0xFA840F06, 0xFA7F0F04, 0xFA790F02, 0xFA730EFF, 0xFA6D0EFD, 0xFA670EFB,
    0xFA610EF9, 0xFA5B0EF7, 0xFA550EF4, 0xFA4F0EF2, 0xFA4A0EF0, 0xFA440EEE,
    0xFA3E0EEB, 0xFA380EE9, 0xFA320EE7, 0xFA2C0EE4, 0xFA260EE2, 0xFA210EE0,
    0xFA1B0EDD, 0xFA150EDB, 0xFA0F0ED9, 0xFA090ED6, 0xFA030ED4, 0xF9FE0ED2,
    0xF9F80ECF, 0xF9F20ECD, 0xF9EC0ECB, 0xF9E60EC8, 0xF9E10EC6, 0xF9DB0EC3,
    0xF9D50EC1, 0xF9CF0EBF, 0xF9C90EBC, 0xF9C40EBA, 0xF9BE0EB7, 0xF9B80EB5,
    0xF9B20EB2, 0xF9AC0EB0, 0xF9A70EAD, 0xF9A10EAB, 0xF99B0EA8, 0xF9950EA6,
    0xF9900EA3, 0xF98A0EA1, 0xF9840E9E, 0xF97E0E9B, 0xF9790E99, 0xF9730E96,
    0xF96D0E94, 0xF9670E91, 0xF9620E8F, 0xF95C0E8C, 0xF9560E89, 0xF9510E87,
    0xF94B0E84, 0xF9450E81, 0xF93F0E7F, 0xF93A0E7C, 0xF9340E79, 0xF92E0E77,
    0xF9290E74, 0xF9230E71, 0xF91D0E6F, 0xF9180E6C, 0xF9120E69, 0xF90C0E66,
    0xF9070E64, 0xF9010E61, 0xF8FB0E5E, 0xF8F60E5B, 0xF8F00E59, 0xF8EB0E56,
    0xF8E50E53, 0xF8DF0E50, 0xF8DA0E4D, 0xF8D40E4B, 0xF8CE0E48, 0xF8C90E45,
    0xF8C30E42, 0xF8BE0E3F, 0xF8B80E3C, 0xF8B20E3A, 0xF8AD0E37, 0xF8A70E34,
    0xF8A20E31, 0xF89C0E2E, 0xF8960E2B, 0xF8910E28, 0xF88B0E25, 0xF8860E22,
    0xF8800E1F, 0xF87B0E1C, 0xF8750E19, 0xF8700E16, 0xF86A0E13, 0xF8650E10,
    0xF85F0E0D, 0xF85A0E0A, 0xF8540E07, 0xF84E0E04, 0xF8490E01, 0xF8430DFE,
    0xF83E0DFB, 0xF8380DF8, 0xF8330DF5, 0xF82E0DF2, 0xF8280DEF, 0xF8230DEC,
    0xF81D0DE9, 0xF8180DE6, 0xF8120DE3, 0xF80D0DDF, 0xF8070DDC, 0xF8020DD9,
    0xF7FC0DD6, 0xF7F70DD3, 0xF7F20DD0, 0xF7EC0DCC, 0xF7E70DC9, 0xF7E10DC6,
    0xF7DC0DC3, 0xF7D60DC0, 0xF7D10DBC, 0xF7CC0DB9, 0xF7C60DB6, 0xF7C10DB3,
    0xF7BB0DB0, 0xF7B60DAC, 0xF7B10DA9, 0xF7AB0DA6, 0xF7A60DA2, 0xF7A10D9F,
    0xF79B0D9C, 0xF7960D99, 0xF7910D95, 0xF78B0D92, 0xF7860D8F, 0xF7810D8B,
    0xF77B0D88, 0xF7760D85, 0xF7710D81, 0xF76B0D7E, 0xF7660D7A, 0xF7610D77,
    0xF75B0D74, 0xF7560D70, 0xF7510D6D, 0xF74C0D69, 0xF7460D66, 0xF7410D62,
    0xF73C0D5F, 0xF7370D5C, 0xF7310D58, 0xF72C0D55, 0xF7270D51, 0xF7220D4E,
    0xF71C0D4A, 0xF7170D47, 0xF7120D43, 0xF70D0D40, 0xF7080D3C, 0xF7020D39,
    0xF6FD0D35, 0xF6F80D32, 0xF6F30D2E, 0xF6EE0D2A, 0xF6E80D27, 0xF6E30D23,
    0xF6DE0D20, 0xF6D90D1C, 0xF6D40D18, 0xF6CF0D15, 0xF6C90D11, 0xF6C40D0E,
    0xF6BF0D0A, 0xF6BA0D06, 0xF6B50D03, 0xF6B00CFF, 0xF6AB0CFB, 0xF6A60CF8,
    0xF6A10CF4, 0xF69B0CF0, 0xF6960CED, 0xF6910CE9, 0xF68C0CE5, 0xF6870CE1,
    0xF6820CDE, 0xF67D0CDA, 0xF6780CD6, 0xF6730CD2, 0xF66E0CCF, 0xF6690CCB,
    0xF6640CC7, 0xF65F0CC3, 0xF65A0CC0, 0xF6550CBC, 0xF6500CB8, 0xF64B0CB4,
    0xF6460CB0, 0xF6410CAC, 0xF63C0CA9, 0xF6370CA5, 0xF6320CA1, 0xF62D0C9D,
    0xF6280C99, 0xF6230C95, 0xF61E0C91, 0xF6190C8E, 0xF6140C8A, 0xF60F0C86,
    0xF60A0C82, 0xF6050C7E, 0xF6010C7A, 0xF5FC0C76, 0xF5F70C72, 0xF5F20C6E,
    0xF5ED0C6A, 0xF5E80C66, 0xF5E30C62, 0xF5DE0C5E, 0xF5DA0C5A, 0xF5D50C56,
    0xF5D00C52, 0xF5CB0C4E, 0xF5C60C4A, 0xF5C10C46, 0xF5BC0C42, 0xF5B80C3E,
    0xF5B30C3A, 0xF5AE0C36, 0xF5A90C32, 0xF5A40C2E, 0xF5A00C2A, 0xF59B0C26,
    0xF5960C22, 0xF5910C1E, 0xF58D0C19, 0xF5880C15, 0xF5830C11, 0xF57E0C0D,
    0xF57A0C09, 0xF5750C05, 0xF5700C01, 0xF56B0BFC, 0xF5670BF8, 0xF5620BF4,
    0xF55D0BF0, 0xF5590BEC, 0xF5540BE8, 0xF54F0BE3, 0xF54B0BDF, 0xF5460BDB,
    0xF5410BD7, 0xF53D0BD2, 0xF5380BCE, 0xF5330BCA, 0xF52F0BC6, 0xF52A0BC1,
    0xF5250BBD, 0xF5210BB9, 0xF51C0BB5, 0xF5180BB0, 0xF5130BAC, 0xF50E0BA8,
    0xF50A0BA3, 0xF5050B9F, 0xF5010B9B, 0xF4FC0B97, 0xF4F80B92, 0xF4F30B8E,
    0xF4EF0B89, 0xF4EA0B85, 0xF4E50B81, 0xF4E10B7C, 0xF4DC0B78, 0xF4D80B74,
    0xF4D30B6F, 0xF4CF0B6B, 0xF4CA0B66, 0xF4C60B62, 0xF4C20B5E, 0xF4BD0B59,
    0xF4B90B55, 0xF4B40B50, 0xF4B00B4C, 0xF4AB0B47, 0xF4A70B43, 0xF4A20B3E,
    0xF49E0B3A, 0xF49A0B36, 0xF4950B31, 0xF4910B2D, 0xF48C0B28, 0xF4880B24,
    0xF4840B1F, 0xF47F0B1B, 0xF47B0B16, 0xF4770B11, 0xF4720B0D, 0xF46E0B08,
    0xF4690B04, 0xF4650AFF, 0xF4610AFB, 0xF45D0AF6, 0xF4580AF2, 0xF4540AED,
    0xF4500AE8, 0xF44B0AE4, 0xF4470ADF, 0xF4430ADB, 0xF43F0AD6, 0xF43A0AD1,
    0xF4360ACD, 0xF4320AC8, 0xF42E0AC3, 0xF4290ABF, 0xF4250ABA, 0xF4210AB5,
    0xF41D0AB1, 0xF4180AAC, 0xF4140AA7, 0xF4100AA3, 0xF40C0A9E, 0xF4080A99,
    0xF4040A95, 0xF3FF0A90, 0xF3FB0A8B, 0xF3F70A86, 0xF3F30A82, 0xF3EF0A7D,
    0xF3EB0A78, 0xF3E70A73, 0xF3E20A6F, 0xF3DE0A6A, 0xF3DA0A65, 0xF3D60A60,
    0xF3D20A5C, 0xF3CE0A57, 0xF3CA0A52, 0xF3C60A4D, 0xF3C20A48, 0xF3BE0A44,
    0xF3BA0A3F, 0xF3B60A3A, 0xF3B20A35, 0xF3AE0A30, 0xF3AA0A2B, 0xF3A60A26,
    0xF3A20A22, 0xF39E0A1D, 0xF39A0A18, 0xF3960A13, 0xF3920A0E, 0xF38E0A09,
    0xF38A0A04, 0xF38609FF, 0xF38209FB, 0xF37E09F6, 0xF37A09F1, 0xF37609EC,
    0xF37209E7, 0xF36F09E2, 0xF36B09DD, 0xF36709D8, 0xF36309D3, 0xF35F09CE,
    0xF35B09C9, 0xF35709C4, 0xF35409BF, 0xF35009BA, 0xF34C09B5, 0xF34809B0,
    0xF34409AB, 0xF34009A6, 0xF33D09A1, 0xF339099C, 0xF3350997, 0xF3310992,
    0xF32E098D, 0xF32A0988, 0xF3260983, 0xF322097E, 0xF31F0979, 0xF31B0974,
    0xF317096F, 0xF313096A, 0xF3100965, 0xF30C095F, 0xF308095A, 0xF3050955,
    0xF3010950, 0xF2FD094B, 0xF2FA0946, 0xF2F60941, 0xF2F2093C, 0xF2EF0937,
    0xF2EB0931, 0xF2E8092C, 0xF2E40927, 0xF2E00922, 0xF2DD091D, 0xF2D90918,
    0xF2D60912, 0xF2D2090D, 0xF2CE0908, 0xF2CB0903, 0xF2C708FE, 0xF2C408F8,
    0xF2C008F3, 0xF2BD08EE, 0xF2B908E9, 0xF2B608E4, 0xF2B208DE, 0xF2AF08D9,
    0xF2AB08D4, 0xF2A808CF, 0xF2A408C9, 0xF2A108C4, 0xF29E08BF, 0xF29A08BA,
    0xF29708B4, 0xF29308AF, 0xF29008AA, 0xF28C08A5, 0xF289089F, 0xF286089A,
    0xF2820895, 0xF27F088F, 0xF27B088A, 0xF2780885, 0xF275087F, 0xF271087A,
    0xF26E0875, 0xF26B086F, 0xF267086A, 0xF2640865, 0xF261085F, 0xF25E085A,
    0xF25A0855, 0xF257084F, 0xF254084A, 0xF2500845, 0xF24D083F, 0xF24A083A,
    0xF2470834, 0xF244082F, 0xF240082A, 0xF23D0824, 0xF23A081F, 0xF2370819,
    0xF2340814, 0xF230080E, 0xF22D0809, 0xF22A0804, 0xF22707FE, 0xF22407F9,
    0xF22107F3, 0xF21D07EE, 0xF21A07E8, 0xF21707E3, 0xF21407DD, 0xF21107D8,
    0xF20E07D2, 0xF20B07CD, 0xF20807C8, 0xF20507C2, 0xF20207BD, 0xF1FF07B7,
    0xF1FC07B2, 0xF1F907AC, 0xF1F607A6, 0xF1F307A1, 0xF1F0079B, 0xF1ED0796,
    0xF1EA0790, 0xF1E7078B, 0xF1E40785, 0xF1E10780, 0xF1DE077A, 0xF1DB0775,
    0xF1D8076F, 0xF1D5076A, 0xF1D20764, 0xF1CF075E, 0xF1CC0759, 0xF1C90753,
    0xF1C6074E, 0xF1C40748, 0xF1C10742, 0xF1BE073D, 0xF1BB0737, 0xF1B80732,
    0xF1B5072C, 0xF1B30726, 0xF1B00721, 0xF1AD071B, 0xF1AA0715, 0xF1A70710,
    0xF1A5070A, 0xF1A20705, 0xF19F06FF, 0xF19C06F9, 0xF19A06F4, 0xF19706EE,
    0xF19406E8, 0xF19106E3, 0xF18F06DD, 0xF18C06D7, 0xF18906D2, 0xF18706CC,
    0xF18406C6, 0xF18106C1, 0xF17F06BB, 0xF17C06B5, 0xF17906AF, 0xF17706AA,
    0xF17406A4, 0xF171069E, 0xF16F0699, 0xF16C0693, 0xF16A068D, 0xF1670687,
    0xF1650682, 0xF162067C, 0xF15F0676, 0xF15D0670, 0xF15A066B, 0xF1580665,
    0xF155065F, 0xF1530659, 0xF1500654, 0xF14E064E, 0xF14B0648, 0xF1490642,
    0xF146063C, 0xF1440637, 0xF1410631, 0xF13F062B, 0xF13D0625, 0xF13A061F,
    0xF138061A, 0xF1350614, 0xF133060E, 0xF1310608, 0xF12E0602, 0xF12C05FD,
    0xF12A05F7, 0xF12705F1, 0xF12505EB, 0xF12305E5, 0xF12005DF, 0xF11E05DA,
    0xF11C05D4, 0xF11905CE, 0xF11705C8, 0xF11505C2, 0xF11205BC, 0xF11005B6,
    0xF10E05B1, 0xF10C05AB, 0xF10905A5, 0xF107059F, 0xF1050599, 0xF1030593,
    0xF101058D, 0xF0FE0587, 0xF0FC0581, 0xF0FA057C, 0xF0F80576, 0xF0F60570,
    0xF0F4056A, 0xF0F20564, 0xF0EF055E, 0xF0ED0558, 0xF0EB0552, 0xF0E9054C,
    0xF0E70546, 0xF0E50540, 0xF0E3053A, 0xF0E10534, 0xF0DF052F, 0xF0DD0529,
    0xF0DB0523, 0xF0D9051D, 0xF0D70517, 0xF0D50511, 0xF0D3050B, 0xF0D10505,
    0xF0CF04FF, 0xF0CD04F9, 0xF0CB04F3, 0xF0C904ED, 0xF0C704E7, 0xF0C504E1,
    0xF0C304DB, 0xF0C104D5, 0xF0BF04CF, 0xF0BD04C9, 0xF0BB04C3, 0xF0BA04BD,
    0xF0B804B7, 0xF0B604B1, 0xF0B404AB, 0xF0B204A5, 0xF0B0049F, 0xF0AF0499,
    0xF0AD0493, 0xF0AB048D, 0xF0A90487, 0xF0A70481, 0xF0A6047B, 0xF0A40475,
    0xF0A2046F, 0xF0A00469, 0xF09F0463, 0xF09D045D, 0xF09B0457, 0xF0990451,
    0xF098044B, 0xF0960444, 0xF094043E, 0xF0930438, 0xF0910432, 0xF08F042C,
    0xF08E0426, 0xF08C0420, 0xF08A041A, 0xF0890414, 0xF087040E, 0xF0860408,
    0xF0840402, 0xF08303FC, 0xF08103F6, 0xF07F03EF, 0xF07E03E9, 0xF07C03E3,
    0xF07B03DD, 0xF07903D7, 0xF07803D1, 0xF07603CB, 0xF07503C5, 0xF07303BF,
    0xF07203B9, 0xF07003B2, 0xF06F03AC, 0xF06D03A6, 0xF06C03A0, 0xF06B039A,
    0xF0690394, 0xF068038E, 0xF0660388, 0xF0650381, 0xF064037B, 0xF0620375,
    0xF061036F, 0xF05F0369, 0xF05E0363, 0xF05D035D, 0xF05B0356, 0xF05A0350,
    0xF059034A, 0xF0580344, 0xF056033E, 0xF0550338, 0xF0540332, 0xF052032B,
    0xF0510325, 0xF050031F, 0xF04F0319, 0xF04D0313, 0xF04C030D, 0xF04B0306,
    0xF04A0300, 0xF04902FA, 0xF04802F4, 0xF04602EE, 0xF04502E8, 0xF04402E1,
    0xF04302DB, 0xF04202D5, 0xF04102CF, 0xF04002C9, 0xF03E02C2, 0xF03D02BC,
    0xF03C02B6, 0xF03B02B0, 0xF03A02AA, 0xF03902A3, 0xF038029D, 0xF0370297,
    0xF0360291, 0xF035028B, 0xF0340284, 0xF033027E, 0xF0320278, 0xF0310272,
    0xF030026C, 0xF02F0265, 0xF02E025F, 0xF02D0259, 0xF02C0253, 0xF02B024D,
    0xF02B0246, 0xF02A0240, 0xF029023A, 0xF0280234, 0xF027022D, 0xF0260227,
    0xF0250221, 0xF024021B, 0xF0240215, 0xF023020E, 0xF0220208, 0xF0210202,
    0xF02001FC, 0xF02001F5, 0xF01F01EF, 0xF01E01E9, 0xF01D01E3, 0xF01D01DC,
    0xF01C01D6, 0xF01B01D0, 0xF01A01CA, 0xF01A01C3, 0xF01901BD, 0xF01801B7,
    0xF01801B1, 0xF01701AA, 0xF01601A4, 0xF016019E, 0xF0150198, 0xF0140191,
    0xF014018B, 0xF0130185, 0xF013017F, 0xF0120178, 0xF0110172, 0xF011016C,
    0xF0100166, 0xF010015F, 0xF00F0159, 0xF00F0153, 0xF00E014D, 0xF00E0146,
    0xF00D0140, 0xF00D013A, 0xF00C0134, 0xF00C012D, 0xF00B0127, 0xF00B0121,
    0xF00A011B, 0xF00A0114, 0xF009010E, 0xF0090108, 0xF0080101, 0xF00800FB,
    0xF00800F5, 0xF00700EF, 0xF00700E8, 0xF00700E2, 0xF00600DC, 0xF00600D6,
    0xF00600CF, 0xF00500C9, 0xF00500C3, 0xF00500BC, 0xF00400B6, 0xF00400B0,
    0xF00400AA, 0xF00400A3, 0xF003009D, 0xF0030097, 0xF0030090, 0xF003008A,
    0xF0020084, 0xF002007E, 0xF0020077, 0xF0020071, 0xF002006B, 0xF0010065,
    0xF001005E, 0xF0010058, 0xF0010052, 0xF001004B, 0xF0010045, 0xF001003F,
    0xF0000039, 0xF0000032, 0xF000002C, 0xF0000026, 0xF000001F, 0xF0000019,
    0xF0000013, 0xF000000D, 0xF0000006, 0xF0000000,
};

u32 view_sincos[1024] = {
    0xF0000000, 0xF000FFFA, 0xF000FFF3, 0xF000FFED, 0xF000FFE7, 0xF000FFE1,
    0xF000FFDA, 0xF000FFD4, 0xF000FFCE, 0xF000FFC7, 0xF001FFC1, 0xF001FFBB,
    0xF001FFB5, 0xF001FFAE, 0xF001FFA8, 0xF001FFA2, 0xF001FF9B, 0xF002FF95,
    0xF002FF8F, 0xF002FF89, 0xF002FF82, 0xF002FF7C, 0xF003FF76, 0xF003FF70,
    0xF003FF69, 0xF003FF63, 0xF004FF5D, 0xF004FF56, 0xF004FF50, 0xF004FF4A,
    0xF005FF44, 0xF005FF3D, 0xF005FF37, 0xF006FF31, 0xF006FF2A, 0xF006FF24,
    0xF007FF1E, 0xF007FF18, 0xF007FF11, 0xF008FF0B, 0xF008FF05, 0xF008FEFF,
    0xF009FEF8, 0xF009FEF2, 0xF00AFEEC, 0xF00AFEE5, 0xF00BFEDF, 0xF00BFED9,
    0xF00CFED3, 0xF00CFECC, 0xF00DFEC6, 0xF00DFEC0, 0xF00EFEBA, 0xF00EFEB3,
    0xF00FFEAD, 0xF00FFEA7, 0xF010FEA1, 0xF010FE9A, 0xF011FE94, 0xF011FE8E,
    0xF012FE88, 0xF013FE81, 0xF013FE7B, 0xF014FE75, 0xF014FE6F, 0xF015FE68,
    0xF016FE62, 0xF016FE5C, 0xF017FE56, 0xF018FE4F, 0xF018FE49, 0xF019FE43,
    0xF01AFE3D, 0xF01AFE36, 0xF01BFE30, 0xF01CFE2A, 0xF01DFE24, 0xF01DFE1D,
    0xF01EFE17, 0xF01FFE11, 0xF020FE0B, 0xF020FE04, 0xF021FDFE, 0xF022FDF8,
    0xF023FDF2, 0xF024FDEB, 0xF024FDE5, 0xF025FDDF, 0xF026FDD9, 0xF027FDD3,
    0xF028FDCC, 0xF029FDC6, 0xF02AFDC0, 0xF02BFDBA, 0xF02BFDB3, 0xF02CFDAD,
    0xF02DFDA7, 0xF02EFDA1, 0xF02FFD9B, 0xF030FD94, 0xF031FD8E, 0xF032FD88,
    0xF033FD82, 0xF034FD7C, 0xF035FD75, 0xF036FD6F, 0xF037FD69, 0xF038FD63,
    0xF039FD5D, 0xF03AFD56, 0xF03BFD50, 0xF03CFD4A, 0xF03DFD44, 0xF03EFD3E,
    0xF040FD37, 0xF041FD31, 0xF042FD2B, 0xF043FD25, 0xF044FD1F, 0xF045FD18,
    0xF046FD12, 0xF048FD0C, 0xF049FD06, 0xF04AFD00, 0xF04BFCFA, 0xF04CFCF3,
    0xF04DFCED, 0xF04FFCE7, 0xF050FCE1, 0xF051FCDB, 0xF052FCD5, 0xF054FCCE,
    0xF055FCC8, 0xF056FCC2, 0xF058FCBC, 0xF059FCB6, 0xF05AFCB0, 0xF05BFCAA,
    0xF05DFCA3, 0xF05EFC9D, 0xF05FFC97, 0xF061FC91, 0xF062FC8B, 0xF064FC85,
    0xF065FC7F, 0xF066FC78, 0xF068FC72, 0xF069FC6C, 0xF06BFC66, 0xF06CFC60,
    0xF06DFC5A, 0xF06FFC54, 0xF070FC4E, 0xF072FC47, 0xF073FC41, 0xF075FC3B,
    0xF076FC35, 0xF078FC2F, 0xF079FC29, 0xF07BFC23, 0xF07CFC1D, 0xF07EFC17,
    0xF07FFC11, 0xF081FC0A, 0xF083FC04, 0xF084FBFE, 0xF086FBF8, 0xF087FBF2,
    0xF089FBEC, 0xF08AFBE6, 0xF08CFBE0, 0xF08EFBDA, 0xF08FFBD4, 0xF091FBCE,
    0xF093FBC8, 0xF094FBC2, 0xF096FBBC, 0xF098FBB5, 0xF099FBAF, 0xF09BFBA9,
    0xF09DFBA3, 0xF09FFB9D, 0xF0A0FB97, 0xF0A2FB91, 0xF0A4FB8B, 0xF0A6FB85,
    0xF0A7FB7F, 0xF0A9FB79, 0xF0ABFB73, 0xF0ADFB6D, 0xF0AFFB67, 0xF0B0FB61,
    0xF0B2FB5B, 0xF0B4FB55, 0xF0B6FB4F, 0xF0B8FB49, 0xF0BAFB43, 0xF0BBFB3D,
    0xF0BDFB37, 0xF0BFFB31, 0xF0C1FB2B, 0xF0C3FB25, 0xF0C5FB1F, 0xF0C7FB19,
    0xF0C9FB13, 0xF0CBFB0D, 0xF0CDFB07, 0xF0CFFB01, 0xF0D1FAFB, 0xF0D3FAF5,
    0xF0D5FAEF, 0xF0D7FAE9, 0xF0D9FAE3, 0xF0DBFADD, 0xF0DDFAD7, 0xF0DFFAD1,
    0xF0E1FACC, 0xF0E3FAC6, 0xF0E5FAC0, 0xF0E7FABA, 0xF0E9FAB4, 0xF0EBFAAE,
    0xF0EDFAA8, 0xF0EFFAA2, 0xF0F2FA9C, 0xF0F4FA96, 0xF0F6FA90, 0xF0F8FA8A,
    0xF0FAFA84, 0xF0FCFA7F, 0xF0FEFA79, 0xF101FA73, 0xF103FA6D, 0xF105FA67,
    0xF107FA61, 0xF109FA5B, 0xF10CFA55, 0xF10EFA4F, 0xF110FA4A, 0xF112FA44,
    0xF115FA3E, 0xF117FA38, 0xF119FA32, 0xF11CFA2C, 0xF11EFA26, 0xF120FA21,
    0xF123FA1B, 0xF125FA15, 0xF127FA0F, 0xF12AFA09, 0xF12CFA03, 0xF12EF9FE,
    0xF131F9F8, 0xF133F9F2, 0xF135F9EC, 0xF138F9E6, 0xF13AF9E1, 0xF13DF9DB,
    0xF13FF9D5, 0xF141F9CF, 0xF144F9C9, 0xF146F9C4, 0xF149F9BE, 0xF14BF9B8,
    0xF14EF9B2, 0xF150F9AC, 0xF153F9A7, 0xF155F9A1, 0xF158F99B, 0xF15AF995,
    0xF15DF990, 0xF15FF98A, 0xF162F984, 0xF165F97E, 0xF167F979, 0xF16AF973,
    0xF16CF96D, 0xF16FF967, 0xF171F962, 0xF174F95C, 0xF177F956, 0xF179F951,
    0xF17CF94B, 0xF17FF945, 0xF181F93F, 0xF184F93A, 0xF187F934, 0xF189F92E,
    0xF18CF929, 0xF18FF923, 0xF191F91D, 0xF194F918, 0xF197F912, 0xF19AF90C,
    0xF19CF907, 0xF19FF901, 0xF1A2F8FB, 0xF1A5F8F6, 0xF1A7F8F0, 0xF1AAF8EB,
    0xF1ADF8E5, 0xF1B0F8DF, 0xF1B3F8DA, 0xF1B5F8D4, 0xF1B8F8CE, 0xF1BBF8C9,
    0xF1BEF8C3, 0xF1C1F8BE, 0xF1C4F8B8, 0xF1C6F8B2, 0xF1C9F8AD, 0xF1CCF8A7,
    0xF1CFF8A2, 0xF1D2F89C, 0xF1D5F896, 0xF1D8F891, 0xF1DBF88B, 0xF1DEF886,
    0xF1E1F880, 0xF1E4F87B, 0xF1E7F875, 0xF1EAF870, 0xF1EDF86A, 0xF1F0F865,
    0xF1F3F85F, 0xF1F6F85A, 0xF1F9F854, 0xF1FCF84E, 0xF1FFF849, 0xF202F843,
    0xF205F83E, 0xF208F838, 0xF20BF833, 0xF20EF82E, 0xF211F828, 0xF214F823,
    0xF217F81D, 0xF21AF818, 0xF21DF812, 0xF221F80D, 0xF224F807, 0xF227F802,
    0xF22AF7FC, 0xF22DF7F7, 0xF230F7F2, 0xF234F7EC, 0xF237F7E7, 0xF23AF7E1,
    0xF23DF7DC, 0xF240F7D6, 0xF244F7D1, 0xF247F7CC, 0xF24AF7C6, 0xF24DF7C1,
    0xF250F7BB, 0xF254F7B6, 0xF257F7B1, 0xF25AF7AB, 0xF25EF7A6, 0xF261F7A1,
    0xF264F79B, 0xF267F796, 0xF26BF791, 0xF26EF78B, 0xF271F786, 0xF275F781,
    0xF278F77B, 0xF27BF776, 0xF27FF771, 0xF282F76B, 0xF286F766, 0xF289F761,
    0xF28CF75B, 0xF290F756, 0xF293F751, 0xF297F74C, 0xF29AF746, 0xF29EF741,
    0xF2A1F73C, 0xF2A4F737, 0xF2A8F731, 0xF2ABF72C, 0xF2AFF727, 0xF2B2F722,
    0xF2B6F71C, 0xF2B9F717, 0xF2BDF712, 0xF2C0F70D, 0xF2C4F708, 0xF2C7F702,
    0xF2CBF6FD, 0xF2CEF6F8, 0xF2D2F6F3, 0xF2D6F6EE, 0xF2D9F6E8, 0xF2DDF6E3,
    0xF2E0F6DE, 0xF2E4F6D9, 0xF2E8F6D4, 0xF2EBF6CF, 0xF2EFF6C9, 0xF2F2F6C4,
    0xF2F6F6BF, 0xF2FAF6BA, 0xF2FDF6B5, 0xF301F6B0, 0xF305F6AB, 0xF308F6A6,
    0xF30CF6A1, 0xF310F69B, 0xF313F696, 0xF317F691, 0xF31BF68C, 0xF31FF687,
    0xF322F682, 0xF326F67D, 0xF32AF678, 0xF32EF673, 0xF331F66E, 0xF335F669,
    0xF339F664, 0xF33DF65F, 0xF340F65A, 0xF344F655, 0xF348F650, 0xF34CF64B,
    0xF350F646, 0xF354F641, 0xF357F63C, 0xF35BF637, 0xF35FF632, 0xF363F62D,
    0xF367F628, 0xF36BF623, 0xF36FF61E, 0xF372F619, 0xF376F614, 0xF37AF60F,
    0xF37EF60A, 0xF382F605, 0xF386F601, 0xF38AF5FC, 0xF38EF5F7, 0xF392F5F2,
    0xF396F5ED, 0xF39AF5E8, 0xF39EF5E3, 0xF3A2F5DE, 0xF3A6F5DA, 0xF3AAF5D5,
    0xF3AEF5D0, 0xF3B2F5CB, 0xF3B6F5C6, 0xF3BAF5C1, 0xF3BEF5BC, 0xF3C2F5B8,
    0xF3C6F5B3, 0xF3CAF5AE, 0xF3CEF5A9, 0xF3D2F5A4, 0xF3D6F5A0, 0xF3DAF59B,
    0xF3DEF596, 0xF3E2F591, 0xF3E7F58D, 0xF3EBF588, 0xF3EFF583, 0xF3F3F57E,
    0xF3F7F57A, 0xF3FBF575, 0xF3FFF570, 0xF404F56B, 0xF408F567, 0xF40CF562,
    0xF410F55D, 0xF414F559, 0xF418F554, 0xF41DF54F, 0xF421F54B, 0xF425F546,
    0xF429F541, 0xF42EF53D, 0xF432F538, 0xF436F533, 0xF43AF52F, 0xF43FF52A,
    0xF443F525, 0xF447F521, 0xF44BF51C, 0xF450F518, 0xF454F513, 0xF458F50E,
    0xF45DF50A, 0xF461F505, 0xF465F501, 0xF469F4FC, 0xF46EF4F8, 0xF472F4F3,
    0xF477F4EF, 0xF47BF4EA, 0xF47FF4E5, 0xF484F4E1, 0xF488F4DC, 0xF48CF4D8,
    0xF491F4D3, 0xF495F4CF, 0xF49AF4CA, 0xF49EF4C6, 0xF4A2F4C2, 0xF4A7F4BD,
    0xF4ABF4B9, 0xF4B0F4B4, 0xF4B4F4B0, 0xF4B9F4AB, 0xF4BDF4A7, 0xF4C2F4A2,
    0xF4C6F49E, 0xF4CAF49A, 0xF4CFF495, 0xF4D3F491, 0xF4D8F48C, 0xF4DCF488,
    0xF4E1F484, 0xF4E5F47F, 0xF4EAF47B, 0xF4EFF477, 0xF4F3F472, 0xF4F8F46E,
    0xF4FCF469, 0xF501F465, 0xF505F461, 0xF50AF45D, 0xF50EF458, 0xF513F454,
    0xF518F450, 0xF51CF44B, 0xF521F447, 0xF525F443, 0xF52AF43F, 0xF52FF43A,
    0xF533F436, 0xF538F432, 0xF53DF42E, 0xF541F429, 0xF546F425, 0xF54BF421,
    0xF54FF41D, 0xF554F418, 0xF559F414, 0xF55DF410, 0xF562F40C, 0xF567F408,
    0xF56BF404, 0xF570F3FF, 0xF575F3FB, 0xF57AF3F7, 0xF57EF3F3, 0xF583F3EF,
    0xF588F3EB, 0xF58DF3E7, 0xF591F3E2, 0xF596F3DE, 0xF59BF3DA, 0xF5A0F3D6,
    0xF5A4F3D2, 0xF5A9F3CE, 0xF5AEF3CA, 0xF5B3F3C6, 0xF5B8F3C2, 0xF5BCF3BE,
    0xF5C1F3BA, 0xF5C6F3B6, 0xF5CBF3B2, 0xF5D0F3AE, 0xF5D5F3AA, 0xF5DAF3A6,
    0xF5DEF3A2, 0xF5E3F39E, 0xF5E8F39A, 0xF5EDF396, 0xF5F2F392, 0xF5F7F38E,
    0xF5FCF38A, 0xF601F386, 0xF605F382, 0xF60AF37E, 0xF60FF37A, 0xF614F376,
    0xF619F372, 0xF61EF36F, 0xF623F36B, 0xF628F367, 0xF62DF363, 0xF632F35F,
    0xF637F35B, 0xF63CF357, 0xF641F354, 0xF646F350, 0xF64BF34C, 0xF650F348,
    0xF655F344, 0xF65AF340, 0xF65FF33D, 0xF664F339, 0xF669F335, 0xF66EF331,
    0xF673F32E, 0xF678F32A, 0xF67DF326, 0xF682F322, 0xF687F31F, 0xF68CF31B,
    0xF691F317, 0xF696F313, 0xF69BF310, 0xF6A1F30C, 0xF6A6F308, 0xF6ABF305,
    0xF6B0F301, 0xF6B5F2FD, 0xF6BAF2FA, 0xF6BFF2F6, 0xF6C4F2F2, 0xF6C9F2EF,
    0xF6CFF2EB, 0xF6D4F2E8, 0xF6D9F2E4, 0xF6DEF2E0, 0xF6E3F2DD, 0xF6E8F2D9,
    0xF6EEF2D6, 0xF6F3F2D2, 0xF6F8F2CE, 0xF6FDF2CB, 0xF702F2C7, 0xF708F2C4,
    0xF70DF2C0, 0xF712F2BD, 0xF717F2B9, 0xF71CF2B6, 0xF722F2B2, 0xF727F2AF,
    0xF72CF2AB, 0xF731F2A8, 0xF737F2A4, 0xF73CF2A1, 0xF741F29E, 0xF746F29A,
    0xF74CF297, 0xF751F293, 0xF756F290, 0xF75BF28C, 0xF761F289, 0xF766F286,
    0xF76BF282, 0xF771F27F, 0xF776F27B, 0xF77BF278, 0xF781F275, 0xF786F271,
    0xF78BF26E, 0xF791F26B, 0xF796F267, 0xF79BF264, 0xF7A1F261, 0xF7A6F25E,
    0xF7ABF25A, 0xF7B1F257, 0xF7B6F254, 0xF7BBF250, 0xF7C1F24D, 0xF7C6F24A,
    0xF7CCF247, 0xF7D1F244, 0xF7D6F240, 0xF7DCF23D, 0xF7E1F23A, 0xF7E7F237,
    0xF7ECF234, 0xF7F2F230, 0xF7F7F22D, 0xF7FCF22A, 0xF802F227, 0xF807F224,
    0xF80DF221, 0xF812F21D, 0xF818F21A, 0xF81DF217, 0xF823F214, 0xF828F211,
    0xF82EF20E, 0xF833F20B, 0xF838F208, 0xF83EF205, 0xF843F202, 0xF849F1FF,
    0xF84EF1FC, 0xF854F1F9, 0xF85AF1F6, 0xF85FF1F3, 0xF865F1F0, 0xF86AF1ED,
    0xF870F1EA, 0xF875F1E7, 0xF87BF1E4, 0xF880F1E1, 0xF886F1DE, 0xF88BF1DB,
    0xF891F1D8, 0xF896F1D5, 0xF89CF1D2, 0xF8A2F1CF, 0xF8A7F1CC, 0xF8ADF1C9,
    0xF8B2F1C6, 0xF8B8F1C4, 0xF8BEF1C1, 0xF8C3F1BE, 0xF8C9F1BB, 0xF8CEF1B8,
    0xF8D4F1B5, 0xF8DAF1B3, 0xF8DFF1B0, 0xF8E5F1AD, 0xF8EBF1AA, 0xF8F0F1A7,
    0xF8F6F1A5, 0xF8FBF1A2, 0xF901F19F, 0xF907F19C, 0xF90CF19A, 0xF912F197,
    0xF918F194, 0xF91DF191, 0xF923F18F, 0xF929F18C, 0xF92EF189, 0xF934F187,
    0xF93AF184, 0xF93FF181, 0xF945F17F, 0xF94BF17C, 0xF951F179, 0xF956F177,
    0xF95CF174, 0xF962F171, 0xF967F16F, 0xF96DF16C, 0xF973F16A, 0xF979F167,
    0xF97EF165, 0xF984F162, 0xF98AF15F, 0xF990F15D, 0xF995F15A, 0xF99BF158,
    0xF9A1F155, 0xF9A7F153, 0xF9ACF150, 0xF9B2F14E, 0xF9B8F14B, 0xF9BEF149,
    0xF9C4F146, 0xF9C9F144, 0xF9CFF141, 0xF9D5F13F, 0xF9DBF13D, 0xF9E1F13A,
    0xF9E6F138, 0xF9ECF135, 0xF9F2F133, 0xF9F8F131, 0xF9FEF12E, 0xFA03F12C,
    0xFA09F12A, 0xFA0FF127, 0xFA15F125, 0xFA1BF123, 0xFA21F120, 0xFA26F11E,
    0xFA2CF11C, 0xFA32F119, 0xFA38F117, 0xFA3EF115, 0xFA44F112, 0xFA4AF110,
    0xFA4FF10E, 0xFA55F10C, 0xFA5BF109, 0xFA61F107, 0xFA67F105, 0xFA6DF103,
    0xFA73F101, 0xFA79F0FE, 0xFA7FF0FC, 0xFA84F0FA, 0xFA8AF0F8, 0xFA90F0F6,
    0xFA96F0F4, 0xFA9CF0F2, 0xFAA2F0EF, 0xFAA8F0ED, 0xFAAEF0EB, 0xFAB4F0E9,
    0xFABAF0E7, 0xFAC0F0E5, 0xFAC6F0E3, 0xFACCF0E1, 0xFAD1F0DF, 0xFAD7F0DD,
    0xFADDF0DB, 0xFAE3F0D9, 0xFAE9F0D7, 0xFAEFF0D5, 0xFAF5F0D3, 0xFAFBF0D1,
    0xFB01F0CF, 0xFB07F0CD, 0xFB0DF0CB, 0xFB13F0C9, 0xFB19F0C7, 0xFB1FF0C5,
    0xFB25F0C3, 0xFB2BF0C1, 0xFB31F0BF, 0xFB37F0BD, 0xFB3DF0BB, 0xFB43F0BA,
    0xFB49F0B8, 0xFB4FF0B6, 0xFB55F0B4, 0xFB5BF0B2, 0xFB61F0B0, 0xFB67F0AF,
    0xFB6DF0AD, 0xFB73F0AB, 0xFB79F0A9, 0xFB7FF0A7, 0xFB85F0A6, 0xFB8BF0A4,
    0xFB91F0A2, 0xFB97F0A0, 0xFB9DF09F, 0xFBA3F09D, 0xFBA9F09B, 0xFBAFF099,
    0xFBB5F098, 0xFBBCF096, 0xFBC2F094, 0xFBC8F093, 0xFBCEF091, 0xFBD4F08F,
    0xFBDAF08E, 0xFBE0F08C, 0xFBE6F08A, 0xFBECF089, 0xFBF2F087, 0xFBF8F086,
    0xFBFEF084, 0xFC04F083, 0xFC0AF081, 0xFC11F07F, 0xFC17F07E, 0xFC1DF07C,
    0xFC23F07B, 0xFC29F079, 0xFC2FF078, 0xFC35F076, 0xFC3BF075, 0xFC41F073,
    0xFC47F072, 0xFC4EF070, 0xFC54F06F, 0xFC5AF06D, 0xFC60F06C, 0xFC66F06B,
    0xFC6CF069, 0xFC72F068, 0xFC78F066, 0xFC7FF065, 0xFC85F064, 0xFC8BF062,
    0xFC91F061, 0xFC97F05F, 0xFC9DF05E, 0xFCA3F05D, 0xFCAAF05B, 0xFCB0F05A,
    0xFCB6F059, 0xFCBCF058, 0xFCC2F056, 0xFCC8F055, 0xFCCEF054, 0xFCD5F052,
    0xFCDBF051, 0xFCE1F050, 0xFCE7F04F, 0xFCEDF04D, 0xFCF3F04C, 0xFCFAF04B,
    0xFD00F04A, 0xFD06F049, 0xFD0CF048, 0xFD12F046, 0xFD18F045, 0xFD1FF044,
    0xFD25F043, 0xFD2BF042, 0xFD31F041, 0xFD37F040, 0xFD3EF03E, 0xFD44F03D,
    0xFD4AF03C, 0xFD50F03B, 0xFD56F03A, 0xFD5DF039, 0xFD63F038, 0xFD69F037,
    0xFD6FF036, 0xFD75F035, 0xFD7CF034, 0xFD82F033, 0xFD88F032, 0xFD8EF031,
    0xFD94F030, 0xFD9BF02F, 0xFDA1F02E, 0xFDA7F02D, 0xFDADF02C, 0xFDB3F02B,
    0xFDBAF02B, 0xFDC0F02A, 0xFDC6F029, 0xFDCCF028, 0xFDD3F027, 0xFDD9F026,
    0xFDDFF025, 0xFDE5F024, 0xFDEBF024, 0xFDF2F023, 0xFDF8F022, 0xFDFEF021,
    0xFE04F020, 0xFE0BF020, 0xFE11F01F, 0xFE17F01E, 0xFE1DF01D, 0xFE24F01D,
    0xFE2AF01C, 0xFE30F01B, 0xFE36F01A, 0xFE3DF01A, 0xFE43F019, 0xFE49F018,
    0xFE4FF018, 0xFE56F017, 0xFE5CF016, 0xFE62F016, 0xFE68F015, 0xFE6FF014,
    0xFE75F014, 0xFE7BF013, 0xFE81F013, 0xFE88F012, 0xFE8EF011, 0xFE94F011,
    0xFE9AF010, 0xFEA1F010, 0xFEA7F00F, 0xFEADF00F, 0xFEB3F00E, 0xFEBAF00E,
    0xFEC0F00D, 0xFEC6F00D, 0xFECCF00C, 0xFED3F00C, 0xFED9F00B, 0xFEDFF00B,
    0xFEE5F00A, 0xFEECF00A, 0xFEF2F009, 0xFEF8F009, 0xFEFFF008, 0xFF05F008,
    0xFF0BF008, 0xFF11F007, 0xFF18F007, 0xFF1EF007, 0xFF24F006, 0xFF2AF006,
    0xFF31F006, 0xFF37F005, 0xFF3DF005, 0xFF44F005, 0xFF4AF004, 0xFF50F004,
    0xFF56F004, 0xFF5DF004, 0xFF63F003, 0xFF69F003, 0xFF70F003, 0xFF76F003,
    0xFF7CF002, 0xFF82F002, 0xFF89F002, 0xFF8FF002, 0xFF95F002, 0xFF9BF001,
    0xFFA2F001, 0xFFA8F001, 0xFFAEF001, 0xFFB5F001, 0xFFBBF001, 0xFFC1F001,
    0xFFC7F000, 0xFFCEF000, 0xFFD4F000, 0xFFDAF000, 0xFFE1F000, 0xFFE7F000,
    0xFFEDF000, 0xFFF3F000, 0xFFFAF000, 0xF000,
};

u32 sincos_deg270[220] = {
    0xF000, 0x6F000, 0xDF000, 0x13F000, 0x19F000, 0x1FF000,
    0x26F000, 0x2CF000, 0x32F000, 0x39F000, 0x3FF001, 0x45F001,
    0x4BF001, 0x52F001, 0x58F001, 0x5EF001, 0x65F001, 0x6BF002,
    0x71F002, 0x77F002, 0x7EF002, 0x84F002, 0x8AF003, 0x90F003,
    0x97F003, 0x9DF003, 0xA3F004, 0xAAF004, 0xB0F004, 0xB6F004,
    0xBCF005, 0xC3F005, 0xC9F005, 0xCFF006, 0xD6F006, 0xDCF006,
    0xE2F007, 0xE8F007, 0xEFF007, 0xF5F008, 0xFBF008, 0x101F008,
    0x108F009, 0x10EF009, 0x114F00A, 0x11BF00A, 0x121F00B, 0x127F00B,
    0x12DF00C, 0x134F00C, 0x13AF00D, 0x140F00D, 0x146F00E, 0x14DF00E,
    0x153F00F, 0x159F00F, 0x15FF010, 0x166F010, 0x16CF011, 0x172F011,
    0x178F012, 0x17FF013, 0x185F013, 0x18BF014, 0x191F014, 0x198F015,
    0x19EF016, 0x1A4F016, 0x1AAF017, 0x1B1F018, 0x1B7F018, 0x1BDF019,
    0x1C3F01A, 0x1CAF01A, 0x1D0F01B, 0x1D6F01C, 0x1DCF01D, 0x1E3F01D,
    0x1E9F01E, 0x1EFF01F, 0x1F5F020, 0x1FCF020, 0x202F021, 0x208F022,
    0x20EF023, 0x215F024, 0x21BF024, 0x221F025, 0x227F026, 0x22DF027,
    0x234F028, 0x23AF029, 0x240F02A, 0x246F02B, 0x24DF02B, 0x253F02C,
    0x259F02D, 0x25FF02E, 0x265F02F, 0x26CF030, 0x272F031, 0x278F032,
    0x27EF033, 0x284F034, 0x28BF035, 0x291F036, 0x297F037, 0x29DF038,
    0x2A3F039, 0x2AAF03A, 0x2B0F03B, 0x2B6F03C, 0x2BCF03D, 0x2C2F03E,
    0x2C9F040, 0x2CFF041, 0x2D5F042, 0x2DBF043, 0x2E1F044, 0x2E8F045,
    0x2EEF046, 0x2F4F048, 0x2FAF049, 0x300F04A, 0x306F04B, 0x30DF04C,
    0x313F04D, 0x319F04F, 0x31FF050, 0x325F051, 0x32BF052, 0x332F054,
    0x338F055, 0x33EF056, 0x344F058, 0x34AF059, 0x350F05A, 0x356F05B,
    0x35DF05D, 0x363F05E, 0x369F05F, 0x36FF061, 0x375F062, 0x37BF064,
    0x381F065, 0x388F066, 0x38EF068, 0x394F069, 0x39AF06B, 0x3A0F06C,
    0x3A6F06D, 0x3ACF06F, 0x3B2F070, 0x3B9F072, 0x3BFF073, 0x3C5F075,
    0x3CBF076, 0x3D1F078, 0x3D7F079, 0x3DDF07B, 0x3E3F07C, 0x3E9F07E,
    0x3EFF07F, 0x3F6F081, 0x3FCF083, 0x402F084, 0x408F086, 0x40EF087,
    0x414F089, 0x41AF08A, 0x420F08C, 0x426F08E, 0x42CF08F, 0x432F091,
    0x438F093, 0x43EF094, 0x444F096, 0x44BF098, 0x451F099, 0x457F09B,
    0x45DF09D, 0x463F09F, 0x469F0A0, 0x46FF0A2, 0x475F0A4, 0x47BF0A6,
    0x481F0A7, 0x487F0A9, 0x48DF0AB, 0x493F0AD, 0x499F0AF, 0x49FF0B0,
    0x4A5F0B2, 0x4ABF0B4, 0x4B1F0B6, 0x4B7F0B8, 0x4BDF0BA, 0x4C3F0BB,
    0x4C9F0BD, 0x4CFF0BF, 0x4D5F0C1, 0x4DBF0C3, 0x4E1F0C5, 0x4E7F0C7,
    0x4EDF0C9, 0x4F3F0CB, 0x4F9F0CD, 0x4FFF0CF, 0x505F0D1, 0x50BF0D3,
    0x511F0D5, 0x517F0D7, 0x51DF0D9, 0x523F0DB, 0x529F0DD, 0x52FF0DF,
    0x534F0E1, 0x53AF0E3, 0x540F0E5, 0x546F0E7,
};

u32 rocket_fuchikoma_asset_s10[119] = {
    0x054CF0E9, 0x0552F0EB, 0x0558F0ED, 0x055EF0EF, 0x0564F0F2, 0x056AF0F4,
    0x0570F0F6, 0x0576F0F8, 0x057CF0FA, 0x0581F0FC, 0x0587F0FE, 0x058DF101,
    0x0593F103, 0x0599F105, 0x059FF107, 0x05A5F109, 0x05ABF10C, 0x05B1F10E,
    0x05B6F110, 0x05BCF112, 0x05C2F115, 0x05C8F117, 0x05CEF119, 0x05D4F11C,
    0x05DAF11E, 0x05DFF120, 0x05E5F123, 0x05EBF125, 0x05F1F127, 0x05F7F12A,
    0x05FDF12C, 0x0602F12E, 0x0608F131, 0x060EF133, 0x0614F135, 0x061AF138,
    0x061FF13A, 0x0625F13D, 0x062BF13F, 0x0631F141, 0x0637F144, 0x063CF146,
    0x0642F149, 0x0648F14B, 0x064EF14E, 0x0654F150, 0x0659F153, 0x065FF155,
    0x0665F158, 0x066BF15A, 0x0670F15D, 0x0676F15F, 0x067CF162, 0x0682F165,
    0x0687F167, 0x068DF16A, 0x0693F16C, 0x0699F16F, 0x069EF171, 0x06A4F174,
    0x06AAF177, 0x06AFF179, 0x06B5F17C, 0x06BBF17F, 0x06C1F181, 0x06C6F184,
    0x06CCF187, 0x06D2F189, 0x06D7F18C, 0x06DDF18F, 0x06E3F191, 0x06E8F194,
    0x06EEF197, 0x06F4F19A, 0x06F9F19C, 0x06FFF19F, 0x0705F1A2, 0x070AF1A5,
    0x0710F1A7, 0x0715F1AA, 0x071BF1AD, 0x0721F1B0, 0x0726F1B3, 0x072CF1B5,
    0x0732F1B8, 0x0737F1BB, 0x073DF1BE, 0x0742F1C1, 0x0748F1C4, 0x074EF1C6,
    0x0753F1C9, 0x0759F1CC, 0x075EF1CF, 0x0764F1D2, 0x076AF1D5, 0x076FF1D8,
    0x0775F1DB, 0x077AF1DE, 0x0780F1E1, 0x0785F1E4, 0x078BF1E7, 0x0790F1EA,
    0x0796F1ED, 0x079BF1F0, 0x07A1F1F3, 0x07A6F1F6, 0x07ACF1F9, 0x07B2F1FC,
    0x07B7F1FF, 0x07BDF202, 0x07C2F205, 0x07C8F208, 0x07CDF20B, 0x07D2F20E,
    0x07D8F211, 0x07DDF214, 0x07E3F217, 0x07E8F21A, 0x07EEF21D,
};

u32 rocket_fuchikoma_jump_table_s10[693] = {
    0x07F3F221, 0x07F9F224, 0x07FEF227, 0x0804F22A, 0x0809F22D, 0x080EF230,
    0x0814F234, 0x0819F237, 0x081FF23A, 0x0824F23D, 0x082AF240, 0x082FF244,
    0x0834F247, 0x083AF24A, 0x083FF24D, 0x0845F250, 0x084AF254, 0x084FF257,
    0x0855F25A, 0x085AF25E, 0x085FF261, 0x0865F264, 0x086AF267, 0x086FF26B,
    0x0875F26E, 0x087AF271, 0x087FF275, 0x0885F278, 0x088AF27B, 0x088FF27F,
    0x0895F282, 0x089AF286, 0x089FF289, 0x08A5F28C, 0x08AAF290, 0x08AFF293,
    0x08B4F297, 0x08BAF29A, 0x08BFF29E, 0x08C4F2A1, 0x08C9F2A4, 0x08CFF2A8,
    0x08D4F2AB, 0x08D9F2AF, 0x08DEF2B2, 0x08E4F2B6, 0x08E9F2B9, 0x08EEF2BD,
    0x08F3F2C0, 0x08F8F2C4, 0x08FEF2C7, 0x0903F2CB, 0x0908F2CE, 0x090DF2D2,
    0x0912F2D6, 0x0918F2D9, 0x091DF2DD, 0x0922F2E0, 0x0927F2E4, 0x092CF2E8,
    0x0931F2EB, 0x0937F2EF, 0x093CF2F2, 0x0941F2F6, 0x0946F2FA, 0x094BF2FD,
    0x0950F301, 0x0955F305, 0x095AF308, 0x095FF30C, 0x0965F310, 0x096AF313,
    0x096FF317, 0x0974F31B, 0x0979F31F, 0x097EF322, 0x0983F326, 0x0988F32A,
    0x098DF32E, 0x0992F331, 0x0997F335, 0x099CF339, 0x09A1F33D, 0x09A6F340,
    0x09ABF344, 0x09B0F348, 0x09B5F34C, 0x09BAF350, 0x09BFF354, 0x09C4F357,
    0x09C9F35B, 0x09CEF35F, 0x09D3F363, 0x09D8F367, 0x09DDF36B, 0x09E2F36F,
    0x09E7F372, 0x09ECF376, 0x09F1F37A, 0x09F6F37E, 0x09FBF382, 0x09FFF386,
    0x0A04F38A, 0x0A09F38E, 0x0A0EF392, 0x0A13F396, 0x0A18F39A, 0x0A1DF39E,
    0x0A22F3A2, 0x0A26F3A6, 0x0A2BF3AA, 0x0A30F3AE, 0x0A35F3B2, 0x0A3AF3B6,
    0x0A3FF3BA, 0x0A44F3BE, 0x0A48F3C2, 0x0A4DF3C6, 0x0A52F3CA, 0x0A57F3CE,
    0x0A5CF3D2, 0x0A60F3D6, 0x0A65F3DA, 0x0A6AF3DE, 0x0A6FF3E2, 0x0A73F3E7,
    0x0A78F3EB, 0x0A7DF3EF, 0x0A82F3F3, 0x0A86F3F7, 0x0A8BF3FB, 0x0A90F3FF,
    0x0A95F404, 0x0A99F408, 0x0A9EF40C, 0x0AA3F410, 0x0AA7F414, 0x0AACF418,
    0x0AB1F41D, 0x0AB5F421, 0x0ABAF425, 0x0ABFF429, 0x0AC3F42E, 0x0AC8F432,
    0x0ACDF436, 0x0AD1F43A, 0x0AD6F43F, 0x0ADBF443, 0x0ADFF447, 0x0AE4F44B,
    0x0AE8F450, 0x0AEDF454, 0x0AF2F458, 0x0AF6F45D, 0x0AFBF461, 0x0AFFF465,
    0x0B04F469, 0x0B08F46E, 0x0B0DF472, 0x0B11F477, 0x0B16F47B, 0x0B1BF47F,
    0x0B1FF484, 0x0B24F488, 0x0B28F48C, 0x0B2DF491, 0x0B31F495, 0x0B36F49A,
    0x0B3AF49E, 0x0B3EF4A2, 0x0B43F4A7, 0x0B47F4AB, 0x0B4CF4B0, 0x0B50F4B4,
    0x0B55F4B9, 0x0B59F4BD, 0x0B5EF4C2, 0x0B62F4C6, 0x0B66F4CA, 0x0B6BF4CF,
    0x0B6FF4D3, 0x0B74F4D8, 0x0B78F4DC, 0x0B7CF4E1, 0x0B81F4E5, 0x0B85F4EA,
    0x0B89F4EF, 0x0B8EF4F3, 0x0B92F4F8, 0x0B97F4FC, 0x0B9BF501, 0x0B9FF505,
    0x0BA3F50A, 0x0BA8F50E, 0x0BACF513, 0x0BB0F518, 0x0BB5F51C, 0x0BB9F521,
    0x0BBDF525, 0x0BC1F52A, 0x0BC6F52F, 0x0BCAF533, 0x0BCEF538, 0x0BD2F53D,
    0x0BD7F541, 0x0BDBF546, 0x0BDFF54B, 0x0BE3F54F, 0x0BE8F554, 0x0BECF559,
    0x0BF0F55D, 0x0BF4F562, 0x0BF8F567, 0x0BFCF56B, 0x0C01F570, 0x0C05F575,
    0x0C09F57A, 0x0C0DF57E, 0x0C11F583, 0x0C15F588, 0x0C19F58D, 0x0C1EF591,
    0x0C22F596, 0x0C26F59B, 0x0C2AF5A0, 0x0C2EF5A4, 0x0C32F5A9, 0x0C36F5AE,
    0x0C3AF5B3, 0x0C3EF5B8, 0x0C42F5BC, 0x0C46F5C1, 0x0C4AF5C6, 0x0C4EF5CB,
    0x0C52F5D0, 0x0C56F5D5, 0x0C5AF5DA, 0x0C5EF5DE, 0x0C62F5E3, 0x0C66F5E8,
    0x0C6AF5ED, 0x0C6EF5F2, 0x0C72F5F7, 0x0C76F5FC, 0x0C7AF601, 0x0C7EF605,
    0x0C82F60A, 0x0C86F60F, 0x0C8AF614, 0x0C8EF619, 0x0C91F61E, 0x0C95F623,
    0x0C99F628, 0x0C9DF62D, 0x0CA1F632, 0x0CA5F637, 0x0CA9F63C, 0x0CACF641,
    0x0CB0F646, 0x0CB4F64B, 0x0CB8F650, 0x0CBCF655, 0x0CC0F65A, 0x0CC3F65F,
    0x0CC7F664, 0x0CCBF669, 0x0CCFF66E, 0x0CD2F673, 0x0CD6F678, 0x0CDAF67D,
    0x0CDEF682, 0x0CE1F687, 0x0CE5F68C, 0x0CE9F691, 0x0CEDF696, 0x0CF0F69B,
    0x0CF4F6A1, 0x0CF8F6A6, 0x0CFBF6AB, 0x0CFFF6B0, 0x0D03F6B5, 0x0D06F6BA,
    0x0D0AF6BF, 0x0D0EF6C4, 0x0D11F6C9, 0x0D15F6CF, 0x0D18F6D4, 0x0D1CF6D9,
    0x0D20F6DE, 0x0D23F6E3, 0x0D27F6E8, 0x0D2AF6EE, 0x0D2EF6F3, 0x0D32F6F8,
    0x0D35F6FD, 0x0D39F702, 0x0D3CF708, 0x0D40F70D, 0x0D43F712, 0x0D47F717,
    0x0D4AF71C, 0x0D4EF722, 0x0D51F727, 0x0D55F72C, 0x0D58F731, 0x0D5CF737,
    0x0D5FF73C, 0x0D62F741, 0x0D66F746, 0x0D69F74C, 0x0D6DF751, 0x0D70F756,
    0x0D74F75B, 0x0D77F761, 0x0D7AF766, 0x0D7EF76B, 0x0D81F771, 0x0D85F776,
    0x0D88F77B, 0x0D8BF781, 0x0D8FF786, 0x0D92F78B, 0x0D95F791, 0x0D99F796,
    0x0D9CF79B, 0x0D9FF7A1, 0x0DA2F7A6, 0x0DA6F7AB, 0x0DA9F7B1, 0x0DACF7B6,
    0x0DB0F7BB, 0x0DB3F7C1, 0x0DB6F7C6, 0x0DB9F7CC, 0x0DBCF7D1, 0x0DC0F7D6,
    0x0DC3F7DC, 0x0DC6F7E1, 0x0DC9F7E7, 0x0DCCF7EC, 0x0DD0F7F2, 0x0DD3F7F7,
    0x0DD6F7FC, 0x0DD9F802, 0x0DDCF807, 0x0DDFF80D, 0x0DE3F812, 0x0DE6F818,
    0x0DE9F81D, 0x0DECF823, 0x0DEFF828, 0x0DF2F82E, 0x0DF5F833, 0x0DF8F838,
    0x0DFBF83E, 0x0DFEF843, 0x0E01F849, 0x0E04F84E, 0x0E07F854, 0x0E0AF85A,
    0x0E0DF85F, 0x0E10F865, 0x0E13F86A, 0x0E16F870, 0x0E19F875, 0x0E1CF87B,
    0x0E1FF880, 0x0E22F886, 0x0E25F88B, 0x0E28F891, 0x0E2BF896, 0x0E2EF89C,
    0x0E31F8A2, 0x0E34F8A7, 0x0E37F8AD, 0x0E3AF8B2, 0x0E3CF8B8, 0x0E3FF8BE,
    0x0E42F8C3, 0x0E45F8C9, 0x0E48F8CE, 0x0E4BF8D4, 0x0E4DF8DA, 0x0E50F8DF,
    0x0E53F8E5, 0x0E56F8EB, 0x0E59F8F0, 0x0E5BF8F6, 0x0E5EF8FB, 0x0E61F901,
    0x0E64F907, 0x0E66F90C, 0x0E69F912, 0x0E6CF918, 0x0E6FF91D, 0x0E71F923,
    0x0E74F929, 0x0E77F92E, 0x0E79F934, 0x0E7CF93A, 0x0E7FF93F, 0x0E81F945,
    0x0E84F94B, 0x0E87F951, 0x0E89F956, 0x0E8CF95C, 0x0E8FF962, 0x0E91F967,
    0x0E94F96D, 0x0E96F973, 0x0E99F979, 0x0E9BF97E, 0x0E9EF984, 0x0EA1F98A,
    0x0EA3F990, 0x0EA6F995, 0x0EA8F99B, 0x0EABF9A1, 0x0EADF9A7, 0x0EB0F9AC,
    0x0EB2F9B2, 0x0EB5F9B8, 0x0EB7F9BE, 0x0EBAF9C4, 0x0EBCF9C9, 0x0EBFF9CF,
    0x0EC1F9D5, 0x0EC3F9DB, 0x0EC6F9E1, 0x0EC8F9E6, 0x0ECBF9EC, 0x0ECDF9F2,
    0x0ECFF9F8, 0x0ED2F9FE, 0x0ED4FA03, 0x0ED6FA09, 0x0ED9FA0F, 0x0EDBFA15,
    0x0EDDFA1B, 0x0EE0FA21, 0x0EE2FA26, 0x0EE4FA2C, 0x0EE7FA32, 0x0EE9FA38,
    0x0EEBFA3E, 0x0EEEFA44, 0x0EF0FA4A, 0x0EF2FA4F, 0x0EF4FA55, 0x0EF7FA5B,
    0x0EF9FA61, 0x0EFBFA67, 0x0EFDFA6D, 0x0EFFFA73, 0x0F02FA79, 0x0F04FA7F,
    0x0F06FA84, 0x0F08FA8A, 0x0F0AFA90, 0x0F0CFA96, 0x0F0EFA9C, 0x0F11FAA2,
    0x0F13FAA8, 0x0F15FAAE, 0x0F17FAB4, 0x0F19FABA, 0x0F1BFAC0, 0x0F1DFAC6,
    0x0F1FFACC, 0x0F21FAD1, 0x0F23FAD7, 0x0F25FADD, 0x0F27FAE3, 0x0F29FAE9,
    0x0F2BFAEF, 0x0F2DFAF5, 0x0F2FFAFB, 0x0F31FB01, 0x0F33FB07, 0x0F35FB0D,
    0x0F37FB13, 0x0F39FB19, 0x0F3BFB1F, 0x0F3DFB25, 0x0F3FFB2B, 0x0F41FB31,
    0x0F43FB37, 0x0F45FB3D, 0x0F46FB43, 0x0F48FB49, 0x0F4AFB4F, 0x0F4CFB55,
    0x0F4EFB5B, 0x0F50FB61, 0x0F51FB67, 0x0F53FB6D, 0x0F55FB73, 0x0F57FB79,
    0x0F59FB7F, 0x0F5AFB85, 0x0F5CFB8B, 0x0F5EFB91, 0x0F60FB97, 0x0F61FB9D,
    0x0F63FBA3, 0x0F65FBA9, 0x0F67FBAF, 0x0F68FBB5, 0x0F6AFBBC, 0x0F6CFBC2,
    0x0F6DFBC8, 0x0F6FFBCE, 0x0F71FBD4, 0x0F72FBDA, 0x0F74FBE0, 0x0F76FBE6,
    0x0F77FBEC, 0x0F79FBF2, 0x0F7AFBF8, 0x0F7CFBFE, 0x0F7DFC04, 0x0F7FFC0A,
    0x0F81FC11, 0x0F82FC17, 0x0F84FC1D, 0x0F85FC23, 0x0F87FC29, 0x0F88FC2F,
    0x0F8AFC35, 0x0F8BFC3B, 0x0F8DFC41, 0x0F8EFC47, 0x0F90FC4E, 0x0F91FC54,
    0x0F93FC5A, 0x0F94FC60, 0x0F95FC66, 0x0F97FC6C, 0x0F98FC72, 0x0F9AFC78,
    0x0F9BFC7F, 0x0F9CFC85, 0x0F9EFC8B, 0x0F9FFC91, 0x0FA1FC97, 0x0FA2FC9D,
    0x0FA3FCA3, 0x0FA5FCAA, 0x0FA6FCB0, 0x0FA7FCB6, 0x0FA8FCBC, 0x0FAAFCC2,
    0x0FABFCC8, 0x0FACFCCE, 0x0FAEFCD5, 0x0FAFFCDB, 0x0FB0FCE1, 0x0FB1FCE7,
    0x0FB3FCED, 0x0FB4FCF3, 0x0FB5FCFA, 0x0FB6FD00, 0x0FB7FD06, 0x0FB8FD0C,
    0x0FBAFD12, 0x0FBBFD18, 0x0FBCFD1F, 0x0FBDFD25, 0x0FBEFD2B, 0x0FBFFD31,
    0x0FC0FD37, 0x0FC2FD3E, 0x0FC3FD44, 0x0FC4FD4A, 0x0FC5FD50, 0x0FC6FD56,
    0x0FC7FD5D, 0x0FC8FD63, 0x0FC9FD69, 0x0FCAFD6F, 0x0FCBFD75, 0x0FCCFD7C,
    0x0FCDFD82, 0x0FCEFD88, 0x0FCFFD8E, 0x0FD0FD94, 0x0FD1FD9B, 0x0FD2FDA1,
    0x0FD3FDA7, 0x0FD4FDAD, 0x0FD5FDB3, 0x0FD5FDBA, 0x0FD6FDC0, 0x0FD7FDC6,
    0x0FD8FDCC, 0x0FD9FDD3, 0x0FDAFDD9, 0x0FDBFDDF, 0x0FDCFDE5, 0x0FDCFDEB,
    0x0FDDFDF2, 0x0FDEFDF8, 0x0FDFFDFE, 0x0FE0FE04, 0x0FE0FE0B, 0x0FE1FE11,
    0x0FE2FE17, 0x0FE3FE1D, 0x0FE3FE24, 0x0FE4FE2A, 0x0FE5FE30, 0x0FE6FE36,
    0x0FE6FE3D, 0x0FE7FE43, 0x0FE8FE49, 0x0FE8FE4F, 0x0FE9FE56, 0x0FEAFE5C,
    0x0FEAFE62, 0x0FEBFE68, 0x0FECFE6F, 0x0FECFE75, 0x0FEDFE7B, 0x0FEDFE81,
    0x0FEEFE88, 0x0FEFFE8E, 0x0FEFFE94, 0x0FF0FE9A, 0x0FF0FEA1, 0x0FF1FEA7,
    0x0FF1FEAD, 0x0FF2FEB3, 0x0FF2FEBA, 0x0FF3FEC0, 0x0FF3FEC6, 0x0FF4FECC,
    0x0FF4FED3, 0x0FF5FED9, 0x0FF5FEDF, 0x0FF6FEE5, 0x0FF6FEEC, 0x0FF7FEF2,
    0x0FF7FEF8, 0x0FF8FEFF, 0x0FF8FF05, 0x0FF8FF0B, 0x0FF9FF11, 0x0FF9FF18,
    0x0FF9FF1E, 0x0FFAFF24, 0x0FFAFF2A, 0x0FFAFF31, 0x0FFBFF37, 0x0FFBFF3D,
    0x0FFBFF44, 0x0FFCFF4A, 0x0FFCFF50, 0x0FFCFF56, 0x0FFCFF5D, 0x0FFDFF63,
    0x0FFDFF69, 0x0FFDFF70, 0x0FFDFF76, 0x0FFEFF7C, 0x0FFEFF82, 0x0FFEFF89,
    0x0FFEFF8F, 0x0FFEFF95, 0x0FFFFF9B, 0x0FFFFFA2, 0x0FFFFFA8, 0x0FFFFFAE,
    0x0FFFFFB5, 0x0FFFFFBB, 0x0FFFFFC1, 0x1000FFC7, 0x1000FFCE, 0x1000FFD4,
    0x1000FFDA, 0x1000FFE1, 0x1000FFE7, 0x1000FFED, 0x1000FFF3, 0x1000FFFA,
    0x10000000, 0x0006FFFF, 0x00070000, 0xFFFF0002, 0x00000001, 0x00050004,
    0x0006FFFF, 0x00040003, 0xFFFF0002,
};

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_8011D310[5] = {0};

#include "../stage/data/d_8011D324.c"

#include "../stage/data/video_mode_id.c"

#include "../stage/data/tint_scale_r.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_8011E470[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_8011EA90 = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

s32 key_codes_acquired = 0;

s32 key_codes_complete_flag = 0;

s32 stage_exit_flag = 0;

s32 warehouse_hint_timer = 0;

s32 ambient_sound_timer = 0;

s32 D_8011FF00 = 0;

#include "../stage/data/value_queue_index.c"

#include "../stage/data/giant_robot_systems_active.c"

s32 giant_robot_aim_result = 0;

s32 giant_robot_aim_x = 0;

s32 giant_robot_aim_y = 0;

s32 giant_robot_aim_z = 0;

s32 giant_robot_fx_timer = 0;

s32 giant_robot_fx_active = 0;

Object *giant_robot_fx_owner = NULL;

s32 fade_amount = 0;

s32 fade_dir = 0;

#include "../stage/data/fade_red_obj.c"

#include "../stage/data/frame_work_area.c"

#include "../stage/data/model_slot_count.c"

u32 D_8011FFE8 = 0x00000000;

#include "../stage/data/ring32_index.c"

/* labels inside the objects above */
__asm__(".globl D_80117783\n.set D_80117783, ripple_fx_params+0x3\n"
        ".globl fade_colour_y_to\n.set fade_colour_y_to, fade_colour_y_from+0x2\n"
        ".globl fade_colour_x_to\n.set fade_colour_x_to, fade_colour_x_from+0x2\n"
        ".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl D_8011EA96\n.set D_8011EA96, texture_image+0x2\n"
        ".globl D_80117782\n.set D_80117782, ripple_fx_params+0x2\n"
        ".globl D_80117781\n.set D_80117781, ripple_fx_params+0x1\n"
        ".globl smg_soldier_hit_script\n.set smg_soldier_hit_script, smg_soldier_anims+0x224\n"
        ".globl d_80117788\n.set d_80117788, ripple_fx_params+0x8\n"
        ".globl d_8011778C\n.set d_8011778C, ripple_fx_params+0xC\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl enemy_fuchikoma_key_code_holder_anim_idle\n.set enemy_fuchikoma_key_code_holder_anim_idle, enemy_fuchikoma_key_code_holder_anims+0x0\n"
        ".globl enemy_fuchikoma_key_code_holder_anim_walk\n.set enemy_fuchikoma_key_code_holder_anim_walk, enemy_fuchikoma_key_code_holder_anims+0x8\n"
        ".globl keyholder_fuchikoma_data\n.set keyholder_fuchikoma_data, enemy_fuchikoma_key_code_holder_anims+0x3C\n"
        ".globl enemy_fuchikoma_key_code_holder_start\n.set enemy_fuchikoma_key_code_holder_start, enemy_fuchikoma_key_code_holder_scripts+0x0\n"
        ".globl enemy_fuchikoma_key_code_holder_patrol_start\n.set enemy_fuchikoma_key_code_holder_patrol_start, enemy_fuchikoma_key_code_holder_scripts+0x4\n"
        ".globl enemy_fuchikoma_key_code_holder_patrol_scan\n.set enemy_fuchikoma_key_code_holder_patrol_scan, enemy_fuchikoma_key_code_holder_scripts+0x10\n"
        ".globl enemy_fuchikoma_key_code_holder_aim\n.set enemy_fuchikoma_key_code_holder_aim, enemy_fuchikoma_key_code_holder_scripts+0x24\n"
        ".globl enemy_fuchikoma_key_code_holder_fire_start\n.set enemy_fuchikoma_key_code_holder_fire_start, enemy_fuchikoma_key_code_holder_scripts+0x44\n"
        ".globl enemy_fuchikoma_key_code_holder_fire_burst\n.set enemy_fuchikoma_key_code_holder_fire_burst, enemy_fuchikoma_key_code_holder_scripts+0x54\n"
        ".globl enemy_fuchikoma_key_code_holder_fire_loop\n.set enemy_fuchikoma_key_code_holder_fire_loop, enemy_fuchikoma_key_code_holder_scripts+0x58\n"
        ".globl keyholder_script\n.set keyholder_script, enemy_fuchikoma_key_code_holder_scripts+0x68\n"
        ".globl D_80116F4C\n.set D_80116F4C, enemy_fuchikoma_key_code_holder_scripts+0x84\n"
        ".globl smg_soldier_anim_idle\n.set smg_soldier_anim_idle, smg_soldier_anims+0x0\n"
        ".globl smg_soldier_anim_idle_alt\n.set smg_soldier_anim_idle_alt, smg_soldier_anims+0xC\n"
        ".globl smg_soldier_anim_walk_start\n.set smg_soldier_anim_walk_start, smg_soldier_anims+0x4C\n"
        ".globl smg_soldier_anim_walk\n.set smg_soldier_anim_walk, smg_soldier_anims+0x88\n"
        ".globl smg_soldier_anim_run_start\n.set smg_soldier_anim_run_start, smg_soldier_anims+0xC0\n"
        ".globl smg_soldier_anim_run\n.set smg_soldier_anim_run, smg_soldier_anims+0x108\n"
        ".globl smg_soldier_anim_aim\n.set smg_soldier_anim_aim, smg_soldier_anims+0x13C\n"
        ".globl smg_soldier_anim_hold\n.set smg_soldier_anim_hold, smg_soldier_anims+0x1C8\n"
        ".globl smg_soldier_anim_hit\n.set smg_soldier_anim_hit, smg_soldier_anims+0x1D8\n"
        ".globl smg_soldier_data\n.set smg_soldier_data, smg_soldier_anims+0x204\n"
        ".globl smg_soldier_idle\n.set smg_soldier_idle, smg_soldier_scripts+0x0\n"
        ".globl smg_soldier_idle_pause\n.set smg_soldier_idle_pause, smg_soldier_scripts+0xC\n"
        ".globl smg_soldier_idle_cycle\n.set smg_soldier_idle_cycle, smg_soldier_scripts+0x14\n"
        ".globl smg_soldier_patrol\n.set smg_soldier_patrol, smg_soldier_scripts+0x28\n"
        ".globl smg_soldier_patrol_cycle\n.set smg_soldier_patrol_cycle, smg_soldier_scripts+0x34\n"
        ".globl smg_soldier_patrol_wait\n.set smg_soldier_patrol_wait, smg_soldier_scripts+0x4C\n"
        ".globl smg_soldier_hold\n.set smg_soldier_hold, smg_soldier_scripts+0x58\n"
        ".globl smg_soldier_hold_pause\n.set smg_soldier_hold_pause, smg_soldier_scripts+0x60\n"
        ".globl smg_soldier_hold_cycle\n.set smg_soldier_hold_cycle, smg_soldier_scripts+0x68\n"
        ".globl smg_soldier_walk\n.set smg_soldier_walk, smg_soldier_scripts+0x7C\n"
        ".globl smg_soldier_walk_step\n.set smg_soldier_walk_step, smg_soldier_scripts+0x84\n"
        ".globl smg_soldier_walk_cycle\n.set smg_soldier_walk_cycle, smg_soldier_scripts+0x8C\n"
        ".globl smg_soldier_walk_pause\n.set smg_soldier_walk_pause, smg_soldier_scripts+0xA0\n"
        ".globl smg_soldier_walk_pause_cycle\n.set smg_soldier_walk_pause_cycle, smg_soldier_scripts+0xA8\n"
        ".globl smg_soldier_jump_table\n.set smg_soldier_jump_table, smg_soldier_scripts+0xBC\n"
        ".globl smg_soldier_script\n.set smg_soldier_script, smg_soldier_scripts+0xF4\n"
        ".globl rocket_fuchikoma_anim_idle\n.set rocket_fuchikoma_anim_idle, rocket_fuchikoma_anims+0x0\n"
        ".globl rocket_fuchikoma_anim_fly\n.set rocket_fuchikoma_anim_fly, rocket_fuchikoma_anims+0x8\n"
        ".globl rocket_fuchikoma_anim_detonate\n.set rocket_fuchikoma_anim_detonate, rocket_fuchikoma_anims+0x3C\n"
        ".globl rocket_fuchikoma_anim_detonate_hold\n.set rocket_fuchikoma_anim_detonate_hold, rocket_fuchikoma_anims+0x40\n"
        ".globl rocket_fuchikoma_data\n.set rocket_fuchikoma_data, rocket_fuchikoma_anims+0x48\n"
        ".globl rocket_fuchikoma_idle\n.set rocket_fuchikoma_idle, rocket_fuchikoma_jump_table_streams+0x0\n"
        ".globl rocket_fuchikoma_reset\n.set rocket_fuchikoma_reset, rocket_fuchikoma_jump_table_streams+0xC\n"
        ".globl rocket_fuchikoma_settle\n.set rocket_fuchikoma_settle, rocket_fuchikoma_jump_table_streams+0x1C\n"
        ".globl rocket_fuchikoma_ready\n.set rocket_fuchikoma_ready, rocket_fuchikoma_jump_table_streams+0x30\n"
        ".globl rocket_fuchikoma_aim_start\n.set rocket_fuchikoma_aim_start, rocket_fuchikoma_jump_table_streams+0x3C\n"
        ".globl grenade_fuchikoma_seek\n.set grenade_fuchikoma_seek, rocket_fuchikoma_jump_table_streams+0x48\n"
        ".globl rocket_fuchikoma_approach\n.set rocket_fuchikoma_approach, rocket_fuchikoma_jump_table_streams+0x5C\n"
        ".globl grenade_fuchikoma_track\n.set grenade_fuchikoma_track, rocket_fuchikoma_jump_table_streams+0x6C\n"
        ".globl rocket_fuchikoma_close_in\n.set rocket_fuchikoma_close_in, rocket_fuchikoma_jump_table_streams+0x8C\n"
        ".globl rocket_fuchikoma_brake\n.set rocket_fuchikoma_brake, rocket_fuchikoma_jump_table_streams+0x9C\n"
        ".globl grenade_fuchikoma_wait_stop\n.set grenade_fuchikoma_wait_stop, rocket_fuchikoma_jump_table_streams+0xA4\n"
        ".globl rocket_fuchikoma_fire_wait\n.set rocket_fuchikoma_fire_wait, rocket_fuchikoma_jump_table_streams+0xB4\n"
        ".globl rocket_fuchikoma_fire_start\n.set rocket_fuchikoma_fire_start, rocket_fuchikoma_jump_table_streams+0xC0\n"
        ".globl grenade_fuchikoma_detonate_wait\n.set grenade_fuchikoma_detonate_wait, rocket_fuchikoma_jump_table_streams+0xC4\n"
        ".globl rocket_fuchikoma_reposition\n.set rocket_fuchikoma_reposition, rocket_fuchikoma_jump_table_streams+0xD4\n"
        ".globl rocket_fuchikoma_reposition_face\n.set rocket_fuchikoma_reposition_face, rocket_fuchikoma_jump_table_streams+0xE4\n"
        ".globl rocket_fuchikoma_jump_table\n.set rocket_fuchikoma_jump_table, rocket_fuchikoma_jump_table_streams+0xF4\n"
        ".globl rocket_fuchikoma_script_pos\n.set rocket_fuchikoma_script_pos, rocket_fuchikoma_jump_table_streams+0x134\n"
        ".globl helicopter_script\n.set helicopter_script, helicopter_anims+0x0\n"
        ".globl helicopter_data\n.set helicopter_data, helicopter_anims+0x8\n"
        ".globl helicopter_idle\n.set helicopter_idle, helicopter_scripts+0x0\n"
        ".globl helicopter_pick_state\n.set helicopter_pick_state, helicopter_scripts+0x4\n"
        ".globl helicopter_patrol\n.set helicopter_patrol, helicopter_scripts+0x2C\n"
        ".globl helicopter_patrol_far\n.set helicopter_patrol_far, helicopter_scripts+0x3C\n"
        ".globl helicopter_spin\n.set helicopter_spin, helicopter_scripts+0x4C\n"
        ".globl helicopter_aim\n.set helicopter_aim, helicopter_scripts+0x5C\n"
        ".globl helicopter_approach\n.set helicopter_approach, helicopter_scripts+0x6C\n"
        ".globl helicopter_cooldown\n.set helicopter_cooldown, helicopter_scripts+0x7C\n"
        ".globl helicopter_cooling\n.set helicopter_cooling, helicopter_scripts+0x84\n"
        ".globl helicopter_cooldown_end\n.set helicopter_cooldown_end, helicopter_scripts+0x90\n"
        ".globl helicopter_label_table\n.set helicopter_label_table, helicopter_scripts+0x98\n"
        ".globl helicopter_script_entry\n.set helicopter_script_entry, helicopter_scripts+0xC0\n"
        ".globl giant_robot_m1_boss_anim_stand\n.set giant_robot_m1_boss_anim_stand, giant_robot_m1_boss_anims+0x0\n"
        ".globl giant_robot_m1_boss_anim_walk_start\n.set giant_robot_m1_boss_anim_walk_start, giant_robot_m1_boss_anims+0xC\n"
        ".globl giant_robot_m1_boss_anim_walk\n.set giant_robot_m1_boss_anim_walk, giant_robot_m1_boss_anims+0x18\n"
        ".globl giant_robot_m1_boss_anim_walk_stop\n.set giant_robot_m1_boss_anim_walk_stop, giant_robot_m1_boss_anims+0x88\n"
        ".globl giant_robot_m1_boss_anim_idle\n.set giant_robot_m1_boss_anim_idle, giant_robot_m1_boss_anims+0x94\n"
        ".globl giant_robot_m1_boss_anim_idle_hold\n.set giant_robot_m1_boss_anim_idle_hold, giant_robot_m1_boss_anims+0x164\n"
        ".globl giant_robot_m1_boss_anim_settle\n.set giant_robot_m1_boss_anim_settle, giant_robot_m1_boss_anims+0x16C\n"
        ".globl giant_robot_m1_boss_anim_dormant\n.set giant_robot_m1_boss_anim_dormant, giant_robot_m1_boss_anims+0x178\n"
        ".globl giant_robot_m1_boss_anim_rise\n.set giant_robot_m1_boss_anim_rise, giant_robot_m1_boss_anims+0x180\n"
        ".globl giant_robot_m1_boss_anim_charge_ramp\n.set giant_robot_m1_boss_anim_charge_ramp, giant_robot_m1_boss_anims+0x204\n"
        ".globl giant_robot_m1_boss_anim_charge_hold\n.set giant_robot_m1_boss_anim_charge_hold, giant_robot_m1_boss_anims+0x238\n"
        ".globl giant_robot_m1_boss_anim_release\n.set giant_robot_m1_boss_anim_release, giant_robot_m1_boss_anims+0x240\n"
        ".globl giant_robot_m1_boss_anim_release_hold\n.set giant_robot_m1_boss_anim_release_hold, giant_robot_m1_boss_anims+0x260\n"
        ".globl giant_robot_m1_boss_anim_return\n.set giant_robot_m1_boss_anim_return, giant_robot_m1_boss_anims+0x268\n"
        ".globl giant_robot_data\n.set giant_robot_data, giant_robot_m1_boss_anims+0x288\n"
        ".globl giant_robot_m1_boss_intro\n.set giant_robot_m1_boss_intro, giant_robot_m1_boss_scripts+0x0\n"
        ".globl giant_robot_m1_boss_intro_wait\n.set giant_robot_m1_boss_intro_wait, giant_robot_m1_boss_scripts+0x2C\n"
        ".globl giant_robot_m1_boss_intro_engage\n.set giant_robot_m1_boss_intro_engage, giant_robot_m1_boss_scripts+0x3C\n"
        ".globl giant_robot_m1_boss_idle_enter\n.set giant_robot_m1_boss_idle_enter, giant_robot_m1_boss_scripts+0x4C\n"
        ".globl giant_robot_m1_boss_idle\n.set giant_robot_m1_boss_idle, giant_robot_m1_boss_scripts+0x50\n"
        ".globl giant_robot_m1_boss_idle_wait\n.set giant_robot_m1_boss_idle_wait, giant_robot_m1_boss_scripts+0x68\n"
        ".globl giant_robot_m1_boss_attack_choice\n.set giant_robot_m1_boss_attack_choice, giant_robot_m1_boss_scripts+0x78\n"
        ".globl giant_robot_m1_boss_sweep_pos\n.set giant_robot_m1_boss_sweep_pos, giant_robot_m1_boss_scripts+0x84\n"
        ".globl giant_robot_m1_boss_fire_burst\n.set giant_robot_m1_boss_fire_burst, giant_robot_m1_boss_scripts+0x8C\n"
        ".globl giant_robot_m1_boss_fire_loop\n.set giant_robot_m1_boss_fire_loop, giant_robot_m1_boss_scripts+0x94\n"
        ".globl giant_robot_m1_boss_sweep_neg\n.set giant_robot_m1_boss_sweep_neg, giant_robot_m1_boss_scripts+0x98\n"
        ".globl giant_robot_m1_boss_sweep_neg_burst\n.set giant_robot_m1_boss_sweep_neg_burst, giant_robot_m1_boss_scripts+0xA0\n"
        ".globl giant_robot_m1_boss_sweep_neg_burst_loop\n.set giant_robot_m1_boss_sweep_neg_burst_loop, giant_robot_m1_boss_scripts+0xA8\n"
        ".globl giant_robot_m1_boss_sweep_pos_again\n.set giant_robot_m1_boss_sweep_pos_again, giant_robot_m1_boss_scripts+0xAC\n"
        ".globl giant_robot_m1_boss_sweep_pos_again_burst\n.set giant_robot_m1_boss_sweep_pos_again_burst, giant_robot_m1_boss_scripts+0xB4\n"
        ".globl giant_robot_m1_boss_sweep_pos_again_burst_loop\n.set giant_robot_m1_boss_sweep_pos_again_burst_loop, giant_robot_m1_boss_scripts+0xBC\n"
        ".globl giant_robot_m1_boss_sweep_neg_again\n.set giant_robot_m1_boss_sweep_neg_again, giant_robot_m1_boss_scripts+0xC4\n"
        ".globl giant_robot_m1_boss_sweep_neg_again_burst\n.set giant_robot_m1_boss_sweep_neg_again_burst, giant_robot_m1_boss_scripts+0xCC\n"
        ".globl giant_robot_m1_boss_sweep_neg_again_burst_loop\n.set giant_robot_m1_boss_sweep_neg_again_burst_loop, giant_robot_m1_boss_scripts+0xD4\n"
        ".globl giant_robot_m1_boss_sweep_pos_long\n.set giant_robot_m1_boss_sweep_pos_long, giant_robot_m1_boss_scripts+0xD8\n"
        ".globl giant_robot_m1_boss_sweep_pos_long_burst\n.set giant_robot_m1_boss_sweep_pos_long_burst, giant_robot_m1_boss_scripts+0xE0\n"
        ".globl giant_robot_m1_boss_sweep_pos_long_burst_loop\n.set giant_robot_m1_boss_sweep_pos_long_burst_loop, giant_robot_m1_boss_scripts+0xE8\n"
        ".globl giant_robot_m1_boss_sweep_neg_short\n.set giant_robot_m1_boss_sweep_neg_short, giant_robot_m1_boss_scripts+0xEC\n"
        ".globl giant_robot_m1_boss_sweep_neg_short_burst\n.set giant_robot_m1_boss_sweep_neg_short_burst, giant_robot_m1_boss_scripts+0xF4\n"
        ".globl giant_robot_m1_boss_sweep_neg_short_burst_loop\n.set giant_robot_m1_boss_sweep_neg_short_burst_loop, giant_robot_m1_boss_scripts+0xFC\n"
        ".globl giant_robot_m1_boss_sweep_stop\n.set giant_robot_m1_boss_sweep_stop, giant_robot_m1_boss_scripts+0x104\n"
        ".globl giant_robot_m1_boss_sweep_done\n.set giant_robot_m1_boss_sweep_done, giant_robot_m1_boss_scripts+0x10C\n"
        ".globl giant_robot_m1_boss_wait_done\n.set giant_robot_m1_boss_wait_done, giant_robot_m1_boss_scripts+0x118\n"
        ".globl giant_robot_m1_boss_sweep_return\n.set giant_robot_m1_boss_sweep_return, giant_robot_m1_boss_scripts+0x128\n"
        ".globl giant_robot_m1_boss_barrage_enter\n.set giant_robot_m1_boss_barrage_enter, giant_robot_m1_boss_scripts+0x12C\n"
        ".globl giant_robot_m1_boss_barrage_start\n.set giant_robot_m1_boss_barrage_start, giant_robot_m1_boss_scripts+0x130\n"
        ".globl giant_robot_m1_boss_barrage_charge\n.set giant_robot_m1_boss_barrage_charge, giant_robot_m1_boss_scripts+0x150\n"
        ".globl giant_robot_m1_boss_barrage_release\n.set giant_robot_m1_boss_barrage_release, giant_robot_m1_boss_scripts+0x15C\n"
        ".globl giant_robot_m1_boss_barrage_sway\n.set giant_robot_m1_boss_barrage_sway, giant_robot_m1_boss_scripts+0x16C\n"
        ".globl giant_robot_m1_boss_barrage_hold\n.set giant_robot_m1_boss_barrage_hold, giant_robot_m1_boss_scripts+0x180\n"
        ".globl giant_robot_m1_boss_barrage_hold_wait\n.set giant_robot_m1_boss_barrage_hold_wait, giant_robot_m1_boss_scripts+0x18C\n"
        ".globl giant_robot_m1_boss_barrage_end\n.set giant_robot_m1_boss_barrage_end, giant_robot_m1_boss_scripts+0x19C\n"
        ".globl giant_robot_m1_boss_barrage_reset\n.set giant_robot_m1_boss_barrage_reset, giant_robot_m1_boss_scripts+0x1A4\n"
        ".globl giant_robot_m1_boss_barrage_cooldown\n.set giant_robot_m1_boss_barrage_cooldown, giant_robot_m1_boss_scripts+0x1AC\n"
        ".globl giant_robot_m1_boss_retreat\n.set giant_robot_m1_boss_retreat, giant_robot_m1_boss_scripts+0x1BC\n"
        ".globl giant_robot_m1_boss_retreat_wait\n.set giant_robot_m1_boss_retreat_wait, giant_robot_m1_boss_scripts+0x1C8\n"
        ".globl giant_robot_m1_boss_retreat_stop\n.set giant_robot_m1_boss_retreat_stop, giant_robot_m1_boss_scripts+0x1D8\n"
        ".globl giant_robot_m1_boss_retreat_stop_wait\n.set giant_robot_m1_boss_retreat_stop_wait, giant_robot_m1_boss_scripts+0x1EC\n"
        ".globl giant_robot_m1_boss_retreat_walk\n.set giant_robot_m1_boss_retreat_walk, giant_robot_m1_boss_scripts+0x1FC\n"
        ".globl giant_robot_m1_boss_retreat_end\n.set giant_robot_m1_boss_retreat_end, giant_robot_m1_boss_scripts+0x208\n"
        ".globl giant_robot_m1_boss_pause_resume\n.set giant_robot_m1_boss_pause_resume, giant_robot_m1_boss_scripts+0x210\n"
        ".globl giant_robot_m1_boss_halt_wait\n.set giant_robot_m1_boss_halt_wait, giant_robot_m1_boss_scripts+0x21C\n"
        ".globl giant_robot_m1_boss_halt\n.set giant_robot_m1_boss_halt, giant_robot_m1_boss_scripts+0x22C\n"
        ".globl giant_robot_m1_boss_pause_clear_wait\n.set giant_robot_m1_boss_pause_clear_wait, giant_robot_m1_boss_scripts+0x240\n"
        ".globl giant_robot_m1_boss_pause_clear\n.set giant_robot_m1_boss_pause_clear, giant_robot_m1_boss_scripts+0x250\n"
        ".globl giant_robot_m1_boss_fade_wait\n.set giant_robot_m1_boss_fade_wait, giant_robot_m1_boss_scripts+0x258\n"
        ".globl giant_robot_m1_boss_side_fx_start\n.set giant_robot_m1_boss_side_fx_start, giant_robot_m1_boss_scripts+0x264\n"
        ".globl giant_robot_m1_boss_side_fx\n.set giant_robot_m1_boss_side_fx, giant_robot_m1_boss_scripts+0x268\n"
        ".globl giant_robot_m1_boss_side_fx_return\n.set giant_robot_m1_boss_side_fx_return, giant_robot_m1_boss_scripts+0x274\n"
        ".globl giant_robot_m1_boss_pause_retreat_enter\n.set giant_robot_m1_boss_pause_retreat_enter, giant_robot_m1_boss_scripts+0x278\n"
        ".globl giant_robot_m1_boss_pause_then_retreat\n.set giant_robot_m1_boss_pause_then_retreat, giant_robot_m1_boss_scripts+0x27C\n"
        ".globl giant_robot_m1_boss_pause\n.set giant_robot_m1_boss_pause, giant_robot_m1_boss_scripts+0x284\n"
        ".globl giant_robot_m1_boss_pause_end\n.set giant_robot_m1_boss_pause_end, giant_robot_m1_boss_scripts+0x288\n"
        ".globl giant_robot_m1_boss_pause_return\n.set giant_robot_m1_boss_pause_return, giant_robot_m1_boss_scripts+0x290\n"
        ".globl giant_robot_m1_boss_fx_retreat_enter\n.set giant_robot_m1_boss_fx_retreat_enter, giant_robot_m1_boss_scripts+0x294\n"
        ".globl giant_robot_m1_boss_fx_then_retreat\n.set giant_robot_m1_boss_fx_then_retreat, giant_robot_m1_boss_scripts+0x298\n"
        ".globl giant_robot_m1_boss_fx_pause\n.set giant_robot_m1_boss_fx_pause, giant_robot_m1_boss_scripts+0x2A0\n"
        ".globl giant_robot_m1_boss_pause_then_resume\n.set giant_robot_m1_boss_pause_then_resume, giant_robot_m1_boss_scripts+0x2A8\n"
        ".globl giant_robot_m1_boss_resume_return\n.set giant_robot_m1_boss_resume_return, giant_robot_m1_boss_scripts+0x2B0\n"
        ".globl giant_robot_m1_boss_wobble_enter\n.set giant_robot_m1_boss_wobble_enter, giant_robot_m1_boss_scripts+0x2B4\n"
        ".globl giant_robot_m1_boss_wobble\n.set giant_robot_m1_boss_wobble, giant_robot_m1_boss_scripts+0x2B8\n"
        ".globl giant_robot_m1_boss_wobble_neg\n.set giant_robot_m1_boss_wobble_neg, giant_robot_m1_boss_scripts+0x2C4\n"
        ".globl giant_robot_m1_boss_wobble_pos\n.set giant_robot_m1_boss_wobble_pos, giant_robot_m1_boss_scripts+0x340\n"
        ".globl giant_robot_m1_boss_wobble_end\n.set giant_robot_m1_boss_wobble_end, giant_robot_m1_boss_scripts+0x3BC\n"
        ".globl giant_robot_m1_boss_side_fx_enter\n.set giant_robot_m1_boss_side_fx_enter, giant_robot_m1_boss_scripts+0x3C4\n"
        ".globl giant_robot_m1_boss_side_fx_then_next\n.set giant_robot_m1_boss_side_fx_then_next, giant_robot_m1_boss_scripts+0x3C8\n"
        ".globl giant_robot_m1_boss_next_action\n.set giant_robot_m1_boss_next_action, giant_robot_m1_boss_scripts+0x3D0\n"
        ".globl giant_robot_m1_boss_next_return\n.set giant_robot_m1_boss_next_return, giant_robot_m1_boss_scripts+0x3EC\n"
        ".globl giant_robot_m1_boss_turn_enter\n.set giant_robot_m1_boss_turn_enter, giant_robot_m1_boss_scripts+0x3F0\n"
        ".globl giant_robot_m1_boss_turn_check\n.set giant_robot_m1_boss_turn_check, giant_robot_m1_boss_scripts+0x3F4\n"
        ".globl giant_robot_m1_boss_turn_choice\n.set giant_robot_m1_boss_turn_choice, giant_robot_m1_boss_scripts+0x40C\n"
        ".globl giant_robot_m1_boss_pick_idle_or_attack\n.set giant_robot_m1_boss_pick_idle_or_attack, giant_robot_m1_boss_scripts+0x424\n"
        ".globl giant_robot_m1_boss_return_after_pick\n.set giant_robot_m1_boss_return_after_pick, giant_robot_m1_boss_scripts+0x438\n"
        ".globl giant_robot_m1_boss_turn_pick_enter\n.set giant_robot_m1_boss_turn_pick_enter, giant_robot_m1_boss_scripts+0x43C\n"
        ".globl giant_robot_m1_boss_turn_pick\n.set giant_robot_m1_boss_turn_pick, giant_robot_m1_boss_scripts+0x440\n"
        ".globl giant_robot_m1_boss_pick_turn\n.set giant_robot_m1_boss_pick_turn, giant_robot_m1_boss_scripts+0x45C\n"
        ".globl giant_robot_m1_boss_return_after_turn\n.set giant_robot_m1_boss_return_after_turn, giant_robot_m1_boss_scripts+0x47C\n"
        ".globl giant_robot_m1_boss_engage_barrage\n.set giant_robot_m1_boss_engage_barrage, giant_robot_m1_boss_scripts+0x480\n"
        ".globl giant_robot_m1_boss_pick_retreat\n.set giant_robot_m1_boss_pick_retreat, giant_robot_m1_boss_scripts+0x488\n"
        ".globl giant_robot_m1_boss_pick_by_distance\n.set giant_robot_m1_boss_pick_by_distance, giant_robot_m1_boss_scripts+0x490\n"
        ".globl giant_robot_link_data\n.set giant_robot_link_data, giant_robot_m1_boss_scripts+0x4A4\n"
        ".globl D_80118570\n.set D_80118570, giant_robot_m1_boss_scripts+0x5F8\n");
