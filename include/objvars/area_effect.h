/* ObjVars.area_effect: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_AREA_EFFECT_H
#define OBJVARS_AREA_EFFECT_H

/* area_effect_spawn (scripts/objkinds.py) */
typedef struct AreaEffectVars {
    /* 0x248 */ s16 target_id;
    /* 0x24A */ u8 pad_24A[2];
    /* 0x24C */ s16 radius;
    /* 0x24E */ u16 timer;
} AreaEffectVars;

#endif
