/* Data shared by s02, s03, s07, s10, s11: scripts/stage_data.py. */

struct GunTurret2Scripts {
    s16 idle[8];
    s16 spotted[2];
    s16 tracking[8];
    s16 aimed[8];
    s16 open_fire[2];
    s16 firing[8];
    s16 cooldown[4];
    s16 cooling[8];
    s16 *table[8];
    s16 *script_pos[1];
} gun_turret_2_scripts = {
    /* idle */ {
        WAIT(3),
        GUN_TURRET_2_JUMP_WITHIN, 3000, GUN_TURRET_2_SPOTTED,
        JUMP(GUN_TURRET_2_IDLE),
    },
    /* spotted */ {
        NEXT_STATE(GUN_TURRET_2_STATE_TRACK),
    },
    /* tracking */ {
        WAIT(3),
        GUN_TURRET_2_BRANCH_IF_AIMED, 256, GUN_TURRET_2_AIMED,
        JUMP(GUN_TURRET_2_TRACKING),
    },
    /* aimed */ {
        WAIT(1),
        GUN_TURRET_2_JUMP_WITHIN, 2000, GUN_TURRET_2_OPEN_FIRE,
        JUMP(GUN_TURRET_2_TRACKING),
    },
    /* open_fire */ {
        NEXT_STATE(GUN_TURRET_2_STATE_FIRE),
    },
    /* firing */ {
        WAIT(1),
        JUMP_IF_STATE(GUN_TURRET_2_STATE_IDLE, GUN_TURRET_2_COOLDOWN),
        JUMP(GUN_TURRET_2_FIRING),
    },
    /* cooldown */ {
        SET_COUNTER(32),
        NEXT_STATE(GUN_TURRET_2_STATE_TRACK),
    },
    /* cooling */ {
        WAIT(1),
        LOOP(GUN_TURRET_2_COOLING),
        NEXT_STATE(GUN_TURRET_2_STATE_IDLE),
        JUMP(GUN_TURRET_2_IDLE),
    },
    /* table */ {
        gun_turret_2_scripts.idle, gun_turret_2_scripts.spotted, gun_turret_2_scripts.tracking, gun_turret_2_scripts.aimed, gun_turret_2_scripts.open_fire, gun_turret_2_scripts.firing,
        gun_turret_2_scripts.cooldown, gun_turret_2_scripts.cooling,
    },
    /* script_pos */ {
        gun_turret_2_scripts.idle,
    },
};
