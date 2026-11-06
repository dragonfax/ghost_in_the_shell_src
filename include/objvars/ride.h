/* ObjVars.ride: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_RIDE_H
#define OBJVARS_RIDE_H

/* s09 kind that starts two looping sounds when the player steps on it (func_800B9C10) */
typedef struct RideVars {
    /* 0x248 */ u8 moving;      /* 1 once started */
    /* 0x249 */ u8 enabled;
    /* 0x24A */ s16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s32 sound;
    /* 0x250 */ s32 sound2;
} RideVars;

#endif
