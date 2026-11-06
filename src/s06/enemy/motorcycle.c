/* motorcycle: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

/* The stage's model and message files: data tables point to them by address. In the original they are their own object, after the engine's file_write_named. */
const char file_bic3_tp2_clt[] = "bic3_tp2.clt";
const char file_bic3_tp1_clt[] = "bic3_tp1.clt";
const char file_bic3_tp0_clt[] = "bic3_tp0.clt";
const char file_bic3_ch0_clt[] = "bic3_ch0.clt";
const char file_bic3_ch0_vx1[] = "bic3_ch0.vx1";
const char file_bic3_tp2_xs3[] = "bic3_tp2.xs3";
const char file_bic3_tp1_xs3[] = "bic3_tp1.xs3";
const char file_bic3_tp0_xs3[] = "bic3_tp0.xs3";
const char file_bic3_ch0_cb4[] = "bic3_ch0.cb4";
const char file_TNK1_tp0_clt[] = "TNK1_tp0.clt";
const char file_TNK1_ch0_clt[] = "TNK1_ch0.clt";
const char file_TNK1_ch0_vx1[] = "TNK1_ch0.vx1";
const char file_TNK1_tp0_xs3[] = "TNK1_tp0.xs3";
const char file_TNK1_ch0_cb4[] = "TNK1_ch0.cb4";
const char file_ohel_tp1_clt[] = "ohel_tp1.clt";
const char file_ohel_tp0_clt[] = "ohel_tp0.clt";
const char file_ohel_ch0_clt[] = "ohel_ch0.clt";
const char file_ohel_tp1_xs3[] = "ohel_tp1.xs3";
const char file_ohel_tp0_xs3[] = "ohel_tp0.xs3";
const char file_ohel_ch0_vx1[] = "ohel_ch0.vx1";
const char file_ohel_ch0_cb4[] = "ohel_ch0.cb4";

/* Mine dropped by a motorcycle: it arms once, homes in on the player when close, and
 * otherwise falls under gravity along its yaw until trace_world hits something. */
void motorcycle_mine_update(Object *obj) {
    s32 world_pos[4];
    s32 unused_pad[8]; /* the original frame reserves this space; keeps the layout identical */
    s32 trace_from[4];
    s32 trace_to[4];
    s32 trace_hit[4];
    s32 cam_dist;
    s16 angle;

    cam_dist = obj->vars.mine.cam_dist = isqrt(length_sq((cam_pos >> 12) - (obj->x >> 12),
                                                         (cam_pos_y >> 12) - (obj->y >> 12),
                                                         (cam_pos_z >> 12) - (obj->z >> 12)));

    world_pos[0] = obj->x >> 12;
    world_pos[1] = obj->y >> 12;
    world_pos[2] = obj->z >> 12;

    if (obj->vars.mine.sound_played == 0 && obj->unk_1B7 != 0) {
        sound_play_at(SND_MINE_ARM | SND_GROUP(2), 0x40, 0x3C, &obj->x);
        obj->vars.mine.sound_played = 1;
    }

    if (cam_dist >= 0xB4) {
        s32 *player = player_position();
        if (player[2] - (obj->z >> 12) < -0x400) {
            obj_free(obj);
            return;
        }
    } else {
        s32 *player;
        spawn_effect(world_pos[0], world_pos[1] - 0x80, world_pos[2], 0);
        player = player_position();
        angle = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
        hit_target_masked(0, 0x10, angle, obj->damage);
        obj_free(obj);
    }

    if (obj->speed != 0) {
        fly_move(obj->yaw, obj->speed >> 12, &obj->vz, &obj->vx);
        trace_from[0] = obj->x >> 12;
        trace_from[1] = obj->y >> 12;
        trace_from[2] = obj->z >> 12;
        obj->vy += 0x1000;
        obj->x += obj->vx;
        obj->z += obj->vz;
        obj->y += obj->vy;
        trace_to[0] = obj->x >> 12;
        trace_to[1] = obj->y >> 12;
        trace_to[2] = obj->z >> 12;
        trace_world(8, 1, trace_from, trace_to, trace_hit);
        if (obj->y == trace_hit[1]) {
            obj->speed--;
        }
        obj->x = trace_hit[0] << 12;
        obj->y = trace_hit[1] << 12;
        obj->z = trace_hit[2] << 12;
    }
}

