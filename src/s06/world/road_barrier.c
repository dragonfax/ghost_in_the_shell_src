/* road_barrier: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

extern s16 road_barrier_script[4];
extern s16 *road_barrier_with_traffic_cone_data[];
extern s32 road_barrier_asset[3];
extern StateEntry road_barrier_states[1];
void road_barrier_with_traffic_cone_phase0(Object *obj, ObjHandler *handler);
void road_barrier_with_traffic_cone_update(Object *obj, ObjHandler *handler);
void s06_road_barrier_with_traffic_cone_draw(Object *obj, ObjHandler *handler);
/* Spawns an object from a placement record: links it into the actor list, sets its
 * state handlers and tuning, and runs its setup. Returns 1 if an object was made. */
s32 road_barrier_with_traffic_cone_spawn(Placement *place) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[0].fn = road_barrier_with_traffic_cone_phase0;
    obj->handlers[1].fn = road_barrier_with_traffic_cone_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = s06_road_barrier_with_traffic_cone_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->kind = place->unk_00[5];
    obj->asset = road_barrier_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = 0;
    obj->state_table = road_barrier_states;
    script_start((Script *) obj, road_barrier_script, (s32) &road_barrier_with_traffic_cone_data);
    obj_init_from_place(obj, place, 0x42);
    obj->speed = 0;
    obj_set_part_bounds(obj, 1, 0xC00);
    /* 0x24A/0x24B are bytes of vars.h.unk_24A; a flag set from unk_17B. */
    *((u8 *) &obj->vars.road_barrier_with_traffic_cone.unk_24A + 1) = 0;
    if (obj->unk_17B == 0) {
        *((u8 *) &obj->vars.road_barrier_with_traffic_cone.unk_24A) = 0;
    } else {
        *((u8 *) &obj->vars.road_barrier_with_traffic_cone.unk_24A) = 1;
    }
    return 1;
}

/* Waits for the player to come within 175 units, then knocks the barrier
   over: it jumps, flies sideways away from the player and spins; it bounces
   once when it lands (unk_1B7 set by the landing). */
