/* ObjVars.enemy_spawn_shooter_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_SPAWN_SHOOTER_OBJ_H
#define OBJVARS_ENEMY_SPAWN_SHOOTER_OBJ_H

/* enemy_spawn_shooter (scripts/objkinds.py) */
typedef struct EnemySpawnShooterObjVars {
    /* 0x248 */ u8 pad_248[32];
    /* 0x268 */ s32 unused_268; /* only ever set to a constant in the C: never read */
    /* 0x26C */ u8 pad_26C[8];
    /* 0x274 */ s16 unused_274; /* only ever set to a constant in the C: never read */
    /* 0x276 */ s16 unk_276;
} EnemySpawnShooterObjVars;

#endif
