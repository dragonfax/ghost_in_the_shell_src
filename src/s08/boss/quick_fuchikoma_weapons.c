/* quick_fuchikoma_weapons: one of s08's own original source files (scripts/objmap.py); part of src/s08/main.c's unit, included there. */

extern s32 quick_fuchikoma_back_offset;
extern s32 laser_spark_speed;
extern s32 D_80120178;

void quick_fuchikoma_m8_boss_set_defaults(void) {
    quick_fuchikoma_back_offset = 0x2D;
    laser_spark_speed = 0x96;
    D_80120178 = 0;
}

s32 obj_check_move(Object *obj, s32 *pos, s32 *next, s32 *hit, s32 flags, s32 expect);
void laser_update(Object *obj, ObjHandler *handler) {
    s32 *pos = scratch_alloc(0x30);
    s32 *next = pos + 4;
    s32 *hit = pos + 8;
    s32 result;
    s32 angle;

    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;

    if (world_flag_get() == 1) {
        pos[0] >>= 12;
        pos[1] >>= 12;
        pos[2] >>= 12;
        impact_spawn(pos, 0x400, 0x100, 0x1770);
    } else {
        next[0] = pos[0] + obj->vx;
        next[1] = pos[1] + obj->vy;
        next[2] = pos[2] + obj->vz;
        obj->x = next[0];
        obj->y = next[1];
        obj->z = next[2];

        pos[0] >>= 12;
        pos[1] >>= 12;
        pos[2] >>= 12;
        next[0] >>= 12;
        next[1] >>= 12;
        next[2] >>= 12;

        result = obj_check_move(obj, pos, next, hit, 0xC, 1);
        switch (result) {
        case 3:
            sound_play_at_units(SND_LASER_IMPACT | SND_GROUP(2), 0x7F, 0x3C, hit);
            impact_spawn(pos, 0x400, 0x100, 0x1770);
            break;
        case 4:
            sound_play_at_units(SND_LASER_IMPACT | SND_GROUP(2), 0x7F, 0x3C, hit);
            impact_spawn(hit, 0x400, 0x100, 0x1770);
            angle = atan2(hit[2] - pos[2], hit[0] - pos[0]);
            hit_target_masked(0, 1, angle, obj->damage);
            break;
        case 1:
            break;
        default:
            scratch_top -= 0x30;
            return;
        }
    }
    obj_free(obj);
    scratch_top -= 0x30;
}

void s08_laser_draw(Object *obj, ObjHandler *handler) {
    SparkList *list = &spark_list;
    s32 x, y, z, yaw, pitch, colour;

    x = obj->x;
    y = obj->y;
    z = obj->z;
    yaw = obj->yaw;
    pitch = obj->pitch;
    x >>= 12;
    y >>= 12;
    z >>= 12;

    spark_add_head(list, x, y, z, yaw, pitch, 0, obj->vars.snd.unk_248, 0);
    colour = 0xA0A0A;
    y = -0x840;
    spark_add_head(list, x, y, z, yaw, -pitch, 0, obj->vars.snd.unk_248, colour);
}

void laser_update(Object *obj, ObjHandler *handler);
s32 laser_spawn(s32 *pos, u16 *rot) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    sound_play_at_units(SND_PAIR(SND_LASER_FIRE | SND_GROUP(1), SND_LASER_FIRE_ALT | SND_GROUP(1)), 0x7F, 0x3C, pos);
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    obj->roll = rot[2];
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->handlers[1].fn = laser_update;
    obj->unk_17A = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = s08_laser_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->vars.words[0] = get_model_slot_base() + 9;
    angles_to_vector(obj->yaw, obj->pitch, 0x38, &obj->vx, &obj->vy, &obj->vz);
    obj->damage = 0xC;
    return 1;
}

