/* heavy_mobile_suit: one of s04's own original source files (scripts/objmap.py); part of src/s04/main.c's unit, included there. */

/* Same code as func_800BC8AC (s01). */
void script_op_jump_table_if_player_far(Object *obj) {
    s32 limit;
    s16 *cursor;
    s32 threshold;
    s32 index;

    limit = (s16) obj_player_dist(obj);
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Bytecode step: reads the opcode at the script cursor (obj->unk_1C.unk_04)
 * and advances it by one halfword. When the halfword at 0x272 is negative,
 * the opcode indexes the object's jump table (obj->unk_1C.data) and the
 * cursor jumps to that entry. */
void script_step(Object *obj) {
    s16 *pc;
    s32 opcode;

    pc = obj->script.pc;
    obj->script.pc = pc + 1;
    opcode = *pc;
    if (*((s16 *)&obj->vars.enemy.sound + 1) < 0) {
        obj->script.pc = ((s16 **)obj->script.data)[opcode];
    }
}


void obj_play_sound_here(Object *obj) {
    s32 pos[3];
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    sound_play_at_units(0x3530, 0x60, 0x3C, pos);
}

#if STAGE == 9
/* Once the timer field unk_F8 has run out, copies the 0x248 halfword into next_state. */
void obj_timer_next_state(Object *obj) {
    obj_link_script_run();
    if (obj->script_flag == 0) {
        obj->next_state = (u16)obj->vars.h.unk_248;
    }
}
#else
/* S04: the same with the 0x24A halfword. */
void obj_timer_next_state(Object *obj) {
    obj_link_script_run();
    if (obj->script_flag == 0) {
        obj->next_state = obj->vars.h.unk_24A;
    }
}
#endif



/* Same code as flier_keep_range (s04). */
void flier_hold_range(s16 *actor, s32 *pos, s32 *out, s32 speed, s32 range) {
    s32 dx;
    s32 dz;
    s32 dist;
    s32 dir;

    dir = speed;
    dx = (cam_pos_z - pos[2]) >> 12;
    dz = (cam_pos - pos[0]) >> 12;
    if (((((atan2(dx, dz) - actor[2]) & 0xFFF) - 0x400) & 0xFFF) < 0x800) {
        dir = -dir;
    }
    dist = isqrt(length_sq(dz, 0, dx));
    if (dist < range - 0x40) {
        dir = -dir;
    } else if (dist < range) {
        return;
    }
    fly_strafe(actor[2], dir, out + 2, out);
}


/* Flying enemy step: turn yaw toward the target (faster while the
   enemy's flag at 0x274 is clear), ease pitch to level, fly along yaw,
   then update the two attached nodes. */
void obj_fly_update(Object *obj) {
    s32 dx = 0;
    s32 dz = 0;
    s32 turn_rate;
    s32 y;

    obj->unk_1B7 = 0;
    if (obj->unk_242 == 0) {
        y = (cam_pos_y >> 12) - 0x190;
        obj_turn_toward_player(obj, 0x18);
    } else {
        y = obj->vars.heavy_mobile_suit.unk_260 >> 12;
        if (*(s16 *)obj->vars.enemy.unk_26E == 0) {
            turn_rate = 0xC00;
            if (obj->vars.heavy_mobile_suit.unk_274 == 0) {
                turn_rate = 0x400;
            }
        } else {
            turn_rate = 0x800;
        }
        obj->yaw = angle_approach(obj->yaw, turn_rate, 0x10);
    }
    obj->pitch = angle_approach(obj->pitch, 0, 8);
    obj->vars.enemy.sound_channel[1] =
        angle_approach(obj->vars.enemy.sound_channel[1], obj->yaw, 0x20);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj_step_axes_toward(obj, dz, dx);
    obj_set_fall_speed(obj, 2, y);
    *(s16 *)&obj->vars.heavy_mobile_suit.unk_264 = 0;
}

void obj_aim_at_player_eased(Object *obj, s32 arg) {
    s32 yaw;
    s32 pitch;
    s32 *pos;
    s32 new_pitch;

    /* aim the object at the player: the aim point is 0x60 above the player's position */
    pos = player_position();
    vector_to_angles(pos[0] - (obj->x >> 12), (pos[1] - (obj->y >> 12)) + 0x60, pos[2] - (obj->z >> 12), &yaw, &pitch);
    obj->vars.heavy_mobile_suit.aim_yaw = angle_approach((s16) obj->vars.heavy_mobile_suit.aim_yaw, yaw, 0x20);
    new_pitch = angle_approach((s16) obj->pitch, pitch, 8);
    /* the new pitch is stored only when it lies outside 0x200..0xE00 */
    if ((u32) (new_pitch - 0x200) >= 0xC01U) {
        obj->pitch = new_pitch;
    }
}

/* Turns obj->yaw toward a point near the player: the player's position, offset by
   the flagged vector from the object's angle (vars.enemy.mode), then turned by at most 0x40. */
void obj_face_flank_point(Object *obj, s32 arg) {
    s32 *pos;
    s32 px;
    s32 pz;
    s32 t;

    pos = player_position();
    if (obj->vars.heavy_mobile_suit.unk_274 == 0) {
        t = *(s16 *)&obj->vars.enemy.sound * cos_table[*(u16 *)&obj->vars.enemy.mode & 0xFFF].value;
        if (t < 0) {
            t += 0xFFF;
        }
        px = pos[0] - (t >> 12);
    } else {
        t = *(s16 *)&obj->vars.enemy.sound * cos_table[*(u16 *)&obj->vars.enemy.mode & 0xFFF].value;
        if (t < 0) {
            t += 0xFFF;
        }
        px = pos[0] + (t >> 12);
    }
    /* z offset: sin of the angle; a flag at 0x26E skips it */
    if (*(s16 *)obj->vars.enemy.unk_26E == 0) {
        pz = pos[2] + *(s16 *)&obj->vars.enemy.sound;
    } else {
        t = *(s16 *)&obj->vars.enemy.sound * *(s16 *)&rcossin_tbl[*(u16 *)&obj->vars.enemy.mode & 0xFFF];
        if (t < 0) {
            t += 0xFFF;
        }
        pz = pos[2] + (t >> 12);
    }
    obj->yaw = angle_approach(obj->yaw, atan2(pz - (obj->z >> 12), px - (obj->x >> 12)), 0x40);
}

void obj_face_flank_point(Object *obj, s32 arg);
void obj_pursue_step(Object *obj, s32 arg) {
    s32 d[2];
    s32 *pdx;

    player_position();
    d[1] = 0;
    d[0] = 0;
    obj_aim_at_player_eased(obj, arg);
    obj_face_flank_point(obj, arg);
    pdx = &d[1];
    if (*(s16 *)&obj->vars.enemy.unk_26E == 0) {
        pdx = 0;
    }
    fly_move(obj->yaw, obj->speed, pdx, &d[0]);
    obj_step_axes_toward(obj, d[0], d[1]);
    obj->vy = ((s16 *)rcossin_tbl)[(((u16 *)obj->vars.words)[14] & 0xFFF) * 2] * 2;
    if (obj->vars.heavy_mobile_suit.unk_274 == 0) {
        obj->vars.heavy_mobile_suit.unk_248 -= 8;
    } else {
        obj->vars.heavy_mobile_suit.unk_248 += 8;
    }
    ((u16 *)obj->vars.words)[21] -= 1;
    ((u16 *)obj->vars.words)[14] += 0x20;
}

void obj_muzzle_shot(Object *obj);
/*
 * Runs obj_pursue_step on the object; if its signed halfword at 0x258 is zero, runs obj_muzzle_shot too.
 * stage.h has no signed view of 0x258 (vars.h.unk_258 is u16, which would compile to lhu), hence the cast.
 */
void obj_pursue_update(Object *obj, s32 arg) {
    obj_pursue_step(obj, arg);
    if (*(s16 *)&obj->vars.heavy_mobile_suit.unk_258 == 0) {
        obj_muzzle_shot(obj);
    }
}

void obj_noop(void) {
}

/* Per-frame update for a flow-driven enemy: steers the yaw by the flow sample,
 * eases speed toward vars.words[1], ticks the timers, then calls obj_lean_into_turn on the
 * sound channels with a +4 or -4 step (by the halfword at 0x26E). */
void heavy_mobile_suit_update(Object *obj, ObjHandler *handler) {
    s32 speed;
    s32 target;

    obj->vz = 0;
    obj->vx = 0;
    obj->vars.enemy.walk_state = get_flow_max();
    if (((s16 *)&obj->vars.enemy.sound)[1] > 0) {
        flow_sample((Flow *)&obj->vars.enemy.unk_266, obj->width, &obj->x, &obj->vx, &obj->turn);
    } else {
        flow_sample((Flow *)&obj->vars.enemy.unk_266, obj->width, player_position(), &obj->vx, &obj->turn);
    }
    obj->yaw += obj->turn;
    obj_script_step(obj, handler);
    if (obj->vars.heavy_mobile_suit.timer == 0) {
        speed = obj->speed;
        target = obj->vars.heavy_mobile_suit.unk_24C;
        if (speed == target) {
            obj->speed = speed;
        } else {
            obj->speed = (target < speed) ? speed - 1 : speed + 1;
        }
        obj->vars.heavy_mobile_suit.timer = 8;
    }
    obj->vars.heavy_mobile_suit.timer -= 1;
    obj->vars.heavy_mobile_suit.unk_258 -= 1;
    obj->vars.heavy_mobile_suit.blend_weight += 0x38;
    obj->vars.enemy.unk_25C += 0x71;
    if (obj->vars.heavy_mobile_suit.blend_weight >= 0x1001) {
        obj->vars.heavy_mobile_suit.blend_weight = 0x1000;
    }
    if (*(s16 *)obj->vars.enemy.unk_26E == 0) {
        obj_lean_into_turn(obj, obj->vars.enemy.sound_channel, 4, 0x100);
    } else {
        obj_lean_into_turn(obj, obj->vars.enemy.sound_channel, -4, 0x100);
    }
}

static inline void spark_add_to(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    s32 n = SPARK_COUNT;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[colour >> 24];
        list->tail[colour >> 24] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}

void spark_emit_damage(Object *obj, Vec3 *pos, SVECTOR *rot) {
    s32 at[3];
    s32 offset[3];
    s32 colour, level, mix;
    s32 strength;
    s32 *asset;
    s32 slot;
    s32 model_copy;
    s32 model;
    s32 id;
    SparkList *list;

    if (obj->vars.heavy_mobile_suit.blend_weight < 0x1000) {
        offset[0] = 0x33;
        asset = obj->asset;
        offset[1] = -0x41;
        slot = *asset;
        offset[2] = 0xC8;
        model = model_slot_pchr(slot);
        vec3_rotate(rot->vy, rot->vx, rot->vz, &offset[0], &offset[1], &offset[2]);
        at[0] = offset[0] + pos->x;
        at[1] = offset[1] + pos->y - 0x60;
        at[2] = offset[2] + pos->z;
        strength = (u16)obj->vars.heavy_mobile_suit.blend_weight;
        do { } while (0);
        model_copy = model;
        FAKE_OPAQUE(model_copy);
        level = (s16)strength >> 5;
        mix = level;
        if (mix == 0) {
            mix = 1;
        }
        colour = (mix << 16) | (level << 8) | level;
        id = pchr_blend(model + 10, model + 11, 0x1000 - (s16)strength, 0);
        list = &spark_list;
        spark_add_to(list, at[0], at[1], at[2], 0, 0x800, 0, id, colour);
        FAKE_USE(list);
        if (obj->vars.heavy_mobile_suit.blend_weight < 0x800) {
            id = pchr_blend(model + 7, model + 8, 0x800 - obj->vars.heavy_mobile_suit.blend_weight, 0);
            spark_add_to(list, at[0], at[1], at[2], rot->vy, rot->vx + 0x800, rot->vz + obj->vars.heavy_mobile_suit.blend_weight / 16, id, colour);
            obj->vars.enemy.unk_25C = 0;
        } else {
            id = pchr_blend(model_copy + 8, model_copy + 9, 0x1000 - obj->vars.enemy.unk_25C, 0);
            spark_add_to(list, at[0], at[1], at[2], rot->vy, rot->vx + 0x800, rot->vz + obj->vars.heavy_mobile_suit.blend_weight / 16, id, colour);
        }
        FAKE_USE(model_copy);
    }
}

void spark_emit_damage(Object *obj, Vec3 *pos, SVECTOR *rot);

void heavy_mobile_suit_draw(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    SVECTOR tmp_rot;
    SVECTOR aim;
    SVECTOR rot;
    s32 model;
    s32 colour;
    s32 pitch;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    tmp_rot.vx = -pitch;
    tmp_rot.vy = obj->yaw;
    tmp_rot.vz = obj->roll;
    tmp_rot.vy = obj->vars.enemy.sound_channel[1];
    rot = tmp_rot;

    if (test_bit(obj->flags, 6)) {
        s32 base = obj->type.unk_0E;
        model = base + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        model = obj_keyframe_value(obj, 0);
    }

    colour = 0;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
        pitch = 0;
    }

    spark_emit_damage(obj, &pos, &rot);
    spark_add_y_offset(pos.x, pos.y, pos.z, tmp_rot.vy, tmp_rot.vx, tmp_rot.vz, model, colour, -0x60);

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

/* Stops the sound handle stored at 0x278 of the object. */
void obj_sound_stop(Object *obj) {
    sound_stop(*(s32 *) &obj->vars.enemy.unk_276[2]);
}


void obj_run_states_raised(Object *obj, ObjHandler *handler) {
    obj->y += 0xFFFA0000;
#if STAGE == 9
    obj_run_states_default(obj, handler);
#else
    obj_state_run_b(obj, handler);
#endif
    obj->y += 0x60000;
}


extern s16 heavy_mobile_suit_script[4];
extern s16 *heavy_mobile_suit_data[];
extern s16 *D_80119860;
extern s32 heavy_mobile_suit_asset[3];
extern ScriptCallEntry heavy_mobile_suit_call_table[11];
extern StateEntry heavy_mobile_suit_state_table[13];
extern s16 *heavy_mobile_suit_type_data[];
void heavy_mobile_suit_draw(Object *obj, ObjHandler *handler);
void obj_sound_stop(Object *obj);
s32 heavy_mobile_suit_spawn(Placement *place) {
    Object *obj;
    SpawnVars *vars;
    s32 sound;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) obj_timer_next_state;
    obj->handlers[1].fn = heavy_mobile_suit_update;
    obj->handlers[2].fn = obj_run_states_raised;
    obj->handlers[3].fn = heavy_mobile_suit_draw;
    obj->callback = (s32) obj_respawn;
    obj->destructor = obj_sound_stop;
    obj->asset = heavy_mobile_suit_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = heavy_mobile_suit_call_table;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->kind = 1;
    obj->state_table = heavy_mobile_suit_state_table;
    script_start((Script *) obj, heavy_mobile_suit_script, (s32) heavy_mobile_suit_data);
    obj->script.data = heavy_mobile_suit_type_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_80119860;
    obj_init_from_place(obj, place, 0x37);
    obj->speed = 0;
    obj_set_part_bounds(obj, 0x11, 0x1000);
    vars = (SpawnVars *) &obj->vars;
    vars->unk_250 = 8;
    vars->unk_258 = -1;
    vars->unk_248 = 0;
    vars->unk_24A = 0;
    vars->unk_24C = 0;
    vars->unk_252 = 1;
    vars->unk_254 = 0;
    vars->unk_25A = 0x1000;
    vars->unk_25C = 0x1000;
    vars->unk_264 = 0;
    vars->initial_yaw = (u16) obj->yaw;
    vars->initial_y = obj->y;
    rec_reset((PartSlot *) vars->pad_266);
    vars->unk_26E = ((SpawnPlace *) place)->unk_1A / 256;
    vars->range = place->range;
    vars->unk_272 = place->unk_1E * 0x3C;
    vars->player_left_flag = 0;
    if (*player_position() < (obj->x >> 12)) {
        vars->player_left_flag = 1;
    }
    obj_hit_set_unk08(obj->index, 4);
    obj_hit_set_unk06(obj->index, 2);
    sound = sound_start(SND_MECH_ENGINE_LOOP | SND_HELD | SND_GROUP(1), 0x40, 0, 0);
    sound_attach(sound, &obj->x, 0);
    sound_set_flag_bit2(sound, 1);
    vars->sound_handle = sound;
    return 1;
}

