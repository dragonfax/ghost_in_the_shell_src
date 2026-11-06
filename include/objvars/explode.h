/* ObjVars.explode: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_EXPLODE_H
#define OBJVARS_EXPLODE_H

/* s12 exploding object (func_800C5A20, set up by sound_obj_spawn) */
typedef struct ExplodeVars {
    /* 0x248 */ struct Object *source; /* its unk_256 is cleared on the blast */
    /* 0x24C */ s32 spawn_index; /* object spawned with the burst (fx_burst_spawn), < 0 none */
    /* 0x250 */ s32 state;
    /* 0x254 */ s32 timer;
} ExplodeVars;

#endif
