/* proximity_sensor: one of s12's own original source files (scripts/objmap.py); part of src/s12/main.c's unit, included there. */

extern struct ProximityFlag proximity_flags[3];
extern s32 prox_blend_base;
void proximity_flags_reset(void) {
    s32 i;
    struct ProximityFlag *rec;

    rec = proximity_flags;
    i = 0;
    prox_blend_base = point_base;
    do {
        i++;
        rec->armed = 1;
        rec->active = 0;
        rec->unk_02 = 0;
        rec->level = 0x1000;
        rec->step = 0x80;
        rec++;
    } while (i < 3);
}

void proximity_sensor_phase0(Object *obj, ObjHandler *handler);
void proximity_sensor_update(Object *obj, ObjHandler *handler);
void proximity_sensor_phase2(Object *obj, ObjHandler *handler);
/* Same code as fn_s11_800BF5C0 (s11). */
void fn_s11_800BF5C0(Object *obj);
extern s32 prox_origin[2];
extern u8 proximity_sensor_offsets[];
s32 proximity_sensor_spawn(Placement *p) {
    Object *obj;
    s32 kind;
    s32 i;
    s32 off;
    s32 z;

    if (get_obj_free_count() < 2) {
        return 0;
    }
    kind = *(s16 *)&p->health;
    if ((u32)kind >= 3) {
        return 0;
    }
    i = 0;
    off = kind * 0x28;
    for (; i < 2;) {
        obj = obj_new();
        list_insert_after((Node *)get_obj_list_b(), &obj->node);
        obj->handlers[0].fn = proximity_sensor_phase0;
        obj->handlers[1].fn = proximity_sensor_update;
        obj->handlers[2].fn = proximity_sensor_phase2;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = fn_s11_800BF5C0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->x = (p->x >> 12) << 12;
        obj->y = (p->y >> 12) << 12;
        z = (p->z >> 12) << 12;
        obj->vars.proximity_sensor.lane = i;
        i++;
        obj->placement = p;
        obj->vars.proximity_sensor.zone = kind;
        obj->z = z;
        obj_clear_block54(obj->unk_A4);
        model_part_extents_max(prox_origin[0] + *(s16 *)(proximity_sensor_offsets + off), 0x1000, &obj->unk_A4[0x34]);
        off += 0x14;
        obj->solid_id = solid_alloc();
        obj->unk_A4[1] = 4;
        obj->vars.proximity_sensor.sound_id = 0;
        obj->unk_A4[0] = obj->index;
    }
    return 1;
}

