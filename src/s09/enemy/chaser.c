/* chaser: one of s09's own original source files (scripts/objmap.py); part of src/s09/main.c's unit, included there. */

void obj_aim_and_turn(Object *obj, void *aim_slot, s16 aim_step, s16 yaw_step);
void chaser_move(Object *obj) {
    s32 dx;
    s32 dz;
    s32 height;

    dx = 0;
    dz = 0;
    obj->unk_1B7 = 0;
    if (obj->unk_242 == 0) {
        height = (cam_pos_y >> 12) - 0x12C;
        obj_turn_toward_player(obj, 0x18);
    } else {
        height = obj->vars.chaser.target_x >> 12;
        obj_aim_and_turn(obj, &obj->yaw, 8, 8);
    }
    obj->pitch = angle_approach(obj->pitch, 0, 8);
    if (*(s16 *)&obj->vars.enemy.unk_260[2] != 0) {
        obj_set_fall_speed(obj, 4, height);
        fly_move(obj->yaw, obj->speed + 0xA, &dx, &dz);
    } else {
        obj_set_fall_speed(obj, 2, height);
        fly_move(obj->yaw, obj->speed, &dx, &dz);
    }
    obj_step_axes_toward(obj, dz, dx);
    *(s16 *)&obj->vars.enemy.unk_260[0] = 0;
}

/* Turns toward the player (pitch only outside 0x200..0xE00), flies at its speed and bobs. */
void obj_hover_home(Object *obj) {
    VECTOR *target;
    s32 yaw;
    s32 pitch;
    s32 dx;
    s32 dz;
    s32 bob;
    s32 turned;

    target = scratch_alloc(0x10);
    bob = (s16)((const s32 *)rcossin_tbl)[obj->vars.hover.phase & 0xFFF];
    dx = 0;
    dz = 0;
    obj->unk_1B7 = 0;
    player_position_copy(target);
    bob <<= 1;
    vector_to_angles(target->vx - (obj->x >> 12), target->vy - (obj->y >> 12) + 0x60,
                     target->vz - (obj->z >> 12), &yaw, &pitch);
    turned = angle_approach(obj->pitch, pitch, 8);
    if ((u32)(turned - 0x200) > 0xC00) {
        obj->pitch = turned;
    }
    obj->yaw = angle_approach(obj->yaw, yaw, 0x18);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    scratch_top -= 0x10;
    obj->vy = bob;
    obj->vars.hover.phase += 0x20;
}

void obj_hover_home(Object *obj);
void obj_spawn_muzzle_child(Object *obj);
/* Clears unk_1B7, runs obj_hover_home, and if the halfword at vars.h.unk_256 is zero, calls obj_spawn_muzzle_child. */
void obj_hover_attack_update(Object *obj) {
    obj->unk_1B7 = 0;
    obj_hover_home(obj);
    /* unk_256 is a signed halfword; stage.h types it u16, so read it through an s16 pointer. */
    if (*(s16 *)&obj->vars.heavy_mobile_suit.aim_yaw == 0) {
        obj_spawn_muzzle_child(obj);
    }
}

void stage_nop_c(void) {
}

void obj_speed_ease_update(Object *obj, ObjHandler *handler) {
    s32 speed;
    s32 target;

    obj->vz = 0;
    obj->vx = 0;
    obj_script_step(obj, handler);
    if (obj->vars.heavy_mobile_suit.timer == 0) {
        speed = obj->speed;
        target = obj->vars.snd.sound;
        if (speed == target) {
            obj->speed = speed;
        } else {
            if (target < speed) {
                obj->speed = speed - 1;
            } else {
                obj->speed = speed + 1;
            }
        }
        obj->vars.heavy_mobile_suit.timer = 4;
    }
    obj->vars.heavy_mobile_suit.timer -= 1;
    obj->vars.enemy.sound_channel[1] -= 1;
    obj->vars.heavy_mobile_suit.unk_258 += 0x38;
    obj->vars.heavy_mobile_suit.blend_weight += 0x71;
    if ((s16) obj->vars.heavy_mobile_suit.unk_258 >= 0x1001) {
        obj->vars.heavy_mobile_suit.unk_258 = 0x1000;
    }
    obj_lean_into_turn(obj, &obj->vars.enemy.sound_channel[0], 4, 0x100);
}

