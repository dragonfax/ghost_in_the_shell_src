#ifndef COP0_H
#define COP0_H

/* System control coprocessor (COP0). */

/* Status register (cop0 $12) bits: the exception stack of interrupt-enable / kernel-user pairs. */
#define SR_IEC 0x1 /* current interrupt enable */
#define SR_KUC 0x2
#define SR_IEP 0x4 /* previous: set inside an exception handler entered with interrupts on */
#define SR_KUP 0x8

/* Reads the Status register (mfc0 and its load-delay nop: the assembler adds none). */
static inline u32 cop0_get_status(void) {
    u32 sr;
    __asm__ volatile("mfc0 %0, $12\n\tnop" : "=r"(sr));
    return sr;
}

/* True inside an interrupt handler: the exception moved IEc (on) to IEp. Thread code runs with IEp clear
 * (TCB status 0x40000404 becomes IEc on, IEp off at rfe; EnterCriticalSection clears both). */
#define in_interrupt() (cop0_get_status() & SR_IEP)

/* Interrupts off with the Status register saved in $at (IEc cleared through $v1), and back on from $at: the
 * loader's GTE blocks keep $at untouched between the two (loader_gte_scale). */
#define cop0_irq_off_at() __asm__ volatile(".set noat\n\tmfc0 $at, $12\n\taddiu $v1, $zero, -2\n\t" \
    "and $v1, $at, $v1\n\tmtc0 $v1, $12\n\t.set at" : : : "$3")
#define cop0_irq_restore_at() __asm__ volatile(".set noat\n\tmtc0 $at, $12\n\t.set at")

#endif
