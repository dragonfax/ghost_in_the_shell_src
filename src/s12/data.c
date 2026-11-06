/* s12 data 0x8011ECBC-0x8012C000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s12_types.h"
#include "script.h"
#include "scripts.h"
#include "sounds.h"

extern void cam_path_obj_spawn();
extern void cam_track_b_setup();
extern void cam_track_get();
extern void cam_track_init();
extern void cam_track_set_active();
extern void cam_track_set_on();
extern void cam_track_setup();
extern void cam_track_slot_get();
extern void cam_track_start_both();
extern void ctrl_spawn();
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
extern void enemy_fly_aim();
extern void enemy_fly_approach();
extern void enemy_fly_move();
extern void enemy_fly_spin();
extern void enemy_move_or_wait();
extern void enemy_retarget_jitter();
extern void enemy_shoot_update();
extern void enemy_wait_switch();
extern void enemy_walk_step();
extern u8 file_arkb_ch0_cb4[];
extern u8 file_arkb_ch0_clt[];
extern u8 file_arkb_ch0_vx1[];
extern u8 file_arkb_tp0_clt[];
extern u8 file_arkb_tp0_xs3[];
extern u8 file_bal2_ch0_cb4[];
extern u8 file_bal2_ch0_clt[];
extern u8 file_bal2_ch0_vx1[];
extern u8 file_bal2_tp0_clt[];
extern u8 file_bal2_tp0_xs3[];
extern u8 file_bosc_ch0_cb4[];
extern u8 file_bosc_ch0_clt[];
extern u8 file_bosc_ch0_vx1[];
extern u8 file_bosc_ch1_cb4[];
extern u8 file_bosc_ch1_vx1[];
extern u8 file_bosc_ch2_cb4[];
extern u8 file_bosc_ch2_vx1[];
extern u8 file_bosc_ch3_cb4[];
extern u8 file_bosc_ch3_vx1[];
extern u8 file_bosc_ch4_vx1[];
extern u8 file_bosc_tp0_clt[];
extern u8 file_bosc_tp0_xs3[];
extern u8 file_bosc_tp1_clt[];
extern u8 file_bosc_tp1_xs3[];
extern u8 file_dorc_ch0_cb4[];
extern u8 file_hou1_ch0_cb4[];
extern u8 file_hou1_ch0_clt[];
extern u8 file_hou1_ch0_vx1[];
extern u8 file_hou1_tp0_clt[];
extern u8 file_hou1_tp0_xs3[];
extern u8 file_jira_ch0_cb4[];
extern u8 file_jira_ch0_clt[];
extern u8 file_jira_ch0_vx1[];
extern u8 file_jira_tp0_clt[];
extern u8 file_jira_tp0_xs3[];
extern u8 file_msub_ch0_cb4[];
extern u8 file_msub_ch0_clt[];
extern u8 file_msub_ch0_vx1[];
extern u8 file_msub_tp0_clt[];
extern u8 file_msub_tp0_xs3[];
extern u8 file_ohel_ch0_cb4[];
extern u8 file_ohel_ch0_clt[];
extern u8 file_ohel_ch0_vx1[];
extern u8 file_ohel_tp0_clt[];
extern u8 file_ohel_tp0_xs3[];
extern u8 file_ohel_tp1_clt[];
extern u8 file_ohel_tp1_xs3[];
extern void fly_path_next();
extern void flyer_retreat();
extern void flyer_wander();
extern void fn_800BD11C();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void fn_s07_800BAE10();
extern void fuchikoma_chase_update();
extern void func_800CCA24();
extern void gun_turret_spawn();
extern void half_stream_read();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void helicopter_spawn();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void loop_sound_fade_in();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void obj_area_update();
extern void obj_attack_player();
extern void obj_call_hook();
extern void obj_fall_update();
extern void obj_handle_result();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_jump_if_player_near();
extern void obj_loop_sound_start();
extern void obj_loop_sound_stop();
extern void obj_release_check();
extern void obj_script_read_jump();
extern void obj_script_read_s32();
extern void obj_script_read_speed();
extern void obj_set_next_state();
extern void obj_sound_play();
extern void obj_speed_approach();
extern void obj_start_loop_sound();
extern void obj_stop_loop_sound();
extern void obj_turn_to_player_16();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placed_actor_spawn();
extern void placement_spawn();
extern void player_status_reload();
extern void proximity_flags_reset();
extern void proximity_sensor_spawn();
extern void ramp_start_script();
extern void rec_clear_flags_list();
extern void ring_index_dec();
extern void script_branch_if_aligned();
extern void script_branch_if_at_least();
extern void script_branch_if_near();
extern void script_branch_if_near_player();
extern void script_branch_if_not_aligned();
extern void script_flag_clear();
extern void script_jump_if_mode();
extern void script_jump_if_op_eq();
extern void script_jump_if_player_far();
extern void script_jump_if_player_in_radius();
extern void script_jump_if_within_range();
extern void script_jump_near_corner();
extern void script_op_aim_and_track();
extern void script_op_chaser_mode();
extern void script_op_fire_aimed();
extern void script_op_fx_spawn();
extern void script_op_fx_stop();
extern void script_op_gun_set_value();
extern void script_op_jump_clear_flag();
extern void script_op_jump_if_facing_player();
extern void script_op_jump_if_flag();
extern void script_op_jump_if_flag_in_range();
extern void script_op_jump_if_health_below();
extern void script_op_jump_if_health_flag();
extern void script_op_jump_if_health_low();
extern void script_op_jump_if_in_range();
extern void script_op_jump_if_outside();
extern void script_op_jump_if_player_below();
extern void script_op_jump_if_player_in_range();
extern void script_op_jump_if_rand();
extern void script_op_jump_if_roll();
extern void script_op_jump_if_sum_nonpositive();
extern void script_op_jump_if_turn_left();
extern void script_op_jump_if_vy_nonneg();
extern void script_op_jump_table_if_player_far();
extern void script_op_mode();
extern void script_op_nop();
extern void script_op_roll_random();
extern void script_op_scroll_seg_retract();
extern void script_op_set_enemy_sound();
extern void script_op_set_flag();
extern void script_op_set_mode();
extern void script_op_set_move_mode();
extern void script_op_set_part_mode();
extern void script_op_set_shot_timer();
extern void script_op_set_sound();
extern void script_op_set_turn();
extern void script_op_set_vy();
extern void script_op_spawn_at_offset();
extern void script_op_turn_step();
extern void script_op_value_push();
extern void script_read_fixed4();
extern void script_set_turn_mode();
extern void script_skip_halfword();
extern void scroll_stream_start();
extern void shot_fire_pair();
extern void smg_soldier_spawn();
extern void sound_start_on_owner();
extern void sound_stop_pair();
extern void spread_shot_fire();
extern u8 str_b12_dat_fac[];
extern u8 str_b12_ene_fac[];
extern u8 str_com_dat_fac[];
extern u8 str_enemy_arkb_data[];
extern u8 str_enemy_bal2_data[];
extern u8 str_enemy_bosc_data[];
extern u8 str_enemy_cbsc_data[];
extern u8 str_enemy_ctlc_data[];
extern u8 str_enemy_dorc_data[];
extern u8 str_enemy_hou1_data[];
extern u8 str_enemy_jira_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_msub_data[];
extern u8 str_enemy_ohel_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_hgh_apdea3[];
extern u8 str_hgh_cnf_bcf[];
extern u8 str_hgh_joy_bin[];
extern u8 str_hpt_apdea3[];
extern u8 str_hpt_joy_bin[];
extern u8 str_lst_cnf_bcf[];
extern u8 str_m12_dat_fac[];
extern u8 str_m43_cnf_bcf[];
extern u8 str_m43_joy_bin[];
extern u8 str_main_data[];
extern u8 str_msgs_spr_clt[];
extern u8 str_msgs_spr_grc[];
extern u8 str_msgs_spr_so3[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_s12_boss[];
extern u8 str_s12_dat_fac[];
extern u8 str_s12_ene_fac[];
extern u8 str_s12_miss[];
extern u8 str_s12_stage[];
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
extern void supermech_fire();
extern void supermech_spawn();
extern u8 text_packets[];
extern void text_slot_setup();
extern void timer_tail_spawn();
extern void track_set_enabled();
extern void track_setup();
extern void value_queue_pop();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_8011EF35[];
extern u8 D_8011EF36[];
extern u8 D_8011EF37[];
extern u8 D_8012A51E[];
extern u8 D_8012B9A8[];
extern u8 D_8012BC92[];
extern u8 D_8012BFE2[];
extern u8 cos_table[];
extern u8 d_80117788[];
extern u8 d_8011778C[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 d_801201AE[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 fade_target_color_vy[];
extern u8 fade_target_color_vz[];
extern u8 flow_angle[];
extern u8 gun_hit_effect_table[];
extern u8 pad1_pressed[];
extern u8 proximity_sensor_offsets[];
extern u8 proximity_sensor_range_x[];
extern u8 proximity_sensor_range_z[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 smg_soldier_hit_script[];
extern u8 view_sincos[];
extern s32 area;
extern ScanItem area_stage_items[];
extern AreaEntry area_stage_record;
extern AreaEntry area_miss_record;
extern ScanItem area_boss_items[];
extern AreaEntry area_boss_entry;
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
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
extern ModelSlotHead timer_tail_data;
extern ModelBlockRef bal2_palettes[];
extern ModelBlockRef bal2_textures[];
extern ModelBlockRef D_8011F4E0[];
extern ModelBlockRange D_8011F4F0[];
extern s16 D_8011F500[];
extern ModelBlock bal2_model_block;
extern u8 *D_8011F52C[];
extern ScanEntry bal2_scan_entry;
extern StateEntry timer_tail_states[1];
extern s16 timer_tail_script[];
extern s16 *timer_tail_script_value[];
extern s32 loop_sound_fade_handle;
extern s16 d_8011B7AC[];
extern s32 smg_soldier_asset[];
extern ModelBlockRef msub_palettes[];
extern ModelBlockRef msub_textures[];
extern ModelBlockRef rocket_fuchikoma_fire_start[];
extern ModelBlockRange model_scale_ranges[];
extern ModelBlockRange model_link_ranges[];
extern ModelBlock msub_model_block;
extern u8 *msub_file_table[];
extern ScanEntry msub_scan_entry;
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
extern s16 smg_soldier_idle_cycle_alt[];
extern s16 smg_soldier_patrol[];
extern s16 smg_soldier_wander_start[];
extern s16 smg_soldier_wander_hold[];
extern s16 smg_soldier_hold[];
extern s16 smg_soldier_hold_pause[];
extern s16 smg_soldier_hold_cycle_alt[];
extern s16 smg_soldier_walk[];
extern s16 smg_soldier_walk_step[];
extern s16 smg_soldier_walk_cycle_alt[];
extern s16 smg_soldier_walk_pause[];
extern s16 smg_soldier_walk_pause_cycle_alt[];
extern s16 *smg_soldier_jump_table[];
extern s16 *smg_soldier_script[];
extern StateEntry smg_soldier_states[];
extern s32 proximity_asset[3];
extern ModelBlockRef D_8011F9B4[];
extern ModelBlockRef D_8011F9CC[];
extern ModelBlockRef D_8011F9DC[];
extern ModelBlockRange D_8011F9EC[];
extern ModelBlock jira_model_block;
extern u8 *jira_stage_files[];
extern ScanEntry jira_load_step;
extern StateEntry placed_actor_states[1];
extern s16 placed_actor_script[];
extern s16 *placed_actor_script_value[];
extern u8 *dorc_stage_files[];
extern s32 D_8011FA5C;
extern s32 prox_origin[2];
extern ScanEntry dorc_load_step;
extern u16 prox_cells[];
extern s32 D_8011FAF8[];
extern ScanEntry ctlc_load_step;
extern s32 cam_trigger_min_x;
extern s32 cam_trigger_max_x;
extern s32 cam_trigger_min_y;
extern s32 cam_trigger_max_y;
extern s32 cam_trigger_min_z;
extern s32 cam_trigger_max_z;
extern BoundsBox cam_boxes[2];
extern s32 rec_clear_ids[7];
extern s32 anim_obj_data[5];
extern PathPoint cam_path_data[11];
extern SoundVolume D_8011FC44[8];
extern s32 supermech_model_id[3];
extern ModelBlockRef bosc_palette_refs[];
extern ModelBlockRef bosc_texture_refs[];
extern ModelBlockRef bosc_model_refs[];
extern ModelBlockRange D_8011FCF8[];
extern ModelBlockRange D_8011FD38[];
extern ModelBlockRange D_8011FD48[];
extern ModelBlock bosc_model_block;
extern u8 *bosc_stage_files[];
extern ScanEntry supermech_scan_entry;
extern s16 rooftop_supermech_m12_final_boss_anim_idle[];
extern s16 rooftop_supermech_m12_final_boss_anim_walk_loop[];
extern s16 rooftop_supermech_m12_final_boss_anim_walk_start[];
extern s16 rooftop_supermech_m12_final_boss_anim_walk_lead_in[];
extern s16 rooftop_supermech_m12_final_boss_anim_halt[];
extern s16 rooftop_supermech_m12_final_boss_anim_halt_settle[];
extern s16 rooftop_supermech_m12_final_boss_anim_turn_start[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge_slow[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge_hold[];
extern s16 rooftop_supermech_m12_final_boss_anim_recover_enter[];
extern ScriptStep rooftop_supermech_m12_final_boss_anim_recover_hold[2];
extern ScriptStep rooftop_supermech_m12_final_boss_anim_turn_recover[17];
extern s16 rooftop_supermech_m12_final_boss_anim_fire_burst[];
extern s16 rooftop_supermech_m12_final_boss_anim_fire_burst_hold[];
extern s16 rooftop_supermech_m12_final_boss_anim_fire_burst_end[];
extern s16 rooftop_supermech_m12_final_boss_anim_spread_attack[];
extern s16 rooftop_supermech_m12_final_boss_anim_spread_attack_end[];
extern s16 rooftop_supermech_m12_final_boss_anim_spread_attack_second[];
extern s16 rooftop_supermech_m12_final_boss_anim_spread_attack_second_end[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge_alt_start[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge_alt_continue[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge_second_alt_start[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge_second_alt_end[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge_end[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge_second[];
extern s16 rooftop_supermech_m12_final_boss_anim_charge_second_end[];
extern s16 rooftop_supermech_m12_final_boss_anim_aim_attack[];
extern s16 rooftop_supermech_m12_final_boss_anim_aim_hold[];
extern s16 rooftop_supermech_m12_final_boss_anim_aim_recover[];
extern s16 rooftop_supermech_m12_final_boss_anim_aim_attack_second[];
extern s16 rooftop_supermech_m12_final_boss_anim_aim_second_hold[];
extern s16 rooftop_supermech_m12_final_boss_anim_aim_second_recover[];
extern s16 rooftop_supermech_m12_final_boss_anim_scroll_attack[];
extern s16 rooftop_supermech_m12_final_boss_anim_scroll_attack_mid[];
extern s16 rooftop_supermech_m12_final_boss_anim_scroll_attack_late[];
extern s16 rooftop_supermech_m12_final_boss_anim_scroll_attack_end[];
extern s16 rooftop_supermech_m12_final_boss_anim_scroll_second_start[];
extern s16 rooftop_supermech_m12_final_boss_anim_scroll_second_mid[];
extern s16 rooftop_supermech_m12_final_boss_anim_scroll_second_late[];
extern s16 rooftop_supermech_m12_final_boss_anim_scroll_second_end[];
extern s16 rooftop_supermech_m12_final_boss_anim_turn_long_start[];
extern s16 rooftop_supermech_m12_final_boss_anim_turn_long_hold[];
extern s16 rooftop_supermech_m12_final_boss_anim_turn_long_recover[];
extern s16 *supermech_script_entry[44];
extern u32 spread_offsets_alt[];
extern u32 spread_offsets_main[];
extern s16 burst_vec_a_x;
extern s16 burst_vec_a_z;
extern s16 burst_vec_a_y;
extern s16 burst_vec_b_x;
extern s16 burst_vec_b_z;
extern s16 burst_vec_b_y;
extern SVECTOR shot_muzzles_a[];
extern SVECTOR shot_muzzles_b[];
extern SVECTOR supermech_side_muzzles[];
extern s16 spawn_offset_x;
extern s16 spawn_offset_y;
extern s16 spawn_offset_z;
extern ScriptCallEntry D_80120630[48];
extern s16 rooftop_supermech_m12_final_boss_intro[];
extern s16 rooftop_supermech_m12_final_boss_scroll_attack_gate[];
extern s16 rooftop_supermech_m12_final_boss_scroll_launch[];
extern s16 rooftop_supermech_m12_final_boss_scroll_launch_wait[];
extern s16 rooftop_supermech_m12_final_boss_scroll_fire[];
extern s16 rooftop_supermech_m12_final_boss_scroll_fire_pause[];
extern s16 rooftop_supermech_m12_final_boss_scroll_pause_wait[];
extern s16 rooftop_supermech_m12_final_boss_scroll_hold_wait[];
extern s16 rooftop_supermech_m12_final_boss_scroll_retract[];
extern s16 rooftop_supermech_m12_final_boss_scroll_retract_wait[];
extern s16 rooftop_supermech_m12_final_boss_scroll_done[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_gate[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_launch[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_launch_wait[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_fire[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_pause[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_pause_wait[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_hold_wait[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_retract[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_retract_wait[];
extern s16 rooftop_supermech_m12_final_boss_scroll_second_done[];
extern s16 rooftop_supermech_m12_final_boss_spread_gate[];
extern s16 rooftop_supermech_m12_final_boss_spread_launch[];
extern s16 rooftop_supermech_m12_final_boss_spread_launch_wait[];
extern s16 rooftop_supermech_m12_final_boss_spread_fire[];
extern s16 rooftop_supermech_m12_final_boss_spread_fire_wait[];
extern s16 rooftop_supermech_m12_final_boss_spread_done[];
extern s16 rooftop_supermech_m12_final_boss_spread_pop[];
extern s16 rooftop_supermech_m12_final_boss_spread_second_gate[];
extern s16 rooftop_supermech_m12_final_boss_spread_second_launch[];
extern s16 rooftop_supermech_m12_final_boss_spread_second_launch_wait[];
extern s16 rooftop_supermech_m12_final_boss_spread_second_fire[];
extern s16 rooftop_supermech_m12_final_boss_spread_second_fire_wait[];
extern s16 rooftop_supermech_m12_final_boss_spread_second_done[];
extern s16 rooftop_supermech_m12_final_boss_spread_second_pop[];
extern s16 rooftop_supermech_m12_final_boss_aim_gate[];
extern s16 rooftop_supermech_m12_final_boss_aim_launch[];
extern s16 rooftop_supermech_m12_final_boss_aim_launch_wait[];
extern s16 rooftop_supermech_m12_final_boss_aim_start[];
extern s16 rooftop_supermech_m12_final_boss_aim_loop_wait[];
extern s16 rooftop_supermech_m12_final_boss_aim_fire[];
extern s16 rooftop_supermech_m12_final_boss_aim_end[];
extern s16 rooftop_supermech_m12_final_boss_aim_end_wait[];
extern s16 rooftop_supermech_m12_final_boss_aim_done[];
extern s16 rooftop_supermech_m12_final_boss_aim_second_gate[];
extern s16 rooftop_supermech_m12_final_boss_aim_second_launch[];
extern s16 rooftop_supermech_m12_final_boss_aim_second_launch_wait[];
extern s16 rooftop_supermech_m12_final_boss_aim_second_start[];
extern s16 rooftop_supermech_m12_final_boss_aim_second_loop_wait[];
extern s16 rooftop_supermech_m12_final_boss_aim_second_fire[];
extern s16 rooftop_supermech_m12_final_boss_aim_second_end[];
extern s16 rooftop_supermech_m12_final_boss_aim_second_end_wait[];
extern s16 rooftop_supermech_m12_final_boss_aim_second_done[];
extern s16 rooftop_supermech_m12_final_boss_fire_gate[];
extern s16 rooftop_supermech_m12_final_boss_fire_burst_launch[];
extern s16 rooftop_supermech_m12_final_boss_fire_burst_launch_wait[];
extern s16 rooftop_supermech_m12_final_boss_fire_burst_start[];
extern s16 rooftop_supermech_m12_final_boss_fire_burst_loop_wait[];
extern s16 rooftop_supermech_m12_final_boss_fire_burst_shot[];
extern s16 rooftop_supermech_m12_final_boss_fire_burst_end[];
extern s16 rooftop_supermech_m12_final_boss_fire_burst_end_wait[];
extern s16 rooftop_supermech_m12_final_boss_fire_burst_done[];
extern s16 rooftop_supermech_m12_final_boss_fire_burst_pop[];
extern s16 rooftop_supermech_m12_final_boss_charge_gate[];
extern s16 rooftop_supermech_m12_final_boss_charge_launch[];
extern s16 rooftop_supermech_m12_final_boss_charge_launch_wait[];
extern s16 rooftop_supermech_m12_final_boss_charge_release[];
extern s16 rooftop_supermech_m12_final_boss_charge_release_wait[];
extern s16 rooftop_supermech_m12_final_boss_charge_done[];
extern s16 rooftop_supermech_m12_final_boss_charge_pop[];
extern s16 rooftop_supermech_m12_final_boss_charge_second_gate[];
extern s16 rooftop_supermech_m12_final_boss_charge_second_launch[];
extern s16 rooftop_supermech_m12_final_boss_charge_second_launch_wait[];
extern s16 rooftop_supermech_m12_final_boss_charge_second_release[];
extern s16 rooftop_supermech_m12_final_boss_charge_second_release_wait[];
extern s16 rooftop_supermech_m12_final_boss_charge_second_done[];
extern s16 rooftop_supermech_m12_final_boss_charge_second_pop[];
extern s16 rooftop_supermech_m12_final_boss_reposition_enter[];
extern s16 rooftop_supermech_m12_final_boss_reposition_launch[];
extern s16 rooftop_supermech_m12_final_boss_reposition_wait[];
extern s16 rooftop_supermech_m12_final_boss_advance_start[];
extern s16 rooftop_supermech_m12_final_boss_advance_loop_wait[];
extern s16 rooftop_supermech_m12_final_boss_advance_check[];
extern s16 rooftop_supermech_m12_final_boss_advance_arrive[];
extern s16 rooftop_supermech_m12_final_boss_halt_wait[];
extern s16 rooftop_supermech_m12_final_boss_halt[];
extern s16 rooftop_supermech_m12_final_boss_halt_wait_end[];
extern s16 rooftop_supermech_m12_final_boss_halt_pop[];
extern s16 rooftop_supermech_m12_final_boss_reposition_alt_enter[];
extern s16 rooftop_supermech_m12_final_boss_reposition_alt_launch[];
extern s16 rooftop_supermech_m12_final_boss_reposition_alt_wait[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_start[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_loop_wait[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_check[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_arrive[];
extern s16 rooftop_supermech_m12_final_boss_halt_far_wait[];
extern s16 rooftop_supermech_m12_final_boss_halt_far[];
extern s16 rooftop_supermech_m12_final_boss_halt_far_wait_end[];
extern s16 rooftop_supermech_m12_final_boss_halt_far_pop[];
extern s16 rooftop_supermech_m12_final_boss_reposition_far_enter[];
extern s16 rooftop_supermech_m12_final_boss_reposition_far_launch[];
extern s16 rooftop_supermech_m12_final_boss_reposition_far_wait[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_alt_start[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_alt_wait[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_alt_check[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_alt_arrive[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_alt_halt_wait[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_halt[];
extern s16 rooftop_supermech_m12_final_boss_advance_far_halt_wait[];
extern s16 rooftop_supermech_m12_final_boss_halt_far_alt_pop[];
extern s16 rooftop_supermech_m12_final_boss_rest_entry[];
extern s16 rooftop_supermech_m12_final_boss_rest_start[];
extern s16 rooftop_supermech_m12_final_boss_rest_wait[];
extern s16 rooftop_supermech_m12_final_boss_rest_done[];
extern s16 rooftop_supermech_m12_final_boss_low_health_entry[];
extern s16 rooftop_supermech_m12_final_boss_low_health_reset[];
extern s16 rooftop_supermech_m12_final_boss_idle_loop[];
extern s16 rooftop_supermech_m12_final_boss_turn_direction_pick[];
extern s16 rooftop_supermech_m12_final_boss_chase_start[];
extern s16 rooftop_supermech_m12_final_boss_chase_wait[];
extern s16 rooftop_supermech_m12_final_boss_chase_end[];
extern s16 rooftop_supermech_m12_final_boss_chase_end_wait[];
extern s16 rooftop_supermech_m12_final_boss_chase_done[];
extern s16 rooftop_supermech_m12_final_boss_chase_pop[];
extern s16 rooftop_supermech_m12_final_boss_idle_entry[];
extern s16 rooftop_supermech_m12_final_boss_idle_reset[];
extern s16 rooftop_supermech_m12_final_boss_idle_loop_b[];
extern s16 rooftop_supermech_m12_final_boss_chase_fly_entry[];
extern s16 rooftop_supermech_m12_final_boss_chase_fly_start[];
extern s16 rooftop_supermech_m12_final_boss_chase_fly_wait[];
extern s16 rooftop_supermech_m12_final_boss_chase_fly_end[];
extern s16 rooftop_supermech_m12_final_boss_chase_fly_end_wait[];
extern s16 rooftop_supermech_m12_final_boss_chase_fly_done[];
extern s16 rooftop_supermech_m12_final_boss_chase_fly_pop[];
extern s16 rooftop_supermech_m12_final_boss_close_range_low_health_pick[];
extern s16 rooftop_supermech_m12_final_boss_charge_side_pick[];
extern s16 rooftop_supermech_m12_final_boss_retreat_pick[];
extern s16 rooftop_supermech_m12_final_boss_retreat_return[];
extern s16 rooftop_supermech_m12_final_boss_scroll_attack_pick[];
extern s16 rooftop_supermech_m12_final_boss_low_health_close_return[];
extern s16 rooftop_supermech_m12_final_boss_far_range_low_health_pick[];
extern s16 rooftop_supermech_m12_final_boss_charge_aligned_pick[];
extern s16 rooftop_supermech_m12_final_boss_spread_pick[];
extern s16 rooftop_supermech_m12_final_boss_fire_pick[];
extern s16 rooftop_supermech_m12_final_boss_mid_fire_aligned_gate[];
extern s16 rooftop_supermech_m12_final_boss_mid_fire_pop[];
extern s16 rooftop_supermech_m12_final_boss_long_range_low_health_pick[];
extern s16 rooftop_supermech_m12_final_boss_far_attack_roll[];
extern s16 rooftop_supermech_m12_final_boss_far_spread_pick[];
extern s16 rooftop_supermech_m12_final_boss_far_charge_pick[];
extern s16 rooftop_supermech_m12_final_boss_far_attack_roll_return[];
extern s16 rooftop_supermech_m12_final_boss_mid_range_pick[];
extern s16 rooftop_supermech_m12_final_boss_default_reposition[];
extern s16 rooftop_supermech_m12_final_boss_default_reposition_fire[];
extern s16 rooftop_supermech_m12_final_boss_default_reposition_rest[];
extern s16 rooftop_supermech_m12_final_boss_default_scroll_pick[];
extern s16 rooftop_supermech_m12_final_boss_random_move_pick[];
extern s16 rooftop_supermech_m12_final_boss_default_random_scroll_pick[];
extern s16 rooftop_supermech_m12_final_boss_default_random_charge_pick[];
extern s16 rooftop_supermech_m12_final_boss_default_random_return[];
extern s16 rooftop_supermech_m12_final_boss_low_health_near_pick[];
extern s16 rooftop_supermech_m12_final_boss_near_charge_pick[];
extern s16 rooftop_supermech_m12_final_boss_near_aligned_roll[];
extern s16 rooftop_supermech_m12_final_boss_near_scroll_turn[];
extern s16 rooftop_supermech_m12_final_boss_aim_pick[];
extern s16 rooftop_supermech_m12_final_boss_near_aligned_scroll[];
extern s16 rooftop_supermech_m12_final_boss_near_pick_return[];
extern s16 rooftop_supermech_m12_final_boss_close_pick[];
extern s16 rooftop_supermech_m12_final_boss_close_range_charge_pick[];
extern s16 rooftop_supermech_m12_final_boss_close_range_retreat_pick[];
extern s16 rooftop_supermech_m12_final_boss_close_range_rest[];
extern s16 rooftop_supermech_m12_final_boss_scroll_close_pick[];
extern s16 rooftop_supermech_m12_final_boss_close_attack_pick_return[];
extern s16 rooftop_supermech_m12_final_boss_mid_pick[];
extern s16 rooftop_supermech_m12_final_boss_far_range_aligned_pick[];
extern s16 rooftop_supermech_m12_final_boss_far_range_spread_pick[];
extern s16 rooftop_supermech_m12_final_boss_far_range_fire_pick[];
extern s16 rooftop_supermech_m12_final_boss_mid_fire_aligned_check[];
extern s16 rooftop_supermech_m12_final_boss_mid_pick_return[];
extern s16 rooftop_supermech_m12_final_boss_far_pick[];
extern s16 rooftop_supermech_m12_final_boss_far_roll_pick[];
extern s16 rooftop_supermech_m12_final_boss_far_roll_spread_turn[];
extern s16 rooftop_supermech_m12_final_boss_far_roll_charge_pick[];
extern s16 rooftop_supermech_m12_final_boss_far_roll_return[];
extern s16 rooftop_supermech_m12_final_boss_mid_range_roll_pick[];
extern s16 rooftop_supermech_m12_final_boss_roll_idle[];
extern s16 rooftop_supermech_m12_final_boss_roll_fire[];
extern s16 rooftop_supermech_m12_final_boss_roll_rest[];
extern s16 rooftop_supermech_m12_final_boss_roll_scroll_pick[];
extern s16 rooftop_supermech_m12_final_boss_roll_random_retreat[];
extern s16 rooftop_supermech_m12_final_boss_roll_random_scroll_pick[];
extern s16 rooftop_supermech_m12_final_boss_roll_random_charge_pick[];
extern s16 rooftop_supermech_m12_final_boss_roll_random_return[];
extern s16 rooftop_supermech_m12_final_boss_near_pick[];
extern s16 rooftop_supermech_m12_final_boss_near_select_charge_pick[];
extern s16 rooftop_supermech_m12_final_boss_near_scroll_entry[];
extern s16 rooftop_supermech_m12_final_boss_near_random_scroll_pick[];
extern s16 rooftop_supermech_m12_final_boss_near_aim_pick[];
extern s16 rooftop_supermech_m12_final_boss_low_health_rest[];
extern s16 rooftop_supermech_m12_final_boss_near_select_return[];
extern s16 rooftop_supermech_m12_final_boss_intro_continue[];
extern s16 rooftop_supermech_m12_final_boss_health_tier_select[];
extern s16 rooftop_supermech_m12_final_boss_health_tier_flag[];
extern s16 rooftop_supermech_m12_final_boss_flag_select_return[];
extern s16 rooftop_supermech_m12_final_boss_attack_select[];
extern s16 rooftop_supermech_m12_final_boss_attack_select_low_health[];
extern s16 *supermech_script_data[206];
extern s16 *D_80121598;
extern StateEntry D_8012159C[21];
extern s16 hit_mask_values[];
extern s16 particle_cursor_a[10];
extern s16 particle_cursor_b[10];
extern s16 particle_cursor_c[10];
extern s32 D_80121690;
extern RecTemplate fade_red_fx_template;
extern RecTemplate blast_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern s16 spark_trail_template[10];
extern s16 spark_particle_template[6];
extern s16 fx_entry_keyframes[];
extern s16 view_nudge_table[];
extern SVECTOR fade_target_color;
extern SVECTOR D_8012174C;
extern SVECTOR D_80121754;
extern BlendVec D_8012175C[];
extern BlendVec D_80121B5C[];
extern s16 D_80121F5C[];
extern s16 D_8012235C[];
extern s16 D_8012275C[];
extern s16 D_80122B5C[];
extern s16 D_80122F5C[];
extern s16 D_8012335C[];
extern BlendVec blend_vec_null;
extern BlendVec blend_base_null;
extern BlendVec *pose_blend_table[];
extern s16 *pose_from_table[];
extern s16 *pose_to_table[];
extern u32 D_801237B4[];
extern s32 burst_particle_template[5];
extern s16 shot_offset_table[24];
extern u32 shot_rot_default[];
extern ScriptCallEntry D_8012380C[9];
extern s16 supermech_m12_boss_start[];
extern s16 supermech_m12_boss_cycle[];
extern s16 supermech_m12_boss_fire_start[];
extern s16 supermech_m12_boss_fire_windup[];
extern s16 supermech_m12_boss_fire_loop[];
extern s16 *D_80123884[5];
extern s16 supermech_m12_boss_anim_idle[];
extern s16 *supermech_m12_script[];
extern s16 *D_801238A4;
extern StateEntry D_801238A8[1];
extern s16 D_801238B0[];
extern FxOffset cam_track_offs[2];
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *D_80123940[];
extern ScanEntry enemy_msgs_scan_entry;
extern s32 boss_slot_index[3];
extern ScanEntry D_80123970;
extern s32 D_80123988[21];
extern s32 D_801239DC[5];
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern u16 ratan_tbl[];
extern s16 video_mode_id;
extern s16 debug_cam_speed_table[][2];
extern s32 pause_prev_work_area;
extern s32 vblank_task_handle;
extern u32 D_80128394[];
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_80128DB4[];
extern u16 d_8011D324[];
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
extern u32 D_80129EF8[];
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
extern u32 D_8012A518;
extern u16 texture_image[];
extern u16 stage_image_width;
extern u16 stage_image_height;
extern u32 stage_image_pixels[];
extern s32 heap_top;
extern s32 heap2_top;
extern s32 prox_blend_base;
extern s32 cam_trigger_inside;
extern s32 loop_sound_id;
extern s32 trail_write_index;
extern s32 supermech_trail_count;
extern s32 sound_pair_active;
extern s32 sound_fade_out_flag;
extern s32 sound_pair_a_handle;
extern s32 sound_pair_b_handle;
extern u32 D_8012B954;
extern s32 sound_pair_volume;
extern s32 sound_pair_volume_step;
extern s32 value_queue_index;
extern s16 shot_aim_a_pitch;
extern s16 shot_aim_a_yaw;
extern s16 shot_aim_a_roll;
extern s16 shot_aim_b_pitch;
extern s16 shot_aim_b_yaw;
extern s16 shot_aim_b_roll;
extern s32 obj_loop_sound_id;
extern s32 supermech_trail_parity;
extern s32 bounds_x_min;
extern s32 bounds_x_max;
extern s32 bounds_z_min;
extern s32 bounds_z_max;
extern s32 stage_active_flag;
extern s32 particle_spawn_param;
extern ObjectMode *fade_target_obj;
extern s32 spark_serial;
extern s32 boss_state;
extern s32 obj_loop_sound_handle;
extern s32 owner_sound_handles[2];
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
extern s32 D_8012B9F0;
extern s32 fly_active_flag;
extern s32 scene_active_flag;
extern s32 fall_height;
extern s32 fall_sound_timer;
extern s16 fly_target_pos;
extern s16 D_8012BA06;
extern s16 D_8012BA08;
extern s32 fly_cam_speed;
extern u32 fly_target_rot[];
extern s32 area_load_flag;
extern u32 D_8012BA1C;
extern s32 alarm_sound_handle;
extern s32 alarm_armed_flag;
extern s32 alarm2_sound_handle;
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
extern u32 D_8012BAE0;
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
extern u32 D_8012BB7C;
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
extern s32 scene_rot_data[2];
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
extern u32 D_8012BFFC;

s32 area = 0x21;

ScanItem area_stage_items[9] = {
    {&helicopter_scan_entry, str_enemy_ohel_data},
    {&gun_turret_scan_entry, str_enemy_hou1_data},
    {&arkb_scan_entry, str_enemy_arkb_data},
    {&msub_scan_entry, str_enemy_msub_data},
    {&jira_load_step, str_enemy_jira_data},
    {&bal2_scan_entry, str_enemy_bal2_data},
    {&dorc_load_step, str_enemy_dorc_data},
    {&ctlc_load_step, str_enemy_ctlc_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry area_stage_record = {str_s12_stage, str_hgh_cnf_bcf, str_hgh_apdea3, str_hgh_joy_bin, str_s12_dat_fac, str_s12_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, area_stage_items};

AreaEntry area_miss_record = {str_s12_miss, str_m43_cnf_bcf, NULL, str_m43_joy_bin, str_m12_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

ScanItem area_boss_items[4] = {
    {&supermech_scan_entry, str_enemy_bosc_data},
    {&enemy_msgs_scan_entry, str_enemy_msgs_data},
    {&D_80123970, str_enemy_cbsc_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry area_boss_entry = {str_s12_boss, str_lst_cnf_bcf, str_hpt_apdea3, str_hpt_joy_bin, str_b12_dat_fac, str_b12_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, area_boss_items};

AreaEntry *area_entry_table[3] = {
    &area_miss_record, &area_stage_record, &area_boss_entry,
};

#include "../stage/data/debug_name_buf.c"

#include "../stage/data/helicopter_asset_slot.c"

#include "../stage/data/d_801176C4.c"

#include "../stage/data/helicopter_scan_entry.c"

#include "../stage/data/shot_twin_desc.c"

#include "../stage/data/fx_send_rec34_params_b.c"

#include "../stage/data/helicopter_scripts.c"

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

#include "../stage/data/timer_tail_data.c"

ModelBlockRef bal2_palettes[3] = {
    {(s32)file_bal2_ch0_clt, 0, 0},
    {(s32)file_bal2_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef bal2_textures[2] = {
    {(s32)file_bal2_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011F4E0[2] = {
    {(s32)file_bal2_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011F4F0[2] = {
    {1, 1, 0x400, 0}, {-1, 0, 0, 0},
};

s16 D_8011F500[4] = {
    1, 0x100, 0x11F, 0,
};

ModelBlock bal2_model_block = {(s32)bal2_palettes, (s32)D_8011F4E0, (s32)bal2_textures, 0, 0, 0, (s32)D_8011F4F0, (s32)D_8011F500, 0};

u8 *D_8011F52C[2] = {
    file_bal2_ch0_cb4, NULL,
};

ScanEntry bal2_scan_entry = {{(s32)loop_sound_fade_in, (s32)timer_tail_spawn}, (s32 *)&timer_tail_data, (s32)&bal2_model_block, (s32)D_8011F52C, 0};

StateEntry timer_tail_states[1] = {
    {0, 0, 0},
};

struct TimerTailAnims {
    s16 script[4];
    s16 *table[1];
} timer_tail_anims = {
    /* script */ {
        STEP(1, 1),
        GOTO(TIMER_TAIL_SCRIPT),
    },
    /* table */ {
        timer_tail_anims.script,
    },
};

