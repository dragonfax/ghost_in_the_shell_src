/* ObjVars.burst: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BURST_H
#define OBJVARS_BURST_H

/* s09 part spawned by obj_spawn_part; func_800C7988 bursts it at two points */
typedef struct BurstVars {
    /* 0x248 */ s16 kind;
    /* 0x24A */ s16 timer;       /* death frames: even frames burst at first_*, then at second_*; freed at 16 */
    /* 0x24C */ s16 second_pos[3];
    /* 0x252 */ s16 second_yaw;
    /* 0x254 */ s16 second_pitch;
    /* 0x256 */ s16 first_pos[3];
    /* 0x25C */ s16 first_yaw;
    /* 0x25E */ s16 first_pitch;
    /* 0x260 */ struct Object *child;
} BurstVars;

#endif
