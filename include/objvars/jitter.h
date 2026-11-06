/* ObjVars.jitter: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_JITTER_H
#define OBJVARS_JITTER_H

/* s07 kinds that shake on screen (func_800C4158) */
typedef struct JitterVars {
    /* 0x248 */ u8 pad_248[0x18];
    /* 0x260 */ s16 timer;     /* < 8: jitter; wraps to 1 */
} JitterVars;

#endif
