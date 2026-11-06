#include "common.h"
#include "startup_types.h"

extern s32 startup_frame_count;
extern s32 D_800EE1B0;
extern s32 (*slot_read_pad)(s32 mode);
/* Frame task (registered by startup_frame_task_start): counts the frame in startup_frame_count, then ORs bit 0x800 of
 * the slot_read_pad service's result (called with 1) into the flags in D_800EE1B0. */
#include "core/startup_main.c"
#include "sys/sys.c"
#include "gfx/fade.c"
#include "sys/start.c"

extern s32 D_800EE1A8;

