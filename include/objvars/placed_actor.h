/* ObjVars.placed_actor: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PLACED_ACTOR_H
#define OBJVARS_PLACED_ACTOR_H

/* placed_actor_spawn (scripts/objkinds.py) */
typedef struct PlacedActorVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ s16 flash;
} PlacedActorVars;

#endif
