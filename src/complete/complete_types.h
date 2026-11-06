#ifndef COMPLETE_TYPES_H
#define COMPLETE_TYPES_H

/* complete's types (main.c's code, data.c and bss.c include this; types only, so the data files can include
 * it without main.c's declarations of the objects they define). */

#include "common.h"

/* from disp_setup_320x240 */
typedef struct CompleteDispEnv {
    u8 pad_00[0x10];
    u8 isinter;
    u8 isrgb24;
    u8 pad_12[2];
} CompleteDispEnv;

/* from disp_setup_320x240 */
typedef struct CompleteDrawEnv {
    u8 pad_00[0x16];
    u8 dtd;
    u8 dfe;
    u8 isbg;
    u8 pad_19[0x5C - 0x19];
} CompleteDrawEnv;

/* from rect_set_fraction */
typedef struct CompleteRect {
    u8 unk_00[8];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} CompleteRect;

typedef struct Bytes8 {
    u8 b[8];
} Bytes8;

typedef struct MovieDispEnv {
    s16 disp_x;
    s16 disp_y;
    s16 disp_w;
    s16 disp_h;
    Bytes8 screen;
    u8 isinter;
    u8 isrgb24;
    u8 pad_12[0x66];
} MovieDispEnv;

/* A sound request (the boot exe's snd_alloc_channel reads it): kind's bits say which fields override the
 * defaults (2 volume, 4 pan, 0x10 note, 0x20 priority). */
typedef struct SndAllocBlock {
    s32 kind;
    s32 tone;     /* bank << 24 | program << 8 | tone */
    s32 handle;
    s32 volume;
    s32 rate;
    s32 rate_scale;
    s16 pan;
    s16 note;
    s16 fine;
    s16 priority;
} SndAllocBlock;

#endif
