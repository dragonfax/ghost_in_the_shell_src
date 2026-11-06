/* ObjVars.triple_barrel_robot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TRIPLE_BARREL_ROBOT_H
#define OBJVARS_TRIPLE_BARREL_ROBOT_H

/* triple_barrel_robot_spawn (scripts/objkinds.py) */
typedef struct TripleBarrelRobotVars {
    /* 0x248 */ s16 pitch;
    /* 0x24A */ u16 yaw;
    /* 0x24C */ s16 roll;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ u16 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25A */ s16 unk_25A;
} TripleBarrelRobotVars;

#endif