void obj_bone_pos(Object *obj, s32 idx, Vec3 *out);
void laser_spawn_random(Object *obj) {
    s32 *pos = scratch_alloc(0x20);
    s16 *rot = scratch_alloc(8);
    s32 *mat = scratch_alloc(0x20);
    s32 *vel = pos + 4;
    s32 a, b, c, back;

    rot[0] = rand_a_next() * 0xC0 / 0x1000 - 0x40;
    rot[1] = rand_a_next() / 8 - 0x100;
    rot[2] = 0;
    rot_matrix(mat, rot[1], rot[0], 0);
    mul_matrix(world_matrix_get(), mat, mat);
    matrix_to_angles(mat, pos + 5, vel, pos + 6);
    rot[0] = pos[4];
    rot[1] = pos[5];
    rot[2] = pos[6];
    back = -quick_fuchikoma_back_offset;
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = back;
    obj_bone_pos(obj, 0x19, (Vec3 *)pos);
    pos[0] = (obj->x >> 12) + pos[0];
    pos[1] = (obj->y >> 12) + pos[1];
    pos[2] = (obj->z >> 12) + pos[2];
    pos[4] = 0;
    pos[5] = 0;
    pos[6] = laser_spark_speed;
    a = ((volatile s32 *)mat)[0];
    b = ((volatile s32 *)mat)[1];
    c = ((volatile s32 *)mat)[2];
    gte_set_ctrl(R11R12, a);
    gte_set_ctrl(R13R21, b);
    gte_set_ctrl(R22R23, c);
    a = ((volatile s32 *)mat)[3];
    b = ((volatile s32 *)mat)[4];
    gte_set_ctrl(R31R32, a);
    gte_set_ctrl(R33, b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    gte_load(IR1, vel, 0);
    gte_load(IR2, vel, 4);
    gte_load(IR3, vel, 8);
    gte_rtirtr();
    gte_store(MAC1, vel, 0);
    gte_store(MAC2, vel, 4);
    gte_store(MAC3, vel, 8);
    pos[0] += pos[4];
    pos[1] += pos[5];
    pos[2] += pos[6];
    laser_spawn(pos, (u16 *)rot);
    scratch_top -= 0x48;
}

s32 timer8_slots_step(struct Timer8 *slots) {
    struct Timer8 *s = slots;
    s32 i = 0;
    do {
        if (s->timer > 0) {
            s->timer -= 1;
        } else if (s->cnt != 0) {
            s->ang += 0x55;
            if ((s16)s->ang >= 0x1001) {
                s->cnt -= 1;
                if (s->cnt > 0) {
                    s->val = rand_a_next();
                    s->ang = 0;
                }
            }
        }
        i++;
        s++;
    } while (i < 3);
    return slots[2].cnt == 0;
}

extern u16 laser_charge_level;
extern struct Timer8 laser_charge_timers[4];
void laser_charge_update(Object *obj) {
    struct LaserCtl *ctl = *(struct LaserCtl **)&obj->vars.snd;
    struct Timer8 *timers = laser_charge_timers;
    struct Timer8 *slot;
    s32 i;
    s16 level;

    switch (ctl->state) {
    case 0:
        for (slot = timers, i = 0; i < 3; i++, slot++) {
            slot->timer = i * 0x10;
            slot->cnt = 1;
            slot->ang = 0;
            slot->val = rand_a_next();
        }
        timers[3].timer = 0;
        ctl->state = 1;
        return;
    case 1:
        level = laser_charge_level + 0x33;
        laser_charge_level = level;
        {
            s32 clamped = level;
            s32 fill;
            if (clamped >= 0x1001) {
                clamped = 0x1000;
            }
            if (clamped >= 0) {
                s32 capped = level;
                if (capped >= 0x1001) {
                    capped = 0x1000;
                }
                fill = capped;
            } else {
                fill = 0;
            }
            timers[3].timer = fill;
        }
        if (timer8_slots_step(timers) == 1) {
            ctl->state = 2;
        }
        return;
    case 2:
        if (!(ctl->count & 3)) {
            laser_spawn_random(obj);
        }
        if (ctl->count >= 0x79) {
            ctl->state = 3;
        }
        ctl->count++;
        return;
    case 3:
        level = laser_charge_level - 0x88;
        laser_charge_level = level;
        if (level < 0) {
            laser_charge_level = 0;
            ctl->flag = 0;
        }
        return;
    }
}

static inline s32 rgb_pack(s32 r, s32 g, s32 b) {
    r >>= 5;
    g >>= 5;
    b >>= 5;
    if ((r | g | b) == 0) {
        b = 1;
    }
    return (b << 16) | (g << 8) | r;
}
/* Spawns a spark at bone 0x19 of obj, then one spark per active entry of
 * laser_charge_timers tinted and sized by its weight. rec->val is read before rec
 * is set, as in the original. */
void quick_fuchikoma_m8_flash_sparks(Object *obj) {
    s32 *mat = scratch_alloc(0x40);
    s32 *pos = scratch_alloc(0x20);
    s32 *ang = pos + 4;
    struct Timer8 *rec;
    s32 value;
    s32 packed;
    s32 level, shade, colour;
    s32 i;
    s32 world_offset;
    s16 weight;
    s32 weight2, red, green, blue;
    s32 blend;
    s32 depth = quick_fuchikoma_back_offset;

    pos[0] = 0;
    pos[1] = 0;
    pos[2] = depth;
    obj_bone_pos(obj, 0x19, (Vec3 *)pos);
    pos[0] = (obj->x >> 12) + pos[0];
    pos[1] = (obj->y >> 12) + pos[1];
    pos[2] = (obj->z >> 12) + pos[2];
    value = get_model_slot_base() + 0xF;
    packed = laser_charge_level << 16;
    value = pool_spawn_scaled(value, 0xBB8, 0xBB8, 0xBB8);
    level = packed >> 21;
    shade = level;
    if (level == 0) {
        shade = 1;
    }
    colour = (shade << 16) | (level << 8) | level;
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, value, colour);
    rot_matrix(mat, 0x800, 0, rec->val);
    mul_matrix(world_matrix_get(), mat, mat);
    matrix_to_angles(mat, pos + 5, ang, pos + 6);
    world_offset = get_world_offset();
    for (rec = laser_charge_timers, i = 0; i < 3; i++, rec++) {
        if (rec->timer <= 0 && rec->cnt != 0) {
            weight = rec->ang;
            red = 0xC00 * weight;
            weight2 = weight * 2;
            green = weight;
            blue = 0x1000 - weight;
            red /= 0x1000;
            blue = (blue * 0x400 + weight * 0x1000) / 0x1000;
            colour = rgb_pack(red, green, blue);
            blend = weight2;
            FAKE_OPAQUE(blend);
            if (blend < 0x1000) {
                value = pchr_blend(world_offset + 0xC5, world_offset + 0xC4, blend, 0);
            } else {
                value = pchr_blend(world_offset + 0xC6, world_offset + 0xC5, weight2 - 0x1000, 0);
            }
            spark_add(pos[0], pos[1], pos[2], ang[1], ang[0], ang[2], value, colour);
        }
    }
    scratch_top -= 0x60;
}

