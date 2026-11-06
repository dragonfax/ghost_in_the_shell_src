/* vec_from_polar: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

void vec_from_polar(SVECTOR *out, s32 radius, s32 angle) {
    s32 idx = (angle & 0xFFF) * 4;
    s32 z, x;
    z = radius * ((s16 *)((u8 *)cos_table + idx))[0];
    z /= 0x1000;
    x = radius * ((s16 *)((u8 *)rcossin_tbl + idx))[0];
    x /= 0x1000;
    out->vx = x;
    out->vy = 0;
    out->vz = z;
}


void obj_pose_draw(Object *obj, s16 arg1) {
    /* Unused; the original frame reserves these 16 bytes. */
    s32 scratch[4];
    s32 pitch;
    u16 yaw;
    u16 roll;
    u8 index;
    u8 *block;

    block = obj->unk_A4;
    obj->unk_A4[1] = 1;
    pitch = obj->pitch;
    yaw = obj->yaw;
    roll = obj->roll;
    index = obj->index;
    *(s16 *)&obj->unk_A4[0x2C] = -pitch;
    *(u16 *)&obj->unk_A4[0x2E] = yaw;
    *(u16 *)&obj->unk_A4[0x30] = roll;
    obj->unk_A4[0] = index;
    obj_block_fill(obj, block);
    solid_setup_scratch(obj->solid_id, block, arg1, obj->unk_190);
    fn_800FB460(obj, block);
}



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
