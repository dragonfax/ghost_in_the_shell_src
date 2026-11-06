/* smg_soldier: one of the original source files (scripts/objmap.py); s01, s08, s10, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Gives the world position (vec[0..2], 1/4096 units) of a point 0x14 ahead, 0x50 out and the
 * halfword at 0x276 up, rotated by the object's yaw and pitch. */
void enemy_muzzle_pos(Object *obj, s32 *vec) {
    s32 up;

    vec[0] = 0x14;
    up = *(s16 *)&obj->vars.enemy.unk_276[0];
    vec[2] = 0x50;
    vec[1] = up;
    rotate_xz_twice(obj->yaw, obj->pitch, vec, vec + 1, vec + 2);
    vec[0] = (obj->x >> 12) + vec[0];
    vec[1] = (obj->y >> 12) + vec[1];
    vec[2] = (obj->z >> 12) + vec[2];
}

/* Fires a shot from the enemy's muzzle: aims along the muzzle direction, takes the yaw from the
 * object, jitters yaw and pitch by -0x18..+0x17, and spawns the shot. */
void enemy_muzzle_shot(Object *obj) {
    s32 *pos = scratch_alloc(0x18);
    s16 *rot = (s16 *)(pos + 4);

    enemy_muzzle_pos(obj, pos);
    dir_to_angles_clamped((Vec3 *)pos, (SVECTOR *)rot);
    rot[1] = obj->yaw;
    rot[1] = (s16)(rot[1] - 0x18) + rand_a_next() % 48;
    rot[0] = (s16)(rot[0] - 0x18) + rand_a_next() % 48;
    shot_spawn_obj(pos, (u16 *)rot, 1, (obj->damage << 16) | 1);
    scratch_top -= 0x18;
}

/* Starts an SMG soldier's burst: 2..4 shots, turns towards the player and, unless the player is
   more than 0x300 off its facing, jumps its script to smg_soldier_data[mode]. */
void enemy_start_burst(Object *obj, ObjHandler *handler, s32 mode) {
    s32 unused[6]; /* never touched; the original frame has 0x18 bytes more */

    handler->timer = 0;
    obj->unk_242 = 0;
    obj->vars.smg_soldier.unk_250 = 0;
    obj->vars.enemy.shots_left = rand_a_next() % 3 + 2;
    turn_toward_player(obj, 0x40);
    if (player_outside_arc(obj, 0x300)) {
        handler->result = -2;
    } else {
        if (enemy_in_range(obj, 0x500, 0x300) == 0) {
            obj->next_state = 2;
        }
        script_jump((Script *) obj, smg_soldier_data[mode], (s32) smg_soldier_data);
        handler->result = 1;
    }
    if (obj->vars.enemy.sound == 0) {
        obj->vars.enemy.sound = 0x100;
    }
}

/* An enemy's firing burst: fire `shots_left` shots at random intervals, then pick the next state. */
void enemy_fire_burst(Object *obj, ObjHandler *handler) {
    s32 same;

    same = 0;
    if (obj->script_flag == -1) {
        same = obj->next_state == handler->state;
    }
    if (same) {
        if (enemy_in_range(obj, 0x480, 0x300) == 0) {
            obj->next_state = 4;
        }
    } else if (obj->vars.enemy.shots_left > 0) {
        if (--obj->vars.enemy.shot_timer <= 0) {
            if (obj->vars.smg_soldier.unk_274 != 0) {
                obj->vars.enemy.shot_timer = rand_a_next() & 7;
                obj->vars.enemy.shots_left--;
                enemy_muzzle_shot(obj);
                handler->result = 1;
                if (obj->vars.enemy.sound == SOUND_PENDING) {
                    obj->vars.enemy.sound = sound_start(SND_HEAVY_GUNFIRE | SND_HELD | SND_GROUP(1), 0x40, 0, 0);
                    sound_attach(obj->vars.enemy.sound, &obj->x, NULL);
                }
            } else {
                if (rand_a_next() > 0xC00) {
                    obj->next_state = 3;
                } else {
                    obj->next_state = 4;
                }
                handler->result = -2;
                if (obj->vars.enemy.sound != 0) {
                    if (obj->vars.enemy.sound != SOUND_PENDING) {
                        sound_stop(obj->vars.enemy.sound);
                    }
                    obj->vars.enemy.sound = 0;
                }
                obj->vars.enemy.shots_left = 0;
            }
        }
    } else {
        if (obj->vars.enemy.sound != 0) {
            if (obj->vars.enemy.sound != SOUND_PENDING) {
                sound_stop(obj->vars.enemy.sound);
            }
            obj->vars.enemy.sound = 0;
        }
        if (obj->vars.smg_soldier.unk_269 == 0) {
            obj->next_state = 4;
        } else if ((u32)(obj->vars.enemy.mode - 3) < 2 || rand_a_next() <= 0xC00) {
            handler->result = -2;
        } else {
            obj->next_state = 4;
        }
    }
}

