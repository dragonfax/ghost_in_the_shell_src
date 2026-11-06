/* s03 data 0x801174B4-0x80121000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s03_types.h"
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
extern void door_pattern_base_set();
extern void enemy_ascend_update();
extern void enemy_descend_update();
extern void enemy_face_player();
extern void enemy_fall_update();
extern void enemy_fire_update();
extern void enemy_fly_attack();
extern void enemy_fly_step();
extern void enemy_fly_update();
extern void enemy_hover_update();
extern void enemy_move_or_wait();
extern void enemy_place_spawn();
extern void enemy_salvo_update();
extern void enemy_sound_clear();
extern void enemy_sound_set();
extern void enemy_spawn_from_place();
extern void enemy_state_counter_update();
extern void enemy_twin_gun_update();
extern void enemy_twin_shot_update();
extern void enemy_wait_switch();
extern void enemy_walk_step();
extern u8 file_bomb_ch0_cb4[];
extern u8 file_bomb_ch0_clt[];
extern u8 file_bomb_ch0_vx1[];
extern u8 file_bomb_tp0_clt[];
extern u8 file_bomb_tp0_xs3[];
extern u8 file_bos3_ch0_cb4[];
extern u8 file_bos3_ch0_clt[];
extern u8 file_bos3_ch0_vx1[];
extern u8 file_bos3_ch1_cb4[];
extern u8 file_bos3_ch1_clt[];
extern u8 file_bos3_ch1_vx1[];
extern u8 file_bos3_tp0_clt[];
extern u8 file_bos3_tp0_xs3[];
extern u8 file_bos3_tp1_clt[];
extern u8 file_bos3_tp1_xs3[];
extern u8 file_fap2_ch0_cb4[];
extern u8 file_fap2_ch0_clt[];
extern u8 file_fap2_ch0_vx1[];
extern u8 file_fap2_tp0_clt[];
extern u8 file_fap2_tp0_xs3[];
extern u8 file_fap2_tp1_clt[];
extern u8 file_fap2_tp1_xs3[];
extern u8 file_hou2_ch0_cb4[];
extern u8 file_hou2_ch0_clt[];
extern u8 file_hou2_ch0_vx1[];
extern u8 file_hou2_tp0_clt[];
extern u8 file_hou2_tp0_xs3[];
extern u8 file_mbaz_ch0_cb4[];
extern u8 file_mbaz_ch0_clt[];
extern u8 file_mbaz_ch0_vx1[];
extern u8 file_mbaz_tp0_clt[];
extern u8 file_mbaz_tp0_xs3[];
extern u8 file_msgs_spr_clt[];
extern u8 file_msgs_spr_grc[];
extern u8 file_msgs_spr_so3[];
extern u8 file_mth1_ch0_cb4[];
extern u8 file_mth1_ch0_clt[];
extern u8 file_mth1_ch0_vx1[];
extern u8 file_mth1_tp0_clt[];
extern u8 file_mth1_tp0_xs3[];
extern u8 file_part_ch0_cb4[];
extern void flyer_bank_turn();
extern void flyer_hover_update();
extern void flyer_retreat();
extern void flyer_wander();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void func_800C0328();
extern void gun_turret_2_spawn();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void helicopter2_spawn();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void obj_aim_jittered();
extern void obj_area_update();
extern void obj_call_hook();
extern void obj_countdown_step();
extern void obj_face_player();
extern void obj_hit_handle();
extern void obj_hit_react();
extern void obj_hook_or_free();
extern void obj_jump_if_player_near();
extern void obj_noop();
extern void obj_read_s32();
extern void obj_release_check();
extern void obj_run_hook();
extern void obj_script_jump_within();
extern void obj_set_next_state();
extern void obj_settle_offset();
extern void obj_speed_approach();
extern void obj_state_dispatch();
extern void params_reset();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void ramp_start_script();
extern void receding_wall_door_spawn();
extern void rocket_fuchikoma_spawn();
extern void script_branch_if_player_near();
extern void script_branch_on_flag();
extern void script_clear_salvo_timer();
extern void script_jump_if_beyond_radius();
extern void script_jump_if_facing_player_in_radius();
extern void script_jump_if_flag();
extern void script_jump_if_not_below_speed();
extern void script_jump_near();
extern void script_jump_near_player();
extern void script_op_jump_table_if_player_far();
extern void script_read_long();
extern void script_read_next_state();
extern void script_read_speed();
extern void script_read_speed_long();
extern void script_set_turn_mode();
extern void shot_params_init();
extern void stage_controller_spawn();
extern void stage_state_reset();
extern u8 str_cob_apdea3[];
extern u8 str_cob_cnf_bcf[];
extern u8 str_com_dat_fac[];
extern u8 str_enemy_bomb_data[];
extern u8 str_enemy_bos3_data[];
extern u8 str_enemy_fap2_data[];
extern u8 str_enemy_hou2_data[];
extern u8 str_enemy_mbaz_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_mth1_data[];
extern u8 str_enemy_part_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_m03_dat_fac[];
extern u8 str_m13_cnf_bcf[];
extern u8 str_m13_joy_bin[];
extern u8 str_main_data[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_s03_boss[];
extern u8 str_s03_dat_fac[];
extern u8 str_s03_ene_fac[];
extern u8 str_s03_joy_bin[];
extern u8 str_s03_miss[];
extern u8 str_s03_stage[];
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
extern void time_bomb_spawn();
extern void track_set_enabled();
extern void track_setup();
extern void turret_branch_if_aimed();
extern void turret_track_player();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_80118198[];
extern u8 D_80118569[];
extern u8 D_8011856A[];
extern u8 D_8011856B[];
extern u8 D_80118570[];
extern u8 D_80118BDD[];
extern u8 D_80118BDE[];
extern u8 D_80118BDF[];
extern u8 D_8011F44E[];
extern u8 D_80120B72[];
extern u8 D_80120EC6[];
extern u8 cos_table[];
extern u8 d_80117788[];
extern u8 d_8011778C[];
extern u8 d_80118574[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 d_801201AE[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 enemy_buffer_index[];
extern u8 flow_angle[];
extern u8 gun_hit_effect_table[];
extern u8 msg_offset_y[];
extern u8 pad1_pressed[];
extern u8 rect_x1_table[];
extern u8 rect_y0_table[];
extern u8 rect_y1_table[];
extern u8 rocket_fuchikoma_asset_s10[];
extern u8 rocket_fuchikoma_jump_table_s10[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 view_sincos[];
extern s32 area;
extern ScanItem enemy_scan_table[];
extern AreaEntry area_entry_s03_stage;
extern AreaEntry area_entry_s03_miss;
extern u32 D_80117558[];
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern s32 d_80116660[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *enemy_msgs_files[];
extern ScanEntry d_801166DC;
extern s32 D_801176E8;
extern s32 rect_x0_table[9][8];
extern DrawRequest door_point_table[];
extern SoundSegmentList stage_sound_owner_a;
extern SoundSegmentList stage_sound_owner_b;
extern s32 D_80117B14[];
extern ScanEntry D_80117B20;
extern FxRecordParams bomb_burst_params;
extern RecTemplate bomb_burst_templates[];
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
extern ModelBlockRef d_80117E6C[];
extern ModelBlockRef d_80117E84[];
extern ModelBlockRef d_80117E94[];
extern ModelBlockRange d_80117EA4[];
extern ModelBlockRange d_80117EB4[];
extern ModelBlock mbaz_model_block;
extern u8 *d_80117EE8[];
extern ScanEntry D_80117EF0;
extern SoundVolume enemy_sound_volume_s03[1];
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
extern s16 bazooka_soldier_idle[];
extern s16 bazooka_soldier_wait[];
extern s16 bazooka_soldier_wait_loop[];
extern s16 bazooka_soldier_wander[];
extern s16 bazooka_soldier_patrol[];
extern s16 bazooka_soldier_patrol_loop[];
extern s16 bazooka_soldier_rest_setup[];
extern s16 bazooka_soldier_rest[];
extern s16 bazooka_soldier_rest_loop[];
extern s16 bazooka_soldier_wander_setup[];
extern s16 bazooka_soldier_wander_step[];
extern s16 bazooka_soldier_wander_loop[];
extern s16 bazooka_soldier_wait_short[];
extern s16 bazooka_soldier_wait_short_loop[];
extern s16 bazooka_soldier_hold[];
extern s16 bazooka_soldier_track_wait[];
extern s16 *enemy_script_jumps_s03[16];
extern s16 *enemy_mode_scripts_s03[7];
extern StateEntry enemy_state_table_s03[15];
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
extern s32 helicopter2_asset[3];
extern GunSetup flyer_shot_setup;
extern ModelBlockRef helicopter2_palettes[];
extern ModelBlockRef helicopter2_textures[];
extern ModelBlockRef helicopter2_models[];
extern ModelBlock helicopter2_model_block;
extern u8 *helicopter2_stage_files[];
extern ScanEntry helicopter2_scan_record;
extern s16 helicopter2_script_cfg[4];
extern s16 *helicopter2_script_arg[];
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
extern FxRecordParams time_bomb_burst_params;
extern RecTemplate time_bomb_burst_templates[2];
extern s32 time_bomb_asset[3];
extern ModelBlockRef time_bomb_palette_refs[];
extern ModelBlockRef time_bomb_texture_refs[];
extern ModelBlockRef D_8011873C[];
extern ModelBlockRange time_bomb_model_ranges[];
extern ModelBlock time_bomb_model_block;
extern u8 *time_bomb_stage_files[];
extern ScanEntry time_bomb_scan_entry;
extern StateEntry time_bomb_params[1];
extern s16 time_bomb_script[4];
extern s32 time_bomb_data;
extern s32 D_801187B4;
extern s32 receding_wall_base_index[2];
extern u8 *D_801187C0[];
extern ScanEntry enemy_part_scan_entry;
extern s32 enemy_asset[];
extern ModelBlockRef D_801187EC[];
extern ModelBlockRef D_80118814[];
extern ModelBlockRef D_8011882C[];
extern ModelBlockRange D_80118844[];
extern ModelBlockRange D_8011885C[];
extern ModelBlock enemy_bos3_model_block;
extern u8 *D_801188B8[];
extern ScanEntry enemy_bos3_scan_entry;
extern u32 D_801188DC[];
extern s16 enemy_script_code[];
extern s16 enemy_place_anim_cycle[];
extern s16 enemy_place_anim_open[];
extern s16 enemy_place_anim_open_hold[];
extern s16 enemy_place_anim_close[];
extern s16 enemy_place_anim_close_hold[];
extern ScriptStep enemy_type_table_a[];
extern s16 enemy_place_anim_raise_hold[];
extern ScriptStep enemy_type_table_b[];
extern s16 enemy_place_anim_lower_hold[];
extern s16 enemy_place_anim_fall[];
extern s16 enemy_place_anim_fall_second[];
extern s16 enemy_place_anim_fall_third[];
extern s16 enemy_place_anim_fall_fourth[];
extern s16 enemy_place_anim_fall_fifth[];
extern s16 enemy_place_anim_fall_sixth[];
extern s16 enemy_place_anim_fall_seventh[];
extern s16 enemy_place_anim_fall_eighth[];
extern s16 enemy_place_anim_fall_ninth[];
extern s16 enemy_place_anim_fall_quick_e[];
extern s16 enemy_place_anim_fall_quick_f[];
extern s16 enemy_place_anim_fall_quick_g[];
extern s16 enemy_place_anim_fall_quick_h[];
extern s16 enemy_place_anim_fall_quick_i[];
extern s16 enemy_place_anim_fall_quick_j[];
extern s16 enemy_place_anim_fall_quick_k[];
extern s16 enemy_place_anim_fall_settle_a[];
extern s16 enemy_place_anim_fall_settle_b[];
extern s16 enemy_place_anim_fall_land_a[];
extern s16 enemy_place_anim_fall_land_b[];
extern u16 enemy_buffer_src[];
extern s16 enemy_place_anim_fall_hold[];
extern s16 *enemy_buffer_table[];
extern FxRecordParams ripple_fx_params;
extern s16 enemy_place_await_enable[];
extern s16 enemy_place_dispatch[];
extern s16 enemy_place_idle[];
extern s16 enemy_place_idle_wait[];
extern s16 enemy_place_patrol[];
extern s16 enemy_place_patrol_wait[];
extern s16 enemy_place_ascend[];
extern s16 enemy_place_ascend_wait[];
extern s16 enemy_place_hover[];
extern s16 enemy_place_hover_wait[];
extern s16 enemy_place_descend[];
extern s16 enemy_place_descend_wait[];
extern s16 enemy_place_spotted[];
extern s16 enemy_place_spotted_wait[];
extern s16 enemy_place_twin_gun[];
extern s16 enemy_place_twin_gun_wait[];
extern s16 enemy_place_aim[];
extern s16 enemy_place_aim_wait[];
extern s16 enemy_place_fire_burst[];
extern s16 enemy_place_fire_burst_wait[];
extern s16 enemy_place_salvo[];
extern s16 enemy_place_salvo_wait[];
extern s16 enemy_place_fire[];
extern s16 enemy_place_fire_wait[];
extern s16 enemy_place_cooldown[];
extern s16 enemy_place_cooldown_wait[];
extern s16 enemy_place_disengage[];
extern s16 enemy_place_disengage_wait[];
extern s16 enemy_place_fall[];
extern s16 enemy_place_fall_wait[];
extern s16 enemy_place_fall_guard[];
extern s16 enemy_place_resume[];
extern s16 enemy_place_aim_cycle[];
extern s16 enemy_place_aim_cycle_wait[];
extern s16 enemy_place_cooldown_cycle[];
extern s16 enemy_place_cooldown_cycle_wait[];
extern s16 *enemy_script_data[];
extern s16 *D_80118F58;
extern ScriptCallEntry enemy_callback_table[];
extern StateEntry enemy_state_table[14];
extern StateEntry enemy_death_state_table[];
extern ObjHandlerFn enemy_handler_table[];
extern Words3 shot_asset;
extern s16 enemy_shot_script[];
extern s16 *D_801190A0[];
extern s32 follow_offset_x_table[];
extern s32 follow_offset_z_table[];
extern RecTemplate fade_red_fx_template;
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_8011DCA4[];
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
extern u32 D_8011EE28[];
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
extern u32 D_8011F448;
extern u16 texture_image[];
extern s32 pursue_flag;
extern u32 msg_active_flag;
extern u32 enemies_remaining[];
extern s32 msg_text;
extern s32 cam_pursue_blend;
extern u32 cam_hurry_blend[];
extern s32 msg_wobble_step;
extern s32 cam_orbit_angle;
extern u8 msg_offset_x[];
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
extern s16 door_open_step[];
extern s16 D_801208A8[];
extern GridEntry *bomb_grid_entry;
extern s32 bomb_armed_flag;
extern s32 mission_active_flag;
extern s32 bomb_exploded_flag;
extern s32 door_sound_idx;
extern s32 door_sound_handle;
extern s32 door_pattern_base;
extern s16 enemy_sound_timer;
extern s16 enemy_sound_5042_flag;
extern s16 enemy_sound_5043_flag;
extern s16 enemy_sound_5044_flag;
extern s16 enemy_loop_sound_flag;
extern s32 enemy_loop_sound_id;
extern s16 enemy_alarm_sound_flag;
extern s32 enemy_alarm_sound_id;
extern s16 enemy_death_started_flag;
extern s32 enemy_death_sound_id;
extern s16 enemy_death_sound_flag;
extern s16 D_801208FC;
extern s32 D_80120900;
extern s32 shot_fired_flag;
extern Next800C5620 *fade_red_obj;
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
extern u32 D_801209C0;
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
extern u32 D_80120A44;
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
extern s16 enemy_ai_enabled;
extern s32 light_env_index;
extern s32 player_mode;
extern s32 point_search_below;
extern s32 cur_camera_index;
extern PadInput pad1;
extern PadInput pad_mirror;
extern s32 pspr_top;
extern s16 door_open_level[];
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
extern GridEntry *flagged_grid_cells[];

s32 area = 6;

ScanItem enemy_scan_table[10] = {
    {&d_801166DC, str_enemy_msgs_data},
    {&D_80117B20, str_enemy_msgs_data},
    {&gun_turret_2_scan_entry, str_enemy_hou2_data},
    {&d_80117448, str_enemy_mth1_data},
    {&helicopter2_scan_record, str_enemy_fap2_data},
    {&D_80117EF0, str_enemy_mbaz_data},
    {&time_bomb_scan_entry, str_enemy_bomb_data},
    {&enemy_part_scan_entry, str_enemy_part_data},
    {&enemy_bos3_scan_entry, str_enemy_bos3_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry area_entry_s03_stage = {str_s03_stage, str_cob_cnf_bcf, str_cob_apdea3, str_s03_joy_bin, str_s03_dat_fac, str_s03_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0x400, enemy_scan_table};

AreaEntry area_entry_s03_miss = {str_s03_miss, str_m13_cnf_bcf, NULL, str_m13_joy_bin, str_m03_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

u32 D_80117558[12] = {
    0xFFFFFFFF, 0x00000000, (u32)str_s03_boss, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x10001000, 0x00001000, 0x00000000, (u32)D_80117558,
};

AreaEntry *area_entry_table[3] = {
    &area_entry_s03_miss, &area_entry_s03_stage, NULL,
};

#include "../stage/data/debug_name_buf.c"

#include "../stage/data/d_80116660.c"

s32 msg_id_base = -1;

u32 d_80117920[5] = {
    0x00000000, 0x00000002, 0x00000004, 0x00000006, 0x00000006,
};

u32 d_80117934[5] = {
    0xFFFFFFBE, 0xFFFFFFB2, 0xFFFFFFA9, 0xFFFFFFBE, 0xFFFFFFBE,
};

u32 d_80117948[3] = {
    0x00000018, 0x00000019, 0x0000001A,
};

s32 msg_slot_ids[12] = {
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55,
    0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
};

#include "../stage/data/enemy_msgs_files.c"

#include "../stage/data/d_801166DC.c"

s32 D_801176E8 = 9;

s32 rect_x0_table[9][8] = {
    {-0x12C, -0x8000, 0x15E0, 1, 0x9C4, 0, 0x22C4, 0},
    {0x12C, -0x8000, -0x1004, 1, 0x2904, 0, 0x22C4, 0},
    {0x12C, -0x8000, -0x5AA, 1, 0x3DB8, 0, 0x1194, 0},
    {0x12C, -0x8000, 0x1194, 1, 0x34BC, 0, 0x22C4, 0},
    {-0xE10, -0x8000, -0x12C, 1, -0x12C, 0, 0x9C4, 0},
    {-0x348A, -0x8000, 0x12C, 1, -0x12C, 0, 0x22C4, 0},
    {-0x3714, -0x8000, -0x25E4, 1, -0x2EE0, 0, -0x1324, 0},
    {-0x348A, -0x8000, -0x3520, 1, -0x12C, 0, -0x12C, 0},
    {-0x4BC8, -0x8000, -0x25E4, 1, -0x3714, 0, -0x1324, 0},
};

DrawRequest door_point_table[4] = {
    {0, 0, 0x1C80, 0}, {-0x7A0, 0, 0, 0}, {-0x4268, 0, -0x1CFE, 0}, {0, 0, 0, -1},
};

SoundSegmentList stage_sound_owner_a = {11, {{{0x32FA, -0x1900, -0x1E0}, 0, {0x32FA, 0, -0x1E0}, 0}, {{0x235A, -0x107C, 0x1194}, 0, {0x235A, 0, 0x1194}, 0}, {{0x9C4, -0x1838, 0x1450}, 0, {0x9C4, 0, 0x1450}, 0}, {{-0x1DB0, -0x1800, 0xE10}, 0, {-0x1DB0, 0, 0xE10}, 0}, {{-0x325A, -0x480, 0x483}, 0, {-0x325A, 0, 0x483}, 0}, {{-0x2328, -0x480, 0x483}, 0, {-0x2328, 0, 0x483}, 0}, {{-0x2EF0, -0xC90, 0x18D6}, 0, {-0x2EF0, 0, 0x18D6}, 0}, {{-0x22B0, -0x480, -0x270E}, 0, {-0x22B0, 0, -0x270E}, 0}, {{-0x3148, -0x480, -0x270E}, 0, {-0x3148, 0, -0x270E}, 0}, {{-0x3160, -0x480, -0x20F8}, 0, {-0x3160, 0, -0x20F8}, 0}, {{-0x1B4C, -0xC90, -0x33A4}, 0, {-0x1B4C, 0, -0x33A4}, 0}}};

SoundSegmentList stage_sound_owner_b = {11, {{{0x1E00, 0xC8, 0xAF0}, 0, {0x1E00, 0xC8, 0xC8}, 0}, {{0xC08, 0xC8, -0x400}, 0, {0xC08, 0xC8, 0x5FF}, 0}, {{-0x1388, -0x7F8, 0x1A90}, 0, {-0x1388, 0, 0x1A90}, 0}, {{-0x1B58, -0x600, 0x8AC}, 0, {-0x1B58, 0, 0x8AC}, 0}, {{-0x1356, -0x7F8, -0x7C0}, 0, {-0x1356, 0, -0x7C0}, 0}, {{-0x408, -0x600, -0x1BF4}, 0, {-0x408, 0, -0x1BF4}, 0}, {{-0xD98, -0x7F8, -0x1572}, 0, {-0xD98, 0, -0x1572}, 0}, {{-0x17AC, -0x7F8, -0x2292}, 0, {-0x17AC, 0, -0x2292}, 0}, {{-0x17AE, -0x7F8, -0x2AB4}, 0, {-0x17AE, 0, -0x2AB4}, 0}, {{-0x2D6E, -0x600, -0x32A0}, 0, {-0x2D6E, 0, -0x32A0}, 0}, {{-0x2AB2, -0x660, -0xB40}, 0, {-0x2AB2, 0, -0xB40}, 0}}};

s32 D_80117B14[3] = {
    -1, -1, -1,
};

ScanEntry D_80117B20 = {{(s32)stage_state_reset, (s32)stage_controller_spawn}, D_80117B14, 0, 0, 0};

FxRecordParams bomb_burst_params = {0, 0x80, 0x40, 0x20, 0, 0x28, {0, 0x40000, 0, 0xA000}};

RecTemplate bomb_burst_templates[2] = {
    {3, 0xFF, 0x80, 0x40, 0, 0x10, 0, 0x28000, -0x400, 0x8000},
    {3, 0xFF, 0xFF, 0xFF, 0, 0x14, 0, 0x1E000, -0x400, 0x8000},
};

#include "../stage/data/rocket_fuchikoma_asset.c"

#include "../stage/data/script_call_table.c"

#include "../stage/data/rocket_fuchikoma_state_table.c"

#include "../stage/data/helicopter_asset_slot.c"

#include "../stage/data/d_80117E6C.c"

#include "../stage/data/d_80117E84.c"

#include "../stage/data/d_80117E94.c"

#include "../stage/data/d_80117EA4.c"

#include "../stage/data/d_80117EB4.c"

#include "../stage/data/mbaz_model_block.c"

#include "../stage/data/d_80117EE8.c"

ScanEntry D_80117EF0 = {{(s32)shot_params_init, (s32)enemy_spawn_from_place}, helicopter_asset_slot, (s32)&mbaz_model_block, (s32)d_80117EE8, 0};

SoundVolume enemy_sound_volume_s03[1] = {
    {SND_GROUND_IMPACT | SND_GROUP(2), 0x1000},
};

#include "../stage/data/bazooka_script_table_streams.c"

struct BazookaSoldierScripts {
    s16 idle[6];
    s16 wait[4];
    s16 wait_loop[10];
    s16 wander[6];
    s16 patrol[12];
    s16 patrol_loop[6];
    s16 rest_setup[4];
    s16 rest[4];
    s16 rest_loop[10];
    s16 wander_setup[4];
    s16 wander_step[4];
    s16 wander_loop[10];
    s16 wait_short[4];
    s16 wait_short_loop[10];
    s16 hold[2];
    s16 track_wait[8];
    s16 *table[16];
    s16 *enemy_mode_scripts[7];
} bazooka_soldier_scripts = {
    /* idle */ {
        JUMP_RANDOM(3072, BAZOOKA_SOLDIER_WANDER),
        SET_COUNTER_RANDOM(3, 1),
    },
    /* wait */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* wait_loop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, BAZOOKA_SOLDIER_WAIT_LOOP),
        LOOP(BAZOOKA_SOLDIER_WAIT),
        JUMP(BAZOOKA_SOLDIER_IDLE),
    },
    /* wander */ {
        WAIT(1),
        WANDER(1),
        NEXT_STATE(ENEMY_STATE_WANDER),
    },
    /* patrol */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, BAZOOKA_SOLDIER_PATROL),
        SET_SPEED(0),
        WANDER(1),
        SET_COUNTER_RANDOM(5, 3),
    },
    /* patrol_loop */ {
        WAIT(1),
        LOOP(BAZOOKA_SOLDIER_PATROL_LOOP),
        JUMP(BAZOOKA_SOLDIER_IDLE),
    },
    /* rest_setup */ {
        SET_COUNTER_RANDOM(3, 1),
    },
    /* rest */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* rest_loop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, BAZOOKA_SOLDIER_REST_LOOP),
        LOOP(BAZOOKA_SOLDIER_REST),
        JUMP(BAZOOKA_SOLDIER_REST_SETUP),
    },
    /* wander_setup */ {
        SET_COUNTER_RANDOM(4, 1),
    },
    /* wander_step */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WANDER),
    },
    /* wander_loop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, BAZOOKA_SOLDIER_WANDER_LOOP),
        LOOP(BAZOOKA_SOLDIER_WANDER_STEP),
        JUMP(BAZOOKA_SOLDIER_WANDER_SETUP),
    },
    /* wait_short */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* wait_short_loop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, BAZOOKA_SOLDIER_WAIT_SHORT_LOOP),
        LOOP(BAZOOKA_SOLDIER_WAIT_SHORT),
        JUMP(BAZOOKA_SOLDIER_WANDER_SETUP),
    },
    /* hold */ {
        NEXT_STATE(ENEMY_STATE_HOLD),
    },
    /* track_wait */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_TRACK, BAZOOKA_SOLDIER_TRACK_WAIT),
        JUMP(BAZOOKA_SOLDIER_IDLE),
    },
    /* table */ {
        bazooka_soldier_scripts.idle, bazooka_soldier_scripts.wait, bazooka_soldier_scripts.wait_loop, bazooka_soldier_scripts.wander, bazooka_soldier_scripts.patrol, bazooka_soldier_scripts.patrol_loop,
        bazooka_soldier_scripts.rest_setup, bazooka_soldier_scripts.rest, bazooka_soldier_scripts.rest_loop, bazooka_soldier_scripts.wander_setup, bazooka_soldier_scripts.wander_step, bazooka_soldier_scripts.wander_loop,
        bazooka_soldier_scripts.wait_short, bazooka_soldier_scripts.wait_short_loop, bazooka_soldier_scripts.hold, bazooka_soldier_scripts.track_wait,
    },
    /* enemy_mode_scripts */ {
        bazooka_soldier_scripts.idle, bazooka_soldier_scripts.rest_setup, bazooka_soldier_scripts.wander_setup, bazooka_soldier_scripts.rest_setup, bazooka_soldier_scripts.wander_setup, bazooka_soldier_scripts.hold,
        bazooka_soldier_scripts.rest_setup,
    },
};

