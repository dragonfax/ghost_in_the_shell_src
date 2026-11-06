/* ObjVars.enemy_part_child: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_PART_CHILD_H
#define OBJVARS_ENEMY_PART_CHILD_H

/* enemy_part_child_spawn (scripts/objkinds.py) */
typedef struct EnemyPartChildVars {
    /* 0x248 */ s32 owner;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
} EnemyPartChildVars;

#endif