#if STAGE != 1
void enemy_fire_burst(Object *obj, ObjHandler *handler);
#endif

/* Shooting enemy: turns towards the player, then (when its animation is done) either fires or ends. */
void enemy_shoot_update(Object *obj, ObjHandler *handler) {
    s32 *player;
    s32 roll;
    s32 old_yaw;
    s16 yaw;
    s16 target;
    s32 turn;
    s32 result;

    switch (handler->result) {
    case -2:
        enemy_start_burst(obj, handler, 6);
        return;
    case -1:
        enemy_fire_burst(obj, handler);
        return;
    default:
        player = player_position();
        target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
        old_yaw = obj->yaw;
        yaw = angle_approach(old_yaw, target, 0x20);
        turn = yaw;
        obj->yaw = yaw;
        turn -= old_yaw;
        obj->turn = turn;
        if (obj->script_flag == 0xFF) {
            if (obj->vars.enemy.shot_timer != 0) {
                if (obj->vars.smg_soldier.unk_274 == 0) {
                    roll = rand_a_next();
                    obj->next_state = roll > 0xC00 ? 3 : 4;
                    handler->result = -2;
                    if (obj->vars.enemy.sound != 0) {
                        if (obj->vars.enemy.sound != SOUND_PENDING) {
                            sound_stop(obj->vars.enemy.sound);
                        }
                        obj->vars.enemy.sound = 0;
                    }
                    obj->vars.enemy.shots_left = 0;
                } else {
                    enemy_muzzle_shot(obj);
                }
            }
            obj->vars.enemy.shot_timer = rand_a_next() & 7;
            result = -1;
        } else {
            result = 1;
        }
        handler->result = result;
        return;
    }
}

void smg_soldier_update(Object *obj, ObjHandler *handler) {
    enemy_sense(obj);
    if (obj->vars.smg_soldier.player_distance < obj->vars.smg_soldier.engage_distance || obj->vars.smg_soldier.unk_250 != 0) {
        if (obj->next_state < 3) {
            if (obj->next_state > 0) {
                if (ABS((obj->y >> 12) - player_position()[1]) < 0x1E0) {
                    if (obj->vars.smg_soldier.unk_274 != 0) {
                        obj->next_state = 3;
                    }
                }
            }
        }
    }
    if (obj->vars.smg_soldier.unk_266 == 0 && obj->vars.smg_soldier.unk_250 == 0) {
        if (obj->next_state == 5 || obj->next_state == 7) {
            obj->speed = 0;
        } else if (obj->vars.smg_soldier.unk_269 != 0 && obj->vars.smg_soldier.unk_274 != 0) {
            obj->next_state = 5;
        } else if (obj->vars.enemy.mode != 2 && obj->vars.enemy.mode != 4) {
            obj->next_state = 6;
        }
    }
    if (obj->next_state == 5 || obj->next_state == 7) {
        if (ABS((obj->y >> 12) - player_position()[1]) > 0x1E0) {
            obj->next_state = 2;
            if (obj->vars.enemy.sound != 0) {
                if (obj->vars.enemy.sound != SOUND_PENDING) {
                    sound_stop(obj->vars.enemy.sound);
                }
                obj->vars.enemy.sound = 0;
            }
        }
    }
    obj_script_step(obj, handler);
    enemy_hit_update(obj);
}

/* One step of the object's spawn script (sound handle and state live in vars). Returns 0 once it has spawned
 * its child and 1 while it is still waiting. */
