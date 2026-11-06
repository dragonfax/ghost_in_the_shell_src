/* ObjVars.stage: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_STAGE_H
#define OBJVARS_STAGE_H

/* stage_init (scripts/objkinds.py) */
typedef struct StageVars {
    /* 0x248 */ u8 pad_248[6];
    /* 0x24E */ u16 unk_24E;
    /* 0x250 */ u8 pad_250[2];
    /* 0x252 */ u16 unk_252;
    /* 0x254 */ s16 unk_254;
} StageVars;

#endif
