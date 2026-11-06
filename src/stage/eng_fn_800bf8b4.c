/* Shared by s06, s07, s09: script_jump_table..obj_avoid_walls (11 functions). */

#include "stage.h"

void script_jump_table(Object *obj) {
    s16 *script = obj->script.pc;
    s32 op;

    obj->script.pc = script + 1;
    op = *script;
    if (obj_dist_to_target(obj) < 0x80) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
}

void script_player_angle_branch(Object *obj) {
    s32 *player;
    s32 dx;
    s32 dz;
    s32 angle;
    s32 a;
    s32 b;
    s32 c;
    s16 *cursor;
    s32 index;
    ObjLink *link;

    player = player_position();
    dx = (obj->x >> 12) - player[0];
    dz = (obj->z >> 12) - player[2];
    angle = atan2(dz, dx);
    angle += get_flow_angle();

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    index = *cursor;
    link = &obj->script;

    a = angle & 0xFFF;
    if (a >= 0x801) {
        a -= 0x1000;
    }
    b = (-a) & 0xFFF;
    if (b >= 0x801) {
        b -= 0x1000;
    }

    if (b >= 0) {
        c = angle & 0xFFF;
        if (c >= 0x801) {
            c -= 0x1000;
        }
        c = (-c) & 0xFFF;
        if (c >= 0x801) {
            c -= 0x1000;
        }
        if (c < 0x400) {
            goto write;
        }
    } else {
        c = angle & 0xFFF;
        if (c >= 0x801) {
            c -= 0x1000;
        }
        c = (-c) & 0xFFF;
        if (c >= 0x801) {
            c -= 0x1000;
        }
        if (-c < 0x400) {
            goto write;
        }
    }
    return;

write:
    link->pc = ((s16 **)link->data)[index];
}

void tank2_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

