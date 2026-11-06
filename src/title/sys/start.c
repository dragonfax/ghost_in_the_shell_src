/* start: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

/* hand-written entry (crt0): clears bss with `sltu $at`, sets $gp, jumps to main (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* crt0 entry: zeroes the bss words from D_8010D6D0 up to title_bss_end, sets $gp to D_8010D6D0 and jumps to title_main. C companion
   of hand-written asm (not compiled): $gp is set by hand and the jump is a tail jump (no frame, no return); C has no
   form for either. */
extern s32 D_8010D6D0[7];
extern s32 title_bss_end;
void start(void) {
    s32 *p;

    for (p = (s32 *)D_8010D6D0; p < (s32 *)&title_bss_end; p++) {
        *p = 0;
    }
    /* $gp = &D_8010D6D0 */
    title_main();
}
#else
INCLUDE_ASM("../src/title/asm", start);
#endif

void title_noop(void) {
}

INCLUDE_ASM("../asm/title/nonmatchings/main", func_800BC1CC);

#ifdef NON_MATCHING
/* Returns the data word at func_800BC1CC. C companion of hand-written asm (not compiled): the word's address is built in $at (lui/addiu), then lw into $v0. */
extern u32 func_800BC1CC;

u32 func_800BC1D0(void) {
    return func_800BC1CC;
}
#else
INCLUDE_ASM("../src/title/asm", func_800BC1D0);
#endif
