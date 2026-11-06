/* complete data 0x801E1B9C-0x801E2000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "complete_types.h"

extern u8 D_801E1BC4[];
extern u8 sound_last_request[];
extern u8 sound_tone_volume[];
extern SndAllocBlock sound_request;
extern s32 screen_buf_ptr;
extern s32 screen_wipe_row_table[272];

SndAllocBlock sound_request = {0x117, 0x805, 0, 0x64, 0, 10, 0x3F, 0x3C, 0, 2};

s32 screen_buf_ptr = 0;

s32 screen_wipe_row_table[272] = {0};