extern BlinkOffset blink_offset_table[];
extern s32 blink_offset_x;
extern s32 blink_offset_y;
extern s32 blink_offset_z;

void blink_offsets_init(void) {
    blink_offset_x = 0x10E;
    blink_offset_y = -0x50;
    blink_offset_z = -0xAA;
    blink_offset_table[0].pos.x = -0x10E;
    blink_offset_table[0].pos.y = -0x50;
    blink_offset_table[0].pos.z = -0xAA;
}

void obj_grow_fade_update(Object *obj) {
    s16 v = obj->vars.obj_grow_fade.frame_count;

    switch (v) {
    case 0:
        v = obj->vars.obj_grow_fade.unk_248;
        v += 0x200;
        obj->vars.obj_grow_fade.unk_248 = v;
        obj->vars.obj_grow_fade.blend_amount = v;
        if (obj->vars.obj_grow_fade.unk_248 >= 0xBB9) {
            obj->vars.obj_grow_fade.frame_count++;
        }
        break;
    case 1:
        v = obj->vars.obj_grow_fade.unk_248 + 0x200;
        obj->vars.obj_grow_fade.unk_248 = v;
        v = MAX(MIN(v, 0x1000), 0);
        obj->vars.obj_grow_fade.unk_248 = v;
        obj->vars.obj_grow_fade.blend_amount = v;
        obj->vars.obj_grow_fade.brightness -= 0x200;
        if (obj->vars.obj_grow_fade.brightness < 0) {
            obj_free(obj);
        }
        break;
    }
}

