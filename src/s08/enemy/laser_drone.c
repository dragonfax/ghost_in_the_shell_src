/* laser_drone: one of s08's own original source files (scripts/objmap.py); part of src/s08/main.c's unit, included there. */

/* Same code as func_800BC8AC (s01). */
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

void laser_drone_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

void obj_aim_and_turn(Object *obj, void *aim_slot, s16 aim_step, s16 yaw_step);
void laser_drone_fly(Object *obj) {
    s32 dx;
    s32 dz;
    s32 target;
    s16 timer;
    Object *self;

    self = obj;
    dx = 0;
    dz = 0;
    self->unk_1B7 = 0;
    target = self->vars.snd.sound >> 12;
    if (self->unk_242 == 0) {
        obj_aim_and_turn(obj, self->vars.turn.pad_250, 0x10, 8);
    } else {
        obj_aim_and_turn(self, self->vars.turn.pad_250, 0x10, 8);
    }
    fly_move(self->yaw, self->speed, &dx, &dz);
    obj_step_axes_toward(self, dz, dx);
    obj_set_fall_speed(self, 2, target);
    timer = self->vars.laser_drone.unk_25E;
    if (timer > 0) {
        self->vars.laser_drone.unk_25E = timer - 0xAA;
    }
}

void laser_drone_fire(Object *obj);
void laser_drone_attack(Object *obj) {
    s32 dx;
    s32 dz;
    s32 target_y;
    s32 az;
    s32 ax;
    s16 t;

    az = obj->z;
    az = (cam_pos_z - az) >> 12;
    ax = (cam_pos - obj->x) >> 12;
    target_y = (cam_pos_y >> 12) - 0x12C;
    dx = 0;
    dz = 0;
    obj->unk_1B7 = 0;
    obj->vars.laser_drone.heading_angle = angle_approach(obj->vars.laser_drone.heading_angle, (s16)atan2(az, ax), 0x10);
    obj_turn_toward_player(obj, 8);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    obj_set_fall_speed(obj, 2, target_y);
    if (obj->vars.h.unk_25A == 0x50) {
        laser_drone_fire(obj);
        *(s16 *)obj->vars.enemy.unk_260 = 1;
    }
    if (obj->vars.h.unk_25A == 0x46) {
        laser_drone_fire(obj);
        *(s16 *)obj->vars.enemy.unk_260 = 1;
    }
    if (obj->vars.h.unk_25A == 0x3C) {
        laser_drone_fire(obj);
        *(s16 *)obj->vars.enemy.unk_260 = 1;
    }
    if ((s16)obj->vars.h.unk_25A < 0) {
        obj->vars.h.unk_25A = 0x64;
    }
    t = obj->vars.h.unk_25A - 1;
    obj->vars.h.unk_25A = t;
    if (t < 0x3C) {
        if (obj->vars.laser_drone.unk_25E > 0) {
            obj->vars.laser_drone.unk_25E -= 0xAA;
        }
    } else {
        if (obj->vars.laser_drone.unk_25E < 0x1000) {
            obj->vars.laser_drone.unk_25E += 0xAA;
        }
    }
    if (obj->vars.laser_drone.hit_timer == 0x168) {
        if (rand_a_next() >= 0x801) {
            obj->yaw += 0x400;
        } else {
            obj->yaw -= 0x400;
        }
    }
    if (obj->vars.laser_drone.hit_timer > 0) {
        obj->vars.laser_drone.hit_timer -= 1;
    }
}

