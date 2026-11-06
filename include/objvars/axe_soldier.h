/* ObjVars.axe_soldier: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_AXE_SOLDIER_H
#define OBJVARS_AXE_SOLDIER_H

/* axe_soldier_spawn (scripts/objkinds.py) */
typedef struct AxeSoldierVars {
    /* 0x248 */ s32 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 player_distance;
    /* 0x25C */ u8 pad_25C[2];
    /* 0x25E */ s16 engage_distance;
    /* 0x260 */ u8 pad_260[6];
    /* 0x266 */ s16 unk_266;
    /* 0x268 */ u8 unk_268;
    /* 0x269 */ u8 unk_269;
} AxeSoldierVars;

#endif
