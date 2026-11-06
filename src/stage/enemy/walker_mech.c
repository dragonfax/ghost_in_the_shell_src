/* walker_mech: one of the original source files (scripts/objmap.py); s05, s07. */

#include "stage.h"

void walker_mech_phase0(Object *obj) {
    if (obj->health > 0) {
        obj_link_script_run();
    }
}

/* Turns the yaw toward the halfword at 0x250 by up to 0x30 per step. */
void obj_turn_to_target_yaw(Object *obj) {
    obj->yaw = angle_approach(obj->yaw, *(s16 *)((u8 *)obj + 0x250), 0x30);
}

/* enemy_wall_steer with the speed limit at 0x24C, probes at +-0x12C and obj_turn_to_target_yaw. */
void walker_mech_move(Object *obj) {
    s32 hold = 4;
    ObjHandler *handler = &obj->handlers[1];
    s32 step = 0x10;
    s32 *block;
    s32 *slot;
    s32 *hit;
    s32 speed;
    register s32 limit asm("$4");
    s32 clamped;
    s32 flags;
    s32 mode;
    s32 hits;
    s32 blocked;
    s32 angle;
    s32 i;

    speed = obj->speed + obj->speed_accel;
    obj->speed = speed;
    limit = *(s32 *)obj->vars.enemy.unk_24C;
    flags = obj->ground_flags;
    clamped = CLAMP_HI(speed, limit) < 0 ? 0 : CLAMP_HI(speed, limit);
    obj->speed = clamped;

    if (flags & 0x3C) {
        mode = 3;
    } else {
        mode = 0;
        if (obj->handlers[1].timer == 0) {
            block = scratch_alloc(0x30);
            slot = block + 4;
            hit = block + 8;
            block[0] = obj->x >> 12;
            block[1] = obj->y >> 12;
            block[2] = obj->z >> 12;
            block[1] -= 0x69;
            angle = obj->yaw - 0x12C;
            hits = 0;
            for (i = 0; i < 2; i++) {
                slot[2] = 0x190;
                slot[0] = 0;
                slot[1] = 0;
                rotate_xz_twice(angle, 0, slot, slot + 1, slot + 2);
                slot[0] += block[0];
                slot[1] += block[1];
                slot[2] += block[2];
                blocked = trace_world(8, 0x64, block, slot, hit);
                hits <<= 1;
                if (blocked) {
                    hits |= 1;
                }
                angle += 0x258;
            }
            scratch_top -= 0x30;
            mode = hits;
            handler->timer = hold;
        }
    }

    switch (mode) {
    case 0:
        if (handler->turn_timer == 0) {
            obj_turn_to_target_yaw(obj);
            break;
        }
        goto spin;
    case 1:
        if (handler->turn_timer == 0) {
            obj->unk_226[0] = -0x10;
        }
        break;
    case 2:
        if (handler->turn_timer == 0) {
            obj->unk_226[0] = step;
        }
        break;
    case 3:
        if (handler->turn_timer == 0) {
            handler->turn_timer = 0x1E;
        }
    spin:
        obj->yaw += obj->unk_226[0];
        break;
    }

    fly_move(obj->yaw, obj->speed >> 12, &obj->vz, &obj->vx);

    if (handler->turn_timer > 0) {
        handler->turn_timer--;
    }
    if (handler->timer > 0) {
        handler->timer--;
    }
}

s32 is_player_near_placement(Object *obj) {
    s32 *pos = player_position();
    u8 *base = (u8 *)obj->placement;

    if (isqrt(length_sq(pos[0] - (*(s32 *)(base + 0x28) >> 12), pos[1] - (*(s32 *)(base + 0x2C) >> 12),
                        pos[2] - (*(s32 *)(base + 0x30) >> 12))) < 0x9C5) {
        s32 *pos2 = player_position();
        if ((obj->y >> 12) - 0x1B0 < pos2[1]) {
            return 1;
        }
        if (player_landed != 1) {
            return 1;
        }
    }
    return 0;
}

