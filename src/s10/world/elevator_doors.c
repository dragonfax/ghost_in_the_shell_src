/* elevator_doors: one of s10's own original source files (scripts/objmap.py); part of src/s10/main.c's unit, included there. */

extern s8 door_table[];
extern s32 door_light_base;
void door_link_entries(void);
void door_table_init(void) {
    DoorState *r = (DoorState *)door_table;
    s32 i = 0;

    door_light_base = point_base;
    do {
        i++;
        r->active = 1;
        r->unk1 = 0;
        r->unk2 = 0;
        r->scale = 0x1000;
        r->value = 0xAA;
        r++;
    } while (i < 11);
    door_link_entries();
}

extern s32 door_shape_origin;
extern s16 door_extents_table[];
extern s32 door_shape_rows[];
void elevator_door_phase0(Object *obj);
void s10_elevator_door_update(Object *obj);
void elevator_door_phase2(Object *obj);
void elevator_door_draw(Object *obj);
s32 elevator_doors_spawn(Placement *placement) {
    Object *obj;
    s32 i;
    s32 kind;
    s32 link;
    s32 z;

    if (get_obj_free_count() < 2) {
        return 0;
    }
    kind = (s16)placement->health;
    i = 0;
    if ((u32)kind >= 11) {
        return 0;
    }
    do {
        obj = obj_new();
        list_insert_after((Node *)get_obj_list_b(), &obj->node);
        obj->handlers[0].fn = elevator_door_phase0;
        obj->handlers[1].fn = s10_elevator_door_update;
        obj->handlers[2].fn = elevator_door_phase2;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = elevator_door_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->x = (placement->x >> 12) << 12;
        obj->y = (placement->y >> 12) << 12;
        z = placement->z;
        obj->placement = placement;
        obj->vars.elevator_doors.door_index = kind;
        obj->vars.elevator_doors.part_index = i;
        obj->z = (z >> 12) << 12;
        obj->vars.elevator_doors.shape_row = door_shape_rows[kind];
        if (i != 1) {
            link = -1;
        } else {
            link = placement->unk_16;
        }
        obj->vars.elevator_doors.grid_entry = link;
        do {
        } while (0);
        obj_clear_block54(obj->unk_A4);
        model_part_extents_max(door_shape_origin + *(s16 *)((u8 *)door_extents_table + ((i << 4) + (obj->vars.elevator_doors.shape_row << 5))),
                               0x1000, obj->unk_A4 + 0x34);
        i++;
        obj->solid_id = solid_alloc();
        obj->unk_A4[1] = 4;
        obj->unk_A4[0] = obj->index;
    } while (i < 2);
    return 1;
}

extern s8 door_range_x_table[];
extern s8 door_range_z_table[];
void grid_entry_activate(s32 index);
s32 grid_entry_is_clear(s32 index);
void elevator_door_phase0(Object *obj) {
    s16 kind;
    s32 *pos;
    s32 dx;
    s32 dz;
    s32 range_x;
    s32 range_z;
    u8 *flags;
    s32 off;

    kind = obj->vars.elevator_doors.part_index;
    if (kind == 1) {
        flags = &door_table[obj->vars.elevator_doors.door_index * 8];
        pos = player_position();
        dx = pos[0] - (obj->x >> 12);
        dz = pos[2] - (obj->z >> 12);
        off = ((s16)obj->vars.elevator_doors.part_index << 4) + ((s16)obj->vars.elevator_doors.shape_row << 5);
        range_z = *(s16 *)(door_range_z_table + off);
        range_x = *(s16 *)(door_range_x_table + off);
        if (ABS(dz) < range_z) {
            if (ABS(dx) < range_x) {
                if (flags[0] != 0) {
                    if (flags[1] != kind) {
                        sound_attach(sound_start(SND_ELEVATOR_DOOR_MOVE | SND_GROUP(1), 0x60, 0, 0), &obj->x, 0);
                    }
                    flags[1] = 1;
                    if (grid_entry_is_clear(obj->vars.elevator_doors.grid_entry) != 0) {
                        *(s16 *)&obj->vars.elevator_doors.grid_entry = -1;
                        return;
                    }
                    grid_entry_activate(obj->vars.elevator_doors.grid_entry);
                    *(s16 *)&obj->placement->unk_16 = -1;
                    return;
                }
            }
        }
        if (obj->vars.elevator_doors.shape_row == 2) {
            return;
        }
        if (flags[1] != 0) {
            sound_attach(sound_start(SND_ELEVATOR_DOOR_MOVE | SND_GROUP(1), 0x60, 0, 0), &obj->x, 0);
        }
        flags[1] = 0;
    }
}

