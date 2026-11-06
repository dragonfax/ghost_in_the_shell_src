/* ObjVars.tracer: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TRACER_H
#define OBJVARS_TRACER_H

/* s11 func_800C5F74: tracer that hits objects, then the world */
typedef struct TracerVars {
    /* 0x248 */ u16 base_a;
    /* 0x24A */ s16 jitter_a;     /* base_a + rand % 5 */
    /* 0x24C */ u16 base_b;
    /* 0x24E */ s16 jitter_b;     /* base_b + rand % 4 */
    /* 0x250 */ s32 hit;
    /* 0x254 */ s16 life;         /* -0x80 a step; freed below 0 */
    /* 0x256 */ s16 miss_a;
    /* 0x258 */ s16 miss_b;
    /* 0x25A */ u16 phase;        /* toggles each step */
    /* 0x25C */ s16 flag;
    /* 0x25E */ s16 spinning;     /* 1: yaw turns 0x18 a step */
    /* 0x260 */ s16 reverse;      /* nonzero: turns the other way */
} TracerVars;

#endif
