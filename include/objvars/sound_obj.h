/* ObjVars.sound_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SOUND_OBJ_H
#define OBJVARS_SOUND_OBJ_H

/* sound_obj_spawn (scripts/objkinds.py) */
typedef struct SoundObjVars {
    /* 0x248 */ s32 source_obj;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x254 */ s32 unused_254; /* only ever set to a constant in the C: never read */
} SoundObjVars;

#endif
