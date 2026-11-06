/* jetski: one of s04's own original source files (scripts/objmap.py); part of src/s04/main.c's unit, included there. */

void jetski_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

/* Reads a (key, index) halfword pair from the object's script cursor (0x20). The key is compared
 * with the object's halfword at 0x250: a key >= 0 jumps through the table when they are equal, a
 * negative key (its bitwise NOT) jumps when they differ. A jump sets the cursor to table[index]. */
void script_jump_if_key(Object *obj) {
    s16 *cursor;
    s32 key;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    key = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (key >= 0) {
        if (obj->vars.jetski.state != key) {
            return;
        }
    } else {
        if (obj->vars.jetski.state == (s16)~key) {
            return;
        }
    }
    obj->script.pc = ((s16 **)obj->script.data)[index];
}

void obj_flow_move(Object *obj);
void jetski_emit_wake(Object *obj);
/* Per-frame jetski update. While the handler's state matches next_state, next_state advances
 * through the riding states; the rider's sound and wake effects run from the frame counter at 0x260. */
void jetski_update(Object *obj, ObjHandler *handler) {
    obj->vz = 0;
    obj->vx = 0;
    obj_flow_move(obj);
    if (obj->script_flag != 0 && obj->next_state == handler->state) {
        switch (obj->next_state) {
        case 7:
        case 12:
            obj->next_state = 8;
            break;
        case 1:
            obj->next_state = 2;
            break;
        case 4:
            obj->next_state = 5;
            break;
        case 0:
        case 2:
        case 5:
        case 8:
        case 9:
        case 11:
            break;
        default:
            obj->next_state = 0;
            obj->speed = 0;
            break;
        }
    }
    limit_move(&obj->x, &obj->vx);
    obj_script_step(obj, handler);
    obj->vars.bob.timer = obj->vars.bob.timer + 1;
    if ((obj->vars.bob.timer & 7) == 0) {
        jetski_emit_wake(obj);
    }
    if ((obj->vars.bob.timer & 0x3F) == 0) {
        if ((rand_a_next() & 3) == 0) {
            sound_attach(sound_start(0x5461, 0x30, 0, 0), &obj->x, 0);
        }
    }
}


void obj_init_aim_at_camera(Object *obj)
{
    s32 z = obj->z;
    s32 dz = cam_pos_z - z;
    s32 x = obj->x;
    s32 dx = cam_pos - x;
    s32 angle = atan2(dz >> 12, dx >> 12);
    s32 yaw = obj->yaw;

    if ((u32)((angle - yaw + 0x400) & 0xFFF) <= 0x800) {
        obj->vars.jetski.aim_yaw = obj->yaw;
    } else {
        obj->vars.jetski.aim_yaw = yaw + 0x800;
    }
    obj->vars.jetski.unk_24E = 0;
}

/* Turns obj toward the point (cam_pos, cam_pos_z) in the XZ plane, then wraps
   the yaw delta into -0x800..0x800 (one full turn is 0x1000). */
void obj_face_point_xz(Object *obj) {
    s16 aim;
    s16 delta;
    s32 yaw;
    s32 z;

    z = obj->z;
    aim = angle_approach(obj->vars.jetski.aim_yaw,
                         atan2((cam_pos_z - z) >> 12, (cam_pos - obj->x) >> 12),
                         0x18);
    obj->vars.jetski.aim_yaw = aim;
    yaw = obj->yaw;
    delta = aim - yaw;

    obj->vars.turn.yaw = delta;
    while (obj->vars.turn.yaw >= 0x801) {
        obj->vars.turn.yaw -= 0x1000;
    }
    delta = obj->vars.turn.yaw;
    if (delta < -0x800) {
        do {
            obj->vars.turn.yaw = delta + 0x1000;
            delta = obj->vars.turn.yaw;
        } while (delta < -0x800);
    }
    delta = obj->vars.turn.yaw;
    if (delta < -0x400) {
        obj->vars.turn.yaw = -0x800 - delta;
    }
    delta = obj->vars.turn.yaw;
    if (delta >= 0x401) {
        obj->vars.turn.yaw = 0x800 - delta;
    }
}

