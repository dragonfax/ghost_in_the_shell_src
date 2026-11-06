/* s13 data 0x8010F584-0x80118000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s13_types.h"
#include "script.h"
#include "scripts.h"
#include "sounds.h"

extern void anim_wait_step();
extern void blink_link_update();
extern void blink_timer_update();
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
extern void enemy_alert();
extern void enemy_spawn_placed();
extern u8 file_msgs_spr_clt[];
extern u8 file_msgs_spr_grc[];
extern u8 file_msgs_spr_so3[];
extern void fly_random_turn_step();
extern void fly_side_270_step();
extern void fly_side_270_turn_minus32_step();
extern void fly_side_270_turn_plus16_step();
extern void fly_side_90_step();
extern void fly_side_90_turn_minus16_step();
extern void fly_side_90_turn_plus32_step();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void func_800BA6D8();
extern void guard_blink_update();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void obj_area_update();
extern void obj_call_hook();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_release_check();
extern void obj_spawn_from_place();
extern void obj_spin_update();
extern void obj_state_clear_if_match();
extern void obj_state_set_if_match();
extern void obj_turn_minus16_step();
extern void obj_turn_plus16_step();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placement_spawn();
extern void ramp_start_script();
extern void reverse_step();
extern void stage_init();
extern void stage_load_params();
extern u8 str_bosd_ch0_clt[];
extern u8 str_bosd_ch0_vx1[];
extern u8 str_bosd_ch0cb4[];
extern u8 str_bosd_ch1_vx1[];
extern u8 str_bosd_tp0_clt[];
extern u8 str_bosd_tp0_xs3[];
extern u8 str_bosd_tp1_clt[];
extern u8 str_bosd_tp1_xs3[];
extern u8 str_com_dat_fac[];
extern u8 str_ctlt_objcb4[];
extern u8 str_ctlt_spr_clt[];
extern u8 str_ctlt_spr_grc[];
extern u8 str_ctlt_spr_so3[];
extern u8 str_enemy_arg_data[];
extern u8 str_enemy_bosd_data[];
extern u8 str_enemy_ctlt_data[];
extern u8 str_enemy_door_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_fc_obj_vx1[];
extern u8 str_fc_objcb4[];
extern u8 str_fc_tp0_clt[];
extern u8 str_fc_tp0_xs3[];
extern u8 str_main_data[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_s13_boss[];
extern u8 str_s13_dat_fac[];
extern u8 str_s13_ene_fac[];
extern u8 str_s13_miss[];
extern u8 str_s13_stage[];
extern u8 str_sdw_obj_vx1[];
extern u8 str_sdw_tp0_clt[];
extern u8 str_sdw_tp0_xs3[];
extern u8 str_targ_ch0_clt[];
extern u8 str_targ_ch0_vx1[];
extern u8 str_targ_tp0_clt[];
extern u8 str_targ_tp0_xs3[];
extern u8 str_targcb0cb4[];
extern u8 str_tg_disp_clt[];
extern u8 str_tg_disp_grc[];
extern u8 str_tg_disp_so3[];
extern u8 str_tre_apdea3[];
extern u8 str_tre_cnf_bcf[];
extern u8 str_tre_joy_bin[];
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
extern u8 D_8010F874[];
extern u8 D_80116532[];
extern u8 D_80117C12[];
extern u8 D_80117F5A[];
extern u8 blink_jump_script[];
extern u8 cos_table[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 d_801201AE[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 enemy_death_slot[];
extern u8 flow_angle[];
extern u8 fly_turn_neg_script[];
extern u8 fly_turn_pos_script[];
extern u8 gun_hit_effect_table[];
extern u8 mission_bonus_table[];
extern u8 pad1_pressed[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 spark_burst_frames[];
extern u8 view_sincos[];
extern s32 area;
extern ScanItem D_8010F588[];
extern AreaEntry D_8010F5B8[];
extern u32 D_8010F608[];
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *enemy_msgs_files[];
extern ScanEntry enemy_msgs_entry;
extern s32 place_asset[];
extern ModelBlockRef target_clt_list[];
extern ModelBlockRef target_xs3_list[];
extern ModelBlockRef target_vx1_list[];
extern ModelBlockRange D_8010F7DC[];
extern ModelBlock target_model_block;
extern u8 *D_8010F820[];
extern ScanEntry D_8010F828;
extern s16 enemy_init_handlers_anim_idle[];
extern s16 enemy_init_handlers_anim_alt_idle[];
extern s16 enemy_init_handlers_anim_alt_to_idle[];
extern s16 enemy_init_handlers_anim_idle_to_alt[];
extern s16 *enemy_script_table[];
extern s16 obj_type_data_idle[];
extern s16 *obj_type_data[];
extern s16 *obj_data_entry_table[];
extern StateEntry D_8010F890[];
extern s32 D_8010F900[];
extern ModelBlockRef bosd_clt_list[];
extern ModelBlockRef bosd_xs3_list[];
extern ModelBlockRef bosd_vx1_list[];
extern ModelBlockRange D_8010F95C[];
extern ModelBlockRange D_8010F97C[];
extern ModelBlock enemy_bosd_model;
extern u8 *D_8010F9B8[];
extern ScanEntry D_8010F9C0;
extern s16 enemy_anim_fly[];
extern s16 enemy_anim_hover_start[];
extern s16 enemy_anim_hover_settle[];
extern s16 enemy_anim_hover_cycle[];
extern s16 enemy_anim_hover_cycle_end[];
extern s16 enemy_anim_turn_right_start[];
extern s16 enemy_anim_turn_right_loop[];
extern s16 enemy_anim_turn_left_start[];
extern s16 enemy_anim_turn_left_loop[];
extern s16 enemy_anim_hold_c_start[];
extern s16 enemy_anim_hold_c_loop[];
extern s16 enemy_anim_hold_d_start[];
extern s16 enemy_anim_hold_d_loop[];
extern s16 enemy_anim_signal_done[];
extern s16 enemy_anim_fly_resume[];
extern s16 enemy_anim_reverse_stop[];
extern s16 *fly_script_base[16];
extern s16 enemy_idle[];
extern s16 enemy_spotted[];
extern s16 enemy_spotted_repeat[];
extern s16 enemy_blink_start[];
extern s16 enemy_blink_cooldown[];
extern s16 enemy_blink_cooling[];
extern s16 enemy_return_idle[];
extern s16 enemy_strafe_pick[];
extern s16 enemy_turn_pick[];
extern s16 enemy_chase_pick[];
extern s16 enemy_strafe_b_start[];
extern s16 enemy_strafe_b_run[];
extern s16 enemy_strafe_a_start[];
extern s16 enemy_strafe_a_run[];
extern s16 enemy_turn_pos_start[];
extern s16 enemy_turn_pos_run[];
extern s16 enemy_turn_neg_start[];
extern s16 enemy_turn_neg_run[];
extern s16 enemy_strafe_b_turn_pos_start[];
extern s16 enemy_strafe_b_turn_pos_run[];
extern s16 enemy_strafe_a_turn_neg_start[];
extern s16 enemy_strafe_a_turn_neg_run[];
extern s16 *enemy_op_table[];
extern s16 *D_8010FCC8;
extern StateEntry D_8010FCCC[];
extern s32 spark_burst_offsets[5][4];
extern RecTemplate fade_red_fx_template;
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern u32 D_8010FE0C[];
extern RecTemplate fx_template_colour_fade;
extern RecTemplate fx_template_spot_effect;
extern RecTemplate fx_template_spot;
extern RecTemplate fx_template_fade_rgb;
extern s32 D_8010FEBC[];
extern s32 zone_spark_base;
extern s32 zone_blend_base;
extern ScanEntry enemy_door_scan_entry;
extern u8 *enemy_ctlt_stage_files[];
extern u8 *enemy_ctlt_ptr_table_ids[];
extern s32 D_8010FEFC;
extern s32 D_8010FF00;
extern s32 mission_text_base;
extern ScanEntry enemy_ctlt_scan_entry;
extern AngleBlendEntry D_8010FF20[];
extern u32 req_entry_table;
extern u32 D_8010FFFC;
extern u32 D_80110000[];
extern u32 D_80110108;
extern u32 D_8011010C;
extern u32 D_80110110;
extern u32 D_80110114[];
extern u32 D_8011011C[];
extern u32 D_80110124;
extern u32 D_80110128;
extern u8 *stage_draw_lists[];
extern u8 *stage_load_lists[];
extern s32 mission_bonus_msg_ids[];
extern s32 slot_range_min_table[];
extern s32 slot_range_max_table[];
extern ClampRange slot_enemy_limits[5];
extern u32 D_801101A8;
extern s32 cam_zone_table[3][6];
extern u32 stage_data_buf[5];
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_80114D88[];
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
extern u32 D_80115F0C[];
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
extern u32 D_8011652C;
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
extern u32 D_80117988;
extern Next800C5620 *fade_red_obj;
extern AngleBlendEntry *zone_table;
extern s32 stage_list_index;
extern s32 slot_enemy_total;
extern s32 slot_kills;
extern s32 slot_kill_base;
extern s32 stage_enemies_left;
extern s32 draw_list_index;
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
extern u32 D_80117A60;
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
extern u32 D_80117AE4;
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
extern GridEntry *flagged_grid_cells[];

s32 area = 0x25;

ScanItem D_8010F588[6] = {
    {&enemy_msgs_entry, str_enemy_msgs_data},
    {&enemy_door_scan_entry, str_enemy_door_data},
    {&enemy_ctlt_scan_entry, str_enemy_ctlt_data},
    {&D_8010F9C0, str_enemy_bosd_data},
    {&D_8010F828, str_enemy_arg_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry D_8010F5B8[2] = {
    {str_s13_stage, str_tre_cnf_bcf, str_tre_apdea3, str_tre_joy_bin, str_s13_dat_fac, str_s13_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, D_8010F588},
    {str_s13_miss, NULL, NULL, NULL, NULL, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL},
};

u32 D_8010F608[12] = {
    0xFFFFFFFF, 0x00000000, (u32)str_s13_boss, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x10001000, 0x00001000, 0x00000000, (u32)D_8010F608,
};

AreaEntry *area_entry_table[3] = {
    NULL, D_8010F5B8, NULL,
};

#include "../stage/data/debug_name_buf.c"

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

#include "../stage/data/enemy_msgs_files.c"

#include "../stage/data/enemy_msgs_entry.c"

#include "../stage/data/place_asset.c"

ModelBlockRef target_clt_list[3] = {
    {(s32)str_targ_ch0_clt, 0, 0},
    {(s32)str_targ_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef target_xs3_list[2] = {
    {(s32)str_targ_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef target_vx1_list[2] = {
    {(s32)str_targ_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_8010F7DC[4] = {
    {0x50, 0x51, 0xCCC, 0}, {0x60, 0x61, 0xCCC, 0}, {0x70, 0x71, 0xCCC, 0}, {-1, 0, 0, 0},
};

ModelBlock target_model_block = {(s32)target_clt_list, (s32)target_vx1_list, (s32)target_xs3_list, 0, 0, 0, (s32)D_8010F7DC, 0, 0};

u8 *D_8010F820[2] = {
    str_targcb0cb4, NULL,
};

ScanEntry D_8010F828 = {{0, (s32)obj_spawn_from_place}, place_asset, (s32)&target_model_block, (s32)D_8010F820, 0};

struct EnemyInitHandlersAnims {
    s16 idle[6];
    s16 alt_idle[6];
    s16 alt_to_idle[6];
    s16 idle_to_alt[6];
    s16 *table[4];
} enemy_init_handlers_anims = {
    /* idle */ {
        FLY(0),
        STEP(10, 32),
        GOTO(ENEMY_INIT_HANDLERS_ANIM_IDLE),
    },
    /* alt_idle */ {
        FLY(0),
        STEP(10, 33),
        GOTO(ENEMY_INIT_HANDLERS_ANIM_ALT_IDLE),
    },
    /* alt_to_idle */ {
        STEP(4, 33),
        STEP(12, 32),
        GOTO(ENEMY_INIT_HANDLERS_ANIM_IDLE),
    },
    /* idle_to_alt */ {
        STEP(4, 32),
        STEP(12, 33),
        GOTO(ENEMY_INIT_HANDLERS_ANIM_ALT_IDLE),
    },
    /* table */ {
        enemy_init_handlers_anims.idle, enemy_init_handlers_anims.alt_idle, enemy_init_handlers_anims.alt_to_idle, enemy_init_handlers_anims.idle_to_alt,
    },
};

