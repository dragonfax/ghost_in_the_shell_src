/* s10 data 0x8011AE18-0x80125000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s10_types.h"
#include "script.h"
#include "scripts.h"
#include "sounds.h"

extern void arrival_warning_start();
extern void beam_enemy_attack_update();
extern void cam_track_b_setup();
extern void cam_track_get();
extern void cam_track_init();
extern void cam_track_set_active();
extern void cam_track_set_on();
extern void cam_track_setup();
extern void cam_track_slot_get();
extern void cmd_branch_if_selector();
extern void cmd_read_u16();
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
extern void door_draw();
extern void door_phase0();
extern void door_table_init();
extern void door_update();
extern void elevator_doors_spawn();
extern void enemy_create();
extern void enemy_move_or_wait();
extern void enemy_shoot_update();
extern void enemy_wait_switch();
extern void enemy_walk_step();
extern u8 file_ball_ch0_cb4[];
extern u8 file_ball_ch0_clt[];
extern u8 file_ball_ch0_vx1[];
extern u8 file_ball_tp0_clt[];
extern u8 file_ball_tp0_xs3[];
extern u8 file_bosa_ch0_cb4[];
extern u8 file_bosa_ch0_clt[];
extern u8 file_bosa_ch0_vx1[];
extern u8 file_bosa_ch1_cb4[];
extern u8 file_bosa_ch1_vx1[];
extern u8 file_bosa_ch2_cb4[];
extern u8 file_bosa_ch2_vx1[];
extern u8 file_bosa_ch3_cb4[];
extern u8 file_bosa_ch3_vx1[];
extern u8 file_bosa_tp0_xs3[];
extern u8 file_bosa_tp1_clt[];
extern u8 file_bosa_tp1_xs3[];
extern u8 file_dora_ch0_cb4[];
extern u8 file_hou2_ch0_cb4[];
extern u8 file_hou2_ch0_clt[];
extern u8 file_hou2_ch0_vx1[];
extern u8 file_hou2_tp0_clt[];
extern u8 file_hou2_tp0_xs3[];
extern u8 file_mfir_ch0_cb4[];
extern u8 file_mfir_ch0_clt[];
extern u8 file_mfir_ch0_vx1[];
extern u8 file_mfir_tp0_clt[];
extern u8 file_mfir_tp0_xs3[];
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
extern u8 file_tetr_ch0_cb4[];
extern u8 file_tetr_ch0_clt[];
extern u8 file_tetr_ch0_vx1[];
extern u8 file_tetr_tp0_clt[];
extern u8 file_tetr_tp0_xs3[];
extern u8 file_troi_ch0_cb4[];
extern u8 file_troi_ch0_clt[];
extern u8 file_troi_ch0_vx1[];
extern u8 file_troi_tp0_clt[];
extern u8 file_troi_tp0_xs3[];
extern void flyer_retreat();
extern void flyer_wander();
extern void fn_800B7514();
extern void fn_800B789C();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void func_800C11D8();
extern void func_800C2D5C();
extern void func_800C903C();
extern void func_800C929C();
extern void func_800C92D0();
extern void gun_turret_2_spawn();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void laser_fire();
extern void loop_sound_fade_in();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void muzzle_debris_spawn();
extern void muzzle_effect_spawn();
extern void obj_aim_at_player_mode();
extern void obj_aim_jittered();
extern void obj_area_update();
extern void obj_call_hook();
extern void obj_cmd_read_u16();
extern void obj_countdown_step();
extern void obj_expire_burst();
extern void obj_face_player();
extern void obj_fade_level();
extern void obj_flag_clear();
extern void obj_flag_set();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_patrol_update();
extern void obj_read_s32();
extern void obj_release_check();
extern void obj_script_branch();
extern void obj_script_branch_if_far();
extern void obj_script_branch_if_near();
extern void obj_script_jump_if_key();
extern void obj_script_jump_within();
extern void obj_script_read_arg();
extern void obj_script_read_next_state();
extern void obj_script_read_u16_var();
extern void obj_script_read_value();
extern void obj_script_set_speed();
extern void obj_settle_offset();
extern void obj_sound_volume_update();
extern void obj_spark_triple();
extern void obj_spawn_placement();
extern void obj_state_dispatch();
extern void obj_turn_to_target();
extern void obj_zigzag_move();
extern void params_reset();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void pyramid_mine_spawn();
extern void ramp_start_script();
extern void red_laser_ball_spawn();
extern void rocket_fire();
extern void rocket_fuchikoma_spawn();
extern void script_branch_on_flag();
extern void script_jump_if_below_height();
extern void script_jump_if_beyond_radius();
extern void script_jump_if_facing_player_in_radius();
extern void script_jump_if_not_below_speed();
extern void script_jump_if_outside_radius();
extern void script_jump_if_partner_kind();
extern void script_jump_near();
extern void script_jump_near_player();
extern void script_read_long();
extern void script_read_speed_long();
extern void smg_soldier_spawn();
extern void sound_emitter_step();
extern void sound_volume_phase2();
extern void sound_volume_ramp();
extern void spark_reset();
extern void state_machine_spawn();
extern u8 str_b10_dat_fac[];
extern u8 str_b10_ene_fac[];
extern u8 str_com_dat_fac[];
extern u8 str_enemy_ball_data[];
extern u8 str_enemy_bosa_data[];
extern u8 str_enemy_ctba_data[];
extern u8 str_enemy_ctla_data[];
extern u8 str_enemy_dora_data[];
extern u8 str_enemy_etr_data[];
extern u8 str_enemy_hou2_data[];
extern u8 str_enemy_mfir_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_msub_data[];
extern u8 str_enemy_mth1_data[];
extern u8 str_enemy_roi_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_m10_dat_fac[];
extern u8 str_m41_cnf_bcf[];
extern u8 str_m41_joy_bin[];
extern u8 str_main_data[];
extern u8 str_msgs_spr_clt[];
extern u8 str_msgs_spr_grc[];
extern u8 str_msgs_spr_so3[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_obs_apdea3[];
extern u8 str_obs_cnf_bcf[];
extern u8 str_obs_joy_bin[];
extern u8 str_ofs_apdea3[];
extern u8 str_ofs_cnf_bcf[];
extern u8 str_ofs_joy_bin[];
extern u8 str_s10_boss[];
extern u8 str_s10_dat_fac[];
extern u8 str_s10_ene_fac[];
extern u8 str_s10_miss[];
extern u8 str_s10_stage[];
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
extern void stream_read_s16();
extern u8 text_packets[];
extern void text_slot_setup();
extern void track_set_enabled();
extern void track_setup();
extern void triple_barrel_robot_spawn();
extern void turret_branch_if_aimed();
extern void turret_track_player();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_8011C0A8[];
extern u8 D_801238F2[];
extern u8 D_80124D19[];
extern u8 D_80124FC6[];
extern u8 cos_table[];
extern u8 d_80116A38[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 d_801201AE[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 door_extents_table[];
extern u8 door_range_x_table[];
extern u8 door_range_z_table[];
extern u8 enemy_death_script[];
extern u8 flow_angle[];
extern u8 gun_hit_effect_table[];
extern u8 obj_phase1_table[];
extern u8 obj_phase2_table[];
extern u8 obj_phase3_table[];
extern u8 script_mode0_reg0[];
extern u8 script_mode0_reg1[];
extern u8 script_mode0_reg2[];
extern u8 script_mode1_ch2[];
extern u8 script_mode1_reg0[];
extern u8 script_mode1_reg1[];
extern u8 shadow_tint_b[];
extern u8 shadow_tint_g[];
extern u8 shadow_tint_rgb[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 smg_soldier_hit_script[];
extern u8 view_sincos[];
extern s32 area;
extern ScanItem area_enemy_scan_items[];
extern AreaEntry d_80116CA0;
extern AreaEntry d_80116CC8;
extern ScanItem boss_scan_items[];
extern AreaEntry d_80116D08;
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern ModelSlotHead D_8011AFD0;
extern ModelBlockRef d_80116FBC[];
extern ModelBlockRef d_80116FD4[];
extern ModelBlockRef d_80116FE4[];
extern ModelBlockRange d_8011B014[];
extern ModelBlock pyramid_mine_model_block;
extern u8 *pyramid_mine_ptr_table_ids[];
extern ScanEntry pyramid_mine_scan_entry;
extern u32 d_8011B068[];
extern s16 pyramid_mine_script_pc[];
extern s16 *pyramid_mine_data[];
extern RecTemplate area_effect_fx_main;
extern RecTemplate area_effect_fx_pulse;
extern s16 moving_pyramid_mine_init[];
extern s16 moving_pyramid_mine_start[];
extern s16 pyramid_mine_watch[];
extern s16 pyramid_mine_detonate[];
extern s16 *pyramid_mine_script_data[];
extern s16 *D_8011B0F0;
extern ScriptCallEntry D_8011B0F4[];
extern StateEntry D_8011B124[];
extern s32 smg_soldier_asset[];
extern ModelBlockRef msub_palettes[];
extern ModelBlockRef msub_textures[];
extern ModelBlockRef D_8011B178[];
extern ModelBlockRange model_scale_ranges[];
extern ModelBlockRange model_link_ranges[];
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
extern s32 d_8011C114[];
extern ModelBlockRef triple_barrel_robot_palette_refs[];
extern ModelBlockRef triple_barrel_robot_texture_refs[];
extern ModelBlockRef triple_barrel_robot_model_refs[];
extern ModelBlock triple_barrel_robot_model_block;
extern u8 *triple_barrel_robot_ptr_names[];
extern ScanEntry triple_barrel_robot_scan_entry;
extern SoundVolume triple_barrel_robot_sounds[];
extern s16 triple_barrel_robot_anim_idle[];
extern s16 triple_barrel_robot_anim_fire[];
extern s16 triple_barrel_robot_anim_walk[];
extern s16 *triple_barrel_robot_data[];
extern s16 walker_mech_begin[];
extern s16 walker_mech_patrol_start[];
extern s16 walker_mech_watch[];
extern s16 walker_mech_engage_wait[];
extern s16 walker_mech_engage[];
extern s16 triple_barrel_robot_fire_end[];
extern s16 triple_barrel_robot_cooldown[];
extern s16 *triple_barrel_robot_script_table[];
extern s16 *d_8011C260;
extern ScriptCallEntry triple_barrel_robot_call_table[];
extern StateEntry triple_barrel_robot_state_table[];
extern ModelSlotHead timer_tail_data;
extern ModelBlockRef red_laser_ball_palette_refs[];
extern ModelBlockRef red_laser_ball_texture_refs[];
extern ModelBlockRef red_laser_ball_model_refs[];
extern ModelBlockRange red_laser_ball_scale_ranges[];
extern s16 red_laser_ball_palette_ids[];
extern ModelBlock red_laser_ball_model_block;
extern u8 *red_laser_ball_ptr_names[];
extern ScanEntry red_laser_ball_scan;
extern StateEntry red_laser_ball_states[1];
extern s16 red_laser_ball_script[];
extern s16 *red_laser_ball_data[];
extern s32 loop_sound_fade_handle;
extern s16 d_8011B7AC[];
extern BeamStep beam_segment_data[6];
extern s32 flamethrower_soldier_model[3];
extern ModelBlockRef enemy_clut_refs[];
extern ModelBlockRef d_80116748[];
extern ModelBlockRef enemy_mesh_refs[];
extern ModelBlockRange enemy_scales[];
extern ModelBlockRange d_801167A8[];
extern ModelBlock enemy_block_def;
extern u8 *D_8011B8B0[];
extern ScanEntry flamethrower_soldier_scan;
extern SoundVolume D_8011B8D0[1];
extern s16 enemy_start_script[];
extern s16 flamethrower_soldier_anim_idle[];
extern s16 flamethrower_soldier_anim_walk_start[];
extern s16 flamethrower_soldier_anim_walk[];
extern s16 flamethrower_soldier_anim_fire_start[];
extern s16 flamethrower_soldier_anim_fire_loop[];
extern s16 flamethrower_soldier_anim_stand[];
extern s16 flamethrower_soldier_anim_death[];
extern s16 *enemy_data[8];
extern s16 flamethrower_soldier_idle[];
extern s16 flamethrower_soldier_idle_wait[];
extern s16 flamethrower_soldier_idle_cycle[];
extern s16 flamethrower_soldier_patrol[];
extern s16 flamethrower_soldier_patrol_stop[];
extern s16 flamethrower_soldier_patrol_hold[];
extern s16 flamethrower_soldier_rest[];
extern s16 flamethrower_soldier_rest_wait[];
extern s16 flamethrower_soldier_rest_cycle[];
extern s16 flamethrower_soldier_walk[];
extern s16 flamethrower_soldier_walk_step[];
extern s16 flamethrower_soldier_walk_cycle[];
extern s16 flamethrower_soldier_walk_pause[];
extern s16 flamethrower_soldier_walk_pause_cycle[];
extern s16 *flamethrower_soldier_jumps[14];
extern s16 *flamethrower_soldier_scripts[5];
extern StateEntry D_8011BC1C[8];
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
extern ModelSlotHead gun_turret_2_asset;
extern ModelBlockRef gun_turret_2_palette_refs[];
extern ModelBlockRef gun_turret_2_texture_refs[];
extern ModelBlockRef gun_turret_2_model_refs[];
extern ModelBlock gun_turret_2_model_block;
extern u8 *gun_turret_2_ptr_table_ids[];
extern ScanEntry gun_turret_2_scan_entry;
extern u32 d_80116D8C[];
extern s16 gun_turret_2_pose[];
extern s16 *gun_turret_2_data;
extern s16 gun_turret_2_idle[];
extern s16 gun_turret_2_spotted[];
extern s16 gun_turret_2_tracking[];
extern s16 gun_turret_2_aimed[];
extern s16 gun_turret_2_open_fire[];
extern s16 gun_turret_2_firing[];
extern s16 gun_turret_2_cooldown[];
extern s16 gun_turret_2_cooling[];
extern s16 *gun_turret_2_link_data[];
extern s16 *gun_turret_2_script_pos[];
extern ScriptCallEntry gun_turret_2_calls[];
extern StateEntry gun_turret_2_states[];
extern u8 *elevator_door_ptr_table_ids[];
extern s32 D_8011C098;
extern s32 door_shape_origin;
extern u32 D_8011C0A0;
extern ScanEntry door_area_key;
extern ElevatorDoorShape elevator_door_shapes[3][2];
extern s32 door_shape_rows[];
extern s32 D_8011C148[];
extern ScanEntry D_8011C154;
extern s32 stage_end_zone_min_x;
extern s32 stage_end_zone_max_x;
extern s32 stage_end_zone_min_y;
extern s32 stage_end_zone_max_y;
extern s32 stage_end_zone_min_z;
extern s32 stage_end_zone_max_z;
extern s32 door_trigger_min_x;
extern s32 door_trigger_max_x;
extern s32 door_trigger_min_y;
extern s32 door_trigger_max_y;
extern s32 door_trigger_min_z;
extern s32 door_trigger_max_z;
extern s32 warp_from_origin_x;
extern s32 warp_from_origin_y;
extern s32 warp_from_origin_z;
extern u32 D_8011C1A8;
extern s32 warp_to_origin_x;
extern s32 warp_to_origin_y;
extern s32 warp_to_origin_z;
extern u32 D_8011C1B8;
extern s32 state_machine_req_table[];
extern PathPoint warp_cam_path[8];
extern PathPoint door_cam_path[10];
extern s32 stream_last_s16;
extern s32 d_80119E84;
extern ModelSlotHead arrival_warning_asset;
extern ModelBlockRef D_8011C310[];
extern ModelBlockRef D_8011C328[];
extern ModelBlockRef D_8011C350[];
extern ModelBlockRange D_8011C368[];
extern ModelBlockRange D_8011C3B8[];
extern ModelBlock D_8011C408;
extern u8 *bosa_file_list[];
extern ScanEntry D_8011C440;
extern ModelSlotHead dual_mech_asset_head;
extern s16 dual_mech_m10_boss_anim_idle[];
extern s16 dual_mech_m10_boss_anim_raise_a[];
extern s16 dual_mech_m10_boss_anim_hold_a[];
extern s16 dual_mech_m10_boss_anim_lower_a[];
extern s16 dual_mech_m10_boss_anim_raise_b[];
extern s16 dual_mech_m10_boss_anim_hold_b[];
extern s16 dual_mech_m10_boss_anim_lower_b[];
extern s16 dual_mech_m10_boss_anim_raise_c[];
extern s16 dual_mech_m10_boss_anim_hold_c[];
extern s16 dual_mech_m10_boss_anim_lower_c[];
extern s16 dual_mech_m10_boss_anim_lower_c_end[];
extern s16 dual_mech_m10_boss_anim_raise_d[];
extern s16 dual_mech_m10_boss_anim_hold_d[];
extern s16 dual_mech_m10_boss_anim_lower_d[];
extern s16 dual_mech_m10_boss_anim_lower_d_end[];
extern s16 dual_mech_m10_boss_anim_raise_lower_c_slow[];
extern s16 dual_mech_m10_boss_anim_raise_d_slow[];
extern s16 dual_mech_m10_boss_anim_hold_d_slow[];
extern s16 dual_mech_m10_boss_anim_lower_d_slow[];
extern s16 dual_mech_m10_boss_anim_lower_d_idle_slow[];
extern s16 *dual_mech_m10_boss_data[];
extern s16 dual_mech_m10_boss_spawn_a[];
extern s16 dual_mech_m10_boss_spawn_close_a[];
extern s16 dual_mech_m10_boss_setup_a[];
extern s16 dual_mech_m10_boss_decide_a[];
extern s16 dual_mech_m10_boss_aim_mode_pick_a[];
extern s16 dual_mech_m10_boss_aim_mode_split_a[];
extern s16 dual_mech_m10_boss_aim_mode_direct_a[];
extern s16 dual_mech_m10_boss_aim_mode_low_a[];
extern s16 dual_mech_m10_boss_aim_mode_wide_a[];
extern s16 dual_mech_m10_boss_aim_mode_tight_a[];
extern s16 dual_mech_m10_boss_aim_mode_cluster_a[];
extern s16 dual_mech_m10_boss_aim_mode_sweep_a[];
extern s16 dual_mech_m10_boss_aim_mode_behind_a[];
extern s16 dual_mech_m10_boss_attack_route_a[];
extern s16 dual_mech_m10_boss_attack_pick_high_a[];
extern s16 dual_mech_m10_boss_attack_pick_low_a[];
extern s16 dual_mech_m10_boss_aim_first_setup_a[];
extern s16 dual_mech_m10_boss_aim_first_a[];
extern s16 dual_mech_m10_boss_aim_first_turn_a[];
extern s16 dual_mech_m10_boss_aim_first_check_a[];
extern s16 dual_mech_m10_boss_aim_first_wait_a[];
extern s16 dual_mech_m10_boss_aim_first_loop_a[];
extern s16 dual_mech_m10_boss_aim_second_setup_a[];
extern s16 dual_mech_m10_boss_aim_second_a[];
extern s16 dual_mech_m10_boss_aim_second_turn_a[];
extern s16 dual_mech_m10_boss_aim_second_check_a[];
extern s16 dual_mech_m10_boss_aim_second_wait_a[];
extern s16 dual_mech_m10_boss_aim_second_loop_a[];
extern s16 dual_mech_m10_boss_aim_third_setup_a[];
extern s16 dual_mech_m10_boss_aim_third_a[];
extern s16 dual_mech_m10_boss_aim_third_turn_a[];
extern s16 dual_mech_m10_boss_aim_third_check_a[];
extern s16 dual_mech_m10_boss_aim_third_wait_a[];
extern s16 dual_mech_m10_boss_aim_third_loop_a[];
extern s16 dual_mech_m10_boss_aim_fourth_setup_a[];
extern s16 dual_mech_m10_boss_aim_fourth_a[];
extern s16 dual_mech_m10_boss_aim_fourth_turn_a[];
extern s16 dual_mech_m10_boss_aim_fourth_check_a[];
extern s16 dual_mech_m10_boss_aim_fourth_route_a[];
extern s16 dual_mech_m10_boss_aim_fourth_dash_route_a[];
extern s16 dual_mech_m10_boss_aim_fourth_dash_check_a[];
extern s16 dual_mech_m10_boss_aim_fourth_loop_a[];
extern s16 dual_mech_m10_boss_dash_a[];
extern s16 dual_mech_m10_boss_fire_burst_a[];
extern s16 dual_mech_m10_boss_dash_idle_a[];
extern s16 dual_mech_m10_boss_laser_arm_a[];
extern s16 dual_mech_m10_boss_laser_fire_a[];
extern s16 dual_mech_m10_boss_laser_fire_repeat_a[];
extern s16 dual_mech_m10_boss_laser_fire_alt_a[];
extern s16 dual_mech_m10_boss_laser_end_a[];
extern s16 dual_mech_m10_boss_laser_arm_idle_a[];
extern s16 dual_mech_m10_boss_debris_arm_a[];
extern s16 dual_mech_m10_boss_debris_fire_a[];
extern s16 dual_mech_m10_boss_debris_end_a[];
extern s16 dual_mech_m10_boss_debris_arm_idle_a[];
extern s16 dual_mech_m10_boss_spawn_b[];
extern s16 dual_mech_m10_boss_spawn_close_b[];
extern s16 dual_mech_m10_boss_setup_b[];
extern s16 dual_mech_m10_boss_decide_b[];
extern s16 dual_mech_m10_boss_aim_mode_pick_b[];
extern s16 dual_mech_m10_boss_aim_mode_split_b[];
extern s16 dual_mech_m10_boss_aim_mode_direct_b[];
extern s16 dual_mech_m10_boss_aim_mode_low_b[];
extern s16 dual_mech_m10_boss_aim_mode_wide_b[];
extern s16 dual_mech_m10_boss_aim_mode_tight_b[];
extern s16 dual_mech_m10_boss_aim_mode_cluster_b[];
extern s16 dual_mech_m10_boss_aim_mode_sweep_b[];
extern s16 dual_mech_m10_boss_aim_mode_behind_b[];
extern s16 dual_mech_m10_boss_attack_route_b[];
extern s16 dual_mech_m10_boss_attack_pick_high_b[];
extern s16 dual_mech_m10_boss_attack_pick_low_b[];
extern s16 dual_mech_m10_boss_aim_first_setup_b[];
extern s16 dual_mech_m10_boss_aim_first_b[];
extern s16 dual_mech_m10_boss_aim_first_turn_b[];
extern s16 dual_mech_m10_boss_aim_first_check_b[];
extern s16 dual_mech_m10_boss_aim_first_wait_b[];
extern s16 dual_mech_m10_boss_aim_first_loop_b[];
extern s16 dual_mech_m10_boss_aim_second_setup_b[];
extern s16 dual_mech_m10_boss_aim_second_b[];
extern s16 dual_mech_m10_boss_aim_second_turn_b[];
extern s16 dual_mech_m10_boss_aim_second_check_b[];
extern s16 dual_mech_m10_boss_aim_second_wait_b[];
extern s16 dual_mech_m10_boss_aim_second_loop_b[];
extern s16 dual_mech_m10_boss_aim_third_setup_b[];
extern s16 dual_mech_m10_boss_aim_third_b[];
extern s16 dual_mech_m10_boss_aim_third_turn_b[];
extern s16 dual_mech_m10_boss_aim_third_check_b[];
extern s16 dual_mech_m10_boss_aim_third_wait_b[];
extern s16 dual_mech_m10_boss_aim_third_loop_b[];
extern s16 dual_mech_m10_boss_aim_fourth_setup_b[];
extern s16 dual_mech_m10_boss_aim_fourth_b[];
extern s16 dual_mech_m10_boss_aim_fourth_turn_b[];
extern s16 dual_mech_m10_boss_aim_fourth_check_b[];
extern s16 dual_mech_m10_boss_aim_fourth_route_b[];
extern s16 dual_mech_m10_boss_aim_fourth_dash_route_b[];
extern s16 dual_mech_m10_boss_aim_fourth_dash_check_b[];
extern s16 dual_mech_m10_boss_aim_fourth_loop_b[];
extern s16 dual_mech_m10_boss_dash_b[];
extern s16 dual_mech_m10_boss_fire_burst_b[];
extern s16 dual_mech_m10_boss_dash_idle_b[];
extern s16 dual_mech_m10_boss_rocket_arm_b[];
extern s16 dual_mech_m10_boss_rocket_fire_b[];
extern s16 dual_mech_m10_boss_rocket_fire_repeat_b[];
extern s16 dual_mech_m10_boss_rocket_fire_alt_b[];
extern s16 dual_mech_m10_boss_rocket_end_b[];
extern s16 dual_mech_m10_boss_rocket_arm_idle_b[];
extern s16 dual_mech_m10_boss_dash_settle[];
extern s16 dual_mech_m10_boss_dash_end[];
extern s16 dual_mech_m10_boss_dash_settle_idle_b[];
extern s16 *D_8011CDD4[109];
extern s16 *dual_mech_script_ids[];
extern ScriptCallEntry dual_mech_table_a[17];
extern StateEntry dual_mech_table_b[24];
extern s32 turn_frame_offsets[];
extern s16 target_blend_table_a[][4];
extern s16 target_blend_table_b[][4];
extern s16 target_blend_table_c[][4];
extern RecTemplate rocket_blast_templates[2];
extern FxRecordParams D_8011D3E8;
extern RecTemplate effect_template;
extern void (*effect_callback_table[])();
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern RecTemplate obj_fx_template_a;
extern RecTemplate obj_fx_template_b;
extern FxRecordParams d_8011ACDC;
extern void (*obj_init_table[])(Object *);
extern ObjPhaseEntry obj_phase0_table[4];
extern s32 D_8011D508[];
extern ScanEntry enemy_ctba_entry;
extern s16 spark_level_offsets[3];
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *D_8011D5A4[];
extern ScanEntry enemy_msgs_scan_entry;
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern s16 video_mode_id;
extern s16 debug_cam_speed_table[][2];
extern s32 pause_prev_work_area;
extern s32 vblank_task_handle;
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_80122168[];
extern u16 inv_sqrt_table[];
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
extern u32 D_801232CC[];
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
extern u32 D_801238EC;
extern u16 texture_image[];
extern u16 stage_image_width;
extern u16 stage_image_height;
extern u32 stage_image_pixels[];
extern s32 heap_top;
extern s32 heap2_top;
extern s32 door_light_base;
extern s32 elevator_cam_slot;
extern s32 elevator_inside_flag;
extern s32 elevator_nudge_phase;
extern s32 spark_base;
extern u8 door_state_table[];
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
extern u32 D_80124E14;
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
extern u32 D_80124EB0;
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

s32 area = 0x1B;

ScanItem area_enemy_scan_items[10] = {
    {&pyramid_mine_scan_entry, str_enemy_etr_data},
    {&d_80117040, str_enemy_msub_data},
    {&triple_barrel_robot_scan_entry, str_enemy_roi_data},
    {&red_laser_ball_scan, str_enemy_ball_data},
    {&flamethrower_soldier_scan, str_enemy_mfir_data},
    {&d_80117448, str_enemy_mth1_data},
    {&gun_turret_2_scan_entry, str_enemy_hou2_data},
    {&door_area_key, str_enemy_dora_data},
    {&D_8011C154, str_enemy_ctla_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116CA0 = {str_s10_stage, str_ofs_cnf_bcf, str_ofs_apdea3, str_ofs_joy_bin, str_s10_dat_fac, str_s10_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, area_enemy_scan_items};

AreaEntry d_80116CC8 = {str_s10_miss, str_m41_cnf_bcf, NULL, str_m41_joy_bin, str_m10_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

ScanItem boss_scan_items[4] = {
    {&enemy_ctba_entry, str_enemy_ctba_data},
    {&enemy_msgs_scan_entry, str_enemy_msgs_data},
    {&D_8011C440, str_enemy_bosa_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116D08 = {str_s10_boss, str_obs_cnf_bcf, str_obs_apdea3, str_obs_joy_bin, str_b10_dat_fac, str_b10_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, boss_scan_items};

#include "../stage/data/area_entry_table.c"

#include "../stage/data/debug_name_buf.c"

ModelSlotHead D_8011AFD0 = {{-1, -1, -1}};

#include "../stage/data/d_80116FBC.c"

#include "../stage/data/d_80116FD4.c"

#include "../stage/data/d_80116FE4.c"

#include "../stage/data/d_8011B014.c"

#include "../stage/data/pyramid_mine_model_block.c"

#include "../stage/data/pyramid_mine_ptr_table_ids.c"

ScanEntry pyramid_mine_scan_entry = {{0, (s32)pyramid_mine_spawn}, (s32 *)&D_8011AFD0, (s32)&pyramid_mine_model_block, (s32)pyramid_mine_ptr_table_ids, 0};

#include "../stage/data/d_8011B068.c"

struct PyramidMineScriptAnims {
    s16 pc[4];
    s16 *table[1];
} pyramid_mine_script_anims = {
    /* pc */ {
        STEP(1, 11),
        GOTO(PYRAMID_MINE_SCRIPT_PC),
    },
    /* table */ {
        pyramid_mine_script_anims.pc,
    },
};

