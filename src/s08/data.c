/* s08 data 0x80117260-0x80120800: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s08_types.h"
#include "script.h"
#include "scripts.h"
#include "sounds.h"

extern void axe_soldier_spawn();
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
extern void enemy_approach_player();
extern void enemy_move_or_wait();
extern void enemy_shoot_update();
extern void enemy_track_player();
extern void enemy_wait_switch();
extern void enemy_walk_step();
extern u8 file_bos8_ch0_cb4[];
extern u8 file_bos8_ch0_clt[];
extern u8 file_bos8_ch0_vx1[];
extern u8 file_bos8_ch1_cb4[];
extern u8 file_bos8_ch1_clt[];
extern u8 file_bos8_ch1_vx1[];
extern u8 file_bos8_tp0_clt[];
extern u8 file_bos8_tp0_xs3[];
extern u8 file_bos8_tp1_clt[];
extern u8 file_bos8_tp1_xs3[];
extern u8 file_maxe_ch0_cb4[];
extern u8 file_maxe_ch0_clt[];
extern u8 file_maxe_ch0_vx1[];
extern u8 file_maxe_tp0_clt[];
extern u8 file_maxe_tp0_xs3[];
extern u8 file_maxe_tp1_clt[];
extern u8 file_maxe_tp1_xs3[];
extern u8 file_msgs_spr_clt[];
extern u8 file_msgs_spr_grc[];
extern u8 file_msgs_spr_so3[];
extern u8 file_msub_ch0_cb4[];
extern u8 file_msub_ch0_clt[];
extern u8 file_msub_ch0_vx1[];
extern u8 file_msub_tp0_clt[];
extern u8 file_msub_tp0_xs3[];
extern u8 file_sel2_ch0_cb4[];
extern u8 file_sel2_ch0_clt[];
extern u8 file_sel2_ch0_vx1[];
extern u8 file_sel2_tp0_clt[];
extern u8 file_sel2_tp0_xs3[];
extern u8 file_stk2_ch0_cb4[];
extern u8 file_stk2_ch0_clt[];
extern u8 file_stk2_ch0_vx1[];
extern u8 file_stk2_tp0_clt[];
extern u8 file_stk2_tp0_xs3[];
extern void flyer_retreat();
extern void flyer_wander();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void grid_controller_spawn();
extern void grid_setup();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void laser_drone_attack();
extern void laser_drone_fly();
extern void laser_drone_spawn();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void night_vision_init();
extern void obj_accel_behaviour();
extern void obj_accel_step();
extern void obj_area_update();
extern void obj_call_hook();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_jump_if_near();
extern void obj_jump_if_player_near();
extern void obj_jump_land_step();
extern void obj_land_update();
extern void obj_release_check();
extern void obj_script_read_jump();
extern void obj_script_read_s32();
extern void obj_script_read_speed();
extern void obj_set_next_state();
extern void obj_speed_approach();
extern void obj_stop_behaviour();
extern void obj_turn_hover_update();
extern void obj_turn_stop_behaviour();
extern void obj_weave_update();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void quick_fuchikoma_face_target();
extern void quick_fuchikoma_m8_boss_dash();
extern void quick_fuchikoma_m8_boss_spawn();
extern void ramp_start_script();
extern void rolling_door_init();
extern void rolling_door_spawn();
extern void script_branch_eq();
extern void script_branch_threshold();
extern void script_jump_by_opcode();
extern void script_jump_if_at_least();
extern void script_jump_if_fixed_point_dist();
extern void script_jump_if_in_range();
extern void script_jump_if_player_close();
extern void script_op_jump_if_in_range();
extern void script_op_jump_table_if_player_far();
extern void script_read_mode();
extern void script_set_turn_mode();
extern void show_moving_object_warning();
extern void smg_soldier_spawn();
extern void stationary_rocket_launcher_2_init();
extern void stationary_rocket_launcher_2_spawn();
extern void stationary_rocket_launcher_2_volley();
extern u8 str_b08_dat_fac[];
extern u8 str_b08_ene_fac[];
extern u8 str_com_dat_fac[];
extern u8 str_dor8_ch0cb4[];
extern u8 str_enemy_bos8_data[];
extern u8 str_enemy_ctl8_data[];
extern u8 str_enemy_dor8_data[];
extern u8 str_enemy_maxe_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_msub_data[];
extern u8 str_enemy_oct_data[];
extern u8 str_enemy_sel2_data[];
extern u8 str_enemy_stk2_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_m08_dat_fac[];
extern u8 str_m32_cnf_bcf[];
extern u8 str_m32_joy_bin[];
extern u8 str_main_data[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_s08_boss[];
extern u8 str_s08_dat_fac[];
extern u8 str_s08_ene_fac[];
extern u8 str_s08_miss[];
extern u8 str_s08_stage[];
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
extern u8 str_ubs_apdea3[];
extern u8 str_ubs_cnf_bcf[];
extern u8 str_ubs_joy_bin[];
extern u8 str_ume_apdea3[];
extern u8 str_ume_cnf_bcf[];
extern u8 str_ume_joy_bin[];
extern u8 text_packets[];
extern void text_slot_setup();
extern void track_set_enabled();
extern void track_setup();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_80117E94[];
extern u8 D_8011ECDA[];
extern u8 D_801203EA[];
extern u8 D_80120732[];
extern u8 axe_soldier_hit_pc[];
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
extern u8 pad1_pressed[];
extern u8 quick_fuchikoma_death_pc[];
extern u8 quick_fuchikoma_turn_neg_slot[];
extern u8 quick_fuchikoma_turn_pos_slot[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 smg_soldier_hit_script[];
extern u8 view_sincos[];
extern s32 area;
extern ScanItem D_80117264[];
extern AreaEntry d_80116CA0;
extern AreaEntry d_80116CC8;
extern ScanItem D_801172FC[];
extern AreaEntry d_80116D08;
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern s32 laser_drone_asset[3];
extern ModelBlockRef laser_drone_palettes[];
extern ModelBlockRef laser_drone_textures[];
extern ModelBlockRef laser_drone_models[];
extern ModelBlock laser_drone_model_block;
extern u8 *laser_drone_ptr_table_ids[];
extern ScanEntry laser_drone_scan_entry;
extern s16 laser_drone_script[];
extern s16 *laser_drone_data[];
extern s16 rocket_drone_restart[];
extern s16 rocket_drone_select[];
extern s16 rocket_drone_patrol[];
extern s16 rocket_drone_spotted[];
extern s16 rocket_drone_idle_start[];
extern s16 rocket_drone_idle[];
extern s16 rocket_drone_cooldown[];
extern s16 *rocket_drone_anim[];
extern s16 *d_80116CC0;
extern ScriptCallEntry laser_drone_script_calls[];
extern StateEntry laser_drone_states[];
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
extern s32 stationary_rocket_launcher_2_asset[];
extern ModelBlockRef stationary_rocket_launcher_2_palettes[];
extern ModelBlockRef stationary_rocket_launcher_2_textures[];
extern ModelBlockRef stationary_rocket_launcher_2_models[];
extern ModelBlock stationary_rocket_launcher_2_model_block;
extern u8 *D_801179DC[];
extern ScanEntry D_801179E4;
extern SoundVolume stationary_rocket_launcher_2_sounds[];
extern s16 stationary_rocket_launcher_2_anim_idle[];
extern s16 stationary_rocket_launcher_2_anim_aim[];
extern s16 stationary_rocket_launcher_2_anim_aimed[];
extern s16 stationary_rocket_launcher_2_anim_fire[];
extern s16 stationary_rocket_launcher_2_anim_fired[];
extern s16 stationary_rocket_launcher_2_anim_disengage[];
extern s16 stationary_rocket_launcher_2_anim_stowed[];
extern s16 stationary_rocket_launcher_2_anim_cooldown[];
extern s16 *stationary_rocket_launcher_2_data[];
extern s16 stationary_rocket_launcher_2_idle[];
extern s16 stationary_rocket_launcher_2_aim[];
extern s16 script_count_down[];
extern s16 stationary_rocket_launcher_2_fire_start[];
extern s16 stationary_rocket_launcher_2_fire_loop[];
extern s16 stationary_rocket_launcher_2_cooldown[];
extern s16 stationary_rocket_launcher_2_cooling[];
extern s16 stationary_rocket_launcher_2_refire[];
extern s16 stationary_rocket_launcher_2_disengage[];
extern s16 stationary_rocket_launcher_2_disengaging[];
extern s16 *stationary_rocket_launcher_2_jumps[];
extern s16 *D_80117B08[];
extern ScriptCallEntry stationary_rocket_launcher_2_script_calls[];
extern StateEntry stationary_rocket_launcher_2_states[];
extern s32 axe_soldier_asset[];
extern ModelBlockRef axe_soldier_palettes[];
extern ModelBlockRef axe_soldier_textures[];
extern ModelBlockRef axe_soldier_model_refs[];
extern ModelBlockRange D_80117B98[];
extern ModelBlockRange D_80117BA8[];
extern ModelBlock axe_soldier_model_block;
extern u8 *axe_soldier_ptr_table_ids[];
extern ScanEntry axe_soldier_scan_entry;
extern SoundVolume D_80117BFC[];
extern s16 axe_soldier_anim_idle[];
extern s16 axe_soldier_anim_walk[];
extern s16 axe_soldier_anim_windup[];
extern s16 axe_soldier_anim_swing[];
extern s16 axe_soldier_anim_windup_alt[];
extern s16 axe_soldier_anim_swing_alt[];
extern s16 axe_soldier_anim_attack[];
extern s16 axe_soldier_anim_lunge[];
extern s16 axe_soldier_anim_death[];
extern s16 *axe_soldier_data[];
extern s16 axe_soldier_idle[];
extern s16 axe_soldier_pause[];
extern s16 axe_soldier_pause_repeat[];
extern s16 axe_soldier_walk[];
extern s16 axe_soldier_wander_stop[];
extern s16 axe_soldier_hold[];
extern s16 axe_soldier_pause_alt_start[];
extern s16 axe_soldier_pause_alt[];
extern s16 axe_soldier_pause_alt_loop[];
extern s16 axe_soldier_patrol[];
extern s16 axe_soldier_patrol_walk[];
extern s16 axe_soldier_patrol_loop[];
extern s16 axe_soldier_patrol_wait[];
extern s16 axe_soldier_patrol_wait_loop[];
extern s16 *axe_soldier_jumps[];
extern s16 *D_80117F9C[];
extern StateEntry axe_soldier_states[];
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *enemy_msgs_files[];
extern ScanEntry enemy_msgs_entry;
extern s32 place_asset[];
extern ScanEntry oct_scan_entry;
extern u8 *rolling_door_ptr_table_ids[];
extern s32 D_801180B8;
extern s32 D_801180BC[];
extern ScanEntry rolling_door_scan_entry;
extern s32 D_801180DC[];
extern ScanEntry grid_controller_scan_entry;
extern GridBox grid_box;
extern s32 area_box_x_min;
extern s32 area_box_x_max;
extern s32 area_box_y_min;
extern s32 area_box_y_max;
extern s32 area_box_z_min;
extern s32 area_box_z_max;
extern s32 cam_path_table[];
extern s32 D_80118160[];
extern s16 mission_door_ids[];
extern PathPoint D_801181A8[5];
extern PathPoint mission_cam_path_clear[];
extern s32 quick_fuchikoma_model_asset[3];
extern ModelBlockRef quick_fuchikoma_palette_refs[];
extern ModelBlockRef quick_fuchikoma_texture_refs[];
extern ModelBlockRef quick_fuchikoma_model_refs[];
extern ModelBlockRange D_8011829C[];
extern ModelBlock quick_fuchikoma_model_block;
extern u8 *quick_fuchikoma_ptr_table_ids[];
extern ScanEntry quick_fuchikoma_scan_entry;
extern SoundVolume D_801182FC[];
extern s16 quick_fuchikoma_m8_boss_anim_idle[];
extern s16 quick_fuchikoma_m8_boss_anim_turn_right_start[];
extern s16 quick_fuchikoma_m8_boss_anim_turn_right_loop[];
extern s16 quick_fuchikoma_m8_boss_anim_turn_left_start[];
extern s16 quick_fuchikoma_m8_boss_anim_turn_left_loop[];
extern s16 quick_fuchikoma_m8_boss_anim_settle[];
extern s16 quick_fuchikoma_m8_boss_anim_walk_loop[];
extern s16 quick_fuchikoma_m8_boss_anim_jump_prep[];
extern s16 quick_fuchikoma_m8_boss_anim_jump[];
extern s16 quick_fuchikoma_m8_boss_anim_jump_hold[];
extern s16 quick_fuchikoma_m8_boss_anim_land[];
extern s16 quick_fuchikoma_m8_boss_anim_land_hold[];
extern s16 quick_fuchikoma_death_script[];
extern s16 quick_fuchikoma_m8_boss_anim_death_hold[];
extern s16 *quick_fuchikoma_m8_boss_data[];
extern s16 quick_fuchikoma_m8_boss_enter[];
extern s16 quick_fuchikoma_m8_boss_idle[];
extern s16 quick_fuchikoma_m8_boss_accel_start[];
extern s16 quick_fuchikoma_m8_boss_patrol[];
extern s16 quick_fuchikoma_m8_boss_dash_start[];
extern s16 quick_fuchikoma_m8_boss_close_poll[];
extern s16 quick_fuchikoma_m8_boss_wait_idle[];
extern s16 quick_fuchikoma_m8_boss_coast_start[];
extern s16 quick_fuchikoma_m8_boss_coast_loop[];
extern s16 quick_fuchikoma_m8_boss_close_check[];
extern s16 quick_fuchikoma_m8_boss_far_step[];
extern s16 quick_fuchikoma_m8_boss_far_wait[];
extern s16 quick_fuchikoma_m8_boss_close_action[];
extern s16 quick_fuchikoma_m8_boss_close_wait[];
extern s16 quick_fuchikoma_m8_boss_decide[];
extern s16 quick_fuchikoma_m8_boss_turn_check[];
extern s16 quick_fuchikoma_m8_boss_cruise_wait[];
extern s16 quick_fuchikoma_m8_boss_cruise_start[];
extern s16 quick_fuchikoma_m8_boss_cruise_loop[];
extern s16 quick_fuchikoma_m8_boss_cruise_end[];
extern s16 quick_fuchikoma_m8_boss_halt[];
extern s16 quick_fuchikoma_m8_boss_turn_stop_start[];
extern s16 quick_fuchikoma_m8_boss_turn_stop_wait[];
extern s16 quick_fuchikoma_m8_boss_stop_wait[];
extern s16 quick_fuchikoma_m8_boss_stop_start[];
extern s16 quick_fuchikoma_m8_boss_turn_stop_align[];
extern s16 quick_fuchikoma_m8_boss_cruise_resume[];
extern s16 quick_fuchikoma_m8_boss_weave_start[];
extern s16 quick_fuchikoma_m8_boss_weave_loop[];
extern s16 quick_fuchikoma_m8_boss_weave_check[];
extern s16 quick_fuchikoma_m8_boss_weave_in_view[];
extern s16 quick_fuchikoma_m8_boss_weave_in_view_wait[];
extern s16 quick_fuchikoma_m8_boss_weave_out_view[];
extern s16 quick_fuchikoma_m8_boss_weave_out_view_wait[];
extern s16 quick_fuchikoma_m8_boss_jump_prep[];
extern s16 quick_fuchikoma_m8_boss_jump_prep_wait[];
extern s16 quick_fuchikoma_m8_boss_jump_start[];
extern s16 quick_fuchikoma_m8_boss_jump_land_wait[];
extern s16 quick_fuchikoma_m8_boss_jump_settle_wait[];
extern s16 quick_fuchikoma_m8_boss_jump_settle[];
extern s16 quick_fuchikoma_m8_boss_leap_prep[];
extern s16 quick_fuchikoma_m8_boss_leap_prep_wait[];
extern s16 quick_fuchikoma_m8_boss_leap_start[];
extern s16 quick_fuchikoma_m8_boss_leap_land_wait[];
extern s16 quick_fuchikoma_m8_boss_leap_settle_wait[];
extern s16 quick_fuchikoma_m8_boss_leap_end[];
extern s16 quick_fuchikoma_m8_boss_turn_start[];
extern s16 quick_fuchikoma_m8_boss_turn_wait[];
extern s16 quick_fuchikoma_m8_boss_turn_jump[];
extern s16 quick_fuchikoma_m8_boss_enter_hover[];
extern s16 quick_fuchikoma_m8_boss_enter_hover_wait[];
extern s16 quick_fuchikoma_m8_boss_enter_ready_wait[];
extern s16 quick_fuchikoma_m8_boss_enter_done[];
extern s16 *quick_fuchikoma_jump_table[];
extern ObjLinkValue D_80118814;
extern ScriptCallEntry quick_fuchikoma_m8_boss_calls[];
extern StateEntry quick_fuchikoma_m8_boss_states[];
extern FxRecordParams hit_burst_params;
extern RecTemplate hit_burst_templates[];
extern RecTemplate fade_red_fx_template;
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern s16 video_mode_id;
extern s16 debug_cam_speed_table[][2];
extern s32 pause_prev_work_area;
extern s32 vblank_task_handle;
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_8011D550[];
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
extern u32 D_8011E6B4[];
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
extern u32 D_8011ECD4;
extern u16 texture_image[];
extern u16 stage_image_width;
extern u16 stage_image_height;
extern u32 stage_image_pixels[];
extern s32 hurry_flag;
extern s32 D_8011FEB0;
extern s32 cam_sway_flag;
extern s32 enemies_left;
extern u32 D_8011FEBC[];
extern s32 hurry_msg_flag;
extern u32 D_8011FEEC[];
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
extern s32 night_vision_level;
extern s32 night_vision_target;
extern s32 night_vision_copy_flag;
extern s32 night_vision_active;
extern s32 rolling_door_base;
extern s32 rolling_door_sound_handle;
extern void *grid_entry_count;
extern s32 cam_path_index;
extern s32 mission_area_entered;
extern s16 shared_flags[3];
extern u16 D_8012015A;
extern s32 moving_object_slot;
extern s32 quick_fuchikoma_health_display;
extern s32 boss_defeated_flag;
extern s32 quick_fuchikoma_seq_timer;
extern s32 quick_fuchikoma_seq_state;
extern s32 quick_fuchikoma_back_offset;
extern s32 laser_spark_speed;
extern s32 D_80120178;
extern s32 stage_sound_handle;
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
extern u32 D_80120238;
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
extern u32 D_801202BC;
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
extern s32 rocket_params;
extern s32 D_80120750;
extern s32 D_80120754;
extern s16 D_80120758;
extern s16 D_8012075A;
extern s16 D_8012075C;
extern s16 D_8012075E;
extern s16 D_80120760;
extern s16 D_80120762;
extern s16 D_80120764;
extern s16 D_80120766;
extern s16 D_80120768;
extern s16 D_8012076A;
extern s16 D_8012076C;
extern s16 D_8012076E;
extern GridEntry *flagged_grid_cells[];

s32 area = 0x15;

ScanItem D_80117264[9] = {
    {&laser_drone_scan_entry, str_enemy_sel2_data},
    {&msub_scan_entry, str_enemy_msub_data},
    {&D_801179E4, str_enemy_stk2_data},
    {&axe_soldier_scan_entry, str_enemy_maxe_data},
    {&grid_controller_scan_entry, str_enemy_ctl8_data},
    {&enemy_msgs_entry, str_enemy_msgs_data},
    {&oct_scan_entry, str_enemy_oct_data},
    {&rolling_door_scan_entry, str_enemy_dor8_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116CA0 = {str_s08_stage, str_ume_cnf_bcf, str_ume_apdea3, str_ume_joy_bin, str_s08_dat_fac, str_s08_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0x2000, D_80117264};

AreaEntry d_80116CC8 = {str_s08_miss, str_m32_cnf_bcf, NULL, str_m32_joy_bin, str_m08_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

ScanItem D_801172FC[2] = {
    {&quick_fuchikoma_scan_entry, str_enemy_bos8_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116D08 = {str_s08_boss, str_ubs_cnf_bcf, str_ubs_apdea3, str_ubs_joy_bin, str_b08_dat_fac, str_b08_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, D_801172FC};

#include "../stage/data/area_entry_table.c"

#include "../stage/data/debug_name_buf.c"

s32 laser_drone_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef laser_drone_palettes[3] = {
    {(s32)file_sel2_ch0_clt, 0, 0},
    {(s32)file_sel2_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef laser_drone_textures[2] = {
    {(s32)file_sel2_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef laser_drone_models[2] = {
    {(s32)file_sel2_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock laser_drone_model_block = {(s32)laser_drone_palettes, (s32)laser_drone_models, (s32)laser_drone_textures, 0, 0, 0, 0, 0, 0};

u8 *laser_drone_ptr_table_ids[2] = {
    file_sel2_ch0_cb4, NULL,
};

ScanEntry laser_drone_scan_entry = {{0, (s32)laser_drone_spawn}, laser_drone_asset, (s32)&laser_drone_model_block, (s32)laser_drone_ptr_table_ids, 0};

struct LaserDroneAnims {
    s16 script[4];
    s16 *table[1];
} laser_drone_anims = {
    /* script */ {
        STEP(1, 0),
        GOTO(LASER_DRONE_SCRIPT),
    },
    /* table */ {
        laser_drone_anims.script,
    },
};

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
        LASER_DRONE_JUMP_TABLE_IF_PLAYER_FAR, 3000, ROCKET_DRONE_PATROL,
        LASER_DRONE_JUMP_IF_PLAYER_NEAR, 1800, ROCKET_DRONE_SPOTTED,
        JUMP(ROCKET_DRONE_PATROL),
    },
    /* patrol */ {
        LASER_DRONE_SET_TURN_MODE, 1,
        LASER_DRONE_SPEED_APPROACH, 6,
        LASER_DRONE_SET_NEXT_STATE, LASER_DRONE_STATE_FLY,
        JUMP(ROCKET_DRONE_IDLE_START),
    },
    /* spotted */ {
        LASER_DRONE_SET_TURN_MODE, 0,
        LASER_DRONE_SPEED_APPROACH, 6,
        LASER_DRONE_SET_NEXT_STATE, LASER_DRONE_STATE_ATTACK,
        JUMP(ROCKET_DRONE_IDLE_START),
    },
    /* idle_start */ {
        SET_COUNTER(50),
        JUMP(ROCKET_DRONE_IDLE),
    },
    /* idle */ {
        WAIT(1),
        LOOP(ROCKET_DRONE_IDLE),
        LASER_DRONE_JUMP_IF_PLAYER_NEAR, 500, ROCKET_DRONE_SPOTTED,
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

ScriptCallEntry laser_drone_script_calls[6] = {
    {NULL, 0},
    {obj_speed_approach, 0},
    {obj_set_next_state, 0},
    {script_set_turn_mode, 0},
    {obj_jump_if_player_near, 0},
    {script_op_jump_table_if_player_far, 0},
};

StateEntry laser_drone_states[2] = {
    {(u32)laser_drone_fly, LASER_DRONE_SCRIPT, 0},
    {(u32)laser_drone_attack, LASER_DRONE_SCRIPT, 0},
};

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

#include "../stage/data/smg_soldier_sounds.c"

s32 stationary_rocket_launcher_2_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef stationary_rocket_launcher_2_palettes[3] = {
    {(s32)file_stk2_ch0_clt, 0, 0},
    {(s32)file_stk2_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef stationary_rocket_launcher_2_textures[2] = {
    {(s32)file_stk2_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef stationary_rocket_launcher_2_models[2] = {
    {(s32)file_stk2_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock stationary_rocket_launcher_2_model_block = {(s32)stationary_rocket_launcher_2_palettes, (s32)stationary_rocket_launcher_2_models, (s32)stationary_rocket_launcher_2_textures, 0, 0, 0, 0, 0, 0};

u8 *D_801179DC[2] = {
    file_stk2_ch0_cb4, NULL,
};

ScanEntry D_801179E4 = {{(s32)stationary_rocket_launcher_2_init, (s32)stationary_rocket_launcher_2_spawn}, stationary_rocket_launcher_2_asset, (s32)&stationary_rocket_launcher_2_model_block, (s32)D_801179DC, 0};

SoundVolume stationary_rocket_launcher_2_sounds[1] = {
    {SND_ROCKET_LAUNCHER_AIM | SND_GROUP(2), 0xC00},
};

struct StationaryRocketLauncher2Anims {
    s16 idle[4];
    s16 aim[12];
    s16 aimed[4];
    s16 fire[6];
    s16 fired[4];
    s16 disengage[10];
    s16 stowed[4];
    s16 cooldown[4];
    s16 *table[8];
} stationary_rocket_launcher_2_anims = {
    /* idle */ {
        STEP(4, 1),
        GOTO(STATIONARY_ROCKET_LAUNCHER_2_ANIM_IDLE),
    },
    /* aim */ {
        STEP(1, 1),
        SOUND(0),
        STEP(6, 2),
        STEP(6, 3),
        STEP(6, 4),
        STEP(6, 5),
    },
    /* aimed */ {
        STEP(1, 5),
        GOTO(STATIONARY_ROCKET_LAUNCHER_2_ANIM_AIMED),
    },
    /* fire */ {
        STEP(1, 5),
        STEP(15, 7),
        STEP(15, 5),
    },
    /* fired */ {
        STEP(1, 5),
        GOTO(STATIONARY_ROCKET_LAUNCHER_2_ANIM_FIRED),
    },
    /* disengage */ {
        STEP(1, 5),
        STEP(6, 4),
        STEP(6, 3),
        STEP(6, 2),
        STEP(6, 1),
    },
    /* stowed */ {
        STEP(1, 1),
        GOTO(STATIONARY_ROCKET_LAUNCHER_2_ANIM_STOWED),
    },
    /* cooldown */ {
        STEP(1, 5),
        GOTO(STATIONARY_ROCKET_LAUNCHER_2_ANIM_COOLDOWN),
    },
    /* table */ {
        stationary_rocket_launcher_2_anims.idle, stationary_rocket_launcher_2_anims.aim, stationary_rocket_launcher_2_anims.aimed, stationary_rocket_launcher_2_anims.fire, stationary_rocket_launcher_2_anims.fired, stationary_rocket_launcher_2_anims.disengage,
        stationary_rocket_launcher_2_anims.stowed, stationary_rocket_launcher_2_anims.cooldown,
    },
};

struct StationaryRocketLauncher2JumpsStreams {
    s16 stationary_rocket_launcher_2_idle[8];
    s16 stationary_rocket_launcher_2_aim[4];
    s16 script_count_down[4];
    s16 stationary_rocket_launcher_2_fire_start[2];
    s16 stationary_rocket_launcher_2_fire_loop[8];
    s16 stationary_rocket_launcher_2_cooldown[2];
    s16 stationary_rocket_launcher_2_cooling[4];
    s16 stationary_rocket_launcher_2_refire[4];
    s16 stationary_rocket_launcher_2_disengage[4];
    s16 stationary_rocket_launcher_2_disengaging[6];
    s16 *table[10];
    s16 *D_80117B08[1];
} stationary_rocket_launcher_2_jumps_streams = {
    /* stationary_rocket_launcher_2_idle */ {
        WAIT(1),
        STATIONARY_ROCKET_LAUNCHER_2_JUMP_IF_NEAR, 1800, STATIONARY_ROCKET_LAUNCHER_2_AIM,
        JUMP(STATIONARY_ROCKET_LAUNCHER_2_IDLE),
    },
    /* stationary_rocket_launcher_2_aim */ {
        NEXT_STATE(STATIONARY_ROCKET_LAUNCHER_2_STATE_AIM),
        SET_COUNTER(24),
    },
    /* script_count_down */ {
        WAIT(1),
        LOOP(SCRIPT_COUNT_DOWN),
    },
    /* stationary_rocket_launcher_2_fire_start */ {
        NEXT_STATE(STATIONARY_ROCKET_LAUNCHER_2_STATE_FIRE),
    },
    /* stationary_rocket_launcher_2_fire_loop */ {
        WAIT(1),
        JUMP_IF_STATE(STATIONARY_ROCKET_LAUNCHER_2_STATE_COOLDOWN, STATIONARY_ROCKET_LAUNCHER_2_COOLDOWN),
        JUMP(STATIONARY_ROCKET_LAUNCHER_2_FIRE_LOOP),
    },
    /* stationary_rocket_launcher_2_cooldown */ {
        SET_COUNTER(90),
    },
    /* stationary_rocket_launcher_2_cooling */ {
        WAIT(1),
        LOOP(STATIONARY_ROCKET_LAUNCHER_2_COOLING),
    },
    /* stationary_rocket_launcher_2_refire */ {
        STATIONARY_ROCKET_LAUNCHER_2_JUMP_IF_NEAR, 1800, STATIONARY_ROCKET_LAUNCHER_2_FIRE_START,
    },
    /* stationary_rocket_launcher_2_disengage */ {
        NEXT_STATE(STATIONARY_ROCKET_LAUNCHER_2_STATE_DISENGAGE),
        SET_COUNTER(24),
    },
    /* stationary_rocket_launcher_2_disengaging */ {
        WAIT(1),
        LOOP(STATIONARY_ROCKET_LAUNCHER_2_DISENGAGING),
        JUMP(STATIONARY_ROCKET_LAUNCHER_2_IDLE),
    },
    /* table */ {
        stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_idle, stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_aim, stationary_rocket_launcher_2_jumps_streams.script_count_down, stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_fire_start, stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_fire_loop, stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_cooldown,
        stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_cooling, stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_refire, stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_disengage, stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_disengaging,
    },
    /* D_80117B08 */ {
        stationary_rocket_launcher_2_jumps_streams.stationary_rocket_launcher_2_idle,
    },
};

ScriptCallEntry stationary_rocket_launcher_2_script_calls[2] = {
    {NULL, 0}, {obj_jump_if_near, 0},
};

StateEntry stationary_rocket_launcher_2_states[5] = {
    {0, STATIONARY_ROCKET_LAUNCHER_2_ANIM_IDLE, 1},
    {0, STATIONARY_ROCKET_LAUNCHER_2_ANIM_AIM, 1},
    {(u32)stationary_rocket_launcher_2_volley, STATIONARY_ROCKET_LAUNCHER_2_ANIM_FIRE, 1},
    {0, STATIONARY_ROCKET_LAUNCHER_2_ANIM_DISENGAGE, 1},
    {0, STATIONARY_ROCKET_LAUNCHER_2_ANIM_COOLDOWN, 1},
};

s32 axe_soldier_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef axe_soldier_palettes[4] = {
    {(s32)file_maxe_ch0_clt, 0, 0},
    {(s32)file_maxe_tp0_clt, 0, 0},
    {(s32)file_maxe_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef axe_soldier_textures[3] = {
    {(s32)file_maxe_tp0_xs3, 1, 0},
    {(s32)file_maxe_tp1_xs3, 2, 0},
    {0, 0, 0},
};

ModelBlockRef axe_soldier_model_refs[2] = {
    {(s32)file_maxe_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_80117B98[2] = {
    {0, 0x7F, 0x1666, 0}, {-1, 0, 0, 0},
};

ModelBlockRange D_80117BA8[2] = {
    {0, 0, 0x400, 0x7F}, {-1, 0, 0, 0},
};

ModelBlock axe_soldier_model_block = {(s32)axe_soldier_palettes, (s32)axe_soldier_model_refs, (s32)axe_soldier_textures, (s32)D_80117BA8, 0, 0, (s32)D_80117B98, 0, 0};

u8 *axe_soldier_ptr_table_ids[2] = {
    file_maxe_ch0_cb4, NULL,
};

ScanEntry axe_soldier_scan_entry = {{0, (s32)axe_soldier_spawn}, axe_soldier_asset, (s32)&axe_soldier_model_block, (s32)axe_soldier_ptr_table_ids, 0};

SoundVolume D_80117BFC[3] = {
    {SND_AXE_ATTACK_WINDUP | SND_GROUP(1), 0x800},
    {SND_AXE_ATTACK_STRIKE | SND_GROUP(1), 0xC00},
    {SND_GROUND_IMPACT | SND_GROUP(2), 0x1000},
};

struct AxeSoldierAnims {
    s16 idle[6];
    s16 walk[20];
    s16 windup[4];
    s16 swing[48];
    s16 windup_alt[4];
    s16 swing_alt[48];
    s16 attack[56];
    s16 lunge[76];
    s16 death[46];
    s16 *table[9];
} axe_soldier_anims = {
    /* idle */ {
        FLY(0),
        STEP(40, 1),
        GOTO(AXE_SOLDIER_ANIM_IDLE),
    },
    /* walk */ {
        FLY(0),
        STEP(40, 1),
        STEP(40, 2),
        STEP(40, 2),
        STEP(40, 1),
        STEP(40, 1),
        STEP(40, 3),
        STEP(40, 3),
        STEP(40, 1),
        GOTO(AXE_SOLDIER_ANIM_WALK),
    },
    /* windup */ {
        FLY(0),
        STEP(12, 12),
    },
    /* swing */ {
        STEP(2, 13),
        STEP(2, 14),
        FLY(4),
        STEP(2, 15),
        STEP(2, 16),
        SOUND(2),
        STEP(2, 17),
        STEP(2, 18),
        STEP(2, 19),
        STEP(2, 20),
        STEP(2, 21),
        STEP(2, 22),
        STEP(2, 23),
        STEP(2, 24),
        STEP(2, 5),
        STEP(2, 6),
        SOUND(2),
        STEP(2, 7),
        STEP(2, 8),
        STEP(2, 9),
        STEP(2, 10),
        STEP(2, 11),
        STEP(2, 12),
        GOTO(AXE_SOLDIER_ANIM_SWING),
    },
    /* windup_alt */ {
        FLY(0),
        STEP(1, 31),
    },
    /* swing_alt */ {
        FLY(8),
        STEP(1, 32),
        STEP(1, 33),
        STEP(1, 34),
        STEP(1, 35),
        STEP(1, 36),
        SOUND(2),
        STEP(1, 37),
        STEP(1, 38),
        STEP(1, 39),
        STEP(1, 40),
        STEP(1, 41),
        STEP(1, 42),
        STEP(1, 43),
        STEP(1, 44),
        STEP(1, 45),
        STEP(1, 26),
        SOUND(2),
        STEP(1, 27),
        STEP(1, 28),
        STEP(1, 29),
        STEP(1, 30),
        STEP(1, 31),
        GOTO(AXE_SOLDIER_ANIM_SWING_ALT),
    },
    /* attack */ {
        FLY(0),
        STEP(2, 97),
        STEP(2, 71),
        FLY(3),
        STEP(2, 72),
        STEP(2, 74),
        STEP(2, 75),
        STEP(2, 76),
        STEP(2, 78),
        STEP(2, 79),
        STEP(2, 80),
        SOUND(0),
        STEP(2, 82),
        STEP(2, 83),
        FLY(2),
        STEP(2, 84),
        SET_F8(255),
        SOUND(1),
        STEP(2, 85),
        STEP(2, 86),
        FLY(0),
        STEP(2, 87),
        STEP(2, 88),
        STEP(2, 89),
        STEP(2, 90),
        STEP(2, 91),
        STEP(2, 71),
        GOTO(AXE_SOLDIER_ANIM_IDLE),
    },
    /* lunge */ {
        FLY(0),
        STEP(2, 99),
        STEP(2, 100),
        FLY(2),
        STEP(2, 101),
        STEP(2, 102),
        FLY(6),
        STEP(2, 103),
        STEP(2, 104),
        HOP(18),
        STEP(2, 105),
        STEP(2, 106),
        STEP(3, 107),
        FLY(8),
        STEP(3, 108),
        SOUND(0),
        STEP(3, 109),
        STEP(3, 110),
        SET_F8(255),
        STEP(2, 111),
        SOUND(1),
        STEP(2, 112),
        SET_F8(255),
        FLY(6),
        STEP(2, 113),
        SET_F8(255),
        STEP(2, 114),
        FLY(0),
        STEP(2, 115),
        SET_F8(255),
        STEP(2, 116),
        STEP(2, 117),
        STEP(2, 118),
        STEP(2, 119),
        STEP(2, 120),
        STEP(2, 121),
        STEP(2, 71),
        GOTO(AXE_SOLDIER_ANIM_IDLE),
    },
    /* death */ {
        STEP(2, 49),
        STEP(2, 50),
        STEP(2, 51),
        STEP(2, 52),
        STEP(2, 53),
        STEP(2, 54),
        STEP(2, 55),
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
        STEP(4, 68),
        STEP(8, 69),
        STEP(12, 69),
        GOTO(AXE_SOLDIER_ANIM_DEATH),
    },
    /* table */ {
        axe_soldier_anims.idle, axe_soldier_anims.walk, axe_soldier_anims.windup, axe_soldier_anims.swing, axe_soldier_anims.windup_alt, axe_soldier_anims.swing_alt,
        axe_soldier_anims.attack, axe_soldier_anims.lunge, axe_soldier_anims.death,
    },
};

struct AxeSoldierScripts {
    s16 idle[6];
    s16 pause[4];
    s16 pause_repeat[10];
    s16 walk[6];
    s16 wander_stop[12];
    s16 hold[6];
    s16 pause_alt_start[4];
    s16 pause_alt[4];
    s16 pause_alt_loop[10];
    s16 patrol[4];
    s16 patrol_walk[4];
    s16 patrol_loop[12];
    s16 patrol_wait[4];
    s16 patrol_wait_loop[12];
    s16 *table[14];
    s16 *D_80117F9C[5];
} axe_soldier_scripts = {
    /* idle */ {
        JUMP_RANDOM(3072, AXE_SOLDIER_WALK),
        SET_COUNTER_RANDOM(3, 1),
    },
    /* pause */ {
        WAIT(8),
        NEXT_STATE(AXE_SOLDIER_STATE_PAUSE),
    },
    /* pause_repeat */ {
        WAIT(1),
        JUMP_UNLESS_STATE(AXE_SOLDIER_STATE_IDLE, AXE_SOLDIER_PAUSE_REPEAT),
        LOOP(AXE_SOLDIER_PAUSE),
        JUMP(AXE_SOLDIER_IDLE),
    },
    /* walk */ {
        WAIT(1),
        WANDER(1),
        NEXT_STATE(AXE_SOLDIER_STATE_PATROL),
    },
    /* wander_stop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(AXE_SOLDIER_STATE_IDLE, AXE_SOLDIER_WANDER_STOP),
        SET_SPEED(0),
        WANDER(1),
        SET_COUNTER_RANDOM(5, 3),
    },
    /* hold */ {
        WAIT(1),
        LOOP(AXE_SOLDIER_HOLD),
        JUMP(AXE_SOLDIER_IDLE),
    },
    /* pause_alt_start */ {
        SET_COUNTER_RANDOM(3, 1),
    },
    /* pause_alt */ {
        WAIT(8),
        NEXT_STATE(AXE_SOLDIER_STATE_PAUSE),
    },
    /* pause_alt_loop */ {
        WAIT(1),
        JUMP_UNLESS_STATE(AXE_SOLDIER_STATE_IDLE, AXE_SOLDIER_PAUSE_ALT_LOOP),
        LOOP(AXE_SOLDIER_PAUSE_ALT),
        JUMP(AXE_SOLDIER_PAUSE_ALT_START),
    },
    /* patrol */ {
        SET_COUNTER_RANDOM(4, 1),
    },
    /* patrol_walk */ {
        WAIT(8),
        NEXT_STATE(AXE_SOLDIER_STATE_PATROL),
    },
    /* patrol_loop */ {
        WAIT(1),
        JUMP_IF_STATE(AXE_SOLDIER_STATE_ALERT, AXE_SOLDIER_IDLE),
        JUMP_UNLESS_STATE(AXE_SOLDIER_STATE_IDLE, AXE_SOLDIER_PATROL_LOOP),
        LOOP(AXE_SOLDIER_PATROL_WALK),
        JUMP(AXE_SOLDIER_PATROL),
    },
    /* patrol_wait */ {
        WAIT(8),
        NEXT_STATE(AXE_SOLDIER_STATE_PAUSE),
    },
    /* patrol_wait_loop */ {
        WAIT(1),
        JUMP_IF_STATE(AXE_SOLDIER_STATE_ALERT, AXE_SOLDIER_IDLE),
        JUMP_UNLESS_STATE(AXE_SOLDIER_STATE_IDLE, AXE_SOLDIER_PATROL_WAIT_LOOP),
        LOOP(AXE_SOLDIER_PATROL_WAIT),
        JUMP(AXE_SOLDIER_PATROL),
    },
    /* table */ {
        axe_soldier_scripts.idle, axe_soldier_scripts.pause, axe_soldier_scripts.pause_repeat, axe_soldier_scripts.walk, axe_soldier_scripts.wander_stop, axe_soldier_scripts.hold,
        axe_soldier_scripts.pause_alt_start, axe_soldier_scripts.pause_alt, axe_soldier_scripts.pause_alt_loop, axe_soldier_scripts.patrol, axe_soldier_scripts.patrol_walk, axe_soldier_scripts.patrol_loop,
        axe_soldier_scripts.patrol_wait, axe_soldier_scripts.patrol_wait_loop,
    },
    /* D_80117F9C */ {
        axe_soldier_scripts.idle, axe_soldier_scripts.pause_alt_start, axe_soldier_scripts.patrol, axe_soldier_scripts.pause_alt_start, axe_soldier_scripts.patrol,
    },
};

StateEntry axe_soldier_states[9] = {
    {0, AXE_SOLDIER_ANIM_IDLE, 0},
    {(u32)enemy_wait_switch, AXE_SOLDIER_ANIM_WALK, 0},
    {(u32)enemy_move_or_wait, AXE_SOLDIER_ANIM_WINDUP, 0},
    {(u32)enemy_walk_step, AXE_SOLDIER_ANIM_WINDUP_ALT, 1},
    {(u32)flyer_wander, AXE_SOLDIER_ANIM_WINDUP_ALT, 1},
    {(u32)enemy_approach_player, AXE_SOLDIER_ANIM_LUNGE, 0},
    {(u32)flyer_retreat, AXE_SOLDIER_ANIM_SWING, 0},
    {(u32)enemy_track_player, AXE_SOLDIER_ANIM_ATTACK, 0},
    {0, AXE_SOLDIER_ANIM_DEATH, 0},
};

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

#include "../stage/data/enemy_msgs_files.c"

#include "../stage/data/enemy_msgs_entry.c"

#include "../stage/data/place_asset.c"

ScanEntry oct_scan_entry = {{(s32)night_vision_init, 0}, place_asset, 0, 0, 0};

u8 *rolling_door_ptr_table_ids[2] = {
    str_dor8_ch0cb4, NULL,
};

s32 D_801180B8 = -1;

s32 D_801180BC[2] = {
    -1, -1,
};

ScanEntry rolling_door_scan_entry = {{(s32)rolling_door_init, (s32)rolling_door_spawn}, &D_801180B8, 0, (s32)rolling_door_ptr_table_ids, 0};

s32 D_801180DC[3] = {
    -1, -1, -1,
};

ScanEntry grid_controller_scan_entry = {{(s32)grid_setup, (s32)grid_controller_spawn}, D_801180DC, 0, 0, 0};

GridBox grid_box = {-0x3454, -0x24EA, -0x420, 0, -0x41B9, -0x1CC2};

s32 area_box_x_min = -0x8FC;

s32 area_box_x_max = -0x3E8;

s32 area_box_y_min = -0x7D0;

s32 area_box_y_max = -0x320;

s32 area_box_z_min = -0x52D0;

s32 area_box_z_max = -0x4C90;

s32 cam_path_table[12] = {
    -0x237C, -0x2B8, -0x20D0, 0, -0x237C, -0x2B8,
    -0x3DB0, 0, -0x678, -0x360, -0x5078, 0,
};

s32 D_80118160[17] = {
    4, 0xE8, -0x348, -0x10E, 0, 0x136,
    -0x364, 0x27B, 0x1E, -10, -0x381, 0x546,
    0x41, -10, -0x381, 0x460, 0x67,
};

s16 mission_door_ids[2] = {
    0x55, 0x56,
};

PathPoint D_801181A8[5] = {
    {-10, -0x240, 0x950, 0}, {-10, -0x2D0, -0x7E0, 0}, {0x8F2, -0x2D0, -0x842, 0},
    {0x8F2, -0x2D0, -0x2089, 0}, {-0x2879, 0, -0x20FE, 0},
};

PathPoint mission_cam_path_clear[3] = {
    {-0x1D6E, -0x1B0, -0x3DAE, 0},
    {-0x694, -0x360, -0x3DAE, 0},
    {-0x694, -0x360, -0x5398, 0},
};

s32 quick_fuchikoma_model_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef quick_fuchikoma_palette_refs[5] = {
    {(s32)file_bos8_ch0_clt, 0, 0},
    {(s32)file_bos8_ch1_clt, 0, 0},
    {(s32)file_bos8_tp0_clt, 0, 0},
    {(s32)file_bos8_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef quick_fuchikoma_texture_refs[3] = {
    {(s32)file_bos8_tp0_xs3, 2, 0},
    {(s32)file_bos8_tp1_xs3, 3, 0},
    {0, 0, 0},
};

ModelBlockRef quick_fuchikoma_model_refs[5] = {
    {(s32)file_bos8_ch0_vx1, 0, 0},
    {(s32)file_bos8_ch1_vx1, 1, 0},
    {0, 0, 0},
    {0x7F0000, 0x1000, 0},
    {0xFFFF, 0, 0},
};

ModelBlockRange D_8011829C[3] = {
    {0x80, 0x83, 0x2000, 0}, {0x86, 0x88, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlock quick_fuchikoma_model_block = {(s32)quick_fuchikoma_palette_refs, (s32)quick_fuchikoma_model_refs, (s32)quick_fuchikoma_texture_refs, 0, (s32)D_8011829C, 0, 0, 0, 0};

u8 *quick_fuchikoma_ptr_table_ids[3] = {
    file_bos8_ch0_cb4, file_bos8_ch1_cb4, NULL,
};

ScanEntry quick_fuchikoma_scan_entry = {{(s32)show_moving_object_warning, (s32)quick_fuchikoma_m8_boss_spawn}, quick_fuchikoma_model_asset, (s32)&quick_fuchikoma_model_block, (s32)quick_fuchikoma_ptr_table_ids, 0};

SoundVolume D_801182FC[1] = {
    {0x50E2, 0x1000},
};

struct QuickFuchikomaAnims {
    s16 m8_boss_anim_idle[4];
    s16 m8_boss_anim_turn_right_start[8];
    s16 m8_boss_anim_turn_right_loop[4];
    s16 m8_boss_anim_turn_left_start[8];
    s16 m8_boss_anim_turn_left_loop[4];
    s16 m8_boss_anim_settle[14];
    s16 m8_boss_anim_walk_loop[66];
    s16 m8_boss_anim_jump_prep[50];
    s16 m8_boss_anim_jump[4];
    s16 m8_boss_anim_jump_hold[4];
    s16 m8_boss_anim_land[14];
    s16 m8_boss_anim_land_hold[4];
    s16 death_script[30];
    s16 m8_boss_anim_death_hold[4];
    s16 *table[14];
} quick_fuchikoma_anims = {
    /* m8_boss_anim_idle */ {
        STEP(4, 1),
        GOTO(QUICK_FUCHIKOMA_M8_BOSS_ANIM_IDLE),
    },
    /* m8_boss_anim_turn_right_start */ {
        STEP(8, 117),
        STEP(8, 116),
        STEP(8, 115),
        STEP(8, 114),
    },
    /* m8_boss_anim_turn_right_loop */ {
        STEP(8, 113),
        GOTO(QUICK_FUCHIKOMA_M8_BOSS_ANIM_TURN_RIGHT_LOOP),
    },
    /* m8_boss_anim_turn_left_start */ {
        STEP(8, 123),
        STEP(8, 122),
        STEP(8, 121),
        STEP(8, 120),
    },
    /* m8_boss_anim_turn_left_loop */ {
        STEP(8, 119),
        GOTO(QUICK_FUCHIKOMA_M8_BOSS_ANIM_TURN_LEFT_LOOP),
    },
    /* m8_boss_anim_settle */ {
        STEP(3, 1),
        STEP(3, 26),
        STEP(2, 27),
        STEP(2, 28),
        STEP(1, 29),
        STEP(1, 30),
        STEP(0, 31),
    },
    /* m8_boss_anim_walk_loop */ {
        STEP(0, 32),
        SOUND(0),
        STEP(0, 33),
        STEP(0, 34),
        STEP(0, 35),
        STEP(0, 36),
        STEP(0, 37),
        STEP(0, 38),
        STEP(0, 39),
        STEP(0, 40),
        STEP(0, 41),
        STEP(0, 42),
        STEP(0, 43),
        STEP(0, 44),
        STEP(0, 45),
        STEP(0, 46),
        STEP(0, 17),
        SOUND(0),
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
        STEP(0, 31),
        GOTO(QUICK_FUCHIKOMA_M8_BOSS_ANIM_WALK_LOOP),
    },
    /* m8_boss_anim_jump_prep */ {
        STEP(0, 49),
        STEP(0, 50),
        STEP(0, 51),
        STEP(0, 52),
        STEP(0, 53),
        STEP(0, 54),
        STEP(0, 55),
        STEP(0, 56),
        STEP(0, 57),
        STEP(0, 58),
        STEP(0, 59),
        STEP(0, 60),
        STEP(0, 61),
        STEP(0, 62),
        STEP(0, 63),
        STEP(0, 64),
        STEP(0, 65),
        STEP(0, 66),
        STEP(0, 67),
        STEP(0, 68),
        STEP(0, 69),
        STEP(0, 70),
        STEP(0, 71),
        STEP(0, 72),
        GOTO(QUICK_FUCHIKOMA_M8_BOSS_ANIM_JUMP),
    },
    /* m8_boss_anim_jump */ {
        STEP(0, 73),
        STEP(0, 74),
    },
    /* m8_boss_anim_jump_hold */ {
        STEP(0, 75),
        GOTO(QUICK_FUCHIKOMA_M8_BOSS_ANIM_JUMP_HOLD),
    },
    /* m8_boss_anim_land */ {
        STEP(1, 76),
        STEP(1, 77),
        STEP(1, 78),
        STEP(1, 79),
        STEP(1, 80),
        STEP(1, 81),
        STEP(1, 82),
    },
    /* m8_boss_anim_land_hold */ {
        STEP(1, 83),
        GOTO(QUICK_FUCHIKOMA_M8_BOSS_ANIM_LAND_HOLD),
    },
    /* death_script */ {
        STEP(4, 97),
        STEP(4, 98),
        STEP(4, 99),
        STEP(4, 100),
        STEP(4, 101),
        STEP(4, 102),
        STEP(4, 103),
        STEP(4, 104),
        STEP(4, 105),
        STEP(4, 106),
        STEP(4, 107),
        STEP(4, 108),
        STEP(4, 109),
        STEP(4, 110),
        STEP(4, 111),
    },
    /* m8_boss_anim_death_hold */ {
        STEP(4, 111),
        GOTO(QUICK_FUCHIKOMA_M8_BOSS_ANIM_DEATH_HOLD),
    },
    /* table */ {
        quick_fuchikoma_anims.m8_boss_anim_idle, quick_fuchikoma_anims.m8_boss_anim_turn_right_start, quick_fuchikoma_anims.m8_boss_anim_turn_right_loop, quick_fuchikoma_anims.m8_boss_anim_turn_left_start, quick_fuchikoma_anims.m8_boss_anim_turn_left_loop, quick_fuchikoma_anims.m8_boss_anim_settle,
        quick_fuchikoma_anims.m8_boss_anim_walk_loop, quick_fuchikoma_anims.m8_boss_anim_jump_prep, quick_fuchikoma_anims.m8_boss_anim_jump, quick_fuchikoma_anims.m8_boss_anim_jump_hold, quick_fuchikoma_anims.m8_boss_anim_land, quick_fuchikoma_anims.m8_boss_anim_land_hold,
        quick_fuchikoma_anims.death_script, quick_fuchikoma_anims.m8_boss_anim_death_hold,
    },
};

struct QuickFuchikomaM8BossScripts {
    s16 enter[2];
    s16 idle[6];
    s16 accel_start[6];
    s16 patrol[14];
    s16 dash_start[2];
    s16 close_poll[8];
    s16 wait_idle[8];
    s16 coast_start[4];
    s16 coast_loop[10];
    s16 close_check[6];
    s16 far_step[2];
    s16 far_wait[8];
    s16 close_action[2];
    s16 close_wait[8];
    s16 decide[8];
    s16 turn_check[4];
    s16 cruise_wait[6];
    s16 cruise_start[8];
    s16 cruise_loop[8];
    s16 cruise_end[8];
    s16 halt[8];
    s16 turn_stop_start[2];
    s16 turn_stop_wait[10];
    s16 stop_wait[6];
    s16 stop_start[2];
    s16 turn_stop_align[10];
    s16 cruise_resume[6];
    s16 weave_start[2];
    s16 weave_loop[6];
    s16 weave_check[4];
    s16 weave_in_view[2];
    s16 weave_in_view_wait[8];
    s16 weave_out_view[2];
    s16 weave_out_view_wait[8];
    s16 jump_prep[2];
    s16 jump_prep_wait[6];
    s16 jump_start[2];
    s16 jump_land_wait[8];
    s16 jump_settle_wait[6];
    s16 jump_settle[4];
    s16 leap_prep[2];
    s16 leap_prep_wait[6];
    s16 leap_start[2];
    s16 leap_land_wait[8];
    s16 leap_settle_wait[6];
    s16 leap_end[8];
    s16 turn_start[2];
    s16 turn_wait[8];
    s16 turn_jump[2];
    s16 enter_hover[2];
    s16 enter_hover_wait[8];
    s16 enter_ready_wait[6];
    s16 enter_done[4];
    s16 *table[53];
    ObjLinkValue D_80118814;
} quick_fuchikoma_m8_boss_scripts = {
    /* enter */ {
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_ENTER_HOVER),
    },
    /* idle */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_JUMP, QUICK_FUCHIKOMA_M8_BOSS_ACCEL_START,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_IDLE),
    },
    /* accel_start */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_S32, 4096, 0,
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_ACCEL),
    },
    /* patrol */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_FIXED_POINT_DIST, -1001, QUICK_FUCHIKOMA_M8_BOSS_DECIDE,
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_IN_RANGE_6, 512, QUICK_FUCHIKOMA_M8_BOSS_DASH_START,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_PATROL),
    },
    /* dash_start */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_DASH),
    },
    /* close_poll */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_AT_LEAST, 8192, 1, QUICK_FUCHIKOMA_M8_BOSS_CLOSE_CHECK,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_CLOSE_POLL),
    },
    /* wait_idle */ {
        WAIT(1),
        JUMP_IF_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_IDLE, QUICK_FUCHIKOMA_M8_BOSS_COAST_START),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_WAIT_IDLE),
    },
    /* coast_start */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_ACCEL),
        SET_COUNTER(30),
    },
    /* coast_loop */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_FIXED_POINT_DIST, -1001, QUICK_FUCHIKOMA_M8_BOSS_DECIDE,
        LOOP(QUICK_FUCHIKOMA_M8_BOSS_COAST_LOOP),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_IDLE),
    },
    /* close_check */ {
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_PLAYER_CLOSE, 2000, QUICK_FUCHIKOMA_M8_BOSS_CLOSE_ACTION,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_FAR_STEP),
    },
    /* far_step */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_MODE, 4,
    },
    /* far_wait */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_BRANCH_EQ, 0, QUICK_FUCHIKOMA_M8_BOSS_WAIT_IDLE,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_FAR_WAIT),
    },
    /* close_action */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_MODE, 2,
    },
    /* close_wait */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_BRANCH_EQ, 0, QUICK_FUCHIKOMA_M8_BOSS_WAIT_IDLE,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_CLOSE_WAIT),
    },
    /* decide */ {
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_IN_RANGE_11, QUICK_FUCHIKOMA_M8_BOSS_TURN_START,
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_IN_RANGE_6, 128, QUICK_FUCHIKOMA_M8_BOSS_HALT,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_CRUISE_WAIT),
    },
    /* turn_check */ {
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_IN_RANGE_11, QUICK_FUCHIKOMA_M8_BOSS_TURN_START,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_CRUISE_WAIT),
    },
    /* cruise_wait */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_JUMP, QUICK_FUCHIKOMA_M8_BOSS_CRUISE_START,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_CRUISE_WAIT),
    },
    /* cruise_start */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_S32, 4096, 0,
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_CRUISE),
        QUICK_FUCHIKOMA_M8_BOSS_READ_MODE, 3,
    },
    /* cruise_loop */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_FIXED_POINT_DIST, 480, QUICK_FUCHIKOMA_M8_BOSS_CRUISE_END,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_CRUISE_LOOP),
    },
    /* cruise_end */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_BRANCH_EQ, 0, QUICK_FUCHIKOMA_M8_BOSS_IDLE,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_CRUISE_END),
    },
    /* halt */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_SPEED, 0, 0,
        QUICK_FUCHIKOMA_M8_BOSS_READ_MODE, 1,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_STOP_WAIT),
    },
    /* turn_stop_start */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_TURN_STOP),
    },
    /* turn_stop_wait */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_BRANCH_EQ, 0, QUICK_FUCHIKOMA_M8_BOSS_CRUISE_RESUME,
        QUICK_FUCHIKOMA_M8_BOSS_BRANCH_THRESHOLD, 32, QUICK_FUCHIKOMA_M8_BOSS_STOP_WAIT,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_TURN_STOP_WAIT),
    },
    /* stop_wait */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_JUMP, QUICK_FUCHIKOMA_M8_BOSS_STOP_START,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_STOP_WAIT),
    },
    /* stop_start */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_STOP),
    },
    /* turn_stop_align */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_BRANCH_EQ, 0, QUICK_FUCHIKOMA_M8_BOSS_CRUISE_RESUME,
        QUICK_FUCHIKOMA_M8_BOSS_BRANCH_THRESHOLD, 32, QUICK_FUCHIKOMA_M8_BOSS_TURN_STOP_ALIGN,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_TURN_STOP_START),
    },
    /* cruise_resume */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_JUMP, QUICK_FUCHIKOMA_M8_BOSS_CRUISE_WAIT,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_CRUISE_RESUME),
    },
    /* weave_start */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_WEAVE),
    },
    /* weave_loop */ {
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_IF_IN_RANGE_6, 128, QUICK_FUCHIKOMA_M8_BOSS_WEAVE_IN_VIEW,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_WEAVE_OUT_VIEW),
    },
    /* weave_check */ {
        QUICK_FUCHIKOMA_M8_BOSS_JUMP_BY_OPCODE, QUICK_FUCHIKOMA_M8_BOSS_LEAP_PREP,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_WEAVE_LOOP),
    },
    /* weave_in_view */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_MODE, 4,
    },
    /* weave_in_view_wait */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_BRANCH_EQ, 0, QUICK_FUCHIKOMA_M8_BOSS_WEAVE_LOOP,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_WEAVE_IN_VIEW_WAIT),
    },
    /* weave_out_view */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_MODE, 3,
    },
    /* weave_out_view_wait */ {
        WAIT(1),
        QUICK_FUCHIKOMA_M8_BOSS_BRANCH_EQ, 0, QUICK_FUCHIKOMA_M8_BOSS_WEAVE_CHECK,
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_WEAVE_OUT_VIEW_WAIT),
    },
    /* jump_prep */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_JUMP_PREP),
    },
    /* jump_prep_wait */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_JUMP, QUICK_FUCHIKOMA_M8_BOSS_JUMP_START,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_JUMP_PREP_WAIT),
    },
    /* jump_start */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_JUMP),
    },
    /* jump_land_wait */ {
        WAIT(1),
        JUMP_IF_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_LANDED, QUICK_FUCHIKOMA_M8_BOSS_JUMP_SETTLE_WAIT),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_JUMP_LAND_WAIT),
    },
    /* jump_settle_wait */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_JUMP, QUICK_FUCHIKOMA_M8_BOSS_JUMP_SETTLE,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_JUMP_SETTLE_WAIT),
    },
    /* jump_settle */ {
        WAIT(30),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_WEAVE_START),
    },
    /* leap_prep */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_JUMP_PREP),
    },
    /* leap_prep_wait */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_JUMP, QUICK_FUCHIKOMA_M8_BOSS_LEAP_START,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_LEAP_PREP_WAIT),
    },
    /* leap_start */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_LEAP),
    },
    /* leap_land_wait */ {
        WAIT(1),
        JUMP_IF_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_LANDED, QUICK_FUCHIKOMA_M8_BOSS_LEAP_SETTLE_WAIT),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_LEAP_LAND_WAIT),
    },
    /* leap_settle_wait */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_JUMP, QUICK_FUCHIKOMA_M8_BOSS_LEAP_END,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_LEAP_SETTLE_WAIT),
    },
    /* leap_end */ {
        WAIT(8),
        JUMP_RANDOM(2662, QUICK_FUCHIKOMA_M8_BOSS_HALT),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_CRUISE_WAIT),
    },
    /* turn_start */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_TURN),
    },
    /* turn_wait */ {
        WAIT(1),
        JUMP_IF_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_IDLE, QUICK_FUCHIKOMA_M8_BOSS_TURN_JUMP),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_TURN_WAIT),
    },
    /* turn_jump */ {
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_JUMP_PREP),
    },
    /* enter_hover */ {
        NEXT_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_HOVER),
    },
    /* enter_hover_wait */ {
        WAIT(1),
        JUMP_IF_STATE(QUICK_FUCHIKOMA_M8_BOSS_STATE_LANDED, QUICK_FUCHIKOMA_M8_BOSS_ENTER_READY_WAIT),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_ENTER_HOVER_WAIT),
    },
    /* enter_ready_wait */ {
        QUICK_FUCHIKOMA_M8_BOSS_READ_JUMP, QUICK_FUCHIKOMA_M8_BOSS_ENTER_DONE,
        WAIT(1),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_ENTER_READY_WAIT),
    },
    /* enter_done */ {
        WAIT(8),
        JUMP(QUICK_FUCHIKOMA_M8_BOSS_IDLE),
    },
    /* table */ {
        quick_fuchikoma_m8_boss_scripts.enter, quick_fuchikoma_m8_boss_scripts.idle, quick_fuchikoma_m8_boss_scripts.accel_start, quick_fuchikoma_m8_boss_scripts.patrol, quick_fuchikoma_m8_boss_scripts.dash_start, quick_fuchikoma_m8_boss_scripts.close_poll,
        quick_fuchikoma_m8_boss_scripts.wait_idle, quick_fuchikoma_m8_boss_scripts.coast_start, quick_fuchikoma_m8_boss_scripts.coast_loop, quick_fuchikoma_m8_boss_scripts.close_check, quick_fuchikoma_m8_boss_scripts.far_step, quick_fuchikoma_m8_boss_scripts.far_wait,
        quick_fuchikoma_m8_boss_scripts.close_action, quick_fuchikoma_m8_boss_scripts.close_wait, quick_fuchikoma_m8_boss_scripts.decide, quick_fuchikoma_m8_boss_scripts.turn_check, quick_fuchikoma_m8_boss_scripts.cruise_wait, quick_fuchikoma_m8_boss_scripts.cruise_start,
        quick_fuchikoma_m8_boss_scripts.cruise_loop, quick_fuchikoma_m8_boss_scripts.cruise_end, quick_fuchikoma_m8_boss_scripts.halt, quick_fuchikoma_m8_boss_scripts.turn_stop_start, quick_fuchikoma_m8_boss_scripts.turn_stop_wait, quick_fuchikoma_m8_boss_scripts.stop_wait,
        quick_fuchikoma_m8_boss_scripts.stop_start, quick_fuchikoma_m8_boss_scripts.turn_stop_align, quick_fuchikoma_m8_boss_scripts.cruise_resume, quick_fuchikoma_m8_boss_scripts.weave_start, quick_fuchikoma_m8_boss_scripts.weave_loop, quick_fuchikoma_m8_boss_scripts.weave_check,
        quick_fuchikoma_m8_boss_scripts.weave_in_view, quick_fuchikoma_m8_boss_scripts.weave_in_view_wait, quick_fuchikoma_m8_boss_scripts.weave_out_view, quick_fuchikoma_m8_boss_scripts.weave_out_view_wait, quick_fuchikoma_m8_boss_scripts.jump_prep, quick_fuchikoma_m8_boss_scripts.jump_prep_wait,
        quick_fuchikoma_m8_boss_scripts.jump_start, quick_fuchikoma_m8_boss_scripts.jump_land_wait, quick_fuchikoma_m8_boss_scripts.jump_settle_wait, quick_fuchikoma_m8_boss_scripts.jump_settle, quick_fuchikoma_m8_boss_scripts.leap_prep, quick_fuchikoma_m8_boss_scripts.leap_prep_wait,
        quick_fuchikoma_m8_boss_scripts.leap_start, quick_fuchikoma_m8_boss_scripts.leap_land_wait, quick_fuchikoma_m8_boss_scripts.leap_settle_wait, quick_fuchikoma_m8_boss_scripts.leap_end, quick_fuchikoma_m8_boss_scripts.turn_start, quick_fuchikoma_m8_boss_scripts.turn_wait,
        quick_fuchikoma_m8_boss_scripts.turn_jump, quick_fuchikoma_m8_boss_scripts.enter_hover, quick_fuchikoma_m8_boss_scripts.enter_hover_wait, quick_fuchikoma_m8_boss_scripts.enter_ready_wait, quick_fuchikoma_m8_boss_scripts.enter_done,
    },
    /* D_80118814 */ {quick_fuchikoma_m8_boss_scripts.enter},
};