/* Turns vars.turn.yaw toward 0 while it is nonzero, wrapping it into
 * -0x800..0x800 (a full turn is 0x1000). Once it reaches 0, sets next_state to 10. */
void obj_turn_to_rest(Object *obj) {
    s16 yaw;

    if (obj->vars.turn.yaw != 0) {
        yaw = angle_approach(obj->vars.turn.yaw, 0, 0x18);
        obj->vars.turn.yaw = yaw;
        if (yaw >= 0x801) {
            obj->vars.turn.yaw = yaw - 0x1000;
        }
        if (obj->vars.turn.yaw < -0x800) {
            obj->vars.turn.yaw = obj->vars.turn.yaw + 0x1000;
        }
    } else {
        obj->next_state = 10;
    }
}

void obj_aim_point(Object *obj, s32 *out);

/* Runs two object helpers with a scratch buffer, then sets next_state to 0xC. */
void obj_fire_shot_at_target(Object *obj, s32 *pos);

void obj_aim_and_fire(Object *obj) {
    void *buf = scratch_alloc(0x10);

    obj_aim_point(obj, buf);
    obj_fire_shot_at_target(obj, buf);
    obj->next_state = 0xC;
    scratch_top -= 0x10;
}

void obj_aim_point(Object *obj, s32 *out) {
    s16 *offs = scratch_alloc(8);
    register s32 pitch asm("$2") = (s16)obj->vars.jetski.unk_24E;
    s32 abs_pitch = pitch;
    s32 scale;
    s32 abs_x4;
    s32 abs_x400;
    s32 angle;

    if (pitch < 0) {
        abs_pitch = -abs_pitch;
    }
    abs_x4 = abs_pitch * 4;
    if (pitch >= 0) {
        scale = 0x4E;
        offs[2] = 0x36;
        offs[0] = 0xE;
        out[1] = -0x64;
    } else {
        scale = 0x34;
        offs[2] = 0x4E;
        offs[0] = 0xE;
        abs_x400 = ((abs_pitch * 8 + abs_x4) * 8 + abs_x4) * 4;
        out[1] = ((0x1000 - abs_x4) * -0x57 - abs_x400) >> 12;
    }
    angle = (u16)obj->vars.jetski.unk_24E & 0xFFF;
    out[2] = offs[2] + ((scale * cos_table[angle].value) >> 12);
    angle = (u16)obj->vars.jetski.unk_24E & 0xFFF;
    out[0] = offs[0] + ((scale * (s16)rcossin_tbl[angle]) >> 12);
    rotate_xz_twice(obj->yaw, obj->pitch, out, out + 1, out + 2);
    scratch_top -= 8;
    out[0] = (obj->x >> 12) + ((out[0] * 0x1666) >> 12);
    out[1] = (obj->y >> 12) + ((out[1] * 0x1666) >> 12);
    out[2] = (obj->z >> 12) + ((out[2] * 0x1666) >> 12);
}

