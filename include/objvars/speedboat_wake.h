/* ObjVars.speedboat_wake: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPEEDBOAT_WAKE_H
#define OBJVARS_SPEEDBOAT_WAKE_H

/* speedboat_wake_spawn (scripts/objkinds.py) */
typedef struct SpeedboatWakeVars {
    /* 0x248 */ s16 base;
    /* 0x24A */ s16 amplitude;
    /* 0x24C */ u16 phase_step;
    /* 0x24E */ u16 phase;
} SpeedboatWakeVars;

#endif
