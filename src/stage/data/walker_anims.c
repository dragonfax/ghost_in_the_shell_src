/* Data shared by s05, s07: scripts/stage_data.py. */

struct WalkerAnims {
    s16 mech_anim_idle[4];
    s16 mech_anim_walk[22];
    s16 mech_anim_fire[10];
    s16 death_script[22];
    s16 *table[4];
} walker_anims = {
    /* mech_anim_idle */ {
        STEP(8, 1),
        GOTO(WALKER_MECH_ANIM_IDLE),
    },
    /* mech_anim_walk */ {
        STEP(4, 19),
        STEP(4, 20),
        STEP(4, 21),
        STEP(4, 22),
        STEP(4, 23),
        STEP(4, 24),
        STEP(4, 25),
        STEP(4, 16),
        STEP(4, 17),
        STEP(4, 18),
        GOTO(WALKER_MECH_ANIM_WALK),
    },
    /* mech_anim_fire */ {
        STEP(4, 2),
        STEP(4, 4),
        STEP(4, 3),
        STEP(4, 5),
        GOTO(WALKER_MECH_ANIM_FIRE),
    },
    /* death_script */ {
        STEP(2, 6),
        STEP(2, 7),
        STEP(2, 8),
        STEP(2, 9),
        STEP(2, 10),
        STEP(2, 11),
        STEP(2, 12),
        STEP(2, 13),
        STEP(2, 14),
        STEP(2, 15),
        GOTO(WALKER_DEATH_SCRIPT),
    },
    /* table */ {
        walker_anims.mech_anim_idle, walker_anims.mech_anim_walk, walker_anims.mech_anim_fire, walker_anims.death_script,
    },
};
