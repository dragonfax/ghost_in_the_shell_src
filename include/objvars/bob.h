/* ObjVars.bob: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BOB_H
#define OBJVARS_BOB_H

/* s04 kinds that drift with a flow and bob (func_800BFC88) */
typedef struct BobVars {
    /* 0x248 */ u8 pad_248[8];
    /* 0x250 */ u8 pad_250[4];
    /* 0x254 */ u8 pad_254[0xC];
    /* 0x260 */ s16 timer;       /* nonzero: bob */
    /* 0x262 */ u16 phase;       /* sine phase, +0x10 a step */
    /* 0x264 */ u8 pad_264[4];
    /* 0x268 */ Flow current;    /* speed: get_flow_max() each step */
} BobVars;

#endif
