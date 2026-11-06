/* ObjVars.enemy_spawn_beeper_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_SPAWN_BEEPER_OBJ_H
#define OBJVARS_ENEMY_SPAWN_BEEPER_OBJ_H

/* enemy_spawn_beeper (scripts/objkinds.py) */
typedef struct EnemySpawnBeeperObjVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s16 blend_factor;
    /* 0x24E */ s16 unk_24E;
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ u8 pad_252[6];
    /* 0x258 */ s32 parent;
    /* 0x25C */ s32 unk_25C;
} EnemySpawnBeeperObjVars;

#endif
