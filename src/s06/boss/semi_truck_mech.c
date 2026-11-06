/* semi_truck_mech: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

extern GridEntry *flagged_grid_cells[];
/* Same code as get_key_table (s01). */
GridEntry **grid_get_flagged_cells(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 func_800C35CC(void) {
    return grid_flagged_count;
}

/* Advances the s32 at 0x20 (unk_1C.unk_04) by 2. */
void script_skip_op(Object *obj) {
    obj->script.pc++;
}

extern s32 interp_slot_a;
extern s32 interp_slot_b;

void interp_pair_set_a(void) {
    interp1c_set_state(interp_slot_a, 0);
    interp1c_set_state(interp_slot_b, 1);
}

extern s32 interp_slot_a;
extern s32 interp_slot_b;

void interp_pair_set_b(void) {
    interp1c_set_state(interp_slot_a, 1);
    interp1c_set_state(interp_slot_b, 0);
}

/* Sets or clears stage flag 0x8, depending on the argument. */
void set_stage_flag_8(s32 enable) {
    s32 flags;

    flags = get_stage_flags();
    if (enable != 0) {
        flags |= 0x8;
    } else {
        flags &= ~0x8;
    }
    set_stage_flags(flags);
}

void cam_turn_toward(Object *obj) {
    Vec3 pos;
    s32 yaw;
    s16 *cam;

    cam = view_angles_get();
    yaw = cam[1];
    yaw &= 0xFFF;
    if (yaw >= 0x801) {
        yaw -= 0x1000;
    }
    pos.x = obj->x >> 12;
    pos.z = obj->z >> 12;
    add_turn(angle_approach(yaw, player_angle_to(&pos), 0x20) - yaw);
}

void fx_system_stop(void);
void flow_speed_update(Object *obj) {
    s16 limit;
    s16 cap;
    s32 v;

    v = obj->vars.semi_truck_mech.unk_268;
    if (v < 0) {
        v = (obj->z >> 12) - obj->vars.semi_truck_mech.unused_258;
        set_stage_flag_8(1);
        cam_turn_toward(obj);
        fx_system_stop();
        if (get_meter_run_flag() == 1) {
            set_d_801202C8(0);
            meter_set_mode(0);
        }
        if (v < -0x2000 && obj->vars.semi_truck_mech.unk_268 == -1) {
            set_stage_end(3);
            obj->vars.semi_truck_mech.unk_268 = -2;
        }
    } else {
        if (mission_timer_get() <= 0 && obj->vars.semi_truck_mech.state != 8) {
            v--;
        } else {
            v++;
        }
        if (obj->vars.semi_truck_mech.state == 6) {
            obj->vars.semi_truck_mech.unk_276 = 0x38;
        } else if (obj->vars.semi_truck_mech.unk_276 > 0x20) {
            obj->vars.semi_truck_mech.unk_276 -= 4;
        }
        cap = obj->vars.semi_truck_mech.unk_276;
        v = MAX(MIN(v, cap), 0);
        obj->vars.semi_truck_mech.unk_268 = v;
        if (v == 0) {
            obj->vars.semi_truck_mech.unk_268 = -1;
        }
        set_flow_max(v);
    }
}

char str_bos6_tp2_clt[16] = "bos6_tp2.clt";

char str_bos6_tp1_clt[16] = "bos6_tp1.clt";

char str_bos6_tp0_clt[16] = "bos6_tp0.clt";

char str_bos6_ch0_clt[16] = "bos6_ch0.clt";

char str_bos6_tp2_xs3[16] = "bos6_tp2.xs3";

char str_bos6_tp0_xs3[16] = "bos6_tp0.xs3";

char str_bos6_tp1_xs3[16] = "bos6_tp1.xs3";

char str_bos6_ch3_vx1[16] = "bos6_ch3.vx1";

char str_bos6_ch2_vx1[16] = "bos6_ch2.vx1";

char str_bos6_ch1_vx1[16] = "bos6_ch1.vx1";

char str_bos6_ch0_vx1[16] = "bos6_ch0.vx1";

char str_bos6_ch2cb4[16] = "bos6_ch2.cb4";

char str_bos6_ch1cb4[16] = "bos6_ch1.cb4";

char str_bos6_ch0cb4[16] = "bos6_ch0.cb4";

void mech_approach_speed(Object *obj) {
    s32 *player = player_position();
    s32 py = player[2];
    s32 cur;
    s32 scaled;
    s32 dz;
    s16 state = obj->vars.semi_truck_mech.state;

    scaled = py - obj->vars.semi_truck_mech.unused_258;
    dz = (obj->z >> 12) - py;
    scaled <<= 12;
    switch (state) {
    case 0:
        break;
    case 5:
        obj->accel_z = -0x800;
        break;
    case 6:
        obj->accel_z = 0xC000;
        if (dz >= 0x3E8) {
            obj->vars.semi_truck_mech.state = 7;
        }
        break;
    case 7:
        if (dz < 0x4B0) {
            obj->accel_z = 0x200;
            if (dz < 0x3E8) {
                obj->accel_z = 0x800;
            }
            if (dz < 0x2BC) {
                obj->accel_z = 0x2000;
            }
        } else if (dz >= 0x709) {
            obj->accel_z = -0x2AA;
        } else {
            cur = obj->vz;
            /* the 0x80 / -0x80 stores are overwritten by the 0 below */
            if (cur < scaled - 0x2000) {
                obj->accel_z = 0x80;
            } else if (scaled + 0x2000 < cur) {
                obj->accel_z = -0x80;
            }
            obj->accel_z = 0;
        }
        break;
    case 1:
        if (dz < -0xFA0) {
            obj->accel_z = 0x200;
            if (dz < -0x1770) {
                obj->accel_z = 0x400;
            }
        } else if (dz >= -0xDAB) {
            obj->accel_z = -0x800;
            if (dz >= -0xCE3) {
                obj->accel_z = -0x2000;
            }
        } else {
            cur = obj->vz;
            if (cur < scaled) {
                obj->accel_z = 0x200;
            } else if (scaled < cur) {
                obj->accel_z = -0x200;
            } else {
                obj->accel_z = 0;
            }
        }
        break;
    case 2:
    case 3:
    case 4:
        if (dz < -0xA8C) {
            obj->accel_z = 0x200;
            if (dz < -0xFD2) {
                obj->accel_z = 0x400;
            }
        } else if (dz >= -0x897) {
            obj->accel_z = -0x800;
            if (dz >= -0x7CF) {
                obj->accel_z = -0x2000;
            }
        } else {
            cur = obj->vz;
            if (cur < scaled) {
                obj->accel_z = 0x200;
            } else if (scaled < cur) {
                obj->accel_z = -0x200;
            } else {
                obj->accel_z = 0;
            }
        }
        break;
    case 8:
        set_stage_end(2);
        meter_set_mode(0);
        obj->accel_z = 0x200;
        break;
    }
    obj->vars.semi_truck_mech.unused_258 = player[2];
    if (obj->vars.semi_truck_mech.unk_268 < 0) {
        obj->accel_z = -0x400;
    }
}

extern s32 get_walk_state(Object *obj);
extern void obj_set_state(void *obj, s32 new_state);
void mech_mode_update(Object *obj) {
    s32 *pos = player_position();

    switch (((MechModeVars *)obj)->mode) {
    case 0:
    case 6:
        break;
    case 4:
        switch (get_walk_state(obj)) {
        case 1:
            ((MechModeVars *)obj)->mode = 5;
            obj_set_state(obj, 1);
            ((MechModeVars *)obj)->timer = 0;
            break;
        case 3:
            obj_set_state(obj, 12);
            break;
        case 2:
            obj_set_state(obj, 10);
            break;
        }
        break;
    case 5:
        ((MechModeVars *)obj)->timer = ((MechModeVars *)obj)->timer + 1;
        if (((MechModeVars *)obj)->timer >= 0x61) {
            ((MechModeVars *)obj)->mode = 6;
        }
        break;
    case 1:
    case 2:
    case 3:
    case 7:
    case 8:
        switch (get_walk_state(obj)) {
        case 1:
            if (rand_a_next() > 0x800) {
                if (((MechModeVars *)obj)->prev_act == 10) {
                    obj_set_state(obj, 8);
                } else {
                    obj_set_state(obj, 9);
                }
            } else {
                if (((MechModeVars *)obj)->prev_act == 12) {
                    obj_set_state(obj, 9);
                } else {
                    obj_set_state(obj, 8);
                }
            }
            break;
        case 2:
            if (rand_a_next() < 0x400) {
                if (*pos >= -0x1B0) {
                    obj_set_state(obj, 10);
                } else {
                    obj_set_state(obj, 11);
                }
            } else {
                obj_set_state(obj, 11);
            }
            break;
        case 3:
            if (rand_a_next() > 0x400 && *pos < -0x8F) {
                obj_set_state(obj, 12);
            } else {
                obj_set_state(obj, 13);
            }
            break;
        }
        break;
    }
}

extern RecTemplate enemy_explode_fx_a, enemy_explode_fx_b;
void obj_sound_release(Object *obj);
void enemy_sound_halt(Object *obj);
void enemy_explode_timer(Object *obj) {
    s32 pos[3];
    u16 timer;

    if (obj->vars.enemy.target_yaw == 8) {
        timer = *(u16 *)&obj->vars.enemy.shot_timer + 1;
        *(u16 *)&obj->vars.enemy.shot_timer = timer;
        if ((s16) timer == 0xDC) {
            pos[0] = obj->x >> 12;
            pos[1] = obj->y >> 12;
            pos[2] = obj->z >> 12;
            fx_spawn_template(pos, &enemy_explode_fx_a, NULL);
            fx_spawn_template(pos, &enemy_explode_fx_b, NULL);
            obj_sound_release(obj);
            enemy_sound_halt(obj);
            sound_play(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x7F, 0xC0, 0x30);
            sound_play(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3F, 0x30);
            obj->vars.turn.yaw_offset = 0;
        }
    }
}

void mech_approach_speed(Object *obj);
void mech_mode_update(Object *obj);
void func_800CB288(void);
void enemy_explode_timer(Object *obj);
void flow_speed_update(Object *obj);
/* Runs the object's setup passes, then picks one of the two stage-flag helpers by the value at +0x21C (0x201 or more: interp_pair_set_a). */
void obj_update_passes(Object *obj) {
    mech_approach_speed(obj);
    mech_mode_update(obj);
    func_800CB288();
    enemy_explode_timer(obj);
    if (obj->accel_z >= 0x201) {
        interp_pair_set_a();
    } else {
        interp_pair_set_b();
    }
    flow_speed_update(obj);
}

extern s32 ring128_head;
extern s32 ring128_data[];
/* Push value into a 128-entry ring buffer; ring128_head is the write index. */
void ring128_push(s32 value) {
    s32 head;
    s32 next;
    s32 wrapped;

    head = ring128_head;
    next = head + 1;
    ring128_data[head] = value;
    ring128_head = next;
    wrapped = next;
    if (next < 0) {
        wrapped = head + 0x80;
    }
    ring128_head = next - ((wrapped >> 7) << 7);
}

s32 ring128_get_back(s32 arg0)
{
    s32 i = ring128_head - arg0;
    while (i < 0) {
        i += 0x80;
    }
    return ring128_data[i];
}

extern s32 ring128_data[];
extern s32 ring128_head;
void ring128_clear(void) {
    s32 *cursor;
    s32 remaining;

    cursor = ring128_data;
    remaining = 0x7F;
    do {
        *cursor = 0;
        remaining -= 1;
        cursor += 1;
    } while (remaining >= 0);
    ring128_head = 0;
}

s32 shot_sound_follow(void *obj, s32 arg) {
    s32 *pos = (s32 *)scratch_top;

    pos[0] = (*(ShotTarget **)((u8 *)obj + 0x260))->pos_x << 12;
    pos[1] = (*(ShotTarget **)((u8 *)obj + 0x260))->pos_y << 12;
    pos[2] = (*(ShotTarget **)((u8 *)obj + 0x260))->pos_z << 12;
    scratch_top += 0x10;
    sound_set_pos(arg, (Vec3 *)pos);
    sound_set_note(arg, 0x39);
    scratch_top -= 0x10;
    return 0;
}

/* If the object has no sound handle yet, starts sound 0x90A0 on it and attaches shot_sound_follow as its update. */
void shot_loop_sound_start(Object *obj) {
    s32 handle;

    if (obj->vars.snd.sound == 0) {
        handle = sound_start(SND_ENEMY_AIM_LOOP | SND_HELD, 0x46, 0, 0);
        if (handle != 0) {
            sound_set_flag_bit2(handle, 1);
            sound_attach(handle, obj, (void (*)())shot_sound_follow);
        }
        obj->vars.snd.sound = handle;
    }
}


void obj_sound_release(Object *obj) {
    s32 temp_a0;

    temp_a0 = obj->vars.snd.sound;
    if (temp_a0 != 0) {
        sound_stop(temp_a0);
        obj->vars.snd.sound = 0;
    }
}


void vec_from_polar(SVECTOR *out, s32 radius, s32 angle);
/* Aims shot sound/effect at the linked object's position plus an offset, then plays effect 0x39. */
s32 aim_sound_update_a(Object *obj, s32 arg) {
    AimSoundBuf *buf = scratch_alloc(sizeof(AimSoundBuf));
    SVECTOR *off = (SVECTOR *)scratch_top;
    Object *t;

    t = (Object *)obj->vars.semi_truck_mech.part_obj_second;
    scratch_top += 8;
    buf->src = *(AimPoint *)&t->vars.words[1];
    buf->dst = buf->src;
    vec_from_polar(off, 0x40D, ((Object *)obj->vars.semi_truck_mech.part_obj_second)->vars.enemy.unk_25E);
    buf->dst.w[0] += off->vx;
    buf->dst.w[1] += off->vy;
    buf->dst.w[2] += off->vz;
    sound_closest_point((Vec3 *)&buf->src, (Vec3 *)&buf->dst, &buf->out);
    buf->out.x <<= 12;
    buf->out.y <<= 12;
    buf->out.z <<= 12;
    sound_set_pos(arg, &buf->out);
    sound_set_note(arg, 0x39);
    scratch_top -= 0x38;
    return 0;
}

/* If the enemy has no sound handle yet, starts sound 0x90A0 on it and attaches aim_sound_update_a as its update. */
void enemy_loop_sound_start(Object *obj) {
    s32 handle;

    if (obj->vars.semi_truck_mech.unused_250 == 0) {
        handle = sound_start(SND_ENEMY_AIM_LOOP | SND_HELD, 0x46, 0, 0);
        if (handle != 0) {
            sound_set_flag_bit2(handle, 1);
            sound_attach(handle, obj, (void (*)())aim_sound_update_a);
        }
        obj->vars.semi_truck_mech.unused_250 = handle;
    }
}

void enemy_sound_halt(Object *obj) {
    if (obj->vars.semi_truck_mech.unused_250 != 0) {
        sound_stop(obj->vars.semi_truck_mech.unused_250);
        obj->vars.semi_truck_mech.unused_250 = 0;
    }
}

/* Aims shot sound/effect at the linked object's position plus an offset, then plays effect 0x39. */
s32 aim_sound_update_b(Object *obj, s32 arg) {
    AimSoundBuf *buf = scratch_alloc(sizeof(AimSoundBuf));
    SVECTOR *off = (SVECTOR *)scratch_top;
    Object *t;

    t = (Object *)obj->vars.semi_truck_mech.part_obj_first;
    scratch_top += 8;
    buf->src = *(AimPoint *)&t->vars.words[1];
    buf->dst = buf->src;
    vec_from_polar(off, 0x40D, ((Object *)obj->vars.semi_truck_mech.part_obj_first)->vars.enemy.unk_25E);
    buf->dst.w[0] += off->vx;
    buf->dst.w[1] += off->vy;
    buf->dst.w[2] += off->vz;
    sound_closest_point((Vec3 *)&buf->src, (Vec3 *)&buf->dst, &buf->out);
    buf->out.x <<= 12;
    buf->out.y <<= 12;
    buf->out.z <<= 12;
    sound_set_pos(arg, &buf->out);
    sound_set_note(arg, 0x39);
    scratch_top -= 0x38;
    return 0;
}

/* Starts the looping sound 0x90A0 for an object once, and stores its handle in vars.words[3] (0x254). */
void obj_loop_sound_start_w3(Object *obj) {
    s32 handle;

    if (obj->vars.semi_truck_mech.loop_sound_handle == 0) {
        handle = sound_start(SND_ENEMY_AIM_LOOP | SND_HELD, 0x46, 0, 0);
        if (handle != 0) {
            sound_set_flag_bit2(handle, 1);
            sound_attach(handle, obj, (void (*)())aim_sound_update_b);
        }
        obj->vars.semi_truck_mech.loop_sound_handle = handle;
    }
}


void obj_stop_held_sound(Object *obj) {
    if (obj->vars.words[3] != 0) {
        sound_stop(obj->vars.words[3]);
        obj->vars.words[3] = 0;
    }
}


/* Places up to three child objects (slots at 0x25C..0x264 of obj) at a running
   position; each child after the first pushes the position by a vector from vec_from_polar. */
void enemy_place_children(EnemyWalkObj *obj, s32 x, s32 y, s32 z, s32 a4, s32 a5, s32 a6) {
    SVECTOR vec_a;
    SVECTOR vec_b;
    Object **children;

    children = (Object **)&obj->pad_24C[0x10];
    if (children[0] != 0) {
        children[0]->vars.words[3] = x;
        children[0]->vars.words[4] = y;
        children[0]->vars.words[5] = z;
        ((s16 *)children[0]->vars.words)[2] = 0;
        ((s16 *)children[0]->vars.words)[3] = a4;
        ((s16 *)children[0]->vars.words)[4] = 0;
    }
    if (children[1] != 0) {
        vec_from_polar(&vec_a, 0x1C0, a4);
        x += vec_a.vx;
        y += vec_a.vy;
        z += vec_a.vz;
        children[1]->vars.words[1] = x;
        children[1]->vars.words[2] = y;
        children[1]->vars.words[3] = z;
        ((s16 *)children[1]->vars.words)[10] = 0;
        ((s16 *)children[1]->vars.words)[11] = a5;
        ((s16 *)children[1]->vars.words)[12] = 0;
    }
    if (children[2] != 0 && children[2]->vars.part.unk_280 != 4) {
        vec_from_polar(&vec_b, 0x40D, a5);
        x += vec_b.vx;
        y += vec_b.vy;
        z += vec_b.vz;
        children[2]->vars.words[1] = x;
        children[2]->vars.words[2] = y;
        children[2]->vars.words[3] = z;
        ((s16 *)children[2]->vars.words)[10] = 0;
        ((s16 *)children[2]->vars.words)[11] = a6;
        ((s16 *)children[2]->vars.words)[12] = 0;
    }
}

void obj_set_state(void *obj, s32 new_state) {
    StateHistory *h = (StateHistory *)((u8 *)obj + 0x26C);
    u16 old = h->state;

    h->state = new_state;
    h->zero = 0;
    h->prev_state = old;
}

s32 get_walk_state(Object *obj) {
    return obj->vars.enemy.walk_state;
}

extern WalkState walk_state_table[];
void walk_frame_advance(EnemyWalkObj *obj) {
    WalkState *r = &walk_state_table[get_walk_state((Object *)obj)];
    s32 f = obj->frame;
    s32 unused[2];
    obj->frame = f + 1;
    if (f >= r->count - 1) {
        obj->pos += obj->step << 12;
        obj_set_state(obj, r->next_state);
    }
}

s32 ring128_get_back(s32 a);
void enemy_place_children();
void fx_frame_update(void);
void enemy_walk_update(EnemyWalkObj *obj) {
    s32 v, lim, gt, vy, off, mag, nx, ny, nz, dz, a, b;
    s16 *e;
    WalkState *r;

    v = obj->vy + obj->accel;
    obj->z = obj->z + *(volatile s32 *)&obj->vy;
    lim = v;
    gt = v > -0x16000;
    if (gt) {
        lim = -0x16000;
    }
    if (lim >= -0x40000) {
        vy = v;
        if (v > -0x16000) {
            vy = -0x16000;
        }
    } else {
        vy = -0x40000;
    }
    obj->vy = vy;
    walk_frame_advance(obj);
    r = &walk_state_table[get_walk_state((Object *)obj)];
    mag = r->mag;
    e = (s16 *)((u8 *)r->tab + obj->frame * 4);
    off = mag * e[1];
    obj->step = off;
    dz = mag * -e[0];
    nx = obj->pos >> 12;
    ny = obj->y >> 12;
    nz = obj->z >> 12;
    nx += off;
    obj->x = nx << 12;
    ring128_push(dz);
    a = ring128_get_back(0x10) / 2;
    b = ring128_get_back(0x20) / 2;
    enemy_place_children(obj, nx, ny, nz, dz, a, b);
    fx_frame_update();
}

/* Boss meter: the clamped health of its three parts (vars.words[7], [6] only
 * while damage_scale is 1, and [5]) summed against a maximum of 14000. */
void enemy_health_meter_update(Object *obj) {
    s32 hp_third;
    s32 hp_second;
    s32 hp_first;

    hp_second = 0;
    hp_first = 0;
    hp_third = 0;
    if ((Object *)obj->vars.semi_truck_mech.part_obj_first != NULL) {
        hp_first = ((Object *)obj->vars.semi_truck_mech.part_obj_first)->health;
    }
    if ((Object *)obj->vars.semi_truck_mech.part_obj_second != NULL) {
        hp_second = 0;
        if (obj->vars.chaser.damage_scale == 1) {
            hp_second = ((Object *)obj->vars.semi_truck_mech.part_obj_second)->health;
        }
    }
    do {
        if ((Object *)obj->vars.semi_truck_mech.part_obj_third != NULL) {
            hp_third = ((Object *)obj->vars.semi_truck_mech.part_obj_third)->health;
        }
    } while (0);
    hp_first = MAX(MIN(hp_first, 3500), 0);
    hp_second = MAX(MIN(hp_second, 3500), 0);
    hp_third = MAX(MIN(hp_third, 7000), 0);
    meter_set(hp_third + (hp_second + hp_first), 14000);
}

void part_set_mode(Object *obj, s32 mode);
void enemy_set_mode(Object *obj, s32 mode);
void enemy_set_state(Object *obj, s32 state);
void mission_timer_extend(void);
void obj_sound_start();
void semi_truck_mech_phase2(Object *obj, ObjHandler *handler) {
    Object *enemy;
    Object *part;

    switch (handler->state) {
    case 0:
        if ((obj->z >> 12) < (s32)0xFFFF01B0) {
            obj_set_state(obj, 7);
            handler->state = 1;
            goto tail;
        }
        break;
    case 1:
        if (get_walk_state(obj) == 1) {
            obj->accel_z = 0xC000;
            handler->state = 2;
            goto tail;
        }
        break;
    case 2:
        if (((obj->z >> 12) - *(s32 *)((u8 *)player_position() + 8)) >= -0x1193) {
            handler->state = 3;
        }
        break;
    case 3:
        enemy_set_state(*(Object **)obj->vars.pair.pad_264, 1);
        obj_sound_start(*(Object **)obj->vars.pair.pad_264, 0x30A2, 0x7F, 0x3C);
        obj->vars.pair.timer = 1;
        mission_timer_set(0xE10);
        mission_timer_active_set(1);
        meter_set_mode(1);
        warning_ack_set(0);
        handler->state = 4;
        set_stage_flag_8(0);
        break;
    case 4:
        enemy = *(Object **)obj->vars.pair.pad_264;
        if (enemy->health <= 0) {
            enemy_set_state(enemy, 3);
            add_score(0x1388);
            obj_stop_held_sound(obj);
            handler->state = 5;
            mission_timer_extend();
        }
        break;
    case 5:
        enemy = *(Object **)obj->vars.pair.pad_264;
        if (enemy->vars.part.unk_280 == 4) {
            enemy->vars.part.unk_280 = 5;
            *(Object **)obj->vars.pair.pad_264 = NULL;
            handler->state = 6;
            goto tail;
        }
        break;
    case 6:
        enemy_set_mode(obj->vars.pair.child, 1);
        obj_sound_start(obj->vars.pair.child, 0x30A2, 0x7F, 0x3C);
        obj->vars.pair.timer = 2;
        handler->state = 7;
        goto tail;
    case 7:
        enemy = obj->vars.pair.child;
        if (enemy->vars.part.unk_280 == 5) {
            enemy_set_mode(enemy, 2);
            part_set_mode(obj->vars.pair.partner, 1);
            obj->vars.pair.timer = 3;
            add_score(0x1388);
            mission_timer_extend();
            handler->state = 8;
            goto tail;
        }
        break;
    case 8:
        part = obj->vars.pair.partner;
        if (part->health < 0xDAC) {
            obj->vars.pair.timer = 4;
            handler->state = 9;
            goto tail;
        }
        break;
    case 9:
        part = obj->vars.pair.partner;
        if (part->health <= 0) {
            enemy_set_mode(obj->vars.pair.child, 3);
            part_set_mode(obj->vars.pair.partner, 3);
            obj->vars.pair.timer = 8;
            add_score(0x32C8);
            add_kill_count(1);
            set_stage_end(2);
            set_mission_active(0);
            obj_actors_clear_index();
            handler->state = 0xA;
            goto tail;
        }
        break;
    case 10:
        break;
    }
tail:
    enemy_health_meter_update(obj);
    giant_robot_shots_tick();
}

void fx_frame_draw(void);

void semi_truck_mech_draw(void) {
    fx_frame_draw();
}

void obj_noop_hook(void);
void obj_noop_update(void);
void stage_setup_flow(void);
extern s32 semi_truck_mech_asset[3];
extern s32 semi_truck_interp_a[7];
extern s32 semi_truck_interp_b[7];
void semi_truck_mech_stage_setup(void) {
    s32 slot_a;
    s32 slot_b;
    s32 *param_ptr;

    if (stage_ready_get() != 0) {
        param_ptr = semi_truck_mech_asset;
        slot_a = interp1c_add((s32)semi_truck_interp_a, *param_ptr);
        interp_slot_a = slot_a;
        interp1c_set_state(slot_a, 0);
        slot_b = interp1c_add((s32)semi_truck_interp_b, *param_ptr);
        interp_slot_b = slot_b;
        interp1c_set_state(slot_b, 0);
    }
    obj_noop_hook();
    obj_noop_update();
    stage_setup_flow();
    set_stage_flag_8(1);
}

void obj_update_passes(Object *obj);
void enemy_walk_update(EnemyWalkObj *obj);
void semi_truck_mech_phase2(Object *obj, ObjHandler *handler);
void fx_system_init(void);
void part_set_mode(Object *obj, s32 mode);
void enemy_set_mode(Object *obj, s32 mode);
void enemy_set_state(Object *obj, s32 state);
Object *part_spawn(Object *parent);
Object *enemy_part_spawn(Object *parent);
Object *enemy_child_spawn(Object *parent);
extern ScriptCallEntry semi_truck_mech_call_table[2];
s32 semi_truck_mech_spawn(Placement *place) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    *(s16 *) &place->unk_00[2] = -1;
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) obj_update_passes;
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) enemy_walk_update;
    obj->handlers[2].fn = semi_truck_mech_phase2;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) semi_truck_mech_draw;
    obj->asset = semi_truck_mech_asset;
    obj->hit_cooldown_max = 0x30;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->unk_1C6 = 0;
    obj->call_table = semi_truck_mech_call_table;
    obj->script.unk_0A = 0;
    obj_init_from_place(obj, place, 0);
    ((void (*)(Object *)) fx_system_init)(obj);
    ring128_clear();
    obj->vars.semi_truck_mech.part_obj_third = 0;
    obj->vars.semi_truck_mech.part_obj_second = 0;
    obj->vars.semi_truck_mech.part_obj_first = 0;
    obj->vars.semi_truck_mech.part_obj_third = (s32) part_spawn(obj);
    obj->vars.semi_truck_mech.part_obj_second = (s32) enemy_part_spawn(obj);
    obj->vars.semi_truck_mech.part_obj_first = (s32) enemy_child_spawn(obj);
    enemy_place_children((EnemyWalkObj *) obj, obj->x >> 12, obj->y >> 12, obj->z >> 12, 0, 0, 0);
    part_set_mode((Object *) obj->vars.semi_truck_mech.part_obj_third, 0);
    enemy_set_mode((Object *) obj->vars.semi_truck_mech.part_obj_second, 0);
    enemy_set_state((Object *) obj->vars.semi_truck_mech.part_obj_first, 0);
    *(s16 *) &obj->vars.enemy.unk_268 = 0x20;
    *(s16 *) &obj->vars.enemy.unk_276[0] = 0x20;
    obj->vars.enemy.target_yaw = 0;
    obj->vars.semi_truck_mech.unused_258 = 0;
    *(s16 *) &obj->vars.enemy.sound = 0;
    obj->vars.semi_truck_mech.unused_274 = 0;
    *(s16 *) &obj->vars.enemy.unk_276[2] = 1;
    *(s16 *) &obj->vars.enemy.unk_276[4] = 1;
    *(s16 *) &obj->vars.enemy.shot_timer = 0;
    obj->vars.semi_truck_mech.unused_24C = 0;
    obj->vars.semi_truck_mech.unused_250 = 0;
    obj->vars.semi_truck_mech.loop_sound_handle = 0;
    obj->vars.semi_truck_mech.spawn_x = obj->x;
    shot_loop_sound_start(obj);
    enemy_loop_sound_start(obj);
    obj_loop_sound_start_w3(obj);
    obj->vars.enemy.walk_state = 0;
    obj_set_state(obj, 0);
    obj->vz = -0x20000;
    mech_aux_spawn();
    mission_timer_set(0x35547);
    mission_state_set(2);
    mission_timer_active_set(0);
    meter_set(0x36B0, 0x36B0);
    meter_set_mode(0);
    show_line((s32) "#1Warning!  Warning! An object running  parallel.\241");
    msg_show_slot(1, -1);
    warning_ack_set(1);
    obj->vz = -0x2D000;
    obj->accel_z = 0;
    return 1;
}
