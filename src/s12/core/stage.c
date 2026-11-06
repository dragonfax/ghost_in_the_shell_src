/* stage: one of s12's own original source files (scripts/objmap.py); part of src/s12/main.c's unit, included there. */

extern s32 stage_active_flag;

void fx_slots_update(void);
void fx_slots_draw(void);
void fx_entries_update(void);

void stage_fx_update(void);

void cam_track_update_all(void);

void particle_update_all(void);

void stage_update(Object *obj, ObjHandler *handler) {
    cam_track_update_all();
    pos_history_push_all();
    particle_update_all();
    sound_pair_fade_update();
    if (stage_active_flag != 0) {
        stage_fx_update();
        fx_entries_update();
        scroll_segs_step();
        burst_update_all();
        sound_slots_tick_all();
        fx_slots_update();
    }
}

extern s32 stage_active_flag;

void fx_entries_hit_check(void);

void stage_shots_hit_sweep(void);

void stage_phase2(Object *obj, ObjHandler *handler) {
    s32 *temp_s0;

    pos_history_update_all();
    if (boss_state_get() == 1) {
        temp_s0 = scene_get_pos();
        supermech_m12_boss_spawn(temp_s0, scene_get_rot());
        keyframe_table_set_flag(2);
    }
    if (stage_active_flag != 0) {
        stage_shots_hit_sweep();
        fx_entries_hit_check();
        burst_check_all();
        sound_slots_hit_all();
    }
}

extern s32 stage_active_flag;

void fx_entries_draw(void);

void stage_shots_update(void);

void particle_draw_all(void);

void stage_draw(Object *obj, ObjHandler *handler) {
    pos_history_draw_all();
    particle_draw_all();
    if (stage_active_flag != 0) {
        stage_shots_update();
        fx_entries_draw();
        burst_draw_all();
        sound_slots_draw_all();
        fx_slots_draw();
    }
}

extern s32 stage_active_flag;

void particle_clear_all(void);

void fx_entries_clear_all(void);

void fx_slots_deactivate(void);

void stage_fx_clear_all(void);

void stage_systems_init(void) {
    stage_active_flag = 1;
    stage_fx_clear_all();
    particle_clear_all();
    fx_entries_clear_all();
    scroll_flags_reset();
    fx_track_flags_reset();
    pos_history_clear_all();
    burst_clear_all();
    sound_slot_clear_all();
    fx_slot_clear_all();
}

extern s32 stage_active_flag;

void spark_shot_reset(void);

void particle_teardown(void);

void giant_robot_systems_teardown(void) {
    obj_actors_clear_index();
    fx_tracks_stop_all();
    particle_teardown();
    if (stage_active_flag != 0) {
        stage_active_flag = 0;
        spark_shot_reset();
        fx_slots_deactivate();
        scroll_flush_pending();
        burst_reset();
        sound_slot_reset();
        scroll_flush_pending();
        fx_slots_reset();
        proximity_hook_set(0);
    }
}

extern s32 stage_active_flag;

void spark_src_check_sphere(ProximityQuery *q);
/* proximity_hook_fn (blast_hit_actors calls it with its query). */
void burst_check_sphere_if_ready(ProximityQuery *q) {
    if (stage_active_flag != 0) {
        spark_src_check_sphere(q);
        burst_check_sphere(q);
    }
}

s32 particles_spawn(void) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *)get_obj_list_actors_tail(), &obj->node);
    obj->handlers[1].fn = stage_update;
    obj->handlers[2].fn = stage_phase2;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = stage_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    return 1;
}

extern s32 particle_spawn_param;

void particle_spawn_param_set(s32 arg0) {
    particle_spawn_param = arg0;
}

extern s32 particle_spawn_param;

s32 particle_spawn_param_get(void) {
    return particle_spawn_param;
}

extern s16 particle_cursor_a[10];
extern s16 particle_cursor_b[10];
extern s16 particle_cursor_c[10];
/* Picks a random offset from the camera position (each axis shifted by a
   random amount of 1/16 of a random value, centred on -0x80) and hands it to
   particle_spawn with one of three tables and a scale, chosen at random. */
void particle_spawn(s32 pos_src, s32 vel_src, s32 accel_src, s32 unk_2C_val, s32 cursor_src, u16 flags_42);
void particle_spawn_near_cam(void) {
    Vec3 pos;
    s16 vel[3];
    s16 accel[3];
    s32 unk_2C_val;

    pos.x = VEC_80139584.x >> 12;
    pos.y = VEC_80139584.y >> 12;
    pos.z = VEC_80139584.z >> 12;
    pos.x -= 0x80 - rand_a_next() / 16;
    pos.y -= rand_a_next() / 16;
    pos.z -= 0x80 - rand_a_next() / 16;
    vel[0] = 0;
    vel[1] = 0;
    vel[2] = 0;
    accel[0] = 0;
    accel[1] = 0;
    accel[2] = 0;
    unk_2C_val = particle_spawn_param_get();
    switch (rand_a_next() & 3) {
    case 0:
        particle_spawn((s32)&pos, (s32)vel, (s32)accel, unk_2C_val, (s32)particle_cursor_a, 0x1000);
        break;
    case 1:
        particle_spawn((s32)&pos, (s32)vel, (s32)accel, unk_2C_val, (s32)particle_cursor_b, 0x800);
        break;
    case 2:
        particle_spawn((s32)&pos, (s32)vel, (s32)accel, unk_2C_val, (s32)particle_cursor_c, 0x555);
        break;
    }
}

void stage_end_fall_sound(void) {
    sound_fall_start();
}

extern s32 D_80121690;

void supermech_reset_flag(void) {
    D_80121690 = 0;
}

extern ObjectMode *fade_target_obj;
void fade_colour_step(FadeEffect *f) {
    s32 q;
    s32 v;

    q = f->timer / 6144;
    q = 0x1000 - q;
    v = q * 0xFF;
    f->colour[0] = v / 4096;
    f->colour[1] = 0;
    f->colour[2] = 0;
    if (f->timer <= 0 || f->limit > 0) {
        f->colour[3] = 0;
        fade_target_obj->mode = 4;
    }
}

extern ObjectMode *fade_target_obj;
void fade_update(FadeEffect *f) {
    s32 q;
    s32 v;

    q = f->timer / 6144;
    q = 0x1000 - q;
    v = q * 0xFF;
    f->colour[0] = v / 4096;
    f->colour[1] = 0;
    f->colour[2] = 0;
    if (f->timer <= 0 || f->limit > 0) {
        f->colour[3] = 0;
        fade_target_obj->mode = 4;
    }
    f->pos += 0x40;
}

extern RecTemplate fade_red_fx_template;
void fade_colour_step(FadeEffect *f);
/* Starts a record from the template D_8011E054 with fn_800C5620 as its callback; pos is passed through. */
s32 fade_colour_spawn(s32 *pos) {
    return fx_spawn_template(pos, &fade_red_fx_template, fade_colour_step);
}

extern RecTemplate fade_red_fx_template;
void fade_update();
/* Starts a record from the template D_8011E054 with fn_800C5620 as its callback; pos is passed through. */
s32 fade_start(s32 *pos) {
    return fx_spawn_template(pos, &fade_red_fx_template, fade_update);
}

void func_800C5584(void) {
}

extern FxRecordParams fx_rec34_params;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void fx_rec34_spawn_default(s32 *pos) {
    fx_rec34_spawn_cb(pos, &fx_rec34_params, 0);
}

extern RecTemplate blast_template_a;
extern RecTemplate fx_owner_template_b;
void fx_burst_spawn(s32 *pos, void *rot, s32 index) {
    fx_spawn_template(pos, &blast_template_a, NULL);
    fx_spawn_template(pos, &fx_owner_template_b, NULL);
    if (index >= 0) {
        object_spawn_at(pos, rot, index);
    }
    sound_play(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x7F, 0xC0, 0x30);
    sound_play(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3F, 0x30);
}

/* Record callback (fx_spawn_template passes the record's pos, assumed): raises y by 0x40. */
void blast_rise(Vec3 *pos) {
    pos->y += 0x40;
}

extern RecTemplate blast_template_a;
extern RecTemplate fx_owner_template_b;
/* Registers the two callbacks with fx_spawn_template, spawns the object at index when index is not
 * negative, and plays sounds 0x2022 and 0x2021 (pan 0xC0 and 0x3F, note 0x30). */
void blast_spawn(s32 *pos, void *rot, s32 index) {
    fx_spawn_template(pos, &blast_template_a, blast_rise);
    fx_spawn_template(pos, &fx_owner_template_b, blast_rise);
    if (index >= 0) {
        object_spawn_at(pos, rot, index);
    }
    sound_play(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x7F, 0xC0, 0x30);
    sound_play(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3F, 0x30);
}

void fly_start(Vec3 *pos, Unaligned8 *src, s32 slot);

void explode_fx_phase0(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    s16 rot[3];
    s32 tick, size;
    s32 rx, ry, rz;
    s32 x, y, z;

    switch (obj->vars.explode.state) {
    case 1:
        tick = obj->vars.explode.timer;
        if (tick & 1) {
            register s32 height asm("$3"); /* pins the half-height in v1 */

            rx = obj->width;
            ry = (s16)obj->height;
            rz = obj->unk_1E8[0];
            tick = tick / 2;
            rx = rx * (rand_a_next() - 0x800) / 4096;
            ry = ry * (rand_a_next() - 0x800) / 4096;
            rz = rz * (rand_a_next() - 0x800) / 4096;
            x = obj->x >> 12;
            height = (s16)obj->height;
            y = (obj->y >> 12) - height / 2;
            x += rx;
            y += ry;
            z = obj->z >> 12;
            z += rz;
            size = ((tick & 1) == 0) << 1;
            if ((tick & 3) == 0) {
                spawn_effect(x, y, z, (size + 0x7F00) | 0x80000000);
            } else {
                spawn_effect(x, y, z, size | 0x80000000);
            }
        }
        obj->vars.explode.timer++;
        if (obj->vars.explode.timer >= 120) {
            obj->vars.explode.state = 2;
            obj->vars.explode.timer = 0;
        }
        break;
    case 2:
        obj->vars.explode.timer++;
        if (obj->vars.explode.timer >= 12) {
            s32 height;

            pos[0] = obj->x >> 12;
            height = (s16)obj->height;
            pos[1] = (obj->y >> 12) - height / 2;
            pos[2] = obj->z >> 12;
            fade_colour_spawn(pos);
            obj->vars.explode.state = 3;
            obj->vars.explode.timer = 0;
        }
        break;
    case 4:
        obj->vars.explode.state = 5;
        obj->vars.explode.timer = 0;
        break;
    case 5:
        obj->vars.explode.timer++;
        if (obj->vars.explode.timer >= 6) {
            obj->vars.explode.state = 6;
            obj->vars.explode.timer = 0;
        }
        break;
    case 6:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot[0] = obj->pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        fx_rec34_spawn_default(pos);
        fly_start((Vec3 *)pos, (Unaligned8 *)rot, obj->unk_1E8[0]);
        pos[1] -= (s16)obj->height / 2;
        fx_burst_spawn(pos, rot, obj->vars.explode.spawn_index);
        obj->vars.explode.state = 7;
        break;
    case 7:
        obj->vars.explode.timer++;
        if (obj->vars.explode.timer >= 210) {
            obj->vars.explode.state = 8;
            obj_free(obj);
        }
        break;
    }
}

void explode_phase0(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    s16 rot[3];
    s32 n;
    s32 dx, dy, dz;
    s32 x, y, z;
    s32 size;

    switch (obj->vars.explode.state) {
    case 1:
        n = obj->vars.explode.timer;
        if (n & 1) {
            dx = obj->width;
            dy = (s16) obj->height;
            dz = obj->unk_1E8[0];
            n = n / 2;
            dx = dx * (rand_a_next() - 0x800) / 4096;
            dy = dy * (rand_a_next() - 0x800) / 4096;
            dz = dz * (rand_a_next() - 0x800) / 4096;
            x = obj->x >> 12;
            y = obj->y >> 12;
            z = obj->z >> 12;
            x += dx;
            y += dy;
            z += dz;
            size = ((n & 1) == 0) * 2;
            if (!(n & 3)) {
                spawn_effect(x, y, z, (size + 0x7F00) | 0x80000000);
            } else {
                spawn_effect(x, y, z, size | 0x80000000);
            }
        }
        obj->vars.explode.timer++;
        if (obj->vars.explode.timer >= 120) {
            obj->vars.explode.state = 2;
            obj->vars.explode.timer = 0;
        }
        break;
    case 2:
        obj->vars.explode.timer++;
        if (obj->vars.explode.timer >= 12) {
            pos[0] = obj->x >> 12;
            pos[1] = obj->y >> 12;
            pos[2] = obj->z >> 12;
            fade_start(pos);
            obj->vars.explode.state = 3;
            obj->vars.explode.timer = 0;
        }
        break;
    case 4:
        obj->vars.explode.state = 5;
        obj->vars.explode.timer = 0;
        break;
    case 5:
        obj->vars.explode.timer++;
        if (obj->vars.explode.timer >= 6) {
            obj->vars.explode.state = 6;
            obj->vars.explode.timer = 0;
        }
        break;
    case 6:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot[0] = obj->pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        blast_spawn(pos, rot, -1);
        obj->vars.explode.state = 7;
        if (obj->vars.explode.source != NULL) {
            obj->vars.explode.source->vars.h.unk_256 = 0;
            obj->vars.explode.source = NULL;
        }
        break;
    case 7:
        obj->vars.explode.timer++;
        if (obj->vars.explode.timer >= 210) {
            set_stage_end(2);
            obj->vars.explode.state = 8;
        }
        break;
    }
}

