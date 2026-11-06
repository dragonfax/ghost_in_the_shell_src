/* ObjVars.s06_helicopter: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_S06_HELICOPTER_H
#define OBJVARS_S06_HELICOPTER_H

/* s06_helicopter_spawn (scripts/objkinds.py) */
typedef struct S06HelicopterVars {
    /* 0x248 */ s16 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24A */ s16 timer;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s16 fx_timer;
    /* 0x252 */ u8 pad_252[6];
    /* 0x258 */ s32 aim_angle;
    /* 0x25C */ u8 pad_25C[8];
    /* 0x264 */ s32 countdown_timer;
    /* 0x268 */ s16 explosion_timer;
} S06HelicopterVars;

#endif
