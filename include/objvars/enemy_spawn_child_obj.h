/* ObjVars.enemy_spawn_child_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_SPAWN_CHILD_OBJ_H
#define OBJVARS_ENEMY_SPAWN_CHILD_OBJ_H

/* enemy_spawn_child (scripts/objkinds.py) */
typedef struct EnemySpawnChildObjVars {
    /* 0x248 */ s32 model;
    /* 0x24C */ s16 progress;
    /* 0x24E */ u16 unused_24E; /* only ever set to a constant in the C: never read */
    /* 0x250 */ u16 phase;
    /* 0x252 */ u16 progress_step;
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ s16 unk_256;
    /* 0x258 */ s32 parent;
} EnemySpawnChildObjVars;

#endif
