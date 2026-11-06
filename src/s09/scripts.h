/* s09: names for the script streams' table indices and op numbers, made by scripts/script_c.py
   from the stage's script data (FINDINGS "Script system"). */

#ifndef SCRIPTS_H
#define SCRIPTS_H

/* heavy_mobile_suit_data: animation streams */
enum {
    HEAVY_MOBILE_SUIT_SCRIPT = 0,
    HEAVY_MOBILE_SUIT_ANIM_PATROL_ENTER = 1,
    HEAVY_MOBILE_SUIT_ANIM_SEARCH_HOLD = 2,
    HEAVY_MOBILE_SUIT_ANIM_SEARCH_END = 3,
    HEAVY_MOBILE_SUIT_ANIM_ALT_ENTER = 4,
    HEAVY_MOBILE_SUIT_ANIM_ALT_HOLD = 5,
    HEAVY_MOBILE_SUIT_ANIM_ALT_END = 6,
    HEAVY_MOBILE_SUIT_ANIM_SPOTTED_ENTER = 7,
    HEAVY_MOBILE_SUIT_ANIM_PURSUE_ENTER = 8,
    HEAVY_MOBILE_SUIT_ANIM_PURSUE_ALT_ENTER = 9,
    HEAVY_MOBILE_SUIT_ANIM_APPROACH_HOLD = 10,
    HEAVY_MOBILE_SUIT_ANIM_FIRE_ENTER = 11,
    HEAVY_MOBILE_SUIT_ANIM_DISENGAGE = 12,
};

