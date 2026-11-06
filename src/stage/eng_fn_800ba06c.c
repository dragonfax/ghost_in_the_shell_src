/* Shared by s06, s11: obj_in_view_angle (1 function); not yet decompiled. */

#include "stage.h"

s32 obj_in_view_angle(Object *obj, s32 max_yaw, s32 max_pitch) {
    s32 pos[3];
    s32 yaw;
    s32 pitch;
    register s32 ok asm("$2");

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    point_to_view_angles(pos[0], pos[1], pos[2], &yaw, &pitch);
    if (yaw > 0x800) {
        yaw = 0x1000 - yaw;
    }
    if (pitch > 0x800) {
        pitch = 0x1000 - pitch;
    }
    ok = 0;
    if (yaw < max_yaw) {
        ok = pitch < max_pitch;
    }
    return ok;
}