struct ObjTypeDataScripts {
    s16 idle[4];
    s16 *table[1];
    s16 *obj_data_entry_table[1];
} obj_type_data_scripts = {
    /* idle */ {
        WAIT(1),
        JUMP(OBJ_TYPE_DATA_IDLE),
    },
    /* table */ {
        obj_type_data_scripts.idle,
    },
    /* obj_data_entry_table */ {
        obj_type_data_scripts.idle,
    },
};

StateEntry D_8010F890[14] = {
    {(u32)enemy_alert, 0, 0},
    {(u32)guard_blink_update, 1, 0},
    {(u32)obj_state_clear_if_match, 2, 0},
    {(u32)obj_state_set_if_match, 3, 1},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0xFFFFFFF4, 1, 0},
    {0, 0, 0},
    {0xFFFFFFC4, 2, 0},
    {0, 0, 0},
    {0xFFFFFFA0, 3, 0},
    {0, 0, 0},
    {0xFFFFFFE8, 4, 0},
};

s32 D_8010F900[3] = {
    -1, -1, -1,
};

ModelBlockRef bosd_clt_list[4] = {
    {(s32)str_bosd_ch0_clt, 0, 0},
    {(s32)str_bosd_tp0_clt, 0, 0},
    {(s32)str_bosd_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef bosd_xs3_list[3] = {
    {(s32)str_bosd_tp0_xs3, 1, 0},
    {(s32)str_bosd_tp1_xs3, 2, 0},
    {0, 0, 0},
};

ModelBlockRef bosd_vx1_list[3] = {
    {(s32)str_bosd_ch0_vx1, 1, 0},
    {(s32)str_bosd_ch1_vx1, 2, 0},
    {0, 0, 0},
};

ModelBlockRange D_8010F95C[4] = {
    {0, 0x7F, 0x1333, 0}, {0x88, 0x88, 0x1333, 0}, {0x8A, 0x8A, 0xCCC, 0}, {-1, 0, 0, 0},
};

ModelBlockRange D_8010F97C[3] = {
    {0x81, 0x81, 0x2000, 0}, {0x83, 0x85, 0x2000, 0}, {0x88, 0x88, 0x2000, 0},
};

ModelBlock enemy_bosd_model = {(s32)bosd_clt_list, (s32)bosd_vx1_list, (s32)bosd_xs3_list, 0, (s32)D_8010F97C, 0, (s32)D_8010F95C, 0, 0};

u8 *D_8010F9B8[2] = {
    str_bosd_ch0cb4, NULL,
};

ScanEntry D_8010F9C0 = {{(s32)func_800BA6D8, (s32)enemy_spawn_placed}, D_8010F900, (s32)&enemy_bosd_model, (s32)D_8010F9B8, 0};

struct EnemyAnims {
    s16 fly[12];
    s16 hover_start[8];
    s16 hover_settle[6];
    s16 hover_cycle[12];
    s16 hover_cycle_end[20];
    s16 turn_right_start[6];
    s16 turn_right_loop[4];
    s16 turn_left_start[6];
    s16 turn_left_loop[4];
    s16 hold_c_start[6];
    s16 hold_c_loop[4];
    s16 hold_d_start[4];
    s16 hold_d_loop[4];
    s16 signal_done[10];
    s16 fly_resume[6];
    s16 reverse_stop[24];
    s16 *table[16];
} enemy_anims = {
    /* fly */ {
        STEP(4, 1),
        FLY(0),
        STEP(4, 1),
        STEP(4, 1),
        STEP(4, 1),
        GOTO(ENEMY_ANIM_FLY),
    },
    /* hover_start */ {
        FLY(3),
        STEP(16, 21),
        FLY(9),
        GOTO(ENEMY_ANIM_HOVER_CYCLE_END),
    },
    /* hover_settle */ {
        FLY(3),
        STEP(16, 30),
        FLY(9),
    },
    /* hover_cycle */ {
        STEP(1, 16),
        STEP(1, 17),
        STEP(1, 18),
        STEP(1, 19),
        STEP(1, 20),
        STEP(1, 21),
    },
    /* hover_cycle_end */ {
        STEP(1, 22),
        STEP(1, 23),
        STEP(1, 24),
        STEP(1, 25),
        STEP(1, 26),
        STEP(1, 27),
        STEP(1, 28),
        STEP(1, 29),
        STEP(1, 30),
        GOTO(ENEMY_ANIM_HOVER_CYCLE),
    },
    /* turn_right_start */ {
        STEP(4, 1),
        STEP(4, 32),
        STEP(12, 32),
    },
    /* turn_right_loop */ {
        STEP(8, 32),
        GOTO(ENEMY_ANIM_TURN_RIGHT_LOOP),
    },
    /* turn_left_start */ {
        STEP(4, 1),
        STEP(4, 33),
        STEP(12, 33),
    },
    /* turn_left_loop */ {
        STEP(8, 33),
        GOTO(ENEMY_ANIM_TURN_LEFT_LOOP),
    },
    /* hold_c_start */ {
        STEP(4, 1),
        STEP(4, 34),
        STEP(12, 34),
    },
    /* hold_c_loop */ {
        STEP(8, 34),
        GOTO(ENEMY_ANIM_HOLD_C_LOOP),
    },
    /* hold_d_start */ {
        STEP(4, 1),
        STEP(12, 35),
    },
    /* hold_d_loop */ {
        STEP(8, 35),
        GOTO(ENEMY_ANIM_HOLD_D_LOOP),
    },
    /* signal_done */ {
        STEP(12, 2),
        SET_F8(255),
        STEP(28, 2),
        STEP(8, 1),
        GOTO(ENEMY_ANIM_FLY),
    },
    /* fly_resume */ {
        STEP(2, 34),
        STEP(20, 1),
        GOTO(ENEMY_ANIM_FLY),
    },
    /* reverse_stop */ {
        STEP(5, 49),
        FLY(-4),
        STEP(5, 49),
        FLY(-2),
        STEP(5, 53),
        STEP(5, 57),
        FLY(0),
        STEP(5, 61),
        STEP(5, 77),
        STEP(5, 81),
        STEP(15, 83),
        GOTO(ENEMY_ANIM_FLY),
    },
    /* table */ {
        enemy_anims.fly, enemy_anims.hover_start, enemy_anims.hover_settle, enemy_anims.hover_cycle, enemy_anims.hover_cycle_end, enemy_anims.turn_right_start,
        enemy_anims.turn_right_loop, enemy_anims.turn_left_start, enemy_anims.turn_left_loop, enemy_anims.hold_c_start, enemy_anims.hold_c_loop, enemy_anims.hold_d_start,
        enemy_anims.hold_d_loop, enemy_anims.fly_resume, enemy_anims.signal_done, enemy_anims.reverse_stop,
    },
};

struct EnemyScripts {
    s16 idle[14];
    s16 spotted[10];
    s16 spotted_repeat[10];
    s16 blink_start[6];
    s16 blink_cooldown[8];
    s16 blink_cooling[6];
    s16 return_idle[8];
    s16 strafe_pick[6];
    s16 turn_pick[6];
    s16 chase_pick[18];
    s16 strafe_b_start[2];
    s16 strafe_b_run[10];
    s16 strafe_a_start[2];
    s16 strafe_a_run[10];
    s16 turn_pos_start[2];
    s16 turn_pos_run[10];
    s16 turn_neg_start[2];
    s16 turn_neg_run[10];
    s16 strafe_b_turn_pos_start[2];
    s16 strafe_b_turn_pos_run[10];
    s16 strafe_a_turn_neg_start[2];
    s16 strafe_a_turn_neg_run[10];
    s16 *table[22];
    s16 *D_8010FCC8;
} enemy_scripts = {
    /* idle */ {
        JUMP_RANDOM(2048, ENEMY_BLINK_START),
        SET_COUNTER_RANDOM(5, 3),
        JUMP_IF_CAMERA_NEAR(2048, ENEMY_SPOTTED),
        NEXT_STATE(ENEMY_STATE_WANDER),
        JUMP(ENEMY_RETURN_IDLE),
    },
    /* spotted */ {
        WAIT(8),
        JUMP_RANDOM(1024, ENEMY_CHASE_PICK),
        JUMP_RANDOM(1024, ENEMY_TURN_PICK),
        NEXT_STATE(ENEMY_STATE_BLINK_TIMER),
    },
    /* spotted_repeat */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, ENEMY_SPOTTED_REPEAT),
        LOOP(ENEMY_SPOTTED),
        JUMP(ENEMY_IDLE),
    },
    /* blink_start */ {
        NEXT_STATE(ENEMY_STATE_BLINK),
        SET_COUNTER_RANDOM(5, 3),
    },
    /* blink_cooldown */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, ENEMY_BLINK_COOLDOWN),
        SET_COUNTER_RANDOM(5, 3),
    },
    /* blink_cooling */ {
        WAIT(1),
        LOOP(ENEMY_BLINK_COOLING),
        JUMP(ENEMY_IDLE),
    },
    /* return_idle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, ENEMY_RETURN_IDLE),
        JUMP(ENEMY_IDLE),
    },
    /* strafe_pick */ {
        JUMP_RANDOM(2048, ENEMY_STRAFE_B_START),
        JUMP(ENEMY_STRAFE_A_START),
    },
    /* turn_pick */ {
        JUMP_RANDOM(2048, ENEMY_TURN_POS_START),
        JUMP(ENEMY_TURN_NEG_START),
    },
    /* chase_pick */ {
        JUMP_RANDOM(1024, ENEMY_STRAFE_PICK),
        JUMP_RANDOM(512, ENEMY_STRAFE_B_TURN_POS_START),
        JUMP_RANDOM(512, ENEMY_STRAFE_A_TURN_NEG_START),
        NEXT_STATE(ENEMY_STATE_STRAFE_A_TURN_POS),
        JUMP_RANDOM(2048, ENEMY_RETURN_IDLE),
        NEXT_STATE(ENEMY_STATE_STRAFE_B_TURN_NEG),
        JUMP(ENEMY_RETURN_IDLE),
    },
    /* strafe_b_start */ {
        NEXT_STATE(ENEMY_STATE_STRAFE_B),
    },
    /* strafe_b_run */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, ENEMY_STRAFE_B_RUN),
        LOOP(ENEMY_STRAFE_B_START),
        JUMP(ENEMY_RETURN_IDLE),
    },
    /* strafe_a_start */ {
        NEXT_STATE(ENEMY_STATE_STRAFE_A),
    },
    /* strafe_a_run */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, ENEMY_STRAFE_A_RUN),
        LOOP(ENEMY_STRAFE_A_START),
        JUMP(ENEMY_RETURN_IDLE),
    },
    /* turn_pos_start */ {
        NEXT_STATE(ENEMY_STATE_TURN_POS),
    },
    /* turn_pos_run */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, ENEMY_TURN_POS_RUN),
        LOOP(ENEMY_TURN_POS_START),
        JUMP(ENEMY_RETURN_IDLE),
    },
    /* turn_neg_start */ {
        NEXT_STATE(ENEMY_STATE_TURN_NEG),
    },
    /* turn_neg_run */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, ENEMY_TURN_NEG_RUN),
        LOOP(ENEMY_TURN_NEG_START),
        JUMP(ENEMY_RETURN_IDLE),
    },
    /* strafe_b_turn_pos_start */ {
        NEXT_STATE(ENEMY_STATE_STRAFE_B_TURN_POS),
    },
    /* strafe_b_turn_pos_run */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, ENEMY_STRAFE_B_TURN_POS_RUN),
        LOOP(ENEMY_STRAFE_B_TURN_POS_START),
        JUMP(ENEMY_RETURN_IDLE),
    },
    /* strafe_a_turn_neg_start */ {
        NEXT_STATE(ENEMY_STATE_STRAFE_A_TURN_NEG),
    },
    /* strafe_a_turn_neg_run */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, ENEMY_STRAFE_A_TURN_NEG_RUN),
        LOOP(ENEMY_STRAFE_A_TURN_NEG_START),
        JUMP(ENEMY_RETURN_IDLE),
    },
    /* table */ {
        enemy_scripts.idle, enemy_scripts.spotted, enemy_scripts.spotted_repeat, enemy_scripts.blink_start, enemy_scripts.blink_cooldown, enemy_scripts.blink_cooling,
        enemy_scripts.return_idle, enemy_scripts.strafe_pick, enemy_scripts.turn_pick, enemy_scripts.chase_pick, enemy_scripts.strafe_b_start, enemy_scripts.strafe_b_run,
        enemy_scripts.strafe_a_start, enemy_scripts.strafe_a_run, enemy_scripts.turn_pos_start, enemy_scripts.turn_pos_run, enemy_scripts.turn_neg_start, enemy_scripts.turn_neg_run,
        enemy_scripts.strafe_b_turn_pos_start, enemy_scripts.strafe_b_turn_pos_run, enemy_scripts.strafe_a_turn_neg_start, enemy_scripts.strafe_a_turn_neg_run,
    },
    /* D_8010FCC8 */ enemy_scripts.idle,
};

