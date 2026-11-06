/* ObjVars.spark_or_shot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPARK_OR_SHOT_H
#define OBJVARS_SPARK_OR_SHOT_H

/* spark_or_shot_spawn (scripts/objkinds.py) */
typedef struct SparkOrShotVars {
    /* 0x248 */ s16 effect_base;
    /* 0x24A */ u16 mode;
    /* 0x24C */ s16 trace_flags;
    /* 0x24E */ u16 blend_factor;
} SparkOrShotVars;

#endif
