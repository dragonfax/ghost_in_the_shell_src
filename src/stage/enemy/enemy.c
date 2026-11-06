/* enemy: one of the original source files (scripts/objmap.py); s01, s02, s03, s05, s08, s10, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Rotates the object's offset (yaw, pitch) into out[0..2] and adds the object's position (>> 12). */
void obj_offset_to_world_shifted(Object *obj, s32 *out) {
    rotate_xz_twice(obj->yaw, -obj->pitch, out, out + 1, out + 2);
    out[0] = (obj->x >> 12) + out[0];
    out[1] = (obj->y >> 12) + out[1];
    out[2] = (obj->z >> 12) + out[2];
}

void enemy_hit_knockback(Object *obj, s32 force, s32 step);

/* Inverse of obj_offset_to_world_shifted: rotates the offset into out[0..2] and sets out to the position plus that (<< 12). */
void obj_offset_to_fixed(Object *obj, s32 *out) {
    rotate_xz_twice(obj->yaw, -obj->pitch, out, out + 1, out + 2);
    out[0] = obj->x + (out[0] << 12);
    out[1] = obj->y + (out[1] << 12);
    out[2] = obj->z + (out[2] << 12);
}

/* Turn a direction vector into angles: out = (-pitch, yaw, 0). */
void vec3_to_angles(Vec3 *dir, SVECTOR *out) {
    s32 yaw;
    s32 pitch;

    angles_to_player(dir->x, dir->y, dir->z, &yaw, &pitch);
    out->vz = 0;
    out->vy = yaw;
    out->vx = -pitch;
}

/* Resets the enemy fields and the first two handlers. */
void enemy_reset(Object *obj) {
    obj->unk_17A = 0;
    obj->speed = 0;
    obj->vz = 0;
    obj->vx = 0;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
}

/* Starts a script: the table entry for the current mode becomes the cursor. */
void enemy_script_start(Object *obj, s16 **scripts, s16 **jumps) {
    s16 *script = scripts[obj->vars.enemy.mode];

    obj->script.data = jumps;
    obj->script.unk_0A = 0;
    obj->script.pc = script;
}

void enemy_draw(Object *obj) {
    FlashScratch *scr = scratch_alloc(sizeof(FlashScratch));
    Vec3 *pos = &scr->pos;
    SVECTOR *rot = &scr->box;
    s32 value;
    s32 colour;
    s32 z;
    s32 size;

    value = obj_keyframe_value(obj, 0);
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
        /* The second store keeps jump.c from turning this select into slt/negu/and; as a branch,
         * colour's known bits still let combine fold spark_add's chain (colour >> 24) to 0. */
        colour = 0;
        colour = 0;
    }
    pos->x = obj->x;
    pos->y = obj->y;
    z = obj->z;
    pos->z = z;
    spark_add(pos->x >> 12, pos->y >> 12, z >> 12, obj->yaw, -obj->pitch, 0, value, colour);
    size = obj->width;
    size += size >> 1;
    rot->vx = size;
    rot->vy = obj->height;
    rot->vz = size;
    aim_marker_draw(2, rot, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= sizeof(FlashScratch);
}

static inline s32 enemy_mode_is_hittable(s32 *mode_ptr, u32 alt_mode) {
    u32 mode = *mode_ptr;
    return mode < 2 || mode == alt_mode;
}
u32 enemy_init(Object *obj, Placement *place) {
    u16 flags;

    obj->handlers[0].fn = (void *)obj_link_script_run;
    obj->handlers[1].fn = obj_script_step;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = (void *)enemy_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32)obj_spawn_from_placement;
    flags = *(u16 *)&place->unk_1A;
    place->unk_02 = 0x708;
    obj->vars.words[1] = -1;
    obj->vars.enemy.unk_250 = 0;
    obj->vars.words[3] = 0;
    obj->vars.enemy.walk_state = -1;
    obj->vars.enemy.target_yaw = 0;
    obj->vars.enemy.mode = flags >> 8;
    obj->vars.enemy.unk_25C = place->range;
    *(s16 *)&obj->vars.enemy.unk_260[4] = 0xA00;
    obj->vars.enemy.unk_25E = 0x600;
    *(s16 *)&obj->vars.enemy.unk_260[0] = 0x300;
    *(s16 *)&obj->vars.enemy.unk_260[2] = 0x330;
    *(s16 *)&obj->vars.enemy.unk_276[2] = place->y & 0xFFF;
    *(s16 *)&obj->vars.enemy.unk_276[4] = ((place->y & 0xFFF) + 0x800) & 0xFFF;
    obj->vars.enemy.target_yaw = *(u16 *)&obj->vars.enemy.unk_276[2];
    obj->vars.enemy.sound = 0;
    obj->kind = place->unk_04[1];
    obj->hit_cooldown_max = 0x30;
    if (enemy_mode_is_hittable(&obj->vars.enemy.mode, 3)) {
        obj->unk_1C6 = 4;
    }
    return obj->vars.enemy.mode;
}

