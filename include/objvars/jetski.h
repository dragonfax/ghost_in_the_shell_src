/* ObjVars.jetski: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_JETSKI_H
#define OBJVARS_JETSKI_H

/* jetski_spawn (scripts/objkinds.py) */
typedef struct JetskiVars {
    /* 0x248 */ s16 script_index;
    /* 0x24A */ s16 destroy_step;
    /* 0x24C */ s16 aim_yaw;
    /* 0x24E */ u16 unk_24E;
    /* 0x250 */ s16 state;
    /* 0x252 */ s16 state_timer;
    /* 0x254 */ s16 heading;
    /* 0x256 */ s16 range;
    /* 0x258 */ s32 slide_speed;
    /* 0x25C */ s32 drift_speed;
    /* 0x260 */ u8 pad_260[4];
    /* 0x264 */ s32 sound_id;
    /* 0x268 */ u8 flow;
} JetskiVars;

#endif
