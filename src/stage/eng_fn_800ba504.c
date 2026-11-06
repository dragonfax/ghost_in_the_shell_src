/* Shared by s06, s11: flier_approach_update..obj_spawn_flier (7 functions). */

#include "stage.h"

#if STAGE == 6
/* Only s06 has this aim/turn update: s11 calls other functions at the same spots, so its copy stays asm. */
s32 obj_in_view_angle(Object *obj, s32 a1, s32 a2);
void enemy_fire_fx(Object *obj);

void flier_approach_update(Object *obj, ObjHandler *handler) {
    Vec3 dir;
    SVECTOR rot;
    s32 dist;

    obj_turn_to_angles(obj, &dir, &rot);
    obj->speed = 0;
    switch (handler->result) {
    case -2:
        handler->result = 1;
        obj->vars.turn.pad_248[2] = 0;
        obj->vars.ride.enabled = rand_a_next() % 8 + 4;
        obj->vars.turn.pad_248[3] = rand_a_next() % 48 + 0x18;
        goto place;
    case -1:
        {
            u8 timer = obj->vars.turn.pad_248[3];

            obj->vars.turn.pad_248[3] = timer + 0xFF;
            if (timer == 0) {
                handler->result = -2;
            }
        }
        goto stop_sound;
    default:
        dist = isqrt(length_sq((VEC_80139584.x >> 12) - (obj->x >> 12),
                               (VEC_80139584.y >> 12) - (obj->y >> 12),
                               (VEC_80139584.z >> 12) - (obj->z >> 12)));
        if (dist >= 0x800 || obj_in_view_angle(obj, 0x300, 0x300) == 0) {
        stop_sound:
            if (obj->vars.chaser.pad_27C[0] != 0) {
                sound_stop(obj->vars.chaser.pad_27C[0]);
                obj->vars.chaser.pad_27C[0] = 0;
            }
            goto place;
        }
        if (obj->vars.ride.enabled == 0) {
            handler->result = -1;
        } else {
            if (obj->vars.turn.pad_248[2]++ >= 4) {
                obj->vars.turn.pad_248[2] = 0;
                obj->vars.ride.enabled--;
                enemy_fire_fx(obj);
            }
            handler->result = 1;
        }
    }
place:
    obj->x = (obj->placement->x >> 12) << 12;
    obj->y = (obj->placement->y >> 12) << 12;
    obj->z = (obj->placement->z >> 12) << 12;
}
#else
void flier_approach_update(Object *obj, ObjHandler *handler) {
    s32 dir[3];
    SVECTOR rot;
    s32 dist;

    obj_turn_to_angles(obj, dir, (s16 *)&rot);
    obj->speed = 0;
    switch (handler->result) {
    case -2:
        handler->result = 1;
        obj->vars.turn.pad_248[2] = 0;
        obj->vars.ride.enabled = rand_a_next() % 8 + 4;
        obj->vars.turn.pad_248[3] = rand_a_next() % 48 + 0x18;
        goto place;
    case -1:
        {
            u8 timer = obj->vars.turn.pad_248[3];

            obj->vars.turn.pad_248[3] = timer + 0xFF;
            if (timer == 0) {
                handler->result = -2;
            }
        }
        goto stop_sound;
    default:
        dist = isqrt(length_sq((VEC_80139584.x >> 12) - (obj->x >> 12),
                               (VEC_80139584.y >> 12) - (obj->y >> 12),
                               (VEC_80139584.z >> 12) - (obj->z >> 12)));
        if (dist >= 0x800 || obj_in_view_angle(obj, 0x300, 0x300) == 0) {
        stop_sound:
            if (obj->vars.chaser.pad_27C[0] != 0) {
                sound_stop(obj->vars.chaser.pad_27C[0]);
                obj->vars.chaser.pad_27C[0] = 0;
            }
            goto place;
        }
        if (obj->vars.ride.enabled == 0) {
            handler->result = -1;
        } else {
            if (obj->vars.turn.pad_248[2]++ >= 4) {
                obj->vars.turn.pad_248[2] = 0;
                obj->vars.ride.enabled--;
                enemy_fire_fx(obj);
            }
            handler->result = 1;
        }
    }
place:
    obj->x = (obj->placement->x >> 12) << 12;
    obj->y = (obj->placement->y >> 12) << 12;
    obj->z = (obj->placement->z >> 12) << 12;
}
#endif