/* Copies the position of the object whose pointer is in vars.snd.unk_248 (if set) into obj. */
void sound_obj_follow(Object *obj, ObjHandler *handler) {
    Object *src = (Object *)obj->vars.sound_obj.source_obj;

    if (src != NULL) {
        obj->x = src->x;
        obj->y = src->y;
        obj->z = src->z;
    }
}

void spark_emitter_draw(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    u16 rot[3];
    s32 value, px, py, pz;
    u16 r0, r1, r2;
    s32 n;
    s32 colour;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    if (obj->vars.replacement.timer < 7) {
        px = obj->x >> 12;
        pos[0] = px;
        colour = 0x60C0FF;
        py = obj->y >> 12;
        pos[1] = py;
        pz = obj->z >> 12;
        pos[2] = pz;
        n = spark_count;
        r0 = obj->pitch;
        rot[0] = r0;
        r1 = obj->yaw;
        rot[1] = r1;
        list = &spark_list;
        r2 = obj->roll;
        rot[2] = r2;
        value = obj->vars.replacement.state;
        if (n < 0xFF) {
            s = &list->items[n];
            n++;
            spark_count = n;
            *(s32 *)s->colour = colour;
            tail = spark_list_tail;
            spark_list_tail = &s->next;
            *tail = n;
            s->next = 0;
            s->x = px;
            s->y = py;
            s->z = pz;
            s->unk_12 = value;
            s->yaw = r1;
            s->pitch = r0;
            s->roll = r2;
        }
    }
}

/* Clears enemy.unk_250, then calls func_800C5584 (which takes no arguments). */
void enemy_clear_state(Object *obj) {
    obj->vars.enemy.unk_250 = 0;
    func_800C5584();
}

void explode_fx_phase0(Object *obj, ObjHandler *handler);
/* Spawns an object copying the placement fields of src, and sets its handlers. */
s32 obj_spawn_replacement(Object *src, s32 arg1) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    obj->x = src->x;
    obj->y = src->y;
    obj->z = src->z;
    obj->width = src->width;
    obj->height = src->height;
    obj->unk_1E8[0] = src->unk_1E8[0];
    obj->yaw = src->yaw;
    obj->pitch = src->pitch;
    obj->roll = src->roll;
    obj->handlers[0].fn = explode_fx_phase0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = spark_emitter_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    enemy_clear_state(obj);
    obj->vars.replacement.state = arg1;
    obj->vars.replacement.timer = 1;
    obj->vars.replacement.unused_254 = 0;
    fade_target_obj = (ObjectMode *)obj;
    obj->vars.replacement.unk_248 = 0;
    return 1;
}

void explode_phase0(Object *obj, ObjHandler *handler);
s32 sound_obj_spawn(Object *src, s32 sound) {
    Object *obj;
    s16 roll;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->x = src->x;
    obj->y = src->y;
    obj->z = src->z;
    obj->width = src->width;
    obj->height = src->height;
    obj->unk_1E8[0] = src->unk_1E8[0];
    obj->yaw = src->yaw;
    obj->pitch = src->pitch;
    roll = src->roll;
    obj->handlers[0].fn = explode_phase0;
    obj->vars.sound_obj.source_obj = (s32) src;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = sound_obj_follow;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = NULL;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->roll = roll;
    enemy_clear_state(obj);
    obj->vars.snd.sound = sound;
    obj->vars.sound_obj.unused_250 = 1;
    obj->vars.sound_obj.unused_254 = 0;
    fade_target_obj = (ObjectMode *) obj;
    return 1;
}

void particle_update(ParticleSlot *entry) {
    ParticleSlotFields *e = (ParticleSlotFields *) entry;

    e->pos_x += e->vel_x;
    e->pos_y += e->vel_y;
    e->pos_z += e->vel_z;
    e->vel_x += e->accel_x;
    e->vel_y += e->accel_y;
    e->vel_z += e->accel_z;
    e->result = particle_keyframe_next(&e->cursor, &e->keyframe_time, &e->chan_a_start, &e->chan_a_end, &e->chan_b_start, &e->chan_b_end, &e->blend_factor);
}

void particle_update(ParticleSlot *entry);
extern ParticleSlot particle_pool[];
void particle_update_all(void) {
    ParticleSlot *entry = particle_pool;
    s32 i;

    for (i = 0; i < 0x30; i++, entry++) {
        if (entry->active != 0) {
            particle_update(entry);
        }
    }
}

void particle_draw(GlowParticle *g) {
    s32 base = g->base;
    s32 pos_a = base;
    s32 pos_b = base;
    s32 shade;
    s32 shade2;
    s32 colour;
    s32 inv;
    s32 value;
    s32 blend;
    u16 size;

    pos_a += g->offset_a;
    pos_b += g->offset_b;
    shade = (g->colour << 16) >> 21;
    shade2 = shade;
    if (shade == 0) {
        shade2 = 1;
    }
    blend = g->blend;
    inv = 0x1000 - blend;
    colour = (shade2 << 16) | (shade << 8) | shade;
    value = pchr_blend(pos_a, pos_b, inv, 1);
    size = g->from;
    if (size != g->to) {
        s32 mix = size * inv + g->to * blend;

        size = mix / 0x1000;
    }
    value = pool_spawn_scaled(value, (s16)size, (s16)size, (s16)size);
    spark_add(g->x >> 12, g->y >> 12, g->z >> 12, 0, 0, 0, value, colour);
}

/* Same code as particle_update_all (s12). */
void particle_draw_all(void) {
    ParticleSlot *entry = particle_pool;
    s32 i;

    for (i = 0; i < 0x30; i++, entry++) {
        if (entry->active != 0) {
            particle_draw((GlowParticle *)entry);
        }
    }
}

/* Returns the first of the 48 entries whose unk_3E flag is clear, or NULL. */
ParticleSlot *particle_alloc(void) {
    ParticleSlot *entry = particle_pool;
    s32 i;

    for (i = 0; i < 0x30; i++) {
        if (entry->active == 0) {
            return entry;
        }
        entry++;
    }
    return NULL;
}

/* Fills the first free entry of the 0x30-entry table: position and velocity
   (shifted up by 12), accel copied from an 8-byte packed block, the cursor
   and a result from particle_keyframe_next. */
void particle_spawn(s32 pos_src, s32 vel_src, s32 accel_src, s32 unk_2C_val, s32 cursor_src, u16 flags_42) {
    ParticleSlotFields *entry;

    entry = (ParticleSlotFields *) particle_alloc();
    if (entry != NULL) {
        *(s16 *) entry->unk_2C = unk_2C_val;
        tick_reset(&entry->keyframe_time);
        entry->cursor = (s16 *) cursor_src;
        entry->result = particle_keyframe_next(&entry->cursor, &entry->keyframe_time, &entry->chan_a_start, &entry->chan_a_end,
                                      &entry->chan_b_start, &entry->chan_b_end, (s16 *) &entry->blend_factor);
        entry->pos_x = *(s32 *) pos_src << 12;
        entry->pos_y = *(s32 *) (pos_src + 4) << 12;
        entry->pos_z = *(s32 *) (pos_src + 8) << 12;
        if (vel_src != 0) {
            entry->vel_x = *(s16 *) vel_src << 12;
            entry->vel_y = *(s16 *) (vel_src + 2) << 12;
            entry->vel_z = *(s16 *) (vel_src + 4) << 12;
        } else {
            entry->vel_x = 0;
            entry->vel_y = 0;
            entry->vel_z = 0;
        }
        if (accel_src != 0) {
            *(Unaligned8 *) &entry->accel_x = *(Unaligned8 *) accel_src;
            entry->flags = flags_42;
        } else {
            entry->accel_x = 0;
            entry->accel_y = 0;
            entry->accel_z = 0;
            entry->flags = flags_42;
        }
    }
}

void particle_spawn_default(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    particle_spawn(a0, a1, a2, a3, a4, 0x1000);
}

/* Clears unk_3E (a s16 flag) in all 0x30 entries of the table. */
void particle_clear_all(void) {
    ParticleSlot *entry = particle_pool;
    s32 i = 0x2F;

    do {
        entry->active = 0;
        i--;
        entry++;
    } while (i >= 0);
}

void particle_teardown(void) {
    particle_clear_all();
}

void shot_move(ShotMover *s) {
    s32 x, dx;
    s->x += s->vx;
    s->y += s->vy;
    s->z += s->vz;
    if (s->y >= -0x338) {
        s->active = 0;
    }
    if (ABS(s->z) > 0x1F40) {
        s->active = 0;
    }
    x = s->x;
    dx = x + 0x2EE00;
    if (dx >= 0 ? dx > 0x1F40 : -0x2EE00 - x > 0x1F40) {
        s->active = 0;
    }
}

extern ShotPoolEntry shot_pool[];
void shot_update_all(void) {
    ShotPoolEntry *entry = shot_pool;
    s32 i;

    for (i = 0; i < 0x30; i++, entry++) {
        if (entry->active != 0) {
            shot_move((ShotMover *)entry);
        }
    }
}

void shot_clear_hit(s32 flags) {
    ShotHitState *e = (ShotHitState *)shot_pool;
    s32 i;

    flags >>= 1;
    for (i = 0; i < 0x30; i++, e++) {
        if (e->active != 0 && e->hit != 0 && (s16)e->flags >> 1 == flags) {
            e->hit = 0;
        }
    }
}

extern void shot_clear_hit(s32 arg);
void hitbox_sweep(Hitbox *rec) {
    HitboxBounds *a = scratch_alloc(0x10);
    HitboxBounds *b = scratch_alloc(0x10);
    s32 *c;

    *b = rec->box;
    *a = *b;
    a->w[0] -= rec->size[0];
    a->w[1] -= rec->size[1];
    a->w[2] -= rec->size[2];
    c = scratch_alloc(0x10);
    if (sweep_hit_test((Vec3 *)a, (Vec4 *)b, (Vec4 *)c, 0x48, 4, rec->unk_1E)) {
        if (ABS(c[0]) > 0x1500 && ABS(c[2]) < 0x1500) {
            spawn_effect(c[0], c[1], c[2], (rec->flags & 1) ? 0x80020002 : 0x80000002);
        }
        rec->unk_1C = 0;
        shot_clear_hit((s16)rec->flags);
    }
    scratch_top -= 0x30;
}

void shot_pool_hitbox_sweep(void) {
    ShotPoolEntry *entry = shot_pool;
    s32 i;

    for (i = 0; i < 0x30; i++, entry++) {
        if (entry->active != 0) {
            hitbox_sweep((Hitbox *)entry);
        }
    }
}

void shot_spark_emit(ShotMover *s) {
    SparkPose *src = (SparkPose *)s;
    s32 value;

    value = model_slot_pchr(src->owner->table[0]);
    value = pool_spawn_scaled(value + 0x214, 0x3000, 0x3000, 0x3000);
    spark_add(src->x, src->y, src->z, 0, 0, 0, value, 0);
    req_queue_push_vec(src->x, src->y, src->z);
}

void shot_spark_emit(ShotMover *s);
/* Same code as shot_update_all (s12). */
void shot_pool_update(void) {
    ShotPoolEntry *entry = shot_pool;
    s32 i;

    for (i = 0; i < 0x30; i++, entry++) {
        if (entry->active != 0) {
            shot_spark_emit((ShotMover *)entry);
        }
    }
}

ShotPoolEntry *shot_alloc(void) {
    ShotPoolEntry *rec = shot_pool;
    s32 i;

    for (i = 0; i < 0x30; i++) {
        if (rec->active == 0) {
            return rec;
        }
        rec++;
    }
    return NULL;
}

