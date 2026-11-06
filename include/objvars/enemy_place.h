/* ObjVars.enemy_place: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_PLACE_H
#define OBJVARS_ENEMY_PLACE_H

/* enemy_place_spawn (scripts/objkinds.py) */
typedef struct EnemyPlaceVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ u16 unk_24C;
    /* 0x24E */ u16 unk_24E;
    /* 0x250 */ u16 unk_250;
    /* 0x252 */ u16 unk_252;
    /* 0x254 */ u16 unk_254;
    /* 0x256 */ u8 pad_256[2];
    /* 0x258 */ u16 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25A */ s16 unused_25A; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s16 unused_25C; /* only ever set to a constant in the C: never read */
    /* 0x25E */ s16 unused_25E; /* only ever set to a constant in the C: never read */
} EnemyPlaceVars;

#endif
