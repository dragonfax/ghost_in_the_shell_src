/* ObjVars.mine: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_MINE_H
#define OBJVARS_MINE_H

/* s06 motorcycle mines (motorcycle_mine_update) */
typedef struct MineVars {
    /* 0x248 */ u8 pad_248[8];
    /* 0x250 */ u8 sound_played; /* set once the arming sound has played */
    /* 0x251 */ u8 pad_251[0x2B];
    /* 0x27C */ s32 cam_dist;    /* distance to the camera, set every frame */
} MineVars;

#endif