ScriptCallEntry quick_fuchikoma_m8_boss_calls[13] = {
    {NULL, 0},
    {script_read_mode, 0},
    {script_branch_eq, 0},
    {obj_script_read_jump, 0},
    {script_jump_if_player_close, 0},
    {script_jump_if_fixed_point_dist, 0},
    {script_op_jump_if_in_range, 0},
    {script_branch_threshold, 0},
    {script_jump_if_at_least, 0},
    {obj_script_read_speed, 0},
    {obj_script_read_s32, 0},
    {script_jump_if_in_range, 0},
    {script_jump_by_opcode, 0},
};

StateEntry quick_fuchikoma_m8_boss_states[14] = {
    {0, QUICK_FUCHIKOMA_M8_BOSS_ANIM_IDLE, 0},
    {0, QUICK_FUCHIKOMA_M8_BOSS_ANIM_JUMP_PREP, 0},
    {(u32)obj_jump_land_step, QUICK_FUCHIKOMA_M8_BOSS_ANIM_JUMP, 0},
    {(u32)obj_land_update, QUICK_FUCHIKOMA_M8_BOSS_ANIM_JUMP, 0},
    {0, QUICK_FUCHIKOMA_M8_BOSS_ANIM_LAND, 0},
    {(u32)quick_fuchikoma_face_target, QUICK_FUCHIKOMA_M8_BOSS_ANIM_IDLE, 0},
    {(u32)obj_accel_behaviour, QUICK_FUCHIKOMA_M8_BOSS_ANIM_SETTLE, 0},
    {(u32)obj_accel_step, QUICK_FUCHIKOMA_M8_BOSS_ANIM_SETTLE, 0},
    {(u32)quick_fuchikoma_m8_boss_dash, QUICK_FUCHIKOMA_M8_BOSS_ANIM_IDLE, 0},
    {(u32)obj_turn_stop_behaviour, QUICK_FUCHIKOMA_M8_BOSS_ANIM_SETTLE, 0},
    {(u32)obj_stop_behaviour, QUICK_FUCHIKOMA_M8_BOSS_ANIM_IDLE, 0},
    {(u32)obj_weave_update, QUICK_FUCHIKOMA_M8_BOSS_ANIM_SETTLE, 0},
    {(u32)obj_turn_hover_update, QUICK_FUCHIKOMA_M8_BOSS_ANIM_JUMP, 0},
    {0, QUICK_FUCHIKOMA_M8_BOSS_ANIM_SETTLE, 0},
};

