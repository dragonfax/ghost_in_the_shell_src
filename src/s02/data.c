/* s02 data 0x801164C0-0x8011F000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s02_types.h"
#include "script.h"
#include "scripts.h"
#include "sounds.h"

extern void beam_enemy_attack_update();
extern void cam_track_b_setup();
extern void cam_track_get();
extern void cam_track_init();
extern void cam_track_set_active();
extern void cam_track_set_on();
extern void cam_track_setup();
extern void cam_track_slot_get();
extern void cam_zone_spawn();
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
extern void enemy_chase_player();
extern void enemy_create();
extern void enemy_fly_forward();
extern void enemy_move_or_wait();
extern void enemy_wait_switch();
extern void enemy_walk_step();
extern u8 file_msgs_spr_clt[];
extern u8 file_msgs_spr_grc[];
extern u8 file_msgs_spr_so3[];
extern void flyer_retreat();
extern void flyer_wander();
extern void fn_800E8024();
extern void fn_800E8030();
extern void fn_801090F8();
extern void gun_turret_2_spawn();
extern void handler_range_call();
extern void handler_range_call_zero();
extern void interp1c_set_state();
extern void interp2c_set_state();
extern void interp38_set_state();
extern void interp38b_set_state();
extern void interp_set_state();
extern void mission_state_reset();
extern u8 model_base_slot[];
extern void night_vision_init();
extern void obj_area_update();
extern void obj_call_hook();
extern void obj_hit_handle();
extern void obj_hook_or_free();
extern void obj_jump_if_player_near();
extern void obj_release_check();
extern void obj_run_stored_update();
extern void obj_script_jump_within();
extern void obj_set_next_state();
extern void obj_speed_approach();
extern void obj_state_dispatch();
extern void part_rec_get();
extern void part_rec_set_active();
extern void part_record_read();
extern void part_slot_set_state();
extern void placed_actor_spawn();
extern void placement_spawn();
extern void ramp_start_script();
extern void rocket_drone_spawn();
extern void script_branch_if_far();
extern void script_branch_if_within();
extern void script_jump_if_above_z();
extern void script_jump_if_below_z();
extern void script_op_jump_table_if_player_far();
extern void script_op_set_next_state();
extern void script_read_speed();
extern void script_read_u16_field();
extern void script_set_turn_mode();
extern void sea_mine_spawn();
extern void show_giant_warning();
extern u8 str_b02_dat_fac[];
extern u8 str_b02_ene_fac[];
extern u8 str_b02_joy_bin[];
extern u8 str_b12_apdea3[];
extern u8 str_b12_cnf_bcf[];
extern u8 str_bos2_ch0_clt[];
extern u8 str_bos2_ch0_vx1[];
extern u8 str_bos2_ch0cb4[];
extern u8 str_bos2_ch1_clt[];
extern u8 str_bos2_ch1_vx1[];
extern u8 str_bos2_ch1cb4[];
extern u8 str_bos2_ch2_clt[];
extern u8 str_bos2_ch2_vx1[];
extern u8 str_bos2_ch2cb4[];
extern u8 str_bos2_ch3_clt[];
extern u8 str_bos2_ch3_vx1[];
extern u8 str_bos2_ch3cb4[];
extern u8 str_bos2_tp0_clt[];
extern u8 str_bos2_tp0_xs3[];
extern u8 str_bos2_tp1_clt[];
extern u8 str_bos2_tp1_xs3[];
extern u8 str_com_dat_fac[];
extern u8 str_enemy_bos2_data[];
extern u8 str_enemy_ctl2_data[];
extern u8 str_enemy_hou2_data[];
extern u8 str_enemy_jira_data[];
extern u8 str_enemy_kira_data[];
extern u8 str_enemy_mfir_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_oct_data[];
extern u8 str_enemy_sel1_data[];
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
extern u8 str_kira_ch0_clt[];
extern u8 str_kira_ch0_vx1[];
extern u8 str_kira_ch0cb4[];
extern u8 str_kira_tp0_clt[];
extern u8 str_kira_tp0_xs3[];
extern u8 str_m02_dat_fac[];
extern u8 str_m12_cnf_bcf[];
extern u8 str_m12_joy_bin[];
extern u8 str_main_data[];
extern u8 str_mfir_ch0_clt[];
extern u8 str_mfir_ch0_vx1[];
extern u8 str_mfir_ch0cb4[];
extern u8 str_mfir_tp0_clt[];
extern u8 str_mfir_tp0_xs3[];
extern u8 str_msgspr_clt[];
extern u8 str_msgspr_grc[];
extern u8 str_msgspr_so3[];
extern u8 str_s02_boss[];
extern u8 str_s02_dat_fac[];
extern u8 str_s02_ene_fac[];
extern u8 str_s02_joy_bin[];
extern u8 str_s02_miss[];
extern u8 str_s02_stage[];
extern u8 str_sdw_obj_vx1[];
extern u8 str_sdw_tp0_clt[];
extern u8 str_sdw_tp0_xs3[];
extern u8 str_sel1_ch0_clt[];
extern u8 str_sel1_ch0_vx1[];
extern u8 str_sel1_ch0cb4[];
extern u8 str_sel1_tp0_clt[];
extern u8 str_sel1_tp0_xs3[];
extern u8 str_sew_apdea3[];
extern u8 str_sew_cnf_bcf[];
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
extern void tunnel_mech_damage_update();
extern void tunnel_mech_m2_boss_spawn();
extern void turret_branch_if_aimed();
extern void turret_track_player();
extern void view_rec_get();
extern void view_rec_set_on();
extern void view_rec_setup();
extern u8 D_80116F02[];
extern u8 D_8011746C[];
extern u8 D_8011DBB2[];
extern u8 cam_zone_x0[];
extern u8 cam_zone_x1[];
extern u8 cam_zone_y[];
extern u8 cam_zone_z0[];
extern u8 cam_zone_z1[];
extern u8 cos_table[];
extern u8 d_80116A38[];
extern u8 d_8011DCA2[];
extern u8 d_8011DCA4[];
extern u8 d_8011DE04[];
extern u8 d_8011DE44[];
extern u8 debug_menu_flag_cell[];
extern u8 debug_menu_marks[];
extern u8 enemy_death_script[];
extern u8 enemy_shot_id[];
extern u8 gun_hit_effect_table[];
extern u8 sincos_deg270[];
extern u8 sincos_deg90[];
extern u8 view_sincos[];
extern s32 area;
extern ScanItem stage_enemy_items[];
extern AreaEntry stage_area_record;
extern AreaEntry D_8011652C;
extern ScanItem boss_area_items[];
extern AreaEntry boss_area_record;
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
extern BeamStep beam_segment_data[6];
extern s32 enemy_model_data[3];
extern ModelBlockRef enemy_clut_refs[];
extern ModelBlockRef d_80116748[];
extern ModelBlockRef enemy_mesh_refs[];
extern ModelBlockRange enemy_scales[];
extern ModelBlockRange d_801167A8[];
extern ModelBlock enemy_block_def;
extern u8 *D_801167DC[];
extern ScanEntry D_801167E4;
extern SoundVolume D_801167FC[1];
extern s16 enemy_start_script[];
extern s16 flamethrower_soldier_anim_idle[];
extern s16 flamethrower_soldier_anim_walk_start[];
extern s16 flamethrower_soldier_anim_walk[];
extern s16 flamethrower_soldier_anim_fire_start[];
extern s16 flamethrower_soldier_anim_fire_loop[];
extern s16 flamethrower_soldier_anim_stand[];
extern s16 flamethrower_soldier_anim_death[];
extern s16 *enemy_data[8];
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
extern s16 *flamethrower_soldier_jumps[14];
extern s16 *flamethrower_soldier_scripts[5];
extern StateEntry D_80116B48[8];
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
extern s32 sea_mine_asset[];
extern ModelBlockRef sea_mine_clt_refs[];
extern ModelBlockRef sea_mine_xs3_refs[];
extern ModelBlockRef sea_mine_vx1_refs[];
extern ModelBlockRange D_80116E9C[];
extern ModelBlock sea_mine_model_set;
extern u8 *sea_mine_cb4_names[];
extern ScanEntry sea_mine_load_entry;
extern u16 sea_mine_anim_frames[];
extern StateEntry d_80116F10[];
extern s16 sea_mine_script[];
extern s16 *sea_mine_script_arg[];
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
extern RecTemplate burst_fx_template;
extern RecTemplate D_80116FE8;
extern s32 tunnel_mech_asset[];
extern ModelBlockRef D_8011700C[];
extern ModelBlockRef D_80117044[];
extern ModelBlockRef tunnel_mech_model_refs[];
extern ModelBlockRange D_80117084[];
extern ModelBlockRange D_801170A4[];
extern ModelBlock tunnel_mech_model_block;
extern u8 *D_801170E0[];
extern ScanEntry tunnel_mech_scan_entry;
extern u32 D_8011710C[];
extern s16 tunnel_mech_path[];
extern s16 tunnel_mech_path_b_table[];
extern s16 tunnel_mech_path_c_table[];
extern s16 tunnel_mech_m2_boss_intro[];
extern s16 tunnel_mech_m2_boss_dispatch[];
extern s16 tunnel_mech_m2_boss_near_check[];
extern s16 tunnel_mech_m2_boss_approach[];
extern s16 tunnel_mech_m2_boss_fire_check[];
extern s16 tunnel_mech_m2_boss_aim[];
extern s16 tunnel_mech_m2_boss_aim_wait[];
extern s16 tunnel_mech_m2_boss_advance[];
extern s16 tunnel_mech_m2_boss_advance_wait[];
extern s16 tunnel_mech_m2_boss_fall_back[];
extern s16 tunnel_mech_m2_boss_retreat_wait[];
extern s16 tunnel_mech_m2_boss_fire_burst[];
extern s16 tunnel_mech_m2_boss_fire_loop[];
extern s16 tunnel_mech_m2_boss_halt[];
extern s16 tunnel_mech_m2_boss_halt_loop[];
extern s16 tunnel_mech_m2_boss_pause[];
extern s16 tunnel_mech_m2_boss_recheck[];
extern s16 *tunnel_mech_script[];
extern s16 *D_80117310;
extern ScriptCallEntry D_80117314[];
extern void (*obj_state_step_table[])(Object *, ObjHandler *);
extern RecTemplate fade_red_fx_template;
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
extern FxRecordParams fx_rec34_params;
extern s32 D_801173BC[];
extern ScanEntry enemy_oct_scan_entry;
extern s32 enemy_ctl2_scan_out[];
extern ScanEntry enemy_ctl2_scan_entry;
extern RangeBox cam_zone_boxes[5];
extern s16 cam_zone_night_table[];
extern s32 cam_zone_shade_rec_ids[];
extern SoundSegmentList cam_zone_sound_owner_a;
extern SoundSegmentList cam_zone_sound_owner_b;
extern SoundSegmentList cam_zone_sound_owner_c;
extern PathPoint cam_zone_path[];
extern s32 player_flag8_obj_ids[];
extern u16 d_8011876C[];
extern s32 rcossin_tbl[4096];
extern s16 video_mode_id;
extern s16 debug_cam_speed_table[][2];
extern s32 pause_prev_work_area;
extern s32 vblank_task_handle;
extern u16 atan_table[];
extern u16 rand_seed_table[64];
extern s16 SQRT[192];
extern u32 D_8011C428[];
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
extern u32 D_8011D58C[];
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
extern u32 D_8011DBAC;
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

s32 area = 3;

ScanItem stage_enemy_items[8] = {
    {&D_801167E4, str_enemy_mfir_data},
    {&sea_mine_load_entry, str_enemy_kira_data},
    {&jira_load_step, str_enemy_jira_data},
    {&rocket_drone_scan_entry, str_enemy_sel1_data},
    {&gun_turret_2_scan, str_enemy_hou2_data},
    {&enemy_oct_scan_entry, str_enemy_oct_data},
    {&enemy_ctl2_scan_entry, str_enemy_ctl2_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry stage_area_record = {str_s02_stage, str_sew_cnf_bcf, str_sew_apdea3, str_s02_joy_bin, str_s02_dat_fac, str_s02_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0x2000, stage_enemy_items};

AreaEntry D_8011652C = {str_s02_miss, str_m12_cnf_bcf, NULL, str_m12_joy_bin, str_m02_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

ScanItem boss_area_items[3] = {
    {&tunnel_mech_scan_entry, str_enemy_bos2_data},
    {&d_801166DC, str_enemy_msgs_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry boss_area_record = {str_s02_boss, str_b12_cnf_bcf, str_b12_apdea3, str_b02_joy_bin, str_b02_dat_fac, str_b02_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0x2000, boss_area_items};

AreaEntry *area_entry_table[3] = {
    &D_8011652C, &stage_area_record, &boss_area_record,
};

#include "../stage/data/debug_name_buf.c"

#include "../stage/data/d_80116660.c"

#include "../stage/data/msg_id_base.c"

#include "../stage/data/enemy_msgs_files.c"

#include "../stage/data/d_801166DC.c"

#include "../stage/data/beam_segment_data.c"

s32 enemy_model_data[3] = {
    -1, -1, -1,
};

ModelBlockRef enemy_clut_refs[3] = {
    {(s32)str_mfir_ch0_clt, 0, 0},
    {(s32)str_mfir_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef d_80116748[2] = {
    {(s32)str_mfir_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef enemy_mesh_refs[2] = {
    {(s32)str_mfir_ch0_vx1, 0, 0},
    {0, 0, 0},
};

#include "../stage/data/enemy_scales.c"

#include "../stage/data/d_801167A8.c"

#include "../stage/data/enemy_block_def.c"

u8 *D_801167DC[2] = {
    str_mfir_ch0cb4, NULL,
};

ScanEntry D_801167E4 = {{0, (s32)enemy_create}, enemy_model_data, (s32)&enemy_block_def, (s32)D_801167DC, 0};

SoundVolume D_801167FC[1] = {
    {SND_GROUND_IMPACT | SND_GROUP(2), 0x1000},
};

#include "../stage/data/enemy_data_streams.c"

struct SmgSoldierScripts {
    s16 idle[6];
    s16 idle_pause[4];
    s16 idle_cycle[10];
    s16 patrol[6];
    s16 patrol_cycle[12];
    s16 patrol_wait[6];
    s16 hold[4];
    s16 hold_pause[4];
    s16 hold_cycle[10];
    s16 walk[4];
    s16 walk_step[4];
    s16 walk_cycle[10];
    s16 walk_pause[4];
    s16 walk_pause_cycle[10];
    s16 *table[14];
    s16 *flamethrower_soldier_scripts[5];
} smg_soldier_scripts = {
    /* idle */ {
        JUMP_RANDOM(3072, SMG_SOLDIER_PATROL),
        SET_COUNTER_RANDOM(3, 1),
    },
    /* idle_pause */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* idle_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_IDLE_CYCLE),
        LOOP(SMG_SOLDIER_IDLE_PAUSE),
        JUMP(SMG_SOLDIER_IDLE),
    },
    /* patrol */ {
        WAIT(1),
        WANDER(1),
        NEXT_STATE(ENEMY_STATE_WANDER),
    },
    /* patrol_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_PATROL_CYCLE),
        SET_SPEED(0),
        WANDER(1),
        SET_COUNTER_RANDOM(5, 3),
    },
    /* patrol_wait */ {
        WAIT(1),
        LOOP(SMG_SOLDIER_PATROL_WAIT),
        JUMP(SMG_SOLDIER_IDLE),
    },
    /* hold */ {
        SET_COUNTER_RANDOM(3, 1),
    },
    /* hold_pause */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* hold_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_HOLD_CYCLE),
        LOOP(SMG_SOLDIER_HOLD_PAUSE),
        JUMP(SMG_SOLDIER_HOLD),
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
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_WALK_CYCLE),
        LOOP(SMG_SOLDIER_WALK_STEP),
        JUMP(SMG_SOLDIER_WALK),
    },
    /* walk_pause */ {
        WAIT(8),
        NEXT_STATE(ENEMY_STATE_WAIT),
    },
    /* walk_pause_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(ENEMY_STATE_IDLE, SMG_SOLDIER_WALK_PAUSE_CYCLE),
        LOOP(SMG_SOLDIER_WALK_PAUSE),
        JUMP(SMG_SOLDIER_WALK),
    },
    /* table */ {
        smg_soldier_scripts.idle, smg_soldier_scripts.idle_pause, smg_soldier_scripts.idle_cycle, smg_soldier_scripts.patrol, smg_soldier_scripts.patrol_cycle, smg_soldier_scripts.patrol_wait,
        smg_soldier_scripts.hold, smg_soldier_scripts.hold_pause, smg_soldier_scripts.hold_cycle, smg_soldier_scripts.walk, smg_soldier_scripts.walk_step, smg_soldier_scripts.walk_cycle,
        smg_soldier_scripts.walk_pause, smg_soldier_scripts.walk_pause_cycle,
    },
    /* flamethrower_soldier_scripts */ {
        smg_soldier_scripts.idle, smg_soldier_scripts.hold, smg_soldier_scripts.walk, smg_soldier_scripts.hold, smg_soldier_scripts.walk,
    },
};

