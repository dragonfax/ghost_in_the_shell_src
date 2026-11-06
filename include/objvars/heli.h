/* ObjVars.heli: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_HELI_H
#define OBJVARS_HELI_H

/* s06 helicopter (s06_helicopter_update) */
typedef struct HeliVars {
    /* 0x248 */ u8 pad_248[2];
    /* 0x24A */ s16 flow_timer;  /* > 0: carried by the source's flow; -1 a step */
    /* 0x24C */ s16 unk_24C;     /* +8 a step */
    /* 0x24E */ u16 blink;       /* toggles; the first two rotors draw at 0 (s06_helicopter_draw) */
    /* 0x250 */ u8 pad_250[8];
    /* 0x258 */ s16 body_yaw;     /* the body's yaw (s06_helicopter_draw) */
    /* 0x25A */ s16 part1_yaw;     /* +8 a step */
    /* 0x25C */ s16 part2_yaw;     /* -8 a step */
    /* 0x25E */ s16 part3_yaw;     /* +0x200 a step */
    /* 0x260 */ s32 prev_yaw;    /* obj_lean_into_turn's slot */
    /* 0x264 */ u8 pad_264[8];
    /* 0x26C */ struct Object *source; /* its vars hold the Flow */
} HeliVars;

#endif
