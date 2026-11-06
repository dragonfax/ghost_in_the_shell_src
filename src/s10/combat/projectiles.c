/* projectiles: one of s10's own original source files (scripts/objmap.py); part of src/s10/main.c's unit, included there. */

extern s16 clip_screen_offset_y;
s32 clip_poly_near_project(s32 count, ClipVertex *src, ClipVertex *dst, s32 ox, s32 oy);
void prim_poly_clip_draw(s32 count, SVECTOR *verts, u8 *tint) {
    register View *vw asm("$22") = views;
    s32 cam_index = cur_cam_index;
    ClipVertex *pts;
    ClipVertex *clipped;
    s32 *rot;
    Camera *cam;
    s32 i;
    s32 x, y, z;
    s32 depth, dist;
    s32 r0, r1, r2;
    s32 ofx, ofy;
    s32 cx, cy, cz;
    ClipVertex *v;
    WorkArea *wa;

    if ((u32)(count - 1) < 8 && cam_index >= 0) {
        cam = &cameras[cam_index];
        pts = scratch_alloc(0x40);
        clipped = scratch_alloc(0x40);
        rot = scratch_alloc(0x20);
        depth = 0;
        FAKE_OPAQUE(depth);
        scale_rows((s16 *)&vw->unk_2C[0x34], (s16 *)&vw->unk_2C[0xC], (s16 *)rot);
        gte_load_R012(rot, r0, r1, r2);
        gte_load_R34(rot, r0, r1);
        ofx = view_screen_offsets[0].value;
        ofy = clip_screen_offset_y;
        gte_set_ctrl(OFX, ofx << 16);
        gte_set_ctrl(OFY, ofy << 16);
        gte_set_ctrl(H, 0x80);
        gte_set_ctrl(TRX, 0);
        gte_set_ctrl(TRY, 0);
        gte_set_ctrl(TRZ, 0);
        cx = cam->pos.vx;
        cy = cam->pos.vy;
        cz = cam->pos.vz;
        v = pts;
        for (i = depth; i < count;) {
            x = verts->vx - cx;
            y = verts->vy - cy;
            z = verts->vz - cz;
            gte_set(VXY0, (y << 16) | (x & 0xFFFF));
            gte_set(VZ0, z);
            gte_rtv0tr();
            gte_store(MAC1, v, 0);
            gte_get(MAC2, depth);
            gte_store(MAC3, v, 4);
            i++;
            v->y = depth;
            verts++;
            v++;
        }
        x = 0;
        y = 0;
        v = pts;
        z = 0;
        for (i = 0; i < count;) {
            i++;
            x += v->x;
            y += v->y;
            z += v->z;
            v++;
        }
        x /= count;
        y /= count;
        z /= count;
        depth = isqrt(length_sq(x, y, z));
        dist = depth;
        if (depth < 0) {
            dist = 0;
        }
        dist >>= 5;
        if (dist >= 0x200) {
            dist = 0x1FF;
        }
        depth = 0x208 - dist;
        count = clip_poly_near_project(count, pts, clipped, ((s16 *)vw->screen_offset)[0], ((s16 *)vw->screen_offset)[1]);
        count = clip_poly_range(count, clipped, pts, 0, vw->vram_w);
        count = clip_poly_range(count, pts, clipped, 0, vw->vram_h);
        if (count >= 3) {
            wa = work_area_ptr;
            wa->packet = prim_fan_ot_add(count, (u32 *)clipped, (u32 *)tint, wa->packet,
                                         (u8 *)((u32 *)vw->ot + depth));
        }
        scratch_top -= 0x20;
        scratch_top -= 0x40;
        scratch_top -= 0x40;
    }
}

s32 obj_blend_target_pos(Object *self, s32 *out_pos, s16 *out_angles);
s32 obj_shot_trace(Object *obj, void *from, void *to, VECTOR *out, s16 attacker);
/* While obj_blend_target_pos finds the target, traces a shot of length vars.turn.yaw along its angles and pushes the
   start and end points into the two point rings (words[3], words[4]); otherwise both rings shrink by one.
   The length then grows by speed, clamped to 0..0x400. */
