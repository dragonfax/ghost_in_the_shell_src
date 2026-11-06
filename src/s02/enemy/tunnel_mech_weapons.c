/* tunnel_mech_weapons: one of s02's own original source files (scripts/objmap.py); part of src/s02/main.c's unit, included there. */

/* Draws the laser strike: a pool model scaled by 0x2000 - unk_24C, added as a spark tinted by unk_250 - unk_24C. */
void tunnel_mech_laser_strike_draw(Object *obj) {
    s32 pos[4];
    s32 model, size, level, hi;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    model = obj->vars.tunnel_mech_laser_strike.model;
    size = 0x2000 - (s16)obj->vars.tunnel_mech_laser_strike.progress;
    model = pool_spawn_scaled(model, size, size, 0x1000);
    level = obj->vars.tunnel_mech_laser_strike.intensity;
    level -= (s16)obj->vars.tunnel_mech_laser_strike.progress;
    level >>= 5;
    hi = level;
    if (hi == 0) {
        hi = 1;
    }
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, model, (hi << 16) | (level << 8) | level);
}

void tunnel_mech_laser_strike_update(Object *obj) {
    s32 rand;
    u16 timer;
    u16 flip;

    timer = obj->vars.tunnel_mech_laser_strike.progress + 0x100;
    flip = obj->vars.tunnel_mech_laser_strike.flip;
    flip ^= 1;
    obj->vars.tunnel_mech_laser_strike.progress = timer;
    obj->vars.tunnel_mech_laser_strike.flip = flip;
    if (flip == 0) {
        rand = rand_a_next();
        obj->vars.tunnel_mech_laser_strike.model = obj->vars.tunnel_mech_laser_strike.base_model + (rand % 4);
    }
    if ((s16) obj->vars.tunnel_mech_laser_strike.progress >= 0x1001) {
        obj_free(obj);
    }
}

void tunnel_mech_laser_strike_draw(Object *obj);
s32 tunnel_mech_laser_strike_spawn(s32 *position, s32 init_248, s32 init_250) {
    Object *obj;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
        obj_hit_clear(obj->index);
        obj_hit_flag_set(obj->index, 0);
        obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) tunnel_mech_laser_strike_update;
        obj->unk_17A = 0;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) tunnel_mech_laser_strike_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->x = position[0] << 12;
        obj->y = position[1] << 12;
        obj->z = position[2] << 12;
        obj->vars.tunnel_mech_laser_strike.base_model = init_248;
        obj->vars.tunnel_mech_laser_strike.model = init_248;
        obj->vars.tunnel_mech_laser_strike.progress = 0;
        obj->vars.tunnel_mech_laser_strike.flip = 0;
        obj->vars.tunnel_mech_laser_strike.intensity = init_250;
        return 1;
    }
    return 0;
}

extern TrailSample laser_trail_scratch;
void prim_world_fan_add(s32 count, MatrixRow *verts, u8 *tint);
/* Draws the tunnel mech laser: a core spark, a beam of sparks along the aim, a tip glow, then the faded trail. */
void tunnel_mech_laser_draw(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 step[3];
    s32 colour;
    s32 level;
    s32 len;
    s32 model;
    s32 i;
    s32 j;
    s32 pitch;
    s32 hi;
    u8 tint[4];

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    level = obj->vars.tunnel_mech_laser.intensity + 0x80;
    level >>= 5;
    len = obj->vars.tunnel_mech_laser.intensity + 0x1000;
    hi = level;
    if (hi == 0) {
        hi = 1;
    }
    colour = (hi << 16) | (level << 8) | level;
    model = pool_spawn_scaled(get_model_slot_base() + 0xF, len, len, 0x1000);
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, model, colour);

    level = (s16)(u16)obj->vars.tunnel_mech_laser.intensity >> 5;
    {
        /* hard register: keeps the copy in v0 as the original does */
        register s32 hi asm("$2") = level;
        if (level == 0) {
            hi = 1;
        }
        colour = (hi << 16) | (level << 8) | level;
    }
    model = obj->vars.tunnel_mech_laser.model_base + 0x181;
    model = pool_spawn_scaled(model, len, len, 0x1000);
    step[0] = 0;
    step[1] = 0;
    step[2] = 0xC0;
    rotate_xz_twice(rot[1], rot[0], &step[0], &step[1], &step[2]);
    for (j = 0; j < obj->vars.tunnel_mech_laser.segment_count; j++) {
        spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], model, colour);
        pos[0] += step[0];
        pos[1] += step[1];
        pos[2] += step[2];
    }
    model = obj->vars.tunnel_mech_laser.model_base + 0x183;
    model = pool_spawn_scaled(model, len, len, obj->vars.tunnel_mech_laser.tail_scale);
    spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], model, colour);

    for (i = 1; i <= trail_count; i++) {
        s32 a;
        s32 b;
        s32 slot = trail_head - i;

        while (slot < 0) {
            slot += 16;
        }
        a = (trail_count - i) * 8;
        b = (trail_count - i) * 16;
        tint[0] = 0;
        tint[1] = a;
        tint[2] = b;
        tint[1] = tint[1] * obj->vars.tunnel_mech_laser.intensity / 0x1000;
        tint[2] = tint[2] * obj->vars.tunnel_mech_laser.intensity / 0x1000;
        laser_trail_scratch.row[0] = laser_trail_ring[slot].row[0];
        laser_trail_scratch.row[1] = laser_trail_ring[slot].row[1];
        laser_trail_scratch.row[2] = laser_trail_ring[slot].row[3];
        laser_trail_scratch.row[3] = laser_trail_ring[slot].row[2];
        prim_world_fan_add(4, laser_trail_scratch.row, tint);
    }
}

