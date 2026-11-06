/* ObjVars.enemy_shot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_SHOT_H
#define OBJVARS_ENEMY_SHOT_H

/* enemy_shot_spawn (scripts/objkinds.py) */
typedef struct EnemyShotVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s16 follow_offset_index;
    /* 0x24E */ u16 unused_24E; /* only ever set to a constant in the C: never read */
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ u16 unk_256;
    /* 0x258 */ s16 unk_258;
    /* 0x25A */ u8 pad_25A[2];
    /* 0x25C */ s32 parent;
} EnemyShotVars;

#endif
