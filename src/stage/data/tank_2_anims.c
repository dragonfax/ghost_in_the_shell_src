/* Data shared by s06, s07, s09: scripts/stage_data.py. */

struct Tank2Anims {
    s16 idle[4];
    s16 *table[1];
} tank_2_anims = {
    /* idle */ {
        STEP(4, 0),
        GOTO(TANK_2_ANIM_IDLE),
    },
    /* table */ {
        tank_2_anims.idle,
    },
};
