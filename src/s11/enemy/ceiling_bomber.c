/* ceiling_bomber: one of s11's own original source files (scripts/objmap.py); part of src/s11/main.c's unit, included there. */

void rotate_vector_int(s32 *src, s32 *dst) {
    gte_load(IR1, src, 0);
    gte_load(IR2, src, 4);
    gte_load(IR3, src, 8);
    gte_rtirtr();
    gte_store(MAC1, dst, 0);
    gte_store(MAC2, dst, 4);
    gte_store(MAC3, dst, 8);
}


/* As func_800B93C4, unshifted. */
void vec_rotate_rt_raw(s32 *src, s32 *dst) {
    gte_load(IR1, src, 0);
    gte_load(IR2, src, 4);
    gte_load(IR3, src, 8);
    gte_rtirtr_sf0();
    gte_store(MAC1, dst, 0);
    gte_store(MAC2, dst, 4);
    gte_store(MAC3, dst, 8);
}

void script_jump_if_player_near(Object *obj) {
    s16 *stream;
    s32 range;
    s32 slot;
    s32 *player;

    /* Read two halfwords from the object's stream: a distance range and a table slot. */
    stream = obj->script.pc;
    obj->script.pc = stream + 1;
    range = stream[0];
    obj->script.pc = stream + 2;
    slot = stream[1];

    if (player_position()[1] >= (obj->y >> 12)) {
        player = player_position();
        if (range >= isqrt(length_sq(player[0] - (obj->x >> 12),
                                     player[1] - (obj->y >> 12),
                                     player[2] - (obj->z >> 12)))) {
            obj->script.pc = ((s16 **)obj->script.data)[slot];
        }
    }
}

void ceiling_bomber_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

/* Advances the enemy's shot timer by 0x140 a step until it reaches 0xF00, then hands the object to
   state 6 through obj_request_state. Words[0xC] (0x278, unnamed) accumulates a 1/64 of the timer each call. */
void enemy_charge_update(Object *obj, ObjHandler *handler) {
    s32 timer;

    timer = obj->vars.enemy.shot_timer;
    if (timer < 0xF00) {
        obj->vars.enemy.shot_timer = timer + 0x140;
    } else {
        obj_request_state(obj, handler, 6, 0);
    }
    obj->vars.words[0xC] += obj->vars.enemy.shot_timer >> 6;
}

/* Winds the shot timer down by 0x140 a step; once it has run out, hands off to the next state (obj_request_state),
   then adds the timer's scaled value to the yaw offset word at 0x278. */
void enemy_cool_update(Object *obj, ObjHandler *handler) {
    s32 timer;

    timer = obj->vars.enemy.shot_timer;
    if (timer > 0) {
        obj->vars.enemy.shot_timer = timer - 0x140;
    } else {
        obj_request_state(obj, handler, 6, 0);
    }
    /* 0x278 is a whole word here (lw/sw); stage.h has only its halfword view at turn.yaw_offset */
    obj->vars.words[0xC] += obj->vars.enemy.shot_timer >> 6;
}

