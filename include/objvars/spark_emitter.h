/* ObjVars.spark_emitter: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPARK_EMITTER_H
#define OBJVARS_SPARK_EMITTER_H

/* spark_emitter_spawn (scripts/objkinds.py) */
typedef struct SparkEmitterVars {
    /* 0x248 */ s32 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s32 model_slot;
    /* 0x250 */ s16 timer;
    /* 0x252 */ u16 toggle;
} SparkEmitterVars;

#endif
