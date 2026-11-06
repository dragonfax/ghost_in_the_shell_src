/* stationary_rocket_launcher: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

/* The stage's model and message files: data tables point to them by address. */
const char file_kitt_tp0_clt[] = "kitt_tp0.clt";
const char file_kitt_ch0_clt[] = "kitt_ch0.clt";
const char file_kitt_tp0_xs3[] = "kitt_tp0.xs3";
const char file_kitt_ch0_vx1[] = "kitt_ch0.vx1";
const char file_kitt_ch0_cb4[] = "kitt_ch0.cb4";
const char file_arkb_tp0_clt[] = "arkb_tp0.clt";
const char file_arkb_ch0_clt[] = "arkb_ch0.clt";
const char file_arkb_tp0_xs3[] = "arkb_tp0.xs3";
const char file_arkb_ch0_vx1[] = "arkb_ch0.vx1";
const char file_arkb_ch0_cb4[] = "arkb_ch0.cb4";
const char file_horo_tp0_clt[] = "horo_tp0.clt";
const char file_horo_ch0_clt[] = "horo_ch0.clt";
const char file_horo_tp0_xs3[] = "horo_tp0.xs3";
const char file_horo_ch0_vx1[] = "horo_ch0.vx1";
const char file_horo_ch0_cb4[] = "horo_ch0.cb4";
const char file_fap2_tp1_clt[] = "fap2_tp1.clt";
const char file_fap2_tp0_clt[] = "fap2_tp0.clt";
const char file_fap2_ch0_clt[] = "fap2_ch0.clt";
const char file_fap2_tp1_xs3[] = "fap2_tp1.xs3";
const char file_fap2_tp0_xs3[] = "fap2_tp0.xs3";
const char file_fap2_ch0_vx1[] = "fap2_ch0.vx1";
const char file_fap2_ch0_cb4[] = "fap2_ch0.cb4";
const char file_tnk2_tp0_clt[] = "tnk2_tp0.clt";
const char file_tnk2_ch0_clt[] = "tnk2_ch0.clt";
const char file_tnk2_tp0_xs3[] = "tnk2_tp0.xs3";
const char file_tnk2_ch0_vx1[] = "tnk2_ch0.vx1";
const char file_tnk2_ch0_cb4[] = "tnk2_ch0.cb4";

extern s32 rocket_shot_params;
extern s32 D_80125FAC;
extern s32 D_80125FB0;
extern s16 D_80125FB4;
extern s16 rocket_shot_hit_effect_index;
extern s16 D_80125FB8;
extern s16 D_80125FBA;
extern s16 D_80125FBC;
extern s16 D_80125FBE;
extern s16 D_80125FC0;
extern s16 D_80125FC2;
extern s16 D_80125FC4;
extern s16 D_80125FC6;
extern s16 D_80125FC8;
extern s16 D_80125FCA;
void stationary_rocket_launcher_defaults(void) {
    rocket_shot_params = 0xC000;
    D_80125FAC = 0x2A000;
    D_80125FB0 = 0x800;
    rocket_shot_hit_effect_index = 0;
    D_80125FB8 = 0x2A;
    D_80125FBA = 0xDE;
    D_80125FBC = 0x10;
    D_80125FBE = 0x10;
    D_80125FC0 = 0x2A;
    D_80125FC2 = 3;
    D_80125FC4 = 0xE;
    D_80125FB4 = 0xC;
    D_80125FC6 = 0;
    D_80125FC8 = 0x2A;
    D_80125FCA = 0x200;
}

void stationary_rocket_launcher_release_target(Object *obj) {
    Object *target;

    target = (Object *)obj->vars.stationary_rocket_launcher.target;
    if (target != NULL) {
        *(u8 *)&target->vars.enemy.walk_state = 1;
    }
}

