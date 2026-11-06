/* ObjVars.pair: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PAIR_H
#define OBJVARS_PAIR_H

/* kinds holding two linked objects (s10 func_800C30C4) */
typedef struct PairVars {
    /* 0x248 */ s16 side;    /* passed to func_800C1E10 */
    /* 0x24A */ u8 pad_24A[6];
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ u8 pad_252[0xA];
    /* 0x25C */ struct Object *partner;
    /* 0x260 */ struct Object *child;
    /* 0x264 */ u8 pad_264[6];
    /* 0x26A */ s16 timer;
} PairVars;

#endif
