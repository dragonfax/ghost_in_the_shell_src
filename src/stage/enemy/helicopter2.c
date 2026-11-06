/* helicopter2: one of the original source files (scripts/objmap.py); s03, s07. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

#if STAGE == 3
/* Same code as func_800BC8AC (s01). */
void script_op_jump_table_if_player_far(Object *obj) {
    s32 limit;
    s16 *cursor;
    s32 threshold;
    s32 index;

    limit = (s16) player_dist_to_placement(obj);
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}
#endif

#if STAGE == 7
/* Same code as func_800BC8AC (s01). */
void script_op_jump_table_if_player_far(Object *obj) {
    s32 limit;
    s16 *cursor;
    s32 threshold;
    s32 index;

    limit = (s16) player_dist_to_placement(obj);
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void helicopter_2_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}
#endif

#if STAGE == 3
void func_800BD9EC(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}
void obj_step_axes_toward(Object *obj, s32 target_a, s32 target_b);
#endif

#if STAGE == 7
void obj_aim_and_turn(Object *obj, void *aim_slot, s16 aim_step, s16 yaw_step);
void obj_step_axes_toward(Object *obj, s32 target_a, s32 target_b);
void obj_set_fall_speed(Object *obj, s32 speed, s32 target);
#endif

void obj_set_fall_speed(Object *obj, s32 speed, s32 target);
void obj_aim_and_turn(Object *obj, void *aim_slot, s16 aim_step, s16 yaw_step);

void enemy_fly_step(Object *obj) {
    s32 out_x;
    s32 out_z;
    s32 sound_arg;

    out_x = 0;
    out_z = 0;
    sound_arg = obj->vars.snd.sound >> 12;
    if (obj->vars.enemy.unk_260[3] != 0) {
        sound_stop(obj->vars.enemy.unk_260[3]);
        obj->vars.enemy.unk_260[3] = 0;
    }
    obj->unk_1B7 = 0;
    if (obj->unk_242 == 0) {
        obj_aim_and_turn(obj, &obj->vars.words[2], 0x10, 8);
    } else {
        obj_aim_and_turn(obj, &obj->vars.words[2], 4, 4);
    }
    fly_move(obj->yaw, obj->speed, &out_x, &out_z);
    obj_step_axes_toward(obj, out_z, out_x);
    obj_set_fall_speed(obj, 2, sound_arg);
}

void enemy_fly_attack(Object *obj) {
    s32 dx;
    s32 dz;
    s32 base_y;
    s32 limit_y;
    u16 shots;
    u8 sound;

    base_y = cam_pos_y >> 12;
    dx = 0;
    dz = 0;
    obj->unk_1B7 = 0;
    obj_aim_and_turn(obj, &obj->vars.enemy.unk_250, 0x10, 8);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    obj_set_fall_speed(obj, 2, base_y - 0x190);
    limit_y = base_y - 0x1C2;
    if (obj_player_in_arc(obj, (s16) obj->vars.h.unk_250, 0x100) == 1 && limit_y < (obj->y >> 12)) {
        shots = obj->vars.enemy.unk_25C;
        obj->vars.enemy.unk_25C = shots - 1;
        if ((s16) shots < 0) {
            enemy_fire_effect(obj);
            obj->vars.enemy.unk_25C = 4;
        }
    } else {
        sound = obj->vars.enemy.unk_260[3];
        if (sound != 0) {
            sound_stop(sound);
            obj->vars.enemy.unk_260[3] = 0;
        }
    }
}

#if STAGE == 3
s32 obj_player_in_arc(Object *obj, s32 center, s32 range);
void flyer_fire_pair(Object *obj);
/* Names helicopter2_spawn uses in this stage (s07 has its own). */
#define SPAWN_HANDLER0 func_800BD9EC
#define SPAWN_ASSET helicopter2_asset
#define SPAWN_UNK_194 helicopter2_script_calls
#define SPAWN_UNK_198 helicopter2_states
#define SPAWN_SCRIPT_CFG helicopter2_script_cfg
#define SPAWN_SCRIPT_ARG helicopter2_script_arg
#define SPAWN_UNK_1C_DATA helicopter2_script_data
#define SPAWN_UNK_1C_VAR helicopter2_script_entry
#endif