/* Angle from the object to its placement point, in the x/z plane (result unused). Positions are
 * 12-bit fixed point. */
s32 obj_placement_angle(Object *obj) {
    Placement *placement = obj->placement;

    return atan2((placement->z >> 12) - (obj->z >> 12), (placement->x >> 12) - (obj->x >> 12));
}

/* Horizontal distance from the object to its placement point (result unused). */
s32 obj_placement_dist(Object *obj) {
    Placement *placement = obj->placement;
    s32 dx = (placement->x >> 12) - (obj->x >> 12);
    s32 dz = (placement->z >> 12) - (obj->z >> 12);

    return SquareRoot0(length_sq(dx, 0, dz));
}

/* Distance from the object to the camera point (both >> 12). Flags it against two thresholds and,
   when the second is set, traces the object's position (raised by part.unk_276) through player_position_copy. */
void enemy_sense(Object *obj) {
    s32 *pos;
    s32 dist;
    s32 lift;

    obj->vz = 0;
    obj->vx = 0;
    dist = isqrt(length_sq((VEC_80139584.x >> 12) - (obj->x >> 12),
                           (VEC_80139584.y >> 12) - (obj->y >> 12),
                           (VEC_80139584.z >> 12) - (obj->z >> 12)));
    obj->vars.enemy.unk_258 = dist;
    obj->vars.enemy.unk_268 = dist < obj->vars.enemy.unk_25E;
    obj->vars.enemy.unk_269 = obj->vars.enemy.unk_258 < obj->vars.jitter.timer;
    obj->vars.enemy.unk_266 = obj_placement_dist(obj) < obj->vars.drift.current.state;
    if (obj->vars.enemy.unk_269 != 0) {
        pos = scratch_alloc(0x20);
        lift = obj->vars.part.unk_276;
        pos[4] = obj->x >> 12;
        pos[5] = obj->y >> 12;
        pos[6] = obj->z >> 12;
        pos[5] += lift;
        player_position_copy((VECTOR *)pos);
        obj->vars.enemy.unk_274 = trace_world(8, 8, &pos[4], pos, &pos[4]) == 0;
        scratch_top -= 0x20;
    } else {
        obj->vars.enemy.unk_274 = 0;
    }
    if (obj->next_state == 3 && obj->vars.enemy.mode == 2) {
        obj->vars.enemy.mode = 0;
    }
}

/* Remembers the hit cooldown in vars.words[2] and passes it on (twice the value) when non-zero. */
void enemy_hit_update(Object *obj) {
    obj->vars.words[2] |= obj->hit_cooldown;
    if (obj->hit_cooldown != 0) {
        enemy_hit_knockback(obj, obj->unk_1C6, obj->hit_cooldown * 2);
    }
}

void enemy_turn_toward(Object *obj, s32 step) {
    s32 yaw = obj->yaw;
    s32 target = obj->vars.enemy.target_yaw;
    s32 new_yaw = angle_approach(yaw, target, step);
    yaw = new_yaw - yaw;
    obj->yaw = new_yaw;
    obj->turn = yaw;
}

void enemy_turn_toward_wobble(Object *obj, s32 step) {
    s32 old_yaw;
    s32 yaw;

    old_yaw = obj->yaw;
    yaw = angle_approach(old_yaw, obj_angle_wobble(obj, obj->vars.enemy.target_yaw), step);
    old_yaw = yaw - old_yaw;
    obj->yaw = yaw;
    obj->turn = old_yaw;
}

/* Behaviour step. result -2 (start): picks a wait of 1..span steps in the word at 0x254 and goes on (0x20);
 * -1: counts the wait down (then sets next_state 0), flags 0x242 and restarts when the player is farther
 * than the placement's range, and when unk_268 is set and nothing blocks the line from the object to its
 * aim point (the height/2 above its position) sets next_state to 3; other results: obj_turn_toward_player. */
