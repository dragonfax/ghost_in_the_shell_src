/* part_attach: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

extern s16 D_801273B0;
/* Reads the next halfword of the object's stream (the pointer at 0x20) into script_index. */
void script_read_u16(Object *obj) {
    u16 *stream = (u16 *)obj->script.pc;

    obj->script.pc = stream + 1;
    D_801273B0 = *stream;
}

/* Loads the word of the object's table (the pointer at 0x1C) selected by script_index into the stream slot (0x20). */
void script_jump_indexed(Object *obj) {
    obj->script.pc = ((s16 **)obj->script.data)[D_801273B0];
}

extern Keyframe side_shot_keyframes[13];
static inline s32 launch_speed(s32 offset, s32 speed) {
    return offset * 12 / 256 + (speed >> 12);
}
/* Spawns a keyframed effect (pchr model) beside obj, offset by `index` (+1/-1) around its yaw, then
 * fires a shot from a point 0xD2 out at that side toward obj's speed vector. */
void obj_fire_side_shot(Object *obj, s32 radius, s32 angle_step, s32 index) {
    s32 pos[3];
    SVECTOR offset;
    s16 vel[3];
    s16 accel[4];
    s16 rot[3];
    s32 target[3];

    vec_from_polar(&offset, radius, obj->yaw + index * angle_step);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pos[1] -= 0x6C;
    pos[0] += offset.vx;
    pos[2] += offset.vz;
    vec_from_polar(&offset, index << 8, obj->yaw + angle_step);
    vel[0] = launch_speed(offset.vx, obj->vx);
    vel[2] = launch_speed(offset.vz, obj->vz);
    vel[1] = 0;
    accel[0] = 0;
    accel[1] = 0x1000;
    accel[2] = 0;
    keyframe_track_start(pos, vel, (Bytes8 *)accel, model_slot_pchr(*(s32 *)obj->asset), side_shot_keyframes, 0x800, 0x1FFF);
    rot[0] = -0xC0;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    vec_from_polar(&offset, 0xD2, obj->yaw + index * 0x160);
    {
        register s32 px asm("$3") = obj->x >> 12;

        pos[0] = px;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        pos[1] -= 0x6C;
        pos[0] = px + offset.vx;
        pos[2] += offset.vz;
    }
    target[0] = obj->vx >> 12;
    target[1] = obj->vy >> 12;
    target[2] = obj->vz >> 12;
    if (target[2] < -0x14) {
        target[2] = -0x14;
    }
    rot[0] = -0x80;
    rot[1] = obj->yaw;
    rot[2] = 0;
    rot_turn_toward(pos, rot, 0x20, 0x20);
    shot_spawn_target(pos, (u16 *)rot, target, 1, 0x80001);
}

void obj_fire_side_shot(Object *obj, s32 radius, s32 angle_step, s32 index);
/* Calls obj_fire_side_shot twice for obj: once with +1, once with -1. */
void obj_fire_both_sides(Object *obj) {
    obj_fire_side_shot(obj, 0x80, 0x400, 1);
    obj_fire_side_shot(obj, 0x80, 0x400, -1);
}

void obj_attach_start(Object *obj, void *rot_src, void *unk_1c_src);
void obj_attach_default(Object *obj) {
    s16 from[3];
    s16 to[3];

    from[0] = 0;
    from[1] = -0x8C;
    from[2] = 0x5A;
    to[0] = 0;
    to[1] = 0;
    to[2] = 0;
    obj_attach_start(obj, from, to);
}

extern s32 obj_sound_loop_handle;

void obj_sound_loop_start(Object *obj) {
    s32 temp_v0;

    if (obj_sound_loop_handle == 0) {
        temp_v0 = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x46, 0, 0);
        obj_sound_loop_handle = temp_v0;
        if (temp_v0 != 0) {
            sound_attach(temp_v0, &obj->x, NULL);
        }
    }
}

extern s32 obj_sound_loop_handle;

void obj_sound_loop_stop(Object *obj, s32 unused) {
    if (obj_sound_loop_handle != 0) {
        sound_stop(obj_sound_loop_handle);
        obj_sound_loop_handle = 0;
    }
}

