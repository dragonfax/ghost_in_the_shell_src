/* ObjVars.ceiling_bomber: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_CEILING_BOMBER_H
#define OBJVARS_CEILING_BOMBER_H

/* ceiling_bomber_spawn (scripts/objkinds.py) */
typedef struct CeilingBomberVars {
    /* 0x248 */ s32 rot_matrix;
    /* 0x24C */ u8 pad_24C[28];
    /* 0x268 */ s32 offset_x;
    /* 0x26C */ s32 offset_y;
    /* 0x270 */ s32 offset_z;
    /* 0x274 */ u8 pad_274[4];
    /* 0x278 */ s32 angle;
} CeilingBomberVars;

#endif
