/* ObjVars.beam_segment: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BEAM_SEGMENT_H
#define OBJVARS_BEAM_SEGMENT_H

/* beam_segment_spawn (scripts/objkinds.py) */
typedef struct BeamSegmentVars {
    /* 0x248 */ u8 pad_248[8];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 pos_x;
    /* 0x25C */ s32 pos_y;
    /* 0x260 */ s32 pos_z;
    /* 0x264 */ u8 pad_264[4];
    /* 0x268 */ u8 unk_268;
} BeamSegmentVars;

#endif