void projectile_straight_update(Object *obj) {
    s32 from[3];
    s32 to[3];
    s32 hit[3];
    s16 hit_obj;

    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    to[0] = (obj->x + obj->vx) >> 12;
    to[1] = (obj->y + obj->vy) >> 12;
    to[2] = (obj->z + obj->vz) >> 12;
    if (cam_range_check(from[0], from[1], from[2]) == 0 || (obj_hit_damage(obj->index) << 16) > 0) {
        obj->vars.muzzle_shot.unk_250 = 1;
    } else if (trace_world(8, 0x10, from, to, hit) != 0) {
        spawn_effect(hit[0], hit[1], hit[2], 0);
        obj->vars.muzzle_shot.unk_250 = 1;
    } else {
        set_collide_mode(1);
        if (trace_objects(from, to, 0x10, hit, &hit_obj) != 0) {
            hit_target_masked(hit_obj, 1, (s16) atan2(hit[2] - from[2], hit[0] - from[0]), obj->damage);
            spawn_effect(hit[0], hit[1], hit[2], 0);
            obj->vars.muzzle_shot.unk_250 = 1;
        }
        set_collide_mode(0);
        obj->z += obj->vz;
        obj->x += obj->vx;
        obj->y += obj->vy;
        if (obj->vars.trace.trace_flags < 0x1000) {
            obj->vars.trace.trace_flags += 0x100;
        }
    }
    if (obj->vars.muzzle_shot.unk_250 != 0) {
        obj_free(obj);
    }
}

