/* Data shared by s01, s03, s10 (10 objects): scripts/stage_data.py. */

s32 rocket_fuchikoma_asset[3] = {
    -1, -1, -1,
};

ModelBlockRef d_801173E4[3] = {
    {(s32)file_mth1_ch0_clt, 0, 0},
    {(s32)file_mth1_tp0_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef d_801173FC[2] = {
    {(s32)file_mth1_tp0_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef d_8011740C[2] = {
    {(s32)file_mth1_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock d_8011741C = {(s32)d_801173E4, (s32)d_8011740C, (s32)d_801173FC, 0, 0, 0, 0, 0, 0};

u8 *d_80117440[2] = {
    file_mth1_ch0_cb4, NULL,
};

ScanEntry d_80117448 = {{(s32)params_reset, (s32)rocket_fuchikoma_spawn}, rocket_fuchikoma_asset, (s32)&d_8011741C, (s32)d_80117440, 0};

SoundVolume rocket_fuchikoma_sounds[1] = {
    {SND_FOOTSTEP | SND_GROUP(2), 0x1000},
};

struct RocketFuchikomaAnims {
    s16 idle[4];
    s16 fly[26];
    s16 detonate[2];
    s16 detonate_hold[4];
    s16 *table[4];
} rocket_fuchikoma_anims = {
    /* idle */ {
        STEP(8, 4),
        GOTO(ROCKET_FUCHIKOMA_ANIM_IDLE),
    },
    /* fly */ {
        STEP(4, 4),
        STEP(4, 5),
        SOUND(0),
        STEP(4, 6),
        STEP(4, 7),
        STEP(4, 8),
        STEP(4, 9),
        STEP(4, 10),
        SOUND(0),
        STEP(4, 1),
        STEP(4, 2),
        STEP(4, 3),
        GOTO(ROCKET_FUCHIKOMA_ANIM_FLY),
    },
    /* detonate */ {
        STEP(1, 11),
    },
    /* detonate_hold */ {
        STEP(4, 12),
        GOTO(ROCKET_FUCHIKOMA_ANIM_DETONATE_HOLD),
    },
    /* table */ {
        rocket_fuchikoma_anims.idle, rocket_fuchikoma_anims.fly, rocket_fuchikoma_anims.detonate, rocket_fuchikoma_anims.detonate_hold,
    },
};

struct RocketFuchikomaJumpTableStreams {
    s16 rocket_fuchikoma_idle[6];
    s16 rocket_fuchikoma_reset[8];
    s16 rocket_fuchikoma_settle[10];
    s16 rocket_fuchikoma_ready[6];
    s16 rocket_fuchikoma_aim_start[6];
    s16 grenade_fuchikoma_seek[10];
    s16 rocket_fuchikoma_approach[8];
    s16 grenade_fuchikoma_track[16];
    s16 rocket_fuchikoma_close_in[8];
    s16 rocket_fuchikoma_brake[4];
    s16 grenade_fuchikoma_wait_stop[8];
    s16 rocket_fuchikoma_fire_wait[6];
    s16 rocket_fuchikoma_fire_start[2];
    s16 grenade_fuchikoma_detonate_wait[8];
    s16 rocket_fuchikoma_reposition[8];
    s16 rocket_fuchikoma_reposition_face[8];
    s16 *table[16];
    s16 *rocket_fuchikoma_script_pos[1];
} rocket_fuchikoma_jump_table_streams = {
    /* rocket_fuchikoma_idle */ {
        WAIT(1),
        ROCKET_FUCHIKOMA_BRANCH_ON_FLAG, ROCKET_FUCHIKOMA_RESET,
        JUMP(ROCKET_FUCHIKOMA_IDLE),
    },
    /* rocket_fuchikoma_reset */ {
        NEXT_STATE(ROCKET_FUCHIKOMA_STATE_IDLE),
        ROCKET_FUCHIKOMA_READ_SPEED_LONG, 0, 0,
        SET_COUNTER(8),
    },
    /* rocket_fuchikoma_settle */ {
        WAIT(1),
        LOOP(ROCKET_FUCHIKOMA_SETTLE),
        ROCKET_FUCHIKOMA_READ_S32, 16384, 0,
        ROCKET_FUCHIKOMA_READ_LONG, 1365, 0,
    },
    /* rocket_fuchikoma_ready */ {
        WAIT(1),
        ROCKET_FUCHIKOMA_BRANCH_ON_FLAG, ROCKET_FUCHIKOMA_AIM_START,
        JUMP(ROCKET_FUCHIKOMA_READY),
    },
    /* rocket_fuchikoma_aim_start */ {
        NEXT_STATE(ROCKET_FUCHIKOMA_STATE_FLY),
        ROCKET_FUCHIKOMA_AIM_JITTERED,
        SET_COUNTER(30),
    },
    /* grenade_fuchikoma_seek */ {
        WAIT(1),
        ROCKET_FUCHIKOMA_JUMP_NEAR_PLAYER, 2000, 2500, ROCKET_FUCHIKOMA_APPROACH,
        LOOP(GRENADE_FUCHIKOMA_SEEK),
        JUMP(ROCKET_FUCHIKOMA_AIM_START),
    },
    /* rocket_fuchikoma_approach */ {
        NEXT_STATE(ROCKET_FUCHIKOMA_STATE_FLY),
        ROCKET_FUCHIKOMA_READ_S32, 16384, 0,
        ROCKET_FUCHIKOMA_READ_LONG, 1365, 0,
    },
    /* grenade_fuchikoma_track */ {
        WAIT(1),
        ROCKET_FUCHIKOMA_FACE_PLAYER,
        ROCKET_FUCHIKOMA_JUMP_IF_BEYOND_RADIUS, 2500, ROCKET_FUCHIKOMA_READY,
        WAIT(1),
        ROCKET_FUCHIKOMA_JUMP_IF_FACING_PLAYER_IN_RADIUS, 2000, 128, ROCKET_FUCHIKOMA_CLOSE_IN, GRENADE_FUCHIKOMA_TRACK,
        JUMP(ROCKET_FUCHIKOMA_READY),
    },
    /* rocket_fuchikoma_close_in */ {
        WAIT(1),
        ROCKET_FUCHIKOMA_JUMP_NEAR, 1024, ROCKET_FUCHIKOMA_BRAKE,
        JUMP(GRENADE_FUCHIKOMA_TRACK),
    },
    /* rocket_fuchikoma_brake */ {
        ROCKET_FUCHIKOMA_READ_LONG, -2730, -1,
    },
    /* grenade_fuchikoma_wait_stop */ {
        WAIT(1),
        ROCKET_FUCHIKOMA_JUMP_IF_NOT_BELOW_SPEED, 0, ROCKET_FUCHIKOMA_FIRE_WAIT,
        JUMP(GRENADE_FUCHIKOMA_WAIT_STOP),
    },
    /* rocket_fuchikoma_fire_wait */ {
        ROCKET_FUCHIKOMA_BRANCH_ON_FLAG, ROCKET_FUCHIKOMA_FIRE_START,
        WAIT(1),
        JUMP(ROCKET_FUCHIKOMA_FIRE_WAIT),
    },
    /* rocket_fuchikoma_fire_start */ {
        NEXT_STATE(ROCKET_FUCHIKOMA_STATE_DETONATE),
    },
    /* grenade_fuchikoma_detonate_wait */ {
        WAIT(1),
        JUMP_IF_STATE(ROCKET_FUCHIKOMA_STATE_IDLE, ROCKET_FUCHIKOMA_REPOSITION),
        JUMP(GRENADE_FUCHIKOMA_DETONATE_WAIT),
    },
    /* rocket_fuchikoma_reposition */ {
        ROCKET_FUCHIKOMA_READ_LONG, 1365, 0,
        NEXT_STATE(ROCKET_FUCHIKOMA_STATE_FLY),
        SET_COUNTER(16),
    },
    /* rocket_fuchikoma_reposition_face */ {
        WAIT(1),
        ROCKET_FUCHIKOMA_FACE_PLAYER,
        LOOP(ROCKET_FUCHIKOMA_REPOSITION_FACE),
        JUMP(ROCKET_FUCHIKOMA_APPROACH),
    },
    /* table */ {
        rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_idle, rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_reset, rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_settle, rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_ready, rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_aim_start, rocket_fuchikoma_jump_table_streams.grenade_fuchikoma_seek,
        rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_approach, rocket_fuchikoma_jump_table_streams.grenade_fuchikoma_track, rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_close_in, rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_brake, rocket_fuchikoma_jump_table_streams.grenade_fuchikoma_wait_stop, rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_fire_wait,
        rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_fire_start, rocket_fuchikoma_jump_table_streams.grenade_fuchikoma_detonate_wait, rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_reposition, rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_reposition_face,
    },
    /* rocket_fuchikoma_script_pos */ {
        rocket_fuchikoma_jump_table_streams.rocket_fuchikoma_idle,
    },
};
