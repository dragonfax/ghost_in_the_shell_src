/* helicopter: one of the original source files (scripts/objmap.py); s01, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

void script_op_jump_table_if_player_far(Object *obj) {
    s32 limit;
    s16 *cursor;
    s32 threshold;
    s32 index;

    limit = (s16) obj_player_dist_whole(obj);
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Reads the next script halfword (cursor at +0x20). While the flag at enemy.unk_266 is 1, it clears the flag
 * and the cursor jumps to the entry of the type's table (+0x1C) that the halfword selects. */
void script_op_jump_clear_flag(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if (obj->vars.enemy.unk_266 == 1) {
        obj->vars.enemy.unk_266 = 0;
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void helicopter_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

/* Calls obj_set_fall_speed with mode 4 (and 1000 less) when the object has both flags set, else mode 2. */
void script_op_seek_target(Object *obj, s32 arg) {
    s32 value = arg;

    if (obj->unk_242 != 0 && *(u16 *)&obj->blocked_z != 0) {
        obj_set_fall_speed(obj, 4, value - 1000);
    } else {
        obj_set_fall_speed(obj, 2, value);
    }
}

#if STAGE == 12
void script_op_seek_target(Object *obj, s32 arg);
#endif

/* Behaviour step of a flying shooting enemy that stops its loop sound, moves along its heading and
 * (in area 11 it can skip one axis) is pushed out of walls by obj_step_axes_toward. */
void enemy_fly_move(Object *obj) {
    s32 dz;
    s32 dx;
    s32 height;
    s32 sound;

    dz = 0;
    dx = 0;
    height = obj->vars.helicopter.spawn_y >> 12;
    sound = obj->vars.helicopter.fly_sound_handle;
    if (sound != 0) {
        sound_stop(sound);
        obj->vars.helicopter.fly_sound_handle = 0;
    }
    obj->unk_1B7 = 0;
    if (obj->unk_242 == 0) {
        obj_aim_and_turn(obj, &obj->vars.enemy.unk_250, 0x10, 8);
    } else {
        obj_aim_and_turn(obj, &obj->vars.enemy.unk_250, 4, 4);
    }
    fly_move(obj->yaw, obj->speed, &dz, &dx);
    if (get_area() / 3 != 11) {
        obj_step_axes_toward(obj, dx, dz);
        script_op_seek_target(obj, height);
    } else if (*(s16 *)&obj->vars.enemy.unk_260[4] == 0) {
        obj_step_axes_toward(obj, 0, dz);
        script_op_seek_target(obj, height);
    } else {
        obj_step_axes_toward(obj, dx, 0);
    }
}

/* Behaviour step of a flying shooting enemy (S01). */
void enemy_fly_aim(Object *obj) {
    s32 dz;
    s32 dx;
    s32 target_yaw;
    s32 target_pitch;
    s32 ground;
    s32 limit;
    s32 *player;
    s32 dist_x;
    s32 dist_y;
    s32 dist_z;
    u16 timer;

    ground = cam_pos_y >> 12;
    limit = ground - 0x2BC;
    dz = 0;
    dx = 0;
    obj->unk_1B7 = 0;
    obj_aim_and_turn(obj, &obj->vars.enemy.unk_250, 0x10, 8);
    fly_move(obj->yaw, obj->speed, &dz, &dx);
    if (get_area() / 3 != 11) {
        obj_step_axes_toward(obj, dx, dz);
        obj_set_fall_speed(obj, 2, ground - 0x28A);
    } else {
        player = player_position();
        dist_z = player[2] - (obj->z >> 12);
        dist_x = player[0] - (obj->x >> 12);
        dist_y = player[1] - (obj->y >> 12);
        vector_to_angles(dist_x, dist_y, dist_z, &target_yaw, &target_pitch);
        if ((u32)(target_pitch - 0x100) >= 0xE01) {
            obj->pitch = angle_approach(obj->pitch, target_pitch, 8);
        }
        if (*(s16 *)&obj->vars.enemy.unk_260[4] == 0) {
            obj_step_axes_toward(obj, 0, dz);
            obj_set_fall_speed(obj, 2, ground - 0x28A);
        } else {
            obj_step_axes_toward(obj, dx, 0);
        }
    }
    if (obj->vars.helicopter.unk_25E >= 0x801 && obj_player_in_arc(obj, *(s16 *)&obj->vars.enemy.unk_250, 0x100) == 1 &&
        limit < (obj->y >> 12)) {
        timer = obj->vars.helicopter.fire_countdown;
        obj->vars.helicopter.fire_countdown = timer - 1;
        if ((s16)timer < 0) {
            enemy_fly_fire(obj);
            obj->vars.helicopter.fire_countdown = 4;
        }
    } else if (obj->vars.helicopter.fly_sound_handle != 0) {
        sound_stop(obj->vars.helicopter.fly_sound_handle);
        obj->vars.helicopter.fly_sound_handle = 0;
    }
    if (obj->vars.helicopter.unk_25E >= 0x1001) {
        obj->vars.helicopter.unk_25E = 0;
    }
    obj->vars.helicopter.unk_25E += 0x40;
}

/* Behaviour step of another flying enemy (S01), like enemy_fly_aim. */
void enemy_fly_approach(Object *obj) {
    s32 dz;
    s32 dx;
    s32 ground;
    s32 limit;
    u16 timer;

    dz = 0;
    dx = 0;
    ground = cam_pos_y >> 12;
    limit = ground - 0x2BC;
    if (obj->vars.helicopter.fly_sound_handle != 0) {
        sound_stop(obj->vars.helicopter.fly_sound_handle);
        obj->vars.helicopter.fly_sound_handle = 0;
    }
    obj->unk_1B7 = 0;
    obj_aim_and_turn(obj, &obj->vars.enemy.unk_250, 0x10, 8);
    fly_move(obj->yaw, obj->speed, &dz, &dx);
    if (get_area() / 3 != 11) {
        obj_step_axes_toward(obj, dx, dz);
        obj_set_fall_speed(obj, 2, ground - 0x2EE);
    } else if (*(s16 *)&obj->vars.enemy.unk_260[4] == 0) {
        obj_step_axes_toward(obj, 0, dz);
        obj_set_fall_speed(obj, 2, ground - 0x2EE);
    } else {
        obj_step_axes_toward(obj, dx, 0);
    }
    if (obj_player_in_arc(obj, *(s16 *)&obj->vars.enemy.unk_250, 0x100) == 1 &&
        (*(s16 *)&obj->vars.enemy.unk_260[4] != 0 || (obj->y >> 12) < limit)) {
        timer = obj->vars.helicopter.timer;
        obj->vars.helicopter.timer = timer - 1;
        if ((s16)timer < 0) {
            obj_sound_pair_play(obj);
            obj->vars.helicopter.timer = 0x78;
        }
    }
}

void enemy_fly_spin(Object *obj) {
    s32 dx;
    s32 dz;

    dx = 0;
    dz = 0;
    if (obj->vars.helicopter.fly_sound_handle != 0) {
        sound_stop(obj->vars.helicopter.fly_sound_handle);
        obj->vars.helicopter.fly_sound_handle = 0;
    }
    if (obj->roll > 0) {
        obj->yaw += 8;
        obj->vars.helicopter.yaw += 0x10;
    } else {
        obj->yaw -= 8;
        obj->vars.helicopter.yaw -= 0x10;
    }
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    if (get_area() / 3 != 11) {
        obj_step_axes_toward(obj, dz, dx);
    } else if (*(s16 *)&obj->vars.helicopter.unk_264 == 0) {
        obj_step_axes_toward(obj, 0, dx);
    } else {
        obj_step_axes_toward(obj, dz, 0);
    }
    obj->vy = 0x3000;
}

#if STAGE == 12
void obj_ease_pitch(Object *obj, s16 step, s16 limit);
#endif

/* Per-frame update: scrolls two texture coordinates, tracks the position's cell and a timer. */
void helicopter_update(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    u16 *timer = (u16 *)obj->vars.enemy.unk_260;

    obj->vz = 0;
    obj->vx = 0;
    ((void (*)(Object *))obj_script_step)(obj); /* the original leaves a1 as it is */
    obj_ease_pitch(obj, 4, 0x100);
    obj_lean_into_turn(obj, &obj->vars.enemy.unk_258, 4, 0x100);
    obj->vars.helicopter.unk_252 += 8;
    obj->vars.helicopter.unk_254 -= 8;
    obj->vars.helicopter.unk_256 += 0x200;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    if (cam_range_check(pos->x, pos->y, pos->z)) {
        *timer -= 1;
        if ((s16)*timer < 0) {
            if (obj->next_state != 3) {
                obj_spawn_ripple(obj, 0x300, 0x580);
                *timer = 0x20;
            }
        }
    }
    scratch_top -= 0x10;
    if ((s16)obj_hit_damage(obj->index) > 0) {
        obj->vars.enemy.unk_266 = 1;
    }
}

/* Runs obj_run_states_default with the object raised by 0x78000 (y negative is up). */
void helicopter_phase2(Object *obj, ObjHandler *handler) {
    obj->y -= 0x78000;
    obj_run_states_default(obj, handler);
    obj->y += 0x78000;
}

#if STAGE == 12
extern s16 helicopter_script[];
extern s16 helicopter_data[];
void helicopter_update();
void helicopter_phase2();
void helicopter_draw();
s32 helicopter_crash(Object *obj);
extern s32 helicopter_asset_slot[3];
extern u8 D_801178BC[], D_801178F4[], D_80117890[];
extern u8 D_801176B8[], D_801178F4[], D_80117890[];
extern ScriptCallEntry d_801178BC[];
extern StateEntry helicopter_slot_table[];
extern s16 *helicopter_script_entry;
extern u8 D_801176B8[], D_801178BC[], D_801178F4[];
extern s16 *helicopter_label_table[];
void obj_sound_pair_stop();
#endif

s32 helicopter_spawn(Placement *place) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    *(s16 *)&place->unk_00[2] = 0x708;
    obj->handlers[0].fn = (void *)helicopter_phase0;
    obj->handlers[1].fn = helicopter_update;
    obj->handlers[2].fn = (void *)helicopter_phase2;
    obj->handlers[3].fn = helicopter_draw;
    obj->callback = (s32)helicopter_crash;
    obj->kind = 1;
    obj->asset = helicopter_asset_slot;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = d_801178BC;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->state_table = helicopter_slot_table;
    script_start((Script *)obj, helicopter_script, (s32)helicopter_data);
    obj->script.data = helicopter_label_table;
    obj->script.unk_0A = 0;
    obj->script.pc = helicopter_script_entry;
    if (get_area() / 3 != 0xB) {
        obj_init_from_place(obj, place, 0x437);
    } else {
        obj_init_from_place(obj, place, 0x135);
    }
    obj->speed = 0xA;
    obj_set_part_bounds(obj, 0, 0x1000);
    obj->vars.helicopter.crash_effect_count = 1;
    obj->vars.helicopter.unk_252 = 6;
    obj->vars.helicopter.timer = 0x78;
    obj->vars.helicopter.fire_countdown = 4;
    *(s16 *)obj->vars.enemy.unk_260 = 0x20;
    obj->vars.helicopter.unk_248 = 0;
    obj->vars.enemy.sound_channel[1] = 0;
    obj->vars.helicopter.unused_258 = 0;
    obj->vars.helicopter.unk_25E = 0;
    *(s16 *)&obj->vars.enemy.unk_260[2] = 0x168;
    obj->vars.helicopter.spawn_y = obj->y;
    obj->vars.helicopter.yaw = obj->yaw;
    obj->vars.enemy.sound_channel[0] = obj->vars.enemy.sound_channel[0] - 7;
    *(s16 *)&obj->vars.enemy.unk_260[4] = *(s16 *)&place->unk_1A / 256;
    obj->vars.enemy.unk_266 = 0;
    obj->vars.helicopter.fly_sound_handle = 0;
    obj->vars.helicopter.sound_handle = sound_start(SND_HELICOPTER | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
    sound_attach(obj->vars.helicopter.sound_handle, &obj->x, NULL);
    sound_set_flag_bit2(obj->vars.helicopter.sound_handle, 1);
    obj->destructor = obj_sound_pair_stop;
    return 1;
}

/* Draws the helicopter as effect-list records: the body (model `model`) and its three rotor parts (models
 * model + 3, model + 3 and model + 4), each 0x78 above its point; the first two parts only every other frame
 * (blink toggles) or while paused. Then fires effect 2 from the object's position. S01's copy of
 * s06_helicopter_draw, with its vectors on the scratchpad.
 *
 * The NULL stores to turn, rot1 and rot2 are dead (flow deletes them) but shape cse: each pointer outlives
 * the vector it copies, so cse keeps the copy (`move s0,s7`, `move a1,fp`) instead of folding it away, and
 * the store right after its last use keeps the copied vector's later reads on its own register. */
void helicopter_draw(Object *self) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    SVECTOR *aim = scratch_alloc(8);
    SVECTOR *body = scratch_alloc(8);
    Vec3 *part1_pos = scratch_alloc(0x10);
    SVECTOR *part1_rot = scratch_alloc(8);
    Vec3 *part2_pos = scratch_alloc(0x10);
    SVECTOR *part2_rot = scratch_alloc(8);
    Vec3 *part3_pos = scratch_alloc(0x10);
    SVECTOR *part3_rot = scratch_alloc(8);
    Object *obj;
    s32 off0_x, off0_y, off0_z, off1_x, off1_y, off1_z, off2_x, off2_y, off2_z;
    s32 pitch;
    s16 roll;
    s16 yaw;
    s32 model;
    s32 colour;
    SVECTOR *turn;
    SVECTOR *rot1;
    SVECTOR *rot2;
    Vec3 *out;

    /* a copy after the allocations: the original moves a0 to s1 next to the first use */
    obj = self;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    off0_x = 0;
    pitch = obj->pitch;
    turn = body;
    off0_y = -0x15E;
    rot->vx = -pitch;
    yaw = obj->yaw;
    off0_z = 0x32;
    off1_x = 0;
    rot->vy = yaw;
    roll = obj->roll;
    off1_y = -0xDA;
    off1_z = 0x32;
    off2_x = 0;
    off2_y = -0xDA;
    off2_z = 0x32;
    rot->vz = roll;
    /* the body keeps the object's pitch and roll but turns by unk_250 instead of the yaw */
    turn->vy = obj->vars.h.unk_250;
    turn->vx = rot->vx;
    turn->vz = rot->vz;
    vec3_rotate(turn->vy, turn->vx, turn->vz, &off0_x, &off0_y, &off0_z);
    out = part1_pos;
    FAKE_OPAQUE(out);
    out->x = off0_x + pos->x;
    out->y = off0_y + pos->y;
    out->z = off0_z + pos->z;
    rot1 = part1_rot;
    rot1->vy = obj->vars.h.unk_252;
    rot1->vx = 0;
    rot1->vz = 0;
    rot_compose_base_yaw(turn, rot1);
    rot1 = NULL;
    vec3_rotate(turn->vy, turn->vx, turn->vz, &off1_x, &off1_y, &off1_z);
    out = part2_pos;
    FAKE_OPAQUE(out);
    out->x = off1_x + pos->x;
    out->y = off1_y + pos->y;
    out->z = off1_z + pos->z;
    rot2 = part2_rot;
    rot2->vy = obj->vars.h.unk_254;
    rot2->vx = 0;
    rot2->vz = 0;
    rot_compose_base_yaw(turn, rot2);
    rot2 = NULL;
    vec3_rotate(turn->vy, turn->vx, turn->vz, &off2_x, &off2_y, &off2_z);
    part3_pos->x = off2_x + pos->x;
    part3_pos->y = off2_y + pos->y;
    part3_pos->z = off2_z + pos->z;
    part3_rot->vy = obj->vars.h.unk_256;
    part3_rot->vx = 0;
    part3_rot->vz = 0;
    rot_compose_base_yaw(turn, part3_rot);
    turn = NULL;
    model = obj_keyframe_value(obj, 0);
    colour = 0;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
        pitch = 0; /* dead store, as in the sibling draw functions; keeps GCC from if-converting colour */
    }
    spark_add(pos->x, pos->y - 0x78, pos->z, body->vy, body->vx, body->vz, model, colour);
    obj->vars.h.unk_248 ^= 1;
    if (obj->vars.h.unk_248 == 0 || is_paused()) {
        spark_add(part1_pos->x, part1_pos->y - 0x78, part1_pos->z, part1_rot->vy, part1_rot->vx, part1_rot->vz,
                  model + 3, colour);
        spark_add(part2_pos->x, part2_pos->y - 0x78, part2_pos->z, part2_rot->vy, part2_rot->vx, part2_rot->vz,
                  model + 3, colour);
    }
    spark_add(part3_pos->x, part3_pos->y - 0x78, part3_pos->z, part3_rot->vy, part3_rot->vx, part3_rot->vz,
              model + 4, colour);
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    aim->vx = 0x300;
    aim->vy = obj->height;
    aim->vz = 0x300;
    aim_marker_draw(2, aim, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    turn = NULL;
    rot2 = NULL;
    rot1 = NULL;
    scratch_top -= 0x40;
    scratch_top -= 0x30;
}

s32 obj_ceiling_near(Object *obj, s32 range) {
    TraceVec4 *seg = scratch_alloc(0x30);
    TraceVec4 *from = &seg[0];
    TraceVec4 *to = &seg[1];
    TraceVec4 *hit = &seg[2];
    s32 near = 0;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    *to = *from;
    to->y += 0xBB8;
    trace_world(8, 0x10, from, to, hit);
    if (ABS(from->y - hit->y) < range) {
        near = 1;
    }
    scratch_top -= 0x30;
    return near;
}

s32 helicopter_crash(Object *obj) {
    s32 origin[3];
    s16 angles[3];
    s32 ox, oy, oz;
    s32 pitch;
    s32 snd;
    u16 yaw;

    ox = rand_a_next() % 0x200;
    oy = rand_a_next() % 0x100;
    oz = rand_a_next() % 0x200;
    snd = obj->vars.snd2.sound[1];
    if (snd != 0) {
        sound_stop(snd);
        obj->vars.snd2.sound[1] = 0;
    }
    obj->unk_17A = 0;
    origin[0] = obj->x >> 12;
    origin[1] = obj->y >> 12;
    origin[2] = obj->z >> 12;
    pitch = (s16)obj->pitch;
    angles[0] = -pitch;
    angles[1] = obj->yaw;
    angles[2] = obj->roll;
    obj->next_state = 3;
    yaw = obj->vars.helicopter.yaw;
    angles[1] = yaw;
    vec3_rotate((s16)yaw, angles[0], angles[2], &ox, &oy, &oz);
    if (obj->vars.helicopter.crash_effect_count-- > 0) {
        spawn_effect(origin[0] + ox, origin[1] - oy, origin[2] + oz, 0x80007F01);
        spawn_effect(origin[0] - ox, origin[1] - oy, origin[2] - oz, 0x80000001);
        spawn_effect(origin[0], origin[1] - 0x200, origin[2], 0x80007F00);
        spawn_effect(origin[0], origin[1] - 0x300, origin[2], 0x80000000);
        spawn_effect(origin[0], origin[1] - 0x380, origin[2], 0x80007F02);
    }
    if (rand_a_next() % 5 == 0) {
        if (obj->vars.helicopter.unk_248 == 0) {
            spawn_effect(origin[0] + ox, origin[1] - oy, origin[2] + oz, 0x80007F00);
        } else {
            spawn_effect(origin[0] - ox, origin[1] - oy, origin[2] - oz, 0x80000000);
        }
    }
    if (obj_ceiling_near(obj, 300) != 0 || (s16)obj->vars.bob.phase-- < 0) {
        spawn_effect(origin[0] + ox, origin[1] - oy, origin[2] + oz, 0x80007F01);
        spawn_effect(origin[0] - ox, origin[1] - oy, origin[2] - oz, 0x80000001);
        spawn_effect(origin[0], origin[1] - 0x200, origin[2], 0x80007F00);
        spawn_effect(origin[0], origin[1] - 0x300, origin[2], 0x80000000);
        spawn_effect(origin[0], origin[1] - 0x380, origin[2], 0x80007F02);
        obj_effect_send_pos(obj);
        placement_list_pop((ListRecord *)obj->placement);
        obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
        return 0;
    }
    return 1;
}

/* Fires a shot: spawns it from the object's position, shifted up and rotated by its angles, and starts the
 * fire sound on first call with sound_set_pos_from_obj as its update. */
void enemy_fly_fire(Object *obj) {
    s32 *pos;
    s16 *rot;
    s32 off_x;
    s32 off_y;
    s32 off_z;
    s16 yaw;
    s32 pitch;
    s32 base;
    s32 rnd;

    pos = scratch_alloc(0x10);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;

    rot = scratch_alloc(8);
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;

    off_x = 0;
    off_y = 0x50;
    off_z = 0x28A;
    pos[1] -= 0x78;

    rnd = rand_a_next();
    rnd %= 20;
    base = obj->vars.helicopter.yaw - 0xA;
    yaw = base + rnd;
    rot[1] = yaw;

    vec3_rotate(yaw, rot[0], rot[2], &off_x, &off_y, &off_z);

    pos[0] += off_x;
    pos[1] += off_y;
    pos[2] += off_z;

    shot_spawn_obj(pos, rot, 1, obj->damage << 16);

    if (obj->vars.snd2.sound[1] == 0) {
        obj->vars.snd2.sound[1] = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        sound_attach(obj->vars.snd2.sound[1], obj, (void (*)())sound_set_pos_from_obj);
        sound_set_flag_bit2(obj->vars.snd2.sound[1], 1);
    }

    scratch_top -= 0x10;
    scratch_top -= 8;
}

/* Plays effect 0x2029 at two points: the object's position shifted up by 0x78, plus
 * two fixed offsets rotated by the object's pitch, yaw and roll (vec3_rotate). */
void obj_sound_pair_play(Object *obj) {
    s32 *origin = scratch_alloc(0x10);
    s32 *point = scratch_alloc(0x10);
    u16 *angles = scratch_alloc(8);
    s32 pitch;
    u16 unk_250;
    s32 offs[6];
    s32 *off_a = offs;
    s32 *off_b = offs + 3;

    off_a[0] = 0x122;
    off_a[1] = 0x64;
    off_a[2] = -0x14;
    off_b[0] = -0x122;
    off_b[1] = 0x64;
    off_b[2] = -0x14;

    get_model_slot_base();

    origin[0] = obj->x >> 12;
    origin[1] = obj->y >> 12;
    origin[2] = obj->z >> 12;
    pitch = (s16)obj->pitch;
    angles[0] = -pitch;
    angles[1] = obj->yaw; /* overwritten below; the original stores it too */
    angles[2] = (s16)obj->roll;
    origin[1] -= 0x78;
    unk_250 = obj->vars.helicopter.yaw;
    angles[1] = unk_250;

    vec3_rotate((s16)unk_250, (s16)angles[0], (s16)angles[2], &off_a[0], &off_a[1], &off_a[2]);
    vec3_rotate((s16)angles[1], (s16)angles[0], (s16)angles[2], &off_b[0], &off_b[1], &off_b[2]);

    point[0] = off_a[0] + origin[0];
    point[1] = off_a[1] + origin[1];
    point[2] = off_a[2] + origin[2];
    shot_spawn_obj(point, angles, 2, (s32)&shot_twin_desc);
    sound_play_at_units(SND_TWIN_SHOT_FIRE | SND_GROUP(1), 0x60, 0x3C, point);

    point[0] = off_b[0] + origin[0];
    point[1] = off_b[1] + origin[1];
    point[2] = off_b[2] + origin[2];
    shot_spawn_obj(point, angles, 2, (s32)&shot_twin_desc);
    sound_play_at_units(SND_TWIN_SHOT_FIRE | SND_GROUP(1), 0x60, 0x3C, point);

    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 8;
}

#if STAGE == 1
void obj_sound_pair_stop(Object *obj) {
    SoundVars *vars = (SoundVars *)&obj->vars;

    sound_stop(vars->sound_a);
    if (vars->sound_b != 0) {
        sound_stop(vars->sound_b);
        vars->sound_b = 0;
    }
}
#else
typedef struct SoundVars {
    /* 0x248 */ u8 unk_248[0x20];
    /* 0x268 */ s32 sound_a; /* stopped unconditionally */
    /* 0x26C */ s32 sound_b; /* 0 when not playing */
} SoundVars;
/* Same code as obj_sound_pair_stop (s01). */
void obj_sound_pair_stop(Object *obj) {
    SoundVars *vars = (SoundVars *)&obj->vars;

    sound_stop(vars->sound_a);
    if (vars->sound_b != 0) {
        sound_stop(vars->sound_b);
        vars->sound_b = 0;
    }
}
#endif
