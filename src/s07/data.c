/* s07 data 0x8011C240-0x80126000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s07_types.h"
#include "script.h"
#include "scripts.h"
#include "sounds.h"

extern void bomb_mech_m7_boss_spawn();
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
extern void enemy_fire_shot_step();
extern void enemy_fly_attack();
extern void enemy_fly_step();
extern void enemy_handler_done();
extern void enemy_retarget_jitter();
extern void enemy_rocket_aim_step();
extern u8 file_arkb_ch0_cb4[];
extern u8 file_arkb_ch0_clt[];
extern u8 file_arkb_ch0_vx1[];
extern u8 file_arkb_tp0_clt[];
extern u8 file_arkb_tp0_xs3[];
extern u8 file_fap2_ch0_cb4[];
extern u8 file_fap2_ch0_clt[];
extern u8 file_fap2_ch0_vx1[];
extern u8 file_fap2_tp0_clt[];
extern u8 file_fap2_tp0_xs3[];
extern u8 file_fap2_tp1_clt[];
extern u8 file_fap2_tp1_xs3[];
extern u8 file_horo_ch0_cb4[];
extern u8 file_horo_ch0_clt[];
extern u8 file_horo_ch0_vx1[];
extern u8 file_horo_tp0_clt[];
extern u8 file_horo_tp0_xs3[];
extern u8 file_kitt_ch0_cb4[];
extern u8 file_kitt_ch0_clt[];
extern u8 file_kitt_ch0_vx1[];
extern u8 file_kitt_tp0_clt[];
extern u8 file_kitt_tp0_xs3[];
extern u8 file_tnk2_ch0_cb4[];
extern u8 file_tnk2_ch0_clt[];
extern u8 file_tnk2_ch0_vx1[];
extern u8 file_tnk2_tp0_clt[];
extern u8 file_tnk2_tp0_xs3[];
extern void fly_emitter_update();
extern void flyer_bank_turn();
extern void flyer_hover_update();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void fn_s07_800BAE10();
extern void fuchikoma_chase_update();
extern void grenade_fuchikoma_spawn();
extern void gun_turret_2_spawn();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void heli_fire_bombs();
extern void helicopter2_spawn();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void mission_state_reset();
extern void mode_keyframe_enable();
extern void mode_reset();
extern u8 model_base_slot[];
extern void model_store_pchr();
extern u8 msgs_spr_clt_name[];
extern u8 msgs_spr_grc_name[];
extern u8 msgs_spr_so3_name[];
extern void obj_aim_jittered();
extern void obj_area_update();
extern void obj_call_hook();
extern void obj_countdown_step();
extern void obj_decelerate_move();
extern void obj_disable();
extern void obj_enable();
extern void obj_face_player();
extern void obj_face_target_update();
extern void obj_fall_update();
extern void obj_finish_step();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_jitter_update();
extern void obj_jump_if_player_near();
extern void obj_keytrack_start();
extern void obj_nop();
extern void obj_ramp_dispatch();
extern void obj_read_s32();
extern void obj_release_check();
extern void obj_retarget();
extern void obj_roll_set();
extern void obj_script_jump_if_key();
extern void obj_script_jump_within();
extern void obj_script_read_jump();
extern void obj_script_read_s32();
extern void obj_script_read_speed();
extern void obj_set_next_state();
extern void obj_settle_offset();
extern void obj_sound_start_a();
extern void obj_sound_start_b();
extern void obj_sound_stop_b();
extern void obj_spawn_muzzle_flash();
extern void obj_speed_approach();
extern void obj_start_positional_sound();
extern void obj_state_dispatch();
extern void obj_stop_held_sound();
extern void obj_turn_sound_update();
extern void obj_turn_step();
extern void params_reset();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void ramp_start_script();
extern void scene_spawn();
extern void script_branch_if_flag();
extern void script_branch_if_repeat();
extern void script_branch_if_roll();
extern void script_branch_on_flag();
extern void script_case_match();
extern void script_clear_model_parts();
extern void script_jump_if_beyond_radius();
extern void script_jump_if_facing_player_in_radius();
extern void script_jump_if_flag_set();
extern void script_jump_if_mode();
extern void script_jump_if_near_player_in_view();
extern void script_jump_if_not_below_speed();
extern void script_jump_if_player_below();
extern void script_jump_if_player_far();
extern void script_jump_if_player_in_radius();
extern void script_jump_if_player_in_view();
extern void script_jump_if_within_range();
extern void script_jump_near();
extern void script_jump_near_corner();
extern void script_jump_near_player();
extern void script_jump_table();
extern void script_jump_table_cond();
extern void script_loop_next();
extern void script_loop_set_count();
extern void script_op_aim_and_track();
extern void script_op_jump_if_flag_1b7();
extern void script_op_jump_if_flag_in_range();
extern void script_op_jump_if_in_cell_corner();
extern void script_op_jump_if_in_range();
extern void script_op_jump_if_near_target();
extern void script_op_jump_if_outside_bounds();
extern void script_op_jump_if_player_beyond();
extern void script_op_jump_if_player_close();
extern void script_op_jump_if_player_far();
extern void script_op_jump_if_player_in_cone();
extern void script_op_jump_if_player_in_range();
extern void script_op_jump_if_player_near();
extern void script_op_jump_if_player_within();
extern void script_op_jump_if_vy_nonneg();
extern void script_op_jump_if_within_dist();
extern void script_op_jump_table_if_player_far();
extern void script_op_set_enemy_sound();
extern void script_op_set_mode();
extern void script_op_set_speed();
extern void script_op_set_unk_234();
extern void script_op_set_vy();
extern void script_op_skip_halfword();
extern void script_player_angle_branch();
extern void script_read_long();
extern void script_read_s32();
extern void script_read_speed_long();
extern void script_read_walk_state();
extern void script_set_enemy_var();
extern void script_set_patrol_phase();
extern void script_set_target_yaw();
extern void script_set_turn_mode();
extern void script_shoot_at_player();
extern void script_spawn_model_parts();
extern void script_store_enemy_halfword();
extern void script_timer_reverse();
extern void script_turn_to_player_jump();
extern void script_value_queue_push();
extern void stationary_rocket_launcher_init();
extern void stationary_rocket_launcher_spawn();
extern u8 str_bos7_ch0_clt[];
extern u8 str_bos7_ch0_vx1[];
extern u8 str_bos7_ch0cb4[];
extern u8 str_bos7_ch1_vx1[];
extern u8 str_bos7_ch1cb4[];
extern u8 str_bos7_ch2_vx1[];
extern u8 str_bos7_tp0_clt[];
extern u8 str_bos7_tp0_xs3[];
extern u8 str_bos7_tp1_clt[];
extern u8 str_bos7_tp1_xs3[];
extern u8 str_com_dat_fac[];
extern u8 str_cty_apdea3[];
extern u8 str_cty_cnf_bcf[];
extern u8 str_cty_joy_bin[];
extern u8 str_enemy_arkb_data[];
extern u8 str_enemy_bos7_data[];
extern u8 str_enemy_ctl7_data[];
extern u8 str_enemy_fap2_data[];
extern u8 str_enemy_horo_data[];
extern u8 str_enemy_hou2_data[];
extern u8 str_enemy_kitt_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_mth2_data[];
extern u8 str_enemy_nk2_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_hou2_ch0_clt[];
extern u8 str_hou2_ch0_vx1[];
extern u8 str_hou2_ch0cb4[];
extern u8 str_hou2_tp0_clt[];
extern u8 str_hou2_tp0_xs3[];
extern u8 str_m07_dat_fac[];
extern u8 str_m31_cnf_bcf[];
extern u8 str_m31_joy_bin[];
extern u8 str_main_data[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_mth2_ch0_clt[];
extern u8 str_mth2_ch0_vx1[];
extern u8 str_mth2_ch0cb4[];
extern u8 str_mth2_tp0_clt[];
extern u8 str_mth2_tp0_xs3[];
extern u8 str_s07_boss[];
extern u8 str_s07_dat_fac[];
extern u8 str_s07_ene_fac[];
extern u8 str_s07_miss[];
extern u8 str_s07_stage[];
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
extern void tank_spawn();
extern u8 text_packets[];
extern void text_slot_setup();
extern void track_set_enabled();
extern void track_setup();
extern void turret_branch_if_aimed();
extern void turret_track_player();
extern void value_queue_pop();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern void walker_mech_attack();
extern void walker_mech_patrol();
extern void walker_mech_spawn();
extern u8 D_8011CA9D[];
extern u8 D_8011CA9E[];
extern u8 D_8011CA9F[];
extern u8 D_8011CAA4[];
extern u8 D_8011E0D0[];
extern u8 D_8011E0D4[];
extern u8 D_80125FD0[];
extern u8 D_80125FDC[];
extern u8 D_80125FDE[];
extern u8 D_80125FE0[];
extern u8 D_80125FE2[];
extern u8 D_80125FE4[];
extern u8 D_80125FE6[];
extern u8 D_80125FE8[];
extern u8 D_80125FEA[];
extern u8 D_80125FEC[];
extern u8 D_80125FEE[];
extern u8 area_sound_first_id[];
extern u8 cos_table[];
extern u8 d_80118574[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 d_801201AE[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 fade_target_vy[];
extern u8 fade_target_vz[];
extern u8 flow_angle[];
extern u8 fuchikoma_state_table_s12[];
extern u8 grenade_saved_param[];
extern u8 gun_hit_effect_table[];
extern u8 pad1_pressed[];
extern u8 scale_vec_y[];
extern u8 shot_hit_effect_index[];
extern u8 shot_speed_delta[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 texture_image_height[];
extern u8 view_nudge_y[];
extern u8 view_sincos[];
extern u8 walker_death_scripts_alt[];
extern s32 area;
extern ScanItem enemy_load_items[];
extern AreaEntry D_8011C29C;
extern AreaEntry D_8011C2C4;
extern u32 D_8011C2EC[];
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern s32 rocket_launcher_asset[];
extern ModelBlockRef rocket_launcher_clt_refs[];
extern ModelBlockRef rocket_launcher_xs3_refs[];
extern ModelBlockRef rocket_launcher_vx1_refs[];
extern ModelBlock rocket_launcher_model;
extern u8 *rocket_launcher_cb4_refs[];
extern ScanEntry stationary_rocket_launcher_entry;
extern u32 D_8011C470[];
extern s16 stationary_rocket_launcher_anim_idle[];
extern s16 *stationary_rocket_launcher_data;
extern s16 stationary_rocket_launcher_idle[];
extern s16 stationary_rocket_launcher_track[];
extern s16 stationary_rocket_launcher_aim[];
extern s16 stationary_rocket_launcher_lock_on[];
extern s16 stationary_rocket_launcher_fire_start[];
extern s16 stationary_rocket_launcher_fire_loop[];
extern s16 stationary_rocket_launcher_launch_start[];
extern s16 stationary_rocket_launcher_launch_loop[];
extern s16 *rocket_launcher_script[];
extern s16 *rocket_launcher_anim_link;
extern ScriptCallEntry D_8011C508[];
extern StateEntry D_8011C520[];
extern RecTemplate rocket_explode_fx_template;
extern RecTemplate D_8011C558;
extern s32 fuchikoma_asset[];
extern ModelBlockRef arkb_palettes[];
extern ModelBlockRef arkb_textures[];
extern ModelBlockRef arkb_models[];
extern ModelBlockRange d_8011C5B4[];
extern ModelBlock arkb_model_block;
extern u8 *enemy_fuchikoma_b_cb4_refs[];
extern ScanEntry arkb_scan_entry;
extern u32 d_8011C610[];
extern s16 enemy_fuchikoma_b_anim_idle[];
extern s16 enemy_fuchikoma_b_anim_walk[];
extern s16 *enemy_fuchikoma_b_data[];
extern s16 enemy_fuchikoma_b_idle[];
extern s16 enemy_fuchikoma_b_start[];
extern s16 enemy_fuchikoma_b_accelerate[];
extern s16 enemy_fuchikoma_b_wait_trigger[];
extern s16 enemy_fuchikoma_b_chase_start[];
extern s16 enemy_fuchikoma_b_search[];
extern s16 enemy_fuchikoma_b_engage[];
extern s16 enemy_fuchikoma_b_aim[];
extern s16 enemy_fuchikoma_b_corner_check[];
extern s16 enemy_fuchikoma_b_corner_turn[];
extern s16 enemy_fuchikoma_b_await_mode[];
extern s16 enemy_fuchikoma_b_death_wait[];
extern s16 enemy_fuchikoma_b_death[];
extern s16 enemy_fuchikoma_b_await_chase[];
extern s16 *fuchikoma_link_data[];
extern s16 *fuchikoma_anim_link;
extern ScriptCallEntry fuchikoma_call_table[];
extern s16 muzzle_side_table[];
extern StateEntry fuchikoma_state_table[];
extern s16 shot_muzzle_x_table[];
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
extern u32 helicopter2_asset[];
extern GunSetup flyer_shot_setup;
extern ModelBlockRef helicopter2_palettes[];
extern ModelBlockRef helicopter2_textures[];
extern ModelBlockRef helicopter2_models[];
extern ModelBlock helicopter2_model_block;
extern u8 *helicopter2_stage_files[];
extern ScanEntry helicopter2_scan_entry;
extern s16 helicopter_2_script_cfg[4];
extern s16 *helicopter_2_data[];
extern FxRecordParams ground_shadow_params;
extern FxRecordParams fx_rec34_params_a;
extern FxRecordParams fx_rec34_params_b;
extern s16 helicopter2_think[];
extern s16 helicopter2_select[];
extern s16 helicopter2_patrol[];
extern s16 helicopter2_cruise[];
extern s16 helicopter2_bank_turn[];
extern s16 helicopter2_attack[];
extern s16 helicopter2_hover[];
extern s16 helicopter2_hold_start[];
extern s16 helicopter2_hold_loop[];
extern s16 helicopter2_cycle_end[];
extern s16 *helicopter2_script_data[];
extern s16 *helicopter2_script_entry;
extern ScriptCallEntry helicopter2_script_calls[6];
extern StateEntry helicopter2_states[4];
extern s32 tank2_asset[3];
extern ModelBlockRef d_8011CBFC[];
extern ModelBlockRef d_8011CC14[];
extern ModelBlockRef tank2_models[];
extern ModelBlock tank_model_block;
extern u8 *d_8011CC58[];
extern ScanEntry tank_scan_entry;
extern s16 tank_2_anim_idle[];
extern s16 *tank_2_data[];
extern s16 tank_2_init[];
extern s16 tank_2_patrol_start[];
extern s16 tank_2_patrol[];
extern s16 tank_2_stop[];
extern s16 tank_2_stop_wait[];
extern s16 tank_2_spotted[];
extern s16 tank_2_chase[];
extern s16 tank_2_engage[];
extern s16 tank_2_aim[];
extern s16 tank_2_turn_to_player[];
extern s16 tank_2_turn_wait[];
extern s16 tank_2_face_wait[];
extern s16 tank_2_halt[];
extern s16 tank_2_fire_ready[];
extern s16 tank_2_fire_start[];
extern s16 tank_2_fire_loop[];
extern s16 tank_2_fire_cooldown[];
extern s16 tank_2_static_init[];
extern s16 tank_2_static_watch[];
extern s16 tank_2_static_spotted[];
extern s16 tank_2_static_chase[];
extern s16 tank_2_static_engage[];
extern s16 tank_2_static_aim[];
extern s16 tank_2_static_turn_to_player[];
extern s16 tank_2_static_turn_wait[];
extern s16 tank_2_static_face_wait[];
extern s16 tank_2_static_fire_start[];
extern s16 tank_2_static_fire_loop[];
extern s16 tank_2_static_fire_cooldown[];
extern s16 tank_2_pursue_watch[];
extern s16 tank_2_pursue_spotted[];
extern s16 tank_2_pursue_chase[];
extern s16 tank_2_pursue_angle_check[];
extern s16 tank_2_pursue_turn_to_player[];
extern s16 tank_2_pursue_turn_wait[];
extern s16 tank_2_pursue_face_wait[];
extern s16 *tank2_link_data[];
extern s16 *tank2_variant_words[];
extern ScriptCallEntry d_8011CF34[];
extern StateEntry d_8011CF9C[];
extern ModelSlotHead gun_turret_2_asset;
extern ModelBlockRef gun_turret_2_palettes[];
extern ModelBlockRef gun_turret_2_texture_list[];
extern ModelBlockRef gun_turret_2_models[];
extern ModelBlock gun_turret_2_block;
extern u8 *gun_turret_2_name_list[];
extern ScanEntry gun_turret_2_scan;
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
extern s32 grenade_asset[3];
extern ModelBlockRef D_8011D130[];
extern ModelBlockRef D_8011D148[];
extern ModelBlockRef D_8011D158[];
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
extern s32 bomb_mech_m7_boss_asset[];
extern ModelBlockRef D_8011D454[];
extern ModelBlockRef D_8011D474[];
extern ModelBlockRef D_8011D48C[];
extern ModelBlockRange D_8011D4AC[];
extern ModelBlock D_8011D50C;
extern u8 *D_8011D530[];
extern ScanEntry bomb_mech_m7_boss_scan;
extern SoundVolume D_8011D554[];
extern s16 bomb_mech_m7_boss_anim_idle[];
extern s16 bomb_mech_m7_boss_anim_walk_start[];
extern s16 bomb_mech_m7_boss_anim_walk[];
extern s16 bomb_mech_m7_boss_anim_turn[];
extern s16 bomb_mech_m7_boss_anim_hide_start[];
extern s16 bomb_mech_m7_boss_anim_hide[];
extern s16 bomb_mech_m7_boss_anim_emerge[];
extern s16 bomb_mech_m7_boss_anim_crouch[];
extern s16 bomb_mech_m7_boss_anim_hop_launch[];
extern s16 bomb_mech_m7_boss_anim_hop_rise[];
extern s16 bomb_mech_m7_boss_anim_hop_rise_hold[];
extern s16 bomb_mech_m7_boss_anim_hop_fall[];
extern s16 bomb_mech_m7_boss_anim_hop_fall_hold[];
extern s16 bomb_mech_m7_boss_anim_hop_land[];
extern s16 bomb_mech_m7_boss_anim_fly_prepare[];
extern s16 bomb_mech_m7_boss_anim_fly_hold[];
extern s16 bomb_mech_m7_boss_anim_fly_end[];
extern s16 bomb_mech_m7_boss_anim_bomb_run[];
extern s16 bomb_mech_m7_boss_anim_jitter[];
extern s16 bomb_mech_m7_boss_anim_jitter_wrap[];
extern s16 *bomb_mech_m7_boss_data[];
extern ScriptCallEntry D_8011D7F0[];
extern s16 bomb_mech_m7_boss_init[];
extern s16 bomb_mech_m7_boss_init_resume[];
extern s16 bomb_mech_m7_boss_init_wait[];
extern s16 bomb_mech_m7_boss_init_wait_loop[];
extern s16 bomb_mech_m7_boss_init_emerge[];
extern s16 bomb_mech_m7_boss_init_emerge_wait[];
extern s16 bomb_mech_m7_boss_init_return[];
extern s16 bomb_mech_m7_boss_turn_then_hop[];
extern s16 bomb_mech_m7_boss_hop_crouch[];
extern s16 bomb_mech_m7_boss_hop_crouch_wait[];
extern s16 bomb_mech_m7_boss_hop_spawn_parts[];
extern s16 bomb_mech_m7_boss_hop_spawn_wait[];
extern s16 bomb_mech_m7_boss_hop_launch[];
extern s16 bomb_mech_m7_boss_hop_rise_wait[];
extern s16 bomb_mech_m7_boss_hop_fall[];
extern s16 bomb_mech_m7_boss_hop_check[];
extern s16 bomb_mech_m7_boss_hop_land[];
extern s16 bomb_mech_m7_boss_hop_land_wait[];
extern s16 bomb_mech_m7_boss_hop_shoot[];
extern s16 bomb_mech_m7_boss_hop_return[];
extern s16 bomb_mech_m7_boss_turn_then_fly[];
extern s16 bomb_mech_m7_boss_fly_prepare[];
extern s16 bomb_mech_m7_boss_fly_prepare_wait[];
extern s16 bomb_mech_m7_boss_fly_start[];
extern s16 bomb_mech_m7_boss_fly_emit_loop[];
extern s16 bomb_mech_m7_boss_fly_hold[];
extern s16 bomb_mech_m7_boss_fly_end[];
extern s16 bomb_mech_m7_boss_fly_end_wait[];
extern s16 bomb_mech_m7_boss_fly_return[];
extern s16 bomb_mech_m7_boss_turn_then_bombs[];
extern s16 bomb_mech_m7_boss_bomb_run_start[];
extern s16 bomb_mech_m7_boss_bomb_pass[];
extern s16 bomb_mech_m7_boss_bomb_pass_wait[];
extern s16 bomb_mech_m7_boss_bomb_drop[];
extern s16 bomb_mech_m7_boss_bomb_drop_wait[];
extern s16 bomb_mech_m7_boss_bomb_pass_loop[];
extern s16 bomb_mech_m7_boss_walk_then_jitter[];
extern s16 bomb_mech_m7_boss_jitter_start[];
extern s16 bomb_mech_m7_boss_jitter_frame[];
extern s16 bomb_mech_m7_boss_jitter_wait[];
extern s16 bomb_mech_m7_boss_jitter_end[];
extern s16 bomb_mech_m7_boss_timer_wait[];
extern s16 bomb_mech_m7_boss_timer_return[];
extern s16 bomb_mech_m7_boss_walk_then_fire[];
extern s16 bomb_mech_m7_boss_fire_burst_start[];
extern s16 bomb_mech_m7_boss_fire_burst_ramp_wait[];
extern s16 bomb_mech_m7_boss_fire_sound[];
extern s16 bomb_mech_m7_boss_fire_muzzle[];
extern s16 bomb_mech_m7_boss_fire_burst_wait[];
extern s16 bomb_mech_m7_boss_fire_burst_end[];
extern s16 bomb_mech_m7_boss_walk_start[];
extern s16 bomb_mech_m7_boss_walk_wait[];
extern s16 bomb_mech_m7_boss_walk_end[];
extern s16 bomb_mech_m7_boss_turn_to_target[];
extern s16 bomb_mech_m7_boss_turn_wait_idle[];
extern s16 bomb_mech_m7_boss_turn_start[];
extern s16 bomb_mech_m7_boss_turn_wait[];
extern s16 bomb_mech_m7_boss_turn_done[];
extern s16 bomb_mech_m7_boss_player_below_check[];
extern s16 bomb_mech_m7_boss_turn_to_player_check[];
extern s16 bomb_mech_m7_boss_player_beyond_check[];
extern s16 bomb_mech_m7_boss_bombs_then_pause[];
extern s16 bomb_mech_m7_boss_attack_fire[];
extern s16 bomb_mech_m7_boss_attack_choose_a[];
extern s16 bomb_mech_m7_boss_attack_choose_b[];
extern s16 bomb_mech_m7_boss_attack_choose_c[];
extern s16 bomb_mech_m7_boss_attack_choose_d[];
extern s16 bomb_mech_m7_boss_attack_return[];
extern s16 bomb_mech_m7_boss_scan_far[];
extern s16 bomb_mech_m7_boss_aim_check[];
extern s16 bomb_mech_m7_boss_aim_jitter[];
extern s16 bomb_mech_m7_boss_attack_choose_e[];
extern s16 bomb_mech_m7_boss_attack_choose_f[];
extern s16 bomb_mech_m7_boss_attack_f_return[];
extern s16 bomb_mech_m7_boss_far_return[];
extern s16 bomb_mech_m7_boss_walk_then_pause[];
extern s16 bomb_mech_m7_boss_pause_return[];
extern s16 bomb_mech_m7_boss_player_scan[];
extern s16 bomb_mech_m7_boss_turn_then_scan[];
extern s16 *D_8011DD68[];
extern u32 D_8011DEA4;
extern u32 D_8011DEA8[];
extern s16 hit_mask_weights[];
extern Keyframe sfx_keyframes[];
extern FxRecordParams sfx_emitter_params;
extern Keyframe spark_keyframe_path[7];
extern Keyframe keyframe_table_alt[];
extern Keyframe keyframe_table_default[];
extern Keyframe keyframe_list[];
extern s32 model_part_slots[];
extern s32 keyframe_spawn_enabled;
extern s16 cam_shake_nudges[];
extern SVECTOR fade_target_color;
extern s32 fly_active;
extern s32 fx_stop_flag;
extern s32 fly_emit_timer;
extern s32 debris_active;
extern s32 debris_stopped;
extern s32 debris_spawn_timer;
extern s32 debris_angle;
extern FxRecordParams fly_spark_params;
extern u32 D_8011E03C[];
extern Keyframe D_8011E04C[];
extern RecTemplate fade_red_fx_template;
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern s32 D_8011E0B4[];
extern s32 clamp_table[8];
extern ClampTable area_clamp_table_set;
extern u32 D_8011E104[];
extern s32 area_capture_state[5];
extern SoundPos area_sound_slots[4];
extern ScanEntry D_8011E164;
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *msgs_file_names[];
extern ScanEntry enemy_msgs_scan_entry;
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_80122D90[];
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
extern u32 D_80123F14[];
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
extern u32 D_80124534;
extern u16 texture_image[];
extern u16 stage_image_width;
extern u16 stage_image_height;
extern u32 stage_image_pixels[];
extern s32 heap_top;
extern s32 heap2_top;
extern s32 model_pchr_saved;
extern s32 area_bounds_x0;
extern s32 area_bounds_x1;
extern s32 area_bounds_z0;
extern s32 area_bounds_z1;
extern s32 area_center_x;
extern s32 area_center_z;
extern s32 value_queue_index;
extern s32 bomb_mech_m7_boss_active;
extern s32 D_80125970;
extern s32 keyframe_spawn_timer;
extern s32 keyframe_spawn_index;
extern s32 keyframe_spawn_owner;
extern s32 fx_owner_obj;
extern Next800C5620 *fade_red_obj;
extern s32 area_ambient_sound;
extern s32 area_capture_count;
extern s32 area_capture_final_flag;
extern s32 area_capture_complete_flag;
extern s32 *area_target_ptr;
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
extern u32 D_80125A94;
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
extern u32 D_80125B18;
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
extern s32 interp_enabled_flag;
extern s32 interp_record_count;
extern s32 interp1c_count;
extern s32 interp2c_count;
extern s32 interp38_count;
extern s32 interp38b_count;
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
extern s32 rocket_shot_params;
extern s32 D_80125FAC;
extern s32 D_80125FB0;
extern s16 D_80125FB4;
extern s16 rocket_shot_hit_effect_index;
extern s16 D_80125FB8;
extern s16 D_80125FBA;
extern s16 D_80125FBC;
extern s16 D_80125FBE;
extern s16 D_80125FC0;
extern s16 D_80125FC2;
extern s16 D_80125FC4;
extern s16 D_80125FC6;
extern s16 D_80125FC8;
extern s16 D_80125FCA;
extern ShotParams shot_params;
extern s16 value_queue[];

s32 area = 0x12;

ScanItem enemy_load_items[11] = {
    {&stationary_rocket_launcher_entry, str_enemy_kitt_data},
    {&arkb_scan_entry, str_enemy_arkb_data},
    {&walker_mech_scan_entry, str_enemy_horo_data},
    {&helicopter2_scan_entry, str_enemy_fap2_data},
    {&tank_scan_entry, str_enemy_nk2_data},
    {&gun_turret_2_scan, str_enemy_hou2_data},
    {&grenade_fuchikoma_scan_entry, str_enemy_mth2_data},
    {&bomb_mech_m7_boss_scan, str_enemy_bos7_data},
    {&D_8011E164, str_enemy_ctl7_data},
    {&enemy_msgs_scan_entry, str_enemy_msgs_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry D_8011C29C = {str_s07_stage, str_cty_cnf_bcf, str_cty_apdea3, str_cty_joy_bin, str_s07_dat_fac, str_s07_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, enemy_load_items};

AreaEntry D_8011C2C4 = {str_s07_miss, str_m31_cnf_bcf, NULL, str_m31_joy_bin, str_m07_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

u32 D_8011C2EC[12] = {
    0xFFFFFFFF, 0x00000000, (u32)str_s07_boss, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x10001000, 0x00001000, 0x00000000, (u32)D_8011C2EC,
};

AreaEntry *area_entry_table[3] = {
    &D_8011C2C4, &D_8011C29C, NULL,
};

#include "../stage/data/debug_name_buf.c"

s32 rocket_launcher_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef rocket_launcher_clt_refs[3] = {
    {(s32)file_kitt_ch0_clt, 0, 0},
    {(s32)file_kitt_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef rocket_launcher_xs3_refs[2] = {
    {(s32)file_kitt_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef rocket_launcher_vx1_refs[2] = {
    {(s32)file_kitt_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock rocket_launcher_model = {(s32)rocket_launcher_clt_refs, (s32)rocket_launcher_vx1_refs, (s32)rocket_launcher_xs3_refs, 0, 0, 0, 0, 0, 0};

u8 *rocket_launcher_cb4_refs[2] = {
    file_kitt_ch0_cb4, NULL,
};

ScanEntry stationary_rocket_launcher_entry = {{(s32)stationary_rocket_launcher_init, (s32)stationary_rocket_launcher_spawn}, rocket_launcher_asset, (s32)&rocket_launcher_model, (s32)rocket_launcher_cb4_refs, 0};

u32 D_8011C470[3] = {
    0x10000000, 0x051E0001, 0x051E0002,
};

struct StationaryRocketLauncherAnims {
    s16 idle[4];
    s16 *table;
} stationary_rocket_launcher_anims = {
    /* idle */ {
        STEP(4, 1),
        GOTO(STATIONARY_ROCKET_LAUNCHER_ANIM_IDLE),
    },
    /* table */ stationary_rocket_launcher_anims.idle,
};

