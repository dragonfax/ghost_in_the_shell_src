/* ObjVars.burst_shot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BURST_SHOT_H
#define OBJVARS_BURST_SHOT_H

/* burst_shot_spawn (scripts/objkinds.py) */
typedef struct BurstShotVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 model;
    /* 0x24C */ s16 second_model;
    /* 0x24E */ s16 unk_24E;
    /* 0x250 */ u16 toggle;
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
} BurstShotVars;

#endif
