/* s11 data 0x80119C2C-0x80123000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s11_types.h"
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
extern void ceiling_bomber_spawn();
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
extern void dir_state_pick_new();
extern void dreadnought_m11_aim_player();
extern void dreadnought_m11_aim_player_fx();
extern void dreadnought_m11_approach();
extern void dreadnought_m11_boss_spawn();
extern void dreadnought_m11_chase_fly();
extern void dreadnought_m11_clear_sound_flag();
extern void dreadnought_m11_cycle_update();
extern void dreadnought_m11_fly_forward();
extern void dreadnought_m11_fly_route();
extern void dreadnought_m11_randomize_flag();
extern void dreadnought_m11_request_attack();
extern void dreadnought_m11_request_muzzle_fx();
extern void dreadnought_m11_reset();
extern void dreadnought_m11_walk_begin();
extern void dreadnought_m11_walk_end();
extern void end_zone_spawn();
extern void enemy_burst_update();
extern void enemy_charge_update();
extern void enemy_cool_update();
extern void enemy_retarget_jitter();
extern void enemy_smoke_update();
extern u8 file_stk3_ch0_cb4[];
extern u8 file_stk3_ch0_clt[];
extern u8 file_stk3_ch0_vx1[];
extern u8 file_stk3_tp0_clt[];
extern u8 file_stk3_tp0_xs3[];
extern u8 file_tetr_ch0_cb4[];
extern u8 file_tetr_ch0_clt[];
extern u8 file_tetr_ch0_vx1[];
extern u8 file_tetr_tp0_clt[];
extern u8 file_tetr_tp0_xs3[];
extern void flier_approach_update();
extern void fn_800B7514();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void fn_s07_800BAE10();
extern void fuchikoma_chase_update();
extern void func_800BF730();
extern void func_800BFA80();
extern void func_800C02C8();
extern void func_800C6D68();
extern void gun_turret_2_spawn();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern u8 model_base_slot[];
extern void obj_area_update();
extern void obj_call_hook();
extern void obj_chase_player();
extern void obj_expire_burst();
extern void obj_fall_update();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_hover_update();
extern void obj_release_check();
extern void obj_script_branch_if_far();
extern void obj_script_branch_if_near();
extern void obj_script_jump_within();
extern void obj_script_read_jump();
extern void obj_script_read_next_state();
extern void obj_script_read_s32();
extern void obj_script_read_speed();
extern void obj_script_read_u16_var();
extern void obj_script_set_speed();
extern void obj_spawn_flier();
extern void obj_spawn_pair_from_placement();
extern void obj_state_dispatch();
extern void obj_steer_decay_update();
extern void obj_steer_fire_update();
extern void obj_steer_spawn_update();
extern void obj_zigzag_move();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placed_actor_spawn();
extern void placed_rects_init();
extern void placement_spawn();
extern void pyramid_mine_spawn();
extern void ramp_start_script();
extern void script_branch_by_bearing();
extern void script_branch_on_repeat();
extern void script_clear_salvo_timer();
extern void script_jump_if_mode();
extern void script_jump_if_near_player();
extern void script_jump_if_player_far();
extern void script_jump_if_player_in_radius();
extern void script_jump_if_player_near();
extern void script_jump_if_player_within();
extern void script_jump_if_within_range();
extern void script_jump_if_z_in_range();
extern void script_jump_near_corner();
extern void script_op_aim_and_track();
extern void script_op_jump_if_flag_in_range();
extern void script_op_jump_if_in_range();
extern void script_op_jump_if_player_in_range();
extern void script_op_set_enemy_sound();
extern void script_op_set_mode();
extern void script_read_speed();
extern void script_read_state();
extern void script_set_next_state();
extern void sound_start_ambient();
extern void spark_init_packet_ptr();
extern u8 str_arkb_ch0_clt[];
extern u8 str_arkb_ch0_vx1[];
extern u8 str_arkb_ch0cb4[];
extern u8 str_arkb_tp0_clt[];
extern u8 str_arkb_tp0_xs3[];
extern u8 str_b11_dat_fac[];
extern u8 str_b11_ene_fac[];
extern u8 str_bosb_ch0_clt[];
extern u8 str_bosb_ch0_vx1[];
extern u8 str_bosb_ch0cb4[];
extern u8 str_bosb_ch1_vx1[];
extern u8 str_bosb_ch1cb4[];
extern u8 str_bosb_tp0_clt[];
extern u8 str_bosb_tp0_xs3[];
extern u8 str_bosb_tp1_clt[];
extern u8 str_bosb_tp1_xs3[];
extern u8 str_com_dat_fac[];
extern u8 str_dbs_apdea3[];
extern u8 str_dbs_cnf_bcf[];
extern u8 str_dbs_joy_bin[];
extern u8 str_dct_apdea3[];
extern u8 str_dct_cnf_bcf[];
extern u8 str_dct_joy_bin[];
extern u8 str_dorb_ch0cb4[];
extern u8 str_enemy_arkb_data[];
extern u8 str_enemy_bosb_data[];
extern u8 str_enemy_ctlb_data[];
extern u8 str_enemy_dorb_data[];
extern u8 str_enemy_etr_data[];
extern u8 str_enemy_hou2_data[];
extern u8 str_enemy_jira_data[];
extern u8 str_enemy_stk3_data[];
extern u8 str_enemy_tnk1_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_hou2_ch0_clt[];
extern u8 str_hou2_ch0_vx1[];
extern u8 str_hou2_ch0cb4[];
extern u8 str_hou2_tp0_clt[];
extern u8 str_hou2_tp0_xs3[];
extern u8 str_jira_ch0_clt[];
extern u8 str_jira_ch0_vx1[];
extern u8 str_jira_ch0cb4[];
extern u8 str_jira_tp0_clt[];
extern u8 str_jira_tp0_xs3[];
extern u8 str_m11_dat_fac[];
extern u8 str_m42_cnf_bcf[];
extern u8 str_m42_joy_bin[];
extern u8 str_main_data[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_s11_boss[];
extern u8 str_s11_dat_fac[];
extern u8 str_s11_ene_fac[];
extern u8 str_s11_miss[];
extern u8 str_s11_stage[];
extern u8 str_sdw_obj_vx1[];
extern u8 str_sdw_tp0_clt[];
extern u8 str_sdw_tp0_xs3[];
extern u8 str_tg_disp_clt[];
extern u8 str_tg_disp_grc[];
extern u8 str_tg_disp_so3[];
extern u8 str_tnk1_ch0_clt[];
extern u8 str_tnk1_ch0_vx1[];
extern u8 str_tnk1_ch0cb4[];
extern u8 str_tnk1_tp0_clt[];
extern u8 str_tnk1_tp0_xs3[];
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
extern void turret_branch_if_aimed();
extern void turret_track_player();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_80119E80[];
extern u8 D_80119E98[];
extern u8 D_8011A6EC[];
extern u8 D_8011B084[];
extern u8 D_8012181E[];
extern u8 D_80122EC6[];
extern u8 cos_table[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 d_801201AE[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 flow_angle[];
extern u8 fuchikoma_state_table_s12[];
extern u8 gun_hit_effect_table[];
extern u8 placed_rect_bounds_x_max[];
extern u8 placed_rect_bounds_x_min[];
extern u8 placed_rect_bounds_z_max[];
extern u8 placed_rect_bounds_z_min[];
extern u8 pyramid_mine_data[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 view_sincos[];
extern s32 area;
extern ScanItem D_80119C30[];
extern AreaEntry d_80116CA0;
extern AreaEntry d_80116CC8;
extern ScanItem D_80119CC8[];
extern AreaEntry d_80116D08;
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern s32 D_80119DCC[3];
extern ModelBlockRef d_80116FBC[];
extern ModelBlockRef d_80116FD4[];
extern ModelBlockRef d_80116FE4[];
extern ModelBlockRange d_8011B014[];
extern ModelBlock pyramid_mine_model_block;
extern u8 *pyramid_mine_ptr_table_ids[];
extern ScanEntry pyramid_mine_scan_entry;
extern u32 d_8011B068[];
extern s16 moving_pyramid_mine_script_pc[];
extern s16 *moving_pyramid_mine_data[];
extern RecTemplate area_effect_fx_main;
extern RecTemplate area_effect_fx_pulse;
extern s16 moving_pyramid_mine_init[];
extern s16 moving_pyramid_mine_start[];
extern s16 pyramid_mine_watch[];
extern s16 pyramid_mine_detonate[];
extern s16 *moving_pyramid_mine_script_data[];
extern s16 *D_80119EEC;
extern ScriptCallEntry D_80119EF0[];
extern StateEntry D_80119F20[];
extern s32 ceiling_bomber_asset[3];
extern ModelBlockRef D_80119F4C[];
extern ModelBlockRef D_80119F64[];
extern ModelBlockRef D_80119F74[];
extern ModelBlock ceiling_bomber_model;
extern u8 *D_80119FA8[];
extern ScanEntry ceiling_bomber_scan_entry;
extern SoundVolume D_80119FC8[];
extern s16 ceiling_bomber_anim_idle[];
extern s16 ceiling_bomber_anim_charge[];
extern s16 ceiling_bomber_anim_hold_charged[];
extern s16 ceiling_bomber_anim_cooldown[];
extern s16 ceiling_bomber_anim_rest[];
extern s16 ceiling_bomber_anim_hold_smoke[];
extern s16 *ceiling_bomber_data[];
extern s16 ceiling_bomber_idle[];
extern s16 ceiling_bomber_arm[];
extern s16 ceiling_bomber_arming[];
extern s16 ceiling_bomber_charge[];
extern s16 ceiling_bomber_charging[];
extern s16 ceiling_bomber_smoke[];
extern s16 ceiling_bomber_smoking[];
extern s16 ceiling_bomber_cool[];
extern s16 ceiling_bomber_cooling[];
extern s16 ceiling_bomber_rest[];
extern s16 ceiling_bomber_resting[];
extern s16 ceiling_bomber_rearm[];
extern s16 ceiling_bomber_rearming[];
extern s16 *ceiling_bomber_script_data[];
extern u32 ceiling_bomber_script_link;
extern u32 D_8011A0E8[];
extern StateEntry D_8011A0F8[];
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
extern s32 D_8011A520[3];
extern ModelBlockRef D_8011A52C[];
extern ModelBlockRef D_8011A544[];
extern ModelBlockRef D_8011A554[];
extern ModelBlock D_8011A564;
extern u8 *D_8011A588[];
extern ScanEntry D_8011A590;
extern s16 flier_script_ptr_anim_idle[];
extern s16 *D_8011A5B0;
extern StateEntry D_8011A5B4[2];
extern s32 proximity_asset[3];
extern ModelBlockRef land_mine_clt_refs[];
extern ModelBlockRef land_mine_xs3_refs[];
extern ModelBlockRef land_mine_vx1_refs[];
extern ModelBlockRange d_80116F68[];
extern ModelBlock jira_model_block;
extern u8 *jira_stage_files[];
extern ScanEntry jira_load_step;
extern StateEntry placed_actor_states[1];
extern s16 placed_actor_script[];
extern s16 *placed_actor_script_value[];
extern u8 *dorb_ptr_table_names[];
extern s32 D_8011A678;
extern s32 solid_point_base[2];
extern ScanEntry dorb_scan_entry;
extern u16 spark_offset_table[];
extern PlacedRectDefs obj_pair_model_table;
extern u32 dreadnought_route;
extern u32 D_8011A6FC;
extern u32 D_8011A700;
extern u32 D_8011A704[];
extern ModelBlockRef D_8011A758[];
extern ModelBlockRef D_8011A778[];
extern ModelBlockRef D_8011A790[];
extern ModelBlockRange D_8011A7A8[];
extern ModelBlockRange D_8011A7D0[];
extern ModelBlock bosb_model_block;
extern u8 *bosb_ptr_table_names[];
extern ScanEntry bosb_scan_entry;
extern u32 D_8011A848[];
extern s16 dreadnought_m11_boss_script[];
extern s16 dreadnought_m11_boss_anim_ramp_up[];
extern s16 dreadnought_m11_boss_anim_hover[];
extern s16 dreadnought_m11_boss_anim_chase_front[];
extern s16 dreadnought_m11_boss_anim_chase_left[];
extern s16 dreadnought_m11_boss_anim_chase_back[];
extern s16 dreadnought_m11_boss_anim_chase_right[];
extern s16 dreadnought_m11_boss_anim_return_rest[];
extern s16 dreadnought_m11_boss_anim_aim[];
extern s16 dreadnought_m11_boss_anim_fire_muzzle[];
extern s16 dreadnought_m11_boss_anim_approach[];
extern s16 *dreadnought_m11_boss_data[];
extern s16 dreadnought_m11_boss_dispatch[];
extern s16 dreadnought_m11_boss_choose_action[];
extern s16 dreadnought_m11_boss_idle[];
extern s16 dreadnought_m11_boss_idle_hold[];
extern s16 dreadnought_m11_boss_patrol[];
extern s16 dreadnought_m11_boss_patrol_wait[];
extern s16 dreadnought_m11_boss_cycle[];
extern s16 dreadnought_m11_boss_cycle_wait[];
extern s16 dreadnought_m11_boss_chase_by_bearing[];
extern s16 dreadnought_m11_boss_chase_front[];
extern s16 dreadnought_m11_boss_chase_left[];
extern s16 dreadnought_m11_boss_chase_back[];
extern s16 dreadnought_m11_boss_chase_right[];
extern s16 dreadnought_m11_boss_chase_wait[];
extern s16 dreadnought_m11_boss_disengage[];
extern s16 dreadnought_m11_boss_disengage_wait[];
extern s16 dreadnought_m11_boss_aim[];
extern s16 dreadnought_m11_boss_aim_hold[];
extern s16 dreadnought_m11_boss_fire_muzzle[];
extern s16 dreadnought_m11_boss_fire_muzzle_hold[];
extern s16 dreadnought_m11_boss_approach[];
extern s16 dreadnought_m11_boss_approach_hold[];
extern s16 dreadnought_m11_boss_idle_wait[];
extern s16 dreadnought_m11_boss_settle[];
extern s16 *dreadnought_m11_script_data[];
extern s16 *D_8011AD54;
extern ScriptCallEntry D_8011AD58[];
extern StateEntry D_8011ADE0[];
extern RecTemplate fade_red_fx_template;
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern RecTemplate hit_flash_template;
extern RecTemplate hit_spark_template;
extern u32 D_8011AED0[];
extern s16 damage_record_script[];
extern u32 D_8011AEE4;
extern s16 damage_record_chase[];
extern s16 damage_record_chase_wait[];
extern s16 damage_record_choose[];
extern s16 damage_record_decay[];
extern s16 damage_record_decay_wait[];
extern s16 damage_record_fire[];
extern s16 damage_record_fire_wait[];
extern s16 damage_record_eject[];
extern s16 damage_record_eject_wait[];
extern s16 damage_record_hover[];
extern s16 damage_record_hover_wait[];
extern s16 damage_record_pause[];
extern s16 damage_record_recheck[];
extern s16 *damage_record_script_data[];
extern s16 *D_8011AFF4;
extern ScriptCallEntry D_8011AFF8[];
extern StateEntry D_8011B020[];
extern s32 D_8011B048[];
extern ScanEntry D_8011B054;
extern CamZone cam_zones[17];
extern s32 end_zone_min_x;
extern s32 end_zone_max_x;
extern s32 end_zone_min_y;
extern s32 end_zone_max_y;
extern s32 end_zone_min_z;
extern s32 end_zone_max_z;
extern SoundSegmentList ambient_sound_owner;
extern PathPoint end_zone_cam_path[21];
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_80120074[];
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
extern u32 D_801211F8[];
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
extern u32 D_80121818;
extern u16 texture_image[];
extern u16 stage_image_width;
extern u16 stage_image_height;
extern u32 stage_image_pixels[];
extern s32 heap_top;
extern s32 heap2_top;
extern s32 spark_pchr_base;
extern s32 placed_rect_sound_handle;
extern s32 spark_blend_base;
extern s16 dreadnought_cycle;
extern s16 dreadnought_m11_sound_flag;
extern s32 giant_robot_on_flag;
extern s16 dreadnought_m11_walk_sound_on;
extern s32 dreadnought_m11_walk_sound_handle;
extern s16 dreadnought_m11_sfx_count;
extern Next800C5620 *fade_red_obj;
extern s32 end_zone_inside_flag;
extern s32 cam_zone_current;
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
extern u32 D_80122D14;
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
extern u32 D_80122D98;
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

s32 area = 0x1E;

ScanItem D_80119C30[9] = {
    {&pyramid_mine_scan_entry, str_enemy_etr_data},
    {&ceiling_bomber_scan_entry, str_enemy_stk3_data},
    {&arkb_loader_step, str_enemy_arkb_data},
    {&gun_turret_2_scan, str_enemy_hou2_data},
    {&jira_load_step, str_enemy_jira_data},
    {&D_8011A590, str_enemy_tnk1_data},
    {&dorb_scan_entry, str_enemy_dorb_data},
    {&D_8011B054, str_enemy_ctlb_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116CA0 = {str_s11_stage, str_dct_cnf_bcf, str_dct_apdea3, str_dct_joy_bin, str_s11_dat_fac, str_s11_ene_fac, {0x1000, 0x800, 0x600}, 0, 0x1000, D_80119C30};

AreaEntry d_80116CC8 = {str_s11_miss, str_m42_cnf_bcf, NULL, str_m42_joy_bin, str_m11_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

ScanItem D_80119CC8[2] = {
    {&bosb_scan_entry, str_enemy_bosb_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116D08 = {str_s11_boss, str_dbs_cnf_bcf, str_dbs_apdea3, str_dbs_joy_bin, str_b11_dat_fac, str_b11_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0x2000, D_80119CC8};

#include "../stage/data/area_entry_table.c"

#include "../stage/data/debug_name_buf.c"

s32 D_80119DCC[3] = {
    -1, -1, -1,
};

#include "../stage/data/d_80116FBC.c"

#include "../stage/data/d_80116FD4.c"

#include "../stage/data/d_80116FE4.c"

#include "../stage/data/d_8011B014.c"

#include "../stage/data/pyramid_mine_model_block.c"

#include "../stage/data/pyramid_mine_ptr_table_ids.c"

ScanEntry pyramid_mine_scan_entry = {{0, (s32)pyramid_mine_spawn}, D_80119DCC, (s32)&pyramid_mine_model_block, (s32)pyramid_mine_ptr_table_ids, 0};

#include "../stage/data/d_8011B068.c"

struct MovingPyramidMineScriptAnims {
    s16 pc[4];
    s16 *table[1];
} moving_pyramid_mine_script_anims = {
    /* pc */ {
        STEP(1, 11),
        GOTO(MOVING_PYRAMID_MINE_SCRIPT_PC),
    },
    /* table */ {
        moving_pyramid_mine_script_anims.pc,
    },
};

