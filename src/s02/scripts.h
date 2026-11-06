/* s02: names for the script streams' table indices and op numbers, made by scripts/script_c.py
   from the stage's script data (FINDINGS "Script system"). */

#ifndef SCRIPTS_H
#define SCRIPTS_H

/* enemy_data: animation streams */
enum {
    ENEMY_START_SCRIPT = 0,
    FLAMETHROWER_SOLDIER_ANIM_IDLE = 1,
    FLAMETHROWER_SOLDIER_ANIM_WALK_START = 2,
    FLAMETHROWER_SOLDIER_ANIM_WALK = 3,
    FLAMETHROWER_SOLDIER_ANIM_FIRE_START = 4,
    FLAMETHROWER_SOLDIER_ANIM_FIRE_LOOP = 5,
    FLAMETHROWER_SOLDIER_ANIM_STAND = 6,
    FLAMETHROWER_SOLDIER_ANIM_DEATH = 7,
};

/* flamethrower_soldier_jumps: behaviour streams */
enum {
    SMG_SOLDIER_IDLE = 0,
    SMG_SOLDIER_IDLE_PAUSE = 1,
    SMG_SOLDIER_IDLE_CYCLE = 2,
    SMG_SOLDIER_PATROL = 3,
    SMG_SOLDIER_PATROL_CYCLE = 4,
    SMG_SOLDIER_PATROL_WAIT = 5,
    SMG_SOLDIER_HOLD = 6,
    SMG_SOLDIER_HOLD_PAUSE = 7,
    SMG_SOLDIER_HOLD_CYCLE = 8,
    SMG_SOLDIER_WALK = 9,
    SMG_SOLDIER_WALK_STEP = 10,
    SMG_SOLDIER_WALK_CYCLE = 11,
    SMG_SOLDIER_WALK_PAUSE = 12,
    SMG_SOLDIER_WALK_PAUSE_CYCLE = 13,
};

/* rocket_drone_data: animation streams */
enum {
    ROCKET_DRONE_ANIM_IDLE = 0,
};

/* rocket_drone_anim: behaviour streams */
enum {
    ROCKET_DRONE_RESTART = 0,
    ROCKET_DRONE_SELECT = 1,
    ROCKET_DRONE_PATROL = 2,
    ROCKET_DRONE_SPOTTED = 3,
    ROCKET_DRONE_IDLE_START = 4,
    ROCKET_DRONE_IDLE = 5,
    ROCKET_DRONE_COOLDOWN = 6,
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

/* sea_mine_script_arg: animation streams */
enum {
    SEA_MINE_SCRIPT = 0,
};

/* placed_actor_script_value: animation streams */
enum {
    PLACED_ACTOR_SCRIPT = 0,
};

/* tunnel_mech_script: behaviour streams */
enum {
    TUNNEL_MECH_M2_BOSS_INTRO = 0,
    TUNNEL_MECH_M2_BOSS_DISPATCH = 1,
    TUNNEL_MECH_M2_BOSS_NEAR_CHECK = 2,
    TUNNEL_MECH_M2_BOSS_APPROACH = 3,
    TUNNEL_MECH_M2_BOSS_FIRE_CHECK = 4,
    TUNNEL_MECH_M2_BOSS_AIM = 5,
    TUNNEL_MECH_M2_BOSS_AIM_WAIT = 6,
    TUNNEL_MECH_M2_BOSS_ADVANCE = 7,
    TUNNEL_MECH_M2_BOSS_ADVANCE_WAIT = 8,
    TUNNEL_MECH_M2_BOSS_FALL_BACK = 9,
    TUNNEL_MECH_M2_BOSS_RETREAT_WAIT = 10,
    TUNNEL_MECH_M2_BOSS_FIRE_BURST = 11,
    TUNNEL_MECH_M2_BOSS_FIRE_LOOP = 12,
    TUNNEL_MECH_M2_BOSS_HALT = 13,
    TUNNEL_MECH_M2_BOSS_HALT_LOOP = 14,
    TUNNEL_MECH_M2_BOSS_PAUSE = 15,
    TUNNEL_MECH_M2_BOSS_RECHECK = 16,
};

/* D_80116B48: states */
enum {
    ENEMY_STATE_IDLE = 0,
    ENEMY_STATE_WAIT = 1,
    ENEMY_STATE_WANDER = 2,
    ENEMY_STATE_TRACK = 3,
    ENEMY_STATE_COOLDOWN = 4,
    ENEMY_STATE_FIRE = 5,
    ENEMY_STATE_RETREAT = 6,
};

/* rocket_drone_state_table: states */
enum {
    ROCKET_DRONE_STATE_PATROL = 0,
    ROCKET_DRONE_STATE_TRACK = 1,
};

/* gun_turret_2_states: states */
enum {
    GUN_TURRET_2_STATE_IDLE = 0,
    GUN_TURRET_2_STATE_TRACK = 1,
    GUN_TURRET_2_STATE_FIRE = 2,
};

/* tunnel_mech_script: states */
enum {
    TUNNEL_MECH_M2_BOSS_STATE_AIM = 0,
    TUNNEL_MECH_M2_BOSS_STATE_ADVANCE = 1,
    TUNNEL_MECH_M2_BOSS_STATE_FALL_BACK = 2,
    TUNNEL_MECH_M2_BOSS_STATE_FIRE = 3,
    TUNNEL_MECH_M2_BOSS_STATE_HALT = 4,
};

/* rocket_drone_call_table: the ops of rocket_drone_spawn */
enum {
    ROCKET_DRONE_SPEED_APPROACH = 1, /* obj_speed_approach */
    ROCKET_DRONE_SET_NEXT_STATE = 2, /* obj_set_next_state */
    ROCKET_DRONE_SET_TURN_MODE = 3, /* script_set_turn_mode */
    ROCKET_DRONE_JUMP_IF_PLAYER_NEAR = 4, /* obj_jump_if_player_near */
    ROCKET_DRONE_JUMP_TABLE_IF_PLAYER_FAR = 5, /* script_op_jump_table_if_player_far */
};

/* gun_turret_2_calls: the ops of gun_turret_2_spawn */
enum {
    GUN_TURRET_2_JUMP_WITHIN = 1, /* obj_script_jump_within */
    GUN_TURRET_2_BRANCH_IF_AIMED = 2, /* turret_branch_if_aimed */
};

/* D_80117314: the ops of tunnel_mech_m2_boss_spawn */
enum {
    TUNNEL_MECH_M2_BOSS_READ_SPEED = 1, /* script_read_speed */
    TUNNEL_MECH_M2_BOSS_SET_NEXT_STATE = 2, /* script_op_set_next_state */
    TUNNEL_MECH_M2_BOSS_READ_U16_FIELD = 3, /* script_read_u16_field */
    TUNNEL_MECH_M2_BOSS_BRANCH_IF_WITHIN = 4, /* script_branch_if_within */
    TUNNEL_MECH_M2_BOSS_BRANCH_IF_FAR = 5, /* script_branch_if_far */
    TUNNEL_MECH_M2_BOSS_JUMP_IF_ABOVE_Z = 6, /* script_jump_if_above_z */
    TUNNEL_MECH_M2_BOSS_JUMP_IF_BELOW_Z = 7, /* script_jump_if_below_z */
};

#endif
