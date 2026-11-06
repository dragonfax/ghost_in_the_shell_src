/* Data shared by s09, s10: scripts/stage_data.py. */

struct TripleBarrelRobotScriptTableStreams {
    s16 walker_mech_begin[2];
    s16 walker_mech_patrol_start[4];
    s16 walker_mech_watch[8];
    s16 walker_mech_engage_wait[6];
    s16 walker_mech_engage[2];
    s16 triple_barrel_robot_fire_end[8];
    s16 triple_barrel_robot_cooldown[8];
    s16 *table[7];
    s16 *d_8011C260;
} triple_barrel_robot_script_table_streams = {
    /* walker_mech_begin */ {
        JUMP(WALKER_MECH_PATROL_START),
    },
    /* walker_mech_patrol_start */ {
        NEXT_STATE(TRIPLE_BARREL_ROBOT_STATE_PATROL),
        TRIPLE_BARREL_ROBOT_READ_ARG, 0,
    },
    /* walker_mech_watch */ {
        WAIT(1),
        TRIPLE_BARREL_ROBOT_JUMP_IF_KEY, 3, WALKER_MECH_ENGAGE_WAIT,
        JUMP(WALKER_MECH_WATCH),
    },
    /* walker_mech_engage_wait */ {
        TRIPLE_BARREL_ROBOT_BRANCH, WALKER_MECH_ENGAGE,
        WAIT(1),
        JUMP(WALKER_MECH_ENGAGE_WAIT),
    },
    /* walker_mech_engage */ {
        NEXT_STATE(TRIPLE_BARREL_ROBOT_STATE_FIRE),
    },
    /* triple_barrel_robot_fire_end */ {
        WAIT(1),
        JUMP_UNLESS_STATE(TRIPLE_BARREL_ROBOT_STATE_PATROL, TRIPLE_BARREL_ROBOT_FIRE_END),
        SET_COUNTER(16),
    },
    /* triple_barrel_robot_cooldown */ {
        WAIT(1),
        LOOP(TRIPLE_BARREL_ROBOT_COOLDOWN),
        TRIPLE_BARREL_ROBOT_READ_ARG, 1,
        JUMP(WALKER_MECH_WATCH),
    },
    /* table */ {
        triple_barrel_robot_script_table_streams.walker_mech_begin, triple_barrel_robot_script_table_streams.walker_mech_patrol_start, triple_barrel_robot_script_table_streams.walker_mech_watch, triple_barrel_robot_script_table_streams.walker_mech_engage_wait, triple_barrel_robot_script_table_streams.walker_mech_engage, triple_barrel_robot_script_table_streams.triple_barrel_robot_fire_end,
        triple_barrel_robot_script_table_streams.triple_barrel_robot_cooldown,
    },
    /* d_8011C260 */ triple_barrel_robot_script_table_streams.walker_mech_begin,
};
