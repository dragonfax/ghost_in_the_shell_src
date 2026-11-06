/* s01's own part of src/stage/enemy/giant_robot_fx.c, included there at this place (scripts/objtree.py). */

s32 trace_shot_segment(VECTOR *from, VECTOR *to, VECTOR *hit, s32 flags, s32 type, s32 damage) {
    VECTOR trace;
    s16 target;
    s32 result;

    result = trace_world(8, flags, from, to, &trace);
    if (result != 0) {
        result = 1;
    }
    set_collide_mode(1);
    if (trace_objects(from, &trace, flags, hit, &target)) {
        result = 2;
        if (damage > 0) {
            hit_target_masked(target, (u8)type, atan2(hit->vz - from->vz, hit->vx - from->vx), damage);
        }
    }
    set_collide_mode(0);
    if (result == 1) {
        *hit = trace;
    }
    return result;
}
