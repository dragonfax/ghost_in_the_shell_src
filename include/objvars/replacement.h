/* ObjVars.replacement: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_REPLACEMENT_H
#define OBJVARS_REPLACEMENT_H

/* obj_spawn_replacement (scripts/objkinds.py) */
typedef struct ReplacementVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s32 state;
    /* 0x250 */ s32 timer;
    /* 0x254 */ s32 unused_254; /* only ever set to a constant in the C: never read */
} ReplacementVars;

#endif
