/* effects: one of s13's own original source files (scripts/objmap.py); part of src/s13/main.c's unit, included there. */

void fade_colour_update(FadeColour *f) {
    s32 v = f->timer;
    s32 q = v >> 6;
    s32 t;

    if (v < 0) {
        v += 0x3F;
        q = v >> 6;
    }
    t = 0x1000 - q;

    f->colour[0] = t / 64;
    f->colour[1] = t * 96 / 4096;
    f->colour[2] = t * 192 / 4096;
    if (f->timer > 0x3FFFF) {
        f->colour[3] = 0;
    }
}

extern RecTemplate fx_template_colour_fade;
void fade_colour_update();
/* Starts a record from the template D_8011E054 with fade_red_update as its callback; pos is passed through. */
s32 fade_colour_start(s32 *pos) {
    return fx_spawn_template(pos, &fx_template_colour_fade, fade_colour_update);
}


/* Turn the object's yaw toward the player and return its pitch to level. */
void obj_turn_yaw_to_player(Object *obj, s32 step) {
    VECTOR *player = (VECTOR *)player_position();

    obj->yaw = angle_approach(obj->yaw, atan2(player->vz - (obj->z >> 12), player->vx - (obj->x >> 12)), step);
    obj->pitch = angle_approach(obj->pitch, 0, step * 4);
}


/* vars.words[2]: age in frames; [9]: flags; [11]: roll step */
void shot_fly_update(Object *obj, ObjHandler *handler) {
    s32 dist;
    s32 yaw;
    s32 pitch;
    s32 speed;
    s32 age;
    s32 roll;
    s32 *player;
    s32 burst_pos[4];
    s32 pos[4];
    s32 snd_pos[4];
    s32 from[4];
    s32 to[4];
    s32 hit[4];
    s32 dx, dy, dz;

    dist = isqrt(length_sq((VEC_80139584.x >> 12) - (obj->x >> 12),
                           (VEC_80139584.y >> 12) - (obj->y >> 12),
                           (VEC_80139584.z >> 12) - (obj->z >> 12)));
    age = obj->vars.fixed.age;
    obj->vars.fixed.age = age + 1;
    if (age >= 0x40) {
        if (age < 0x60) {
            goto fast_spin;
        }
        if (age >= 0x79) {
            goto expire;
        }
    } else if (age < 0x2A) {
        if (age < 0) {
            goto expire;
        }
        if (age >= 0x18) {
            obj->vars.fixed.unk_274 = 8;
            obj->vars.fixed.flags |= 1;
        }
    } else {
        obj->vars.fixed.unk_274 = 0xC;
        obj->accel_y = (obj->accel_y * 7) >> 3;
        obj->vy = (obj->vy * 7) >> 3;
        obj->vars.fixed.flags |= 2;
    }
    goto done;
fast_spin:
    obj->vars.fixed.unk_274 = 0x20;
    goto done;
expire:
    obj_free(obj);
done:
    roll = obj->roll;
    obj->roll = roll + obj->vars.fixed.unk_274;
    if (dist < 0xB4) {
        burst_pos[0] = obj->x >> 12;
        burst_pos[1] = obj->y >> 12;
        burst_pos[2] = obj->z >> 12;
        fade_colour_start(burst_pos);
        player = player_position();
        hit_target_masked(0, 0x10, atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)), obj->damage);
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        sound_play_at_units(SND_RICOCHET2 | SND_GROUP(2), 0x40, 0x3C, pos);
        obj_free(obj);
    } else {
        if (obj->speed == 0) {
            pos[0] = obj->x >> 12;
            pos[1] = obj->y >> 12;
            pos[2] = obj->z >> 12;
            fade_colour_start(pos);
            snd_pos[0] = obj->x >> 12;
            snd_pos[1] = obj->y >> 12;
            snd_pos[2] = obj->z >> 12;
            sound_play_at_units(SND_RICOCHET2 | SND_GROUP(2), 0x40, 0x3C, snd_pos);
            obj_free(obj);
            return;
        }
        if (abs(player_position()[2] - (obj->z >> 12)) > 0xC00) {
            obj_free(obj);
            return;
        }
    }
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    yaw = obj->yaw;
    pitch = obj->pitch;
    speed = obj->speed;
    angles_to_vector(yaw, pitch, speed, &dx, &dy, &dz);
    obj->x = obj->x + dx;
    obj->y = obj->y + dy;
    obj->z = obj->z + dz;
    to[0] = obj->x >> 12;
    to[1] = obj->y >> 12;
    to[2] = obj->z >> 12;
    if (trace_world(8, 1, from, to, hit)) {
        obj->speed = 0;
    }
    obj->x = hit[0] << 12;
    obj->y = hit[1] << 12;
    obj->z = hit[2] << 12;
}