static inline void spark_add_rot_first_u(SparkList *list, s32 ry, s32 rx, u16 rz, s32 x, s32 y, s32 z, s32 value, s32 colour) {
    s32 n = spark_count;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = spark_list_tail;
        spark_list_tail = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}
void spark_emit_obj_pair(Object *obj) {
    s32 base[3];
    s32 pos[3];
    SVECTOR rot;
    s32 off[3];
    s32 id = obj->vars.muzzle_shot.unk_248;
    s16 pitch;
    s32 raw_pitch;
    s32 yaw;
    u16 roll;
    register s32 z asm("$9");
    register s32 raw_z asm("$2");
    s32 unused[2];
    register s32 first_id asm("$8");

    base[0] = obj->x >> 12;
    base[1] = obj->y >> 12;
    first_id = id + 1;
    raw_z = obj->z;
    z = raw_z >> 12;
    base[2] = z;
    raw_pitch = obj->pitch;
    pitch = -raw_pitch;
    rot.vx = pitch;
    yaw = obj->yaw;
    off[0] = 0;
    off[1] = 0;
    rot.vy = yaw;
    roll = obj->roll;
    off[2] = 0x4B;
    rot.vz = roll;
    spark_add_rot_first_u(&spark_list, rot.vy + 0x800, rot.vx, roll, base[0], base[1], z, first_id, 0);
    rotate_xz_twice(rot.vy, -rot.vx, &off[0], &off[1], &off[2]);
    pos[0] = base[0] + off[0];
    pos[1] = base[1] + off[1];
    pos[2] = base[2] + off[2];
    spark_add_rot_first_u(&spark_list, 0, 0x800, 0, pos[0], pos[1], pos[2], id + 2, 0);
}