StateEntry D_8010FCCC[18] = {
    {0, ENEMY_ANIM_FLY, 0},
    {(u32)fly_random_turn_step, -1, 0},
    {(u32)blink_timer_update, ENEMY_ANIM_FLY, 0},
    {(u32)blink_link_update, ENEMY_ANIM_HOVER_SETTLE, 0},
    {0, ENEMY_ANIM_HOVER_START, 0},
    {(u32)fly_side_270_turn_plus16_step, ENEMY_ANIM_TURN_LEFT_START, 0},
    {(u32)fly_side_90_turn_minus16_step, ENEMY_ANIM_TURN_RIGHT_START, 0},
    {(u32)anim_wait_step, ENEMY_ANIM_SIGNAL_DONE, 0},
    {(u32)obj_spin_update, ENEMY_ANIM_SIGNAL_DONE, 0},
    {(u32)reverse_step, ENEMY_ANIM_FLY_RESUME, 1},
    {0, -1, 0},
    {(u32)fly_side_270_step, ENEMY_ANIM_TURN_LEFT_START, 1},
    {(u32)fly_side_90_step, ENEMY_ANIM_TURN_RIGHT_START, 1},
    {(u32)obj_turn_minus16_step, ENEMY_ANIM_HOVER_SETTLE, 0},
    {(u32)obj_turn_plus16_step, ENEMY_ANIM_HOVER_START, 0},
    {(u32)fly_side_270_turn_minus32_step, ENEMY_ANIM_TURN_LEFT_START, 0},
    {(u32)fly_side_90_turn_plus32_step, ENEMY_ANIM_TURN_RIGHT_START, 0},
    {0, -1, 0},
};