void shot_spawn(s32 owner, s32 *src, s16 *ref, s32 flag) {
    ShotPoolEntry *rec;
    s32 vel_x;
    s32 vel_z;
    s32 vel_y;
    s32 src_z;

    rec = shot_alloc();
    if (rec != NULL) {
        *(s32 *)&rec->unk_00[0] = owner;
        rec->active = 1;
        vel_x = 0;
        vel_z = 0;
        vel_y = (rand_a_next() & 3) + 0x40;
        rotate_xz_twice(ref[1], ref[0], &vel_x, &vel_z, &vel_y);
        *(s16 *)&rec->unk_00[0x14] = vel_x;
        *(s16 *)&rec->unk_00[0x16] = vel_z;
        *(s16 *)&rec->unk_00[0x18] = vel_y;
        *(s32 *)&rec->unk_00[4] = src[0];
        *(s32 *)&rec->unk_00[8] = src[1];
        src_z = src[2];
        *(s16 *)&rec->unk_00[0x1E] = 0xA;
        *(s16 *)&rec->unk_00[0x20] = flag;
        *(s32 *)&rec->unk_00[0xC] = src_z;
    }
}

/* Clears unk_1C of all 0x30 entries in shot_pool. */
void shot_clear_all(void) {
    ShotPoolEntry *entry;
    s32 i;

    entry = shot_pool;
    i = 0x2F;
    do {
        entry->active = 0;
        i -= 1;
        entry++;
    } while (i >= 0);
}

void shot_reset(void) {
    shot_clear_all();
}

extern s16 D_8012D70C;
void func_800C6B2C(void) {
    s32 i;
    s16 *entry;
    s32 val;

    i = 0;
    val = 0x61;
    entry = &D_8012D70C;
    do {
        if (entry[-1] != 0) {
            entry[0] = val;
        }
        i++;
        entry += 0x14;
    } while (i < 6);
}

extern s16 spark_trail_template[10];
extern s16 spark_particle_template[6];
extern s32 spark_serial;
void spark_src_step(SparkSource *e) {
    VECTOR trail;
    VECTOR pos;
    s16 rot[3];
    s32 i;

    if (!(e->timer & 1)) {
        trail = e->pos;
        trail.vx -= e->vel[0];
        trail.vy -= e->vel[1];
        trail.vz -= e->vel[2];
        particle_spawn_default((s32)&trail, 0, 0, get_model_slot_base(), (s32)spark_trail_template);
    }
    {
        s32 dx = e->vel[0];
        s32 dy = e->vel[1];
        s32 dz = e->vel[2];

        s32 z;
        s16 t;

        e->pos.vx += dx;
        z = e->pos.vz;
        e->pos.vy += dy;
        t = e->timer;
        e->pos.vz = z + dz;
        e->timer = t + 1;
    }
    if (e->pos.vy >= -0x400) {
        e->active = 0;
    }
    if (ABS(e->pos.vz) > 0x1F40) {
        e->active = 0;
    }
    if (e->pos.vx + 0x2EE00 >= 0) {
        if (e->pos.vx + 0x2EE00 > 0x1F40) {
            goto out_of_range;
        }
    } else if (-0x2EE00 - e->pos.vx > 0x1F40) {
    out_of_range:
        e->active = 0;
    }
    if (e->timer < 0xD) {
        return;
    }
    if (e->timer < 0x61) {
        if (player_dist_sq(&e->pos.vx) > 0x22550F) {
            return;
        }
        if (!is_facing_target(&e->pos.vx, e->rot_y, 0x200)) {
            return;
        }
    }
    pos = e->pos;
    particle_spawn((s32)&pos, 0, 0, model_slot_pchr(*(s32 *)e->owner->asset), (s32)spark_particle_template, 0x1000);
    rot[0] = e->rot_x;
    rot[1] = e->rot_y;
    rot[2] = e->rot_z;
    rot[0] -= 0x80;
    if (pos.vx + 0x2EE00 >= 0) {
        if (pos.vx + 0x2EE00 >= 0x1500) {
            e->active = 0;
            return;
        }
    } else if (-0x2EE00 - pos.vx >= 0x1500) {
        goto done;
    }
    if (ABS(pos.vz) < 0x1500) {
        s32 flag;

        sound_play_at_units(SND_SPARK_BURST | SND_GROUP(2), 0x7F, 0x3C, &pos);
        spark_serial++;
        spark_serial %= 0x1000;
        flag = spark_serial;
        flag <<= 1;
        for (i = 1; i < 4; i++) {
            shot_spawn((s32)e->owner, &pos.vx, rot, flag | 1);
            rot[1] += 0x50 + rand_a_next() / 42;
            rot[0] += rand_a_next() / 128 - 0x10;
            shot_spawn((s32)e->owner, &pos.vx, rot, flag);
            rot[1] -= 0xD0 + rand_a_next() / 42;
            rot[0] += rand_a_next() / 128 - 0x10;
            shot_spawn((s32)e->owner, &pos.vx, rot, flag);
            rot[1] += 0x50 + rand_a_next() / 42;
            rot[0] = rot[0] - 0x10 + rand_a_next() / 128 - (i << 6);
        }
    }
done:
    e->active = 0;
}

void spark_src_step(SparkSource *e);
extern SparkSource spark_src_pool[];
void spark_src_update_all(void) {
    SparkSource *entry = spark_src_pool;
    s32 i;

    for (i = 0; i < 0x6; i++, entry++) {
        if (entry->active != 0) {
            spark_src_step(entry);
        }
    }
}

/* Sweeps from the object's position minus its offset; on result 2 spawns an effect at the hit point. */
void shot_sweep_test(ShotSweep *obj) {
    VECTOR *start = scratch_alloc(0x10);
    VECTOR *end = scratch_alloc(0x10);
    VECTOR *hit = scratch_alloc(0x10);

    *end = obj->from;
    *start = *end;
    start->vx -= obj->off[0];
    start->vy -= obj->off[1];
    start->vz -= obj->off[2];
    if (sweep_hit_test((Vec3 *)start, (Vec4 *)end, (Vec4 *)hit, 0x24, 4, 10) == 2) {
        spawn_effect(hit->vx, hit->vy, hit->vz, 0x80060000);
        obj->unk_22 = 0;
    }
    scratch_top -= 0x30;
}

void spark_src_pool_sweep(void) {
    SparkSource *entry = spark_src_pool;
    s32 i;

    for (i = 0; i < 0x6; i++, entry++) {
        if (entry->active != 0) {
            shot_sweep_test((ShotSweep *)entry); /* the same records, ShotSweep's view */
        }
    }
}

void spark_src_check_entry(SparkSource *entry, s32 *pos, s32 radius, s32 radius_sq) {
    ShotSweep *obj = (ShotSweep *)entry;
    s32 dx;
    s32 dy;
    s32 dz;

    dx = obj->from.vx - pos[0];
    dy = obj->from.vy - pos[1];
    dz = obj->from.vz - pos[2];
    if (ABS(dx) > radius) {
        return;
    }
    if (ABS(dy) > radius) {
        return;
    }
    if (ABS(dz) > radius) {
        return;
    }
    if (length_sq(dx, dy, dz) < radius_sq) {
        spawn_effect(obj->from.vx, obj->from.vy, obj->from.vz, 0x80060000);
        obj->unk_22 = 0;
    }
}

void spark_src_check_entry(SparkSource *entry, s32 *pos, s32 radius, s32 radius_sq);
void spark_src_check_sphere(ProximityQuery *q) {
    s32 *pos;
    SparkSource *entry = spark_src_pool;
    s32 radius;
    s32 radius_sq;
    s32 i;

    pos = scratch_alloc(0x10);
    pos[0] = q->x;
    pos[1] = q->y;
    pos[2] = q->z;
    radius = q->range >> 12;
    radius_sq = radius * radius;
    for (i = 0; i < 6; i++, entry++) {
        if (entry->active != 0) {
            spark_src_check_entry(entry, pos, radius, radius_sq);
        }
    }
    scratch_top -= 0x10;
}

void spark_src_update(SparkSource *entry) {
    SparkPose *src = (SparkPose *)entry;
    s32 colour = 0xFFFFFF;
    s32 value;

    value = model_slot_pchr(src->owner->table[0]);
    value = pool_spawn_scaled(value + 0x210, 0x1800, 0x1800, 0x1800);
    spark_add_head(&spark_list, src->x, src->y, src->z, src->ry, src->rx, src->rz, value, colour);
    req_queue_push_vec(src->x, src->y, src->z);
}

/* Same code as spark_src_update_all (s12). */
void spark_src_pool_update(void) {
    SparkSource *entry = spark_src_pool;
    s32 i;

    for (i = 0; i < 0x6; i++, entry++) {
        if (entry->active != 0) {
            spark_src_update(entry);
        }
    }
}

/* First of the 6 entries whose unk_22 is 0, or NULL if all are in use. */
SparkSource *spark_src_alloc(void) {
    SparkSource *entry;
    s32 i;

    entry = spark_src_pool;
    for (i = 0; i < 6; i++) {
        if (entry->active == 0) {
            return entry;
        }
        entry++;
    }
    return NULL;
}

