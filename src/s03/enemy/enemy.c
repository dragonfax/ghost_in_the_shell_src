/* enemy: one of s03's own original source files (scripts/objmap.py); part of src/s03/main.c's unit, included there. */

void script_read_speed(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->speed = *cursor;
}


/* Same code as func_800BC7AC (s01). */
void script_read_next_state(Object *obj) {
    obj->next_state = obj_read_u16(obj);
}

/* Same code as func_800BC7C8 (s01). */
void func_800C0328(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void script_branch_if_player_near(Object *obj) {
    s32 *player;
    s32 dist;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 half;
    s16 *cursor;
    s32 threshold;
    s32 index;

    player = player_position();
    half = (s16) obj->height / 2;
    dx = player[0] - (obj->x >> 12);
    dy = player[1] - ((obj->y >> 12) - half);
    dz = player[2] - (obj->z >> 12);
    dist = (s16) isqrt(length_sq(dx, dy, dz));

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < dist) {
        return;
    }
    obj->script.pc = ((s16 **)obj->script.data)[index];
}


void script_clear_salvo_timer(Object *obj) {
    obj->vars.enemy.unk_25C = 0;
}


extern s16 enemy_ai_enabled;
void script_jump_if_flag(Object *obj) {
    s16 *script;
    s32 saved;
    s32 index;

    script = obj->script.pc;
    obj->script.pc = script + 1;
    index = script[0];
    if (enemy_ai_enabled == 1) {
        saved = obj->score;
        obj->script.pc = ((s16 **)obj->script.data)[index];
        meter_set_mode(1);
        obj_actors_clear_index();
        obj_hit_clear(obj->index);
        obj->score = saved;
    }
}

void enemy_sound_set(Object *obj) {
    /* low half of the enemy sound slot, written as a s16 */
    *(s16 *) &obj->vars.enemy.sound = 1;
}

/* Object callback (entry in the handler table at enemy_callback_table): clears the
   halfword at 0x270, the low half of vars.enemy.sound. */
void enemy_sound_clear(Object *obj) {
    *(s16 *)&obj->vars.enemy.sound = 0;
}

void enemy_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

/* Counts down the halfword at 0x262 (inside vars.enemy.unk_260); when it runs
 * below zero, calls obj_spawn_ripple and reloads it with 0x20. */
void enemy_cooldown_tick(Object *obj) {
    s16 remaining;

    remaining = *(u16 *)&obj->vars.enemy.unk_260[2] - 1;
    *(u16 *)&obj->vars.enemy.unk_260[2] = remaining;
    if (remaining < 0) {
        obj_spawn_ripple(obj, 0x300, 0x580);
        *(u16 *)&obj->vars.enemy.unk_260[2] = 0x20;
    }
}

/* Turns the four s16 angles at vars.turn.yaw (+0, +2, +4, +6) toward the
 * object's yaw (pairs 0/2) and pitch (pairs 1/3), 0x18 per frame. */
void turn_angles_approach(Object *obj, s32 arg) {
    s16 *angles = &obj->vars.turn.yaw;

    angles[0] = angle_approach(angles[0], obj->yaw, 0x18);
    angles[2] = angle_approach(angles[2], obj->yaw, 0x18);
    angles[1] = angle_approach(angles[1], obj->pitch, 0x18);
    angles[3] = angle_approach(angles[3], obj->pitch, 0x18);
}

void obj_yaw_approach(Object *obj, s32 unused) {
    s16 *angle = (s16 *)&obj->vars.h.unk_24A;

    *angle = angle_approach(*angle, obj->yaw, 0x18);
}

void enemy_turn_step(Object *obj, s32 arg) {
    obj_turn_toward_player(obj, 8);
    obj->vars.h.unk_24A = angle_approach((s16)obj->vars.h.unk_24A, obj->yaw, 0x18);
    turn_angles_approach(obj, arg);
}

void obj_trace_aim_at_player(Object *obj, s32 arg) {
    s32 *player;
    s16 turned;
    register s16 aim asm("$4");

    obj_turn_toward_player(obj, 8);
    player = player_position();
    turned = angle_approach(obj->vars.trace.aim_yaw,
                            (s16)atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)),
                            0x18);
    aim = turned;
    if (ABS(obj->yaw - turned) < 0x300) {
        obj->vars.trace.aim_yaw = aim;
    }
}

extern s16 enemy_ai_enabled;
/* Counts the object's next_state up while it is 8 and down while it is 0xC,
   and clears the counter in any other state. The counter is the halfword
   at 0x272, the upper half of vars.enemy.sound (no stage.h field for it). */
void enemy_state_counter_update(Object *obj) {
    u16 *state_counter;
    s16 state;

    if (enemy_ai_enabled == 1) {
        ((void (*)(void))enemy_turn_step)(); /* the original passes no arguments */
    }
    state_counter = (u16 *)&obj->vars.enemy.sound + 1;
    state = obj->next_state;
    if (state == 8) {
        *state_counter = (u16)(*state_counter + 1);
        return;
    }
    if (state == 0xC) {
        *state_counter = (u16)(*state_counter - 1);
        return;
    }
    *state_counter = 0;
}

extern void enemy_fire_shot(Object *obj);
void enemy_fly_update(Object *obj, s32 arg) {
    s32 d[2];
    s32 sub;
    u16 timer;
    s32 vz;
    s32 dist;

    dist = ((s16 *)rcossin_tbl)[(((u16 *)obj->vars.words)[0] & 0xFFF) * 2];
    sub = dist * obj->speed;
    d[0] = 0;
    d[1] = 0;
    if (sub < 0) {
        sub += 0xFFF;
    }
    dist = sub >> 12;
    enemy_turn_step(obj, arg);
    sub = ABS(dist);
    fly_move(obj->yaw, sub, &d[0], &d[1]);
    vz = d[0];
    timer = ((u16 *)obj->vars.words)[11];
    obj->vx = d[1];
    obj->vz = vz;
    ((u16 *)obj->vars.words)[11] = timer - 1;
    if ((s16)timer < 0) {
        enemy_fire_shot(obj);
        ((s16 *)obj->vars.words)[11] = 0x46;
    }
}

void enemy_fire_shot(Object *obj);
void enemy_ascend_update(Object *obj) {
    s16 timer;

    obj->unk_1B7 = 0;
    ((void (*)(void))enemy_turn_step)(); /* the original passes no arguments */
    timer = obj->vars.enemy.unk_25E;
    obj->vy = -0x2000;
    obj->vars.enemy.unk_25E = timer - 1;
    if (timer < 0) {
        enemy_fire_shot(obj);
        obj->vars.enemy.unk_25E = 0x46;
    }
    enemy_cooldown_tick(obj);
}

void enemy_hover_update(Object *obj, s32 arg) {
    s32 dx;
    s32 dz;
    u16 timer;

    dx = 0;
    dz = 0;
    enemy_turn_step(obj, arg);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj->vx = dz;
    obj->vz = dx;
    timer = obj->vars.enemy.unk_25E;
    obj->vy = 0;
    obj->vars.enemy.unk_25E = timer - 1;
    if ((s16) timer < 0) {
        enemy_fire_shot(obj);
        obj->vars.enemy.unk_25E = 0x46;
    }
    enemy_cooldown_tick(obj);
}

void enemy_descend_update(Object *obj, s32 arg) {
    u16 timer;

    enemy_turn_step(obj, arg);
    timer = obj->vars.enemy.unk_25E;
    obj->vy = 0x2000;
    obj->vars.enemy.unk_25E = timer - 1;
    if ((s16) timer < 0) {
        enemy_fire_shot(obj);
        obj->vars.enemy.unk_25E = 0x46;
    }
    enemy_cooldown_tick(obj);
}

void enemy_twin_shot_fire(Object *obj, s32 arg, ShotAim *q);
void obj_trace_aim_at_player(Object *obj, s32 arg);
void enemy_twin_shot_update(Object *obj, s32 arg1) {
    ShotAim q = {0, 0, 0, 0};
    obj_turn_toward_player(obj, 8);
    obj_trace_aim_at_player(obj, arg1);
    turn_angles_approach(obj, arg1);
    q.b = obj->vars.h.unk_24A;
    if ((s16)obj->vars.h.unk_256-- < 0) {
        enemy_twin_shot_fire(obj, 0x3C, &q);
        enemy_twin_shot_fire(obj, -0x3C, &q);
        obj->vars.h.unk_256 = 8;
    }
}

s32 muzzle_aim_yaw(Object *obj, s32 mode);
void muzzle_fx_spawn(Object *self, s32 x_offset, s16 *rot);

/* Turns toward the player, swings both guns toward their aim angles
   (each kept only while within 0x200 of the body's yaw) and fires the
   two guns in turn every 0x28 frames. */
void enemy_twin_gun_update(Object *obj, s32 arg) {
    u16 rot[3];
    s16 angle; /* left gun's aim, later the gun toggle */
    s16 right;
    s32 diff;
    s32 diff_right;
    u16 timer;

    obj_turn_toward_player(obj, 8);
    obj_yaw_approach(obj, arg);

    angle = angle_approach(obj->vars.h.unk_24E & 0xFFF, muzzle_aim_yaw(obj, 1) & 0xFFF, 0x18);
    diff = obj->yaw - angle;
    if (diff >= 0 ? diff < 0x200 : (angle - obj->yaw) < 0x200) {
        obj->vars.h.unk_24E = angle;
    }
    obj->vars.h.unk_24E = angle;

    right = angle_approach(obj->vars.h.unk_252 & 0xFFF, muzzle_aim_yaw(obj, 0) & 0xFFF, 0x18);
    diff_right = obj->yaw - right;
    if (diff_right >= 0) {
        if (diff_right >= 0x200) {
        } else {
            obj->vars.h.unk_252 = right;
        }
    } else if ((right - obj->yaw) < 0x200) {
        obj->vars.h.unk_252 = right;
    }
    obj->vars.h.unk_252 = right;

    timer = obj->vars.h.unk_258;
    obj->vars.h.unk_258 = timer - 1;
    if ((s16) timer < 0) {
        angle = *(u16 *) obj->vars.enemy.unk_260 ^ 1;
        *(u16 *) obj->vars.enemy.unk_260 = angle;
        if (angle == 0) {
            rot[0] = obj->vars.h.unk_250;
            rot[1] = obj->vars.h.unk_24E;
            rot[2] = 0;
            muzzle_fx_spawn(obj, 0x357, (s16 *) rot);
        } else {
            rot[0] = obj->vars.enemy.sound_channel[0];
            rot[1] = obj->vars.h.unk_252;
            rot[2] = 0;
            muzzle_fx_spawn(obj, -0x357, (s16 *) rot);
        }
        obj->vars.h.unk_258 = 0x28;
    }
}