static inline void spark_add_head_s(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s16 rx, s32 rz, s32 value, s32 colour) {
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
/* Emits two sparks: one at the object, one 8 units ahead along its heading. */
void obj_emit_sparks(Object *obj, ObjHandler *handler) {
    VECTOR pos;
    VECTOR off;
    s16 tilt;
    s32 pitch;
    s32 yaw;
    s32 sound;
    s32 turn;
    s32 second_id;
    register s32 x asm("$10");
    register s32 y asm("$9");
    register s32 z asm("$8");
    register s32 raw asm("$2");

    raw = obj->x;
    x = raw >> 12;
    pos.vx = x;
    raw = obj->y;
    y = raw >> 12;
    pos.vy = y;
    raw = obj->z;
    z = raw >> 12;
    pos.vz = z;
    tilt = obj->pitch;
    pitch = tilt;
    yaw = obj->yaw;
    sound = obj->vars.snd.sound;
    turn = yaw + 0x800;
    spark_add_head_s(&spark_list, x, y, z, yaw + 0x1000, tilt, 0, sound + 6, 0);
    off.vz = -8;
    off.vx = 0;
    off.vy = 0;
    rotate_xz_twice(turn, pitch, &off.vx, &off.vy, &off.vz);
    second_id = sound + 7;
    off.vx += pos.vx;
    off.vy += pos.vy;
    off.vz += pos.vz;
    spark_add_head(&spark_list, off.vx, off.vy, off.vz, 0x800, 0, 0, second_id, 0);
}

/* Frees the object once the function of its index (obj_hit_damage) reports a positive result. */
void obj_free_on_hit(Object *obj, ObjHandler *handler) {
    if ((obj_hit_damage(obj->index) << 16) > 0) {
        obj_free(obj);
    }
}

void shot_fly_update(Object *obj, ObjHandler *handler);
void obj_emit_sparks(Object *obj, ObjHandler *handler);
s32 obj_spawn_fixed(s32 *pos, u16 *rot, s32 arg) {
    Object *obj;
    ObjHandler *h;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    obj_hit_clear(obj->index);
    obj->vars.fixed.unk_24C = arg;
    obj->damage = rot[3];
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    obj->roll = rot[2];
    obj->speed = 0x40;
    h = obj->handlers;
    h[2].fn = obj_free_on_hit;
    h[1].fn = shot_fly_update;
    h[2].unk_11 = 0;
    h[2].state = 0;
    h[1].unk_11 = 0;
    h[1].state = 0;
    h[3].fn = obj_emit_sparks;
    h[3].unk_11 = 0;
    h[3].state = 0;
    obj_set_flags(obj, 0x80);
    return 1;
}

static inline void gun_fire_shot(Object *obj, Vec3 *muzzle, SVECTOR *ang, s32 side) {
    s32 rnd, base;

    ang->pad = obj->damage;
    muzzle->x = side;
    muzzle->y = (-(s16)obj->height * 2) / 5;
    muzzle->z = 0xA3;
    obj_offset_to_world_shifted(obj, (s32 *)muzzle);
    dir_to_angles(muzzle, ang);
    ang->vy = angle_approach(obj->yaw, ang->vy, 0x60);
    ang->vx = angle_approach(obj->pitch, ang->vx, 0xC0);
    rnd = rand_a_next();
    base = (u16)ang->vy - 0x10;
    ang->vy = base + rnd % 32;
    rnd = rand_a_next();
    base = (u16)ang->vx - 0x10;
    ang->vx = base + rnd % 32;
    ang->vy = angle_approach(obj->yaw, ang->vy, 8);
    obj_spawn_fixed((s32 *)muzzle, (u16 *)ang, model_slot_pchr(*(s32 *)obj->asset) + 0x81);
}
/* Twin-gun burst: while bursts are left, every 2-3 steps fires both guns
   (starting the loop sound on the first burst); when none are left, stops
   the sound. */
void gun_burst_update(Object *obj) {
    Vec3 muzzle_vec;
    Vec3 *muzzle;
    SVECTOR ang;

    if (obj->vars.guns.bursts_left == 0) {
        s32 handle = obj->vars.guns.sound;
        obj->vars.guns.burst_delay = 0;
        obj->vars.guns.firing = 0;
        if (handle != 0) {
            if (handle != SOUND_PENDING) {
                sound_stop(handle);
            }
            obj->vars.guns.sound = 0;
        }
        return;
    }
    if (obj->vars.guns.burst_delay != 0) {
        obj->vars.guns.burst_delay--;
        return;
    }
    if (obj->vars.guns.sound == SOUND_PENDING) {
        obj->vars.guns.sound = sound_start(SND_HEAVY_GUNFIRE | SND_HELD | SND_GROUP(1), 0x7F, 0, 0);
        sound_attach(obj->vars.guns.sound, &obj->x, 0);
    }
    obj->vars.guns.bursts_left--;
    obj->vars.guns.burst_delay = rand_a_next() % 2 + 2;
    obj->vars.guns.firing = 1;
    muzzle = &muzzle_vec;
    gun_fire_shot(obj, muzzle, &ang, 0x21);
    gun_fire_shot(obj, muzzle, &ang, -0x22);
}

void spot_effect_update(SpotRec *rec) {
    s32 t = rec->dist / 256;
    s32 level;
    s32 shade;

    level = ABS(t);
    level = ABS(0x1000 - level);
    shade = level / 64;
    rec->scale_a = shade;
    rec->scale_b = shade;
    rec->scale_c = level * 0xC0 / 0x1000;
    if (rec->dist <= 0 || rec->unk_1C > 0) {
        rec->flag = 0;
    }
}

extern RecTemplate fx_template_spot_effect;
void spot_effect_update(SpotRec *rec);
void spot_effect_start(s32 *pos) {
    sound_play_at_units(SND_PROJECTILE_FIRE_ALT | SND_GROUP(1), 0x7F, 0x3C, pos);
    fx_spawn_template(pos, &fx_template_spot_effect, spot_effect_update);
}

void spot_update(SpotRec *rec) {
    s32 scaled;
    s32 angle;
    s32 frac;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 *pos;
    s32 ang;

    angle = 0x1000 - (rec->dist / 768);
    frac = angle / 64;
    scaled = angle * 0xC0;
    rec->scale_a = frac;
    rec->scale_b = frac;
    rec->scale_c = scaled / 0x1000;
    if (rec->dist > 0x2FFFFF) {
        rec->flag = 0;
        return;
    }
    if (rec->dist <= 0x1CCCCB) {
        pos = player_position();
        dx = pos[0] - rec->x;
        dy = pos[1] - rec->y;
        dz = pos[2] - rec->z;
        if (SquareRoot0(length_sq(dx, dy, dz)) < (rec->dist >> 12)) {
            ang = atan2(dz, dx);
            hit_target_masked(0, 0x10, (s16) ang, 0x10);
        }
    }
}

extern RecTemplate fx_template_spot;
void spot_update();
/* Starts a record from the template D_8011E054 with fade_red_update as its callback; pos is passed through. */
s32 spot_start(s32 *pos) {
    return fx_spawn_template(pos, &fx_template_spot, spot_update);
}

void fade_rgb_update(FadeRgbState *p) {
    s32 v = p->level / 0x200;
    v = 0x1000 - v;
    p->r = v / 0x40;
    p->g = v / 0x40;
    p->b = v * 0xC0 / 0x1000;
    if (p->level > 0x1FFFFF) {
        p->a = 0;
    }
}

void fade_rgb_update();
extern RecTemplate fx_template_fade_rgb;
void spot_fade_start(s32 *obj) {
    sound_play_at_units(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, obj);
    spot_start(obj);
    fx_spawn_template(obj, &fx_template_fade_rgb, fade_rgb_update);
}

void projectile_fly_update(Object *obj, ObjHandler *handler) {
    s32 near_pos[3];
    s32 expire_pos[3];
    s32 far_pos[3];
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s32 dx, dy, dz;
    s32 dist;
    s32 roll;
    s32 dz_player;
    s32 yaw, pitch, speed;

    dist = isqrt(length_sq((cam_pos >> 12) - (obj->x >> 12), (cam_pos_y >> 12) - (obj->y >> 12),
                           (cam_pos_z >> 12) - (obj->z >> 12)));
    roll = obj->roll;
    obj->roll = roll + 0x10;
    if (dist < 180) {
        near_pos[0] = obj->x >> 12;
        near_pos[1] = obj->y >> 12;
        near_pos[2] = obj->z >> 12;
        spot_fade_start(near_pos);
        obj_free(obj);
    } else {
        if (--obj->vars.ranged.range_remaining < 0 || obj->speed == 0) {
            expire_pos[0] = obj->x >> 12;
            expire_pos[1] = obj->y >> 12;
            expire_pos[2] = obj->z >> 12;
            spot_fade_start(expire_pos);
            obj_free(obj);
            return;
        }
        dz_player = player_position()[2] - (obj->z >> 12);
        if (dz_player < 0) {
            dz_player = -dz_player;
        }
        if (dz_player > 0xC00) {
            far_pos[0] = obj->x >> 12;
            far_pos[1] = obj->y >> 12;
            far_pos[2] = obj->z >> 12;
            spot_fade_start(far_pos);
            obj_free(obj);
            return;
        }
    }
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    yaw = obj->yaw;
    pitch = obj->pitch;
    speed = obj->speed;
    angles_to_vector(yaw, pitch, speed, &dx, &dy, &dz);
    obj->x += dx;
    obj->y += dy;
    obj->z += dz;
    to[0] = obj->x >> 12;
    to[1] = obj->y >> 12;
    to[2] = obj->z >> 12;
    if (trace_world(8, 1, from, to, hit) != 0) {
        obj->speed = 0;
    }
    obj->x = hit[0] << 12;
    obj->y = hit[1] << 12;
    obj->z = hit[2] << 12;
}

static inline void spark_add_s16(s32 x, s32 y, s32 z, s32 value, s32 ry, s16 rx, s32 colour) {
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
        s->roll = 0;
    }
}
static inline void offset_point(Vec3 *out, s32 *base, s32 yaw, s32 pitch, s32 dist) {
    out->x = 0;
    out->y = 0;
    out->z = dist;
    rotate_xz_twice(yaw, pitch, &out->x, &out->y, &out->z);
    out->x += base[0];
    out->y += base[1];
    out->z += base[2];
}
/* A spark at the object, then three along its facing (0x30 and 0x10 ahead). */
void spark_burst_draw(Object *obj, ObjHandler *handler) {
    s32 base[3];
    Vec3 off;
    s32 value, yaw;
    s32 dist;
    s16 pitch;
    s32 pitch_arg;

    base[0] = obj->x >> 12;
    base[1] = obj->y >> 12;
    base[2] = obj->z >> 12;
    pitch = obj->pitch;
    pitch_arg = pitch;
    yaw = obj->yaw + 0x800;
    value = obj->vars.ranged.unk_24C;
    spark_add_s16(base[0], base[1], base[2], value, yaw + 0x800, pitch, 0);
    offset_point(&off, base, yaw, pitch_arg, 0x30);
    spark_add_s16(off.x, off.y, off.z, value - 2, 0x800, 0, 0);
    dist = 0x10;
    spark_add_s16(off.x, off.y, off.z, value - 9, 0x800, 0, 0x800010);
    offset_point(&off, base, yaw, pitch_arg, dist);
    spark_add_s16(off.x, off.y, off.z, value - 5, 0x800, 0, 0x801010);
}