void obj_ease_pitch(Object *obj, s16 step, s16 limit);
void laser_drone_update(Object *obj, ObjHandler *handler) {
    obj->vz = 0;
    obj->vx = 0;
    obj->vy = 0;
    obj_script_step(obj, handler);
    obj_ease_pitch(obj, 4, 0xC0);
    obj_lean_into_turn(obj, &obj->vars.laser_drone.prev_yaw, 4, 0xC0);
    obj->vars.laser_drone.unk_252 += 8;
    obj->vars.enemy.sound_channel[0] -= 8;
    obj->vars.enemy.sound_channel[1] += 0x200;
    if (obj->vars.laser_drone.hit_timer == 0 && (obj_hit_damage(obj->index) << 16) != 0) {
        obj->vars.laser_drone.hit_timer = 0x168;
    }
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


/* Stops the sound whose handle is the byte at 0x262. */
void laser_drone_stop_sound(Object *obj) {
    sound_stop(obj->vars.enemy.unk_260[2]);
}

extern s16 *laser_drone_data[];
extern s16 laser_drone_script[];
extern s32 laser_drone_asset[3];
extern ScriptCallEntry laser_drone_script_calls[];
extern StateEntry laser_drone_states[];
extern s16 *rocket_drone_anim[];
extern s16 *d_80116CC0;
void laser_drone_phase0(Object *obj, ObjHandler *handler);
void laser_drone_update(Object *obj, ObjHandler *handler);
void laser_drone_draw(Object *obj, ObjHandler *handler);
void laser_drone_stop_sound(Object *obj);
s32 laser_drone_spawn(Placement *place) {
    Object *obj;
    s32 sound;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    *(s16 *)&place->unk_00[2] = 0x708;
    obj->handlers[0].fn = laser_drone_phase0;
    obj->handlers[1].fn = laser_drone_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = laser_drone_draw;
    obj->callback = (s32)obj_destroy_effect;
    obj->destructor = laser_drone_stop_sound;
    obj->asset = laser_drone_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = laser_drone_script_calls;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->kind = 1;
    obj->state_table = laser_drone_states;
    script_start((Script *)obj, laser_drone_script, (s32)&laser_drone_data);
    obj->script.data = rocket_drone_anim;
    obj->script.unk_0A = 0;
    obj->script.pc = d_80116CC0;
    obj_init_from_place(obj, place, 0x37);
    obj->speed = 6;
    obj_set_part_bounds(obj, 8, 0x1000);
    obj->vars.laser_drone.unk_252 = 6;
    obj->vars.laser_drone.unused_248 = 0;
    obj->vars.laser_drone.unused_24A = 1;
    obj->vars.enemy.sound_channel[1] = 0;
    obj->vars.h.unk_258 = 0;
    obj->vars.h.unk_25A = 0x64;
    obj->vars.laser_drone.hit_timer = 0;
    obj->vars.laser_drone.unk_25E = 0;
    *(s16 *)&obj->vars.enemy.unk_260[0] = 0;
    obj->vars.laser_drone.base_y = obj->y;
    obj->vars.laser_drone.heading_angle = (u16)obj->yaw;
    obj->vars.enemy.sound_channel[0] = (u16)obj->vars.enemy.sound_channel[0] - 7;
    sound = sound_start(SND_LASER_DRONE_LOOP | SND_HELD | SND_GROUP(2), 0x40, 0, 0);
    obj->vars.enemy.unk_260[2] = sound;
    sound_attach(sound & 0xFF, &obj->x, NULL);
    sound_set_flag_bit2(obj->vars.enemy.unk_260[2], 1);
    return 1;
}

/* Aims at the player from pos: yaw + 0x800 goes to rot[1], the muzzle offset (0, -0xA8, 0x46) is turned by the
 * angles and added to pos, and a spark is added there with the enemy's 0x25E level as its colour. */
void enemy_aim_spark(Object *obj, Vec3 *pos, s16 *rot) {
    s32 offset_x, offset_y, offset_z;
    s32 yaw, pitch;
    s32 *player;
    Vec3 *spark_pos;
    s32 value;
    s32 packed;
    s32 level;
    s32 shade;
    s32 colour;

    player = player_position();
    spark_pos = scratch_alloc(0x10);
    offset_y = -0xA8;
    offset_x = 0;
    offset_z = 0x46;
    value = get_model_slot_base() + 0xF;
    pitch = 0;
    yaw = 0;
    vector_to_angles(pos->x - player[0], pos->y - player[1], pos->z - player[2], &yaw, &pitch);
    rot[1] = yaw + 0x800;
    vec3_rotate(rot[1], rot[0], rot[2], &offset_x, &offset_y, &offset_z);
    spark_pos->x = pos->x + offset_x;
    spark_pos->y = pos->y + offset_y;
    spark_pos->z = pos->z + offset_z;

    packed = (u16)obj->vars.laser_drone.unk_25E << 16;
    if (obj->vars.jitter.timer == 1) {
        value = pool_spawn_scaled(value, 0x2000, 0x2000, 0);
        obj->vars.jitter.timer = 0;
    }
    level = packed >> 21;
    shade = level;
    if (level == 0) {
        shade = 1;
    }
    colour = (shade << 16) | (level << 8) | level;
    spark_add(spark_pos->x, spark_pos->y, spark_pos->z, 0, 0, 0, value, colour);
    scratch_top -= 0x10;
}

/* Draws the laser drone as five sparks: the body and four parts, each offset from the drone's position by the
 * drone's rotation and turned by its own yaw (vars.h.unk_252/254/256 for parts 2-4). Parts 2 and 3 are drawn every
 * other frame (vars.h.unk_248 toggles) unless the game is paused; all sparks flash 0x60C0FF while hit. Then the
 * muzzle spark (enemy_aim_spark), the aim marker sized from unk_1E4/height/unk_1E8, and the hit flag reset. */
void laser_drone_draw(Object *obj, ObjHandler *handler) {
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

    enemy_aim_spark(drone, base, (s16 *)rot);
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

/* Aims an effect from a point 0x6C above the object's position toward the player (yaw + 0x800), turns a
 * muzzle offset (0, -0x3C, 0xAA) by those angles and spawns the effect there. */
void laser_drone_fire(Object *obj) {
    s32 *player = player_position();
    Vec3 *base = scratch_alloc(0x10);
    Vec3 *pos = scratch_alloc(0x10);
    u16 *rot = scratch_alloc(8);
    s32 yaw, pitch;
    s32 ox, oy, oz;
    s32 p;
    s32 new_pitch;

    base->x = obj->x >> 12;
    base->y = obj->y >> 12;
    base->z = obj->z >> 12;
    p = obj->pitch;
    rot[0] = -p;
    pitch = 0;
    yaw = 0;
    ox = 0;
    rot[1] = obj->yaw;
    oy = -0x3C;
    rot[2] = obj->roll;
    oz = 0xAA;
    base->y -= 0x6C;
    vector_to_angles(base->x - player[0], base->y - player[1], base->z - player[2], &yaw, &pitch);
    rot[1] = yaw + 0x800;
    new_pitch = pitch;
    rot[0] = new_pitch;
    vec3_rotate((s16)rot[1], (s16)new_pitch, (s16)rot[2], &ox, &oy, &oz);
    pos->x = ox + base->x;
    pos->y = oy + base->y;
    pos->z = oz + base->z;
    sound_play_at_units(SND_LASER_DRONE_FIRE | SND_GROUP(1), 0x60, 0x3C, pos);
    shot_spawn_obj((s32 *)pos, rot, 3, (obj->damage << 16) | 0x28);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 8;
}