void motorcycle_rocket_phase2(Object *obj);
void motorcycle_mine_draw(Object *obj);
void motorcycle_mine_spawn(Object *obj) {
    MineSpawn m;
    s32 rnd;
    s32 speed;
    s32 pitch;
    s32 yaw;
    s32 yaw2;
    s32 *ppx;
    s32 *player;
    s32 sound;
    u16 kind;
    u16 kind2;
    Object *mine;

    rnd = rand_a_next();
    if (rnd < 0xF00) {
        return;
    }
    player = player_position();
    if ((u32)(atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)) - 0x200) < 0xC01U) {
        return;
    }
    if (obj->vars.enemy.shot_timer >= 0x800) {
        return;
    }
    ppx = &m.px;
    m.px = 0x20;
    m.py = -0x50;
    m.pz = -0xC0;
    rotate_xz_twice(obj->yaw, -obj->pitch, ppx, &m.py, &m.pz);
    m.px = (m.px << 12) + obj->x;
    m.py = (m.py << 12) + obj->y;
    m.pz = (m.pz << 12) + obj->z;
    pitch = -obj->pitch;
    m.pitch = pitch;
    yaw = obj->yaw;
    m.yaw = yaw;
    m.roll = obj->roll;
    m.rnd = rnd;
    yaw -= 0x80;
    m.yaw = yaw + (rnd % 256);
    speed = obj->speed;
    speed += get_flow_max();
    speed <<= 12;
    speed += rnd;
    m.speed = speed;
    sound = model_slot_pchr(*(s32 *)obj->asset);
    kind = obj->damage;
    mine = obj_new();
    if (mine != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &mine->node);
        mine->handlers[2].fn = (void (*)(Object *, ObjHandler *))motorcycle_rocket_phase2;
        mine->handlers[1].fn = (void (*)(Object *, ObjHandler *))motorcycle_mine_update;
        mine->vars.snd.sound = sound;
        mine->damage = kind;
        mine->handlers[2].unk_11 = 0;
        mine->handlers[2].state = 0;
        mine->handlers[1].unk_11 = 0;
        mine->handlers[1].state = 0;
        mine->handlers[3].fn = (void (*)(Object *, ObjHandler *))motorcycle_mine_draw;
        mine->handlers[3].unk_11 = 0;
        mine->handlers[3].state = 0;
        obj_set_flags(mine, 0x80);
        mine->x = m.px;
        mine->y = m.py;
        mine->z = m.pz;
        mine->pitch = m.pitch;
        mine->yaw = m.yaw;
        mine->roll = m.roll;
        mine->roll = m.rnd;
        mine->health = 0x38;
        mine->speed = m.speed;
        mine->vars.turn.pad_250[0] = 0;
    }
    m.px = -0x20;
    m.py = -0x50;
    m.pz = -0xC0;
    rotate_xz_twice(obj->yaw, -obj->pitch, ppx, &m.py, &m.pz);
    m.px = (m.px << 12) + obj->x;
    m.py = (m.py << 12) + obj->y;
    m.pz = (m.pz << 12) + obj->z;
    rnd = rand_a_next();
    yaw2 = obj->yaw - 0x80;
    m.yaw = yaw2 + (rnd % 256);
    speed = obj->speed;
    speed += get_flow_max();
    speed <<= 12;
    speed += rnd;
    m.speed = speed;
    sound = model_slot_pchr(*(s32 *)obj->asset);
    kind2 = obj->damage;
    mine = obj_new();
    if (mine != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &mine->node);
        mine->handlers[2].fn = (void (*)(Object *, ObjHandler *))motorcycle_rocket_phase2;
        mine->handlers[1].fn = (void (*)(Object *, ObjHandler *))motorcycle_mine_update;
        mine->vars.snd.sound = sound;
        mine->damage = kind2;
        mine->handlers[2].unk_11 = 0;
        mine->handlers[2].state = 0;
        mine->handlers[1].unk_11 = 0;
        mine->handlers[1].state = 0;
        mine->handlers[3].fn = (void (*)(Object *, ObjHandler *))motorcycle_mine_draw;
        mine->handlers[3].unk_11 = 0;
        mine->handlers[3].state = 0;
        obj_set_flags(mine, 0x80);
        mine->x = m.px;
        mine->y = m.py;
        mine->z = m.pz;
        mine->pitch = m.pitch;
        mine->yaw = m.yaw;
        mine->roll = m.roll;
        mine->roll = m.rnd;
        mine->health = 0x38;
        mine->speed = m.speed;
        mine->vars.turn.pad_250[0] = 0;
    }
}

/* Stores the distance from the object to the player in words[0xD] (0x27C, the enemy shot_timer slot),
   with the object's position taken in 1/4096 units. */
void obj_dist_to_player(Object *obj) {
    s32 *player;

    player = player_position();
    obj->vars.words[0xD] = SquareRoot0(length_sq(player[0] - (obj->x >> 12),
                                                 player[1] - (obj->y >> 12),
                                                 player[2] - (obj->z >> 12)));
}

s32 flier_chase_player(s16 *ang, s32 *pos, s32 *vec, s32 speed, s32 range);
void flier_strafe_to_cam_angle(Object *obj, s32 strafe_speed);
void flier_strafe_to_limit(Object *obj, s32 speed);

static inline s32 flier_probe_floor(Object *obj, s32 offset) {
    VECTOR from;
    VECTOR to;
    VECTOR hit;
    s32 dz, dx;
    s32 grounded;
    s16 flags;

    fly_move(obj->yaw, offset, &dz, &dx);
    to.vx = obj->x >> 12;
    to.vy = obj->y >> 12;
    to.vz = obj->z >> 12;
    to.vx += dx >> 12;
    from.vx = to.vx;
    from.vy = to.vy;
    to.vz += dz >> 12;
    from.vz = to.vz;
    from.vy = to.vy - (s16)obj->height;
    to.vy = to.vy + ((s16)obj->height >> 1);
    trace_world(0x12, 4, &from, &to, &hit);
    grounded = obj->vars.flier.grounded;
    if (to.vy == hit.vy) {
        flags = grounded | 1;
    } else {
        flags = grounded;
    }
    obj->vars.flier.grounded = flags;
    return hit.vy;
}

/* Like motorcycle_update, but first drops the chase when the player is
 * more than 0x80 behind on z. */
