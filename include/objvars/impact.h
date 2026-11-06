/* ObjVars.impact: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_IMPACT_H
#define OBJVARS_IMPACT_H

/* impact_spawn (scripts/objkinds.py) */
typedef struct ImpactVars {
    /* 0x248 */ s16 progress;
    /* 0x24A */ s16 level;
    /* 0x24C */ s16 max_scale;
    /* 0x24E */ u16 phase;
    /* 0x250 */ u16 rise_step;
    /* 0x252 */ u16 fall_step;
} ImpactVars;

#endif
