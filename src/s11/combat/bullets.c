/* bullets: one of s11's own original source files (scripts/objmap.py); part of src/s11/main.c's unit, included there. */

void bullet_update(Object *obj, ObjHandler *handler) {
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s16 target;

    if (flag_get() != 0 || obj->vars.snd.sound != 0) {
        obj_free(obj);
        return;
    }

    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    to[0] = (obj->x + obj->vx) >> 12;
    to[1] = (obj->y + obj->vy) >> 12;
    to[2] = (obj->z + obj->vz) >> 12;

    if (trace_world(8, 0x10, from, to, hit) != 0) {
        obj->vars.snd.sound = 1;
        obj_spawn_ramp_in_out(hit, obj->vars.pair.unk_250);
    } else {
        set_collide_mode(1);
        if (trace_objects(from, to, 0x10, hit, &target) != 0) {
            hit_target_masked(target, 1, atan2(hit[2] - from[2], hit[0] - from[0]), 8);
            obj_spawn_ramp_in_out(hit, obj->vars.pair.unk_250);
            obj->vars.snd.sound = 1;
        }
        set_collide_mode(0);
        obj->z += obj->vz;
        obj->x += obj->vx;
        obj->y += obj->vy;
    }

    if (obj->vars.snd.sound != 0) {
        obj_free(obj);
    }
}

void bullet_update(Object *obj, ObjHandler *handler);
/* Spawns an object at a placement position (whole units) and rotation. */
void obj_spawn_placed(Vec3 *pos, SVECTOR *rot, s32 flag) {
    Object *obj;
    s32 unused[6]; /* stack padding the original's frame has (0x48 bytes) */
    s32 base;
    s32 yaw;
    s32 pitch;
    s32 speed;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = bullet_update;
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
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot->vx;
        obj->yaw = rot->vy;
        obj->roll = rot->vz;
        base = get_model_slot_base();
        yaw = obj->yaw;
        pitch = obj->pitch;
        speed = obj->speed;
        obj->vars.placed.unk_248 = base + 9;
        obj->vars.placed.unused_24C = 0;
        obj->vars.placed.unk_250 = flag;
        angles_to_vector(yaw, pitch, speed, &obj->vx, &obj->vy, &obj->vz);
    }
}

/* Emits a spark at the object's position. The colour word comes from the object's 0x248 value: folded
 * around 0x2000 (above 0x1001), divided by 32, and used as the top byte's level (at least 1) and as the
 * middle and low bytes. The spark's life value is get_model_slot_base() + 0xF. */
void spark_colour_draw(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    s32 value = get_model_slot_base() + 0xF;
    s32 angle = *(s16 *)&obj->vars;
    s32 scale;
    s32 hi;

    if (angle >= 0x1001) {
        angle = 0x2000 - angle;
    }
    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    scale = angle >> 5;
    hi = scale;
    if (scale == 0) {
        hi = 1;
    }
    spark_add(pos.x, pos.y, pos.z, 0, 0, 0, value, (hi << 16) | (scale << 8) | scale);
}

/* Step of the sound-loop object obj_spawn_sound_loop makes: follows its parent (vars.words[2]), aims at
 * the player, spawns placed shots in 0x1001..0x19FF of its timer (0x248), fades the loop in and frees
 * itself past 0x2000 or when the parent's next_state is 0xB. */
void sound_loop_update(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    s32 part_pos[4];
    SVECTOR rot;
    Vec3 own;
    Vec3 *pos_ptr;
    s32 *player;
    s32 yaw;
    s32 pitch;
    Object *parent;
    s32 volume;
    s32 angle;
    s32 dz;

    if (((Object *) obj->vars.sound_loop.target_obj)->next_state == 0xB) {
        sound_stop(obj->vars.sound_loop.sound_handle);
        obj->vars.sound_loop.sound_handle = 0;
        obj_free(obj);
        return;
    }
    solid_part_box(((Object *) obj->vars.sound_loop.target_obj)->solid_id, 6, part_pos, 0);
    parent = ((Object *) obj->vars.sound_loop.target_obj);
    pos.x = parent->x >> 12;
    pos.y = parent->y >> 12;
    pos.z = parent->z >> 12;
    parent = ((Object *) obj->vars.sound_loop.target_obj);
    pos_ptr = &pos;
    angle = parent->pitch;
    rot.vx = -angle;
    rot.vy = parent->yaw;
    rot.vz = parent->roll;
    rot.vy = ((Object *) obj->vars.sound_loop.target_obj)->vars.h.unk_24C;
    pos.y = part_pos[1];
    pos_add_rotated_offset_flipped(pos_ptr, &rot, 0, 0x46, 0x14A);
    obj->x = pos.x << 12;
    obj->y = pos.y << 12;
    obj->z = pos.z << 12;
    player = player_position();
    own.x = obj->x >> 12;
    own.y = obj->y >> 12;
    own.z = obj->z >> 12;
    dz = player[2] - own.z;
    vector_to_angles(player[0] - own.x, player[1] - own.y, dz, &yaw, &pitch);
    obj->pitch = angle_approach(obj->pitch, pitch, 0x20);
    obj->yaw = ((Object *) obj->vars.sound_loop.target_obj)->vars.h.unk_24C;
    obj->roll = 0;
    if ((u16) obj->vars.sound_loop.volume - 0x1001U < 0x9FF) {
        if (obj->vars.sound_loop.unk_24C > 0x1000) {
            angle = obj->pitch;
            rot.vx = -angle;
            rot.vy = obj->yaw;
            rot.vz = obj->roll;
            rot.vy += (s16) (rand_a_next() % 512 - 0x100);
            rot.vx += (s16) (rand_a_next() % 256 - 0x80);
            obj->vars.sound_loop.toggle ^= 1;
            if (obj->vars.sound_loop.toggle) {
                obj_spawn_placed(pos_ptr, &rot, 0);
            } else {
                obj_spawn_placed(pos_ptr, &rot, 1);
            }
            obj->vars.sound_loop.unk_24C = 0;
        }
        obj->vars.sound_loop.unk_24C += 0x800;
    }
    volume = obj->vars.sound_loop.volume;
    if (volume > 0x1000) {
        volume = 0x1000;
    }
    sound_set_volume(obj->vars.sound_loop.sound_handle, (s16) sound_volume_of(0xB14CB14D, volume));
    if (obj->vars.sound_loop.volume > 0x2000) {
        sound_stop(obj->vars.sound_loop.sound_handle);
        obj->vars.sound_loop.sound_handle = 0;
        obj_free(obj);
    }
    obj->vars.sound_loop.volume += 0x1A;
}

void sound_loop_update(Object *obj, ObjHandler *handler);
void obj_spawn_sound_loop(s32 extra, s32 *pos, u16 *angles) {
    Object *obj;
    s32 handle;
    u16 roll;
    s32 unused[6];

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = sound_loop_update;
        obj->unk_17A = 0;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = spark_colour_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_hit_clear(obj->index);
        obj->speed = 0;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = angles[0];
        obj->yaw = angles[1];
        roll = angles[2];
        obj->vars.sound_loop.volume = 0;
        obj->vars.sound_loop.unused_24A = 0;
        obj->vars.sound_loop.unk_24C = 0;
        obj->vars.sound_loop.toggle = 0;
        obj->vars.sound_loop.target_obj = extra;
        obj->roll = roll;
        handle = sound_start(0xB14CB14D, 0x60, 0, 0);
        obj->vars.sound_loop.sound_handle = handle;
        sound_attach(handle, &obj->x, NULL);
    }
}