#if STAGE == 7
s32 obj_player_in_arc(Object *obj, s32 center, s32 range);
void flyer_fire_pair(Object *obj);
/* Names helicopter2_spawn uses in this stage (s03 has its own). */
#define SPAWN_HANDLER0 helicopter_2_phase0
#define SPAWN_ASSET helicopter2_asset
#define SPAWN_UNK_194 helicopter2_script_calls
#define SPAWN_UNK_198 helicopter2_states
#define SPAWN_SCRIPT_CFG helicopter_2_script_cfg
#define SPAWN_SCRIPT_ARG helicopter_2_data
#define SPAWN_UNK_1C_DATA helicopter2_script_data
#define SPAWN_UNK_1C_VAR helicopter2_script_entry
#endif

void obj_set_fall_speed(Object *obj, s32 speed, s32 target);

void flyer_hover_update(Object *obj) {
    s32 fly_dz;
    s32 fly_dx;
    s32 center;
    s32 limit;
    u16 *timer = &obj->vars.h.unk_25A;
    u16 timer_val;

    fly_dz = 0;
    fly_dx = 0;
    center = (s32) cam_pos_y >> 12;
    limit = center - 0x1F4;
    if (obj->vars.enemy.unk_260[3] != 0) {
        sound_stop(obj->vars.enemy.unk_260[3]);
        obj->vars.enemy.unk_260[3] = 0;
    }
    obj->unk_1B7 = 0;
    obj_aim_and_turn(obj, (s16 *) &obj->vars.h.unk_250, 0x10, 8);
    fly_move(obj->yaw, obj->speed, &fly_dz, &fly_dx);
    obj_step_axes_toward(obj, fly_dx, fly_dz);
    obj_set_fall_speed(obj, 2, center - 0x226);
    if (obj_player_in_arc(obj, *(s16 *) &obj->vars.h.unk_250, 0x100) == 1 && (obj->y >> 12) < limit) {
        timer_val = *timer;
        *timer = timer_val - 1;
        if ((s16) timer_val < 0) {
            flyer_fire_pair(obj);
            *timer = 0x50;
        }
    }
}

void flyer_bank_turn(Object *obj) {
    s32 dx = 0;
    s32 dz = 0;
    s32 handle;

    handle = obj->vars.enemy.unk_260[3];
    if (handle != 0) {
        sound_stop(handle);
        obj->vars.enemy.unk_260[3] = 0;
    }
    if (obj->roll > 0) {
        obj->yaw += 8;
        obj->vars.h.unk_250 += 0x10;
    } else {
        obj->yaw -= 8;
        obj->vars.h.unk_250 -= 0x10;
    }
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    obj->vy = 0x3000;
}

void obj_ease_pitch(Object *obj, s16 step, s16 limit);
void obj_ground_shadow_spawn(Object *obj, s32 base, s32 range);
void helicopter2_update(Object *obj, ObjHandler *handler) {
    s16 timer;
    obj->vz = 0;
    obj->vx = 0;
    obj_script_step(obj, handler);
    obj_ease_pitch(obj, 4, 0x100);
    obj_lean_into_turn(obj, &obj->vars.helicopter2.prev_yaw, 4, 0x100);
    obj->vars.helicopter2.rotor_angle += 8;
    obj->vars.enemy.sound_channel[0] -= 8;
    obj->vars.enemy.sound_channel[1] += 0x200;
    timer = obj->vars.helicopter2.timer - 1;
    obj->vars.helicopter2.timer = timer;
    if (timer < 0 && obj->next_state != 3) {
        obj_ground_shadow_spawn(obj, 0x100, 0x400);
        obj->vars.helicopter2.timer = 0x20;
    }
}

/* Shifts the object's y by a fixed amount around the call to obj_run_states_default (meaning unknown). */
void helicopter2_phase2(Object *obj) {
    obj->y += 0xFFFAC000;
    ((void (*)(Object *))obj_run_states_default)(obj); /* the original leaves a1 as it is */
    obj->y += 0x54000;
}

