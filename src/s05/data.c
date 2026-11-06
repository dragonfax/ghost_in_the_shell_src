/* s05 data 0x80115D70-0x80120000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s05_types.h"
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
extern void camouflaged_target_m5_boss_spawn();
extern void camouflaged_target_pick_point();
extern void camouflaged_target_route_update();
extern void chase_player_store_type_param();
extern void chase_player_update();
extern void chaser_fly_update();
extern void clamp_spawn_control();
extern void cursor_read_u16_mirror2();
extern void cursor_read_u16_mirror6();
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
extern void enemy_face_player();
extern void enemy_health_update();
extern void enemy_move_or_wait();
extern void enemy_spawn_from_place();
extern void enemy_wait_switch();
extern void enemy_walk_step();
extern u8 file_horo_ch0_cb4[];
extern u8 file_horo_ch0_clt[];
extern u8 file_horo_ch0_vx1[];
extern u8 file_horo_tp0_clt[];
extern u8 file_horo_tp0_xs3[];
extern u8 file_hou1_ch0_cb4[];
extern u8 file_hou1_ch0_clt[];
extern u8 file_hou1_ch0_vx1[];
extern u8 file_hou1_tp0_clt[];
extern u8 file_hou1_tp0_xs3[];
extern u8 file_mbaz_ch0_cb4[];
extern u8 file_mbaz_ch0_clt[];
extern u8 file_mbaz_ch0_vx1[];
extern u8 file_mbaz_tp0_clt[];
extern u8 file_mbaz_tp0_xs3[];
extern u8 file_msgs_spr_clt[];
extern u8 file_msgs_spr_grc[];
extern u8 file_msgs_spr_so3[];
extern u8 file_mth2_ch0_cb4[];
extern u8 file_mth2_ch0_clt[];
extern u8 file_mth2_ch0_vx1[];
extern u8 file_mth2_tp0_clt[];
extern u8 file_mth2_tp0_xs3[];
extern u8 file_seaf_ch0_cb4[];
extern u8 file_seaf_ch0_clt[];
extern u8 file_seaf_ch0_vx1[];
extern u8 file_seaf_tp0_clt[];
extern u8 file_seaf_tp0_xs3[];
extern void fly_shoot_update();
extern void fly_sweep();
extern void flyer_retreat();
extern void flyer_wander();
extern void fn_800BD11C();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void func_800C093C();
extern void func_800C1B28();
extern void grenade_fuchikoma_spawn();
extern void gun_turret_spawn();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void model_slot_refresh();
extern void obj_aim_jittered();
extern void obj_airborne_step();
extern void obj_apply_stored_velocity();
extern void obj_area_update();
extern void obj_bounce();
extern void obj_call_hook();
extern void obj_countdown_step();
extern void obj_death_effect();
extern void obj_face_player();
extern void obj_fade_level();
extern void obj_flight_setup();
extern void obj_fly_step();
extern void obj_fly_turn_to_player();
extern void obj_fly_velocity();
extern void obj_handle_result();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_jump_if_player_near();
extern void obj_landing_step();
extern void obj_read_s32();
extern void obj_release_check();
extern void obj_restore_velocity();
extern void obj_retreat_move();
extern void obj_script_jump_if_key();
extern void obj_set_next_state();
extern void obj_settle_offset();
extern void obj_sound_volume_update();
extern void obj_spawn_effects();
extern void obj_speed_approach();
extern void obj_sweep_step();
extern void obj_turn_fire_burst();
extern void obj_turn_fire_shot();
extern void obj_turn_to_player_16();
extern void obj_turn_to_player_hit_reset();
extern void obj_turn_to_player_yaw();
extern void obj_type_param_store_a();
extern void obj_type_param_store_b();
extern void obj_type_params_set();
extern void params_reset();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void projectile_home_update();
extern void ramp_start_script();
extern void script_branch_if_near_player();
extern void script_branch_on_flag();
extern void script_jump_if_beyond_radius();
extern void script_jump_if_facing_player_in_radius();
extern void script_jump_if_flag_set();
extern void script_jump_if_not_below_speed();
extern void script_jump_near();
extern void script_jump_near_player();
extern void script_op_clear_actors();
extern void script_op_health_jump();
extern void script_op_jump_if_beyond_point();
extern void script_op_jump_if_facing_player();
extern void script_op_jump_if_flag_clear();
extern void script_op_jump_if_health_under();
extern void script_op_jump_if_near_point();
extern void script_op_jump_if_ready();
extern void script_op_meter_mode();
extern void script_op_power_switch();
extern void script_op_target_lock();
extern void script_read_long();
extern void script_read_speed_long();
extern void script_set_patrol_phase();
extern void script_set_turn_mode();
extern void script_store_stage_param();
extern void shot_homing_store_type_param();
extern void shot_homing_update();
extern void shot_params_init();
extern void slot_table_init();
extern void sound_volume_phase2();
extern void sound_volume_ramp();
extern u8 str_bos5_ch0_clt[];
extern u8 str_bos5_ch0_vx1[];
extern u8 str_bos5_ch0cb4[];
extern u8 str_bos5_ch1_vx1[];
extern u8 str_bos5_ch1cb4[];
extern u8 str_bos5_ch2_vx1[];
extern u8 str_bos5_ch2cb4[];
extern u8 str_bos5_ch3_vx1[];
extern u8 str_bos5_ch3cb4[];
extern u8 str_bos5_tp0_clt[];
extern u8 str_bos5_tp0_xs3[];
extern u8 str_bos5_tp1_xs3[];
extern u8 str_com_dat_fac[];
extern u8 str_enemy_bos5_data[];
extern u8 str_enemy_ctl5_data[];
extern u8 str_enemy_horo_data[];
extern u8 str_enemy_hou1_data[];
extern u8 str_enemy_mbaz_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_mth2_data[];
extern u8 str_enemy_seaf_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_m05_dat_fac[];
extern u8 str_m22_cnf_bcf[];
extern u8 str_m22_joy_bin[];
extern u8 str_main_data[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_oct_apdea3[];
extern u8 str_oct_cnf_bcf[];
extern u8 str_s05_boss[];
extern u8 str_s05_dat_fac[];
extern u8 str_s05_ene_fac[];
extern u8 str_s05_joy_bin[];
extern u8 str_s05_miss[];
extern u8 str_s05_stage[];
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
extern void stream_read_u16();
extern u8 text_packets[];
extern void text_slot_setup();
extern void track_set_enabled();
extern void track_setup();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern void walker_mech_attack();
extern void walker_mech_patrol();
extern void walker_mech_spawn();
extern u8 D_80117C9C[];
extern u8 D_80117CB4[];
extern u8 D_80117CC8[];
extern u8 D_80117CE0[];
extern u8 D_80117CFC[];
extern u8 D_80117D14[];
extern u8 D_80117EE4[];
extern u8 D_80117EF4[];
extern u8 D_80117EFC[];
extern u8 D_80117F04[];
extern u8 D_80117F3C[];
extern u8 D_80117F8C[];
extern u8 D_80117FAC[];
extern u8 D_80117FB4[];
extern u8 D_8011819A[];
extern u8 D_801181BA[];
extern u8 D_8011E5D2[];
extern u8 D_8011FC8E[];
extern u8 D_8011FFD6[];
extern u8 chase_player_param[];
extern u8 clamp_box_max_x[];
extern u8 clamp_box_max_y[];
extern u8 clamp_box_max_z[];
extern u8 clamp_box_min_y[];
extern u8 clamp_box_min_z[];
extern u8 cos_table[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 d_801201AE[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 enemy_hit_script[];
extern u8 flow_angle[];
extern u8 gun_hit_effect_table[];
extern u8 pad1_pressed[];
extern u8 shot_homing_param[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 view_sincos[];
extern u8 walker_death_scripts_alt[];
extern s32 area;
extern ScanItem enemy_scan_items[];
extern AreaEntry D_80115DBC;
extern AreaEntry D_80115DE4;
extern u32 D_80115E0C[];
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern ModelSlotHead enemy_asset_slots;
extern ModelBlockRef d_80117E6C[];
extern ModelBlockRef d_80117E84[];
extern ModelBlockRef d_80117E94[];
extern ModelBlockRange d_80117EA4[];
extern ModelBlockRange d_80117EB4[];
extern ModelBlock mbaz_model_block;
extern u8 *d_80117EE8[];
extern ScanEntry D_80115F98;
extern SoundVolume enemy_sound_volume[1];
extern s16 bazooka_soldier_anim_idle[];
extern s16 enemy_anim_fidget[];
extern s16 bazooka_soldier_anim_walk_start[];
extern s16 enemy_anim_walk[];
extern s16 bazooka_soldier_anim_run_start[];
extern s16 bazooka_soldier_anim_run[];
extern s16 bazooka_soldier_anim_fire[];
extern s16 bazooka_soldier_anim_fire_shot[];
extern s16 bazooka_soldier_anim_fire_alt[];
extern s16 bazooka_soldier_anim_hold[];
extern s16 bazooka_soldier_anim_aim_hold[];
extern s16 bazooka_soldier_anim_pose_hold[];
extern s16 bazooka_soldier_anim_sweep[];
extern s16 enemy_anim_fall[];
extern s16 enemy_anim_dead[];
extern s16 bazooka_soldier_anim_fly_start[];
extern s16 bazooka_soldier_anim_fly_loop[];
extern s16 *bazooka_script_table[17];
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
extern s16 enemy_fire[];
extern s16 bazooka_soldier_track_wait[];
extern s16 *enemy_script_jumps[16];
extern s16 *enemy_mode_scripts[7];
extern StateEntry enemy_state_table[15];
extern s32 walker_asset_table_alt[];
extern ModelBlockRef enemy_horo_clt_refs[];
extern ModelBlockRef enemy_horo_xs3_refs[];
extern ModelBlockRef enemy_horo_vx1_refs[];
extern ModelBlockRange d_80116438[];
extern ModelBlock walker_mech_model_block;
extern u8 *walker_mech_file_table[];
extern ScanEntry walker_mech_scan_entry;
extern s16 walker_mech_anim_idle[];
extern s16 walker_mech_anim_walk[];
extern s16 walker_mech_anim_fire[];
extern s16 walker_death_script[];
extern s16 *walker_mech_data[4];
extern s16 walker_mech_begin[];
extern s16 walker_mech_patrol_start[];
extern s16 walker_mech_watch[];
extern s16 walker_mech_engage_wait[];
extern s16 walker_mech_engage[];
extern s16 triple_barrel_robot_fire_end[];
extern s16 triple_barrel_robot_cooldown[];
extern s16 *walker_type_data_alt[];
extern s16 *d_80116578;
extern ScriptCallEntry script_handler_table[];
extern StateEntry walker_state_table_alt[];
extern u16 walker_step_sounds_alt[];
extern u32 grenade_asset[];
extern ModelBlockRef grenade_fuchikoma_clt_list[];
extern ModelBlockRef grenade_fuchikoma_xs3_list[];
extern ModelBlockRef grenade_fuchikoma_vx1_list[];
extern ModelBlock grenade_fuchikoma_model;
extern u8 *d_80116624[];
extern ScanEntry grenade_fuchikoma_scan_entry;
extern u32 d_80116644[];
extern s16 grenade_fuchikoma_anim_idle[];
extern s16 grenade_fuchikoma_anim_spin[];
extern s16 grenade_fuchikoma_anim_hold_start[];
extern s16 grenade_fuchikoma_anim_hold[];
extern s16 *grenade_fuchikoma_data[];
extern s16 grenade_fuchikoma_dormant[];
extern s16 grenade_fuchikoma_release[];
extern s16 grenade_fuchikoma_release_wait[];
extern s16 rocket_fuchikoma_ready[];
extern s16 rocket_fuchikoma_aim_start[];
extern s16 grenade_fuchikoma_seek[];
extern s16 grenade_fuchikoma_set_params[];
extern s16 grenade_fuchikoma_track[];
extern s16 rocket_fuchikoma_close_in[];
extern s16 rocket_fuchikoma_brake[];
extern s16 grenade_fuchikoma_wait_stop[];
extern s16 rocket_fuchikoma_fire_wait[];
extern s16 rocket_fuchikoma_fire_start[];
extern s16 grenade_fuchikoma_detonate_wait[];
extern s16 rocket_fuchikoma_reposition[];
extern s16 grenade_fuchikoma_recover_face[];
extern s16 *grenade_type_data[];
extern s16 *grenade_script_pc;
extern ScriptCallEntry script_call_table[];
extern s16 spawn_offset_x_table[];
extern s16 spawn_offset_y_table[];
extern s16 spawn_offset_z_table[];
extern StateEntry rocket_fuchikoma_state_table[];
extern u32 splash_table[];
extern s32 gun_turret_asset[];
extern ModelBlockRef gun_turret_clt_list[];
extern ModelBlockRef gun_turret_xs3_list[];
extern ModelBlockRef gun_turret_vx1_list[];
extern ModelBlock gun_turret_model;
extern u8 *gun_turret_file_list[];
extern ScanEntry gun_turret_scan_entry;
extern u32 d_80116968[];
extern s16 gun_turret_anim_idle[];
extern s16 *gun_turret_data;
extern s16 gun_turret_idle[];
extern s16 gun_turret_spotted[];
extern s16 gun_turret_aim[];
extern s16 gun_turret_fire_check[];
extern s16 gun_turret_fire_start[];
extern s16 gun_turret_cooldown[];
extern s16 *gun_turret_link_data[];
extern s16 *gun_turret_script_pos;
extern ScriptCallEntry gun_turret_call_table[];
extern s16 muzzle_x_table[];
extern s16 muzzle_y_table[];
extern StateEntry gun_turret_states[];
extern s32 fighter_jet_asset[];
extern ModelBlockRef fighter_jet_palette_refs[];
extern ModelBlockRef fighter_jet_texture_refs[];
extern ModelBlockRef fighter_jet_model_refs[];
extern ModelBlock fighter_jet_model_block;
extern u8 *fighter_jet_file_list[];
extern ScanEntry fighter_jet_scan_entry;
extern FxRecordParams obj_effect_rec34_start;
extern FxRecordParams obj_effect_rec34_end;
extern RecTemplate obj_effect_template_start;
extern RecTemplate obj_effect_template_mid;
extern u32 d_80119A1C[];
extern s16 fighter_jet_script[];
extern s16 *fighter_jet_data[];
extern s16 fighter_jet_idle[];
extern s16 fighter_jet_dispatch[];
extern s16 fighter_jet_patrol[];
extern s16 fighter_jet_sweep_end[];
extern s16 fighter_jet_spotted[];
extern s16 fighter_jet_cooldown[];
extern s16 fighter_jet_cooling[];
extern s16 fighter_jet_resume[];
extern s16 *fighter_jet_type_data[];
extern s16 *fighter_jet_script_start;
extern ScriptCallEntry obj_call_table[];
extern StateEntry obj_state_table[];
extern s32 clamp_row;
extern s32 D_80116C00[];
extern ScanEntry clamp_scan_entry;
extern s32 clamp_row_data[];
extern s32 clamp_box_table[8][8];
extern s16 clamp_row_table[][3];
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *enemy_msgs_files[];
extern ScanEntry enemy_msgs_entry;
extern s32 meter_mode_cmd;
extern s32 D_80116DE4;
extern s32 spawn_effects_flag;
extern s32 boss_area_attack_active;
extern s32 boss_area_attack_level;
extern s32 boss_area_attack_seq;
extern u16 camouflaged_target_waypoints[];
extern u16 D_80116DFC[];
extern s16 camouflaged_target_routes[][8];
extern s32 camouflaged_target_m5_asset[3];
extern ModelBlockRef D_80116EDC[];
extern ModelBlockRef D_80116EF4[];
extern ModelBlockRef D_80116F1C[];
extern ModelBlockRange D_80116F34[];
extern ModelBlockRange D_80116F54[];
extern ModelBlock m5_boss_model_block;
extern u8 *D_80116FB0[];
extern ScanEntry m5_boss_scan_entry;
extern SoundVolume m5_boss_sounds[2];
extern s16 camouflaged_target_m5_boss_anim_idle[];
extern s16 camouflaged_target_m5_boss_anim_transition_from_idle_01[];
extern s16 camouflaged_target_m5_boss_anim_transition_from_idle_02[];
extern s16 camouflaged_target_m5_boss_anim_transition_from_idle_03[];
extern s16 camouflaged_target_m5_boss_anim_transition_from_idle_04[];
extern s16 camouflaged_target_m5_boss_anim_transition_from_idle_05[];
extern s16 camouflaged_target_m5_boss_anim_transition_from_idle_06[];
extern s16 camouflaged_target_m5_boss_anim_transition_from_idle_07[];
extern s16 camouflaged_target_m5_boss_anim_transition_from_idle_08[];
extern s16 camouflaged_target_m5_boss_anim_transition_from_idle_09[];
extern s16 camouflaged_target_m5_boss_anim_transition[];
extern s16 camouflaged_target_m5_boss_anim_run_00[];
extern s16 camouflaged_target_m5_boss_anim_run_01[];
extern s16 camouflaged_target_m5_boss_anim_run_02[];
extern s16 camouflaged_target_m5_boss_anim_run_03[];
extern s16 camouflaged_target_m5_boss_anim_run_04[];
extern s16 camouflaged_target_m5_boss_anim_run_05[];
extern s16 camouflaged_target_m5_boss_anim_run_06[];
extern s16 camouflaged_target_m5_boss_anim_run_07[];
extern s16 camouflaged_target_m5_boss_anim_run_08[];
extern s16 camouflaged_target_m5_boss_anim_run_09[];
extern s16 camouflaged_target_m5_boss_anim_run_10[];
extern s16 camouflaged_target_m5_boss_anim_run_11[];
extern s16 camouflaged_target_m5_boss_anim_run_12[];
extern s16 camouflaged_target_m5_boss_anim_run_13[];
extern s16 camouflaged_target_m5_boss_anim_run_14[];
extern s16 camouflaged_target_m5_boss_anim_run_15[];
extern s16 camouflaged_target_m5_boss_anim_run_16[];
extern s16 camouflaged_target_m5_boss_anim_run_17[];
extern s16 camouflaged_target_m5_boss_anim_run_18[];
extern s16 camouflaged_target_m5_boss_anim_run_19[];
extern s16 camouflaged_target_m5_boss_anim_run_20[];
extern s16 camouflaged_target_m5_boss_anim_run_21[];
extern s16 camouflaged_target_m5_boss_anim_run_22[];
extern s16 camouflaged_target_m5_boss_anim_run_23[];
extern s16 camouflaged_target_m5_boss_anim_run_24[];
extern s16 camouflaged_target_m5_boss_anim_run_25[];
extern s16 camouflaged_target_m5_boss_anim_run_26[];
extern s16 camouflaged_target_m5_boss_anim_run_27[];
extern s16 camouflaged_target_m5_boss_anim_run_28[];
extern s16 camouflaged_target_m5_boss_anim_run_29[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_01[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_02[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_03[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_04[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_05[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_06[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_07[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_08[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_09[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_10[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_11[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_12[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_13[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_14[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_15[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_16[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_17[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_18[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_19[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_20[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_21[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_22[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_23[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_24[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_25[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_26[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_27[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_28[];
extern s16 camouflaged_target_m5_boss_anim_settle_from_run_29[];
extern s16 camouflaged_target_m5_boss_anim_settle[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_17[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_18[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_19[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_20[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_21[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_22[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_23[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_24[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_25[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_26[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_27[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_28[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_29[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_00[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_01[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_02[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_03[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_04[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_05[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_06[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_07[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_08[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_09[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_10[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_11[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_12[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_13[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_14[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt_from_run_15[];
extern s16 camouflaged_target_m5_boss_anim_transition_alt[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_01[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_02[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_03[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_04[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_05[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_06[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_07[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_08[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_09[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_10[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_11[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_12[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_13[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_14[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_15[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_16[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_17[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_18[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_19[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_20[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_21[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_22[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_23[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_24[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_25[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_26[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_27[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_28[];
extern s16 camouflaged_target_m5_boss_anim_transition_two_from_run_29[];
extern s16 camouflaged_target_m5_boss_anim_transition_two[];
extern s16 camouflaged_target_m5_boss_anim_hold_lead[];
extern s16 camouflaged_target_m5_boss_anim_hold[];
extern s16 camouflaged_target_m5_boss_anim_release[];
extern s16 camouflaged_target_m5_boss_anim_release_alt[];
extern s16 camouflaged_target_m5_boss_anim_release_long[];
extern s16 camouflaged_target_m5_boss_anim_fire_shot[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_16[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_17[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_18[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_19[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_20[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_21[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_22[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_23[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_24[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_25[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_26[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_27[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_28[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_29[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_00[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_01[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_02[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_03[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_04[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_05[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_06[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_07[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_08[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_09[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_10[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_11[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_12[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_13[];
extern s16 camouflaged_target_m5_boss_anim_hold_start_from_run_14[];
extern s16 camouflaged_target_m5_boss_anim_hold_start[];
extern s16 camouflaged_target_m5_boss_anim_hold_alt[];
extern s16 camouflaged_target_m5_boss_anim_hold_mid[];
extern s16 camouflaged_target_m5_boss_anim_hold_two[];
extern s16 camouflaged_target_m5_boss_anim_impact_lead[];
extern s16 camouflaged_target_m5_boss_anim_impact_hold[];
extern s16 camouflaged_target_m5_boss_anim_recover[];
extern s16 camouflaged_target_m5_boss_anim_recover_alt[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_01[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_02[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_03[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_04[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_05[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_06[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_07[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_08[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_09[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_10[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_11[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_12[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_13[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_14[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_15[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_16[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_17[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_18[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_19[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_20[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_21[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_22[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_23[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_24[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_25[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_26[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_27[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_28[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_29[];
extern s16 camouflaged_target_m5_boss_anim_hold_enter_alt[];
extern s16 camouflaged_target_m5_boss_anim_settle_hold[];
extern s16 camouflaged_target_m5_boss_anim_return_idle[];
extern s16 *camouflaged_target_m5_boss_data[206];
extern s16 camouflaged_target_m5_boss_lock_wait_one[];
extern s16 camouflaged_target_m5_boss_clear_one[];
extern s16 script_count_down[];
extern s16 camouflaged_target_m5_boss_phase_setup_one[];
extern s16 camouflaged_target_m5_boss_phase_reset_one[];
extern s16 camouflaged_target_m5_boss_lock_wait_two[];
extern s16 camouflaged_target_m5_boss_clear_two[];
extern s16 camouflaged_target_m5_boss_phase_reset_two[];
extern s16 camouflaged_target_m5_boss_lock_wait_three[];
extern s16 camouflaged_target_m5_boss_clear_three[];
extern s16 camouflaged_target_m5_boss_phase_reset_three[];
extern s16 camouflaged_target_m5_boss_lock_wait_four[];
extern s16 camouflaged_target_m5_boss_clear_four[];
extern s16 camouflaged_target_m5_boss_phase_reset_four[];
extern s16 camouflaged_target_m5_boss_lock_wait_five[];
extern s16 camouflaged_target_m5_boss_clear_five[];
extern s16 camouflaged_target_m5_boss_meter_on[];
extern s16 camouflaged_target_m5_boss_attack_choose[];
extern s16 camouflaged_target_m5_boss_attack_choose_far[];
extern s16 camouflaged_target_m5_boss_cooldown_start[];
extern s16 camouflaged_target_m5_boss_cooldown_wait[];
extern s16 camouflaged_target_m5_boss_ready_gate[];
extern s16 camouflaged_target_m5_boss_ready_enter[];
extern s16 camouflaged_target_m5_boss_state_seven_wait[];
extern s16 camouflaged_target_m5_boss_post_state_wait[];
extern s16 camouflaged_target_m5_boss_low_health_effects[];
extern s16 camouflaged_target_m5_boss_pause_short[];
extern s16 camouflaged_target_m5_boss_pause_wait[];
extern s16 camouflaged_target_m5_boss_idle_wait[];
extern s16 camouflaged_target_m5_boss_idle_then_attack[];
extern s16 camouflaged_target_m5_boss_attack_choose_alt[];
extern s16 camouflaged_target_m5_boss_attack_choose_alt_far[];
extern s16 camouflaged_target_m5_boss_random_wait[];
extern s16 camouflaged_target_m5_boss_cooldown_alt[];
extern s16 camouflaged_target_m5_boss_meter_off[];
extern u16 D_80117C86;
extern s16 camouflaged_target_m5_boss_attack_a[];
extern s16 camouflaged_target_m5_boss_attack_a_repeat[];
extern s16 camouflaged_target_m5_boss_attack_b[];
extern s16 camouflaged_target_m5_boss_attack_b_repeat[];
extern s16 camouflaged_target_m5_boss_attack_c[];
extern s16 camouflaged_target_m5_boss_attack_c_repeat[];
extern s16 camouflaged_target_m5_boss_attack_d[];
extern s16 camouflaged_target_m5_boss_attack_d_repeat[];
extern s16 camouflaged_target_m5_boss_attack_e[];
extern s16 camouflaged_target_m5_boss_attack_e_repeat[];
extern s16 camouflaged_target_m5_boss_pick_flight_point[];
extern s16 camouflaged_target_m5_boss_pick_flight_repeat[];
extern s16 camouflaged_target_m5_boss_power_on[];
extern s16 camouflaged_target_m5_boss_power_on_wait[];
extern s16 camouflaged_target_m5_boss_power_off_when_idle[];
extern s16 camouflaged_target_m5_boss_power_off[];
extern s16 camouflaged_target_m5_boss_power_off_wait[];
extern s16 camouflaged_target_m5_boss_power_restart;
extern u16 D_80117D4E;
extern s16 *camouflaged_target_m5_script_data[53];
extern s16 *D_80117E24[];
extern ScriptCallEntry m5_boss_call_table[22];
extern StateEntry m5_boss_states[28];
extern u16 D_80117FB8[];
extern u16 obj_type_param_table[];
extern u16 D_80118008[];
extern u16 D_80118044[];
extern u16 shot_homing_param_table[];
extern u16 chase_player_param_table[];
extern FxRecordParams death_effect_params[2];
extern s16 D_80118128[];
extern s16 D_80118130[];
extern s16 D_80118138[];
extern s16 D_80118158[];
extern ObjHandlerFn camouflaged_target_m5_boss_states[];
extern s16 laser_slice_table[][4];
extern s32 d_80118190;
extern s32 screen_fade_amount;
extern s16 D_80118198[][2];
extern s16 D_801181B8[][2];
extern s16 spark_script_a[];
extern s16 rocket_boat_spark_anim_idle[];
extern s16 *spark_script_ptr[2];
extern RecTemplate effect_template;
extern void (*effect_callback_table[])();
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern RecTemplate obj_fx_template_a;
extern RecTemplate obj_fx_template_b;
extern FxRecordParams d_8011ACDC;
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern u16 atan_table[];
extern u32 walker_step_sounds[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_8011CE28[];
extern u16 inv_sqrt_table[];
extern s32 vblank_task_handle;
extern s16 tint_scale_r;
extern s16 tint_scale_g;
extern s16 tint_scale_b;
extern s16 tint_add_r;
extern s16 tint_add_g;
extern s16 tint_add_b;
extern s16 video_mode_id;
extern s16 debug_cam_speed_table[][2];
extern s32 pause_prev_work_area;
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
extern u32 D_8011DFAC[];
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
extern u32 D_8011E5CC;
extern u16 texture_image[];
extern u32 gun_turret_asset_s12[];
extern u32 muzzle_x_table_s12[];
extern u32 muzzle_y_table_s12[];
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
extern s32 d_8011FFE4;
extern u32 D_8011FADC;
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
extern u32 D_8011FB60;
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
extern s32 interp_enabled_flag;
extern s32 interp_record_count;
extern s32 interp1c_count;
extern s32 interp2c_count;
extern s32 interp38_count;
extern s32 interp38b_count;
extern s32 pause_flag;
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
extern s32 meter_mode;
extern s32 gauge_flash_level;
extern s32 lock_spawn_timer;
extern s32 rec_table_enabled;
extern s32 lock_slot_phase;
extern s32 id_marker_pushed;
extern s32 pursuit_blend;
extern s32 cam_mode;
extern s16 cam_offset_x;
extern s16 cam_offset_y;
extern s16 pursuit_view_w;
extern s16 pursuit_view_h;
extern s32 target_current;
extern s32 target_requested;
extern s32 pursuit_spin_angle;
extern s32 pursue_msg_timer;
extern s32 pursuit_hold_timer;
extern s32 target_switch_timer;
extern s32 cam_path_last_seg;
extern s32 cam_path_start;
extern s32 cam_path_end;
extern s32 impact_effect_base;
extern s32 object_slots_free;
extern s32 spark_effect_base;
extern s32 spark_free_count;
extern s32 trail_ring_count;
extern s32 trail_ring_head;
extern s32 trail_ring_tail;
extern s32 grenade_effect_base;
extern s32 grenade_slots_free;
extern s32 proximity_hook_fn;
extern s32 lock_frame_base;
extern s32 lock_target_count;
extern s32 lock_mode;
extern s32 lock_cooldown_timer;
extern s16 fx_tpage;
extern s16 fx_clut_word;
extern s32 fx_saved_bk_red;
extern s32 fx_saved_bk_green;
extern s32 fx_saved_bk_blue;
extern s16 d_8012040C;
extern s16 d_80120410;
extern s32 sound_alloc_free_count;
extern s32 sound_fade_rate;
extern s32 sound_fade_step;
extern s32 sound_fade_level;
extern s32 sound_load_id;
extern s32 sound_load_flag;
extern s32 sound_load_handle;
extern s32 sound_timer;
extern s32 sound_master_volume;
extern s16 sound_listener_pitch;
extern s16 sound_listener_yaw;
extern s16 sound_listener_roll;
extern s32 sound_mode;
extern s32 sound_paused;
extern s32 sound_active_flag;
extern u8 sound_alloc_used_tail[];
extern u8 sound_alloc_free_head[];
extern s32 particle_base_ptr;
extern s32 wall_tables_ptr;
extern s32 placement_angle_table;
extern s32 cam_offset_blend;
extern s32 cam_offset_speed;
extern s32 cam_stick_offset;
extern s32 cam_aim_blend;
extern s32 d_80120470;
extern s32 player_model_pchr;
extern s32 player_model_state;
extern s32 player_model_enabled;
extern s32 player_model_on_flag;
extern s32 fade_level;
extern s32 player_mode_bits;
extern s32 player_mode_flags_saved;
extern s32 player_ceiling_limit;
extern s32 cam_follow_blend;
extern s32 cam_distance;
extern s32 d_8012049C;
extern s16 mover_angle_b;
extern s16 mover_angle_a;
extern s16 mover_angle_c;
extern s32 mover_min_dist;
extern s32 mover_max_dist;
extern s32 cur_view_index;
extern s32 light_env_index;
extern s32 player_mode;
extern s32 point_search_below;
extern s32 cur_camera_index;
extern PadInput pad1;
extern PadInput pad_mirror;
extern s32 pspr_top;
extern WorkArea *work_area_ptr;
extern s32 point_search_above;
extern s16 scale_vec[3];
extern s16 stage_screen_w;
extern s16 stage_screen_h;
extern s32 point_search_radius;
extern u8 fade_color_r;
extern u8 fade_color_g;
extern u16 fade_color_b;
extern s32 point_base;
extern s32 packet_free_list;
extern s32 shot_params_b;
extern s32 enemy_area_limit;
extern u32 D_8011FFF8;
extern u16 D_8011FFFC;
extern u16 D_8011FFFE;

s32 area = 12;

ScanItem enemy_scan_items[9] = {
    {&clamp_scan_entry, str_enemy_ctl5_data},
    {&walker_mech_scan_entry, str_enemy_horo_data},
    {&grenade_fuchikoma_scan_entry, str_enemy_mth2_data},
    {&D_80115F98, str_enemy_mbaz_data},
    {&gun_turret_scan_entry, str_enemy_hou1_data},
    {&fighter_jet_scan_entry, str_enemy_seaf_data},
    {&enemy_msgs_entry, str_enemy_msgs_data},
    {&m5_boss_scan_entry, str_enemy_bos5_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry D_80115DBC = {str_s05_stage, str_oct_cnf_bcf, str_oct_apdea3, str_s05_joy_bin, str_s05_dat_fac, str_s05_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, enemy_scan_items};

AreaEntry D_80115DE4 = {str_s05_miss, str_m22_cnf_bcf, NULL, str_m22_joy_bin, str_m05_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

u32 D_80115E0C[12] = {
    0xFFFFFFFF, 0x00000000, (u32)str_s05_boss, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x10001000, 0x00001000, 0x00000000, (u32)D_80115E0C,
};

AreaEntry *area_entry_table[3] = {
    &D_80115DE4, &D_80115DBC, NULL,
};

#include "../stage/data/debug_name_buf.c"

ModelSlotHead enemy_asset_slots = {{-1, -1, -1}};

#include "../stage/data/d_80117E6C.c"

#include "../stage/data/d_80117E84.c"

#include "../stage/data/d_80117E94.c"

#include "../stage/data/d_80117EA4.c"

#include "../stage/data/d_80117EB4.c"

#include "../stage/data/mbaz_model_block.c"

#include "../stage/data/d_80117EE8.c"

ScanEntry D_80115F98 = {{(s32)shot_params_init, (s32)enemy_spawn_from_place}, (s32 *)&enemy_asset_slots, (s32)&mbaz_model_block, (s32)d_80117EE8, 0};

SoundVolume enemy_sound_volume[1] = {
    {SND_GROUND_IMPACT | SND_GROUP(2), 0x1000},
};

#include "../stage/data/bazooka_script_table_streams.c"

struct EnemyScriptJumpsStreams {
    s16 smg_soldier_idle[6];
    s16 smg_soldier_idle_pause[4];
    s16 smg_soldier_idle_cycle[10];
    s16 smg_soldier_patrol[6];
    s16 smg_soldier_patrol_cycle[12];
    s16 smg_soldier_patrol_wait[6];
    s16 smg_soldier_hold[4];
    s16 smg_soldier_hold_pause[4];
    s16 smg_soldier_hold_cycle[10];
    s16 smg_soldier_walk[4];
    s16 smg_soldier_walk_step[4];
    s16 smg_soldier_walk_cycle[10];
    s16 smg_soldier_walk_pause[4];
    s16 smg_soldier_walk_pause_cycle[10];
    s16 enemy_fire[2];
    s16 bazooka_soldier_track_wait[8];
    s16 *table[16];
    s16 *enemy_mode_scripts[7];
} enemy_script_jumps_streams = {
    /* smg_soldier_idle */ {
        JUMP_RANDOM(3072, SMG_SOLDIER_PATROL),
        SET_COUNTER_RANDOM(3, 1),
    },
    /* smg_soldier_idle_pause */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* smg_soldier_idle_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_IDLE_CYCLE),
        LOOP(SMG_SOLDIER_IDLE_PAUSE),
        JUMP(SMG_SOLDIER_IDLE),
    },
    /* smg_soldier_patrol */ {
        WAIT(1),
        WANDER(1),
        NEXT_STATE(ENEMY_STATE_WANDER),
    },
    /* smg_soldier_patrol_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_PATROL_CYCLE),
        SET_SPEED(0),
        WANDER(1),
        SET_COUNTER_RANDOM(5, 3),
    },
    /* smg_soldier_patrol_wait */ {
        WAIT(1),
        LOOP(SMG_SOLDIER_PATROL_WAIT),
        JUMP(SMG_SOLDIER_IDLE),
    },
    /* smg_soldier_hold */ {
        SET_COUNTER_RANDOM(3, 1),
    },
    /* smg_soldier_hold_pause */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* smg_soldier_hold_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_HOLD_CYCLE),
        LOOP(SMG_SOLDIER_HOLD_PAUSE),
        JUMP(SMG_SOLDIER_HOLD),
    },
    /* smg_soldier_walk */ {
        SET_COUNTER_RANDOM(4, 1),
    },
    /* smg_soldier_walk_step */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WANDER),
    },
    /* smg_soldier_walk_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_WALK_CYCLE),
        LOOP(SMG_SOLDIER_WALK_STEP),
        JUMP(SMG_SOLDIER_WALK),
    },
    /* smg_soldier_walk_pause */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* smg_soldier_walk_pause_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_WALK_PAUSE_CYCLE),
        LOOP(SMG_SOLDIER_WALK_PAUSE),
        JUMP(SMG_SOLDIER_WALK),
    },
    /* enemy_fire */ {
        NEXT_STATE(ENEMY_STATE_FIRE),
    },
    /* bazooka_soldier_track_wait */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_TRACK, BAZOOKA_SOLDIER_TRACK_WAIT),
        JUMP(SMG_SOLDIER_IDLE),
    },
    /* table */ {
        enemy_script_jumps_streams.smg_soldier_idle, enemy_script_jumps_streams.smg_soldier_idle_pause, enemy_script_jumps_streams.smg_soldier_idle_cycle, enemy_script_jumps_streams.smg_soldier_patrol, enemy_script_jumps_streams.smg_soldier_patrol_cycle, enemy_script_jumps_streams.smg_soldier_patrol_wait,
        enemy_script_jumps_streams.smg_soldier_hold, enemy_script_jumps_streams.smg_soldier_hold_pause, enemy_script_jumps_streams.smg_soldier_hold_cycle, enemy_script_jumps_streams.smg_soldier_walk, enemy_script_jumps_streams.smg_soldier_walk_step, enemy_script_jumps_streams.smg_soldier_walk_cycle,
        enemy_script_jumps_streams.smg_soldier_walk_pause, enemy_script_jumps_streams.smg_soldier_walk_pause_cycle, enemy_script_jumps_streams.enemy_fire, enemy_script_jumps_streams.bazooka_soldier_track_wait,
    },
    /* enemy_mode_scripts */ {
        enemy_script_jumps_streams.smg_soldier_idle, enemy_script_jumps_streams.smg_soldier_hold, enemy_script_jumps_streams.smg_soldier_walk, enemy_script_jumps_streams.smg_soldier_hold, enemy_script_jumps_streams.smg_soldier_walk, enemy_script_jumps_streams.enemy_fire,
        enemy_script_jumps_streams.smg_soldier_hold,
    },
};