void enemy_spawn_child(Object *parent);
void enemy_spawn_beeper(Object *parent, s32 variant);
void enemy_salvo_update(Object *obj, s32 arg) {
    u16 timer;

    obj_turn_toward_player(obj, 8);
    obj_trace_aim_at_player(obj, arg);
    turn_angles_approach(obj, arg);
    timer = (u16) obj->vars.enemy.unk_25C;
    obj->vars.enemy.unk_25C = timer - 1;
    if ((s16) timer < 0) {
        enemy_spawn_child(obj);
        obj->vars.enemy.unk_25C = 0x96;
    }
    if (obj->vars.enemy.unk_25C == 0x96) {
        enemy_spawn_beeper(obj, 0);
    }
    if (obj->vars.enemy.unk_25C == 0x82) {
        enemy_spawn_beeper(obj, 1);
    }
    if (obj->vars.enemy.unk_25C == 0x6E) {
        enemy_spawn_beeper(obj, 0);
    }
    if (obj->vars.enemy.unk_25C == 0x5A) {
        enemy_spawn_beeper(obj, 1);
    }
    if (obj->vars.enemy.unk_25C == 0x46) {
        enemy_spawn_beeper(obj, 0);
    }
    if (obj->vars.enemy.unk_25C == 0x3C) {
        enemy_spawn_beeper(obj, 1);
    }
    obj->vars.h.unk_25A = 0x1E;
}

void obj_trace_aim_at_player(Object *obj, s32 arg);
void enemy_fire_trace(Object *obj);
void enemy_fire_update(Object *obj, s32 arg) {
    u16 old_unk_25A;

    obj_turn_toward_player(obj, 8);
    obj_trace_aim_at_player(obj, arg);
    turn_angles_approach(obj, arg);
    old_unk_25A = obj->vars.h.unk_25A;
    obj->vars.h.unk_25A = old_unk_25A - 1;
    if ((s16) old_unk_25A < 0) {
        enemy_fire_trace(obj);
        obj->vars.h.unk_25A = 0x1E;
    }
}

extern s16 enemy_sound_timer;
extern s16 enemy_sound_5042_flag;
extern s16 enemy_sound_5043_flag;
extern s16 enemy_sound_5044_flag;
extern s16 enemy_loop_sound_flag;
extern s32 enemy_loop_sound_id;
extern s16 enemy_alarm_sound_flag;
extern s32 enemy_alarm_sound_id;
void obj_state_sound_play(Object *obj, ObjHandler *h) {
    s32 pos[3];
    s32 *pos_ptr;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    /* the first sound takes the array address computed before the branch;
       the later ones recompute it (matches the original's register use) */
    pos_ptr = pos;
    if (obj->next_state == 1) {
        if (enemy_sound_timer >= 0x1001) {
            sound_play_at_units(0x5040, 0x60, 0x3C, pos_ptr);
            enemy_sound_timer = 0;
        }
        enemy_sound_timer += 0xAA;
    }
    if (obj->next_state == 5 && enemy_sound_5042_flag == 0) {
        sound_play_at_units(0x5042, 0x60, 0x3C, pos);
        enemy_sound_5042_flag = 1;
    }
    if (obj->next_state == 8 || obj->next_state == 0xA) {
        if (enemy_sound_5043_flag == 0) {
            sound_play_at_units(0x5043, 0x60, 0x3C, pos);
            enemy_sound_5043_flag = 1;
        }
        enemy_sound_5044_flag = 0;
    }
    if (obj->next_state == 0xC) {
        if (enemy_sound_5044_flag == 0) {
            sound_play_at_units(0x5044, 0x60, 0x3C, pos);
            enemy_sound_5044_flag = 1;
        }
        enemy_sound_5043_flag = 0;
    }
    if (obj->next_state == 9) {
        if (enemy_loop_sound_flag == 0) {
            enemy_loop_sound_id = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
            sound_attach(enemy_loop_sound_id, &obj->x, NULL);
            enemy_loop_sound_flag = 1;
        }
    } else if (enemy_loop_sound_flag == 1) {
        sound_stop(enemy_loop_sound_id);
        enemy_loop_sound_id = 0;
        enemy_loop_sound_flag = 0;
    }
    if (*(s16 *)&obj->vars.enemy.sound == 1) {
        if (enemy_alarm_sound_flag == 0) {
            enemy_alarm_sound_id = sound_start(0xD053D054, 0x60, 0, 0);
            sound_attach(enemy_alarm_sound_id, &obj->x, NULL);
            enemy_alarm_sound_flag = 1;
        }
    } else if (enemy_alarm_sound_flag == 1) {
        sound_stop(enemy_alarm_sound_id);
        enemy_alarm_sound_id = 0;
        enemy_alarm_sound_flag = 0;
    }
    if ((u16)obj->next_state < 2) {
        enemy_sound_5042_flag = 0;
    }
}

/* 0x26E is a halfword in the enemy view of vars (u8 unk_26E[2] in stage.h). */
void enemy_fall_update(Object *obj) {
    s16 mode;

    mode = *(s16 *)obj->vars.enemy.unk_26E;
    if (mode < 0xD) {
        if (mode >= 8) {
            obj->unk_1B7 = 1;
            return;
        }
    }
    if ((u8)obj->unk_1B7 == 0) {
        obj->roll += 4;
        obj->yaw += 8;
        obj->vy += 0x400;
        return;
    }
    if (obj->roll > 0) {
        obj->roll -= 8;
    }
}

extern u16 enemy_buffer_src[];
extern s16 *enemy_buffer_table[];
// Copies the 10-halfword source block into the buffers listed in enemy_buffer_table,
// starting at slot idx.
void enemy_buffers_fill(s32 idx) {
    u16 *src;
    s16 **dst;
    s16 **table;

    if (idx < 10) {
        table = enemy_buffer_table;
        dst = table + idx;
        src = enemy_buffer_src;
        do {
            **dst = *src;
            src++;
            dst++;
            idx++;
        } while (idx < 10);
    }
}

extern ScriptStep enemy_type_table_a[];
extern ScriptStep enemy_type_table_b[];
extern StateEntry enemy_state_table[14]; /* [13].index is the script of the fall state, set per enemy type (enemy_setup_update) */
void enemy_buffers_fill(s32 idx);
void obj_state_sound_play(Object *obj, ObjHandler *h);
void enemy_setup_update(Object *obj, ObjHandler *h) {
    u32 idx = (u32)((s32)obj->type.pc - (s32)enemy_type_table_a) >> 3;

    idx = 9 - idx;

    if (idx >= 10) {
        idx = (u32)((s32)obj->type.pc - (s32)enemy_type_table_b) >> 3;
        if (idx >= 10) {
            idx = 0;
        }
    }
    enemy_state_table[13].index = idx + 10;
    enemy_buffers_fill(idx);
    obj->vz = 0;
    obj->vx = 0;
    obj_script_step(obj, h);
    obj->vars.enemy_place.unk_248 += 0x20;
    obj_state_sound_play(obj, h);
}

