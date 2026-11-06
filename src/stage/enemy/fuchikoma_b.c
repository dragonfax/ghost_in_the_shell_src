/* fuchikoma_b: one of the original source files (scripts/objmap.py); s07, s09, s11, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"
#include "gte.h"

/* Transforms the vector at src by the rotation matrix and translation (MAC = (RT * IR + TR) >> 12) and
 * stores MAC1-3 at dst.
 * Hand-written in the original. */
void vec_rotate_rt(s32 *src, s32 *dst) {
    gte_load(IR1, src, 0);
    gte_load(IR2, src, 4);
    gte_load(IR3, src, 8);
    gte_rtirtr();
    gte_store(MAC1, dst, 0);
    gte_store(MAC2, dst, 4);
    gte_store(MAC3, dst, 8);
}

/* As vec_rotate_rt, unshifted. */
void vec_rotate_rt_unshifted(s32 *src, s32 *dst) {
    gte_load(IR1, src, 0);
    gte_load(IR2, src, 4);
    gte_load(IR3, src, 8);
    gte_rtirtr_sf0();
    gte_store(MAC1, dst, 0);
    gte_store(MAC2, dst, 4);
    gte_store(MAC3, dst, 8);
}

/* Builds the object's rotation matrix into dst: yaw from target_yaw, pitch and roll from the negated angles,
 * the second matrix multiplied into dst. Uses a 0x20-byte scratch matrix. */
void obj_build_rot_matrix(Object *obj, void *dst) {
    void *tmp = scratch_alloc(0x20);

    rot_matrix(dst, obj->vars.enemy.target_yaw, 0, 0);
    rot_matrix(tmp, -obj->rot_angles[1], -obj->rot_angles[0], -obj->rot_angles[2]);
    mul_matrix(tmp, dst, dst);
    scratch_top -= 0x20;
}

void obj_build_rot_matrix(Object *obj, void *dst);

/* Builds the object's matrix, converts it to angles (yaw, pitch negated, roll) and copies the matrix into the
 * object's vars. Uses 0x30 bytes of scratch. */
void obj_angles_from_matrix_copy(Object *obj) {
    s32 *mat = scratch_alloc(0x20);
    s32 *angles = scratch_alloc(0x10);
    s32 pitch, yaw, roll;

    obj_build_rot_matrix(obj, mat);
    matrix_to_angles(mat, &angles[1], angles, &angles[2]);
    *(MatrixHalf *)&obj->vars.fn_s07_800BAE10_obj.unk_248 = *(MatrixHalf *)&mat[0];
    *(MatrixHalf *)&obj->vars.fn_s07_800BAE10_obj.unk_258 = *(MatrixHalf *)&mat[4];
    pitch = angles[0];
    yaw = angles[1];
    roll = angles[2];
    scratch_top -= 0x30;
    obj->pitch = -pitch;
    obj->yaw = yaw;
    obj->roll = roll;
}

void obj_target_angles(Object *obj, void *table, s32 *yaw, s32 *pitch) {
    s32 *rot = scratch_alloc(0x10);
    volatile s32 *m = scratch_alloc(0x40);
    s32 *m2 = (s32 *)m + 8;
    Vec3 *target = table;
    s32 *dir;
    (void)rot;

    rot_matrix_b((void *)m, -obj->vars.enemy.target_yaw, 0, 0);
    rot_matrix_b(m2, obj->rot_angles[1], obj->rot_angles[0], obj->rot_angles[2]);
    mul_matrix((void *)m, m2, (void *)m);
    {
        s32 r0, r1, r2;
        r0 = m[0];
        r1 = m[1];
        r2 = m[2];
        gte_set_ctrl(R11R12, r0);
        gte_set_ctrl(R13R21, r1);
        gte_set_ctrl(R22R23, r2);
        r0 = m[3];
        r1 = m[4];
        gte_set_ctrl(R31R32, r0);
        gte_set_ctrl(R33, r1);
    }
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    dir = (s32 *)rot;
    dir[0] = (target->x - obj->x) >> 12;
    dir[1] = ((target->y - obj->y) >> 12) + (s16)obj->height / 2;
    dir[2] = (target->z - obj->z) >> 12;
    vec_rotate_rt(dir, dir);
    vector_to_angles(dir[0], dir[1], dir[2], yaw, pitch);
    scratch_top -= 0x50;
}