StateEntry enemy_state_table[15] = {
    {0, BAZOOKA_SOLDIER_ANIM_IDLE, 0},
    {(u32)enemy_wait_switch, ENEMY_ANIM_FIDGET, 0},
    {(u32)enemy_move_or_wait, BAZOOKA_SOLDIER_ANIM_WALK_START, 0},
    {(u32)enemy_walk_step, BAZOOKA_SOLDIER_ANIM_RUN_START, 0},
    {(u32)flyer_wander, BAZOOKA_SOLDIER_ANIM_FLY_START, 0},
    {(u32)enemy_face_player, BAZOOKA_SOLDIER_ANIM_HOLD, 0},
    {(u32)flyer_retreat, ENEMY_ANIM_WALK, 0},
    {(u32)enemy_face_player, BAZOOKA_SOLDIER_ANIM_FIRE_SHOT, 0},
    {(u32)enemy_face_player, BAZOOKA_SOLDIER_ANIM_FIRE_ALT, 0},
    {0, BAZOOKA_SOLDIER_ANIM_HOLD, 0},
    {0, BAZOOKA_SOLDIER_ANIM_AIM_HOLD, 0},
    {0, BAZOOKA_SOLDIER_ANIM_POSE_HOLD, 0},
    {0, BAZOOKA_SOLDIER_ANIM_SWEEP, 0},
    {0, ENEMY_ANIM_FALL, 0},
    {0, ENEMY_ANIM_DEAD, 0},
};

#include "../stage/data/walker_asset_table_alt.c"

#include "../stage/data/enemy_horo_clt_refs.c"

#include "../stage/data/enemy_horo_xs3_refs.c"

#include "../stage/data/enemy_horo_vx1_refs.c"

#include "../stage/data/d_80116438.c"

#include "../stage/data/walker_mech_model_block.c"

#include "../stage/data/walker_mech_file_table.c"

#include "../stage/data/walker_mech_scan_entry.c"

#include "../stage/data/walker_anims.c"

#include "../stage/data/walker_type_data_alt_streams.c"

#include "../stage/data/script_handler_table.c"

#include "../stage/data/walker_state_table_alt.c"

#include "../stage/data/walker_step_sounds_alt.c"

u32 grenade_asset[3] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
};