/* Stores the distance from `to` to `from` divided by 192 (unk_256), and the
 * remainder scaled by 4096 / 192 (unk_258). */
void tunnel_mech_laser_set_segments(Object *obj, Vec3 *from, Vec3 *to) {
    s32 dist = isqrt(length_sq(from->x - to->x, from->y - to->y, from->z - to->z));

    obj->vars.tunnel_mech_laser.segment_count = dist / 192;
    obj->vars.tunnel_mech_laser.tail_scale = ((dist % 192) << 12) / 192;
}

extern s32 laser_sound_a_handle;
extern s32 laser_sound_b_handle;
extern MatrixRow laser_prev_from, laser_prev_hit, laser_sound_pos_a, laser_sound_pos_b;
void tunnel_mech_laser_update(Object *obj) {
    s32 id = obj->vars.tunnel_mech_laser.model_base + 0x185;
    s16 traced = 0;
    MatrixRow from, to, hit, trail[4];
    s32 box[6], yaw, pitch, vx, vy, vz;
    s16 target;

    if (((Object *) obj->vars.enemy.mode)->vars.enemy.unk_266 == 2) {
        goto stop;
    }
    {
        s32 *ppos;
        s32 px, py, dz, idx, base, pz;
        s32 tx, ty;
        MatrixRow *to_p, *hit_p;

        solid_part_box(((Object *) obj->vars.enemy.mode)->solid_id, 0, box, 0);
        obj->x = box[0] << 12;
        obj->y = (box[1] - 0x46) << 12;
        obj->z = (box[2] + 0x12C) << 12;
        obj->vars.tunnel_mech_laser.toggle ^= 1;
        ppos = player_position();
        pz = obj->z >> 12;
        base = pz - 0xC8;
        dz = ppos[2] - base;
        dz *= obj->vars.tunnel_mech_laser.intensity;
        py = obj->y >> 12;
        px = obj->x >> 12;
        if (dz < 0) {
            dz += 0xFFF;
        }
        dz >>= 12;
        if (dz < 0x12C) {
            dz = 0x12C;
        }
        idx = (u16) obj->vars.tunnel_mech_laser.wave_phase & 0xFFF;
        dz += pz;
        ty = ((s16) rcossin_tbl[idx] * 0x360) / 0x1000 - 0x400;
        tx = (cos_table[idx].value * 0x360) / 0x1000;
        vector_to_angles(tx - px, ty - py, dz - pz, &yaw, &pitch);
        obj->pitch = pitch;
        obj->yaw = yaw;
        if (obj->vars.tunnel_mech_laser.unk_25A == 0) {
            obj->vars.tunnel_mech_laser.wave_phase = (u16) obj->vars.tunnel_mech_laser.wave_phase + (obj->vars.tunnel_mech_laser.intensity * 0x18) / 0x1000;
        } else {
            obj->vars.tunnel_mech_laser.wave_phase = (u16) obj->vars.tunnel_mech_laser.wave_phase - (obj->vars.tunnel_mech_laser.intensity * 0x18) / 0x1000;
        }
        angles_to_vector(obj->yaw, -obj->pitch, 0x4E20, &vx, &vy, &vz);
        from.w[0] = obj->x >> 12;
        from.w[1] = obj->y >> 12;
        from.w[2] = obj->z >> 12;
        to.w[0] = (obj->x + vx) >> 12;
        to.w[1] = (obj->y + vy) >> 12;
        to.w[2] = (obj->z + vz) >> 12;
        hit_p = &hit;
        to_p = &to;
        *hit_p = *to_p;
        if (obj->vars.tunnel_mech_laser.intensity >= 0xFE1) {
            set_collide_mode(1);
            if (trace_objects(&from, to_p, 0x10, hit_p, &target)) {
                hit_target_masked(target, 1, atan2(hit.w[2] - from.w[2], hit.w[0] - from.w[0]), 0x14);
                if (obj->vars.tunnel_mech_laser.toggle == 0) {
                    tunnel_mech_laser_strike_spawn(hit_p->w, id, obj->vars.tunnel_mech_laser.intensity);
                }
                tunnel_mech_laser_set_segments(obj, (Vec3 *) hit_p, (Vec3 *) &from);
                traced = 1;
            }
            set_collide_mode(0);
        }
        if (traced != 1) {
            if (trace_world(8, 1, &from, &to, &hit)) {
                if (obj->vars.tunnel_mech_laser.toggle == 0) {
                    tunnel_mech_laser_strike_spawn(hit.w, id, obj->vars.tunnel_mech_laser.intensity);
                }
                tunnel_mech_laser_set_segments(obj, (Vec3 *) &hit, (Vec3 *) &from);
            } else {
                obj->vars.tunnel_mech_laser.segment_count = 0x68;
                obj->vars.tunnel_mech_laser.tail_scale = 0x1000;
            }
        }
        trail[0].w[0] = from.w[0];
        trail[0].w[1] = from.w[1];
        trail[0].w[2] = from.w[2];
        trail[1].w[0] = hit.w[0];
        trail[1].w[1] = hit.w[1];
        trail[1].w[2] = hit.w[2];
        trail[2].w[0] = laser_prev_from.w[0];
        trail[2].w[1] = laser_prev_from.w[1];
        trail[2].w[2] = laser_prev_from.w[2];
        trail[3].w[0] = laser_prev_hit.w[0];
        trail[3].w[1] = laser_prev_hit.w[1];
        trail[3].w[2] = laser_prev_hit.w[2];
        laser_prev_from.w[0] = from.w[0];
        laser_prev_from.w[1] = from.w[1];
        laser_prev_from.w[2] = from.w[2];
        laser_prev_hit.w[0] = hit.w[0];
        laser_prev_hit.w[1] = hit.w[1];
        laser_prev_hit.w[2] = hit.w[2];
        trail_push(trail);
        sound_closest_point((Vec3 *) &from, (Vec3 *) &hit, (Vec3 *) &laser_sound_pos_a);
        laser_sound_pos_a.w[0] <<= 12;
        laser_sound_pos_a.w[1] <<= 12;
        laser_sound_pos_a.w[2] <<= 12;
        laser_sound_pos_b.w[0] = hit.w[0] << 12;
        laser_sound_pos_b.w[1] = hit.w[1] << 12;
        laser_sound_pos_b.w[2] = hit.w[2] << 12;
        {
            s32 v1 = sound_volume_of(0xB025B02B, obj->vars.tunnel_mech_laser.intensity);
            s32 v2 = sound_volume_of(SND_LASER_IMPACT_LOOP | SND_HELD | SND_GROUP(2), obj->vars.tunnel_mech_laser.intensity);
            sound_set_volume(laser_sound_a_handle, v1);
            sound_set_volume(laser_sound_b_handle, v2);
        }
        if ((s16) obj->vars.tunnel_mech_laser.timer-- < 0) {
            if (obj->vars.tunnel_mech_laser.intensity > 0) {
                obj->vars.tunnel_mech_laser.intensity -= 0x40;
            } else {
                ((Object *) obj->vars.enemy.mode)->vars.enemy.unk_266 = 0;
            stop:
                sound_stop(laser_sound_a_handle);
                sound_stop(laser_sound_b_handle);
                laser_sound_a_handle = 0;
                laser_sound_b_handle = 0;
                obj_free(obj);
            }
        } else if (obj->vars.tunnel_mech_laser.intensity < 0x1000) {
            obj->vars.tunnel_mech_laser.intensity += 0x40;
        }
    }
}