void trail_draw(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 k, i, m, c, g, b;
    s32 t;
    s32 r;
    s32 colour;
    s32 model = ((TrailObjectVars *)&obj->vars)->model;
    s32 p;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    p = obj->pitch;
    rot[0] = -p;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;

    t = ((TrailObjectVars *)&obj->vars)->t0;
    k = 0x1000 - t;
    r = ((t * 0xC00 + (k << 9)) / 0x1000);
    g = ((t * 0xC00 + (k << 8)) / 0x1000);
    b = ((t * 0x1000 + (k << 10)) / 0x1000) >> 5;
    if (((r >> 5) | (g >> 5) | b) == 0) {
        b = 1;
    }
    colour = (b << 16) | ((g >> 5) << 8) | (r >> 5);
    if (((TrailObjectVars *)&obj->vars)->flag == 0) {
        model = pool_spawn_scaled(model, t, 0x1000, t);
    } else {
        model = pool_spawn_scaled(model, ((TrailObjectVars *)&obj->vars)->t1, ((TrailObjectVars *)&obj->vars)->t1, t);
    }
    spark_add(pos[0], pos[1], pos[2], rot[1], -rot[0], rot[2], model, colour);

    for (i = 1, m = 0x400; i < 4; i++, m += 0x400) {
        k = 0x1000 - m;
        r = ((k * 0xC00 + (i << 19)) / 0x1000);
        g = ((k * 0xC00 + (i << 18)) / 0x1000);
        b = ((k * 0x1000 + (i << 20)) / 0x1000) >> 5;
        if (((r >> 5) | (g >> 5) | b) == 0) {
            b = 1;
        }
        colour = (b << 16) | ((g >> 5) << 8) | (r >> 5);
        c = ((TrailObjectVars *)&obj->vars)->start - i;
        while (c < 0) {
            c += 4;
        }
        pos[0] = ((TrailObject *)obj)->pts[c].x;
        pos[1] = ((TrailObject *)obj)->pts[c].y;
        pos[2] = ((TrailObject *)obj)->pts[c].z;
        spark_add(pos[0], pos[1], pos[2], rot[1], -rot[0], rot[2], model, colour);
    }
}

void trail_record_pos(Object *obj) {
    TrailObj *t = (TrailObj *)obj;
    s32 pos[3];
    s32 next;
    s32 wrapped;

    pos[0] = t->x >> 12;
    pos[1] = t->y >> 12;
    pos[2] = t->z >> 12;

    t->entries[t->index].x = pos[0];
    t->entries[t->index].y = pos[1];
    t->entries[t->index].z = pos[2];

    next = t->index + 1;
    wrapped = next;
    if (next < 0) {
        wrapped = t->index + 4;
    }
    t->index = next - ((wrapped >> 2) * 4);
}

/* Rotate the offset (x, y, z) by the angles in rot (yaw sign reversed) and add the result to pos. */
void pos_add_rotated(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    rotate_xz_twice(rot->vy, -rot->vx, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}

/* Homing missile: while its steering timer runs, turns toward the player;
   moves, traces the world and objects (a beam 0x200 to each side) for a hit,
   then fades its trail out and frees itself. */
void homing_shot_update(Object *obj) {
    TraceVec4 from;
    TraceVec4 to;
    TraceVec4 hit;
    TraceVec4 unused;
    TraceVec4 pos;
    s16 pitch;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 yaw;
    s32 speed;
    s32 aim_yaw;
    s32 aim_pitch;
    Vec3 *player = (Vec3 *)player_position();

    if (obj->vars.burst_obj.unused_250 == 0) {
        if ((s16)obj->vars.part.parent_yaw-- > 0) {
            pos.x = obj->x >> 12;
            pos.y = obj->y >> 12;
            pos.z = obj->z >> 12;
            dz = player->z - pos.z;
            dx = player->x - pos.x;
            dy = player->y - pos.y;
            vector_to_angles(dx, dy, dz, &aim_yaw, &aim_pitch);
            obj->yaw = angle_approach(obj->yaw, aim_yaw, 8);
            pitch = angle_approach(obj->pitch, -aim_pitch, 8);
            yaw = obj->yaw;
            speed = obj->speed;
            obj->pitch = pitch;
            angles_to_vector(yaw, pitch, speed, &obj->vx, &obj->vy, &obj->vz);
        }
        if (obj->vars.burst_obj.trail_accum > 0x1000) {
            trail_record_pos(obj);
            obj->vars.burst_obj.trail_accum = 0;
        }
        from.x = obj->x >> 12;
        from.y = obj->y >> 12;
        from.z = obj->z >> 12;
        to.x = (obj->x + obj->vx) >> 12;
        to.y = (obj->y + obj->vy) >> 12;
        to.z = (obj->z + obj->vz) >> 12;
        if (trace_world(8, 0x10, &from, &to, &hit)) {
            obj->vars.burst_obj.unused_250 = 1;
        } else {
            TraceVec4 left;
            TraceVec4 right;
            s16 rot[3];
            s16 target;
            s32 obj_pitch;

            set_collide_mode(1);
            obj_pitch = obj->pitch;
            rot[0] = -obj_pitch;
            rot[1] = obj->yaw;
            rot[2] = obj->roll;
            left = from;
            right = to;
            pos_add_rotated((Vec3 *)&left, (SVECTOR *)rot, 0x200, 0, 0);
            pos_add_rotated((Vec3 *)&right, (SVECTOR *)rot, -0x200, 0, 0);
            if (trace_objects(&from, &to, 0x10, &hit, &target) ||
                trace_objects(&left, &right, 0x10, &hit, &target)) {
                hit_target_masked(target, 1, atan2(hit.z - from.z, hit.x - from.x), 0xC);
                obj->vars.burst_obj.unused_250 = 1;
            }
            set_collide_mode(0);
            obj->z += obj->vz;
            obj->x += obj->vx;
            obj->y += obj->vy;
        }
    }
    if (obj->vars.burst_obj.unused_250 != 0) {
        if ((s16)obj->vars.burst_obj.trail_fade > 0) {
            if (obj->vars.burst_obj.trail_accum > 0x1000) {
                trail_record_pos(obj);
                obj->vars.burst_obj.trail_accum = 0;
            }
            obj->vars.burst_obj.trail_fade -= 0x126;
        } else {
            obj_free(obj);
        }
    } else {
        if ((s16)obj->vars.burst_obj.trail_fade < 0x1000) {
            obj->vars.burst_obj.trail_fade += 0x31;
        }
        obj->vars.burst_obj.unk_25A = obj->vars.burst_obj.trail_fade;
    }
    obj->vars.burst_obj.trail_accum += 0x1000;
    if (obj->speed < 0x3C) {
        obj->speed += 2;
    }
}

void homing_shot_update(Object *obj);
void trail_draw(Object *obj);
void burst_obj_spawn(s32 kind, Vec3 *pos, SVECTOR *rot) {
    Object *obj;
    s32 unused[6];
    s32 i;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = homing_shot_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = trail_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_set_flags(obj, 0x80);
        obj->unk_17A = 0;
        obj_hit_clear(obj->index);
        obj->speed = 0;
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot->vx;
        obj->yaw = rot->vy;
        obj->roll = rot->vz;
        obj->vars.burst_obj.unk_248 = kind + 0xE7;
        obj->vars.burst_obj.unused_24A = 10;
        obj->vars.burst_obj.unused_24C = 60;
        obj->vars.burst_obj.unused_250 = 0;
        obj->vars.enemy.sound_channel[0] = 0;
        obj->vars.enemy.sound_channel[1] = 0;
        obj->vars.burst_obj.trail_fade = 0;
        obj->vars.burst_obj.unk_25A = 0;
        for (i = 0; i < 4; i++) {
            ((PosSample *)&obj->vars.burst_obj.trail_positions)[i].x = pos->x;
            ((PosSample *)&obj->vars.burst_obj.trail_positions)[i].y = pos->y;
            ((PosSample *)&obj->vars.burst_obj.trail_positions)[i].z = pos->z;
        }
    }
}

