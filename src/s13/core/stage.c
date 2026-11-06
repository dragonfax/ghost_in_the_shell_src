/* stage: one of s13's own original source files (scripts/objmap.py); part of src/s13/main.c's unit, included there. */

void func_800B7C50(Object *obj, s32 *out) {
    out[0] = 0;
    out[1] = (-(s16)obj->height * 3) / 4;
    out[2] = 0x40;
    rotate_xz_twice(obj->yaw, obj->pitch, out, &out[1], &out[2]);
    out[0] = (obj->x >> 12) + out[0];
    out[1] = (obj->y >> 12) + out[1];
    out[2] = (obj->z >> 12) + out[2];
}

/* Turn a direction vector into angles: out = (-pitch, yaw, 0). */
void vec_to_angles(Vec3 *dir, SVECTOR *out) {
    s32 yaw;
    s32 pitch;

    angles_to_player(dir->x, dir->y, dir->z, &yaw, &pitch);
    out->vz = 0;
    out->vy = yaw;
    out->vx = -pitch;
}

void enemy_flash_spawn(Object *obj) {
    Vec3 dir;
    SVECTOR pos;
    s32 yaw;
    s32 rnd;
    s32 base;

    func_800B7C50(obj, (s32 *)&dir);
    vec_to_angles(&dir, &pos);
    yaw = obj->yaw;
    pos.vy = yaw + (rand_a_next() % 32) - 0x10;
    rnd = rand_a_next();
    base = (u16)pos.vx - 0x10;
    pos.vx = base + (rnd % 32);
    shot_spawn_obj((s32 *)&dir, (u16 *)&pos, 1, 1);
}

/* Arms the object's sound when its target_yaw byte is set and its
 * word at 0x264 has no bits in 0x1C set (words[7] is the unnamed
 * 0x264 word inside the enemy view). */
void enemy_alert(Object *obj) {
    if (*(u8 *)&obj->vars.enemy.target_yaw != 0) {
        obj->next_state = 3;
        if (!(obj->vars.from.flags & 0x1C)) {
            sound_attach(sound_start(SND_ENEMY_ALERT | SND_GROUP(1), 0x7F, 0, 0), &obj->x, NULL);
        }
    }
}

static inline GuardVars *GUARD_VARS(Object *o) { return (GuardVars *)&o->vars; }
void guard_blink_update(Object *arg0, AiTimers *arg1) {
    s32 var_a1;
    s32 var_v0;
    s32 temp_v1;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    s32 temp_v0_4;
    s32 var_v0_3;
    u16 var_v0_2;
    s32 temp_v1_2;

    if (arg1->mode == -2) {
        arg1->mode = -1;
        arg1->timer = 0;
        arg1->subtimer = 0;
    }
    var_a1 = 0;
    if (arg0->script_flag == -1) {
        var_a1 = arg0->next_state == arg1->target_id;
    }
    if ((var_a1 != 0) && (GUARD_VARS(arg0)->flags & 2) && (GUARD_VARS(arg0)->hold == 0)) {
        arg0->next_state = 0;
    }
    temp_v1 = GUARD_VARS(arg0)->flags;
    if ((temp_v1 & 0x20) && (!(temp_v1 & 0x40) || !(temp_v1 & 0x1C))) {
        if (arg1->subtimer == 0) {
            temp_v0 = arg1->timer;
            arg1->timer = (u16)(temp_v0 - 1);
            if (((temp_v0 << 0x10) <= 0) && (GUARD_VARS(arg0)->can_blink != 0)) {
                var_v0 = rand_a_next();
                temp_v1_2 = var_v0;
                if (temp_v1_2 < 0) {
                    var_v0 = temp_v1_2 + 3;
                }
                arg1->subtimer = (s16)((temp_v1_2 - ((var_v0 >> 2) * 4)) + 4);
                arg1->timer = (rand_a_next() % 6) + 2;
            }
        } else {
            temp_v0_2 = arg1->timer;
            arg1->timer = (u16)(temp_v0_2 - 1);
            if ((temp_v0_2 << 0x10) <= 0) {
                enemy_flash_spawn(arg0);
                temp_v0_3 = (u16)arg1->subtimer;
                arg1->subtimer = (s16)(temp_v0_3 - 1);
                if ((s16)temp_v0_3 >= 2) {
                    arg1->timer = (rand_a_next() % 6) + 2;
                } else {
                    temp_v0_4 = rand_a_next();
                    var_v0_3 = temp_v0_4 < 0 ? temp_v0_4 + 0x3F : temp_v0_4;
                    var_v0_3 >>= 6;
                    arg1->timer = (temp_v0_4 - (var_v0_3 << 6)) + 0x20;
                }
            }
        }
    }
}

/* Clears obj->next_state when it equals src->unk_12 and obj->unk_F8 is -1. */
void obj_state_clear_if_match(Object *obj, StateSource *src) {
    s32 same = 0;

    if (obj->script_flag == -1) {
        same = obj->next_state == src->state;
    }
    if (same != 0) {
        obj->next_state = 0;
    }
}

/* Sets obj->next_state to 1 when it equals src->unk_12 and obj->unk_F8 is -1. */
void obj_state_set_if_match(Object *obj, StateSource *src) {
    s32 same = 0;

    if (obj->script_flag == -1) {
        same = obj->next_state == src->state;
    }
    if (same != 0) {
        obj->next_state = 1;
    }
}

/* swings the object along one axis: angle += speed, pos = base +/- amplitude * sin(angle);
   flag 0x40 stops the swing (clears the axis flags 0x1C) once |angle| passes 0x400 */
