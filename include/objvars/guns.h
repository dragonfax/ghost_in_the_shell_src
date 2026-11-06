/* ObjVars.guns: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_GUNS_H
#define OBJVARS_GUNS_H

/* s13 twin guns firing in bursts (func_800BB918) */
typedef struct GunsVars {
    /* 0x248 */ u8 pad_248[0xD];
    /* 0x255 */ u8 firing;
    /* 0x256 */ u8 bursts_left;
    /* 0x257 */ u8 burst_delay;
    /* 0x258 */ u8 pad_258[0x10];
    /* 0x268 */ s32 sound; /* SOUND_PENDING: start at the next burst */
} GunsVars;

#endif
