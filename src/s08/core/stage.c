/* stage: one of s08's own original source files (scripts/objmap.py); part of src/s08/main.c's unit, included there. */

extern s32 night_vision_target;

void set_night_vision_target(s32 arg0) {
    night_vision_target = arg0;
}

extern s32 night_vision_target;

s32 get_night_vision_target(void) {
    return night_vision_target;
}

extern s32 night_vision_level;

s32 get_night_vision_level(void) {
    return night_vision_level;
}

extern s32 rolling_door_sound_handle;

void rolling_door_sound_start(Object *obj) {
    s32 temp_v0;

    if (rolling_door_sound_handle == 0) {
        temp_v0 = sound_start(SND_PAIR(SND_ROLLING_DOOR_LOOP | SND_HELD | SND_GROUP(1), SND_ROLLING_DOOR_LOOP_ALT | SND_HELD | SND_GROUP(1)), 0x40, 0, 0);
        rolling_door_sound_handle = temp_v0;
        sound_attach(temp_v0, &obj->x, NULL);
    }
}

extern s32 rolling_door_sound_handle;

void rolling_door_sound_stop(void) {
    if (rolling_door_sound_handle != 0) {
        sound_stop(rolling_door_sound_handle);
        sound_play_at(SND_PAIR(SND_ROLLING_DOOR_STOP | SND_HELD | SND_GROUP(1), SND_ROLLING_DOOR_STOP_ALT | SND_HELD | SND_GROUP(1)), 0x40, 0, 0);
        rolling_door_sound_handle = 0;
    }
}

extern RollingDoorState rolling_door_states[];
extern s32 rolling_door_base;
void rolling_door_init(void) {
    RollingDoorState *r = rolling_door_states;
    s32 i;

    rolling_door_base = point_base;
    for (i = 0; i < 4; i++, r++) {
        r->active = 1;
        r->unk4 = 0;
        r->scale = 0x1000;
        if (i < 2) {
            r->value = 0xAA;
        } else {
            r->value = 0x66;
        }
    }
    rolling_door_sound_handle = 0;
}

void rolling_door_phase0(Object *obj, ObjHandler *handler);
void rolling_door_update(Object *obj, ObjHandler *handler);
void rolling_door_phase2(Object *obj, ObjHandler *handler);
void rolling_door_draw(Object *obj, ObjHandler *handler);
extern s32 D_801180BC[];
s32 rolling_door_spawn(Placement *placement) {
    Object *obj;
    s32 health;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    /* the placement's health word (read as signed) is the variant: 0..3 spawn */
    health = *(s16 *)&placement->health;
    if ((u32)health >= 4) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_b(), &obj->node);
    obj->handlers[0].fn = rolling_door_phase0;
    obj->handlers[1].fn = rolling_door_update;
    obj->handlers[2].fn = rolling_door_phase2;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = rolling_door_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = ((s32)placement->x >> 12) << 12;
    obj->y = ((s32)placement->y >> 12) << 12;
    obj->z = ((s32)placement->z >> 12) << 12;
    obj->placement = placement;
    health = *(s16 *)&placement->health;
    obj->vars.rolling_door.health = health;
    if (health < 2) {
        obj_clear_block54(obj->unk_A4);
        model_part_extents_max(D_801180BC[0], 0x1000, &obj->unk_A4[0x34]);
        obj->solid_id = solid_alloc();
        obj->unk_A4[1] = 4;
        obj->unk_A4[0] = obj->index;
    }
    return 1;
}

void rolling_door_phase0(Object *obj, ObjHandler *handler) {
    RollingDoorState *r;
    s32 *pos;
    s32 dx;
    s32 dz;
    s32 behind;
    s32 ahead;
    s32 radius;

    r = &rolling_door_states[obj->vars.enemy.mode];
    pos = player_position();
    dx = pos[0] - (obj->x >> 12);
    dz = pos[2] - (obj->z >> 12);

    if (obj->vars.enemy.mode == 0) {
        ahead = 0x578;
        behind = 0x320;
        radius = 0x320;
    } else {
        behind = 0x578;
        if (obj->vars.enemy.mode == 1) {
            behind = 0x320;
            ahead = 0x320;
            radius = 0x320;
        } else {
            ahead = 0x578;
            radius = 0x578;
        }
    }


    if (ABS(dz) < radius && -behind < dx && dx < ahead && r->active != 0) {
        if (r->unk4 == 0) {
            r->unk4 = 1;
            if (obj->vars.enemy.mode < 2 && dx < 0) {
                set_night_vision_target(0);
            }
        }
    } else if (r->unk4 != 0) {
        r->unk4 = 0;
        if (obj->vars.enemy.mode < 2 && dx < 0) {
            set_night_vision_target(1);
        }
    }
}

void rolling_door_update(Object *obj, ObjHandler *handler) {
    RollingDoorState *r = &rolling_door_states[obj->vars.rolling_door.health];
    s32 step = r->value;
    s32 scale = r->scale;
    s16 pos;
    s16 clamped;

    if (r->active != 0 && r->unk4 != 0) {
        step = -step;
    }
    if (scale != 0 && scale != 0x1000) {
        rolling_door_sound_start(obj);
    }
    pos = r->scale + step;
    r->scale = pos;
    clamped = MAX(MIN(pos, 0x1000), 0);
    r->scale = clamped;
    if (scale > 0 && clamped == 0) {
        rolling_door_sound_stop();
    }
    if (scale < 0x1000 && r->scale == 0x1000) {
        rolling_door_sound_stop();
    }
}

void rolling_door_phase2(Object *obj, ObjHandler *handler) {
    Placement *placement;
    s32 frame_pad[5]; /* not used; the original's frame is 0x30 bytes */

    if (cam_range_check_alt(obj->x >> 12, obj->y >> 12, obj->z >> 12) == 0) {
        placement = obj->placement;
        ((s16 *)placement->unk_00)[1] = 0;
        placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
        if (obj->vars.enemy.mode < 2) {
            solid_free(obj->solid_id);
        }
        obj_free(obj);
    }
}

extern s16 rolling_door_weights[];
static inline void spark_add_head_n(s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    s32 n = SPARK_COUNT;
    SparkList *list;
    SparkRec *s;
    u8 *tail;

    list = &spark_list;
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
void rolling_door_draw(Object *obj, ObjHandler *handler) {
    s32 cx = obj->x >> 12;
    s32 cy = obj->y >> 12;
    s32 cz = obj->z >> 12;
    s32 mode = obj->vars.enemy.mode;
    s32 weight = rolling_door_weights[mode * 6];
    s32 value;

    if (mode < 2) {
        value = pchr_blend(rolling_door_base + 0x3A, rolling_door_base + 0x3C, weight, 1);
        spark_add_head_n(cx, cy, cz + 0xA8, 0, 0, 0, value, 0);
        spark_add_head_n(cx, cy, cz - 0xA8, 0, 0, 0, value, 0);
    } else {
        value = pchr_blend(rolling_door_base + 0x78, rolling_door_base + 0x4E, weight, 1);
        spark_add_head_n(cx + 0x150, cy, cz, 0, 0, 0, value, 0);
        value = pchr_blend(rolling_door_base + 0x79, rolling_door_base + 0x4F, weight, 1);
        spark_add_head_n(cx - 0x150, cy, cz, 0, 0, 0, value, 0);
    }
}

void rolling_door_set_active(u32 index, s32 value) {
    if (index < 4U) {
        rolling_door_states[index].active = value;
    }
}

extern s16 rolling_door_weights[];
/* Returns the s16 of table entry `index` for index 0-3, else 0x1000. */
s32 rolling_door_get_scale(u32 index) {
    if (index >= 4U) {
        return 0x1000;
    }
    return *(s16 *)((u8 *)rolling_door_weights + index * 12);
}

s32 grid_collect_in_box(GridBox *box, GridEntry **out, s32 max);
s32 grid_collect_in_box(GridBox *box, GridEntry **out, s32 max) {
    GridEntry *entry;
    s32 remaining;
    s32 count;

    entry = grid_entry(0);
    remaining = grid_count();
    count = 0;
    while (remaining > 0) {
        if (count > max) {
            return count;
        }
        if (entry->kind < 0x40 && in_box_800C0D44(box, entry->x >> 12, entry->y >> 12, entry->z >> 12)) {
            out[count] = entry;
            count++;
            entry->flags |= 8;
            entry->unk_14[0x10] |= 8;
        }
        remaining--;
        entry++;
    }
    return count;
}

void obj_mark_linked(Object *obj) {
    Object *cur;

    cur = (Object *)*get_obj_list_actors();
    if (cur->node.next != 0) {
        do {
            if (cur->placement == (void *)obj) {
                cur->flags |= 0x200;
            }
            cur = (Object *)cur->node.next;
        } while (cur->node.next != 0);
    }
}

extern void *grid_entry_count;
extern s32 grid_states[];
void grid_init_states(void) {
    s32 i;
    s32 unused; /* pads the frame to 0x8 bytes, as in the original */

    for (i = 0; i < (s32)grid_entry_count; i++) {
        grid_states[i] = 1;
    }
}

extern void *grid_entry_count;
extern s32 grid_entry_list;
extern s32 grid_states[];
void obj_mark_linked(Object *obj);

/* Steps each grid entry's state in grid_states: 1 waits for the entry to come back to state 0, 0 takes
 * the entry's state (state 2 with a delay left removes the entry and records 3). */
void grid_states_step(void) {
    GridEntry *entry;
    s32 *slot;
    s32 delay;
    s32 state;
    s32 i;

    for (i = 0; i < (s32)grid_entry_count; i++) {
        entry = ((GridEntry **)&grid_entry_list)[i];
        delay = entry->delay;
        state = entry->flags & 3;
        if (state == 0) {
            obj_mark_linked((Object *)entry);
        }
        slot = &grid_states[i];
        if (*slot != 0) {
            if (*slot == 1 && state == 0) {
                *slot = 0;
                entry->unk_14[0x10] |= 3;
                if (delay >= 0) {
                    entry->delay = -1;
                }
            }
        } else {
            switch (state) {
            case 3:
                *slot = state;
                break;
            case 2:
                if (delay != 0) {
                    /* two statements: the extra store keeps loop.c from hoisting the table address */
                    entry->flags |= 3;
                    entry->flags &= 0xF7;
                    entry->unk_14[0x10] &= 0xF7;
                    *slot = 3;
                } else {
                    *slot = 1;
                }
                break;
            case 1:
                *slot = state;
                break;
            }
        }
    }
}

extern void *grid_entry_count;
extern s32 grid_states[];
s32 grid_count_active(void) {
    s32 i;
    s32 count = 0;
    s32 unused;

    for (i = 0; i < (s32)grid_entry_count; i++) {
        if (grid_states[i] != 3) {
            count++;
        }
    }
    return count;
}

extern void *grid_entry_count;
extern s32 grid_entry_list;
void grid_clear_state(void) {
    s32 i;
    u8 **table = (u8 **)&grid_entry_list;

    for (i = 0; i < (s32)grid_entry_count; i++) {
        table[i][4] &= 0xFC;
    }
}

void grid_set_state(void) {
    s32 i;
    u8 **table = (u8 **)&grid_entry_list;

    for (i = 0; i < (s32)grid_entry_count; i++) {
        table[i][4] = (table[i][4] & 0xFC) | 9;
    }
}

extern GridBox grid_box;
extern s32 grid_entry_list;
extern void *grid_entry_count;
void grid_init_states(void);
/* Sets up the table at grid_entry_list (32 bytes) through grid_collect_in_box, keeps the result in grid_entry_count, then runs grid_init_states. */
void grid_setup(void) {
    grid_entry_count = (void *)grid_collect_in_box(&grid_box, (GridEntry **)&grid_entry_list, 0x20);
    grid_init_states();
}

void mission_night_vision_update(Object *obj, ObjHandler *handler);
void cam_path_advance(void);
extern s32 cam_path_index;
extern s32 mission_area_entered;
extern s32 D_80118160[];
extern PathPoint D_801181A8[5];
s32 grid_controller_spawn(void) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_b(), (Node *)obj);
    obj->handlers[2].fn = mission_night_vision_update;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = cam_path_advance;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->vars.grid_controller.unused_248 = 0;
    obj->vars.grid_controller.unused_24C = 0;
    cam_path_index = 0;
    mission_area_entered = 0;
    grid_clear_state();
    anim_obj_spawn((s32)D_80118160, 0, 0x32, 0x51, 0);
    cam_path_set(5, (s32)D_801181A8);
    return 1;
}

