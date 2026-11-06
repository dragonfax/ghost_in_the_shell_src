/* ObjVars.spin: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPIN_H
#define OBJVARS_SPIN_H

/* s13 kinds that spin down (func_800B93C8) */
typedef struct SpinVars {
    /* 0x248 */ u8 pad_248[0xE];
    /* 0x256 */ u8 unk_256;       /* 0: brake */
    /* 0x257 */ u8 pad_257[9];
    /* 0x260 */ s32 speed;        /* added to yaw and turn */
} SpinVars;

#endif