ModelBlockRef grenade_fuchikoma_clt_list[3] = {
    {(s32)file_mth2_ch0_clt, 0, 0},
    {(s32)file_mth2_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef grenade_fuchikoma_xs3_list[2] = {
    {(s32)file_mth2_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef grenade_fuchikoma_vx1_list[2] = {
    {(s32)file_mth2_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock grenade_fuchikoma_model = {(s32)grenade_fuchikoma_clt_list, (s32)grenade_fuchikoma_vx1_list, (s32)grenade_fuchikoma_xs3_list, 0, 0, 0, 0, 0, 0};

u8 *d_80116624[2] = {
    file_mth2_ch0_cb4, NULL,
};

ScanEntry grenade_fuchikoma_scan_entry = {{(s32)params_reset, (s32)grenade_fuchikoma_spawn}, (s32 *)grenade_asset, (s32)&grenade_fuchikoma_model, (s32)d_80116624, 0};

#include "../stage/data/d_80116644.c"

#include "../stage/data/grenade_fuchikoma_anims.c"

#include "../stage/data/grenade_type_data_streams.c"

#include "../stage/data/script_call_table.c"

StateEntry rocket_fuchikoma_state_table[3] = {
    {0, GRENADE_FUCHIKOMA_ANIM_IDLE, 0},
    {(u32)obj_settle_offset, GRENADE_FUCHIKOMA_ANIM_SPIN, 0},
    {(u32)obj_countdown_step, GRENADE_FUCHIKOMA_ANIM_HOLD_START, 0},
};

#include "../stage/data/splash_table.c"

#include "../stage/data/gun_turret_asset.c"

#include "../stage/data/gun_turret_clt_list.c"

#include "../stage/data/gun_turret_xs3_list.c"

#include "../stage/data/gun_turret_vx1_list.c"

#include "../stage/data/gun_turret_model.c"

#include "../stage/data/gun_turret_file_list.c"

#include "../stage/data/gun_turret_scan_entry.c"

#include "../stage/data/d_80116968.c"

#include "../stage/data/gun_turret_anims.c"

#include "../stage/data/gun_turret_scripts.c"

#include "../stage/data/gun_turret_call_table.c"

#include "../stage/data/muzzle_x_table.c"

#include "../stage/data/muzzle_y_table.c"

#include "../stage/data/gun_turret_states.c"

s32 fighter_jet_asset[3] = {
    -1, -1, -1,
};

#include "../stage/data/fighter_jet_palette_refs.c"

#include "../stage/data/fighter_jet_texture_refs.c"

#include "../stage/data/fighter_jet_model_refs.c"

#include "../stage/data/fighter_jet_model_block.c"

#include "../stage/data/fighter_jet_file_list.c"

ScanEntry fighter_jet_scan_entry = {{(s32)slot_table_init, 0}, fighter_jet_asset, (s32)&fighter_jet_model_block, (s32)fighter_jet_file_list, 0};

FxRecordParams obj_effect_rec34_start = {0, 0xFF, 0x70, 0, 0x100, 0x55, {0x800000, 0x34000, 0x1000, 0x8000}};

FxRecordParams obj_effect_rec34_end = {0, 0xFF, 0x20, 0, 0x400, 0x4E, {0x300000, 0x18000, 0x1000, 0x8000}};

RecTemplate obj_effect_template_start = {1, 0xFF, 0, 0, 0x400, 0x40, 0x500000, 0x40000, 0x1000, 0x8000};

RecTemplate obj_effect_template_mid = {1, 0xFF, 0xFF, 0x80, 0x580, 0x40, 0x400000, 0x30000, 0x1000, 0x8000};

#include "../stage/data/d_80119A1C.c"

#include "../stage/data/fighter_jet_anims.c"

struct FighterJetScripts {
    s16 idle[2];
    s16 dispatch[8];
    s16 patrol[8];
    s16 sweep_end[8];
    s16 spotted[8];
    s16 cooldown[4];
    s16 cooling[6];
    s16 resume[4];
    s16 *table[8];
    s16 *script_start;
} fighter_jet_scripts = {
    /* idle */ {
        JUMP(FIGHTER_JET_DISPATCH),
    },
    /* dispatch */ {
        JUMP_IF_STATE(FIGHTER_JET_SPAWN_FROM_PARENT_STATE_SWEEP, FIGHTER_JET_SWEEP_END),
        FIGHTER_JET_SPAWN_FROM_PARENT_JUMP_IF_PLAYER_NEAR, 12000, FIGHTER_JET_SPOTTED,
        JUMP(FIGHTER_JET_PATROL),
    },
    /* patrol */ {
        FIGHTER_JET_SPAWN_FROM_PARENT_SET_TURN_MODE, 0,
        FIGHTER_JET_SPAWN_FROM_PARENT_SPEED_APPROACH, 35,
        FIGHTER_JET_SPAWN_FROM_PARENT_SET_NEXT_STATE, FIGHTER_JET_SPAWN_FROM_PARENT_STATE_FLY,
        JUMP(FIGHTER_JET_COOLDOWN),
    },
    /* sweep_end */ {
        FIGHTER_JET_SPAWN_FROM_PARENT_SET_TURN_MODE, 1,
        FIGHTER_JET_SPAWN_FROM_PARENT_SPEED_APPROACH, 17,
        FIGHTER_JET_SPAWN_FROM_PARENT_SET_NEXT_STATE, FIGHTER_JET_SPAWN_FROM_PARENT_STATE_FLY,
        JUMP(FIGHTER_JET_COOLDOWN),
    },
    /* spotted */ {
        FIGHTER_JET_SPAWN_FROM_PARENT_SET_TURN_MODE, 0,
        FIGHTER_JET_SPAWN_FROM_PARENT_SPEED_APPROACH, 24,
        FIGHTER_JET_SPAWN_FROM_PARENT_SET_NEXT_STATE, FIGHTER_JET_SPAWN_FROM_PARENT_STATE_FIRE,
        JUMP(FIGHTER_JET_COOLDOWN),
    },
    /* cooldown */ {
        SET_COUNTER(50),
        JUMP(FIGHTER_JET_COOLING),
    },
    /* cooling */ {
        WAIT(1),
        LOOP(FIGHTER_JET_COOLING),
        JUMP(FIGHTER_JET_RESUME),
    },
    /* resume */ {
        WAIT(1),
        JUMP(FIGHTER_JET_IDLE),
    },
    /* table */ {
        fighter_jet_scripts.idle, fighter_jet_scripts.dispatch, fighter_jet_scripts.patrol, fighter_jet_scripts.sweep_end, fighter_jet_scripts.spotted, fighter_jet_scripts.cooldown,
        fighter_jet_scripts.cooling, fighter_jet_scripts.resume,
    },
    /* script_start */ fighter_jet_scripts.idle,
};

#include "../stage/data/obj_call_table.c"

#include "../stage/data/obj_state_table.c"

s32 clamp_row = 0;

s32 D_80116C00[3] = {
    -1, -1, -1,
};

ScanEntry clamp_scan_entry = {{0, (s32)clamp_spawn_control}, D_80116C00, 0, 0, 0};

s32 clamp_row_data[1] = {
    8,
};

s32 clamp_box_table[8][8] = {
    {-0x3480, -0x8000, -0x2640, 1, 0x3300, 0, 0x2E20, 0},
    {0x1740, -0x8000, -0x2FA0, 1, 0x18C0, 0, -0x24C0, 0},
    {0xD80, -0x8000, -0x3C00, 1, 0x2280, 0, -0x2FA0, 0},
    {0x3C0, -0x8000, 0x2280, 0, 0x1800, 0, 0x2DC0, 0},
    {-0x21C0, -0x8000, -0x1200, 0, -0x1080, 0, -0xC0, 0},
    {0x18C0, -0x8000, -0xA80, 0, 0x2700, 0, 0x3C0, 0},
    {0x2100, -0x8000, -0x24C0, 0, 0x3180, 0, -0xE40, 0},
    {0xD80, -0x8000, -0x3C00, 0, 0x2280, 0, -0x2FA0, 0},
};

s16 clamp_row_table[6][3] = {
    {0, 1, 2}, {3, -1, -1}, {4, -1, -1}, {5, -1, -1}, {6, -1, -1}, {7, -1, -1},
};

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

#include "../stage/data/enemy_msgs_files.c"

#include "../stage/data/enemy_msgs_entry.c"

s32 meter_mode_cmd = 0;

s32 D_80116DE4 = 1;

s32 spawn_effects_flag = 1;

s32 boss_area_attack_active = 0;

s32 boss_area_attack_level = 0;

s32 boss_area_attack_seq = 0;

u16 camouflaged_target_waypoints[2] = {
    0x03C0, 0x0000,
};

u16 D_80116DFC[74] = {
    0x2666, 0x0000, 0xF580, 0x0000, 0x2666, 0x0000, 0xF580, 0x0000,
    0xFA60, 0x0000, 0xEF80, 0x0000, 0xFA60, 0x0000, 0xE7A0, 0x0000,
    0xFA00, 0x0000, 0xEF80, 0x0000, 0xFA60, 0x0000, 0xF580, 0x0000,
    0xFA60, 0x0000, 0xF580, 0x0000, 0x06C0, 0x0000, 0x0A20, 0x0000,
    0x06C0, 0x0000, 0x0A20, 0x0000, 0xF940, 0x0000, 0x18C0, 0x0000,
    0xF940, 0x0000, 0x2040, 0x0000, 0xFC40, 0x0000, 0x2400, 0x0000,
    0xF580, 0x0000, 0x2400, 0x0000, 0xF1C0, 0x0000, 0x2B80, 0x0000,
    0xE500, 0x0000, 0x2100, 0x0000, 0xDEA0, 0x0000, 0x1800, 0x0000,
    0xDEA0, 0x0000, 0x1800, 0x0000, 0xD060, 0x0000, 0x1800, 0x0000,
    0xCA30, 0x0000,
};

s16 camouflaged_target_routes[4][8] = {
    {0, 1, 2, 3, -1, -1, -1, 4},
    {5, 6, 7, 8, 9, 10, -1, 11},
    {12, 13, -1, -1, -1, -1, -1, 14},
    {15, 0x10, 0x11, -1, -1, -1, -1, 0x12},
};

s32 camouflaged_target_m5_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_80116EDC[3] = {
    {(s32)str_bos5_ch0_clt, 0, 0},
    {(s32)str_bos5_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80116EF4[5] = {
    {(s32)str_bos5_ch0_vx1, 0, 0},
    {(s32)str_bos5_ch1_vx1, 0, 0},
    {(s32)str_bos5_ch2_vx1, 0, 0},
    {(s32)str_bos5_ch3_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80116F1C[3] = {
    {(s32)str_bos5_tp0_xs3, 1, 0},
    {(s32)str_bos5_tp1_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRange D_80116F34[4] = {
    {0x183, 0x18B, 0x2000, 0}, {0x190, 0x195, 0x1000, 0}, {0x1A0, 0x1A0, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlockRange D_80116F54[7] = {
    {0, 0x7F, 0x1666, 0}, {0x80, 0xFF, 0x1666, 0}, {0x100, 0x17F, 0x1666, 0}, {0x180, 0x197, 0x1666, 0},
    {0x198, 0x19F, 0x1666, 0}, {0x1A0, 0x1FF, 0x1666, 0}, {-1, 0, 0, 0},
};

ModelBlock m5_boss_model_block = {(s32)D_80116EDC, (s32)D_80116EF4, (s32)D_80116F1C, 0, (s32)D_80116F34, 0, (s32)D_80116F54, 0, 0};

u8 *D_80116FB0[5] = {
    str_bos5_ch0cb4, str_bos5_ch1cb4, str_bos5_ch2cb4, str_bos5_ch3cb4, NULL,
};

ScanEntry m5_boss_scan_entry = {{(s32)model_slot_refresh, (s32)camouflaged_target_m5_boss_spawn}, camouflaged_target_m5_asset, (s32)&m5_boss_model_block, (s32)D_80116FB0, 0};

SoundVolume m5_boss_sounds[2] = {
    {0x5085, 0x1000},
    {SND_BOSS_IMPACT_LEAD | SND_GROUP(2), 0x1000},
};

struct CamouflagedTargetM5BossAnims {
    s16 idle[22];
    s16 transition_from_idle_01[2];
    s16 transition_from_idle_02[2];
    s16 transition_from_idle_03[2];
    s16 transition_from_idle_04[2];
    s16 transition_from_idle_05[2];
    s16 transition_from_idle_06[2];
    s16 transition_from_idle_07[2];
    s16 transition_from_idle_08[2];
    s16 transition_from_idle_09[2];
    s16 transition[38];
    s16 run_00[2];
    s16 run_01[2];
    s16 run_02[2];
    s16 run_03[2];
    s16 run_04[2];
    s16 run_05[2];
    s16 run_06[2];
    s16 run_07[2];
    s16 run_08[2];
    s16 run_09[2];
    s16 run_10[2];
    s16 run_11[2];
    s16 run_12[2];
    s16 run_13[2];
    s16 run_14[2];
    s16 run_15[2];
    s16 run_16[2];
    s16 run_17[2];
    s16 run_18[2];
    s16 run_19[2];
    s16 run_20[2];
    s16 run_21[2];
    s16 run_22[2];
    s16 run_23[2];
    s16 run_24[2];
    s16 run_25[2];
    s16 run_26[2];
    s16 run_27[2];
    s16 run_28[2];
    s16 run_29[4];
    s16 settle_from_run_01[2];
    s16 settle_from_run_02[2];
    s16 settle_from_run_03[2];
    s16 settle_from_run_04[2];
    s16 settle_from_run_05[2];
    s16 settle_from_run_06[2];
    s16 settle_from_run_07[2];
    s16 settle_from_run_08[2];
    s16 settle_from_run_09[2];
    s16 settle_from_run_10[2];
    s16 settle_from_run_11[2];
    s16 settle_from_run_12[2];
    s16 settle_from_run_13[2];
    s16 settle_from_run_14[2];
    s16 settle_from_run_15[2];
    s16 settle_from_run_16[2];
    s16 settle_from_run_17[2];
    s16 settle_from_run_18[2];
    s16 settle_from_run_19[2];
    s16 settle_from_run_20[2];
    s16 settle_from_run_21[2];
    s16 settle_from_run_22[2];
    s16 settle_from_run_23[2];
    s16 settle_from_run_24[2];
    s16 settle_from_run_25[2];
    s16 settle_from_run_26[2];
    s16 settle_from_run_27[2];
    s16 settle_from_run_28[2];
    s16 settle_from_run_29[2];
    s16 settle[32];
    s16 transition_alt_from_run_17[2];
    s16 transition_alt_from_run_18[2];
    s16 transition_alt_from_run_19[2];
    s16 transition_alt_from_run_20[2];
    s16 transition_alt_from_run_21[2];
    s16 transition_alt_from_run_22[2];
    s16 transition_alt_from_run_23[2];
    s16 transition_alt_from_run_24[2];
    s16 transition_alt_from_run_25[2];
    s16 transition_alt_from_run_26[2];
    s16 transition_alt_from_run_27[2];
    s16 transition_alt_from_run_28[2];
    s16 transition_alt_from_run_29[2];
    s16 transition_alt_from_run_00[2];
    s16 transition_alt_from_run_01[2];
    s16 transition_alt_from_run_02[2];
    s16 transition_alt_from_run_03[2];
    s16 transition_alt_from_run_04[2];
    s16 transition_alt_from_run_05[2];
    s16 transition_alt_from_run_06[2];
    s16 transition_alt_from_run_07[2];
    s16 transition_alt_from_run_08[2];
    s16 transition_alt_from_run_09[2];
    s16 transition_alt_from_run_10[2];
    s16 transition_alt_from_run_11[2];
    s16 transition_alt_from_run_12[2];
    s16 transition_alt_from_run_13[2];
    s16 transition_alt_from_run_14[2];
    s16 transition_alt_from_run_15[2];
    s16 transition_alt[42];
    s16 transition_two_from_run_01[2];
    s16 transition_two_from_run_02[2];
    s16 transition_two_from_run_03[2];
    s16 transition_two_from_run_04[2];
    s16 transition_two_from_run_05[2];
    s16 transition_two_from_run_06[2];
    s16 transition_two_from_run_07[2];
    s16 transition_two_from_run_08[2];
    s16 transition_two_from_run_09[2];
    s16 transition_two_from_run_10[2];
    s16 transition_two_from_run_11[2];
    s16 transition_two_from_run_12[2];
    s16 transition_two_from_run_13[2];
    s16 transition_two_from_run_14[2];
    s16 transition_two_from_run_15[2];
    s16 transition_two_from_run_16[2];
    s16 transition_two_from_run_17[2];
    s16 transition_two_from_run_18[2];
    s16 transition_two_from_run_19[2];
    s16 transition_two_from_run_20[2];
    s16 transition_two_from_run_21[2];
    s16 transition_two_from_run_22[2];
    s16 transition_two_from_run_23[2];
    s16 transition_two_from_run_24[2];
    s16 transition_two_from_run_25[2];
    s16 transition_two_from_run_26[2];
    s16 transition_two_from_run_27[2];
    s16 transition_two_from_run_28[2];
    s16 transition_two_from_run_29[2];
    s16 transition_two[42];
    s16 hold_lead[28];
    s16 hold[4];
    s16 release[20];
    s16 release_alt[30];
    s16 release_long[54];
    s16 fire_shot[26];
    s16 hold_start_from_run_16[2];
    s16 hold_start_from_run_17[2];
    s16 hold_start_from_run_18[2];
    s16 hold_start_from_run_19[2];
    s16 hold_start_from_run_20[2];
    s16 hold_start_from_run_21[2];
    s16 hold_start_from_run_22[2];
    s16 hold_start_from_run_23[2];
    s16 hold_start_from_run_24[2];
    s16 hold_start_from_run_25[2];
    s16 hold_start_from_run_26[2];
    s16 hold_start_from_run_27[2];
    s16 hold_start_from_run_28[2];
    s16 hold_start_from_run_29[2];
    s16 hold_start_from_run_00[2];
    s16 hold_start_from_run_01[2];
    s16 hold_start_from_run_02[2];
    s16 hold_start_from_run_03[2];
    s16 hold_start_from_run_04[2];
    s16 hold_start_from_run_05[2];
    s16 hold_start_from_run_06[2];
    s16 hold_start_from_run_07[2];
    s16 hold_start_from_run_08[2];
    s16 hold_start_from_run_09[2];
    s16 hold_start_from_run_10[2];
    s16 hold_start_from_run_11[2];
    s16 hold_start_from_run_12[2];
    s16 hold_start_from_run_13[2];
    s16 hold_start_from_run_14[2];
    s16 hold_start[6];
    s16 hold_alt[4];
    s16 hold_mid[6];
    s16 hold_two[4];
    s16 impact_lead[18];
    s16 impact_hold[4];
    s16 recover[36];
    s16 recover_alt[42];
    s16 hold_enter_alt_from_run_01[2];
    s16 hold_enter_alt_from_run_02[2];
    s16 hold_enter_alt_from_run_03[2];
    s16 hold_enter_alt_from_run_04[2];
    s16 hold_enter_alt_from_run_05[2];
    s16 hold_enter_alt_from_run_06[2];
    s16 hold_enter_alt_from_run_07[2];
    s16 hold_enter_alt_from_run_08[2];
    s16 hold_enter_alt_from_run_09[2];
    s16 hold_enter_alt_from_run_10[2];
    s16 hold_enter_alt_from_run_11[2];
    s16 hold_enter_alt_from_run_12[2];
    s16 hold_enter_alt_from_run_13[2];
    s16 hold_enter_alt_from_run_14[2];
    s16 hold_enter_alt_from_run_15[2];
    s16 hold_enter_alt_from_run_16[2];
    s16 hold_enter_alt_from_run_17[2];
    s16 hold_enter_alt_from_run_18[2];
    s16 hold_enter_alt_from_run_19[2];
    s16 hold_enter_alt_from_run_20[2];
    s16 hold_enter_alt_from_run_21[2];
    s16 hold_enter_alt_from_run_22[2];
    s16 hold_enter_alt_from_run_23[2];
    s16 hold_enter_alt_from_run_24[2];
    s16 hold_enter_alt_from_run_25[2];
    s16 hold_enter_alt_from_run_26[2];
    s16 hold_enter_alt_from_run_27[2];
    s16 hold_enter_alt_from_run_28[2];
    s16 hold_enter_alt_from_run_29[2];
    s16 hold_enter_alt[30];
    s16 settle_hold[4];
    s16 return_idle[82];
    s16 *table[206];
} camouflaged_target_m5_boss_anims = {
    /* idle */ {
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
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE),
    },
    /* transition_from_idle_01 */ {
        STEP(4, 2),
    },
    /* transition_from_idle_02 */ {
        STEP(4, 3),
    },
    /* transition_from_idle_03 */ {
        STEP(4, 4),
    },
    /* transition_from_idle_04 */ {
        STEP(4, 5),
    },
    /* transition_from_idle_05 */ {
        STEP(4, 6),
    },
    /* transition_from_idle_06 */ {
        STEP(4, 7),
    },
    /* transition_from_idle_07 */ {
        STEP(4, 8),
    },
    /* transition_from_idle_08 */ {
        STEP(4, 9),
    },
    /* transition_from_idle_09 */ {
        STEP(4, 10),
    },
    /* transition */ {
        STEP(0, 13),
        STEP(0, 14),
        STEP(0, 15),
        STEP(0, 16),
        STEP(0, 17),
        STEP(0, 18),
        STEP(0, 19),
        STEP(0, 20),
        STEP(0, 21),
        STEP(0, 22),
        STEP(0, 23),
        STEP(0, 24),
        STEP(0, 25),
        STEP(0, 26),
        STEP(0, 27),
        STEP(0, 28),
        STEP(0, 29),
        STEP(0, 30),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RUN_06),
    },
    /* run_00 */ {
        STEP(0, 33),
    },
    /* run_01 */ {
        STEP(0, 34),
    },
    /* run_02 */ {
        STEP(0, 35),
    },
    /* run_03 */ {
        STEP(0, 36),
    },
    /* run_04 */ {
        STEP(0, 37),
    },
    /* run_05 */ {
        STEP(0, 38),
    },
    /* run_06 */ {
        STEP(0, 39),
    },
    /* run_07 */ {
        STEP(0, 40),
    },
    /* run_08 */ {
        STEP(0, 41),
    },
    /* run_09 */ {
        STEP(0, 42),
    },
    /* run_10 */ {
        STEP(0, 43),
    },
    /* run_11 */ {
        STEP(0, 44),
    },
    /* run_12 */ {
        STEP(0, 45),
    },
    /* run_13 */ {
        STEP(0, 46),
    },
    /* run_14 */ {
        STEP(0, 47),
    },
    /* run_15 */ {
        STEP(0, 48),
    },
    /* run_16 */ {
        STEP(0, 49),
    },
    /* run_17 */ {
        STEP(0, 50),
    },
    /* run_18 */ {
        STEP(0, 51),
    },
    /* run_19 */ {
        STEP(0, 52),
    },
    /* run_20 */ {
        STEP(0, 53),
    },
    /* run_21 */ {
        STEP(0, 54),
    },
    /* run_22 */ {
        STEP(0, 55),
    },
    /* run_23 */ {
        STEP(0, 56),
    },
    /* run_24 */ {
        STEP(0, 57),
    },
    /* run_25 */ {
        STEP(0, 58),
    },
    /* run_26 */ {
        STEP(0, 59),
    },
    /* run_27 */ {
        STEP(0, 60),
    },
    /* run_28 */ {
        STEP(0, 61),
    },
    /* run_29 */ {
        STEP(0, 62),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RUN_00),
    },
    /* settle_from_run_01 */ {
        STEP(0, 34),
    },
    /* settle_from_run_02 */ {
        STEP(0, 35),
    },
    /* settle_from_run_03 */ {
        STEP(0, 36),
    },
    /* settle_from_run_04 */ {
        STEP(0, 37),
    },
    /* settle_from_run_05 */ {
        STEP(0, 38),
    },
    /* settle_from_run_06 */ {
        STEP(0, 39),
    },
    /* settle_from_run_07 */ {
        STEP(0, 40),
    },
    /* settle_from_run_08 */ {
        STEP(0, 41),
    },
    /* settle_from_run_09 */ {
        STEP(0, 42),
    },
    /* settle_from_run_10 */ {
        STEP(0, 43),
    },
    /* settle_from_run_11 */ {
        STEP(0, 44),
    },
    /* settle_from_run_12 */ {
        STEP(0, 45),
    },
    /* settle_from_run_13 */ {
        STEP(0, 46),
    },
    /* settle_from_run_14 */ {
        STEP(0, 47),
    },
    /* settle_from_run_15 */ {
        STEP(0, 48),
    },
    /* settle_from_run_16 */ {
        STEP(0, 49),
    },
    /* settle_from_run_17 */ {
        STEP(0, 50),
    },
    /* settle_from_run_18 */ {
        STEP(0, 51),
    },
    /* settle_from_run_19 */ {
        STEP(0, 52),
    },
    /* settle_from_run_20 */ {
        STEP(0, 53),
    },
    /* settle_from_run_21 */ {
        STEP(0, 54),
    },
    /* settle_from_run_22 */ {
        STEP(0, 55),
    },
    /* settle_from_run_23 */ {
        STEP(0, 56),
    },
    /* settle_from_run_24 */ {
        STEP(0, 57),
    },
    /* settle_from_run_25 */ {
        STEP(0, 58),
    },
    /* settle_from_run_26 */ {
        STEP(0, 59),
    },
    /* settle_from_run_27 */ {
        STEP(0, 60),
    },
    /* settle_from_run_28 */ {
        STEP(0, 61),
    },
    /* settle_from_run_29 */ {
        STEP(0, 62),
    },
    /* settle */ {
        STEP(0, 65),
        STEP(0, 66),
        STEP(0, 67),
        STEP(0, 68),
        STEP(0, 69),
        STEP(0, 70),
        STEP(0, 71),
        STEP(0, 72),
        STEP(0, 73),
        STEP(0, 74),
        STEP(0, 75),
        STEP(0, 76),
        STEP(0, 77),
        STEP(0, 78),
        STEP(0, 79),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE),
    },
    /* transition_alt_from_run_17 */ {
        STEP(0, 50),
    },
    /* transition_alt_from_run_18 */ {
        STEP(0, 51),
    },
    /* transition_alt_from_run_19 */ {
        STEP(0, 52),
    },
    /* transition_alt_from_run_20 */ {
        STEP(0, 53),
    },
    /* transition_alt_from_run_21 */ {
        STEP(0, 54),
    },
    /* transition_alt_from_run_22 */ {
        STEP(0, 55),
    },
    /* transition_alt_from_run_23 */ {
        STEP(0, 56),
    },
    /* transition_alt_from_run_24 */ {
        STEP(0, 57),
    },
    /* transition_alt_from_run_25 */ {
        STEP(0, 58),
    },
    /* transition_alt_from_run_26 */ {
        STEP(0, 59),
    },
    /* transition_alt_from_run_27 */ {
        STEP(0, 60),
    },
    /* transition_alt_from_run_28 */ {
        STEP(0, 61),
    },
    /* transition_alt_from_run_29 */ {
        STEP(0, 62),
    },
    /* transition_alt_from_run_00 */ {
        STEP(0, 33),
    },
    /* transition_alt_from_run_01 */ {
        STEP(0, 34),
    },
    /* transition_alt_from_run_02 */ {
        STEP(0, 35),
    },
    /* transition_alt_from_run_03 */ {
        STEP(0, 36),
    },
    /* transition_alt_from_run_04 */ {
        STEP(0, 37),
    },
    /* transition_alt_from_run_05 */ {
        STEP(0, 38),
    },
    /* transition_alt_from_run_06 */ {
        STEP(0, 39),
    },
    /* transition_alt_from_run_07 */ {
        STEP(0, 40),
    },
    /* transition_alt_from_run_08 */ {
        STEP(0, 41),
    },
    /* transition_alt_from_run_09 */ {
        STEP(0, 42),
    },
    /* transition_alt_from_run_10 */ {
        STEP(0, 43),
    },
    /* transition_alt_from_run_11 */ {
        STEP(0, 44),
    },
    /* transition_alt_from_run_12 */ {
        STEP(0, 45),
    },
    /* transition_alt_from_run_13 */ {
        STEP(0, 46),
    },
    /* transition_alt_from_run_14 */ {
        STEP(0, 47),
    },
    /* transition_alt_from_run_15 */ {
        STEP(0, 48),
    },
    /* transition_alt */ {
        STEP(1, 86),
        STEP(1, 87),
        STEP(1, 88),
        STEP(1, 89),
        STEP(1, 90),
        STEP(1, 91),
        STEP(1, 92),
        STEP(1, 93),
        STEP(1, 94),
        STEP(1, 95),
        STEP(1, 96),
        STEP(1, 97),
        STEP(1, 98),
        STEP(1, 99),
        STEP(1, 100),
        STEP(1, 101),
        STEP(1, 102),
        STEP(1, 103),
        STEP(1, 104),
        STEP(1, 105),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RUN_06),
    },
    /* transition_two_from_run_01 */ {
        STEP(0, 34),
    },
    /* transition_two_from_run_02 */ {
        STEP(0, 35),
    },
    /* transition_two_from_run_03 */ {
        STEP(0, 36),
    },
    /* transition_two_from_run_04 */ {
        STEP(0, 37),
    },
    /* transition_two_from_run_05 */ {
        STEP(0, 38),
    },
    /* transition_two_from_run_06 */ {
        STEP(0, 39),
    },
    /* transition_two_from_run_07 */ {
        STEP(0, 40),
    },
    /* transition_two_from_run_08 */ {
        STEP(0, 41),
    },
    /* transition_two_from_run_09 */ {
        STEP(0, 42),
    },
    /* transition_two_from_run_10 */ {
        STEP(0, 43),
    },
    /* transition_two_from_run_11 */ {
        STEP(0, 44),
    },
    /* transition_two_from_run_12 */ {
        STEP(0, 45),
    },
    /* transition_two_from_run_13 */ {
        STEP(0, 46),
    },
    /* transition_two_from_run_14 */ {
        STEP(0, 47),
    },
    /* transition_two_from_run_15 */ {
        STEP(0, 48),
    },
    /* transition_two_from_run_16 */ {
        STEP(0, 49),
    },
    /* transition_two_from_run_17 */ {
        STEP(0, 50),
    },
    /* transition_two_from_run_18 */ {
        STEP(0, 51),
    },
    /* transition_two_from_run_19 */ {
        STEP(0, 52),
    },
    /* transition_two_from_run_20 */ {
        STEP(0, 53),
    },
    /* transition_two_from_run_21 */ {
        STEP(0, 54),
    },
    /* transition_two_from_run_22 */ {
        STEP(0, 55),
    },
    /* transition_two_from_run_23 */ {
        STEP(0, 56),
    },
    /* transition_two_from_run_24 */ {
        STEP(0, 57),
    },
    /* transition_two_from_run_25 */ {
        STEP(0, 58),
    },
    /* transition_two_from_run_26 */ {
        STEP(0, 59),
    },
    /* transition_two_from_run_27 */ {
        STEP(0, 60),
    },
    /* transition_two_from_run_28 */ {
        STEP(0, 61),
    },
    /* transition_two_from_run_29 */ {
        STEP(0, 62),
    },
    /* transition_two */ {
        STEP(1, 108),
        STEP(1, 109),
        STEP(1, 110),
        STEP(1, 111),
        STEP(1, 112),
        STEP(1, 113),
        STEP(1, 114),
        STEP(1, 115),
        STEP(1, 116),
        STEP(1, 117),
        STEP(1, 118),
        STEP(1, 119),
        STEP(1, 120),
        STEP(1, 121),
        STEP(1, 122),
        STEP(1, 123),
        STEP(1, 124),
        STEP(1, 125),
        STEP(1, 126),
        STEP(1, 127),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RUN_20),
    },
    /* hold_lead */ {
        STEP(3, 129),
        STEP(3, 130),
        STEP(3, 131),
        STEP(3, 132),
        STEP(3, 133),
        STEP(3, 134),
        SOUND(0),
        STEP(3, 135),
        STEP(3, 136),
        STEP(3, 137),
        STEP(3, 138),
        STEP(3, 139),
        STEP(3, 140),
        STEP(3, 141),
    },
    /* hold */ {
        STEP(3, 142),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_HOLD),
    },
    /* release */ {
        STEP(3, 143),
        STEP(3, 144),
        STEP(3, 145),
        STEP(3, 146),
        STEP(3, 147),
        STEP(3, 148),
        STEP(3, 149),
        STEP(3, 150),
        STEP(3, 151),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE),
    },
    /* release_alt */ {
        STEP(3, 161),
        STEP(3, 162),
        STEP(3, 163),
        STEP(3, 164),
        STEP(3, 165),
        STEP(3, 166),
        STEP(3, 167),
        STEP(3, 168),
        STEP(3, 169),
        STEP(3, 170),
        STEP(3, 171),
        STEP(3, 172),
        STEP(3, 173),
        STEP(3, 174),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE),
    },
    /* release_long */ {
        STEP(3, 182),
        STEP(3, 183),
        STEP(3, 184),
        STEP(3, 185),
        STEP(3, 186),
        STEP(3, 187),
        STEP(3, 188),
        STEP(3, 189),
        STEP(3, 190),
        STEP(3, 191),
        STEP(3, 192),
        STEP(3, 193),
        STEP(3, 203),
        STEP(3, 204),
        STEP(3, 205),
        STEP(3, 206),
        STEP(3, 207),
        STEP(3, 208),
        STEP(3, 209),
        STEP(3, 210),
        STEP(3, 211),
        STEP(3, 212),
        STEP(3, 213),
        STEP(3, 214),
        STEP(3, 215),
        STEP(3, 216),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE),
    },
    /* fire_shot */ {
        STEP(2, 225),
        STEP(2, 226),
        STEP(2, 227),
        STEP(2, 228),
        STEP(2, 229),
        STEP(2, 230),
        STEP(2, 231),
        STEP(2, 232),
        STEP(2, 233),
        STEP(2, 234),
        STEP(2, 235),
        STEP(2, 236),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE),
    },
    /* hold_start_from_run_16 */ {
        STEP(0, 49),
    },
    /* hold_start_from_run_17 */ {
        STEP(0, 50),
    },
    /* hold_start_from_run_18 */ {
        STEP(0, 51),
    },
    /* hold_start_from_run_19 */ {
        STEP(0, 52),
    },
    /* hold_start_from_run_20 */ {
        STEP(0, 53),
    },
    /* hold_start_from_run_21 */ {
        STEP(0, 54),
    },
    /* hold_start_from_run_22 */ {
        STEP(0, 55),
    },
    /* hold_start_from_run_23 */ {
        STEP(0, 56),
    },
    /* hold_start_from_run_24 */ {
        STEP(0, 57),
    },
    /* hold_start_from_run_25 */ {
        STEP(0, 58),
    },
    /* hold_start_from_run_26 */ {
        STEP(0, 59),
    },
    /* hold_start_from_run_27 */ {
        STEP(0, 60),
    },
    /* hold_start_from_run_28 */ {
        STEP(0, 61),
    },
    /* hold_start_from_run_29 */ {
        STEP(0, 62),
    },
    /* hold_start_from_run_00 */ {
        STEP(0, 33),
    },
    /* hold_start_from_run_01 */ {
        STEP(0, 34),
    },
    /* hold_start_from_run_02 */ {
        STEP(0, 35),
    },
    /* hold_start_from_run_03 */ {
        STEP(0, 36),
    },
    /* hold_start_from_run_04 */ {
        STEP(0, 37),
    },
    /* hold_start_from_run_05 */ {
        STEP(0, 38),
    },
    /* hold_start_from_run_06 */ {
        STEP(0, 39),
    },
    /* hold_start_from_run_07 */ {
        STEP(0, 40),
    },
    /* hold_start_from_run_08 */ {
        STEP(0, 41),
    },
    /* hold_start_from_run_09 */ {
        STEP(0, 42),
    },
    /* hold_start_from_run_10 */ {
        STEP(0, 43),
    },
    /* hold_start_from_run_11 */ {
        STEP(0, 44),
    },
    /* hold_start_from_run_12 */ {
        STEP(0, 45),
    },
    /* hold_start_from_run_13 */ {
        STEP(0, 46),
    },
    /* hold_start_from_run_14 */ {
        STEP(0, 47),
    },
    /* hold_start */ {
        STEP(6, 257),
        STEP(6, 258),
        STEP(6, 259),
    },
    /* hold_alt */ {
        STEP(6, 260),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_HOLD_ALT),
    },
    /* hold_mid */ {
        STEP(6, 261),
        STEP(6, 262),
        STEP(6, 263),
    },
    /* hold_two */ {
        STEP(6, 264),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_HOLD_TWO),
    },
    /* impact_lead */ {
        STEP(6, 265),
        STEP(6, 266),
        STEP(6, 267),
        STEP(6, 268),
        SOUND(1),
        STEP(6, 269),
        STEP(6, 270),
        STEP(6, 271),
        STEP(6, 272),
    },
    /* impact_hold */ {
        STEP(6, 273),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IMPACT_HOLD),
    },
    /* recover */ {
        STEP(6, 274),
        STEP(2, 282),
        STEP(2, 283),
        STEP(2, 284),
        STEP(2, 285),
        STEP(2, 286),
        STEP(2, 287),
        STEP(2, 288),
        STEP(2, 289),
        STEP(2, 290),
        STEP(2, 291),
        STEP(2, 292),
        STEP(2, 293),
        STEP(2, 294),
        STEP(2, 295),
        STEP(2, 296),
        STEP(2, 297),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE),
    },
    /* recover_alt */ {
        STEP(2, 310),
        STEP(2, 311),
        STEP(2, 312),
        STEP(2, 313),
        STEP(2, 314),
        STEP(2, 315),
        STEP(2, 316),
        STEP(2, 317),
        STEP(2, 318),
        STEP(2, 319),
        STEP(2, 320),
        STEP(2, 321),
        STEP(2, 322),
        STEP(2, 323),
        STEP(2, 324),
        STEP(2, 377),
        STEP(2, 378),
        STEP(2, 379),
        STEP(2, 380),
        STEP(2, 381),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE),
    },
    /* hold_enter_alt_from_run_01 */ {
        STEP(0, 34),
    },
    /* hold_enter_alt_from_run_02 */ {
        STEP(0, 35),
    },
    /* hold_enter_alt_from_run_03 */ {
        STEP(0, 36),
    },
    /* hold_enter_alt_from_run_04 */ {
        STEP(0, 37),
    },
    /* hold_enter_alt_from_run_05 */ {
        STEP(0, 38),
    },
    /* hold_enter_alt_from_run_06 */ {
        STEP(0, 39),
    },
    /* hold_enter_alt_from_run_07 */ {
        STEP(0, 40),
    },
    /* hold_enter_alt_from_run_08 */ {
        STEP(0, 41),
    },
    /* hold_enter_alt_from_run_09 */ {
        STEP(0, 42),
    },
    /* hold_enter_alt_from_run_10 */ {
        STEP(0, 43),
    },
    /* hold_enter_alt_from_run_11 */ {
        STEP(0, 44),
    },
    /* hold_enter_alt_from_run_12 */ {
        STEP(0, 45),
    },
    /* hold_enter_alt_from_run_13 */ {
        STEP(0, 46),
    },
    /* hold_enter_alt_from_run_14 */ {
        STEP(0, 47),
    },
    /* hold_enter_alt_from_run_15 */ {
        STEP(0, 48),
    },
    /* hold_enter_alt_from_run_16 */ {
        STEP(0, 49),
    },
    /* hold_enter_alt_from_run_17 */ {
        STEP(0, 50),
    },
    /* hold_enter_alt_from_run_18 */ {
        STEP(0, 51),
    },
    /* hold_enter_alt_from_run_19 */ {
        STEP(0, 52),
    },
    /* hold_enter_alt_from_run_20 */ {
        STEP(0, 53),
    },
    /* hold_enter_alt_from_run_21 */ {
        STEP(0, 54),
    },
    /* hold_enter_alt_from_run_22 */ {
        STEP(0, 55),
    },
    /* hold_enter_alt_from_run_23 */ {
        STEP(0, 56),
    },
    /* hold_enter_alt_from_run_24 */ {
        STEP(0, 57),
    },
    /* hold_enter_alt_from_run_25 */ {
        STEP(0, 58),
    },
    /* hold_enter_alt_from_run_26 */ {
        STEP(0, 59),
    },
    /* hold_enter_alt_from_run_27 */ {
        STEP(0, 60),
    },
    /* hold_enter_alt_from_run_28 */ {
        STEP(0, 61),
    },
    /* hold_enter_alt_from_run_29 */ {
        STEP(0, 62),
    },
    /* hold_enter_alt */ {
        STEP(3, 327),
        STEP(3, 328),
        STEP(3, 329),
        STEP(3, 330),
        STEP(3, 331),
        STEP(3, 332),
        STEP(3, 333),
        STEP(3, 334),
        STEP(3, 335),
        STEP(3, 335),
        STEP(3, 335),
        STEP(3, 335),
        STEP(3, 335),
        STEP(3, 335),
        STEP(3, 335),
    },
    /* settle_hold */ {
        STEP(3, 335),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_SETTLE_HOLD),
    },
    /* return_idle */ {
        STEP(3, 336),
        STEP(3, 337),
        STEP(3, 338),
        STEP(3, 339),
        STEP(3, 340),
        STEP(3, 341),
        STEP(3, 342),
        STEP(3, 343),
        STEP(3, 344),
        STEP(3, 345),
        STEP(3, 346),
        STEP(3, 347),
        STEP(3, 348),
        STEP(3, 349),
        STEP(3, 350),
        STEP(3, 351),
        STEP(3, 352),
        STEP(3, 353),
        STEP(3, 354),
        STEP(3, 355),
        STEP(3, 356),
        STEP(3, 357),
        STEP(3, 358),
        STEP(3, 348),
        STEP(3, 349),
        STEP(3, 350),
        STEP(3, 351),
        STEP(3, 352),
        STEP(3, 353),
        STEP(3, 354),
        STEP(3, 355),
        STEP(3, 356),
        STEP(3, 357),
        STEP(3, 358),
        STEP(3, 366),
        STEP(3, 367),
        STEP(3, 368),
        STEP(3, 369),
        STEP(3, 370),
        STEP(3, 371),
        GOTO(CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE),
    },
    /* table */ {
        camouflaged_target_m5_boss_anims.idle, camouflaged_target_m5_boss_anims.transition_from_idle_01, camouflaged_target_m5_boss_anims.transition_from_idle_02, camouflaged_target_m5_boss_anims.transition_from_idle_03, camouflaged_target_m5_boss_anims.transition_from_idle_04, camouflaged_target_m5_boss_anims.transition_from_idle_05,
        camouflaged_target_m5_boss_anims.transition_from_idle_06, camouflaged_target_m5_boss_anims.transition_from_idle_07, camouflaged_target_m5_boss_anims.transition_from_idle_08, camouflaged_target_m5_boss_anims.transition_from_idle_09, camouflaged_target_m5_boss_anims.transition, camouflaged_target_m5_boss_anims.run_00,
        camouflaged_target_m5_boss_anims.run_01, camouflaged_target_m5_boss_anims.run_02, camouflaged_target_m5_boss_anims.run_03, camouflaged_target_m5_boss_anims.run_04, camouflaged_target_m5_boss_anims.run_05, camouflaged_target_m5_boss_anims.run_06,
        camouflaged_target_m5_boss_anims.run_07, camouflaged_target_m5_boss_anims.run_08, camouflaged_target_m5_boss_anims.run_09, camouflaged_target_m5_boss_anims.run_10, camouflaged_target_m5_boss_anims.run_11, camouflaged_target_m5_boss_anims.run_12,
        camouflaged_target_m5_boss_anims.run_13, camouflaged_target_m5_boss_anims.run_14, camouflaged_target_m5_boss_anims.run_15, camouflaged_target_m5_boss_anims.run_16, camouflaged_target_m5_boss_anims.run_17, camouflaged_target_m5_boss_anims.run_18,
        camouflaged_target_m5_boss_anims.run_19, camouflaged_target_m5_boss_anims.run_20, camouflaged_target_m5_boss_anims.run_21, camouflaged_target_m5_boss_anims.run_22, camouflaged_target_m5_boss_anims.run_23, camouflaged_target_m5_boss_anims.run_24,
        camouflaged_target_m5_boss_anims.run_25, camouflaged_target_m5_boss_anims.run_26, camouflaged_target_m5_boss_anims.run_27, camouflaged_target_m5_boss_anims.run_28, camouflaged_target_m5_boss_anims.run_29, camouflaged_target_m5_boss_anims.settle_from_run_01,
        camouflaged_target_m5_boss_anims.settle_from_run_02, camouflaged_target_m5_boss_anims.settle_from_run_03, camouflaged_target_m5_boss_anims.settle_from_run_04, camouflaged_target_m5_boss_anims.settle_from_run_05, camouflaged_target_m5_boss_anims.settle_from_run_06, camouflaged_target_m5_boss_anims.settle_from_run_07,
        camouflaged_target_m5_boss_anims.settle_from_run_08, camouflaged_target_m5_boss_anims.settle_from_run_09, camouflaged_target_m5_boss_anims.settle_from_run_10, camouflaged_target_m5_boss_anims.settle_from_run_11, camouflaged_target_m5_boss_anims.settle_from_run_12, camouflaged_target_m5_boss_anims.settle_from_run_13,
        camouflaged_target_m5_boss_anims.settle_from_run_14, camouflaged_target_m5_boss_anims.settle_from_run_15, camouflaged_target_m5_boss_anims.settle_from_run_16, camouflaged_target_m5_boss_anims.settle_from_run_17, camouflaged_target_m5_boss_anims.settle_from_run_18, camouflaged_target_m5_boss_anims.settle_from_run_19,
        camouflaged_target_m5_boss_anims.settle_from_run_20, camouflaged_target_m5_boss_anims.settle_from_run_21, camouflaged_target_m5_boss_anims.settle_from_run_22, camouflaged_target_m5_boss_anims.settle_from_run_23, camouflaged_target_m5_boss_anims.settle_from_run_24, camouflaged_target_m5_boss_anims.settle_from_run_25,
        camouflaged_target_m5_boss_anims.settle_from_run_26, camouflaged_target_m5_boss_anims.settle_from_run_27, camouflaged_target_m5_boss_anims.settle_from_run_28, camouflaged_target_m5_boss_anims.settle_from_run_29, camouflaged_target_m5_boss_anims.settle, camouflaged_target_m5_boss_anims.transition_alt_from_run_17,
        camouflaged_target_m5_boss_anims.transition_alt_from_run_18, camouflaged_target_m5_boss_anims.transition_alt_from_run_19, camouflaged_target_m5_boss_anims.transition_alt_from_run_20, camouflaged_target_m5_boss_anims.transition_alt_from_run_21, camouflaged_target_m5_boss_anims.transition_alt_from_run_22, camouflaged_target_m5_boss_anims.transition_alt_from_run_23,
        camouflaged_target_m5_boss_anims.transition_alt_from_run_24, camouflaged_target_m5_boss_anims.transition_alt_from_run_25, camouflaged_target_m5_boss_anims.transition_alt_from_run_26, camouflaged_target_m5_boss_anims.transition_alt_from_run_27, camouflaged_target_m5_boss_anims.transition_alt_from_run_28, camouflaged_target_m5_boss_anims.transition_alt_from_run_29,
        camouflaged_target_m5_boss_anims.transition_alt_from_run_00, camouflaged_target_m5_boss_anims.transition_alt_from_run_01, camouflaged_target_m5_boss_anims.transition_alt_from_run_02, camouflaged_target_m5_boss_anims.transition_alt_from_run_03, camouflaged_target_m5_boss_anims.transition_alt_from_run_04, camouflaged_target_m5_boss_anims.transition_alt_from_run_05,
        camouflaged_target_m5_boss_anims.transition_alt_from_run_06, camouflaged_target_m5_boss_anims.transition_alt_from_run_07, camouflaged_target_m5_boss_anims.transition_alt_from_run_08, camouflaged_target_m5_boss_anims.transition_alt_from_run_09, camouflaged_target_m5_boss_anims.transition_alt_from_run_10, camouflaged_target_m5_boss_anims.transition_alt_from_run_11,
        camouflaged_target_m5_boss_anims.transition_alt_from_run_12, camouflaged_target_m5_boss_anims.transition_alt_from_run_13, camouflaged_target_m5_boss_anims.transition_alt_from_run_14, camouflaged_target_m5_boss_anims.transition_alt_from_run_15, camouflaged_target_m5_boss_anims.transition_alt, camouflaged_target_m5_boss_anims.transition_two_from_run_01,
        camouflaged_target_m5_boss_anims.transition_two_from_run_02, camouflaged_target_m5_boss_anims.transition_two_from_run_03, camouflaged_target_m5_boss_anims.transition_two_from_run_04, camouflaged_target_m5_boss_anims.transition_two_from_run_05, camouflaged_target_m5_boss_anims.transition_two_from_run_06, camouflaged_target_m5_boss_anims.transition_two_from_run_07,
        camouflaged_target_m5_boss_anims.transition_two_from_run_08, camouflaged_target_m5_boss_anims.transition_two_from_run_09, camouflaged_target_m5_boss_anims.transition_two_from_run_10, camouflaged_target_m5_boss_anims.transition_two_from_run_11, camouflaged_target_m5_boss_anims.transition_two_from_run_12, camouflaged_target_m5_boss_anims.transition_two_from_run_13,
        camouflaged_target_m5_boss_anims.transition_two_from_run_14, camouflaged_target_m5_boss_anims.transition_two_from_run_15, camouflaged_target_m5_boss_anims.transition_two_from_run_16, camouflaged_target_m5_boss_anims.transition_two_from_run_17, camouflaged_target_m5_boss_anims.transition_two_from_run_18, camouflaged_target_m5_boss_anims.transition_two_from_run_19,
        camouflaged_target_m5_boss_anims.transition_two_from_run_20, camouflaged_target_m5_boss_anims.transition_two_from_run_21, camouflaged_target_m5_boss_anims.transition_two_from_run_22, camouflaged_target_m5_boss_anims.transition_two_from_run_23, camouflaged_target_m5_boss_anims.transition_two_from_run_24, camouflaged_target_m5_boss_anims.transition_two_from_run_25,
        camouflaged_target_m5_boss_anims.transition_two_from_run_26, camouflaged_target_m5_boss_anims.transition_two_from_run_27, camouflaged_target_m5_boss_anims.transition_two_from_run_28, camouflaged_target_m5_boss_anims.transition_two_from_run_29, camouflaged_target_m5_boss_anims.transition_two, camouflaged_target_m5_boss_anims.hold_lead,
        camouflaged_target_m5_boss_anims.hold, camouflaged_target_m5_boss_anims.release, camouflaged_target_m5_boss_anims.release_alt, camouflaged_target_m5_boss_anims.release_long, camouflaged_target_m5_boss_anims.fire_shot, camouflaged_target_m5_boss_anims.hold_start_from_run_16,
        camouflaged_target_m5_boss_anims.hold_start_from_run_17, camouflaged_target_m5_boss_anims.hold_start_from_run_18, camouflaged_target_m5_boss_anims.hold_start_from_run_19, camouflaged_target_m5_boss_anims.hold_start_from_run_20, camouflaged_target_m5_boss_anims.hold_start_from_run_21, camouflaged_target_m5_boss_anims.hold_start_from_run_22,
        camouflaged_target_m5_boss_anims.hold_start_from_run_23, camouflaged_target_m5_boss_anims.hold_start_from_run_24, camouflaged_target_m5_boss_anims.hold_start_from_run_25, camouflaged_target_m5_boss_anims.hold_start_from_run_26, camouflaged_target_m5_boss_anims.hold_start_from_run_27, camouflaged_target_m5_boss_anims.hold_start_from_run_28,
        camouflaged_target_m5_boss_anims.hold_start_from_run_29, camouflaged_target_m5_boss_anims.hold_start_from_run_00, camouflaged_target_m5_boss_anims.hold_start_from_run_01, camouflaged_target_m5_boss_anims.hold_start_from_run_02, camouflaged_target_m5_boss_anims.hold_start_from_run_03, camouflaged_target_m5_boss_anims.hold_start_from_run_04,
        camouflaged_target_m5_boss_anims.hold_start_from_run_05, camouflaged_target_m5_boss_anims.hold_start_from_run_06, camouflaged_target_m5_boss_anims.hold_start_from_run_07, camouflaged_target_m5_boss_anims.hold_start_from_run_08, camouflaged_target_m5_boss_anims.hold_start_from_run_09, camouflaged_target_m5_boss_anims.hold_start_from_run_10,
        camouflaged_target_m5_boss_anims.hold_start_from_run_11, camouflaged_target_m5_boss_anims.hold_start_from_run_12, camouflaged_target_m5_boss_anims.hold_start_from_run_13, camouflaged_target_m5_boss_anims.hold_start_from_run_14, camouflaged_target_m5_boss_anims.hold_start, camouflaged_target_m5_boss_anims.hold_alt,
        camouflaged_target_m5_boss_anims.hold_mid, camouflaged_target_m5_boss_anims.hold_two, camouflaged_target_m5_boss_anims.impact_lead, camouflaged_target_m5_boss_anims.impact_hold, camouflaged_target_m5_boss_anims.recover, camouflaged_target_m5_boss_anims.recover_alt,
        camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_01, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_02, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_03, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_04, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_05, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_06,
        camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_07, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_08, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_09, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_10, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_11, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_12,
        camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_13, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_14, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_15, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_16, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_17, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_18,
        camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_19, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_20, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_21, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_22, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_23, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_24,
        camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_25, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_26, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_27, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_28, camouflaged_target_m5_boss_anims.hold_enter_alt_from_run_29, camouflaged_target_m5_boss_anims.hold_enter_alt,
        camouflaged_target_m5_boss_anims.settle_hold, camouflaged_target_m5_boss_anims.return_idle,
    },
};

