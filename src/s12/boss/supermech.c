/* supermech: one of s12's own original source files (scripts/objmap.py); part of src/s12/main.c's unit, included there. */

extern s32 value_queue_index;
extern s16 value_queue[];
void value_queue_push(s16 arg0) {
    value_queue[value_queue_index++] = arg0;
    value_queue_index = MAX(MIN(value_queue_index, 0xF), 0);
}

typedef struct ObjScript {
    /* 0x00 */ u8 unk_00[0x20];
    /* 0x20 */ s16 *pc;
} ObjScript;
/* Same code as script_op_set_target (s01). */
void script_op_value_push(ObjScript *script) {
    value_queue_push(*script->pc++);
}


void value_queue_pop(RingLookup *obj) {
    s32 raw = value_queue_index - 1;
    s32 idx;
    s32 in_range;

    value_queue_index = raw;
    idx = raw;
    in_range = idx < 16;
    if (!in_range) {
        idx = 15;
    }
    FAKE_OPAQUE(in_range);
    if (in_range == 0) {
        raw = 15;
    }
    if (raw < 0) {
        idx = 0;
    }
    value_queue_index = idx;
    obj->value = obj->table[value_queue[idx]];
}



void obj_attack_player(Object *obj) {
    Vec3 pos;
    s32 *player;
    s32 type;
    s32 damage;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    player = player_position();
    type = obj_read_s16(obj);
    damage = obj_read_s16(obj);
    hit_target_masked(0, type & 0xFF, atan2(pos.z - player[2], pos.x - player[0]), damage);
}


extern s32 spread_offsets_main[3];
extern s32 spread_offsets_alt[3];
void spark_src_spawn(s32 owner, s32 *pos, u16 *rot);
void spread_shot_fire(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 *offsets;
    s16 *cursor;
    s32 pitch;

    /* the type link's cursor steps through a halfword script; a zero entry picks the second table */
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    offsets = spread_offsets_main;
    if (*cursor == 0) {
        offsets = spread_offsets_alt;
    }
    pos[0] = -(offsets[0] * 0x1800) / 4096;
    pos[1] = -(offsets[2] * 0x1800) / 4096;
    pos[2] = -(offsets[1] * 0x1800) / 4096;
    rotate_xz_twice(obj->yaw, obj->pitch, pos, &pos[1], &pos[2]);
    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    pos[2] += obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = pitch + 0x10;
    rot[1] = obj->yaw;
    rot[2] = 0;
    spark_src_spawn((s32) obj, pos, (u16 *) rot);
    rot[1] += 0xC0;
    spark_src_spawn((s32) obj, pos, (u16 *) rot);
    rot[1] -= 0x180;
    spark_src_spawn((s32) obj, pos, (u16 *) rot);
}

void scroll_seg_start(Object *obj, s32 mode);
/* Reads the next halfword of the object's stream (the pointer at 0x20) and passes it to scroll_seg_start. */
void scroll_stream_start(Object *obj) {
    s16 *stream = obj->script.pc;

    obj->script.pc = stream + 1;
    scroll_seg_start(obj, *stream);
}

void scroll_seg_retract(s32 flag);
/* Same code as script_op_set_target (s01). */
void script_op_scroll_seg_retract(ObjScript *script) {
    scroll_seg_retract(*script->pc++);
}

void half_stream_read(HalfStream *s) {
    u8 *p = s->cursor;

    s->cursor = p + 2;
    s->value = *(u16 *)p;
}

extern s16 burst_vec_a_x, burst_vec_a_z, burst_vec_a_y;
extern s16 burst_vec_b_x, burst_vec_b_z, burst_vec_b_y;
extern s16 shot_aim_a_pitch, shot_aim_a_yaw, shot_aim_a_roll;
extern s16 shot_aim_b_pitch, shot_aim_b_yaw, shot_aim_b_roll;

/* Turns the vectors at burst_vec_a_x and burst_vec_b_x into rotations (pitch negated, yaw, no roll) at
 * shot_aim_a_pitch and shot_aim_b_pitch. */
void angles_from_vectors_set(void) {
    s32 yaw;
    s32 pitch;
    s32 x, y, z;

    /* one set of locals for both calls: set twice, they keep their loads in source order */
    x = burst_vec_a_x;
    y = burst_vec_a_y;
    z = burst_vec_a_z;
    vector_to_angles(x, y, z, &yaw, &pitch);
    x = burst_vec_b_x;
    y = burst_vec_b_y;
    z = burst_vec_b_z;
    shot_aim_a_roll = 0;
    shot_aim_a_pitch = -pitch;
    shot_aim_a_yaw = yaw;
    vector_to_angles(x, y, z, &yaw, &pitch);
    shot_aim_b_roll = 0;
    shot_aim_b_pitch = -pitch;
    shot_aim_b_yaw = yaw;
}

extern SVECTOR shot_muzzles_a[];
extern SVECTOR shot_muzzles_b[];
s32 ratan2(s32 y, s32 x);
void shot_spawn_relative_zeroed();
/* Script op: reads a flag from the script, steps the shot counter (wraps at 4096) and fires a
 * pair of shots from muzzle (counter % 3) of one of two muzzle sets, aimed up at the player
 * (pitch from the muzzle height against the horizontal distance clamped to 800..4000). */