extern s32 sound_held_handle;

void sound_start_held(Object *obj) {
    s32 temp_v0;

    if (sound_held_handle == 0) {
        temp_v0 = sound_start(SND_PAIR(SND_WHIRR | SND_HELD | SND_GROUP(1), SND_WHIRR_LOOP | SND_HELD | SND_GROUP(1)), 0x64, 0, 0);
        sound_held_handle = temp_v0;
        if (temp_v0 != 0) {
            sound_attach(temp_v0, &obj->x, NULL);
        }
    }
}

extern s32 sound_held_handle;

void sound_stop_held(Object *obj, s32 unused) {
    if (sound_held_handle != 0) {
        sound_stop(sound_held_handle);
        sound_held_handle = 0;
    }
}

void enemy_part_child_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

void obj_pos_from_ref(Object *obj) {
    SVECTOR offset;
    VECTOR pos;
    PosRef *src;
    u16 yaw;

    src = (PosRef *)obj->vars.enemy.mode;
    vec_from_polar(&offset, 0x366, src->unk_25E);
    obj->x = (src->pos_x + offset.vx) << 12;
    obj->y = ((src->pos_y + offset.vy) - 0xC0) << 12;
    obj->z = (src->pos_z + offset.vz) << 12;
    pos.vx = obj->x >> 12;
    pos.vy = obj->y >> 12;
    pos.vz = obj->z >> 12;
    offset.vx = ((PosRef *)obj->vars.enemy.mode)->pitch;
    yaw = ((PosRef *)obj->vars.enemy.mode)->yaw;
    offset.vy = yaw;
    offset.vz = ((PosRef *)obj->vars.enemy.mode)->roll;
    obj->yaw = yaw;
    obj->pitch = 0;
    obj->roll = 0;
}

void obj_pos_from_ref(Object *obj);
void obj_move_update(Object *obj, ObjHandler *handler) {
    s32 prev_pos[3];

    collider_begin((Collider *) &obj->unk_A4);
    prev_pos[0] = obj->x;
    prev_pos[1] = obj->y;
    prev_pos[2] = obj->z;
    obj_pos_from_ref(obj);
    obj->vx = obj->x - prev_pos[0];
    obj->vy = obj->y - prev_pos[1];
    obj->vz = obj->z - prev_pos[2];
    obj->move_delta[0] = obj->vx >> 12;
    obj->move_delta[1] = obj->vy >> 12;
    obj->move_delta[2] = obj->vz >> 12;
    obj_script_step(obj, handler);
}

