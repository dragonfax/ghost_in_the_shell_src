/* ObjVars.obj_expanding_blast: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_OBJ_EXPANDING_BLAST_H
#define OBJVARS_OBJ_EXPANDING_BLAST_H

/* obj_expanding_blast_spawn (scripts/objkinds.py) */
typedef struct ObjExpandingBlastVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s16 progress;
    /* 0x24E */ s16 damage_radius;
    /* 0x250 */ s32 sound_handle;
} ObjExpandingBlastVars;

#endif
