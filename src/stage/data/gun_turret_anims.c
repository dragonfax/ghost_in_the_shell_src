/* Data shared by s05, s09, s12: scripts/stage_data.py. */

struct GunTurretAnims {
    s16 idle[4];
    s16 *table;
} gun_turret_anims = {
    /* idle */ {
        STEP(4, 0),
        GOTO(GUN_TURRET_ANIM_IDLE),
    },
    /* table */ gun_turret_anims.idle,
};