void obj_spark_emit_draw(Object *obj) {
    s32 base = get_world_offset();
    s32 v = (s16)obj->vars.obj_grow_fade.brightness;
    s32 g = v >> 4;
    s32 b = v >> 5;
    s32 value = base + 0x82;
    s32 colour;

    if ((b | g) == 0) {
        g = 1;
    }
    colour = (g << 16) | (b << 8) | b;
    value = pchr_blend(base + 0x83, value, obj->vars.obj_grow_fade.blend_amount, 0);
    spark_add(obj->x, obj->y, obj->z, 0, 0, 0, value, colour);
}

void obj_spark_emit_draw(Object *obj);
/* Spawns an object at pos (x, y, z) with its two handlers; returns 1 if one was made, 0 if obj_new failed. */
s32 obj_grow_fade_spawn(s32 *pos) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) obj_grow_fade_update;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) obj_spark_emit_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    obj->x = pos[0];
    obj->y = pos[1];
    obj->z = pos[2];
    obj->vars.obj_grow_fade.unk_248 = 0;
    obj->vars.obj_grow_fade.brightness = 0x1000;
    obj->vars.obj_grow_fade.frame_count = 0;
    obj->vars.obj_grow_fade.blend_amount = 0;
    return 1;
}

extern s32 obj_grow_fade_spawn(s32 *pos);
void homing_rocket_update(Object *obj) {
    s32 *old = scratch_alloc(0x40);
    s32 *next = old + 4;
    s32 *vel = old + 8;
    s32 *hit = old + 12;
    s32 aim_yaw, aim_pitch;

    old[0] = obj->x;
    old[1] = obj->y;
    old[2] = obj->z;
    if (world_flag_get() == 1) {
        old[0] >>= 12;
        old[1] >>= 12;
        old[2] >>= 12;
        obj_grow_fade_spawn(old);
        obj_free(obj);
        scratch_top -= 0x40;
        return;
    }
    switch (obj->vars.homing_rocket.state) {
    case 0:
        angles_to_vector(obj->yaw, -obj->pitch, obj->speed >> 12, vel, vel + 1, vel + 2);
        angles_to_player(obj->x >> 12, (obj->y >> 12) - ((s16)obj->height / 2), obj->z >> 12, &aim_yaw, &aim_pitch);
        obj->yaw = angle_approach(obj->yaw, aim_yaw, 0x3C);
        obj->pitch = angle_approach(obj->pitch, aim_pitch, 0x3C);
        obj->speed -= 0x1000;
        if (obj->speed < 0x4000) {
            obj->vars.homing_rocket.timer = 0;
            obj->vars.homing_rocket.state++;
        }
        break;
    case 1:
        obj->speed += 0x1000;
        obj->speed = MAX(MIN(obj->speed, 0x40000), 0);
        angles_to_player(obj->x >> 12, (obj->y >> 12) - ((s16)obj->height / 2), obj->z >> 12, &aim_yaw, &aim_pitch);
        obj->yaw = angle_approach(obj->yaw, aim_yaw, 0x18);
        obj->pitch = angle_approach(obj->pitch, aim_pitch, 0x18);
        angles_to_vector(obj->yaw, -obj->pitch, obj->speed >> 12, vel, vel + 1, vel + 2);
        obj->vars.homing_rocket.timer++;
        if (obj->vars.homing_rocket.timer >= 0x35) {
            obj->vx = vel[0];
            obj->vy = vel[1];
            obj->vz = vel[2];
            obj->vars.homing_rocket.state++;
        }
        break;
    case 2:
        vel[0] = obj->vx;
        vel[1] = obj->vy;
        vel[2] = obj->vz;
        break;
    }
    next[0] = old[0] + vel[0];
    next[1] = old[1] + vel[1];
    next[2] = old[2] + vel[2];
    obj->x = next[0];
    obj->y = next[1];
    obj->z = next[2];
    old[0] >>= 12;
    old[1] >>= 12;
    old[2] >>= 12;
    next[0] >>= 12;
    next[1] >>= 12;
    next[2] >>= 12;
    if (old[0] == next[0] && old[1] == next[1] && old[2] == next[2]) {
        next[1] = old[1] + 8;
    }
    switch (obj_check_move(obj, old, next, hit, 8, 1)) {
    case 1:
        break;
    case 3:
        obj_grow_fade_spawn(hit);
        break;
    case 4:
        obj_grow_fade_spawn(hit);
        hit_target_masked(0, 1, atan2(hit[2] - old[2], hit[0] - old[0]), obj->damage);
        break;
    default:
        scratch_top -= 0x40;
        return;
    }
    obj_free(obj);
    scratch_top -= 0x40;
}