void obj_swing_step(Object *obj) {
    SwingPlacement *pl;
    s32 prev;
    s32 angle;
    s32 angle_high;
    s32 offset;

    pl = (SwingPlacement *)obj->placement;
    prev = pl->angle;
    pl->angle = prev + obj->vars.from.angle_step;
    angle = ((SwingPlacement *)obj->placement)->angle;
    offset = obj->vars.from.swing_range * (s16)rcossin_tbl[angle & 0xFFF];
    if (obj->vars.from.flags & 4) {
        obj->x = obj->vars.from.origin_x + offset;
    } else if (obj->vars.from.flags & 8) {
        obj->z = obj->vars.from.origin_z + offset;
    } else {
        obj->y = obj->vars.from.origin_y - offset;
    }
    if (obj->vars.from.flags & 0x40) {
        angle = ((SwingPlacement *)obj->placement)->angle;
        angle_high = angle << 16;
        if ((angle >= 0 ? angle_high >> 16 : -angle) > 0x400) {
            obj->vars.from.flags &= ~0x1C;
        }
    }
}


/* Reaction of an object to a hit: when dead it turns away from the hit's source; otherwise it is pushed
 * from it for the cooldown steps. */
void enemy_hit_knockback(Object *obj, s32 force, s32 step) {
    s32 dx;
    s32 dz;
    s32 old_yaw;
    s16 yaw;
    s32 turn;
    s32 cooldown;
    s32 from;
    s32 ddx, ddz;

    if (obj->health <= 0) {
        old_yaw = obj->yaw;
        yaw = angle_approach(old_yaw, (obj->hit_from + 0x800) & 0xFFF, (s16)step);
        turn = yaw;
        obj->yaw = yaw;
        turn -= old_yaw;
        obj->turn = turn;
        return;
    }
    cooldown = obj->hit_cooldown;
    if (cooldown > 0) {
        obj->unk_242 = 0;
        if ((s16)step != 0) {
            force++;
            force--;
            obj_turn_toward_player(obj, (s16)step);
        }
        from = obj->hit_from;
        if (from >= 0) {
            dx = 0;
            dz = 0;
            fly_move(from, cooldown * force / 48, &dx, &dz);
            obj->pitch = (cooldown - 1) * 4;
            ddx = dx;
            obj->vz += ddx;
            ddz = dz;
            obj->vx += ddz;
        }
    }
}


/* Enemy-to-target distance check: rejects targets outside the Y band around
 * the object, otherwise tests the horizontal distance (in 4096ths) against 0x101. */
s32 obj_near_camera(Object *obj) {
    s32 dx;
    s32 dz;
    s32 y;
    s32 x;
    s32 z;

    x = obj->x;
    dx = (cam_pos - x) >> 12;
    z = obj->z;
    dz = (cam_pos_z - z) >> 12;
    y = obj->y;
    if ((cam_pos_y < y - (((s16)obj->height + 0x30) << 12)) ||
        (y < cam_pos_y - ((player_height + 0x20) << 12))) {
        return 0;
    }
    return isqrt(length_sq(dx, 0, dz)) < 0x101;
}

/* True when the player is within 336 units of the object's center: its position raised by half its
 * height, rotated by its yaw and pitch. */
s32 obj_near_player(Object *obj) {
    s32 *target;
    VECTOR center;
    VECTOR offset;
    s32 half_height;
    s32 x;
    s32 dx, dy, dz;
    s32 *off_x;
    s32 *off_y;
    s32 *off_z;

    target = player_position();
    off_x = &offset.vx;
    off_y = &offset.vy;
    off_z = &offset.vz;
    x = obj->x;
    half_height = -(s16)obj->height;
    center.vx = x >> 12;
    *off_x = 0;
    *off_z = 0;
    center.vy = obj->y >> 12;
    *off_y = half_height / 2;
    center.vz = obj->z >> 12;
    rotate_xz_twice(obj->yaw, -obj->pitch, off_x, off_y, off_z);
    center.vx += offset.vx;
    center.vy += offset.vy;
    center.vz += offset.vz;
    dx = target[0] - center.vx;
    dy = target[1] - center.vy;
    dz = target[2] - center.vz;
    offset.vx = dx;
    offset.vy = dy;
    offset.vz = dz;
    return isqrt(length_sq(dx, dy, dz)) < 0x151;
}

s32 obj_near_camera(Object *obj);
s32 obj_near_player(Object *obj);
/* Aims at the player when the object's state allows it (vars word 0x264: bits 0xC000
   select which check to use), then sends the yaw to the target. The goto keeps the
   original branch layout (both checks share the aim block). */
void enemy_aim_at_player(Object *obj) {
    s32 *player;

    if (!(obj->vars.from.flags & 0xC000)) {
        if (obj_near_camera(obj) != 0) {
            goto aim;
        }
    } else if (obj_near_player(obj) != 0) {
aim:
        player = player_position();
        hit_target_masked(0, 0x10,
                    atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)),
                    6);
    }
}

void enemy_aim_at_player(Object *obj);
void obj_swing_step(Object *obj);
/* Enemy aim update: distance to the camera-side target, solid alloc/free by range,
 * yaw toward the player when not locked, then the script step. */
void enemy_aim_update(Object *obj, ObjHandler *handler) {
    s32 dist;
    s32 flags;
    s32 *player;
    Object *self;

    dist = isqrt(length_sq((cam_pos >> 12) - (obj->x >> 12),
                           (cam_pos_y >> 12) - (obj->y >> 12),
                           (cam_pos_z >> 12) - (obj->z >> 12)));
    /* the copy of obj into self is needed to match the register allocation */
    self = obj;
    __asm__("" : "=r"(self) : "0"(obj));
    obj->vars.from.player_dist = dist;
    if (dist < 0xA00) {
        if (dist < 0x400) {
            enemy_aim_at_player(obj);
        }
        if (obj->solid_id == 0xFF) {
            obj->solid_id = solid_alloc();
        }
    } else {
        if (obj->solid_id != 0xFF) {
            solid_free(obj->solid_id);
            obj->solid_id = 0xFF;
        }
    }
    __asm__ __volatile__("" : : "r"(self));
    self->vz = 0;
    self->vx = 0;
    *(u8 *)&self->vars.enemy.target_yaw = (u8)(dist < self->vars.from.unk_270);
    ((u8 *)&self->vars.enemy.target_yaw)[1] = (u8)(dist < self->vars.from.unk_274);
    if (!(self->vars.from.flags & 0xC000)) {
        player = player_position();
        obj->yaw = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    }
    flags = self->vars.from.flags;
    if (flags & 0x1C) {
        if (flags & 0x80) {
            if (*(u8 *)&self->vars.enemy.target_yaw == 0) {
                return;
            }
            self->vars.from.flags = flags & ~0x80;
            sound_attach(sound_start(SND_ENEMY_AIM_START | SND_GROUP(1), 0x7F, 0, 0), &self->x, NULL);
        }
        obj_swing_step(self);
    }
    obj_script_step(obj, handler);
}