StateEntry D_80116B48[8] = {
    {0, ENEMY_START_SCRIPT, 0},
    {(u32)enemy_wait_switch, FLAMETHROWER_SOLDIER_ANIM_IDLE, 0},
    {(u32)enemy_move_or_wait, FLAMETHROWER_SOLDIER_ANIM_WALK_START, 0},
    {(u32)enemy_walk_step, FLAMETHROWER_SOLDIER_ANIM_FIRE_START, 0},
    {(u32)flyer_wander, FLAMETHROWER_SOLDIER_ANIM_FIRE_START, 0},
    {(u32)beam_enemy_attack_update, FLAMETHROWER_SOLDIER_ANIM_STAND, 0},
    {(u32)flyer_retreat, FLAMETHROWER_SOLDIER_ANIM_WALK, 0},
    {0, FLAMETHROWER_SOLDIER_ANIM_DEATH, 0},
};

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
        ROCKET_DRONE_JUMP_TABLE_IF_PLAYER_FAR, 3200, ROCKET_DRONE_PATROL,
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
    {NULL, 0},
    {obj_speed_approach, 0},
    {obj_set_next_state, 0},
    {script_set_turn_mode, 0},
    {obj_jump_if_player_near, 0},
    {script_op_jump_table_if_player_far, 0},
};

