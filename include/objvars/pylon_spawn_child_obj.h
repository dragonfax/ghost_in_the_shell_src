/* ObjVars.pylon_spawn_child_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PYLON_SPAWN_CHILD_OBJ_H
#define OBJVARS_PYLON_SPAWN_CHILD_OBJ_H

/* pylon_spawn_child (scripts/objkinds.py) */
typedef struct PylonSpawnChildObjVars {
    /* 0x248 */ s16 child_index;
    /* 0x24A */ s16 unk_24A;
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
} PylonSpawnChildObjVars;

#endif