void enemy_wait_step(Object *obj, ObjHandler *handler, s32 span) {
    s32 *pos;
    s32 dist;
    s32 h;
    s32 hit;

    switch (handler->result) {
    case -2:
        *(s32 *)&obj->vars.enemy.sound_channel[0] = rand_a_next() % span + 1;
        handler->result = 0x20;
        break;
    case -1:
        if (obj->script_flag != 0) {
            if (*(s32 *)&obj->vars.enemy.sound_channel[0] > 0) {
                (*(s32 *)&obj->vars.enemy.sound_channel[0])--;
            } else {
                obj->next_state = 0;
            }
            dist = SquareRoot0(length_sq((obj->placement->x >> 12) - (obj->x >> 12), 0,
                                         (obj->placement->z >> 12) - (obj->z >> 12)));
            if (obj->placement->range < dist) {
                obj->unk_242 = 1;
                handler->result = 0x20;
            }
            if (obj->vars.enemy.unk_268 != 0) {
                pos = scratch_alloc(0x20);
                h = (s16)obj->height;
                pos[4] = obj->x >> 12;
                pos[5] = obj->y >> 12;
                pos[6] = obj->z >> 12;
                pos[5] += -h / 2;
                player_position_copy((VECTOR *)pos);
                hit = trace_world(8, 8, &pos[4], pos, &pos[4]);
                scratch_top -= 0x20;
                if (hit == 0) {
                    obj->next_state = 3;
                }
            }
        }
        break;
    default:
        obj_turn_toward_player(obj, 8);
        break;
    }
}

/* Behaviour step of a wandering enemy (S01): turns toward its start, walks, and backs off past its range
 * (vars.enemy.walk_state: > 0 heading back, < 0 returning, 0 free). */
void enemy_wander_step(Object *obj, ObjHandler *handler) {
    Placement *place;
    s32 result;
    s32 dx;
    s32 dz;
    s32 active;

    switch (handler->result) {
    case -2:
        if (obj->vars.enemy.walk_state > 0) {
            obj->vars.enemy.walk_state = -1;
            obj->vars.enemy.target_yaw = (obj->vars.enemy.target_yaw + 0x800) & 0xFFF;
        }
        result = 1;
        break;
    case -1:
        if (obj->yaw != obj->vars.enemy.target_yaw) {
            enemy_turn_toward(obj, 0x30);
            result = 1;
            obj->speed = 0;
            break;
        }
        if (obj->speed == 0) {
            obj->speed = 2;
        }
        active = obj->blocked_x;
        if (active == 0) {
            active = obj->blocked_z;
        }
        if (active != 0 && obj->vars.enemy.walk_state == 0) {
            obj->vars.enemy.walk_state = 1;
            result = -2;
            break;
        }
        place = (Placement *)obj->placement;
        dx = (place->x >> 12) - (obj->x >> 12);
        dz = (place->z >> 12) - (obj->z >> 12);
        if (SquareRoot0(length_sq(dx, 0, dz)) <= ((Placement *)obj->placement)->range - 0x80 &&
            obj->vars.enemy.walk_state < 0) {
            obj->vars.enemy.walk_state = 0;
        } else {
            place = (Placement *)obj->placement;
            dx = (place->x >> 12) - (obj->x >> 12);
            dz = (place->z >> 12) - (obj->z >> 12);
            if (SquareRoot0(length_sq(dx, 0, dz)) > ((Placement *)obj->placement)->range) {
                if (obj->vars.enemy.walk_state == 0) {
                    obj->vars.enemy.walk_state = 1;
                }
            }
            if (obj->vars.enemy.walk_state > 0) {
                handler->result = -2;
            }
        }
        if (obj->vars.enemy.unk_268 != 0 && obj->vars.enemy.unk_274 != 0) {
            obj->next_state = 5;
        }
        return;
    default:
        enemy_turn_toward(obj, 0x30);
        if (obj->turn == 0) {
            result = -1;
        } else {
            result = 1;
            obj->speed = 0;
        }
        break;
    }
    handler->result = result;
}

#if STAGE != 1
void enemy_wander_step(Object *obj, ObjHandler *handler);
#endif

void enemy_move_or_wait(Object *obj, ObjHandler *handler) {
    s32 mode = obj->vars.enemy.mode;

    if (mode == 2 || mode == 4) {
        enemy_wander_step(obj, handler);
    } else {
        enemy_wait_step(obj, handler, 5);
    }
    fly_move(obj->yaw, obj->speed, &obj->vz, &obj->vx);
}

