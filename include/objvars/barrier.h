/* ObjVars.barrier: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BARRIER_H
#define OBJVARS_BARRIER_H

/* s06 road barrier with traffic cone (road_barrier_with_traffic_cone_phase0) */
typedef struct BarrierVars {
    /* 0x248 */ s16 spin;     /* yaw step while knocked over */
    /* 0x24A */ u8 landed;    /* 1 after the first bounce */
    /* 0x24B */ u8 knocked;   /* 1: hit by the player */
} BarrierVars;

#endif