s32 spark_debris_spawn(Object *parent, s32 *pos, u16 *rot, s32 narrow, s32 kind);
void enemy_smoke_update(Object *obj, ObjHandler *h) {
    s32 *pos;
    s16 *rot;
    s32 *vel;
    s32 *m;
    s32 a, b, c;
    s32 step;
    s32 r, vy;

    step = h->result;
    obj->vars.words[0xC] += obj->vars.words[0xD] >> 6;
    if (step == -2) {
        h->queued_entry = -1;
        h->result = 0x3C;
        return;
    }
    if (step == (step / 6) * 6) {
        if (obj->health > 0) {
            pos = scratch_alloc(0x20);
            pos[0] = obj->x;
            pos[1] = obj->y;
            pos[2] = obj->z;
            rot = scratch_alloc(8);
            rot[0] = obj->pitch;
            rot[1] = obj->yaw;
            rot[2] = obj->roll;
            vel = pos + 4;
            vy = (rand_a_next() * 3 / 4096) * 30 + 0x32;
            if (rot[0] == 0 && rot[2] == 0) {
                r = ((rand_a_next() / 2048) * 30 + 0x2D) << 12;
                pos[4] = 0;
                pos[5] = r;
                pos[6] = 0;
                pos[0] += pos[4];
                pos[1] += pos[5];
                pos[2] += pos[6];
                sound_play_at(SND_ENEMY_SMOKE_PUFF | SND_GROUP(1), 0x40, 0x3C, pos);
                spark_debris_spawn(obj, pos, rot, 0, obj->damage);
            } else {
                vel[0] = 0;
                vel[1] = vy;
                vel[2] = 0;
                m = &obj->vars.ceiling_bomber.rot_matrix;
                gte_load_R012(m, a, b, c);
                gte_load_R34(m, a, b);
                gte_set_ctrl(TRX, 0);
                gte_set_ctrl(TRY, 0);
                gte_set_ctrl(TRZ, 0);
                vec_rotate_rt_raw(vel, vel);
                pos[0] += vel[0];
                pos[1] += vel[1];
                pos[2] += vel[2];
                spark_debris_spawn(obj, pos, rot, 1, obj->damage);
            }
            scratch_top -= 0x28;
        }
    }
    if (step == -1) {
        obj_request_state(obj, h, 6, 0);
    }
}

/* Saves the position, moves the object back by the words at 0x268..0x270 around obj_run_states_default, then restores the saved position. */
void ceiling_bomber_update(Object *obj, ObjHandler *handler) {
    Vec3 *saved = scratch_alloc(0x10);

    saved->x = obj->x;
    saved->y = obj->y;
    saved->z = obj->z;
    obj->x -= obj->vars.ceiling_bomber.offset_x;
    obj->y -= obj->vars.ceiling_bomber.offset_y;
    obj->z -= obj->vars.ceiling_bomber.offset_z;
    obj_script_step(obj, handler);
    obj->x = saved->x;
    obj->y = saved->y;
    obj->z = saved->z;
    scratch_top -= 0x10;
}

/* Saves the position, moves the object back by the words at 0x268..0x270 around obj_run_states_default, then restores the saved position. */
void ceiling_bomber_phase2(Object *obj, ObjHandler *handler) {
    Vec3 *saved = scratch_alloc(0x10);

    saved->x = obj->x;
    saved->y = obj->y;
    saved->z = obj->z;
    obj->x -= obj->vars.ceiling_bomber.offset_x;
    obj->y -= obj->vars.ceiling_bomber.offset_y;
    obj->z -= obj->vars.ceiling_bomber.offset_z;
    obj_run_states_default(obj, handler);
    obj->x = saved->x;
    obj->y = saved->y;
    obj->z = saved->z;
    scratch_top -= 0x10;
}

s32 enemy_shooter_update(Object *obj) {
    s32 ret = 1;
    s32 *m;
    s32 *p;
    s32 a, b, c;

    switch (obj->vars.enemy.shots_left) {
    case -2:
        obj->unk_17A = 0;
        obj->handlers[0].fn = 0;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->vars.enemy.shots_left = 0x10;
        break;
    case -1:
        ret = 0;
        placement_list_pop((ListRecord *)obj->placement);
        obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
        break;
    default:
        if ((obj->vars.enemy.shots_left & 0xF) == 0) {
            p = (s32 *)scratch_top;
            p[4] = obj->x >> 12;
            p[5] = obj->y >> 12;
            scratch_top += 0x20;
            p[6] = obj->z >> 12;
            p[0] = rand_a_next() * 100 / 4096 - 0x32;
            p[1] = 100;
            p[2] = rand_a_next() * 100 / 4096 - 0x32;
            m = &obj->vars.ceiling_bomber.rot_matrix;
            gte_load_R012(m, a, b, c);
            gte_load_R34(m, a, b);
            gte_set_ctrl(TRX, 0);
            gte_set_ctrl(TRY, 0);
            gte_set_ctrl(TRZ, 0);
            rotate_vector_int(p, p);
            spawn_effect(p[4] + p[0], p[5] + p[1], p[6] + p[2], 0);
            scratch_top -= 0x20;
        }
        obj->vars.enemy.shots_left--;
        break;
    }
    return ret;
}