#include "../stage/data/rocket_drone_state_table.c"

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

#include "../stage/data/sea_mine_asset.c"

ModelBlockRef sea_mine_clt_refs[3] = {
    {(s32)str_kira_ch0_clt, 0, 0},
    {(s32)str_kira_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef sea_mine_xs3_refs[2] = {
    {(s32)str_kira_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef sea_mine_vx1_refs[2] = {
    {(s32)str_kira_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_80116E9C[4] = {
    {1, 2, 0x2000, 0}, {4, 5, 0x2000, 0}, {8, 10, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlock sea_mine_model_set = {(s32)sea_mine_clt_refs, (s32)sea_mine_vx1_refs, (s32)sea_mine_xs3_refs, 0, 0, 0, (s32)D_80116E9C, 0, 0};

u8 *sea_mine_cb4_names[2] = {
    str_kira_ch0cb4, NULL,
};

ScanEntry sea_mine_load_entry = {{0, (s32)sea_mine_spawn}, sea_mine_asset, (s32)&sea_mine_model_set, (s32)sea_mine_cb4_names, 0};

#include "../stage/data/sea_mine_anim_frames.c"

#include "../stage/data/d_80116F10.c"

#include "../stage/data/sea_mine_anims.c"

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

RecTemplate burst_fx_template = {1, 0x40, 0x52, 0xFF, 0x800, 0x2A, 0x70000, 0x28000, -0x1000, 0x4000};

RecTemplate D_80116FE8 = {1, 0xC0, 0xC0, 0xFF, 0x800, 0x2A, 0x70000, 0x26000, -0x1000, 0x4000};

s32 tunnel_mech_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_8011700C[7] = {
    {(s32)str_bos2_ch0_clt, 0, 0},
    {(s32)str_bos2_ch1_clt, 0, 0},
    {(s32)str_bos2_ch2_clt, 0, 0},
    {(s32)str_bos2_ch3_clt, 0, 0},
    {(s32)str_bos2_tp0_clt, 0, 0},
    {(s32)str_bos2_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_80117044[3] = {
    {(s32)str_bos2_tp0_xs3, 4, 0},
    {(s32)str_bos2_tp1_xs3, 5, 0},
    {0, 0, 0},
};

ModelBlockRef tunnel_mech_model_refs[5] = {
    {(s32)str_bos2_ch0_vx1, 0, 0},
    {(s32)str_bos2_ch1_vx1, 0, 0},
    {(s32)str_bos2_ch2_vx1, 0, 0},
    {(s32)str_bos2_ch3_vx1, 3, 0},
    {0, 0, 0},
};

ModelBlockRange D_80117084[4] = {
    {0x185, 0x188, 0x2000, 0}, {0x191, 0x193, 0x2000, 0}, {0x1A0, 0x1A3, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlockRange D_801170A4[3] = {
    {-1, 0, 0, 0}, {0, 0x100, 0x1000, 0}, {-1, 0, 0, 0},
};

ModelBlock tunnel_mech_model_block = {(s32)D_8011700C, (s32)tunnel_mech_model_refs, (s32)D_80117044, 0, (s32)D_80117084, 0, (s32)D_801170A4, 0, 0};

u8 *D_801170E0[5] = {
    str_bos2_ch0cb4, str_bos2_ch1cb4, str_bos2_ch2cb4, str_bos2_ch3cb4, NULL,
};

ScanEntry tunnel_mech_scan_entry = {{(s32)show_giant_warning, (s32)tunnel_mech_m2_boss_spawn}, tunnel_mech_asset, (s32)&tunnel_mech_model_block, (s32)D_801170E0, 0};

u32 D_8011710C[3] = {
    0x10000000, 0x051E0001, 0x051E0002,
};

s16 tunnel_mech_path[14] = {
    8, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40,
    0x48, 0x50, 0x58, 0x60, 5, -1,
};

s16 tunnel_mech_path_b_table[14] = {
    5, 0x60, 0x58, 0x50, 0x48, 0x40, 0x38, 0x30,
    0x28, 0x20, 0x18, 0x10, 8, -1,
};

s16 tunnel_mech_path_c_table[16] = {
    0x101, 0x103, 0x105, 0x107, 0x109, 0x111, 0x119, 0x121,
    0x129, 0x131, 0x139, 0x141, 0x149, 0x14B, 0x150, -1,
};

struct TunnelMechM2BossScripts {
    s16 intro[8];
    s16 dispatch[6];
    s16 near_check[8];
    s16 approach[24];
    s16 fire_check[6];
    s16 aim[10];
    s16 aim_wait[12];
    s16 advance[10];
    s16 advance_wait[16];
    s16 fall_back[10];
    s16 retreat_wait[16];
    s16 fire_burst[8];
    s16 fire_loop[12];
    s16 halt[8];
    s16 halt_loop[4];
    s16 pause[10];
    s16 recheck[6];
    s16 *table[17];
    s16 *D_80117310;
} tunnel_mech_m2_boss_scripts = {
    /* intro */ {
        TUNNEL_MECH_M2_BOSS_READ_SPEED, 4,
        TUNNEL_MECH_M2_BOSS_SET_NEXT_STATE, TUNNEL_MECH_M2_BOSS_STATE_ADVANCE,
        SET_COUNTER(128),
        JUMP(TUNNEL_MECH_M2_BOSS_PAUSE),
    },
    /* dispatch */ {
        JUMP_IF_STATE(TUNNEL_MECH_M2_BOSS_STATE_HALT, TUNNEL_MECH_M2_BOSS_HALT),
        JUMP(TUNNEL_MECH_M2_BOSS_NEAR_CHECK),
    },
    /* near_check */ {
        TUNNEL_MECH_M2_BOSS_READ_SPEED, 0,
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_WITHIN, 1600, TUNNEL_MECH_M2_BOSS_FIRE_CHECK,
        JUMP(TUNNEL_MECH_M2_BOSS_APPROACH),
    },
    /* approach */ {
        TUNNEL_MECH_M2_BOSS_READ_SPEED, 0,
        JUMP_RANDOM(2048, TUNNEL_MECH_M2_BOSS_AIM),
        TUNNEL_MECH_M2_BOSS_JUMP_IF_ABOVE_Z, TUNNEL_MECH_M2_BOSS_FALL_BACK,
        TUNNEL_MECH_M2_BOSS_JUMP_IF_BELOW_Z, TUNNEL_MECH_M2_BOSS_ADVANCE,
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_WITHIN, 1800, TUNNEL_MECH_M2_BOSS_FALL_BACK,
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_FAR, 2500, TUNNEL_MECH_M2_BOSS_ADVANCE,
        JUMP_RANDOM(768, TUNNEL_MECH_M2_BOSS_FALL_BACK),
        JUMP_RANDOM(768, TUNNEL_MECH_M2_BOSS_ADVANCE),
        JUMP(TUNNEL_MECH_M2_BOSS_AIM),
    },
    /* fire_check */ {
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_WITHIN, 1600, TUNNEL_MECH_M2_BOSS_FIRE_BURST,
        JUMP(TUNNEL_MECH_M2_BOSS_FALL_BACK),
    },
    /* aim */ {
        TUNNEL_MECH_M2_BOSS_READ_SPEED, 0,
        TUNNEL_MECH_M2_BOSS_SET_NEXT_STATE, TUNNEL_MECH_M2_BOSS_STATE_AIM,
        SET_COUNTER_RANDOM(128, 128),
        JUMP(TUNNEL_MECH_M2_BOSS_AIM_WAIT),
    },
    /* aim_wait */ {
        WAIT(1),
        JUMP_IF_STATE(TUNNEL_MECH_M2_BOSS_STATE_HALT, TUNNEL_MECH_M2_BOSS_HALT),
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_WITHIN, 1600, TUNNEL_MECH_M2_BOSS_RECHECK,
        LOOP(TUNNEL_MECH_M2_BOSS_AIM_WAIT),
        JUMP(TUNNEL_MECH_M2_BOSS_RECHECK),
    },
    /* advance */ {
        TUNNEL_MECH_M2_BOSS_READ_SPEED, 4,
        TUNNEL_MECH_M2_BOSS_SET_NEXT_STATE, TUNNEL_MECH_M2_BOSS_STATE_ADVANCE,
        SET_COUNTER_RANDOM(128, 164),
        JUMP(TUNNEL_MECH_M2_BOSS_ADVANCE_WAIT),
    },
    /* advance_wait */ {
        WAIT(1),
        JUMP_IF_STATE(TUNNEL_MECH_M2_BOSS_STATE_HALT, TUNNEL_MECH_M2_BOSS_HALT),
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_WITHIN, 1600, TUNNEL_MECH_M2_BOSS_RECHECK,
        LOOP(TUNNEL_MECH_M2_BOSS_ADVANCE_WAIT),
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_FAR, 2500, TUNNEL_MECH_M2_BOSS_RECHECK,
        JUMP(TUNNEL_MECH_M2_BOSS_RECHECK),
    },
    /* fall_back */ {
        TUNNEL_MECH_M2_BOSS_READ_SPEED, -4,
        TUNNEL_MECH_M2_BOSS_SET_NEXT_STATE, TUNNEL_MECH_M2_BOSS_STATE_FALL_BACK,
        SET_COUNTER_RANDOM(128, 164),
        JUMP(TUNNEL_MECH_M2_BOSS_RETREAT_WAIT),
    },
    /* retreat_wait */ {
        WAIT(1),
        JUMP_IF_STATE(TUNNEL_MECH_M2_BOSS_STATE_HALT, TUNNEL_MECH_M2_BOSS_HALT),
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_WITHIN, 1600, TUNNEL_MECH_M2_BOSS_RECHECK,
        LOOP(TUNNEL_MECH_M2_BOSS_RETREAT_WAIT),
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_WITHIN, 1800, TUNNEL_MECH_M2_BOSS_RECHECK,
        JUMP(TUNNEL_MECH_M2_BOSS_RECHECK),
    },
    /* fire_burst */ {
        TUNNEL_MECH_M2_BOSS_READ_SPEED, 0,
        TUNNEL_MECH_M2_BOSS_SET_NEXT_STATE, TUNNEL_MECH_M2_BOSS_STATE_FIRE,
        SET_COUNTER(2),
        JUMP(TUNNEL_MECH_M2_BOSS_FIRE_LOOP),
    },
    /* fire_loop */ {
        WAIT(1),
        JUMP_IF_STATE(TUNNEL_MECH_M2_BOSS_STATE_HALT, TUNNEL_MECH_M2_BOSS_HALT),
        LOOP(TUNNEL_MECH_M2_BOSS_FIRE_LOOP),
        TUNNEL_MECH_M2_BOSS_BRANCH_IF_WITHIN, 1600, TUNNEL_MECH_M2_BOSS_FIRE_BURST,
        JUMP(TUNNEL_MECH_M2_BOSS_RECHECK),
    },
    /* halt */ {
        TUNNEL_MECH_M2_BOSS_READ_SPEED, 0,
        TUNNEL_MECH_M2_BOSS_SET_NEXT_STATE, TUNNEL_MECH_M2_BOSS_STATE_HALT,
        SET_COUNTER(2),
        JUMP(TUNNEL_MECH_M2_BOSS_HALT_LOOP),
    },
    /* halt_loop */ {
        WAIT(1),
        JUMP(TUNNEL_MECH_M2_BOSS_HALT_LOOP),
    },
    /* pause */ {
        WAIT(1),
        JUMP_IF_STATE(TUNNEL_MECH_M2_BOSS_STATE_HALT, TUNNEL_MECH_M2_BOSS_HALT),
        LOOP(TUNNEL_MECH_M2_BOSS_PAUSE),
        JUMP(TUNNEL_MECH_M2_BOSS_RECHECK),
    },
    /* recheck */ {
        WAIT(1),
        TUNNEL_MECH_M2_BOSS_READ_SPEED, 0,
        JUMP(TUNNEL_MECH_M2_BOSS_DISPATCH),
    },
    /* table */ {
        tunnel_mech_m2_boss_scripts.intro, tunnel_mech_m2_boss_scripts.dispatch, tunnel_mech_m2_boss_scripts.near_check, tunnel_mech_m2_boss_scripts.approach, tunnel_mech_m2_boss_scripts.fire_check, tunnel_mech_m2_boss_scripts.aim,
        tunnel_mech_m2_boss_scripts.aim_wait, tunnel_mech_m2_boss_scripts.advance, tunnel_mech_m2_boss_scripts.advance_wait, tunnel_mech_m2_boss_scripts.fall_back, tunnel_mech_m2_boss_scripts.retreat_wait, tunnel_mech_m2_boss_scripts.fire_burst,
        tunnel_mech_m2_boss_scripts.fire_loop, tunnel_mech_m2_boss_scripts.halt, tunnel_mech_m2_boss_scripts.halt_loop, tunnel_mech_m2_boss_scripts.pause, tunnel_mech_m2_boss_scripts.recheck,
    },
    /* D_80117310 */ tunnel_mech_m2_boss_scripts.intro,
};

ScriptCallEntry D_80117314[8] = {
    {NULL, 0},
    {script_read_speed, 0},
    {script_op_set_next_state, 0},
    {script_read_u16_field, 0},
    {script_branch_if_within, 0},
    {script_branch_if_far, 0},
    {script_jump_if_above_z, 0},
    {script_jump_if_below_z, 0},
};

void (*obj_state_step_table[2])(Object *, ObjHandler *) = {
    tunnel_mech_damage_update, obj_run_stored_update,
};

#include "../stage/data/fade_red_fx_template.c"

#include "../stage/data/fx_owner_template_a.c"

s32 D_801173BC[3] = {
    -1, -1, -1,
};

ScanEntry enemy_oct_scan_entry = {{(s32)night_vision_init, 0}, D_801173BC, 0, 0, 0};

s32 enemy_ctl2_scan_out[3] = {
    -1, -1, -1,
};

ScanEntry enemy_ctl2_scan_entry = {{0, (s32)cam_zone_spawn}, enemy_ctl2_scan_out, 0, 0, 0};

RangeBox cam_zone_boxes[5] = {
    {0x3C28, 0x3D54, -0x12C0, -0x1158, -0x28A0, -0x2454},
    {0x3D54, 0x3E80, -0x12C0, -0x1158, -0x28A0, -0x2454},
    {0x1B58, 0x21FC, -0x2260, -0x20D0, -0x640, 0xC8},
    {0x1B58, 0x21FC, -0x20D0, -0x1F40, -0x640, 0xC8},
    {0x4268, 0x4D38, -0xA8C, 0, -0x6AB4, -0x6094},
};

s16 cam_zone_night_table[16] = {
    0, 1, 0, 0, 1, 0, 1, 0,
    2, 3, 1, 0, 3, 2, 0, 0,
};

s32 cam_zone_shade_rec_ids[8] = {
    0x70, 0x71, 0x72, 0x83, 0x91, 11,
    0x49, -1,
};

SoundSegmentList cam_zone_sound_owner_a = {4, {{{-0x168, -0x25C8, -0x5F0}, 0, {-0x288, -0x25C8, -0x4F8}, 0}, {{-0x168, -0x25C8, -0x5F0}, 0, {-0x288, -0x25C8, -0x4F8}, 0}, {{-0x7F8, -0x2898, -0x1A40}, 0, {-0x7F8, -0x2898, -0x13EC}, 0}, {{-0x7F8, -0x25C8, -0x13EC}, 0, {-0x7F8, -0x25C8, -0x654}, 0}}};

SoundSegmentList cam_zone_sound_owner_b = {10, {{{0x102C, -0x2898, -0x17AC}, 0, {0x6CC, -0x2898, -0xE4C}, 0}, {{0x6EA, -0x2898, -0xE4C}, 0, {-0x168, -0x25C8, -0x5F0}, 0}, {{-0x7F8, -0x2898, -0x13EC}, 0, {-0x7F8, -0x25C8, -0x13EC}, 0}, {{-0x7E0, -0x2508, -0x528}, 0, {-0x720, -0x2508, -0x330}, 0}, {{-0x720, -0x2508, -0x330}, 0, {-0x450, -0x2508, -0x60}, 0}, {{-0x450, -0x2508, -0x60}, 0, {-0x390, -0x2508, 0}, 0}, {{-0x390, -0x2508, 0}, 0, {0x1C20, -0x2508, 0}, 0}, {{0x1C20, -0x2508, 0}, 0, {0x1C20, -0x2508, 0x1C20}, 0}, {{-0x768, -0x25C8, -0x18}, 0, {-0x9B4, -0x25C8, 0x234}, 0}, {{0x588E, -0x168, -0x655E}, 0, {0x36B0, -0x168, -0x655E}, 0}}};

SoundSegmentList cam_zone_sound_owner_c = {1, {{{0x588E, -0x168, -0x655E}, 0, {0x36B0, -0x168, -0x655E}, 0}}};

PathPoint cam_zone_path[29] = {
    {0x7F0, -0x288C, -0xF78, 0},
    {-0x1C0, -0x28C8, -0x18D4, 0},
    {-0x800, -0x288C, -0x1938, 0},
    {-0x7EA, -0x2580, -0x5B6, 0},
    {-0x336, -0x2508, 0x26, 0},
    {0x1B4E, -0x2508, 0x26, 0},
    {0x1E62, -0x2580, -0x24E, 0},
    {0x1E62, -0x1E00, -0x24E, 0},
    {0x1E62, -0x1680, -0x24E, 0},
    {0x2C56, -0x16BF, -0x1046, 0},
    {0x25B0, -0x16F8, -0x16A8, 0},
    {0x209A, -0x16F8, -0x1722, 0},
    {0x190A, -0x16BC, -0x1DFE, 0},
    {0x2BBE, -0x111E, -0x3096, 0},
    {0x323A, -0x1158, -0x2A62, 0},
    {0x37A2, -0x1158, -0x29E5, 0},
    {0x3B6E, -0x1158, -0x26BB, 0},
    {0x421E, -0x111C, -0x2650, 0},
    {0x421E, -0x10EE, -0x3568, 0},
    {0x3E5E, -0x1068, -0x38B8, 0},
    {0x3E26, -0x10E0, -0x4132, 0},
    {0x4400, -0x10E0, -0x4132, 0},
    {0x4400, -0x1068, -0x511D, 0},
    {0x482A, -0x1068, -0x525B, 0},
    {0x482A, -0x1068, -0x60B8, 0},
    {0x482A, -0xC80, -0x6338, 0},
    {0x482A, -0x898, -0x6338, 0},
    {0x482A, -0x4B0, -0x6338, 0},
    {0x482A, -0x168, -0x6338, 0},
};

s32 player_flag8_obj_ids[4] = {
    0x11, 0x40, 0x84, -1,
};

#include "../stage/data/d_8011876C.c"

#include "../stage/data/rcossin_tbl.c"

s16 video_mode_id = 0;

#include "../stage/data/debug_cam_speed_table.c"

#include "../stage/data/pause_prev_work_area.c"

#include "../stage/data/vblank_task_handle.c"

#include "../stage/data/atan_table.c"

#include "../stage/data/rand_seed_table.c"

u32 D_8011C428[5] = {0};

#include "../stage/data/inv_sqrt_table.c"

#include "../stage/data/tint_scale_r.c"

#include "../stage/data/lens_flare_table.c"

#include "../stage/data/font_bitmap.c"

#include "../stage/data/font_clut.c"

u32 D_8011D58C[2] = {
    0x00000000, 0x00000000,
};

#include "../stage/data/trail_offsets.c"

u32 D_8011DBAC = 0x00000000;

INCBIN(texture_image, "build/stage/assets/texture_image.bin");

#include "../stage/data/stage_image_width.c"

#include "../stage/data/stage_image_pixels.c"

#include "../stage/data/heap_top.c"

#include "../stage/data/grid_flagged_count.c"