/* Spawns an enemy from a placement: links it into the actor list, sets its four state
   handlers, destructor and asset, runs its script and sets up the placement. Starts its
   sound handle on first spawn. Returns 1, or 0 if no object slot is free. The SPAWN_*
   names are the data and first handler of each stage, defined in its main.c. */
void func_800BD9EC(Object *obj, ObjHandler *handler);
void enemy_sounds_stop(Object *obj);
void helicopter2_draw(Object *obj, ObjHandler *handler);
s32 obj_timed_spawn_update(Object *obj);
extern s32 SPAWN_ASSET[3];
extern ScriptCallEntry SPAWN_UNK_194[6];
extern StateEntry SPAWN_UNK_198[4];
extern s16 SPAWN_SCRIPT_CFG[4];
extern s16 *SPAWN_SCRIPT_ARG[];
extern s16 *SPAWN_UNK_1C_DATA[];
extern s16 *SPAWN_UNK_1C_VAR;

s32 helicopter2_spawn(Placement *place) {
    Object *obj;
    s32 snd;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    *(s16 *) &place->unk_00[2] = 0;
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) SPAWN_HANDLER0;
    obj->handlers[1].fn = helicopter2_update;
    obj->handlers[2].fn = (void (*)(Object *, ObjHandler *)) helicopter2_phase2;
    obj->handlers[3].fn = helicopter2_draw;
    obj->callback = (s32) obj_timed_spawn_update;
    obj->destructor = enemy_sounds_stop;
    obj->asset = SPAWN_ASSET;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = SPAWN_UNK_194;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->kind = 1;
    obj->state_table = SPAWN_UNK_198;
    script_start((Script *) obj, SPAWN_SCRIPT_CFG, (s32) &SPAWN_SCRIPT_ARG);
    obj->script.data = SPAWN_UNK_1C_DATA;
    obj->script.unk_0A = 0;
    obj->script.pc = SPAWN_UNK_1C_VAR;
    obj_init_from_place(obj, place, 0x437);
    obj->speed = 8;
    obj_set_part_bounds(obj, 0, 0x1000);
    obj->vars.helicopter2.rotor_angle = 6;
    obj->vars.h.unk_25A = 0x50;
    obj->vars.helicopter2.unused_25C = 4;
    obj->vars.helicopter2.timer = 0x20;
    *(s16 *) obj->vars.enemy.unk_260 = 0x168;
    obj->vars.helicopter2.draw_toggle = 0;
    obj->vars.helicopter2.unk_24A = 1;
    obj->vars.helicopter2.unk_256 = 0;
    obj->vars.h.unk_258 = 0;
    obj->vars.snd.sound = obj->y;
    obj->vars.helicopter2.yaw = (u16) obj->yaw;
    obj->vars.helicopter2.unk_254 = obj->vars.helicopter2.unk_254 - 7;
    if (obj->vars.enemy.unk_260[2] == 0) {
        snd = sound_start(SND_HELICOPTER_ROTOR_LOOP | SND_HELD | SND_GROUP(2), 0x40, 0, 0);
        sound_attach(snd, &obj->x, NULL);
        sound_set_flag_bit2(snd, 1);
        obj->vars.enemy.unk_260[2] = (u8) snd;
    }
    return 1;
}

