/* ObjVars.fn_800BBB78_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FN_800BBB78_OBJ_H
#define OBJVARS_FN_800BBB78_OBJ_H

/* rocket_fuchikoma_spawn (scripts/objkinds.py) */
typedef struct Fn800BBB78ObjVars {
    /* 0x248 */ s16 pitch;
    /* 0x24A */ u16 yaw;
    /* 0x24C */ s16 roll;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
} Fn800BBB78ObjVars;

#endif