s32 pchr_pose_setup(Object *obj, s32 value) {
    s32 slot;
    s32 *poses;
    s16 rot_buf[3];
    u16 pos_buf[3];
    register s32 track asm("$3");
    s32 yaw;

    slot = pchr_copy_slot(value);
    poses = pchr_poses_build(slot);
    pchr_table[slot & 0x7FF].unk_0C = poses;

    if (obj->speed != 0 && obj->vars.ride.moving) {
        s16 *rot = rot_buf;
        u16 *pos = pos_buf;

        pos[0] = obj->vars.flier.unk_24E;
        pos[1] = 0;
        pos[2] = 0;
        rot[0] = 0x6C;
        rot[1] = -0x31;
        rot[2] = 0xBA;
        pose_rotate_range(poses, 2, 1, rot, pos);
        rot[0] = -0x6C;
        rot[1] = -0x31;
        rot[2] = 0xBA;
        pose_rotate_range(poses, 3, 1, rot, pos);
        rot[0] = 0x6C;
        rot[1] = -0x31;
        rot[2] = -0x30;
        pose_rotate_range(poses, 4, 1, rot, pos);
        rot[0] = -0x6C;
        rot[1] = -0x31;
        rot[2] = -0x30;
        pose_rotate_range(poses, 5, 1, rot, pos);
        rot[0] = 0x6C;
        rot[1] = -0x31;
        rot[2] = -0xB4;
        pose_rotate_range(poses, 6, 1, rot, pos);
        rot[0] = -0x6C;
        rot[1] = -0x31;
        rot[2] = -0xB4;
        pose_rotate_range(poses, 7, 1, rot, pos);
    }

    {
        s16 *rot = rot_buf;
        u16 *pos = pos_buf;

        yaw = obj->yaw;
        track = obj->vars.words[3] - yaw;
        track -= obj->vars.flier.floor_slope;
        rot[1] = -0xC2;
        rot[0] = 0;
        rot[2] = -0x48;
        pos[0] = 0;
        pos[1] = track & 0xFFF;
        pos[2] = 0;
        pose_rotate_range(poses, 0, 1, rot, pos);
        pos[0] = obj->vars.flier.pitch & 0xFFF;
        pose_rotate_range(poses, 0xD, 1, rot, pos);
    }
    return slot;
}

s32 pchr_pose_setup(Object *obj, s32 model);
void flier_draw(Object *obj, ObjHandler *handler) {
    s32 mode;
    Vec3 pos;
    SVECTOR rot;
    SVECTOR aim;
    s32 dx;
    s32 dz;
    s32 colour;
    s32 pitch;
    s32 *player;
    Vec3 *posp;
    SVECTOR *aimp;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    colour = 0;
    do {
        mode = pchr_pose_setup(obj, model_slot_pchr(*(s32 *)obj->asset));
        if (obj->hit > 0) {
            FAKE_OPAQUE(colour);
            colour = 0x60C0FF;
        }
    } while (0);
    if (obj->vars.turn.pad_248[0] != 0) {
        spark_add(pos.x, pos.y, pos.z, rot.vy += obj->vars.flier.floor_slope, rot.vx, rot.vz, mode, colour);
        pos.x = obj->x;
        pos.y = obj->y - 0x20000;
        pos.z = obj->z;
        aim.vx = obj->width + 0x20;
        aim.vy = obj->height;
        aim.vz = obj->unk_1E8[0] + 0x20;
        posp = &pos;
        aimp = &aim;
        player = player_position();
        fly_move(atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)) + 0x800, 8, &dx, &dz);
        rot.vz = 0;
        pos.x += dz;
        pos.z += dx;
        if (ABS(obj->vars.flier.unk_264) > 20) {
            aim_marker_draw(2, aimp, posp, &rot);
        } else {
            aim_marker_draw(2, aimp, posp, 0);
        }
    } else {
        spark_add(pos.x, pos.y, pos.z, rot.vy, rot.vx, rot.vz, mode, colour);
        pos.x = obj->x;
        pos.y = obj->y - 0x20000;
        pos.z = obj->z;
        aim.vx = obj->width + 0x20;
        aim.vy = obj->height;
        aim.vz = obj->unk_1E8[0] + 0x20;
        aim_marker_draw(2, &aim, &pos, 0);
    }
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