char str_land_tp1_clt[16] = "land_tp1.clt";

char str_land_tp0_clt[16] = "land_tp0.clt";

char str_land_ch0_clt[16] = "land_ch0.clt";

char str_land_tp1_xs3[16] = "land_tp1.xs3";

char str_land_tp0_xs3[16] = "land_tp0.xs3";

char str_land_ch0_vx1[16] = "land_ch0.vx1";

char str_land_ch0cb4[16] = "land_ch0.cb4";

void muzzle_shot_spawn(Object *obj, s32 *pos, u16 *rot, s32 shot_param) {
    s32 unused[6];
    s32 move[4] = { 0, 0, 0, 0 };
    s32 dir[4];
    Object *shot;
    s32 yaw, pitch, len;

    shot = obj_new();
    if (shot != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &shot->node);
        shot->handlers[1].fn = projectile_straight_update;
        shot->handlers[3].fn = spark_emit_obj_pair;
        shot->handlers[0].fn = NULL;
        shot->handlers[0].unk_11 = 0;
        shot->handlers[0].state = 0;
        shot->handlers[1].unk_11 = 0;
        shot->handlers[1].state = 0;
        shot->handlers[2].fn = NULL;
        shot->handlers[2].unk_11 = 0;
        shot->handlers[2].state = 0;
        shot->handlers[3].unk_11 = 0;
        shot->handlers[3].state = 0;
        shot->callback = 0;
        shot->asset = heavy_mobile_suit_asset;
        obj_set_flags(shot, 0x80);
        shot->unk_17A = 0;
        obj_hit_clear(shot->index);
        shot->damage = shot_param;
        shot->speed = 0x32;
        shot->x = pos[0] << 12;
        shot->y = pos[1] << 12;
        shot->z = pos[2] << 12;
        shot->pitch = rot[0];
        shot->yaw = rot[1];
        shot->roll = rot[2];
        shot->vars.words[0] = model_slot_pchr(*(s32 *)obj->asset) + 4;
        shot->vars.h.unk_24C = 0;
        shot->vars.words[2] = 0;
        flow_sample((Flow *)&obj->vars.muzzle_shot.flow, obj->width, &obj->x, move, &obj->turn);
        yaw = shot->yaw;
        pitch = shot->pitch;
        len = shot->speed;
        angles_to_vector(yaw, pitch, len, dir, &dir[1], &dir[2]);
        shot->vx = dir[0] + move[0];
        shot->vy = dir[1] + move[1];
        shot->vz = dir[2] + move[2];
    }
}