/* Frees the object once the function of its index (obj_hit_damage) reports a positive result. */
void func_800BC528(Object *obj, ObjHandler *handler) {
    if ((obj_hit_damage(obj->index) << 16) > 0) {
        obj_free(obj);
    }
}

static inline void fire_ranged_shot(Object *obj, VECTOR *pos) {
    SVECTOR ang;
    s32 rnd, base;

    ang.pad = obj->damage;
    pos->vx = 0;
    pos->vy = (-(s16)obj->height * 2) / 5;
    pos->vz = 0xA3;
    obj_offset_to_world_shifted(obj, (s32 *)pos);
    dir_to_angles((Vec3 *)pos, &ang);
    ang.vy = angle_approach(obj->yaw, ang.vy, 0x60);
    ang.vx = angle_approach(obj->pitch, ang.vx, 0xC0);
    rnd = rand_a_next();
    base = (u16)ang.vy - 0x10;
    ang.vy = base + rnd % 32;
    rnd = rand_a_next();
    base = (u16)ang.vx - 0x10;
    ang.vx = base + rnd % 32;
    pos->pad = obj->vars.enemy.unk_25E;
    obj_spawn_ranged(model_slot_pchr(*(s32 *)obj->asset) + 0x8A, (s32 *)pos, (u16 *)&ang);
}
void ranged_shot_fire(Object *obj) {
    VECTOR pos;

    fire_ranged_shot(obj, &pos);
}

void projectile_fly_update(Object *obj, ObjHandler *handler);
void spark_burst_draw(Object *obj, ObjHandler *handler);
s32 obj_spawn_ranged(s32 param, s32 *pos, u16 *rot) {
    Object *obj;
    s32 range;
    s32 clamped;
    u16 roll;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj_hit_clear(obj->index);
    obj->vars.ranged.unk_24C = param;
    obj->damage = rot[3];
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    roll = rot[2];
    obj->speed = 0x28;
    obj->roll = roll;
    range = pos[3] / 40;
    obj->vars.ranged.range_remaining = range;
    clamped = range;
    if (range >= 0x41) {
        clamped = 0x40;
    }
    if (clamped >= 0x10) {
        if (range >= 0x41) {
            range = 0x40;
        }
    } else {
        range = 0x10;
    }
    obj->handlers[2].fn = func_800BC528;
    obj->handlers[1].fn = projectile_fly_update;
    obj->vars.ranged.range_remaining = range;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = spark_burst_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj_set_flags(obj, 0x80);
    spot_effect_start(pos);
    return 1;
}