static inline s32 debris_floor_probe(Object *obj, s32 speed) {
    s32 from[3];
    s32 to[3];
    struct { s32 x, y, z, pad; } hit;
    s32 dz;
    s32 dx;
    s16 ground;
    s32 old;

    fly_move(obj->yaw, speed, &dx, &dz);
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
    trace_world(0x12, 4, from, to, &hit);
    old = ((DebrisVars *)&obj->vars)->ground;
    if (to[1] == hit.y) {
        ground = old | 1;
    } else {
        ground = old;
    }
    ((DebrisVars *)&obj->vars)->ground = ground;

    return hit.y;
}
static inline s32 debris_spread(s32 rnd, s32 half) {
    s16 narrow = half;
    return rnd * (narrow + half) / 0x1000 - narrow;
}
s32 flier_callback(Object *obj) {
    s32 pos[3];
    s32 pos2[3];
    s32 sum;
    s32 yaw;

    switch (((DebrisVars *)&obj->vars)->timer) {
    case -2:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        if (((DebrisVars *)&obj->vars)->sound != 0) {
            sound_stop(((DebrisVars *)&obj->vars)->sound);
            ((DebrisVars *)&obj->vars)->sound = 0;
        }
        obj->handlers[3].fn = obj_draw_spark;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->handlers[0].fn = 0;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->unk_17A = 0;
        spawn_effect(pos[0], pos[1], pos[2], 0x80007F00);
        ((DebrisVars *)&obj->vars)->timer = 0x5A;
        if (((DebrisVars *)&obj->vars)->flying != 0) {
            ((DebrisVars *)&obj->vars)->pitch = obj->yaw;
            if (rand_a_next() < 0x800) {
                ((DebrisVars *)&obj->vars)->pitch_turn = 0x3E8;
            } else {
                ((DebrisVars *)&obj->vars)->pitch_turn = -0x3E8;
            }
            if (rand_a_next() < 0x800) {
                ((DebrisVars *)&obj->vars)->yaw_turn = 0x18;
            } else {
                ((DebrisVars *)&obj->vars)->yaw_turn = -0x18;
            }
            obj->speed = get_flow_max();
        }
        return 1;
    case -1:
        pos2[0] = obj->x >> 12;
        pos2[1] = obj->y >> 12;
        pos2[2] = obj->z >> 12;
        particle_spawn_burst(pos2[0], pos2[1], pos2[2], 0);
        obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
        spawn_effect(pos2[0], pos2[1], pos2[2], 0x80007F00);
        return 0;
    }
    if (((DebrisVars *)&obj->vars)->flying != 0) {
        if (((DebrisVars *)&obj->vars)->timer < 0x2D) {
            obj->speed = obj->speed * 7 >> 3;
        } else {
            ((DebrisVars *)&obj->vars)->ground = 0;
            ((DebrisVars *)&obj->vars)->floor_a = debris_floor_probe(obj, obj->unk_1E8[0]);
            ((DebrisVars *)&obj->vars)->floor_b = debris_floor_probe(obj, -obj->unk_1E8[0]);
            ((DebrisVars *)&obj->vars)->floor_diff = ((DebrisVars *)&obj->vars)->floor_a - ((DebrisVars *)&obj->vars)->floor_b;
            atan2(obj->unk_1E8[0] << 3, ((DebrisVars *)&obj->vars)->floor_diff << 2);
            sum = ((DebrisVars *)&obj->vars)->floor_a;
            sum += ((DebrisVars *)&obj->vars)->floor_b;
            sum <<= 11;
            if (obj->y < sum && sum - obj->y > 0x8000) {
                sum = obj->y + 0x8000;
            }
            obj->move_delta[1] = sum - obj->y;
            obj->y = sum;
        }
        yaw = obj->yaw + ((DebrisVars *)&obj->vars)->yaw_turn;
        obj->yaw = yaw;
        fly_move(((DebrisVars *)&obj->vars)->pitch, obj->speed, &obj->vz, &obj->vx);
    }
    if (((DebrisVars *)&obj->vars)->timer % 30 == 0) {
        s32 spot[3];
        s32 rnd;

        spot[0] = obj->x >> 12;
        spot[1] = obj->y >> 12;
        spot[2] = obj->z >> 12;
        rnd = rand_a_next();
        spot[0] += debris_spread(rnd, obj->width);
        spot[1] -= (s16)obj->height;
        rnd = rand_a_next();
        spot[2] += debris_spread(rnd, obj->unk_1E8[0]);
        spawn_effect(spot[0], spot[1], spot[2], 0x80000000);
    }
    ((DebrisVars *)&obj->vars)->timer--;
    return 1;
}

