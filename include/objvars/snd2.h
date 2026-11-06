/* ObjVars.snd2: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SND2_H
#define OBJVARS_SND2_H

/* kinds with two sound handles at 0x268 (s09 func_800C52B0 stops them) */
typedef struct Snd2Vars {
    /* 0x248 */ u8 pad_248[0x20];
    /* 0x268 */ s32 sound[2];
} Snd2Vars;

#endif
