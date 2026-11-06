/* part_extents: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

void obj_set_extents_from_part(Object *obj, s32 part, s32 part_arg) {
    u16 ext[3];
    s32 unused[2];
    u16 depth;
    s32 span;
    s32 y;
    s16 y_copy;
    s16 span_copy;

    model_part_extents_max(part, part_arg, ext);
    obj->unk_190 = part_arg;
    obj->width = ext[0];
    obj->height = ext[1];
    obj->unk_1E8[0] = depth = ext[2];
    y = (s16)obj->height;
    span = (s16)depth;
    y_copy = y;
    if (span < obj->width) {
        span = obj->width;
    }
    span_copy = span;
    obj->extents[0] = span_copy;
    obj->extents[1] = y_copy;
    obj->extents[2] = span_copy;
    obj->bound_radius = isqrt(length_sq(span, y, span));
}