struct StationaryRocketLauncherScripts {
    s16 idle[8];
    s16 track[2];
    s16 aim[10];
    s16 lock_on[6];
    s16 fire_start[2];
    s16 fire_loop[8];
    s16 launch_start[2];
    s16 launch_loop[8];
    s16 *table[8];
    s16 *rocket_launcher_anim_link;
} stationary_rocket_launcher_scripts = {
    /* idle */ {
        WAIT(1),
        STATIONARY_ROCKET_LAUNCHER_JUMP_IF_WITHIN_DIST, 3000, STATIONARY_ROCKET_LAUNCHER_TRACK,
        JUMP(STATIONARY_ROCKET_LAUNCHER_IDLE),
    },
    /* track */ {
        NEXT_STATE(STATIONARY_ROCKET_LAUNCHER_STATE_TRACK),
    },
    /* aim */ {
        WAIT(1),
        STATIONARY_ROCKET_LAUNCHER_JUMP_IF_WITHIN_DIST, 2000, STATIONARY_ROCKET_LAUNCHER_LOCK_ON,
        STATIONARY_ROCKET_LAUNCHER_JUMP_IF_PLAYER_IN_CONE, 128, STATIONARY_ROCKET_LAUNCHER_FIRE_START,
        JUMP(STATIONARY_ROCKET_LAUNCHER_AIM),
    },
    /* lock_on */ {
        STATIONARY_ROCKET_LAUNCHER_JUMP_IF_PLAYER_IN_CONE, 256, STATIONARY_ROCKET_LAUNCHER_LAUNCH_START,
        JUMP(STATIONARY_ROCKET_LAUNCHER_AIM),
    },
    /* fire_start */ {
        NEXT_STATE(STATIONARY_ROCKET_LAUNCHER_STATE_FIRE),
    },
    /* fire_loop */ {
        WAIT(1),
        JUMP_IF_STATE(STATIONARY_ROCKET_LAUNCHER_STATE_IDLE, STATIONARY_ROCKET_LAUNCHER_IDLE),
        JUMP(STATIONARY_ROCKET_LAUNCHER_FIRE_LOOP),
    },
    /* launch_start */ {
        NEXT_STATE(STATIONARY_ROCKET_LAUNCHER_STATE_LAUNCH),
    },
    /* launch_loop */ {
        WAIT(1),
        JUMP_IF_STATE(STATIONARY_ROCKET_LAUNCHER_STATE_IDLE, STATIONARY_ROCKET_LAUNCHER_IDLE),
        JUMP(STATIONARY_ROCKET_LAUNCHER_LAUNCH_LOOP),
    },
    /* table */ {
        stationary_rocket_launcher_scripts.idle, stationary_rocket_launcher_scripts.track, stationary_rocket_launcher_scripts.aim, stationary_rocket_launcher_scripts.lock_on, stationary_rocket_launcher_scripts.fire_start, stationary_rocket_launcher_scripts.fire_loop,
        stationary_rocket_launcher_scripts.launch_start, stationary_rocket_launcher_scripts.launch_loop,
    },
    /* rocket_launcher_anim_link */ stationary_rocket_launcher_scripts.idle,
};

