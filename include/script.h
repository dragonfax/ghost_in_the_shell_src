#ifndef SCRIPT_H
#define SCRIPT_H

/* The stages' object scripts (docs/FINDINGS.md "Script system"): s16 streams in the stage data, one array per
 * stream, written with these macros by scripts/script_c.py. Jump operands are indices into the object's stream
 * table (enums in src/<stage>/scripts.h); a custom op is its index in the object's call table, followed by the
 * operands its handler reads. */

/* Behaviour streams (obj_link_script_run, cursor obj->script.pc). */
#define WAIT(frames)                -1, (frames)
#define LOOP(target)                -2, (target)         /* --counter > 0: jump */
#define JUMP(target)                -3, (target)
#define JUMP_RANDOM(chance, target) -4, (chance), (target) /* rand < chance: jump */
#define SET_COUNTER(n)              -5, (n)
#define SET_COUNTER_RANDOM(mod, base) -6, (mod), (base)  /* counter = rand % mod + base */
#define JUMP_IF_STATE(state, target) -7, (state), (target)
#define JUMP_UNLESS_STATE(state, target) -7, ~(state), (target)
#define SET_SPEED(speed)            -8, (speed)
#define NEXT_STATE(state)           -9, (state)
#define WANDER(on)                  -10, (on)
#define JUMP_IF_CAMERA_NEAR(range, target) -11, (range), (target)
#define TURN_RANDOM(step)           -12, (step)
#define TURN_RANDOM_SPAN(span)      -13, (span)

/* Animation streams (script_start / script_advance, cursor obj->type.pc): steps and the ops between them. */
#define STEP(frames, pose)          (frames), (pose)
#define SET_F8(v)                   -6, (v)
#define HOP_RANDOM(speed)           -5, (speed)
#define HOP(speed)                  -4, (speed)
#define FLY(speed)                  -3, (speed)
#define SOUND(index)                -2, (index)          /* obj->sounds[index] */
#define GOTO(target)                -1, (target)

#endif
