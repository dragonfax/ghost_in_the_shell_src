/* rocket_drone: one of the original source files (scripts/objmap.py); s02, s09. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

#if STAGE == 2
void rocket_drone_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}
#endif

#if STAGE == 9
/* Same code as func_800BC8AC (s01). */
void obj_stream_branch(Object *obj) {
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

void rocket_drone_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}
#endif

#if STAGE == 2
void obj_step_axes_toward(Object *obj, s32 target_a, s32 target_b);
#endif

#if STAGE == 9
void obj_aim_and_turn(Object *obj, void *aim_slot, s16 aim_step, s16 yaw_step);
void obj_step_axes_toward(Object *obj, s32 target_a, s32 target_b);
void obj_set_fall_speed(Object *obj, s32 speed, s32 target);
#endif

void obj_set_fall_speed(Object *obj, s32 speed, s32 target);

void enemy_fly_forward(Object *obj) {
    s32 dx = 0;
    s32 dz = 0;
    s32 level;
    s32 cell_w;
    s32 cell_h;
    level = obj->vars.snd.sound >> 12;
    obj->unk_1B7 = 0;
    if (obj->unk_242 == 0) {
        obj_aim_and_turn(obj, &obj->vars.h.unk_250, 0x10, 8);
    } else {
        obj_aim_and_turn(obj, &obj->vars.h.unk_250, 4, 4);
    }
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    obj_set_fall_speed(obj, 2, level);
}

void enemy_shoot(Object *obj);
void enemy_chase_player(Object *obj) {
    s32 dx;
    s32 dz;
    s32 aim_y;
    s32 oz;
    s32 ox;
    s32 dist_z;
    s32 dist_x;
    s16 timer;

    oz = obj->z;
    dist_z = cam_pos_z - oz;
    ox = obj->x;
    dist_x = cam_pos - ox;
    aim_y = (cam_pos_y >> 12) - 0x17C;
    dx = 0;
    dz = 0;
    obj->unk_1B7 = 0;
    obj->vars.h.unk_250 = angle_approach(
        (s16) obj->vars.h.unk_250,
        (s16) atan2(dist_z >> 12, dist_x >> 12),
        0x20);
    obj_turn_toward_player(obj, 8);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    obj_set_fall_speed(obj, 2, aim_y);
    timer = obj->vars.h.unk_25A;
    obj->vars.h.unk_25A = timer - 1;
    if (timer < 0) {
        enemy_shoot(obj);
        obj->vars.h.unk_25A = 0x96;
    }
}

void rocket_drone_update(Object *obj, ObjHandler *handler) {
    obj->vz = 0;
    obj->vx = 0;
    obj_script_step(obj, handler);
    obj_ease_pitch(obj, 4, 0x80);
    obj_lean_into_turn(obj, &obj->vars.enemy.unk_258, 4, 0x80);
    obj->vars.rocket_drone.rotor_angle += 8;
    obj->vars.enemy.sound_channel[0] -= 8;
    obj->vars.enemy.sound_channel[1] += 0x200;
}

s32 obj_destroy_effect(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    spawn_effect(pos[0], pos[1], pos[2], 0);
    spawn_effect(pos[0], pos[1], pos[2], 1);
    placement_list_pop((ListRecord *) obj->placement);
    obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
    return 0;
}

void fighter_jet_stop_sound(Object *obj) {
    sound_stop(obj->vars.words[5]); /* 0x25C */
}

extern s16 *rocket_drone_data[];

/* The stage's rocket drone data (script, asset, tables). */
extern s32 rocket_drone_asset asm("d_80116B88");
extern s32 rocket_drone_script asm("rocket_drone_anim_idle");
extern s16 *rocket_drone_anim[] asm("rocket_drone_anim");
extern s16 *rocket_drone_anim_word asm("d_80116CC0");
extern ScriptCallEntry rocket_drone_table_194[] asm("rocket_drone_call_table");
extern StateEntry rocket_drone_table_198[] asm("rocket_drone_state_table");

void rocket_drone_draw(Object *obj, ObjHandler *handler);
void rocket_drone_phase0(Object *obj, ObjHandler *handler);

