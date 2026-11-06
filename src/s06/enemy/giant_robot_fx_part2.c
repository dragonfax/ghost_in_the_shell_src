/* s06's shot tracing, used by src/stage/enemy/giant_robot_fx.c. */

s32 shot_hit_trace(s32 *from, s32 *to_unused, HitPos16 *to, s32 flags, s32 type, s32 damage) {
    HitPos16 world_hit;
    s16 target;
    s32 result;

    result = trace_world(8, flags, from, to_unused, &world_hit);
    if (result != 0) {
        result = 1;
    }
    set_collide_mode(1);
    if (trace_objects(from, to_unused, flags, to, &target) != 0) {
        result = 2;
        if (damage > 0) {
            hit_target_masked(target, (u8)type, atan2(to->z - from[2], to->x - from[0]), damage);
        }
    }
    set_collide_mode(0);
    if (result == 1) {
        *to = world_hit;
    }
    return result;
}
