/* ObjVars.ramp: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_RAMP_H
#define OBJVARS_RAMP_H

/* obj_spawn_ramp (scripts/objkinds.py) */
typedef struct RampVars {
    /* 0x248 */ s32 blend;
    /* 0x24C */ s32 unk_24C;
} RampVars;

#endif
