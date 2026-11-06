/* exit_doors: one of the original source files (scripts/objmap.py); s01, s06, s07, s10, s11. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

#if STAGE == 1
s32 *sound_position_for_slot(s32 n) {
    s32 *out;
    s32 offset = (n - 1) << 1;

    sound_closest_point((Vec3 *)(sound_slot_points + offset), (Vec3 *)(sound_slot_points + 1 + offset), (Vec3 *)(out = &sound_slot_pos));
    *out <<= 12;
    sound_slot_pos_y <<= 12;
    sound_slot_pos_z <<= 12;
    return out;
}

/* Every so many steps plays sound 0x51E2 at a random position. */
void ambient_sound_tick(void) {
    s32 pos[3];

    ambient_sound_timer--;
    if (ambient_sound_timer <= 0) {
        ambient_sound_timer = rand_a_next() / 64 + 0x40;
        pos[0] = rand_a_next() * 0x5460 / 4096 - 0x2580;
        pos[1] = rand_a_next() * 0x7D0 / 4096 + 0x1F4;
        pos[2] = -0x300C;
        sound_play_at_units(SND_SEAGULL | SND_GROUP(2), 0x28, 0x3C, pos);
    }
}

void key_progress_update();
/* Stage init: clears four state words, spawns the controller object with
 * handlers 2 and 3 set, starts two sounds, and shows the "Pursue the target." line. */
s32 stage_init_pursue(void) {
    Object *obj;

    key_codes_complete_flag = 0;
    stage_exit_flag = 0;
    key_codes_acquired = 0;
    warehouse_hint_timer = 0;
    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_b(), &obj->node);
    obj->handlers[2].fn = key_progress_update;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *))stage_pursue_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    mission_timer_set(0x176F);
    sound_zone_set_enabled(0, 0);
    rec_set_flags(0x58, 0);
    stage_camera_start();
    sound_attach(sound_start(SND_PURSUE_AMBIENCE_LOOP | SND_HELD | SND_GROUP(1), 0x7F, 0, 0), (void *)1, (void (*)())sound_position_for_slot);
    sound_attach(sound_start(SND_PURSUE_AMBIENCE_LOOP | SND_HELD | SND_GROUP(1), 0x7F, 0x78, 0), (void *)2, (void (*)())sound_position_for_slot);
    ambient_sound_timer = 0x80;
    target_select(1);
    pursue_flag_set(1);
    show_line((s32)"Pursue the target.\xA1");
    set_area_warnings(1);
    return 1;
}

/* When flag 0x10 of pad1_pressed is set, toggle state 0 (scene_model_get_flag) and pass the new value to the
 * three setters. */
void debug_toggle_rec(void) {
    s32 off;

    if (pad1_pressed & 0x10) {
        off = scene_model_get_flag(0) == 0;
        scene_model_set_flag(0, off);
        rec_set_value(0, off);
        rec_set_on(0, off);
    }
}

void debug_draw_toggle(void) {
    if ((pad1_pressed & 0x10) && (pad1.held & 0x100)) {
        set_draw_enabled(get_draw_enabled() == 0);
    }
}

/* Steps a 6-entry selection (0..5) when the 0x10 bit of pad1_pressed is set. */
void debug_step_selection(void) {
    if (pad1_pressed & 0x10) {
        s32 index = target_get_index() + 1;

        if (index >= 6) {
            index = 0;
        }
        target_select(index);
    }
}

