/* ObjVars.camouflaged_target_m5_boss: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_CAMOUFLAGED_TARGET_M5_BOSS_H
#define OBJVARS_CAMOUFLAGED_TARGET_M5_BOSS_H

/* camouflaged_target_m5_boss_spawn (scripts/objkinds.py) */
typedef struct CamouflagedTargetM5BossVars {
    /* 0x248 */ s16 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24A */ s16 unk_24A;
    /* 0x24C */ s16 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x24E */ u16 unused_24E; /* only ever set to a constant in the C: never read */
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u16 unk_252;
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ s16 health_mark;
    /* 0x258 */ s16 unk_258;
    /* 0x25A */ s16 last_surface_id;
    /* 0x25C */ s32 pose_table;
    /* 0x260 */ s32 unused_260; /* only ever set to a constant in the C: never read */
    /* 0x264 */ s32 unused_264; /* only ever set to a constant in the C: never read */
    /* 0x268 */ s32 target_z;
    /* 0x26C */ s32 target_x;
    /* 0x270 */ s16 unk_270;
    /* 0x272 */ s16 sound;
} CamouflagedTargetM5BossVars;

#endif