static inline void spark_add_to(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    s32 n = SPARK_COUNT;
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
        s->pitch = rx;
        s->roll = rz;
    }
}
void boss_laser_spark_emit(Object *obj, Vec3 *pos, SVECTOR *rot) {
    s32 offset[3];
    s32 *at;
    s32 level;
    s32 colour;
    s32 mix;
    s32 *asset;
    s32 slot;
    s32 id;
    s32 model;
    s32 model_copy;
    s32 strength;
    SparkList *list;

    if ((s16)obj->vars.heavy_mobile_suit.unk_258 < 0x1000) {
        at = (s32 *)scratch_top;
        scratch_top += 0x10;
        offset[0] = 0x33;
        asset = obj->asset;
        offset[1] = -0x41;
        slot = *asset;
        offset[2] = 0xC8;
        model = model_slot_pchr(slot);
        vec3_rotate(rot->vy, rot->vx, rot->vz, &offset[0], &offset[1], &offset[2]);
        at[0] = offset[0] + pos->x;
        at[1] = offset[1] + pos->y - 0x60;
        at[2] = offset[2] + pos->z;
        strength = (u16)obj->vars.heavy_mobile_suit.unk_258;
        do { } while (0);
        model_copy = model;
        FAKE_OPAQUE(model_copy);
        level = (s16)strength >> 5;
        mix = level;
        if (level == 0) {
            mix = 1;
        }
        colour = (mix << 16) | (level << 8) | level;
        id = pchr_blend(model + 10, model + 11, 0x1000 - (s16)strength, 0);
        list = &spark_list;
        spark_add_to(list, at[0], at[1], at[2], 0, 0x800, 0, id, colour);
        FAKE_USE(list);
        if ((s16)obj->vars.heavy_mobile_suit.unk_258 < 0x800) {
            id = pchr_blend(model + 7, model + 8, 0x800 - (s16)obj->vars.heavy_mobile_suit.unk_258, 0);
            spark_add_to(list, at[0], at[1], at[2], rot->vy, rot->vx + 0x800, rot->vz + ((s16)obj->vars.heavy_mobile_suit.unk_258 / 16), id, colour);
            obj->vars.heavy_mobile_suit.blend_weight = 0;
        } else {
            id = pchr_blend(model_copy + 8, model_copy + 9, 0x1000 - obj->vars.heavy_mobile_suit.blend_weight, 0);
            spark_add_to(list, at[0], at[1], at[2], rot->vy, rot->vx + 0x800, rot->vz + ((s16)obj->vars.heavy_mobile_suit.unk_258 / 16), id, colour);
        }
        FAKE_USE(model_copy);
        scratch_top -= 0x10;
    }
}

void boss_laser_spark_emit(Object *obj, Vec3 *pos, SVECTOR *rot);
void spark_add_y_offset(s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour, s32 y_offset);
/* Adds a spark record at the object's position, then fires effect 2 from the same place. */
void obj_emit_spark(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    SVECTOR *rot2 = scratch_alloc(8);
    s32 value;
    s32 colour;
    s32 pitch;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    pitch = obj->pitch;
    rot->vx = -pitch;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    if (test_bit(obj->flags, 6)) {
        s32 base = obj->type.unk_0E;

        value = base + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        value = obj_keyframe_value(obj, 0);
    }
    colour = 0;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
        pitch = 0;
    }
    boss_laser_spark_emit(obj, pos, rot);
    spark_add_y_offset(pos->x, pos->y, pos->z, rot->vy, rot->vx, rot->vz, value, colour, -0x60);
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    rot2->vx = obj->width;
    rot2->vy = obj->height;
    rot2->vz = obj->unk_1E8[0];
    aim_marker_draw(2, rot2, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}

/* Stops the sound whose handle is the byte at 0x264. */
void enemy_destructor(Object *obj) {
    sound_stop(obj->vars.enemy.unk_260[4]);
}


void obj_run_states_raised(Object *obj, ObjHandler *handler) {
    obj->y += 0xFFFA0000;
#if STAGE == 9
    obj_run_states_default(obj, handler);
#else
    obj_state_run_b(obj, handler);
#endif
    obj->y += 0x60000;
}


