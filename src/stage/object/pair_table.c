/* pair_table: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void pair_table_init(void) {
    grid_block = 0;
    grid_entry_total = 0;
    grid_entries = 0;
    grid_active_flag = 1;
    grid_camera_reset();
    hook_table_clear();
}