extern s16 obj_hit_mask_weights[];
s32 obj_hit_mask_avg(s32 mask, s16 *values);
void obj_hit_reaction(Object *obj, s32 arg1);
void obj_hit_apply(Object *obj, ObjHandler *handler) {
    s32 rate;
    s32 scaled;
    s32 flags;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    rate = obj_hit_damage(obj->index);
    if (obj->hit_cooldown != 0) {
        /* countdown; 0xFF instead of -- (the original's addiu is 0xFF) */
        obj->hit_cooldown += 0xFF;
    }
    if (rate > 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        scaled = rate * obj_hit_mask_avg(obj_hit_type(obj->index) & 0xFF, obj_hit_mask_weights);
        rate = scaled >> 12;
        if (scaled < 0) {
            rate = (scaled + 0xFFF) >> 12;
        }
        obj->health -= rate;
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
    if (obj->health <= 0) {
        /* dead: vars.words[0] points at the owner, whose vars.words[0] is the
         * object whose 0x27A halfword is cleared (unk_27A) */
        handler->state = 1;
        ((Object *) obj->vars.enemy_part_child.owner)->health = 0;
        ((s16 *) ((Object *) ((Object *) obj->vars.enemy_part_child.owner)->vars.words[0])->vars.words)[25] = 0;
        return;
    }
    ((Object *) obj->vars.enemy_part_child.owner)->health = obj->health;
    flags = obj->flags;
    if (((u32) flags >> 5) & 1) {
        obj_hit_reaction(obj, 0);
    }
}

/* Runs the object's callback (0x170) if it has one; a callback that returns 0 is cleared.
 * The unused array keeps the 0x30-byte frame of the original (its locals are not recoverable). */
void obj_callback_tick(Object *obj, ObjHandler *handler) {
    s32 (*callback)(void);
    s32 unused[6];

    callback = (s32 (*)(void))obj->callback;
    if (callback != NULL && callback() == 0) {
        obj->callback = 0;
    }
}

/* Applies hits while the object is alive; once handler->state marks it dead,
 * clears its hit reaction and runs its callback.
 * The first test reads a local: with handler->state read the same way twice, thread_jumps sends the
 * first branch past the second test (FINDINGS "Jump threading over a repeated test"). */
void obj_hit_state_update(Object *obj, ObjHandler *handler) {
    s16 state = handler->state;

    if (state == 0) {
        obj_hit_apply(obj, handler);
    }
    if (handler->state != 0) {
        obj_set_hit_reaction(obj, 0);
        obj_callback_tick(obj, handler);
    }
}

static inline void spark_add_list0(s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    register SparkList *list asm("$4");
    s32 n;
    SparkRec *s;
    u8 *tail;

    __asm__("" : "=r"(list) : "0"(&spark_list));
    n = spark_count;
    if (n < 0xFF) {
        s = (SparkRec *)(n * sizeof(SparkRec) + (s32)list->items);
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[0];
        list->tail[0] = &s->next;
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
/* Draws the object as one spark record at its position, tinted while hit. */
void obj_hit_spark_draw(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 colour;
    s32 value;
    s32 pitch;
    s32 unused[2];

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    colour = 0;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
        pitch = 0;
    }
    if (test_bit(obj->flags, 6)) {
        s32 base = obj->type.unk_0E;

        value = base + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        value = obj_keyframe_value(obj, 0);
    }
    spark_add_list0( pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], value, colour);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

/* Dying enemy part: smokes every 8 frames, after 96 frames frees itself and spawns its debris. */
void attach_reset(void);

s32 enemy_part_dying_update(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 x;
    s32 y;
    s32 z;
    s32 effect;
    s32 jitter_x;
    s32 base_x;
    s32 jitter_z;
    s32 base_z;
    Object *owner;

    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    attach_reset();
    obj->vars.enemy_part_child.unused_250++;
    obj_sound_loop_stop(obj, 0);
    sound_stop_held(obj, 0);
    if (obj->vars.enemy_part_child.unused_250 > 96) {
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot[0] = obj->pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        owner = (Object *) obj->vars.enemy_part_child.owner;
        owner->vars.part.unk_280 = 5;
        obj_free(obj);
        object_spawn_at(pos, rot, model_slot_pchr(*(s32 *) obj->asset) + 0x118);
        return 0;
    }
    if ((obj->vars.enemy_part_child.unused_250 & 7) == 0) {
        x = obj->x >> 12;
        y = obj->y >> 12;
        z = obj->z >> 12;
        jitter_x = rand_a_next();
        base_x = x - 0x80;
        x = base_x + jitter_x / 16;
        y = y - rand_a_next() / 16;
        jitter_z = rand_a_next();
        base_z = z - 0x80;
        z = base_z + jitter_z / 16;
        effect = ((rand_a_next() & 1) == 0) * 2;
        if (!((obj->vars.enemy_part_child.unused_250 >> 3) & 1)) {
            spawn_effect(x, y, z, (effect + 0x7F00) | 0x80000000);
        } else {
            spawn_effect(x, y, z, effect | 0x80000000);
        }
    }
    return 1;
}

extern ScriptCallEntry D_8011F160[14];
extern StateEntry D_8011F2E4[5];
extern SoundVolume D_8011F124[]; /* obj->unk_19C: sound id, volume */
extern s16 *enemy_part_child_jump_table[9];
extern s16 *D_8011F2E0[];
extern s16 *enemy_part_child_script_table[];
s32 enemy_part_dying_update(Object *obj);
Object *enemy_part_child_spawn(Object *parent) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return NULL;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj->handlers[0].fn = (ObjHandlerFn) enemy_part_child_phase0;
    obj->handlers[1].fn = (ObjHandlerFn) obj_move_update;
    obj->handlers[2].fn = (ObjHandlerFn) obj_hit_state_update;
    obj->handlers[3].fn = (ObjHandlerFn) obj_hit_spark_draw;
    obj->asset = semi_truck_mech_asset;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = D_8011F160;
    obj->state_table = D_8011F2E4;
    obj->vars.part.parent = parent;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->unk_1C6 = 0;
    obj->sounds = D_8011F124;
    obj->script.pc = D_8011F2E0[0];
    obj->script.data = enemy_part_child_jump_table;
    obj->script.unk_0A = 0;
    obj->callback = (s32) &enemy_part_dying_update;
    script_start((Script *) obj, enemy_part_child_script_table[0], (s32) enemy_part_child_script_table);
    obj_init_common(obj, 0x31);
    obj_set_extents_from_part(obj, ((s32 *) parent->vars.part.parent->asset)[1] + 0x101, 0x1000);
    obj_set_hit_reaction(obj, 1);
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, 2);
    obj_pos_from_ref(obj);
    obj_sound_loop_handle = 0;
    sound_held_handle = 0;
    obj->health = 0xDAC;
    obj->vars.enemy_part_child.unused_250 = 0;
    obj_hit_flag_set(obj->index, 0x80);
    return obj;
}

