/* start: one of loader's own original source files (scripts/objmap.py); part of src/loader/main.c's unit, included there. */

/* hand-written entry (crt0): clears bss with `sltu $at`, sets $gp, jumps to main (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* crt0 entry: zeroes the bss words from loader_event_flag up to loader_bss_end, sets $gp to loader_event_flag and jumps to loader_run_event. C companion
   of hand-written asm (not compiled): $gp is set by hand and the jump is a tail jump (no frame, no return); C has no
   form for either. */
extern s32 loader_bss_end;
void start(void) {
    s32 *p;

    for (p = (s32 *)&loader_event_flag; p < (s32 *)&loader_bss_end; p++) {
        *p = 0;
    }
    /* $gp = &loader_event_flag */
    loader_run_event();
}
#else
INCLUDE_ASM("../src/loader/asm", start);
#endif

void func_800E5FC4(void) {
}