/* Claims a free table entry and fills it from owner, a position vector and a 3-component rotation. */
void spark_src_spawn(s32 owner, s32 *pos, u16 *rot) {
    SparkSourceFields *entry;
    s32 out[3];

    entry = (SparkSourceFields *) spark_src_alloc();
    if (entry != NULL) {
        entry->owner = owner;
        entry->active = 1;
        entry->yaw = rot[1];
        entry->pitch = rot[0];
        entry->roll = rot[2];
        out[0] = 0;
        out[1] = 0;
        out[2] = 0x30;
        rotate_xz_twice(entry->yaw, entry->pitch, &out[0], &out[1], &out[2]);
        entry->dir_x = out[0];
        entry->dir_y = out[1];
        entry->dir_z = out[2];
        entry->unk_24 = 0;
        entry->pos_x = pos[0];
        entry->pos_y = pos[1];
        entry->pos_z = pos[2];
        sound_play_at_units(SND_ROCKET_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    }
}

extern s32 spark_serial;
/* Clears the active flag (unk_22) of all six table entries and the global spark_serial. */
void spark_src_clear_all(void) {
    SparkSource *entry = spark_src_pool;
    s32 i;

    for (i = 5; i >= 0; i--, entry++) {
        entry->active = 0;
    }
    spark_serial = 0;
}

void spark_src_reset(void) {
    spark_src_clear_all();
}

void stage_fx_update(void) {
    spark_src_update_all();
    shot_update_all();
}

void stage_shots_hit_sweep(void) {
    spark_src_pool_sweep();
    shot_pool_hitbox_sweep();
}

void stage_shots_update(void) {
    spark_src_pool_update();
    shot_pool_update();
}

void stage_fx_clear_all(void) {
    spark_src_clear_all();
    shot_clear_all();
}

void spark_shot_reset(void) {
    spark_src_reset();
    shot_reset();
}

extern s16 view_nudge_table[];
void fx_entry_step(FxEntry *entry) {
    s32 nudge;
    s16 *view;

    entry->result = particle_keyframe_next(&entry->cursor, &entry->remaining, &entry->out0, &entry->out1,
                                  &entry->out2, &entry->out3, &entry->out4);
    if (entry->speed <= 0) {
        entry->result = 0;
    }
    if (entry->result != 0) {
        entry->scroll += 0x200;
        entry->speed -= 0x40;
        entry->rand_2E = rand_a_next();
        entry->rand_18 = rand_a_next() + 0xFFF;
        entry->rand_1A = rand_a_next() + 0xFFF;
        entry->rand_1C = rand_a_next() + 0xFFF;
        if (entry->index >= 0) {
            nudge = view_nudge_table[entry->index];
            if (nudge < 0) {
                entry->index = -1;
                nudge = 0;
            }
            view = (s16 *) get_view_nudge();
            set_view_nudge(view[0], view[1] + nudge);
        }
    }
}

void fx_entry_step(FxEntry *entry);
extern FxEntry fx_entries[];
void fx_entries_update(void) {
    FxEntry *entry = fx_entries;
    s32 i;

    for (i = 0; i < 0x2; i++, entry++) {
        if (entry->result != 0) {
            fx_entry_step(entry);
        }
    }
}

extern Vec3 player_xyz_y;
void fx_entry_hit_check(FxEntry *entry) {
    s32 a;
    s32 t;
    s32 lo;
    s32 hi;
    s32 d;
    s32 *p;

    if ((player_xyz_y.x >> 12) < -0x410) {
        entry->index = -1;
        return;
    }
    a = entry->scroll;
    a <<= 12;
    a /= 0x1000;
    t = entry->out4;
    t = MAX(MIN(t, 0x1000), 0);
    lo = (0x1000 - t) * 0xC0 + t * 0x480;
    lo /= 0x1000;
    lo *= a;
    lo /= 0x1000;
    hi = a * 0x480;
    hi /= 0x1000;
    d = player_horiz_dist(&entry->pos_x);
    if (lo < d && d < hi) {
        p = player_position();
        hit_target_masked(0, 4, atan2(entry->pos_z - p[2], entry->pos_x - p[0]), 0x14);
    }
}

/* Same code as fx_entries_update (s12). */
void fx_entries_hit_check(void) {
    FxEntry *entry = fx_entries;
    s32 i;

    for (i = 0; i < 0x2; i++, entry++) {
        if (entry->result != 0) {
            fx_entry_hit_check(entry);
        }
    }
}


extern SVECTOR fade_target_color;
#define BLEND_TARGET fade_target_color

/* Blends `from` toward the stage's target vector by weight/4096, then scales
 * each component of `v` by the result (in 4096ths). Returns v. */
SVECTOR *color_blend_scale(SVECTOR *v, s32 weight, SVECTOR *from)
{
    s32 inv = 0x1000 - weight;
    s32 x = from->vx * inv + BLEND_TARGET.vx * weight;
    s32 y = from->vy * inv + BLEND_TARGET.vy * weight;
    s32 z = from->vz * inv + BLEND_TARGET.vz * weight;

    x /= 4096;
    y /= 4096;
    z /= 4096;
    x *= v->vx;
    y *= v->vy;
    z *= v->vz;
    x /= 4096;
    y /= 4096;
    z /= 4096;
    v->vx = x;
    v->vy = y;
    v->vz = z;
    return v;
}


void fx_entry_draw(FxEntry *entry) {
    SVECTOR scale;
    s32 base;
    s32 pos_a;
    s32 pos_b;
    s32 t;
    s32 r, g, b;
    s32 colour;
    s32 value;
    s32 size;

    base = model_slot_pchr(*(s32 *)entry->owner->asset);
    pos_a = base;
    pos_b = base;
    pos_a += (s16)entry->out0;
    pos_b += (s16)entry->out1;
    scale.vx = 0x1000;
    scale.vy = 0x1000;
    scale.vz = 0x1000;
    t = entry->speed;
    t = MAX(MIN(t, 0xFFF), 0);
    color_blend_scale(&scale, 0x1000 - t, (SVECTOR *)&entry->rand_18);
    b = scale.vz >> 5;
    g = scale.vy >> 5;
    r = scale.vx >> 5;
    if ((r | g | b) == 0) {
        b = 1;
    }
    colour = (b << 16) | (g << 8) | r;
    value = pchr_blend(pos_a, pos_b, 0x1000 - entry->out4, 1);
    size = entry->scroll;
    size <<= 12;
    size /= 0x1000;
    value = pool_spawn_scaled(value, size, size, size);
    spark_add(entry->pos_x, entry->pos_y, entry->pos_z, entry->rand_2E, 0, 0, value, colour);
    if (entry->index >= 0) {
        entry->index++;
    }
}

/* Same code as fx_entries_update (s12). */
void fx_entries_draw(void) {
    FxEntry *entry = fx_entries;
    s32 i;

    for (i = 0; i < 0x2; i++, entry++) {
        if (entry->result != 0) {
            fx_entry_draw(entry);
        }
    }
}

extern Vec3 player_xyz_y;
extern s16 fx_entry_keyframes[];
void fx_entry_init(FxEntry *entry, Object *owner, Vec3 *src) {
    s32 z;

    entry->owner = owner;
    tick_reset(&entry->remaining);
    entry->pos_x = src->x;
    entry->pos_y = src->y;
    z = src->z;
    entry->cursor = fx_entry_keyframes;
    entry->pos_z = z;
    entry->result = particle_keyframe_next(&entry->cursor, &entry->remaining, &entry->out0, &entry->out1,
                                  &entry->out2, &entry->out3, &entry->out4);
    entry->scroll = 0x800;
    entry->speed = 0x1000;
    if ((player_xyz_y.x >> 12) < -0x410) {
        entry->index = -1;
    } else {
        entry->index = 0;
    }
    sound_play(0x3169, 0x64, 0x3F, 0x3C);
    sound_play(0x516B, 0x64, 0xC0, 0x3C);
}

void fx_entry_init(FxEntry *entry, Object *owner, Vec3 *pos);
void fx_entry_spawn(Object *owner, Vec3 *pos) {
    FxEntry *entry = fx_entries;
    s32 i = 0;

    do {
        i++;
        if (entry->result == 0) {
            fx_entry_init(entry, owner, pos);
            return;
        }
        entry++;
    } while (i < 2);
}

/* Same code as func_800C8480 (s07). */
void fx_entry_clear(FxEntry *entry) {
    entry->result = 0;
}

void fx_entries_clear_all(void) {
    FxEntry *entry = fx_entries;
    s32 i = 0;
    do {
        fx_entry_clear(entry);
        i++;
        entry++;
    } while (i < 2);
}


void keytrack_slot_deactivate(KeyTrackSlot *entry) {
    entry->active = 0;
}


/* Deactivates the two FxEntry slots at fx_entries (0x3C apart) through keytrack_slot_deactivate. */
void fx_slots_deactivate(void) {
    FxEntry *entry;
    s32 i;

    entry = fx_entries;
    i = 0;
    do {
        keytrack_slot_deactivate((KeyTrackSlot *)entry);
        i++;
        entry++;
    } while (i < 2);
}

/* Advances the slot's level (dropping it when it goes negative), clamps it to
   0..0x3FFF and re-rolls its seed and its four random jitter vectors. */
void fx_slot_update(FxSlot *slot) {
    s32 i;
    s16 r;
    s32 level;
    s16 clamped;
    s16 *px;
    s16 *pz;
    s32 x, y, z;

    slot->level += slot->level_step;
    if (slot->level < 0) {
        slot->active = 0;
    }
    level = slot->level;
    clamped = MIN(level, 0x3FFF);
    if (MIN(level, 0x3FFF) < 0) {
        clamped = 0;
    }
    slot->level = clamped;
    slot->seed = rand_a_next();
    px = &slot->jitter[0].vx;
    i = 0;
    pz = &slot->jitter[0].vz;
    do {
        i++;
        r = rand_a_next();
        x = r & 0xFF;
        y = (r >> 2) & 0xFF;
        z = (r >> 4) & 0xFF;
        x -= 0x7F;
        y -= 0x7F;
        z -= 0x7F;
        x *= 2;
        y *= 2;
        z *= 2;
        *px = x;
        pz[-1] = y;
        *pz = z;
        pz += 4;
        px += 4;
    } while (i < 4);
}

void fx_slot_update(FxSlot *slot);
extern FxSlot fx_slot_pool[];
void fx_slots_update(void) {
    FxSlot *entry = fx_slot_pool;
    s32 i;

    for (i = 0; i < 0x2; i++, entry++) {
        if (entry->active != 0) {
            fx_slot_update(entry);
        }
    }
}

extern SVECTOR D_8012174C;
extern SVECTOR D_80121754;
/* Sparks of an effect slot at its owner's model part (9 when unk_3A is 0, else 11): one spark tinted by the
   slot's level and seed (red = green, blue from twice the brightness), then four white ones at the jitter
   offsets. */
void fx_slot_draw(FxSlot *slot) {
    SVECTOR offset;
    s32 x, y, z;
    s32 part;
    s32 level;
    s32 blue_level;
    register s32 doubled asm("$3");
    s32 red;
    s32 blue;
    s32 colour;
    s32 white;
    s16 value;
    s32 i;

    part = 11;
    if (slot->unk_3A == 0) {
        offset = D_8012174C;
        part = 9;
    } else {
        offset = D_80121754;
    }
    colour = slot->level;
    level = MIN(colour, 0x1000);
    if (MIN(colour, 0x1000) < 0) {
        level = 0;
    }
    colour = level;
    colour += slot->seed / 2;
    doubled = colour * 2;
    blue_level = doubled;
    if (doubled >= 0x2000) {
        blue_level = 0x1FFF;
    }
    if (MIN(doubled, 0x1FFF) < 0) {
        blue_level = 0;
    }
    blue = blue_level >> 5;
    red = colour >> 5;
    if ((red | blue) == 0) {
        blue = 1;
    }
    colour = (blue << 16) | (red << 8) | red;
    model_part_transform(slot->owner->vars.words[0], part, &offset);
    obj_point_to_world(slot->owner, &offset.vx, &x, &y, &z);
    value = pool_spawn_scaled((s16)(model_slot_pchr(*(s32 *)slot->owner->asset) + 0x235),
                              slot->level * 2, slot->level * 2, slot->level * 2);
    spark_add(x, y, z, 0, 0, 0, value, colour);
    white = 0xFFFFFF;
    for (i = 0; i < 4; i++) {
        offset = slot->jitter[i];
        model_part_transform(slot->owner->vars.words[0], part, &offset);
        obj_point_to_world(slot->owner, &offset.vx, &x, &y, &z);
        value = pool_spawn_scaled((s16)(model_slot_pchr(*(s32 *)slot->owner->asset) + slot->seed % 3 + 0x208),
                                  0x3000, 0x3000, 0x3000);
        /* copied in the loop: loop.c hoists the copy, and the colour stays unknown to cse inside */
        colour = white;
        spark_add_link(x, y, z, 0, 0, 0, value, colour);
    }
}

/* Same code as fx_slots_update (s12). */
void fx_slots_draw(void) {
    FxSlot *entry = fx_slot_pool;
    s32 i;

    for (i = 0; i < 0x2; i++, entry++) {
        if (entry->active != 0) {
            fx_slot_draw(entry);
        }
    }
}

/* Returns the first of the two entries whose unk_38 is zero, or NULL. */
FxSlot *fx_slot_alloc(void) {
    FxSlot *entry = fx_slot_pool;
    s32 i;

    for (i = 0; i < 0x2; i++, entry++) {
        if (entry->active == 0) {
            return entry;
        }
    }
    return NULL;
}

/* Claims a free entry and initialises it with the owner and a parameter. */
void fx_slot_spawn(s32 owner, s16 param) {
    FxSlotSpawn *entry = (FxSlotSpawn *)fx_slot_alloc();

    if (entry != NULL) {
        entry->unk_38 = 1;
        entry->owner = owner;
        entry->unk_3A = param;
        entry->unk_34 = 0;
        entry->unk_36 = 0x400;
    }
}

extern s16 fx_id_records[];
/* Two 0x40-byte records start at fx_id_records; each has an id halfword at +4.
 * A record whose id matches gets its halfword at -2 cleared and its halfword
 * at +0 set to -0x200. */
void fx_stop_by_id(s32 id) {
    s32 i;
    u8 *rec;

    for (i = 0; i < 2; i++) {
        rec = (u8 *) fx_id_records + i * 0x40;
        if (*(s16 *) (rec + 4) == id) {
            *(s16 *) (rec - 2) = 0;
            *(s16 *) rec = -0x200;
        }
    }
}

void fx_slot_clear_all(void) {
    FxSlot *entry;
    s32 i;

    entry = fx_slot_pool;
    i = 1;
    do {
        entry->active = 0;
        i -= 1;
        entry += 1;
    } while (i >= 0);
}

void fx_slots_reset(void) {
    fx_slot_clear_all();
}

void pos_history_free(s32 idx);
void pos_history_set_pose(s32 index, s32 pose, s32 scale, s32 arg);
void scroll_seg_step(ScrollSeg *seg) {
    s32 i;
    s32 t;
    s32 mul;

    if (seg->active != 0) {
        seg->pos += seg->vel;
        if ((s16)seg->pos >= 0x1001) {
            seg->pos = 0x1000;
        }
        if ((s16)seg->pos < 0) {
            seg->active = 0;
            for (i = 0; i < 3; i++) {
                pos_history_free(seg->vals[i]);
            }
        } else {
            t = seg->scale * (s16)seg->pos;
            mul = t >> 12;
            if (t < 0) {
                mul = (t + 0xFFF) >> 12;
            }
            for (i = 0; i < 3; i++) {
                pos_history_set_pose(seg->vals[i], seg->base + i, mul, ((s16)seg->pos / 2) + 0x800);
            }
        }
    }
}

extern ScrollSeg D_8012D8D0;
extern ScrollSeg D_8012D8E8;
/* Steps both segments. */
void scroll_segs_step(void) {
    scroll_seg_step(&D_8012D8D0);
    scroll_seg_step(&D_8012D8E8);
}

s32 pos_history_add(Object *obj, s32 a1, s32 a2, s32 a3);
/* Starts scroll segment mode 0-3: modes 0 and 2 use the first segment, 1 and 3 the second; 2 and 3 at half scale. */
void scroll_seg_start(Object *obj, s32 mode) {
    ScrollSeg *seg;
    s32 base;
    s32 scale;
    s32 rel;
    s32 half;
    s32 garbage; /* never set: the original stores whatever $v1 holds on entry */

    if (mode == 0 || mode == 2) {
        seg = &D_8012D8D0;
        base = 0;
    } else {
        seg = &D_8012D8E8;
        base = 3;
    }
    seg->vel = 0x100;
    seg->active = 1;
    /* set-once values, so sched1 keeps the test above the stores */
    rel = mode - 2;
    half = (u32)rel < 2;
    seg->pos = 0;
    seg->unk_00[1] = garbage;
    seg->base = base;
    /* loop notes: keep the scale's li after the stores (it fills the branch's delay slot) */
    do { } while (0);
    scale = 0x800;
    if (half) {
        scale = 0x400;
    }
    seg->scale = scale;
    seg->vals[0] = pos_history_add(obj, base, scale, (s16)seg->pos);
    seg->vals[1] = pos_history_add(obj, base + 1, scale, (s16)seg->pos);
    seg->vals[2] = pos_history_add(obj, base + 2, scale, (s16)seg->pos);
}

extern s16 scroll_pending_a;
extern s16 scroll_pending_b;

void scroll_flags_reset(void) {
    scroll_pending_a = 0;
    scroll_pending_b = 0;
}

/* Sets the vel (0x0A) of one of the two segments to -0xAA; flag 0 picks D_8012D8D0, otherwise D_8012D8E8. */
void scroll_seg_retract(s32 flag) {
    s16 *state = (s16 *) &D_8012D8E8;

    if (flag == 0) {
        state = (s16 *) &D_8012D8D0;
    }
    state[5] = -0xAA;
}

void pos_history_free(s32 idx);
void scroll_flush_pending(void) {
    s16 *base;
    s16 *p;
    s32 i;

    base = &scroll_pending_a;
    if (*base == 1) {
        i = 0;
        p = base + 3;
        do {
            pos_history_free(*p);
            p++;
            i++;
        } while (i < 3);
    }
    base = &scroll_pending_b;
    if (*base == 1) {
        i = 0;
        p = base + 3;
        do {
            pos_history_free(*p);
            p++;
            i++;
        } while (i < 3);
    }
    scroll_pending_a = 0;
    scroll_pending_b = 0;
}

void pos_history_push(PosHistoryEntry *entry) {
    PosHistorySlot *slot;
    s16 count;
    s32 next;

    if (entry->active != 0) {
        entry->index++;
        entry->index = entry->index % 64;
        slot = &entry->slots[entry->index];
        slot->unk_00 = *(Quad *)entry->world_pos;
        slot->pos = entry->cur;
        /* push the current pair into the 64-slot ring, count up to 31 */
        next = entry->count + 1;
        count = MIN(next, 0x1F);
        if (MIN(next, 0x1F) < 0) {
            count = 0;
        }
        entry->count = count;
        entry->rnd = rand_a_next();
    }
}

void pos_history_push(PosHistoryEntry *entry);
extern PosHistoryEntry pos_history_table[];
void pos_history_push_all(void) {
    PosHistoryEntry *entry = pos_history_table;
    s32 i;

    for (i = 0; i < 0x6; i++, entry++) {
        if (entry->active != 0) {
            pos_history_push(entry);
        }
    }
}

extern BlendVec blend_vec_null;
/* Blends two table vectors by num/den, adds offset, scales by scale/0x1000
 * and stores base + that into dst->result. */
void blend_vec_lerp(BlendSrc *src, BlendDst *dst, BlendVec *table, SVECTOR *offset, s32 scale) {
    BlendVec *a;
    BlendVec *b;
    s32 t = src->num;
    u32 ia = src->index_a;
    u32 ib = src->index_b;
    s32 inv;
    s32 x, y, z;

    ia -= 0x180;
    t = (t << 12) / src->den;
    ib -= 0x180;
    if (ia >= 0x80) {
        a = &blend_vec_null;
    } else {
        a = &table[ia];
    }
    if (ib >= 0x80) {
        b = &blend_vec_null;
    } else {
        b = &table[ib];
    }
    inv = 0x1000 - t;
    x = a->x * t + b->x * inv;
    y = a->y * t + b->y * inv;
    z = a->z * t + b->z * inv;
    x = x / 0x1000;
    y = y / 0x1000;
    z = z / 0x1000;
    x += offset->vx;
    z += offset->vz;
    y += offset->vy;
    x = x * scale / 0x1000;
    y = y * scale / 0x1000;
    z = z * scale / 0x1000;
    dst->result[0] = x + dst->base[0];
    dst->result[1] = y + dst->base[1];
    dst->result[2] = z + dst->base[2];
}

extern BlendVec blend_base_null;
void blend_base_lerp(BlendSrc *src, BlendDst *dst, BlendVec *table) {
    BlendVec *a;
    BlendVec *b;
    s32 t = src->num;
    u32 ia = src->index_a;
    u32 ib = src->index_b;
    s32 inv;
    s32 x, y, z;

    ia -= 0x180;
    t = (t << 12) / src->den;
    ib -= 0x180;
    if (ia >= 0x80) {
        a = &blend_base_null;
    } else {
        a = &table[ia];
    }
    if (ib >= 0x80) {
        b = &blend_base_null;
    } else {
        b = &table[ib];
    }
    inv = 0x1000 - t;
    x = a->x * t + b->x * inv;
    y = a->y * t + b->y * inv;
    z = a->z * t + b->z * inv;
    x = x / 0x1000;
    y = y / 0x1000;
    z = z / 0x1000;
    x = x * 0x1800 / 0x1000;
    y = y * 0x1800 / 0x1000;
    z = z * 0x1800 / 0x1000;
    x = -x;
    z = -z;
    y = -y;
    dst->base[0] = x;
    dst->base[1] = y;
    dst->base[2] = z;
}

void obj_local_to_world(Object *obj, s32 *out) {
    rotate_xz_twice(obj->yaw, -obj->pitch, out, &out[1], &out[2]);
    out[0] += obj->x >> 12;
    out[1] += obj->y >> 12;
    out[2] += obj->z >> 12;
}

extern s16 *pose_from_table[];
extern s16 *pose_to_table[];
extern BlendVec *pose_blend_table[];
void blend_base_lerp(BlendSrc *src, BlendDst *dst, BlendVec *table);
/* Starts entry `index` on pose pair `pose` (clamped to 0..5), unless the entry has its own handler. */
void pos_history_set_pose(s32 index, s32 pose, s32 scale, s32 arg) {
    PosHistoryEntry *entry;
    s16 *from;
    s16 *to;
    SVECTOR *offset;

    {
        register s32 clamped asm("$3") = MIN(index, 5);
        index = MIN(index, 5);
        if (index < 0) {
            clamped = 0;
        }
        index = clamped;
    }
    pose = MAX(MIN(pose, 5), 0);
    entry = &pos_history_table[index];
    if (entry->active != 0) {
        entry->unk_838 = arg;
        if (entry->mode == 0) {
            from = pose_from_table[pose];
            to = pose_to_table[pose];
            offset = scratch_alloc(8);
            offset->vx = -((from[0] - to[0]) * 20);
            offset->vy = -((from[2] - to[2]) * 20);
            offset->vz = -((from[1] - to[1]) * 20);
            blend_base_lerp((BlendSrc *)entry->obj, (BlendDst *)entry, (BlendVec *)from);
            blend_vec_lerp((BlendSrc *)entry->obj, (BlendDst *)entry, pose_blend_table[pose], offset, scale);
            scratch_top -= 8;
            obj_local_to_world((Object *)entry->obj, (s32 *)entry->world_pos);
            obj_local_to_world((Object *)entry->obj, (s32 *)&entry->cur);
        } else {
            ((void (*)(s32, PosHistoryEntry *, s32, s32))entry->mode)(entry->obj, entry, pose, scale);
        }
    }
}

s32 trace_hit_apply(Vec3 *from, void *hit, Vec3 *to, s32 flags, s32 type, s32 damage);
/* mode selects the setup call; its result goes to result, and on success cur is stored in
   slots[index]. */
void pos_history_step(PosHistoryEntry *rec) {
    s32 scratch[4];

    if (rec->mode == 0) {
        sweep_hit_test((Vec3 *)rec->world_pos, (Vec4 *)&rec->cur, (Vec4 *)scratch, 0xC0, 8, 0x10);
        rec->result = sweep_hit_test((Vec3 *)rec->world_pos, (Vec4 *)&rec->cur, (Vec4 *)&rec->cur, 0x18, 8, 0);
    } else {
        rec->result = trace_hit_apply((Vec3 *)rec->world_pos, &rec->cur, (Vec3 *)&rec->cur, 0x18, 8, 8);
    }
    if (rec->result != 0) {
        PosHistorySlot *slot = &rec->slots[rec->index];

        slot->pos = rec->cur;
    }
}

/* Same code as pos_history_push_all (s12). */
void pos_history_update_all(void) {
    PosHistoryEntry *entry = pos_history_table;
    s32 i;

    for (i = 0; i < 0x6; i++, entry++) {
        if (entry->active != 0) {
            pos_history_step(entry);
        }
    }
}

void pos_history_get_origin(u8 *base, s32 idx, Quad4 *out) {
    s32 i = *(s16 *)(base + 0x832) - idx;
    while (i < 0) {
        i += 0x40;
    }
    *out = *(Quad4 *)(base + (i << 5) + 0x28);
}

void pos_history_get_pos(u8 *base, s32 idx, Quad4 *out) {
    s32 i = *(s16 *)(base + 0x832) - idx;
    while (i < 0) {
        i += 0x40;
    }
    *out = *(Quad4 *)(base + (i << 5) + 0x38);
}


/* Clears a 3-word vector (x, y, z pointers into the same block) and rotates it by two angles; the
 * fourth argument is stored in the third word before the rotation. */
void vec3_set_from_angles(s32 *out, s32 angle2, s32 angle1, s32 w) {
    out[2] = w;
    out[0] = 0;
    out[1] = 0;
    rotate_xz_twice(angle2, angle1, out, &out[1], &out[2]);
}


void prim_world_fan_add(s32 count, MatrixRow *verts, u8 *tint);
/* Draws a pos-history entry's trail: a line of sparks from its origin to cur,
   a tip spark, an optional glow spark, then the history ribbon quads. */
void pos_history_draw_entry(PosHistoryEntry *entry) {
    s32 dx = entry->cur.w[0] - ((s32 *)entry->world_pos)[0];
    s32 dy = entry->cur.w[1] - ((s32 *)entry->world_pos)[1];
    s32 dz = entry->cur.w[2] - ((s32 *)entry->world_pos)[2];
    s32 len = SquareRoot0(length_sq(dx, dy, dz));
    s32 steps = len / 192;
    s32 frac = ((len % 192) << 12) / 192;
    s32 step[3];
    s32 yaw, pitch;
    s32 shade, colour;
    s32 life, blue, half;
    s16 size;
    Quad4 *q;
    u8 *info;
    s32 i;

    vector_to_angles(dx, dy, dz, &yaw, &pitch);
    vec3_set_from_angles(step, yaw, -pitch, 0xC0);
    dx = ((s32 *)entry->world_pos)[0];
    dy = ((s32 *)entry->world_pos)[1];
    dz = ((s32 *)entry->world_pos)[2];

    life = entry->unk_838 + entry->rnd - 0x800;
    life = MAX(MIN(life, 0x1FFF), 0);
    shade = life >> 5;

    blue = shade == 0 ? 1 : shade;
    colour = (blue << 16) | (shade << 8) | shade;
    size = pool_spawn_scaled(((s16 *)entry->pool_model_ids)[0], 0x2000, 0x2000, 0x1000);
    for (; steps > 0; steps--) {
        spark_add(dx, dy, dz, yaw, -pitch, 0, size, colour);
        dx += step[0];
        dy += step[1];
        dz += step[2];
    }
    size = pool_spawn_scaled(((s16 *)entry->pool_model_ids)[1], 0x2000, 0x2000, frac);
    spark_add(dx, dy, dz, yaw, -pitch, 0, size, colour);
    if (entry->result != 0) {
        dx += step[0] * frac / 0x1000;
        dy += step[1] * frac / 0x1000;
        dz += step[2] * frac / 0x1000;
        half = (s16)(u16)entry->rnd / 2 + 0xC00;
        size = pool_spawn_scaled(((s16 *)entry->pool_model_ids)[2], half, half, half);
        spark_add(dx, dy, dz, yaw, -pitch, entry->rnd, size, colour);
    }
    q = scratch_alloc(0x40);
    if (entry->count >= 2) {
        info = scratch_alloc(4);
        info[0] = 0;
        for (i = 0; i < entry->count - 2; i++) {
            info[1] = 0x20 - i;
            info[2] = (0x20 - i) * 4;
            pos_history_get_origin((u8 *)entry, i, q);
            pos_history_get_pos((u8 *)entry, i, q + 1);
            pos_history_get_pos((u8 *)entry, i + 1, q + 2);
            pos_history_get_origin((u8 *)entry, i + 1, q + 3);
            prim_world_fan_add(4, (MatrixRow *)q, info);
        }
        scratch_top -= 4;
    }
    scratch_top -= 0x40;
}

/* Same code as pos_history_push_all (s12). */
void pos_history_draw_all(void) {
    PosHistoryEntry *entry = pos_history_table;
    s32 i;

    for (i = 0; i < 0x6; i++, entry++) {
        if (entry->active != 0) {
            pos_history_draw_entry(entry);
        }
    }
}

/* Returns the index of the first of the 6 entries whose unk_834 is 0, or -1 if none. */
s32 pos_history_find_free(void) {
    PosHistoryEntry *entry = pos_history_table;
    s32 i;

    for (i = 0; i < 6; i++, entry++) {
        if (entry->active == 0) {
            return i;
        }
    }
    return -1;
}

s32 pos_history_add(Object *obj, s32 a1, s32 a2, s32 a3) {
    PosHistoryEntry *entry;
    s32 idx;

    idx = pos_history_find_free();
    if (idx < 0) {
        return -1;
    }
    entry = &pos_history_table[idx];
    entry->obj = (s32) obj;
    entry->active = 1;
    entry->mode = 0;
    pos_history_set_pose(idx, a1, a2, a3);
    entry->slots[0].unk_00 = *(Quad *) entry->world_pos;
    entry->slots[0].pos = *(Quad *) &entry->cur;
    /* three s16 table positions from the asset's first word, then two zeroed s16 */
    *(s16 *) &entry->pool_model_ids[0] =(s16) (model_slot_pchr(*(s32 *) obj->asset) + 0x230);
    *(s16 *) &entry->pool_model_ids[2] = (s16) (model_slot_pchr(*(s32 *) obj->asset) + 0x232);
    *(s16 *) &entry->pool_model_ids[4] = (s16) (model_slot_pchr(*(s32 *) obj->asset) + 0x238);
    *(s16 *) &entry->pool_model_ids[6] = 0;
    *(s16 *) &entry->pool_model_ids[8] = 0;
    entry->index = 0;
    return idx;
}

s32 pos_history_add_mode(Object *obj, s32 a1, s32 a2, s32 a3, s32 mode) {
    PosHistoryEntry *entry;
    s32 index;

    index = pos_history_find_free();
    if (index < 0) {
        return -1;
    }
    entry = &pos_history_table[index];
    entry->obj = (s32) obj;
    entry->active = 1;
    entry->mode = mode;
    pos_history_set_pose(index, a1, a2, a3);
    entry->slots[0].unk_00 = *(Quad *) entry->world_pos;
    entry->slots[0].pos = entry->cur;
    *(s16 *) &entry->pool_model_ids[0] = model_slot_pchr(((s32 *) obj->asset)[0]) + 0x230;
    *(s16 *) &entry->pool_model_ids[2] = model_slot_pchr(((s32 *) obj->asset)[0]) + 0x232;
    *(s16 *) &entry->pool_model_ids[4] = model_slot_pchr(((s32 *) obj->asset)[0]) + 0x238;
    *(s16 *) &entry->pool_model_ids[6] = 0;
    *(s16 *) &entry->pool_model_ids[8] = 0;
    entry->index = 0;
    return index;
}

extern char pos_history_buf[];
void pos_history_free(s32 idx) {
    if (idx < 6) {
        if (idx >= 0) {
            *(s16 *)(pos_history_buf + idx * 0x83C) = 0;
        }
    }
}

void pos_history_clear_all(void) {
    PosHistoryEntry *entry = pos_history_table;
    s32 i = 5;

    do {
        entry->active = 0;
        i--;
        entry++;
    } while (i >= 0);
}

void pos_history_reset(void) {
    pos_history_clear_all();
}

s32 pos_history_entry(u32 slot) {
    PosHistoryEntry *rec;

    if (slot >= 6) {
        return 0;
    }
    rec = &pos_history_table[slot];
    return (s32) rec & -(rec->active != 0);
}

void obj_vec_to_world_gte(Object *obj, s32 *vec);
void shot_spawn_relative(Object *obj, s16 *pos, u16 *rot, s32 *target) {
    s32 vec[3];
    s16 ang[3];
    s32 pitch;
    s32 yaw;
    s32 sum;

    vec[0] = -(pos[0] * 0x1800) / 4096;
    vec[1] = -(pos[2] * 0x1800) / 4096;
    vec[2] = -(pos[1] * 0x1800) / 4096;
    obj_vec_to_world_gte(obj, vec);
    pitch = obj->pitch;
    ang[0] = -pitch - rot[0];
    yaw = obj->yaw;
    sum = yaw + rot[1];
    ang[1] = sum;
    ang[2] = rot[2];
    shot_spawn_target(vec, ang, target, 1, 0x80001);
}

void shot_spawn_relative(Object *obj, s16 *pos, u16 *rot, s32 *target);
/* Zeroes a 3-word result block and calls shot_spawn_relative with it as the 4th
 * argument. The first three argument registers are not set here; they carry
 * whatever the caller left in a0-a2. */
void shot_spawn_relative_zeroed(void) {
    Object *unused_a0;
    u16 *unused_a2;
    s16 *unused_a1;
    s32 result[3];

    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    shot_spawn_relative(unused_a0, unused_a1, unused_a2, result);
}

/* Advances the entry's timer; once it reaches 0x31 the entry's unk_18 is cleared. */
void sound_slot_tick(SoundSlotEntry *entry) {
    SoundSlotTimer *timed = (SoundSlotTimer *)entry;

    timed->timer++;
    if (timed->timer >= 0x31) {
        timed->unk_18 = 0;
    }
}

void sound_slot_tick(SoundSlotEntry *entry);
extern SoundSlotEntry sound_slot_table[];
void sound_slots_tick_all(void) {
    SoundSlotEntry *entry = sound_slot_table;
    s32 i;

    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active != 0) {
            sound_slot_tick(entry);
        }
    }
}

