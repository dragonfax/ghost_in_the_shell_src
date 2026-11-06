/* s09 data 0x8011B5A8-0x80124800: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s09_types.h"
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
extern void chaser_move();
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
extern void diagonal_elevator_draw();
extern void diagonal_elevator_phase2();
extern void diagonal_elevator_trigger();
extern void enemy_chase_player();
extern void enemy_fly_forward();
extern void enemy_kill();
extern void enemy_retarget_jitter();
extern void enemy_sound_start();
extern void enemy_sound_stop_cue();
extern void enemy_spawn_record();
extern void enemy_vars_init_raw();
extern void enemy_vars_reset_bytes();
extern void enemy_vars_reset_offsets();
extern u8 file_gt3_mobj_cb4[];
extern void fn_800B789C();
extern void fn_800BD11C();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void fn_s07_800BAE10();
extern void fuchikoma_chase_update();
extern void gun_turret_spawn();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void heavy_mobile_suit_place();
extern void homing_move();
extern void homing_steer_player();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void model_store_pchr();
extern void obj_area_update();
extern void obj_boss_laser_init();
extern void obj_call_hook();
extern void obj_decelerate_move();
extern void obj_face_target_update();
extern void obj_fall_update();
extern void obj_finish_step();
extern void obj_handle_result();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_hover_attack_update();
extern void obj_hover_home();
extern void obj_jump_if_player_near();
extern void obj_patrol_update();
extern void obj_play_sound_here();
extern void obj_release_check();
extern void obj_retarget();
extern void obj_script_branch();
extern void obj_script_jump_far();
extern void obj_script_jump_if_beyond();
extern void obj_script_jump_if_key();
extern void obj_script_jump_if_within();
extern void obj_script_jump_linked();
extern void obj_script_jump_near();
extern void obj_script_jump_on_flag();
extern void obj_script_read_arg();
extern void obj_script_read_jump();
extern void obj_script_read_s32();
extern void obj_script_read_speed();
extern void obj_script_read_u16();
extern void obj_script_set_258();
extern void obj_script_set_fly_mode();
extern void obj_script_set_sound();
extern void obj_set_next_state();
extern void obj_speed_approach();
extern void obj_stream_branch();
extern void obj_stream_read_op();
extern void obj_turn_sound_update();
extern void obj_turn_step();
extern void obj_turn_to_player_16();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void player_switch_update();
extern void ramp_start_script();
extern void reactor_control_rods_m9_boss_update();
extern void rising_door_draw();
extern void rising_door_phase0();
extern void rising_door_phase2();
extern void rising_door_sense_check();
extern void rising_door_sense_gated();
extern void rising_door_sense_phase0();
extern void rising_door_sense_vars_init();
extern void rising_door_vars_init();
extern void rocket_drone_spawn();
extern void s09_diagonal_elevator_init();
extern void s09_diagonal_elevator_phase0();
extern void s09_diagonal_elevator_update();
extern void script_branch_if_near_player();
extern void script_dispatch();
extern void script_jump_if_mode();
extern void script_jump_if_near_player_in_view();
extern void script_jump_if_player_far();
extern void script_jump_if_player_in_radius();
extern void script_jump_if_player_in_view();
extern void script_jump_if_within_range();
extern void script_jump_near_corner();
extern void script_jump_table();
extern void script_op_aim_and_track();
extern void script_op_jump_if_facing_player();
extern void script_op_jump_if_flag_in_range();
extern void script_op_jump_if_in_cell_corner();
extern void script_op_jump_if_in_range();
extern void script_op_jump_if_near_target();
extern void script_op_jump_if_player_far();
extern void script_op_jump_if_player_in_range();
extern void script_op_jump_if_player_near();
extern void script_op_read_u16();
extern void script_op_set_enemy_sound();
extern void script_op_set_mode();
extern void script_op_set_speed();
extern void script_op_set_unk_234();
extern void script_op_switch();
extern void script_player_angle_branch();
extern void script_read_s32();
extern void script_set_turn_mode();
extern void shooter_vars_reset();
extern void sound_emitter_step();
extern void stage_ctrl_init();
extern void stage_engine_init();
extern u8 str_arkb_ch0_clt[];
extern u8 str_arkb_ch0_vx1[];
extern u8 str_arkb_ch0cb4[];
extern u8 str_arkb_tp0_clt[];
extern u8 str_arkb_tp0_xs3[];
extern u8 str_b09_dat_fac[];
extern u8 str_b09_ene_fac[];
extern u8 str_bos9_ch0_vx1[];
extern u8 str_bos9_ch0cb4[];
extern u8 str_bos9_tp0_clt[];
extern u8 str_bos9_tp0_xs3[];
extern u8 str_bos9_tp1_xs3[];
extern u8 str_com_dat_fac[];
extern u8 str_enemy_arkb_data[];
extern u8 str_enemy_bos9_data[];
extern u8 str_enemy_ctl9_data[];
extern u8 str_enemy_hou1_data[];
extern u8 str_enemy_land_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_nk2_data[];
extern u8 str_enemy_roi_data[];
extern u8 str_enemy_sel1_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_gen_apdea3[];
extern u8 str_gen_cnf_bcf[];
extern u8 str_gen_joy_bin[];
extern u8 str_gt3_apdea3[];
extern u8 str_gt3_cnf_bcf[];
extern u8 str_gt3_joy_bin[];
extern u8 str_hou1_ch0_clt[];
extern u8 str_hou1_ch0_vx1[];
extern u8 str_hou1_ch0cb4[];
extern u8 str_hou1_tp0_clt[];
extern u8 str_hou1_tp0_xs3[];
extern u8 str_land_ch0_clt[];
extern u8 str_land_ch0_vx1[];
extern u8 str_land_ch0cb4[];
extern u8 str_land_tp0_clt[];
extern u8 str_land_tp0_xs3[];
extern u8 str_land_tp1_clt[];
extern u8 str_land_tp1_xs3[];
extern u8 str_m09_dat_fac[];
extern u8 str_m33_cnf_bcf[];
extern u8 str_m33_joy_bin[];
extern u8 str_main_data[];
extern u8 str_msgs_spr_clt[];
extern u8 str_msgs_spr_grc[];
extern u8 str_msgs_spr_so3[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_s09_boss[];
extern u8 str_s09_dat_fac[];
extern u8 str_s09_ene_fac[];
extern u8 str_s09_miss[];
extern u8 str_s09_stage[];
extern u8 str_sdw_obj_vx1[];
extern u8 str_sdw_tp0_clt[];
extern u8 str_sdw_tp0_xs3[];
extern u8 str_sel1_ch0_clt[];
extern u8 str_sel1_ch0_vx1[];
extern u8 str_sel1_ch0cb4[];
extern u8 str_sel1_tp0_clt[];
extern u8 str_sel1_tp0_xs3[];
extern u8 str_tg_disp_clt[];
extern u8 str_tg_disp_grc[];
extern u8 str_tg_disp_so3[];
extern u8 str_tnk2_ch0_clt[];
extern u8 str_tnk2_ch0_vx1[];
extern u8 str_tnk2_ch0cb4[];
extern u8 str_tnk2_tp0_clt[];
extern u8 str_tnk2_tp0_xs3[];
extern u8 str_troi_ch0_clt[];
extern u8 str_troi_ch0_vx1[];
extern u8 str_troi_ch0cb4[];
extern u8 str_troi_tp0_clt[];
extern u8 str_troi_tp0_xs3[];
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
extern void trace_enemy_update();
extern void track_set_enabled();
extern void track_setup();
extern void triple_barrel_robot_spawn();
extern void tune_obj_init();
extern void tune_vars_reset();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_8011B938[];
extern u8 D_8011B940[];
extern u8 D_8011B948[];
extern u8 D_8011CBB4[];
extern u8 D_8011CBB8[];
extern u8 D_8011FEEC[];
extern u8 D_80123246[];
extern u8 cos_table[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 elevator_ride_flag[];
extern u8 enemy_count[];
extern u8 enemy_shot_id[];
extern u8 fuchikoma_state_table_s12[];
extern u8 gun_hit_effect_table[];
extern u8 gun_turret_asset_s12[];
extern u8 hurry_msg_shown[];
extern u8 msg_x[];
extern u8 msg_y[];
extern u8 muzzle_x_table_s12[];
extern u8 muzzle_y_table_s12[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 spin_angle[];
extern u8 view_sincos[];
extern s32 area;
extern ScanItem stage_scan_items[];
extern AreaEntry stage_area_entry;
extern AreaEntry D_8011B614;
extern ScanItem boss_area_scan_items[];
extern AreaEntry boss_area_entry;
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern void (*enemy_kind_init_fns[])(Object *);
extern void (*enemy_kind_phase0_fns[])(Object *, ObjHandler *);
extern void (*enemy_kind_phase1_fns[])(Object *, ObjHandler *);
extern void (*enemy_kind_phase2_fns[])(Object *, ObjHandler *);
extern void (*enemy_kind_phase3_fns[])(Object *, ObjHandler *);
extern u32 marker_points;
extern u32 D_8011B814;
extern u32 D_8011B818;
extern u32 D_8011B81C[];
extern s32 stage_ctrl_entries[];
extern PathPoint stage_ctrl_cam_path[];
extern PathPoint elevator_cam_path_final[];
extern PathPoint elevator_cam_path_pos[2];
extern s32 D_8011B920;
extern s32 door_model_base[];
extern EdgeSlot800B9D84 elevator_edges[4];
extern u8 *D_8011B950[];
extern ScanEntry stage_ctrl_scan_entry;
extern s32 heavy_mobile_suit_model_asset[];
extern ModelBlockRef d_801194DC[];
extern ModelBlockRef d_801194FC[];
extern ModelBlockRef d_80119514[];
extern ModelBlockRange d_80119524[];
extern ModelBlock heavy_mobile_suit_model_block;
extern u8 *d_80119560[];
extern ScanEntry heavy_mobile_suit_scan_entry;
extern u32 d_80119580[];
extern s16 heavy_mobile_suit_script[4];
extern s16 heavy_mobile_suit_anim_patrol_enter[];
extern s16 heavy_mobile_suit_anim_search_hold[];
extern s16 heavy_mobile_suit_anim_search_end[];
extern s16 heavy_mobile_suit_anim_alt_enter[];
extern s16 heavy_mobile_suit_anim_alt_hold[];
extern s16 heavy_mobile_suit_anim_alt_end[];
extern s16 heavy_mobile_suit_anim_spotted_enter[];
extern s16 heavy_mobile_suit_anim_pursue_enter[];
extern s16 heavy_mobile_suit_anim_pursue_alt_enter[];
extern s16 heavy_mobile_suit_anim_approach_hold[];
extern s16 heavy_mobile_suit_anim_fire_enter[];
extern s16 heavy_mobile_suit_anim_disengage[];
extern s16 *heavy_mobile_suit_data[];
extern s16 heavy_mobile_suit_place_select[];
extern s16 heavy_mobile_suit_place_far_aim[];
extern s16 heavy_mobile_suit_place_spotted[];
extern s16 heavy_mobile_suit_place_idle[];
extern s16 heavy_mobile_suit_place_idle_loop[];
extern s16 heavy_mobile_suit_place_fire_start[];
extern s16 heavy_mobile_suit_place_fire_start_loop[];
extern s16 heavy_mobile_suit_place_chase[];
extern s16 heavy_mobile_suit_place_chase_wait[];
extern s16 heavy_mobile_suit_place_chase_pursue[];
extern s16 heavy_mobile_suit_place_chase_pursue_loop[];
extern s16 heavy_mobile_suit_place_chase_end[];
extern s16 heavy_mobile_suit_place_fire_aim[];
extern s16 heavy_mobile_suit_place_fire_aim_loop[];
extern s16 heavy_mobile_suit_place_aim_chase[];
extern s16 heavy_mobile_suit_place_aim_chase_loop[];
extern s16 heavy_mobile_suit_place_aim_pursue[];
extern s16 heavy_mobile_suit_place_aim_pursue_loop[];
extern s16 heavy_mobile_suit_place_aim_end[];
extern s16 heavy_mobile_suit_place_aim_fire[];
extern s16 heavy_mobile_suit_place_aim_fire_loop[];
extern s16 heavy_mobile_suit_place_fire_burst[];
extern s16 heavy_mobile_suit_place_fire_burst_loop[];
extern s16 heavy_mobile_suit_place_cooldown[];
extern s16 heavy_mobile_suit_place_cooling[];
extern s16 heavy_mobile_suit_place_disengage[];
extern s16 heavy_mobile_suit_place_disengage_loop[];
extern s16 heavy_mobile_suit_place_settle[];
extern s16 heavy_mobile_suit_place_restart[];
extern s16 *heavy_mobile_suit_script_data[];
extern s16 *D_8011BDB4;
extern ScriptCallEntry D_8011BDB8[];
extern StateEntry D_8011BE10[];
extern s32 fuchikoma_asset[];
extern ModelBlockRef d_8011BE84[];
extern ModelBlockRef d_8011BE9C[];
extern ModelBlockRef d_8011BEAC[];
extern ModelBlockRange d_8011BEBC[];
extern ModelBlock arkb_model_set;
extern u8 *fuchikoma_b_ptr_table_ids[];
extern ScanEntry arkb_loader_step;
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
extern s32 d_8011C114[];
extern ModelBlockRef troi_clt_list[];
extern ModelBlockRef troi_xs3_list[];
extern ModelBlockRef troi_vx1_list[];
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
extern u32 d_80116B88[];
extern GunSetup enemy_shot_setup;
extern ModelBlockRef rocket_drone_palettes[];
extern ModelBlockRef rocket_drone_textures[];
extern ModelBlockRef rocket_drone_models[];
extern ModelBlock rocket_drone_model_block;
extern u8 *rocket_drone_stage_files[];
extern ScanEntry rocket_drone_scan_entry;
extern u32 d_80116C34[];
extern s16 rocket_drone_anim_idle[];
extern s16 *rocket_drone_data[];
extern s16 rocket_drone_restart[];
extern s16 rocket_drone_select[];
extern s16 rocket_drone_patrol[];
extern s16 rocket_drone_spotted[];
extern s16 rocket_drone_idle_start[];
extern s16 rocket_drone_idle[];
extern s16 rocket_drone_cooldown[];
extern s16 *rocket_drone_anim[];
extern s16 *d_80116CC0;
extern ScriptCallEntry rocket_drone_call_table[];
extern StateEntry rocket_drone_state_table[];
extern s32 gun_turret_asset[];
extern ModelBlockRef D_8011C424[];
extern ModelBlockRef D_8011C43C[];
extern ModelBlockRef D_8011C44C[];
extern ModelBlock D_8011C45C;
extern u8 *D_8011C480[];
extern ScanEntry D_8011C488;
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
extern s32 tank2_asset[3];
extern ModelBlockRef D_8011C56C[];
extern ModelBlockRef D_8011C584[];
extern ModelBlockRef D_8011C594[];
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
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *enemy_msgs_ptr_table_ids[];
extern ScanEntry enemy_msgs_scan_entry;
extern s32 reactor_boss_active_flag;
extern s32 boss_done_flag;
extern s32 control_rods_left;
extern s32 reactor_boss_asset[];
extern ModelBlockRef reactor_boss_palette_refs[];
extern ModelBlockRef reactor_boss_model_refs[];
extern ModelBlockRef reactor_boss_texture_refs[];
extern ModelBlockRange D_8011CA20[];
extern ModelBlockRange D_8011CA40[];
extern ModelBlockRange D_8011CA50[];
extern ModelBlock reactor_boss_model_block;
extern u8 *reactor_boss_ptr_table_ids[];
extern ScanEntry reactor_boss_entry;
extern s16 reactor_control_rods_m9_boss_start[];
extern s16 reactor_control_rods_m9_boss_idle[];
extern s16 *reactor_boss_script_data[];
extern s16 *reactor_boss_script_start;
extern ScriptCallEntry reactor_boss_table[2];
extern RecTemplate mission_end_fx[];
extern u32 ring_effect_points;
extern u32 D_8011CB34;
extern u32 D_8011CB38[];
extern EffectOffset aimed_effect_points[8];
extern PylonAsset pylon_asset;
extern s16 pylon_anim_idle[];
extern s16 pylon_anim_open[];
extern s16 pylon_anim_open_loop[];
extern s16 pylon_anim_charge[];
extern s16 pylon_anim_charge_loop[];
extern s16 pylon_anim_death[];
extern s16 pylon_anim_dead[];
extern s16 *pylon_data[];
extern s16 pylon_link_script[];
extern s16 pylon_death[];
extern s16 pylon_death_delay[];
extern s16 pylon_death_sound[];
extern s16 pylon_dead_wait[];
extern s16 pylon_dead_idle[];
extern s16 *pylon_script_data[];
extern PylonLinkWord pylon_link_word;
extern ScriptCallEntry pylon_call_table[];
extern DeathPiece enemy_death_points[6];
extern StateEntry pylon_state_table[];
extern s32 obj_size_table[];
extern u32 part_asset_buf[];
extern s16 spawn_part_anim_idle[];
extern s16 *part_scripts[];
extern u32 part_kind_params;
extern u32 dual_mech_script_table;
extern u32 D_8011CDD8[];
extern s16 spawn_part_await_boss[];
extern s16 spawn_part_hover[];
extern s16 spawn_part_hover_scan[];
extern s16 spawn_part_track[];
extern s16 spawn_part_track_fire[];
extern s16 spawn_part_laser_hold[];
extern s16 *D_8011CEA8[];
extern s16 *D_8011CEC0;
extern ScriptCallEntry D_8011CEC4[];
extern StateEntry D_8011CEF4[];
extern FxRecordParams fade_fx_params;
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_80121A9C[];
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
extern u32 D_80122C20[];
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
extern u32 D_80123240;
extern u16 texture_image[];
extern u16 stage_image_width;
extern u16 stage_image_height;
extern u32 stage_image_pixels[];
extern s32 heap_top;
extern s32 heap2_top;
extern s32 stage_ctrl_index;
extern s32 spark_model_index_base;
extern s32 view_nudge_toggle;
extern s32 elevator_done_flag;
extern s32 model_pchr_saved;
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
extern u32 D_80124764;
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
extern u32 D_801247E8;
extern s32 pause_flag;
extern s32 cell_cursor_step1;
extern s32 cell_cursor_step2;
extern s32 cell_cursor_step1_saved;
extern s32 cell_cursor_step2_saved;

s32 area = 0x18;

ScanItem stage_scan_items[8] = {
    {&stage_ctrl_scan_entry, str_enemy_ctl9_data},
    {&heavy_mobile_suit_scan_entry, str_enemy_land_data},
    {&arkb_loader_step, str_enemy_arkb_data},
    {&triple_barrel_robot_scan_entry, str_enemy_roi_data},
    {&rocket_drone_scan_entry, str_enemy_sel1_data},
    {&D_8011C488, str_enemy_hou1_data},
    {&tank_scan_entry, str_enemy_nk2_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry stage_area_entry = {str_s09_stage, str_gt3_cnf_bcf, str_gt3_apdea3, str_gt3_joy_bin, str_s09_dat_fac, str_s09_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, stage_scan_items};

AreaEntry D_8011B614 = {str_s09_miss, str_m33_cnf_bcf, NULL, str_m33_joy_bin, str_m09_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

ScanItem boss_area_scan_items[3] = {
    {&enemy_msgs_scan_entry, str_enemy_msgs_data},
    {&reactor_boss_entry, str_enemy_bos9_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry boss_area_entry = {str_s09_boss, str_gen_cnf_bcf, str_gen_apdea3, str_gen_joy_bin, str_b09_dat_fac, str_b09_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, boss_area_scan_items};

AreaEntry *area_entry_table[3] = {
    &D_8011B614, &stage_area_entry, &boss_area_entry,
};

#include "../stage/data/debug_name_buf.c"

void (*enemy_kind_init_fns[10])(Object *) = {
    NULL, tune_obj_init, rising_door_vars_init, rising_door_sense_vars_init, shooter_vars_reset, enemy_vars_init_raw,
    enemy_vars_reset_bytes, enemy_vars_reset_offsets, tune_vars_reset, s09_diagonal_elevator_init,
};

void (*enemy_kind_phase0_fns[1])(Object *, ObjHandler *) = {
    NULL,
};

void (*enemy_kind_phase1_fns[1])(Object *, ObjHandler *) = {
    NULL,
};

void (*enemy_kind_phase2_fns[1])(Object *, ObjHandler *) = {
    NULL,
};

void (*enemy_kind_phase3_fns[37])(Object *, ObjHandler *) = {
    NULL, player_switch_update, fn_800B789C, rising_door_phase2, rising_door_draw, rising_door_phase0,
    fn_800B789C, rising_door_phase2, rising_door_draw, rising_door_sense_phase0, fn_800B789C, rising_door_phase2,
    rising_door_draw, player_switch_update, fn_800B789C, rising_door_phase2, rising_door_draw, trace_enemy_update,
    fn_800B789C, rising_door_phase2, rising_door_draw, rising_door_sense_check, fn_800B789C, rising_door_phase2,
    rising_door_draw, diagonal_elevator_trigger, fn_800B789C, rising_door_phase2, rising_door_draw, rising_door_sense_gated,
    fn_800B789C, rising_door_phase2, rising_door_draw, s09_diagonal_elevator_phase0, s09_diagonal_elevator_update, diagonal_elevator_phase2,
    diagonal_elevator_draw,
};

u32 marker_points = 0x00009780;

u32 D_8011B814 = 0xFFFFD480;

u32 D_8011B818 = 0xFFFFE8C0;

u32 D_8011B81C[5] = {
    0x00000000, 0x000014FF, 0xFFFF9880, 0xFFFFFE7F, 0x00000000,
};

s32 stage_ctrl_entries[12] = {
    0x320, 0, 0x2443, 0, 0xCBBE, 0,
    -0xCC5, 0, -0x6431, -0x4680, -0x2A, 0,
};

PathPoint stage_ctrl_cam_path[6] = {
    {0xE60, 0, -0x1D40, 0}, {0x5A2, 0, -0x938, 0}, {-0x1075, 0, -0x938, 0}, {-0x1075, 0, 0x308A, 0},
    {-0x65B, 0, 0x308A, 0}, {0x332, 0, 0x2442, 0},
};

PathPoint elevator_cam_path_final[4] = {
    {0xA524, -0x2761, -0x9C5, 0}, {0xA524, -0x1B00, -0x9C5, 0}, {0xAB2E, 0, -0x11C6, 0},
    {0xCBBF, 0, -0xC86, 0},
};

PathPoint elevator_cam_path_pos[2] = {
    {-0x6564, -0x6600, 0, 0}, {-0x6978, -0x4680, 0, 0},
};

s32 D_8011B920 = -1;

s32 door_model_base[3] = {
    -1, -1, 1,
};

EdgeSlot800B9D84 elevator_edges[4] = {
    {0, -0x8000}, {0, 1}, {0, 0}, {0, 0},
};

u8 *D_8011B950[2] = {
    file_gt3_mobj_cb4, NULL,
};

ScanEntry stage_ctrl_scan_entry = {{(s32)stage_ctrl_init, (s32)enemy_spawn_record}, &D_8011B920, 0, (s32)D_8011B950, 0};

s32 heavy_mobile_suit_model_asset[3] = {
    -1, -1, -1,
};

#include "../stage/data/d_801194DC.c"

#include "../stage/data/d_801194FC.c"

#include "../stage/data/d_80119514.c"

#include "../stage/data/d_80119524.c"

#include "../stage/data/heavy_mobile_suit_model_block.c"

#include "../stage/data/d_80119560.c"

ScanEntry heavy_mobile_suit_scan_entry = {{0, (s32)heavy_mobile_suit_place}, heavy_mobile_suit_model_asset, (s32)&heavy_mobile_suit_model_block, (s32)d_80119560, 0};

#include "../stage/data/d_80119580.c"

#include "../stage/data/heavy_mobile_suit_anims.c"

struct HeavyMobileSuitPlaceScripts {
    s16 select[6];
    s16 far_aim[4];
    s16 spotted[16];
    s16 idle[8];
    s16 idle_loop[10];
    s16 fire_start[8];
    s16 fire_start_loop[6];
    s16 chase[8];
    s16 chase_wait[6];
    s16 chase_pursue[8];
    s16 chase_pursue_loop[10];
    s16 chase_end[8];
    s16 fire_aim[8];
    s16 fire_aim_loop[6];
    s16 aim_chase[8];
    s16 aim_chase_loop[6];
    s16 aim_pursue[8];
    s16 aim_pursue_loop[10];
    s16 aim_end[8];
    s16 aim_fire[8];
    s16 aim_fire_loop[6];
    s16 fire_burst[14];
    s16 fire_burst_loop[6];
    s16 cooldown[8];
    s16 cooling[12];
    s16 disengage[16];
    s16 disengage_loop[8];
    s16 settle[6];
    s16 restart[2];
    s16 *table[29];
    s16 *D_8011BDB4;
} heavy_mobile_suit_place_scripts = {
    /* select */ {
        HEAVY_MOBILE_SUIT_PLACE_SWITCH, 3500, HEAVY_MOBILE_SUIT_PLACE_FAR_AIM,
        JUMP(HEAVY_MOBILE_SUIT_PLACE_SPOTTED),
    },
    /* far_aim */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_FLY_MODE, 1,
        JUMP(HEAVY_MOBILE_SUIT_PLACE_AIM_CHASE),
    },
    /* spotted */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_FLY_MODE, 0,
        HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN, 1000, HEAVY_MOBILE_SUIT_PLACE_FIRE_START,
        HEAVY_MOBILE_SUIT_PLACE_DISPATCH, HEAVY_MOBILE_SUIT_PLACE_CHASE,
        HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN, 2500, HEAVY_MOBILE_SUIT_PLACE_AIM_CHASE,
        HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN, 3500, HEAVY_MOBILE_SUIT_PLACE_CHASE,
        JUMP(HEAVY_MOBILE_SUIT_PLACE_FIRE_START),
    },
    /* idle */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 0,
        SET_COUNTER(128),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_IDLE_LOOP),
    },
    /* idle_loop */ {
        WAIT(1),
        HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN, 1000, HEAVY_MOBILE_SUIT_PLACE_FIRE_START,
        LOOP(HEAVY_MOBILE_SUIT_PLACE_IDLE_LOOP),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_RESTART),
    },
    /* fire_start */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 3,
        SET_COUNTER(40),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_FIRE_START_LOOP),
    },
    /* fire_start_loop */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PLACE_FIRE_START_LOOP),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_FIRE_BURST),
    },
    /* chase */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 14,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 1,
        SET_COUNTER(40),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_CHASE_WAIT),
    },
    /* chase_wait */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PLACE_CHASE_WAIT),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_CHASE_PURSUE),
    },
    /* chase_pursue */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 14,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 4,
        SET_COUNTER(768),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_CHASE_PURSUE_LOOP),
    },
    /* chase_pursue_loop */ {
        WAIT(1),
        HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN, 1300, HEAVY_MOBILE_SUIT_PLACE_FIRE_AIM,
        LOOP(HEAVY_MOBILE_SUIT_PLACE_CHASE_PURSUE_LOOP),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_CHASE_END),
    },
    /* chase_end */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 5,
        SET_COUNTER(40),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_SETTLE),
    },
    /* fire_aim */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 6,
        SET_COUNTER(56),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_FIRE_AIM_LOOP),
    },
    /* fire_aim_loop */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PLACE_FIRE_AIM_LOOP),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_FIRE_BURST),
    },
    /* aim_chase */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 10,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 2,
        SET_COUNTER(40),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_AIM_CHASE_LOOP),
    },
    /* aim_chase_loop */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PLACE_AIM_CHASE_LOOP),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_AIM_PURSUE),
    },
    /* aim_pursue */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 10,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 7,
        SET_COUNTER(768),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_AIM_PURSUE_LOOP),
    },
    /* aim_pursue_loop */ {
        WAIT(1),
        HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN, 1000, HEAVY_MOBILE_SUIT_PLACE_AIM_FIRE,
        LOOP(HEAVY_MOBILE_SUIT_PLACE_AIM_PURSUE_LOOP),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_AIM_END),
    },
    /* aim_end */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 8,
        SET_COUNTER(40),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_SETTLE),
    },
    /* aim_fire */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 9,
        SET_COUNTER(56),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_AIM_FIRE_LOOP),
    },
    /* aim_fire_loop */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PLACE_AIM_FIRE_LOOP),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_FIRE_BURST),
    },
    /* fire_burst */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 10,
        HEAVY_MOBILE_SUIT_PLACE_PLAY_SOUND_HERE,
        SET_COUNTER(96),
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_6, 72,
        HEAVY_MOBILE_SUIT_PLACE_SET_258, 0,
        JUMP(HEAVY_MOBILE_SUIT_PLACE_FIRE_BURST_LOOP),
    },
    /* fire_burst_loop */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PLACE_FIRE_BURST_LOOP),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_COOLDOWN),
    },
    /* cooldown */ {
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 11,
        SET_COUNTER(5),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_COOLING),
    },
    /* cooling */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PLACE_COOLING),
        HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN, 700, HEAVY_MOBILE_SUIT_PLACE_DISENGAGE,
        HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN, 1000, HEAVY_MOBILE_SUIT_PLACE_FIRE_BURST,
        JUMP(HEAVY_MOBILE_SUIT_PLACE_DISENGAGE),
    },
    /* disengage */ {
        HEAVY_MOBILE_SUIT_PLACE_READ_U16_2, 12,
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, -20,
        SET_COUNTER(64),
        HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN, 700, HEAVY_MOBILE_SUIT_PLACE_DISENGAGE_LOOP,
        HEAVY_MOBILE_SUIT_PLACE_SET_SOUND, 0,
        SET_COUNTER(32),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_SETTLE),
    },
    /* disengage_loop */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PLACE_DISENGAGE_LOOP),
        HEAVY_MOBILE_SUIT_PLACE_DISPATCH, HEAVY_MOBILE_SUIT_PLACE_CHASE,
        JUMP(HEAVY_MOBILE_SUIT_PLACE_AIM_CHASE),
    },
    /* settle */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PLACE_SETTLE),
        JUMP(HEAVY_MOBILE_SUIT_PLACE_RESTART),
    },
    /* restart */ {
        JUMP(HEAVY_MOBILE_SUIT_PLACE_SELECT),
    },
    /* table */ {
        heavy_mobile_suit_place_scripts.select, heavy_mobile_suit_place_scripts.far_aim, heavy_mobile_suit_place_scripts.spotted, heavy_mobile_suit_place_scripts.idle, heavy_mobile_suit_place_scripts.idle_loop, heavy_mobile_suit_place_scripts.fire_start,
        heavy_mobile_suit_place_scripts.fire_start_loop, heavy_mobile_suit_place_scripts.chase, heavy_mobile_suit_place_scripts.chase_wait, heavy_mobile_suit_place_scripts.chase_pursue, heavy_mobile_suit_place_scripts.chase_pursue_loop, heavy_mobile_suit_place_scripts.chase_end,
        heavy_mobile_suit_place_scripts.fire_aim, heavy_mobile_suit_place_scripts.fire_aim_loop, heavy_mobile_suit_place_scripts.aim_chase, heavy_mobile_suit_place_scripts.aim_chase_loop, heavy_mobile_suit_place_scripts.aim_pursue, heavy_mobile_suit_place_scripts.aim_pursue_loop,
        heavy_mobile_suit_place_scripts.aim_end, heavy_mobile_suit_place_scripts.aim_fire, heavy_mobile_suit_place_scripts.aim_fire_loop, heavy_mobile_suit_place_scripts.fire_burst, heavy_mobile_suit_place_scripts.fire_burst_loop, heavy_mobile_suit_place_scripts.cooldown,
        heavy_mobile_suit_place_scripts.cooling, heavy_mobile_suit_place_scripts.disengage, heavy_mobile_suit_place_scripts.disengage_loop, heavy_mobile_suit_place_scripts.settle, heavy_mobile_suit_place_scripts.restart,
    },
    /* D_8011BDB4 */ heavy_mobile_suit_place_scripts.select,
};

