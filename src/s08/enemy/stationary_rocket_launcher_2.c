/* stationary_rocket_launcher_2: one of s08's own original source files (scripts/objmap.py); part of src/s08/main.c's unit, included there. */

extern s32 rocket_params, D_80120750, D_80120754;
extern s16 D_8012075A;
extern s16 D_8012075E;
extern s16 D_80120760;
extern s16 D_80120762;
extern s16 D_80120766;
extern s16 D_80120768;
extern s16 D_80120758;
extern s16 D_8012075C;
extern s16 D_80120764;
extern s16 D_8012076A;
extern s16 D_8012076C;
extern s16 D_8012076E;
void rocket_params_init(void) {
    s32 k = 0x2A;
    D_8012075A = 2;
    rocket_params = 0x6000;
    D_80120750 = 0x12000;
    D_80120754 = 0x555;
    D_8012075C = k;
    D_8012075E = 0x48;
    D_80120760 = 0xC;
    D_80120762 = 0xC;
    D_80120766 = 3;
    D_80120768 = 0xE;
    D_80120758 = 0xA;
    D_80120764 = k;
    D_8012076A = 0;
    D_8012076C = k;
    D_8012076E = 0x80;
}

/* Same code as func_800B7534 (s01). */
void stationary_rocket_launcher_2_phase0(Object *obj) {
    if (obj->health > 0) {
        obj_link_script_run();
    }
}


/* Transforms the vector at src by the rotation matrix and translation (MAC = (RT * IR + TR) >> 12) and
 * stores MAC1-3 at dst.
 * Hand-written in the original. */
void rotate_vector_int(s32 *src, s32 *dst) {
    gte_load(IR1, src, 0);
    gte_load(IR2, src, 4);
    gte_load(IR3, src, 8);
    gte_rtirtr();
    gte_store(MAC1, dst, 0);
    gte_store(MAC2, dst, 4);
    gte_store(MAC3, dst, 8);
}


void obj_angles_to_player(Object *obj, s32 *yaw, s32 *pitch) {
    VECTOR *pos = (VECTOR *)scratch_alloc(0x10);
    s32 *m;
    s32 a, b, c;

    player_position_copy(pos);
    m = &obj->vars.stationary_rocket_launcher_2.unk_248;
    gte_load_R012(m, a, b, c);
    gte_load_R34(m, a, b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    pos->vx -= obj->x >> 12;
    pos->vy -= obj->y >> 12;
    pos->vz -= obj->z >> 12;
    rotate_vector_int((s32 *)pos, (s32 *)pos);
    vector_to_angles(pos->vx, pos->vy, pos->vz, yaw, pitch);
    scratch_top -= 0x10;
}

/* Converts the matrix to three angles (matrix_to_angles takes the second and third ones in the order
 * &angles[1], &angles[0], &angles[2]) and stores the first three as halfwords at out. */
void matrix_to_angles_s16(void *matrix, s16 *out) {
    s32 *angles = scratch_alloc(0x10);

    matrix_to_angles(matrix, &angles[1], &angles[0], &angles[2]);
    out[0] = angles[0];
    out[1] = angles[1];
    out[2] = angles[2];
    scratch_top -= 0x10;
}

void vec_rotate_by_matrix(volatile s32 *m, s32 *vec) {
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
    rotate_vector_int(vec, vec);
}

void vec_rotate_by_matrix(volatile s32 *m, s32 *vec);
extern s32 rocket_params;
/* Builds an offset (0, -0x8C, 0x28) turned by the object's matrix, adds the object's position
 * and passes the result to shot_spawn_obj. */
void stationary_rocket_launcher_2_fire_rocket(Object *obj, s32 a1, s32 a2) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);
    void *mat = scratch_alloc(0x20);

    rot_matrix(mat, a1, a2, 0);
    mul_matrix(&obj->vars, mat, mat);
    pos[1] = -0x8C;
    pos[0] = 0;
    pos[2] = 0x28;
    vec_rotate_by_matrix(mat, pos);
    pos[0] = (obj->x >> 12) + pos[0];
    pos[1] = (obj->y >> 12) + pos[1];
    pos[2] = (obj->z >> 12) + pos[2];
    matrix_to_angles_s16(mat, rot);
    shot_spawn_obj(pos, (u16 *)rot, 2, (s32)&rocket_params);
    scratch_top -= 0x38;
}

