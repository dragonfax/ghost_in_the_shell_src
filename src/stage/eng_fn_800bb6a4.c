/* Shared by s01, s03, s10: shot_burst_spawn..rocket_fuchikoma_update (3 functions). */

#include "stage.h"

/* Spawns an effect at a random offset (three 11-entry tables) from a point in front of the object. */
void shot_burst_spawn(Object *obj) {
    s32 *pos = scratch_alloc(0x20);
    SVECTOR *rot = scratch_alloc(8);
    s32 *pos2;
    s32 idx;

    rot->vx = -obj->vars.h.unk_248 + 0x100;
    rot->vy = obj->yaw;
    rot->vz = 0;
    pos[1] = -0x88;
    pos[0] = 0;
    pos[2] = -0x2C;
    rotate_xz_twice(rot->vy, -obj->pitch, pos, pos + 1, pos + 2);
    pos2 = pos + 4;
    idx = rand_a_next() * 11 / 4096;
    pos2[0] = spawn_offset_x_table[idx];
    pos2[1] = spawn_offset_y_table[idx] - 0x42;
    pos2[2] = spawn_offset_z_table[idx] + 0x50;
    rotate_xz_twice(rot->vy, rot->vx, pos2, pos2 + 1, pos2 + 2);
    pos2[0] = (obj->x >> 12) + pos[0] + pos2[0];
    pos2[1] = (obj->y >> 12) + pos[1] + pos2[1];
    pos2[2] = (obj->z >> 12) + pos[2] + pos2[2];
    sound_play_at_units(SND_ENEMY_BURST_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos2);
    shot_spawn_obj(pos2, (u16 *)rot, 2, (s32)&shot_params);
    scratch_top -= 0x28;
}

/* Handler step: result -2 counts vars.h.unk_248 down and then finishes with state 3 and 0x3C steps left,
 * -1 starts the next state, and every 12th step of a running count calls shot_burst_spawn. */
void obj_countdown_step(Object *obj, ObjHandler *handler) {
    s32 result = handler->result;

    switch (result) {
    case -2:
        if (obj->vars.h.unk_248 >= -0xC7) {
            obj->vars.h.unk_248 -= 0x10;
        } else {
            handler->queued_entry = -1;
            handler->result = 0x3C;
            obj->vars.h.unk_258 = 3;
        }
        break;
    case -1:
        obj_request_state(obj, handler, 0, 0);
        break;
    default:
        if ((s16)obj->vars.h.unk_258 > 0 && result % 12 == 0) {
            shot_burst_spawn(obj);
            obj->vars.h.unk_258 = obj->vars.h.unk_258 - 1;
        }
        break;
    }
}

void rocket_fuchikoma_update(Object *obj, ObjHandler *handler) {
    if (obj->health > 0) {
        obj_script_step(obj, handler);
    }
}
