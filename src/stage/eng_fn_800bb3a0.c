/* Shared by s01, s03, s05, s07, s10: enemy_wall_steer..obj_settle_offset (2 functions). */

#include "stage.h"

void enemy_wall_steer(Object *obj) {
    s32 hold = 4;
    ObjHandler *handler = &obj->handlers[1];
    s32 step = 0x10;
    s32 *block;
    s32 *slot;
    s32 *hit;
    s32 speed;
    register s32 limit asm("$4");
    s32 clamped;
    s32 flags;
    s32 mode;
    s32 hits;
    s32 blocked;
    s32 angle;
    s32 i;

    speed = obj->speed + obj->speed_accel;
    obj->speed = speed;
    limit = obj->vars.enemy.unk_250;
    flags = obj->ground_flags;
    clamped = CLAMP_HI(speed, limit) < 0 ? 0 : CLAMP_HI(speed, limit);
    obj->speed = clamped;

    if (flags & 0x3C) {
        mode = 3;
    } else {
        mode = 0;
        if (obj->handlers[1].timer == 0) {
            block = scratch_alloc(0x30);
            slot = block + 4;
            hit = block + 8;
            block[0] = obj->x >> 12;
            block[1] = obj->y >> 12;
            block[2] = obj->z >> 12;
            block[1] -= 0x69;
            angle = obj->yaw - 0x190;
            hits = 0;
            for (i = 0; i < 2; i++) {
                slot[2] = 0x190;
                slot[0] = 0;
                slot[1] = 0;
                rotate_xz_twice(angle, 0, slot, slot + 1, slot + 2);
                slot[0] += block[0];
                slot[1] += block[1];
                slot[2] += block[2];
                blocked = trace_world(8, 0x64, block, slot, hit);
                hits <<= 1;
                if (blocked) {
                    hits |= 1;
                }
                angle += 0x320;
            }
            scratch_top -= 0x30;
            mode = hits;
            handler->timer = hold;
        }
    }

    switch (mode) {
    case 0:
        if (handler->turn_timer == 0) {
#if STAGE == 5 || STAGE == 7
            obj_yaw_turn(obj);
#else
            rocket_fuchikoma_turn(obj);
#endif
            break;
        }
        goto spin;
    case 1:
        if (handler->turn_timer == 0) {
            obj->unk_226[0] = -0x10;
        }
        break;
    case 2:
        if (handler->turn_timer == 0) {
            obj->unk_226[0] = step;
        }
        break;
    case 3:
        if (handler->turn_timer == 0) {
            handler->turn_timer = 0x1E;
        }
    spin:
        obj->yaw += obj->unk_226[0];
        break;
    }

    fly_move(obj->yaw, obj->speed >> 12, &obj->vz, &obj->vx);

    if (handler->turn_timer > 0) {
        handler->turn_timer--;
    }
    if (handler->timer > 0) {
        handler->timer--;
    }
}

void obj_settle_offset(Object *obj) {
    s16 value = obj->vars.h.unk_248;

    if (value < 0) {
        obj->vars.h.unk_248 = value + 0x10;
    }
    enemy_wall_steer(obj);
}
