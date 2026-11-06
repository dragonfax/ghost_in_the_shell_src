/* minicopter: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

void enemy_loop_sound_attach(Object *obj) {
    s32 handle;

    if (obj->vars.minicopter.loop_sound_handle == 0) {
        handle = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        sound_attach(handle, &obj->x, NULL);
        obj->vars.minicopter.loop_sound_handle = handle;
    }
}

void enemy_loop_sound_halt(Object *obj) {
    if (obj->vars.minicopter.loop_sound_handle != 0) {
        sound_stop(obj->vars.minicopter.loop_sound_handle);
        obj->vars.minicopter.loop_sound_handle = 0;
    }
}


void script_read_speed(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->speed = *cursor;
}


/* Same code as func_800BC7AC (s01). */
void obj_script_read_state(Object *obj) {
    obj->next_state = obj_read_u16(obj);
}

/* Same code as func_800BC7C8 (s01). */
void obj_script_read_mode(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void obj_script_jump_if_near(Object *obj) {
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

/* Script step: advance the object's script pointer past one halfword opcode.
 * When the signed flag in vars.h is negative, the pointer is replaced by the
 * table entry for that opcode (the table is the type link's data). */
void script_step_op(Object *obj) {
    s16 *script;
    s32 op;

    script = obj->script.pc;
    obj->script.pc = script + 1;
    op = *script;
    if ((s16)obj->vars.minicopter.pursue_timer < 0) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
}

void minicopter_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}


/* Same code as flier_keep_range (s04). */
void flier_hold_range(s16 *actor, s32 *pos, s32 *out, s32 speed, s32 range) {
    s32 dx;
    s32 dz;
    s32 dist;
    s32 dir;

    dir = speed;
    dx = (cam_pos_z - pos[2]) >> 12;
    dz = (cam_pos - pos[0]) >> 12;
    if (((((atan2(dx, dz) - actor[2]) & 0xFFF) - 0x400) & 0xFFF) < 0x800) {
        dir = -dir;
    }
    dist = isqrt(length_sq(dz, 0, dx));
    if (dist < range - 0x40) {
        dir = -dir;
    } else if (dist < range) {
        return;
    }
    fly_strafe(actor[2], dir, out + 2, out);
}


/* Same code as obj_snap_to_ground (s06). */
void obj_snap_to_floor(Object *obj) {
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

/* Yaw is stepped by 0x10 per frame while vars.h.unk_24A is negative, with a snap to 0 outside both
 * ranges; unk_254 turns toward the player. Then fly_move and obj_step_axes_toward apply the step. */
void flier_chase_step(Object *obj) {
    s32 dx;
    s32 dz;
    s32 *player;
    s32 yaw;

    dx = 0;
    dz = 0;
    enemy_loop_sound_halt(obj);
    if ((s16)obj->vars.minicopter.pursue_timer < 0) {
        yaw = (u16)obj->yaw;
        if ((u32)(yaw - 1) < 0x7FF) {
            obj->yaw = yaw - 0x10;
        } else if ((u32)(yaw - 0x801) < 0x7FF) {
            obj->yaw = yaw + 0x10;
        } else {
            obj->yaw = 0;
        }
        player = player_position();
        obj->vars.minicopter.yaw = angle_approach(obj->vars.minicopter.yaw,
            atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)), 0x20);
        obj->speed += 1;
    } else {
        obj_aim_and_turn(obj, &obj->vars.minicopter.yaw, 0x20, 8);
    }
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
}

void fly_pursue_player(Object *obj, s32 unused) {
    s32 fly_dx;
    s32 fly_dz;
    s32 *player;
    s32 idx;

    fly_dx = 0;
    fly_dz = 0;
    player = player_position();

    obj->vars.minicopter.yaw = angle_approach(obj->vars.minicopter.yaw,
        atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)), 0x10);

    idx = obj->vars.minicopter.weave_angle & 0xFFF;
    obj->yaw = angle_approach(obj->yaw,
        atan2(player[2] - (obj->z >> 12),
              (player[0] + cos_table[idx].value) - (obj->x >> 12)), 0x10);

    fly_move(obj->yaw, obj->speed, &fly_dx, &fly_dz);
    obj->vx += fly_dz;
    obj->vars.minicopter.pursue_timer = obj->vars.minicopter.pursue_timer - 1;
}

