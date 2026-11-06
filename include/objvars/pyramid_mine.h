/* ObjVars.pyramid_mine: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PYRAMID_MINE_H
#define OBJVARS_PYRAMID_MINE_H

/* pyramid_mine_spawn (scripts/objkinds.py) */
typedef struct PyramidMineVars {
    /* 0x248 */ s16 spin_yaw;
    /* 0x24A */ u16 zigzag_toggle;
    /* 0x24C */ s16 blend;
    /* 0x24E */ u16 wave_angle;
} PyramidMineVars;

#endif
