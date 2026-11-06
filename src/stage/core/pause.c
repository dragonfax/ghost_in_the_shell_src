/* pause: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void toggle_paused(void) {
    pause_flag = pause_flag == 0;
}

s32 is_paused(void) {
    return pause_flag;
}

void counters_clear(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        counter_set(i, 0);
    }
}

s32 counter_get(u32 index) {
    s32 result;

    if (index < 8) {
        result = counter_table[index];
    } else {
        result = 0;
    }
    return result;
}

void counter_set(u32 index, s32 value) {
    if (index < 8) {
        counter_table[index] = value;
    }
}

/* Adds `amount` to entry `index` of the eight-word table counter_table. */
void counter_add(u32 index, s32 amount) {
    if (index < 8) {
        counter_table[index] += amount;
    }
}
