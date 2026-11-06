/* ObjVars.giant_robot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_GIANT_ROBOT_H
#define OBJVARS_GIANT_ROBOT_H

/* giant_robot_spawn (scripts/objkinds.py) */
typedef struct GiantRobotVars {
    /* 0x248 */ s32 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s32 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x250 */ s16 turn_speed;
    /* 0x252 */ u16 script_vars;
    /* 0x254 */ s16 unused_254; /* only ever set to a constant in the C: never read */
    /* 0x256 */ u16 unused_256; /* only ever set to a constant in the C: never read */
    /* 0x258 */ u16 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25A */ s16 random_roll;
    /* 0x25C */ s16 unk_25C;
    /* 0x25E */ s16 max_health;
} GiantRobotVars;

#endif
