/* ObjVars.sound_loop: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SOUND_LOOP_H
#define OBJVARS_SOUND_LOOP_H

/* obj_spawn_sound_loop (scripts/objkinds.py) */
typedef struct SoundLoopVars {
    /* 0x248 */ s16 volume;
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ u16 toggle;
    /* 0x250 */ s32 target_obj;
    /* 0x254 */ s32 sound_handle;
} SoundLoopVars;

#endif
