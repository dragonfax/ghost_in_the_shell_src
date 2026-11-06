/* ObjVars.camo: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_CAMO_H
#define OBJVARS_CAMO_H

/* s05 M5 camouflaged target boss (camouflaged_target_m5_boss_phase0) */
typedef struct CamoVars {
    /* 0x248 */ u8 pad_248[0x10];
    /* 0x258 */ s16 timer;
    /* 0x25A */ s16 pad_25A;
    /* 0x25C */ M5BossModel *model;
    /* 0x260 */ u8 pad_260[0x10];
    /* 0x270 */ s16 fade_left;  /* set to 0x1000 on a left-side sound, -42 a step */
    /* 0x272 */ s16 fade_right;
} CamoVars;

#endif