/* Fires a hit at the player when the player is inside a radius that grows with the record's 0x14 word.
 * SoundSlotEntry lacks the s32 words at 0x04, 0x0C, 0x14 (the cast reads them); proposed fields below. */
void sound_slot_hit_player(SoundSlotEntry *entry) {
    s32 *rec = (s32 *)entry;
    s32 dist_sq;
    s32 scale;
    s32 radius_sq;
    s32 *player;

    dist_sq = player_dist_sq(rec + 1);
    scale = (rec[5] << 12) / 48;
    radius_sq = scale * 0x2D0 + (0x1000 - scale) * 0x3C;
    radius_sq = radius_sq / 0x1000;
    radius_sq = radius_sq * radius_sq;
    if (dist_sq < radius_sq) {
        player = player_position();
        hit_target_masked(0, 4, atan2(rec[3] - player[2], rec[1] - player[0]), 0x10);
    }
}

/* Same code as sound_slots_tick_all (s12). */
void sound_slots_hit_all(void) {
    SoundSlotEntry *entry = sound_slot_table;
    s32 i;

    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active != 0) {
            sound_slot_hit_player(entry);
        }
    }
}

/* Spawns the slot's spark: a pool model scaled 0x5000 with a weight fading from 0x1000 over 48 frames, a grey
 * spark whose level is twice the weight clamped to 0..0x1FFF over 32 (top byte at least 1), and queues the
 * position. */
