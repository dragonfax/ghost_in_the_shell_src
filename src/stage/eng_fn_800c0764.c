/* Shared by s06, s07, s09: tank_update..tank_draw (3 functions). */

#include "stage.h"

#if STAGE == 6
/* Main behaviour for state 2: steers the flow toward the object's last move, then runs obj_script_step. */
void tank_update(Object *obj, ObjHandler *handler) {
    Vec3 *pos;
    s32 angle;
    s32 dy;

    if (*(s16 *)&obj->vars.tank.unk_284 == 2) {
        pos = scratch_alloc(0x10);
        FLOW(obj)->speed = get_flow_max() + obj->speed;
        pos->x = obj->x;
        pos->y = obj->y;
        pos->z = obj->z;
        fly_strafe(FLOW(obj)->angle, obj->unk_1E8[0], &pos->z, &pos->x);
        flow_sample(FLOW(obj), obj->width, &pos->x, &obj->vx, &obj->turn);
        scratch_top -= 0x10;
        obj->yaw += obj->turn;
        obj_script_step(obj, handler);
        obj->vx += obj->vars.tank.unk_27C;
        limit_move(&obj->x, &obj->vx);
        dy = (obj->y - obj->vars.tank.prev_y) >> 12;
        angle = atan2(-(get_flow_max() + obj->speed), dy);
        obj->pitch = angle_approach(obj->pitch, angle + 0x800, 8);
        obj->vars.tank.prev_x = obj->x;
        obj->vars.tank.prev_y = obj->y;
        obj->vars.tank.prev_z = obj->z;
    } else {
        obj_script_step(obj, handler);
    }
}
#else
/* Main behaviour for state 2: steers the flow toward the object's last move, then runs obj_script_step. */
void tank_update(Object *obj, ObjHandler *handler) {
    Vec3 *pos;
    s32 angle;
    s32 dy;

    if (*(s16 *)&obj->vars.tank.unk_284 == 2) {
        pos = scratch_alloc(0x10);
        ((Flow *)&obj->vars)->speed = get_flow_max() + obj->speed;
        pos->x = obj->x;
        pos->y = obj->y;
        pos->z = obj->z;
        fly_strafe(((Flow *)&obj->vars)->angle, obj->unk_1E8[0], &pos->z, &pos->x);
        flow_sample((Flow *)&obj->vars, obj->width, &pos->x, &obj->vx, &obj->turn);
        scratch_top -= 0x10;
        obj->yaw += obj->turn;
        obj_script_step(obj, handler);
        obj->vx += obj->vars.tank.unk_27C;
        limit_move(&obj->x, &obj->vx);
        dy = (obj->y - obj->vars.tank.prev_y) >> 12;
        angle = atan2(-(get_flow_max() + obj->speed), dy);
        obj->pitch = angle_approach(obj->pitch, angle + 0x800, 8);
        obj->vars.tank.prev_x = obj->x;
        obj->vars.tank.prev_y = obj->y;
        obj->vars.tank.prev_z = obj->z;
    } else {
        obj_script_step(obj, handler);
    }
}
#endif

