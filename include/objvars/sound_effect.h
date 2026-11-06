/* ObjVars.sound_effect: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SOUND_EFFECT_H
#define OBJVARS_SOUND_EFFECT_H

/* sound_effect_spawn (scripts/objkinds.py) */
typedef struct SoundEffectVars {
    /* 0x248 */ s32 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s32 base_sound;
    /* 0x250 */ s32 current_sound;
    /* 0x254 */ s32 toggle;
} SoundEffectVars;

#endif
