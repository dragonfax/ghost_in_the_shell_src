/* ObjVars.drift: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_DRIFT_H
#define OBJVARS_DRIFT_H

/* kinds that drift with a flow (s04 func_800C18A8) */
typedef struct DriftVars {
    /* 0x248 */ u8 pad_248[8];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ u8 pad_254[0x10];
    /* 0x264 */ Flow current; /* speed: get_flow_max() each step */
} DriftVars;

#endif