s16 camouflaged_target_m5_boss_lock_wait_one[8] = {
    CAMOUFLAGED_TARGET_M5_BOSS_LOCK, 1, CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ONE,
    WAIT(1),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_LOCK_WAIT_ONE),
};

s16 camouflaged_target_m5_boss_clear_one[4] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ACTORS, 1,
    SET_COUNTER(60),
};

s16 script_count_down[4] = {
    WAIT(1),
    LOOP(SCRIPT_COUNT_DOWN),
};

s16 camouflaged_target_m5_boss_phase_setup_one[6] = {
    CAMOUFLAGED_TARGET_M5_BOSS_STREAM_READ_U16, 16800,
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR2, 4,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_METER_ON),
};

s16 camouflaged_target_m5_boss_phase_reset_one[6] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ACTORS, 0,
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR2, 5,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_POWER_ON),
};

s16 camouflaged_target_m5_boss_lock_wait_two[8] = {
    CAMOUFLAGED_TARGET_M5_BOSS_LOCK, 2, CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_TWO,
    WAIT(1),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_LOCK_WAIT_TWO),
};

s16 camouflaged_target_m5_boss_clear_two[8] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ACTORS, 2,
    CAMOUFLAGED_TARGET_M5_BOSS_STREAM_READ_U16, 14400,
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR2, 7,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_METER_ON),
};

s16 camouflaged_target_m5_boss_phase_reset_two[6] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ACTORS, 0,
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR2, 8,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_POWER_ON),
};

s16 camouflaged_target_m5_boss_lock_wait_three[8] = {
    CAMOUFLAGED_TARGET_M5_BOSS_LOCK, 3, CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_THREE,
    WAIT(1),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_LOCK_WAIT_THREE),
};

s16 camouflaged_target_m5_boss_clear_three[8] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ACTORS, 3,
    CAMOUFLAGED_TARGET_M5_BOSS_STREAM_READ_U16, 12000,
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR2, 10,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_METER_ON),
};

s16 camouflaged_target_m5_boss_phase_reset_three[6] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ACTORS, 0,
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR2, 11,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_POWER_ON),
};

s16 camouflaged_target_m5_boss_lock_wait_four[8] = {
    CAMOUFLAGED_TARGET_M5_BOSS_LOCK, 4, CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_FOUR,
    WAIT(1),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_LOCK_WAIT_FOUR),
};

s16 camouflaged_target_m5_boss_clear_four[8] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ACTORS, 4,
    CAMOUFLAGED_TARGET_M5_BOSS_STREAM_READ_U16, 9600,
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR2, 13,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_METER_ON),
};

s16 camouflaged_target_m5_boss_phase_reset_four[6] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ACTORS, 0,
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR2, 14,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_POWER_ON),
};

s16 camouflaged_target_m5_boss_lock_wait_five[8] = {
    CAMOUFLAGED_TARGET_M5_BOSS_LOCK, 5, CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_FIVE,
    WAIT(1),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_LOCK_WAIT_FIVE),
};

s16 camouflaged_target_m5_boss_clear_five[6] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CLEAR_ACTORS, 5,
    CAMOUFLAGED_TARGET_M5_BOSS_STREAM_READ_U16, 0,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_METER_ON),
};

s16 camouflaged_target_m5_boss_meter_on[2] = {
    CAMOUFLAGED_TARGET_M5_BOSS_METER_MODE, 1,
};

s16 camouflaged_target_m5_boss_attack_choose[24] = {
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_FLAG_CLEAR, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_CHOOSE_ALT,
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR6, 19,
    JUMP_RANDOM(2048, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_CHOOSE_FAR),
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_BEYOND_POINT, 1280, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_CHOOSE_FAR,
    JUMP_RANDOM(2048, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_B),
    JUMP_RANDOM(2048, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_E),
    JUMP_RANDOM(2048, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_A),
    JUMP_RANDOM(2048, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_D),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_PICK_FLIGHT_POINT),
};

s16 camouflaged_target_m5_boss_attack_choose_far[14] = {
    JUMP_RANDOM(2048, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_E),
    JUMP_RANDOM(2048, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_B),
    JUMP_RANDOM(2048, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_D),
    JUMP_RANDOM(2048, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_A),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_PICK_FLIGHT_POINT),
};

s16 camouflaged_target_m5_boss_cooldown_start[6] = {
    SET_COUNTER_RANDOM(16, 32),
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_HEALTH_UNDER, 7680, CAMOUFLAGED_TARGET_M5_BOSS_READY_GATE,
};

s16 camouflaged_target_m5_boss_cooldown_wait[10] = {
    CAMOUFLAGED_TARGET_M5_BOSS_HEALTH_JUMP, CAMOUFLAGED_TARGET_M5_BOSS_METER_OFF,
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_READY, CAMOUFLAGED_TARGET_M5_BOSS_READY_ENTER,
    WAIT(1),
    LOOP(CAMOUFLAGED_TARGET_M5_BOSS_COOLDOWN_WAIT),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_CHOOSE),
};

s16 camouflaged_target_m5_boss_ready_gate[6] = {
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_FLAG_CLEAR, CAMOUFLAGED_TARGET_M5_BOSS_COOLDOWN_ALT,
    CAMOUFLAGED_TARGET_M5_BOSS_HEALTH_JUMP, CAMOUFLAGED_TARGET_M5_BOSS_METER_OFF,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_READY_ENTER),
};

s16 camouflaged_target_m5_boss_ready_enter[2] = {
    NEXT_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_READY),
};

s16 camouflaged_target_m5_boss_state_seven_wait[8] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_HIT_REACT, CAMOUFLAGED_TARGET_M5_BOSS_STATE_SEVEN_WAIT),
    SET_COUNTER(8),
};

s16 camouflaged_target_m5_boss_post_state_wait[10] = {
    WAIT(1),
    LOOP(CAMOUFLAGED_TARGET_M5_BOSS_POST_STATE_WAIT),
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_HEALTH_UNDER, 7680, CAMOUFLAGED_TARGET_M5_BOSS_LOW_HEALTH_EFFECTS,
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_PAUSE_SHORT),
};

