/* ObjVars.spark_trail: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPARK_TRAIL_H
#define OBJVARS_SPARK_TRAIL_H

/* spark_trail_spawn (scripts/objkinds.py) */
typedef struct SparkTrailKindVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ s16 progress;
    /* 0x24E */ s16 burst_accum;
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u16 color_phase;
    /* 0x254 */ s32 origin_x;
    /* 0x258 */ s32 origin_y;
    /* 0x25C */ s32 origin_z;
    /* 0x260 */ u8 pad_260[4];
    /* 0x264 */ s32 rot_x;
    /* 0x268 */ s32 rot_z;
    /* 0x26C */ s32 parent;
} SparkTrailKindVars;

#endif
