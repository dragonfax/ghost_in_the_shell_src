/* ObjVars.child: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_CHILD_H
#define OBJVARS_CHILD_H

/* obj_spawn_child (scripts/objkinds.py) */
typedef struct ChildVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s16 progress;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 unk_250;
} ChildVars;

#endif