void obj_sound_attach_start(Object *obj) {
    if (((u8 *)obj)[0x287] == 0) {
        s32 handle = sound_start(SND_MACHINE_GUN_FIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        sound_attach(handle, &obj->x, 0);
        ((u8 *)obj)[0x287] = (u8)handle;
    }
}

/* Stops the sound handle byte at 0x287 (the object's last byte) if one is set. */
void obj_sound_held_stop(Object *obj) {
    u8 *sound = (u8 *)obj + 0x287;

    if (*sound != 0) {
        sound_stop(*sound);
        *sound = 0;
    }
}

/* Starts the looping sound 0xD442D443 for the object once: unless the halfword at 0x284 is 1 or the
   byte at 0x286 is set, starts the sound, attaches it to the object's position and stores the handle
   in the byte at 0x286. */
void obj_sound2_start(Object *obj) {
    u8 *flags = (u8 *) &obj->vars.tank.unk_284;
    s32 handle;

    if (*(s16 *) flags == 1) {
        return;
    }
    if (flags[2] != 0) {
        return;
    }
    handle = sound_start(SND_PAIR(SND_TRAIN_LOOP | SND_HELD | SND_GROUP(2), SND_TRAIN_LOOP_ALT | SND_HELD | SND_GROUP(2)), 0x40, 0, 0);
    sound_attach(handle, &obj->x, 0);
    sound_set_flag_bit2(handle, 1);
    flags[2] = handle;
}

/* Stops the sound handle byte at 0x286 if one is set. */
void obj_sound2_stop(Object *obj) {
    u8 *sound = (u8 *)obj + 0x286;

    if (*sound != 0) {
        sound_stop(*sound);
        *sound = 0;
    }
}

/* Turns the halfword at 0x252 toward the yaw by up to 6 per step. */
void obj_yaw_step(Object *obj) {
    *(s16 *)((u8 *)obj + 0x252) = angle_approach(*(s16 *)((u8 *)obj + 0x252), obj->yaw, 6);
}

void obj_track_player(Object *obj, s32 yaw_step, s32 pitch_step) {
    s32 yaw;
    s32 pitch;
    s32 dist;
    s32 offset;
    s32 scale;
    s32 cur;
    s32 target;
    s32 diff;
    s32 sign;
    s16 *angles;
    s32 cur_yaw;
    s32 limit;

    angles_to_player(obj->x >> 12, (obj->y >> 12) - ((s16)obj->height / 2), obj->z >> 12, &yaw, &pitch);
    dist = obj_player_distance(obj);
    angles = (s16 *)&obj->vars.h.unk_250;
    dist = MAX(MIN(dist, 2000), 0);
    scale = (dist << 12) / 2000;
    scale = 0x1000 - scale;
    offset = scale * 0x280 / 0x1000;
    cur_yaw = (s16)obj->vars.h.unk_252;
    cur = cur_yaw & 0xFFF;
    target = yaw & 0xFFF;
    if (cur > 0x800) {
        cur -= 0x1000;
    }
    if (target > 0x800) {
        target -= 0x1000;
    }
    diff = (cur - target) & 0xFFF;
    if (diff > 0x800) {
        diff -= 0x1000;
    }
    sign = -1;
    if (diff >= 0) {
        sign = 1;
    }
    offset *= sign;
    obj->vars.h.unk_252 = angle_approach(cur_yaw, yaw + offset, yaw_step);
    pitch = angle_approach((s16)obj->vars.h.unk_250, pitch, pitch_step);
    limit = 0x78;
    diff = pitch & 0xFFF;
    if (diff >= 0x800) {
        if (diff < 0xF88) {
            diff = 0xF88;
        }
    } else {
        if (diff > limit) diff = limit;
    }
    angles[0] = diff;
}

/* vars.words[4] and [6] are the target point (0x258, 0x260); 0x1F0..0x1F8 are the position. */
void obj_face_target(Object *obj) {
    s32 z = obj->z;
    obj->yaw = angle_approach(obj->yaw,
                              atan2((obj->vars.words[6] - z) >> 12, (obj->vars.words[4] - obj->x) >> 12),
                              8);
}

void obj_avoid_walls(Object *obj) {
    ObjHandler *handler;
    VECTOR *base;
    VECTOR *probe;
    VECTOR *hit;
    s32 cooldown = 4;
    s32 turn_rate = 16;
    register s32 state asm("$3");
    s32 max;
    s32 flags;
    register s32 hits asm("$19");
    s32 shifted;
    s32 i;
    s32 angle;

    if (*(s16 *)&obj->vars.words[15] != 0) {
        return;
    }
    handler = &obj->handlers[1];
    max = obj->vars.words[12];
    obj->speed += obj->speed_accel;
    flags = obj->ground_flags;
    obj->speed = MAX(CLAMP_HI(obj->speed, max), 0);
    if (flags & 0x3C) {
        state = 3;
    } else {
        state = 0;
        if (obj->handlers[1].timer == 0) {
            base = scratch_alloc(0x30);
            probe = base + 1;
            hit = base + 2;
            base->vx = obj->x >> 12;
            base->vy = obj->y >> 12;
            base->vz = obj->z >> 12;
            base->vy -= 105;
            hits = 0;
            angle = obj->yaw - 300;
            for (i = 0; i < 2; i++) {
                probe->vz = 600;
                probe->vx = 0;
                probe->vy = 0;
                rotate_xz_twice(angle, 0, &probe->vx, &probe->vy, &probe->vz);
                probe->vx += base->vx;
                probe->vy += base->vy;
                probe->vz += base->vz;
                shifted = hits << 1;
                if (trace_world(8, 100, base, probe, hit) != 0) {
                    hits = shifted | 1;
                } else {
                    hits = shifted;
                }
                angle += 600;
            }
            scratch_top -= 0x30;
            state = hits;
            handler->timer = cooldown;
        }
    }
    switch (state) {
    case 0:
        if (handler->turn_timer == 0) {
            obj_face_target(obj);
            break;
        }
        goto turn;
    case 1:
        if (handler->turn_timer == 0) {
            obj->unk_226[0] = -16;
        }
        break;
    case 2:
        if (handler->turn_timer == 0) {
            obj->unk_226[0] = turn_rate;
        }
        break;
    case 3:
        if (handler->turn_timer == 0) {
            handler->turn_timer = 30;
        }
    turn:
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
