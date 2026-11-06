/* ObjVars.burst_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BURST_OBJ_H
#define OBJVARS_BURST_OBJ_H

/* burst_obj_spawn (scripts/objkinds.py) */
typedef struct BurstObjVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s16 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x254 */ u8 pad_254[2];
    /* 0x256 */ s16 trail_accum;
    /* 0x258 */ u16 trail_fade;
    /* 0x25A */ s16 unk_25A;
    /* 0x25C */ s16 trail_positions;
} BurstObjVars;

#endif
