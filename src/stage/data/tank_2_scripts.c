/* Data shared by s06, s07, s09: scripts/stage_data.py. */

struct Tank2Scripts {
    s16 init[10];
    s16 patrol_start[6];
    s16 patrol[12];
    s16 stop[2];
    s16 stop_wait[8];
    s16 spotted[4];
    s16 chase[16];
    s16 engage[10];
    s16 aim[14];
    s16 turn_to_player[6];
    s16 turn_wait[12];
    s16 face_wait[6];
    s16 halt[2];
    s16 fire_ready[8];
    s16 fire_start[4];
    s16 fire_loop[8];
    s16 fire_cooldown[6];
    s16 static_init[6];
    s16 static_watch[8];
    s16 static_spotted[2];
    s16 static_chase[10];
    s16 static_engage[8];
    s16 static_aim[12];
    s16 static_turn_to_player[4];
    s16 static_turn_wait[12];
    s16 static_face_wait[6];
    s16 static_fire_start[4];
    s16 static_fire_loop[8];
    s16 static_fire_cooldown[6];
    s16 pursue_watch[8];
    s16 pursue_spotted[2];
    s16 pursue_chase[10];
    s16 pursue_angle_check[4];
    s16 pursue_turn_to_player[4];
    s16 pursue_turn_wait[12];
    s16 pursue_face_wait[6];
    s16 *table[36];
    s16 *tank2_variant_words[3];
} tank_2_scripts = {
    /* init */ {
        TANK_SET_SPEED, 0, 0,
        TANK_READ_S32, 28672, 0,
        TANK_SET_UNK_234, 682, 0,
    },
    /* patrol_start */ {
        NEXT_STATE(TANK_STATE_TURN),
        TANK_RETARGET,
        SET_COUNTER(720),
    },
    /* patrol */ {
        WAIT(1),
        TANK_JUMP_IF_PLAYER_NEAR, 2000, TANK_2_SPOTTED,
        TANK_JUMP_TABLE, TANK_2_STOP,
        LOOP(TANK_2_PATROL),
        JUMP(TANK_2_PATROL_START),
    },
    /* stop */ {
        NEXT_STATE(TANK_STATE_STOP),
    },
    /* stop_wait */ {
        WAIT(1),
        JUMP_IF_STATE(TANK_STATE_IDLE, TANK_2_PATROL_START),
        JUMP(TANK_2_STOP_WAIT),
    },
    /* spotted */ {
        TANK_RETARGET,
        NEXT_STATE(TANK_STATE_TRACK),
    },
    /* chase */ {
        WAIT(1),
        TANK_JUMP_IF_PLAYER_FAR, 2000, TANK_2_PATROL_START,
        WAIT(1),
        TANK_JUMP_IF_PLAYER_IN_VIEW, 800, TANK_2_ENGAGE,
        WAIT(1),
        TANK_JUMP_TABLE, TANK_2_SPOTTED,
        JUMP(TANK_2_CHASE),
    },
    /* engage */ {
        TANK_JUMP_IF_PLAYER_NEAR, 750, TANK_2_TURN_TO_PLAYER,
        WAIT(1),
        TANK_JUMP_IF_IN_CELL_CORNER, 1024, TANK_2_AIM,
        JUMP(TANK_2_CHASE),
    },
    /* aim */ {
        WAIT(1),
        TANK_JUMP_IF_NEAR_PLAYER_IN_VIEW, 1500, 800, TANK_2_TURN_TO_PLAYER,
        WAIT(1),
        TANK_JUMP_IF_NEAR_PLAYER_IN_VIEW, 2000, 128, TANK_2_HALT,
        JUMP(TANK_2_SPOTTED),
    },
    /* turn_to_player */ {
        NEXT_STATE(TANK_STATE_FACE_PLAYER),
        TANK_RETARGET,
        SET_COUNTER(90),
    },
    /* turn_wait */ {
        WAIT(1),
        JUMP_IF_STATE(TANK_STATE_IDLE, TANK_2_SPOTTED),
        LOOP(TANK_2_TURN_WAIT),
        NEXT_STATE(TANK_STATE_TRACK),
        SET_COUNTER(30),
    },
    /* face_wait */ {
        WAIT(1),
        LOOP(TANK_2_FACE_WAIT),
        JUMP(TANK_2_SPOTTED),
    },
    /* halt */ {
        NEXT_STATE(TANK_STATE_STOP),
    },
    /* fire_ready */ {
        WAIT(1),
        JUMP_IF_STATE(TANK_STATE_IDLE, TANK_2_FIRE_START),
        JUMP(TANK_2_FIRE_READY),
    },
    /* fire_start */ {
        NEXT_STATE(TANK_STATE_FIRE),
        SET_COUNTER(60),
    },
    /* fire_loop */ {
        WAIT(1),
        LOOP(TANK_2_FIRE_LOOP),
        NEXT_STATE(TANK_STATE_TRACK),
        SET_COUNTER(60),
    },
    /* fire_cooldown */ {
        WAIT(1),
        LOOP(TANK_2_FIRE_COOLDOWN),
        JUMP(TANK_2_SPOTTED),
    },
    /* static_init */ {
        TANK_READ_S32, 0, 0,
        TANK_SET_SPEED, 0, 0,
    },
    /* static_watch */ {
        WAIT(1),
        TANK_JUMP_IF_PLAYER_NEAR, 2000, TANK_2_STATIC_SPOTTED,
        JUMP(TANK_2_STATIC_WATCH),
    },
    /* static_spotted */ {
        NEXT_STATE(TANK_STATE_TRACK),
    },
    /* static_chase */ {
        WAIT(1),
        TANK_JUMP_IF_PLAYER_FAR, 2000, TANK_2_STATIC_WATCH,
        TANK_JUMP_IF_PLAYER_IN_VIEW, 800, TANK_2_STATIC_ENGAGE,
        JUMP(TANK_2_STATIC_CHASE),
    },
    /* static_engage */ {
        TANK_JUMP_IF_PLAYER_NEAR, 750, TANK_2_STATIC_TURN_TO_PLAYER,
        TANK_JUMP_IF_IN_CELL_CORNER, 1024, TANK_2_STATIC_AIM,
        JUMP(TANK_2_STATIC_CHASE),
    },
    /* static_aim */ {
        WAIT(1),
        TANK_JUMP_IF_NEAR_PLAYER_IN_VIEW, 1500, 800, TANK_2_STATIC_TURN_TO_PLAYER,
        TANK_JUMP_IF_NEAR_PLAYER_IN_VIEW, 2000, 128, TANK_2_STATIC_FIRE_START,
        JUMP(TANK_2_STATIC_SPOTTED),
    },
    /* static_turn_to_player */ {
        NEXT_STATE(TANK_STATE_FACE_PLAYER),
        SET_COUNTER(90),
    },
    /* static_turn_wait */ {
        WAIT(1),
        JUMP_IF_STATE(TANK_STATE_IDLE, TANK_2_STATIC_SPOTTED),
        LOOP(TANK_2_STATIC_TURN_WAIT),
        NEXT_STATE(TANK_STATE_TRACK),
        SET_COUNTER(15),
    },
    /* static_face_wait */ {
        WAIT(1),
        LOOP(TANK_2_STATIC_FACE_WAIT),
        JUMP(TANK_2_STATIC_SPOTTED),
    },
    /* static_fire_start */ {
        NEXT_STATE(TANK_STATE_FIRE),
        SET_COUNTER(60),
    },
    /* static_fire_loop */ {
        WAIT(1),
        LOOP(TANK_2_STATIC_FIRE_LOOP),
        NEXT_STATE(TANK_STATE_TRACK),
        SET_COUNTER(60),
    },
    /* static_fire_cooldown */ {
        WAIT(1),
        LOOP(TANK_2_STATIC_FIRE_COOLDOWN),
        JUMP(TANK_2_STATIC_SPOTTED),
    },
    /* pursue_watch */ {
        TANK_JUMP_IF_PLAYER_NEAR, 2000, TANK_2_PURSUE_SPOTTED,
        WAIT(1),
        JUMP(TANK_2_PURSUE_WATCH),
    },
    /* pursue_spotted */ {
        NEXT_STATE(TANK_STATE_TRACK),
    },
    /* pursue_chase */ {
        WAIT(1),
        TANK_JUMP_IF_PLAYER_FAR, 2000, TANK_2_PURSUE_WATCH,
        TANK_JUMP_IF_PLAYER_IN_VIEW, 800, TANK_2_PURSUE_ANGLE_CHECK,
        JUMP(TANK_2_PURSUE_CHASE),
    },
    /* pursue_angle_check */ {
        TANK_PLAYER_ANGLE_BRANCH, TANK_2_PURSUE_TURN_TO_PLAYER,
        JUMP(TANK_2_PURSUE_CHASE),
    },
    /* pursue_turn_to_player */ {
        NEXT_STATE(TANK_STATE_FACE_PLAYER),
        SET_COUNTER(90),
    },
    /* pursue_turn_wait */ {
        WAIT(1),
        JUMP_IF_STATE(TANK_STATE_IDLE, TANK_2_PURSUE_SPOTTED),
        LOOP(TANK_2_PURSUE_TURN_WAIT),
        NEXT_STATE(TANK_STATE_TRACK),
        SET_COUNTER(15),
    },
    /* pursue_face_wait */ {
        WAIT(1),
        LOOP(TANK_2_PURSUE_FACE_WAIT),
        JUMP(TANK_2_PURSUE_SPOTTED),
    },
    /* table */ {
        tank_2_scripts.init, tank_2_scripts.patrol_start, tank_2_scripts.patrol, tank_2_scripts.stop, tank_2_scripts.stop_wait, tank_2_scripts.spotted,
        tank_2_scripts.chase, tank_2_scripts.engage, tank_2_scripts.aim, tank_2_scripts.turn_to_player, tank_2_scripts.turn_wait, tank_2_scripts.face_wait,
        tank_2_scripts.halt, tank_2_scripts.fire_ready, tank_2_scripts.fire_start, tank_2_scripts.fire_loop, tank_2_scripts.fire_cooldown, tank_2_scripts.static_init,
        tank_2_scripts.static_watch, tank_2_scripts.static_spotted, tank_2_scripts.static_chase, tank_2_scripts.static_engage, tank_2_scripts.static_aim, tank_2_scripts.static_turn_to_player,
        tank_2_scripts.static_turn_wait, tank_2_scripts.static_face_wait, tank_2_scripts.static_fire_start, tank_2_scripts.static_fire_loop, tank_2_scripts.static_fire_cooldown, tank_2_scripts.pursue_watch,
        tank_2_scripts.pursue_spotted, tank_2_scripts.pursue_chase, tank_2_scripts.pursue_angle_check, tank_2_scripts.pursue_turn_to_player, tank_2_scripts.pursue_turn_wait, tank_2_scripts.pursue_face_wait,
    },
    /* tank2_variant_words */ {
        tank_2_scripts.init, tank_2_scripts.static_init, tank_2_scripts.pursue_watch,
    },
};
