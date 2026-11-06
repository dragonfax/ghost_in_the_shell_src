/* semi_truck_mech_parts: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

/* Calls msg_show_slot(2, 0x78), then mission_timer_set with the address 0x708 past the mission_timer_get result. */
void mission_timer_extend(void) {
    msg_show_slot(2, 0x78);
    mission_timer_set(mission_timer_get() + 0x708);
}

void obj_sound_start(Object *obj, s32 id, s32 volume) {
    s32 handle;

    handle = sound_start(id, volume, 0, 0);
    if (handle != 0) {
        sound_attach(handle, &obj->x, NULL);
    }
}

extern Rec8011EB0C spin_fx_table[3];
extern GunSetup spin_fx_gun_setups[2];
void obj_spin_fx(Object *obj, s32 arg1) {
    SVECTOR off;
    SVECTOR rot;
    s32 tgt[3];
    s32 pos[3];
    Rec8011EB0C *r;
    s32 n;
    u16 t;

    t = obj->vars.part.unk_280;
    n = (s16)((s16)t / 80);
    r = &spin_fx_table[n % 3];
    vec_from_polar(&off, r->id, obj->yaw + arg1 * r->mul);
    pos[0] = obj->vars.part.unk_254;
    pos[1] = obj->vars.part.unk_258;
    pos[2] = obj->vars.words[5];
    pos[0] += off.vx;
    pos[1] += off.vy + r->y;
    pos[2] += off.vz;
    rot.vx = 0;
    rot.vy = obj->yaw;
    rot.vz = 0;
    tgt[0] = obj->vx >> 12;
    tgt[1] = obj->vy >> 12;
    tgt[2] = obj->vz >> 12;
    sound_play_at_units(SND_ENEMY_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    shot_spawn_target(pos, (u16 *)&rot, tgt, 2, (s32)spin_fx_gun_setups);
}

void obj_spin_fx(Object *obj, s32 dir);
void obj_fx_pingpong(Object *obj) {
    s16 unk_280 = ((s16 *)obj->vars.words)[0x1C]; /* 0x280 */

    if ((unk_280 / 40) & 1) {
        obj_spin_fx(obj, 1);
    } else {
        obj_spin_fx(obj, -1);
    }
}

extern s32 part_loop_sound_handle;

void obj_loop_sound_start_global(Object *obj) {
    s32 temp_v0;

    if (part_loop_sound_handle == 0) {
        temp_v0 = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x46, 0, 0);
        part_loop_sound_handle = temp_v0;
        if (temp_v0 != 0) {
            sound_attach(temp_v0, &obj->x, NULL);
        }
    }
}

extern s32 part_loop_sound_handle;

void part_sound_stop(Object *unused) {
    if (part_loop_sound_handle != 0) {
        sound_stop(part_loop_sound_handle);
        part_loop_sound_handle = 0;
    }
}

void part_spawn_shot(s32 id, s32 step) {
    Object *obj = (Object *)id;
    Quad pos;
    s32 target[3];
    SVECTOR offset;
    s16 rot[3];
    s32 y;

    vec_from_polar(&offset, 0x11A, obj->vars.turn.yaw + step * 0xFA);
    rot[0] = -0x40;
    rot[1] = obj->vars.turn.yaw + 0x800;
    rot[2] = 0;
    pos = *(Quad *)&obj->vars.part.unk_254;
    pos.w[0] -= offset.vx;
    y = pos.w[1] - 0x87;
    pos.w[1] = y - offset.vy;
    pos.w[2] -= offset.vz;
    target[0] = obj->vx >> 12;
    target[1] = obj->vy >> 12;
    target[2] = obj->vz >> 12;
    shot_spawn_target(pos.w, (u16 *)rot, target, 1, 0x80001);
}

void part_spawn_shot(s32 id, s32 step);
void part_fire_pair(s32 id) {
    part_spawn_shot(id, 1);
    part_spawn_shot(id, -1);
}

/* Per-frame update for a child of a parent object (vars.part.parent). The
 * halfword at 0x280 (vars.enemy.shots_left) is a frame counter that wraps
 * every 0x1000 steps. The parent's state (vars.pair.timer at 0x26A) picks
 * the action: 3 = count pulses, 7 = sound and phase work, anything else
 * resets the counter. */
void part_update(Object *obj, ObjHandler *handler) {
    u16 *counter = (u16 *)&obj->vars.enemy.shots_left;
    s16 next;
    s16 phase;
    s16 state;

    next = *counter + 1;
    *counter = next;
    phase = next % 0x1000;
    *counter = phase;

    state = obj->vars.part.parent->vars.pair.timer;
    switch (state) {
    case 7:
        if ((phase >> 5) & 3) {
            part_sound_stop(obj);
            return;
        }
        if (!(phase & 7)) {
            obj_loop_sound_start_global(obj);
            part_fire_pair((s32)obj);
        }
        break;
    case 3:
        if (mission_timer_get() >= 0x12C) {
            if (((s16)*counter % 40) == 0 && !(((s16)*counter / 240) & 1)) {
                obj_fx_pingpong(obj);
            }
        }
        break;
    default:
        *counter = 0;
        break;
    }
}

void flare_part_update(Object *obj, ObjHandler *handler) {
    s16 yaw;
    s32 old_x, old_y, old_z;
    s32 x, y, z;
    s32 type;
    s32 jitter, base_x;

    collider_begin((Collider *)obj->unk_A4);
    yaw = obj->vars.flare.spark_yaw;
    old_x = obj->x;
    old_y = obj->y;
    old_z = obj->z;
    vec_from_polar((SVECTOR *)&obj->vars.flare.spark_offset[0], -0x5B, yaw);
    vec_from_polar((SVECTOR *)&obj->vars.flare.spark_offset[1], 0, yaw);
    vec_from_polar((SVECTOR *)&obj->vars.flare.spark_offset[2], 0, yaw);
    obj->vars.flare.spark_offset[2].vy += 0x60;
    obj->vars.flare.pose_angle += 0x101;
    obj->x = (obj->vars.flare.spark_offset[1].vx + obj->vars.flare.pos[0]) << 12;
    obj->y = (obj->vars.flare.spark_offset[1].vy + obj->vars.flare.pos[1]) << 12;
    obj->z = (obj->vars.flare.spark_offset[1].vz + obj->vars.flare.pos[2]) << 12;
    obj->pitch = 0;
    obj->roll = 0;
    obj->yaw = obj->vars.flare.spark_yaw;
    obj->vx = obj->x - old_x;
    obj->vy = obj->y - old_y;
    obj->vz = obj->z - old_z;
    obj->move_delta[0] = obj->vx >> 12;
    obj->move_delta[1] = obj->vy >> 12;
    obj->move_delta[2] = obj->vz >> 12;
    if (obj->vars.flare.kind == 3) {
        if (obj->vars.flare.parent->vars.part.unk_278 == 1 && !(obj->vars.flare.pose_angle & 7)) {
            x = obj->vars.flare.pos[0];
            y = obj->vars.flare.pos[1];
            z = obj->vars.flare.pos[2];
            jitter = rand_a_next();
            base_x = x - 0x100;
            x = base_x + jitter / 8;
            y -= rand_a_next() / 8;
            z += rand_a_next() / 8;
            type = ((rand_a_next() & 1) == 0) * 2;
            if (!((obj->vars.flare.pose_angle >> 3) & 1)) {
                spawn_effect(x, y, z, (type + 0x7F00) | 0x80000000);
            } else {
                spawn_effect(x, y, z, type | 0x80000000);
            }
        }
        part_sound_stop(obj);
    }
}

