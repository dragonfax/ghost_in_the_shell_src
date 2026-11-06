/* Data shared by s07, s09, s11, s12: scripts/stage_data.py. */

struct EnemyFuchikomaBAnims {
    s16 idle[4];
    s16 walk[26];
    s16 *table[2];
} enemy_fuchikoma_b_anims = {
    /* idle */ {
        STEP(8, 12),
        GOTO(ENEMY_FUCHIKOMA_B_ANIM_IDLE),
    },
    /* walk */ {
        STEP(3, 3),
        STEP(3, 4),
        STEP(3, 5),
        SET_F8(15),
        STEP(3, 6),
        STEP(3, 7),
        STEP(3, 8),
        STEP(3, 9),
        STEP(3, 10),
        SET_F8(15),
        STEP(3, 1),
        STEP(3, 2),
        GOTO(ENEMY_FUCHIKOMA_B_ANIM_WALK),
    },
    /* table */ {
        enemy_fuchikoma_b_anims.idle, enemy_fuchikoma_b_anims.walk,
    },
};
