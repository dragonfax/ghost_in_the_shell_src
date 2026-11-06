/* ObjVars.copter: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_COPTER_H
#define OBJVARS_COPTER_H

/* s06 minicopter: flow-driven hover */
typedef struct CopterVars {
    /* 0x248 */ u8 pad_248[0x16];
    /* 0x25E */ s16 fire_delay;  /* func_800BE500: steps until the next shot */
    /* 0x260 */ Flow current; /* speed: get_flow_max() each step */
} CopterVars;

#endif
