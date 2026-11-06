/* pchr_angle_span: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

void pchr_set_angle_span(s32 first, s32 last, s32 unused, s32 base) {
    pchr_set_angle_range(first + base, last - first + 1, unused);
}