ScriptCallEntry D_8011C508[3] = {
    {NULL, 0},
    {script_op_jump_if_within_dist, 0},
    {script_op_jump_if_player_in_cone, 0},
};

StateEntry D_8011C520[4] = {
    {0, STATIONARY_ROCKET_LAUNCHER_ANIM_IDLE, 1},
    {(u32)enemy_handler_done, STATIONARY_ROCKET_LAUNCHER_ANIM_IDLE, 1},
    {(u32)enemy_fire_shot_step, STATIONARY_ROCKET_LAUNCHER_ANIM_IDLE, 1},
    {(u32)enemy_rocket_aim_step, STATIONARY_ROCKET_LAUNCHER_ANIM_IDLE, 1},
};

RecTemplate rocket_explode_fx_template = {1, 0x94, 0x6C, 0x6C, 0, 0x24, 0, 0x46000, -0x1000, 0x8000};

RecTemplate D_8011C558 = {1, 0xFF, 0x40, 0, 0, 0x20, 0, 0x54000, -0x1000, 0x8000};

#include "../stage/data/fuchikoma_asset.c"

#include "../stage/data/arkb_palettes.c"

#include "../stage/data/arkb_textures.c"

#include "../stage/data/arkb_models.c"

#include "../stage/data/d_8011C5B4.c"

#include "../stage/data/arkb_model_block.c"

#include "../stage/data/enemy_fuchikoma_b_cb4_refs.c"

#include "../stage/data/arkb_scan_entry.c"

#include "../stage/data/d_8011C610.c"

#include "../stage/data/enemy_fuchikoma_b_anims.c"

#include "../stage/data/enemy_fuchikoma_b_scripts.c"

#include "../stage/data/fuchikoma_call_table.c"

#include "../stage/data/muzzle_side_table.c"

#include "../stage/data/fuchikoma_state_table.c"

#include "../stage/data/shot_muzzle_x_table.c"

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

u32 helicopter2_asset[3] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
};

#include "../stage/data/flyer_shot_setup.c"

#include "../stage/data/helicopter2_palettes.c"

#include "../stage/data/helicopter2_textures.c"

#include "../stage/data/helicopter2_models.c"

#include "../stage/data/helicopter2_model_block.c"

#include "../stage/data/helicopter2_stage_files.c"

ScanEntry helicopter2_scan_entry = {{0, (s32)helicopter2_spawn}, (s32 *)helicopter2_asset, (s32)&helicopter2_model_block, (s32)helicopter2_stage_files, 0};

struct Helicopter2ScriptAnims {
    s16 cfg[4];
    s16 *table[1];
} helicopter_2_script_anims = {
    /* cfg */ {
        STEP(1, 0),
        GOTO(HELICOPTER_2_SCRIPT_CFG),
    },
    /* table */ {
        helicopter_2_script_anims.cfg,
    },
};

#include "../stage/data/ground_shadow_params.c"

#include "../stage/data/fx_rec34_params_a.c"

#include "../stage/data/fx_rec34_params_b.c"

#include "../stage/data/helicopter2_scripts.c"

#include "../stage/data/helicopter2_script_calls.c"

StateEntry helicopter2_states[4] = {
    {(u32)enemy_fly_step, HELICOPTER_2_SCRIPT_CFG, 0},
    {(u32)enemy_fly_attack, HELICOPTER_2_SCRIPT_CFG, 0},
    {(u32)flyer_hover_update, HELICOPTER_2_SCRIPT_CFG, 0},
    {(u32)flyer_bank_turn, HELICOPTER_2_SCRIPT_CFG, 0},
};

#include "../stage/data/tank2_asset.c"

#include "../stage/data/d_8011CBFC.c"

#include "../stage/data/d_8011CC14.c"

#include "../stage/data/tank2_models.c"

#include "../stage/data/tank_model_block.c"

#include "../stage/data/d_8011CC58.c"

#include "../stage/data/tank_scan_entry.c"

#include "../stage/data/tank_2_anims.c"

#include "../stage/data/tank_2_scripts.c"

#include "../stage/data/d_8011CF34.c"

#include "../stage/data/d_8011CF9C.c"

#include "../stage/data/gun_turret_2_asset.c"

#include "../stage/data/gun_turret_2_palettes.c"

#include "../stage/data/gun_turret_2_texture_list.c"

#include "../stage/data/gun_turret_2_models.c"

#include "../stage/data/gun_turret_2_block.c"

#include "../stage/data/gun_turret_2_name_list.c"

#include "../stage/data/gun_turret_2_scan.c"

#include "../stage/data/d_80116D8C.c"

#include "../stage/data/gun_turret_2_anims.c"

#include "../stage/data/gun_turret_2_scripts.c"

#include "../stage/data/gun_turret_2_calls.c"

#include "../stage/data/gun_turret_2_states.c"

s32 grenade_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_8011D130[3] = {
    {(s32)str_mth2_ch0_clt, 0, 0},
    {(s32)str_mth2_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011D148[2] = {
    {(s32)str_mth2_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011D158[2] = {
    {(s32)str_mth2_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock grenade_fuchikoma_model = {(s32)D_8011D130, (s32)D_8011D158, (s32)D_8011D148, 0, 0, 0, 0, 0, 0};

u8 *d_80116624[2] = {
    str_mth2_ch0cb4, NULL,
};

ScanEntry grenade_fuchikoma_scan_entry = {{(s32)params_reset, (s32)grenade_fuchikoma_spawn}, grenade_asset, (s32)&grenade_fuchikoma_model, (s32)d_80116624, 0};

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

s32 bomb_mech_m7_boss_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_8011D454[4] = {
    {(s32)str_bos7_ch0_clt, 0, 0},
    {(s32)str_bos7_tp0_clt, 0, 0},
    {(s32)str_bos7_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011D474[3] = {
    {(s32)str_bos7_tp0_xs3, 1, 0},
    {(s32)str_bos7_tp1_xs3, 2, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011D48C[4] = {
    {(s32)str_bos7_ch0_vx1, 0, 0},
    {(s32)str_bos7_ch1_vx1, 0, 0},
    {(s32)str_bos7_ch2_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011D4AC[12] = {
    {0x100, 0x103, 0x2000, 0}, {0x104, 0x104, 0x2000, 0}, {0x108, 0x10C, 0x2000, 0}, {0x110, 0x112, 0x1000, 0},
    {0x114, 0x115, 0x2000, 0}, {0x118, 0x119, 0x1000, 0}, {0x128, 0x12B, 0x1000, 0}, {0x130, 0x131, 0x2000, 0},
    {0x138, 0x13A, 0x2000, 0}, {0x140, 0x142, 0x2000, 0}, {0x148, 0x149, 0x807, 0}, {-1, -1, -1, 0},
};

ModelBlock D_8011D50C = {(s32)D_8011D454, (s32)D_8011D48C, (s32)D_8011D474, 0, (s32)D_8011D4AC, 0, 0, 0, 0};

u8 *D_8011D530[3] = {
    str_bos7_ch0cb4, str_bos7_ch1cb4, NULL,
};

ScanEntry bomb_mech_m7_boss_scan = {{0, (s32)bomb_mech_m7_boss_spawn}, bomb_mech_m7_boss_asset, (s32)&D_8011D50C, (s32)D_8011D530, 0};

SoundVolume D_8011D554[7] = {
    {0x50C0, 0x1000},
    {0x50C2, 0x1000},
    {0x50CB, 0x1000},
    {SND_DOOR_OPEN | SND_GROUP(2), 0x1000},
    {SND_DOOR_CLOSE | SND_GROUP(2), 0x1000},
    {0x50CF, 0x1000},
    {0x50D2, 0x1000},
};

struct BombMechM7BossAnims {
    s16 idle[6];
    s16 walk_start[4];
    s16 walk[38];
    s16 turn[6];
    s16 hide_start[4];
    s16 hide[4];
    s16 emerge[16];
    s16 crouch[16];
    s16 hop_launch[14];
    s16 hop_rise[22];
    s16 hop_rise_hold[4];
    s16 hop_fall[4];
    s16 hop_fall_hold[4];
    s16 hop_land[20];
    s16 fly_prepare[36];
    s16 fly_hold[4];
    s16 fly_end[34];
    s16 bomb_run[8];
    s16 jitter[18];
    s16 jitter_wrap[4];
    s16 *table[20];
} bomb_mech_m7_boss_anims = {
    /* idle */ {
        STEP(2, 1),
        STEP(2, 1),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_IDLE),
    },
    /* walk_start */ {
        STEP(30, 16),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_WALK),
    },
    /* walk */ {
        STEP(4, 16),
        STEP(4, 17),
        STEP(4, 18),
        STEP(4, 19),
        STEP(4, 20),
        SOUND(0),
        STEP(4, 21),
        STEP(4, 22),
        STEP(4, 23),
        STEP(4, 24),
        STEP(4, 25),
        STEP(4, 26),
        STEP(4, 27),
        STEP(4, 28),
        SOUND(0),
        STEP(4, 29),
        STEP(4, 30),
        STEP(4, 31),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_WALK),
    },
    /* turn */ {
        STEP(30, 1),
        STEP(2, 1),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_IDLE),
    },
    /* hide_start */ {
        STEP(2, 46),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_HIDE),
    },
    /* hide */ {
        STEP(2, 46),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_HIDE),
    },
    /* emerge */ {
        STEP(0, 47),
        SOUND(1),
        STEP(10, 50),
        STEP(10, 51),
        STEP(10, 52),
        STEP(10, 53),
        STEP(10, 1),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_IDLE),
    },
    /* crouch */ {
        STEP(8, 1),
        STEP(8, 97),
        STEP(8, 99),
        STEP(4, 101),
        STEP(4, 102),
        STEP(0, 103),
        STEP(8, 215),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_HOP_LAUNCH),
    },
    /* hop_launch */ {
        SOUND(3),
        STEP(8, 217),
        STEP(8, 219),
        STEP(8, 221),
        STEP(8, 223),
        STEP(2, 225),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_HOP_RISE),
    },
    /* hop_rise */ {
        STEP(2, 229),
        STEP(2, 230),
        STEP(2, 231),
        STEP(2, 232),
        STEP(2, 233),
        STEP(2, 234),
        STEP(2, 235),
        STEP(2, 236),
        STEP(2, 237),
        STEP(2, 238),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_HOP_RISE_HOLD),
    },
    /* hop_rise_hold */ {
        STEP(2, 238),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_HOP_RISE_HOLD),
    },
    /* hop_fall */ {
        STEP(2, 238),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_HOP_FALL_HOLD),
    },
    /* hop_fall_hold */ {
        STEP(2, 238),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_HOP_FALL_HOLD),
    },
    /* hop_land */ {
        SOUND(2),
        STEP(10, 243),
        STEP(10, 244),
        STEP(10, 245),
        STEP(10, 246),
        STEP(10, 247),
        SOUND(4),
        STEP(0, 1),
        STEP(10, 1),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_IDLE),
    },
    /* fly_prepare */ {
        STEP(2, 80),
        STEP(2, 81),
        STEP(2, 82),
        STEP(2, 83),
        STEP(2, 84),
        STEP(2, 85),
        STEP(0, 86),
        STEP(2, 158),
        SOUND(5),
        STEP(2, 159),
        STEP(2, 160),
        STEP(2, 161),
        STEP(2, 162),
        STEP(2, 163),
        STEP(2, 164),
        STEP(2, 165),
        STEP(2, 166),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_FLY_HOLD),
    },
    /* fly_hold */ {
        STEP(2, 166),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_FLY_HOLD),
    },
    /* fly_end */ {
        STEP(2, 165),
        STEP(2, 164),
        STEP(2, 163),
        STEP(2, 162),
        STEP(2, 161),
        STEP(2, 160),
        STEP(2, 159),
        STEP(0, 86),
        STEP(2, 86),
        SOUND(6),
        STEP(2, 85),
        STEP(2, 84),
        STEP(2, 83),
        STEP(2, 82),
        STEP(2, 81),
        STEP(2, 80),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_IDLE),
    },
    /* bomb_run */ {
        STEP(4, 66),
        STEP(2, 65),
        STEP(2, 64),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_BOMB_RUN),
    },
    /* jitter */ {
        STEP(6, 64),
        STEP(6, 65),
        STEP(6, 66),
        STEP(6, 67),
        STEP(6, 68),
        STEP(6, 69),
        STEP(6, 70),
        STEP(6, 71),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_JITTER_WRAP),
    },
    /* jitter_wrap */ {
        STEP(3, 71),
        GOTO(BOMB_MECH_M7_BOSS_ANIM_JITTER),
    },
    /* table */ {
        bomb_mech_m7_boss_anims.idle, bomb_mech_m7_boss_anims.walk_start, bomb_mech_m7_boss_anims.walk, bomb_mech_m7_boss_anims.turn, bomb_mech_m7_boss_anims.hide_start, bomb_mech_m7_boss_anims.hide,
        bomb_mech_m7_boss_anims.emerge, bomb_mech_m7_boss_anims.crouch, bomb_mech_m7_boss_anims.hop_launch, bomb_mech_m7_boss_anims.hop_rise, bomb_mech_m7_boss_anims.hop_rise_hold, bomb_mech_m7_boss_anims.hop_fall,
        bomb_mech_m7_boss_anims.hop_fall_hold, bomb_mech_m7_boss_anims.hop_land, bomb_mech_m7_boss_anims.fly_prepare, bomb_mech_m7_boss_anims.fly_hold, bomb_mech_m7_boss_anims.fly_end, bomb_mech_m7_boss_anims.bomb_run,
        bomb_mech_m7_boss_anims.jitter, bomb_mech_m7_boss_anims.jitter_wrap,
    },
};

