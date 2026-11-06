/* ObjVars.flare: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FLARE_H
#define OBJVARS_FLARE_H

/* s06 part drawn as three sparks and a pose (func_800C5A88) */
typedef struct FlareVars {
    /* 0x248 */ struct Object *parent;
    /* 0x24C */ u8 pad_24C[2];
    /* 0x24E */ s16 spark_yaw;
    /* 0x250 */ u8 pad_250[4];
    /* 0x254 */ s32 pos[3];          /* base of the spark offsets */
    /* 0x260 */ u8 pad_260[4];
    /* 0x264 */ struct { s16 vx, vy, vz, pad; } spark_offset[3];
    /* 0x27C */ s16 pose_angle;
    /* 0x27E */ s16 kind;            /* 3: spawns sparks and stops the part sound (func_800C56FC) */
} FlareVars;

#endif