extern s16 heavy_mobile_suit_script[4];
extern s16 *heavy_mobile_suit_data[];
extern u8 heavy_mobile_suit_model_asset[];
extern s16 *heavy_mobile_suit_script_data[];
extern ScriptCallEntry D_8011BDB8[];
extern StateEntry D_8011BE10[];
extern s16 *D_8011BDB4;
extern void obj_emit_spark(Object *obj);
/* Spawns the s09 enemy at a placement: handlers, script, sound loop. Returns 0 when no object is free. */
s32 heavy_mobile_suit_place(Placement *placement) {
    Object *obj;
    s32 yaw;
    s32 sound;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    *(s16 *) &placement->unk_00[2] = 0x708;
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) obj_timer_next_state;
    obj->handlers[1].fn = obj_speed_ease_update;
    obj->handlers[2].fn = obj_run_states_raised;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) obj_emit_spark;
    obj->callback = (s32) obj_respawn;
    obj->destructor = enemy_destructor;
    obj->asset = heavy_mobile_suit_model_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = D_8011BDB8;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->kind = 1;
    obj->state_table = D_8011BE10;
    script_start((Script *) obj, heavy_mobile_suit_script, (s32) heavy_mobile_suit_data);
    obj->script.data = heavy_mobile_suit_script_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_8011BDB4;
    obj_init_from_place(obj, placement, 0x37);
    obj->speed = 0;
    obj_set_part_bounds(obj, 0x11, 0x1000);
    obj->vars.heavy_mobile_suit.timer = 4;
    obj->vars.enemy.sound_channel[1] = -1;
    obj->vars.heavy_mobile_suit.unk_248 = 0;
    obj->vars.heavy_mobile_suit.unk_24C = 0;
    obj->vars.heavy_mobile_suit.unused_252 = 1;
    obj->vars.enemy.sound_channel[0] = 0;
    obj->vars.heavy_mobile_suit.unk_258 = 0x1000;
    obj->vars.heavy_mobile_suit.blend_weight = 0x1000;
    *(s16 *) &obj->vars.enemy.unk_260[0] = 0;
    obj->vars.heavy_mobile_suit.unk_25C = obj->y;
    /* the placement's yaw, rounded toward zero to whole units of 256 */
    yaw = *(s16 *) &placement->unk_1A;
    if (yaw < 0) {
        yaw += 0xFF;
    }
    *(s16 *) &obj->vars.enemy.unk_260[2] = yaw >> 8;
    obj_hit_set_unk08(obj->index, 4);
    obj_hit_set_unk06(obj->index, 2);
    sound = sound_start(SND_MOBILE_SUIT_IDLE_LOOP | SND_HELD | SND_GROUP(1), 0x40, 0, 0);
    sound_attach(sound, &obj->x, NULL);
    sound_set_flag_bit2(sound, 1);
    obj->vars.enemy.unk_260[4] = sound;
    return 1;
}

/* Per-frame sweep for a flying object: traces from its position to the position one
 * velocity step ahead, and on a hit spawns an effect and marks it for removal. */
void shot_sweep(Object *obj, ObjHandler *handler) {
    s32 *from;
    s32 *ahead;
    s32 *hit;
    s16 target;

    from = scratch_alloc(0x30);
    ahead = from + 4;
    hit = from + 8;
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    ahead[0] = (obj->x + obj->vx) >> 12;
    ahead[1] = (obj->y + obj->vy) >> 12;
    ahead[2] = (obj->z + obj->vz) >> 12;

    if (cam_range_check(from[0], from[1], from[2]) == 0 ||
        (obj_hit_damage(obj->index) << 16) > 0) {
        goto expire;
    }
    if (trace_world(8, 0x10, from, ahead, hit) != 0) {
        spawn_effect(hit[0], hit[1], hit[2], 0);
expire:
        obj->vars.child.unk_250 = 1;
    } else {
        set_collide_mode(1);
        if (trace_objects(from, ahead, 0x10, hit, &target) != 0) {
            hit_target_masked(target, 1,
                (s16)atan2(hit[2] - from[2], hit[0] - from[0]), obj->damage);
            spawn_effect(hit[0], hit[1], hit[2], 0);
            obj->vars.child.unk_250 = 1;
        }
        set_collide_mode(0);
        obj->z += obj->vz;
        obj->x += obj->vx;
        obj->y += obj->vy;
        if (obj->vars.child.progress < 0x1000) {
            obj->vars.child.progress += 0x100;
        }
    }

    if (obj->vars.child.unk_250 != 0) {
        obj_free(obj);
    }
    scratch_top -= 0x30;
}

