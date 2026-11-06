/* mission_status: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

s32 get_ptr_entry_word2(s32 n) {
    n = NOT_NEGATIVE(n < 6 ? n : 5);
    return (s32)ptr_entry_table[n].entry->out;
}

s32 get_model_slot_base(void) {
    return model_slot_pchr(model_base_slot);
}

s32 fn_800FBAB0(void) {
    return d_8012D3B4;
}

/* Sets the three result words of each of the six engine loader steps to -1. */
void ptr_entry_clear_targets(void) {
    s32 *target;
    s32 i;

    for (i = 0; i < 6; i++) {
        if (ptr_entry_table[i].entry != NULL) {
            target = ptr_entry_table[i].entry->out;
            target[0] = -1;
            target[2] = -1;
            target[1] = -1;
        }
    }
}

void mission_start(void) {
    mission_active = 1;
    mission_elapsed = 0;
    mission_timer = 0;
    mission_limit = 0;
    mission_total = 0;
    mission_count = 0;
    mission_score = 0;
    stage_end = 0;
    stage_flags = 0;
}

void set_mission_active(s32 value) {
    mission_active = value;
}

s32 mission_status_active(void) {
    return mission_active;
}