ScriptCallEntry D_8011D7F0[45] = {
    {NULL, 0},
    {script_op_skip_halfword, 0},
    {script_op_jump_if_player_within, 0},
    {script_op_jump_if_player_beyond, 0},
    {script_turn_to_player_jump, 0},
    {script_op_jump_if_outside_bounds, 0},
    {script_case_match, 0},
    {script_op_jump_if_flag_1b7, 0},
    {script_op_jump_if_player_close, 0},
    {script_set_enemy_var, 0},
    {script_op_set_vy, 0},
    {script_op_jump_if_vy_nonneg, 0},
    {script_value_queue_push, 0},
    {value_queue_pop, 0},
    {heli_fire_bombs, 0},
    {fly_emitter_update, 0},
    {obj_jitter_update, 0},
    {obj_nop, 0},
    {script_timer_reverse, 0},
    {script_jump_table_cond, 0},
    {script_store_enemy_halfword, 0},
    {script_loop_set_count, 0},
    {script_loop_next, 0},
    {obj_spawn_muzzle_flash, 0},
    {script_spawn_model_parts, 0},
    {script_clear_model_parts, 0},
    {mode_keyframe_enable, 0},
    {mode_reset, 0},
    {obj_keytrack_start, 0},
    {script_shoot_at_player, 0},
    {obj_enable, 0},
    {obj_disable, 0},
    {obj_roll_set, 0},
    {script_branch_if_roll, 0},
    {script_branch_if_repeat, 0},
    {obj_start_positional_sound, 0},
    {obj_ramp_dispatch, 0},
    {obj_sound_start_a, 0},
    {obj_stop_held_sound, 0},
    {obj_sound_start_b, 0},
    {obj_sound_stop_b, 0},
    {script_set_target_yaw, 0},
    {script_branch_if_flag, 0},
    {script_read_walk_state, 0},
    {script_jump_if_player_below, 0},
};