/* Death handler: counts down a delay, then scores the kill, spawns the
 * death effect and sound, marks its placement done and frees itself. */
void enemy_defeat(Object *obj) {
    struct {
        s32 pos[3];
        s32 pad;
        s16 rot[3];
    } spawn;
    Placement *placement;
    s32 pitch;

    if (obj->vars.part.unk_268 > 0) {
        obj->vars.part.unk_268--;
        return;
    }
    add_score(obj->score);
    add_kill_count(1);
    spawn.pos[0] = obj->x >> 12;
    spawn.pos[1] = obj->y >> 12;
    spawn.pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    spawn.rot[0] = -pitch;
    spawn.rot[1] = obj->yaw;
    spawn.rot[2] = obj->roll;
    spawn_effect(spawn.pos[0], spawn.pos[1] - 0x80, spawn.pos[2], 0x80000000);
    sound_play_at(SND_ENEMY_DEATH_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, &obj->x);
    placement_list_pop((ListRecord *)obj->placement);
    placement = obj->placement;
    placement->unk_00[4] |= 3;
    obj_free(obj);
}

s32 placement_check_free(Object *obj) {
    Placement *placement;
    s32 x, y, z;
    s32 use_alt_test;
    s32 placement_flags;
    s32 done;

    use_alt_test = 0;
    x = obj->x >> 12;
    y = obj->y >> 12;
    placement = obj->placement;
    z = obj->z >> 12;
    if (placement != NULL) {
        placement_flags = placement->unk_00[4] & 4;
        use_alt_test = placement_flags != 0;
    }
    if (use_alt_test != 0) {
        done = cam_range_check_alt(x, y, z, placement) == 0;
    } else {
        done = cam_range_check(x, y, z, placement) == 0;
    }
    if (done != 0) {
        Placement *target = obj->placement;
        *(s16 *)&target->unk_00[6] = 0;
        *(s16 *)&target->unk_00[2] = 0;
        target->unk_00[4] = (target->unk_00[4] & 0xFC) | 2;
        obj_free(obj);
    }
    return done;
}

/* Per-step hit handling: counts the hit cooldown down, applies this step's damage and records the hit. */
void obj_apply_hit(Object *obj) {
    s16 damage;
    u8 cooldown;

    damage = obj_hit_damage(obj->index);
    cooldown = obj->hit_cooldown;
    if (cooldown != 0) {
        obj->hit_cooldown = cooldown + 0xFF;
    }
    if (damage > 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        obj->health -= damage;
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
}

void placement_set_flag(Object *obj, s32 set) {
    Placement *placement = obj->placement;
    u8 flags;

    if (set == 0) {
        flags = placement->unk_00[4] & 0xFB;
    } else {
        if (*(s32 *) &obj->vars.enemy.unk_260[4] & 2) {
            return;
        }
        flags = placement->unk_00[4] | 4;
    }
    placement->unk_00[4] = flags;
}

s32 placement_free_if_done(Object *obj) {
    if ((obj->placement->unk_00[4] & 3) == 3) {
        obj_free(obj);
        return 1;
    }
    return 0;
}

void obj_anim_start(Object *obj) {
    s32 unused[4];
    s32 f = ((s32 *)obj->asset)[1];
    u8 *rec = obj->unk_A4;
    s16 frame;
    if (obj->vars.from.flags & 0xC000) f += 3;
    frame = f + 1;
    rec[1] = 1;
    rec[0] = obj->index;
    obj_block_fill(obj, rec);
    solid_setup_scratch(obj->solid_id, rec, frame, obj->unk_190);
}

static inline s16 obj_next_state(Object *obj) {
    return obj->next_state;
}
/* Enemy step: idle while next_state is 0 or 2; otherwise applies hits and,
 * once health runs out, jumps to the death script and queues enemy_defeat. */
void enemy_damage_update(Object *obj) {
    void *data;
    s32 hit_type;

    if (placement_free_if_done(obj) != 0) {
        return;
    }

    if (obj_next_state(obj) == 0 || obj_next_state(obj) == 2) {
        obj_hit_clear(obj->index);
        obj->hit = 0;
        obj->unk_17A = 0;
        placement_set_flag(obj, 0);
        obj_hit_clear(obj->index);
        return;
    }
    placement_set_flag(obj, 1);
    obj->unk_17A = 1;
    if (obj->hit < 0) {
        obj->hit = 0;
    }
    obj_apply_hit(obj);
    if (obj->health <= 0) {
        data = obj->type.data;
        script_jump((Script *)obj, ((s16 **)data)[2], (s32)data);
        hit_type = (u8)obj->hit_type;
        obj->type.unk_0A = obj->type.blend_duration >> 1;
        if (hit_type < 3 && hit_type != 0) {
            obj->vars.part.unk_268 = 4;
        }
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = (void (*)(Object *, ObjHandler *))enemy_defeat;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        return;
    }
    obj_anim_start(obj);
}

void enemy_spark_add(Object *obj, s32 *pos, s16 *rot, s32 colour) {
    s32 base;
    s32 slot;

    base = model_slot_pchr(*(s32 *)obj->asset);
    slot = base + 0x10;
    if (obj_next_state(obj) != 0 && obj_next_state(obj) != 2) {
        slot = base + 0x11;
    }
    spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], slot, colour);
}