extern ModelPartList seq_slots[];
void obj_draw_pose(Object *obj) {
    Vec3 pos;
    SVECTOR rot2;
    SVECTOR aim;
    SVECTOR rot;
    SVECTOR rot3;
    s32 *first;
    s32 model;
    s32 colour;
    s32 id;
    s32 type_offset;
    s32 pitch;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot2.vx = -pitch;
    rot2.vy = obj->yaw;
    rot2.vz = obj->roll;
    if (test_bit(obj->flags, 6)) {
        type_offset = obj->type.unk_0E;
        model = type_offset + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        model = obj_keyframe_value(obj, 0);
    }
    colour = 0;
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    }
    pchr_lists_build(model);
    model = pchr_copy_slot(model);
    first = pchr_poses_build(model);
    seq_slots[model & 0x7FF].first = first;
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    pose_transform_vec((u8 *)first, 0xC, &rot);
    rot3.vx = obj->vars.enemy_place.unk_24C - (u16)obj->pitch;
    rot3.vy = (u16)obj->vars.enemy_place.unk_24A - (u16)obj->yaw;
    rot3.vz = 0;
    pose_rotate_range(first, 0xC, 1, &rot, &rot3);
    pose_rotate_range(first, 9, 1, &rot, &rot3);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    pose_transform_vec((u8 *)first, 0xA, &rot);
    rot3.vx = obj->vars.enemy_place.unk_254 - (u16)obj->pitch;
    rot3.vy = (u16)obj->vars.enemy_place.unk_252 - (u16)obj->yaw;
    rot3.vz = 0;
    pose_rotate_range(first, 0xA, 1, &rot, &rot3);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    pose_transform_vec((u8 *)first, 0xB, &rot);
    rot3.vx = (u16)obj->vars.enemy_place.unk_250 - (u16)obj->pitch;
    rot3.vy = (u16)obj->vars.enemy_place.unk_24E - (u16)obj->yaw;
    rot3.vz = 0;
    pose_rotate_range(first, 0xB, 1, &rot, &rot3);
    spark_add(pos.x, pos.y, pos.z, rot2.vy, rot2.vx, rot2.vz, model, colour);
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    aim.vx = obj->width;
    aim.vy = obj->height;
    aim.vz = obj->unk_1E8[0];
    aim_marker_draw(2, &aim, &pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

extern s32 D_80120900;
extern s16 enemy_death_started_flag;
extern s32 enemy_death_sound_id;
extern s16 enemy_death_sound_flag;
extern StateEntry enemy_death_state_table[];
void obj_free_and_respawn(Object *obj);

/* Death handler (obj->unk_170) of the enemies enemy_place_spawn makes: bursts of
   effects around the body, its sounds stopped, then the meter update and respawn.
   The first burst reads pos before it is set, as the original does. */
s32 enemy_death_sequence(Object *obj) {
    VECTOR pos;
    SVECTOR rot;
    s32 dx, dy, dz;
    s16 phase;
    s32 pitch;

    dx = rand_a_next() % 512;
    do { /* raises dy's register priority */
        dy = rand_a_next() % 512;
    } while (0);
    dz = rand_a_next() % 512;
    D_80120900 = 1;
    meter_set_mode(0);
    set_d_801202C8(0);
    if (enemy_death_started_flag == 0) {
        enemy_death_started_flag = 1;
        *(s16 *) obj->vars.enemy.unk_26E = obj->next_state;
        spawn_effect(pos.vx + dx, pos.vy - dy - 0x380, pos.vz + dz, 0x80007F01);
        spawn_effect(pos.vx - dx, pos.vy - dy - 0x380, pos.vz - dz, 0x80000002);
        spawn_effect(pos.vx, pos.vy - 0x380, pos.vz, 0x80007F00);
        spawn_effect(pos.vx, pos.vy - 0x400, pos.vz, 0x80000001);
        spawn_effect(pos.vx, pos.vy - 0x480, pos.vz, 0x80007F02);
        enemy_death_sound_id = sound_start(SND_ENEMY_DEATH | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        sound_attach(enemy_death_sound_id, &obj->x, NULL);
        enemy_death_sound_flag = 1;
        obj_actors_clear_index();
    }
    phase = *(s16 *) obj->vars.enemy.unk_26E;
    if (phase < 13) {
        if (phase >= 8) {
            obj->unk_1B7 = 1;
            goto dying;
        }
    }
    obj->next_state = 13;
    pos.vx = obj->x >> 12;
    pos.vy = obj->y >> 12;
    pos.vz = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    obj->state_table = enemy_death_state_table;
    if (rand_a_next() % 3 == 0) {
        if ((*(u16 *) obj->vars.enemy.unk_260 ^= 1) == 0) {
            s32 kind = 0x80007F00;
            s32 rise = dy + 0x200;
            spawn_effect(pos.vx + dx, pos.vy - rise, pos.vz + dz, kind);
        } else {
            s32 kind = 0x80000001;
            s32 rise = dy + 0x200;
            spawn_effect(pos.vx - dx, pos.vy - rise, pos.vz - dz, kind);
        }
    }
    if (rand_a_next() % 10 == 0 && *(s16 *) obj->vars.enemy.unk_260 == 0) {
        particle_spawn_burst(pos.vx, pos.vy, pos.vz, 1);
    }
    goto stop_sounds;

dying:
    obj->next_state = 13;
    pos.vx = obj->x >> 12;
    pos.vy = obj->y >> 12;
    pos.vz = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    if (rand_a_next() % 5 == 0) {
        if ((*(u16 *) obj->vars.enemy.unk_260 ^= 1) == 0) {
            s32 kind = 0x80007F00;
            s32 rise = dy + 0x200;
            spawn_effect(pos.vx + dx, pos.vy - rise, pos.vz + dz, kind);
        } else {
            s32 kind = 0x80000001;
            s32 rise = dy + 0x200;
            spawn_effect(pos.vx - dx, pos.vy - rise, pos.vz - dz, kind);
        }
    }
    if (enemy_loop_sound_flag == 1) {
        sound_stop(enemy_loop_sound_id);
        enemy_loop_sound_id = 0;
        enemy_loop_sound_flag = 0;
    }
    if (enemy_alarm_sound_flag == 1) {
        sound_stop(enemy_alarm_sound_id);
        enemy_alarm_sound_id = 0;
        enemy_alarm_sound_flag = 0;
    }
    if (obj->type.unk_0E != 0x58) {
        return 1;
    }
stop_sounds:
    if (enemy_loop_sound_flag == 1) {
        sound_stop(enemy_loop_sound_id);
        enemy_loop_sound_id = 0;
        enemy_loop_sound_flag = 0;
    }
    if (enemy_death_sound_flag == 1) {
        sound_stop(enemy_death_sound_id);
        enemy_death_sound_id = 0;
        enemy_death_sound_flag = 0;
    }
    if (enemy_alarm_sound_flag == 1) {
        sound_stop(enemy_alarm_sound_id);
        enemy_alarm_sound_id = 0;
        enemy_alarm_sound_flag = 0;
    }
    meter_set_mode(0);
    if (obj->unk_1B7 != 0) {
        if (obj->roll <= 0) {
            meter_set(obj->health, obj->vars.enemy.walk_state * 100 / 80);
            obj_free_and_respawn(obj);
            return 0;
        }
        return 1;
    }
    return 1;
}

/* Per-frame update of a hit object: the health drain for its index (halved
   unless flag 0x2000 is set), the hit cooldown and the hit record. */
void obj_hit_apply_damage(Object *obj) {
    s16 amount;
    u8 cooldown;

    if (obj_hit_get_unk0c(obj->index) & 0x2000) {
        amount = obj_hit_damage(obj->index);
    } else {
        amount = (obj_hit_damage(obj->index) * 0x50) / 100;
    }
    cooldown = obj->hit_cooldown;
    if (cooldown != 0) {
        obj->hit_cooldown = cooldown + 0xFF; /* minus one, as a byte */
    }
    if ((amount << 0x10) > 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        obj->health = (u16)(obj->health - amount);
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
}

/* Same code as obj_hit_handle (s01). */
void obj_hit_react(Object *obj, ObjHandler *handler) {
    if (obj->hit < 0) {
        obj->hit = 0;
    }
    obj_hit_apply_damage(obj);
    if (obj->health <= 0) {
        add_score(obj->score);
        if (obj->score != 0) {
            add_kill_count(1);
        }
        obj->score = 0;
        handler->state = 1;
        handler->request_flags = 8;
        return;
    }
    if (test_bit(obj->flags, 5)) {
        obj_block_lerp(obj, 0);
    }
}

/* Runs the object's hook at 0x170 (if set) with the object as its argument; returns its result, else 0. */
s32 obj_run_hook(Object *obj) {
    s32 (*hook)(Object *) = (s32 (*)(Object *))obj->callback;
    s32 result = 0;
    if (hook != NULL) {
        result = hook(obj);
    }
    return result;
}

extern ObjHandlerFn enemy_handler_table[];
void enemy_handler_run(Object *obj, ObjHandler *handler) {
    Object *self;
    ObjHandlerFn fn;

    self = obj;
loop:
    handler->request_flags = 0;
    fn = enemy_handler_table[handler->state];
    if (fn) {
        fn(obj, handler);
    }
    if (handler->request_flags != 0) {
        goto loop;
    }
    if (meter_get_mode() != 0) {
        meter_set(obj->health, self->vars.enemy.walk_state);
    } else {
        meter_set(obj->health, self->vars.enemy.walk_state * 100 / 80);
    }
}

extern s16 enemy_ai_enabled;

void enemy_handler_run_if_active(Object *obj, ObjHandler *handler) {
    if (enemy_ai_enabled == 1) {
        enemy_handler_run(obj, handler);
    }
}

extern ScriptCallEntry enemy_callback_table[];

extern u8 enemy_asset[];
extern s16 enemy_script_code[];
extern s16 *enemy_script_data[];
extern StateEntry enemy_state_table[14];
extern s16 *D_80118F58;
extern s32 D_80120900;
extern s32 shot_fired_flag;
extern s16 enemy_death_started_flag;
extern s32 enemy_death_sound_id;
extern s16 enemy_death_sound_flag;
extern s16 D_801208FC;
s32 enemy_death_sequence(Object *obj);
s32 enemy_place_spawn(Placement *placement) {
    Object *obj;
    s32 i;
    u8 *base;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) enemy_phase0;
    obj->handlers[1].fn = enemy_setup_update;
    obj->handlers[2].fn = enemy_handler_run_if_active;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) obj_draw_pose;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) enemy_death_sequence;
    obj->kind = placement->unk_00[5];
    obj->asset = enemy_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = enemy_callback_table;
    obj->state_table = enemy_state_table;
    script_start((Script *) obj, enemy_script_code, (s32) enemy_buffer_table);
    obj->script.data = enemy_script_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_80118F58;
    obj_init_from_place(obj, placement, 0x37);
    obj->speed = 0;
    obj_set_part_bounds(obj, 1, 0x1800);
    i = 3;
    base = (u8 *) obj + 6;
    obj->vars.enemy_place.unk_248 = 0;
    obj->vars.enemy_place.unk_24C = 0;
    obj->vars.enemy_place.unk_250 = 0;
    obj->vars.enemy.sound_channel[0] = 0;
    obj->vars.enemy.sound_channel[1] = 0;
    obj->vars.enemy_place.unused_258 = 0;
    obj->vars.enemy_place.unused_25A = 0;
    obj->vars.enemy_place.unused_25C = 0;
    obj->vars.enemy_place.unused_25E = 0;
    ((s16 *) obj->vars.enemy.unk_260)[0] = 0;
    ((s16 *) obj->vars.enemy.unk_260)[1] = 0x20;
    obj->vars.enemy_place.unk_24A = (u16) obj->yaw;
    obj->vars.enemy_place.unk_24E = (u16) obj->yaw;
    obj->vars.enemy_place.unk_252 = (u16) obj->yaw;
    do {
        *(s16 *) (base + 0x264) = 0;
        i -= 1;
        base -= 2;
    } while (i >= 0);
    obj->vy = 0;
    ((s16 *) obj->vars.enemy.unk_26E)[0] = 0;
    ((s16 *) obj->vars.enemy.unk_26E)[1] = 0;
    ((s16 *) obj->vars.enemy.unk_26E)[2] = 0;
    enemy_ai_enabled = 0;
    D_80120900 = 0;
    shot_fired_flag = 0;
    obj->vars.enemy.walk_state = (s16) (u16) obj->health;
    placement->unk_00[4] |= 4;
    obj_hit_set_unk08(obj->index, 0x2000);
    obj_hit_set_unk06(obj->index, 0xD);
    meter_set(obj->health, obj->vars.enemy.walk_state);
    enemy_sound_timer = 0;
    enemy_sound_5042_flag = 0;
    enemy_sound_5043_flag = 0;
    enemy_sound_5044_flag = 0;
    enemy_loop_sound_flag = 0;
    enemy_loop_sound_id = 0;
    enemy_alarm_sound_flag = 0;
    enemy_alarm_sound_id = 0;
    enemy_death_started_flag = 0;
    enemy_death_sound_id = 0;
    enemy_death_sound_flag = 0;
    D_801208FC = 0;
    obj_hit_flag_set(obj->index, 0x80);
    enemy_buffers_fill(0);
    return 1;
}

