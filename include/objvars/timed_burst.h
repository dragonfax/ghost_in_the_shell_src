/* ObjVars.timed_burst: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TIMED_BURST_H
#define OBJVARS_TIMED_BURST_H

/* spawn_timed_burst (scripts/objkinds.py) */
typedef struct TimedBurstVars {
    /* 0x248 */ s16 countdown;
    /* 0x24A */ u16 tag;
} TimedBurstVars;

#endif
