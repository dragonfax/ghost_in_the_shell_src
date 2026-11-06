/* ObjVars.after: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_AFTER_H
#define OBJVARS_AFTER_H

/* obj_spawn_after (scripts/objkinds.py) */
typedef struct AfterVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ u16 unused_24E; /* only ever set to a constant in the C: never read */
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ s32 near_ring;
    /* 0x258 */ s32 far_ring;
} AfterVars;

#endif
