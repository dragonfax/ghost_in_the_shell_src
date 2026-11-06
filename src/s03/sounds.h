/* s03's sound IDs in its stage bank (BC03.VAB); made by scripts/sound_c.py. */
#ifndef STAGE_SOUNDS_H
#define STAGE_SOUNDS_H

#include "sound.h"

#define SND_ENEMY_DEATH                      0x1046 /* BC03 4/6, 1.8 s; named from the code */
#define SND_MUZZLE_FIRE                      0x1047 /* BC03 4/7, 2.11 s; named from the code */
#define SND_ENEMY_BEEPER_LOOP                0x1048 /* BC03 4/8, 1.91 s, loops; named from the code */
#define SND_EXPANDING_BLAST_LOOP             0x104A /* BC03 4/10, 1.81 s, loops; named from the code */
#define SND_S03_ENEMY_FIRE                   0x104F /* BC03 4/15, 0.69 s; named from the code */
#define SND_ENEMY_ALARM_LOOP                 0x1053 /* BC03 5/3, 1.93 s, loops; named from the code */
#define SND_BOMB_EXPLOSION                   0x1221 /* BC03 34/1, 3.14 s; named from the code */
#define SND_DOOR_MOVE_LOOP                   0x1223 /* BC03 34/3, 1.85 s, loops; named from the code */
#define SND_TIME_BOMB_EXPLOSION              0x1224 /* BC03 34/4, 0.69 s; named from the code */
#define SND_TIME_BOMB_EXPLOSION_ALT          0x1225 /* BC03 34/5, 1.23 s; named from the code */
#define SND_COLLISION_IMPACT                 0x1284 /* BC03 40/4, no tone; named from the code */
#define SND_ENEMY_BURST_FIRE                 0x1420 /* BC03 66/0, 1.03 s; named from the code */
#define SND_HELICOPTER_ROTOR_LOOP            0x1510 /* BC03 81/0, 1.63 s, loops; named from the code */
#define SND_SHOT_FIRE                        0x1580 /* BC03 88/0, 0.52 s; named from the code */

#endif