extern s16 part_hit_weights[8];
void part_damage_phase2(Object *obj, ObjHandler *handler) {
    Object *mirror = obj->vars.part.parent->vars.part.mirror;
    Object *parent;
    s16 raw;
    s32 factor;
    s32 delta;
    s32 kind;
    s16 step;
    s16 frame;
    s32 base;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    if (obj->hit_cooldown != 0) {
        obj->hit_cooldown += 0xFF;
    }
    raw = obj_hit_damage(obj->index);
    factor = obj_hit_mask_avg(obj_hit_type(obj->index) & 0xFF, part_hit_weights);
    if (obj->vars.part.kind == 0) {
        factor = 0;
    }
    delta = (factor * raw) / 4096;
    if ((s16)delta != 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        obj->health -= delta;
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
    parent = obj->vars.part.parent;
    base = ((s32 *)parent->asset)[1];
    kind = obj->vars.part.kind;
    step = 2;
    if (kind == 1) {
        step = 1;
    }
    frame = base + step;
    if (kind != 3 && parent->vars.part.unk_268 >= 0) {
        obj_pose_draw(obj, frame);
    }
    mirror->hit = obj->hit;
    mirror->health = obj->health;
}

/* Draws the part while its parent's unk_278 is set: a spark at each of three offsets from its base
 * (tinted while hit) and the next pchr slot posed through bones 9 and 10. */
void part_draw_sparks(Object *obj, ObjHandler *handler) {
    s32 x, y, z;
    s32 model;
    s32 colour;
    s32 value;
    s32 *poses;
    s16 *bone_pos;
    s16 *bone_rot;
    s16 angle;

    if (obj->vars.part.parent->vars.part.unk_278 != 0) {
        x = obj->vars.flare.pos[0];
        y = obj->vars.flare.pos[1];
        z = obj->vars.flare.pos[2];
        model = model_slot_pchr(*(s32 *)obj->vars.flare.parent->asset);
        if (obj->hit > 0) {
            colour = 0x60C0FF;
        } else {
            colour = 0;
            colour = 0;
        }
        value = model + 10;
        spark_add(x + obj->vars.flare.spark_offset[2].vx, y + obj->vars.flare.spark_offset[2].vy,
                  z + obj->vars.flare.spark_offset[2].vz, obj->vars.flare.spark_yaw, 0, 0, value, colour);
        bone_pos = scratch_alloc(16);
        bone_rot = scratch_alloc(8);
        value = pchr_copy_slot(model + 1);
        poses = pchr_poses_build(value);
        pchr_table[value & 0x7FF].unk_0C = poses;
        angle = obj->vars.flare.pose_angle;
        bone_rot[1] = 0;
        bone_rot[2] = 0;
        bone_rot[0] = angle;
        bone_pos[0] = 0;
        bone_pos[1] = -0x42;
        bone_pos[2] = 0x152;
        pose_rotate_range(poses, 9, 1, bone_pos, bone_rot);
        bone_pos[0] = 0;
        bone_pos[1] = -0x42;
        bone_pos[2] = -0x64;
        pose_rotate_range(poses, 10, 1, bone_pos, bone_rot);
        spark_add(x + obj->vars.flare.spark_offset[1].vx, y + obj->vars.flare.spark_offset[1].vy,
                  z + obj->vars.flare.spark_offset[1].vz, obj->vars.flare.spark_yaw, 0, 0, value, colour);
        value = model;
        spark_add(x + obj->vars.flare.spark_offset[0].vx, y + obj->vars.flare.spark_offset[0].vy,
                  z + obj->vars.flare.spark_offset[0].vz, obj->vars.flare.spark_yaw, 0, 0, value, colour);
        scratch_top -= 0x18;
        if (obj->hit != 0) {
            obj->hit = -1;
        }
    }
}

void obj_set_hit_reaction(Object *obj, s32 flag);
void part_set_mode(Object *obj, s32 mode) {
    ((s16 *)obj->vars.words)[0x1B] = mode;
    switch (mode) {
    case 1:
        obj_set_hit_reaction(obj, 1);
        break;
    case 0:
    case 3:
        obj_set_hit_reaction(obj, 0);
        break;
    }
}

void flare_part_update(Object *obj, ObjHandler *handler);
void part_draw_sparks(Object *obj, ObjHandler *handler);
void obj_set_extents_from_part(Object *obj, s32 part, s32 part_arg);
/* Spawns an object for the given parent: sets up its four handlers, its asset and its timers. */
Object *part_spawn(Object *parent) {
    Object *obj;
    Object *result;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
        obj->asset = semi_truck_mech_asset;
        obj->handlers[0].fn = part_update;
        obj->handlers[1].fn = flare_part_update;
        obj->handlers[2].fn = part_damage_phase2;
        obj->handlers[3].fn = part_draw_sparks;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->hit_cooldown_max = 0x30;
        obj->vars.part.parent = parent;
        obj->vars.part.unk_27C = 0;
        obj->vars.part.unk_280 = 0;
        obj_init_common(obj, 0x20);
        obj_hit_set_unk08((s32) obj->index, -1);
        obj_hit_set_unk06((s32) obj->index, 1);
        obj_set_extents_from_part(obj, ((s32 *) parent->asset)[1] + 2, 0x1000);
        obj_set_hit_reaction(obj, 0);
        part_loop_sound_handle = 0;
        obj->health = 0x1B58;
        obj_hit_flag_set((s32) obj->index, 0x80);
        result = obj;
    } else {
        result = NULL;
    }
    return result;
}

/* Debris of a destroyed enemy part: 10 pieces, each a velocity (x, y, z) and a keyframe list (hold the
   value for 48 frames, then end); pieces 6-10 reuse pieces 1-5's velocities. */
extern SVECTOR enemy_part_vel_up;
extern SVECTOR enemy_part_vel_forward;
extern SVECTOR enemy_part_vel_left;
extern SVECTOR enemy_part_vel_right;
extern SVECTOR enemy_part_vel_high;
extern Keyframe enemy_part_keys_10[], enemy_part_keys_11[], enemy_part_keys_12[], enemy_part_keys_13[], enemy_part_keys_14[];
extern Keyframe enemy_part_keys_20[], enemy_part_keys_21[], enemy_part_keys_22[], enemy_part_keys_23[], enemy_part_keys_24[];
Object * enemy_part_child_spawn(Object *parent);
void fx_spawn_unit_scale(s32 a, s32 b, s32 c, s32 d, s32 e, s16 f);
void enemy_part_phase0(Object *self, ObjHandler *handler) {
    EnemyPartObj *obj = (EnemyPartObj *)self;
    s32 pos[3];
    u16 rot[3];
    s16 vel[3];

    if (obj->state == 1) {
        pos[0] = obj->pos[0] >> 12;
        pos[1] = obj->pos[1] >> 12;
        pos[2] = obj->pos[2] >> 12;
        rot[0] = obj->rot[0];
        rot[1] = obj->rot[1];
        rot[2] = obj->rot[2];
        obj->anim = 6;
        enemy_part_child_spawn(self);
        vel[0] = 0;
        vel[1] = 0x1000;
        vel[2] = 0;
        pos[2] -= 0x221;
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_up, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_10, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_forward, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_11, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_left, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_12, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_right, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_13, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_high, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_14, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_up, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_20, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_forward, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_21, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_left, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_22, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_right, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_23, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_part_vel_high, (s32)vel, model_slot_pchr(*obj->asset), (s32)enemy_part_keys_24, 0x1000);
        obj->state = 2;
    }
}

