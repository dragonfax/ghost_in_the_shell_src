/* s04 data 0x80118DD0-0x80122800: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s04_types.h"
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
extern void cursor_read_u16();
extern void cursor_read_u16_globals();
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
extern void escaping_boat_m4_boss_spawn();
extern void fighter_jet_spawn();
extern u8 file_bos4_ch0_cb4[];
extern u8 file_bos4_ch0_clt[];
extern u8 file_bos4_ch0_vx1[];
extern u8 file_bos4_tp0_xs3[];
extern u8 file_bos4_tp1_clt[];
extern u8 file_bos4_tp1_xs3[];
extern u8 file_flip_ch0_cb4[];
extern u8 file_flip_ch0_clt[];
extern u8 file_flip_ch0_vx1[];
extern u8 file_flip_tp0_clt[];
extern u8 file_flip_tp0_xs3[];
extern u8 file_kira_ch0_cb4[];
extern u8 file_kira_ch0_clt[];
extern u8 file_kira_ch0_vx1[];
extern u8 file_kira_tp0_clt[];
extern u8 file_kira_tp0_xs3[];
extern u8 file_mjet_ch0_cb4[];
extern u8 file_mjet_ch0_clt[];
extern u8 file_mjet_ch0_vx1[];
extern u8 file_mjet_tp0_clt[];
extern u8 file_mjet_tp0_xs3[];
extern u8 file_msgs_spr_clt[];
extern u8 file_msgs_spr_grc[];
extern u8 file_msgs_spr_so3[];
extern u8 file_seaf_ch0_cb4[];
extern u8 file_seaf_ch0_clt[];
extern u8 file_seaf_ch0_vx1[];
extern u8 file_seaf_tp0_clt[];
extern u8 file_seaf_tp0_xs3[];
extern void fly_pair_update();
extern void fly_shoot_update();
extern void fly_sweep();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void heavy_mobile_suit_spawn();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void jetski_spawn();
extern void laser_barrier_boat_spawn_placed();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void moving_pyramid_mine_phase0();
extern void obj_aim_and_fire();
extern void obj_area_update();
extern void obj_call_hook();
extern void obj_cursor_read_jump();
extern void obj_face_point_xz();
extern void obj_fade_level();
extern void obj_fly_update();
extern void obj_fly_velocity();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_init_aim_at_camera();
extern void obj_jump_if_player_near();
extern void obj_play_sound_here();
extern void obj_pursue_step();
extern void obj_pursue_update();
extern void obj_read_next_state();
extern void obj_read_unk_242();
extern void obj_release_check();
extern void obj_script_jump_if_beyond();
extern void obj_script_jump_if_within();
extern void obj_script_muzzle_shot();
extern void obj_script_read_u16();
extern void obj_script_read_value();
extern void obj_script_set_258();
extern void obj_script_set_angle();
extern void obj_script_set_fly_mode();
extern void obj_script_set_selector();
extern void obj_script_set_sound();
extern void obj_set_next_state();
extern void obj_sound_volume_update();
extern void obj_spawn_effect_offset();
extern void obj_speed_approach();
extern void obj_turn_to_rest();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void ramp_start_script();
extern void rocket_boat_fire();
extern void rocket_boat_fire_aimed();
extern void rocket_boat_fire_drift();
extern void rocket_boat_fire_near();
extern void script_jump_if_height();
extern void script_jump_if_key();
extern void script_jump_if_mission_flag();
extern void script_jump_if_wanted_matches();
extern void script_op_jump_table_if_player_far();
extern void script_read_param();
extern void script_read_speed();
extern void script_set_turn_mode();
extern void script_step();
extern void sea_mine_spawn();
extern void seq_branch_on_match();
extern void sound_driver_spawn();
extern void sound_volume_phase2();
extern void sound_volume_ramp();
extern void stage_spawn_slots_reset();
extern void stage_start();
extern u8 str_com_dat_fac[];
extern u8 str_ctl4_ch0_vx1[];
extern u8 str_ctl4_tp0_clt[];
extern u8 str_ctl4_tp0_xs3[];
extern u8 str_enemy_bos4_data[];
extern u8 str_enemy_ctl4_data[];
extern u8 str_enemy_flip_data[];
extern u8 str_enemy_kira_data[];
extern u8 str_enemy_lan2_data[];
extern u8 str_enemy_mjet_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_sea2_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_land_ch0_clt[];
extern u8 str_land_ch0_vx1[];
extern u8 str_land_ch0cb4[];
extern u8 str_land_tp0_clt[];
extern u8 str_land_tp0_xs3[];
extern u8 str_land_tp1_clt[];
extern u8 str_land_tp1_xs3[];
extern u8 str_m04_dat_fac[];
extern u8 str_m21_cnf_bcf[];
extern u8 str_m21_joy_bin[];
extern u8 str_main_data[];
extern u8 str_mrn_apdea3[];
extern u8 str_mrn_cnf_bcf[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_s04_boss[];
extern u8 str_s04_dat_fac[];
extern u8 str_s04_ene_fac[];
extern u8 str_s04_joy_bin[];
extern u8 str_s04_miss[];
extern u8 str_s04_stage[];
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
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_80119BA2[];
extern u8 D_8011A294[];
extern u8 D_8012101E[];
extern u8 D_801226E6[];
extern u8 cos_table[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 d_801201AE[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 enemy_gun_shot_id[];
extern u8 flow_angle[];
extern u8 gun_hit_effect_table[];
extern u8 muzzle_yaw_table[];
extern u8 script_mode0_reg1[];
extern u8 script_mode1_reg1[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 view_sincos[];
extern s32 area;
extern ScanItem area_scan_items[];
extern AreaEntry D_80118E1C;
extern AreaEntry D_80118E44;
extern u32 D_80118E6C[];
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern s32 laser_barrier_boat_asset[];
extern ModelBlockRef D_80118F74[];
extern ModelBlockRef D_80118F8C[];
extern ModelBlockRef D_80118F9C[];
extern ModelBlockRange D_80118FAC[];
extern ModelBlock flip_model_block;
extern u8 *D_80118FE0[];
extern ScanEntry flip_scan_entry;
extern u32 D_80119000[];
extern s16 laser_barrier_boat_script[];
extern s16 *laser_barrier_boat_data[];
extern s16 laser_barrier_boat_select[];
extern s16 laser_barrier_boat_fly[];
extern s16 laser_barrier_boat_mine[];
extern s16 laser_barrier_boat_mine_idle[];
extern s16 laser_barrier_boat_fly_wait[];
extern s16 laser_barrier_boat_recheck[];
extern s16 *laser_barrier_boat_type_data[];
extern s16 *D_80119070;
extern ScriptCallEntry D_80119074[];
extern StateEntry D_8011909C[];
extern s32 jetski_asset[];
extern ModelBlockRef D_801190B8[];
extern ModelBlockRef D_801190D0[];
extern ModelBlockRef D_801190E0[];
extern ModelBlockRange D_801190F0[];
extern ModelBlock D_80119100;
extern u8 *D_80119124[];
extern ScanEntry jetski_scan_entry;
extern s16 jetski_anim_ride[];
extern s16 jetski_anim_bank_in_a[];
extern s16 jetski_anim_bank_hold_a[];
extern s16 jetski_anim_bank_out_a[];
extern s16 jetski_anim_bank_in_b[];
extern s16 jetski_anim_bank_hold_b[];
extern s16 jetski_anim_bank_out_b[];
extern s16 jetski_anim_aim_raise[];
extern s16 jetski_anim_aim_hold[];
extern s16 jetski_anim_aim_lower[];
extern s16 jetski_anim_fire[];
extern s16 D_801191D4[];
extern s16 D_80119200[];
extern s16 *jetski_data[11];
extern s16 *jetski_script_table[];
extern s16 jetski_wait_approach[];
extern s16 jetski_aim[];
extern s16 jetski_fire_start[];
extern s16 jetski_fire_shot[];
extern s16 jetski_fire_loop[];
extern s16 jetski_turn_back[];
extern s16 jetski_idle_start[];
extern s16 jetski_idle_wait[];
extern s16 jetski_halt[];
extern s16 jetski_wait_side_slide[];
extern s16 jetski_side_aim[];
extern s16 jetski_side_fire_start[];
extern s16 jetski_side_fire_shot[];
extern s16 jetski_side_fire_loop[];
extern s16 jetski_side_turn_back[];
extern s16 jetski_side_idle_start[];
extern s16 jetski_side_idle_wait[];
extern s16 jetski_side_exit_wait[];
extern s16 jetski_approach_aim[];
extern s16 jetski_approach_fire_start[];
extern s16 jetski_approach_fire_shot[];
extern s16 jetski_approach_fire_loop[];
extern s16 jetski_approach_turn_back[];
extern s16 jetski_approach_idle_start[];
extern s16 jetski_approach_idle_wait[];
extern s16 jetski_approach_halt[];
extern s16 *jetski_type_data[];
extern s16 *D_8011941C[];
extern ScriptCallEntry jetski_call_table[];
extern StateEntry D_80119434[];
extern GunSetup enemy_gun_setup;
extern s32 heavy_mobile_suit_asset[3];
extern ModelBlockRef d_801194DC[];
extern ModelBlockRef d_801194FC[];
extern ModelBlockRef d_80119514[];
extern ModelBlockRange d_80119524[];
extern ModelBlock heavy_mobile_suit_model_block;
extern u8 *d_80119560[];
extern ScanEntry D_80119568;
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
extern s16 heavy_mobile_suit_cycle[];
extern s16 heavy_mobile_suit_patrol_start[];
extern s16 heavy_mobile_suit_scan[];
extern s16 heavy_mobile_suit_idle[];
extern s16 heavy_mobile_suit_idle_watch[];
extern s16 heavy_mobile_suit_spotted[];
extern s16 heavy_mobile_suit_spotted_wait[];
extern s16 heavy_mobile_suit_patrol[];
extern s16 heavy_mobile_suit_patrol_wait[];
extern s16 heavy_mobile_suit_search[];
extern s16 heavy_mobile_suit_search_watch[];
extern s16 heavy_mobile_suit_search_end[];
extern s16 heavy_mobile_suit_pursue[];
extern s16 heavy_mobile_suit_pursue_wait[];
extern s16 heavy_mobile_suit_fire_burst[];
extern s16 heavy_mobile_suit_fire_wait[];
extern s16 heavy_mobile_suit_cooldown[];
extern s16 heavy_mobile_suit_cooling[];
extern s16 heavy_mobile_suit_disengage[];
extern s16 heavy_mobile_suit_disengage_wait[];
extern s16 heavy_mobile_suit_search_done[];
extern s16 heavy_mobile_suit_restart[];
extern s16 *heavy_mobile_suit_type_data[];
extern s16 *D_80119860;
extern ScriptCallEntry heavy_mobile_suit_call_table[11];
extern StateEntry heavy_mobile_suit_state_table[13];
extern s32 D_80119924[];
extern ModelBlockRef fighter_jet_palette_refs[];
extern ModelBlockRef fighter_jet_texture_refs[];
extern ModelBlockRef fighter_jet_model_refs[];
extern ModelBlock fighter_jet_model_block;
extern u8 *fighter_jet_file_list[];
extern ScanEntry fighter_jet_sea2_scan_entry;
extern FxRecordParams fx_send_rec34_params_a;
extern FxRecordParams fx_send_rec34_params_b;
extern RecTemplate fx_send_template_a;
extern RecTemplate fx_send_template_b;
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
extern s32 sea_mine_asset[];
extern ModelBlockRef sea_mine_palettes[];
extern ModelBlockRef sea_mine_textures[];
extern ModelBlockRef sea_mine_models[];
extern ModelBlockRange D_80119B3C[];
extern ModelBlock sea_mine_model_block;
extern u8 *D_80119B80[];
extern ScanEntry sea_mine_scan_entry;
extern u16 sea_mine_anim_frames[];
extern StateEntry d_80116F10[];
extern s16 sea_mine_script[];
extern s16 *sea_mine_script_arg[];
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *enemy_msgs_files[];
extern ScanEntry enemy_msgs_entry;
extern ModelBlockRef D_80119C58[];
extern ModelBlockRef D_80119C68[];
extern ModelBlockRef D_80119C78[];
extern ModelBlockRange D_80119C88[];
extern ModelBlock D_80119C98;
extern ModelSlotHead spark_model_index;
extern ScanEntry D_80119CC8;
extern u8 span_table[];
extern s32 D_80119DA4[];
extern LightData stage_data_base;
extern s32 boss_active_flag;
extern s32 boss_meter_flag;
extern s32 d_80119E84;
extern s32 boss_retreat_flag;
extern s32 rocket_boat_count;
extern s32 escaping_boat_m4_boss_asset[];
extern ModelBlockRef escaping_boat_boss_palettes[];
extern ModelBlockRef escaping_boat_boss_models[];
extern ModelBlockRef escaping_boat_boss_textures[];
extern ModelBlockRange D_80119EDC[];
extern ModelBlockRange D_80119F14[];
extern ModelBlock escaping_boat_boss_model_block;
extern u8 *D_80119F98[];
extern ScanEntry escaping_boat_boss_scan_entry;
extern s16 escaping_boat_m4_boss_anim_idle[];
extern s16 escaping_boat_m4_boss_anim_fire_start[];
extern s16 escaping_boat_m4_boss_anim_fire_loop[];
extern s16 escaping_boat_m4_boss_anim_cooldown[];
extern s16 *escaping_boat_m4_boss_data[];
extern s16 escaping_boat_m4_boss_dispatch[];
extern s16 escaping_boat_m4_boss_pick_turn[];
extern s16 escaping_boat_m4_boss_turn_hub[];
extern s16 escaping_boat_m4_boss_choose_attack[];
extern s16 escaping_boat_m4_boss_attack_a_alt[];
extern s16 escaping_boat_m4_boss_attack_a_alt2[];
extern s16 escaping_boat_m4_boss_turn_start[];
extern s16 escaping_boat_m4_boss_turn_hold[];
extern s16 escaping_boat_m4_boss_turn_hold_a_alt[];
extern s16 escaping_boat_m4_boss_attack_b[];
extern s16 escaping_boat_m4_boss_attack_b_alt[];
extern s16 escaping_boat_m4_boss_attack_b_alt2[];
extern s16 escaping_boat_m4_boss_turn_start_b[];
extern s16 escaping_boat_m4_boss_turn_hold_b[];
extern s16 escaping_boat_m4_boss_turn_hold_b_alt[];
extern s16 escaping_boat_m4_boss_attack_c[];
extern s16 escaping_boat_m4_boss_attack_c_alt[];
extern s16 escaping_boat_m4_boss_attack_c_alt2[];
extern s16 escaping_boat_m4_boss_turn_start_c[];
extern s16 escaping_boat_m4_boss_turn_hold_c[];
extern s16 escaping_boat_m4_boss_turn_hold_c_alt[];
extern s16 escaping_boat_m4_boss_attack_d[];
extern s16 escaping_boat_m4_boss_attack_d_alt[];
extern s16 escaping_boat_m4_boss_attack_d_alt2[];
extern s16 escaping_boat_m4_boss_turn_start_d[];
extern s16 escaping_boat_m4_boss_turn_hold_d[];
extern s16 escaping_boat_m4_boss_turn_hold_d_alt[];
extern s16 escaping_boat_m4_boss_rocket_volley_start[];
extern s16 escaping_boat_m4_boss_rocket_volley[];
extern s16 escaping_boat_m4_boss_rocket_volley_repeat[];
extern u16 stream_last_u16;
extern s16 escaping_boat_m4_boss_aim_start[];
extern s16 escaping_boat_m4_boss_fire_pick[];
extern s16 escaping_boat_m4_boss_fire_burst_a[];
extern s16 escaping_boat_m4_boss_fire_burst_b[];
extern s16 escaping_boat_m4_boss_fire_burst_c[];
extern s16 escaping_boat_m4_boss_fire_burst_d[];
extern s16 escaping_boat_m4_boss_fire_end[];
extern s16 escaping_boat_m4_boss_idle_wait[];
extern s16 escaping_boat_m4_boss_effect_burst_start[];
extern s16 escaping_boat_m4_boss_effect_burst[];
extern s16 escaping_boat_m4_boss_effect_burst_repeat[];
extern u16 D_8011A2C6;
extern s16 *escaping_boat_m4_boss_type_data[];
extern s16 *escaping_boat_m4_boss_script_start;
extern ScriptCallEntry D_8011A370[];
extern s16 muzzle_offset_x_table[];
extern u16 muzzle_offset_y_table;
extern s16 muzzle_offset_z_table[];
extern u16 effect_offset_table;
extern u16 D_8011A3EA;
extern u16 D_8011A3EC[];
extern StateEntry D_8011A408[];
extern ObjModelSlots rocket_boat_asset_slots;
extern s16 rocket_boat_anim_idle[];
extern s16 rocket_boat_anim_start[];
extern s16 rocket_boat_anim_hold[];
extern s16 rocket_boat_anim_return[];
extern s16 *rocket_boat_data[];
extern s16 rocket_boat_idle[];
extern s16 rocket_boat_activate[];
extern s16 rocket_boat_sweep[];
extern s16 rocket_boat_followup[];
extern s16 rocket_boat_patrol_a_pause[];
extern s16 rocket_boat_patrol_a_pause_b[];
extern s16 rocket_boat_patrol_a_hold_setup[];
extern s16 rocket_boat_patrol_a_hold[];
extern s16 rocket_boat_patrol_b_decide[];
extern s16 rocket_boat_patrol_b_pause[];
extern s16 rocket_boat_patrol_b_pause_b[];
extern s16 rocket_boat_patrol_b_hold_setup[];
extern s16 rocket_boat_patrol_b_hold[];
extern s16 rocket_boat_patrol_b_turn[];
extern s16 rocket_boat_patrol_c_decide[];
extern s16 rocket_boat_patrol_c_pause[];
extern s16 rocket_boat_patrol_c_pause_b[];
extern s16 rocket_boat_patrol_c_hold_setup[];
extern s16 rocket_boat_patrol_c_hold[];
extern s16 rocket_boat_patrol_c_turn[];
extern s16 rocket_boat_patrol_d_decide[];
extern s16 rocket_boat_patrol_d_pause[];
extern s16 rocket_boat_patrol_d_pause_b[];
extern s16 rocket_boat_patrol_d_hold_setup[];
extern s16 rocket_boat_patrol_d_hold[];
extern s16 rocket_boat_patrol_d_turn[];
extern s16 rocket_boat_choose_drift[];
extern s16 rocket_boat_patrol_e_pause[];
extern s16 rocket_boat_patrol_e_pause_b[];
extern s16 rocket_boat_patrol_e_hold_setup[];
extern s16 rocket_boat_patrol_e_hold[];
extern s16 rocket_boat_drift_start[];
extern s16 rocket_boat_drift_loop[];
extern s16 rocket_boat_drift_cooling[];
extern u16 script_mode0_reg0;
extern s16 rocket_boat_resume[];
extern s16 rocket_boat_shell_start[];
extern s16 rocket_boat_shell_loop[];
extern s16 rocket_boat_shell_cooling[];
extern s16 rocket_boat_fire_start[];
extern s16 rocket_boat_fire_loop[];
extern s16 rocket_boat_fire_cooling[];
extern u16 script_mode0_reg2;
extern s16 rocket_boat_idle_alt[];
extern s16 rocket_boat_activate_alt[];
extern s16 rocket_boat_sweep_alt[];
extern s16 rocket_boat_followup_alt[];
extern s16 rocket_boat_patrol_a_pause_alt[];
extern s16 rocket_boat_patrol_a_pause_alt_b[];
extern s16 rocket_boat_patrol_a_hold_setup_alt[];
extern s16 rocket_boat_patrol_a_hold_alt[];
extern s16 rocket_boat_patrol_b_decide_alt[];
extern s16 rocket_boat_patrol_b_pause_alt[];
extern s16 rocket_boat_patrol_b_pause_alt_b[];
extern s16 rocket_boat_patrol_b_hold_setup_alt[];
extern s16 rocket_boat_patrol_b_hold_alt[];
extern s16 rocket_boat_patrol_b_turn_alt[];
extern s16 rocket_boat_patrol_c_decide_alt[];
extern s16 rocket_boat_patrol_c_pause_alt[];
extern s16 rocket_boat_patrol_c_pause_alt_b[];
extern s16 rocket_boat_patrol_c_hold_setup_alt[];
extern s16 rocket_boat_patrol_c_hold_alt[];
extern s16 rocket_boat_patrol_c_turn_alt[];
extern s16 rocket_boat_patrol_d_decide_alt[];
extern s16 rocket_boat_patrol_d_pause_alt[];
extern s16 rocket_boat_patrol_d_pause_alt_b[];
extern s16 rocket_boat_patrol_d_hold_setup_alt[];
extern s16 rocket_boat_patrol_d_hold_alt[];
extern s16 rocket_boat_patrol_d_turn_alt[];
extern s16 rocket_boat_choose_drift_alt[];
extern s16 rocket_boat_patrol_e_pause_alt[];
extern s16 rocket_boat_patrol_e_pause_alt_b[];
extern s16 rocket_boat_patrol_e_hold_setup_alt[];
extern s16 rocket_boat_patrol_e_hold_alt[];
extern s16 rocket_boat_drift_start_alt[];
extern s16 rocket_boat_drift_loop_alt[];
extern s16 rocket_boat_drift_cooling_alt[];
extern u16 script_mode1_reg0;
extern s16 rocket_boat_resume_alt[];
extern s16 rocket_boat_shell_start_alt[];
extern s16 rocket_boat_shell_loop_alt[];
extern s16 rocket_boat_shell_cooling_alt[];
extern s16 rocket_boat_fire_start_alt[];
extern s16 rocket_boat_fire_loop_alt[];
extern s16 rocket_boat_fire_cooling_alt[];
extern u16 script_mode1_ch2;
extern s16 *rocket_boat_script_data[82];
extern s16 *rocket_boat_side_anim_table[];
extern ScriptCallEntry rocket_boat_side_call_table[8];
extern StateEntry rocket_boat_side_state_table[5];
extern RocketBoatRocketParams rocket_boat_rocket_params[];
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
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_8011F874[];
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
extern s32 cam_effect_flag;
extern s32 D_8011FEB8;
extern u32 D_8011FEBC[];
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
extern u32 D_801209F8[];
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
extern u32 D_80121018;
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
extern s32 effect_spawn_phase;
extern s32 sound_ramp_level;
extern s32 sound_interval_timer;
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
extern u32 D_80122534;
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
extern u32 D_801225B8;
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

s32 area = 9;

ScanItem area_scan_items[9] = {
    {&flip_scan_entry, str_enemy_flip_data},
    {&jetski_scan_entry, str_enemy_mjet_data},
    {&D_80119568, str_enemy_lan2_data},
    {&fighter_jet_sea2_scan_entry, str_enemy_sea2_data},
    {&sea_mine_scan_entry, str_enemy_kira_data},
    {&enemy_msgs_entry, str_enemy_msgs_data},
    {&D_80119CC8, str_enemy_ctl4_data},
    {&escaping_boat_boss_scan_entry, str_enemy_bos4_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry D_80118E1C = {str_s04_stage, str_mrn_cnf_bcf, str_mrn_apdea3, str_s04_joy_bin, str_s04_dat_fac, str_s04_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, area_scan_items};

AreaEntry D_80118E44 = {str_s04_miss, str_m21_cnf_bcf, NULL, str_m21_joy_bin, str_m04_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

u32 D_80118E6C[12] = {
    0xFFFFFFFF, 0x00000000, (u32)str_s04_boss, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x10001000, 0x00001000, 0x00000000, (u32)D_80118E6C,
};

AreaEntry *area_entry_table[3] = {
    &D_80118E44, &D_80118E1C, NULL,
};

#include "../stage/data/debug_name_buf.c"

s32 laser_barrier_boat_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_80118F74[3] = {
    {(s32)file_flip_ch0_clt, 0, 0},
    {(s32)file_flip_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80118F8C[2] = {
    {(s32)file_flip_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_80118F9C[2] = {
    {(s32)file_flip_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_80118FAC[2] = {
    {0x10, 0x13, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlock flip_model_block = {(s32)D_80118F74, (s32)D_80118F9C, (s32)D_80118F8C, 0, (s32)D_80118FAC, 0, 0, 0, 0};

u8 *D_80118FE0[2] = {
    file_flip_ch0_cb4, NULL,
};

ScanEntry flip_scan_entry = {{0, (s32)laser_barrier_boat_spawn_placed}, laser_barrier_boat_asset, (s32)&flip_model_block, (s32)D_80118FE0, 0};

u32 D_80119000[3] = {
    0x10000000, 0x051E0001, 0x051E0002,
};

struct LaserBarrierBoatAnims {
    s16 script[4];
    s16 *table[1];
} laser_barrier_boat_anims = {
    /* script */ {
        STEP(1, 0),
        GOTO(LASER_BARRIER_BOAT_SCRIPT),
    },
    /* table */ {
        laser_barrier_boat_anims.script,
    },
};

