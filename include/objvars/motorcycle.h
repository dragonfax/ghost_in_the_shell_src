/* ObjVars.motorcycle: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_MOTORCYCLE_H
#define OBJVARS_MOTORCYCLE_H

/* motorcycle_spawn (scripts/objkinds.py) */
typedef struct MotorcycleVars {
    /* 0x248 */ s16 variant;
    /* 0x24A */ u8 pad_24A[2];
    /* 0x24C */ s16 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x24E */ u16 unused_24E; /* only ever set to a constant in the C: never read */
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
    /* 0x254 */ u8 pad_254[20];
    /* 0x268 */ s32 sound_handle;
    /* 0x26C */ u8 pad_26C[20];
    /* 0x280 */ s16 unk_280;
} MotorcycleVars;

#endif