static inline void spark_list_add(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    SparkList *head;
    s32 n = SPARK_COUNT;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
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
static inline void rot_y_matrix(RotMatrix *m, u32 sincos) {
    s16 cos_val;
    s16 neg_sin;

    m->m[0][1] = 0;
    m->m[1][0] = 0;
    m->m[1][1] = 0x1000;
    m->m[1][2] = 0;
    m->m[2][1] = 0;
    cos_val = sincos >> 16;
    neg_sin = -sincos;
    m->m[0][0] = cos_val;
    m->m[0][2] = sincos;
    m->m[2][0] = neg_sin;
    m->m[2][2] = cos_val;
}
void ceiling_bomber_draw(Object *obj, ObjHandler *handler) {
    RotMatrix *mat;
    s32 *vec;
    s32 *pos;
    s32 *offset;
    s32 *angles;
    SparkList *list;
    s32 colour;
    s32 value;
    RotMatrix *rot;
    s32 x, y, z;
    s32 rx;

    mat = scratch_alloc(0x20);
    vec = scratch_alloc(0x30);
    colour = 0;
    pos = vec;
    offset = pos + 4;
    angles = pos + 8;

    x = obj->x;
    y = obj->y;
    z = obj->z;
    x -= obj->vars.ceiling_bomber.offset_x;
    y -= obj->vars.ceiling_bomber.offset_y;
    z -= obj->vars.ceiling_bomber.offset_z;
    pos[0] = x >> 12;
    pos[1] = y >> 12;
    pos[2] = z >> 12;
    FAKE_OPAQUE(colour);
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    }
    value = model_slot_pchr(*(s32 *)obj->asset);
    rx = -obj->pitch;
    list = &spark_list;
    spark_list_add(list, pos[0], pos[1], pos[2], obj->yaw, rx, obj->roll, value, colour);

    value = obj_keyframe_value(obj, 0);
    rot = (RotMatrix *)&obj->vars.ceiling_bomber.rot_matrix;
    rot_y_matrix(mat, rcossin_tbl[obj->vars.ceiling_bomber.angle & 0xFFF]);
    mul_matrix(rot, mat, mat);
    /* the loop doubles mat's ref count: mat outranks obj for $s2 (global-alloc priority) */
    do {
        matrix_to_angles(mat, &angles[1], angles, &angles[2]);
    } while (0);

    rot_matrix_load(rot);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    offset[0] = 0;
    offset[1] = 0xC;
    offset[2] = 0;
    rotate_vector_int(offset, offset);
    pos[0] += offset[0];
    pos[1] += offset[1];
    pos[2] += offset[2];
    spark_list_add(list, pos[0], pos[1], pos[2], angles[1], angles[0], angles[2], value, colour);

    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x50;
}

extern s32 ceiling_bomber_asset[3];
extern s32 spark_pchr_base;
void spark_init_packet_ptr(void) {
    spark_pchr_base = model_slot_pchr(ceiling_bomber_asset[0]) + 8;
}

