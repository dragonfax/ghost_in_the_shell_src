/* start: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

/* hand-written entry (crt0): clears bss with `sltu $at`, sets $gp, jumps to main */
/* crt0 entry: zeroes the bss words from D_8010D6D0 up to title_bss_end, sets $gp to D_8010D6D0 and jumps to title_main. The original is hand-written asm: $gp is set by hand and the jump is a tail jump (no frame, no return); C has no
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

void title_noop(void) {
}

/* Returns the data word at func_800BC1CC. The original is hand-written asm: the word's address is built in $at (lui/addiu), then lw into $v0. */
extern u32 func_800BC1CC;

u32 func_800BC1D0(void) {
    return func_800BC1CC;
}