s32 tunnel_mech_laser_spawn(Object *parent) {
    s32 pos[3];
    s32 cell[3];
    MatrixRow *sound_a;
    MatrixRow *sound_b;
    s32 *player;
    Object *obj;

    player_position();
    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->vars.part.parent = parent;
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) tunnel_mech_laser_update;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) tunnel_mech_laser_draw;
    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->damage = 0x14;
    obj->vars.tunnel_mech_laser.intensity = 0;
    obj->vars.tunnel_mech_laser.toggle = 0;
    obj->vars.tunnel_mech_laser.model_base = model_slot_pchr(*(s32 *) obj->vars.part.parent->asset);
    obj->vars.enemy.sound_channel[0] = 0x12C;
    obj->vars.enemy.sound_channel[1] = 0x68;
    obj->vars.tunnel_mech_laser.unused_252 = 0;
    obj->vars.tunnel_mech_laser.tail_scale = 0x4E20;
    obj->vars.tunnel_mech_laser.unk_25A = 0;
    obj->vars.tunnel_mech_laser.wave_phase = 0;
    solid_part_box(obj->vars.part.parent->solid_id, 0, pos, NULL);
    obj->x = pos[0] << 12;
    obj->y = (pos[1] - 0x46) << 12;
    obj->z = (pos[2] + 0x12C) << 12;

    player = player_position();
    cell[0] = obj->x >> 12;
    cell[1] = obj->y >> 12;
    cell[2] = obj->z >> 12;
    if (cell[0] < player[0]) {
        obj->vars.tunnel_mech_laser.unk_25A = 1;
    }
    if (player[1] > cell[1]) {
        obj->pitch = 0x300;
    } else {
        obj->pitch = -0x300;
    }
    obj->yaw = 0;
    obj->roll = 0;
    obj->vars.part.parent->vars.tunnel_mech_laser.unused_266 = 1;
    trail_clear();

    sound_a = &laser_sound_pos_a;
    sound_a->w[0] = 0;
    laser_sound_pos_a.w[1] = 0;
    laser_sound_pos_a.w[2] = 0;
    sound_b = &laser_sound_pos_b;
    sound_b->w[0] = 0;
    laser_sound_pos_b.w[1] = 0;
    laser_sound_pos_b.w[2] = 0;
    laser_prev_from.w[0] = pos[0];
    laser_prev_from.w[1] = pos[1] - 0x46;
    laser_prev_from.w[2] = pos[2] + 0x12C;
    laser_prev_hit.w[0] = pos[0];
    laser_prev_hit.w[1] = pos[1] - 0x46;
    laser_prev_hit.w[2] = pos[2] + 0x12C;
    laser_sound_a_handle = sound_start(0xB025B02B, 0, 0, 0);
    laser_sound_b_handle = sound_start(SND_LASER_IMPACT_LOOP | SND_HELD | SND_GROUP(2), 0, 0, 0);
    sound_attach(laser_sound_a_handle, sound_a, NULL);
    sound_attach(laser_sound_b_handle, sound_b, NULL);
    return 1;
}

