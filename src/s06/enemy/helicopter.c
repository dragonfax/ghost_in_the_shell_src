/* helicopter: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

void flier_strafe_hold_range(s16 *actor, s32 *target, s32 *pos, s32 speed, s32 range, s32 unused) {
    s32 dir;
    s32 limit;

    dir = speed;
    limit = (cam_pos_z >> 12) + range;
    if ((target[2] >> 12) < limit) {
        dir = -dir;
    }
    fly_strafe(actor[2], dir, pos + 2, pos);
}

void obj_snap_to_ground(Object *obj) {
    Placement *target;
    s32 from[3];
    s32 to[3];
    s32 hit[3];

    target = obj->placement;
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    to[0] = obj->x >> 12;
    to[1] = (obj->y >> 12) + 0xBB8;
    to[2] = obj->z >> 12;
    trace_world(8, 0x10, from, to, hit);
    obj->y = (hit[1] - target->range) << 12;
}

void obj_aim_and_turn(Object *obj, void *aim_slot, s16 aim_step, s16 yaw_step);
/* Stops the object's loop sound if one is playing, then moves it by its heading and speed. */
void obj_move_and_snap(Object *obj) {
    ObjSoundBytes *snd;
    s32 dx;
    s32 dz;
    u8 handle;

    dx = 0;
    dz = 0;
    snd = (ObjSoundBytes *)obj;
    handle = snd->sound_1;
    if (handle != 0) {
        sound_stop(handle);
        snd->sound_1 = 0;
    }
    obj_aim_and_turn(obj, &obj->vars.s06_helicopter.aim_angle, 0x10, 8);
    obj_step_axes_toward(obj, dz, dx);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_snap_to_ground(obj);
}

void fighter_jet_rocket_update(Object *obj);
void obj_move_countdown(Object *obj) {
    s32 dx;
    s32 dz;
    u16 *timer;
    u16 prev;

    dx = 0;
    dz = 0;
    obj_aim_and_turn(obj, &obj->vars.s06_helicopter.aim_angle, 0x10, 8);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    obj_snap_to_ground(obj);
    /* halfword countdown at 0x264; when it goes negative, it reloads to 4 */
    timer = (u16 *)&obj->vars.s06_helicopter.countdown_timer;
    prev = *timer;
    *timer = prev - 1;
    if ((s16)prev < 0) {
        if (obj->vars.s06_helicopter.timer > 0) {
            fighter_jet_rocket_update(obj);
        }
        *timer = 4;
    }
}

extern Vec4 D_800B5D9C;
void obj_play_pos_sound(Object *obj, s32 *pos);
/* Stops the loop sound, moves the object by its heading and speed, and every 0x78 frames
 * samples the flow of its source object (its vars block and position) and
 * pushes the position from it. Timer at 0x262 is vars.enemy.unk_260[2]. */
void obj_move_sample_flow(Object *obj) {
    Vec4 pos;
    s32 dx;
    s32 dz;
    u8 handle;
    u16 timer;
    Object *parent;

    pos = D_800B5D9C;
    dx = 0;
    dz = 0;
    handle = ((ObjSoundBytes *)obj)->sound_1;
    if (handle != 0) {
        sound_stop(handle);
        ((ObjSoundBytes *)obj)->sound_1 = 0;
    }
    obj_aim_and_turn(obj, &obj->vars.s06_helicopter.aim_angle, 0x10, 8);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    obj_snap_to_ground(obj);
    timer = *(u16 *)&obj->vars.enemy.unk_260[2];
    *(u16 *)&obj->vars.enemy.unk_260[2] = timer - 1;
    if ((s16)timer < 0) {
        parent = obj->vars.pushed.source;
        flow_sample((Flow *)&parent->vars, obj->width, &parent->x, pos.v, &obj->turn);
        pos.v[0] = pos.v[0] >> 12;
        pos.v[1] = pos.v[1] >> 12;
        pos.v[2] = pos.v[2] >> 12;
        obj_play_pos_sound(obj, pos.v);
        *(u16 *)&obj->vars.enemy.unk_260[2] = 0x78;
    }
}

void obj_turn_bank(Object *obj) {
    u8 *sound_handle;
    s32 dx;
    s32 dz;

    dx = 0;
    dz = 0;
    /* byte 0x271 (inside vars.enemy.sound): the sound handle, stopped and cleared */
    sound_handle = (u8 *)obj + 0x271;
    if (*sound_handle != 0) {
        sound_stop(*sound_handle);
        *sound_handle = 0;
    }
    if (obj->roll > 0) {
        obj->yaw += 8;
        obj->vars.h.unk_258 += 0x10;
    } else {
        obj->yaw -= 8;
        obj->vars.h.unk_258 -= 0x10;
    }
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    obj->vy = 0x3000;
}