void enemy_spark_add(Object *obj, s32 *pos, s16 *rot, s32 colour);
static inline void spark_add_list0(s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    register SparkList *list asm("$4");
    register s32 frame asm("$13") = value;
    s32 n;
    SparkRec *s;
    u8 *tail;

    n = spark_count;
    __asm__("" : "=r"(list) : "0"(&spark_list), "r"(frame));
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
        s->unk_12 = frame;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}
/* Queues the object's position, draws it (tinted blue while hit) and adds its keyframe spark record. */
void enemy_draw_sparks(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    s16 rot[3];
    s32 colour;
    s32 offset;
    s32 visible;
    s32 frame;
    register Object *self asm("$18");
    s32 pitch;
    s32 busy;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    busy = (u8)obj->unk_17A;
    self = obj;
    if (busy == 0) {
        req_queue_push(pos[0], pos[1], pos[2], 0);
    }
    colour = 0x666666;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    }
    FAKE_OPAQUE(self);
    pitch = -obj->pitch;
    rot[0] = pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    if (!(obj->vars.from.flags & 0x8000)) {
        enemy_spark_add(obj, pos, rot, colour);
    }
    visible = 1;
    if (obj->type.unk_0C == obj->type.unk_0E) {
        visible = obj->type.unk_0C != 0x20;
    }
    if (visible) {
        offset = 0x50;
        if (!(obj->vars.from.flags & 0x8000)) {
            offset = (obj->vars.from.flags & 0x7000) >> 8;
        }
        if ((self->vars.from.flags & 0x1C) && (self->vars.from.flags & 0x4000)) {
            offset = 0x50;
        }
        frame = obj_keyframe_value(obj, offset);
        spark_add_list0(pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], frame, colour);
    }
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

/* Sets up obj from a placement record: copies the position (whole units in
 * the high bits, angle in the low 12), the health and the hit/flag bits. */
void obj_apply_placement(Object *obj, Placement *place, s32 flags) {
    Placement *old_place;
    s32 bits;
    s32 unk_16;
    s32 unit;
    s32 divisor;
    s32 quotient;

    *(s16 *)&place->unk_00[2] = -1;
    old_place = obj->placement;
    old_place->unk_00[4] &= 0xFC;
    obj->kind = place->unk_00[5];
    obj_set_flags(obj, flags);
    obj->health = place->health;
    unk_16 = (s16)place->unk_16;
    obj->vars.from.unk_258 = 0;
    obj->vars.from.unused_25C = 0;
    *(s16 *)&obj->vars.from.unk_268 = 8;
    *((u8 *)obj + 0x26A) = 0;
    obj->score = unk_16;
    obj->vars.from.unk_270 = *(s16 *)&place->unk_18;
    obj->vars.from.flags = *(s16 *)&place->unk_1A;
    obj->vars.from.swing_range = place->range;
    unit = 0x1000;
    divisor = place->unk_1E;
    quotient = unit / divisor;
    bits = obj->vars.from.flags;
    obj->vars.from.unk_274 = 0x600;
    obj->vars.from.angle_step = quotient;
    if (bits & 0x8000) {
        flags |= 0x10;
    }
    if (bits & 0x100) {
        flags |= 0x2;
    }
    obj->unk_17A = 1;
    obj->accel_y = unit;
    obj->flags = (s16)flags;
    obj->placement = place;
    obj->solid_id = 0xFF;
    obj->vars.from.origin_x = ((s32)place->x >> 12) << 12;
    obj->vars.from.origin_y = ((s32)place->y >> 12) << 12;
    obj->vars.from.origin_z = ((s32)place->z >> 12) << 12;
    obj->y = obj->vars.from.origin_y;
    obj->x = obj->vars.from.origin_x;
    obj->z = obj->vars.from.origin_z;
    obj->yaw = place->y & 0xFFF;
    obj->pitch = place->x & 0xFFF;
    obj->roll = place->z & 0xFFF;
}

void enemy_draw_sparks(Object *obj, ObjHandler *handler);
extern s16 *enemy_script_table[]; /* the enemy's scripts: [0] normal start, [1] start when flag bit 0 is set */
/* Sets up an enemy's handlers: damage and draw, the script (by flag bit 0, which is also its first
 * next_state), aiming, and the phase 0 handler when vars.words[4] is set. */
s32 enemy_init_handlers(Object *obj, s32 flags) {
    obj->handlers[2].fn = (ObjHandlerFn)enemy_damage_update;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = enemy_draw_sparks;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    if (flags & 1) {
        obj->next_state = 1;
        script_start((Script *)obj, enemy_script_table[1], (s32)enemy_script_table);
    } else {
        obj->next_state = 0;
        script_start((Script *)obj, enemy_script_table[0], (s32)enemy_script_table);
    }
    obj->handlers[1].fn = enemy_aim_update;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    if (obj->vars.from.unk_258 != 0) {
        obj->handlers[0].fn = (ObjHandlerFn)obj_link_script_run;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
    }
    return 0;
}

extern s16 *obj_type_data[];
extern s16 *obj_data_entry_table[];
void obj_set_data_entry(ObjDataView *self, s32 idx) {
    s16 *entry = obj_data_entry_table[idx];

    self->jumps = obj_type_data;
    self->unk_26 = 0;
    self->pc = entry;
}

void obj_set_part_mode(s32 arg0, s32 flags) {
    s32 mode;
    s32 size;

    mode = 1;
    size = 0x1000;
    if (flags & 0xC000) {
        mode = 4;
        size = 0xCCC;
    }
    obj_set_part_bounds((Object *)arg0, mode, size);
}

extern s32 place_asset[];
extern StateEntry D_8010F890[];
s32 obj_spawn_from_place(s32 init_arg) {
    Object *obj;
    s32 ok;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
        obj_hit_clear(obj->index);
        obj_hit_flag_set(obj->index, 0);
        obj_hit_set_unk08(obj->index, 2);
        obj_hit_set_unk06(obj->index, 1);
        obj->asset = place_asset;
        obj->hit_cooldown_max = 0x30;
        obj->state_table = D_8010F890;
        obj_apply_placement(obj, (Placement *) init_arg, 0x221);
        obj_set_part_mode((s32) obj, obj->vars.from.flags);
        obj_set_data_entry((ObjDataView *) obj, enemy_init_handlers(obj, obj->vars.from.flags));
        ok = 1;
    } else {
        ok = 0;
    }
    return ok;
}

