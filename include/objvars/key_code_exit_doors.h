/* ObjVars.key_code_exit_doors: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_KEY_CODE_EXIT_DOORS_H
#define OBJVARS_KEY_CODE_EXIT_DOORS_H

/* key_code_exit_doors_spawn (scripts/objkinds.py) */
typedef struct KeyCodeExitDoorsVars {
    /* 0x248 */ s16 sound_zone_index;
    /* 0x24A */ u16 sound_channel;
} KeyCodeExitDoorsVars;

#endif