/* Turns a flier towards pos within range (or stops it), then strafes it. Returns the signed speed. */
s32 flier_strafe_to_player(s16 *ang, s32 *pos, s32 *vec, s32 speed, s32 range) {
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

/* The vars of the fliers flier_update moves. */
typedef struct FlierVars {
    /* 0x248 */ u8 pad_248[4];
    /* 0x24C */ s16 chase_timer;
    /* 0x24E */ u16 bob_phase;
    /* 0x250 */ u8 pad_250[2];
    /* 0x252 */ u16 ground_flags;
    /* 0x254 */ u8 pad_254[8];
    /* 0x25C */ s32 ground_a;
    /* 0x260 */ s32 ground_b;
    /* 0x264 */ s32 ground_diff;
    /* 0x268 */ s32 player_dist;
    /* 0x26C */ s32 limit;
    /* 0x270 */ s32 strafe_speed;
    /* 0x274 */ s32 strafe_target;
    /* 0x278 */ s32 strafe_angle;
    /* 0x27C */ u8 pad_27C[4];
    /* 0x280 */ Flow flow;
} FlierVars;

/* The burst-fire update each stage's copy calls (s11's is named). */
#define BURST_UPDATE enemy_burst_update
void BURST_UPDATE(Object *obj, ObjHandler *handler);

#define V ((FlierVars *)&obj->vars)

static inline s32 probe_ground_height(Object *obj, s32 dist) {
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s32 dx, dz;
    s32 flags;

    fly_move(obj->yaw, dist, &dx, &dz);
    to[0] = obj->x >> 12;
    to[1] = obj->y >> 12;
    to[2] = obj->z >> 12;
    to[0] += dz >> 12;
    from[0] = to[0];
    from[1] = to[1];
    to[2] += dx >> 12;
    from[2] = to[2];
    from[1] = to[1] - (s16)obj->height;
    to[1] = to[1] + ((s16)obj->height >> 1);
    trace_world(0x12, 4, from, to, hit);
    flags = (s16)V->ground_flags;
    V->ground_flags = to[1] == hit[1] ? flags | 1 : flags;
    return hit[1];
}

void flier_update(Object *obj, ObjHandler *handler) {
    s32 *pos;
    s32 *player;
    s32 move[3];
    s32 speed;
    Flow *flow;
    s32 tilt;
    register s32 ground_y asm("$4");
    s32 old_y;

    obj->vy = 0;
    obj->accel_y = 0;
    pos = player_position();
    V->player_dist = SquareRoot0(length_sq(pos[0] - (obj->x >> 12), pos[1] - (obj->y >> 12), pos[2] - (obj->z >> 12)));
    flow = &V->flow;
    flow->speed = get_flow_max();
    flow_sample(flow, obj->width * 3 / 4, &obj->x, move, &obj->turn);
    obj->vx = move[0];
    obj->vz = move[2];
    obj->yaw = flow->angle;
    if (V->chase_timer <= 0) {
        if (V->player_dist >= 0) {
            if (V->player_dist < 0x400) {
                speed = 0x10;
                goto picked;
            }
            if (V->player_dist < 0x801) {
                speed = 0x14;
                goto picked;
            }
        }
        speed = 0x20;
    picked:
        player = player_position();
        if (((atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)) + 0x400) & 0xFFF) > 0x800) {
            speed = -speed;
        }
        fly_strafe(obj->yaw, speed, &obj->vz, &obj->vx);
    } else {
        speed = V->player_dist >> 8;
        flier_strafe_to_player(&flow->state, &obj->x, &obj->vx, speed + (V->player_dist >> 9), 0x400);
        if (flow->wall_direction > 0x400) {
            V->strafe_speed = (rand_a_next() >> 10) + 8;
            V->strafe_target = 0xF80;
        } else if (flow->wall_direction < -0x400) {
            V->strafe_speed = (rand_a_next() >> 10) + 8;
            V->strafe_target = 0x80;
        }
        if (V->strafe_target != 0) {
            V->strafe_angle = angle_approach(V->strafe_angle, V->strafe_target, 6);
        }
        fly_strafe(-(V->strafe_angle << 2), V->strafe_speed, &obj->vz, &obj->vx);
        V->chase_timer--;
    }
    V->limit = limit_move(&obj->x, &obj->vx);
    V->ground_flags = 0;
    V->ground_a = probe_ground_height(obj, obj->unk_1E8[0]);
    V->ground_b = probe_ground_height(obj, -obj->unk_1E8[0]);
    V->ground_diff = V->ground_a - V->ground_b;
    tilt = atan2(obj->unk_1E8[0] << 3, V->ground_diff << 2);
    ground_y = (V->ground_a + V->ground_b) << 11;
    if (obj->y < ground_y) {
        if (ground_y - obj->y > 0x8000) {
            ground_y = obj->y + 0x8000;
            tilt += 2;
        }
        tilt += 2;
    }
    old_y = obj->y;
    obj->y = ground_y;
    {
        register s32 dy asm("$2") = ground_y - old_y;
        obj->move_delta[1] = dy;
    }
    if (V->ground_diff > 0) {
        obj->pitch = angle_approach(obj->pitch, -tilt, 1);
    } else {
        obj->pitch = angle_approach(obj->pitch, tilt, 4);
    }
    V->bob_phase = (V->bob_phase + 0x48) & 0x1FF;
    BURST_UPDATE(obj, handler);
}
#undef V
#undef BURST_UPDATE