#include "../stage/data/loop_sound_fade_handle.c"

#include "../stage/data/d_8011B7AC.c"

#include "../stage/data/smg_soldier_asset.c"

#include "../stage/data/msub_palettes.c"

#include "../stage/data/msub_textures.c"

#include "../stage/data/rocket_fuchikoma_fire_start.c"

#include "../stage/data/model_scale_ranges.c"

#include "../stage/data/model_link_ranges.c"

#include "../stage/data/msub_model_block.c"

u8 *msub_file_table[2] = {
    file_msub_ch0_cb4, NULL,
};

#include "../stage/data/msub_scan_entry.c"

SoundVolume smg_soldier_sounds[1] = {
    {SND_GROUND_IMPACT | SND_GROUP(2), 0x1000},
};

struct SmgSoldierAnims {
    s16 idle[6];
    s16 idle_alt[32];
    s16 walk_start[30];
    s16 walk[28];
    s16 run_start[36];
    s16 run[26];
    s16 aim[70];
    s16 hold[8];
    s16 hit[22];
    s16 *table[9];
} smg_soldier_anims = {
    /* idle */ {
        STEP(20, 4),
        FLY(0),
        GOTO(SMG_SOLDIER_ANIM_IDLE),
    },
    /* idle_alt */ {
        STEP(40, 4),
        STEP(40, 98),
        STEP(20, 97),
        STEP(20, 97),
        STEP(20, 97),
        STEP(40, 98),
        STEP(40, 4),
        STEP(20, 4),
        STEP(20, 4),
        STEP(40, 98),
        STEP(20, 98),
        STEP(20, 97),
        STEP(20, 97),
        STEP(40, 98),
        STEP(40, 4),
        GOTO(SMG_SOLDIER_ANIM_IDLE_ALT),
    },
    /* walk_start */ {
        STEP(6, 4),
        FLY(1),
        STEP(6, 5),
        FLY(3),
        STEP(6, 6),
        SOUND(0),
        FLY(4),
        STEP(6, 7),
        STEP(6, 8),
        STEP(6, 9),
        STEP(6, 10),
        SOUND(0),
        STEP(6, 2),
        STEP(6, 3),
        GOTO(SMG_SOLDIER_ANIM_WALK),
    },
    /* walk */ {
        STEP(6, 4),
        FLY(4),
        STEP(6, 5),
        STEP(6, 6),
        SOUND(0),
        STEP(6, 7),
        STEP(6, 8),
        STEP(6, 9),
        STEP(6, 10),
        SOUND(0),
        STEP(6, 1),
        STEP(6, 2),
        STEP(6, 3),
        GOTO(SMG_SOLDIER_ANIM_WALK),
    },
    /* run_start */ {
        STEP(6, 4),
        STEP(3, 15),
        FLY(1),
        STEP(3, 16),
        FLY(6),
        STEP(3, 17),
        SOUND(0),
        STEP(3, 18),
        FLY(6),
        STEP(3, 19),
        STEP(3, 20),
        FLY(9),
        STEP(3, 21),
        STEP(3, 12),
        SOUND(0),
        STEP(3, 13),
        STEP(3, 14),
        GOTO(SMG_SOLDIER_ANIM_RUN),
    },
    /* run */ {
        STEP(3, 15),
        STEP(3, 16),
        STEP(3, 17),
        SOUND(0),
        STEP(3, 18),
        STEP(3, 19),
        STEP(3, 20),
        STEP(3, 21),
        STEP(3, 12),
        SOUND(0),
        STEP(3, 13),
        STEP(3, 14),
        GOTO(SMG_SOLDIER_ANIM_RUN),
    },
    /* aim */ {
        FLY(0),
        STEP(8, 90),
        STEP(8, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 90),
        STEP(2, 89),
        GOTO(SMG_SOLDIER_ANIM_AIM),
    },
    /* hold */ {
        FLY(2),
        FLY(0),
        STEP(14, 92),
        GOTO(SMG_SOLDIER_ANIM_HOLD),
    },
    /* hit */ {
        STEP(12, 75),
        STEP(4, 77),
        STEP(4, 78),
        STEP(4, 79),
        STEP(4, 80),
        STEP(4, 81),
        STEP(4, 83),
        STEP(4, 85),
        STEP(4, 86),
        STEP(10, 87),
        GOTO(SMG_SOLDIER_ANIM_HIT),
    },
    /* table */ {
        smg_soldier_anims.idle, smg_soldier_anims.idle_alt, smg_soldier_anims.walk_start, smg_soldier_anims.walk, smg_soldier_anims.run_start, smg_soldier_anims.run,
        smg_soldier_anims.aim, smg_soldier_anims.hold, smg_soldier_anims.hit,
    },
};

struct SmgSoldierScripts {
    s16 idle[6];
    s16 idle_pause[4];
    s16 idle_cycle_alt[10];
    s16 patrol[6];
    s16 wander_start[12];
    s16 wander_hold[6];
    s16 hold[4];
    s16 hold_pause[4];
    s16 hold_cycle_alt[10];
    s16 walk[4];
    s16 walk_step[4];
    s16 walk_cycle_alt[10];
    s16 walk_pause[4];
    s16 walk_pause_cycle_alt[10];
    s16 *table[14];
    s16 *script[5];
} smg_soldier_scripts = {
    /* idle */ {
        JUMP_RANDOM(3072, SMG_SOLDIER_PATROL),
        SET_COUNTER_RANDOM(3, 1),
    },
    /* idle_pause */ {
        WAIT(8),
        NEXT_STATE(SMG_SOLDIER_STATE_WAIT),
    },
    /* idle_cycle_alt */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_IDLE_CYCLE_ALT),
        LOOP(SMG_SOLDIER_IDLE_PAUSE),
        JUMP(SMG_SOLDIER_IDLE),
    },
    /* patrol */ {
        WAIT(1),
        WANDER(1),
        NEXT_STATE(SMG_SOLDIER_STATE_PATROL),
    },
    /* wander_start */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_WANDER_START),
        SET_SPEED(0),
        WANDER(1),
        SET_COUNTER_RANDOM(5, 3),
    },
    /* wander_hold */ {
        WAIT(1),
        LOOP(SMG_SOLDIER_WANDER_HOLD),
        JUMP(SMG_SOLDIER_IDLE),
    },
    /* hold */ {
        SET_COUNTER_RANDOM(3, 1),
    },
    /* hold_pause */ {
        WAIT(8),
        NEXT_STATE(SMG_SOLDIER_STATE_WAIT),
    },
    /* hold_cycle_alt */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_HOLD_CYCLE_ALT),
        LOOP(SMG_SOLDIER_HOLD_PAUSE),
        JUMP(SMG_SOLDIER_HOLD),
    },
    /* walk */ {
        SET_COUNTER_RANDOM(4, 1),
    },
    /* walk_step */ {
        WAIT(8),
        NEXT_STATE(SMG_SOLDIER_STATE_PATROL),
    },
    /* walk_cycle_alt */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_WALK_CYCLE_ALT),
        LOOP(SMG_SOLDIER_WALK_STEP),
        JUMP(SMG_SOLDIER_WALK),
    },
    /* walk_pause */ {
        WAIT(8),
        NEXT_STATE(SMG_SOLDIER_STATE_WAIT),
    },
    /* walk_pause_cycle_alt */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_WALK_PAUSE_CYCLE_ALT),
        LOOP(SMG_SOLDIER_WALK_PAUSE),
        JUMP(SMG_SOLDIER_WALK),
    },
    /* table */ {
        smg_soldier_scripts.idle, smg_soldier_scripts.idle_pause, smg_soldier_scripts.idle_cycle_alt, smg_soldier_scripts.patrol, smg_soldier_scripts.wander_start, smg_soldier_scripts.wander_hold,
        smg_soldier_scripts.hold, smg_soldier_scripts.hold_pause, smg_soldier_scripts.hold_cycle_alt, smg_soldier_scripts.walk, smg_soldier_scripts.walk_step, smg_soldier_scripts.walk_cycle_alt,
        smg_soldier_scripts.walk_pause, smg_soldier_scripts.walk_pause_cycle_alt,
    },
    /* script */ {
        smg_soldier_scripts.idle, smg_soldier_scripts.hold, smg_soldier_scripts.walk, smg_soldier_scripts.hold, smg_soldier_scripts.walk,
    },
};

StateEntry smg_soldier_states[9] = {
    {0, SMG_SOLDIER_ANIM_IDLE, 0},
    {(u32)enemy_wait_switch, SMG_SOLDIER_ANIM_IDLE_ALT, 0},
    {(u32)enemy_move_or_wait, SMG_SOLDIER_ANIM_WALK_START, 0},
    {(u32)enemy_walk_step, SMG_SOLDIER_ANIM_RUN_START, 0},
    {(u32)flyer_wander, SMG_SOLDIER_ANIM_RUN_START, 0},
    {(u32)enemy_shoot_update, SMG_SOLDIER_ANIM_AIM, 0},
    {(u32)flyer_retreat, SMG_SOLDIER_ANIM_WALK, 0},
    {(u32)enemy_shoot_update, SMG_SOLDIER_ANIM_HOLD, 0},
    {0, SMG_SOLDIER_ANIM_HIT, 0},
};

#include "../stage/data/proximity_asset.c"