#include "../stage/data/area_effect_fx_main.c"

#include "../stage/data/area_effect_fx_pulse.c"

struct PyramidMineScriptDataStreams {
    s16 moving_pyramid_mine_init[2];
    s16 moving_pyramid_mine_start[6];
    s16 pyramid_mine_watch[10];
    s16 pyramid_mine_detonate[6];
    s16 *table[4];
    s16 *D_8011B0F0;
} pyramid_mine_script_data_streams = {
    /* moving_pyramid_mine_init */ {
        JUMP(MOVING_PYRAMID_MINE_START),
    },
    /* moving_pyramid_mine_start */ {
        PYRAMID_MINE_SET_SPEED, 16,
        PYRAMID_MINE_READ_NEXT_STATE, PYRAMID_MINE_STATE_ZIGZAG,
        JUMP(PYRAMID_MINE_WATCH),
    },
    /* pyramid_mine_watch */ {
        WAIT(1),
        JUMP_IF_STATE(PYRAMID_MINE_STATE_BURST, PYRAMID_MINE_DETONATE),
        PYRAMID_MINE_BRANCH_IF_NEAR, 312, PYRAMID_MINE_DETONATE,
        JUMP(PYRAMID_MINE_WATCH),
    },
    /* pyramid_mine_detonate */ {
        WAIT(1),
        PYRAMID_MINE_READ_NEXT_STATE, PYRAMID_MINE_STATE_BURST,
        JUMP(PYRAMID_MINE_DETONATE),
    },
    /* table */ {
        pyramid_mine_script_data_streams.moving_pyramid_mine_init, pyramid_mine_script_data_streams.moving_pyramid_mine_start, pyramid_mine_script_data_streams.pyramid_mine_watch, pyramid_mine_script_data_streams.pyramid_mine_detonate,
    },
    /* D_8011B0F0 */ pyramid_mine_script_data_streams.moving_pyramid_mine_init,
};