void helicopter2_draw(Object *obj, ObjHandler *handler) {
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
    s32 off0_x, off0_y, off0_z, off1_x, off1_y, off1_z, off2_x, off2_y, off2_z;
    s32 pitch;
    s16 roll;
    s16 yaw;
    s32 model;
    s32 colour;
    s16 half_w;
    s16 half_d;
    SVECTOR *turn;
    SVECTOR *rot1;
    SVECTOR *rot2;
    Vec3 *out;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    off0_x = 0;
    pitch = obj->pitch;
    turn = body;
    off0_y = -0xAA;
    rot->vx = -pitch;
    yaw = obj->yaw;
    off0_z = -0x78;
    off1_x = 0;
    rot->vy = yaw;
    roll = obj->roll;
    off1_y = -0x78;
    off1_z = -0x78;
    off2_x = 0;
    off2_y = -0xAA;
    off2_z = -0x78;
    rot->vz = roll;
    turn->vy = obj->vars.helicopter2.yaw;
    turn->vx = rot->vx;
    turn->vz = rot->vz;
    vec3_rotate(turn->vy, turn->vx, turn->vz, &off0_x, &off0_y, &off0_z);
    out = part1_pos;
    FAKE_OPAQUE(out);
    out->x = off0_x + pos->x;
    out->y = off0_y + pos->y;
    out->z = off0_z + pos->z;
    rot1 = part1_rot;
    rot1->vy = obj->vars.helicopter2.rotor_angle;
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
    rot2->vy = obj->vars.helicopter2.unk_254;
    rot2->vx = 0;
    rot2->vz = 0;
    rot_compose_base_yaw(turn, rot2);
    rot2 = NULL;
    vec3_rotate(turn->vy, turn->vx, turn->vz, &off2_x, &off2_y, &off2_z);
    part3_pos->x = off2_x + pos->x;
    part3_pos->y = off2_y + pos->y;
    part3_pos->z = off2_z + pos->z;
    part3_rot->vy = obj->vars.helicopter2.unk_256;
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
    spark_add(pos->x, pos->y - 0x54, pos->z, body->vy, body->vx, body->vz, model, colour);
    obj->vars.helicopter2.draw_toggle ^= 1;
    if (obj->vars.helicopter2.draw_toggle == 0 || is_paused()) {
        spark_add(part1_pos->x, part1_pos->y - 0x54, part1_pos->z, part1_rot->vy, part1_rot->vx, part1_rot->vz,
                  model + 3, colour);
        spark_add(part2_pos->x, part2_pos->y - 0x54, part2_pos->z, part2_rot->vy, part2_rot->vx, part2_rot->vz,
                  model + 3, colour);
    }
    spark_add(part3_pos->x, part3_pos->y - 0x54, part3_pos->z, part3_rot->vy, part3_rot->vx - 0x54, part3_rot->vz,
              model + 4, colour);
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    /* s16 halves: the truncation makes combine shift with srl */
    half_w = obj->width / 2;
    aim->vx = half_w;
    aim->vy = obj->height;
    half_d = obj->unk_1E8[0] / 2;
    aim->vz = half_d;
    aim_marker_draw(2, aim, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    /* the NULL stores keep the pointers' live ranges as in the original (as in helicopter_draw) */
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

s32 obj_timed_spawn_update(Object *obj) {
    s32 pos[3];
    s16 angles[3];
    Placement *placement;
    s32 rand_val;
    s32 type_index;
    s32 pitch;
    s32 jitter;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    angles[0] = -pitch;
    angles[1] = obj->yaw;
    angles[2] = obj->roll;
    obj->unk_17A = 0;
    obj->next_state = 3;
    angles[1] = obj->vars.helicopter2.yaw;

    if (grid_active_get() != 0) {
        if ((obj->vars.helicopter2.unk_24A-- << 16) > 0) {
            spawn_effect(pos[0], pos[1], pos[2], 0x80007F01);
            spawn_effect(pos[0], pos[1] - 0x100, pos[2], 0x80000000);
            spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0x80007F02);
        }
        if (*(s16 *)&obj->vars.enemy.mode == 0) {
            rand_val = rand_a_next();
            if (rand_val == (rand_val / 5) * 5) {
                jitter = (rand_a_next() % 200) - 0x64;
                spawn_effect(pos[0] + jitter, pos[1], pos[2], 0x80007F00);
            }
        }
        if (obj_ceiling_near(obj, 0x64) == 0 && ((*(u16 *)obj->vars.enemy.unk_260)-- << 16) >= 0) {
            goto done_active;
        }
    }

    angles[0] = 0;
    angles[2] = 0;
    type_index = obj->type.unk_0E;
    object_spawn_at(pos, angles, type_index + model_slot_pchr(*(s32 *)obj->asset));
    spawn_effect(pos[0], pos[1] - 0x100, pos[2], 0x80007F01);
    spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0x80000000);
    spawn_effect(pos[0], pos[1] - 0x300, pos[2], 0x80007F01);
    spawn_effect(pos[0], pos[1] - 0x400, pos[2], 0x80000002);
    obj_play_pos_sounds(obj);
    placement_list_pop((ListRecord *)obj->placement);
    placement = obj->placement;
    placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
    return 0;

done_active:
    return 1;
}