s32 spark_burst_offsets[5][4] = {
    {0, 0, 0, 0}, {0, 0, -12, 1}, {0, 0, -0x3C, 2}, {0, 0, -0x60, 3}, {0, 0, -0x18, 4},
};

#include "../stage/data/fade_red_fx_template.c"

#include "../stage/data/fx_owner_template_a.c"

u32 D_8010FE0C[20] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xFFFFFFF4, 0x00000001, 0x00000000, 0x00000000, 0xFFFFFFC4, 0x00000002,
    0x00000000, 0x00000000, 0xFFFFFFA0, 0x00000003, 0x00000000, 0x00000000,
    0xFFFFFFE8, 0x00000004,
};

RecTemplate fx_template_colour_fade = {1, 0x40, 0x60, 0xC0, 0, 0, 0x8000, -0xAAA, 0x71, 0xC000};

RecTemplate fx_template_spot_effect = {1, 0x40, 0x40, 0xC0, 0, 0, 0x100000, (s32)0xFFFEAAAB, 0xE38, (s32)0xFF000000};

RecTemplate fx_template_spot = {1, 0, 0, 0xFF, 0, 0x80, 0x80000, 0x5145, -0x1000, 0x10000};

RecTemplate fx_template_fade_rgb = {1, 0x80, 0x80, 0x80, 0, 0x30, 0x80000, 0x8590, -0x55, 0x20000};

