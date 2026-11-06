/* stage_camera: one of the original source files (scripts/objmap.py); s01, s05. */

#include "stage.h"

#if STAGE == 1
void stage_camera_start(void) {
    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(-0x1073, -0x3F0, -0x2BB6);
    cam_look_at_set((s32) cam_pos >> 0xC, (s32) cam_pos_y >> 0xC, (s32) cam_pos_z >> 0xC);
    fade_level_set(0);
}
#elif STAGE == 5
void stage_camera_start(void) {
    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(0x2890, -0x1E0, 0x2FBA);
    cam_look_at_set((s32) cam_pos >> 0xC, (s32) cam_pos_y >> 0xC, (s32) cam_pos_z >> 0xC);
    fade_level_set(0);
}
#endif

void stage_camera_fade_in_step(void) {
    s32 full = 0x1000;
    s32 progress;

    progress = fade_level_get();
    if (progress != full) {
        cam_look_at_set(cam_pos >> 12, cam_pos_y >> 12, cam_pos_z >> 12);
        progress = CLAMP_HI(progress + 0x33, 0x1000);
        fade_level_set(progress);
        if (progress == full) {
            set_d_801202C8(1);
            set_stage_flags(get_stage_flags() & ~0x28);
        }
    }
}