void script_op_fire_aimed(Object *obj) {
    SVECTOR rot;
    s32 pos[3];
    SVECTOR *muzzle;
    s16 *script;
    s32 phase;
    u16 count;
    s32 flag;
    s32 pitch;
    s32 dist;

    count = obj->vars.turn.yaw_offset;
    script = obj->script.pc;
    phase = (s16)count;
    obj->script.pc = script + 1;
    flag = *script;
    obj->vars.turn.yaw_offset = count + 1;
    obj->vars.turn.yaw_offset = (s16)(count + 1) % 4096;
    phase %= 3;
    if (flag == 0) {
        rot = *(SVECTOR *)&shot_aim_a_pitch;
        muzzle = &shot_muzzles_a[phase];
    } else {
        rot = *(SVECTOR *)&shot_aim_b_pitch;
        muzzle = &shot_muzzles_b[phase];
    }
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = ABS(muzzle->vz * 6144 / 4096);
    dist = player_horiz_dist(pos);
    dist = (dist <= 4000 ? dist : 4000) < 800 ? 800 : (dist <= 4000 ? dist : 4000);
    rot.vx = ratan2(pitch, dist);
    shot_spawn_relative_zeroed(obj, muzzle, &rot);
    shot_spawn_relative_zeroed(obj, muzzle + 3, &rot);
}

extern SVECTOR supermech_side_muzzles[];
void burst_spawn(s32 owner, s32 *pos, s32 arg2, s32 arg3, s32 arg4);
/* Script op: reads a side (clamped to 0..1) and lobs a burst from that side's muzzle
 * (supermech_side_muzzles) toward the player: the range is the jittered horizontal distance (at least 800),
 * the burst size 16 near (under 1200) or 32 far; the yaw fans out 64 to that side, and every
 * 9th call it aims straight at the target instead. */
void supermech_fire(Object *obj) {
    s32 pos[3];
    s16 rot[4];
    s16 *script;
    s16 side;
    s32 arg;
    s32 dist;
    s32 jitter;
    s32 closer;
    s32 base;
    s32 size;
    s32 speed;
    s32 yaw;
    SVECTOR *muzzle;

    script = obj->script.pc;
    obj->vars.part.unk_280++;
    obj->script.pc = script + 1;
    arg = *script;
    side = ((arg < 2 ? arg : 1) < 0 ? 0 : (arg < 2 ? arg : 1));
    muzzle = &supermech_side_muzzles[side];
    pos[0] = -(muzzle->vx * 6144) / 4096;
    pos[1] = -(muzzle->vz * 6144) / 4096;
    pos[2] = -(muzzle->vy * 6144) / 4096;
    rotate_xz_twice(obj->yaw, obj->pitch, &pos[0], &pos[1], &pos[2]);
    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    pos[2] += obj->z >> 12;
    dist = player_horiz_dist(pos);
    jitter = rand_a_next();
    closer = dist - 256;
    dist = closer + jitter / 8;
    if (dist < 800) {
        dist = 800;
    }
    size = 32;
    if (dist < 1200) {
        size = 16;
    }
    speed = ((size * size * (pos[1] + 1024)) << 12) / dist + (dist << 11);
    speed /= size;
    speed = -speed;
    yaw = obj->yaw;
    if (side == 0) {
        s32 spread = rand_a_next();
        base = yaw + 64;
        yaw = base - spread / 4;
    } else {
        s32 spread = rand_a_next();
        base = yaw - 64;
        yaw = base + spread / 4;
    }
    if (obj->vars.part.unk_280 >= 9) {
        rot_turn_toward(pos, rot, 1024, 0);
        yaw = rot[1];
        obj->vars.part.unk_280 = 0;
    }
    burst_spawn((s32)obj, pos, yaw, speed, size);
}

/* Reads the s16 at the cursor, advances the cursor by 2 bytes and
 * passes (value != 0) as the mode. */
void script_op_set_flag(CursorObj20 *obj) {
    u8 *p;

    p = obj->cursor;
    obj->cursor = p + 2;
    if (*(s16 *)p == 0) {
        meter_set_mode(0);
    } else {
        meter_set_mode(1);
    }
}

/* Reads the halfword at the object's byte cursor (ObjLink unk_1C.unk_04), advances the cursor by 2 bytes,
 * and stores the value as the gun's unk_27A. */
void script_op_gun_set_value(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;

    obj->script.pc = cursor + 1;
    GUN_VARS(obj)->unk_27A = *cursor;
}

void obj_set_hit_reaction(Object *obj, s32 flag);
/* Reads the next halfword of the object's stream (the pointer at 0x20) and passes it to scroll_seg_start. */
void script_op_set_part_mode(Object *obj) {
    s16 *stream = obj->script.pc;

    obj->script.pc = stream + 1;
    obj_set_hit_reaction(obj, *stream);
}