/* Spawns the rocket drone from a placement record: returns 1 if an object was made, 0 if the pool is full. */
s32 rocket_drone_spawn(Placement *place) {
    Object *obj;
    s32 snd;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    place->unk_02 = 0x708;
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) rocket_drone_phase0;
    obj->handlers[1].fn = rocket_drone_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = rocket_drone_draw;
    obj->callback = (s32) obj_destroy_effect;
    obj->destructor = fighter_jet_stop_sound;
    obj->asset = &rocket_drone_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = rocket_drone_table_194;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->kind = 1;
    obj->state_table = rocket_drone_table_198;
    script_start((Script *) obj, (s16 *) &rocket_drone_script, (s32) &rocket_drone_data);
    obj->script.data = rocket_drone_anim;
    obj->script.unk_0A = 0;
    obj->script.pc = rocket_drone_anim_word;
    obj_init_from_place(obj, place, 0x37);
    obj->speed = 3;
    obj_set_part_bounds(obj, 8, 0x1000);
    obj->vars.rocket_drone.rotor_angle = 6;
    obj->vars.rocket_drone.unused_248 = 0;
    obj->vars.rocket_drone.unused_24A = 1;
    obj->vars.enemy.sound_channel[1] = 0;
    obj->vars.rocket_drone.unused_258 = 0;
    obj->vars.rocket_drone.unused_25A = 0x96;
    obj->vars.rocket_drone.base_y = obj->y;
    obj->vars.rocket_drone.base_yaw = (u16) obj->yaw;
    obj->vars.enemy.sound_channel[0] = (u16) obj->vars.enemy.sound_channel[0] - 7;
    snd = sound_start(SND_ROCKET_DRONE_LOOP | SND_HELD | SND_GROUP(2), 0x40, 0, 0);
    obj->vars.rocket_drone.sound_channel = snd;
    sound_attach(snd, &obj->x, NULL);
    sound_set_flag_bit2(obj->vars.rocket_drone.sound_channel, 1);
    return 1;
}

/* Draws the five sparks of the aim/effect helper around an object (same body as laser_drone_draw without
 * the enemy_aim_spark call): rotates five offsets by the object's angles, adds a spark at each, then the aim marker. */