/* Swings the part around its pivot by `angle`, moves it to the arm's end
   (keeping the step in unk_238) and, for kind 3 while the parent's unk_278
   is 1, sprays an effect near the pivot every 8 frames. */
void enemy_arm_update(Object *obj, ObjHandler *handler) {
    SwingArmVars *v = (SwingArmVars *)&obj->vars;
    s32 x, y, z;
    s32 type, rnd, left;
    s16 angle;
    s32 old_x, old_y, old_z;

    collider_begin((Collider *)obj->unk_A4);
    angle = v->angle;
    old_x = obj->x >> 12;
    old_y = obj->y >> 12;
    old_z = obj->z >> 12;
    vec_from_polar(&v->arm0, 0x19, angle);
    vec_from_polar(&v->arm1, 0x23A, angle);
    vec_from_polar(&v->arm2, 0x23A, angle);
    obj->pitch = 0;
    obj->roll = 0;
    v->arm2.vy += 0x60;
    v->timer += 0x101;
    obj->x = (v->arm1.vx + v->pivot[0]) << 12;
    obj->y = (v->arm1.vy + v->pivot[1]) << 12;
    obj->z = (v->arm1.vz + v->pivot[2]) << 12;
    obj->move_delta[0] = (obj->x >> 12) - old_x;
    obj->move_delta[1] = (obj->y >> 12) - old_y;
    obj->move_delta[2] = (obj->z >> 12) - old_z;
    obj->yaw = v->angle;
    if (v->kind == 3 && v->parent->vars.part.unk_278 == 1 && !(v->timer & 7)) {
        x = v->pivot[0];
        y = v->pivot[1];
        z = v->pivot[2];
        rnd = rand_a_next();
        left = x - 0x100;
        x = left + rnd / 8;
        y -= rand_a_next() / 16;
        z += rand_a_next() / 4;
        type = ((rand_a_next() & 1) == 0) * 2;
        if (!((v->timer >> 3) & 1)) {
            spawn_effect(x, y, z, (type + 0x7F00) | 0x80000000);
        } else {
            spawn_effect(x, y, z, type | 0x80000000);
        }
    }
}

extern s16 D_8011EBAC[];
s32 obj_hit_mask_avg(s32 mask, s16 *values);
void part_damage_update(Object *obj, ObjHandler *handler) {
    Object *hit = obj->vars.part.parent->vars.part.body;
    s32 raw;
    s32 factor;
    s32 delta;
    s32 mode;
    s16 a1;

    if (hit->hit < 0) {
        hit->hit = 0;
    }
    if (hit->hit_cooldown != 0) {
        hit->hit_cooldown += 0xFF;
    }

    /* called as returning int here: the result is narrowed where it's used, not after the call */
    raw = ((s32 (*)(s32))obj_hit_damage)(obj->index);
    factor = obj_hit_mask_avg(obj_hit_type(obj->index) & 0xFF, D_8011EBAC);
    if ((u16)obj->vars.part.kind < 2) {
        factor = 0;
    }
    delta = (factor * (s16)raw) / 4096;
    if ((s16)delta != 0) {
        if (hit->hit == 0) {
            hit->hit = 1;
        }
        hit->health -= delta;
        if (hit->hit_cooldown == 0) {
            hit->hit_cooldown = hit->hit_cooldown_max;
        }
    }

    obj_hit_clear(obj->index);
    mode = obj->vars.part.kind;
    if (mode == 2) {
        a1 = *(s32 *)((u8 *)obj->vars.part.parent->asset + 4) + 4;
    } else {
        a1 = *(s32 *)((u8 *)obj->vars.part.parent->asset + 4) + 3;
    }
    if (mode != 3 && obj->vars.part.parent->vars.part.unk_268 >= 0) {
        obj_pose_draw(obj, a1);
    }
}

extern ModelPartList model_part_lists[];
static inline void spark_add0(s32 x, s32 y, s32 z, s32 ry, s32 value, s32 colour) {
    SparkList *list = &spark_list;
    s32 n = SPARK_COUNT;
    SparkRec *s;
    u8 *tail;
    SparkList *head;

    if (n < 0xFF) {
        s = &list->items[n];
        head = list;
        FAKE_OPAQUE(head);
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
        s->pitch = 0;
        s->roll = 0;
    }
}
void spark_part_draw(Object *obj, ObjHandler *handler) {
    s32 model, colour, value;
    s32 px, py, pz;
    s32 *first;
    s16 *pos, *rot;

    if (obj->vars.spark_part.parent->vars.part.unk_278 != 0) {
        px = obj->vars.spark_part.x;
        py = obj->vars.spark_part.y;
        pz = obj->vars.spark_part.z;
        model = model_slot_pchr(*(s32 *)obj->vars.spark_part.parent->asset);
        if (obj->hit > 0) {
            colour = 0x60C0FF;
        } else {
            colour = 0;
            FAKE_OPAQUE(colour);
        }
        value = model + 0xB;
        spark_add0(px + obj->vars.spark_part.spark_a[0], py + obj->vars.spark_part.spark_a[1],
                   pz + obj->vars.spark_part.spark_a[2], obj->vars.spark_part.spark_yaw, value, colour);
        pos = scratch_alloc(0x10);
        rot = scratch_alloc(8);
        value = pchr_copy_slot(model + 3);
        first = pchr_poses_build(value);
        model_part_lists[value & 0x7FF].first = first;
        rot[0] = obj->vars.spark_part.pose_rot;
        rot[1] = 0;
        rot[2] = 0;
        pos[0] = 0;
        pos[1] = -0x42;
        pos[2] = 0x15A;
        pose_rotate_range(first, 6, 1, pos, rot);
        pos[0] = 0;
        pos[1] = -0x42;
        pos[2] = 0xB9;
        pose_rotate_range(first, 5, 1, pos, rot);
        spark_add0(px + obj->vars.spark_part.spark_b[0], py + obj->vars.spark_part.spark_b[1],
                   pz + obj->vars.spark_part.spark_b[2], obj->vars.spark_part.spark_yaw, value, colour);
        value = obj->vars.spark_part.model_offset + model;
        spark_add0(px + obj->vars.spark_part.spark_c[0], py + obj->vars.spark_part.spark_c[1],
                   pz + obj->vars.spark_part.spark_c[2], obj->vars.spark_part.spark_yaw, value, colour);
        scratch_top -= 0x18;
        if (obj->hit != 0) {
            obj->hit = -1;
        }
    }
}

/* Sets the enemy's state (mode 0..3) and reacts to it. The halfword at
 * 0x27E is the top half of enemy.shot_timer; the halfword at 0x280 is the
 * low half of enemy.shots_left. */
void enemy_set_mode(Object *obj, s32 mode) {
    *((s16 *)&obj->vars.enemy.shot_timer + 1) = mode;
    switch (mode) {
    case 1:
        obj_set_hit_reaction(obj, 0);
        if (*(s16 *)&obj->vars.enemy.shots_left == 0) {
            *(s16 *)&obj->vars.enemy.shots_left = 1;
        }
        return;
    case 2:
        obj_set_hit_reaction(obj, 1);
        obj_hit_set_unk08(obj->index, -1);
        return;
    case 3:
    case 0:
        obj_set_hit_reaction(obj, 0);
        break;
    }
}