extern u8 proximity_sensor_range_x[];
extern u8 proximity_sensor_range_z[];
void proximity_sensor_phase0(Object *obj, ObjHandler *handler) {
    struct ProximityFlag *flag;
    s32 *pp;
    s32 dx, dz;
    s32 prev, rx, rz;
    s32 off;

    if (obj->vars.proximity_sensor.lane == 1) {
        flag = &proximity_flags[obj->vars.proximity_sensor.zone];
        pp = player_position();
        dx = pp[0] - (obj->x >> 12);
        dz = pp[2] - (obj->z >> 12);
        off = obj->vars.proximity_sensor.lane * 0x14 + obj->vars.proximity_sensor.zone * 0x28;
        rz = *(s16 *)(proximity_sensor_range_z + off);
        rx = *(s16 *)(proximity_sensor_range_x + off);
        prev = flag->active;
        if (ABS(dz) < rz
            && ABS(dx) < rx
            && flag->armed) {
            flag->active = 1;
        } else if (flag->active) {
            if (obj->vars.proximity_sensor.zone != 1) {
                flag->active = 0;
            }
            if (obj->vars.proximity_sensor.zone == 2 && dz < 0) {
                flag->armed = 0;
            }
        }
        if (prev != flag->active && (u16)obj->vars.proximity_sensor.sound_id == 0) {
            obj->vars.proximity_sensor.sound_id = sound_start(SND_PROXIMITY_ALERT_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
            sound_attach(obj->vars.proximity_sensor.sound_id & 0xFFFF, &obj->x, NULL);
        }
    }
}

void proximity_sensor_update(Object *obj, ObjHandler *handler) {
    struct ProximityFlag *flag;
    s32 step;
    s16 level;

    if (obj->vars.proximity_sensor.lane == 1) {
        flag = &proximity_flags[obj->vars.proximity_sensor.zone];
        step = flag->step;
        if (flag->armed && flag->active) {
            step = -step;
        }
        level = flag->level += step;
        level = MAX(MIN(level, 0x1000), 0);
        flag->level = level;
        if (level == 0 || level == 0x1000) {
            if ((u16)obj->vars.proximity_sensor.sound_id != 0) {
                sound_stop((u16)obj->vars.proximity_sensor.sound_id);
                obj->vars.proximity_sensor.sound_id = 0;
            }
        }
    }
}

extern u8 prox_cells[];
void proximity_sensor_phase2(Object *obj, ObjHandler *handler) {
    struct ProximityFlag *flag;
    ProxCell *cell;
    ProxBlock *block;
    Placement *placement;
    s16 zone;
    s16 lane;
    s16 span;
    s16 solid_index;
    s16 corner[2];
    s16 extent[2];
    s32 frame_pad[2]; /* unused; the original's frame is 0x48 bytes */

    block = (ProxBlock *)obj->unk_A4;
    zone = obj->vars.proximity_sensor.zone;
    lane = obj->vars.proximity_sensor.lane;
    flag = &proximity_flags[zone];
    cell = (ProxCell *)(prox_cells + zone * 0x28 + lane * 0x14);

    if (lane == 1) {
        flag->unk_02 = cam_range_check_alt(obj->x >> 12, obj->y >> 12, obj->z >> 12);
        if (cell->flag_offset >= 0) {
            aobj_set_flag(get_rec_id(0) + cell->flag_offset, flag->level == 0x1000);
        }
    }
    if (flag->unk_02 == 0) {
        if (obj->vars.proximity_sensor.lane == 1) {
            placement = obj->placement;
            placement->unk_02 = 0;
            placement->unk_04[0] = (placement->unk_04[0] & 0xFC) | 2;
        }
        solid_free(obj->solid_id);
        obj_free(obj);
        return;
    }
    span = flag->level;
    if (span > 0) {
        extent[0] = span;
        extent[1] = 0x1000 - span;
        corner[0] = cell->unk_04 + prox_origin[0];
        corner[1] = cell->unk_06 + prox_origin[0];
        /* the caller passes two arguments; solid_add's definition has four (see eng_rotate_vector.c) */
        solid_index = ((s32 (*)())solid_add)(corner, extent);
        block->x = obj->x + (cell->x_offset << 12);
        block->y = obj->y - 0x1000;
        block->z = obj->z + (cell->z_offset << 12);
        solid_setup_scratch(obj->solid_id, block, solid_index, 0x1000);
    }
}

extern u8 spark_weights[];
/* Same code as fn_s11_800BF5C0 (s11). */
void fn_s11_800BF5C0(Object *obj) {
    s32 idx = *(s16 *)&obj->vars;
    s32 sub = ((s16 *)&obj->vars)[1];
    s32 idx8 = idx << 3;
    SparkOffset *off = (SparkOffset *)((u8 *)(prox_cells + ((idx * 5) << 3)) + sub * 0x14);
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    s32 weight = *(s16 *)(spark_weights + idx8);
    s32 value = pchr_blend(prox_blend_base + off->ay, prox_blend_base + off->ax, weight, 1);

    spark_add(x + off->dx, y, z + off->dz, 0, 0, 0, value, 0);
}

extern s32 loop_sound_id;

void loop_sound_clear(void) {
    loop_sound_id = 0;
}

extern s32 loop_sound_id;

void loop_sound_start(void) {
    s32 temp_v0;

    if (loop_sound_id == 0) {
        temp_v0 = sound_start(SND_PAIR(SND_HOLLOW_WIND_LOOP | SND_HELD | SND_GROUP(2), SND_HOLLOW_WIND_LOOP_ALT | SND_HELD | SND_GROUP(2)), 0x7F, 0, 0);
        loop_sound_id = temp_v0;
        sound_set_flag_bit3(temp_v0, 1);
    }
}

extern s32 loop_sound_id;

void loop_sound_stop(void) {
    if (loop_sound_id != 0) {
        sound_stop(loop_sound_id);
        loop_sound_id = 0;
    }
}

extern s32 rec_clear_ids[7];
void rec_clear_flags_list(void) {
    s32 *entry;
    s32 value;

    entry = rec_clear_ids;
    value = *entry;
    if (value >= 0) {
        do {
            rec_set_flags(value, 0);
            entry += 1;
            value = *entry;
        } while (value >= 0);
    }
    stage_set_offset_x(0x7FFF);
}

/* Passes the button mask of key action 4 from the active key configuration to player_set_input as the held buttons, with no pressed buttons. */
void pad_hold_action4(void) {
    player_set_input(get_key_config()->action[4], 0);
}

extern s32 anim_obj_data[5];
extern PathPoint cam_path_data[11];
extern s32 cam_trigger_inside;
void cam_box_trigger_update(void);
void cam_path_obj_draw(void);
/* Spawns the object, links it into the object list and sets up its handlers. Returns 1 on success. */
s32 cam_path_obj_spawn(void) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_b(), &obj->node);
    obj->handlers[2].fn = cam_box_trigger_update;
    obj->handlers[3].fn = cam_path_obj_draw;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->vars.cam_path_obj.unused_248 = 0;
    obj->vars.snd.sound = 0;
    cam_trigger_inside = 0;
    anim_obj_spawn((s32) anim_obj_data, 0, 0, 0x28, (s32) pad_hold_action4);
    cam_path_set(0xB, (s32) cam_path_data);
    target_select(5);
    loop_sound_clear();
    return 1;
}