void flier_flow_update(Object *obj, ObjHandler *handler) {
    s32 move[4];
    s32 y, slope_angle;
    s32 *player;
    s32 recoil, from_angle, roll;

    obj->vy = 0;
    obj->accel_y = 0;
    obj_dist_to_player(obj);
    if (player_position()[2] - (obj->z >> 12) < -0x80) {
        obj->vars.flier.chase_timer = 0;
    }
    obj->vars.flier.flow.speed = get_flow_max();
    flow_sample(&obj->vars.flier.flow, obj->width, &obj->x, move, &obj->turn);
    obj->vx = move[0];
    obj->vz = move[2];
    obj->yaw = obj->vars.flier.flow.angle;
    if (obj->vars.flier.chase_timer <= 0) {
        player = player_position();
        if (((atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)) + 0x400) & 0xFFF) < 0x800) {
            obj->speed = 0x10;
        } else {
            obj->speed = -0x10;
        }
    } else {
        flier_chase_player(&obj->vars.flier.flow.state, &obj->x, &obj->vx, 8, 0x400);
        obj->vars.flier.chase_timer--;
    }
    if (obj->hit_cooldown != 0) {
        register s32 cooldown asm("$2") = obj->hit_cooldown;
        recoil = cooldown / 6;
        fly_move(obj->hit_from, 8, &move[0], &move[1]);
        obj->vx += move[1];
        from_angle = obj->hit_from;
        obj->vz += move[0];
        from_angle &= 0xFFF;
        if (from_angle >= 0) {
            if (from_angle < 0x400) {
                recoil = -recoil;
            } else if (from_angle < 0xC00) {
                if (from_angle >= 0x800) {
                    recoil = -recoil;
                }
            }
        }
        obj->roll += recoil;
    }
    if (obj->vars.flier.grounded == 0) {
        if (obj->vars.flier.chase_timer > 0) {
            flier_strafe_to_cam_angle(obj, 8);
        } else {
            flier_strafe_to_limit(obj, -8);
        }
    }
    fly_strafe(obj->yaw, obj->speed, &obj->vz, &obj->vx);
    limit_move(&obj->x, &obj->vx);
    obj_script_step(obj, handler);
    obj->vars.flier.grounded = 0;

    obj->vars.flier.floor_y[0] = flier_probe_floor(obj, obj->unk_1E8[0]);
    obj->vars.flier.floor_y[1] = flier_probe_floor(obj, -obj->unk_1E8[0]);
    obj->vars.flier.floor_slope = obj->vars.flier.floor_y[0] - obj->vars.flier.floor_y[1];

    slope_angle = atan2(obj->unk_1E8[0] * 8, obj->vars.flier.floor_slope * 4);
    y = obj->vars.flier.floor_y[0] + obj->vars.flier.floor_y[1];
    y <<= 11;
    if (obj->y < y) {
        if (y - obj->y > 0x8000) {
            y = obj->y + 0x8000;
            slope_angle += 2;
        }
        slope_angle += 2;
    }
    obj->move_delta[1] = y - obj->y;
    obj->y = y;
    if (obj->vars.flier.grounded != 0) {
        angle_approach(obj->pitch, 0x200, 8);
    } else {
        if (obj->vars.flier.floor_slope > 0) {
            obj->pitch = angle_approach(obj->pitch, -slope_angle, 2);
        } else {
            obj->pitch = angle_approach(obj->pitch, slope_angle, 4);
        }
    }
    roll = obj->turn << 5;
    roll = MAX(roll <= 0x200 ? roll : 0x200, -0x200);
    obj->roll = angle_approach(obj->roll, roll, 8);
    obj->vars.flier.rotor = (obj->vars.flier.rotor - 0x40) & 0xFFF;
}


extern ModelPartList model_part_lists[];
s32 motorcycle_pose_build(Object *obj, s32 model)
{
    SVECTOR pos;
    SVECTOR rot;
    s32 y;
    s32 z1;
    s32 z2;
    s32 part1;
    s32 part2;
    s32 *first;
    s16 posY;
    SVECTOR *posp;
    SVECTOR *rotp;

    if (obj->vars.h.unk_248 != 0) {
        part1 = 4;
        part2 = 3;
        y = -0x26;
        z1 = 0x96;
        z2 = -0x82;
    } else {
        part1 = 0xE;
        part2 = 0;
        y = -0x1F;
        z1 = -0x54;
        z2 = 0x5E;
    }
    y = y * 0x1333 / 4096;
    z1 = z1 * 0x1333 / 4096;
    z2 = z2 * 0x1333 / 4096;
    model = pchr_copy_slot(model);
    first = pchr_poses_build(model);
    posY = y; /* s16 copy: an s2=s2 move that sched2 schedules before jump2 drops it */
    posp = &pos;
    model_part_lists[model & 0x7FF].first = first;
    rot.vx = obj->vars.h.unk_252;
    pos.vz = z1;
    rotp = &rot;
    rot.vy = 0;
    rot.vz = 0;
    pos.vx = 0;
    pos.vy = posY;
    pose_rotate_range(first, part1, 1, posp, rotp);
    pos.vx = 0;
    pos.vy = posY;
    pos.vz = z2;
    pose_rotate_range(first, part2, 1, posp, rotp);
    return model;
}

/* Draws the motorcycle as a spark record (model +3 in its variant, +1 when far, tinted while hit, shaken
   sideways during the hit cooldown), then its rider marker beside it, facing away from the player and
   rolled when leaning hard; a hit flag is set to -1 once drawn. */
