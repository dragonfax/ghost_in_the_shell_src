/* ObjVars.hover: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_HOVER_H
#define OBJVARS_HOVER_H

/* s09 kinds that hover toward the player and bob (func_800BA958) */
typedef struct HoverVars {
    /* 0x248 */ u8 pad_248[0x18];
    /* 0x260 */ u16 phase;     /* sine phase, +0x20 a step */
} HoverVars;

#endif