void enemy_part_phase0(Object *self, ObjHandler *handler);
void enemy_arm_update(Object *obj, ObjHandler *handler);
void spark_part_draw(Object *obj, ObjHandler *handler);
/* Spawns an s06 part of the enemy `parent`: sets up its handlers and enemy state. */
Object *enemy_part_spawn(Object *parent) {
    Object *part;

    part = obj_new();
    if (part == NULL) {
        return NULL;
    }
    list_insert_before((Node *)get_obj_list_actors_tail(), &part->node);
    part->asset = semi_truck_mech_asset;
    part->handlers[0].fn = enemy_part_phase0;
    part->handlers[1].fn = enemy_arm_update;
    part->handlers[2].fn = part_damage_update;
    part->handlers[3].fn = spark_part_draw;
    part->handlers[0].unk_11 = 0;
    part->handlers[0].state = 0;
    part->handlers[1].unk_11 = 0;
    part->handlers[1].state = 0;
    part->handlers[2].unk_11 = 0;
    part->handlers[2].state = 0;
    part->handlers[3].unk_11 = 0;
    part->handlers[3].state = 0;
    part->hit_cooldown_max = 0x30;
    part->vars.part.parent = parent;
    part->vars.part.unk_27C = 0;
    obj_init_common(part, 0x20);
    obj_set_extents_from_part(part, ((s32 *)parent->asset)[1] + 3, 0x1000);
    obj_hit_set_unk08(part->index, 0);
    obj_hit_set_unk06(part->index, 0);
    obj_set_hit_reaction(part, 0);
    part->vars.part.unk_282 = 2;
    part->vars.part.unk_280 = 0;
    part->health = 0xDAC;
    obj_hit_flag_set(part->index, 0x80);
    return part;
}

/* Debris of a destroyed enemy child: 10 pieces, each a velocity (x, y, z) and a keyframe list (hold the
   value for 48 frames, then end); pieces 6-10 reuse pieces 1-5's velocities. */
extern SVECTOR enemy_child_vel_up;
extern SVECTOR enemy_child_vel_forward;
extern SVECTOR enemy_child_vel_left;
extern SVECTOR enemy_child_vel_right;
extern SVECTOR enemy_child_vel_high;
extern Keyframe enemy_child_keys_18[], enemy_child_keys_19[], enemy_child_keys_1a[], enemy_child_keys_1b[], enemy_child_keys_1c[];
extern Keyframe enemy_child_keys_28[], enemy_child_keys_29[], enemy_child_keys_2a[], enemy_child_keys_2b[], enemy_child_keys_2c[];
Object * enemy_child_part_spawn(); /* the caller relies on a0 still holding obj */
void enemy_child_phase0(Object *obj, ObjHandler *h) {
    s32 pos[3];
    s16 rot_in[3];
    s16 rot[3];
    u16 *aim = (u16 *)&obj->vars.enemy_child.unk_25C;

    if (obj->vars.enemy_child.unk_280 == 1) {
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot_in[0] = aim[0];
        rot_in[1] = aim[1];
        rot_in[2] = aim[2];
        obj->vars.enemy_child.unused_282 = 7;
        enemy_child_part_spawn();
        rot[0] = 0;
        rot[1] = 0x1000;
        rot[2] = 0;
        pos[2] += 0x222;
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_up, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_18, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_forward, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_19, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_left, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_1a, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_right, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_1b, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_high, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_1c, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_up, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_28, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_forward, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_29, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_left, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_2a, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_right, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_2b, 0x1000);
        fx_spawn_unit_scale((s32)pos, (s32)&enemy_child_vel_high, (s32)rot, model_slot_pchr(*(s32 *)obj->asset), (s32)enemy_child_keys_2c, 0x1000);
        obj->vars.enemy_child.unk_280 = 2;
    }
}

void swing_arm_update(Object *obj, ObjHandler *handler) {
    SwingArmVars *v = (SwingArmVars *)&obj->vars;
    s32 x, y, z;
    s32 type, rnd, left;
    s16 angle;
    s32 old_x, old_y, old_z;

    if ((((u32)(v->mode - 3) < 2U) || v->mode == 5) && !(v->timer & 7)) {
        x = v->pivot[0];
        y = v->pivot[1];
        z = v->pivot[2];
        rnd = rand_a_next();
        left = x - 0x100;
        x = left + rnd / 8;
        y -= rand_a_next() / 16;
        z += rand_a_next() / 4;
        type = ((rand_a_next() & 1) == 0) * 2;
        if (!((v->timer >> 3) & 1)) {
            spawn_effect(x, y, z, (type + 0x7F00) | 0x80000000);
        } else {
            spawn_effect(x, y, z, type | 0x80000000);
        }
    }
    v = (SwingArmVars *)&obj->vars;
    collider_begin((Collider *)obj->unk_A4);
    angle = v->angle;
    old_x = obj->x >> 12;
    old_y = obj->y >> 12;
    old_z = obj->z >> 12;
    vec_from_polar(&v->arm0, 0x492, angle);
    vec_from_polar(&v->arm1, 0x270, angle);
    vec_from_polar(&v->arm2, 0x270, angle);
    obj->pitch = 0;
    obj->roll = 0;
    v->arm2.vy += 0x60;
    v->timer += 0x101;
    obj->x = (v->arm1.vx + v->pivot[0]) << 12;
    obj->y = (v->arm1.vy + v->pivot[1]) << 12;
    obj->z = (v->arm1.vz + v->pivot[2]) << 12;
    obj->move_delta[0] = (obj->x >> 12) - old_x;
    obj->move_delta[1] = (obj->y >> 12) - old_y;
    obj->move_delta[2] = (obj->z >> 12) - old_z;
    obj->yaw = v->angle;
}

extern s16 enemy_child_hit_factors[];
/* Part that takes no damage: the scaled damage is only left in a2 for obj_hit_clear,
   which ignores it (a1 is stale). Matching needs the hard-register locals and the barrier. */
void enemy_child_phase2(Object *obj, ObjHandler *handler) {
    s32 raw;
    register s32 factor __asm__("$4");
    register s32 scaled __asm__("$6");
    s32 pose;
    register s32 stale __asm__("$5");

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    if (obj->hit_cooldown != 0) {
        obj->hit_cooldown += 0xFF;
    }
    /* called as returning int: the result is narrowed where it's used */
    raw = ((s32 (*)(s32))obj_hit_damage)(obj->index);
    factor = obj_hit_mask_avg(obj_hit_type(obj->index), enemy_child_hit_factors);
    if (obj->vars.part.kind == 0) {
        factor = 0;
    }
    {
        register s32 damage __asm__("$2") = (s16)raw;
        scaled = factor * damage;
    }
    __asm__ __volatile__("");
    ((void (*)(s32, s32, s32))obj_hit_clear)(obj->index, stale, scaled);
    pose = ((s32 *)obj->vars.part.parent->asset)[1] + 5;
    if (obj->vars.part.kind != 3) {
        obj_pose_draw(obj, pose);
    }
}

