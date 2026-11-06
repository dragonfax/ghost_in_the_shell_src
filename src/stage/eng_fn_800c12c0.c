/* Shared by s06, s07, s09: projectile_trace_update..script_op_jump_if_near_target (9 functions). */

#include "stage.h"

void trace_spawn_fan(Vec3 *pos, u16 *src);
void projectile_trace_update(Object *obj, ObjHandler *handler) {
    u8 *scratch = scratch_alloc(0x40);
    Vec3 *pos = (Vec3 *) (scratch + 0x10);
    Vec3 *next = (Vec3 *) (scratch + 0x20);
    Vec3 *hit = (Vec3 *) (scratch + 0x30);
    u16 *rot = scratch_alloc(8);
    s32 x = obj->x;
    s32 y = obj->y;
    s32 z = obj->z;
    s32 trace_flags;
    s32 result;
    s16 target;

    rot[0] = obj->pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    pos->x = x >> 12;
    pos->y = y >> 12;
    pos->z = z >> 12;

    x += obj->vx;
    if (obj->vars.enemy.mode == 0) {
        y += obj->vy;
    } else {
        s32 lifted = y + 0x1000;

        y = lifted + obj->vy;
    }
    z += obj->vz;
    next->x = x >> 12;
    next->y = y >> 12;
    next->z = z >> 12;

    trace_flags = obj->vars.shot_spawn_trace_obj.unused_250;
    result = 0;
    if (cam_range_check(next->x, next->y, next->z) == 0) {
        result = 1;
    } else if ((obj_hit_damage(obj->index) << 16) > 0) {
        result = 2;
    } else if (trace_world(8, trace_flags, pos, next, hit) == 1) {
        result = 3;
    } else {
        set_collide_mode(1);
        if (trace_objects(pos, next, trace_flags, hit, &target) != 0) {
            result = 4;
        }
        set_collide_mode(0);
    }

    switch (result) {
    case 0:
        if (obj->vars.enemy.mode == 0 && (u32) obj->vars.shot_spawn_trace_obj.age >= 0x29) {
            spawn_effect(next->x, next->y, next->z, 2);
            trace_spawn_fan(next, rot);
            obj_free(obj);
        } else {
            obj->x = x;
            obj->y = y;
            obj->z = z;
        }
        break;
    case 1:
        obj_free(obj);
        break;
    case 2:
        spawn_effect(hit->x, hit->y, hit->z, 0);
        obj_free(obj);
        break;
    case 3:
        spawn_effect(hit->x, hit->y, hit->z, 0);
        obj_free(obj);
        break;
    case 4:
        spawn_effect(hit->x, hit->y, hit->z, 0);
        hit_target_masked(0, 1, (s16) atan2(hit->z - pos->z, hit->x - pos->x), obj->damage);
        obj_free(obj);
        break;
    }
    obj->vars.shot_spawn_trace_obj.age += 1;
    scratch_top -= 0x48;
}

void shot_spawn_trace_draw(Object *obj, ObjHandler *handler) {
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 yaw = obj->yaw;
    s32 roll = obj->roll;
    s32 z = obj->z >> 12;
    s32 pitch = -obj->pitch;
    s32 colour = 0;
    s32 value;

    if (obj->vars.enemy.mode == 0) {
        value = model_pchr_saved + 1;
    } else {
        value = model_pchr_saved + 2;
    }
    spark_add(x, y, z, yaw, pitch, roll, value, colour);
}

void projectile_trace_update(Object *obj, ObjHandler *handler);
void shot_spawn_trace_draw(Object *obj, ObjHandler *handler);
s32 shot_spawn_trace(Vec3 *pos, SVECTOR *rot, s32 kind) {
    Object *obj;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot->vx;
        obj->yaw = rot->vy;
        obj->roll = rot->vz;
        obj->handlers[1].fn = projectile_trace_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->callback = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[3].fn = shot_spawn_trace_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj_set_flags(obj, 0x80);
        obj_hit_clear(obj->index);
        obj_hit_flag_set(obj->index, 0);
        obj->unk_17A = 0;
        if (kind == 0) {
            obj->vars.shot_spawn_trace_obj.unused_250 = 0x16;
            obj->speed = 0x12000;
            obj->damage = 0x10;
        } else {
            obj->vars.shot_spawn_trace_obj.unused_250 = 0xA;
            obj->speed = 0x12000;
            obj->damage = 6;
        }
        obj->vars.shot_spawn_trace_obj.age = 0;
        obj->vars.shot_spawn_trace_obj.kind = kind;
        angles_to_vector(rot->vy, -rot->vx, obj->speed >> 12, &obj->vx, &obj->vy, &obj->vz);
        return 1;
    }
    return 0;
}

/* Distance from the object to the player. The object's script cursor reads a
   (threshold, index) pair; when the distance is at most the threshold, the cursor
   jumps to the entry at index in the object's table. */
void script_op_jump_if_player_near(Object *obj) {
    s32 *player = player_position();
    s32 dist = isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12)));
    s16 *cursor = obj->script.pc;
    s32 threshold;
    s32 index;

    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold >= dist) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_op_jump_if_player_far(Object *obj) {
    s32 *player;
    s32 dist;
    s16 *cursor;
    s32 range;
    s32 target;
    player = player_position();
    dist = isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12)));
    cursor = obj->script.pc;
    obj->script.pc++;
    range = cursor[0];
    obj->script.pc++;
    target = cursor[1];
    if (range < dist) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

/* Script op: jump to the target given by the operand pair when the object is within radius of a cell corner. */
void script_op_jump_if_in_cell_corner(Object *obj) {
    s32 cx;
    s32 cy;
    s32 radius;
    s32 target;
    s16 *cursor;
    s32 dx;
    s32 dy;
    s32 inside;
    s32 px;
    s32 py;
    s32 pz;

    px = obj->x;
    py = obj->y;
    cursor = obj->script.pc;
    pz = obj->z;
    /* shifted in place: a register set twice keeps its load where it is (sched1 moves single-set loads) */
    px >>= 12;
    py >>= 12;
    pz >>= 12;
    obj->script.pc++;
    radius = cursor[0];
    obj->script.pc++;
    target = cursor[1];
    point_to_view_angles(px, py, pz, &cx, &cy);
    dx = cx;
    dy = cy;
    if (dx > 0x800) {
        dx = 0x1000 - dx;
    }
    if (dy > 0x800) {
        dy = 0x1000 - dy;
    }
    inside = dx < radius && dy < radius;
    if (inside) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

/* Reads two halfwords from the script stream and combines them into the speed. */
void script_op_set_speed(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;
    s32 hi;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    hi = pc[1] << 16;
    obj->speed = (lo & 0xFFFF) | hi;
}

void script_op_set_unk_234(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    obj->speed_accel = pc[1] << 16;
    obj->speed_accel = (lo & 0xFFFF) | obj->speed_accel;
}

void script_op_jump_if_near_target(Object *obj) {
    PlacedTarget *target;
    s32 *player;
    s16 *cursor;
    s32 range;
    s32 index;
    s32 dx;
    s32 dy;
    s32 dz;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    range = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    player = player_position();
    target = (PlacedTarget *)obj->placement;
    dx = player[0] - (target->x >> 12);
    dy = player[1] - (target->y >> 12);
    dz = player[2] - (target->z >> 12);
    if (range >= isqrt(length_sq(dx, dy, dz))) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}
