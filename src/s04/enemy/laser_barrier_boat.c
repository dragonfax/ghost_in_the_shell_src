/* laser_barrier_boat: one of s04's own original source files (scripts/objmap.py); part of src/s04/main.c's unit, included there. */

void fly_pair_update(Object *obj) {
    FlyPairVars *v = (FlyPairVars *)&obj->vars;
    s32 dx;
    s32 dz;
    s32 ax;
    s32 ay;
    s32 az;
    s32 bx;
    s32 bz;
    u16 yaw;

    dx = 0;
    dz = 0;
    az = 0;
    ax = 0;
    bz = 0;
    bx = 0;
    ay = 0;

    if (v->off_a > 0x100) {
        v->off_a -= 0xC;
    }
    if (v->off_a < 0x100) {
        v->off_a += 0xC;
    }
    if (v->off_b >= -0xFF) {
        v->off_b -= 0xC;
    }
    if (v->off_b < -0x100) {
        v->off_b += 0xC;
    }
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    ax = v->off_a;
    bx = v->off_b;
    rotate_xz_twice(obj->yaw, obj->pitch, &ax, &ay, &az);
    rotate_xz_twice(obj->yaw, obj->pitch, &bx, &ay, &bz);
    if (v->hold_a == 0) {
        yaw = obj->yaw;
        v->part_a->yaw = yaw;
        v->part_a->x = (ax << 12) + obj->x;
        v->part_a->z = (az << 12) + obj->z;
    }
    if (v->hold_b == 0) {
        yaw = obj->yaw;
        v->part_b->yaw = yaw;
        v->part_b->x = (bx << 12) + obj->x;
        v->part_b->z = (bz << 12) + obj->z;
    }
    if (v->timer > 0) {
        v->timer -= 0x20;
    }
}

void obj_trace_hit(Object *obj);
void moving_pyramid_mine_phase0(Object *obj) {
    s32 dx1;
    s32 dy;
    s32 dz1;
    s32 dx2;
    s32 dz2;
    MinePairVars *v;
    Placement *placement;

    v = (MinePairVars *) &obj->vars;
    dz1 = 0;
    dx1 = 0;
    dz2 = 0;
    dx2 = 0;
    dy = 0;
    placement = obj->placement;
    if (v->spawned == 0) {
        sound_attach(sound_start(SND_COMPUTER_GARBLE | SND_GROUP(1), 0x40, 0, 0), &v->partner_a->x, NULL);
        v->spawned = 1;
    }
    if (v->partner_a_offset < placement->range) {
        v->partner_a_offset += 0xC;
    }
    if (-placement->range < v->partner_b_offset) {
        v->partner_b_offset -= 0xC;
    }
    obj->vz = 0;
    dx1 = v->partner_a_offset;
    dx2 = v->partner_b_offset;
    rotate_xz_twice(obj->yaw, obj->pitch, &dx1, &dy, &dz1);
    rotate_xz_twice(obj->yaw, obj->pitch, &dx2, &dy, &dz2);
    if (v->unk_24A == 0) {
        u16 yaw = obj->yaw;

        v->partner_a->yaw = yaw;
        v->partner_a->x = (dx1 << 12) + obj->x;
        v->partner_a->z = (dz1 << 12) + obj->z;
    }
    if (v->unk_24C == 0) {
        u16 yaw = obj->yaw;

        v->partner_b->yaw = yaw;
        v->partner_b->x = (dx2 << 12) + obj->x;
        v->partner_b->z = (dz2 << 12) + obj->z;
    }
    v->unk_24E += 0x20;
    if ((s16) v->unk_24E >= 0x1001) {
        v->unk_24E = 0x1000;
    }
    obj_trace_hit(obj);
}

void laser_barrier_boat_update(Object *obj, ObjHandler *handler) {
    s16 state;

    obj->vz = 0;
    obj->vx = 0;
    if (*(s16 *)&obj->vars.laser_barrier_boat.state == 1) {
        obj_free((Object *)obj->vars.laser_barrier_boat.left_barrier);
        *(s16 *)&obj->vars.laser_barrier_boat.state = 2;
    }
    if (*(s16 *)&obj->vars.snd.sound == 1) {
        obj_free(*(Object **)&obj->vars.enemy.unk_25C);
        *(s16 *)&obj->vars.snd.sound = 2;
    }
    state = *(s16 *)&obj->vars.laser_barrier_boat.state;
    if (state == 2 && *(s16 *)&obj->vars.snd.sound == state) {
        obj_free(obj);
    }
    obj_script_step(obj, handler);
}