void sound_slot_draw(SoundSlotEntry *entry) {
    s32 model = model_slot_pchr(*(s32 *)entry->owner->asset);
    s32 weight = 0x1000 - ((entry->timer << 12) / 48);
    s32 clamped;
    s32 colour; /* twice the weight, then the colour word */
    s32 hi;
    s32 level;

    model = pool_spawn_scaled(pchr_blend(model + 0x249, model + 0x248, weight, 0), 0x5000, 0x5000, 0x5000);
    colour = weight;
    colour *= 2; /* a separate statement: cc1 then keeps the copy's references and allocates colour first */
    clamped = MAX(MIN(colour, 0x1FFF), 0);
    level = clamped >> 5;
    hi = level;
    if (hi == 0) {
        hi = 1;
    }
    colour = (hi << 16) | (level << 8) | level;
    spark_add(entry->pos.x, entry->pos.y, entry->pos.z, 0, 0, 0, model, colour);
    req_queue_push_vec(entry->pos.x, entry->pos.y, entry->pos.z);
}

/* Same code as sound_slots_tick_all (s12). */
void sound_slots_draw_all(void) {
    SoundSlotEntry *entry = sound_slot_table;
    s32 i;

    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active != 0) {
            sound_slot_draw(entry);
        }
    }
}

/* Returns the first slot of sound_slot_table (64 entries of 0x1C bytes) whose 0x18 halfword is zero, or NULL if all are in use. */
SoundSlotEntry *sound_slot_alloc(void) {
    SoundSlotEntry *entry = sound_slot_table;
    s32 i;

    for (i = 0; i < 0x40; i++) {
        if (entry->active == 0) {
            return entry;
        }
        entry++;
    }
    return NULL;
}

void sound_slot_play_at(s32 id, SoundPos *pos) {
    SoundSlot *slot = (SoundSlot *) sound_slot_alloc();

    if (slot != NULL) {
        slot->active = 1;
        slot->id = id;
        slot->pos = *pos;
        slot->unk_14 = 0;
        sound_play_at_units(SND_SMALL_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, pos);
    }
}

void sound_slot_clear_all(void) {
    SoundSlotEntry *rec;
    s32 i;

    rec = sound_slot_table;
    i = 0x3F;
    do {
        rec->active = 0;
        i -= 1;
        rec++;
    } while (i >= 0);
}

void sound_slot_reset(void) {
    sound_slot_clear_all();
}

extern s32 burst_particle_template[5];
void burst_entry_update(RecS12Burst *entry) {
    s32 dx;
    s32 dz;
    u16 count;

    entry->lo = entry->pos;
    fly_move(entry->angle, entry->speed, &dx, &dz);
    entry->pos.v[0] += dz;
    entry->pos.v[2] += dx;
    entry->pos.v[1] += entry->vel_y;
    entry->vel_y += 0x1000;
    count = ++entry->frame_count;
    if (count & 1) {
        s32 pos[3];

        pos[0] = entry->pos.v[0] >> 12;
        pos[1] = entry->pos.v[1] >> 12;
        pos[2] = entry->pos.v[2] >> 12;
        particle_spawn_default((s32) pos, 0, 0,
                               model_slot_pchr(**(s32 **) (entry->owner + 0x1A0)),
                               (s32) burst_particle_template);
    }
}

void burst_entry_update(RecS12Burst *entry);
extern RecS12Burst burst_table[];
void burst_update_all(void) {
    RecS12Burst *entry = burst_table;
    s32 i;

    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active != 0) {
            burst_entry_update(entry);
        }
    }
}

void burst_check_hit(RecS12Burst *e, s32 *pos_out, s32 *lo_out, s32 *hit) {
    s32 x;
    s32 z;
    s32 result;

    pos_out[0] = e->pos.v[0] >> 12;
    pos_out[1] = e->pos.v[1] >> 12;
    pos_out[2] = e->pos.v[2] >> 12;
    lo_out[0] = e->lo.v[0] >> 12;
    lo_out[1] = e->lo.v[1] >> 12;
    lo_out[2] = e->lo.v[2] >> 12;

    result = sweep_hit_test((Vec3 *)pos_out, (Vec4 *)lo_out, (Vec4 *)hit, 0x20, 1, 0xE);
    switch (result) {
    case 1:
        x = hit[0] + 0x2EE00;
        if (x >= 0) {
            if (x >= 0x1500) {
                e->active = 0;
                break;
            }
        } else if (((s32)0xFFFD1200 - hit[0]) >= 0x1500) {
            e->active = 0;
            break;
        }
        z = hit[2];
        if (z < 0) {
            z = -z;
        }
        if (z < 0x1500) {
            sound_slot_play_at(e->owner, (SoundPos *)hit);
        }
        e->active = 0;
        break;
    case 2:
        spawn_effect(hit[0], hit[1], hit[2], 0x80040000);
        e->active = 0;
        break;
    }
}

