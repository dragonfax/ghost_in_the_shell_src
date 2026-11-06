/* ObjVars.arrival_warning: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ARRIVAL_WARNING_H
#define OBJVARS_ARRIVAL_WARNING_H

/* arrival_warning_spawn (scripts/objkinds.py) */
typedef struct ArrivalWarningVars {
    /* 0x248 */ s32 sound_a;
    /* 0x24C */ s32 sound_b;
} ArrivalWarningVars;

#endif