void ranged_shot_fire(Object *obj);
/* Mode 1 hands off to ranged_shot_fire. Otherwise: if the 0x268 word is
   unset, seed it with 0x100, then store a random 6 or 7 as a byte at 0x256. */
void obj_set_mode(Object *obj, s32 mode) {
    if (mode != 0 && mode == 1) {
        ranged_shot_fire(obj);
        return;
    }
    if (obj->vars.snd2.sound[0] == 0) {
        obj->vars.snd2.sound[0] = 0x100;
    }
    *(s8 *)&obj->vars.h.unk_256 = (s8)((rand_a_next() % 2) + 6);
}
extern s32 zone_spark_base;
extern s32 zone_blend_base;
extern AngleBlendEntry *zone_table;
extern s32 point_base;
extern Object *slot_objs[];
void zone_trigger_check(Object *obj, ObjHandler *handler);
void spark_line_draw(Object *obj, ObjHandler *handler);
void obj_fade_level_update(Object *obj, ObjHandler *handler);
void obj_blend_angles(Object *obj, ObjHandler *handler);

/* Spawns one object per 16-byte entry of the table until unk_0C == -1 (the caller's
 * req_entry_table). unk_00..unk_08 are the position (<< 12), unk_0C the kind and param. */
s32 obj_spawn_table(DrawReqEntry *spawn, AngleBlendEntry *blend, s32 arg2) {
    Object *obj;
    s32 index;
    s32 info;
    s32 i;

    index = 0;
    zone_spark_base = point_base;
    zone_blend_base = arg2;
    zone_table = blend;
    for (i = 63; i >= 0; i--) {
        slot_objs[i] = NULL;
    }

    while (spawn->unk_0C != -1) {
        obj = obj_new();
        if (obj == NULL) {
            return 0;
        }
        list_insert_after((Node *)get_obj_list_b(), &obj->node);
        obj->handlers[0].fn = zone_trigger_check;
        obj->handlers[1].fn = obj_fade_level_update;
        obj->handlers[2].fn = obj_blend_angles;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = spark_line_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->x = spawn->x << 12;
        obj->y = spawn->y << 12;
        obj->z = spawn->z << 12;
        obj->solid_id = solid_alloc();
        obj->vars.table.blend_amount = 0x1000;
        obj->vars.table.unk_252 = 0;
        obj->vars.table.unk_248 = index;
        obj->vars.table.entry_index = (u8)spawn->unk_0C;
        info = spawn->unk_0C;
        obj->vars.table.unused_254 = 0;
        obj->vars.table.unk_24E = 1;
        *(u8 *)&obj->vars.table.unk_256 = 1;
        ((u8 *)&obj->vars.table.unk_256)[1] = 0;
        obj->vars.table.unk_24C = info >> 8;
        slot_objs[index] = obj;
        index++;
        spawn++;
    }
    return 1;
}

void obj_set_state_2(Object *obj) {
    if (*(u8 *)&obj->vars.table.unk_256 != 0) {
        if (*(s16 *)&obj->vars.table.unk_24E != 2) {
            sound_attach(sound_start(SND_OBJECT_STATE_CHANGE | SND_GROUP(1), 0x60, 0, 0), &obj->x, NULL);
        }
        *(s16 *)&obj->vars.table.unk_252 = -0x80;
        *(s16 *)&obj->vars.table.unk_24E = 2;
    }
}

void obj_set_state_1(Object *obj) {
    StatusView *v = (StatusView *)&obj->vars;

    if (v->unk_256 != 0) {
        if (v->unk_24E != 1) {
            sound_attach(sound_start(SND_OBJECT_STATE_CHANGE | SND_GROUP(1), 0x60, 0, 0), &obj->x, NULL);
        }
        v->unk_252 = 0x80;
        v->unk_24E = 1;
    }
}

extern Object *slot_objs[];
void slot_set_state_2(s32 idx) {
    Object *obj;

    obj = slot_objs[idx];
    if (obj != NULL) {
        if (obj->vars.turn.yaw != 2) {
            sound_attach(sound_start(SND_OBJECT_STATE_CHANGE | SND_GROUP(1), 0x60, 0, 0), &obj->x, NULL);
        }
        *(s16 *)&obj->vars.stage.unk_252 = -0x80;
        *((u8 *)obj + 0x256) = 0;
        obj->vars.turn.yaw = 2;
    }
}

/* Restarts the object in slot `index`: starts sound 0x3005 on its position
 * if it was not already marked 1 at 0x24E, then sets the halfwords at 0x252
 * and 0x24E and clears the byte at 0x256. */
void slot_restart(s32 index) {
    Object *obj;

    obj = slot_objs[index];
    if (obj != NULL) {
        if (*(s16 *)&obj->vars.stage.unk_24E != 1) {
            sound_attach(sound_start(SND_OBJECT_STATE_CHANGE | SND_GROUP(1), 0x60, 0, 0), &obj->x, NULL);
        }
        obj->vars.stage.unk_252 = 0x80;
        *((u8 *)obj + 0x256) = 0;
        obj->vars.stage.unk_24E = 1;
    }
}

extern Object *slot_objs[];
s32 slot_get_value(s32 idx, s32 *out) {
    Object *obj;
    u8 result;

    obj = slot_objs[idx];
    result = 0;
    if (obj != NULL) {
        *out = obj->vars.stage.unk_254;
        result = *((u8 *)obj + 0x257);
    }
    return result;
}

s32 slot_find_flagged(void) {
    s32 i;

    /* Index of the first object in the table with byte 0x257 set, or -1.
     * 0x257 is the high byte of vars.h.unk_256 (no name yet). */
    i = 0;
    if (slot_objs[0] != NULL) {
        do {
            if (slot_objs[i]->vars.turn.pad_250[7] != 0) {
                return i;
            }
            i++;
        } while (slot_objs[i] != NULL);
    }
    return -1;
}