void walker_mech_move(Object *obj);
static inline PlacedTarget *patrol_home(Object *obj) {
    return (PlacedTarget *)obj->placement;
}
static inline s32 patrol_aimed_at(s32 yaw0, s32 yaw1, s32 pitch0, s32 pitch1) {
    if (ANG_ABS_DIFF(yaw0, yaw1) < 0x80 && ANG_ABS_DIFF(pitch0, pitch1) < 0x155) {
        return 1;
    }
    return 0;
}
static inline s32 patrol_player_dist(Object *obj) {
    s32 *pos = player_position();

    return isqrt(length_sq(pos[0] - (obj->x >> 12), pos[1] - (obj->y >> 12), pos[2] - (obj->z >> 12)));
}
void walker_mech_patrol(Object *obj) {
    PlacedTarget *place;
    s32 range;
    s32 px;
    s32 offset_x;
    s32 yaw;
    s32 pitch;
    s32 ahead;
    s32 view_yaw;
    s32 view_pitch;

    switch (obj->unk_242) {
    case 0:
        if (is_player_near_placement(obj)) {
            if (patrol_player_dist(obj) < 0x6D7) {
                obj->unk_242 = 1;
            }
        }
        if ((s16)--obj->vars.h.unk_258 > 0) {
            break;
        }
        obj->vars.h.unk_258 = 0x5A;
        place = (PlacedTarget *)obj->placement;
        range = 0x1388;
        offset_x = rand_a_next() * range / 0x1000 - 0x9C4;
        px = place->x + offset_x;
        {
            register s32 offset_z asm("$3") = rand_a_next() * range / 0x1000 - 0x9C4;

            obj->vars.h.unk_250 = atan2((place->z + offset_z - obj->z) >> 12, (px - obj->x) >> 12);
        }
        break;
    case 1:
        {
            s32 *pos = player_position();

            obj->vars.h.unk_250 = atan2(pos[2] - (obj->z >> 12), pos[0] - (obj->x >> 12));
        }
        if (is_player_near_placement(obj)) {
            if (patrol_player_dist(obj) < 0x6D7) {
                s32 cur_yaw;
                s32 cur_pitch;

                cur_yaw = obj->yaw;
                cur_pitch = obj->pitch;

                angles_to_player(obj->x >> 12, (obj->y >> 12) - (s16)obj->height / 2, obj->z >> 12, &yaw, &pitch);
                if (patrol_aimed_at(cur_yaw, yaw, cur_pitch, pitch)) {
                    point_to_view_angles(obj->x >> 12, obj->y >> 12, obj->z >> 12, &yaw, &pitch);
                    view_yaw = yaw;
                    view_pitch = pitch;
                    if (view_yaw > 0x800) {
                        view_yaw = 0x1000 - view_yaw;
                    }
                    if (view_pitch > 0x800) {
                        view_pitch = 0x1000 - view_pitch;
                    }
                    ahead = view_yaw < 0x400 && view_pitch < 0x400;
                    if (ahead) {
                        obj->unk_242 = 3;
                    }
                }
                break;
            }
        }
        obj->unk_242 = 2;
        break;
    case 2:
        obj->vars.h.unk_250 = atan2((patrol_home(obj)->z - obj->z) >> 12, (patrol_home(obj)->x - obj->x) >> 12);
        if (isqrt(length_sq((obj->x - patrol_home(obj)->x) >> 12, (obj->y - patrol_home(obj)->y) >> 12,
                            (obj->z - patrol_home(obj)->z) >> 12)) < 0x200) {
            obj->unk_242 = 0;
            break;
        }
        {
            s32 *pos = player_position();

            if (isqrt(length_sq(pos[0] - (patrol_home(obj)->x >> 12), pos[1] - (patrol_home(obj)->y >> 12),
                                pos[2] - (patrol_home(obj)->z >> 12))) < 0x9C5) {
                if (patrol_player_dist(obj) < 0x6D7) {
                    obj->unk_242 = 1;
                }
            }
        }
        break;
    }
    walker_mech_move(obj);
}

/* Two effects at +/-0x33 offsets from the object's position, rotated by its yaw and a pitch word. */
void obj_spawn_twin_effects(Object *obj, s32 arg) {
    s32 *v = scratch_alloc(0x20);
    u16 *rot = scratch_alloc(8);
    s32 z;

    rot[0] = -obj->vars.words[0];
    rot[1] = obj->yaw;
    rot[2] = 0;
    v[0] = obj->x >> 12;
    v[1] = obj->y >> 12;
    z = obj->z >> 12;
    v[4] = 0x33;
    v[5] = arg;
    v[6] = 0x81;
    v[2] = z;
    rotate_xz_twice((s16)rot[1], (s16)rot[0], &v[4], &v[5], &v[6]);
    v[4] += v[0];
    v[5] += v[1];
    v[6] += v[2];
    sound_play_at_units(SND_SHOT_FIRE_ALT_B | SND_GROUP(1), 0x60, 0x3C, &v[4]);
    shot_spawn_obj(&v[4], rot, 1, (obj->damage << 16) | 1);
    v[4] = -0x33;
    v[5] = arg;
    v[6] = 0x81;
    rotate_xz_twice((s16)rot[1], (s16)rot[0], &v[4], &v[5], &v[6]);
    v[4] += v[0];
    v[5] += v[1];
    v[6] += v[2];
    shot_spawn_obj(&v[4], rot, 1, (obj->damage << 16) | 1);
    scratch_top -= 0x28;
}

