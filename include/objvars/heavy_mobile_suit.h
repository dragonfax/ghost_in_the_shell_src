/* ObjVars.heavy_mobile_suit: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_HEAVY_MOBILE_SUIT_H
#define OBJVARS_HEAVY_MOBILE_SUIT_H

/* heavy_mobile_suit_place, heavy_mobile_suit_spawn (scripts/objkinds.py) */
typedef struct HeavyMobileSuitVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u8 pad_24A[2];
    /* 0x24C */ s32 unk_24C;
    /* 0x250 */ s16 timer;
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
    /* 0x254 */ u8 pad_254[2];
    /* 0x256 */ u16 aim_yaw;
    /* 0x258 */ u16 unk_258;
    /* 0x25A */ s16 blend_weight;
    /* 0x25C */ s32 unk_25C;
    /* 0x260 */ s32 unk_260;
    /* 0x264 */ s32 unk_264;
    /* 0x268 */ u8 pad_268[12];
    /* 0x274 */ s16 unk_274;
} HeavyMobileSuitVars;

#endif