void s06_helicopter_update(Object *obj, ObjHandler *handler) {
    s32 *pos;
    s32 *vel;
    s32 speed;

    obj->vz = 0;
    obj->vx = 0;
    if (obj->vars.heli.flow_timer > 0) {
        vel = &obj->vx;
        pos = &obj->x;
        ((Flow *)&obj->vars.heli.source->vars)->speed = get_flow_max();
        flow_sample((Flow *)&obj->vars.heli.source->vars, obj->width, pos, vel, &obj->turn);
        speed = obj->speed;
        flier_strafe_hold_range((s16 *)&obj->vars.heli.source->vars, pos, vel, speed, 0x500,
                                obj->next_state);
    }
    obj_script_step(obj, handler);
    if (obj->blocked_z != 0) {
        obj->score = 0;
        obj->health = -1;
    }
    obj_ease_pitch(obj, 4, 0x100);
    obj_lean_into_turn(obj, &obj->vars.heli.prev_yaw, 4, 0x100);
    obj->vars.heli.part1_yaw += 8;
    obj->vars.heli.part2_yaw -= 8;
    obj->vars.heli.part3_yaw += 0x200;
    obj->vars.heli.unk_24C += 8;
    obj->vars.heli.flow_timer = obj->vars.heli.flow_timer - 1;
}

/* Draws the helicopter as effect-list records: the body (model `model`) and its three rotor parts (models
 * model + 3, model + 3 and model + 4); the first two only every other frame (blink toggles) or while paused.
 * Then fires effect 2 from the object's position. Same shape as minicopter_draw. */