void walker_mech_attack(Object *obj, ObjHandler *handler) {
    s32 yaw;
    s32 pitch;
    s32 angle;
    s32 lim;
    s32 result = handler->result;

    angles_to_player(obj->x >> 12, (obj->y >> 12) - ((s16)obj->height / 2), obj->z >> 12, &yaw, &pitch);
    pitch = angle_approach(obj->vars.words[0], pitch, 0x10);
    angle = pitch & 0xFFF;
    lim = 0x40;
    if (angle >= 0x800) {
        if (angle < 0x1000 - lim) {
            angle = 0x1000 - lim;
        }
    } else if (angle > lim) {
        angle = lim;
    }
    obj->vars.words[0] = angle;
    switch (result) {
    case -2:
        handler->queued_entry = -1;
        handler->result = 0x28;
        obj->vx = 0;
        obj->vy = 0;
        obj->vz = 0;
        obj->speed = 0;
        break;
    case -1:
        obj_request_state(obj, handler, 1, 0);
        break;
    default:
        if ((result & 7) == 0) {
            obj_spawn_twin_effects(obj, -0xCF);
        }
        break;
    }
}

/* As spark_pair_spawn_at_obj, with the source taken from a 12-byte entry (index - 1) of table, and other angles. */
void fn_s05_800BA504(Object *obj, u8 *table, s32 index) {
    s32 *out = scratch_alloc(0x10);
    s16 *entry = (s16 *)(table + 4 + 12 * (index - 1));

    out[0] = entry[0];
    out[1] = 0;
    out[2] = entry[2];
    rotate_xz_twice(obj->yaw, 0, out, out + 1, out + 2);
    out[0] += obj->x >> 12;
    out[1] = obj->y >> 12;
    out[2] += obj->z >> 12;
    spark_pair_spawn((Vec3 *)out, 0x2000, 0x1555);
    scratch_top -= 0x10;
}

typedef struct ModelSound {
    s16 type;
    s16 index;
} ModelSound;

/* Each stage's copy uses its own tables. */
extern ModelSound walker_step_sounds_alt[2];
extern s32 pchr_pose_table_alt[];
#define STEP_SOUNDS walker_step_sounds_alt
#define MODEL_POINTS pchr_pose_table_alt

/* On a new type matching one of the two entries: plays a footstep sound (in the wet
   area/ground variant, a splash with sparks at the model's point). */