s32 obj_player_in_view(Object *obj, s32 max_yaw, s32 max_pitch) {
    VECTOR *pos;
    s32 yaw;
    s32 pitch;
    register s32 ok asm("$2");

    pos = scratch_alloc(0x10);
    player_position_copy(pos);
    pos->vx <<= 12;
    pos->vy <<= 12;
    pos->vz <<= 12;
    obj_target_angles(obj, pos, &yaw, &pitch);
    if (yaw > 0x800) {
        yaw = 0x1000 - yaw;
    }
    if (pitch > 0x800) {
        pitch = 0x1000 - pitch;
    }
    scratch_top -= 0x10;
    ok = 0;
    if (max_yaw >= yaw) {
        ok = max_pitch >= pitch;
    }
    return ok;
}

/* Turns the object's yaw (0x26A) toward a target made from the halfword at 0x27A plus the current yaw,
 * rounded down to a multiple of 0x20, by step. */
void obj_turn_toward_yaw(Object *obj, s32 step) {
    s32 yaw;
    s32 target;

    target = *(s16 *)((u8 *)obj + 0x27A);
    yaw = obj->vars.enemy.target_yaw;
    target = (target + yaw) & ~0x1F;
    obj->vars.enemy.target_yaw = angle_approach(yaw, target, step);
}

#if STAGE == 7
void obj_target_angles(Object *obj, void *table, s32 *first, s32 *second);
#endif

/* Looks up the object's value from cam_pos (obj_target_angles also writes a second result, unused here)
 * and stores the first result as a halfword at 0x27A. */
void enemy_aim_yaw_at_player(Object *obj) {
    s32 first;
    s32 second;

    obj_target_angles(obj, &cam_pos, &first, &second);
    *(s16 *)((u8 *)obj + 0x27A) = (s16)first;
}

/* Jitters the placement's target position by up to +-2500 units in x and z, reads a pair of angles toward it from
 * obj_target_angles and stores the first one as a halfword at 0x27A. Uses 0x10 bytes of scratch. */
void enemy_aim_yaw_jittered(Object *obj) {
    PlacedTarget *place = (PlacedTarget *)obj->placement;
    Vec3 *pos = scratch_alloc(0x10);
    s32 angle0;
    s32 angle1;

    pos->x = place->x;
    pos->y = place->y;
    pos->z = place->z;
    pos->x += ((rand_a_next() * 5000) / 4096 - 0x9C4) << 12;
    pos->z += ((rand_a_next() * 5000) / 4096 - 0x9C4) << 12;
    obj_target_angles(obj, pos, &angle0, &angle1);
    scratch_top -= 0x10;
    *(s16 *)&obj->vars.enemy.unk_276[4] = angle0;
}

#if STAGE == 7
s32 obj_player_in_view(Object *obj, s32 max_yaw, s32 max_pitch);
#endif

/* Reads two halfwords from the object's script; if obj_player_in_view accepts the first, the
   script continues at the entry (the second halfword) of the object's table. */
