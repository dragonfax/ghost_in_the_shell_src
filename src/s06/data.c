/* s06 data 0x8011C4A8-0x8011EB34: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "s06_types.h"
#include "script.h"
#include "scripts.h"
#include "sounds.h"

extern void cam_transition_spawn();
extern void copter_update();
extern void enemy_burst_update();
extern void enemy_fire_rocket();
extern u8 file_TNK1_ch0_cb4[];
extern u8 file_TNK1_ch0_clt[];
extern u8 file_TNK1_ch0_vx1[];
extern u8 file_TNK1_tp0_clt[];
extern u8 file_TNK1_tp0_xs3[];
extern u8 file_bic3_ch0_cb4[];
extern u8 file_bic3_ch0_clt[];
extern u8 file_bic3_ch0_vx1[];
extern u8 file_bic3_tp0_clt[];
extern u8 file_bic3_tp0_xs3[];
extern u8 file_bic3_tp1_clt[];
extern u8 file_bic3_tp1_xs3[];
extern u8 file_bic3_tp2_clt[];
extern u8 file_bic3_tp2_xs3[];
extern u8 file_msgs_spr_clt[];
extern u8 file_msgs_spr_grc[];
extern u8 file_msgs_spr_so3[];
extern u8 file_ohel_ch0_cb4[];
extern u8 file_ohel_ch0_clt[];
extern u8 file_ohel_ch0_vx1[];
extern u8 file_ohel_tp0_clt[];
extern u8 file_ohel_tp0_xs3[];
extern u8 file_ohel_tp1_clt[];
extern u8 file_ohel_tp1_xs3[];
extern u8 file_tnk2_ch0_cb4[];
extern u8 file_tnk2_ch0_clt[];
extern u8 file_tnk2_ch0_vx1[];
extern u8 file_tnk2_tp0_clt[];
extern u8 file_tnk2_tp0_xs3[];
extern void flier_approach_update();
extern void flier_chase_step();
extern void fly_pursue_update();
extern void minicopter_spawn();
extern void mission_state_reset();
extern void model_store_pchr();
extern void motorcycle_fire_check();
extern void motorcycle_spawn();
extern void obj_decelerate_move();
extern void obj_face_target_update();
extern void obj_finish_step();
extern void obj_jump_if_player_near();
extern void obj_move_and_snap();
extern void obj_move_countdown();
extern void obj_move_sample_flow();
extern void obj_retarget();
extern void obj_script_jump_if_near();
extern void obj_script_read_mode();
extern void obj_script_read_state();
extern void obj_set_next_state();
extern void obj_spawn_flier();
extern void obj_speed_approach();
extern void obj_turn_bank();
extern void obj_turn_sound_update();
extern void obj_turn_step();
extern void road_barrier_with_traffic_cone_spawn();
extern void s06_helicopter_spawn();
extern void script_jump_if_near_player_in_view();
extern void script_jump_if_player_in_view();
extern void script_jump_table();
extern void script_op_jump_if_in_cell_corner();
extern void script_op_jump_if_near_target();
extern void script_op_jump_if_player_far();
extern void script_op_jump_if_player_near();
extern void script_op_jump_table_if_player_far();
extern void script_op_set_speed();
extern void script_op_set_unk_234();
extern void script_player_angle_branch();
extern void script_read_s32();
extern void script_read_speed();
extern void script_set_turn_mode();
extern void script_skip_op();
extern void script_step_op();
extern void semi_truck_mech_spawn();
extern void semi_truck_mech_stage_setup();
extern void stage_setup();
extern u8 str_b06_dat_fac[];
extern u8 str_b06_ene_fac[];
extern u8 str_b06_joy_bin[];
extern u8 str_bos6_ch0_clt[];
extern u8 str_bos6_ch0_vx1[];
extern u8 str_bos6_ch0cb4[];
extern u8 str_bos6_ch1_vx1[];
extern u8 str_bos6_ch1cb4[];
extern u8 str_bos6_ch2_vx1[];
extern u8 str_bos6_ch2cb4[];
extern u8 str_bos6_ch3_vx1[];
extern u8 str_bos6_tp0_clt[];
extern u8 str_bos6_tp0_xs3[];
extern u8 str_bos6_tp1_clt[];
extern u8 str_bos6_tp1_xs3[];
extern u8 str_bos6_tp2_clt[];
extern u8 str_bos6_tp2_xs3[];
extern u8 str_enemy_bic3_data[];
extern u8 str_enemy_bos6_data[];
extern u8 str_enemy_corn_data[];
extern u8 str_enemy_ctl6_data[];
extern u8 str_enemy_fap3_data[];
extern u8 str_enemy_msgs_data[];
extern u8 str_enemy_nk1_data[];
extern u8 str_enemy_nk2_data[];
extern u8 str_enemy_ohe2_data[];
extern u8 str_fap1_ch0_clt[];
extern u8 str_fap1_ch0_vx1[];
extern u8 str_fap1_ch0cb4[];
extern u8 str_fap1_tp0_clt[];
extern u8 str_fap1_tp0_xs3[];
extern u8 str_fap1_tp1_clt[];
extern u8 str_fap1_tp1_xs3[];
extern u8 str_ksb_apdea3[];
extern u8 str_ksb_cnf_bcf[];
extern u8 str_m06_dat_fac[];
extern u8 str_m23_cnf_bcf[];
extern u8 str_m23_joy_bin[];
extern u8 str_s06_boss[];
extern u8 str_s06_dat_fac[];
extern u8 str_s06_ene_fac[];
extern u8 str_s06_joy_bin[];
extern u8 str_s06_miss[];
extern u8 str_s06_stage[];
extern u8 str_way_apdea3[];
extern u8 str_way_cnf_bcf[];
extern u8 str_waycrnp_clt[];
extern u8 str_waycrnp_vx1[];
extern u8 str_waycrnt_clt[];
extern u8 str_waycrnt_xs3[];
extern void tank_spawn();
extern u8 D_8011C8A1[];
extern u8 D_8011C8A2[];
extern u8 D_8011C8A3[];
extern u8 d_80117788[];
extern u8 d_8011778C[];
extern u8 span_table_offset[];
extern s32 area;
extern ScanItem enemy_scan_list[];
extern AreaEntry d_80116CA0;
extern AreaEntry d_80116CC8;
extern ScanItem boss_scan_table[];
extern AreaEntry d_80116D08;
extern AreaEntry *area_entry_table[3];
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern u32 exec_path_buf[];
extern s32 motorcycle_asset[];
extern ModelBlockRef D_8011C65C[];
extern ModelBlockRef D_8011C684[];
extern ModelBlockRef D_8011C694[];
extern ModelBlockRange D_8011C6B4[];
extern ModelBlock D_8011C6CC;
extern u8 *D_8011C6F0[];
extern ScanEntry motorcycle_entry;
extern s16 motorcycle_anim_idle[];
extern s16 *motorcycle_data;
extern StateEntry D_8011C71C[];
extern s32 flier_asset[3];
extern ModelBlockRef D_8011C740[];
extern ModelBlockRef D_8011C758[];
extern ModelBlockRef D_8011C768[];
extern ModelBlock flier_model;
extern u8 *D_8011C79C[];
extern ScanEntry flier_entry;
extern s16 flier_script_ptr_anim_idle[];
extern s16 *flier_script_ptr;
extern StateEntry D_8011C7C8[2];
extern s32 helicopter_asset[];
extern ModelBlockRef d_801176C4[];
extern ModelBlockRef d_801176E4[];
extern ModelBlockRef d_801176FC[];
extern ModelBlock d_8011770C;
extern u8 *d_80117730[];
extern ScanEntry helicopter_entry;
extern s16 s06_helicopter_anim_idle[];
extern s16 *s06_helicopter_data[];
extern GunSetup shot_twin_desc;
extern FxRecordParams ripple_fx_params;
extern FxRecordParams fx_send_rec34_params_a;
extern FxRecordParams fx_send_rec34_params_b;
extern RecTemplate fx_send_template_a;
extern RecTemplate fx_send_template_b;
extern s16 helicopter_idle[];
extern s16 s06_helicopter_choose[];
extern s16 s06_helicopter_patrol[];
extern s16 s06_helicopter_patrol_wait[];
extern s16 s06_helicopter_turn_to_patrol[];
extern s16 s06_helicopter_turn[];
extern s16 s06_helicopter_attack[];
extern s16 s06_helicopter_attack_wait[];
extern s16 s06_helicopter_drift_hold[];
extern s16 s06_helicopter_turn_hold[];
extern s16 s06_helicopter_turn_wait[];
extern s16 s06_helicopter_turn_end[];
extern s16 *helicopter_script_table[];
extern s16 *helicopter_script_start;
extern ScriptCallEntry D_8011C9FC[];
extern StateEntry D_8011CA2C[];
extern s32 minicopter_asset[3];
extern ModelBlockRef D_8011CA58[];
extern ModelBlockRef D_8011CA78[];
extern ModelBlockRef D_8011CA90[];
extern ModelBlockRange D_8011CAA0[];
extern ModelBlock D_8011CAB0;
extern u8 *D_8011CAD4[];
extern ScanEntry minicopter_scan_entry;
extern s16 minicopter_script[4];
extern s16 *minicopter_data[];
extern s16 minicopter_cycle[];
extern s16 minicopter_decide[];
extern s16 minicopter_chase[];
extern s16 minicopter_chase_hold[];
extern s16 minicopter_pursue[];
extern s16 minicopter_pursue_hold[];
extern s16 minicopter_fire[];
extern s16 minicopter_fire_hold[];
extern s16 minicopter_restart[];
extern s16 *minicopter_script_ops[];
extern s16 *minicopter_script_start;
extern ScriptCallEntry minicopter_call_table[6];
extern StateEntry minicopter_states[4];
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
extern s32 road_barrier_asset[3];
extern ModelBlockRef D_8011CFD8[];
extern ModelBlockRef D_8011CFF0[];
extern ModelBlockRef D_8011D000[];
extern ModelBlockRange D_8011D010[];
extern ModelBlock D_8011D028;
extern ScanEntry road_barrier_scan_entry;
extern StateEntry road_barrier_states[1];
extern s16 road_barrier_script[4];
extern s16 *road_barrier_with_traffic_cone_data[];
extern s32 D_8011D078[];
extern ScanEntry ctl6_scan_entry;
extern s16 loop_sound_start_ids[];
extern s16 loop_sound_stop_ids[];
extern s32 stage_data_block[944];
extern s32 d_80117914[];
extern s32 msg_id_base;
extern u32 d_80117920[];
extern u32 d_80117934[];
extern u32 d_80117948[];
extern s32 msg_slot_ids[12];
extern u8 *msgs_stage_files[];
extern ScanEntry D_8011DFF4;
extern s32 semi_truck_mech_asset[3];
extern s32 interp_slot_a;
extern s32 interp_slot_b;
extern ModelBlockRef D_8011E020[];
extern ModelBlockRef D_8011E048[];
extern ModelBlockRef D_8011E068[];
extern ModelBlockRange D_8011E090[];
extern ModelBlockRange D_8011E0C0[];
extern s16 D_8011E108[];
extern ModelBlock semi_truck_mech_model_block;
extern u8 *semi_truck_mech_ptr_table_ids[];
extern ScanEntry semi_truck_mech_scan_entry;
extern ScriptCallEntry semi_truck_mech_call_table[2];
extern RecTemplate enemy_explode_fx_a;
extern RecTemplate enemy_explode_fx_b;
extern u32 D_8011E19C;
extern u32 D_8011E1A0[];
extern s32 ring128_head;
extern s16 D_8011E1B8[];
extern s16 D_8011E2B8[];
extern s16 D_8011E4B8[];
extern s16 D_8011E4BC[];
extern s16 D_8011E5AC[];
extern WalkState walk_state_table[];
extern s32 semi_truck_interp_a[7];
extern s32 semi_truck_interp_b[7];
extern GunSetup spin_fx_gun_setups[2];
extern u16 spin_fx_table[];
extern u32 part_hit_weights[];

s32 area = 15;

ScanItem enemy_scan_list[9] = {
    {&motorcycle_entry, str_enemy_bic3_data},
    {&flier_entry, str_enemy_nk1_data},
    {&helicopter_entry, str_enemy_ohe2_data},
    {&minicopter_scan_entry, str_enemy_fap3_data},
    {&tank_scan_entry, str_enemy_nk2_data},
    {&road_barrier_scan_entry, str_enemy_corn_data},
    {&D_8011DFF4, str_enemy_msgs_data},
    {&ctl6_scan_entry, str_enemy_ctl6_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116CA0 = {str_s06_stage, str_way_cnf_bcf, str_way_apdea3, str_s06_joy_bin, str_s06_dat_fac, str_s06_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 1, enemy_scan_list};

AreaEntry d_80116CC8 = {str_s06_miss, str_m23_cnf_bcf, NULL, str_m23_joy_bin, str_m06_dat_fac, NULL, {0x1000, 0x1000, 0x1000}, 0, 0, NULL};

ScanItem boss_scan_table[3] = {
    {&semi_truck_mech_scan_entry, str_enemy_bos6_data},
    {&D_8011DFF4, str_enemy_msgs_data},
    {(ScanEntry *)-1, NULL},
};

AreaEntry d_80116D08 = {str_s06_boss, str_ksb_cnf_bcf, str_ksb_apdea3, str_b06_joy_bin, str_b06_dat_fac, str_b06_ene_fac, {0x1000, 0x1000, 0x1000}, 0, 0, boss_scan_table};

#include "../stage/data/area_entry_table.c"

#include "../stage/data/debug_name_buf.c"

s32 motorcycle_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_8011C65C[5] = {
    {(s32)file_bic3_ch0_clt, 0, 0},
    {(s32)file_bic3_tp0_clt, 0, 0},
    {(s32)file_bic3_tp1_clt, 0, 0},
    {(s32)file_bic3_tp2_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C684[2] = {
    {(s32)file_bic3_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C694[4] = {
    {(s32)file_bic3_tp0_xs3, 1, 0},
    {(s32)file_bic3_tp1_xs3, 2, 0},
    {(s32)file_bic3_tp2_xs3, 3, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011C6B4[3] = {
    {0, 4, 0x1333, 0}, {7, 9, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlock D_8011C6CC = {(s32)D_8011C65C, (s32)D_8011C684, (s32)D_8011C694, 0, 0, 0, (s32)D_8011C6B4, 0, 0};

u8 *D_8011C6F0[2] = {
    file_bic3_ch0_cb4, NULL,
};

ScanEntry motorcycle_entry = {{0, (s32)motorcycle_spawn}, motorcycle_asset, (s32)&D_8011C6CC, (s32)D_8011C6F0, 0};

struct MotorcycleAnims {
    s16 idle[4];
    s16 *table;
} motorcycle_anims = {
    /* idle */ {
        STEP(20, 0),
        GOTO(MOTORCYCLE_ANIM_IDLE),
    },
    /* table */ motorcycle_anims.idle,
};

