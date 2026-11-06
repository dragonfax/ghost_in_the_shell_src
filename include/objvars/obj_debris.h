/* ObjVars.obj_debris: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_OBJ_DEBRIS_H
#define OBJVARS_OBJ_DEBRIS_H

/* obj_debris_spawn (scripts/objkinds.py) */
typedef struct ObjDebrisVars {
    /* 0x248 */ s16 variant;
    /* 0x24A */ u16 kind;
    /* 0x24C */ s16 trace_mask;
    /* 0x24E */ s16 age;
    /* 0x250 */ s16 lifetime;
    /* 0x252 */ u16 phase;
    /* 0x254 */ s32 unused_254; /* only ever set to a constant in the C: never read */
    /* 0x258 */ s16 damage_scale;
} ObjDebrisVars;

#endif
