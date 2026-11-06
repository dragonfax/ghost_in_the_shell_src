/* ObjVars.spark_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPARK_OBJ_H
#define OBJVARS_SPARK_OBJ_H

/* spark_obj_spawn (scripts/objkinds.py) */
typedef struct SparkObjVars {
    /* 0x248 */ s32 mode;
    /* 0x24C */ s32 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x254 */ s32 unk_254;
} SparkObjVars;

#endif
