/* grid_areas: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

extern GridEntry *flagged_grid_cells[];
/* Same code as get_key_table (s01). */
GridEntry **get_grid_areas(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 grid_flagged_count_read(void) {
    return grid_flagged_count;
}