void key_progress_update(void) {
    GridEntry **table;
    s32 entry_count;
    s32 done_count;
    s32 i;
    s32 cam_x;
    s32 cam_y;
    s32 cam_z;

    ambient_sound_tick();
    stage_camera_fade_in_step();
    done_count = 0;
    table = get_key_table();
    entry_count = get_key_count();
    for (i = 0; i < entry_count; i++) {
        if ((table[i]->flags & 3) == 3) {
            done_count++;
        }
    }

    if (key_codes_acquired < done_count) {
        key_codes_acquired = done_count;
        if (done_count == entry_count) {
            key_codes_complete_flag = 1;
            show_line((s32)"#1All key codes acquired.\xA1|2\0\0\0");
            show_line((s32)"Proceed to the warehouse!\xA1\0");
            sound_start(SND_ALL_KEY_CODES_ACQUIRED | SND_VOICE_FLAG, 0x40, 0, 0);
            msg_show_slot(0, -1);
            sound_zone_set_enabled(0, 1);
            target_select(5);
            cam_set_target(0, 0, 0x226F);
            pursue_flag_set(0);
        } else {
            show_line((s32)"#2Key code acquired.\xA1|2");
            sound_start(SND_KEY_CODE_ACQUIRED | SND_VOICE_FLAG, 0x40, 0, 0);
            msg_show_slot(5, 0xB4);
            switch (key_codes_acquired) {
            case 1:
                show_line((s32)"3 more key codes.\xA1\0");
                break;
            case 2:
                show_line((s32)"2 more key codes.\xA1\0");
                break;
            default:
                show_line((s32)"1 more key code.\xA1\0\0");
                break;
            }
        }
    }

    eng_set_mode(0);
    set_enemies_left(entry_count - key_codes_acquired);
    if (stage_exit_flag == 0 && key_codes_acquired == entry_count) {
        cam_x = cam_pos >> 12;
        if (cam_x >= -0x28A) {
            if (cam_x < 0x28B) {
                cam_y = cam_pos_y >> 12;
                if (cam_y >= 0) {
                    if (cam_y <= 0) {
                        cam_z = cam_pos_z >> 12;
                        if (cam_z >= 0x1EDC) {
                            if (cam_z < 0x2329) {
                                stage_exit_flag = 1;
                                set_d_801202C8(0);
                                set_stage_end(2);
                                return;
                            }
                        }
                    }
                }
            }
        }
        warehouse_hint_timer++;
        if (warehouse_hint_timer >= 0x4B1) {
            show_line((s32)"Repeat - Proceed tothe warehouse!\xA1");
            warehouse_hint_timer = 0;
        }
    }
}

/* The boss's model files: data tables point to them by address. */
const char file_bos1_tp1_clt[] = "bos1_tp1.clt";
const char file_bos1_tp0_clt[] = "bos1_tp0.clt";
const char file_bos1_ch0_clt[] = "bos1_ch0.clt";
const char file_bos1_tp1_xs3[] = "bos1_tp1.xs3";
const char file_bos1_tp0_xs3[] = "bos1_tp0.xs3";
const char file_bos1_ch1_vx1[] = "bos1_ch1.vx1";
const char file_bos1_ch0_vx1[] = "bos1_ch0.vx1";
const char file_bos1_ch1_cb4[] = "bos1_ch1.cb4";
const char file_bos1_ch0_cb4[] = "bos1_ch0.cb4";

extern s32 key_codes_complete_flag;

void stage_pursue_draw(void) {
    if (key_codes_complete_flag != 0) {
        req_queue_push(0, 0, 0x226F, 4);
    }
}

/* Initialises the sound zones (one in S01): enabled, level 0x1000, fade step 0x66. */
void sound_zones_init(void) {
    SoundZone *zone;
    s32 i;

    zone = sound_zones;
    i = 0;
    D_8011FF00 = point_base;
    do {
        i++;
        zone->enabled = 1;
        zone->near = 0;
        zone->level = 0x1000;
        zone->step = 0x66;
        zone++;
    } while (i <= 0);
}

s32 key_code_exit_doors_spawn(Placement *placement) {
    Object *obj;
    s16 health;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    health = placement->health;
    if (health < 0 || health > 0) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_b(), &obj->node);
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) key_code_exit_doors_phase0;
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) key_code_exit_doors_update;
    obj->handlers[2].fn = (void (*)(Object *, ObjHandler *)) key_code_exit_doors_phase2;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) key_code_exit_doors_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = ((s32) placement->x >> 12) << 12;
    obj->y = ((s32) placement->y >> 12) << 12;
    obj->z = ((s32) placement->z >> 12) << 12;
    obj->placement = placement;
    obj->vars.key_code_exit_doors.sound_zone_index = placement->health;
    obj->vars.key_code_exit_doors.sound_channel = 0;
    return 1;
}

/* Plays sound 0xB1E3 from the object when the player enters or leaves its range (|dz| < 2000, |dx| < 1400). */
void key_code_exit_doors_phase0(Object *obj) {
    SoundZone *rec = &sound_zones[obj->vars.key_code_exit_doors.sound_zone_index];
    s32 *pos = player_position();
    s32 dx = pos[0] - (obj->x >> 12);
    s32 dz = pos[2] - (obj->z >> 12);

    if (abs(dz) < 2000 && abs(dx) < 1400 && rec->enabled != 0) {
        if (rec->near == 0 && obj->vars.key_code_exit_doors.sound_channel == 0) {
            obj->vars.key_code_exit_doors.sound_channel = sound_start(SND_EXIT_DOOR_LOOP | SND_HELD | SND_GROUP(1), 0x7F, 0, 0);
            sound_attach(obj->vars.key_code_exit_doors.sound_channel, &obj->x, 0);
        }
        rec->near = 1;
        return;
    }
    if (rec->near == 1 && obj->vars.key_code_exit_doors.sound_channel == 0) {
        obj->vars.key_code_exit_doors.sound_channel = sound_start(SND_EXIT_DOOR_LOOP | SND_HELD | SND_GROUP(1), 0x7F, 0, 0);
        sound_attach(obj->vars.key_code_exit_doors.sound_channel, &obj->x, 0);
    }
    rec->near = 0;
}