s16 camouflaged_target_m5_boss_low_health_effects[6] = {
    CAMOUFLAGED_TARGET_M5_BOSS_SPAWN_EFFECTS,
    SET_COUNTER(48),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_PAUSE_WAIT),
};

s16 camouflaged_target_m5_boss_pause_short[2] = {
    SET_COUNTER(8),
};

s16 camouflaged_target_m5_boss_pause_wait[6] = {
    WAIT(1),
    LOOP(CAMOUFLAGED_TARGET_M5_BOSS_PAUSE_WAIT),
    NEXT_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_RESUME),
};

s16 camouflaged_target_m5_boss_idle_wait[8] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_TRACK, CAMOUFLAGED_TARGET_M5_BOSS_IDLE_WAIT),
    SET_COUNTER_RANDOM(8, 8),
};

s16 camouflaged_target_m5_boss_idle_then_attack[8] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_TRACK, CAMOUFLAGED_TARGET_M5_BOSS_IDLE_THEN_ATTACK),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_CHOOSE),
};

s16 camouflaged_target_m5_boss_attack_choose_alt[14] = {
    CAMOUFLAGED_TARGET_M5_BOSS_CURSOR_READ_U16_MIRROR6, 32,
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_BEYOND_POINT, 1280, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_CHOOSE_ALT_FAR,
    JUMP_RANDOM(3072, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_C),
    JUMP_RANDOM(3072, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_D),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_PICK_FLIGHT_POINT),
};

s16 camouflaged_target_m5_boss_attack_choose_alt_far[8] = {
    JUMP_RANDOM(3072, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_D),
    JUMP_RANDOM(3072, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_C),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_PICK_FLIGHT_POINT),
};

s16 camouflaged_target_m5_boss_random_wait[4] = {
    SET_COUNTER_RANDOM(8, 8),
};

s16 camouflaged_target_m5_boss_cooldown_alt[8] = {
    CAMOUFLAGED_TARGET_M5_BOSS_HEALTH_JUMP, CAMOUFLAGED_TARGET_M5_BOSS_METER_OFF,
    WAIT(1),
    LOOP(CAMOUFLAGED_TARGET_M5_BOSS_COOLDOWN_ALT),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_CHOOSE_ALT),
};

s16 camouflaged_target_m5_boss_meter_off[3] = {
    12, 0, -3,
};

u16 D_80117C86 = 0x10;

s16 camouflaged_target_m5_boss_attack_a[4] = {
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_FLAG_CLEAR, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_C,
    NEXT_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_FIRE_BURST),
};

s16 camouflaged_target_m5_boss_attack_a_repeat[8] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_TRACK, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_A_REPEAT),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_A),
};

s16 camouflaged_target_m5_boss_attack_b[4] = {
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_FLAG_CLEAR, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_C,
    NEXT_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_FIRE_TWIN),
};

s16 camouflaged_target_m5_boss_attack_b_repeat[8] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_TRACK, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_B_REPEAT),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_B),
};

s16 camouflaged_target_m5_boss_attack_c[2] = {
    NEXT_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_FIRE_SHOT),
};

s16 camouflaged_target_m5_boss_attack_c_repeat[8] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_TRACK, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_C_REPEAT),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_C),
};

s16 camouflaged_target_m5_boss_attack_d[4] = {
    CAMOUFLAGED_TARGET_M5_BOSS_STORE_STAGE_PARAM,
    NEXT_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_APPROACH),
};

s16 camouflaged_target_m5_boss_attack_d_repeat[8] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_TRACK, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_D_REPEAT),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_D),
};

s16 camouflaged_target_m5_boss_attack_e[6] = {
    CAMOUFLAGED_TARGET_M5_BOSS_JUMP_IF_FLAG_CLEAR, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_D,
    CAMOUFLAGED_TARGET_M5_BOSS_STORE_STAGE_PARAM,
    NEXT_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_APPROACH_ALT),
};

s16 camouflaged_target_m5_boss_attack_e_repeat[8] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_TRACK, CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_E_REPEAT),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_ATTACK_E),
};

s16 camouflaged_target_m5_boss_pick_flight_point[4] = {
    CAMOUFLAGED_TARGET_M5_BOSS_PICK_POINT,
    CAMOUFLAGED_TARGET_M5_BOSS_STORE_STAGE_PARAM,
    NEXT_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_FLY_START),
};

s16 camouflaged_target_m5_boss_pick_flight_repeat[8] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_TRACK, CAMOUFLAGED_TARGET_M5_BOSS_PICK_FLIGHT_REPEAT),
    JUMP(CAMOUFLAGED_TARGET_M5_BOSS_PICK_FLIGHT_POINT),
};

s16 camouflaged_target_m5_boss_power_on[4] = {
    CAMOUFLAGED_TARGET_M5_BOSS_POWER_SWITCH, 1,
    SET_COUNTER(128),
};

s16 camouflaged_target_m5_boss_power_on_wait[8] = {
    WAIT(1),
    LOOP(CAMOUFLAGED_TARGET_M5_BOSS_POWER_ON_WAIT),
    CAMOUFLAGED_TARGET_M5_BOSS_STORE_STAGE_PARAM,
    NEXT_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_ROUTE),
};

s16 camouflaged_target_m5_boss_power_off_when_idle[6] = {
    WAIT(1),
    JUMP_UNLESS_STATE(CAMOUFLAGED_TARGET_M5_BOSS_STATE_TRACK, CAMOUFLAGED_TARGET_M5_BOSS_POWER_OFF_WHEN_IDLE),
};

s16 camouflaged_target_m5_boss_power_off[4] = {
    CAMOUFLAGED_TARGET_M5_BOSS_POWER_SWITCH, 0,
    SET_COUNTER(128),
};

s16 camouflaged_target_m5_boss_power_off_wait[4] = {
    WAIT(1),
    LOOP(CAMOUFLAGED_TARGET_M5_BOSS_POWER_OFF_WAIT),
};

s16 camouflaged_target_m5_boss_power_restart = -3;

u16 D_80117D4E = 0x2F;

s16 *camouflaged_target_m5_script_data[53] = {
    camouflaged_target_m5_boss_lock_wait_one, camouflaged_target_m5_boss_clear_one, script_count_down, camouflaged_target_m5_boss_phase_setup_one, camouflaged_target_m5_boss_phase_reset_one, camouflaged_target_m5_boss_lock_wait_two,
    camouflaged_target_m5_boss_clear_two, camouflaged_target_m5_boss_phase_reset_two, camouflaged_target_m5_boss_lock_wait_three, camouflaged_target_m5_boss_clear_three, camouflaged_target_m5_boss_phase_reset_three, camouflaged_target_m5_boss_lock_wait_four,
    camouflaged_target_m5_boss_clear_four, camouflaged_target_m5_boss_phase_reset_four, camouflaged_target_m5_boss_lock_wait_five, camouflaged_target_m5_boss_clear_five, camouflaged_target_m5_boss_meter_on, camouflaged_target_m5_boss_attack_choose,
    camouflaged_target_m5_boss_attack_choose_far, camouflaged_target_m5_boss_cooldown_start, camouflaged_target_m5_boss_cooldown_wait, camouflaged_target_m5_boss_ready_gate, camouflaged_target_m5_boss_ready_enter, camouflaged_target_m5_boss_state_seven_wait,
    camouflaged_target_m5_boss_post_state_wait, camouflaged_target_m5_boss_low_health_effects, camouflaged_target_m5_boss_pause_short, camouflaged_target_m5_boss_pause_wait, camouflaged_target_m5_boss_idle_wait, camouflaged_target_m5_boss_idle_then_attack,
    camouflaged_target_m5_boss_attack_choose_alt, camouflaged_target_m5_boss_attack_choose_alt_far, camouflaged_target_m5_boss_random_wait, camouflaged_target_m5_boss_cooldown_alt, camouflaged_target_m5_boss_meter_off, camouflaged_target_m5_boss_attack_a,
    camouflaged_target_m5_boss_attack_a_repeat, camouflaged_target_m5_boss_attack_b, camouflaged_target_m5_boss_attack_b_repeat, camouflaged_target_m5_boss_attack_c, camouflaged_target_m5_boss_attack_c_repeat, camouflaged_target_m5_boss_attack_d,
    camouflaged_target_m5_boss_attack_d_repeat, camouflaged_target_m5_boss_attack_e, camouflaged_target_m5_boss_attack_e_repeat, camouflaged_target_m5_boss_pick_flight_point, camouflaged_target_m5_boss_pick_flight_repeat, camouflaged_target_m5_boss_power_on,
    camouflaged_target_m5_boss_power_on_wait, camouflaged_target_m5_boss_power_off_when_idle, camouflaged_target_m5_boss_power_off, camouflaged_target_m5_boss_power_off_wait, &camouflaged_target_m5_boss_power_restart,
};

s16 *D_80117E24[1] = {
    camouflaged_target_m5_boss_lock_wait_one,
};

ScriptCallEntry m5_boss_call_table[22] = {
    {NULL, 0},
    {script_store_stage_param, 0},
    {obj_type_params_set, 0},
    {obj_type_param_store_a, 0},
    {obj_type_param_store_b, 0},
    {shot_homing_store_type_param, 0},
    {chase_player_store_type_param, 0},
    {script_op_power_switch, 0},
    {cursor_read_u16_mirror2, 0},
    {cursor_read_u16_mirror6, 0},
    {stream_read_u16, 0},
    {script_op_health_jump, 0},
    {script_op_meter_mode, 0},
    {script_op_target_lock, 0},
    {script_op_clear_actors, 0},
    {obj_spawn_effects, 0},
    {script_op_jump_if_flag_clear, 0},
    {script_op_jump_if_ready, 0},
    {script_op_jump_if_health_under, 0},
    {script_op_jump_if_near_point, 0},
    {script_op_jump_if_beyond_point, 0},
    {camouflaged_target_pick_point, 0},
};

StateEntry m5_boss_states[28] = {
    {(u32)func_800C093C, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IDLE, 0},
    {(u32)obj_flight_setup, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_TRANSITION_FROM_IDLE_01, 1},
    {(u32)obj_fly_step, -1, 1},
    {(u32)obj_restore_velocity, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_SETTLE_FROM_RUN_01, 1},
    {0, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_TRANSITION_ALT_FROM_RUN_01, 1},
    {0, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_TRANSITION_TWO_FROM_RUN_01, 1},
    {(u32)func_800C093C, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_HOLD_LEAD, 1},
    {(u32)obj_turn_to_player_hit_reset, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_HOLD, 1},
    {(u32)func_800C093C, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RELEASE, 1},
    {(u32)obj_turn_fire_burst, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RELEASE_ALT, 0},
    {(u32)obj_turn_to_player_yaw, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RELEASE_LONG, 0},
    {(u32)obj_turn_fire_shot, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_FIRE_SHOT, 0},
    {(u32)obj_fly_turn_to_player, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_TRANSITION_FROM_IDLE_01, 1},
    {(u32)shot_homing_update, -1, 1},
    {(u32)projectile_home_update, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_HOLD_START_FROM_RUN_01, 1},
    {(u32)obj_airborne_step, -1, 1},
    {(u32)obj_sweep_step, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_HOLD_MID, 1},
    {(u32)obj_bounce, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_IMPACT_LEAD, 1},
    {(u32)obj_landing_step, -1, 1},
    {0, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RECOVER, 1},
    {(u32)obj_death_effect, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RECOVER_ALT, 1},
    {0, -1, 1},
    {(u32)func_800C1B28, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_TRANSITION_FROM_IDLE_01, 1},
    {(u32)chase_player_update, -1, 1},
    {(u32)chaser_fly_update, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_HOLD_ENTER_ALT_FROM_RUN_01, 1},
    {(u32)obj_retreat_move, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_RETURN_IDLE, 1},
    {(u32)camouflaged_target_route_update, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_TRANSITION_FROM_IDLE_01, 1},
    {(u32)obj_apply_stored_velocity, CAMOUFLAGED_TARGET_M5_BOSS_ANIM_SETTLE_FROM_RUN_01, 1},
};

u16 D_80117FB8[10] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 0xA,
};

u16 obj_type_param_table[30] = {
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,
    0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
};

u16 D_80118008[30] = {
    0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C,
    0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64,
    0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E,
    0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
};

u16 D_80118044[30] = {
    0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C,
    0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
    0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C,
    0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82,
};

u16 shot_homing_param_table[30] = {
    0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0x89,
    0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91,
    0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
};

u16 chase_player_param_table[30] = {
    0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5,
    0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD,
    0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5,
    0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB,
};

FxRecordParams death_effect_params[2] = {
    {1, 0, 0x3F, 0xFF, 0, 0x55, {0x86000, 0x24000, -0x800, 0x8000}},
    {1, 0xFF, 0xFF, 0xFF, 0, 0x55, {0xC6000, 0x24000, -0x800, 0x8000}},
};

s16 D_80118128[4] = {
    0x112, 0x155, 0x160, -1,
};

s16 D_80118130[4] = {
    0x112, 0x155, 0x160, -1,
};

s16 D_80118138[16] = {
    0x31, 0x48, 0x56, 0x7C, 0x85, 0xD5, 0x101, 0x112,
    0x12E, 0x136, 0x140, 0x14F, 0x15B, 0x166, -1, 0,
};

s16 D_80118158[16] = {
    0x1A, 0x22, 0x42, 0x65, 0x6D, 0xAB, 0xC0, 0xED,
    0x112, 0x136, 0x147, 0x151, 0x15B, 0x166, -1, 0,
};

ObjHandlerFn camouflaged_target_m5_boss_states[2] = {
    enemy_health_update, obj_call_hook,
};

s16 laser_slice_table[2][4] = {
    {0x180, 0x64, 10, 0x24}, {0x181, 0x64, 12, 0x24},
};

s32 d_80118190 = 0;

s32 screen_fade_amount = 0;

s16 D_80118198[8][2] = {
    {0x1000, 0x1000}, {0x1000, 0x1000}, {0x1000, 0xC00}, {0xC00, 0x800}, {0x800, 0x400}, {0x400, 0},
    {0, 0}, {0, 0},
};