void script_op_jump_if_in_range(Object *obj) {
    s16 *script = obj->script.pc;
    s32 first;
    s32 index;

    obj->script.pc = script + 1;
    first = script[0];
    obj->script.pc = script + 2;
    index = script[1];
    if (obj_player_in_view(obj, first, first) != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_op_jump_if_player_in_range(Object *obj) {
    s32 *player = player_position();
    s32 dist = isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12)));
    s16 *script = obj->script.pc;
    s32 radius;
    s32 target;
    s32 index;

    obj->script.pc = script + 1;
    radius = script[0];
    obj->script.pc = script + 2;
    target = script[1];
    obj->script.pc = script + 3;
    index = script[2];
    if (radius >= dist && obj_player_in_view(obj, target, target) != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* As script_op_jump_if_in_range, but only when the flag byte at 0x284 is set; a successful step clears the flag. */
void script_op_jump_if_flag_in_range(Object *obj) {
    s16 *script = obj->script.pc;
    s32 first;
    s32 index;
    s16 *next;

    obj->script.pc = script + 1;
    first = script[0];
    obj->script.pc = script + 2;
    index = script[1];
    if (*(u8 *) &obj->vars.words[15] != 0) {
        if (obj_player_in_view(obj, first, first) != 0) {
            next = ((s16 **)obj->script.data)[index];
            *(u8 *) &obj->vars.words[15] = 0;
            obj->script.pc = next;
        }
    }
}

void script_op_set_enemy_sound(Object *obj) {
    s16 *p = obj->script.pc;
    s32 lo, hi;
    obj->script.pc = p + 1;
    lo = p[0];
    obj->script.pc = p + 2;
    hi = p[1] << 16;
    obj->vars.enemy.sound = (lo & 0xFFFF) | hi;
}

#if STAGE == 7
void enemy_aim_yaw_jittered(Object *obj);
#endif

/* Runs enemy_aim_yaw_jittered, then clears the halfword at 0x242. */
void enemy_retarget_jitter(Object *obj) {
    enemy_aim_yaw_jittered(obj);
    obj->unk_242 = 0;
}

void enemy_aim_yaw_at_player(Object *obj);

void script_op_aim_and_track(Object *obj) {
    enemy_aim_yaw_at_player(obj);
    obj->unk_242 = 1;
}

void script_op_set_mode(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;

    obj->script.pc = cursor + 1;
    *((s8 *)obj + 0x285) = (s8)*cursor;
}

/* Reads a script entry (a key and an index) from the object's cursor (0x20, in unk_1C.unk_04). When the
 * key matches the byte at 0x285 (proposed stage.h field: u8 @0x285), the cursor jumps to the table entry
 * for the index. */
void script_jump_if_mode(Object *obj) {
    s16 *cursor;
    s32 key;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    key = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (key == ((u8 *)obj)[0x285]) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void obj_run_if_alive(Object *obj) {
    if (obj->health > 0) {
        obj_link_script_run();
    }
}

void vec_rotate_rt_unshifted(s32 *in, s32 *out);
void obj_velocity_to_ctrl(Object *obj, s16 *ctrl) {
    Vector3 *vec = scratch_alloc(0x10);
    s32 *mat = scratch_alloc(0x20);
    s32 m0, m1, m2;

    rot_matrix(mat, obj->vars.pair.timer, 0, 0);
    m0 = mat[0];
    m1 = mat[1];
    m2 = mat[2];
    __asm__ volatile("" : : : "memory");
    gte_set_ctrl(R11R12, m0);
    gte_set_ctrl(R13R21, m1);
    gte_set_ctrl(R22R23, m2);
    m0 = mat[3];
    m1 = mat[4];
    __asm__ volatile("" : : : "memory");
    gte_set_ctrl(R31R32, m0);
    gte_set_ctrl(R33, m1);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    vec->x = obj->vars.words[11] >> 12;
    vec->y = obj->vy >> 12;
    vec->z = obj->speed >> 12;
    vec_rotate_rt_unshifted((s32 *)vec, (s32 *)vec);
    ((TargetCtrl *)ctrl)->pos = *vec;
    scratch_top -= 0x30;
    if (obj->unk_1B7 != 0) {
        ((TargetCtrl *)ctrl)->flags |= 1;
    } else {
        ((TargetCtrl *)ctrl)->flags &= ~1;
    }
}

static inline s32 yaw_diff(s32 a, s32 b) {
    a &= 0xFFF;
    if (a > 0x800) {
        a -= 0x1000;
    }
    b &= 0xFFF;
    if (b > 0x800) {
        b -= 0x1000;
    }
    a = (a - b) & 0xFFF;
    if (a > 0x800) {
        a -= 0x1000;
    }
    return a;
}
void fuchikoma_chase_update(Object *obj) {
    s32 throttle, brake, limit;
    s32 old_yaw;
    s32 new_yaw;
    s32 *pos;
    s32 *player;
    s32 was_grounded;
    s16 *ctrl;

    throttle = obj->vars.enemy.throttle;
    brake = obj->vars.enemy.brake;
    old_yaw = obj->vars.enemy.target_yaw;
    obj_turn_toward_yaw(obj, 0x16);
    if (obj->unk_242 == 0 || ((player = player_position()), 0) ||
        isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12))) > 0x200) {
        throttle -= 0x20;
        brake -= 0x20;
    } else {
        new_yaw = obj->vars.enemy.target_yaw;
        brake += 0xA;
        if ((YAW_DIFF(old_yaw, new_yaw) >= 0 ? YAW_DIFF(old_yaw, new_yaw) : -yaw_diff(old_yaw, new_yaw)) < 0x16) {
            throttle += 0xA;
        } else {
            throttle -= 0x20;
        }
    }
    throttle = MAX(MIN(throttle, 0x80), 0);
    brake = MAX(MIN(brake, 0x80), 0);
    limit = obj->vars.enemy.sound;
    if (brake != 0) {
        limit = limit * (0x80 - brake) / 128;
    }
    obj->speed += obj->speed_accel;
    obj->speed = MAX(MIN(obj->speed, limit), 0);
    obj->vars.enemy.throttle = throttle;
    obj->vars.enemy.brake = brake;
    if (obj->vars.enemy.throttle != 0x80 && obj->script_flag == 0xF) {
        sound_play_at(SND_FOOTSTEP | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
    }
    ctrl = obj->rot_angles;
    if (!(obj->ground_flags & 1)) {
        obj->vy += obj->accel_y;
    }
    if (obj->vy > 0x30000) {
        obj->vy = 0x30000;
    }
    was_grounded = obj->ground_flags;
    obj_velocity_to_ctrl(obj, ctrl);
    player_step_move_scratch(ctrl);
    obj_snapshot_restore(obj, (ObjSnapshot *)ctrl);
    if (!(was_grounded & 1) && (obj->ground_flags & 1)) {
        pos = scratch_alloc(0x10);
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        sound_play_at_units(SND_LANDING_THUD | SND_GROUP(2), 0x5A, 0x3C, pos);
        scratch_top -= 0x10;
    }
    if ((u8)obj->blocked_y != 0) {
        obj->vy = 0;
    }
}

