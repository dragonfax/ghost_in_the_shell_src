/* enemy_ai: one of the original source files (scripts/objmap.py); s03, s05. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Builds a 0x18-byte scratch record (Vec3 at 0, SVECTOR at 0x10) from the object's angles and height, then runs
 * the two draw helpers with it. */
void obj_fire_effect(Object *obj) {
    Vec3 *pos = (Vec3 *)scratch_top;
    SVECTOR *rot = (SVECTOR *)((u8 *)pos + 0x10);
    s32 pitch = obj->pitch;
    s16 roll;

    rot->vx = -pitch;
    rot->vy = obj->yaw;
    scratch_top += 0x18;
    roll = obj->roll;
    pos->x = 0x1C;
    rot->vz = roll;
    pos->y = (-(s16)obj->height * 3) / 4 - 0x10;
    pos->z = 0x5A;
    obj_offset_to_world_shifted(obj, (s32 *)pos);
    rot->vx -= 0x10;
    sound_play_at_units(SND_SHOT_FIRE | SND_GROUP(1), 0x40, 0x3C, pos);
    shot_spawn_obj((s32 *)pos, (u16 *)rot, 2, (s32)&shot_params_b);
    scratch_top -= 0x18;
}

/* Looks up the direction from the object to a point (angles_to_player) and reports whether the yaw is
   within 0x200 of the object's yaw: *flag is set when the pitch, negated and offset by 0x200, is below
   0x200. Returns whether the yaw, offset by 0x200 and wrapped to 0..0xFFF, is in the first 0x400. */
s32 fn_800BA0F8(Object *obj, s32 *flag) {
    s32 yaw;
    s32 pitch;

    angles_to_player(obj->x, obj->y, obj->z, &yaw, &pitch);
    pitch = -0x200 - pitch;
    if (pitch < 0x200) {
        *flag = 1;
    } else {
        *flag = 0;
    }
    return ((yaw + 0x200) & 0xFFF) < 0x400;
}

/* Starts an enemy's shot: picks a shot timer of 1..4, turns towards the player and, unless the
   player is more than 0x300 off its facing, jumps its script to the stage's script table[mode]
   (next_state 2 when the player is out of range). */
extern s16 *bazooka_script_table[17];
void enemy_start_shot(Object *obj, ObjHandler *handler, s32 mode) {
    s32 unused[6]; /* never touched; the original frame has 0x18 bytes more */

    handler->timer = 0;
    obj->unk_242 = 0;
    obj->vars.ride.sound2 = 0;
    obj->vars.enemy.shot_timer = rand_a_next() % 4 + 1;
    turn_toward_player(obj, 0x40);
    if (player_outside_arc(obj, 0x300)) {
        handler->result = -2;
    } else {
        if (enemy_in_range(obj, 0x480, 0x200) == 0) {
            obj->next_state = 2;
        }
        {
            script_jump((Script *) obj, bazooka_script_table[mode], (s32) bazooka_script_table);
        }
        handler->result = 1;
    }
}

#if STAGE == 5
s32 enemy_in_range(Object *obj, s32 arg1, s32 arg2);
#endif

/* Once the object has reached its target state, count down its shot timer and
   keep reporting the step as running; when the timer runs out, move to state 4. */
void enemy_wait_shot_timer(Object *obj, ObjHandler *handler) {
    s32 at_target = 0;
    s32 shot_timer;

    if (obj->script_flag == -1) {
        at_target = obj->next_state == handler->state;
    }
    if (at_target != 0) {
        if (enemy_in_range(obj, 0x480, 0x200) == 0) {
            obj->next_state = 4;
        }
        shot_timer = obj->vars.enemy.shot_timer;
        if (shot_timer > 0) {
            obj->vars.enemy.shot_timer = shot_timer - 1;
            handler->result = 1;
            return;
        }
        obj->next_state = 4;
    }
}

void enemy_start_shot(Object *obj, ObjHandler *handler, s32 mode);
void enemy_face_player(Object *obj, ObjHandler *handler) {
    s32 *player_pos;
    s32 aim_yaw;
    s32 old_yaw;
    s32 new_yaw;
    s32 turn;
    s32 next_result;

    switch (handler->result) {
    case -2:
        enemy_start_shot(obj, handler, 6);
        return;
    case -1:
        enemy_wait_shot_timer(obj, handler);
        return;
    default:
        break;
    }

    player_pos = player_position();
    aim_yaw = atan2(player_pos[2] - (obj->z >> 12),
                    player_pos[0] - (obj->x >> 12));
    old_yaw = obj->yaw;
    new_yaw = angle_approach(old_yaw, (s16) aim_yaw, 0x20);
    turn = (s16) new_yaw - old_yaw;
    obj->turn = turn;
    obj->yaw = new_yaw;

    if (obj->script_flag == 0xFF) {
        obj_fire_effect(obj);
        next_result = -1;
    } else {
        next_result = handler->result + 1;
    }
    handler->result = next_result;
}

