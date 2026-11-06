/* ObjVars.homing_rocket: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_HOMING_ROCKET_H
#define OBJVARS_HOMING_ROCKET_H

/* homing_rocket_spawn (scripts/objkinds.py) */
typedef struct HomingRocketVars {
    /* 0x248 */ s16 state;
    /* 0x24A */ s16 timer;
} HomingRocketVars;

#endif