static inline void spark_add_list(s32 x, s32 y, s32 z, s32 ry, s32 value, s32 colour, SparkList *list) {
    u8 *tail;
    SparkRec *s;
    s32 n = spark_count;
    if (n >= 0xFF) {
        return;
    }
    s = &list->items[n];
    n++;
    spark_count = n;
    FAKE_OPAQUE(list);
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
    s->pitch = 0;
    s->roll = 0;
}
void enemy_child_draw(Object *obj, ObjHandler *handler) {
    s32 slot;
    s32 mode = ((SparkEmitVars *)&obj->vars)->mode;
    s32 bx = ((SparkEmitVars *)&obj->vars)->base_x;
    s32 by = ((SparkEmitVars *)&obj->vars)->base_y;
    s32 bz = ((SparkEmitVars *)&obj->vars)->base_z;
    s32 colour;
    s32 value;
    s32 *first;
    SVECTOR *pos;
    SVECTOR *rot;

    slot = model_slot_pchr(*(s32 *)((SparkEmitVars *)&obj->vars)->parent->asset);
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
        colour = 0;
        FAKE_OPAQUE(colour);
    }
    value = slot + 0xC;
    /* x as its own set-once local: sched1 then loads its offset before spark_count, as the original does */
    {
        s32 x1 = bx + ((SparkEmitVars *)&obj->vars)->off1[0];
        spark_add_list(x1, by + ((SparkEmitVars *)&obj->vars)->off1[1], bz + ((SparkEmitVars *)&obj->vars)->off1[2], ((SparkEmitVars *)&obj->vars)->spark_rot, value, colour, &spark_list);
    }
    pos = scratch_alloc(0x10);
    rot = scratch_alloc(8);
    value = pchr_copy_slot(slot + 5);
    first = pchr_poses_build(value);
    model_part_lists[value & 0x7FF].first = first;
    if ((u32)(mode - 4) < 2) {
        rot->vx = 0;
        rot->vy = 0;
        rot->vz = 0;
    } else {
        u16 pose_x = ((SparkEmitVars *)&obj->vars)->pose_x;

        rot->vy = 0;
        rot->vz = 0;
        rot->vx = pose_x;
    }
    pos->vx = 0;
    pos->vy = -0x42;
    pos->vz = -0x17E;
    pose_rotate_range(first, 0xA, 1, pos, rot);
    pos->vx = 0;
    pos->vy = -0x42;
    pos->vz = 0x21B;
    pose_rotate_range(first, 2, 1, pos, rot);
    pos->vx = 0;
    pos->vy = -0x42;
    pos->vz = 0x17A;
    pose_rotate_range(first, 3, 1, pos, rot);
    {
        s32 x2 = bx + ((SparkEmitVars *)&obj->vars)->off2[0];
        spark_add_list(x2, by + ((SparkEmitVars *)&obj->vars)->off2[1], bz + ((SparkEmitVars *)&obj->vars)->off2[2], ((SparkEmitVars *)&obj->vars)->spark_rot, value, colour, &spark_list);
    }
    value = ((SparkEmitVars *)&obj->vars)->model_offset + slot;
    spark_add_list(bx + ((SparkEmitVars *)&obj->vars)->off3[0], by + ((SparkEmitVars *)&obj->vars)->off3[1], bz + ((SparkEmitVars *)&obj->vars)->off3[2], ((SparkEmitVars *)&obj->vars)->spark_rot, value, colour, &spark_list);
    scratch_top -= 0x18;
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

void enemy_set_state(Object *obj, s32 state) {
    ShotHalves *h = (ShotHalves *)&obj->vars.enemy.shot_timer;

    h->state = state;
    switch (state) {
    case 1:
        obj_set_hit_reaction(obj, 0);
        if (h->shots_left == 0) {
            h->shots_left = 1;
        }
        return;
    case 3:
        h->shots_left = 3;
        obj_set_hit_reaction(obj, 0);
        return;
    case 0:
        obj_set_hit_reaction(obj, 0);
        return;
    }
}

void enemy_child_phase0(Object *obj, ObjHandler *h);
void swing_arm_update(Object *obj, ObjHandler *handler);
void enemy_child_phase2(Object *obj, ObjHandler *handler);
void enemy_child_draw(Object *obj, ObjHandler *handler);
/* Spawns the enemy child of `parent` (vars.part.parent); NULL if no free slot. */
Object *enemy_child_spawn(Object *parent) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return NULL;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj->asset = semi_truck_mech_asset;
    obj->handlers[0].fn = enemy_child_phase0;
    obj->handlers[1].fn = swing_arm_update;
    obj->handlers[2].fn = enemy_child_phase2;
    obj->handlers[3].fn = enemy_child_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->hit_cooldown_max = 0x30;
    obj->vars.part.parent = parent;
    obj->vars.enemy_child.unused_27C = 0;
    obj_init_common(obj, 0x20);
    obj_hit_set_unk08(obj->index, 0);
    obj_hit_set_unk06(obj->index, 0);
    obj_set_extents_from_part(obj, ((s32 *)parent->asset)[1] + 5, 0x1000);
    obj_set_hit_reaction(obj, 0);
    obj->health = 0xDAC;
    obj->vars.enemy_child.unk_280 = 0;
    obj->vars.enemy_child.unused_282 = 4;
    obj_hit_flag_set(obj->index, 0x80);
    return obj;
}

