/* slot_list: one of the original source files (scripts/objmap.py); s03, s13. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

extern GridEntry *flagged_grid_cells[];
/* Same code as get_key_table (s01). */
GridEntry **slot_list_get(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 slot_list_count(void) {
    return grid_flagged_count;
}