extern AngleBlendEntry *zone_table;
/* Hard-register locals pin the object to $s2 and the distance to $v0, where the original keeps them. */
void zone_trigger_check(Object *obj, ObjHandler *handler) {
    register Object *self asm("$18") = obj;
    AngleBlendEntry *zone = &zone_table[self->vars.table.entry_index];
    s32 *player = player_position();
    s32 dx = self->x / 0x1000 + zone->x - player[0];
    s32 dz = self->z / 0x1000 + zone->z - player[2];
    s32 half;
    s32 limit;
    s32 back;
    s32 sign;
    register s32 dist asm("$2");

    half = (s16)zone->width / 2;
    limit = zone->limit;
    back = -zone->back;
    self->vars.spin.pad_257[0] = 0;
    if (zone->axis == 0) {
        if (ABS(dx) < half && dz < limit && back < dz) {
            dist = isqrt(length_sq(dx, 0, dz));
            sign = dz < 0 ? -1 : 1;
            goto hit;
        }
    } else if (ABS(dz) < half && dx < limit && back < dx) {
        dist = isqrt(length_sq(dx, 0, dz));
        sign = dx < 0 ? -1 : 1;
hit:
        self->vars.spin.pad_257[0] = 1;
        self->vars.enemy.sound_channel[0] = dist * sign;
        obj_set_state_2(self);
        return;
    }
    obj_set_state_1(self);
}

void obj_fade_level_update(Object *obj, ObjHandler *handler) {
    s32 sum, level, lim;
    s16 cur;

    sum = obj->vars.fade.level;
    sum += obj->vars.fade.step;
    level = sum < 0x1001 ? sum : 0x1000;
    lim = sum < 0x1001 ? sum : 0x1000;
    if (lim < 0) {
        level = 0;
    }
    sum = level;
    cur = sum;
    obj->vars.fade.level = cur;
    if (obj->vars.fade.step < 0 && cur == 0) {
        aobj_set_flag(get_rec_id(obj->vars.fade.aobj / 256) + (u8)obj->vars.fade.aobj, 0);
        obj->vars.fade.step = 0;
    }
    if (obj->vars.fade.step > 0 && obj->vars.fade.level == 0x1000) {
        aobj_set_flag(get_rec_id(obj->vars.fade.aobj / 256) + (u8)obj->vars.fade.aobj, 1);
        obj->vars.fade.step = 0;
    }
}

extern AngleBlendEntry *zone_table;
extern s32 zone_blend_base;
/* Blends two scratch pairs of angles from a table entry and the object's 0x250 fraction, then
 * runs the follow-up solid_setup_scratch / fn_800FB460 calls on the object's 0xA4 block. */
void obj_blend_angles(Object *obj, ObjHandler *handler) {
    s16 *from = scratch_alloc(4);
    s16 *frac = scratch_alloc(4);
    AngleBlendEntry *entry = zone_table;
    s32 base = zone_blend_base;
    u8 *block = (u8 *)obj + 0xA4;
    s16 amount;
    s32 res;
    s32 kind;

    if (base >= 0) {
        amount = obj->vars.table.blend_amount;
        frac[0] = amount;
        if (amount != 0 && amount != 0x1000) {
            frac[1] = 0x1000 - amount;
            entry = &entry[obj->vars.table.entry_index];
            from[0] = entry->unk_12 + base;
            from[1] = entry->unk_16 + base;
            res = solid_add(from, frac, 0x1000, entry);
            kind = obj->index;
            block[1] = 4;
            block[0] = kind;
            ((void (*)())obj_block_fill)(obj, block, kind);
            solid_setup_scratch(obj->solid_id, block, (s16)res, 0x1000);
            fn_800FB460(obj, block);
        }
    }
    scratch_top -= 0x8;
}

extern s32 zone_spark_base;
extern s32 zone_blend_base;
extern AngleBlendEntry *zone_table;
extern Object *slot_objs[];
void zone_trigger_check(Object *obj, ObjHandler *handler);
void spark_line_draw(Object *obj, ObjHandler *handler);
void obj_fade_level_update(Object *obj, ObjHandler *handler);
void obj_blend_angles(Object *obj, ObjHandler *handler);
/* Emits a row of entry->count sparks from the object's position, spaced by entry->step along x
 * (axis 0) or z, all with the model blended from the entry's two keys by the 0x250 fraction.
 * value holds the first key and then the blend, as the original keeps both in one register. */
void spark_line_draw(Object *obj, ObjHandler *handler) {
    AngleBlendEntry *entry;
    s32 count;
    s32 dx = 0;
    s32 dz = 0;
    s32 x, y, z;
    s32 value;
    s32 colour;
    s32 key_b;
    s32 base;

    entry = zone_table;
    entry += obj->vars.table.entry_index;
    base = zone_spark_base;
    count = entry->count;
    value = entry->unk_10 + base;
    key_b = entry->unk_14 + base;
    x = obj->x / 0x1000;
    y = obj->y / 0x1000;
    z = obj->z / 0x1000;
    value = pchr_blend(value, key_b, (s16)obj->vars.table.blend_amount, 1);
    colour = 0;
    if (entry->axis == 0) {
        dx = entry->step;
    } else {
        dz = entry->step;
    }
    while (count > 0) {
        spark_add(x, y, z, 0, 0, 0, value, colour);
        x += dx;
        count--;
        z += dz;
    }
}

extern s32 slot_range_min_table[];
extern s32 slot_range_max_table[];
/* Is the object's position (unk_04 >> 12) strictly inside range i's bounds? */
s32 slot_obj_in_range(void *obj, s32 i) {
    register s32 inside asm("v0") = 0;
    s32 lo = slot_range_min_table[i * 3];
    s32 hi = slot_range_max_table[i * 3];
    s32 x = (s32)((Object *)obj)->type.pc >> 12;
    if (lo < x) {
        inside = x < hi;
    }
    return inside;
}

s32 slot_obj_in_range(void *obj, s32 i);
s32 obj_list_mark_matching(s32 arg0) {
    GridEntry **list;
    s32 count;
    s32 i;
    s32 marked;
    u8 *obj;

    list = slot_list_get();
    count = slot_list_count();
    marked = 0;
    for (i = 0; i < count; i++) {
        obj = (u8 *) list[i];
        if (slot_obj_in_range(obj, arg0) != 0) {
            marked++;
            obj[4] = (obj[4] & 0xFC) | 1;
        }
    }
    return marked;
}

s32 slot_obj_in_range(void *obj, s32 i);
void obj_list_flag_matching(s32 arg0) {
    GridEntry **list;
    s32 count;
    s32 i;
    u8 *obj;
    s16 pad;

    list = slot_list_get();
    count = slot_list_count();
    for (i = 0; i < count; i++) {
        obj = (u8 *) list[i];
        if (slot_obj_in_range(obj, arg0) != 0) {
            obj[4] |= 3;
        }
    }
}

