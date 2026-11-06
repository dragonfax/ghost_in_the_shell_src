/* ObjVars.gun_turret_2: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_GUN_TURRET_2_H
#define OBJVARS_GUN_TURRET_2_H

/* gun_turret_2_spawn (scripts/objkinds.py) */
typedef struct GunTurret2Vars {
    /* 0x248 */ u8 pad_248[2];
    /* 0x24A */ u16 turret_yaw;
    /* 0x24C */ u8 pad_24C[8];
    /* 0x254 */ s32 sound_channel;
} GunTurret2Vars;

#endif
