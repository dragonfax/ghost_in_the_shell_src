/* s13's sound IDs in its stage bank (TRNG.VAB); made by scripts/sound_c.py. */
#ifndef STAGE_SOUNDS_H
#define STAGE_SOUNDS_H

#include "sound.h"

#define SND_ENEMY_DEATH_EXPLOSION            0x1000 /* TRNG 0/0, 1.95 s; named from the code */
#define SND_ENEMY_AIM_START                  0x1001 /* TRNG 0/1, 1.81 s; named from the code */
#define SND_ENEMY_ALERT                      0x1002 /* TRNG 0/2, 1.32 s; named from the code */
#define SND_MISSION_CLEAR_JINGLE             0x1003 /* TRNG 0/3, 2.09 s; named from the code */
#define SND_MISSION_START_JINGLE             0x1004 /* TRNG 0/4, 1.99 s; named from the code */
#define SND_OBJECT_STATE_CHANGE              0x1005 /* TRNG 0/5, 0.68 s; named from the code */
#define SND_COLLISION_IMPACT                 0x1284 /* TRNG 40/4, no tone; named from the code */

#endif