ScriptCallEntry D_8011B0F4[6] = {
    {NULL, 0},
    {obj_script_set_speed, 0},
    {obj_script_read_next_state, 0},
    {fn_800B7514, 0},
    {obj_script_branch_if_near, 0},
    {obj_script_branch_if_far, 0},
};

StateEntry D_8011B124[4] = {
    {0, PYRAMID_MINE_SCRIPT_PC, 0},
    {(u32)obj_zigzag_move, PYRAMID_MINE_SCRIPT_PC, 0},
    {(u32)obj_expire_burst, PYRAMID_MINE_SCRIPT_PC, 0},
    {0, PYRAMID_MINE_SCRIPT_PC, 0},
};

#include "../stage/data/smg_soldier_asset.c"

#include "../stage/data/msub_palettes.c"

#include "../stage/data/msub_textures.c"

ModelBlockRef D_8011B178[2] = {
    {(s32)file_msub_ch0_vx1, 0, 0},
    {0, 0, 0},
};

#include "../stage/data/model_scale_ranges.c"

#include "../stage/data/model_link_ranges.c"

ModelBlock d_80117014 = {(s32)msub_palettes, (s32)D_8011B178, (s32)msub_textures, (s32)model_link_ranges, 0, 0, (s32)model_scale_ranges, 0, 0};

#include "../stage/data/msub_file_table.c"

#include "../stage/data/smg_soldier_sounds.c"

#include "../stage/data/d_8011C114.c"

