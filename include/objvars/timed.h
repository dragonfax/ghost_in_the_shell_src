/* ObjVars.timed: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TIMED_H
#define OBJVARS_TIMED_H

/* obj_spawn_timed (scripts/objkinds.py) */
typedef struct TimedVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s32 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
} TimedVars;

#endif