void obj_noop_update(void) {
}

s32 shot_hit_trace(s32 *from, s32 *to_unused, HitPos16 *to, s32 flags, s32 type, s32 damage);
s32 trace_ray_dist(Vec4 *pos, s16 *rot, s32 unused, s32 ctx, s32 max_dist, s32 layer, s32 mask) {
    Vec4 origin;
    Vec3 offset;
    Vec3 hit;

    offset.x = 0;
    offset.y = 0;
    offset.z = max_dist;
    rotate_xz_twice(rot[1], rot[0], &offset.x, &offset.y, &offset.z);
    offset.x += pos->v[0];
    offset.y += pos->v[1];
    offset.z += pos->v[2];
    origin = *pos;
    if (shot_hit_trace(origin.v, &offset.x, (HitPos16 *)&hit, ctx, layer, mask) != 0) {
        return SquareRoot0(length_sq(hit.x - origin.v[0], hit.y - origin.v[1], hit.z - origin.v[2]));
    }
    return max_dist;
}

s32 trace_ray_dist(Vec4 *pos, s16 *rot, s32 unused, s32 ctx, s32 max_dist, s32 layer, s32 mask);
s32 trace_ray_dist_plain(Vec4 *pos, s16 *rot, s32 unused, s32 ctx, s32 max_dist) {
    return trace_ray_dist(pos, rot, unused, ctx, max_dist, 0, 0);
}

void trace_ray_probe(Vec4 *pos, s16 *rot, s32 unused, s32 ctx, s32 max_dist, s32 layer, s32 mask) {
    trace_ray_dist(pos, rot, unused, ctx, max_dist, layer, mask);
}

/* Rotates the s16 offset vector rot[] by the two angles and adds the
 * result to the s32 position vector pos[]. */
void vec_add_rotated(s32 *pos, s16 *rot, s32 angle2, s32 angle1) {
    s32 offset_x;
    s32 offset_y;
    s32 offset_z;

    offset_x = rot[0];
    offset_y = rot[1];
    offset_z = rot[2];
    rotate_xz_twice(angle2, angle1, &offset_x, &offset_y, &offset_z);
    pos[0] += offset_x;
    pos[1] += offset_y;
    pos[2] += offset_z;
}

/* Sets the part's position from its object's position, adds yaw * 3 to the
 * angle sum, and rotates the part's offset by the object's yaw and pitch. */
void attach_update(ObjAttach *a) {
    a->pos[0] = a->obj->x >> 12;
    a->pos[1] = a->obj->y >> 12;
    a->pos[2] = a->obj->z >> 12;
    *(Unaligned8 *)a->unk_24 = *(Unaligned8 *)a->unk_1C;
    a->angle_sum += a->obj->yaw * 3;
    vec_add_rotated(a->pos, a->rot, a->obj->yaw, a->obj->pitch);
}