#include "../stage/data/area_effect_fx_main.c"

#include "../stage/data/area_effect_fx_pulse.c"

struct MovingPyramidMineScriptDataStreams {
    s16 moving_pyramid_mine_init[2];
    s16 moving_pyramid_mine_start[6];
    s16 pyramid_mine_watch[10];
    s16 pyramid_mine_detonate[6];
    s16 *table[4];
    s16 *D_80119EEC;
} moving_pyramid_mine_script_data_streams = {
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
        moving_pyramid_mine_script_data_streams.moving_pyramid_mine_init, moving_pyramid_mine_script_data_streams.moving_pyramid_mine_start, moving_pyramid_mine_script_data_streams.pyramid_mine_watch, moving_pyramid_mine_script_data_streams.pyramid_mine_detonate,
    },
    /* D_80119EEC */ moving_pyramid_mine_script_data_streams.moving_pyramid_mine_init,
};

ScriptCallEntry D_80119EF0[6] = {
    {NULL, 0},
    {obj_script_set_speed, 0},
    {obj_script_read_next_state, 0},
    {fn_800B7514, 0},
    {obj_script_branch_if_near, 0},
    {obj_script_branch_if_far, 0},
};

StateEntry D_80119F20[4] = {
    {0, MOVING_PYRAMID_MINE_SCRIPT_PC, 0},
    {(u32)obj_zigzag_move, MOVING_PYRAMID_MINE_SCRIPT_PC, 0},
    {(u32)obj_expire_burst, MOVING_PYRAMID_MINE_SCRIPT_PC, 0},
    {0, MOVING_PYRAMID_MINE_SCRIPT_PC, 0},
};