void obj_play_sound_attached(Object *obj) {
    s32 temp_v0;

    temp_v0 = sound_start(SND_GROUND_IMPACT | SND_GROUP(2), 0x7F, 0, 0);
    if (temp_v0 != 0) {
        sound_attach(temp_v0, &obj->x, NULL);
    }
}

#if STAGE == 5
void obj_play_sound_attached(Object *obj);
#endif

/* Runs func_800B77CC when the halfword at 0xF8 is 0xF. */
void enemy_state_f_sound(Object *obj) {
    if (obj->script_flag == 0xF) {
        obj_play_sound_attached(obj);
    }
}

#if STAGE == 3
void obj_play_sound_attached(Object *obj);
#endif

/* With state 0xF: if the object stands on surface type 1, builds a rotated position vector in scratch, runs the
 * matrix helper and starts a sound attached to the object. Otherwise calls obj_play_sound_attached. */
void enemy_step_spark(Object *obj) {
    Vec3 *pos;
    s32 handle;

    if (obj->script_flag == 0xF) {
        if (((surface_of(obj->ground_id) & 0x300) >> 8) == 1) {
            pos = scratch_alloc(0x10);
            pos->x = 0;
            pos->y = 0;
            pos->z = 0x30;
            rotate_xz_twice(obj->yaw, 0, &pos->x, &pos->y, &pos->z);
            pos->x += obj->x >> 12;
            pos->y = obj->y >> 12;
            pos->z += obj->z >> 12;
            spark_pair_spawn(pos, 0x1000, 0x1000);
            scratch_top -= 0x10;
            handle = sound_start(SND_SMALL_SPLASH | SND_GROUP(2), 0x7F, 0, 0);
            if (handle != 0) {
                sound_attach(handle, &obj->x, 0);
            }
        } else {
            obj_play_sound_attached(obj);
        }
    }
}

void enemy_ai_update(Object *obj, ObjHandler *handler) {
    enemy_sense(obj);
    if ((obj->vars.enemy_spawn_from.player_dist < obj->vars.enemy_spawn_from.sense_range) || (obj->vars.enemy_spawn_from.unk_250 != 0)) {
        if (obj->next_state < 3) {
            if (obj->next_state > 0) {
                obj->next_state = 3;
            }
        }
    }
    if ((obj->vars.enemy_spawn_from.unk_266 == 0) && (obj->vars.enemy_spawn_from.unk_250 == 0)) {
        if (obj->next_state == 5) {
            obj->speed = 0;
        } else {
            if (obj->vars.enemy_spawn_from.unk_269 == 0) {
                obj->next_state = 6;
            } else {
                obj->next_state = 5;
            }
        }
    }
    obj_script_step(obj, handler);
    enemy_hit_update(obj);
    if (get_area() / 3 == 4) {
        enemy_step_spark(obj);
        return;
    }
    enemy_state_f_sound(obj);
}

#if STAGE == 3 /* s05 has its own data addresses */
void enemy_reset(Object *obj);
extern ScriptCursor D_80118198[4];
extern s16 *bazooka_script_table[17];
s32 enemy_spawn_countdown(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 hits;
    s32 base;
    s32 next;
    s32 hit;
    s32 pitch;
    ListRecord *rec;

    hits = obj->vars.snd.sound;
    switch (hits) {
    case -1:
        enemy_reset(obj);
        hit = (u8)obj->hit_type;
        if (hit < 3 && hit != 0) {
            obj->vars.enemy_spawn_from.unused_248 = 0xD;
            ((Script *)obj)->state.b = 2;
            script_jump((Script *)obj, D_80118198[0].pc, (s32)bazooka_script_table);
            next = 0x42;
        } else {
            next = 4;
        }
        break;
    case 0:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        pitch = obj->pitch;
        rot[0] = -pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        base = (s16)((Script *)obj)->state.d;
        object_spawn_at(pos, rot, base + model_slot_pchr(*(s32 *)obj->asset));
        placement_list_pop((ListRecord *)obj->placement);
        rec = (ListRecord *)obj->placement;
        *(u8 *)rec->body = (*(u8 *)rec->body & 0xFC) | 2;
        return 0;
    default:
        next = obj->vars.snd.sound - 1;
        break;
    }
    obj->vars.snd.sound = next;
    return 1;
}
#else
extern s16 *enemy_hit_script[4];
extern s16 *bazooka_script_table[17];
/* Same code as enemy_spawn_countdown (s03). */
s32 enemy_spawn_countdown(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 hits;
    s32 base;
    s32 next;
    s32 hit;
    s32 pitch;
    ListRecord *rec;

    hits = obj->vars.snd.sound;
    switch (hits) {
    case -1:
        enemy_reset(obj);
        hit = (u8)obj->hit_type;
        if (hit < 3 && hit != 0) {
            obj->vars.enemy_spawn_from.unused_248 = 0xD;
            ((Script *)obj)->state.b = 2;
            script_jump((Script *)obj, enemy_hit_script[0], (s32)bazooka_script_table);
            next = 0x42;
        } else {
            next = 4;
        }
        break;
    case 0:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        pitch = obj->pitch;
        rot[0] = -pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        base = (s16)((Script *)obj)->state.d;
        object_spawn_at(pos, rot, base + model_slot_pchr(*(s32 *)obj->asset));
        placement_list_pop((ListRecord *)obj->placement);
        rec = (ListRecord *)obj->placement;
        *(u8 *)rec->body = (*(u8 *)rec->body & 0xFC) | 2;
        return 0;
    default:
        next = obj->vars.snd.sound - 1;
        break;
    }
    obj->vars.snd.sound = next;
    return 1;
}
#endif