void enemy_wait_switch(Object *obj, ObjHandler *handler) {
    enemy_wait_step(obj, handler, 3);
    if (obj->vars.enemy.unk_268 != 0) {
        obj->next_state = 3;
    }
    if (handler->result == -1 && obj->script_flag != 0) {
        handler->result = 0x10;
    }
}

static inline s32 player_bearing(Object *obj) {
    s32 *p = player_position();

    return atan2(p[2] - (obj->z >> 12), p[0] - (obj->x >> 12));
}

static inline s32 yaw_delta(s16 to, s32 from) {
    return to - from;
}

/* 1 when the player's bearing is more than limit away from the yaw. */
static inline s16 yaw_far(Object *obj, s32 bearing, s32 old, s32 limit) {
    if (bearing - old >= 0) {
        if (player_bearing(obj) - obj->yaw > limit) {
            return 1;
        }
        return 0;
    }
    if (old - player_bearing(obj) > limit) {
        return 1;
    }
    return 0;
}

/* 1 when aim is less than 0x300 away from the yaw (the sign extension only on the positive side). */
static inline s16 yaw_near(Object *obj, s32 aim) {
    s32 yaw = obj->yaw;
    s32 shifted = yaw << 16;

    if (aim - yaw >= 0) {
        if (aim - (shifted >> 16) < 0x300) {
            return 1;
        }
        return 0;
    }
    if (yaw - aim < 0x300) {
        return 1;
    }
    return 0;
}

/* Turns the yaw toward aim by at most step and records the turn. */
static inline void yaw_approach(Object *obj, s32 aim, s32 step) {
    s32 old = obj->yaw;
    s16 new_yaw = angle_approach(old, aim, step);
    s32 turn = new_yaw;

    obj->yaw = new_yaw;
    turn -= old;
    obj->turn = turn;
}

/* Behaviour step of a walking enemy. In modes 3 and 4 it engages at once (next_state 5) and
 * doesn't walk; otherwise it engages when the player is in range with a clear line of sight.
 * While the wait timer (0x26E) runs it only walks. Result -2 picks a new wait and nudges the
 * yaw; -1 engages when facing the player in range; others turn toward the player (twice as
 * fast when it is more than 0x400 off the facing). */
void enemy_walk_step(Object *obj, ObjHandler *handler) {
    s32 *p;
    s32 *pos;
    s32 height;
    s32 hit;
    s32 aim;
    s32 yaw;
    s32 step;
    s32 limit;
    s32 active;
    s32 spread;
    s32 turn;
    s32 shifted;

    if ((u32)(obj->vars.enemy.mode - 3) < 2) {
        obj->next_state = 5;
        return;
    }
    if (obj->vars.enemy.unk_269 != 0 && enemy_in_range(obj, 0x500, 0x200) != 0) {
        p = scratch_alloc(0x20);
        height = (s16)obj->height;
        p[4] = obj->x >> 12;
        p[5] = obj->y >> 12;
        p[6] = obj->z >> 12;
        p[5] += -height / 2;
        player_position_copy((VECTOR *)p);
        hit = trace_world(8, 8, &p[4], p, &p[4]);
        scratch_top -= 0x20;
        if (hit == 0) {
            obj->next_state = 5;
            return;
        }
    }
    if (*(s16 *)obj->vars.enemy.unk_26E > 0) {
        (*(s16 *)obj->vars.enemy.unk_26E)--;
        *(s16 *)obj->vars.enemy.unk_26E =
            NOT_NEGATIVE(CLAMP_HI_VAR(*(s16 *)obj->vars.enemy.unk_26E, 0x30));
        goto move;
    }
    switch (handler->result) {
    case -2:
        obj->vars.enemy.unk_250 = 0;
        obj->unk_242 = 0;
        handler->result = rand_a_next() % 16 + 0x18;
        yaw = obj->yaw;
        spread = rand_a_next() % 0x300 - 0x180;
        yaw += spread;
        obj->yaw = yaw;
        break;
    case -1:
        if (obj->script_flag == 0) {
            break;
        }
        if (obj->vars.enemy.unk_269 != 0) {
            turn = obj->turn;
            shifted = turn << 16;
            if ((turn >= 0 ? (shifted >> 16) < 8 : -turn < 8) &&
                enemy_in_range(obj, 0x500, 0x200) != 0) {
                obj->next_state = 5;
            }
        }
        if (obj->vars.enemy.unk_268 == 0) {
            if ((u32)(obj->vars.enemy.mode - 3) < 2) {
                obj->next_state = 2;
            } else {
                obj->next_state = 0;
            }
        }
        handler->result = rand_a_next() % 16 + 0x18;
        break;
    default:
        if (obj->vars.enemy.unk_269 != 0) {
            /* atan2 straight into yaw_near: player_bearing's extra copy would merge the bearing's two registers */
            pos = player_position();
            if (yaw_near(obj, atan2(pos[2] - (obj->z >> 12), pos[0] - (obj->x >> 12)))) {
                turn = obj->turn;
                shifted = turn << 16;
                if (turn >= 0 ? (shifted >> 16) < 8 : -turn < 8) {
                    if (enemy_in_range(obj, 0x480, 0x200) != 0) {
                        obj->next_state = 5;
                    }
                } else {
                    handler->result = 1;
                }
                break;
            }
            yaw_approach(obj, (s16)player_bearing(obj), 0x20);
            break;
        }
        step = 0x10;
        limit = 0x400;
        aim = player_bearing(obj);
        yaw = obj->yaw;
        if (yaw_far(obj, aim, yaw, limit)) {
            step *= 2;
        }
        active = obj->blocked_x;
        if (active == 0) {
            active = obj->blocked_z;
        }
        if (active != 0) {
            obj_turn_toward_player(obj, (s16)step);
            break;
        }
        yaw_approach(obj, (s16)player_bearing(obj), (s16)step);
        break;
    }
move:
    if ((u32)(obj->vars.enemy.mode - 3) < 2) {
        obj->speed = 0;
    } else {
        fly_move(obj->yaw, obj->speed, &obj->vz, &obj->vx);
    }
}

