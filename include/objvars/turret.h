/* ObjVars.turret: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TURRET_H
#define OBJVARS_TURRET_H

/* gun turret 2 (gun_turret_2_spawn; obj_loop_sound_clear stops the sound) */
typedef struct TurretVars {
    /* 0x248 */ s16 pitch;
    /* 0x24A */ u16 yaw;
    /* 0x24C */ s16 roll;
    /* 0x24E */ u16 unused_24E; /* no use in the C */
    /* 0x250 */ s16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u16 variant; /* 0..2, from the placement */
    /* 0x254 */ s32 sound;
} TurretVars;

#endif