void s10_elevator_door_update(Object *obj) {
    DoorFadeEntry *e;
    s32 step;

    if ((s16)obj->vars.elevator_doors.part_index == 1) {
        e = &((DoorFadeEntry *)door_table)[obj->vars.elevator_doors.door_index];
        step = e->step;
        if (e->active && e->reverse) {
            step = -step;
        }
        e->level += step;
        e->level = MAX(MIN(e->level, 0x1000), 0);
    }
}

extern ElevatorDoorShape elevator_door_shapes[3][2];
extern s32 door_shape_origin;
/* Elevator door object, phase 2. The door's open flag comes from a position
 * lookup; a closed door frees the object, an open one adds its solid and
 * places it in the obj+0xA4 block. */
void elevator_door_phase2(Object *obj) {
    u8 *block;
    DoorState *door;
    ElevatorDoorShape *shape;
    Placement *placement;
    s16 pts[12]; /* pts[0,1] and pts[4,5] are used; 12 keeps the 0x48 frame */
    s16 scale;
    s32 solid;
    u8 flags;

    block = obj->unk_A4;
    door = &((DoorState *)door_table)[obj->vars.elevator_doors.door_index];
    shape = &elevator_door_shapes[(s16)obj->vars.elevator_doors.shape_row][(s16)obj->vars.elevator_doors.part_index];
    if ((s16)obj->vars.elevator_doors.part_index == 1) {
        door->unk2 = cam_range_check_alt(obj->x >> 12, obj->y >> 12, obj->z >> 12);
    }
    if (door->unk2 == 0) {
        if ((s16)obj->vars.elevator_doors.part_index == 1) {
            placement = obj->placement;
            flags = placement->unk_04[0];
            placement->unk_02 = 0;
            placement->unk_04[0] = (flags & 0xFC) | 2;
        }
        solid_free(obj->solid_id);
        obj_free(obj);
        return;
    }
    scale = door->scale;
    if (scale <= 0) {
        return;
    }
    pts[4] = scale;
    pts[5] = 0x1000 - scale;
    pts[0] = shape->unk_04 + door_shape_origin;
    pts[1] = shape->unk_06 + door_shape_origin;
    /* the original sets only the first two arguments of solid_add */
    solid = ((s32 (*)(s16 *, s16 *))solid_add)(pts, &pts[4]);
    *(s32 *)(block + 0x1C) = obj->x + (shape->dx << 12);
    *(s32 *)(block + 0x20) = obj->y - 0x1000;
    *(s32 *)(block + 0x24) = obj->z + (shape->dz << 12);
    solid_setup_scratch(obj->solid_id, block, (s16)solid, 0x1000);
}

extern ElevatorDoorShape elevator_door_shapes[3][2];
extern u8 door_scale_table[];
void grid_entry_spawn_fx(s32 index);
void elevator_door_draw(Object *obj) {
    ElevatorDoorShape *shape;
    s32 x, y, z;
    s32 level;
    s32 base;
    s32 scale;

    base = door_light_base;
    shape = &elevator_door_shapes[(s16)obj->vars.elevator_doors.shape_row][(s16)obj->vars.elevator_doors.part_index];
    x = obj->x >> 12;
    z = obj->z >> 12;
    {
        register s32 slot asm("$3") = (s16)obj->vars.elevator_doors.door_index * 8;
        scale = *(s16 *)&door_scale_table[slot];
    }
    y = obj->y >> 12;
    level = pchr_blend(base + shape->unk_00, base + shape->unk_02, scale, 1);
    spark_add(x + shape->dx, y, z + shape->dz, 0, 0, 0, level, 0);
    grid_entry_spawn_fx(obj->vars.elevator_doors.grid_entry);
}

