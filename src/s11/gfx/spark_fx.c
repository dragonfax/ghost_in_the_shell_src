/* spark_fx: one of s11's own original source files (scripts/objmap.py); part of src/s11/main.c's unit, included there. */

/* Sets the object's 0x24C word to 2 and its 0x250 word to 0, then calls obj_noop_hook. */
void obj_copy_init(Object *obj) {
    obj->vars.snd.sound = 2;
    obj->vars.copy.unused_250 = 0;
    obj_noop_hook();
}

s32 obj_spawn_copy(Object *src, s32 mode) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->x = src->x;
    obj->y = src->y;
    obj->z = src->z;
    obj->width = (u16) src->width;
    obj->height = src->height;
    obj->unk_1E8[0] = (u16) src->unk_1E8[0];
    obj->yaw = (u16) src->yaw;
    obj->pitch = (u16) src->pitch;
    obj->roll = (u16) src->roll;
    obj->handlers[0].fn = fn_800C4368;
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) obj_noop_update;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) spark_record_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj_copy_init(obj);
    obj->vars.copy.unk_248 = mode;
    fade_red_obj = (Next800C5620 *) obj;
    return 1;
}

s32 obj_spawn_copy(Object *src, s32 mode);
void obj_replace_with_copy(Object *obj) {
    s32 asset_value;
    s32 type_offset;

    asset_value = *(s32 *)obj->asset;
    type_offset = obj->type.unk_0E;
    obj_spawn_copy(obj, type_offset + model_slot_pchr(asset_value));
    obj_free(obj);
}

