/* start: one of startup's own original source files (scripts/objmap.py); part of src/startup/main.c's unit, included there. */

/* hand-written entry (crt0): clears bss with `sltu $at`, sets $gp, jumps to main (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* crt0 entry: zeroes the bss words from startup_frame_count up to boot_bss_end, sets $gp to startup_frame_count and jumps to
   startup_main. C companion of hand-written asm (not compiled): $gp is set by hand and the jump is a tail
   jump (no frame, no return); C has no form for either. */
extern s32 boot_bss_end;
void start(void) {
    s32 *p;

    for (p = &startup_frame_count; p < &boot_bss_end; p++) {
        *p = 0;
    }
    /* $gp = &startup_frame_count */
    startup_main();
}
#else
INCLUDE_ASM("../src/startup/asm", start);
#endif

void startup_noop(void) {
}

/* Hand-written: syscall 0 with a hand-made frame (`addi $sp`); not C. */
#ifdef NON_MATCHING
/* BIOS syscall 0 with argument 0x80000000 returns a function pointer (or 0); calls it if set. C companion of
   hand-written asm (not compiled): the asm does a dummy `lb $at, 0($zero)`, keeps $ra in a hand-made 4-byte
   frame (addi, not addiu) and issues the syscall instruction, which C has no form for. */
extern void *syscall_0(u32 arg);
void func_800E92B0(void) {
    void (*fn)(void) = syscall_0(0x80000000);

    if (fn != 0) {
        fn();
    }
}
#else
INCLUDE_ASM("../src/startup/asm", func_800E92B0);
#endif
