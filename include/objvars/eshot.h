/* ObjVars.eshot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ESHOT_H
#define OBJVARS_ESHOT_H

/* s03 enemy shot (enemy_shot_spawn, func_800C34E8) */
typedef struct EshotVars {
    /* 0x248 */ s32 model;        /* model slot of the shot */
    /* 0x24C */ s16 power;
    /* 0x24E */ u16 bob_phase;    /* sine phase of the vertical bob */
    /* 0x250 */ u16 rise_time;    /* > 0: rising */
    /* 0x252 */ u16 smoke_toggle; /* smoke every other frame */
    /* 0x254 */ s16 aiming;       /* 1: charging a bazooka shot */
    /* 0x256 */ s16 charge;       /* fires past 0x1000 */
    /* 0x258 */ s16 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25A */ u8 pad_25A[2];
    /* 0x25C */ struct Object *parent;
} EshotVars;

#endif
