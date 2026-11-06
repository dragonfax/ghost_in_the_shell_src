/* ObjVars.jetski_wake: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_JETSKI_WAKE_H
#define OBJVARS_JETSKI_WAKE_H

/* jetski_wake_spawn (scripts/objkinds.py) */
typedef struct JetskiWakeVars {
    /* 0x248 */ s16 base_size;
    /* 0x24A */ s16 amplitude;
    /* 0x24C */ u16 phase_step;
    /* 0x24E */ u16 phase;
} JetskiWakeVars;

#endif
