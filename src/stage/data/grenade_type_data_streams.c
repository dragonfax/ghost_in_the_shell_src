/* Data shared by s05, s07: scripts/stage_data.py. */

struct GrenadeTypeDataStreams {
    s16 grenade_fuchikoma_dormant[6];
    s16 grenade_fuchikoma_release[8];
    s16 grenade_fuchikoma_release_wait[10];
    s16 rocket_fuchikoma_ready[6];
    s16 rocket_fuchikoma_aim_start[6];
    s16 grenade_fuchikoma_seek[10];
    s16 grenade_fuchikoma_set_params[6];
    s16 grenade_fuchikoma_track[16];
    s16 rocket_fuchikoma_close_in[8];
    s16 rocket_fuchikoma_brake[4];
    s16 grenade_fuchikoma_wait_stop[8];
    s16 rocket_fuchikoma_fire_wait[6];
    s16 rocket_fuchikoma_fire_start[2];
    s16 grenade_fuchikoma_detonate_wait[8];
    s16 rocket_fuchikoma_reposition[8];
    s16 grenade_fuchikoma_recover_face[10];
    s16 *table[16];
    s16 *grenade_script_pc;
} grenade_type_data_streams = {
    /* grenade_fuchikoma_dormant */ {
        WAIT(1),
        GRENADE_FUCHIKOMA_BRANCH_ON_FLAG, GRENADE_FUCHIKOMA_RELEASE,
        JUMP(GRENADE_FUCHIKOMA_DORMANT),
    },
    /* grenade_fuchikoma_release */ {
        NEXT_STATE(GRENADE_FUCHIKOMA_STATE_IDLE),
        GRENADE_FUCHIKOMA_READ_SPEED_LONG, 0, 0,
        SET_COUNTER(8),
    },
    /* grenade_fuchikoma_release_wait */ {
        WAIT(1),
        LOOP(GRENADE_FUCHIKOMA_RELEASE_WAIT),
        GRENADE_FUCHIKOMA_READ_S32, 24576, 0,
        GRENADE_FUCHIKOMA_READ_LONG, 1365, 0,
    },
    /* rocket_fuchikoma_ready */ {
        WAIT(1),
        GRENADE_FUCHIKOMA_BRANCH_ON_FLAG, ROCKET_FUCHIKOMA_AIM_START,
        JUMP(ROCKET_FUCHIKOMA_READY),
    },
    /* rocket_fuchikoma_aim_start */ {
        NEXT_STATE(GRENADE_FUCHIKOMA_STATE_FLY),
        GRENADE_FUCHIKOMA_AIM_JITTERED,
        SET_COUNTER(30),
    },
    /* grenade_fuchikoma_seek */ {
        WAIT(1),
        GRENADE_FUCHIKOMA_JUMP_NEAR_PLAYER, 2000, 2500, GRENADE_FUCHIKOMA_SET_PARAMS,
        LOOP(GRENADE_FUCHIKOMA_SEEK),
        JUMP(ROCKET_FUCHIKOMA_AIM_START),
    },
    /* grenade_fuchikoma_set_params */ {
        GRENADE_FUCHIKOMA_READ_S32, 24576, 0,
        GRENADE_FUCHIKOMA_READ_LONG, 1365, 0,
    },
    /* grenade_fuchikoma_track */ {
        WAIT(1),
        GRENADE_FUCHIKOMA_FACE_PLAYER,
        GRENADE_FUCHIKOMA_JUMP_IF_BEYOND_RADIUS, 2500, ROCKET_FUCHIKOMA_READY,
        WAIT(1),
        GRENADE_FUCHIKOMA_JUMP_IF_FACING_PLAYER_IN_RADIUS, 2000, 128, ROCKET_FUCHIKOMA_CLOSE_IN, GRENADE_FUCHIKOMA_TRACK,
        JUMP(ROCKET_FUCHIKOMA_READY),
    },
    /* rocket_fuchikoma_close_in */ {
        WAIT(1),
        GRENADE_FUCHIKOMA_JUMP_NEAR, 1024, ROCKET_FUCHIKOMA_BRAKE,
        JUMP(GRENADE_FUCHIKOMA_TRACK),
    },
    /* rocket_fuchikoma_brake */ {
        GRENADE_FUCHIKOMA_READ_LONG, -2730, -1,
    },
    /* grenade_fuchikoma_wait_stop */ {
        WAIT(1),
        GRENADE_FUCHIKOMA_JUMP_IF_NOT_BELOW_SPEED, 0, ROCKET_FUCHIKOMA_FIRE_WAIT,
        JUMP(GRENADE_FUCHIKOMA_WAIT_STOP),
    },
    /* rocket_fuchikoma_fire_wait */ {
        GRENADE_FUCHIKOMA_BRANCH_ON_FLAG, ROCKET_FUCHIKOMA_FIRE_START,
        WAIT(1),
        JUMP(ROCKET_FUCHIKOMA_FIRE_WAIT),
    },
    /* rocket_fuchikoma_fire_start */ {
        NEXT_STATE(GRENADE_FUCHIKOMA_STATE_DETONATE),
    },
    /* grenade_fuchikoma_detonate_wait */ {
        WAIT(1),
        JUMP_IF_STATE(GRENADE_FUCHIKOMA_STATE_IDLE, ROCKET_FUCHIKOMA_REPOSITION),
        JUMP(GRENADE_FUCHIKOMA_DETONATE_WAIT),
    },
    /* rocket_fuchikoma_reposition */ {
        GRENADE_FUCHIKOMA_READ_LONG, 1365, 0,
        NEXT_STATE(GRENADE_FUCHIKOMA_STATE_FLY),
        SET_COUNTER(16),
    },
    /* grenade_fuchikoma_recover_face */ {
        WAIT(1),
        GRENADE_FUCHIKOMA_FACE_PLAYER,
        LOOP(GRENADE_FUCHIKOMA_RECOVER_FACE),
        NEXT_STATE(GRENADE_FUCHIKOMA_STATE_FLY),
        JUMP(GRENADE_FUCHIKOMA_SET_PARAMS),
    },
    /* table */ {
        grenade_type_data_streams.grenade_fuchikoma_dormant, grenade_type_data_streams.grenade_fuchikoma_release, grenade_type_data_streams.grenade_fuchikoma_release_wait, grenade_type_data_streams.rocket_fuchikoma_ready, grenade_type_data_streams.rocket_fuchikoma_aim_start, grenade_type_data_streams.grenade_fuchikoma_seek,
        grenade_type_data_streams.grenade_fuchikoma_set_params, grenade_type_data_streams.grenade_fuchikoma_track, grenade_type_data_streams.rocket_fuchikoma_close_in, grenade_type_data_streams.rocket_fuchikoma_brake, grenade_type_data_streams.grenade_fuchikoma_wait_stop, grenade_type_data_streams.rocket_fuchikoma_fire_wait,
        grenade_type_data_streams.rocket_fuchikoma_fire_start, grenade_type_data_streams.grenade_fuchikoma_detonate_wait, grenade_type_data_streams.rocket_fuchikoma_reposition, grenade_type_data_streams.grenade_fuchikoma_recover_face,
    },
    /* grenade_script_pc */ grenade_type_data_streams.grenade_fuchikoma_dormant,
};
