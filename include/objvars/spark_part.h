/* ObjVars.spark_part: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPARK_PART_H
#define OBJVARS_SPARK_PART_H

/* s06 func_800C664C: a part that draws sparks at three points and posts two pose rotations */
typedef struct SparkPartVars {
    /* 0x248 */ struct Object *parent; /* its vars.part.unk_278 nonzero: drawn */
    /* 0x24C */ s32 x, y, z;          /* spark origin */
    /* 0x258 */ u8 pad_258[6];
    /* 0x25E */ s16 spark_yaw;
    /* 0x260 */ u8 pad_260[4];
    /* 0x264 */ s16 spark_c[3];       /* offsets from x, y, z */
    /* 0x26A */ u8 pad_26A[2];
    /* 0x26C */ s16 spark_b[3];
    /* 0x272 */ u8 pad_272[2];
    /* 0x274 */ s16 spark_a[3];
    /* 0x27A */ u8 pad_27A[2];
    /* 0x27C */ u16 pose_rot;
    /* 0x27E */ u8 pad_27E[4];
    /* 0x282 */ s16 model_offset;     /* added to the parent's model slot for spark_c */
} SparkPartVars;

#endif
