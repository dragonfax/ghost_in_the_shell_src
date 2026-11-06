/* projectiles: one of s08's own original source files (scripts/objmap.py); part of src/s08/main.c's unit, included there. */

void burst_hit_player_check(s32 *obj) {
    s32 x = obj[0];
    s32 y = obj[1];
    s32 z = obj[2];
    s32 radius = obj[6] >> 12;
    s32 dx, dy, dz, dist_sq;
    s32 *p;

    p = player_position();
    dx = p[0] - x;
    p = player_position();
    dy = p[1] - y;
    p = player_position();
    dz = p[2] - z;
    dist_sq = radius * radius;

    if (radius < ABS(dx)) {
        return;
    }
    if (radius < ABS(dy)) {
        return;
    }
    if (radius < ABS(dz)) {
        return;
    }
    if (length_sq(dx, dy, dz) < dist_sq && world_flag_get() == 0) {
        hit_target_masked(0, 4, (s16)atan2(dz, dx), 0x12);
    }
}

extern RecTemplate hit_burst_templates[];
extern FxRecordParams hit_burst_params;
void burst_hit_player_check();
void hit_burst_spawn(s32 *pos) {
    fx_spawn_template(pos, &hit_burst_templates[0], NULL);
    fx_spawn_template(pos, &hit_burst_templates[1], burst_hit_player_check);
    fx_spawn_template(pos, &hit_burst_templates[2], NULL);
    fx_rec34_spawn_cb(pos, &hit_burst_params, 0);
}

s32 obj_check_move(Object *obj, s32 *pos, s32 *next, s32 *hit, s32 a, s32 b);
void hit_burst_spawn(s32 *pos);
/* Moves the object by its velocity; frees it when the move hits something. */
void projectile_update(Object *obj) {
    s32 *v = scratch_alloc(0x30);
    s32 *next = &v[4];
    s32 *hit = &v[8];
    s32 r;

    v[0] = obj->x;
    v[1] = obj->y;
    v[2] = obj->z;
    if (world_flag_get() == 1) {
        v[0] >>= 12;
        v[1] >>= 12;
        v[2] >>= 12;
        spawn_effect(v[0], v[1], v[2], 0);
        obj_snd2_stop(obj);
        obj_free(obj);
    } else {
        v[4] = v[0] + obj->vx;
        v[5] = v[1] + obj->vy;
        v[6] = v[2] + obj->vz;
        obj->x = v[4];
        obj->y = v[5];
        obj->z = v[6];
        v[0] >>= 12;
        v[1] >>= 12;
        v[2] >>= 12;
        v[4] >>= 12;
        v[5] >>= 12;
        v[6] >>= 12;
        r = obj_check_move(obj, v, next, hit, 6, 1);
        if (r != 1) {
            if (r > 0) {
                if (r < 5) {
                    hit_burst_spawn(next);
                    obj_snd2_stop(obj);
                    sound_play_at_units(SND_S08_PROJECTILE_IMPACT | SND_GROUP(1), 0x7F, 0x3C, next);
                    obj_free(obj);
                }
            }
        } else {
            obj_snd2_stop(obj);
            obj_free(obj);
        }
    }
    scratch_top -= 0x30;
}

/* Spawns three spark records for the object: one at its position with its angles (value 0x85 + get_world_offset),
 * then two at the position offset by the object's vars fields (value 0x73 + get_model_slot_base); the last one
 * uses colour 0x191919 and y -0x840. The scratch vectors are $gp allocations, given back at the end. */
void obj_sparks_draw(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);
    s32 value;
    s32 value2;
    s32 pitch;

    value = get_world_offset();
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    value += 0x85;
    rot[2] = obj->roll;
    spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], 0, value, 0);

    value2 = get_model_slot_base();
    pos[0] += obj->vars.enemy.mode;
    pos[1] += obj->vars.snd.sound;
    value2 += 0x73;
    pos[2] += obj->vars.projectile_fire.unk_250;
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, value2, 0);
    spark_add(pos[0], -0x840, pos[2], 0, 0, 0, value2, 0x191919);

    scratch_top -= 0x18;
}