s32 slot_list_count(void);

void slot_mark_all(void) {
    GridEntry **list = slot_list_get();
    s32 count = slot_list_count();
    s32 i;

    for (i = 0; i < count; i++) {
        FlagRecord04 *rec = (FlagRecord04 *)list[i];
        rec->flags = (rec->flags & 0xFC) | 2;
    }
}


extern Rec8011016E mission_bonus_table[];
extern s32 mission_bonus_msg_ids[];
void mission_time_bonus_show(s32 arg0) {
    s32 v = (s16)mission_bonus_table[arg0].value;
    mission_timer_set(mission_timer_get() + v * 60);
    v = v / 10 - 2;
    v = MAX(MIN(v, 6), 0);
    msg_show_at(12, 0x42, msg_slot_to_id(mission_bonus_msg_ids[v]), 0x78, 0x88);
}

extern ClampRange slot_enemy_limits[5];
extern s32 slot_enemy_total;
extern s32 slot_kill_base;
extern s32 slot_kills;
extern s32 stage_enemies_left;
void stage_update_enemies_left(s32 index) {
    s32 cap = slot_enemy_total;
    s32 limit;
    s32 kills;

    kills = get_kill_count() - slot_kill_base;
    limit = slot_enemy_limits[index].low;
    slot_kills = kills;
    if (cap < limit) {
        limit = cap;
    }
    stage_enemies_left = limit - kills;
    stage_enemies_left = MAX(MIN(stage_enemies_left, 99), 0);
}

extern s32 stage_list_index;
extern s32 slot_enemy_total;
extern s32 slot_kill_base;
void stage_update_enemies_left(s32 index);
extern u8 *stage_draw_lists[];
extern u8 *stage_load_lists[];
/* Runs two 0xFF-terminated byte lists for slot `index`, calling slot_restart on each byte. */
void slot_restart_lists(s32 index) {
    u8 *list;
    u8 byte;

    stage_list_index = index;
    slot_enemy_total = obj_list_mark_matching(index);
    slot_kill_base = get_kill_count();
    stage_update_enemies_left(index);
    list = stage_draw_lists[index];
    byte = *list;
    if ((byte & 0xFF) != 0xFF) {
        do {
            slot_restart(byte);
            list++;
            byte = *list;
        } while (byte != 0xFF);
    }
    list = stage_load_lists[index];
    byte = *list;
    if ((byte & 0xFF) != 0xFF) {
        do {
            slot_restart(byte);
            list++;
            byte = *list;
        } while (byte != 0xFF);
    }
}

void stage_list_flag_objs(s32 arg0) {
    obj_list_flag_matching(arg0);
}

extern s32 cam_zone_table[3][6];
/* Returns 1 if the camera position (12 fractional bits dropped) lies inside any zone. */
s32 cam_in_zone(void) {
    s32 i;
    s32 inside;
    s32 *zone;
    s32 cam_x;
    s32 cam_y;
    s32 cam_z;

    cam_x = cam_pos >> 12;
    cam_z = cam_pos_y >> 12;
    cam_y = cam_pos_z >> 12;
    zone = &cam_zone_table[0][0];
    for (i = 0; i < 3; i++, zone += 6) {
        if (cam_x < zone[0] || zone[1] < cam_x || cam_z < zone[2] || zone[3] < cam_z ||
            cam_y < zone[4] || zone[5] < cam_y) {
            inside = 0;
        } else {
            inside = 1;
        }
        if (inside) {
            return 1;
        }
    }
    return 0;
}

s32 cam_in_zone(void);
void cam_zone_update(void) {
    s32 flag;
    s32 i;

    flag = cam_in_zone() == 0;
    if (flag != scene_model_get_flag(0)) {
        for (i = 0; i < 6; i++) {
            scene_model_set_flag(i, flag);
        }
        for (i = 0; i < 3; i++) {
            rec_set_value(i, flag);
        }
        rec_set_on(0, flag);
        rec_set_flag(0, flag);
    }
}

void stage_mode_on(void) {
    slot_restart(0);
    set_stage_flags(get_stage_flags() | 8);
    set_mission_active(0);
    slot_restart_lists(0);
}

void stage_hold_slot0(void) {
    slot_set_state_2(0);
    set_stage_flags(get_stage_flags() & ~8);
    set_mission_active(1);
}

void rec_init_xyz(Rec800BE394 *r, s32 x, s32 y, s32 z);
extern s32 jtbl_80118474;
extern s32 D_80118478;
extern s32 mission_effect;
extern DrawReqEntry req_entry_table[];
extern s32 D_8010FF00;
extern AngleBlendEntry D_8010FF20[];
extern u32 stage_data_buf[5];
void mission_update(Object *obj, ObjHandler *handler);
void stage_draw_all(void);
void mission_state_set(u32 arg0);
void eng_set_mode(u32 arg0);
void stage_init(void) {
    Object *obj;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_b(), &obj->node);
        obj->handlers[2].fn = mission_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) stage_draw_all;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        set_mission_score(0);
        stage_list_index = 0;
        set_kill_count(0);
        set_mission_limit(slot_list_count());
        obj_spawn_table(req_entry_table, D_8010FF20, D_8010FF00);
        set_msg_enabled(0);
        set_view_rect(3, 0x85, 0x4E, 0x46);
        slot_mark_all();
        stage_mode_on();
        jtbl_80118474 = 0;
        D_80118478 = 0;
        mission_timer_set(0xE10);
        mission_state_set(2);
        mission_timer_active_set(1);
        eng_set_mode(3);
        pursue_flag_set(1);
        rec_init_xyz((Rec800BE394 *) &mission_effect, 0, 0, -1);
        rec_table_set_enabled(0);
        set_data_base((s32) stage_data_buf);
    }
}

extern ClampRange slot_enemy_limits[5];
extern s32 draw_list_index;
s32 stage_load_params(s16 *values) {
    s32 i;
    s32 v;

    for (i = 0; i < 5; i++) {
        v = values[i + 10];
        slot_enemy_limits[i].low = v % 256;
        slot_enemy_limits[i].high = v / 256;
    }
    for (i = 0; i < 6; i++) {
        clamp_set_max_x(i, 1);
    }
    draw_list_index = -1;
    return 1;
}