void shot_params_init(void) {
    ShotParamBlock *params = (ShotParamBlock *)&shot_params_b;
    s16 two = 2;
    s16 twenty = 0x20;

    params->unk_00 = 0xC000;
    params->unk_08 = 0x2800;
    params->unk_0E = two;
    params->unk_10 = twenty;
    params->unk_12 = 0x28;
    params->unk_14 = 0x10;
    params->unk_16 = 0x16;
    params->unk_18 = 0xC;
    params->unk_1A = two;
    params->unk_1C = 0x80;
    params->unk_1E = 0x18;
    params->unk_20 = 0xA;
    params->unk_22 = twenty;
}

#if STAGE == 3 /* s05 has its own data addresses */
void enemy_script_start(Object *obj, s16 **scripts, s16 **jumps);
void enemy_ai_update(Object *obj, ObjHandler *handler);
extern s32 helicopter_asset_slot[3];
extern SoundVolume enemy_sound_volume_s03[1];
extern s16 *bazooka_script_table[17];
extern s16 *enemy_script_jumps_s03[16];
extern s16 *enemy_mode_scripts_s03[7];
extern StateEntry enemy_state_table_s03[15];
extern s32 D_80121318;
extern u16 D_80121320;
s32 enemy_spawn_from_place(Placement *place) {
    Object *obj;
    s32 script_arg;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    enemy_init(obj, place);
    enemy_script_start(obj, enemy_mode_scripts_s03, enemy_script_jumps_s03);
    obj->handlers[1].fn = enemy_ai_update;
    obj->callback = (s32) &enemy_spawn_countdown;
    obj->vars.enemy_spawn_from.sense_range = 0x800;
    *(s16 *) &obj->vars.enemy.unk_260[4] = 0xA00;
    *(s16 *) obj->vars.enemy.unk_260 = 0x600;
    obj->asset = helicopter_asset_slot;
    obj->state_table = enemy_state_table_s03;
    script_arg = (s32) bazooka_script_table;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->sounds = enemy_sound_volume_s03;
    script_start((Script *) obj, *(s16 **) script_arg, script_arg);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 1, 0x1666);
    D_80121320 = obj->damage;
    D_80121318 = (get_area() * 2 + 0xC) << 12;
    return 1;
}
#else
extern s16 *enemy_mode_scripts[7];
extern s16 *enemy_script_jumps[16];
extern ModelSlotHead enemy_asset_slots;
extern StateEntry enemy_state_table[15];
extern SoundVolume enemy_sound_volume[1];
extern s16 *bazooka_script_table[17];
extern u16 D_8011FFFC;
extern s32 enemy_area_limit;
/* Same code as enemy_spawn_from_place (s03). */
s32 enemy_spawn_from_place(Placement *place) {
    Object *obj;
    s32 script_arg;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    enemy_init(obj, place);
    enemy_script_start(obj, enemy_mode_scripts, enemy_script_jumps);
    obj->handlers[1].fn = enemy_ai_update;
    obj->callback = (s32) &enemy_spawn_countdown;
    obj->vars.enemy_spawn_from.sense_range = 0x800;
    *(s16 *) &obj->vars.enemy.unk_260[4] = 0xA00;
    *(s16 *) obj->vars.enemy.unk_260 = 0x600;
    obj->asset = &enemy_asset_slots;
    obj->state_table = enemy_state_table;
    script_arg = (s32) bazooka_script_table;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->sounds = enemy_sound_volume;
    script_start((Script *) obj, *(s16 **) script_arg, script_arg);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 1, 0x1666);
    D_8011FFFC = obj->damage;
    enemy_area_limit = (get_area() * 2 + 0xC) << 12;
    return 1;
}
#endif