void burst_check_hit(RecS12Burst *e, s32 *a, s32 *b, s32 *c);
/* Runs burst_check_hit for each in-use entry of burst_table, with three scratch vectors. */
void burst_check_all(void) {
    s32 *a = scratch_alloc(0x30);
    s32 *b = a + 4;
    s32 *c = a + 8;
    RecS12Burst *e = burst_table;
    s32 i;

    for (i = 0; i < 0x40; i++, e++) {
        if (e->active != 0) {
            burst_check_hit(e, a, b, c);
        }
    }
    scratch_top -= 0x30;
}

void req_queue_push_vec(s32 a, s32 b, s32 c);
void burst_draw_one(RecS12Burst *e) {
    s32 yaw, pitch;
    s32 pos[3];
    s16 value;
    s32 colour = 0x808080;

    vector_to_angles((e->pos.v[0] - e->lo.v[0]) >> 12, -((e->pos.v[1] - e->lo.v[1]) >> 12), (e->pos.v[2] - e->lo.v[2]) >> 12, &yaw, &pitch);
    value = pool_spawn_scaled((s16)(model_slot_pchr(*(s32 *)((Object *)e->owner)->asset) + 0x204), 0x1800, 0x1800, 0x1800);
    pos[0] = e->pos.v[0] >> 12;
    pos[1] = e->pos.v[1] >> 12;
    pos[2] = e->pos.v[2] >> 12;
    spark_add_head(&spark_list, pos[0], pos[1], pos[2], yaw, pitch, 0, value, colour);
    req_queue_push_vec(pos[0], pos[1], pos[2]);
}

/* Same code as burst_update_all (s12). */
void burst_draw_all(void) {
    RecS12Burst *entry = burst_table;
    s32 i;

    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active != 0) {
            burst_draw_one(entry);
        }
    }
}

RecS12Burst *burst_alloc(void) {
    RecS12Burst *entry;
    s32 i;

    entry = burst_table;
    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active == 0) {
            return entry;
        }
    }
    return NULL;
}

void burst_spawn(s32 owner, s32 *pos, s32 arg2, s32 arg3, s32 arg4) {
    RecS12Burst *r = burst_alloc();

    if (r != NULL) {
        r->active = 1;
        r->owner = owner;
        r->angle = arg2;
        r->vel_y = arg3;
        r->speed = arg4;
        r->pos.v[0] = pos[0] << 12;
        r->pos.v[1] = pos[1] << 12;
        r->pos.v[2] = pos[2] << 12;
        r->lo = r->pos;
        r->frame_count = 0;
        r->lo.v[0] += 0x1000;
        r->lo.v[1] += 0x1000;
        r->lo.v[2] += 0x1000;
        sound_play_at_units(SND_WHISTLE | SND_GROUP(2), 0x7F, 0x3C, pos);
    }
}

void burst_clear_all(void) {
    RecS12Burst *entry;
    s32 i;

    entry = burst_table;
    i = 0x3F;
    do {
        entry->active = 0;
        i -= 1;
        entry++;
    } while (i >= 0);
}

void burst_reset(void) {
    burst_clear_all();
}

void burst_check_entry(RecS12Burst *entry, s32 *pos, s32 radius, s32 radius_sq) {
    s32 dx;
    s32 dy;
    s32 dz;

    dx = (entry->pos.v[0] >> 12) - pos[0];
    dy = (entry->pos.v[1] >> 12) - pos[1];
    dz = (entry->pos.v[2] >> 12) - pos[2];
    if (ABS(dx) <= radius && ABS(dy) <= radius && ABS(dz) <= radius) {
        if (length_sq(dx, dy, dz) < radius_sq) {
            spawn_effect(entry->pos.v[0] >> 12, entry->pos.v[1] >> 12, entry->pos.v[2] >> 12, 0x80040000);
            entry->active = 0;
        }
    }
}

void burst_check_entry(RecS12Burst *entry, s32 *pos, s32 radius, s32 radius_sq);
void burst_check_sphere(ProximityQuery *q) {
    s32 *pos;
    RecS12Burst *entry = burst_table;
    s32 radius;
    s32 radius_sq;
    s32 i;

    pos = scratch_alloc(0x10);
    pos[0] = q->x;
    pos[1] = q->y;
    pos[2] = q->z;
    radius = q->range >> 12;
    radius_sq = radius * radius;
    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active != 0) {
            burst_check_entry(entry, pos, radius, radius_sq);
        }
    }
    scratch_top -= 0x10;
}

extern s32 boss_state;

void keyframe_table_set_flag(s32 arg0) {
    boss_state = arg0;
}

extern s32 boss_state;

s32 boss_state_get(void) {
    return boss_state;
}


void mode_reset(void) {
    keyframe_table_set_flag(0);
}


extern s32 scene_pos;
/* Same code as get_key_table (s01). */
s32 *scene_get_pos(void) {
    return &scene_pos;
}

void scene_set_pos(Vec3 *pos) {
    *(PosRecord16 *)&scene_pos = *(PosRecord16 *)pos;
}

extern s32 scene_rot_data[2];
/* Same code as get_key_table (s01). */
s32 *scene_get_rot(void) {
    return scene_rot_data;
}

/* Copies 8 bytes from src to scene_rot_data (both unaligned). */
void scene_set_rot(void *src) {
    *(Bytes8 *)scene_rot_data = *(Bytes8 *)src;
}

void cam_track_start(Object *obj, s32 flag);
void cam_track_start_both(Object *obj) {
    cam_track_start(obj, 0);
    cam_track_start(obj, 1);
}

void script_op_nop(void) {
}

extern s16 shot_offset_table[24];
extern u8 shot_rot_default[8];
void shot_fire_pair(Object *obj) {
    Bytes8 rot_raw;
    s32 target[3];
    u16 counter;
    s32 idx;
    s16 next;
    s16 *table;
    s32 rnd;

    counter = obj->vars.supermech_m12_boss.shot_counter;
    idx = (s16)counter;
    next = counter + 1;
    obj->vars.supermech_m12_boss.shot_counter = next;
    obj->vars.supermech_m12_boss.shot_counter = next % 4096;
    idx %= 3;
    table = shot_offset_table + idx * 4;

    rot_raw = *(Bytes8 *)shot_rot_default;

    rnd = rand_a_next();
    if (rnd < 0) {
        rnd += 0xF;
    }
    ((u16 *)rot_raw.b)[1] += rnd >> 4;
    rnd = rand_a_next();
    if (rnd < 0) {
        rnd += 0xF;
    }
    ((u16 *)rot_raw.b)[0] += rnd >> 4;
    target[0] = get_flow_move()[0] >> 12;
    target[1] = get_flow_move()[1] >> 12;
    target[2] = get_flow_move()[2] >> 12;
    shot_spawn_relative(obj, table, (u16 *)rot_raw.b, target);
    shot_spawn_relative(obj, table + 0xC, (u16 *)rot_raw.b, target);
}

/* Reads the s16 at the cursor, advances the cursor by 2 bytes and
 * passes (value != 0) as the mode. */
void script_op_mode(CursorObj20 *obj) {
    u8 *p;

    p = obj->cursor;
    obj->cursor = p + 2;
    if (*(s16 *)p == 0) {
        meter_set_mode(0);
    } else {
        meter_set_mode(1);
    }
}

extern s32 obj_loop_sound_handle;

void obj_start_loop_sound(Object *obj) {
    s32 temp_v0;

    if (obj_loop_sound_handle == 0) {
        temp_v0 = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x7F, 0, 0);
        obj_loop_sound_handle = temp_v0;
        if (temp_v0 != 0) {
            sound_attach(temp_v0, &obj->x, NULL);
        }
    }
}

extern s32 obj_loop_sound_handle;

void obj_stop_loop_sound(void) {
    if (obj_loop_sound_handle != 0) {
        sound_stop(obj_loop_sound_handle);
        obj_loop_sound_handle = 0;
    }
}

CamTrackState *get_cam_track_0(void);
s32 cam_track0_sound_update(s32 unused, s32 handle) {
    CamTrackState *track;
    Vec3 *pos;
    PosHistoryEntry *entry;

    track = get_cam_track_0();
    pos = scratch_alloc(0x10);
    pos->x = 0;
    pos->y = 0;
    pos->z = 0;
    sound_set_pos(handle, pos);
    scratch_top -= 0x10;
    if (track->enabled == 0) {
        sound_set_volume(handle, 0);
        return 0;
    }
    entry = (PosHistoryEntry *)pos_history_entry(track->pos_history_index);
    if (entry == NULL || entry->active == 0) {
        sound_set_volume(handle, 0);
        return 0;
    }
    pos = scratch_alloc(0x10);
    sound_set_volume(handle, sound_volume_of(0xB171B172, 0x1000));
    sound_closest_point((Vec3 *)entry->world_pos, (Vec3 *)&entry->cur, pos);
    pos->x <<= 12;
    pos->y <<= 12;
    pos->z <<= 12;
    sound_set_pos(handle, pos);
    scratch_top -= 0x10;
    return 0;
}

CamTrackState *get_cam_track_1(void);
/* Same code as cam_track0_sound_update (s12). */
s32 cam_track1_sound_update(s32 unused, s32 handle) {
    CamTrackState *track;
    Vec3 *pos;
    PosHistoryEntry *entry;

    track = get_cam_track_1();
    pos = scratch_alloc(0x10);
    pos->x = 0;
    pos->y = 0;
    pos->z = 0;
    sound_set_pos(handle, pos);
    scratch_top -= 0x10;
    if (track->enabled == 0) {
        sound_set_volume(handle, 0);
        return 0;
    }
    entry = (PosHistoryEntry *)pos_history_entry(track->pos_history_index);
    if (entry == NULL || entry->active == 0) {
        sound_set_volume(handle, 0);
        return 0;
    }
    pos = scratch_alloc(0x10);
    sound_set_volume(handle, sound_volume_of(0xB171B172, 0x1000));
    sound_closest_point((Vec3 *)entry->world_pos, (Vec3 *)&entry->cur, pos);
    pos->x <<= 12;
    pos->y <<= 12;
    pos->z <<= 12;
    sound_set_pos(handle, pos);
    scratch_top -= 0x10;
    return 0;
}

extern s32 owner_sound_handles[2];
void sound_start_on_owner(s32 owner) {
    if (owner_sound_handles[0] == 0) {
        owner_sound_handles[0] = sound_start(0xB171B172, 0x32, 0, 0);
        if (owner_sound_handles[0] != 0) {
            sound_attach(owner_sound_handles[0], (void *)(owner + 0x1F0), NULL);
        }
    }
}

extern s32 owner_sound_handles[2];
void sound_stop_pair(void) {
    s32 *entry;
    s32 handle;
    s32 i;

    i = 0;
    entry = owner_sound_handles;
    do {
        handle = *entry;
        if (handle != 0) {
            sound_stop(handle);
            *entry = 0;
        }
        i += 1;
        entry += 1;
    } while (i < 2);
}

void supermech_m12_boss_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

static inline TurnVars *rec_of(Object *obj) {
    return (TurnVars *)&obj->vars;
}
/* Orbits a point: advances the phase and the turn angle, follows the camera target's yaw (limited to +-0x200000
 * from it), and takes the resulting position and rotation as the object's. */
void orbit_update(Object *obj) {
    Vec3 *pos;
    SVECTOR *rot;
    Vec3 *target;
    s32 t;
    s32 d;
    s32 big;
    Mover *mv = &rec_of(obj)->mover;
    s32 phase = rec_of(obj)->phase + 8;
    s32 sin;

    sin = (s16) * (u16 *)&rcossin_tbl[phase & 0xFFF];
    rec_of(obj)->phase = phase;
    rec_of(obj)->turn_c += 4;
    rec_of(obj)->turn_a = sin / 12;
    collider_begin((Collider *)obj->unk_A4);
    pos = scratch_alloc(0x10);
    rot = scratch_alloc(8);
    target = scratch_alloc(0xC);
    mover_to_vec3((Vec3 *)get_mover(), target);
    d = mv->yaw - target->y;
    d &= 0xFFFFFF;
    if (d > 0x7FFFFF) {
        d += 0xFF000000;
    }
    big = d > 0x200000;
    t = d;
    if (big) {
        t = 0x200000;
    }
    if (t >= -0x200000) {
        if (big) {
            d = 0x200000;
        }
    } else {
        d = -0x200000;
    }
    mv->yaw = target->y + d;
    mv->yaw += rec_of(obj)->yaw_offset;
    mv->pitch += rec_of(obj)->pitch_offset;
    mover_calc_pos(mv, (s32 *)pos);
    mover_set_rot(mv, (PlayerObj *)rot);
    rot_compose_angles(rec_of(obj)->turn_a, rec_of(obj)->turn_b, (s16)rec_of(obj)->turn_c, rot);
    obj->x = pos->x;
    obj->y = pos->y;
    obj->z = pos->z;
    obj->yaw = -rot->vy;
    obj->pitch = rot->vx;
    obj->roll = -rot->vz;
    scratch_top -= 0x24;
}

