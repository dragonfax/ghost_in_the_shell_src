/* ObjVars.enemy_fire_rocket_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_FIRE_ROCKET_OBJ_H
#define OBJVARS_ENEMY_FIRE_ROCKET_OBJ_H

/* enemy_fire_rocket (scripts/objkinds.py) */
typedef struct EnemyFireRocketObjVars {
    /* 0x248 */ u8 pad_248[2];
    /* 0x24A */ s16 burst_count;
    /* 0x24C */ s32 spark_index;
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ u8 pad_252[2];
    /* 0x254 */ s32 spark_a_x;
    /* 0x258 */ s32 spark_a_y;
    /* 0x25C */ s32 spark_a_z;
    /* 0x260 */ s32 spark_b_x;
    /* 0x264 */ s32 spark_b_y;
    /* 0x268 */ s32 spark_b_z;
    /* 0x26C */ s32 unk_26C;
} EnemyFireRocketObjVars;

#endif