extern GunSetup enemy_gun_setup;
void obj_fire_shot_at_target(Object *obj, s32 *pos) {
    SVECTOR *rot = scratch_alloc(8);
    Vec3 *dir;
    s32 neg;

    neg = obj->pitch;
    neg = -neg;
    rot->vx = neg;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    rot->vy = rot->vy + obj->vars.jetski.unk_24E;
    dir = scratch_alloc(0x10);
    angles_to_vector(obj->vars.enemy.walk_state, 0, get_flow_max(), &dir->x, &dir->y, &dir->z);
    dir->x >>= 12;
    dir->y >>= 12;
    dir->z >>= 12;
    sound_play_at_units(SND_ENEMY_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    shot_spawn_target(pos, (u16 *)rot, &dir->x, 2, (s32)&enemy_gun_setup);
    scratch_top -= 0x10;
    scratch_top -= 0x8;
}

void jetski_speed_update(Object *obj);
void jetski_swerve_update(Object *obj);
void obj_flow_move(Object *obj) {
    ((Flow *)&obj->vars.jetski.flow)->speed = get_flow_max();
    flow_sample((Flow *)&obj->vars.jetski.flow, obj->width, &obj->x, &obj->vx, &obj->turn);
    obj->yaw += obj->turn;
    switch (obj->vars.jetski.script_index) {
    case 0:
        jetski_speed_update(obj);
        break;
    case 1:
        jetski_swerve_update(obj);
        break;
    }
}

void jetski_speed_update(Object *obj) {
    s32 speed;
    s32 dist;
    s32 z_hi;
    s32 z_mid;

    switch (obj->vars.jetski.state) {
    case 0:
        speed = obj->speed;
        z_hi = obj->z;
        if (((cam_pos_z - z_hi) >> 12) >= 0x280) {
            obj->speed_accel = 0x2000;
        }
        speed += obj->speed_accel;
        speed = MAX(MIN(speed, 0), -0x10000);
        obj->speed = speed;
        fly_strafe(obj->vars.enemy.walk_state, speed >> 12, &obj->vz, &obj->vx);
        if (obj->speed == 0) {
            obj->vars.jetski.state = 1;
            obj->vars.jetski.state_timer = 0;
        }
        break;
    case 1:
        speed = obj->speed;
        z_mid = obj->z;
        dist = (cam_pos_z - z_mid) >> 12;
        if (dist >= 0x180) {
            obj->speed_accel = 0x800;
        }
        if (dist < -0x180) {
            obj->speed_accel = -0x800;
        }
        speed += obj->speed_accel;
        speed = MAX(MIN(speed, 0x8000), -0x8000);
        obj->speed = speed;
        fly_strafe(obj->vars.enemy.walk_state, speed >> 12, &obj->vz, &obj->vx);
        obj->vars.jetski.state_timer++;
        if (obj->vars.jetski.state_timer >= 0x280 && obj->speed <= 0) {
            obj->speed_accel = -0x2000;
            obj->vars.jetski.state = 2;
        }
        break;
    case 2:
        speed = obj->speed;
        speed += obj->speed_accel;
        speed = MAX(MIN(speed, 0x18000), -0x18000);
        obj->speed = speed;
        fly_strafe(obj->vars.enemy.walk_state, speed >> 12, &obj->vz, &obj->vx);
        break;
    }
}

/* The jetski's second movement pattern: approach, swerve past the camera, side-slide back, repeat. */
void jetski_swerve_update(Object *obj) {
    s32 speed;
    s32 depth;
    register s32 zpos asm("$2");
    s32 side;
    s32 drift;
    s32 dx, dy, dz;

    switch (obj->vars.jetski.state) {
    case 3: {
        s32 dist;
        s32 z;
        z = obj->z;
        dist = (cam_pos_z - z) >> 12;
        fly_strafe(obj->vars.enemy.walk_state, obj->speed >> 12, &obj->vz, &obj->vx);
        if (dist < obj->vars.jetski.range) {
            obj->vars.jetski.state = 4;
            obj->vars.jetski.heading = 0;
        }
        break;
    }
    case 4: {
        s32 dist;
        s32 z;
        s32 turn;
        s32 heading;
        s32 len;
        s32 speed;
        speed = obj->speed;
        turn = -0x2AA;
        dx = 0;
        dy = 0;
        dz = 0;
        z = obj->z;
        dist = (cam_pos_z - z) >> 12;
        if (cam_pos - obj->x >= 0) {
            turn = 0x2AA;
        }
        if (dist < obj->vars.jetski.range - 0x200) {
            obj->speed_accel = -0x1000;
        }
        speed += obj->speed_accel;
        speed = MAX(MIN(speed, 0x14000), 0);
        obj->speed = speed;
        heading = angle_approach(obj->vars.jetski.heading, turn, 0x30);
        obj->vars.jetski.heading = heading;
        len = obj->speed;
        len >>= 12;
        angles_to_vector(obj->vars.enemy.walk_state + (s16)heading, 0, len, &dx, &dy, &dz);
        obj->vz += dz;
        obj->vx += dx;
        if (dist < obj->vars.jetski.range - 0x200 && dz <= 0x8000 && dx <= 0xC000) {
            obj->vars.jetski.state = 5;
            obj->vars.jetski.state_timer = 0;
            obj->accel_z = dz >= 0 ? -0x1000 : 0x1000;
            obj->accel_x = dx >= 0 ? 0x1000 : -0x1000;
            obj->vars.jetski.drift_speed = dz;
            obj->vars.jetski.slide_speed = dx;
        }
        break;
    }
    case 5: {
        s32 slide;
        drift = obj->vars.jetski.drift_speed;
        zpos = obj->z;
        depth = (cam_pos_z - zpos) >> 12;
        slide = obj->vars.jetski.slide_speed;
        side = (cam_pos - obj->x) >> 12;
        if (depth >= obj->vars.jetski.range - 0x280 && depth < obj->vars.jetski.range - 0x180) {
            if (drift < 0) {
                drift += 0x1000;
                obj->vars.jetski.drift_speed = MAX(MIN(drift, 0), -0x8000);
            } else if (drift > 0) {
                drift -= 0x1000;
                drift = MAX(MIN(drift, 0x8000), 0);
                obj->vars.jetski.drift_speed = drift;
            }
        } else {
            if (depth >= obj->vars.jetski.range - 0x180) {
                obj->accel_z = 0x1000;
            }
            if (depth < obj->vars.jetski.range - 0x280) {
                obj->accel_z = -0x1000;
            }
            drift += obj->accel_z;
            obj->vars.jetski.drift_speed = MAX(MIN(drift, 0x8000), -0x8000);
        }
        fly_strafe(obj->vars.enemy.walk_state, obj->vars.jetski.drift_speed >> 12, &obj->vz, &obj->vx);
        if (side >= 0x280) {
            obj->accel_x = 0x1000;
        }
        if (side < -0x280) {
            obj->accel_x = -0x1000;
        }
        slide += obj->accel_x;
        slide = MAX(MIN(slide, 0xC000), -0xC000);
        obj->vars.jetski.slide_speed = slide;
        fly_strafe(obj->vars.enemy.walk_state + 0x400, slide >> 12, &obj->vz, &obj->vx);
        obj->vars.jetski.state_timer++;
        if (obj->vars.jetski.state_timer >= 0x140 && ABS(obj->vars.jetski.slide_speed) <= 0x1000) {
            obj->vars.jetski.state = 1;
            obj->vars.jetski.state_timer = 0;
            obj->speed = obj->vars.jetski.drift_speed;
        }
        break;
    }
    case 1: {
        s32 dist;
        s32 z;
        speed = obj->speed;
        z = obj->z;
        dist = (cam_pos_z - z) >> 12;
        if (dist >= 0x180) {
            obj->speed_accel = 0x800;
        }
        if (dist < -0x180) {
            obj->speed_accel = -0x800;
        }
        speed += obj->speed_accel;
        speed = MAX(MIN(speed, 0x8000), -0x8000);
        obj->speed = speed;
        fly_strafe(obj->vars.enemy.walk_state, speed >> 12, &obj->vz, &obj->vx);
        obj->vars.jetski.state_timer++;
        if (obj->vars.jetski.state_timer >= 0x1E0 && obj->speed <= 0) {
            obj->speed_accel = -0x2000;
            obj->vars.jetski.state = 2;
        }
        break;
    }
    case 2:
        speed = obj->speed;
        speed += obj->speed_accel;
        speed = MAX(MIN(speed, 0x18000), -0x18000);
        obj->speed = speed;
        fly_strafe(obj->vars.enemy.walk_state, speed >> 12, &obj->vz, &obj->vx);
        break;
    }
}

s32 jetski_wake_spawn(s32 *pos, u16 *rot, s32 arg2, s32 arg3, s32 arg4);
/* Spawns something 0x65 behind the object, turned by its angles, with the angles half-turned. */
void jetski_emit_wake(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);

    pos[0] = 0;
    pos[1] = 0;
    pos[2] = -0x65;
    rot[0] = obj->pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    rotate_xz_twice(rot[1], -rot[0], pos, pos + 1, pos + 2);
    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    pos[2] += obj->z >> 12;
    rot[1] += 0x800;
    jetski_wake_spawn(pos, (u16 *)rot, get_model_slot_base() + 0x50, 8, 0xAA);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

extern s16 *jetski_script_table[];
s32 jetski_destroy(Object *obj) {
    s32 result = 1;
    s32 *pos;
    SVECTOR *rot;
    s32 p;

    switch (obj->vars.jetski.destroy_step) {
    case -1:
        obj->next_state = 0xD;
        obj->unk_17A = 0;
        obj->speed = 0;
        obj->vz = 0;
        obj->vx = 0;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->vars.jetski.destroy_step = 4;
        script_jump((Script *)obj, jetski_script_table[0], (s32)&jetski_script_table[-11]);
        break;
    case 0:
        pos = (s32 *)scratch_top;
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        scratch_top += 0x10;
        rot = (SVECTOR *)scratch_top;
        p = obj->pitch;
        rot->vx = -p;
        rot->vy = obj->yaw;
        rot->vz = obj->roll;
        scratch_top += 8;
        object_spawn_at(pos, rot, model_slot_pchr(*(s32 *)obj->asset) + obj->type.unk_0E);
        result = 0;
        object_spawn_at(pos, rot, model_slot_pchr(*(s32 *)obj->asset) + 0x7F);
        scratch_top -= 8;
        scratch_top -= 0x10;
        break;
    default:
        obj->vars.jetski.destroy_step--;
        break;
    }
    return result;
}

s32 obj_pose_turn_blend(Object *obj, s32 base);
void spark_add_at_obj(Object *obj);
/* Adds a spark record at the jet ski's position (tinted while hit), then the camera-facing one. */
void jetski_draw(Object *obj, ObjHandler *handler) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 *unused = scratch_alloc(8);
    SVECTOR *rot = scratch_alloc(8);
    s32 value;
    s32 colour;
    u16 roll;
    s32 pitch;
    Vec3 *out = pos;

    FAKE_OPAQUE(out);
    out->x = obj->x >> 12;
    out->y = obj->y >> 12;
    out->z = obj->z >> 12;
    value = obj_pose_turn_blend(obj, 0);
    colour = 0;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
        pitch = 0;
    }
    pitch = obj->pitch;
    rot->vx = -pitch;
    rot->vy = obj->yaw;
    roll = obj->roll;
    rot->vz = roll;
    spark_add_u(pos->x, pos->y, pos->z, rot->vy, rot->vx, roll, value, colour);
    spark_add_at_obj(obj);
    scratch_top -= 8;
    if (obj->hit != 0)
        obj->hit = -1;
    scratch_top -= 8;
    scratch_top -= 0x10;
}