s32 D_8010FEBC[3] = {
    -1, -1, -1,
};

s32 zone_spark_base = -1;

s32 zone_blend_base = -1;

ScanEntry enemy_door_scan_entry = {{0, 0}, D_8010FEBC, 0, 0, 0};

u8 *enemy_ctlt_stage_files[3] = {
    str_ctlt_spr_clt, str_ctlt_spr_grc, str_ctlt_spr_so3,
};

u8 *enemy_ctlt_ptr_table_ids[2] = {
    str_ctlt_objcb4, NULL,
};

s32 D_8010FEFC = -1;

s32 D_8010FF00 = -1;

s32 mission_text_base = -1;

ScanEntry enemy_ctlt_scan_entry = {{(s32)stage_init, (s32)stage_load_params}, &D_8010FEFC, 0, (s32)enemy_ctlt_ptr_table_ids, (s32)enemy_ctlt_stage_files};

AngleBlendEntry D_8010FF20[6] = {
    {0, 0, 0xD8, {0, 0, 0, 0}, 0xF3, 1, 0xF4, 2, 1, 0x180, 0x180, 0x300, 0x300, 0},
    {0, 0, -0x180, {0, 0, 0, 0}, 0x16, 5, 0x75, 6, 1, 0x300, 0x400, 0x400, 0x400, 0},
    {0, 0, 0x180, {0, 0, 0, 0}, 0x18, 7, 0x76, 8, 1, 0x300, 0x1388, 0x400, 0x400, 0},
    {0, 0, -0xD8, {0, 0, 0, 0}, 0xF8, 3, 0xF9, 4, 1, 0x180, 0x180, 0x400, 0x400, 0},
    {0, 0, -0xD8, {0, 0, 0, 0}, 0x2C, 9, 0x2D, 0xA, 1, 0x180, 0x180, 0x400, 0x400, 0},
    {0, 0, -0xD8, {0, 0, 0, 0}, 0x5C, 0xB, 0x5D, 0xC, 1, 0x180, 0x180, 0x400, 0x400, 0},
};