s32 ceiling_bomber_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_80119F4C[3] = {
    {(s32)file_stk3_ch0_clt, 0, 0},
    {(s32)file_stk3_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80119F64[2] = {
    {(s32)file_stk3_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_80119F74[2] = {
    {(s32)file_stk3_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock ceiling_bomber_model = {(s32)D_80119F4C, (s32)D_80119F74, (s32)D_80119F64, 0, 0, 0, 0, 0, 0};

u8 *D_80119FA8[2] = {
    file_stk3_ch0_cb4, NULL,
};

ScanEntry ceiling_bomber_scan_entry = {{(s32)spark_init_packet_ptr, (s32)ceiling_bomber_spawn}, ceiling_bomber_asset, (s32)&ceiling_bomber_model, (s32)D_80119FA8, 0};

SoundVolume D_80119FC8[1] = {
    {0x54D2, 0xC00},
};

struct CeilingBomberAnims {
    s16 idle[4];
    s16 charge[12];
    s16 hold_charged[4];
    s16 cooldown[10];
    s16 rest[4];
    s16 hold_smoke[4];
    s16 *table[6];
} ceiling_bomber_anims = {
    /* idle */ {
        STEP(4, 3),
        GOTO(CEILING_BOMBER_ANIM_IDLE),
    },
    /* charge */ {
        STEP(1, 3),
        SOUND(0),
        STEP(4, 4),
        STEP(4, 5),
        STEP(4, 6),
        STEP(4, 7),
    },
    /* hold_charged */ {
        STEP(1, 7),
        GOTO(CEILING_BOMBER_ANIM_HOLD_CHARGED),
    },
    /* cooldown */ {
        STEP(1, 7),
        STEP(4, 6),
        STEP(4, 5),
        STEP(4, 4),
        STEP(4, 3),
    },
    /* rest */ {
        STEP(1, 3),
        GOTO(CEILING_BOMBER_ANIM_REST),
    },
    /* hold_smoke */ {
        STEP(1, 7),
        GOTO(CEILING_BOMBER_ANIM_HOLD_SMOKE),
    },
    /* table */ {
        ceiling_bomber_anims.idle, ceiling_bomber_anims.charge, ceiling_bomber_anims.hold_charged, ceiling_bomber_anims.cooldown, ceiling_bomber_anims.rest, ceiling_bomber_anims.hold_smoke,
    },
};

struct CeilingBomberScripts {
    s16 idle[8];
    s16 arm[4];
    s16 arming[4];
    s16 charge[2];
    s16 charging[8];
    s16 smoke[2];
    s16 smoking[8];
    s16 cool[2];
    s16 cooling[8];
    s16 rest[4];
    s16 resting[4];
    s16 rearm[2];
    s16 rearming[6];
    s16 *table[13];
    u32 script_link;
} ceiling_bomber_scripts = {
    /* idle */ {
        WAIT(1),
        CEILING_BOMBER_JUMP_IF_PLAYER_NEAR, 1024, CEILING_BOMBER_ARM,
        JUMP(CEILING_BOMBER_IDLE),
    },
    /* arm */ {
        NEXT_STATE(CEILING_BOMBER_STATE_ARM),
        SET_COUNTER(18),
    },
    /* arming */ {
        WAIT(1),
        LOOP(CEILING_BOMBER_ARMING),
    },
    /* charge */ {
        NEXT_STATE(CEILING_BOMBER_STATE_CHARGE),
    },
    /* charging */ {
        WAIT(1),
        JUMP_IF_STATE(CEILING_BOMBER_STATE_DONE, CEILING_BOMBER_SMOKE),
        JUMP(CEILING_BOMBER_CHARGING),
    },
    /* smoke */ {
        NEXT_STATE(CEILING_BOMBER_STATE_SMOKE),
    },
    /* smoking */ {
        WAIT(1),
        JUMP_IF_STATE(CEILING_BOMBER_STATE_DONE, CEILING_BOMBER_COOL),
        JUMP(CEILING_BOMBER_SMOKING),
    },
    /* cool */ {
        NEXT_STATE(CEILING_BOMBER_STATE_COOL),
    },
    /* cooling */ {
        WAIT(1),
        JUMP_IF_STATE(CEILING_BOMBER_STATE_DONE, CEILING_BOMBER_REST),
        JUMP(CEILING_BOMBER_COOLING),
    },
    /* rest */ {
        NEXT_STATE(CEILING_BOMBER_STATE_REST),
        SET_COUNTER(18),
    },
    /* resting */ {
        WAIT(1),
        LOOP(CEILING_BOMBER_RESTING),
    },
    /* rearm */ {
        SET_COUNTER(30),
    },
    /* rearming */ {
        WAIT(1),
        LOOP(CEILING_BOMBER_REARMING),
        JUMP(CEILING_BOMBER_IDLE),
    },
    /* table */ {
        ceiling_bomber_scripts.idle, ceiling_bomber_scripts.arm, ceiling_bomber_scripts.arming, ceiling_bomber_scripts.charge, ceiling_bomber_scripts.charging, ceiling_bomber_scripts.smoke,
        ceiling_bomber_scripts.smoking, ceiling_bomber_scripts.cool, ceiling_bomber_scripts.cooling, ceiling_bomber_scripts.rest, ceiling_bomber_scripts.resting, ceiling_bomber_scripts.rearm,
        ceiling_bomber_scripts.rearming,
    },
    /* script_link */ (u32)ceiling_bomber_scripts.idle,
};

u32 D_8011A0E8[4] = {
    0x00000000, 0x00000000, (u32)script_jump_if_player_near, 0x00000000,
};

StateEntry D_8011A0F8[7] = {
    {0, CEILING_BOMBER_ANIM_IDLE, 1},
    {0, CEILING_BOMBER_ANIM_CHARGE, 1},
    {(u32)enemy_charge_update, CEILING_BOMBER_ANIM_HOLD_SMOKE, 1},
    {(u32)enemy_smoke_update, CEILING_BOMBER_ANIM_HOLD_SMOKE, 1},
    {(u32)enemy_cool_update, CEILING_BOMBER_ANIM_HOLD_SMOKE, 1},
    {0, CEILING_BOMBER_ANIM_COOLDOWN, 1},
    {0, CEILING_BOMBER_ANIM_HOLD_SMOKE, 1},
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

s32 D_8011A520[3] = {
    -1, -1, -1,
};

ModelBlockRef D_8011A52C[3] = {
    {(s32)str_tnk1_ch0_clt, 0, 0},
    {(s32)str_tnk1_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011A544[2] = {
    {(s32)str_tnk1_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011A554[2] = {
    {(s32)str_tnk1_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlock D_8011A564 = {(s32)D_8011A52C, (s32)D_8011A544, (s32)D_8011A554, 0, 0, 0, 0, 0, 0};

u8 *D_8011A588[2] = {
    str_tnk1_ch0cb4, NULL,
};

ScanEntry D_8011A590 = {{0, (s32)obj_spawn_flier}, D_8011A520, (s32)&D_8011A564, (s32)D_8011A588, 0};

#include "../stage/data/flier_script_ptr_anims.c"

StateEntry D_8011A5B4[2] = {
    {(u32)enemy_burst_update, 0, 0},
    {(u32)flier_approach_update, 0, 0},
};

#include "../stage/data/proximity_asset.c"

#include "../stage/data/land_mine_clt_refs.c"

#include "../stage/data/land_mine_xs3_refs.c"

#include "../stage/data/land_mine_vx1_refs.c"

#include "../stage/data/d_80116F68.c"

#include "../stage/data/jira_model_block.c"

#include "../stage/data/jira_stage_files.c"

#include "../stage/data/jira_load_step.c"

#include "../stage/data/placed_actor_states.c"

#include "../stage/data/placed_actor_anims.c"

u8 *dorb_ptr_table_names[2] = {
    str_dorb_ch0cb4, NULL,
};

s32 D_8011A678 = -1;

s32 solid_point_base[2] = {
    -1, -1,
};

ScanEntry dorb_scan_entry = {{(s32)placed_rects_init, (s32)obj_spawn_pair_from_placement}, &D_8011A678, 0, (s32)dorb_ptr_table_names, 0};

u16 spark_offset_table[2] = {
    0x00FE, 0x00F5,
};

PlacedRectDefs obj_pair_model_table = {{{2, 3, 0xA8, 0, 0x2BC, 0x578, 0x2BC, 0x2BC, 0xFF, 0xF6}, {4, 5, -0xA8, 0, 0x2BC, 0x578, 0x2BC, 0x2BC, 0x95, 0x9C}, {0, 1, 0, 0x150, 0x578, 0x4B0, 0x578, 0x4B0, 0x95, 0x9C}, {0, 1, 0, -0x150, 0x578, 0x4B0, 0x578, 0x4B0, -1, -1}}, {-1, -1}};

u32 dreadnought_route = 0xFFFFFEE2;

u32 D_8011A6FC = 0x00000000;

u32 D_8011A700 = 0xFFFFFA34;

u32 D_8011A704[21] = {
    0x00000000, 0xFFFFF962, 0x00000000, 0xFFFFF6C4, 0x00000000, 0x00000541,
    0x00000000, 0xFFFFF60E, 0x00000000, 0xFFFFF962, 0xFFFFFE20, 0xFFFFEB84,
    0x00000000, 0xFFFFFEE2, 0xFFFFFE20, 0xFFFFEC78, 0x00000000, 0x000003F7,
    0xFFFFFE20, 0xFFFFEABE, 0x00000000,
};

ModelBlockRef D_8011A758[4] = {
    {(s32)str_bosb_ch0_clt, 0, 0},
    {(s32)str_bosb_tp0_clt, 0, 0},
    {(s32)str_bosb_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011A778[3] = {
    {(s32)str_bosb_tp0_xs3, 1, 0},
    {(s32)str_bosb_tp1_xs3, 2, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011A790[3] = {
    {(s32)str_bosb_ch0_vx1, 0, 0},
    {(s32)str_bosb_ch1_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011A7A8[5] = {
    {0xD0, 0xD8, 0x2000, 0}, {0xF7, 0xFA, 0x2000, 0}, {0xF4, 0xF5, 0x2000, 0}, {0xB6, 0xB9, 0x2000, 0},
    {-1, 0, 0, 0},
};

ModelBlockRange D_8011A7D0[6] = {
    {0, 0x7A, 0x1400, 0}, {0x80, 0xC2, 0x1400, 0}, {0xC4, 0xC6, 0x1800, 0}, {0xCC, 0xCD, 0x1400, 0},
    {0xE6, 0xE6, 0xA00, 0}, {-1, 0, 0, 0},
};

ModelBlock bosb_model_block = {(s32)D_8011A758, (s32)D_8011A790, (s32)D_8011A778, 0, (s32)D_8011A7A8, 0, (s32)D_8011A7D0, 0, 0};

u8 *bosb_ptr_table_names[3] = {
    str_bosb_ch0cb4, str_bosb_ch1cb4, NULL,
};

ScanEntry bosb_scan_entry = {{0, (s32)dreadnought_m11_boss_spawn}, (s32 *)D_8011A6EC, (s32)&bosb_model_block, (s32)bosb_ptr_table_names, 0};

u32 D_8011A848[3] = {
    0x10000000, 0x051E0001, 0x051E0002,
};

struct DreadnoughtM11BossAnims {
    s16 script[4];
    s16 anim_ramp_up[22];
    s16 anim_hover[10];
    s16 anim_chase_front[48];
    s16 anim_chase_left[48];
    s16 anim_chase_back[48];
    s16 anim_chase_right[48];
    s16 anim_return_rest[18];
    s16 anim_aim[54];
    s16 anim_fire_muzzle[38];
    s16 anim_approach[10];
    s16 *table[11];
} dreadnought_m11_boss_anims = {
    /* script */ {
        STEP(1, 1),
        GOTO(DREADNOUGHT_M11_BOSS_SCRIPT),
    },
    /* anim_ramp_up */ {
        STEP(6, 1),
        STEP(6, 2),
        STEP(6, 3),
        STEP(6, 4),
        STEP(6, 5),
        STEP(6, 6),
        STEP(6, 7),
        STEP(6, 8),
        STEP(6, 9),
        STEP(6, 10),
        GOTO(DREADNOUGHT_M11_BOSS_ANIM_HOVER),
    },
    /* anim_hover */ {
        STEP(8, 11),
        STEP(8, 12),
        STEP(8, 11),
        STEP(8, 10),
        GOTO(DREADNOUGHT_M11_BOSS_ANIM_HOVER),
    },
    /* anim_chase_front */ {
        STEP(6, 10),
        STEP(6, 33),
        STEP(6, 34),
        STEP(6, 35),
        STEP(6, 36),
        STEP(6, 37),
        STEP(6, 38),
        STEP(6, 39),
        STEP(6, 40),
        STEP(6, 41),
        STEP(6, 42),
        STEP(6, 43),
        STEP(6, 44),
        STEP(6, 45),
        STEP(6, 46),
        STEP(6, 47),
        STEP(6, 48),
        STEP(6, 49),
        STEP(6, 50),
        STEP(6, 51),
        STEP(6, 52),
        STEP(6, 53),
        STEP(6, 10),
        GOTO(DREADNOUGHT_M11_BOSS_ANIM_RETURN_REST),
    },
    /* anim_chase_left */ {
        STEP(6, 10),
        STEP(6, 56),
        STEP(6, 57),
        STEP(6, 58),
        STEP(6, 59),
        STEP(6, 60),
        STEP(6, 61),
        STEP(6, 62),
        STEP(6, 63),
        STEP(6, 64),
        STEP(6, 65),
        STEP(6, 66),
        STEP(6, 67),
        STEP(6, 68),
        STEP(6, 69),
        STEP(6, 70),
        STEP(6, 71),
        STEP(6, 72),
        STEP(6, 73),
        STEP(6, 74),
        STEP(6, 75),
        STEP(6, 76),
        STEP(6, 10),
        GOTO(DREADNOUGHT_M11_BOSS_ANIM_RETURN_REST),
    },
    /* anim_chase_back */ {
        STEP(6, 10),
        STEP(6, 79),
        STEP(6, 80),
        STEP(6, 81),
        STEP(6, 82),
        STEP(6, 83),
        STEP(6, 84),
        STEP(6, 85),
        STEP(6, 86),
        STEP(6, 87),
        STEP(6, 88),
        STEP(6, 89),
        STEP(6, 90),
        STEP(6, 91),
        STEP(6, 92),
        STEP(6, 93),
        STEP(6, 94),
        STEP(6, 95),
        STEP(6, 96),
        STEP(6, 97),
        STEP(6, 98),
        STEP(6, 99),
        STEP(6, 10),
        GOTO(DREADNOUGHT_M11_BOSS_ANIM_RETURN_REST),
    },
    /* anim_chase_right */ {
        STEP(6, 10),
        STEP(6, 102),
        STEP(6, 103),
        STEP(6, 104),
        STEP(6, 105),
        STEP(6, 106),
        STEP(6, 107),
        STEP(6, 108),
        STEP(6, 109),
        STEP(6, 110),
        STEP(6, 111),
        STEP(6, 112),
        STEP(6, 113),
        STEP(6, 114),
        STEP(6, 115),
        STEP(6, 116),
        STEP(6, 117),
        STEP(6, 118),
        STEP(6, 119),
        STEP(6, 120),
        STEP(6, 121),
        STEP(6, 122),
        STEP(6, 10),
        GOTO(DREADNOUGHT_M11_BOSS_ANIM_RETURN_REST),
    },
    /* anim_return_rest */ {
        STEP(6, 10),
        STEP(6, 11),
        STEP(6, 12),
        STEP(6, 13),
        STEP(6, 14),
        STEP(6, 15),
        STEP(6, 16),
        STEP(6, 1),
        GOTO(DREADNOUGHT_M11_BOSS_SCRIPT),
    },
    /* anim_aim */ {
        STEP(6, 129),
        STEP(6, 130),
        STEP(6, 131),
        STEP(6, 132),
        STEP(6, 133),
        STEP(6, 134),
        STEP(6, 134),
        STEP(6, 134),
        STEP(6, 134),
        STEP(6, 134),
        STEP(6, 134),
        STEP(6, 135),
        STEP(6, 136),
        STEP(6, 137),
        STEP(6, 138),
        STEP(6, 139),
        STEP(6, 140),
        STEP(6, 141),
        STEP(6, 142),
        STEP(6, 143),
        STEP(6, 144),
        STEP(6, 145),
        STEP(6, 146),
        STEP(6, 147),
        STEP(6, 147),
        STEP(6, 1),
        GOTO(DREADNOUGHT_M11_BOSS_SCRIPT),
    },
    /* anim_fire_muzzle */ {
        STEP(6, 161),
        STEP(6, 162),
        STEP(6, 163),
        STEP(6, 164),
        STEP(6, 165),
        STEP(6, 166),
        STEP(6, 167),
        STEP(6, 168),
        STEP(6, 169),
        STEP(6, 170),
        STEP(174, 170),
        STEP(6, 171),
        STEP(6, 172),
        STEP(6, 173),
        STEP(6, 174),
        STEP(6, 175),
        STEP(6, 176),
        STEP(6, 1),
        GOTO(DREADNOUGHT_M11_BOSS_SCRIPT),
    },
    /* anim_approach */ {
        STEP(2, 11),
        STEP(2, 12),
        STEP(2, 11),
        STEP(2, 10),
        GOTO(DREADNOUGHT_M11_BOSS_ANIM_APPROACH),
    },
    /* table */ {
        dreadnought_m11_boss_anims.script, dreadnought_m11_boss_anims.anim_ramp_up, dreadnought_m11_boss_anims.anim_hover, dreadnought_m11_boss_anims.anim_chase_front, dreadnought_m11_boss_anims.anim_chase_left, dreadnought_m11_boss_anims.anim_chase_back,
        dreadnought_m11_boss_anims.anim_chase_right, dreadnought_m11_boss_anims.anim_return_rest, dreadnought_m11_boss_anims.anim_aim, dreadnought_m11_boss_anims.anim_fire_muzzle, dreadnought_m11_boss_anims.anim_approach,
    },
};

struct DreadnoughtM11BossScripts {
    s16 dispatch[6];
    s16 choose_action[30];
    s16 idle[8];
    s16 idle_hold[6];
    s16 patrol[12];
    s16 patrol_wait[6];
    s16 cycle[8];
    s16 cycle_wait[10];
    s16 chase_by_bearing[6];
    s16 chase_front[8];
    s16 chase_left[8];
    s16 chase_back[8];
    s16 chase_right[8];
    s16 chase_wait[6];
    s16 disengage[8];
    s16 disengage_wait[6];
    s16 aim[12];
    s16 aim_hold[8];
    s16 fire_muzzle[12];
    s16 fire_muzzle_hold[8];
    s16 approach[12];
    s16 approach_hold[10];
    s16 idle_wait[10];
    s16 settle[6];
    s16 *table[24];
    s16 *D_8011AD54;
} dreadnought_m11_boss_scripts = {
    /* dispatch */ {
        JUMP_IF_STATE(DREADNOUGHT_M11_BOSS_STATE_DEATH, DREADNOUGHT_M11_BOSS_SETTLE),
        JUMP(DREADNOUGHT_M11_BOSS_CHOOSE_ACTION),
    },
    /* choose_action */ {
        DREADNOUGHT_M11_BOSS_RANDOMIZE_FLAG,
        DREADNOUGHT_M11_BOSS_JUMP_IF_Z_IN_RANGE, DREADNOUGHT_M11_BOSS_PATROL,
        JUMP_RANDOM(512, DREADNOUGHT_M11_BOSS_FIRE_MUZZLE),
        JUMP_RANDOM(512, DREADNOUGHT_M11_BOSS_APPROACH),
        JUMP_RANDOM(768, DREADNOUGHT_M11_BOSS_AIM),
        DREADNOUGHT_M11_BOSS_JUMP_IF_PLAYER_WITHIN, 2048, DREADNOUGHT_M11_BOSS_PATROL,
        JUMP_RANDOM(1024, DREADNOUGHT_M11_BOSS_FIRE_MUZZLE),
        JUMP_RANDOM(1024, DREADNOUGHT_M11_BOSS_APPROACH),
        JUMP_RANDOM(1024, DREADNOUGHT_M11_BOSS_PATROL),
        JUMP_RANDOM(1024, DREADNOUGHT_M11_BOSS_AIM),
        JUMP(DREADNOUGHT_M11_BOSS_IDLE),
    },
    /* idle */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 0,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_IDLE,
        SET_COUNTER(1),
        JUMP(DREADNOUGHT_M11_BOSS_IDLE_HOLD),
    },
    /* idle_hold */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_IDLE_HOLD),
        JUMP(DREADNOUGHT_M11_BOSS_IDLE_WAIT),
    },
    /* patrol */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 9,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_PATROL,
        DREADNOUGHT_M11_BOSS_DIR_STATE_PICK_NEW,
        DREADNOUGHT_M11_BOSS_FUNC_800BFA80,
        DREADNOUGHT_M11_BOSS_RESET,
        DREADNOUGHT_M11_BOSS_WALK_BEGIN,
        SET_COUNTER(60),
        JUMP(DREADNOUGHT_M11_BOSS_PATROL_WAIT),
    },
    /* patrol_wait */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_PATROL_WAIT),
        JUMP(DREADNOUGHT_M11_BOSS_CYCLE),
    },
    /* cycle */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 18,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_CYCLE_SPAWN,
        SET_COUNTER(160),
        JUMP(DREADNOUGHT_M11_BOSS_CYCLE_WAIT),
    },
    /* cycle_wait */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_CYCLE_WAIT),
        DREADNOUGHT_M11_BOSS_JUMP_IF_Z_IN_RANGE, DREADNOUGHT_M11_BOSS_CYCLE,
        DREADNOUGHT_M11_BOSS_WALK_END,
        JUMP(DREADNOUGHT_M11_BOSS_CHASE_BY_BEARING),
    },
    /* chase_by_bearing */ {
        DREADNOUGHT_M11_BOSS_BRANCH_BY_BEARING, DREADNOUGHT_M11_BOSS_CHASE_FRONT, DREADNOUGHT_M11_BOSS_CHASE_LEFT, DREADNOUGHT_M11_BOSS_CHASE_BACK, DREADNOUGHT_M11_BOSS_CHASE_RIGHT,
    },
    /* chase_front */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 0,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_CHASE_FRONT,
        SET_COUNTER(138),
        JUMP(DREADNOUGHT_M11_BOSS_CHASE_WAIT),
    },
    /* chase_left */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 0,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_CHASE_LEFT,
        SET_COUNTER(138),
        JUMP(DREADNOUGHT_M11_BOSS_CHASE_WAIT),
    },
    /* chase_back */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 0,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_CHASE_BACK,
        SET_COUNTER(138),
        JUMP(DREADNOUGHT_M11_BOSS_CHASE_WAIT),
    },
    /* chase_right */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 0,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_CHASE_RIGHT,
        SET_COUNTER(138),
        JUMP(DREADNOUGHT_M11_BOSS_CHASE_WAIT),
    },
    /* chase_wait */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_CHASE_WAIT),
        JUMP(DREADNOUGHT_M11_BOSS_DISENGAGE),
    },
    /* disengage */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 0,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_DISENGAGE,
        SET_COUNTER(48),
        JUMP(DREADNOUGHT_M11_BOSS_DISENGAGE_WAIT),
    },
    /* disengage_wait */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_DISENGAGE_WAIT),
        JUMP(DREADNOUGHT_M11_BOSS_SETTLE),
    },
    /* aim */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 0,
        DREADNOUGHT_M11_BOSS_BRANCH_ON_REPEAT, 1, DREADNOUGHT_M11_BOSS_APPROACH,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_AIM,
        DREADNOUGHT_M11_BOSS_REQUEST_ATTACK,
        SET_COUNTER(360),
        JUMP(DREADNOUGHT_M11_BOSS_AIM_HOLD),
    },
    /* aim_hold */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_AIM_HOLD),
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_IDLE,
        JUMP(DREADNOUGHT_M11_BOSS_SETTLE),
    },
    /* fire_muzzle */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 0,
        DREADNOUGHT_M11_BOSS_BRANCH_ON_REPEAT, 2, DREADNOUGHT_M11_BOSS_AIM,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_FIRE_MUZZLE,
        DREADNOUGHT_M11_BOSS_REQUEST_MUZZLE_FX,
        SET_COUNTER(180),
        JUMP(DREADNOUGHT_M11_BOSS_FIRE_MUZZLE_HOLD),
    },
    /* fire_muzzle_hold */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_FIRE_MUZZLE_HOLD),
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_IDLE,
        JUMP(DREADNOUGHT_M11_BOSS_SETTLE),
    },
    /* approach */ {
        DREADNOUGHT_M11_BOSS_READ_U16_VAR, 0,
        DREADNOUGHT_M11_BOSS_BRANCH_ON_REPEAT, 3, DREADNOUGHT_M11_BOSS_FIRE_MUZZLE,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_APPROACH,
        SET_COUNTER(300),
        JUMP(DREADNOUGHT_M11_BOSS_APPROACH_HOLD),
    },
    /* approach_hold */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_APPROACH_HOLD),
        DREADNOUGHT_M11_BOSS_CLEAR_SALVO_TIMER,
        DREADNOUGHT_M11_BOSS_SET_NEXT_STATE, DREADNOUGHT_M11_BOSS_STATE_IDLE,
        JUMP(DREADNOUGHT_M11_BOSS_SETTLE),
    },
    /* idle_wait */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_IDLE_WAIT),
        SET_COUNTER_RANDOM(60, 80),
        JUMP(DREADNOUGHT_M11_BOSS_SETTLE),
    },
    /* settle */ {
        WAIT(1),
        LOOP(DREADNOUGHT_M11_BOSS_SETTLE),
        JUMP(DREADNOUGHT_M11_BOSS_DISPATCH),
    },
    /* table */ {
        dreadnought_m11_boss_scripts.dispatch, dreadnought_m11_boss_scripts.choose_action, dreadnought_m11_boss_scripts.idle, dreadnought_m11_boss_scripts.idle_hold, dreadnought_m11_boss_scripts.patrol, dreadnought_m11_boss_scripts.patrol_wait,
        dreadnought_m11_boss_scripts.cycle, dreadnought_m11_boss_scripts.cycle_wait, dreadnought_m11_boss_scripts.chase_by_bearing, dreadnought_m11_boss_scripts.chase_front, dreadnought_m11_boss_scripts.chase_left, dreadnought_m11_boss_scripts.chase_back,
        dreadnought_m11_boss_scripts.chase_right, dreadnought_m11_boss_scripts.chase_wait, dreadnought_m11_boss_scripts.disengage, dreadnought_m11_boss_scripts.disengage_wait, dreadnought_m11_boss_scripts.aim, dreadnought_m11_boss_scripts.aim_hold,
        dreadnought_m11_boss_scripts.fire_muzzle, dreadnought_m11_boss_scripts.fire_muzzle_hold, dreadnought_m11_boss_scripts.approach, dreadnought_m11_boss_scripts.approach_hold, dreadnought_m11_boss_scripts.idle_wait, dreadnought_m11_boss_scripts.settle,
    },
    /* D_8011AD54 */ dreadnought_m11_boss_scripts.dispatch,
};

