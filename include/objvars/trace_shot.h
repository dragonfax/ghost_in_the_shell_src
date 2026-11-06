/* ObjVars.trace_shot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TRACE_SHOT_H
#define OBJVARS_TRACE_SHOT_H

/* trace_shot_init shot */
typedef struct TraceShotVars {
    /* 0x248 */ s32 done;
    /* 0x24C */ s16 mode;   /* 0: speed 1200, traced 1 step; else speed 40, 6 steps */
    /* 0x24E */ s16 unused_24E; /* only ever set to a constant in the C: never read */
    /* 0x250 */ s32 start[3];  /* spawn position, whole units */
    /* 0x25C */ s16 offset[3]; /* added to the velocity */
    /* 0x262 */ s16 pad_262;
    /* 0x264 */ s32 dir[3];    /* (0, 0, 100) rotated by the spawn angles */
    /* 0x270 */ Countdown trace;
} TraceShotVars;

#endif
