/* ObjVars.enemy_spawn_from: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_SPAWN_FROM_H
#define OBJVARS_ENEMY_SPAWN_FROM_H

/* enemy_spawn_from_place (scripts/objkinds.py) */
typedef struct EnemySpawnFromVars {
    /* 0x248 */ s32 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 player_dist;
    /* 0x25C */ u8 pad_25C[2];
    /* 0x25E */ s16 sense_range;
    /* 0x260 */ u8 pad_260[6];
    /* 0x266 */ s16 unk_266;
    /* 0x268 */ u8 pad_268[1];
    /* 0x269 */ u8 unk_269;
} EnemySpawnFromVars;

#endif
