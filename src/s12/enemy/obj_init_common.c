/* obj_init_common: one of s12's own original source files (scripts/objmap.py); part of src/s12/main.c's unit, included there. */

void obj_init_common(Object *obj, s32 flags) {
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, -1);
    obj->flags = flags;
    if (flags & 0x4) {
        obj->unk_17A = 1;
    }
    obj->accel_y = 0x1000;
    obj_set_flags(obj, flags);
    obj->unk_1E8[2] = 0;
    obj->unk_1E8[3] = 0;
    obj->unk_1E8[1] = 0;
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}