void fx_entry_spawn(Object *owner, Vec3 *pos);
void fx_slot_spawn(s32 owner, s16 param);
void fx_slot_clear_all(void);
void fx_slots_reset(void);
void scroll_segs_step(void);
void keyframe_table_set_flag(s32 arg0);
void fx_track_flags_reset(void);
void fx_tracks_stop_all(void);
s32 *scene_get_rot(void);
s32 *scene_get_pos(void);
void burst_check_sphere(ProximityQuery *q);
void burst_reset(void);
void burst_clear_all(void);
void burst_draw_all(void);
void burst_check_all(void);
void burst_update_all(void);
void sound_slot_reset(void);
void sound_slot_clear_all(void);
void sound_slots_draw_all(void);
void sound_slots_hit_all(void);
void sound_slots_tick_all(void);
void pos_history_clear_all(void);
void pos_history_draw_all(void);
void pos_history_update_all(void);
void pos_history_push_all(void);
void scroll_flush_pending(void);
void scroll_flags_reset(void);
extern s16 spawn_offset_x;
extern s16 spawn_offset_y;
extern s16 spawn_offset_z;
void script_op_spawn_at_offset(Object *obj) {
    s16 *cursor;
    s32 vec[3];

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    if (*cursor == 0) {
        vec[0] = spawn_offset_x;
        vec[1] = spawn_offset_y;
        vec[2] = spawn_offset_z;
    } else {
        vec[0] = -spawn_offset_x;
        vec[1] = spawn_offset_y;
        vec[2] = spawn_offset_z;
    }
    rotate_xz_twice(obj->yaw, obj->pitch, &vec[0], &vec[1], &vec[2]);
    vec[0] += obj->x >> 12;
    vec[1] += obj->y >> 12;
    vec[2] += obj->z >> 12;
    fx_entry_spawn(obj, (Vec3 *)vec);
}

/* Reads the s16 at stream->cursor and advances the cursor by 2 bytes. */
void script_op_fx_spawn(u8 **stream) {
    u8 *cursor;
    s32 frame_pad[4]; /* keeps the 0x28-byte frame of the original */

    cursor = stream[8];
    stream[8] = cursor + 2;
    fx_slot_spawn((s32)stream, *(s16 *)cursor);
}

void fx_stop_by_id(s32 id);
void script_op_fx_stop(BytecodeCursor *cursor) {
    /* the original reserves 16 bytes of stack here; keeps the frame size */
    s32 frame_pad[4];
    s16 *pc = cursor->pc;
    cursor->pc = pc + 1;
    fx_stop_by_id(*pc);
}

/* Reads two halfwords from the object's stream (the pointer at unk_1C.unk_04).
   If the first one is below health * 4096 / vars.enemy.unk_274, the stream jumps
   to the table entry the second one picks. */
void script_op_jump_if_health_below(Object *obj) {
    /* the original reserves 16 bytes of stack here; keeps the frame size */
    s32 frame_pad[4];
    s16 *cursor;
    s32 scaled_health;
    s32 key;
    s32 entry;

    cursor = obj->script.pc;
    scaled_health = (obj->health << 12) / obj->vars.supermech.max_health;
    obj->script.pc = cursor + 1;
    key = cursor[0];
    obj->script.pc = cursor + 2;
    entry = cursor[1];
    if (key < scaled_health) {
        obj->script.pc = ((s16 **)obj->script.data)[entry];
    }
}

s32 is_outside_bounds(s32 arg0, s32 arg1);
void script_op_jump_if_outside(Object *obj) {
    s16 *pc;
    s32 op;

    pc = obj->script.pc;
    obj->script.pc = pc + 1;
    op = *pc;
    if (is_outside_bounds(obj->x >> 12, obj->z >> 12) != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
}

/* Reads one halfword from the byte stream at obj->unk_1C.unk_04, advances the
   stream by 2 bytes, and stores the value in the low half of the shot timer. */
void script_op_set_shot_timer(Object *obj) {
    u16 *stream;

    stream = (u16 *)obj->script.pc;
    obj->script.pc = (s16 *)(stream + 1);
    *(s16 *)&obj->vars.enemy.shot_timer = *stream;
}

/* Bytecode step: read (threshold, index) from the cursor at unk_1C.unk_04, advance past them,
 * and if rand < threshold jump the cursor to the table entry at index. */
void script_op_jump_if_rand(Object *obj) {
    s32 threshold;
    s32 index;
    s16 *cursor;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = *(s16 *)cursor;
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (rand_a_next() < threshold) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_op_jump_if_turn_left(Object *obj) {
    s16 *cursor;
    s32 op;
    s32 *player;
    s32 target;
    s32 yaw;
    s32 delta;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    op = *cursor;

    player = player_position();
    target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));

    yaw = obj->yaw;
    yaw &= 0xFFF;
    if (yaw >= 0x800) {
        yaw -= 0x1000;
    }
    delta = angle_approach(yaw, target, 0x800) - yaw;
    delta &= 0xFFF;
    if (delta >= 0x800) {
        delta -= 0x1000;
    }
    if (delta < 0) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
}

/* Script op: when the player is below y -0x590, jump to the table entry for this op's index. */
void script_op_jump_if_player_below(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 op;

    obj->script.pc = pc + 1;
    op = *pc;
    if (player_position()[1] < -0x590) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
}

/* Reads the next halfword of the object's stream (the pointer at 0x20) and passes it to scroll_seg_start. */
void script_op_set_move_mode(Object *obj) {
    s16 *stream = obj->script.pc;

    obj->script.pc = stream + 1;
    obj_set_move_mode(obj, *stream);
}

/* Stores a random halfword at 0x27E, the upper half of vars.words[13]. */
void script_op_roll_random(Object *obj) {
    s16 *half = (s16 *)&obj->vars.supermech.unk_27C;

    half[1] = rand_a_next();
}

