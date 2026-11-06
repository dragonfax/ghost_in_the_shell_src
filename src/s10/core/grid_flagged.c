/* grid_flagged: one of s10's own original source files (scripts/objmap.py); part of src/s10/main.c's unit, included there. */

extern GridEntry *flagged_grid_cells[];
/* Same code as get_key_table (s01). */
GridEntry **get_flagged_cells(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 get_grid_flagged_count(void) {
    return grid_flagged_count;
}
