/* giant_robot_systems: one of s01's own original source files (scripts/objmap.py); part of src/s01/main.c's unit, included there. */

/* Runs when giant_robot_fx_active is set and the countdown giant_robot_fx_timer reaches below zero: rebuilds two
 * position/rotation sets from the object at giant_robot_fx_owner (x, y, z >> 12, pitch, yaw, roll) and
 * calls obj_point_to_world and shot_spawn_obj for each; then the countdown restarts at 8. */
void giant_robot_side_fx_tick(void) {
    s16 box[3];
    s16 rot[3];
    s32 pos[3];
    s32 pitch;
    s32 unused[2];  /* only sizes the frame to match the original */
    Object *obj;

    if (giant_robot_fx_active == 0) {
        return;
    }
    if (--giant_robot_fx_timer >= 0) {
        return;
    }

    obj = giant_robot_fx_owner;
    box[0] = 0x17;
    box[1] = -0x1E0;
    box[2] = 0xBF;

    pos[0] = obj->x >> 12;
    pos[1] = (obj->y >> 12) - 0x1E0;
    pos[2] = obj->z >> 12;

    pitch = obj->pitch;
    rot[0] = pitch;
    rot[1] = (u16) obj->yaw;
    rot[2] = (u16) obj->roll;
    rot[0] = pitch - 0x80;

    rot_turn_toward(pos, rot, 0x80, 0x40);
    obj_point_to_world(obj, box, pos, &pos[1], &pos[2]);
    shot_spawn_obj(pos, rot, 1, 0x80001);

    box[0] = -0x17;
    box[1] = -0x1E0;
    box[2] = 0xBF;
    obj_point_to_world(obj, box, pos, &pos[1], &pos[2]);
    shot_spawn_obj(pos, rot, 1, 1);

    giant_robot_fx_timer = 8;
}

void giant_robot_fx_set_active(s32 flag) {
    giant_robot_fx_active = flag;
    if (flag == 0) {
        giant_robot_fx_timer = 0;
    }
}

extern s32 giant_robot_fx_timer;
extern s32 giant_robot_fx_active;

void giant_robot_fx_bind(s32 owner) {
    giant_robot_fx_owner = (Object *)owner;
    giant_robot_fx_timer = 0;
    giant_robot_fx_active = 0;
}

void giant_robot_fx_tick(void) {
    if (giant_robot_systems_active != 0) {
        giant_robot_side_fx_tick();
    }
}

extern s32 giant_robot_systems_active;

void giant_robot_systems_update(void) {
    if (giant_robot_systems_active != 0) {
        fade_step();
        giant_robot_sound_update();
        keyframe_update_all();
        sway_update();
        keyframe_ramp_update_all();
        shots_update();
        loop_state_update();
    }
}
extern s32 giant_robot_systems_active;


void giant_robot_shots_tick(void) {
    if (giant_robot_systems_active != 0) {
        sound_pair_run_copy();
        shots_trace();
    }
}

void giant_robot_systems_draw(void) {
    if (giant_robot_systems_active != 0) {
        giant_robot_spark_draw();
        keyframe_run_all();
        rec_list_update();
        keyframe_ramp_run_all();
        shot_draw_all();
        loop_state_spark_emit();
    }
}

void giant_robot_systems_init(s32 flag) {
    fade_in_full();
    sound_loop_reset(flag);
    keyframe_clear_all();
    sway_disable();
    keyframe_ramp_clear_all();
    shot_pool_clear();
    loop_state_init();
    obj_clear_target();
    giant_robot_fx_bind(flag);
    giant_robot_systems_active = 1;
}

/* Runs the teardown of the systems that giant_robot_systems_active enables, once. */
void giant_robot_systems_teardown(void) {
    if (giant_robot_systems_active != 0) {
        giant_robot_systems_active = 0;
        fade_clear();
        sound_loop_clear();
        keyframe_reset();
        sway_stop();
        keyframe_ramp_reset();
        shot_pool_reset();
        loop_state_stop();
    }
}
