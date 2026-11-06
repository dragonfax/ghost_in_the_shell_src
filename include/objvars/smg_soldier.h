/* ObjVars.smg_soldier: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SMG_SOLDIER_H
#define OBJVARS_SMG_SOLDIER_H

/* smg_soldier_spawn (scripts/objkinds.py) */
typedef struct SmgSoldierVars {
    /* 0x248 */ u8 pad_248[8];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 player_distance;
    /* 0x25C */ u8 pad_25C[2];
    /* 0x25E */ s16 engage_distance;
    /* 0x260 */ u8 pad_260[6];
    /* 0x266 */ s16 unk_266;
    /* 0x268 */ u8 pad_268[1];
    /* 0x269 */ u8 unk_269;
    /* 0x26A */ u8 pad_26A[10];
    /* 0x274 */ s16 unk_274;
} SmgSoldierVars;

#endif