struct BombMechM7BossScripts {
    s16 init[10];
    s16 init_resume[2];
    s16 init_wait[2];
    s16 init_wait_loop[6];
    s16 init_emerge[12];
    s16 init_emerge_wait[8];
    s16 init_return[2];
    s16 turn_then_hop[4];
    s16 hop_crouch[10];
    s16 hop_crouch_wait[8];
    s16 hop_spawn_parts[4];
    s16 hop_spawn_wait[8];
    s16 hop_launch[10];
    s16 hop_rise_wait[6];
    s16 hop_fall[4];
    s16 hop_check[8];
    s16 hop_land[14];
    s16 hop_land_wait[8];
    s16 hop_shoot[6];
    s16 hop_return[2];
    s16 turn_then_fly[4];
    s16 fly_prepare[10];
    s16 fly_prepare_wait[8];
    s16 fly_start[10];
    s16 fly_emit_loop[10];
    s16 fly_hold[6];
    s16 fly_end[8];
    s16 fly_end_wait[8];
    s16 fly_return[2];
    s16 turn_then_bombs[4];
    s16 bomb_run_start[10];
    s16 bomb_pass[2];
    s16 bomb_pass_wait[8];
    s16 bomb_drop[4];
    s16 bomb_drop_wait[8];
    s16 bomb_pass_loop[6];
    s16 walk_then_jitter[4];
    s16 jitter_start[4];
    s16 jitter_frame[4];
    s16 jitter_wait[10];
    s16 jitter_end[4];
    s16 timer_wait[6];
    s16 timer_return[2];
    s16 walk_then_fire[4];
    s16 fire_burst_start[6];
    s16 fire_burst_ramp_wait[6];
    s16 fire_sound[2];
    s16 fire_muzzle[4];
    s16 fire_burst_wait[10];
    s16 fire_burst_end[4];
    s16 walk_start[12];
    s16 walk_wait[8];
    s16 walk_end[6];
    s16 turn_to_target[4];
    s16 turn_wait_idle[8];
    s16 turn_start[4];
    s16 turn_wait[8];
    s16 turn_done[12];
    s16 player_below_check[4];
    s16 turn_to_player_check[6];
    s16 player_beyond_check[8];
    s16 bombs_then_pause[2];
    s16 attack_fire[4];
    s16 attack_choose_a[12];
    s16 attack_choose_b[12];
    s16 attack_choose_c[14];
    s16 attack_choose_d[24];
    s16 attack_return[2];
    s16 scan_far[2];
    s16 aim_check[6];
    s16 aim_jitter[4];
    s16 attack_choose_e[10];
    s16 attack_choose_f[12];
    s16 attack_f_return[2];
    s16 far_return[2];
    s16 walk_then_pause[4];
    s16 pause_return[4];
    s16 player_scan[8];
    s16 turn_then_scan[4];
    s16 *table[79];
    u32 D_8011DEA4;
} bomb_mech_m7_boss_scripts = {
    /* init */ {
        BOMB_MECH_M7_BOSS_SET_ENEMY_VAR, 0,
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_HOLD),
        WANDER(0),
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 1,
        JUMP(BOMB_MECH_M7_BOSS_INIT_WAIT),
    },
    /* init_resume */ {
        JUMP(BOMB_MECH_M7_BOSS_PLAYER_SCAN),
    },
    /* init_wait */ {
        JUMP(BOMB_MECH_M7_BOSS_INIT_WAIT_LOOP),
    },
    /* init_wait_loop */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_JUMP_IF_FLAG_1B7, BOMB_MECH_M7_BOSS_INIT_EMERGE,
        JUMP(BOMB_MECH_M7_BOSS_INIT_WAIT_LOOP),
    },
    /* init_emerge */ {
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_EMERGE),
        WANDER(0),
        BOMB_MECH_M7_BOSS_SET_ENEMY_VAR, 0,
        SET_SPEED(0),
        WAIT(1),
        JUMP(BOMB_MECH_M7_BOSS_INIT_EMERGE_WAIT),
    },
    /* init_emerge_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_INIT_RETURN,
        JUMP(BOMB_MECH_M7_BOSS_INIT_EMERGE_WAIT),
    },
    /* init_return */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* turn_then_hop */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 8,
        JUMP(BOMB_MECH_M7_BOSS_TURN_TO_TARGET),
    },
    /* hop_crouch */ {
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_CROUCH),
        WANDER(0),
        BOMB_MECH_M7_BOSS_SET_ENEMY_VAR, 0,
        SET_SPEED(0),
        JUMP(BOMB_MECH_M7_BOSS_HOP_CROUCH_WAIT),
    },
    /* hop_crouch_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_HOP_SPAWN_PARTS,
        JUMP(BOMB_MECH_M7_BOSS_HOP_CROUCH_WAIT),
    },
    /* hop_spawn_parts */ {
        BOMB_MECH_M7_BOSS_SPAWN_MODEL_PARTS,
        BOMB_MECH_M7_BOSS_MODE_KEYFRAME_ENABLE,
        JUMP(BOMB_MECH_M7_BOSS_HOP_SPAWN_WAIT),
    },
    /* hop_spawn_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_HOP_LAUNCH,
        JUMP(BOMB_MECH_M7_BOSS_HOP_SPAWN_WAIT),
    },
    /* hop_launch */ {
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_RISE),
        WANDER(0),
        BOMB_MECH_M7_BOSS_SET_ENEMY_VAR, 0,
        SET_SPEED(0),
        BOMB_MECH_M7_BOSS_SET_VY, -60,
    },
    /* hop_rise_wait */ {
        BOMB_MECH_M7_BOSS_JUMP_IF_VY_NONNEG, BOMB_MECH_M7_BOSS_HOP_FALL,
        WAIT(1),
        JUMP(BOMB_MECH_M7_BOSS_HOP_RISE_WAIT),
    },
    /* hop_fall */ {
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_FALL),
        JUMP(BOMB_MECH_M7_BOSS_HOP_CHECK),
    },
    /* hop_check */ {
        BOMB_MECH_M7_BOSS_JUMP_IF_PLAYER_CLOSE, BOMB_MECH_M7_BOSS_HOP_SHOOT,
        BOMB_MECH_M7_BOSS_JUMP_IF_FLAG_1B7, BOMB_MECH_M7_BOSS_HOP_LAND,
        WAIT(1),
        JUMP(BOMB_MECH_M7_BOSS_HOP_CHECK),
    },
    /* hop_land */ {
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_LAND),
        WANDER(0),
        BOMB_MECH_M7_BOSS_SET_ENEMY_VAR, 0,
        SET_SPEED(0),
        BOMB_MECH_M7_BOSS_CLEAR_MODEL_PARTS,
        BOMB_MECH_M7_BOSS_MODE_RESET,
        BOMB_MECH_M7_BOSS_KEYTRACK_START,
        JUMP(BOMB_MECH_M7_BOSS_HOP_LAND_WAIT),
    },
    /* hop_land_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_HOP_RETURN,
        JUMP(BOMB_MECH_M7_BOSS_HOP_LAND_WAIT),
    },
    /* hop_shoot */ {
        BOMB_MECH_M7_BOSS_SHOOT_AT_PLAYER, 4, 30,
        JUMP(BOMB_MECH_M7_BOSS_HOP_LAUNCH),
    },
    /* hop_return */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* turn_then_fly */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 21,
        JUMP(BOMB_MECH_M7_BOSS_TURN_TO_TARGET),
    },
    /* fly_prepare */ {
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_FOLD),
        WANDER(0),
        BOMB_MECH_M7_BOSS_SET_ENEMY_VAR, 0,
        SET_SPEED(0),
        JUMP(BOMB_MECH_M7_BOSS_FLY_PREPARE_WAIT),
    },
    /* fly_prepare_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_FLY_START,
        JUMP(BOMB_MECH_M7_BOSS_FLY_PREPARE_WAIT),
    },
    /* fly_start */ {
        BOMB_MECH_M7_BOSS_ENABLE,
        BOMB_MECH_M7_BOSS_SOUND_START_B,
        SET_COUNTER(60),
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_FLY),
        BOMB_MECH_M7_BOSS_FLY_EMITTER_UPDATE, 0,
        JUMP(BOMB_MECH_M7_BOSS_FLY_EMIT_LOOP),
    },
    /* fly_emit_loop */ {
        WAIT(1),
        LOOP(BOMB_MECH_M7_BOSS_FLY_EMIT_LOOP),
        BOMB_MECH_M7_BOSS_FLY_EMITTER_UPDATE, 2,
        SET_COUNTER(60),
        JUMP(BOMB_MECH_M7_BOSS_FLY_HOLD),
    },
    /* fly_hold */ {
        WAIT(1),
        LOOP(BOMB_MECH_M7_BOSS_FLY_HOLD),
        JUMP(BOMB_MECH_M7_BOSS_FLY_END),
    },
    /* fly_end */ {
        BOMB_MECH_M7_BOSS_DISABLE,
        BOMB_MECH_M7_BOSS_SOUND_STOP_B,
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_UNFOLD),
        WAIT(1),
        JUMP(BOMB_MECH_M7_BOSS_FLY_END_WAIT),
    },
    /* fly_end_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_FLY_RETURN,
        JUMP(BOMB_MECH_M7_BOSS_FLY_END_WAIT),
    },
    /* fly_return */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* turn_then_bombs */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 30,
        JUMP(BOMB_MECH_M7_BOSS_TURN_TO_TARGET),
    },
    /* bomb_run_start */ {
        SET_COUNTER(8),
        BOMB_MECH_M7_BOSS_SET_ENEMY_VAR, 0,
        WANDER(0),
        SET_SPEED(0),
        JUMP(BOMB_MECH_M7_BOSS_BOMB_PASS),
    },
    /* bomb_pass */ {
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_BOMB_PASS),
    },
    /* bomb_pass_wait */ {
        WAIT(1),
        JUMP_IF_STATE(BOMB_MECH_M7_BOSS_STATE_BOMB_PASS, BOMB_MECH_M7_BOSS_BOMB_DROP),
        JUMP(BOMB_MECH_M7_BOSS_BOMB_PASS_WAIT),
    },
    /* bomb_drop */ {
        BOMB_MECH_M7_BOSS_HELI_FIRE_BOMBS,
        JUMP(BOMB_MECH_M7_BOSS_BOMB_DROP_WAIT),
    },
    /* bomb_drop_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_BOMB_PASS_LOOP,
        JUMP(BOMB_MECH_M7_BOSS_BOMB_DROP_WAIT),
    },
    /* bomb_pass_loop */ {
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_IDLE),
        LOOP(BOMB_MECH_M7_BOSS_BOMB_PASS),
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* walk_then_jitter */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 37,
        JUMP(BOMB_MECH_M7_BOSS_WALK_START),
    },
    /* jitter_start */ {
        SET_COUNTER(3),
        JUMP(BOMB_MECH_M7_BOSS_JITTER_FRAME),
    },
    /* jitter_frame */ {
        BOMB_MECH_M7_BOSS_JITTER_UPDATE,
        BOMB_MECH_M7_BOSS_STORE_ENEMY_HALFWORD, 0, 8,
    },
    /* jitter_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_JITTER_END,
        BOMB_MECH_M7_BOSS_LOOP_NEXT, 0, BOMB_MECH_M7_BOSS_JITTER_WAIT,
        JUMP(BOMB_MECH_M7_BOSS_JITTER_FRAME),
    },
    /* jitter_end */ {
        LOOP(BOMB_MECH_M7_BOSS_JITTER_FRAME),
        BOMB_MECH_M7_BOSS_TIMER_REVERSE,
    },
    /* timer_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_JUMP_TABLE_COND, BOMB_MECH_M7_BOSS_TIMER_RETURN,
        JUMP(BOMB_MECH_M7_BOSS_TIMER_WAIT),
    },
    /* timer_return */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* walk_then_fire */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 44,
        JUMP(BOMB_MECH_M7_BOSS_WALK_START),
    },
    /* fire_burst_start */ {
        SET_COUNTER(3),
        BOMB_MECH_M7_BOSS_START_POSITIONAL_SOUND,
        JUMP(BOMB_MECH_M7_BOSS_FIRE_BURST_RAMP_WAIT),
    },
    /* fire_burst_ramp_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_RAMP_DISPATCH, BOMB_MECH_M7_BOSS_FIRE_SOUND,
        JUMP(BOMB_MECH_M7_BOSS_FIRE_BURST_RAMP_WAIT),
    },
    /* fire_sound */ {
        BOMB_MECH_M7_BOSS_SOUND_START_A,
    },
    /* fire_muzzle */ {
        BOMB_MECH_M7_BOSS_SPAWN_MUZZLE_FLASH,
        BOMB_MECH_M7_BOSS_STORE_ENEMY_HALFWORD, 0, 6,
    },
    /* fire_burst_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_FIRE_BURST_END,
        BOMB_MECH_M7_BOSS_LOOP_NEXT, 0, BOMB_MECH_M7_BOSS_FIRE_BURST_WAIT,
        JUMP(BOMB_MECH_M7_BOSS_FIRE_MUZZLE),
    },
    /* fire_burst_end */ {
        LOOP(BOMB_MECH_M7_BOSS_FIRE_MUZZLE),
        BOMB_MECH_M7_BOSS_STOP_HELD_SOUND,
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* walk_start */ {
        BOMB_MECH_M7_BOSS_BRANCH_IF_FLAG, BOMB_MECH_M7_BOSS_WALK_END,
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_WALK),
        BOMB_MECH_M7_BOSS_SET_ENEMY_VAR, 8,
        WANDER(0),
        SET_SPEED(6),
        JUMP(BOMB_MECH_M7_BOSS_WALK_WAIT),
    },
    /* walk_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_WALK_END,
        JUMP(BOMB_MECH_M7_BOSS_WALK_WAIT),
    },
    /* walk_end */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_SET_TARGET_YAW, 1,
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* turn_to_target */ {
        BOMB_MECH_M7_BOSS_BRANCH_IF_FLAG, BOMB_MECH_M7_BOSS_TURN_WAIT_IDLE,
        JUMP(BOMB_MECH_M7_BOSS_TURN_DONE),
    },
    /* turn_wait_idle */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_TURN_START,
        JUMP(BOMB_MECH_M7_BOSS_TURN_WAIT_IDLE),
    },
    /* turn_start */ {
        NEXT_STATE(BOMB_MECH_M7_BOSS_STATE_TURN),
        JUMP(BOMB_MECH_M7_BOSS_TURN_WAIT),
    },
    /* turn_wait */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_CASE_MATCH, -1, BOMB_MECH_M7_BOSS_TURN_DONE,
        JUMP(BOMB_MECH_M7_BOSS_TURN_WAIT),
    },
    /* turn_done */ {
        WAIT(1),
        BOMB_MECH_M7_BOSS_SET_TARGET_YAW, 0,
        BOMB_MECH_M7_BOSS_SET_ENEMY_VAR, 0,
        WANDER(0),
        SET_SPEED(0),
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* player_below_check */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 67,
        BOMB_MECH_M7_BOSS_JUMP_IF_PLAYER_BELOW, BOMB_MECH_M7_BOSS_PLAYER_BEYOND_CHECK,
    },
    /* turn_to_player_check */ {
        BOMB_MECH_M7_BOSS_TURN_TO_PLAYER_JUMP, 512, BOMB_MECH_M7_BOSS_ATTACK_FIRE,
        JUMP(BOMB_MECH_M7_BOSS_ATTACK_CHOOSE_C),
    },
    /* player_beyond_check */ {
        BOMB_MECH_M7_BOSS_JUMP_IF_PLAYER_BEYOND, 600, BOMB_MECH_M7_BOSS_TURN_TO_PLAYER_CHECK,
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 61,
        JUMP(BOMB_MECH_M7_BOSS_TURN_THEN_BOMBS),
    },
    /* bombs_then_pause */ {
        JUMP(BOMB_MECH_M7_BOSS_WALK_THEN_PAUSE),
    },
    /* attack_fire */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 63,
        JUMP(BOMB_MECH_M7_BOSS_WALK_THEN_FIRE),
    },
    /* attack_choose_a */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 64,
        BOMB_MECH_M7_BOSS_ROLL_SET,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 1024, BOMB_MECH_M7_BOSS_TURN_THEN_FLY,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 2048, BOMB_MECH_M7_BOSS_TURN_THEN_HOP,
        JUMP(BOMB_MECH_M7_BOSS_ATTACK_RETURN),
    },
    /* attack_choose_b */ {
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 1024, BOMB_MECH_M7_BOSS_ATTACK_RETURN,
        BOMB_MECH_M7_BOSS_ROLL_SET,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 1024, BOMB_MECH_M7_BOSS_TURN_THEN_BOMBS,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 2048, BOMB_MECH_M7_BOSS_TURN_THEN_FLY,
        JUMP(BOMB_MECH_M7_BOSS_ATTACK_RETURN),
    },
    /* attack_choose_c */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 66,
        BOMB_MECH_M7_BOSS_ROLL_SET,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 1024, BOMB_MECH_M7_BOSS_TURN_THEN_FLY,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 2048, BOMB_MECH_M7_BOSS_TURN_THEN_HOP,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 3072, BOMB_MECH_M7_BOSS_WALK_THEN_PAUSE,
        JUMP(BOMB_MECH_M7_BOSS_TURN_THEN_BOMBS),
    },
    /* attack_choose_d */ {
        BOMB_MECH_M7_BOSS_TURN_TO_PLAYER_JUMP, 512, BOMB_MECH_M7_BOSS_ATTACK_FIRE,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 512, BOMB_MECH_M7_BOSS_WALK_THEN_PAUSE,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 1024, BOMB_MECH_M7_BOSS_TURN_THEN_BOMBS,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 1536, BOMB_MECH_M7_BOSS_WALK_THEN_PAUSE,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 2048, BOMB_MECH_M7_BOSS_TURN_THEN_FLY,
        BOMB_MECH_M7_BOSS_ROLL_SET,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 512, BOMB_MECH_M7_BOSS_TURN_THEN_BOMBS,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 2048, BOMB_MECH_M7_BOSS_TURN_THEN_HOP,
        JUMP(BOMB_MECH_M7_BOSS_WALK_THEN_PAUSE),
    },
    /* attack_return */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* scan_far */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 74,
    },
    /* aim_check */ {
        BOMB_MECH_M7_BOSS_TURN_TO_PLAYER_JUMP, 512, BOMB_MECH_M7_BOSS_AIM_JITTER,
        JUMP(BOMB_MECH_M7_BOSS_ATTACK_CHOOSE_F),
    },
    /* aim_jitter */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 71,
        JUMP(BOMB_MECH_M7_BOSS_WALK_THEN_JITTER),
    },
    /* attack_choose_e */ {
        BOMB_MECH_M7_BOSS_ROLL_SET,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 1024, BOMB_MECH_M7_BOSS_WALK_THEN_PAUSE,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 2048, BOMB_MECH_M7_BOSS_TURN_THEN_HOP,
        JUMP(BOMB_MECH_M7_BOSS_TURN_THEN_FLY),
    },
    /* attack_choose_f */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 73,
        BOMB_MECH_M7_BOSS_ROLL_SET,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 1024, BOMB_MECH_M7_BOSS_TURN_THEN_BOMBS,
        BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL, 2048, BOMB_MECH_M7_BOSS_TURN_THEN_HOP,
        JUMP(BOMB_MECH_M7_BOSS_TURN_THEN_FLY),
    },
    /* attack_f_return */ {
        JUMP(BOMB_MECH_M7_BOSS_WALK_THEN_PAUSE),
    },
    /* far_return */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* walk_then_pause */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 76,
        JUMP(BOMB_MECH_M7_BOSS_WALK_START),
    },
    /* pause_return */ {
        WAIT(90),
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP,
    },
    /* player_scan */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 77,
        BOMB_MECH_M7_BOSS_JUMP_IF_PLAYER_WITHIN, 2000, BOMB_MECH_M7_BOSS_PLAYER_BELOW_CHECK,
        JUMP(BOMB_MECH_M7_BOSS_SCAN_FAR),
    },
    /* turn_then_scan */ {
        BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH, 77,
        JUMP(BOMB_MECH_M7_BOSS_TURN_TO_TARGET),
    },
    /* table */ {
        bomb_mech_m7_boss_scripts.init, bomb_mech_m7_boss_scripts.init_resume, bomb_mech_m7_boss_scripts.init_wait, bomb_mech_m7_boss_scripts.init_wait_loop, bomb_mech_m7_boss_scripts.init_emerge, bomb_mech_m7_boss_scripts.init_emerge_wait,
        bomb_mech_m7_boss_scripts.init_return, bomb_mech_m7_boss_scripts.turn_then_hop, bomb_mech_m7_boss_scripts.hop_crouch, bomb_mech_m7_boss_scripts.hop_crouch_wait, bomb_mech_m7_boss_scripts.hop_spawn_parts, bomb_mech_m7_boss_scripts.hop_spawn_wait,
        bomb_mech_m7_boss_scripts.hop_launch, bomb_mech_m7_boss_scripts.hop_rise_wait, bomb_mech_m7_boss_scripts.hop_fall, bomb_mech_m7_boss_scripts.hop_check, bomb_mech_m7_boss_scripts.hop_land, bomb_mech_m7_boss_scripts.hop_land_wait,
        bomb_mech_m7_boss_scripts.hop_shoot, bomb_mech_m7_boss_scripts.hop_return, bomb_mech_m7_boss_scripts.turn_then_fly, bomb_mech_m7_boss_scripts.fly_prepare, bomb_mech_m7_boss_scripts.fly_prepare_wait, bomb_mech_m7_boss_scripts.fly_start,
        bomb_mech_m7_boss_scripts.fly_emit_loop, bomb_mech_m7_boss_scripts.fly_hold, bomb_mech_m7_boss_scripts.fly_end, bomb_mech_m7_boss_scripts.fly_end_wait, bomb_mech_m7_boss_scripts.fly_return, bomb_mech_m7_boss_scripts.turn_then_bombs,
        bomb_mech_m7_boss_scripts.bomb_run_start, bomb_mech_m7_boss_scripts.bomb_pass, bomb_mech_m7_boss_scripts.bomb_pass_wait, bomb_mech_m7_boss_scripts.bomb_drop, bomb_mech_m7_boss_scripts.bomb_drop_wait, bomb_mech_m7_boss_scripts.bomb_pass_loop,
        bomb_mech_m7_boss_scripts.walk_then_jitter, bomb_mech_m7_boss_scripts.jitter_start, bomb_mech_m7_boss_scripts.jitter_frame, bomb_mech_m7_boss_scripts.jitter_wait, bomb_mech_m7_boss_scripts.jitter_end, bomb_mech_m7_boss_scripts.timer_wait,
        bomb_mech_m7_boss_scripts.timer_return, bomb_mech_m7_boss_scripts.walk_then_fire, bomb_mech_m7_boss_scripts.fire_burst_start, bomb_mech_m7_boss_scripts.fire_burst_ramp_wait, bomb_mech_m7_boss_scripts.fire_sound, bomb_mech_m7_boss_scripts.fire_muzzle,
        bomb_mech_m7_boss_scripts.fire_burst_wait, bomb_mech_m7_boss_scripts.fire_burst_end, bomb_mech_m7_boss_scripts.walk_start, bomb_mech_m7_boss_scripts.walk_wait, bomb_mech_m7_boss_scripts.walk_end, bomb_mech_m7_boss_scripts.turn_to_target,
        bomb_mech_m7_boss_scripts.turn_wait_idle, bomb_mech_m7_boss_scripts.turn_start, bomb_mech_m7_boss_scripts.turn_wait, bomb_mech_m7_boss_scripts.turn_done, bomb_mech_m7_boss_scripts.player_below_check, bomb_mech_m7_boss_scripts.turn_to_player_check,
        bomb_mech_m7_boss_scripts.player_beyond_check, bomb_mech_m7_boss_scripts.bombs_then_pause, bomb_mech_m7_boss_scripts.attack_fire, bomb_mech_m7_boss_scripts.attack_choose_a, bomb_mech_m7_boss_scripts.attack_choose_b, bomb_mech_m7_boss_scripts.attack_choose_c,
        bomb_mech_m7_boss_scripts.attack_choose_d, bomb_mech_m7_boss_scripts.attack_return, bomb_mech_m7_boss_scripts.scan_far, bomb_mech_m7_boss_scripts.aim_check, bomb_mech_m7_boss_scripts.aim_jitter, bomb_mech_m7_boss_scripts.attack_choose_e,
        bomb_mech_m7_boss_scripts.attack_choose_f, bomb_mech_m7_boss_scripts.attack_f_return, bomb_mech_m7_boss_scripts.far_return, bomb_mech_m7_boss_scripts.walk_then_pause, bomb_mech_m7_boss_scripts.pause_return, bomb_mech_m7_boss_scripts.player_scan,
        bomb_mech_m7_boss_scripts.turn_then_scan,
    },
    /* D_8011DEA4 */ (u32)bomb_mech_m7_boss_scripts.init,
};