void sound_effect_draw(Object *obj) {
    s32 pos[3];
    s32 age;
    s32 colour;
    s32 value;
    s32 n;
    SparkRec *s;
    SparkList *list;
    s32 x, y, z;
    u8 *tail;

    value = obj->vars.sound_effect.current_sound;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    age = obj->vars.sound_effect.unused_248;
    colour = (((0x1000 - age) >> 5) << 16) | 0x8080;
    value = pool_spawn_scaled(value, 0x2000 - age, 0x2000 - age, 0x1000);
    list = &spark_list;
    n = spark_count;
    x = pos[0];
    y = pos[1];
    z = pos[2];
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

void sound_effect_update(Object *obj, ObjHandler *handler) {
    s32 toggle;
    s32 r;

    toggle = obj->vars.sound_effect.toggle ^ 1;
    obj->vars.sound_effect.toggle = toggle;
    if (toggle == 0) {
        r = rand_a_next();
        obj->vars.sound_effect.current_sound = obj->vars.snd.sound + (r % 4);
    }
    if (obj->vars.sound_effect.unused_248 >= 0x1001) {
        obj_free(obj);
    }
    obj->vars.sound_effect.unused_248 += 0xAA;
}

void sound_effect_draw(Object *obj);
/* Spawns an object at pos (world units, shifted to 12-bit fixed point) and
   sets its vars.words[1] and [2] to arg1. Returns 0 if obj_new fails. */
s32 sound_effect_spawn(s32 *pos, s32 arg1) {
    Object *obj;
    s32 z;
    s32 frame_pad[4]; /* the original's frame is 16 bytes larger; keeps it matching */

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->handlers[1].fn = sound_effect_update;
    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = sound_effect_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->speed = 0;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    z = pos[2];
    obj->yaw = 0;
    obj->pitch = 0;
    obj->roll = 0;
    obj->vars.sound_effect.unused_248 = 0;
    obj->vars.sound_effect.base_sound = arg1;
    obj->vars.sound_effect.current_sound = arg1;
    obj->vars.sound_effect.toggle = 0;
    obj->z = z << 12;
    return 1;
}

/* Rotates the offset (dx, dy, dz) by the angle pair and adds it to pos. */
void pos_add_offset_by_angles(Vec3 *pos, s16 *angles, s32 dx, s32 dy, s32 dz) {
    s32 rot_x;
    s32 rot_y;
    s32 rot_z;

    rot_x = dx;
    rot_y = dy;
    rot_z = dz;
    rotate_xz_twice(angles[1], angles[0], &rot_x, &rot_y, &rot_z);
    pos->x += rot_x;
    pos->y += rot_y;
    pos->z += rot_z;
}

/* Emits a fading spark at the object's position: the value comes from pool_spawn_scaled with the object's
 * 0x250 value and the remaining amount (0x1000 - vars.enemy.mode); the colour grows grey with it. */
void obj_follow_draw(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    struct { s16 x, y, z; } rot;
    s32 pitch;
    s32 amount;
    s32 shade;
    s32 colour;
    s32 value = obj->vars.enemy.unk_250;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.x = -pitch;
    rot.y = (u16)obj->yaw;
    rot.z = (u16)obj->roll;
    amount = 0x1000 - obj->vars.enemy.mode;
    shade = amount >> 5;
    colour = (shade << 8) | (shade | 0x800000);
    value = pool_spawn_scaled(value, amount, amount, amount);
    spark_add(pos.x, pos.y, pos.z, rot.y, rot.x, rot.z, value, colour);
}

void obj_follow_update(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    s16 angles[3];
    Object *target;
    Object *src;
    s32 toggle;
    s32 pitch;

    target = (Object *)obj->vars.words[4];
    toggle = obj->vars.follow.toggle ^ 1;
    obj->vars.follow.toggle = toggle;
    if (target->next_state != 0xB) {
        solid_part_box(target->solid_id, toggle == 0 ? 0xA : 0xB, &pos.x, 0);
        src = (Object *)obj->vars.words[4];
        pitch = src->pitch;
        angles[0] = -pitch;
        angles[1] = src->yaw;
        angles[2] = src->roll;
        pos_add_offset_by_angles(&pos, angles, 0, 0x32, -0x64);
        obj->x = pos.x << 12;
        obj->y = pos.y << 12;
        obj->z = pos.z << 12;
        obj->yaw = ((Object *)obj->vars.words[4])->yaw;
        obj->pitch = ((Object *)obj->vars.words[4])->pitch;
        obj->roll = ((Object *)obj->vars.words[4])->roll;
    } else {
        obj_free(obj);
    }
    if (obj->vars.follow.toggle == 0) {
        obj->vars.words[2] = obj->vars.words[1] + (rand_a_next() % 3);
    }
    if (obj->vars.follow.unk_248 >= 0x1001) {
        obj_free(obj);
    }
    obj->vars.follow.unk_248 += 0x200;
}

void obj_follow_update(Object *obj, ObjHandler *handler);
void obj_follow_draw(Object *obj, ObjHandler *handler);
s32 obj_spawn_follow(Object *parent) {
    Object *obj;
    s32 anim;
    s32 frame_pad[4]; /* unused; the original's stack frame is 16 bytes bigger */

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->handlers[1].fn = obj_follow_update;
    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = obj_follow_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->speed = 0;
    obj->x = parent->x;
    obj->y = parent->y;
    obj->z = parent->z;
    obj->yaw = parent->yaw;
    obj->pitch = parent->pitch;
    obj->roll = parent->roll;
    obj->vars.follow.unk_248 = 0;
    anim = model_slot_pchr(*(s32 *) parent->asset) + 0xC4;
    obj->vars.words[1] = anim;
    obj->vars.words[2] = anim;
    obj->vars.follow.toggle = 0;
    obj->vars.words[4] = (s32) parent;
    return 1;
}

/* Spawns a spark with the enemy's position, angles and colour. The colour is a blend of the
 * enemy's mode: red, green and blue weights of inv (0x1000 - mode) and mode in 1/4096 steps. */
void spark_blend_draw(Object *obj, ObjHandler *handler) {
    VECTOR pos;
    SVECTOR rot;
    s32 mode = obj->vars.enemy.mode;
    s32 inv = 0x1000 - mode;
    s32 pitch;
    s32 red, green, blue;
    s32 colour;
    s32 pool_id; /* the pool index going in, the spawn's result coming out (one register) */
    s32 red_t, green_t, blue_t;

    pool_id = obj->vars.at_point.pool_id;
    red_t = (inv + mode) * 0xC00;
    if (red_t < 0) {
        red_t += 0xFFF;
    }
    green_t = inv * 0xC00 + (mode << 9);
    if (green_t < 0) {
        green_t += 0xFFF;
    }
    blue_t = inv * 0x1C00 + (mode << 9);
    if (blue_t < 0) {
        blue_t += 0xFFF;
    }
    blue = blue_t >> 17;
    red = red_t >> 17;
    green = green_t >> 17;
    if ((red | green | blue) == 0) {
        blue = 1;
    }
    pos.vx = obj->x >> 12;
    pos.vy = obj->y >> 12;
    pos.vz = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = (u16)obj->yaw;
    rot.vz = (u16)obj->roll;
    colour = (blue << 16) | (green << 8) | red;
    pool_id = pool_spawn_scaled(pool_id, 0x1000 - obj->vars.enemy.mode, 0x1000 - obj->vars.enemy.mode, 0x1000);
    spark_add(pos.vx, pos.vy, pos.vz, rot.vy - 0x800, rot.vx, rot.vz, pool_id, colour);
}

void spark_blend_update(Object *obj) {
    s32 yaw, pitch, speed;

    obj->vars.at_point.flicker_toggle ^= 1;
    if (obj->vars.at_point.flicker_toggle == 0) {
        obj->vars.at_point.pool_id = obj->vars.at_point.base_pool_id + (rand_a_next() % 3);
    }
    if (obj->vars.at_point.progress >= 0x1001) {
        obj_free(obj);
    }
    yaw = obj->yaw;
    pitch = obj->pitch;
    speed = obj->speed;
    obj->vars.at_point.progress += 0x100;
    angles_to_vector(yaw, pitch, speed, &obj->vx, &obj->vy, &obj->vz);
    obj->z += obj->vz;
    obj->x += obj->vx;
    obj->y += obj->vy;
    obj->speed += 1;
}

void spark_blend_update(Object *obj);
void spark_blend_draw(Object *obj, ObjHandler *handler);
/* Spawns an object at pos (world units, shifted to 12-bit fixed point) with the angles in rot (yaw
 * advanced by 0x800, pitch and yaw swapped into the object) and arg2 as vars.words[1] and [2].
 * Returns 0 if obj_new fails. */
s32 obj_spawn_at_point(s32 *pos, u16 *rot, s32 arg2) {
    Object *obj;
    s32 frame_pad[4]; /* the original's frame is 16 bytes larger; keeps it matching */

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->handlers[1].fn = spark_blend_update;
    obj->handlers[3].fn = spark_blend_draw;
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
    obj->speed = 0x14;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    rot[1] += 0x800;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    obj->roll = rot[2];
    obj->vars.at_point.progress = 0;
    obj->vars.at_point.base_pool_id = arg2;
    obj->vars.at_point.pool_id = arg2;
    obj->vars.at_point.flicker_toggle = 0;
    return 1;
}

void ramp_draw(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    SVECTOR rot;
    s32 blend, rest; /* blend: 0x1000 = all the second colour */
    s32 r, g, b;
    s32 colour;
    s32 pitch;
    s32 value = obj->vars.ramp.unk_24C;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    blend = obj->vars.ramp.blend;
    rest = 0x1000 - blend;
    r = (rest * 0xC00 + blend * 0x200) / 0x1000;
    g = (rest * 0xC00 + blend * 0x100) / 0x1000;
    b = (rest * 0x1000 + blend * 0x400) / 0x1000;
    r >>= 5;
    g >>= 5;
    b >>= 5;
    if ((r | g | b) == 0) {
        b = 1;
    }
    colour = (b << 16) | (g << 8) | r;
    value = pool_spawn_scaled(value, 0x1000, 0x2000, 0x1000);
    spark_add(pos.x, pos.y, pos.z, rot.vy, rot.vx, rot.vz, value, colour);
}

void ramp_update(Object *obj, ObjHandler *handler) {
    if (obj->vars.enemy.mode >= 0x1001) {
        obj_free(obj);
    }
    obj->vars.enemy.mode += 0x80;
}

void ramp_draw(Object *obj, ObjHandler *handler);
s32 obj_spawn_ramp(s32 arg, s32 *pos, u16 *rot) {
    Object *obj;
    u16 roll;
    s32 frame_pad[4]; /* unused; the original's stack frame is 16 bytes bigger */

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->handlers[1].fn = ramp_update;
    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = ramp_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->speed = 0;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    roll = rot[2];
    obj->vars.ramp.blend = 0;
    obj->vars.ramp.unk_24C = arg;
    obj->roll = roll;
    return 1;
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


/* Runs shoot_at_player with the word at 0x18 (12 fraction bits dropped) while the halfword at 0x28 is below 0x999. */
void spark_fx_update(Object *obj) {
    if (obj->script.unk_0C < 0x999) {
        fx_shoot_at_player(obj, *(s32 *)&obj->type.unk_0C >> 12);
    }
}

void homing_energy_pulse_draw(Object *obj) {
    s32 pos[3];
    s32 value;
    s32 fade;
    s32 i;
    s32 scale;
    s32 hi;
    s32 colour;
    register PulseTrail *shifted asm("$2");

    value = obj->vars.homing_energy_pulse.unk_248;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    value = pool_spawn_scaled(value, 0x2000, 0x2000, 0x1000);
    spark_add_head(&spark_list, pos[0], pos[1], pos[2], 0, 0, 0, value, 0);
    for (i = 1, fade = 0x333; i < 5; i++, fade += 0x333) {
        s32 idx = /* the trail entry i steps back (ring of 5) */ obj->vars.homing_energy_pulse.trail_index - i;

        value = obj->vars.homing_energy_pulse.unk_248;
        if (idx < 0) {
            do {
                idx += 5;
            } while (idx < 0);
        }
        idx *= sizeof(SVECTOR);
        shifted = (PulseTrail *)((u8 *)obj + idx);
        scale = 0x1000 - fade;
        scale >>= 5;
        pos[0] = shifted->trail[0].vx;
        pos[1] = shifted->trail[0].vy;
        pos[2] = shifted->trail[0].vz;
        hi = scale;
        if (scale == 0) {
            hi = 1;
        }
        colour = (hi << 16) | (scale << 8) | scale;
        value = pool_spawn_scaled(value, 0x2000 - fade, 0x2000 - fade, 0x1000);
        spark_add(pos[0], pos[1], pos[2], 0, 0, 0, value, colour);
    }
}

/* Records the object's current position (x/y/z >> 12) in its 5-entry history ring at the
   write index (vars.h.unk_254), then advances the index modulo 5. */
void pos_history_record(Object *obj) {
    s32 pos[3];

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;

    ((PosHistRing *)obj)->ring[obj->vars.homing_energy_pulse.trail_index].x = pos[0];
    ((PosHistRing *)obj)->ring[obj->vars.homing_energy_pulse.trail_index].y = pos[1];
    ((PosHistRing *)obj)->ring[obj->vars.homing_energy_pulse.trail_index].z = pos[2];
    obj->vars.homing_energy_pulse.trail_index = (obj->vars.homing_energy_pulse.trail_index + 1) % 5;
}

extern RecTemplate hit_flash_template;
extern RecTemplate hit_spark_template;
/* Homing energy pulse: flies straight while ramping up, then after a delay steers toward
 * the player for a limited number of frames; records its trail and dies on any hit. */
void homing_energy_pulse_update(Object *obj, ObjHandler *handler) {
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s32 unused[4]; /* frame space the original reserves */
    Vec3 pos;
    Vec3 snd;
    s32 yaw;
    s32 pitch;
    s16 target;
    Vec3 *player;
    s32 dz;
    s32 *vel;
    s32 speed;
    s32 turn_yaw;
    register s32 turn_pitch asm("$5"); /* the original sign-extends in a1 itself */

    player = (Vec3 *)player_position();
    if (obj->vars.homing_energy_pulse.unk_258 < 0x1000) {
        s32 cur_yaw = obj->yaw;
        s32 cur_pitch = obj->pitch;
        s32 cur_speed = obj->speed;
        angles_to_vector(cur_yaw, cur_pitch, cur_speed, &obj->vx, &obj->vy, &obj->vz);
        obj->vars.homing_energy_pulse.unk_258 += 0x200;
    } else {
        if ((s16)obj->vars.homing_energy_pulse.unk_25A-- < 0) {
            if (obj->vars.homing_energy_pulse.unk_25C == 0) {
                snd.x = obj->x >> 12;
                snd.y = obj->y >> 12;
                snd.z = obj->z >> 12;
                sound_play_at_units(SND_HOMING_PULSE_FIRE | SND_GROUP(1), 0x60, 0x3C, &snd);
                obj->vars.homing_energy_pulse.unk_25C = 1;
            }
            if ((s16)obj->vars.homing_energy_pulse.life_timer-- > 0) {
                pos.x = obj->x >> 12;
                pos.y = obj->y >> 12;
                pos.z = obj->z >> 12;
                dz = player->z - pos.z;
                vector_to_angles(player->x - pos.x, player->y - pos.y, dz, &yaw, &pitch);
                obj->yaw = angle_approach(obj->yaw, yaw, 0x18);
                obj->pitch = angle_approach(obj->pitch, -pitch, 0x18);
                turn_pitch = obj->pitch;
                turn_yaw = obj->yaw;
                speed = obj->speed;
                vel = &obj->vx;
                goto set_velocity;
            }
        } else {
            speed = 1;
            vel = &obj->vx;
            turn_yaw = obj->yaw;
            turn_pitch = obj->pitch;
        set_velocity:
            angles_to_vector(turn_yaw, turn_pitch, speed, vel, &obj->vy, &obj->vz);
        }
    }
    if (obj->vars.homing_energy_pulse.unk_256 > 0x1000) {
        pos_history_record(obj);
        obj->vars.homing_energy_pulse.unk_256 = 0;
    }
    obj->vars.homing_energy_pulse.unk_256 += 0x1000;
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    to[0] = (obj->x + obj->vx) >> 12;
    to[1] = (obj->y + obj->vy) >> 12;
    to[2] = (obj->z + obj->vz) >> 12;
    if (trace_world(8, 0x10, from, to, hit)) {
        fx_spawn_template(from, &hit_flash_template, 0);
        fx_spawn_template(from, &hit_spark_template, spark_fx_update);
        obj->vars.homing_energy_pulse.unk_250 = 1;
    } else {
        set_collide_mode(1);
        if (trace_objects(from, to, 0x10, hit, &target)) {
            hit_target_masked(target, 1, atan2(hit[2] - from[2], hit[0] - from[0]), 10);
            fx_spawn_template(from, &hit_flash_template, 0);
            fx_spawn_template(from, &hit_spark_template, spark_fx_update);
            obj->vars.homing_energy_pulse.unk_250 = 1;
        }
        set_collide_mode(0);
        obj->z += obj->vz;
        obj->x += obj->vx;
        obj->y += obj->vy;
    }
    if (obj->vars.homing_energy_pulse.unk_250 != 0) {
        obj_free(obj);
    }
}

void homing_energy_pulse_update(Object *obj, ObjHandler *handler);
void homing_energy_pulse_draw(Object *obj);
/* Spawns a homing energy pulse at pos/rot. unk_a and unk_n are stored into
 * the object's vars; their meaning is not yet known. */
void homing_energy_pulse_spawn(s32 unk_a, Vec3 *pos, SVECTOR *rot, s32 unk_n) {
    PulseTrail *trail;
    /* The original reserves this stack space (frame 0x40); nothing reads it. */
    s32 unused[6];
    Object *obj;
    s32 i;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = homing_energy_pulse_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = homing_energy_pulse_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_set_flags(obj, 0x80);
        obj->unk_17A = 0;
        obj_hit_clear(obj->index);
        obj->speed = 0x28;
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot->vx;
        obj->yaw = rot->vy;
        obj->roll = rot->vz;
        obj->vars.homing_energy_pulse.unk_248 = unk_a + 0xD6;
        obj->vars.homing_energy_pulse.unused_24A = 0xA;
        obj->vars.homing_energy_pulse.life_timer = 0x50;
        obj->vars.homing_energy_pulse.unk_250 = 0;
        obj->vars.enemy.sound_channel[0] = 0;
        obj->vars.enemy.sound_channel[1] = 0;
        obj->vars.homing_energy_pulse.unk_258 = 0;
        obj->vars.homing_energy_pulse.unk_25A = unk_n;
        obj->vars.homing_energy_pulse.unk_25C = 0;
        trail = (PulseTrail *) obj;
        for (i = 0; i < 5; i++) {
            trail->trail[i].vx = pos->x;
            trail->trail[i].vy = pos->y;
            trail->trail[i].vz = pos->z;
        }
    }
}

/* Emits an effect record at the object's position (x, y, z in 1/4096 units) with a value read from the
 * object's table at 0x24A, indexed by the halfword at 0x252, clamped to 0x1000 (stored into the record). */
void spark_emit_head(Object *obj) {
    s32 pos[3];
    s32 radius;
    s32 value;

    value = ((s16 *)&obj->vars.spark_emit_obj.unk_24A)[(s16)obj->vars.fly.phase];
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    radius = obj->vars.spark_emit_obj.radius;
    if (radius >= 0x1001) {
        radius = 0x1000;
    }
    value = pool_spawn_scaled(value, radius, radius, 0x1000);
    spark_add_head(&spark_list, pos[0], pos[1], pos[2], 0, 0, 0, value, 0);
}

/* Rotate the offset (x, y, z) by the angles in rot (yaw sign reversed) and add the result to pos. */
void pos_add_rotated_svec(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    rotate_xz_twice(rot->vy, -rot->vx, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}

extern RecTemplate hit_flash_template;
extern RecTemplate hit_spark_template;
void homing_energy_pulse_spawn(s32 unk_a, Vec3 *pos, SVECTOR *rot, s32 unk_n);
void spark_shot_update(Object *obj, ObjHandler *handler) {
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s16 target;
    s32 unused[8];
    Vec3 snd;
    Vec3 pos;
    SVECTOR rot;
    SVECTOR rot3;
    SVECTOR rot2;
    u16 old;
    s32 pitch;
    s32 p;
    Object *own;
    u16 step;
    s16 sc;
    s32 yaw;
    s32 speed;
    Object *owner;

    player_position();
    if (((SparkShot *)&obj->vars)->owner->next_state == 0xB) {
        obj_free(obj);
    }
    if (((SparkShot *)&obj->vars)->scale > 0x2000) {
        old = ((SparkShot *)&obj->vars)->life;
        ((SparkShot *)&obj->vars)->life = old - 1;
        if ((s16)old > 0) {
            if (((SparkShot *)&obj->vars)->sounded == 0) {
                snd.x = obj->x >> 12;
                snd.y = obj->y >> 12;
                snd.z = obj->z >> 12;
                sound_play_at_units(SND_SPARK_SHOT | SND_GROUP(1), 0x60, 0x3C, &snd);
                ((SparkShot *)&obj->vars)->sounded = 1;
            }
            yaw = obj->yaw;
            pitch = obj->pitch;
            speed = obj->speed;
            angles_to_vector(yaw, pitch, speed, &obj->vx, &obj->vy, &obj->vz);
        } else {
            pos.x = obj->x >> 12;
            pos.y = obj->y >> 12;
            pos.z = obj->z >> 12;
            p = obj->pitch;
            rot.vx = -p;
            rot.vy = obj->yaw;
            rot.vz = obj->roll;
            rot3 = rot;
            sound_play_at_units(SND_PAIR(SND_SPARK_SHOT_PULSE | SND_GROUP(1), SND_SPARK_SHOT_DETONATE | SND_GROUP(1)), 0x60, 0x3C, &pos);
            rot3.vx = rot.vx + 0x300;
            homing_energy_pulse_spawn(((SparkShot *)&obj->vars)->id, &pos, &rot3, rand_a_next() % 10 + 0x14);
            rot3.vx = rot.vx + 0x100;
            rot3.vy = rot.vy + 0x200;
            homing_energy_pulse_spawn(((SparkShot *)&obj->vars)->id, &pos, &rot3, rand_a_next() % 10 + 0x28);
            rot3.vy = rot.vy - 0x200;
            homing_energy_pulse_spawn(((SparkShot *)&obj->vars)->id, &pos, &rot3, rand_a_next() % 10 + 0x3C);
            rot3.vx = rot.vx - 0x100;
            rot3.vy = rot.vy + 0x100;
            homing_energy_pulse_spawn(((SparkShot *)&obj->vars)->id, &pos, &rot3, rand_a_next() % 10 + 0x50);
            rot3.vy = rot.vy - 0x100;
            homing_energy_pulse_spawn(((SparkShot *)&obj->vars)->id, &pos, &rot3, rand_a_next() % 10 + 0x64);
            obj_free(obj);
        }
    } else {
        owner = ((SparkShot *)&obj->vars)->owner;
        snd.x = owner->x >> 12;
        snd.y = owner->y >> 12;
        snd.z = owner->z >> 12;
        own = ((SparkShot *)&obj->vars)->owner;
        p = own->pitch;
        rot2.vx = -p;
        rot2.vy = own->yaw;
        rot2.vz = own->roll;
        rot2.vy = ((SparkShot *)&((SparkShot *)&obj->vars)->owner->vars)->yaw_base;
        pos_add_rotated_svec(&snd, &rot2, 0x118, -0x190, 0x1D6);
        obj->x = snd.x << 12;
        obj->y = snd.y << 12;
        obj->z = snd.z << 12;
        obj->yaw = ((SparkShot *)&((SparkShot *)&obj->vars)->owner->vars)->yaw_base;
    }
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    to[0] = (obj->x + obj->vx) >> 12;
    to[1] = (obj->y + obj->vy) >> 12;
    to[2] = (obj->z + obj->vz) >> 12;
    if (trace_world(8, 0x10, from, to, hit)) {
        fx_spawn_template(from, &hit_flash_template, 0);
        fx_spawn_template(from, &hit_spark_template, spark_fx_update);
        ((SparkShot *)&obj->vars)->done = 1;
    } else {
        set_collide_mode(1);
        if (trace_objects(from, to, 0x10, hit, &target)) {
            hit_target_masked(target, 1, atan2(hit[2] - from[2], hit[0] - from[0]), 0x1E);
            fx_spawn_template(from, &hit_flash_template, 0);
            fx_spawn_template(from, &hit_spark_template, spark_fx_update);
            ((SparkShot *)&obj->vars)->done = 1;
        }
        set_collide_mode(0);
        obj->z += obj->vz;
        obj->x += obj->vx;
        obj->y += obj->vy;
    }
    if (((SparkShot *)&obj->vars)->done != 0) {
        obj_free(obj);
    }
    if (((SparkShot *)&obj->vars)->phase_step > 0x1000) {
        ((SparkShot *)&obj->vars)->phase_step = 0;
        ((SparkShot *)&obj->vars)->phase = (((SparkShot *)&obj->vars)->phase + 1) % 3;
    }
    step = ((SparkShot *)&obj->vars)->phase_step;
    sc = ((SparkShot *)&obj->vars)->scale + 0x55;
    step += 0x400;
    ((SparkShot *)&obj->vars)->scale = sc;
    ((SparkShot *)&obj->vars)->phase_step = step;
    if (sc > 0x2000) {
        ((SparkShot *)&obj->vars)->scale = 0x2001;
    }
}

void spark_shot_update(Object *obj, ObjHandler *handler);
void spark_emit_head(Object *obj);
void spark_emit_spawn(TrailObjPose *owner, Vec3 *pos, SVECTOR *rot) {
    Object *obj;
    s16 pchr;
    s32 scratch[6]; /* unused; the original's frame is 0x40 bytes, this keeps it */

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = spark_shot_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = (void (*)(Object *, ObjHandler *))spark_emit_head;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_set_flags(obj, 0x80);
        obj_hit_clear(obj->index);
        obj->unk_17A = 0;
        obj->speed = 0x19;
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = (u16)rot->vx;
        obj->yaw = (u16)rot->vy;
        obj->roll = (u16)rot->vz;
        pchr = model_slot_pchr(((s32 *)((Object *)owner)->asset)[0]);
        obj->vars.spark_emit_obj.pchr_base = pchr;
        obj->vars.spark_emit_obj.unk_24A = pchr + 0xD1;
        obj->vars.spark_emit_obj.unk_24C = obj->vars.spark_emit_obj.pchr_base + 0xD3;
        obj->vars.spark_emit_obj.unk_24E = obj->vars.spark_emit_obj.pchr_base + 0xD5;
        obj->vars.enemy.sound_channel[0] = 0x1E;
        obj->vars.spark_emit_obj.unused_250 = 0;
        obj->vars.spark_emit_obj.unused_252 = 0;
        obj->vars.spark_emit_obj.unused_258 = 0;
        obj->vars.spark_emit_obj.radius = 0;
        obj->vars.spark_emit_obj.unused_25E = 0;
        obj->vars.spark_emit_obj.sound_handle = sound_start(SND_SPARK_EMIT_LOOP | SND_HELD | SND_GROUP(2), 0x60, 0, 0x30);
        obj->vars.spark_emit_obj.owner = (s32)owner;
    }
}

/* Object phase in vars.h: 0 ramps progress up by unk_250 and moves to phase 1 past 0x1000; 1 ramps by
 * unk_252 and frees the object past 0x1000. unk_24A follows progress (inverted in phase 1). */
void ramp_in_out_update(Object *obj, ObjHandler *handler) {
    s16 phase;

    phase = obj->vars.ramp_in_out.phase;
    switch (phase) {
    case 0: {
        s16 progress;

        progress = (u16) obj->vars.ramp_in_out.progress + obj->vars.ramp_in_out.rise_step;
        obj->vars.ramp_in_out.progress = progress;
        obj->vars.ramp_in_out.unk_24A = (u16) progress;
        if (obj->vars.ramp_in_out.progress >= 0x1001) {
            obj->vars.ramp_in_out.progress = 0;
            obj->vars.ramp_in_out.phase += 1;
            return;
        }
        return;
    }
    case 1: {
        u16 progress;

        progress = obj->vars.ramp_in_out.progress + obj->vars.ramp_in_out.fall_step;
        obj->vars.ramp_in_out.progress = progress;
        obj->vars.ramp_in_out.unk_24A = 0x1000 - progress;
        if ((s16) obj->vars.ramp_in_out.progress >= 0x1001) {
            obj_free(obj);
        }
        break;
    }
    }
}


void obj_scaled_spark_draw(Object *obj) {
    s32 product;
    s32 scale;
    s32 level;
    s32 channel;
    s32 colour;
    s32 pool_index;

    pool_index = get_model_slot_base() + 0xF;
    product = (s16)obj->vars.h.unk_24A * (s16)obj->vars.h.unk_24C;
    if (product < 0) {
        product += 0xFFF;
    }
    scale = product >> 12;
    pool_index = pool_spawn_scaled(pool_index, scale, scale, scale);

    level = (s16)obj->vars.h.unk_24A >> 5;
    channel = level ? level : 1;
    colour = (channel << 16) | (level << 8) | level;
    spark_add(obj->x, obj->y, obj->z, 0, 0, 0, pool_index, colour);
}


void obj_scaled_spark_draw(Object *obj);
s32 obj_spawn_ramp_in_out(s32 *pos, s32 flag) {
    Object *obj;
    s32 z;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), &obj->node);
    obj->handlers[1].fn = ramp_in_out_update;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = obj_scaled_spark_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    obj->x = pos[0];
    obj->y = pos[1];
    z = pos[2];
    obj->vars.ramp_in_out.unused_24C = 0x1770;
    obj->vars.ramp_in_out.rise_step = 0x400;
    obj->vars.ramp_in_out.fall_step = 0x100;
    obj->vars.ramp_in_out.progress = 0;
    obj->vars.ramp_in_out.unk_24A = 0;
    obj->vars.ramp_in_out.phase = 0;
    obj->z = z;
    if ((flag << 16) != 0) {
        sound_play_at_units(SND_PAIR(SND_RAMP_MOVE | SND_GROUP(2), SND_RAMP_MOVE_ALT | SND_GROUP(2)), 0x60, 0x3C, pos);
    }
    return 1;
}


void pos_add_rotated_offset_flipped(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    rotate_xz_twice(rot->vy, -rot->vx, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}

void spark_spawn_at_obj(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    SVECTOR rot;
    SVECTOR rot2;
    s32 value = *(s16 *)&obj->vars;
    s32 pitch, yaw, roll;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    yaw = obj->yaw;
    rot.vy = yaw;
    roll = (u16)obj->roll;
    rot.vz = roll;
    spark_add(pos.x, pos.y, pos.z, yaw + 0x800, rot.vx, roll, value, 0);
}
