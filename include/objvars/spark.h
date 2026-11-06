/* ObjVars.spark: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPARK_H
#define OBJVARS_SPARK_H

/* spark_spawn (scripts/objkinds.py) */
typedef struct SparkVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 unk_24A;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s32 range_start;
    /* 0x254 */ s32 range_end;
    /* 0x258 */ s32 life_step;
    /* 0x25C */ s32 life_progress;
    /* 0x260 */ s32 brightness;
    /* 0x264 */ s32 brightness_step;
    /* 0x268 */ s32 frame;
    /* 0x26C */ s32 scale;
} SparkVars;

#endif
