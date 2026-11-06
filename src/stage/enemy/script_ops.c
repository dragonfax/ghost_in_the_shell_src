/* script_ops: one of the original source files (scripts/objmap.py); s01. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Script op: reads a halfword from the cursor, advances it, sets vy to the value << 12. */
void script_op_set_vy(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->vy = *cursor << 12;
}

/* Reads a code from the object's script cursor (ObjLink unk_04) and, while vy is not negative, replaces
 * the cursor with the entry for that code in the table at data. */
void script_op_jump_if_vy_nonneg(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 code;

    obj->script.pc = cursor + 1;
    code = *cursor;
    if (obj->vy >= 0) {
        obj->script.pc = ((s16 **)obj->script.data)[code];
    }
}

void script_value_queue_push(ValueScript *script) {
    s16 value = *script->pc++;

    value_queue[value_queue_index++] = value;
    value_queue_index = MAX(MIN(value_queue_index, 0xF), 0);
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

/* Script op: reads two halfwords at the script pointer (obj + 0x20), an index and a value, and stores the
 * value in the halfword table at vars.h.unk_252 + index (cf. obj_script_set_var_rand). */
void obj_script_set_var(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 index;

    obj->script.pc = pc + 1;
    index = *pc;
    obj->script.pc = pc + 2;
    (&obj->vars.giant_robot.script_vars)[index] = pc[1];
}

/* Reads two entries from the script at obj->unk_1C.unk_04 (an index, then a value) and stores the value
 * in the halfword table at vars.h.unk_252. */
void obj_script_set_var_rand(Object *obj) {
    s16 **script = &obj->script.pc;
    s16 *pc;
    s32 index;

    pc = *script;
    *script = pc + 1;
    index = *pc;
    rand_a_next();
    pc = *script;
    *script = pc + 2;
    (&obj->vars.giant_robot.script_vars)[index] = ((u16 *)pc)[1];
}

/* Reads two script words: a counter index, then a jump index. While the u16 counter at +0x252 for the
 * first index is above zero, the object jumps to table[jump index] (the table is at unk_1C.data);
 * otherwise the cursor steps past the jump index. The counters are u16s at +0x252, one per index.
 * `target` holds the counter index first and the new cursor last (the permuter's register reuse). */
s32 obj_script_loop(Object *obj) {
    s16 *cursor;
    s16 *next;
    s32 jump;
    s32 remaining;
    s32 target;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    target = cursor[0];
    remaining = *(u16 *) ((u8 *) obj + 0x252 + target * 2) - 1;
    *(u16 *) ((u8 *) obj + 0x252 + target * 2) = remaining;
    if ((s16) remaining <= 0) {
        target = (s32)(obj->script.pc + 1);
    } else {
        next = obj->script.pc;
        obj->script.pc = next + 1;
        jump = next[0];
        target = ((s32 *) obj->script.data)[jump];
    }
    obj->script.pc = (s16 *)target; /* target doubles as the index and the cursor (register reuse) */
    return target;
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

void obj_roll_random(Object *obj) {
    obj->vars.giant_robot.random_roll = rand_a_next();
}

/* Script op: if the op is not below obj->unk_25A, jump to the table entry given by the next word. */
void obj_script_jump_if_roll_le(Object *obj) {
    s16 op = obj_read_s16(obj);
    s16 target = obj_read_s16(obj);

    if (op >= obj->vars.giant_robot.random_roll) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

/* Script op: if obj->vars.enemy.unk_25C equals the op, jump to the table entry given by the next word. */
void obj_script_jump_if_equal(Object *obj) {
    s16 op = obj_read_s16(obj);
    s16 target = obj_read_s16(obj);

    if (obj->vars.giant_robot.unk_25C == op) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

void script_set_enemy_var(Object *obj) {
    obj->vars.enemy.unk_25C = obj_read_u16(obj);
}

/* Script op: reads a fade direction word, plays sound 0x3A at the object's
 * position and sets fade_dir. The s16 range check never fires (the word is read
 * as s16), but it shapes the code: combine folds it away only after flow, so the
 * word stays live across the first call (s0) and dir has two sets (no sched1 boost,
 * the copy to s2 stays among the position stores). */
void obj_play_fade_sound(Object *obj) {
    VECTOR sound_pos;
    VECTOR *pos = &sound_pos;
    s32 word = obj_read_s16(obj);
    s16 dir = word;

    pos->vx = obj->x >> 12;
    pos->vy = obj->y >> 12;
    pos->vz = obj->z >> 12;
    sound_scale_pos_about_listener(pos, pos, 0x800);
    if (dir != word) {
        word = (word < 0) ? -0x8000 : 0x7FFF;
        dir = word;
    }
    sound_play_at_units(SND_POWER_ON, 0x7F, 0x3C, pos);
    set_fade_dir(dir);
}

void obj_sway_start(Object *obj) {
    s16 offset[3];
    s16 angles[3];

    offset[0] = 0;
    offset[1] = -0xD1;
    offset[2] = -0x9F;
    angles[0] = 0;
    angles[1] = (u16) obj->yaw;
    angles[2] = 0;
    sway_start(obj, offset, angles);
    keyframe_ramp_alloc_wrapper(obj, offset, angles);
}

void script_op_sway_reset(void) {
    sway_reset_params();
}

void script_op_sound_loop_start(void) {
    sound_loop_start();
}

void script_op_sound_loop_stop(void) {
    sound_loop_stop();
}

void script_op_flag_set(void) {
    flag_set();
}

void script_op_clear_flag(void) {
    flag_clear();
}

void script_op_set_yaw_rate(Object *obj) {
    obj->unk_226[0] = obj_read_u16(obj);
}

/* Jitters the object's yaw and pitch by random amounts (obj_point_to_world and rot_turn_toward derive the
 * vector and angle table first), then hands the vector and angles to shot_pool_take with sound_play_at_units's
 * effect. */
void obj_fire_shot(Object *obj) {
    s16 offset[3];
    u16 angles[3];
    s32 pos[3];
    s32 v;
    s32 pitch;
    s32 yaw_jitter;
    s32 pitch_jitter;

    offset[0] = 0;
    offset[1] = -0x16E;
    offset[2] = 0xB9;
    obj_point_to_world(obj, offset, &pos[0], &pos[1], &pos[2]);
    pitch = obj->pitch;
    angles[0] = pitch - 0x20;
    angles[1] = (u16) obj->yaw;
    angles[2] = (u16) obj->roll;
    rot_turn_toward(pos, angles, 0xC0, 0xC0);
    v = rand_a_next();
    yaw_jitter = angles[1] - 0x40;
    if (v < 0) {
        v += 0x1F;
    }
    angles[1] = yaw_jitter + (v >> 5);
    v = rand_a_next();
    pitch_jitter = angles[0] - 0x10;
    if (v < 0) {
        v += 0x7F;
    }
    angles[0] = pitch_jitter + (v >> 7);
    angles[2] = 0;
    shot_fire_sound_stop();
    sound_play_at_units(SND_SHOT_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    shot_pool_take(obj, pos, angles);
}

void loop_state_start(Object *owner, Vec3 *pos, s32 unk_1C);
void obj_loop_anim_start(Object *obj) {
    Vec3 pos;
    s32 anim = model_slot_pchr(*(s32 *)obj->asset);

    pos.x = 0;
    pos.y = 0x40;
    pos.z = -0x16;
    loop_state_start(obj, &pos, anim + 0xB8);
}

void script_op_state_stop(void) {
    state_stop();
}

/* Script op: read the next halfword operand and pass it to obj_set_target. */
void script_op_set_target(ObjScript *script) {
    obj_set_target(*script->pc++);
}

/* Passes the object's position to sound_set_pos through a scratch vector. */
s32 obj_sound_track(Object *obj, s32 arg) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    sound_set_pos(arg, pos);
    scratch_top -= 0x10;
    return 0;
}

/* Starts the object's looping sound (id 0xA024) once and hands it the update callback. */
void giant_robot_fx_sound_start(Object *obj) {
    if (obj->vars.snd.sound == 0) {
        s32 handle = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x7F, 0, 0);

        obj->vars.snd.sound = handle;
        if (handle != 0) {
            sound_attach(handle, obj, (void (*)())obj_sound_track);
        }
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

void giant_robot_fx_start(Object *obj) {
    giant_robot_fx_sound_start(obj);
    giant_robot_fx_set_active(1);
}

void giant_robot_fx_stop(Object *obj) {
    obj_sound_release(obj);
    giant_robot_fx_set_active(0);
}

void giant_robot_side_fx(Object *obj) {
    s16 delta[3];
    s16 rot[3];
    s32 pos[3];
    s32 yaw;

    delta[0] = 0x22;
    delta[1] = -0x1E3;
    delta[2] = 0x5A;
    obj_point_to_world(obj, delta, &pos[0], &pos[1], &pos[2]);
    rot[0] = 0x380;
    yaw = obj->yaw;
    rot[1] = yaw + 0x200;
    rot[2] = 0;
    shot_spawn_obj(pos, (u16 *)rot, 2, (s32)&giant_robot_side_shot_setup);

    delta[0] = -0x22;
    delta[1] = -0x1E3;
    delta[2] = 0x5A;
    obj_point_to_world(obj, delta, &pos[0], &pos[1], &pos[2]);
    rot[0] = 0x380;
    yaw = obj->yaw;
    rot[1] = yaw - 0x200;
    rot[2] = 0;
    sound_play_at_units(SND_TWIN_SHOT_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    shot_spawn_obj(pos, (u16 *)rot, 2, (s32)&giant_robot_side_shot_setup);
}

/* Reads two s16 values from the object's script cursor (ObjLink unk_1C.unk_04); if the first is below
 * get_fade_level's result, the cursor jumps to entry `second` of the table at unk_1C.data. */
void script_jump_if_below(Object *obj) {
    s16 *cursor;
    s32 first;
    s32 second;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    first = cursor[0];
    obj->script.pc = cursor + 2;
    second = cursor[1];
    if (first < get_fade_level()) {
        obj->script.pc = ((s16 **)obj->script.data)[second];
    }
}

/* Reads a halfword index from the script stream (obj->unk_1C.unk_04 is its position) and counts up
 * that entry of the object's halfword vars. */
void script_counter_inc(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 index;

    obj->script.pc = pc + 1;
    index = *pc;
    (&obj->vars.giant_robot.script_vars)[index]++;
}

/* Script op: reads a counter index, a value and a jump index; when counter[index] equals the value, the
 * stream jumps to the table entry at jump index (the table is at unk_1C.data). */
void script_jump_if_counter_eq(Object *obj) {
    s16 index;
    s16 value;
    s16 target;

    index = obj_read_s16(obj);
    value = obj_read_s16(obj);
    target = obj_read_s16(obj);
    if (value == (s16) (&obj->vars.giant_robot.script_vars)[index]) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

/* Script op: reads three s16 operands. The first selects an s16 entry in
 * the object's table at 0x252; if that entry is >= the second operand,
 * the object jumps to the third operand's entry in its data table. */
void script_jump_if_counter_ge(Object *obj) {
    s32 table_index = obj_read_s16(obj);
    s32 limit = obj_read_s16(obj);
    s32 jump_index = obj_read_s16(obj);

    if (((s16 *)&obj->vars.giant_robot.script_vars)[table_index] >= limit) {
        obj->script.pc = ((s16 **)obj->script.data)[jump_index];
    }
}

/* Reads a 16-bit value from the script cursor, stores it in unk_17A and sets or clears flags bit 2. */
void script_set_flag(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 flags = obj->flags;
    s32 value;
    s32 unused[2]; /* the original's frame is 8 bytes larger than its locals need */

    obj->script.pc = cursor + 1;
    value = *cursor;
    obj->unk_17A = value;
    if (value != 0) {
        flags |= 4;
    } else {
        flags &= ~4;
    }
    obj->flags = flags;
}

extern s32 giant_robot_damage_scale;

void giant_robot_set_damage_scale(s32 arg0) {
    giant_robot_damage_scale = arg0;
}

void giant_robot_reset_scale(void) {
    meter_set_mode(1);
    giant_robot_set_damage_scale(0x1000);
    warning_ack_set(0);
}

/* Reads a 16-bit index from the object's script stream; while the player is below -0x352 (y), the
 * stream jumps to the table entry it names. */
void script_jump_if_player_low(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 index;
    s32 *player;

    obj->script.pc = pc + 1;
    index = *pc;
    player = player_position();
    if (player[1] < -0x352) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Reads a threshold and a target index from the object's script stream; when a random value is at
 * or below the threshold, the stream jumps to the table entry the target names. */
void script_jump_if_rand_le(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 threshold;
    s32 target;

    obj->script.pc = pc + 1;
    threshold = pc[0];
    obj->script.pc = pc + 2;
    target = pc[1];
    if (rand_a_next() <= threshold) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

void giant_robot_phase0(void) {
    obj_link_script_run();
    giant_robot_fx_tick();
}

void giant_robot_update(Object *obj, ObjHandler *handler) {
    s32 dx;
    s32 dz;
    s32 old_yaw;
    s32 angle;
    s16 yaw;
    s32 turn;
    s32 x;
    s32 z;

    dx = 0;
    dz = 0;
    x = obj->x;
    z = obj->z;
    if (obj->unk_242 == 0) {
        obj_turn_toward_player(obj, obj->vars.giant_robot.turn_speed);
    } else {
        old_yaw = obj->yaw;
        angle = atan2(-(z >> 12), -(x >> 12));
        obj->target_yaw = angle;
        yaw = angle_approach(obj->yaw, obj_angle_wobble(obj, (s16)angle), obj->vars.giant_robot.turn_speed);
        turn = yaw;
        turn -= old_yaw;
        obj->yaw = yaw;
        obj->turn = turn;
        obj->unk_242 = -1;
    }
    obj->yaw += obj->unk_226[0];
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj->vz = dx;
    obj->vx = dz;
    obj_script_step(obj, handler);
    giant_robot_systems_update();
}

/* Copies the object's yaw/pitch/roll into its unk_A4 block (the pitch is
 * negated and the roll and yaw swapped into the block's slots), sets the
 * block's index bytes, then runs the two follow-up helpers on it. */
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
