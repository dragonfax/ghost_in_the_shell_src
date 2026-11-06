/* Shared by s04, s05: fly_shoot_update..fly_sweep (2 functions). */

#include "stage.h"

void fly_shoot_update(Object *obj) {
    s32 step_x = 0;
    s32 step_z = 0;
    u16 timer;

    fly_move(obj->yaw, obj->speed, &step_x, &step_z);
    timer = obj->vars.h.unk_252;
    obj->vz = step_x;
    obj->vx = step_z;
    obj->vars.h.unk_252 = timer - 1;
    if ((s16) timer < 0) {
        obj_fire_projectile(obj);
        obj->vars.h.unk_252 = 0x1E;
    }
}

#if STAGE == 4
void fly_sweep(Object *obj) {
    s32 dx;
    s32 dz;

    dx = 0;
    dz = 0;
    if (obj->vars.h.unk_254 == 0) {
        obj->yaw += 2;
    } else {
        obj->yaw -= 2;
    }
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj->vy = 0x4000;
    obj->vx = dz;
    obj->vz = dx;
}
#elif STAGE == 5
void fly_sweep(Object *obj) {
    s32 dx = 0;
    s32 dz = 0;

    if (obj->vars.enemy.sound_channel[1] == 0) {
        obj->yaw += 2;
    } else {
        obj->yaw -= 2;
    }
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj->vy = 0x4000;
    obj->vx = dz;
    obj->vz = dx;
}
#else
INCLUDE_ASM(STAGE_ASM, fly_sweep);
#endif