static inline s32 clamp_hi_800(s32 v) {
    if (v > 0x800) {
        v = 0x800;
    }
    return v;
}
/* Draws the rocket as two sparks: its flame at its position, and a glow on the ground (y -0x840) below it whose
 * colour (GTE interpolation of a fixed grey-blue) fades with the height above the ground. The do-while gives
 * red the register priority the original has. */
void homing_rocket_draw(Object *obj) {
    s32 red, green, blue;
    s32 x = obj->x;
    s32 y = obj->y;
    s32 z = obj->z;
    s32 flame_colour = 0xFFBBBB;
    s32 model = get_world_offset() + 0x81;
    SparkList *list = &spark_list;
    s32 ground_y;
    s32 height;
    s32 height_hi;
    s32 fade;
    s32 r, g, b;
    s32 glow_colour;

    x >>= 12;
    y >>= 12;
    z >>= 12;
    spark_add_head(list, x, y, z, 0, 0, 0, model, flame_colour);
    ground_y = -0x840;
    y = ground_y - y;
    height = clamp_hi_800(y);
    height_hi = clamp_hi_800(y);
    g = 0x4B0;
    if (height_hi < 0) {
        height = 0;
    }
    fade = 0x1000 - height * 2;
    b = 0x5C8;
    gte_set(IR1, g);
    gte_set(IR2, g);
    gte_set(IR3, b);
    gte_set(IR0, fade);
    gte_gpf12();
    gte_get(IR1, r);
    gte_get(IR2, g);
    gte_get(IR3, b);
    gte_nop();
    blue = b >> 5;
    do {
        red = r >> 5;
    } while (0);
    green = g >> 5;
    if ((red | green | blue) == 0) {
        blue = 1;
    }
    glow_colour = (blue << 16) | (green << 8) | red;
    spark_add(x, ground_y, z, 0, 0, 0, model, glow_colour);
}

