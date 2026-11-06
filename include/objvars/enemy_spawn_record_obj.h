/* ObjVars.enemy_spawn_record_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_SPAWN_RECORD_OBJ_H
#define OBJVARS_ENEMY_SPAWN_RECORD_OBJ_H

/* enemy_spawn_record (scripts/objkinds.py) */
typedef struct EnemySpawnRecordObjVars {
    /* 0x248 */ u8 pad_248[20];
    /* 0x25C */ s16 unused_25C; /* only ever set to a constant in the C: never read */
} EnemySpawnRecordObjVars;

#endif