struct LaserBarrierBoatScripts {
    s16 select[6];
    s16 fly[8];
    s16 mine[4];
    s16 mine_idle[4];
    s16 fly_wait[6];
    s16 recheck[4];
    s16 *table[6];
    s16 *D_80119070;
} laser_barrier_boat_scripts = {
    /* select */ {
        LASER_BARRIER_BOAT_JUMP_IF_HEIGHT, 3000, LASER_BARRIER_BOAT_MINE,
        JUMP(LASER_BARRIER_BOAT_FLY),
    },
    /* fly */ {
        LASER_BARRIER_BOAT_READ_SPEED, 24,
        LASER_BARRIER_BOAT_READ_NEXT_STATE, LASER_BARRIER_BOAT_STATE_FLY_PAIR,
        SET_COUNTER(10),
        JUMP(LASER_BARRIER_BOAT_FLY_WAIT),
    },
    /* mine */ {
        LASER_BARRIER_BOAT_READ_SPEED, 24,
        LASER_BARRIER_BOAT_READ_NEXT_STATE, LASER_BARRIER_BOAT_STATE_MINE_PAIR,
    },
    /* mine_idle */ {
        WAIT(1),
        JUMP(LASER_BARRIER_BOAT_MINE_IDLE),
    },
    /* fly_wait */ {
        -1, 1, 4, 4, -3, 5,
    },
    /* recheck */ {
        WAIT(1),
        JUMP(LASER_BARRIER_BOAT_SELECT),
    },
    /* table */ {
        laser_barrier_boat_scripts.select, laser_barrier_boat_scripts.fly, laser_barrier_boat_scripts.mine, laser_barrier_boat_scripts.mine_idle, laser_barrier_boat_scripts.fly_wait, laser_barrier_boat_scripts.recheck,
    },
    /* D_80119070 */ laser_barrier_boat_scripts.select,
};

ScriptCallEntry D_80119074[5] = {
    {NULL, 0}, {script_read_speed, 0}, {obj_read_next_state, 0}, {obj_read_unk_242, 0},
    {script_jump_if_height, 0},
};

StateEntry D_8011909C[2] = {
    {(u32)fly_pair_update, LASER_BARRIER_BOAT_SCRIPT, 0},
    {(u32)moving_pyramid_mine_phase0, LASER_BARRIER_BOAT_SCRIPT, 0},
};

