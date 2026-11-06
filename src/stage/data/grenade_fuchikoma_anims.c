/* Data shared by s05, s07: scripts/stage_data.py. */

struct GrenadeFuchikomaAnims {
    s16 idle[4];
    s16 spin[22];
    s16 hold_start[2];
    s16 hold[4];
    s16 *table[4];
} grenade_fuchikoma_anims = {
    /* idle */ {
        STEP(8, 4),
        GOTO(GRENADE_FUCHIKOMA_ANIM_IDLE),
    },
    /* spin */ {
        STEP(2, 4),
        STEP(2, 5),
        STEP(2, 6),
        STEP(2, 7),
        STEP(2, 8),
        STEP(2, 9),
        STEP(2, 10),
        STEP(2, 1),
        STEP(2, 2),
        STEP(2, 3),
        GOTO(GRENADE_FUCHIKOMA_ANIM_SPIN),
    },
    /* hold_start */ {
        STEP(1, 11),
    },
    /* hold */ {
        STEP(2, 12),
        GOTO(GRENADE_FUCHIKOMA_ANIM_HOLD),
    },
    /* table */ {
        grenade_fuchikoma_anims.idle, grenade_fuchikoma_anims.spin, grenade_fuchikoma_anims.hold_start, grenade_fuchikoma_anims.hold,
    },
};