ModelBlockRef D_8011F9B4[3] = {
    {(s32)file_jira_ch0_clt, 0, 0},
    {(s32)file_jira_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011F9CC[2] = {
    {(s32)file_jira_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011F9DC[2] = {
    {(s32)file_jira_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011F9EC[2] = {
    {1, 1, 0x800, 0}, {-1, 0, 0, 0},
};

ModelBlock jira_model_block = {(s32)D_8011F9B4, (s32)D_8011F9DC, (s32)D_8011F9CC, 0, 0, 0, (s32)D_8011F9EC, 0, 0};

u8 *jira_stage_files[2] = {
    file_jira_ch0_cb4, NULL,
};

#include "../stage/data/jira_load_step.c"

#include "../stage/data/placed_actor_states.c"

#include "../stage/data/placed_actor_anims.c"

u8 *dorc_stage_files[2] = {
    file_dorc_ch0_cb4, NULL,
};

s32 D_8011FA5C = -1;

s32 prox_origin[2] = {
    -1, -1,
};

ScanEntry dorc_load_step = {{(s32)proximity_flags_reset, (s32)proximity_sensor_spawn}, &D_8011FA5C, 0, (s32)dorc_stage_files, 0};

u16 prox_cells[60] = {
    0x00F5, 0x00F6, 0x0005, 0x0004, 0x0000, 0x0180, 0x03E8, 0x03E8,
    0x0071, 0x0000, 0x00F7, 0x00F8, 0x0007, 0x0006, 0x0000, 0xFE80,
    0x03E8, 0x03E8, 0x0071, 0x0000, 0x00E9, 0x00EA, 0x0001, 0x0000,
    0x0000, 0x0180, 0x03E8, 0x03E8, 0xFFFF, 0x0000, 0x00EB, 0x00EC,
    0x0003, 0x0002, 0x0000, 0xFE80, 0x03E8, 0x03E8, 0xFFFF, 0x0000,
    0x00FC, 0x00FD, 0x0009, 0x0008, 0x0180, 0x0000, 0x03E8, 0x04B0,
    0x0070, 0x0000, 0x00FE, 0x00FF, 0x000B, 0x000A, 0xFE80, 0x0000,
    0x03E8, 0x04B0, 0x0070, 0x0000,
};

s32 D_8011FAF8[3] = {
    -1, -1, -1,
};

ScanEntry ctlc_load_step = {{(s32)rec_clear_flags_list, (s32)cam_path_obj_spawn}, D_8011FAF8, 0, 0, 0};

s32 cam_trigger_min_x = -0x79E0;

s32 cam_trigger_max_x = -0x7530;

s32 cam_trigger_min_y = -0xDAC;

s32 cam_trigger_max_y = -0xBB8;

s32 cam_trigger_min_z = -0x42CC;

s32 cam_trigger_max_z = -0x3E1C;

BoundsBox cam_boxes[2] = {
    {-0x1C80, 0x1F80, -0x1380, 0x7FFF, -0x3780, 0x3780},
    {-0x4C80, 0x1F80, -0x900, 0x7FFF, -0x7140, -0x2280},
};

s32 rec_clear_ids[7] = {
    0x18, 0x19, 5, 6, 0x30, 0x31,
    -1,
};

s32 anim_obj_data[5] = {
    1, -0x35C, -0x1710, 0x1BDC, 0,
};

PathPoint cam_path_data[11] = {
    {0x180, -0x1680, -0x39FF, 0},
    {0x180, -0x1200, -0x4D7A, 0},
    {-0xC5C, -0x10B6, -0x5580, 0},
    {-0x167F, -0xF00, -0x4E0C, 0},
    {-0x1A01, -0xD68, -0x4E0C, 0},
    {-0x2761, -0xD68, -0x4E0C, 0},
    {-0x2E6E, -0xF60, -0x407D, 0},
    {-0x524E, -0xF60, -0x407D, 0},
    {-0x524E, -0xB40, -0x407D, 0},
    {-0x5F9F, -0xC60, -0x407D, 0},
    {-0x7D00, -0xC00, -0x407D, 0},
};

SoundVolume D_8011FC44[8] = {
    {0x5160, 0x1000},
    {0x3167, 0x1000},
    {0x3169, 0x1000},
    {0x516D, 0x1000},
    {0x31763177, 0x1000},
    {0x5170, 0x1000},
    {SND_WHISTLE | SND_GROUP(2), 0x1000},
    {SND_SMALL_EXPLOSION | SND_GROUP(1), 0x1000},
};

s32 supermech_model_id[3] = {
    -1, -1, -1,
};

ModelBlockRef bosc_palette_refs[4] = {
    {(s32)file_bosc_ch0_clt, 0, 0},
    {(s32)file_bosc_tp0_clt, 0, 0},
    {(s32)file_bosc_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef bosc_texture_refs[3] = {
    {(s32)file_bosc_tp0_xs3, 1, 0},
    {(s32)file_bosc_tp1_xs3, 2, 0},
    {0, 0, 0},
};

ModelBlockRef bosc_model_refs[6] = {
    {(s32)file_bosc_ch0_vx1, 0, 0},
    {(s32)file_bosc_ch1_vx1, 0, 0},
    {(s32)file_bosc_ch2_vx1, 0, 0},
    {(s32)file_bosc_ch3_vx1, 0, 0},
    {(s32)file_bosc_ch4_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011FCF8[8] = {
    {0x208, 0x20B, 0x2000, 0}, {0x214, 0x214, 0x2000, 0}, {0x218, 0x21A, 0x2000, 0}, {0x220, 0x223, 0x2000, 0},
    {0x228, 0x22A, 0x2000, 0}, {0x234, 0x235, 0x2000, 0}, {0x258, 0x25A, 0x2000, 0}, {-1, -1, -1, 0},
};

ModelBlockRange D_8011FD38[2] = {
    {0, 0x1FF, 0x1800, 0}, {-1, -1, -1, 0},
};

ModelBlockRange D_8011FD48[4] = {
    {2, 2, 0x400, 0}, {0x200, 0x201, 0x400, 0}, {0x258, 0x25A, -0x2000, 0}, {-1, -1, -1, 0},
};

ModelBlock bosc_model_block = {(s32)bosc_palette_refs, (s32)bosc_model_refs, (s32)bosc_texture_refs, 0, (s32)D_8011FCF8, (s32)D_8011FD48, (s32)D_8011FD38, 0, 0};

u8 *bosc_stage_files[5] = {
    file_bosc_ch0_cb4, file_bosc_ch1_cb4, file_bosc_ch2_cb4, file_bosc_ch3_cb4, NULL,
};

ScanEntry supermech_scan_entry = {{(s32)player_status_reload, (s32)supermech_spawn}, supermech_model_id, (s32)&bosc_model_block, (s32)bosc_stage_files, 0};

struct RooftopSupermechM12FinalBossAnims {
    s16 idle[4];
    s16 walk_loop[38];
    s16 walk_start[6];
    s16 walk_lead_in[26];
    s16 halt[16];
    s16 halt_settle[4];
    s16 turn_start[20];
    s16 charge_slow[16];
    s16 charge_hold[4];
    s16 recover_enter[4];
    ScriptStep recover_hold[2];
    ScriptStep turn_recover[17];
    s16 fire_burst[38];
    s16 fire_burst_hold[6];
    s16 fire_burst_end[14];
    s16 spread_attack[28];
    s16 spread_attack_end[14];
    s16 spread_attack_second[28];
    s16 spread_attack_second_end[14];
    s16 charge_alt_start[32];
    s16 charge_alt_continue[28];
    s16 charge_second_alt_start[32];
    s16 charge_second_alt_end[30];
    s16 charge[32];
    s16 charge_end[30];
    s16 charge_second[32];
    s16 charge_second_end[30];
    s16 aim_attack[22];
    s16 aim_hold[6];
    s16 aim_recover[24];
    s16 aim_attack_second[22];
    s16 aim_second_hold[6];
    s16 aim_second_recover[24];
    s16 scroll_attack[14];
    s16 scroll_attack_mid[24];
    s16 scroll_attack_late[20];
    s16 scroll_attack_end[28];
    s16 scroll_second_start[14];
    s16 scroll_second_mid[24];
    s16 scroll_second_late[20];
    s16 scroll_second_end[28];
    s16 turn_long_start[38];
    s16 turn_long_hold[4];
    s16 turn_long_recover[30];
    s16 *table[44];
} rooftop_supermech_m12_final_boss_anims = {
    /* idle */ {
        STEP(2, 1),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* walk_loop */ {
        STEP(2, 8),
        SOUND(0),
        STEP(2, 9),
        STEP(2, 10),
        STEP(2, 11),
        STEP(2, 12),
        STEP(2, 13),
        STEP(2, 14),
        STEP(2, 15),
        STEP(2, 16),
        SOUND(0),
        STEP(2, 17),
        STEP(2, 18),
        STEP(2, 19),
        STEP(2, 20),
        STEP(2, 21),
        STEP(2, 22),
        STEP(2, 23),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_WALK_LOOP),
    },
    /* walk_start */ {
        STEP(12, 1),
        STEP(12, 13),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_WALK_LEAD_IN),
    },
    /* walk_lead_in */ {
        STEP(2, 13),
        STEP(2, 14),
        STEP(2, 15),
        STEP(2, 16),
        SOUND(0),
        STEP(2, 17),
        STEP(2, 18),
        STEP(2, 19),
        STEP(2, 20),
        STEP(2, 21),
        STEP(2, 22),
        STEP(2, 23),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_WALK_LOOP),
    },
    /* halt */ {
        STEP(2, 8),
        SOUND(0),
        STEP(2, 9),
        STEP(2, 10),
        STEP(2, 11),
        STEP(2, 12),
        STEP(2, 13),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_HALT_SETTLE),
    },
    /* halt_settle */ {
        STEP(16, 1),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* turn_start */ {
        STEP(2, 24),
        STEP(2, 25),
        STEP(2, 26),
        STEP(2, 27),
        STEP(2, 28),
        STEP(2, 29),
        STEP(2, 30),
        STEP(2, 31),
        STEP(2, 32),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_SLOW),
    },
    /* charge_slow */ {
        STEP(2, 33),
        STEP(2, 34),
        STEP(2, 35),
        STEP(2, 36),
        STEP(2, 37),
        STEP(2, 38),
        STEP(2, 39),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_HOLD),
    },
    /* charge_hold */ {
        STEP(2, 39),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_HOLD),
    },
    /* recover_enter */ {
        STEP(2, 40),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_RECOVER_HOLD),
    },
    /* recover_hold */ {
        {2, 0x28}, {-1, 10},
    },
    /* turn_recover */ {
        {2, 0x28}, {2, 0x29}, {2, 0x2A}, {2, 0x2B}, {2, 0x2C}, {2, 0x2D}, {2, 0x2E}, {2, 0x2F}, {2, 0x30}, {2, 0x31},
        {2, 0x32}, {2, 0x33}, {2, 0x34}, {2, 0x35}, {2, 0x36}, {2, 0x37}, {-1, 0},
    },
    /* fire_burst */ {
        STEP(2, 56),
        STEP(2, 57),
        STEP(2, 58),
        STEP(2, 59),
        STEP(2, 60),
        STEP(2, 61),
        STEP(2, 62),
        STEP(2, 63),
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
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_FIRE_BURST_HOLD),
    },
    /* fire_burst_hold */ {
        STEP(4, 74),
        STEP(4, 73),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_FIRE_BURST_HOLD),
    },
    /* fire_burst_end */ {
        STEP(2, 75),
        STEP(2, 76),
        STEP(2, 77),
        STEP(2, 78),
        STEP(2, 79),
        STEP(2, 80),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* spread_attack */ {
        STEP(2, 88),
        STEP(2, 89),
        STEP(2, 90),
        STEP(2, 91),
        STEP(2, 92),
        STEP(2, 93),
        STEP(2, 94),
        STEP(2, 95),
        STEP(2, 95),
        STEP(2, 96),
        STEP(2, 97),
        STEP(2, 98),
        STEP(2, 99),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SPREAD_ATTACK_END),
    },
    /* spread_attack_end */ {
        STEP(2, 100),
        STEP(2, 101),
        STEP(2, 102),
        STEP(2, 103),
        STEP(2, 104),
        STEP(2, 105),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* spread_attack_second */ {
        STEP(2, 110),
        STEP(2, 111),
        STEP(2, 112),
        STEP(2, 113),
        STEP(2, 114),
        STEP(2, 115),
        STEP(2, 116),
        STEP(2, 117),
        STEP(2, 117),
        STEP(2, 118),
        STEP(2, 119),
        STEP(2, 120),
        STEP(2, 121),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SPREAD_ATTACK_SECOND_END),
    },
    /* spread_attack_second_end */ {
        STEP(2, 122),
        STEP(2, 123),
        STEP(2, 124),
        STEP(2, 125),
        STEP(2, 126),
        STEP(2, 127),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* charge_alt_start */ {
        STEP(5, 257),
        SOUND(1),
        STEP(5, 258),
        STEP(5, 259),
        STEP(5, 260),
        STEP(5, 261),
        STEP(5, 262),
        STEP(5, 263),
        STEP(5, 264),
        STEP(5, 264),
        STEP(5, 264),
        STEP(1, 265),
        STEP(1, 266),
        STEP(1, 267),
        STEP(1, 268),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_ALT_CONTINUE),
    },
    /* charge_alt_continue */ {
        STEP(1, 269),
        STEP(1, 270),
        STEP(1, 271),
        STEP(1, 272),
        STEP(1, 273),
        STEP(1, 274),
        STEP(1, 275),
        STEP(1, 276),
        STEP(1, 277),
        STEP(1, 278),
        STEP(3, 279),
        STEP(3, 280),
        STEP(3, 281),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* charge_second_alt_start */ {
        STEP(5, 288),
        SOUND(1),
        STEP(5, 289),
        STEP(5, 290),
        STEP(5, 291),
        STEP(5, 292),
        STEP(5, 293),
        STEP(5, 294),
        STEP(5, 295),
        STEP(5, 295),
        STEP(5, 295),
        STEP(1, 296),
        STEP(1, 297),
        STEP(1, 298),
        STEP(1, 299),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_SECOND_ALT_END),
    },
    /* charge_second_alt_end */ {
        SOUND(2),
        STEP(1, 300),
        STEP(1, 301),
        STEP(1, 302),
        STEP(1, 303),
        STEP(1, 304),
        STEP(1, 305),
        STEP(1, 306),
        STEP(1, 307),
        STEP(1, 308),
        STEP(1, 309),
        STEP(3, 310),
        STEP(3, 311),
        STEP(3, 312),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* charge */ {
        STEP(3, 257),
        SOUND(1),
        STEP(3, 258),
        STEP(3, 259),
        STEP(3, 260),
        STEP(3, 261),
        STEP(3, 262),
        STEP(3, 263),
        STEP(3, 264),
        STEP(3, 264),
        STEP(3, 264),
        STEP(1, 265),
        STEP(1, 266),
        STEP(1, 267),
        STEP(1, 268),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_END),
    },
    /* charge_end */ {
        SOUND(2),
        STEP(1, 269),
        STEP(1, 270),
        STEP(1, 271),
        STEP(1, 272),
        STEP(1, 273),
        STEP(1, 274),
        STEP(1, 275),
        STEP(1, 276),
        STEP(1, 277),
        STEP(1, 278),
        STEP(3, 279),
        STEP(3, 280),
        STEP(3, 281),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* charge_second */ {
        STEP(3, 288),
        SOUND(1),
        STEP(3, 289),
        STEP(3, 290),
        STEP(3, 291),
        STEP(3, 292),
        STEP(3, 293),
        STEP(3, 294),
        STEP(3, 295),
        STEP(3, 295),
        STEP(3, 295),
        STEP(1, 296),
        STEP(1, 297),
        STEP(1, 298),
        STEP(1, 299),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_SECOND_END),
    },
    /* charge_second_end */ {
        SOUND(2),
        STEP(1, 300),
        STEP(1, 301),
        STEP(1, 302),
        STEP(1, 303),
        STEP(1, 304),
        STEP(1, 305),
        STEP(1, 306),
        STEP(1, 307),
        STEP(1, 308),
        STEP(1, 309),
        STEP(3, 310),
        STEP(3, 311),
        STEP(3, 312),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* aim_attack */ {
        STEP(2, 320),
        STEP(2, 321),
        STEP(2, 322),
        STEP(2, 323),
        STEP(2, 324),
        STEP(2, 325),
        STEP(2, 326),
        STEP(2, 327),
        STEP(2, 328),
        STEP(2, 329),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_AIM_HOLD),
    },
    /* aim_hold */ {
        STEP(2, 339),
        STEP(2, 329),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_AIM_HOLD),
    },
    /* aim_recover */ {
        STEP(2, 339),
        STEP(2, 340),
        STEP(2, 341),
        STEP(2, 342),
        STEP(2, 343),
        STEP(2, 344),
        STEP(2, 345),
        STEP(2, 346),
        STEP(2, 347),
        STEP(2, 348),
        STEP(2, 349),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* aim_attack_second */ {
        STEP(2, 352),
        STEP(2, 353),
        STEP(2, 354),
        STEP(2, 355),
        STEP(2, 356),
        STEP(2, 357),
        STEP(2, 358),
        STEP(2, 359),
        STEP(2, 360),
        STEP(2, 361),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_AIM_SECOND_HOLD),
    },
    /* aim_second_hold */ {
        STEP(2, 371),
        STEP(2, 361),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_AIM_SECOND_HOLD),
    },
    /* aim_second_recover */ {
        STEP(2, 371),
        STEP(2, 372),
        STEP(2, 373),
        STEP(2, 374),
        STEP(2, 375),
        STEP(2, 376),
        STEP(2, 377),
        STEP(2, 378),
        STEP(2, 379),
        STEP(2, 380),
        STEP(2, 381),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* scroll_attack */ {
        STEP(2, 400),
        SOUND(3),
        STEP(2, 401),
        STEP(2, 402),
        STEP(2, 403),
        STEP(2, 404),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SCROLL_ATTACK_MID),
    },
    /* scroll_attack_mid */ {
        STEP(2, 405),
        STEP(2, 406),
        STEP(2, 407),
        STEP(2, 408),
        STEP(2, 409),
        STEP(2, 410),
        STEP(2, 411),
        STEP(2, 412),
        STEP(2, 413),
        STEP(2, 414),
        STEP(16, 415),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SCROLL_ATTACK_LATE),
    },
    /* scroll_attack_late */ {
        SOUND(4),
        STEP(2, 416),
        STEP(2, 417),
        STEP(2, 418),
        STEP(2, 419),
        STEP(2, 420),
        STEP(2, 421),
        STEP(2, 422),
        STEP(2, 423),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SCROLL_ATTACK_END),
    },
    /* scroll_attack_end */ {
        STEP(2, 423),
        SOUND(5),
        STEP(2, 424),
        STEP(2, 425),
        STEP(2, 426),
        STEP(2, 427),
        STEP(2, 428),
        STEP(2, 429),
        STEP(2, 430),
        STEP(2, 431),
        STEP(2, 432),
        STEP(2, 433),
        STEP(2, 434),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* scroll_second_start */ {
        STEP(2, 448),
        SOUND(3),
        STEP(2, 449),
        STEP(2, 450),
        STEP(2, 451),
        STEP(2, 452),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SCROLL_SECOND_MID),
    },
    /* scroll_second_mid */ {
        STEP(2, 453),
        STEP(2, 454),
        STEP(2, 455),
        STEP(2, 456),
        STEP(2, 457),
        STEP(2, 458),
        STEP(2, 459),
        STEP(2, 460),
        STEP(2, 461),
        STEP(2, 462),
        STEP(16, 463),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SCROLL_SECOND_LATE),
    },
    /* scroll_second_late */ {
        SOUND(4),
        STEP(2, 464),
        STEP(2, 465),
        STEP(2, 466),
        STEP(2, 467),
        STEP(2, 468),
        STEP(2, 469),
        STEP(2, 470),
        STEP(2, 471),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SCROLL_SECOND_END),
    },
    /* scroll_second_end */ {
        STEP(2, 471),
        SOUND(5),
        STEP(2, 472),
        STEP(2, 473),
        STEP(2, 474),
        STEP(2, 475),
        STEP(2, 476),
        STEP(2, 477),
        STEP(2, 478),
        STEP(2, 479),
        STEP(2, 480),
        STEP(2, 481),
        STEP(2, 482),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SCROLL_SECOND_START),
    },
    /* turn_long_start */ {
        STEP(2, 24),
        STEP(2, 25),
        STEP(2, 26),
        STEP(2, 27),
        STEP(2, 28),
        STEP(2, 29),
        STEP(2, 30),
        STEP(2, 31),
        STEP(2, 32),
        STEP(2, 33),
        STEP(2, 34),
        STEP(2, 35),
        STEP(2, 36),
        STEP(2, 37),
        STEP(2, 38),
        STEP(2, 39),
        STEP(2, 40),
        STEP(2, 41),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_TURN_LONG_RECOVER),
    },
    /* turn_long_hold */ {
        STEP(2, 33),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_TURN_LONG_HOLD),
    },
    /* turn_long_recover */ {
        STEP(2, 42),
        STEP(2, 43),
        STEP(2, 44),
        STEP(2, 45),
        STEP(2, 46),
        STEP(2, 47),
        STEP(2, 48),
        STEP(2, 49),
        STEP(2, 50),
        STEP(2, 51),
        STEP(2, 52),
        STEP(2, 53),
        STEP(2, 54),
        STEP(2, 55),
        GOTO(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE),
    },
    /* table */ {
        rooftop_supermech_m12_final_boss_anims.idle, rooftop_supermech_m12_final_boss_anims.walk_loop, rooftop_supermech_m12_final_boss_anims.walk_start, rooftop_supermech_m12_final_boss_anims.walk_lead_in, rooftop_supermech_m12_final_boss_anims.halt, rooftop_supermech_m12_final_boss_anims.halt_settle,
        rooftop_supermech_m12_final_boss_anims.turn_start, rooftop_supermech_m12_final_boss_anims.charge_slow, rooftop_supermech_m12_final_boss_anims.charge_hold, rooftop_supermech_m12_final_boss_anims.recover_enter, (s16 *)rooftop_supermech_m12_final_boss_anims.recover_hold, (s16 *)rooftop_supermech_m12_final_boss_anims.turn_recover,
        rooftop_supermech_m12_final_boss_anims.fire_burst, rooftop_supermech_m12_final_boss_anims.fire_burst_hold, rooftop_supermech_m12_final_boss_anims.fire_burst_end, rooftop_supermech_m12_final_boss_anims.spread_attack, rooftop_supermech_m12_final_boss_anims.spread_attack_end, rooftop_supermech_m12_final_boss_anims.spread_attack_second,
        rooftop_supermech_m12_final_boss_anims.spread_attack_second_end, rooftop_supermech_m12_final_boss_anims.charge_alt_start, rooftop_supermech_m12_final_boss_anims.charge_alt_continue, rooftop_supermech_m12_final_boss_anims.charge_second_alt_start, rooftop_supermech_m12_final_boss_anims.charge_second_alt_end, rooftop_supermech_m12_final_boss_anims.charge,
        rooftop_supermech_m12_final_boss_anims.charge_end, rooftop_supermech_m12_final_boss_anims.charge_second, rooftop_supermech_m12_final_boss_anims.charge_second_end, rooftop_supermech_m12_final_boss_anims.aim_attack, rooftop_supermech_m12_final_boss_anims.aim_hold, rooftop_supermech_m12_final_boss_anims.aim_recover,
        rooftop_supermech_m12_final_boss_anims.aim_attack_second, rooftop_supermech_m12_final_boss_anims.aim_second_hold, rooftop_supermech_m12_final_boss_anims.aim_second_recover, rooftop_supermech_m12_final_boss_anims.scroll_attack, rooftop_supermech_m12_final_boss_anims.scroll_attack_mid, rooftop_supermech_m12_final_boss_anims.scroll_attack_late,
        rooftop_supermech_m12_final_boss_anims.scroll_attack_end, rooftop_supermech_m12_final_boss_anims.scroll_second_start, rooftop_supermech_m12_final_boss_anims.scroll_second_mid, rooftop_supermech_m12_final_boss_anims.scroll_second_late, rooftop_supermech_m12_final_boss_anims.scroll_second_end, rooftop_supermech_m12_final_boss_anims.turn_long_start,
        rooftop_supermech_m12_final_boss_anims.turn_long_hold, rooftop_supermech_m12_final_boss_anims.turn_long_recover,
    },
};

u32 spread_offsets_alt[4] = {
    0x0000005D, 0xFFFFFF19, 0x000000F2, 0x00000000,
};

u32 spread_offsets_main[4] = {
    0xFFFFFFA3, 0xFFFFFF19, 0x000000F2, 0x00000000,
};

s16 burst_vec_a_x = -0x33B;

s16 burst_vec_a_z = 0xF2C;

s16 burst_vec_a_y = 0x3EA;

s16 burst_vec_b_x = 0x33B;

s16 burst_vec_b_z = 0xF40;

s16 burst_vec_b_y = 0x397;

SVECTOR shot_muzzles_a[6] = {
    {0x56, -0x70, 0x134, 0}, {0x45, -0x76, 0x13E, 0}, {0x57, -0x74, 0x147, 0}, {-0x19, -0x88, 0x134, 0},
    {-8, -0x86, 0x13E, 0}, {-0x18, -0x8C, 0x147, 0},
};

SVECTOR shot_muzzles_b[6] = {
    {-0x4B, -0x76, 0x150, 0}, {-0x3B, -0x77, 0x144, 0}, {-0x4C, -0x72, 0x13C, 0}, {0x23, -0x87, 0x131, 0},
    {0x12, -0x86, 0x13C, 0}, {0x24, -0x8C, 0x144, 0},
};

SVECTOR supermech_side_muzzles[2] = {
    {0x67, -0x3F, 0xE6, 0}, {-0x67, -0x3F, 0xE6, 0},
};

s16 spawn_offset_x = -0xD2;

s16 spawn_offset_y = 0;

s16 spawn_offset_z = 0x330;

ScriptCallEntry D_80120630[48] = {
    {NULL, 0},
    {script_skip_halfword, 0},
    {script_branch_if_near, 0},
    {script_branch_if_at_least, 0},
    {script_branch_if_aligned, 0},
    {script_jump_if_op_eq, 0},
    {script_op_set_vy, 0},
    {script_op_jump_if_vy_nonneg, 0},
    {script_op_value_push, 0},
    {value_queue_pop, 0},
    {obj_attack_player, 0},
    {spread_shot_fire, 0},
    {scroll_stream_start, 0},
    {script_op_scroll_seg_retract, 0},
    {half_stream_read, 0},
    {script_op_fire_aimed, 0},
    {supermech_fire, 0},
    {script_op_set_flag, 0},
    {script_op_gun_set_value, 0},
    {script_op_set_part_mode, 0},
    {script_op_spawn_at_offset, 0},
    {script_op_fx_spawn, 0},
    {script_op_fx_stop, 0},
    {script_op_jump_if_health_below, 0},
    {script_op_jump_if_outside, 0},
    {script_op_set_shot_timer, 0},
    {script_op_jump_if_rand, 0},
    {script_op_jump_if_turn_left, 0},
    {script_op_set_move_mode, 0},
    {script_op_jump_if_player_below, 0},
    {script_branch_if_not_aligned, 0},
    {script_op_roll_random, 0},
    {script_op_jump_if_roll, 0},
    {obj_loop_sound_start, 0},
    {obj_loop_sound_stop, 0},
    {script_op_set_sound, 0},
    {script_read_fixed4, 0},
    {script_op_chaser_mode, 0},
    {script_op_set_turn, 0},
    {script_op_jump_if_sum_nonpositive, 0},
    {script_op_jump_if_flag, 0},
    {ring_index_dec, 0},
    {script_flag_clear, 0},
    {script_op_turn_step, 0},
    {script_op_jump_if_health_low, 0},
    {fly_path_next, 0},
    {script_op_jump_if_health_flag, 0},
    {obj_sound_play, 0},
};

