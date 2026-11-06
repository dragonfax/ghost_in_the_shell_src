/* ObjVars.supermech: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SUPERMECH_H
#define OBJVARS_SUPERMECH_H

/* supermech_spawn (scripts/objkinds.py) */
typedef struct SupermechVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s32 target_x;
    /* 0x250 */ u8 pad_250[4];
    /* 0x254 */ s32 target_z;
    /* 0x258 */ u8 pad_258[4];
    /* 0x25C */ s32 center_x;
    /* 0x260 */ s32 unk_260;
    /* 0x264 */ s32 center_z;
    /* 0x268 */ s32 unk_268;
    /* 0x26C */ s32 speed;
    /* 0x270 */ s32 acceleration;
    /* 0x274 */ s16 max_health;
    /* 0x276 */ s16 yaw_offset;
    /* 0x278 */ s16 unused_278; /* only ever set to a constant in the C: never read */
    /* 0x27A */ u8 pad_27A[2];
    /* 0x27C */ s32 unk_27C;
    /* 0x280 */ s32 unk_280;
    /* 0x284 */ s32 unk_284;
} SupermechVars;

#endif