ModelBlockRef triple_barrel_robot_palette_refs[3] = {
    {(s32)file_troi_ch0_clt, 0, 0},
    {(s32)file_troi_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef triple_barrel_robot_texture_refs[2] = {
    {(s32)file_troi_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef triple_barrel_robot_model_refs[2] = {
    {(s32)file_troi_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock triple_barrel_robot_model_block = {(s32)triple_barrel_robot_palette_refs, (s32)triple_barrel_robot_model_refs, (s32)triple_barrel_robot_texture_refs, 0, 0, 0, 0, 0, 0};

u8 *triple_barrel_robot_ptr_names[2] = {
    file_troi_ch0_cb4, NULL,
};

#include "../stage/data/triple_barrel_robot_scan_entry.c"

#include "../stage/data/triple_barrel_robot_sounds.c"

#include "../stage/data/triple_barrel_robot_anims.c"

#include "../stage/data/triple_barrel_robot_script_table_streams.c"

#include "../stage/data/triple_barrel_robot_call_table.c"

#include "../stage/data/triple_barrel_robot_state_table.c"

#include "../stage/data/timer_tail_data.c"

ModelBlockRef red_laser_ball_palette_refs[3] = {
    {(s32)file_ball_ch0_clt, 0, 0},
    {(s32)file_ball_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef red_laser_ball_texture_refs[2] = {
    {(s32)file_ball_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef red_laser_ball_model_refs[2] = {
    {(s32)file_ball_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange red_laser_ball_scale_ranges[2] = {
    {1, 1, 0x400, 0}, {-1, 0, 0, 0},
};

s16 red_laser_ball_palette_ids[4] = {
    1, 0x100, 0x11F, 0,
};

ModelBlock red_laser_ball_model_block = {(s32)red_laser_ball_palette_refs, (s32)red_laser_ball_model_refs, (s32)red_laser_ball_texture_refs, 0, 0, 0, (s32)red_laser_ball_scale_ranges, (s32)red_laser_ball_palette_ids, 0};

u8 *red_laser_ball_ptr_names[2] = {
    file_ball_ch0_cb4, NULL,
};

ScanEntry red_laser_ball_scan = {{(s32)loop_sound_fade_in, (s32)red_laser_ball_spawn}, (s32 *)&timer_tail_data, (s32)&red_laser_ball_model_block, (s32)red_laser_ball_ptr_names, 0};

StateEntry red_laser_ball_states[1] = {
    {0, 0, 0},
};

struct RedLaserBallAnims {
    s16 script[4];
    s16 *table[1];
} red_laser_ball_anims = {
    /* script */ {
        STEP(1, 1),
        GOTO(RED_LASER_BALL_SCRIPT),
    },
    /* table */ {
        red_laser_ball_anims.script,
    },
};

#include "../stage/data/loop_sound_fade_handle.c"

#include "../stage/data/d_8011B7AC.c"

#include "../stage/data/beam_segment_data.c"

s32 flamethrower_soldier_model[3] = {
    -1, -1, -1,
};

ModelBlockRef enemy_clut_refs[3] = {
    {(s32)file_mfir_ch0_clt, 0, 0},
    {(s32)file_mfir_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef d_80116748[2] = {
    {(s32)file_mfir_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef enemy_mesh_refs[2] = {
    {(s32)file_mfir_ch0_vx1, 0, 0},
    {0, 0, 0},
};

#include "../stage/data/enemy_scales.c"

#include "../stage/data/d_801167A8.c"

#include "../stage/data/enemy_block_def.c"

u8 *D_8011B8B0[2] = {
    file_mfir_ch0_cb4, NULL,
};

ScanEntry flamethrower_soldier_scan = {{0, (s32)enemy_create}, flamethrower_soldier_model, (s32)&enemy_block_def, (s32)D_8011B8B0, 0};

SoundVolume D_8011B8D0[1] = {
    {SND_GROUND_IMPACT | SND_GROUP(2), 0x1000},
};

#include "../stage/data/enemy_data_streams.c"

struct FlamethrowerSoldierScriptsSet {
    s16 idle[6];
    s16 idle_wait[4];
    s16 idle_cycle[10];
    s16 patrol[6];
    s16 patrol_stop[12];
    s16 patrol_hold[6];
    s16 rest[4];
    s16 rest_wait[4];
    s16 rest_cycle[10];
    s16 walk[4];
    s16 walk_step[4];
    s16 walk_cycle[10];
    s16 walk_pause[4];
    s16 walk_pause_cycle[10];
    s16 *table[14];
    s16 *scripts[5];
} flamethrower_soldier_scripts_set = {
    /* idle */ {
        JUMP_RANDOM(3072, FLAMETHROWER_SOLDIER_PATROL),
        SET_COUNTER_RANDOM(3, 1),
    },
    /* idle_wait */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* idle_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, FLAMETHROWER_SOLDIER_IDLE_CYCLE),
        LOOP(FLAMETHROWER_SOLDIER_IDLE_WAIT),
        JUMP(FLAMETHROWER_SOLDIER_IDLE),
    },
    /* patrol */ {
        WAIT(1),
        WANDER(1),
        NEXT_STATE(ENEMY_STATE_WANDER),
    },
    /* patrol_stop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, FLAMETHROWER_SOLDIER_PATROL_STOP),
        SET_SPEED(0),
        WANDER(1),
        SET_COUNTER_RANDOM(5, 3),
    },
    /* patrol_hold */ {
        WAIT(1),
        LOOP(FLAMETHROWER_SOLDIER_PATROL_HOLD),
        JUMP(FLAMETHROWER_SOLDIER_IDLE),
    },
    /* rest */ {
        SET_COUNTER_RANDOM(3, 1),
    },
    /* rest_wait */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* rest_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, FLAMETHROWER_SOLDIER_REST_CYCLE),
        LOOP(FLAMETHROWER_SOLDIER_REST_WAIT),
        JUMP(FLAMETHROWER_SOLDIER_REST),
    },
    /* walk */ {
        SET_COUNTER_RANDOM(4, 1),
    },
    /* walk_step */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WANDER),
    },
    /* walk_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, FLAMETHROWER_SOLDIER_WALK_CYCLE),
        LOOP(FLAMETHROWER_SOLDIER_WALK_STEP),
        JUMP(FLAMETHROWER_SOLDIER_WALK),
    },
    /* walk_pause */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* walk_pause_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, FLAMETHROWER_SOLDIER_WALK_PAUSE_CYCLE),
        LOOP(FLAMETHROWER_SOLDIER_WALK_PAUSE),
        JUMP(FLAMETHROWER_SOLDIER_WALK),
    },
    /* table */ {
        flamethrower_soldier_scripts_set.idle, flamethrower_soldier_scripts_set.idle_wait, flamethrower_soldier_scripts_set.idle_cycle, flamethrower_soldier_scripts_set.patrol, flamethrower_soldier_scripts_set.patrol_stop, flamethrower_soldier_scripts_set.patrol_hold,
        flamethrower_soldier_scripts_set.rest, flamethrower_soldier_scripts_set.rest_wait, flamethrower_soldier_scripts_set.rest_cycle, flamethrower_soldier_scripts_set.walk, flamethrower_soldier_scripts_set.walk_step, flamethrower_soldier_scripts_set.walk_cycle,
        flamethrower_soldier_scripts_set.walk_pause, flamethrower_soldier_scripts_set.walk_pause_cycle,
    },
    /* scripts */ {
        flamethrower_soldier_scripts_set.idle, flamethrower_soldier_scripts_set.rest, flamethrower_soldier_scripts_set.walk, flamethrower_soldier_scripts_set.rest, flamethrower_soldier_scripts_set.walk,
    },
};

StateEntry D_8011BC1C[8] = {
    {0, ENEMY_START_SCRIPT, 0},
    {(u32)enemy_wait_switch, FLAMETHROWER_SOLDIER_ANIM_IDLE, 0},
    {(u32)enemy_move_or_wait, FLAMETHROWER_SOLDIER_ANIM_WALK_START, 0},
    {(u32)enemy_walk_step, FLAMETHROWER_SOLDIER_ANIM_FIRE_START, 0},
    {(u32)flyer_wander, FLAMETHROWER_SOLDIER_ANIM_FIRE_START, 0},
    {(u32)beam_enemy_attack_update, FLAMETHROWER_SOLDIER_ANIM_STAND, 0},
    {(u32)flyer_retreat, FLAMETHROWER_SOLDIER_ANIM_WALK, 0},
    {0, FLAMETHROWER_SOLDIER_ANIM_DEATH, 0},
};

#include "../stage/data/rocket_fuchikoma_asset.c"

#include "../stage/data/script_call_table.c"

#include "../stage/data/rocket_fuchikoma_state_table.c"

#include "../stage/data/gun_turret_2_asset.c"

#include "../stage/data/gun_turret_2_palette_refs.c"

#include "../stage/data/gun_turret_2_texture_refs.c"

#include "../stage/data/gun_turret_2_model_refs.c"

#include "../stage/data/gun_turret_2_model_block.c"

#include "../stage/data/gun_turret_2_ptr_table_ids.c"

#include "../stage/data/gun_turret_2_scan_entry.c"

#include "../stage/data/d_80116D8C.c"

#include "../stage/data/gun_turret_2_anims.c"

#include "../stage/data/gun_turret_2_scripts.c"

#include "../stage/data/gun_turret_2_calls.c"

#include "../stage/data/gun_turret_2_states.c"

u8 *elevator_door_ptr_table_ids[2] = {
    file_dora_ch0_cb4, NULL,
};

s32 D_8011C098 = -1;

s32 door_shape_origin = -1;

u32 D_8011C0A0 = 0xFFFFFFFF;

ScanEntry door_area_key = {{(s32)door_table_init, (s32)elevator_doors_spawn}, &D_8011C098, 0, (s32)elevator_door_ptr_table_ids, 0};

ElevatorDoorShape elevator_door_shapes[3][2] = {
    {{0xD9, 0xD7, 8, 9, 0x90, 0, 0x3E8, 0x3E8}, {0xDA, 0xD8, 0xA, 0xB, -0x90, 0, 0x3E8, 0x3E8}},
    {{0x59, 0x7D, 0, 1, 0xA8, 0, 0x3E8, 0x4B0}, {0x5A, 0x7E, 2, 3, -0xA8, 0, 0x3E8, 0x4B0}},
    {{0x78, 0x76, 4, 5, 0, 0x48, 0x3E8, 0x3E8}, {0x79, 0x77, 6, 7, 0, -0x48, 0x3E8, 0x3E8}},
};

s32 door_shape_rows[11] = {
    0, 0, 1, 2, 2, 2,
    2, 2, 2, 2, 2,
};

s32 D_8011C148[3] = {
    -1, -1, -1,
};

ScanEntry D_8011C154 = {{(s32)func_800C11D8, (s32)state_machine_spawn}, D_8011C148, 0, 0, 0};

s32 stage_end_zone_min_x = 0x4E8;

s32 stage_end_zone_max_x = 0x77C;

s32 stage_end_zone_min_y = -0x690;

s32 stage_end_zone_max_y = -0x2E4;

s32 stage_end_zone_min_z = -0x20D0;

s32 stage_end_zone_max_z = -0x1B58;

s32 door_trigger_min_x = 0x7F8;

s32 door_trigger_max_x = 0xB22;

s32 door_trigger_min_y = -0x4CE;

s32 door_trigger_max_y = -0x320;

s32 door_trigger_min_z = 0x1086;

s32 door_trigger_max_z = 0x125C;

s32 warp_from_origin_x = 0x988;

s32 warp_from_origin_y = -0x450;

s32 warp_from_origin_z = 0xF08;

u32 D_8011C1A8 = 0x00000000;

s32 warp_to_origin_x = 0x4530;

s32 warp_to_origin_y = -0x180;

s32 warp_to_origin_z = -0x1B60;

u32 D_8011C1B8 = 0x00000000;

s32 state_machine_req_table[8] = {
    0x988, -0x330, 0x10F9, 0, 0x618, -0x300,
    -0x1DF1, 0,
};

PathPoint warp_cam_path[8] = {
    {-0x1C5, -0x5D0, 0x1F27, 0}, {-0x1355, -0x5D0, 0x1F27, 0}, {-0x1355, -0x5D0, 0x19DC, 0},
    {-0x1B3F, -0x5D0, 0x19DC, 0}, {-0x2313, -0x330, 0x109B, 0}, {-0x2313, -0x330, 0x23B, 0},
    {0x981, -0x330, 0x23B, 0}, {0x981, -0x330, 0x1086, 0},
};

PathPoint door_cam_path[10] = {
    {0x452E, -0x60, -0x2AB9, 0}, {0x3031, -0x60, -0x2AB9, 0}, {0x3031, -0x60, -0x375B, 0},
    {0x26A0, -0x300, -0x4262, 0}, {0x230B, -0x300, -0x4262, 0}, {0x230B, -0x300, -0x5A01, 0},
    {0xB74, -0x300, -0x5A01, 0}, {0xB74, -0x300, -0x4679, 0}, {0x636, -0x300, -0x4679, 0},
    {0x636, -0x300, -0x1F40, 0},
};

s32 stream_last_s16 = 0;

#include "../stage/data/d_80119E84.c"

ModelSlotHead arrival_warning_asset = {{-1, -1, -1}};

ModelBlockRef D_8011C310[3] = {
    {(s32)file_bosa_ch0_clt, 0, 0},
    {(s32)file_bosa_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C328[5] = {
    {(s32)file_bosa_ch0_vx1, 0, 0},
    {(s32)file_bosa_ch1_vx1, 0, 0},
    {(s32)file_bosa_ch2_vx1, 0, 0},
    {(s32)file_bosa_ch3_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C350[3] = {
    {(s32)file_bosa_tp0_xs3, 1, 0},
    {(s32)file_bosa_tp1_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011C368[10] = {
    {0xC0, 0xC4, 0x2000, 0}, {0xC8, 0xCA, 0x2000, 0}, {0xCC, 0xCF, 0x1000, 0}, {0xD2, 0xD5, 0x2000, 0},
    {0xDA, 0xDA, 0x2000, 0}, {0xE2, 0xE7, 0x2000, 0}, {0xE9, 0xEC, 0x1000, 0}, {0xEE, 0xEE, 0x2000, 0},
    {0xF0, 0xF7, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlockRange D_8011C3B8[10] = {
    {0, 0x7F, 0x1000, 0}, {0x80, 0xBF, 0x1000, 0}, {0xC0, 0xC7, 0xCCC, 0}, {0xD0, 0xD1, 0x1000, 0},
    {0xD8, 0xDB, 0x666, 0}, {0xE0, 0xE1, 0x1000, 0}, {0xE2, 0xF7, 0x1800, 0}, {0x100, 0x17F, 0x1000, 0},
    {0x180, 0x1BF, 0x1000, 0}, {-1, 0, 0, 0},
};

ModelBlock D_8011C408 = {(s32)D_8011C310, (s32)D_8011C328, (s32)D_8011C350, 0, (s32)D_8011C368, 0, (s32)D_8011C3B8, 0, 0};

u8 *bosa_file_list[5] = {
    file_bosa_ch0_cb4, file_bosa_ch1_cb4, file_bosa_ch2_cb4, file_bosa_ch3_cb4, NULL,
};

ScanEntry D_8011C440 = {{(s32)arrival_warning_start, 0}, (s32 *)&arrival_warning_asset, (s32)&D_8011C408, (s32)bosa_file_list, 0};

ModelSlotHead dual_mech_asset_head = {{-1, -1, -1}};

struct DualMechM10BossAnims {
    s16 idle[4];
    s16 raise_a[18];
    s16 hold_a[4];
    s16 lower_a[18];
    s16 raise_b[18];
    s16 hold_b[4];
    s16 lower_b[24];
    s16 raise_c[28];
    s16 hold_c[4];
    s16 lower_c[12];
    s16 lower_c_end[20];
    s16 raise_d[28];
    s16 hold_d[4];
    s16 lower_d[12];
    s16 lower_d_end[20];
    s16 raise_lower_c_slow[62];
    s16 raise_d_slow[28];
    s16 hold_d_slow[4];
    s16 lower_d_slow[12];
    s16 lower_d_idle_slow[20];
    s16 *table[20];
} dual_mech_m10_boss_anims = {
    /* idle */ {
        STEP(2, 1),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_IDLE),
    },
    /* raise_a */ {
        STEP(1, 5),
        STEP(1, 6),
        STEP(1, 7),
        STEP(1, 8),
        STEP(1, 9),
        STEP(1, 10),
        STEP(1, 11),
        STEP(1, 12),
        STEP(1, 13),
    },
    /* hold_a */ {
        STEP(1, 14),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_HOLD_A),
    },
    /* lower_a */ {
        STEP(1, 15),
        STEP(1, 16),
        STEP(1, 17),
        STEP(1, 18),
        STEP(1, 19),
        STEP(1, 20),
        STEP(1, 21),
        STEP(1, 1),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_IDLE),
    },
    /* raise_b */ {
        STEP(1, 97),
        STEP(1, 98),
        STEP(1, 99),
        STEP(1, 100),
        STEP(1, 101),
        STEP(1, 102),
        STEP(1, 103),
        STEP(1, 104),
        STEP(1, 105),
    },
    /* hold_b */ {
        STEP(1, 106),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_HOLD_B),
    },
    /* lower_b */ {
        STEP(1, 106),
        STEP(1, 107),
        STEP(1, 108),
        STEP(1, 109),
        STEP(1, 110),
        STEP(1, 111),
        STEP(1, 112),
        STEP(1, 113),
        STEP(1, 114),
        STEP(1, 115),
        STEP(1, 1),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_IDLE),
    },
    /* raise_c */ {
        STEP(1, 129),
        STEP(1, 130),
        STEP(1, 131),
        STEP(1, 132),
        STEP(1, 133),
        STEP(1, 134),
        STEP(1, 135),
        STEP(1, 136),
        STEP(1, 137),
        STEP(1, 138),
        STEP(1, 139),
        STEP(1, 140),
        STEP(1, 141),
        STEP(1, 142),
    },
    /* hold_c */ {
        STEP(1, 143),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_HOLD_C),
    },
    /* lower_c */ {
        STEP(1, 144),
        STEP(1, 145),
        STEP(1, 146),
        STEP(1, 147),
        STEP(1, 148),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_HOLD_C),
    },
    /* lower_c_end */ {
        STEP(1, 150),
        STEP(1, 151),
        STEP(1, 152),
        STEP(1, 153),
        STEP(1, 154),
        STEP(1, 155),
        STEP(1, 156),
        STEP(1, 157),
        STEP(1, 1),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_IDLE),
    },
    /* raise_d */ {
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
    },
    /* hold_d */ {
        STEP(1, 175),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_HOLD_D),
    },
    /* lower_d */ {
        STEP(1, 176),
        STEP(1, 177),
        STEP(1, 178),
        STEP(1, 179),
        STEP(1, 180),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_HOLD_D),
    },
    /* lower_d_end */ {
        STEP(1, 182),
        STEP(1, 183),
        STEP(1, 184),
        STEP(1, 185),
        STEP(1, 186),
        STEP(1, 187),
        STEP(1, 188),
        STEP(1, 189),
        STEP(1, 1),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_IDLE),
    },
    /* raise_lower_c_slow */ {
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
        STEP(2, 1),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_IDLE),
    },
    /* raise_d_slow */ {
        STEP(2, 161),
        STEP(2, 162),
        STEP(2, 163),
        STEP(2, 164),
        STEP(2, 165),
        STEP(2, 166),
        STEP(2, 167),
        STEP(2, 168),
        STEP(2, 169),
        STEP(2, 170),
        STEP(2, 171),
        STEP(2, 172),
        STEP(2, 173),
        STEP(2, 174),
    },
    /* hold_d_slow */ {
        STEP(2, 175),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_HOLD_D_SLOW),
    },
    /* lower_d_slow */ {
        STEP(2, 176),
        STEP(2, 177),
        STEP(2, 178),
        STEP(2, 179),
        STEP(2, 180),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_HOLD_D_SLOW),
    },
    /* lower_d_idle_slow */ {
        STEP(2, 182),
        STEP(2, 183),
        STEP(2, 184),
        STEP(2, 185),
        STEP(2, 186),
        STEP(2, 187),
        STEP(2, 188),
        STEP(2, 189),
        STEP(2, 1),
        GOTO(DUAL_MECH_M10_BOSS_ANIM_IDLE),
    },
    /* table */ {
        dual_mech_m10_boss_anims.idle, dual_mech_m10_boss_anims.raise_a, dual_mech_m10_boss_anims.hold_a, dual_mech_m10_boss_anims.lower_a, dual_mech_m10_boss_anims.raise_b, dual_mech_m10_boss_anims.hold_b,
        dual_mech_m10_boss_anims.lower_b, dual_mech_m10_boss_anims.raise_c, dual_mech_m10_boss_anims.hold_c, dual_mech_m10_boss_anims.lower_c, dual_mech_m10_boss_anims.lower_c_end, dual_mech_m10_boss_anims.raise_d,
        dual_mech_m10_boss_anims.hold_d, dual_mech_m10_boss_anims.lower_d, dual_mech_m10_boss_anims.lower_d_end, dual_mech_m10_boss_anims.raise_lower_c_slow, dual_mech_m10_boss_anims.raise_d_slow, dual_mech_m10_boss_anims.hold_d_slow,
        dual_mech_m10_boss_anims.lower_d_slow, dual_mech_m10_boss_anims.lower_d_idle_slow,
    },
};

struct DualMechM10BossScripts {
    s16 spawn_a[10];
    s16 spawn_close_a[12];
    s16 setup_a[14];
    s16 decide_a[18];
    s16 aim_mode_pick_a[4];
    s16 aim_mode_split_a[8];
    s16 aim_mode_direct_a[4];
    s16 aim_mode_low_a[4];
    s16 aim_mode_wide_a[8];
    s16 aim_mode_tight_a[4];
    s16 aim_mode_cluster_a[4];
    s16 aim_mode_sweep_a[8];
    s16 aim_mode_behind_a[4];
    s16 attack_route_a[6];
    s16 attack_pick_high_a[12];
    s16 attack_pick_low_a[12];
    s16 aim_first_setup_a[6];
    s16 aim_first_a[4];
    s16 aim_first_turn_a[10];
    s16 aim_first_check_a[20];
    s16 aim_first_wait_a[2];
    s16 aim_first_loop_a[4];
    s16 aim_second_setup_a[6];
    s16 aim_second_a[4];
    s16 aim_second_turn_a[10];
    s16 aim_second_check_a[10];
    s16 aim_second_wait_a[2];
    s16 aim_second_loop_a[4];
    s16 aim_third_setup_a[6];
    s16 aim_third_a[4];
    s16 aim_third_turn_a[10];
    s16 aim_third_check_a[16];
    s16 aim_third_wait_a[2];
    s16 aim_third_loop_a[4];
    s16 aim_fourth_setup_a[6];
    s16 aim_fourth_a[4];
    s16 aim_fourth_turn_a[10];
    s16 aim_fourth_check_a[10];
    s16 aim_fourth_route_a[6];
    s16 aim_fourth_dash_route_a[6];
    s16 aim_fourth_dash_check_a[6];
    s16 aim_fourth_loop_a[4];
    s16 dash_a[6];
    s16 fire_burst_a[12];
    s16 dash_idle_a[10];
    s16 laser_arm_a[2];
    s16 laser_fire_a[10];
    s16 laser_fire_repeat_a[10];
    s16 laser_fire_alt_a[10];
    s16 laser_end_a[10];
    s16 laser_arm_idle_a[8];
    s16 debris_arm_a[2];
    s16 debris_fire_a[10];
    s16 debris_end_a[10];
    s16 debris_arm_idle_a[8];
    s16 spawn_b[10];
    s16 spawn_close_b[12];
    s16 setup_b[14];
    s16 decide_b[18];
    s16 aim_mode_pick_b[4];
    s16 aim_mode_split_b[8];
    s16 aim_mode_direct_b[4];
    s16 aim_mode_low_b[4];
    s16 aim_mode_wide_b[8];
    s16 aim_mode_tight_b[4];
    s16 aim_mode_cluster_b[4];
    s16 aim_mode_sweep_b[8];
    s16 aim_mode_behind_b[4];
    s16 attack_route_b[6];
    s16 attack_pick_high_b[12];
    s16 attack_pick_low_b[12];
    s16 aim_first_setup_b[6];
    s16 aim_first_b[4];
    s16 aim_first_turn_b[10];
    s16 aim_first_check_b[20];
    s16 aim_first_wait_b[2];
    s16 aim_first_loop_b[4];
    s16 aim_second_setup_b[6];
    s16 aim_second_b[4];
    s16 aim_second_turn_b[10];
    s16 aim_second_check_b[10];
    s16 aim_second_wait_b[2];
    s16 aim_second_loop_b[4];
    s16 aim_third_setup_b[6];
    s16 aim_third_b[4];
    s16 aim_third_turn_b[10];
    s16 aim_third_check_b[20];
    s16 aim_third_wait_b[2];
    s16 aim_third_loop_b[4];
    s16 aim_fourth_setup_b[6];
    s16 aim_fourth_b[4];
    s16 aim_fourth_turn_b[10];
    s16 aim_fourth_check_b[10];
    s16 aim_fourth_route_b[6];
    s16 aim_fourth_dash_route_b[6];
    s16 aim_fourth_dash_check_b[6];
    s16 aim_fourth_loop_b[4];
    s16 dash_b[6];
    s16 fire_burst_b[12];
    s16 dash_idle_b[10];
    s16 rocket_arm_b[2];
    s16 rocket_fire_b[10];
    s16 rocket_fire_repeat_b[10];
    s16 rocket_fire_alt_b[10];
    s16 rocket_end_b[10];
    s16 rocket_arm_idle_b[8];
    s16 dash_settle[6];
    s16 dash_end[2];
    s16 dash_settle_idle_b[10];
    s16 *table[109];
    s16 *dual_mech_script_ids[2];
} dual_mech_m10_boss_scripts = {
    /* spawn_a */ {
        WAIT(60),
        DUAL_MECH_FLAG_SET,
        WAIT(32),
        DUAL_MECH_READ_U16_8, 3072,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* spawn_close_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_SPAWN_CLOSE_A),
        WAIT(4),
        DUAL_MECH_FLAG_CLEAR,
        WAIT(24),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* setup_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_SETUP_A),
        WAIT(8),
        DUAL_MECH_READ_U16_VAR, -256,
        WAIT(32),
        DUAL_MECH_STREAM_READ_S16, 1,
    },
    /* decide_a */ {
        DUAL_MECH_BRANCH_IF_SELECTOR, 0, DUAL_MECH_M10_BOSS_AIM_MODE_LOW_A,
        DUAL_MECH_BRANCH_IF_SELECTOR, 2, DUAL_MECH_M10_BOSS_AIM_MODE_LOW_A,
        DUAL_MECH_BRANCH_IF_SELECTOR, 1, DUAL_MECH_M10_BOSS_AIM_MODE_PICK_A,
        DUAL_MECH_BRANCH_IF_SELECTOR, 3, DUAL_MECH_M10_BOSS_AIM_MODE_PICK_A,
        DUAL_MECH_BRANCH_IF_SELECTOR, 4, DUAL_MECH_M10_BOSS_AIM_MODE_CLUSTER_A,
        DUAL_MECH_BRANCH_IF_SELECTOR, 5, DUAL_MECH_M10_BOSS_AIM_MODE_CLUSTER_A,
    },
    /* aim_mode_pick_a */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_SWEEP_A),
    },
    /* aim_mode_split_a */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_DIRECT_A),
        DUAL_MECH_READ_U16_5, 2,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_A),
    },
    /* aim_mode_direct_a */ {
        DUAL_MECH_READ_U16_5, 0,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_A),
    },
    /* aim_mode_low_a */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_SPLIT_A),
    },
    /* aim_mode_wide_a */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_TIGHT_A),
        DUAL_MECH_READ_U16_5, 4,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_A),
    },
    /* aim_mode_tight_a */ {
        DUAL_MECH_READ_U16_5, 5,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_A),
    },
    /* aim_mode_cluster_a */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_WIDE_A),
    },
    /* aim_mode_sweep_a */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_BEHIND_A),
        DUAL_MECH_READ_U16_5, 3,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_A),
    },
    /* aim_mode_behind_a */ {
        DUAL_MECH_READ_U16_5, 1,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_A),
    },
    /* attack_route_a */ {
        DUAL_MECH_JUMP_IF_PARTNER_KIND, 1, DUAL_MECH_M10_BOSS_AIM_FOURTH_SETUP_A,
        DUAL_MECH_JUMP_IF_BELOW_HEIGHT, DUAL_MECH_M10_BOSS_ATTACK_PICK_LOW_A,
    },
    /* attack_pick_high_a */ {
        JUMP_RANDOM(3072, DUAL_MECH_M10_BOSS_AIM_THIRD_SETUP_A),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FIRST_SETUP_A),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_SECOND_SETUP_A),
        JUMP(DUAL_MECH_M10_BOSS_AIM_FOURTH_SETUP_A),
    },
    /* attack_pick_low_a */ {
        JUMP_RANDOM(3072, DUAL_MECH_M10_BOSS_AIM_SECOND_SETUP_A),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FIRST_SETUP_A),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_THIRD_SETUP_A),
        JUMP(DUAL_MECH_M10_BOSS_AIM_FOURTH_SETUP_A),
    },
    /* aim_first_setup_a */ {
        DUAL_MECH_READ_VALUE, 21,
        SET_COUNTER_RANDOM(4, 4),
    },
    /* aim_first_a */ {
        DUAL_MECH_AIM_AT_PLAYER_MODE,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* aim_first_turn_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_AIM_FIRST_TURN_A),
        WAIT(2),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* aim_first_check_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_AIM_FIRST_CHECK_A),
        DUAL_MECH_JUMP_IF_OUTSIDE_RADIUS, 1536, DUAL_MECH_M10_BOSS_AIM_FIRST_WAIT_A,
        DUAL_MECH_BRANCH_IF_SELECTOR, 1, DUAL_MECH_M10_BOSS_AIM_FIRST_WAIT_A,
        DUAL_MECH_BRANCH_IF_SELECTOR, 3, DUAL_MECH_M10_BOSS_AIM_FIRST_WAIT_A,
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FIRST_WAIT_A),
        JUMP(DUAL_MECH_M10_BOSS_DASH_A),
    },
    /* aim_first_wait_a */ {
        WAIT(8),
    },
    /* aim_first_loop_a */ {
        LOOP(DUAL_MECH_M10_BOSS_AIM_FIRST_A),
        JUMP(DUAL_MECH_M10_BOSS_DECIDE_A),
    },
    /* aim_second_setup_a */ {
        DUAL_MECH_READ_VALUE, 27,
        SET_COUNTER_RANDOM(4, 4),
    },
    /* aim_second_a */ {
        DUAL_MECH_AIM_AT_PLAYER_MODE,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* aim_second_turn_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_AIM_SECOND_TURN_A),
        WAIT(2),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* aim_second_check_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_AIM_SECOND_CHECK_A),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_SECOND_WAIT_A),
        JUMP(DUAL_MECH_M10_BOSS_LASER_ARM_A),
    },
    /* aim_second_wait_a */ {
        WAIT(8),
    },
    /* aim_second_loop_a */ {
        LOOP(DUAL_MECH_M10_BOSS_AIM_SECOND_A),
        JUMP(DUAL_MECH_M10_BOSS_DECIDE_A),
    },
    /* aim_third_setup_a */ {
        DUAL_MECH_READ_VALUE, 33,
        SET_COUNTER_RANDOM(4, 4),
    },
    /* aim_third_a */ {
        DUAL_MECH_AIM_AT_PLAYER_MODE,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* aim_third_turn_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_AIM_THIRD_TURN_A),
        WAIT(2),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* aim_third_check_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_AIM_THIRD_CHECK_A),
        DUAL_MECH_BRANCH_IF_SELECTOR, 1, DUAL_MECH_M10_BOSS_AIM_THIRD_WAIT_A,
        DUAL_MECH_BRANCH_IF_SELECTOR, 3, DUAL_MECH_M10_BOSS_AIM_THIRD_WAIT_A,
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_THIRD_WAIT_A),
        JUMP(DUAL_MECH_M10_BOSS_DEBRIS_ARM_A),
    },
    /* aim_third_wait_a */ {
        WAIT(8),
    },
    /* aim_third_loop_a */ {
        LOOP(DUAL_MECH_M10_BOSS_AIM_THIRD_A),
        JUMP(DUAL_MECH_M10_BOSS_DECIDE_A),
    },
    /* aim_fourth_setup_a */ {
        DUAL_MECH_READ_VALUE, 41,
        SET_COUNTER_RANDOM(4, 4),
    },
    /* aim_fourth_a */ {
        DUAL_MECH_AIM_AT_PLAYER_MODE,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* aim_fourth_turn_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_AIM_FOURTH_TURN_A),
        WAIT(2),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* aim_fourth_check_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_AIM_FOURTH_CHECK_A),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FOURTH_ROUTE_A),
        JUMP(DUAL_MECH_M10_BOSS_LASER_ARM_A),
    },
    /* aim_fourth_route_a */ {
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FOURTH_DASH_ROUTE_A),
        JUMP(DUAL_MECH_M10_BOSS_DEBRIS_ARM_A),
    },
    /* aim_fourth_dash_route_a */ {
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FOURTH_DASH_CHECK_A),
        JUMP(DUAL_MECH_M10_BOSS_DASH_A),
    },
    /* aim_fourth_dash_check_a */ {
        DUAL_MECH_JUMP_IF_PARTNER_KIND, 1, DUAL_MECH_M10_BOSS_DASH_A,
        WAIT(8),
    },
    /* aim_fourth_loop_a */ {
        LOOP(DUAL_MECH_M10_BOSS_AIM_FOURTH_A),
        JUMP(DUAL_MECH_M10_BOSS_DECIDE_A),
    },
    /* dash_a */ {
        DUAL_MECH_READ_U16_VAR, -64,
        WAIT(32),
        NEXT_STATE(DUAL_MECH_STATE_DASH),
    },
    /* fire_burst_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_FIRE_BURST, DUAL_MECH_M10_BOSS_FIRE_BURST_A),
        WAIT(8),
        DUAL_MECH_MUZZLE_EFFECT_SPAWN,
        WAIT(8),
        NEXT_STATE(DUAL_MECH_STATE_BURST_DONE),
    },
    /* dash_idle_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_DASH_IDLE_A),
        DUAL_MECH_READ_U16_VAR, -256,
        JUMP(DUAL_MECH_M10_BOSS_DASH_A),
    },
    /* laser_arm_a */ {
        NEXT_STATE(DUAL_MECH_STATE_LASER_ARM),
    },
    /* laser_fire_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_LASER_FIRE, DUAL_MECH_M10_BOSS_LASER_FIRE_A),
        WAIT(8),
        DUAL_MECH_LASER_FIRE,
        NEXT_STATE(DUAL_MECH_STATE_LASER_PAUSE),
    },
    /* laser_fire_repeat_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_LASER_FIRE, DUAL_MECH_M10_BOSS_LASER_FIRE_REPEAT_A),
        WAIT(8),
        DUAL_MECH_LASER_FIRE,
        NEXT_STATE(DUAL_MECH_STATE_LASER_PAUSE),
    },
    /* laser_fire_alt_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_LASER_FIRE, DUAL_MECH_M10_BOSS_LASER_FIRE_ALT_A),
        WAIT(8),
        DUAL_MECH_LASER_FIRE,
        NEXT_STATE(DUAL_MECH_STATE_LASER_PAUSE),
    },
    /* laser_end_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_LASER_FIRE, DUAL_MECH_M10_BOSS_LASER_END_A),
        WAIT(8),
        NEXT_STATE(DUAL_MECH_STATE_LASER_OFF),
    },
    /* laser_arm_idle_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_LASER_ARM_IDLE_A),
        JUMP(DUAL_MECH_M10_BOSS_LASER_ARM_A),
    },
    /* debris_arm_a */ {
        NEXT_STATE(DUAL_MECH_STATE_DEBRIS_ARM),
    },
    /* debris_fire_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_DEBRIS_FIRE, DUAL_MECH_M10_BOSS_DEBRIS_FIRE_A),
        WAIT(8),
        DUAL_MECH_MUZZLE_DEBRIS_SPAWN,
        NEXT_STATE(DUAL_MECH_STATE_DEBRIS_PAUSE),
    },
    /* debris_end_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_DEBRIS_FIRE, DUAL_MECH_M10_BOSS_DEBRIS_END_A),
        WAIT(8),
        NEXT_STATE(DUAL_MECH_STATE_DEBRIS_OFF),
    },
    /* debris_arm_idle_a */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_DEBRIS_ARM_IDLE_A),
        JUMP(DUAL_MECH_M10_BOSS_DEBRIS_ARM_A),
    },
    /* spawn_b */ {
        WAIT(60),
        DUAL_MECH_FLAG_SET,
        WAIT(32),
        DUAL_MECH_READ_U16_8, 1024,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* spawn_close_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_SPAWN_CLOSE_B),
        WAIT(4),
        DUAL_MECH_FLAG_CLEAR,
        WAIT(24),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* setup_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_SETUP_B),
        WAIT(8),
        DUAL_MECH_READ_U16_VAR, -256,
        WAIT(32),
        DUAL_MECH_STREAM_READ_S16, 1,
    },
    /* decide_b */ {
        DUAL_MECH_BRANCH_IF_SELECTOR, 0, DUAL_MECH_M10_BOSS_AIM_MODE_LOW_B,
        DUAL_MECH_BRANCH_IF_SELECTOR, 2, DUAL_MECH_M10_BOSS_AIM_MODE_LOW_B,
        DUAL_MECH_BRANCH_IF_SELECTOR, 1, DUAL_MECH_M10_BOSS_AIM_MODE_PICK_B,
        DUAL_MECH_BRANCH_IF_SELECTOR, 3, DUAL_MECH_M10_BOSS_AIM_MODE_PICK_B,
        DUAL_MECH_BRANCH_IF_SELECTOR, 4, DUAL_MECH_M10_BOSS_AIM_MODE_CLUSTER_B,
        DUAL_MECH_BRANCH_IF_SELECTOR, 5, DUAL_MECH_M10_BOSS_AIM_MODE_CLUSTER_B,
    },
    /* aim_mode_pick_b */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_SWEEP_B),
    },
    /* aim_mode_split_b */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_DIRECT_B),
        DUAL_MECH_READ_U16_5, 2,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_B),
    },
    /* aim_mode_direct_b */ {
        DUAL_MECH_READ_U16_5, 0,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_B),
    },
    /* aim_mode_low_b */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_SPLIT_B),
    },
    /* aim_mode_wide_b */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_TIGHT_B),
        DUAL_MECH_READ_U16_5, 4,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_B),
    },
    /* aim_mode_tight_b */ {
        DUAL_MECH_READ_U16_5, 5,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_B),
    },
    /* aim_mode_cluster_b */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_WIDE_B),
    },
    /* aim_mode_sweep_b */ {
        JUMP_RANDOM(1024, DUAL_MECH_M10_BOSS_AIM_MODE_BEHIND_B),
        DUAL_MECH_READ_U16_5, 3,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_B),
    },
    /* aim_mode_behind_b */ {
        DUAL_MECH_READ_U16_5, 1,
        JUMP(DUAL_MECH_M10_BOSS_ATTACK_ROUTE_B),
    },
    /* attack_route_b */ {
        DUAL_MECH_JUMP_IF_PARTNER_KIND, 1, DUAL_MECH_M10_BOSS_AIM_FOURTH_SETUP_B,
        DUAL_MECH_JUMP_IF_BELOW_HEIGHT, DUAL_MECH_M10_BOSS_ATTACK_PICK_LOW_B,
    },
    /* attack_pick_high_b */ {
        JUMP_RANDOM(3072, DUAL_MECH_M10_BOSS_AIM_SECOND_SETUP_B),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FIRST_SETUP_B),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_THIRD_SETUP_B),
        JUMP(DUAL_MECH_M10_BOSS_AIM_FOURTH_SETUP_B),
    },
    /* attack_pick_low_b */ {
        JUMP_RANDOM(3072, DUAL_MECH_M10_BOSS_AIM_THIRD_SETUP_B),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FIRST_SETUP_B),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_SECOND_SETUP_B),
        JUMP(DUAL_MECH_M10_BOSS_AIM_FOURTH_SETUP_B),
    },
    /* aim_first_setup_b */ {
        DUAL_MECH_READ_VALUE, 76,
        SET_COUNTER_RANDOM(4, 4),
    },
    /* aim_first_b */ {
        DUAL_MECH_AIM_AT_PLAYER_MODE,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* aim_first_turn_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_AIM_FIRST_TURN_B),
        WAIT(2),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* aim_first_check_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_AIM_FIRST_CHECK_B),
        DUAL_MECH_JUMP_IF_OUTSIDE_RADIUS, 1536, DUAL_MECH_M10_BOSS_AIM_FIRST_WAIT_B,
        DUAL_MECH_BRANCH_IF_SELECTOR, 1, DUAL_MECH_M10_BOSS_AIM_FIRST_WAIT_B,
        DUAL_MECH_BRANCH_IF_SELECTOR, 3, DUAL_MECH_M10_BOSS_AIM_FIRST_WAIT_B,
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FIRST_WAIT_B),
        JUMP(DUAL_MECH_M10_BOSS_DASH_B),
    },
    /* aim_first_wait_b */ {
        WAIT(8),
    },
    /* aim_first_loop_b */ {
        LOOP(DUAL_MECH_M10_BOSS_AIM_FIRST_B),
        JUMP(DUAL_MECH_M10_BOSS_DECIDE_B),
    },
    /* aim_second_setup_b */ {
        DUAL_MECH_READ_VALUE, 82,
        SET_COUNTER_RANDOM(4, 4),
    },
    /* aim_second_b */ {
        DUAL_MECH_AIM_AT_PLAYER_MODE,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* aim_second_turn_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_AIM_SECOND_TURN_B),
        WAIT(2),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* aim_second_check_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_AIM_SECOND_CHECK_B),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_SECOND_WAIT_B),
        JUMP(DUAL_MECH_M10_BOSS_ROCKET_ARM_B),
    },
    /* aim_second_wait_b */ {
        WAIT(8),
    },
    /* aim_second_loop_b */ {
        LOOP(DUAL_MECH_M10_BOSS_AIM_SECOND_B),
        JUMP(DUAL_MECH_M10_BOSS_DECIDE_B),
    },
    /* aim_third_setup_b */ {
        DUAL_MECH_READ_VALUE, 88,
        SET_COUNTER_RANDOM(4, 4),
    },
    /* aim_third_b */ {
        DUAL_MECH_AIM_AT_PLAYER_MODE,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* aim_third_turn_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_AIM_THIRD_TURN_B),
        WAIT(2),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* aim_third_check_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_AIM_THIRD_CHECK_B),
        DUAL_MECH_JUMP_IF_OUTSIDE_RADIUS, 1024, DUAL_MECH_M10_BOSS_AIM_THIRD_WAIT_B,
        DUAL_MECH_BRANCH_IF_SELECTOR, 1, DUAL_MECH_M10_BOSS_AIM_THIRD_WAIT_B,
        DUAL_MECH_BRANCH_IF_SELECTOR, 3, DUAL_MECH_M10_BOSS_AIM_THIRD_WAIT_B,
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_THIRD_WAIT_B),
        JUMP(DUAL_MECH_M10_BOSS_DASH_SETTLE),
    },
    /* aim_third_wait_b */ {
        WAIT(8),
    },
    /* aim_third_loop_b */ {
        LOOP(DUAL_MECH_M10_BOSS_AIM_THIRD_B),
        JUMP(DUAL_MECH_M10_BOSS_DECIDE_B),
    },
    /* aim_fourth_setup_b */ {
        DUAL_MECH_READ_VALUE, 96,
        SET_COUNTER_RANDOM(4, 4),
    },
    /* aim_fourth_b */ {
        DUAL_MECH_AIM_AT_PLAYER_MODE,
        NEXT_STATE(DUAL_MECH_STATE_ADVANCE),
    },
    /* aim_fourth_turn_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_COAST, DUAL_MECH_M10_BOSS_AIM_FOURTH_TURN_B),
        WAIT(2),
        NEXT_STATE(DUAL_MECH_STATE_TURN_TO_PLAYER),
    },
    /* aim_fourth_check_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_AIM_FOURTH_CHECK_B),
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FOURTH_ROUTE_B),
        JUMP(DUAL_MECH_M10_BOSS_ROCKET_ARM_B),
    },
    /* aim_fourth_route_b */ {
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FOURTH_DASH_ROUTE_B),
        JUMP(DUAL_MECH_M10_BOSS_DASH_SETTLE),
    },
    /* aim_fourth_dash_route_b */ {
        JUMP_RANDOM(2048, DUAL_MECH_M10_BOSS_AIM_FOURTH_DASH_CHECK_B),
        JUMP(DUAL_MECH_M10_BOSS_DASH_B),
    },
    /* aim_fourth_dash_check_b */ {
        DUAL_MECH_JUMP_IF_PARTNER_KIND, 1, DUAL_MECH_M10_BOSS_DASH_B,
        WAIT(8),
    },
    /* aim_fourth_loop_b */ {
        LOOP(DUAL_MECH_M10_BOSS_AIM_FOURTH_B),
        JUMP(DUAL_MECH_M10_BOSS_DECIDE_B),
    },
    /* dash_b */ {
        DUAL_MECH_READ_U16_VAR, -64,
        WAIT(32),
        NEXT_STATE(DUAL_MECH_STATE_DASH),
    },
    /* fire_burst_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_FIRE_BURST, DUAL_MECH_M10_BOSS_FIRE_BURST_B),
        WAIT(8),
        DUAL_MECH_MUZZLE_EFFECT_SPAWN,
        WAIT(8),
        NEXT_STATE(DUAL_MECH_STATE_BURST_DONE),
    },
    /* dash_idle_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_DASH_IDLE_B),
        DUAL_MECH_READ_U16_VAR, -256,
        JUMP(DUAL_MECH_M10_BOSS_DASH_B),
    },
    /* rocket_arm_b */ {
        NEXT_STATE(DUAL_MECH_STATE_ROCKET_ARM),
    },
    /* rocket_fire_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_ROCKET_FIRE, DUAL_MECH_M10_BOSS_ROCKET_FIRE_B),
        WAIT(8),
        DUAL_MECH_ROCKET_FIRE,
        NEXT_STATE(DUAL_MECH_STATE_ROCKET_PAUSE),
    },
    /* rocket_fire_repeat_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_ROCKET_FIRE, DUAL_MECH_M10_BOSS_ROCKET_FIRE_REPEAT_B),
        WAIT(8),
        DUAL_MECH_ROCKET_FIRE,
        NEXT_STATE(DUAL_MECH_STATE_ROCKET_PAUSE),
    },
    /* rocket_fire_alt_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_ROCKET_FIRE, DUAL_MECH_M10_BOSS_ROCKET_FIRE_ALT_B),
        WAIT(8),
        DUAL_MECH_ROCKET_FIRE,
        NEXT_STATE(DUAL_MECH_STATE_ROCKET_PAUSE),
    },
    /* rocket_end_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_ROCKET_FIRE, DUAL_MECH_M10_BOSS_ROCKET_END_B),
        WAIT(8),
        NEXT_STATE(DUAL_MECH_STATE_ROCKET_OFF),
    },
    /* rocket_arm_idle_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_ROCKET_ARM_IDLE_B),
        JUMP(DUAL_MECH_M10_BOSS_ROCKET_ARM_B),
    },
    /* dash_settle */ {
        DUAL_MECH_JUMP_IF_BELOW_HEIGHT, DUAL_MECH_M10_BOSS_DASH_END,
        DUAL_MECH_READ_U16_VAR, -64,
        WAIT(32),
    },
    /* dash_end */ {
        NEXT_STATE(DUAL_MECH_STATE_DASH_LAND),
    },
    /* dash_settle_idle_b */ {
        WAIT(1),
        JUMP_UNLESS_STATE(DUAL_MECH_STATE_IDLE, DUAL_MECH_M10_BOSS_DASH_SETTLE_IDLE_B),
        DUAL_MECH_READ_U16_VAR, -256,
        JUMP(DUAL_MECH_M10_BOSS_DASH_SETTLE),
    },
    /* table */ {
        dual_mech_m10_boss_scripts.spawn_a, dual_mech_m10_boss_scripts.spawn_close_a, dual_mech_m10_boss_scripts.setup_a, dual_mech_m10_boss_scripts.decide_a, dual_mech_m10_boss_scripts.aim_mode_pick_a, dual_mech_m10_boss_scripts.aim_mode_split_a,
        dual_mech_m10_boss_scripts.aim_mode_direct_a, dual_mech_m10_boss_scripts.aim_mode_low_a, dual_mech_m10_boss_scripts.aim_mode_wide_a, dual_mech_m10_boss_scripts.aim_mode_tight_a, dual_mech_m10_boss_scripts.aim_mode_cluster_a, dual_mech_m10_boss_scripts.aim_mode_sweep_a,
        dual_mech_m10_boss_scripts.aim_mode_behind_a, dual_mech_m10_boss_scripts.attack_route_a, dual_mech_m10_boss_scripts.attack_pick_high_a, dual_mech_m10_boss_scripts.attack_pick_low_a, dual_mech_m10_boss_scripts.aim_first_setup_a, dual_mech_m10_boss_scripts.aim_first_a,
        dual_mech_m10_boss_scripts.aim_first_turn_a, dual_mech_m10_boss_scripts.aim_first_check_a, dual_mech_m10_boss_scripts.aim_first_wait_a, dual_mech_m10_boss_scripts.aim_first_loop_a, dual_mech_m10_boss_scripts.aim_second_setup_a, dual_mech_m10_boss_scripts.aim_second_a,
        dual_mech_m10_boss_scripts.aim_second_turn_a, dual_mech_m10_boss_scripts.aim_second_check_a, dual_mech_m10_boss_scripts.aim_second_wait_a, dual_mech_m10_boss_scripts.aim_second_loop_a, dual_mech_m10_boss_scripts.aim_third_setup_a, dual_mech_m10_boss_scripts.aim_third_a,
        dual_mech_m10_boss_scripts.aim_third_turn_a, dual_mech_m10_boss_scripts.aim_third_check_a, dual_mech_m10_boss_scripts.aim_third_wait_a, dual_mech_m10_boss_scripts.aim_third_loop_a, dual_mech_m10_boss_scripts.aim_fourth_setup_a, dual_mech_m10_boss_scripts.aim_fourth_a,
        dual_mech_m10_boss_scripts.aim_fourth_turn_a, dual_mech_m10_boss_scripts.aim_fourth_check_a, dual_mech_m10_boss_scripts.aim_fourth_route_a, dual_mech_m10_boss_scripts.aim_fourth_dash_route_a, dual_mech_m10_boss_scripts.aim_fourth_dash_check_a, dual_mech_m10_boss_scripts.aim_fourth_loop_a,
        dual_mech_m10_boss_scripts.dash_a, dual_mech_m10_boss_scripts.fire_burst_a, dual_mech_m10_boss_scripts.dash_idle_a, dual_mech_m10_boss_scripts.laser_arm_a, dual_mech_m10_boss_scripts.laser_fire_a, dual_mech_m10_boss_scripts.laser_fire_repeat_a,
        dual_mech_m10_boss_scripts.laser_fire_alt_a, dual_mech_m10_boss_scripts.laser_end_a, dual_mech_m10_boss_scripts.laser_arm_idle_a, dual_mech_m10_boss_scripts.debris_arm_a, dual_mech_m10_boss_scripts.debris_fire_a, dual_mech_m10_boss_scripts.debris_end_a,
        dual_mech_m10_boss_scripts.debris_arm_idle_a, dual_mech_m10_boss_scripts.spawn_b, dual_mech_m10_boss_scripts.spawn_close_b, dual_mech_m10_boss_scripts.setup_b, dual_mech_m10_boss_scripts.decide_b, dual_mech_m10_boss_scripts.aim_mode_pick_b,
        dual_mech_m10_boss_scripts.aim_mode_split_b, dual_mech_m10_boss_scripts.aim_mode_direct_b, dual_mech_m10_boss_scripts.aim_mode_low_b, dual_mech_m10_boss_scripts.aim_mode_wide_b, dual_mech_m10_boss_scripts.aim_mode_tight_b, dual_mech_m10_boss_scripts.aim_mode_cluster_b,
        dual_mech_m10_boss_scripts.aim_mode_sweep_b, dual_mech_m10_boss_scripts.aim_mode_behind_b, dual_mech_m10_boss_scripts.attack_route_b, dual_mech_m10_boss_scripts.attack_pick_high_b, dual_mech_m10_boss_scripts.attack_pick_low_b, dual_mech_m10_boss_scripts.aim_first_setup_b,
        dual_mech_m10_boss_scripts.aim_first_b, dual_mech_m10_boss_scripts.aim_first_turn_b, dual_mech_m10_boss_scripts.aim_first_check_b, dual_mech_m10_boss_scripts.aim_first_wait_b, dual_mech_m10_boss_scripts.aim_first_loop_b, dual_mech_m10_boss_scripts.aim_second_setup_b,
        dual_mech_m10_boss_scripts.aim_second_b, dual_mech_m10_boss_scripts.aim_second_turn_b, dual_mech_m10_boss_scripts.aim_second_check_b, dual_mech_m10_boss_scripts.aim_second_wait_b, dual_mech_m10_boss_scripts.aim_second_loop_b, dual_mech_m10_boss_scripts.aim_third_setup_b,
        dual_mech_m10_boss_scripts.aim_third_b, dual_mech_m10_boss_scripts.aim_third_turn_b, dual_mech_m10_boss_scripts.aim_third_check_b, dual_mech_m10_boss_scripts.aim_third_wait_b, dual_mech_m10_boss_scripts.aim_third_loop_b, dual_mech_m10_boss_scripts.aim_fourth_setup_b,
        dual_mech_m10_boss_scripts.aim_fourth_b, dual_mech_m10_boss_scripts.aim_fourth_turn_b, dual_mech_m10_boss_scripts.aim_fourth_check_b, dual_mech_m10_boss_scripts.aim_fourth_route_b, dual_mech_m10_boss_scripts.aim_fourth_dash_route_b, dual_mech_m10_boss_scripts.aim_fourth_dash_check_b,
        dual_mech_m10_boss_scripts.aim_fourth_loop_b, dual_mech_m10_boss_scripts.dash_b, dual_mech_m10_boss_scripts.fire_burst_b, dual_mech_m10_boss_scripts.dash_idle_b, dual_mech_m10_boss_scripts.rocket_arm_b, dual_mech_m10_boss_scripts.rocket_fire_b,
        dual_mech_m10_boss_scripts.rocket_fire_repeat_b, dual_mech_m10_boss_scripts.rocket_fire_alt_b, dual_mech_m10_boss_scripts.rocket_end_b, dual_mech_m10_boss_scripts.rocket_arm_idle_b, dual_mech_m10_boss_scripts.dash_settle, dual_mech_m10_boss_scripts.dash_end,
        dual_mech_m10_boss_scripts.dash_settle_idle_b,
    },
    /* dual_mech_script_ids */ {
        dual_mech_m10_boss_scripts.spawn_a, dual_mech_m10_boss_scripts.spawn_b,
    },
};

