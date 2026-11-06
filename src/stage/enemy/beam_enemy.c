/* beam_enemy: one of the original source files (scripts/objmap.py); s02, s10. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Beam segment step: moves along its speed table until it hits a wall or nears
   the camera (hits the player once); spawns the next segment below 55 health. */
void beam_segment_update(Object *obj, ObjHandler *handler) {
    s32 to[3];
    s32 from[3];
    s32 hit[4];
    s32 step_x, step_y, step_z;
    s16 *steps;
    s16 *step;
    s32 hp;
    s32 next;
    s32 *player;
    u32 state_pair;
    s32 rnd;
    s32 yaw, pitch, speed;
    s32 base_pitch, base_yaw, base_roll;
    Object *next_seg;

    steps = obj->vars.beam.steps;
    hp = obj->health;
    if (hp <= 0) {
        obj_free(obj);
        return;
    }
    obj->health = hp - 1;
    if (obj->health < steps[0] && steps[0] > 0) {
        step = obj->vars.beam.steps;
        obj->vars.beam.steps = step + 4;
        obj->speed = step[6];
    }
    if (obj->vars.beam.active == 0) {
        return;
    }
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    to[0] = obj->vars.beam.origin[0] >> 12;
    to[1] = obj->vars.beam.origin[1] >> 12;
    to[2] = obj->vars.beam.origin[2] >> 12;
    if (trace_world(8, 0x28, to, from, hit) != 1) {
        if (isqrt(length_sq((cam_pos >> 12) - (obj->x >> 12),
                            (cam_pos_y >> 12) - (obj->y >> 12),
                            (cam_pos_z >> 12) - (obj->z >> 12))) < 180) {
            if (obj->vars.beam.owner->unk_180 == 1) {
                player = player_position();
                hit_target_masked(0, 0x10, atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)), obj->damage);
                obj->vars.beam.owner->unk_180 = 0;
                obj->vars.beam.active = 0;
            }
        } else {
            yaw = obj->yaw;
            pitch = obj->pitch;
            speed = obj->speed;
            angles_to_vector(yaw, pitch, speed, &step_x, &step_y, &step_z);
            obj->x += step_x;
            obj->move_delta[0] = step_x;
            obj->y += step_y;
            obj->move_delta[1] = step_y;
            obj->z += step_z;
            obj->move_delta[2] = step_z;
        }
    }
    if (obj->health < 55 && (next = obj->next_state) != 0) {
        u16 rot[3];

        state_pair = (obj->damage << 16) | (u16)(next - 1);
        rnd = rand_a_next();
        base_yaw = obj->vars.beam.rot[1] - 0x20;
        rot[1] = base_yaw + rnd % 64;
        rnd = rand_a_next();
        base_roll = obj->vars.beam.rot[2] - 0x20;
        rot[2] = base_roll + rnd % 64;
        rnd = rand_a_next();
        base_pitch = obj->vars.beam.rot[0] - 0x20;
        rot[0] = base_pitch + rnd % 64;
        next_seg = beam_segment_spawn(obj->vars.beam.sound, obj->vars.beam.origin, rot, state_pair);
        obj->unk_180 = (s32)next_seg;
        next_seg->vars.beam.owner = obj->vars.beam.owner;
        obj->next_state = 0;
    }
    obj->y -= 0x2000;
}

/* Beam segment draw: adds one spark at the segment's position, its model the
   beam's sound slot plus the step table's second entry (flag 0x2000). The
   loads are split into separate statements to keep the original's order. */
void beam_segment_draw(Object *obj, ObjHandler *handler) {
    SparkList *list;
    SparkRec *s;
    u8 *tail;
    s32 n, y, z, value, x, rx, raw_y, raw_z, sound, sum, step;

    step = obj->vars.beam.steps[1];
    x = obj->x >> 12;
    sound = obj->vars.beam.sound;
    raw_z = obj->z;
    raw_y = obj->y;
    sum = sound + step;
    y = raw_y >> 12;
    z = raw_z >> 12;
    value = sum | 0x2000;
    rx = 0x800;
    list = &spark_list;
    n = spark_count;
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
        s->pitch = rx;
        s->roll = 0;
    }
}

void beam_segment_update(Object *obj, ObjHandler *handler);
void beam_segment_draw(Object *obj, ObjHandler *handler);
/* The stage's data this object points at. */
extern BeamStep beam_segment_data[6];
#define SPAWN_DATA beam_segment_data

