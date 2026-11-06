/* ObjVars.beam: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BEAM_H
#define OBJVARS_BEAM_H

/* s02/s10 beam segment (beam_segment_update, spawned by beam_segment_spawn) */
typedef struct BeamVars {
    /* 0x248 */ s32 active;
    /* 0x24C */ s32 sound;
    /* 0x250 */ s16 *steps;      /* {health, _, _, _, speed, ...} 8 bytes each */
    /* 0x254 */ struct Object *owner;
    /* 0x258 */ s32 origin[3];
    /* 0x264 */ u8 pad_264[4];
    /* 0x268 */ u16 rot[3];
} BeamVars;

#endif
