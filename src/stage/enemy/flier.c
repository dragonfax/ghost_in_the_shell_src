/* flier: one of the original source files (scripts/objmap.py); s04, s06. */

#include "stage.h"

void obj_phase0_default(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

void flier_keep_range(s16 *actor, s32 *pos, s32 *out, s32 speed, s32 range) {
    s32 dx;
    s32 dz;
    s32 dist;
    s32 dir;

    dir = speed;
    dx = (cam_pos_z - pos[2]) >> 12;
    dz = (cam_pos - pos[0]) >> 12;
    if (((((atan2(dx, dz) - actor[2]) & 0xFFF) - 0x400) & 0xFFF) < 0x800) {
        dir = -dir;
    }
    dist = isqrt(length_sq(dz, 0, dx));
    if (dist < range - 0x40) {
        dir = -dir;
    } else if (dist < range) {
        return;
    }
    fly_strafe(actor[2], dir, out + 2, out);
}