void obj_stop(Object *obj) {
    obj->speed = 0;
}

void blink_timer_update(BlinkObject *obj, BlinkLink *link) {
    if (link->flag == -2) {
        s32 n = 30;
        obj->timer = (rand_a_next() % n) + 0xA;
        link->flag = -1;
    } else {
        obj->timer -= 1;
        if (obj->timer <= 0) {
            obj->next_state = 0;
        }
    }
    {
        s16 t = obj->hold;
        if (t > 0) {
            obj->hold = t - 1;
            __asm__ volatile("" ::: "memory"); /* original reloads hold */
            if (obj->hold > 0) {
                return;
            }
        }
    }
    if (obj->blink_on_end != 0) {
        obj->next_state = 7;
    }
}

extern s16 *blink_jump_script[];
void blink_link_update(BlinkObject *obj, BlinkLink *link) {
    if (link->flag == -2) {
        s32 n;
        if (rand_a_next() > 0x800) {
            s16 **slot = blink_jump_script;
            script_jump((Script *)obj, *slot, (s32)(slot - 1));
        }
        n = 30;
        obj->timer = (rand_a_next() % n) + 0xA;
        link->flag = -1;
    } else {
        obj->timer -= 1;
        if (obj->timer <= 0) {
            obj->next_state = 0;
        }
    }
    {
        s16 t = obj->hold;
        if (t > 0) {
            obj->hold = t - 1;
            __asm__ volatile("" ::: "memory"); /* original reloads hold */
            if (obj->hold > 0) {
                return;
            }
        }
    }
    if (obj->blink_on_end != 0) {
        obj->next_state = 7;
    }
}

s32 obj_turn_by_state(Object *obj, s32 turn_step);
void obj_set_mode(Object *obj, s32 mode);
void obj_spin_update(Object *obj, ObjHandler *handler) {
    s32 yaw;
    s32 turn;
    s32 spin;
    s32 yaw2;
    s32 turn2;

    switch (handler->result) {
    case -2:
        handler->result = 1;
        obj->vars.spin.speed = obj_turn_by_state(obj, 0x20);
        return;
    case -1:
        if (obj->vars.spin.speed != 0) {
            yaw = obj->yaw;
            obj->yaw = (yaw + obj->vars.spin.speed) & 0xFFF;
            turn = obj->turn;
            obj->turn = (turn + obj->vars.spin.speed) & 0xFFF;
        }
        if (obj->vars.spin.unk_256 == 0) {
            obj->speed = 0;
            obj->vars.spin.speed = (obj->vars.spin.speed * 7) >> 3;
        }
        if (obj->script_flag != 0) {
            obj->vars.spin.speed = 0;
            obj->next_state = 0;
        }
        return;
    default:
        if (obj->script_flag == 0xFF) {
            obj_set_mode(obj, 0);
            handler->result = -1;
            obj->speed = -4;
            return;
        }
        spin = obj->vars.spin.speed;
        if (spin != 0) {
            spin >>= 2;
            yaw2 = obj->yaw;
            turn2 = obj->turn;
            obj->yaw = (yaw2 + spin) & 0xFFF;
            obj->turn = (turn2 + spin) & 0xFFF;
        }
        handler->result = 1;
        break;
    }
}

void obj_set_mode(Object *obj, s32 mode);
s32 obj_turn_by_state(Object *obj, s32 turn_step);
/* Per-frame step of a behaviour: -2 is the start (random chance to set next_state 9, speed 0),
 * -1 waits for the object's animation/sound flag, anything else checks for the 0xFF target. */
void anim_wait_step(Object *obj, ObjHandler *handler) {
    switch (handler->result) {
    case -2:
        if (rand_a_next() < 0x400) {
            obj->next_state = 9;
        }
        obj->speed = 0;
        handler->result = 1;
        break;
    case -1:
        if (obj->script_flag != 0) {
            obj->next_state = 0;
        }
        if (*(u8 *)&obj->vars.h.unk_256 == 0) {
            obj->next_state = 0;
        }
        break;
    default:
        if (obj->script_flag == 0xFF) {
            obj_set_mode(obj, 0);
            handler->result = -1;
        } else {
            handler->result = 1;
        }
        break;
    }
    if (obj->script_flag == -1) {
        obj->next_state = 0;
    }
    obj_turn_by_state(obj, 0x10);
}

void reverse_step(Object *obj, ObjHandler *handler) {
    switch (handler->result) {
    case -2:
        obj_set_mode(obj, 1);
        obj->speed = -8;
        handler->result = 0xC;
        break;
    case -1:
        if (obj->script_flag != 0) {
            obj->next_state = 0;
        }
        obj->speed = 0;
        break;
    }
}

void fly_timed_move(Object *obj, ObjHandler *handler, s32 a2, s32 a3) {
    s32 period;
    s32 speed;
    s32 clamped;
    s32 timer;

    if (handler->result == -2) {
        obj->vars.enemy.unk_258 = a3;
        period = 30;
        obj->vars.words[7] = (rand_a_next() % period) + 0x32;
        handler->result = -1;
    } else {
        speed = (obj->vars.enemy.unk_258 * 9) >> 3;
        clamped = speed;
        obj->vars.enemy.unk_258 = speed;
        if (speed > 0x14000) {
            clamped = 0x14000;
        }
        if (clamped >= 0x2000) {
            if (speed > 0x14000) {
                speed = 0x14000;
            }
        } else {
            speed = 0x2000;
        }
        obj->vars.enemy.unk_258 = speed;
        timer = obj->vars.words[7] - 1;
        obj->vars.words[7] = timer;
        if (timer <= 0) {
            obj->next_state = 0;
        }
    }
    fly_strafe((obj->yaw + a2) & 0xFFF, obj->vars.enemy.unk_258 >> 12, &obj->vz, &obj->vx);
}