ScriptCallEntry dual_mech_table_a[17] = {
    {NULL, 0},
    {muzzle_effect_spawn, 0},
    {rocket_fire, 0},
    {laser_fire, 0},
    {muzzle_debris_spawn, 0},
    {obj_cmd_read_u16, 0},
    {cmd_branch_if_selector, 0},
    {obj_aim_at_player_mode, 0},
    {cmd_read_u16, 0},
    {obj_script_read_value, 0},
    {script_jump_if_partner_kind, 0},
    {script_jump_if_below_height, 0},
    {script_jump_if_outside_radius, 0},
    {obj_flag_set, 0},
    {obj_flag_clear, 0},
    {obj_script_read_u16_var, 0},
    {stream_read_s16, 0},
};

StateEntry dual_mech_table_b[24] = {
    {0, DUAL_MECH_M10_BOSS_ANIM_IDLE, 0},
    {(u32)func_800C2D5C, DUAL_MECH_M10_BOSS_ANIM_RAISE_A, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_HOLD_A, 0},
    {(u32)obj_turn_to_target, DUAL_MECH_M10_BOSS_ANIM_LOWER_A, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_RAISE_B, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_HOLD_B, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_LOWER_B, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_RAISE_C, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_HOLD_C, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_LOWER_C, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_LOWER_C_END, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_RAISE_D, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_HOLD_D, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_LOWER_D, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_LOWER_D_END, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_RAISE_LOWER_C_SLOW, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_RAISE_D_SLOW, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_HOLD_D_SLOW, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_LOWER_D_SLOW, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_LOWER_D_IDLE_SLOW, 0},
    {0, DUAL_MECH_M10_BOSS_ANIM_IDLE, 0},
    {0x30303000, DUAL_MECH_M10_BOSS_ANIM_IDLE, 128},
    {0x00040000, DUAL_MECH_M10_BOSS_ANIM_IDLE, 1},
    {0, -32768, 0},
};