s32 ratan2(s32 y, s32 x);
/* Per-frame update of an attach entry: follows its object, adds fade_rate to
 * the level in unk_30 (the entry goes inactive once it drops below 0; the
 * level is kept in 0..0x1000), picks a new flicker value, eases range toward
 * the player's horizontal distance + 0x80 (at most 0x10 a frame, kept in
 * 0..0x2000) and turns rx toward the angle of (y + 0x780, range). */
void attach_entry_update(AttachEntry *rec) {
    s32 level;
    s32 height;
    s32 range;
    s32 angle;

    attach_update((ObjAttach *)rec);
    level = rec->level;
    level += rec->fade_rate;
    if (level < 0) {
        rec->active = 0;
    }
    /* The loop doubles the clamp's register priorities, as in the original. */
    do {
        level = MAX(MIN(level, 0x1000), 0);
    } while (0);
    rec->level = level;
    rec->flicker = rand_a_next();
    height = ((AttachView *)rec)->y + 0x780;
    range = player_horiz_dist(&((AttachView *)rec)->x) + 0x80;
    range = rec->range - 0x10 > MIN(range, rec->range + 0x10)
        ? rec->range - 0x10 : MIN(range, rec->range + 0x10);
    range = MAX(MIN(range, 0x2000), 0);
    angle = ratan2(height, range);
    rec->range = range;
    ((AttachView *)rec)->rx = angle_approach(((AttachView *)rec)->rx, angle, 1) + angle;
}

extern AttachEntry attach_table[];
void attach_entry_update(AttachEntry *rec);
void attach_update_all(void) {
    AttachEntry *rec = attach_table;
    s32 i = 0;
    do {
        if (rec->active != 0) {
            attach_entry_update(rec);
        }
        i++;
        rec++;
    } while (i <= 0);
}

/* Stores trace_ray_dist_plain's result in unk_2C; if unk_30 == 0x1000 and the
 * result != 0x1E00, also calls trace_ray_probe with extra args 8 and 0x10. */
void attach_probe(AttachEntry *rec) {
    s32 result;

    result = trace_ray_dist_plain((Vec4 *)rec->ray_pos, (s16 *)rec->ray_rot, 0xC0, 0x10, 0x1E00);
    rec->ray_dist = result;
    if (rec->level == 0x1000 && result != 0x1E00) {
        trace_ray_probe((Vec4 *)rec->ray_pos, (s16 *)rec->ray_rot, 0xC0, 0x10, 0x1E00, 8, 0x10);
    }
}

/* Same code as attach_update_all (s06). */
void shots_trace(void) {
    AttachEntry *rec = attach_table;
    s32 i = 0;
    do {
        if (rec->active != 0) {
            attach_probe(rec);
        }
        i++;
        rec++;
    } while (i <= 0);
}


/* Clears a 3-word vector (x, y, z pointers into the same block) and rotates it by two angles; the
 * fourth argument is stored in the third word before the rotation. */
void vec3_set_from_angles(s32 *out, s32 angle2, s32 angle1, s32 w) {
    out[2] = w;
    out[0] = 0;
    out[1] = 0;
    rotate_xz_twice(angle2, angle1, out, &out[1], &out[2]);
}


void attach_draw_entry(AttachEntry *rec) {
    AttachView *a = (AttachView *)rec;
    s32 step[3];
    s32 value;
    s32 count;
    s32 colour;
    s32 rem;
    s32 x, y, z;
    s32 ry;
    s32 rx;
    s32 sum, lo, green;
    register s32 clamped asm("$3");

    count = a->dist / 192;
    value = model_slot_pchr(*(s32 *)a->obj->asset);
    x = a->x;
    y = a->y;
    z = a->z;
    rx = a->rx;
    ry = a->ry;
    value += 0x1D0;
    rem = a->dist % 192;
    vec3_set_from_angles(step, ry, rx, 0xC0);
    sum = a->unk_30 / 2;
    sum += a->unk_3E / 4;
    clamped = sum;
    if (sum >= 0x2000) {
        clamped = 0x1FFF;
    }
    if (MIN(sum, 0x1FFF) < 0) {
        clamped = 0;
    }
    lo = clamped >> 5;
    green = lo;
    if (green == 0) {
        green = 1;
    }
    colour = (green << 16) | (lo << 8) | lo;
    for (; count > 0; count--) {
        spark_add(x, y, z, ry, rx, 0, value, colour);
        x += step[0];
        y += step[1];
        z += step[2];
    }
    if (a->dist != 0x1E00) {
        value = model_slot_pchr(*(s32 *)a->obj->asset) + 0x1D8;
        value = pool_spawn_scaled(value + (a->unk_3E & 1), 0x1000, 0x1000, 0x1000);
        vec3_set_from_angles(step, ry, rx, rem);
        spark_add(x + step[0], y + step[1], z + step[2], ry, rx, a->unk_3E, value, colour);
    }
    rem = (rem << 12) / 192;
    value = pool_spawn_scaled(model_slot_pchr(*(s32 *)a->obj->asset) + 0x1D0, 0x1000, 0x1000, rem);
    spark_add(x, y, z, ry, rx, 0, value, colour);
}