void fly_pursue_player(Object *obj, s32 unk_a1);
void fly_pursue_update(Object *obj, s32 unk_a1) {
    enemy_loop_sound_halt(obj);
    fly_pursue_player(obj, unk_a1);
}

Vec4 D_800B5D9C = {0};
char str_fap1_tp1_clt[16] = "fap1_tp1.clt";

char str_fap1_tp0_clt[16] = "fap1_tp0.clt";

char str_fap1_ch0_clt[16] = "fap1_ch0.clt";

char str_fap1_tp1_xs3[16] = "fap1_tp1.xs3";

char str_fap1_tp0_xs3[16] = "fap1_tp0.xs3";

char str_fap1_ch0_vx1[16] = "fap1_ch0.vx1";

char str_fap1_ch0cb4[16] = "fap1_ch0.cb4";

void flier_fire_at_target(Object *obj, s32 *target);
/* Pursues the player; when the fire countdown runs out, samples the flow for an aim point
 * and fires at it, then waits 4 more steps. */
void copter_update(Object *obj, s32 unk_a1) {
    s32 aim[4] = {0, 0, 0, 0};

    fly_pursue_player(obj, unk_a1);
    if (obj->vars.copter.fire_delay-- < 0) {
        flow_sample(&obj->vars.copter.current, obj->width, &obj->x, aim, &obj->turn);
        aim[0] >>= 12;
        aim[1] >>= 12;
        aim[2] >>= 12;
        flier_fire_at_target(obj, aim);
        obj->vars.copter.fire_delay = 4;
    }
}

/* Tank model files a data table points to by address; they follow this function's constant. */
const char file_tnk2_tp0_clt[] = "tnk2_tp0.clt";
const char file_tnk2_ch0_clt[] = "tnk2_ch0.clt";
const char file_tnk2_tp0_xs3[] = "tnk2_tp0.xs3";
const char file_tnk2_ch0_vx1[] = "tnk2_ch0.vx1";
const char file_tnk2_ch0_cb4[] = "tnk2_ch0.cb4";

/* Samples the flow into the step, holds range while vars.h.unk_24A is positive, runs the script,
 * snaps to the ground and eases pitch and yaw; then advances the rotor animation counters. */
void minicopter_update(Object *obj, ObjHandler *handler) {
    Flow *flow;
    s32 *pos;
    s32 *move;
    s32 speed;

    obj->vz = 0;
    obj->vx = 0;
    obj->vars.copter.current.speed = get_flow_max();
    flow = &obj->vars.copter.current;
    pos = &obj->x;
    move = &obj->vx;
    flow_sample(flow, obj->width, pos, move, &obj->turn);
    obj->yaw += obj->turn;
    if ((s16)obj->vars.minicopter.pursue_timer > 0) {
        speed = obj->speed;
        flier_hold_range((s16 *)flow, pos, move, speed, 0x300);
    }
    obj_script_step(obj, handler);
    if (obj->blocked_z != 0) {
        obj->score = 0;
        obj->health = -1;
    }
    obj_snap_to_floor(obj);
    obj_ease_pitch(obj, 4, 0x100);
    obj_lean_into_turn(obj, &obj->vars.minicopter.prev_yaw, 8, 0x100);
    obj->vars.minicopter.part1_angle += 8;
    obj->vars.minicopter.part2_angle -= 8;
    obj->vars.minicopter.part3_angle += 0x200;
    obj->vars.minicopter.weave_angle += 0x12;
}

void minicopter_destructor(Object *obj) {
    enemy_loop_sound_halt(obj);
    sound_stop(obj->vars.minicopter.spawn_sound_handle);
}

