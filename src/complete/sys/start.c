/* start: one of complete's own original source files (scripts/objmap.py); part of src/complete/main.c's unit, included there. */

/* hand-written entry (crt0): clears bss with `sltu $at`, sets $gp, jumps to main (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* crt0 entry: zeroes the bss words from screen_buf_ptr up to complete_bss_end, sets $gp to screen_buf_ptr and jumps to complete_image_show. C companion
   of hand-written asm (not compiled): $gp is set by hand and the jump is a tail jump (no frame, no return); C has no
   form for either. */
extern s32 complete_bss_end;
void start(void) {
    s32 *p;

    for (p = (s32 *)&screen_buf_ptr; p < (s32 *)&complete_bss_end; p++) {
        *p = 0;
    }
    /* $gp = &screen_buf_ptr */
    complete_image_show();
}
#else
INCLUDE_ASM("../src/complete/asm", start);
#endif

void func_80100B80(void) {
}