u32 req_entry_table = 0x000002D0;

u32 D_8010FFFC = 0xFFFFFF70;

u32 D_80110000[66] = {
    0xFFFFAA40, 0x0000FA00, 0x00000000, 0xFFFFFF40, 0xFFFFDCB0, 0x0000FB01,
    0x00000000, 0xFFFFFF40, 0xFFFFF7B0, 0x0000FC02, 0x00000F30, 0xFFFFFF70,
    0x00001816, 0x0001FD03, 0x000007B0, 0xFFFFFF70, 0x00001816, 0x0001FD03,
    0x00000030, 0xFFFFFF70, 0x00001816, 0x0001FD03, 0xFFFFF8B0, 0xFFFFFF70,
    0x00001816, 0x0001FD03, 0xFFFFF130, 0xFFFFFF70, 0x00001816, 0x0001FD03,
    0x00000F30, 0xFFFFFF70, 0x00003D36, 0x0001FE04, 0x000007B0, 0xFFFFFF70,
    0x00003D36, 0x0001FE04, 0x00000030, 0xFFFFFF70, 0x00003D36, 0x0001FE04,
    0xFFFFF8B0, 0xFFFFFF70, 0x00003D36, 0x0001FE04, 0xFFFFF130, 0xFFFFFF70,
    0x00003D36, 0x0001FE04, 0x000007B0, 0xFFFFFF70, 0x00006A36, 0x0001FF05,
    0x00000210, 0xFFFFFF70, 0x00006A36, 0x0001FF05, 0xFFFFFC70, 0xFFFFFF70,
    0x00006A36, 0x0001FF05, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF,
};

u32 D_80110108 = 0x000000FF;

u32 D_8011010C = 0x0000FF01;

u32 D_80110110 = 0x0000FF02;

