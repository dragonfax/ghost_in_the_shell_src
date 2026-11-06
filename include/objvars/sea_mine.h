/* ObjVars.sea_mine: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SEA_MINE_H
#define OBJVARS_SEA_MINE_H

/* sea_mine_spawn (scripts/objkinds.py) */
typedef struct SeaMineVars {
    /* 0x248 */ s16 frame_counter;
    /* 0x24A */ u16 trigger_timer;
    /* 0x24C */ s16 fuse_time;
    /* 0x24E */ u16 anim_frame;
    /* 0x250 */ s16 anim_timer;
    /* 0x252 */ s16 anim_index;
    /* 0x254 */ s16 start_y;
    /* 0x256 */ s16 triggered;
    /* 0x258 */ u16 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25A */ s16 unk_25A;
    /* 0x25C */ s16 unk_25C;
} SeaMineVars;

#endif