/* Advances the s32 at 0x20 (unk_1C.unk_04) by 2. */
void script_cursor_advance_alt(Object *obj) {
    obj->script.pc++;
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void script_jump_if_near(Object *obj) {
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

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is at least
 * `threshold` from the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void script_jump_if_far(Object *obj) {
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
    if (dist < threshold) {
        return;
    }
    obj->script.pc = ((s16 **)obj->script.data)[index];
}

/* Script command: reads a turn step and a target index from the script cursor, turns the yaw toward the
 * player by at most |step|; once the yaw is within the step of the target, jumps to the type table's entry. */
void script_turn_to_player(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 raw_step;
    s16 step;
    s32 target;
    s32 *player;
    s32 target_yaw;
    s32 yaw;
    s32 diff;

    obj->script.pc = cursor + 1;
    raw_step = cursor[0];
    obj->script.pc = cursor + 2;
    target = cursor[1];
    step = ABS(raw_step);
    player = player_position();
    target_yaw = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    yaw = obj->yaw;
    diff = angle_approach(yaw, target_yaw, step) - yaw;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff < step) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}


void script_jump_if_op_eq(Object *obj) {
    s16 op = obj_read_s16(obj);
    s16 target = obj_read_s16(obj);

    if (op == obj->script_flag) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}


extern s16 script_index[2];
/* Reads the next halfword of the object's stream (the pointer at 0x20) into script_index. */
void stream_read_halfword(Object *obj) {
    u16 *stream = (u16 *)obj->script.pc;

    obj->script.pc = stream + 1;
    script_index[0] = *stream;
}

/* Loads the word of the object's table (the pointer at 0x1C) selected by script_index into the stream slot (0x20). */
void script_load_table_entry(Object *obj) {
    obj->script.pc = ((s16 **)obj->script.data)[script_index[0]];
}

extern Keyframe obj_trail_keys[8];
void fx_spawn(s32 owner, FxPosition *src);
void obj_trail_emit(Object *obj) {
    SVECTOR offset;
    FxPosition pos;
    s16 zero_a[3];
    s16 zero_b[3];
    s16 *stream;
    s32 angle;
    s32 x;
    s32 y;
    s32 z;

    x = obj->x >> 12;
    stream = obj->script.pc;
    z = obj->z >> 12;
    obj->script.pc = stream + 1;
    angle = *stream;
    vec_from_polar(&offset, 0x218, obj->yaw + angle);
    x += offset.vx;
    z += offset.vz;
    y = obj->vars.part.parent->y >> 12;
    particle_spawn_burst_masked(x, y, z, 0, 0xF, 0xF);
    pos.w[0] = x;
    pos.w[1] = y;
    pos.w[2] = z;
    fx_spawn(model_slot_pchr(*(s32 *)obj->asset), &pos);
    zero_a[0] = 0;
    zero_a[1] = 0;
    zero_a[2] = 0;
    zero_b[0] = 0;
    zero_b[1] = 0;
    zero_b[2] = 0;
    fx_spawn_unit_scale((s32)&pos, (s32)zero_a, (s32)zero_b, model_slot_pchr(*(s32 *)obj->asset), (s32)obj_trail_keys, 0x1800);
}

/* Reads a halfword opcode and a halfword operand at pc and advances pc by 4 bytes.
   If the opcode is below bounds->unk_186, pc becomes jump_table[operand]. */
void script_op_jump(ScriptVm *vm) {
    u8 *pc;
    s32 opcode;
    s32 operand;
    ScriptBounds *bounds;

    pc = vm->pc;
    bounds = vm->bounds;
    vm->pc = pc + 2;
    opcode = *(s16 *)pc;
    vm->pc = pc + 4;
    operand = *(s16 *)(pc + 2);
    if (opcode < bounds->unk_186) {
        vm->pc = (u8 *)vm->jump_table[operand];
    }
}

void semi_truck_mech_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

void part_place_on_parent(Object *self) {
    s16 rot[3];
    s32 pos[3];
    s32 kind;
    Object *parent;
    s32 yaw;
    u16 new_yaw;
    Object *link;
    s32 parent_yaw;

    parent = self->vars.part.parent;
    vec_from_polar((SVECTOR *)rot, 0x464, ((s16 *)parent->vars.words)[0xB]);
    self->x = (parent->vars.words[1] + rot[0]) << 12;
    self->y = (parent->vars.words[2] + rot[1] - 0xF0) << 12;
    self->z = (parent->vars.words[3] + rot[2]) << 12;
    pos[0] = self->x >> 12;
    pos[1] = self->y >> 12;
    pos[2] = self->z >> 12;
    rot[0] = self->pitch;
    rot[1] = self->yaw;
    rot[2] = self->roll;
    kind = self->vars.part.parent->vars.part.unk_280;
    if ((u32)(kind - 3) < 2 || kind == 5) {
        yaw = self->yaw;
        parent_yaw = self->vars.part.parent->yaw;
        rot[1] = yaw + (parent_yaw - self->vars.part.parent_yaw);
    } else {
        rot_turn_toward(pos, rot, 0x10, 0x10);
    }
    new_yaw = rot[1];
    link = self->vars.part.parent;
    self->pitch = 0;
    self->roll = 0;
    self->yaw = new_yaw;
    self->vars.part.parent_yaw = link->yaw;
}

/* Reads the asset's first word as an index, maps it to a base (model_slot_pchr) and runs pchr_set_angle_span over
 * 0x81..0xFE from there. The second argument goes through as pchr_set_angle_span's unused parameter. */
void obj_pchr_angle_span(Object *obj, s32 unused) {
    s32 base = model_slot_pchr(*(s32 *)obj->asset);

    pchr_set_angle_span(0x81, 0xFE, unused, base);
}

/* Part step: places itself on its parent, runs the script while the parent
 * lives, and for parent kinds 3-5 spawns a random effect near itself every
 * 8 frames, then turns one way (kinds 3-5) or the other. */
void enemy_part_update(Object *obj, ObjHandler *handler) {
    s16 next; /* frame counter, wraps at 0x1000 */
    s32 kind;
    s32 type;
    s32 x, y, z;

    collider_begin((Collider *)obj->unk_A4);
    next = obj->vars.enemy_child_part.frame_counter + 1;
    kind = obj->vars.part.parent->vars.part.unk_280;
    obj->vars.enemy_child_part.frame_counter = next;
    obj->vars.enemy_child_part.frame_counter = next % 0x1000;
    part_place_on_parent(obj);
    if (obj->vars.part.parent->health > 0) {
        obj_script_step(obj, handler);
    }
    if (kind == 3 || kind == 4 || kind == 5) {
        if (!(obj->vars.enemy_child_part.frame_counter & 7)) {
            x = obj->x >> 12;
            y = obj->y >> 12;
            z = obj->z >> 12;
            x -= 0x80 - rand_a_next() / 16;
            y -= rand_a_next() / 16;
            z -= 0x80 - rand_a_next() / 16;
            type = !(rand_a_next() & 1) << 1;
            if (!((obj->vars.enemy_child_part.frame_counter >> 3) & 1)) {
                spawn_effect(x, y, z, (type + 0x7F00) | 0x80000000);
            } else {
                spawn_effect(x, y, z, type | 0x80000000);
            }
        }
        obj_pchr_angle_span(obj, 0x200);
    } else {
        obj_pchr_angle_span(obj, -0x200);
    }
}

extern s16 part_hit_factors[];
void part_hit_update(Object *obj, ObjHandler *handler) {
    s32 damage;
    s32 scaled;
    s32 flags;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    obj->health = obj->vars.part.parent->health;
    damage = obj_hit_damage(obj->index);
    if (obj->hit_cooldown != 0) {
        obj->hit_cooldown += 0xFF;
    }
    if (damage > 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        scaled = damage * obj_hit_mask_avg(obj_hit_type(obj->index) & 0xFF, part_hit_factors);
        if (scaled < 0) {
            scaled += 0xFFF;
        }
        damage = scaled >> 12;
        obj->vars.part.parent->health -= damage;
        obj->vars.part.parent->hit_from = obj_hit_from(obj->index);
        obj->vars.part.parent->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
    flags = obj->flags;
    if (((u32) flags >> 5) & 1) {
        obj_hit_reaction(obj, 0);
    }
}

/* Runs the object's callback (0x170) if it has one; a callback that returns 0 is cleared.
 * The unused array keeps the 0x30-byte frame of the original (its locals are not recoverable). */
void obj_callback_run(Object *obj, ObjHandler *handler) {
    s32 (*callback)(void);
    s32 unused[6];

    callback = (s32 (*)(void))obj->callback;
    if (callback != NULL && callback() == 0) {
        obj->callback = 0;
    }
}

/* Part handler: starts the hit reaction once the owner dies, runs hit updates
 * until then and the callback after; kind-5 parts free themselves and their owner
 * when they leave the area. */
void part_area_phase0(Object *obj, ObjHandler *handler) {
    Object *owner = obj->vars.part.parent;
    s32 kind = owner->vars.part.unk_280;
    s32 state;
    s32 out_of_area;
    Placement *placement;
    s32 whole_x, whole_y, whole_z;
    s32 alt, flags;

    /* the state copies keep GCC from threading the state tests */
    if (owner->health <= 0) {
        state = handler->state;
        if (state == 0) {
            handler->state = 1;
            obj_set_hit_reaction(obj, 0);
        }
    }
    state = handler->state;
    if (state == 0) {
        part_hit_update(obj, handler);
    }
    if (handler->state != 0) {
        obj_callback_run(obj, handler);
    }
    alt = 0;
    if (kind == 5) {
        whole_x = obj->x >> 12;
        whole_y = obj->y >> 12;
        whole_z = obj->z >> 12;
        placement = obj->placement;
        if (placement != NULL) {
            flags = placement->unk_00[4] & 4;
            alt = flags != 0;
        }
        if (alt != 0) {
            out_of_area = cam_range_check_alt(whole_x, whole_y, whole_z, placement) == 0;
        } else {
            out_of_area = cam_range_check(whole_x, whole_y, whole_z, placement) == 0;
        }
        if (out_of_area != 0) {
            obj_free(obj->vars.part.parent);
            obj_free(obj);
        }
    }
}

static inline void spark_add_list_a0(SparkList *base, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    register SparkList *list asm("$4");
    s32 n;
    SparkRec *s;
    u8 *tail;

    n = spark_count;
    if (n < 0xFF) {
        s = (SparkRec *)(n * sizeof(SparkRec) + (s32)base->items);
        n++;
        __asm__("" : "=r"(list) : "0"(base), "r"(s));
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
/* Draws the object as two spark records (one 0x30 higher, one turned to the parent's yaw), tinted while hit. */
void semi_truck_mech_spark_draw(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 colour;
    s32 value;
    s32 pitch;
    s32 unused[2];
    SparkList *list;

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
    list = &spark_list;
    {
        /* The raised y: loaded into v0, summed into t4 (after the record's other values). */
        register s32 py asm("$2") = pos[1];
        register s32 y asm("$12") = py + 0x30;

        spark_add_list_a0(list, pos[0], y, pos[2], rot[1], rot[0], rot[2], value, colour);
    }
    value = model_slot_pchr(*(s32 *)obj->asset) + 0xFF;
    spark_add_list_a0(list, pos[0], pos[1], pos[2], (u16)obj->vars.part.parent->yaw, rot[0], rot[2], value, colour);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

s32 enemy_timed_spawn(Object *self) {
    s32 pos[3];
    u16 rot[3];
    u8 *obj = (u8 *)self;

    *(s32 *)(obj + 0x100) = 0;
    *(s8 *)(obj + 0x111) = 0;
    *(s16 *)(obj + 0x112) = 0;
    self->vars.enemy_child_part.timer++;
    if (self->vars.enemy_child_part.timer != 0x60) {
        return 1;
    }
    {
        *(s16 *)(((u8 *)self->vars.enemy.mode) + 0x280) = 4;
        pos[0] = self->x >> 12;
        pos[1] = self->y >> 12;
        pos[2] = self->z >> 12;
        rot[0] = *(u16 *)(obj + 0x222);
        rot[1] = *(u16 *)(obj + 0x220);
        rot[2] = *(u16 *)(obj + 0x224);
        object_spawn_at(pos, rot, model_slot_pchr(*(s32 *)self->asset) + 0x9F);
        *(s32 *)(obj + 0x11C) = 0;
        *(s8 *)(obj + 0x12D) = 0;
        *(s16 *)(obj + 0x12E) = 0;
        *(s32 *)(obj + 0x154) = 0;
        *(s8 *)(obj + 0x165) = 0;
        *(s16 *)(obj + 0x166) = 0;
    }
    return 0;
}

extern ScriptCallEntry enemy_part_call_table[10];
extern StateEntry enemy_part_states[7];
extern SoundVolume enemy_part_sound_entry[]; /* obj->unk_19C: sound id, volume */
extern s16 *D_8011F0D8[];
extern s16 *enemy_child_part_jump_table[16];
extern s16 *enemy_child_part_script_table[];
void enemy_part_update(Object *obj, ObjHandler *handler);
void semi_truck_mech_spark_draw(Object *obj);
Object *enemy_child_part_spawn(parent)
    Object *parent; /* K&R: enemy_child_phase0 calls it with no argument, obj still in a0 */
{
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return NULL;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj->handlers[0].fn = (ObjHandlerFn) semi_truck_mech_phase0;
    obj->handlers[1].fn = (ObjHandlerFn) enemy_part_update;
    obj->handlers[2].fn = (ObjHandlerFn) part_area_phase0;
    obj->handlers[3].fn = (ObjHandlerFn) semi_truck_mech_spark_draw;
    obj->asset = semi_truck_mech_asset;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = enemy_part_call_table;
    obj->state_table = enemy_part_states;
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
    obj->sounds = enemy_part_sound_entry;
    obj->script.pc = D_8011F0D8[0];
    obj->script.data = enemy_child_part_jump_table;
    obj->script.unk_0A = 0;
    obj->callback = (s32) &enemy_timed_spawn;
    script_start((Script *) obj, enemy_child_part_script_table[0], (s32) enemy_child_part_script_table);
    obj_init_common(obj, 0x33);
    obj->vars.part.parent_yaw = obj->vars.part.parent->yaw;
    obj->vars.enemy_child_part.frame_counter = 0;
    obj->vars.enemy_child_part.timer = 0;
    obj_set_extents_from_part(obj, ((s32 *) parent->vars.part.parent->asset)[1] + 0x81, 0x1000);
    obj_set_hit_reaction(obj, 1);
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, 3);
    obj_hit_flag_set(obj->index, 0x80);
    part_place_on_parent(obj);
    return obj;
}

void obj_noop_hook(void) {
}

/* Shifts the three words of src by 12 into a scratch vector and passes it to sound_set_pos. */
s32 sound_follow_pos(Vec3 *src, s32 index) {
    Vec3 *scaled = scratch_alloc(0x10);

    scaled->x = src->x << 12;
    scaled->y = src->y << 12;
    scaled->z = src->z << 12;
    sound_set_pos(index, scaled);
    scratch_top -= 0x10;
    return 0;
}

/* Starts the two looping sounds of an object (handles at 0x1C and 0x20);
   a slot that is already playing is left alone. */
void obj_start_loop_sounds(Object *obj) {
    s32 handle;

    if (obj->script.data == NULL) {
        handle = sound_start(0x30A9, 0x46, 0, 0);
        obj->script.data = (void *)handle;
        if (handle != 0) {
            sound_set_flag_bit2(handle, 1);
            sound_attach((s32)obj->script.data, obj, (void (*)())sound_follow_pos);
        }
    }
    if (obj->script.pc == 0) {
        handle = sound_start(0x30A9, 0x46, 0, 0);
        obj->script.pc = (s16 *)handle; /* a sound handle, not a script */
        if (handle != 0) {
            sound_set_flag_bit2(handle, 1);
            sound_attach((s32)obj->script.pc, obj, (void (*)())sound_follow_pos);
        }
    }
}

void sound_handles_stop(SoundHandles *h) {
    if (h->sound_a != 0) {
        sound_stop(h->sound_a);
        h->sound_a = 0;
    }
    if (h->sound_b != 0) {
        sound_stop(h->sound_b);
        h->sound_b = 0;
    }
}

/* Advances one table entry; frees it when cam_range_check rejects its position. */
void fx_entry_update(FxPointEntry *entry) {
    entry->age++;
    if (cam_range_check(entry->x, entry->y, entry->z) == 0) {
        entry->ptr = NULL;
    }
    entry->phase += 8;
}

extern FxTableEntry fx_table[];
void fx_table_update(void) {
    FxTableEntry *entry = fx_table;
    s32 i;

    for (i = 0; i < 0x60; i++, entry++) {
        if (entry->ptr != NULL) {
            fx_entry_update((FxPointEntry *)entry);
        }
    }
}

void fx_entry_proximity(s32 *obj) {
    s32 *player;
    s16 angle;
    s32 radius;
    s32 dist;

    dist = player_dist_sq(obj);
    radius = obj[5];
    radius = radius * radius; /* compares squared distance, as the original does */
    if (dist < radius) {
        player = player_position();
        angle = atan2(obj[2] - player[2], obj[0] - player[0]);
        hit_target_masked(0, 4, angle, 0x10);
    }
}

/* Same code as fx_table_update (s06). */
void sound_pair_run_copy(void) {
    FxTableEntry *entry = fx_table;
    s32 i;

    for (i = 0; i < 0x60; i++, entry++) {
        if (entry->ptr != NULL) {
            fx_entry_proximity((s32 *)entry);
        }
    }
}

/* Draws one fx table entry: a spark record (spark_add with no rotation and
 * colour 0, written out so the model value is allocated first) at its
 * position, then queues the position. */
void fx_spark_spawn(FxTableEntry *entry) {
    s32 unused[8];
    s32 value;
    s32 x, y, z;
    SparkList *list;
    s32 n;
    SparkRec *s;
    u8 *tail;

    value = pool_spawn_scaled(entry->pool_index + 0x1E0, 0x1000, 0x1000, 0x1000);
    list = &spark_list;
    n = SPARK_COUNT;
    x = entry->pos[0];
    y = entry->pos[1];
    z = entry->pos[2];
    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = 0;
        tail = list->tail[0];
        list->tail[0] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        /* the loop raises value's register priority */
        do {
            s->unk_12 = value;
        } while (0);
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
    req_queue_push_vec(entry->pos[0], entry->pos[1], entry->pos[2]);
}

/* Same code as fx_table_update (s06). */
void fx_table_draw(void) {
    FxTableEntry *entry = fx_table;
    s32 i;

    for (i = 0; i < 0x60; i++, entry++) {
        if (entry->ptr != NULL) {
            fx_spark_spawn(entry);
        }
    }
}

/* Returns the first free slot (ptr == NULL) of the 0x60-entry table, or NULL. */
FxTableEntry *fx_table_alloc(void) {
    FxTableEntry *entry = fx_table;
    s32 i;

    for (i = 0; i < 0x60; i++, entry++) {
        if (entry->ptr == NULL) {
            return entry;
        }
    }
    return NULL;
}

void fx_spawn(s32 owner, FxPosition *src) {
    FxEmitter *r = (FxEmitter *)fx_table_alloc();
    if (r != NULL) {
        r->owner = owner;
        r->f18 = 1;
        r->pos = *src;
        r->f10 = 0;
        r->f14 = 0x60;
        r->f1C = 0;
        r->f20 = 0;
        obj_start_loop_sounds((Object *)r); /* starts the sounds at 0x1C/0x20 */
    }
}

void fx_table_clear(void) {
    FxTableEntry *entry = fx_table;
    s32 i = 0x5F;
    do {
        entry->ptr = NULL;
        i -= 1;
        entry++;
    } while (i >= 0);
}

/* Stops the sounds of every live entry, then clears the table. */
void fx_table_stop_all(void) {
    FxTableEntry *entry = fx_table;
    s32 i;

    for (i = 0; i < 0x60; i++, entry++) {
        if (entry->ptr != NULL) {
            sound_handles_stop((SoundHandles *)entry);
        }
    }
    fx_table_clear();
}

s32 keyframe_step(Keyframe **cursor, s32 *tick, u16 *from, u16 *to, s16 *t);
void keyframe_track_step(KeyframeTrack *entry) {
    KeyframeTrackFields *e = (KeyframeTrackFields *)entry;

    e->pos[0] += e->vel[0];
    e->pos[1] += e->vel[1];
    e->pos[2] += e->vel[2];
    e->vel[0] += e->accel[0];
    e->vel[1] += e->accel[1];
    e->vel[2] += e->accel[2];
    e->result = keyframe_step(&e->cursor, &e->tick, (u16 *)&e->from, (u16 *)&e->to, &e->value);
}

void keyframe_track_step(KeyframeTrack *entry);
extern KeyframeTrack keyframe_table[];
void keyframe_table_update(void) {
    KeyframeTrack *entry = keyframe_table;
    s32 i;

    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active != 0) {
            keyframe_track_step(entry);
        }
    }
}

/* Draws a keyframe track as a spark: the model blended between two slots, scaled by its lifetime. */
void keyframe_track_draw(KeyframeTrackFields *e) {
    s32 slot_b = e->kind;
    s32 slot_a = slot_b + e->from;
    s32 shade;
    s32 hi;
    s32 colour;
    s32 value;

    slot_b += e->to;
    shade = (s16)e->rate >> 5;
    hi = shade;
    if (shade == 0) {
        hi = 1;
    }
    colour = (hi << 16) | (shade << 8) | shade;
    value = pchr_blend(slot_a, slot_b, 0x1000 - e->value, 1);
    value = pool_spawn_scaled(value, e->lifetime, e->lifetime, e->lifetime);
    spark_add(e->pos[0] >> 12, e->pos[1] >> 12, e->pos[2] >> 12, 0, 0, 0, value, colour);
}

/* Same code as keyframe_table_update (s06). */
void keyframe_table_draw(void) {
    KeyframeTrack *entry = keyframe_table;
    s32 i;

    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active != 0) {
            keyframe_track_draw((KeyframeTrackFields *)entry);
        }
    }
}

