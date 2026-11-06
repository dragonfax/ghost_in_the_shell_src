/* ObjVars.muzzle_shot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_MUZZLE_SHOT_H
#define OBJVARS_MUZZLE_SHOT_H

/* muzzle_shot_spawn (scripts/objkinds.py) */
typedef struct MuzzleShotVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ u8 pad_254[18];
    /* 0x266 */ s16 flow;
} MuzzleShotVars;

#endif