ScriptCallEntry D_8011AD58[17] = {
    {NULL, 0},
    {obj_script_read_u16_var, 0},
    {script_set_next_state, 0},
    {func_800BF730, 0},
    {script_jump_if_player_within, 0},
    {script_branch_by_bearing, 0},
    {dir_state_pick_new, 0},
    {script_jump_if_z_in_range, 0},
    {dreadnought_m11_request_muzzle_fx, 0},
    {script_clear_salvo_timer, 0},
    {func_800BFA80, 0},
    {dreadnought_m11_reset, 0},
    {dreadnought_m11_randomize_flag, 0},
    {dreadnought_m11_request_attack, 0},
    {script_branch_on_repeat, 0},
    {dreadnought_m11_walk_begin, 0},
    {dreadnought_m11_walk_end, 0},
};

StateEntry D_8011ADE0[12] = {
    {(u32)dreadnought_m11_clear_sound_flag, DREADNOUGHT_M11_BOSS_SCRIPT, 0},
    {(u32)dreadnought_m11_fly_route, DREADNOUGHT_M11_BOSS_ANIM_RAMP_UP, 0},
    {(u32)dreadnought_m11_cycle_update, DREADNOUGHT_M11_BOSS_ANIM_HOVER, 0},
    {(u32)dreadnought_m11_chase_fly, DREADNOUGHT_M11_BOSS_ANIM_CHASE_FRONT, 0},
    {(u32)dreadnought_m11_chase_fly, DREADNOUGHT_M11_BOSS_ANIM_CHASE_LEFT, 0},
    {(u32)dreadnought_m11_chase_fly, DREADNOUGHT_M11_BOSS_ANIM_CHASE_BACK, 0},
    {(u32)dreadnought_m11_chase_fly, DREADNOUGHT_M11_BOSS_ANIM_CHASE_RIGHT, 0},
    {(u32)dreadnought_m11_fly_forward, DREADNOUGHT_M11_BOSS_ANIM_RETURN_REST, 0},
    {(u32)dreadnought_m11_aim_player, DREADNOUGHT_M11_BOSS_SCRIPT, 0},
    {(u32)dreadnought_m11_aim_player_fx, DREADNOUGHT_M11_BOSS_ANIM_AIM, 0},
    {(u32)dreadnought_m11_approach, DREADNOUGHT_M11_BOSS_ANIM_FIRE_MUZZLE, 0},
    {(u32)func_800C02C8, DREADNOUGHT_M11_BOSS_ANIM_APPROACH, 0},
};