extern u8 *stage_load_lists[];
/* Walks the 0xFF-terminated byte list at table[idx]. Returns 1 as soon as
   an entry decodes with a value below -0x200, otherwise 0. */
s32 stage_list_any_below(s32 idx) {
    s32 value;
    u8 *p;
    u8 c;

    p = stage_load_lists[idx];
    c = *p;
    if (c != 0xFF) {
        do {
            if (slot_get_value(c, &value) != 0) {
                p++;
                if (value < -0x200) {
                    return 1;
                }
            } else {
                p++;
            }
            c = *p;
        } while (c != 0xFF);
    }
    return 0;
}

void stage_load_list(s32 index) {
    u8 *list;
    u8 entry;

    list = stage_load_lists[index];
    entry = *list;
    if (entry != 0xFF) {
        do {
            list++;
            slot_set_state_2(entry);
            entry = *list;
        } while (entry != 0xFF);
    }
    draw_list_index = index + 1;
}

extern s32 slot_kills;
extern s32 stage_enemies_left;
extern s32 mission_text_base;
void cam_zone_update(void);
void mission_time_bonus_show(s32 arg0);
void stage_hold_slot0(void);
void effect_fade_update(EffectObj *e);
void stage_load_list(s32 index);
s32 stage_list_any_below(s32 idx);
/* Mission driver for the stage: a coroutine (CoItem jtbl_80118474) that shows the mission
 * messages, then loads each list of enemies in turn, awards a bonus when all are dead. */
void mission_update(Object *obj, ObjHandler *handler) {
    CoItem *item;
    s32 unused[2];
    void *target;
    s32 i;
    s32 flag;

    cam_zone_update();
    stage_update_enemies_left(stage_list_index);
    if (stage_list_index != 5) {
        set_enemies_left(stage_enemies_left);
        flag = 1;
    } else {
        flag = 0;
    }
    pursue_flag_set(flag);
    item = (CoItem *)&jtbl_80118474;

    if (item->resume[item->level] != NULL) {
        goto *item->resume[item->level];
    }
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&intro_a;
    goto after_b;
intro_a:
    sound_start(SND_MISSION_START_JINGLE, 0x7F, 0, 0);
    msg_show_at(-0x20, -0x14, mission_text_base + 0x70, 0x34, 0);
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&intro_b;
after_b:
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&timer_start;
    goto timer_start;
intro_b:
    msg_show_at(-0x20, -0x14, mission_text_base + 0x71, 0x20, 0);
    stage_hold_slot0();
main_loop:
    item->resume[item->level] = &&check_start;
check_start:
    if (stage_enemies_left != 0 || stage_list_index == 5) {
        goto finish;
    }
    rec_init_xyz((Rec800BE394 *)&mission_effect, 0, -0x14, mission_text_base + 0x62);
    stage_load_list(stage_list_index);
    item->resume[item->level] = &&check_clear;
check_clear:
    if (slot_enemy_total == slot_kills) {
        add_score(0xC350);
        sound_start(SND_MISSION_CLEAR_JINGLE | SND_GROUP(1), 0x7F, 0, 0);
        rec_init_xyz((Rec800BE394 *)&mission_effect, 0, -0x14, mission_text_base + 0x64);
        item->resume[item->level] = &&check_list;
    }
check_list:
    if (stage_list_any_below(stage_list_index) == 0) {
        goto finish;
    }
    draw_list_index = -1;
    mission_time_bonus_show(stage_list_index);
    stage_list_flag_objs(stage_list_index++);
    if (stage_list_index == 5) {
        for (i = 0; i < 5; i++) {
            clamp_set_max_x(i, 0);
        }
    }
    mission_score_add(1);
    slot_restart_lists(stage_list_index);
    goto main_loop;
timer_start:
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&timer_wait;
    item->count[item->level] = 0x3B;
timer_wait:
    if (--item->count[item->level] < 0) {
        item->level = (item->level - 1) & 7;
        item->level = (item->level - 1) & 7;
        target = item->resume[item->level];
        item->level = (item->level - 1) & 7;
        goto *target;
    }
finish:
    effect_fade_update((EffectObj *)&mission_effect);
    if (mission_timer_get() <= 0) {
        set_stage_end(3);
    }
}

/* Maps a value to a tier: 3 for 100 and up, 2 for 10 to 99, 1 below 10. */
s32 get_value_tier(s32 value) {
    s32 tier = 1;

    if (value >= 100) {
        tier = 3;
    } else if (value >= 10) {
        tier = 2;
    }
    return tier;
}

/* Pushes count IdRecords along a row: each at (x, y), scale 0x1000, linked into
 * a random bucket, its colour the next decimal digit of seed (lowest first) plus
 * base and mission_text_base. x steps back by step per record. */
void id_table_add_row(s32 x, s32 y, s32 seed, s32 count, s32 base, s32 step) {
    IdTable *tbl;
    IdRecord *rec;
    s32 digit;
    s32 packed;
    s32 index;
    s32 slot;
    s32 off;
    s32 scale;

    if (count <= 0) {
        return;
    }
    scale = 0x1000;
    do {
        /* digit = seed % 10; the quotient stays in LO for the mflo below */
        div10_rem(digit, seed, 8);
        digit += base;
        packed = id_table_default_bucket() << 24;
        __asm__ volatile("");
        digit += mission_text_base;
        __asm__ volatile("");
        __asm__ volatile("" : "=r"(tbl) : "0"(&id_table));
        index = tbl->count;
        slot = packed >> 24;
        if (index < 0x100) {
            tbl->count = index + 1;
            do {
            } while (0);
            off = index * 0x14 + 0x24;
            rec = (IdRecord *)((u8 *)tbl + off);
            rec->prev_id = tbl->id[slot];
            tbl->id[slot] = index;
            rec->field_00 = x;
            rec->field_02 = y;
            rec->field_04 = scale;
            rec->field_0E = digit;
            rec->field_08 = 0;
            rec->field_0A = 0;
            rec->field_0C = 0;
            rec->field_10 = packed;
        }
        /* seed /= 10 */
        mips_mflo(seed);
        count--;
        x -= step;
    } while (count > 0);
}

