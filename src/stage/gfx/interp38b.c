/* interp38b: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void interp38b_clear(void) {
    interp38b_count = 0;
}

s32 interp38b_add(u8 *script) {
    InterpRec38 *rec;
    s32 index;

    if (interp38b_count >= 32) {
        return -1;
    }
    rec = &interp38b_table[interp38b_count];
    *(u8 **)rec->script = script;
    script += 0x10;
    *(u8 **)rec->part[0].unk_0C = script;
    index = interp38b_count;
    script += *(s16 *)script * 4 + 2;
    *(u8 **)rec->part[1].unk_0C = script;
    script += *(s16 *)script * 4 + 2;
    interp38b_count = index + 1;
    *(u8 **)rec->part[2].unk_0C = script;
    return index;
}

/* Sets entry i's state; state 2 resets its three parts and becomes 1. */
void interp38b_set_state(s32 i, s32 state) {
    if (i >= 0) {
        InterpRec38 *rec = &interp38b_table[i];
        if (state == 2) {
            state = 1;
            interp_reset(&rec->part[0]);
            interp_reset(&rec->part[1]);
            interp_reset(&rec->part[2]);
        }
        rec->state = state;
    }
}

/* Restarts every interp38b entry: state 1 and its three parts reset.
   The parts are addressed through interp38_parts (interp38_table + 4): interp38b_table
   follows interp38_table's 32 entries, so entry i is interp38_parts[32 + i]. */
void interp38b_restart_all(void) {
    s32 i;

    for (i = 0; i < interp38b_count; i++) {
        interp38b_table[i].state = 1;
        interp_reset(&interp38_parts[32 + i].part[0]);
        interp_reset(&interp38_parts[32 + i].part[1]);
        interp_reset(&interp38_parts[32 + i].part[2]);
    }
}

void interp38b_run_scripts(void) {
    s32 i;

    for (i = 0; i < interp38b_count; i++) {
        if (interp38b_table[i].state == 1) {
            script_runner_step(&interp38b_triples[i].part[0]);
            script_runner_step(&interp38b_triples[i].part[1]);
            script_runner_step(&interp38b_triples[i].part[2]);
        }
    }
}

/* Same code as interp38_run_all (s01). */
void interp38b_run_all(void) {
    s32 i;

    for (i = 0; i < interp38b_count; i++) {
        if (interp38b_table[i].state == 1) {
            interp38_run_span(&interp38b_table[i]);
        }
    }
}
