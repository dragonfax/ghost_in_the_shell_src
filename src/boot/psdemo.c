#include "common.h"

extern void _boot(void);
extern char *psyq_strcpy(char *dst, const char *src) __asm__("strcpy");
extern s32 EnterCriticalSection(void);
extern char psdemo_name[]; /* "PSDEMO" */

/* Copies the "PSDEMO" name to the fixed address 0xA000DF00, enters a critical section, then runs _boot. */
void boot_psdemo(void) {
    psyq_strcpy((char *)0xA000DF00, psdemo_name);
    EnterCriticalSection();
    _boot();
}