/* Index (0-3) of the first zero s16 in the four-entry table at obj+0x264, or -1 if none is zero. */
s32 obj_find_free_slot(Object *obj) {
    s16 *p = (s16 *)obj;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (p[0x264 / sizeof(s16)] == 0) {
            return i;
        }
        p++;
    }
    return -1;
}

s32 enemy_shot_spawn(Object *parent, s32 *pos, s16 *rot, s32 arg3);
void enemy_fire_shot(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 off[3];
    s32 slot;
    s32 *pp;
    s32 unused[2];
    s16 np;
    s32 yaw, pitch;

    off[0] = 0xF0;
    off[1] = -0x21C;
    off[2] = -0xF0;
    slot = obj_find_free_slot(obj);
    if (slot != -1) {
        u16 *vars = (u16 *)&obj->vars;

        rot[0] = vars[2];
        rot[1] = vars[1];
        rot[2] = 0;
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        pitch = obj->pitch;
        np = -pitch;
        rot[0] = np;
        yaw = obj->yaw;
        rot[1] = yaw;
        rot[2] = obj->roll;
        rotate_xz_twice(yaw, np, &off[0], &off[1], &off[2]);
        pos[0] += off[0];
        pos[1] += off[1];
        pos[2] += off[2];
        pp = pos;
        sound_play_at_units(SND_S03_ENEMY_FIRE | SND_GROUP(1), 0x60, 0x3C, pp);
        if (enemy_shot_spawn(obj, pp, rot, slot)) {
            *(s16 *)((u8 *)obj + slot * 2 + 0x264) = 1;
        }
    }
}

void enemy_twin_shot_fire(Object *obj, s32 arg, ShotAim *q)
{
    VECTOR player;
    s32 pos[3];
    ShotAim rot;
    s32 off_x;
    s32 off_y;
    s32 off_z;
    s32 yaw;
    s32 pitch;

    rot = *q;
    off_x = arg;
    off_y = -0x339;
    off_z = 0x20D;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    rotate_xz_twice(rot.b, rot.a, &off_x, &off_y, &off_z);
    pos[0] += off_x;
    pos[1] += off_y;
    pos[2] += off_z;
    player_position_copy(&player);
    vector_to_angles(player.vx - pos[0], player.vy - pos[1], player.vz - pos[2], &yaw, &pitch);
    if (ABS(obj->pitch - pitch) < 0x300) {
        rot.a = -pitch + (rand_a_next() % 20 - 10);
    }
    if (ABS(obj->yaw - yaw) < 0x300) {
        rot.b += rand_a_next() % 10 - 5;
    }
    shot_spawn_obj(pos, (u16 *)&rot, 1, 0x80001);
}

void spark_fx_spawn(Object *parent, s32 *pos, u16 *rot);

/* Spawns sparks with a sound at the object's position plus a body offset
   (x_offset, -0x124, 0x2AA) rotated by its angles and a fixed offset rotated by rot. */
void muzzle_fx_spawn(Object *self, s32 x_offset, s16 *rot) {
    Vec3 pos;
    s16 ang[3];
    Vec3 off[2];
    s32 pitch;
    s32 yaw;
    Vec3 *at;
    SVECTOR unused;

    pos.x = self->x >> 12;
    off[0].x = x_offset;
    pos.y = self->y >> 12;
    off[0].y = -0x124;
    pos.z = self->z >> 12;
    off[0].z = 0x2AA;
    off[1].x = 0;
    off[1].y = 0;
    pitch = self->pitch;
    off[1].z = 0x11D;
    ang[0] = -pitch;
    yaw = self->yaw;
    ang[1] = yaw;
    ang[2] = self->roll;
    rotate_xz_twice(yaw, (s16)-pitch, &off[0].x, &off[0].y, &off[0].z);
    rotate_xz_twice(rot[1], rot[0], &off[1].x, &off[1].y, &off[1].z);
    pos.x += off[0].x + off[1].x;
    pos.y += off[0].y + off[1].y;
    pos.z += off[0].z + off[1].z;
    at = &pos;
    sound_play_at_units(SND_MUZZLE_FIRE | SND_GROUP(1), 0x60, 0x3C, at);
    spark_fx_spawn(self, &at->x, (u16 *)rot);
}

void trace_shot_spawn(Object *owner, s32 *pos, u16 *rot);
void enemy_fire_trace(Object *obj)
{
    VECTOR target;
    VECTOR pos;
    u16 rot[4];
    s32 off_x;
    s32 off_y;
    s32 off_z;
    s32 yaw;
    s32 pitch;
    s32 neg_pitch;
    s32 yaw_in;

    pos.vx = obj->x >> 12;
    off_x = 0;
    pos.vy = obj->y >> 12;
    off_y = -0x29B;
    pos.vz = obj->z >> 12;
    neg_pitch = -obj->pitch;
    off_z = 0xA5;
    rot[0] = neg_pitch;
    yaw_in = obj->yaw;
    rot[1] = yaw_in;
    rot[2] = obj->roll;
    rotate_xz_twice(yaw_in, (s16)neg_pitch, &off_x, &off_y, &off_z);
    pos.vx += off_x;
    pos.vy += off_y;
    pos.vz += off_z;
    player_position_copy(&target);
    vector_to_angles(target.vx - pos.vx, target.vy - pos.vy, target.vz - pos.vz, &yaw, &pitch);
    {
        s32 unused[2]; /* never used; only pads the frame to 0x68 */
        if (ABS(obj->pitch - pitch) < 0x300) {
            rot[0] = -pitch;
        }
        if (ABS(obj->yaw - yaw) < 0x300) {
            rot[1] = yaw;
        }
    }
    trace_shot_spawn(obj, &pos.vx, rot);
    shot_fired_flag = 1;
}

void TransMatrix(void *mat, Vec3 *pos);

/* Rotates the vector v by the pose record table[index] (position and angles), in place. */
void pose_transform_vec(u8 *table, s32 index, SVECTOR *v) {
    s32 offset = index * 12;
    PosRot12 *rec;
    u8 *mat;
    SVECTOR ang;
    Vec3 pos;
    s32 mx, my, mz;

    offset += 4;
    rec = (PosRot12 *)(table + offset);
    pos.x = rec->x;
    pos.y = rec->y;
    pos.z = rec->z;
    mat = scratch_alloc(0x20);
    TransMatrix(mat, &pos);
    ang.vx = rec->ax;
    ang.vy = rec->ay;
    ang.vz = rec->az;
    rot_matrix(mat, ang.vy, ang.vx, ang.vz);
    SetRotMatrix(mat);
    SetTransMatrix(mat);
    gte_load(VXY0, v, 0);
    gte_load(VZ0, v, 4);
    gte_rtv0tr();
    gte_get(MAC1, mx);
    gte_get(MAC2, my);
    gte_get(MAC3, mz);
    scratch_top -= 0x20;
    v->vx = mx;
    v->vy = my;
    v->vz = mz;
}


/* Turns the left (mode 0, unk_254) or right (mode 1, unk_250) gun toward the
   player when it is within 0x100 of the body pitch; returns the yaw from the
   gun's muzzle (offset (+-0x357, -0x124, 0x2AA) rotated by the body) to the player. */
s32 muzzle_aim_yaw(Object *obj, s32 mode) {
    Vec3 pos;
    s16 rot[3];
    MuzzleAim aim;
    SVECTOR unused;
    Vec3 *player;
    s32 diff;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 pitch;
    s32 yaw;

    player = (Vec3 *)player_position();
    aim.off.y = -0x124;
    aim.off.x = 0;
    aim.off.z = 0x2AA;
    aim.off.x = mode == 0 ? -0x357 : 0x357;
    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    yaw = obj->yaw;
    rot[1] = yaw;
    rot[2] = obj->roll;
    rotate_xz_twice(yaw, (s16)-pitch, &aim.off.x, &aim.off.y, &aim.off.z);
    pos.x += aim.off.x;
    pos.y += aim.off.y;
    pos.z += aim.off.z;
    dz = player->z - pos.z;
    dx = player->x - pos.x;
    dy = player->y - pos.y;
    vector_to_angles(dx, dy, dz, &aim.yaw, &aim.pitch);
    diff = obj->pitch - aim.pitch;
    if (diff >= 0 ? diff < 0x100 : aim.pitch - obj->pitch < 0x100) {
        if (mode == 0) {
            obj->vars.h.unk_254 = angle_approach(obj->vars.h.unk_254, -aim.pitch, 0x18);
        } else {
            obj->vars.h.unk_250 = angle_approach((s16)obj->vars.h.unk_250, -aim.pitch, 0x18);
        }
    }
    return aim.yaw;
}

extern s16 enemy_ai_enabled;

void area_load_start(void) {
    enemy_ai_enabled = 1;
    area_load_request(0x50);
}

extern s32 D_80120900;

s32 get_pause_flag(void) {
    return D_80120900;
}

extern s32 shot_fired_flag;

s32 take_shot_fired(void) {
    s32 temp_v0;

    temp_v0 = shot_fired_flag;
    shot_fired_flag = 0;
    return temp_v0;
}

/* Follower object: copies its parent's position each frame, runs its phase machine
 * (state at unk_250, phase counter at unk_24C), and frees itself once finished. */