/* Rotate the offset (x, y, z) by the angles in rot (yaw sign reversed) and add the result to pos. */
void pos_add_rotated_b(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    rotate_xz_twice(rot->vy, -rot->vx, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}

static inline void spark_add_head_s(s32 x, s32 y, s32 z, s32 ry, s32 rx, s16 rz, s32 value, s32 colour) {
    s32 n = spark_count;
    SparkList *list;
    SparkRec *s;
    u8 *tail;

    list = &spark_list;
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
/* Draw handler: a spark at the object turned around (yaw + 0x800), then one 100 units ahead of it. */
void spark_tip_draw(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    Vec3 *p;
    SVECTOR rot;
    s32 value;
    s32 tip_value;
    s32 pitch;
    s32 yaw;
    s16 roll;
    s32 unused[2];

    value = obj->vars.typed.kind;
    tip_value = get_model_slot_base() + 0xE;
    p = &pos;
    p->x = obj->x >> 12;
    p->y = obj->y >> 12;
    p->z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    yaw = obj->yaw;
    rot.vy = yaw;
    roll = obj->roll;
    rot.vz = roll;
    spark_add_head_s(p->x, p->y, p->z, yaw + 0x800, rot.vx, roll, value, 0);
    pos_add_rotated_b(p, &rot, 0, 0, -100);
    spark_add_head(&spark_list, pos.x, pos.y, pos.z, 0, 0, 0, tip_value, 0);
}

void homing_seek_update(Object *obj, ObjHandler *handler) {
    s32 *target = player_position();
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s32 pad[3];
    s32 aim[3];
    s32 yaw, pitch;
    s16 hit_target;
    s32 tz;
    s16 new_pitch;
    s32 cur_yaw, speed;

    if (obj->vars.snd.sound == 0) {
        if (obj->vars.typed.seek_timer-- > 0) {
            aim[0] = obj->x >> 12;
            aim[1] = obj->y >> 12;
            aim[2] = obj->z >> 12;
            tz = target[2];
            vector_to_angles(target[0] - aim[0], target[1] - aim[1], tz - aim[2], &yaw, &pitch);
            obj->yaw = angle_approach(obj->yaw, yaw, 8);
            new_pitch = angle_approach(obj->pitch, -pitch, 8);
            cur_yaw = obj->yaw;
            speed = obj->speed;
            obj->pitch = new_pitch;
            angles_to_vector(cur_yaw, new_pitch, speed,&obj->vx, &obj->vy, &obj->vz);
        }
        from[0] = obj->x >> 12;
        from[1] = obj->y >> 12;
        from[2] = obj->z >> 12;
        to[0] = (obj->x + obj->vx) >> 12;
        to[1] = (obj->y + obj->vy) >> 12;
        to[2] = (obj->z + obj->vz) >> 12;
        if (obj_hit_damage(obj->index) > 0) {
            spawn_effect(from[0], from[1], from[2], 0x80000000);
            obj->vars.snd.sound = 1;
        } else if (trace_world(8, 0x10, from, to, hit)) {
            obj->vars.snd.sound = 1;
            spawn_effect(hit[0], hit[1], hit[2], 0);
        } else {
            set_collide_mode(1);
            if (trace_objects(from, to, 0x10, hit, &hit_target)) {
                hit_target_masked(hit_target, 1, atan2(hit[2] - from[2], hit[0] - from[0]), 10);
                spawn_effect(hit[0], hit[1], hit[2], 0);
                obj->vars.snd.sound = 1;
            }
            set_collide_mode(0);
            if ((obj->vars.fly.phase ^= 1) == 0) {
                Vec3 fx;
                s32 id = get_model_slot_base();
                fx.x = obj->x >> 12;
                fx.y = obj->y >> 12;
                fx.z = obj->z >> 12;
                effect_spawn_at(&fx, id + 0x20, 10, 0x10);
            }
            obj->z += obj->vz;
            obj->x += obj->vx;
            obj->y += obj->vy;
            if (obj->speed < 0x32) {
                obj->speed++;
            }
        }
        if (obj->vars.snd.sound != 0) {
            obj_free(obj);
        }
    } else {
        obj_free(obj);
    }
}

void homing_seek_update(Object *obj, ObjHandler *handler);
void spark_tip_draw(Object *obj, ObjHandler *handler);
void obj_spawn_typed(s32 kind, s32 *pos, u16 *angles) {
    Object *obj;
    s32 frame_pad[6];

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = homing_seek_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = spark_tip_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_set_flags(obj, 0x80);
        obj->unk_17A = 0;
        obj_hit_clear(obj->index);
        obj->speed = 0;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = angles[0];
        obj->yaw = angles[1];
        obj->roll = angles[2];
        obj->vars.typed.kind = kind;
        obj->vars.typed.seek_timer = 0x50;
        obj->vars.typed.unused_24C = 0;
        obj->vars.typed.unused_250 = 0;
        obj->vars.typed.unused_252 = 0;
    }
}

/* Draws a line of sparks along the object's heading: unk_256 steps of 0x240 plus a last one, coloured by unk_254. */
void spark_heading_draw(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    s16 rot[3];
    s32 vx, vy, vz;
    s32 value;
    s32 size;
    s32 colour;
    s32 scale;
    s32 shade;
    s32 inv;
    s32 i;

    value = (s16)obj->vars.h.unk_24A;
    if (obj->vars.enemy.unk_25C == 1) {
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot[1] = obj->yaw;
        rot[0] = obj->pitch;
        rot[2] = obj->roll;
        inv = 0x1000 - obj->vars.h.unk_254;
        scale = ((obj->vars.h.unk_254 * 0x1C00 + inv * 0x200) / 0x1000) >> 5;
        shade = obj->vars.h.unk_254 >> 5;
        if ((shade | scale) == 0) {
            scale = 1;
        }
        vz = 0x240;
        vx = 0;
        vy = 0;
        colour = (scale << 16) | (shade << 8) | shade;
        rotate_xz_twice(rot[1], rot[0], &vx, &vy, &vz);
        if (obj->vars.enemy.unk_25E == 0) {
            size = obj->vars.h.unk_254 + 0x1000;
        } else {
            size = obj->vars.h.unk_254 / 2;
        }
        value = pool_spawn_scaled(value, size, size, 0x1000);
        for (i = 0; i < (s16)obj->vars.h.unk_256; i++) {
            spark_add(pos[0], pos[1], pos[2], rot[1] + 0x800, -rot[0], rot[2], value, colour);
            pos[0] += vx;
            pos[1] += vy;
            pos[2] += vz;
        }
        value = pool_spawn_scaled(value, size, size, (s16)obj->vars.h.unk_258);
        spark_add(pos[0], pos[1], pos[2], rot[1] + 0x800, -rot[0], rot[2], value, colour);
    }
}

/* Distance from `from` to `to`, stored as whole units (/576) and a 12-bit fraction. */
void obj_store_distance(Object *obj, Vec3 *from, Vec3 *to) {
    s32 dist;

    dist = isqrt(length_sq(from->x - to->x, from->y - to->y, from->z - to->z));
    obj->vars.h.unk_256 = dist / 576;
    obj->vars.h.unk_258 = ((dist % 576) << 12) / 576;
}

void enemy_tracer_update(Object *obj, ObjHandler *handler) {
    s32 from[4];
    Vec4Words seg[2]; /* [0] trace end, [1] hit point */
    s16 target;
    s16 hit_obj = 0;
    s32 *vel;
    s32 yaw, pitch, speed;

    if (obj->vars.tracer.spinning == 1) {
        if (obj->vars.tracer.reverse == 0) {
            obj->yaw += 0x18;
        } else {
            obj->yaw -= 0x18;
        }
        if ((obj->vars.tracer.phase ^= 1) == 0) {
            obj->vars.tracer.jitter_a = obj->vars.tracer.base_a + rand_a_next() % 5;
        }
        if ((s16)obj->vars.tracer.phase == 0) {
            obj->vars.tracer.jitter_b = obj->vars.tracer.base_b + rand_a_next() % 4;
        }
    }
    vel = &obj->vx;
    yaw = obj->yaw;
    pitch = obj->pitch;
    speed = obj->speed;
    angles_to_vector(yaw, pitch, speed, vel, &obj->vy, &obj->vz);
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    seg[0].x = (obj->x + obj->vx) >> 12;
    seg[0].y = (obj->y + obj->vy) >> 12;
    seg[0].z = (obj->z + obj->vz) >> 12;
    seg[1] = seg[0];
    if (obj->vars.tracer.hit == 0) {
        if ((obj->vars.tracer.phase ^= 1) == 0) {
            obj->vars.tracer.jitter_a = obj->vars.tracer.base_a + rand_a_next() % 5;
        }
        if ((s16)obj->vars.tracer.phase == 0) {
            obj->vars.tracer.jitter_b = obj->vars.tracer.base_b + rand_a_next() % 4;
        }
        set_collide_mode(1);
        if (trace_objects(from, &seg[0], 0x20, &seg[1], &target)) {
            hit_target_masked(target, 1, atan2(seg[1].z - from[2], seg[1].x - from[0]), 0x12);
            do { } while (0);
            obj->vars.tracer.hit = 1;
            do { } while (0);
            obj_store_distance(obj, (Vec3 *)&seg[1], (Vec3 *)from);
            hit_obj = 1;
            set_collide_mode(0);
        } else {
            set_collide_mode(0);
        }
        if (hit_obj != 1) {
            if (trace_world(8, 0x20, from, &seg[0], &seg[1])) {
                obj->vars.tracer.hit = 1;
                obj_store_distance(obj, (Vec3 *)&seg[1], (Vec3 *)from);
            } else {
                obj->vars.tracer.miss_a = 0x11;
                obj->vars.tracer.miss_b = 0x1000;
            }
        }
    }
    if (obj->vars.tracer.life < 0) {
        obj_free(obj);
    }
    obj->vars.tracer.flag = 1;
    obj->vars.tracer.life -= 0x80;
}

void enemy_tracer_update(Object *obj, ObjHandler *handler);
void spark_heading_draw(Object *obj, ObjHandler *handler);
/* Spawns an enemy at pos (x, y, z; 20.12 after the shift) with rot (pitch, yaw, roll).
 * base offsets the four random table values; param goes to vars.enemy.unk_25E. */
void enemy_spawn(s32 base, s32 param, s32 *pos, u16 *rot) {
    Object *obj;
    s32 rnd_a;
    s32 rnd_b;
    s32 unused[6]; /* keeps the 0x40 frame of the original */

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = enemy_tracer_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = spark_heading_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_set_flags(obj, 0x80);
        obj_hit_clear(obj->index);
        obj->speed = 0x2710;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        obj->vars.h.unk_248 = base + 0xBB;
        rnd_a = rand_a_next();
        obj->vars.h.unk_24C = base + 0xB6;
        obj->vars.enemy.unk_250 = 0;
        obj->vars.h.unk_24A = base + (rnd_a % 5 + 0xBB);
        rnd_b = rand_a_next() % 4;
        obj->vars.h.unk_24E = base + (rnd_b + 0xB6);
        obj->vars.enemy.sound_channel[0] = 0x1000;
        obj->vars.enemy.sound_channel[1] = 0;
        obj->vars.h.unk_258 = 0;
        obj->vars.h.unk_25A = 0;
        obj->vars.enemy.unk_25C = 0;
        obj->vars.enemy.unk_25E = param;
        *(s16 *)obj->vars.enemy.unk_260 = rand_a_next() % 2;
    }
}