void obj_shot_update(Object *obj, ObjHandler *handler) {
    s32 *pos = scratch_alloc(0x10);
    s16 *angles = scratch_alloc(8);
    ShotPointRing *ring;
    s32 dx;
    s32 dy;
    s32 dz;

    if (obj_blend_target_pos(obj, pos, angles) == 1) {
        s32 *from = scratch_alloc(0x10);
        s32 *to = scratch_alloc(0x10);
        SVECTOR *point = scratch_alloc(8);

        dx = 0;
        dy = 0;
        dz = 0;
        angles_to_vector(angles[1], -angles[0], obj->vars.turn.yaw, &dx, &dy, &dz);
        from[0] = pos[0];
        from[1] = pos[1];
        from[2] = pos[2];
        to[0] = pos[0] + (dx >> 12);
        to[1] = pos[1] + (dy >> 12);
        to[2] = pos[2] + (dz >> 12);
        obj_shot_trace(obj, from, to, (VECTOR *)to, angles[1]);

        point->vx = from[0];
        point->vy = from[1];
        point->vz = from[2];
        ring = (ShotPointRing *)obj->vars.after.near_ring;
        ring->head = (ring->head + 1) & 0x3F;
        ring->points[ring->head] = *point;
        if (ring->count < 0x40) {
            ring->count++;
        }

        point->vx = to[0];
        point->vy = to[1];
        point->vz = to[2];
        ring = (ShotPointRing *)obj->vars.after.far_ring;
        ring->head = (ring->head + 1) & 0x3F;
        ring->points[ring->head] = *point;
        if (ring->count < 0x40) {
            ring->count++;
        }
        scratch_top -= 8;
        scratch_top -= 0x10;
        scratch_top -= 0x10;
    } else {
        ShotPointRing *near = (ShotPointRing *)obj->vars.after.near_ring;
        ShotPointRing *far;

        if (near->count > 0) {
            near->count--;
        }
        far = (ShotPointRing *)obj->vars.after.far_ring;
        if (far->count > 0) {
            far->count--;
        }
    }
    obj->vars.turn.yaw += obj->speed;
    obj->vars.turn.yaw = MAX(MIN(obj->vars.turn.yaw, 0x400), 0);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

extern s16 target_blend_table_a[][4];
extern s16 target_blend_table_b[][4];
extern s16 target_blend_table_c[][4];
void vec3_blend(s32 wa, s32 wb, s16 *a, s16 *b, s32 *out);
void obj_patrol_turn(Object *obj, s32 range);
/* Blends three 4x4 tables at the target's (sx, sy) cell, rotates the three results
   by the target's yaw/pitch, and moves self to the blended position. */
s32 obj_blend_target_pos(Object *self, s32 *out_pos, s16 *out_angles) {
    Object *target = (Object *)self->vars.after.unk_250;
    s32 yaw;
    s32 pitch;
    s32 *tmp_a;
    s32 *tmp_b;
    s32 w_a;
    s32 w_b;
    s32 out_yaw;
    s32 out_pitch;
    u32 sx;
    u32 sy;
    s32 result = 0;

    if (target != NULL) {
        sx = target->type.unk_0C - 0x81;
        sy = target->type.unk_0E - 0x81;
        if (sx < 0x1E) {
            if (sy < 0x1E) {
                tmp_a = scratch_alloc(0x10);
                w_a = ((target->type.unk_0A + 1) << 12) / target->type.blend_duration;
                tmp_b = scratch_alloc(0x10);
                yaw = target->yaw;
                pitch = target->pitch;
                w_b = 0x1000 - w_a;

                vec3_blend(w_a, w_b, target_blend_table_a[sx], target_blend_table_a[sy], out_pos);
                vec3_blend(w_a, w_b, target_blend_table_b[sx], target_blend_table_b[sy], tmp_a);
                vec3_blend(w_a, w_b, target_blend_table_c[sx], target_blend_table_c[sy], tmp_b);

                rotate_xz_twice(yaw, -pitch, out_pos, out_pos + 1, out_pos + 2);
                rotate_xz_twice(yaw, -pitch, tmp_a, tmp_a + 1, tmp_a + 2);
                rotate_xz_twice(yaw, -pitch, tmp_b, tmp_b + 1, tmp_b + 2);

                out_pos[0] += target->x >> 12;
                out_pos[1] += target->y >> 12;
                out_pos[2] += target->z >> 12;
                self->x = out_pos[0] << 12;
                self->y = out_pos[1] << 12;
                self->z = out_pos[2] << 12;

                vector_to_angles(tmp_a[0] - tmp_b[0], tmp_a[1] - tmp_b[1], tmp_a[2] - tmp_b[2],
                                 &yaw, &pitch);
                scratch_top -= 0x10;
                scratch_top -= 0x10;

                out_pitch = pitch;
                out_yaw = yaw;
                out_angles[2] = 0;
                out_angles[0] = out_pitch;
                out_angles[1] = out_yaw;
                obj_patrol_turn(self, sy);
                result = 1;
            }
        }
    } else {
        self->speed = -0x80;
    }
    return result;
}

void vec3_blend(s32 wa, s32 wb, s16 *a, s16 *b, s32 *out) {
    out[0] = (a[0] * wa + b[0] * wb) >> 12;
    out[1] = (a[1] * wa + b[1] * wb) >> 12;
    out[2] = (a[2] * wa + b[2] * wb) >> 12;
    out[0] = (out[0] << 12) >> 12;
    out[1] = (out[1] << 12) >> 12;
    out[2] = (out[2] << 12) >> 12;
}

void obj_patrol_turn(Object *obj, s32 range) {
    s32 old_speed = obj->speed;
    s32 *pos;

    if (range >= 3) {
        obj->speed = 0x80;
    }
    if (range >= 0x18) {
        obj->speed = -0x80;
    }
    pos = (s32 *)scratch_top;
    if (obj->speed * old_speed < 0) {
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        scratch_top += 0x10;
        if (old_speed < 0) {
            sound_play_at_units(SND_PATROL_REVERSE_TURN | SND_GROUP(2), 0x7F, 0x3C, pos);
        } else {
            sound_play_at_units(SND_PATROL_FORWARD_TURN | SND_GROUP(2), 0x7F, 0x3C, pos);
        }
        scratch_top -= 0x10;
    }
}

/* Traces from..to through the world and the objects; on an object hit damages it, on a world hit stores the
 * hit point in out. Returns whether either hit. */
s32 obj_shot_trace(Object *obj, void *from, void *to, VECTOR *out, s16 attacker) {
    s32 hit_any = 0;
    s16 target;
    s32 world_hit;
    VECTOR *hit = scratch_alloc(0x10);

    target = 0;
    set_collide_mode(1);
    world_hit = trace_world(8, obj->vars.after.unk_24C, from, to, hit);
    if (trace_objects(from, hit, obj->vars.after.unk_24C, out, &target) == 1) {
        hit_target_masked(target, 8, attacker, obj->damage);
        hit_any = 1;
    } else if (world_hit == 1) {
        *out = *hit;
        hit_any = 1;
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    return hit_any;
}

/* Frees obj once its word at 0x250 is clear and the block its word at 0x254
 * points to has a zero word at +8 (nothing left for it to wait on). */
void obj_free_when_done(Object *obj, ObjHandler *handler) {
    s32 *linked = (s32 *)obj->vars.after.near_ring;

    if (obj->vars.after.unk_250 == 0 && linked[2] == 0) {
        obj_free(obj);
    }
}

extern SVECTOR ribbon_quad[4] __asm__("ribbon_quad_verts");
extern SVECTOR ribbon_quad_verts;
extern SVECTOR ribbon_quad_b_prev;
extern SVECTOR ribbon_quad_b_cur;
extern SVECTOR ribbon_quad_a_cur;
void prim_poly_clip_draw(s32 count, SVECTOR *verts, u8 *tint);
/* Draws the ribbon between the two point rings as quads fading out with
   age, then adds a spark at the newest point of ring A. */
void ribbon_draw(Object *obj, ObjHandler *handler) {
    RibbonRing *a = obj->vars.ribbon.ring_a;
    s32 i = 1;
    s32 count = a->count;
    RibbonRing *b = obj->vars.ribbon.ring_b;
    u8 rgb[4];
    s32 unused[2];
    s32 hi, lo, colour;
    s32 n, prev;
    s32 x, y, z, value;
    SparkList *list;
    SparkRec *s;
    u8 *tail;

    for (; i < count; i++) {
        prev = i - 1;
        ribbon_quad_verts = a->points[(a->head - prev) & 0x3F];
        ribbon_quad_b_prev = b->points[(b->head - prev) & 0x3F];
        ribbon_quad_a_cur = a->points[(a->head - i) & 0x3F];
        ribbon_quad_b_cur = b->points[(b->head - i) & 0x3F];
        rgb[0] = 0;
        rgb[1] = (count - i) * 4;
        rgb[2] = (count - i) * 2;
        prim_poly_clip_draw(4, ribbon_quad, rgb);
    }
    colour = obj->vars.ribbon.spark_colour * 4;
    lo = colour >> 6;
    hi = colour >> 5;
    value = obj->vars.ribbon.unk_248 + 0xEE;
    if ((hi | lo) == 0) {
        lo = 1;
    }
    colour = (lo << 16) | (hi << 8);
    n = spark_count;
    ribbon_quad_verts = a->points[a->head & 0x3F];
    list = &spark_list;
    x = ribbon_quad[0].vx;
    y = ribbon_quad_verts.vy;
    z = ribbon_quad_verts.vz;
    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[colour >> 24];
        list->tail[colour >> 24] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
}

void obj_init_linked(Object *obj, s32 initParam);

Object *obj_spawn_after(Node *pos, s32 mode, s32 param) {
    Object *obj;

    obj = NULL;
    if (mode >= 0 && mode <= 0) {
        obj = obj_new();
        if (obj != NULL) {
            list_insert_after(pos, &obj->node);
            obj_hit_clear(obj->index);
            obj_hit_flag_set(obj->index, 0);
            obj->vars.after.unk_248 = param;
            obj->vars.after.unk_24A = mode;
            if (mode == 0) {
                obj_init_linked(obj, (s32)pos);
            }
        }
    }
    return obj;
}

void obj_shot_update(Object *obj, ObjHandler *handler);
void obj_free_when_done(Object *obj, ObjHandler *handler);
void ribbon_draw(Object *obj, ObjHandler *handler);
s32 ribbon_slot_claim();
void obj_init_linked(Object *obj, s32 initParam) {
    obj->handlers[1].fn = obj_shot_update;
    obj->handlers[2].fn = obj_free_when_done;
    obj->handlers[3].fn = ribbon_draw;

    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;

    obj->vars.after.unk_24C = 8;
    obj->vars.after.unused_24E = 0;
    obj->vars.after.unk_250 = initParam;
    obj->vars.after.near_ring = ribbon_slot_claim();
    obj->vars.after.far_ring = ribbon_slot_claim();
    obj->damage = 0x10;
    obj->speed = -0x80;
}

void slot_records_clear_all(void) {
    slot_records_clear();
}


void pair_release_child(Object *obj) {
    if (obj != NULL) {
        obj->vars.enemy.unk_250 = 0;
    }
}


void rocket_update(Object *obj);
/* Rocket flight: falls under gravity and bounces off the world; each of the first 3 bounces splits the velocity and
 * spins it up, after which the rocket turns into rocket_update. */
void rocket_bounce_update(Object *obj, ObjHandler *handler) {
    Vec3 *hit = scratch_alloc(0x10);
    s32 bounced = obj_bounce_off_world(obj);
    s32 vx = obj->vx;
    s32 vz = obj->vz;
    s32 vy = obj->vy + 0x1000;
    s32 r;
    s32 yaw;
    s32 yaw_step;
    s32 pitch;

    obj->vy = vy;
    if (obj_trace_world(obj, hit) == 1) {
        obj->vars.h.unk_250++;
        if ((s16)obj->vars.h.unk_250 < 3) {
            vx = vx * 2 / (rand_a_next() % 7 + 2);
            vy = -vy * 3 / (rand_a_next() % 2 + 4);
            vz = vz * 2 / (rand_a_next() % 7 + 2);
            obj->vx = vx;
            obj->vy = vy;
            obj->vz = vz;
            r = rand_a_next();
            if (r < 0) {
                r += 0xF;
            }
            obj->unk_226[1] = (u32)r >> 4;
            r = rand_a_next();
            if (r < 0) {
                r += 0xF;
            }
            obj->unk_226[0] = (u32)r >> 4;
        } else {
            obj->vx = 0;
            obj->vy = 0;
            obj->vz = 0;
            vx = 0;
            obj->x = hit->x << 12;
            vy = 0;
            obj->y = hit->y << 12;
            vz = 0;
            obj->z = hit->z << 12;
            handler->fn = (void *)rocket_update;
        }
        sound_play_at_units(SND_ROCKET_BOUNCE | SND_GROUP(2), 0x7F, 0x3C, hit);
    } else if (bounced == 1) {
        hit->x = obj->x >> 12;
        hit->y = obj->y >> 12;
        hit->z = obj->z >> 12;
        sound_play_at_units(SND_ROCKET_BOUNCE | SND_GROUP(2), 0x7F, 0x3C, hit);
    }
    yaw = obj->yaw;
    yaw_step = obj->unk_226[0];
    obj->x += vx;
    yaw += yaw_step;
    obj->yaw = yaw;
    obj->y += vy;
    obj->z += vz;
    if ((s16)obj->vars.h.unk_250 != 2) {
        s32 pitch_step;

        pitch = obj->pitch;
        pitch_step = obj->unk_226[1];
        obj->pitch = pitch + pitch_step;
    } else {
        pitch = obj->pitch;
        yaw = angle_approach(pitch, 0, 0x100);
        obj->pitch = yaw;
    }
    scratch_top -= 0x10;
}

/* Levels the pitch, counts vars.h.unk_24E up, adds 0x80 to unk_252 once the count passes 0xF0,
   and at 0x12C calls hit_target_masked and sets hit. */
void rocket_update(Object *obj) {
    obj->pitch = angle_approach(obj->pitch, 0, 0x100);
    obj->vars.rocket.life_counter++;
    if ((s16)obj->vars.rocket.life_counter >= 0xF0) {
        obj->vars.h.unk_252 += 0x80;
    }
    if ((s16)obj->vars.rocket.life_counter >= 0x12C) {
        hit_target_masked((s16)obj->index, 4, 0, 0xA);
        obj->hit = 1;
    }
}

/* Traces a world query from the object's position, and from the position plus its velocity-like offset. */
s32 obj_trace_world(Object *obj, Vec3 *hit) {
    Vec3 *pos = scratch_alloc(0x10);
    Vec3 *target = scratch_alloc(0x10);
    s32 result;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    target->x = (obj->x + obj->vx) >> 12;
    target->y = (obj->y + obj->vy) >> 12;
    target->z = (obj->z + obj->vz) >> 12;
    result = trace_world(8, obj->vars.rocket.trace_flags, pos, target, hit);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return result;
}

/* Probes the world one step along x (0x208), then along z (0x210); a velocity that runs into something is
 * reversed. Returns 1 when either was. */
s32 obj_bounce_off_world(Object *obj) {
    s32 bounced = 0;
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to = scratch_alloc(0x10);
    Vec3 *hit = scratch_alloc(0x10);

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    to->x = (obj->x + obj->vx) >> 12;
    to->y = from->y;
    to->z = from->z;
    if (trace_world(8, obj->vars.rocket.trace_flags, from, to, hit) == 1) {
        bounced = 1;
        obj->vx = -obj->vx;
    }
    to->x = from->x;
    to->y = from->y;
    to->z = (obj->z + obj->vz) >> 12;
    if (trace_world(8, obj->vars.rocket.trace_flags, from, to, hit) == 1) {
        bounced = 1;
        obj->vz = -obj->vz;
    }
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return bounced;
}

void fx_shoot_at_player(void *origin, s32 len);
/* Callback of the hit records (rocket_phase2): while the record is near (unk_28 < 0x999),
   every object of type 0xBB within range (distance squared <= the record's range squared)
   gets hit_target_masked; then fx_shoot_at_player runs on the record. */
void rocket_blast_callback(FxEffect *rec) {
    Object *obj;
    s32 range;
    s32 range_sq;

    if (rec->intensity < 0x999) {
        obj = (Object *)*get_obj_list_actors();
        range = rec->size >> 12;
        range_sq = range * range;
loop:
        if (obj->node.next == NULL) {
            goto done;
        }
        if ((u8)obj->rocket_marker == 0xBB &&
            range_sq >= length_sq((obj->x >> 12) - ((Vec3 *)rec)->x,
                                  (obj->y >> 12) - ((Vec3 *)rec)->y,
                                  (obj->z >> 12) - ((Vec3 *)rec)->z)) {
            hit_target_masked(obj->index, 4, 0, 0xA);
        }
        obj = (Object *)obj->node.next;
        goto loop;
done:
        fx_shoot_at_player(rec, rec->size >> 12);
    }
}


void fx_shoot_at_player(void *origin, s32 len) {
    s32 *from = origin;
    VECTOR *aim_pos = scratch_alloc(0x10);
    s32 dx = 0, dy = 0, dz = 0;
    s32 pitch = 0, yaw = 0;
    s16 target = 0;

    player_position_copy(aim_pos);
    dx = aim_pos->vx - from[0];
    dy = aim_pos->vy - from[1];
    dz = aim_pos->vz - from[2];
    vector_to_angles(dx, dy, dz, &yaw, &pitch);
    angles_to_vector(yaw, -pitch, len, &dx, &dy, &dz);
    aim_pos->vx = from[0] + (dx >> 12);
    aim_pos->vy = from[1] + (dy >> 12);
    aim_pos->vz = from[2] + (dz >> 12);
    set_collide_mode(1);
    if (trace_objects(origin, aim_pos, 8, aim_pos, &target) == 1) {
        hit_target_masked(target, 4, (s16)yaw, 10);
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
}


extern RecTemplate rocket_blast_templates[2];
extern s32 d_80119E84;
void rocket_blast_callback();
/* Frees the object at its position: when hurt, with a sound and two records (the second with
   rocket_blast_callback as callback); otherwise, unless it was hit, with an effect. */
void rocket_phase2(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    if ((obj_hit_damage(obj->index) << 16) > 0) {
        sound_play_at_units(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, pos);
        fx_spawn_template((s32 *)pos, &rocket_blast_templates[0], 0);
        fx_spawn_template((s32 *)pos, &rocket_blast_templates[1], rocket_blast_callback);
    } else if (obj->hit != 1 && cam_range_check(pos->x, pos->y, pos->z) != 0) {
        if (d_80119E84 == 0) {
            spawn_effect(pos->x, pos->y, pos->z, 0x80000000);
        } else {
            goto done;
        }
    }
    obj_free(obj);
done:
    scratch_top -= 0x10;
}

static inline void spark_add_head_u(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, u16 rz, s32 value, s32 colour) {
    s32 n = SPARK_COUNT;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = spark_list_tail;
        spark_list_tail = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}
static inline void spark_add_scalar(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    s32 n = spark_count;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[colour >> 24];
        list->tail[colour >> 24] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}
/* Two spark records at the rocket: its exhaust (rotated with it), then a glow pulsing with cos(unk_252), added twice. */
void rocket_draw(Object *obj) {
    s32 *pos;
    s16 *rot;
    s32 value;
    u16 roll;
    s32 r;
    s32 g;
    s32 colour;
    s32 pitch;
    s32 flag;
    s32 base;

    base = obj->vars.rocket.unk_248;
    pos = (s32 *)scratch_top;
    scratch_top += 0x10;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot = scratch_alloc(8);
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    value = base + 0xD0;
    spark_add_head_u(&spark_list, pos[0], pos[1], pos[2], rot[1], rot[0], roll, value, 0);
    colour = (cos_table[obj->vars.h.unk_252 & 0xFFF].value + 0x1000) / 2;
    g = colour / 2;
    r = colour >> 5;
    g >>= 5;
    flag = (r | g) == 0;
    colour = (flag << 16) | (g << 8) | r;
    value = obj->vars.rocket.unk_248 + 0xEE;
    spark_add_scalar(&spark_list, pos[0], pos[1], pos[2], 0, 0, 0, value, colour);
    spark_add_scalar(&spark_list, pos[0], pos[1], pos[2], 0, 0, 0, value, colour);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void rocket_init(Object *obj, s32 arg);
s32 rocket_spawn(s32 arg0, s32 *pos, u16 *rot, s32 arg3, s32 arg4) {
    s32 result = 0;
    Object *obj;
    u16 roll;

    if (arg3 >= 0) {
        if (arg3 <= 0) {
            obj = obj_new();
            if (obj != NULL) {
                list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
                obj->hit = 0;
                obj_hit_clear(obj->index);
                obj_hit_flag_set(obj->index, 0);
                obj->x = pos[0] << 12;
                obj->y = pos[1] << 12;
                obj->z = pos[2] << 12;
                obj->pitch = rot[0];
                obj->yaw = rot[1];
                roll = rot[2];
                obj->vars.rocket.unk_248 = arg4;
                obj->vars.rocket.unk_24A = arg3;
                obj->roll = roll;
                if (arg3 == 0) {
                    rocket_init(obj, arg0);
                }
                result = 1;
            }
        }
    }
    return result;
}

void rocket_bounce_update(Object *obj, ObjHandler *handler);
void rocket_draw(Object *obj);
/* Sets up the object (handlers, flags, speed 0x28), gives it a velocity along its yaw/pitch, and passes its
 * position (whole units) to effect_spawn_at through a scratch vector. Callers pass a second argument it ignores. */
void rocket_init(Object *obj, s32 unused) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 vx;
    s32 vy;
    s32 vz;

    vx = 0;
    vy = 0;
    vz = 0;
    *(u8 *)&obj->rocket_marker = 0xBB;
    obj->handlers[1].fn = rocket_bounce_update;
    obj->handlers[2].fn = (void *)rocket_phase2;
    obj->handlers[3].fn = (void *)rocket_draw;
    obj->flags = 0x80;
    obj->vars.rocket.trace_flags = 0x18;
    obj->speed = 0x28;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.rocket.life_counter = 0;
    obj->vars.h.unk_250 = 0;
    obj->vars.h.unk_252 = 0;
    obj->damage = 0;
    angles_to_vector(obj->yaw, -obj->pitch, 0x28, &vx, &vy, &vz);
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    effect_spawn_at(pos, obj->vars.rocket.unk_248 + 0xC8, 3, 0x19);
    scratch_top -= 0x10;
}

extern FxRecordParams D_8011D3E8;
s32 obj_trace_velocity(Object *obj, TraceHit *out);
void obj_shoot_callback(FxRecord *rec);
void projectile_flight_update(Object *obj, ObjHandler *handler) {
    s32 *pos = (s32 *)scratch_top;
    s32 *pz = pos + 2;
    s32 aim_yaw;
    s32 aim_pitch;
    s32 vel_x;
    s32 vel_y;
    s32 vel_z;
    s32 yaw;
    s32 pitch;
    s32 speed;
    register s32 roll asm("$6");
    register s16 count asm("$7");

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    vel_x = 0;
    vel_y = 0;
    vel_z = 0;
    *pz = obj->z >> 12;
    scratch_top += 16;
    if (obj->vars.trace.active % 3 == 0) {
        effect_spawn_at((Vec3 *)pos, get_model_slot_base() + 0x20, 0xA, 0xC);
    }
    if ((u16)(obj->vars.trace.active - 4) < 0xC) {
        aim_yaw = 0;
        aim_pitch = 0;
        vector_to_angles((cam_pos >> 12) - pos[0], (cam_pos_y >> 12) - pos[1], (cam_pos_z >> 12) - pos[2], &aim_yaw, &aim_pitch);
        obj->yaw = angle_approach(obj->yaw, aim_yaw, 0x20);
        obj->pitch = angle_approach(obj->pitch, aim_pitch, 0x20);
    }
    yaw = obj->yaw;
    pitch = obj->pitch;
    speed = obj->speed;
    angles_to_vector(yaw, -pitch, speed, &vel_x, &vel_y, &vel_z);
    obj->vx = vel_x;
    obj->vy = vel_y;
    obj->vz = vel_z;
    if (obj_trace_velocity(obj, (TraceHit *)pos) == 1) {
        spawn_effect(pos[0], pos[1], pos[2], 0x80000000);
        sound_play_at_units(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, pos);
        fx_rec34_spawn_cb(pos, &D_8011D3E8, (s32)obj_shoot_callback);
        obj->hit = 1;
    }
    scratch_top -= 16;
    count = obj->vars.trace.active;
    count++;
    obj->x += vel_x;
    roll = obj->roll + 0x60;
    obj->y += vel_y;
    obj->z += vel_z;
    obj->vars.trace.active = count;
    obj->roll = roll;
}

/* Traces a line from the object's position to position + velocity; returns 1 if it hit something. */
s32 obj_trace_velocity(Object *obj, TraceHit *out) {
    s32 result = 0;
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to;
    TraceHit *hit;
    s16 extra;
    s32 world;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    to = scratch_alloc(0x10);
    to->x = (obj->x + obj->vx) >> 12;
    to->y = (obj->y + obj->vy) >> 12;
    hit = scratch_alloc(0x10);
    extra = 0;
    to->z = (obj->z + obj->vz) >> 12;
    set_collide_mode(1);
    world = trace_world(8, obj->vars.h.unk_24C, from, to, hit);
    if (trace_objects(from, hit, obj->vars.h.unk_24C, out, &extra) != 1) {
        if (world == 1) {
            *out = *hit;
            result = 1;
        }
    } else {
        result = 1;
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return result;
}

void aim_at_player(VECTOR *pos, s32 range);
/* FxRecord step (projectile_flight_update spawns it): aims at the player from the record's position, range from its
 * word at 0x18 (12 fraction bits). */
void obj_shoot_callback(FxRecord *rec) {
    aim_at_player((VECTOR *)rec->pos, rec->radius_motion[0] >> 12);
}

/* Turns toward a target that is within `range` horizontally and 0x100 vertically. */
void aim_at_player(VECTOR *pos, s32 range) {
    VECTOR *tgt = scratch_alloc(0x10);
    s32 dx, dy, dz;
    s32 yaw, pitch;

    player_position_copy(tgt);
    dx = tgt->vx - pos->vx;
    dz = tgt->vz - pos->vz;
    dy = tgt->vy - pos->vy;
    if (length_sq(dx, 0, dz) <= range * range) {
        if (ABS(dy) < 0x101) {
            yaw = 0;
            pitch = 0;
            vector_to_angles(dx, dy, dz, &yaw, &pitch);
            hit_target_masked(0, 4, yaw, 10);
        }
    }
    scratch_top -= 0x10;
}

extern s32 d_80119E84;

void projectile_impact_phase2(Object *obj) {
    s32 x;
    s32 y;
    s32 z;

    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    if (obj->hit != 1 && cam_range_check(x, y, z) != 0) {
        if (d_80119E84 == 0 || (obj_hit_damage(obj->index) << 16) > 0) {
            spawn_effect(x, y, z, 0x80000000);
        } else {
            return;
        }
    }
    obj_free(obj);
}


static inline void spark_add_tail0_u(s32 x, s32 y, s32 z, s32 ry, s32 rx, u16 rz, s32 value) {
    SparkList *list = &spark_list;
    s32 n = SPARK_COUNT;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = 0;
        tail = spark_list_tail;
        spark_list_tail = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}
/* Draws two sparks: one at the object, one rotated 15 units ahead of it. */
void projectile_trail_draw(Object *obj, ObjHandler *handler) {
    s32 off[3];
    s32 *pos;
    s16 *rot;
    s32 value;
    s32 pitch;
    s32 z;

    off[0] = 0;
    off[1] = 0;
    off[2] = -0xF;
    pos = scratch_alloc(0x10);
    value = obj->vars.h.unk_248 + 0xD8;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    rot = scratch_alloc(8);
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    spark_add_tail0_u(pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], value);
    value = obj->vars.h.unk_248 + 0xDA;
    rotate_xz_twice(obj->yaw, -obj->pitch, &off[0], &off[1], &off[2]);
    pos[0] += off[0];
    z = pos[2] + off[2];
    pos[1] += off[1];
    pos[2] = z;
    spark_add_tail0_u(pos[0], pos[1], pos[2], 0, 0, 0, value);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void projectile_init(Object *obj, s32 unused);
/* Same code as rocket_spawn (s10). */
s32 projectile_spawn(s32 arg0, s32 *pos, u16 *rot, s32 arg3, s32 arg4) {
    s32 result = 0;
    Object *obj;
    u16 roll;

    if (arg3 >= 0) {
        if (arg3 <= 0) {
            obj = obj_new();
            if (obj != NULL) {
                list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
                obj->hit = 0;
                obj_hit_clear(obj->index);
                obj_hit_flag_set(obj->index, 0);
                obj->x = pos[0] << 12;
                obj->y = pos[1] << 12;
                obj->z = pos[2] << 12;
                obj->pitch = rot[0];
                obj->yaw = rot[1];
                roll = rot[2];
                obj->vars.h.unk_248 = arg4;
                obj->vars.h.unk_24A = arg3;
                obj->roll = roll;
                if (arg3 == 0) {
                    projectile_init(obj, arg0);
                }
                result = 1;
            }
        }
    }
    return result;
}

void projectile_flight_update(Object *obj, ObjHandler *handler);
void projectile_trail_draw(Object *obj, ObjHandler *handler);
/* Initialises a projectile: handlers, speed 0x1C along its facing, and a spawn effect at its position. */
void projectile_init(Object *obj, s32 unused) {
    s32 *pos = scratch_alloc(0x10);
    s32 vel[3];
    s32 x, vx, vy, vz;

    vel[0] = 0;
    vel[1] = 0;
    vel[2] = 0;
    obj->handlers[1].fn = projectile_flight_update;
    obj->handlers[2].fn = projectile_impact_phase2;
    obj->handlers[3].fn = projectile_trail_draw;
    obj->flags = 0x80;
    obj->vars.h.unk_24C = 9;
    obj->speed = 0x1C;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.h.unk_24E = 0;
    obj->damage = 0;
    angles_to_vector(obj->yaw, -obj->pitch, 0x1C, &vel[0], &vel[1], &vel[2]);
    vx = vel[0];
    vy = vel[1];
    vz = vel[2];
    x = obj->x >> 12;
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
    pos[0] = x;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    effect_spawn_at((Vec3 *)pos, obj->vars.h.unk_248 + 0xC8, 3, 0x19);
    scratch_top -= 0x10;
}

s32 projectile_trace(Object *obj, VECTOR *out);
void spark_spawn_random(Object *obj);

/* Falling shard step: gravity, bursts (sound, effect, 16 sparks) on a hit or once it starts falling,
 * moves, spins and raises the 0..0x1000 counter at 0x24E. */
void spark_fly_update(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 vx = obj->vx;
    s32 vz = obj->vz;
    s32 vy;
    s32 i;
    s32 roll;
    s16 level;

    vy = obj->vy + 0x1000;
    obj->vy = vy;
    if (projectile_trace(obj, (VECTOR *)pos) == 1) {
        sound_play_at_units(SND_S10_PROJECTILE_IMPACT | SND_GROUP(2), 0x7F, 0x3C, pos);
        spawn_effect(pos->x, pos->y, pos->z, 0x80000002);
        obj->hit = 1;
    }
    if (obj->vy >= 0 && obj->hit == 0) {
        i = 0;
        sound_play_at_units(SND_S10_PROJECTILE_IMPACT | SND_GROUP(2), 0x7F, 0x3C, pos);
        spawn_effect(pos->x, pos->y, pos->z, 0x80000002);
        obj->hit = 1;
        do {
            spark_spawn_random(obj);
            i++;
        } while (i < 0x10);
    }
    roll = obj->roll;
    roll += 0x60;
    level = obj->vars.follow.unk_24E + 0x80;
    obj->x += vx;
    obj->y += vy;
    obj->z += vz;
    obj->roll = roll;
    obj->vars.follow.unk_24E = level;
    level = MAX(MIN(level, 0x1000), 0);
    obj->vars.follow.unk_24E = level;
    scratch_top -= 0x10;
}

s32 projectile_trace(Object *obj, VECTOR *out);
void missile_explode(Object *obj, ObjHandler *handler);
/* Behaviour step: moves the object by its speed (or, once projectile_trace finds a target, jumps to it and
 * switches handler), and raises the counter at 0x24E by 0x55, capped at 0x1000. */
void missile_update(Object *obj, ObjHandler *handler) {
    Vec3 *pos = scratch_alloc(0x10);

    if (projectile_trace(obj, (VECTOR *)pos) == 1) {
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        sound_play_at_units(SND_MISSILE_IMPACT | SND_GROUP(2), 0x7F, 0x3C, pos);
        handler->fn = missile_explode;
    } else {
        obj->x += obj->vx;
        obj->y += obj->vy;
        obj->z += obj->vz;
    }
    *(s16 *)&obj->vars.spark_or_shot.blend_factor += 0x55;
    *(s16 *)&obj->vars.spark_or_shot.blend_factor = MAX(MIN(*(s16 *)&obj->vars.spark_or_shot.blend_factor, 0x1000), 0);
    scratch_top -= 0x10;
}

void missile_explode(Object *obj, ObjHandler *handler) {
    Vec3 *pos;

    if ((s16)obj->vars.spark_or_shot.blend_factor == 0) {
        pos = (Vec3 *)scratch_top;
        pos->x = obj->x >> 12;
        scratch_top += 0x10;
        pos->y = obj->y >> 12;
        pos->z = obj->z >> 12;
        effect_spawn_at(pos, obj->vars.spark_or_shot.effect_base + 0xCC, 4, 0x15);
        scratch_top -= 0x10;
        obj->hit = 1;
    }
    obj->vars.spark_or_shot.blend_factor -= 0x155;
    obj->vars.spark_or_shot.blend_factor = MAX(MIN((s16)obj->vars.spark_or_shot.blend_factor, 0x1000), 0);
}

/* Traces the object's step through the world, then through other objects. Returns 1 on a hit; the hit
 * position goes to `out` (a world hit) and an object hit damages its target. */
s32 projectile_trace(Object *obj, VECTOR *out) {
    s32 result = 0;
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to = scratch_alloc(0x10);
    VECTOR *hit = scratch_alloc(0x10);
    s16 target = 0;
    s32 world;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    to->x = (obj->x + obj->vx) >> 12;
    to->y = (obj->y + obj->vy) >> 12;
    to->z = (obj->z + obj->vz) >> 12;
    set_collide_mode(1);
    world = trace_world(8, obj->vars.spark_or_shot.trace_flags, from, to, hit);
    if (trace_objects(from, hit, obj->vars.spark_or_shot.trace_flags, out, &target) == 1) {
        hit_target_masked(target, 2, obj->yaw, obj->damage);
        result = 1;
    } else if (world == 1) {
        *out = *hit;
        result = 1;
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return result;
}

/* Spawns a spark at the object, aimed along a random direction plus the object's own heading. */
void spark_spawn_random(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    s32 dx = 0, dy = 0, dz = 0;
    s32 fx = 0, fy = 0, fz = 0;
    s32 yaw;
    s32 pitch;
    s32 spread;

    pitch = 0;
    yaw = 0;
    spread = (rand_a_next() * 0x600) / 0x1000;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    angles_to_vector(rand_a_next(), 0, spread, &dx, &dy, &dz);
    angles_to_vector(obj->yaw, 0, 0x200, &fx, &fy, &fz);
    dx = (dx + fx) >> 12;
    dy = -pos->y;
    dz = (dz + fz) >> 12;
    vector_to_angles(dx, dy, dz, &yaw, &pitch);
    rot->vz = 0;
    rot->vx = pitch;
    rot->vy = yaw;
    spark_or_shot_spawn(obj, pos, rot, 1, obj->vars.spark_or_shot.effect_base);
    scratch_top -= 8;
    scratch_top -= 0x10;
}


void rocket_hit_phase2(Object *obj) {
    s32 x;
    s32 y;
    s32 z;

    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    if (obj->hit != 1 && cam_range_check(x, y, z) != 0) {
        if (d_80119E84 == 0 || (obj_hit_damage(obj->index) << 16) > 0) {
            spawn_effect(x, y, z, 0x80000000);
        } else {
            return;
        }
    }
    obj_free(obj);
}



void obj_free_outside_area(Object *obj) {
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    if ((obj->hit == 1) || (cam_range_check(x, y, z) == 0)) {
        obj_free(obj);
    }
}


void spark_emit(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 c;
    s32 v;
    s32 z;
    s32 value = obj->vars.h.unk_248 + 0xC0;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    z = obj->z >> 12;
    pos->z = z;
    spark_add(pos->x, pos->y, z, 0, 0, (u16)obj->roll, value, 0);
    value = obj->vars.h.unk_248 + 0xC1;
    c = (obj->vars.h.unk_24E << 16) >> 21;
    v = c;
    if (c == 0) {
        v = 1;
    }
    spark_add(pos->x, pos->y, pos->z, 0, 0, 0, value, (v << 16) | (c << 8) | c);
    scratch_top -= 0x10;
}

/* Adds a spark at the object's position with its pitch negated, its yaw and roll, and the blend value
 * from obj_blend_slots, on the head chain (colour 0). The position and rotation go through scratch
 * vectors first, as in speedboat_wake_draw. */
void spark_emit_head_obj(Object *obj, ObjHandler *handler) {
    s16 *rot;
    s32 *pos;
    s32 value;
    s32 pitch;
    u16 roll;
    s32 n;
    s32 x, y, z, rx, ry;
    SparkList *list;
    SparkRec *rec;
    u8 *tail;

    pos = (s32 *)scratch_top;
    scratch_top += 0x10;
    rot = (s16 *)scratch_top;
    scratch_top += 8;
    value = obj_blend_slots(obj, 0);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    rx = rot[0];
    ry = rot[1];
    list = &spark_list;
    n = SPARK_COUNT;
    x = pos[0];
    y = pos[1];
    z = pos[2];
    if (n < 0xFF) {
        rec = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)rec->colour = 0;
        tail = spark_list_tail;
        spark_list_tail = &rec->next;
        *tail = n;
        rec->next = 0;
        rec->x = x;
        rec->y = y;
        rec->z = z;
        rec->unk_12 = value;
        rec->yaw = ry;
        rec->pitch = rx;
        rec->roll = roll;
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

static inline s32 obj_slot(Object *obj, s32 index) {
    return obj->vars.spark_or_shot.effect_base + index;
}
/* Blends two adjacent table entries (base + 0xC6, base + 0xC7) by the object's weight at 0x24E. */
s32 obj_blend_slots(Object *obj, s32 base) {
    s32 blend[4];

    switch ((s16)obj->vars.spark_or_shot.blend_factor) {
    case 0:
        return obj_slot(obj, base + 0xC6);
    case 0x1000:
        return obj_slot(obj, base + 0xC7);
    }
    blend[0] = obj_slot(obj, base + 0xC6);
    blend[1] = obj_slot(obj, base + 0xC7);
    blend[2] = 0x1000 - (s16)obj->vars.spark_or_shot.blend_factor;
    blend[3] = 0x1000 - blend[2];
    return pchr_blend(blend[0], blend[1], blend[2], 0);
}

/* Spawns an object at pos/rot and sets it up for mode 0 or 1 (spark_init, shot_init). */
s32 spark_or_shot_spawn(Object *owner, Vec3 *pos, SVECTOR *rot, s32 mode, s32 arg4) {
    Object *obj;
    s32 result;
    s16 roll;

    result = 0;
    if ((u32) mode < 2) {
        obj = obj_new();
        if (obj != NULL) {
            list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
            obj->hit = 0;
            obj_hit_clear(obj->index);
            obj_hit_flag_set(obj->index, 0);
            obj->x = pos->x << 12;
            obj->y = pos->y << 12;
            obj->z = pos->z << 12;
            obj->pitch = rot->vx;
            obj->yaw = rot->vy;
            roll = rot->vz;
            obj->vars.spark_or_shot.effect_base = arg4;
            obj->vars.spark_or_shot.mode = mode;
            obj->roll = roll;
            switch (mode) {
            case 0:
                spark_init(obj, owner);
                break;
            case 1:
                shot_init(obj, owner);
                break;
            }
            result = 1;
        }
    }
    return result;
}

void spark_fly_update(Object *obj);
/* Sets up the object (handlers, flags, speed 0x24), gives it a velocity along its yaw/pitch, and passes its
 * position (whole units) to effect_spawn_at through a scratch vector. */
void spark_init(Object *obj, Object *owner) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 vx;
    s32 vy;
    s32 vz;

    vx = 0;
    vy = 0;
    vz = 0;
    obj->handlers[1].fn = spark_fly_update;
    obj->handlers[2].fn = (void *)rocket_hit_phase2;
    obj->handlers[3].fn = (void *)spark_emit;
    obj->flags = 0x80;
    obj->vars.spark_or_shot.trace_flags = 0x13;
    obj->damage = 0x10;
    obj->speed = 0x24;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.spark_or_shot.blend_factor = 0;
    angles_to_vector(obj->yaw, -obj->pitch, 0x24, &vx, &vy, &vz);
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    effect_spawn_at(pos, obj->vars.spark_or_shot.effect_base + 0xC8, 3, 0x19);
    scratch_top -= 0x10;
}

void spark_emit_head_obj(Object *obj, ObjHandler *handler);
void shot_init(Object *obj, Object *owner) {
    s32 vec_x;
    s32 vec_y;
    s32 vec_z;

    vec_x = 0;
    vec_y = 0;
    vec_z = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[1].fn = missile_update;
    obj->handlers[2].fn = (void (*)(Object *, ObjHandler *))obj_free_outside_area;
    obj->handlers[3].fn = spark_emit_head_obj;
    obj->flags = 0x80;
    obj->vars.spark_or_shot.trace_flags = 9;
    obj->damage = 8;
    obj->speed = 0x28;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.spark_or_shot.blend_factor = 0;
    angles_to_vector(obj->yaw, -obj->pitch, 0x28, &vec_x, &vec_y, &vec_z);
    obj->vx = vec_x;
    obj->vy = vec_y;
    obj->vz = vec_z;
}

s32 obj_fall_probe(Object *obj, Vec3 *hit);
/* Falling object: gravity (+0x1000 to vy), moves by its velocity. When obj_fall_probe reports a hit (1) it
 * bursts: a sound, 12 effects fanned around the yaw toward the player, and it is marked hit. Then it
 * faces its direction of travel. */
void falling_update(Object *obj, ObjHandler *handler) {
    Vec3 *pos = scratch_alloc(0x10);
    Vec3 *target;
    SVECTOR *rot;
    s32 yaw = 0;
    s32 pitch = 0;
    s32 vx, vy, vz;
    s32 i;

    vy = obj->vy + 0x1000;
    vx = obj->vx;
    vz = obj->vz;
    obj->vy = vy;
    if (obj_fall_probe(obj, pos) == 1) {
        target = scratch_alloc(0x10);
        rot = scratch_alloc(8);
        i = 0;
        effect_spawn_at(pos, obj->vars.obj_debris.variant + 0xE9, 4, 0xA);
        player_position_copy((VECTOR *)target);
        vector_to_angles(target->x - pos->x, target->y - pos->y, target->z - pos->z, &yaw, &pitch);
        rot->vx = 0;
        rot->vz = 0;
        rot->vy = yaw;
        pos->y -= 0x48;
        sound_play_at_units(SND_DEBRIS_IMPACT | SND_GROUP(2), 0x7F, 0x3C, pos);
        do {
            obj_debris_spawn(obj, pos, rot, 1, obj->vars.obj_debris.variant);
            rot->vy += 0x155;
            i++;
        } while (i < 12);
        obj->hit = 1;
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
    obj->x += vx;
    obj->y += vy;
    obj->z += vz;
    vector_to_angles(vx >> 12, vy >> 12, vz >> 12, &yaw, &pitch);
    obj->yaw = *(u16 *)&yaw;
    obj->pitch = *(u16 *)&pitch;
    scratch_top -= 0x10;
}

s32 obj_trace_damage(Object *obj, TraceHit *out);
/* Flame step: puffs every third frame, burns out on its lifetime or a hit (sound, effect, debris), then
 * drifts by its speeds and grows its scale toward 0x1000. */
void flame_update(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot;
    s32 count;
    s32 i;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    if ((s16)(obj->vars.obj_debris.age % 3) == 0) {
        effect_spawn_at(pos, obj->vars.obj_debris.variant + 0xF0, 8, 0xC);
    }
    if (obj->vars.obj_debris.lifetime <= obj->vars.obj_debris.age || obj_trace_damage(obj, (TraceHit *)pos) == 1) {
        sound_play_at_units(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, pos);
        spawn_effect(pos->x, pos->y, pos->z, 0x80000002);
        if (obj->vars.obj_debris.lifetime <= obj->vars.obj_debris.age) {
            rot = scratch_alloc(8);
            count = rand_a_next() % 4 + 3;
            for (i = 0; i < count; i++) {
                rot->vx = -rand_a_next() / 4;
                rot->vy = rand_a_next();
                rot->vz = 0;
                obj_debris_spawn(obj, pos, rot, 2, obj->vars.obj_debris.variant);
            }
            scratch_top -= 8;
        }
        obj->hit = 1;
    }
    obj->x += obj->vx;
    obj->y += obj->vy;
    obj->z += obj->vz;
    obj->vars.obj_debris.age++;
    obj->vars.obj_debris.damage_scale += 0x155;
    obj->vars.obj_debris.damage_scale = MAX(MIN(obj->vars.obj_debris.damage_scale, 0x1000), 0);
    scratch_top -= 0x10;
}

s32 obj_trace_damage(Object *obj, TraceHit *out);
/* Falls by the vertical speed, drifts by the per-step speeds, and sets hit when obj_trace_damage returns 1. */
void debris_update(Object *obj) {
    Vec3 *scratch = scratch_alloc(0x10);

    obj->vy += 0x1000;
    if (obj_trace_damage(obj, (TraceHit *)scratch) == 1) {
        obj->hit = 1;
    }
    scratch_top -= 0x10;
    obj->x += obj->vx;
    obj->y += obj->vy;
    obj->z += obj->vz;
    obj->vars.obj_debris.age++;
}

/* Traces a line from the object's position to position + velocity; on an object hit damages it (1 returned),
 * on a world hit stores the hit record in out (1 returned). */
s32 obj_trace_damage(Object *obj, TraceHit *out) {
    s32 result = 0;
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to;
    TraceHit *hit;
    s16 target;
    s32 world;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    to = scratch_alloc(0x10);
    to->x = (obj->x + obj->vx) >> 12;
    to->y = (obj->y + obj->vy) >> 12;
    hit = scratch_alloc(0x10);
    target = 0;
    to->z = (obj->z + obj->vz) >> 12;
    set_collide_mode(1);
    world = trace_world(8, obj->vars.obj_debris.trace_mask, from, to, hit);
    if (trace_objects(from, hit, obj->vars.obj_debris.trace_mask, out, &target) == 1) {
        result = 1;
        hit_target_masked(target, 0x10, obj->yaw, (obj->damage * obj->vars.obj_debris.damage_scale * 0x10) >> 16);
    } else if (world == 1) {
        *out = *hit;
        result = 1;
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return result;
}

/* Traces a world query from the object's position to the position plus its velocity; 1 when it hit. */
s32 obj_fall_probe(Object *obj, Vec3 *hit) {
    Vec3 *pos = scratch_alloc(0x10);
    Vec3 *target = scratch_alloc(0x10);
    s32 result;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    target->x = (obj->x + obj->vx) >> 12;
    target->y = (obj->y + obj->vy) >> 12;
    target->z = (obj->z + obj->vz) >> 12;
    result = trace_world(8, obj->vars.obj_debris.trace_mask, pos, target, hit);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return result;
}


void obj_terrain_hit_expire(Object *obj) {
    s32 x;
    s32 y;
    s32 z;

    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    if (obj->hit != 1 && cam_range_check(x, y, z) != 0) {
        if (d_80119E84 == 0 || (obj_hit_damage(obj->index) << 16) > 0) {
            spawn_effect(x, y, z, 0x80000000);
        } else {
            return;
        }
    }
    obj_free(obj);
}



/* Same code as obj_free_outside_area (s05). */
void boss_area_attack_explosion_phase2(Object *obj) {
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    if ((obj->hit == 1) || (cam_range_check(x, y, z) == 0)) {
        obj_free(obj);
    }
}


void func_800C7AB4(void) {
}

/* Adds two sparks at the object: one turned like it, and one whose colour pulses with
 * the cosine of vars.h.unk_252 (red, green, blue at 1, 1/2, 1/4 of the level; never black). */
void falling_draw(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot;
    s32 level;
    s32 blue;
    s32 green;
    s32 red;
    s32 roll;
    s32 pitch;
    s32 model = obj->vars.obj_debris.variant + 0xE0;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    rot = scratch_alloc(8);
    pitch = obj->pitch;
    rot->vx = -pitch;
    rot->vy = obj->yaw;
    roll = (u16)obj->roll;
    rot->vz = roll;
    spark_add(pos->x, pos->y, pos->z, rot->vy, rot->vx, roll, model, 0);
    model = obj->vars.obj_debris.variant + 0xEE;
    level = (cos_table[obj->vars.obj_debris.phase & 0xFFF].value + 0x1000) / 2;
    blue = level / 4;
    green = level / 2;
    red = level >> 5;
    blue >>= 5;
    green >>= 5;
    if ((blue | green | red) == 0) {
        red = 1;
    }
    level = (red << 16) | (green << 8) | blue;
    spark_add(pos->x, pos->y, pos->z, 0, 0, 0, model, level);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void spark_emit_at_obj(Object *obj) {
    Vec3 *pos;
    s32 x, y, z;
    s32 n;
    s32 base;
    s16 value;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    pos = (Vec3 *)scratch_top;
    scratch_top += 0x10;
    __asm__ volatile(""); /* keeps the gp bump here, out of the beqz delay slot */
    base = obj->vars.obj_debris.variant;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    x = pos->x;
    y = pos->y;
    z = pos->z;
    n = SPARK_COUNT;
    list = &spark_list;
    if (n < 0xFF) {
        value = base + 0xE7;
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = 0;
        tail = spark_list_tail;
        spark_list_tail = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
    scratch_top -= 0x10;
}

void falling_init(Object *obj, Object *parent);
void flame_init(Object *obj, Object *parent);
void debris_setup(Object *obj, Object *parent);

/* Spawns an object at the given position (whole units, shifted to 20.12) and rotation, sets its
 * vars.h words and runs the init for kind 0/1/2. Returns 1 when spawned, 0 when obj_new fails or kind is out of range. */
s32 obj_debris_spawn(Object *parent, Vec3 *pos, SVECTOR *rot, s32 kind, s32 value) {
    Object *obj;
    s32 result = 0;

    if (kind >= 0 && kind < 3) {
        obj = obj_new();
        if (obj != NULL) {
            list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
            obj->hit = 0;
            obj_hit_clear(obj->index);
            obj_hit_flag_set(obj->index, 0);
            obj->x = pos->x << 12;
            obj->y = pos->y << 12;
            obj->z = pos->z << 12;
            obj->pitch = rot->vx;
            obj->yaw = rot->vy;
            obj->roll = rot->vz;
            obj->vars.obj_debris.variant = value;
            obj->vars.obj_debris.kind = kind;
            switch (kind) {
            case 0:
                falling_init(obj, parent);
                break;
            case 1:
                flame_init(obj, parent);
                break;
            case 2:
                debris_setup(obj, parent);
                break;
            }
            result = 1;
        }
    }
    return result;
}

void falling_update(Object *obj, ObjHandler *handler);
void falling_draw(Object *obj);
/* Sets up the object (handlers, flags, speed 0x28), gives it a velocity along its yaw/pitch, and passes its
 * position (whole units) to effect_spawn_at through a scratch vector. */
void falling_init(Object *obj, Object *parent) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 vx;
    s32 vy;
    s32 vz;

    vx = 0;
    vy = 0;
    vz = 0;
    obj->handlers[1].fn = falling_update;
    obj->handlers[2].fn = (void *)obj_terrain_hit_expire;
    obj->handlers[3].fn = (void *)falling_draw;
    obj->flags = 0x80;
    obj->vars.obj_debris.trace_mask = 0x18;
    obj->vars.obj_debris.damage_scale = 0x1000;
    obj->speed = 0x28;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.obj_debris.age = 0;
    obj->vars.obj_debris.lifetime = 0;
    obj->vars.obj_debris.phase = 0;
    obj->vars.obj_debris.unused_254 = 0;
    obj->damage = 0;
    angles_to_vector(obj->yaw, -obj->pitch, 0x28, &vx, &vy, &vz);
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    effect_spawn_at(pos, obj->vars.obj_debris.variant + 0xC8, 3, 0x19);
    scratch_top -= 0x10;
}

void flame_update(Object *obj);
void boss_area_attack_explosion_phase2();
void flame_init(Object *obj, Object *parent) {
    s32 vx = 0;
    s32 vy = 0;
    s32 vz = 0;
    s32 rnd;

    obj->handlers[1].fn = flame_update;
    obj->handlers[2].fn = boss_area_attack_explosion_phase2;
    obj->flags = 0x80;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.obj_debris.trace_mask = 0x24;
    obj->vars.obj_debris.age = 0;
    rnd = rand_a_next();
    obj->vars.obj_debris.damage_scale = 0x200;
    obj->damage = 0xC;
    obj->speed = 0x14;
    obj->vars.obj_debris.phase = 0;
    obj->vars.obj_debris.lifetime = rnd % 0x30 + 0x18;

    angles_to_vector(obj->yaw, -obj->pitch, 0x14, &vx, &vy, &vz);
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
}

void boss_area_attack_explosion_phase2();
void spark_emit_at_obj(Object *obj);
void debris_setup(Object *obj, Object *parent) {
    s32 vx = 0;
    s32 vy = 0;
    s32 vz = 0;

    obj->handlers[1].fn = debris_update;
    obj->handlers[2].fn = boss_area_attack_explosion_phase2;
    obj->handlers[3].fn = spark_emit_at_obj;
    obj->flags = 0x80;
    obj->vars.obj_debris.trace_mask = 0x24;
    obj->vars.obj_debris.damage_scale = 0x1000;
    obj->damage = 4;
    obj->speed = 0x10;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.obj_debris.age = 0;
    obj->vars.obj_debris.lifetime = 0;
    obj->vars.obj_debris.phase = 0;
    obj->vars.obj_debris.unused_254 = 0;

    angles_to_vector(obj->yaw, -obj->pitch, 0x10, &vx, &vy, &vz);
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
}