void enemy_child_update(Object *obj, ObjHandler *handler) {
    s16 finished;
    s16 state;

    finished = ((Object *)obj->vars.enemy_spawn_child_obj.parent)->next_state == 0xD;
    obj->x = ((Object *)obj->vars.enemy_spawn_child_obj.parent)->x;
    obj->y = ((Object *)obj->vars.enemy_spawn_child_obj.parent)->y;
    obj->z = ((Object *)obj->vars.enemy_spawn_child_obj.parent)->z;
    state = obj->vars.enemy_spawn_child_obj.phase;
    switch (state) {
    case 0:
        if (obj->vars.enemy_spawn_child_obj.progress >= 0x1000) {
            obj->vars.enemy_spawn_child_obj.phase = 1;
            obj->vars.enemy_spawn_child_obj.progress = 0;
            obj->vars.enemy_spawn_child_obj.progress_step = 0x24;
        } else {
            obj->vars.enemy_spawn_child_obj.progress += obj->vars.enemy_spawn_child_obj.progress_step;
        }
        break;
    case 1:
        if (take_shot_fired()) {
            obj->vars.enemy.sound_channel[0] = 1;
            obj->vars.enemy_spawn_child_obj.progress = 0;
            obj->vars.enemy.sound_channel[1] = 0;
            obj->vars.enemy_spawn_child_obj.progress_step += 0x12;
        }
        if (obj->vars.enemy.sound_channel[1] < 0x1000) {
            obj->vars.enemy.sound_channel[1] += 0xAA;
        } else {
            obj->vars.enemy.sound_channel[0] = 0;
        }
        if (obj->vars.enemy_spawn_child_obj.progress < 0x1000) {
            obj->vars.enemy_spawn_child_obj.progress += obj->vars.enemy_spawn_child_obj.progress_step;
        } else {
            finished = 1;
        }
        break;
    }
    if (finished) {
        obj_free(obj);
    }
}


static inline s32 beam_colour(s32 blue, s32 green, s32 red) {
    red >>= 5;
    blue >>= 5;
    green >>= 5;
    if ((blue | green | red) == 0) {
        red = 1;
    }
    return (red << 16) | (green << 8) | blue;
}


void enemy_beam_draw(Object *obj, ObjHandler *handler) {
    s32 model = obj->vars.enemy_spawn_child_obj.model;
    Vec3 pos;
    struct { s16 x, y, z; } rot;
    s32 yaw, pitch;
    Vec3 off;
    s32 unused[2];
    s32 level, raw, blue;
    s32 colour, colour2;
    s32 value, value2;
    Object *src;

    colour = 0;
    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    off.x = 0;
    src = obj->vars.trace.from;
    off.y = -0x29B;
    pitch = src->pitch;
    off.z = 0xB4;
    rot.x = -pitch;
    yaw = src->yaw;
    rot.y = yaw;
    rot.z = (u16)src->roll;
    rotate_xz_twice(yaw, -rot.x, &off.x, &off.y, &off.z);
    value = model + 0x95;
    pos.x += off.x;
    pos.y += off.y;
    pos.z += off.z;
    value2 = value;
    switch ((s16)obj->vars.enemy_spawn_child_obj.phase) {
    case 0:
        /* the (u32) keeps the division in int (no s16 shortening) */
        blue = (s32)(u32)obj->vars.enemy_spawn_child_obj.progress / 4;
        level = (s16)obj->vars.enemy_spawn_child_obj.progress;
        colour = beam_colour(blue, level, level / 8);
        value = pchr_blend(value, model + 0x96, 0x1000 - level, 0);
        break;
    case 1:
        blue = (0x1000 - obj->vars.enemy_spawn_child_obj.progress) / 4;
        level = 0x1000 - obj->vars.enemy_spawn_child_obj.progress;
        colour = beam_colour(blue, level, level / 8);
        model += 0x96;
        value = pchr_blend(model, value, level, 0);
        if (obj->vars.enemy_spawn_child_obj.unk_254 != 0) {
            raw = 0x1000 - obj->vars.enemy_spawn_child_obj.unk_256;
            blue = raw * 0x600 / 0x1000;
            level = raw;
            colour2 = beam_colour(blue, level, level / 4);
            value2 = pchr_blend(model, value2, level, 0);
            spark_add(pos.x, pos.y, pos.z, 0, 0x800, 0, value2, colour2);
        }
        break;
    }
    spark_add(pos.x, pos.y, pos.z, 0, 0x800, 0, value, colour);
}

void enemy_child_update(Object *obj, ObjHandler *handler);
void enemy_beam_draw(Object *obj, ObjHandler *handler);
void enemy_spawn_child(Object *parent) {
    Object *obj;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = enemy_child_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = enemy_beam_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj->vars.enemy.mode = model_slot_pchr(*(s32 *)parent->asset);
        obj->vars.enemy_spawn_child_obj.parent = (s32)parent;
        obj->vars.enemy_spawn_child_obj.progress = 0;
        obj->vars.enemy_spawn_child_obj.unused_24E = 0;
        obj->vars.enemy_spawn_child_obj.phase = 0;
        obj->vars.enemy_spawn_child_obj.progress_step = 0x16;
        obj->vars.enemy.sound_channel[0] = 0;
        obj->vars.enemy.sound_channel[1] = 0;
    }
}

static inline void ramp_level(s16 *level, s32 step) {
    s16 cur = *level;
    if (cur < 0x1000) {
        *level = cur + step;
    }
}
void enemy_beeper_update(Object *obj, ObjHandler *handler) {
    s16 done;
    s32 x;
    Object *target;

    target = obj->vars.follow.target;
    x = target->x;
    done = target->next_state == 0xD;
    obj->x = x;
    obj->y = obj->vars.follow.target->y;
    obj->z = obj->vars.follow.target->z;
    ramp_level(&obj->vars.follow.unk_24E, 0x19);
    switch (obj->vars.follow.phase) {
    case 0:
        if (obj->vars.follow.level < 0x1000) {
            ramp_level(&obj->vars.follow.level, 0x6B);
        } else {
            obj->vars.follow.phase = 1;
            obj->vars.follow.level = 0;
        }
        break;
    case 1:
        if (obj->vars.follow.level < 0x1000) {
            ramp_level(&obj->vars.follow.level, 0x40);
        } else {
            obj->vars.follow.phase = 2;
            obj->vars.follow.level = 0;
        }
        break;
    case 2:
        if (obj->vars.follow.level < 0x1000) {
            ramp_level(&obj->vars.follow.level, 0x40);
        } else {
            done = 1;
        }
        break;
    }
    sound_set_volume(obj->vars.follow.sound, sound_volume_of(SND_ENEMY_BEEPER_LOOP | SND_HELD | SND_GROUP(1), 0x1000 - obj->vars.follow.level));
    if (done) {
        sound_stop(obj->vars.follow.sound);
        obj->vars.follow.sound = 0;
        obj_free(obj);
    }
}

void beeper_spark_draw(Object *obj, ObjHandler *handler) {
    s32 model = obj->vars.enemy_spawn_beeper_obj.unk_248;
    Vec3 pos;
    struct { s16 x, y, z; } rot;
    s32 yaw, pitch;
    Vec3 off;
    s32 unused[2];
    s32 red;
    s32 shade, colour;
    Object *src;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    off.x = 0;
    src = obj->vars.trace.from;
    off.y = -0x29B;
    pitch = src->pitch;
    off.z = 0xB4;
    rot.x = -pitch;
    yaw = src->yaw;
    rot.y = yaw;
    rot.z = (u16)src->roll;
    rotate_xz_twice(yaw, -rot.x, &off.x, &off.y, &off.z);
    pos.x += off.x;
    pos.y += off.y;
    pos.z += off.z;
    shade = obj->vars.enemy_spawn_beeper_obj.unk_24E >> 5;
    red = shade;
    if (shade == 0) {
        red = 1;
    }
    colour = (red << 16) | (shade << 8) | shade;
    switch (obj->vars.enemy_spawn_beeper_obj.unk_250) {
    case 0:
        model = pchr_blend(model, model + 1, 0x1000 - obj->vars.enemy_spawn_beeper_obj.blend_factor, 0);
        break;
    case 1:
        model = pchr_blend(model + 1, model + 2, 0x1000 - obj->vars.enemy_spawn_beeper_obj.blend_factor, 0);
        break;
    case 2:
        model = pchr_blend(model + 2, model + 3, 0x1000 - obj->vars.enemy_spawn_beeper_obj.blend_factor, 0);
        break;
    }
    spark_add(pos.x, pos.y, pos.z, rot.y, rot.x, rot.z, model, colour);
}

void enemy_beeper_update(Object *obj, ObjHandler *handler);
void beeper_spark_draw(Object *obj, ObjHandler *handler);
void enemy_spawn_beeper(Object *parent, s32 variant) {
    Object *obj;
    s32 handle;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = enemy_beeper_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = beeper_spark_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        if (variant == 0) {
            obj->vars.enemy_spawn_beeper_obj.unk_248 = model_slot_pchr(*(s32 *)parent->asset) + 0x98;
        } else {
            obj->vars.enemy_spawn_beeper_obj.unk_248 = model_slot_pchr(*(s32 *)parent->asset) + 0x9C;
        }
        obj->vars.enemy_spawn_beeper_obj.parent = (s32)parent;
        obj->vars.enemy_spawn_beeper_obj.blend_factor = 0;
        obj->vars.enemy_spawn_beeper_obj.unk_24E = 0;
        obj->vars.enemy_spawn_beeper_obj.unk_250 = 0;
        handle = sound_start(SND_ENEMY_BEEPER_LOOP | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        obj->vars.enemy_spawn_beeper_obj.unk_25C = handle;
        sound_attach(handle, &obj->x, NULL);
    }
}

extern s32 follow_offset_x_table[];
extern s32 follow_offset_z_table[];
s32 obj_angle_to_target(Object *obj) {
    VECTOR aim;
    s32 dx, dy, dz;

    Object *tgt = ((Object **)obj->vars.words)[5];
    dz = 0;
    dx = 0;
    dy = 0;
    dz = follow_offset_z_table[obj->vars.enemy_shot.follow_offset_index];
    dx = follow_offset_x_table[obj->vars.enemy_shot.follow_offset_index];
    rotate_xz_twice(tgt->yaw, tgt->pitch, &dx, &dy, &dz);
    aim.vx = (((Object **)obj->vars.words)[5]->x >> 12) + dx;
    aim.vz = (((Object **)obj->vars.words)[5]->z >> 12) + dz;
    dz = aim.vz - (obj->z >> 12);
    dx = aim.vx - (obj->x >> 12);
    return atan2(dz, dx);
}

