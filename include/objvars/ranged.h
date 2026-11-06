/* ObjVars.ranged: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_RANGED_H
#define OBJVARS_RANGED_H

/* obj_spawn_ranged (scripts/objkinds.py) */
typedef struct RangedVars {
    /* 0x248 */ u8 pad_248[4];
    /* 0x24C */ s32 unk_24C;
    /* 0x250 */ s32 range_remaining;
} RangedVars;

#endif