/* Behaviour step of a flying enemy (S01). */
void flyer_wander(Object *obj, ObjHandler *handler) {
    s32 *pos;
    s32 height;
    s32 hit;
    s32 old;
    s32 yaw;
    s32 limit;
    s32 active;
    s32 spread;
    s32 new_yaw;

    if (obj->vars.flyer.unk_269 != 0) {
        pos = scratch_alloc(0x20);
        height = (s16)obj->height;
        pos[4] = obj->x >> 12;
        pos[5] = obj->y >> 12;
        pos[6] = obj->z >> 12;
        pos[5] += -height / 2;
        player_position_copy((VECTOR *)pos);
        hit = trace_world(8, 8, &pos[4], pos, &pos[4]);
        scratch_top -= 0x20;
        if (hit == 0) {
            obj->next_state = 5;
            return;
        }
    }
    switch (handler->result) {
    case -2:
        if ((u32)(obj->vars.flyer.mode - 3) < 2) {
            if (obj->vars.flyer.mode == 3) {
                obj->next_state = 0;
            } else {
                obj->next_state = 2;
            }
            return;
        }
        obj->vars.flyer.wait_count = rand_a_next() % 3 + 1;
        yaw = player_bearing(obj);
        spread = rand_a_next();
        yaw -= 0x180;
        yaw += spread % 0x300;
        obj->vars.flyer.target_yaw = yaw;
        handler->result = -1;
        break;
    case -1:
        if (obj->script_flag == 0) {
            goto turn;
        }
        active = obj->blocked_x;
        if (active == 0) {
            active = obj->blocked_z;
        }
        if (active != 0 &&
            obj->vars.flyer.unk_258 < obj->vars.flyer.unk_25E * 3 / 4) {
            obj->next_state = 3;
            break;
        }
        if (obj->vars.flyer.unk_269 != 0) {
            limit = 0x300;
            yaw = player_bearing(obj);
            old = obj->yaw;
            if (yaw_far(obj, yaw, old, limit)) {
                yaw = (s16)player_bearing(obj);
                old = obj->yaw;
                new_yaw = angle_approach(old, yaw, 0x30);
                obj->turn = yaw_delta(new_yaw, old);
                obj->yaw = new_yaw;
                obj->next_state = 5;
            }
        } else if (obj->vars.flyer.wait_count > 0 &&
                   obj->vars.flyer.unk_258 < obj->vars.flyer.unk_262) {
            obj->vars.flyer.wait_count--;
        } else {
            obj->next_state = 2;
            goto turn;
        }
        break;
    default:
    turn:
        enemy_turn_toward(obj, 0xC);
        break;
    }
    fly_move(obj->yaw, obj->speed, &obj->vz, &obj->vx);
}