/* Squared distance from the player to the object's centre (half its height above its base). */
s32 tunnel_mech_player_dist_sq(Object *obj) {
    s32 *player = player_position();
    s32 x = obj->x >> 12;
    s32 height_hi = obj->height << 16;
    s32 height = height_hi >> 16;
    /* (s16)obj->height / 2, written out: the plain form schedules y's shift too early */
    return length_sq(player[0] - x,
                     player[1] - ((obj->y >> 12) - ((s32)(height + ((u32)height_hi >> 31)) >> 1)),
                     player[2] - (obj->z >> 12));
}

extern s32 tunnel_mech_shot_damage;

void tunnel_mech_shot_arm(void) {
    tunnel_mech_shot_damage = 0x14;
}
static inline void spark_add_pos(s32 *pos, s32 value, s32 colour) {
    SparkList *list = &spark_list;
    s32 n = SPARK_COUNT;
    s32 x = pos[0], y = pos[1], z = pos[2];
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
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
}

void tunnel_mech_shot_draw(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    s32 value = obj->vars.tunnel_mech_shot_launch_obj.unk_248;
    s32 size, full, inv, level, hi;
    s32 fade;

    full = 0x1000;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    fade = obj->vars.tunnel_mech_shot_launch_obj.fade;
    size = fade;
    size += 0x1000;
    inv = full - fade;
    value = pool_spawn_scaled(value, size, size, 0x1000);
    level = inv >> 5;
    hi = level;
    if (hi == 0) {
        hi = 1;
    }
    spark_add_pos(pos, value, (hi << 16) | (level << 8) | level);
    scratch_top -= 0x10;
}