void motorcycle_draw(Object *obj) {
    s32 pos[4];
    s16 rot[4];
    s16 aim[4];
    s32 dz, dx;
    s32 model;
    s32 colour;
    s32 *player;
    s32 lean;
    s32 pitch;
    SVECTOR *aimp;
    Vec3 *posp;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    colour = 0;
    model = model_slot_pchr(*(s32 *)obj->asset);
    if (obj->vars.motorcycle.variant != 0) {
        model += 3;
    }
    if (obj->vars.words[0xD] > 0x800) {
        model++;
    }
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    }
    if (obj->hit_cooldown != 0) {
        s32 shake = obj->hit_cooldown * 8;
        s32 from = obj->hit_from;
        s32 a = from & 0xFFF;
        if (a >= 0) {
            if (a < 0x400) {
                shake = -shake;
            } else if (a < 0xC00) {
                if (a >= 0x800) {
                    shake = -shake;
                }
            }
        }
        rot[1] += shake;
    }
    spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], model, colour);
    pos[0] = obj->x;
    pos[1] = obj->y - 0x20000;
    pos[2] = obj->z;
    aim[0] = obj->width + 0x20;
    aim[1] = obj->height;
    aim[2] = obj->unk_1E8[0] + 0x20;
    posp = (Vec3 *)pos;
    aimp = (SVECTOR *)aim;
    player = player_position();
    fly_move(atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)) + 0x800, 8, &dz, &dx);
    rot[2] = 0;
    pos[0] += dx;
    pos[2] += dz;
    lean = obj->vars.words[0xC];
    if (lean > 0) {
        rot[0] = -rot[0];
    }
    if (ABS(obj->vars.words[0xC]) > 0x14) {
        aim_marker_draw(2, aimp, posp, (SVECTOR *)rot);
    } else {
        aim_marker_draw(2, aimp, posp, 0);
    }
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

s32 motorcycle_crash_update(Object *obj) {
    s32 pos[4];
    s32 from[4];
    s32 to[4];
    s32 hit[4];
    s32 dx;
    s32 dz;
    s32 half;
    s32 y;
    s32 prev_y;
    s32 right;
    s32 yaw;
    s32 r;
    s16 spread;
    s32 extent; /* the same value as spread, kept apart for the matching addu */
    s16 flags;
    s32 old;

    switch (((CrashVars *)&obj->vars)->timer) {
    case -2:
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->unk_17A = 0;
        ((CrashVars *)&obj->vars)->timer = 90;
        ((CrashVars *)&obj->vars)->heading = obj->yaw;
        if (rand_a_next() < 0x800) {
            ((CrashVars *)&obj->vars)->roll_target = 1000;
        } else {
            ((CrashVars *)&obj->vars)->roll_target = -1000;
        }
        if (rand_a_next() < 0x800) {
            ((CrashVars *)&obj->vars)->yaw_rate = 0x30;
        } else {
            ((CrashVars *)&obj->vars)->yaw_rate = -0x30;
        }
        obj->speed = get_flow_max();
        return 1;
    case -1:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        particle_spawn_burst(pos[0], pos[1], pos[2], 0);
        obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
        return 0;
    }
    if (((CrashVars *)&obj->vars)->timer < 45) {
        obj->speed = obj->speed * 7 >> 3;
    } else {
        ((CrashVars *)&obj->vars)->ground_flags = 0;
        fly_move(obj->yaw, obj->unk_1E8[0], &dx, &dz);
        to[0] = obj->x >> 12;
        to[1] = obj->y >> 12;
        to[2] = obj->z >> 12;
        to[0] += dz >> 12;
        from[0] = to[0];
        from[1] = to[1];
        to[2] += dx >> 12;
        from[2] = to[2];
        from[1] = to[1] - (s16)obj->height;
        to[1] += (s16)obj->height >> 1;
        trace_world(0x12, 4, from, to, hit);
        old = ((CrashVars *)&obj->vars)->ground_flags;
        if (to[1] == hit[1]) {
            flags = old | 1;
        } else {
            flags = old;
        }
        ((CrashVars *)&obj->vars)->ground_flags = flags;
        ((CrashVars *)&obj->vars)->ground_left = hit[1];
        fly_move(obj->yaw, -obj->unk_1E8[0], &dx, &dz);
        to[0] = obj->x >> 12;
        to[1] = obj->y >> 12;
        to[2] = obj->z >> 12;
        to[0] += dz >> 12;
        from[0] = to[0];
        from[1] = to[1];
        to[2] += dx >> 12;
        from[2] = to[2];
        from[1] = to[1] - (s16)obj->height;
        to[1] += (s16)obj->height >> 1;
        trace_world(0x12, 4, from, to, hit);
        old = ((CrashVars *)&obj->vars)->ground_flags;
        if (to[1] == hit[1]) {
            flags = old | 1;
        } else {
            flags = old;
        }
        ((CrashVars *)&obj->vars)->ground_flags = flags;
        right = hit[1];
        ((CrashVars *)&obj->vars)->ground_right = right;
        ((CrashVars *)&obj->vars)->ground_diff = ((CrashVars *)&obj->vars)->ground_left - right;
        atan2(obj->unk_1E8[0] * 8, ((CrashVars *)&obj->vars)->ground_diff * 4);
        half = ((CrashVars *)&obj->vars)->ground_left + ((CrashVars *)&obj->vars)->ground_right;
        half <<= 11;
        y = obj->y;
        if (y < half && half - y > 0x8000) {
            half = y + 0x8000;
        }
        prev_y = obj->y;
        obj->y = half;
        obj->move_delta[1] = half - prev_y;
    }
    yaw = obj->yaw;
    obj->yaw = yaw + ((CrashVars *)&obj->vars)->yaw_rate;
    obj->roll = angle_approach(obj->roll, ((CrashVars *)&obj->vars)->roll_target, 12);
    fly_move(((CrashVars *)&obj->vars)->heading, obj->speed, &obj->vz, &obj->vx);
    if (((CrashVars *)&obj->vars)->timer % 20 == 0) {
        from[0] = obj->x >> 12;
        from[1] = obj->y >> 12;
        from[2] = obj->z >> 12;
        r = rand_a_next();
        extent = obj->width;
        spread = extent;
        from[0] += r * (spread + extent) / 4096 - spread;
        from[1] -= (s16)obj->height;
        r = rand_a_next();
        extent = obj->unk_1E8[0];
        spread = extent;
        from[2] += r * (spread + extent) / 4096 - spread;
        spawn_effect(from[0], from[1], from[2], 0);
    }
    ((CrashVars *)&obj->vars)->timer--;
    return 1;
}