void key_code_exit_doors_update(Object *obj) {
    SoundZone *f = &sound_zones[obj->vars.key_code_exit_doors.sound_zone_index];
    s32 step = f->step;

    if (f->enabled != 0 && f->near != 0) {
        step = -step;
    }
    f->level += step;
    f->level = MAX(MIN(f->level, 0x1000), 0);
    if (f->level == 0 || f->level == 0x1000) {
        if (obj->vars.key_code_exit_doors.sound_channel != 0) {
            sound_stop(obj->vars.key_code_exit_doors.sound_channel);
            obj->vars.key_code_exit_doors.sound_channel = 0;
        }
    }
}

void key_code_exit_doors_phase2(Object *obj) {
    GridEntry *entry;
    s32 unused[5]; /* stack frame of the original */

    if (cam_range_check_alt(obj->x >> 12, obj->y >> 12, obj->z >> 12) == 0) {
        entry = (GridEntry *)obj->placement;
        entry->delay = 0;
        entry->flags = (entry->flags & 0xFC) | 2;
        obj_free(obj);
    }
}

void key_code_exit_doors_draw(Object *obj) {
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    s16 value;
    s32 n;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    value = pchr_blend(D_8011FF00 + 0x59, D_8011FF00 + 0x58, sound_zones[obj->vars.key_code_exit_doors.sound_zone_index].level, 1);
    n = spark_count;
    list = &spark_list;
    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = 0;
        tail = spark_list_tail;
        spark_list_tail = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
}

/* Set the value of entry `index` of a one-entry table. */
void sound_zone_set_enabled(s32 index, s32 value) {
    if (index >= 0 && index < 1) {
        sound_zones[index].enabled = value;
    }
}

s32 sound_zone_get_level(s32 index) {
    s32 result = 0x1000;

    if (index >= 0) {
        if (index <= 0) {
            result = sound_zones[index].level;
        }
    }
    return result;
}

/* Advances the s32 at 0x20 (unk_1C.unk_04) by 2. */
void obj_script_skip_operand(Object *obj) {
    obj->script.pc++;
}
#endif

#if STAGE == 6
/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is at least
 * `threshold` from the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void obj_script_jump_if_far(Object *obj) {
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
    if (dist < threshold) {
        return;
    }
    obj->script.pc = ((s16 **)obj->script.data)[index];
}
#endif

#if STAGE == 1
/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void func_800C02FC(Object *obj) {
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
/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is at least
 * `threshold` from the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void obj_script_jump_if_far(Object *obj) {
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
    if (dist < threshold) {
        return;
    }
    obj->script.pc = ((s16 **)obj->script.data)[index];
}
#endif

#if STAGE != 10 && STAGE != 11
/* Script op (step, index): turns obj toward the player by at most step; once the remaining turn is
 * under step, jumps to table entry index. */
void script_turn_to_player_jump(Object *obj) {
    s16 *cursor;
    s32 raw;
    s32 index;
    s16 step;
    s32 *player;
    s32 target;
    s32 yaw;
    s32 diff;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    raw = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    step = ABS(raw);
    player = player_position();
    target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    yaw = obj->yaw;
    yaw &= 0xFFF;
    if (yaw >= 0x800) {
        yaw -= 0x1000;
    }
    diff = angle_approach(yaw, target, step) - yaw;
    diff &= 0xFFF;
    if (diff >= 0x800) {
        diff -= 0x1000;
    }
    if (ABS(diff) < step) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op: if the op equals obj->unk_F8, jump to the table entry given by the next word. */
void script_case_match(Object *obj) {
    s16 op = obj_read_s16(obj);
    s16 target = obj_read_s16(obj);

    if (op == obj->script_flag) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}
#endif

#if STAGE != 6 && STAGE != 7
/* Reads a halfword from the object's data cursor (+0x20), advances the cursor by 2, and stores the value at +0x250. */
void obj_script_read_u16_var(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->vars.h.unk_250 = *cursor;
}
#endif