s32 turn_frame_offsets[4] = {
    0, 0x3C, 0x14, 0x28,
};

s16 target_blend_table_a[30][4] = {
    {0x50, -0x9E, 0xA0, 0}, {0x55, -0xA3, 0x9E, 0}, {0x63, -0xB1, 0x97, 0}, {0x75, -0xC2, 0x8A, 0},
    {0x87, -0xD4, 0x78, 0}, {0x94, -0xE3, 0x65, 0}, {0x9E, -0xED, 0x54, 0}, {0xA5, -0xF2, 0x45, 0},
    {0xAA, -0xF5, 0x3A, 0}, {0xAB, -0xF8, 0x38, 0}, {0xA4, -0xFB, 0x44, 0}, {0x8F, -0xFE, 0x62, 0},
    {0x5A, -0xFB, 0x8E, 0}, {8, -0xE2, 0xAB, 0}, {-0x44, -0xB3, 0xA1, 0}, {-0x6E, -0x89, 0x80, 0},
    {-0x79, -0x76, 0x6C, 0}, {-0x77, -0x73, 0x6A, 0}, {-0x73, -0x72, 0x6F, 0}, {-0x6B, -0x74, 0x78, 0},
    {-0x5F, -0x78, 0x84, 0}, {-0x4E, -0x7E, 0x91, 0}, {-0x39, -0x85, 0x9D, 0}, {-0x20, -0x8C, 0xA7, 0},
    {-6, -0x92, 0xAC, 0}, {0x15, -0x97, 0xAD, 0}, {0x2C, -0x9A, 0xAA, 0}, {0x3F, -0x9C, 0xA6, 0},
    {0x4B, -0x9D, 0xA2, 0}, {0x50, -0x9E, 0xA0, 0},
};