s32 obj_pose_range_blend(Object *obj, s32 base);
s32 obj_pose_turn_blend(Object *obj, s32 base) {
    s32 blend[4];
    s32 yaw;
    s32 mag;
    s32 step;

    switch (obj->next_state) {
    case 8:
    case 9:
    case 11:
    case 12:
        yaw = obj->vars.turn.yaw;
        mag = ABS(yaw);
        if (mag == 0 || mag == 0x400) {
            return obj_pose_range_blend(obj, base + (yaw / 0x400) * 0x20);
        }
        step = -0x20;
        if (yaw > 0)
            step = 0x20;
        blend[0] = step;
        blend[1] = 0;
        blend[0] = obj_pose_range_blend(obj, base + step);
        blend[1] = obj_pose_range_blend(obj, base + blend[1]);
        blend[2] = ABS(obj->vars.turn.yaw) * 4;
        blend[3] = 0x1000 - blend[2];
        return pchr_blend(blend[0], blend[1], blend[2], 0);
    }
    return obj_pose_range_blend(obj, base);
}

s32 obj_pose_range_blend(Object *obj, s32 base) {
    s32 blend[4]; /* start, end, weight, 0x1000 - weight */

    base += model_slot_pchr(*(s32 *)obj->asset);
    if (obj->type.unk_0C != obj->type.unk_0E) {
        blend[0] = obj->type.unk_0C + base;
        blend[1] = obj->type.unk_0E + base;
        blend[2] = ((obj->type.unk_0A + 1) << 12) / obj->type.blend_duration;
        blend[3] = 0x1000 - blend[2];
        return pchr_blend(blend[0], blend[1], blend[2], 0);
    }
    return obj->type.unk_0C + base;
}