/* Plays the looping sound and spawns an effect (shot_spawn_obj) at the object's position, shifted by a rotated
 * offset (0, 0x50, 0xC8) with the object's pitch/yaw jittered. */
void enemy_fire_effect(Object *obj) {
    Vec3 *pos;
    SVECTOR *rot;
    s32 dx = 0;
    s32 dy = 0x50;
    s32 dz = 0xC8;
    s32 handle;
    s32 pitch, r, yaw;

    pos = (Vec3 *)scratch_top;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    scratch_top += 0x10;
    pos->z = obj->z >> 12;
    rot = (SVECTOR *)scratch_top;
    pitch = obj->pitch;
    rot->vx = -pitch;
    scratch_top += 8;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    pos->y -= 0x54;
    r = rand_a_next();
    yaw = obj->vars.h.unk_250 - 10;
    rot->vy = yaw + r % 20;
    vec3_rotate(rot->vy, rot->vx, rot->vz, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
    if (obj->vars.enemy.unk_260[3] == 0) {
        handle = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        sound_attach(handle, &obj->x, 0);
        obj->vars.enemy.unk_260[3] = handle;
    }
    shot_spawn_obj((s32 *)pos, (u16 *)rot, 1, obj->damage << 16);
    scratch_top -= 0x10;
    scratch_top -= 0x8;
}

extern GunSetup flyer_shot_setup;
/* Spawns two effects (shot_spawn_obj) at the object's position plus an offset each; vec3_rotate turns
 * the rotation block into each offset. The first pass uses the yaw from vars.h.unk_250. */
void flyer_fire_pair(Object *obj) {
    s32 offsets[6]; /* [0..2] and [3..5]: the two offset vectors */
    SVECTOR *rot;
    Vec3 *obj_pos;
    Vec3 *out_pos;
    s32 pitch;
    s32 vars_yaw;

    offsets[0] = 0x78;
    offsets[1] = -0x14;
    offsets[2] = -0x3C;
    offsets[3] = -0x78;
    offsets[4] = -0x14;
    offsets[5] = -0x3C;
    get_model_slot_base();
    obj_pos = (Vec3 *)scratch_top;
    scratch_top += 0x10;
    out_pos = (Vec3 *)scratch_top;
    scratch_top += 0x10;
    rot = (SVECTOR *)scratch_top;
    scratch_top += 8;

    obj_pos->x = obj->x >> 12;
    obj_pos->y = obj->y >> 12;
    obj_pos->z = obj->z >> 12;
    pitch = obj->pitch;
    rot->vx = -pitch;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    obj_pos->y -= 0x54;
    vars_yaw = obj->vars.h.unk_250;
    rot->vy = vars_yaw;

    vec3_rotate((s16)vars_yaw, rot->vx, rot->vz, &offsets[0], &offsets[1], &offsets[2]);
    out_pos->x = offsets[0] + obj_pos->x;
    out_pos->y = offsets[1] + obj_pos->y;
    out_pos->z = offsets[2] + obj_pos->z;
    shot_spawn_obj((s32 *)out_pos, (u16 *)rot, 2, (s32)&flyer_shot_setup);

    vec3_rotate(rot->vy, rot->vx, rot->vz, &offsets[3], &offsets[4], &offsets[5]);
    out_pos->x = offsets[3] + obj_pos->x;
    out_pos->y = offsets[4] + obj_pos->y;
    out_pos->z = offsets[5] + obj_pos->z;
    shot_spawn_obj((s32 *)out_pos, (u16 *)rot, 2, (s32)&flyer_shot_setup);

    scratch_top -= 0x20;
    scratch_top -= 8;
}