/* heavy_mobile_suit_script_data: behaviour streams */
enum {
    HEAVY_MOBILE_SUIT_PLACE_SELECT = 0,
    HEAVY_MOBILE_SUIT_PLACE_FAR_AIM = 1,
    HEAVY_MOBILE_SUIT_PLACE_SPOTTED = 2,
    HEAVY_MOBILE_SUIT_PLACE_IDLE = 3,
    HEAVY_MOBILE_SUIT_PLACE_IDLE_LOOP = 4,
    HEAVY_MOBILE_SUIT_PLACE_FIRE_START = 5,
    HEAVY_MOBILE_SUIT_PLACE_FIRE_START_LOOP = 6,
    HEAVY_MOBILE_SUIT_PLACE_CHASE = 7,
    HEAVY_MOBILE_SUIT_PLACE_CHASE_WAIT = 8,
    HEAVY_MOBILE_SUIT_PLACE_CHASE_PURSUE = 9,
    HEAVY_MOBILE_SUIT_PLACE_CHASE_PURSUE_LOOP = 10,
    HEAVY_MOBILE_SUIT_PLACE_CHASE_END = 11,
    HEAVY_MOBILE_SUIT_PLACE_FIRE_AIM = 12,
    HEAVY_MOBILE_SUIT_PLACE_FIRE_AIM_LOOP = 13,
    HEAVY_MOBILE_SUIT_PLACE_AIM_CHASE = 14,
    HEAVY_MOBILE_SUIT_PLACE_AIM_CHASE_LOOP = 15,
    HEAVY_MOBILE_SUIT_PLACE_AIM_PURSUE = 16,
    HEAVY_MOBILE_SUIT_PLACE_AIM_PURSUE_LOOP = 17,
    HEAVY_MOBILE_SUIT_PLACE_AIM_END = 18,
    HEAVY_MOBILE_SUIT_PLACE_AIM_FIRE = 19,
    HEAVY_MOBILE_SUIT_PLACE_AIM_FIRE_LOOP = 20,
    HEAVY_MOBILE_SUIT_PLACE_FIRE_BURST = 21,
    HEAVY_MOBILE_SUIT_PLACE_FIRE_BURST_LOOP = 22,
    HEAVY_MOBILE_SUIT_PLACE_COOLDOWN = 23,
    HEAVY_MOBILE_SUIT_PLACE_COOLING = 24,
    HEAVY_MOBILE_SUIT_PLACE_DISENGAGE = 25,
    HEAVY_MOBILE_SUIT_PLACE_DISENGAGE_LOOP = 26,
    HEAVY_MOBILE_SUIT_PLACE_SETTLE = 27,
    HEAVY_MOBILE_SUIT_PLACE_RESTART = 28,
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

/* triple_barrel_robot_data: animation streams */
enum {
    TRIPLE_BARREL_ROBOT_ANIM_IDLE = 0,
    TRIPLE_BARREL_ROBOT_ANIM_FIRE = 1,
    TRIPLE_BARREL_ROBOT_ANIM_WALK = 2,
};

/* triple_barrel_robot_script_table: behaviour streams */
enum {
    WALKER_MECH_BEGIN = 0,
    WALKER_MECH_PATROL_START = 1,
    WALKER_MECH_WATCH = 2,
    WALKER_MECH_ENGAGE_WAIT = 3,
    WALKER_MECH_ENGAGE = 4,
    TRIPLE_BARREL_ROBOT_FIRE_END = 5,
    TRIPLE_BARREL_ROBOT_COOLDOWN = 6,
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

/* gun_turret_data: animation streams */
enum {
    GUN_TURRET_ANIM_IDLE = 0,
};

/* gun_turret_link_data: behaviour streams */
enum {
    GUN_TURRET_IDLE = 0,
    GUN_TURRET_SPOTTED = 1,
    GUN_TURRET_AIM = 2,
    GUN_TURRET_FIRE_CHECK = 3,
    GUN_TURRET_FIRE_START = 4,
    GUN_TURRET_COOLDOWN = 5,
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

/* reactor_boss_script_data: behaviour streams */
enum {
    REACTOR_CONTROL_RODS_M9_BOSS_START = 0,
    REACTOR_CONTROL_RODS_M9_BOSS_IDLE = 1,
};

/* pylon_data: animation streams */
enum {
    PYLON_ANIM_IDLE = 0,
    PYLON_ANIM_OPEN = 1,
    PYLON_ANIM_OPEN_LOOP = 2,
    PYLON_ANIM_CHARGE = 3,
    PYLON_ANIM_CHARGE_LOOP = 4,
    PYLON_ANIM_DEATH = 5,
    PYLON_ANIM_DEAD = 6,
};

/* pylon_script_data: behaviour streams */
enum {
    PYLON_LINK_SCRIPT = 0,
    PYLON_DEATH = 1,
    PYLON_DEATH_DELAY = 2,
    PYLON_DEATH_SOUND = 3,
    PYLON_DEAD_WAIT = 4,
    PYLON_DEAD_IDLE = 5,
};

/* part_scripts: animation streams */
enum {
    SPAWN_PART_ANIM_IDLE = 0,
};

/* D_8011CEA8: behaviour streams */
enum {
    SPAWN_PART_AWAIT_BOSS = 0,
    SPAWN_PART_HOVER = 1,
    SPAWN_PART_HOVER_SCAN = 2,
    SPAWN_PART_TRACK = 3,
    SPAWN_PART_TRACK_FIRE = 4,
    SPAWN_PART_LASER_HOLD = 5,
};

/* D_8011BE10: states */
enum {
    HEAVY_MOBILE_SUIT_PLACE_STATE_IDLE = 0,
    HEAVY_MOBILE_SUIT_PLACE_STATE_CHASE = 1,
    HEAVY_MOBILE_SUIT_PLACE_STATE_FIRE = 3,
    HEAVY_MOBILE_SUIT_PLACE_STATE_COOLDOWN = 11,
};

/* fuchikoma_state_table: states */
enum {
    FUCHIKOMA_STATE_STATE_IDLE = 0,
    FUCHIKOMA_STATE_STATE_CHASE = 1,
    FUCHIKOMA_STATE_STATE_DEAD = 2,
};

/* triple_barrel_robot_state_table: states */
enum {
    TRIPLE_BARREL_ROBOT_STATE_PATROL = 1,
    TRIPLE_BARREL_ROBOT_STATE_FIRE = 2,
};

/* rocket_drone_state_table: states */
enum {
    ROCKET_DRONE_STATE_PATROL = 0,
    ROCKET_DRONE_STATE_TRACK = 1,
};

/* gun_turret_states: states */
enum {
    GUN_TURRET_STATE_IDLE = 0,
    GUN_TURRET_STATE_TRACK = 1,
    GUN_TURRET_STATE_FIRE = 2,
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

/* pylon_state_table: states */
enum {
    PYLON_SPAWN_CHILD_STATE_IDLE = 0,
    PYLON_SPAWN_CHILD_STATE_DEATH = 1,
    PYLON_SPAWN_CHILD_STATE_DEATH_DELAY = 2,
    PYLON_SPAWN_CHILD_STATE_DEATH_SOUND = 3,
    PYLON_SPAWN_CHILD_STATE_DEATH_SOUND_WAIT = 4,
    PYLON_SPAWN_CHILD_STATE_DEATH_SOUND_STOP = 5,
    PYLON_SPAWN_CHILD_STATE_DEAD = 6,
};

/* D_8011CEF4: states */
enum {
    OBJ_SPAWN_PART_STATE_HOVER = 0,
    OBJ_SPAWN_PART_STATE_TRACK = 1,
};

/* D_8011BDB8: the ops of heavy_mobile_suit_place */
enum {
    HEAVY_MOBILE_SUIT_PLACE_SET_SOUND = 1, /* obj_script_set_sound */
    HEAVY_MOBILE_SUIT_PLACE_READ_U16_2 = 2, /* obj_script_read_u16 */
    HEAVY_MOBILE_SUIT_PLACE_SET_FLY_MODE = 3, /* obj_script_set_fly_mode */
    HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_WITHIN = 4, /* obj_script_jump_if_within */
    HEAVY_MOBILE_SUIT_PLACE_JUMP_IF_BEYOND = 5, /* obj_script_jump_if_beyond */
    HEAVY_MOBILE_SUIT_PLACE_READ_U16_6 = 6, /* script_op_read_u16 */
    HEAVY_MOBILE_SUIT_PLACE_SET_258 = 7, /* obj_script_set_258 */
    HEAVY_MOBILE_SUIT_PLACE_SWITCH = 8, /* script_op_switch */
    HEAVY_MOBILE_SUIT_PLACE_DISPATCH = 9, /* script_dispatch */
    HEAVY_MOBILE_SUIT_PLACE_PLAY_SOUND_HERE = 10, /* obj_play_sound_here */
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

/* triple_barrel_robot_call_table: the ops of triple_barrel_robot_spawn */
enum {
    TRIPLE_BARREL_ROBOT_BRANCH = 1, /* obj_script_branch */
    TRIPLE_BARREL_ROBOT_READ_ARG = 2, /* obj_script_read_arg */
    TRIPLE_BARREL_ROBOT_JUMP_IF_KEY = 3, /* obj_script_jump_if_key */
};

/* rocket_drone_call_table: the ops of rocket_drone_spawn */
enum {
    ROCKET_DRONE_SPEED_APPROACH = 1, /* obj_speed_approach */
    ROCKET_DRONE_SET_NEXT_STATE = 2, /* obj_set_next_state */
    ROCKET_DRONE_SET_TURN_MODE = 3, /* script_set_turn_mode */
    ROCKET_DRONE_JUMP_IF_PLAYER_NEAR = 4, /* obj_jump_if_player_near */
    ROCKET_DRONE_STREAM_BRANCH = 5, /* obj_stream_branch */
};

/* gun_turret_call_table: the ops of gun_turret_spawn */
enum {
    GUN_TURRET_BRANCH_IF_NEAR_PLAYER = 1, /* script_branch_if_near_player */
    GUN_TURRET_JUMP_IF_FACING_PLAYER = 2, /* script_op_jump_if_facing_player */
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

/* reactor_boss_table: the ops of reactor_control_rods_m9_boss_spawn */
enum {
    REACTOR_CONTROL_RODS_M9_BOSS_STAGE_ENGINE_INIT = 1, /* stage_engine_init */
};

/* pylon_call_table: the ops of pylon_spawn_child */
enum {
    PYLON_SPAWN_CHILD_STREAM_READ_OP = 1, /* obj_stream_read_op */
    PYLON_SPAWN_CHILD_ENEMY_KILL = 2, /* enemy_kill */
};

/* D_8011CEC4: the ops of obj_spawn_part */
enum {
    OBJ_SPAWN_PART_BOSS_LASER_INIT = 1, /* obj_boss_laser_init */
    OBJ_SPAWN_PART_JUMP_LINKED = 2, /* obj_script_jump_linked */
    OBJ_SPAWN_PART_JUMP_ON_FLAG = 3, /* obj_script_jump_on_flag */
    OBJ_SPAWN_PART_JUMP_FAR = 4, /* obj_script_jump_far */
    OBJ_SPAWN_PART_JUMP_NEAR = 5, /* obj_script_jump_near */
};

#endif