StateEntry enemy_state_table_s03[15] = {
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

s32 helicopter2_asset[3] = {
    -1, -1, -1,
};

#include "../stage/data/flyer_shot_setup.c"

#include "../stage/data/helicopter2_palettes.c"

#include "../stage/data/helicopter2_textures.c"

#include "../stage/data/helicopter2_models.c"

#include "../stage/data/helicopter2_model_block.c"

#include "../stage/data/helicopter2_stage_files.c"

ScanEntry helicopter2_scan_record = {{0, (s32)helicopter2_spawn}, helicopter2_asset, (s32)&helicopter2_model_block, (s32)helicopter2_stage_files, 0};

struct Helicopter2ScriptAnims {
    s16 cfg[4];
    s16 *table[1];
} helicopter2_script_anims = {
    /* cfg */ {
        STEP(1, 0),
        GOTO(HELICOPTER2_SCRIPT_CFG),
    },
    /* table */ {
        helicopter2_script_anims.cfg,
    },
};

#include "../stage/data/ground_shadow_params.c"

#include "../stage/data/fx_rec34_params_a.c"

#include "../stage/data/fx_rec34_params_b.c"

#include "../stage/data/helicopter2_scripts.c"

#include "../stage/data/helicopter2_script_calls.c"

StateEntry helicopter2_states[4] = {
    {(u32)enemy_fly_step, HELICOPTER2_SCRIPT_CFG, 0},
    {(u32)enemy_fly_attack, HELICOPTER2_SCRIPT_CFG, 0},
    {(u32)flyer_hover_update, HELICOPTER2_SCRIPT_CFG, 0},
    {(u32)flyer_bank_turn, HELICOPTER2_SCRIPT_CFG, 0},
};

FxRecordParams time_bomb_burst_params = {0, 0x80, 0x40, 0x20, 0, 0x28, {0, 0x40000, 0, 0xA000}};

RecTemplate time_bomb_burst_templates[2] = {
    {3, 0xFF, 0x80, 0x40, 0, 0x10, 0, 0x28000, -0x400, 0x8000},
    {3, 0xFF, 0xFF, 0xFF, 0, 0x14, 0, 0x1E000, -0x400, 0x8000},
};

s32 time_bomb_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef time_bomb_palette_refs[3] = {
    {(s32)file_bomb_ch0_clt, 0, 0},
    {(s32)file_bomb_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef time_bomb_texture_refs[2] = {
    {(s32)file_bomb_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011873C[2] = {
    {(s32)file_bomb_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange time_bomb_model_ranges[2] = {
    {1, 1, 0x800, 0}, {-1, 0, 0, 0},
};

ModelBlock time_bomb_model_block = {(s32)time_bomb_palette_refs, (s32)D_8011873C, (s32)time_bomb_texture_refs, 0, 0, 0, (s32)time_bomb_model_ranges, 0, 0};

u8 *time_bomb_stage_files[2] = {
    file_bomb_ch0_cb4, NULL,
};

ScanEntry time_bomb_scan_entry = {{(s32)obj_noop, (s32)time_bomb_spawn}, time_bomb_asset, (s32)&time_bomb_model_block, (s32)time_bomb_stage_files, 0};

StateEntry time_bomb_params[1] = {
    {0, 0, 0},
};

struct TimeBombAnims {
    s16 script[4];
    s32 table;
} time_bomb_anims = {
    /* script */ {
        STEP(1, 1),
        GOTO(TIME_BOMB_SCRIPT),
    },
    /* table */ (s32)time_bomb_anims.script,
};

s32 D_801187B4 = -1;

s32 receding_wall_base_index[2] = {
    -1, -1,
};

u8 *D_801187C0[2] = {
    file_part_ch0_cb4, NULL,
};

ScanEntry enemy_part_scan_entry = {{(s32)door_pattern_base_set, (s32)receding_wall_door_spawn}, &D_801187B4, 0, (s32)D_801187C0, 0};

s32 enemy_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_801187EC[5] = {
    {(s32)file_bos3_ch0_clt, 0, 0},
    {(s32)file_bos3_tp0_clt, 0, 0},
    {(s32)file_bos3_ch1_clt, 0, 0},
    {(s32)file_bos3_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80118814[3] = {
    {(s32)file_bos3_tp0_xs3, 1, 0},
    {(s32)file_bos3_tp1_xs3, 3, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011882C[3] = {
    {(s32)file_bos3_ch0_vx1, 0, 0},
    {(s32)file_bos3_ch1_vx1, 2, 0},
    {0, 0, 0},
};

ModelBlockRange D_80118844[3] = {
    {0x83, 0x86, 0x2000, 0}, {0x93, 0x96, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlockRange D_8011885C[7] = {
    {0, 0x74, 0x1800, 0}, {0x80, 0x80, 0x10CC, 0}, {0x95, 0x96, 0x10CC, 0}, {0xA0, 0xA1, 0x3C00, 0},
    {0xA2, 0xA3, 0x3000, 0}, {0xA5, 0xA5, 0x733, 0}, {-1, 0, 0, 0},
};

ModelBlock enemy_bos3_model_block = {(s32)D_801187EC, (s32)D_8011882C, (s32)D_80118814, 0, (s32)D_80118844, 0, (s32)D_8011885C, 0, 0};

u8 *D_801188B8[3] = {
    file_bos3_ch0_cb4, file_bos3_ch1_cb4, NULL,
};

ScanEntry enemy_bos3_scan_entry = {{0, (s32)enemy_place_spawn}, enemy_asset, (s32)&enemy_bos3_model_block, (s32)D_801188B8, 0};

u32 D_801188DC[3] = {
    0x10000000, 0x051E0001, 0x051E0002,
};

s16 enemy_script_code[4] = {
    STEP(1, 1),
    GOTO(ENEMY_SCRIPT_CODE),
};

s16 enemy_place_anim_cycle[16] = {
    STEP(8, 1),
    STEP(8, 98),
    STEP(8, 102),
    STEP(8, 106),
    STEP(8, 110),
    STEP(8, 114),
    STEP(8, 1),
    GOTO(ENEMY_PLACE_ANIM_CYCLE),
};

s16 enemy_place_anim_open[102] = {
    STEP(2, 1),
    STEP(2, 2),
    STEP(2, 3),
    STEP(2, 4),
    STEP(2, 5),
    STEP(2, 6),
    STEP(2, 7),
    STEP(2, 8),
    STEP(2, 9),
    STEP(2, 10),
    STEP(2, 11),
    STEP(2, 12),
    STEP(2, 13),
    STEP(2, 14),
    STEP(2, 15),
    STEP(2, 16),
    STEP(2, 17),
    STEP(2, 18),
    STEP(2, 19),
    STEP(2, 20),
    STEP(2, 21),
    STEP(2, 22),
    STEP(2, 23),
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
    STEP(2, 42),
    STEP(2, 43),
    STEP(2, 44),
    STEP(2, 45),
    STEP(2, 46),
    STEP(2, 47),
    STEP(2, 48),
    STEP(2, 49),
    STEP(2, 50),
    GOTO(ENEMY_PLACE_ANIM_OPEN_HOLD),
};

s16 enemy_place_anim_open_hold[4] = {
    STEP(2, 50),
    GOTO(ENEMY_PLACE_ANIM_OPEN_HOLD),
};

s16 enemy_place_anim_close[28] = {
    STEP(1, 50),
    STEP(1, 46),
    STEP(1, 42),
    STEP(1, 38),
    STEP(1, 34),
    STEP(1, 30),
    STEP(1, 26),
    STEP(1, 22),
    STEP(1, 18),
    STEP(1, 14),
    STEP(1, 10),
    STEP(1, 6),
    STEP(1, 2),
    GOTO(ENEMY_PLACE_ANIM_CLOSE_HOLD),
};

s16 enemy_place_anim_close_hold[4] = {
    STEP(2, 1),
    GOTO(ENEMY_PLACE_ANIM_CLOSE_HOLD),
};

ScriptStep enemy_type_table_a[21] = {
    {2, 0x33}, {2, 0x34}, {2, 0x35}, {2, 0x36}, {2, 0x37}, {2, 0x38}, {2, 0x39}, {2, 0x3A}, {2, 0x3B}, {2, 0x3C},
    {2, 0x3D}, {2, 0x3E}, {2, 0x3F}, {2, 0x40}, {2, 0x41}, {2, 0x42}, {2, 0x43}, {2, 0x44}, {2, 0x45}, {2, 0x46},
    {-1, 7},
};

s16 enemy_place_anim_raise_hold[4] = {
    STEP(2, 70),
    GOTO(ENEMY_PLACE_ANIM_RAISE_HOLD),
};

ScriptStep enemy_type_table_b[21] = {
    {2, 0x46}, {2, 0x45}, {2, 0x44}, {2, 0x43}, {2, 0x42}, {2, 0x41}, {2, 0x40}, {2, 0x3F}, {2, 0x3E}, {2, 0x3D},
    {2, 0x3C}, {2, 0x3B}, {2, 0x3A}, {2, 0x39}, {2, 0x38}, {2, 0x37}, {2, 0x36}, {2, 0x35}, {2, 0x34}, {2, 0x33},
    {-1, 9},
};

s16 enemy_place_anim_lower_hold[4] = {
    STEP(2, 51),
    GOTO(ENEMY_PLACE_ANIM_LOWER_HOLD),
};

s16 enemy_place_anim_fall[2] = {
    STEP(8, 72),
};

s16 enemy_place_anim_fall_second[2] = {
    STEP(8, 73),
};

s16 enemy_place_anim_fall_third[2] = {
    STEP(8, 74),
};

s16 enemy_place_anim_fall_fourth[2] = {
    STEP(6, 75),
};

s16 enemy_place_anim_fall_fifth[2] = {
    STEP(6, 76),
};

s16 enemy_place_anim_fall_sixth[2] = {
    STEP(2, 77),
};

s16 enemy_place_anim_fall_seventh[2] = {
    STEP(2, 77),
};

s16 enemy_place_anim_fall_eighth[2] = {
    STEP(2, 78),
};

s16 enemy_place_anim_fall_ninth[2] = {
    STEP(2, 79),
};

s16 enemy_place_anim_fall_quick_e[2] = {
    STEP(2, 80),
};

s16 enemy_place_anim_fall_quick_f[2] = {
    STEP(2, 81),
};

s16 enemy_place_anim_fall_quick_g[2] = {
    STEP(2, 82),
};

s16 enemy_place_anim_fall_quick_h[2] = {
    STEP(2, 83),
};

s16 enemy_place_anim_fall_quick_i[2] = {
    STEP(2, 84),
};

s16 enemy_place_anim_fall_quick_j[2] = {
    STEP(2, 85),
};

s16 enemy_place_anim_fall_quick_k[2] = {
    STEP(2, 86),
};

s16 enemy_place_anim_fall_settle_a[2] = {
    STEP(2, 87),
};

s16 enemy_place_anim_fall_settle_b[2] = {
    STEP(2, 87),
};

s16 enemy_place_anim_fall_land_a[2] = {
    STEP(3, 88),
};

s16 enemy_place_anim_fall_land_b[4] = {
    STEP(3, 88),
    GOTO(ENEMY_PLACE_ANIM_FALL_HOLD),
};

u16 enemy_buffer_src[20] = {
    8, 8, 8, 6, 6, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 3, 3,
};

struct EnemyPlaceAnimFallAnims {
    s16 hold[4];
    s16 *table[31];
} enemy_place_anim_fall_anims = {
    /* hold */ {
        STEP(2, 88),
        GOTO(ENEMY_PLACE_ANIM_FALL_HOLD),
    },
    /* table */ {
        enemy_script_code, enemy_place_anim_cycle, enemy_place_anim_open, enemy_place_anim_open_hold, enemy_place_anim_close, enemy_place_anim_close_hold,
        (s16 *)enemy_type_table_a, enemy_place_anim_raise_hold, (s16 *)enemy_type_table_b, enemy_place_anim_lower_hold, enemy_place_anim_fall, enemy_place_anim_fall_second,
        enemy_place_anim_fall_third, enemy_place_anim_fall_fourth, enemy_place_anim_fall_fifth, enemy_place_anim_fall_sixth, enemy_place_anim_fall_seventh, enemy_place_anim_fall_eighth,
        enemy_place_anim_fall_ninth, enemy_place_anim_fall_quick_e, enemy_place_anim_fall_quick_f, enemy_place_anim_fall_quick_g, enemy_place_anim_fall_quick_h, enemy_place_anim_fall_quick_i,
        enemy_place_anim_fall_quick_j, enemy_place_anim_fall_quick_k, enemy_place_anim_fall_settle_a, enemy_place_anim_fall_settle_b, enemy_place_anim_fall_land_a, enemy_place_anim_fall_land_b,
        enemy_place_anim_fall_anims.hold,
    },
};

FxRecordParams ripple_fx_params = {0, 0x30, 0x30, 0x30, 0x300, 0x40, {0x180000, 0, 0, 0x8000}};

struct EnemyPlaceScripts {
    s16 await_enable[8];
    s16 dispatch[8];
    s16 idle[10];
    s16 idle_wait[10];
    s16 patrol[10];
    s16 patrol_wait[10];
    s16 ascend[10];
    s16 ascend_wait[10];
    s16 hover[8];
    s16 hover_wait[10];
    s16 descend[8];
    s16 descend_wait[10];
    s16 spotted[8];
    s16 spotted_wait[12];
    s16 twin_gun[10];
    s16 twin_gun_wait[18];
    s16 aim[8];
    s16 aim_wait[12];
    s16 fire_burst[10];
    s16 fire_burst_wait[16];
    s16 salvo[10];
    s16 salvo_wait[10];
    s16 fire[8];
    s16 fire_wait[16];
    s16 cooldown[8];
    s16 cooldown_wait[16];
    s16 disengage[8];
    s16 disengage_wait[16];
    s16 fall[6];
    s16 fall_wait[4];
    s16 fall_guard[10];
    s16 resume[8];
    s16 aim_cycle[8];
    s16 aim_cycle_wait[10];
    s16 cooldown_cycle[8];
    s16 cooldown_cycle_wait[10];
    s16 *table[36];
    s16 *D_80118F58;
} enemy_place_scripts = {
    /* await_enable */ {
        WAIT(1),
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_IDLE,
        ENEMY_PLACE_JUMP_IF_FLAG, ENEMY_PLACE_DISPATCH,
        JUMP(ENEMY_PLACE_AWAIT_ENABLE),
    },
    /* dispatch */ {
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        ENEMY_PLACE_BRANCH_IF_PLAYER_NEAR, 2250, ENEMY_PLACE_SPOTTED,
        JUMP(ENEMY_PLACE_PATROL),
    },
    /* idle */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_IDLE,
        SET_COUNTER_RANDOM(64, 64),
        JUMP(ENEMY_PLACE_IDLE_WAIT),
    },
    /* idle_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_IDLE_WAIT),
        JUMP(ENEMY_PLACE_RESUME),
    },
    /* patrol */ {
        ENEMY_PLACE_READ_SPEED, 6,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_WAIT,
        SET_COUNTER_RANDOM(64, 64),
        JUMP(ENEMY_PLACE_PATROL_WAIT),
    },
    /* patrol_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_PATROL_WAIT),
        JUMP(ENEMY_PLACE_RESUME),
    },
    /* ascend */ {
        ENEMY_PLACE_READ_SPEED, 6,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_WANDER,
        ENEMY_PLACE_SOUND_SET,
        SET_COUNTER(100),
        JUMP(ENEMY_PLACE_ASCEND_WAIT),
    },
    /* ascend_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_ASCEND_WAIT),
        JUMP(ENEMY_PLACE_HOVER),
    },
    /* hover */ {
        ENEMY_PLACE_READ_SPEED, -15,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_TRACK,
        SET_COUNTER(100),
        JUMP(ENEMY_PLACE_HOVER_WAIT),
    },
    /* hover_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_HOVER_WAIT),
        JUMP(ENEMY_PLACE_DESCEND),
    },
    /* descend */ {
        ENEMY_PLACE_READ_SPEED, 6,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_FLY_WANDER,
        SET_COUNTER(100),
        JUMP(ENEMY_PLACE_DESCEND_WAIT),
    },
    /* descend_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_DESCEND_WAIT),
        ENEMY_PLACE_SOUND_CLEAR,
        JUMP(ENEMY_PLACE_RESUME),
    },
    /* spotted */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_FACE,
        SET_COUNTER(150),
        JUMP(ENEMY_PLACE_SPOTTED_WAIT),
    },
    /* spotted_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_SPOTTED_WAIT),
        JUMP_RANDOM(1280, ENEMY_PLACE_AIM),
        JUMP(ENEMY_PLACE_TWIN_GUN),
    },
    /* twin_gun */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_RETREAT,
        SET_COUNTER_RANDOM(128, 128),
        JUMP(ENEMY_PLACE_TWIN_GUN_WAIT),
    },
    /* twin_gun_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_TWIN_GUN_WAIT),
        ENEMY_PLACE_BRANCH_IF_PLAYER_NEAR, 1800, ENEMY_PLACE_DISENGAGE,
        ENEMY_PLACE_BRANCH_IF_PLAYER_NEAR, 2250, ENEMY_PLACE_AIM,
        ENEMY_PLACE_BRANCH_IF_PLAYER_NEAR, 2250, ENEMY_PLACE_TWIN_GUN,
        JUMP(ENEMY_PLACE_DISENGAGE),
    },
    /* aim */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_AIM,
        SET_COUNTER(60),
        JUMP(ENEMY_PLACE_AIM_WAIT),
    },
    /* aim_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_AIM_WAIT),
        JUMP_RANDOM(2048, ENEMY_PLACE_SALVO),
        JUMP(ENEMY_PLACE_FIRE_BURST),
    },
    /* fire_burst */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_TWIN_SHOT,
        SET_COUNTER_RANDOM(128, 128),
        JUMP(ENEMY_PLACE_FIRE_BURST_WAIT),
    },
    /* fire_burst_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_FIRE_BURST_WAIT),
        JUMP_RANDOM(2304, ENEMY_PLACE_SALVO),
        ENEMY_PLACE_BRANCH_IF_PLAYER_NEAR, 2250, ENEMY_PLACE_SALVO,
        JUMP(ENEMY_PLACE_COOLDOWN),
    },
    /* salvo */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_CLEAR_SALVO_TIMER,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_SALVO,
        SET_COUNTER(150),
        JUMP(ENEMY_PLACE_SALVO_WAIT),
    },
    /* salvo_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_SALVO_WAIT),
        JUMP(ENEMY_PLACE_FIRE),
    },
    /* fire */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_FIRE,
        SET_COUNTER(150),
        JUMP(ENEMY_PLACE_FIRE_WAIT),
    },
    /* fire_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_FIRE_WAIT),
        ENEMY_PLACE_BRANCH_IF_PLAYER_NEAR, 1800, ENEMY_PLACE_COOLDOWN,
        JUMP_RANDOM(1792, ENEMY_PLACE_COOLDOWN),
        JUMP(ENEMY_PLACE_FIRE_BURST),
    },
    /* cooldown */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_COOLDOWN,
        SET_COUNTER(60),
        JUMP(ENEMY_PLACE_COOLDOWN_WAIT),
    },
    /* cooldown_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_COOLDOWN_WAIT),
        ENEMY_PLACE_BRANCH_IF_PLAYER_NEAR, 1800, ENEMY_PLACE_DISENGAGE,
        ENEMY_PLACE_BRANCH_IF_PLAYER_NEAR, 2250, ENEMY_PLACE_TWIN_GUN,
        JUMP(ENEMY_PLACE_DISENGAGE),
    },
    /* disengage */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_DISENGAGE,
        SET_COUNTER(120),
        JUMP(ENEMY_PLACE_DISENGAGE_WAIT),
    },
    /* disengage_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_DISENGAGE_WAIT),
        JUMP_RANDOM(1024, ENEMY_PLACE_ASCEND),
        ENEMY_PLACE_BRANCH_IF_PLAYER_NEAR, 1800, ENEMY_PLACE_ASCEND,
        JUMP(ENEMY_PLACE_RESUME),
    },
    /* fall */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_FALL,
        JUMP(ENEMY_PLACE_FALL_WAIT),
    },
    /* fall_wait */ {
        WAIT(1),
        JUMP(ENEMY_PLACE_RESUME),
    },
    /* fall_guard */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_FALL_GUARD),
        JUMP(ENEMY_PLACE_RESUME),
    },
    /* resume */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        JUMP(ENEMY_PLACE_DISPATCH),
    },
    /* aim_cycle */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_AIM,
        SET_COUNTER(60),
        JUMP(ENEMY_PLACE_AIM_CYCLE_WAIT),
    },
    /* aim_cycle_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_AIM_CYCLE_WAIT),
        JUMP(ENEMY_PLACE_COOLDOWN_CYCLE),
    },
    /* cooldown_cycle */ {
        ENEMY_PLACE_READ_SPEED, 0,
        ENEMY_PLACE_READ_NEXT_STATE, ENEMY_PLACE_STATE_COOLDOWN,
        SET_COUNTER(60),
        JUMP(ENEMY_PLACE_COOLDOWN_CYCLE_WAIT),
    },
    /* cooldown_cycle_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ENEMY_PLACE_STATE_FALL, ENEMY_PLACE_FALL),
        LOOP(ENEMY_PLACE_COOLDOWN_CYCLE_WAIT),
        JUMP(ENEMY_PLACE_AIM_CYCLE),
    },
    /* table */ {
        enemy_place_scripts.await_enable, enemy_place_scripts.dispatch, enemy_place_scripts.idle, enemy_place_scripts.idle_wait, enemy_place_scripts.patrol, enemy_place_scripts.patrol_wait,
        enemy_place_scripts.ascend, enemy_place_scripts.ascend_wait, enemy_place_scripts.hover, enemy_place_scripts.hover_wait, enemy_place_scripts.descend, enemy_place_scripts.descend_wait,
        enemy_place_scripts.spotted, enemy_place_scripts.spotted_wait, enemy_place_scripts.twin_gun, enemy_place_scripts.twin_gun_wait, enemy_place_scripts.aim, enemy_place_scripts.aim_wait,
        enemy_place_scripts.fire_burst, enemy_place_scripts.fire_burst_wait, enemy_place_scripts.salvo, enemy_place_scripts.salvo_wait, enemy_place_scripts.fire, enemy_place_scripts.fire_wait,
        enemy_place_scripts.cooldown, enemy_place_scripts.cooldown_wait, enemy_place_scripts.disengage, enemy_place_scripts.disengage_wait, enemy_place_scripts.fall, enemy_place_scripts.fall_wait,
        enemy_place_scripts.fall_guard, enemy_place_scripts.resume, enemy_place_scripts.aim_cycle, enemy_place_scripts.aim_cycle_wait, enemy_place_scripts.cooldown_cycle, enemy_place_scripts.cooldown_cycle_wait,
    },
    /* D_80118F58 */ enemy_place_scripts.await_enable,
};

