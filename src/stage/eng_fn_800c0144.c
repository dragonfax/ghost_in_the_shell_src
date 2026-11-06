/* Shared by s06, s07, s09: obj_face_target_update..obj_turn_step (4 functions). */

#include "stage.h"

void obj_face_target_update(Object *obj) {
    obj_sound_held_stop(obj);
    obj_track_player(obj, 0x18, 8);
    if (((ObjTail *) obj)->unk_284 == 0) {
        obj_sound2_start(obj);
    }
    obj_avoid_walls(obj);
}

/* Slow the object by 0x2AA per step (stopping at zero, then calling the handler with state 0),
   and move it along its yaw; the new position goes to 0x208/0x210. */
void obj_decelerate_move(Object *obj, ObjHandler *handler) {
    s32 dx;
    s32 dz;
    s32 speed;

    obj_sound_held_stop(obj);
    if (*(s16 *)&obj->vars.words[15] == 0) { /* 0x284, not named yet */
        obj_sound2_stop(obj);
    }
    speed = obj->speed;
    if (speed >= 0) {
        speed -= 0x2AA;
        obj->speed = speed;
        if (speed <= 0) {
            obj->speed = 0;
            obj_request_state(obj, handler, 0, 0);
        }
    }
    fly_move(obj->yaw, obj->speed >> 12, &dx, &dz);
    obj->vx = dz;
    obj->vz = dx;
}

void obj_fire_muzzle(Object *obj) {
    s32 *pos;
    s16 *rot;
    s32 *target;
    s32 pitch_step;
    s32 y;

    pos = scratch_alloc(0x30);
    rot = scratch_alloc(8);

    pos[4] = 0;
    pos[5] = -0xBC;
    pos[6] = -0x6C;
    rotate_xz_twice(obj->yaw, -obj->pitch, &pos[4], &pos[5], &pos[6]);

    rot[0] = -obj->vars.h.unk_250;
    rot[1] = obj->vars.h.unk_252;
    rot[2] = 0;
    pos[8] = 0x23;
    pos[9] = 0;
    pos[10] = 0x84;
    rotate_xz_twice(rot[1], rot[0], &pos[8], &pos[9], &pos[10]);

    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0xA6;
    rotate_xz_twice(rot[1], rot[0], &pos[0], &pos[1], &pos[2]);

    pos[0] = (obj->x >> 12) + pos[4] + pos[8] + pos[0];
    pos[1] = (obj->y >> 12) + pos[5] + pos[9] + pos[1];
    pos[2] = (obj->z >> 12) + pos[6] + pos[10] + pos[2];

    if (*(s16 *)&obj->vars.words[15] != 2) {
        shot_spawn_obj(pos, rot, 1, (obj->damage << 16) | 1);
    } else {
        target = scratch_alloc(0x10);
        target[0] = obj->vx >> 12;
        target[1] = obj->vy >> 12;
        target[2] = obj->vz >> 12;

        pitch_step = obj->unk_1E8[0] * (s16)rcossin_tbl[(u16)obj->pitch & 0xFFF] / 4096;
        pos[1] += abs(pitch_step);

        shot_spawn_target(pos, rot, target, 1, (obj->damage << 16) | 1);
        scratch_top -= 0x10;
    }

    obj_sound_attach_start(obj);
    scratch_top -= 0x38;
}

void obj_fire_muzzle(Object *obj);
/* Behaviour step. handler->result == -2 means "turn toward the player": it sets the turn speed
   (vars.part.unk_280) to -12 or +12 for the shorter way round from the heading at 0x252 to the
   bearing of the player. Otherwise the heading moves by the turn speed, and obj_fire_muzzle runs on
   every sixth result. */
void obj_turn_step(Object *obj, ObjHandler *handler) {
    s32 result = handler->result;
    s32 heading;
    s32 bearing;
    s32 diff;
    s32 turn;
    s32 *player;

    if (result == -2) {
        handler->queued_entry = -1;
        handler->result = 0x5A;
        player = player_position();
        bearing = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
        heading = *(s16 *)&obj->vars.fly.phase;
        heading &= 0xFFF;
        if (heading >= 0x801) {
            heading -= 0x1000;
        }
        bearing &= 0xFFF;
        if (bearing >= 0x801) {
            bearing -= 0x1000;
        }
        diff = (heading - bearing) & 0xFFF;
        if (diff >= 0x801) {
            diff -= 0x1000;
        }
        turn = -1;
        if (diff >= 0) {
            turn = 1;
        }
        obj->vars.part.unk_280 = -(turn * 12);
        return;
    }
    obj_avoid_walls(obj);
    obj->vars.fly.phase += obj->vars.part.unk_280;
    if (result == (result / 6) * 6) {
        obj_fire_muzzle(obj);
    }
}