static inline s32 ang_in_cone(s32 a, s32 b, s32 cone) {
    if (ANG_ABS_DIFF(a, b) < cone) {
        return 1;
    }
    return 0;
}
static inline s32 obj_heading(Object *obj) {
    return obj->vars.trace.aim_yaw;
}
/* Script op: reads a cone half-width and a jump-table index; jumps when the player lies within the cone
 * around the object's heading. The first read is written out (not obj_read_s16) and the heading goes
 * through an inline: both are needed for the original's registers. */
void script_op_jump_if_player_in_cone(Object *obj) {
    ObjLink *link = &obj->script;
    s32 heading = obj_heading(obj);
    s16 *script = obj->script.pc;
    s32 cone;
    s32 target;
    s32 *player;
    s32 dx;

    obj->script.pc = script + 1;
    cone = *script;
    target = obj_read_s16(obj);
    player = player_position();
    dx = player[0] - (obj->x >> 12);

    if (ang_in_cone(heading, atan2(player[2] - (obj->z >> 12), dx), cone)) {
        link->pc = ((s16 **)link->data)[target];
    }
}

void stationary_rocket_launcher_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}


/* Sets up the object's position (x, y, z) from i. Returns 0. */
s32 sound_follow_obj(Object *obj, s32 i) {
    sound_set_pos(i, (Vec3 *)&obj->x);
    return 0;
}


/* Starts the looping sound (id 0xD4B2) on first call and attaches sound_follow_obj
 * as its update; the handle is kept at vars.enemy.unk_258 so later calls do nothing. */
void func_800B76AC(Object *obj) {
    s32 handle;

    if (obj->vars.stationary_rocket_launcher.sound_channel == 0) {
        handle = sound_start(0xD4B2, 0x60, 0, 0);
        obj->vars.stationary_rocket_launcher.sound_channel = handle;
        sound_attach(handle, obj, (void (*)())sound_follow_obj);
    }
}

/* Stops the sound handle at 0x258 if one is playing. */
void enemy_loop_sound_stop(Object *obj) {
    if (obj->vars.stationary_rocket_launcher.sound_channel != 0) {
        sound_stop(obj->vars.stationary_rocket_launcher.sound_channel);
        obj->vars.stationary_rocket_launcher.sound_channel = 0;
    }
}

void enemy_turn_to_player(Object *obj, s32 yaw_step, s32 pitch_step) {
    s32 yaw;
    s32 pitch;
    s32 angle;
    s16 *out;
    s32 lo = 0;

    angles_to_player(obj->x >> 12, (obj->y >> 12) - ((s16)obj->height / 2), obj->z >> 12, &yaw, &pitch);
    yaw = angle_approach(obj->vars.trace.aim_yaw, yaw, yaw_step);
    pitch = angle_approach(obj->vars.stationary_rocket_launcher.aim_pitch, pitch - 0x40, pitch_step);
    angle = pitch & 0xFFF;
    obj->vars.trace.aim_yaw = yaw;
    out = &obj->vars.stationary_rocket_launcher.aim_pitch;
    if (angle >= 0x800) {
        if (angle < 0xE0C) {
            angle = 0xE0C;
        }
    } else if (angle > lo) {
        angle = lo;
    }
    pitch = angle;
    *out = angle;
}

void enemy_turn_to_player(Object *obj, s32 yaw_step, s32 pitch_step);
/* When the handler's behaviour step reports done (result -2), mark it
   finished (unk_0C = -1, result = 1) and run func_800B76AC; then always
   run enemy_turn_to_player on the object. */
void enemy_handler_done(Object *obj, ObjHandler *handler) {
    if (handler->result == -2) {
        handler->queued_entry = -1;
        handler->result = 1;
        func_800B76AC(obj);
    }
    enemy_turn_to_player(obj, 0x10, 8);
}

/* Handler step: when `result` is -2, restarts the countdown (result = 60) and spawns an effect at a random
 * position beside the object, rotated by its angles; when -1, calls obj_request_state. */
