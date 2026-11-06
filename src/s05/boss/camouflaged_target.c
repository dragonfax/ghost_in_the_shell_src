/* camouflaged_target: one of s05's own original source files (scripts/objmap.py); part of src/s05/main.c's unit, included there. */

extern GridEntry *flagged_grid_cells[];
/* Same code as get_key_table (s01). */
GridEntry **grid_get_flagged_list(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 grid_get_flagged_count(void) {
    return grid_flagged_count;
}

extern s32 spawn_effects_flag;
void rotate_vector_xyz(s32 angle_x, s32 angle_y, s32 angle_z, s32 *px, s32 *py, s32 *pz);
/* Fades both camouflage shimmers down by 42 a step; every 48 steps, at random, starts one side at full
 * and plays sound 0x5087 at a point on the model, offset to that side. */
void camouflaged_target_m5_boss_phase0(Object *obj, ObjHandler *handler) {
    Vec3 *pos;
    M5BossPart *part;
    s32 left = obj->vars.camo.fade_left - 42;
    s32 right = obj->vars.camo.fade_right - 42;
    s32 clamped; /* the value stored: clamped to [0, 0x1000] */
    s32 limit;   /* the same upper clamp, evaluated again for the sign test */
    s16 timer;

    clamped = left;
    if (clamped > 0x1000) {
        clamped = 0x1000;
    }
    limit = left;
    if (limit > 0x1000) {
        limit = 0x1000;
    }
    if (limit < 0) {
        clamped = 0;
    }
    obj->vars.camo.fade_left = clamped;
    clamped = right;
    if (clamped > 0x1000) {
        clamped = 0x1000;
    }
    limit = right;
    if (limit > 0x1000) {
        limit = 0x1000;
    }
    if (limit < 0) {
        clamped = 0;
    }
    obj->vars.camo.fade_right = clamped;
    obj_link_script_run(obj, handler);
    timer = obj->vars.camo.timer + 1;
    obj->vars.camo.timer = timer;
    do {
    } while (0); /* keeps the store above spawn_effects_flag's load */
    if (spawn_effects_flag == 0 && timer % 48 == 0 && rand_a_next() < 0x800
        && obj->vars.camo.model != NULL) {
        pos = scratch_alloc(0x10);
        part = &obj->vars.camo.model->part;
        if (rand_a_next() < 0x800) {
            pos->x = -21;
            pos->y = -51;
            pos->z = -3;
            obj->vars.camo.fade_left = 0x1000;
        } else {
            pos->x = 20;
            pos->y = -51;
            pos->z = -3;
            obj->vars.camo.fade_right = 0x1000;
        }
        rotate_vector_xyz(part->rot_y, part->rot_x, part->rot_z, &pos->x, &pos->y, &pos->z);
        pos->x += part->x;
        pos->y += part->y;
        pos->z += part->z;
        rotate_xz_twice(obj->yaw, -obj->pitch, &pos->x, &pos->y, &pos->z);
        pos->x += obj->x >> 12;
        pos->y += obj->y >> 12;
        pos->z += obj->z >> 12;
        sound_play_at_units(SND_ZAT | SND_GROUP(2), 0x7F, 0x3C, pos);
        scratch_top -= 0x10;
    }
}

extern u16 D_80117FB8[];
extern ScriptParamEntry D_80117EE4[2];
extern ScriptParamEntry D_80117F3C[2];
extern ScriptParamEntry D_80117F8C[2];
extern ScriptParamEntry D_80117FAC[1];
void script_store_stage_param(s16 *arg0) {
    s32 i;
    s32 idx;
    s32 lt;
    volatile u16 *p;

    i = arg0[0xD] - 1;
    lt = i < 10;
    idx = i;
    if (!lt) {
        idx = 9;
    }
    FAKE_OPAQUE(lt);
    if (!lt) {
        i = 9;
    }
    if (i < 0) {
        idx = 0;
    }
    FAKE_OPAQUE(idx);
    {
        u8 *base = (u8 *)D_80117FB8;
        u32 off = idx * 2;
        p = (volatile u16 *)(off + base);
    }
    D_80117EE4[0].param = *p;
    D_80117F3C[0].param = *p;
    D_80117F8C[0].param = *p;
    D_80117FAC[0].param = *p;
}

extern u16 obj_type_param_table[];
extern u16 D_80117EF4[];
extern u16 D_80117FB4[];
void obj_type_params_set(Object *obj, s32 arg1) {
    s32 index = obj->type.unk_0E - 0x21;

    index = MAX(MIN(index, 29), 0);
    D_80117EF4[0] = obj_type_param_table[index];
    D_80117FB4[0] = obj_type_param_table[index];
}

extern ScriptParamEntry D_80117EFC[1];
extern u16 D_80118008[];
void obj_type_param_store_a(ObjHandler *handler)
{
    s32 index = handler->timer - 0x21;

    index = MIN(index, 29) < 0 ? 0 : MIN(index, 29);
    D_80117EFC[0].param = D_80118008[index];
}

extern u16 D_80118044[];
extern ScriptParamEntry D_80117F04[7];
/* Same code as obj_type_param_store_a (s05). */
void obj_type_param_store_b(ObjHandler *handler)
{
    s32 index = handler->timer - 0x21;

    index = MIN(index, 29) < 0 ? 0 : MIN(index, 29);
    D_80117F04[0].param = D_80118044[index];
}

extern u16 shot_homing_param_table[];
extern ScriptParamEntry shot_homing_param[8];
void shot_homing_store_type_param(Object *obj, s32 arg)
{
    s32 index = obj->type.unk_0E - 0x21;

    index = MIN(index, 29) < 0 ? 0 : MIN(index, 29);
    shot_homing_param[0].param = shot_homing_param_table[index];
}

extern u16 chase_player_param_table[];
extern ScriptParamEntry chase_player_param[2];
void chase_player_store_type_param(Object *obj, ObjHandler *handler)
{
    s32 index = obj->type.unk_0E - 0x21;

    index = MIN(index, 29) < 0 ? 0 : MIN(index, 29);
    chase_player_param[0].param = chase_player_param_table[index];
}

void set_d_80118190(s32 arg0);

void script_op_power_switch(Object *obj) {
    VECTOR *pos;
    s16 *cursor;
    s32 height;
    s32 y;

    pos = scratch_alloc(0x10);
    pos->vx = obj->x >> 12;
    height = (s16)obj->height;
    y = obj->y >> 12;
    pos->vy = y - height / 2;
    pos->vz = obj->z >> 12;
    sound_scale_pos_about_listener(pos, pos, 0x800);
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    if (*cursor == 1) {
        sound_play_at_units(SND_POWER_ON, 0x7F, 0x3C, pos);
        set_d_80118190(1);
    } else {
        sound_play_at_units(SND_POWER_ON, 0x7F, 0x3C, pos);
        set_d_80118190(0);
    }
    scratch_top -= 0x10;
}

extern u16 D_80117C86;
extern u16 D_80117D4E;
void cursor_read_u16_mirror2(ReadCursor *cursor) {
    u16 *p;
    u16 value;

    p = (u16 *) cursor->cursor;
    cursor->cursor = (u8 *)p + 2;
    value = *p;
    D_80117C86 = value;
    D_80117D4E = value;
}

extern u16 D_80117C9C;
extern u16 D_80117CB4;
extern u16 D_80117CC8;
extern u16 D_80117CE0;
extern u16 D_80117CFC;
extern u16 D_80117D14;
/* Reads one u16 from the cursor, advances it, and copies the value to six globals. */
void cursor_read_u16_mirror6(ReadCursor *stream) {
    u16 *p;
    u16 value;

    p = (u16 *) stream->cursor;
    stream->cursor = (u8 *) (p + 1);
    value = *p;
    D_80117C9C = value;
    D_80117CB4 = value;
    D_80117CC8 = value;
    D_80117CE0 = value;
    D_80117CFC = value;
    D_80117D14 = value;
}

void stream_read_u16(StreamObj *obj) {
    u8 *cursor = obj->cursor;
    u16 value;

    obj->cursor = cursor + 2;
    value = *(u16 *)cursor;
    obj->unk_258 = 0;
    obj->value = value;
}

void script_op_health_jump(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;
    s32 health;
    s32 health_mark;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if (get_clamp_row() != 5) {
        health = obj->health;
        health_mark = obj->vars.camouflaged_target_m5_boss.health_mark;
        if (health_mark == health || obj->vars.camouflaged_target_m5_boss.unk_258 >= 0x4B1) {
            obj->script.pc = ((s16 **)obj->script.data)[index];
        }
    }
}

extern s32 meter_mode_cmd;
s32 get_d_80118194(void);
void script_op_meter_mode(ScriptMeterCtx *self) {
    s16 *p;
    s16 cmd;
    s32 idle_a;
    s8 idle_b;

    p = self->cursor;
    self->cursor = p + 1;
    cmd = *p;
    meter_mode_cmd = cmd;
    idle_a = 0;
    if (cmd != 0) {
        idle_a = get_d_80118194() == 0;
    }
    meter_set_mode(idle_a);
    idle_b = 0;
    if (cmd != 0) {
        idle_b = get_d_80118194() == 0;
    }
    self->flag_17A = idle_b;
}

char str_bos5_tp0_clt[16] RODATA = "bos5_tp0.clt";

char str_bos5_ch0_clt[16] RODATA = "bos5_ch0.clt";

char str_bos5_ch3_vx1[16] RODATA = "bos5_ch3.vx1";

char str_bos5_ch2_vx1[16] RODATA = "bos5_ch2.vx1";

char str_bos5_ch1_vx1[16] RODATA = "bos5_ch1.vx1";

char str_bos5_ch0_vx1[16] RODATA = "bos5_ch0.vx1";

char str_bos5_tp1_xs3[16] RODATA = "bos5_tp1.xs3";

char str_bos5_tp0_xs3[16] RODATA = "bos5_tp0.xs3";

char str_bos5_ch3cb4[16] RODATA = "bos5_ch3.cb4";

char str_bos5_ch2cb4[16] RODATA = "bos5_ch2.cb4";

char str_bos5_ch1cb4[16] RODATA = "bos5_ch1.cb4";

char str_bos5_ch0cb4[16] RODATA = "bos5_ch0.cb4";

s32 zone_contains_pos(s32 key, VECTOR *pos, s32 range);
/* Script op: reads a key and a table index; zone_contains_pos looks the key up with the vector from
 * player_position_copy. On a result of 1 the script jumps to the table entry, a message is shown (and the extra
 * calls run when the result equals the key), and target_select(0) runs. */
void script_op_target_lock(Object *obj) {
    VECTOR *vec = scratch_alloc(0x10);
    s32 key = obj_read_s16(obj);
    s32 index = obj_read_s16(obj);
    s32 result;

    player_position_copy(vec);
    result = zone_contains_pos(key, vec, 0x100);
    if (result == 1) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
        if (key == result) {
            show_line((s32)"#1Warning!  Warning! Moving object acknowledged.\xA1");
            msg_show_slot(1, 0xB4);
            warning_ack_set(1);
        } else {
            show_line((s32)"#2Target confirmed.\xA1");
        }
        target_select(0);
    }
    scratch_top -= 0x10;
}