void fly_side_270_step(Object *obj, ObjHandler *handler) {
    fly_timed_move(obj, handler, 0xC00, 0x2000);
}

/* Forwards its first two arguments unchanged; passes 0x400 and 0x2000 as the last two. */
void fly_side_90_step(Object *obj, ObjHandler *handler) {
    fly_timed_move(obj, handler, 0x400, 0x2000);
}

void obj_turn_timed(Object *obj, ObjHandler *handler, s32 turn) {
    s32 range;
    s32 turn_acc;
    s32 yaw;

    if (handler->result == -2) {
        range = 30;
        obj->vars.words[7] = rand_a_next() % range + 60;
        handler->result = -1;
    } else if (--obj->vars.words[7] <= 0) {
        obj->next_state = 0;
    }
    yaw = obj->yaw;
    turn_acc = obj->turn;
    yaw = (yaw + turn) & 0xFFF;
    obj->yaw = yaw;
    obj->turn = (turn_acc + turn) & 0xFFF;
}

void obj_turn_timed(Object *obj, ObjHandler *handler, s32 turn);
void obj_turn_minus16_step(Object *obj, ObjHandler *handler) {
    obj_turn_timed(obj, handler, -0x10);
}

void obj_turn_plus16_step(Object *obj, ObjHandler *handler) {
    obj_turn_timed(obj, handler, 0x10);
}

/* Forwards its two arguments to both helpers, each with its own fixed
   constants (0xC00/0x2000 and -0x20). Meaning of the constants unknown. */
void fly_side_270_turn_minus32_step(Object *obj, ObjHandler *handler) {
    fly_timed_move(obj, handler, 0xC00, 0x2000);
    obj_turn_timed(obj, handler, -0x20);
}

void fly_side_90_turn_plus32_step(Object *obj, ObjHandler *handler) {
    fly_timed_move(obj, handler, 0x400, 0x2000);
    obj_turn_timed(obj, handler, 0x20);
}

void fly_side_270_turn_plus16_step(Object *obj, ObjHandler *handler) {
    fly_timed_move(obj, handler, 0xC00, 0x2000);
    obj_turn_timed(obj, handler, 0x10);
}

void fly_side_90_turn_minus16_step(Object *obj, ObjHandler *handler) {
    fly_timed_move(obj, handler, 0x400, 0x2000);
    obj_turn_timed(obj, handler, -0x10);
}

extern s16 *fly_script_base;
extern s16 *fly_turn_pos_script[];
extern s16 *fly_turn_neg_script[];
void fly_random_turn_step(Object *obj, ObjHandler *handler) {
    s32 *ppos;
    register s16 **src asm("$6"); /* the original keeps the slot address in a2 */
    s16 turn;
    Script *script;
    s32 roll;

    if (handler->result == -2) {
        roll = rand_a_next();
        script = (Script *)obj;
        if (roll >= 0x801) {
            src = fly_turn_pos_script;
            turn = 0x400;
        } else {
            turn = -0x400;
            src = fly_turn_neg_script;
        }
        handler->timer = turn;
        script_jump(script, *src, (s32)&fly_script_base);
    }
    fly_timed_move(obj, handler, handler->timer, 0x2000);
    if (((u8 *)obj->vars.words)[9] != 0) {
        ppos = player_position();
        if (((atan2(ppos[2] - (obj->z >> 12), ppos[0] - (obj->x >> 12)) + 0x400) & 0xFFF) < 0x800) {
            obj->next_state = 9;
            return;
        }
        obj->next_state = 0;
    }
}

void gun_burst_update(Object *obj);
void enemy_pursue_move(Object *obj, s32 a1, s32 a2);
void enemy_update(Object *obj, ObjHandler *handler) {
    s32 dist;

    dist = isqrt(length_sq((cam_pos >> 12) - (obj->x >> 12),
                           (cam_pos_y >> 12) - (obj->y >> 12),
                           (cam_pos_z >> 12) - (obj->z >> 12)));
    obj->vars.enemy.unk_25E = dist;
    obj->vz = 0;
    obj->vx = 0;
    ((u8 *)obj->vars.words)[9] = dist < 0x800;
    ((u8 *)obj->vars.words)[10] = dist < 0x600;
    obj_script_step(obj, handler);
    gun_burst_update(obj);
    fly_strafe(obj->yaw, obj->speed, &obj->vz, &obj->vx);
    obj_turn_by_state(obj, 0x10);
    enemy_pursue_move(obj, obj->unk_1C6, 0x20);
}

extern u8 D_8010F900[];
extern s16 *fly_script_base;
extern s16 *enemy_op_table[];
extern s16 *D_8010FCC8;
extern StateEntry D_8010FCCC[];
void enemy_phase2(Object *obj);
void obj_spark_phase3(Object *obj);
s32 enemy_spawn_placed(Placement *place) {
    Object *obj;
    s16 **script;
    ObjHandler *h;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    h = obj->handlers;
    obj->handlers[0].fn = (void *)obj_link_script_run;
    obj->handlers[1].fn = (void *)enemy_update;
    obj->handlers[2].fn = (void *)enemy_phase2;
    obj->handlers[3].fn = (void *)obj_spark_phase3;
    obj->asset = D_8010F900;
    obj->hit_cooldown_max = 4;
    obj->unk_1C6 = 4;
    obj->state_table = D_8010FCCC;
    h[0].unk_11 = 0;
    *(volatile s16 *)&h[0].state = 0;
    h[1].unk_11 = 0;
    *(volatile s16 *)&h[1].state = 0;
    h[2].unk_11 = 0;
    *(volatile s16 *)&h[2].state = 0;
    h[3].unk_11 = 0;
    *(volatile s16 *)&h[3].state = 0;
    obj->script.data = enemy_op_table;
    obj->script.unk_0A = 0;
    obj->script.pc = D_8010FCC8;
    script = &fly_script_base;
    script_start((Script *)obj, *script, (s32)script);
    obj_init_from_place(obj, place, 0x227);
    obj_set_part_bounds(obj, 1, 0x1333);
    obj->vars.enemy.mode = obj->health;
    meter_set_mode(1);
    obj_hit_flag_set(obj->index, 0x80);
    return 1;
}

