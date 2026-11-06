/* ObjVars.fighter_jet: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FIGHTER_JET_H
#define OBJVARS_FIGHTER_JET_H

/* fighter_jet_spawn (scripts/objkinds.py) */
typedef struct FighterJetVars {
    /* 0x248 */ s16 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s16 toggle;
    /* 0x24E */ s16 timer;
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 sound;
} FighterJetVars;

#endif