void rocket_drone_draw(Object *obj, ObjHandler *handler) {
    s32 off0_x, off0_y, off0_z;
    s32 off1_x, off1_y, off1_z;
    s32 off2_x, off2_y, off2_z;
    s32 off3_x, off3_y, off3_z;
    s32 off4_x, off4_y, off4_z;
    Vec3 *base;
    SVECTOR *rot;
    SVECTOR *aim;
    Vec3 *pos0;
    SVECTOR *rot0;
    Vec3 *pos1;
    SVECTOR *rot1;
    Vec3 *pos2;
    SVECTOR *rot2;
    Vec3 *pos3;
    SVECTOR *rot3;
    Vec3 *pos4;
    SVECTOR *rot4;
    s32 model;
    s32 colour;
    s32 pitch;
    s16 roll;
    s32 roll_arg;
    Object *drone;
    s16 half_w;
    s16 half_d;

    base = scratch_alloc(0x10);
    rot = scratch_alloc(8);
    aim = scratch_alloc(8);
    pos0 = scratch_alloc(0x10);
    rot0 = scratch_alloc(8);
    pos1 = scratch_alloc(0x10);
    rot1 = scratch_alloc(8);
    pos2 = scratch_alloc(0x10);
    rot2 = scratch_alloc(8);
    pos3 = scratch_alloc(0x10);
    rot3 = scratch_alloc(8);
    pos4 = scratch_alloc(0x10);
    rot4 = scratch_alloc(8);
    /* a copy after the allocations: the parameter stays in a0 until here, as in the original */
    drone = obj;

    off0_x = 0;
    off0_y = 0;
    off0_z = 0;
    off1_x = 0;
    off1_y = 0x73;
    off1_z = 0;
    off2_x = 0;
    off2_y = 6;
    off2_z = 0;
    off3_x = 0;
    off3_y = 0x14;
    off3_z = 0;
    off4_x = 0;
    off4_y = 0x19;
    off4_z = 0;
    base->x = drone->x >> 12;
    base->y = drone->y >> 12;
    base->z = drone->z >> 12;
    pitch = drone->pitch;
    rot->vx = -pitch;
    rot->vy = drone->yaw;
    /* s16 roll converted to s32 before it is stored: combine merges the load into the sign extension (lh) and
     * keeps roll as a copy, and the dropped shift temp still gets a stack slot (the original's unused 8 bytes
     * after the spills) */
    roll = drone->roll;
    roll_arg = roll;
    rot->vz = roll;
    vec3_rotate(rot->vy, rot->vx, roll_arg, &off0_x, &off0_y, &off0_z);
    pos0->x = off0_x + base->x;
    pos0->y = off0_y + base->y;
    pos0->z = off0_z + base->z;
    rot0->vy = 0;
    rot0->vx = 0;
    rot0->vz = 0;
    rot_compose_base_yaw(rot, rot0);
    vec3_rotate(rot->vy, rot->vx, rot->vz, &off1_x, &off1_y, &off1_z);
    pos1->x = off1_x + base->x;
    pos1->y = off1_y + base->y;
    pos1->z = off1_z + base->z;
    rot1->vy = 0;
    rot1->vx = 0;
    rot1->vz = 0;
    rot_compose_base_yaw(rot, rot1);
    vec3_rotate(rot->vy, rot->vx, rot->vz, &off2_x, &off2_y, &off2_z);
    pos2->x = off2_x + base->x;
    pos2->y = off2_y + base->y;
    pos2->z = off2_z + base->z;
    rot2->vy = drone->vars.h.unk_252;
    rot2->vx = 0;
    rot2->vz = 0;
    rot_compose_base_yaw(rot, rot2);
    vec3_rotate(rot->vy, rot->vx, rot->vz, &off3_x, &off3_y, &off3_z);
    pos3->x = off3_x + base->x;
    pos3->y = off3_y + base->y;
    pos3->z = off3_z + base->z;
    rot3->vy = drone->vars.h.unk_254;
    rot3->vx = 0;
    rot3->vz = 0;
    rot_compose_base_yaw(rot, rot3);
    vec3_rotate(rot->vy, rot->vx, rot->vz, &off4_x, &off4_y, &off4_z);
    colour = 0;
    pos4->x = off4_x + base->x;
    pos4->y = off4_y + base->y;
    pos4->z = off4_z + base->z;
    rot4->vy = drone->vars.h.unk_256;
    rot4->vx = 0;
    rot4->vz = 0;
    rot_compose_base_yaw(rot, rot4);
    /* empty loop: its notes end cse's first block and stop the scheduler here, which gives the original's
     * registers for pos4/rot4 and keeps colour = 0 above the last rot_compose_base_yaw */
    do {
    } while (0);

    model = obj_keyframe_value(drone, 0);
    if (drone->hit > 0) {
        colour = 0x60C0FF;
        pitch = 0; /* dead store, as in the sibling draw functions; keeps GCC from if-converting colour */
    }
    spark_add(pos0->x, pos0->y - 0x6C, pos0->z, rot0->vy, rot0->vx, rot0->vz, model, colour);
    spark_add(pos1->x, pos1->y - 0x6C, pos1->z, rot1->vy, rot1->vx, rot1->vz, model + 1, colour);
    drone->vars.h.unk_248 ^= 1;
    if (drone->vars.h.unk_248 == 0 || is_paused()) {
        spark_add(pos2->x, pos2->y - 0x6C, pos2->z, rot2->vy, rot2->vx, rot2->vz, model + 5, colour);
        spark_add(pos3->x, pos3->y - 0x6C, pos3->z, rot3->vy, rot3->vx, rot3->vz, model + 5, colour);
    }
    spark_add(pos4->x, pos4->y - 0x6C, pos4->z, rot4->vy, rot4->vx, rot4->vz, model + 6, colour);

    base->x = drone->x;
    base->y = drone->y;
    base->z = drone->z;
    /* s16 halves: the truncation makes combine shift with srl */
    half_w = drone->width / 2;
    aim->vx = half_w;
    aim->vy = drone->height;
    half_d = drone->unk_1E8[0] / 2;
    aim->vz = half_d;
    aim_marker_draw(2, aim, base, 0);
    if (drone->hit != 0) {
        drone->hit = -1;
    }

    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 8;
    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 0x10;
    scratch_top -= 8;
}

extern GunSetup enemy_shot_setup; /* its unk_0C is set per shot */

void enemy_shoot(Object *obj) {
    Vec3 *pos;
    SVECTOR *ang;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 neg;
    u16 *snd;

    snd = &enemy_shot_setup.damage;
    *snd = obj->damage;
    pos = (Vec3 *) scratch_top;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    scratch_top += 0x10;
    pos->z = obj->z >> 12;
    ang = (SVECTOR *) scratch_top;
    dx = 0;
    neg = -obj->pitch;
    ang->vx = neg;
    scratch_top += 8;
    ang->vy = obj->yaw;
    dy = -0xA8;
    dz = 0;
    ang->vz = obj->roll;
    ang->vy = obj->vars.h.unk_250;
    vec3_rotate(ang->vy, ang->vx, ang->vz, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
    sound_play_at_units(SND_STAGE_ENEMY_FIRE | SND_GROUP(1), 0x60, 0x3C, pos);
    shot_spawn_obj((s32 *) pos, (u16 *) ang, 2, (s32) &enemy_shot_setup);
    ang->vy += 0x100;
    shot_spawn_obj((s32 *) pos, (u16 *) ang, 2, (s32) &enemy_shot_setup);
    ang->vy -= 0x200;
    shot_spawn_obj((s32 *) pos, (u16 *) ang, 2, (s32) &enemy_shot_setup);
    scratch_top -= 0x10;
    scratch_top -= 8;
}