s16 target_blend_table_b[30][4] = {
    {0x57, -0xA8, 0x95, 0}, {0x5C, -0xAD, 0x92, 0}, {0x69, -0xBA, 0x8A, 0}, {0x79, -0xCA, 0x7B, 0},
    {0x88, -0xDA, 0x68, 0}, {0x93, -0xE7, 0x55, 0}, {0x9B, -0xF0, 0x43, 0}, {0xA1, -0xF5, 0x34, 0},
    {0xA4, -0xF7, 0x2A, 0}, {0xA5, -0xFA, 0x28, 0}, {0xA0, -0xFD, 0x33, 0}, {0x8E, -0x100, 0x50, 0},
    {0x5F, -0xFF, 0x7D, 0}, {0x12, -0xE9, 0x9F, 0}, {-0x37, -0xBD, 0x9F, 0}, {-0x62, -0x94, 0x85, 0},
    {-0x6E, -0x81, 0x74, 0}, {-0x6D, -0x7E, 0x73, 0}, {-0x68, -0x7E, 0x77, 0}, {-0x5F, -0x80, 0x7F, 0},
    {-0x53, -0x84, 0x89, 0}, {-0x41, -0x8A, 0x94, 0}, {-0x2C, -0x91, 0x9E, 0}, {-0x14, -0x97, 0xA4, 0},
    {7, -0x9D, 0xA7, 0}, {0x20, -0xA2, 0xA6, 0}, {0x36, -0xA5, 0xA1, 0}, {0x48, -0xA7, 0x9B, 0},
    {0x53, -0xA8, 0x97, 0}, {0x57, -0xA8, 0x95, 0},
};