s32 tank_sink_step(Object *obj) {
    s32 interval;
    s32 dx;
    s32 dz;
    register s32 timer asm("$19");
    s32 smoke_interval;
    Vec3 *pos;
    s32 alive;
    s16 *timer_p;

    alive = 1;
    timer_p = &obj->vars.tank.sink_timer;
    interval = 10;
    timer = *timer_p;
    switch (timer) {
    case -2:
        obj_sound_held_stop(obj);
        obj_sound2_stop(obj);
        timer = 0x78;
        obj->unk_17A = 0;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        break;
    case -1:
        alive = 0;
        placement_list_pop((ListRecord *)obj->placement);
        pos = scratch_alloc(0x10);
        obj->placement->unk_04[0] = (obj->placement->unk_04[0] & 0xFC) | 2;
        pos->x = obj->x >> 12;
        pos->y = obj->y >> 12;
        pos->z = obj->z >> 12;
        particle_spawn_burst(pos->x, pos->y, pos->z, 0);
        spawn_effect(pos->x, pos->y - 0xF0, pos->z, 0);
        scratch_top -= 0x10;
        break;
    default:
        obj->speed -= 0xE3;
        obj->speed = MAX(MIN(obj->speed, obj->vars.tank.max_sink_speed), 0);
        fly_move(obj->yaw, obj->speed >> 12, &obj->vz, &obj->vx);
        if (timer % interval == 0) {
            pos = scratch_alloc(0x10);
            pos->x = obj->x >> 12;
            pos->y = obj->y >> 12;
            pos->z = obj->z >> 12;
            dx = rand_a_next() * (obj->width / 2 - -obj->width / 2) / 4096 + -obj->width / 2;
            dz = rand_a_next() * (obj->unk_1E8[0] / 2 - -obj->unk_1E8[0] / 2) / 4096 + -obj->unk_1E8[0] / 2;
            smoke_interval = 20;
            dz += pos->z;
            spawn_effect(dx + pos->x, pos->y - 0xEC, dz, (timer % smoke_interval == 0) * 2);
            scratch_top -= 0x10;
        }
        timer--;
        break;
    }
    *timer_p = timer;
    return alive;
}

/* spark_add on chain 0, list pinned to a0; the record address written as offset + list for the addu order. */
static inline void spark_add_chain0(s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    register SparkList *list asm("$4") = &spark_list;
    s32 n = spark_count;
    SparkRec *s;
    u8 *tail;

    FAKE_OPAQUE(list);
    if (n < 0xFF) {
        s = (SparkRec *)((s32)&list->items[n] - (s32)list + (s32)list);
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[0];
        list->tail[0] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}

void tank_draw(Object *obj, ObjHandler *handler) {
    s32 *pos;
    s16 *rot;
    register s32 slot asm("$4");
    s32 value;
    s32 *seq;
    s32 colour;
    s16 *turn;
    register SVECTOR *aim asm("$16");
    s32 off;

    pos = scratch_alloc(0x10);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    slot = model_pchr_saved;
    rot = scratch_alloc(0x28);
    rot[0] = obj->pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    value = pchr_copy_slot(slot);
    seq = pchr_poses_build(value);
    pchr_table[value & 0x7FF].unk_0C = seq;
    rot[4] = 0x23;
    rot[5] = -0xBC;
    rot[6] = 0x18;
    rot[12] = -obj->vars.tank.unk_250 + rot[0];
    turn = rot + 12;
    rot[13] = 0;
    rot[14] = 0;
    pose_rotate_range(seq, 6, 1, rot + 4, turn);
    rot[4] = 0;
    rot[5] = -0xBC;
    rot[6] = -0x6C;
    rot[12] = 0;
    rot[13] = obj->vars.tank.unk_252 - rot[1];
    rot[14] = 0;
    pose_rotate_range(seq, 0, 1, rot + 4, turn);
    pose_rotate_range(seq, 4, 3, rot + 4, turn);
    colour = 0;
    aim = (SVECTOR *)(rot + 8);
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    }
    if (obj->vars.h.unk_284 == 2) {
        off = obj->unk_1E8[0] * (s16)rcossin_tbl[rot[0] & 0xFFF] / 0x1000;
        pos[1] += ABS(off);
    }
    spark_add_chain0(pos[0], pos[1], pos[2], rot[1], -rot[0], rot[2], value, colour);
    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;
    aim->vx = obj->unk_1E8[0];
    aim->vy = obj->height;
    aim->vz = obj->unk_1E8[0];
    if (obj->vars.h.unk_284 != 2) {
        rot[0] = -rot[0];
        aim_marker_draw(2, aim, (Vec3 *)pos, (SVECTOR *)rot);
    } else {
        aim_marker_draw(2, aim, (Vec3 *)pos, 0);
    }
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x38;
}
