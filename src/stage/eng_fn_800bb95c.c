/* Shared by s01, s03, s05, s07, s10: rocket_fuchikoma_draw..params_reset (2 functions). */

#include "stage.h"

void rocket_fuchikoma_draw(Object *obj, ObjHandler *handler) {
    Vec3 *pos;
    SVECTOR *rot;
    s32 colour;
    s32 *poses;
    s32 slot;
    SVECTOR *trans;

    pos = scratch_alloc(0x10);
    rot = scratch_alloc(0x18);
    slot = obj_keyframe_value(obj, 0);
    trans = &rot[1];
    if (obj->health > 0) {
        pchr_lists_build(slot);
        slot = pchr_copy_slot(slot);
        poses = pchr_poses_build(slot);
        pchr_table[slot & 0x7FF].unk_0C = poses;
        rot[0].vx = 0;
        rot[0].vy = -0x88;
        rot[0].vz = -0x2C;
        trans->vx = -obj->vars.h.unk_248;
        trans->vy = 0;
        trans->vz = 0;
        pose_rotate_range(poses, 5, 1, rot, trans);
        pose_rotate_range(poses, 7, 1, rot, trans);
    }
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
        colour = 0;
        colour = 0;
    }
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    spark_add(pos->x >> 12, pos->y >> 12, pos->z >> 12, obj->yaw, 0, 0, slot, colour);
    aim_marker_draw(2, (SVECTOR *)&obj->width, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x28;
}

void params_reset(void) {
    params_set_defaults();
}
