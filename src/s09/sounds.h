/* s09's sound IDs in its stage bank (BC09.VAB); made by scripts/sound_c.py. */
#ifndef STAGE_SOUNDS_H
#define STAGE_SOUNDS_H

#include "sound.h"

#define SND_BOSS_SPAWN_LOOP                  0x1100 /* BC09 16/0, 1.75 s, loops; named from the code */
#define SND_BOSS_SPAWN_LOOP_ALT              0x1101 /* BC09 16/1, 2.47 s, loops; named from the code */
#define SND_ENEMY_IDLE_LOOP                  0x1104 /* BC09 16/4, 2.44 s, loops; named from the code */
#define SND_ENEMY_IDLE_LOOP_ALT              0x1105 /* BC09 16/5, 3.07 s, loops; named from the code */
#define SND_ENEMY_SHUTDOWN                   0x1106 /* BC09 16/6, 2.52 s; named from the code */
#define SND_REACTOR_HUM_LOOP                 0x1109 /* BC09 16/9, 1.92 s, loops; named from the code */
#define SND_BOSS_ENGINE_LOOP                 0x110A /* BC09 16/10, 1.71 s, loops; named from the code */
#define SND_ELECTRIC_ARC_SPAWN               0x110B /* BC09 16/11, 0.72 s; named from the code */
#define SND_ENEMY_MOVE_LOOP                  0x110D /* BC09 16/13, 1.62 s, loops; named from the code */
#define SND_OBJECT_MOVE_LOOP                 0x110E /* BC09 16/14, 1.54 s, loops; named from the code */
#define SND_WHIRR                            0x1110 /* BC09 17/0, 1.51 s, loops; heard as "whirr" */
#define SND_BOSS_LASER_WHIRR_LOOP            0x1111 /* BC09 17/1, 1.51 s, loops; named from the code */
#define SND_BURST_IMPACT                     0x1112 /* BC09 17/2, 1.47 s; named from the code */
#define SND_COLLISION_IMPACT                 0x1284 /* BC09 40/4, no tone; named from the code */
#define SND_ELEVATOR_ENGAGE                  0x12E0 /* BC09 46/0, 0.65 s; named from the code */
#define SND_ELEVATOR_MOVE_LOOP               0x12E1 /* BC09 46/1, 1.77 s, loops; named from the code */
#define SND_ELEVATOR_MOVE_ALT_LOOP           0x12E2 /* BC09 46/2, 1.6 s, loops; named from the code */
#define SND_ELEVATOR_RIDE_LOOP               0x12E3 /* BC09 46/3, 2.12 s, loops; named from the code */
#define SND_SWITCH_TOGGLE                    0x12E4 /* BC09 46/4, 1.56 s; named from the code */
#define SND_QUAKE_RUMBLE                     0x12E5 /* BC09 46/5, 2.56 s; named from the code */
#define SND_QUAKE_RUMBLE_ALT                 0x12E6 /* BC09 46/6, 3.23 s; named from the code */
#define SND_FALL_LAUNCH                      0x13F1 /* BC09 63/1, 0.77 s; named from the code */
#define SND_LANDING_THUD                     0x13F2 /* BC09 63/2, 0.68 s; named from the code */
#define SND_SOUND_EMITTER_LOOP               0x1400 /* BC09 64/0, 1.52 s, loops; named from the code */
#define SND_MACHINE_GUN_FIRE                 0x1440 /* BC09 68/0, 1.55 s, loops; heard as "machine gun fire" */
#define SND_MUZZLE_FIRE                      0x1441 /* BC09 68/1, 0.8 s; named from the code */
#define SND_TRAIN_LOOP                       0x1442 /* BC09 68/2, 1.68 s, loops; named from the code */
#define SND_TRAIN_LOOP_ALT                   0x1443 /* BC09 68/3, 2.24 s, loops; named from the code */
#define SND_STAGE_ENEMY_FIRE                 0x1490 /* BC09 73/0, 0.77 s; named from the code */
#define SND_ROCKET_DRONE_LOOP                0x1492 /* BC09 73/2, 1.51 s, loops; named from the code */
#define SND_MOBILE_SUIT_IDLE_LOOP            0x1532 /* BC09 83/2, 1.85 s, loops; named from the code */
#define SND_S09_MUZZLE_FIRE                  0x1534 /* BC09 83/4, 1.36 s; named from the code */

#endif