struct RooftopSupermechM12FinalBossScripts {
    s16 intro[12];
    s16 scroll_attack_gate[6];
    s16 scroll_launch[6];
    s16 scroll_launch_wait[8];
    s16 scroll_fire[8];
    s16 scroll_fire_pause[4];
    s16 scroll_pause_wait[8];
    s16 scroll_hold_wait[8];
    s16 scroll_retract[8];
    s16 scroll_retract_wait[8];
    s16 scroll_done[6];
    s16 scroll_second_gate[6];
    s16 scroll_second_launch[6];
    s16 scroll_second_launch_wait[8];
    s16 scroll_second_fire[8];
    s16 scroll_second_pause[4];
    s16 scroll_second_pause_wait[8];
    s16 scroll_second_hold_wait[8];
    s16 scroll_second_retract[8];
    s16 scroll_second_retract_wait[8];
    s16 scroll_second_done[6];
    s16 spread_gate[6];
    s16 spread_launch[4];
    s16 spread_launch_wait[8];
    s16 spread_fire[4];
    s16 spread_fire_wait[10];
    s16 spread_done[10];
    s16 spread_pop[2];
    s16 spread_second_gate[6];
    s16 spread_second_launch[4];
    s16 spread_second_launch_wait[8];
    s16 spread_second_fire[6];
    s16 spread_second_fire_wait[8];
    s16 spread_second_done[10];
    s16 spread_second_pop[2];
    s16 aim_gate[6];
    s16 aim_launch[4];
    s16 aim_launch_wait[8];
    s16 aim_start[8];
    s16 aim_loop_wait[8];
    s16 aim_fire[12];
    s16 aim_end[8];
    s16 aim_end_wait[8];
    s16 aim_done[6];
    s16 aim_second_gate[6];
    s16 aim_second_launch[4];
    s16 aim_second_launch_wait[8];
    s16 aim_second_start[8];
    s16 aim_second_loop_wait[8];
    s16 aim_second_fire[12];
    s16 aim_second_end[8];
    s16 aim_second_end_wait[8];
    s16 aim_second_done[6];
    s16 fire_gate[6];
    s16 fire_burst_launch[4];
    s16 fire_burst_launch_wait[8];
    s16 fire_burst_start[6];
    s16 fire_burst_loop_wait[8];
    s16 fire_burst_shot[8];
    s16 fire_burst_end[4];
    s16 fire_burst_end_wait[8];
    s16 fire_burst_done[8];
    s16 fire_burst_pop[2];
    s16 charge_gate[6];
    s16 charge_launch[6];
    s16 charge_launch_wait[8];
    s16 charge_release[6];
    s16 charge_release_wait[8];
    s16 charge_done[8];
    s16 charge_pop[2];
    s16 charge_second_gate[6];
    s16 charge_second_launch[6];
    s16 charge_second_launch_wait[8];
    s16 charge_second_release[6];
    s16 charge_second_release_wait[8];
    s16 charge_second_done[8];
    s16 charge_second_pop[2];
    s16 reposition_enter[2];
    s16 reposition_launch[6];
    s16 reposition_wait[8];
    s16 advance_start[6];
    s16 advance_loop_wait[8];
    s16 advance_check[10];
    s16 advance_arrive[2];
    s16 halt_wait[8];
    s16 halt[4];
    s16 halt_wait_end[8];
    s16 halt_pop[2];
    s16 reposition_alt_enter[2];
    s16 reposition_alt_launch[6];
    s16 reposition_alt_wait[8];
    s16 advance_far_start[6];
    s16 advance_far_loop_wait[8];
    s16 advance_far_check[10];
    s16 advance_far_arrive[2];
    s16 halt_far_wait[8];
    s16 halt_far[4];
    s16 halt_far_wait_end[8];
    s16 halt_far_pop[2];
    s16 reposition_far_enter[2];
    s16 reposition_far_launch[6];
    s16 reposition_far_wait[8];
    s16 advance_far_alt_start[6];
    s16 advance_far_alt_wait[8];
    s16 advance_far_alt_check[8];
    s16 advance_far_alt_arrive[2];
    s16 advance_far_alt_halt_wait[8];
    s16 advance_far_halt[4];
    s16 advance_far_halt_wait[8];
    s16 halt_far_alt_pop[2];
    s16 rest_entry[2];
    s16 rest_start[6];
    s16 rest_wait[8];
    s16 rest_done[4];
    s16 low_health_entry[2];
    s16 low_health_reset[4];
    s16 idle_loop[8];
    s16 turn_direction_pick[6];
    s16 chase_start[20];
    s16 chase_wait[6];
    s16 chase_end[12];
    s16 chase_end_wait[8];
    s16 chase_done[8];
    s16 chase_pop[2];
    s16 idle_entry[2];
    s16 idle_reset[4];
    s16 idle_loop_b[8];
    s16 chase_fly_entry[2];
    s16 chase_fly_start[20];
    s16 chase_fly_wait[6];
    s16 chase_fly_end[12];
    s16 chase_fly_end_wait[8];
    s16 chase_fly_done[8];
    s16 chase_fly_pop[2];
    s16 close_range_low_health_pick[14];
    s16 charge_side_pick[8];
    s16 retreat_pick[10];
    s16 retreat_return[4];
    s16 scroll_attack_pick[4];
    s16 low_health_close_return[2];
    s16 far_range_low_health_pick[8];
    s16 charge_aligned_pick[8];
    s16 spread_pick[8];
    s16 fire_pick[4];
    s16 mid_fire_aligned_gate[6];
    s16 mid_fire_pop[2];
    s16 long_range_low_health_pick[8];
    s16 far_attack_roll[12];
    s16 far_spread_pick[4];
    s16 far_charge_pick[4];
    s16 far_attack_roll_return[2];
    s16 mid_range_pick[20];
    s16 default_reposition[6];
    s16 default_reposition_fire[4];
    s16 default_reposition_rest[4];
    s16 default_scroll_pick[4];
    s16 random_move_pick[12];
    s16 default_random_scroll_pick[4];
    s16 default_random_charge_pick[4];
    s16 default_random_return[2];
    s16 low_health_near_pick[14];
    s16 near_charge_pick[4];
    s16 near_aligned_roll[6];
    s16 near_scroll_turn[4];
    s16 aim_pick[4];
    s16 near_aligned_scroll[2];
    s16 near_pick_return[2];
    s16 close_pick[14];
    s16 close_range_charge_pick[8];
    s16 close_range_retreat_pick[14];
    s16 close_range_rest[4];
    s16 scroll_close_pick[4];
    s16 close_attack_pick_return[2];
    s16 mid_pick[18];
    s16 far_range_aligned_pick[8];
    s16 far_range_spread_pick[8];
    s16 far_range_fire_pick[4];
    s16 mid_fire_aligned_check[6];
    s16 mid_pick_return[2];
    s16 far_pick[14];
    s16 far_roll_pick[12];
    s16 far_roll_spread_turn[4];
    s16 far_roll_charge_pick[4];
    s16 far_roll_return[2];
    s16 mid_range_roll_pick[20];
    s16 roll_idle[6];
    s16 roll_fire[4];
    s16 roll_rest[4];
    s16 roll_scroll_pick[4];
    s16 roll_random_retreat[14];
    s16 roll_random_scroll_pick[4];
    s16 roll_random_charge_pick[4];
    s16 roll_random_return[2];
    s16 near_pick[12];
    s16 near_select_charge_pick[4];
    s16 near_scroll_entry[2];
    s16 near_random_scroll_pick[8];
    s16 near_aim_pick[4];
    s16 low_health_rest[4];
    s16 near_select_return[2];
    s16 intro_continue[4];
    s16 health_tier_select[10];
    s16 health_tier_flag[4];
    s16 flag_select_return[6];
    s16 attack_select[16];
    s16 attack_select_low_health[14];
    s16 *table[206];
    s16 *D_80121598;
} rooftop_supermech_m12_final_boss_scripts = {
    /* intro */ {
        SUPERMECH_SET_PART_MODE, 0,
        WAIT(32),
        SUPERMECH_SET_FLAG, 1,
        SUPERMECH_GUN_SET_VALUE, 4096,
        SUPERMECH_SET_PART_MODE, 1,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_INTRO_CONTINUE),
    },
    /* scroll_attack_gate */ {
        SUPERMECH_JUMP_IF_HEALTH_LOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_LAUNCH),
    },
    /* scroll_launch */ {
        NEXT_STATE(SUPERMECH_STATE_SCROLL_FIRE),
        SUPERMECH_SET_SHOT_TIMER, 8,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_LAUNCH_WAIT),
    },
    /* scroll_launch_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_FIRE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_LAUNCH_WAIT),
    },
    /* scroll_fire */ {
        SUPERMECH_SCROLL_STREAM_START, 0,
        SUPERMECH_JUMP_IF_HEALTH_BELOW, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_FIRE_PAUSE,
        SUPERMECH_SCROLL_STREAM_START, 3,
    },
    /* scroll_fire_pause */ {
        SUPERMECH_SET_SHOT_TIMER, 4,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_PAUSE_WAIT),
    },
    /* scroll_pause_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_HOLD_WAIT,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_PAUSE_WAIT),
    },
    /* scroll_hold_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_RETRACT,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_HOLD_WAIT),
    },
    /* scroll_retract */ {
        SUPERMECH_SCROLL_SEG_RETRACT, 0,
        SUPERMECH_SCROLL_SEG_RETRACT, 1,
        SUPERMECH_SET_SHOT_TIMER, 0,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_RETRACT_WAIT),
    },
    /* scroll_retract_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_DONE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_RETRACT_WAIT),
    },
    /* scroll_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(1),
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* scroll_second_gate */ {
        SUPERMECH_JUMP_IF_HEALTH_LOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY, 12,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_LAUNCH),
    },
    /* scroll_second_launch */ {
        NEXT_STATE(SUPERMECH_STATE_SCROLL_FIRE_SECOND),
        SUPERMECH_SET_SHOT_TIMER, 8,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_LAUNCH_WAIT),
    },
    /* scroll_second_launch_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_FIRE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_LAUNCH_WAIT),
    },
    /* scroll_second_fire */ {
        SUPERMECH_SCROLL_STREAM_START, 1,
        SUPERMECH_JUMP_IF_HEALTH_BELOW, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_PAUSE,
        SUPERMECH_SCROLL_STREAM_START, 2,
    },
    /* scroll_second_pause */ {
        SUPERMECH_SET_SHOT_TIMER, 4,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_PAUSE_WAIT),
    },
    /* scroll_second_pause_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_HOLD_WAIT,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_PAUSE_WAIT),
    },
    /* scroll_second_hold_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_RETRACT,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_HOLD_WAIT),
    },
    /* scroll_second_retract */ {
        SUPERMECH_SCROLL_SEG_RETRACT, 0,
        SUPERMECH_SCROLL_SEG_RETRACT, 1,
        SUPERMECH_SET_SHOT_TIMER, 0,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_RETRACT_WAIT),
    },
    /* scroll_second_retract_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_DONE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_RETRACT_WAIT),
    },
    /* scroll_second_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(1),
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* spread_gate */ {
        SUPERMECH_JUMP_IF_HEALTH_LOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY, 22,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_LAUNCH),
    },
    /* spread_launch */ {
        NEXT_STATE(SUPERMECH_STATE_SPREAD_FIRE),
        SUPERMECH_SET_SHOT_TIMER, 10,
    },
    /* spread_launch_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_FIRE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_LAUNCH_WAIT),
    },
    /* spread_fire */ {
        SUPERMECH_SPREAD_SHOT_FIRE, 0,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_FIRE_WAIT),
    },
    /* spread_fire_wait */ {
        SUPERMECH_SET_SHOT_TIMER, 0,
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_DONE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_FIRE_WAIT),
    },
    /* spread_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(12),
        SUPERMECH_JUMP_IF_HEALTH_FLAG, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_POP,
        WAIT(12),
    },
    /* spread_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* spread_second_gate */ {
        SUPERMECH_JUMP_IF_HEALTH_LOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY, 29,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_LAUNCH),
    },
    /* spread_second_launch */ {
        NEXT_STATE(SUPERMECH_STATE_SPREAD_FIRE_SECOND),
        SUPERMECH_SET_SHOT_TIMER, 10,
    },
    /* spread_second_launch_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_FIRE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_LAUNCH_WAIT),
    },
    /* spread_second_fire */ {
        SUPERMECH_SET_SHOT_TIMER, 0,
        SUPERMECH_SPREAD_SHOT_FIRE, 1,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_FIRE_WAIT),
    },
    /* spread_second_fire_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_DONE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_FIRE_WAIT),
    },
    /* spread_second_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(12),
        SUPERMECH_JUMP_IF_HEALTH_FLAG, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_POP,
        WAIT(12),
    },
    /* spread_second_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* aim_gate */ {
        SUPERMECH_JUMP_IF_HEALTH_LOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY, 36,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_LAUNCH),
    },
    /* aim_launch */ {
        NEXT_STATE(SUPERMECH_STATE_AIM_FIRE),
        SUPERMECH_SET_SHOT_TIMER, 0,
    },
    /* aim_launch_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_START,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_LAUNCH_WAIT),
    },
    /* aim_start */ {
        SUPERMECH_HALF_STREAM_READ, 8,
        SET_COUNTER(20),
        SUPERMECH_LOOP_SOUND_START,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_LOOP_WAIT),
    },
    /* aim_loop_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_FIRE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_LOOP_WAIT),
    },
    /* aim_fire */ {
        SUPERMECH_FIRE_AIMED, 0,
        SUPERMECH_BRANCH_IF_NOT_ALIGNED, 682, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_END,
        SUPERMECH_JUMP_IF_HEALTH_FLAG, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_END,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_LOOP_WAIT),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_END),
    },
    /* aim_end */ {
        SUPERMECH_HALF_STREAM_READ, 0,
        SUPERMECH_LOOP_SOUND_STOP,
        NEXT_STATE(SUPERMECH_STATE_AIM_END),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_END_WAIT),
    },
    /* aim_end_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_DONE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_END_WAIT),
    },
    /* aim_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(1),
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* aim_second_gate */ {
        SUPERMECH_JUMP_IF_HEALTH_LOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY, 45,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_LAUNCH),
    },
    /* aim_second_launch */ {
        NEXT_STATE(SUPERMECH_STATE_AIM_FIRE_SECOND),
        SUPERMECH_SET_SHOT_TIMER, 0,
    },
    /* aim_second_launch_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_START,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_LAUNCH_WAIT),
    },
    /* aim_second_start */ {
        SUPERMECH_HALF_STREAM_READ, -8,
        SET_COUNTER(20),
        SUPERMECH_LOOP_SOUND_START,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_LOOP_WAIT),
    },
    /* aim_second_loop_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_FIRE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_LOOP_WAIT),
    },
    /* aim_second_fire */ {
        SUPERMECH_FIRE_AIMED, 1,
        SUPERMECH_BRANCH_IF_NOT_ALIGNED, 682, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_END,
        SUPERMECH_JUMP_IF_HEALTH_FLAG, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_END,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_LOOP_WAIT),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_END),
    },
    /* aim_second_end */ {
        SUPERMECH_HALF_STREAM_READ, 0,
        NEXT_STATE(SUPERMECH_STATE_AIM_END_SECOND),
        SUPERMECH_LOOP_SOUND_STOP,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_END_WAIT),
    },
    /* aim_second_end_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_DONE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_END_WAIT),
    },
    /* aim_second_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(1),
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* fire_gate */ {
        SUPERMECH_JUMP_IF_HEALTH_LOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY, 54,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_LAUNCH),
    },
    /* fire_burst_launch */ {
        NEXT_STATE(SUPERMECH_STATE_FIRE_BURST),
        SUPERMECH_SET_SHOT_TIMER, 10,
    },
    /* fire_burst_launch_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_START,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_LAUNCH_WAIT),
    },
    /* fire_burst_start */ {
        SUPERMECH_SET_SHOT_TIMER, 0,
        SET_COUNTER(4),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_LOOP_WAIT),
    },
    /* fire_burst_loop_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_SHOT,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_LOOP_WAIT),
    },
    /* fire_burst_shot */ {
        SUPERMECH_FIRE, 0,
        SUPERMECH_FIRE, 1,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_LOOP_WAIT),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_END),
    },
    /* fire_burst_end */ {
        NEXT_STATE(SUPERMECH_STATE_FIRE_END),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_END_WAIT),
    },
    /* fire_burst_end_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_DONE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_END_WAIT),
    },
    /* fire_burst_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(32),
        SUPERMECH_JUMP_IF_HEALTH_FLAG, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_BURST_POP,
    },
    /* fire_burst_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* charge_gate */ {
        SUPERMECH_JUMP_IF_HEALTH_LOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY, 64,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_LAUNCH),
    },
    /* charge_launch */ {
        NEXT_STATE(SUPERMECH_STATE_CHARGE),
        SUPERMECH_SET_SHOT_TIMER, 16,
        SUPERMECH_FX_SPAWN, 0,
    },
    /* charge_launch_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_RELEASE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_LAUNCH_WAIT),
    },
    /* charge_release */ {
        SUPERMECH_SPAWN_AT_OFFSET, 0,
        SUPERMECH_FX_STOP, 0,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_RELEASE_WAIT),
    },
    /* charge_release_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_DONE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_RELEASE_WAIT),
    },
    /* charge_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(8),
        SUPERMECH_JUMP_IF_HEALTH_FLAG, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_POP,
    },
    /* charge_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* charge_second_gate */ {
        SUPERMECH_JUMP_IF_HEALTH_LOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY, 71,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_LAUNCH),
    },
    /* charge_second_launch */ {
        NEXT_STATE(SUPERMECH_STATE_CHARGE_SECOND),
        SUPERMECH_SET_SHOT_TIMER, 16,
        SUPERMECH_FX_SPAWN, 1,
    },
    /* charge_second_launch_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_RELEASE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_LAUNCH_WAIT),
    },
    /* charge_second_release */ {
        SUPERMECH_SPAWN_AT_OFFSET, 1,
        SUPERMECH_FX_STOP, 1,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_RELEASE_WAIT),
    },
    /* charge_second_release_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_DONE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_RELEASE_WAIT),
    },
    /* charge_second_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(8),
        SUPERMECH_JUMP_IF_HEALTH_FLAG, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_POP,
    },
    /* charge_second_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* reposition_enter */ {
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_LAUNCH),
    },
    /* reposition_launch */ {
        NEXT_STATE(SUPERMECH_STATE_TURN),
        SUPERMECH_SET_SHOT_TIMER, 26,
        WAIT(1),
    },
    /* reposition_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_START,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_WAIT),
    },
    /* advance_start */ {
        SET_SPEED(16),
        SET_COUNTER(4),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_LOOP_WAIT),
    },
    /* advance_loop_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_CHECK,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_LOOP_WAIT),
    },
    /* advance_check */ {
        SUPERMECH_BRANCH_IF_NEAR, 1300, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_ARRIVE,
        SUPERMECH_JUMP_IF_OUTSIDE, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_ARRIVE,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_LOOP_WAIT),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_ARRIVE),
    },
    /* advance_arrive */ {
        NEXT_STATE(SUPERMECH_STATE_HALT),
    },
    /* halt_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_WAIT),
    },
    /* halt */ {
        SET_SPEED(0),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_WAIT_END),
    },
    /* halt_wait_end */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_POP,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_WAIT_END),
    },
    /* halt_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* reposition_alt_enter */ {
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ALT_LAUNCH),
    },
    /* reposition_alt_launch */ {
        NEXT_STATE(SUPERMECH_STATE_TURN),
        SUPERMECH_SET_SHOT_TIMER, 26,
        WAIT(1),
    },
    /* reposition_alt_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_START,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ALT_WAIT),
    },
    /* advance_far_start */ {
        SET_SPEED(16),
        SET_COUNTER(8),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_LOOP_WAIT),
    },
    /* advance_far_loop_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_CHECK,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_LOOP_WAIT),
    },
    /* advance_far_check */ {
        SUPERMECH_BRANCH_IF_NEAR, 2500, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ARRIVE,
        SUPERMECH_JUMP_IF_OUTSIDE, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ARRIVE,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_LOOP_WAIT),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ARRIVE),
    },
    /* advance_far_arrive */ {
        NEXT_STATE(SUPERMECH_STATE_HALT),
    },
    /* halt_far_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_FAR,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_FAR_WAIT),
    },
    /* halt_far */ {
        SET_SPEED(0),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_FAR_WAIT_END),
    },
    /* halt_far_wait_end */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_FAR_POP,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_FAR_WAIT_END),
    },
    /* halt_far_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* reposition_far_enter */ {
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_FAR_LAUNCH),
    },
    /* reposition_far_launch */ {
        NEXT_STATE(SUPERMECH_STATE_TURN),
        SUPERMECH_SET_SHOT_TIMER, 26,
        WAIT(1),
    },
    /* reposition_far_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ALT_START,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_FAR_WAIT),
    },
    /* advance_far_alt_start */ {
        SET_SPEED(16),
        SET_COUNTER(8),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ALT_WAIT),
    },
    /* advance_far_alt_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ALT_CHECK,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ALT_WAIT),
    },
    /* advance_far_alt_check */ {
        SUPERMECH_BRANCH_IF_AT_LEAST, 2500, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ALT_ARRIVE,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ALT_WAIT),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ALT_ARRIVE),
    },
    /* advance_far_alt_arrive */ {
        NEXT_STATE(SUPERMECH_STATE_HALT),
    },
    /* advance_far_alt_halt_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_HALT,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_ALT_HALT_WAIT),
    },
    /* advance_far_halt */ {
        SET_SPEED(0),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_HALT_WAIT),
    },
    /* advance_far_halt_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HALT_FAR_ALT_POP,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ADVANCE_FAR_HALT_WAIT),
    },
    /* halt_far_alt_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* rest_entry */ {
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_START),
    },
    /* rest_start */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        SUPERMECH_SET_SHOT_TIMER, 96,
        SET_COUNTER(32),
    },
    /* rest_wait */ {
        WAIT(1),
        SUPERMECH_BRANCH_IF_ALIGNED, 256, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_DONE,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_WAIT),
    },
    /* rest_done */ {
        SUPERMECH_SET_SHOT_TIMER, 0,
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* low_health_entry */ {
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_RESET),
    },
    /* low_health_reset */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(1),
    },
    /* idle_loop */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_TURN_DIRECTION_PICK,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_IDLE_LOOP),
    },
    /* turn_direction_pick */ {
        SUPERMECH_SET_TURN, 1,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_START,
        SUPERMECH_SET_TURN, -1,
    },
    /* chase_start */ {
        SUPERMECH_TURN_STEP, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_POP,
        SUPERMECH_SET_SOUND, 0,
        SUPERMECH_CHASER_MODE, 1,
        SUPERMECH_SET_SHOT_TIMER, 128,
        SUPERMECH_SOUND_PLAY,
        SUPERMECH_READ_FIXED4, 8192,
        WAIT(4),
        SUPERMECH_READ_FIXED4, 0,
        WAIT(4),
        SUPERMECH_READ_FIXED4, -3584,
    },
    /* chase_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_SUM_NONPOSITIVE, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_END,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_WAIT),
    },
    /* chase_end */ {
        SUPERMECH_CHASER_MODE, 0,
        SUPERMECH_SET_SOUND, 0,
        SUPERMECH_READ_FIXED4, 0,
        SUPERMECH_SET_SHOT_TIMER, 0,
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(1),
    },
    /* chase_end_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_DONE,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_END_WAIT),
    },
    /* chase_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(16),
        SUPERMECH_JUMP_IF_HEALTH_FLAG, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_POP,
    },
    /* chase_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* idle_entry */ {
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_IDLE_RESET),
    },
    /* idle_reset */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(1),
    },
    /* idle_loop_b */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_FLY_ENTRY,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_IDLE_LOOP_B),
    },
    /* chase_fly_entry */ {
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_FLY_START),
    },
    /* chase_fly_start */ {
        SUPERMECH_FLY_PATH_NEXT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_FLY_POP,
        SUPERMECH_SET_SOUND, 0,
        SUPERMECH_CHASER_MODE, 2,
        SUPERMECH_SET_SHOT_TIMER, 128,
        SUPERMECH_SOUND_PLAY,
        SUPERMECH_READ_FIXED4, 8192,
        WAIT(4),
        SUPERMECH_READ_FIXED4, 0,
        WAIT(4),
        SUPERMECH_READ_FIXED4, -3584,
    },
    /* chase_fly_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_SUM_NONPOSITIVE, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_FLY_END,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_FLY_WAIT),
    },
    /* chase_fly_end */ {
        SUPERMECH_CHASER_MODE, 0,
        SUPERMECH_SET_SOUND, 0,
        SUPERMECH_READ_FIXED4, 0,
        SUPERMECH_SET_SHOT_TIMER, 0,
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(1),
    },
    /* chase_fly_end_wait */ {
        WAIT(1),
        SUPERMECH_JUMP_IF_OP_EQ, -1, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_FLY_DONE,
        LOOP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_FLY_END_WAIT),
    },
    /* chase_fly_done */ {
        NEXT_STATE(SUPERMECH_STATE_IDLE),
        WAIT(16),
        SUPERMECH_JUMP_IF_HEALTH_FLAG, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHASE_FLY_POP,
    },
    /* chase_fly_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* close_range_low_health_pick */ {
        SUPERMECH_SKIP_HALFWORD, 1,
        SUPERMECH_VALUE_PUSH, 139,
        SUPERMECH_JUMP_IF_PLAYER_BELOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_RETREAT_PICK,
        SUPERMECH_BRANCH_IF_ALIGNED, 1024, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SIDE_PICK,
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* charge_side_pick */ {
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_PICK,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* retreat_pick */ {
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SIDE_PICK,
        SUPERMECH_VALUE_PUSH, 137,
        SUPERMECH_SET_MOVE_MODE, 3,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ALT_ENTER),
    },
    /* retreat_return */ {
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* scroll_attack_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_GATE),
    },
    /* low_health_close_return */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* far_range_low_health_pick */ {
        SUPERMECH_SKIP_HALFWORD, 4,
        SUPERMECH_VALUE_PUSH, 141,
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ENTER),
    },
    /* charge_aligned_pick */ {
        SUPERMECH_BRANCH_IF_ALIGNED, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_PICK,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* spread_pick */ {
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_PICK,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_GATE),
    },
    /* fire_pick */ {
        SUPERMECH_VALUE_PUSH, 144,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_GATE),
    },
    /* mid_fire_aligned_gate */ {
        SUPERMECH_BRANCH_IF_ALIGNED, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_PICK,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_MID_FIRE_POP),
    },
    /* mid_fire_pop */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* long_range_low_health_pick */ {
        SUPERMECH_SKIP_HALFWORD, 5,
        SUPERMECH_VALUE_PUSH, 147,
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ALT_ENTER),
    },
    /* far_attack_roll */ {
        SUPERMECH_ROLL_RANDOM,
        SUPERMECH_JUMP_IF_ROLL, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_ATTACK_ROLL_RETURN,
        SUPERMECH_JUMP_IF_ROLL, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_SPREAD_PICK,
        SUPERMECH_JUMP_IF_ROLL, 3072, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_CHARGE_PICK,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_GATE),
    },
    /* far_spread_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_GATE),
    },
    /* far_charge_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* far_attack_roll_return */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* mid_range_pick */ {
        SUPERMECH_SKIP_HALFWORD, 3,
        SUPERMECH_BRANCH_IF_NOT_ALIGNED, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_RANDOM_MOVE_PICK,
        SUPERMECH_ROLL_RANDOM,
        SUPERMECH_JUMP_IF_ROLL, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_DEFAULT_REPOSITION,
        SUPERMECH_JUMP_IF_ROLL, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE,
        SUPERMECH_JUMP_IF_ROLL, 3072, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_DEFAULT_SCROLL_PICK,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_GATE),
    },
    /* default_reposition */ {
        SUPERMECH_VALUE_PUSH, 153,
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ENTER),
    },
    /* default_reposition_fire */ {
        SUPERMECH_VALUE_PUSH, 154,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_GATE),
    },
    /* default_reposition_rest */ {
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* default_scroll_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_GATE),
    },
    /* random_move_pick */ {
        SUPERMECH_JUMP_IF_RAND, 1024, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_DEFAULT_RANDOM_CHARGE_PICK,
        SUPERMECH_VALUE_PUSH, 157,
        SUPERMECH_SET_MOVE_MODE, 2,
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ENTER,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* default_random_scroll_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_GATE),
    },
    /* default_random_charge_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* default_random_return */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* low_health_near_pick */ {
        SUPERMECH_SKIP_HALFWORD, 2,
        SUPERMECH_BRANCH_IF_ALIGNED, 341, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_NEAR_ALIGNED_ROLL,
        SUPERMECH_BRANCH_IF_ALIGNED, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_NEAR_ALIGNED_SCROLL,
        SUPERMECH_VALUE_PUSH, 161,
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* near_charge_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* near_aligned_roll */ {
        SUPERMECH_VALUE_PUSH, 166,
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_PICK,
    },
    /* near_scroll_turn */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_GATE),
    },
    /* aim_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_GATE),
    },
    /* near_aligned_scroll */ {
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_NEAR_SCROLL_TURN),
    },
    /* near_pick_return */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* close_pick */ {
        SUPERMECH_SKIP_HALFWORD, 1,
        SUPERMECH_VALUE_PUSH, 172,
        SUPERMECH_JUMP_IF_PLAYER_BELOW, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CLOSE_RANGE_RETREAT_PICK,
        SUPERMECH_BRANCH_IF_ALIGNED, 1024, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CLOSE_RANGE_CHARGE_PICK,
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* close_range_charge_pick */ {
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_CLOSE_PICK,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* close_range_retreat_pick */ {
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CLOSE_RANGE_CHARGE_PICK,
        SUPERMECH_VALUE_PUSH, 170,
        SUPERMECH_SET_MOVE_MODE, 3,
        SUPERMECH_SET_TURN, -1,
        JUMP_RANDOM(1024, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ALT_ENTER),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_IDLE_ENTRY),
    },
    /* close_range_rest */ {
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* scroll_close_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_GATE),
    },
    /* close_attack_pick_return */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* mid_pick */ {
        SUPERMECH_SKIP_HALFWORD, 4,
        SUPERMECH_VALUE_PUSH, 174,
        SUPERMECH_SET_MOVE_MODE, 2,
        SUPERMECH_SET_TURN, 1,
        SUPERMECH_ROLL_RANDOM,
        SUPERMECH_JUMP_IF_ROLL, 1024, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ENTER,
        SUPERMECH_JUMP_IF_ROLL, 3072, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_IDLE_ENTRY,
        SUPERMECH_RING_INDEX_DEC,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_RANGE_ALIGNED_PICK),
    },
    /* far_range_aligned_pick */ {
        SUPERMECH_BRANCH_IF_ALIGNED, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_RANGE_SPREAD_PICK,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* far_range_spread_pick */ {
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_RANGE_FIRE_PICK,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_GATE),
    },
    /* far_range_fire_pick */ {
        SUPERMECH_VALUE_PUSH, 177,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_GATE),
    },
    /* mid_fire_aligned_check */ {
        SUPERMECH_BRANCH_IF_ALIGNED, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_RANGE_SPREAD_PICK,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_MID_PICK_RETURN),
    },
    /* mid_pick_return */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* far_pick */ {
        SUPERMECH_SKIP_HALFWORD, 5,
        SUPERMECH_VALUE_PUSH, 180,
        SUPERMECH_SET_MOVE_MODE, 2,
        SUPERMECH_SET_TURN, 1,
        JUMP_RANDOM(1024, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REPOSITION_ALT_ENTER),
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_IDLE_ENTRY),
    },
    /* far_roll_pick */ {
        SUPERMECH_ROLL_RANDOM,
        SUPERMECH_JUMP_IF_ROLL, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_ROLL_RETURN,
        SUPERMECH_JUMP_IF_ROLL, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_ROLL_SPREAD_TURN,
        SUPERMECH_JUMP_IF_ROLL, 3072, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_ROLL_CHARGE_PICK,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_GATE),
    },
    /* far_roll_spread_turn */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_GATE),
    },
    /* far_roll_charge_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* far_roll_return */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* mid_range_roll_pick */ {
        SUPERMECH_SKIP_HALFWORD, 3,
        SUPERMECH_BRANCH_IF_NOT_ALIGNED, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ROLL_RANDOM_RETREAT,
        SUPERMECH_ROLL_RANDOM,
        SUPERMECH_JUMP_IF_ROLL, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ROLL_IDLE,
        SUPERMECH_JUMP_IF_ROLL, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE,
        SUPERMECH_JUMP_IF_ROLL, 3072, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ROLL_SCROLL_PICK,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SPREAD_SECOND_GATE),
    },
    /* roll_idle */ {
        SUPERMECH_VALUE_PUSH, 186,
        SUPERMECH_SET_TURN, 1,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_IDLE_ENTRY),
    },
    /* roll_fire */ {
        SUPERMECH_VALUE_PUSH, 187,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FIRE_GATE),
    },
    /* roll_rest */ {
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* roll_scroll_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_GATE),
    },
    /* roll_random_retreat */ {
        SUPERMECH_JUMP_IF_RAND, 1024, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ROLL_RANDOM_CHARGE_PICK,
        SUPERMECH_VALUE_PUSH, 190,
        SUPERMECH_SET_MOVE_MODE, 2,
        SUPERMECH_SET_TURN, 1,
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_IDLE_ENTRY,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* roll_random_scroll_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_GATE),
    },
    /* roll_random_charge_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* roll_random_return */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* near_pick */ {
        SUPERMECH_SKIP_HALFWORD, 2,
        SUPERMECH_BRANCH_IF_ALIGNED, 512, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_REST,
        SUPERMECH_VALUE_PUSH, 194,
        SUPERMECH_SET_MOVE_MODE, 2,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_REST_ENTRY),
    },
    /* near_select_charge_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CHARGE_SECOND_GATE),
    },
    /* near_scroll_entry */ {
        SUPERMECH_VALUE_PUSH, 199,
    },
    /* near_random_scroll_pick */ {
        SUPERMECH_JUMP_IF_RAND, 2048, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_NEAR_AIM_PICK,
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_SECOND_GATE),
    },
    /* near_aim_pick */ {
        SUPERMECH_JUMP_IF_TURN_LEFT, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_SECOND_GATE,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_AIM_GATE),
    },
    /* low_health_rest */ {
        SUPERMECH_VALUE_PUSH, 196,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_ENTRY),
    },
    /* near_select_return */ {
        SUPERMECH_VALUE_QUEUE_POP,
    },
    /* intro_continue */ {
        SUPERMECH_VALUE_PUSH, 201,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_SCROLL_ATTACK_GATE),
    },
    /* health_tier_select */ {
        SUPERMECH_VALUE_PUSH, 201,
        SUPERMECH_JUMP_IF_HEALTH_BELOW, 2730, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ATTACK_SELECT_LOW_HEALTH,
        SUPERMECH_JUMP_IF_HEALTH_BELOW, 1365, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_HEALTH_TIER_FLAG,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ATTACK_SELECT),
    },
    /* health_tier_flag */ {
        SUPERMECH_JUMP_IF_FLAG, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FLAG_SELECT_RETURN,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ATTACK_SELECT),
    },
    /* flag_select_return */ {
        8, 0xCC, -3, 0x72, 0x29, 0,
    },
    /* attack_select */ {
        SUPERMECH_FLAG_CLEAR,
        SUPERMECH_BRANCH_IF_NEAR, 800, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CLOSE_PICK,
        SUPERMECH_BRANCH_IF_NEAR, 1300, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_NEAR_PICK,
        SUPERMECH_BRANCH_IF_AT_LEAST, 2500, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_MID_PICK,
        SUPERMECH_BRANCH_IF_AT_LEAST, 4000, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_PICK,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_MID_RANGE_PICK),
    },
    /* attack_select_low_health */ {
        SUPERMECH_BRANCH_IF_NEAR, 800, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_CLOSE_RANGE_LOW_HEALTH_PICK,
        SUPERMECH_BRANCH_IF_NEAR, 1300, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LOW_HEALTH_NEAR_PICK,
        SUPERMECH_BRANCH_IF_AT_LEAST, 2500, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_FAR_RANGE_LOW_HEALTH_PICK,
        SUPERMECH_BRANCH_IF_AT_LEAST, 4000, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_LONG_RANGE_LOW_HEALTH_PICK,
        JUMP(ROOFTOP_SUPERMECH_M12_FINAL_BOSS_MID_RANGE_PICK),
    },
    /* table */ {
        rooftop_supermech_m12_final_boss_scripts.intro, rooftop_supermech_m12_final_boss_scripts.scroll_attack_gate, rooftop_supermech_m12_final_boss_scripts.scroll_launch, rooftop_supermech_m12_final_boss_scripts.scroll_launch_wait, rooftop_supermech_m12_final_boss_scripts.scroll_fire, rooftop_supermech_m12_final_boss_scripts.scroll_fire_pause,
        rooftop_supermech_m12_final_boss_scripts.scroll_pause_wait, rooftop_supermech_m12_final_boss_scripts.scroll_hold_wait, rooftop_supermech_m12_final_boss_scripts.scroll_retract, rooftop_supermech_m12_final_boss_scripts.scroll_retract_wait, rooftop_supermech_m12_final_boss_scripts.scroll_done, rooftop_supermech_m12_final_boss_scripts.scroll_second_gate,
        rooftop_supermech_m12_final_boss_scripts.scroll_second_launch, rooftop_supermech_m12_final_boss_scripts.scroll_second_launch_wait, rooftop_supermech_m12_final_boss_scripts.scroll_second_fire, rooftop_supermech_m12_final_boss_scripts.scroll_second_pause, rooftop_supermech_m12_final_boss_scripts.scroll_second_pause_wait, rooftop_supermech_m12_final_boss_scripts.scroll_second_hold_wait,
        rooftop_supermech_m12_final_boss_scripts.scroll_second_retract, rooftop_supermech_m12_final_boss_scripts.scroll_second_retract_wait, rooftop_supermech_m12_final_boss_scripts.scroll_second_done, rooftop_supermech_m12_final_boss_scripts.spread_gate, rooftop_supermech_m12_final_boss_scripts.spread_launch, rooftop_supermech_m12_final_boss_scripts.spread_launch_wait,
        rooftop_supermech_m12_final_boss_scripts.spread_fire, rooftop_supermech_m12_final_boss_scripts.spread_fire_wait, rooftop_supermech_m12_final_boss_scripts.spread_done, rooftop_supermech_m12_final_boss_scripts.spread_pop, rooftop_supermech_m12_final_boss_scripts.spread_second_gate, rooftop_supermech_m12_final_boss_scripts.spread_second_launch,
        rooftop_supermech_m12_final_boss_scripts.spread_second_launch_wait, rooftop_supermech_m12_final_boss_scripts.spread_second_fire, rooftop_supermech_m12_final_boss_scripts.spread_second_fire_wait, rooftop_supermech_m12_final_boss_scripts.spread_second_done, rooftop_supermech_m12_final_boss_scripts.spread_second_pop, rooftop_supermech_m12_final_boss_scripts.aim_gate,
        rooftop_supermech_m12_final_boss_scripts.aim_launch, rooftop_supermech_m12_final_boss_scripts.aim_launch_wait, rooftop_supermech_m12_final_boss_scripts.aim_start, rooftop_supermech_m12_final_boss_scripts.aim_loop_wait, rooftop_supermech_m12_final_boss_scripts.aim_fire, rooftop_supermech_m12_final_boss_scripts.aim_end,
        rooftop_supermech_m12_final_boss_scripts.aim_end_wait, rooftop_supermech_m12_final_boss_scripts.aim_done, rooftop_supermech_m12_final_boss_scripts.aim_second_gate, rooftop_supermech_m12_final_boss_scripts.aim_second_launch, rooftop_supermech_m12_final_boss_scripts.aim_second_launch_wait, rooftop_supermech_m12_final_boss_scripts.aim_second_start,
        rooftop_supermech_m12_final_boss_scripts.aim_second_loop_wait, rooftop_supermech_m12_final_boss_scripts.aim_second_fire, rooftop_supermech_m12_final_boss_scripts.aim_second_end, rooftop_supermech_m12_final_boss_scripts.aim_second_end_wait, rooftop_supermech_m12_final_boss_scripts.aim_second_done, rooftop_supermech_m12_final_boss_scripts.fire_gate,
        rooftop_supermech_m12_final_boss_scripts.fire_burst_launch, rooftop_supermech_m12_final_boss_scripts.fire_burst_launch_wait, rooftop_supermech_m12_final_boss_scripts.fire_burst_start, rooftop_supermech_m12_final_boss_scripts.fire_burst_loop_wait, rooftop_supermech_m12_final_boss_scripts.fire_burst_shot, rooftop_supermech_m12_final_boss_scripts.fire_burst_end,
        rooftop_supermech_m12_final_boss_scripts.fire_burst_end_wait, rooftop_supermech_m12_final_boss_scripts.fire_burst_done, rooftop_supermech_m12_final_boss_scripts.fire_burst_pop, rooftop_supermech_m12_final_boss_scripts.charge_gate, rooftop_supermech_m12_final_boss_scripts.charge_launch, rooftop_supermech_m12_final_boss_scripts.charge_launch_wait,
        rooftop_supermech_m12_final_boss_scripts.charge_release, rooftop_supermech_m12_final_boss_scripts.charge_release_wait, rooftop_supermech_m12_final_boss_scripts.charge_done, rooftop_supermech_m12_final_boss_scripts.charge_pop, rooftop_supermech_m12_final_boss_scripts.charge_second_gate, rooftop_supermech_m12_final_boss_scripts.charge_second_launch,
        rooftop_supermech_m12_final_boss_scripts.charge_second_launch_wait, rooftop_supermech_m12_final_boss_scripts.charge_second_release, rooftop_supermech_m12_final_boss_scripts.charge_second_release_wait, rooftop_supermech_m12_final_boss_scripts.charge_second_done, rooftop_supermech_m12_final_boss_scripts.charge_second_pop, rooftop_supermech_m12_final_boss_scripts.reposition_enter,
        rooftop_supermech_m12_final_boss_scripts.reposition_launch, rooftop_supermech_m12_final_boss_scripts.reposition_wait, rooftop_supermech_m12_final_boss_scripts.advance_start, rooftop_supermech_m12_final_boss_scripts.advance_loop_wait, rooftop_supermech_m12_final_boss_scripts.advance_check, rooftop_supermech_m12_final_boss_scripts.advance_arrive,
        rooftop_supermech_m12_final_boss_scripts.halt_wait, rooftop_supermech_m12_final_boss_scripts.halt, rooftop_supermech_m12_final_boss_scripts.halt_wait_end, rooftop_supermech_m12_final_boss_scripts.halt_pop, rooftop_supermech_m12_final_boss_scripts.reposition_alt_enter, rooftop_supermech_m12_final_boss_scripts.reposition_alt_launch,
        rooftop_supermech_m12_final_boss_scripts.reposition_alt_wait, rooftop_supermech_m12_final_boss_scripts.advance_far_start, rooftop_supermech_m12_final_boss_scripts.advance_far_loop_wait, rooftop_supermech_m12_final_boss_scripts.advance_far_check, rooftop_supermech_m12_final_boss_scripts.advance_far_arrive, rooftop_supermech_m12_final_boss_scripts.halt_far_wait,
        rooftop_supermech_m12_final_boss_scripts.halt_far, rooftop_supermech_m12_final_boss_scripts.halt_far_wait_end, rooftop_supermech_m12_final_boss_scripts.halt_far_pop, rooftop_supermech_m12_final_boss_scripts.reposition_far_enter, rooftop_supermech_m12_final_boss_scripts.reposition_far_launch, rooftop_supermech_m12_final_boss_scripts.reposition_far_wait,
        rooftop_supermech_m12_final_boss_scripts.advance_far_alt_start, rooftop_supermech_m12_final_boss_scripts.advance_far_alt_wait, rooftop_supermech_m12_final_boss_scripts.advance_far_alt_check, rooftop_supermech_m12_final_boss_scripts.advance_far_alt_arrive, rooftop_supermech_m12_final_boss_scripts.advance_far_alt_halt_wait, rooftop_supermech_m12_final_boss_scripts.advance_far_halt,
        rooftop_supermech_m12_final_boss_scripts.advance_far_halt_wait, rooftop_supermech_m12_final_boss_scripts.halt_far_alt_pop, rooftop_supermech_m12_final_boss_scripts.rest_entry, rooftop_supermech_m12_final_boss_scripts.rest_start, rooftop_supermech_m12_final_boss_scripts.rest_wait, rooftop_supermech_m12_final_boss_scripts.rest_done,
        rooftop_supermech_m12_final_boss_scripts.low_health_entry, rooftop_supermech_m12_final_boss_scripts.low_health_reset, rooftop_supermech_m12_final_boss_scripts.idle_loop, rooftop_supermech_m12_final_boss_scripts.turn_direction_pick, rooftop_supermech_m12_final_boss_scripts.chase_start, rooftop_supermech_m12_final_boss_scripts.chase_wait,
        rooftop_supermech_m12_final_boss_scripts.chase_end, rooftop_supermech_m12_final_boss_scripts.chase_end_wait, rooftop_supermech_m12_final_boss_scripts.chase_done, rooftop_supermech_m12_final_boss_scripts.chase_pop, rooftop_supermech_m12_final_boss_scripts.idle_entry, rooftop_supermech_m12_final_boss_scripts.idle_reset,
        rooftop_supermech_m12_final_boss_scripts.idle_loop_b, rooftop_supermech_m12_final_boss_scripts.chase_fly_entry, rooftop_supermech_m12_final_boss_scripts.chase_fly_start, rooftop_supermech_m12_final_boss_scripts.chase_fly_wait, rooftop_supermech_m12_final_boss_scripts.chase_fly_end, rooftop_supermech_m12_final_boss_scripts.chase_fly_end_wait,
        rooftop_supermech_m12_final_boss_scripts.chase_fly_done, rooftop_supermech_m12_final_boss_scripts.chase_fly_pop, rooftop_supermech_m12_final_boss_scripts.close_range_low_health_pick, rooftop_supermech_m12_final_boss_scripts.charge_side_pick, rooftop_supermech_m12_final_boss_scripts.retreat_pick, rooftop_supermech_m12_final_boss_scripts.retreat_return,
        rooftop_supermech_m12_final_boss_scripts.scroll_attack_pick, rooftop_supermech_m12_final_boss_scripts.low_health_close_return, rooftop_supermech_m12_final_boss_scripts.far_range_low_health_pick, rooftop_supermech_m12_final_boss_scripts.charge_aligned_pick, rooftop_supermech_m12_final_boss_scripts.spread_pick, rooftop_supermech_m12_final_boss_scripts.fire_pick,
        rooftop_supermech_m12_final_boss_scripts.mid_fire_aligned_gate, rooftop_supermech_m12_final_boss_scripts.mid_fire_pop, rooftop_supermech_m12_final_boss_scripts.long_range_low_health_pick, rooftop_supermech_m12_final_boss_scripts.far_attack_roll, rooftop_supermech_m12_final_boss_scripts.far_spread_pick, rooftop_supermech_m12_final_boss_scripts.far_charge_pick,
        rooftop_supermech_m12_final_boss_scripts.far_attack_roll_return, rooftop_supermech_m12_final_boss_scripts.mid_range_pick, rooftop_supermech_m12_final_boss_scripts.default_reposition, rooftop_supermech_m12_final_boss_scripts.default_reposition_fire, rooftop_supermech_m12_final_boss_scripts.default_reposition_rest, rooftop_supermech_m12_final_boss_scripts.default_scroll_pick,
        rooftop_supermech_m12_final_boss_scripts.random_move_pick, rooftop_supermech_m12_final_boss_scripts.default_random_scroll_pick, rooftop_supermech_m12_final_boss_scripts.default_random_charge_pick, rooftop_supermech_m12_final_boss_scripts.default_random_return, rooftop_supermech_m12_final_boss_scripts.low_health_near_pick, rooftop_supermech_m12_final_boss_scripts.near_charge_pick,
        rooftop_supermech_m12_final_boss_scripts.near_aligned_roll, rooftop_supermech_m12_final_boss_scripts.near_scroll_turn, rooftop_supermech_m12_final_boss_scripts.aim_pick, rooftop_supermech_m12_final_boss_scripts.near_aligned_scroll, rooftop_supermech_m12_final_boss_scripts.near_pick_return, rooftop_supermech_m12_final_boss_scripts.close_pick,
        rooftop_supermech_m12_final_boss_scripts.close_range_charge_pick, rooftop_supermech_m12_final_boss_scripts.close_range_retreat_pick, rooftop_supermech_m12_final_boss_scripts.close_range_rest, rooftop_supermech_m12_final_boss_scripts.scroll_close_pick, rooftop_supermech_m12_final_boss_scripts.close_attack_pick_return, rooftop_supermech_m12_final_boss_scripts.mid_pick,
        rooftop_supermech_m12_final_boss_scripts.far_range_aligned_pick, rooftop_supermech_m12_final_boss_scripts.far_range_spread_pick, rooftop_supermech_m12_final_boss_scripts.far_range_fire_pick, rooftop_supermech_m12_final_boss_scripts.mid_fire_aligned_check, rooftop_supermech_m12_final_boss_scripts.mid_pick_return, rooftop_supermech_m12_final_boss_scripts.far_pick,
        rooftop_supermech_m12_final_boss_scripts.far_roll_pick, rooftop_supermech_m12_final_boss_scripts.far_roll_spread_turn, rooftop_supermech_m12_final_boss_scripts.far_roll_charge_pick, rooftop_supermech_m12_final_boss_scripts.far_roll_return, rooftop_supermech_m12_final_boss_scripts.mid_range_roll_pick, rooftop_supermech_m12_final_boss_scripts.roll_idle,
        rooftop_supermech_m12_final_boss_scripts.roll_fire, rooftop_supermech_m12_final_boss_scripts.roll_rest, rooftop_supermech_m12_final_boss_scripts.roll_scroll_pick, rooftop_supermech_m12_final_boss_scripts.roll_random_retreat, rooftop_supermech_m12_final_boss_scripts.roll_random_scroll_pick, rooftop_supermech_m12_final_boss_scripts.roll_random_charge_pick,
        rooftop_supermech_m12_final_boss_scripts.roll_random_return, rooftop_supermech_m12_final_boss_scripts.near_pick, rooftop_supermech_m12_final_boss_scripts.near_select_charge_pick, rooftop_supermech_m12_final_boss_scripts.near_scroll_entry, rooftop_supermech_m12_final_boss_scripts.near_random_scroll_pick, rooftop_supermech_m12_final_boss_scripts.near_aim_pick,
        rooftop_supermech_m12_final_boss_scripts.low_health_rest, rooftop_supermech_m12_final_boss_scripts.near_select_return, rooftop_supermech_m12_final_boss_scripts.intro_continue, rooftop_supermech_m12_final_boss_scripts.health_tier_select, rooftop_supermech_m12_final_boss_scripts.health_tier_flag, rooftop_supermech_m12_final_boss_scripts.flag_select_return,
        rooftop_supermech_m12_final_boss_scripts.attack_select, rooftop_supermech_m12_final_boss_scripts.attack_select_low_health,
    },
    /* D_80121598 */ rooftop_supermech_m12_final_boss_scripts.intro,
};