/* Rotate the offset (x, y, z) by the angles in rot (yaw sign reversed) and add the result to pos. */
void pos_add_rotated_c(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    rotate_xz_twice(rot->vy, -rot->vx, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}

void pos_add_rotated_c(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z);
void enemy_spawn(s32 base, s32 param, s32 *pos, u16 *rot);
void obj_spawn_enemy_burst(Object *obj) {
    Vec3 pos;
    SVECTOR rot;
    s32 i;
    s32 r;
    s32 q;
    s32 d;
    u16 vx;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    rot.vy = obj->vars.part.parent_yaw;
    rot.vx = obj->pitch;
    rot.vz = obj->roll;
    pos_add_rotated_c(&pos, &rot, -0x12C, -0x15E, 0x190);
    i = 0;
    do {
        r = rand_a_next();
        q = r / 0x800;
        d = r - (q << 11);
        d -= 0x400;
        rot.vy = obj->vars.part.parent_yaw + d;
        vx = obj->pitch + (rand_a_next() % 1536 - 0x300);
        rot.vx = vx;
        if (obj->vars.trace.aim_yaw == 0) {
            vx = vx + 0x400;
        } else {
            vx = vx - 0x400;
        }
        rot.vx = vx;
        rot.vz = obj->roll;
        i++;
        enemy_spawn(model_slot_pchr(*(s32 *)obj->asset), 1, (s32 *)&pos, (u16 *)&rot);
    } while (i < 4);
    sound_play_at_units(SND_PAIR(SND_ENEMY_BURST_SPAWN | SND_GROUP(1), SND_ENEMY_BURST_SPAWN_ALT | SND_GROUP(1)), 0x60, 0x3C, &pos);
}

/* Spawns seven enemies from a point offset in front of the object, each with a
 * random yaw/pitch spread of +-256 around the object's, then one more facing
 * final_rot, and plays a sound. */
void spark_trail_burst(Object *obj, SVECTOR *final_rot) {
    Vec3 pos;
    SVECTOR rot;
    s32 i;
    s32 r;
    s32 spread;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    rot.vy = obj->vars.part.parent_yaw;
    rot.vx = obj->pitch;
    rot.vz = obj->roll;
    pos_add_rotated_c(&pos, &rot, -0x12C, -0x15E, 0x190);
    for (i = 0; i < 7; i++) {
        r = rand_a_next();
        spread = r - r / 512 * 512 - 0x100;
        rot.vy = obj->vars.part.parent_yaw + spread;
        r = rand_a_next();
        spread = r - r / 512 * 512 - 0x100;
        rot.vx = obj->pitch + spread;
        rot.vz = obj->roll;
        enemy_spawn(model_slot_pchr(*(s32 *)obj->asset), 0, (s32 *)&pos, (u16 *)&rot);
    }
    enemy_spawn(model_slot_pchr(*(s32 *)obj->asset), 0, (s32 *)&pos, (u16 *)final_rot);
    sound_play(SND_PAIR(SND_SPARK_TRAIL_FIRE | SND_GROUP(2), SND_SPARK_BURST | SND_GROUP(2)), 0x60, 0x3F, 0x3C);
}

void spark_trail_draw(Object *obj) {
    Vec3 pos;
    s16 phase;
    s32 angle = obj->vars.trace.aim_yaw;
    s32 inv, green, blue, colour, t;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    phase = obj->vars.spark_trail.color_phase;
    inv = 0x1000 - phase;
    t = phase * 0x1C00 + (inv << 9);
    blue = t >> 17;
    if (t < 0) {
        blue = (t + 0xFFF) >> 17;
    }
    green = phase >> 5;
    if ((green | blue) == 0) {
        blue = 1;
    }
    colour = (blue << 16) | (green << 8) | green;
    angle = pool_spawn_scaled(angle, phase + 0x1000, phase + 0x1000, 0x1000);
    spark_add(pos.x, pos.y, pos.z, 0, 0, 0, angle, colour);
}

void obj_spawn_enemy_burst(Object *obj);
void spark_trail_burst(Object *obj, SVECTOR *final_rot);
void spark_trail_update(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    SVECTOR rot;
    s32 yaw;
    s32 pitch;
    s32 rnd;
    s32 rnd_mod;

    if (obj->vars.pushed.source->next_state == 0xB) {
        obj_free(obj);
    }
    /* random offset: rnd % 4, signed */
    rnd = rand_a_next();
    rnd_mod = rnd;
    if (rnd < 0) {
        rnd_mod = rnd + 3;
    }
    obj->vars.spark_trail.unk_24A = obj->vars.spark_trail.unk_248 + (rnd - ((rnd_mod >> 2) * 4));

    {
        Object *source = obj->vars.pushed.source;

        pos.x = source->x >> 12;
        pos.y = source->y >> 12;
        pos.z = source->z >> 12;
    }
    rot.vy = obj->vars.pushed.source->vars.h.unk_24C;
    rot.vx = obj->vars.pushed.source->pitch;
    rot.vz = obj->vars.pushed.source->roll;
    pos_add_rotated_c(&pos, &rot, -0x12C, -0x15E, 0x190);
    obj->x = pos.x << 12;
    obj->y = pos.y << 12;
    obj->z = pos.z << 12;

    if ((s16) obj->vars.spark_trail.progress < 0x1000) {
        Vec3 self_pos;
        s32 *player;
        s32 dx;
        s32 dy;
        s32 dz;

        if (obj->vars.spark_trail.burst_accum >= 0x1001) {
            obj_spawn_enemy_burst(obj->vars.pushed.source);
            obj->vars.spark_trail.burst_accum = 0;
        }
        obj->vars.spark_trail.color_phase = obj->vars.spark_trail.progress;
        player = player_position();
        self_pos.x = obj->x >> 12;
        self_pos.y = obj->y >> 12;
        self_pos.z = obj->z >> 12;
        dz = player[2] - self_pos.z;
        dx = player[0] - self_pos.x;
        dy = player[1] - self_pos.y;
        vector_to_angles(dx, dy, dz, &yaw, &pitch);
        obj->yaw = yaw;
        obj->pitch = -pitch;
    }
    if ((s16) obj->vars.spark_trail.progress >= 0x1801) {
        SVECTOR angles;

        angles.vy = obj->yaw;
        angles.vx = obj->pitch;
        angles.vz = obj->roll;
        spark_trail_burst(obj->vars.pushed.source, &angles);
        obj_free(obj);
    }
    obj->vars.spark_trail.burst_accum += 0x200;
    obj->vars.spark_trail.progress += 0x1A;
}

void spark_trail_update(Object *obj, ObjHandler *handler);
void spark_trail_spawn(Object *parent, Vec3 *pos, SVECTOR *rot) {
    Object *obj;
    s32 frame_pad[6]; /* unused; the original's 0x40-byte frame needs it */

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = spark_trail_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) spark_trail_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_set_flags(obj, 0x80);
        obj_hit_clear(obj->index);
        obj->unk_17A = 0;
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot->vx;
        obj->yaw = rot->vy;
        obj->roll = rot->vz;
        obj->vars.spark_trail.unk_248 = model_slot_pchr(*(s32 *) parent->asset) + 0xB6;
        obj->vars.spark_trail.unk_24A = model_slot_pchr(*(s32 *) parent->asset) + 0xB6;
        obj->vars.spark_trail.progress = 0;
        obj->vars.spark_trail.burst_accum = 0;
        obj->vars.spark_trail.unused_250 = 0;
        obj->vars.spark_trail.color_phase = 0;
        obj->vars.spark_trail.origin_x = pos->x;
        obj->vars.spark_trail.origin_y = pos->y;
        obj->vars.spark_trail.origin_z = pos->z;
        *(s16 *) &obj->vars.spark_trail.rot_x = rot->vx;
        obj->vars.enemy.unk_266 = rot->vy;
        *(s16 *) &obj->vars.spark_trail.rot_z = rot->vz;
        obj->vars.spark_trail.parent = (s32) parent;
    }
}