u32 D_8011DEA8[36] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000000, 0x00000003,
    0x00000000, 0x00000004, 0x00000000, 0x00000005, 0x00000000, 0x00000006,
    0x00000000, 0x00000011, 0x00000000, 0x00000002, 0x00000000, 0x00000002,
    0x00000000, 0x00000002, 0x00000000, 0x00000007, 0x00000000, 0x00000009,
    0x00000000, 0x0000000B, 0x00000000, 0x0000000D, 0x00000000, 0x0000000E,
    0x00000000, 0x0000000F, 0x00000000, 0x00000010, 0x00000000, 0x00000012,
};

s16 hit_mask_weights[8] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
};

Keyframe sfx_keyframes[8] = {
    {0x40, 0x125}, {-1, 0x124}, {6, 0x110}, {6, 0x111}, {-1, 0x112}, {8, 0x118}, {8, 0x119},
    {-1, 0x119},
};

FxRecordParams sfx_emitter_params = {0, 0x80, 0x80, 0x80, 0, 0x60, {0, 0x28000, -0x1000, 0x10000}};

Keyframe spark_keyframe_path[7] = {
    {6, 0x108}, {6, 0x109}, {6, 0x10A}, {6, 0x10B}, {6, 0x10C}, {-1, 0x10C}, {0, 0},
};

Keyframe keyframe_table_alt[4] = {
    {4, 0x138}, {4, 0x139}, {4, 0x13A}, {-1, 0x13A},
};

Keyframe keyframe_table_default[4] = {
    {4, 0x140}, {4, 0x141}, {4, 0x142}, {-1, 0x142},
};

Keyframe keyframe_list[2] = {
    {0x60, 0x148}, {-1, 0x149},
};

s32 model_part_slots[5] = {
    0, 1, 2, 3, -1,
};

s32 keyframe_spawn_enabled = 0;

s16 cam_shake_nudges[18] = {
    3, 0, 3, 0, 2, 0, 2, 0,
    1, 0, 1, 0, -1, 0, 0x800, 0x800,
    0x800, 0,
};

SVECTOR fade_target_color = {0, 0x80, 0x400, 0};

s32 fly_active = 0;

s32 fx_stop_flag = 0;

s32 fly_emit_timer = 0;

s32 debris_active = 0;

s32 debris_stopped = 0;

s32 debris_spawn_timer = 0;

s32 debris_angle = 0;

FxRecordParams fly_spark_params = {0, 0x40, 0x40, 0x40, 0x200, 0x40, {0x800000, 0, 0, 0}};

u32 D_8011E03C[4] = {
    0x01280004, 0x01290004, 0x012A0004, 0x012BFFFF,
};

Keyframe D_8011E04C[2] = {
    {0x10, 0x131}, {-1, 0x130},
};

#include "../stage/data/fade_red_fx_template.c"

RecTemplate fx_owner_template_a = {3, 0xFF, 0xFF, 0xFF, 0, 0x14, 0x80000, 0x60000, -0x100, 0x40000};

#include "../stage/data/fx_owner_template_b.c"

#include "../stage/data/fx_rec34_params.c"

s32 D_8011E0B4[4] = {
    -1, -1, -1, 3,
};

s32 clamp_table[8] = {
    0, -0x2800, 0, 1, 0, 0,
    0, 0,
};

ClampTable area_clamp_table_set = {{-0xE40, -0x2800, -0x4260, 1, 0xDE0, 0, -0x2880, 0}};

u32 D_8011E104[3] = {
    0xFFFFC2E0, 0xFFFFD800, 0xFFFFB4A0,
};

s32 area_capture_state[5] = {
    1, 0x2DC0, 0, 0x2400, 0,
};

SoundPos area_sound_slots[4] = {
    {{0xBE8000, 0, 0x170C000}, (s32)0xD2A0D2A1},
    {{(s32)0xFE124000, 0, 0x20DF000}, (s32)0xD2A4D2A5},
    {{0x1D33000, 0, (s32)0xFD34B000}, (s32)0xD2A6D2A7},
    {{0, 0, 0}, -1},
};

ScanEntry D_8011E164 = {{0, (s32)scene_spawn}, D_8011E0B4, 0, 0, 0};

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

u8 *msgs_file_names[3] = {
    msgs_spr_clt_name, msgs_spr_grc_name, msgs_spr_so3_name,
};

