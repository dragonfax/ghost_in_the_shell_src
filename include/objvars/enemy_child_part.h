/* ObjVars.enemy_child_part: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_CHILD_PART_H
#define OBJVARS_ENEMY_CHILD_PART_H

/* enemy_child_part_spawn (scripts/objkinds.py) */
typedef struct EnemyChildPartVars {
    /* 0x248 */ u8 pad_248[6];
    /* 0x24E */ u16 frame_counter;
    /* 0x250 */ s16 timer;
} EnemyChildPartVars;

#endif