/* Turn the object's yaw toward the player and return its pitch to level. */
void obj_turn_yaw_to_player(Object *obj, s32 step) {
    VECTOR *player = (VECTOR *)player_position();

    obj->yaw = angle_approach(obj->yaw, atan2(player->vz - (obj->z >> 12), player->vx - (obj->x >> 12)), step);
    obj->pitch = angle_approach(obj->pitch, 0, step * 4);
}


void motorcycle_rocket_update(Object *obj) {
    Vec3 at;
    Vec3 from;
    Vec3 to;
    Vec3 hit;
    s32 roll;
    s32 dist;
    s32 dz;

    obj->vars.rocket.cam_dist = isqrt(length_sq((cam_pos >> 12) - (obj->x >> 12),
                                                (cam_pos_y >> 12) - (obj->y >> 12),
                                                (cam_pos_z >> 12) - (obj->z >> 12)));
    dist = obj->vars.rocket.cam_dist;
    switch (obj->vars.rocket.age++) {
    case 0 ... 0x17:
        obj_turn_yaw_to_player(obj, 4);
        break;
    case 0x18 ... 0x29:
        obj->vars.rocket.roll_step = 8;
        obj->vars.rocket.flags |= 1;
        break;
    case 0x2A ... 0x3F:
        obj->accel_y = obj->accel_y * 7 >> 3;
        obj->vy = obj->vy * 7 >> 3;
        obj_turn_yaw_to_player(obj, 0x10);
        obj->vars.rocket.roll_step = 0xC;
        obj->vars.rocket.flags |= 2;
        break;
    case 0x40 ... 0x5F:
        obj->vars.rocket.roll_step = 0x20;
        break;
    case 0x60 ... 0x78:
        break;
    default:
        obj_free(obj);
        break;
    }
    roll = obj->roll;
    obj->roll = roll + obj->vars.rocket.roll_step;
    if (dist >= 0xB4) {
        dz = player_position()[2] - (obj->z >> 12);
        if (ABS(dz) >= 0x801) {
            obj_free(obj);
            return;
        }
    } else {
        s32 *p;
        at.x = obj->x >> 12;
        at.y = obj->y >> 12;
        at.z = obj->z >> 12;
        spawn_effect(at.x, at.y - 0x80, at.z, 0);
        p = player_position();
        hit_target_masked(0, 0x10, atan2(p[2] - (obj->z >> 12), p[0] - (obj->x >> 12)), obj->damage);
        obj_free(obj);
    }
    fly_move(obj->yaw, obj->vars.rocket.roll_step, &obj->vz, &obj->vx);
    if (obj->speed != 0) {
        fly_strafe(obj->vars.rocket.strafe_angle, obj->speed, &obj->vz, &obj->vx);
        from.x = obj->x >> 12;
        from.y = obj->y >> 12;
        from.z = obj->z >> 12;
        obj->vy += obj->accel_y;
        obj->x += obj->vx;
        obj->z += obj->vz;
        obj->y += obj->vy;
        to.x = obj->x >> 12;
        to.y = obj->y >> 12;
        to.z = obj->z >> 12;
        if (trace_world(8, 1, &from, &to, &hit)) {
            obj->speed = obj->speed * 7 >> 3;
        }
        obj->x = hit.x << 12;
        obj->y = hit.y << 12;
        obj->z = hit.z << 12;
    }
}

static inline void add_spark(s32 x, s32 y, s32 z, u16 rot_x, u16 rot_y, u16 rot_z, s16 value) {
    SparkList *list = &spark_list;
    SparkRec *rec;
    u8 *tail;
    s32 n;

    n = SPARK_COUNT;
    if (n < 0xFF) {
        rec = &list->items[n];
        n++;
        SPARK_COUNT = n;
        *(s32 *)rec->colour = 0;
        tail = spark_list_tail;
        spark_list_tail = &rec->next;
        *tail = n;
        rec->next = 0;
        rec->x = x;
        rec->y = y;
        rec->z = z;
        rec->unk_12 = value;
        rec->yaw = rot_x;
        rec->pitch = rot_y;
        rec->roll = rot_z;
    }
}
/* Spawns the rocket exhaust sparks: one at the object, plus one per exhaust port
   (vars.words[3..5] and [6..8]) whose flag is set in words[9]. */