void obj_yaw_approach_target(Object *obj, s16 step) {
    s32 old_yaw;
    s32 new_yaw;
    s32 turn;

    old_yaw = obj->yaw;
    new_yaw = angle_approach(obj->yaw, obj_angle_wobble(obj, (s16)obj_angle_to_target(obj)), step);
    turn = (s16)new_yaw - old_yaw;
    do { } while (0);
    obj->yaw = new_yaw;
    obj->turn = turn;
}

void part_free(Object *obj);
void bazooka_fire(Object *self);
extern long long __floatsidf(s32 x);
extern s32 __ltdf2(long long a, long long b);
/* Enemy shot step: rises, then bobs on a sine; trails smoke while rising, flies toward its target, and once the
 * player is within 1500 units of the parent (or the parent is in state 3) charges and fires a bazooka shot. */
void enemy_shot_update(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    s32 dz;
    s32 dx;
    s32 slot;
    Object *parent;
    s32 *player;
    s32 bob;
    s32 step;
    s32 vy;
    s32 dist;
    s32 half;
    long long fdist, limit;

    dz = 0;
    dx = 0;
    slot = get_model_slot_base() + 0x20;
    if (obj->vars.eshot.parent->next_state == 0xD) {
        obj->vars.eshot.unused_258 = -1;
        obj->health = -1;
        part_free(obj);
        return;
    }
    if ((s16)obj->vars.eshot.rise_time > 0) {
        vy = obj->vy;
        vy += 0x1000;
        obj->vy = vy;
        obj->vars.eshot.rise_time--;
    } else {
        bob = (s16)rcossin_tbl[obj->vars.eshot.bob_phase & 0xFFF] * 6;
        step = bob >> 12;
        if (bob < 0) {
            step = (bob + 0xFFF) >> 12;
        }
        obj->vy = step << 12;
        obj->vars.eshot.bob_phase += 0x2D;
    }
    if (obj->speed >= 5) {
        obj->speed--;
    }
    if ((s16)obj->vars.eshot.rise_time >= 0x38) {
        if ((obj->vars.eshot.smoke_toggle ^= 1) == 0) {
            pos.x = obj->x >> 12;
            pos.y = obj->y >> 12;
            pos.z = obj->z >> 12;
            effect_spawn_at(&pos, slot, 0xA, 8);
        }
    }
    obj_yaw_approach_target(obj, 0x20);
    fly_move(obj->yaw, obj->speed, &dz, &dx);
    parent = obj->vars.eshot.parent;
    obj->vx = dx;
    obj->vz = dz;
    player = player_position();
    half = (s16)parent->height / 2;
    dist = isqrt(length_sq(player[0] - (parent->x >> 12), player[1] - ((parent->y >> 12) - half),
                           player[2] - (parent->z >> 12)));
    if (obj->vars.eshot.parent->next_state == 3) {
        obj->vars.eshot.aiming = 1;
    } else {
        /* (double)dist < 1500.0 */
        fdist = __floatsidf(dist);
        limit = 0x4097700000000000LL;
        __asm__("" : "=r"(limit) : "0"(limit));
        if (__ltdf2(fdist, limit) < 0) {
            obj->vars.eshot.aiming = 1;
        }
    }
    if (obj->vars.eshot.aiming == 1) {
        if (obj->vars.eshot.charge > 0x1000) {
            bazooka_fire(obj);
            obj->vars.eshot.aiming = 0;
            obj->vars.eshot.charge = 0;
        }
        obj->vars.eshot.charge += 0x40;
    } else {
        obj->vars.eshot.charge = 0;
    }
}