extern s16 *ceiling_bomber_script_data[];
extern SoundVolume D_80119FC8[];
extern StateEntry D_8011A0F8[];
extern ScriptCallEntry D_8011A0E8[2];
extern struct { s16 *v; } ceiling_bomber_script_link;
void ceiling_bomber_draw(Object *obj, ObjHandler *handler);
extern s16 *ceiling_bomber_data[];
/* Spawns a ceiling bomber from a placement; returns 1 if the object was made. */
s32 ceiling_bomber_spawn(Placement *place) {
    Object *obj = obj_new();
    register s32 *m asm("$16"); /* the original keeps the matrix in s0 */
    s32 *v;
    s16 *link4;

    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), &obj->node);
    place->unk_02 = -1;
    obj->handlers[0].fn = ceiling_bomber_phase0;
    obj->handlers[1].fn = ceiling_bomber_update;
    obj->handlers[2].fn = ceiling_bomber_phase2;
    obj->handlers[3].fn = ceiling_bomber_draw;
    obj->callback = (s32)enemy_shooter_update;
    obj->asset = ceiling_bomber_asset;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = D_8011A0E8;
    obj->state_table = D_8011A0F8;
    obj->sounds = D_80119FC8;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->kind = 0;
    obj->unk_1C6 = 0;
    link4 = ceiling_bomber_script_link.v;
    obj->script.data = ceiling_bomber_script_data;
    obj->script.unk_0A = 0;
    obj->script.pc = link4;
    script_start((Script *)obj, ceiling_bomber_data[0], (s32)ceiling_bomber_data);
    obj_init_from_place(obj, place, 0x25);
    obj_set_part_bounds(obj, 3, 0x1000);
    m = (s32 *)scratch_top;
    scratch_top += 0x20;
    v = (s32 *)scratch_top;
    scratch_top += 0x10;
    obj->vars.words[0xC] = 0;
    obj->vars.words[0xD] = 0;
    obj->vars.words[0xE] = -2;
    rot_matrix(m, obj->yaw, -obj->pitch, obj->roll);
    *(CeilingBomberMat *)&obj->vars.ceiling_bomber.rot_matrix = *(CeilingBomberMat *)m;
    /* rotation matrix into the GTE control registers, as one group */
    gte_load_R_v1a0v0(m);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    v[0] = 0;
    v[1] = (s16)obj->height;
    v[2] = 0;
    vec_rotate_rt_raw(v, v);
    obj->x += v[0];
    obj->y += v[1];
    obj->z += v[2];
    obj->vars.ceiling_bomber.offset_x = v[0];
    obj->vars.ceiling_bomber.offset_y = v[1];
    obj->vars.ceiling_bomber.offset_z = v[2];
    scratch_top -= 0x30;
    obj_hit_set_unk08(obj->index, 1);
    obj_hit_set_unk06(obj->index, 0);
    return 1;
}

/* Moves a falling object one step (gravity clamped at 0x30000), traces the
   step against the world and other objects, and reacts to the first hit:
   the object is freed, and on a target hit a sound and an effect play and
   the target takes damage. */
void obj_fall_step(Object *obj) {
    s32 *start;
    s32 *end;
    s32 *hit_pos;
    s16 hit_obj;
    s32 x;
    s32 y;
    s32 z;
    s32 fall_speed;
    s32 hit_kind;

    start = scratch_alloc(0x30);
    end = start + 4;
    hit_pos = start + 8;

    x = obj->x;
    y = obj->y;
    z = obj->z;
    start[0] = x >> 12;
    start[1] = y >> 12;
    start[2] = z >> 12;

    fall_speed = obj->vy + obj->accel_y;
    if (fall_speed > 0x30000) {
        fall_speed = 0x30000;
    }
    y += fall_speed;
    obj->vy = fall_speed;
    obj->y = y;
    x += obj->vx;
    z += obj->vz;
    obj->x = x;
    obj->z = z;

    end[0] = x >> 12;
    end[1] = y >> 12;
    end[2] = z >> 12;

    hit_kind = 0;
    if (cam_range_check(end[0], end[1], end[2]) == 0) {
        hit_kind = 1;
    } else if ((obj_hit_damage(obj->index) << 16) > 0) {
        hit_kind = 2;
    } else if (trace_world(8, 8, start, end, hit_pos) == 1) {
        hit_kind = 3;
    } else {
        set_collide_mode(1);
        if (trace_objects(start, end, 8, hit_pos, &hit_obj) != 0) {
            hit_kind = 4;
        }
        set_collide_mode(0);
    }

    switch (hit_kind) {
    case 0:
        break;
    case 1:
        obj_free(obj);
        break;
    case 2:
        spawn_effect(hit_pos[0], hit_pos[1], hit_pos[2], 2);
        obj_free(obj);
        break;
    case 3:
        spawn_effect(hit_pos[0], hit_pos[1], hit_pos[2], 2);
        obj_free(obj);
        break;
    case 4:
        sound_play_at_units(SND_S11_PROJECTILE_IMPACT | SND_GROUP(2), 0x20, 0x3C, hit_pos);
        spawn_effect(hit_pos[0], hit_pos[1], hit_pos[2], 2);
        hit_target_masked(0, 1, atan2(hit_pos[2] - start[2], hit_pos[0] - start[0]), obj->damage);
        obj_free(obj);
        break;
    }

    scratch_top -= 0x30;
}