void homing_rocket_update(Object *obj);
void homing_rocket_draw(Object *obj);
/* Spawns the object at pos (20.12): sets its handlers, aims it at a random-rolled direction, and starts it with a sound. */
s32 homing_rocket_spawn(s32 *pos) {
    Object *obj;
    s32 *ang;
    s32 *ang_next;
    RotMatrix *mat;
    RotMatrix *mat2;
    s32 spin;
    s32 pitch;
    s32 yaw;
    s32 roll;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *)get_obj_list_actors_tail(), (Node *)obj);
    ang = scratch_alloc(0x10);
    mat = scratch_alloc(0x40);
    obj->handlers[1].fn = (void *)homing_rocket_update;
    ang_next = ang + 1;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].fn = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->callback = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = (void *)homing_rocket_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = pos[0];
    obj->y = pos[1];
    obj->z = pos[2];
    angles_to_player(obj->x >> 12, (obj->y >> 12) - (s16)obj->height / 2, obj->z >> 12, ang_next, ang);
    mat2 = mat + 1;
    rot_matrix(mat2, ang[1], ang[0], 0);
    spin = rand_a_next();
    rot_matrix(mat, 0x500, 0, spin);
    mul_matrix(mat, mat2, mat);
    rot_matrix_to_angles(mat, ang_next, ang, ang + 2);
    pitch = ang[0];
    yaw = ang[1];
    roll = ang[2];
    scratch_top -= 0x50;
    obj->damage = 8;
    obj->speed = 0x10000;
    obj->pitch = pitch;
    obj->yaw = yaw;
    obj->roll = roll;
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    obj->vars.homing_rocket.state = 0;
    sound_play_at(SND_HOMING_ROCKET_LAUNCH | SND_GROUP(1), 0x7F, 0x3C, pos);
    return 1;
}

static inline void shot_load_matrix(s32 *m) {
    s32 t0, t1, t2;

    gte_set_R012(t0, t1, t2, m[0], m[1], m[2]);
    gte_set_R34(t0, t1, m[3], m[4]);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
}
void shot_trace_update(Object *obj, ObjHandler *handler) {
    s32 *pos = scratch_alloc(0x40);
    s32 *next = pos + 4;
    s32 *vel = pos + 8;
    s32 *hit = pos + 12;
    s32 expect;
    s32 r;
    s32 speed, clamped;

    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;
    if (world_flag_get() == 1) {
        pos[0] >>= 12;
        pos[1] >>= 12;
        pos[2] >>= 12;
        obj_grow_fade_spawn(pos);
        goto free;
    }
    switch (((ShotTraceFields *)obj)->phase) {
    case 0:
        shot_load_matrix(obj->vars.words);
        vel[0] = 0;
        vel[1] = 0;
        vel[2] = obj->speed >> 12;
        gte_load(IR1, vel, 0);
        gte_load(IR2, vel, 4);
        gte_load(IR3, vel, 8);
        gte_rtirtr_sf0();
        gte_store(MAC1, vel, 0);
        gte_store(MAC2, vel, 4);
        gte_store(MAC3, vel, 8);
        obj->speed -= obj->speed_accel;
        clamped = obj->speed;
        if (clamped > 0x18000) {
            clamped = 0x18000;
        }
        speed = obj->speed;
        if (speed > 0x18000) {
            speed = 0x18000;
        }
        if (speed < 0) {
            clamped = 0;
        }
        obj->speed = clamped;
        obj->vy += obj->accel_y;
        next[0] = pos[0] + vel[0];
        next[1] = pos[1] + vel[1] + obj->vy;
        next[2] = pos[2] + vel[2];
        ((ShotTraceFields *)obj)->alpha = ((ShotTraceFields *)obj)->timer * 4;
        ((ShotTraceFields *)obj)->alpha = NOT_NEGATIVE(MIN(((ShotTraceFields *)obj)->alpha, 0x1FFF));
        ((ShotTraceFields *)obj)->timer += 0x80;
        expect = 1;
        if (((ShotTraceFields *)obj)->timer > 0x1000) {
            ((ShotTraceFields *)obj)->timer = 0;
            ((ShotTraceFields *)obj)->phase++;
            ((ShotTraceFields *)obj)->base_y = obj->y >> 12;
        }
        break;
    case 1:
        ((ShotTraceFields *)obj)->angle += 0x80;
        next[0] = pos[0];
        expect = 0;
        next[1] = (((ShotTraceFields *)obj)->base_y + cos_table[((ShotTraceFields *)obj)->angle & 0xFFF].value / 256) << 12;
        next[2] = pos[2];
        ((ShotTraceFields *)obj)->alpha = (*(s16 *)&rcossin_tbl[((ShotTraceFields *)obj)->wobble & 0xFFF] + 0x1000) / 2 + 0x1000;
        ((ShotTraceFields *)obj)->wobble += 0x155;
        ((ShotTraceFields *)obj)->alpha = NOT_NEGATIVE(MIN(((ShotTraceFields *)obj)->alpha, 0x1FFF));
        ((ShotTraceFields *)obj)->timer++;
        if (((ShotTraceFields *)obj)->timer > 0x3C) {
            ((ShotTraceFields *)obj)->timer = 0;
            ((ShotTraceFields *)obj)->phase++;
        }
        break;
    case 2:
        ((ShotTraceFields *)obj)->angle += 0x80;
        next[0] = pos[0];
        expect = 0;
        next[1] = (((ShotTraceFields *)obj)->base_y + cos_table[((ShotTraceFields *)obj)->angle & 0xFFF].value / 256) << 12;
        next[2] = pos[2];
        ((ShotTraceFields *)obj)->timer++;
        if ((((ShotTraceFields *)obj)->timer & 0xF) == 0) {
            homing_rocket_spawn(next);
        }
        ((ShotTraceFields *)obj)->alpha -= 0x80;
        if (((ShotTraceFields *)obj)->alpha <= 0) {
            goto free;
        }
        break;
    }
    obj->x = next[0];
    obj->y = next[1];
    obj->z = next[2];
    pos[0] >>= 12;
    pos[1] >>= 12;
    pos[2] >>= 12;
    next[0] >>= 12;
    next[1] >>= 12;
    next[2] >>= 12;
    if (pos[0] == next[0] && pos[1] == next[1] && pos[2] == next[2]) {
        next[1] = pos[1] + 8;
    }
    r = obj_check_move(obj, pos, next, hit, 8, expect);
    switch (r) {
    case 3:
        obj_grow_fade_spawn(hit);
        break;
    case 4:
        obj_grow_fade_spawn(hit);
        hit_target_masked(0, 1, atan2(hit[2] - pos[2], hit[0] - pos[0]), obj->damage);
        break;
    default:
        scratch_top -= 0x40;
        return;
    }
free:
    obj_free(obj);
    scratch_top -= 0x40;
}