StateEntry D_8011C71C[3] = {
    {0, 0, 0},
    {(u32)enemy_fire_rocket, 0, 0},
    {(u32)motorcycle_fire_check, 0, 0},
};

s32 flier_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_8011C740[3] = {
    {(s32)file_TNK1_ch0_clt, 0, 0},
    {(s32)file_TNK1_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C758[2] = {
    {(s32)file_TNK1_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011C768[2] = {
    {(s32)file_TNK1_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlock flier_model = {(s32)D_8011C740, (s32)D_8011C758, (s32)D_8011C768, 0, 0, 0, 0, 0, 0};

u8 *D_8011C79C[2] = {
    file_TNK1_ch0_cb4, NULL,
};

ScanEntry flier_entry = {{0, (s32)obj_spawn_flier}, flier_asset, (s32)&flier_model, (s32)D_8011C79C, 0};

#include "../stage/data/flier_script_ptr_anims.c"

StateEntry D_8011C7C8[2] = {
    {(u32)enemy_burst_update, 0, 0},
    {(u32)flier_approach_update, 0, 0},
};

s32 helicopter_asset[3] = {
    -1, -1, -1,
};

#include "../stage/data/d_801176C4.c"

ScanEntry helicopter_entry = {{0, (s32)s06_helicopter_spawn}, helicopter_asset, (s32)&d_8011770C, (s32)d_80117730, 0};

struct S06HelicopterAnims {
    s16 idle[4];
    s16 *table[1];
} s06_helicopter_anims = {
    /* idle */ {
        STEP(1, 0),
        GOTO(S06_HELICOPTER_ANIM_IDLE),
    },
    /* table */ {
        s06_helicopter_anims.idle,
    },
};

#include "../stage/data/shot_twin_desc.c"

#include "../stage/data/fx_send_rec34_params_b.c"

struct HelicopterScriptTableStreams {
    s16 helicopter_idle[2];
    s16 s06_helicopter_choose[8];
    s16 s06_helicopter_patrol[10];
    s16 s06_helicopter_patrol_wait[10];
    s16 s06_helicopter_turn_to_patrol[8];
    s16 s06_helicopter_turn[8];
    s16 s06_helicopter_attack[10];
    s16 s06_helicopter_attack_wait[10];
    s16 s06_helicopter_drift_hold[8];
    s16 s06_helicopter_turn_hold[4];
    s16 s06_helicopter_turn_wait[6];
    s16 s06_helicopter_turn_end[4];
    s16 *table[12];
    s16 *helicopter_script_start;
} helicopter_script_table_streams = {
    /* helicopter_idle */ {
        JUMP(S06_HELICOPTER_CHOOSE),
    },
    /* s06_helicopter_choose */ {
        JUMP_IF_STATE(S06_HELICOPTER_STATE_TURN, S06_HELICOPTER_TURN),
        S06_HELICOPTER_JUMP_IF_PLAYER_NEAR, 3000, S06_HELICOPTER_ATTACK,
        JUMP(S06_HELICOPTER_PATROL),
    },
    /* s06_helicopter_patrol */ {
        S06_HELICOPTER_SET_TURN_MODE, 0,
        S06_HELICOPTER_SPEED_APPROACH, 17,
        S06_HELICOPTER_SET_NEXT_STATE, S06_HELICOPTER_STATE_FLY,
        SET_COUNTER(120),
        JUMP(S06_HELICOPTER_PATROL_WAIT),
    },
    /* s06_helicopter_patrol_wait */ {
        WAIT(1),
        JUMP_IF_STATE(S06_HELICOPTER_STATE_TURN, S06_HELICOPTER_TURN),
        LOOP(S06_HELICOPTER_PATROL_WAIT),
        JUMP(S06_HELICOPTER_ATTACK),
    },
    /* s06_helicopter_turn_to_patrol */ {
        S06_HELICOPTER_SET_TURN_MODE, 1,
        S06_HELICOPTER_SPEED_APPROACH, 8,
        S06_HELICOPTER_SET_NEXT_STATE, S06_HELICOPTER_STATE_FLY,
        JUMP(S06_HELICOPTER_TURN_HOLD),
    },
    /* s06_helicopter_turn */ {
        S06_HELICOPTER_SET_TURN_MODE, 1,
        S06_HELICOPTER_SPEED_APPROACH, 8,
        S06_HELICOPTER_SET_NEXT_STATE, S06_HELICOPTER_STATE_TURN,
        JUMP(S06_HELICOPTER_TURN_HOLD),
    },
    /* s06_helicopter_attack */ {
        S06_HELICOPTER_SET_TURN_MODE, 0,
        S06_HELICOPTER_SPEED_APPROACH, 11,
        S06_HELICOPTER_SET_NEXT_STATE, S06_HELICOPTER_STATE_FIRE,
        SET_COUNTER(60),
        JUMP(S06_HELICOPTER_ATTACK_WAIT),
    },
    /* s06_helicopter_attack_wait */ {
        WAIT(1),
        JUMP_IF_STATE(S06_HELICOPTER_STATE_TURN, S06_HELICOPTER_TURN),
        LOOP(S06_HELICOPTER_ATTACK_WAIT),
        JUMP(S06_HELICOPTER_PATROL),
    },
    /* s06_helicopter_drift_hold */ {
        S06_HELICOPTER_SET_TURN_MODE, 0,
        S06_HELICOPTER_SPEED_APPROACH, 8,
        S06_HELICOPTER_SET_NEXT_STATE, S06_HELICOPTER_STATE_FLOW,
        JUMP(S06_HELICOPTER_TURN_HOLD),
    },
    /* s06_helicopter_turn_hold */ {
        SET_COUNTER(120),
        JUMP(S06_HELICOPTER_TURN_WAIT),
    },
    /* s06_helicopter_turn_wait */ {
        WAIT(1),
        LOOP(S06_HELICOPTER_TURN_WAIT),
        JUMP(S06_HELICOPTER_TURN_END),
    },
    /* s06_helicopter_turn_end */ {
        WAIT(1),
        JUMP(HELICOPTER_IDLE),
    },
    /* table */ {
        helicopter_script_table_streams.helicopter_idle, helicopter_script_table_streams.s06_helicopter_choose, helicopter_script_table_streams.s06_helicopter_patrol, helicopter_script_table_streams.s06_helicopter_patrol_wait, helicopter_script_table_streams.s06_helicopter_turn_to_patrol, helicopter_script_table_streams.s06_helicopter_turn,
        helicopter_script_table_streams.s06_helicopter_attack, helicopter_script_table_streams.s06_helicopter_attack_wait, helicopter_script_table_streams.s06_helicopter_drift_hold, helicopter_script_table_streams.s06_helicopter_turn_hold, helicopter_script_table_streams.s06_helicopter_turn_wait, helicopter_script_table_streams.s06_helicopter_turn_end,
    },
    /* helicopter_script_start */ helicopter_script_table_streams.helicopter_idle,
};

ScriptCallEntry D_8011C9FC[6] = {
    {NULL, 0},
    {obj_speed_approach, 0},
    {obj_set_next_state, 0},
    {script_set_turn_mode, 0},
    {obj_jump_if_player_near, 0},
    {script_op_jump_table_if_player_far, 0},
};

StateEntry D_8011CA2C[4] = {
    {(u32)obj_move_and_snap, S06_HELICOPTER_ANIM_IDLE, 0},
    {(u32)obj_move_countdown, S06_HELICOPTER_ANIM_IDLE, 0},
    {(u32)obj_move_sample_flow, S06_HELICOPTER_ANIM_IDLE, 0},
    {(u32)obj_turn_bank, S06_HELICOPTER_ANIM_IDLE, 0},
};

s32 minicopter_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_8011CA58[4] = {
    {(s32)str_fap1_ch0_clt, 0, 0},
    {(s32)str_fap1_tp0_clt, 0, 0},
    {(s32)str_fap1_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011CA78[3] = {
    {(s32)str_fap1_tp0_xs3, 1, 0},
    {(s32)str_fap1_tp1_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011CA90[2] = {
    {(s32)str_fap1_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011CAA0[2] = {
    {0, 4, -0x400, 0}, {-1, 0, 0, 0},
};

ModelBlock D_8011CAB0 = {(s32)D_8011CA58, (s32)D_8011CA90, (s32)D_8011CA78, 0, 0, (s32)D_8011CAA0, 0, 0, 0};

u8 *D_8011CAD4[2] = {
    str_fap1_ch0cb4, NULL,
};

ScanEntry minicopter_scan_entry = {{0, (s32)minicopter_spawn}, minicopter_asset, (s32)&D_8011CAB0, (s32)D_8011CAD4, 0};

struct MinicopterAnims {
    s16 script[4];
    s16 *table[1];
} minicopter_anims = {
    /* script */ {
        STEP(1, 0),
        GOTO(MINICOPTER_SCRIPT),
    },
    /* table */ {
        minicopter_anims.script,
    },
};

struct MinicopterScripts {
    s16 cycle[2];
    s16 decide[8];
    s16 chase[10];
    s16 chase_hold[6];
    s16 pursue[10];
    s16 pursue_hold[4];
    s16 fire[10];
    s16 fire_hold[6];
    s16 restart[4];
    s16 *table[9];
    s16 *script_start;
} minicopter_scripts = {
    /* cycle */ {
        JUMP(MINICOPTER_DECIDE),
    },
    /* decide */ {
        MINICOPTER_STEP_OP, MINICOPTER_CHASE,
        MINICOPTER_JUMP_IF_NEAR, 1280, MINICOPTER_PURSUE,
        JUMP(MINICOPTER_CHASE),
    },
    /* chase */ {
        MINICOPTER_READ_MODE, 0,
        MINICOPTER_READ_SPEED, 8,
        MINICOPTER_READ_STATE, 0,
        SET_COUNTER(20),
        JUMP(MINICOPTER_CHASE_HOLD),
    },
    /* chase_hold */ {
        WAIT(1),
        LOOP(MINICOPTER_CHASE_HOLD),
        JUMP(MINICOPTER_RESTART),
    },
    /* pursue */ {
        MINICOPTER_READ_MODE, 0,
        MINICOPTER_READ_SPEED, 8,
        MINICOPTER_READ_STATE, 1,
        SET_COUNTER(120),
        JUMP(MINICOPTER_PURSUE_HOLD),
    },
    /* pursue_hold */ {
        WAIT(1),
        LOOP(MINICOPTER_PURSUE_HOLD),
    },
    /* fire */ {
        MINICOPTER_READ_MODE, 0,
        MINICOPTER_READ_SPEED, 8,
        MINICOPTER_READ_STATE, 2,
        SET_COUNTER(60),
        JUMP(MINICOPTER_FIRE_HOLD),
    },
    /* fire_hold */ {
        WAIT(1),
        LOOP(MINICOPTER_FIRE_HOLD),
        JUMP(MINICOPTER_RESTART),
    },
    /* restart */ {
        WAIT(1),
        JUMP(MINICOPTER_CYCLE),
    },
    /* table */ {
        minicopter_scripts.cycle, minicopter_scripts.decide, minicopter_scripts.chase, minicopter_scripts.chase_hold, minicopter_scripts.pursue, minicopter_scripts.pursue_hold,
        minicopter_scripts.fire, minicopter_scripts.fire_hold, minicopter_scripts.restart,
    },
    /* script_start */ minicopter_scripts.cycle,
};

ScriptCallEntry minicopter_call_table[6] = {
    {NULL, 0}, {script_read_speed, 0}, {obj_script_read_state, 0},
    {obj_script_read_mode, 0}, {obj_script_jump_if_near, 0}, {script_step_op, 0},
};

StateEntry minicopter_states[4] = {
    {(u32)flier_chase_step, MINICOPTER_SCRIPT, 0},
    {(u32)fly_pursue_update, MINICOPTER_SCRIPT, 0},
    {(u32)copter_update, MINICOPTER_SCRIPT, 0},
    {0, MINICOPTER_SCRIPT, 0},
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

s32 road_barrier_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef D_8011CFD8[3] = {
    {(s32)str_waycrnp_clt, 0, 0}, {(s32)str_waycrnt_clt, 0, 0}, {0, 0, 0},
};

ModelBlockRef D_8011CFF0[2] = {
    {(s32)str_waycrnt_xs3, 1, 0}, {0, 0, 0},
};

ModelBlockRef D_8011D000[2] = {
    {(s32)str_waycrnp_vx1, 0, 0}, {0, 0, 0},
};

ModelBlockRange D_8011D010[3] = {
    {1, 1, 0x1800, 0}, {2, 2, 0x1000, 0}, {-1, 0, 0, 0},
};

ModelBlock D_8011D028 = {(s32)D_8011CFD8, (s32)D_8011D000, (s32)D_8011CFF0, 0, 0, 0, (s32)D_8011D010, 0, 0};

ScanEntry road_barrier_scan_entry = {{0, (s32)road_barrier_with_traffic_cone_spawn}, road_barrier_asset, (s32)&D_8011D028, 0, 0};

StateEntry road_barrier_states[1] = {
    {0, 0, 0},
};

struct RoadBarrierAnims {
    s16 script[4];
    s16 *table[1];
} road_barrier_anims = {
    /* script */ {
        STEP(1, 1),
        GOTO(ROAD_BARRIER_SCRIPT),
    },
    /* table */ {
        road_barrier_anims.script,
    },
};

s32 D_8011D078[3] = {
    -1, -1, -1,
};

ScanEntry ctl6_scan_entry = {{(s32)stage_setup, (s32)cam_transition_spawn}, D_8011D078, 0, 0, 0};

s16 loop_sound_start_ids[8] = {
    0x6A, 0x7E, 0xDC, 0x110, 0x26C, 0xBF, 0x261, -1,
};

s16 loop_sound_stop_ids[6] = {
    0x64, 0xD0, 0xEF, 0x108, 0x1D0, -1,
};

s32 stage_data_block[944] = {
    8, 0x40C, 0x100, 0, 0x10000, 0,
    0x10001, 0x10002, 0x10003, 0x10004, 0x10005, 0x10006,
    0, 0x10007, 0x10008, 0x10009, 0x1000A, 0,
    0, 0x1000B, 0x1000C, 0x1000D, 0x2000E, 0x20010,
    0x20012, 0x10014, 0x10015, 0x10016, 0x10017, 0x10018,
    0x10019, 0x1001A, 0x1001B, 0x1001C, 0x1001D, 0,
    0, 0, 0, 0x1001E, 0x1001F, 0x10020,
    0x10021, 0, 0x10022, 0x10023, 0, 0,
    0, 0, 0, 0x10024, 0x10025, 0x10026,
    0x10027, 0x10028, 0, 0x10029, 0x1002A, 0x1002B,
    0, 0, 0, 0x1002C, 0x1002D, 0,
    0, 0x1002E, 0x1002F, 0x10030, 0x10031, 0x10032,
    0x10033, 0, 0, 0, 0x10034, 0x10035,
    0x10036, 0x10037, 0x10038, 0x10039, 0x1003A, 0x1003B,
    0x1003C, 0x1003D, 0, 0, 0, 0,
    0x1003E, 0, 0, 0, 0, 0,
    0, 0, 0x1003F, 0x10040, 0x10041, 0x10042,
    0x20043, 0, 0, 0x10045, 0x10046, 0,
    0, 0, 0, 0, 0x10047, 0x10048,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0x10049, 0, 0,
    0, 0, 0x1004A, 0x1004B, 0x1004C, 0,
    0, 0x1004D, 0x1004E, 0x1004F, 0x10050, 0x10051,
    0x10052, 0x10053, 0, 0x20054, 0x10056, 0x20057,
    0x10059, 0x1005A, 0x1005B, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0x1005C, 0x1005D, 0,
    0x2005E, 0x10060, 0x30061, 0x10064, 0x20065, 0x20067,
    0x20069, 0x2006B, 0x1006D, 0x1006E, 0x1006F, 0x10070,
    0x20071, 0x10073, 0x20074, 0x20076, 0x20078, 0x2007A,
    0, 0, 0x1007C, 0x1007D, 0x2007E, 0,
    0x20080, 0x20082, 0x20084, 0x20086, 0x20088, 0x2008A,
    0x2008C, 0, 0x1008E, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0x1008F, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0x20090, 0x20092, 0x20094,
    0x20096, 0x20098, 0x2009A, 0x2009C, 0, 0x1009E,
    0x1009F, 0x100A0, 0x100A1, 0x100A2, 0, 0,
    0x200A3, 0, 0, 0, 0, 0,
    0, 0x200A5, 0x100A7, 0x200A8, 0, 0x100AA,
    0, 0xAB, 0x36001E0, (s32)0xFCA001E0, 0x2E8FDA8, (s32)0xFC58FEE0,
    0x3A80108, (s32)0xFD180240, 0x295FCF0, (s32)0xFC5EFF93, 0x3B50050, (s32)0xFD7E02F3,
    0x295FD50, (s32)0xFC5EFFF3, 0x3B500B0, (s32)0xFD7E0353, 0x2E8FDA8, (s32)0xFC58FEE0,
    0x3A80108, (s32)0xFD180240, 0x360FE20, (s32)0xFCA0FE20, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x36001E0, (s32)0xFCA001E0, 0x3A8FEE0, (s32)0xFD18FDA8,
    0x2E80240, (s32)0xFC580108, 0x3A2FF93, (s32)0xFD6BFCF0, 0x28202F3, (s32)0xFC4B0050,
    0x3A2FFF3, (s32)0xFD6BFD50, 0x2820353, (s32)0xFC4B00B0, 0x3A8FEE0, (s32)0xFD18FDA8,
    0x2E80240, (s32)0xFC580108, 0x360FE20, (s32)0xFCA0FE20, 0x5A00180, (s32)0xFA600180,
    0x5A0FE80, (s32)0xFA60FE80, 0x5A00180, (s32)0xFA600180, 0x5A0FE80, (s32)0xFA60FE80,
    0x5A00180, (s32)0xFA600180, 0x5A0FE80, (s32)0xFA60FE80, 0x300180, (s32)0xFA600180,
    0x30FE80, (s32)0xFA60FE80, 0x5A00180, (s32)0xFFD00180, 0x5A0FE80, (s32)0xFFD0FE80,
    0x5A00180, (s32)0xFFD00180, 0x5A0FE80, 0x120FE80, 0x300180, (s32)0xFA600180,
    (s32)0xFEE0FE80, (s32)0xFA60FE80, 0x5A00180, 0x1200180, 0x5A0FE80, 0x120FE80,
    (s32)0xFEE00180, (s32)0xFA600180, (s32)0xFEE0FE80, (s32)0xFA60FE80, 0x2400180, (s32)0xFDC00180,
    0x240FE80, (s32)0xFDC0FE80, 0x2400180, (s32)0xFDC00180, 0x240FE80, (s32)0xFDC0FE80,
    0x2A00180, (s32)0xFE200180, 0x1E0FDC0, (s32)0xFDC0FF40, 0x3000060, (s32)0xFEE001E0,
    0x120FD00, (s32)0xFDC00000, 0x2A0FF40, (s32)0xFF400240, 0xC0FD30, (s32)0xFD600030,
    0x2A0FF40, (s32)0xFF400240, 0xC0FD30, (s32)0xFD600030, 0x2A0FF40, (s32)0xFF400240,
    0xC0FD30, (s32)0xFD600030, 0x1E00180, (s32)0xFD600180, 0x240FF40, (s32)0xFE20FDC0,
    0x12001E0, (s32)0xFD000060, 0x2400000, (s32)0xFEE0FD00, 0xC00240, (s32)0xFD60FF40,
    0x2A00030, (s32)0xFF40FD30, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x36001E0, (s32)0xFCA001E0, 0x3A8FEE0, (s32)0xFD18FDA8, 0x2E80240, (s32)0xFC580108,
    0x3A2FF93, (s32)0xFD6BFCF0, 0x22202F3, (s32)0xFBEB0050, 0x3900060, (s32)0xFDF0FCA0,
    0x1B00360, (s32)0xFC10FFA0, 0x39000F0, (s32)0xFEE0FC40, 0xF00390, (s32)0xFC40FEE0,
    0x39000F0, (s32)0xFEE0FC40, 0xF00390, (s32)0xFC40FEE0, 0x39000F0, (s32)0xFEE0FC40,
    0x2E80258, (s32)0xFC580120, 0x360FE20, (s32)0xFCA0FE20, 0x2950310, (s32)0xFC5E006D,
    0x3A8FEF8, (s32)0xFD18FDC0, 0x2100360, (s32)0xFC70FFA0, 0x415FFB0, (s32)0xFDDEFD0D,
    0x12003C0, (s32)0xFC70FF10, 0x3F00060, (s32)0xFE50FCA0, 0x1200180, (s32)0xFCA00180,
    0x120FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x120FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x300FFD0, (s32)0xFFA002D0,
    0x115FD50, (s32)0xFADEFFF3, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x1800000, (s32)0xFAC00000, 0x180FC40, (s32)0xFAC0FC40, 0x1800300, (s32)0xFAC00300,
    0x1800000, (s32)0xFAC00000, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600000, (s32)0xFCA00000,
    0x360FD00, (s32)0xFCA0FD00, 0x3600300, (s32)0xFCA00300, 0x3600000, (s32)0xFCA00000,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x5A00180, (s32)0xFA600180,
    0x5A0FE80, (s32)0xFA60FE80, 0x5A00180, (s32)0xFA600180, 0x5A0FE80, (s32)0xFA60FE80,
    0x5A00180, (s32)0xFA600180, 0x360FE80, (s32)0xFCA0FE80, 0x5A00180, (s32)0xFA600180,
    0x5A0FE80, (s32)0xFA60FE80, 0x210FEE0, (s32)0xFE2B0120, (s32)0xFE7FFB4E, (s32)0xFC40FF34,
    0x36003C0, (s32)0xFEE003C0, 0x210FEE0, (s32)0xFE2B0120, 0x29FFEAE, 0x600294,
    -0x2D2, (s32)0xFDC00114, 0x1EFFEDF, (s32)0xFE090120, 0x120FBE0, (s32)0xFCA0FBE0,
    0x41F00EE, 0x1E004D4, 0x1EFFEDF, (s32)0xFE090120, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x1200180, (s32)0xFA600180, 0x120FE80, (s32)0xFA60FE80,
    0x1200180, (s32)0xFA600180, 0x120FE80, (s32)0xFA60FE80, 0x57CFB43, 0xB60009,
    0x1BCF603, (s32)0xFB20F8E0, 0x51CFFC3, (s32)0xFE8002A0, 0x300FD00, (s32)0xFC40FD00,
    0x3600000, (s32)0xFCA00000, 0x360FD00, (s32)0xFCA0FD00, 0x3600300, (s32)0xFCA00300,
    0x3600000, (s32)0xFCA00000, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    (s32)0xFFA0FEE0, (s32)0xF8E0FEE0, (s32)0xFFA0F8E0, (s32)0xF8E0F8E0, (s32)0xFE8B0392, (s32)0xF85500EF,
    (s32)0xFFA0FEE0, (s32)0xF8E0FEE0, (s32)0xFC4A0729, (s32)0xF7840263, (s32)0xFE8B0392, (s32)0xF85500EF,
    0x30002A0, (s32)0xFC4002A0, 0x300FD00, (s32)0xFC40FD00, 0x32BFEAF, (s32)0xFCF50152,
    0x9CFAE3, (s32)0xFBD6FFA9, 0x4200360, (s32)0xFD600360, 0x32BFEAF, (s32)0xFCF50152,
    0x30B0152, (s32)0xFCD5FEAF, 0x42AFFA9, (s32)0xFF64FAE3, 0x2A00360, (s32)0xFBE00360,
    0x30B0152, (s32)0xFCD5FEAF, 0x32BFEAF, (s32)0xFCF50152, 0x2A0FCA0, (s32)0xFBE0FCA0,
    0x3FC0023, (s32)0xFF3604E9, 0x32BFEAF, (s32)0xFCF50152, 0x30B0152, (s32)0xFCD5FEAF,
    0x420FCA0, (s32)0xFD60FCA0, 0xCA04E9, (s32)0xFC040023, 0x30B0152, (s32)0xFCD5FEAF,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x33CFEA3, (s32)0xFE760369,
    0x15CFC03, (s32)0xFC9600C9, 0x18A0369, (s32)0xFCC4FEA3, 0x36A00C9, (s32)0xFEA4FC03,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x3600000, (s32)0xFCA00000,
    0x360FD00, (s32)0xFCA0FD00, 0x3600300, (s32)0xFCA00300, 0x3600000, (s32)0xFCA00000,
    0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80, 0x32BFEAF, (s32)0xFCF50152,
    0x9CFAE3, (s32)0xFBD6FFA9, 0x4200360, (s32)0xFD600360, 0x32BFEAF, (s32)0xFCF50152,
    0x30B0152, (s32)0xFCD5FEAF, 0x42AFFA9, (s32)0xFF64FAE3, 0x2A00360, (s32)0xFBE00360,
    0x30B0152, (s32)0xFCD5FEAF, 0x32C0150, (s32)0xFCF6FEAD, 0x420FCA0, (s32)0xFD60FCA0,
    0x6A0549, (s32)0xFBA40083, 0x32C0150, (s32)0xFCF6FEAD, 0x30AFEAD, (s32)0xFCD40150,
    0x2A0FCA0, (s32)0xFBE0FCA0, 0x45C0083, (s32)0xFF960549, 0x30AFEAD, (s32)0xFCD40150,
    0x33CFF03, (s32)0xFE7603C9, 0x15CFC63, (s32)0xFC960129, 0x18A03C9, (s32)0xFCC4FF03,
    0x36A0129, (s32)0xFEA4FC63, 0x3600000, (s32)0xFCA00000, 0x360FD00, (s32)0xFCA0FD00,
    0x3600300, (s32)0xFCA00300, 0x3600000, (s32)0xFCA00000, 0x3600000, (s32)0xFCA00000,
    0x3CBFDF2, (s32)0xFD95FB4F, 0x3600300, (s32)0xFCA00300, 0x3600000, (s32)0xFCA00000,
    0x2AA02A9, (s32)0xFDE4FDE3, 0x48A0009, (s32)0xFFC4FB43, 0x18B0452, (s32)0xFB5501AF,
    0x2AA02A9, (s32)0xFDE4FDE3, 0x30B0152, (s32)0xFCD5FEAF, 0x420FCA0, (s32)0xFD60FCA0,
    0xCA04E9, (s32)0xFC040023, 0x30B0152, (s32)0xFCD5FEAF, 0x3600000, (s32)0xFCA00000,
    0x360FD00, (s32)0xFCA0FD00, 0x3600300, (s32)0xFCA00300, 0x3600000, (s32)0xFCA00000,
    0x3600000, (s32)0xFCA00000, 0x360FD00, (s32)0xFCA0FD00, 0x3600300, (s32)0xFCA00300,
    0x3600000, (s32)0xFCA00000, 0x3600000, (s32)0xFCA00000, 0x360FD00, (s32)0xFCA0FD00,
    0x3600300, (s32)0xFCA00300, 0x3600000, (s32)0xFCA00000, 0x3600000, (s32)0xFCA00000,
    0x360FD00, (s32)0xFCA0FD00, 0x3600300, (s32)0xFCA00300, 0x3600000, (s32)0xFCA00000,
    0xC00390, (s32)0xFD600090, 0x3D2FFC3, (s32)0xFD9BFD20, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x32BFEAF, (s32)0xFCF50152, 0x9CFAE3, (s32)0xFBD6FFA9,
    0x4200360, (s32)0xFD600360, 0x32BFEAF, (s32)0xFCF50152, 0x30B0152, (s32)0xFCD5FEAF,
    0x42AFFA9, (s32)0xFF64FAE3, 0x2A00360, (s32)0xFBE00360, 0x30B0152, (s32)0xFCD5FEAF,
    0x32BFEAF, (s32)0xFCF50152, 0x2A0FCA0, (s32)0xFBE0FCA0, 0x3FC0023, (s32)0xFF3604E9,
    0x32BFEAF, (s32)0xFCF50152, 0x30B0152, (s32)0xFCD5FEAF, 0x420FCA0, (s32)0xFD60FCA0,
    0xCA04E9, (s32)0xFC040023, 0x30B0152, (s32)0xFCD5FEAF, 0x32BFEAF, (s32)0xFCF50152,
    0x9CFAE3, (s32)0xFBD6FFA9, 0x4200360, (s32)0xFD600360, 0x32BFEAF, (s32)0xFCF50152,
    0x27CFD83, (s32)0xFDB60249, 0x9CFAE3, (s32)0xFBD6FFA9, 0x45C0023, (s32)0xFF9604E9,
    0x27CFD83, (s32)0xFDB60249, 0x32BFEAF, (s32)0xFCF50152, 0x2A0FCA0, (s32)0xFBE0FCA0,
    0x3FC0023, (s32)0xFF3604E9, 0x32BFEAF, (s32)0xFCF50152, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x33CFEA3, (s32)0xFE760369, 0x15CFC03, (s32)0xFC9600C9,
    0x18A0369, (s32)0xFCC4FEA3, 0x36A00C9, (s32)0xFEA4FC03, 0x3600180, (s32)0xFCA00180,
    0x360FE80, (s32)0xFCA0FE80, 0x3600180, (s32)0xFCA00180, 0x360FE80, (s32)0xFCA0FE80,
    0x3600000, (s32)0xFCA00000, 0x360FD00, (s32)0xFCA0FD00, 0x3600300, (s32)0xFCA00300,
    0x3600000, (s32)0xFCA00000, 0x3600000, (s32)0xFCA00000, 0x360FD00, (s32)0xFCA0FD00,
    0x3600300, (s32)0xFCA00300, 0x3600000, (s32)0xFCA00000, 0x36001E0, (s32)0xFCA001E0,
    0x27CFD0A, (s32)0xFC40FFA0, 0x33CFE8A, (s32)0xFD000120, 0x21CFBEA, (s32)0xFBE0FE80,
    0x45C012A, (s32)0xFE2003C0, 0x33CFE8A, (s32)0xFD000120, 0x39B0069, (s32)0xFD600300,
    0x300FE80, (s32)0xFC40FE80,
};

#include "../stage/data/d_80117914.c"

#include "../stage/data/msg_id_base.c"

u8 *msgs_stage_files[3] = {
    file_msgs_spr_clt, file_msgs_spr_grc, file_msgs_spr_so3,
};

ScanEntry D_8011DFF4 = {{(s32)mission_state_reset, 0}, d_80117914, 0, 0, (s32)msgs_stage_files};

s32 semi_truck_mech_asset[3] = {
    -1, -1, -1,
};

s32 interp_slot_a = -1;

s32 interp_slot_b = -1;

ModelBlockRef D_8011E020[5] = {
    {(s32)str_bos6_ch0_clt, 0, 0},
    {(s32)str_bos6_tp0_clt, 0, 0},
    {(s32)str_bos6_tp1_clt, 0, 0},
    {(s32)str_bos6_tp2_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011E048[4] = {
    {(s32)str_bos6_tp1_xs3, 2, 0},
    {(s32)str_bos6_tp0_xs3, 1, 0},
    {(s32)str_bos6_tp2_xs3, 3, 0},
    {0, 0, 0},
};

ModelBlockRef D_8011E068[5] = {
    {(s32)str_bos6_ch0_vx1, 0, 1},
    {(s32)str_bos6_ch1_vx1, 1, 0},
    {(s32)str_bos6_ch2_vx1, 1, 0},
    {(s32)str_bos6_ch3_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlockRange D_8011E090[6] = {
    {0x1A0, 0x1A3, 0x1000, 0}, {0x1A9, 0x1A9, 0x2000, 0}, {0x1B0, 0x1BC, 0x2000, 0}, {0x1C0, 0x1C2, 0x2000, 0},
    {-1, -1, -1, 0}, {-1, -1, -1, 0},
};

ModelBlockRange D_8011E0C0[9] = {
    {1, 1, 0x400, 0}, {3, 3, 0x400, 0}, {5, 5, 0x400, 0}, {2, 2, 0, 0},
    {6, 9, 0x400, 0}, {6, 6, 0, 0}, {10, 12, 0x800, 0}, {0x1E0, 0x1E0, 0x40, 0},
    {-1, -1, -1, 0},
};

s16 D_8011E108[4] = {
    1, 0x100, 0x14F, 0,
};

ModelBlock semi_truck_mech_model_block = {(s32)D_8011E020, (s32)D_8011E068, (s32)D_8011E048, 0, (s32)D_8011E090, (s32)D_8011E0C0, 0, (s32)D_8011E108, 0};

u8 *semi_truck_mech_ptr_table_ids[4] = {
    str_bos6_ch0cb4, str_bos6_ch1cb4, str_bos6_ch2cb4, NULL,
};

ScanEntry semi_truck_mech_scan_entry = {{(s32)semi_truck_mech_stage_setup, (s32)semi_truck_mech_spawn}, semi_truck_mech_asset, (s32)&semi_truck_mech_model_block, (s32)semi_truck_mech_ptr_table_ids, 0};

ScriptCallEntry semi_truck_mech_call_table[2] = {
    {NULL, 0}, {script_skip_op, 0},
};

RecTemplate enemy_explode_fx_a = {3, 0xFF, 0xFF, 0xFF, 0, 0x14, 0x80000, 0x60000, -0x100, 0x40000};

RecTemplate enemy_explode_fx_b = {3, 0xFF, 0x40, 0, 0, 0x10, 0x100000, 0x80000, -0x100, 0x80000};

u32 D_8011E19C = 0x0001FFFD;

u32 D_8011E1A0[5] = {
    0x0001FFFF, 0x0001FFFD, (u32)&D_8011E19C, (u32)D_8011E1A0, (u32)&D_8011E19C,
};

s32 ring128_head = 0;

s16 D_8011E1B8[128] = {
    6, 0, 12, 2, 0x12, 4, 0x18, 6,
    0x1F, 10, 0x25, 14, 0x2B, 0x13, 0x30, 0x18,
    0x36, 0x1E, 0x3C, 0x25, 0x41, 0x2C, 0x47, 0x34,
    0x4C, 0x3C, 0x51, 0x45, 0x55, 0x4F, 0x5A, 0x59,
    0x5E, 0x63, 0x62, 0x6E, 0x66, 0x7A, 0x6A, 0x85,
    0x6D, 0x92, 0x70, 0x9E, 0x73, 0xAB, 0x76, 0xB8,
    0x78, 0xC5, 0x7A, 0xD3, 0x7C, 0xE0, 0x7D, 0xEE,
    0x7E, 0xFC, 0x7F, 0x10A, 0x7F, 0x118, 0x80, 0x127,
    0x7F, 0x135, 0x7F, 0x143, 0x7E, 0x151, 0x7D, 0x15F,
    0x7C, 0x16C, 0x7A, 0x17A, 0x78, 0x187, 0x76, 0x194,
    0x73, 0x1A1, 0x70, 0x1AD, 0x6D, 0x1BA, 0x6A, 0x1C5,
    0x66, 0x1D1, 0x62, 0x1DC, 0x5E, 0x1E6, 0x5A, 0x1F0,
    0x55, 0x1FA, 0x51, 0x203, 0x4C, 0x20B, 0x47, 0x213,
    0x41, 0x21A, 0x3C, 0x221, 0x36, 0x227, 0x30, 0x22C,
    0x2B, 0x231, 0x25, 0x235, 0x1F, 0x239, 0x18, 0x23B,
    0x12, 0x23D, 12, 0x23F, 6, 0x23F, 0, 0x240,
};

s16 D_8011E2B8[256] = {
    6, 0, 12, 1, 0x12, 2, 0x19, 3,
    0x1F, 5, 0x25, 7, 0x2B, 9, 0x31, 12,
    0x38, 15, 0x3E, 0x13, 0x44, 0x16, 0x4A, 0x1A,
    0x50, 0x1F, 0x56, 0x24, 0x5C, 0x29, 0x61, 0x2E,
    0x67, 0x34, 0x6D, 0x3A, 0x73, 0x40, 0x78, 0x47,
    0x7E, 0x4E, 0x83, 0x55, 0x88, 0x5D, 0x8E, 0x65,
    0x93, 0x6D, 0x98, 0x75, 0x9D, 0x7E, 0xA2, 0x87,
    0xA7, 0x90, 0xAB, 0x9A, 0xB0, 0xA4, 0xB5, 0xAE,
    0xB9, 0xB8, 0xBD, 0xC2, 0xC1, 0xCD, 0xC5, 0xD8,
    0xC9, 0xE3, 0xCD, 0xEF, 0xD1, 0xFA, 0xD4, 0x106,
    0xD8, 0x112, 0xDB, 0x11E, 0xDE, 0x12A, 0xE1, 0x137,
    0xE4, 0x143, 0xE7, 0x150, 0xEA, 0x15D, 0xEC, 0x16A,
    0xEE, 0x177, 0xF1, 0x184, 0xF3, 0x192, 0xF4, 0x19F,
    0xF6, 0x1AD, 0xF8, 0x1BB, 0xF9, 0x1C8, 0xFB, 0x1D6,
    0xFC, 0x1E4, 0xFD, 0x1F2, 0xFE, 0x200, 0xFE, 0x20E,
    0xFF, 0x21C, 0xFF, 0x22A, 0xFF, 0x238, 0x100, 0x247,
    0xFF, 0x255, 0xFF, 0x263, 0xFF, 0x271, 0xFE, 0x27F,
    0xFE, 0x28D, 0xFD, 0x29B, 0xFC, 0x2A9, 0xFB, 0x2B7,
    0xF9, 0x2C4, 0xF8, 0x2D2, 0xF6, 0x2E0, 0xF4, 0x2ED,
    0xF3, 0x2FB, 0xF1, 0x308, 0xEE, 0x315, 0xEC, 0x322,
    0xEA, 0x32F, 0xE7, 0x33C, 0xE4, 0x348, 0xE1, 0x355,
    0xDE, 0x361, 0xDB, 0x36D, 0xD8, 0x379, 0xD4, 0x385,
    0xD1, 0x390, 0xCD, 0x39C, 0xC9, 0x3A7, 0xC5, 0x3B2,
    0xC1, 0x3BD, 0xBD, 0x3C7, 0xB9, 0x3D1, 0xB5, 0x3DB,
    0xB0, 0x3E5, 0xAB, 0x3EF, 0xA7, 0x3F8, 0xA2, 0x401,
    0x9D, 0x40A, 0x98, 0x412, 0x93, 0x41A, 0x8E, 0x422,
    0x88, 0x42A, 0x83, 0x431, 0x7E, 0x438, 0x78, 0x43F,
    0x73, 0x445, 0x6D, 0x44B, 0x67, 0x451, 0x61, 0x456,
    0x5C, 0x45B, 0x56, 0x460, 0x50, 0x465, 0x4A, 0x469,
    0x44, 0x46C, 0x3E, 0x470, 0x38, 0x473, 0x31, 0x476,
    0x2B, 0x478, 0x25, 0x47A, 0x1F, 0x47C, 0x19, 0x47D,
    0x12, 0x47E, 12, 0x47F, 6, 0x47F, 0, 0x480,
};

s16 D_8011E4B8[2] = {
    0, 0,
};

s16 D_8011E4BC[120] = {0};

s16 D_8011E5AC[512] = {
    1, 0, 3, 0, 4, 0, 6, 1,
    7, 1, 9, 2, 10, 3, 12, 4,
    14, 5, 15, 6, 0x11, 8, 0x12, 9,
    0x14, 11, 0x15, 12, 0x17, 14, 0x18, 0x10,
    0x1A, 0x12, 0x1C, 0x14, 0x1D, 0x17, 0x1F, 0x19,
    0x20, 0x1C, 0x22, 0x1E, 0x23, 0x21, 0x25, 0x24,
    0x26, 0x27, 0x28, 0x2A, 0x29, 0x2E, 0x2B, 0x31,
    0x2C, 0x34, 0x2E, 0x38, 0x2F, 0x3C, 0x30, 0x40,
    0x32, 0x44, 0x33, 0x48, 0x35, 0x4C, 0x36, 0x50,
    0x38, 0x54, 0x39, 0x59, 0x3A, 0x5E, 0x3C, 0x62,
    0x3D, 0x67, 0x3F, 0x6C, 0x40, 0x71, 0x41, 0x76,
    0x43, 0x7C, 0x44, 0x81, 0x45, 0x86, 0x47, 0x8C,
    0x48, 0x92, 0x49, 0x97, 0x4A, 0x9D, 0x4C, 0xA3,
    0x4D, 0xA9, 0x4E, 0xAF, 0x4F, 0xB6, 0x51, 0xBC,
    0x52, 0xC2, 0x53, 0xC9, 0x54, 0xD0, 0x55, 0xD6,
    0x57, 0xDD, 0x58, 0xE4, 0x59, 0xEB, 0x5A, 0xF2,
    0x5B, 0xF9, 0x5C, 0x101, 0x5D, 0x108, 0x5E, 0x10F,
    0x5F, 0x117, 0x60, 0x11E, 0x61, 0x126, 0x62, 0x12E,
    0x63, 0x136, 0x64, 0x13E, 0x65, 0x146, 0x66, 0x14E,
    0x67, 0x156, 0x68, 0x15E, 0x69, 0x166, 0x6A, 0x16E,
    0x6B, 0x177, 0x6C, 0x17F, 0x6C, 0x188, 0x6D, 0x190,
    0x6E, 0x199, 0x6F, 0x1A2, 0x70, 0x1AB, 0x70, 0x1B3,
    0x71, 0x1BC, 0x72, 0x1C5, 0x73, 0x1CE, 0x73, 0x1D7,
    0x74, 0x1E0, 0x75, 0x1EA, 0x75, 0x1F3, 0x76, 0x1FC,
    0x76, 0x205, 0x77, 0x20F, 0x77, 0x218, 0x78, 0x221,
    0x79, 0x22B, 0x79, 0x234, 0x7A, 0x23E, 0x7A, 0x248,
    0x7A, 0x251, 0x7B, 0x25B, 0x7B, 0x264, 0x7C, 0x26E,
    0x7C, 0x278, 0x7C, 0x282, 0x7D, 0x28B, 0x7D, 0x295,
    0x7D, 0x29F, 0x7E, 0x2A9, 0x7E, 0x2B3, 0x7E, 0x2BD,
    0x7E, 0x2C7, 0x7F, 0x2D1, 0x7F, 0x2DB, 0x7F, 0x2E5,
    0x7F, 0x2EF, 0x7F, 0x2F8, 0x7F, 0x302, 0x7F, 0x30C,
    0x7F, 0x316, 0x7F, 0x320, 0x7F, 0x32A, 0x80, 0x335,
    0x7F, 0x33F, 0x7F, 0x349, 0x7F, 0x353, 0x7F, 0x35D,
    0x7F, 0x367, 0x7F, 0x370, 0x7F, 0x37A, 0x7F, 0x384,
    0x7F, 0x38E, 0x7F, 0x398, 0x7E, 0x3A2, 0x7E, 0x3AC,
    0x7E, 0x3B6, 0x7E, 0x3C0, 0x7D, 0x3CA, 0x7D, 0x3D4,
    0x7D, 0x3DD, 0x7C, 0x3E7, 0x7C, 0x3F1, 0x7C, 0x3FB,
    0x7B, 0x404, 0x7B, 0x40E, 0x7A, 0x417, 0x7A, 0x421,
    0x7A, 0x42B, 0x79, 0x434, 0x79, 0x43E, 0x78, 0x447,
    0x77, 0x450, 0x77, 0x45A, 0x76, 0x463, 0x76, 0x46C,
    0x75, 0x475, 0x75, 0x47F, 0x74, 0x488, 0x73, 0x491,
    0x73, 0x49A, 0x72, 0x4A3, 0x71, 0x4AC, 0x70, 0x4B4,
    0x70, 0x4BD, 0x6F, 0x4C6, 0x6E, 0x4CF, 0x6D, 0x4D7,
    0x6C, 0x4E0, 0x6C, 0x4E8, 0x6B, 0x4F1, 0x6A, 0x4F9,
    0x69, 0x501, 0x68, 0x509, 0x67, 0x511, 0x66, 0x519,
    0x65, 0x521, 0x64, 0x529, 0x63, 0x531, 0x62, 0x539,
    0x61, 0x541, 0x60, 0x548, 0x5F, 0x550, 0x5E, 0x557,
    0x5D, 0x55E, 0x5C, 0x566, 0x5B, 0x56D, 0x5A, 0x574,
    0x59, 0x57B, 0x58, 0x582, 0x57, 0x589, 0x55, 0x58F,
    0x54, 0x596, 0x53, 0x59D, 0x52, 0x5A3, 0x51, 0x5A9,
    0x4F, 0x5B0, 0x4E, 0x5B6, 0x4D, 0x5BC, 0x4C, 0x5C2,
    0x4A, 0x5C8, 0x49, 0x5CD, 0x48, 0x5D3, 0x47, 0x5D9,
    0x45, 0x5DE, 0x44, 0x5E3, 0x43, 0x5E9, 0x41, 0x5EE,
    0x40, 0x5F3, 0x3F, 0x5F8, 0x3D, 0x5FD, 0x3C, 0x601,
    0x3A, 0x606, 0x39, 0x60B, 0x38, 0x60F, 0x36, 0x613,
    0x35, 0x617, 0x33, 0x61B, 0x32, 0x61F, 0x30, 0x623,
    0x2F, 0x627, 0x2E, 0x62B, 0x2C, 0x62E, 0x2B, 0x631,
    0x29, 0x635, 0x28, 0x638, 0x26, 0x63B, 0x25, 0x63E,
    0x23, 0x641, 0x22, 0x643, 0x20, 0x646, 0x1F, 0x648,
    0x1D, 0x64B, 0x1C, 0x64D, 0x1A, 0x64F, 0x18, 0x651,
    0x17, 0x653, 0x15, 0x654, 0x14, 0x656, 0x12, 0x657,
    0x11, 0x659, 15, 0x65A, 14, 0x65B, 12, 0x65C,
    10, 0x65D, 9, 0x65E, 7, 0x65E, 6, 0x65F,
    4, 0x65F, 3, 0x65F, 1, 0x65F, 0, 0x660,
};

WalkState walk_state_table[14] = {
    {D_8011E4B8, 1, 1, 0}, {D_8011E4B8, 1, 1, 1}, {D_8011E4B8, 1, 1, 2}, {D_8011E4B8, 1, 1, 3},
    {D_8011E4BC, 0x40, 1, 1}, {D_8011E4BC, 0x40, 1, 2}, {D_8011E4BC, 0x40, 1, 3}, {D_8011E5AC, 0x100, 1, 1},
    {D_8011E1B8, 0x40, 1, 2}, {D_8011E1B8, 0x40, -1, 3}, {D_8011E1B8, 0x40, -1, 1}, {D_8011E2B8, 0x80, -1, 3},
    {D_8011E1B8, 0x40, 1, 1}, {D_8011E2B8, 0x80, 1, 2},
};

s32 semi_truck_interp_a[7] = {
    0x30001, 0x3012D, 0x4014A, 2, 0, 0x1000001,
    -0xFFFC,
};

s32 semi_truck_interp_b[7] = {
    0x30001, 0x3012D, 0x4014D, 2, 0, 0x1000001,
    -0xFFFC,
};

GunSetup spin_fx_gun_setups[2] = {
    {0xE000, 0x32000, 0x800, 0xA, 0, 0xC, 0x3C, 0x14, 0x14, 0x2D, 7, 6, 0xF, 0x1E, 0x51},
    {0xE000, 0x32000, 0x800, 0xA, 0, 0xC, 0x96, 0x14, 0x14, 0x2D, 7, 6, 0xF, 0x1E, 0x51},
};

u16 spin_fx_table[12] = {
    0x010E, 0xFED9, 0xFE80, 0x0000, 0x0110, 0xFECC, 0xFEA2, 0x0000,
    0x0114, 0xFEC0, 0xFEC4, 0x0000,
};

u32 part_hit_weights[4] = {
    0x10001000, 0x10001000, 0x10001000, 0x10001000,
};

/* labels inside the objects above */
__asm__(".globl D_8011C8A3\n.set D_8011C8A3, ripple_fx_params+0x3\n"
        ".globl D_8011C8A2\n.set D_8011C8A2, ripple_fx_params+0x2\n"
        ".globl D_8011C8A1\n.set D_8011C8A1, ripple_fx_params+0x1\n"
        ".globl d_80117788\n.set d_80117788, ripple_fx_params+0x8\n"
        ".globl d_8011778C\n.set d_8011778C, ripple_fx_params+0xC\n"
        ".globl span_table_offset\n.set span_table_offset, stage_data_block+0x4\n");
/* script group members: their names at their starts in the struct (object bounds) */
__asm__(".globl motorcycle_anim_idle\n.set motorcycle_anim_idle, motorcycle_anims+0x0\n"
        ".globl motorcycle_data\n.set motorcycle_data, motorcycle_anims+0x8\n"
        ".globl flier_script_ptr_anim_idle\n.set flier_script_ptr_anim_idle, flier_script_ptr_anims+0x0\n"
        ".globl flier_script_ptr\n.set flier_script_ptr, flier_script_ptr_anims+0x8\n"
        ".globl s06_helicopter_anim_idle\n.set s06_helicopter_anim_idle, s06_helicopter_anims+0x0\n"
        ".globl s06_helicopter_data\n.set s06_helicopter_data, s06_helicopter_anims+0x8\n"
        ".globl helicopter_idle\n.set helicopter_idle, helicopter_script_table_streams+0x0\n"
        ".globl s06_helicopter_choose\n.set s06_helicopter_choose, helicopter_script_table_streams+0x4\n"
        ".globl s06_helicopter_patrol\n.set s06_helicopter_patrol, helicopter_script_table_streams+0x14\n"
        ".globl s06_helicopter_patrol_wait\n.set s06_helicopter_patrol_wait, helicopter_script_table_streams+0x28\n"
        ".globl s06_helicopter_turn_to_patrol\n.set s06_helicopter_turn_to_patrol, helicopter_script_table_streams+0x3C\n"
        ".globl s06_helicopter_turn\n.set s06_helicopter_turn, helicopter_script_table_streams+0x4C\n"
        ".globl s06_helicopter_attack\n.set s06_helicopter_attack, helicopter_script_table_streams+0x5C\n"
        ".globl s06_helicopter_attack_wait\n.set s06_helicopter_attack_wait, helicopter_script_table_streams+0x70\n"
        ".globl s06_helicopter_drift_hold\n.set s06_helicopter_drift_hold, helicopter_script_table_streams+0x84\n"
        ".globl s06_helicopter_turn_hold\n.set s06_helicopter_turn_hold, helicopter_script_table_streams+0x94\n"
        ".globl s06_helicopter_turn_wait\n.set s06_helicopter_turn_wait, helicopter_script_table_streams+0x9C\n"
        ".globl s06_helicopter_turn_end\n.set s06_helicopter_turn_end, helicopter_script_table_streams+0xA8\n"
        ".globl helicopter_script_table\n.set helicopter_script_table, helicopter_script_table_streams+0xB0\n"
        ".globl helicopter_script_start\n.set helicopter_script_start, helicopter_script_table_streams+0xE0\n"
        ".globl minicopter_script\n.set minicopter_script, minicopter_anims+0x0\n"
        ".globl minicopter_data\n.set minicopter_data, minicopter_anims+0x8\n"
        ".globl minicopter_cycle\n.set minicopter_cycle, minicopter_scripts+0x0\n"
        ".globl minicopter_decide\n.set minicopter_decide, minicopter_scripts+0x4\n"
        ".globl minicopter_chase\n.set minicopter_chase, minicopter_scripts+0x14\n"
        ".globl minicopter_chase_hold\n.set minicopter_chase_hold, minicopter_scripts+0x28\n"
        ".globl minicopter_pursue\n.set minicopter_pursue, minicopter_scripts+0x34\n"
        ".globl minicopter_pursue_hold\n.set minicopter_pursue_hold, minicopter_scripts+0x48\n"
        ".globl minicopter_fire\n.set minicopter_fire, minicopter_scripts+0x50\n"
        ".globl minicopter_fire_hold\n.set minicopter_fire_hold, minicopter_scripts+0x64\n"
        ".globl minicopter_restart\n.set minicopter_restart, minicopter_scripts+0x70\n"
        ".globl minicopter_script_ops\n.set minicopter_script_ops, minicopter_scripts+0x78\n"
        ".globl minicopter_script_start\n.set minicopter_script_start, minicopter_scripts+0x9C\n"
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
        ".globl road_barrier_script\n.set road_barrier_script, road_barrier_anims+0x0\n"
        ".globl road_barrier_with_traffic_cone_data\n.set road_barrier_with_traffic_cone_data, road_barrier_anims+0x8\n");