#include "../stage/data/fade_red_fx_template.c"

#include "../stage/data/fx_owner_template_a.c"

RecTemplate hit_flash_template = {1, 0x40, 0x52, 0xFF, 0, 0x2A, 0x18000, 0x18000, -0x1000, 0x4000};

RecTemplate hit_spark_template = {1, 0xC0, 0xC0, 0xFF, 0, 0x2A, 0xC000, 0x16000, -0x1000, 0x4000};

u32 D_8011AED0[3] = {
    0x10000000, 0x051E0001, 0x051E0002,
};

struct DamageRecordAnims {
    s16 script[4];
    u32 table;
} damage_record_anims = {
    /* script */ {
        STEP(1, 193),
        GOTO(DAMAGE_RECORD_SCRIPT),
    },
    /* table */ (u32)damage_record_anims.script,
};

struct DamageRecordScripts {
    s16 chase[12];
    s16 chase_wait[10];
    s16 choose[12];
    s16 decay[8];
    s16 decay_wait[10];
    s16 fire[8];
    s16 fire_wait[10];
    s16 eject[8];
    s16 eject_wait[10];
    s16 hover[6];
    s16 hover_wait[4];
    s16 pause[6];
    s16 recheck[4];
    s16 *table[13];
    s16 *D_8011AFF4;
} damage_record_scripts = {
    /* chase */ {
        DAMAGE_RECORD_READ_SPEED, 0,
        JUMP_IF_STATE(DAMAGE_RECORD_STATE_HOVER, DAMAGE_RECORD_HOVER),
        DAMAGE_RECORD_READ_STATE, 0,
        SET_COUNTER(180),
        JUMP(DAMAGE_RECORD_CHASE_WAIT),
    },
    /* chase_wait */ {
        WAIT(1),
        JUMP_IF_STATE(DAMAGE_RECORD_STATE_HOVER, DAMAGE_RECORD_HOVER),
        LOOP(DAMAGE_RECORD_CHASE_WAIT),
        JUMP(DAMAGE_RECORD_CHOOSE),
    },
    /* choose */ {
        JUMP_IF_STATE(DAMAGE_RECORD_STATE_HOVER, DAMAGE_RECORD_HOVER),
        DAMAGE_RECORD_JUMP_IF_NEAR_PLAYER, 1500, DAMAGE_RECORD_FIRE,
        DAMAGE_RECORD_JUMP_IF_NEAR_PLAYER, 4000, DAMAGE_RECORD_EJECT,
        JUMP(DAMAGE_RECORD_DECAY),
    },
    /* decay */ {
        DAMAGE_RECORD_READ_SPEED, 10,
        DAMAGE_RECORD_READ_STATE, 1,
        SET_COUNTER(60),
        JUMP(DAMAGE_RECORD_DECAY_WAIT),
    },
    /* decay_wait */ {
        WAIT(1),
        JUMP_IF_STATE(DAMAGE_RECORD_STATE_HOVER, DAMAGE_RECORD_HOVER),
        LOOP(DAMAGE_RECORD_DECAY_WAIT),
        JUMP(DAMAGE_RECORD_RECHECK),
    },
    /* fire */ {
        DAMAGE_RECORD_READ_SPEED, 10,
        DAMAGE_RECORD_READ_STATE, 2,
        SET_COUNTER(60),
        JUMP(DAMAGE_RECORD_FIRE_WAIT),
    },
    /* fire_wait */ {
        WAIT(1),
        JUMP_IF_STATE(DAMAGE_RECORD_STATE_HOVER, DAMAGE_RECORD_HOVER),
        LOOP(DAMAGE_RECORD_FIRE_WAIT),
        JUMP(DAMAGE_RECORD_RECHECK),
    },
    /* eject */ {
        DAMAGE_RECORD_READ_SPEED, 10,
        DAMAGE_RECORD_READ_STATE, 3,
        SET_COUNTER(60),
        JUMP(DAMAGE_RECORD_EJECT_WAIT),
    },
    /* eject_wait */ {
        WAIT(1),
        JUMP_IF_STATE(DAMAGE_RECORD_STATE_HOVER, DAMAGE_RECORD_HOVER),
        LOOP(DAMAGE_RECORD_EJECT_WAIT),
        JUMP(DAMAGE_RECORD_RECHECK),
    },
    /* hover */ {
        DAMAGE_RECORD_READ_SPEED, 10,
        DAMAGE_RECORD_READ_STATE, 4,
        JUMP(DAMAGE_RECORD_HOVER_WAIT),
    },
    /* hover_wait */ {
        WAIT(1),
        JUMP(DAMAGE_RECORD_HOVER_WAIT),
    },
    /* pause */ {
        WAIT(1),
        LOOP(DAMAGE_RECORD_PAUSE),
        JUMP(DAMAGE_RECORD_RECHECK),
    },
    /* recheck */ {
        WAIT(1),
        JUMP(DAMAGE_RECORD_CHOOSE),
    },
    /* table */ {
        damage_record_scripts.chase, damage_record_scripts.chase_wait, damage_record_scripts.choose, damage_record_scripts.decay, damage_record_scripts.decay_wait, damage_record_scripts.fire,
        damage_record_scripts.fire_wait, damage_record_scripts.eject, damage_record_scripts.eject_wait, damage_record_scripts.hover, damage_record_scripts.hover_wait, damage_record_scripts.pause,
        damage_record_scripts.recheck,
    },
    /* D_8011AFF4 */ damage_record_scripts.chase,
};

