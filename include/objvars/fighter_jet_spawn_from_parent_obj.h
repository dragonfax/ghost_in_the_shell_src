/* ObjVars.fighter_jet_spawn_from_parent_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FIGHTER_JET_SPAWN_FROM_PARENT_OBJ_H
#define OBJVARS_FIGHTER_JET_SPAWN_FROM_PARENT_OBJ_H

/* fighter_jet_spawn_from_parent (scripts/objkinds.py) */
typedef struct FighterJetSpawnFromParentObjVars {
    /* 0x248 */ s16 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s16 effect_side;
    /* 0x24E */ u16 life_timer;
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 parent;
    /* 0x25C */ s32 sound_handle;
} FighterJetSpawnFromParentObjVars;

#endif
