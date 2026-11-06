/* Data shared by s02, s03, s07, s10, s11: scripts/stage_data.py. */

struct GunTurret2Anims {
    s16 pose[4];
    s16 *table;
} gun_turret_2_anims = {
    /* pose */ {
        STEP(4, 0),
        GOTO(GUN_TURRET_2_POSE),
    },
    /* table */ gun_turret_2_anims.pose,
};