ScriptCallEntry enemy_callback_table[9] = {
    {NULL, 0},
    {script_read_speed, 0},
    {script_read_next_state, 0},
    {func_800C0328, 0},
    {script_branch_if_player_near, 0},
    {script_clear_salvo_timer, 0},
    {script_jump_if_flag, 0},
    {enemy_sound_set, 0},
    {enemy_sound_clear, 0},
};

StateEntry enemy_state_table[14] = {
    {(u32)enemy_state_counter_update, ENEMY_SCRIPT_CODE, 0},
    {(u32)enemy_fly_update, ENEMY_PLACE_ANIM_CYCLE, 0},
    {(u32)enemy_ascend_update, ENEMY_SCRIPT_CODE, 0},
    {(u32)enemy_hover_update, ENEMY_SCRIPT_CODE, 0},
    {(u32)enemy_descend_update, ENEMY_SCRIPT_CODE, 0},
    {(u32)enemy_state_counter_update, ENEMY_PLACE_ANIM_OPEN, 0},
    {(u32)enemy_twin_gun_update, ENEMY_PLACE_ANIM_OPEN_HOLD, 0},
    {(u32)enemy_state_counter_update, ENEMY_PLACE_ANIM_CLOSE, 0},
    {(u32)enemy_state_counter_update, ENEMY_TYPE_TABLE_A, 0},
    {(u32)enemy_twin_shot_update, ENEMY_PLACE_ANIM_RAISE_HOLD, 0},
    {(u32)enemy_salvo_update, ENEMY_PLACE_ANIM_RAISE_HOLD, 0},
    {(u32)enemy_fire_update, ENEMY_PLACE_ANIM_RAISE_HOLD, 0},
    {(u32)enemy_state_counter_update, ENEMY_TYPE_TABLE_B, 0},
    {(u32)enemy_fall_update, ENEMY_PLACE_ANIM_FALL, 0},
};

