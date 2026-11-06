/* s07's shot tracing, used by src/stage/enemy/giant_robot_fx.c. */

s32 trace_hit_damage(s32 *from, s32 *to, s32 *hit, s32 size, s32 type, s32 damage) {
    s16 target;
    s32 result;

    result = trace_world(8, size, from, to, hit);
    if (result != 0) {
        result = 1;
    }
    set_collide_mode(1);
    if (trace_objects(from, hit, size, hit, &target) != 0) {
        result = 2;
        hit_target_masked(target, (u8)type, atan2(hit[2] - from[2], hit[0] - from[0]), damage);
    }
    set_collide_mode(0);
    return result;
}