void road_barrier_with_traffic_cone_phase0(Object *obj, ObjHandler *handler) {
    s32 *player;
    s32 *rel;

    player = player_position();
    rel = scratch_alloc(0x10);

    if (obj->vars.barrier.knocked != 0) {
        if (obj->unk_1B7 != 0) {
            if (obj->vars.barrier.landed == 0) {
                obj->vz = 0xFFFD0000;
                obj->vy = 0xFFFF4000;
                obj->unk_1B7 = 0;
                obj->vars.barrier.landed = 1;
                if (obj->unk_17B == 0) {
                    sound_play_at(SND_BARRIER_LAND | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
                }
            } else {
                obj->vars.barrier.knocked = 0;
                if (obj->unk_17B == 0) {
                    obj->vars.barrier.landed = 0;
                }
                obj->vz = 0;
                obj->vx = 0;
            }
        }
    } else {
        rel[0] = obj->x >> 12;
        rel[1] = obj->y >> 12;
        rel[2] = obj->z >> 12;
        rel[0] -= player[0];
        rel[1] -= player[1];
        rel[2] -= player[2];
        if (isqrt(length_sq(rel[0], rel[1], rel[2])) < 175) {
            obj->vars.barrier.knocked = 1;
            obj->scale[1] = 0x80000;
            if (obj->unk_17B == 1) {
                obj->vz = 0xFFFC0000;
                obj->vy = 0xFFFF4000;
                sound_play_at(SND_BARRIER_KNOCK_OVER | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
            } else {
                obj->vz = 0xFFFA0000;
                obj->vy = 0xFFFE8000;
                sound_play_at(SND_BARRIER_LAND | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
            }
            obj->unk_1B7 = 0;
            if (rel[0] == 0) {
                rel[0] = 1 - ((rand_a_next() & 1) << 1);
            }
            if (rel[0] < 0) {
                obj->vx = -(((rand_a_next() % 12) + 4) << 12);
                obj->vars.barrier.spin = 0x1000 / ((rand_a_next() % 16) + 16);
            } else {
                obj->vx = ((rand_a_next() % 12) + 4) << 12;
                obj->vars.barrier.spin = -0x1000 / ((rand_a_next() % 16) + 16);
            }
        }
    }
    scratch_top -= 0x10;
}

void road_barrier_with_traffic_cone_update(Object *obj, ObjHandler *handler) {
    if (obj->unk_17B == 0) {
        s32 lift = obj->vz + 0x400;
        s32 clamped;

        obj->vz = lift;
        clamped = MAX(MIN(lift, 0), -0x80000);
        obj->vz = clamped;
    }
    if (*((u8 *) &obj->vars.road_barrier_with_traffic_cone.unk_24A + 1) != 0) {
        s16 pitch = obj->pitch + 0x20;
        s16 clamped;

        obj->yaw += obj->vars.road_barrier_with_traffic_cone.yaw_speed;
        obj->pitch = pitch;
        clamped = MAX(MIN(pitch, 0x400), 0);
        obj->pitch = clamped;
    }
    obj_script_step(obj, handler);
}

/* Adds a spark at the object's position with its rotation as the velocity. */
void s06_road_barrier_with_traffic_cone_draw(Object *obj, ObjHandler *handler) {
    Vec3 *pos = scratch_alloc(0x10);
    EulerAngles *rot;
    s32 pitch;
    s32 rx, ry, rz;
    s16 value;
    s32 base, flag;
    s32 n;
    s32 x, y, z;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    rot = scratch_alloc(0x10);
    pitch = obj->pitch;
    rot->pitch = -pitch;
    rot->yaw = obj->yaw;
    rot->roll = obj->roll;
    base = model_slot_pchr(*(s32 *)obj->asset) + 1;
    n = spark_count;
    flag = obj->unk_17B == 1;
    value = base + flag;
    rx = rot->yaw;
    ry = rot->pitch;
    rz = rot->roll;
    x = pos->x;
    y = pos->y;
    z = pos->z;
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
        s->yaw = rx;
        s->pitch = ry;
        s->roll = rz;
    }
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x20;
}

extern s32 loop_sound_handle;
extern s32 loop_sound_saved_mode;
extern s16 loop_sound_start_ids[];
extern s16 loop_sound_stop_ids[];
void sound_loop_toggle_by_id(s32 sound_id) {
    s16 *p;

    if (loop_sound_handle == 0) {
        if (loop_sound_start_ids[0] != -1) {
            s32 sentinel = -1;
            p = loop_sound_start_ids;
            do {
                if (*p == sound_id) {
                    loop_sound_handle = sound_start(0xD283, 0x40, 0, 0);
                    loop_sound_saved_mode = set_sound_mode(0x3800);
                    return;
                }
                p++;
            } while (*p != sentinel);
        }
    } else {
        if (loop_sound_stop_ids[0] != -1) {
            s32 sentinel = -1;
            p = loop_sound_stop_ids;
            do {
                if (*p == sound_id) {
                    sound_stop(loop_sound_handle);
                    loop_sound_handle = 0;
                    set_sound_mode(loop_sound_saved_mode);
                    return;
                }
                p++;
            } while (*p != sentinel);
        }
    }
}

/* A self-relative block: word 0 the offset of the strip ranges span_source_build reads, word 1 the offset of the
 * span table span_table_build reads. */
extern s32 stage_data_block[944];
extern s32 cam_fade_color;
extern s32 cam_fade_dir;
extern s32 cam_fade_ramp;
extern s32 cam_rec_request;
extern s32 loop_sound_handle;
extern s32 cam_bounce_offset;
void stage_setup(void) {
    s32 *base;
    s32 *span_src;
    s32 i;
    u8 *src;
    PackedWord *dst;

    if (stage_ready_get() != 0) {
        base = stage_data_block;
        span_src = span_source_build((s32)base + base[0]);
        span_table_build((s32)base + stage_data_block[1], span_src);
        i = 0;
        dst = (PackedWord *)&cam_fade_color;
        src = (u8 *)light_sets;
        for (; i < 3; i++) {
            *dst++ = *(PackedWord *)(src + 8);
            src += 4;
        }
    }
    set_flow_max(0x28);
    set_player_status(get_player_status() | 9);
    player_ceiling_limit_set(0x7FFFF);
    cam_fade_dir = 0;
    cam_fade_ramp = -1;
    cam_bounce_offset = 0;
    cam_rec_request = 0;
    loop_sound_handle = 0;
}

void cam_transition_start(void) {
    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(0x640, -0x2BC, 0x28490);
    cam_look_at_set((s32) cam_pos >> 0xC, (s32) cam_pos_y >> 0xC, (s32) cam_pos_z >> 0xC);
    fade_level_set(0);
}

void cam_transition_step(void) {
    s32 *pos;
    s32 fade;

    fade = fade_level_get();
    if (fade == 0x1000) {
        return;
    }
    pos = cam_view_pos_get();
    pos[0] += half_shift(get_flow_move()[0]);
    pos[1] += half_shift(get_flow_move()[1]);
    pos[2] += half_shift(get_flow_move()[2]);
    cam_view_pos_set(pos[0], pos[1], pos[2]);
    cam_look_at_set(cam_pos >> 12, cam_pos_y >> 12, cam_pos_z >> 12);
    fade = CLAMP_HI(fade + 0x16, 0x1000);
    fade_level_set(fade);
    if (fade == 0x1000) {
        set_d_801202C8(1);
        set_stage_flags(get_stage_flags() & ~0x28);
    }
}

void cam_transition_phase2(Object *obj, ObjHandler *handler);
void cam_transition_draw(Object *obj, ObjHandler *handler);
extern s32 last_flow_state;
s32 cam_transition_spawn(void) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_b(), &obj->node);
    obj->handlers[2].fn = cam_transition_phase2;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = cam_transition_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    cam_transition_start();
    last_flow_state = -1;
    return 1;
}