s16 D_801181B8[8][2] = {
    {0x1000, 0x800}, {0x800, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
    {0, 0x800}, {0x800, 0x1000},
};

struct SparkScriptPtrStreams {
    s16 spark_script_a[4];
    s16 rocket_boat_spark_anim_idle[4];
    s16 *table[2];
} spark_script_ptr_streams = {
    /* spark_script_a */ {
        STEP(48, 421),
        STEP(48, 422),
    },
    /* rocket_boat_spark_anim_idle */ {
        STEP(48, 423),
        GOTO(ROCKET_BOAT_SPARK_ANIM_IDLE),
    },
    /* table */ {
        spark_script_ptr_streams.spark_script_a, spark_script_ptr_streams.rocket_boat_spark_anim_idle,
    },
};

#include "../stage/data/effect_template.c"

#include "../stage/data/effect_callback_table.c"

#include "../stage/data/fx_owner_template_a.c"

#include "../stage/data/obj_fx_template_a.c"

#include "../stage/data/obj_fx_template_b.c"

#include "../stage/data/d_8011ACDC.c"

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

u16 atan_table[722] = {
    0x0000, 0x0001, 0x0002, 0x0002, 0x0003, 0x0003, 0x0004, 0x0005,
    0x0005, 0x0006, 0x0007, 0x0007, 0x0008, 0x0009, 0x0009, 0x000A,
    0x000A, 0x000B, 0x000C, 0x000C, 0x000D, 0x000E, 0x000E, 0x000F,
    0x0010, 0x0010, 0x0011, 0x0011, 0x0012, 0x0013, 0x0013, 0x0014,
    0x0015, 0x0015, 0x0016, 0x0017, 0x0017, 0x0018, 0x0018, 0x0019,
    0x001A, 0x001A, 0x001B, 0x001C, 0x001C, 0x001D, 0x001E, 0x001E,
    0x001F, 0x001F, 0x0020, 0x0021, 0x0021, 0x0022, 0x0023, 0x0023,
    0x0024, 0x0024, 0x0025, 0x0026, 0x0026, 0x0027, 0x0028, 0x0028,
    0x0029, 0x002A, 0x002A, 0x002B, 0x002B, 0x002C, 0x002D, 0x002D,
    0x002E, 0x002F, 0x002F, 0x0030, 0x0031, 0x0031, 0x0032, 0x0032,
    0x0033, 0x0034, 0x0034, 0x0035, 0x0036, 0x0036, 0x0037, 0x0037,
    0x0038, 0x0039, 0x0039, 0x003A, 0x003B, 0x003B, 0x003C, 0x003D,
    0x003D, 0x003E, 0x003E, 0x003F, 0x0040, 0x0040, 0x0041, 0x0042,
    0x0042, 0x0043, 0x0043, 0x0044, 0x0045, 0x0045, 0x0046, 0x0047,
    0x0047, 0x0048, 0x0049, 0x0049, 0x004A, 0x004A, 0x004B, 0x004C,
    0x004C, 0x004D, 0x004E, 0x004E, 0x004F, 0x004F, 0x0050, 0x0051,
    0x0051, 0x0052, 0x0053, 0x0053, 0x0054, 0x0054, 0x0055, 0x0056,
    0x0056, 0x0057, 0x0058, 0x0058, 0x0059, 0x0059, 0x005A, 0x005B,
    0x005B, 0x005C, 0x005D, 0x005D, 0x005E, 0x005E, 0x005F, 0x0060,
    0x0060, 0x0061, 0x0062, 0x0062, 0x0063, 0x0063, 0x0064, 0x0065,
    0x0065, 0x0066, 0x0067, 0x0067, 0x0068, 0x0068, 0x0069, 0x006A,
    0x006A, 0x006B, 0x006B, 0x006C, 0x006D, 0x006D, 0x006E, 0x006F,
    0x006F, 0x0070, 0x0070, 0x0071, 0x0072, 0x0072, 0x0073, 0x0074,
    0x0074, 0x0075, 0x0075, 0x0076, 0x0077, 0x0077, 0x0078, 0x0078,
    0x0079, 0x007A, 0x007A, 0x007B, 0x007C, 0x007C, 0x007D, 0x007D,
    0x007E, 0x007F, 0x007F, 0x0080, 0x0080, 0x0081, 0x0082, 0x0082,
    0x0083, 0x0083, 0x0084, 0x0085, 0x0085, 0x0086, 0x0087, 0x0087,
    0x0088, 0x0088, 0x0089, 0x008A, 0x008A, 0x008B, 0x008B, 0x008C,
    0x008D, 0x008D, 0x008E, 0x008E, 0x008F, 0x0090, 0x0090, 0x0091,
    0x0091, 0x0092, 0x0093, 0x0093, 0x0094, 0x0094, 0x0095, 0x0096,
    0x0096, 0x0097, 0x0098, 0x0098, 0x0099, 0x0099, 0x009A, 0x009B,
    0x009B, 0x009C, 0x009C, 0x009D, 0x009E, 0x009E, 0x009F, 0x009F,
    0x00A0, 0x00A1, 0x00A1, 0x00A2, 0x00A2, 0x00A3, 0x00A4, 0x00A4,
    0x00A5, 0x00A5, 0x00A6, 0x00A6, 0x00A7, 0x00A8, 0x00A8, 0x00A9,
    0x00A9, 0x00AA, 0x00AB, 0x00AB, 0x00AC, 0x00AC, 0x00AD, 0x00AE,
    0x00AE, 0x00AF, 0x00AF, 0x00B0, 0x00B1, 0x00B1, 0x00B2, 0x00B2,
    0x00B3, 0x00B4, 0x00B4, 0x00B5, 0x00B5, 0x00B6, 0x00B6, 0x00B7,
    0x00B8, 0x00B8, 0x00B9, 0x00B9, 0x00BA, 0x00BB, 0x00BB, 0x00BC,
    0x00BC, 0x00BD, 0x00BE, 0x00BE, 0x00BF, 0x00BF, 0x00C0, 0x00C0,
    0x00C1, 0x00C2, 0x00C2, 0x00C3, 0x00C3, 0x00C4, 0x00C5, 0x00C5,
    0x00C6, 0x00C6, 0x00C7, 0x00C7, 0x00C8, 0x00C9, 0x00C9, 0x00CA,
    0x00CA, 0x00CB, 0x00CB, 0x00CC, 0x00CD, 0x00CD, 0x00CE, 0x00CE,
    0x00CF, 0x00CF, 0x00D0, 0x00D1, 0x00D1, 0x00D2, 0x00D2, 0x00D3,
    0x00D3, 0x00D4, 0x00D5, 0x00D5, 0x00D6, 0x00D6, 0x00D7, 0x00D7,
    0x00D8, 0x00D9, 0x00D9, 0x00DA, 0x00DA, 0x00DB, 0x00DB, 0x00DC,
    0x00DD, 0x00DD, 0x00DE, 0x00DE, 0x00DF, 0x00DF, 0x00E0, 0x00E1,
    0x00E1, 0x00E2, 0x00E2, 0x00E3, 0x00E3, 0x00E4, 0x00E4, 0x00E5,
    0x00E6, 0x00E6, 0x00E7, 0x00E7, 0x00E8, 0x00E8, 0x00E9, 0x00EA,
    0x00EA, 0x00EB, 0x00EB, 0x00EC, 0x00EC, 0x00ED, 0x00ED, 0x00EE,
    0x00EF, 0x00EF, 0x00F0, 0x00F0, 0x00F1, 0x00F1, 0x00F2, 0x00F2,
    0x00F3, 0x00F4, 0x00F4, 0x00F5, 0x00F5, 0x00F6, 0x00F6, 0x00F7,
    0x00F7, 0x00F8, 0x00F8, 0x00F9, 0x00FA, 0x00FA, 0x00FB, 0x00FB,
    0x00FC, 0x00FC, 0x00FD, 0x00FD, 0x00FE, 0x00FE, 0x00FF, 0x0100,
    0x0100, 0x0101, 0x0101, 0x0102, 0x0102, 0x0103, 0x0103, 0x0104,
    0x0104, 0x0105, 0x0106, 0x0106, 0x0107, 0x0107, 0x0108, 0x0108,
    0x0109, 0x0109, 0x010A, 0x010A, 0x010B, 0x010B, 0x010C, 0x010D,
    0x010D, 0x010E, 0x010E, 0x010F, 0x010F, 0x0110, 0x0110, 0x0111,
    0x0111, 0x0112, 0x0112, 0x0113, 0x0113, 0x0114, 0x0114, 0x0115,
    0x0116, 0x0116, 0x0117, 0x0117, 0x0118, 0x0118, 0x0119, 0x0119,
    0x011A, 0x011A, 0x011B, 0x011B, 0x011C, 0x011C, 0x011D, 0x011D,
    0x011E, 0x011E, 0x011F, 0x0120, 0x0120, 0x0121, 0x0121, 0x0122,
    0x0122, 0x0123, 0x0123, 0x0124, 0x0124, 0x0125, 0x0125, 0x0126,
    0x0126, 0x0127, 0x0127, 0x0128, 0x0128, 0x0129, 0x0129, 0x012A,
    0x012A, 0x012B, 0x012B, 0x012C, 0x012C, 0x012D, 0x012D, 0x012E,
    0x012E, 0x012F, 0x012F, 0x0130, 0x0130, 0x0131, 0x0131, 0x0132,
    0x0133, 0x0133, 0x0134, 0x0134, 0x0135, 0x0135, 0x0136, 0x0136,
    0x0137, 0x0137, 0x0138, 0x0138, 0x0139, 0x0139, 0x013A, 0x013A,
    0x013B, 0x013B, 0x013C, 0x013C, 0x013D, 0x013D, 0x013E, 0x013E,
    0x013F, 0x013F, 0x0140, 0x0140, 0x0141, 0x0141, 0x0142, 0x0142,
    0x0142, 0x0143, 0x0143, 0x0144, 0x0144, 0x0145, 0x0145, 0x0146,
    0x0146, 0x0147, 0x0147, 0x0148, 0x0148, 0x0149, 0x0149, 0x014A,
    0x014A, 0x014B, 0x014B, 0x014C, 0x014C, 0x014D, 0x014D, 0x014E,
    0x014E, 0x014F, 0x014F, 0x0150, 0x0150, 0x0151, 0x0151, 0x0152,
    0x0152, 0x0153, 0x0153, 0x0154, 0x0154, 0x0154, 0x0155, 0x0155,
    0x0156, 0x0156, 0x0157, 0x0157, 0x0158, 0x0158, 0x0159, 0x0159,
    0x015A, 0x015A, 0x015B, 0x015B, 0x015C, 0x015C, 0x015D, 0x015D,
    0x015D, 0x015E, 0x015E, 0x015F, 0x015F, 0x0160, 0x0160, 0x0161,
    0x0161, 0x0162, 0x0162, 0x0163, 0x0163, 0x0164, 0x0164, 0x0164,
    0x0165, 0x0165, 0x0166, 0x0166, 0x0167, 0x0167, 0x0168, 0x0168,
    0x0169, 0x0169, 0x016A, 0x016A, 0x016A, 0x016B, 0x016B, 0x016C,
    0x016C, 0x016D, 0x016D, 0x016E, 0x016E, 0x016F, 0x016F, 0x0170,
    0x0170, 0x0170, 0x0171, 0x0171, 0x0172, 0x0172, 0x0173, 0x0173,
    0x0174, 0x0174, 0x0174, 0x0175, 0x0175, 0x0176, 0x0176, 0x0177,
    0x0177, 0x0178, 0x0178, 0x0179, 0x0179, 0x0179, 0x017A, 0x017A,
    0x017B, 0x017B, 0x017C, 0x017C, 0x017D, 0x017D, 0x017D, 0x017E,
    0x017E, 0x017F, 0x017F, 0x0180, 0x0180, 0x0181, 0x0181, 0x0181,
    0x0182, 0x0182, 0x0183, 0x0183, 0x0184, 0x0184, 0x0184, 0x0185,
    0x0185, 0x0186, 0x0186, 0x0187, 0x0187, 0x0187, 0x0188, 0x0188,
    0x0189, 0x0189, 0x018A, 0x018A, 0x018B, 0x018B, 0x018B, 0x018C,
    0x018C, 0x018D, 0x018D, 0x018E, 0x018E, 0x018E, 0x018F, 0x018F,
    0x0190, 0x0190,
};

u32 walker_step_sounds[151] = {
    0x01910191, 0x01920191, 0x01930192, 0x01930193, 0x01940194, 0x01950195,
    0x01960196, 0x01970196, 0x01980197, 0x01990198, 0x01990199, 0x019A019A,
    0x019B019B, 0x019C019B, 0x019D019C, 0x019D019D, 0x019E019E, 0x019F019F,
    0x01A001A0, 0x01A101A0, 0x01A201A1, 0x01A201A2, 0x01A301A3, 0x01A401A4,
    0x01A501A4, 0x01A601A5, 0x01A601A6, 0x01A701A7, 0x01A801A8, 0x01A901A9,
    0x01AA01A9, 0x01AB01AA, 0x01AB01AB, 0x01AC01AC, 0x01AD01AD, 0x01AE01AD,
    0x01AF01AE, 0x01AF01AF, 0x01B001B0, 0x01B101B0, 0x01B201B1, 0x01B201B2,
    0x01B301B3, 0x01B401B4, 0x01B501B4, 0x01B601B5, 0x01B601B6, 0x01B701B7,
    0x01B801B8, 0x01B901B8, 0x01B901B9, 0x01BA01BA, 0x01BB01BB, 0x01BC01BB,
    0x01BD01BC, 0x01BD01BD, 0x01BE01BE, 0x01BF01BE, 0x01C001BF, 0x01C001C0,
    0x01C101C1, 0x01C201C2, 0x01C301C2, 0x01C301C3, 0x01C401C4, 0x01C501C5,
    0x01C601C5, 0x01C601C6, 0x01C701C7, 0x01C801C8, 0x01C901C8, 0x01C901C9,
    0x01CA01CA, 0x01CB01CB, 0x01CC01CB, 0x01CC01CC, 0x01CD01CD, 0x01CE01CD,
    0x01CF01CE, 0x01CF01CF, 0x01D001D0, 0x01D101D0, 0x01D101D1, 0x01D201D2,
    0x01D301D3, 0x01D401D3, 0x01D401D4, 0x01D501D5, 0x01D601D5, 0x01D701D6,
    0x01D701D7, 0x01D801D8, 0x01D901D8, 0x01D901D9, 0x01DA01DA, 0x01DB01DA,
    0x01DC01DB, 0x01DC01DC, 0x01DD01DD, 0x01DE01DD, 0x01DE01DE, 0x01DF01DF,
    0x01E001DF, 0x01E001E0, 0x01E101E1, 0x01E201E1, 0x01E301E2, 0x01E301E3,
    0x01E401E4, 0x01E501E4, 0x01E501E5, 0x01E601E6, 0x01E701E6, 0x01E701E7,
    0x01E801E8, 0x01E901E8, 0x01E901E9, 0x01EA01EA, 0x01EB01EA, 0x01EB01EB,
    0x01EC01EC, 0x01ED01EC, 0x01ED01ED, 0x01EE01EE, 0x01EF01EE, 0x01EF01EF,
    0x01F001F0, 0x01F101F0, 0x01F101F1, 0x01F201F2, 0x01F301F2, 0x01F301F3,
    0x01F401F4, 0x01F501F4, 0x01F501F5, 0x01F601F6, 0x01F701F6, 0x01F701F7,
    0x01F801F8, 0x01F901F8, 0x01F901F9, 0x01FA01FA, 0x01FB01FA, 0x01FB01FB,
    0x01FC01FC, 0x01FD01FC, 0x01FD01FD, 0x01FE01FE, 0x01FF01FE, 0x01FF01FF,
    0x020001FF,
};

#include "../stage/data/rand_seed_table.c"

u32 D_8011CE28[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/tint_scale_r.c"

s16 video_mode_id WORD_ALIGNED = 0;

#include "../stage/data/debug_cam_speed_table.c"

#include "../stage/data/pause_prev_work_area.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_8011DFAC[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_8011E5CC = 0x00000000;

u16 texture_image[1404] = {
    0x4000, 0x4000, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1E1F,
    0x1E1E, 0x1D1E, 0x1D1D, 0x1C1C, 0x1B1C, 0x1B1B, 0x1A1A, 0x1919,
    0x1818, 0x1717, 0x1616, 0x1415, 0x1314, 0x1213, 0x1111, 0xF10,
    0xE0F, 0xC0D, 0xB0C, 0xA0A, 0x809, 0x707, 0x506, 0x304,
    0x203, 0x101, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1E1F,
    0x1E1E, 0x1D1E, 0x1D1D, 0x1C1C, 0x1B1C, 0x1B1B, 0x1A1A, 0x1919,
    0x1818, 0x1717, 0x1616, 0x1415, 0x1314, 0x1213, 0x1111, 0xF10,
    0xE0F, 0xC0D, 0xB0C, 0xA0A, 0x809, 0x707, 0x506, 0x304,
    0x203, 1, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1E1F,
    0x1E1E, 0x1D1E, 0x1D1D, 0x1C1C, 0x1B1C, 0x1A1B, 0x1A1A, 0x1919,
    0x1818, 0x1717, 0x1616, 0x1415, 0x1314, 0x1213, 0x1111, 0xF10,
    0xE0F, 0xC0D, 0xB0C, 0xA0A, 0x809, 0x607, 0x506, 0x304,
    0x203, 1, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1E1E,
    0x1E1E, 0x1D1E, 0x1D1D, 0x1C1C, 0x1B1C, 0x1A1B, 0x1A1A, 0x1919,
    0x1818, 0x1717, 0x1516, 0x1415, 0x1314, 0x1212, 0x1111, 0xF10,
    0xE0F, 0xC0D, 0xB0C, 0x90A, 0x809, 0x607, 0x506, 0x304,
    0x203, 1, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1E1E,
    0x1E1E, 0x1D1D, 0x1D1D, 0x1C1C, 0x1B1C, 0x1A1B, 0x1A1A, 0x1919,
    0x1818, 0x1717, 0x1516, 0x1415, 0x1314, 0x1212, 0x1011, 0xF10,
    0xE0E, 0xC0D, 0xB0C, 0x90A, 0x809, 0x607, 0x506, 0x304,
    0x203, 1, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1E1F, 0x1E1E,
    0x1E1E, 0x1D1D, 0x1D1D, 0x1C1C, 0x1B1B, 0x1A1B, 0x191A, 0x1919,
    0x1818, 0x1617, 0x1516, 0x1415, 0x1314, 0x1212, 0x1011, 0xF10,
    0xE0E, 0xC0D, 0xB0C, 0x90A, 0x809, 0x607, 0x506, 0x304,
    0x202, 1, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1E1F, 0x1E1E,
    0x1E1E, 0x1D1D, 0x1C1D, 0x1C1C, 0x1B1B, 0x1A1B, 0x191A, 0x1819,
    0x1718, 0x1617, 0x1516, 0x1415, 0x1313, 0x1212, 0x1011, 0xF10,
    0xE0E, 0xC0D, 0xB0B, 0x90A, 0x809, 0x607, 0x505, 0x304,
    0x202, 1, 0x1F1F, 0x1F1F, 0x1F1F, 0x1F1F, 0x1E1E, 0x1E1E,
    0x1D1E, 0x1D1D, 0x1C1D, 0x1C1C, 0x1B1B, 0x1A1A, 0x191A, 0x1819,
    0x1718, 0x1617, 0x1516, 0x1415, 0x1313, 0x1212, 0x1011, 0xF10,
    0xE0E, 0xC0D, 0xB0B, 0x90A, 0x808, 0x607, 0x505, 0x304,
    0x202, 1, 0x1F1F, 0x1F1F, 0x1F1F, 0x1E1F, 0x1E1E, 0x1E1E,
    0x1D1E, 0x1D1D, 0x1C1C, 0x1B1C, 0x1B1B, 0x1A1A, 0x191A, 0x1819,
    0x1718, 0x1617, 0x1516, 0x1414, 0x1313, 0x1112, 0x1011, 0xF0F,
    0xD0E, 0xC0D, 0xB0B, 0x90A, 0x808, 0x607, 0x505, 0x304,
    0x102, 1, 0x1F1F, 0x1F1F, 0x1E1F, 0x1E1E, 0x1E1E, 0x1E1E,
    0x1D1D, 0x1D1D, 0x1C1C, 0x1B1C, 0x1B1B, 0x1A1A, 0x1919, 0x1818,
    0x1718, 0x1617, 0x1515, 0x1414, 0x1313, 0x1112, 0x1011, 0xF0F,
    0xD0E, 0xC0D, 0xA0B, 0x90A, 0x708, 0x607, 0x405, 0x304,
    0x102, 1, 0x1F1F, 0x1E1F, 0x1E1E, 0x1E1E, 0x1E1E, 0x1D1E,
    0x1D1D, 0x1C1D, 0x1C1C, 0x1B1B, 0x1A1B, 0x1A1A, 0x1919, 0x1818,
    0x1717, 0x1616, 0x1515, 0x1414, 0x1213, 0x1112, 0x1010, 0xE0F,
    0xD0E, 0xC0C, 0xA0B, 0x90A, 0x708, 0x607, 0x405, 0x304,
    0x102, 1, 0x1E1E, 0x1E1E, 0x1E1E, 0x1E1E, 0x1E1E, 0x1D1D,
    0x1D1D, 0x1C1C, 0x1C1C, 0x1B1B, 0x1A1B, 0x191A, 0x1919, 0x1818,
    0x1717, 0x1616, 0x1515, 0x1314, 0x1213, 0x1112, 0x1010, 0xE0F,
    0xD0E, 0xC0C, 0xA0B, 0x909, 0x708, 0x606, 0x405, 0x303,
    0x102, 1, 0x1E1E, 0x1E1E, 0x1E1E, 0x1E1E, 0x1D1E, 0x1D1D,
    0x1D1D, 0x1C1C, 0x1B1C, 0x1B1B, 0x1A1A, 0x191A, 0x1819, 0x1718,
    0x1617, 0x1516, 0x1415, 0x1314, 0x1213, 0x1111, 0xF10, 0xE0F,
    0xD0D, 0xB0C, 0xA0B, 0x809, 0x708, 0x606, 0x405, 0x203,
    0x102, 0, 0x1E1E, 0x1E1E, 0x1E1E, 0x1D1E, 0x1D1D, 0x1D1D,
    0x1C1D, 0x1C1C, 0x1B1B, 0x1B1B, 0x1A1A, 0x1919, 0x1819, 0x1718,
    0x1617, 0x1516, 0x1415, 0x1314, 0x1212, 0x1111, 0xF10, 0xE0F,
    0xD0D, 0xB0C, 0xA0A, 0x809, 0x708, 0x506, 0x405, 0x203,
    0x102, 0, 0x1E1E, 0x1E1E, 0x1D1D, 0x1D1D, 0x1D1D, 0x1C1D,
    0x1C1C, 0x1C1C, 0x1B1B, 0x1A1B, 0x1A1A, 0x1919, 0x1818, 0x1717,
    0x1617, 0x1516, 0x1414, 0x1313, 0x1212, 0x1011, 0xF10, 0xE0E,
    0xC0D, 0xB0C, 0xA0A, 0x809, 0x707, 0x506, 0x404, 0x203,
    0x101, 0, 0x1D1D, 0x1D1D, 0x1D1D, 0x1D1D, 0x1D1D, 0x1C1C,
    0x1C1C, 0x1B1C, 0x1B1B, 0x1A1A, 0x191A, 0x1919, 0x1818, 0x1717,
    0x1616, 0x1515, 0x1414, 0x1313, 0x1112, 0x1011, 0xF0F, 0xE0E,
    0xC0D, 0xB0B, 0x90A, 0x809, 0x607, 0x506, 0x304, 0x203,
    0x101, 0, 0x1D1D, 0x1D1D, 0x1D1D, 0x1D1D, 0x1C1C, 0x1C1C,
    0x1B1C, 0x1B1B, 0x1A1B, 0x1A1A, 0x1919, 0x1819, 0x1718, 0x1617,
    0x1516, 0x1415, 0x1314, 0x1213, 0x1112, 0x1010, 0xF0F, 0xD0E,
    0xC0D, 0xB0B, 0x90A, 0x808, 0x607, 0x505, 0x304, 0x203,
    1, 0, 0x1D1D, 0x1D1D, 0x1D1D, 0x1C1C, 0x1C1C, 0x1C1C,
    0x1B1B, 0x1B1B, 0x1A1A, 0x191A, 0x1919, 0x1818, 0x1718, 0x1617,
    0x1516, 0x1415, 0x1314, 0x1213, 0x1111, 0x1010, 0xE0F, 0xD0E,
    0xC0C, 0xA0B, 0x90A, 0x708, 0x607, 0x505, 0x304, 0x202,
    1, 0, 0x1C1C, 0x1C1C, 0x1C1C, 0x1C1C, 0x1C1C, 0x1B1B,
    0x1B1B, 0x1A1B, 0x1A1A, 0x1919, 0x1819, 0x1818, 0x1717, 0x1616,
    0x1515, 0x1414, 0x1313, 0x1212, 0x1111, 0xF10, 0xE0F, 0xD0D,
    0xB0C, 0xA0B, 0x909, 0x708, 0x606, 0x405, 0x304, 0x102,
    1, 0, 0x1C1C, 0x1C1C, 0x1C1C, 0x1C1C, 0x1B1B, 0x1B1B,
    0x1B1B, 0x1A1A, 0x191A, 0x1919, 0x1818, 0x1718, 0x1617, 0x1616,
    0x1515, 0x1414, 0x1313, 0x1112, 0x1011, 0xF10, 0xE0E, 0xC0D,
    0xB0C, 0xA0A, 0x809, 0x708, 0x606, 0x405, 0x303, 0x102,
    1, 0, 0x1C1C, 0x1C1C, 0x1B1C, 0x1B1B, 0x1B1B, 0x1B1B,
    0x1A1A, 0x1A1A, 0x1919, 0x1819, 0x1818, 0x1717, 0x1617, 0x1516,
    0x1415, 0x1314, 0x1213, 0x1112, 0x1010, 0xF0F, 0xD0E, 0xC0D,
    0xB0C, 0x90A, 0x809, 0x707, 0x506, 0x405, 0x203, 0x102,
    0, 0, 0x1B1B, 0x1B1B, 0x1B1B, 0x1B1B, 0x1B1B, 0x1A1A,
    0x1A1A, 0x191A, 0x1919, 0x1818, 0x1718, 0x1717, 0x1616, 0x1515,
    0x1414, 0x1313, 0x1212, 0x1111, 0x1010, 0xE0F, 0xD0E, 0xC0C,
    0xB0B, 0x90A, 0x808, 0x607, 0x506, 0x404, 0x203, 0x101,
    0, 0, 0x1B1B, 0x1B1B, 0x1B1B, 0x1A1B, 0x1A1A, 0x1A1A,
    0x191A, 0x1919, 0x1819, 0x1818, 0x1717, 0x1617, 0x1516, 0x1515,
    0x1414, 0x1313, 0x1112, 0x1011, 0xF10, 0xE0F, 0xD0D, 0xC0C,
    0xA0B, 0x90A, 0x708, 0x607, 0x505, 0x304, 0x203, 0x101,
    0, 0, 0x1B1B, 0x1A1A, 0x1A1A, 0x1A1A, 0x1A1A, 0x191A,
    0x1919, 0x1919, 0x1818, 0x1718, 0x1717, 0x1616, 0x1515, 0x1415,
    0x1314, 0x1213, 0x1112, 0x1011, 0xF0F, 0xE0E, 0xC0D, 0xB0C,
    0xA0B, 0x909, 0x708, 0x606, 0x405, 0x304, 0x102, 1,
    0, 0, 0x1A1A, 0x1A1A, 0x1A1A, 0x1A1A, 0x191A, 0x1919,
    0x1919, 0x1818, 0x1818, 0x1717, 0x1617, 0x1516, 0x1515, 0x1414,
    0x1313, 0x1212, 0x1111, 0x1010, 0xF0F, 0xD0E, 0xC0D, 0xB0B,
    0xA0A, 0x809, 0x708, 0x506, 0x405, 0x303, 0x102, 1,
    0, 0, 0x1A1A, 0x1A1A, 0x191A, 0x1919, 0x1919, 0x1919,
    0x1818, 0x1818, 0x1717, 0x1617, 0x1616, 0x1515, 0x1415, 0x1314,
    0x1213, 0x1112, 0x1011, 0xF10, 0xE0F, 0xD0E, 0xC0C, 0xA0B,
    0x90A, 0x809, 0x707, 0x506, 0x404, 0x203, 0x102, 0,
    0, 0, 0x1919, 0x1919, 0x1919, 0x1919, 0x1819, 0x1818,
    0x1818, 0x1717, 0x1717, 0x1616, 0x1516, 0x1515, 0x1414, 0x1313,
    0x1212, 0x1111, 0x1010, 0xF0F, 0xE0E, 0xD0D, 0xB0C, 0xA0B,
    0x909, 0x708, 0x607, 0x505, 0x304, 0x203, 0x101, 0,
    0, 0, 0x1919, 0x1919, 0x1919, 0x1818, 0x1818, 0x1818,
    0x1717, 0x1717, 0x1616, 0x1616, 0x1515, 0x1415, 0x1314, 0x1213,
    0x1212, 0x1111, 0x1010, 0xE0F, 0xD0E, 0xC0D, 0xB0C, 0xA0A,
    0x809, 0x708, 0x606, 0x405, 0x304, 0x202, 0x101, 0,
    0, 0, 0x1818, 0x1818, 0x1818, 0x1818, 0x1818, 0x1717,
    0x1717, 0x1617, 0x1616, 0x1515, 0x1415, 0x1414, 0x1313, 0x1212,
    0x1112, 0x1011, 0xF10, 0xE0F, 0xD0D, 0xC0C, 0xB0B, 0x90A,
    0x809, 0x707, 0x506, 0x405, 0x303, 0x102, 1, 0,
    0, 0, 0x1818, 0x1818, 0x1818, 0x1717, 0x1717, 0x1717,
    0x1616, 0x1616, 0x1515, 0x1515, 0x1414, 0x1314, 0x1213, 0x1212,
    0x1111, 0x1010, 0xF0F, 0xE0E, 0xC0D, 0xB0C, 0xA0B, 0x90A,
    0x808, 0x607, 0x506, 0x404, 0x203, 0x102, 1, 0,
    0, 0, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1616,
    0x1616, 0x1516, 0x1515, 0x1414, 0x1314, 0x1313, 0x1212, 0x1111,
    0x1011, 0xF10, 0xE0F, 0xD0E, 0xC0D, 0xB0B, 0xA0A, 0x809,
    0x708, 0x607, 0x505, 0x304, 0x203, 0x101, 0, 0,
    0, 0, 0x1717, 0x1717, 0x1617, 0x1616, 0x1616, 0x1616,
    0x1515, 0x1515, 0x1414, 0x1414, 0x1313, 0x1213, 0x1112, 0x1111,
    0x1010, 0xF0F, 0xE0E, 0xD0D, 0xC0C, 0xA0B, 0x90A, 0x809,
    0x707, 0x606, 0x405, 0x304, 0x202, 1, 0, 0,
    0, 0, 0x1616, 0x1616, 0x1616, 0x1616, 0x1516, 0x1515,
    0x1515, 0x1414, 0x1414, 0x1313, 0x1213, 0x1212, 0x1111, 0x1010,
    0xF10, 0xE0F, 0xD0E, 0xC0D, 0xB0C, 0xA0B, 0x909, 0x808,
    0x607, 0x506, 0x404, 0x203, 0x102, 1, 0, 0,
    0, 0, 0x1616, 0x1516, 0x1515, 0x1515, 0x1515, 0x1515,
    0x1414, 0x1414, 0x1313, 0x1313, 0x1212, 0x1111, 0x1011, 0x1010,
    0xF0F, 0xE0E, 0xD0D, 0xC0C, 0xB0B, 0x90A, 0x809, 0x708,
    0x607, 0x505, 0x304, 0x203, 0x101, 0, 0, 0,
    0, 0, 0x1515, 0x1515, 0x1515, 0x1515, 0x1414, 0x1414,
    0x1414, 0x1313, 0x1313, 0x1212, 0x1112, 0x1111, 0x1010, 0xF0F,
    0xE0F, 0xD0E, 0xC0D, 0xB0C, 0xA0B, 0x90A, 0x808, 0x707,
    0x506, 0x405, 0x304, 0x202, 0x101, 0, 0, 0,
    0, 0, 0x1414, 0x1414, 0x1414, 0x1414, 0x1414, 0x1314,
    0x1313, 0x1313, 0x1212, 0x1112, 0x1111, 0x1010, 0xF10, 0xE0F,
    0xE0E, 0xD0D, 0xC0C, 0xB0B, 0xA0A, 0x809, 0x708, 0x607,
    0x506, 0x404, 0x203, 0x102, 1, 0, 0, 0,
    0, 0, 0x1414, 0x1414, 0x1414, 0x1313, 0x1313, 0x1313,
    0x1213, 0x1212, 0x1112, 0x1111, 0x1010, 0xF10, 0xF0F, 0xE0E,
    0xD0D, 0xC0D, 0xB0C, 0xA0B, 0x90A, 0x809, 0x707, 0x606,
    0x405, 0x304, 0x203, 0x101, 0, 0, 0, 0,
    0, 0, 0x1313, 0x1313, 0x1313, 0x1313, 0x1313, 0x1212,
    0x1212, 0x1112, 0x1111, 0x1011, 0x1010, 0xF0F, 0xE0F, 0xD0E,
    0xC0D, 0xC0C, 0xB0B, 0xA0A, 0x909, 0x708, 0x607, 0x506,
    0x405, 0x303, 0x202, 0x101, 0, 0, 0, 0,
    0, 0, 0x1313, 0x1213, 0x1212, 0x1212, 0x1212, 0x1212,
    0x1111, 0x1111, 0x1010, 0x1010, 0xF0F, 0xE0F, 0xE0E, 0xD0D,
    0xC0C, 0xB0B, 0xA0B, 0x90A, 0x809, 0x707, 0x606, 0x505,
    0x304, 0x203, 0x102, 1, 0, 0, 0, 0,
    0, 0, 0x1212, 0x1212, 0x1212, 0x1212, 0x1111, 0x1111,
    0x1111, 0x1010, 0x1010, 0xF0F, 0xE0F, 0xE0E, 0xD0D, 0xC0D,
    0xB0C, 0xA0B, 0x90A, 0x809, 0x708, 0x607, 0x506, 0x405,
    0x304, 0x202, 0x101, 0, 0, 0, 0, 0,
    0, 0, 0x1111, 0x1111, 0x1111, 0x1111, 0x1111, 0x1010,
    0x1010, 0xF10, 0xF0F, 0xE0F, 0xE0E, 0xD0D, 0xC0D, 0xC0C,
    0xB0B, 0xA0A, 0x909, 0x808, 0x707, 0x606, 0x505, 0x404,
    0x203, 0x102, 1, 0, 0, 0, 0, 0,
    0, 0, 0x1111, 0x1111, 0x1010, 0x1010, 0x1010, 0x1010,
    0xF0F, 0xF0F, 0xE0F, 0xE0E, 0xD0D, 0xC0D, 0xC0C, 0xB0B,
    0xA0B, 0x90A, 0x809, 0x708, 0x607, 0x506, 0x405, 0x304,
    0x203, 0x101, 1, 0, 0, 0, 0, 0,
    0, 0, 0x1010, 0x1010, 0x1010, 0x1010, 0xF0F, 0xF0F,
    0xF0F, 0xE0E, 0xE0E, 0xD0D, 0xC0D, 0xC0C, 0xB0B, 0xA0B,
    0xA0A, 0x909, 0x808, 0x707, 0x606, 0x505, 0x404, 0x303,
    0x102, 0x101, 0, 0, 0, 0, 0, 0,
    0, 0, 0xF0F, 0xF0F, 0xF0F, 0xF0F, 0xF0F, 0xE0E,
    0xE0E, 0xE0E, 0xD0D, 0xC0D, 0xC0C, 0xB0C, 0xA0B, 0xA0A,
    0x909, 0x808, 0x708, 0x607, 0x506, 0x405, 0x304, 0x203,
    0x101, 1, 0, 0,
};

u32 gun_turret_asset_s12[70] = {
    0x00000000, 0x00000000, 0x00000000, 0x0F0F0F0F, 0x0E0E0E0E, 0x0E0E0E0E,
    0x0D0D0D0D, 0x0C0C0C0D, 0x0B0B0B0C, 0x09090A0A, 0x07080809, 0x06060707,
    0x04040505, 0x01020303, 0x00000101, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x0E0E0E0E, 0x0E0E0E0E, 0x0D0D0D0D, 0x0C0C0D0D, 0x0B0B0C0C,
    0x0A0A0B0B, 0x0809090A, 0x07070808, 0x05050606, 0x03030404, 0x01010202,
    0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0D0D0D0D,
    0x0D0D0D0D, 0x0C0C0D0D, 0x0B0C0C0C, 0x0A0B0B0B, 0x090A0A0A, 0x08080909,
    0x06070707, 0x04050506, 0x02030304, 0x01010102, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0B0B0B0B, 0x0A0A0A0B, 0x09090909, 0x07070808, 0x06060607, 0x04040505,
    0x02020303, 0x00010101, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x0C0C0C0C, 0x0B0B0C0C, 0x0B0B0B0B,
};

u32 muzzle_x_table_s12[3] = {
    0x0A0A0A0B, 0x09090A0A, 0x08080809,
};

u32 muzzle_y_table_s12[251] = {
    0x06070708, 0x05050606, 0x03040404, 0x01020203, 0x00000101, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0B0B0B0B, 0x0B0B0B0B,
    0x0A0A0A0B, 0x090A0A0A, 0x08090909, 0x07070808, 0x06060707, 0x04050505,
    0x02030304, 0x01010202, 0x00000001, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x0A0A0A0A, 0x0A0A0A0A, 0x090A0A0A, 0x09090909,
    0x08080808, 0x06070707, 0x05050606, 0x04040405, 0x02020303, 0x00010101,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x090A0A0A, 0x09090909, 0x09090909, 0x08080808, 0x07070708, 0x06060607,
    0x04050505, 0x03030404, 0x01020202, 0x00000101, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x09090909, 0x08090909,
    0x08080808, 0x07070808, 0x06060707, 0x05050606, 0x04040405, 0x02030303,
    0x01010102, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x08080808, 0x08080808, 0x07070708, 0x06070707,
    0x06060606, 0x04050505, 0x03030404, 0x02020203, 0x00010101, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x07070707, 0x07070707, 0x06070707, 0x06060606, 0x05050505, 0x04040405,
    0x02030303, 0x01010202, 0x00000101, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x06060707, 0x06060606,
    0x06060606, 0x05050506, 0x04040505, 0x03030404, 0x02020203, 0x01010101,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x06060606, 0x05050606, 0x05050505, 0x04040505,
    0x03040404, 0x02030303, 0x01010202, 0x00000101, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x05050505, 0x05050505, 0x04040405, 0x03040404, 0x03030303, 0x01020202,
    0x01010101, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x04040404, 0x04040404,
    0x03040404, 0x03030303, 0x02020203, 0x01010102, 0x00010101, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x03030303, 0x03030303, 0x03030303, 0x02020202,
    0x01010202, 0x01010101, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x03030303, 0x02020203, 0x02020202, 0x01010202, 0x01010101, 0x00000101,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x02020202, 0x02020202,
    0x01010101, 0x01010101, 0x00010101, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x01010101, 0x01010101, 0x01010101, 0x00010101,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x01010101, 0x01010101, 0x00010101, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

s32 model_slot_count = 0;

#include "../stage/data/model_atlas_y.c"

#include "../stage/data/model_atlas_x.c"

#include "../stage/data/clut_count.c"

#include "../stage/data/model_slot_width.c"

#include "../stage/data/model_slot_height.c"

#include "../stage/data/block_map_buf.c"

#include "../stage/data/texel_mask_buf.c"

#include "../stage/data/clut_used_flags.c"

#include "../stage/data/last_env_colour_a.c"

#include "../stage/data/last_env_colour_b.c"

#include "../stage/data/last_env_colour_c.c"

#include "../stage/data/saved_pchr_count.c"

#include "../stage/data/saved_clut_count.c"

#include "../stage/data/saved_model_count.c"

#include "../stage/data/saved_atlas_y.c"

#include "../stage/data/saved_atlas_x.c"

#include "../stage/data/frame_work_area.c"

#include "../stage/data/d_8011FFE4.c"

u32 D_8011FADC = 0x00000000;

#include "../stage/data/ring32_index.c"

#include "../stage/data/vec3_x.c"

#include "../stage/data/vec3_y.c"

#include "../stage/data/vec3_z.c"

#include "../stage/data/vec3_pad.c"

#include "../stage/data/d_80120008.c"

#include "../stage/data/img_upload_active.c"

#include "../stage/data/light_data_base.c"

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

u32 D_8011FB60 = 0x00000000;

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

#include "../stage/data/interp_enabled_flag.c"

#include "../stage/data/interp_record_count.c"

#include "../stage/data/interp1c_count.c"

#include "../stage/data/interp2c_count.c"

#include "../stage/data/interp38_count.c"

#include "../stage/data/interp38b_count.c"

#include "../stage/data/pause_flag.c"

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

#include "../stage/data/meter_mode.c"

#include "../stage/data/gauge_flash_level.c"

#include "../stage/data/lock_spawn_timer.c"

#include "../stage/data/rec_table_enabled.c"

#include "../stage/data/lock_slot_phase.c"

#include "../stage/data/id_marker_pushed.c"

#include "../stage/data/pursuit_blend.c"

#include "../stage/data/cam_mode.c"

#include "../stage/data/cam_offset_x.c"

#include "../stage/data/cam_offset_y.c"

#include "../stage/data/pursuit_view_w.c"

#include "../stage/data/pursuit_view_h.c"

#include "../stage/data/target_current.c"

#include "../stage/data/target_requested.c"

#include "../stage/data/pursuit_spin_angle.c"

#include "../stage/data/pursue_msg_timer.c"

#include "../stage/data/pursuit_hold_timer.c"

#include "../stage/data/target_switch_timer.c"

#include "../stage/data/cam_path_last_seg.c"

#include "../stage/data/cam_path_start.c"

#include "../stage/data/cam_path_end.c"

#include "../stage/data/impact_effect_base.c"

#include "../stage/data/object_slots_free.c"

#include "../stage/data/spark_effect_base.c"

#include "../stage/data/spark_free_count.c"

#include "../stage/data/trail_ring_count.c"

#include "../stage/data/trail_ring_head.c"

#include "../stage/data/trail_ring_tail.c"

#include "../stage/data/grenade_effect_base.c"

#include "../stage/data/grenade_slots_free.c"

#include "../stage/data/proximity_hook_fn.c"

#include "../stage/data/lock_frame_base.c"

#include "../stage/data/lock_target_count.c"

#include "../stage/data/lock_mode.c"

#include "../stage/data/lock_cooldown_timer.c"

#include "../stage/data/fx_tpage.c"

#include "../stage/data/fx_clut_word.c"

#include "../stage/data/fx_saved_bk_red.c"

#include "../stage/data/fx_saved_bk_green.c"

#include "../stage/data/fx_saved_bk_blue.c"

#include "../stage/data/d_8012040C.c"

#include "../stage/data/d_80120410.c"

#include "../stage/data/sound_alloc_free_count.c"

#include "../stage/data/sound_fade_rate.c"

#include "../stage/data/sound_fade_step.c"

#include "../stage/data/sound_fade_level.c"

#include "../stage/data/sound_load_id.c"

#include "../stage/data/sound_load_flag.c"

#include "../stage/data/sound_load_handle.c"

#include "../stage/data/sound_timer.c"

#include "../stage/data/sound_master_volume.c"

#include "../stage/data/sound_listener_pitch.c"

#include "../stage/data/sound_listener_yaw.c"

#include "../stage/data/sound_listener_roll.c"

#include "../stage/data/sound_mode.c"

#include "../stage/data/sound_paused.c"

#include "../stage/data/sound_active_flag.c"

#include "../stage/data/sound_alloc_used_tail.c"

#include "../stage/data/sound_alloc_free_head.c"

#include "../stage/data/particle_base_ptr.c"

#include "../stage/data/wall_tables_ptr.c"

#include "../stage/data/placement_angle_table.c"

#include "../stage/data/cam_offset_blend.c"

#include "../stage/data/cam_offset_speed.c"

#include "../stage/data/cam_stick_offset.c"

#include "../stage/data/cam_aim_blend.c"

#include "../stage/data/d_80120470.c"

#include "../stage/data/player_model_pchr.c"

#include "../stage/data/player_model_state.c"

#include "../stage/data/player_model_enabled.c"

#include "../stage/data/player_model_on_flag.c"

#include "../stage/data/fade_level.c"

#include "../stage/data/player_mode_bits.c"

#include "../stage/data/player_mode_flags_saved.c"

#include "../stage/data/player_ceiling_limit.c"

#include "../stage/data/cam_follow_blend.c"

#include "../stage/data/cam_distance.c"

#include "../stage/data/d_8012049C.c"

#include "../stage/data/mover_angle_b.c"

#include "../stage/data/mover_angle_a.c"

#include "../stage/data/mover_angle_c.c"

#include "../stage/data/mover_min_dist.c"

#include "../stage/data/mover_max_dist.c"

#include "../stage/data/cur_view_index.c"

#include "../stage/data/light_env_index.c"

#include "../stage/data/player_mode.c"

#include "../stage/data/point_search_below.c"

#include "../stage/data/cur_camera_index.c"

#include "../stage/data/pad1.c"

#include "../stage/data/pad_mirror.c"

#include "../stage/data/pspr_top.c"

#include "../stage/data/work_area_ptr.c"

#include "../stage/data/point_search_above.c"

#include "../stage/data/scale_vec.c"

#include "../stage/data/stage_screen_w.c"

#include "../stage/data/stage_screen_h.c"

#include "../stage/data/point_search_radius.c"

#include "../stage/data/fade_color_r.c"

#include "../stage/data/fade_color_g.c"

#include "../stage/data/fade_color_b.c"

#include "../stage/data/point_base.c"

#include "../stage/data/packet_free_list.c"

s32 shot_params_b = 0;

s32 enemy_area_limit = 0;

u32 D_8011FFF8 = 0x00000000;

u16 D_8011FFFC = 0;

u16 D_8011FFFE = 0x0000;

/* labels inside the objects above */
__asm__(".globl D_8011819A\n.set D_8011819A, D_80118198+0x2\n"
        ".globl D_801181BA\n.set D_801181BA, D_801181B8+0x2\n"
        ".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl D_8011E5D2\n.set D_8011E5D2, texture_image+0x2\n"
        ".globl pad1_pressed\n.set pad1_pressed, pad1+0x2\n"
        ".globl D_8011FFD6\n.set D_8011FFD6, scale_vec+0x2\n"
        ".globl enemy_hit_script\n.set enemy_hit_script, bazooka_script_table_streams+0x288\n"
        ".globl walker_death_scripts_alt\n.set walker_death_scripts_alt, walker_anims+0x80\n"
        ".globl clamp_box_min_y\n.set clamp_box_min_y, clamp_box_table+0x4\n"
        ".globl clamp_box_min_z\n.set clamp_box_min_z, clamp_box_table+0x8\n"
        ".globl clamp_box_max_x\n.set clamp_box_max_x, clamp_box_table+0x10\n"
        ".globl clamp_box_max_y\n.set clamp_box_max_y, clamp_box_table+0x14\n"
        ".globl clamp_box_max_z\n.set clamp_box_max_z, clamp_box_table+0x18\n"
        ".globl D_80117C9C\n.set D_80117C9C, camouflaged_target_m5_boss_attack_a_repeat+0xC\n"
        ".globl D_80117CB4\n.set D_80117CB4, camouflaged_target_m5_boss_attack_b_repeat+0xC\n"
        ".globl D_80117CC8\n.set D_80117CC8, camouflaged_target_m5_boss_attack_c_repeat+0xC\n"
        ".globl D_80117CE0\n.set D_80117CE0, camouflaged_target_m5_boss_attack_d_repeat+0xC\n"
        ".globl D_80117CFC\n.set D_80117CFC, camouflaged_target_m5_boss_attack_e_repeat+0xC\n"
        ".globl D_80117D14\n.set D_80117D14, camouflaged_target_m5_boss_pick_flight_repeat+0xC\n"
        ".globl D_80117EE4\n.set D_80117EE4, m5_boss_states+0xC\n"
        ".globl D_80117EF4\n.set D_80117EF4, m5_boss_states+0x1C\n"
        ".globl D_80117EFC\n.set D_80117EFC, m5_boss_states+0x24\n"
        ".globl D_80117F04\n.set D_80117F04, m5_boss_states+0x2C\n"
        ".globl D_80117F3C\n.set D_80117F3C, m5_boss_states+0x64\n"
        ".globl shot_homing_param\n.set shot_homing_param, m5_boss_states+0x74\n"
        ".globl D_80117F8C\n.set D_80117F8C, m5_boss_states+0xB4\n"
        ".globl chase_player_param\n.set chase_player_param, m5_boss_states+0xC4\n"
        ".globl D_80117FAC\n.set D_80117FAC, m5_boss_states+0xD4\n"
        ".globl D_80117FB4\n.set D_80117FB4, m5_boss_states+0xDC\n"
        ".globl sincos_deg90\n.set sincos_deg90, rcossin_tbl+0x1000\n"
        ".globl view_sincos\n.set view_sincos, rcossin_tbl+0x2000\n"
        ".globl sincos_deg270\n.set sincos_deg270, rcossin_tbl+0x3000\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n"
        ".globl D_8011FC8E\n.set D_8011FC8E, view_nudge+0x2\n"
        ".globl d_801201AE\n.set d_801201AE, flow+0x2\n"
        ".globl flow_angle\n.set flow_angle, flow+0x4\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl bazooka_soldier_anim_idle\n.set bazooka_soldier_anim_idle, bazooka_script_table_streams+0x0\n"
        ".globl enemy_anim_fidget\n.set enemy_anim_fidget, bazooka_script_table_streams+0xC\n"
        ".globl bazooka_soldier_anim_walk_start\n.set bazooka_soldier_anim_walk_start, bazooka_script_table_streams+0x30\n"
        ".globl enemy_anim_walk\n.set enemy_anim_walk, bazooka_script_table_streams+0x50\n"
        ".globl bazooka_soldier_anim_run_start\n.set bazooka_soldier_anim_run_start, bazooka_script_table_streams+0x7C\n"
        ".globl bazooka_soldier_anim_run\n.set bazooka_soldier_anim_run, bazooka_script_table_streams+0xAC\n"
        ".globl bazooka_soldier_anim_fire\n.set bazooka_soldier_anim_fire, bazooka_script_table_streams+0xD4\n"
        ".globl bazooka_soldier_anim_fire_shot\n.set bazooka_soldier_anim_fire_shot, bazooka_script_table_streams+0xFC\n"
        ".globl bazooka_soldier_anim_fire_alt\n.set bazooka_soldier_anim_fire_alt, bazooka_script_table_streams+0x128\n"
        ".globl bazooka_soldier_anim_hold\n.set bazooka_soldier_anim_hold, bazooka_script_table_streams+0x16C\n"
        ".globl bazooka_soldier_anim_aim_hold\n.set bazooka_soldier_anim_aim_hold, bazooka_script_table_streams+0x174\n"
        ".globl bazooka_soldier_anim_pose_hold\n.set bazooka_soldier_anim_pose_hold, bazooka_script_table_streams+0x17C\n"
        ".globl bazooka_soldier_anim_sweep\n.set bazooka_soldier_anim_sweep, bazooka_script_table_streams+0x184\n"
        ".globl enemy_anim_fall\n.set enemy_anim_fall, bazooka_script_table_streams+0x1AC\n"
        ".globl enemy_anim_dead\n.set enemy_anim_dead, bazooka_script_table_streams+0x1CC\n"
        ".globl bazooka_soldier_anim_fly_start\n.set bazooka_soldier_anim_fly_start, bazooka_script_table_streams+0x1FC\n"
        ".globl bazooka_soldier_anim_fly_loop\n.set bazooka_soldier_anim_fly_loop, bazooka_script_table_streams+0x22C\n"
        ".globl bazooka_script_table\n.set bazooka_script_table, bazooka_script_table_streams+0x254\n"
        ".globl smg_soldier_idle\n.set smg_soldier_idle, enemy_script_jumps_streams+0x0\n"
        ".globl smg_soldier_idle_pause\n.set smg_soldier_idle_pause, enemy_script_jumps_streams+0xC\n"
        ".globl smg_soldier_idle_cycle\n.set smg_soldier_idle_cycle, enemy_script_jumps_streams+0x14\n"
        ".globl smg_soldier_patrol\n.set smg_soldier_patrol, enemy_script_jumps_streams+0x28\n"
        ".globl smg_soldier_patrol_cycle\n.set smg_soldier_patrol_cycle, enemy_script_jumps_streams+0x34\n"
        ".globl smg_soldier_patrol_wait\n.set smg_soldier_patrol_wait, enemy_script_jumps_streams+0x4C\n"
        ".globl smg_soldier_hold\n.set smg_soldier_hold, enemy_script_jumps_streams+0x58\n"
        ".globl smg_soldier_hold_pause\n.set smg_soldier_hold_pause, enemy_script_jumps_streams+0x60\n"
        ".globl smg_soldier_hold_cycle\n.set smg_soldier_hold_cycle, enemy_script_jumps_streams+0x68\n"
        ".globl smg_soldier_walk\n.set smg_soldier_walk, enemy_script_jumps_streams+0x7C\n"
        ".globl smg_soldier_walk_step\n.set smg_soldier_walk_step, enemy_script_jumps_streams+0x84\n"
        ".globl smg_soldier_walk_cycle\n.set smg_soldier_walk_cycle, enemy_script_jumps_streams+0x8C\n"
        ".globl smg_soldier_walk_pause\n.set smg_soldier_walk_pause, enemy_script_jumps_streams+0xA0\n"
        ".globl smg_soldier_walk_pause_cycle\n.set smg_soldier_walk_pause_cycle, enemy_script_jumps_streams+0xA8\n"
        ".globl enemy_fire\n.set enemy_fire, enemy_script_jumps_streams+0xBC\n"
        ".globl bazooka_soldier_track_wait\n.set bazooka_soldier_track_wait, enemy_script_jumps_streams+0xC0\n"
        ".globl enemy_script_jumps\n.set enemy_script_jumps, enemy_script_jumps_streams+0xD0\n"
        ".globl enemy_mode_scripts\n.set enemy_mode_scripts, enemy_script_jumps_streams+0x110\n"
        ".globl walker_mech_anim_idle\n.set walker_mech_anim_idle, walker_anims+0x0\n"
        ".globl walker_mech_anim_walk\n.set walker_mech_anim_walk, walker_anims+0x8\n"
        ".globl walker_mech_anim_fire\n.set walker_mech_anim_fire, walker_anims+0x34\n"
        ".globl walker_death_script\n.set walker_death_script, walker_anims+0x48\n"
        ".globl walker_mech_data\n.set walker_mech_data, walker_anims+0x74\n"
        ".globl walker_mech_begin\n.set walker_mech_begin, walker_type_data_alt_streams+0x0\n"
        ".globl walker_mech_patrol_start\n.set walker_mech_patrol_start, walker_type_data_alt_streams+0x4\n"
        ".globl walker_mech_watch\n.set walker_mech_watch, walker_type_data_alt_streams+0xC\n"
        ".globl walker_mech_engage_wait\n.set walker_mech_engage_wait, walker_type_data_alt_streams+0x1C\n"
        ".globl walker_mech_engage\n.set walker_mech_engage, walker_type_data_alt_streams+0x28\n"
        ".globl triple_barrel_robot_fire_end\n.set triple_barrel_robot_fire_end, walker_type_data_alt_streams+0x2C\n"
        ".globl triple_barrel_robot_cooldown\n.set triple_barrel_robot_cooldown, walker_type_data_alt_streams+0x3C\n"
        ".globl walker_type_data_alt\n.set walker_type_data_alt, walker_type_data_alt_streams+0x4C\n"
        ".globl d_80116578\n.set d_80116578, walker_type_data_alt_streams+0x68\n"
        ".globl grenade_fuchikoma_anim_idle\n.set grenade_fuchikoma_anim_idle, grenade_fuchikoma_anims+0x0\n"
        ".globl grenade_fuchikoma_anim_spin\n.set grenade_fuchikoma_anim_spin, grenade_fuchikoma_anims+0x8\n"
        ".globl grenade_fuchikoma_anim_hold_start\n.set grenade_fuchikoma_anim_hold_start, grenade_fuchikoma_anims+0x34\n"
        ".globl grenade_fuchikoma_anim_hold\n.set grenade_fuchikoma_anim_hold, grenade_fuchikoma_anims+0x38\n"
        ".globl grenade_fuchikoma_data\n.set grenade_fuchikoma_data, grenade_fuchikoma_anims+0x40\n"
        ".globl grenade_fuchikoma_dormant\n.set grenade_fuchikoma_dormant, grenade_type_data_streams+0x0\n"
        ".globl grenade_fuchikoma_release\n.set grenade_fuchikoma_release, grenade_type_data_streams+0xC\n"
        ".globl grenade_fuchikoma_release_wait\n.set grenade_fuchikoma_release_wait, grenade_type_data_streams+0x1C\n"
        ".globl rocket_fuchikoma_ready\n.set rocket_fuchikoma_ready, grenade_type_data_streams+0x30\n"
        ".globl rocket_fuchikoma_aim_start\n.set rocket_fuchikoma_aim_start, grenade_type_data_streams+0x3C\n"
        ".globl grenade_fuchikoma_seek\n.set grenade_fuchikoma_seek, grenade_type_data_streams+0x48\n"
        ".globl grenade_fuchikoma_set_params\n.set grenade_fuchikoma_set_params, grenade_type_data_streams+0x5C\n"
        ".globl grenade_fuchikoma_track\n.set grenade_fuchikoma_track, grenade_type_data_streams+0x68\n"
        ".globl rocket_fuchikoma_close_in\n.set rocket_fuchikoma_close_in, grenade_type_data_streams+0x88\n"
        ".globl rocket_fuchikoma_brake\n.set rocket_fuchikoma_brake, grenade_type_data_streams+0x98\n"
        ".globl grenade_fuchikoma_wait_stop\n.set grenade_fuchikoma_wait_stop, grenade_type_data_streams+0xA0\n"
        ".globl rocket_fuchikoma_fire_wait\n.set rocket_fuchikoma_fire_wait, grenade_type_data_streams+0xB0\n"
        ".globl rocket_fuchikoma_fire_start\n.set rocket_fuchikoma_fire_start, grenade_type_data_streams+0xBC\n"
        ".globl grenade_fuchikoma_detonate_wait\n.set grenade_fuchikoma_detonate_wait, grenade_type_data_streams+0xC0\n"
        ".globl rocket_fuchikoma_reposition\n.set rocket_fuchikoma_reposition, grenade_type_data_streams+0xD0\n"
        ".globl grenade_fuchikoma_recover_face\n.set grenade_fuchikoma_recover_face, grenade_type_data_streams+0xE0\n"
        ".globl grenade_type_data\n.set grenade_type_data, grenade_type_data_streams+0xF4\n"
        ".globl grenade_script_pc\n.set grenade_script_pc, grenade_type_data_streams+0x134\n"
        ".globl gun_turret_anim_idle\n.set gun_turret_anim_idle, gun_turret_anims+0x0\n"
        ".globl gun_turret_data\n.set gun_turret_data, gun_turret_anims+0x8\n"
        ".globl gun_turret_idle\n.set gun_turret_idle, gun_turret_scripts+0x0\n"
        ".globl gun_turret_spotted\n.set gun_turret_spotted, gun_turret_scripts+0x10\n"
        ".globl gun_turret_aim\n.set gun_turret_aim, gun_turret_scripts+0x14\n"
        ".globl gun_turret_fire_check\n.set gun_turret_fire_check, gun_turret_scripts+0x24\n"
        ".globl gun_turret_fire_start\n.set gun_turret_fire_start, gun_turret_scripts+0x30\n"
        ".globl gun_turret_cooldown\n.set gun_turret_cooldown, gun_turret_scripts+0x34\n"
        ".globl gun_turret_link_data\n.set gun_turret_link_data, gun_turret_scripts+0x44\n"
        ".globl gun_turret_script_pos\n.set gun_turret_script_pos, gun_turret_scripts+0x5C\n"
        ".globl fighter_jet_script\n.set fighter_jet_script, fighter_jet_anims+0x0\n"
        ".globl fighter_jet_data\n.set fighter_jet_data, fighter_jet_anims+0x8\n"
        ".globl fighter_jet_idle\n.set fighter_jet_idle, fighter_jet_scripts+0x0\n"
        ".globl fighter_jet_dispatch\n.set fighter_jet_dispatch, fighter_jet_scripts+0x4\n"
        ".globl fighter_jet_patrol\n.set fighter_jet_patrol, fighter_jet_scripts+0x14\n"
        ".globl fighter_jet_sweep_end\n.set fighter_jet_sweep_end, fighter_jet_scripts+0x24\n"
        ".globl fighter_jet_spotted\n.set fighter_jet_spotted, fighter_jet_scripts+0x34\n"
        ".globl fighter_jet_cooldown\n.set fighter_jet_cooldown, fighter_jet_scripts+0x44\n"
        ".globl fighter_jet_cooling\n.set fighter_jet_cooling, fighter_jet_scripts+0x4C\n"
        ".globl fighter_jet_resume\n.set fighter_jet_resume, fighter_jet_scripts+0x58\n"
        ".globl fighter_jet_type_data\n.set fighter_jet_type_data, fighter_jet_scripts+0x60\n"
        ".globl fighter_jet_script_start\n.set fighter_jet_script_start, fighter_jet_scripts+0x80\n"
        ".globl camouflaged_target_m5_boss_anim_idle\n.set camouflaged_target_m5_boss_anim_idle, camouflaged_target_m5_boss_anims+0x0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_from_idle_01\n.set camouflaged_target_m5_boss_anim_transition_from_idle_01, camouflaged_target_m5_boss_anims+0x2C\n"
        ".globl camouflaged_target_m5_boss_anim_transition_from_idle_02\n.set camouflaged_target_m5_boss_anim_transition_from_idle_02, camouflaged_target_m5_boss_anims+0x30\n"
        ".globl camouflaged_target_m5_boss_anim_transition_from_idle_03\n.set camouflaged_target_m5_boss_anim_transition_from_idle_03, camouflaged_target_m5_boss_anims+0x34\n"
        ".globl camouflaged_target_m5_boss_anim_transition_from_idle_04\n.set camouflaged_target_m5_boss_anim_transition_from_idle_04, camouflaged_target_m5_boss_anims+0x38\n"
        ".globl camouflaged_target_m5_boss_anim_transition_from_idle_05\n.set camouflaged_target_m5_boss_anim_transition_from_idle_05, camouflaged_target_m5_boss_anims+0x3C\n"
        ".globl camouflaged_target_m5_boss_anim_transition_from_idle_06\n.set camouflaged_target_m5_boss_anim_transition_from_idle_06, camouflaged_target_m5_boss_anims+0x40\n"
        ".globl camouflaged_target_m5_boss_anim_transition_from_idle_07\n.set camouflaged_target_m5_boss_anim_transition_from_idle_07, camouflaged_target_m5_boss_anims+0x44\n"
        ".globl camouflaged_target_m5_boss_anim_transition_from_idle_08\n.set camouflaged_target_m5_boss_anim_transition_from_idle_08, camouflaged_target_m5_boss_anims+0x48\n"
        ".globl camouflaged_target_m5_boss_anim_transition_from_idle_09\n.set camouflaged_target_m5_boss_anim_transition_from_idle_09, camouflaged_target_m5_boss_anims+0x4C\n"
        ".globl camouflaged_target_m5_boss_anim_transition\n.set camouflaged_target_m5_boss_anim_transition, camouflaged_target_m5_boss_anims+0x50\n"
        ".globl camouflaged_target_m5_boss_anim_run_00\n.set camouflaged_target_m5_boss_anim_run_00, camouflaged_target_m5_boss_anims+0x9C\n"
        ".globl camouflaged_target_m5_boss_anim_run_01\n.set camouflaged_target_m5_boss_anim_run_01, camouflaged_target_m5_boss_anims+0xA0\n"
        ".globl camouflaged_target_m5_boss_anim_run_02\n.set camouflaged_target_m5_boss_anim_run_02, camouflaged_target_m5_boss_anims+0xA4\n"
        ".globl camouflaged_target_m5_boss_anim_run_03\n.set camouflaged_target_m5_boss_anim_run_03, camouflaged_target_m5_boss_anims+0xA8\n"
        ".globl camouflaged_target_m5_boss_anim_run_04\n.set camouflaged_target_m5_boss_anim_run_04, camouflaged_target_m5_boss_anims+0xAC\n"
        ".globl camouflaged_target_m5_boss_anim_run_05\n.set camouflaged_target_m5_boss_anim_run_05, camouflaged_target_m5_boss_anims+0xB0\n"
        ".globl camouflaged_target_m5_boss_anim_run_06\n.set camouflaged_target_m5_boss_anim_run_06, camouflaged_target_m5_boss_anims+0xB4\n"
        ".globl camouflaged_target_m5_boss_anim_run_07\n.set camouflaged_target_m5_boss_anim_run_07, camouflaged_target_m5_boss_anims+0xB8\n"
        ".globl camouflaged_target_m5_boss_anim_run_08\n.set camouflaged_target_m5_boss_anim_run_08, camouflaged_target_m5_boss_anims+0xBC\n"
        ".globl camouflaged_target_m5_boss_anim_run_09\n.set camouflaged_target_m5_boss_anim_run_09, camouflaged_target_m5_boss_anims+0xC0\n"
        ".globl camouflaged_target_m5_boss_anim_run_10\n.set camouflaged_target_m5_boss_anim_run_10, camouflaged_target_m5_boss_anims+0xC4\n"
        ".globl camouflaged_target_m5_boss_anim_run_11\n.set camouflaged_target_m5_boss_anim_run_11, camouflaged_target_m5_boss_anims+0xC8\n"
        ".globl camouflaged_target_m5_boss_anim_run_12\n.set camouflaged_target_m5_boss_anim_run_12, camouflaged_target_m5_boss_anims+0xCC\n"
        ".globl camouflaged_target_m5_boss_anim_run_13\n.set camouflaged_target_m5_boss_anim_run_13, camouflaged_target_m5_boss_anims+0xD0\n"
        ".globl camouflaged_target_m5_boss_anim_run_14\n.set camouflaged_target_m5_boss_anim_run_14, camouflaged_target_m5_boss_anims+0xD4\n"
        ".globl camouflaged_target_m5_boss_anim_run_15\n.set camouflaged_target_m5_boss_anim_run_15, camouflaged_target_m5_boss_anims+0xD8\n"
        ".globl camouflaged_target_m5_boss_anim_run_16\n.set camouflaged_target_m5_boss_anim_run_16, camouflaged_target_m5_boss_anims+0xDC\n"
        ".globl camouflaged_target_m5_boss_anim_run_17\n.set camouflaged_target_m5_boss_anim_run_17, camouflaged_target_m5_boss_anims+0xE0\n"
        ".globl camouflaged_target_m5_boss_anim_run_18\n.set camouflaged_target_m5_boss_anim_run_18, camouflaged_target_m5_boss_anims+0xE4\n"
        ".globl camouflaged_target_m5_boss_anim_run_19\n.set camouflaged_target_m5_boss_anim_run_19, camouflaged_target_m5_boss_anims+0xE8\n"
        ".globl camouflaged_target_m5_boss_anim_run_20\n.set camouflaged_target_m5_boss_anim_run_20, camouflaged_target_m5_boss_anims+0xEC\n"
        ".globl camouflaged_target_m5_boss_anim_run_21\n.set camouflaged_target_m5_boss_anim_run_21, camouflaged_target_m5_boss_anims+0xF0\n"
        ".globl camouflaged_target_m5_boss_anim_run_22\n.set camouflaged_target_m5_boss_anim_run_22, camouflaged_target_m5_boss_anims+0xF4\n"
        ".globl camouflaged_target_m5_boss_anim_run_23\n.set camouflaged_target_m5_boss_anim_run_23, camouflaged_target_m5_boss_anims+0xF8\n"
        ".globl camouflaged_target_m5_boss_anim_run_24\n.set camouflaged_target_m5_boss_anim_run_24, camouflaged_target_m5_boss_anims+0xFC\n"
        ".globl camouflaged_target_m5_boss_anim_run_25\n.set camouflaged_target_m5_boss_anim_run_25, camouflaged_target_m5_boss_anims+0x100\n"
        ".globl camouflaged_target_m5_boss_anim_run_26\n.set camouflaged_target_m5_boss_anim_run_26, camouflaged_target_m5_boss_anims+0x104\n"
        ".globl camouflaged_target_m5_boss_anim_run_27\n.set camouflaged_target_m5_boss_anim_run_27, camouflaged_target_m5_boss_anims+0x108\n"
        ".globl camouflaged_target_m5_boss_anim_run_28\n.set camouflaged_target_m5_boss_anim_run_28, camouflaged_target_m5_boss_anims+0x10C\n"
        ".globl camouflaged_target_m5_boss_anim_run_29\n.set camouflaged_target_m5_boss_anim_run_29, camouflaged_target_m5_boss_anims+0x110\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_01\n.set camouflaged_target_m5_boss_anim_settle_from_run_01, camouflaged_target_m5_boss_anims+0x118\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_02\n.set camouflaged_target_m5_boss_anim_settle_from_run_02, camouflaged_target_m5_boss_anims+0x11C\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_03\n.set camouflaged_target_m5_boss_anim_settle_from_run_03, camouflaged_target_m5_boss_anims+0x120\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_04\n.set camouflaged_target_m5_boss_anim_settle_from_run_04, camouflaged_target_m5_boss_anims+0x124\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_05\n.set camouflaged_target_m5_boss_anim_settle_from_run_05, camouflaged_target_m5_boss_anims+0x128\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_06\n.set camouflaged_target_m5_boss_anim_settle_from_run_06, camouflaged_target_m5_boss_anims+0x12C\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_07\n.set camouflaged_target_m5_boss_anim_settle_from_run_07, camouflaged_target_m5_boss_anims+0x130\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_08\n.set camouflaged_target_m5_boss_anim_settle_from_run_08, camouflaged_target_m5_boss_anims+0x134\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_09\n.set camouflaged_target_m5_boss_anim_settle_from_run_09, camouflaged_target_m5_boss_anims+0x138\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_10\n.set camouflaged_target_m5_boss_anim_settle_from_run_10, camouflaged_target_m5_boss_anims+0x13C\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_11\n.set camouflaged_target_m5_boss_anim_settle_from_run_11, camouflaged_target_m5_boss_anims+0x140\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_12\n.set camouflaged_target_m5_boss_anim_settle_from_run_12, camouflaged_target_m5_boss_anims+0x144\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_13\n.set camouflaged_target_m5_boss_anim_settle_from_run_13, camouflaged_target_m5_boss_anims+0x148\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_14\n.set camouflaged_target_m5_boss_anim_settle_from_run_14, camouflaged_target_m5_boss_anims+0x14C\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_15\n.set camouflaged_target_m5_boss_anim_settle_from_run_15, camouflaged_target_m5_boss_anims+0x150\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_16\n.set camouflaged_target_m5_boss_anim_settle_from_run_16, camouflaged_target_m5_boss_anims+0x154\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_17\n.set camouflaged_target_m5_boss_anim_settle_from_run_17, camouflaged_target_m5_boss_anims+0x158\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_18\n.set camouflaged_target_m5_boss_anim_settle_from_run_18, camouflaged_target_m5_boss_anims+0x15C\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_19\n.set camouflaged_target_m5_boss_anim_settle_from_run_19, camouflaged_target_m5_boss_anims+0x160\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_20\n.set camouflaged_target_m5_boss_anim_settle_from_run_20, camouflaged_target_m5_boss_anims+0x164\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_21\n.set camouflaged_target_m5_boss_anim_settle_from_run_21, camouflaged_target_m5_boss_anims+0x168\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_22\n.set camouflaged_target_m5_boss_anim_settle_from_run_22, camouflaged_target_m5_boss_anims+0x16C\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_23\n.set camouflaged_target_m5_boss_anim_settle_from_run_23, camouflaged_target_m5_boss_anims+0x170\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_24\n.set camouflaged_target_m5_boss_anim_settle_from_run_24, camouflaged_target_m5_boss_anims+0x174\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_25\n.set camouflaged_target_m5_boss_anim_settle_from_run_25, camouflaged_target_m5_boss_anims+0x178\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_26\n.set camouflaged_target_m5_boss_anim_settle_from_run_26, camouflaged_target_m5_boss_anims+0x17C\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_27\n.set camouflaged_target_m5_boss_anim_settle_from_run_27, camouflaged_target_m5_boss_anims+0x180\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_28\n.set camouflaged_target_m5_boss_anim_settle_from_run_28, camouflaged_target_m5_boss_anims+0x184\n"
        ".globl camouflaged_target_m5_boss_anim_settle_from_run_29\n.set camouflaged_target_m5_boss_anim_settle_from_run_29, camouflaged_target_m5_boss_anims+0x188\n"
        ".globl camouflaged_target_m5_boss_anim_settle\n.set camouflaged_target_m5_boss_anim_settle, camouflaged_target_m5_boss_anims+0x18C\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_17\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_17, camouflaged_target_m5_boss_anims+0x1CC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_18\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_18, camouflaged_target_m5_boss_anims+0x1D0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_19\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_19, camouflaged_target_m5_boss_anims+0x1D4\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_20\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_20, camouflaged_target_m5_boss_anims+0x1D8\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_21\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_21, camouflaged_target_m5_boss_anims+0x1DC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_22\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_22, camouflaged_target_m5_boss_anims+0x1E0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_23\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_23, camouflaged_target_m5_boss_anims+0x1E4\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_24\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_24, camouflaged_target_m5_boss_anims+0x1E8\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_25\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_25, camouflaged_target_m5_boss_anims+0x1EC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_26\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_26, camouflaged_target_m5_boss_anims+0x1F0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_27\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_27, camouflaged_target_m5_boss_anims+0x1F4\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_28\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_28, camouflaged_target_m5_boss_anims+0x1F8\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_29\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_29, camouflaged_target_m5_boss_anims+0x1FC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_00\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_00, camouflaged_target_m5_boss_anims+0x200\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_01\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_01, camouflaged_target_m5_boss_anims+0x204\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_02\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_02, camouflaged_target_m5_boss_anims+0x208\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_03\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_03, camouflaged_target_m5_boss_anims+0x20C\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_04\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_04, camouflaged_target_m5_boss_anims+0x210\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_05\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_05, camouflaged_target_m5_boss_anims+0x214\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_06\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_06, camouflaged_target_m5_boss_anims+0x218\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_07\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_07, camouflaged_target_m5_boss_anims+0x21C\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_08\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_08, camouflaged_target_m5_boss_anims+0x220\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_09\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_09, camouflaged_target_m5_boss_anims+0x224\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_10\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_10, camouflaged_target_m5_boss_anims+0x228\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_11\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_11, camouflaged_target_m5_boss_anims+0x22C\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_12\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_12, camouflaged_target_m5_boss_anims+0x230\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_13\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_13, camouflaged_target_m5_boss_anims+0x234\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_14\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_14, camouflaged_target_m5_boss_anims+0x238\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt_from_run_15\n.set camouflaged_target_m5_boss_anim_transition_alt_from_run_15, camouflaged_target_m5_boss_anims+0x23C\n"
        ".globl camouflaged_target_m5_boss_anim_transition_alt\n.set camouflaged_target_m5_boss_anim_transition_alt, camouflaged_target_m5_boss_anims+0x240\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_01\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_01, camouflaged_target_m5_boss_anims+0x294\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_02\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_02, camouflaged_target_m5_boss_anims+0x298\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_03\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_03, camouflaged_target_m5_boss_anims+0x29C\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_04\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_04, camouflaged_target_m5_boss_anims+0x2A0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_05\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_05, camouflaged_target_m5_boss_anims+0x2A4\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_06\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_06, camouflaged_target_m5_boss_anims+0x2A8\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_07\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_07, camouflaged_target_m5_boss_anims+0x2AC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_08\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_08, camouflaged_target_m5_boss_anims+0x2B0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_09\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_09, camouflaged_target_m5_boss_anims+0x2B4\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_10\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_10, camouflaged_target_m5_boss_anims+0x2B8\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_11\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_11, camouflaged_target_m5_boss_anims+0x2BC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_12\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_12, camouflaged_target_m5_boss_anims+0x2C0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_13\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_13, camouflaged_target_m5_boss_anims+0x2C4\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_14\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_14, camouflaged_target_m5_boss_anims+0x2C8\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_15\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_15, camouflaged_target_m5_boss_anims+0x2CC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_16\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_16, camouflaged_target_m5_boss_anims+0x2D0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_17\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_17, camouflaged_target_m5_boss_anims+0x2D4\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_18\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_18, camouflaged_target_m5_boss_anims+0x2D8\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_19\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_19, camouflaged_target_m5_boss_anims+0x2DC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_20\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_20, camouflaged_target_m5_boss_anims+0x2E0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_21\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_21, camouflaged_target_m5_boss_anims+0x2E4\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_22\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_22, camouflaged_target_m5_boss_anims+0x2E8\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_23\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_23, camouflaged_target_m5_boss_anims+0x2EC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_24\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_24, camouflaged_target_m5_boss_anims+0x2F0\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_25\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_25, camouflaged_target_m5_boss_anims+0x2F4\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_26\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_26, camouflaged_target_m5_boss_anims+0x2F8\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_27\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_27, camouflaged_target_m5_boss_anims+0x2FC\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_28\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_28, camouflaged_target_m5_boss_anims+0x300\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two_from_run_29\n.set camouflaged_target_m5_boss_anim_transition_two_from_run_29, camouflaged_target_m5_boss_anims+0x304\n"
        ".globl camouflaged_target_m5_boss_anim_transition_two\n.set camouflaged_target_m5_boss_anim_transition_two, camouflaged_target_m5_boss_anims+0x308\n"
        ".globl camouflaged_target_m5_boss_anim_hold_lead\n.set camouflaged_target_m5_boss_anim_hold_lead, camouflaged_target_m5_boss_anims+0x35C\n"
        ".globl camouflaged_target_m5_boss_anim_hold\n.set camouflaged_target_m5_boss_anim_hold, camouflaged_target_m5_boss_anims+0x394\n"
        ".globl camouflaged_target_m5_boss_anim_release\n.set camouflaged_target_m5_boss_anim_release, camouflaged_target_m5_boss_anims+0x39C\n"
        ".globl camouflaged_target_m5_boss_anim_release_alt\n.set camouflaged_target_m5_boss_anim_release_alt, camouflaged_target_m5_boss_anims+0x3C4\n"
        ".globl camouflaged_target_m5_boss_anim_release_long\n.set camouflaged_target_m5_boss_anim_release_long, camouflaged_target_m5_boss_anims+0x400\n"
        ".globl camouflaged_target_m5_boss_anim_fire_shot\n.set camouflaged_target_m5_boss_anim_fire_shot, camouflaged_target_m5_boss_anims+0x46C\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_16\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_16, camouflaged_target_m5_boss_anims+0x4A0\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_17\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_17, camouflaged_target_m5_boss_anims+0x4A4\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_18\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_18, camouflaged_target_m5_boss_anims+0x4A8\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_19\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_19, camouflaged_target_m5_boss_anims+0x4AC\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_20\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_20, camouflaged_target_m5_boss_anims+0x4B0\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_21\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_21, camouflaged_target_m5_boss_anims+0x4B4\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_22\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_22, camouflaged_target_m5_boss_anims+0x4B8\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_23\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_23, camouflaged_target_m5_boss_anims+0x4BC\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_24\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_24, camouflaged_target_m5_boss_anims+0x4C0\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_25\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_25, camouflaged_target_m5_boss_anims+0x4C4\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_26\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_26, camouflaged_target_m5_boss_anims+0x4C8\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_27\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_27, camouflaged_target_m5_boss_anims+0x4CC\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_28\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_28, camouflaged_target_m5_boss_anims+0x4D0\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_29\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_29, camouflaged_target_m5_boss_anims+0x4D4\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_00\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_00, camouflaged_target_m5_boss_anims+0x4D8\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_01\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_01, camouflaged_target_m5_boss_anims+0x4DC\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_02\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_02, camouflaged_target_m5_boss_anims+0x4E0\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_03\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_03, camouflaged_target_m5_boss_anims+0x4E4\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_04\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_04, camouflaged_target_m5_boss_anims+0x4E8\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_05\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_05, camouflaged_target_m5_boss_anims+0x4EC\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_06\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_06, camouflaged_target_m5_boss_anims+0x4F0\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_07\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_07, camouflaged_target_m5_boss_anims+0x4F4\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_08\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_08, camouflaged_target_m5_boss_anims+0x4F8\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_09\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_09, camouflaged_target_m5_boss_anims+0x4FC\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_10\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_10, camouflaged_target_m5_boss_anims+0x500\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_11\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_11, camouflaged_target_m5_boss_anims+0x504\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_12\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_12, camouflaged_target_m5_boss_anims+0x508\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_13\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_13, camouflaged_target_m5_boss_anims+0x50C\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start_from_run_14\n.set camouflaged_target_m5_boss_anim_hold_start_from_run_14, camouflaged_target_m5_boss_anims+0x510\n"
        ".globl camouflaged_target_m5_boss_anim_hold_start\n.set camouflaged_target_m5_boss_anim_hold_start, camouflaged_target_m5_boss_anims+0x514\n"
        ".globl camouflaged_target_m5_boss_anim_hold_alt\n.set camouflaged_target_m5_boss_anim_hold_alt, camouflaged_target_m5_boss_anims+0x520\n"
        ".globl camouflaged_target_m5_boss_anim_hold_mid\n.set camouflaged_target_m5_boss_anim_hold_mid, camouflaged_target_m5_boss_anims+0x528\n"
        ".globl camouflaged_target_m5_boss_anim_hold_two\n.set camouflaged_target_m5_boss_anim_hold_two, camouflaged_target_m5_boss_anims+0x534\n"
        ".globl camouflaged_target_m5_boss_anim_impact_lead\n.set camouflaged_target_m5_boss_anim_impact_lead, camouflaged_target_m5_boss_anims+0x53C\n"
        ".globl camouflaged_target_m5_boss_anim_impact_hold\n.set camouflaged_target_m5_boss_anim_impact_hold, camouflaged_target_m5_boss_anims+0x560\n"
        ".globl camouflaged_target_m5_boss_anim_recover\n.set camouflaged_target_m5_boss_anim_recover, camouflaged_target_m5_boss_anims+0x568\n"
        ".globl camouflaged_target_m5_boss_anim_recover_alt\n.set camouflaged_target_m5_boss_anim_recover_alt, camouflaged_target_m5_boss_anims+0x5B0\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_01\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_01, camouflaged_target_m5_boss_anims+0x604\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_02\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_02, camouflaged_target_m5_boss_anims+0x608\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_03\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_03, camouflaged_target_m5_boss_anims+0x60C\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_04\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_04, camouflaged_target_m5_boss_anims+0x610\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_05\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_05, camouflaged_target_m5_boss_anims+0x614\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_06\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_06, camouflaged_target_m5_boss_anims+0x618\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_07\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_07, camouflaged_target_m5_boss_anims+0x61C\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_08\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_08, camouflaged_target_m5_boss_anims+0x620\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_09\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_09, camouflaged_target_m5_boss_anims+0x624\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_10\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_10, camouflaged_target_m5_boss_anims+0x628\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_11\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_11, camouflaged_target_m5_boss_anims+0x62C\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_12\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_12, camouflaged_target_m5_boss_anims+0x630\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_13\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_13, camouflaged_target_m5_boss_anims+0x634\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_14\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_14, camouflaged_target_m5_boss_anims+0x638\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_15\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_15, camouflaged_target_m5_boss_anims+0x63C\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_16\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_16, camouflaged_target_m5_boss_anims+0x640\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_17\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_17, camouflaged_target_m5_boss_anims+0x644\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_18\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_18, camouflaged_target_m5_boss_anims+0x648\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_19\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_19, camouflaged_target_m5_boss_anims+0x64C\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_20\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_20, camouflaged_target_m5_boss_anims+0x650\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_21\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_21, camouflaged_target_m5_boss_anims+0x654\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_22\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_22, camouflaged_target_m5_boss_anims+0x658\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_23\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_23, camouflaged_target_m5_boss_anims+0x65C\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_24\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_24, camouflaged_target_m5_boss_anims+0x660\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_25\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_25, camouflaged_target_m5_boss_anims+0x664\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_26\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_26, camouflaged_target_m5_boss_anims+0x668\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_27\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_27, camouflaged_target_m5_boss_anims+0x66C\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_28\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_28, camouflaged_target_m5_boss_anims+0x670\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_29\n.set camouflaged_target_m5_boss_anim_hold_enter_alt_from_run_29, camouflaged_target_m5_boss_anims+0x674\n"
        ".globl camouflaged_target_m5_boss_anim_hold_enter_alt\n.set camouflaged_target_m5_boss_anim_hold_enter_alt, camouflaged_target_m5_boss_anims+0x678\n"
        ".globl camouflaged_target_m5_boss_anim_settle_hold\n.set camouflaged_target_m5_boss_anim_settle_hold, camouflaged_target_m5_boss_anims+0x6B4\n"
        ".globl camouflaged_target_m5_boss_anim_return_idle\n.set camouflaged_target_m5_boss_anim_return_idle, camouflaged_target_m5_boss_anims+0x6BC\n"
        ".globl camouflaged_target_m5_boss_data\n.set camouflaged_target_m5_boss_data, camouflaged_target_m5_boss_anims+0x760\n"
        ".globl spark_script_a\n.set spark_script_a, spark_script_ptr_streams+0x0\n"
        ".globl rocket_boat_spark_anim_idle\n.set rocket_boat_spark_anim_idle, spark_script_ptr_streams+0x8\n"
        ".globl spark_script_ptr\n.set spark_script_ptr, spark_script_ptr_streams+0x10\n");