void enemy_fire_shot_step(Object *obj, ObjHandler *handler) {
    s32 result = handler->result;
    Vec3 *pos;
    SVECTOR *rot;
    register s32 rz asm("$18");
    s32 rx, left;
    register s32 y asm("$2");

    if (result == -2) {
        enemy_loop_sound_stop(obj);
        pos = scratch_alloc(0x10);
        rot = scratch_alloc(8);
        handler->queued_entry = -1;
        handler->result = 0x3C;
        rx = rand_a_next() / 128;
        left = rx - 0x10;
        rz = rand_a_next() / 128;
        if (rand_a_next() > 0x800) {
            pos->x = rx + 0xB8;
            y = rz - 0xC4;
        } else {
            y = rz - 0xC4;
            pos->x = left;
        }
        pos->y = y;
        do { } while (0);
        pos->z = 0;
        rotate_xz_twice((s16)obj->vars.stationary_rocket_launcher.aim_yaw, -(s16)obj->vars.stationary_rocket_launcher.aim_pitch, &pos->x, &pos->y, &pos->z);
        pos->x = (obj->x >> 12) + pos->x;
        {
            s32 oy = obj->y >> 12;
            s32 dy = pos->y - 0xFA;
            pos->y = oy + dy;
        }
        pos->z = (obj->z >> 12) + pos->z;
        rot->vx = 0x91 - (u16)obj->vars.stationary_rocket_launcher.aim_pitch;
        rot->vy = (u16)obj->vars.stationary_rocket_launcher.aim_yaw;
        rot->vz = 0;
        shot_spawn_obj((s32 *)pos, (u16 *)rot, 2, (s32)&rocket_shot_params);
        sound_play_at_units(SND_STATIONARY_ROCKET_LAUNCH | SND_GROUP(1), 0x5A, 0x3C, pos);
        scratch_top -= 0x18;
    }
    if (result == -1) {
        obj_request_state(obj, handler, 0, 0);
    }
}

void enemy_muzzle_pose(Object *obj, s32 *v, s16 *out) {
    v[0] = 0x69;
    v[1] = 0x2D;
    v[2] = 0x15E;
    rotate_xz_twice((s16)obj->vars.stationary_rocket_launcher.aim_yaw, -obj->vars.stationary_rocket_launcher.aim_pitch, v, v + 1, v + 2);
    v[0] = obj->x + (v[0] << 12);
    v[1] = obj->y + ((v[1] - 0xFA) << 12);
    v[2] = obj->z + (v[2] << 12);
    out[0] = obj->vars.stationary_rocket_launcher.aim_pitch + 0x5C;
    out[1] = obj->vars.stationary_rocket_launcher.aim_yaw;
    out[2] = obj->vars.stationary_rocket_launcher.aim_roll;
}

Object * enemy_spawn_shooter(s32 *pos, s16 *angles, Object *parent);
void enemy_rocket_aim_step(Object *obj, ObjHandler *handler) {
    s32 yaw;
    s32 pitch;
    s32 result;
    s32 *pos;
    s16 *rot;
    s32 diff;
    s32 sign;
    Object *target;

    pos = scratch_alloc(0x10);
    rot = scratch_alloc(8);
    result = handler->result;
    switch (result) {
    case -2:
        enemy_loop_sound_stop(obj);
        enemy_muzzle_pose(obj, pos, rot);
        target = enemy_spawn_shooter(pos, rot, obj);
        obj->vars.stationary_rocket_launcher.target = (s32)target;
        if (target == NULL) {
            obj_request_state(obj, handler, 0, 0);
        }
        handler->queued_entry = -1;
        handler->result = 0x14C;
        break;
    case -1:
        obj_request_state(obj, handler, 0, 0);
        enemy_loop_sound_stop(obj);
        break;
    default:
        if (result > 180) {
            break;
        }
        if (result == 180) {
            angles_to_player(obj->x >> 12, (obj->y >> 12) - (s16)obj->height / 2, obj->z >> 12, &yaw, &pitch);
            diff = angle_diff(obj->vars.trace.aim_yaw, yaw);
            sign = -1;
            if (diff >= 0) {
                sign = 1;
            }
            obj->unk_226[0] = -(sign * 8);
            func_800B76AC(obj);
        }
        if (result == 60) {
            stationary_rocket_launcher_release_target(obj);
        }
        if (result >= 60) {
            enemy_turn_to_player(obj, 0, 2);
            obj->vars.stationary_rocket_launcher.aim_yaw += obj->unk_226[0];
            enemy_muzzle_pose(obj, pos, rot);
            ((Object *)obj->vars.stationary_rocket_launcher.target)->x = pos[0];
            ((Object *)obj->vars.stationary_rocket_launcher.target)->y = pos[1];
            ((Object *)obj->vars.stationary_rocket_launcher.target)->z = pos[2];
            ((Object *)obj->vars.stationary_rocket_launcher.target)->yaw = rot[1];
            ((Object *)obj->vars.stationary_rocket_launcher.target)->pitch = rot[0];
            ((Object *)obj->vars.stationary_rocket_launcher.target)->roll = rot[2];
        }
    }
    scratch_top -= 0x18;
}