RectU night_vision_rect RODATA = {0x300, 0x0, 0x100, 0xD8}; /* the night vision copy rect */
__asm__(".globl night_vision_rect_y\n.set night_vision_rect_y, night_vision_rect+0x2\n");
char str_dor8_ch0cb4[16] RODATA = "dor8_ch0.cb4";

extern s16 mission_door_ids[];
extern const char next_area_text[];
extern PathPoint mission_cam_path_clear[];
extern s32 area_box_x_min, area_box_x_max, area_box_y_min, area_box_y_max, area_box_z_min, area_box_z_max;
static inline s32 in_area(s32 x, s32 y, s32 z) {
    if (x < area_box_x_min || area_box_x_max < x) {
        return 0;
    }
    if (y < area_box_y_min || area_box_y_max < y) {
        return 0;
    }
    if (z < area_box_z_min || area_box_z_max < z) {
        return 0;
    }
    return 1;
}
/* Mission handler: waits for the night-vision target, runs the door/grid sequence, shows the
 * "destroy all the targets" messages, and ends the stage once the camera leaves the area box. */
void mission_night_vision_update(Object *obj, ObjHandler *handler) {
    register s32 i asm("$16");
    register s16 *door asm("$17");
    CoItem *co;
    s32 rec;
    s32 left;
    s32 x;
    s32 y;
    s32 z;
    s32 unused[2];

    rec = get_rec_id(0);
    for (i = 0, door = mission_door_ids; i < 2; i++, door++) {
        if (rolling_door_get_scale(i) == 0) {
            aobj_set_flag(rec + *door, 0);
        } else {
            aobj_set_flag(rec + *door, 1);
        }
    }
    grid_states_step();
    co = (CoItem *)&obj->vars;
    __asm__("" : "=r"(co) : "0"(co));
    if (co->resume[((CoItem *)&obj->vars)->level] != NULL) {
        goto *co->resume[((CoItem *)&obj->vars)->level];
    }
    target_select(5);
    co->resume[((CoItem *)&obj->vars)->level] = &&wait_target;
wait_target:
    if (get_night_vision_target() == 0) {
        goto done;
    }
    target_select(0);
    co->resume[co->level] = &&wait_scale;
wait_scale:
    if (get_night_vision_target() == 0) {
        goto done;
    }
    if (rolling_door_get_scale(0) < 0x1000) {
        goto done;
    }
    cam_path_index = -1;
    grid_set_state();
    rolling_door_set_active(0, 0);
    rolling_door_set_active(1, 0);
    eng_set_mode(4);
    pursue_flag_set(1);
    co->resume[co->level] = &&start_count;
start_count:
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&count_down;
    co->count[co->level] = 0x1F;
count_down:
    set_enemies_left(grid_count_active());
    if (--co->count[co->level] >= 0) {
        goto done;
    }
    co->level = (co->level - 1) & 7;
    show_line((s32)"#1Destroy all the targets.\xA1");
    co->resume[co->level] = &&wait_clear;
wait_clear:
    left = grid_count_active();
    set_enemies_left(left);
    if (left > 0) {
        goto done;
    }
    pursue_flag_set(0);
    rolling_door_set_active(1, 1);
    msg_show_slot(4, 0xB4);
    show_line((s32)"#1All targets destroyed!\xA1|2");
    show_line((s32)next_area_text);
    cam_path_index = 1;
    cam_path_set(3, (s32)mission_cam_path_clear);
    target_select(5);
    co->resume[co->level] = &&wait_leave;
wait_leave:
    if (get_night_vision_target() != 0) {
        goto done;
    }
    if (rolling_door_get_scale(1) < 0x1000) {
        goto done;
    }
    warning_ack_set(0);
    rolling_door_set_active(1, 0);
    cam_path_index = 2;
    co->resume[co->level] = &&done;
done:
    if (mission_area_entered == 0) {
        x = VEC_80139584.x >> 12;
        y = VEC_80139584.y >> 12;
        z = VEC_80139584.z >> 12;
        mission_area_entered = in_area(x, y, z);
        if (mission_area_entered != 0) {
            set_stage_end(2);
        }
    }
}

const char next_area_text[] = "Proceed to the nextarea.\xA1";

/* The boss's model files: data tables point to them by address. */
const char file_bos8_tp1_clt[] = "bos8_tp1.clt";
const char file_bos8_tp0_clt[] = "bos8_tp0.clt";
const char file_bos8_ch1_clt[] = "bos8_ch1.clt";
const char file_bos8_ch0_clt[] = "bos8_ch0.clt";
const char file_bos8_tp1_xs3[] = "bos8_tp1.xs3";
const char file_bos8_tp0_xs3[] = "bos8_tp0.xs3";
const char file_bos8_ch1_vx1[] = "bos8_ch1.vx1";
const char file_bos8_ch0_vx1[] = "bos8_ch0.vx1";
const char file_bos8_ch1_cb4[] = "bos8_ch1.cb4";
const char file_bos8_ch0_cb4[] = "bos8_ch0.cb4";

extern s32 cam_path_index;
extern s32 cam_path_table[];
void cam_path_advance(void) {
    s32 *entry;

    if (cam_path_index >= 0) {
        entry = &cam_path_table[cam_path_index * 4];
        req_queue_push(entry[0], entry[1], entry[2], 4);
        cam_path_update();
    }
}

void func_800BEC40(void) {
}


/* Sets up the object's position (x, y, z) from i. Returns 0. */
s32 sound_follow_obj(Object *obj, s32 i) {
    sound_set_pos(i, (Vec3 *)&obj->x);
    return 0;
}


extern s32 boss_defeated_flag;

s32 world_flag_get(void) {
    return boss_defeated_flag;
}

extern s32 world_matrix;
/* Same code as get_key_table (s01). */
s32 *world_matrix_get(void) {
    return &world_matrix;
}

/* 32 bytes copied as one struct (3+3+2 word groups, as the struct copy compiles). */
struct Block32 {
    s32 a[3];
    s32 b[3];
    s32 c[2];
};

void world_matrix_set(s32 *src) {
    *(struct Block32 *)&world_matrix = *(struct Block32 *)src;
}

extern s32 moving_object_slot;

s32 get_world_offset(void) {
    return moving_object_slot;
}