/* Same code as attach_update_all (s06). */
void attach_draw_all(void) {
    AttachEntry *rec = attach_table;
    s32 i = 0;
    do {
        if (rec->active != 0) {
            attach_draw_entry(rec);
        }
        i++;
        rec++;
    } while (i <= 0);
}

/* Returns the first 0x44-byte entry of attach_table whose unk_3C is 0, or NULL.
 * The loop bound is an s32 counter that must stay <= 0, so it runs at most once
 * in practice; the search effectively checks the first entry only. */
AttachEntry *attach_find_free(void) {
    AttachEntry *p;
    s32 i;

    p = attach_table;
    for (i = 0; i <= 0; i++, p++) {
        if (p->active == 0) {
            return p;
        }
    }
    return NULL;
}

/* Claims a free AttachEntry slot for an object: sets its object pointer, copies two
 * 8-byte unaligned blocks (rot and unk_1C), then sets up the rest of the record and
 * its attach state. */
void obj_attach_start(Object *obj, void *rot_src, void *unk_1c_src) {
    AttachEntry *rec;
    ObjAttach *a;

    rec = attach_find_free();
    if (rec != NULL) {
        a = (ObjAttach *)rec;
        a->obj = obj;
        rec->active = 1;
        *(Unaligned8 *)a->rot = *(Unaligned8 *)rot_src;
        *(Unaligned8 *)a->unk_1C = *(Unaligned8 *)unk_1c_src;
        rec->level = 0;
        rec->fade_rate = 0x40;
        attach_update(a);
        rec->ray_dist = trace_ray_dist_plain((Vec4 *)rec->ray_pos, (s16 *)rec->ray_rot, 0xC0, 0x10, 0x1E00);
        rec->unk_40 = 0;
        rec->range = 0x200;
    }
}

extern s32 attach_timer;

void attach_timer_reset(void) {
    attach_timer = 0x40;
}

/* Clears unk_3C of the first record. The original loop's counter starts at 0,
 * so the body runs once. */
void attach_clear(void) {
    AttachEntry *rec;
    s32 i;

    rec = attach_table;
    i = 0;
    do {
        rec->active = 0;
        i -= 1;
        rec++;
    } while (i >= 0);
}

void attach_reset(void) {
    attach_clear();
}

extern s32 span_table_base[17];
extern s32 span_source_table[41];
/* If stage_ready_get reports a result, runs the span setup on span_table_base with span_source_table as its source. Then
 * sets the flow max to 0x20, sets the status bit 1 and the player mode flags to 6. */
void stage_setup_flow(void) {
    if (stage_ready_get() != 0) {
        span_table_build((s32) span_table_base, span_source_table);
    }
    set_flow_max(0x20);
    set_player_status(get_player_status() | 1);
    set_player_mode_flags(6);
}

void mech_aux_phase2(Object *obj, ObjHandler *handler);
void mech_aux_draw(Object *obj, ObjHandler *handler);
s32 mech_aux_spawn(void) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_b(), &obj->node);
    obj->handlers[2].fn = mech_aux_phase2;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = mech_aux_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    return 1;
}

void mech_aux_phase2(Object *obj, ObjHandler *handler) {
}

void mech_aux_draw(Object *obj, ObjHandler *handler) {
}