Object *beam_segment_spawn(s32 sound, s32 *pos, u16 *rot, u32 state_pair) {
    Object *obj;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = beam_segment_update;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[3].fn = beam_segment_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj_set_flags(obj, 0x80);
        obj->vars.snd.sound = sound;
        obj->vars.beam_segment.unk_250 = (s32) SPAWN_DATA;
        obj->vars.beam_segment.pos_x = pos[0];
        obj->vars.beam_segment.pos_y = pos[1];
        obj->vars.beam_segment.pos_z = pos[2];
        *(u16 *) &obj->vars.beam_segment.unk_268 = rot[0];
        obj->vars.enemy.target_yaw = rot[1];
        obj->vars.enemy.walk_state = rot[2];
        obj->x = pos[0];
        obj->y = pos[1];
        obj->z = pos[2];
        obj->pitch = rot[0];
        {
            s16 hi = state_pair >> 16;
            u16 yaw = rot[1];
            u16 roll;
            register Object *spawned asm("$2") = obj;

            spawned->yaw = yaw;
            roll = rot[2];
        spawned->speed = 0x14;
        spawned->health = 0x38;
        spawned->next_state = state_pair;
        spawned->damage = hi;
        spawned->vars.words[0] = 1;
        spawned->roll = roll;
        return spawned;
        }
    }
    /* NULL: obj_new's result is still in v0 */
}

/* Stops the enemy's loop sound, if it has one. */
void enemy_sound_handle_stop(Object *obj) {
    if (obj->vars.enemy.sound != 0) {
        sound_stop(obj->vars.enemy.sound);
        obj->vars.enemy.sound = 0;
    }
}

/* Fires a beam segment from the object's muzzle (0x20, -2/3 height, 0x40) at the
   player, its pitch held to 0..0x180 or 0xF00..0xFFF. */
void enemy_fire_beam(Object *obj) {
    s32 *pos;
    u16 *rot;
    s32 yaw, pitch;
    s32 angle;
    s32 lo, hi;
    Object *seg;
    u32 state_pair;

    obj->pitch = 0;
    pos = scratch_alloc(0x18);
    pos[0] = 0x20;
    pos[1] = (-(s16)obj->height * 2) / 3;
    pos[2] = 0x40;
    obj_offset_to_fixed(obj, pos);
    ((u16 *)(pos + 4))[1] = obj->yaw;
    angles_to_player(pos[0] >> 12, pos[1] >> 12, pos[2] >> 12, &yaw, &pitch);
    rot = (u16 *)(pos + 4);
    angle = -pitch;
    angle &= 0xFFF;
    hi = 0x180;
    if (angle < 0x800) {
        angle = NOT_NEGATIVE(MIN(angle, hi));
    } else {
        lo = 0xF00;
        angle = lo > MIN(angle, 0xFFF) ? lo : MIN(angle, 0xFFF);
    }
    rot[0] = angle;
    state_pair = (((s16)obj->damage / 2) << 16) | 8;
    seg = beam_segment_spawn(model_slot_pchr(*(s32 *)obj->asset), pos, rot, state_pair);
    scratch_top -= 0x18;
    seg->vars.beam.active = 1;
    seg->vars.beam.owner = obj;
    obj->unk_180 = 1;
}

/* The stage's enemy data: word 0 its start script, word 6 the script it runs once it faces
   the player. */
extern s16 *enemy_data[8];
#define ENEMY_DATA enemy_data

/* Attack step of the beam-firing enemy (s10: the flamethrower soldier): turns toward the
   player (0x30 a frame). Result -2 (start): once the player is within 0x300 of its facing, it
   jumps to the data's word-6 script (result 1), else stays at -2. Result -1: when the next
   state is the handler's, stops the loop sound, goes to state 4 and sets unk_26E to 30..89.
   Otherwise, once it stops turning: with the player in range, it picks state 3 or 4
   (unk_274 clear) or keeps the loop sound going and fires a beam segment (result -1); out of
   range it stops the sound and goes to state 2; still turning, it stops the sound (result 1). */