void obj_velocity_world(Object *obj, s32 *out) {
    volatile s32 *m = world_matrix_get();

    s32 a = m[0];
    s32 b = m[1];
    s32 c = m[2];
    gte_set_ctrl(R11R12, a);
    gte_set_ctrl(R13R21, b);
    gte_set_ctrl(R22R23, c);
    a = m[3];
    b = m[4];
    gte_set_ctrl(R31R32, a);
    gte_set_ctrl(R33, b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    out[0] = obj->vars.enemy.sound >> 12;
    out[1] = obj->vy >> 12;
    out[2] = obj->speed >> 12;
    gte_load(IR1, out, 0);
    gte_load(IR2, out, 4);
    gte_load(IR3, out, 8);
    gte_rtirtr_sf0();
    gte_store(MAC1, out, 0);
    gte_store(MAC2, out, 4);
    gte_store(MAC3, out, 8);
}

/* Collision check for a move from pos to next (flags as the trace mode). Returns 3 when the world trace
 * hits with the expected result, 2 when the object's index is flagged, 1 when the player is at least
 * 0x1F41 away, 4 when a trace against the objects hits, else 0. */
s32 obj_check_move(Object *obj, s32 *pos, s32 *next, s32 *hit, s32 flags, s32 expect) {
    s16 hitObj;
    s32 *player;
    s32 result = 0;

    if (expect == 1 && trace_world(8, flags, pos, next, hit) == expect) {
        result = 3;
    } else if (obj_hit_damage(obj->index) > 0) {
        result = 2;
    } else {
        player = player_position();
        if (isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12),
                            player[2] - (obj->z >> 12))) >= 0x1F41) {
            result = 1;
        } else {
            set_collide_mode(1);
            if (trace_objects(pos, next, flags, hit, &hitObj) != 0) {
                result = 4;
            }
            set_collide_mode(0);
        }
    }
    return result;
}

void obj_rot_matrix(Object *obj, s32 *m) {
    s32 *tmp = scratch_alloc(0x20);

    rot_matrix(m, *(s16 *)&obj->vars.quick_fuchikoma_m8_boss.unk_24E, 0, 0);
    rot_matrix(tmp, -obj->rot_angles[1], -obj->rot_angles[0], -obj->rot_angles[2]);
    mul_matrix(tmp, m, m);
    scratch_top -= 0x20;
}

extern ObjAngleTableSlot obj_angle_tables[];
/* Transforms out by the rotation and translation of the object's record idx, then by the world matrix. */
void obj_bone_pos(Object *obj, s32 idx, Vec3 *out) {
    s32 base = obj->type.unk_0E;
    ObjAngleTable *table = obj_angle_tables[(base + get_world_offset()) & 0x7FF].table;
    ObjAngleRec *r;
    volatile s32 *m;
    volatile s32 *world;
    s32 r0, r1, world_r2, tz;
    register s32 r2 asm("$2");

    if (table != 0) {
        m = (volatile s32 *)scratch_alloc(0x20);
        r = &table->rec[idx];
        rot_matrix((s32 *)m, r->ang[0], r->ang[1], r->ang[2]);
        m[5] = r->pos[0];
        m[6] = r->pos[1];
        tz = r->pos[2];
        m[7] = tz;
        r0 = m[0];
        r1 = m[1];
        r2 = m[2];
        gte_set_ctrl(R11R12, r0);
        gte_set_ctrl(R13R21, r1);
        gte_set_ctrl(R22R23, r2);
        r0 = m[3];
        r1 = m[4];
        gte_set_ctrl(R31R32, r0);
        gte_set_ctrl(R33, r1);
        r2 = m[6];
        {
            register s32 tx asm("$17") = m[5];
            gte_set_TR(tx, r2, tz);
        }
        gte_load(IR1, out, 0);
        gte_load(IR2, out, 4);
        gte_load(IR3, out, 8);
        gte_rtirtr();
        gte_store(MAC1, out, 0);
        gte_store(MAC2, out, 4);
        gte_store(MAC3, out, 8);
        world = world_matrix_get();
        r0 = world[0];
        r1 = world[1];
        world_r2 = world[2];
        gte_set_ctrl(R11R12, r0);
        gte_set_ctrl(R13R21, r1);
        gte_set_ctrl(R22R23, world_r2);
        r0 = world[3];
        r1 = world[4];
        gte_set_ctrl(R31R32, r0);
        gte_set_ctrl(R33, r1);
        gte_set_ctrl(TRX, 0);
        gte_set_ctrl(TRY, 0);
        gte_set_ctrl(TRZ, 0);
        gte_load(IR1, out, 0);
        gte_load(IR2, out, 4);
        gte_load(IR3, out, 8);
        gte_rtirtr();
        gte_store(MAC1, out, 0);
        gte_store(MAC2, out, 4);
        gte_store(MAC3, out, 8);
        scratch_top -= 0x20;
    }
}

extern ObjAngleTableSlot obj_angle_tables[];
/* Writes to out the angles of the object's record `idx`, combined with the matrix of world_matrix_get. */
void obj_rec_angles(Object *obj, s32 idx, SVECTOR *out) {
    s32 base = obj->type.unk_0E;
    ObjAngleTable *table = obj_angle_tables[(base + get_world_offset()) & 0x7FF].table;
    ObjAngleRec *r;
    s32 *mat;
    s32 *ang;

    if (table != 0) {
        mat = scratch_alloc(0x20);
        ang = scratch_alloc(0x10);
        r = &table->rec[idx];
        rot_matrix(mat, r->ang[0], r->ang[1], r->ang[2]);
        mul_matrix(world_matrix_get(), mat, mat);
        matrix_to_angles(mat, &ang[1], &ang[0], &ang[2]);
        out->vx = ang[0];
        out->vy = ang[1];
        scratch_top -= 0x30;
        out->vz = ang[2];
    }
}

