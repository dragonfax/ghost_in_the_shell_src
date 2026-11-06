/* ObjVars.snd: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SND_H
#define OBJVARS_SND_H

/* kinds with a sound handle at 0x24C (func_800C0E1C stops it) */
typedef struct SndVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s32 sound;
} SndVars;

#endif
