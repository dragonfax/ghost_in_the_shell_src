/* ObjVars.ctrl: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_CTRL_H
#define OBJVARS_CTRL_H

/* ctrl_spawn (scripts/objkinds.py) */
typedef struct CtrlVars {
    /* 0x248 */ s32 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s32 unused_24C; /* only ever set to a constant in the C: never read */
} CtrlVars;

#endif