void motorcycle_rocket_draw(Object *obj) {
    /* pinned to a1: the original keeps the spark value there after the rotate call */
    register s16 value asm("$5");
    s32 index = obj->vars.enemy_fire_rocket_obj.spark_index;

    add_spark(obj->x >> 12, obj->y >> 12, obj->z >> 12, obj->yaw, obj->pitch, obj->roll, index++);

    if (obj->vars.enemy_fire_rocket_obj.unk_26C & 1) {
        obj->vars.enemy_fire_rocket_obj.spark_a_x = 0;
        obj->vars.enemy_fire_rocket_obj.spark_a_y = 0;
        obj->vars.enemy_fire_rocket_obj.spark_a_z = 0x20;
        rotate_xz_twice(obj->yaw + 0x800, -obj->pitch, &obj->vars.enemy_fire_rocket_obj.spark_a_x, &obj->vars.enemy_fire_rocket_obj.spark_a_y, &obj->vars.enemy_fire_rocket_obj.spark_a_z);
        obj->vars.enemy_fire_rocket_obj.spark_a_x = (obj->vars.enemy_fire_rocket_obj.spark_a_x << 12) + obj->x;
        obj->vars.enemy_fire_rocket_obj.spark_a_y = (obj->vars.enemy_fire_rocket_obj.spark_a_y << 12) + obj->y;
        obj->vars.enemy_fire_rocket_obj.spark_a_z = (obj->vars.enemy_fire_rocket_obj.spark_a_z << 12) + obj->z;
        value = index++;
        value |= 0x2000;
        add_spark(obj->vars.enemy_fire_rocket_obj.spark_a_x >> 12, obj->vars.enemy_fire_rocket_obj.spark_a_y >> 12, obj->vars.enemy_fire_rocket_obj.spark_a_z >> 12, 0x800, 0, 0, value);
    }
    if (obj->vars.enemy_fire_rocket_obj.unk_26C & 2) {
        obj->vars.enemy_fire_rocket_obj.spark_b_x = 0;
        obj->vars.enemy_fire_rocket_obj.spark_b_y = 0;
        obj->vars.enemy_fire_rocket_obj.spark_b_z = 0x40;
        rotate_xz_twice(obj->yaw + 0x800, -obj->pitch, &obj->vars.enemy_fire_rocket_obj.spark_b_x, &obj->vars.enemy_fire_rocket_obj.spark_b_y, &obj->vars.enemy_fire_rocket_obj.spark_b_z);
        obj->vars.enemy_fire_rocket_obj.spark_b_x = (obj->vars.enemy_fire_rocket_obj.spark_b_x << 12) + obj->x;
        obj->vars.enemy_fire_rocket_obj.spark_b_y = (obj->vars.enemy_fire_rocket_obj.spark_b_y << 12) + obj->y;
        obj->vars.enemy_fire_rocket_obj.spark_b_z = (obj->vars.enemy_fire_rocket_obj.spark_b_z << 12) + obj->z;
        value = index;
        value |= 0x2000;
        add_spark(obj->vars.enemy_fire_rocket_obj.spark_b_x >> 12, obj->vars.enemy_fire_rocket_obj.spark_b_y >> 12, obj->vars.enemy_fire_rocket_obj.spark_b_z >> 12, 0x800, 0, 0, index | 0x2000);
    }
}

void motorcycle_rocket_phase2(Object *obj);
extern void motorcycle_rocket_update(Object *obj);
void enemy_fire_rocket(Object *obj) {
    s32 pos[4];
    s32 *pp;
    s32 pitch;
    s32 speed;
    
    s16 rot[3];
    u16 mask;
    s32 model;
    Object *rocket;
    s32 *player;

    if (ABS(obj->vars.enemy.shot_timer) < 0x801) {
        if ((s16) obj->vars.h.unk_24E > 0) {
            obj->vars.h.unk_24E--;
            return;
        }
        if (obj->vars.enemy_fire_rocket_obj.burst_count <= 0) {
            obj->vars.enemy_fire_rocket_obj.burst_count = rand_a_next() & 7;
            obj->vars.h.unk_24C = 0;
        }
        if (obj->vars.h.unk_24C > 0) {
            obj->vars.h.unk_24C--;
            return;
        }
        obj->vars.enemy_fire_rocket_obj.burst_count--;
        if (obj->vars.enemy_fire_rocket_obj.burst_count <= 0) {
            obj->vars.h.unk_24E = rand_a_next() & 0x5F;
        }
        obj->vars.h.unk_24C = rand_a_next() & 5;
        pos[0] = 0;
        pos[1] = -0xA0;
        pos[2] = 0xA8 - obj->vars.enemy_fire_rocket_obj.unk_26C;
        obj->vars.enemy_fire_rocket_obj.unk_26C += 8;
        if (obj->vars.enemy_fire_rocket_obj.unk_26C > 0x40) {
            obj->vars.enemy_fire_rocket_obj.unk_26C = 0;
        }
        pp = pos;
        rotate_xz_twice(obj->yaw, -obj->pitch, pp, &pos[1], &pos[2]);
        pos[0] = (pos[0] << 12) + obj->x;
        pos[1] = (pos[1] << 12) + obj->y;
        pos[2] = (pos[2] << 12) + obj->z;
        pitch = obj->pitch;
        rot[0] = -pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        pos[3] = get_flow_max();
        model = model_slot_pchr(*(s32 *)obj->asset);
        mask = obj->damage;
        rocket = obj_new();
        if (rocket != NULL) {
            list_insert_after((Node *) get_obj_list_actors(), &rocket->node);
            rocket->vars.snd.sound = model + 7;
            rocket->handlers[2].fn = (void (*)(Object *, ObjHandler *))motorcycle_rocket_phase2;
            rocket->handlers[1].fn = (void (*)(Object *, ObjHandler *))motorcycle_rocket_update;
            rocket->damage = mask;
            rocket->handlers[2].unk_11 = 0;
            rocket->handlers[2].state = 0;
            rocket->handlers[1].unk_11 = 0;
            rocket->handlers[1].state = 0;
            rocket->handlers[3].fn = (void (*)(Object *, ObjHandler *))motorcycle_rocket_draw;
            rocket->handlers[3].unk_11 = 0;
            rocket->handlers[3].state = 0;
            obj_set_flags(rocket, 0x80);
            rocket->x = pos[0];
            rocket->y = pos[1];
            rocket->z = pos[2];
            rocket->vy = 0xFFFF6000 - rand_a_next() * 2;
            rocket->accel_y = 0x800;
            rocket->pitch = rot[0];
            rocket->yaw = rot[1];
            rocket->roll = rot[2];
            rocket->vars.enemy.sound = rocket->yaw;
            rocket->pitch = 0x400;
            player = player_position();
            rocket->yaw = atan2(player[2] - (rocket->z >> 12), player[0] - (rocket->x >> 12));
            rocket->roll = 0;
            speed = pos[3];
            rocket->vars.enemy.unk_250 = 0;
            rocket->speed = speed;
        }
        sound_play_at(SND_ENEMY_ROCKET_LAUNCH | SND_GROUP(1), 0x60, 0x3C, pp);
        if (obj->vars.enemy_fire_rocket_obj.unk_250 <= 0) {
            obj->next_state = 0;
        }
    }
}