void walker_mech_update(Object *obj, ObjHandler *handler) {
    ModelSound *entry;
    s32 type;
    s32 wet;
    s32 i;

    if (obj->health > 0) {
        obj_script_step(obj, handler);
        if (get_area() / 3 == 4) {
            s32 ground = (surface_of(obj->ground_id) & 0x300) >> 8;
            wet = ground == 1;
        } else {
            wet = 0;
        }
        type = obj->type.unk_0C;
        entry = STEP_SOUNDS;
        for (i = 0; i < 2; i++, entry++) {
            if (entry->type == type && type != obj->vars.walker_mech.last_type) {
                if (wet == 1) {
                    fn_s05_800BA504(obj, (u8 *)MODEL_POINTS[((type + model_slot_pchr(*(s32 *)obj->asset)) & 0x7FF) * 7], entry->index);
                    sound_play_at(SND_SMALL_SPLASH | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
                    break;
                }
                sound_play_at(SND_MECH_STEP | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
                break;
            }
        }
        obj->vars.walker_mech.last_type = type;
    }
}

extern s16 *walker_mech_data[4];

extern s16 *walker_death_scripts_alt[];

/* Walker death: spawns the wreck model at the walker's pose, removes its
 * placement; the countdown in vars.h.unk_256 drives the sequence. */
s32 walker_mech_death(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 ret;
    s32 step;
    s32 pitch;
    s32 model;
    s32 wreck_model;
    s16 *counter;

    if ((s16)obj->vars.walker_mech.unk_256 == -2 && (u8)obj->hit_type == 4) {
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        pitch = obj->pitch;
        rot[0] = -pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        model = obj->type.unk_0E;
        object_spawn_at(pos, rot, model + model_slot_pchr(*(s32 *)obj->asset));
        placement_list_pop((ListRecord *)obj->placement);
        obj->placement->unk_04[0] = (obj->placement->unk_04[0] & 0xFC) | 2;
        return 0;
    }

    counter = (s16 *)&obj->vars.walker_mech.unk_256;
    step = *counter;
    ret = 1;
    switch (step) {
    case -2:
        obj->unk_17A = 0;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->type.unk_0A = 2;
        script_jump((Script *)obj, walker_death_scripts_alt[0], (s32)walker_mech_data);
        step = 0x16;
        break;
    case -1:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        pitch = obj->pitch;
        rot[0] = -pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        wreck_model = obj->type.unk_0E;
        object_spawn_at(pos, rot, wreck_model + model_slot_pchr(*(s32 *)obj->asset));
        ret = 0;
        placement_list_pop((ListRecord *)obj->placement);
        obj->placement->unk_04[0] = (obj->placement->unk_04[0] & 0xFC) | 2;
        break;
    default:
        step--;
        break;
    }
    *counter = step;
    return ret;
}

/* Each stage's copy uses its own tables. */
extern u8 walker_asset_table_alt[];
extern s16 *walker_type_data_alt[];
extern s16 *d_80116578;
extern ScriptCallEntry script_handler_table[];
extern StateEntry walker_state_table_alt[];
#define WALKER_ASSET walker_asset_table_alt
#define WALKER_TYPE_DATA walker_type_data_alt
#define WALKER_TYPE_WORD d_80116578
#define WALKER_TABLE_194 script_handler_table
#define WALKER_TABLE_198 walker_state_table_alt

/* Spawns the walker mech from its placement. */
s32 walker_mech_spawn(Placement *place) {
    Object *obj;
    s16 **script;
    ObjHandler *h;
    s32 kind;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    *(s16 *)&place->unk_00[2] = 0x708;
    h = obj->handlers;
    obj->handlers[0].fn = (void *)walker_mech_phase0;
    obj->handlers[1].fn = walker_mech_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = obj_draw_spark;
    *(volatile u8 *)&h[0].unk_11 = 0;
    *(volatile s16 *)&h[0].state = 0;
    *(volatile u8 *)&h[1].unk_11 = 0;
    *(volatile s16 *)&h[1].state = 0;
    *(volatile u8 *)&h[2].unk_11 = 0;
    *(volatile s16 *)&h[2].state = 0;
    *(volatile u8 *)&h[3].unk_11 = 0;
    *(volatile s16 *)&h[3].state = 0;
    *(volatile s32 *)&obj->callback = (s32)walker_mech_death;
    kind = place->unk_00[5];
    obj->asset = WALKER_ASSET;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = WALKER_TABLE_194;
    obj->state_table = WALKER_TABLE_198;
    *(volatile s16 *)&obj->unk_1C6 = 0;
    *(volatile s16 *)&obj->kind = kind;
    obj->script.data = WALKER_TYPE_DATA;
    obj->script.unk_0A = 0;
    obj->script.pc = WALKER_TYPE_WORD;
    script = walker_mech_data;
    script_start((Script *)obj, *script, (s32)script);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 1, 0x14CC);
    obj->vars.enemy.sound_channel[1] = -2;
    obj->vars.walker_mech.unused_24C = 0x8000;
    obj->speed_accel = 0x1000;
    obj->vars.walker_mech.last_type = 1;
    obj->vars.walker_mech.unused_248 = 0;
    obj->vars.walker_mech.unused_258 = 0;
    obj->speed = 0;
    obj->handlers[1].turn_timer = 0;
    obj->handlers[1].timer = 0;
    obj->unk_226[0] = 0x10;
    obj->vars.walker_mech.spawn_yaw = obj->yaw;
    return 1;
}

/* Reads the next script halfword (cursor at +0x20). With the flag at +0xF8 set, the cursor jumps to the
 * entry of the type's table (+0x1C) that the halfword selects. */
void script_jump_if_flag_set(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if (obj->script_flag != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_set_patrol_phase(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

/* Reads a script entry (a key and an index) from the object's cursor (0x20, in unk_1C.unk_04). When the
 * key matches the object's field at 0x242, the cursor jumps to the table entry for the index. */
void obj_script_jump_if_key(Object *obj) {
    s16 *cursor;
    s32 key;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    key = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (key == obj->unk_242) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}
