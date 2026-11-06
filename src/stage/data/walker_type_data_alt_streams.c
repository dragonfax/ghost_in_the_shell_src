/* Data shared by s05, s07: scripts/stage_data.py. */

struct WalkerTypeDataAltStreams {
    s16 walker_mech_begin[2];
    s16 walker_mech_patrol_start[4];
    s16 walker_mech_watch[8];
    s16 walker_mech_engage_wait[6];
    s16 walker_mech_engage[2];
    s16 triple_barrel_robot_fire_end[8];
    s16 triple_barrel_robot_cooldown[8];
    s16 *table[7];
    s16 *d_80116578;
} walker_type_data_alt_streams = {
    /* walker_mech_begin */ {
        JUMP(WALKER_MECH_PATROL_START),
    },
    /* walker_mech_patrol_start */ {
        NEXT_STATE(WALKER_MECH_STATE_PATROL),
        WALKER_MECH_SET_PATROL_PHASE, 0,
    },
    /* walker_mech_watch */ {
        WAIT(1),
        WALKER_MECH_JUMP_IF_KEY, 3, WALKER_MECH_ENGAGE_WAIT,
        JUMP(WALKER_MECH_WATCH),
    },
    /* walker_mech_engage_wait */ {
        WALKER_MECH_JUMP_IF_FLAG_SET, WALKER_MECH_ENGAGE,
        WAIT(1),
        JUMP(WALKER_MECH_ENGAGE_WAIT),
    },
    /* walker_mech_engage */ {
        NEXT_STATE(WALKER_MECH_STATE_ATTACK),
    },
    /* triple_barrel_robot_fire_end */ {
        WAIT(1),
        JUMP_UNLESS_STATE(WALKER_MECH_STATE_PATROL, TRIPLE_BARREL_ROBOT_FIRE_END),
        SET_COUNTER(16),
    },
    /* triple_barrel_robot_cooldown */ {
        WAIT(1),
        LOOP(TRIPLE_BARREL_ROBOT_COOLDOWN),
        WALKER_MECH_SET_PATROL_PHASE, 1,
        JUMP(WALKER_MECH_WATCH),
    },
    /* table */ {
        walker_type_data_alt_streams.walker_mech_begin, walker_type_data_alt_streams.walker_mech_patrol_start, walker_type_data_alt_streams.walker_mech_watch, walker_type_data_alt_streams.walker_mech_engage_wait, walker_type_data_alt_streams.walker_mech_engage, walker_type_data_alt_streams.triple_barrel_robot_fire_end,
        walker_type_data_alt_streams.triple_barrel_robot_cooldown,
    },
    /* d_80116578 */ walker_type_data_alt_streams.walker_mech_begin,
};