/* Object spawn/init. s06 only: the data it points at (flier_asset, flier_script_ptr, D_8011C7C8) is a
 * different table in s11, so s11 keeps the asm. */
#if STAGE == 6
extern s16 *flier_script_ptr;
extern s32 flier_asset[3];
extern StateEntry D_8011C7C8[2];
void flier_approach_update(Object *obj, ObjHandler *handler);
void flier_draw(Object *obj, ObjHandler *handler);
s32 flier_callback(Object *obj);
void flier_update(Object *obj, ObjHandler *handler);
void obj_state_run_b(Object *obj, ObjHandler *handler);

s32 obj_spawn_flier(Placement *place) {
    Object *obj;
    s32 sound;
    s16 **script_slot;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    *(s16 *)&place->unk_00[2] = -1;
    *(s16 *) &obj->vars.h.unk_250 = -2;
    obj->vars.flier.unk_24E = 0;
    obj->vars.words[3] = 0;
    obj->vars.flier.pitch = 0;
    *(u8 *)&obj->vars.flier.unk_24A = 0;
    ((u8 *)&obj->vars.flier.unk_24A)[1] = 0;
    obj->vars.flier.range = place->range;
    *(u8 *)&obj->vars.flier.unk_248 = *(u16 *) &place->unk_1A >> 8;
    script_slot = &flier_script_ptr;
    obj->kind = place->unk_00[5];
    obj->asset = flier_asset;
    obj->state_table = D_8011C7C8;
    script_start((Script *) obj, *script_slot, (s32) script_slot);
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = flier_draw;
    obj->callback = (s32) &flier_callback;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->destructor = obj_stop_sound_slots;
    ((s8 *)&obj->vars.enemy.shot_timer)[0] = 0;
    ((s8 *)&obj->vars.enemy.shot_timer)[1] = 0;
    if (*(u8 *)&obj->vars.flier.unk_248 == 0) {
        obj->handlers[1].fn = flier_approach_update;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj_init_from_place(obj, place, 0x24);
        obj->next_state = 1;
        obj->accel_y = 0;
    } else {
        obj->handlers[1].fn = flier_update;
        obj->vars.words[10] = -8;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->vars.words[11] = 0x200;
        obj->vars.flier.floor_slope = 0;
        obj_init_from_place(obj, place, 0x124);
        obj->handlers[2].fn = obj_state_run_b;
        obj->speed = 1;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->yaw = 0x800;
        obj->hit_cooldown_max = rand_a_next();
        sound = sound_start(SND_PAIR(SND_SLOW_MECH_MOVE | SND_HELD, SND_FAST_MECH_MOVE | SND_HELD), 0x40, 0, 0);
        sound_attach(sound, &obj->x, NULL);
        sound_set_flag_bit2(sound, 1);
        ((s8 *)&obj->vars.enemy.shot_timer)[1] = sound;
        rec_reset((PartSlot *) &obj->vars.words[0xE]);
    }
    obj_set_part_bounds(obj, 0, 0x1000);
    return 1;
}
#else
extern s16 *D_8011A5B0;
extern s32 D_8011A520[3];
extern StateEntry D_8011A5B4[2];
s32 flier_callback(Object *obj);
void flier_approach_update(Object *obj, ObjHandler *handler);
/* Same code as obj_spawn_flier (s06). */
s32 obj_spawn_flier(Placement *place) {
    Object *obj;
    s32 sound;
    s16 **script_slot;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    *(s16 *)&place->unk_00[2] = -1;
    *(s16 *) &obj->vars.h.unk_250 = -2;
    obj->vars.flier.unk_24E = 0;
    obj->vars.words[3] = 0;
    obj->vars.flier.pitch = 0;
    *(u8 *)&obj->vars.flier.unk_24A = 0;
    ((u8 *)&obj->vars.flier.unk_24A)[1] = 0;
    obj->vars.flier.range = place->range;
    *(u8 *)&obj->vars.flier.unk_248 = *(u16 *) &place->unk_1A >> 8;
    script_slot = &D_8011A5B0;
    obj->kind = place->unk_00[5];
    obj->asset = D_8011A520;
    obj->state_table = D_8011A5B4;
    script_start((Script *) obj, *script_slot, (s32) script_slot);
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = flier_draw;
    obj->callback = (s32) &flier_callback;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->destructor = obj_stop_sound_slots;
    ((s8 *)&obj->vars.enemy.shot_timer)[0] = 0;
    ((s8 *)&obj->vars.enemy.shot_timer)[1] = 0;
    if (*(u8 *)&obj->vars.flier.unk_248 == 0) {
        obj->handlers[1].fn = flier_approach_update;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj_init_from_place(obj, place, 0x24);
        obj->next_state = 1;
        obj->accel_y = 0;
    } else {
        obj->handlers[1].fn = flier_update;
        obj->vars.words[10] = -8;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->vars.words[11] = 0x200;
        obj->vars.flier.floor_slope = 0;
        obj_init_from_place(obj, place, 0x124);
        obj->handlers[2].fn = obj_state_run_b;
        obj->speed = 1;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->yaw = 0x800;
        obj->hit_cooldown_max = rand_a_next();
        sound = sound_start(SND_PAIR(SND_SLOW_MECH_MOVE | SND_HELD, SND_FAST_MECH_MOVE | SND_HELD), 0x40, 0, 0);
        sound_attach(sound, &obj->x, NULL);
        sound_set_flag_bit2(sound, 1);
        ((s8 *)&obj->vars.enemy.shot_timer)[1] = sound;
        rec_reset((PartSlot *) &obj->vars.words[0xE]);
    }
    obj_set_part_bounds(obj, 0, 0x1000);
    return 1;
}
#endif
