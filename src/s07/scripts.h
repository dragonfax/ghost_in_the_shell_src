/* s07: names for the script streams' table indices and op numbers, made by scripts/script_c.py
   from the stage's script data (FINDINGS "Script system"). */

#ifndef SCRIPTS_H
#define SCRIPTS_H

/* stationary_rocket_launcher_data: animation streams */
enum {
    STATIONARY_ROCKET_LAUNCHER_ANIM_IDLE = 0,
};

/* rocket_launcher_script: behaviour streams */
enum {
    STATIONARY_ROCKET_LAUNCHER_IDLE = 0,
    STATIONARY_ROCKET_LAUNCHER_TRACK = 1,
    STATIONARY_ROCKET_LAUNCHER_AIM = 2,
    STATIONARY_ROCKET_LAUNCHER_LOCK_ON = 3,
    STATIONARY_ROCKET_LAUNCHER_FIRE_START = 4,
    STATIONARY_ROCKET_LAUNCHER_FIRE_LOOP = 5,
    STATIONARY_ROCKET_LAUNCHER_LAUNCH_START = 6,
    STATIONARY_ROCKET_LAUNCHER_LAUNCH_LOOP = 7,
};

/* enemy_fuchikoma_b_data: animation streams */
enum {
    ENEMY_FUCHIKOMA_B_ANIM_IDLE = 0,
    ENEMY_FUCHIKOMA_B_ANIM_WALK = 1,
};

/* fuchikoma_link_data: behaviour streams */
enum {
    ENEMY_FUCHIKOMA_B_IDLE = 0,
    ENEMY_FUCHIKOMA_B_START = 1,
    ENEMY_FUCHIKOMA_B_ACCELERATE = 2,
    ENEMY_FUCHIKOMA_B_WAIT_TRIGGER = 3,
    ENEMY_FUCHIKOMA_B_CHASE_START = 4,
    ENEMY_FUCHIKOMA_B_SEARCH = 5,
    ENEMY_FUCHIKOMA_B_ENGAGE = 6,
    ENEMY_FUCHIKOMA_B_AIM = 7,
    ENEMY_FUCHIKOMA_B_CORNER_CHECK = 8,
    ENEMY_FUCHIKOMA_B_CORNER_TURN = 9,
    ENEMY_FUCHIKOMA_B_AWAIT_MODE = 10,
    ENEMY_FUCHIKOMA_B_DEATH_WAIT = 11,
    ENEMY_FUCHIKOMA_B_DEATH = 12,
    ENEMY_FUCHIKOMA_B_AWAIT_CHASE = 13,
};

/* walker_mech_data: animation streams */
enum {
    WALKER_MECH_ANIM_IDLE = 0,
    WALKER_MECH_ANIM_WALK = 1,
    WALKER_MECH_ANIM_FIRE = 2,
    WALKER_DEATH_SCRIPT = 3,
};

/* walker_type_data_alt: behaviour streams */
enum {
    WALKER_MECH_BEGIN = 0,
    WALKER_MECH_PATROL_START = 1,
    WALKER_MECH_WATCH = 2,
    WALKER_MECH_ENGAGE_WAIT = 3,
    WALKER_MECH_ENGAGE = 4,
    TRIPLE_BARREL_ROBOT_FIRE_END = 5,
    TRIPLE_BARREL_ROBOT_COOLDOWN = 6,
};

/* helicopter_2_data: animation streams */
enum {
    HELICOPTER_2_SCRIPT_CFG = 0,
};

