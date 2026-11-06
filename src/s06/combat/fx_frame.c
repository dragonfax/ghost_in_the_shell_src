/* fx_frame: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

void func_800CB288(void) {
}

extern s32 giant_robot_systems_active;

void fx_frame_update(void) {
    if (giant_robot_systems_active != 0) {
        fx_table_update();
        keyframe_table_update();
        attach_update_all();
    }
}
extern s32 giant_robot_systems_active;


void giant_robot_shots_tick(void) {
    if (giant_robot_systems_active != 0) {
        sound_pair_run_copy();
        shots_trace();
    }
}

extern s32 giant_robot_systems_active;

void fx_frame_draw(void) {
    if (giant_robot_systems_active != 0) {
        fx_table_draw();
        keyframe_table_draw();
        attach_draw_all();
    }
}

extern s32 giant_robot_systems_active;

void fx_system_init(void) {
    giant_robot_systems_active = 1;
    fx_table_clear();
    keyframe_table_deactivate_all();
    attach_clear();
}

extern s32 giant_robot_systems_active;

void fx_system_stop(void) {
    if (giant_robot_systems_active != 0) {
        giant_robot_systems_active = 0;
        fx_table_stop_all();
        keyframe_table_stop();
        attach_reset();
    }
}