FxRecordParams hit_burst_params = {1, 0x80, 0x40, 0x20, 0, 0x40, {0x200000, 0x40000, 0, 0xA000}};

RecTemplate hit_burst_templates[3] = {
    {1, 0xC8, 0x40, 0, 0, 0x40, 0, 0x80000, -0x3000, 0x4000},
    {1, 0x80, 0x80, 0x80, 0, 0x40, 0, 0x60000, -0x3000, 0x4000},
    {1, 0x40, 0x40, 0x40, 0, 0x40, 0, 0x40000, -0x1800, 0x2000},
};

#include "../stage/data/fade_red_fx_template.c"

#include "../stage/data/fx_owner_template_a.c"

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

s16 video_mode_id = 0;

#include "../stage/data/debug_cam_speed_table.c"

#include "../stage/data/pause_prev_work_area.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_8011D550[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/tint_scale_r.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_8011E6B4[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_8011ECD4 = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

u32 stage_image_pixels[114] = {
    0x51515151, 0x51515151, 0x51515151, 0x51515151, 0x50515151, 0x50505050,
    0x50505050, 0x50505050, 0x51515151, 0x51515151, 0x51515151, 0x51515151,
    0x50515151, 0x50505050, 0x50505050, 0x50505050, 0x51515151, 0x51515151,
    0x51515151, 0x51515151, 0x50515151, 0x50505050, 0x50505050, 0x50505050,
    0x51515151, 0x51515151, 0x51515151, 0x51515151, 0x50515151, 0x50505050,
    0x50505050, 0x50505050, 0x51515151, 0x51515151, 0x51515151, 0x51515151,
    0x50505151, 0x50505050, 0x50505050, 0x50505050, 0x51515151, 0x51515151,
    0x51515151, 0x51515151, 0x50505151, 0x50505050, 0x50505050, 0x50505050,
    0x51515151, 0x51515151, 0x51515151, 0x51515151, 0x50505151, 0x50505050,
    0x50505050, 0x50505050, 0x51515151, 0x51515151, 0x51515151, 0x51515151,
    0x50505051, 0x50505050, 0x50505050, 0x50505050, 0x51515151, 0x51515151,
    0x51515151, 0x51515151, 0x50505051, 0x50505050, 0x50505050, 0x50505050,
    0x51515151, 0x51515151, 0x51515151, 0x51515151, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x51515151, 0x51515151, 0x51515151, 0x51515151,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x51515151, 0x51515151,
    0x51515151, 0x50515151, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x51515151, 0x51515151, 0x51515151, 0x50505151, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x51515151, 0x51515151, 0x51515151, 0x50505051,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x51515151, 0x51515151,
};

