/* ObjVars.from: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FROM_H
#define OBJVARS_FROM_H

/* obj_spawn_from_place (scripts/objkinds.py) */
typedef struct FromVars {
    /* 0x248 */ s32 origin_x;
    /* 0x24C */ s32 origin_y;
    /* 0x250 */ s32 origin_z;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 unk_258;
    /* 0x25C */ s32 unused_25C; /* only ever set to a constant in the C: never read */
    /* 0x260 */ s32 angle_step;
    /* 0x264 */ s32 flags;
    /* 0x268 */ s32 unk_268;
    /* 0x26C */ s32 swing_range;
    /* 0x270 */ s32 unk_270;
    /* 0x274 */ s32 unk_274;
    /* 0x278 */ s32 player_dist;
} FromVars;

#endif