s32 tunnel_mech_player_dist_sq(Object *obj);
/* Per-step update of a spinning effect object; frees itself when done or when it has flown too far. */
void tunnel_mech_shot_update(Object *obj) {
    s32 unused[4];
    s32 *p = scratch_alloc(0x40);

    if (is_stage_ending(obj) == 0) {
        s16 angle = obj->vars.tunnel_mech_shot_launch_obj.angle;

        if (angle < obj->vars.tunnel_mech_shot_launch_obj.fade) {
            obj->vars.tunnel_mech_shot_launch_obj.angle = angle + 0x400;
            obj->vars.tunnel_mech_shot_launch_obj.unk_248++;
        }
        if (tunnel_mech_shot_damage != 0) {
            p[0] = obj->x >> 12;
            p[2] = obj->z >> 12;
            p[4] = (obj->x + obj->vx) >> 12;
            p[6] = ((obj->z + obj->vz) >> 12) + 0x64;
            if (tunnel_mech_player_dist_sq(obj) <= 0x3D08F) {
                hit_target_masked(0, 1, atan2(p[6] - p[2], p[4] - p[0]), (s16)tunnel_mech_shot_damage);
                tunnel_mech_shot_damage = 0;
            }
        }
        obj->z += obj->vz;
        obj->x += obj->vx;
        obj->y += obj->vy;
        if (obj->vars.tunnel_mech_shot_launch_obj.fade <= 0x1000) {
            goto tail;
        }
    }
    obj_free(obj);
tail:
    obj->vars.tunnel_mech_shot_launch_obj.fade += 0x40;
    scratch_top -= 0x40;
}