extern s16 D_801238B0[];
void obj_take_hit(Object *obj, s16 *arg1) {
    s32 amount;
    s32 scaled;
    s32 flags;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    amount = obj_hit_damage(obj->index);
    if (obj->hit_cooldown != 0) {
        obj->hit_cooldown = obj->hit_cooldown + 0xFF;
    }
    if (amount > 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        scaled = amount * obj_hit_mask_avg(obj_hit_type(obj->index) & 0xFF, D_801238B0);
        amount = scaled >> 12;
        if (scaled < 0) {
            amount = (scaled + 0xFFF) >> 12;
        }
        obj->health -= amount;
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
    if (obj->health <= 0) {
        arg1[9] = 1; /* arg1 + 0x12: set when the object dies */
        add_score(obj->score);
        add_kill_count(1);
        fx_tracks_stop_all();
        ((void (*)(Object *, s32))sound_stop_pair)(obj, 0); /* defined as void(void) in main.c; args unused */
        obj_set_hit_reaction(obj, 0);
        obj_actors_clear_index();
        set_mission_active(0);
        mission_timer_active_set(0);
        set_d_801202C8(0);
        return;
    }
    flags = obj->flags;
    if (((u32)flags >> 5) & 1) {
        obj_hit_reaction(obj, 0);
    }
}

/* Runs the object's callback (0x170) if it has one; a callback that returns 0 is cleared.
 * The unused array keeps the 0x30-byte frame of the original (its locals are not recoverable). */
void obj_run_callback(Object *obj) {
    s32 (*callback)(void);
    s32 unused[6];

    callback = (s32 (*)(void))obj->callback;
    if (callback != NULL && callback() == 0) {
        obj->callback = 0;
    }
}

void enemy_hit_handler(Object *obj, ObjHandler *handler) {
    s32 hit;
    if (!(get_stage_flags() & 8) && (mission_timer_get() <= 0)) {
        set_player_status(get_player_status() | 0x40);
    }
    hit = handler->state;
    if (hit == 0) {
        obj_take_hit(obj, (s16 *)handler);
        meter_set(obj->health, obj->vars.supermech_m12_boss.max_health);
        hit = handler->state;
    }
    __asm__("");
    if (hit != 0) {
        ((void (*)(Object *, s32))obj_stop_loop_sound)(obj, 0);
        ((void (*)(Object *, s32))sound_stop_pair)(obj, 0);
        ((void (*)(Object *, ObjHandler *))obj_run_callback)(obj, handler);
    }
    if (obj->vars.enemy.sound_channel[1] == 0) {
        obj_free(obj);
    }
}

/* Emits a spark from an object whose sound channel 1 is playing: its position, its
 * angles (pitch negated) and a height value, with a colour when it is hit or dead.
 * The object pointer is pinned to $s1 (the original keeps it there). */
void supermech_m12_boss_draw(Object *self) {
    register Object *obj asm("$17") = self;
    s32 pos[3];
    SVECTOR rot;
    s32 colour;
    s32 value;
    s32 pitch;
    s32 unused[2]; /* frame padding: the original's frame is 0x40 bytes */

    if (obj->vars.enemy.sound_channel[1] == 0) {
        return;
    }
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = (s16)obj->pitch;
    rot.vx = -pitch;
    rot.vy = (u16)obj->yaw;
    rot.vz = (u16)obj->roll;

    colour = 0;
    if (obj->hit > 0 || obj->health <= 0) {
        colour = 0x60C0FF;
    }
    if (test_bit(obj->flags, 6)) {
        value = obj->type.unk_0E;
        value += model_slot_pchr(*(s32 *)obj->asset);
    } else {
        value = obj_keyframe_value(obj, 0);
    }

    spark_add(pos[0], pos[1], pos[2], rot.vy, rot.vx, rot.vz, value, colour);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

s32 sound_obj_spawn(Object *obj, s32 slot);
s32 sound_obj_init(Object *obj) {
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    return sound_obj_spawn(obj, model_slot_pchr(((s32 *) obj->asset)[0]) + 0x1F0) != 1;
}

extern ScriptCallEntry D_8012380C[9];
extern StateEntry D_801238A8[1];
extern s16 *D_80123884[5];
extern s16 *D_801238A4;
extern s16 *supermech_m12_script[];
extern s32 D_8012B9A8;
void orbit_update(Object *obj);
void enemy_hit_handler(Object *obj, ObjHandler *handler);
void supermech_m12_boss_draw(Object *self);
void obj_set_extents_from_part(Object *obj, s32 part, s32 part_arg);
/* Spawns an enemy at pos (x, y, z, shifted to 1/4096 units) with rot (yaw, pitch, roll) and returns it,
 * or NULL if boss_state_get() is 2 or obj_new() fails. The empty do-whiles are scheduling barriers that keep
 * the stores in the original order. */
s32 supermech_m12_boss_spawn(s32 *pos, s32 *rot) {
    u16 *rot16 = (u16 *) rot;
    Object *obj;
    s32 *asset;
    s16 **script_src;
    StateEntry *addr_198;
    s16 *sound_ptr;

    if (boss_state_get() != 2) {
        obj = obj_new();
        if (obj != NULL) {
            list_insert_after((Node *) get_obj_list_actors(), &obj->node);
            obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) supermech_m12_boss_phase0;
            obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) orbit_update;
            obj->handlers[2].fn = enemy_hit_handler;
            obj->handlers[3].fn = supermech_m12_boss_draw;
            obj->asset = supermech_model_id;
            obj->hit_cooldown_max = 0x30;
            obj->call_table = D_8012380C;
            addr_198 = D_801238A8;
            do { } while (0);
            obj->handlers[0].unk_11 = 0;
            obj->handlers[0].state = 0;
            obj->handlers[1].unk_11 = 0;
            obj->handlers[1].state = 0;
            obj->handlers[2].unk_11 = 0;
            obj->handlers[2].state = 0;
            obj->handlers[3].unk_11 = 0;
            obj->handlers[3].state = 0;
            do { } while (0);
            obj->unk_1C6 = 0;
            obj->state_table = addr_198;
            do { } while (0);
            sound_ptr = D_801238A4;
            do { } while (0);
            obj->script.data = D_80123884;
            obj->script.unk_0A = 0;
            obj->callback = (s32) &sound_obj_init;
            obj->script.pc = sound_ptr;
            script_src = supermech_m12_script;
            script_start((Script *) obj, *script_src, (s32) script_src);
            obj_init_common(obj, 0x37);
            obj->health = 0x2328;
            obj->score = 0x7530;
            obj->damage = 0x20;
            obj->unk_17B = 0;
            obj->x = pos[0] << 12;
            obj->y = pos[1] << 12;
            obj->z = pos[2] << 12;
            obj->yaw = rot16[1];
            obj->pitch = rot16[0];
            obj->roll = rot16[2];
            asset = obj->asset;
            obj_set_extents_from_part(obj, asset[1] + 0x1F0, 0x1800);
            obj_set_hit_reaction(obj, 1);
            obj->vars.enemy.sound_channel[0] = 0;
            obj->vars.enemy.sound_channel[1] = 1;
            obj->vars.supermech_m12_boss.unused_25A = 0;
            obj->vars.supermech_m12_boss.unused_25C = 0;
            obj->vars.supermech_m12_boss.unused_25E = 0;
            ((s16 *) obj->vars.enemy.unk_260)[0] = 0;
            ((s16 *) obj->vars.enemy.unk_260)[1] = 0;
            ((s16 *) obj->vars.enemy.unk_260)[2] = 0;
            obj->vars.supermech_m12_boss.unused_266 = 0;
            obj->vars.supermech_m12_boss.max_health = (u16) obj->health;
            obj_hit_set_unk08(obj->index, -1);
            obj_hit_set_unk06(obj->index, 3);
            meter_set(obj->health, obj->vars.supermech_m12_boss.max_health);
            meter_set_mode(0);
            mover_to_vec3((Vec3 *) get_mover(), (Vec3 *) &obj->vars);
            obj_loop_sound_handle = 0;
            owner_sound_handles[0] = 0;
            D_8012B9A8 = 0;
            obj_hit_flag_set(obj->index, 0x80);
            return (s32) obj;
        }
    }
    return 0;
}

void fx_track_update(FxTrack *t) {
    s32 angle;
    s32 i;
    u16 idx;

    idx = t->phase + 0x10;
    angle = cos_table[idx & 0xFFF].value;
    t->unk_12 += 0x20;
    t->phase = idx;
    if (angle < 0) {
        angle += 7;
    }
    t->unk_10 = angle >> 3;
    t->unk_0E = 0x155;
    if (t->active != 0) {
        t->level = t->level + t->rate;
        if ((s16) t->level >= 0x1001) {
            t->level = 0x1000;
        }
        if ((s16) t->level < 0) {
            t->active = 0;
            for (i = 0; i < 3; i++) {
                pos_history_free(t->handle);
            }
        } else {
            pos_history_set_pose(t->handle, t->unk_18, (s16) t->level, ((s16) t->level / 2) + 0x800);
        }
    }
}

extern CamTrackState cam_track_0_state;
extern CamTrackState cam_track_1_state;
void cam_track_update_all(void) {
    fx_track_update((FxTrack *) &cam_track_0_state);
    fx_track_update((FxTrack *) &cam_track_1_state);
}

extern FxOffset cam_track_offs[2];
extern CamTrackState cam_track_0_state;
extern CamTrackState cam_track_1_state;
void cam_track_points(Object *obj, s32 *out, s32 flag, s32 height) {
    FxOffset *offs;
    CamTrackState *cam;

    if (flag == 0) {
        offs = &cam_track_offs[0];
        cam = &cam_track_0_state;
    } else {
        offs = &cam_track_offs[1];
        cam = &cam_track_1_state;
    }
    if (cam->enabled != 0) {
        out[2] = offs->x;
        out[3] = offs->z;
        out[4] = offs->y;
        out[6] = 0;
        out[7] = 0;
        out[8] = height / 2;
        if (flag == 0) {
            rotate_xz_twice(-cam->angle2, -cam->angle1, &out[6], &out[7], &out[8]);
        } else {
            rotate_xz_twice(cam->angle2, cam->angle1, &out[6], &out[7], &out[8]);
        }
        out[6] += out[2];
        out[7] += out[3];
        out[8] += out[4];
        obj_vec_to_world_gte(obj, &out[2]);
        obj_vec_to_world_gte(obj, &out[6]);
    }
}

void cam_track_start(Object *obj, s32 flag) {
    CamTrackState *state;
    s32 uninit;
    s32 mode;

    if (flag == 0) {
        state = &cam_track_0_state;
        mode = 0;
    } else {
        state = &cam_track_1_state;
        mode = 1;
    }
    state->unk_0A = 0x100;
    state->enabled = 1;
    state->unk_08 = 0;
    state->unk_04 = uninit;
    state->mode = mode;
    state->unk_12 = 0;
    state->pos_history_index = pos_history_add_mode(obj, mode, 0x80, state->unk_08, (s32)cam_track_points);
}

extern CamTrackState cam_track_0_state;
extern CamTrackState cam_track_1_state;
/* Sets unk_0A of one of two states to -0x100; flag 0 picks cam_track_0_state, otherwise cam_track_1_state. */
void cam_track_release(s32 flag) {
    CamTrackState *state = &cam_track_1_state;

    if (flag == 0) {
        state = &cam_track_0_state;
    }
    state->unk_0A = -0x100;
}

extern s16 fx_track_a_flag;
extern s16 fx_track_a_id;
extern s16 fx_track_b_flag;
extern s16 fx_track_b_id;
void fx_tracks_stop_all(void) {
    s16 *flagA = &fx_track_a_flag;

    if (*flagA == 1) {
        pos_history_free(fx_track_a_id);
    }
    {
        s16 *flagB = &fx_track_b_flag;

        if (*flagB == 1) {
            pos_history_free(fx_track_b_id);
        }
        *flagA = 0;
        *flagB = 0;
    }
    pos_history_reset();
}

extern s16 fx_track_a_flag;
extern s16 fx_track_b_flag;

void fx_track_flags_reset(void) {
    fx_track_a_flag = 0;
    fx_track_b_flag = 0;
}

/* Same code as get_key_table (s01). */
CamTrackState *get_cam_track_0(void) {
    return &cam_track_0_state;
}

/* Same code as get_key_table (s01). */
CamTrackState *get_cam_track_1(void) {
    return &cam_track_1_state;
}