void s06_helicopter_draw(Object *obj) {
    Vec3 pos;
    SVECTOR rot;
    SVECTOR aim;
    SVECTOR body;
    Vec3 part1_pos;
    SVECTOR part1_rot;
    Vec3 part2_pos;
    SVECTOR part2_rot;
    Vec3 part3_pos;
    SVECTOR part3_rot;
    Vec3 part_off[3];
    SVECTOR unused; /* never touched; only keeps the original 0xD0 frame */
    s32 pitch;
    s32 roll;
    s16 roll16;
    s32 model;
    s32 colour;

    /* the order of these stores and loads follows the original (loads and stack stores don't reorder) */
    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    part_off[0].x = 0;
    pos.z = obj->z >> 12;
    part_off[0].y = -0x15E;
    pitch = obj->pitch;
    part_off[0].z = 0x32;
    part_off[1].x = 0;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    part_off[1].y = -0xDA;
    part_off[1].z = 0x32;
    part_off[2].x = 0;
    part_off[2].y = -0xDA;
    part_off[2].z = 0x32;
    roll = obj->roll;
    roll16 = roll;
    rot.vz = roll16;
    /* the body keeps the object's pitch and roll but turns by unk_258 instead of the yaw */
    body.vy = obj->vars.heli.body_yaw;
    body.vz = rot.vz;
    body.vx = rot.vx;
    vec3_rotate(body.vy, body.vx, body.vz, &part_off[0].x, &part_off[0].y, &part_off[0].z);
    part1_pos.x = part_off[0].x + pos.x;
    part1_pos.y = part_off[0].y + pos.y;
    part1_pos.z = part_off[0].z + pos.z;
    part1_rot.vy = obj->vars.heli.part1_yaw;
    part1_rot.vx = 0;
    part1_rot.vz = 0;
    rot_compose_base_yaw(&body, &part1_rot);
    vec3_rotate(body.vy, body.vx, body.vz, &part_off[1].x, &part_off[1].y, &part_off[1].z);
    part2_pos.x = part_off[1].x + pos.x;
    part2_pos.y = part_off[1].y + pos.y;
    part2_pos.z = part_off[1].z + pos.z;
    part2_rot.vy = obj->vars.heli.part2_yaw;
    part2_rot.vx = 0;
    part2_rot.vz = 0;
    rot_compose_base_yaw(&body, &part2_rot);
    vec3_rotate(body.vy, body.vx, body.vz, &part_off[2].x, &part_off[2].y, &part_off[2].z);
    part3_pos.x = part_off[2].x + pos.x;
    part3_pos.y = part_off[2].y + pos.y;
    part3_pos.z = part_off[2].z + pos.z;
    part3_rot.vy = obj->vars.heli.part3_yaw;
    part3_rot.vx = 0;
    part3_rot.vz = 0;
    rot_compose_base_yaw(&body, &part3_rot);
    model = obj_keyframe_value(obj, 0);
    colour = 0;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
        pitch = 0; /* dead store, as in the sibling draw functions; keeps GCC from if-converting colour */
    }
    spark_add(pos.x, pos.y, pos.z, body.vy, body.vx, body.vz, model, colour);
    obj->vars.heli.blink ^= 1;
    if (obj->vars.heli.blink == 0 || is_paused()) {
        spark_add(part1_pos.x, part1_pos.y, part1_pos.z, part1_rot.vy, part1_rot.vx, part1_rot.vz, model + 3, colour);
        spark_add(part2_pos.x, part2_pos.y, part2_pos.z, part2_rot.vy, part2_rot.vx, part2_rot.vz, model + 3, colour);
    }
    spark_add(part3_pos.x, part3_pos.y, part3_pos.z, part3_rot.vy, part3_rot.vx, part3_rot.vz, model + 4, colour);
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    aim.vx = 0x300;
    aim.vy = obj->height;
    aim.vz = 0x300;
    aim_marker_draw(2, &aim, &pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

s32 obj_is_near_ground(Object *obj, s32 range) {
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s32 dy;
    s32 ret;

    ret = 0;
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    to[0] = obj->x >> 12;
    to[1] = (obj->y >> 12) + 0xBB8;
    to[2] = obj->z >> 12;
    trace_world(8, 0x10, from, to, hit);
    dy = from[1] - hit[1];
    if (dy >= 0 ? dy < range : hit[1] - from[1] < range) {
        ret = 1;
    }
    return ret;
}

s32 helicopter_fx_update(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 off_x, off_y, off_z;
    s32 rnd;
    s32 pitch;

    off_x = rand_a_next() % 512;
    off_y = rand_a_next() % 256;
    rnd = rand_a_next();
    off_z = rnd % 512;
    obj->unk_17A = 0;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    obj->next_state = 3;
    rot[1] = obj->vars.h.unk_258;
    vec3_rotate(rot[1], rot[0], rot[2], &off_x, &off_y, &off_z);
    if (obj->vars.s06_helicopter.fx_timer-- > 0) {
        spawn_effect(pos[0] + off_x, pos[1] - off_y, pos[2] + off_z, 0x80007F01);
        spawn_effect(pos[0] - off_x, pos[1] - off_y, pos[2] - off_z, 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0x80007F00);
        spawn_effect(pos[0], pos[1] - 0x300, pos[2], 0x80000000);
        spawn_effect(pos[0], pos[1] - 0x380, pos[2], 0x80007F02);
    }
    {
        s32 chance = rand_a_next();
        if (chance % 5 == 0) {
            if (obj->vars.trace.active == 0) {
                spawn_effect(pos[0] + off_x, pos[1] - off_y, pos[2] + off_z, 0x80007F00);
            } else {
                spawn_effect(pos[0] - off_x, pos[1] - off_y, pos[2] - off_z, 0x80000000);
            }
        }
    }
    if (obj_is_near_ground(obj, 0x12C) || (s16)(*(u16 *)&obj->vars.s06_helicopter.explosion_timer)-- < 0) {
        spawn_effect(pos[0] + off_x, pos[1] - off_y, pos[2] + off_z, 0x80007F01);
        spawn_effect(pos[0] - off_x, pos[1] - off_y, pos[2] - off_z, 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0x80007F00);
        spawn_effect(pos[0], pos[1] - 0x300, pos[2], 0x80000000);
        spawn_effect(pos[0], pos[1] - 0x380, pos[2], 0x80007F02);
        obj_effect_send_pos(obj);
        placement_list_pop((ListRecord *)obj->placement);
        ((u8 *)obj->placement)[4] = (((u8 *)obj->placement)[4] & 0xFC) | 2;
        obj_free(obj->vars.pushed.source);
        return 0;
    }
    return 1;
}

extern Vec3 rocket_sound_pos;

/* Sound-position callback: the object's position plus (0, 0x50, 0x28A) rotated by its angles,
 * stored in rocket_sound_pos and returned. */
void *rocket_sound_position(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *ang;
    Vec3 *dst;
    s32 offs_x = 0;
    s32 offs_y = 0x50;
    s32 offs_z = 0x28A;
    s32 neg;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    ang = (SVECTOR *)scratch_top;
    neg = -obj->pitch;
    ang->vx = neg;
    ang->vy = obj->yaw;
    ang->vz = obj->roll;
    scratch_top += 8;
    ang->vy += obj->vars.h.unk_258;
    vec3_rotate(ang->vy, ang->vx, ang->vz, &offs_x, &offs_y, &offs_z);
    pos->x = (pos->x + offs_x) << 12;
    pos->y = (pos->y + offs_y) << 12;
    pos->z = (pos->z + offs_z) << 12;
    dst = &rocket_sound_pos;
    dst->x = pos->x;
    dst->y = pos->y;
    dst->z = pos->z;
    scratch_top -= 0x18;
    return dst;
}

void fighter_jet_rocket_update(Object *obj) {
    Vec4 origin;
    s32 pos[3];
    s16 rot[3];
    u16 aim[3];
    s32 spawn[3];
    s32 offset[3];
    s32 rnd;
    s16 aim_yaw;
    s32 pitch;
    u8 sound;

    origin = D_800B5D9C;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    offset[0] = 0;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    offset[1] = 0x50;
    rot[2] = obj->roll;
    offset[2] = 0x28A;
    rnd = rand_a_next();
    aim_yaw = obj->vars.h.unk_258 - 0xA;
    aim_yaw += rnd % 0x14;
    aim[0] = rot[0];
    aim[1] = aim_yaw;
    aim[2] = rot[2];
    vec3_rotate(aim_yaw, (s16)rot[0], (s16)rot[2], &offset[0], &offset[1], &offset[2]);
    spawn[0] = offset[0] + pos[0];
    spawn[1] = offset[1] + pos[1];
    spawn[2] = offset[2] + pos[2];
    shot_spawn_target(spawn, aim, origin.v, 1, obj->damage << 16);
    if (((ObjSoundBytes *)obj)->sound_1 == 0) {
        sound = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        ((ObjSoundBytes *)obj)->sound_1 = sound;
        sound_attach(sound & 0xFF, obj, (void (*)())rocket_sound_position);
        sound_set_flag_bit2(((ObjSoundBytes *)obj)->sound_1, 1);
    }
}

extern GunSetup shot_twin_desc;
void obj_play_pos_sound(Object *obj, s32 *pos) {
    u8 *raw;
    s32 origin[3];
    s16 angles_a[3];
    s16 angles_b[3];
    s32 point_a[3];
    s32 point_b[3];
    s32 offsets[6];
    s32 pitch;
    s32 neg_pitch;
    s32 unused[2];
    s16 roll_s16;
    s32 roll;
    s32 yaw;

    raw = (u8 *)obj;
    offsets[0] = 0x122;
    offsets[1] = 0x64;
    offsets[2] = -0x14;
    offsets[3] = -0x122;
    offsets[4] = 0x64;
    offsets[5] = -0x14;
    get_model_slot_base();
    origin[0] = *(s32 *)(raw + 0x1F0) >> 12;
    origin[1] = *(s32 *)(raw + 0x1F4) >> 12;
    origin[2] = *(s32 *)(raw + 0x1F8) >> 12;
    pitch = *(s16 *)(raw + 0x222);
    neg_pitch = -pitch;
    angles_a[0] = neg_pitch;
    angles_a[1] = *(u16 *)(raw + 0x220);
    roll = *(s16 *)(raw + 0x224);
    roll_s16 = roll;
    angles_a[2] = roll_s16;
    yaw = *(u16 *)(raw + 0x258);
    angles_b[2] = roll_s16;
    angles_b[0] = neg_pitch;
    angles_b[1] = yaw;
    vec3_rotate((s16)yaw, (s16)neg_pitch, roll, &offsets[0], &offsets[1], &offsets[2]);
    vec3_rotate(angles_b[1], angles_b[0], angles_b[2], &offsets[3], &offsets[4], &offsets[5]);
    point_a[0] = offsets[0] + origin[0];
    point_a[1] = offsets[1] + origin[1];
    point_a[2] = offsets[2] + origin[2];
    point_b[0] = offsets[3] + origin[0];
    point_b[1] = offsets[4] + origin[1];
    point_b[2] = offsets[5] + origin[2];
    sound_play_at_units(SND_TWIN_SHOT_FIRE | SND_GROUP(1), 0x60, 0x3C, point_a);
    sound_play_at_units(SND_TWIN_SHOT_FIRE | SND_GROUP(1), 0x60, 0x3C, point_b);
    shot_spawn_target(point_a, (u16 *)angles_b, pos, 2, (s32)&shot_twin_desc);
    shot_spawn_target(point_b, (u16 *)angles_b, pos, 2, (s32)&shot_twin_desc);
}

/* Stops both sounds; the second handle is cleared once it has been stopped. */
void obj_stop_sounds(ObjSoundBytes *obj) {
    sound_stop(obj->sound_0);
    if (obj->sound_1 != 0) {
        sound_stop(obj->sound_1);
        obj->sound_1 = 0;
    }
}

extern u8 helicopter_asset[];
extern s16 *s06_helicopter_data[];
extern s16 *helicopter_script_table[];
extern StateEntry D_8011CA2C[];
extern ScriptCallEntry D_8011C9FC[];
extern s16 s06_helicopter_anim_idle[];
extern s16 *helicopter_script_start;
s32 helicopter_fx_update(Object *obj);
void s06_helicopter_update(Object *obj, ObjHandler *handler);
void s06_helicopter_draw(Object *obj);
Object *obj_spawn_at_player(void);
s32 s06_helicopter_spawn(Placement *place) {
    Object *obj = obj_new();
    u8 *o = (u8 *)obj;
    s32 y;
    s32 ang;
    u16 yaw;

    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(),&obj->node);
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *))obj_phase0_default;
    obj->handlers[1].fn = s06_helicopter_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = (ObjHandlerFn) s06_helicopter_draw;
    obj->callback = (s32)helicopter_fx_update;
    obj->asset = helicopter_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = D_8011C9FC;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->kind = 1;
    obj->state_table = D_8011CA2C;
    script_start((Script *)obj, s06_helicopter_anim_idle, (s32)s06_helicopter_data);
    obj->script.data = helicopter_script_table;
    obj->script.unk_0A = 0;
    obj->script.pc = helicopter_script_start;
    obj_init_from_place(obj, place, 0x37);
    obj->speed = 0x11;
    obj_set_part_bounds(obj, 0, 0x400);
    obj->vars.s06_helicopter.unused_248 = 0;
    ang = place->unk_1E;
    y = obj->y;
    yaw = obj->yaw;
    *(s16 *)(o + 0x25A) = 6;
    *(s16 *)(o + 0x262) = 0x78;
    *(s16 *)(o + 0x264) = 4;
    *(s16 *)(o + 0x266) = 0x20;
    *(s16 *)(o + 0x24C) = 0;
    *(s16 *)(o + 0x24E) = 0;
    *(s16 *)(o + 0x250) = 1;
    *(s16 *)(o + 0x25E) = 0;
    *(s16 *)(o + 0x260) = 0;
    *(s16 *)(o + 0x268) = 0x168;
    *(s16 *)(o + 0x24A) = ang * 0x3C;
    *(s32 *)(o + 0x254) = y;
    *(s16 *)(o + 0x258) = yaw;
    *(u16 *)(o + 0x25C) -= 7;
    *(Object **)(o + 0x26C) = obj_spawn_at_player();
    if (*(Object **)(o + 0x26C) == NULL) {
        return 0;
    }
    o[0x271] = 0;
    o[0x270] = sound_start(SND_HELICOPTER | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
    sound_attach(o[0x270], &obj->x, NULL);
    sound_set_flag_bit2(o[0x270], 1);
    obj->destructor = (void (*)(Object *))obj_stop_sounds;
    return 1;
}

