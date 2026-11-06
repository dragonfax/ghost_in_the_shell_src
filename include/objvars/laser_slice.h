/* ObjVars.laser_slice: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_LASER_SLICE_H
#define OBJVARS_LASER_SLICE_H

/* laser_slice_spawn (scripts/objkinds.py) */
typedef struct LaserSliceVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 table_index;
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ u16 beam_length;
} LaserSliceVars;

#endif
