/* player_flags: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

s32 player_model_on_get(void) {
    return player_model_on_flag;
}

/* Switches a state on or off, calling pchr_set_entry_flags only when it changes. */
void player_model_enable(s32 on) {
    if (on != 0) {
        if (player_model_enabled == 0) {
            pchr_set_entry_flags(player_model_pchr + 1, 0xFB3B87E7);
        }
    } else if (player_model_enabled != 0) {
        pchr_set_entry_flags(player_model_pchr + 1, 0);
    }
    player_model_enabled = on;
}

void player_model_state_set(s32 value) {
    player_model_state = value;
    player_model_enable(value);
}

/* Set the view position cam_blend_view blends from. */
void cam_view_pos_set(s32 x, s32 y, s32 z) {
    cam_view_pos_x = x;
    cam_view_pos_y = y;
    cam_view_pos_z = z;
}

s32 *cam_view_pos_get(void) {
    return &cam_view_pos_x;
}

/* Set the look-at point cam_blend_view blends from. */
void cam_look_at_set(s32 x, s32 y, s32 z) {
    cam_look_at_x = x;
    cam_look_at_y = y;
    cam_look_at_z = z;
}

/* Sets fade_level to value limited to 0..0x1000. */
void fade_level_set(s32 value) {
    s32 result = cap_1000(value);

    if (cap_1000(value) < 0) {
        result = 0;
    }
    fade_level = result;
}

s32 fade_level_get(void) {
    return fade_level;
}

void set_player_mode_flags(s32 value) {
    player_mode_bits = value;
}

s32 player_mode_flags(void) {
    return player_mode_bits;
}

void player_ceiling_limit_set(s32 value) {
    player_ceiling_limit = value;
}

s32 player_ceiling_limit_get(void) {
    return player_ceiling_limit;
}