/* The muzzle side table is at a different address in each stage: this file is shared by s07, s09, s11 and
 * s12, and the alias picks the stage's own table. */
extern s16 muzzle_side_table[];
#define muzzle_side_table muzzle_side_table

void muzzle_fire(Object *obj, s32 idx) {
    s32 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    s32 *m;
    s32 p;
    s32 side;

    side = muzzle_side_table[idx];

    pos[1] = -0x37;
    pos[2] = 0x5F;
    pos[0] = side;
    m = (s32 *)&obj->vars;
    gte_load_R_a0a1v1(m);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    vec_rotate_rt(pos, pos);
    pos[0] = (obj->x >> 12) + pos[0];
    pos[1] = (obj->y >> 12) + pos[1];
    pos[2] = (obj->z >> 12) + pos[2];
    p = obj->pitch;
    rot->vx = -p;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    sound_play_at_units(SND_SHOT_FIRE_ALT | SND_GROUP(1), 0x40, 0x3C, pos);
    shot_spawn_obj(pos, (u16 *)rot, 3, (obj->damage << 16) | 0x38);
    scratch_top -= 0x18;
}

#if STAGE == 7
void muzzle_fire(Object *obj, s32 slot);
#endif

/* Raw offsets (stage.h has no fields here): s16 timers at 0x27C and 0x27E, a u16 cooldown at 0x280,
 * s16 state at 0x282, a byte flag at 0x285. */
void obj_spawner_tick(Object *obj) {
    s16 *entry;
    s32 i;
    s16 t;
    s32 next;

    i = 0;
    do {
        if (((s16 *) obj)[0x13E + i] > 0) {
            t = ((s16 *) obj)[0x13E + i] - 1;
            ((s16 *) obj)[0x13E + i] = t;
            if (t == 6) {
                muzzle_fire(obj, i);
            }
        }
        i++;
    } while (i < 2);

    switch (((s16 *) obj)[0x141]) {
    case -2:
        ((s16 *) obj)[0x141] = 0x28;
        ((u16 *) obj)[0x140] = 8;
        return;
    case -1:
        if (((s16 *) obj)[0x13E] <= 0 && ((s16 *) obj)[0x13F] <= 0) {
            *((u8 *) obj + 0x285) = 0;
            ((s16 *) obj)[0x141] = -2;
        }
        return;
    default:
        next = ((u16 *) obj)[0x140] - 1;
        ((u16 *) obj)[0x140] = next;
        if ((next << 16) <= 0) {
            ((u16 *) obj)[0x140] = 8;
            entry = (s16 *) ((rand_a_next() / 2048) * 2 + (s32) obj);
            if (entry[0x13E] <= 0) {
                entry[0x13E] = 0x34;
            }
        }
        break;
    }
}