StateEntry enemy_death_state_table[14] = {
    {(u32)enemy_state_counter_update, 0, 0},
    {(u32)enemy_fly_update, 1, 0},
    {(u32)enemy_ascend_update, 0, 0},
    {(u32)enemy_hover_update, 0, 0},
    {(u32)enemy_descend_update, 0, 0},
    {(u32)enemy_state_counter_update, 2, 0},
    {(u32)enemy_twin_gun_update, 3, 0},
    {(u32)enemy_state_counter_update, 4, 0},
    {(u32)enemy_state_counter_update, 6, 0},
    {(u32)enemy_twin_shot_update, 7, 0},
    {(u32)enemy_salvo_update, 7, 0},
    {(u32)enemy_fire_update, 7, 0},
    {(u32)enemy_state_counter_update, 8, 0},
    {(u32)enemy_fall_update, 0, 0},
};

ObjHandlerFn enemy_handler_table[2] = {
    obj_hit_react, obj_run_hook,
};

Words3 shot_asset = {{-1, -1, -1}};

struct EnemyShotAnims {
    s16 script[4];
    s16 *table[1];
} enemy_shot_anims = {
    /* script */ {
        STEP(1, 165),
        GOTO(ENEMY_SHOT_SCRIPT),
    },
    /* table */ {
        enemy_shot_anims.script,
    },
};

