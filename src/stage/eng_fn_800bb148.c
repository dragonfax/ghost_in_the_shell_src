/* Shared by s01, s03, s05, s07, s10: params_set_defaults..obj_face_player (4 functions). */

#include "stage.h"

/* Sets the shot_params parameters to their defaults. */
void params_set_defaults(void) {
    shot_params.hit_effect_index = 1;
    shot_params.speed = 0x8000;
    shot_params.max_speed = 0x18000;
    shot_params.speed_delta = 0x400;
    shot_params.launch_age = 0x28;
    shot_params.homing_duration = 0x46;
    shot_params.unk_14 = 0x10;
    shot_params.unk_16 = 0x10;
    shot_params.smoke_period = 3;
    shot_params.smoke_arg = 0xE;
    shot_params.smoke_limit = 0x14;
    shot_params.unk_0C = 0xF;
    shot_params.turn_start_age = 0;
    shot_params.unk_20 = 0x28;
    shot_params.turn_step = 0xAA;
}

void obj_read_s32(Object *obj) {
    s32 lo = obj_read_s16(obj);
    s32 hi = obj_read_s16(obj) << 16;

    obj->vars.words[2] = (lo & 0xFFFF) | hi;
}

/* Sets the object's aim (vars.h.unk_254, an angle) toward a randomly jittered point of its placement. */
void obj_aim_jittered(Object *obj) {
    PlacedTarget *placement = (PlacedTarget *)obj->placement;
    s32 span = 0x1388;
    s32 jitter;
    s32 target_x;
    s32 target_z;

    jitter = ((s32) (rand_a_next() * span) / 4096) - 0x9C4;
    target_x = placement->x + jitter;
    jitter = ((s32) (rand_a_next() * span) / 4096) - 0x9C4;
    target_z = placement->z + jitter;
    obj->vars.h.unk_254 = atan2((target_z - obj->z) >> 12, (target_x - obj->x) >> 12);
}

/* Sets the object's unk_254 angle to point at the player. */
void obj_face_player(Object *obj) {
    s32 *pos = player_position();
    s32 dx = pos[0] - (obj->x >> 12);
    s32 dz = pos[2] - (obj->z >> 12);

    obj->vars.h.unk_254 = atan2(dz, dx);
}