void minicopter_phase0(Object *obj, ObjHandler *handler);
void minicopter_update(Object *obj, ObjHandler *handler);
void minicopter_draw(Object *obj);
s32 obj_explode(Object *obj);
extern s16 *minicopter_data[];
extern s16 minicopter_script[4];
extern s32 minicopter_asset[3];
extern ScriptCallEntry minicopter_call_table[6];
extern StateEntry minicopter_states[4];
extern s16 *minicopter_script_start;
extern s16 *minicopter_script_ops[];
/* Spawns a minicopter from a placement; returns 1 if the object was made. */
s32 minicopter_spawn(Placement *place) {
    Object *obj;
    PartSlot *rec;
    s32 rate;
    s32 pos_y;
    u16 yaw;
    s32 sound;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[0].fn = (ObjHandlerFn) minicopter_phase0;
    obj->handlers[1].fn = (ObjHandlerFn) minicopter_update;
    obj->handlers[2].fn = (ObjHandlerFn) obj_run_states_default;
    obj->handlers[3].fn = (ObjHandlerFn) minicopter_draw;
    obj->callback = (s32) &obj_explode;
    obj->destructor = minicopter_destructor;
    obj->kind = 1;
    obj->asset = minicopter_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = minicopter_call_table;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->state_table = minicopter_states;
    script_start((Script *) obj, minicopter_script, (s32) &minicopter_data);
    obj->script.data = minicopter_script_ops;
    obj->script.unk_0A = 0;
    obj->script.pc = minicopter_script_start;
    obj_init_from_place(obj, place, 0x37);
    obj->speed = 8;
    obj_set_part_bounds(obj, 0, 0x800);
    rec = (PartSlot *) &obj->vars.minicopter.part_slot;
    obj->vars.minicopter.weave_angle = 0;
    rate = place->unk_1E;
    pos_y = obj->y;
    yaw = (u16) obj->yaw;
    obj->vars.minicopter.part1_angle = 6;
    obj->vars.minicopter.draw_toggle = 0;
    obj->vars.minicopter.part3_angle = 0;
    obj->vars.enemy.unk_25C = 0;
    obj->vars.enemy.unk_25E = 4;
    obj->vars.minicopter.pursue_timer = rate * 0x3C;
    obj->vars.minicopter.base_y = pos_y;
    obj->vars.enemy.sound_channel[0] = yaw;
    obj->vars.minicopter.part2_angle -= 7;
    rec_reset(rec);
    sound = sound_start(SND_MINICOPTER_ROTOR_LOOP | SND_HELD | SND_GROUP(2), 0x40, 0, 0);
    sound_attach(sound, &obj->x, 0);
    sound_set_flag_bit2(sound, 1);
    obj->vars.minicopter.spawn_sound_handle = (u8) sound;
    obj->vars.minicopter.loop_sound_handle = 0;
    return 1;
}

/* Draws the minicopter as effect-list records: the body (model `model`) and its three rotor parts (models
 * model + 3, model + 3 and model + 4). The first two parts are only drawn on every other frame (unk_24C
 * toggles), or while the game is paused. Then fires effect 2 from the object's position. */
