/* ObjVars.rocket_boat_shell: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ROCKET_BOAT_SHELL_H
#define OBJVARS_ROCKET_BOAT_SHELL_H

/* rocket_boat_shell_spawn (scripts/objkinds.py) */
typedef struct RocketBoatShellVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 unk_24A;
    /* 0x24C */ s16 timer;
    /* 0x24E */ u16 unk_24E;
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ u8 pad_252[14];
    /* 0x260 */ s32 sound_handle;
} RocketBoatShellVars;

#endif