void laser_barrier_boat_update(Object *obj, ObjHandler *handler);
void laser_barrier_boat_draw(Object *obj, ObjHandler *handler);
Object *laser_barrier_boat_spawn(Object *src, s32 mode);
extern u8 laser_barrier_boat_asset[];
extern ScriptCallEntry D_80119074[];
extern StateEntry D_8011909C[];
extern s16 laser_barrier_boat_script[];
extern s16 *laser_barrier_boat_data[];
extern s16 *laser_barrier_boat_type_data[];
extern s16 *D_80119070;
/* Spawns a laser barrier boat from a placement; returns 1 on success, 0 if no slots. */
s32 laser_barrier_boat_spawn_placed(Placement *place) {
    Object *obj;
    s32 left_barrier;
    s32 right_barrier;
    u8 kind;
    s16 *script_pc;
    s16 **script_data;

    if (get_obj_free_count() >= 3) {
        obj = obj_new();
        if (obj != NULL) {
            list_insert_after((Node *) get_obj_list_actors(), &obj->node);
            script_pc = laser_barrier_boat_script;
            script_data = laser_barrier_boat_data;
            obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) obj_phase0_default;
            obj->handlers[1].fn = laser_barrier_boat_update;
            obj->handlers[0].unk_11 = 0;
            obj->handlers[0].state = 0;
            obj->handlers[1].unk_11 = 0;
            obj->handlers[1].state = 0;
            obj->handlers[2].fn = NULL;
            obj->handlers[2].unk_11 = 0;
            obj->handlers[2].state = 0;
            obj->handlers[3].fn = laser_barrier_boat_draw;
            obj->handlers[3].unk_11 = 0;
            obj->handlers[3].state = 0;
            obj->callback = 0;
            kind = place->unk_00[5];
            obj->asset = laser_barrier_boat_asset;
            obj->hit_cooldown_max = 0x30;
            obj->unk_1C6 = -0xC0;
            obj->call_table = D_80119074;
            obj->state_table = D_8011909C;
            obj->kind = kind;
            script_start((Script *) obj, script_pc, (s32) script_data);
            obj->script.data = laser_barrier_boat_type_data;
            obj->script.unk_0A = 0;
            obj->script.pc = D_80119070;
            obj_init_from_place(obj, place, 0x100);
            obj->speed = 0;
            obj_set_part_bounds(obj, 0, 0x1000);
            obj->unk_17A = 0;
            obj->x += 0x100000;
            left_barrier = (s32) laser_barrier_boat_spawn(obj, 1);
            obj->vars.laser_barrier_boat.left_barrier = left_barrier;
            if (left_barrier != 0) {
                obj->x += 0xFFE00000;
                right_barrier = (s32) laser_barrier_boat_spawn(obj, 2);
                obj->vars.laser_barrier_boat.right_barrier = right_barrier;
                if (right_barrier != 0) {
                    obj->vars.laser_barrier_boat.unused_250 = 0x100;
                    obj->vars.laser_barrier_boat.unused_254 = -0x100;
                    obj->vars.laser_barrier_boat.unused_248 = 0;
                    obj->vars.h.unk_24E = 0;
                    obj->vars.laser_barrier_boat.state = 0;
                    obj->vars.h.unk_24C = 0;
                    obj->x += 0x100000;
                    rec_reset((PartSlot *) &obj->vars.laser_barrier_boat.unk_260);
                    obj->vars.laser_barrier_boat.unused_268 = 0;
                    return 1;
                }
            }
            return 0;
        }
    }
    return 0;
}