void enemy_death(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    s16 rot[3];
    s32 pitch;
    s32 kind;

    if (obj->vars.drift.pad_254[0] != 0) {
        obj->speed -= 0xE3;
        obj->speed = MAX(MIN(obj->speed, 0x1000), 0);
        fly_move(obj->yaw, obj->speed >> 12, &obj->vz, &obj->vx);
        obj->speed = obj->speed >> 1;
        obj->vars.drift.pad_254[0]--;
        return;
    }

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    rot[2] = (u16)obj->roll;
    kind = obj->type.unk_0E;
    obj_spawn_replacement(obj, kind + model_slot_pchr(*(s32 *)obj->asset));
    obj->placement->unk_00[4] |= 3;
    obj_free(obj);
}

void obj_apply_hits(Object *obj) {
    s16 damage;
    u8 cooldown;

    damage = obj_hit_damage(obj->index);
    obj->hit_from = obj_hit_from(obj->index);
    obj->hit_type = obj_hit_type(obj->index);
    obj_hit_clear(obj->index);
    cooldown = obj->hit_cooldown;
    if (cooldown != 0) {
        obj->hit_cooldown = cooldown + 0xFF;
    }
    if (damage != 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        obj->health -= damage;
        obj->hit_cooldown = obj->hit_cooldown_max;
    }
}

extern s16 *enemy_death_slot[]; /* the last entry of the jump table at fly_script_base */
void enemy_phase2(Object *obj) {
    s32 sound;
    s16 **slot;
    s32 hit_type;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    obj_apply_hits(obj);
    meter_set(obj->health, obj->vars.enemy.mode);
    if (obj->health > 0) {
        obj_block_lerp(obj, 0);
        return;
    }
    sound = obj->vars.snd2.sound[0];
    obj->handlers[2].fn = enemy_death;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = obj_draw_spark;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    if (sound != 0) {
        if (sound != 0x100) {
            sound_stop(sound);
        }
        obj->vars.snd2.sound[0] = 0;
    }
    add_score(obj->score);
    add_kill_count(1);
    meter_set_mode(0);
    set_mission_active(0);
    slot = enemy_death_slot;
    script_start((Script *)obj, *slot, (s32)slot - 0x3C);
    hit_type = (u8)obj->hit_type;
    if (hit_type < 3 && hit_type != 0) {
        /* byte store at 0x254 (low byte of enemy.sound_channel[0]) */
        *(u8 *)&obj->vars.words[3] = 0x2D;
    }
}

/* Maps a value through the object's range (type.unk_0C..unk_0E) with a weight from
 * (type.unk_08, unk_0A). When the object's vars byte 11 is set, the result is blended
 * a second time. base is the caller's offset, advanced by model_slot_pchr. */
s32 obj_range_blend(Object *obj, s32 base) {
    s32 result;
    s32 blend;

    blend = ((u8 *)obj->vars.words)[11];
    base += model_slot_pchr(*(s32 *)obj->asset);
    if (obj->type.unk_0C == obj->type.unk_0E) {
        result = obj->type.unk_0E + base;
    } else {
        result = pchr_blend(obj->type.unk_0C + base, obj->type.unk_0E + base,
                             ((obj->type.unk_0A + 1) << 12) / obj->type.blend_duration, 0);
        if (blend > 0) {
            pchr_lists_build(result);
            result = pchr_blend(result, base + 1, 0x1000 - (blend << 7), 0);
        }
    }
    return result;
}

void obj_aim_marker_draw(Object *obj, Vec3 *pos) {
    SVECTOR rot;

    rot.vx = obj->width + 0x20;
    rot.vy = obj->height;
    rot.vz = obj->unk_1E8[0] + 0x20;
    aim_marker_draw(2, &rot, pos, 0);
}

extern u8 tab_burst_pos[] __asm__("spark_burst_offsets");
extern u8 tab_burst_frame[] __asm__("spark_burst_frames");
static inline void spawn_burst(Object *obj, s32 side) {
    Vec3 dir_vec;
    Vec3 *dir = &dir_vec;
    Vec3 *origin;
    SVECTOR ang;
    s32 pos[3];
    s32 frame_base;
    s32 rnd, frame, half_turn;
    s32 height;
    s32 off;
    s32 base;
    s32 back_yaw, pitch;
    SparkList *list;

    dir->x = side;
    height = (s16)obj->height;
    dir->z = 0xA3;
    dir->y = (-height * 2) / 5;
    obj_offset_to_world_shifted(obj, (s32 *)dir);
    dir_to_angles(dir, &ang);
    ang.vy = angle_approach(obj->yaw, ang.vy, 0x60);
    ang.vx = angle_approach(obj->pitch, ang.vx, 0xC0);
    rnd = rand_a_next();
    base = (u16)ang.vy - 0x10;
    ang.vy = base + rnd % 32;
    rnd = rand_a_next();
    base = (u16)ang.vx - 0x10;
    ang.vx = base + rnd % 32;
    origin = dir;
    half_turn = 0x800;
    list = &spark_list;
    frame_base = model_slot_pchr(*(s32 *)obj->asset) + 0x81;
    back_yaw = ang.vy + 0x800;
    pitch = ang.vx;
    for (off = 0; off < 0x50; off += 0x10) {
        s32 count, px, py, pz;
        SparkRec *rec;
        u8 *tail;
        s32 *src = (s32 *)(tab_burst_pos + off);

        pos[0] = src[0];
        pos[1] = src[1];
        pos[2] = src[2];
        rotate_xz_twice(back_yaw, pitch, &pos[0], &pos[1], &pos[2]);
        px = pos[0] + origin->x;
        pos[0] = px;
        py = pos[1] + origin->y;
        pz = pos[2] + origin->z;
        pos[1] = py;
        pos[2] = pz;
        frame = frame_base + *(s32 *)(tab_burst_frame + off);
        count = spark_count;
        if (count < 0xFF) {
            rec = (SparkRec *)(count * sizeof(SparkRec) + (s32)list->items);
            count++;
            spark_count = count;
            *(s32 *)rec->colour = 0;
            tail = list->tail[0];
            list->tail[0] = &rec->next;
            *tail = count;
            rec->next = 0;
            rec->x = px;
            rec->y = py;
            rec->z = pz;
            rec->unk_12 = frame;
            rec->yaw = half_turn;
            rec->pitch = 0;
            rec->roll = 0;
        }
    }
}
void drift_spawn_sparks(Object *obj) {
    obj->vars.drift.pad_254[1] = 0;
    spawn_burst(obj, 0x26);
    spawn_burst(obj, -0x27);
}

