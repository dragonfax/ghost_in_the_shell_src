/* ObjVars.at: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_AT_H
#define OBJVARS_AT_H

/* obj_spawn_at (scripts/objkinds.py) */
typedef struct AtVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ s16 unk_24E;
    /* 0x250 */ s16 fade_timer;
    /* 0x252 */ s16 fade_level;
    /* 0x254 */ s16 origin_x;
    /* 0x256 */ s16 origin_y;
    /* 0x258 */ s16 origin_z;
    /* 0x25A */ s16 unused_25A; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s16 unk_25C;
} AtVars;

#endif
