/* ObjVars.ramp_in_out: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_RAMP_IN_OUT_H
#define OBJVARS_RAMP_IN_OUT_H

/* obj_spawn_ramp_in_out (scripts/objkinds.py) */
typedef struct RampInOutVars {
    /* 0x248 */ s16 progress;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ s16 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x24E */ u16 phase;
    /* 0x250 */ u16 rise_step;
    /* 0x252 */ u16 fall_step;
} RampInOutVars;

#endif