void beam_enemy_attack_update(Object *obj, ObjHandler *handler) {
    s32 result;
    s16 **slot;
    s32 ready;
    s32 rnd;
    s32 turn;
    s32 turn_high;

    turn_toward_player(obj, 0x30);
    switch (handler->result) {
    case -2:
        obj->unk_242 = 0;
        handler->result = 1;
        handler->timer = 0;
        if (player_outside_arc(obj, 0x300)) {
            result = -2;
        } else {
            slot = ENEMY_DATA + 6;
            script_jump((Script *) obj, *slot, (s32) (slot - 6));
            result = 1;
        }
        break;
    case -1:
        ready = obj->script_flag == -1 && obj->next_state == handler->state;
        if (ready) {
            if (obj->vars.enemy.sound != 0) {
                sound_stop(obj->vars.enemy.sound);
                obj->vars.enemy.sound = 0;
            }
            rnd = rand_a_next();
            obj->next_state = 4;
            *(s16 *) obj->vars.enemy.unk_26E = rnd % 60 + 30;
        }
        return;
    default:
        turn = obj->turn;
        turn_high = turn << 16;
        if ((turn >= 0 ? turn_high >> 16 : -turn) < 4) {
            if (enemy_in_range(obj, 0x500, 0x300)) {
                if (obj->vars.enemy_create_obj.unk_274 == 0) {
                    if (rand_a_next() > 0xC00) {
                        obj->next_state = 3;
                    } else {
                        obj->next_state = 4;
                    }
                    handler->result = -2;
                } else {
                    if (obj->vars.enemy.sound == 0) {
                        obj->vars.enemy.sound = sound_start(SND_PAIR(SND_ENEMY_BEAM_LOOP | SND_HELD | SND_GROUP(1), SND_ENEMY_BEAM_FIRE_LOOP | SND_HELD | SND_GROUP(1)), 0x60, 0, 0);
                        sound_attach(obj->vars.enemy.sound, &obj->x, 0);
                    }
                    enemy_fire_beam(obj);
                }
                result = -1;
            } else {
                if (obj->vars.enemy.sound != 0) {
                    sound_stop(obj->vars.enemy.sound);
                    obj->vars.enemy.sound = 0;
                }
                obj->next_state = 2;
                return;
            }
        } else {
            if (obj->vars.enemy.sound != 0) {
                sound_stop(obj->vars.enemy.sound);
                obj->vars.enemy.sound = 0;
            }
            result = 1;
        }
        break;
    }
    handler->result = result;
}

#if STAGE == 2
void enemy_hit_update(Object *obj);
#endif

void enemy_step(Object *obj, ObjHandler *handler) {
    enemy_sense(obj);
    if (obj->vars.enemy_create_obj.player_distance < obj->vars.enemy_create_obj.activation_distance || obj->vars.enemy_create_obj.unk_250 != 0) {
        if (obj->next_state < 3) {
            if (obj->next_state > 0) {
                obj->next_state = 3;
            }
        }
    }
    if (obj->vars.enemy_create_obj.unk_266 == 0 && obj->vars.enemy_create_obj.unk_250 == 0) {
        if (obj->next_state == 5) {
            obj->speed = 0;
        } else if (obj->vars.enemy_create_obj.unk_269 == 0) {
            obj->next_state = 6;
        } else if (obj->vars.enemy_create_obj.unk_274 != 0) {
            obj->next_state = 5;
        } else {
            obj->next_state = 6;
        }
    }
    obj_script_step(obj, handler);
    enemy_hit_update(obj);
}