/* Reads two halfwords from the object's stream (the pointer at 0x20). If the
 * random halfword at 0x27E is below the first, the stream pointer becomes the
 * table entry indexed by the second halfword. */
void script_op_jump_if_roll(Object *obj) {
    s16 *stream = obj->script.pc;
    s16 *half = (s16 *)&obj->vars.supermech.unk_27C;
    s32 rnd = half[1];
    s32 limit;
    s32 index;

    obj->script.pc = stream + 1;
    limit = stream[0];
    obj->script.pc = stream + 2;
    index = stream[1];
    if (rnd < limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_op_set_sound(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->vars.snd2.sound[1] = *cursor;
}

void script_read_fixed4(ScriptCtx *ctx) {
    s16 *p = ctx->cursor;

    ctx->cursor = p + 1;
    ctx->value = p[0] << 4;
}

extern s32 get_angle_to_player(s32 *pos);
void script_op_chaser_mode(Object *obj) {
    s32 pos[4];
    s32 pos2[6];
    s32 *pp;
    s32 dist;
    s32 yaw;
    s32 op;
    u8 mode;

    op = obj_read_s16(obj);
    mode = op;
    obj->vars.chaser.mode = mode;
    if (op == 1) {
        pp = player_position();
        pos[0] = obj->x >> 12;
        pos[2] = obj->z >> 12;
        obj->vars.chaser.target_x = pp[0] << 12;
        obj->vars.chaser.target_z = pp[2] << 12;
        dist = player_horiz_dist(pos);
        if (dist < 0x320) {
            dist = 0x320;
        }
        obj->vars.chaser.target_dist = dist;
        yaw = player_angle_to((Vec3 *)pos) & 0xFFF;
        if (yaw >= 0x800) {
            yaw -= 0x1000;
        }
        obj->vars.chaser.target_yaw = yaw;
        return;
    }
    if (mode == 2) {
        pos2[0] = obj->x >> 12;
        pos2[1] = obj->y >> 12;
        pos2[2] = obj->z >> 12;
        obj->vars.chaser.target_dist = get_angle_to_player(pos2);
    }
}

/* Reads the halfword at the cursor kept in ObjLink unk_1C.unk_04 (object +0x20), advances the cursor by 2,
 * and stores the halfword at 0x282 (upper half of vars.words[14]). */
void script_op_set_turn(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;
    s16 *half = (s16 *)&obj->vars.supermech.unk_280;

    obj->script.pc = (s16 *)(cursor + 1);
    half[1] = *cursor;
}

/* Script op: reads the table index at the script pointer (obj->unk_1C.unk_04) and advances past it.
 * If vars.words[9] + vars.words[10] is not positive, jumps the pointer to that entry of the
 * object's jump table (obj->unk_1C.data). */
void script_op_jump_if_sum_nonpositive(Object *obj) {
    s32 sum;
    s16 *pc;
    s32 index;

    sum = obj->vars.supermech.speed;
    sum += obj->vars.supermech.acceleration;
    pc = obj->script.pc;
    obj->script.pc = pc + 1;
    index = *pc;
    if (sum <= 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op: reads the opcode at the script pointer (obj->unk_1C.unk_04) and advances the pointer past it.
 * If the halfword flag at 0x286 is set, the pointer jumps to the per-type table entry for the opcode
 * (obj->unk_1C.data, 32-bit entries). The flag is cleared either way. */
void script_op_jump_if_flag(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 op;

    obj->script.pc = pc + 1;
    op = *pc;
    if (((s16 *)&obj->vars.supermech.unk_284)[1] != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
    ((s16 *)&obj->vars.supermech.unk_284)[1] = 0;
}

/*
 * Track-follow step: reads a (threshold, table index) pair from the object's
 * cursor and advances it. When the ratio health<<12 / vars.enemy.unk_274 is
 * below the threshold, it jumps the cursor to the table entry; the 0x286
 * flag (raw, no stage.h field yet) is cleared either way.
 */
void script_op_jump_if_health_flag(Object *obj) {
    s16 *cursor;
    s32 threshold;
    s32 table_index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    table_index = cursor[1];
    if (((s32) (obj->health << 12) / obj->vars.supermech.max_health) < threshold) {
        if (((s16 *)obj->vars.words)[0x1F] != 0) {
            obj->script.pc = ((s16 **)obj->script.data)[table_index];
        }
        ((s16 *)obj->vars.words)[0x1F] = 0;
    }
}

void ring_index_dec(void) {
    value_queue_index -= 1;
    value_queue_index = MAX(MIN(value_queue_index, 0xF), 0);
}

/* Clears the halfword at 0x286: the upper half of words[15], which stage.h has no field for. */
void script_flag_clear(Object *obj) {
    ((s16 *)&obj->vars.supermech.unk_284)[1] = 0;
}

/* Projects two points from the player, at the object's distance and at its
 * angle +-0xD7, and tests each against the 0xDAD box around (-0x2EE00, 0)
 * (fly_move's outputs added crosswise to the player's x/z). Starts at 3; the
 * first point outside gives 2, the second outside clears bit 1. */
s32 obj_turn_probe(Object *obj) {
    Vec3 pos;
    s32 delta[2];
    s32 *player;
    s32 result;
    s32 dist;
    s32 angle;
    s32 along;
    s32 across;
    s32 add;
    s32 player_z;

    player = player_position();
    result = 3;
    pos.x = obj->x >> 12;
    pos.z = obj->z >> 12;
    dist = player_horiz_dist((s32 *)&pos);
    angle = player_angle_to(&pos) & 0xFFF;
    if (angle >= 0x800) {
        angle -= 0x1000;
    }

    fly_move(angle + 0xD7, dist, &delta[0], &delta[1]);
    add = 0x2EE00;
    along = delta[1] >> 12;
    across = delta[0] >> 12;
    delta[1] = along;
    do { } while (0);
    along += add;
    delta[0] = across;
    add = player[0];
    player_z = player[2];
    delta[1] = along + add;
    delta[0] = across + player_z;
    delta[1] = ABS(delta[1]);
    delta[0] = ABS(delta[0]);
    if (delta[1] >= 0xDAD || delta[0] >= 0xDAD) {
        result = 2;
    }

    fly_move(angle - 0xD7, dist, &delta[0], &delta[1]);
    add = 0x2EE00;
    along = delta[1] >> 12;
    across = delta[0] >> 12;
    delta[1] = along;
    do { } while (0);
    along += add;
    delta[0] = across;
    add = player[0];
    player_z = player[2];
    delta[1] = along + add;
    delta[0] = across + player_z;
    delta[1] = ABS(delta[1]);
    delta[0] = ABS(delta[0]);
    if (delta[1] >= 0xDAD || delta[0] >= 0xDAD) {
        result &= ~2;
    }
    return result;
}

s32 obj_turn_probe(Object *obj);
/* Reads one op from the object's stream (unk_1C.unk_04) and advances it by 2. obj_turn_probe
 * decides the result: 0 jumps the stream to the data table's entry for op; the low and high bits
 * step the halfword at words[14] (upper half, 0x282) to +1 or -1 unless it already points that way. */
void script_op_turn_step(Object *obj) {
    s16 *stream;
    s32 op;
    s32 turn;
    s32 result;

    turn = ((s16 *)&obj->vars.supermech.unk_280)[1];
    stream = obj->script.pc;
    obj->script.pc = stream + 1;
    op = *stream;
    result = obj_turn_probe(obj);
    if (result == 0) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
    if (result != 3) {
        if (result & 1) {
            if (turn > 0) {
                return;
            }
            turn = 1;
        }
        if (result & 2) {
            if (turn < 0) {
                return;
            }
            turn = -1;
        }
        ((s16 *)&obj->vars.supermech.unk_280)[1] = turn;
    }
}

/* Reads a (table index, value) halfword pair from the object's stream at unk_1C.unk_04
 * and advances the stream by 4. The index selects a s32 from the type's data table, which
 * becomes the new stream cursor. The value is passed on to value_queue_push only while
 * health * 4096 / vars.enemy.unk_274 is below 0x555. */
void script_op_jump_if_health_low(Object *obj) {
    s16 *stream;
    s32 table_index;
    s32 value;

    stream = obj->script.pc;
    obj->script.pc = stream + 1;
    table_index = stream[0];
    obj->script.pc = stream + 2;
    value = stream[1];
    if ((((s32)obj->health << 12) / obj->vars.supermech.max_health) < 0x555) {
        obj->script.pc = ((s16 **)obj->script.data)[table_index];
        value_queue_push(value);
    }
}

/* Script op: reads a jump index, moves ahead along vars.words[8] at speed
 * unk_282 * 0x549 from the object's position; if the point is over 3000 units
 * from x = -0x2EE00 or from z = 0 (fly_move's outputs added crosswise), jumps the script to that table entry. */
void fly_path_next(Object *obj) {
    s32 dx;
    s32 dz;
    s16 *cursor;
    s32 index;
    s32 dist_z;
    s32 x;
    s32 z;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    index = *cursor;
    fly_move(obj->vars.supermech.unk_268, obj->vars.part.unk_282 * 0x549, &dx, &dz);
    x = obj->x;
    dz += x;
    z = obj->z;
    dx += z;
    dist_z = (dz >> 12) + 0x2EE00;
    if (dist_z < 0) {
        dist_z = -0x2EE00 - (dz >> 12);
    }
    dz = dist_z;
    dx = ABS(dx >> 12);
    if (dz > 3000 || dx > 3000) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

extern s32 obj_loop_sound_id;

void obj_loop_sound_start(Object *obj) {
    s32 temp_v0;

    if (obj_loop_sound_id == 0) {
        temp_v0 = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x7F, 0, 0);
        obj_loop_sound_id = temp_v0;
        if (temp_v0 != 0) {
            sound_attach(temp_v0, &obj->x, NULL);
        }
    }
}

extern s32 obj_loop_sound_id;

void obj_loop_sound_stop(Object *obj, s32 arg) {
    if (obj_loop_sound_id != 0) {
        sound_stop(obj_loop_sound_id);
        obj_loop_sound_id = 0;
    }
}

void obj_sound_play(Object *obj) {
    s32 temp_v0;

    temp_v0 = sound_start(0x51745175, 0x7F, 0, 0);
    if (temp_v0 != 0) {
        sound_attach(temp_v0, &obj->x, NULL);
    }
}

void supermech_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

extern s32 supermech_trail_count;
extern TrailPos supermech_trail_pos[];
extern SVECTOR supermech_trail_rot[];
void obj_turn_toward_target(Object *obj, s32 mode, s32 step);
void supermech_step(Object *obj, ObjHandler *handler) {
    s32 dx;
    s32 dz;
    s32 mode;
    s32 yaw;
    register s32 new_yaw asm("$4");
    s32 idx;
    TrailPos *pos;
    SVECTOR *rot;

    dx = 0;
    dz = 0;
    yaw = obj->yaw;
    new_yaw = (u16)obj->vars.supermech.yaw_offset + yaw;
    obj->vars.supermech.speed += obj->vars.supermech.acceleration;
    obj->yaw = new_yaw;
    if (obj->vy < 0) {
        obj->unk_1B7 = 0;
    }
    obj_turn_toward_target(obj, obj->vars.part.turn_rate, obj->vars.part.unk_27C);
    mode = obj->vars.part.move_mode;
    if (mode == 0) {
        fly_move(obj->yaw, obj->speed, &dx, &dz);
        obj->vz = dx;
        obj->vx = dz;
    } else if (mode == 2) {
        fly_move(obj->vars.supermech.unk_268, (obj->vars.supermech.speed / 0x1000) * obj->vars.part.unk_282, &dx, &dz);
        obj->vz = dx;
        obj->vx = dz;
    } else {
        obj->vars.supermech.unk_260 += ratan2(obj->vars.supermech.speed / 0x1000, obj->vars.supermech.unk_268) * obj->vars.part.unk_282;
        fly_move(obj->vars.supermech.unk_260, obj->vars.supermech.unk_268, &dx, &dz);
        dz += obj->vars.supermech.center_x;
        dx += obj->vars.supermech.center_z;
        dz -= obj->x;
        dx -= obj->z;
        obj->vz = dx;
        obj->vx = dz;
    }
    obj_script_step(obj, handler);

    /* 32-entry history ring of position and rotation */
    idx = trail_write_index;
    pos = &supermech_trail_pos[idx];
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    rot = &supermech_trail_rot[idx];
    rot->vx = obj->pitch;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    trail_write_index = idx + 1;
    trail_write_index = (idx + 1) % 32;
    supermech_trail_count++;
    supermech_trail_count = MAX(MIN(supermech_trail_count, 4), 1);
}


void obj_hit_reaction(Object *obj, s32 arg1) {
    u8 *block;
    s32 pos;
    s32 pitch;
    s32 pad[2]; /* keeps the original 0x28-byte frame */

    block = obj->unk_A4;
    pos = obj->type.unk_0E + (arg1 + ((s32 *)obj->asset)[1]);
    pitch = obj->pitch;
    *(u16 *)&block[0x2E] = obj->yaw;
    *(u16 *)&block[0x30] = obj->roll;
    *(s16 *)&block[0x2C] = -pitch;
    block[1] = 1;
    block[0] = obj->index;
    obj_block_fill(obj, block);
    solid_setup_scratch(obj->solid_id, block, (s16)pos, obj->unk_190);
    fn_800FB460(obj, block);
}


void obj_hit_reaction(Object *obj, s32 arg1);
s32 obj_hit_mask_avg(s32 mask, s16 *values);
extern s16 hit_mask_values[];
void chaser_take_hit(Object *obj, s16 *out) {
    s32 step;
    s32 amount;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    step = obj_hit_damage(obj->index);
    if (obj->hit_cooldown != 0) {
        obj->hit_cooldown += 0xFF;
    }
    amount = step * obj->vars.chaser.damage_scale;
    step = amount >> 12;
    if (amount < 0) {
        step = (amount + 0xFFF) >> 12;
    }
    if (step > 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        amount = step * obj_hit_mask_avg(obj_hit_type(obj->index) & 0xFF, hit_mask_values);
        step = amount >> 12;
        if (amount < 0) {
            step = (amount + 0xFFF) >> 12;
        }
        obj->vars.chaser.damage += step;
        obj->health -= step;
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
    if (obj->health <= 0) {
        out[9] = 1;
        obj_set_hit_reaction(obj, 0);
        obj->vars.chaser.mode = 0;
        obj_actors_clear_index();
        return;
    }
    if (test_bit(obj->flags, 5)) {
        obj_hit_reaction(obj, 0);
    }
}


/* Calls the object's hook at 0x170 (if set) with the object as its argument. */
void obj_hook_call(Object *obj, ObjHandler *handler) {
    s32 frame_pad[6]; /* unused: keeps the frame at 0x30 bytes, as in the original */
    void (*hook)(Object *) = (void (*)(Object *))obj->callback;
    if (hook != NULL) {
        hook(obj);
    }
}


void chaser_dispatch(Object *obj, ObjHandler *handler) {
    s16 state = handler->state;

    if (state == 0) {
        chaser_take_hit(obj, (s16 *)handler);
        meter_set(obj->health, obj->vars.supermech.max_health);
    }
    if (handler->state != 0) {
        obj_loop_sound_stop(obj, 0);
        obj_hook_call(obj, handler);
    }
}

extern s32 supermech_trail_parity;
extern s32 supermech_trail_count;
extern s32 seq_slots[][7];
extern TrailPos supermech_trail_pos[];
extern SVECTOR supermech_trail_rot[];
void supermech_draw_trail(Object *obj) {
    s32 t;
    Vec3 pos;
    SVECTOR rot;
    SVECTOR rot2;
    s32 model;
    s32 colour;
    s32 *rec;
    u32 kind;
    s32 notbit;
    s32 scale;
    s32 i;
    s32 idx;
    TrailPos *tp;
    SVECTOR *tr;
    s32 pitch;
    s32 hit;
    u32 flags;

    if (is_paused() == 0) {
        supermech_trail_parity = supermech_trail_parity == 0;
    }
    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    kind = obj->type.unk_0E;
    {
        register u32 offset asm("$2") = kind - 0x108;
        notbit = offset >= 0x10;
    }
    if ((u32)(kind - 0x127) <= 0xF) {
        notbit = 0;
    }
    flags = obj->flags;
    if (((flags >> 6) & 1) || notbit == 0) {
        model = kind + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        model = obj_keyframe_value(obj, 0);
    }
    pchr_lists_build(model);
    model = pchr_copy_slot(model);
    rec = pchr_poses_build(model);
    seq_slots[model & 0x7FF][0] = (s32)rec;
    obj->vars.supermech.unk_248 = (s32)rec;
    hit = obj->hit;
    FAKE_OPAQUE(hit);
    colour = 0;
    FAKE_OPAQUE(colour);
    if (hit > 0) {
        colour = 0x60C0FF;
    }
    spark_add(pos.x, pos.y, pos.z, rot.vy, rot.vx, rot.vz, model, colour);

    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    rot2.vx = obj->width;
    rot2.vy = obj->height;
    rot2.vz = obj->unk_1E8[0];
    aim_marker_draw(2, &rot2, &pos, 0);
    if (obj->vars.chaser.mode != 0 && supermech_trail_count >= 2) {
        scale = 0x1000;
        i = 1;
        model = model_slot_pchr(*(s32 *)obj->asset) + 2;
        while (i < supermech_trail_count) {
            if (scale == 0) {
                break;
            }
            t = scale >> 5;
            colour = (t << 8) | (0x800000 | t);
            idx = ring_index_delta(i * 2 + supermech_trail_parity);
            tp = &supermech_trail_pos[idx];
            tr = &supermech_trail_rot[idx];
            spark_add(tp->x, tp->y, tp->z, tr->vy, tr->vx, tr->vz, model, colour);
            i++;
            t = scale * 3;
            if (t < 0) {
                t += 3;
            }
            scale = t >> 2;
        }
    }
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

extern s32 sound_pair_active;
extern s32 sound_pair_a_handle;
extern s32 sound_pair_b_handle;
extern s32 sound_pair_volume;
extern s32 sound_pair_volume_step;

void sound_pair_start(void) {
    if (sound_pair_active == 0) {
        sound_play(SND_S12_MECH_MOVE_START | SND_GROUP(1), 0x7F, 0x3F, 0x3C);
        sound_play(SND_MECH_MOVE_START | SND_GROUP(1), 0x7F, 0x3F, 0x3C);
        sound_pair_volume = 0x1000;
        sound_pair_volume_step = 0;
        sound_pair_a_handle = sound_play(SND_MECH_MOVE_A_LOOP | SND_HELD | SND_GROUP(1), 0x7F, 0x3F, 0x3C);
        sound_pair_b_handle = sound_play(SND_MECH_MOVE_B_LOOP | SND_HELD | SND_GROUP(1), 0x7F, 0x3F, 0x3C);
        sound_pair_active = 1;
    }
}

void sound_fall_start(void) {
    sound_play(SND_FALL_START | SND_GROUP(2), 0x7F, 0x3F, 0x3F);
}

extern s32 sound_fade_out_flag;
extern s32 sound_pair_volume_step;

void sound_fade_out_start(void) {
    if (sound_fade_out_flag == 0) {
        sound_play(0x51785179, 0x7F, 0x3F, 0x3C);
        sound_pair_volume_step = -0x40;
        sound_fade_out_flag = 1;
    }
}

extern s32 sound_pair_a_handle;
extern s32 sound_pair_b_handle;

void sound_pair_stop(void) {
    if (sound_pair_a_handle >= 0) {
        sound_note_request(sound_pair_a_handle, 0, 0x3F, 0x3C);
        sound_pair_a_handle = -1;
    }
    if (sound_pair_b_handle >= 0) {
        sound_note_request(sound_pair_b_handle, 0, 0x3F, 0x3C);
        sound_pair_b_handle = -1;
    }
}

extern s32 sound_pair_a_handle;
extern s32 sound_pair_b_handle;
extern s32 sound_pair_volume;
extern s32 sound_pair_volume_step;

void sound_pair_fade_update(void) {
    s32 temp_s0;

    temp_s0 = sound_pair_volume + sound_pair_volume_step;
    sound_pair_volume = temp_s0;
    if (sound_pair_a_handle >= 0) {
        sound_pair_a_handle = sound_note_request(sound_pair_a_handle, sound_volume_of(SND_MECH_MOVE_A_LOOP | SND_HELD | SND_GROUP(1), temp_s0), 0x3F, 0x3C);
    }
    if (sound_pair_b_handle >= 0) {
        sound_pair_b_handle = sound_note_request(sound_pair_b_handle, sound_volume_of(SND_MECH_MOVE_B_LOOP | SND_HELD | SND_GROUP(1), temp_s0), 0x3F, 0x3C);
    }
    if (temp_s0 <= 0) {
        sound_pair_volume = 0;
        sound_pair_volume_step = 0;
        sound_pair_a_handle = -1;
        sound_pair_b_handle = -1;
    }
}

extern s32 supermech_model_id[3];
/* Passes get_player_status's result to set_player_status, calls mode_reset, then pchr_copy_range with the entry for supermech_model_id offset by 0x80. */
void player_status_reload(void) {
    s32 entry;

    set_player_status(get_player_status());
    mode_reset();
    entry = model_slot_pchr(supermech_model_id[0]);
    pchr_copy_range(entry + 0x80, 0x163, entry);
}

extern SoundVolume D_8011FC44[8];
extern ScriptCallEntry D_80120630[48];
extern StateEntry D_8012159C[21];
extern s16 *supermech_script_data[206];
extern s16 *D_80121598;
extern s16 *supermech_script_entry[44];
void chaser_dispatch(Object *obj, ObjHandler *handler);
void stage_systems_init(void);
void burst_check_sphere_if_ready();
s32 particles_spawn(void);
void bounds_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void particle_spawn_param_set(s32 arg0);
void supermech_reset_flag(void);
/* Spawns the M12 supermech: handlers, script, hit setup, meter, bounds and sound state. */
s32 supermech_spawn(Placement *place) {
    Object *obj;
    ObjHandler *h;
    s16 **script;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), &obj->node);
    *(s16 *)&place->unk_00[2] = -1;
    h = obj->handlers;
    obj->handlers[0].fn = (void *)supermech_phase0;
    obj->handlers[1].fn = supermech_step;
    obj->handlers[2].fn = chaser_dispatch;
    obj->handlers[3].fn = (void *)supermech_draw_trail;
    obj->callback = (s32)giant_robot_teardown;
    obj->asset = supermech_model_id;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = D_80120630;
    obj->state_table = D_8012159C;
    obj->sounds = D_8011FC44;
    h[0].unk_11 = 0;
    *(volatile s16 *)&h[0].state = 0;
    h[1].unk_11 = 0;
    *(volatile s16 *)&h[1].state = 0;
    h[2].unk_11 = 0;
    *(volatile s16 *)&h[2].state = 0;
    h[3].unk_11 = 0;
    *(volatile s16 *)&h[3].state = 0;
    *(volatile s16 *)&obj->unk_1C6 = 0;
    obj->script.data = (void *)supermech_script_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_80121598;
    script = supermech_script_entry;
    script_start((Script *)obj, *script, (s32)script);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 1, 0x1800);
    ((void (*)(Object *))stage_systems_init)(obj);
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, 0x19);
    obj->vars.supermech.yaw_offset = 0;
    obj->vars.supermech.unused_278 = 0;
    obj->vars.part.unused_27A = 0;
    obj->vars.part.unk_27C = 0;
    obj->vars.part.turn_rate = 2;
    obj->vars.supermech.max_health = obj->health;
    obj->vars.part.kind = rand_a_next();
    obj->vars.part.unk_280 = 0;
    obj->vars.part.move_mode = 0;
    obj->vars.supermech.speed = 0;
    obj->vars.supermech.acceleration = 0;
    obj->vars.part.unused_286 = 0;
    meter_set(obj->health, obj->vars.supermech.max_health);
    meter_set_mode(0);
    obj_set_hit_reaction(obj, 0);
    proximity_hook_set((s32)burst_check_sphere_if_ready);
    angles_from_vectors_set();
    ((s32 (*)(Object *))particles_spawn)(obj);
    value_queue_index = 0;
    bounds_set(0xFFFD0648, 0xFFFD1DB8, -0xBB8, 0xBB8);
    obj_loop_sound_id = 0;
    obj_hit_flag_set(obj->index, 0x80);
    particle_spawn_param_set(model_slot_pchr(*(s32 *)obj->asset));
    sound_pair_a_handle = -1;
    sound_pair_b_handle = -1;
    trail_write_index = 0;
    supermech_trail_count = 0;
    supermech_trail_parity = 0;
    sound_pair_active = 0;
    sound_fade_out_flag = 0;
    sound_pair_volume = 0x1000;
    sound_pair_volume_step = 0;
    supermech_reset_flag();
    return 1;
}

void giant_robot_systems_teardown(void);
/* Tears an object down: resets the two globals, frees its asset-driven index and removes it. */
void giant_robot_teardown(Object *obj) {
    s32 offset;
    s32 index;

    meter_set_mode(0);
    set_d_801202C8(0);
    giant_robot_systems_teardown();
    index = obj->type.unk_0E;
    offset = model_slot_pchr(*(s32 *)obj->asset);
    obj_spawn_replacement(obj, index + offset);
    obj_free(obj);
}


void obj_set_extents_from_part(Object *obj, s32 part, s32 part_arg) {
    u16 ext[3];
    s32 unused[2];
    u16 depth;
    s32 span;
    s32 y;
    s16 y_copy;
    s16 span_copy;

    model_part_extents_max(part, part_arg, ext);
    obj->unk_190 = part_arg;
    obj->width = ext[0];
    obj->height = ext[1];
    obj->unk_1E8[0] = depth = ext[2];
    y = (s16)obj->height;
    span = (s16)depth;
    y_copy = y;
    if (span < obj->width) {
        span = obj->width;
    }
    span_copy = span;
    obj->extents[0] = span_copy;
    obj->extents[1] = y_copy;
    obj->extents[2] = span_copy;
    obj->bound_radius = isqrt(length_sq(span, y, span));
}