/* Emits two spark records at the object's position: the first carries the yaw + 0x800 and the roll, the second
 * one after the offset (0, 0, 0x4B) is rotated by the yaw and pitch. */
void obj_spark_pair_draw(Object *obj, ObjHandler *handler) {
    s32 *origin;
    s16 *angles;
    s32 off_x, off_y, off_z;
    s32 mode;
    s32 pitch;
    u16 roll;

    mode = obj->vars.child.unk_248;
    origin = scratch_alloc(0x10);
    origin[0] = obj->x >> 12;
    origin[1] = obj->y >> 12;
    origin[2] = obj->z >> 12;
    angles = scratch_alloc(8);
    pitch = obj->pitch;
    angles[0] = -pitch;
    angles[1] = obj->yaw;
    roll = obj->roll;
    angles[2] = roll;
    off_x = 0;
    off_y = 0;
    off_z = 0x4B;
    spark_add_u(origin[0], origin[1], origin[2], angles[1] + 0x800, angles[0], roll, mode + 1, 0);
    rotate_xz_twice(angles[1], -angles[0], &off_x, &off_y, &off_z);
    origin[0] += off_x;
    origin[1] += off_y;
    origin[2] += off_z;
    spark_add(origin[0], origin[1], origin[2], 0, 0x800, 0, mode + 2, 0);
    scratch_top -= 0x10;
    scratch_top -= 8;
}

extern u8 heavy_mobile_suit_model_asset[];
void shot_sweep(Object *obj, ObjHandler *handler);
void obj_spark_pair_draw(Object *obj, ObjHandler *handler);
void obj_spawn_child(Object *parent, s32 *pos, u16 *rot, s16 unk_184_init) {
    Object *obj;
    s32 anim;
    s32 yaw;
    s32 pitch;
    s32 speed;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = shot_sweep;
        obj->handlers[3].fn = obj_spark_pair_draw;
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
        obj->callback = 0;
        obj->asset = heavy_mobile_suit_model_asset;
        obj_hit_clear(obj->index);
        obj->damage = unk_184_init;
        obj->speed = 0x32;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        anim = model_slot_pchr(*(s32 *) parent->asset);
        yaw = obj->yaw;
        pitch = obj->pitch;
        speed = obj->speed;
        obj->vars.child.unk_248 = anim + 4;
        obj->vars.child.progress = 0;
        obj->vars.child.unk_250 = 0;
        angles_to_vector(yaw, pitch, speed, &obj->vx, &obj->vy, &obj->vz);
    }
}

void obj_spawn_muzzle_child(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    u16 *rot;
    s32 pitch;
    s32 dx, dy, dz;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    rot = scratch_alloc(8);
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    dx = 0x33;
    rot[1] = obj->yaw;
    dy = -0x41;
    rot[2] = obj->roll;
    dz = 0x118;
    pos[1] -= 0x60;
    vec3_rotate((s16)rot[1], (s16)rot[0], (s16)rot[2], &dx, &dy, &dz);
    pos[0] += dx;
    pos[1] += dy;
    pos[2] += dz;
    sound_play_at_units(SND_S09_MUZZLE_FIRE | SND_GROUP(1), 0x60, 0x3C, pos);
    obj_spawn_child(obj, pos, rot, obj->damage);
    scratch_top -= 0x10;
    scratch_top -= 8;
}



/* Spawns an object of this object's kind (its type plus the index of its asset) at its position in whole
 * units, with its angles (pitch negated), then marks its placement as spawned (byte 4 bits 0-1 = 2). */
s32 obj_respawn(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 kind;
    Placement *placement;
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    rot[2] = (u16)obj->roll;
    kind = *(s16 *)&obj->type.unk_0E;
    object_spawn_at(pos, rot, kind + model_slot_pchr(*(s32 *)obj->asset));
    placement_list_pop((ListRecord *)obj->placement);
    placement = obj->placement;
    placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
    return 0;
}