void obj_angles_to_player(Object *obj, s32 *yaw, s32 *pitch);
/* Behaviour step on handler->result: -2 marks it done (unk_0C = -1, result = 0x1E), -1 advances
 * with obj_request_state. On 15 it takes the angle from obj_angles_to_player, rounds it to a multiple of 0x200
 * and calls stationary_rocket_launcher_2_fire_rocket there and 0x200 either side of it. */
void stationary_rocket_launcher_2_volley(Object *obj, ObjHandler *handler) {
    s32 angle;
    s32 unk;

    switch (handler->result) {
    case -2:
        handler->queued_entry = -1;
        handler->result = 0x1E;
        return;
    case -1:
        obj_request_state(obj, handler, 4, 0);
        return;
    case 15:
        obj_angles_to_player(obj, &angle, &unk);
        angle = ((angle + 0x100) >> 9) << 9;
        sound_play_at(SND_ROCKET_SALVO_FIRE | SND_GROUP(1), 0x60, 0x3C, &obj->x);
        stationary_rocket_launcher_2_fire_rocket(obj, angle, 0x100);
        stationary_rocket_launcher_2_fire_rocket(obj, angle + 0x200, 0x100);
        stationary_rocket_launcher_2_fire_rocket(obj, angle - 0x200, 0x100);
        return;
    }
}

/* Same code as func_800BB92C (s01). */
void stationary_rocket_launcher_2_update(Object *obj, ObjHandler *handler) {
    if (obj->health > 0) {
        obj_script_step(obj, handler);
    }
}

void stationary_rocket_launcher_2_init(void) {
    rocket_params_init();
}

extern u8 stationary_rocket_launcher_2_asset[];
extern s16 *stationary_rocket_launcher_2_jumps[];
extern s16 *D_80117B08[];
extern s16 *stationary_rocket_launcher_2_data[];
extern ScriptCallEntry stationary_rocket_launcher_2_script_calls[];
extern StateEntry stationary_rocket_launcher_2_states[];
extern SoundVolume stationary_rocket_launcher_2_sounds[];
s32 stationary_rocket_launcher_2_spawn(Placement *placement) {
    Object *obj;
    s16 *anim_frame;
    register s32 ret asm("$2");

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        placement->unk_02 = -1;
        obj->handlers[0].fn = (void (*)(Object *, ObjHandler *))stationary_rocket_launcher_2_phase0;
        obj->handlers[1].fn = stationary_rocket_launcher_2_update;
        obj->handlers[2].fn = obj_run_states_default;
        obj->handlers[3].fn = obj_draw_spark;
        obj->callback = (s32)obj_respawn;
        obj->asset = stationary_rocket_launcher_2_asset;
        obj->hit_cooldown_max = 0x30;
        obj->call_table = stationary_rocket_launcher_2_script_calls;
        obj->state_table = stationary_rocket_launcher_2_states;
        obj->sounds = stationary_rocket_launcher_2_sounds;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->kind = 0;
        obj->unk_1C6 = 0;
        anim_frame = D_80117B08[0];
        obj->script.data = stationary_rocket_launcher_2_jumps;
        obj->script.unk_0A = 0;
        obj->script.pc = anim_frame;
        script_start((Script *)obj, (s16 *)stationary_rocket_launcher_2_data[0], (s32)stationary_rocket_launcher_2_data);
        obj_init_from_place(obj, placement, 0x25);
        obj_set_part_bounds(obj, 1, 0x1000);
        obj_hit_set_unk08(obj->index, 4);
        obj_hit_set_unk06(obj->index, 2);
        rot_matrix(&obj->vars, obj->yaw, -obj->pitch, obj->roll);
        ret = 1;
        D_80120758 = obj->damage;
    } else {
        ret = 0;
    }
    return ret;
}


