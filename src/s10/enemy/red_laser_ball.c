/* red_laser_ball: one of s10's own original source files (scripts/objmap.py); part of src/s10/main.c's unit, included there. */

extern s16 red_laser_ball_script[];
extern StateEntry red_laser_ball_states[1];
extern s16 *red_laser_ball_data[];
void red_laser_ball_phase0(Object *obj);
void red_laser_ball_update(Object *obj, ObjHandler *handler);
void time_bomb_draw(Object *obj, ObjHandler *handler);
s32 enemy_dying_step(Object *obj);
void obj_destroy_loop_sound(Object *obj);
s32 red_laser_ball_spawn(Placement *place) {
    Object *obj;
    s32 px;
    s32 py;
    s32 pz;
    s16 sound_id;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    obj->handlers[0].fn = red_laser_ball_phase0;
    obj->handlers[1].fn = red_laser_ball_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = time_bomb_draw;
    obj->callback = (s32)enemy_dying_step;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->destructor = obj_destroy_loop_sound;
    obj->kind = place->unk_04[1];
    obj->asset = &timer_tail_data;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = 0;
    obj->state_table = red_laser_ball_states;
    script_start((Script *)obj, red_laser_ball_script, (s32)&red_laser_ball_data);
    obj_init_from_place(obj, place, 0x174);
    obj->speed = 0;
    obj_set_part_bounds(obj, 1, 0x200);
    obj->placement->unk_02 = 0x708;
    px = obj->x;
    if (px < 0) {
        px += 0xFFF;
    }
    obj->vars.red_laser_ball.spawn_x = px >> 12;
    py = obj->y;
    if (py < 0) {
        py += 0xFFF;
    }
    obj->vars.red_laser_ball.spawn_y = py >> 12;
    pz = obj->z;
    if (pz < 0) {
        pz += 0xFFF;
    }
    obj->vars.red_laser_ball.spawn_z = pz >> 12;
    *(s16 *)&obj->vars.red_laser_ball.unk_268 = rand_a_next();
    obj->vars.enemy.target_yaw = 0;
    *(s16 *)obj->vars.enemy.unk_26E = 0;
    *(s16 *)&obj->vars.enemy.sound = 0;
    obj->vars.enemy.walk_state = 0;
    sound_id = sound_start(SND_RED_LASER_BALL_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
    ((s16 *)&obj->vars.enemy.sound)[1] = sound_id;
    sound_attach(sound_id & 0xFFFF, &obj->x, NULL);
    return 1;
}

/* Picks a new move target (vars.words[0..2]) once: near the player (within 0x600) a random point around the
 * player rotated by the view, else a random point around the home position (vars.words[4..6]); retried up to
 * 3 times while trace_world hits something, then clamped to 0x300 from the object.
 * Scratch v: [0..2] target, [4..6] object position, [8..10] player / home position (all >> 12). */
void enemy_pick_move_target(Object *obj) {
    s32 *m;
    s32 *v;
    s32 *src;
    s32 tries;
    s32 direct;
    s32 dx, dy, dz;
    s32 dist_cam;
    s32 dist_pos;

    tries = 0;
    if (*(s16 *)obj->vars.enemy.unk_26E == 0) {
        m = scratch_alloc(0x20);
        v = scratch_alloc(0x30);
        view_matrix_copy(m);
        v[4] = obj->x >> 12;
        v[5] = obj->y >> 12;
        v[6] = obj->z >> 12;
        player_position_copy((VECTOR *)&v[8]);
        src = (s32 *)&obj->vars.red_laser_ball.spawn_x;
        dist_cam = isqrt(length_sq(v[8] - v[4], v[9] - v[5], v[10] - v[6]));
        direct = 1;
        v[8] = obj->vars.red_laser_ball.spawn_x;
        v[9] = obj->vars.red_laser_ball.spawn_y;
        v[10] = obj->vars.red_laser_ball.spawn_z;
        dy = v[9] - v[5];
        dz = v[10] - v[6];
        dist_pos = isqrt(length_sq(v[8] - v[4], dy, dz));
        if (dist_cam < 0x600) {
            src = player_position();
            direct = 0;
        }
        if (dist_pos >= 0x7D1) {
            src = (s32 *)&obj->vars.red_laser_ball.spawn_x;
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
        obj->vars.red_laser_ball.target_x = v[0];
        obj->vars.red_laser_ball.target_y = v[1];
        obj->vars.red_laser_ball.target_z = v[2];
        scratch_top -= 0x50;
        *(s16 *)obj->vars.enemy.unk_26E = 1;
    }
}

void enemy_pick_move_target(Object *obj);
void red_laser_ball_phase0(Object *obj) {
    s32 r;

    obj->unk_1B7 = 0;
    obj->vars.enemy.target_yaw++;
    if (obj->vars.enemy.target_yaw >= 0x79) {
        r = rand_a_next();
        if (r == (r / 10) * 10) {
            enemy_pick_move_target(obj);
            obj->vars.enemy.target_yaw = 0;
        }
    }
}

extern SinCosHalves sincos_halves[] __asm__("rcossin_tbl");
void red_laser_ball_update(Object *obj, ObjHandler *handler) {
    s32 idx;
    s32 cos_v;
    s32 sin_v;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 *player;
    VECTOR pos;
    SVECTOR rot;
    s32 yaw;
    s32 pitch;
    s32 shot_yaw;
    s32 shot_pitch;

    if (obj->vars.laser.frozen == 0) {
        idx = obj->vars.laser.phase = (obj->vars.laser.phase + 0x20) & 0xFFF;
        cos_v = cos_table[idx].value;
        sin_v = (s16)sincos_halves[idx].sin;
        obj->x += cos_v / 4;
        obj->z += cos_v / 4;
        obj->y += sin_v / 2;
        if (obj->vars.laser.moving != 0) {
            dx = (obj->vars.laser.target[0] - obj->x) / 10;
            dy = (obj->vars.laser.target[1] - obj->y) / 10;
            dz = (obj->vars.laser.target[2] - obj->z) / 10;
            obj->x += dx;
            dx = __builtin_abs(dx);
            obj->y += dy;
            dy = __builtin_abs(dy);
            obj->z += dz;
            dz = __builtin_abs(dz);
            sound_set_pitch(obj->vars.laser.sound, ((dx + dy + dz) / 4096) * 32 + 0x1E00);
            dx = (obj->x - obj->vars.laser.target[0]) / 4096;
            dy = (obj->y - obj->vars.laser.target[1]) / 4096;
            dz = (obj->z - obj->vars.laser.target[2]) / 4096;
            if (isqrt(length_sq(dx, dy, dz)) < 16) {
                obj->vars.laser.moving = 0;
                obj->vars.laser.fired = 0;
                sound_set_pitch(obj->vars.laser.sound, 0x1E00);
            }
        }
        angles_to_player(obj->x >> 12, obj->y >> 12, obj->z >> 12, &yaw, &pitch);
        obj->yaw = angle_approach(obj->yaw, yaw, 0x40);
        obj->pitch = angle_approach(obj->pitch, pitch, 0x40);
        if (obj->vars.laser.moving == 0 && obj->vars.laser.fired == 0 &&
            (rand_a_next() & 0x1F) == 0) {
            SVECTOR unused; /* never used; the original frame has it */

            player = player_position();
            dx = obj->x / 4096 - player[0];
            dy = obj->y / 4096 - player[1];
            dz = obj->z / 4096 - player[2];
            if (isqrt(length_sq(dx, dy, dz)) < 0x600) {
                shot_pitch = -obj->pitch;
                rot.vx = shot_pitch;
                shot_yaw = obj->yaw;
                rot.vy = shot_yaw;
                rot.vz = obj->roll;
                angles_to_vector(shot_yaw, rot.vx, 0x20, &pos.vx, &pos.vy, &pos.vz);
                pos.vx = (pos.vx + obj->x) >> 12;
                pos.vy = (pos.vy + obj->y) >> 12;
                pos.vz = (pos.vz + obj->z) >> 12;
                sound_play_at_units(SND_SHOT_FIRE_ALT | SND_GROUP(1), 0x60, 0x3C, &pos);
                shot_spawn_obj(&pos.vx, (u16 *)&rot, 3, (obj->damage << 16) | 0x20);
                obj->vars.laser.fired = 1;
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


extern void spawn_effect_dup(s32, s32, s32, s32, s32, s32, s32) __asm__("spawn_effect");
s32 enemy_dying_step(Object *obj) {
    register s32 x asm("a0"); register s32 y asm("a1"); register s32 z asm("a2");

    if (obj->vars.enemy.walk_state != 0) {
        obj->vars.enemy.walk_state++;
        if (obj->vars.enemy.walk_state >= 0xC) {
            spawn_effect_dup(x, y, z, 0, x = obj->x >> 12, y = obj->y >> 12, z = obj->z >> 12);
            placement_list_pop((ListRecord *)obj->placement);
            obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
            return 0;
        }
        return 1;
    }
    spawn_effect_dup(x, y, z, 2, x = obj->x >> 12, y = obj->y >> 12, z = obj->z >> 12);
    obj->flags = 0x160;
    obj->unk_17A = 0;
    obj->vars.enemy.walk_state++;
    if (obj->vars.red_laser_ball.sound != 0) {
        sound_stop(obj->vars.red_laser_ball.sound);
        obj->vars.red_laser_ball.sound = 0;
    }
    return 1;
}