extern s8 door_table[];
void door_set_active(u32 index, s8 value) {
    if (index < 0xB) {
        door_table[index * 8] = value;
    }
}

extern u8 door_scale_table[];
s16 door_get_scale(u32 index) {
    return (index < 0xBU) ? *(s16 *)&door_scale_table[index * 8] : 0x1000;
}

/* Returns the index of the first row whose key equals `key`, or -1.
 * The rows are 8-byte {key, value} pairs ending with a -1 key. */
s32 area_row_find(void *key) {
    s32 i;
    s32 *table;
    s32 *row;

    table = (s32 *)((AreaData *)get_area_entry())->rows;
    if (*table != -1) {
        s32 end;
        i = 0;
        end = -1;
        row = table;
        do {
            if (*row == (s32)key) {
                return i;
            }
            row += 2;
            i++;
        } while (*row != end);
    }
    return -1;
}

s32 grid_find_in_box(GridBox *box, s32 skip_kind) {
    GridEntry *list;
    s32 count;
    s32 i;
    s32 x, y, z;
    s32 kind;
    s32 inside;

    list = grid_entry(0);
    count = grid_count();
    for (i = 0; i < count; i++, list++) {
        kind = list->kind;
        if (kind < 0x40 && kind != skip_kind) {
            x = list->x >> 12;
            y = list->y >> 12;
            z = list->z >> 12;
            inside = in_box_800C0D44(box, x, y, z);
            if (inside) {
                return i;
            }
        }
    }
    return -1;
}

extern ScanEntry door_area_key; /* the elevator doors' loader step: area rows key on its address */
extern s32 door_shape_rows[];
s32 area_row_find(void *table);
void door_link_entries(void) {
    GridEntry *e = grid_entry(0);
    s32 count = grid_count();
    s32 kind = area_row_find(&door_area_key);
    s32 *box = scratch_alloc(0x18);
    s32 i;
    s32 x;
    s32 y;
    s32 z;
    s32 slot;
    GridEntry *spawned;

    for (i = 0; i < count; i++, e++) {
        if (e->kind != kind) {
            continue;
        }
        *(s16 *)&e->unk_14[2] = -1;
        if (door_shape_rows[*(s16 *)&e->unk_14[0]] != 2) {
            continue;
        }
        x = e->x >> 12;
        y = e->y >> 12;
        z = e->z >> 12;
        box[2] = y - 0xF0;
        box[3] = y + 0x90;
        box[4] = z - 0x90;
        box[5] = z + 0x90;
        if (x < 0x630) {
            box[0] = x - 0x1B0;
            box[1] = x;
        } else {
            box[0] = x;
            box[1] = x + 0x1B0;
        }
        slot = grid_find_in_box((GridBox *)box, kind);
        if (slot >= 0) {
            *(s16 *)&e->unk_14[2] = slot;
            spawned = grid_entry(slot);
            spawned->flags = (grid_entry(slot)->flags & 0xFC) | 2;
        }
    }
    scratch_top -= 0x18;
}

void grid_entry_activate(s32 index) {
    GridEntry *entry;

    if (index >= 0) {
        entry = grid_entry(index);
        entry->flags = (grid_entry(index)->flags & 0xFC) | 1;
    }
}

s32 grid_entry_is_clear(s32 index) {
    u8 flags;
    u32 state;

    if (index < 0) {
        return 1;
    }
    flags = grid_entry(index)->flags;
    state = flags & 3;
    if (flags & 8) {
        return state < 2U;
    }
    return state == 0;
}

void grid_entry_spawn_fx(s32 index) {
    GridEntry *entry;

    if (index >= 0) {
        entry = grid_entry(index);
        req_queue_push(entry->x >> 12, entry->y >> 12, entry->z >> 12, (entry->flags & 8) ? 0 : 2);
    }
}
