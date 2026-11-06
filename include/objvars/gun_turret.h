/* ObjVars.gun_turret: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_GUN_TURRET_H
#define OBJVARS_GUN_TURRET_H

/* gun_turret_spawn (scripts/objkinds.py) */
typedef struct GunTurretVars {
    /* 0x248 */ s16 initial_pitch;
    /* 0x24A */ u16 initial_yaw;
    /* 0x24C */ s16 initial_roll;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ u16 unk_250;
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
} GunTurretVars;

#endif
