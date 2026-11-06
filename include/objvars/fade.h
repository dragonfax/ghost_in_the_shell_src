/* ObjVars.fade: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FADE_H
#define OBJVARS_FADE_H

/* s13 kinds that fade a level and flag an aobj at either end (func_800BCE60) */
typedef struct FadeVars {
    /* 0x248 */ u8 pad_248[4];
    /* 0x24C */ s16 aobj;      /* high byte: record (get_rec_id), low byte: index in it */
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s16 level;     /* 0..0x1000 */
    /* 0x252 */ s16 step;      /* added each step; cleared at either end */
} FadeVars;

#endif