ScriptCallEntry D_8011AFF8[5] = {
    {NULL, 0},
    {script_read_speed, 0},
    {script_read_state, 0},
    {func_800C6D68, 0},
    {script_jump_if_near_player, 0},
};

StateEntry D_8011B020[5] = {
    {(u32)obj_chase_player, DAMAGE_RECORD_SCRIPT, 0},
    {(u32)obj_steer_decay_update, DAMAGE_RECORD_SCRIPT, 0},
    {(u32)obj_steer_fire_update, DAMAGE_RECORD_SCRIPT, 0},
    {(u32)obj_steer_spawn_update, DAMAGE_RECORD_SCRIPT, 0},
    {(u32)obj_hover_update, DAMAGE_RECORD_SCRIPT, 0},
};

s32 D_8011B048[3] = {
    -1, -1, -1,
};

ScanEntry D_8011B054 = {{(s32)sound_start_ambient, (s32)end_zone_spawn}, D_8011B048, 0, 0, 0};

CamZone cam_zones[17] = {
    {{0x120, 0x720, -0x6C0, -0x120, -0x2A0, 0x660}, 1},
    {{0xC0, 0x1080, -0x786, -0x3C0, -0xB40, -0x480}, 3},
    {{0x840, 0x1B00, -0xA80, -0x3C0, -0x600, -0x60}, 2},
    {{0x780, 0x1BC0, -0x6D8, -0xC0, -0x180, 0xC00}, 2},
    {{0x840, 0x1620, -0x6F0, -0xC0, -0xFC0, -0xB40}, 2},
    {{0x840, 0x1080, -0x780, -0x3C0, -0x1680, -0xF00}, 2},
    {{0xE40, 0x1BC0, -0xA80, -0x3C0, -0x1C80, -0x15C0}, 2},
    {{0x1380, 0x1C80, -0xA80, -0x6C0, -0x1800, -0xFC0}, 2},
    {{0x1380, 0x1E00, -0xA80, -0x6C0, -0x1080, -0x3C0}, 2},
    {{0xDE0, 0x1620, -0xC00, -0x6C0, -0xF00, -0xC00}, 6},
    {{0x1620, 0x1B60, -0xA20, -0x6C0, -0xFC0, -0xAE0}, 2},
    {{0x7E0, 0x1080, -0xCC0, -0x960, -0xBA0, 0x120}, 4},
    {{0x7E0, 0xE10, -0xCC0, -0x900, -0xFC0, -0xAE0}, 4},
    {{0x7E0, 0x1140, -0xCC0, -0x900, -0x2100, -0xF00}, 4},
    {{0x480, 0x12C0, -0xCC0, -0x900, -0x28E0, -0x2040}, 4},
    {{-0x12C0, 0x600, -0x2BA0, -0xC60, -0x3300, -0xD80}, 8},
    {{-0x1800, 0x840, -0x3600, -0x2FA0, -0x1B00, -0xC00}, 0x18},
};