s32 jetski_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_801190B8[3] = {
    {(s32)file_mjet_ch0_clt, 0, 0},
    {(s32)file_mjet_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_801190D0[2] = {
    {(s32)file_mjet_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_801190E0[2] = {
    {(s32)file_mjet_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRange D_801190F0[2] = {
    {0, 0x7F, 0x1666, 0}, {-1, 0, 0, 0},
};

ModelBlock D_80119100 = {(s32)D_801190B8, (s32)D_801190D0, (s32)D_801190E0, 0, 0, 0, (s32)D_801190F0, 0, 0};

u8 *D_80119124[2] = {
    file_mjet_ch0_cb4, NULL,
};

ScanEntry jetski_scan_entry = {{0, (s32)jetski_spawn}, jetski_asset, (s32)&D_80119100, (s32)D_80119124, 0};

s16 jetski_anim_ride[6] = {
    STEP(1, 1),
    STEP(1, 2),
    GOTO(JETSKI_ANIM_RIDE),
};

s16 jetski_anim_bank_in_a[4] = {
    STEP(12, 9),
    STEP(12, 10),
};

s16 jetski_anim_bank_hold_a[4] = {
    STEP(12, 11),
    GOTO(JETSKI_ANIM_BANK_HOLD_A),
};

s16 jetski_anim_bank_out_a[6] = {
    STEP(12, 10),
    STEP(12, 9),
    GOTO(JETSKI_ANIM_RIDE),
};

s16 jetski_anim_bank_in_b[4] = {
    STEP(12, 13),
    STEP(12, 14),
};

s16 jetski_anim_bank_hold_b[4] = {
    STEP(12, 15),
    GOTO(JETSKI_ANIM_BANK_HOLD_B),
};

s16 jetski_anim_bank_out_b[6] = {
    STEP(12, 14),
    STEP(12, 13),
    GOTO(JETSKI_ANIM_RIDE),
};

s16 jetski_anim_aim_raise[12] = {
    STEP(3, 49),
    STEP(3, 50),
    STEP(3, 51),
    STEP(3, 52),
    STEP(3, 53),
    STEP(3, 54),
};

s16 jetski_anim_aim_hold[4] = {
    STEP(3, 55),
    GOTO(JETSKI_ANIM_AIM_HOLD),
};

s16 jetski_anim_aim_lower[8] = {
    STEP(3, 51),
    STEP(3, 50),
    STEP(3, 49),
    GOTO(JETSKI_ANIM_RIDE),
};

s16 jetski_anim_fire[14] = {
    STEP(3, 57),
    STEP(3, 58),
    STEP(3, 59),
    STEP(3, 60),
    STEP(3, 61),
    STEP(3, 62),
    GOTO(JETSKI_ANIM_AIM_HOLD),
};

s16 D_801191D4[22] = {
    STEP(3, 97),
    STEP(3, 98),
    STEP(3, 99),
    STEP(3, 100),
    STEP(3, 101),
    STEP(3, 102),
    STEP(3, 103),
    STEP(3, 104),
    STEP(3, 105),
    STEP(3, 106),
    STEP(3, 107),
};

s16 D_80119200[4] = {
    3, 0x6C, -1, 12,
};

s16 *jetski_data[11] = {
    jetski_anim_ride, jetski_anim_bank_in_a, jetski_anim_bank_hold_a, jetski_anim_bank_out_a, jetski_anim_bank_in_b, jetski_anim_bank_hold_b,
    jetski_anim_bank_out_b, jetski_anim_aim_raise, jetski_anim_aim_hold, jetski_anim_aim_lower, jetski_anim_fire,
};

s16 *jetski_script_table[2] = {
    D_801191D4, D_80119200,
};

struct JetskiScripts {
    s16 wait_approach[6];
    s16 aim[8];
    s16 fire_start[12];
    s16 fire_shot[2];
    s16 fire_loop[12];
    s16 turn_back[2];
    s16 idle_start[8];
    s16 idle_wait[10];
    s16 halt[4];
    s16 wait_side_slide[6];
    s16 side_aim[8];
    s16 side_fire_start[12];
    s16 side_fire_shot[2];
    s16 side_fire_loop[12];
    s16 side_turn_back[2];
    s16 side_idle_start[8];
    s16 side_idle_wait[10];
    s16 side_exit_wait[6];
    s16 approach_aim[8];
    s16 approach_fire_start[12];
    s16 approach_fire_shot[2];
    s16 approach_fire_loop[12];
    s16 approach_turn_back[2];
    s16 approach_idle_start[8];
    s16 approach_idle_wait[10];
    s16 approach_halt[4];
    s16 *table[26];
    s16 *D_8011941C[2];
} jetski_scripts = {
    /* wait_approach */ {
        WAIT(1),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_WAIT_APPROACH,
    },
    /* aim */ {
        WAIT(16),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_HALT,
        NEXT_STATE(JETSKI_STATE_AIM),
    },
    /* fire_start */ {
        WAIT(1),
        JUMP_UNLESS_STATE(JETSKI_STATE_TRACK, JETSKI_FIRE_START),
        WAIT(32),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_TURN_BACK,
        SET_COUNTER(2),
    },
    /* fire_shot */ {
        NEXT_STATE(JETSKI_STATE_FIRE),
    },
    /* fire_loop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(JETSKI_STATE_TRACK, JETSKI_FIRE_LOOP),
        WAIT(32),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_TURN_BACK,
        LOOP(JETSKI_FIRE_SHOT),
    },
    /* turn_back */ {
        NEXT_STATE(JETSKI_STATE_TURN_BACK),
    },
    /* idle_start */ {
        WAIT(1),
        JUMP_UNLESS_STATE(JETSKI_STATE_IDLE, JETSKI_IDLE_START),
        SET_COUNTER_RANDOM(64, 128),
    },
    /* idle_wait */ {
        WAIT(1),
        LOOP(JETSKI_IDLE_WAIT),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_HALT,
        JUMP(JETSKI_AIM),
    },
    /* halt */ {
        WAIT(1),
        JUMP(JETSKI_HALT),
    },
    /* wait_side_slide */ {
        WAIT(1),
        JETSKI_JUMP_IF_KEY, -6, JETSKI_WAIT_SIDE_SLIDE,
    },
    /* side_aim */ {
        WAIT(16),
        JETSKI_JUMP_IF_KEY, -6, JETSKI_SIDE_EXIT_WAIT,
        NEXT_STATE(JETSKI_STATE_AIM),
    },
    /* side_fire_start */ {
        WAIT(1),
        JUMP_UNLESS_STATE(JETSKI_STATE_TRACK, JETSKI_SIDE_FIRE_START),
        WAIT(32),
        JETSKI_JUMP_IF_KEY, -6, JETSKI_SIDE_TURN_BACK,
        SET_COUNTER(2),
    },
    /* side_fire_shot */ {
        NEXT_STATE(JETSKI_STATE_FIRE),
    },
    /* side_fire_loop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(JETSKI_STATE_TRACK, JETSKI_SIDE_FIRE_LOOP),
        WAIT(32),
        JETSKI_JUMP_IF_KEY, -6, JETSKI_SIDE_TURN_BACK,
        LOOP(JETSKI_SIDE_FIRE_SHOT),
    },
    /* side_turn_back */ {
        NEXT_STATE(JETSKI_STATE_TURN_BACK),
    },
    /* side_idle_start */ {
        WAIT(1),
        JUMP_UNLESS_STATE(JETSKI_STATE_IDLE, JETSKI_SIDE_IDLE_START),
        SET_COUNTER_RANDOM(64, 128),
    },
    /* side_idle_wait */ {
        WAIT(1),
        LOOP(JETSKI_SIDE_IDLE_WAIT),
        JETSKI_JUMP_IF_KEY, -6, JETSKI_SIDE_EXIT_WAIT,
        JUMP(JETSKI_SIDE_AIM),
    },
    /* side_exit_wait */ {
        WAIT(1),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_SIDE_EXIT_WAIT,
    },
    /* approach_aim */ {
        WAIT(16),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_APPROACH_HALT,
        NEXT_STATE(JETSKI_STATE_AIM),
    },
    /* approach_fire_start */ {
        WAIT(1),
        JUMP_UNLESS_STATE(JETSKI_STATE_TRACK, JETSKI_APPROACH_FIRE_START),
        WAIT(32),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_APPROACH_TURN_BACK,
        SET_COUNTER(2),
    },
    /* approach_fire_shot */ {
        NEXT_STATE(JETSKI_STATE_FIRE),
    },
    /* approach_fire_loop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(JETSKI_STATE_TRACK, JETSKI_APPROACH_FIRE_LOOP),
        WAIT(32),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_APPROACH_TURN_BACK,
        LOOP(JETSKI_APPROACH_FIRE_SHOT),
    },
    /* approach_turn_back */ {
        NEXT_STATE(JETSKI_STATE_TURN_BACK),
    },
    /* approach_idle_start */ {
        WAIT(1),
        JUMP_UNLESS_STATE(JETSKI_STATE_IDLE, JETSKI_APPROACH_IDLE_START),
        SET_COUNTER_RANDOM(64, 128),
    },
    /* approach_idle_wait */ {
        WAIT(1),
        LOOP(JETSKI_APPROACH_IDLE_WAIT),
        JETSKI_JUMP_IF_KEY, -2, JETSKI_APPROACH_HALT,
        JUMP(JETSKI_APPROACH_AIM),
    },
    /* approach_halt */ {
        WAIT(1),
        JUMP(JETSKI_APPROACH_HALT),
    },
    /* table */ {
        jetski_scripts.wait_approach, jetski_scripts.aim, jetski_scripts.fire_start, jetski_scripts.fire_shot, jetski_scripts.fire_loop, jetski_scripts.turn_back,
        jetski_scripts.idle_start, jetski_scripts.idle_wait, jetski_scripts.halt, jetski_scripts.wait_side_slide, jetski_scripts.side_aim, jetski_scripts.side_fire_start,
        jetski_scripts.side_fire_shot, jetski_scripts.side_fire_loop, jetski_scripts.side_turn_back, jetski_scripts.side_idle_start, jetski_scripts.side_idle_wait, jetski_scripts.side_exit_wait,
        jetski_scripts.approach_aim, jetski_scripts.approach_fire_start, jetski_scripts.approach_fire_shot, jetski_scripts.approach_fire_loop, jetski_scripts.approach_turn_back, jetski_scripts.approach_idle_start,
        jetski_scripts.approach_idle_wait, jetski_scripts.approach_halt,
    },
    /* D_8011941C */ {
        jetski_scripts.wait_approach, jetski_scripts.wait_side_slide,
    },
};

ScriptCallEntry jetski_call_table[2] = {
    {NULL, 0}, {script_jump_if_key, 0},
};

StateEntry D_80119434[15] = {
    {0, JETSKI_ANIM_RIDE, 1},
    {0, JETSKI_ANIM_BANK_IN_A, 0},
    {0, JETSKI_ANIM_BANK_HOLD_A, 0},
    {0, JETSKI_ANIM_BANK_OUT_A, 0},
    {0, JETSKI_ANIM_BANK_IN_B, 0},
    {0, JETSKI_ANIM_BANK_HOLD_B, 0},
    {0, JETSKI_ANIM_BANK_OUT_B, 0},
    {(u32)obj_init_aim_at_camera, JETSKI_ANIM_AIM_RAISE, 1},
    {(u32)obj_face_point_xz, JETSKI_ANIM_AIM_HOLD, 0},
    {(u32)obj_turn_to_rest, JETSKI_ANIM_AIM_HOLD, 0},
    {0, JETSKI_ANIM_AIM_LOWER, 0},
    {(u32)obj_aim_and_fire, JETSKI_ANIM_FIRE, 0},
    {0, -1, 0},
    {0, JETSKI_ANIM_RIDE, 0},
    {0, JETSKI_ANIM_RIDE, 0},
};

GunSetup enemy_gun_setup = {0x8000, 0x20000, 0x800, 0xA, 2, 8, 0x40, 0x20, 0x10, 4, 4, 0xA, 8, 0xC, 0x80};

s32 heavy_mobile_suit_asset[3] = {
    -1, -1, -1,
};

#include "../stage/data/d_801194DC.c"

#include "../stage/data/d_801194FC.c"

#include "../stage/data/d_80119514.c"

#include "../stage/data/d_80119524.c"

#include "../stage/data/heavy_mobile_suit_model_block.c"

#include "../stage/data/d_80119560.c"

ScanEntry D_80119568 = {{0, (s32)heavy_mobile_suit_spawn}, heavy_mobile_suit_asset, (s32)&heavy_mobile_suit_model_block, (s32)d_80119560, 0};

#include "../stage/data/d_80119580.c"

#include "../stage/data/heavy_mobile_suit_anims.c"

struct HeavyMobileSuitScripts {
    s16 cycle[2];
    s16 patrol_start[4];
    s16 scan[8];
    s16 idle[8];
    s16 idle_watch[10];
    s16 spotted[8];
    s16 spotted_wait[6];
    s16 patrol[8];
    s16 patrol_wait[6];
    s16 search[8];
    s16 search_watch[12];
    s16 search_end[8];
    s16 pursue[8];
    s16 pursue_wait[6];
    s16 fire_burst[14];
    s16 fire_wait[6];
    s16 cooldown[8];
    s16 cooling[8];
    s16 disengage[10];
    s16 disengage_wait[6];
    s16 search_done[6];
    s16 restart[2];
    s16 *table[22];
    s16 *D_80119860;
} heavy_mobile_suit_scripts = {
    /* cycle */ {
        JUMP(HEAVY_MOBILE_SUIT_SCAN),
    },
    /* patrol_start */ {
        HEAVY_MOBILE_SUIT_SET_FLY_MODE, 1,
        JUMP(HEAVY_MOBILE_SUIT_PATROL),
    },
    /* scan */ {
        HEAVY_MOBILE_SUIT_SET_FLY_MODE, 0,
        HEAVY_MOBILE_SUIT_JUMP_IF_WITHIN, 1000, HEAVY_MOBILE_SUIT_SPOTTED,
        JUMP(HEAVY_MOBILE_SUIT_PATROL),
    },
    /* idle */ {
        HEAVY_MOBILE_SUIT_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_READ_U16, 0,
        SET_COUNTER(128),
        JUMP(HEAVY_MOBILE_SUIT_IDLE_WATCH),
    },
    /* idle_watch */ {
        WAIT(1),
        HEAVY_MOBILE_SUIT_JUMP_IF_WITHIN, 1000, HEAVY_MOBILE_SUIT_SPOTTED,
        LOOP(HEAVY_MOBILE_SUIT_IDLE_WATCH),
        JUMP(HEAVY_MOBILE_SUIT_RESTART),
    },
    /* spotted */ {
        HEAVY_MOBILE_SUIT_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_READ_U16, 3,
        SET_COUNTER(40),
        JUMP(HEAVY_MOBILE_SUIT_SPOTTED_WAIT),
    },
    /* spotted_wait */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_SPOTTED_WAIT),
        JUMP(HEAVY_MOBILE_SUIT_FIRE_BURST),
    },
    /* patrol */ {
        HEAVY_MOBILE_SUIT_SET_SOUND, 60,
        HEAVY_MOBILE_SUIT_READ_U16, 1,
        SET_COUNTER(40),
        JUMP(HEAVY_MOBILE_SUIT_PATROL_WAIT),
    },
    /* patrol_wait */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PATROL_WAIT),
        JUMP(HEAVY_MOBILE_SUIT_SEARCH),
    },
    /* search */ {
        HEAVY_MOBILE_SUIT_SET_SOUND, 60,
        HEAVY_MOBILE_SUIT_READ_U16, 4,
        SET_COUNTER(768),
        JUMP(HEAVY_MOBILE_SUIT_SEARCH_WATCH),
    },
    /* search_watch */ {
        WAIT(1),
        HEAVY_MOBILE_SUIT_STEP, HEAVY_MOBILE_SUIT_SEARCH_WATCH,
        HEAVY_MOBILE_SUIT_JUMP_IF_WITHIN, 1000, HEAVY_MOBILE_SUIT_PURSUE,
        LOOP(HEAVY_MOBILE_SUIT_SEARCH_WATCH),
        JUMP(HEAVY_MOBILE_SUIT_SEARCH_END),
    },
    /* search_end */ {
        HEAVY_MOBILE_SUIT_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_READ_U16, 5,
        SET_COUNTER(40),
        JUMP(HEAVY_MOBILE_SUIT_SEARCH_DONE),
    },
    /* pursue */ {
        HEAVY_MOBILE_SUIT_SET_SOUND, 0,
        HEAVY_MOBILE_SUIT_READ_U16, 6,
        SET_COUNTER(56),
        JUMP(HEAVY_MOBILE_SUIT_PURSUE_WAIT),
    },
    /* pursue_wait */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_PURSUE_WAIT),
        JUMP(HEAVY_MOBILE_SUIT_FIRE_BURST),
    },
    /* fire_burst */ {
        HEAVY_MOBILE_SUIT_SET_SOUND, 12,
        HEAVY_MOBILE_SUIT_READ_U16, 10,
        HEAVY_MOBILE_SUIT_PLAY_SOUND_HERE,
        SET_COUNTER(96),
        HEAVY_MOBILE_SUIT_SET_258, 72,
        HEAVY_MOBILE_SUIT_SET_SELECTOR, 0,
        JUMP(HEAVY_MOBILE_SUIT_FIRE_WAIT),
    },
    /* fire_wait */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_FIRE_WAIT),
        JUMP(HEAVY_MOBILE_SUIT_COOLDOWN),
    },
    /* cooldown */ {
        HEAVY_MOBILE_SUIT_SET_SOUND, 12,
        HEAVY_MOBILE_SUIT_READ_U16, 11,
        SET_COUNTER(5),
        JUMP(HEAVY_MOBILE_SUIT_COOLING),
    },
    /* cooling */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_COOLING),
        HEAVY_MOBILE_SUIT_STEP, HEAVY_MOBILE_SUIT_DISENGAGE,
        JUMP(HEAVY_MOBILE_SUIT_FIRE_BURST),
    },
    /* disengage */ {
        HEAVY_MOBILE_SUIT_READ_U16, 12,
        HEAVY_MOBILE_SUIT_SET_FLY_MODE, 1,
        HEAVY_MOBILE_SUIT_SET_SOUND, 12,
        SET_COUNTER(32),
        JUMP(HEAVY_MOBILE_SUIT_DISENGAGE_WAIT),
    },
    /* disengage_wait */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_DISENGAGE_WAIT),
        JUMP(HEAVY_MOBILE_SUIT_PATROL_START),
    },
    /* search_done */ {
        WAIT(1),
        LOOP(HEAVY_MOBILE_SUIT_SEARCH_DONE),
        JUMP(HEAVY_MOBILE_SUIT_RESTART),
    },
    /* restart */ {
        JUMP(HEAVY_MOBILE_SUIT_CYCLE),
    },
    /* table */ {
        heavy_mobile_suit_scripts.cycle, heavy_mobile_suit_scripts.patrol_start, heavy_mobile_suit_scripts.scan, heavy_mobile_suit_scripts.idle, heavy_mobile_suit_scripts.idle_watch, heavy_mobile_suit_scripts.spotted,
        heavy_mobile_suit_scripts.spotted_wait, heavy_mobile_suit_scripts.patrol, heavy_mobile_suit_scripts.patrol_wait, heavy_mobile_suit_scripts.search, heavy_mobile_suit_scripts.search_watch, heavy_mobile_suit_scripts.search_end,
        heavy_mobile_suit_scripts.pursue, heavy_mobile_suit_scripts.pursue_wait, heavy_mobile_suit_scripts.fire_burst, heavy_mobile_suit_scripts.fire_wait, heavy_mobile_suit_scripts.cooldown, heavy_mobile_suit_scripts.cooling,
        heavy_mobile_suit_scripts.disengage, heavy_mobile_suit_scripts.disengage_wait, heavy_mobile_suit_scripts.search_done, heavy_mobile_suit_scripts.restart,
    },
    /* D_80119860 */ heavy_mobile_suit_scripts.cycle,
};

