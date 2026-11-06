/* ObjVars.anim_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ANIM_OBJ_H
#define OBJVARS_ANIM_OBJ_H

/* anim_obj_spawn (scripts/objkinds.py) */
typedef struct AnimObjVars {
    /* 0x248 */ s32 anim_data;
    /* 0x24C */ s32 models;
    /* 0x250 */ s16 frame;
    /* 0x252 */ s16 timer;
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ u8 pad_256[2];
    /* 0x258 */ s32 callback;
} AnimObjVars;

#endif