void motorcycle_mine_spawn(Object *obj);
void motorcycle_fire_check(Object *obj) {
    if (obj->vars.enemy.shot_timer < 0x800) {
        motorcycle_mine_spawn(obj);
    }
    if (obj->vars.motorcycle.unk_250 <= 0) {
        obj->next_state = 0;
    }
}

/* Turns a flier towards pos within range (or stops it), then strafes it. Returns the signed speed. */
s32 flier_chase_player(s16 *ang, s32 *pos, s32 *vec, s32 speed, s32 range) {
    s32 dir = speed;
    s32 dz = (cam_pos_z - pos[2]) >> 12;
    s32 dx = (cam_pos - pos[0]) >> 12;
    s32 dist;

    if (((((atan2(dz, dx) - ang[2]) & 0xFFF) - 0x400) & 0xFFF) < 0x800) {
        dir = -dir;
    }
    dist = isqrt(length_sq(dx, 0, dz));
    if (dist < range - 0x40) {
        dir = -dir;
    } else if (dist < range) {
        return 0;
    }
    fly_strafe(ang[2], dir, vec + 2, vec);
    return dir;
}

/* Strafes the object sideways when its aim angle (0x282) is at least 0x100 away from the camera angle. */
void flier_strafe_to_cam_angle(Object *obj, s32 strafe_speed) {
    s16 *aim;
    s32 aim_angle;
    s32 cam_angle;
    s32 diff;

    aim = &obj->vars.motorcycle.unk_280;
    /* stage_decls declares cam_angle_get as s16; the original uses the full s32 return */
    cam_angle = ((GetAngleFn)cam_angle_get)();
    aim_angle = aim[1];
    diff = aim_angle - cam_angle;
    if (diff >= 0) {
        if (diff < 0x100) {
            return;
        }
    } else {
        if (cam_angle - aim_angle < 0x100) {
            return;
        }
    }
    if (cam_angle < aim_angle) {
        strafe_speed = -strafe_speed;
    }
    fly_strafe(aim[2] + 0x400, strafe_speed, &obj->vz, &obj->vx);
}

void flier_strafe_to_limit(Object *obj, s32 speed) {
    s32 angle;

    angle = speed;
    if (((s32 (*)(void))cam_angle_get)() < ((s16 *)obj->vars.words)[0x1D]) {
        angle = -angle;
    }
    fly_strafe(((s16 *)obj->vars.words)[0x1E] + 0x400, angle, &obj->vz, &obj->vx);
}

/* Flies along its flow, chases or circles the player, recoils from hits,
 * then probes the floor ahead and behind to set its height and pitch. */
void motorcycle_update(Object *obj, ObjHandler *handler) {
    s32 move[4];
    s32 y, slope_angle;
    s32 *player;
    s32 recoil, from_angle, roll;

    obj->vy = 0;
    obj->accel_y = 0;
    obj_dist_to_player(obj);
    obj->vars.flier.flow.speed = get_flow_max();
    flow_sample(&obj->vars.flier.flow, obj->width, &obj->x, move, &obj->turn);
    obj->vx = move[0];
    obj->vz = move[2];
    obj->yaw = obj->vars.flier.flow.angle;
    if (obj->vars.flier.chase_timer <= 0) {
        player = player_position();
        if (((atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)) + 0x400) & 0xFFF) < 0x800) {
            obj->speed = 0x10;
        } else {
            obj->speed = -0x10;
        }
    } else {
        flier_chase_player(&obj->vars.flier.flow.state, &obj->x, &obj->vx, 8, 0x400);
        obj->vars.flier.chase_timer--;
    }
    if (obj->hit_cooldown != 0) {
        register s32 cooldown asm("$2") = obj->hit_cooldown;
        recoil = cooldown / 6;
        fly_move(obj->hit_from, 8, &move[0], &move[1]);
        obj->vx += move[1];
        from_angle = obj->hit_from;
        obj->vz += move[0];
        from_angle &= 0xFFF;
        if (from_angle >= 0) {
            if (from_angle < 0x400) {
                recoil = -recoil;
            } else if (from_angle < 0xC00) {
                if (from_angle >= 0x800) {
                    recoil = -recoil;
                }
            }
        }
        obj->roll += recoil;
    }
    if (obj->vars.flier.grounded == 0) {
        if (obj->vars.flier.chase_timer > 0) {
            flier_strafe_to_cam_angle(obj, 8);
        } else {
            flier_strafe_to_limit(obj, -8);
        }
    }
    fly_strafe(obj->yaw, obj->speed, &obj->vz, &obj->vx);
    limit_move(&obj->x, &obj->vx);
    obj_script_step(obj, handler);
    obj->vars.flier.grounded = 0;

    obj->vars.flier.floor_y[0] = flier_probe_floor(obj, obj->unk_1E8[0]);
    obj->vars.flier.floor_y[1] = flier_probe_floor(obj, -obj->unk_1E8[0]);
    obj->vars.flier.floor_slope = obj->vars.flier.floor_y[0] - obj->vars.flier.floor_y[1];

    slope_angle = atan2(obj->unk_1E8[0] * 8, obj->vars.flier.floor_slope * 4);
    y = obj->vars.flier.floor_y[0] + obj->vars.flier.floor_y[1];
    y <<= 11;
    if (obj->y < y) {
        if (y - obj->y > 0x8000) {
            y = obj->y + 0x8000;
            slope_angle += 2;
        }
        slope_angle += 2;
    }
    obj->move_delta[1] = y - obj->y;
    obj->y = y;
    if (obj->vars.flier.grounded != 0) {
        angle_approach(obj->pitch, 0x200, 8);
    } else {
        if (obj->vars.flier.floor_slope > 0) {
            obj->pitch = angle_approach(obj->pitch, -slope_angle, 2);
        } else {
            obj->pitch = angle_approach(obj->pitch, slope_angle, 4);
        }
    }
    roll = obj->turn << 5;
    roll = MAX(roll <= 0x200 ? roll : 0x200, -0x200);
    obj->roll = angle_approach(obj->roll, roll, 8);
    obj->vars.flier.rotor = (obj->vars.flier.rotor - 0x40) & 0xFFF;
}