void obj_snd2_loop_start(Object *obj);
s32 projectile_fire_spawn(Vec3 *pos, SVECTOR *rot, volatile s32 *mat) {
    Object *obj = obj_new();
    s32 *v;
    s32 a, b, c;
    s32 *out, *out2;
    
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj->handlers[1].fn = (ObjHandlerFn) projectile_update;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->callback = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = (ObjHandlerFn) obj_sparks_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = pos->x;
    obj->y = pos->y;
    obj->z = pos->z;
    obj->pitch = (u16)rot->vx;
    obj->yaw = (u16)rot->vy;
    v = scratch_alloc(0x10);
    obj->roll = (u16)rot->vz;
    a = mat[0];
    b = mat[1];
    c = mat[2];
    gte_set_ctrl(R11R12, a);
    gte_set_ctrl(R13R21, b);
    gte_set_ctrl(R22R23, c);
    a = mat[3];
    b = mat[4];
    gte_set_ctrl(R31R32, a);
    gte_set_ctrl(R33, b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    v[2] = 0x20;
    out = &obj->vx;
    v[0] = 0;
    v[1] = 0;
    gte_load(IR1, v, 0);
    gte_load(IR2, v, 4);
    gte_load(IR3, v, 8);
    gte_rtirtr_sf0();
    gte_store(MAC1, out, 0);
    gte_store(MAC2, out, 4);
    gte_store(MAC3, out, 8);
    v[2] = -0x2D;
    out2 = &obj->vars.projectile_fire.unk_248;
    v[0] = 0;
    v[1] = 0;
    gte_load(IR1, v, 0);
    gte_load(IR2, v, 4);
    gte_load(IR3, v, 8);
    gte_rtirtr();
    gte_store(MAC1, out2, 0);
    gte_store(MAC2, out2, 4);
    gte_store(MAC3, out2, 8);
    scratch_top -= 0x10;
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    obj->vars.projectile_fire.unused_268 = 0;
    obj_snd2_loop_start(obj);
    pos->x >>= 12;
    pos->y >>= 12;
    pos->z >>= 12;
    sound_play_at_units(SND_PROJECTILE_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    return 1;
}

void obj_bone_pos(Object *obj, s32 idx, Vec3 *out);
s32 projectile_fire_spawn(Vec3 *pos, SVECTOR *rot, volatile s32 *mat);
/* Builds a world position from a local offset and the object's position, then hands it on. */
void muzzle_flash_spawn(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);

    pos->x = 0;
    pos->y = 0;
    pos->z = 0xAF;
    obj_bone_pos(obj, 0, pos);
    pos->x = obj->x + (pos->x << 12);
    pos->y = obj->y + (pos->y << 12);
    pos->z = obj->z + (pos->z << 12);
    rot[0] = obj->pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    projectile_fire_spawn(pos, (SVECTOR *)rot, world_matrix_get());
    pos->x >>= 12;
    pos->y >>= 12;
    pos->z >>= 12;
    effect_spawn_at(pos, get_world_offset() + 0x86, 3, 0x15);
    scratch_top -= 0x18;
}

/* Phase 0 counts 0x1F ticks and fires muzzle_flash_spawn every 30; phase 1 counts 0x29 ticks; phase 2 clears flag. */
void muzzle_burst_update(Object *obj) {
    PhaseTimer *t = *(PhaseTimer **)&obj->vars.snd;

    switch (t->phase) {
    case 0:
        if ((s16)t->tick % 30 == 0) {
            muzzle_flash_spawn(obj);
        }
        t->tick++;
        if ((s16)t->tick >= 0x1F) {
            t->tick = 0;
            t->phase++;
        }
        break;
    case 1:
        t->tick++;
        if ((s16)t->tick >= 0x29) {
            t->phase++;
        }
        break;
    case 2:
        t->flag = 0;
        break;
    }
}

extern s32 stage_sound_handle;

void stage_sound_reset(void) {
    stage_sound_handle = 0;
}

/* Moves the object by its speed, tracing the move for a hit; once the object has no shots left it bursts. */
void quick_fuchikoma_rocket_update(Object *obj) {
    s32 *pos;
    s32 *to;
    s32 hit = 0;
    s16 target;
    s32 x, y, z;
    s32 handle;
    s32 off;

    if (obj_hit_damage(obj->index) > 0) {
        obj_free(obj);
        return;
    }
    pos = scratch_alloc(0x30);
    x = obj->x;
    y = obj->y;
    z = obj->z;
    pos[0] = x >> 12;
    pos[1] = y >> 12;
    pos[2] = z >> 12;
    x += obj->vx;
    y += obj->vy;
    z += obj->vz;
    pos[4] = x >> 12;
    pos[5] = y >> 12;
    pos[6] = z >> 12;
    obj->x = x;
    obj->y = y;
    obj->z = z;
    set_collide_mode(1);
    to = pos + 8;
    if (trace_objects(pos, pos + 4, 8, to, &target)) {
        hit = 1;
        hit_target_masked(target, 1, atan2(to[2] - pos[2], to[0] - pos[0]), obj->damage);
    }
    set_collide_mode(0);
    if (hit != 0 || obj->vars.enemy.shot_timer <= 0) {
        if (hit == 0) {
            to[0] = obj->vars.quick_fuchikoma_rocket.target_x;
            to[1] = obj->vars.quick_fuchikoma_rocket.target_y;
            to[2] = obj->vars.quick_fuchikoma_rocket.target_z;
        }
        sound_play_at_units(SND_PROJECTILE_IMPACT | SND_GROUP(2), 0x60, 0x3C, to);
        handle = get_model_slot_base();
        off = ((rand_a_next() * 3 / 0x1000) << 2) + 0x30;
        effect_spawn_at((Vec3 *)to, handle + off, 4, 0x3C);
        obj_free(obj);
        scratch_top -= 0x30;
    } else {
        obj->vars.enemy.shot_timer--;
        scratch_top -= 0x30;
    }
}

/* spark_add_head with the count read as a struct member (the load stays below the scratch stores). */
static inline void spark_add_head_m(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
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

void quick_fuchikoma_rocket_draw(Object *obj, ObjHandler *handler) {
    s32 *dir;
    s32 base;
    s32 x, y, z;
    s32 px, py, pz;
    s32 tail_x, tail_y, tail_z;
    s32 level, red, rem, colour;
    s32 scale, model;
    s32 shadow_colour, rocket_model, tail_model;
    SparkList *list;

    base = get_model_slot_base();
    dir = scratch_alloc(0x10);
    shadow_colour = 0x111111;
    dir[0] = obj->vars.quick_fuchikoma_rocket.dir_x;
    rocket_model = base + 0x15;
    dir[1] = obj->vars.quick_fuchikoma_rocket.dir_y;
    list = &spark_list;
    dir[2] = obj->vars.quick_fuchikoma_rocket.dir_z;
    x = obj->x;
    y = obj->y;
    z = obj->z;
    x >>= 12;
    y >>= 12;
    z >>= 12;
    spark_add_head_m(list, x, y, z, obj->yaw + 0x800, -obj->pitch, 0, rocket_model, 0);
    spark_add_head_m(list, x, -0x840, z, obj->yaw + 0x800, -obj->pitch, 0, rocket_model, shadow_colour);
    scale = 0x266;
    tail_model = base + 0x16;
    gte_load(IR1, dir, 0);
    gte_load(IR2, dir, 4);
    gte_load(IR3, dir, 8);
    gte_set(IR0, scale);
    gte_set(MAC1, x);
    gte_set(MAC2, y);
    gte_set(MAC3, z);
    gte_gpl12();
    gte_get(IR1, tail_x);
    gte_get(IR2, tail_y);
    gte_get(IR3, tail_z);
    spark_add_head_m(list, tail_x, tail_y, tail_z, 0, 0, 0, tail_model, 0);
    spark_add_head_m(list, tail_x, -0x840, tail_z, 0, 0, 0, tail_model, shadow_colour);

    if (obj->vars.quick_fuchikoma_rocket.muzzle_flash_pending == 1) {
        x = obj->vars.quick_fuchikoma_rocket.spawn_x;
        y = obj->vars.quick_fuchikoma_rocket.spawn_y;
        z = obj->vars.quick_fuchikoma_rocket.spawn_z;
        level = rand_b_next();
        rem = level % 0x800;
        level = 0x1000 - rem;
        level >>= 5;
        red = level;
        if (red == 0) {
            red = 1;
        }
        colour = (red << 16) | (level << 8) | level;
        spark_add(x, y, z, 0, 0, 0, base + 1, colour);
        scale = 0xB33;
        model = base + 3;
        gte_load(IR1, dir, 0);
        gte_load(IR2, dir, 4);
        gte_load(IR3, dir, 8);
        gte_set(IR0, scale);
        gte_set(MAC1, x);
        gte_set(MAC2, y);
        gte_set(MAC3, z);
        gte_gpl12();
        gte_get(IR1, px);
        gte_get(IR2, py);
        gte_get(IR3, pz);
        spark_add(px, py, pz, 0, 0, 0, model, colour);
        if (rand_b_next() % 3 == 0) {
            scale = 0x1333;
            model = base + 4;
            gte_load(IR1, dir, 0);
            gte_load(IR2, dir, 4);
            gte_load(IR3, dir, 8);
            gte_set(IR0, scale);
            gte_set(MAC1, x);
            gte_set(MAC2, y);
            gte_set(MAC3, z);
            gte_gpl12();
            gte_get(IR1, px);
            gte_get(IR2, py);
            gte_get(IR3, pz);
            spark_add(px, py, pz, 0, 0, 0, model, colour);
            scale = 0x333;
            model = base + 5;
            gte_load(IR1, dir, 0);
            gte_load(IR2, dir, 4);
            gte_load(IR3, dir, 8);
            gte_set(IR0, scale);
            gte_set(MAC1, x);
            gte_set(MAC2, y);
            gte_set(MAC3, z);
            gte_gpl12();
            gte_get(IR1, px);
            gte_get(IR2, py);
            gte_get(IR3, pz);
            spark_add(px, py, pz, 0, 0, 0, model, colour);
        }
        obj->vars.quick_fuchikoma_rocket.muzzle_flash_pending = 0;
    }
    scratch_top -= 0x10;
}

void quick_fuchikoma_rocket_draw(Object *obj, ObjHandler *handler);
s32 quick_fuchikoma_rocket_spawn(Vec3 *pos, SVECTOR *rot) {
    Object *obj;
    s32 *tmp;
    s32 *tmp1;
    s32 *tmp2;
    s32 dist;
    u16 roll;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *)get_obj_list_actors_tail(), &obj->node);
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *))quick_fuchikoma_rocket_update;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = quick_fuchikoma_rocket_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = pos->x << 12;
    obj->y = pos->y << 12;
    obj->z = pos->z << 12;
    obj->pitch = rot->vx;
    obj->yaw = rot->vy;
    roll = rot->vz;
    obj->vars.quick_fuchikoma_rocket.muzzle_flash_pending = 1;
    obj->damage = 6;
    obj->roll = roll;
    obj->vars.quick_fuchikoma_rocket.spawn_x = pos->x;
    obj->vars.quick_fuchikoma_rocket.spawn_y = pos->y;
    obj->vars.quick_fuchikoma_rocket.spawn_z = pos->z;
    angles_to_vector(rot->vy, rot->vx, 0x28, &obj->vx, &obj->vy, &obj->vz);
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    tmp = scratch_alloc(0x20);
    tmp1 = tmp + 1;
    tmp2 = tmp + 2;
    obj->unk_17A = 0;
    tmp[0] = 0;
    tmp[1] = 0;
    tmp[2] = 0x64;
    rotate_xz_twice(rot->vy, rot->vx, tmp, tmp1, tmp2);
    obj->vars.quick_fuchikoma_rocket.dir_x = tmp[0];
    obj->vars.quick_fuchikoma_rocket.dir_y = tmp[1];
    obj->vars.quick_fuchikoma_rocket.dir_z = tmp[2];
    tmp[0] = 0;
    tmp[1] = 0;
    tmp[2] = 0x2000;
    rotate_xz_twice(rot->vy, rot->vx, tmp, tmp1, tmp2);
    tmp[0] += pos->x;
    tmp[1] += pos->y;
    tmp[2] += pos->z;
    if (trace_world(8, 8, pos, tmp, tmp + 4) != 0) {
        dist = isqrt(length_sq(tmp[4] - pos->x, tmp[5] - pos->y, tmp[6] - pos->z));
        obj->vars.quick_fuchikoma_rocket.target_x = tmp[4];
        obj->vars.quick_fuchikoma_rocket.target_y = tmp[5];
        obj->vars.quick_fuchikoma_rocket.target_z = tmp[6];
        obj->vars.quick_fuchikoma_rocket.flight_timer = dist / 40;
    } else {
        obj->vars.quick_fuchikoma_rocket.target_x = tmp[0];
        obj->vars.quick_fuchikoma_rocket.target_y = tmp[1];
        obj->vars.quick_fuchikoma_rocket.target_z = tmp[2];
        obj->vars.quick_fuchikoma_rocket.flight_timer = 0xCC;
    }
    scratch_top -= 0x20;
}

