/* ObjVars.rocket_boat_shot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ROCKET_BOAT_SHOT_H
#define OBJVARS_ROCKET_BOAT_SHOT_H

/* rocket_boat_shot_spawn (scripts/objkinds.py) */
typedef struct RocketBoatShotVars {
    /* 0x248 */ s16 frame_base;
    /* 0x24A */ u8 pad_24A[6];
    /* 0x250 */ s32 extra_vy;
} RocketBoatShotVars;

#endif