ScriptCallEntry D_8011BDB8[11] = {
    {NULL, 0},
    {obj_script_set_sound, 0},
    {obj_script_read_u16, 0},
    {obj_script_set_fly_mode, 0},
    {obj_script_jump_if_within, 0},
    {obj_script_jump_if_beyond, 0},
    {script_op_read_u16, 0},
    {obj_script_set_258, 0},
    {script_op_switch, 0},
    {script_dispatch, 0},
    {obj_play_sound_here, 0},
};

StateEntry D_8011BE10[13] = {
    {(u32)chaser_move, HEAVY_MOBILE_SUIT_SCRIPT, 0},
    {(u32)chaser_move, HEAVY_MOBILE_SUIT_ANIM_PATROL_ENTER, 0},
    {(u32)chaser_move, HEAVY_MOBILE_SUIT_ANIM_ALT_ENTER, 0},
    {(u32)obj_hover_attack_update, HEAVY_MOBILE_SUIT_ANIM_SPOTTED_ENTER, 0},
    {(u32)chaser_move, HEAVY_MOBILE_SUIT_ANIM_SEARCH_HOLD, 0},
    {(u32)chaser_move, HEAVY_MOBILE_SUIT_ANIM_SEARCH_END, 0},
    {(u32)obj_hover_attack_update, HEAVY_MOBILE_SUIT_ANIM_PURSUE_ENTER, 0},
    {(u32)chaser_move, HEAVY_MOBILE_SUIT_ANIM_ALT_HOLD, 0},
    {(u32)chaser_move, HEAVY_MOBILE_SUIT_ANIM_ALT_END, 0},
    {(u32)obj_hover_attack_update, HEAVY_MOBILE_SUIT_ANIM_PURSUE_ALT_ENTER, 0},
    {(u32)obj_hover_attack_update, HEAVY_MOBILE_SUIT_ANIM_FIRE_ENTER, 0},
    {(u32)obj_hover_home, HEAVY_MOBILE_SUIT_ANIM_APPROACH_HOLD, 0},
    {(u32)chaser_move, HEAVY_MOBILE_SUIT_ANIM_DISENGAGE, 0},
};

