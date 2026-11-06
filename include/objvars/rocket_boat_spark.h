/* ObjVars.rocket_boat_spark: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ROCKET_BOAT_SPARK_H
#define OBJVARS_ROCKET_BOAT_SPARK_H

/* rocket_boat_spark_spawn (scripts/objkinds.py) */
typedef struct RocketBoatSparkVars {
    /* 0x248 */ s16 frame_base;
    /* 0x24A */ u16 frame_count;
} RocketBoatSparkVars;

#endif
