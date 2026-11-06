/* ObjVars.turn: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TURN_H
#define OBJVARS_TURN_H

/* kinds that turn toward their yaw plus an offset (s08 func_800BFB30) */
typedef struct TurnKindVars {
    /* 0x248 */ u8 pad_248[6];
    /* 0x24E */ s16 yaw;
    /* 0x250 */ u8 pad_250[0x28];
    /* 0x278 */ s16 yaw_offset;
    /* 0x27A */ s16 bearing; /* s08 func_800C0524: bearing to the target point */
} TurnKindVars;

#endif
