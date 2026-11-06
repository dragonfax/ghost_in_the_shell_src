/* giant_robot: one of the original source files (scripts/objmap.py); s01, s06, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Average of the values whose bit is set in mask (8 values). */
s32 obj_hit_mask_avg(s32 mask, s16 *values) {
    s32 sum;
    s32 count;
    s32 i;

    sum = 0;
    count = 0;
    i = 0;
    do {
        if ((mask >> i) & 1) {
            count++;
            sum += *values;
        }
        i++;
        values++;
    } while (i < 8);
    if (count != 0) {
        sum = sum / count;
    }
    return sum;
}

#if STAGE == 1
void giant_robot_take_hit(Object *obj, ObjHandler *handler) {
    s32 damage;
    s32 factor;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    damage = obj_hit_damage(obj->index);
    if (obj->hit_cooldown != 0) {
        obj->hit_cooldown += 0xFF; /* -1 as a byte; `--` gives addiu -1 */
    }
    if (damage > 0 && giant_robot_damage_scale != 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        factor = obj_hit_mask_avg(obj_hit_type(obj->index), giant_robot_hit_factors) * giant_robot_damage_scale;
        factor /= 0x1000;
        damage = damage * factor / 0x1000;
        obj->health -= damage;
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
    if (obj->health <= 0) {
        handler->state = 1;
        add_score(obj->score);
        add_kill_count(1);
        obj_set_hit_reaction(obj, 0);
        obj_sound_release(obj);
        obj_actors_clear_index();
        return;
    }
    if (test_bit(obj->flags, 5)) {
        obj_hit_reaction(obj, 0);
    }
}
#endif

#if STAGE == 1
/* Calls the object's hook at 0x170 (if set) with the object as its argument. */
void obj_hook_call(Object *obj, ObjHandler *handler) {
    s32 frame_pad[6]; /* unused: keeps the frame at 0x30 bytes, as in the original */
    void (*hook)(Object *) = (void (*)(Object *))obj->callback;
    if (hook != NULL) {
        hook(obj);
    }
}
#endif

#if STAGE == 1
/* Runs the start-up calls on the first step (state 0), then obj_hook_call once the state is set. */
void giant_robot_phase2(Object *obj, ObjHandler *handler) {
    s16 state = handler->state;

    if (state == 0) {
        giant_robot_take_hit(obj, handler);
        meter_set(obj->health, obj->vars.giant_robot.max_health);
        giant_robot_shots_tick();
    }
    if (handler->state != 0) {
        obj_hook_call(obj, handler);
    }
}

void giant_robot_draw(Object *obj) {
    Vec3 pos;
    SVECTOR rot;
    SVECTOR rot2;
    s32 value;
    s32 pitch;
    s32 colour;
    s32 *seq;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    obj_target_pchr_update();
    if (test_bit(obj->flags, 6)) {
        s32 base = obj->type.unk_0E;

        value = base + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        value = obj_keyframe_value(obj, 0);
    }
    pchr_lists_build(value);
    value = pchr_copy_slot(value);
    seq = pchr_poses_build(value);
    seq_slots[value & 0x7FF].first = (s32)seq;
    obj->vars.giant_robot.unused_248 = (s32)seq;
    if (get_fade_level() != 0) {
        value |= 0x8000;
        colour = fade_colour_from_level(get_fade_level());
    } else {
        colour = 0;
    }
    if (obj->hit > 0) {
        if (get_fade_level() != 0) {
            if (*(s16 *)&obj->vars.enemy.unk_260[0] != 0) {
                value &= 0xFFFF7FFF;
                colour = 0x60C0FF;
                *(s16 *)&obj->vars.enemy.unk_260[0] = 0;
            } else {
                *(s16 *)&obj->vars.enemy.unk_260[0] = 1;
            }
        } else {
            colour = 0x60C0FF;
        }
    }
    spark_add(pos.x, pos.y, pos.z, rot.vy, rot.vx, rot.vz, value, colour);
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    rot2.vx = obj->width;
    rot2.vy = obj->height;
    rot2.vz = obj->unk_1E8[0];
    aim_marker_draw(2, &rot2, &pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    giant_robot_systems_draw();
}

void giant_robot_sounds_start(void) {
    s32 *arg;
    s32 handle;

    if (stage_ready_get() != 0) {
        arg = (s32 *)giant_robot_asset;
        FAKE_OPAQUE(arg);
        handle = interp2c_add(giant_robot_sound_data_a, *arg);
        giant_robot_sound_handle_a = handle;
        interp2c_set_state(handle, 1);
        handle = interp2c_add(giant_robot_sound_data_b, *arg);
        giant_robot_sound_handle_b = handle;
        interp2c_set_state(handle, 1);
    }
}

s32 giant_robot_spawn(Placement *place) {
    Object *obj;
    s16 **script;
    ObjHandler *h;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    *(s16 *)&place->unk_00[2] = 0;
    h = obj->handlers;
    obj->handlers[0].fn = (void *)giant_robot_phase0;
    obj->handlers[1].fn = giant_robot_update;
    obj->handlers[2].fn = giant_robot_phase2;
    obj->handlers[3].fn = giant_robot_draw;
    obj->callback = (s32)giant_robot_teardown;
    obj->asset = giant_robot_asset;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = giant_robot_call_table;
    obj->state_table = D_80118574;
    obj->sounds = D_80117B30;
    h[0].unk_11 = 0;
    *(volatile s16 *)&h[0].state = 0;
    h[1].unk_11 = 0;
    *(volatile s16 *)&h[1].state = 0;
    h[2].unk_11 = 0;
    *(volatile s16 *)&h[2].state = 0;
    h[3].unk_11 = 0;
    *(volatile s16 *)&h[3].state = 0;
    *(volatile s16 *)&obj->unk_1C6 = 0;
    obj->script.data = giant_robot_link_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_80118570;
    script = giant_robot_data;
    script_start((Script *)obj, *script, (s32)script);
    obj_init_from_place(obj, place, 0x23);
    obj_set_part_bounds(obj, 0x1F, 0x1000);
    giant_robot_systems_init(obj);
    obj->vars.giant_robot.unk_25C = -1;
    obj->vars.giant_robot.turn_speed = 0;
    obj->vars.giant_robot.script_vars = 0;
    obj->vars.giant_robot.unused_254 = 0;
    obj->vars.giant_robot.unused_256 = 0;
    obj->vars.giant_robot.unused_258 = 0;
    obj->vars.giant_robot.unused_248 = 0;
    *(s16 *)obj->vars.enemy.unk_260 = 1;
    obj->vars.giant_robot.unused_24C = 0;
    obj->vars.giant_robot.max_health = obj->health;
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, 0x15);
    meter_set(obj->health, obj->vars.giant_robot.max_health);
    meter_set_mode(0);
    show_line((s32)"#1Warning!  Warning! Moving object acknowledged.\xA1");
    msg_show_slot(1, -1);
    warning_ack_set(1);
    giant_robot_set_damage_scale(0);
    obj_hit_flag_set(obj->index, 0x80);
    value_queue_index = 0;
    return 1;
}
#endif
