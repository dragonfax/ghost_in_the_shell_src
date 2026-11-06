/* ObjVars.fixed: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FIXED_H
#define OBJVARS_FIXED_H

/* obj_spawn_fixed (scripts/objkinds.py) */
typedef struct FixedVars {
    /* 0x248 */ u8 pad_248[4];
    /* 0x24C */ s32 unk_24C;
    /* 0x250 */ s32 age;
    /* 0x254 */ u8 pad_254[24];
    /* 0x26C */ s32 flags;
    /* 0x270 */ u8 pad_270[4];
    /* 0x274 */ s32 unk_274;
} FixedVars;

#endif
