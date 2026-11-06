/* ObjVars.rolling_door: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ROLLING_DOOR_H
#define OBJVARS_ROLLING_DOOR_H

/* rolling_door_spawn (scripts/objkinds.py) */
typedef struct RollingDoorVars {
    /* 0x248 */ s32 health;
} RollingDoorVars;

#endif
