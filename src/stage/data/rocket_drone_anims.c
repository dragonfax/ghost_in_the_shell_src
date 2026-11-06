/* Data shared by s02, s09: scripts/stage_data.py. */

struct RocketDroneAnims {
    s16 idle[4];
    s16 *table[1];
} rocket_drone_anims = {
    /* idle */ {
        STEP(1, 0),
        GOTO(ROCKET_DRONE_ANIM_IDLE),
    },
    /* table */ {
        rocket_drone_anims.idle,
    },
};