s32 obj_camera_facing_pchr();
/* Adds a spark record at the object's position with its (pitch negated) rotation. */
void spark_add_at_obj(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);
    s16 word;
    s32 rx, ry;
    SparkList *list;
    SparkRec *s;
    u8 *tail;
    s32 n;
    u16 roll;
    s32 x, y, z, pitch;

    word = obj_camera_facing_pchr();
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    list = &spark_list;
    n = SPARK_COUNT;
    rx = rot[0];
    ry = rot[1];
    x = pos[0];
    y = pos[1];
    z = pos[2];
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
        s->unk_12 = word;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = roll;
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

extern s32 camera0_pos_z;
s32 obj_camera_facing_pchr(Object *obj) {
    s32 base;
    s32 angle;
    s32 old;

    base = model_slot_pchr(*(s32 *)obj->asset) + 0x7F;
    if (((atan2(camera0_pos_z - (obj->z >> 12), cameras[0].pos.vx - (obj->x >> 12)) - obj->yaw) + 0x80 & 0xFFF) < 0x101U) {
        angle = pchr_get_angle(base);
        pchr_set_angle_range(base, 1, angle - 0x200);
        old = base;
        FAKE_OPAQUE(old);
        base = pchr_copy_slot(base);
        pchr_set_angle_range(old, 1, angle);
    }
    return base;
}