void laser_barrier_boat_phase2(Object *obj, ObjHandler *handler);
s32 laser_barrier_boat_on_destroy(Object *obj);
void obj_init_from_src(Object *src, Object *obj, s32 flags);
extern u8 laser_barrier_boat_asset[];
extern ScriptCallEntry D_80119074[];
extern StateEntry D_8011909C[];
extern s16 laser_barrier_boat_script[];
extern s16 *laser_barrier_boat_data[];
extern s16 *laser_barrier_boat_type_data[];
extern s16 *D_80119070;
Object *laser_barrier_boat_spawn(Object *src, s32 mode) {
    Object *obj;
    u16 src_17E;

    obj = obj_new();
    if (obj == NULL) {
        return NULL;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[2].fn = laser_barrier_boat_phase2;
    obj->handlers[3].fn = obj_draw_spark;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) laser_barrier_boat_on_destroy;
    src_17E = src->kind;
    obj->asset = &laser_barrier_boat_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = D_80119074;
    obj->state_table = D_8011909C;
    obj->kind = src_17E;
    script_start((Script *) obj, laser_barrier_boat_script, (s32) laser_barrier_boat_data);
    obj->script.data = &laser_barrier_boat_type_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_80119070;
    obj_init_from_src(src, obj, 0x174);
    obj->speed = 0;
    obj_set_part_bounds(obj, 0, 0x1000);
    obj->vars.laser_barrier_boat.unk_24C = (s32) src;
    obj->vars.enemy.mode = mode;
    return obj;
}

void laser_barrier_boat_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

/* Resets the object's two counters (0x208, 0x210) and runs its handler. */
void obj_reset_run_handler(Object *obj, ObjHandler *handler) {
    obj->vz = 0;
    obj->vx = 0;
    obj_script_step(obj, handler);
}

void obj_init_from_src(Object *src, Object *obj, s32 flags) {
    s32 z;

    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj_hit_set_unk08(obj->index, 2);
    obj_hit_set_unk06(obj->index, 1);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj->health = src->health;
    obj->score = src->score;
    obj->damage = src->damage;
    obj->unk_17B = src->unk_17B;
    obj->x = src->x;
    obj->y = src->y;
    z = src->z;
    obj->accel_y = 0x1000;
    obj->z = z;
    obj->yaw = src->yaw;
    obj->pitch = src->pitch;
    obj->roll = src->roll;
    obj->placement = src->placement;
    obj_set_flags(obj, flags);
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}

/* When cam_range_check_alt finds nothing at the object's position (in 4096ths),
   flag the object pointed to by vars.snd.sound: its h.unk_24A if this
   object's mode is 1, otherwise its h.unk_24C. Then run the handler. */
void laser_barrier_boat_phase2(Object *obj, ObjHandler *handler) {
    if (cam_range_check_alt(obj->x >> 12, obj->y >> 12, obj->z >> 12) == 0) {
        if (obj->vars.enemy.mode == 1) {
            ((Object *)obj->vars.snd.sound)->vars.h.unk_24A = 1;
        } else {
            ((Object *)obj->vars.snd.sound)->vars.h.unk_24C = 1;
        }
    }
    obj_state_run(obj, handler);
}

s32 laser_barrier_boat_on_destroy(Object *obj) {
    s32 pitch;
    struct SpawnPos {
        s32 x;
        s32 y;
        s32 z;
        s32 unk_0C;
        s16 pitch;
        u16 yaw;
        u16 roll;
    } pos;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    pos.pitch = -pitch;
    pos.yaw = obj->yaw;
    pos.roll = obj->roll;
    model_slot_pchr(*(s32 *)obj->asset);
    spawn_effect(pos.x, pos.y, pos.z, 1);
    if (obj->vars.enemy.mode == 1) {
        ((Object *)obj->vars.snd.sound)->vars.h.unk_24A = 1;
    } else {
        ((Object *)obj->vars.snd.sound)->vars.h.unk_24C = 1;
    }
    return 0;
}

/* Distance between two positions. */
s32 pos_distance(Vec3 *a, Vec3 *b) {
    return SquareRoot0(length_sq(a->x - b->x, a->y - b->y, a->z - b->z));
}

/* Traces from vars.trace.from towards vars.trace.to, both boxed
 * (+0x14 / -0x78 offsets), and turns the hit into an effect angle. */
