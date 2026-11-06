/* s12's shot tracing, used by src/stage/enemy/giant_robot_fx.c. */

/* Clips segment a->b against the near plane y = -0x400. If exactly one end
 * is behind it, writes the crossing point and returns 1; otherwise copies b
 * and returns 1 only when both ends are in front. */
s32 sweep_clip_y(s32 flags, s32 a1, Vec3 *a, Vec4 *b, Vec4 *out) {
    s32 ay = a->y;
    s32 by = b->v[1];
    s32 t;
    s32 inv;
    s32 ret;

    if ((!(ay < -0x3FF) && by < -0x3FF) || (!(by < -0x3FF) && ay < -0x3FF)) {
        t = ((-0x400 - ay) << 12) / (by - ay);
        inv = 0x1000 - t;
        out->v[0] = (b->v[0] * t + a->x * inv) / 0x1000;
        out->v[1] = (b->v[1] * t + a->y * inv) / 0x1000;
        out->v[2] = (b->v[2] * t + a->z * inv) / 0x1000;
        ret = 1;
    } else {
        if (ay < -0x3FF || by < -0x3FF) {
            ret = 0;
        } else {
            ret = 1;
        }
        *out = *b;
    }
    return ret;
}

s32 sweep_clip_y(s32 flags, s32 a1, Vec3 *a, Vec4 *b, Vec4 *out);
s32 sweep_hit_test(Vec3 *from, Vec4 *start, Vec4 *dest, s32 flags, s32 type, s32 power) {
    Vec4 path;
    s16 target;
    s32 result;

    path = *start;
    result = sweep_clip_y(8, flags, from, start, &path);
    if (result != 0) {
        result = 1;
    }
    set_collide_mode(1);
    if (trace_objects(from, &path, flags, dest, &target) != 0) {
        result = 2;
        if (power > 0) {
            hit_target_masked(target, (u8) type, atan2(dest->v[2] - from->z, dest->v[0] - from->x), (s16) power);
        }
    }
    set_collide_mode(0);
    if (result == 1) {
        *dest = path;
    }
    return result;
}

s32 trace_hit_apply(Vec3 *from, void *hit, Vec3 *to, s32 flags, s32 type, s32 damage) {
    s32 pad[4];
    s16 target;
    s32 result;

    result = 0;
    set_collide_mode(1);
    if (trace_objects(from, hit, flags, to, &target) != 0) {
        result = 2;
        if (damage > 0) {
            hit_target_masked(target, (u8)type, atan2(to->z - from->z, to->x - from->x), damage);
        }
    }
    set_collide_mode(0);
    return result;
}
