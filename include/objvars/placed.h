/* ObjVars.placed: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PLACED_H
#define OBJVARS_PLACED_H

/* obj_spawn_placed (scripts/objkinds.py) */
typedef struct PlacedVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u8 pad_24A[2];
    /* 0x24C */ s32 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x250 */ u16 unk_250;
} PlacedVars;

#endif
