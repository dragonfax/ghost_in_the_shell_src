/* cam_zone: one of the original source files (scripts/objmap.py); s02, s10, s11. */

#include "stage.h"

#if STAGE == 2
void cam_zone_setup(void) {
    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(0xB9E, -0x29AC, -0x1140);
    cam_look_at_set((s32) cam_pos >> 0xC, (s32) cam_pos_y >> 0xC, (s32) cam_pos_z >> 0xC);
    fade_level_set(0);
}
#elif STAGE == 10
void cam_zone_setup(void) {
    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(0x8C1, -0x619, 0x2330);
    cam_look_at_set((s32) cam_pos >> 0xC, (s32) cam_pos_y >> 0xC, (s32) cam_pos_z >> 0xC);
    fade_level_set(0);
}
#elif STAGE == 11
void cam_zone_setup(void) {
    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(0xFD, -0x168, 0x147E);
    cam_look_at_set((s32) cam_pos >> 0xC, (s32) cam_pos_y >> 0xC, (s32) cam_pos_z >> 0xC);
    fade_level_set(0);
}
#endif

void cam_zone_fade_step(void) {
    s32 pos;
    s32 next;
    s32 clamped;

    pos = fade_level_get();
    if (pos != 0x1000) {
        cam_look_at_set(cam_pos >> 12, cam_pos_y >> 12, cam_pos_z >> 12);
        next = pos + 0x28;
        clamped = 0x1000;
        if (next < 0x1001) {
            clamped = next;
        }
        pos = clamped;
        fade_level_set(pos);
        if (pos == 0x1000) {
            set_d_801202C8(1);
            set_stage_flags(get_stage_flags() & ~0x28);
        }
    }
}