void obj_velocity_to_ctrl(Object *obj, s16 *ctrl);
/* Falling object behaviour. On a -2 result it launches: random direction, a fixed
 * downward speed and a sound at its position. While falling it applies gravity, caps the
 * fall speed, and plays a landing sound on the frame it touches the ground. */
void obj_fall_update(Object *obj, ObjHandler *handler) {
    s16 *ctrl;
    s32 *pos;
    s32 dir;
    s32 prev_flags;

    if (handler->result == -2) {
        s32 launch_vy = -0xFFF0;

        dir = 1;
        handler->queued_entry = -1;
        handler->result = 1;
        obj->vy = launch_vy;
        obj->unk_1B7 = 0;
        if (rand_a_next() < 0x800) {
            dir = -1;
        }
        ((FallState *)obj)->fall_dir = dir;
        *(s32 *)&obj->vars.enemy.unk_274 = dir * 0x19980;
        pos = (s32 *)scratch_top;
        scratch_top += 0x10;
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        sound_play_at_units(SND_FALL_LAUNCH | SND_GROUP(2), 0x5A, 0x3C, pos);
        scratch_top -= 0x10;
        ((FallState *)obj)->launch_timer = 8;
    }

    obj_turn_toward_yaw(obj, 0x16);
    if (*(s32 *)&obj->vars.enemy.unk_274 == 0 && ((FallState *)obj)->unk_27C <= 0 && ((FallState *)obj)->unk_27E <= 0) {
        ((FallState *)obj)->unk_282 = -2;
        obj_request_state(obj, handler, 1, 0);
    }

    ctrl = obj->rot_angles;
    if (!(obj->ground_flags & 1)) {
        obj->vy += obj->accel_y;
    }
    if (obj->vy > 0x30000) {
        obj->vy = 0x30000;
    }

    prev_flags = obj->ground_flags;
    obj_velocity_to_ctrl(obj, ctrl);
    player_step_move_scratch(ctrl);
    obj_snapshot_restore(obj, (ObjSnapshot *)ctrl);

    /* Landing sound on the frame the object first touches the ground. */
    if (!(prev_flags & 1) && (obj->ground_flags & 1)) {
        pos = (s32 *)scratch_top;
        scratch_top += 0x10;
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        sound_play_at_units(SND_LANDING_THUD | SND_GROUP(2), 0x5A, 0x3C, pos);
        scratch_top -= 0x10;
    }

    if ((u8)obj->blocked_y != 0) {
        obj->vy = 0;
    }
}

#if STAGE == 7
#define VARS_TAIL274(obj) ((VarsTail274 *)&(obj)->vars.words[11])
#define TIMER_REREAD(obj) (*(volatile s32 *)&VARS_TAIL274(obj)->timer)
void obj_angles_from_matrix_copy(Object *obj);
void obj_spawner_tick(Object *obj);
#endif