/* Pushes one IdRecord at (x, y) into the bucket in packed's top byte. */
static inline void id_table_push_glyph(s32 x, s32 y, s32 scale, s32 depth, s32 packed) {
    IdTable *tbl;
    IdRecord *rec;
    s32 index;
    s32 slot;
    s32 off;

    __asm__ volatile("" : "=r"(tbl) : "0"(&id_table));
    index = tbl->count;
    slot = packed >> 24;
    if (index < 0x100) {
        tbl->count = index + 1;
        do {
        } while (0);
        off = index * 0x14 + 0x24;
        rec = (IdRecord *)((u8 *)tbl + off);
        rec->prev_id = tbl->id[slot];
        tbl->id[slot] = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = depth;
        rec->field_08 = 0;
        rec->field_0A = 0;
        rec->field_0C = 0;
        rec->field_10 = packed;
    }
}

/* Mission result screen: pushes two glyphs (the second offset by the mission
 * score) then four number rows: slot_enemy_total, slot_kills, kills and the
 * mission completion percentage. */
void result_table_build(void) {
    s32 scale;
    s32 glyph_x;
    s32 glyph_y;
    s32 score_x;
    s32 score_y;
    s32 depth;
    s32 packed;
    s32 value;
    s32 percent;

    depth = mission_text_base;
    packed = id_table_default_bucket() << 24;
    glyph_x = 3;
    glyph_y = 4;
    scale = 0x1000;
    __asm__ volatile("");
    depth += 0x61;
    __asm__ volatile("");
    id_table_push_glyph(glyph_x, glyph_y, scale, depth, packed);

    score_x = 0x2B;
    score_y = 2;
    depth = get_mission_score();
    packed = id_table_default_bucket();
    __asm__ volatile("");
    packed <<= 24;
    __asm__ volatile("");
    depth += 0x31;
    depth += mission_text_base;
    __asm__ volatile("");
    id_table_push_glyph(score_x, score_y, scale, depth, packed);

    value = slot_enemy_total;
    id_table_add_row(0x23, 0xE, value, get_value_tier(value), 0x30, 8);
    value = slot_kills;
    id_table_add_row(0xB, 0xE, value, get_value_tier(value), 0x50, 8);
    value = get_kill_count();
    id_table_add_row(0x2F, 0x2C, value, get_value_tier(value), 0x20, 0xE);
    percent = 0;
    if (get_mission_total() != 0) {
        percent = get_mission_count() * 100 / get_mission_total();
    }
    id_table_add_row(0x2F, 0x3C, percent, get_value_tier(percent), 0x20, 0xE);
}

extern s32 draw_list_index;
extern u8 *stage_draw_lists[];
extern DrawReqEntry req_entry_table[];
void stage_draw_list(void) {
    u8 *p;
    u8 id;
    if (draw_list_index > 0) {
        p = stage_draw_lists[draw_list_index];
        id = *p;
        if (id != 0xFF) {
            do {
                p++;
                req_queue_push(req_entry_table[id].x, req_entry_table[id].y, req_entry_table[id].z, 4);
                id = *p;
            } while (id != 0xFF);
        }
    }
}

extern s32 mission_effect;
void result_table_build(void);
void id_table_append(s32 *table);
void stage_draw_list(void);
/* Calls result_table_build, then id_table_append with the table at mission_effect, then stage_draw_list. */
void stage_draw_all(void) {
    result_table_build();
    id_table_append(&mission_effect);
    stage_draw_list();
}

void rec_init_xyz(Rec800BE394 *r, s32 x, s32 y, s32 z) {
    r->x0 = x;
    r->y0 = y;
    r->x1 = x;
    r->y1 = y;
    r->scale = 0x1000;
    r->z = z;
    r->unk_E = 0;
    r->unk_10 = 0;
    r->unk_12 = 0;
    r->unk_14 = 0;
    r->unk_18 = 0;
}

void effect_fade_update(EffectObj *e) {
    CoItem *co;
    s32 unused[2]; /* the original's 8-byte stack frame (no locals are used) */

    if (e->active < 0) {
        return;
    }
    co = &e->co;
    if (co->resume[co->level] != NULL) {
        goto *co->resume[co->level];
    }
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&fade_in;
    co->count[co->level] = 0x1F;
fade_in:
    e->unk_0A = e->base + co->count[co->level & 7];
    e->unk_0C = (0x20 - co->count[co->level & 7]) << 7;
    e->unk_10 = co->count[co->level & 7] << 5;
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (co->level - 1) & 7;
    e->unk_0C = 0x1000;
    e->unk_0E = 0;
    e->unk_10 = 0;
    e->unk_0A = e->base;
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&fade_hold;
    co->count[co->level] = 0x3B;
fade_hold:
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (co->level - 1) & 7;
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&fade_out;
    co->count[co->level] = 0xF;
fade_out:
    e->unk_0E = (0x10 - co->count[co->level & 7]) << 6;
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (co->level - 1) & 7;
    e->active = -1;
}

/* Appends a 0x14-byte record to id_table when the request's flag is non-negative.
 * The old head id goes into the record's prev_id and the new index becomes the head. */
void id_table_append(s32 *table) {
    IdRequest *req = (IdRequest *)table;
    IdTable *tbl;
    s32 index;
    s32 flag;
    s32 f08;
    s32 f0A;
    s32 f0C;
    s32 f0E;
    s32 f10;
    s32 f12;
    s32 off;
    IdRecord *rec;

    flag = req->flag_04;
    if (flag >= 0) {
        f08 = req->field_08;
        f0A = req->field_0A;
        f0C = req->field_0C;
        f0E = req->field_0E;
        f10 = req->field_10;
        f12 = req->field_12;
        /* scheduling barrier: keeps the request loads ahead of the table address */
        do {
        } while (0);
        tbl = &id_table;
        FAKE_OPAQUE(tbl);
        index = tbl->count;
        FAKE_OPAQUE(index);
        if (index < 0x100) {
            tbl->count = index + 1;
            do {
            } while (0);
            off = index * 0x14 + 0x24;
            FAKE_OPAQUE(off);
            rec = (IdRecord *)((u8 *)tbl + off);
            rec->prev_id = tbl->id[0];
            tbl->id[0] = index;
            rec->field_00 = f08;
            rec->field_02 = f0A;
            rec->field_04 = f0C;
            rec->field_0E = flag;
            rec->field_08 = f0E;
            rec->field_0A = f10;
            rec->field_0C = f12;
            rec->field_10 = 0;
        }
    }
}