void set_clamp_row(s32 code);
void script_op_clear_actors(Object *obj) {
    s16 *script;
    s16 cmd;

    script = obj->script.pc;
    obj->script.pc = script + 1;
    cmd = *script;
    set_clamp_row(cmd);
    if (cmd == 5) {
        obj_actors_clear_index();
        obj_hit_clear(obj->index);
        obj->score = 0x4E20;
        grid_active_set(0);
    }
}

extern s32 spawn_effects_flag;
void obj_spawn_effect_at(Object *obj, SpawnOffset *table, s32 index);
/* Plays the four spawn effects from the table at +0x25C, then clears spawn_effects_flag once the asset's
 * effect id is sent. Runs only while spawn_effects_flag is 1 and the table pointer is set. */
void obj_spawn_effects(Object *obj) {
    SpawnOffset *table = (SpawnOffset *)obj->vars.camouflaged_target_m5_boss.pose_table;

    if (table != NULL && spawn_effects_flag == 1) {
        obj_spawn_effect_at(obj, table, 0x18);
        obj_spawn_effect_at(obj, table, 0x10);
        obj_spawn_effect_at(obj, table, 0x19);
        obj_spawn_effect_at(obj, table, 0xF);
        pchr_set_entry_flags(model_slot_pchr(*(s32 *)obj->asset), 0x3C187E3);
        spawn_effects_flag = 0;
    }
}

/* Spawns an effect at the object's position plus table[index]'s offset, rotated by the object's yaw and pitch. */
void obj_spawn_effect_at(Object *obj, SpawnOffset *table, s32 index) {
    Vec3 *pos = scratch_alloc(0x10);
    SpawnOffset *entry = &table[index];

    pos->x = entry->x;
    pos->y = entry->y;
    pos->z = entry->z;
    rotate_xz_twice(obj->yaw, -obj->pitch, &pos->x, &pos->y, &pos->z);
    pos->x += obj->x >> 12;
    pos->y += obj->y >> 12;
    pos->z += obj->z >> 12;
    spawn_effect(pos->x, pos->y, pos->z, 0x80007F00);
    scratch_top -= 0x10;
}

extern s32 spawn_effects_flag;
/* Reads the next script halfword (cursor at +0x20). While spawn_effects_flag is 0 the cursor jumps to the
 * entry of the table (+0x1C) that the halfword selects; the inverse of script_branch_on_flag's flag. */
