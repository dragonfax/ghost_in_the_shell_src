/* ObjVars.helicopter: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_HELICOPTER_H
#define OBJVARS_HELICOPTER_H

/* helicopter_spawn (scripts/objkinds.py) */
typedef struct HelicopterVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 crash_effect_count;
    /* 0x24C */ s32 spawn_y;
    /* 0x250 */ u16 yaw;
    /* 0x252 */ u16 unk_252;
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ u16 unk_256;
    /* 0x258 */ u16 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25A */ s16 timer;
    /* 0x25C */ s16 fire_countdown;
    /* 0x25E */ s16 unk_25E;
    /* 0x260 */ u8 pad_260[4];
    /* 0x264 */ s32 unk_264;
    /* 0x268 */ s32 sound_handle;
    /* 0x26C */ s32 fly_sound_handle;
} HelicopterVars;

#endif
