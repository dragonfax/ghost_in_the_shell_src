#ifndef MIPS_H
#define MIPS_H

/* CPU instruction idioms the original's code shape needs as asm (one name each; operand order is the original's:
 * cc1 assigns registers by operand order). */

/* A nop the original has where GCC puts none (a load delay, a scheduling slot). */
#define mips_nop() __asm__ volatile("nop")
/* The same with x in a register at the nop (the original: a load delay before x is used). */
#define mips_nop_use(x) __asm__ volatile("nop" : : "r"(x))

/* Starts a product (HI:LO = a * b) or a division (LO = a / b, HI = a % b); read later with mips_mfhi / mips_mflo. */
/* A tab after the mnemonic, as cc1 writes it: maspsx only recognizes "div\t" and adds the hazard nops before it
 * (with a space it passes the line through: cam_track_part_eval lost 2 nops). */
#define mips_mult(a, b) __asm__ volatile("mult\t%0,%1" : : "r"(a), "r"(b))
#define mips_div(a, b) __asm__ volatile("div\t$0,%0,%1" : : "r"(a), "r"(b))
#define mips_mfhi(x) __asm__ volatile("mfhi\t%0" : "=r"(x))
#define mips_mflo(x) __asm__ volatile("mflo\t%0" : "=r"(x))
/* Sets LO / HI: a value passed in LO or HI to a hand-written callee (its mflo / mfhi). */
#define mips_mtlo(x) __asm__ volatile("mtlo %0" : : "r"(x))
#define mips_mthi(x) __asm__ volatile("mthi %0" : : "r"(x))

/* rem = x % 10 through the temporary register tmp (a number); the quotient x / 10 stays in LO for mips_mflo. */
#define div10_rem(rem, x, tmp) __asm__ volatile( \
    "li $" #tmp ",10\n\tdiv $0,%1,$" #tmp "\n\tmfhi %0" : "=r"(rem) : "r"(x) : "$" #tmp)
#define div10_rem_mem(rem, x, tmp) __asm__ volatile( \
    "li $" #tmp ",10\n\tdiv $0,%1,$" #tmp "\n\tmfhi %0" : "=r"(rem) : "r"(x) : "$" #tmp, "memory")

/* q = x / 3 for x >= 0: the high word of x * 0x55555556 (clang has no "=h": plain C there). */
#if defined(PERMUTER) || defined(__clang__)
#define div3_hi(q, x) ((q) = (x) / 3)
#else
#define div3_hi(q, x) __asm__ volatile("mult %1,%2" : "=h"(q) : "d"(x), "d"(0x55555556) : "lo")
#endif

/* The return address of the current function (read before any call). */
#define get_ra(x) __asm__ volatile("move %0,$31" : "=r"(x))

/* Stops in the debugger after a fatal message (break code 1031). */
#define debug_break() __asm__ volatile("break 1031")

/* Saves sp at `top` and runs on the stack just below it, in the scratchpad (sp = top - 4, through $8); LEAVE_BELOW
 * goes back. stage.h has SCRATCH_STACK_ENTER/LEAVE, the form with sp = top. */
#define SCRATCH_STACK_ENTER_BELOW(top) \
    __asm__ volatile("addu $8, %0, $zero\n\tsw $sp, 0($8)\n\taddiu $8, $8, -4\n\taddu $sp, $8, $zero" : : "r"(top) : "$8")
#define SCRATCH_STACK_LEAVE_BELOW() __asm__ volatile("lw $sp, 4($sp)")

#endif
