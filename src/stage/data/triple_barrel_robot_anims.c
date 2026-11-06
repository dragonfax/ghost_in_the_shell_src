/* Data shared by s09, s10: scripts/stage_data.py. */

struct TripleBarrelRobotAnims {
    s16 idle[4];
    s16 fire[26];
    s16 walk[6];
    s16 *table[3];
} triple_barrel_robot_anims = {
    /* idle */ {
        STEP(8, 1),
        GOTO(TRIPLE_BARREL_ROBOT_ANIM_IDLE),
    },
    /* fire */ {
        STEP(4, 4),
        STEP(4, 5),
        STEP(4, 6),
        SOUND(0),
        STEP(4, 7),
        STEP(4, 8),
        STEP(4, 9),
        STEP(4, 10),
        STEP(4, 11),
        SOUND(0),
        STEP(4, 2),
        STEP(4, 3),
        GOTO(TRIPLE_BARREL_ROBOT_ANIM_FIRE),
    },
    /* walk */ {
        STEP(4, 12),
        STEP(4, 13),
        GOTO(TRIPLE_BARREL_ROBOT_ANIM_WALK),
    },
    /* table */ {
        triple_barrel_robot_anims.idle, triple_barrel_robot_anims.fire, triple_barrel_robot_anims.walk,
    },
};
