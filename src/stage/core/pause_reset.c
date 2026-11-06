/* pause_reset: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void pause_reset(void) {
    pause_flag = 0;
}

void counters_reset(void) {
    counters_clear();
}
