/* ObjVars.minicopter: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_MINICOPTER_H
#define OBJVARS_MINICOPTER_H

/* minicopter_spawn (scripts/objkinds.py) */
typedef struct MinicopterVars {
    /* 0x248 */ s16 weave_angle;
    /* 0x24A */ u16 pursue_timer;
    /* 0x24C */ s16 draw_toggle;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 base_y;
    /* 0x254 */ s16 yaw;
    /* 0x256 */ u16 part1_angle;
    /* 0x258 */ u16 part2_angle;
    /* 0x25A */ s16 part3_angle;
    /* 0x25C */ s32 prev_yaw;
    /* 0x260 */ s32 part_slot;
    /* 0x264 */ u8 pad_264[4];
    /* 0x268 */ u8 spawn_sound_handle;
    /* 0x269 */ u8 loop_sound_handle;
} MinicopterVars;

#endif