void stationary_rocket_launcher_update(Object *obj, ObjHandler *handler) {
    obj_script_step(obj, handler);
}

extern RecTemplate rocket_explode_fx_template;
extern RecTemplate D_8011C558;
/* Destroyed rocket launcher: countdown in sound_channel[0], smoke puffs every
   15 frames, then explosion effects and removal at -1. */
void stationary_rocket_launcher_teardown(Object *obj) {
    s32 *pos;
    s32 dx, dy, dz;
    s32 width, h, half, depth, z;
    s16 ext;

    pos = scratch_alloc(0x10);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    switch (obj->vars.enemy.sound_channel[0]) {
    case -2:
        obj->unk_17A = 0;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        stationary_rocket_launcher_release_target(obj);
        obj->vars.enemy.sound_channel[0] = 60;
        break;
    case -1:
        fx_spawn_template(pos, &rocket_explode_fx_template, NULL);
        fx_spawn_template(pos, &D_8011C558, NULL);
        placement_list_pop((ListRecord *)obj->placement);
        obj->placement->unk_04[0] |= 3;
        enemy_loop_sound_stop(obj);
        sound_play_at(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, &obj->x);
        obj_free(obj);
        break;
    default:
        if ((s16)(obj->vars.enemy.sound_channel[0] % 15) == 0) {
            /* random point: x and z within +-extent, y between half and full height above */
            dx = rand_a_next();
            width = obj->width;
            ext = width;
            dx = dx * (width + ext) / 4096 - ext;

            dy = rand_a_next();
            h = (s16)obj->height;
            half = (s16)h / 2;
            dy = -(dy * (h - half) / 4096 + half);

            dz = rand_a_next();
            depth = obj->unk_1E8[0];
            ext = depth;
            /* two statements: one set fewer would make sched1 hoist the args above it */
            z = dz * (depth + ext) / 4096;
            z -= ext;
            spawn_effect(dx + pos[0], dy + pos[1], z + pos[2], 0);
        }
        obj->vars.enemy.sound_channel[0]--;
        break;
    }
    scratch_top -= 0x10;
}

s32 enemy_cam_range_test(Object *obj) {
    return cam_range_check(obj->x >> 12, obj->y >> 12, obj->z >> 12);
}

void stationary_rocket_launcher_release_target(Object *obj);
void stationary_rocket_launcher_phase2(Object *obj, ObjHandler *handler) {
    Placement *placement;

    if (obj->health > 0 && enemy_cam_range_test(obj) == 0) {
        placement = obj->placement;
        placement_snap_to_obj(placement, obj);
        ((s16 *)placement->unk_00)[1] = 0;
        placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
        stationary_rocket_launcher_release_target(obj);
        enemy_loop_sound_stop(obj);
        obj_free(obj);
        return;
    }
    obj_state_run(obj, handler);
}

