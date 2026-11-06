/* ObjVars.flyer: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FLYER_H
#define OBJVARS_FLYER_H

/* flying enemy (flyer_wander) */
typedef struct FlyerVars {
    /* 0x248 */ s32 mode;
    /* 0x24C */ u8 pad_24C[8];
    /* 0x254 */ s32 wait_count; /* rand 1..3, counted down before turning */
    /* 0x258 */ s32 unk_258;
    /* 0x25C */ s16 unused_25C; /* no use in the C */
    /* 0x25E */ s16 unk_25E;
    /* 0x260 */ s16 unused_260; /* no use in the C */
    /* 0x262 */ s16 unk_262;
    /* 0x264 */ u8 pad_264[5];
    /* 0x269 */ u8 unk_269;
    /* 0x26A */ s16 target_yaw;
} FlyerVars;

#endif
