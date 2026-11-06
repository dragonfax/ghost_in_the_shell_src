/* ObjVars.pushed: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PUSHED_H
#define OBJVARS_PUSHED_H

/* s06 kinds pushed by another object's flow (func_800BC0D8) */
typedef struct PushedVars {
    /* 0x248 */ u8 pad_248[0x24];
    /* 0x26C */ struct Object *source; /* its vars hold the Flow, its position the origin */
} PushedVars;

#endif