void enemy_reset(Object *obj);
s32 enemy_spawn_step(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 base;
    s32 pitch;
    s32 hit;
    s32 next;
    s16 *pc;
    s32 tbl;

    if (obj->vars.enemy.sound != 0) {
        if (obj->vars.enemy.sound != SOUND_PENDING) {
            sound_stop(obj->vars.enemy.sound);
        }
        obj->vars.enemy.sound = 0;
    }
    switch (obj->vars.snd.sound) {
    case -1:
        enemy_reset(obj);
        hit = (u8)obj->hit_type;
        if (hit < 3 && hit != 0) {
            *(s32 *)&obj->vars.enemy.mode = 8;
            ((Script *)obj)->state.b = 2;
            pc = smg_soldier_hit_script.pc;
            tbl = (s32)smg_soldier_data;
            script_jump((Script *)obj, pc, tbl);
            next = 0x34;
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
        base = obj->type.unk_0E;
        object_spawn_at(pos, rot, base + model_slot_pchr(*(s32 *)obj->asset));
        placement_list_pop((ListRecord *)obj->placement);
        ((u8 *)obj->placement)[4] = (((u8 *)obj->placement)[4] & 0xFC) | 2;
        return 0;
    default:
        next = obj->vars.snd.sound - 1;
        break;
    }
    obj->vars.snd.sound = next;
    return 1;
}

void enemy_destroy(Object *obj) {
    s32 sound = obj->vars.enemy.sound;

    if (sound != 0) {
        if (sound != SOUND_PENDING) {
            sound_stop(sound);
        }
        obj->vars.enemy.sound = 0;
    }
}

#if STAGE == 1
s32 smg_soldier_spawn(Placement *place) {
    Object *obj;
    s16 *angles;
    s16 **slot;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    enemy_init(obj, place);
    enemy_script_start(obj, smg_soldier_script, smg_soldier_jump_table);
    *(s16 *)obj->vars.enemy.unk_260 = 0x500;
    obj->handlers[1].fn = smg_soldier_update;
    obj->callback = (s32)enemy_spawn_step;
    obj->destructor = enemy_destroy;
    obj->asset = smg_soldier_asset;
    obj->state_table = smg_soldier_states;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->sounds = smg_soldier_sounds;
    slot = smg_soldier_data;
    script_start((Script *)obj, *slot, (s32)slot);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 4, 0x1666);
    angles = (s16 *)obj->vars.enemy.unk_276;
    angles[0] = (-(s16)obj->height * 3) / 4 + 0x14;
    return 1;
}
#endif

#if STAGE == 8 || STAGE == 10
extern s32 D_80117344[];
extern s16 *smg_soldier_script[];
extern s32 D_8011737C[];
extern s16 *smg_soldier_jump_table[];
extern u8 smg_soldier_asset[], D_80117390[], D_80117058[];
extern u8 D_80116FB0[], D_80117058[];
extern StateEntry smg_soldier_states[];
extern u8 D_80116FB0[], D_80117390[];
extern SoundVolume smg_soldier_sounds[];
/* Same code as func_800B9568 (s01). */
s32 smg_soldier_spawn(Placement *place) {
    Object *obj;
    s16 *angles;
    s16 **slot;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    enemy_init(obj, place);
    enemy_script_start(obj, smg_soldier_script, smg_soldier_jump_table);
    *(s16 *)obj->vars.enemy.unk_260 = 0x500;
    obj->handlers[1].fn = smg_soldier_update;
    obj->callback = (s32)enemy_spawn_step;
    obj->destructor = enemy_destroy;
    obj->asset = smg_soldier_asset;
    obj->state_table = smg_soldier_states;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->sounds = smg_soldier_sounds;
    slot = smg_soldier_data;
    script_start((Script *)obj, *slot, (s32)slot);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 4, 0x1666);
    angles = (s16 *)obj->vars.enemy.unk_276;
    angles[0] = (-(s16)obj->height * 3) / 4 + 0x14;
    return 1;
}
#endif

#if STAGE == 12
extern s16 *smg_soldier_script[];
extern s16 *smg_soldier_jump_table[];
extern u8 D_80116FB0[], D_80117390[], D_80117058[];
void enemy_script_start();
void smg_soldier_update();
s32 enemy_spawn_step(Object *obj);
void enemy_destroy();
extern u8 D_8011737C[], D_80117344[], smg_soldier_asset[], D_80117390[], D_80117058[];
extern u8 D_8011737C[], D_80117344[], D_80116FB0[], D_80117058[];
extern StateEntry smg_soldier_states[];
extern u8 D_8011737C[], D_80117344[], D_80116FB0[], D_80117390[];
extern SoundVolume smg_soldier_sounds[];
extern s16 *smg_soldier_data[9];
/* Same code as func_800B9568 (s01). */
s32 smg_soldier_spawn(Placement *place) {
    Object *obj;
    s16 *angles;
    s16 **slot;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    enemy_init(obj, place);
    enemy_script_start(obj, smg_soldier_script, smg_soldier_jump_table);
    *(s16 *)obj->vars.enemy.unk_260 = 0x500;
    obj->handlers[1].fn = smg_soldier_update;
    obj->callback = (s32)enemy_spawn_step;
    obj->destructor = enemy_destroy;
    obj->asset = smg_soldier_asset;
    obj->state_table = smg_soldier_states;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->sounds = smg_soldier_sounds;
    slot = smg_soldier_data;
    script_start((Script *)obj, *slot, (s32)slot);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 4, 0x1666);
    angles = (s16 *)obj->vars.enemy.unk_276;
    angles[0] = (-(s16)obj->height * 3) / 4 + 0x14;
    return 1;
}
#endif