KeyframeTrack *keyframe_table_alloc(void) {
    KeyframeTrack *entry = keyframe_table;
    s32 i;

    for (i = 0; i < 0x40; i++, entry++) {
        if (entry->active == 0) {
            return entry;
        }
    }
    return 0;
}

/* Spawns a keyframe track: position and velocity in 20.12 fixed point, a raw 8-byte acceleration,
 * and a keyframe cursor stepped once to get the first value. The do/while blocks only weight
 * register priority and scheduling as the original does. */
void keyframe_track_start(s32 *pos, s16 *vel, Bytes8 *accel, s32 kind, Keyframe *cursor, s16 lifetime, u16 rate) {
    KeyframeTrackFields *track = (KeyframeTrackFields *)keyframe_table_alloc();
    s32 velZ;

    if (track != NULL) {
        track->kind = kind;
        track->lifetime = lifetime;
        tick_reset(&track->tick);
        track->cursor = cursor;
        track->result = keyframe_step(&track->cursor, &track->tick, (u16 *)&track->from, (u16 *)&track->to,
                                      &track->value);
        do {
            track->pos[0] = pos[0] << 12;
            track->pos[1] = pos[1] << 12;
            track->pos[2] = pos[2] << 12;
            track->vel[0] = vel[0] << 12;
            track->vel[1] = vel[1] << 12;
            velZ = vel[2];
        } while (0);
        track->rate = rate;
        track->vel[2] = velZ << 12;
        *(Bytes8 *)track->accel = *accel;
    }
}

void keyframe_track_start(s32 *pos, s16 *vel, Bytes8 *accel, s32 kind, Keyframe *cursor, s16 lifetime, u16 rate);
void fx_spawn_unit_scale(s32 a, s32 b, s32 c, s32 d, s32 e, s16 f) {
    keyframe_track_start((s32 *)a, (s16 *)b, (Bytes8 *)c, d, (Keyframe *)e, f, 0x1000);
}

void keyframe_table_deactivate_all(void) {
    KeyframeTrack *rec;
    s32 i;

    rec = keyframe_table;
    i = 0x3F;
    do {
        rec->active = 0;
        i -= 1;
        rec++;
    } while (i >= 0);
}

void keyframe_table_stop(void) {
    keyframe_table_deactivate_all();
}

/* Advances the s32 at 0x20 (unk_1C.unk_04) by 2. */
void script_cursor_advance(Object *obj) {
    obj->script.pc++;
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void script_jump_if_near_alt(Object *obj) {
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