void obj_trace_hit(Object *obj) {
    TraceVec from;
    TraceVec hit;
    TraceVec to;
    s16 target;
    Object *src;
    Object *dst;
    s32 src_x;
    s32 src_y;
    s32 src_z;
    s32 dst_x;
    s32 dst_y;
    s32 dst_z;

    if (obj->vars.trace.active != 0 && obj->vars.trace.aim_yaw == 0 && obj->vars.trace.trace_flags == 0) {
        src = obj->vars.trace.from;
        from.x = src_x = src->x >> 12;
        from.y = src_y = src->y >> 12;
        from.z = src_z = src->z >> 12;
        dst = obj->vars.trace.to;
        hit.x = dst_x = dst->x >> 12;
        hit.y = dst_y = dst->y >> 12;
        hit.z = dst_z = dst->z >> 12;
        from.x = src_x + 0x14;
        from.y = src_y - 0x78;
        from.z = src_z + 0x14;
        hit.x = dst_x - 0x14;
        hit.y = dst_y - 0x78;
        hit.z = dst_z + 0x14;
        set_collide_mode(1);
        if (trace_objects(&from, &hit, 0x18, &to, &target)) {
            hit_target_masked(target, 1, atan2(to.z - from.z, to.x - from.x), obj->damage);
        }
        set_collide_mode(0);
    }
}

/* Draws the laser beam between the boat's two emitters as a row of sparks. */
void laser_barrier_boat_draw(Object *obj, ObjHandler *handler) {
    LaserBarrierBoatVars *v = (LaserBarrierBoatVars *) &obj->vars;
    Object *emitter, *self;
    Vec3 left, right, end;
    s16 rot[3];
    s32 step[3];
    s32 sprite, colour, steps, i, beam, level, green, flicker_green;
    s32 slot_base, ret;
    s32 pitch;
    Vec3 *start;
    s32 x, y, z;

    step[0] = 0;
    step[1] = 0;
    step[2] = 0xBE;
    if (v->beam == 0) {
        return;
    }
    __asm__("" : "=r"(self) : "0"(obj));
    if (v->left_state != 0 || v->right_state != 0) {
        return;
    }
    emitter = v->left;
    left.x = emitter->x >> 12;
    left.y = emitter->y >> 12;
    left.z = emitter->z >> 12;
    emitter = v->right;
    right.x = emitter->x >> 12;
    right.y = emitter->y >> 12;
    right.z = emitter->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;

    /* glow at both emitters */
    beam = v->beam + 0x80;
    ret = get_model_slot_base();
    level = beam >> 5;
    green = level;
    do { } while (0);
    start = &left;
    slot_base = ret;
    if (level == 0) {
        green = 1;
    }
    colour = (green << 16) | (level << 8) | level;
    left.x += 0x28;
    left.y -= 0x28;
    left.z += 0x14;
    right.x -= 0x28;
    right.y -= 0x28;
    right.z += 0x14;
    sprite = pool_spawn_scaled(slot_base + 0xF, 0x1800, 0x1800, 0x1000);
    spark_add(left.x, left.y, left.z, 0, 0, 0, sprite, colour);
    spark_add(right.x, right.y, right.z, 0, 0, 0, sprite, colour);

    /* the beam: one spark every 0xBE units, flickering */
    steps = pos_distance(start, &right) / 0xBE;
    sprite = slot_base + 8;
    beam = ((LaserBarrierBoatVars *) &self->vars)->beam;
    if (!is_paused()) {
        beam += (rand_b_next() % 32) * 16;
    }
    level = beam >> 5;
    flicker_green = level;
    if (level == 0) {
        flicker_green = 1;
    }
    colour = (flicker_green << 16) | (level << 8) | level;
    x = left.x;
    y = left.y;
    z = left.z;
    rotate_xz_twice(rot[1] - 0x400, rot[0], &step[0], &step[1], &step[2]);
    sprite = pool_spawn_scaled(sprite, 0x2000, 0x2000, 0x1000);
    for (i = 0; i < steps; i++) {
        spark_add(x, y, z, rot[1] + 0x400, rot[0], rot[2], sprite, colour);
        x += step[0];
        y += step[1];
        z += step[2];
    }

    /* the last, shortened spark up to the right emitter */
    end.x = x;
    end.y = y;
    end.z = z;
    beam = (pos_distance(&end, &right) << 12) / 0xBE;
    sprite = slot_base + 8;
    sprite = pool_spawn_scaled(sprite, 0x2000, 0x2000, beam);
    spark_add(x, y, z, rot[1] + 0x400, rot[0], rot[2], sprite, colour);
}