#include "../stage/data/fuchikoma_asset.c"

#include "../stage/data/d_8011BE84.c"

#include "../stage/data/d_8011BE9C.c"

#include "../stage/data/d_8011BEAC.c"

#include "../stage/data/d_8011BEBC.c"

#include "../stage/data/arkb_model_set.c"

#include "../stage/data/fuchikoma_b_ptr_table_ids.c"

#include "../stage/data/arkb_loader_step.c"

#include "../stage/data/d_8011C610.c"

#include "../stage/data/enemy_fuchikoma_b_anims.c"

#include "../stage/data/enemy_fuchikoma_b_scripts.c"

#include "../stage/data/fuchikoma_call_table.c"

#include "../stage/data/muzzle_side_table.c"

#include "../stage/data/fuchikoma_state_table.c"

#include "../stage/data/shot_muzzle_x_table.c"

#include "../stage/data/d_8011C114.c"

ModelBlockRef troi_clt_list[3] = {
    {(s32)str_troi_ch0_clt, 0, 0},
    {(s32)str_troi_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef troi_xs3_list[2] = {
    {(s32)str_troi_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef troi_vx1_list[2] = {
    {(s32)str_troi_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock triple_barrel_robot_model_block = {(s32)troi_clt_list, (s32)troi_vx1_list, (s32)troi_xs3_list, 0, 0, 0, 0, 0, 0};

u8 *triple_barrel_robot_ptr_names[2] = {
    str_troi_ch0cb4, NULL,
};

#include "../stage/data/triple_barrel_robot_scan_entry.c"

#include "../stage/data/triple_barrel_robot_sounds.c"

#include "../stage/data/triple_barrel_robot_anims.c"

#include "../stage/data/triple_barrel_robot_script_table_streams.c"

#include "../stage/data/triple_barrel_robot_call_table.c"

#include "../stage/data/triple_barrel_robot_state_table.c"

#include "../stage/data/d_80116B88.c"

#include "../stage/data/enemy_shot_setup.c"

#include "../stage/data/rocket_drone_palettes.c"

#include "../stage/data/rocket_drone_textures.c"

#include "../stage/data/rocket_drone_models.c"

#include "../stage/data/rocket_drone_model_block.c"

#include "../stage/data/rocket_drone_stage_files.c"

#include "../stage/data/rocket_drone_scan_entry.c"

#include "../stage/data/d_80116C34.c"

#include "../stage/data/rocket_drone_anims.c"

struct RocketDroneScripts {
    s16 restart[2];
    s16 select[8];
    s16 patrol[8];
    s16 spotted[8];
    s16 idle_start[4];
    s16 idle[10];
    s16 cooldown[4];
    s16 *table[7];
    s16 *d_80116CC0;
} rocket_drone_scripts = {
    /* restart */ {
        JUMP(ROCKET_DRONE_SELECT),
    },
    /* select */ {
        ROCKET_DRONE_STREAM_BRANCH, 3200, ROCKET_DRONE_PATROL,
        ROCKET_DRONE_JUMP_IF_PLAYER_NEAR, 1800, ROCKET_DRONE_SPOTTED,
        JUMP(ROCKET_DRONE_PATROL),
    },
    /* patrol */ {
        ROCKET_DRONE_SET_TURN_MODE, 1,
        ROCKET_DRONE_SPEED_APPROACH, 3,
        ROCKET_DRONE_SET_NEXT_STATE, ROCKET_DRONE_STATE_PATROL,
        JUMP(ROCKET_DRONE_IDLE_START),
    },
    /* spotted */ {
        ROCKET_DRONE_SET_TURN_MODE, 0,
        ROCKET_DRONE_SPEED_APPROACH, 3,
        ROCKET_DRONE_SET_NEXT_STATE, ROCKET_DRONE_STATE_TRACK,
        JUMP(ROCKET_DRONE_IDLE_START),
    },
    /* idle_start */ {
        SET_COUNTER(50),
        JUMP(ROCKET_DRONE_IDLE),
    },
    /* idle */ {
        WAIT(1),
        LOOP(ROCKET_DRONE_IDLE),
        ROCKET_DRONE_JUMP_IF_PLAYER_NEAR, 500, ROCKET_DRONE_SPOTTED,
        JUMP(ROCKET_DRONE_COOLDOWN),
    },
    /* cooldown */ {
        WAIT(1),
        JUMP(ROCKET_DRONE_RESTART),
    },
    /* table */ {
        rocket_drone_scripts.restart, rocket_drone_scripts.select, rocket_drone_scripts.patrol, rocket_drone_scripts.spotted, rocket_drone_scripts.idle_start, rocket_drone_scripts.idle,
        rocket_drone_scripts.cooldown,
    },
    /* d_80116CC0 */ rocket_drone_scripts.restart,
};

ScriptCallEntry rocket_drone_call_table[6] = {
    {NULL, 0}, {obj_speed_approach, 0}, {obj_set_next_state, 0},
    {script_set_turn_mode, 0}, {obj_jump_if_player_near, 0}, {obj_stream_branch, 0},
};

#include "../stage/data/rocket_drone_state_table.c"

#include "../stage/data/gun_turret_asset.c"

ModelBlockRef D_8011C424[3] = {
    {(s32)str_hou1_ch0_clt, 0, 0},
    {(s32)str_hou1_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C43C[2] = {
    {(s32)str_hou1_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C44C[2] = {
    {(s32)str_hou1_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock D_8011C45C = {(s32)D_8011C424, (s32)D_8011C44C, (s32)D_8011C43C, 0, 0, 0, 0, 0, 0};

u8 *D_8011C480[2] = {
    str_hou1_ch0cb4, NULL,
};

ScanEntry D_8011C488 = {{(s32)fn_800BD11C, (s32)gun_turret_spawn}, gun_turret_asset, (s32)&D_8011C45C, (s32)D_8011C480, 0};

#include "../stage/data/d_80116968.c"

#include "../stage/data/gun_turret_anims.c"

#include "../stage/data/gun_turret_scripts.c"

#include "../stage/data/gun_turret_call_table.c"

#include "../stage/data/muzzle_x_table.c"

#include "../stage/data/muzzle_y_table.c"

#include "../stage/data/gun_turret_states.c"

#include "../stage/data/tank2_asset.c"

ModelBlockRef D_8011C56C[3] = {
    {(s32)str_tnk2_ch0_clt, 0, 0},
    {(s32)str_tnk2_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C584[2] = {
    {(s32)str_tnk2_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C594[2] = {
    {(s32)str_tnk2_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock tank_model_block = {(s32)D_8011C56C, (s32)D_8011C594, (s32)D_8011C584, 0, 0, 0, 0, 0, 0};

u8 *d_8011CC58[2] = {
    str_tnk2_ch0cb4, NULL,
};

#include "../stage/data/tank_scan_entry.c"

#include "../stage/data/tank_2_anims.c"

#include "../stage/data/tank_2_scripts.c"

#include "../stage/data/d_8011CF34.c"

#include "../stage/data/d_8011CF9C.c"

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

u8 *enemy_msgs_ptr_table_ids[3] = {
    str_msgs_spr_clt, str_msgs_spr_grc, str_msgs_spr_so3,
};

ScanEntry enemy_msgs_scan_entry = {{(s32)mission_state_reset, 0}, d_80117914, 0, 0, (s32)enemy_msgs_ptr_table_ids};

s32 reactor_boss_active_flag = 0;

s32 boss_done_flag = 0;

s32 control_rods_left = 0;

s32 reactor_boss_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef reactor_boss_palette_refs[2] = {
    {(s32)str_bos9_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef reactor_boss_model_refs[2] = {
    {(s32)str_bos9_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRef reactor_boss_texture_refs[3] = {
    {(s32)str_bos9_tp0_xs3, 0, 0},
    {(s32)str_bos9_tp1_xs3, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011CA20[4] = {
    {14, 14, 0x2000, 0}, {0x1D, 0x1D, 0x2000, 0}, {0x20, 0x25, 0x1000, 0}, {-1, 0, 0, 0},
};

ModelBlockRange D_8011CA40[2] = {
    {14, 14, -0x200, 0}, {-1, 0, 0, 0},
};

ModelBlockRange D_8011CA50[8] = {
    {0, 8, 0x1000, 0}, {9, 9, 0x1000, 0}, {10, 15, 0x1000, 0}, {0x10, 0x17, 0x800, 0},
    {0x18, 0x1F, 0x1000, 0}, {0x20, 0x2F, 0x800, 0}, {0x30, 0x7F, 0x1000, 0}, {-1, 0, 0, 0},
};

ModelBlock reactor_boss_model_block = {(s32)reactor_boss_palette_refs, (s32)reactor_boss_model_refs, (s32)reactor_boss_texture_refs, 0, (s32)D_8011CA20, (s32)D_8011CA40, (s32)D_8011CA50, 0, 0};

u8 *reactor_boss_ptr_table_ids[2] = {
    str_bos9_ch0cb4, NULL,
};

ScanEntry reactor_boss_entry = {{(s32)reactor_control_rods_m9_boss_update, 0}, reactor_boss_asset, (s32)&reactor_boss_model_block, (s32)reactor_boss_ptr_table_ids, 0};

struct ReactorControlRodsM9BossScripts {
    s16 start[4];
    s16 idle[4];
    s16 *table[2];
    s16 *reactor_boss_script_start;
} reactor_control_rods_m9_boss_scripts = {
    /* start */ {
        WAIT(30),
        REACTOR_CONTROL_RODS_M9_BOSS_STAGE_ENGINE_INIT,
    },
    /* idle */ {
        WAIT(1),
        JUMP(REACTOR_CONTROL_RODS_M9_BOSS_IDLE),
    },
    /* table */ {
        reactor_control_rods_m9_boss_scripts.start, reactor_control_rods_m9_boss_scripts.idle,
    },
    /* reactor_boss_script_start */ reactor_control_rods_m9_boss_scripts.start,
};

ScriptCallEntry reactor_boss_table[2] = {
    {NULL, 0}, {stage_engine_init, 0},
};

RecTemplate mission_end_fx[2] = {
    {3, 0x1F, 0x7F, 0xFF, 0, 8, 0x10000, 0x40000, -0x400, 0x10000},
    {3, 0xFF, 0xFF, 0xFF, 0, 8, 0x8000, 0x3E000, -0x400, 0x10000},
};

u32 ring_effect_points = 0x00000A08;

u32 D_8011CB34 = 0x00000000;

u32 D_8011CB38[30] = {
    0xFFFFFEB0, 0x00000000, 0x00000678, 0x00000000, 0xFFFFF7D8, 0x00000000,
    0xFFFFFF10, 0x00000000, 0xFFFFF598, 0x00000000, 0xFFFFF838, 0x00000000,
    0xFFFFF928, 0x00000000, 0xFFFFF5F8, 0x00000000, 0x00000090, 0x00000000,
    0xFFFFF9A0, 0x00000000, 0x00000764, 0x00000000, 0x000000F0, 0x00000000,
    0x000009A8, 0x00000000, 0x000007C8, 0x00000000, 0x00000618, 0x00000000,
};

EffectOffset aimed_effect_points[8] = {
    {-0xC0, -0x960, -0x8A0, 0}, {-0x660, -0x960, -0x5A0, 0}, {-0x840, -0x960, 0x60, 0},
    {-0x540, -0x960, 0x600, 0}, {0xC0, -0x960, 0x7E0, 0}, {0x660, -0x960, 0x4E0, 0},
    {0x840, -0x960, -0x120, 0}, {0x540, -0x960, -0x6C0, 0},
};

PylonAsset pylon_asset = {{-1, -1, -1}};

struct PylonAnims {
    s16 idle[4];
    s16 open[2];
    s16 open_loop[4];
    s16 charge[2];
    s16 charge_loop[4];
    s16 death[4];
    s16 dead[4];
    s16 *table[7];
} pylon_anims = {
    /* idle */ {
        STEP(1, 8),
        GOTO(PYLON_ANIM_IDLE),
    },
    /* open */ {
        STEP(1, 9),
    },
    /* open_loop */ {
        STEP(1, 9),
        GOTO(PYLON_ANIM_OPEN_LOOP),
    },
    /* charge */ {
        STEP(128, 10),
    },
    /* charge_loop */ {
        STEP(1, 10),
        GOTO(PYLON_ANIM_CHARGE_LOOP),
    },
    /* death */ {
        STEP(0, 11),
        STEP(4, 12),
    },
    /* dead */ {
        STEP(1, 12),
        GOTO(PYLON_ANIM_DEAD),
    },
    /* table */ {
        pylon_anims.idle, pylon_anims.open, pylon_anims.open_loop, pylon_anims.charge, pylon_anims.charge_loop, pylon_anims.death,
        pylon_anims.dead,
    },
};

struct PylonScripts {
    s16 link_script[6];
    s16 death[4];
    s16 death_delay[10];
    s16 death_sound[10];
    s16 dead_wait[6];
    s16 dead_idle[4];
    s16 *table[6];
    PylonLinkWord link_word;
} pylon_scripts = {
    /* link_script */ {
        WAIT(1),
        PYLON_SPAWN_CHILD_STREAM_READ_OP, PYLON_DEATH,
        JUMP(PYLON_LINK_SCRIPT),
    },
    /* death */ {
        PYLON_SPAWN_CHILD_ENEMY_KILL,
        NEXT_STATE(PYLON_SPAWN_CHILD_STATE_DEATH),
    },
    /* death_delay */ {
        WAIT(1),
        JUMP_UNLESS_STATE(PYLON_SPAWN_CHILD_STATE_DEATH_DELAY, PYLON_DEATH_DELAY),
        WAIT(48),
        NEXT_STATE(PYLON_SPAWN_CHILD_STATE_DEATH_SOUND),
    },
    /* death_sound */ {
        WAIT(1),
        JUMP_UNLESS_STATE(PYLON_SPAWN_CHILD_STATE_DEATH_SOUND_WAIT, PYLON_DEATH_SOUND),
        WAIT(10),
        NEXT_STATE(PYLON_SPAWN_CHILD_STATE_DEATH_SOUND_STOP),
    },
    /* dead_wait */ {
        WAIT(1),
        JUMP_UNLESS_STATE(PYLON_SPAWN_CHILD_STATE_DEAD, PYLON_DEAD_WAIT),
    },
    /* dead_idle */ {
        WAIT(1),
        JUMP(PYLON_DEAD_IDLE),
    },
    /* table */ {
        pylon_scripts.link_script, pylon_scripts.death, pylon_scripts.death_delay, pylon_scripts.death_sound, pylon_scripts.dead_wait, pylon_scripts.dead_idle,
    },
    /* link_word */ {pylon_scripts.link_script},
};

ScriptCallEntry pylon_call_table[3] = {
    {NULL, 0}, {obj_stream_read_op, 0}, {enemy_kill, 0},
};

DeathPiece enemy_death_points[6] = {
    {-0x27, 0, -0x65, 0}, {-0x6B, 0, -0x12, 0}, {-0x45, 0, 0x53, 0}, {0x26, 0, 0x64, 0}, {0x6A, 0, 0x10, 0},
    {0x44, 0, -0x53, 0},
};

StateEntry pylon_state_table[7] = {
    {0, PYLON_ANIM_IDLE, 0},
    {0, PYLON_ANIM_OPEN, 1},
    {0, -1, 0},
    {(u32)enemy_sound_start, PYLON_ANIM_CHARGE, 0},
    {0, -1, 0},
    {(u32)enemy_sound_stop_cue, PYLON_ANIM_DEATH, 1},
    {0, -1, 0},
};

s32 obj_size_table[5] = {
    0x210, 0x210, 0x84, 0x60, 12,
};

u32 part_asset_buf[3] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
};

struct SpawnPartAnims {
    s16 idle[4];
    s16 *table[1];
} spawn_part_anims = {
    /* idle */ {
        STEP(1, 17),
        GOTO(SPAWN_PART_ANIM_IDLE),
    },
    /* table */ {
        (s16 *)spawn_part_anims.idle,
    },
};

u32 part_kind_params = 0xFFFFFF40;

u32 dual_mech_script_table = 0xFFFFF6A0;

u32 D_8011CDD8[30] = {
    0xFFFFF760, 0x00000000, 0xFFFFF9A0, 0xFFFFF6A0, 0xFFFFFA60, 0x00000000,
    0xFFFFF7C0, 0xFFFFF6A0, 0x00000060, 0x00000000, 0xFFFFFAC0, 0xFFFFF6A0,
    0x00000600, 0x00000000, 0x000000C0, 0xFFFFF6A0, 0x000007E0, 0x00000000,
    0x00000660, 0xFFFFF6A0, 0x000004E0, 0x00000000, 0x00000840, 0xFFFFF6A0,
    0xFFFFFEE0, 0x00000000, 0x00000540, 0xFFFFF6A0, 0xFFFFF940, 0x00000000,
};

struct SpawnPartScripts {
    s16 await_boss[8];
    s16 hover[6];
    s16 hover_scan[10];
    s16 track[6];
    s16 track_fire[8];
    s16 laser_hold[6];
    s16 *table[6];
    s16 *D_8011CEC0;
} spawn_part_scripts = {
    /* await_boss */ {
        NEXT_STATE(OBJ_SPAWN_PART_STATE_HOVER),
        WAIT(1),
        OBJ_SPAWN_PART_JUMP_ON_FLAG, SPAWN_PART_HOVER,
        JUMP(SPAWN_PART_AWAIT_BOSS),
    },
    /* hover */ {
        NEXT_STATE(OBJ_SPAWN_PART_STATE_HOVER),
        SET_COUNTER_RANDOM(64, 64),
    },
    /* hover_scan */ {
        WAIT(1),
        LOOP(SPAWN_PART_HOVER_SCAN),
        OBJ_SPAWN_PART_JUMP_NEAR, 2688, SPAWN_PART_TRACK,
        JUMP(SPAWN_PART_HOVER),
    },
    /* track */ {
        NEXT_STATE(OBJ_SPAWN_PART_STATE_TRACK),
        SET_COUNTER_RANDOM(64, 128),
    },
    /* track_fire */ {
        WAIT(1),
        LOOP(SPAWN_PART_TRACK_FIRE),
        OBJ_SPAWN_PART_JUMP_FAR, 2688, SPAWN_PART_HOVER,
        OBJ_SPAWN_PART_BOSS_LASER_INIT,
    },
    /* laser_hold */ {
        WAIT(1),
        OBJ_SPAWN_PART_JUMP_LINKED, SPAWN_PART_LASER_HOLD,
        JUMP(SPAWN_PART_TRACK),
    },
    /* table */ {
        spawn_part_scripts.await_boss, spawn_part_scripts.hover, spawn_part_scripts.hover_scan, spawn_part_scripts.track, spawn_part_scripts.track_fire, spawn_part_scripts.laser_hold,
    },
    /* D_8011CEC0 */ spawn_part_scripts.await_boss,
};

ScriptCallEntry D_8011CEC4[6] = {
    {NULL, 0}, {obj_boss_laser_init, 0}, {obj_script_jump_linked, 0},
    {obj_script_jump_on_flag, 0}, {obj_script_jump_far, 0}, {obj_script_jump_near, 0},
};

StateEntry D_8011CEF4[2] = {
    {(u32)homing_move, SPAWN_PART_ANIM_IDLE, 0},
    {(u32)homing_steer_player, SPAWN_PART_ANIM_IDLE, 0},
};

FxRecordParams fade_fx_params = {1, 0xFF, 0xFF, 0, 0, 0x100, {0x4000, 0x14000, -0x1000, 0x4000}};

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_80121A9C[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/tint_scale_r.c"

s16 video_mode_id = 0;

#include "../stage/data/debug_cam_speed_table.c"

#include "../stage/data/pause_prev_work_area.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_80122C20[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_80123240 = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

s32 stage_ctrl_index = 0;

s32 spark_model_index_base = 0;

s32 view_nudge_toggle = 0;

s32 elevator_done_flag = 0;

#include "../stage/data/model_pchr_saved.c"

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

u32 D_80124764 = 0x00000000;

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

u32 D_801247E8 = 0x00000000;

#include "../stage/data/pause_flag.c"

#include "../stage/data/cell_cursor_step1.c"

#include "../stage/data/cell_cursor_step2.c"

#include "../stage/data/cell_cursor_step1_saved.c"

#include "../stage/data/cell_cursor_step2_saved.c"

/* labels inside the objects above */
__asm__(".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl msg_y\n.set msg_y, rcossin_tbl+0x2E46\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl D_80123246\n.set D_80123246, texture_image+0x2\n"
        ".globl D_8011B938\n.set D_8011B938, elevator_edges+0x8\n"
        ".globl elevator_ride_flag\n.set elevator_ride_flag, elevator_edges+0xC\n"
        ".globl D_8011B940\n.set D_8011B940, elevator_edges+0x10\n"
        ".globl D_8011B948\n.set D_8011B948, elevator_edges+0x18\n"
        ".globl enemy_shot_id\n.set enemy_shot_id, enemy_shot_setup+0xC\n"
        ".globl D_8011CBB4\n.set D_8011CBB4, aimed_effect_points+0x4\n"
        ".globl D_8011CBB8\n.set D_8011CBB8, aimed_effect_points+0x8\n"
        ".globl sincos_deg90\n.set sincos_deg90, rcossin_tbl+0x1000\n"
        ".globl view_sincos\n.set view_sincos, rcossin_tbl+0x2000\n"
        ".globl gun_turret_asset_s12\n.set gun_turret_asset_s12, rcossin_tbl+0x202C\n"
        ".globl muzzle_x_table_s12\n.set muzzle_x_table_s12, rcossin_tbl+0x2144\n"
        ".globl muzzle_y_table_s12\n.set muzzle_y_table_s12, rcossin_tbl+0x2150\n"
        ".globl fuchikoma_state_table_s12\n.set fuchikoma_state_table_s12, rcossin_tbl+0x23F4\n"
        ".globl enemy_count\n.set enemy_count, rcossin_tbl+0x2E1C\n"
        ".globl spin_angle\n.set spin_angle, rcossin_tbl+0x2E40\n"
        ".globl msg_x\n.set msg_x, rcossin_tbl+0x2E44\n"
        ".globl hurry_msg_shown\n.set hurry_msg_shown, rcossin_tbl+0x2E4C\n"
        ".globl D_8011FEEC\n.set D_8011FEEC, rcossin_tbl+0x2E50\n"
        ".globl sincos_deg270\n.set sincos_deg270, rcossin_tbl+0x3000\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl heavy_mobile_suit_script\n.set heavy_mobile_suit_script, heavy_mobile_suit_anims+0x0\n"
        ".globl heavy_mobile_suit_anim_patrol_enter\n.set heavy_mobile_suit_anim_patrol_enter, heavy_mobile_suit_anims+0x8\n"
        ".globl heavy_mobile_suit_anim_search_hold\n.set heavy_mobile_suit_anim_search_hold, heavy_mobile_suit_anims+0x20\n"
        ".globl heavy_mobile_suit_anim_search_end\n.set heavy_mobile_suit_anim_search_end, heavy_mobile_suit_anims+0x28\n"
        ".globl heavy_mobile_suit_anim_alt_enter\n.set heavy_mobile_suit_anim_alt_enter, heavy_mobile_suit_anims+0x40\n"
        ".globl heavy_mobile_suit_anim_alt_hold\n.set heavy_mobile_suit_anim_alt_hold, heavy_mobile_suit_anims+0x58\n"
        ".globl heavy_mobile_suit_anim_alt_end\n.set heavy_mobile_suit_anim_alt_end, heavy_mobile_suit_anims+0x60\n"
        ".globl heavy_mobile_suit_anim_spotted_enter\n.set heavy_mobile_suit_anim_spotted_enter, heavy_mobile_suit_anims+0x78\n"
        ".globl heavy_mobile_suit_anim_pursue_enter\n.set heavy_mobile_suit_anim_pursue_enter, heavy_mobile_suit_anims+0x90\n"
        ".globl heavy_mobile_suit_anim_pursue_alt_enter\n.set heavy_mobile_suit_anim_pursue_alt_enter, heavy_mobile_suit_anims+0xB0\n"
        ".globl heavy_mobile_suit_anim_approach_hold\n.set heavy_mobile_suit_anim_approach_hold, heavy_mobile_suit_anims+0xD0\n"
        ".globl heavy_mobile_suit_anim_fire_enter\n.set heavy_mobile_suit_anim_fire_enter, heavy_mobile_suit_anims+0xD8\n"
        ".globl heavy_mobile_suit_anim_disengage\n.set heavy_mobile_suit_anim_disengage, heavy_mobile_suit_anims+0xF0\n"
        ".globl heavy_mobile_suit_data\n.set heavy_mobile_suit_data, heavy_mobile_suit_anims+0x104\n"
        ".globl heavy_mobile_suit_place_select\n.set heavy_mobile_suit_place_select, heavy_mobile_suit_place_scripts+0x0\n"
        ".globl heavy_mobile_suit_place_far_aim\n.set heavy_mobile_suit_place_far_aim, heavy_mobile_suit_place_scripts+0xC\n"
        ".globl heavy_mobile_suit_place_spotted\n.set heavy_mobile_suit_place_spotted, heavy_mobile_suit_place_scripts+0x14\n"
        ".globl heavy_mobile_suit_place_idle\n.set heavy_mobile_suit_place_idle, heavy_mobile_suit_place_scripts+0x34\n"
        ".globl heavy_mobile_suit_place_idle_loop\n.set heavy_mobile_suit_place_idle_loop, heavy_mobile_suit_place_scripts+0x44\n"
        ".globl heavy_mobile_suit_place_fire_start\n.set heavy_mobile_suit_place_fire_start, heavy_mobile_suit_place_scripts+0x58\n"
        ".globl heavy_mobile_suit_place_fire_start_loop\n.set heavy_mobile_suit_place_fire_start_loop, heavy_mobile_suit_place_scripts+0x68\n"
        ".globl heavy_mobile_suit_place_chase\n.set heavy_mobile_suit_place_chase, heavy_mobile_suit_place_scripts+0x74\n"
        ".globl heavy_mobile_suit_place_chase_wait\n.set heavy_mobile_suit_place_chase_wait, heavy_mobile_suit_place_scripts+0x84\n"
        ".globl heavy_mobile_suit_place_chase_pursue\n.set heavy_mobile_suit_place_chase_pursue, heavy_mobile_suit_place_scripts+0x90\n"
        ".globl heavy_mobile_suit_place_chase_pursue_loop\n.set heavy_mobile_suit_place_chase_pursue_loop, heavy_mobile_suit_place_scripts+0xA0\n"
        ".globl heavy_mobile_suit_place_chase_end\n.set heavy_mobile_suit_place_chase_end, heavy_mobile_suit_place_scripts+0xB4\n"
        ".globl heavy_mobile_suit_place_fire_aim\n.set heavy_mobile_suit_place_fire_aim, heavy_mobile_suit_place_scripts+0xC4\n"
        ".globl heavy_mobile_suit_place_fire_aim_loop\n.set heavy_mobile_suit_place_fire_aim_loop, heavy_mobile_suit_place_scripts+0xD4\n"
        ".globl heavy_mobile_suit_place_aim_chase\n.set heavy_mobile_suit_place_aim_chase, heavy_mobile_suit_place_scripts+0xE0\n"
        ".globl heavy_mobile_suit_place_aim_chase_loop\n.set heavy_mobile_suit_place_aim_chase_loop, heavy_mobile_suit_place_scripts+0xF0\n"
        ".globl heavy_mobile_suit_place_aim_pursue\n.set heavy_mobile_suit_place_aim_pursue, heavy_mobile_suit_place_scripts+0xFC\n"
        ".globl heavy_mobile_suit_place_aim_pursue_loop\n.set heavy_mobile_suit_place_aim_pursue_loop, heavy_mobile_suit_place_scripts+0x10C\n"
        ".globl heavy_mobile_suit_place_aim_end\n.set heavy_mobile_suit_place_aim_end, heavy_mobile_suit_place_scripts+0x120\n"
        ".globl heavy_mobile_suit_place_aim_fire\n.set heavy_mobile_suit_place_aim_fire, heavy_mobile_suit_place_scripts+0x130\n"
        ".globl heavy_mobile_suit_place_aim_fire_loop\n.set heavy_mobile_suit_place_aim_fire_loop, heavy_mobile_suit_place_scripts+0x140\n"
        ".globl heavy_mobile_suit_place_fire_burst\n.set heavy_mobile_suit_place_fire_burst, heavy_mobile_suit_place_scripts+0x14C\n"
        ".globl heavy_mobile_suit_place_fire_burst_loop\n.set heavy_mobile_suit_place_fire_burst_loop, heavy_mobile_suit_place_scripts+0x168\n"
        ".globl heavy_mobile_suit_place_cooldown\n.set heavy_mobile_suit_place_cooldown, heavy_mobile_suit_place_scripts+0x174\n"
        ".globl heavy_mobile_suit_place_cooling\n.set heavy_mobile_suit_place_cooling, heavy_mobile_suit_place_scripts+0x184\n"
        ".globl heavy_mobile_suit_place_disengage\n.set heavy_mobile_suit_place_disengage, heavy_mobile_suit_place_scripts+0x19C\n"
        ".globl heavy_mobile_suit_place_disengage_loop\n.set heavy_mobile_suit_place_disengage_loop, heavy_mobile_suit_place_scripts+0x1BC\n"
        ".globl heavy_mobile_suit_place_settle\n.set heavy_mobile_suit_place_settle, heavy_mobile_suit_place_scripts+0x1CC\n"
        ".globl heavy_mobile_suit_place_restart\n.set heavy_mobile_suit_place_restart, heavy_mobile_suit_place_scripts+0x1D8\n"
        ".globl heavy_mobile_suit_script_data\n.set heavy_mobile_suit_script_data, heavy_mobile_suit_place_scripts+0x1DC\n"
        ".globl D_8011BDB4\n.set D_8011BDB4, heavy_mobile_suit_place_scripts+0x250\n"
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
        ".globl triple_barrel_robot_anim_idle\n.set triple_barrel_robot_anim_idle, triple_barrel_robot_anims+0x0\n"
        ".globl triple_barrel_robot_anim_fire\n.set triple_barrel_robot_anim_fire, triple_barrel_robot_anims+0x8\n"
        ".globl triple_barrel_robot_anim_walk\n.set triple_barrel_robot_anim_walk, triple_barrel_robot_anims+0x3C\n"
        ".globl triple_barrel_robot_data\n.set triple_barrel_robot_data, triple_barrel_robot_anims+0x48\n"
        ".globl walker_mech_begin\n.set walker_mech_begin, triple_barrel_robot_script_table_streams+0x0\n"
        ".globl walker_mech_patrol_start\n.set walker_mech_patrol_start, triple_barrel_robot_script_table_streams+0x4\n"
        ".globl walker_mech_watch\n.set walker_mech_watch, triple_barrel_robot_script_table_streams+0xC\n"
        ".globl walker_mech_engage_wait\n.set walker_mech_engage_wait, triple_barrel_robot_script_table_streams+0x1C\n"
        ".globl walker_mech_engage\n.set walker_mech_engage, triple_barrel_robot_script_table_streams+0x28\n"
        ".globl triple_barrel_robot_fire_end\n.set triple_barrel_robot_fire_end, triple_barrel_robot_script_table_streams+0x2C\n"
        ".globl triple_barrel_robot_cooldown\n.set triple_barrel_robot_cooldown, triple_barrel_robot_script_table_streams+0x3C\n"
        ".globl triple_barrel_robot_script_table\n.set triple_barrel_robot_script_table, triple_barrel_robot_script_table_streams+0x4C\n"
        ".globl d_8011C260\n.set d_8011C260, triple_barrel_robot_script_table_streams+0x68\n"
        ".globl rocket_drone_anim_idle\n.set rocket_drone_anim_idle, rocket_drone_anims+0x0\n"
        ".globl rocket_drone_data\n.set rocket_drone_data, rocket_drone_anims+0x8\n"
        ".globl rocket_drone_restart\n.set rocket_drone_restart, rocket_drone_scripts+0x0\n"
        ".globl rocket_drone_select\n.set rocket_drone_select, rocket_drone_scripts+0x4\n"
        ".globl rocket_drone_patrol\n.set rocket_drone_patrol, rocket_drone_scripts+0x14\n"
        ".globl rocket_drone_spotted\n.set rocket_drone_spotted, rocket_drone_scripts+0x24\n"
        ".globl rocket_drone_idle_start\n.set rocket_drone_idle_start, rocket_drone_scripts+0x34\n"
        ".globl rocket_drone_idle\n.set rocket_drone_idle, rocket_drone_scripts+0x3C\n"
        ".globl rocket_drone_cooldown\n.set rocket_drone_cooldown, rocket_drone_scripts+0x50\n"
        ".globl rocket_drone_anim\n.set rocket_drone_anim, rocket_drone_scripts+0x58\n"
        ".globl d_80116CC0\n.set d_80116CC0, rocket_drone_scripts+0x74\n"
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
        ".globl reactor_control_rods_m9_boss_start\n.set reactor_control_rods_m9_boss_start, reactor_control_rods_m9_boss_scripts+0x0\n"
        ".globl reactor_control_rods_m9_boss_idle\n.set reactor_control_rods_m9_boss_idle, reactor_control_rods_m9_boss_scripts+0x8\n"
        ".globl reactor_boss_script_data\n.set reactor_boss_script_data, reactor_control_rods_m9_boss_scripts+0x10\n"
        ".globl reactor_boss_script_start\n.set reactor_boss_script_start, reactor_control_rods_m9_boss_scripts+0x18\n"
        ".globl pylon_anim_idle\n.set pylon_anim_idle, pylon_anims+0x0\n"
        ".globl pylon_anim_open\n.set pylon_anim_open, pylon_anims+0x8\n"
        ".globl pylon_anim_open_loop\n.set pylon_anim_open_loop, pylon_anims+0xC\n"
        ".globl pylon_anim_charge\n.set pylon_anim_charge, pylon_anims+0x14\n"
        ".globl pylon_anim_charge_loop\n.set pylon_anim_charge_loop, pylon_anims+0x18\n"
        ".globl pylon_anim_death\n.set pylon_anim_death, pylon_anims+0x20\n"
        ".globl pylon_anim_dead\n.set pylon_anim_dead, pylon_anims+0x28\n"
        ".globl pylon_data\n.set pylon_data, pylon_anims+0x30\n"
        ".globl pylon_link_script\n.set pylon_link_script, pylon_scripts+0x0\n"
        ".globl pylon_death\n.set pylon_death, pylon_scripts+0xC\n"
        ".globl pylon_death_delay\n.set pylon_death_delay, pylon_scripts+0x14\n"
        ".globl pylon_death_sound\n.set pylon_death_sound, pylon_scripts+0x28\n"
        ".globl pylon_dead_wait\n.set pylon_dead_wait, pylon_scripts+0x3C\n"
        ".globl pylon_dead_idle\n.set pylon_dead_idle, pylon_scripts+0x48\n"
        ".globl pylon_script_data\n.set pylon_script_data, pylon_scripts+0x50\n"
        ".globl pylon_link_word\n.set pylon_link_word, pylon_scripts+0x68\n"
        ".globl spawn_part_anim_idle\n.set spawn_part_anim_idle, spawn_part_anims+0x0\n"
        ".globl part_scripts\n.set part_scripts, spawn_part_anims+0x8\n"
        ".globl spawn_part_await_boss\n.set spawn_part_await_boss, spawn_part_scripts+0x0\n"
        ".globl spawn_part_hover\n.set spawn_part_hover, spawn_part_scripts+0x10\n"
        ".globl spawn_part_hover_scan\n.set spawn_part_hover_scan, spawn_part_scripts+0x1C\n"
        ".globl spawn_part_track\n.set spawn_part_track, spawn_part_scripts+0x30\n"
        ".globl spawn_part_track_fire\n.set spawn_part_track_fire, spawn_part_scripts+0x3C\n"
        ".globl spawn_part_laser_hold\n.set spawn_part_laser_hold, spawn_part_scripts+0x4C\n"
        ".globl D_8011CEA8\n.set D_8011CEA8, spawn_part_scripts+0x58\n"
        ".globl D_8011CEC0\n.set D_8011CEC0, spawn_part_scripts+0x70\n");