s32 obj_respawn(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 kind;
    Placement *placement;
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    rot[2] = (u16)obj->roll;
    kind = *(s16 *)&obj->type.unk_0E;
    object_spawn_at(pos, rot, kind + model_slot_pchr(*(s32 *)obj->asset));
    placement_list_pop((ListRecord *)obj->placement);
    placement = obj->placement;
    placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
    return 0;
}


/* Distance from the object to the player. The object's script cursor reads a
   (threshold, index) pair; when the distance is at most the threshold, the cursor
   jumps to the entry at index in the object's table. */
void obj_jump_if_near(Object *obj) {
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

void obj_hit_player_in_front(Object *obj) {
    s32 *player;
    s32 bearing;
    s32 yaw;
    s32 yaw_hi;
    s32 diff;
    s16 damage;

    if (isqrt(length_sq((cam_pos >> 12) - (obj->x >> 12), (cam_pos_y >> 12) - (obj->y >> 12),
                        (cam_pos_z >> 12) - (obj->z >> 12))) < 0x164) {
        player = player_position();
        bearing = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
        yaw = obj->yaw;
        yaw_hi = yaw << 16; /* yaw in the upper half: >> 16 re-sign-extends it */
        diff = bearing - yaw;
        if (diff >= 0) {
            diff = bearing - (yaw_hi >> 16);
        } else {
            diff = yaw - bearing;
        }
        if (diff < 0x201) {
            damage = obj->damage / 2;
            hit_target_masked(0, 0x10, bearing, damage);
        }
    }
}

void obj_hit_player_in_front(Object *obj);

extern s16 *D_80117E94[];
void enemy_state_pick(Object *obj, ObjHandler *handler, s16 next_state) {
    s32 threshold;
    s16 **slot;

    if (obj->vars.axe_soldier.unk_269 != 0) {
        threshold = *(s16 *)&obj->vars.enemy.unk_260[0] * 3;
        if (threshold < 0) {
            threshold += 3;
        }
        if (obj->vars.axe_soldier.player_distance < (threshold >> 2)) {
            if (rand_a_next() < 0xC01) {
                if (rand_a_next() >= 0xC01) {
                    obj->next_state = next_state;
                    return;
                }
                handler->result = -2;
                slot = D_80117E94;
                script_start((Script *)obj, *slot, (s32)slot - 0x18);
                return;
            }
            obj->next_state = 1;
            return;
        }
    }
    if (obj->vars.axe_soldier.unk_268 == 0) {
        obj->next_state = 1;
    } else {
        obj->next_state = 3;
    }
}
void enemy_approach_player(Object *obj, ObjHandler *handler) {
    s32 *player;
    s32 match;
    s32 yaw;
    s32 new_yaw;
    s32 turn;
    s16 target;

    if (handler->result == -2) {
        handler->result = -1;
        obj->speed = 0;
        if (obj->vars.axe_soldier.unk_269 != 0) {
            if (rand_a_next() >= 0xC01) {
                obj->next_state = 7;
            }
        } else {
            obj->next_state = 1;
        }
    }
    match = 0;
    if (obj->script_flag == -1) {
        match = obj->next_state == handler->state;
    }
    if (match != 0) {
        enemy_state_pick(obj, handler, 7);
    }
    if (obj->script_flag == 0xFF) {
        obj_hit_player_in_front(obj);
    }
    player = player_position();
    target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    yaw = obj->yaw;
    new_yaw = angle_approach(yaw, target, 0x18);
    turn = (s16)new_yaw;
    turn -= yaw;
    obj->yaw = new_yaw;
    obj->turn = turn;
    fly_move(obj->yaw, obj->speed, &obj->vz, &obj->vx);
}

void enemy_track_player(Object *obj, ObjHandler *handler) {
    s32 *player;
    s32 pick;
    s16 target;
    s32 yaw;
    s32 new_yaw;
    s32 turn;

    if (handler->result == -2) {
        handler->result = -1;
        obj->speed = 0;
        if (obj->vars.axe_soldier.unk_269 != 0) {
            if (rand_a_next() >= 0xC01) {
                obj->next_state = 5;
            }
        } else {
            obj->next_state = 1;
        }
    }
    pick = 0;
    if (obj->script_flag == -1) {
        pick = obj->next_state == handler->state;
    }
    if (pick != 0) {
        enemy_state_pick(obj, handler, 5);
    }
    if (obj->script_flag == 0xFF) {
        obj_hit_player_in_front(obj);
    }
    player = player_position();
    target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    yaw = obj->yaw;
    new_yaw = angle_approach(yaw, target, 0x18);
    turn = (s16)new_yaw;
    turn -= yaw;
    obj->yaw = new_yaw;
    obj->turn = turn;
    fly_move(obj->yaw, obj->speed, &obj->vz, &obj->vx);
}

void axe_soldier_update(Object *obj, ObjHandler *handler) {
    s16 state;

    enemy_sense(obj);
    if ((obj->vars.axe_soldier.player_distance < obj->vars.axe_soldier.engage_distance) || (obj->vars.axe_soldier.unk_250 != 0)) {
        state = obj->next_state;
        if (state < 3) {
            if (state > 0) {
                obj->next_state = 3;
            }
        }
    }
    if ((obj->vars.axe_soldier.unk_266 == 0) && (obj->vars.axe_soldier.unk_250 == 0)) {
        state = obj->next_state;
        if ((state == 5) || (state == 7)) {
            obj->speed = 0;
        } else if (obj->vars.axe_soldier.unk_269 == 0) {
            obj->next_state = 6;
        }
    }
    obj_script_step(obj, handler);
    enemy_hit_update(obj);
}

extern ScriptPcSlot axe_soldier_hit_pc;
extern s16 *axe_soldier_data[];
void enemy_reset(Object *obj);
s32 axe_soldier_dying(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 next;
    s32 base, pitch;
    s32 hit;

    switch (obj->vars.snd.sound) {
    case -1:
        enemy_reset(obj);
        if (obj->unk_1B7 != 0) {
            hit = (u8)obj->hit_type;
            if (hit < 3 && hit != 0) {
                obj->vars.axe_soldier.unused_248 = 8;
                obj->type.unk_0A = 2;
                script_jump((Script *)obj, axe_soldier_hit_pc.pc, (s32)axe_soldier_data);
                next = 0x3E;
            } else {
                next = 4;
            }
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
        obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
        return 0;
    default:
        next = obj->vars.snd.sound - 1;
        break;
    }
    obj->vars.snd.sound = next;
    return 1;
}

extern s16 *D_80117F9C[];
extern s16 *axe_soldier_jumps[];
extern s32 axe_soldier_asset[];
extern StateEntry axe_soldier_states[];
extern SoundVolume D_80117BFC[];
extern s16 *axe_soldier_data[];
s32 axe_soldier_dying(Object *obj);
/* Spawns the object from a placement record; returns 1 if it was created, 0 if the pool was full. */
s32 axe_soldier_spawn(Placement *place) {
    Object *obj;
    s16 **script_pc;
    SoundVolume *unk_19C_src;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    enemy_init(obj, place);
    enemy_script_start(obj, D_80117F9C, axe_soldier_jumps);
    if (obj->vars.enemy.mode >= 3) {
        obj->vars.enemy.mode = 0;
    }
    *(s16 *)obj->vars.enemy.unk_260 = 0x218;
    obj->handlers[1].fn = axe_soldier_update;
    obj->callback = (s32)axe_soldier_dying;
    obj->asset = axe_soldier_asset;
    obj->state_table = axe_soldier_states;
    unk_19C_src = D_80117BFC;
    script_pc = axe_soldier_data;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->sounds = unk_19C_src;
    script_start((Script *)obj, *script_pc, (s32)script_pc);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 1, 0x1666);
    return 1;
}
