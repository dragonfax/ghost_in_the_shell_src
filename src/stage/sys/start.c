/* start: one of the original source files (scripts/objmap.py); s01, s02, s03, s04, s05, s07, s08, s09, s10, s11, s12, s13. */

#include "stage.h"

#ifdef NON_MATCHING
/* crt0 entry: zeroes the bss words from heap_top up to bss_end, sets $gp to vram_image_b and jumps to stage_main. C companion
   of hand-written asm (not compiled): $gp is set by hand and the jump is a tail jump (no frame, no return); C has no
   form for either. */
extern s32 bss_end;
void start(void) {
    s32 *p;

    for (p = (s32 *)&heap_top; p < (s32 *)&bss_end; p++) {
        *p = 0;
    }
    /* $gp = &vram_image_b */
    stage_main();
}
#else
INCLUDE_ASM("../src/stage/asm", start);
#endif