u32 D_80110114[2] = {
    0x06050403, 0x0000FF07,
};

u32 D_8011011C[2] = {
    0x0B0A0908, 0x0000FF0C,
};

u32 D_80110124 = 0xFF0F0E0D;

u32 D_80110128 = 0x000000FF;

u8 *stage_draw_lists[1] = {
    (u8 *)&D_80110108,
};

u8 *stage_load_lists[6] = {
    (u8 *)&D_8011010C, (u8 *)&D_80110110, D_80110114, D_8011011C, (u8 *)&D_80110124, (u8 *)&D_80110128,
};

s32 mission_bonus_msg_ids[7] = {
    6, 2, 7, 8, 3, 9,
    10,
};

s32 slot_range_min_table[1] = {
    -0x55F0,
};

s32 slot_range_max_table[1] = {
    -0x251C,
};

ClampRange slot_enemy_limits[5] = {
    {0x63, 0xE10, -0x251C, -0x5DC},
    {0x63, 0xE10, -0x5DC, 0x1B58},
    {0x63, 0xE10, 0x1B58, 0x4074},
    {0x63, 0xE10, 0x4074, 0x6D60},
    {0x63, 0xE10, 0x6D60, 0x86C4},
};

u32 D_801101A8 = 0x00000001;

s32 cam_zone_table[3][6] = {
    {0x480, 0xE44, -0x240, 0, -0x2290, -0x15D0},
    {-0x540, 0x840, -0x240, 0, -0x1690, -0x1210},
    {-0x840, -0x3C0, -0x240, 0, -0x1690, -0x910},
};