void spark_add_chain0(Object *obj) {
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 n = spark_count;
    s32 z = obj->z >> 12;
    s32 value = spark_pchr_base;
    s32 yaw = obj->yaw;
    s32 pitch = obj->pitch;
    s32 roll = obj->roll;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    list = &spark_list;
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
        s->yaw = yaw;
        s->pitch = pitch;
        s->roll = roll;
    }
}

/* Builds the object's yaw matrix and the negated unk_2C matrix, multiplies them into the first, and writes the
 * angles of the product to out (out[0], out[4] and out[8] as in matrix_to_angles). */
void obj_get_world_angles(Object *obj, u8 *out) {
    u8 *m = scratch_alloc(0x40);
    u8 *m2 = m + 0x20;

    rot_matrix(m, obj->yaw, 0, 0);
    rot_matrix(m2, -obj->rot_angles[1], -obj->rot_angles[0], -obj->rot_angles[2]);
    mul_matrix(m2, m, m);
    matrix_to_angles(m, out + 4, out, out + 8);
    scratch_top -= 0x40;
}

/* Spawns a falling spark at pos with rotation rot, its velocity rotated by the parent's matrix (vars) and a turn
 * about Y: random over the full circle, or within about +-106 degrees when narrow is set. */
s32 spark_debris_spawn(Object *parent, s32 *pos, u16 *rot, s32 narrow, s32 kind) {
    Object *obj;
    s16 *turn;
    s32 *speed;
    s32 *words;
    s32 t0, t1, t2;
    s32 angle;
    u32 sincos;
    u16 roll;
    register s16 cosv asm("$6"); /* the original keeps it in a2 */
    s16 neg_sin;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *)get_obj_list_actors_tail(), (Node *)obj);
    obj->x = pos[0];
    obj->y = pos[1];
    obj->z = pos[2];
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    roll = rot[2];
    obj->handlers[1].fn = (ObjHandlerFn)obj_fall_step;
    obj->handlers[3].fn = (ObjHandlerFn)spark_add_chain0;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].fn = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->callback = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->damage = kind;
    obj->accel_y = 0x800;
    obj->roll = roll;

    if (narrow == 0) {
        angle = rand_a_next();
    } else {
        angle = rand_a_next() * 0x8B4 / 4096 - 0x4B4;
    }
    turn = scratch_alloc(0x20);
    speed = scratch_alloc(0x10);
    sincos = rcossin_tbl[angle & 0xFFF];
    turn[1] = 0;
    turn[3] = 0;
    turn[4] = 0x1000;
    turn[5] = 0;
    turn[7] = 0;
    cosv = sincos >> 16;
    neg_sin = -sincos;
    turn[0] = cosv;
    turn[8] = cosv;
    turn[2] = sincos;
    turn[6] = neg_sin;
    words = (s32 *)turn;
    mul_matrix(&parent->vars, turn, words);
    gte_set_R012(t0, t1, t2, words[0], words[1], words[2]);
    gte_set_R34(t0, t1, words[3], words[4]);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    speed[0] = 0;
    speed[1] = 0;
    speed[2] = 3;
    vec_rotate_rt_raw(speed, &obj->vx);
    scratch_top -= 0x30;
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    return 1;
}