ScriptCallEntry heavy_mobile_suit_call_table[11] = {
    {NULL, 0},
    {obj_script_set_sound, 0},
    {obj_script_read_u16, 0},
    {obj_script_set_fly_mode, 0},
    {obj_script_jump_if_within, 0},
    {obj_script_jump_if_beyond, 0},
    {obj_script_set_258, 0},
    {obj_script_set_selector, 0},
    {script_op_jump_table_if_player_far, 0},
    {script_step, 0},
    {obj_play_sound_here, 0},
};

StateEntry heavy_mobile_suit_state_table[13] = {
    {(u32)obj_fly_update, HEAVY_MOBILE_SUIT_SCRIPT, 0},
    {(u32)obj_fly_update, HEAVY_MOBILE_SUIT_ANIM_PATROL_ENTER, 0},
    {(u32)obj_fly_update, HEAVY_MOBILE_SUIT_ANIM_ALT_ENTER, 0},
    {(u32)obj_pursue_update, HEAVY_MOBILE_SUIT_ANIM_SPOTTED_ENTER, 0},
    {(u32)obj_fly_update, HEAVY_MOBILE_SUIT_ANIM_SEARCH_HOLD, 0},
    {(u32)obj_fly_update, HEAVY_MOBILE_SUIT_ANIM_SEARCH_END, 0},
    {(u32)obj_pursue_update, HEAVY_MOBILE_SUIT_ANIM_PURSUE_ENTER, 0},
    {(u32)obj_fly_update, HEAVY_MOBILE_SUIT_ANIM_ALT_HOLD, 0},
    {(u32)obj_fly_update, HEAVY_MOBILE_SUIT_ANIM_ALT_END, 0},
    {(u32)obj_pursue_update, HEAVY_MOBILE_SUIT_ANIM_PURSUE_ALT_ENTER, 0},
    {(u32)obj_pursue_update, HEAVY_MOBILE_SUIT_ANIM_FIRE_ENTER, 0},
    {(u32)obj_pursue_step, HEAVY_MOBILE_SUIT_ANIM_APPROACH_HOLD, 0},
    {(u32)obj_fly_update, HEAVY_MOBILE_SUIT_ANIM_DISENGAGE, 0},
};

s32 D_80119924[3] = {
    -1, -1, -1,
};

#include "../stage/data/fighter_jet_palette_refs.c"

#include "../stage/data/fighter_jet_texture_refs.c"

#include "../stage/data/fighter_jet_model_refs.c"

#include "../stage/data/fighter_jet_model_block.c"

#include "../stage/data/fighter_jet_file_list.c"

ScanEntry fighter_jet_sea2_scan_entry = {{0, (s32)fighter_jet_spawn}, D_80119924, (s32)&fighter_jet_model_block, (s32)fighter_jet_file_list, 0};

FxRecordParams fx_send_rec34_params_a = {0, 0xFF, 0x70, 0, 0x100, 0x55, {0x800000, 0x34000, 0x1000, 0x8000}};

