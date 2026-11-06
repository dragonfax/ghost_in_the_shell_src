/* ObjVars.arc: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ARC_H
#define OBJVARS_ARC_H

/* s05 arcing projectile (projectile_arc_update) */
typedef struct ArcVars {
    /* 0x248 */ s32 done;         /* freed at the end of the step */
    /* 0x24C */ s16 life;
    /* 0x24E */ u16 turn_speed;
    /* 0x250 */ u16 smoke_time;   /* frames left dropping smoke */
    /* 0x252 */ u16 smoke_toggle; /* smoke every other frame */
} ArcVars;

#endif
