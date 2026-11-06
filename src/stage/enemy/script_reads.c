/* script_reads: one of the original source files (scripts/objmap.py); s07, s08, s09, s11, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

void obj_script_read_speed(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;
    s32 hi;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    hi = pc[1] << 16;
    obj->speed = (lo & 0xFFFF) | hi;
}

void obj_script_read_s32(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    obj->speed_accel = pc[1] << 16;
    obj->speed_accel = (lo & 0xFFFF) | obj->speed_accel;
}

/* Reads the next script halfword (cursor at +0x20). With the flag at +0xF8 set, the cursor jumps to the
 * entry of the type's table (+0x1C) that the halfword selects. */
void obj_script_read_jump(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if (obj->script_flag != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

#if STAGE != 8
void script_jump_if_player_far(Object *obj) {
    s16 radius;
    s16 index;
    s32 *player;
    PlacedTarget *target;
    s32 dist;

    radius = obj_read_s16(obj);
    index = obj_read_s16(obj);
    player = player_position();
    target = (PlacedTarget *) obj->placement;
    dist = isqrt(length_sq(player[0] - (target->x >> 12), player[1] - (target->y >> 12),
                           player[2] - (target->z >> 12)));
    if (dist >= radius) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}
#endif

#if STAGE == 12
s32 trace_world_fixed(Vec3 *from, Vec3 *to, Vec3 *hit) {
    Vec3 start;
    Vec3 end;
    s32 x, y, z;
    s32 result;

    start.x = from->x >> 12;
    start.y = from->y >> 12;
    start.z = from->z >> 12;
    end.x = to->x >> 12;
    end.y = to->y >> 12;
    end.z = to->z >> 12;
    result = trace_world(2, 0x80, &start, &end, hit);
    x = hit->x;
    y = hit->y;
    z = hit->z;
    hit->x = x << 12;
    hit->y = y << 12;
    hit->z = z << 12;
    return result;
}
extern s32 loop_sound_fade_handle;
extern ModelSlotHead timer_tail_data;
extern s16 d_8011B7AC[];
#endif

#if STAGE == 12
void loop_sound_fade_in(void) {
    if (stage_ready_get() != 0) {
        loop_sound_fade_handle = interp1c_add((s32)d_8011B7AC, timer_tail_data.words[0]);
        interp1c_set_state(loop_sound_fade_handle, 1);
    }
}

#if STAGE == 10
void obj_destroy_loop_sound(Object *obj) {
    /* the high halfword of the loop sound handle (0x272) */
    u16 *handle_hi = &((u16 *) &obj->vars.enemy.sound)[1];

    if (*handle_hi != 0) {
        sound_stop(*handle_hi);
        *handle_hi = 0;
    }
}
#elif STAGE == 12
void obj_destroy_loop_sound(Object *obj) {
    /* the halfword sound handle at 0x278 (shares the turn view's yaw_offset slot) */
    u16 *handle = (u16 *) &obj->vars.turn.yaw_offset;

    if (*handle != 0) {
        sound_stop(*handle);
        *handle = 0;
    }
}
#else
INCLUDE_ASM(STAGE_ASM, obj_destroy_loop_sound);
#endif
#endif