static inline void gte_set_ir(s32 r, s32 g, s32 b) {
    register s32 r_reg asm("$3") = r;
    register s32 b_reg asm("$4") = b;

    gte_set(IR1, r_reg);
    gte_set(IR2, g);
    gte_set(IR3, b_reg);
}
/* Draws the object as two sparks: one at its position, coloured from its power (unk_27C), and a glow on the ground
 * (y -0x840) below it, the same colour faded by the GTE with the height above the ground. */
void shot_glow_draw(Object *obj, ObjHandler *handler) {
    s32 power;
    s32 bright;
    s32 blue, grey;
    s32 colour, glow_colour;
    s32 model;
    s32 x, y, z;
    s32 ground_y;
    register s32 height asm("$3");
    s32 height_hi;
    s32 fade;
    s32 r, g, b;
    s32 red, green;

    do {
        power = obj->vars.with_matrix.glow_power;
    } while (0);
    bright = power * 3 / 2;
    if (bright >= 0x2000) {
        bright = 0x1FFF;
    }
    blue = bright >> 5;
    grey = power >> 5;
    if ((grey | blue) == 0) {
        blue = 1;
    }
    colour = (blue << 16) | (grey << 8) | grey;
    model = get_world_offset() + 0x80;
    x = obj->x;
    y = obj->y;
    z = obj->z;
    x >>= 12;
    y >>= 12;
    z >>= 12;
    spark_add(x, y, z, 0, 0, 0, model, colour);
    ground_y = -0x840;
    y = ground_y - y;
    height = clamp_hi_800(y);
    height_hi = clamp_hi_800(y);
    if (height_hi < 0) {
        height = 0;
    }
    fade = 0x1000 - height;
    gte_set_ir(power / 8, power / 8, bright / 8);
    gte_set(IR0, fade);
    gte_gpf12();
    gte_get(IR1, r);
    gte_get(IR2, g);
    gte_get(IR3, b);
    gte_nop();
    b >>= 5;
    do {
        red = r >> 5;
    } while (0);
    green = g >> 5;
    if ((red | green | b) == 0) {
        b = 1;
    }
    glow_colour = (b << 16) | (green << 8) | red;
    spark_add(x, ground_y, z, 0, 0, 0, model, glow_colour);
}

