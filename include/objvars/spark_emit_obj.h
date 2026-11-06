/* ObjVars.spark_emit_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPARK_EMIT_OBJ_H
#define OBJVARS_SPARK_EMIT_OBJ_H

/* spark_emit_spawn (scripts/objkinds.py) */
typedef struct SparkEmitObjVars {
    /* 0x248 */ s16 pchr_base;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ u16 unk_24E;
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s16 radius;
    /* 0x25E */ s16 unused_25E; /* only ever set to a constant in the C: never read */
    /* 0x260 */ s32 sound_handle;
    /* 0x264 */ s32 owner;
} SparkEmitObjVars;

#endif
