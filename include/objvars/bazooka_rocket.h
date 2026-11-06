/* ObjVars.bazooka_rocket: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BAZOOKA_ROCKET_H
#define OBJVARS_BAZOOKA_ROCKET_H

/* bazooka_rocket_spawn (scripts/objkinds.py) */
typedef struct BazookaRocketVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u8 pad_24A[2];
    /* 0x24C */ s32 done;
} BazookaRocketVars;

#endif
