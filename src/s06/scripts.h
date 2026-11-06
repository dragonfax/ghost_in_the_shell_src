/* s06: names for the script streams' table indices and op numbers, made by scripts/script_c.py
   from the stage's script data (FINDINGS "Script system"). */

#ifndef SCRIPTS_H
#define SCRIPTS_H

/* motorcycle_data: animation streams */
enum {
    MOTORCYCLE_ANIM_IDLE = 0,
};

/* flier_script_ptr: animation streams */
enum {
    FLIER_SCRIPT_PTR_ANIM_IDLE = 0,
};

/* s06_helicopter_data: animation streams */
enum {
    S06_HELICOPTER_ANIM_IDLE = 0,
};

/* helicopter_script_table: behaviour streams */
enum {
    HELICOPTER_IDLE = 0,
    S06_HELICOPTER_CHOOSE = 1,
    S06_HELICOPTER_PATROL = 2,
    S06_HELICOPTER_PATROL_WAIT = 3,
    S06_HELICOPTER_TURN_TO_PATROL = 4,
    S06_HELICOPTER_TURN = 5,
    S06_HELICOPTER_ATTACK = 6,
    S06_HELICOPTER_ATTACK_WAIT = 7,
    S06_HELICOPTER_DRIFT_HOLD = 8,
    S06_HELICOPTER_TURN_HOLD = 9,
    S06_HELICOPTER_TURN_WAIT = 10,
    S06_HELICOPTER_TURN_END = 11,
};

/* minicopter_data: animation streams */
enum {
    MINICOPTER_SCRIPT = 0,
};

/* minicopter_script_ops: behaviour streams */
enum {
    MINICOPTER_CYCLE = 0,
    MINICOPTER_DECIDE = 1,
    MINICOPTER_CHASE = 2,
    MINICOPTER_CHASE_HOLD = 3,
    MINICOPTER_PURSUE = 4,
    MINICOPTER_PURSUE_HOLD = 5,
    MINICOPTER_FIRE = 6,
    MINICOPTER_FIRE_HOLD = 7,
    MINICOPTER_RESTART = 8,
};

/* tank_2_data: animation streams */
enum {
    TANK_2_ANIM_IDLE = 0,
};

/* tank2_link_data: behaviour streams */
enum {
    TANK_2_INIT = 0,
    TANK_2_PATROL_START = 1,
    TANK_2_PATROL = 2,
    TANK_2_STOP = 3,
    TANK_2_STOP_WAIT = 4,
    TANK_2_SPOTTED = 5,
    TANK_2_CHASE = 6,
    TANK_2_ENGAGE = 7,
    TANK_2_AIM = 8,
    TANK_2_TURN_TO_PLAYER = 9,
    TANK_2_TURN_WAIT = 10,
    TANK_2_FACE_WAIT = 11,
    TANK_2_HALT = 12,
    TANK_2_FIRE_READY = 13,
    TANK_2_FIRE_START = 14,
    TANK_2_FIRE_LOOP = 15,
    TANK_2_FIRE_COOLDOWN = 16,
    TANK_2_STATIC_INIT = 17,
    TANK_2_STATIC_WATCH = 18,
    TANK_2_STATIC_SPOTTED = 19,
    TANK_2_STATIC_CHASE = 20,
    TANK_2_STATIC_ENGAGE = 21,
    TANK_2_STATIC_AIM = 22,
    TANK_2_STATIC_TURN_TO_PLAYER = 23,
    TANK_2_STATIC_TURN_WAIT = 24,
    TANK_2_STATIC_FACE_WAIT = 25,
    TANK_2_STATIC_FIRE_START = 26,
    TANK_2_STATIC_FIRE_LOOP = 27,
    TANK_2_STATIC_FIRE_COOLDOWN = 28,
    TANK_2_PURSUE_WATCH = 29,
    TANK_2_PURSUE_SPOTTED = 30,
    TANK_2_PURSUE_CHASE = 31,
    TANK_2_PURSUE_ANGLE_CHECK = 32,
    TANK_2_PURSUE_TURN_TO_PLAYER = 33,
    TANK_2_PURSUE_TURN_WAIT = 34,
    TANK_2_PURSUE_FACE_WAIT = 35,
};

/* road_barrier_with_traffic_cone_data: animation streams */
enum {
    ROAD_BARRIER_SCRIPT = 0,
};