/* file names the data tables reference by address */

/* file names the data tables reference by address */
const char file_seaf_tp0_clt[] = "seaf_tp0.clt";
const char file_seaf_ch0_clt[] = "seaf_ch0.clt";
const char file_seaf_tp0_xs3[] = "seaf_tp0.xs3";
const char file_seaf_ch0_vx1[] = "seaf_ch0.vx1";
const char file_seaf_ch0_cb4[] = "seaf_ch0.cb4";
const char file_kira_tp0_clt[] = "kira_tp0.clt";
const char file_kira_ch0_clt[] = "kira_ch0.clt";
const char file_kira_tp0_xs3[] = "kira_tp0.xs3";
const char file_kira_ch0_vx1[] = "kira_ch0.vx1";
const char file_kira_ch0_cb4[] = "kira_ch0.cb4";
const char file_msgs_spr_so3[] = "msgs_spr.so3";
const char file_msgs_spr_grc[] = "msgs_spr.grc";
const char file_msgs_spr_clt[] = "msgs_spr.clt";

void muzzle_shot_spawn(Object *obj, s32 *pos, u16 *rot, s32 shot_param);

void obj_muzzle_shot(Object *obj) {
    s32 base[3];
    s16 rot[3];
    s32 pos[3];
    s32 dir[3];
    s32 unused[2];
    s32 pitch;
    s32 yaw;
    s32 roll;
    s32 y;
    s32 *off = dir;

    base[0] = obj->x >> 12;
    y = obj->y >> 12;
    base[1] = y;
    off[0] = 0x33;
    base[2] = obj->z >> 12;
    off[1] = -0x41;
    pitch = -obj->pitch;
    off[2] = 0x118;
    rot[0] = pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    base[1] = y - 0x60;
    rot[2] = roll;
    yaw = obj->vars.heavy_mobile_suit.aim_yaw;
    rot[1] = yaw;
    vec3_rotate((s16) yaw, (s16) pitch, roll, off, &off[1], &off[2]);
    pos[0] = dir[0] + base[0];
    pos[1] = dir[1] + base[1];
    pos[2] = dir[2] + base[2];
    sound_play_at_units(SND_MECH_GUN_FIRE | SND_GROUP(1), 0x60, 0x3C, pos);
    muzzle_shot_spawn(obj, pos, (u16 *) rot, obj->damage);
}


s32 obj_respawn(Object *obj) {
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
