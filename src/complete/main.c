#include "common.h"
#include "complete_types.h"

void screen_restore_row(s32 arg0);

#include "core/complete.c"
#include "sys/start.c"

u32 D_80100000[21] RODATA = {
    0x80010000, 0x534F4942, 0x7265563A, 0x6E6F6973, 0x72724520, 0x0D2E726F,
    0x00000000, 0x80010000, 0x534F4942, 0x7265563A, 0x6E6F6973, 0x72724520,
    0x0D2E726F, 0x00000000, 0x80010000, 0x534F4942, 0x7265563A, 0x6E6F6973,
    0x72724520, 0x0D2E726F, 0x00000000,
};
