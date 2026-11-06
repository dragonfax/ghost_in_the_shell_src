/* ObjVars.rocket: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ROCKET_H
#define OBJVARS_ROCKET_H

/* s06 motorcycle_rocket_update */
typedef struct RocketVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ s16 trace_flags;
    /* 0x24E */ u16 life_counter;
    /* 0x250 */ s32 age;         /* frames since launch */
    /* 0x254 */ u8 pad_254[0x18];
    /* 0x26C */ s32 flags;
    /* 0x270 */ s32 strafe_angle;
    /* 0x274 */ s32 roll_step;   /* added to roll each frame */
    /* 0x278 */ s32 pad_278;
    /* 0x27C */ s32 cam_dist;    /* distance to the camera */
} RocketVars;

#endif