s32 end_zone_min_x = 0x3C0;

s32 end_zone_max_x = 0x7D0;

s32 end_zone_min_y = -0x34BC;

s32 end_zone_max_y = -0x32C8;

s32 end_zone_min_z = -0x1518;

s32 end_zone_max_z = -0x10CC;

SoundSegmentList ambient_sound_owner = {10, {{{0x468, -0x1B26, -0x2A7C}, 0, {0x468, -0x1B26, -0x2A7C}, 0}, {{0x18, -0x1B26, -0x2432}, 0, {0x18, -0x1B26, -0x2432}, 0}, {{0x468, -0x1B26, -0x1DE2}, 0, {0x468, -0x1B26, -0x1DE2}, 0}, {{-0x1620, -0x3390, -0x1838}, 0, {-0x1620, -0x3390, -0x1838}, 0}, {{-0x1620, -0x3390, -0x12F2}, 0, {-0x1620, -0x3390, -0x12F2}, 0}, {{-0x1620, -0x3390, -0xDA2}, 0, {-0x1620, -0x3390, -0xDA2}, 0}, {{-0x900, -0x3390, -0xDA2}, 0, {-0x900, -0x3390, -0xDA2}, 0}, {{-0x900, -0x3390, -0x1838}, 0, {-0x900, -0x3390, -0x1838}, 0}, {{-0x120, -0x3390, -0xDAC}, 0, {-0x120, -0x3390, -0xDAC}, 0}, {{-0x120, -0x3390, -0x1838}, 0, {-0x120, -0x3390, -0x1838}, 0}}};