void obj_angles_to_point(Object *obj, s32 *target, s32 *yaw, s32 *pitch) {
    s32 *v = (s32 *)scratch_alloc(0x10);
    volatile s32 *rot = (volatile s32 *)scratch_alloc(0x40);
    s32 *rot2 = (s32 *)rot + 8;
    s32 a, b, c;

    rot_matrix_b((void *)rot, -obj->vars.turn.yaw, 0, 0);
    rot_matrix_b(rot2, obj->rot_angles[1], obj->rot_angles[0], obj->rot_angles[2]);
    mul_matrix((void *)rot, rot2, (void *)rot);
    a = rot[0];
    b = rot[1];
    c = rot[2];
    gte_set_ctrl(R11R12, a);
    gte_set_ctrl(R13R21, b);
    gte_set_ctrl(R22R23, c);
    a = rot[3];
    b = rot[4];
    gte_set_ctrl(R31R32, a);
    gte_set_ctrl(R33, b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    v[0] = (target[0] - obj->x) >> 12;
    v[1] = ((target[1] - obj->y) >> 12) + (s16)obj->height / 2;
    v[2] = (target[2] - obj->z) >> 12;
    gte_load(IR1, v, 0);
    gte_load(IR2, v, 4);
    gte_load(IR3, v, 8);
    gte_rtirtr();
    gte_store(MAC1, v, 0);
    gte_store(MAC2, v, 4);
    gte_store(MAC3, v, 8);
    vector_to_angles(v[0], v[1], v[2], yaw, pitch);
    scratch_top -= 0x50;
}

void obj_angles_to_point(Object *obj, s32 *target, s32 *yaw, s32 *pitch);

/* Converts a position (whole units) to 12-bit fixed point through a scratch vector, then calls obj_angles_to_point. */
void obj_angles_to_target(void *a, s32 *b, s32 *c) {
    Vec3 *v = scratch_alloc(0x10);

    player_position_copy((VECTOR *)v);
    v->x <<= 12;
    v->y <<= 12;
    v->z <<= 12;
    obj_angles_to_point(a, (s32 *)v, b, c);
    scratch_top -= 0x10;
}

s32 obj_player_in_view(Object *obj, s32 max_yaw, s32 max_pitch) {
    s32 yaw;
    s32 pitch;
    register s32 ok asm("$2");

    obj_angles_to_target(obj, &yaw, &pitch);
    if (yaw > 0x800) {
        yaw = 0x1000 - yaw;
    }
    if (pitch > 0x800) {
        pitch = 0x1000 - pitch;
    }
    ok = 0;
    if (max_yaw >= yaw) {
        ok = max_pitch >= pitch;
    }
    return ok;
}

s32 obj_facing_within(void *a, s32 limit) {
    s32 angle;
    s32 unused;

    obj_angles_to_target(a, &angle, &unused);
    if (angle >= 0x801) {
        angle = 0x1000 - angle;
    }
    return limit >= angle;
}

s32 obj_bearing_to_point(Object *obj) {
    s32 y = (obj->x >> 12) + 0x258;
    return atan2((obj->z >> 12) - 0xBB8, y);
}

static inline void rot_y_matrix(RotMatrix *m, u32 sincos) {
    s16 cos_val;
    s16 neg_sin;

    m->m[0][1] = 0;
    m->m[1][0] = 0;
    m->m[1][1] = 0x1000;
    m->m[1][2] = 0;
    m->m[2][1] = 0;
    cos_val = sincos >> 16;
    neg_sin = -sincos;
    m->m[0][0] = cos_val;
    m->m[0][2] = sincos;
    m->m[2][0] = neg_sin;
    m->m[2][2] = cos_val;
}
/*
 * Casts a ray 0x2000 units from the object's position (0x20 up) along its yaw turned by quadrant * 90 degrees.
 * Returns the distance to the first world hit, or 0x2000 when nothing is hit.
 */
s32 obj_wall_probe_dist(Object *obj, s32 quadrant) {
    s32 *ray = scratch_alloc(0x40);
    RotMatrix *rot = scratch_alloc(0x40);
    s32 *from = &ray[4];
    s32 *to = &ray[8];
    s32 *hit = &ray[12];
    s32 dist;
    volatile s32 *words;
    s32 m_a, m_b, m_c;

    ray[0] = 0;
    ray[1] = 0;
    ray[2] = 0x2000;
    rot_y_matrix(&rot[1], rcossin_tbl[(quadrant << 10) & 0xC00]);
    rot_y_matrix(&rot[0], rcossin_tbl[obj->yaw & 0xFFF]);
    mul_matrix(&rot[0], &rot[1], &rot[0]);
    words = (volatile s32 *)rot;
    m_a = words[0];
    m_b = words[1];
    m_c = words[2];
    gte_set_ctrl(R11R12, m_a);
    gte_set_ctrl(R13R21, m_b);
    gte_set_ctrl(R22R23, m_c);
    m_a = words[3];
    m_b = words[4];
    gte_set_ctrl(R31R32, m_a);
    gte_set_ctrl(R33, m_b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    gte_ldlvl(ray);
    gte_rtirtr();
    gte_stlvnl(ray);
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    from[1] -= 0x20;
    to[0] = from[0] + ray[0];
    to[1] = from[1] + ray[1];
    to[2] = from[2] + ray[2];
    if (trace_world(8, 4, from, to, hit) != 1) {
        scratch_top -= 0x80;
        return 0x2000;
    }
    dist = isqrt(length_sq(hit[0] - from[0], hit[1] - from[1], hit[2] - from[2]));
    scratch_top -= 0x80;
    return dist;
}

/*
 * Casts a ray from the object's position along its bearing (Y-axis rotation
 * of the forward vector (0, 0, 0x2000), built into a GTE matrix). Returns the
 * distance to the first world hit, or 0x2000 when nothing is hit.
 */
s32 obj_trace_dist_to_target(Object *obj) {
    s32 *ray = scratch_alloc(0x40);
    volatile s16 *rot = scratch_alloc(0x20);
    u32 sincos;
    s16 neg_sin;
    register s16 cos_val asm("$4");
    s32 m_a, m_b, m_c, dist;
    s32 *from = &ray[4];
    s32 *to = &ray[8];
    s32 *hit = &ray[12];
    volatile s32 *rot_words = (volatile s32 *)rot;

    ray[0] = 0;
    ray[1] = 0;
    ray[2] = 0x2000;
    ray[4] = obj->x >> 12;
    ray[5] = obj->y >> 12;
    ray[6] = obj->z >> 12;
    ray[5] -= 0x20;
    sincos = rcossin_tbl[obj_bearing_to_point(obj) & 0xFFF];
    rot[1] = 0;
    rot[3] = 0;
    rot[4] = 0x1000;
    rot[5] = 0;
    rot[7] = 0;
    cos_val = sincos >> 16;
    neg_sin = -sincos;
    rot[2] = sincos;
    rot[0] = cos_val;
    rot[6] = neg_sin;
    rot[8] = cos_val;
    m_a = rot_words[0];
    m_b = rot_words[1];
    m_c = rot_words[2];
    gte_set_ctrl(R11R12, m_a);
    gte_set_ctrl(R13R21, m_b);
    gte_set_ctrl(R22R23, m_c);
    m_a = rot_words[3];
    m_b = rot_words[4];
    gte_set_ctrl(R31R32, m_a);
    gte_set_ctrl(R33, m_b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    gte_ldlvl(ray);
    gte_rtirtr();
    gte_stlvnl(ray);
    to[0] = from[0] + ray[0];
    to[1] = from[1] + ray[1];
    to[2] = from[2] + ray[2];
    if (trace_world(8, 4, from, to, hit) != 1) {
        scratch_top -= 0x60;
        return 0x2000;
    }
    dist = isqrt(length_sq(hit[0] - from[0], hit[1] - from[1], hit[2] - from[2]));
    scratch_top -= 0x60;
    return dist;
}

/* Casts a ray 0x2000 units forward along the yaw from a fixed offset; returns the distance from the player to the hit point, or 0x2000 when nothing is hit. */
s32 probe_wall_dist(s32 yaw) {
    s32 *buf = scratch_alloc(0x40);
    s32 *dir = buf;
    s32 *from = buf + 4;
    s32 *to = buf + 8;
    s32 *hit = buf + 12;
    volatile RotMatrix *mat;
    u32 sc;
    s32 a, b, c;
    s32 *pp;
    s32 dist;

    from[0] = -600;
    from[1] = -0xC40;
    from[2] = 0xBB8;
    mat = scratch_alloc(sizeof(RotMatrix));
    sc = rcossin_tbl[yaw & 0xFFF];
    mat->m[0][1] = 0;
    mat->m[1][0] = 0;
    mat->m[1][1] = 0x1000;
    mat->m[1][2] = 0;
    mat->m[2][1] = 0;
    {
        register s16 cos asm("$5") = sc >> 16;
        s16 neg_sin = -sc;

        mat->m[0][2] = sc;
        mat->m[0][0] = cos;
        mat->m[2][0] = neg_sin;
        mat->m[2][2] = cos;
    }
    a = ((volatile s32 *)mat)[0];
    b = ((volatile s32 *)mat)[1];
    c = ((volatile s32 *)mat)[2];
    gte_set_ctrl(R11R12, a);
    gte_set_ctrl(R13R21, b);
    gte_set_ctrl(R22R23, c);
    a = ((volatile s32 *)mat)[3];
    b = ((volatile s32 *)mat)[4];
    gte_set_ctrl(R31R32, a);
    gte_set_ctrl(R33, b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    dir[0] = 0;
    dir[1] = 0;
    dir[2] = 0x2000;
    gte_load(IR1, dir, 0);
    gte_load(IR2, dir, 4);
    gte_load(IR3, dir, 8);
    gte_rtirtr();
    gte_store(MAC1, dir, 0);
    gte_store(MAC2, dir, 4);
    gte_store(MAC3, dir, 8);
    to[0] = from[0] + dir[0];
    to[1] = from[1] + dir[1];
    to[2] = from[2] + dir[2];
    if (trace_world(8, 1, from, to, hit) != 1) {
        scratch_top -= 0x60;
        return 0x2000;
    }
    pp = player_position();
    dist = isqrt(length_sq(hit[0] - pp[0], 0, hit[2] - pp[2]));
    scratch_top -= 0x60;
    return dist;
}

/* Horizontal (x/z) distance from the player to obj, in the same units as isqrt. */
s32 obj_dist_xz_to_player(Object *obj) {
    s32 *pos = player_position();

    return isqrt(length_sq(pos[0] - (obj->x >> 12), 0, pos[2] - (obj->z >> 12)));
}

/* Distance from the object's x/z position (fixed point, 12 fraction bits) to the point (-0x258, 0, 0xBB8) in whole units. */
s32 obj_dist_to_fixed_point(Object *obj) {
    return isqrt(length_sq(-0x258 - (obj->x >> 12), 0, 0xBB8 - (obj->z >> 12)));
}

/* Turns the object's yaw toward yaw + yaw_offset, by at most step per call. */
void obj_turn_to_offset(Object *obj, s32 step) {
    s16 yaw = obj->vars.turn.yaw;

    obj->vars.turn.yaw = angle_approach(yaw, obj->vars.turn.yaw_offset + yaw, step);
}

void obj_update_yaw_offset(Object *obj) {
    s32 out_a;
    s32 out_b;

    obj_angles_to_target(obj, &out_a, &out_b);
    obj->vars.turn.yaw_offset = out_a;
}

void obj_yaw_offset_to_fixed(void *obj) {
    s32 *buf = scratch_alloc(0x10);
    s32 result;
    s32 unused;

    buf[0] = 0xFFDA8000;
    buf[1] = 0xFF840000;
    buf[2] = 0xBB8000;
    obj_angles_to_point(obj, buf, &result, &unused);
    *(s16 *)((u8 *)obj + 0x278) = result;
    scratch_top -= 0x10;
}

void world_matrix_set(s32 *m);
/* Builds the object's rotation matrix and writes its angles back: pitch is negated. */
void obj_angles_from_matrix(Object *obj) {
    s32 *m = scratch_alloc(0x20);
    Vec3 *angles = scratch_alloc(0x10);
    s32 pitch;
    s32 yaw;
    s32 roll;

    obj_rot_matrix(obj, m);
    matrix_to_angles(m, &angles->y, &angles->x, &angles->z);
    world_matrix_set(m);
    pitch = angles->x;
    yaw = angles->y;
    roll = angles->z;
    scratch_top -= 0x30;
    obj->pitch = -pitch;
    obj->yaw = yaw;
    obj->roll = roll;
}

/* Reads one u16 from the stream at unk_1C.unk_04 (advancing it by 2 bytes),
 * writes it to the packet at vars.enemy.mode, and zeroes the next three shorts. */
void script_read_mode(Object *obj) {
    u16 *src;
    s16 *dst;
    u16 value;

    src = (u16 *)obj->script.pc;
    obj->script.pc = (s16 *)(src + 1);
    dst = (s16 *)obj->vars.enemy.mode;
    value = *src;
    dst[1] = 0;
    dst[2] = 0;
    dst[3] = 0;
    dst[0] = value;
}

void script_branch_eq(ScriptBranchCtx *obj) {
    s16 *pc = obj->pc;
    s16 *expected = obj->expected;
    s32 value;
    s32 index;

    obj->pc = pc + 1;
    value = *pc;
    obj->pc = pc + 2;
    index = pc[1];
    if (value == *expected) {
        obj->pc = (s16 *)obj->targets[index];
    }
}

void script_jump_if_fixed_point_dist(Object *obj) {
    s16 *cursor;
    s32 threshold;
    s32 index;
    s32 dist;
    s32 radius;
    s32 far;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    radius = threshold;
    dist = isqrt(length_sq(-600 - (obj->x >> 12), 0, 3000 - (obj->z >> 12)));
    if (radius >= 0) {
        far = radius < dist;
    } else {
        radius = ~threshold;
        far = dist < radius;
    }
    if (!far) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}


/* Reads two halfwords from the object's script; if obj_player_in_view accepts the first, the
   script continues at the entry (the second halfword) of the object's table. */
void script_op_jump_if_in_range(Object *obj) {
    s16 *script = obj->script.pc;
    s32 first;
    s32 index;

    obj->script.pc = script + 1;
    first = script[0];
    obj->script.pc = script + 2;
    index = script[1];
    if (obj_player_in_view(obj, first, first) != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}


void script_branch_threshold(Object *obj) {
    s16 *cursor;
    s32 threshold;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (obj_facing_within(obj, threshold)) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_jump_if_at_least(Object *obj) {
    s16 *cursor;
    s32 lo;
    s32 hi;
    s32 value;
    s32 limit;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    lo = cursor[0];
    obj->script.pc = cursor + 2;
    hi = cursor[1] << 16;
    value = (lo & 0xFFFF) | hi;
    obj->script.pc = cursor + 3;
    limit = ABS(obj->vars.enemy.sound);
    index = cursor[2];
    if (value >= limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

s32 probe_wall_dist(s32 yaw);
s32 obj_trace_dist_to_target(Object *obj);
/* Reads the next 16-bit word of the object's script stream. When the
 * current value passes both range checks, the stream jumps to the
 * address stored in the table at obj->unk_1C.data[word]. */
void script_jump_if_in_range(Object *obj) {
    s16 *script;
    s32 word;

    script = obj->script.pc;
    obj->script.pc = script + 1;
    word = *script;
    if (probe_wall_dist(obj_bearing_to_point(obj)) >= 0x6A5) {
        if ((u32) (obj_trace_dist_to_target(obj) - 0x3E9) < 0x397U) {
            obj->script.pc = ((s16 **)obj->script.data)[word];
        }
    }
}

/* Script step: reads the next opcode from the stream at unk_1C.unk_04; if
 * obj_dist_xz_to_player returns at least 0x7D1, jumps to the entry for the opcode in
 * the per-type table at unk_1C.data. */
void script_jump_by_opcode(Object *obj) {
    s16 *cursor;
    s32 opcode;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    opcode = cursor[0];
    if (obj_dist_xz_to_player(obj) >= 0x7D1) {
        obj->script.pc = ((s16 **)obj->script.data)[opcode];
    }
}

/* Same code as func_800B7534 (s01). */
void quick_fuchikoma_m8_boss_phase0(Object *obj) {
    if (obj->health > 0) {
        obj_link_script_run();
    }
}

/* Turns the object's velocity (unk_270, vy, speed) by its yaw into ctrl's position; with a radius in
 * unk_264, adds an offset at angle unk_27A, turned by ctrl's rotation. Copies unk_1B7 into flag bit 0. */
void quick_fuchikoma_m8_boss_target_update(Object *obj, TargetCtrl *ctrl) {
    BossM8Vars *vars = (BossM8Vars *)&obj->vars;
    s32 *vec = scratch_alloc(0x20);
    s32 *mat = scratch_alloc(0x20);
    s32 *offset;
    register s32 word0 asm("$3");
    register s32 word1 asm("$4");
    register s32 word2 asm("$2");

    rot_matrix(mat, vars->unk_24E, 0, 0);
    offset = vec + 4;
    word0 = mat[0];
    word1 = mat[1];
    word2 = mat[2];
    gte_set_ctrl(R11R12, word0);
    gte_set_ctrl(R13R21, word1);
    gte_set_ctrl(R22R23, word2);
    word0 = mat[3];
    word1 = mat[4];
    gte_set_ctrl(R31R32, word0);
    gte_set_ctrl(R33, word1);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    vec[0] = vars->unk_270 >> 12;
    vec[1] = obj->vy >> 12;
    vec[2] = obj->speed >> 12;
    gte_load(IR1, vec, 0);
    gte_load(IR2, vec, 4);
    gte_load(IR3, vec, 8);
    gte_rtirtr_sf0();
    gte_store(MAC1, vec, 0);
    gte_store(MAC2, vec, 4);
    gte_store(MAC3, vec, 8);
    word0 = vars->circle_radius; /* the radius shares the matrix word's register */
    if (word0 != 0) {
        s32 angle = vars->circle_angle;
        s32 x = word0 * (s16)rcossin_tbl[angle & 0xFFF] / 4096;
        s32 cos = cos_table[angle & 0xFFF].value;

        offset[0] = x;
        offset[1] = 0;
        offset[2] = vars->circle_radius * cos / 4096;
        rot_matrix_b(mat, ctrl->rot[1], ctrl->rot[0], ctrl->rot[2]);
        word0 = mat[0];
        word1 = mat[1];
        word2 = mat[2];
        gte_set_ctrl(R11R12, word0);
        gte_set_ctrl(R13R21, word1);
        gte_set_ctrl(R22R23, word2);
        word0 = mat[3];
        word1 = mat[4];
        gte_set_ctrl(R31R32, word0);
        gte_set_ctrl(R33, word1);
        offset[0] >>= 12;
        offset[1] >>= 12;
        offset[2] >>= 12;
        gte_load(IR1, offset, 0);
        gte_load(IR2, offset, 4);
        gte_load(IR3, offset, 8);
        gte_rtirtr_sf0();
        gte_store(MAC1, offset, 0);
        gte_store(MAC2, offset, 4);
        gte_store(MAC3, offset, 8);
        vec[0] += offset[0];
        vec[1] += offset[1];
        vec[2] += offset[2];
    }
    ctrl->pos = *(Vector3 *)vec;
    scratch_top -= 0x40;
    do { /* a loop doubles ctrl's register priority (s2 over obj) */
        if (obj->unk_1B7) {
            ctrl->flags |= 1;
        } else {
            ctrl->flags &= ~1;
        }
    } while (0);
}

/* Behaviour step: on result -2 starts the sequence, on a hit at 1 reports done, else advances the timer. */
void obj_jump_land_step(Object *obj, ObjHandler *handler) {
    s32 result = handler->result;
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    if (result == -2) {
        obj->vy = 0xFFFB4000;
        obj->unk_1B7 = 0;
        handler->queued_entry = -1;
        handler->result = 1;
        sound_play_at_units(SND_FUCHIKOMA_LAND | SND_GROUP(2), 0x7F, 0x3C, pos);
        obj->vars.quick_fuchikoma_m8_boss.unk_264 = 0x10000;
        *(s16 *)((u8 *)obj + 0x27A) = obj_bearing_to_point(obj);
    } else {
        if ((u8)obj->unk_1B7 == 1) {
            sound_play_at_units(SND_FUCHIKOMA_LAND_ALT | SND_GROUP(2), 0x7F, 0x3C, pos);
            obj->vars.quick_fuchikoma_m8_boss.unk_264 = 0;
            obj_request_state(obj, handler, 4, 0);
            scratch_top -= 0x10;
            return;
        }
        obj->vars.quick_fuchikoma_m8_boss.unk_264 += 0x1000;
    }
    scratch_top -= 0x10;
}

extern s32 quick_fuchikoma_charge;
extern s32 quick_fuchikoma_charge_step;
extern s32 quick_fuchikoma_charge_timer;
extern s32 quick_fuchikoma_charge_mode;
/* Behaviour step: on result -2 starts the sequence (vy up, sound, effect globals); once the object is within
 * 0x10 of y = -0x840 (whole units) after that it plays the landing sound and moves on to state 4. */
void obj_land_update(Object *obj, ObjHandler *handler) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 y, t;

    if (handler->result == -2) {
        obj->vy = 0xFFFF0000;
        obj->unk_1B7 = 0;
        handler->queued_entry = -1;
        handler->result = 1;
        obj->vars.quick_fuchikoma_m8_boss.unk_264 = 0xFFFE8000;
        *(s16 *)((u8 *)obj + 0x27A) = obj_bearing_to_point(obj);
        sound_play_at_units(SND_FUCHIKOMA_LAND | SND_GROUP(2), 0x7F, 0x3C, pos);
        if (quick_fuchikoma_charge != 0) {
            quick_fuchikoma_charge_mode = 2;
            quick_fuchikoma_charge_step = 0x44;
            quick_fuchikoma_charge_timer = 0x1E;
        }
    } else if ((u8)obj->unk_1B7 == 1) {
        y = obj->y >> 12;
        t = y + 0x840;
        if (t >= 0 ? t < 0x10 : -0x840 - y < 0x10) {
            obj->vars.quick_fuchikoma_m8_boss.unk_264 = 0;
            sound_play_at_units(SND_FUCHIKOMA_LAND_ALT | SND_GROUP(2), 0x7F, 0x3C, pos);
            obj_request_state(obj, handler, 4, 0);
        }
    }
    scratch_top -= 0x10;
}

extern s16 *quick_fuchikoma_turn_pos_slot[];
extern s16 *quick_fuchikoma_turn_neg_slot[];
extern s16 *quick_fuchikoma_m8_boss_data[];
/* Behaviour step: on result -2 picks a turn direction from the bearing to the target point, starts the
 * turn script and plays a sound; then turns yaw toward yaw_offset until within 4 and the timer runs out. */
void quick_fuchikoma_face_target(Object *obj, ObjHandler *handler) {
    s32 bearing;
    s32 target;
    Vec3 *pos;
    s16 *pc;
    s32 diff;
    register Script *script asm("$4"); /* set before the branch, as the original */

    if (handler->result == -2) {
        handler->queued_entry = -1;
        handler->result = 1;
        bearing = obj_bearing_to_point(obj);
        target = bearing - obj->rot_angles[1];
        diff = angle_diff(obj->vars.turn.yaw, target);
        script = (Script *)obj;
        if (diff < 0) {
            obj->vars.turn.yaw_offset = target - 0x400;
            obj->type.unk_0A = 2;
            pc = quick_fuchikoma_turn_neg_slot[0];
        } else {
            obj->vars.turn.yaw_offset = target + 0x400;
            obj->type.unk_0A = 2;
            pc = quick_fuchikoma_turn_pos_slot[0];
        }
        script_jump(script, pc, (s32)quick_fuchikoma_m8_boss_data);
        pos = scratch_alloc(0x10);
        obj->vars.turn.bearing = bearing;
        obj->vars.quick_fuchikoma_m8_boss.unk_264 = 0x20000;
        obj->speed = 0;
        pos->x = obj->x >> 12;
        pos->y = obj->y >> 12;
        pos->z = obj->z >> 12;
        sound_play_at_units(SND_FUCHIKOMA_BOSS_CHARGE | SND_GROUP(1), 0x7F, 0x3C, pos);
        scratch_top -= 0x10;
        if (rand_a_next() < 0x800 && quick_fuchikoma_charge_mode == 0) {
            quick_fuchikoma_charge_mode = 1;
            quick_fuchikoma_charge_step = 0x44;
            quick_fuchikoma_charge_timer = 0;
        }
    } else {
        obj->vars.quick_fuchikoma_m8_boss.unk_264 -= 0x1000;
        if (obj->vars.quick_fuchikoma_m8_boss.unk_264 < 0) {
            obj->vars.quick_fuchikoma_m8_boss.unk_264 = 0;
        }
        if (ABS(angle_diff(obj->vars.turn.yaw, obj->vars.turn.yaw_offset)) >= 5) {
            obj->vars.turn.yaw = angle_approach(obj->vars.turn.yaw, obj->vars.turn.yaw_offset, 0x20);
        } else if (obj->vars.quick_fuchikoma_m8_boss.unk_264 == 0) {
            obj_request_state(obj, handler, 0, 0);
        }
    }
}

void obj_accel_behaviour(Object *obj, ObjHandler *h) {
    if (h->result == -2) {
        h->queued_entry = -1;
        h->result = 1;
        obj->speed_accel = 0x1000;
        return;
    }
    obj->speed += obj->speed_accel;
    obj->speed = MAX(MIN(obj->speed, obj->vars.snd2.sound[0]), 0);
    obj_update_yaw_offset(obj);
    obj_turn_to_offset(obj, 0x16);
}

void obj_accel_step(Object *obj) {
    obj->speed += obj->speed_accel;
    obj->speed = MAX(MIN(obj->speed, obj->vars.snd2.sound[0]), 0);
    obj_yaw_offset_to_fixed(obj);
    obj_turn_to_offset(obj, 0x16);
}

/* Behaviour step: on result -2 picks a random side, starts its strafe script and a sound; then
 * accelerates up to the speed limit while the sideways offset (words[0xA]) runs to 0, and ends the state. */
void quick_fuchikoma_m8_boss_dash(Object *obj, ObjHandler *handler) {
    if (handler->result == -2) {
        Vec3 *pos;
        s32 dir;
        s32 rnd;
        s16 *pc;
        register Script *script asm("$4"); /* set before the branch, as the original */

        handler->queued_entry = -1;
        handler->result = 1;
        rnd = rand_a_next();
        dir = -1;
        if (rnd >= 0x801) {
            dir = 1;
            obj->type.unk_0A = 2;
            pc = quick_fuchikoma_turn_neg_slot[0];
            script = (Script *)obj;
        } else {
            script = (Script *)obj;
            obj->type.unk_0A = 2;
            pc = quick_fuchikoma_turn_pos_slot[0];
        }
        script_jump(script, pc, (s32)quick_fuchikoma_m8_boss_data);
        obj->vars.words[0xA] = dir * 0x24000;
        obj->vars.words[0xB] = -dir * 0xBB8;
        obj->speed_accel = -0x1000;
        pos = scratch_alloc(0x10);
        pos->x = obj->x >> 12;
        pos->y = obj->y >> 12;
        pos->z = obj->z >> 12;
        sound_play_at_units(SND_FUCHIKOMA_BOSS_CHARGE | SND_GROUP(1), 0x7F, 0x3C, pos);
        scratch_top -= 0x10;
        if (rand_a_next() >= 0xD57 && quick_fuchikoma_charge_mode == 0) {
            quick_fuchikoma_charge_mode = 1;
            quick_fuchikoma_charge_step = 0x44;
            quick_fuchikoma_charge_timer = 0;
        }
    } else {
        s32 limit;
        s32 next;
        s32 clamped;
        s32 lo;

        obj_update_yaw_offset(obj);
        obj_turn_to_offset(obj, 0x20);
        limit = obj->vars.quick_fuchikoma_m8_boss.speed_limit;
        next = obj->speed + obj->speed_accel;
        obj->speed = next;
        obj->vars.words[0xA] += obj->vars.words[0xB];
        clamped = next;
        if (limit < clamped) {
            clamped = limit;
        }
        lo = next;
        if (limit < lo) {
            lo = limit;
        }
        if (lo < 0) {
            clamped = 0;
        }
        obj->speed = clamped;
        if (obj->vars.words[0xB] < 0 ? obj->vars.words[0xA] <= 0 : obj->vars.words[0xA] >= 0) {
            obj->vars.words[0xA] = 0;
            obj_request_state(obj, handler, 0, 0);
        }
    }
}

void obj_update_yaw_offset(Object *obj);
/* When the handler's result is -2 (done), sets its unk_0C to -1, its result to 1 and clears the
 * object's speed. */
void obj_turn_stop_behaviour(Object *obj, ObjHandler *handler) {
    if (handler->result == -2) {
        handler->queued_entry = -1;
        handler->result = 1;
        obj->speed = 0;
        return;
    }
    obj_update_yaw_offset(obj);
    obj_turn_to_offset(obj, 0x12);
}

/* When the handler's result is -2 (done), sets its unk_0C to -1, its result to 1 and clears the
 * object's speed. */
void obj_stop_behaviour(Object *obj, ObjHandler *handler) {
    if (handler->result == -2) {
        handler->queued_entry = -1;
        handler->result = 1;
        obj->speed = 0;
    }
}

void obj_weave_update(Object *obj, ObjHandler *handler) {
    s32 yaw;
    s32 pitch;

    if (handler->result == -2) {
        handler->queued_entry = -1;
        handler->result = 1;
        obj->vars.quick_fuchikoma_m8_boss.frame_counter = 0;
        obj->speed_accel = 0x1000;
        return;
    }
    obj->speed += obj->speed_accel;
    obj->speed = MAX(MIN(obj->speed, obj->vars.quick_fuchikoma_m8_boss.speed_limit), 0);
    if ((s16)((s16)obj->vars.quick_fuchikoma_m8_boss.frame_counter % 90) == 0) {
        volatile GteMatrix *mat = scratch_alloc(0x20);
        s32 *vec = scratch_alloc(0x10);
        s32 a, b, c;
        s32 angle = obj_bearing_to_point(obj);
        u32 sc;
        s32 *out;

        if (rand_a_next() < 0x800) {
            angle += 0x2BC;
        } else {
            angle -= 0x2BC;
        }
        vec[2] = 0xFA0;
        vec[0] = 0;
        vec[1] = 0;
        sc = rcossin_tbl[angle & 0xFFF];
        mat->h[1] = 0;
        mat->h[3] = 0;
        mat->h[4] = 0x1000;
        mat->h[5] = 0;
        mat->h[7] = 0;
        {
            register s16 cos asm("$4") = sc >> 16;
            s16 neg_sin = -sc;

            mat->h[0] = cos;
            mat->h[2] = sc;
            mat->h[6] = neg_sin;
            mat->h[8] = cos;
        }
        a = mat->w[0];
        b = mat->w[1];
        c = mat->w[2];
        gte_set_ctrl(R11R12, a);
        gte_set_ctrl(R13R21, b);
        gte_set_ctrl(R22R23, c);
        a = mat->w[3];
        b = mat->w[4];
        gte_set_ctrl(R31R32, a);
        gte_set_ctrl(R33, b);
        mat->w[5] = -0x258;
        mat->w[6] = -0xE74;
        mat->w[7] = 0xBB8;
        {
            register s32 tz asm("$3") = 0xBB8;
            register s32 ty asm("$2") = mat->w[6];
            register s32 tx asm("$16") = mat->w[5];
            gte_set_ctrl(TRX, tx);
            gte_set_ctrl(TRY, ty);
            gte_set_ctrl(TRZ, tz);
        }
        out = (s32 *)&obj->vars.quick_fuchikoma_m8_boss.unk_254;
        gte_load(IR1, vec, 0);
        gte_load(IR2, vec, 4);
        gte_load(IR3, vec, 8);
        gte_rtirtr_sf0();
        gte_store(MAC1, out, 0);
        gte_store(MAC2, out, 4);
        gte_store(MAC3, out, 8);
        scratch_top -= 0x30;
    }
    obj_angles_to_point(obj, (s32 *)&obj->vars.quick_fuchikoma_m8_boss.unk_254, &yaw, &pitch);
    obj->vars.turn.yaw_offset = yaw;
    obj_turn_to_offset(obj, 0x26);
    obj->vars.quick_fuchikoma_m8_boss.frame_counter = (obj->vars.quick_fuchikoma_m8_boss.frame_counter + 1) & 0xFFF;
}

void obj_update_yaw_offset(Object *obj);
void obj_turn_to_offset(Object *obj, s32 arg);
/* Steps the object; when its behaviour reports -2 it is reset, when it reaches stage 1 it plays a sound
 * at its position and moves on to behaviour 4. */
void obj_turn_hover_update(Object *obj, ObjHandler *handler) {
    TurnHoverVars *vars = (TurnHoverVars *)&obj->vars;
    s32 *pos = scratch_alloc(0x10);
    s32 result = handler->result;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    if (result == -2) {
        obj->vy = 0;
        obj->unk_1B7 = 0;
        handler->queued_entry = -1;
        handler->result = 1;
        vars->unk_264 = 0xC000;
        vars->unk_27A = 0x400;
    } else {
        obj_update_yaw_offset(obj);
        obj_turn_to_offset(obj, 0x10);
        if ((u8)obj->unk_1B7 == 1) {
            vars->unk_264 = 0;
            sound_play_at_units(SND_FUCHIKOMA_LAND_ALT | SND_GROUP(2), 0x7F, 0x3C, pos);
            obj_request_state(obj, handler, 4, 0);
        }
    }
    scratch_top -= 0x10;
}

extern s32 quick_fuchikoma_heat;
extern s32 quick_fuchikoma_charge_sounded;
void laser_charge_update(Object *obj);
void blink_update(Object *obj);
void muzzle_burst_update(Object *obj);
void stage_cue_update(Object *obj);
void quick_fuchikoma_m8_boss_update(Object *obj, ObjHandler *handler) {
    s16 *vars = (s16 *)obj->vars.quick_fuchikoma_m8_boss.unk_248;
    ObjSnapshot *snap;
    s32 *level;
    VECTOR *pos;
    s32 lim;
    s32 vy;

    if (obj->health > 0) {
        obj_script_step(obj, handler);
        switch (*vars) {
        case 1:
            laser_charge_update(obj);
            break;
        case 3:
            blink_update(obj);
            break;
        case 4:
            muzzle_burst_update(obj);
            break;
        case 2:
            stage_cue_update(obj);
            break;
        }
    }
    snap = (ObjSnapshot *)obj->rot_angles;
    if (!(obj->ground_flags & 1)) {
        obj->vy += obj->accel_y;
    }
    lim = obj->vy;
    if (obj->scale[1] < lim) {
        lim = obj->scale[1];
    }
    vy = obj->vy;
    if (vy < lim) {
        vy = lim;
    }
    obj->vy = vy;
    quick_fuchikoma_m8_boss_target_update(obj, (TargetCtrl *)snap);
    player_step_move_scratch(snap);
    obj_snapshot_restore(obj, snap);
    if ((u8)obj->blocked_y != 0) {
        obj->vy = 0;
    }
    obj_angles_from_matrix(obj);
    level = &quick_fuchikoma_charge;
    switch (quick_fuchikoma_charge_mode) {
    case 1:
        if (quick_fuchikoma_charge_timer > 0) {
            quick_fuchikoma_charge_timer--;
            break;
        }
        if (quick_fuchikoma_charge_sounded == 0) {
            VECTOR sound_pos;
            pos = &sound_pos;
            pos->vx = obj->x >> 12;
            pos->vy = obj->y >> 12;
            pos->vz = obj->z >> 12;
            sound_scale_pos_about_listener(pos, pos, 0x800);
            sound_play_at_units(SND_POWER_ON, 0x7F, 0x3C, pos);
            quick_fuchikoma_charge_sounded = 1;
        }
        *level += quick_fuchikoma_charge_step;
        if (*level > 0x1000) {
            *level = 0x1000;
            quick_fuchikoma_charge_mode = 3;
            quick_fuchikoma_heat = 0;
            quick_fuchikoma_charge_sounded = 0;
        }
        break;
    case 2:
        if (quick_fuchikoma_charge_timer > 0) {
            quick_fuchikoma_charge_timer--;
            break;
        }
        if (quick_fuchikoma_charge_sounded == 0) {
            VECTOR fade_pos;
            VECTOR *fade_ptr = &fade_pos;
            FAKE_OPAQUE(fade_ptr);
            fade_pos.vx = obj->x >> 12;
            fade_pos.vy = obj->y >> 12;
            fade_pos.vz = obj->z >> 12;
            sound_scale_pos_about_listener(fade_ptr, fade_ptr, 0x800);
            sound_play_at_units(SND_POWER_ON, 0x7F, 0x3C, &fade_pos);
            quick_fuchikoma_charge_sounded = 1;
        }
        *level -= quick_fuchikoma_charge_step;
        if (*level < 0) {
            *level = 0;
            quick_fuchikoma_charge_mode = 0;
            quick_fuchikoma_heat = 0;
            quick_fuchikoma_charge_sounded = 0;
        }
        break;
    case 0:
        break;
    }
    if (quick_fuchikoma_heat > 0x300) {
        quick_fuchikoma_charge_mode = 2;
        quick_fuchikoma_charge_step = 0x44;
        quick_fuchikoma_charge_timer = 0;
    }
}

void actors_hit_all(void) {
    Object *obj;

    obj = (Object *) *get_obj_list_actors();
    if (obj->node.next != NULL) {
        do {
            hit_target_masked(obj->index, 1, 0, 0x7CD);
            obj = (Object *) obj->node.next;
        } while (obj->node.next != NULL);
    }
}

extern s32 quick_fuchikoma_health_display;
extern s32 quick_fuchikoma_heat;
void quick_fuchikoma_m8_boss_sequence(Object *obj, ObjHandler *handler);
void quick_fuchikoma_m8_boss_phase2(Object *obj) {
    s32 damage;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    damage = obj_hit_damage(obj->index);
    if (quick_fuchikoma_charge_mode == 3) {
        quick_fuchikoma_heat += damage;
    }
    if (obj->hit_cooldown != 0) {
        obj->hit_cooldown += 0xFF;
    }
    if (damage > 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
        obj->health -= damage;
    }
    obj_hit_clear(obj->index);
    obj_block_lerp(obj, 0);
    meter_set(obj->health, quick_fuchikoma_health_display);
    if (obj->health <= 0) {
        s32 next_phase;

        /* the empty do-while blocks are scheduling barriers that keep the
           stores in the original order; the asm pins the constant 2 to a
           register at the point the original loads it */
        boss_defeated_flag = 1;
        actors_hit_all();
        stage_sound_stop();
        do { } while (0);
        obj->handlers[2].fn = quick_fuchikoma_m8_boss_sequence;
        __asm__("" : "=r"(next_phase) : "0"(2));
        obj->speed = 0;
        obj->vars.enemy.sound = 0;
        obj->vars.quick_fuchikoma_m8_boss.unk_264 = 0;
        do { } while (0);
        obj->unk_17A = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        do { } while (0);
        quick_fuchikoma_charge_mode = next_phase;
        quick_fuchikoma_charge_step = 0x44;
        quick_fuchikoma_charge_timer = 0;
        do { } while (0);
        add_score(obj->score);
        add_kill_count(1);
        meter_set_mode(0);
        set_d_801202C8(0);
    }
}

extern s32 quick_fuchikoma_seq_state;
extern s32 quick_fuchikoma_seq_timer;
extern s16 *quick_fuchikoma_death_pc[];
void quick_fuchikoma_m8_boss_sequence(Object *obj, ObjHandler *handler) {
    s32 *pos;
    s32 *m;
    s32 slot;
    s32 n;
    Script *script = (Script *)obj;
    s32 type;
    s32 r0, r1, r2;
    u16 *state;

    switch (quick_fuchikoma_seq_state) {
    case -2:
        quick_fuchikoma_seq_timer = quick_fuchikoma_seq_timer + 1;
        if (quick_fuchikoma_seq_timer <= 0xF0 && !(obj->ground_flags & 1)) {
            break;
        }
        pos = scratch_alloc(0x10);
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        sound_play_at_units(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, pos);
        sound_play_at_units(SND_PAIR(SND_BOSS_CRASH | SND_GROUP(1), SND_BOSS_CRASH_ALT | SND_GROUP(1)), 0x7F, 0x3C, pos);
        state = &script->state.b;
        *state = 2;
        scratch_top -= 0x10;
        script_jump(script, quick_fuchikoma_death_pc[0], (s32)quick_fuchikoma_m8_boss_data);
        quick_fuchikoma_seq_state = 0x3E;
        break;
    case -1:
        slot = obj->type.unk_0E;
        if (obj_spawn_replacement(obj, slot + model_slot_pchr(*(s32 *)obj->asset)) == 1) {
            obj_free(obj);
        }
        break;
    default:
        n = quick_fuchikoma_seq_state - 1;
        quick_fuchikoma_seq_state = n;
        if (!(n & 7)) {
            pos = scratch_alloc(0x10);
            type = ((n & 0xF) == 0) * 2;
            pos[0] = obj->width * (rand_a_next() - 0x800) / 4096;
            pos[1] = (s16)obj->height * (rand_a_next() - 0x800) / 4096;
            pos[2] = obj->unk_1E8[0] * (rand_a_next() - 0x800) / 4096;
            pos[1] -= (s16)obj->height / 2;
            m = world_matrix_get();
            gte_set_R012(r0, r1, r2, m[0], m[1], m[2]);
            gte_set_R34(r0, r1, m[3], m[4]);
            gte_set_ctrl(TRX, 0);
            gte_set_ctrl(TRY, 0);
            gte_set_ctrl(TRZ, 0);
            gte_load(IR1, pos, 0);
            gte_load(IR2, pos, 4);
            gte_load(IR3, pos, 8);
            gte_rtirtr();
            gte_store(MAC1, pos, 0);
            gte_store(MAC2, pos, 4);
            gte_store(MAC3, pos, 8);
            pos[0] += obj->x >> 12;
            pos[1] += obj->y >> 12;
            pos[2] += obj->z >> 12;
            spawn_effect(pos[0], pos[1], pos[2], type);
            scratch_top -= 0x10;
        }
        break;
    }
}

void quick_fuchikoma_m8_flash_sparks(Object *obj);
void quick_fuchikoma_m8_boss_draw(Object *obj) {
    Vec3 *pos;
    s16 *rot;
    s16 *state;
    s32 value;
    s32 colour;
    s32 progress;

    pos = scratch_alloc(0x10);
    rot = scratch_alloc(8);
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    value = obj_keyframe_value(obj, 0);

    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else if (quick_fuchikoma_charge == 0) {
        colour = 0;
    } else {
        s32 rest;
        s32 done;
        s32 finished;

        progress = quick_fuchikoma_charge;
        value |= 0x8000;
        rest = (0x1000 - progress) >> 5;
        done = progress >> 5;
        finished = (rest | done) == 0;
        colour = (finished << 16) | (done << 8) | rest;
    }

    rot[0] = obj->pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    rot[0] = -rot[0];

    spark_add(pos->x >> 12, pos->y >> 12, pos->z >> 12, rot[1], rot[0], rot[2], value, colour);
    aim_marker_draw(2, (SVECTOR *)&obj->width, pos, (SVECTOR *)rot);

    if (obj->hit != 0) {
        obj->hit = -1;
    }
    state = (s16 *)obj->vars.quick_fuchikoma_m8_boss.unk_248;
    scratch_top -= 0x18;
    if (*state == 1) {
        quick_fuchikoma_m8_flash_sparks(obj);
    }
}

extern s32 quick_fuchikoma_model_asset[3];
void show_moving_object_warning(void) {
    moving_object_slot = model_slot_pchr(quick_fuchikoma_model_asset[0]);
    show_line((s32)"#1Warning!  Warning! Moving object confirmed in the area.\xA1");
}

void obj_init_from_placement(Object *obj, Placement *placement, s32 flags) {
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0x80);
    obj_hit_set_unk08(obj->index, 8);
    obj_hit_set_unk06(obj->index, 3);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj->health = placement->health;
    obj->score = (s16)placement->unk_16;
    obj->damage = placement->unk_18;
    obj->unk_17B = placement->unk_1A;
    obj_set_flags(obj, flags);
    obj->placement = placement;
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}

void obj_place_setup(Object *obj, Placement *place) {
    s32 x, y, z;
    s32 ext;
    s32 height;
    s32 ax, ay, az;
    s16 *rot;

    x = (place->x >> 12) << 12;
    y = (place->y >> 12) << 12;
    z = (place->z >> 12) << 12;
    obj->home_pos[0] = x;
    obj->home_pos[1] = y;
    obj->home_pos[2] = z;
    obj->x = x;
    obj->y = y;
    obj->z = z;
    ay = place->y & 0xFFF;
    ax = place->x & 0xFFF;
    az = place->z & 0xFFF;
    obj->vars.quick_fuchikoma_m8_boss.unused_24C = 0;
    obj->vars.quick_fuchikoma_m8_boss.unk_24E = 0x400;
    obj->vars.quick_fuchikoma_m8_boss.unused_250 = 0;
    obj->rot_angles[0] = ax;
    obj->rot_angles[1] = ay;
    obj->rot_angles[2] = az;
    obj->unk_34[0] = ax;
    obj->unk_34[1] = ay;
    obj->unk_34[2] = az;
    obj_angles_from_matrix(obj);
    rot = obj->rot_angles;
    ext = obj->unk_1E8[0];
    height = (s16)obj->height;
    if (ext < obj->width) {
        ext = obj->width;
    }
    obj->extents[1] = obj->height;
    obj->extents[2] = obj->extents[0] = ext;
    obj->bound_radius = isqrt(length_sq(ext, height, ext));
    obj->unk_3C = 0xF2;
    player_refresh_state_scratch(rot);
}

extern s16 shared_flags[3];
/* Points obj's 0x248 slot at shared_flags and clears all three. */
void obj_bind_shared_flags(Object *obj) {
    s16 *ptr = shared_flags;

    *(s16 **)&obj->vars.snd = ptr;
    *ptr = 0;
    shared_flags[1] = 0;
    shared_flags[2] = 0;
}

extern ScriptCallEntry quick_fuchikoma_m8_boss_calls[];
extern StateEntry quick_fuchikoma_m8_boss_states[];
extern SoundVolume D_801182FC[];
extern s16 *quick_fuchikoma_jump_table[];
extern ObjLinkValue D_80118814;
extern s32 quick_fuchikoma_charge_sounded;
void quick_fuchikoma_m8_boss_update(Object *obj, ObjHandler *handler);
void quick_fuchikoma_m8_boss_set_defaults(void);
void blink_offsets_init(void);
void func_800C4318(void);
/* Spawns the quick fuchikoma (m8 boss) and resets the fight state. */
void stage_sound_reset(void);

s32 quick_fuchikoma_m8_boss_spawn(Placement *place) {
    Object *obj;
    u8 variant;
    s16 *link_value;
    s16 **slot;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    grid_active_set(0);
    place->unk_02 = -1;
    obj->handlers[0].fn = quick_fuchikoma_m8_boss_phase0;
    obj->handlers[1].fn = quick_fuchikoma_m8_boss_update;
    obj->handlers[2].fn = quick_fuchikoma_m8_boss_phase2;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = quick_fuchikoma_m8_boss_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    variant = place->unk_04[1];
    obj->asset = quick_fuchikoma_model_asset;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = quick_fuchikoma_m8_boss_calls;
    obj->state_table = quick_fuchikoma_m8_boss_states;
    obj->sounds = D_801182FC;
    obj->unk_1C6 = 0;
    obj->kind = variant;
    link_value = D_80118814.value;
    obj->script.data = (s32 *)quick_fuchikoma_jump_table;
    obj->script.unk_0A = 0;
    obj->script.pc = link_value;
    slot = quick_fuchikoma_m8_boss_data;
    script_start((Script *)obj, *slot, (s32)slot);
    obj_init_from_placement(obj, place, 0x25);
    obj_set_part_bounds(obj, 0, 0x1000);
    obj->accel_y = 0x2000;
    obj->speed_accel = 0x1000;
    obj->vy = 0;
    obj->speed = 0;
    obj->vars.quick_fuchikoma_m8_boss.speed_limit = 0x8000;
    obj->vars.quick_fuchikoma_m8_boss.unused_270 = 0;
    obj->vars.quick_fuchikoma_m8_boss.unused_274 = 0;
    obj->vars.quick_fuchikoma_m8_boss.unused_26C = 0;
    obj->vars.quick_fuchikoma_m8_boss.unk_264 = 0;
    obj->vars.turn.bearing = 0;
    obj->vars.turn.yaw_offset = obj->yaw;
    obj_place_setup(obj, place);
    obj_bind_shared_flags(obj);
    quick_fuchikoma_m8_boss_set_defaults();
    blink_offsets_init();
    func_800C4318();
    stage_sound_reset();
    func_800BEC40();
    quick_fuchikoma_health_display = obj->health;
    meter_set(obj->health, obj->health);
    meter_set_mode(1);
    boss_defeated_flag = 0;
    quick_fuchikoma_seq_timer = 0;
    quick_fuchikoma_seq_state = -2;
    quick_fuchikoma_charge = 0;
    quick_fuchikoma_charge_step = 0;
    quick_fuchikoma_charge_mode = 0;
    quick_fuchikoma_charge_timer = 0;
    quick_fuchikoma_heat = 0;
    quick_fuchikoma_charge_sounded = 0;
    stage_set_offset_x(-0x840);
    return 1;
}

/* Distance from the object to the player. The object's script cursor reads a
   (threshold, index) pair; when the distance is at most the threshold, the cursor
   jumps to the entry at index in the object's table. */
void script_jump_if_player_close(Object *obj) {
    s32 *player = player_position();
    s32 dist = isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12)));
    s16 *cursor = obj->script.pc;
    s32 threshold;
    s32 index;

    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold >= dist) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}