/* Stops the sound handle at 0x268. */
void obj_stop_sound(Object *obj) {
    sound_stop(obj->vars.motorcycle.sound_handle);
}

extern s16 *motorcycle_data;
extern StateEntry D_8011C71C[];
extern char motorcycle_asset[];
s32 motorcycle_crash_update(Object *obj);
void motorcycle_update(Object *obj, ObjHandler *handler);
void flier_flow_update(Object *obj, ObjHandler *handler);
s32 motorcycle_spawn(Placement *place) {
    Object *obj;
    s32 sound;
    s32 id;
    s32 state;
    s16 **script;
    s32 kind;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), &obj->node);
    place->unk_02 = 0x708;
    obj->handlers[2].fn = obj_state_run_b;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *))motorcycle_draw;
    obj->callback = (s32)&motorcycle_crash_update;
    obj->destructor = obj_stop_sound;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->vars.enemy.sound_channel[1] = 0;
    obj->vars.motorcycle.unused_252 = 0;
    obj->vars.motorcycle.unused_24C = 0;
    obj->vars.motorcycle.unused_24E = 0;
    obj->vars.words[0xA] = 0;
    obj->vars.enemy.sound_channel[0] = -2;
    obj->vars.motorcycle.unk_250 = place->range;
    obj->vars.motorcycle.variant = *(u16 *)&place->unk_1A >> 8;
    script = &motorcycle_data;
    kind = place->unk_04[1];
    obj->asset = motorcycle_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = 4;
    obj->state_table = D_8011C71C;
    obj->kind = kind;
    script_start((Script *)obj, *script, (s32)script);
    obj_init_from_place(obj, place, 0x124);
    obj_set_part_bounds(obj, 0, 0x1333);
    obj->accel_y = 0x1000;
    if (obj->vars.motorcycle.variant != 0) {
        id = SND_MOTORCYCLE_ENGINE_LOOP | SND_HELD | SND_GROUP(2);
        obj->handlers[1].fn = motorcycle_update;
        state = 1;
    } else {
        id = SND_FLIER_ENGINE_LOOP | SND_HELD | SND_GROUP(2);
        obj->handlers[1].fn = flier_flow_update;
        state = 2;
    }
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    do {
    } while (0);
    obj->next_state = state;
    rec_reset((PartSlot *)&obj->vars.words[0xE]);
    sound = sound_start(id, 0x40, 0, 0);
    sound_attach(sound, &obj->x, NULL);
    sound_set_flag_bit2(sound, 1);
    do {
    } while (0);
    obj->vars.motorcycle.sound_handle = sound;
    return 1;
}

void motorcycle_rocket_phase2(Object *obj) {
    if ((obj_hit_damage(obj->index) << 0x10) != 0) {
        obj_free(obj);
    }
}

/* Adds two sparks at the object's position (shifted down 12 bits), one per colour: 0 and 0xFF0000. */
void motorcycle_mine_draw(Object *obj) {
    spark_add(obj->x >> 12, obj->y >> 12, obj->z >> 12, 0, 0x800, (u16)obj->roll,
              (obj->vars.snd.sound + 6) | 0x2000, 0);
    spark_add(obj->x >> 12, obj->y >> 12, obj->z >> 12, 0x800, 0, (u16)obj->roll,
              (obj->vars.snd.sound + 8) | 0x2000, 0xFF0000);
}



/* Stops the two sound effects an object may have playing (sound handles are bytes at 0x27C and 0x27D).
 * Proposed stage.h fields: Object u8 sound_a @0x27C, sound_b @0x27D (not in stage.h yet). */
void obj_stop_sound_slots(Object *obj) {
    if (((u8 *)obj)[0x27C] != 0) {
        sound_stop(((u8 *)obj)[0x27C]);
        ((u8 *)obj)[0x27C] = 0;
    }
    if (((u8 *)obj)[0x27D] != 0) {
        sound_stop(((u8 *)obj)[0x27D]);
    }
}

/* An angle (low 12 bits) limited to 0..0x20 in its first half turn, 0xEE4..0xFFF in its second. */
s16 angle_clamp_pitch(s32 angle) {
    s32 result;

    angle &= 0xFFF;
    if (angle >= 0x801) {
        result = MAX(cap_FFF(angle), 0xEE4);
    } else {
        result = NOT_NEGATIVE(cap_20(angle));
    }
    return result;
}



void dir_to_angles_clamped(Vec3 *dir, SVECTOR *out) {
    s32 yaw;
    s32 pitch;

    angles_to_player(dir->x, dir->y, dir->z, &yaw, &pitch);
    out->vy = yaw;
    out->vx = -angle_clamp_pitch((s16)pitch);
    out->vz = 0;
}
