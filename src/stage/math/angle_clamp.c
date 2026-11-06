/* angle_clamp: one of the original source files (scripts/objmap.py); s08, s10. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

static inline s32 cap_200(s32 v) {
    if (v > 0x200) {
        v = 0x200;
    }
    return v;
}

/* An angle (low 12 bits) limited to 0..0x200 in its first half turn, 0xEE4..0xFFF in its second. */
s16 angle_clamp_pitch(s32 angle) {
    s32 result;

    angle &= 0xFFF;
    if (angle >= 0x801) {
        result = MAX(cap_FFF(angle), 0xEE4);
    } else {
        result = NOT_NEGATIVE(cap_200(angle));
    }
    return result;
}

void dir_to_angles_clamped(Vec3 *dir, SVECTOR *out) {
    s32 yaw;
    s32 pitch;

    angles_to_player(dir->x, dir->y, dir->z, &yaw, &pitch);
    out->vy = yaw;
    out->vx = -angle_clamp_pitch((s16)pitch);
    out->vz = 0;
}
