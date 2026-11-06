/* ObjVars.obj_grow_fade: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_OBJ_GROW_FADE_H
#define OBJVARS_OBJ_GROW_FADE_H

/* obj_grow_fade_spawn (scripts/objkinds.py) */
typedef struct ObjGrowFadeVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 blend_amount;
    /* 0x24C */ s16 brightness;
    /* 0x24E */ u16 frame_count;
} ObjGrowFadeVars;

#endif