void flier_strafe_to_target(SVECTOR *rot, s32 *pos, s32 speed) {
    s32 cur = ((s32 (*)(void))cam_angle_get)(); /* the original takes the result unextended */
    s32 target = rot->vy;
    s32 diff = target - cur;

    if (diff < 0) {
        diff = cur - target;
    }
    if (diff >= 0x100) {
        if (cur < target) {
            speed = -speed;
        }
        fly_strafe(rot->vz + 0x400, speed, pos + 2, pos);
    }
}

void flier_strafe_to_target(SVECTOR *rot, s32 *pos, s32 speed);
void flow_obj_update(Object *obj, ObjHandler *handler) {
    Flow *flow;
    s32 *pos;
    s32 *vel;
    s32 speed;

    ((Flow *)&obj->vars)->speed = get_flow_max();
    flow = (Flow *)&obj->vars;
    pos = &obj->x;
    vel = &obj->vx;
    flow_sample(flow, obj->width, pos, vel, &obj->turn);
    speed = obj->speed;
    flier_keep_range((s16 *)flow, pos, vel, speed, 0x300);
    flier_strafe_to_target((SVECTOR *)flow, vel, 0xC);
    obj->x += obj->vx;
    obj->y += obj->vy;
    obj->z += obj->vz;
}

void flow_obj_update(Object *obj, ObjHandler *handler);
Object *obj_spawn_at_player(void) {
    s32 *pos;
    Object *obj;

    pos = player_position();
    obj = obj_new();
    if (obj == NULL) {
        return NULL;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->handlers[1].fn = flow_obj_update;
    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = NULL;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->speed = 0x11;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    rec_reset((PartSlot *) &obj->vars);
    return obj;
}