/* Adds the object's spark record on chain 0 (tinted blue while hit), draws
 * its aim marker and spawns the drift sparks when they are pending. */
void obj_spark_phase3(Object *obj) {
    Vec3 pos;
    SVECTOR rot;
    s32 colour;
    s32 pitch;
    s32 count;
    register SparkList *list asm("$4");
    register s32 frame asm("$13");
    SparkRec *spark;
    u8 *tail;
    u16 ry, rz;
    s32 rx;
    s32 x, y, z;
    s32 sched_pin;

    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    frame = obj_range_blend(obj, 0);
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
        colour = 0;
        FAKE_OPAQUE(colour);
    }
    x = pos.x >> 12;
    y = pos.y >> 12;
    z = pos.z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    ry = obj->yaw;
    rot.vy = ry;
    rz = obj->roll;
    rot.vz = rz;
    rot.vx += obj->vars.part.parent_yaw;
    rx = rot.vx;
    count = spark_count;
    /* The list address in $a0. sched_pin, a set-once output kept alive below,
     * and the read of rot.vx place this asm where the original's code goes. */
    __asm__("" : "=r"(list), "=r"(sched_pin) : "0"(&spark_list), "m"(rot.vx));
    if (count < 0xFF) {
        spark = (SparkRec *)(count * sizeof(SparkRec) + (s32)list->items);
        count++;
        spark_count = count;
        *(s32 *)spark->colour = colour;
        tail = list->tail[0];
        list->tail[0] = &spark->next;
        *tail = count;
        spark->next = 0;
        spark->x = x;
        spark->y = y;
        spark->z = z;
        spark->unk_12 = frame;
        spark->yaw = ry;
        spark->pitch = rx;
        spark->roll = rz;
    }
    FAKE_USE(sched_pin);
    obj_aim_marker_draw(obj, &pos);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    if (obj->vars.drift.pad_254[1] != 0) {
        drift_spawn_sparks(obj);
    }
}

void func_800BA6D8(void) {
}


/* Rotates the object's offset (yaw, pitch) into out[0..2] and adds the object's position (>> 12). */
void obj_offset_to_world_shifted(Object *obj, s32 *out) {
    rotate_xz_twice(obj->yaw, -obj->pitch, out, out + 1, out + 2);
    out[0] = (obj->x >> 12) + out[0];
    out[1] = (obj->y >> 12) + out[1];
    out[2] = (obj->z >> 12) + out[2];
}


void obj_offset_to_world(Object *obj, s32 *pos) {
    rotate_xz_twice(obj->yaw, -obj->pitch, pos, pos + 1, pos + 2);
    pos[0] = obj->x + pos[0];
    pos[1] = obj->y + pos[1];
    pos[2] = obj->z + pos[2];
}

/* Turn a direction vector into angles: out = (-pitch, yaw, 0). */
void dir_to_angles(Vec3 *dir, SVECTOR *out) {
    s32 yaw;
    s32 pitch;

    angles_to_player(dir->x, dir->y, dir->z, &yaw, &pitch);
    out->vz = 0;
    out->vy = yaw;
    out->vx = -pitch;
}

/* Turns the object toward the player and records the turn amount. */
void obj_turn_to_player(Object *obj, s32 turn_step) {
    s32 old_yaw;
    s32 new_yaw;
    s32 *player;
    s32 turn;

    old_yaw = obj->yaw;
    player = player_position();
    new_yaw = angle_approach(old_yaw,
                             atan2(player[2] - (obj->z >> 12),
                                   player[0] - (obj->x >> 12)),
                             turn_step);
    obj->yaw = new_yaw;
    turn = obj->turn;
    obj->turn = turn + (new_yaw - old_yaw);
}

/* States 1 and 7..10 turn toward the player; turn_step passes through.
   The original returns whatever obj_turn_to_player left in v0. */
s32 obj_turn_by_state(Object *obj, s32 turn_step) {
    s32 s = obj->next_state;
    if (s == 1) {
        goto call;
    }
    if (s > 0) {
        if (s < 11) {
            if (s >= 7) {
call:
                return ((s32 (*)(Object *, s32))obj_turn_to_player)(obj, turn_step);
            }
        }
    }
    return 0;
}

void enemy_pursue_move(Object *obj, s32 speed, s32 step) {
    s32 dx;
    s32 dz;
    s32 x, z;
    s32 old_yaw;
    s16 new_yaw;
    s32 diff;
    s16 from;
    s32 cooldown;

    if (obj->health <= 0) {
        old_yaw = obj->yaw;
        new_yaw = angle_approach(old_yaw, (obj->hit_from + 0x800) & 0xFFF, (s16)step);
        diff = new_yaw - old_yaw;
        do {
        } while (0);
        obj->yaw = new_yaw;
        obj->turn = diff;
        return;
    }
    cooldown = obj->hit_cooldown;
    if (cooldown > 0) {
        obj_turn_to_player(obj, 0x18);
        from = obj->hit_from;
        if (from >= 0) {
            dx = 0;
            dz = 0;
            speed = cooldown * speed / 48;
            fly_move(from, speed, &dx, &dz);
            obj->vars.h.unk_24C = cooldown * 4;
            x = dx;
            obj->vz += x;
            z = dz;
            obj->vx += z;
        }
    } else {
        obj->vars.h.unk_24C = 0;
    }
}