PathPoint end_zone_cam_path[21] = {
    {0, 0, 0x1220, 0},
    {0x29B, 0, 0x1220, 0},
    {0x29B, -0x420, -0x64, 0},
    {-0x2A4, -0x420, -0x64, 0},
    {-0x2A4, -0x420, -0x840, 0},
    {0xBA9, -0x420, -0x840, 0},
    {0xBA9, -0x420, -0x18D9, 0},
    {0x1844, -0x6F0, -0x18D9, 0},
    {0x1844, -0x6F0, 0x8CC, 0},
    {0xB8E, -0x9C0, 0x8CC, 0},
    {0xB8E, -0x9C0, -0x3065, 0},
    {-0x630, -0x9C0, -0x3065, 0},
    {-0x630, -0x1DE8, -0x3065, 0},
    {0x246, -0x1DE8, -0x3065, 0},
    {0x246, -0x1A58, -0x3065, 0},
    {0x246, -0x1A58, -0x12DF, 0},
    {0x246, -0x1578, -0x12DF, 0},
    {-0xF90, -0x1578, -0x12DF, 0},
    {-0xF90, -0x2FA0, -0x12DF, 0},
    {-0x9DC, -0x32E8, -0x12DF, 0},
    {0x9DC, -0x32E8, -0x12DF, 0},
};

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_80120074[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/tint_scale_r.c"

s16 video_mode_id = 0;

#include "../stage/data/debug_cam_speed_table.c"

#include "../stage/data/pause_prev_work_area.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_801211F8[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_80121818 = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

s32 spark_pchr_base = 0;

s32 placed_rect_sound_handle = 0;

s32 spark_blend_base = 0;

s16 dreadnought_cycle = 0;

s16 dreadnought_m11_sound_flag = 0;

#include "../stage/data/giant_robot_on_flag.c"

s16 dreadnought_m11_walk_sound_on = 0;

s32 dreadnought_m11_walk_sound_handle = 0;

s16 dreadnought_m11_sfx_count = 0;

#include "../stage/data/fade_red_obj.c"

s32 end_zone_inside_flag = 0;

s32 cam_zone_current = 0;

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

u32 D_80122D14 = 0x00000000;

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

u32 D_80122D98 = 0x00000000;

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