void script_read_speed(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->speed = *cursor;
}


/* Same code as func_800BC7AC (s01). */
void script_read_state(Object *obj) {
    obj->next_state = obj_read_u16(obj);
}

/* Same code as func_800BC7C8 (s01). */
void func_800C6D68(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void script_jump_if_near_player(Object *obj) {
    s32 *player;
    s32 dist;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 half;
    s16 *cursor;
    s32 threshold;
    s32 index;

    player = player_position();
    half = (s16) obj->height / 2;
    dx = player[0] - (obj->x >> 12);
    dy = player[1] - ((obj->y >> 12) - half);
    dz = player[2] - (obj->z >> 12);
    dist = (s16) isqrt(length_sq(dx, dy, dz));

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < dist) {
        return;
    }
    obj->script.pc = ((s16 **)obj->script.data)[index];
}

void spark_burst_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}


/* Rotate the offset (x, y, z) by the angles in rot and add the result to pos. */
void pos_add_vec3_rotated(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    vec3_rotate(rot->vy, rot->vx, rot->vz, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}


void obj_aim_and_turn(Object *obj, void *aim_slot, s16 aim_step, s16 yaw_step);
/* Steers the object toward the player: flies its yaw/speed to a step (dx, dz), then
 * eases its pitch toward the player's pitch when that lies outside 0x140..0x140+0xD80. */
void obj_steer_to_player(Object *obj) {
    s32 dx;
    s32 dz;
    s32 yaw;
    s32 pitch;
    s32 *pos;
    s32 ex;
    s32 ey;
    s32 ez;

    dx = 0;
    dz = 0;
    obj->unk_1B7 = 0;
    obj_aim_and_turn(obj, &obj->vars.snd.sound, 0x18, 0xC);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    pos = player_position();
    ez = pos[2] - (obj->z >> 12);
    ex = pos[0] - (obj->x >> 12);
    ey = pos[1] - (obj->y >> 12);
    vector_to_angles(ex, ey, ez, &yaw, &pitch);
    if ((u32)(pitch - 0x140) >= 0xD81U) {
        obj->pitch = angle_approach(obj->pitch, pitch, 8);
    }
    obj_step_axes_toward(obj, dz, dx);
}

void obj_chase_player(Object *obj) {
    s32 offset;

    offset = cam_pos_y >> 12;
    obj_steer_to_player(obj);
    obj_set_fall_speed(obj, 2, offset - 0x5AA);
}

void obj_steer_to_player(Object *obj);
void obj_set_fall_speed(Object *obj, s32 speed, s32 target);
/* Decays the value at vars.h.unk_250 toward zero by 0x80 per call, then
 * steers obj toward a target derived from cam_pos_y. */
void obj_steer_decay_update(Object *obj) {
    s32 base;
    s16 level;

    base = cam_pos_y >> 12;
    obj_steer_to_player(obj);
    level = *(s16 *)&obj->vars.damage_record.steer_level;
    if (level > 0) {
        *(s16 *)&obj->vars.damage_record.steer_level = level - 0x80;
    }
    obj_set_fall_speed(obj, 2, base - 0x1C2);
}

void obj_muzzle_fx_spawn(Object *obj);
void obj_steer_fire_update(Object *obj) {
    s32 target;

    target = (cam_pos_y >> 12) - 0x12C;
    obj_steer_to_player(obj);
    if ((s16)obj->vars.damage_record.steer_level >= 0x1001) {
        if (obj->vars.damage_record.unk_252 >= 0x1001) {
            obj_muzzle_fx_spawn(obj);
            obj->vars.damage_record.unk_252 = 0;
        }
        obj->vars.damage_record.unk_252 += 0x100;
    }
    obj_set_fall_speed(obj, 2, target + 0x32);
    obj->vars.damage_record.steer_level += 0x80;
    if ((s16)obj->vars.damage_record.steer_level >= 0x1001) {
        obj->vars.damage_record.steer_level = 0x1001;
    }
}

void obj_eject_fx(Object *obj);
void obj_steer_spawn_update(SteerSpawnObject *obj) {
    s32 cam = cam_pos_y >> 12;
    s16 unused;
    s16 v;

    obj_steer_to_player((Object *)obj);
    if (obj->b > 0x1000) {
        obj_eject_fx((Object *)obj);
        obj->b = 0;
    }
    obj->b += 0x40;
    v = obj->a;
    if (v > 0) {
        obj->a = v - 0x80;
    }
    obj_set_fall_speed((Object *)obj, 2, cam - 0x15E);
}

void obj_hover_update(Object *obj) {
    s32 dz = 0;
    s32 dx = 0;
    s32 speed = 0;

    if (*(u8 *)&obj->unk_1B7 == 0) {
        if (obj->roll > 0) {
            obj->yaw += 4;
            obj->vars.damage_record.saved_yaw += 6;
        } else {
            obj->yaw -= 4;
            obj->vars.damage_record.saved_yaw -= 6;
        }
        fly_move(obj->yaw, obj->speed, &dz, &dx);
        obj_step_axes_toward(obj, dx, dz);
        obj->vy = 0x8000;
        return;
    }
    fly_move(obj->yaw, speed, &dz, &dx);
    obj_step_axes_toward(obj, dx, dz);
    obj->vy = 0;
}

void obj_bob_update(Object *obj, ObjHandler *handler) {
    s32 sin_val;

    obj->vz = 0;
    sin_val = *(s16 *)((u8 *)rcossin_tbl + ((obj->vars.damage_record.bob_phase & 0xFFF) << 2));
    obj->vx = 0;
    obj_script_step(obj, handler);
    obj_lean_into_turn(obj, &obj->vars.enemy.unk_24C[2], 4, 0x100);
    sin_val <<= 2;
    if (((s32) obj->y >> 0xC) < -0x5DC) {
        obj->y = -0x5DC000;
    }
    if (obj->next_state != 0) {
        obj->vy += sin_val;
    }
    obj->vars.damage_record.bob_phase = (u16) obj->vars.damage_record.bob_phase + 0x20;
    obj->vars.damage_record.unk_24A ^= 1;
    meter_set((s32) obj->health, (s32) obj->vars.enemy.sound_channel[1]);
}

static inline void spark_add_c7360_list(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    s32 n = SPARK_COUNT;
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
static inline void spark_add_c7360_head(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    SparkList *head;
    s32 n = SPARK_COUNT;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        head = list;
        __asm__("" : "=r"(head) : "0"(list));
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = head->tail[0];
        head->tail[0] = &s->next;
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
static inline void obj_pos_rot_c7360(Object *obj, Vec3 *pos, SVECTOR *rot) {
    s32 pitch;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    pitch = obj->pitch;
    rot->vx = -pitch;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    rot->vy = obj->vars.damage_record.saved_yaw;
}
static inline void obj_aim_c7360(Object *obj, Vec3 *pos, SVECTOR *aim) {
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    aim->vx = obj->width;
    aim->vy = obj->height;
    aim->vz = obj->unk_1E8[0];
    aim_marker_draw(2, aim, pos, 0);
}
void damage_record_draw(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    SVECTOR rot;
    SVECTOR aim;
    Vec3 pos2;
    SVECTOR rot2;
    register s32 value asm("$16");
    s32 colour;
    s32 level;
    s32 high;
    s32 low;
    s32 scale;
    s32 model;
    s32 colour2;
    s32 inv;
    SparkList *list;
    s32 depth;

    obj_pos_rot_c7360(obj, &pos, &rot);
    if (test_bit(obj->flags, 6)) {
        value = obj->type.unk_0E;
        value += model_slot_pchr(*(s32 *)obj->asset);
    } else {
        value = obj_keyframe_value(obj, 0);
    }
    colour = 0;
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    }
    list = &spark_list;
    spark_add_c7360_head(list, pos.x, pos.y, pos.z, rot.vy, rot.vx, rot.vz, value, colour);
    if (obj->next_state != 4) {
        depth = 0x17C;
        model = get_model_slot_base() + 0xF;
        level = (s16)obj->vars.damage_record.steer_level;
        scale = level / 2;
        inv = 0x1000 - level;
        high = (level * 0x1C00 + inv * 0x200) / 0x1000 >> 5;
        low = level >> 5;
        if ((low | high) == 0) {
            high = 1;
        }
        colour2 = (high << 16) | (low << 8) | low;
        model = pool_spawn_scaled(model, scale, scale, 0x1000);
        obj_pos_rot_c7360(obj, &pos2, &rot2);
        pos_add_vec3_rotated(&pos2, &rot2, 0x19, -0x32, depth);
        spark_add_c7360_list(list, pos2.x, pos2.y, pos2.z, 0, 0, 0, model, colour2);
        obj_pos_rot_c7360(obj, &pos2, &rot2);
        pos_add_vec3_rotated(&pos2, &rot2, -0x19, -0x32, depth);
        spark_add_c7360_list(list, pos2.x, pos2.y, pos2.z, 0, 0, 0, model, colour2);
    }
    obj_aim_c7360(obj, &pos, &aim);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

/* Random sparks around the object's position, one burst per frame.
 * Returns 0 once the object's timer runs out, 1 otherwise. */
s32 obj_spark_burst_update(Object *obj) {
    s32 pos[3];
    s16 saved_rot[3];
    s32 spread_x;
    s32 spread_y;
    s32 spread_z;
    s32 timer;
    s32 pitch;
    s32 effect_type;

    spread_x = rand_a_next() % 512;
    spread_y = rand_a_next() % 256;
    spread_z = rand_a_next() % 512;
    flag_set();
    meter_set_mode(0);
    set_d_801202C8(0);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    saved_rot[0] = -pitch;
    saved_rot[1] = obj->yaw;
    saved_rot[2] = obj->roll;
    saved_rot[1] = obj->vars.damage_record.saved_yaw;
    obj->next_state = 4;
    obj->unk_17A = 0;
    if ((s16)obj->vars.damage_record.timer == 0xF0) {
        spawn_effect(pos[0] + spread_x, pos[1] - spread_y, pos[2] + spread_z, 0x80007F01);
        spawn_effect(pos[0] - spread_x, pos[1] - spread_y, pos[2] - spread_z, 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0x80007F00);
        spawn_effect(pos[0], pos[1] - 0x300, pos[2], 0x80000000);
        spawn_effect(pos[0], pos[1] - 0x380, pos[2], 0x80007F02);
    }
    if (rand_a_next() % 5 == 0) {
        effect_type = 0x80000000;
        if (obj->vars.damage_record.unk_24A == 0) {
            effect_type = 0x80007F00;
            spawn_effect(pos[0] + spread_x, pos[1] - spread_y, pos[2] + spread_z, effect_type);
        } else {
            spawn_effect(pos[0] - spread_x, pos[1] - spread_y, pos[2] - spread_z, effect_type);
        }
    }
    obj->vars.damage_record.timer = (u16)obj->vars.damage_record.timer - 1;
    timer = (s16)obj->vars.damage_record.timer;
    if (timer < 0 || (timer < 0x78 && obj->unk_1B7 != 0)) {
        sound_stop(obj->vars.chaser.target_x);
        obj->vars.chaser.target_x = 0;
        obj->yaw = obj->vars.damage_record.saved_yaw;
        obj->pitch = -obj->pitch;
        obj_replace_with_copy(obj);
        return 0;
    }
    return 1;
}

void damage_record_draw(Object *obj, ObjHandler *handler);
extern s16 damage_record_script[];
extern s16 D_8011AEE4[];
extern s16 *damage_record_script_data[];
extern s16 *D_8011AFF4;
extern ScriptCallEntry D_8011AFF8[];
extern StateEntry D_8011B020[];
s32 damage_record_spawn(DamageRecord *rec) {
    Object *obj;
    s32 snd;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[0].fn = (void *) spark_burst_phase0;
    obj->handlers[1].fn = obj_bob_update;
    obj->handlers[2].fn = obj_state_run;
    obj->handlers[3].fn = (void *) damage_record_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) &obj_spark_burst_update;
    obj->kind = rec->sub;
    obj->asset = D_8011A6EC;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = D_8011AFF8;
    obj->state_table = D_8011B020;
    script_start((Script *) obj, damage_record_script, (s32) D_8011AEE4);
    obj->script.data = damage_record_script_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_8011AFF4;
    obj_init_from_place(obj, (Placement *) rec, 0x37);
    obj->speed = 10;
    obj_set_part_bounds(obj, 0xC1, 0x1000);
    obj->vars.damage_record.timer = 0xF0;
    obj->vars.damage_record.bob_phase = 0;
    obj->vars.damage_record.unk_24A = 0;
    obj->vars.damage_record.steer_level = 0;
    obj->vars.damage_record.unk_252 = 0;
    obj->vars.damage_record.unused_254 = 0;
    obj->vars.damage_record.saved_yaw = obj->yaw;
    obj->vars.damage_record.unk_24E = obj->yaw;
    obj->vars.damage_record.max_health = obj->health;
    obj->health = 5000;
    obj_hit_flag_set(obj->index, 0x80);
    meter_set(obj->health, obj->vars.damage_record.max_health);
    snd = sound_start(SND_DAMAGE_RECORD_ENGINE_LOOP | SND_HELD | SND_GROUP(2), 0x60, 0, 0);
    obj->vars.damage_record.sound_id = snd;
    sound_attach(snd, &obj->x, NULL);
    return 1;
}

void obj_spawn_placed(Vec3 *pos, SVECTOR *rot, s32 flag);
void obj_muzzle_fx_spawn(Object *obj) {
    s32 z;
    Vec3 pos;
    SVECTOR rot;

    s32 pitch;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    rot.vy = ((u16 *)obj->vars.words)[2];
    z = 0x17C;
    FAKE_OPAQUE(z);
    if (obj->vars.damage_record.unk_24A == 0) {
        pos_add_vec3_rotated(&pos, &rot, 0x19, -0x32, z);
    } else {
        pos_add_vec3_rotated(&pos, &rot, -0x19, -0x32, z);
    }
    sound_play_at_units(SND_MUZZLE_FIRE | SND_GROUP(1), 0x60, 0x3C, &pos);
    obj_spawn_placed(&pos, &rot, 1);
}

void obj_spawn_timed(s32 arg0, Vec3 *pos, SVECTOR *rot);
void obj_eject_fx(Object *obj) {
    Vec3 pos;
    SVECTOR rot;
    Vec3 *posp;
    SVECTOR *rotp;
    s32 rnd;
    s32 rnd_bias;
    s32 yaw_plus;
    s32 pitch;

    posp = &pos;
    rotp = &rot;
    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    rot.vy = obj->vars.damage_record.saved_yaw;
    pos_add_vec3_rotated(posp, rotp, 0, -0x96, -0xC8);
    rot.vx += 0x400;
    rnd = rand_a_next();
    yaw_plus = (u16)rot.vy + 0x100;
    /* rnd % 256 with the sign handled as C does it for the remainder */
    rnd_bias = (rnd < 0) ? rnd + 0xFF : rnd;
    rot.vy = yaw_plus + (rnd - ((rnd_bias >> 8) << 8));
    sound_play_at_units(SND_TWIN_SHOT_FIRE | SND_GROUP(1), 0x60, 0x3C, posp);
    obj_spawn_timed(model_slot_pchr(*(s32 *)obj->asset) + 0xE8, posp, rotp);
}

/* Rotate the offset (x, y, z) by the angles in rot (yaw sign reversed) and add the result to pos. */
void pos_add_rotated_d(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    rotate_xz_twice(rot->vy, -rot->vx, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}

static inline void spark_add_list_u(s32 x, s32 y, s32 z, s32 ry, s32 rx, u16 rz, s32 value, s32 colour) {
    SparkList *list = &spark_list;
    s32 n = spark_count;
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
/* Adds two sparks: one at the object's position along its heading, one 30 units behind it. */
void spark_tip_emit_draw(Object *obj) {
    s32 value;
    s32 tip_value;
    s32 pitch;
    s32 yaw;
    Vec3 pos;
    s32 pad; /* pos is a 0x10-byte slot in the original's frame */
    SVECTOR rot;
    s32 frame_pad[2]; /* the original's frame is 8 bytes larger */
    Vec3 *tip_pos;

    value = obj->vars.timed.unk_248;
    tip_value = get_model_slot_base() + 0xE;
    tip_pos = &pos;
    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    yaw = obj->yaw;
    rot.vy = yaw;
    rot.vz = obj->roll;
    spark_add_list_u(pos.x, pos.y, pos.z, yaw + 0x800, rot.vx, rot.vz, value, 0);
    pos_add_rotated_d(tip_pos, &rot, 0, 0, -0x1E);
    spark_add_head(&spark_list, pos.x, pos.y, pos.z, 0, 0, 0, tip_value, 0);
}

/* Homing missile: steers at the player for a while, leaves a smoke trail,
   and explodes on owner damage, a wall or an object it hits. */
void homing_missile_update(Object *m) {
    s32 *target = player_position();
    s32 start[4];
    s32 end[4];
    s32 hit[4];
    s32 unused[4];
    s32 from[4];
    s32 yaw_pitch[2];
    s32 smoke_pos[4];
    s16 victim;
    s32 dz;
    s16 pitch;
    s32 cur;
    s32 want;
    s32 speed;
    s16 yaw;

    if (flag_get() != 0) {
        goto explode;
    }
    if (m->vars.missile.done == 0) {
        if ((s16)m->vars.missile.steer_time-- > 0) {
            from[0] = m->x >> 12;
            from[1] = m->y >> 12;
            from[2] = m->z >> 12;
            dz = target[2] - from[2];
            vector_to_angles(target[0] - from[0], target[1] - from[1], dz,
                             &yaw_pitch[0], &yaw_pitch[1]);
            yaw = angle_approach(m->yaw, yaw_pitch[0], 0x20);
            cur = m->pitch;
            want = yaw_pitch[1];
            m->yaw = yaw;
            pitch = angle_approach(cur, -want, 0x20);
            want = pitch;
            cur = m->yaw;
            speed = m->speed;
            m->pitch = pitch;
            angles_to_vector(cur, want, speed, &m->vx, &m->vy, &m->vz);
        }
        m->vars.missile.trail ^= 1;
        if (m->vars.missile.trail == 0) {
            s32 base = get_model_slot_base();
            smoke_pos[0] = m->x >> 12;
            smoke_pos[1] = m->y >> 12;
            smoke_pos[2] = m->z >> 12;
            effect_spawn_at((Vec3 *)smoke_pos, base + 0x20, 10, 0x10);
        }
        start[0] = m->x >> 12;
        start[1] = m->y >> 12;
        start[2] = m->z >> 12;
        end[0] = (m->x + m->vx) >> 12;
        end[1] = (m->y + m->vy) >> 12;
        end[2] = (m->z + m->vz) >> 12;
        if (obj_hit_damage(m->index) > 0) {
        explode:
            spawn_effect(start[0], start[1], start[2], 0x80000000);
            m->vars.missile.done = 1;
        } else if (trace_world(8, 0x10, start, end, hit)) {
            m->vars.missile.done = 1;
            spawn_effect(hit[0], hit[1], hit[2], 0);
        } else {
            set_collide_mode(1);
            if (trace_objects(start, end, 0x10, hit, &victim)) {
                hit_target_masked(victim, 1, atan2(hit[2] - start[2], hit[0] - start[0]), 10);
                spawn_effect(hit[0], hit[1], hit[2], 0);
                m->vars.missile.done = 1;
            }
            set_collide_mode(0);
            m->z += m->vz;
            m->x += m->vx;
            m->y += m->vy;
            if (m->speed < 0x28) {
                m->speed++;
            }
        }
        if (m->vars.missile.done == 0) {
            return;
        }
    }
    obj_free(m);
}

void homing_missile_update(Object *m);
void spark_tip_emit_draw(Object *obj);
void obj_spawn_timed(s32 arg0, Vec3 *pos, SVECTOR *rot) {
    Object *obj;
    ObjHandler *h;
    s32 frame_pad[6]; /* unused; the original's frame is 24 bytes larger */

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
        h = obj->handlers;
        h[1].fn = homing_missile_update;
        h[0].fn = NULL;
        h[0].unk_11 = 0;
        h[0].state = 0;
        h[1].unk_11 = 0;
        h[1].state = 0;
        h[2].fn = NULL;
        h[2].unk_11 = 0;
        h[2].state = 0;
        h[3].fn = spark_tip_emit_draw;
        h[3].unk_11 = 0;
        h[3].state = 0;
        obj->callback = 0;
        obj_set_flags(obj, 0x80);
        obj->unk_17A = 0;
        obj_hit_clear(obj->index);
        obj->speed = 0;
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot->vx;
        obj->yaw = rot->vy;
        obj->roll = rot->vz;
        obj->vars.timed.unk_248 = arg0;
        obj->vars.timed.unused_24A = 0x3C;
        obj->vars.timed.unused_24C = 0;
        obj->vars.timed.unused_250 = 0;
    }
}

extern CamZone cam_zones[17];
extern s32 cam_zone_current;
static inline s16 zone_contains(CamZone *zone, s32 x, s32 y, s32 z) {
    if (x < zone->box.min_x) return 0;
    if (x > zone->box.max_x) return 0;
    if (y < zone->box.min_y) return 0;
    if (y > zone->box.max_y) return 0;
    if (z < zone->box.min_z) return 0;
    if (z > zone->box.max_z) return 0;
    return 1;
}
void cam_zone_update_lights(void) {
    s32 x = cam_pos >> 12;
    s32 y = cam_pos_y >> 12;
    s32 z = cam_pos_z >> 12;
    s32 i;
    s32 bit;
    s32 lights;

    if (cam_zone_current >= 0 && zone_contains(&cam_zones[cam_zone_current], x, y, z)) {
        return;
    }
    for (i = 0; i < 17; i++) {
        if (zone_contains(&cam_zones[i], x, y, z)) {
            break;
        }
    }
    if (i < 17) {
        lights = cam_zones[i].lights;
    } else {
        i = -1;
        lights = -1;
    }
    cam_zone_current = i;
    for (bit = 0; bit < 5; bit++) {
        scene_model_set_flag(bit, lights & 1);
        lights >>= 1;
    }
}