/* Behaviour step of a flying enemy that turns away from the player. */
void flyer_retreat(Object *obj, ObjHandler *handler) {
    s32 old;
    s32 from;
    s32 yaw;
    s32 limit;
    s32 new_yaw;
    s32 placement;

    s32 result = handler->result;

    switch (result) {
    case -2:
        if ((u32)(obj->vars.flyer.mode - 3) < 2) {
            if (obj->vars.flyer.mode == 3) {
                obj->next_state = 0;
            } else {
                obj->next_state = 2;
            }
            return;
        }
        obj->vars.flyer.wait_count = rand_a_next() % 3 + 1;
        obj->vars.flyer.target_yaw = player_bearing(obj) + 0x800;
        placement = obj_placement_angle(obj);
        if (placement - obj->vars.flyer.target_yaw >= 0) {
            if (placement - obj->vars.flyer.target_yaw > 0x400) {
                goto reset;
            }
        } else if (obj->vars.flyer.target_yaw - placement > 0x400) {
        reset:
            obj->vars.flyer.target_yaw = placement;
        }
        handler->result = 0x78;
        break;
    case -1:
        if (obj->script_flag == 0) {
            goto turn;
        }
        if (obj->vars.flyer.unk_269 != 0) {
            limit = 0x300;
            yaw = player_bearing(obj);
            old = obj->yaw;
            if (!yaw_far(obj, yaw, old, limit)) {
                yaw = (s16)player_bearing(obj);
                from = obj->yaw;
                new_yaw = angle_approach(from, yaw, 0x30);
                obj->turn = yaw_delta(new_yaw, from);
                obj->yaw = new_yaw;
                obj->next_state = 5;
                break;
            }
        }
        if (obj->vars.flyer.wait_count > 0) {
            obj->vars.flyer.wait_count--;
        } else {
            obj->next_state = 2;
        }
        goto turn;
    default:
        if (result < 7) {
            obj->vars.flyer.target_yaw = obj_placement_angle(obj);
        }
    turn:
        enemy_turn_toward_wobble(obj, 0xC);
        break;
    }
    fly_move(obj->yaw, obj->speed, &obj->vz, &obj->vx);
}

/* Reaction of an object to a hit: when dead it turns away from the hit's source; otherwise it is pushed
 * from it for the cooldown steps. */
void enemy_hit_knockback(Object *obj, s32 force, s32 step) {
    s32 dx;
    s32 dz;
    s32 old_yaw;
    s16 yaw;
    s32 turn;
    s32 cooldown;
    s32 from;
    s32 ddx, ddz;

    if (obj->health <= 0) {
        old_yaw = obj->yaw;
        yaw = angle_approach(old_yaw, (obj->hit_from + 0x800) & 0xFFF, (s16)step);
        turn = yaw;
        obj->yaw = yaw;
        turn -= old_yaw;
        obj->turn = turn;
        return;
    }
    cooldown = obj->hit_cooldown;
    if (cooldown > 0) {
        obj->unk_242 = 0;
        if ((s16)step != 0) {
            force++;
            force--;
            obj_turn_toward_player(obj, (s16)step);
        }
        from = obj->hit_from;
        if (from >= 0) {
            dx = 0;
            dz = 0;
            fly_move(from, cooldown * force / 48, &dx, &dz);
            obj->pitch = (cooldown - 1) * 4;
            ddx = dx;
            obj->vz += ddx;
            ddz = dz;
            obj->vx += ddz;
        }
    }
}

s32 enemy_in_range(Object *obj, s32 range_x, s32 range_z) {
    s32 dz;
    s32 dx;
    s32 ax;
    s32 az;

    if (obj->vars.enemy.unk_258 < 0x168) {
        return 1;
    }
    point_to_view_angles(obj->x >> 12, obj->y >> 12, obj->z >> 12, &dx, &dz);
    ax = dx;
    az = dz;
    if (ax > 0x800) {
        ax = 0x1000 - ax;
    }
    if (az > 0x800) {
        az = 0x1000 - az;
    }
    ax = ax < range_x;
    if (!ax) {
        return 0;
    }
    return az < range_z;
}

/* Spawns an object of this object's kind (its type plus the index of its asset) at its position in whole
 * units, with its angles (pitch negated), then marks its placement as spawned (byte 4 bits 0-1 = 2). */
s32 obj_spawn_from_placement(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 kind;
    Placement *placement;
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    rot[2] = (u16)obj->roll;
    kind = *(s16 *)&obj->type.unk_0E;
    object_spawn_at(pos, rot, kind + model_slot_pchr(*(s32 *)obj->asset));
    placement_list_pop((ListRecord *)obj->placement);
    placement = obj->placement;
    placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
    return 0;
}
