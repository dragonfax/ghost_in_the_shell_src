/* Data shared by s03, s07: scripts/stage_data.py. */

struct Helicopter2Scripts {
    s16 think[2];
    s16 select[18];
    s16 patrol[8];
    s16 cruise[8];
    s16 bank_turn[8];
    s16 attack[8];
    s16 hover[8];
    s16 hold_start[4];
    s16 hold_loop[6];
    s16 cycle_end[4];
    s16 *table[10];
    s16 *script_entry;
} helicopter2_scripts = {
    /* think */ {
        JUMP(HELICOPTER2_SELECT),
    },
    /* select */ {
        HELICOPTER2_JUMP_TABLE_IF_PLAYER_FAR, 5000, HELICOPTER2_CRUISE,
        JUMP_IF_STATE(HELICOPTER2_STATE_BANK_TURN, HELICOPTER2_BANK_TURN),
        HELICOPTER2_JUMP_IF_PLAYER_NEAR, 1150, HELICOPTER2_ATTACK,
        HELICOPTER2_JUMP_IF_PLAYER_NEAR, 1850, HELICOPTER2_HOVER,
        HELICOPTER2_JUMP_IF_PLAYER_NEAR, 2150, HELICOPTER2_PATROL,
        JUMP(HELICOPTER2_CRUISE),
    },
    /* patrol */ {
        HELICOPTER2_SET_TURN_MODE, 0,
        HELICOPTER2_SPEED_APPROACH, 8,
        HELICOPTER2_SET_NEXT_STATE, HELICOPTER2_STATE_PATROL,
        JUMP(HELICOPTER2_HOLD_START),
    },
    /* cruise */ {
        HELICOPTER2_SET_TURN_MODE, 1,
        HELICOPTER2_SPEED_APPROACH, 4,
        HELICOPTER2_SET_NEXT_STATE, HELICOPTER2_STATE_PATROL,
        JUMP(HELICOPTER2_HOLD_START),
    },
    /* bank_turn */ {
        HELICOPTER2_SET_TURN_MODE, 1,
        HELICOPTER2_SPEED_APPROACH, 4,
        HELICOPTER2_SET_NEXT_STATE, HELICOPTER2_STATE_BANK_TURN,
        JUMP(HELICOPTER2_HOLD_START),
    },
    /* attack */ {
        HELICOPTER2_SET_TURN_MODE, 0,
        HELICOPTER2_SPEED_APPROACH, 8,
        HELICOPTER2_SET_NEXT_STATE, HELICOPTER2_STATE_ATTACK,
        JUMP(HELICOPTER2_HOLD_START),
    },
    /* hover */ {
        HELICOPTER2_SET_TURN_MODE, 0,
        HELICOPTER2_SPEED_APPROACH, 4,
        HELICOPTER2_SET_NEXT_STATE, HELICOPTER2_STATE_HOVER,
        JUMP(HELICOPTER2_HOLD_START),
    },
    /* hold_start */ {
        SET_COUNTER(50),
        JUMP(HELICOPTER2_HOLD_LOOP),
    },
    /* hold_loop */ {
        WAIT(1),
        LOOP(HELICOPTER2_HOLD_LOOP),
        JUMP(HELICOPTER2_CYCLE_END),
    },
    /* cycle_end */ {
        WAIT(1),
        JUMP(HELICOPTER2_THINK),
    },
    /* table */ {
        helicopter2_scripts.think, helicopter2_scripts.select, helicopter2_scripts.patrol, helicopter2_scripts.cruise, helicopter2_scripts.bank_turn, helicopter2_scripts.attack,
        helicopter2_scripts.hover, helicopter2_scripts.hold_start, helicopter2_scripts.hold_loop, helicopter2_scripts.cycle_end,
    },
    /* script_entry */ helicopter2_scripts.think,
};