#if STAGE == 2 /* s10's copy uses its own data */
extern ScriptPcSlot enemy_death_script;
extern s16 *enemy_data[8];
void enemy_reset(Object *obj);
s32 enemy_death_update(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 base;
    u8 *flags;
    s32 hit;
    s32 pitch;

    switch (obj->vars.enemy_create_obj.timer) {
    case -1:
        enemy_reset(obj);
        if (obj->vars.enemy.sound != 0) {
            sound_stop(obj->vars.enemy.sound);
            obj->vars.enemy.sound = 0;
        }
        hit = (u8) obj->hit_type;
        if (hit < 3 && hit != 0) {
            obj->vars.enemy.mode = 7;
            obj->type.unk_0A = 2;
            script_jump((Script *) obj, enemy_death_script.pc, (s32) enemy_data);
            obj->vars.enemy_create_obj.timer = 0x30;
        } else {
            obj->vars.enemy_create_obj.timer = 4;
        }
        obj->unk_180 = 0;
        break;
    case 0:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        pitch = obj->pitch;
        rot[0] = -pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        base = obj->type.unk_0E;
        object_spawn_at(pos, rot, base + model_slot_pchr(*(s32 *) obj->asset));
        placement_list_pop((ListRecord *) obj->placement);
        flags = (u8 *) obj->placement + 4;
        *flags = (*flags & 0xFC) | 2;
        return 0;
    default:
        obj->vars.enemy_create_obj.timer -= 1;
        break;
    }
    return 1;
}
#else
extern ScriptPcSlot enemy_death_script;
extern s16 *enemy_data[8];
/* Same code as enemy_death_update (s02). */
s32 enemy_death_update(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 base;
    u8 *flags;
    s32 hit;
    s32 pitch;

    switch (obj->vars.enemy_create_obj.timer) {
    case -1:
        enemy_reset(obj);
        if (obj->vars.enemy.sound != 0) {
            sound_stop(obj->vars.enemy.sound);
            obj->vars.enemy.sound = 0;
        }
        hit = (u8) obj->hit_type;
        if (hit < 3 && hit != 0) {
            obj->vars.enemy.mode = 7;
            obj->type.unk_0A = 2;
            script_jump((Script *) obj, enemy_death_script.pc, (s32) enemy_data);
            obj->vars.enemy_create_obj.timer = 0x30;
        } else {
            obj->vars.enemy_create_obj.timer = 4;
        }
        obj->unk_180 = 0;
        break;
    case 0:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        pitch = obj->pitch;
        rot[0] = -pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        base = obj->type.unk_0E;
        object_spawn_at(pos, rot, base + model_slot_pchr(*(s32 *) obj->asset));
        placement_list_pop((ListRecord *) obj->placement);
        flags = (u8 *) obj->placement + 4;
        *flags = (*flags & 0xFC) | 2;
        return 0;
    default:
        obj->vars.enemy_create_obj.timer -= 1;
        break;
    }
    return 1;
}
#endif

void enemy_script_start(Object *obj, s16 **scripts, s16 **jumps);
#if STAGE == 2 /* s10's copy uses its own data */
extern s16 *flamethrower_soldier_scripts[5];
extern s16 *flamethrower_soldier_jumps[14];
extern s32 enemy_model_data[3];
extern StateEntry D_80116B48[8];
extern SoundVolume D_801167FC[1];
s32 enemy_create(Placement *place) {
    Object *obj;
    s16 **table;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
    enemy_init(obj, place);
    enemy_script_start(obj, flamethrower_soldier_scripts, flamethrower_soldier_jumps);
    if ((u32) (obj->vars.enemy.mode - 3) < 2U) {
        obj->vars.enemy_create_obj.activation_distance = obj->vars.jitter.timer;
    }
    obj->handlers[1].fn = enemy_step;
    obj->callback = (s32) &enemy_death_update;
    obj->destructor = enemy_sound_handle_stop;
    obj->asset = enemy_model_data;
    obj->state_table = D_80116B48;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->sounds = D_801167FC;
    table = enemy_data;
    script_start((Script *) obj, *table, (s32) table);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 1, 0x1666);
    obj->vars.enemy_create_obj.unk_276 = (s16) (((s32) (-(s16) obj->height * 3) / 4) - 0x10);
    return 1;
}
#else
extern s16 *flamethrower_soldier_scripts[5];
extern s16 *flamethrower_soldier_jumps[14];
extern s32 flamethrower_soldier_model[3];
extern StateEntry D_8011BC1C[8];
extern SoundVolume D_8011B8D0[1];
extern s16 *enemy_data[8];
/* Same code as enemy_create (s02). */
s32 enemy_create(Placement *place) {
    Object *obj;
    s16 **table;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
    enemy_init(obj, place);
    enemy_script_start(obj, flamethrower_soldier_scripts, flamethrower_soldier_jumps);
    if ((u32) (obj->vars.enemy.mode - 3) < 2U) {
        obj->vars.enemy_create_obj.activation_distance = obj->vars.jitter.timer;
    }
    obj->handlers[1].fn = enemy_step;
    obj->callback = (s32) &enemy_death_update;
    obj->destructor = enemy_sound_handle_stop;
    obj->asset = flamethrower_soldier_model;
    obj->state_table = D_8011BC1C;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->sounds = D_8011B8D0;
    table = enemy_data;
    script_start((Script *) obj, *table, (s32) table);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 1, 0x1666);
    obj->vars.enemy_create_obj.unk_276 = (s16) (((s32) (-(s16) obj->height * 3) / 4) - 0x10);
    return 1;
}
#endif
