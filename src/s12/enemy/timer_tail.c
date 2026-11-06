/* timer_tail: one of s12's own original source files (scripts/objmap.py); part of src/s12/main.c's unit, included there. */

void timer_tail_tick(TimerTail *t);
void spin_laser_update(Object *obj, ObjHandler *handler);
void time_bomb_draw();
s32 enemy_death_step(Object *obj);
void obj_destroy_loop_sound(Object *obj);
extern StateEntry timer_tail_states[1];
extern s16 *timer_tail_script_value[];
extern s16 timer_tail_script[];
/* Spawns the timer-tail object from a placement; returns 1 when it got a slot. */
s32 timer_tail_spawn(Placement *place) {
    Object *obj;
    TimerTailFields *tail;
    s32 sound;
    s32 x, y, z;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    obj->handlers[0].fn = (ObjHandlerFn)timer_tail_tick; /* takes a TimerTail * */
    obj->handlers[1].fn = spin_laser_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = time_bomb_draw;
    obj->callback = (s32)enemy_death_step;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->destructor = obj_destroy_loop_sound;
    obj->kind = place->unk_00[5];
    obj->asset = &timer_tail_data;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = 0;
    obj->state_table = timer_tail_states;
    script_start((Script *)obj, timer_tail_script, (s32)&timer_tail_script_value);
    obj_init_from_place(obj, place, 0x174);
    obj->speed = 0;
    obj_set_part_bounds(obj, 1, 0x200);
    *(u16 *)&obj->placement->unk_00[2] = 0x708;
    x = obj->x;
    if (x < 0) {
        x += 0xFFF;
    }
    y = obj->y;
    obj->vars.timer_tail.home_x = x >> 12;
    if (y < 0) {
        y += 0xFFF;
    }
    z = obj->z;
    obj->vars.timer_tail.home_y = y >> 12;
    if (z < 0) {
        z += 0xFFF;
    }
    obj->vars.timer_tail.home_z = z >> 12;
    tail = (TimerTailFields *)obj;
    tail->unk_268 = rand_a_next();
    tail->unk_26A = 0;
    tail->unk_274 = 0;
    tail->unk_276 = 0;
    tail->unk_26E = 0;
    tail->unk_270 = 0;
    tail->unk_26C = 0;
    tail->unk_272 = 0;
    sound = sound_start(SND_TIMER_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
    tail->sound_handle = sound;
    sound_attach(sound & 0xFFFF, &obj->x, NULL);
    return 1;
}

/* Picks a new move target (vars.words[0..2]) once: near the player (within 0x600) a random point around the
 * player rotated by the view, else a random point around the home position (vars.words[4..6]); retried up to
 * 3 times while trace_world hits something, then clamped to 0x300 from the object.
 * Scratch v: [0..2] target, [4..6] object position, [8..10] player / home position (all >> 12). */
void enemy_pick_wander_point(Object *obj) {
    s32 *m;
    s32 *v;
    s32 *src;
    s32 tries;
    s32 direct;
    s32 dx, dy, dz;
    s32 dist_cam;
    s32 dist_pos;

    tries = 0;
    if (obj->vars.timer_tail.unk_274 == 0) {
        m = scratch_alloc(0x20);
        v = scratch_alloc(0x30);
        view_matrix_copy(m);
        v[4] = obj->x >> 12;
        v[5] = obj->y >> 12;
        v[6] = obj->z >> 12;
        player_position_copy((VECTOR *)&v[8]);
        src = (s32 *)&obj->vars.timer_tail.home_x;
        dist_cam = isqrt(length_sq(v[8] - v[4], v[9] - v[5], v[10] - v[6]));
        direct = 1;
        v[8] = obj->vars.timer_tail.home_x;
        v[9] = obj->vars.timer_tail.home_y;
        v[10] = obj->vars.timer_tail.home_z;
        dy = v[9] - v[5];
        dz = v[10] - v[6];
        dist_pos = isqrt(length_sq(v[8] - v[4], dy, dz));
        if (dist_cam < 0x600) {
            src = player_position();
            direct = 0;
        }
        if (dist_pos >= 0x7D1) {
            src = (s32 *)&obj->vars.timer_tail.home_x;
            direct = 1;
        }
        while (1) {
            tries++;
            if (tries >= 4) {
                v[0] = v[8];
                v[1] = v[9];
                v[2] = v[10];
                break;
            }
            dx = rand_a_next() % 0x200 - 0x100;
            if (direct == 0) {
                dy = rand_a_next() % (isqrt(length_sq(dx, 0, dz)) * 5 / 3);
                dy = MAX(MIN(dy, 0x200), 0xC8);
                dy = -dy;
                dz = rand_a_next() % 0x100;
                {
                    s32 a = ((volatile s32 *)m)[0];
                    s32 b = ((volatile s32 *)m)[1];
                    s32 c = ((volatile s32 *)m)[2];
                    gte_set_ctrl(R11R12, a);
                    gte_set_ctrl(R13R21, b);
                    gte_set_ctrl(R22R23, c);
                    a = ((volatile s32 *)m)[3];
                    b = ((volatile s32 *)m)[4];
                    gte_set_ctrl(R31R32, a);
                    gte_set_ctrl(R33, b);
                }
                gte_set(IR1, dx);
                gte_set(IR2, dy);
                gte_set(IR3, dz);
                gte_rtir();
                gte_get(MAC1, dx);
                gte_get(MAC2, dy);
                gte_get(MAC3, dz);
                v[0] = src[0] + dx;
                v[1] = src[1] + dy;
                v[2] = src[2] + dz;
            } else {
                dz = rand_a_next() % 0x200 - 0x100;
                v[0] = src[0] + dx;
                v[1] = src[1];
                v[2] = src[2] + dz;
            }
            if (trace_world(2, 0x80, &v[4], v, &v[8]) == 0) break;
        }
        dx = v[0] - v[4];
        dy = v[1] - v[5];
        dz = v[2] - v[6];
        dist_pos = isqrt(length_sq(dx, dy, dz));
        if (dist_pos >= 0x300) {
            dx = dx * 0x300 / dist_pos;
            dy = dy * 0x300 / dist_pos;
            dz = dz * 0x300 / dist_pos;
            v[0] = dx + v[4];
            v[1] = dy + v[5];
            v[2] = dz + v[6];
        }
        v[0] <<= 12;
        v[1] <<= 12;
        v[2] <<= 12;
        obj->vars.timer_tail.wander_target_x = v[0];
        obj->vars.timer_tail.wander_target_y = v[1];
        obj->vars.timer_tail.wander_target_z = v[2];
        scratch_top -= 0x50;
        obj->vars.timer_tail.unk_274 = 1;
    }
}

void enemy_pick_wander_point(Object *obj);
/* Per-frame tick: advances the 0x26A timer; at random (1 in 120) rearms the
 * 0x270 counter to 45 and marks 0x276; once the timer passes 120, a 1 in 10
 * roll calls enemy_pick_wander_point and bumps the 0x272 counter. */
void timer_tail_tick(TimerTail *t) {
    s16 timer = t->wander_timer + 1;

    t->unk_1B7 = 0;
    t->wander_timer = timer;
    if (t->unk_270 == 0 && t->unk_274.word == 0) {
        s32 roll = rand_a_next();
        if (roll == (roll / 120) * 120 || t->wander_count >= 3) {
            t->unk_270 = 45;
            t->unk_274.half[1] = 1;
            t->wander_count = 0;
        }
    }
    if ((s16)t->wander_timer >= 0x79) {
        s32 roll = rand_a_next();
        if (roll == (roll / 10) * 10 && t->unk_270 == 0) {
            enemy_pick_wander_point((Object *)t);
            t->wander_timer = 0;
            t->wander_count++;
        }
    }
}

extern SinCosHalves sincos_halves[] __asm__("rcossin_tbl");
/* s12 laser ball: bobs, spins up with spin (0x1000 = full: fires a stream), aims at the player when still */
void spin_laser_update(Object *obj, ObjHandler *handler) {
    s32 spin;
    s32 idx;
    s32 cos_full;
    s32 sin_v;
    s32 sin_full;
    s32 scale;
    s32 dx;
    s32 dy;
    s32 dz;
    VECTOR pos;
    SVECTOR rot;
    s32 yaw;
    s32 pitch;
    s32 shot_yaw;
    s32 shot_pitch;

    if (obj->vars.spin_laser.frozen == 0) {
        if (obj->vars.spin_laser.spin > 0x1400) {
            obj->vars.spin_laser.spin = 0x1400;
            obj->vars.spin_laser.spin_step *= -1;
        }
        if (obj->vars.spin_laser.spin < 0) {
            obj->vars.spin_laser.spin_step = 0;
            obj->vars.spin_laser.spin = 0;
        }
        spin = obj->vars.spin_laser.spin += obj->vars.spin_laser.spin_step;
        spin = MAX(MIN(spin, 0x1000), 0);
        idx = obj->vars.spin_laser.phase = (obj->vars.spin_laser.phase + 0x20 + spin * 96 / 4096) & 0xFFF;
        scale = spin * 3;
        cos_full = cos_table[idx].value;
        sin_full = (s16)sincos_halves[idx].sin;
        obj->x += cos_full / 4;
        obj->z += cos_full / 4;
        sin_v = sin_full / 2;
        obj->y += sin_v;
        obj->x += cos_full / 4 * scale / 4096;
        obj->z += cos_full / 4 * scale / 4096;
        obj->y += sin_v * scale / 4096;
        if (obj->vars.spin_laser.moving != 0) {
            dx = (obj->vars.spin_laser.target[0] - obj->x) / 10;
            dy = (obj->vars.spin_laser.target[1] - obj->y) / 10;
            dz = (obj->vars.spin_laser.target[2] - obj->z) / 10;
            obj->x += dx;
            dx = __builtin_abs(dx);
            obj->y += dy;
            dy = __builtin_abs(dy);
            obj->z += dz;
            dz = __builtin_abs(dz);
            sound_set_pitch(obj->vars.spin_laser.sound, ((dx + dy + dz) / 4096) * 32 + 0x1E00);
            dx = (obj->x - obj->vars.spin_laser.target[0]) / 4096;
            dy = (obj->y - obj->vars.spin_laser.target[1]) / 4096;
            dz = (obj->z - obj->vars.spin_laser.target[2]) / 4096;
            if (isqrt(length_sq(dx, dy, dz)) < 16) {
                obj->vars.spin_laser.moving = 0;
                obj->vars.spin_laser.fired = 0;
                sound_set_pitch(obj->vars.spin_laser.sound, 0x1E00);
            }
        }
        if (spin == 0) {
            angles_to_player(obj->x >> 12, obj->y >> 12, obj->z >> 12, &yaw, &pitch);
            obj->yaw = angle_approach(obj->yaw, yaw, 0x40);
            obj->pitch = angle_approach(obj->pitch, pitch, 0x40);
        } else if (spin < 0x1000) {
            obj->yaw += spin / 32;
            obj->pitch += spin / 32;
            obj->roll += spin / 128;
        } else {
            SVECTOR unused; /* never used; the original frame has it */
            u16 *shot_rot;

            obj->yaw = rand_a_next();
            obj->pitch = rand_a_next();
            obj->roll += 0x20;
            shot_pitch = -obj->pitch;
            rot.vx = shot_pitch;
            shot_yaw = obj->yaw;
            rot.vy = shot_yaw;
            rot.vz = obj->roll;
            angles_to_vector(shot_yaw, rot.vx, 0x20, &pos.vx, &pos.vy, &pos.vz);
            pos.vx = (pos.vx + obj->x) >> 12;
            pos.vy = (pos.vy + obj->y) >> 12;
            pos.vz = (pos.vz + obj->z) >> 12;
            shot_rot = (u16 *)&rot;
            if (!(obj->vars.spin_laser.timer & 1)) {
                if (!(obj->vars.spin_laser.timer & 7)) {
                    sound_play_at_units(SND_SHOT_FIRE_ALT | SND_GROUP(2), 0x40, 0x3C, &pos);
                }
                shot_spawn_obj(&pos.vx, shot_rot, 3, (obj->damage << 16) | 0x20);
            }
        }
    }
    obj_script_step(obj, handler);
}


void time_bomb_draw(Object *obj, ObjHandler *handler) {
    Vec3 *pos = scratch_alloc(0x10);
    ScratchRot *blk = scratch_alloc(0x10);
    s32 colour;
    s32 pitch;
    s32 value;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    pitch = obj->pitch;
    blk->spark_rot.vx = -pitch;
    blk->spark_rot.vy = obj->yaw;
    blk->spark_rot.vz = obj->roll;
    value = model_slot_pchr(*(s32 *)obj->asset) + 1;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
        colour = 0;
        FAKE_OPAQUE(obj);
    }
    spark_add(pos->x, pos->y, pos->z, blk->spark_rot.vy, blk->spark_rot.vx, blk->spark_rot.vz, value, colour);
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    blk->rot.vx = obj->width * 3;
    blk->rot.vy = obj->height;
    blk->rot.vz = obj->unk_1E8[0] * 3;
    aim_marker_draw(2, &blk->rot, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x20;
}


s32 enemy_death_step(Object *obj) {
    s32 pos[3];

    if (obj->vars.enemy.walk_state != 0) {
        obj->vars.enemy.walk_state++;
        if (obj->vars.enemy.walk_state >= 0xC) {
            pos[0] = obj->x >> 12;
            pos[1] = obj->y >> 12;
            pos[2] = obj->z >> 12;
            spawn_effect(pos[0], pos[1], pos[2], 0);
            placement_list_pop((ListRecord *)obj->placement);
            ((u8 *)obj->placement)[4] = (((u8 *)obj->placement)[4] & 0xFC) | 2;
            return 0;
        }
        return 1;
    }
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    spawn_effect(pos[0], pos[1], pos[2], 2);
    obj->flags = 0x160;
    obj->unk_17A = 0;
    obj->vars.enemy.walk_state++;
    if (*(u16 *)&obj->vars.enemy.unk_276[2] != 0) {
        sound_stop(*(u16 *)&obj->vars.enemy.unk_276[2]);
        *(u16 *)&obj->vars.enemy.unk_276[2] = 0;
    }
    return 1;
}


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


/* Turns a direction vector into rotation angles: out[0] from the pitch, out[1] the yaw, out[2] 0. */
void dir_to_angles_clamped(Vec3 *dir, SVECTOR *out) {
    s32 yaw;
    s32 pitch;

    angles_to_player(dir->x, dir->y, dir->z, &yaw, &pitch);
    out->vy = yaw;
    out->vx = -angle_clamp_pitch((s16)pitch);
    out->vz = 0;
}