u32 stage_data_buf[5] = {
    1, 0, 0xFFFFFC00, 0, 0xF0000000,
};

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_80114D88[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/video_mode_id.c"

#include "../stage/data/tint_scale_r.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_80115F0C[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_8011652C = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

#include "../stage/data/grid_flagged_count.c"

#include "../stage/data/d_8011FEE4.c"

u32 D_80117988 = 0x00000000;

#include "../stage/data/fade_red_obj.c"

AngleBlendEntry *zone_table = NULL;

s32 stage_list_index = 0;

s32 slot_enemy_total = 0;

s32 slot_kills = 0;

s32 slot_kill_base = 0;

s32 stage_enemies_left = 0;

s32 draw_list_index = 0;

#include "../stage/data/frame_work_area.c"

#include "../stage/data/model_slot_count.c"

u32 D_80117A60 = 0x00000000;

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

u32 D_80117AE4 = 0x00000000;

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

GridEntry *flagged_grid_cells[35] = {0};

/* labels inside the objects above */
__asm__(".globl mission_bonus_table\n.set mission_bonus_table, slot_enemy_limits+0x2\n"
        ".globl cos_table\n.set cos_table, rcossin_tbl+0x2\n"
        ".globl debug_menu_marks\n.set debug_menu_marks, debug_menu_text_rows+0x1\n"
        ".globl debug_menu_flag_cell\n.set debug_menu_flag_cell, debug_menu_text_rows+0x4F\n"
        ".globl gun_hit_effect_table\n.set gun_hit_effect_table, trail_offsets+0xE\n"
        ".globl D_80116532\n.set D_80116532, texture_image+0x2\n"
        ".globl pad1_pressed\n.set pad1_pressed, pad1+0x2\n"
        ".globl D_80117F5A\n.set D_80117F5A, scale_vec+0x2\n"
        ".globl D_8010F874\n.set D_8010F874, enemy_init_handlers_anims+0x34\n"
        ".globl blink_jump_script\n.set blink_jump_script, enemy_anims+0x114\n"
        ".globl fly_turn_pos_script\n.set fly_turn_pos_script, enemy_anims+0x124\n"
        ".globl fly_turn_neg_script\n.set fly_turn_neg_script, enemy_anims+0x12C\n"
        ".globl enemy_death_slot\n.set enemy_death_slot, enemy_anims+0x14C\n"
        ".globl spark_burst_frames\n.set spark_burst_frames, spark_burst_offsets+0xC\n"
        ".globl sincos_deg90\n.set sincos_deg90, rcossin_tbl+0x1000\n"
        ".globl view_sincos\n.set view_sincos, rcossin_tbl+0x2000\n"
        ".globl sincos_deg270\n.set sincos_deg270, rcossin_tbl+0x3000\n"
        ".globl d_8011DCA2\n.set d_8011DCA2, font_clut+0x2\n"
        ".globl d_8011DCA4\n.set d_8011DCA4, font_clut+0x4\n"
        ".globl d_8011DE04\n.set d_8011DE04, spark_point_table+0xC\n"
        ".globl d_8011DE44\n.set d_8011DE44, spark_point_table+0x4C\n"
        ".globl D_80117C12\n.set D_80117C12, view_nudge+0x2\n"
        ".globl d_801201AE\n.set d_801201AE, flow+0x2\n"
        ".globl flow_angle\n.set flow_angle, flow+0x4\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl enemy_init_handlers_anim_idle\n.set enemy_init_handlers_anim_idle, enemy_init_handlers_anims+0x0\n"
        ".globl enemy_init_handlers_anim_alt_idle\n.set enemy_init_handlers_anim_alt_idle, enemy_init_handlers_anims+0xC\n"
        ".globl enemy_init_handlers_anim_alt_to_idle\n.set enemy_init_handlers_anim_alt_to_idle, enemy_init_handlers_anims+0x18\n"
        ".globl enemy_init_handlers_anim_idle_to_alt\n.set enemy_init_handlers_anim_idle_to_alt, enemy_init_handlers_anims+0x24\n"
        ".globl enemy_script_table\n.set enemy_script_table, enemy_init_handlers_anims+0x30\n"
        ".globl obj_type_data_idle\n.set obj_type_data_idle, obj_type_data_scripts+0x0\n"
        ".globl obj_type_data\n.set obj_type_data, obj_type_data_scripts+0x8\n"
        ".globl obj_data_entry_table\n.set obj_data_entry_table, obj_type_data_scripts+0xC\n"
        ".globl enemy_anim_fly\n.set enemy_anim_fly, enemy_anims+0x0\n"
        ".globl enemy_anim_hover_start\n.set enemy_anim_hover_start, enemy_anims+0x18\n"
        ".globl enemy_anim_hover_settle\n.set enemy_anim_hover_settle, enemy_anims+0x28\n"
        ".globl enemy_anim_hover_cycle\n.set enemy_anim_hover_cycle, enemy_anims+0x34\n"
        ".globl enemy_anim_hover_cycle_end\n.set enemy_anim_hover_cycle_end, enemy_anims+0x4C\n"
        ".globl enemy_anim_turn_right_start\n.set enemy_anim_turn_right_start, enemy_anims+0x74\n"
        ".globl enemy_anim_turn_right_loop\n.set enemy_anim_turn_right_loop, enemy_anims+0x80\n"
        ".globl enemy_anim_turn_left_start\n.set enemy_anim_turn_left_start, enemy_anims+0x88\n"
        ".globl enemy_anim_turn_left_loop\n.set enemy_anim_turn_left_loop, enemy_anims+0x94\n"
        ".globl enemy_anim_hold_c_start\n.set enemy_anim_hold_c_start, enemy_anims+0x9C\n"
        ".globl enemy_anim_hold_c_loop\n.set enemy_anim_hold_c_loop, enemy_anims+0xA8\n"
        ".globl enemy_anim_hold_d_start\n.set enemy_anim_hold_d_start, enemy_anims+0xB0\n"
        ".globl enemy_anim_hold_d_loop\n.set enemy_anim_hold_d_loop, enemy_anims+0xB8\n"
        ".globl enemy_anim_signal_done\n.set enemy_anim_signal_done, enemy_anims+0xC0\n"
        ".globl enemy_anim_fly_resume\n.set enemy_anim_fly_resume, enemy_anims+0xD4\n"
        ".globl enemy_anim_reverse_stop\n.set enemy_anim_reverse_stop, enemy_anims+0xE0\n"
        ".globl fly_script_base\n.set fly_script_base, enemy_anims+0x110\n"
        ".globl enemy_idle\n.set enemy_idle, enemy_scripts+0x0\n"
        ".globl enemy_spotted\n.set enemy_spotted, enemy_scripts+0x1C\n"
        ".globl enemy_spotted_repeat\n.set enemy_spotted_repeat, enemy_scripts+0x30\n"
        ".globl enemy_blink_start\n.set enemy_blink_start, enemy_scripts+0x44\n"
        ".globl enemy_blink_cooldown\n.set enemy_blink_cooldown, enemy_scripts+0x50\n"
        ".globl enemy_blink_cooling\n.set enemy_blink_cooling, enemy_scripts+0x60\n"
        ".globl enemy_return_idle\n.set enemy_return_idle, enemy_scripts+0x6C\n"
        ".globl enemy_strafe_pick\n.set enemy_strafe_pick, enemy_scripts+0x7C\n"
        ".globl enemy_turn_pick\n.set enemy_turn_pick, enemy_scripts+0x88\n"
        ".globl enemy_chase_pick\n.set enemy_chase_pick, enemy_scripts+0x94\n"
        ".globl enemy_strafe_b_start\n.set enemy_strafe_b_start, enemy_scripts+0xB8\n"
        ".globl enemy_strafe_b_run\n.set enemy_strafe_b_run, enemy_scripts+0xBC\n"
        ".globl enemy_strafe_a_start\n.set enemy_strafe_a_start, enemy_scripts+0xD0\n"
        ".globl enemy_strafe_a_run\n.set enemy_strafe_a_run, enemy_scripts+0xD4\n"
        ".globl enemy_turn_pos_start\n.set enemy_turn_pos_start, enemy_scripts+0xE8\n"
        ".globl enemy_turn_pos_run\n.set enemy_turn_pos_run, enemy_scripts+0xEC\n"
        ".globl enemy_turn_neg_start\n.set enemy_turn_neg_start, enemy_scripts+0x100\n"
        ".globl enemy_turn_neg_run\n.set enemy_turn_neg_run, enemy_scripts+0x104\n"
        ".globl enemy_strafe_b_turn_pos_start\n.set enemy_strafe_b_turn_pos_start, enemy_scripts+0x118\n"
        ".globl enemy_strafe_b_turn_pos_run\n.set enemy_strafe_b_turn_pos_run, enemy_scripts+0x11C\n"
        ".globl enemy_strafe_a_turn_neg_start\n.set enemy_strafe_a_turn_neg_start, enemy_scripts+0x130\n"
        ".globl enemy_strafe_a_turn_neg_run\n.set enemy_strafe_a_turn_neg_run, enemy_scripts+0x134\n"
        ".globl enemy_op_table\n.set enemy_op_table, enemy_scripts+0x148\n"
        ".globl D_8010FCC8\n.set D_8010FCC8, enemy_scripts+0x1A0\n");
