/* ObjVars.quick_fuchikoma_m8_boss: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_QUICK_FUCHIKOMA_M8_BOSS_H
#define OBJVARS_QUICK_FUCHIKOMA_M8_BOSS_H

/* quick_fuchikoma_m8_boss_spawn (scripts/objkinds.py) */
typedef struct QuickFuchikomaM8BossVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s16 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x24E */ u16 unk_24E;
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u8 pad_252[2];
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ u8 pad_256[14];
    /* 0x264 */ s32 unk_264;
    /* 0x268 */ s32 speed_limit;
    /* 0x26C */ s32 unused_26C; /* only ever set to a constant in the C: never read */
    /* 0x270 */ s32 unused_270; /* only ever set to a constant in the C: never read */
    /* 0x274 */ s32 unused_274; /* only ever set to a constant in the C: never read */
    /* 0x278 */ u8 pad_278[4];
    /* 0x27C */ s16 frame_counter;
} QuickFuchikomaM8BossVars;

#endif