void shot_trace_update(Object *obj, ObjHandler *handler);
void shot_glow_draw(Object *obj, ObjHandler *handler);
s32 obj_spawn_with_matrix(Object *parent, Vec3 *pos, s32 *matrix) {
    Object *obj;
    s32 z;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj->handlers[1].fn = shot_trace_update;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->callback = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = shot_glow_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = pos->x;
    obj->y = pos->y;
    z = pos->z;
    obj->speed = 0x18000;
    obj->speed_accel = 0x708;
    obj->vy = 0;
    obj->accel_y = 0x7D0;
    obj->z = z;
    *(RotMatrixWords *) obj->vars.words = *(RotMatrixWords *) matrix;
    obj->vars.turn.yaw_offset = 0;
    obj->vars.chaser.damage_scale = 0;
    obj->vars.with_matrix.glow_power = 0;
    obj->vars.part.kind = 0;
    obj->vars.with_matrix.unused_282 = 0;
    obj->damage = 0x10;
    obj_hit_clear((s32) obj->index);
    obj_hit_flag_set((s32) obj->index, 0);
    obj_set_flags(obj, 0x80);
    obj->unk_17A = 0;
    sound_play_at(SND_PROJECTILE_LAUNCH | SND_GROUP(1), 0x7F, 0x3C, pos);
    return 1;
}

void obj_bone_pos(Object *obj, s32 idx, Vec3 *out);
s32 obj_spawn_with_matrix(Object *parent, Vec3 *pos, s32 *matrix);
/* Takes offset `which` of the table, turns it into a world position near the object and hands it on with a
 * randomly tilted matrix. */
void blink_light_spawn(Object *obj, s32 which) {
    s32 *mat = scratch_alloc(0x20);
    Vec3 *pos = scratch_alloc(0x10);
    BlinkOffset *tab = blink_offset_table;
    BlinkOffset *rec;
    s32 yaw, pitch, a;

    rec = tab + which;
    pos->x = rec->pos.x;
    pos->y = rec->pos.y;
    pos->z = rec->pos.z;
    obj_bone_pos(obj, 8, pos);
    pos->x = obj->x + (pos->x << 12);
    pos->y = obj->y + (pos->y << 12);
    pos->z = obj->z + (pos->z << 12);
    yaw = rand_a_next() / 4;
    pitch = rand_a_next() / 8;
    if (which == 0) {
        rot_matrix(mat, yaw - 0x6C8, pitch + 0x1D4, 0);
    } else {
        rot_matrix(mat, yaw + 0x2C8, pitch + 0x1D4, 0);
    }
    mul_matrix(world_matrix_get(), mat, mat);
    obj_spawn_with_matrix(obj, pos, mat);
    scratch_top -= 0x30;
}

void blink_light_spawn(Object *obj, s32 value);
void blink_update(Object *obj) {
    BlinkState *st = (BlinkState *)obj->vars.part.parent;
    s32 r;

    switch (st->state) {
    case 0:
        r = rand_a_next();
        if (r < 0) {
            r += 0x7FF;
        }
        st->value = r >> 11;
        st->state++;
        break;
    case 1:
        if (st->counter % 40 == 0) {
            blink_light_spawn(obj, st->value);
            st->value ^= 1;
        }
        st->counter++;
        if (st->counter >= 200) {
            st->counter = 0;
            st->state++;
        }
        break;
    case 2:
        st->counter++;
        if (st->counter >= 0x1F) {
            st->unk_0 = 0;
        }
        break;
    }
}


void func_800C4318(void) {
}
