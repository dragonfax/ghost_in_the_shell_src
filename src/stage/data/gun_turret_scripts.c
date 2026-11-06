/* Data shared by s05, s09, s12: scripts/stage_data.py. */

struct GunTurretScripts {
    s16 idle[8];
    s16 spotted[2];
    s16 aim[8];
    s16 fire_check[6];
    s16 fire_start[2];
    s16 cooldown[8];
    s16 *table[6];
    s16 *script_pos;
} gun_turret_scripts = {
    /* idle */ {
        WAIT(1),
        GUN_TURRET_BRANCH_IF_NEAR_PLAYER, 3000, GUN_TURRET_SPOTTED,
        JUMP(GUN_TURRET_IDLE),
    },
    /* spotted */ {
        NEXT_STATE(GUN_TURRET_STATE_TRACK),
    },
    /* aim */ {
        WAIT(1),
        GUN_TURRET_JUMP_IF_FACING_PLAYER, 128, GUN_TURRET_FIRE_CHECK,
        JUMP(GUN_TURRET_AIM),
    },
    /* fire_check */ {
        GUN_TURRET_BRANCH_IF_NEAR_PLAYER, 2000, GUN_TURRET_FIRE_START,
        JUMP(GUN_TURRET_AIM),
    },
    /* fire_start */ {
        NEXT_STATE(GUN_TURRET_STATE_FIRE),
    },
    /* cooldown */ {
        WAIT(1),
        JUMP_IF_STATE(GUN_TURRET_STATE_IDLE, GUN_TURRET_IDLE),
        JUMP(GUN_TURRET_COOLDOWN),
    },
    /* table */ {
        gun_turret_scripts.idle, gun_turret_scripts.spotted, gun_turret_scripts.aim, gun_turret_scripts.fire_check, gun_turret_scripts.fire_start, gun_turret_scripts.cooldown,
    },
    /* script_pos */ gun_turret_scripts.idle,
};
