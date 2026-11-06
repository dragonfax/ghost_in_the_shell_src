/* Sound IDs (FINDINGS "Sound effects"): bits 0-3 tone, 4-10 program, 11 a voice allocator flag, 12 the stage bank,
   13-14 voice group, 15 held (keeps its handle until sound_stop). A 32-bit ID is two sounds keyed on together.
   Made by scripts/sound_c.py: names heard by ear (labels/sounds.tsv) or read from the code that plays them
   (config/sound_names.tsv). */
#ifndef SOUND_H
#define SOUND_H

#define SND_VOICE_FLAG                       0x0800
#define SND_STAGE_BANK                       0x1000
#define SND_GROUP(n)                         ((n) << 13)
#define SND_HELD                             0x8000
#define SND_PAIR(a, b)                       ((u32)(a) << 16 | (b))

/* the resident bank (JOCHUOK.VAB), every stage */
#define SND_PLAYER_JUMP                      0x0000 /* JOCHUOK 0/0, 1.31 s; named from the code */
#define SND_PLAYER_LAND                      0x0001 /* JOCHUOK 0/1, 0.77 s; named from the code */
#define SND_PLAYER_MOVE_START                0x0002 /* JOCHUOK 0/2, 0.77 s; named from the code */
#define SND_PLAYER_HIT_LIGHT                 0x0003 /* JOCHUOK 0/3, 0.65 s; named from the code */
#define SND_PLAYER_HIT_HEAVY                 0x0004 /* JOCHUOK 0/4, 0.98 s; named from the code */
#define SND_SMG_FIRE                         0x0005 /* JOCHUOK 0/5, 1.54 s, loops; heard as "smg fire" */
#define SND_GRENADE_LAUNCH                   0x0006 /* JOCHUOK 0/6, 0.76 s; named from the code */
#define SND_ITEM_PICKUP                      0x0007 /* JOCHUOK 0/7, 1.29 s; named from the code */
#define SND_SMALL_SPLASH                     0x0009 /* JOCHUOK 0/9, 0.57 s; heard as "small splash" */
#define SND_SLOW_MECH_MOVE                   0x000B /* JOCHUOK 0/11, 1.76 s, loops; heard as "slow mech move" */
#define SND_FAST_MECH_MOVE                   0x000C /* JOCHUOK 0/12, 1.61 s, loops; heard as "fast mech move" */
#define SND_RICOCHET                         0x0010 /* JOCHUOK 1/0, 0.75 s; heard as "ricochet" */
#define SND_THREE_BEEPS                      0x0012 /* JOCHUOK 1/2, 0.4 s; heard as "three beeps" */
#define SND_LOCK_ON_BEEP                     0x0015 /* JOCHUOK 1/5, 0.39 s; named from the code */
#define SND_ROCKET_LAUNCH                    0x0016 /* JOCHUOK 1/6, 1.38 s; heard as "rocket launch" */
#define SND_LIGHT_MONITOR_HUM                0x0017 /* JOCHUOK 1/7, 1.51 s, loops; heard as "light monitor hum" */
#define SND_HEAVY_MONITOR_HUM                0x0018 /* JOCHUOK 1/8, 1.52 s, loops; heard as "heavy monitor hum" */
#define SND_HEAVY_WARBLE                     0x0019 /* JOCHUOK 1/9, 1.54 s, loops; heard as "heavy warble" */
#define SND_LIGHT_WARBLE                     0x001A /* JOCHUOK 1/10, 1.51 s, loops; heard as "light warble" */
#define SND_SMALL_EXPLOSION                  0x0020 /* JOCHUOK 2/0, 0.8 s; heard as "small explosion" */
#define SND_MEDIUM_EXPLOSION                 0x0021 /* JOCHUOK 2/1, 1.13 s; heard as "medium explosion" */
#define SND_LARGE_EXPLOSION                  0x0022 /* JOCHUOK 2/2, 1.69 s; heard as "large explosion" */
#define SND_LIGHT_GUNFIRE                    0x0023 /* JOCHUOK 2/3, 1.51 s, loops; heard as "light gunfire" */
#define SND_MEDIUM_GUNFIRE                   0x0024 /* JOCHUOK 2/4, 1.52 s, loops; heard as "medium gunfire" */
#define SND_HEAVY_GUNFIRE                    0x0025 /* JOCHUOK 2/5, 1.55 s, loops; heard as "heavy gunfire" */
#define SND_RICOCHET2                        0x0026 /* JOCHUOK 2/6, 0.75 s; heard as "ricochet2" */
#define SND_PROJECTILE_IMPACT                0x0027 /* JOCHUOK 2/7, 0.48 s; named from the code */
#define SND_ENEMY_FIRE                       0x0028 /* JOCHUOK 2/8, 1.05 s; named from the code */
#define SND_TWIN_SHOT_FIRE                   0x0029 /* JOCHUOK 2/9, 0.78 s; named from the code */
#define SND_ROCKET_ENGINE_LOOP               0x002A /* JOCHUOK 2/10, 1.98 s, loops; named from the code */
#define SND_PROJECTILE_FIRE_ALT              0x0030 /* JOCHUOK 3/0, 1.09 s; named from the code */
#define SND_PROJECTILE_FIRE                  0x0031 /* JOCHUOK 3/1, 0.79 s; named from the code */
#define SND_ROCKET_FIRE                      0x0032 /* JOCHUOK 3/2, 0.87 s; named from the code */
#define SND_WHISTLE                          0x0034 /* JOCHUOK 3/4, 0.82 s; heard as "whistle" */
#define SND_LASER_DRONE_FIRE                 0x0036 /* JOCHUOK 3/6, 1.51 s, loops; named from the code */
#define SND_LASER_IMPACT                     0x0039 /* JOCHUOK 3/9, 1.64 s, loops; named from the code */
#define SND_POWER_ON                         0x003A /* JOCHUOK 3/10, 1.15 s; heard as "power on" */
#define SND_SHOT_FIRE_ALT                    0x003D /* JOCHUOK 3/13, 0.63 s; named from the code */
#define SND_MENU_CONFIRM                     0x0041 /* JOCHUOK 4/1, 0.62 s; named from the code */
#define SND_PICKUP_DENIED                    0x0043 /* JOCHUOK 4/3, 0.2 s; named from the code */
#define SND_MENU_CURSOR_MOVE                 0x0044 /* JOCHUOK 4/4, 0.55 s; named from the code */
#define SND_BEEP                             0x0050 /* JOCHUOK 5/0, 0.33 s; heard as "beep" */
#define SND_LANDING_THUD_ALT                 0x0062 /* JOCHUOK 6/2, 1.05 s; named from the code */
#define SND_FOOTSTEP                         0x0072 /* JOCHUOK 7/2, 0.36 s; named from the code */
#define SND_GROUND_IMPACT                    0x0074 /* JOCHUOK 7/4, 0.27 s; named from the code */
#define SND_DOUBLE_BEEP                      0x0076 /* JOCHUOK 7/6, 0.17 s; heard as "double beep" */
#define SND_BULLET_IMPACT                    0x0077 /* JOCHUOK 7/7, 0.27 s; named from the code */
#define SND_BELL                             0x0080 /* JOCHUOK 8/0, 0.47 s; heard as "bell" */
#define SND_ITEM_PICKUP_ALT                  0x0081 /* JOCHUOK 8/1, 0.88 s; named from the code */
#define SND_MESSAGE_POPUP                    0x0082 /* JOCHUOK 8/2, 0.5 s; named from the code */
#define SND_UI_BOX_OPEN                      0x0083 /* JOCHUOK 8/3, 0.72 s; named from the code */
#define SND_MECH_MOVE_START                  0x0090 /* JOCHUOK 9/0, 1.16 s; named from the code */
#define SND_MECH_MOVE_A_LOOP                 0x0091 /* JOCHUOK 9/1, 1.63 s, loops; named from the code */
#define SND_MECH_MOVE_B_LOOP                 0x0092 /* JOCHUOK 9/2, 1.58 s, loops; named from the code */

#endif
