/* facing: one of s12's own original source files (scripts/objmap.py); part of src/s12/main.c's unit, included there. */

/* Call pchr_set_angle_range with first + base and the count of first..last. */
void pchr_set_angle_span(s32 first, s32 last, s32 unused, s32 base) {
    pchr_set_angle_range(first + base, last - first + 1, unused);
}


s32 get_angle_to_player(s32 *pos);
/* Returns 1 when one angle_approach step from `angle` toward the angle
 * get_angle_to_player gives for `pos` moves less than `max_step`. */
s32 is_facing_target(s32 *pos, s32 angle, s32 max_step) {
    s32 step;
    s32 cur;
    s32 target;
    s32 diff;

    step = ABS(max_step);
    cur = angle;
    target = get_angle_to_player(pos);
    cur &= 0xFFF;
    if (cur >= 0x800) {
        cur -= 0x1000;
    }
    diff = angle_approach(cur, target, step) - cur;
    diff &= 0xFFF;
    if (diff >= 0x800) {
        diff -= 0x1000;
    }
    return ABS(diff) < step;
}