/* Rotate the offset (x, y, z) by the angles in rot and add the result to pos. */
void pos_add_vec3_rotated(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    vec3_rotate(rot->vy, rot->vx, rot->vz, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}


void enemy_shot_draw(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    SVECTOR rot;
    SVECTOR aim;
    Vec3 pos2;
    SVECTOR rot2;
    s32 pitch;
    s32 neg_pitch;
    register s32 colour asm("$3");
    s32 colour2;
    s32 level;
    s32 low;
    s32 inv;
    s32 high;
    s32 model;
    s32 mode;
    s32 angle;
    s32 reach;
    s32 *player;
    s32 x, y, z;
    s32 count;
    SparkList *list;
    SparkList *head;
    SparkRec *spark;
    u8 *tail;
    u16 ry, rz;
    s32 rx;

    x = obj->x >> 12;
    pos.x = x;
    y = obj->y >> 12;
    pos.y = y;
    z = obj->z >> 12;
    pos.z = z;
    neg_pitch = -obj->pitch;
    rot.vx = neg_pitch;
    ry = obj->yaw;
    rot.vy = ry;
    rz = obj->roll;
    rot.vz = rz;
    mode = obj->vars.enemy.mode;
    colour = 0;
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    }
    rx = (s16)neg_pitch;
    count = spark_count;
    list = &spark_list;
    if (count < 0xFF) {
        spark = &list->items[count];
        head = list;
        __asm__("" : "=r"(head) : "0"(list));
        count++;
        spark_count = count;
        *(s32 *)spark->colour = colour;
        tail = head->tail[0];
        head->tail[0] = &spark->next;
        *tail = count;
        spark->next = 0;
        spark->x = x;
        spark->y = y;
        spark->z = z;
        spark->unk_12 = mode;
        spark->yaw = ry;
        spark->pitch = rx;
        spark->roll = rz;
    }
    if (obj->vars.enemy_shot.unk_254 == 1) {
        s16 level16;

        reach = 0x4B;
        model = get_model_slot_base() + 0xF;
        level16 = obj->vars.enemy_shot.unk_256;
        level = level16;
        inv = 0x1000 - level;
        high = ((level * 0x1C00 + inv * 0x200) / 0x1000) >> 5;
        low = level >> 5;
        if ((low | high) == 0) {
            high = 1;
        }
        colour2 = (high << 16) | (low << 8) | low;
        model = pool_spawn_scaled(model, level, level, 0x1000);
        player = player_position();
        angle = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
        pos2.x = obj->x >> 12;
        pos2.y = obj->y >> 12;
        pos2.z = obj->z >> 12;
        pitch = obj->pitch;
        rot2.vx = -pitch;
        rot2.vy = obj->yaw;
        rot2.vz = obj->roll;
        rot2.vy = angle;
        pos_add_vec3_rotated(&pos2, &rot2, 0, -reach, reach);
        spark_add(pos2.x, pos2.y, pos2.z, 0, 0, 0, model, colour2);
        pos2.x = obj->x >> 12;
        pos2.y = obj->y >> 12;
        pos2.z = obj->z >> 12;
        {
            s32 pitch2 = obj->pitch;
            rot2.vx = -pitch2;
        }
        rot2.vy = obj->yaw;
        rot2.vz = obj->roll;
        rot2.vy = angle;
        pos_add_vec3_rotated(&pos2, &rot2, 0, -reach, reach);
        spark_add(pos2.x, pos2.y, pos2.z, 0, 0, 0, model, colour2);
    }
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    aim.vx = obj->width;
    aim.vy = obj->height;
    aim.vz = obj->unk_1E8[0];
    aim_marker_draw(2, &aim, &pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

/* Frees a part object: spawns an effect and a pchr object at its position,
 * clears a halfword in the body's table, then frees the part. */
void part_free(Object *obj) {
    struct {
        s32 pos[3];
        s32 pad;
        s16 rot[3];
    } spawn;
    u16 parent_yaw;
    s32 pitch;
    s32 *pos;

    parent_yaw = obj->vars.part.parent_yaw;
    spawn.pos[0] = obj->x >> 12;
    spawn.pos[1] = obj->y >> 12;
    spawn.pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    spawn.rot[0] = -pitch;
    spawn.rot[1] = obj->yaw;
    spawn.rot[2] = obj->roll;
    pos = spawn.pos;
    object_spawn_at(pos, spawn.rot, model_slot_pchr(*(s32 *)obj->asset) + 0xA5);
    particle_spawn_burst(spawn.pos[0], spawn.pos[1], spawn.pos[2], 0);
    spawn_effect(spawn.pos[0], spawn.pos[1], spawn.pos[2], 0);
    if (obj->vars.enemy_shot.unk_258 == 0) {
        obj->vars.part.body->vars.part.part_slots[(s16)parent_yaw] = 0;
    }
    obj_free(obj);
}

extern Words3 shot_asset;
extern s16 enemy_shot_script[];
extern s16 *D_801190A0[];
void enemy_shot_update(Object *obj, ObjHandler *handler);
void enemy_shot_draw(Object *obj, ObjHandler *handler);
s32 enemy_shot_spawn(Object *parent, s32 *pos, s16 *rot, s32 arg3) {
    Object *obj;
    s32 pchr;
    s32 speed;
    s32 vy;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
        obj->handlers[1].fn = enemy_shot_update;
        obj->handlers[2].fn = obj_state_run;
        obj->handlers[3].fn = enemy_shot_draw;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = (s32) &part_free;
        obj->kind = parent->kind;
        shot_asset = *(Words3 *) parent->asset;
        obj->asset = &shot_asset;
        script_start((Script *) obj, enemy_shot_script, (s32) &D_801190A0);
        obj_setup_flags(obj, 0x26);
        obj_set_part_bounds(obj, 0xA5, 0x733);
        obj_hit_clear(obj->index);
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->yaw = rot[1];
        obj->pitch = rot[0];
        obj->roll = rot[2];
        pchr = model_slot_pchr(((s32 *) parent->asset)[0]);
        speed = arg3 * 3;
        speed += 0x30;
        vy = -0x1E000;
        obj->vars.enemy_shot.unk_248 = pchr + 0xA5;
        obj->vars.enemy_shot.unused_24E = 0x400;
        obj->vars.enemy_shot.unused_250 = 0x46;
        obj->vars.enemy_shot.follow_offset_index = arg3;
        obj->vars.enemy_shot.unused_252 = 0;
        obj->vars.enemy.sound_channel[0] = 0;
        obj->vars.enemy.sound_channel[1] = 0;
        obj->vars.enemy_shot.unk_258 = 0;
        obj->vars.enemy_shot.parent = (s32) parent;
        obj->speed = speed;
        obj->vy = vy;
        obj->health = 0x190;
        return 1;
    }
    return 0;
}

void obj_update_snapshot(Object *obj, s32 flags);
void obj_setup_flags(Object *obj, s32 flags) {
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj_update_snapshot(obj, flags);
    obj->health = 0x190;
    obj->score = 0x258;
    obj->damage = 0x190;
    obj->unk_17B = 0;
    obj->placement = 0;
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}

// Sets up the object's snapshot flags from the caller's flags, refreshes the
// snapshot through obj_snapshot_save, then stores the final flags back into it.
void obj_update_snapshot(Object *obj, s32 flags) {
    ObjSnapshot *snap;
    s32 bits;
    s32 result;

    bits = ((flags & 0x10) == 0) << 4;
    snap = (ObjSnapshot *)obj->rot_angles;
    if (flags & 0x80) {
        bits |= 0x8;
    } else {
        bits |= 0x2;
    }
    obj_snapshot_save(obj, snap);
    result = bits;
    if (result & 0x10) {
        if (result & 0x80) {
            result |= 0x40;
        }
        if (result & 0x40) {
            result |= 0x20;
        }
    } else {
        result &= ~0x1F0;
    }
    snap->unk_10 = result;
    player_refresh_state_scratch(snap);
    obj_snapshot_restore(obj, snap);
}

void bazooka_rocket_spawn(s32 *pos, u16 *rot);
/* Aims a point from self towards the player and hands it to bazooka_rocket_spawn */
void bazooka_fire(Object *self) {
    s32 origin[3];
    s16 rot[3];
    s32 tilt;
    s32 aim[3];
    /* [0..1] yaw and pitch out of vector_to_angles, [2..4] offset rotated by them */
    s32 angles_offset[5];
    s32 *player;
    s32 x, y, z;

    player = player_position();
    x = self->x >> 12;
    origin[0] = x;
    y = self->y >> 12;
    origin[1] = y;
    z = self->z >> 12;
    origin[2] = z;
    tilt = self->pitch;
    angles_offset[1] = 0;
    angles_offset[0] = 0;
    angles_offset[2] = 0;
    rot[0] = -tilt;
    rot[1] = (u16)self->yaw;
    angles_offset[3] = -0x4B;
    rot[2] = (u16)self->roll;
    angles_offset[4] = 0x4B;
    vector_to_angles(x - player[0], y - player[1], z - player[2], &angles_offset[0], &angles_offset[1]);
    rot[1] = angles_offset[0] + 0x800;
    rot[0] = angles_offset[1];
    rotate_xz_twice((s16)rot[1], (s16)rot[0], &angles_offset[2], &angles_offset[3], &angles_offset[4]);
    aim[0] = angles_offset[2] + origin[0];
    aim[1] = angles_offset[3] + origin[1];
    aim[2] = angles_offset[4] + origin[2];
    sound_play_at_units(SND_SHOT_FIRE_ALT | SND_GROUP(1), 0x7F, 0x3C, aim);
    bazooka_rocket_spawn(aim, (u16 *)rot);
}

void obj_expanding_blast_update(Object *self, ObjHandler *handler) {
    s32 *pos;
    s16 dist;
    s32 dx, dy, dz, half;

    if (get_pause_flag() == 0) {
        if (self->vars.obj_expanding_blast.progress < 0x1000) {
            self->vars.obj_expanding_blast.progress += 0x38;
        }
        self->vars.obj_expanding_blast.damage_radius += 0xA;
        pos = player_position();
        half = (s16)self->height / 2;
        dx = pos[0] - (self->x >> 12);
        dy = pos[1] - ((self->y >> 12) - half);
        dz = pos[2] - (self->z >> 12);
        dist = isqrt(length_sq(dx, dy, dz));
        if (self->vars.obj_expanding_blast.damage_radius >= dist) {
            set_collide_mode(1);
            hit_target_masked(0, 1, atan2(cam_pos_z - self->z, cam_pos - self->x), 0xF);
            set_collide_mode(0);
        }
        sound_set_volume(self->vars.obj_expanding_blast.sound_handle, sound_volume_of(-0x2FB52FB5, 0x1000 - self->vars.obj_expanding_blast.progress));
        if (self->vars.obj_expanding_blast.progress < 0x1000) {
            return;
        }
    }
    sound_stop(self->vars.obj_expanding_blast.sound_handle);
    self->vars.obj_expanding_blast.sound_handle = 0;
    obj_free(self);
}

static inline s32 rgb_from_fixed(s32 r, s32 g, s32 b) {
    r >>= 5;
    g >>= 5;
    b >>= 5;
    if ((r | g | b) == 0) {
        b = 1;
    }
    return (b << 16) | (g << 8) | r;
}
/* Adds two sparks at the object: colours and pool entries (base + 0xA0..0xA3) blended by the level at
 * vars.h.unk_24C (0..0x1000); the second entry is also scaled by the level. */
void obj_expanding_blast_draw(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    s32 unused[4];
    s16 rot[3];
    Object *self = obj;
    s32 base = obj->vars.obj_expanding_blast.unk_248;
    s32 level;
    s32 pitch;
    s32 fade;
    s32 entry;
    s32 value;
    s32 colour;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    entry = base + 0xA0;
    level = obj->vars.obj_expanding_blast.progress;
    fade = 0x1000 - level;

    colour = rgb_from_fixed((fade * 0xC00) / 4096, (fade * 0x1C00 + level * 0x200) / 4096, (fade * 0xC00) / 4096);
    value = pchr_blend(entry + 1, entry, fade, 0);
    spark_add(pos[0], pos[1], pos[2], rot[1], -rot[0], rot[2], value, colour);

    colour = rgb_from_fixed((fade * 0xA00 + level * 0x200) / 4096, (fade * 0x1000 + level * 0x200) / 4096, fade / 2);
    value = pchr_blend(base + 0xA2, base + 0xA3, 0x1000 - self->vars.obj_expanding_blast.progress, 0);
    value = pool_spawn_scaled(value, self->vars.obj_expanding_blast.progress, self->vars.obj_expanding_blast.progress, self->vars.obj_expanding_blast.progress);
    spark_add(pos[0], pos[1], pos[2], rot[1], -rot[0], rot[2], value, colour);
}

void obj_expanding_blast_draw(Object *obj, ObjHandler *handler);
void obj_expanding_blast_spawn(Object *parent, s32 *pos) {
    u16 rot[4] = {0, 0, 0, 0};
    Object *obj;
    s32 handle;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = obj_expanding_blast_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = obj_expanding_blast_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_hit_clear(obj->index);
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        obj->vars.obj_expanding_blast.unk_248 = parent->vars.obj_expanding_blast.unk_248;
        obj->vars.obj_expanding_blast.progress = 0;
        obj->vars.obj_expanding_blast.damage_radius = 0;
        handle = sound_start(0xD04AD04B, 0x60, 0, 0);
        obj->vars.obj_expanding_blast.sound_handle = handle;
        sound_attach(handle, &obj->x, NULL);
    }
}

void trace_shot_update(Object *obj, ObjHandler *handler) {
    VECTOR from;
    VECTOR to;
    VECTOR hit;
    s16 target;
    s16 aim;

    if (get_pause_flag() != 0) {
        goto kill;
    }
    from.vx = obj->x >> 12;
    from.vy = obj->y >> 12;
    from.vz = obj->z >> 12;
    to.vx = ((obj->x + obj->vx) >> 12) + obj->vars.words[1];
    to.vy = ((obj->y + obj->vy) >> 12) + obj->vars.words[2];
    to.vz = ((obj->z + obj->vz) >> 12) + obj->vars.words[3];
    if (cam_range_check(from.vx, from.vy, from.vz) == 0) {
        goto kill;
    }
    if (trace_world(8, 0x50, &from, &to, &hit) == 0) {
        goto miss;
    }
    obj_expanding_blast_spawn(obj, &hit.vx);

kill:
    obj->vars.words[5] = 1;
    goto update;

miss:
    set_collide_mode(1);
    if (trace_objects(&from, &to, 0x50, &hit, &target) != 0) {
        aim = atan2(hit.vz - from.vz, hit.vx - from.vx);
        hit_target_masked(target, 1, aim, 0x14);
        obj_expanding_blast_spawn(obj, &hit.vx);
        obj->vars.words[5] = 1;
    }
    set_collide_mode(0);
    if (obj->vars.h.unk_25A < 0x1000) {
        obj->vars.h.unk_25A += 0xAA;
    }
    sound_set_volume(obj->vars.words[6],
                     sound_volume_of(0xD04AD04B, obj->vars.h.unk_25A));

update:
    if (obj->vars.words[5] != 0) {
        sound_stop(obj->vars.words[6]);
        obj->vars.words[6] = 0;
        obj_free(obj);
    }
    obj->vars.h.unk_258 += 0x40;
    obj->z += obj->vz;
    obj->x += obj->vx;
    obj->y += obj->vy;
}

void trace_shot_draw(Object *obj, ObjHandler *handler) {
    Object *self = obj;
    s32 base = obj->vars.trace_shot.done;
    Vec3 pos;
    Vec3 tip;
    struct { s16 x, y, z; } rot;
    Vec3 off;
    s32 value;
    s32 pitch;
    s32 len;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.x = -pitch;
    rot.y = (u16)obj->yaw;
    rot.z = (u16)obj->roll;

    value = pchr_blend(base + 0x90, base + 0x91, 0x1000 - obj->vars.h.unk_25A, 0);
    spark_add(pos.x, pos.y, pos.z, rot.y, -rot.x, rot.z, value, 0);

    value = pool_spawn_scaled(base + 0x92, obj->vars.h.unk_25A, obj->vars.h.unk_25A, obj->vars.h.unk_25A);
    spark_add(pos.x, pos.y, pos.z, rot.y, -rot.x, rot.z + (s16)obj->vars.h.unk_258, value, 0);

    len = obj->vars.h.unk_25A * 0x15E;
    off.y = 0;
    off.x = 0;
    if (len < 0) {
        len += 0xFFF;
    }
    off.z = len >> 12;
    rotate_xz_twice(rot.y, -rot.x, &off.x, &off.y, &off.z);
    tip.x = pos.x + off.x;
    tip.y = pos.y + off.y;
    tip.z = pos.z + off.z;

    value = pool_spawn_scaled(base + 0x93, self->vars.h.unk_25A, self->vars.h.unk_25A, self->vars.h.unk_25A);
    spark_add(tip.x, tip.y, tip.z, 0, 0x800, 0, value, 0);
}

