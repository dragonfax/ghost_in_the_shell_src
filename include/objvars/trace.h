/* ObjVars.trace: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TRACE_H
#define OBJVARS_TRACE_H

/* s04 kinds that trace a line between two objects (func_800B7F18) */
typedef struct TraceVars {
    /* 0x248 */ u8 pad_248[2];
    /* 0x24A */ s16 aim_yaw;
    /* 0x24C */ s16 trace_flags;
    /* 0x24E */ s16 active;    /* nonzero: trace */
    /* 0x250 */ u8 pad_250[8];
    /* 0x258 */ struct Object *from;
    /* 0x25C */ struct Object *to;
} TraceVars;

#endif