StateEntry D_8012159C[21] = {
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_IDLE, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_WALK_START, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_WALK_LOOP, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_HALT, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SCROLL_ATTACK, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SCROLL_SECOND_START, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SPREAD_ATTACK, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_SPREAD_ATTACK_SECOND, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_AIM_ATTACK, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_AIM_ATTACK_SECOND, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_AIM_RECOVER, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_AIM_SECOND_RECOVER, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_FIRE_BURST, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_FIRE_BURST_END, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_ALT_START, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_SECOND_ALT_START, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_CHARGE_SECOND, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_TURN_LONG_START, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_TURN_LONG_HOLD, 0},
    {0, ROOFTOP_SUPERMECH_M12_FINAL_BOSS_ANIM_TURN_LONG_RECOVER, 0},
};

s16 hit_mask_values[8] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
};

s16 particle_cursor_a[10] = {
    4, 0x258, 0x1000, 7, 0x259, 0x2000, -1, 0x25A,
    0x3000, 0,
};

s16 particle_cursor_b[10] = {
    3, 0x258, 0x1000, 4, 0x259, 0x1800, -1, 0x25A,
    0x2000, 0,
};

s16 particle_cursor_c[10] = {
    2, 0x258, 0x1000, 3, 0x259, 0x2000, -1, 0x25A,
    0x3000, 0,
};

s32 D_80121690 = 0;

#include "../stage/data/fade_red_fx_template.c"

RecTemplate blast_template_a = {3, 0xFF, 0xFF, 0xFF, 0, 0x14, 0x80000, 0x60000, -0x100, 0x40000};

#include "../stage/data/fx_owner_template_b.c"

#include "../stage/data/fx_rec34_params.c"

s16 spark_trail_template[10] = {
    6, 0x70, 0x4000, 3, 0x71, 0x2000, -1, 0x71,
    0x1000, 0,
};

s16 spark_particle_template[6] = {
    0x10, 0x235, -0x8000, -1, 0x234, 0x1000,
};

s16 fx_entry_keyframes[6] = {
    0x60, 0x200, 0x1000, -1, 0x201, 0x1000,
};

s16 view_nudge_table[18] = {
    3, 0, 3, 0, 2, 0, 2, 0,
    1, 0, 1, 0, -1, 0, 0x400, 0x400,
    0x400, 0,
};

SVECTOR fade_target_color = {0, 0x40, 0x200, 0};

SVECTOR D_8012174C = {0, -0x5E, -0xBD, 0};

SVECTOR D_80121754 = {0, -0x5E, 0xBD, 0};