void minicopter_draw(Object *obj) {
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
    part_off[0].y = -0x8C;
    pitch = obj->pitch;
    part_off[0].z = 0x14;
    part_off[1].x = 0;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    part_off[1].y = -0x5A;
    part_off[1].z = 0x14;
    part_off[2].x = 0;
    part_off[2].y = -0x8C;
    part_off[2].z = 0x14;
    roll = obj->roll;
    roll16 = roll;
    rot.vz = roll16;
    /* the body keeps the object's pitch and roll but turns by unk_254 instead of the yaw */
    body.vy = obj->vars.minicopter.yaw;
    body.vz = rot.vz;
    body.vx = rot.vx;
    vec3_rotate(body.vy, body.vx, body.vz, &part_off[0].x, &part_off[0].y, &part_off[0].z);
    part1_pos.x = part_off[0].x + pos.x;
    part1_pos.y = part_off[0].y + pos.y;
    part1_pos.z = part_off[0].z + pos.z;
    part1_rot.vy = obj->vars.minicopter.part1_angle;
    part1_rot.vx = 0;
    part1_rot.vz = 0;
    rot_compose_base_yaw(&body, &part1_rot);
    vec3_rotate(body.vy, body.vx, body.vz, &part_off[1].x, &part_off[1].y, &part_off[1].z);
    part2_pos.x = part_off[1].x + pos.x;
    part2_pos.y = part_off[1].y + pos.y;
    part2_pos.z = part_off[1].z + pos.z;
    part2_rot.vy = obj->vars.minicopter.part2_angle;
    part2_rot.vx = 0;
    part2_rot.vz = 0;
    rot_compose_base_yaw(&body, &part2_rot);
    vec3_rotate(body.vy, body.vx, body.vz, &part_off[2].x, &part_off[2].y, &part_off[2].z);
    part3_pos.x = part_off[2].x + pos.x;
    part3_pos.y = part_off[2].y + pos.y;
    part3_pos.z = part_off[2].z + pos.z;
    part3_rot.vy = obj->vars.minicopter.part3_angle;
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
    obj->vars.minicopter.draw_toggle ^= 1;
    if (obj->vars.minicopter.draw_toggle == 0 || is_paused()) {
        spark_add(part1_pos.x, part1_pos.y, part1_pos.z, part1_rot.vy, part1_rot.vx, part1_rot.vz, model + 3, colour);
        spark_add(part2_pos.x, part2_pos.y, part2_pos.z, part2_rot.vy, part2_rot.vx, part2_rot.vz, model + 3, colour);
    }
    spark_add(part3_pos.x, part3_pos.y, part3_pos.z, part3_rot.vy, part3_rot.vx, part3_rot.vz, model + 4, colour);
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    aim.vx = obj->width;
    aim.vy = obj->height;
    aim.vz = obj->unk_1E8[0];
    aim_marker_draw(2, &aim, &pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

s32 obj_explode(Object *obj) {
    s32 pos[3];
    struct { s16 x; u16 y; u16 z; } rot;
    s32 off[3];
    Placement *place;
    u16 t;
    s32 pitch;
    s32 r;
    s32 adj;

    off[0] = rand_a_next() % 0x200;
    off[1] = rand_a_next() % 0x100;
    r = rand_a_next();
    adj = r;
    if (r < 0) {
        adj = r + 0x1FF;
    }
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot.x = -pitch;
    rot.y = obj->yaw;
    rot.z = obj->roll;
    off[2] = r - ((adj >> 9) << 9);
    obj->next_state = 3;
    t = obj->vars.minicopter.yaw;
    rot.y = t;
    vec3_rotate((s16) t, rot.x, (s16) rot.z, &off[0], &off[1], &off[2]);
    spawn_effect(pos[0] + off[0], pos[1] - off[1], pos[2] + off[2], 1);
    spawn_effect(pos[0] - off[0], pos[1] - off[1], pos[2] - off[2], 1);
    spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0);
    spawn_effect(pos[0], pos[1] - 0x300, pos[2], 0);
    spawn_effect(pos[0], pos[1] - 0x380, pos[2], 2);
    placement_list_pop((ListRecord *) obj->placement);
    place = obj->placement;
    place->unk_00[4] = (place->unk_00[4] & 0xFC) | 2;
    return 0;
}

void flier_fire_at_target(Object *obj, s32 *target) {
    s32 base_pos[3];
    u16 angles[3];
    u16 spawn_rot[3];
    s32 spawn_pos[3];
    s32 offset[3];
    s32 pitch;
    s32 rnd;
    s32 jitter;

    base_pos[0] = obj->x >> 12;
    base_pos[1] = obj->y >> 12;
    base_pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    offset[0] = 0;
    angles[0] = -pitch;
    angles[1] = obj->yaw;
    offset[1] = 0x50;
    angles[2] = obj->roll;
    offset[2] = 0xFA;
    rnd = rand_a_next();
    jitter = (u16)obj->vars.minicopter.yaw - 10;
    spawn_rot[0] = angles[0];
    spawn_rot[1] = jitter + rnd % 20;
    spawn_rot[2] = angles[2];
    vec3_rotate((s16)spawn_rot[1], (s16)angles[0], (s16)angles[2], &offset[0], &offset[1], &offset[2]);
    spawn_pos[0] = offset[0] + base_pos[0];
    spawn_pos[1] = offset[1] + base_pos[1];
    spawn_pos[2] = offset[2] + base_pos[2];
    enemy_loop_sound_attach(obj);
    shot_spawn_target(spawn_pos, spawn_rot, target, 1, obj->damage << 16);
}