s32 follow_offset_x_table[4] = {
    0x546, 0x177, -0x177, -0x546,
};

s32 follow_offset_z_table[4] = {
    0x384, 0x5DC, 0x5DC, 0x384,
};

#include "../stage/data/fade_red_fx_template.c"

#include "../stage/data/fx_owner_template_a.c"

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_8011DCA4[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/tint_scale_r.c"

s16 video_mode_id = 0;

#include "../stage/data/debug_cam_speed_table.c"

#include "../stage/data/pause_prev_work_area.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_8011EE28[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_8011F448 = 0x00000000;

u16 texture_image[1330] = {
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
    0xA0B, 0x90A,
};

s32 pursue_flag = 0x7080809;

u32 msg_active_flag = 0x05060607;

u32 enemies_remaining[4] = {
    0x03040405, 0x01010203, 0x00000001, 0x00000000,
};

s32 msg_text = 0;

s32 cam_pursue_blend = 0;

u32 cam_hurry_blend[2] = {
    0x10101010, 0x10101010,
};

s32 msg_wobble_step = 0xF0F0F0F;

s32 cam_orbit_angle = 0xE0E0F0F;

u8 msg_offset_x[1396] = {
    0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0A,
    0x0A, 0x0A, 0x09, 0x09, 0x08, 0x08, 0x07, 0x07, 0x06, 0x06, 0x05, 0x05,
    0x04, 0x04, 0x03, 0x03, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E,
    0x0E, 0x0E, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0x0B,
    0x0B, 0x0A, 0x0A, 0x0A, 0x09, 0x09, 0x08, 0x08, 0x08, 0x07, 0x07, 0x06,
    0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x01, 0x01, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0E,
    0x0E, 0x0E, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C,
    0x0C, 0x0B, 0x0B, 0x0B, 0x0A, 0x0A, 0x09, 0x09, 0x09, 0x08, 0x08, 0x07,
    0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x01,
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0x0E, 0x0E,
    0x0E, 0x0E, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C,
    0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0A, 0x0A, 0x09, 0x09, 0x08,
    0x08, 0x08, 0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03,
    0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C,
    0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0A, 0x0A, 0x0A, 0x09,
    0x09, 0x09, 0x08, 0x08, 0x07, 0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x04,
    0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
    0x0C, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0A, 0x0A,
    0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06,
    0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x0C,
    0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0A, 0x0A,
    0x0A, 0x0A, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x06,
    0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01,
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0A, 0x0A, 0x0A,
    0x0A, 0x0A, 0x0A, 0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x07, 0x07,
    0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02,
    0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
    0x0A, 0x0A, 0x0A, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08,
    0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04,
    0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x0A, 0x0A, 0x09,
    0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x04,
    0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x05, 0x05,
    0x05, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02,
    0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x02,
    0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03,
    0x03, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03,
    0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

s16 door_open_step[2] = {
    0, 0,
};

s16 D_801208A8[6] = {
    0, 0, 0, 0, 0, 0,
};

GridEntry *bomb_grid_entry = NULL;

s32 bomb_armed_flag = 0;

s32 mission_active_flag = 0;

s32 bomb_exploded_flag = 0;

s32 door_sound_idx = 0;

s32 door_sound_handle = 0;

s32 door_pattern_base = 0;

s16 enemy_sound_timer = 0;

s16 enemy_sound_5042_flag = 0;

s16 enemy_sound_5043_flag = 0;

s16 enemy_sound_5044_flag = 0;

s16 enemy_loop_sound_flag = 0;

s32 enemy_loop_sound_id = 0;

s16 enemy_alarm_sound_flag = 0;

s32 enemy_alarm_sound_id = 0;

s16 enemy_death_started_flag = 0;

s32 enemy_death_sound_id = 0;

s16 enemy_death_sound_flag = 0;

s16 D_801208FC = 0;

s32 D_80120900 = 0;

s32 shot_fired_flag = 0;

#include "../stage/data/fade_red_obj.c"

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

u32 D_801209C0 = 0x00000000;

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

u32 D_80120A44 = 0x00000000;

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

s16 enemy_ai_enabled = 0;

#include "../stage/data/light_env_index.c"

#include "../stage/data/player_mode.c"

#include "../stage/data/point_search_below.c"

#include "../stage/data/cur_camera_index.c"

#include "../stage/data/pad1.c"

#include "../stage/data/pad_mirror.c"

#include "../stage/data/pspr_top.c"

s16 door_open_level[4] = {
    0, 0, 0, 0,
};

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

GridEntry *flagged_grid_cells[72] = {0};

/* labels inside the objects above */
__asm__(".globl D_8011856B\n.set D_8011856B, ground_shadow_params+0x3\n"
        ".globl D_80118BDF\n.set D_80118BDF, ripple_fx_params+0x3\n"
        ".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl D_8011F44E\n.set D_8011F44E, texture_image+0x2\n"
        ".globl msg_offset_y\n.set msg_offset_y, msg_offset_x+0x2\n"
        ".globl pad1_pressed\n.set pad1_pressed, pad1+0x2\n"
        ".globl D_80120EC6\n.set D_80120EC6, scale_vec+0x2\n"
        ".globl D_8011856A\n.set D_8011856A, ground_shadow_params+0x2\n"
        ".globl D_80118569\n.set D_80118569, ground_shadow_params+0x1\n"
        ".globl D_80118BDE\n.set D_80118BDE, ripple_fx_params+0x2\n"
        ".globl D_80118BDD\n.set D_80118BDD, ripple_fx_params+0x1\n"
        ".globl rect_y0_table\n.set rect_y0_table, rect_x0_table+0x8\n"
        ".globl rect_x1_table\n.set rect_x1_table, rect_x0_table+0x10\n"
        ".globl rect_y1_table\n.set rect_y1_table, rect_x0_table+0x18\n"
        ".globl D_80118198\n.set D_80118198, bazooka_script_table_streams+0x288\n"
        ".globl D_80118570\n.set D_80118570, ground_shadow_params+0x8\n"
        ".globl d_80118574\n.set d_80118574, ground_shadow_params+0xC\n"
        ".globl d_80117788\n.set d_80117788, ripple_fx_params+0x8\n"
        ".globl d_8011778C\n.set d_8011778C, ripple_fx_params+0xC\n"
        ".globl enemy_buffer_index\n.set enemy_buffer_index, enemy_state_table+0x6C\n"
        ".globl sincos_deg90\n.set sincos_deg90, rcossin_tbl+0x1000\n"
        ".globl view_sincos\n.set view_sincos, rcossin_tbl+0x2000\n"
        ".globl rocket_fuchikoma_asset_s10\n.set rocket_fuchikoma_asset_s10, rcossin_tbl+0x29B8\n"
        ".globl rocket_fuchikoma_jump_table_s10\n.set rocket_fuchikoma_jump_table_s10, rcossin_tbl+0x2B94\n"
        ".globl sincos_deg270\n.set sincos_deg270, rcossin_tbl+0x3000\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n"
        ".globl D_80120B72\n.set D_80120B72, view_nudge+0x2\n"
        ".globl d_801201AE\n.set d_801201AE, flow+0x2\n"
        ".globl flow_angle\n.set flow_angle, flow+0x4\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl rocket_fuchikoma_anim_idle\n.set rocket_fuchikoma_anim_idle, rocket_fuchikoma_anims+0x0\n"
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
        ".globl bazooka_soldier_anim_idle\n.set bazooka_soldier_anim_idle, bazooka_script_table_streams+0x0\n"
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
        ".globl bazooka_soldier_idle\n.set bazooka_soldier_idle, bazooka_soldier_scripts+0x0\n"
        ".globl bazooka_soldier_wait\n.set bazooka_soldier_wait, bazooka_soldier_scripts+0xC\n"
        ".globl bazooka_soldier_wait_loop\n.set bazooka_soldier_wait_loop, bazooka_soldier_scripts+0x14\n"
        ".globl bazooka_soldier_wander\n.set bazooka_soldier_wander, bazooka_soldier_scripts+0x28\n"
        ".globl bazooka_soldier_patrol\n.set bazooka_soldier_patrol, bazooka_soldier_scripts+0x34\n"
        ".globl bazooka_soldier_patrol_loop\n.set bazooka_soldier_patrol_loop, bazooka_soldier_scripts+0x4C\n"
        ".globl bazooka_soldier_rest_setup\n.set bazooka_soldier_rest_setup, bazooka_soldier_scripts+0x58\n"
        ".globl bazooka_soldier_rest\n.set bazooka_soldier_rest, bazooka_soldier_scripts+0x60\n"
        ".globl bazooka_soldier_rest_loop\n.set bazooka_soldier_rest_loop, bazooka_soldier_scripts+0x68\n"
        ".globl bazooka_soldier_wander_setup\n.set bazooka_soldier_wander_setup, bazooka_soldier_scripts+0x7C\n"
        ".globl bazooka_soldier_wander_step\n.set bazooka_soldier_wander_step, bazooka_soldier_scripts+0x84\n"
        ".globl bazooka_soldier_wander_loop\n.set bazooka_soldier_wander_loop, bazooka_soldier_scripts+0x8C\n"
        ".globl bazooka_soldier_wait_short\n.set bazooka_soldier_wait_short, bazooka_soldier_scripts+0xA0\n"
        ".globl bazooka_soldier_wait_short_loop\n.set bazooka_soldier_wait_short_loop, bazooka_soldier_scripts+0xA8\n"
        ".globl bazooka_soldier_hold\n.set bazooka_soldier_hold, bazooka_soldier_scripts+0xBC\n"
        ".globl bazooka_soldier_track_wait\n.set bazooka_soldier_track_wait, bazooka_soldier_scripts+0xC0\n"
        ".globl enemy_script_jumps_s03\n.set enemy_script_jumps_s03, bazooka_soldier_scripts+0xD0\n"
        ".globl enemy_mode_scripts_s03\n.set enemy_mode_scripts_s03, bazooka_soldier_scripts+0x110\n"
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
        ".globl helicopter2_script_cfg\n.set helicopter2_script_cfg, helicopter2_script_anims+0x0\n"
        ".globl helicopter2_script_arg\n.set helicopter2_script_arg, helicopter2_script_anims+0x8\n"
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
        ".globl time_bomb_script\n.set time_bomb_script, time_bomb_anims+0x0\n"
        ".globl time_bomb_data\n.set time_bomb_data, time_bomb_anims+0x8\n"
        ".globl enemy_place_anim_fall_hold\n.set enemy_place_anim_fall_hold, enemy_place_anim_fall_anims+0x0\n"
        ".globl enemy_buffer_table\n.set enemy_buffer_table, enemy_place_anim_fall_anims+0x8\n"
        ".globl enemy_place_await_enable\n.set enemy_place_await_enable, enemy_place_scripts+0x0\n"
        ".globl enemy_place_dispatch\n.set enemy_place_dispatch, enemy_place_scripts+0x10\n"
        ".globl enemy_place_idle\n.set enemy_place_idle, enemy_place_scripts+0x20\n"
        ".globl enemy_place_idle_wait\n.set enemy_place_idle_wait, enemy_place_scripts+0x34\n"
        ".globl enemy_place_patrol\n.set enemy_place_patrol, enemy_place_scripts+0x48\n"
        ".globl enemy_place_patrol_wait\n.set enemy_place_patrol_wait, enemy_place_scripts+0x5C\n"
        ".globl enemy_place_ascend\n.set enemy_place_ascend, enemy_place_scripts+0x70\n"
        ".globl enemy_place_ascend_wait\n.set enemy_place_ascend_wait, enemy_place_scripts+0x84\n"
        ".globl enemy_place_hover\n.set enemy_place_hover, enemy_place_scripts+0x98\n"
        ".globl enemy_place_hover_wait\n.set enemy_place_hover_wait, enemy_place_scripts+0xA8\n"
        ".globl enemy_place_descend\n.set enemy_place_descend, enemy_place_scripts+0xBC\n"
        ".globl enemy_place_descend_wait\n.set enemy_place_descend_wait, enemy_place_scripts+0xCC\n"
        ".globl enemy_place_spotted\n.set enemy_place_spotted, enemy_place_scripts+0xE0\n"
        ".globl enemy_place_spotted_wait\n.set enemy_place_spotted_wait, enemy_place_scripts+0xF0\n"
        ".globl enemy_place_twin_gun\n.set enemy_place_twin_gun, enemy_place_scripts+0x108\n"
        ".globl enemy_place_twin_gun_wait\n.set enemy_place_twin_gun_wait, enemy_place_scripts+0x11C\n"
        ".globl enemy_place_aim\n.set enemy_place_aim, enemy_place_scripts+0x140\n"
        ".globl enemy_place_aim_wait\n.set enemy_place_aim_wait, enemy_place_scripts+0x150\n"
        ".globl enemy_place_fire_burst\n.set enemy_place_fire_burst, enemy_place_scripts+0x168\n"
        ".globl enemy_place_fire_burst_wait\n.set enemy_place_fire_burst_wait, enemy_place_scripts+0x17C\n"
        ".globl enemy_place_salvo\n.set enemy_place_salvo, enemy_place_scripts+0x19C\n"
        ".globl enemy_place_salvo_wait\n.set enemy_place_salvo_wait, enemy_place_scripts+0x1B0\n"
        ".globl enemy_place_fire\n.set enemy_place_fire, enemy_place_scripts+0x1C4\n"
        ".globl enemy_place_fire_wait\n.set enemy_place_fire_wait, enemy_place_scripts+0x1D4\n"
        ".globl enemy_place_cooldown\n.set enemy_place_cooldown, enemy_place_scripts+0x1F4\n"
        ".globl enemy_place_cooldown_wait\n.set enemy_place_cooldown_wait, enemy_place_scripts+0x204\n"
        ".globl enemy_place_disengage\n.set enemy_place_disengage, enemy_place_scripts+0x224\n"
        ".globl enemy_place_disengage_wait\n.set enemy_place_disengage_wait, enemy_place_scripts+0x234\n"
        ".globl enemy_place_fall\n.set enemy_place_fall, enemy_place_scripts+0x254\n"
        ".globl enemy_place_fall_wait\n.set enemy_place_fall_wait, enemy_place_scripts+0x260\n"
        ".globl enemy_place_fall_guard\n.set enemy_place_fall_guard, enemy_place_scripts+0x268\n"
        ".globl enemy_place_resume\n.set enemy_place_resume, enemy_place_scripts+0x27C\n"
        ".globl enemy_place_aim_cycle\n.set enemy_place_aim_cycle, enemy_place_scripts+0x28C\n"
        ".globl enemy_place_aim_cycle_wait\n.set enemy_place_aim_cycle_wait, enemy_place_scripts+0x29C\n"
        ".globl enemy_place_cooldown_cycle\n.set enemy_place_cooldown_cycle, enemy_place_scripts+0x2B0\n"
        ".globl enemy_place_cooldown_cycle_wait\n.set enemy_place_cooldown_cycle_wait, enemy_place_scripts+0x2C0\n"
        ".globl enemy_script_data\n.set enemy_script_data, enemy_place_scripts+0x2D4\n"
        ".globl D_80118F58\n.set D_80118F58, enemy_place_scripts+0x364\n"
        ".globl enemy_shot_script\n.set enemy_shot_script, enemy_shot_anims+0x0\n"
        ".globl D_801190A0\n.set D_801190A0, enemy_shot_anims+0x8\n");