char str_waycrnt_clt[12] RODATA = "waycrnt.clt";

char str_waycrnp_clt[12] RODATA = "waycrnp.clt";

char str_waycrnt_xs3[12] RODATA = "waycrnt.xs3";

char str_waycrnp_vx1[12] RODATA = "waycrnp.vx1";

extern s32 player_xyz_y;
static const char msg_junction_ahead[] = "#1A junction ahead.\xA1";
static const char msg_road_divided[] = "#1Warning!  Warning! The road is dividedahead.\xA1";
/* The message sprite files: data tables point to them by address. */
const char file_msgs_spr_so3[] = "msgs_spr.so3";
const char file_msgs_spr_grc[] = "msgs_spr.grc";
const char file_msgs_spr_clt[] = "msgs_spr.clt";
void cam_transition_phase2(Object *obj, ObjHandler *handler) {
    VECTOR pos;
    s32 flow;
    s32 old_fade;
    s32 fade;
    s32 on;
    s32 i;
    s32 off;
    s32 inv;
    s32 r, g, b;
    PlayerObj *self;
    PlayerObj *player;

    cam_transition_step();
    flow = flow_state_get();
    if (last_flow_state != flow) {
        if (flow == 0xA8) {
            show_line((s32)msg_junction_ahead);
        } else if (flow == 0x15F) {
            show_line((s32)msg_road_divided);
        }
    }
    if (flow == 0x20C || flow == 0x15E) {
        cam_rec_request = 1;
    }
    if (cam_fade_dir != 0) {
        if (flow == 0x1A9) {
            cam_fade_dir = 0;
        }
    } else if (flow == 0x18D || flow == 0x25A || flow == 0x262) {
        cam_fade_dir = 1;
    }
    old_fade = cam_fade_ramp;
    if (cam_fade_dir != 0) {
        s32 up = old_fade + 0x100;
        fade = 0x1000;
        if (up < 0x1001) {
            fade = up;
        }
        cam_fade_ramp = fade;
    } else {
        s32 down = old_fade - 0x100;
        if (down < 0) {
            down = 0;
        }
        cam_fade_ramp = down;
    }
    on = 0;
    if (cam_fade_ramp != 0x1000) {
        on = cam_rec_request != 0;
    }
    rec_set_on(0, on);
    rec_set_tex_flag(0, cam_fade_ramp != 0x1000);
    rec_set_flag(0, cam_fade_ramp == 0);
    if (old_fade != cam_fade_ramp) {
        for (i = 0, off = 0; i < 3; i++, off += 4) {
            inv = 0x1000 - cam_fade_ramp;
            r = ((u8 *)&cam_fade_color)[off] * inv / 4096;
            g = ((u8 *)&cam_fade_color)[off + 1] * inv / 4096;
            b = ((u8 *)&cam_fade_color)[off + 2] * inv / 4096;
            rec_set_colour(0, i, r, g, b);
        }
    }
    sound_loop_toggle_by_id(flow);
    if (flow == 0x27E || flow == 0x24A) {
        set_stage_end(2);
    }
    player_ceiling_limit_set(0x7FFFF);
    set_player_mode_flags(player_mode_flags() | 6);
    if ((u32)(flow - 0x147) < 0x13) {
        player_ceiling_limit_set(-0xF30);
        set_player_mode_flags(player_mode_flags() & ~4);
        self = &player_obj;
        player = self;
        if (player_landed == 0 && (player_xyz_y >> 12) >= -0xF2F) {
            s32 push;
            s32 top;

            player_y_speed -= 0x1200;
            push = player_y_speed;
            if (push > 0xC000) {
                player_y_speed = push = 0xC000;
            }
            if (player_xyz_y > (s32)0xFF0D0000) {
                top = push;
                if (top > 0) {
                    top = 0;
                }
                player_y_speed = top;
            }
            if (player->flags & 0xC) {
                pos.vy = -0xF94;
                pos.vx = player->sub[0] >> 12;
                pos.vz = (player->sub[2] >> 12) - 0x140;
                player_warp_request(&pos, 0, 0);
                FAKE_USE(player);
                cam_bounce_offset = -0x3C000;
                self->vy = -0xA000;
                hit_target_masked(0, 1, -1, (get_shield() / 4) << 16 >> 16);
            }
        }
        {
            s32 disp = cam_bounce_offset;

            disp = disp * 15 / 16;
            if (ABS(disp) < 0x4000) {
                disp = 0;
            }
            cam_bounce_offset = disp;
            add_displacement(0, 0, disp);
        }
    }
    last_flow_state = flow;
}

void cam_transition_draw(Object *obj, ObjHandler *handler) {
}