s16 target_blend_table_c[30][4] = {
    {0x57, -0xA8, 0x4A, 0}, {0x5A, -0xAB, 0x48, 0}, {0x60, -0xB1, 0x40, 0}, {0x67, -0xB9, 0x35, 0},
    {0x6D, -0xC1, 0x27, 0}, {0x72, -0xC7, 0x1B, 0}, {0x74, -0xCB, 0x10, 0}, {0x76, -0xCD, 6, 0},
    {0x77, -0xCE, 0, 0}, {0x77, -0xCF, -1, 0}, {0x76, -0xD1, 7, 0}, {0x6F, -0xD5, 0x1C, 0},
    {0x5A, -0xD7, 0x3E, 0}, {0x31, -0xD0, 0x60, 0}, {3, -0xB9, 0x70, 0}, {-0x1C, -0x9F, 0x6E, 0},
    {-0x27, -0x92, 0x69, 0}, {-0x26, -0x90, 0x68, 0}, {-0x22, -0x90, 0x69, 0}, {-0x1A, -0x92, 0x6B, 0},
    {-0x10, -0x95, 0x6D, 0}, {-3, -0x99, 0x6E, 0}, {11, -0x9D, 0x6E, 0}, {0x1B, -0xA1, 0x6B, 0},
    {0x2B, -0xA4, 0x67, 0}, {0x3A, -0xA6, 0x60, 0}, {0x46, -0xA7, 0x59, 0}, {0x50, -0xA8, 0x52, 0},
    {0x55, -0xA8, 0x4C, 0}, {0x57, -0xA8, 0x4A, 0},
};

RecTemplate rocket_blast_templates[2] = {
    {1, 0x7F, 0, 0, 0, 0x2A, 0x18000, 0x18000, -0x1000, 0x4000},
    {1, 0xFF, 0x7F, 0, 0, 0x2A, 0xC000, 0x16000, -0x1000, 0x4000},
};

FxRecordParams D_8011D3E8 = {1, 0x5F, 0xBF, 0xFF, 0, 0x80, {0x18000, 0x28000, -0x1000, 0x18000}};

#include "../stage/data/effect_template.c"

#include "../stage/data/effect_callback_table.c"

RecTemplate fx_owner_template_a = {3, 0xFF, 0xFF, 0xFF, 0, 0x14, 0x80000, 0x60000, -0x100, 0x40000};

#include "../stage/data/fx_owner_template_b.c"

#include "../stage/data/fx_rec34_params.c"

#include "../stage/data/obj_fx_template_a.c"

#include "../stage/data/obj_fx_template_b.c"

#include "../stage/data/d_8011ACDC.c"

void (*obj_init_table[4])(Object *) = {
    NULL, func_800C903C, func_800C929C, func_800C92D0,
};

ObjPhaseEntry obj_phase0_table[4] = {
    {NULL, {NULL, NULL, NULL}},
    {door_update, {fn_800B789C, NULL, obj_spark_triple}},
    {door_phase0, {fn_800B789C, NULL, door_draw}},
    {door_phase0, {fn_800B789C, NULL, door_draw}},
};

s32 D_8011D508[3] = {
    -1, -1, -1,
};

ScanEntry enemy_ctba_entry = {{(s32)spark_reset, (s32)obj_spawn_placement}, D_8011D508, 0, 0, 0};

s16 spark_level_offsets[3] = {
    0x82, 0x83, 0x81,
};

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

u8 *D_8011D5A4[3] = {
    str_msgs_spr_clt, str_msgs_spr_grc, str_msgs_spr_so3,
};

ScanEntry enemy_msgs_scan_entry = {{(s32)mission_state_reset, 0}, d_80117914, 0, 0, (s32)D_8011D5A4};

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

s16 video_mode_id = 0;

#include "../stage/data/debug_cam_speed_table.c"

#include "../stage/data/pause_prev_work_area.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_80122168[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/tint_scale_r.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_801232CC[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_801238EC = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

s32 door_light_base = 0;

s32 elevator_cam_slot = 0;

s32 elevator_inside_flag = 0;

s32 elevator_nudge_phase = 0;

s32 spark_base = 0;

u8 door_state_table[4] = {
    0x00, 0x00, 0x00, 0x00,
};

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

#include "../stage/data/frame_work_area.c"

#include "../stage/data/model_slot_count.c"

u32 D_80124E14 = 0x00000000;

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

u32 D_80124EB0 = 0x00000000;

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