s32 hurry_flag = 0x51515151;

s32 D_8011FEB0 = 0x50505050;

s32 cam_sway_flag = 0x50505050;

s32 enemies_left = 0x50505050;

u32 D_8011FEBC[11] = {
    0x50505050, 0x50505050, 0x51515151, 0x51515151, 0x50515151, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x51515151,
};

s32 hurry_msg_flag = 0x51515151;

u32 D_8011FEEC[126] = {
    0x50505051, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x51515151, 0x50515151, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x51515151, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
    0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050, 0x50505050,
};

#include "../stage/data/heap_top.c"

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

s32 night_vision_level = 0;

s32 night_vision_target = 0;

s32 night_vision_copy_flag = 0;

s32 night_vision_active = 0;

s32 rolling_door_base = 0;

s32 rolling_door_sound_handle = 0;

void *grid_entry_count = NULL;

s32 cam_path_index = 0;

s32 mission_area_entered = 0;

s16 shared_flags[3] = {
    0, 0, 0,
};

u16 D_8012015A = 0x0000;

s32 moving_object_slot = 0;

s32 quick_fuchikoma_health_display = 0;

s32 boss_defeated_flag = 0;

s32 quick_fuchikoma_seq_timer = 0;

s32 quick_fuchikoma_seq_state = 0;

