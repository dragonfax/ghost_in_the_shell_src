/* s11: names for the script streams' table indices and op numbers, made by scripts/script_c.py
   from the stage's script data (FINDINGS "Script system"). */

#ifndef SCRIPTS_H
#define SCRIPTS_H

/* moving_pyramid_mine_data: animation streams */
enum {
    MOVING_PYRAMID_MINE_SCRIPT_PC = 0,
};

/* moving_pyramid_mine_script_data: behaviour streams */
enum {
    MOVING_PYRAMID_MINE_INIT = 0,
    MOVING_PYRAMID_MINE_START = 1,
    PYRAMID_MINE_WATCH = 2,
    PYRAMID_MINE_DETONATE = 3,
};

/* ceiling_bomber_data: animation streams */
enum {
    CEILING_BOMBER_ANIM_IDLE = 0,
    CEILING_BOMBER_ANIM_CHARGE = 1,
    CEILING_BOMBER_ANIM_HOLD_CHARGED = 2,
    CEILING_BOMBER_ANIM_COOLDOWN = 3,
    CEILING_BOMBER_ANIM_REST = 4,
    CEILING_BOMBER_ANIM_HOLD_SMOKE = 5,
};

/* ceiling_bomber_script_data: behaviour streams */
enum {
    CEILING_BOMBER_IDLE = 0,
    CEILING_BOMBER_ARM = 1,
    CEILING_BOMBER_ARMING = 2,
    CEILING_BOMBER_CHARGE = 3,
    CEILING_BOMBER_CHARGING = 4,
    CEILING_BOMBER_SMOKE = 5,
    CEILING_BOMBER_SMOKING = 6,
    CEILING_BOMBER_COOL = 7,
    CEILING_BOMBER_COOLING = 8,
    CEILING_BOMBER_REST = 9,
    CEILING_BOMBER_RESTING = 10,
    CEILING_BOMBER_REARM = 11,
    CEILING_BOMBER_REARMING = 12,
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

/* D_8011A5B0: animation streams */
enum {
    FLIER_SCRIPT_PTR_ANIM_IDLE = 0,
};

/* placed_actor_script_value: animation streams */
enum {
    PLACED_ACTOR_SCRIPT = 0,
};

/* dreadnought_m11_boss_data: animation streams */
enum {
    DREADNOUGHT_M11_BOSS_SCRIPT = 0,
    DREADNOUGHT_M11_BOSS_ANIM_RAMP_UP = 1,
    DREADNOUGHT_M11_BOSS_ANIM_HOVER = 2,
    DREADNOUGHT_M11_BOSS_ANIM_CHASE_FRONT = 3,
    DREADNOUGHT_M11_BOSS_ANIM_CHASE_LEFT = 4,
    DREADNOUGHT_M11_BOSS_ANIM_CHASE_BACK = 5,
    DREADNOUGHT_M11_BOSS_ANIM_CHASE_RIGHT = 6,
    DREADNOUGHT_M11_BOSS_ANIM_RETURN_REST = 7,
    DREADNOUGHT_M11_BOSS_ANIM_AIM = 8,
    DREADNOUGHT_M11_BOSS_ANIM_FIRE_MUZZLE = 9,
    DREADNOUGHT_M11_BOSS_ANIM_APPROACH = 10,
};

/* dreadnought_m11_script_data: behaviour streams */
enum {
    DREADNOUGHT_M11_BOSS_DISPATCH = 0,
    DREADNOUGHT_M11_BOSS_CHOOSE_ACTION = 1,
    DREADNOUGHT_M11_BOSS_IDLE = 2,
    DREADNOUGHT_M11_BOSS_IDLE_HOLD = 3,
    DREADNOUGHT_M11_BOSS_PATROL = 4,
    DREADNOUGHT_M11_BOSS_PATROL_WAIT = 5,
    DREADNOUGHT_M11_BOSS_CYCLE = 6,
    DREADNOUGHT_M11_BOSS_CYCLE_WAIT = 7,
    DREADNOUGHT_M11_BOSS_CHASE_BY_BEARING = 8,
    DREADNOUGHT_M11_BOSS_CHASE_FRONT = 9,
    DREADNOUGHT_M11_BOSS_CHASE_LEFT = 10,
    DREADNOUGHT_M11_BOSS_CHASE_BACK = 11,
    DREADNOUGHT_M11_BOSS_CHASE_RIGHT = 12,
    DREADNOUGHT_M11_BOSS_CHASE_WAIT = 13,
    DREADNOUGHT_M11_BOSS_DISENGAGE = 14,
    DREADNOUGHT_M11_BOSS_DISENGAGE_WAIT = 15,
    DREADNOUGHT_M11_BOSS_AIM = 16,
    DREADNOUGHT_M11_BOSS_AIM_HOLD = 17,
    DREADNOUGHT_M11_BOSS_FIRE_MUZZLE = 18,
    DREADNOUGHT_M11_BOSS_FIRE_MUZZLE_HOLD = 19,
    DREADNOUGHT_M11_BOSS_APPROACH = 20,
    DREADNOUGHT_M11_BOSS_APPROACH_HOLD = 21,
    DREADNOUGHT_M11_BOSS_IDLE_WAIT = 22,
    DREADNOUGHT_M11_BOSS_SETTLE = 23,
};

/* D_8011AEE4: animation streams */
enum {
    DAMAGE_RECORD_SCRIPT = 0,
};

/* damage_record_script_data: behaviour streams */
enum {
    DAMAGE_RECORD_CHASE = 0,
    DAMAGE_RECORD_CHASE_WAIT = 1,
    DAMAGE_RECORD_CHOOSE = 2,
    DAMAGE_RECORD_DECAY = 3,
    DAMAGE_RECORD_DECAY_WAIT = 4,
    DAMAGE_RECORD_FIRE = 5,
    DAMAGE_RECORD_FIRE_WAIT = 6,
    DAMAGE_RECORD_EJECT = 7,
    DAMAGE_RECORD_EJECT_WAIT = 8,
    DAMAGE_RECORD_HOVER = 9,
    DAMAGE_RECORD_HOVER_WAIT = 10,
    DAMAGE_RECORD_PAUSE = 11,
    DAMAGE_RECORD_RECHECK = 12,
};

/* D_80119F20: states */
enum {
    PYRAMID_MINE_STATE_ZIGZAG = 1,
    PYRAMID_MINE_STATE_BURST = 2,
};

/* D_8011A0F8: states */
enum {
    CEILING_BOMBER_STATE_IDLE = 0,
    CEILING_BOMBER_STATE_ARM = 1,
    CEILING_BOMBER_STATE_CHARGE = 2,
    CEILING_BOMBER_STATE_SMOKE = 3,
    CEILING_BOMBER_STATE_COOL = 4,
    CEILING_BOMBER_STATE_REST = 5,
    CEILING_BOMBER_STATE_DONE = 6,
};

/* fuchikoma_state_table: states */
enum {
    FUCHIKOMA_STATE_STATE_IDLE = 0,
    FUCHIKOMA_STATE_STATE_CHASE = 1,
    FUCHIKOMA_STATE_STATE_DEAD = 2,
};

/* gun_turret_2_states: states */
enum {
    GUN_TURRET_2_STATE_IDLE = 0,
    GUN_TURRET_2_STATE_TRACK = 1,
    GUN_TURRET_2_STATE_FIRE = 2,
};

/* D_8011ADE0: states */
enum {
    DREADNOUGHT_M11_BOSS_STATE_IDLE = 0,
    DREADNOUGHT_M11_BOSS_STATE_PATROL = 1,
    DREADNOUGHT_M11_BOSS_STATE_CYCLE_SPAWN = 2,
    DREADNOUGHT_M11_BOSS_STATE_CHASE_FRONT = 3,
    DREADNOUGHT_M11_BOSS_STATE_CHASE_LEFT = 4,
    DREADNOUGHT_M11_BOSS_STATE_CHASE_BACK = 5,
    DREADNOUGHT_M11_BOSS_STATE_CHASE_RIGHT = 6,
    DREADNOUGHT_M11_BOSS_STATE_DISENGAGE = 7,
    DREADNOUGHT_M11_BOSS_STATE_AIM = 8,
    DREADNOUGHT_M11_BOSS_STATE_FIRE_MUZZLE = 9,
    DREADNOUGHT_M11_BOSS_STATE_APPROACH = 10,
    DREADNOUGHT_M11_BOSS_STATE_DEATH = 11,
};

/* D_8011B020: states */
enum {
    DAMAGE_RECORD_STATE_CHASE = 0,
    DAMAGE_RECORD_STATE_DECAY = 1,
    DAMAGE_RECORD_STATE_FIRE = 2,
    DAMAGE_RECORD_STATE_EJECT = 3,
    DAMAGE_RECORD_STATE_HOVER = 4,
};

/* D_80119EF0: the ops of pyramid_mine_spawn */
enum {
    PYRAMID_MINE_SET_SPEED = 1, /* obj_script_set_speed */
    PYRAMID_MINE_READ_NEXT_STATE = 2, /* obj_script_read_next_state */
    PYRAMID_MINE_FN_800B7514 = 3, /* fn_800B7514 */
    PYRAMID_MINE_BRANCH_IF_NEAR = 4, /* obj_script_branch_if_near */
    PYRAMID_MINE_BRANCH_IF_FAR = 5, /* obj_script_branch_if_far */
};

/* D_8011A0E8: the ops of ceiling_bomber_spawn */
enum {
    CEILING_BOMBER_JUMP_IF_PLAYER_NEAR = 1, /* script_jump_if_player_near */
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

/* gun_turret_2_calls: the ops of gun_turret_2_spawn */
enum {
    GUN_TURRET_2_JUMP_WITHIN = 1, /* obj_script_jump_within */
    GUN_TURRET_2_BRANCH_IF_AIMED = 2, /* turret_branch_if_aimed */
};

/* D_8011AD58: the ops of dreadnought_m11_boss_spawn */
enum {
    DREADNOUGHT_M11_BOSS_READ_U16_VAR = 1, /* obj_script_read_u16_var */
    DREADNOUGHT_M11_BOSS_SET_NEXT_STATE = 2, /* script_set_next_state */
    DREADNOUGHT_M11_BOSS_FUNC_800BF730 = 3, /* func_800BF730 */
    DREADNOUGHT_M11_BOSS_JUMP_IF_PLAYER_WITHIN = 4, /* script_jump_if_player_within */
    DREADNOUGHT_M11_BOSS_BRANCH_BY_BEARING = 5, /* script_branch_by_bearing */
    DREADNOUGHT_M11_BOSS_DIR_STATE_PICK_NEW = 6, /* dir_state_pick_new */
    DREADNOUGHT_M11_BOSS_JUMP_IF_Z_IN_RANGE = 7, /* script_jump_if_z_in_range */
    DREADNOUGHT_M11_BOSS_REQUEST_MUZZLE_FX = 8, /* dreadnought_m11_request_muzzle_fx */
    DREADNOUGHT_M11_BOSS_CLEAR_SALVO_TIMER = 9, /* script_clear_salvo_timer */
    DREADNOUGHT_M11_BOSS_FUNC_800BFA80 = 10, /* func_800BFA80 */
    DREADNOUGHT_M11_BOSS_RESET = 11, /* dreadnought_m11_reset */
    DREADNOUGHT_M11_BOSS_RANDOMIZE_FLAG = 12, /* dreadnought_m11_randomize_flag */
    DREADNOUGHT_M11_BOSS_REQUEST_ATTACK = 13, /* dreadnought_m11_request_attack */
    DREADNOUGHT_M11_BOSS_BRANCH_ON_REPEAT = 14, /* script_branch_on_repeat */
    DREADNOUGHT_M11_BOSS_WALK_BEGIN = 15, /* dreadnought_m11_walk_begin */
    DREADNOUGHT_M11_BOSS_WALK_END = 16, /* dreadnought_m11_walk_end */
};

/* D_8011AFF8: the ops of damage_record_spawn */
enum {
    DAMAGE_RECORD_READ_SPEED = 1, /* script_read_speed */
    DAMAGE_RECORD_READ_STATE = 2, /* script_read_state */
    DAMAGE_RECORD_FUNC_800C6D68 = 3, /* func_800C6D68 */
    DAMAGE_RECORD_JUMP_IF_NEAR_PLAYER = 4, /* script_jump_if_near_player */
};

#endif