void tunnel_mech_shot_draw(Object *obj);
s32 tunnel_mech_shot_launch(Vec3 *pos, s16 *rot, s32 index) {
    s32 yaw;
    s32 pitch;
    u16 roll;
    s32 table_index;
    s32 speed;
    s32 result;
    Object *obj;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
        obj_set_flags(obj, 0x80);
        obj_hit_clear(obj->index);
        obj_hit_flag_set(obj->index, 0);
        obj->handlers[1].fn = tunnel_mech_shot_update;
        obj->handlers[3].fn = tunnel_mech_shot_draw;
        obj->speed = 0x10;
        obj->unk_17A = 0;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->damage = 0x14;
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        roll = rot[2];
        obj->vars.tunnel_mech_shot_launch_obj.unk_248 = index + 0x1A0;
        obj->vars.tunnel_mech_shot_launch_obj.angle = 0x400;
        obj->vars.tunnel_mech_shot_launch_obj.fade = 0;
        obj->roll = roll;
        player_position();
        table_index = obj->roll & 0xFFF;
        {
            register s32 *yaw_ptr asm("$7") = &yaw;
            register s32 *pitch_ptr asm("$3") = &pitch;
            vector_to_angles(cos_table[table_index].value, (s16) rcossin_tbl[table_index], 0x1000, yaw_ptr, pitch_ptr);
        }
        speed = obj->speed;
        obj->pitch = *(s16 *) &pitch;
        obj->yaw = yaw;
        angles_to_vector((s16) yaw, obj->pitch, speed, &obj->vx, &obj->vy, &obj->vz);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void spark_puff_update(Object *obj) {
    s32 base[3];
    s16 rot[3];
    s32 pos[3];
    s32 off[3];
    s32 r, r2, t, colour;
    s32 rem;
    s16 pn;
    s32 yaw, pitch, hi, value, x, y, z;
    s32 unused[2];

    r = rand_b_next();
    rem = r % 0x800;
    base[0] = obj->x >> 12;
    base[1] = obj->y >> 12;
    base[2] = obj->z >> 12;
    pitch = obj->pitch;
    pn = -pitch;
    rot[0] = pn;
    yaw = obj->yaw;
    rot[1] = yaw;
    rot[2] = obj->roll;
    if (obj->vars.tunnel_mech_shot.timer > 0) {
        t = 0x1000 - rem;
        t >>= 5;
        hi = t;
        if (hi == 0) {
            hi = 1;
        }
        colour = (hi << 16) | (t << 8) | t;
        off[0] = 0;
        off[1] = 0;
        off[2] = 0;
        rotate_xz_twice(yaw, -pn, &off[0], &off[1], &off[2]);
        pos[0] = obj->vars.tunnel_mech_shot.origin_x + off[0];
        pos[1] = obj->vars.tunnel_mech_shot.origin_y + off[1];
        pos[2] = obj->vars.tunnel_mech_shot.origin_z + off[2];
        value = get_model_slot_base() + 1;
        spark_add_pos(pos, value, colour);
        off[0] = 0;
        off[1] = 0;
        off[2] = 0x46;
        rotate_xz_twice(rot[1], -rot[0], &off[0], &off[1], &off[2]);
        pos[0] = obj->vars.tunnel_mech_shot.origin_x + off[0];
        pos[1] = obj->vars.tunnel_mech_shot.origin_y + off[1];
        pos[2] = obj->vars.tunnel_mech_shot.origin_z + off[2];
        value = get_model_slot_base() + 3;
        spark_add_pos(pos, value, colour);
        r2 = rand_b_next();
    rem = r % 0x800;
        if (r2 == (r2 / 3) * 3) {
            off[0] = 0;
            off[1] = 0;
            off[2] = 0x78;
            rotate_xz_twice(rot[1], -rot[0], &off[0], &off[1], &off[2]);
            pos[0] = obj->vars.tunnel_mech_shot.origin_x + off[0];
            pos[1] = obj->vars.tunnel_mech_shot.origin_y + off[1];
            pos[2] = obj->vars.tunnel_mech_shot.origin_z + off[2];
            value = get_model_slot_base() + 4;
        spark_add_pos(pos, value, colour);
            off[0] = 0;
            off[1] = 0;
            off[2] = 0x14;
            rotate_xz_twice(rot[1], -rot[0], &off[0], &off[1], &off[2]);
            pos[0] = obj->vars.tunnel_mech_shot.origin_x + off[0];
            pos[1] = obj->vars.tunnel_mech_shot.origin_y + off[1];
            pos[2] = obj->vars.tunnel_mech_shot.origin_z + off[2];
            value = get_model_slot_base() + 5;
        spark_add_pos(pos, value, colour);
        }
        obj->vars.tunnel_mech_shot.timer = obj->vars.tunnel_mech_shot.timer - 1;
    }
    if (obj->vars.tunnel_mech_shot.unk_248) {
        obj_free(obj);
    }
}

void tunnel_mech_shot_collide(Object *obj, ObjHandler *handler) {
    s16 target;
    s32 *p; /* from [0..2], to [4..6], hit surface [7] */
    s32 *to;
    s32 hit;
    s32 surface;
    s32 anim;
    s32 life;
    s32 fx_type;

    if (obj->vars.enemy.mode == 1) {
        return;
    }
    if ((s16)obj_hit_damage(obj->index) > 0) {
        obj->vars.enemy.mode = 1;
        return;
    }
    p = scratch_alloc(0x20);
    p[0] = obj->x >> 12;
    p[1] = obj->y >> 12;
    p[2] = obj->z >> 12;
    p[4] = (obj->x + obj->vx) >> 12;
    to = p + 4;
    p[5] = (obj->y + obj->vy) >> 12;
    p[6] = (obj->z + obj->vz) >> 12;
    hit = trace_world(8, 8, p, to, to);
    surface = (surface_of(p[7]) & 0x300) >> 8;
    set_collide_mode(1);
    if (trace_objects(p, to, 8, to, &target)) {
        hit = 1;
        surface = 0;
        hit_target_masked(target, 1, (s16)atan2(p[6] - p[2], p[4] - p[0]), obj->damage);
    }
    set_collide_mode(0);
    if (hit != 0) {
        if (surface == 1) {
            if (obj->vars.tunnel_mech_shot.unk_25C == 1) {
                sound_play_at_units(SND_TUNNEL_MECH_SHOT_IMPACT | SND_GROUP(2), 0x60, 0x3C, to);
            }
            anim = 0x48;
            fx_type = 5;
            life = 0xF;
        } else {
            if (obj->vars.tunnel_mech_shot.unk_25C == 1) {
                sound_play_at_units(SND_RICOCHET2 | SND_GROUP(2), 0x60, 0x3C, to);
            }
            anim = rand_a_next(); /* rand 0..0xFFF */
            anim = (anim * 3 / 4096) * 4 + 0x30;
            fx_type = 4;
            life = 0x3C;
        }
        effect_spawn_at((Vec3 *)(p + 4), anim + get_model_slot_base(), fx_type, life);
        obj->vars.enemy.mode = 1;
    } else if (cam_range_check(p[0], p[1], p[2]) == 0) {
        obj->vars.enemy.mode = 1;
    }
    scratch_top -= 0x20;
    obj->vars.enemy.mode = 1;
}

void tunnel_mech_shot_collide(Object *obj, ObjHandler *handler);
void tunnel_mech_shot_init(Object *obj, s32 *pos, u16 *angles, s16 unk_25C) {
    s32 speed;
    s32 yaw;
    s32 pitch;

    obj->handlers[1].fn = tunnel_mech_shot_collide;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) spark_puff_update;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = angles[0];
    obj->yaw = angles[1];
    obj->roll = angles[2];
    obj->speed = 8000;
    obj->vars.shot.age = 1;
    obj->vars.shot.unused_248 = 0;
    obj->vars.shot.unk_25C = unk_25C;
    obj->damage = 10;
    obj->vars.shot.origin[0] = pos[0];
    obj->vars.shot.origin[1] = pos[1];
    obj->vars.shot.origin[2] = pos[2];
    yaw = obj->yaw;
    pitch = obj->pitch;
    speed = obj->speed;
    angles_to_vector(yaw, pitch, speed, &obj->vx, &obj->vy, &obj->vz);
}