/* enemy_child_part_jump_table: behaviour streams */
enum {
    SEMI_TRUCK_MECH_M6_BOSS_IDLE = 0,
    SEMI_TRUCK_MECH_M6_BOSS_READY = 1,
    SEMI_TRUCK_MECH_M6_BOSS_WAIT_GO = 2,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_START = 3,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_BRANCH = 4,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_LEFT_WAIT = 5,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_LEFT_TRAIL = 6,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_LEFT_SETTLE = 7,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_LEFT_EXIT = 8,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_BEGIN = 9,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_WAIT = 10,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_TRAIL = 11,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_SETTLE = 12,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_RIGHT_EXIT = 13,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_LOOP = 14,
    SEMI_TRUCK_MECH_M6_BOSS_WALK_TO_RIGHT = 15,
};

/* enemy_child_part_script_table: animation streams */
enum {
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_IDLE = 0,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_WAKE = 1,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_READY_HOLD = 2,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_A = 3,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_A_END = 4,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_B = 5,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_B_END = 6,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_A_FAST = 7,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_A_FAST_END = 8,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_B_FAST = 9,
    SEMI_TRUCK_MECH_M6_BOSS_ANIM_WALK_B_FAST_END = 10,
};

/* enemy_part_child_jump_table: behaviour streams */
enum {
    ENEMY_PART_CHILD_DEPLOY = 0,
    ENEMY_PART_CHILD_AWAIT_TRIGGER = 1,
    ENEMY_PART_CHILD_ATTACH = 2,
    ENEMY_PART_CHILD_FIRE_START = 3,
    ENEMY_PART_CHILD_FIRE_LOOP = 4,
    ENEMY_PART_CHILD_FIRE_BURST = 5,
    ENEMY_PART_CHILD_FIRE_END = 6,
    ENEMY_PART_CHILD_FIRE_RESTART = 7,
    ENEMY_PART_CHILD_COOLDOWN = 8,
};

/* enemy_part_child_script_table: animation streams */
enum {
    ENEMY_PART_CHILD_ANIM_HOLD = 0,
    ENEMY_PART_CHILD_ANIM_DEPLOY = 1,
    ENEMY_PART_CHILD_ANIM_IDLE = 2,
    ENEMY_PART_CHILD_ANIM_FIRE = 3,
};

/* D_8011CA2C: states */
enum {
    S06_HELICOPTER_STATE_FLY = 0,
    S06_HELICOPTER_STATE_FIRE = 1,
    S06_HELICOPTER_STATE_FLOW = 2,
    S06_HELICOPTER_STATE_TURN = 3,
};

/* minicopter_states: states */
enum {
    MINICOPTER_STATE_CHASE = 0,
    MINICOPTER_STATE_PURSUE = 1,
    MINICOPTER_STATE_FIRE = 2,
};

/* d_8011CF9C: states */
enum {
    TANK_STATE_IDLE = 0,
    TANK_STATE_STOP = 1,
    TANK_STATE_TURN = 2,
    TANK_STATE_TRACK = 3,
    TANK_STATE_FACE_PLAYER = 4,
    TANK_STATE_FIRE = 5,
};

/* enemy_part_states: states */
enum {
    ENEMY_CHILD_PART_STATE_IDLE = 0,
    ENEMY_CHILD_PART_STATE_READY = 1,
    ENEMY_CHILD_PART_STATE_WAIT_GO = 2,
    ENEMY_CHILD_PART_STATE_WALK_START = 3,
    ENEMY_CHILD_PART_STATE_WALK_LEFT = 4,
    ENEMY_CHILD_PART_STATE_WALK_LEFT_SETTLE = 5,
    ENEMY_CHILD_PART_STATE_WALK_RIGHT = 6,
};

/* D_8011F2E4: states */
enum {
    ENEMY_PART_CHILD_STATE_STOWED = 0,
    ENEMY_PART_CHILD_STATE_DEPLOY = 1,
    ENEMY_PART_CHILD_STATE_IDLE = 2,
    ENEMY_PART_CHILD_STATE_FIRE = 3,
};

/* D_8011C9FC: the ops of s06_helicopter_spawn */
enum {
    S06_HELICOPTER_SPEED_APPROACH = 1, /* obj_speed_approach */
    S06_HELICOPTER_SET_NEXT_STATE = 2, /* obj_set_next_state */
    S06_HELICOPTER_SET_TURN_MODE = 3, /* script_set_turn_mode */
    S06_HELICOPTER_JUMP_IF_PLAYER_NEAR = 4, /* obj_jump_if_player_near */
    S06_HELICOPTER_JUMP_TABLE_IF_PLAYER_FAR = 5, /* script_op_jump_table_if_player_far */
};

