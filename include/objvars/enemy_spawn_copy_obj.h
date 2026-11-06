/* ObjVars.enemy_spawn_copy_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_SPAWN_COPY_OBJ_H
#define OBJVARS_ENEMY_SPAWN_COPY_OBJ_H

/* enemy_spawn_copy (scripts/objkinds.py) */
typedef struct EnemySpawnCopyObjVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s32 unk_24C;
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x254 */ s32 unk_254;
    /* 0x258 */ s32 index;
} EnemySpawnCopyObjVars;

#endif
