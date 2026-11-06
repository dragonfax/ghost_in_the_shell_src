/* ObjVars.enemy_child: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_CHILD_H
#define OBJVARS_ENEMY_CHILD_H

/* enemy_child_spawn (scripts/objkinds.py) */
typedef struct EnemyChildVars {
    /* 0x248 */ u8 pad_248[20];
    /* 0x25C */ s16 unk_25C;
    /* 0x25E */ u8 pad_25E[30];
    /* 0x27C */ s16 unused_27C; /* only ever set to a constant in the C: never read */
    /* 0x27E */ u8 pad_27E[2];
    /* 0x280 */ s16 unk_280;
    /* 0x282 */ s16 unused_282; /* only ever set to a constant in the C: never read */
} EnemyChildVars;

#endif
