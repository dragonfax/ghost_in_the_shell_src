/* ObjVars.spark_fx: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPARK_FX_H
#define OBJVARS_SPARK_FX_H

/* spark_fx_spawn (scripts/objkinds.py) */
typedef struct SparkFxVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s16 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x24E */ u16 unused_24E; /* only ever set to a constant in the C: never read */
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u8 pad_252[2];
    /* 0x254 */ s32 unused_254; /* only ever set to a constant in the C: never read */
} SparkFxVars;

#endif