void trace_shot_draw(Object *obj, ObjHandler *handler);
void trace_shot_spawn(Object *owner, s32 *pos, u16 *rot) {
    s32 x;
    s32 y;
    s32 z;
    Object *obj;
    s32 handle;
    s32 yaw;
    s32 pitch;
    s32 speed;
    s32 *vel_x;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = trace_shot_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = trace_shot_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_hit_clear(obj->index);
        obj->speed = 0x46;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        obj->vars.trace_shot.done = model_slot_pchr(*(s32 *)owner->asset);
        yaw = obj->yaw;
        pitch = obj->pitch;
        speed = obj->speed;
        vel_x = &obj->vx;
        obj->vars.h.unk_25A = 0;
        obj->vars.h.unk_258 = 0;
        obj->vars.words[5] = 0;
        angles_to_vector(yaw, pitch, speed, vel_x, &obj->vy, &obj->vz);
        y = 0;
        x = 0;
        z = 0x13A;
        rotate_xz_twice(obj->yaw, obj->pitch, &x, &y, &z);
        obj->vars.words[1] = x;
        obj->vars.words[2] = y;
        obj->vars.words[3] = z;
        handle = sound_start(0xD04AD04B, 0x60, 0, 0);
        obj->vars.words[6] = handle;
        sound_attach(handle, &obj->x, NULL);
    }
}

/* Homing shot step: steers toward the player while steer_time lasts, moves,
 * explodes on the world or an object (damaging it), drops a trail. */
void homing_trail_update(Object *obj, ObjHandler *handler) {
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s32 trail[3];
    s32 here[3];
    s32 angles[2];
    s16 target;
    s16 pitch;
    s16 yaw;
    s32 cur;
    s32 speed;
    s32 tilt;
    u16 trail_time;
    s32 *player;
    s32 trail_model;

    trail_model = get_model_slot_base() + 0x20;
    player = player_position();
    if (get_pause_flag() != 0) {
        goto explode;
    }
    {
        u16 steer_time = obj->vars.homing.steer_time;
        obj->vars.homing.steer_time = steer_time - 1;
        if ((s16)steer_time > 0) {
            here[0] = obj->x >> 12;
            here[1] = obj->y >> 12;
            here[2] = obj->z >> 12;
            {
                s32 dz = player[2] - here[2];
                s32 dx = player[0] - here[0];
                vector_to_angles(dx, player[1] - here[1], dz, &angles[0], &angles[1]);
            }
            yaw = angle_approach(obj->yaw, angles[0], 8);
            cur = obj->pitch;
            tilt = angles[1];
            obj->yaw = yaw;
            pitch = angle_approach(cur, -tilt, 8);
            cur = obj->yaw;
            speed = obj->speed;
            obj->pitch = pitch;
            angles_to_vector(cur, pitch, speed, &obj->vx, &obj->vy, &obj->vz);
        }
        from[0] = obj->x >> 12;
        from[1] = obj->y >> 12;
        from[2] = obj->z >> 12;
        to[0] = (obj->x + obj->vx) >> 12;
        to[1] = (obj->y + obj->vy) >> 12;
        to[2] = (obj->z + obj->vz) >> 12;
        if (cam_range_check(from[0], from[1], from[2]) == 0) {
            goto done;
        }
        if (obj_hit_damage(obj->index) > 0) {
explode:
            spawn_effect(from[0], from[1], from[2], 0x80000000);
            goto done;
        }
        if (trace_world(8, 0x10, from, to, hit)) {
            spawn_effect(hit[0], hit[1], hit[2], 0);
            sound_play_at_units(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x60, 0x3C, hit);
done:
            obj->vars.homing.done = 1;
        } else {
            set_collide_mode(1);
            if (trace_objects(from, to, 0x10, hit, &target)) {
                hit_target_masked(target, 1, atan2(hit[2] - from[2], hit[0] - from[0]), 0xC);
                spawn_effect(hit[0], hit[1], hit[2], 0);
                sound_play_at_units(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x60, 0x3C, hit);
                obj->vars.homing.done = 1;
            }
            set_collide_mode(0);
            obj->z += obj->vz;
            obj->x += obj->vx;
            obj->y += obj->vy;
            trail_time = obj->vars.homing.trail_time;
            obj->vars.homing.trail_time = trail_time - 1;
            if ((s16)trail_time > 0) {
                obj->vars.homing.trail_toggle ^= 1;
                if (obj->vars.homing.trail_toggle == 0) {
                    trail[0] = obj->x >> 12;
                    trail[1] = obj->y >> 12;
                    trail[2] = obj->z >> 12;
                    effect_spawn_at((Vec3 *)trail, trail_model, 0xA, 8);
                }
            }
        }
    }
    if (obj->vars.homing.done != 0) {
        obj_free(obj);
    }
}

void spark_obj_draw(Object *obj) {
    s32 base = obj->vars.spark_fx.unk_248;
    s32 value = get_model_slot_base() + 0xE;
    Vec3 pos;
    struct { s16 x; u16 y, z; } rot;
    s32 pitch;
    s32 yaw, roll;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.x = -pitch;
    yaw = (u16)obj->yaw;
    rot.y = yaw;
    roll = (u16)obj->roll;
    rot.z = roll;
    spark_add(pos.x, pos.y, pos.z, yaw, -rot.x, roll, base, 0);
    spark_add(pos.x, pos.y, pos.z, 0, 0, 0, value, 0);
}

void homing_trail_update(Object *obj, ObjHandler *handler);
void spark_fx_spawn(Object *parent, s32 *pos, u16 *rot) {
    Object *obj;
    s32 frame_pad[6]; /* not used: the original's stack frame is 0x40 bytes */

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = homing_trail_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = (void (*)(Object *, ObjHandler *))spark_obj_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj_hit_clear(obj->index);
        obj->speed = 0x28;
        obj->x = pos[0] << 0xC;
        obj->y = pos[1] << 0xC;
        obj->z = pos[2] << 0xC;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        obj->vars.spark_fx.unk_248 = model_slot_pchr(*(s32 *)parent->asset) + 0x80;
        obj->vars.spark_fx.unused_24C = 0xA;
        obj->vars.spark_fx.unused_24E = 0x3C;
        obj->vars.spark_fx.unused_254 = 0;
        obj->vars.spark_fx.unused_250 = 0;
    }
}

/* Timed effect. Phase 0 counts pos (0x248) up by the step at 0x250 and mirrors it
 * to 0x24A; at 0x1000 it switches to phase 1. Phase 1 counts pos up by the step
 * at 0x252 and shows 0x1000 - pos; at the end it stops the sound in words[3]
 * (0x254) and frees the object. */
void timed_effect_update(Object *obj, ObjHandler *handler) {
    s16 phase;
    s16 pos;
    u16 step;

    phase = obj->vars.timed_effect.phase;
    switch (phase) {
    case 0:
        pos = (u16) obj->vars.timed_effect.progress + obj->vars.timed_effect.rise_step;
        obj->vars.timed_effect.progress = pos;
        obj->vars.timed_effect.level = (u16) pos;
        if (obj->vars.timed_effect.progress >= 0x1001) {
            obj->vars.timed_effect.progress = 0;
            obj->vars.timed_effect.phase += 1;
        }
        return;
    case 1:
        step = obj->vars.timed_effect.progress + obj->vars.timed_effect.fall_step;
        obj->vars.timed_effect.progress = step;
        obj->vars.timed_effect.level = 0x1000 - step;
        if ((s16) obj->vars.timed_effect.progress >= 0x1001) {
            sound_stop(obj->vars.timed_effect.sound_handle);
            obj->vars.timed_effect.sound_handle = 0;
            obj_free(obj);
        }
        break;
    }
}


void obj_scaled_spark_draw(Object *obj) {
    s32 product;
    s32 scale;
    s32 level;
    s32 channel;
    s32 colour;
    s32 pool_index;

    pool_index = get_model_slot_base() + 0xF;
    product = (s16)obj->vars.h.unk_24A * (s16)obj->vars.h.unk_24C;
    if (product < 0) {
        product += 0xFFF;
    }
    scale = product >> 12;
    pool_index = pool_spawn_scaled(pool_index, scale, scale, scale);

    level = (s16)obj->vars.h.unk_24A >> 5;
    channel = level ? level : 1;
    colour = (channel << 16) | (level << 8) | level;
    spark_add(obj->x, obj->y, obj->z, 0, 0, 0, pool_index, colour);
}


void obj_scaled_spark_draw(Object *obj);
s32 timed_effect_spawn(s32 *pos) {
    Object *obj;
    s16 *vars;
    s32 pos_z;
    s32 result;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = timed_effect_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[3].fn = obj_scaled_spark_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj_hit_clear(obj->index);
        obj_hit_flag_set(obj->index, 0);
        obj->unk_17A = 0;
        obj->x = pos[0];
        obj->y = pos[1];
        pos_z = pos[2];
        /* vars as s16 halfwords: [0..1] unk_248/unk_24A, [2] unk_24C, [3] unk_24E, [4] unk_250, [5] unk_252 */
        vars = (s16 *) &obj->vars;
        vars[2] = 0x1770;
        vars[4] = 0x400;
        vars[0] = 0;
        vars[1] = 0;
        vars[3] = 0;
        vars[5] = 0x100;
        obj->z = pos_z;
        sound_play_at_units(SND_BULLET_IMPACT | SND_GROUP(2), 0x60, 0x3C, pos);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}


void pos_add_rotated_offset_flipped(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    rotate_xz_twice(rot->vy, -rot->vx, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}

void spark_spawn_at_obj(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    SVECTOR rot;
    SVECTOR rot2;
    s32 value = *(s16 *)&obj->vars;
    s32 pitch, yaw, roll;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    yaw = obj->yaw;
    rot.vy = yaw;
    roll = (u16)obj->roll;
    rot.vz = roll;
    spark_add(pos.x, pos.y, pos.z, yaw + 0x800, rot.vx, roll, value, 0);
}
