/* bazooka_rocket: one of s03's own original source files (scripts/objmap.py); part of src/s03/main.c's unit, included there. */

void bazooka_rocket_update(Object *obj, ObjHandler *handler) {
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s16 target;

    if ((get_pause_flag() == 0) && (obj->vars.bazooka_rocket.done == 0)) {
        from[0] = obj->x >> 12;
        from[1] = obj->y >> 12;
        from[2] = obj->z >> 12;
        to[0] = (obj->x + obj->vx) >> 12;
        to[1] = (obj->y + obj->vy) >> 12;
        to[2] = (obj->z + obj->vz) >> 12;
        if (cam_range_check(from[0], from[1], from[2]) == 0) {
            obj->vars.bazooka_rocket.done = 1;
        } else if (trace_world(8, 0x10, from, to, hit) != 0) {
            obj->vars.bazooka_rocket.done = 1;
            timed_effect_spawn(hit);
        } else {
            set_collide_mode(1);
            if (trace_objects(from, to, 0x10, hit, &target) != 0) {
                hit_target_masked(target, 1, (s16)atan2(hit[2] - from[2], hit[0] - from[0]), 0xA);
                timed_effect_spawn(hit);
                obj->vars.bazooka_rocket.done = 1;
            }
            set_collide_mode(0);
            obj->z += obj->vz;
            obj->x += obj->vx;
            obj->y += obj->vy;
        }
        if (obj->vars.bazooka_rocket.done != 0) {
            obj_free(obj);
        }
    } else {
        obj_free(obj);
    }
}

void bazooka_rocket_update(Object *obj, ObjHandler *handler);
void bazooka_rocket_spawn(s32 *pos, u16 *rot) {
    Object *obj;
    s32 unused[6];
    s32 t, a, b, c;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = bazooka_rocket_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = spark_spawn_at_obj;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_set_flags(obj, 0x80);
        obj_hit_clear(obj->index);
        obj->unk_17A = 0;
        obj->speed = 0x46;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        t = get_model_slot_base();
        a = obj->yaw;
        b = obj->pitch;
        c = obj->speed;
        obj->vars.bazooka_rocket.unk_248 = t + 9;
        obj->vars.bazooka_rocket.done = 0;
        angles_to_vector(a, b, c, &obj->vx, &obj->vy, &obj->vz);
    }
}
