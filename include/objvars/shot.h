/* ObjVars.shot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SHOT_H
#define OBJVARS_SHOT_H

/* s02 tunnel mech shots (func_800C3D84) */
typedef struct ShotVars {
    /* 0x248 */ s32 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s16 trace_flags;
    /* 0x24E */ s16 age;
    /* 0x250 */ s32 origin[3]; /* the spawn position */
    /* 0x25C */ s16 unk_25C;
    /* 0x25E */ u8 pad_25E[2];
    /* 0x260 */ s32 vel_z;
    /* 0x264 */ s32 sound_handle;
} ShotVars;

#endif