void script_op_jump_if_flag_clear(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if (spawn_effects_flag == 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op: reads the next script halfword (cursor at +0x20) as a table index. While the object's
 * obj_hit_damage result is positive and spawn_effects_flag == 1, the cursor jumps to the entry of the table
 * (+0x1C) that the halfword selects. */
void script_op_jump_if_ready(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if ((obj_hit_damage(obj->index) << 16) > 0 && spawn_effects_flag == 1) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op: the object's cursor reads a (threshold, index) pair. When the
   object's health is at most the threshold, the cursor jumps to the entry at
   index in the object's table. */
void script_op_jump_if_health_under(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 threshold;
    s32 index;

    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold >= obj->health) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_op_jump_if_near_point(Object *obj) {
    s16 *cursor;
    s32 threshold;
    s32 index;
    s32 dx;
    s32 dz;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    dx = obj->x;
    dx = (VEC_80139584.x - dx) >> 12;
    dz = (VEC_80139584.z - obj->z) >> 12;
    if (threshold >= isqrt(length_sq(dx, 0, dz))) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_op_jump_if_beyond_point(Object *obj) {
    s16 *cursor;
    s32 threshold;
    s32 index;
    s32 dx;
    s32 dz;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    dx = obj->x;
    dx = (VEC_80139584.x - dx) >> 12;
    dz = (VEC_80139584.z - obj->z) >> 12;
    if (threshold < isqrt(length_sq(dx, 0, dz))) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Picks a point a short flight from the target near the camera and stores it (z at vars[8], x at vars[9]). */
void camouflaged_target_pick_point(Object *obj) {
    s32 *center = scratch_alloc(0x10);
    s32 *extent = scratch_alloc(0x10);
    s32 speed = 0x800;
    s32 dz;
    s32 dx;
    s32 angle;
    s32 off[2];
    s32 *cam;
    s32 cx;
    s32 lim;
    s32 jitter;

    off[0] = 0;
    off[1] = 0;
    clamp_row_bounds(get_clamp_row(), center, extent);
    cam = &cam_pos;
    cx = *cam >> 12;
    dz = center[2] - (cam_pos_z >> 12);
    off[0] = dz;
    dx = center[0] - cx;
    lim = extent[0];
    off[1] = dx;
    if (lim < speed) {
        speed = lim;
    }
    if (extent[2] < speed) {
        speed = extent[2];
    }
    angle = atan2(dz, dx);
    jitter = rand_a_next();
    angle -= 0x200;
    angle += jitter / 4;
    fly_move(angle, speed, &off[0], &off[1]);
    obj->vars.camouflaged_target_m5_boss.target_z = (cam_pos_z + off[0]) >> 12;
    obj->vars.camouflaged_target_m5_boss.target_x = (*cam + off[1]) >> 12;
    off[0] = obj->vars.camouflaged_target_m5_boss.target_z - (obj->z >> 12);
    off[1] = obj->vars.camouflaged_target_m5_boss.target_x - (obj->x >> 12);
    if (isqrt(length_sq(off[1], 0, off[0])) < 0x200) {
        angle = atan2(off[0], off[1]);
        fly_move(angle, speed, &off[0], &off[1]);
        obj->vars.camouflaged_target_m5_boss.target_z = (obj->z + off[0]) >> 12;
        obj->vars.camouflaged_target_m5_boss.target_x = (obj->x + off[1]) >> 12;
    }
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}

void obj_surface_sound(Object *obj);
void boss_area_attack_step(Object *obj);
void fade_level_step(void);
void camouflaged_target_m5_boss_update(Object *obj, ObjHandler *handler) {
    s16 state;

    obj->vz = 0;
    obj->vx = 0;
    if (obj->script_flag != 0) {
        state = obj->next_state;
        if (state == handler->state) {
            switch (state) {
            case 1:
            case 4:
            case 5:
                obj->next_state = 2;
                break;
            case 3:
            case 8:
            case 9:
            case 10:
            case 11:
            case 19:
            case 21:
            case 25:
            case 27:
                obj->next_state = 0;
                obj->vars.camouflaged_target_m5_boss.unused_248 = 0;
                break;
            case 6:
                obj->next_state = 7;
                break;
            case 12:
                obj->next_state = 0xD;
                break;
            case 22:
                obj->next_state = 0x17;
                break;
            case 24:
                obj->next_state = 0x19;
                break;
            case 0:
            case 2:
            case 7:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 20:
            case 23:
            case 26:
                break;
            default:
                obj->next_state = 0;
                break;
            }
        }
    }
    obj_script_step(obj, handler);
    obj_surface_sound(obj);
    boss_area_attack_step(obj);
    fade_level_step();
    meter_set(obj->health, 0x4B00);
}

void func_800C093C(Object *obj) {
    s32 *pos;
    s32 target_yaw;
    s32 old_yaw;
    s32 new_yaw;
    s32 turn;

    /* turn the object's yaw toward the player's XZ position by at most 0x20 per call */
    pos = player_position();
    target_yaw = (s16) atan2(pos[2] - (obj->z >> 12), pos[0] - (obj->x >> 12));
    old_yaw = obj->yaw;
    new_yaw = angle_approach(old_yaw, target_yaw, 0x20);
    turn = (s16) new_yaw;
    turn -= old_yaw;
    obj->yaw = new_yaw;
    obj->turn = turn;
}

void obj_turn_toward_point(Object *obj);
void obj_flight_setup(Object *obj) {
    s32 dx;
    s32 dz;

    obj->vars.camouflaged_target_m5_boss.unk_252 = isqrt(length_sq(obj->vars.snd2.sound[1] - (obj->x >> 12), 0, obj->vars.snd2.sound[0] - (obj->z >> 12))) / 20;
    if (obj->type.unk_0C >= 0xD) {
        dx = 0;
        dz = 0;
        obj_turn_toward_point(obj);
        fly_move(obj->yaw, 0x14, &dx, &dz);
        obj->vz = dx;
        obj->vx = dz;
    }
}

void obj_type_params_set(Object *obj, s32 arg1);
/* Flying step: move along the yaw for 0x14 units, count the flight timer
 * down, and when it runs out switch the object to state 3. */
void obj_fly_step(Object *obj, s32 arg1) {
    s32 step_x;
    s32 step_z;
    s32 saved_x;
    u16 timer;

    step_x = 0;
    step_z = 0;
    obj_turn_toward_point(obj);
    fly_move(obj->yaw, 0x14, &step_x, &step_z);
    saved_x = step_x;
    timer = obj->vars.camouflaged_target_m5_boss.unk_252 - 1;
    obj->vars.camouflaged_target_m5_boss.unk_252 = timer;
    obj->vz = saved_x;
    obj->vx = step_z;
    obj->vars.camouflaged_target_m5_boss.unused_260 = saved_x; /* 0x260 */
    obj->vars.camouflaged_target_m5_boss.unused_264 = step_z; /* 0x264 */
    if ((timer << 16) <= 0) {
        obj->next_state = 3;
        obj_type_params_set(obj, arg1);
    }
}

void obj_restore_velocity(Object *obj) {
    if (obj->type.unk_0C < 0x41) {
        obj->vz = obj->vars.camouflaged_target_m5_boss.unused_260;
        obj->vx = obj->vars.camouflaged_target_m5_boss.unused_264;
    }
}

void obj_turn_toward_point(Object *obj) {
    s32 old_yaw;
    s32 new_yaw;
    s32 turn;

    old_yaw = obj->yaw;
    new_yaw = angle_approach(old_yaw, atan2(obj->vars.snd2.sound[0] - (obj->z >> 12), obj->vars.snd2.sound[1] - (obj->x >> 12)), 0x2A);
    turn = (s16) new_yaw;
    turn = turn - old_yaw;
    obj->yaw = new_yaw;
    obj->turn = turn;
}

void obj_turn_to_player_hit_reset(Object *obj) {
    s32 *pos;
    s32 target_yaw;
    s32 old_yaw;
    s32 new_yaw;
    s32 turn;

    /* turn toward the player by at most 0x20, then clear the hit flag */
    pos = player_position();
    target_yaw = (s16) atan2(pos[2] - (obj->z >> 12), pos[0] - (obj->x >> 12));
    old_yaw = obj->yaw;
    new_yaw = angle_approach(old_yaw, target_yaw, 0x20);
    turn = (s16) new_yaw;
    turn -= old_yaw;
    obj->yaw = new_yaw;
    obj->turn = turn;
    obj_hit_clear(obj->index);
}

extern s32 spawn_effects_flag;
s32 laser_slice_spawn(Object *unused, Vec3 *pos, SVECTOR *ang, s32 a, s32 kind);
/* Turns the object towards the player; while spawn_effects_flag == 1 and the counter at 0x248 is 0x14 it also
 * plays a sound at a point in front of the object and calls laser_slice_spawn. Counts 0x248 up. */
void obj_turn_fire_burst(Object *obj) {
    s32 *player = player_position();
    s16 target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    s32 old = obj->yaw;
    s16 yaw;
    s32 turn;
    s32 roll;
    Vec3 *pos;
    SVECTOR *ang;

    yaw = angle_approach(old, target, 0x20);
    turn = yaw;
    turn -= old;
    obj->turn = turn;
    obj->yaw = yaw;
    if (spawn_effects_flag == 1 && obj->vars.camouflaged_target_m5_boss.unused_248 == 0x14) {
        pos = scratch_alloc(0x10);
        ang = scratch_alloc(8);
        pos->x = 0x21;
        pos->y = -0xCA;
        pos->z = 0xA7;
        rotate_xz_twice(obj->yaw, -obj->pitch, &pos->x, &pos->y, &pos->z);
        ang->vx = obj->pitch;
        ang->vy = obj->yaw;
        roll = obj->roll;
        ang->vz = roll + 0x200;
        pos->x += obj->x >> 12;
        pos->y += obj->y >> 12;
        pos->z += obj->z >> 12;
        sound_play_at_units(SND_LASER_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
        laser_slice_spawn(obj, pos, ang, 0, model_slot_pchr(*(s32 *)obj->asset));
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
    obj->vars.camouflaged_target_m5_boss.unused_248++;
}

void obj_turn_to_player_yaw(Object *obj) {
    s32 *player;
    s32 roll;
    s16 target;
    s32 old_yaw;
    s16 new_yaw;
    s32 wide_yaw;

    player = player_position();
    target = (s16)atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    old_yaw = obj->yaw;
    new_yaw = angle_approach(old_yaw, target, 0x20);
    wide_yaw = new_yaw;
    obj->turn = wide_yaw - old_yaw;
    obj->yaw = new_yaw;

    if (spawn_effects_flag == 1) {
        if (obj->vars.camouflaged_target_m5_boss.unused_248 == 0x18) {
            Vec3 *pos = (Vec3 *)scratch_top;
            SVECTOR *ang;
            scratch_top += 0x10;
            ang = (SVECTOR *)scratch_top;
            scratch_top += 8;
            pos->x = 0x21;
            pos->y = -0xCA;
            pos->z = 0xA7;
            rotate_xz_twice(obj->yaw, -obj->pitch, &pos->x, &pos->y, &pos->z);
            ang->vx = obj->pitch;
            ang->vy = obj->yaw;
            roll = obj->roll;
            ang->vz = roll + 0x200;
            pos->x += obj->x >> 12;
            pos->y += obj->y >> 12;
            pos->z += obj->z >> 12;
            sound_play_at_units(SND_LASER_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
            laser_slice_spawn(obj, pos, ang, 0, model_slot_pchr(*(s32 *)obj->asset));
            scratch_top -= 8;
            scratch_top -= 0x10;
        }
    }
    if (obj->vars.camouflaged_target_m5_boss.unused_248 == 0x48) {
        Vec3 *pos = (Vec3 *)scratch_top;
        SVECTOR *ang;
        scratch_top += 0x10;
        ang = (SVECTOR *)scratch_top;
        scratch_top += 8;
        pos->x = -0x22;
        pos->y = -0xCA;
        pos->z = 0xA7;
        rotate_xz_twice(obj->yaw, -obj->pitch, &pos->x, &pos->y, &pos->z);
        ang->vx = obj->pitch;
        ang->vy = obj->yaw;
        roll = obj->roll;
        ang->vz = roll - 0x200;
        pos->x += obj->x >> 12;
        pos->y += obj->y >> 12;
        pos->z += obj->z >> 12;
        sound_play_at_units(SND_LASER_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
        laser_slice_spawn(obj, pos, ang, 0, model_slot_pchr(*(s32 *)obj->asset));
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
    obj->vars.camouflaged_target_m5_boss.unused_248 = (u16)obj->vars.camouflaged_target_m5_boss.unused_248 + 1;
}

/* Turns toward the player; on step 0x15 of its counter fires an effect from a muzzle offset. */
void obj_turn_fire_shot(Object *obj) {
    s32 *player;
    s32 old_yaw;
    s16 yaw;
    s16 target;
    s32 turn;
    s32 roll;
    Vec3 *pos;
    SVECTOR *rot;

    player = player_position();
    target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    old_yaw = obj->yaw;
    yaw = angle_approach(old_yaw, target, 0x20);
    turn = yaw;
    obj->yaw = yaw;
    turn -= old_yaw;
    obj->turn = turn;
    if (obj->vars.camouflaged_target_m5_boss.unused_248 == 0x15) {
        pos = scratch_alloc(0x10);
        rot = scratch_alloc(8);
        pos->x = -0x22;
        pos->y = -0x98;
        pos->z = 0xEB;
        rotate_xz_twice(obj->yaw, -obj->pitch, &pos->x, &pos->y, &pos->z);
        rot->vx = obj->pitch;
        rot->vy = obj->yaw;
        roll = obj->roll;
    rot->vz = roll - 0x400;
        pos->x += obj->x >> 12;
        pos->y += obj->y >> 12;
        pos->z += obj->z >> 12;
        sound_play_at_units(SND_LASER_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
        laser_slice_spawn(obj, pos, rot, 1, model_slot_pchr(*(s32 *)obj->asset));
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
    obj->vars.camouflaged_target_m5_boss.unused_248++;
}

void obj_fly_turn_to_player(Object *obj) {
    s32 fly_dx;
    s32 fly_dz;
    s32 target;
    s32 old;
    s32 new_yaw;
    s32 turn;
    s32 *player;

    if (obj->type.unk_0C >= 0xD) {
        fly_dz = 0;
        fly_dx = 0;
        player = player_position();
        target = (s16) atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
        old = obj->yaw;
        new_yaw = angle_approach(old, target, 0x2A);
        turn = (s16) new_yaw;
        turn -= old;
        obj->yaw = new_yaw;
        obj->turn = turn;
        fly_move(obj->yaw, 0x14, &fly_dx, &fly_dz);
        obj->vx = fly_dz;
        obj->vz = fly_dx;
    }
}

void shot_homing_store_type_param(Object *obj, s32 arg);
/* Turns toward the player and flies at it; within 0x400 units, switches to state 0xE. */
void shot_homing_update(Object *obj, s32 arg) {
    s32 *dir = scratch_alloc(0x10);
    s32 step_x;
    s32 step_z;
    s32 *ppos;
    s32 x;
    s32 z;
    s32 turn;
    s32 old_yaw;
    s16 yaw;
    s16 target;

    step_z = 0;
    step_x = 0;
    ppos = player_position();
    target = atan2(ppos[2] - (obj->z >> 12), ppos[0] - (obj->x >> 12));
    old_yaw = obj->yaw;
    yaw = angle_approach(old_yaw, target, 0x2A);
    turn = yaw;
    obj->yaw = yaw;
    turn -= old_yaw;
    obj->turn = turn;
    fly_move(obj->yaw, 0x14, &step_x, &step_z);
    obj->vx = step_z;
    obj->vz = step_x;
    x = obj->x;
    dir[0] = (VEC_80139584.x - x) >> 12;
    z = obj->z;
    dir[2] = (VEC_80139584.z - z) >> 12;
    if (isqrt(length_sq(dir[0], 0, dir[2])) < 0x401) {
        shot_homing_store_type_param(obj, arg);
        obj->next_state = 0xE;
    }
    scratch_top -= 0x10;
}

/* A projectile: when its life (type.unk_0C) is over 0x100 it drops toward the camera and plays a sound at its
 * position; otherwise it turns toward the player and flies. */
void projectile_home_update(Object *obj) {
    s32 sp10, sp14;
    Vec3 *pos;
    s32 *player;
    s32 old_yaw;
    s16 yaw;
    s16 target;
    s32 turn;
    s32 *drift;

    if (obj->type.unk_0C > 0x100) {
        register s32 div asm("$3") = 64;
        s32 obj_z = obj->z;
        register s32 cam_x asm("$6");
        drift = &obj->vars.camouflaged_target_m5_boss.unused_260;
        drift[0] = (VEC_80139584.z - obj_z) / div;
        drift[1] = (VEC_80139584.x - obj->x) / div;
        drift[2] = VEC_80139584.z >> 12;
        cam_x = VEC_80139584.x;
        cam_x >>= 12;
        drift[3] = cam_x;
        obj->vx = drift[1];
        obj->vz = drift[0];
        obj->unk_1B7 = 0;
        obj->vy = 0xFFFE0000;
        obj->next_state = 0xF;
        pos = scratch_alloc(0x10);
        pos->x = obj->x >> 12;
        pos->y = obj->y >> 12;
        pos->z = obj->z >> 12;
        sound_play_at_units(SND_PROJECTILE_LAUNCH | SND_GROUP(2), 0x7F, 0x3C, pos);
        scratch_top -= 0x10;
    } else {
        sp14 = 0;
        sp10 = 0;
        player = player_position();
        target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
        old_yaw = obj->yaw;
        yaw = angle_approach(old_yaw, target, 0x2A);
        turn = yaw;
        obj->yaw = yaw;
        turn -= old_yaw;
        obj->turn = turn;
        fly_move(obj->yaw, 0x14, &sp10, &sp14);
        obj->vx = sp14;
        obj->vz = sp10;
    }
}

void obj_airborne_step(Object *obj) {
    obj->vz = obj->vars.camouflaged_target_m5_boss.unused_260;
    obj->vx = obj->vars.camouflaged_target_m5_boss.unused_264;
    if (obj->vy >= 0) {
        obj->next_state = 0x10;
    }
}

s32 obj_sweep_hit(Object *obj, Vec3 *out);   /* fills the 0x10-byte block `out` */
void obj_get_attach_point(Object *obj, Vec3 *out);
/* Runs the path step unless the 0x1B7 flag is set: two scratch blocks from obj_sweep_hit and obj_get_attach_point, the deltas to 0x208-0x210, then sound_play_at_units. */
void obj_sweep_step(Object *obj) {
    Vec3 *from;
    Vec3 *to;

    if (*(u8 *)&obj->unk_1B7 != 0) {
        obj->next_state = 0x14;
        return;
    }
    from = scratch_alloc(0x10);
    obj->vz = obj->vars.camouflaged_target_m5_boss.unused_260;
    obj->vx = obj->vars.camouflaged_target_m5_boss.unused_264;
    if (obj_sweep_hit(obj, from) == 1) {
        to = scratch_alloc(0x10);
        obj->next_state = 0x11;
        obj_get_attach_point(obj, to);
        obj->vx = (from->x - to->x) << 12;
        obj->vy = (from->y - to->y) << 12;
        obj->vz = (from->z - to->z) << 12;
        sound_play_at_units(SND_S05_PROJECTILE_IMPACT | SND_GROUP(1), 0x7F, 0x3C, to);
        scratch_top -= 0x10;
    }
    scratch_top -= 0x10;
}

void obj_bounce(Object *obj) {
    s32 *pos;
    s32 vz;

    obj->vy = 0;
    if (obj->type.unk_0C >= 0x10A) {
        pos = (s32 *)scratch_top;
        obj->vy = 0xFFFE0000;
        obj->vars.camouflaged_target_m5_boss.unused_260 = -obj->vars.camouflaged_target_m5_boss.unused_260 * 2;
        vz = -obj->vars.camouflaged_target_m5_boss.unused_264 * 2;
        obj->unk_1B7 = 0;
        obj->vars.camouflaged_target_m5_boss.unused_264 = vz;
        obj->vx = vz;
        obj->vz = obj->vars.camouflaged_target_m5_boss.unused_260;
        obj->next_state = 0x12;
        scratch_top += 0x10;
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        sound_play_at_units(SND_PROJECTILE_LAUNCH | SND_GROUP(2), 0x7F, 0x3C, pos);
        scratch_top -= 0x10;
    }
}

void obj_landing_step(Object *obj) {
    obj->vx = obj->vars.camouflaged_target_m5_boss.unused_264;
    obj->vz = obj->vars.camouflaged_target_m5_boss.unused_260;
    if (*(u8 *)&obj->unk_1B7 != 0) {
        obj->next_state = 0x13;
    }
}

void rec_fire_at_player();
extern FxRecordParams death_effect_params[2];
void obj_death_effect(Object *obj) {
    Vec3 *pos;

    if (obj->type.unk_0C == 0x139) {
        pos = scratch_alloc(0x10);
        pos->x = obj->x >> 12;
        pos->y = (obj->y >> 12) - 0xA7;
        pos->z = obj->z >> 12;
        sound_play_at_units(SND_ENEMY_DEATH_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, pos);
        fx_rec34_spawn_cb((s32 *)pos, &death_effect_params[0], 0);
        fx_rec34_spawn_cb((s32 *)pos, &death_effect_params[1], (s32)rec_fire_at_player);
        scratch_top -= 0x10;
        obj->next_state = 0x15;
    }
}

/* Sweeps from the point of obj_get_attach_point along the object's velocity (0x208..0x210); on hitting an object
 * spawns a hit effect at arg2 and returns 1. */
s32 obj_sweep_hit(Object *obj, Vec3 *effect_pos) {
    s32 hit_object = 0;
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to = scratch_alloc(0x10);
    Vec3 *hit = scratch_alloc(0x10);
    s16 target = 0;

    obj_get_attach_point(obj, from);
    to->x = from->x + (obj->vx >> 12);
    to->y = from->y + (obj->vy >> 12);
    to->z = from->z + (obj->vz >> 12);
    set_collide_mode(1);
    trace_world(8, 0x18, from, to, hit);
    if (trace_objects(from, hit, 0x18, effect_pos, &target) == 1) {
        hit_target_masked(target, 2, obj->yaw, obj->damage);
        hit_object = 1;
        effect_spawn_at(effect_pos, model_slot_pchr(*(s32 *)obj->asset) + 0x188, 4, 0xC);
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return hit_object;
}

/* The object's point at offset (0xE8 of its words[5] table), turned by its yaw and pitch, in world units. */
void obj_get_attach_point(Object *obj, Vec3 *out) {
    u8 *src;

    src = (u8 *)obj->vars.camouflaged_target_m5_boss.pose_table; /* the same table obj_surface_sound reads */
    if (src != NULL) {
        out->x = *(s16 *)(src + 0xE8);
        out->y = *(s16 *)(src + 0xEA);
        out->z = *(s16 *)(src + 0xEC);
        rotate_xz_twice(obj->yaw, -obj->pitch, &out->x, &out->y, &out->z);
        out->x += obj->x >> 12;
        out->y += obj->y >> 12;
        out->z += obj->z >> 12;
    }
}

void fire_at_player_in_range(VECTOR *from, s32 radius);
void rec_fire_at_player(FxRecord *rec) {
    if (rec->clamped_phase < 0xE00) {
        fire_at_player_in_range((VECTOR *)rec, rec->radius_motion[0] >> 12);
    }
}

void fire_at_player_in_range(VECTOR *from, s32 radius) {
    VECTOR *pos = scratch_alloc(0x10);
    s32 dx, dy, dz;

    player_position_copy(pos);
    dx = pos->vx - from->vx;
    dz = pos->vz - from->vz;
    dy = pos->vy - from->vy;
    if (length_sq(dx, 0, dz) <= radius * radius) {
        if (ABS(dy) < 0x81) {
            hit_target_masked(0, 0x10, atan2(dz, dx), 0x10);
        }
    }
    scratch_top -= 0x10;
}

/* Same code as obj_fly_turn_to_player (s05). */
void func_800C1B28(Object *obj) {
    s32 fly_dx;
    s32 fly_dz;
    s32 target;
    s32 old;
    s32 new_yaw;
    s32 turn;
    s32 *player;

    if (obj->type.unk_0C >= 0xD) {
        fly_dz = 0;
        fly_dx = 0;
        player = player_position();
        target = (s16) atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
        old = obj->yaw;
        new_yaw = angle_approach(old, target, 0x2A);
        turn = (s16) new_yaw;
        turn -= old;
        obj->yaw = new_yaw;
        obj->turn = turn;
        fly_move(obj->yaw, 0x14, &fly_dx, &fly_dz);
        obj->vx = fly_dz;
        obj->vz = fly_dx;
    }
}

void chase_player_store_type_param(Object *obj, ObjHandler *handler);
void chase_player_update(Object *obj, ObjHandler *handler) {
    Vec3 *delta = scratch_alloc(0x10);
    s32 ox;
    s32 oz;
    s32 vz;
    s32 vx;
    s32 *player;
    s32 old_yaw;
    s16 yaw;
    s32 turn;
    s16 target;

    vz = 0;
    vx = 0;
    player = player_position();
    target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    old_yaw = obj->yaw;
    yaw = angle_approach(old_yaw, target, 0x2A);
    turn = yaw;
    obj->yaw = yaw;
    turn -= old_yaw;
    obj->turn = turn;
    fly_move(obj->yaw, 0x14, &vx, &vz);
    obj->vx = vz;
    obj->vz = vx;
    ox = obj->x;
    delta->x = (VEC_80139584.x - ox) >> 12;
    oz = obj->z;
    delta->z = (VEC_80139584.z - oz) >> 12;
    if (isqrt(length_sq(delta->x, 0, delta->z)) < 0x701) {
        obj->speed = 0x14000;
        chase_player_store_type_param(obj, handler);
        obj->next_state = 0x18;
    }
    scratch_top -= 0x10;
}

void chaser_fly_update(Object *obj) {
    s32 dx, dz;
    s32 *target;
    s32 clamped, v, over;
    s32 old;
    s16 angle;
    s32 turn, ret;

    dz = 0;
    dx = 0;
    if (obj->type.unk_0C < 0x147) {
        target = player_position();
        angle = atan2(target[2] - (obj->z >> 12), target[0] - (obj->x >> 12));
        old = obj->yaw;
        ret = angle_approach(old, angle, 0x2A);
        turn = (s16)ret;
        turn -= old;
        obj->yaw = ret;
        obj->turn = turn;
    }
    if (obj->type.unk_0C == 0x14F) {
        v = obj->speed - 0x800;
        over = v > 0x14000;
        clamped = v;
        if (over) {
            clamped = 0x14000;
        }
        FAKE_OPAQUE(over);
        v = over ? 0x14000 : v;
        if (v < 0) {
            clamped = 0;
        }
        obj->speed = clamped;
    }
    fly_move(obj->yaw, obj->speed >> 12, &dx, &dz);
    obj->vz = dx;
    obj->vx = dz;
}

void obj_retreat_move(Object *obj) {
    s32 dx;
    s32 dz;

    if (obj->type.unk_0C < 0x16E) {
        dz = 0;
        dx = 0;
        fly_move(obj->yaw + 0x800, 0x14, &dx, &dz);
        obj->vz = dx;
        obj->vx = dz;
    }
}

extern s16 camouflaged_target_routes[][8];
extern s16 camouflaged_target_waypoints[][4];
/* Camouflaged target flying a waypoint route (vars.h: 0x24C next waypoint,
 * 0x24E route, 0x250 phase, 0x252 flight timer, 0x254 heading). */
void camouflaged_target_route_update(Object *obj, s32 arg1) {
    s16 *route;
    s32 step[2];
    s32 dx;
    s32 idx;
    s32 point;
    s32 x;
    s32 z;
    u16 timer;

    switch ((s16)obj->vars.camouflaged_target_m5_boss.unused_250) {
    case 0:
        if (obj->type.unk_0C >= 0xD) {
            obj->vars.camouflaged_target_m5_boss.unused_24C = 0;
            obj->vars.camouflaged_target_m5_boss.unused_250 = 1;
            show_line((s32)"#2Target switched to optical camouflage.");
            target_select(3);
        }
        break;
    case 1:
        step[1] = 0;
        step[0] = 0;
        route = camouflaged_target_routes[(s16)obj->vars.camouflaged_target_m5_boss.unused_24E];
        idx = obj->vars.camouflaged_target_m5_boss.unused_24C;
        point = route[idx++];
        while (point < 0) {
            point = route[idx++];
        }
        x = camouflaged_target_waypoints[point][0] - (obj->x >> 12);
        z = camouflaged_target_waypoints[point][2] - (obj->z >> 12);
        obj->vars.camouflaged_target_m5_boss.unk_252 = isqrt(length_sq(x, 0, z)) / 20;
        obj->vars.camouflaged_target_m5_boss.unk_254 = atan2(z, x);
        fly_move(obj->vars.camouflaged_target_m5_boss.unk_254, 0x14, &step[0], &step[1]);
        obj->vars.camouflaged_target_m5_boss.unused_264 = step[1];
        dx = step[0];
        obj->vars.camouflaged_target_m5_boss.unused_24C = idx;
        obj->vars.camouflaged_target_m5_boss.unused_250 = 2;
        obj->vars.camouflaged_target_m5_boss.unused_260 = dx;
    case 2:
        obj->vx = obj->vars.camouflaged_target_m5_boss.unused_264;
        timer = obj->vars.camouflaged_target_m5_boss.unk_252 - 1;
        obj->vars.camouflaged_target_m5_boss.unk_252 = timer;
        obj->vz = obj->vars.camouflaged_target_m5_boss.unused_260;
        if ((timer << 16) <= 0) {
            if (obj->vars.camouflaged_target_m5_boss.unused_24C == 8) {
                obj->vars.camouflaged_target_m5_boss.unused_250 = 3;
            } else {
                obj->vars.camouflaged_target_m5_boss.unused_250 = 1;
            }
        }
        break;
    case 3:
        obj->vars.camouflaged_target_m5_boss.unused_250 = 0;
        obj->next_state = 0x1B;
        obj->vars.camouflaged_target_m5_boss.unused_24E++;
        obj_type_params_set(obj, arg1);
        break;
    }
    obj->yaw = angle_approach(obj->yaw, obj->vars.camouflaged_target_m5_boss.unk_254, 0x40);
}

void obj_apply_stored_velocity(Object *obj) {
    if (obj->type.unk_0C < 0x41) {
        obj->vx = obj->vars.camouflaged_target_m5_boss.unused_264;
        obj->vz = obj->vars.camouflaged_target_m5_boss.unused_260;
    }
}

extern s16 D_80118128[], D_80118130[], D_80118138[], D_80118158[];
void obj_surface_flash(Object *obj, s32 id, u8 *table, s32 index, s16 *ids, s32 *count);
/* Plays a hit sound at the object's position when it enters a new surface id. */
void obj_surface_sound(Object *obj) {
    s32 count = 0;
    u8 *table = (u8 *)obj->vars.camouflaged_target_m5_boss.pose_table;
    s32 id = obj->type.unk_0C;
    s16 *base = obj->rot_angles;
    s32 *pos;
    s32 sound;

    if (table != 0 && id != obj->vars.camouflaged_target_m5_boss.last_surface_id) {
        if (spawn_effects_flag == 1) {
            obj_surface_flash(obj, id, table, 0xF, D_80118128, &count);
            obj_surface_flash(obj, id, table, 0x10, D_80118130, &count);
        }
        obj_surface_flash(obj, id, table, 0x12, D_80118138, &count);
        obj_surface_flash(obj, id, table, 0x13, D_80118158, &count);
    }
    if (count > 0) {
        pos = (s32 *)scratch_top;
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        scratch_top += 0x10;
        if (((surface_of(*(s32 *)((u8 *)base + 0x64)) & 0x300) >> 8) == 1) {
            sound = count < 3 ? SND_SPLASH | SND_GROUP(2) : SND_BIG_SPLASH | SND_GROUP(2);
        } else {
            sound = SND_GROUND_IMPACT | SND_GROUP(2);
        }
        sound_play_at_units(sound, 0x7F, 0x3C, pos);
        scratch_top -= 0x10;
    }
    obj->vars.camouflaged_target_m5_boss.last_surface_id = id;
}

/* Walks the -1-terminated id list; on the entry equal to `id`, spawns a flash at record `index` of `table`
 * (12-byte records, position at +4) when the object stands on surface type 1, bumps *count and stops. */
void obj_surface_flash(Object *obj, s32 id, u8 *table, s32 index, s16 *ids, s32 *count) {
    s32 *pos;
    u8 *rec;
    s16 cur;

    cur = *ids;
    if (*ids >= 0) {
        rec = table + index * 12;
        do {
            ids++;
            if (id == cur) {
                if (((surface_of(obj->ground_id) & 0x300) >> 8) == 1) {
                    pos = scratch_alloc(0x10);
                    pos[0] = *(s16 *)(rec + 4);
                    pos[1] = *(s16 *)(rec + 6);
                    pos[2] = *(s16 *)(rec + 8);
                    rotate_xz_twice(obj->yaw, -obj->pitch, pos, pos + 1, pos + 2);
                    pos[0] += obj->x >> 12;
                    pos[1] = 0;
                    pos[2] = pos[2] + (obj->z >> 12);
                    effect_spawn_at((Vec3 *)pos, model_slot_pchr(*(s32 *)obj->asset) + 0x190, 6, 0xC);
                    scratch_top -= 0x10;
                }
                *count += 1;
                return;
            }
            cur = *ids;
        } while (*ids >= 0);
    }
}

extern s32 boss_area_attack_active;
extern s32 boss_area_attack_level;
extern s32 boss_area_attack_seq;
extern s32 boss_area_attack_pos[3];
extern s32 boss_area_attack_delta[3];
s32 boss_area_attack_explosion_spawn(s32 unused, s32 *pos, u16 *rot, s32 kind, s32 param);
void boss_area_attack_step(Object *obj) {
    s32 frame = obj->type.unk_0C;
    s32 *pos;
    s32 *next;
    s32 *cur;
    u16 *rot;
    s32 active;

    if (frame == 0x147 && boss_area_attack_active == 0) {
        boss_area_attack_active = 1;
        boss_area_attack_level = 0;
    }
    active = boss_area_attack_active;
    if (active == 1) {
        boss_area_attack_level += 0x100;
        boss_area_attack_level = MAX(MIN(boss_area_attack_level, 0x1000), 0);
        if (frame < 0x14E) {
            s16 *seq = (s16 *)boss_area_attack_seq;
            if (seq != NULL) {
                pos = scratch_alloc(0x10);
                pos[0] = seq[0xC4 / 2];
                pos[1] = seq[0xC6 / 2];
                pos[2] = seq[0xC8 / 2];
                rotate_xz_twice(obj->yaw, -obj->pitch, pos, pos + 1, pos + 2);
                pos[0] += obj->x >> 12;
                pos[1] += obj->y >> 12;
                pos[2] += obj->z >> 12;
                boss_area_attack_delta[0] = pos[0] - boss_area_attack_pos[0];
                boss_area_attack_delta[1] = pos[1] - boss_area_attack_pos[1];
                boss_area_attack_delta[2] = pos[2] - boss_area_attack_pos[2];
                boss_area_attack_pos[0] = pos[0];
                boss_area_attack_pos[1] = pos[1];
                boss_area_attack_seq = 0;
                boss_area_attack_pos[2] = pos[2];
                scratch_top -= 0x10;
            }
        } else {
            cur = (s32 *)scratch_top;
            scratch_top += 0x10;
            cur[0] = boss_area_attack_pos[0];
            cur[1] = boss_area_attack_pos[1];
            cur[2] = boss_area_attack_pos[2];
            next = scratch_alloc(0x10);
            next[0] = cur[0] + boss_area_attack_delta[0];
            next[1] = cur[1] + boss_area_attack_delta[1];
            next[2] = cur[2] + boss_area_attack_delta[2];
            if (trace_world(8, 8, cur, next, next) == active) {
                rot = scratch_alloc(8);
                rot[0] = obj->pitch;
                rot[1] = obj->yaw;
                rot[2] = obj->roll;
                sound_play_at_units(SND_AREA_ATTACK_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, next);
                boss_area_attack_explosion_spawn((s32)obj, next, rot, 0, model_slot_pchr(*(s32 *)obj->asset));
                boss_area_attack_active = 0;
                boss_area_attack_level = 0;
                scratch_top -= 8;
            } else {
                boss_area_attack_pos[0] += boss_area_attack_delta[0];
                boss_area_attack_pos[1] += boss_area_attack_delta[1];
                boss_area_attack_pos[2] += boss_area_attack_delta[2];
            }
            scratch_top -= 0x10;
            scratch_top -= 0x10;
        }
    }
}

extern s32 meter_mode_cmd;
extern ObjHandlerFn camouflaged_target_m5_boss_states[];
void camouflaged_target_m5_boss_phase2(Object *obj, ObjHandler *handler) {
    if (meter_mode_cmd == 0) {
        obj_hit_clear(obj->index);
    }
    obj_run_states(obj, handler, camouflaged_target_m5_boss_states);
}

void enemy_health_update(Object *obj, ObjHandler *handler) {
    s16 max_health;
    s32 flags;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    obj_hit_update(obj);
    max_health = obj->vars.enemy.sound_channel[1];
    if (obj->health < max_health) {
        obj->health = max_health;
    }
    if ((obj->health <= 0) && ((u8) obj->unk_1B7 != 0)) {
        add_score(obj->score);
        if (obj->score != 0) {
            add_kill_count(1);
        }
        obj->score = 0;
        handler->state = 1;
        handler->request_flags = 8;
        return;
    }
    /* the s32 copy keeps the halfword load signed (lh), as the original does */
    flags = obj->flags;
    if (((u32) flags >> 5) & 1) {
        obj_block_lerp(obj, 0);
    }
}

extern s32 D_80116DE4;
s32 enemy_die(Object *obj) {
    s32 type_offset;
    s32 asset_first_word;

    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->next_state = 0x1C;
    meter_set_mode(0);
    warning_ack_set(0);
    set_d_801202C8(0);
    type_offset = obj->type.unk_0E;
    asset_first_word = *(s32 *)obj->asset;
    D_80116DE4 = 0;
    enemy_spawn_copy(obj, type_offset + model_slot_pchr(asset_first_word), 1);
    obj_free(obj);
    return 0;
}

s32 obj_anim_pose_blend(Object *obj, s32 arg);
void spark_emit_level(Object *obj);
void spark_emit_pose(Object *obj);
s32 fade_colour_lookup(s32 level);
extern s32 boss_area_attack_seq;
extern s32 pchr_pose_table_alt[];
void camouflaged_target_m5_boss_draw(Object *obj) {
    Placement *placement;
    s32 x, y, z;
    s32 use_alt;
    s32 in_area;
    Vec3 *pos;
    SVECTOR *rot2;
    SVECTOR *rot;
    s32 value;
    s32 *seq;
    s32 fade;
    s32 colour;
    s32 pitch;

    use_alt = 0;
    placement = obj->placement;
    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    if (placement != NULL) {
        in_area = placement->unk_00[4] & 4;
        use_alt = in_area != 0;
    }
    if (use_alt != 0) {
        in_area = cam_range_check_alt(x, y, z, placement) == 0;
    } else {
        in_area = cam_range_check(x, y, z, placement) == 0;
    }
    if (in_area == 0) {
        pos = scratch_alloc(0x10);
        rot2 = scratch_alloc(8);
        rot = scratch_alloc(8);
        pos->x = obj->x >> 12;
        pos->y = obj->y >> 12;
        pos->z = obj->z >> 12;
        value = obj_anim_pose_blend(obj, 0);
        fade = get_d_80118194();
        colour = 0;
        pitch = (s16)obj->pitch;
        rot->vx = -pitch;
        rot->vy = obj->yaw;
        rot->vz = obj->roll;
        pchr_lists_build(value);
        value = pchr_copy_slot(value);
        seq = pchr_poses_build(value);
        obj->vars.chaser.target_x = (s32)seq;
        boss_area_attack_seq = (s32)seq;
        pchr_pose_table_alt[(value & 0x7FF) * 7] = obj->vars.chaser.target_x;
        if (fade > 0) {
            value |= 0x8000;
            colour = fade_colour_lookup(fade);
        }
        if (obj->hit > 0) {
            if (fade > 0) {
                if (obj->vars.camouflaged_target_m5_boss.unk_24A == 1) {
                    value &= 0xFFFF7FFF;
                    colour = 0x60C0FF;
                    obj->vars.camouflaged_target_m5_boss.unk_24A = 0;
                } else {
                    obj->vars.camouflaged_target_m5_boss.unk_24A = 1;
                }
            } else {
                colour = 0x60C0FF;
            }
        }
        spark_add(pos->x, pos->y, pos->z, rot->vy, rot->vx, rot->vz, value, colour);
        scratch_top -= 8;
        spark_emit_level(obj);
        spark_emit_pose(obj);
        pos->x = obj->x;
        pos->y = obj->y;
        pos->z = obj->z;
        rot2->vx = obj->width;
        rot2->vy = obj->height;
        rot2->vz = obj->unk_1E8[0];
        aim_marker_draw(2, rot2, pos, 0);
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    if ((u8)obj->unk_17A == 0 && get_d_80118194() == 0) {
        req_queue_push(obj->x >> 12, obj->y >> 12, obj->z >> 12, 0);
    }
}

/* Same code as func_800BA27C (s04). */
s32 obj_anim_pose_blend(Object *obj, s32 base) {
    s32 blend[4]; /* start, end, weight, 0x1000 - weight */

    base += model_slot_pchr(*(s32 *)obj->asset);
    if (obj->type.unk_0C != obj->type.unk_0E) {
        blend[0] = obj->type.unk_0C + base;
        blend[1] = obj->type.unk_0E + base;
        blend[2] = ((obj->type.unk_0A + 1) << 12) / obj->type.blend_duration;
        blend[3] = 0x1000 - blend[2];
        return pchr_blend(blend[0], blend[1], blend[2], 0);
    }
    return obj->type.unk_0C + base;
}

void spark_emit_level(Object *obj) {
    s32 value;
    register s32 level asm("$3");
    s32 quarter, eighth;
    s32 r, g, b;

    if (boss_area_attack_active == 1) {
        value = model_slot_pchr(*(s32 *)obj->asset) + 0x1A0;
        level = boss_area_attack_level;
        /* level / 4 and level / 8, rounded toward zero; then >> 5 */
        quarter = level;
        if (level < 0) {
            quarter = level + 3;
        }
        eighth = level;
        if (level < 0) {
            eighth = level + 7;
        }
        r = quarter >> 7;
        g = eighth >> 8;
        b = level >> 5;
        if ((r | g | b) == 0) {
            b = 1;
        }
        spark_add(boss_area_attack_pos[0], boss_area_attack_pos[1], boss_area_attack_pos[2], 0, 0, 0, value, (b << 16) | (g << 8) | r);
    }
}

void spark_emit_pose(Object *obj) {
    BonePose *pose;
    s32 v[3];
    s32 value, base;
    s32 pitch, yaw, roll, npitch;
    s32 shade1, shade2, hi1, hi2, colour;
    s32 pose_y1, pose_z1, cur_y1, pose_y2, pose_z2, cur_y2, off, start;
    s32 prx, pry, prz;
    s32 ax, ay, az, ay2;

    if (spawn_effects_flag == 0 && obj->vars.camouflaged_target_m5_boss.pose_table != 0) {
        base = model_slot_pchr(*(s32 *)obj->asset);
        off = (s16)(obj->vars.camouflaged_target_m5_boss.unk_258 % 9 / 3) + 0x198;
        pose = (BonePose *)obj->vars.camouflaged_target_m5_boss.pose_table;
        v[1] = -0x33;
        v[2] = -3;
        v[0] = -0x15;
        pitch = obj->pitch;
        yaw = obj->yaw;
        roll = obj->roll;
        value = base + off;
        rotate_vector_xyz(pose->rx, pose->ry, pose->rz, &v[0], &v[1], &v[2]);
        npitch = -pitch;
        v[0] += pose->x;
        pose_y1 = pose->y;
        cur_y1 = v[1];
        pose_z1 = pose->z;
        v[1] = cur_y1 + pose_y1;
        v[2] += pose_z1;
        rotate_xz_twice(yaw, npitch, &v[0], &v[1], &v[2]);
        v[0] += obj->x >> 12;
        v[1] += obj->y >> 12;
        v[2] += obj->z >> 12;
        shade1 = (s16)*(u16 *)&obj->vars.camouflaged_target_m5_boss.unk_270 >> 5;
        hi1 = shade1 == 0;
        colour = (hi1 << 16) | (shade1 << 8) | shade1;
        ax = -(pitch + pose->rx);
        ay = yaw + pose->ry;
        az = roll + pose->rz;
        spark_add(v[0], v[1], v[2], ay, ax, az, value, colour);
        start = 0x14;
        prx = pose->rx;
        pry = pose->ry;
        prz = pose->rz;
        v[0] = start;
        v[1] = -0x33;
        v[2] = -3;
        rotate_vector_xyz(prx, pry, prz, &v[0], &v[1], &v[2]);
        v[0] += pose->x;
        pose_y2 = pose->y;
        cur_y2 = v[1];
        pose_z2 = pose->z;
        v[1] = cur_y2 + pose_y2;
        v[2] += pose_z2;
        rotate_xz_twice(yaw, npitch, &v[0], &v[1], &v[2]);
        ay2 = yaw + pose->ry;
        v[0] += obj->x >> 12;
        v[1] += obj->y >> 12;
        v[2] += obj->z >> 12;
        shade2 = obj->vars.camouflaged_target_m5_boss.sound >> 5;
        hi2 = shade2 == 0;
        colour = (hi2 << 16) | (shade2 << 8) | shade2;
        ay2 += 0x800;
        spark_add(v[0], v[1], v[2], ay2, -(pitch + pose->rx), roll + pose->rz, value, colour);
    }
}

void rotate_vector_xyz(s32 angle_x, s32 angle_y, s32 angle_z, s32 *px, s32 *py, s32 *pz) {
    s32 x;
    s32 y;
    s32 z;
    s32 idx;
    s32 c;
    s32 s;
    s32 old;

    x = *px;
    y = *py;
    z = *pz;

    idx = angle_z & 0xFFF;
    if (idx != 0) {
        c = cos_table[idx].value;
        s = *(s16 *)&rcossin_tbl[idx];
        old = x;
        x = (c * x - s * y) >> 12;
        y = (s * old + c * y) >> 12;
    }
    idx = angle_x & 0xFFF;
    if (idx != 0) {
        c = cos_table[idx].value;
        s = *(s16 *)&rcossin_tbl[idx];
        old = y;
        y = (c * y - s * z) >> 12;
        z = (s * old + c * z) >> 12;
    }
    idx = angle_y & 0xFFF;
    if (idx != 0) {
        c = cos_table[idx].value;
        s = *(s16 *)&rcossin_tbl[idx];
        old = z;
        z = (c * z - s * x) >> 12;
        x = (s * old + c * x) >> 12;
    }
    *px = x;
    *py = y;
    *pz = z;
}

extern s32 camouflaged_target_m5_asset[3];
extern SoundVolume m5_boss_sounds[2];
extern s16 *camouflaged_target_m5_script_data[53];
extern s16 *D_80117E24[];
extern ScriptCallEntry m5_boss_call_table[22];
extern StateEntry m5_boss_states[28];
extern s16 *camouflaged_target_m5_boss_data[206];
void camouflaged_target_m5_boss_phase0(Object *obj, ObjHandler *handler);
s32 camouflaged_target_m5_boss_spawn(Placement *place) {
    Object *obj;
    s32 ok;
    u8 kind;

    ok = 0;
    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[0].fn = camouflaged_target_m5_boss_phase0;
        obj->handlers[1].fn = camouflaged_target_m5_boss_update;
        obj->handlers[2].fn = camouflaged_target_m5_boss_phase2;
        obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) camouflaged_target_m5_boss_draw;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = (s32) &enemy_die;
        kind = place->unk_00[5];
        obj->asset = camouflaged_target_m5_asset;
        obj->hit_cooldown_max = 0x30;
        obj->call_table = m5_boss_call_table;
        obj->state_table = m5_boss_states;
        obj->sounds = m5_boss_sounds;
        obj->unk_1C6 = 0;
        obj->kind = kind;
        obj->script.pc = D_80117E24[0];
        obj->script.data = camouflaged_target_m5_script_data;
        obj->script.unk_0A = 0;
        {
            script_start((Script *) obj, camouflaged_target_m5_boss_data[0], (s32) camouflaged_target_m5_boss_data);
        }
        obj_init_from_place(obj, place, 0x227);
        obj_set_part_bounds(obj, 1, 0x1666);
        obj->health = 0x4B00;
        obj->score = 20000;
        obj->damage = 0x20;
        obj->scale[0] = 0x100000;
        obj->scale[1] = 0x100000;
        obj->scale[2] = 0x100000;
        obj_hit_set_unk06(obj->index, 0);
        obj_hit_flag_set(obj->index, 0x80);
        pchr_set_entry_flags(model_slot_pchr(*(s32 *) obj->asset), 0);
        obj->vars.camouflaged_target_m5_boss.unused_248 = 0;
        obj->vars.camouflaged_target_m5_boss.unk_24A = 0;
        obj->vars.camouflaged_target_m5_boss.unused_24C = 0;
        obj->vars.camouflaged_target_m5_boss.unused_24E = 0;
        obj->vars.camouflaged_target_m5_boss.unused_250 = 0;
        obj->vars.camouflaged_target_m5_boss.unk_252 = 0;
        obj->vars.enemy.sound_channel[0] = 0;
        obj->vars.enemy.sound_channel[1] = 0x4B00;
        obj->vars.camouflaged_target_m5_boss.unk_258 = 0;
        obj->vars.camouflaged_target_m5_boss.last_surface_id = 1;
        obj->vars.camouflaged_target_m5_boss.pose_table = 0;
        obj->vars.camouflaged_target_m5_boss.unused_260 = 0;
        obj->vars.camouflaged_target_m5_boss.unused_264 = 0;
        obj->vars.camouflaged_target_m5_boss.target_z = 0;
        obj->vars.camouflaged_target_m5_boss.target_x = 0;
        obj->vars.camouflaged_target_m5_boss.unk_270 = 0;
        obj->vars.camouflaged_target_m5_boss.sound = 0;
        meter_set(0x4B00, 0x4B00);
        meter_set_mode(0);
        obj->unk_17A = 0;
        rec_table_set_enabled(0);
        meter_mode_cmd = 0;
        D_80116DE4 = 1;
        spawn_effects_flag = 1;
        boss_area_attack_active = 0;
        boss_area_attack_level = 0;
        boss_area_attack_seq = 0;
        ok = 1;
    }
    return ok;
}

extern s32 camouflaged_target_m5_asset[3];
/* Looks up the record for camouflaged_target_m5_asset, runs the two 0x80-byte blocks at its offsets 0x80 and 0x100,
 * then the two follow-up steps. */
void model_slot_refresh(void) {
    s32 base;

    base = model_slot_pchr(camouflaged_target_m5_asset[0]);
    pchr_copy_range(base + 0x80, 0x80, base);
    pchr_copy_range(base + 0x100, 0x80, base);
    fade_reset();
    spawn_slots_reset();
}

/* Laser beam slice: sweeps the beam from the current end point along its
 * velocity, hits the first world or object target, then grows the beam
 * length (unk_24E) by 0x200 per frame up to 0x1000. */
void laser_slice_update(Object *obj, ObjHandler *handler) {
    s32 *from;
    s32 *to;
    s32 *spawn;
    s32 *hit;
    s16 target;
    s32 world_hit;
    s32 beam_len;
    s32 beam_len_signed;
    s32 clamped_len;
    s32 stored_len;
    s32 vel_x;
    s32 vel_y;
    s32 vel_z;

    vel_x = obj->vx;
    vel_y = obj->vy;
    vel_z = obj->vz;
    from = scratch_alloc(0x10);
    to = scratch_alloc(0x10);
    spawn = scratch_alloc(0x10);
    hit = scratch_alloc(0x10);

    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    to[0] = (obj->x + vel_x) >> 12;
    to[1] = (obj->y + vel_y) >> 12;
    to[2] = (obj->z + vel_z) >> 12;

    target = 0;
    set_collide_mode(1);
    world_hit = trace_world(8, obj->vars.trace.trace_flags, from, to, hit);
    if (trace_objects(from, hit, obj->vars.trace.trace_flags, spawn, &target) == 1) {
        hit_target_masked(target, 0x10, obj->yaw, obj->damage);
        spawn_effect(spawn[0], spawn[1], spawn[2], 0x80007F00);
        obj->hit = 1;
    } else if (world_hit == 1) {
        obj->hit = 1;
    }

    set_collide_mode(0);

    beam_len = obj->vars.laser_slice.beam_length + 0x200;
    obj->x += vel_x;
    obj->y += vel_y;
    obj->z += vel_z;
    obj->vars.laser_slice.beam_length = beam_len;
    beam_len_signed = (s16)beam_len;
    if (beam_len_signed > 0x1000) {
        beam_len_signed = 0x1000;
    }
    clamped_len = (s16)beam_len;
    if (beam_len_signed >= 0) {
        if (clamped_len > 0x1000) {
            clamped_len = 0x1000;
        }
        stored_len = clamped_len;
    } else {
        stored_len = 0;
    }
    obj->vars.laser_slice.beam_length = stored_len;

    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}


void obj_free_outside_area(Object *obj) {
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    if ((obj->hit == 1) || (cam_range_check(x, y, z) == 0)) {
        obj_free(obj);
    }
}


extern s16 laser_slice_table[][4];
/* Adds a spark at the object's position: colour from the object's 0x24E field, rotation words from its angles. */
void laser_slice_draw(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    s32 shade, low;
    s32 color;
    s16 value;
    s32 pitch, base, idx, step;
    s32 n, x, y, z;
    s32 vx, vy, ang;
    u16 roll;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    idx = obj->vars.laser_slice.table_index;
    idx *= sizeof(laser_slice_table[0]); /* the byte offset first, as the original schedules it */
    shade = (s16)obj->vars.laser_slice.beam_length >> 5;
    base = (s16)obj->vars.laser_slice.unk_248;
    low = shade;
    step = *(s16 *)((u8 *)laser_slice_table + idx);
    value = base + step;
    if (shade == 0) {
        low = 1;
    }
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    pitch = obj->pitch;
    rot->vx = -pitch;
    rot->vy = obj->yaw;
    color = (low << 16) | (shade << 8) | shade;
    roll = obj->roll;
    rot->vz = roll;
    vx = rot->vx;
    vy = rot->vy;
    ang = vy + 0x800;
    n = SPARK_COUNT;
    list = &spark_list;
    x = pos->x;
    y = pos->y;
    z = pos->z;
    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = color;
        tail = list->tail[color >> 24];
        list->tail[color >> 24] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ang;
        s->pitch = vx;
        s->roll = roll;
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void laser_slice_update(Object *obj, ObjHandler *handler);
void laser_slice_draw(Object *obj);
/* Spawns a laser slice object at pos/ang. Table row a (laser_slice_table) gives the
 * 0x24C, 0x184 and speed values; kind goes to 0x248. Returns 1 on success. */
s32 laser_slice_spawn(Object *unused, Vec3 *pos, SVECTOR *ang, s32 a, s32 kind) {
    s32 vx, vy, vz;
    Object *obj;
    s16 *row;
    s32 result;
    u16 roll;

    result = 0;
    if ((u32)a < 2) {
        obj = obj_new();
        if (obj != NULL) {
            row = laser_slice_table[a];
            vx = 0;
            vy = 0;
            vz = 0;
            list_insert_after((Node *)get_obj_list_actors(), &obj->node);
            obj->handlers[1].fn = laser_slice_update;
            obj->handlers[2].fn = (void (*)(Object *, ObjHandler *))obj_free_outside_area;
            obj->handlers[0].fn = NULL;
            obj->handlers[0].unk_11 = 0;
            obj->handlers[0].state = 0;
            obj->handlers[1].unk_11 = 0;
            obj->handlers[1].state = 0;
            obj->handlers[2].unk_11 = 0;
            obj->handlers[2].state = 0;
            obj->handlers[3].fn = (void (*)(Object *, ObjHandler *))laser_slice_draw;
            obj->handlers[3].unk_11 = 0;
            obj->handlers[3].state = 0;
            obj->callback = 0;
            obj->hit = 0;
            obj_hit_clear(obj->index);
            obj_hit_flag_set(obj->index, 0);
            obj->x = pos->x << 12;
            obj->y = pos->y << 12;
            obj->z = pos->z << 12;
            obj->pitch = ang->vx;
            obj->yaw = ang->vy;
            roll = ang->vz;
            obj->flags = 0x80;
            obj->vars.laser_slice.unk_248 = (s16)kind;
            obj->vars.laser_slice.table_index = (s16)a;
            obj->roll = roll;
            obj->vars.laser_slice.unk_24C = row[1];
            obj->vars.laser_slice.beam_length = 0;
            obj->damage = row[2];
            obj->speed = row[3];
            angles_to_vector(ang->vy, -ang->vx, row[3], &vx, &vy, &vz);
            result = 1;
            obj->vx = vx;
            obj->vy = vy;
            obj->vz = vz;
        }
    }
    return result;
}

extern s32 d_80118190;
extern s32 screen_fade_amount;


void fade_reset(void) {
    d_80118190 = 0;
    screen_fade_amount = 0;
}


extern s32 d_80118190;

void set_d_80118190(s32 arg0) {
    d_80118190 = arg0;
}

extern s32 d_80118190;

s32 get_d_80118190(void) {
    return d_80118190;
}

extern s32 screen_fade_amount;

void set_d_80118194(s32 arg0) {
    screen_fade_amount = arg0;
}

extern s32 screen_fade_amount;

s32 get_d_80118194(void) {
    return screen_fade_amount;
}

void fade_level_step(void) {
    s32 value;
    s32 result;
    s32 clamped;

    value = screen_fade_amount;
    if (d_80118190 == 1) {
        value += 0x20;
    } else {
        value -= 0x20;
    }
    if (value >= 0x1000) {
        result = 0xFFF;
    } else {
        result = value;
    }
    clamped = value;
    if (value >= 0x1000) {
        clamped = 0xFFF;
    }
    if (clamped < 0) {
        result = 0;
    }
    screen_fade_amount = result;
}

extern s16 D_80118198[][2];
extern s16 D_8011819A[][2];
extern s16 D_801181B8[][2];
extern s16 D_801181BA[][2];
s32 fade_colour_lookup(s32 level)
{
    s32 unused[4];
    s32 pos = level;
    s32 result = 0;
    s32 idx;

    pos = MAX(MIN(pos, 0xFFF), 0);
    if (pos > 0) {
        s32 lo_x, lo_y, hi_x, hi_y;
        s32 inv;
        s32 x, y, zero;

        idx = pos >> 9;
        pos = (pos - (idx << 9)) * 8;
        lo_x = D_80118198[idx][0] * (inv = 0x1000 - pos);
        hi_x = D_8011819A[idx][0] * pos;
        lo_y = D_801181B8[idx][0] * inv;
        hi_y = D_801181BA[idx][0] * pos;
        x = (lo_x + hi_x) >> 17;
        y = (lo_y + hi_y) >> 17;
        zero = (x | y) == 0;
        result = (zero << 16) | (y << 8) | x;
    }
    return result;
}

void boss_area_attack_fire(Object *obj);
void boss_area_attack_explosion_update(Object *obj) {
    s32 speed = obj->vars.boss_area_attack_explosion.grow_speed + obj->vars.boss_area_attack_explosion.grow_accel;

    speed = MAX(MIN(speed, 0x1E000), 0x2000);
    obj->vars.boss_area_attack_explosion.grow_speed = speed;
    obj->vars.boss_area_attack_explosion.size += speed;
    if (obj->vars.boss_area_attack_explosion.age > 0x20) {
        s16 timer = obj->vars.boss_area_attack_explosion.colour - 0x2A;

        obj->vars.boss_area_attack_explosion.colour = timer;
        timer = MAX(MIN(timer, 0x1000), 0);
        obj->vars.boss_area_attack_explosion.colour = timer;
        if (timer == 0) {
            obj->hit = 1;
        }
    }
    if (obj->vars.boss_area_attack_explosion.colour > 0x80) {
        boss_area_attack_fire(obj);
    }
    obj->vars.boss_area_attack_explosion.unk_25C += 0x10;
    obj->vars.boss_area_attack_explosion.age++;
}

/* Fires a shot at the player (offset from the object, in whole units) when the player is within the object's
 * range (vars.enemy.unk_250) and the object is aimed by its yaw toward the player. */
void boss_area_attack_fire(Object *obj) {
    VECTOR *delta = scratch_alloc(0x10);
    s32 dx;
    s32 dy;
    s32 dz;
    s32 dist;

    player_position_copy(delta);
    dx = delta->vx - (obj->x >> 12);
    dy = delta->vy - (obj->y >> 12);
    dz = delta->vz - (obj->z >> 12);
    dist = isqrt(length_sq(dx, dy, dz));
    if ((obj->vars.boss_area_attack_explosion.size >> 12) >= dist) {
        hit_target_masked(0, 0x10, atan2(dz, dx), obj->damage);
    }
    scratch_top -= 0x10;
}


/* Same code as obj_free_outside_area (s05). */
void boss_area_attack_explosion_phase2(Object *obj) {
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    if ((obj->hit == 1) || (cam_range_check(x, y, z) == 0)) {
        obj_free(obj);
    }
}


void boss_area_attack_explosion_draw(Object *obj) {
    Vec3 *pos = (Vec3 *)scratch_top;
    s32 colour;
    s32 size;
    s32 model;
    s32 r, g, b;

    scratch_top += 0x10;
    model = obj->vars.boss_area_attack_explosion.model_base + 0x1A3;
    colour = (s16)obj->vars.boss_area_attack_explosion.colour;
    size = ((obj->vars.boss_area_attack_explosion.size >> 12) << 12) / 176;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    b = colour / 4;
    g = colour / 8;
    r = colour >> 5;
    b >>= 5;
    g >>= 5;
    if ((b | g | r) == 0) {
        r = 1;
    }
    colour = (r << 16) | (g << 8) | b;
    model = pool_spawn_scaled(model, size, size, size);
    spark_add(pos->x, pos->y, pos->z, obj->vars.boss_area_attack_explosion.unk_25C, 0, 0, model, colour);
    size = (((obj->vars.boss_area_attack_explosion.size >> 12) * 3) << 12) / 704;
    model = pool_spawn_scaled(obj->vars.boss_area_attack_explosion.model_base + 0x1A2, size, size, size);
    spark_add(pos->x, pos->y, pos->z, -obj->vars.boss_area_attack_explosion.unk_25C, 0, 0, model, colour);
    model = obj_anim_pose_blend_vars(obj, 4);
    size = ((obj->vars.boss_area_attack_explosion.size >> 12) << 12) / 216;
    model = pool_spawn_scaled(model, size, size, size);
    spark_add(pos->x, pos->y, pos->z, -obj->vars.boss_area_attack_explosion.unk_25C, 0, 0, model, colour);
    scratch_top -= 0x10;
}

/* Interpolates between the type's start and end keys (offset by base) at weight (unk_0A + 1) / unk_08. */
s32 obj_anim_pose_blend_vars(Object *obj, s32 offset) {
    s32 key[4];
    s32 base = offset + obj->vars.boss_area_attack_explosion.model_base;
    s32 result;

    if (obj->type.unk_0C == obj->type.unk_0E) {
        result = obj->type.unk_0C + base;
    } else {
        key[0] = obj->type.unk_0C + base;
        key[1] = obj->type.unk_0E + base;
        key[2] = ((obj->type.unk_0A + 1) << 12) / obj->type.blend_duration;
        key[3] = 0x1000 - key[2];
        result = pchr_blend(key[0], key[1], key[2], 0);
    }
    return result;
}

void boss_area_attack_explosion_draw(Object *obj);
extern s16 *spark_script_ptr[2];
/* Spawns a s05 object at pos (<< 12) with rot (pitch, yaw, roll). Only kind 0 spawns; returns 1 if it did. */
s32 boss_area_attack_explosion_spawn(s32 unused, s32 *pos, u16 *rot, s32 kind, s32 param) {
    Object *obj;
    s32 spawned = 0;

    if (kind >= 0) {
        if (kind <= 0) {
        obj = obj_new();
        if (obj != NULL) {
            spawned = 1;
            list_insert_after((Node *) get_obj_list_actors(), &obj->node);
            obj->handlers[1].fn = (ObjHandlerFn) boss_area_attack_explosion_update;
            obj->handlers[2].fn = (void (*)(Object *, ObjHandler *)) boss_area_attack_explosion_phase2;
            obj->handlers[0].fn = NULL;
            obj->handlers[0].unk_11 = 0;
            obj->handlers[0].state = 0;
            obj->handlers[1].unk_11 = 0;
            obj->handlers[1].state = 0;
            obj->handlers[2].unk_11 = 0;
            obj->handlers[2].state = 0;
            obj->handlers[3].fn = (ObjHandlerFn) boss_area_attack_explosion_draw;
            obj->handlers[3].unk_11 = 0;
            obj->handlers[3].state = 0;
            obj->callback = 0;
            obj->hit = 0;
            obj_hit_clear(obj->index);
            obj_hit_flag_set(obj->index, 0);
            obj->x = pos[0] << 12;
            obj->y = pos[1] << 12;
            obj->z = pos[2] << 12;
            obj->pitch = rot[0];
            obj->yaw = rot[1];
            obj->roll = rot[2];
            obj->flags = 1;
            script_start((Script *) obj, spark_script_ptr[0], (s32) spark_script_ptr);
            obj->vars.boss_area_attack_explosion.colour = 0x1000;
            obj->vars.boss_area_attack_explosion.size = 0x20000;
            obj->vars.boss_area_attack_explosion.grow_accel = -0x800;
            obj->vars.boss_area_attack_explosion.model_base = param;
            obj->vars.boss_area_attack_explosion.kind = kind;
            obj->vars.boss_area_attack_explosion.age = 0;
            obj->vars.boss_area_attack_explosion.grow_speed = 0x1E000;
            obj->damage = 0xA;
        }
        }
    }
    return spawned;
}
