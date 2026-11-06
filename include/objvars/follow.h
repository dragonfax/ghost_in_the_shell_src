/* ObjVars.follow: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FOLLOW_H
#define OBJVARS_FOLLOW_H

/* s03 sound that follows a target and fades in, holds, fades out (func_800C2EF8) */
typedef struct FollowVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s16 level;     /* 0..0x1000 within the phase */
    /* 0x24E */ s16 unk_24E;
    /* 0x250 */ s16 phase;     /* 0 fade in, 1 hold, 2 fade out */
    /* 0x252 */ u8 pad_252[2];
    /* 0x254 */ s32 toggle;
    /* 0x258 */ struct Object *target;
    /* 0x25C */ s32 sound;
} FollowVars;

#endif
