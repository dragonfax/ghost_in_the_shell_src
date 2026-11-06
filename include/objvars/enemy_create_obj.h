/* ObjVars.enemy_create_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_CREATE_OBJ_H
#define OBJVARS_ENEMY_CREATE_OBJ_H

/* enemy_create (scripts/objkinds.py) */
typedef struct EnemyCreateObjVars {
    /* 0x248 */ u8 pad_248[4];
    /* 0x24C */ s32 timer;
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 player_distance;
    /* 0x25C */ u8 pad_25C[2];
    /* 0x25E */ s16 activation_distance;
    /* 0x260 */ u8 pad_260[6];
    /* 0x266 */ s16 unk_266;
    /* 0x268 */ u8 pad_268[1];
    /* 0x269 */ u8 unk_269;
    /* 0x26A */ u8 pad_26A[10];
    /* 0x274 */ s16 unk_274;
    /* 0x276 */ s16 unk_276;
} EnemyCreateObjVars;

#endif