/* Same code as func_800C31C4 (s10). */
void sound_stop_on_destroy(Object *obj) {
    sound_stop(obj->vars.jetski.sound_id); /* 0x264 */
}

extern u8 jetski_asset[];
extern ScriptCallEntry jetski_call_table[];
extern StateEntry D_80119434[];
extern s16 *jetski_type_data[];
extern s16 *D_8011941C[];
extern GunSetup enemy_gun_setup;
extern s16 *jetski_data[11];
s32 jetski_spawn(Placement *place) {
    Object *obj;
    s32 sound;
    s32 result = 0;
    s16 **script;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[0].fn = jetski_phase0;
        obj->handlers[1].fn = jetski_update;
        obj->handlers[2].fn = obj_state_run_b;
        obj->handlers[3].fn = jetski_draw;
        obj->callback = (s32) jetski_destroy;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->destructor = sound_stop_on_destroy;
        obj->kind = place->unk_04[1];
        obj->asset = jetski_asset;
        obj->hit_cooldown_max = 0x30;
        obj->call_table = jetski_call_table;
        obj->unk_1C6 = 0;
        obj->state_table = D_80119434;
        obj_init_from_place(obj, place, 0x27);
        obj_set_part_bounds(obj, 0x7F, 0x1666);
        enemy_gun_setup.damage = obj->damage;
        do { } while (0);
        obj->vars.trace.aim_yaw = -1;
        obj->vars.jetski.script_index = *(u16 *) &place->unk_1A >> 8;
        script = jetski_data;
        obj->vars.jetski.aim_yaw = 0;
        obj->vars.jetski.unk_24E = 0;
        obj->vars.bob.timer = 0;
        obj->script.pc = D_8011941C[obj->vars.jetski.script_index];
        obj->script.data = jetski_type_data;
        obj->script.unk_0A = 0;
        script_start((Script *) obj, *script, (s32) script);
        place->unk_02 = 0;
        rec_reset((PartSlot *) &obj->vars.bob.current);
        switch (obj->vars.jetski.script_index) {
        case 0:
            obj->vars.jetski.state = 0;
            obj->vars.jetski.state_timer = 0;
            obj->vars.jetski.heading = 0;
            obj->vars.jetski.range = 0;
            obj->vars.jetski.slide_speed = 0;
            obj->vars.jetski.drift_speed = 0;
            obj->speed_accel = 0;
            obj->speed = -0x10000;
            break;
        case 1:
            obj->vars.jetski.state = 3;
            obj->vars.jetski.state_timer = 0;
            obj->vars.jetski.heading = 0;
            obj->vars.jetski.range = place->range;
            obj->vars.jetski.slide_speed = 0;
            obj->vars.jetski.drift_speed = 0;
            obj->speed_accel = 0;
            obj->speed = 0x14000;
            break;
        }
        sound = sound_start(SND_JETSKI_ENGINE_LOOP | SND_HELD | SND_GROUP(2), 0x28, 0, 0);
        obj->vars.jetski.sound_id = sound;
        sound_attach(sound, &obj->x, NULL);
        sound_set_flag_bit2(obj->vars.jetski.sound_id, 1);
        result = 1;
    }
    return result;
}