#include "../stage/data/fx_send_rec34_params_b.c"

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
        JUMP_IF_STATE(FIGHTER_JET_STATE_SWEEP, FIGHTER_JET_SWEEP_END),
        FIGHTER_JET_JUMP_IF_PLAYER_NEAR, 12000, FIGHTER_JET_SPOTTED,
        JUMP(FIGHTER_JET_PATROL),
    },
    /* patrol */ {
        FIGHTER_JET_SET_TURN_MODE, 0,
        FIGHTER_JET_SPEED_APPROACH, 35,
        FIGHTER_JET_SET_NEXT_STATE, FIGHTER_JET_STATE_FLY,
        JUMP(FIGHTER_JET_COOLDOWN),
    },
    /* sweep_end */ {
        FIGHTER_JET_SET_TURN_MODE, 1,
        FIGHTER_JET_SPEED_APPROACH, 17,
        FIGHTER_JET_SET_NEXT_STATE, FIGHTER_JET_STATE_FLY,
        JUMP(FIGHTER_JET_COOLDOWN),
    },
    /* spotted */ {
        FIGHTER_JET_SET_TURN_MODE, 0,
        FIGHTER_JET_SPEED_APPROACH, 24,
        FIGHTER_JET_SET_NEXT_STATE, FIGHTER_JET_STATE_FIRE,
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

#include "../stage/data/sea_mine_asset.c"

ModelBlockRef sea_mine_palettes[3] = {
    {(s32)file_kira_ch0_clt, 0, 0},
    {(s32)file_kira_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef sea_mine_textures[2] = {
    {(s32)file_kira_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef sea_mine_models[2] = {
    {(s32)file_kira_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_80119B3C[4] = {
    {1, 2, 0x2000, 0}, {4, 5, 0x2000, 0}, {8, 10, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlock sea_mine_model_block = {(s32)sea_mine_palettes, (s32)sea_mine_models, (s32)sea_mine_textures, 0, 0, 0, (s32)D_80119B3C, 0, 0};

u8 *D_80119B80[2] = {
    file_kira_ch0_cb4, NULL,
};

ScanEntry sea_mine_scan_entry = {{0, (s32)sea_mine_spawn}, sea_mine_asset, (s32)&sea_mine_model_block, (s32)D_80119B80, 0};

#include "../stage/data/sea_mine_anim_frames.c"

#include "../stage/data/d_80116F10.c"

#include "../stage/data/sea_mine_anims.c"

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

#include "../stage/data/enemy_msgs_files.c"

#include "../stage/data/enemy_msgs_entry.c"

ModelBlockRef D_80119C58[2] = {
    {(s32)str_ctl4_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80119C68[2] = {
    {(s32)str_ctl4_tp0_xs3, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80119C78[2] = {
    {(s32)str_ctl4_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_80119C88[2] = {
    {0, 0, 0x80, 0}, {-1, 0, 0, 0},
};

ModelBlock D_80119C98 = {(s32)D_80119C58, (s32)D_80119C78, (s32)D_80119C68, 0, 0, (s32)D_80119C88, 0, 0, 0};

ModelSlotHead spark_model_index = {{-1, -1, -1}};

ScanEntry D_80119CC8 = {{(s32)stage_start, (s32)sound_driver_spawn}, (s32 *)&spark_model_index, (s32)&D_80119C98, 0, 0};

u8 span_table[196] = {
    0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x23,
    0x30, 0x75, 0x00, 0x00, 0x30, 0x75, 0xF0, 0x23, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xF0, 0x23, 0x08, 0x6B, 0x00, 0x00, 0x08, 0x6B, 0xF0, 0x23,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x0C, 0xF8, 0x11, 0x00, 0x00,
    0xF8, 0x11, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x17,
    0xF8, 0x11, 0x98, 0x05, 0xF8, 0x11, 0x90, 0x17, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xF0, 0x23, 0x50, 0x46, 0x00, 0x00, 0x50, 0x46, 0xF0, 0x23,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x23, 0xE0, 0x2E, 0x94, 0x11,
    0xE0, 0x2E, 0xF0, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5C, 0x12,
    0x40, 0x1F, 0x00, 0x00, 0x40, 0x1F, 0x5C, 0x12, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5C, 0x12, 0xF8, 0x2A, 0x00, 0x00, 0xF8, 0x2A, 0x78, 0x05,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x05, 0xF0, 0x55, 0x00, 0x00,
    0xF0, 0x55, 0x78, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x10,
    0x10, 0x0E, 0x00, 0x00, 0x10, 0x0E, 0x68, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x58, 0x1B, 0xB8, 0x24, 0x00, 0x00, 0xB8, 0x24, 0x58, 0x1B,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x1B, 0x30, 0x75, 0x00, 0x00,
    0x30, 0x75, 0x58, 0x1B,
};

s32 D_80119DA4[49] = {
    0x18, (s32)0xF8AD0000, (s32)0xFEBB0000, 1, (s32)0xFEBB0000, 0x6B08002,
    (s32)0xFEBB0000, 0x6B08003, (s32)0xFF810000, 0x7D00004, (s32)0xFEBB0000, 0xC350005,
    (s32)0xFEBB0000, 0xF230006, (s32)0xFFD44000, 0x11170007, (s32)0xFFD44000, 0x13C68008,
    (s32)0xFFD44000, 0x19258009, (s32)0xFF254000, 0x1A06800A, (s32)0xFF254000, 0x1C52000B,
    (s32)0xFF254000, 0x23A5000B, (s32)0xFF254000, 0x2AF8000B, (s32)0xFF254000, 0x324B000B,
    (s32)0xFF254000, 0x399E000B, (s32)0xFF254000, 0x40F1000B, (s32)0xFF254000, 0x4844000B,
    (s32)0xFF254000, 0x4F97000B, (s32)0xFF254000, 0x56EA000B, (s32)0xFF254000, 0x5E3D000B,
    (s32)0xFF254000, 0x6590000B, (s32)0xFF254000, 0x6CE3000B, (s32)0xFF254000, 0x7436000B,
    (s32)0xFF254000,
};

LightData stage_data_base = {1, {{0x2EE, -0x1C2, 0x1C2, 0, -0x2000}}};

s32 boss_active_flag = 0;

s32 boss_meter_flag = 0;

#include "../stage/data/d_80119E84.c"

s32 boss_retreat_flag = 0;

s32 rocket_boat_count = 0;

s32 escaping_boat_m4_boss_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef escaping_boat_boss_palettes[3] = {
    {(s32)file_bos4_ch0_clt, 0, 0},
    {(s32)file_bos4_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef escaping_boat_boss_models[2] = {
    {(s32)file_bos4_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRef escaping_boat_boss_textures[3] = {
    {(s32)file_bos4_tp0_xs3, 1, 0},
    {(s32)file_bos4_tp1_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRange D_80119EDC[7] = {
    {9, 12, 0x2000, 0}, {0x1B, 0x1B, 0x2000, 0}, {0x39, 0x3C, 0x2000, 0}, {0x42, 0x45, 0x2000, 0},
    {0x50, 0x58, 0x1000, 0}, {0x60, 0x64, 0x1000, 0}, {-1, 0, 0, 0},
};

ModelBlockRange D_80119F14[12] = {
    {0, 7, 0xCCC, 0}, {8, 15, 0x1000, 0}, {0x10, 0x13, 0xCCC, 0}, {0x14, 0x17, 0xCCC, 0},
    {0x18, 0x1B, 0xCCC, 0}, {0x20, 0x37, 0xCCC, 0}, {0x38, 0x3F, 0x1000, 0}, {0x40, 0x47, 0xCCC, 0},
    {0x48, 0x4F, 0xCCC, 0}, {0x50, 0x6F, 0xCCC, 0}, {0x70, 0x7F, 0xCCC, 0}, {-1, 0, 0, 0},
};

ModelBlock escaping_boat_boss_model_block = {(s32)escaping_boat_boss_palettes, (s32)escaping_boat_boss_models, (s32)escaping_boat_boss_textures, 0, (s32)D_80119EDC, 0, (s32)D_80119F14, 0, 0};

u8 *D_80119F98[2] = {
    file_bos4_ch0_cb4, NULL,
};

ScanEntry escaping_boat_boss_scan_entry = {{(s32)stage_spawn_slots_reset, (s32)escaping_boat_m4_boss_spawn}, escaping_boat_m4_boss_asset, (s32)&escaping_boat_boss_model_block, (s32)D_80119F98, 0};

struct EscapingBoatM4BossAnims {
    s16 idle[4];
    s16 fire_start[2];
    s16 fire_loop[4];
    s16 cooldown[6];
    s16 *table[4];
} escaping_boat_m4_boss_anims = {
    /* idle */ {
        STEP(1, 0),
        GOTO(ESCAPING_BOAT_M4_BOSS_ANIM_IDLE),
    },
    /* fire_start */ {
        STEP(4, 1),
    },
    /* fire_loop */ {
        STEP(4, 2),
        GOTO(ESCAPING_BOAT_M4_BOSS_ANIM_FIRE_LOOP),
    },
    /* cooldown */ {
        STEP(4, 1),
        STEP(4, 0),
        GOTO(ESCAPING_BOAT_M4_BOSS_ANIM_IDLE),
    },
    /* table */ {
        escaping_boat_m4_boss_anims.idle, escaping_boat_m4_boss_anims.fire_start, escaping_boat_m4_boss_anims.fire_loop, escaping_boat_m4_boss_anims.cooldown,
    },
};

s16 escaping_boat_m4_boss_dispatch[6] = {
    WAIT(1),
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_JUMP, ESCAPING_BOAT_M4_BOSS_PICK_TURN,
    JUMP(ESCAPING_BOAT_M4_BOSS_DISPATCH),
};

s16 escaping_boat_m4_boss_pick_turn[14] = {
    SET_COUNTER_RANDOM(64, 64),
    ESCAPING_BOAT_M4_BOSS_SEQ_BRANCH_ON_MATCH, 0, ESCAPING_BOAT_M4_BOSS_TURN_HOLD,
    ESCAPING_BOAT_M4_BOSS_SEQ_BRANCH_ON_MATCH, 1024, ESCAPING_BOAT_M4_BOSS_TURN_HOLD_B,
    ESCAPING_BOAT_M4_BOSS_SEQ_BRANCH_ON_MATCH, 2048, ESCAPING_BOAT_M4_BOSS_TURN_HOLD_C,
    JUMP(ESCAPING_BOAT_M4_BOSS_TURN_HOLD_D),
};

s16 escaping_boat_m4_boss_turn_hub[12] = {
    ESCAPING_BOAT_M4_BOSS_SEQ_BRANCH_ON_MATCH, 0, ESCAPING_BOAT_M4_BOSS_CHOOSE_ATTACK,
    ESCAPING_BOAT_M4_BOSS_SEQ_BRANCH_ON_MATCH, 1024, ESCAPING_BOAT_M4_BOSS_ATTACK_B,
    ESCAPING_BOAT_M4_BOSS_SEQ_BRANCH_ON_MATCH, 2048, ESCAPING_BOAT_M4_BOSS_ATTACK_C,
    JUMP(ESCAPING_BOAT_M4_BOSS_ATTACK_D),
};

s16 escaping_boat_m4_boss_choose_attack[10] = {
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 4,
    JUMP_RANDOM(3072, ESCAPING_BOAT_M4_BOSS_EFFECT_BURST_START),
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_attack_a_alt[12] = {
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_START),
    WAIT(32),
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 5,
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_attack_a_alt2[16] = {
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_START),
    WAIT(32),
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 6,
    JUMP_RANDOM(3072, ESCAPING_BOAT_M4_BOSS_EFFECT_BURST_START),
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_turn_start[4] = {
    SET_COUNTER_RANDOM(128, 128),
};

s16 escaping_boat_m4_boss_turn_hold[12] = {
    WAIT(1),
    LOOP(ESCAPING_BOAT_M4_BOSS_TURN_HOLD),
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_HOLD_A_ALT),
    ESCAPING_BOAT_M4_BOSS_READ_PARAM, 1024,
    JUMP(ESCAPING_BOAT_M4_BOSS_TURN_HUB),
};

s16 escaping_boat_m4_boss_turn_hold_a_alt[4] = {
    ESCAPING_BOAT_M4_BOSS_READ_PARAM, 3072,
    JUMP(ESCAPING_BOAT_M4_BOSS_TURN_HUB),
};

s16 escaping_boat_m4_boss_attack_b[8] = {
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 10,
    JUMP_RANDOM(2457, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_attack_b_alt[12] = {
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_START_B),
    WAIT(32),
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 11,
    JUMP_RANDOM(2457, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_attack_b_alt2[12] = {
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_START_B),
    WAIT(32),
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 12,
    JUMP_RANDOM(2457, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_turn_start_b[4] = {
    SET_COUNTER_RANDOM(128, 128),
};

s16 escaping_boat_m4_boss_turn_hold_b[12] = {
    WAIT(1),
    LOOP(ESCAPING_BOAT_M4_BOSS_TURN_HOLD_B),
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_HOLD_B_ALT),
    ESCAPING_BOAT_M4_BOSS_READ_PARAM, 2048,
    JUMP(ESCAPING_BOAT_M4_BOSS_TURN_HUB),
};

s16 escaping_boat_m4_boss_turn_hold_b_alt[4] = {
    ESCAPING_BOAT_M4_BOSS_READ_PARAM, 0,
    JUMP(ESCAPING_BOAT_M4_BOSS_TURN_HUB),
};

s16 escaping_boat_m4_boss_attack_c[8] = {
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 16,
    JUMP_RANDOM(1638, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_attack_c_alt[12] = {
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_START_C),
    WAIT(32),
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 17,
    JUMP_RANDOM(1638, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_attack_c_alt2[12] = {
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_START_C),
    WAIT(32),
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 18,
    JUMP_RANDOM(1638, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_turn_start_c[4] = {
    SET_COUNTER_RANDOM(128, 128),
};

s16 escaping_boat_m4_boss_turn_hold_c[12] = {
    WAIT(1),
    LOOP(ESCAPING_BOAT_M4_BOSS_TURN_HOLD_C),
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_HOLD_C_ALT),
    ESCAPING_BOAT_M4_BOSS_READ_PARAM, 3072,
    JUMP(ESCAPING_BOAT_M4_BOSS_TURN_HUB),
};

s16 escaping_boat_m4_boss_turn_hold_c_alt[4] = {
    ESCAPING_BOAT_M4_BOSS_READ_PARAM, 1024,
    JUMP(ESCAPING_BOAT_M4_BOSS_TURN_HUB),
};

s16 escaping_boat_m4_boss_attack_d[8] = {
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 22,
    JUMP_RANDOM(2457, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_attack_d_alt[12] = {
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_START_D),
    WAIT(32),
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 23,
    JUMP_RANDOM(2457, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_attack_d_alt2[12] = {
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_START_D),
    WAIT(32),
    ESCAPING_BOAT_M4_BOSS_CURSOR_READ_U16_GLOBALS, 24,
    JUMP_RANDOM(2457, ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY_START),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_turn_start_d[4] = {
    SET_COUNTER_RANDOM(128, 128),
};

s16 escaping_boat_m4_boss_turn_hold_d[12] = {
    WAIT(1),
    LOOP(ESCAPING_BOAT_M4_BOSS_TURN_HOLD_D),
    JUMP_RANDOM(2048, ESCAPING_BOAT_M4_BOSS_TURN_HOLD_D_ALT),
    ESCAPING_BOAT_M4_BOSS_READ_PARAM, 0,
    JUMP(ESCAPING_BOAT_M4_BOSS_TURN_HUB),
};

s16 escaping_boat_m4_boss_turn_hold_d_alt[4] = {
    ESCAPING_BOAT_M4_BOSS_READ_PARAM, 2048,
    JUMP(ESCAPING_BOAT_M4_BOSS_TURN_HUB),
};

s16 escaping_boat_m4_boss_rocket_volley_start[6] = {
    WAIT(32),
    SET_COUNTER_RANDOM(3, 3),
};

s16 escaping_boat_m4_boss_rocket_volley[6] = {
    ESCAPING_BOAT_M4_BOSS_ROCKET_BOAT_FIRE_AIMED,
    WAIT(16),
    LOOP(ESCAPING_BOAT_M4_BOSS_ROCKET_VOLLEY),
};

s16 escaping_boat_m4_boss_rocket_volley_repeat[3] = {
    -1, 0x20, -3,
};

u16 stream_last_u16 = 0x1B;

s16 escaping_boat_m4_boss_aim_start[4] = {
    WAIT(32),
    NEXT_STATE(ESCAPING_BOAT_M4_BOSS_STATE_AIM),
};

s16 escaping_boat_m4_boss_fire_pick[18] = {
    WAIT(1),
    JUMP_UNLESS_STATE(ESCAPING_BOAT_M4_BOSS_STATE_FIRE, ESCAPING_BOAT_M4_BOSS_FIRE_PICK),
    WAIT(16),
    ESCAPING_BOAT_M4_BOSS_SEQ_BRANCH_ON_MATCH, 0, ESCAPING_BOAT_M4_BOSS_FIRE_BURST_A,
    ESCAPING_BOAT_M4_BOSS_SEQ_BRANCH_ON_MATCH, 1024, ESCAPING_BOAT_M4_BOSS_FIRE_BURST_B,
    ESCAPING_BOAT_M4_BOSS_SEQ_BRANCH_ON_MATCH, 2048, ESCAPING_BOAT_M4_BOSS_FIRE_BURST_C,
    JUMP(ESCAPING_BOAT_M4_BOSS_FIRE_BURST_D),
};

s16 escaping_boat_m4_boss_fire_burst_a[12] = {
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 4,
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 5,
    WAIT(16),
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 2,
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 3,
    JUMP(ESCAPING_BOAT_M4_BOSS_FIRE_END),
};

s16 escaping_boat_m4_boss_fire_burst_b[12] = {
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 0,
    WAIT(16),
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 2,
    WAIT(16),
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 4,
    JUMP(ESCAPING_BOAT_M4_BOSS_FIRE_END),
};

s16 escaping_boat_m4_boss_fire_burst_c[12] = {
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 0,
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 1,
    WAIT(16),
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 2,
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 3,
    JUMP(ESCAPING_BOAT_M4_BOSS_FIRE_END),
};

s16 escaping_boat_m4_boss_fire_burst_d[10] = {
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 1,
    WAIT(16),
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 3,
    WAIT(16),
    ESCAPING_BOAT_M4_BOSS_MUZZLE_SHOT, 5,
};

s16 escaping_boat_m4_boss_fire_end[4] = {
    WAIT(16),
    NEXT_STATE(ESCAPING_BOAT_M4_BOSS_STATE_RECOVER),
};

s16 escaping_boat_m4_boss_idle_wait[10] = {
    WAIT(1),
    JUMP_UNLESS_STATE(ESCAPING_BOAT_M4_BOSS_STATE_IDLE, ESCAPING_BOAT_M4_BOSS_IDLE_WAIT),
    WAIT(32),
    JUMP(ESCAPING_BOAT_M4_BOSS_AIM_START),
};

s16 escaping_boat_m4_boss_effect_burst_start[6] = {
    WAIT(32),
    SET_COUNTER_RANDOM(2, 2),
};

s16 escaping_boat_m4_boss_effect_burst[14] = {
    ESCAPING_BOAT_M4_BOSS_SPAWN_EFFECT_OFFSET, 0,
    ESCAPING_BOAT_M4_BOSS_SPAWN_EFFECT_OFFSET, 1,
    WAIT(32),
    ESCAPING_BOAT_M4_BOSS_SPAWN_EFFECT_OFFSET, 2,
    ESCAPING_BOAT_M4_BOSS_SPAWN_EFFECT_OFFSET, 3,
    WAIT(32),
    LOOP(ESCAPING_BOAT_M4_BOSS_EFFECT_BURST),
};

s16 escaping_boat_m4_boss_effect_burst_repeat[3] = {
    -1, 0x20, -3,
};

u16 D_8011A2C6 = 0x26;

s16 *escaping_boat_m4_boss_type_data[41] = {
    escaping_boat_m4_boss_dispatch, escaping_boat_m4_boss_pick_turn, escaping_boat_m4_boss_turn_hub, escaping_boat_m4_boss_choose_attack, escaping_boat_m4_boss_attack_a_alt, escaping_boat_m4_boss_attack_a_alt2,
    escaping_boat_m4_boss_turn_start, escaping_boat_m4_boss_turn_hold, escaping_boat_m4_boss_turn_hold_a_alt, escaping_boat_m4_boss_attack_b, escaping_boat_m4_boss_attack_b_alt, escaping_boat_m4_boss_attack_b_alt2,
    escaping_boat_m4_boss_turn_start_b, escaping_boat_m4_boss_turn_hold_b, escaping_boat_m4_boss_turn_hold_b_alt, escaping_boat_m4_boss_attack_c, escaping_boat_m4_boss_attack_c_alt, escaping_boat_m4_boss_attack_c_alt2,
    escaping_boat_m4_boss_turn_start_c, escaping_boat_m4_boss_turn_hold_c, escaping_boat_m4_boss_turn_hold_c_alt, escaping_boat_m4_boss_attack_d, escaping_boat_m4_boss_attack_d_alt, escaping_boat_m4_boss_attack_d_alt2,
    escaping_boat_m4_boss_turn_start_d, escaping_boat_m4_boss_turn_hold_d, escaping_boat_m4_boss_turn_hold_d_alt, escaping_boat_m4_boss_rocket_volley_start, escaping_boat_m4_boss_rocket_volley, escaping_boat_m4_boss_rocket_volley_repeat,
    escaping_boat_m4_boss_aim_start, escaping_boat_m4_boss_fire_pick, escaping_boat_m4_boss_fire_burst_a, escaping_boat_m4_boss_fire_burst_b, escaping_boat_m4_boss_fire_burst_c, escaping_boat_m4_boss_fire_burst_d,
    escaping_boat_m4_boss_fire_end, escaping_boat_m4_boss_idle_wait, escaping_boat_m4_boss_effect_burst_start, escaping_boat_m4_boss_effect_burst, escaping_boat_m4_boss_effect_burst_repeat,
};

s16 *escaping_boat_m4_boss_script_start = escaping_boat_m4_boss_dispatch;

ScriptCallEntry D_8011A370[9] = {
    {NULL, 0}, {rocket_boat_fire_aimed, 0}, {obj_script_muzzle_shot, 0},
    {obj_spawn_effect_offset, 0}, {script_read_param, 0}, {seq_branch_on_match, 0},
    {cursor_read_u16_globals, 0}, {obj_cursor_read_jump, 0}, {cursor_read_u16, 0},
};

s16 muzzle_offset_x_table[1] = {
    -0x84,
};

u16 muzzle_offset_y_table = 0xFED8;

s16 muzzle_offset_z_table[22] = {
    0x3C9, -0x400, 0x84, -0x128, 0x3C9, 0x400, -0x8B, -0x141,
    0x2E7, -0x400, 0x8B, -0x141, 0x2E7, 0x400, -0x97, -0x147,
    0x204, -0x400, 0x97, -0x147, 0x204, 0x400,
};

u16 effect_offset_table = 0xFD94;

u16 D_8011A3EA = 0xFE99;

u16 D_8011A3EC[14] = {
    0xFEDE, 0x0000, 0x026C, 0xFE99, 0xFEDE, 0x0000, 0xFD81, 0xFEF1,
    0xFEDE, 0x0000, 0x027F, 0xFEF1, 0xFEDE, 0x0000,
};

StateEntry D_8011A408[5] = {
    {0, ESCAPING_BOAT_M4_BOSS_ANIM_IDLE, 0},
    {0, ESCAPING_BOAT_M4_BOSS_ANIM_FIRE_START, 0},
    {0, ESCAPING_BOAT_M4_BOSS_ANIM_FIRE_LOOP, 0},
    {0, ESCAPING_BOAT_M4_BOSS_ANIM_COOLDOWN, 0},
    {0, ESCAPING_BOAT_M4_BOSS_ANIM_IDLE, 0},
};

ObjModelSlots rocket_boat_asset_slots = {{-1, -1, -1}};

struct RocketBoatAnims {
    s16 idle[4];
    s16 start[2];
    s16 hold[4];
    s16 anim_return[6];
    s16 *table[4];
} rocket_boat_anims = {
    /* idle */ {
        STEP(1, 48),
        GOTO(ROCKET_BOAT_ANIM_IDLE),
    },
    /* start */ {
        STEP(4, 49),
    },
    /* hold */ {
        STEP(4, 50),
        GOTO(ROCKET_BOAT_ANIM_HOLD),
    },
    /* anim_return */ {
        STEP(4, 49),
        STEP(4, 48),
        GOTO(ROCKET_BOAT_ANIM_IDLE),
    },
    /* table */ {
        rocket_boat_anims.idle, rocket_boat_anims.start, rocket_boat_anims.hold, rocket_boat_anims.anim_return,
    },
};

s16 rocket_boat_idle[6] = {
    WAIT(1),
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_MISSION_FLAG, ROCKET_BOAT_ACTIVATE,
    JUMP(ROCKET_BOAT_IDLE),
};

s16 rocket_boat_activate[18] = {
    SET_COUNTER_RANDOM(64, 64),
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 3072, ROCKET_BOAT_PATROL_A_HOLD,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 3584, ROCKET_BOAT_PATROL_B_HOLD,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 0, ROCKET_BOAT_PATROL_C_HOLD,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 512, ROCKET_BOAT_PATROL_D_HOLD,
    JUMP(ROCKET_BOAT_PATROL_E_HOLD),
};

s16 rocket_boat_sweep[14] = {
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 3072, ROCKET_BOAT_FOLLOWUP,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 3584, ROCKET_BOAT_PATROL_B_DECIDE,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 0, ROCKET_BOAT_PATROL_C_DECIDE,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 512, ROCKET_BOAT_PATROL_D_DECIDE,
    JUMP(ROCKET_BOAT_CHOOSE_DRIFT),
};

s16 rocket_boat_followup[8] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 4,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_a_pause[12] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_A_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 5,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_a_pause_b[12] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_A_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 6,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_a_hold_setup[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_a_hold[8] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_A_HOLD),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 3584,
    JUMP(ROCKET_BOAT_SWEEP),
};

s16 rocket_boat_patrol_b_decide[10] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 9,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_b_pause[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_B_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 10,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_b_pause_b[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_B_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 11,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_b_hold_setup[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_b_hold[12] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_B_HOLD),
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_B_TURN),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 0,
    JUMP(ROCKET_BOAT_SWEEP),
};

s16 rocket_boat_patrol_b_turn[4] = {
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 3072,
    JUMP(ROCKET_BOAT_SWEEP),
};

s16 rocket_boat_patrol_c_decide[10] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 15,
    JUMP_RANDOM(2457, ROCKET_BOAT_FIRE_START),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_c_pause[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_C_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 16,
    JUMP_RANDOM(2457, ROCKET_BOAT_FIRE_START),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_c_pause_b[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_C_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 17,
    JUMP_RANDOM(2457, ROCKET_BOAT_FIRE_START),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_c_hold_setup[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_c_hold[12] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_C_HOLD),
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_C_TURN),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 512,
    JUMP(ROCKET_BOAT_SWEEP),
};

s16 rocket_boat_patrol_c_turn[4] = {
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 3584,
    JUMP(ROCKET_BOAT_SWEEP),
};

s16 rocket_boat_patrol_d_decide[10] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 21,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_d_pause[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_D_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 22,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_d_pause_b[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_D_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 23,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_d_hold_setup[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_d_hold[12] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_D_HOLD),
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_D_TURN),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 1024,
    JUMP(ROCKET_BOAT_SWEEP),
};

s16 rocket_boat_patrol_d_turn[4] = {
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 0,
    JUMP(ROCKET_BOAT_SWEEP),
};

s16 rocket_boat_choose_drift[8] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 27,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_e_pause[12] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_E_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 28,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_e_pause_b[12] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_E_HOLD_SETUP),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 29,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_patrol_e_hold_setup[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_e_hold[8] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_E_HOLD),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 512,
    JUMP(ROCKET_BOAT_SWEEP),
};

s16 rocket_boat_drift_start[6] = {
    WAIT(32),
    SET_COUNTER_RANDOM(3, 3),
};

s16 rocket_boat_drift_loop[6] = {
    ROCKET_BOAT_SPAWN_SIDE_FIRE_DRIFT,
    WAIT(16),
    LOOP(ROCKET_BOAT_DRIFT_LOOP),
};

s16 rocket_boat_drift_cooling[3] = {
    -1, 0x20, -3,
};

u16 script_mode0_reg0 = 0x1F;

s16 rocket_boat_resume[4] = {
    WAIT(32),
    NEXT_STATE(ROCKET_BOAT_SPAWN_SIDE_STATE_PATROL),
};

s16 rocket_boat_shell_start[10] = {
    WAIT(1),
    JUMP_UNLESS_STATE(ROCKET_BOAT_SPAWN_SIDE_STATE_ENGAGE, ROCKET_BOAT_SHELL_START),
    WAIT(16),
    SET_COUNTER_RANDOM(2, 2),
};

s16 rocket_boat_shell_loop[10] = {
    ROCKET_BOAT_SPAWN_SIDE_FIRE_NEAR,
    WAIT(32),
    LOOP(ROCKET_BOAT_SHELL_LOOP),
    WAIT(16),
    NEXT_STATE(ROCKET_BOAT_SPAWN_SIDE_STATE_COOLDOWN),
};

s16 rocket_boat_shell_cooling[10] = {
    WAIT(1),
    JUMP_UNLESS_STATE(ROCKET_BOAT_SPAWN_SIDE_STATE_IDLE, ROCKET_BOAT_SHELL_COOLING),
    WAIT(32),
    JUMP(ROCKET_BOAT_RESUME),
};

s16 rocket_boat_fire_start[6] = {
    WAIT(32),
    SET_COUNTER_RANDOM(2, 2),
};

s16 rocket_boat_fire_loop[6] = {
    ROCKET_BOAT_SPAWN_SIDE_FIRE,
    WAIT(32),
    LOOP(ROCKET_BOAT_FIRE_LOOP),
};

s16 rocket_boat_fire_cooling[3] = {
    -1, 0x20, -3,
};

u16 script_mode0_reg2 = 0x26;

s16 rocket_boat_idle_alt[6] = {
    WAIT(1),
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_MISSION_FLAG, ROCKET_BOAT_ACTIVATE_ALT,
    JUMP(ROCKET_BOAT_IDLE_ALT),
};

s16 rocket_boat_activate_alt[18] = {
    SET_COUNTER_RANDOM(64, 64),
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 3072, ROCKET_BOAT_PATROL_A_HOLD_ALT,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 3584, ROCKET_BOAT_PATROL_B_HOLD_ALT,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 0, ROCKET_BOAT_PATROL_C_HOLD_ALT,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 512, ROCKET_BOAT_PATROL_D_HOLD_ALT,
    JUMP(ROCKET_BOAT_PATROL_E_HOLD_ALT),
};

s16 rocket_boat_sweep_alt[14] = {
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 3072, ROCKET_BOAT_FOLLOWUP_ALT,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 3584, ROCKET_BOAT_PATROL_B_DECIDE_ALT,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 0, ROCKET_BOAT_PATROL_C_DECIDE_ALT,
    ROCKET_BOAT_SPAWN_SIDE_JUMP_IF_WANTED_MATCHES, 512, ROCKET_BOAT_PATROL_D_DECIDE_ALT,
    JUMP(ROCKET_BOAT_CHOOSE_DRIFT_ALT),
};

s16 rocket_boat_followup_alt[8] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 45,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_a_pause_alt[12] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_A_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 46,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_a_pause_alt_b[12] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_A_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 47,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_a_hold_setup_alt[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_a_hold_alt[8] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_A_HOLD_ALT),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 3584,
    JUMP(ROCKET_BOAT_SWEEP_ALT),
};

s16 rocket_boat_patrol_b_decide_alt[10] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 50,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_b_pause_alt[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_B_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 51,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_b_pause_alt_b[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_B_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 52,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_b_hold_setup_alt[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_b_hold_alt[12] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_B_HOLD_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_B_TURN_ALT),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 0,
    JUMP(ROCKET_BOAT_SWEEP_ALT),
};

s16 rocket_boat_patrol_b_turn_alt[4] = {
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 3072,
    JUMP(ROCKET_BOAT_SWEEP_ALT),
};

s16 rocket_boat_patrol_c_decide_alt[10] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 56,
    JUMP_RANDOM(2457, ROCKET_BOAT_FIRE_START_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_c_pause_alt[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_C_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 57,
    JUMP_RANDOM(2457, ROCKET_BOAT_FIRE_START_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_c_pause_alt_b[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_C_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 58,
    JUMP_RANDOM(2457, ROCKET_BOAT_FIRE_START_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_c_hold_setup_alt[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_c_hold_alt[12] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_C_HOLD_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_C_TURN_ALT),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 512,
    JUMP(ROCKET_BOAT_SWEEP_ALT),
};

s16 rocket_boat_patrol_c_turn_alt[4] = {
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 3584,
    JUMP(ROCKET_BOAT_SWEEP_ALT),
};

s16 rocket_boat_patrol_d_decide_alt[10] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 62,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_d_pause_alt[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_D_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 63,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_d_pause_alt_b[16] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_D_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 64,
    JUMP_RANDOM(1638, ROCKET_BOAT_FIRE_START_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_d_hold_setup_alt[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_d_hold_alt[12] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_D_HOLD_ALT),
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_D_TURN_ALT),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 1024,
    JUMP(ROCKET_BOAT_SWEEP_ALT),
};

s16 rocket_boat_patrol_d_turn_alt[4] = {
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 0,
    JUMP(ROCKET_BOAT_SWEEP_ALT),
};

s16 rocket_boat_choose_drift_alt[8] = {
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 68,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_e_pause_alt[12] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_E_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 69,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_e_pause_alt_b[12] = {
    JUMP_RANDOM(2048, ROCKET_BOAT_PATROL_E_HOLD_SETUP_ALT),
    WAIT(32),
    ROCKET_BOAT_SPAWN_SIDE_READ_VALUE, 70,
    JUMP_RANDOM(2048, ROCKET_BOAT_DRIFT_START_ALT),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_patrol_e_hold_setup_alt[4] = {
    SET_COUNTER_RANDOM(64, 64),
};

s16 rocket_boat_patrol_e_hold_alt[8] = {
    WAIT(1),
    LOOP(ROCKET_BOAT_PATROL_E_HOLD_ALT),
    ROCKET_BOAT_SPAWN_SIDE_SET_ANGLE, 512,
    JUMP(ROCKET_BOAT_SWEEP_ALT),
};

s16 rocket_boat_drift_start_alt[6] = {
    WAIT(32),
    SET_COUNTER_RANDOM(3, 3),
};

s16 rocket_boat_drift_loop_alt[6] = {
    ROCKET_BOAT_SPAWN_SIDE_FIRE_DRIFT,
    WAIT(16),
    LOOP(ROCKET_BOAT_DRIFT_LOOP_ALT),
};

s16 rocket_boat_drift_cooling_alt[3] = {
    -1, 0x20, -3,
};

u16 script_mode1_reg0 = 0x48;

s16 rocket_boat_resume_alt[4] = {
    WAIT(32),
    NEXT_STATE(ROCKET_BOAT_SPAWN_SIDE_STATE_PATROL),
};

s16 rocket_boat_shell_start_alt[10] = {
    WAIT(1),
    JUMP_UNLESS_STATE(ROCKET_BOAT_SPAWN_SIDE_STATE_ENGAGE, ROCKET_BOAT_SHELL_START_ALT),
    WAIT(16),
    SET_COUNTER_RANDOM(2, 2),
};

s16 rocket_boat_shell_loop_alt[10] = {
    ROCKET_BOAT_SPAWN_SIDE_FIRE_NEAR,
    WAIT(32),
    LOOP(ROCKET_BOAT_SHELL_LOOP_ALT),
    WAIT(16),
    NEXT_STATE(ROCKET_BOAT_SPAWN_SIDE_STATE_COOLDOWN),
};

s16 rocket_boat_shell_cooling_alt[10] = {
    WAIT(1),
    JUMP_UNLESS_STATE(ROCKET_BOAT_SPAWN_SIDE_STATE_IDLE, ROCKET_BOAT_SHELL_COOLING_ALT),
    WAIT(32),
    JUMP(ROCKET_BOAT_RESUME_ALT),
};

s16 rocket_boat_fire_start_alt[6] = {
    WAIT(32),
    SET_COUNTER_RANDOM(2, 2),
};

s16 rocket_boat_fire_loop_alt[6] = {
    ROCKET_BOAT_SPAWN_SIDE_FIRE,
    WAIT(32),
    LOOP(ROCKET_BOAT_FIRE_LOOP_ALT),
};

s16 rocket_boat_fire_cooling_alt[3] = {
    -1, 0x20, -3,
};

u16 script_mode1_ch2 = 0x4F;

s16 *rocket_boat_script_data[82] = {
    rocket_boat_idle, rocket_boat_activate, rocket_boat_sweep, rocket_boat_followup, rocket_boat_patrol_a_pause, rocket_boat_patrol_a_pause_b,
    rocket_boat_patrol_a_hold_setup, rocket_boat_patrol_a_hold, rocket_boat_patrol_b_decide, rocket_boat_patrol_b_pause, rocket_boat_patrol_b_pause_b, rocket_boat_patrol_b_hold_setup,
    rocket_boat_patrol_b_hold, rocket_boat_patrol_b_turn, rocket_boat_patrol_c_decide, rocket_boat_patrol_c_pause, rocket_boat_patrol_c_pause_b, rocket_boat_patrol_c_hold_setup,
    rocket_boat_patrol_c_hold, rocket_boat_patrol_c_turn, rocket_boat_patrol_d_decide, rocket_boat_patrol_d_pause, rocket_boat_patrol_d_pause_b, rocket_boat_patrol_d_hold_setup,
    rocket_boat_patrol_d_hold, rocket_boat_patrol_d_turn, rocket_boat_choose_drift, rocket_boat_patrol_e_pause, rocket_boat_patrol_e_pause_b, rocket_boat_patrol_e_hold_setup,
    rocket_boat_patrol_e_hold, rocket_boat_drift_start, rocket_boat_drift_loop, rocket_boat_drift_cooling, rocket_boat_resume, rocket_boat_shell_start,
    rocket_boat_shell_loop, rocket_boat_shell_cooling, rocket_boat_fire_start, rocket_boat_fire_loop, rocket_boat_fire_cooling, rocket_boat_idle_alt,
    rocket_boat_activate_alt, rocket_boat_sweep_alt, rocket_boat_followup_alt, rocket_boat_patrol_a_pause_alt, rocket_boat_patrol_a_pause_alt_b, rocket_boat_patrol_a_hold_setup_alt,
    rocket_boat_patrol_a_hold_alt, rocket_boat_patrol_b_decide_alt, rocket_boat_patrol_b_pause_alt, rocket_boat_patrol_b_pause_alt_b, rocket_boat_patrol_b_hold_setup_alt, rocket_boat_patrol_b_hold_alt,
    rocket_boat_patrol_b_turn_alt, rocket_boat_patrol_c_decide_alt, rocket_boat_patrol_c_pause_alt, rocket_boat_patrol_c_pause_alt_b, rocket_boat_patrol_c_hold_setup_alt, rocket_boat_patrol_c_hold_alt,
    rocket_boat_patrol_c_turn_alt, rocket_boat_patrol_d_decide_alt, rocket_boat_patrol_d_pause_alt, rocket_boat_patrol_d_pause_alt_b, rocket_boat_patrol_d_hold_setup_alt, rocket_boat_patrol_d_hold_alt,
    rocket_boat_patrol_d_turn_alt, rocket_boat_choose_drift_alt, rocket_boat_patrol_e_pause_alt, rocket_boat_patrol_e_pause_alt_b, rocket_boat_patrol_e_hold_setup_alt, rocket_boat_patrol_e_hold_alt,
    rocket_boat_drift_start_alt, rocket_boat_drift_loop_alt, rocket_boat_drift_cooling_alt, rocket_boat_resume_alt, rocket_boat_shell_start_alt, rocket_boat_shell_loop_alt,
    rocket_boat_shell_cooling_alt, rocket_boat_fire_start_alt, rocket_boat_fire_loop_alt, rocket_boat_fire_cooling_alt,
};

s16 *rocket_boat_side_anim_table[2] = {
    rocket_boat_idle, rocket_boat_idle_alt,
};

ScriptCallEntry rocket_boat_side_call_table[8] = {
    {NULL, 0},
    {rocket_boat_fire_drift, 0},
    {rocket_boat_fire, 0},
    {rocket_boat_fire_near, 0},
    {obj_script_set_angle, 0},
    {script_jump_if_wanted_matches, 0},
    {obj_script_read_value, 0},
    {script_jump_if_mission_flag, 0},
};

StateEntry rocket_boat_side_state_table[5] = {
    {0, ROCKET_BOAT_ANIM_IDLE, 0},
    {0, ROCKET_BOAT_ANIM_START, 0},
    {0, ROCKET_BOAT_ANIM_HOLD, 0},
    {0, ROCKET_BOAT_ANIM_RETURN, 0},
    {0, ROCKET_BOAT_ANIM_IDLE, 0},
};

RocketBoatRocketParams rocket_boat_rocket_params[2] = {
    {8, 12, 8, 0x2C}, {0x38, 6, 6, 0x2C},
};

struct SparkScriptPtrStreams {
    s16 spark_script_a[8];
    s16 rocket_boat_spark_anim_idle[4];
    s16 *table[2];
} spark_script_ptr_streams = {
    /* spark_script_a */ {
        STEP(0, 96),
        STEP(12, 97),
        STEP(12, 98),
        STEP(12, 99),
    },
    /* rocket_boat_spark_anim_idle */ {
        STEP(12, 100),
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

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_8011F874[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/video_mode_id.c"

#include "../stage/data/tint_scale_r.c"

#include "../stage/data/lens_flare_table.c"

u8 font_bitmap[92] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x80, 0xEA, 0x2A,
    0xEE, 0x0A, 0x0A, 0x00, 0xE0, 0x80, 0xEA, 0x2A, 0xE4, 0x0A, 0x0A, 0x00,
    0xE0, 0x80, 0xEA, 0x8A, 0xE4, 0x0A, 0x0A, 0x00, 0xE0, 0x80, 0xEE, 0x84,
    0xE4, 0x04, 0x04, 0x00, 0xE0, 0x80, 0xEC, 0x92, 0xF2, 0x14, 0x0A, 0x00,
    0x40, 0xA0, 0xEA, 0xAA, 0xAC, 0x0A, 0x0A, 0x00, 0xC0, 0xA0, 0xC8, 0xA8,
    0xC8, 0x08, 0x0E, 0x00, 0xC0, 0xA0, 0xCE, 0xA8, 0xCE, 0x02, 0x0E, 0x00,
    0xA0, 0xA0, 0xEE, 0xA4, 0xA4, 0x04, 0x04, 0x00, 0x80, 0x80, 0x8E, 0x88,
    0xEE, 0x08, 0x08, 0x00, 0xA0, 0xA0, 0xAE, 0xA4,
};

s32 cam_effect_flag = 0x40444;

s32 D_8011FEB8 = (s32)0x88EE80E0;

u32 D_8011FEBC[219] = {
    0x0008088E, 0x8A8E80E0, 0x000A0CEE, 0x2AEE80E0, 0x000E0AEA, 0x24EE80E0,
    0x000E04E4, 0xA8AEA0C0, 0x000E08CE, 0xACA4A0C0, 0x000E04C4, 0xA2ACA0C0,
    0x000E08C4, 0xA2ACA0C0, 0x000C02C4, 0xAAA6A0C0, 0x00020ECA, 0x9ABAD090,
    0x000A0A9C, 0x3AF280E0, 0x001212F6, 0x8AEC80E0, 0x000C0AEC, 0x9A9280E0,
    0x001212F6, 0x9EF280E0, 0x001212FE, 0x2AEC80E0, 0x000C0AEC, 0x88EE80E0,
    0x000E08E8, 0xFE040800, 0x00000804, 0xFE402000, 0x00002040, 0x10543810,
    0x00101010, 0x10101010, 0x00103854, 0x00000000, 0x00000000, 0x10101000,
    0x00100010, 0x00282800, 0x00000000, 0x287C2800, 0x00287C28, 0x507C1000,
    0x00107C14, 0x10C8C400, 0x008C4C20, 0x28483000, 0x00748854, 0x00101000,
    0x00000000, 0x20100800, 0x00081020, 0x08102000, 0x00201008, 0x38540000,
    0x00005438, 0x7C101000, 0x00001010, 0x00000000, 0x00100818, 0x7C000000,
    0x00000000, 0x00000000, 0x00001818, 0x10080400, 0x00804020, 0x84483000,
    0x00304884, 0x10301000, 0x00381010, 0x04847800, 0x00FC8078, 0x18847800,
    0x00788404, 0x90503000, 0x001010FC, 0xF880FC00, 0x00F80404, 0xF8807800,
    0x00788484, 0x0804FC00, 0x00101010, 0x78847800, 0x00788484, 0x84847800,
    0x0078047C, 0x00101000, 0x00001010, 0x00101000, 0x00201010, 0x40300C00,
    0x000C3040, 0x007C0000, 0x0000007C, 0x04186000, 0x00601804, 0x04847800,
    0x00300038, 0xB8847800, 0x0078C4C4, 0x84483000, 0x008484FC, 0xF884F800,
    0x00F88484, 0x80847800, 0x00788480, 0x8488F000, 0x00F08884, 0xF080FC00,
    0x00FC8080, 0xF880FC00, 0x00808080, 0x80847800, 0x0078849C, 0xFC848400,
    0x00848484, 0x10101000, 0x00101010, 0x04040400, 0x00788404, 0xE0988400,
    0x00848890, 0x80808000, 0x00FC8080, 0xB4CC8400, 0x00848484, 0xA4C48400,
    0x00848C94, 0x84483000, 0x00304884, 0x8484F800, 0x008080F8, 0x84483000,
    0x00344894, 0x8484F800, 0x008488F8, 0x78807C00, 0x00F80404, 0x10107C00,
    0x00101010, 0x84848400, 0x00788484, 0x84848400, 0x00304884, 0x84848400,
    0x0048B4B4, 0x30488400, 0x00844830, 0x28444400, 0x00101010, 0x1008FC00,
    0x00FC4020, 0x40407800, 0x00784040, 0x7C284400, 0x00107C10, 0x08087800,
    0x00780808, 0x00281000, 0x00000000, 0x00000000, 0x007C0000, 0x00101000,
    0x00000000, 0x7F7F7F00, 0x70707070, 0x70707070, 0x007F7F7F, 0xFEFEFE00,
    0x0E0E0E0E, 0x0E0E0E0E, 0x00FEFEFE, 0x70707070, 0x70707070, 0x0E0E0E0E,
    0x0E0E0E0E, 0xFFFFFF00, 0x00000000, 0x00000000, 0x00FFFFFF, 0x1F0C0400,
    0x0000040C, 0xF8302000, 0x00002030, 0x10000000, 0x10107C38, 0x387C1010,
    0x00000010, 0x7F361200, 0x00001236, 0xFE6C4800, 0x0000486C, 0x7C381000,
    0x107C3810, 0x10387C10, 0x0010387C, 0xFE6C2800, 0x0000286C, 0x107C3810,
    0x0010387C, 0x898583FF, 0xFFC1A191, 0x9F8484FC, 0xFC80848E, 0x00EAAEAA,
    0x00CEAACE, 0xFE7CFE00, 0x00FEF2FA, 0xFFFFFFFF, 0xFFFFFFFF, 0x70707070,
    0x707F7F7F, 0x0E0E0E0E, 0x0EFEFEFE,
};

#include "../stage/data/font_clut.c"

u32 D_801209F8[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_80121018 = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

s32 effect_spawn_phase = 0;

s32 sound_ramp_level = 0;

s32 sound_interval_timer = 0;

#include "../stage/data/frame_work_area.c"

#include "../stage/data/model_slot_count.c"

u32 D_80122534 = 0x00000000;

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

u32 D_801225B8 = 0x00000000;

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

/* labels inside the objects above */
__asm__(".globl D_80119BA2\n.set D_80119BA2, sea_mine_anim_frames+0x2\n"
        ".globl muzzle_yaw_table\n.set muzzle_yaw_table, muzzle_offset_z_table+0x2\n"
        ".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl D_8012101E\n.set D_8012101E, texture_image+0x2\n"
        ".globl enemy_gun_shot_id\n.set enemy_gun_shot_id, enemy_gun_setup+0xC\n"
        ".globl D_8011A294\n.set D_8011A294, escaping_boat_m4_boss_idle_wait+0x10\n"
        ".globl script_mode0_reg1\n.set script_mode0_reg1, rocket_boat_shell_cooling+0x10\n"
        ".globl script_mode1_reg1\n.set script_mode1_reg1, rocket_boat_shell_cooling_alt+0x10\n"
        ".globl sincos_deg90\n.set sincos_deg90, rcossin_tbl+0x1000\n"
        ".globl view_sincos\n.set view_sincos, rcossin_tbl+0x2000\n"
        ".globl sincos_deg270\n.set sincos_deg270, rcossin_tbl+0x3000\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n"
        ".globl D_801226E6\n.set D_801226E6, view_nudge+0x2\n"
        ".globl d_801201AE\n.set d_801201AE, flow+0x2\n"
        ".globl flow_angle\n.set flow_angle, flow+0x4\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl laser_barrier_boat_script\n.set laser_barrier_boat_script, laser_barrier_boat_anims+0x0\n"
        ".globl laser_barrier_boat_data\n.set laser_barrier_boat_data, laser_barrier_boat_anims+0x8\n"
        ".globl laser_barrier_boat_select\n.set laser_barrier_boat_select, laser_barrier_boat_scripts+0x0\n"
        ".globl laser_barrier_boat_fly\n.set laser_barrier_boat_fly, laser_barrier_boat_scripts+0xC\n"
        ".globl laser_barrier_boat_mine\n.set laser_barrier_boat_mine, laser_barrier_boat_scripts+0x1C\n"
        ".globl laser_barrier_boat_mine_idle\n.set laser_barrier_boat_mine_idle, laser_barrier_boat_scripts+0x24\n"
        ".globl laser_barrier_boat_fly_wait\n.set laser_barrier_boat_fly_wait, laser_barrier_boat_scripts+0x2C\n"
        ".globl laser_barrier_boat_recheck\n.set laser_barrier_boat_recheck, laser_barrier_boat_scripts+0x38\n"
        ".globl laser_barrier_boat_type_data\n.set laser_barrier_boat_type_data, laser_barrier_boat_scripts+0x40\n"
        ".globl D_80119070\n.set D_80119070, laser_barrier_boat_scripts+0x58\n"
        ".globl jetski_wait_approach\n.set jetski_wait_approach, jetski_scripts+0x0\n"
        ".globl jetski_aim\n.set jetski_aim, jetski_scripts+0xC\n"
        ".globl jetski_fire_start\n.set jetski_fire_start, jetski_scripts+0x1C\n"
        ".globl jetski_fire_shot\n.set jetski_fire_shot, jetski_scripts+0x34\n"
        ".globl jetski_fire_loop\n.set jetski_fire_loop, jetski_scripts+0x38\n"
        ".globl jetski_turn_back\n.set jetski_turn_back, jetski_scripts+0x50\n"
        ".globl jetski_idle_start\n.set jetski_idle_start, jetski_scripts+0x54\n"
        ".globl jetski_idle_wait\n.set jetski_idle_wait, jetski_scripts+0x64\n"
        ".globl jetski_halt\n.set jetski_halt, jetski_scripts+0x78\n"
        ".globl jetski_wait_side_slide\n.set jetski_wait_side_slide, jetski_scripts+0x80\n"
        ".globl jetski_side_aim\n.set jetski_side_aim, jetski_scripts+0x8C\n"
        ".globl jetski_side_fire_start\n.set jetski_side_fire_start, jetski_scripts+0x9C\n"
        ".globl jetski_side_fire_shot\n.set jetski_side_fire_shot, jetski_scripts+0xB4\n"
        ".globl jetski_side_fire_loop\n.set jetski_side_fire_loop, jetski_scripts+0xB8\n"
        ".globl jetski_side_turn_back\n.set jetski_side_turn_back, jetski_scripts+0xD0\n"
        ".globl jetski_side_idle_start\n.set jetski_side_idle_start, jetski_scripts+0xD4\n"
        ".globl jetski_side_idle_wait\n.set jetski_side_idle_wait, jetski_scripts+0xE4\n"
        ".globl jetski_side_exit_wait\n.set jetski_side_exit_wait, jetski_scripts+0xF8\n"
        ".globl jetski_approach_aim\n.set jetski_approach_aim, jetski_scripts+0x104\n"
        ".globl jetski_approach_fire_start\n.set jetski_approach_fire_start, jetski_scripts+0x114\n"
        ".globl jetski_approach_fire_shot\n.set jetski_approach_fire_shot, jetski_scripts+0x12C\n"
        ".globl jetski_approach_fire_loop\n.set jetski_approach_fire_loop, jetski_scripts+0x130\n"
        ".globl jetski_approach_turn_back\n.set jetski_approach_turn_back, jetski_scripts+0x148\n"
        ".globl jetski_approach_idle_start\n.set jetski_approach_idle_start, jetski_scripts+0x14C\n"
        ".globl jetski_approach_idle_wait\n.set jetski_approach_idle_wait, jetski_scripts+0x15C\n"
        ".globl jetski_approach_halt\n.set jetski_approach_halt, jetski_scripts+0x170\n"
        ".globl jetski_type_data\n.set jetski_type_data, jetski_scripts+0x178\n"
        ".globl D_8011941C\n.set D_8011941C, jetski_scripts+0x1E0\n"
        ".globl heavy_mobile_suit_script\n.set heavy_mobile_suit_script, heavy_mobile_suit_anims+0x0\n"
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
        ".globl heavy_mobile_suit_cycle\n.set heavy_mobile_suit_cycle, heavy_mobile_suit_scripts+0x0\n"
        ".globl heavy_mobile_suit_patrol_start\n.set heavy_mobile_suit_patrol_start, heavy_mobile_suit_scripts+0x4\n"
        ".globl heavy_mobile_suit_scan\n.set heavy_mobile_suit_scan, heavy_mobile_suit_scripts+0xC\n"
        ".globl heavy_mobile_suit_idle\n.set heavy_mobile_suit_idle, heavy_mobile_suit_scripts+0x1C\n"
        ".globl heavy_mobile_suit_idle_watch\n.set heavy_mobile_suit_idle_watch, heavy_mobile_suit_scripts+0x2C\n"
        ".globl heavy_mobile_suit_spotted\n.set heavy_mobile_suit_spotted, heavy_mobile_suit_scripts+0x40\n"
        ".globl heavy_mobile_suit_spotted_wait\n.set heavy_mobile_suit_spotted_wait, heavy_mobile_suit_scripts+0x50\n"
        ".globl heavy_mobile_suit_patrol\n.set heavy_mobile_suit_patrol, heavy_mobile_suit_scripts+0x5C\n"
        ".globl heavy_mobile_suit_patrol_wait\n.set heavy_mobile_suit_patrol_wait, heavy_mobile_suit_scripts+0x6C\n"
        ".globl heavy_mobile_suit_search\n.set heavy_mobile_suit_search, heavy_mobile_suit_scripts+0x78\n"
        ".globl heavy_mobile_suit_search_watch\n.set heavy_mobile_suit_search_watch, heavy_mobile_suit_scripts+0x88\n"
        ".globl heavy_mobile_suit_search_end\n.set heavy_mobile_suit_search_end, heavy_mobile_suit_scripts+0xA0\n"
        ".globl heavy_mobile_suit_pursue\n.set heavy_mobile_suit_pursue, heavy_mobile_suit_scripts+0xB0\n"
        ".globl heavy_mobile_suit_pursue_wait\n.set heavy_mobile_suit_pursue_wait, heavy_mobile_suit_scripts+0xC0\n"
        ".globl heavy_mobile_suit_fire_burst\n.set heavy_mobile_suit_fire_burst, heavy_mobile_suit_scripts+0xCC\n"
        ".globl heavy_mobile_suit_fire_wait\n.set heavy_mobile_suit_fire_wait, heavy_mobile_suit_scripts+0xE8\n"
        ".globl heavy_mobile_suit_cooldown\n.set heavy_mobile_suit_cooldown, heavy_mobile_suit_scripts+0xF4\n"
        ".globl heavy_mobile_suit_cooling\n.set heavy_mobile_suit_cooling, heavy_mobile_suit_scripts+0x104\n"
        ".globl heavy_mobile_suit_disengage\n.set heavy_mobile_suit_disengage, heavy_mobile_suit_scripts+0x114\n"
        ".globl heavy_mobile_suit_disengage_wait\n.set heavy_mobile_suit_disengage_wait, heavy_mobile_suit_scripts+0x128\n"
        ".globl heavy_mobile_suit_search_done\n.set heavy_mobile_suit_search_done, heavy_mobile_suit_scripts+0x134\n"
        ".globl heavy_mobile_suit_restart\n.set heavy_mobile_suit_restart, heavy_mobile_suit_scripts+0x140\n"
        ".globl heavy_mobile_suit_type_data\n.set heavy_mobile_suit_type_data, heavy_mobile_suit_scripts+0x144\n"
        ".globl D_80119860\n.set D_80119860, heavy_mobile_suit_scripts+0x19C\n"
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
        ".globl sea_mine_script\n.set sea_mine_script, sea_mine_anims+0x0\n"
        ".globl sea_mine_script_arg\n.set sea_mine_script_arg, sea_mine_anims+0x8\n"
        ".globl escaping_boat_m4_boss_anim_idle\n.set escaping_boat_m4_boss_anim_idle, escaping_boat_m4_boss_anims+0x0\n"
        ".globl escaping_boat_m4_boss_anim_fire_start\n.set escaping_boat_m4_boss_anim_fire_start, escaping_boat_m4_boss_anims+0x8\n"
        ".globl escaping_boat_m4_boss_anim_fire_loop\n.set escaping_boat_m4_boss_anim_fire_loop, escaping_boat_m4_boss_anims+0xC\n"
        ".globl escaping_boat_m4_boss_anim_cooldown\n.set escaping_boat_m4_boss_anim_cooldown, escaping_boat_m4_boss_anims+0x14\n"
        ".globl escaping_boat_m4_boss_data\n.set escaping_boat_m4_boss_data, escaping_boat_m4_boss_anims+0x20\n"
        ".globl rocket_boat_anim_idle\n.set rocket_boat_anim_idle, rocket_boat_anims+0x0\n"
        ".globl rocket_boat_anim_start\n.set rocket_boat_anim_start, rocket_boat_anims+0x8\n"
        ".globl rocket_boat_anim_hold\n.set rocket_boat_anim_hold, rocket_boat_anims+0xC\n"
        ".globl rocket_boat_anim_return\n.set rocket_boat_anim_return, rocket_boat_anims+0x14\n"
        ".globl rocket_boat_data\n.set rocket_boat_data, rocket_boat_anims+0x20\n"
        ".globl spark_script_a\n.set spark_script_a, spark_script_ptr_streams+0x0\n"
        ".globl rocket_boat_spark_anim_idle\n.set rocket_boat_spark_anim_idle, spark_script_ptr_streams+0x10\n"
        ".globl spark_script_ptr\n.set spark_script_ptr, spark_script_ptr_streams+0x18\n");