extern BoundsBox cam_boxes[2];
static inline s16 in_box(BoundsBox *box, s32 x, s32 y, s32 z) {
    if (x < box->min_x) return 0;
    if (x > box->max_x) return 0;
    if (y < box->min_y) return 0;
    if (y > box->max_y) return 0;
    if (z < box->min_z) return 0;
    if (z > box->max_z) return 0;
    return 1;
}
s32 cam_in_boxes(void) {
    s32 x = cam_pos >> 12;
    s32 y = cam_pos_y >> 12;
    s32 z = cam_pos_z >> 12;
    s32 i;
    BoundsBox *box;

    if (y >= -0x300) {
        return 1;
    }
    box = cam_boxes;
    for (i = 0; i < 2; i++, box++) {
        if (in_box(box, x, y, z) != 0) {
            return 1;
        }
    }
    return 0;
}

extern s32 cam_trigger_min_x;
extern s32 cam_trigger_max_x;
extern s32 cam_trigger_min_y;
extern s32 cam_trigger_max_y;
extern s32 cam_trigger_min_z;
extern s32 cam_trigger_max_z;
void cam_box_trigger_update(void) {
    s32 x;
    s32 y;
    s32 z;
    s32 inside;

    loop_sound_start();
    if (!(get_player_status() & 0x40) && cam_in_boxes() != 0) {
        set_player_status(get_player_status() | 0x40);
    }
    if (cam_trigger_inside == 0) {
        x = cam_pos >> 12;
        y = cam_pos_y >> 12;
        z = cam_pos_z >> 12;
        if (x < cam_trigger_min_x || x > cam_trigger_max_x || y < cam_trigger_min_y || y > cam_trigger_max_y ||
            z < cam_trigger_min_z || z > cam_trigger_max_z) {
            inside = 0;
        } else {
            inside = 1;
        }
        cam_trigger_inside = inside;
        if (inside != 0) {
            set_stage_end(2);
        }
    }
}

void cam_path_obj_draw(void) {
    cam_path_update();
    req_queue_push(-0x7727, -0xC00, -0x4066, 4);
}

extern s32 trail_write_index;
s32 ring_index_delta(s32 arg0) {
    s32 v = trail_write_index - arg0;
    while (v < 0) {
        v += 0x20;
    }
    return v;
}

/* Advances the s32 at 0x20 (unk_1C.unk_04) by 2. */
void script_skip_halfword(Object *obj) {
    obj->script.pc++;
}

s32 player_horiz_dist(s32 *pos);
void script_branch_if_near(Object *obj) {
    s32 pos[3];
    s16 *cursor;
    s32 threshold;
    s32 index;
    s16 dist;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    dist = player_horiz_dist(pos);
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

s32 player_horiz_dist(s32 *pos);
/* Script-stream branch: read a (limit, index) pair from the object's cursor;
 * if the value from player_horiz_dist is >= limit, jump the cursor to table[index]. */
void script_branch_if_at_least(Object *self) {
    s32 pos[3];
    s16 *cursor;
    s32 limit;
    s32 index;
    s16 key;

    pos[0] = self->x >> 12;
    pos[1] = self->y >> 12;
    pos[2] = self->z >> 12;
    key = (s16) player_horiz_dist(pos);
    cursor = self->script.pc;
    self->script.pc = cursor + 1;
    limit = cursor[0];
    self->script.pc = cursor + 2;
    index = cursor[1];
    if (key >= limit) {
        self->script.pc = ((s16 **)self->script.data)[index];
    }
}

s32 is_facing_target(s32 *pos, s32 angle, s32 max_step);
/* Reads a 2-word script record from obj's cursor (unk_1C.unk_04): max_step, then
 * a table index. Advances the cursor past it; when the object's position is
 * within max_step of turning toward yaw, jumps to the table entry. */
void script_branch_if_aligned(Object *obj) {
    s32 pos[3];
    s16 *cursor;
    s32 max_step;
    s32 table_index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    max_step = cursor[0];
    obj->script.pc = cursor + 2;
    table_index = cursor[1];
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    if (is_facing_target(pos, obj->yaw, max_step) != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[table_index];
    }
}

/* Script step: reads two halfwords from the object's script stream (max_step, index).
 * If the object has not yet turned to face its position target within max_step,
 * the stream jumps to the per-type table entry at index. */
void script_branch_if_not_aligned(Object *obj) {
    s16 *stream;
    s32 vec[3];
    s32 max_step;
    s32 index;

    stream = obj->script.pc;
    obj->script.pc = stream + 1;
    max_step = stream[0];
    obj->script.pc = stream + 2;
    index = stream[1];

    vec[0] = obj->x >> 12;
    vec[1] = obj->y >> 12;
    vec[2] = obj->z >> 12;
    if (!is_facing_target(vec, obj->yaw, max_step)) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}



void script_jump_if_op_eq(Object *obj) {
    s16 op = obj_read_s16(obj);
    s16 target = obj_read_s16(obj);

    if (op == obj->script_flag) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}



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