/* Advances the object's 16-bit counter (0x24E) by its step (0x24C); frees the object once the counter
 * reaches 0x1000 (as signed). */
void jetski_wake_update(Object *obj) {
    u16 counter;

    counter = obj->vars.jetski_wake.phase + obj->vars.jetski_wake.phase_step;
    obj->vars.jetski_wake.phase = counter;
    if ((s16)counter >= 0x1000) {
        obj_free(obj);
    }
}

/* Adds a spark record at the wake's position; its size grows with the wake's age. */
void jetski_wake_draw(Object *obj, ObjHandler *handler) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);
    s32 size;
    s32 rx, ry;
    SparkList *list;
    SparkRec *s;
    u8 *tail;
    s32 n;
    s16 roll;
    s32 x, y, z;
    s32 pitch;

    size = obj->vars.jetski_wake.base_size + (((s16)obj->vars.jetski_wake.phase * obj->vars.jetski_wake.amplitude) >> 12);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    list = &spark_list;
    n = SPARK_COUNT;
    rx = rot[0];
    ry = rot[1];
    x = pos[0];
    y = pos[1];
    z = pos[2];
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
        s->unk_12 = size;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = roll;
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void jetski_wake_update(Object *obj);
void jetski_wake_draw(Object *obj, ObjHandler *handler);
s32 jetski_wake_spawn(s32 *pos, u16 *rot, s32 arg2, s32 arg3, s32 arg4) {
    Object *obj;
    s32 result;
    u16 roll;

    result = 0;
    obj = obj_new();
    if (obj != NULL) {
        result = 1;
        list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
        obj->handlers[1].fn = jetski_wake_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = jetski_wake_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        roll = rot[2];
        obj->vars.jetski_wake.base_size = arg2;
        obj->vars.jetski_wake.amplitude = arg3;
        obj->vars.jetski_wake.phase_step = arg4;
        obj->vars.jetski_wake.phase = 0;
        obj->roll = roll;
    }
    return result;
}
