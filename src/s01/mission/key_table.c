/* key_table: one of s01's own original source files (scripts/objmap.py); part of src/s01/main.c's unit, included there. */

extern GridEntry *flagged_grid_cells[];

GridEntry **get_key_table(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 get_key_count(void) {
    return grid_flagged_count;
}


void func_800BF598(void) {
    hit_ext_flag_set(1);
    set_data_base((s32)&data_base_area);
}