void stationary_rocket_launcher_draw(Object *obj, ObjHandler *handler) {
    Vec3 *pos;
    SVECTOR *rot;
    s32 slot;
    s32 colour;
    s32 *poses;
    s32 yaw;

    pos = scratch_alloc(0x10);
    rot = scratch_alloc(0x10);
    slot = pchr_copy_slot(model_slot_pchr(*(s32 *)obj->asset) + 1);
    poses = pchr_poses_build(slot);
    pchr_table[slot & 0x7FF].unk_0C = poses;
    rot[0].vx = 0;
    rot[0].vy = -0xFA;
    rot[0].vz = 0;
    yaw = obj->yaw;
    rot[1].vx = -obj->vars.turret.pitch;
    rot[1].vy = obj->vars.turret.yaw - yaw;
    rot[1].vz = 0;
    pose_rotate_range(poses, 0, 3, rot, &rot[1]);
    pose_rotate_range(poses, 9, 2, rot, &rot[1]);
    rot[1].vx = 0;
    pose_rotate_range(poses, 3, 1, rot, &rot[1]);
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
        colour = 0;
        colour = 0;
    }
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    spark_add(pos->x >> 12, pos->y >> 12, pos->z >> 12, yaw, 0, 0, slot, colour);
    aim_marker_draw(2, (SVECTOR *)&obj->width, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x20;
}

void stationary_rocket_launcher_init(void) {
    stationary_rocket_launcher_defaults();
}

void stationary_rocket_launcher_draw(Object *obj, ObjHandler *handler);
void stationary_rocket_launcher_teardown(Object *obj);
extern s16 *stationary_rocket_launcher_data;
extern char rocket_launcher_asset[];
extern s16 *rocket_launcher_script[];
extern s16 *rocket_launcher_anim_link;
extern ScriptCallEntry D_8011C508[];
extern StateEntry D_8011C520[];
s32 stationary_rocket_launcher_spawn(Placement *place) {
    Object *obj;
    s32 flags;
    s32 teardown_fn;
    s16 **script;
    s32 kind;
    s16 *anim_link;
    register Script *self asm("$4");

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    script = &stationary_rocket_launcher_data;
    __asm__("" : "=r"(self) : "0"(obj)); /* a0 = obj set early, as the original */
    do { } while (0);
    flags = place->unk_04[0];
    place->unk_02 = -1;
    obj->handlers[0].fn = (void *)stationary_rocket_launcher_phase0;
    obj->handlers[1].fn = stationary_rocket_launcher_update;
    obj->handlers[2].fn = stationary_rocket_launcher_phase2;
    obj->handlers[3].fn = stationary_rocket_launcher_draw;
    teardown_fn = (s32)stationary_rocket_launcher_teardown;
    do {
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
    } while (0);
    do {
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
    } while (0);
    do {
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
    } while (0);
    do {
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
    } while (0);
    obj->callback = teardown_fn;
    kind = place->unk_04[1];
    do { } while (0);
    obj->asset = rocket_launcher_asset;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = D_8011C508;
    obj->unk_1C6 = 0;
    obj->state_table = D_8011C520;
    do { } while (0);
    obj->kind = kind;
    do { } while (0);
    anim_link = rocket_launcher_anim_link;
    obj->script.data = rocket_launcher_script;
    obj->script.unk_0A = 0;
    obj->script.pc = anim_link;
    script_start(self, *script, (s32)script);
    obj_init_from_place(obj, place, (flags & 8) ? 0x224 : 0x24);
    obj_set_part_bounds(obj, 1, 0x1000);
    obj->vars.enemy.sound_channel[0] = -2;
    obj->vars.stationary_rocket_launcher.target = 0;
    obj->vars.stationary_rocket_launcher.sound_channel = 0;
    obj->vars.stationary_rocket_launcher.aim_pitch = obj->pitch;
    obj->vars.stationary_rocket_launcher.aim_yaw = obj->yaw;
    obj->vars.stationary_rocket_launcher.aim_roll = obj->roll;
    return 1;
}