s32 quick_fuchikoma_rocket_spawn(Vec3 *pos, SVECTOR *rot);
void mount_flash_spawn(Object *obj, s32 arg1) {
    Vec3 *pos = scratch_alloc(0x20);
    SVECTOR *rot = scratch_alloc(8);
    s32 index = arg1 + 1;

    pos->x = 0;
    pos->y = 0;
    pos->z = 0x84;
    obj_bone_pos(obj, index, pos);
    pos->x = (obj->x >> 12) + pos->x;
    pos->y = (obj->y >> 12) + pos->y;
    pos->z = (obj->z >> 12) + pos->z;
    obj_rec_angles(obj, index, rot);
    quick_fuchikoma_rocket_spawn(pos, rot);
    scratch_top -= 0x28;
}

/* Starts sound 0xA025 once for the whole stage (handle kept in stage_sound_handle)
 * and attaches sound_follow_obj to the calling object as its update. */
void stage_sound_start(Object *obj) {
    s32 handle;

    if (stage_sound_handle == 0) {
        handle = sound_start(SND_HEAVY_GUNFIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        stage_sound_handle = handle;
        sound_attach(handle, obj, (void (*)())sound_follow_obj);
    }
}

extern s32 stage_sound_handle;

void stage_sound_stop(void) {
    if (stage_sound_handle != 0) {
        sound_stop(stage_sound_handle);
        stage_sound_handle = 0;
    }
}

/* Per-object cue: stage 0 starts the stage sound and fires mount_flash_spawn every
   6 ticks until tick 0x29, then stage 1 stops the sound and clears active. */
void stage_cue_update(Object *obj) {
    CueState *cue = *(CueState **)&obj->vars.snd;

    switch (cue->stage) {
    case 0:
        stage_sound_start(obj);
        if ((s16)cue->tick % 6 == 0) {
            mount_flash_spawn(obj, 0);
            mount_flash_spawn(obj, 1);
        }
        if ((s16)cue->tick >= 0x29) {
            cue->stage = (s16)((u16)cue->stage + 1);
        }
        cue->tick = (u16)(cue->tick + 1);
        break;
    case 1:
        stage_sound_stop();
        cue->active = 0;
        break;
    }
}