/* helicopter2_script_data: behaviour streams */
enum {
    HELICOPTER2_THINK = 0,
    HELICOPTER2_SELECT = 1,
    HELICOPTER2_PATROL = 2,
    HELICOPTER2_CRUISE = 3,
    HELICOPTER2_BANK_TURN = 4,
    HELICOPTER2_ATTACK = 5,
    HELICOPTER2_HOVER = 6,
    HELICOPTER2_HOLD_START = 7,
    HELICOPTER2_HOLD_LOOP = 8,
    HELICOPTER2_CYCLE_END = 9,
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

/* gun_turret_2_data: animation streams */
enum {
    GUN_TURRET_2_POSE = 0,
};

/* gun_turret_2_link_data: behaviour streams */
enum {
    GUN_TURRET_2_IDLE = 0,
    GUN_TURRET_2_SPOTTED = 1,
    GUN_TURRET_2_TRACKING = 2,
    GUN_TURRET_2_AIMED = 3,
    GUN_TURRET_2_OPEN_FIRE = 4,
    GUN_TURRET_2_FIRING = 5,
    GUN_TURRET_2_COOLDOWN = 6,
    GUN_TURRET_2_COOLING = 7,
};

/* grenade_fuchikoma_data: animation streams */
enum {
    GRENADE_FUCHIKOMA_ANIM_IDLE = 0,
    GRENADE_FUCHIKOMA_ANIM_SPIN = 1,
    GRENADE_FUCHIKOMA_ANIM_HOLD_START = 2,
    GRENADE_FUCHIKOMA_ANIM_HOLD = 3,
};

/* grenade_type_data: behaviour streams */
enum {
    GRENADE_FUCHIKOMA_DORMANT = 0,
    GRENADE_FUCHIKOMA_RELEASE = 1,
    GRENADE_FUCHIKOMA_RELEASE_WAIT = 2,
    ROCKET_FUCHIKOMA_READY = 3,
    ROCKET_FUCHIKOMA_AIM_START = 4,
    GRENADE_FUCHIKOMA_SEEK = 5,
    GRENADE_FUCHIKOMA_SET_PARAMS = 6,
    GRENADE_FUCHIKOMA_TRACK = 7,
    ROCKET_FUCHIKOMA_CLOSE_IN = 8,
    ROCKET_FUCHIKOMA_BRAKE = 9,
    GRENADE_FUCHIKOMA_WAIT_STOP = 10,
    ROCKET_FUCHIKOMA_FIRE_WAIT = 11,
    ROCKET_FUCHIKOMA_FIRE_START = 12,
    GRENADE_FUCHIKOMA_DETONATE_WAIT = 13,
    ROCKET_FUCHIKOMA_REPOSITION = 14,
    GRENADE_FUCHIKOMA_RECOVER_FACE = 15,
};

/* bomb_mech_m7_boss_data: animation streams */
enum {
    BOMB_MECH_M7_BOSS_ANIM_IDLE = 0,
    BOMB_MECH_M7_BOSS_ANIM_WALK_START = 1,
    BOMB_MECH_M7_BOSS_ANIM_WALK = 2,
    BOMB_MECH_M7_BOSS_ANIM_TURN = 3,
    BOMB_MECH_M7_BOSS_ANIM_HIDE_START = 4,
    BOMB_MECH_M7_BOSS_ANIM_HIDE = 5,
    BOMB_MECH_M7_BOSS_ANIM_EMERGE = 6,
    BOMB_MECH_M7_BOSS_ANIM_CROUCH = 7,
    BOMB_MECH_M7_BOSS_ANIM_HOP_LAUNCH = 8,
    BOMB_MECH_M7_BOSS_ANIM_HOP_RISE = 9,
    BOMB_MECH_M7_BOSS_ANIM_HOP_RISE_HOLD = 10,
    BOMB_MECH_M7_BOSS_ANIM_HOP_FALL = 11,
    BOMB_MECH_M7_BOSS_ANIM_HOP_FALL_HOLD = 12,
    BOMB_MECH_M7_BOSS_ANIM_HOP_LAND = 13,
    BOMB_MECH_M7_BOSS_ANIM_FLY_PREPARE = 14,
    BOMB_MECH_M7_BOSS_ANIM_FLY_HOLD = 15,
    BOMB_MECH_M7_BOSS_ANIM_FLY_END = 16,
    BOMB_MECH_M7_BOSS_ANIM_BOMB_RUN = 17,
    BOMB_MECH_M7_BOSS_ANIM_JITTER = 18,
    BOMB_MECH_M7_BOSS_ANIM_JITTER_WRAP = 19,
};

/* D_8011DD68: behaviour streams */
enum {
    BOMB_MECH_M7_BOSS_INIT = 0,
    BOMB_MECH_M7_BOSS_INIT_RESUME = 1,
    BOMB_MECH_M7_BOSS_INIT_WAIT = 2,
    BOMB_MECH_M7_BOSS_INIT_WAIT_LOOP = 3,
    BOMB_MECH_M7_BOSS_INIT_EMERGE = 4,
    BOMB_MECH_M7_BOSS_INIT_EMERGE_WAIT = 5,
    BOMB_MECH_M7_BOSS_INIT_RETURN = 6,
    BOMB_MECH_M7_BOSS_TURN_THEN_HOP = 7,
    BOMB_MECH_M7_BOSS_HOP_CROUCH = 8,
    BOMB_MECH_M7_BOSS_HOP_CROUCH_WAIT = 9,
    BOMB_MECH_M7_BOSS_HOP_SPAWN_PARTS = 10,
    BOMB_MECH_M7_BOSS_HOP_SPAWN_WAIT = 11,
    BOMB_MECH_M7_BOSS_HOP_LAUNCH = 12,
    BOMB_MECH_M7_BOSS_HOP_RISE_WAIT = 13,
    BOMB_MECH_M7_BOSS_HOP_FALL = 14,
    BOMB_MECH_M7_BOSS_HOP_CHECK = 15,
    BOMB_MECH_M7_BOSS_HOP_LAND = 16,
    BOMB_MECH_M7_BOSS_HOP_LAND_WAIT = 17,
    BOMB_MECH_M7_BOSS_HOP_SHOOT = 18,
    BOMB_MECH_M7_BOSS_HOP_RETURN = 19,
    BOMB_MECH_M7_BOSS_TURN_THEN_FLY = 20,
    BOMB_MECH_M7_BOSS_FLY_PREPARE = 21,
    BOMB_MECH_M7_BOSS_FLY_PREPARE_WAIT = 22,
    BOMB_MECH_M7_BOSS_FLY_START = 23,
    BOMB_MECH_M7_BOSS_FLY_EMIT_LOOP = 24,
    BOMB_MECH_M7_BOSS_FLY_HOLD = 25,
    BOMB_MECH_M7_BOSS_FLY_END = 26,
    BOMB_MECH_M7_BOSS_FLY_END_WAIT = 27,
    BOMB_MECH_M7_BOSS_FLY_RETURN = 28,
    BOMB_MECH_M7_BOSS_TURN_THEN_BOMBS = 29,
    BOMB_MECH_M7_BOSS_BOMB_RUN_START = 30,
    BOMB_MECH_M7_BOSS_BOMB_PASS = 31,
    BOMB_MECH_M7_BOSS_BOMB_PASS_WAIT = 32,
    BOMB_MECH_M7_BOSS_BOMB_DROP = 33,
    BOMB_MECH_M7_BOSS_BOMB_DROP_WAIT = 34,
    BOMB_MECH_M7_BOSS_BOMB_PASS_LOOP = 35,
    BOMB_MECH_M7_BOSS_WALK_THEN_JITTER = 36,
    BOMB_MECH_M7_BOSS_JITTER_START = 37,
    BOMB_MECH_M7_BOSS_JITTER_FRAME = 38,
    BOMB_MECH_M7_BOSS_JITTER_WAIT = 39,
    BOMB_MECH_M7_BOSS_JITTER_END = 40,
    BOMB_MECH_M7_BOSS_TIMER_WAIT = 41,
    BOMB_MECH_M7_BOSS_TIMER_RETURN = 42,
    BOMB_MECH_M7_BOSS_WALK_THEN_FIRE = 43,
    BOMB_MECH_M7_BOSS_FIRE_BURST_START = 44,
    BOMB_MECH_M7_BOSS_FIRE_BURST_RAMP_WAIT = 45,
    BOMB_MECH_M7_BOSS_FIRE_SOUND = 46,
    BOMB_MECH_M7_BOSS_FIRE_MUZZLE = 47,
    BOMB_MECH_M7_BOSS_FIRE_BURST_WAIT = 48,
    BOMB_MECH_M7_BOSS_FIRE_BURST_END = 49,
    BOMB_MECH_M7_BOSS_WALK_START = 50,
    BOMB_MECH_M7_BOSS_WALK_WAIT = 51,
    BOMB_MECH_M7_BOSS_WALK_END = 52,
    BOMB_MECH_M7_BOSS_TURN_TO_TARGET = 53,
    BOMB_MECH_M7_BOSS_TURN_WAIT_IDLE = 54,
    BOMB_MECH_M7_BOSS_TURN_START = 55,
    BOMB_MECH_M7_BOSS_TURN_WAIT = 56,
    BOMB_MECH_M7_BOSS_TURN_DONE = 57,
    BOMB_MECH_M7_BOSS_PLAYER_BELOW_CHECK = 58,
    BOMB_MECH_M7_BOSS_TURN_TO_PLAYER_CHECK = 59,
    BOMB_MECH_M7_BOSS_PLAYER_BEYOND_CHECK = 60,
    BOMB_MECH_M7_BOSS_BOMBS_THEN_PAUSE = 61,
    BOMB_MECH_M7_BOSS_ATTACK_FIRE = 62,
    BOMB_MECH_M7_BOSS_ATTACK_CHOOSE_A = 63,
    BOMB_MECH_M7_BOSS_ATTACK_CHOOSE_B = 64,
    BOMB_MECH_M7_BOSS_ATTACK_CHOOSE_C = 65,
    BOMB_MECH_M7_BOSS_ATTACK_CHOOSE_D = 66,
    BOMB_MECH_M7_BOSS_ATTACK_RETURN = 67,
    BOMB_MECH_M7_BOSS_SCAN_FAR = 68,
    BOMB_MECH_M7_BOSS_AIM_CHECK = 69,
    BOMB_MECH_M7_BOSS_AIM_JITTER = 70,
    BOMB_MECH_M7_BOSS_ATTACK_CHOOSE_E = 71,
    BOMB_MECH_M7_BOSS_ATTACK_CHOOSE_F = 72,
    BOMB_MECH_M7_BOSS_ATTACK_F_RETURN = 73,
    BOMB_MECH_M7_BOSS_FAR_RETURN = 74,
    BOMB_MECH_M7_BOSS_WALK_THEN_PAUSE = 75,
    BOMB_MECH_M7_BOSS_PAUSE_RETURN = 76,
    BOMB_MECH_M7_BOSS_PLAYER_SCAN = 77,
    BOMB_MECH_M7_BOSS_TURN_THEN_SCAN = 78,
};

/* D_8011C520: states */
enum {
    STATIONARY_ROCKET_LAUNCHER_STATE_IDLE = 0,
    STATIONARY_ROCKET_LAUNCHER_STATE_TRACK = 1,
    STATIONARY_ROCKET_LAUNCHER_STATE_FIRE = 2,
    STATIONARY_ROCKET_LAUNCHER_STATE_LAUNCH = 3,
};

/* fuchikoma_state_table: states */
enum {
    FUCHIKOMA_STATE_STATE_IDLE = 0,
    FUCHIKOMA_STATE_STATE_CHASE = 1,
    FUCHIKOMA_STATE_STATE_DEAD = 2,
};

/* walker_state_table_alt: states */
enum {
    WALKER_MECH_STATE_IDLE = 0,
    WALKER_MECH_STATE_PATROL = 1,
    WALKER_MECH_STATE_ATTACK = 2,
};

/* helicopter2_states: states */
enum {
    HELICOPTER2_STATE_PATROL = 0,
    HELICOPTER2_STATE_ATTACK = 1,
    HELICOPTER2_STATE_HOVER = 2,
    HELICOPTER2_STATE_BANK_TURN = 3,
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

/* gun_turret_2_states: states */
enum {
    GUN_TURRET_2_STATE_IDLE = 0,
    GUN_TURRET_2_STATE_TRACK = 1,
    GUN_TURRET_2_STATE_FIRE = 2,
};

/* rocket_fuchikoma_state_table: states */
enum {
    GRENADE_FUCHIKOMA_STATE_IDLE = 0,
    GRENADE_FUCHIKOMA_STATE_FLY = 1,
    GRENADE_FUCHIKOMA_STATE_DETONATE = 2,
};

/* D_8011DEA8: states */
enum {
    BOMB_MECH_M7_BOSS_STATE_IDLE = 0,
    BOMB_MECH_M7_BOSS_STATE_WALK = 1,
    BOMB_MECH_M7_BOSS_STATE_TURN = 2,
    BOMB_MECH_M7_BOSS_STATE_HOLD = 4,
    BOMB_MECH_M7_BOSS_STATE_EMERGE = 5,
    BOMB_MECH_M7_BOSS_STATE_BOMB_PASS = 6,
    BOMB_MECH_M7_BOSS_STATE_CROUCH = 10,
    BOMB_MECH_M7_BOSS_STATE_RISE = 11,
    BOMB_MECH_M7_BOSS_STATE_FALL = 12,
    BOMB_MECH_M7_BOSS_STATE_LAND = 13,
    BOMB_MECH_M7_BOSS_STATE_FOLD = 14,
    BOMB_MECH_M7_BOSS_STATE_FLY = 15,
    BOMB_MECH_M7_BOSS_STATE_UNFOLD = 16,
};

/* D_8011C508: the ops of stationary_rocket_launcher_spawn */
enum {
    STATIONARY_ROCKET_LAUNCHER_JUMP_IF_WITHIN_DIST = 1, /* script_op_jump_if_within_dist */
    STATIONARY_ROCKET_LAUNCHER_JUMP_IF_PLAYER_IN_CONE = 2, /* script_op_jump_if_player_in_cone */
};

/* fuchikoma_call_table: the ops of fn_s07_800BAE10 */
enum {
    FUCHIKOMA_JUMP_IF_WITHIN_RANGE = 1, /* script_jump_if_within_range */
    FUCHIKOMA_JUMP_IF_PLAYER_IN_RANGE = 2, /* script_op_jump_if_player_in_range */
    FUCHIKOMA_JUMP_IF_FLAG_IN_RANGE = 3, /* script_op_jump_if_flag_in_range */
    FUCHIKOMA_JUMP_IF_IN_RANGE = 4, /* script_op_jump_if_in_range */
    FUCHIKOMA_JUMP_NEAR_CORNER = 5, /* script_jump_near_corner */
    FUCHIKOMA_READ_SPEED = 6, /* obj_script_read_speed */
    FUCHIKOMA_SET_ENEMY_SOUND = 7, /* script_op_set_enemy_sound */
    FUCHIKOMA_READ_S32 = 8, /* obj_script_read_s32 */
    FUCHIKOMA_ENEMY_RETARGET_JITTER = 9, /* enemy_retarget_jitter */
    FUCHIKOMA_AIM_AND_TRACK = 10, /* script_op_aim_and_track */
    FUCHIKOMA_READ_JUMP = 11, /* obj_script_read_jump */
    FUCHIKOMA_JUMP_IF_PLAYER_IN_RADIUS = 12, /* script_jump_if_player_in_radius */
    FUCHIKOMA_JUMP_IF_PLAYER_FAR = 13, /* script_jump_if_player_far */
    FUCHIKOMA_SET_MODE = 14, /* script_op_set_mode */
    FUCHIKOMA_JUMP_IF_MODE = 15, /* script_jump_if_mode */
};

/* script_handler_table: the ops of walker_mech_spawn */
enum {
    WALKER_MECH_JUMP_IF_FLAG_SET = 1, /* script_jump_if_flag_set */
    WALKER_MECH_SET_PATROL_PHASE = 2, /* script_set_patrol_phase */
    WALKER_MECH_JUMP_IF_KEY = 3, /* obj_script_jump_if_key */
};

/* helicopter2_script_calls: the ops of helicopter2_spawn */
enum {
    HELICOPTER2_SPEED_APPROACH = 1, /* obj_speed_approach */
    HELICOPTER2_SET_NEXT_STATE = 2, /* obj_set_next_state */
    HELICOPTER2_SET_TURN_MODE = 3, /* script_set_turn_mode */
    HELICOPTER2_JUMP_IF_PLAYER_NEAR = 4, /* obj_jump_if_player_near */
    HELICOPTER2_JUMP_TABLE_IF_PLAYER_FAR = 5, /* script_op_jump_table_if_player_far */
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

/* gun_turret_2_calls: the ops of gun_turret_2_spawn */
enum {
    GUN_TURRET_2_JUMP_WITHIN = 1, /* obj_script_jump_within */
    GUN_TURRET_2_BRANCH_IF_AIMED = 2, /* turret_branch_if_aimed */
};

/* script_call_table: the ops of grenade_fuchikoma_spawn */
enum {
    GRENADE_FUCHIKOMA_JUMP_NEAR = 1, /* script_jump_near */
    GRENADE_FUCHIKOMA_READ_SPEED_LONG = 2, /* script_read_speed_long */
    GRENADE_FUCHIKOMA_READ_S32 = 3, /* obj_read_s32 */
    GRENADE_FUCHIKOMA_READ_LONG = 4, /* script_read_long */
    GRENADE_FUCHIKOMA_AIM_JITTERED = 5, /* obj_aim_jittered */
    GRENADE_FUCHIKOMA_FACE_PLAYER = 6, /* obj_face_player */
    GRENADE_FUCHIKOMA_BRANCH_ON_FLAG = 7, /* script_branch_on_flag */
    GRENADE_FUCHIKOMA_JUMP_IF_NOT_BELOW_SPEED = 8, /* script_jump_if_not_below_speed */
    GRENADE_FUCHIKOMA_JUMP_NEAR_PLAYER = 9, /* script_jump_near_player */
    GRENADE_FUCHIKOMA_JUMP_IF_BEYOND_RADIUS = 10, /* script_jump_if_beyond_radius */
    GRENADE_FUCHIKOMA_JUMP_IF_FACING_PLAYER_IN_RADIUS = 11, /* script_jump_if_facing_player_in_radius */
};

/* D_8011D7F0: the ops of bomb_mech_m7_boss_spawn */
enum {
    BOMB_MECH_M7_BOSS_SKIP_HALFWORD = 1, /* script_op_skip_halfword */
    BOMB_MECH_M7_BOSS_JUMP_IF_PLAYER_WITHIN = 2, /* script_op_jump_if_player_within */
    BOMB_MECH_M7_BOSS_JUMP_IF_PLAYER_BEYOND = 3, /* script_op_jump_if_player_beyond */
    BOMB_MECH_M7_BOSS_TURN_TO_PLAYER_JUMP = 4, /* script_turn_to_player_jump */
    BOMB_MECH_M7_BOSS_JUMP_IF_OUTSIDE_BOUNDS = 5, /* script_op_jump_if_outside_bounds */
    BOMB_MECH_M7_BOSS_CASE_MATCH = 6, /* script_case_match */
    BOMB_MECH_M7_BOSS_JUMP_IF_FLAG_1B7 = 7, /* script_op_jump_if_flag_1b7 */
    BOMB_MECH_M7_BOSS_JUMP_IF_PLAYER_CLOSE = 8, /* script_op_jump_if_player_close */
    BOMB_MECH_M7_BOSS_SET_ENEMY_VAR = 9, /* script_set_enemy_var */
    BOMB_MECH_M7_BOSS_SET_VY = 10, /* script_op_set_vy */
    BOMB_MECH_M7_BOSS_JUMP_IF_VY_NONNEG = 11, /* script_op_jump_if_vy_nonneg */
    BOMB_MECH_M7_BOSS_VALUE_QUEUE_PUSH = 12, /* script_value_queue_push */
    BOMB_MECH_M7_BOSS_VALUE_QUEUE_POP = 13, /* value_queue_pop */
    BOMB_MECH_M7_BOSS_HELI_FIRE_BOMBS = 14, /* heli_fire_bombs */
    BOMB_MECH_M7_BOSS_FLY_EMITTER_UPDATE = 15, /* fly_emitter_update */
    BOMB_MECH_M7_BOSS_JITTER_UPDATE = 16, /* obj_jitter_update */
    BOMB_MECH_M7_BOSS_NOP = 17, /* obj_nop */
    BOMB_MECH_M7_BOSS_TIMER_REVERSE = 18, /* script_timer_reverse */
    BOMB_MECH_M7_BOSS_JUMP_TABLE_COND = 19, /* script_jump_table_cond */
    BOMB_MECH_M7_BOSS_STORE_ENEMY_HALFWORD = 20, /* script_store_enemy_halfword */
    BOMB_MECH_M7_BOSS_LOOP_SET_COUNT = 21, /* script_loop_set_count */
    BOMB_MECH_M7_BOSS_LOOP_NEXT = 22, /* script_loop_next */
    BOMB_MECH_M7_BOSS_SPAWN_MUZZLE_FLASH = 23, /* obj_spawn_muzzle_flash */
    BOMB_MECH_M7_BOSS_SPAWN_MODEL_PARTS = 24, /* script_spawn_model_parts */
    BOMB_MECH_M7_BOSS_CLEAR_MODEL_PARTS = 25, /* script_clear_model_parts */
    BOMB_MECH_M7_BOSS_MODE_KEYFRAME_ENABLE = 26, /* mode_keyframe_enable */
    BOMB_MECH_M7_BOSS_MODE_RESET = 27, /* mode_reset */
    BOMB_MECH_M7_BOSS_KEYTRACK_START = 28, /* obj_keytrack_start */
    BOMB_MECH_M7_BOSS_SHOOT_AT_PLAYER = 29, /* script_shoot_at_player */
    BOMB_MECH_M7_BOSS_ENABLE = 30, /* obj_enable */
    BOMB_MECH_M7_BOSS_DISABLE = 31, /* obj_disable */
    BOMB_MECH_M7_BOSS_ROLL_SET = 32, /* obj_roll_set */
    BOMB_MECH_M7_BOSS_BRANCH_IF_ROLL = 33, /* script_branch_if_roll */
    BOMB_MECH_M7_BOSS_BRANCH_IF_REPEAT = 34, /* script_branch_if_repeat */
    BOMB_MECH_M7_BOSS_START_POSITIONAL_SOUND = 35, /* obj_start_positional_sound */
    BOMB_MECH_M7_BOSS_RAMP_DISPATCH = 36, /* obj_ramp_dispatch */
    BOMB_MECH_M7_BOSS_SOUND_START_A = 37, /* obj_sound_start_a */
    BOMB_MECH_M7_BOSS_STOP_HELD_SOUND = 38, /* obj_stop_held_sound */
    BOMB_MECH_M7_BOSS_SOUND_START_B = 39, /* obj_sound_start_b */
    BOMB_MECH_M7_BOSS_SOUND_STOP_B = 40, /* obj_sound_stop_b */
    BOMB_MECH_M7_BOSS_SET_TARGET_YAW = 41, /* script_set_target_yaw */
    BOMB_MECH_M7_BOSS_BRANCH_IF_FLAG = 42, /* script_branch_if_flag */
    BOMB_MECH_M7_BOSS_READ_WALK_STATE = 43, /* script_read_walk_state */
    BOMB_MECH_M7_BOSS_JUMP_IF_PLAYER_BELOW = 44, /* script_jump_if_player_below */
};

#endif
