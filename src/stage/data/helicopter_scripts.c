/* Data shared by s01, s12 (3 objects): scripts/stage_data.py. */

struct HelicopterScripts {
    s16 idle[2];
    s16 pick_state[20];
    s16 patrol[8];
    s16 patrol_far[8];
    s16 spin[8];
    s16 aim[8];
    s16 approach[8];
    s16 cooldown[4];
    s16 cooling[6];
    s16 cooldown_end[4];
    s16 *table[10];
    s16 *script_entry;
} helicopter_scripts = {
    /* idle */ {
        JUMP(HELICOPTER_PICK_STATE),
    },
    /* pick_state */ {
        HELICOPTER_JUMP_CLEAR_FLAG, HELICOPTER_PATROL,
        HELICOPTER_JUMP_TABLE_IF_PLAYER_FAR, 5000, HELICOPTER_PATROL_FAR,
        JUMP_IF_STATE(HELICOPTER_STATE_SPIN, HELICOPTER_SPIN),
        HELICOPTER_JUMP_IF_PLAYER_NEAR, 1900, HELICOPTER_AIM,
        HELICOPTER_JUMP_IF_PLAYER_NEAR, 2700, HELICOPTER_APPROACH,
        HELICOPTER_JUMP_IF_PLAYER_NEAR, 3000, HELICOPTER_PATROL,
        JUMP(HELICOPTER_PATROL_FAR),
    },
    /* patrol */ {
        HELICOPTER_SET_TURN_MODE, 0,
        HELICOPTER_SPEED_APPROACH, 10,
        HELICOPTER_SET_NEXT_STATE, HELICOPTER_STATE_MOVE,
        JUMP(HELICOPTER_COOLDOWN),
    },
    /* patrol_far */ {
        HELICOPTER_SET_TURN_MODE, 1,
        HELICOPTER_SPEED_APPROACH, 8,
        HELICOPTER_SET_NEXT_STATE, HELICOPTER_STATE_MOVE,
        JUMP(HELICOPTER_COOLDOWN),
    },
    /* spin */ {
        HELICOPTER_SET_TURN_MODE, 1,
        HELICOPTER_SPEED_APPROACH, 8,
        HELICOPTER_SET_NEXT_STATE, HELICOPTER_STATE_SPIN,
        JUMP(HELICOPTER_COOLDOWN),
    },
    /* aim */ {
        HELICOPTER_SET_TURN_MODE, 0,
        HELICOPTER_SPEED_APPROACH, 11,
        HELICOPTER_SET_NEXT_STATE, HELICOPTER_STATE_AIM,
        JUMP(HELICOPTER_COOLDOWN),
    },
    /* approach */ {
        HELICOPTER_SET_TURN_MODE, 0,
        HELICOPTER_SPEED_APPROACH, 8,
        HELICOPTER_SET_NEXT_STATE, HELICOPTER_STATE_APPROACH,
        JUMP(HELICOPTER_COOLDOWN),
    },
    /* cooldown */ {
        SET_COUNTER(100),
        JUMP(HELICOPTER_COOLING),
    },
    /* cooling */ {
        WAIT(1),
        LOOP(HELICOPTER_COOLING),
        JUMP(HELICOPTER_COOLDOWN_END),
    },
    /* cooldown_end */ {
        WAIT(1),
        JUMP(HELICOPTER_IDLE),
    },
    /* table */ {
        helicopter_scripts.idle, helicopter_scripts.pick_state, helicopter_scripts.patrol, helicopter_scripts.patrol_far, helicopter_scripts.spin, helicopter_scripts.aim,
        helicopter_scripts.approach, helicopter_scripts.cooldown, helicopter_scripts.cooling, helicopter_scripts.cooldown_end,
    },
    /* script_entry */ helicopter_scripts.idle,
};

ScriptCallEntry d_801178BC[7] = {
    {NULL, 0},
    {obj_speed_approach, 0},
    {obj_set_next_state, 0},
    {script_set_turn_mode, 0},
    {obj_jump_if_player_near, 0},
    {script_op_jump_table_if_player_far, 0},
    {script_op_jump_clear_flag, 0},
};

StateEntry helicopter_slot_table[4] = {
    {(u32)enemy_fly_move, HELICOPTER_SCRIPT, 0},
    {(u32)enemy_fly_aim, HELICOPTER_SCRIPT, 0},
    {(u32)enemy_fly_approach, HELICOPTER_SCRIPT, 0},
    {(u32)enemy_fly_spin, HELICOPTER_SCRIPT, 0},
};