/* minicopter_call_table: the ops of minicopter_spawn */
enum {
    MINICOPTER_READ_SPEED = 1, /* script_read_speed */
    MINICOPTER_READ_STATE = 2, /* obj_script_read_state */
    MINICOPTER_READ_MODE = 3, /* obj_script_read_mode */
    MINICOPTER_JUMP_IF_NEAR = 4, /* obj_script_jump_if_near */
    MINICOPTER_STEP_OP = 5, /* script_step_op */
};

/* d_8011CF34: the ops of tank_spawn */
enum {
    TANK_JUMP_IF_PLAYER_NEAR = 1, /* script_op_jump_if_player_near */
    TANK_JUMP_IF_NEAR_PLAYER_IN_VIEW = 2, /* script_jump_if_near_player_in_view */
    TANK_JUMP_IF_PLAYER_FAR = 3, /* script_op_jump_if_player_far */
    TANK_JUMP_IF_PLAYER_IN_VIEW = 4, /* script_jump_if_player_in_view */
    TANK_JUMP_IF_IN_CELL_CORNER = 5, /* script_op_jump_if_in_cell_corner */
    TANK_SET_SPEED = 6, /* script_op_set_speed */
    TANK_READ_S32 = 7, /* script_read_s32 */
    TANK_SET_UNK_234 = 8, /* script_op_set_unk_234 */
    TANK_RETARGET = 9, /* obj_retarget */
    TANK_JUMP_TABLE = 10, /* script_jump_table */
    TANK_JUMP_IF_NEAR_TARGET = 11, /* script_op_jump_if_near_target */
    TANK_PLAYER_ANGLE_BRANCH = 12, /* script_player_angle_branch */
};

/* semi_truck_mech_call_table: the ops of semi_truck_mech_spawn */
enum {
    SEMI_TRUCK_MECH_SKIP_OP = 1, /* script_skip_op */
};

/* enemy_part_call_table: the ops of enemy_child_part_spawn */
enum {
    ENEMY_CHILD_PART_CURSOR_ADVANCE_ALT = 1, /* script_cursor_advance_alt */
    ENEMY_CHILD_PART_JUMP_IF_NEAR = 2, /* script_jump_if_near */
    ENEMY_CHILD_PART_JUMP_IF_FAR = 3, /* script_jump_if_far */
    ENEMY_CHILD_PART_TURN_TO_PLAYER = 4, /* script_turn_to_player */
    ENEMY_CHILD_PART_JUMP_IF_OP_EQ = 5, /* script_jump_if_op_eq */
    ENEMY_CHILD_PART_STREAM_READ_HALFWORD = 6, /* stream_read_halfword */
    ENEMY_CHILD_PART_LOAD_TABLE_ENTRY = 7, /* script_load_table_entry */
    ENEMY_CHILD_PART_TRAIL_EMIT = 8, /* obj_trail_emit */
    ENEMY_CHILD_PART_JUMP = 9, /* script_op_jump */
};

/* D_8011F160: the ops of enemy_part_child_spawn */
enum {
    ENEMY_PART_CHILD_CURSOR_ADVANCE = 1, /* script_cursor_advance */
    ENEMY_PART_CHILD_JUMP_IF_NEAR_ALT = 2, /* script_jump_if_near_alt */
    ENEMY_PART_CHILD_JUMP_IF_FAR = 3, /* obj_script_jump_if_far */
    ENEMY_PART_CHILD_TURN_TO_PLAYER_JUMP = 4, /* script_turn_to_player_jump */
    ENEMY_PART_CHILD_CASE_MATCH = 5, /* script_case_match */
    ENEMY_PART_CHILD_READ_U16 = 6, /* script_read_u16 */
    ENEMY_PART_CHILD_JUMP_INDEXED = 7, /* script_jump_indexed */
    ENEMY_PART_CHILD_FIRE_BOTH_SIDES = 8, /* obj_fire_both_sides */
    ENEMY_PART_CHILD_ATTACH_DEFAULT = 9, /* obj_attach_default */
    ENEMY_PART_CHILD_SOUND_LOOP_START = 10, /* obj_sound_loop_start */
    ENEMY_PART_CHILD_SOUND_LOOP_STOP = 11, /* obj_sound_loop_stop */
    ENEMY_PART_CHILD_SOUND_START_HELD = 12, /* sound_start_held */
    ENEMY_PART_CHILD_SOUND_STOP_HELD = 13, /* sound_stop_held */
};

#endif