s32 quick_fuchikoma_back_offset = 0;

s32 laser_spark_speed = 0;

s32 D_80120178 = 0;

s32 stage_sound_handle = 0;

#include "../stage/data/fade_red_obj.c"

#include "../stage/data/frame_work_area.c"

#include "../stage/data/model_slot_count.c"

u32 D_80120238 = 0x00000000;

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

u32 D_801202BC = 0x00000000;

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

s32 rocket_params = 0;

s32 D_80120750 = 0;

s32 D_80120754 = 0;

s16 D_80120758 = 0;

s16 D_8012075A = 0;

s16 D_8012075C = 0;

s16 D_8012075E = 0;

s16 D_80120760 = 0;

s16 D_80120762 = 0;

s16 D_80120764 = 0;

s16 D_80120766 = 0;

s16 D_80120768 = 0;

s16 D_8012076A = 0;

s16 D_8012076C = 0;

s16 D_8012076E = 0;

GridEntry *flagged_grid_cells[36] = {0};

/* labels inside the objects above */
__asm__(".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl D_8011ECDA\n.set D_8011ECDA, texture_image+0x2\n"
        ".globl pad1_pressed\n.set pad1_pressed, pad1+0x2\n"
        ".globl D_80120732\n.set D_80120732, scale_vec+0x2\n"
        ".globl smg_soldier_hit_script\n.set smg_soldier_hit_script, smg_soldier_anims+0x224\n"
        ".globl D_80117E94\n.set D_80117E94, axe_soldier_anims+0x280\n"
        ".globl axe_soldier_hit_pc\n.set axe_soldier_hit_pc, axe_soldier_anims+0x288\n"
        ".globl quick_fuchikoma_turn_pos_slot\n.set quick_fuchikoma_turn_pos_slot, quick_fuchikoma_anims+0x1B8\n"
        ".globl quick_fuchikoma_turn_neg_slot\n.set quick_fuchikoma_turn_neg_slot, quick_fuchikoma_anims+0x1C0\n"
        ".globl quick_fuchikoma_death_pc\n.set quick_fuchikoma_death_pc, quick_fuchikoma_anims+0x1E4\n"
        ".globl sincos_deg90\n.set sincos_deg90, rcossin_tbl+0x1000\n"
        ".globl view_sincos\n.set view_sincos, rcossin_tbl+0x2000\n"
        ".globl sincos_deg270\n.set sincos_deg270, rcossin_tbl+0x3000\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n"
        ".globl D_801203EA\n.set D_801203EA, view_nudge+0x2\n"
        ".globl d_801201AE\n.set d_801201AE, flow+0x2\n"
        ".globl flow_angle\n.set flow_angle, flow+0x4\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl laser_drone_script\n.set laser_drone_script, laser_drone_anims+0x0\n"
        ".globl laser_drone_data\n.set laser_drone_data, laser_drone_anims+0x8\n"
        ".globl rocket_drone_restart\n.set rocket_drone_restart, rocket_drone_scripts+0x0\n"
        ".globl rocket_drone_select\n.set rocket_drone_select, rocket_drone_scripts+0x4\n"
        ".globl rocket_drone_patrol\n.set rocket_drone_patrol, rocket_drone_scripts+0x14\n"
        ".globl rocket_drone_spotted\n.set rocket_drone_spotted, rocket_drone_scripts+0x24\n"
        ".globl rocket_drone_idle_start\n.set rocket_drone_idle_start, rocket_drone_scripts+0x34\n"
        ".globl rocket_drone_idle\n.set rocket_drone_idle, rocket_drone_scripts+0x3C\n"
        ".globl rocket_drone_cooldown\n.set rocket_drone_cooldown, rocket_drone_scripts+0x50\n"
        ".globl rocket_drone_anim\n.set rocket_drone_anim, rocket_drone_scripts+0x58\n"
        ".globl d_80116CC0\n.set d_80116CC0, rocket_drone_scripts+0x74\n"
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
        ".globl stationary_rocket_launcher_2_anim_idle\n.set stationary_rocket_launcher_2_anim_idle, stationary_rocket_launcher_2_anims+0x0\n"
        ".globl stationary_rocket_launcher_2_anim_aim\n.set stationary_rocket_launcher_2_anim_aim, stationary_rocket_launcher_2_anims+0x8\n"
        ".globl stationary_rocket_launcher_2_anim_aimed\n.set stationary_rocket_launcher_2_anim_aimed, stationary_rocket_launcher_2_anims+0x20\n"
        ".globl stationary_rocket_launcher_2_anim_fire\n.set stationary_rocket_launcher_2_anim_fire, stationary_rocket_launcher_2_anims+0x28\n"
        ".globl stationary_rocket_launcher_2_anim_fired\n.set stationary_rocket_launcher_2_anim_fired, stationary_rocket_launcher_2_anims+0x34\n"
        ".globl stationary_rocket_launcher_2_anim_disengage\n.set stationary_rocket_launcher_2_anim_disengage, stationary_rocket_launcher_2_anims+0x3C\n"
        ".globl stationary_rocket_launcher_2_anim_stowed\n.set stationary_rocket_launcher_2_anim_stowed, stationary_rocket_launcher_2_anims+0x50\n"
        ".globl stationary_rocket_launcher_2_anim_cooldown\n.set stationary_rocket_launcher_2_anim_cooldown, stationary_rocket_launcher_2_anims+0x58\n"
        ".globl stationary_rocket_launcher_2_data\n.set stationary_rocket_launcher_2_data, stationary_rocket_launcher_2_anims+0x60\n"
        ".globl stationary_rocket_launcher_2_idle\n.set stationary_rocket_launcher_2_idle, stationary_rocket_launcher_2_jumps_streams+0x0\n"
        ".globl stationary_rocket_launcher_2_aim\n.set stationary_rocket_launcher_2_aim, stationary_rocket_launcher_2_jumps_streams+0x10\n"
        ".globl script_count_down\n.set script_count_down, stationary_rocket_launcher_2_jumps_streams+0x18\n"
        ".globl stationary_rocket_launcher_2_fire_start\n.set stationary_rocket_launcher_2_fire_start, stationary_rocket_launcher_2_jumps_streams+0x20\n"
        ".globl stationary_rocket_launcher_2_fire_loop\n.set stationary_rocket_launcher_2_fire_loop, stationary_rocket_launcher_2_jumps_streams+0x24\n"
        ".globl stationary_rocket_launcher_2_cooldown\n.set stationary_rocket_launcher_2_cooldown, stationary_rocket_launcher_2_jumps_streams+0x34\n"
        ".globl stationary_rocket_launcher_2_cooling\n.set stationary_rocket_launcher_2_cooling, stationary_rocket_launcher_2_jumps_streams+0x38\n"
        ".globl stationary_rocket_launcher_2_refire\n.set stationary_rocket_launcher_2_refire, stationary_rocket_launcher_2_jumps_streams+0x40\n"
        ".globl stationary_rocket_launcher_2_disengage\n.set stationary_rocket_launcher_2_disengage, stationary_rocket_launcher_2_jumps_streams+0x48\n"
        ".globl stationary_rocket_launcher_2_disengaging\n.set stationary_rocket_launcher_2_disengaging, stationary_rocket_launcher_2_jumps_streams+0x50\n"
        ".globl stationary_rocket_launcher_2_jumps\n.set stationary_rocket_launcher_2_jumps, stationary_rocket_launcher_2_jumps_streams+0x5C\n"
        ".globl D_80117B08\n.set D_80117B08, stationary_rocket_launcher_2_jumps_streams+0x84\n"
        ".globl axe_soldier_anim_idle\n.set axe_soldier_anim_idle, axe_soldier_anims+0x0\n"
        ".globl axe_soldier_anim_walk\n.set axe_soldier_anim_walk, axe_soldier_anims+0xC\n"
        ".globl axe_soldier_anim_windup\n.set axe_soldier_anim_windup, axe_soldier_anims+0x34\n"
        ".globl axe_soldier_anim_swing\n.set axe_soldier_anim_swing, axe_soldier_anims+0x3C\n"
        ".globl axe_soldier_anim_windup_alt\n.set axe_soldier_anim_windup_alt, axe_soldier_anims+0x9C\n"
        ".globl axe_soldier_anim_swing_alt\n.set axe_soldier_anim_swing_alt, axe_soldier_anims+0xA4\n"
        ".globl axe_soldier_anim_attack\n.set axe_soldier_anim_attack, axe_soldier_anims+0x104\n"
        ".globl axe_soldier_anim_lunge\n.set axe_soldier_anim_lunge, axe_soldier_anims+0x174\n"
        ".globl axe_soldier_anim_death\n.set axe_soldier_anim_death, axe_soldier_anims+0x20C\n"
        ".globl axe_soldier_data\n.set axe_soldier_data, axe_soldier_anims+0x268\n"
        ".globl axe_soldier_idle\n.set axe_soldier_idle, axe_soldier_scripts+0x0\n"
        ".globl axe_soldier_pause\n.set axe_soldier_pause, axe_soldier_scripts+0xC\n"
        ".globl axe_soldier_pause_repeat\n.set axe_soldier_pause_repeat, axe_soldier_scripts+0x14\n"
        ".globl axe_soldier_walk\n.set axe_soldier_walk, axe_soldier_scripts+0x28\n"
        ".globl axe_soldier_wander_stop\n.set axe_soldier_wander_stop, axe_soldier_scripts+0x34\n"
        ".globl axe_soldier_hold\n.set axe_soldier_hold, axe_soldier_scripts+0x4C\n"
        ".globl axe_soldier_pause_alt_start\n.set axe_soldier_pause_alt_start, axe_soldier_scripts+0x58\n"
        ".globl axe_soldier_pause_alt\n.set axe_soldier_pause_alt, axe_soldier_scripts+0x60\n"
        ".globl axe_soldier_pause_alt_loop\n.set axe_soldier_pause_alt_loop, axe_soldier_scripts+0x68\n"
        ".globl axe_soldier_patrol\n.set axe_soldier_patrol, axe_soldier_scripts+0x7C\n"
        ".globl axe_soldier_patrol_walk\n.set axe_soldier_patrol_walk, axe_soldier_scripts+0x84\n"
        ".globl axe_soldier_patrol_loop\n.set axe_soldier_patrol_loop, axe_soldier_scripts+0x8C\n"
        ".globl axe_soldier_patrol_wait\n.set axe_soldier_patrol_wait, axe_soldier_scripts+0xA4\n"
        ".globl axe_soldier_patrol_wait_loop\n.set axe_soldier_patrol_wait_loop, axe_soldier_scripts+0xAC\n"
        ".globl axe_soldier_jumps\n.set axe_soldier_jumps, axe_soldier_scripts+0xC4\n"
        ".globl D_80117F9C\n.set D_80117F9C, axe_soldier_scripts+0xFC\n"
        ".globl quick_fuchikoma_m8_boss_anim_idle\n.set quick_fuchikoma_m8_boss_anim_idle, quick_fuchikoma_anims+0x0\n"
        ".globl quick_fuchikoma_m8_boss_anim_turn_right_start\n.set quick_fuchikoma_m8_boss_anim_turn_right_start, quick_fuchikoma_anims+0x8\n"
        ".globl quick_fuchikoma_m8_boss_anim_turn_right_loop\n.set quick_fuchikoma_m8_boss_anim_turn_right_loop, quick_fuchikoma_anims+0x18\n"
        ".globl quick_fuchikoma_m8_boss_anim_turn_left_start\n.set quick_fuchikoma_m8_boss_anim_turn_left_start, quick_fuchikoma_anims+0x20\n"
        ".globl quick_fuchikoma_m8_boss_anim_turn_left_loop\n.set quick_fuchikoma_m8_boss_anim_turn_left_loop, quick_fuchikoma_anims+0x30\n"
        ".globl quick_fuchikoma_m8_boss_anim_settle\n.set quick_fuchikoma_m8_boss_anim_settle, quick_fuchikoma_anims+0x38\n"
        ".globl quick_fuchikoma_m8_boss_anim_walk_loop\n.set quick_fuchikoma_m8_boss_anim_walk_loop, quick_fuchikoma_anims+0x54\n"
        ".globl quick_fuchikoma_m8_boss_anim_jump_prep\n.set quick_fuchikoma_m8_boss_anim_jump_prep, quick_fuchikoma_anims+0xD8\n"
        ".globl quick_fuchikoma_m8_boss_anim_jump\n.set quick_fuchikoma_m8_boss_anim_jump, quick_fuchikoma_anims+0x13C\n"
        ".globl quick_fuchikoma_m8_boss_anim_jump_hold\n.set quick_fuchikoma_m8_boss_anim_jump_hold, quick_fuchikoma_anims+0x144\n"
        ".globl quick_fuchikoma_m8_boss_anim_land\n.set quick_fuchikoma_m8_boss_anim_land, quick_fuchikoma_anims+0x14C\n"
        ".globl quick_fuchikoma_m8_boss_anim_land_hold\n.set quick_fuchikoma_m8_boss_anim_land_hold, quick_fuchikoma_anims+0x168\n"
        ".globl quick_fuchikoma_death_script\n.set quick_fuchikoma_death_script, quick_fuchikoma_anims+0x170\n"
        ".globl quick_fuchikoma_m8_boss_anim_death_hold\n.set quick_fuchikoma_m8_boss_anim_death_hold, quick_fuchikoma_anims+0x1AC\n"
        ".globl quick_fuchikoma_m8_boss_data\n.set quick_fuchikoma_m8_boss_data, quick_fuchikoma_anims+0x1B4\n"
        ".globl quick_fuchikoma_m8_boss_enter\n.set quick_fuchikoma_m8_boss_enter, quick_fuchikoma_m8_boss_scripts+0x0\n"
        ".globl quick_fuchikoma_m8_boss_idle\n.set quick_fuchikoma_m8_boss_idle, quick_fuchikoma_m8_boss_scripts+0x4\n"
        ".globl quick_fuchikoma_m8_boss_accel_start\n.set quick_fuchikoma_m8_boss_accel_start, quick_fuchikoma_m8_boss_scripts+0x10\n"
        ".globl quick_fuchikoma_m8_boss_patrol\n.set quick_fuchikoma_m8_boss_patrol, quick_fuchikoma_m8_boss_scripts+0x1C\n"
        ".globl quick_fuchikoma_m8_boss_dash_start\n.set quick_fuchikoma_m8_boss_dash_start, quick_fuchikoma_m8_boss_scripts+0x38\n"
        ".globl quick_fuchikoma_m8_boss_close_poll\n.set quick_fuchikoma_m8_boss_close_poll, quick_fuchikoma_m8_boss_scripts+0x3C\n"
        ".globl quick_fuchikoma_m8_boss_wait_idle\n.set quick_fuchikoma_m8_boss_wait_idle, quick_fuchikoma_m8_boss_scripts+0x4C\n"
        ".globl quick_fuchikoma_m8_boss_coast_start\n.set quick_fuchikoma_m8_boss_coast_start, quick_fuchikoma_m8_boss_scripts+0x5C\n"
        ".globl quick_fuchikoma_m8_boss_coast_loop\n.set quick_fuchikoma_m8_boss_coast_loop, quick_fuchikoma_m8_boss_scripts+0x64\n"
        ".globl quick_fuchikoma_m8_boss_close_check\n.set quick_fuchikoma_m8_boss_close_check, quick_fuchikoma_m8_boss_scripts+0x78\n"
        ".globl quick_fuchikoma_m8_boss_far_step\n.set quick_fuchikoma_m8_boss_far_step, quick_fuchikoma_m8_boss_scripts+0x84\n"
        ".globl quick_fuchikoma_m8_boss_far_wait\n.set quick_fuchikoma_m8_boss_far_wait, quick_fuchikoma_m8_boss_scripts+0x88\n"
        ".globl quick_fuchikoma_m8_boss_close_action\n.set quick_fuchikoma_m8_boss_close_action, quick_fuchikoma_m8_boss_scripts+0x98\n"
        ".globl quick_fuchikoma_m8_boss_close_wait\n.set quick_fuchikoma_m8_boss_close_wait, quick_fuchikoma_m8_boss_scripts+0x9C\n"
        ".globl quick_fuchikoma_m8_boss_decide\n.set quick_fuchikoma_m8_boss_decide, quick_fuchikoma_m8_boss_scripts+0xAC\n"
        ".globl quick_fuchikoma_m8_boss_turn_check\n.set quick_fuchikoma_m8_boss_turn_check, quick_fuchikoma_m8_boss_scripts+0xBC\n"
        ".globl quick_fuchikoma_m8_boss_cruise_wait\n.set quick_fuchikoma_m8_boss_cruise_wait, quick_fuchikoma_m8_boss_scripts+0xC4\n"
        ".globl quick_fuchikoma_m8_boss_cruise_start\n.set quick_fuchikoma_m8_boss_cruise_start, quick_fuchikoma_m8_boss_scripts+0xD0\n"
        ".globl quick_fuchikoma_m8_boss_cruise_loop\n.set quick_fuchikoma_m8_boss_cruise_loop, quick_fuchikoma_m8_boss_scripts+0xE0\n"
        ".globl quick_fuchikoma_m8_boss_cruise_end\n.set quick_fuchikoma_m8_boss_cruise_end, quick_fuchikoma_m8_boss_scripts+0xF0\n"
        ".globl quick_fuchikoma_m8_boss_halt\n.set quick_fuchikoma_m8_boss_halt, quick_fuchikoma_m8_boss_scripts+0x100\n"
        ".globl quick_fuchikoma_m8_boss_turn_stop_start\n.set quick_fuchikoma_m8_boss_turn_stop_start, quick_fuchikoma_m8_boss_scripts+0x110\n"
        ".globl quick_fuchikoma_m8_boss_turn_stop_wait\n.set quick_fuchikoma_m8_boss_turn_stop_wait, quick_fuchikoma_m8_boss_scripts+0x114\n"
        ".globl quick_fuchikoma_m8_boss_stop_wait\n.set quick_fuchikoma_m8_boss_stop_wait, quick_fuchikoma_m8_boss_scripts+0x128\n"
        ".globl quick_fuchikoma_m8_boss_stop_start\n.set quick_fuchikoma_m8_boss_stop_start, quick_fuchikoma_m8_boss_scripts+0x134\n"
        ".globl quick_fuchikoma_m8_boss_turn_stop_align\n.set quick_fuchikoma_m8_boss_turn_stop_align, quick_fuchikoma_m8_boss_scripts+0x138\n"
        ".globl quick_fuchikoma_m8_boss_cruise_resume\n.set quick_fuchikoma_m8_boss_cruise_resume, quick_fuchikoma_m8_boss_scripts+0x14C\n"
        ".globl quick_fuchikoma_m8_boss_weave_start\n.set quick_fuchikoma_m8_boss_weave_start, quick_fuchikoma_m8_boss_scripts+0x158\n"
        ".globl quick_fuchikoma_m8_boss_weave_loop\n.set quick_fuchikoma_m8_boss_weave_loop, quick_fuchikoma_m8_boss_scripts+0x15C\n"
        ".globl quick_fuchikoma_m8_boss_weave_check\n.set quick_fuchikoma_m8_boss_weave_check, quick_fuchikoma_m8_boss_scripts+0x168\n"
        ".globl quick_fuchikoma_m8_boss_weave_in_view\n.set quick_fuchikoma_m8_boss_weave_in_view, quick_fuchikoma_m8_boss_scripts+0x170\n"
        ".globl quick_fuchikoma_m8_boss_weave_in_view_wait\n.set quick_fuchikoma_m8_boss_weave_in_view_wait, quick_fuchikoma_m8_boss_scripts+0x174\n"
        ".globl quick_fuchikoma_m8_boss_weave_out_view\n.set quick_fuchikoma_m8_boss_weave_out_view, quick_fuchikoma_m8_boss_scripts+0x184\n"
        ".globl quick_fuchikoma_m8_boss_weave_out_view_wait\n.set quick_fuchikoma_m8_boss_weave_out_view_wait, quick_fuchikoma_m8_boss_scripts+0x188\n"
        ".globl quick_fuchikoma_m8_boss_jump_prep\n.set quick_fuchikoma_m8_boss_jump_prep, quick_fuchikoma_m8_boss_scripts+0x198\n"
        ".globl quick_fuchikoma_m8_boss_jump_prep_wait\n.set quick_fuchikoma_m8_boss_jump_prep_wait, quick_fuchikoma_m8_boss_scripts+0x19C\n"
        ".globl quick_fuchikoma_m8_boss_jump_start\n.set quick_fuchikoma_m8_boss_jump_start, quick_fuchikoma_m8_boss_scripts+0x1A8\n"
        ".globl quick_fuchikoma_m8_boss_jump_land_wait\n.set quick_fuchikoma_m8_boss_jump_land_wait, quick_fuchikoma_m8_boss_scripts+0x1AC\n"
        ".globl quick_fuchikoma_m8_boss_jump_settle_wait\n.set quick_fuchikoma_m8_boss_jump_settle_wait, quick_fuchikoma_m8_boss_scripts+0x1BC\n"
        ".globl quick_fuchikoma_m8_boss_jump_settle\n.set quick_fuchikoma_m8_boss_jump_settle, quick_fuchikoma_m8_boss_scripts+0x1C8\n"
        ".globl quick_fuchikoma_m8_boss_leap_prep\n.set quick_fuchikoma_m8_boss_leap_prep, quick_fuchikoma_m8_boss_scripts+0x1D0\n"
        ".globl quick_fuchikoma_m8_boss_leap_prep_wait\n.set quick_fuchikoma_m8_boss_leap_prep_wait, quick_fuchikoma_m8_boss_scripts+0x1D4\n"
        ".globl quick_fuchikoma_m8_boss_leap_start\n.set quick_fuchikoma_m8_boss_leap_start, quick_fuchikoma_m8_boss_scripts+0x1E0\n"
        ".globl quick_fuchikoma_m8_boss_leap_land_wait\n.set quick_fuchikoma_m8_boss_leap_land_wait, quick_fuchikoma_m8_boss_scripts+0x1E4\n"
        ".globl quick_fuchikoma_m8_boss_leap_settle_wait\n.set quick_fuchikoma_m8_boss_leap_settle_wait, quick_fuchikoma_m8_boss_scripts+0x1F4\n"
        ".globl quick_fuchikoma_m8_boss_leap_end\n.set quick_fuchikoma_m8_boss_leap_end, quick_fuchikoma_m8_boss_scripts+0x200\n"
        ".globl quick_fuchikoma_m8_boss_turn_start\n.set quick_fuchikoma_m8_boss_turn_start, quick_fuchikoma_m8_boss_scripts+0x210\n"
        ".globl quick_fuchikoma_m8_boss_turn_wait\n.set quick_fuchikoma_m8_boss_turn_wait, quick_fuchikoma_m8_boss_scripts+0x214\n"
        ".globl quick_fuchikoma_m8_boss_turn_jump\n.set quick_fuchikoma_m8_boss_turn_jump, quick_fuchikoma_m8_boss_scripts+0x224\n"
        ".globl quick_fuchikoma_m8_boss_enter_hover\n.set quick_fuchikoma_m8_boss_enter_hover, quick_fuchikoma_m8_boss_scripts+0x228\n"
        ".globl quick_fuchikoma_m8_boss_enter_hover_wait\n.set quick_fuchikoma_m8_boss_enter_hover_wait, quick_fuchikoma_m8_boss_scripts+0x22C\n"
        ".globl quick_fuchikoma_m8_boss_enter_ready_wait\n.set quick_fuchikoma_m8_boss_enter_ready_wait, quick_fuchikoma_m8_boss_scripts+0x23C\n"
        ".globl quick_fuchikoma_m8_boss_enter_done\n.set quick_fuchikoma_m8_boss_enter_done, quick_fuchikoma_m8_boss_scripts+0x248\n"
        ".globl quick_fuchikoma_jump_table\n.set quick_fuchikoma_jump_table, quick_fuchikoma_m8_boss_scripts+0x250\n"
        ".globl D_80118814\n.set D_80118814, quick_fuchikoma_m8_boss_scripts+0x324\n");
