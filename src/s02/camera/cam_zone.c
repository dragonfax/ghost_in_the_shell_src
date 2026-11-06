/* cam_zone: one of s02's own original source files (scripts/objmap.py); part of src/s02/main.c's unit, included there. */

extern s32 cam_zone_index;
extern s32 cam_zone_exit_flag;
extern SoundSegmentList cam_zone_sound_owner_a;
extern SoundSegmentList cam_zone_sound_owner_b;
extern SoundSegmentList cam_zone_sound_owner_c;
extern PathPoint cam_zone_path[];
void cam_zone_setup(void);
void cam_zone_phase2(Object *obj, ObjHandler *handler);
void cam_zone_draw(Object *obj, ObjHandler *handler);
s32 cam_zone_spawn(void) {
    Object *obj;
    s32 ok;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_b(), &obj->node);
        obj->handlers[2].fn = cam_zone_phase2;
        obj->handlers[3].fn = cam_zone_draw;
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
        cam_zone_index = -1;
        cam_zone_exit_flag = 0;
        cam_zone_setup();
        sound_start_attached(0xD200, 0x7F, &cam_zone_sound_owner_a);
        sound_start_attached(SND_WARNING_ALARM_LOOP | SND_HELD | SND_GROUP(2), 0x7F, &cam_zone_sound_owner_b);
        sound_start_attached(0xD205, 0x7F, &cam_zone_sound_owner_c);
        cam_path_set(0x1D, (s32) cam_zone_path);
        target_select(5);
        ok = 1;
    } else {
        ok = 0;
    }
    return ok;
}

extern s32 player_ground_id;
extern s32 player_flag8_obj_ids[];
/* Sets player mode flag 0x8 when the current object's id (s16 at +6) is in
   player_flag8_obj_ids, a list of ids terminated by a negative entry; clears it otherwise. */
void player_flag8_by_obj_id(void) {
    s32 *cursor;
    s32 found;
    s32 id;
    s16 *obj;
    s32 key;

    found = 0;
    obj = (s16 *)rec_table_word_addr(player_ground_id);
    if (obj != NULL) {
        cursor = player_flag8_obj_ids;
        id = *cursor;
        key = obj[3];
        while (id >= 0) {
            if (id == key) {
                found = 1;
                break;
            }
            cursor++;
            id = *cursor;
        }
    }
    if (found != 0) {
        set_player_mode_flags(player_mode_flags() | 0x8);
    } else {
        set_player_mode_flags(player_mode_flags() & ~0x8);
    }
}

extern RangeBox cam_zone_boxes[5];
/* Returns the index of the first box that contains the camera position, or -1. */
s32 cam_zone_find(void) {
    s32 i;
    RangeBox *box;
    s32 x, y, z;

    x = VEC_80139584.x >> 12;
    y = VEC_80139584.y >> 12;
    z = VEC_80139584.z >> 12;

    box = cam_zone_boxes;
    for (i = 0; i < 5; i++, box++) {
        if (x < box->min_x || box->max_x < x) {
            continue;
        }
        if (y < box->min_y || box->max_y < y) {
            continue;
        }
        if (z < box->min_z || box->max_z < z) {
            continue;
        }
        return i;
    }
    return -1;
}

extern s16 cam_zone_night_table[];
/* Scans the 4-entry table cam_zone_night_table (8 bytes per entry: key_a, key_b, flag, pad).
 * When both keys match, passes the entry's flag to set_night_vision_flag. */
void cam_zone_transition_flag(s32 key_a, s32 key_b) {
    s32 i;
    s16 *key;
    s16 *val;

    if (key_a < 0 || key_b < 0) {
        return;
    }
    i = 0;
    key = cam_zone_night_table;
    val = key + 2;
    do {
        if (*key == key_a && val[-1] == key_b) {
            set_night_vision_flag(val[0]);
            return;
        }
        i++;
        val += 4;
        key += 4;
    } while (i < 4);
}

extern s32 cam_zone_shade_rec_ids[];
void cam_zone_shade_recs(void) {
    s32 *p;
    s32 size;
    s32 i;

    size = 0x1000;
    if (func_800C5048() < 0x800) {
        size = 0x800;
    }
    p = cam_zone_shade_rec_ids;
    i = *p;
    if (i >= 0) {
        do {
            rec_set_rgb(i, size, size, size);
            p++;
            i = *p;
        } while (i >= 0);
    }
}

extern s32 cam_zone_index;
extern s32 cam_zone_exit_flag;

void cam_zone_phase2(Object *obj, ObjHandler *handler) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;

    cam_zone_fade_step();
    temp_s0 = cam_zone_index;
    temp_v0 = cam_zone_find();
    cam_zone_index = temp_v0;
    cam_zone_transition_flag(temp_s0, temp_v0);
    player_flag8_by_obj_id();
    cam_zone_shade_recs();
    if (cam_zone_exit_flag == 0) {
        temp_v0_2 = cam_zone_index == 4;
        cam_zone_exit_flag = temp_v0_2;
        if (temp_v0_2 != 0) {
            set_stage_end(2);
        }
    }
}

extern s32 cam_zone_x0;
extern s32 cam_zone_x1;
extern s32 cam_zone_y;
extern s32 cam_zone_z0;
extern s32 cam_zone_z1;
/* Calls req_queue_push with the midpoints of the X and Z pairs and the Y value cam_zone_y. */
void cam_zone_draw(Object *obj, ObjHandler *handler) {
    cam_path_update();
    req_queue_push((cam_zone_x0 + cam_zone_x1) / 2, cam_zone_y, (cam_zone_z0 + cam_zone_z1) / 2, 4);
}
