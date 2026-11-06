/* ObjVars.obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_OBJ_H
#define OBJVARS_OBJ_H

/* obj_spawn (scripts/objkinds.py) */
typedef struct ObjKindVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 mode;
    /* 0x24C */ s16 frame_count;
} ObjKindVars;

#endif