#if STAGE == 7
void fuchikoma_b_update(Object *obj, ObjHandler *handler) {
    if (obj->health > 0) {
        obj_script_step(obj, handler);
        if (VARS_TAIL274(obj)->unk_285 == 1) {
            obj_spawner_tick(obj);
        }
        if (VARS_TAIL274(obj)->countdown >= 0) {
            VARS_TAIL274(obj)->countdown = VARS_TAIL274(obj)->countdown - 1;
        }
        if (VARS_TAIL274(obj)->unk_278 == 1) {
            if (VARS_TAIL274(obj)->timer > 0) {
                VARS_TAIL274(obj)->timer -= (*(u8 *)&obj->unk_1B7 == 1) ? 0x8FC : 0xA28;
                if (TIMER_REREAD(obj) < 0) {
                    VARS_TAIL274(obj)->timer = 0;
                }
            }
        } else {
            if (VARS_TAIL274(obj)->timer < 0) {
                VARS_TAIL274(obj)->timer += (*(u8 *)&obj->unk_1B7 == 1) ? 0x8FC : 0xA28;
                if (TIMER_REREAD(obj) > 0) {
                    VARS_TAIL274(obj)->timer = 0;
                }
            }
        }
    }
    obj_angles_from_matrix_copy(obj);
}
#else
void fuchikoma_b_update(Object *obj, ObjHandler *handler) {
    if (obj->health > 0) {
        obj_script_step(obj, handler);
        if (((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->unk_285 == 1) {
            obj_spawner_tick(obj);
        }
        if (((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->countdown >= 0) {
            ((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->countdown = ((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->countdown - 1;
        }
        if (((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->unk_278 == 1) {
            if (((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->timer > 0) {
                ((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->timer -= (obj->unk_1B7 == 1) ? 0x8FC : 0xA28;
                if (*(volatile s32 *)&((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->timer < 0) {
                    ((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->timer = 0;
                }
            }
        } else {
            if (((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->timer < 0) {
                ((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->timer += (obj->unk_1B7 == 1) ? 0x8FC : 0xA28;
                if (*(volatile s32 *)&((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->timer > 0) {
                    ((VarsTail274 *)&obj->vars.fn_s07_800BAE10_obj.unk_274)->timer = 0;
                }
            }
        }
    }
    obj_angles_from_matrix_copy(obj);
}
#endif

void obj_snap_placement_free(Object *obj, ObjHandler *handler) {
    Placement *place;

    place = obj->placement;
    if (obj->health > 0) {
        if (cam_range_check(obj->home_pos[0] >> 12, obj->home_pos[1] >> 12, obj->home_pos[2] >> 12) == 0) {
            /* snap the placement to the object's position, keeping each low 12-bit angle */
            place->x = ((obj->home_pos[0] >> 12) << 12) + (place->x & 0xFFF);
            place->y = ((obj->home_pos[1] >> 12) << 12) + (place->y & 0xFFF);
            place->z = ((obj->home_pos[2] >> 12) << 12) + (place->z & 0xFFF);
            /* then add the signed per-axis offsets from unk_34 (s16, sign-extended before the mask) */
            place->x = ((place->x >> 12) << 12) + ((obj->unk_34[0] << 16 >> 16) & 0xFFF);
            place->y = ((place->y >> 12) << 12) + ((obj->unk_34[1] << 16 >> 16) & 0xFFF);
            place->z = ((place->z >> 12) << 12) + ((obj->unk_34[2] << 16 >> 16) & 0xFFF);
            /* clear the two halfwords at +2 and +6 (unk_00 is a byte array) */
            ((s16 *)place->unk_00)[3] = 0;
            ((s16 *)place->unk_00)[1] = 0;
            /* flag bits 0..1 of unk_00[4] set to 2 */
            place->unk_00[4] = (place->unk_00[4] & 0xFC) | 2;
            obj_free(obj);
            return;
        }
    }
    obj_state_run(obj, handler);
}

/* Spawns a child at the object's position (scaled to whole units) and angles, then frees the object and clears
 * the flags byte of its placement. Uses 0x18 bytes of scratch: a position and three halfword angles. */
void obj_spawn_replace(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 *angles = scratch_alloc(8);

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    /* `* -1` keeps the signed halfword load; `-obj->pitch` compiles to lhu. */
    angles[0] = obj->pitch * -1;
    angles[1] = (u16)obj->yaw;
    angles[2] = (u16)obj->roll;
    object_spawn_at(pos, angles, model_slot_pchr(*(s32 *)obj->asset) + obj->type.unk_0E);
    placement_list_pop((ListRecord *)obj->placement);
    scratch_top -= 0x18;
    obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
    obj_free(obj);
}

/* x offset of each shot slot's muzzle: each stage's own table. */
extern s16 shot_muzzle_x_table[];
#define SLOT_MUZZLE_X shot_muzzle_x_table

/* Spawns the muzzle spark of shot slot `channel`: its offset rotated by the object's matrix, sized and shaded
 * by the slot timer (rising over 6 steps, then fading over 46). */
void shot_muzzle_spark_spawn(Object *obj, s32 channel) {
    s32 offset = SLOT_MUZZLE_X[channel];
    s32 *pos = scratch_alloc(16);
    s32 *rot;
    s32 r0, r1, r2;
    s32 level;
    s32 scale;
    s32 clamped;
    s32 size;
    s32 model;
    s32 shade;
    s32 colour;
    s32 blue;

    pos[1] = -0x37;
    pos[2] = 0x5F;
    pos[0] = offset;
    rot = obj->vars.slots.rot;
    gte_set_R012(r0, r1, r2, rot[0], rot[1], rot[2]);
    gte_set_R34(r0, r1, rot[3], rot[4]);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    vec_rotate_rt(pos, pos);
    pos[0] = (obj->x >> 12) + pos[0];
    pos[1] = (obj->y >> 12) + pos[1];
    pos[2] = (obj->z >> 12) + pos[2];
    model = get_model_slot_base() + 0xF;
    level = obj->vars.slots.timer[channel];
    if (level >= 6) {
        level -= 6;
        clamped = MAX(MIN(level, 46), 0);
        scale = (clamped << 12) / 46;
        scale = 0x1000 - scale;
    } else {
        level = MAX(MIN(level, 6), 0);
        scale = (level << 12) / 6;
    }
    size = scale * 3000 / 4096;
    model = pool_spawn_scaled(model, size, size, size);
    shade = scale >> 5;
    blue = shade;
    if (shade == 0) {
        blue = 1;
    }
    colour = (blue << 16) | (shade << 8) | shade;
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, model, colour);
    scratch_top -= 0x10;
}

#if STAGE == 7
void shot_muzzle_spark_spawn(Object *obj, s32 index);
#endif

void shot_slots_update(Object *obj) {
    s32 i = 0;
    u8 *base = (u8 *)obj;
    do {
        if (*(s16 *)(base + 0x27C) > 0) {
            shot_muzzle_spark_spawn(obj, i);
        }
        i += 1;
        base += 2;
    } while (i < 2);
}

void fuchikoma_b_draw(Object *obj) {
    Vec3 *pos;
    SVECTOR *rot;
    s32 colour;
    s32 value;
    s32 fade;

    if (obj->hit != 0 && obj->vars.slots.unk_287 == 0) {
        obj->vars.slots.was_hit = 1;
    }
    pos = scratch_alloc(0x10);
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    rot = scratch_alloc(8);
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
        /* The second store keeps jump.c from turning this select into slt/negu/and. */
        colour = 0;
        colour = 0;
    }
    value = obj_keyframe_value(obj, 0);
    fade = obj->vars.slots.fade;
    if (fade != 0) {
        fade = 0x80 - fade;
        fade <<= 5;
        value = pchr_blend(value, model_slot_pchr(*(s32 *)obj->asset) + 0xC, fade, 0);
    }
    rot->vx = obj->pitch;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    spark_add(pos->x >> 12, pos->y >> 12, pos->z >> 12, rot->vy, -rot->vx, rot->vz, value, colour);
    rot->vx = -rot->vx;
    aim_marker_draw(2, (SVECTOR *)&obj->width, pos, rot);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x18;
    shot_slots_update(obj);
}

void obj_setup_from_placement(Object *obj, Placement *placement, s32 flags) {
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, -1);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj->health = placement->health;
    obj->score = (s16) placement->unk_16;
    obj->damage = placement->unk_18;
    obj->unk_17B = placement->unk_1A;
    obj->accel_y = 0x1000;
    obj_set_flags(obj, flags);
    obj->placement = placement;
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}

#ifndef VARS_TAIL274
#define VARS_TAIL274(obj) ((VarsTail274 *)&(obj)->vars.words[11])
#endif

/* Each stage's own copy of the Fuchikoma's model, part tables, animation links and script. */
extern char fuchikoma_asset[];
extern ScriptCallEntry fuchikoma_call_table[];
extern StateEntry fuchikoma_state_table[];
extern s16 *fuchikoma_link_data[];
extern s16 *fuchikoma_anim_link;
extern s16 *enemy_fuchikoma_b_data[];
#define FUCHIKOMA_ASSET fuchikoma_asset
#define FUCHIKOMA_194 fuchikoma_call_table
#define FUCHIKOMA_198 fuchikoma_state_table
#define FUCHIKOMA_LINKS fuchikoma_link_data
#define FUCHIKOMA_ANIM fuchikoma_anim_link
#define FUCHIKOMA_SCRIPT enemy_fuchikoma_b_data

void fuchikoma_b_update(Object *obj, ObjHandler *handler);
void obj_spawn_replace(Object *obj);

/* Spawns a Fuchikoma (type B) from its placement: handlers, model, script, hit setup, then the position and
 * angles from the placement and the bounds. The empty do-whiles split the scheduling blocks as the original. */
s32 fn_s07_800BAE10(Placement *placement) {
    Object *obj;
    s32 kind;
    s16 **link_data;
    s16 *anim_link;
    s32 x, y, z;
    s32 ax, ay, az;
    s32 ext;
    s32 height;
    u16 half;
    s16 extent;
    s16 *rot;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), &obj->node);
    placement->unk_02 = 0x708;
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *))obj_run_if_alive;
    obj->handlers[1].fn = fuchikoma_b_update;
    obj->handlers[2].fn = obj_snap_placement_free;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *))fuchikoma_b_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32)obj_spawn_replace;
    kind = placement->unk_04[1];
    obj->asset = FUCHIKOMA_ASSET;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = FUCHIKOMA_194;
    obj->state_table = FUCHIKOMA_198;
    link_data = FUCHIKOMA_LINKS;
    obj->unk_1C6 = 0;
    obj->kind = kind;
    do { } while (0);
    anim_link = FUCHIKOMA_ANIM;
    obj->script.data = link_data;
    obj->script.unk_0A = 0;
    obj->script.pc = anim_link;
    script_start((Script *)obj, (s16 *)FUCHIKOMA_SCRIPT[0], (s32)FUCHIKOMA_SCRIPT);
    obj_setup_from_placement(obj, placement, 0x25);
    obj_set_part_bounds(obj, 0xC, 0xCCC);
    VARS_TAIL274(obj)->countdown = -2;
    obj->vy = 0;
    obj->vars.slots.timer[0] = 0;
    obj->vars.slots.timer[1] = 0;
    VARS_TAIL274(obj)->unk_285 = 0;
    VARS_TAIL274(obj)->timer = 0;
    obj->vars.slots.was_hit = 0;
    obj->accel_y = 0x2000;
    obj->vars.slots.fade = 0;
    obj->vars.slots.unk_287 = 0;
    obj->unk_242 = 0;
    *(s16 *)VARS_TAIL274(obj)->unk_27A = obj->yaw;
    obj_hit_set_unk08(obj->index, 0x80);
    obj_hit_set_unk06(obj->index, 7);

    x = (placement->x >> 12) << 12;
    y = (placement->y >> 12) << 12;
    z = (placement->z >> 12) << 12;
    obj->home_pos[0] = x;
    obj->home_pos[1] = y;
    obj->home_pos[2] = z;
    obj->x = x;
    obj->y = y;
    obj->z = z;
    ay = placement->y & 0xFFF;
    ax = placement->x & 0xFFF;
    az = placement->z & 0xFFF;
    obj->vars.dmech.unused_268 = 0;
    obj->vars.enemy.target_yaw = 0;
    obj->vars.enemy.walk_state = 0;
    obj->rot_angles[0] = ax;
    obj->rot_angles[1] = ay;
    obj->rot_angles[2] = az;
    obj->unk_34[0] = ax;
    obj->unk_34[1] = ay;
    obj->unk_34[2] = az;
    obj_angles_from_matrix_copy(obj);
    rot = obj->rot_angles;
    ext = obj->unk_1E8[0];
    height = (s16)obj->height;
    if (ext < obj->width) {
        ext = obj->width;
    }
    half = obj->height;
    extent = ext;
    obj->extents[0] = extent;
    obj->extents[1] = half;
    obj->extents[2] = extent;
    obj->bound_radius = isqrt(length_sq(ext, height, ext));
    obj->unk_3C = 0xF2;
    player_refresh_state_scratch(rot);
    return 1;
}

/* Distance from the object to the player. The object's script cursor reads a
   (threshold, index) pair; when the distance is at most the threshold, the cursor
   jumps to the entry at index in the object's table. */
void script_jump_if_within_range(Object *obj) {
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