void tunnel_mech_shot_init(Object *obj, s32 *pos, u16 *angles, s16 unk_25C);
s32 tunnel_mech_shot_spawn(s32 *pos, u16 *angles, s32 c) {
    Object *obj;
    s32 result;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
        obj_set_flags(obj, 0x80);
        obj_hit_clear(obj->index);
        obj_hit_flag_set(obj->index, 0);
        obj->unk_17A = 0;
        tunnel_mech_shot_init(obj, pos, angles, (s16) c);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

static inline void spark_add_pos_yaw(s32 *pos, s32 ry, s32 value, s32 colour) {
    SparkList *list = &spark_list;
    s32 n = SPARK_COUNT;
    s32 x = pos[0], y = pos[1], z = pos[2];
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
        s->pitch = 0;
        s->roll = 0;
    }
}
void tunnel_mech_spark_draw(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    s32 t, inv, r, b, colour, value;

    value = obj->vars.at_pos.unk_248; /* pool index, then the pool entry */
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    t = obj->vars.at_pos.unk_24A;
    r = t * 0xC00;
    inv = 0x1000 - t;
    b = r;
    /* r = t * 0xC00 / 0x1000 >> 5, rounded by hand */
    if (r < 0) {
        r += 0xFFF;
    }
    b = (b + (inv << 9)) / 0x1000 >> 5;
    r >>= 17;
    if ((r | b) == 0) {
        b = 1;
    }
    colour = (b << 16) | (r << 8) | r;
    do {
        inv *= 8;
        value = pool_spawn_scaled(value, inv, inv, 0x1000);
    } while (0);
    spark_add_pos_yaw(pos, 0x800, value, colour);
}

/* Steps the object's 16-bit counter at 0x24A down by 0xAA each call; once it goes
   negative the object is freed. The 0x28 multiplier is the displacement stride. */
void tunnel_mech_effect_update(Object *obj) {
    add_displacement(0, 0, obj->vars.at_pos.unk_24A * 0x28);
    if (obj->vars.at_pos.unk_24A < 0) {
        obj_free(obj);
    }
    obj->vars.at_pos.unk_24A -= 0xAA;
}

void tunnel_mech_spark_draw(Object *obj, ObjHandler *handler);
/* Spawns an object at the position pos (world units, shifted to 20.12 fixed point). */
void obj_spawn_at_pos(s32 base, s32 *pos) {
    Object *obj;
    s32 z;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = tunnel_mech_effect_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = tunnel_mech_spark_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj->unk_17A = 0;
        obj_hit_clear(obj->index);
        obj->speed = 0;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        z = pos[2];
        obj->vars.at_pos.unk_248 = base + 0x1B0;
        obj->vars.at_pos.unk_24A = 0x1000;
        obj->z = z << 12;
    }
}