BlendVec D_8012175C[128] = {
    {0, 0xFFF, 0, 0}, {0x490, 0xF1F, 0x289, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0x490, 0xF1F, 0x289, 0}, {0x4DF, 0xF36, 0xEE, 0}, {0x50D, 0xF2A, -0xB4, 0}, {0x515, 0xEFD, -0x255, 0},
    {0x4F0, 0xEB4, -0x3ED, 0}, {0x49B, 0xE51, -0x574, 0}, {0x417, 0xDD9, -0x6E2, 0}, {0x366, 0xD4F, -0x833, 0},
    {0x292, 0xCB4, -0x960, 0}, {0x1BD, 0xC06, -0xA68, 0}, {0x107, 0xB4A, -0xB4A, 0}, {0x85, 0xA88, -0xC08, 0},
    {0x44, 0x9CE, -0xCA3, 0}, {0x46, 0x924, -0xD20, 0}, {0x87, 0x88A, -0xD84, 0}, {0xFE, 0x7F9, -0xDD5, 0},
    {0x1ED, 0x74E, -0xE1A, 0}, {0x340, 0x7AB, -0xDA8, 0}, {0x51A, 0x764, -0xD3D, 0}, {0x30A, 0xCCD, -0x91A, 0},
    {0x288, 0xF94, -0x29F, 0}, {-0x5A, 0xFCA, 0x28F, 0}, {0x487, 0xE7F, 0x507, 0}, {0x5F4, 0xD9B, 0x5F2, 0},
    {0x685, 0xD0E, 0x68E, 0}, {0x684, 0xCDE, 0x6EB, 0}, {0x61B, 0xD01, 0x709, 0}, {0x571, 0xD5F, 0x6E4, 0},
    {0x4A9, 0xDDC, 0x67D, 0}, {0x3E3, 0xE60, 0x5D9, 0}, {0x33F, 0xED6, 0x507, 0}, {0x2DC, 0xF30, 0x423, 0},
    {0x2DD, 0xF63, 0x34F, 0}, {0x364, 0xF66, 0x2B6, 0}, {0x490, 0xF1F, 0x289, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0x490, 0xF1F, 0x289, 0}, {0x48C, 0xF25, 0x26A, 0}, {0x48B, 0xF32, 0x215, 0}, {0x4A4, 0xF3A, 0x192, 0},
    {0x4ED, 0xF31, 0xED, 0}, {0x57A, 0xF08, 0x2F, 0}, {0x657, 0xEAD, -0x9B, 0}, {0x78A, 0xE0A, -0x169, 0},
    {0x911, 0xD00, -0x22C, 0}, {0xABD, 0xB82, -0x2DB, 0}, {0xC48, 0x9AA, -0x36D, 0}, {0xD80, 0x7AB, -0x3DC, 0},
    {0xE54, 0x5C9, -0x424, 0}, {0xE88, 0x557, -0x408, 0}, {0xE13, 0x6AA, -0x3AA, 0}, {0xD83, 0x803, -0x306, 0},
    {0xCAF, 0x991, -0x1E5, 0}, {0xA81, 0xC10, -0x43, 0}, {0x6A7, 0xE6E, 0x1DB, 0}, {0x18A, 0xF55, 0x44B, 0},
    {-0x378, 0xE24, 0x6A0, 0}, {-0x6F6, 0xBB2, 0x868, 0}, {-0x8D6, 0x969, 0x972, 0}, {-0x997, 0x831, 0x9D7, 0},
    {-0x97E, 0x840, 0x9E3, 0}, {-0x8D3, 0x924, 0x9B8, 0}, {-0x7A2, 0xA8D, 0x94A, 0}, {-0x5F9, 0xC23, 0x88A, 0},
    {-0x3F8, 0xD90, 0x780, 0}, {-0x1D0, 0xE99, 0x64A, 0}, {0x41, 0xF2B, 0x514, 0}, {0x20B, 0xF59, 0x405, 0},
    {0x367, 0xF4C, 0x337, 0}, {0x443, 0xF2E, 0x2B6, 0}, {0x490, 0xF1F, 0x289, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
};

BlendVec D_80121B5C[128] = {
    {0, -0xFFF, 0, 0}, {-0x490, 0xF1F, 0x289, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {-0x490, 0xF1F, 0x289, 0}, {-0x48C, 0xF25, 0x26A, 0}, {-0x48B, 0xF32, 0x215, 0}, {-0x4A4, 0xF3A, 0x192, 0},
    {-0x4ED, 0xF31, 0xED, 0}, {-0x57A, 0xF08, 0x2F, 0}, {-0x657, 0xEAD, -0x9B, 0}, {-0x789, 0xE0A, -0x169, 0},
    {-0x902, 0xD0A, -0x22C, 0}, {-0xA91, 0xBAB, -0x2DB, 0}, {-0xC02, 0xA01, -0x36B, 0}, {-0xD30, 0x833, -0x3D8, 0},
    {-0xE0C, 0x673, -0x41F, 0}, {-0xE49, 0x5FC, -0x402, 0}, {-0xDDF, 0x717, -0x3A5, 0}, {-0xD83, 0x803, -0x306, 0},
    {-0xCF0, 0x936, -0x1EA, 0}, {-0xAEC, 0xBAF, -0x48, 0}, {-0x715, 0xE39, 0x1D9, 0}, {-0x1D2, 0xF4D, 0x44D, 0},
    {0x363, 0xE29, 0x6A1, 0}, {0x6F6, 0xBB2, 0x868, 0}, {0x8D6, 0x969, 0x972, 0}, {0x997, 0x831, 0x9D7, 0},
    {0x97E, 0x841, 0x9E3, 0}, {0x8D3, 0x924, 0x9B8, 0}, {0x7A2, 0xA8D, 0x94A, 0}, {0x5F9, 0xC23, 0x88A, 0},
    {0x3F8, 0xD90, 0x780, 0}, {0x1D0, 0xE99, 0x64A, 0}, {-0x41, 0xF2B, 0x514, 0}, {-0x20B, 0xF59, 0x405, 0},
    {-0x367, 0xF4C, 0x337, 0}, {-0x443, 0xF2E, 0x2B6, 0}, {-0x490, 0xF1F, 0x289, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {-0x490, 0xF1F, 0x289, 0}, {-0x4DF, 0xF36, 0xEE, 0}, {-0x50D, 0xF2A, -0xB4, 0}, {-0x515, 0xEFD, -0x255, 0},
    {-0x4F0, 0xEB4, -0x3ED, 0}, {-0x49B, 0xE51, -0x574, 0}, {-0x417, 0xDD9, -0x6E2, 0}, {-0x366, 0xD4F, -0x833, 0},
    {-0x284, 0xCB7, -0x960, 0}, {-0x190, 0xC0D, -0xA67, 0}, {-0xB8, 0xB51, -0xB49, 0}, {-0x1E, 0xA8D, -0xC06, 0},
    {0x2A, 0x9D1, -0xCA2, 0}, {0x1B, 0x927, -0xD1F, 0}, {-0x4A, 0x88F, -0xD83, 0}, {-0xFE, 0x7F9, -0xDD5, 0},
    {-0x21A, 0x73D, -0xE1C, 0}, {-0x37B, 0x789, -0xDAD, 0}, {-0x549, 0x739, -0xD42, 0}, {-0x340, 0xCBD, -0x91D, 0},
    {-0x29D, 0xF90, -0x2A0, 0}, {0x5A, 0xFCA, 0x28F, 0}, {-0x487, 0xE7F, 0x507, 0}, {-0x5F4, 0xD9B, 0x5F2, 0},
    {-0x685, 0xD0E, 0x68E, 0}, {-0x684, 0xCDE, 0x6EB, 0}, {-0x61B, 0xD01, 0x709, 0}, {-0x571, 0xD5F, 0x6E4, 0},
    {-0x4A9, 0xDDC, 0x67D, 0}, {-0x3E3, 0xE60, 0x5D9, 0}, {-0x33F, 0xED6, 0x507, 0}, {-0x2DC, 0xF30, 0x423, 0},
    {-0x2DD, 0xF63, 0x34F, 0}, {-0x364, 0xF66, 0x2B6, 0}, {-0x490, 0xF1F, 0x289, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
    {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0}, {0, 0, 0x1000, 0},
};

s16 D_80121F5C[512] = {
    0x28, -0xA0, 0x18, 0, 0xC5, -0x89, 0xD9, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0xC5, -0x89, 0xD9, 0, 0xC2, -0x88, 0xEB, 0,
    0xC0, -0x84, 0xFE, 0, 0xBF, -0x7E, 0x111, 0,
    0xC1, -0x74, 0x123, 0, 0xC4, -0x66, 0x135, 0,
    0xC8, -0x53, 0x145, 0, 0xCB, -0x3A, 0x154, 0,
    0xCD, -0x1D, 0x161, 0, 0xCC, 3, 0x16D, 0,
    0xC5, 0x25, 0x177, 0, 0xB9, 0x45, 0x181, 0,
    0xA9, 0x61, 0x189, 0, 0x97, 0x78, 0x190, 0,
    0x87, 0x8A, 0x197, 0, 0x7B, 0x96, 0x19D, 0,
    0x7D, 0x98, 0x1A2, 0, 0x8D, 0x7B, 0x1A2, 0,
    0x9F, 0x54, 0x1A0, 0, 0xD5, -0x2E, 0x17E, 0,
    0xE2, -0xB0, 0x12F, 0, 0xE4, -0xEA, 0xDB, 0,
    0x9C, -0xFA, 0xAC, 0, 0x8A, -0xF8, 0x9E, 0,
    0x86, -0xF2, 0x97, 0, 0x8D, -0xEB, 0x96, 0,
    0x9B, -0xE1, 0x9A, 0, 0xAC, -0xD6, 0xA1, 0,
    0xBE, -0xC8, 0xAA, 0, 0xCD, -0xB9, 0xB4, 0,
    0xD7, -0xAA, 0xBE, 0, 0xDC, -0x9C, 0xC7, 0,
    0xDB, -0x92, 0xCF, 0, 0xD4, -0x8B, 0xD5, 0,
    0xC5, -0x89, 0xD9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0xC5, -0x89, 0xD9, 0, 0xC5, -0x89, 0xD9, 0,
    0xC5, -0x8B, 0xD9, 0, 0xC3, -0x8F, 0xDA, 0,
    0xBE, -0x96, 0xDC, 0, 0xB5, -0xA0, 0xE0, 0,
    0xA8, -0xAD, 0xE6, 0, 0x95, -0xBC, 0xEE, 0,
    0x7A, -0xCC, 0xF8, 0, 0x59, -0xDA, 0x103, 0,
    0x35, -0xE3, 0x10F, 0, 0x13, -0xE6, 0x11A, 0,
    -9, -0xE4, 0x124, 0, -0x10, -0xE9, 0x12F, 0,
    1, -0xF7, 0x135, 0, 0x13, -0x100, 0x12A, 0,
    0x2D, -0x100, 0x10D, 0, 0x61, -0xF1, 0xE9, 0,
    0xA2, -0xC9, 0xC4, 0, 0xDE, -0x83, 0xA6, 0,
    0x102, -0x2F, 0x95, 0, 0x10E, 0x19, 0x93, 0,
    0x10F, 0x48, 0x9A, 0, 0x10F, 0x5D, 0xA1, 0,
    0x10F, 0x5C, 0xA4, 0, 0x10F, 0x4D, 0xA2, 0,
    0x10F, 0x32, 0xA0, 0, 0x10B, 0x11, 0x9F, 0,
    0x103, -0x12, 0xA2, 0, 0xF7, -0x35, 0xAA, 0,
    0xEA, -0x53, 0xB5, 0, 0xDC, -0x6B, 0xC2, 0,
    0xD0, -0x7B, 0xCD, 0, 0xC8, -0x85, 0xD6, 0,
    0xC5, -0x89, 0xD9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

s16 D_8012235C[512] = {
    0x28, -0xA0, -3, 0, 0xC5, -0x84, 0xBD, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0xC5, -0x84, 0xBD, 0, 0xC2, -0x86, 0xCF, 0,
    0xC1, -0x86, 0xE3, 0, 0xC1, -0x83, 0xF6, 0,
    0xC3, -0x7C, 0x109, 0, 0xC7, -0x71, 0x11B, 0,
    0xCC, -0x60, 0x12D, 0, 0xD2, -0x4A, 0x13D, 0,
    0xD6, -0x2E, 0x14C, 0, 0xD7, -13, 0x15A, 0,
    0xD2, 0x13, 0x167, 0, 0xC9, 0x34, 0x172, 0,
    0xBB, 0x50, 0x17C, 0, 0xAC, 0x68, 0x186, 0,
    0x9C, 0x7A, 0x18E, 0, 0x90, 0x86, 0x195, 0,
    0x91, 0x85, 0x19B, 0, 0x9F, 0x67, 0x19B, 0,
    0xAC, 0x3C, 0x198, 0, 0xE1, -0x3F, 0x16B, 0,
    0xE9, -0xB5, 0x115, 0, 0xE7, -0xE6, 0xC0, 0,
    0x9F, -0xF2, 0x91, 0, 0x8C, -0xEE, 0x84, 0,
    0x89, -0xE7, 0x7E, 0, 0x90, -0xDF, 0x7D, 0,
    0x9D, -0xD5, 0x81, 0, 0xAE, -0xCA, 0x88, 0,
    0xBE, -0xBC, 0x90, 0, 0xCC, -0xAE, 0x9A, 0,
    0xD6, -0xA0, 0xA3, 0, 0xDA, -0x94, 0xAC, 0,
    0xD9, -0x8B, 0xB4, 0, 0xD2, -0x86, 0xBA, 0,
    0xC5, -0x84, 0xBD, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0xC5, -0x84, 0xBD, 0, 0xC5, -0x85, 0xBD, 0,
    0xC3, -0x87, 0xBE, 0, 0xC0, -0x8C, 0xBF, 0,
    0xBA, -0x93, 0xC1, 0, 0xB0, -0x9E, 0xC5, 0,
    0xA1, -0xAB, 0xCB, 0, 0x8D, -0xBB, 0xD3, 0,
    0x72, -0xCB, 0xDD, 0, 0x50, -0xD9, 0xE9, 0,
    0x2D, -0xE1, 0xF5, 0, 10, -0xE4, 0x100, 0,
    -0x12, -0xE3, 0x10A, 0, -0x17, -0xEA, 0x114, 0,
    -3, -0xFB, 0x11A, 0, 15, -0x104, 0x10F, 0,
    0x29, -0x100, 0xF2, 0, 0x5C, -0xEE, 0xCE, 0,
    0x9B, -0xC2, 0xAA, 0, 0xD4, -0x7C, 0x8D, 0,
    0xF5, -0x27, 0x7D, 0, 0x100, 0x21, 0x7C, 0,
    0x101, 0x51, 0x83, 0, 0x101, 0x67, 0x8B, 0,
    0x102, 0x67, 0x8E, 0, 0x103, 0x58, 0x8C, 0,
    0x103, 0x3E, 0x89, 0, 0x100, 0x1C, 0x88, 0,
    0xFA, -7, 0x8A, 0, 0xF0, -0x2B, 0x91, 0,
    0xE5, -0x4A, 0x9B, 0, 0xD9, -0x63, 0xA7, 0,
    0xCF, -0x75, 0xB2, 0, 0xC8, -0x80, 0xBA, 0,
    0xC5, -0x84, 0xBD, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

s16 D_8012275C[512] = {
    0x28, -0xA0, -0x1F, 0, 0xC5, -0x7F, 0xA2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0xC5, -0x7F, 0xA2, 0, 0xC3, -0x85, 0xB4, 0,
    0xC2, -0x88, 0xC7, 0, 0xC3, -0x88, 0xDA, 0,
    0xC6, -0x84, 0xEE, 0, 0xCB, -0x7B, 0x102, 0,
    0xD1, -0x6D, 0x115, 0, 0xD8, -0x59, 0x127, 0,
    0xDF, -0x3E, 0x138, 0, 0xE2, -0x1F, 0x148, 0,
    0xE0, 1, 0x156, 0, 0xD9, 0x22, 0x164, 0,
    0xCE, 0x40, 0x170, 0, 0xC0, 0x58, 0x17B, 0,
    0xB1, 0x6A, 0x185, 0, 0xA6, 0x76, 0x18D, 0,
    0xA5, 0x73, 0x194, 0, 0xB0, 0x53, 0x193, 0,
    0xB9, 0x25, 0x190, 0, 0xEC, -0x4F, 0x158, 0,
    0xF0, -0xBB, 0xFA, 0, 0xEB, -0xE1, 0xA5, 0,
    0xA1, -0xE9, 0x77, 0, 0x8F, -0xE4, 0x6A, 0,
    0x8C, -0xDB, 0x64, 0, 0x93, -0xD3, 0x64, 0,
    0xA0, -0xC9, 0x68, 0, 0xB0, -0xBE, 0x6F, 0,
    0xBF, -0xB1, 0x77, 0, 0xCC, -0xA4, 0x80, 0,
    0xD4, -0x97, 0x89, 0, 0xD8, -0x8D, 0x92, 0,
    0xD7, -0x85, 0x99, 0, 0xD1, -0x81, 0x9F, 0,
    0xC5, -0x7F, 0xA2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0xC5, -0x7F, 0xA2, 0, 0xC4, -0x80, 0xA2, 0,
    0xC2, -0x83, 0xA2, 0, 0xBD, -0x88, 0xA3, 0,
    0xB6, -0x90, 0xA5, 0, 0xAA, -0x9C, 0xA9, 0,
    0x9A, -0xAA, 0xB0, 0, 0x85, -0xB9, 0xB8, 0,
    0x69, -0xCA, 0xC3, 0, 0x48, -0xD7, 0xCE, 0,
    0x24, -0xE0, 0xDA, 0, 2, -0xE3, 0xE5, 0,
    -0x1A, -0xE2, 0xEF, 0, -0x1E, -0xEB, 0xF9, 0,
    -9, -0xFF, 0xFE, 0, 11, -0x107, 0xF3, 0,
    0x25, -0x100, 0xD6, 0, 0x57, -0xEA, 0xB3, 0,
    0x94, -0xBC, 0x8F, 0, 0xCA, -0x74, 0x74, 0,
    0xE9, -0x1F, 0x66, 0, 0xF3, 0x29, 0x65, 0,
    0xF3, 0x5A, 0x6D, 0, 0xF3, 0x71, 0x75, 0,
    0xF4, 0x72, 0x78, 0, 0xF6, 0x63, 0x76, 0,
    0xF7, 0x49, 0x72, 0, 0xF6, 0x28, 0x70, 0,
    0xF1, 3, 0x72, 0, 0xEA, -0x21, 0x78, 0,
    0xE0, -0x42, 0x81, 0, 0xD6, -0x5C, 0x8C, 0,
    0xCD, -0x6F, 0x97, 0, 0xC7, -0x7B, 0x9F, 0,
    0xC5, -0x7F, 0xA2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

s16 D_80122B5C[512] = {
    0x28, 0xA0, -0x1F, 0, -0xC5, -0x7F, 0xA2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -0xC5, -0x7F, 0xA2, 0, -0xC4, -0x80, 0xA2, 0,
    -0xC2, -0x83, 0xA2, 0, -0xBD, -0x88, 0xA3, 0,
    -0xB6, -0x90, 0xA5, 0, -0xAA, -0x9C, 0xA9, 0,
    -0x9A, -0xAA, 0xB0, 0, -0x85, -0xB9, 0xB8, 0,
    -0x6A, -0xC9, 0xC3, 0, -0x4B, -0xD6, 0xCE, 0,
    -0x2B, -0xDF, 0xDA, 0, -12, -0xE3, 0xE5, 0,
    14, -0xE3, 0xEF, 0, 0x13, -0xEC, 0xF9, 0,
    0, -0xFF, 0xFF, 0, -11, -0x107, 0xF3, 0,
    -0x1E, -0x101, 0xD6, 0, -0x4E, -0xED, 0xB2, 0,
    -0x8E, -0xC0, 0x8F, 0, -0xC7, -0x77, 0x74, 0,
    -0xE9, -0x20, 0x66, 0, -0xF3, 0x29, 0x65, 0,
    -0xF3, 0x5A, 0x6D, 0, -0xF3, 0x71, 0x75, 0,
    -0xF4, 0x72, 0x78, 0, -0xF6, 0x63, 0x76, 0,
    -0xF7, 0x49, 0x72, 0, -0xF6, 0x28, 0x70, 0,
    -0xF1, 3, 0x72, 0, -0xEA, -0x21, 0x78, 0,
    -0xE0, -0x42, 0x81, 0, -0xD6, -0x5C, 0x8C, 0,
    -0xCD, -0x6F, 0x97, 0, -0xC7, -0x7B, 0x9F, 0,
    -0xC5, -0x7F, 0xA2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -0xC5, -0x7F, 0xA2, 0, -0xC3, -0x85, 0xB4, 0,
    -0xC2, -0x88, 0xC7, 0, -0xC3, -0x88, 0xDA, 0,
    -0xC6, -0x84, 0xEE, 0, -0xCB, -0x7B, 0x102, 0,
    -0xD1, -0x6D, 0x115, 0, -0xD8, -0x59, 0x127, 0,
    -0xDF, -0x3D, 0x138, 0, -0xE2, -0x1C, 0x148, 0,
    -0xE0, 8, 0x157, 0, -0xD8, 0x2B, 0x164, 0,
    -0xCB, 0x49, 0x170, 0, -0xBC, 0x61, 0x17B, 0,
    -0xAE, 0x70, 0x185, 0, -0xA6, 0x76, 0x18D, 0,
    -0xA8, 0x6F, 0x194, 0, -0xB3, 0x4C, 0x193, 0,
    -0xBA, 0x20, 0x18F, 0, -0xEB, -0x53, 0x157, 0,
    -0xEF, -0xBC, 0xFA, 0, -0xEB, -0xE1, 0xA5, 0,
    -0xA1, -0xE9, 0x77, 0, -0x8F, -0xE4, 0x6A, 0,
    -0x8C, -0xDB, 0x64, 0, -0x93, -0xD3, 0x64, 0,
    -0xA0, -0xC9, 0x68, 0, -0xB0, -0xBE, 0x6F, 0,
    -0xBF, -0xB1, 0x77, 0, -0xCC, -0xA4, 0x80, 0,
    -0xD4, -0x97, 0x89, 0, -0xD8, -0x8D, 0x92, 0,
    -0xD7, -0x85, 0x99, 0, -0xD1, -0x81, 0x9F, 0,
    -0xC5, -0x7F, 0xA2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

s16 D_80122F5C[512] = {
    0x28, 0xA0, -3, 0, -0xC5, -0x84, 0xBD, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -0xC5, -0x84, 0xBD, 0, -0xC5, -0x85, 0xBD, 0,
    -0xC3, -0x87, 0xBE, 0, -0xC0, -0x8C, 0xBF, 0,
    -0xBA, -0x93, 0xC1, 0, -0xB0, -0x9E, 0xC5, 0,
    -0xA1, -0xAB, 0xCB, 0, -0x8D, -0xBB, 0xD3, 0,
    -0x73, -0xCA, 0xDD, 0, -0x54, -0xD7, 0xE9, 0,
    -0x33, -0xE0, 0xF5, 0, -0x14, -0xE4, 0x100, 0,
    6, -0xE3, 0x10A, 0, 12, -0xEB, 0x114, 0,
    -4, -0xFB, 0x11A, 0, -15, -0x104, 0x10F, 0,
    -0x22, -0x101, 0xF2, 0, -0x53, -0xF1, 0xCD, 0,
    -0x95, -0xC7, 0xA9, 0, -0xD1, -0x7F, 0x8C, 0,
    -0xF5, -0x28, 0x7D, 0, -0x100, 0x21, 0x7C, 0,
    -0x101, 0x51, 0x83, 0, -0x101, 0x67, 0x8B, 0,
    -0x102, 0x67, 0x8E, 0, -0x103, 0x58, 0x8C, 0,
    -0x103, 0x3E, 0x89, 0, -0x100, 0x1C, 0x88, 0,
    -0xFA, -7, 0x8A, 0, -0xF0, -0x2B, 0x91, 0,
    -0xE5, -0x4A, 0x9B, 0, -0xD9, -0x63, 0xA7, 0,
    -0xCF, -0x75, 0xB2, 0, -0xC8, -0x80, 0xBA, 0,
    -0xC5, -0x84, 0xBD, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -0xC5, -0x84, 0xBD, 0, -0xC2, -0x86, 0xCF, 0,
    -0xC1, -0x86, 0xE3, 0, -0xC1, -0x83, 0xF6, 0,
    -0xC3, -0x7C, 0x109, 0, -0xC7, -0x71, 0x11B, 0,
    -0xCC, -0x60, 0x12D, 0, -0xD2, -0x4A, 0x13D, 0,
    -0xD6, -0x2D, 0x14D, 0, -0xD7, -10, 0x15A, 0,
    -0xD2, 0x19, 0x167, 0, -0xC7, 0x3B, 0x173, 0,
    -0xB8, 0x59, 0x17D, 0, -0xA7, 0x70, 0x186, 0,
    -0x99, 0x7F, 0x18E, 0, -0x90, 0x86, 0x195, 0,
    -0x94, 0x82, 0x19B, 0, -0xA2, 0x61, 0x19A, 0,
    -0xAE, 0x37, 0x197, 0, -0xDF, -0x43, 0x16B, 0,
    -0xE8, -0xB7, 0x115, 0, -0xE7, -0xE6, 0xC0, 0,
    -0x9F, -0xF2, 0x91, 0, -0x8C, -0xEE, 0x84, 0,
    -0x89, -0xE7, 0x7E, 0, -0x90, -0xDF, 0x7D, 0,
    -0x9D, -0xD5, 0x81, 0, -0xAE, -0xCA, 0x88, 0,
    -0xBE, -0xBC, 0x90, 0, -0xCC, -0xAE, 0x9A, 0,
    -0xD6, -0xA0, 0xA3, 0, -0xDA, -0x94, 0xAC, 0,
    -0xD9, -0x8B, 0xB4, 0, -0xD2, -0x86, 0xBA, 0,
    -0xC5, -0x84, 0xBD, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

s16 D_8012335C[512] = {
    0x28, 0xA0, 0x18, 0, -0xC5, -0x89, 0xD9, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -0xC5, -0x89, 0xD9, 0, -0xC5, -0x89, 0xD9, 0,
    -0xC5, -0x8B, 0xD9, 0, -0xC3, -0x8F, 0xDA, 0,
    -0xBE, -0x96, 0xDC, 0, -0xB5, -0xA0, 0xE0, 0,
    -0xA8, -0xAD, 0xE6, 0, -0x95, -0xBC, 0xEE, 0,
    -0x7B, -0xCC, 0xF8, 0, -0x5D, -0xD9, 0x103, 0,
    -0x3C, -0xE1, 0x10F, 0, -0x1C, -0xE5, 0x11B, 0,
    -1, -0xE4, 0x124, 0, 5, -0xE9, 0x12F, 0,
    -9, -0xF7, 0x135, 0, -0x13, -0x100, 0x12A, 0,
    -0x26, -0x101, 0x10D, 0, -0x58, -0xF5, 0xE9, 0,
    -0x9C, -0xCE, 0xC3, 0, -0xDB, -0x87, 0xA5, 0,
    -0x102, -0x30, 0x95, 0, -0x10E, 0x19, 0x93, 0,
    -0x10F, 0x48, 0x9A, 0, -0x10F, 0x5D, 0xA1, 0,
    -0x10F, 0x5C, 0xA4, 0, -0x10F, 0x4D, 0xA2, 0,
    -0x10F, 0x32, 0xA0, 0, -0x10B, 0x11, 0x9F, 0,
    -0x103, -0x12, 0xA2, 0, -0xF7, -0x35, 0xAA, 0,
    -0xEA, -0x53, 0xB5, 0, -0xDC, -0x6B, 0xC2, 0,
    -0xD0, -0x7B, 0xCD, 0, -0xC8, -0x85, 0xD6, 0,
    -0xC5, -0x89, 0xD9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -0xC5, -0x89, 0xD9, 0, -0xC2, -0x88, 0xEB, 0,
    -0xC0, -0x84, 0xFE, 0, -0xBF, -0x7E, 0x111, 0,
    -0xC1, -0x74, 0x123, 0, -0xC4, -0x66, 0x135, 0,
    -0xC8, -0x53, 0x145, 0, -0xCB, -0x3A, 0x154, 0,
    -0xCE, -0x1C, 0x161, 0, -0xCC, 6, 0x16D, 0,
    -0xC4, 0x2A, 0x178, 0, -0xB6, 0x4C, 0x181, 0,
    -0xA5, 0x69, 0x189, 0, -0x92, 0x7F, 0x191, 0,
    -0x83, 0x8E, 0x197, 0, -0x7B, 0x96, 0x19D, 0,
    -0x81, 0x94, 0x1A1, 0, -0x92, 0x77, 0x1A1, 0,
    -0xA2, 0x4F, 0x19F, 0, -0xD4, -0x32, 0x17E, 0,
    -0xE1, -0xB1, 0x12F, 0, -0xE4, -0xEA, 0xDB, 0,
    -0x9C, -0xFA, 0xAC, 0, -0x8A, -0xF8, 0x9E, 0,
    -0x86, -0xF2, 0x97, 0, -0x8D, -0xEB, 0x96, 0,
    -0x9B, -0xE1, 0x9A, 0, -0xAC, -0xD6, 0xA1, 0,
    -0xBE, -0xC8, 0xAA, 0, -0xCD, -0xB9, 0xB4, 0,
    -0xD7, -0xAA, 0xBE, 0, -0xDC, -0x9C, 0xC7, 0,
    -0xDB, -0x92, 0xCF, 0, -0xD4, -0x8B, 0xD5, 0,
    -0xC5, -0x89, 0xD9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

BlendVec blend_vec_null = {0, 0, 0x1000, 0};

BlendVec blend_base_null = {0, 0, 0, 0};

BlendVec *pose_blend_table[6] = {
    D_8012175C, D_8012175C, D_8012175C, D_80121B5C, D_80121B5C, D_80121B5C,
};

s16 *pose_from_table[6] = {
    D_80121F5C, D_8012235C, D_8012275C, D_80122B5C, D_80122F5C, D_8012335C,
};

s16 *pose_to_table[6] = {
    D_8012235C, D_8012235C, D_8012235C, D_80122F5C, D_80122F5C, D_80122F5C,
};

u32 D_801237B4[3] = {
    0x02420018, 0xFFFF1000, 0x40000243,
};

s32 burst_particle_template[5] = {
    0x2180004, 0x32800, 0x30000219, 0x21AFFFF, 0x2000,
};

s16 shot_offset_table[24] = {
    0x39, -0x6D, 0x27, 0, 0x27, -0x6D, 0x31, 0,
    0x39, -0x6D, 0x3B, 0, -0x39, -0x6D, 0x3B, 0,
    -0x27, -0x6D, 0x31, 0, -0x39, -0x6D, 0x27, 0,
};

u32 shot_rot_default[2] = {
    0x00000000, 0x00000000,
};

ScriptCallEntry D_8012380C[9] = {
    {NULL, 0}, {cam_track_start_both, 0}, {script_op_nop, 0}, {shot_fire_pair, 0},
    {script_op_mode, 0}, {obj_start_loop_sound, 0}, {obj_stop_loop_sound, 0}, {sound_start_on_owner, 0},
    {sound_stop_pair, 0},
};

struct SupermechM12BossScripts {
    s16 start[8];
    s16 cycle[2];
    s16 fire_start[2];
    s16 fire_windup[4];
    s16 fire_loop[8];
    s16 *table[5];
} supermech_m12_boss_scripts = {
    /* start */ {
        NEXT_STATE(SUPERMECH_M12_BOSS_STATE_IDLE),
        WAIT(240),
        SUPERMECH_M12_BOSS_MODE, 1,
        JUMP(SUPERMECH_M12_BOSS_CYCLE),
    },
    /* cycle */ {
        JUMP(SUPERMECH_M12_BOSS_FIRE_START),
    },
    /* fire_start */ {
        SET_COUNTER(16),
    },
    /* fire_windup */ {
        WAIT(64),
        SUPERMECH_M12_BOSS_START_LOOP_SOUND,
    },
    /* fire_loop */ {
        WAIT(4),
        SUPERMECH_M12_BOSS_SHOT_FIRE_PAIR,
        LOOP(SUPERMECH_M12_BOSS_FIRE_LOOP),
        SUPERMECH_M12_BOSS_STOP_LOOP_SOUND,
        JUMP(SUPERMECH_M12_BOSS_CYCLE),
    },
    /* table */ {
        supermech_m12_boss_scripts.start, supermech_m12_boss_scripts.cycle, supermech_m12_boss_scripts.fire_start, supermech_m12_boss_scripts.fire_windup, supermech_m12_boss_scripts.fire_loop,
    },
};

struct SupermechM12BossAnims {
    s16 idle[4];
    s16 *table[1];
} supermech_m12_boss_anims = {
    /* idle */ {
        STEP(2, 496),
        GOTO(SUPERMECH_M12_BOSS_ANIM_IDLE),
    },
    /* table */ {
        supermech_m12_boss_anims.idle,
    },
};

s16 *D_801238A4 = supermech_m12_boss_start;

StateEntry D_801238A8[1] = {
    {0, SUPERMECH_M12_BOSS_ANIM_IDLE, 0},
};

s16 D_801238B0[8] = {
    0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000,
};

FxOffset cam_track_offs[2] = {
    {-0x9C, 0x84, -0x2D, 0}, {0x9C, 0x84, -0x2D, 0},
};

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

u8 *D_80123940[3] = {
    str_msgs_spr_clt, str_msgs_spr_grc, str_msgs_spr_so3,
};

ScanEntry enemy_msgs_scan_entry = {{(s32)mission_state_reset, 0}, d_80117914, 0, 0, (s32)D_80123940};

s32 boss_slot_index[3] = {
    -1, -1, -1,
};

ScanEntry D_80123970 = {{(s32)func_800CCA24, (s32)ctrl_spawn}, boss_slot_index, 0, 0, 0};

s32 D_80123988[21] = {
    5, (s32)0xFFFCDE96, -0xC10, 0x153E, 0, (s32)0xFFFCF571,
    -0xC10, -0x125D, 0x4B, (s32)0xFFFD19AA, -0x6D0, -0xBDA,
    0x71, (s32)0xFFFD22D0, -0x4E2, 0x883, 0x91, (s32)0xFFFD1DF6,
    -0x490, 0xC3F, 0xC3,
};

s32 D_801239DC[5] = {
    1, (s32)0xFFFD1E0A, -0x580, 0x7CD, 0,
};

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

#include "../stage/data/ratan_tbl.c"

s16 video_mode_id = 0;

#include "../stage/data/debug_cam_speed_table.c"

#include "../stage/data/pause_prev_work_area.c"

#include "../stage/data/vblank_task_handle.c"

u32 D_80128394[8] = {
    0x0006FFFF, 0x00070000, 0xFFFF0002, 0x00000001, 0x00050004, 0x0006FFFF,
    0x00040003, 0xFFFF0002,
};

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_80128DB4[5] = {0};

#include "../stage/data/d_8011D324.c"

#include "../stage/data/tint_scale_r.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_80129EF8[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_8012A518 = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

s32 prox_blend_base = 0;

s32 cam_trigger_inside = 0;

s32 loop_sound_id = 0;

s32 trail_write_index = 0;

s32 supermech_trail_count = 0;

s32 sound_pair_active = 0;

s32 sound_fade_out_flag = 0;

s32 sound_pair_a_handle = 0;

s32 sound_pair_b_handle = 0;

u32 D_8012B954 = 0x00000000;

s32 sound_pair_volume = 0;

s32 sound_pair_volume_step = 0;

#include "../stage/data/value_queue_index.c"

s16 shot_aim_a_pitch = 0;

s16 shot_aim_a_yaw = 0;

s16 shot_aim_a_roll = 0;

s16 shot_aim_b_pitch = 0;

s16 shot_aim_b_yaw = 0;

s16 shot_aim_b_roll = 0;

s32 obj_loop_sound_id = 0;

s32 supermech_trail_parity = 0;

s32 bounds_x_min = 0;

s32 bounds_x_max = 0;

s32 bounds_z_min = 0;

s32 bounds_z_max = 0;

s32 stage_active_flag = 0;

s32 particle_spawn_param = 0;

ObjectMode *fade_target_obj = NULL;

s32 spark_serial = 0;

s32 boss_state = 0;

s32 obj_loop_sound_handle = 0;

s32 owner_sound_handles[2] = {
    0, 0,
};

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

s32 D_8012B9F0 = 0;

s32 fly_active_flag = 0;

s32 scene_active_flag = 0;

s32 fall_height = 0;

s32 fall_sound_timer = 0;

s16 fly_target_pos = 0;

s16 D_8012BA06 = 0;

s16 D_8012BA08 = 0;

s32 fly_cam_speed = 0;

u32 fly_target_rot[2] = {
    0x00000000, 0x00000000,
};

s32 area_load_flag = 0;

u32 D_8012BA1C = 0x00000000;

s32 alarm_sound_handle = 0;

s32 alarm_armed_flag = 0;

s32 alarm2_sound_handle = 0;

#include "../stage/data/frame_work_area.c"

#include "../stage/data/model_slot_count.c"

u32 D_8012BAE0 = 0x00000000;

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

u32 D_8012BB7C = 0x00000000;

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

s32 scene_rot_data[2] = {
    0, 0,
};

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

u32 D_8012BFFC = 0x00000000;

/* labels inside the objects above */
__asm__(".globl D_8011EF37\n.set D_8011EF37, ripple_fx_params+0x3\n"
        ".globl proximity_sensor_offsets\n.set proximity_sensor_offsets, prox_cells+0x6\n"
        ".globl proximity_sensor_range_z\n.set proximity_sensor_range_z, prox_cells+0xE\n"
        ".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl D_8012A51E\n.set D_8012A51E, texture_image+0x2\n"
        ".globl pad1_pressed\n.set pad1_pressed, pad1+0x2\n"
        ".globl D_8012BFE2\n.set D_8012BFE2, scale_vec+0x2\n"
        ".globl D_8011EF36\n.set D_8011EF36, ripple_fx_params+0x2\n"
        ".globl D_8011EF35\n.set D_8011EF35, ripple_fx_params+0x1\n"
        ".globl d_80117788\n.set d_80117788, ripple_fx_params+0x8\n"
        ".globl d_8011778C\n.set d_8011778C, ripple_fx_params+0xC\n"
        ".globl smg_soldier_hit_script\n.set smg_soldier_hit_script, smg_soldier_anims+0x224\n"
        ".globl proximity_sensor_range_x\n.set proximity_sensor_range_x, prox_cells+0xC\n"
        ".globl fade_target_color_vy\n.set fade_target_color_vy, fade_target_color+0x2\n"
        ".globl fade_target_color_vz\n.set fade_target_color_vz, fade_target_color+0x4\n"
        ".globl sincos_deg90\n.set sincos_deg90, rcossin_tbl+0x1000\n"
        ".globl view_sincos\n.set view_sincos, rcossin_tbl+0x2000\n"
        ".globl sincos_deg270\n.set sincos_deg270, rcossin_tbl+0x3000\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n"
        ".globl D_8012B9A8\n.set D_8012B9A8, owner_sound_handles+0x4\n"
        ".globl D_8012BC92\n.set D_8012BC92, view_nudge+0x2\n"
        ".globl d_801201AE\n.set d_801201AE, flow+0x2\n"
        ".globl flow_angle\n.set flow_angle, flow+0x4\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl helicopter_script\n.set helicopter_script, helicopter_anims+0x0\n"
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
        ".globl timer_tail_script\n.set timer_tail_script, timer_tail_anims+0x0\n"
        ".globl timer_tail_script_value\n.set timer_tail_script_value, timer_tail_anims+0x8\n"
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
        ".globl smg_soldier_idle_cycle_alt\n.set smg_soldier_idle_cycle_alt, smg_soldier_scripts+0x14\n"
        ".globl smg_soldier_patrol\n.set smg_soldier_patrol, smg_soldier_scripts+0x28\n"
        ".globl smg_soldier_wander_start\n.set smg_soldier_wander_start, smg_soldier_scripts+0x34\n"
        ".globl smg_soldier_wander_hold\n.set smg_soldier_wander_hold, smg_soldier_scripts+0x4C\n"
        ".globl smg_soldier_hold\n.set smg_soldier_hold, smg_soldier_scripts+0x58\n"
        ".globl smg_soldier_hold_pause\n.set smg_soldier_hold_pause, smg_soldier_scripts+0x60\n"
        ".globl smg_soldier_hold_cycle_alt\n.set smg_soldier_hold_cycle_alt, smg_soldier_scripts+0x68\n"
        ".globl smg_soldier_walk\n.set smg_soldier_walk, smg_soldier_scripts+0x7C\n"
        ".globl smg_soldier_walk_step\n.set smg_soldier_walk_step, smg_soldier_scripts+0x84\n"
        ".globl smg_soldier_walk_cycle_alt\n.set smg_soldier_walk_cycle_alt, smg_soldier_scripts+0x8C\n"
        ".globl smg_soldier_walk_pause\n.set smg_soldier_walk_pause, smg_soldier_scripts+0xA0\n"
        ".globl smg_soldier_walk_pause_cycle_alt\n.set smg_soldier_walk_pause_cycle_alt, smg_soldier_scripts+0xA8\n"
        ".globl smg_soldier_jump_table\n.set smg_soldier_jump_table, smg_soldier_scripts+0xBC\n"
        ".globl smg_soldier_script\n.set smg_soldier_script, smg_soldier_scripts+0xF4\n"
        ".globl placed_actor_script\n.set placed_actor_script, placed_actor_anims+0x0\n"
        ".globl placed_actor_script_value\n.set placed_actor_script_value, placed_actor_anims+0x8\n"
        ".globl rooftop_supermech_m12_final_boss_anim_idle\n.set rooftop_supermech_m12_final_boss_anim_idle, rooftop_supermech_m12_final_boss_anims+0x0\n"
        ".globl rooftop_supermech_m12_final_boss_anim_walk_loop\n.set rooftop_supermech_m12_final_boss_anim_walk_loop, rooftop_supermech_m12_final_boss_anims+0x8\n"
        ".globl rooftop_supermech_m12_final_boss_anim_walk_start\n.set rooftop_supermech_m12_final_boss_anim_walk_start, rooftop_supermech_m12_final_boss_anims+0x54\n"
        ".globl rooftop_supermech_m12_final_boss_anim_walk_lead_in\n.set rooftop_supermech_m12_final_boss_anim_walk_lead_in, rooftop_supermech_m12_final_boss_anims+0x60\n"
        ".globl rooftop_supermech_m12_final_boss_anim_halt\n.set rooftop_supermech_m12_final_boss_anim_halt, rooftop_supermech_m12_final_boss_anims+0x94\n"
        ".globl rooftop_supermech_m12_final_boss_anim_halt_settle\n.set rooftop_supermech_m12_final_boss_anim_halt_settle, rooftop_supermech_m12_final_boss_anims+0xB4\n"
        ".globl rooftop_supermech_m12_final_boss_anim_turn_start\n.set rooftop_supermech_m12_final_boss_anim_turn_start, rooftop_supermech_m12_final_boss_anims+0xBC\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge_slow\n.set rooftop_supermech_m12_final_boss_anim_charge_slow, rooftop_supermech_m12_final_boss_anims+0xE4\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge_hold\n.set rooftop_supermech_m12_final_boss_anim_charge_hold, rooftop_supermech_m12_final_boss_anims+0x104\n"
        ".globl rooftop_supermech_m12_final_boss_anim_recover_enter\n.set rooftop_supermech_m12_final_boss_anim_recover_enter, rooftop_supermech_m12_final_boss_anims+0x10C\n"
        ".globl rooftop_supermech_m12_final_boss_anim_recover_hold\n.set rooftop_supermech_m12_final_boss_anim_recover_hold, rooftop_supermech_m12_final_boss_anims+0x114\n"
        ".globl rooftop_supermech_m12_final_boss_anim_turn_recover\n.set rooftop_supermech_m12_final_boss_anim_turn_recover, rooftop_supermech_m12_final_boss_anims+0x11C\n"
        ".globl rooftop_supermech_m12_final_boss_anim_fire_burst\n.set rooftop_supermech_m12_final_boss_anim_fire_burst, rooftop_supermech_m12_final_boss_anims+0x160\n"
        ".globl rooftop_supermech_m12_final_boss_anim_fire_burst_hold\n.set rooftop_supermech_m12_final_boss_anim_fire_burst_hold, rooftop_supermech_m12_final_boss_anims+0x1AC\n"
        ".globl rooftop_supermech_m12_final_boss_anim_fire_burst_end\n.set rooftop_supermech_m12_final_boss_anim_fire_burst_end, rooftop_supermech_m12_final_boss_anims+0x1B8\n"
        ".globl rooftop_supermech_m12_final_boss_anim_spread_attack\n.set rooftop_supermech_m12_final_boss_anim_spread_attack, rooftop_supermech_m12_final_boss_anims+0x1D4\n"
        ".globl rooftop_supermech_m12_final_boss_anim_spread_attack_end\n.set rooftop_supermech_m12_final_boss_anim_spread_attack_end, rooftop_supermech_m12_final_boss_anims+0x20C\n"
        ".globl rooftop_supermech_m12_final_boss_anim_spread_attack_second\n.set rooftop_supermech_m12_final_boss_anim_spread_attack_second, rooftop_supermech_m12_final_boss_anims+0x228\n"
        ".globl rooftop_supermech_m12_final_boss_anim_spread_attack_second_end\n.set rooftop_supermech_m12_final_boss_anim_spread_attack_second_end, rooftop_supermech_m12_final_boss_anims+0x260\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge_alt_start\n.set rooftop_supermech_m12_final_boss_anim_charge_alt_start, rooftop_supermech_m12_final_boss_anims+0x27C\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge_alt_continue\n.set rooftop_supermech_m12_final_boss_anim_charge_alt_continue, rooftop_supermech_m12_final_boss_anims+0x2BC\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge_second_alt_start\n.set rooftop_supermech_m12_final_boss_anim_charge_second_alt_start, rooftop_supermech_m12_final_boss_anims+0x2F4\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge_second_alt_end\n.set rooftop_supermech_m12_final_boss_anim_charge_second_alt_end, rooftop_supermech_m12_final_boss_anims+0x334\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge\n.set rooftop_supermech_m12_final_boss_anim_charge, rooftop_supermech_m12_final_boss_anims+0x370\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge_end\n.set rooftop_supermech_m12_final_boss_anim_charge_end, rooftop_supermech_m12_final_boss_anims+0x3B0\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge_second\n.set rooftop_supermech_m12_final_boss_anim_charge_second, rooftop_supermech_m12_final_boss_anims+0x3EC\n"
        ".globl rooftop_supermech_m12_final_boss_anim_charge_second_end\n.set rooftop_supermech_m12_final_boss_anim_charge_second_end, rooftop_supermech_m12_final_boss_anims+0x42C\n"
        ".globl rooftop_supermech_m12_final_boss_anim_aim_attack\n.set rooftop_supermech_m12_final_boss_anim_aim_attack, rooftop_supermech_m12_final_boss_anims+0x468\n"
        ".globl rooftop_supermech_m12_final_boss_anim_aim_hold\n.set rooftop_supermech_m12_final_boss_anim_aim_hold, rooftop_supermech_m12_final_boss_anims+0x494\n"
        ".globl rooftop_supermech_m12_final_boss_anim_aim_recover\n.set rooftop_supermech_m12_final_boss_anim_aim_recover, rooftop_supermech_m12_final_boss_anims+0x4A0\n"
        ".globl rooftop_supermech_m12_final_boss_anim_aim_attack_second\n.set rooftop_supermech_m12_final_boss_anim_aim_attack_second, rooftop_supermech_m12_final_boss_anims+0x4D0\n"
        ".globl rooftop_supermech_m12_final_boss_anim_aim_second_hold\n.set rooftop_supermech_m12_final_boss_anim_aim_second_hold, rooftop_supermech_m12_final_boss_anims+0x4FC\n"
        ".globl rooftop_supermech_m12_final_boss_anim_aim_second_recover\n.set rooftop_supermech_m12_final_boss_anim_aim_second_recover, rooftop_supermech_m12_final_boss_anims+0x508\n"
        ".globl rooftop_supermech_m12_final_boss_anim_scroll_attack\n.set rooftop_supermech_m12_final_boss_anim_scroll_attack, rooftop_supermech_m12_final_boss_anims+0x538\n"
        ".globl rooftop_supermech_m12_final_boss_anim_scroll_attack_mid\n.set rooftop_supermech_m12_final_boss_anim_scroll_attack_mid, rooftop_supermech_m12_final_boss_anims+0x554\n"
        ".globl rooftop_supermech_m12_final_boss_anim_scroll_attack_late\n.set rooftop_supermech_m12_final_boss_anim_scroll_attack_late, rooftop_supermech_m12_final_boss_anims+0x584\n"
        ".globl rooftop_supermech_m12_final_boss_anim_scroll_attack_end\n.set rooftop_supermech_m12_final_boss_anim_scroll_attack_end, rooftop_supermech_m12_final_boss_anims+0x5AC\n"
        ".globl rooftop_supermech_m12_final_boss_anim_scroll_second_start\n.set rooftop_supermech_m12_final_boss_anim_scroll_second_start, rooftop_supermech_m12_final_boss_anims+0x5E4\n"
        ".globl rooftop_supermech_m12_final_boss_anim_scroll_second_mid\n.set rooftop_supermech_m12_final_boss_anim_scroll_second_mid, rooftop_supermech_m12_final_boss_anims+0x600\n"
        ".globl rooftop_supermech_m12_final_boss_anim_scroll_second_late\n.set rooftop_supermech_m12_final_boss_anim_scroll_second_late, rooftop_supermech_m12_final_boss_anims+0x630\n"
        ".globl rooftop_supermech_m12_final_boss_anim_scroll_second_end\n.set rooftop_supermech_m12_final_boss_anim_scroll_second_end, rooftop_supermech_m12_final_boss_anims+0x658\n"
        ".globl rooftop_supermech_m12_final_boss_anim_turn_long_start\n.set rooftop_supermech_m12_final_boss_anim_turn_long_start, rooftop_supermech_m12_final_boss_anims+0x690\n"
        ".globl rooftop_supermech_m12_final_boss_anim_turn_long_hold\n.set rooftop_supermech_m12_final_boss_anim_turn_long_hold, rooftop_supermech_m12_final_boss_anims+0x6DC\n"
        ".globl rooftop_supermech_m12_final_boss_anim_turn_long_recover\n.set rooftop_supermech_m12_final_boss_anim_turn_long_recover, rooftop_supermech_m12_final_boss_anims+0x6E4\n"
        ".globl supermech_script_entry\n.set supermech_script_entry, rooftop_supermech_m12_final_boss_anims+0x720\n"
        ".globl rooftop_supermech_m12_final_boss_intro\n.set rooftop_supermech_m12_final_boss_intro, rooftop_supermech_m12_final_boss_scripts+0x0\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_attack_gate\n.set rooftop_supermech_m12_final_boss_scroll_attack_gate, rooftop_supermech_m12_final_boss_scripts+0x18\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_launch\n.set rooftop_supermech_m12_final_boss_scroll_launch, rooftop_supermech_m12_final_boss_scripts+0x24\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_launch_wait\n.set rooftop_supermech_m12_final_boss_scroll_launch_wait, rooftop_supermech_m12_final_boss_scripts+0x30\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_fire\n.set rooftop_supermech_m12_final_boss_scroll_fire, rooftop_supermech_m12_final_boss_scripts+0x40\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_fire_pause\n.set rooftop_supermech_m12_final_boss_scroll_fire_pause, rooftop_supermech_m12_final_boss_scripts+0x50\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_pause_wait\n.set rooftop_supermech_m12_final_boss_scroll_pause_wait, rooftop_supermech_m12_final_boss_scripts+0x58\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_hold_wait\n.set rooftop_supermech_m12_final_boss_scroll_hold_wait, rooftop_supermech_m12_final_boss_scripts+0x68\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_retract\n.set rooftop_supermech_m12_final_boss_scroll_retract, rooftop_supermech_m12_final_boss_scripts+0x78\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_retract_wait\n.set rooftop_supermech_m12_final_boss_scroll_retract_wait, rooftop_supermech_m12_final_boss_scripts+0x88\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_done\n.set rooftop_supermech_m12_final_boss_scroll_done, rooftop_supermech_m12_final_boss_scripts+0x98\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_gate\n.set rooftop_supermech_m12_final_boss_scroll_second_gate, rooftop_supermech_m12_final_boss_scripts+0xA4\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_launch\n.set rooftop_supermech_m12_final_boss_scroll_second_launch, rooftop_supermech_m12_final_boss_scripts+0xB0\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_launch_wait\n.set rooftop_supermech_m12_final_boss_scroll_second_launch_wait, rooftop_supermech_m12_final_boss_scripts+0xBC\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_fire\n.set rooftop_supermech_m12_final_boss_scroll_second_fire, rooftop_supermech_m12_final_boss_scripts+0xCC\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_pause\n.set rooftop_supermech_m12_final_boss_scroll_second_pause, rooftop_supermech_m12_final_boss_scripts+0xDC\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_pause_wait\n.set rooftop_supermech_m12_final_boss_scroll_second_pause_wait, rooftop_supermech_m12_final_boss_scripts+0xE4\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_hold_wait\n.set rooftop_supermech_m12_final_boss_scroll_second_hold_wait, rooftop_supermech_m12_final_boss_scripts+0xF4\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_retract\n.set rooftop_supermech_m12_final_boss_scroll_second_retract, rooftop_supermech_m12_final_boss_scripts+0x104\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_retract_wait\n.set rooftop_supermech_m12_final_boss_scroll_second_retract_wait, rooftop_supermech_m12_final_boss_scripts+0x114\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_second_done\n.set rooftop_supermech_m12_final_boss_scroll_second_done, rooftop_supermech_m12_final_boss_scripts+0x124\n"
        ".globl rooftop_supermech_m12_final_boss_spread_gate\n.set rooftop_supermech_m12_final_boss_spread_gate, rooftop_supermech_m12_final_boss_scripts+0x130\n"
        ".globl rooftop_supermech_m12_final_boss_spread_launch\n.set rooftop_supermech_m12_final_boss_spread_launch, rooftop_supermech_m12_final_boss_scripts+0x13C\n"
        ".globl rooftop_supermech_m12_final_boss_spread_launch_wait\n.set rooftop_supermech_m12_final_boss_spread_launch_wait, rooftop_supermech_m12_final_boss_scripts+0x144\n"
        ".globl rooftop_supermech_m12_final_boss_spread_fire\n.set rooftop_supermech_m12_final_boss_spread_fire, rooftop_supermech_m12_final_boss_scripts+0x154\n"
        ".globl rooftop_supermech_m12_final_boss_spread_fire_wait\n.set rooftop_supermech_m12_final_boss_spread_fire_wait, rooftop_supermech_m12_final_boss_scripts+0x15C\n"
        ".globl rooftop_supermech_m12_final_boss_spread_done\n.set rooftop_supermech_m12_final_boss_spread_done, rooftop_supermech_m12_final_boss_scripts+0x170\n"
        ".globl rooftop_supermech_m12_final_boss_spread_pop\n.set rooftop_supermech_m12_final_boss_spread_pop, rooftop_supermech_m12_final_boss_scripts+0x184\n"
        ".globl rooftop_supermech_m12_final_boss_spread_second_gate\n.set rooftop_supermech_m12_final_boss_spread_second_gate, rooftop_supermech_m12_final_boss_scripts+0x188\n"
        ".globl rooftop_supermech_m12_final_boss_spread_second_launch\n.set rooftop_supermech_m12_final_boss_spread_second_launch, rooftop_supermech_m12_final_boss_scripts+0x194\n"
        ".globl rooftop_supermech_m12_final_boss_spread_second_launch_wait\n.set rooftop_supermech_m12_final_boss_spread_second_launch_wait, rooftop_supermech_m12_final_boss_scripts+0x19C\n"
        ".globl rooftop_supermech_m12_final_boss_spread_second_fire\n.set rooftop_supermech_m12_final_boss_spread_second_fire, rooftop_supermech_m12_final_boss_scripts+0x1AC\n"
        ".globl rooftop_supermech_m12_final_boss_spread_second_fire_wait\n.set rooftop_supermech_m12_final_boss_spread_second_fire_wait, rooftop_supermech_m12_final_boss_scripts+0x1B8\n"
        ".globl rooftop_supermech_m12_final_boss_spread_second_done\n.set rooftop_supermech_m12_final_boss_spread_second_done, rooftop_supermech_m12_final_boss_scripts+0x1C8\n"
        ".globl rooftop_supermech_m12_final_boss_spread_second_pop\n.set rooftop_supermech_m12_final_boss_spread_second_pop, rooftop_supermech_m12_final_boss_scripts+0x1DC\n"
        ".globl rooftop_supermech_m12_final_boss_aim_gate\n.set rooftop_supermech_m12_final_boss_aim_gate, rooftop_supermech_m12_final_boss_scripts+0x1E0\n"
        ".globl rooftop_supermech_m12_final_boss_aim_launch\n.set rooftop_supermech_m12_final_boss_aim_launch, rooftop_supermech_m12_final_boss_scripts+0x1EC\n"
        ".globl rooftop_supermech_m12_final_boss_aim_launch_wait\n.set rooftop_supermech_m12_final_boss_aim_launch_wait, rooftop_supermech_m12_final_boss_scripts+0x1F4\n"
        ".globl rooftop_supermech_m12_final_boss_aim_start\n.set rooftop_supermech_m12_final_boss_aim_start, rooftop_supermech_m12_final_boss_scripts+0x204\n"
        ".globl rooftop_supermech_m12_final_boss_aim_loop_wait\n.set rooftop_supermech_m12_final_boss_aim_loop_wait, rooftop_supermech_m12_final_boss_scripts+0x214\n"
        ".globl rooftop_supermech_m12_final_boss_aim_fire\n.set rooftop_supermech_m12_final_boss_aim_fire, rooftop_supermech_m12_final_boss_scripts+0x224\n"
        ".globl rooftop_supermech_m12_final_boss_aim_end\n.set rooftop_supermech_m12_final_boss_aim_end, rooftop_supermech_m12_final_boss_scripts+0x23C\n"
        ".globl rooftop_supermech_m12_final_boss_aim_end_wait\n.set rooftop_supermech_m12_final_boss_aim_end_wait, rooftop_supermech_m12_final_boss_scripts+0x24C\n"
        ".globl rooftop_supermech_m12_final_boss_aim_done\n.set rooftop_supermech_m12_final_boss_aim_done, rooftop_supermech_m12_final_boss_scripts+0x25C\n"
        ".globl rooftop_supermech_m12_final_boss_aim_second_gate\n.set rooftop_supermech_m12_final_boss_aim_second_gate, rooftop_supermech_m12_final_boss_scripts+0x268\n"
        ".globl rooftop_supermech_m12_final_boss_aim_second_launch\n.set rooftop_supermech_m12_final_boss_aim_second_launch, rooftop_supermech_m12_final_boss_scripts+0x274\n"
        ".globl rooftop_supermech_m12_final_boss_aim_second_launch_wait\n.set rooftop_supermech_m12_final_boss_aim_second_launch_wait, rooftop_supermech_m12_final_boss_scripts+0x27C\n"
        ".globl rooftop_supermech_m12_final_boss_aim_second_start\n.set rooftop_supermech_m12_final_boss_aim_second_start, rooftop_supermech_m12_final_boss_scripts+0x28C\n"
        ".globl rooftop_supermech_m12_final_boss_aim_second_loop_wait\n.set rooftop_supermech_m12_final_boss_aim_second_loop_wait, rooftop_supermech_m12_final_boss_scripts+0x29C\n"
        ".globl rooftop_supermech_m12_final_boss_aim_second_fire\n.set rooftop_supermech_m12_final_boss_aim_second_fire, rooftop_supermech_m12_final_boss_scripts+0x2AC\n"
        ".globl rooftop_supermech_m12_final_boss_aim_second_end\n.set rooftop_supermech_m12_final_boss_aim_second_end, rooftop_supermech_m12_final_boss_scripts+0x2C4\n"
        ".globl rooftop_supermech_m12_final_boss_aim_second_end_wait\n.set rooftop_supermech_m12_final_boss_aim_second_end_wait, rooftop_supermech_m12_final_boss_scripts+0x2D4\n"
        ".globl rooftop_supermech_m12_final_boss_aim_second_done\n.set rooftop_supermech_m12_final_boss_aim_second_done, rooftop_supermech_m12_final_boss_scripts+0x2E4\n"
        ".globl rooftop_supermech_m12_final_boss_fire_gate\n.set rooftop_supermech_m12_final_boss_fire_gate, rooftop_supermech_m12_final_boss_scripts+0x2F0\n"
        ".globl rooftop_supermech_m12_final_boss_fire_burst_launch\n.set rooftop_supermech_m12_final_boss_fire_burst_launch, rooftop_supermech_m12_final_boss_scripts+0x2FC\n"
        ".globl rooftop_supermech_m12_final_boss_fire_burst_launch_wait\n.set rooftop_supermech_m12_final_boss_fire_burst_launch_wait, rooftop_supermech_m12_final_boss_scripts+0x304\n"
        ".globl rooftop_supermech_m12_final_boss_fire_burst_start\n.set rooftop_supermech_m12_final_boss_fire_burst_start, rooftop_supermech_m12_final_boss_scripts+0x314\n"
        ".globl rooftop_supermech_m12_final_boss_fire_burst_loop_wait\n.set rooftop_supermech_m12_final_boss_fire_burst_loop_wait, rooftop_supermech_m12_final_boss_scripts+0x320\n"
        ".globl rooftop_supermech_m12_final_boss_fire_burst_shot\n.set rooftop_supermech_m12_final_boss_fire_burst_shot, rooftop_supermech_m12_final_boss_scripts+0x330\n"
        ".globl rooftop_supermech_m12_final_boss_fire_burst_end\n.set rooftop_supermech_m12_final_boss_fire_burst_end, rooftop_supermech_m12_final_boss_scripts+0x340\n"
        ".globl rooftop_supermech_m12_final_boss_fire_burst_end_wait\n.set rooftop_supermech_m12_final_boss_fire_burst_end_wait, rooftop_supermech_m12_final_boss_scripts+0x348\n"
        ".globl rooftop_supermech_m12_final_boss_fire_burst_done\n.set rooftop_supermech_m12_final_boss_fire_burst_done, rooftop_supermech_m12_final_boss_scripts+0x358\n"
        ".globl rooftop_supermech_m12_final_boss_fire_burst_pop\n.set rooftop_supermech_m12_final_boss_fire_burst_pop, rooftop_supermech_m12_final_boss_scripts+0x368\n"
        ".globl rooftop_supermech_m12_final_boss_charge_gate\n.set rooftop_supermech_m12_final_boss_charge_gate, rooftop_supermech_m12_final_boss_scripts+0x36C\n"
        ".globl rooftop_supermech_m12_final_boss_charge_launch\n.set rooftop_supermech_m12_final_boss_charge_launch, rooftop_supermech_m12_final_boss_scripts+0x378\n"
        ".globl rooftop_supermech_m12_final_boss_charge_launch_wait\n.set rooftop_supermech_m12_final_boss_charge_launch_wait, rooftop_supermech_m12_final_boss_scripts+0x384\n"
        ".globl rooftop_supermech_m12_final_boss_charge_release\n.set rooftop_supermech_m12_final_boss_charge_release, rooftop_supermech_m12_final_boss_scripts+0x394\n"
        ".globl rooftop_supermech_m12_final_boss_charge_release_wait\n.set rooftop_supermech_m12_final_boss_charge_release_wait, rooftop_supermech_m12_final_boss_scripts+0x3A0\n"
        ".globl rooftop_supermech_m12_final_boss_charge_done\n.set rooftop_supermech_m12_final_boss_charge_done, rooftop_supermech_m12_final_boss_scripts+0x3B0\n"
        ".globl rooftop_supermech_m12_final_boss_charge_pop\n.set rooftop_supermech_m12_final_boss_charge_pop, rooftop_supermech_m12_final_boss_scripts+0x3C0\n"
        ".globl rooftop_supermech_m12_final_boss_charge_second_gate\n.set rooftop_supermech_m12_final_boss_charge_second_gate, rooftop_supermech_m12_final_boss_scripts+0x3C4\n"
        ".globl rooftop_supermech_m12_final_boss_charge_second_launch\n.set rooftop_supermech_m12_final_boss_charge_second_launch, rooftop_supermech_m12_final_boss_scripts+0x3D0\n"
        ".globl rooftop_supermech_m12_final_boss_charge_second_launch_wait\n.set rooftop_supermech_m12_final_boss_charge_second_launch_wait, rooftop_supermech_m12_final_boss_scripts+0x3DC\n"
        ".globl rooftop_supermech_m12_final_boss_charge_second_release\n.set rooftop_supermech_m12_final_boss_charge_second_release, rooftop_supermech_m12_final_boss_scripts+0x3EC\n"
        ".globl rooftop_supermech_m12_final_boss_charge_second_release_wait\n.set rooftop_supermech_m12_final_boss_charge_second_release_wait, rooftop_supermech_m12_final_boss_scripts+0x3F8\n"
        ".globl rooftop_supermech_m12_final_boss_charge_second_done\n.set rooftop_supermech_m12_final_boss_charge_second_done, rooftop_supermech_m12_final_boss_scripts+0x408\n"
        ".globl rooftop_supermech_m12_final_boss_charge_second_pop\n.set rooftop_supermech_m12_final_boss_charge_second_pop, rooftop_supermech_m12_final_boss_scripts+0x418\n"
        ".globl rooftop_supermech_m12_final_boss_reposition_enter\n.set rooftop_supermech_m12_final_boss_reposition_enter, rooftop_supermech_m12_final_boss_scripts+0x41C\n"
        ".globl rooftop_supermech_m12_final_boss_reposition_launch\n.set rooftop_supermech_m12_final_boss_reposition_launch, rooftop_supermech_m12_final_boss_scripts+0x420\n"
        ".globl rooftop_supermech_m12_final_boss_reposition_wait\n.set rooftop_supermech_m12_final_boss_reposition_wait, rooftop_supermech_m12_final_boss_scripts+0x42C\n"
        ".globl rooftop_supermech_m12_final_boss_advance_start\n.set rooftop_supermech_m12_final_boss_advance_start, rooftop_supermech_m12_final_boss_scripts+0x43C\n"
        ".globl rooftop_supermech_m12_final_boss_advance_loop_wait\n.set rooftop_supermech_m12_final_boss_advance_loop_wait, rooftop_supermech_m12_final_boss_scripts+0x448\n"
        ".globl rooftop_supermech_m12_final_boss_advance_check\n.set rooftop_supermech_m12_final_boss_advance_check, rooftop_supermech_m12_final_boss_scripts+0x458\n"
        ".globl rooftop_supermech_m12_final_boss_advance_arrive\n.set rooftop_supermech_m12_final_boss_advance_arrive, rooftop_supermech_m12_final_boss_scripts+0x46C\n"
        ".globl rooftop_supermech_m12_final_boss_halt_wait\n.set rooftop_supermech_m12_final_boss_halt_wait, rooftop_supermech_m12_final_boss_scripts+0x470\n"
        ".globl rooftop_supermech_m12_final_boss_halt\n.set rooftop_supermech_m12_final_boss_halt, rooftop_supermech_m12_final_boss_scripts+0x480\n"
        ".globl rooftop_supermech_m12_final_boss_halt_wait_end\n.set rooftop_supermech_m12_final_boss_halt_wait_end, rooftop_supermech_m12_final_boss_scripts+0x488\n"
        ".globl rooftop_supermech_m12_final_boss_halt_pop\n.set rooftop_supermech_m12_final_boss_halt_pop, rooftop_supermech_m12_final_boss_scripts+0x498\n"
        ".globl rooftop_supermech_m12_final_boss_reposition_alt_enter\n.set rooftop_supermech_m12_final_boss_reposition_alt_enter, rooftop_supermech_m12_final_boss_scripts+0x49C\n"
        ".globl rooftop_supermech_m12_final_boss_reposition_alt_launch\n.set rooftop_supermech_m12_final_boss_reposition_alt_launch, rooftop_supermech_m12_final_boss_scripts+0x4A0\n"
        ".globl rooftop_supermech_m12_final_boss_reposition_alt_wait\n.set rooftop_supermech_m12_final_boss_reposition_alt_wait, rooftop_supermech_m12_final_boss_scripts+0x4AC\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_start\n.set rooftop_supermech_m12_final_boss_advance_far_start, rooftop_supermech_m12_final_boss_scripts+0x4BC\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_loop_wait\n.set rooftop_supermech_m12_final_boss_advance_far_loop_wait, rooftop_supermech_m12_final_boss_scripts+0x4C8\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_check\n.set rooftop_supermech_m12_final_boss_advance_far_check, rooftop_supermech_m12_final_boss_scripts+0x4D8\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_arrive\n.set rooftop_supermech_m12_final_boss_advance_far_arrive, rooftop_supermech_m12_final_boss_scripts+0x4EC\n"
        ".globl rooftop_supermech_m12_final_boss_halt_far_wait\n.set rooftop_supermech_m12_final_boss_halt_far_wait, rooftop_supermech_m12_final_boss_scripts+0x4F0\n"
        ".globl rooftop_supermech_m12_final_boss_halt_far\n.set rooftop_supermech_m12_final_boss_halt_far, rooftop_supermech_m12_final_boss_scripts+0x500\n"
        ".globl rooftop_supermech_m12_final_boss_halt_far_wait_end\n.set rooftop_supermech_m12_final_boss_halt_far_wait_end, rooftop_supermech_m12_final_boss_scripts+0x508\n"
        ".globl rooftop_supermech_m12_final_boss_halt_far_pop\n.set rooftop_supermech_m12_final_boss_halt_far_pop, rooftop_supermech_m12_final_boss_scripts+0x518\n"
        ".globl rooftop_supermech_m12_final_boss_reposition_far_enter\n.set rooftop_supermech_m12_final_boss_reposition_far_enter, rooftop_supermech_m12_final_boss_scripts+0x51C\n"
        ".globl rooftop_supermech_m12_final_boss_reposition_far_launch\n.set rooftop_supermech_m12_final_boss_reposition_far_launch, rooftop_supermech_m12_final_boss_scripts+0x520\n"
        ".globl rooftop_supermech_m12_final_boss_reposition_far_wait\n.set rooftop_supermech_m12_final_boss_reposition_far_wait, rooftop_supermech_m12_final_boss_scripts+0x52C\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_alt_start\n.set rooftop_supermech_m12_final_boss_advance_far_alt_start, rooftop_supermech_m12_final_boss_scripts+0x53C\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_alt_wait\n.set rooftop_supermech_m12_final_boss_advance_far_alt_wait, rooftop_supermech_m12_final_boss_scripts+0x548\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_alt_check\n.set rooftop_supermech_m12_final_boss_advance_far_alt_check, rooftop_supermech_m12_final_boss_scripts+0x558\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_alt_arrive\n.set rooftop_supermech_m12_final_boss_advance_far_alt_arrive, rooftop_supermech_m12_final_boss_scripts+0x568\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_alt_halt_wait\n.set rooftop_supermech_m12_final_boss_advance_far_alt_halt_wait, rooftop_supermech_m12_final_boss_scripts+0x56C\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_halt\n.set rooftop_supermech_m12_final_boss_advance_far_halt, rooftop_supermech_m12_final_boss_scripts+0x57C\n"
        ".globl rooftop_supermech_m12_final_boss_advance_far_halt_wait\n.set rooftop_supermech_m12_final_boss_advance_far_halt_wait, rooftop_supermech_m12_final_boss_scripts+0x584\n"
        ".globl rooftop_supermech_m12_final_boss_halt_far_alt_pop\n.set rooftop_supermech_m12_final_boss_halt_far_alt_pop, rooftop_supermech_m12_final_boss_scripts+0x594\n"
        ".globl rooftop_supermech_m12_final_boss_rest_entry\n.set rooftop_supermech_m12_final_boss_rest_entry, rooftop_supermech_m12_final_boss_scripts+0x598\n"
        ".globl rooftop_supermech_m12_final_boss_rest_start\n.set rooftop_supermech_m12_final_boss_rest_start, rooftop_supermech_m12_final_boss_scripts+0x59C\n"
        ".globl rooftop_supermech_m12_final_boss_rest_wait\n.set rooftop_supermech_m12_final_boss_rest_wait, rooftop_supermech_m12_final_boss_scripts+0x5A8\n"
        ".globl rooftop_supermech_m12_final_boss_rest_done\n.set rooftop_supermech_m12_final_boss_rest_done, rooftop_supermech_m12_final_boss_scripts+0x5B8\n"
        ".globl rooftop_supermech_m12_final_boss_low_health_entry\n.set rooftop_supermech_m12_final_boss_low_health_entry, rooftop_supermech_m12_final_boss_scripts+0x5C0\n"
        ".globl rooftop_supermech_m12_final_boss_low_health_reset\n.set rooftop_supermech_m12_final_boss_low_health_reset, rooftop_supermech_m12_final_boss_scripts+0x5C4\n"
        ".globl rooftop_supermech_m12_final_boss_idle_loop\n.set rooftop_supermech_m12_final_boss_idle_loop, rooftop_supermech_m12_final_boss_scripts+0x5CC\n"
        ".globl rooftop_supermech_m12_final_boss_turn_direction_pick\n.set rooftop_supermech_m12_final_boss_turn_direction_pick, rooftop_supermech_m12_final_boss_scripts+0x5DC\n"
        ".globl rooftop_supermech_m12_final_boss_chase_start\n.set rooftop_supermech_m12_final_boss_chase_start, rooftop_supermech_m12_final_boss_scripts+0x5E8\n"
        ".globl rooftop_supermech_m12_final_boss_chase_wait\n.set rooftop_supermech_m12_final_boss_chase_wait, rooftop_supermech_m12_final_boss_scripts+0x610\n"
        ".globl rooftop_supermech_m12_final_boss_chase_end\n.set rooftop_supermech_m12_final_boss_chase_end, rooftop_supermech_m12_final_boss_scripts+0x61C\n"
        ".globl rooftop_supermech_m12_final_boss_chase_end_wait\n.set rooftop_supermech_m12_final_boss_chase_end_wait, rooftop_supermech_m12_final_boss_scripts+0x634\n"
        ".globl rooftop_supermech_m12_final_boss_chase_done\n.set rooftop_supermech_m12_final_boss_chase_done, rooftop_supermech_m12_final_boss_scripts+0x644\n"
        ".globl rooftop_supermech_m12_final_boss_chase_pop\n.set rooftop_supermech_m12_final_boss_chase_pop, rooftop_supermech_m12_final_boss_scripts+0x654\n"
        ".globl rooftop_supermech_m12_final_boss_idle_entry\n.set rooftop_supermech_m12_final_boss_idle_entry, rooftop_supermech_m12_final_boss_scripts+0x658\n"
        ".globl rooftop_supermech_m12_final_boss_idle_reset\n.set rooftop_supermech_m12_final_boss_idle_reset, rooftop_supermech_m12_final_boss_scripts+0x65C\n"
        ".globl rooftop_supermech_m12_final_boss_idle_loop_b\n.set rooftop_supermech_m12_final_boss_idle_loop_b, rooftop_supermech_m12_final_boss_scripts+0x664\n"
        ".globl rooftop_supermech_m12_final_boss_chase_fly_entry\n.set rooftop_supermech_m12_final_boss_chase_fly_entry, rooftop_supermech_m12_final_boss_scripts+0x674\n"
        ".globl rooftop_supermech_m12_final_boss_chase_fly_start\n.set rooftop_supermech_m12_final_boss_chase_fly_start, rooftop_supermech_m12_final_boss_scripts+0x678\n"
        ".globl rooftop_supermech_m12_final_boss_chase_fly_wait\n.set rooftop_supermech_m12_final_boss_chase_fly_wait, rooftop_supermech_m12_final_boss_scripts+0x6A0\n"
        ".globl rooftop_supermech_m12_final_boss_chase_fly_end\n.set rooftop_supermech_m12_final_boss_chase_fly_end, rooftop_supermech_m12_final_boss_scripts+0x6AC\n"
        ".globl rooftop_supermech_m12_final_boss_chase_fly_end_wait\n.set rooftop_supermech_m12_final_boss_chase_fly_end_wait, rooftop_supermech_m12_final_boss_scripts+0x6C4\n"
        ".globl rooftop_supermech_m12_final_boss_chase_fly_done\n.set rooftop_supermech_m12_final_boss_chase_fly_done, rooftop_supermech_m12_final_boss_scripts+0x6D4\n"
        ".globl rooftop_supermech_m12_final_boss_chase_fly_pop\n.set rooftop_supermech_m12_final_boss_chase_fly_pop, rooftop_supermech_m12_final_boss_scripts+0x6E4\n"
        ".globl rooftop_supermech_m12_final_boss_close_range_low_health_pick\n.set rooftop_supermech_m12_final_boss_close_range_low_health_pick, rooftop_supermech_m12_final_boss_scripts+0x6E8\n"
        ".globl rooftop_supermech_m12_final_boss_charge_side_pick\n.set rooftop_supermech_m12_final_boss_charge_side_pick, rooftop_supermech_m12_final_boss_scripts+0x704\n"
        ".globl rooftop_supermech_m12_final_boss_retreat_pick\n.set rooftop_supermech_m12_final_boss_retreat_pick, rooftop_supermech_m12_final_boss_scripts+0x714\n"
        ".globl rooftop_supermech_m12_final_boss_retreat_return\n.set rooftop_supermech_m12_final_boss_retreat_return, rooftop_supermech_m12_final_boss_scripts+0x728\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_attack_pick\n.set rooftop_supermech_m12_final_boss_scroll_attack_pick, rooftop_supermech_m12_final_boss_scripts+0x730\n"
        ".globl rooftop_supermech_m12_final_boss_low_health_close_return\n.set rooftop_supermech_m12_final_boss_low_health_close_return, rooftop_supermech_m12_final_boss_scripts+0x738\n"
        ".globl rooftop_supermech_m12_final_boss_far_range_low_health_pick\n.set rooftop_supermech_m12_final_boss_far_range_low_health_pick, rooftop_supermech_m12_final_boss_scripts+0x73C\n"
        ".globl rooftop_supermech_m12_final_boss_charge_aligned_pick\n.set rooftop_supermech_m12_final_boss_charge_aligned_pick, rooftop_supermech_m12_final_boss_scripts+0x74C\n"
        ".globl rooftop_supermech_m12_final_boss_spread_pick\n.set rooftop_supermech_m12_final_boss_spread_pick, rooftop_supermech_m12_final_boss_scripts+0x75C\n"
        ".globl rooftop_supermech_m12_final_boss_fire_pick\n.set rooftop_supermech_m12_final_boss_fire_pick, rooftop_supermech_m12_final_boss_scripts+0x76C\n"
        ".globl rooftop_supermech_m12_final_boss_mid_fire_aligned_gate\n.set rooftop_supermech_m12_final_boss_mid_fire_aligned_gate, rooftop_supermech_m12_final_boss_scripts+0x774\n"
        ".globl rooftop_supermech_m12_final_boss_mid_fire_pop\n.set rooftop_supermech_m12_final_boss_mid_fire_pop, rooftop_supermech_m12_final_boss_scripts+0x780\n"
        ".globl rooftop_supermech_m12_final_boss_long_range_low_health_pick\n.set rooftop_supermech_m12_final_boss_long_range_low_health_pick, rooftop_supermech_m12_final_boss_scripts+0x784\n"
        ".globl rooftop_supermech_m12_final_boss_far_attack_roll\n.set rooftop_supermech_m12_final_boss_far_attack_roll, rooftop_supermech_m12_final_boss_scripts+0x794\n"
        ".globl rooftop_supermech_m12_final_boss_far_spread_pick\n.set rooftop_supermech_m12_final_boss_far_spread_pick, rooftop_supermech_m12_final_boss_scripts+0x7AC\n"
        ".globl rooftop_supermech_m12_final_boss_far_charge_pick\n.set rooftop_supermech_m12_final_boss_far_charge_pick, rooftop_supermech_m12_final_boss_scripts+0x7B4\n"
        ".globl rooftop_supermech_m12_final_boss_far_attack_roll_return\n.set rooftop_supermech_m12_final_boss_far_attack_roll_return, rooftop_supermech_m12_final_boss_scripts+0x7BC\n"
        ".globl rooftop_supermech_m12_final_boss_mid_range_pick\n.set rooftop_supermech_m12_final_boss_mid_range_pick, rooftop_supermech_m12_final_boss_scripts+0x7C0\n"
        ".globl rooftop_supermech_m12_final_boss_default_reposition\n.set rooftop_supermech_m12_final_boss_default_reposition, rooftop_supermech_m12_final_boss_scripts+0x7E8\n"
        ".globl rooftop_supermech_m12_final_boss_default_reposition_fire\n.set rooftop_supermech_m12_final_boss_default_reposition_fire, rooftop_supermech_m12_final_boss_scripts+0x7F4\n"
        ".globl rooftop_supermech_m12_final_boss_default_reposition_rest\n.set rooftop_supermech_m12_final_boss_default_reposition_rest, rooftop_supermech_m12_final_boss_scripts+0x7FC\n"
        ".globl rooftop_supermech_m12_final_boss_default_scroll_pick\n.set rooftop_supermech_m12_final_boss_default_scroll_pick, rooftop_supermech_m12_final_boss_scripts+0x804\n"
        ".globl rooftop_supermech_m12_final_boss_random_move_pick\n.set rooftop_supermech_m12_final_boss_random_move_pick, rooftop_supermech_m12_final_boss_scripts+0x80C\n"
        ".globl rooftop_supermech_m12_final_boss_default_random_scroll_pick\n.set rooftop_supermech_m12_final_boss_default_random_scroll_pick, rooftop_supermech_m12_final_boss_scripts+0x824\n"
        ".globl rooftop_supermech_m12_final_boss_default_random_charge_pick\n.set rooftop_supermech_m12_final_boss_default_random_charge_pick, rooftop_supermech_m12_final_boss_scripts+0x82C\n"
        ".globl rooftop_supermech_m12_final_boss_default_random_return\n.set rooftop_supermech_m12_final_boss_default_random_return, rooftop_supermech_m12_final_boss_scripts+0x834\n"
        ".globl rooftop_supermech_m12_final_boss_low_health_near_pick\n.set rooftop_supermech_m12_final_boss_low_health_near_pick, rooftop_supermech_m12_final_boss_scripts+0x838\n"
        ".globl rooftop_supermech_m12_final_boss_near_charge_pick\n.set rooftop_supermech_m12_final_boss_near_charge_pick, rooftop_supermech_m12_final_boss_scripts+0x854\n"
        ".globl rooftop_supermech_m12_final_boss_near_aligned_roll\n.set rooftop_supermech_m12_final_boss_near_aligned_roll, rooftop_supermech_m12_final_boss_scripts+0x85C\n"
        ".globl rooftop_supermech_m12_final_boss_near_scroll_turn\n.set rooftop_supermech_m12_final_boss_near_scroll_turn, rooftop_supermech_m12_final_boss_scripts+0x868\n"
        ".globl rooftop_supermech_m12_final_boss_aim_pick\n.set rooftop_supermech_m12_final_boss_aim_pick, rooftop_supermech_m12_final_boss_scripts+0x870\n"
        ".globl rooftop_supermech_m12_final_boss_near_aligned_scroll\n.set rooftop_supermech_m12_final_boss_near_aligned_scroll, rooftop_supermech_m12_final_boss_scripts+0x878\n"
        ".globl rooftop_supermech_m12_final_boss_near_pick_return\n.set rooftop_supermech_m12_final_boss_near_pick_return, rooftop_supermech_m12_final_boss_scripts+0x87C\n"
        ".globl rooftop_supermech_m12_final_boss_close_pick\n.set rooftop_supermech_m12_final_boss_close_pick, rooftop_supermech_m12_final_boss_scripts+0x880\n"
        ".globl rooftop_supermech_m12_final_boss_close_range_charge_pick\n.set rooftop_supermech_m12_final_boss_close_range_charge_pick, rooftop_supermech_m12_final_boss_scripts+0x89C\n"
        ".globl rooftop_supermech_m12_final_boss_close_range_retreat_pick\n.set rooftop_supermech_m12_final_boss_close_range_retreat_pick, rooftop_supermech_m12_final_boss_scripts+0x8AC\n"
        ".globl rooftop_supermech_m12_final_boss_close_range_rest\n.set rooftop_supermech_m12_final_boss_close_range_rest, rooftop_supermech_m12_final_boss_scripts+0x8C8\n"
        ".globl rooftop_supermech_m12_final_boss_scroll_close_pick\n.set rooftop_supermech_m12_final_boss_scroll_close_pick, rooftop_supermech_m12_final_boss_scripts+0x8D0\n"
        ".globl rooftop_supermech_m12_final_boss_close_attack_pick_return\n.set rooftop_supermech_m12_final_boss_close_attack_pick_return, rooftop_supermech_m12_final_boss_scripts+0x8D8\n"
        ".globl rooftop_supermech_m12_final_boss_mid_pick\n.set rooftop_supermech_m12_final_boss_mid_pick, rooftop_supermech_m12_final_boss_scripts+0x8DC\n"
        ".globl rooftop_supermech_m12_final_boss_far_range_aligned_pick\n.set rooftop_supermech_m12_final_boss_far_range_aligned_pick, rooftop_supermech_m12_final_boss_scripts+0x900\n"
        ".globl rooftop_supermech_m12_final_boss_far_range_spread_pick\n.set rooftop_supermech_m12_final_boss_far_range_spread_pick, rooftop_supermech_m12_final_boss_scripts+0x910\n"
        ".globl rooftop_supermech_m12_final_boss_far_range_fire_pick\n.set rooftop_supermech_m12_final_boss_far_range_fire_pick, rooftop_supermech_m12_final_boss_scripts+0x920\n"
        ".globl rooftop_supermech_m12_final_boss_mid_fire_aligned_check\n.set rooftop_supermech_m12_final_boss_mid_fire_aligned_check, rooftop_supermech_m12_final_boss_scripts+0x928\n"
        ".globl rooftop_supermech_m12_final_boss_mid_pick_return\n.set rooftop_supermech_m12_final_boss_mid_pick_return, rooftop_supermech_m12_final_boss_scripts+0x934\n"
        ".globl rooftop_supermech_m12_final_boss_far_pick\n.set rooftop_supermech_m12_final_boss_far_pick, rooftop_supermech_m12_final_boss_scripts+0x938\n"
        ".globl rooftop_supermech_m12_final_boss_far_roll_pick\n.set rooftop_supermech_m12_final_boss_far_roll_pick, rooftop_supermech_m12_final_boss_scripts+0x954\n"
        ".globl rooftop_supermech_m12_final_boss_far_roll_spread_turn\n.set rooftop_supermech_m12_final_boss_far_roll_spread_turn, rooftop_supermech_m12_final_boss_scripts+0x96C\n"
        ".globl rooftop_supermech_m12_final_boss_far_roll_charge_pick\n.set rooftop_supermech_m12_final_boss_far_roll_charge_pick, rooftop_supermech_m12_final_boss_scripts+0x974\n"
        ".globl rooftop_supermech_m12_final_boss_far_roll_return\n.set rooftop_supermech_m12_final_boss_far_roll_return, rooftop_supermech_m12_final_boss_scripts+0x97C\n"
        ".globl rooftop_supermech_m12_final_boss_mid_range_roll_pick\n.set rooftop_supermech_m12_final_boss_mid_range_roll_pick, rooftop_supermech_m12_final_boss_scripts+0x980\n"
        ".globl rooftop_supermech_m12_final_boss_roll_idle\n.set rooftop_supermech_m12_final_boss_roll_idle, rooftop_supermech_m12_final_boss_scripts+0x9A8\n"
        ".globl rooftop_supermech_m12_final_boss_roll_fire\n.set rooftop_supermech_m12_final_boss_roll_fire, rooftop_supermech_m12_final_boss_scripts+0x9B4\n"
        ".globl rooftop_supermech_m12_final_boss_roll_rest\n.set rooftop_supermech_m12_final_boss_roll_rest, rooftop_supermech_m12_final_boss_scripts+0x9BC\n"
        ".globl rooftop_supermech_m12_final_boss_roll_scroll_pick\n.set rooftop_supermech_m12_final_boss_roll_scroll_pick, rooftop_supermech_m12_final_boss_scripts+0x9C4\n"
        ".globl rooftop_supermech_m12_final_boss_roll_random_retreat\n.set rooftop_supermech_m12_final_boss_roll_random_retreat, rooftop_supermech_m12_final_boss_scripts+0x9CC\n"
        ".globl rooftop_supermech_m12_final_boss_roll_random_scroll_pick\n.set rooftop_supermech_m12_final_boss_roll_random_scroll_pick, rooftop_supermech_m12_final_boss_scripts+0x9E8\n"
        ".globl rooftop_supermech_m12_final_boss_roll_random_charge_pick\n.set rooftop_supermech_m12_final_boss_roll_random_charge_pick, rooftop_supermech_m12_final_boss_scripts+0x9F0\n"
        ".globl rooftop_supermech_m12_final_boss_roll_random_return\n.set rooftop_supermech_m12_final_boss_roll_random_return, rooftop_supermech_m12_final_boss_scripts+0x9F8\n"
        ".globl rooftop_supermech_m12_final_boss_near_pick\n.set rooftop_supermech_m12_final_boss_near_pick, rooftop_supermech_m12_final_boss_scripts+0x9FC\n"
        ".globl rooftop_supermech_m12_final_boss_near_select_charge_pick\n.set rooftop_supermech_m12_final_boss_near_select_charge_pick, rooftop_supermech_m12_final_boss_scripts+0xA14\n"
        ".globl rooftop_supermech_m12_final_boss_near_scroll_entry\n.set rooftop_supermech_m12_final_boss_near_scroll_entry, rooftop_supermech_m12_final_boss_scripts+0xA1C\n"
        ".globl rooftop_supermech_m12_final_boss_near_random_scroll_pick\n.set rooftop_supermech_m12_final_boss_near_random_scroll_pick, rooftop_supermech_m12_final_boss_scripts+0xA20\n"
        ".globl rooftop_supermech_m12_final_boss_near_aim_pick\n.set rooftop_supermech_m12_final_boss_near_aim_pick, rooftop_supermech_m12_final_boss_scripts+0xA30\n"
        ".globl rooftop_supermech_m12_final_boss_low_health_rest\n.set rooftop_supermech_m12_final_boss_low_health_rest, rooftop_supermech_m12_final_boss_scripts+0xA38\n"
        ".globl rooftop_supermech_m12_final_boss_near_select_return\n.set rooftop_supermech_m12_final_boss_near_select_return, rooftop_supermech_m12_final_boss_scripts+0xA40\n"
        ".globl rooftop_supermech_m12_final_boss_intro_continue\n.set rooftop_supermech_m12_final_boss_intro_continue, rooftop_supermech_m12_final_boss_scripts+0xA44\n"
        ".globl rooftop_supermech_m12_final_boss_health_tier_select\n.set rooftop_supermech_m12_final_boss_health_tier_select, rooftop_supermech_m12_final_boss_scripts+0xA4C\n"
        ".globl rooftop_supermech_m12_final_boss_health_tier_flag\n.set rooftop_supermech_m12_final_boss_health_tier_flag, rooftop_supermech_m12_final_boss_scripts+0xA60\n"
        ".globl rooftop_supermech_m12_final_boss_flag_select_return\n.set rooftop_supermech_m12_final_boss_flag_select_return, rooftop_supermech_m12_final_boss_scripts+0xA68\n"
        ".globl rooftop_supermech_m12_final_boss_attack_select\n.set rooftop_supermech_m12_final_boss_attack_select, rooftop_supermech_m12_final_boss_scripts+0xA74\n"
        ".globl rooftop_supermech_m12_final_boss_attack_select_low_health\n.set rooftop_supermech_m12_final_boss_attack_select_low_health, rooftop_supermech_m12_final_boss_scripts+0xA94\n"
        ".globl supermech_script_data\n.set supermech_script_data, rooftop_supermech_m12_final_boss_scripts+0xAB0\n"
        ".globl D_80121598\n.set D_80121598, rooftop_supermech_m12_final_boss_scripts+0xDE8\n"
        ".globl supermech_m12_boss_start\n.set supermech_m12_boss_start, supermech_m12_boss_scripts+0x0\n"
        ".globl supermech_m12_boss_cycle\n.set supermech_m12_boss_cycle, supermech_m12_boss_scripts+0x10\n"
        ".globl supermech_m12_boss_fire_start\n.set supermech_m12_boss_fire_start, supermech_m12_boss_scripts+0x14\n"
        ".globl supermech_m12_boss_fire_windup\n.set supermech_m12_boss_fire_windup, supermech_m12_boss_scripts+0x18\n"
        ".globl supermech_m12_boss_fire_loop\n.set supermech_m12_boss_fire_loop, supermech_m12_boss_scripts+0x20\n"
        ".globl D_80123884\n.set D_80123884, supermech_m12_boss_scripts+0x30\n"
        ".globl supermech_m12_boss_anim_idle\n.set supermech_m12_boss_anim_idle, supermech_m12_boss_anims+0x0\n"
        ".globl supermech_m12_script\n.set supermech_m12_script, supermech_m12_boss_anims+0x8\n");
