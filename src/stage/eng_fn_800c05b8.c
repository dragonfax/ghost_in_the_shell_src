/* Shared by s06, s07, s09: obj_muzzle_effect. */

#include "stage.h"

/* Builds a rotated offset and a rotation from the object, and calls sound_play_at_units and shot_spawn_trace with the object's position added. */
void obj_muzzle_effect(Object *obj) {
    s32 *dir = scratch_alloc(0x20);
    Vec3 *pos = (Vec3 *)(dir + 4);
    SVECTOR *rot = scratch_alloc(8);

    dir[0] = 0;
    dir[1] = -0xBC;
    dir[2] = -0x6C;
    rotate_xz_twice(obj->yaw, -obj->pitch, dir, dir + 1, dir + 2);
    rot->vx = -obj->pitch;
    rot->vy = obj->vars.h.unk_252;
    rot->vz = obj->roll;
    pos->x = -0x18;
    pos->y = 0xE;
    pos->z = 0xCA;
    rotate_xz_twice(rot->vy, rot->vx, &pos->x, &pos->y, &pos->z);
    pos->x = (obj->x >> 12) + dir[0] + pos->x;
    pos->y = (obj->y >> 12) + dir[1] + pos->y;
    pos->z = (obj->z >> 12) + dir[2] + pos->z;
    sound_play_at_units(SND_MUZZLE_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    shot_spawn_trace(pos, rot, 0);
    scratch_top -= 0x28;
}
