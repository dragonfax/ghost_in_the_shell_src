/* lock_mode: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void lock_frame_base_clear(void) {
    lock_frame_base = 0;
}

void lock_frame_base_set(s32 value) {
    lock_frame_base = value;
}

void lock_reset(void) {
    u8 *p;
    s32 i;

    lock_cooldown_timer = 0;
    i = 0x7F;
    p = d_80131E1B;
    do {
        *p-- = 0;
    } while (--i >= 0);
    for (i = 0; i < 6; i++) {
        lock_slots[i].id = -1;
        lock_slots[i].flag_index = 0;
    }
    lock_target_count = 0;
    lock_mode = 0;
}

s32 lock_get_mode(void) {
    return lock_mode;
}

void lock_set_mode(s32 value) {
    s32 i;
    Slot14 *slot;

    if (value != lock_mode) {
        lock_mode = value;
        i = 0;
        if (value != 0) {
            lock_cooldown_timer = 0;
            return;
        }
        {
            s32 none = -1;

            slot = lock_slots;
            do {
                if (slot->id >= 0) {
                    slot->id = none;
                    lock_flag_counts[lock_slots[i].flag_index] = 0;
                }
                slot++;
                i++;
            } while (i < 6);
        }
        lock_target_count = 0;
    }
}

s32 lock_count(void) {
    return lock_target_count;
}