ScanEntry enemy_msgs_scan_entry = {{(s32)mission_state_reset, 0}, d_80117914, 0, 0, (s32)msgs_file_names};

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_80122D90[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/video_mode_id.c"

#include "../stage/data/tint_scale_r.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_80123F14[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_80124534 = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

#include "../stage/data/model_pchr_saved.c"

s32 area_bounds_x0 = 0;

s32 area_bounds_x1 = 0;

s32 area_bounds_z0 = 0;

s32 area_bounds_z1 = 0;

s32 area_center_x = 0;

s32 area_center_z = 0;

#include "../stage/data/value_queue_index.c"

s32 bomb_mech_m7_boss_active = 0;

s32 D_80125970 = 0;

s32 keyframe_spawn_timer = 0;

s32 keyframe_spawn_index = 0;

s32 keyframe_spawn_owner = 0;

s32 fx_owner_obj = 0;

#include "../stage/data/fade_red_obj.c"

s32 area_ambient_sound = 0;

s32 area_capture_count = 0;

s32 area_capture_final_flag = 0;

s32 area_capture_complete_flag = 0;

s32 *area_target_ptr = NULL;

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

#include "../stage/data/frame_work_area.c"

#include "../stage/data/model_slot_count.c"

u32 D_80125A94 = 0x00000000;

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

u32 D_80125B18 = 0x00000000;

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

#include "../stage/data/interp_enabled_flag.c"

#include "../stage/data/interp_record_count.c"

#include "../stage/data/interp1c_count.c"

#include "../stage/data/interp2c_count.c"

#include "../stage/data/interp38_count.c"

#include "../stage/data/interp38b_count.c"

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

s32 rocket_shot_params = 0;

s32 D_80125FAC = 0;

s32 D_80125FB0 = 0;

s16 D_80125FB4 = 0;

s16 rocket_shot_hit_effect_index = 0;

s16 D_80125FB8 = 0;

s16 D_80125FBA = 0;

s16 D_80125FBC = 0;

s16 D_80125FBE = 0;

s16 D_80125FC0 = 0;

s16 D_80125FC2 = 0;

s16 D_80125FC4 = 0;

s16 D_80125FC6 = 0;

s16 D_80125FC8 = 0;

s16 D_80125FCA = 0;

ShotParams shot_params = {0};

s16 value_queue[8] = {0};

/* labels inside the objects above */
__asm__(".globl D_8011CA9F\n.set D_8011CA9F, ground_shadow_params+0x3\n"
        ".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl texture_image_height\n.set texture_image_height, texture_image+0x2\n"
        ".globl pad1_pressed\n.set pad1_pressed, pad1+0x2\n"
        ".globl scale_vec_y\n.set scale_vec_y, scale_vec+0x2\n"
        ".globl D_8011CA9E\n.set D_8011CA9E, ground_shadow_params+0x2\n"
        ".globl D_8011CA9D\n.set D_8011CA9D, ground_shadow_params+0x1\n"
        ".globl walker_death_scripts_alt\n.set walker_death_scripts_alt, walker_anims+0x80\n"
        ".globl D_8011CAA4\n.set D_8011CAA4, ground_shadow_params+0x8\n"
        ".globl d_80118574\n.set d_80118574, ground_shadow_params+0xC\n"
        ".globl fade_target_vy\n.set fade_target_vy, fade_target_color+0x2\n"
        ".globl fade_target_vz\n.set fade_target_vz, fade_target_color+0x4\n"
        ".globl D_8011E0D0\n.set D_8011E0D0, clamp_table+0xC\n"
        ".globl D_8011E0D4\n.set D_8011E0D4, clamp_table+0x10\n"
        ".globl area_sound_first_id\n.set area_sound_first_id, area_sound_slots+0xC\n"
        ".globl sincos_deg90\n.set sincos_deg90, rcossin_tbl+0x1000\n"
        ".globl fuchikoma_state_table_s12\n.set fuchikoma_state_table_s12, rcossin_tbl+0x1100\n"
        ".globl view_sincos\n.set view_sincos, rcossin_tbl+0x2000\n"
        ".globl sincos_deg270\n.set sincos_deg270, rcossin_tbl+0x3000\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n"
        ".globl view_nudge_y\n.set view_nudge_y, view_nudge+0x2\n"
        ".globl d_801201AE\n.set d_801201AE, flow+0x2\n"
        ".globl flow_angle\n.set flow_angle, flow+0x4\n"
        ".globl D_80125FD0\n.set D_80125FD0, shot_params+0x4\n"
        ".globl shot_speed_delta\n.set shot_speed_delta, shot_params+0x8\n"
        ".globl grenade_saved_param\n.set grenade_saved_param, shot_params+0xC\n"
        ".globl shot_hit_effect_index\n.set shot_hit_effect_index, shot_params+0xE\n"
        ".globl D_80125FDC\n.set D_80125FDC, shot_params+0x10\n"
        ".globl D_80125FDE\n.set D_80125FDE, shot_params+0x12\n"
        ".globl D_80125FE0\n.set D_80125FE0, shot_params+0x14\n"
        ".globl D_80125FE2\n.set D_80125FE2, shot_params+0x16\n"
        ".globl D_80125FE4\n.set D_80125FE4, shot_params+0x18\n"
        ".globl D_80125FE6\n.set D_80125FE6, shot_params+0x1A\n"
        ".globl D_80125FE8\n.set D_80125FE8, shot_params+0x1C\n"
        ".globl D_80125FEA\n.set D_80125FEA, shot_params+0x1E\n"
        ".globl D_80125FEC\n.set D_80125FEC, shot_params+0x20\n"
        ".globl D_80125FEE\n.set D_80125FEE, shot_params+0x22\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl stationary_rocket_launcher_anim_idle\n.set stationary_rocket_launcher_anim_idle, stationary_rocket_launcher_anims+0x0\n"
        ".globl stationary_rocket_launcher_data\n.set stationary_rocket_launcher_data, stationary_rocket_launcher_anims+0x8\n"
        ".globl stationary_rocket_launcher_idle\n.set stationary_rocket_launcher_idle, stationary_rocket_launcher_scripts+0x0\n"
        ".globl stationary_rocket_launcher_track\n.set stationary_rocket_launcher_track, stationary_rocket_launcher_scripts+0x10\n"
        ".globl stationary_rocket_launcher_aim\n.set stationary_rocket_launcher_aim, stationary_rocket_launcher_scripts+0x14\n"
        ".globl stationary_rocket_launcher_lock_on\n.set stationary_rocket_launcher_lock_on, stationary_rocket_launcher_scripts+0x28\n"
        ".globl stationary_rocket_launcher_fire_start\n.set stationary_rocket_launcher_fire_start, stationary_rocket_launcher_scripts+0x34\n"
        ".globl stationary_rocket_launcher_fire_loop\n.set stationary_rocket_launcher_fire_loop, stationary_rocket_launcher_scripts+0x38\n"
        ".globl stationary_rocket_launcher_launch_start\n.set stationary_rocket_launcher_launch_start, stationary_rocket_launcher_scripts+0x48\n"
        ".globl stationary_rocket_launcher_launch_loop\n.set stationary_rocket_launcher_launch_loop, stationary_rocket_launcher_scripts+0x4C\n"
        ".globl rocket_launcher_script\n.set rocket_launcher_script, stationary_rocket_launcher_scripts+0x5C\n"
        ".globl rocket_launcher_anim_link\n.set rocket_launcher_anim_link, stationary_rocket_launcher_scripts+0x7C\n"
        ".globl enemy_fuchikoma_b_anim_idle\n.set enemy_fuchikoma_b_anim_idle, enemy_fuchikoma_b_anims+0x0\n"
        ".globl enemy_fuchikoma_b_anim_walk\n.set enemy_fuchikoma_b_anim_walk, enemy_fuchikoma_b_anims+0x8\n"
        ".globl enemy_fuchikoma_b_data\n.set enemy_fuchikoma_b_data, enemy_fuchikoma_b_anims+0x3C\n"
        ".globl enemy_fuchikoma_b_idle\n.set enemy_fuchikoma_b_idle, enemy_fuchikoma_b_scripts+0x0\n"
        ".globl enemy_fuchikoma_b_start\n.set enemy_fuchikoma_b_start, enemy_fuchikoma_b_scripts+0xC\n"
        ".globl enemy_fuchikoma_b_accelerate\n.set enemy_fuchikoma_b_accelerate, enemy_fuchikoma_b_scripts+0x1C\n"
        ".globl enemy_fuchikoma_b_wait_trigger\n.set enemy_fuchikoma_b_wait_trigger, enemy_fuchikoma_b_scripts+0x30\n"
        ".globl enemy_fuchikoma_b_chase_start\n.set enemy_fuchikoma_b_chase_start, enemy_fuchikoma_b_scripts+0x3C\n"
        ".globl enemy_fuchikoma_b_search\n.set enemy_fuchikoma_b_search, enemy_fuchikoma_b_scripts+0x48\n"
        ".globl enemy_fuchikoma_b_engage\n.set enemy_fuchikoma_b_engage, enemy_fuchikoma_b_scripts+0x5C\n"
        ".globl enemy_fuchikoma_b_aim\n.set enemy_fuchikoma_b_aim, enemy_fuchikoma_b_scripts+0x60\n"
        ".globl enemy_fuchikoma_b_corner_check\n.set enemy_fuchikoma_b_corner_check, enemy_fuchikoma_b_scripts+0x88\n"
        ".globl enemy_fuchikoma_b_corner_turn\n.set enemy_fuchikoma_b_corner_turn, enemy_fuchikoma_b_scripts+0x98\n"
        ".globl enemy_fuchikoma_b_await_mode\n.set enemy_fuchikoma_b_await_mode, enemy_fuchikoma_b_scripts+0x9C\n"
        ".globl enemy_fuchikoma_b_death_wait\n.set enemy_fuchikoma_b_death_wait, enemy_fuchikoma_b_scripts+0xAC\n"
        ".globl enemy_fuchikoma_b_death\n.set enemy_fuchikoma_b_death, enemy_fuchikoma_b_scripts+0xB8\n"
        ".globl enemy_fuchikoma_b_await_chase\n.set enemy_fuchikoma_b_await_chase, enemy_fuchikoma_b_scripts+0xC0\n"
        ".globl fuchikoma_link_data\n.set fuchikoma_link_data, enemy_fuchikoma_b_scripts+0xD0\n"
        ".globl fuchikoma_anim_link\n.set fuchikoma_anim_link, enemy_fuchikoma_b_scripts+0x108\n"
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
        ".globl helicopter_2_script_cfg\n.set helicopter_2_script_cfg, helicopter_2_script_anims+0x0\n"
        ".globl helicopter_2_data\n.set helicopter_2_data, helicopter_2_script_anims+0x8\n"
        ".globl helicopter2_think\n.set helicopter2_think, helicopter2_scripts+0x0\n"
        ".globl helicopter2_select\n.set helicopter2_select, helicopter2_scripts+0x4\n"
        ".globl helicopter2_patrol\n.set helicopter2_patrol, helicopter2_scripts+0x28\n"
        ".globl helicopter2_cruise\n.set helicopter2_cruise, helicopter2_scripts+0x38\n"
        ".globl helicopter2_bank_turn\n.set helicopter2_bank_turn, helicopter2_scripts+0x48\n"
        ".globl helicopter2_attack\n.set helicopter2_attack, helicopter2_scripts+0x58\n"
        ".globl helicopter2_hover\n.set helicopter2_hover, helicopter2_scripts+0x68\n"
        ".globl helicopter2_hold_start\n.set helicopter2_hold_start, helicopter2_scripts+0x78\n"
        ".globl helicopter2_hold_loop\n.set helicopter2_hold_loop, helicopter2_scripts+0x80\n"
        ".globl helicopter2_cycle_end\n.set helicopter2_cycle_end, helicopter2_scripts+0x8C\n"
        ".globl helicopter2_script_data\n.set helicopter2_script_data, helicopter2_scripts+0x94\n"
        ".globl helicopter2_script_entry\n.set helicopter2_script_entry, helicopter2_scripts+0xBC\n"
        ".globl tank_2_anim_idle\n.set tank_2_anim_idle, tank_2_anims+0x0\n"
        ".globl tank_2_data\n.set tank_2_data, tank_2_anims+0x8\n"
        ".globl tank_2_init\n.set tank_2_init, tank_2_scripts+0x0\n"
        ".globl tank_2_patrol_start\n.set tank_2_patrol_start, tank_2_scripts+0x14\n"
        ".globl tank_2_patrol\n.set tank_2_patrol, tank_2_scripts+0x20\n"
        ".globl tank_2_stop\n.set tank_2_stop, tank_2_scripts+0x38\n"
        ".globl tank_2_stop_wait\n.set tank_2_stop_wait, tank_2_scripts+0x3C\n"
        ".globl tank_2_spotted\n.set tank_2_spotted, tank_2_scripts+0x4C\n"
        ".globl tank_2_chase\n.set tank_2_chase, tank_2_scripts+0x54\n"
        ".globl tank_2_engage\n.set tank_2_engage, tank_2_scripts+0x74\n"
        ".globl tank_2_aim\n.set tank_2_aim, tank_2_scripts+0x88\n"
        ".globl tank_2_turn_to_player\n.set tank_2_turn_to_player, tank_2_scripts+0xA4\n"
        ".globl tank_2_turn_wait\n.set tank_2_turn_wait, tank_2_scripts+0xB0\n"
        ".globl tank_2_face_wait\n.set tank_2_face_wait, tank_2_scripts+0xC8\n"
        ".globl tank_2_halt\n.set tank_2_halt, tank_2_scripts+0xD4\n"
        ".globl tank_2_fire_ready\n.set tank_2_fire_ready, tank_2_scripts+0xD8\n"
        ".globl tank_2_fire_start\n.set tank_2_fire_start, tank_2_scripts+0xE8\n"
        ".globl tank_2_fire_loop\n.set tank_2_fire_loop, tank_2_scripts+0xF0\n"
        ".globl tank_2_fire_cooldown\n.set tank_2_fire_cooldown, tank_2_scripts+0x100\n"
        ".globl tank_2_static_init\n.set tank_2_static_init, tank_2_scripts+0x10C\n"
        ".globl tank_2_static_watch\n.set tank_2_static_watch, tank_2_scripts+0x118\n"
        ".globl tank_2_static_spotted\n.set tank_2_static_spotted, tank_2_scripts+0x128\n"
        ".globl tank_2_static_chase\n.set tank_2_static_chase, tank_2_scripts+0x12C\n"
        ".globl tank_2_static_engage\n.set tank_2_static_engage, tank_2_scripts+0x140\n"
        ".globl tank_2_static_aim\n.set tank_2_static_aim, tank_2_scripts+0x150\n"
        ".globl tank_2_static_turn_to_player\n.set tank_2_static_turn_to_player, tank_2_scripts+0x168\n"
        ".globl tank_2_static_turn_wait\n.set tank_2_static_turn_wait, tank_2_scripts+0x170\n"
        ".globl tank_2_static_face_wait\n.set tank_2_static_face_wait, tank_2_scripts+0x188\n"
        ".globl tank_2_static_fire_start\n.set tank_2_static_fire_start, tank_2_scripts+0x194\n"
        ".globl tank_2_static_fire_loop\n.set tank_2_static_fire_loop, tank_2_scripts+0x19C\n"
        ".globl tank_2_static_fire_cooldown\n.set tank_2_static_fire_cooldown, tank_2_scripts+0x1AC\n"
        ".globl tank_2_pursue_watch\n.set tank_2_pursue_watch, tank_2_scripts+0x1B8\n"
        ".globl tank_2_pursue_spotted\n.set tank_2_pursue_spotted, tank_2_scripts+0x1C8\n"
        ".globl tank_2_pursue_chase\n.set tank_2_pursue_chase, tank_2_scripts+0x1CC\n"
        ".globl tank_2_pursue_angle_check\n.set tank_2_pursue_angle_check, tank_2_scripts+0x1E0\n"
        ".globl tank_2_pursue_turn_to_player\n.set tank_2_pursue_turn_to_player, tank_2_scripts+0x1E8\n"
        ".globl tank_2_pursue_turn_wait\n.set tank_2_pursue_turn_wait, tank_2_scripts+0x1F0\n"
        ".globl tank_2_pursue_face_wait\n.set tank_2_pursue_face_wait, tank_2_scripts+0x208\n"
        ".globl tank2_link_data\n.set tank2_link_data, tank_2_scripts+0x214\n"
        ".globl tank2_variant_words\n.set tank2_variant_words, tank_2_scripts+0x2A4\n"
        ".globl gun_turret_2_pose\n.set gun_turret_2_pose, gun_turret_2_anims+0x0\n"
        ".globl gun_turret_2_data\n.set gun_turret_2_data, gun_turret_2_anims+0x8\n"
        ".globl gun_turret_2_idle\n.set gun_turret_2_idle, gun_turret_2_scripts+0x0\n"
        ".globl gun_turret_2_spotted\n.set gun_turret_2_spotted, gun_turret_2_scripts+0x10\n"
        ".globl gun_turret_2_tracking\n.set gun_turret_2_tracking, gun_turret_2_scripts+0x14\n"
        ".globl gun_turret_2_aimed\n.set gun_turret_2_aimed, gun_turret_2_scripts+0x24\n"
        ".globl gun_turret_2_open_fire\n.set gun_turret_2_open_fire, gun_turret_2_scripts+0x34\n"
        ".globl gun_turret_2_firing\n.set gun_turret_2_firing, gun_turret_2_scripts+0x38\n"
        ".globl gun_turret_2_cooldown\n.set gun_turret_2_cooldown, gun_turret_2_scripts+0x48\n"
        ".globl gun_turret_2_cooling\n.set gun_turret_2_cooling, gun_turret_2_scripts+0x50\n"
        ".globl gun_turret_2_link_data\n.set gun_turret_2_link_data, gun_turret_2_scripts+0x60\n"
        ".globl gun_turret_2_script_pos\n.set gun_turret_2_script_pos, gun_turret_2_scripts+0x80\n"
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
        ".globl bomb_mech_m7_boss_anim_idle\n.set bomb_mech_m7_boss_anim_idle, bomb_mech_m7_boss_anims+0x0\n"
        ".globl bomb_mech_m7_boss_anim_walk_start\n.set bomb_mech_m7_boss_anim_walk_start, bomb_mech_m7_boss_anims+0xC\n"
        ".globl bomb_mech_m7_boss_anim_walk\n.set bomb_mech_m7_boss_anim_walk, bomb_mech_m7_boss_anims+0x14\n"
        ".globl bomb_mech_m7_boss_anim_turn\n.set bomb_mech_m7_boss_anim_turn, bomb_mech_m7_boss_anims+0x60\n"
        ".globl bomb_mech_m7_boss_anim_hide_start\n.set bomb_mech_m7_boss_anim_hide_start, bomb_mech_m7_boss_anims+0x6C\n"
        ".globl bomb_mech_m7_boss_anim_hide\n.set bomb_mech_m7_boss_anim_hide, bomb_mech_m7_boss_anims+0x74\n"
        ".globl bomb_mech_m7_boss_anim_emerge\n.set bomb_mech_m7_boss_anim_emerge, bomb_mech_m7_boss_anims+0x7C\n"
        ".globl bomb_mech_m7_boss_anim_crouch\n.set bomb_mech_m7_boss_anim_crouch, bomb_mech_m7_boss_anims+0x9C\n"
        ".globl bomb_mech_m7_boss_anim_hop_launch\n.set bomb_mech_m7_boss_anim_hop_launch, bomb_mech_m7_boss_anims+0xBC\n"
        ".globl bomb_mech_m7_boss_anim_hop_rise\n.set bomb_mech_m7_boss_anim_hop_rise, bomb_mech_m7_boss_anims+0xD8\n"
        ".globl bomb_mech_m7_boss_anim_hop_rise_hold\n.set bomb_mech_m7_boss_anim_hop_rise_hold, bomb_mech_m7_boss_anims+0x104\n"
        ".globl bomb_mech_m7_boss_anim_hop_fall\n.set bomb_mech_m7_boss_anim_hop_fall, bomb_mech_m7_boss_anims+0x10C\n"
        ".globl bomb_mech_m7_boss_anim_hop_fall_hold\n.set bomb_mech_m7_boss_anim_hop_fall_hold, bomb_mech_m7_boss_anims+0x114\n"
        ".globl bomb_mech_m7_boss_anim_hop_land\n.set bomb_mech_m7_boss_anim_hop_land, bomb_mech_m7_boss_anims+0x11C\n"
        ".globl bomb_mech_m7_boss_anim_fly_prepare\n.set bomb_mech_m7_boss_anim_fly_prepare, bomb_mech_m7_boss_anims+0x144\n"
        ".globl bomb_mech_m7_boss_anim_fly_hold\n.set bomb_mech_m7_boss_anim_fly_hold, bomb_mech_m7_boss_anims+0x18C\n"
        ".globl bomb_mech_m7_boss_anim_fly_end\n.set bomb_mech_m7_boss_anim_fly_end, bomb_mech_m7_boss_anims+0x194\n"
        ".globl bomb_mech_m7_boss_anim_bomb_run\n.set bomb_mech_m7_boss_anim_bomb_run, bomb_mech_m7_boss_anims+0x1D8\n"
        ".globl bomb_mech_m7_boss_anim_jitter\n.set bomb_mech_m7_boss_anim_jitter, bomb_mech_m7_boss_anims+0x1E8\n"
        ".globl bomb_mech_m7_boss_anim_jitter_wrap\n.set bomb_mech_m7_boss_anim_jitter_wrap, bomb_mech_m7_boss_anims+0x20C\n"
        ".globl bomb_mech_m7_boss_data\n.set bomb_mech_m7_boss_data, bomb_mech_m7_boss_anims+0x214\n"
        ".globl bomb_mech_m7_boss_init\n.set bomb_mech_m7_boss_init, bomb_mech_m7_boss_scripts+0x0\n"
        ".globl bomb_mech_m7_boss_init_resume\n.set bomb_mech_m7_boss_init_resume, bomb_mech_m7_boss_scripts+0x14\n"
        ".globl bomb_mech_m7_boss_init_wait\n.set bomb_mech_m7_boss_init_wait, bomb_mech_m7_boss_scripts+0x18\n"
        ".globl bomb_mech_m7_boss_init_wait_loop\n.set bomb_mech_m7_boss_init_wait_loop, bomb_mech_m7_boss_scripts+0x1C\n"
        ".globl bomb_mech_m7_boss_init_emerge\n.set bomb_mech_m7_boss_init_emerge, bomb_mech_m7_boss_scripts+0x28\n"
        ".globl bomb_mech_m7_boss_init_emerge_wait\n.set bomb_mech_m7_boss_init_emerge_wait, bomb_mech_m7_boss_scripts+0x40\n"
        ".globl bomb_mech_m7_boss_init_return\n.set bomb_mech_m7_boss_init_return, bomb_mech_m7_boss_scripts+0x50\n"
        ".globl bomb_mech_m7_boss_turn_then_hop\n.set bomb_mech_m7_boss_turn_then_hop, bomb_mech_m7_boss_scripts+0x54\n"
        ".globl bomb_mech_m7_boss_hop_crouch\n.set bomb_mech_m7_boss_hop_crouch, bomb_mech_m7_boss_scripts+0x5C\n"
        ".globl bomb_mech_m7_boss_hop_crouch_wait\n.set bomb_mech_m7_boss_hop_crouch_wait, bomb_mech_m7_boss_scripts+0x70\n"
        ".globl bomb_mech_m7_boss_hop_spawn_parts\n.set bomb_mech_m7_boss_hop_spawn_parts, bomb_mech_m7_boss_scripts+0x80\n"
        ".globl bomb_mech_m7_boss_hop_spawn_wait\n.set bomb_mech_m7_boss_hop_spawn_wait, bomb_mech_m7_boss_scripts+0x88\n"
        ".globl bomb_mech_m7_boss_hop_launch\n.set bomb_mech_m7_boss_hop_launch, bomb_mech_m7_boss_scripts+0x98\n"
        ".globl bomb_mech_m7_boss_hop_rise_wait\n.set bomb_mech_m7_boss_hop_rise_wait, bomb_mech_m7_boss_scripts+0xAC\n"
        ".globl bomb_mech_m7_boss_hop_fall\n.set bomb_mech_m7_boss_hop_fall, bomb_mech_m7_boss_scripts+0xB8\n"
        ".globl bomb_mech_m7_boss_hop_check\n.set bomb_mech_m7_boss_hop_check, bomb_mech_m7_boss_scripts+0xC0\n"
        ".globl bomb_mech_m7_boss_hop_land\n.set bomb_mech_m7_boss_hop_land, bomb_mech_m7_boss_scripts+0xD0\n"
        ".globl bomb_mech_m7_boss_hop_land_wait\n.set bomb_mech_m7_boss_hop_land_wait, bomb_mech_m7_boss_scripts+0xEC\n"
        ".globl bomb_mech_m7_boss_hop_shoot\n.set bomb_mech_m7_boss_hop_shoot, bomb_mech_m7_boss_scripts+0xFC\n"
        ".globl bomb_mech_m7_boss_hop_return\n.set bomb_mech_m7_boss_hop_return, bomb_mech_m7_boss_scripts+0x108\n"
        ".globl bomb_mech_m7_boss_turn_then_fly\n.set bomb_mech_m7_boss_turn_then_fly, bomb_mech_m7_boss_scripts+0x10C\n"
        ".globl bomb_mech_m7_boss_fly_prepare\n.set bomb_mech_m7_boss_fly_prepare, bomb_mech_m7_boss_scripts+0x114\n"
        ".globl bomb_mech_m7_boss_fly_prepare_wait\n.set bomb_mech_m7_boss_fly_prepare_wait, bomb_mech_m7_boss_scripts+0x128\n"
        ".globl bomb_mech_m7_boss_fly_start\n.set bomb_mech_m7_boss_fly_start, bomb_mech_m7_boss_scripts+0x138\n"
        ".globl bomb_mech_m7_boss_fly_emit_loop\n.set bomb_mech_m7_boss_fly_emit_loop, bomb_mech_m7_boss_scripts+0x14C\n"
        ".globl bomb_mech_m7_boss_fly_hold\n.set bomb_mech_m7_boss_fly_hold, bomb_mech_m7_boss_scripts+0x160\n"
        ".globl bomb_mech_m7_boss_fly_end\n.set bomb_mech_m7_boss_fly_end, bomb_mech_m7_boss_scripts+0x16C\n"
        ".globl bomb_mech_m7_boss_fly_end_wait\n.set bomb_mech_m7_boss_fly_end_wait, bomb_mech_m7_boss_scripts+0x17C\n"
        ".globl bomb_mech_m7_boss_fly_return\n.set bomb_mech_m7_boss_fly_return, bomb_mech_m7_boss_scripts+0x18C\n"
        ".globl bomb_mech_m7_boss_turn_then_bombs\n.set bomb_mech_m7_boss_turn_then_bombs, bomb_mech_m7_boss_scripts+0x190\n"
        ".globl bomb_mech_m7_boss_bomb_run_start\n.set bomb_mech_m7_boss_bomb_run_start, bomb_mech_m7_boss_scripts+0x198\n"
        ".globl bomb_mech_m7_boss_bomb_pass\n.set bomb_mech_m7_boss_bomb_pass, bomb_mech_m7_boss_scripts+0x1AC\n"
        ".globl bomb_mech_m7_boss_bomb_pass_wait\n.set bomb_mech_m7_boss_bomb_pass_wait, bomb_mech_m7_boss_scripts+0x1B0\n"
        ".globl bomb_mech_m7_boss_bomb_drop\n.set bomb_mech_m7_boss_bomb_drop, bomb_mech_m7_boss_scripts+0x1C0\n"
        ".globl bomb_mech_m7_boss_bomb_drop_wait\n.set bomb_mech_m7_boss_bomb_drop_wait, bomb_mech_m7_boss_scripts+0x1C8\n"
        ".globl bomb_mech_m7_boss_bomb_pass_loop\n.set bomb_mech_m7_boss_bomb_pass_loop, bomb_mech_m7_boss_scripts+0x1D8\n"
        ".globl bomb_mech_m7_boss_walk_then_jitter\n.set bomb_mech_m7_boss_walk_then_jitter, bomb_mech_m7_boss_scripts+0x1E4\n"
        ".globl bomb_mech_m7_boss_jitter_start\n.set bomb_mech_m7_boss_jitter_start, bomb_mech_m7_boss_scripts+0x1EC\n"
        ".globl bomb_mech_m7_boss_jitter_frame\n.set bomb_mech_m7_boss_jitter_frame, bomb_mech_m7_boss_scripts+0x1F4\n"
        ".globl bomb_mech_m7_boss_jitter_wait\n.set bomb_mech_m7_boss_jitter_wait, bomb_mech_m7_boss_scripts+0x1FC\n"
        ".globl bomb_mech_m7_boss_jitter_end\n.set bomb_mech_m7_boss_jitter_end, bomb_mech_m7_boss_scripts+0x210\n"
        ".globl bomb_mech_m7_boss_timer_wait\n.set bomb_mech_m7_boss_timer_wait, bomb_mech_m7_boss_scripts+0x218\n"
        ".globl bomb_mech_m7_boss_timer_return\n.set bomb_mech_m7_boss_timer_return, bomb_mech_m7_boss_scripts+0x224\n"
        ".globl bomb_mech_m7_boss_walk_then_fire\n.set bomb_mech_m7_boss_walk_then_fire, bomb_mech_m7_boss_scripts+0x228\n"
        ".globl bomb_mech_m7_boss_fire_burst_start\n.set bomb_mech_m7_boss_fire_burst_start, bomb_mech_m7_boss_scripts+0x230\n"
        ".globl bomb_mech_m7_boss_fire_burst_ramp_wait\n.set bomb_mech_m7_boss_fire_burst_ramp_wait, bomb_mech_m7_boss_scripts+0x23C\n"
        ".globl bomb_mech_m7_boss_fire_sound\n.set bomb_mech_m7_boss_fire_sound, bomb_mech_m7_boss_scripts+0x248\n"
        ".globl bomb_mech_m7_boss_fire_muzzle\n.set bomb_mech_m7_boss_fire_muzzle, bomb_mech_m7_boss_scripts+0x24C\n"
        ".globl bomb_mech_m7_boss_fire_burst_wait\n.set bomb_mech_m7_boss_fire_burst_wait, bomb_mech_m7_boss_scripts+0x254\n"
        ".globl bomb_mech_m7_boss_fire_burst_end\n.set bomb_mech_m7_boss_fire_burst_end, bomb_mech_m7_boss_scripts+0x268\n"
        ".globl bomb_mech_m7_boss_walk_start\n.set bomb_mech_m7_boss_walk_start, bomb_mech_m7_boss_scripts+0x270\n"
        ".globl bomb_mech_m7_boss_walk_wait\n.set bomb_mech_m7_boss_walk_wait, bomb_mech_m7_boss_scripts+0x288\n"
        ".globl bomb_mech_m7_boss_walk_end\n.set bomb_mech_m7_boss_walk_end, bomb_mech_m7_boss_scripts+0x298\n"
        ".globl bomb_mech_m7_boss_turn_to_target\n.set bomb_mech_m7_boss_turn_to_target, bomb_mech_m7_boss_scripts+0x2A4\n"
        ".globl bomb_mech_m7_boss_turn_wait_idle\n.set bomb_mech_m7_boss_turn_wait_idle, bomb_mech_m7_boss_scripts+0x2AC\n"
        ".globl bomb_mech_m7_boss_turn_start\n.set bomb_mech_m7_boss_turn_start, bomb_mech_m7_boss_scripts+0x2BC\n"
        ".globl bomb_mech_m7_boss_turn_wait\n.set bomb_mech_m7_boss_turn_wait, bomb_mech_m7_boss_scripts+0x2C4\n"
        ".globl bomb_mech_m7_boss_turn_done\n.set bomb_mech_m7_boss_turn_done, bomb_mech_m7_boss_scripts+0x2D4\n"
        ".globl bomb_mech_m7_boss_player_below_check\n.set bomb_mech_m7_boss_player_below_check, bomb_mech_m7_boss_scripts+0x2EC\n"
        ".globl bomb_mech_m7_boss_turn_to_player_check\n.set bomb_mech_m7_boss_turn_to_player_check, bomb_mech_m7_boss_scripts+0x2F4\n"
        ".globl bomb_mech_m7_boss_player_beyond_check\n.set bomb_mech_m7_boss_player_beyond_check, bomb_mech_m7_boss_scripts+0x300\n"
        ".globl bomb_mech_m7_boss_bombs_then_pause\n.set bomb_mech_m7_boss_bombs_then_pause, bomb_mech_m7_boss_scripts+0x310\n"
        ".globl bomb_mech_m7_boss_attack_fire\n.set bomb_mech_m7_boss_attack_fire, bomb_mech_m7_boss_scripts+0x314\n"
        ".globl bomb_mech_m7_boss_attack_choose_a\n.set bomb_mech_m7_boss_attack_choose_a, bomb_mech_m7_boss_scripts+0x31C\n"
        ".globl bomb_mech_m7_boss_attack_choose_b\n.set bomb_mech_m7_boss_attack_choose_b, bomb_mech_m7_boss_scripts+0x334\n"
        ".globl bomb_mech_m7_boss_attack_choose_c\n.set bomb_mech_m7_boss_attack_choose_c, bomb_mech_m7_boss_scripts+0x34C\n"
        ".globl bomb_mech_m7_boss_attack_choose_d\n.set bomb_mech_m7_boss_attack_choose_d, bomb_mech_m7_boss_scripts+0x368\n"
        ".globl bomb_mech_m7_boss_attack_return\n.set bomb_mech_m7_boss_attack_return, bomb_mech_m7_boss_scripts+0x398\n"
        ".globl bomb_mech_m7_boss_scan_far\n.set bomb_mech_m7_boss_scan_far, bomb_mech_m7_boss_scripts+0x39C\n"
        ".globl bomb_mech_m7_boss_aim_check\n.set bomb_mech_m7_boss_aim_check, bomb_mech_m7_boss_scripts+0x3A0\n"
        ".globl bomb_mech_m7_boss_aim_jitter\n.set bomb_mech_m7_boss_aim_jitter, bomb_mech_m7_boss_scripts+0x3AC\n"
        ".globl bomb_mech_m7_boss_attack_choose_e\n.set bomb_mech_m7_boss_attack_choose_e, bomb_mech_m7_boss_scripts+0x3B4\n"
        ".globl bomb_mech_m7_boss_attack_choose_f\n.set bomb_mech_m7_boss_attack_choose_f, bomb_mech_m7_boss_scripts+0x3C8\n"
        ".globl bomb_mech_m7_boss_attack_f_return\n.set bomb_mech_m7_boss_attack_f_return, bomb_mech_m7_boss_scripts+0x3E0\n"
        ".globl bomb_mech_m7_boss_far_return\n.set bomb_mech_m7_boss_far_return, bomb_mech_m7_boss_scripts+0x3E4\n"
        ".globl bomb_mech_m7_boss_walk_then_pause\n.set bomb_mech_m7_boss_walk_then_pause, bomb_mech_m7_boss_scripts+0x3E8\n"
        ".globl bomb_mech_m7_boss_pause_return\n.set bomb_mech_m7_boss_pause_return, bomb_mech_m7_boss_scripts+0x3F0\n"
        ".globl bomb_mech_m7_boss_player_scan\n.set bomb_mech_m7_boss_player_scan, bomb_mech_m7_boss_scripts+0x3F8\n"
        ".globl bomb_mech_m7_boss_turn_then_scan\n.set bomb_mech_m7_boss_turn_then_scan, bomb_mech_m7_boss_scripts+0x408\n"
        ".globl D_8011DD68\n.set D_8011DD68, bomb_mech_m7_boss_scripts+0x410\n"
        ".globl D_8011DEA4\n.set D_8011DEA4, bomb_mech_m7_boss_scripts+0x54C\n");
