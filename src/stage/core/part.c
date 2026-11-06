/* part: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void part_reset_all(void) {
    part_slots_clear();
    str_queue_clear();
    part_rec_reset();
    cam_tracks_reset();
    view_slots_reset();
    stage_queue_clear();
    cam_track_reset();
    text_slots_reset();
    ramp_reset();
    part_timer_start();
}

void part_timer_start(void) {
    part_time = 0;
    part_timer_on = part_slots_in_use();
    part_fade_swap(0);
    part_slots_reset();
    cam_tracks_clear_on();
    view_slots_clear();
    cam_track_clear_active();
    part_rec_clear_active();
    text_slots_clear();
    ramp_clear();
}

void part_timer_step(void) {
    if (part_timer_on != 0) {
        part_time += 1;
        part_slots_step();
        cam_tracks_step();
        fn_800E8AE4();
        part_recs_step();
        countdown_rec_step();
        text_slots_step();
        ramp_step();
    }
}

void part_view_apply(void) {
    if (part_timer_on != 0) {
        fn_800E8A34();
        view_recs_apply();
    }
}

void part_draw(void) {
    if (part_timer_on != 0) {
        part_recs_emit_sparks();
        cam_tracks_emit_ids();
        fn_800E9440();
        ramp_apply();
    }
}

void part_base_set(s32 value) {
    part_pose_base = value;
}

void part_offset_set(s32 value) {
    part_offset = value;
}

/* Set part_fade_handler and return its old value. */
s32 part_fade_swap(s32 value) {
    s32 old;

    old = part_fade_handler;
    part_fade_handler = value;
    return old;
}

/* Clear a CamTrackPart. */
void cam_track_part_clear(CamTrackPart *rec) {
    s32 *p;
    s32 i;

    i = 2;
    p = &rec->unk_00[2];
    rec->mode = 0;
    rec->unk_11 = 0;
    rec->start_time = 0;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

/* Evaluate a camera track part at part_time into out[] (20.12; whole units if `whole`).
 * Mode (low nibble of unk_10) 2: linear keys from/to over `duration` (high nibble 0 clamps, 1 wraps);
 * 3: a value_queue_get table curve, delayed, scaled by rate, shifted by offset, weighted per axis;
 * others: the base values. The divides and multiplies are the original's hand mult/div macros
 * (volatile asm keeps the scheduler from moving loads across them). */
void cam_track_part_eval(CamTrackPart *rec, s32 *out, s32 whole) {
    u32 mode = rec->mode;

    switch (mode & 0xF) {
    case 2: {
        register s32 dur asm("$9") = rec->duration;
        register s32 now asm("$3") = part_time;
        register s32 start asm("$2") = rec->start_time;
        register s32 t asm("$8") = now - start;
        s32 count;
        s32 j;

        if (t < 0) {
            t = 0;
        }
        switch (mode >> 4) {
        case 0:
            if (dur < t) {
                t = dur;
            }
            break;
        case 1:
            t = t % dur;
            break;
        }
        count = rec->unk_11;
        for (j = 0; j < count; j++) {
            register s32 from asm("$3") = rec->anim.keys[j][0];
            s32 span = rec->anim.keys[j][1] - from;
            register s32 num asm("$6") = span * t;
            s32 quot;
            register s32 rem asm("$5");

            /* quot, rem = num / dur, num % dur */
            mips_div(num, dur);
            num = rec->unk_00[j];
            mips_mfhi(rem);
            mips_mflo(quot);
            rem <<= 12;
            /* fraction = (rem << 12) / dur */
            mips_div(rem, dur);
            from = num + from;
            from += quot;
            num = from << 12;
            mips_mflo(rem);
            span = num + rem;
            out[j] = span;
        }
        break;
    }
    case 3: {
        register s32 *table asm("$6") = (s32 *)value_queue_get(rec->duration);
        s32 t;
        s32 stride;
        s32 count;
        s32 k;
        s32 *xs;
        s32 *ys;
        s32 i = 0;
        s32 x;

        if (table == NULL) {
            for (; i < 3; i++) {
                out[i] = rec->unk_00[i] << 12;
            }
            break;
        }
        rec->unk_11 = table[1];
        t = part_time - rec->start_time - rec->anim.curve.delay;
        if (t < 0) {
            t = 0;
        }
        /* t = (t * rate >> 12) + offset */
        x = rec->anim.curve.rate;
        mips_mult(t, x);
        x = rec->anim.curve.offset;
        mips_mflo(t);
        t = (t >> 12) + x;
        count = table[1];
        xs = &table[3];
        stride = table[2];
        ys = xs + stride;
        for (k = 0; k < count; k++) {
            s32 v = table_curve_eval(t, stride, xs, (u8 *)ys);
            u32 lo;
            s32 hi;

            /* out[k] = (base << 12) + (s64)v * weight >> 12, the halves added */
            x = rec->anim.curve.weight[k];
            mips_mult(v, x);
            x = rec->unk_00[k];
            mips_mflo(lo);
            mips_mfhi(hi);
            lo >>= 12;
            hi <<= 20;
            out[k] = (x << 12) + hi + lo;
            ys += stride;
        }
        break;
    }
    default: {
        s32 i;
        for (i = 0; i < 3; i++) {
            out[i] = rec->unk_00[i] << 12;
        }
        break;
    }
    }
    if (whole) {
        out[0] >>= 12;
        out[1] >>= 12;
        out[2] >>= 12;
    }
}

/* Projects part 0 of rec, after cam_track_part_eval updates out, into view view_index's screen: out[0..1] become the
 * screen x/y (offset by the part's position). 0 when the view has no camera, the point is out of range or the
 * projection overflows; 1 otherwise (and when the part's kind isn't 3). */
s32 part_rec_visible(TrackRec *rec, s32 *out, s32 view_index) {
    TrackPart *part = (TrackPart *)rec->part[0];
    View *view;
    Camera *cam;
    s32 dx, dy, dz;
    s32 r0, r1, r2;
    s32 flag;
    s32 base_x;

    cam_track_part_eval((CamTrackPart *)rec, out, 1);
    if (part->kind != 3) {
        return 1;
    }
    view = &views[view_index];
    if (view->camera < 0) {
        return 0;
    }
    cam = &cameras[view->camera];
    base_x = part->pos[0];
    dx = out[0] - cam->pos.vx - base_x;
    if ((u32)(dx + 0x4000) > 0x7FFF) {
        return 0;
    }
    dy = out[1] - cam->pos.vy - part->pos[1];
    if ((u32)(dy + 0x4000) > 0x7FFF) {
        return 0;
    }
    dz = out[2] - cam->pos.vz - part->pos[2];
    if ((u32)(dz + 0x4000) > 0x7FFF) {
        return 0;
    }
    gte_load_R012(view->rot, r0, r1, r2);
    gte_load_R34(view->rot, r0, r1);
    gte_set_screen_h80_origin_via(12);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    gte_set(VXY0, (dy << 16) | (dx & 0xFFFF));
    gte_set(VZ0, dz);
    gte_rtps();
    gte_get_ctrl(FLAG, flag);
    gte_get(SXY2, dx);
    dy = dx >> 16;
    if (flag >= 0) {
        dx = (s16)dx;
        out[0] = dx + base_x;
        {
            register s32 y asm("$2") = dy + part->pos[1];
            out[1] = y;
        }
        return 1;
    }
    return 0;
}

/* True when no entry of part_slot_recs has a nonzero state. */
s32 part_slots_idle(void) {
    s32 i;

    for (i = 0; i < part_slot_count; i++) {
        if (part_slot_recs[i].state != 0) {
            return 0;
        }
    }
    return 1;
}

void part_slots_clear(void) {
    part_slot_count = 0;
}

s32 part_slots_in_use(void) {
    return part_slot_count > 0;
}

/* Resets the part_slot_recs records (count part_slot_count): each gets state 1 and
 * zeroed unk_04, unk_06 and unk_00. */
void part_slots_reset(void) {
    s32 unused; /* keeps the original's 8-byte stack frame */
    s32 count;
    s32 i;

    count = part_slot_count;
    for (i = 0; i < count; i++) {
        part_slot_recs[i].state = 1;
        part_slot_recs[i].wait_timer = 0;
        part_slot_recs[i].script_index = 0;
        part_slot_recs[i].unk_00 = 0;
    }
}

/* Append a value to the 16-entry list at 0x80128728 (count in part_slot_count). */
void part_slots_append(s32 value) {
    s32 n = part_slot_count;

    if (n < 16) {
        part_slot_count = n + 1;
        part_slot_recs[n].value = value;
    }
}

void part_slot_set_state(s32 n, s32 state) {
    PartSlot *rec = &part_slot_recs[n];

    if (state == 2) {
        state = 1;
        rec->wait_timer = 0;
        rec->script_index = 0;
        rec->unk_00 = 0;
    }
    rec->state = state;
}

/* Sets the halfword at +4 of a record to the word *value. */
void fn_800E8024(s16 *rec, s32 *value) {
    rec[2] = *value;
}

/* Clears the halfword at +2 of a record. */
void fn_800E8030(s16 *rec) {
    rec[1] = 0;
}

/* Calls handler kind for each index from args[1] to args[2] inclusive, passing args[3]. */
void handler_range_call(s32 unk_a0, s32 *args) {
    s32 kind;
    s32 index;
    s32 last;
    s32 param;

    kind = *args;
    args++;
    index = *args;
    args++;
    last = *args;
    param = args[1];
    if (last < index) {
        return;
    }
    do {
        handler_fn_table[kind](index, param);
        index++;
    } while (index <= last);
}

void handler_range_call_zero(s32 index, s32 *args) {
    s32 i;
    s32 last;

    index = *args++;
    i = args[0];
    last = args[1];
    while (i <= last) {
        clear_handler_table[index](i++, 0);
    }
}

/* Reads one record from the stream (a word after the key, then 13 words) into the slot the key picks:
 * three words, two bytes, part_time (the stream word after the bytes is skipped), then seven halfwords. */
void part_record_read(s32 unused, u32 *stream, s32 key) {
    u8 *rec;
    s32 i;

    rec = (u8 *) part_record_resolve_table[(key >> 16) & 0xFF](*stream++) + (((u32) key >> 24) << 5);
    for (i = 0; i < 3; i++) {
        *(u32 *) (rec + i * 4) = *stream;
        stream++;
    }
    rec[0x10] = *stream;
    stream++;
    rec[0x11] = *stream;
    *(s32 *) (rec + 0xC) = part_time;
    stream++;
    for (i = 0; i < 7; i++) {
        *(u16 *) (rec + 0x12 + i * 2) = *stream;
        stream++;
    }
}

void cam_track_setup(s32 unused, s32 *args) {
    s32 n;
    TrackRec *rec;

    n = *args++;
    rec = cam_track_slot_get(n);
    rec->on = 1;
    rec->index = n;
    cam_set_rec(n, *args);
    cam_track_part_clear((CamTrackPart *)rec->part[0]);
    cam_track_part_clear((CamTrackPart *)rec->part[1]);
    cam_track_part_clear((CamTrackPart *)rec->part[2]);
    cam_track_part_clear((CamTrackPart *)rec->part[3]);
    *(s32 *)&rec->part[3][0] = 0x1000;
    *(s32 *)&rec->part[3][4] = 0x1000;
    rec->unk_82 = 0;
    rec->unk_80 = 0;
}

/* Script op: sets up a view record from the words at `args` (view number, four values for
 * view_set_parent/F8/9320 and the three colour triples for view_set_colour/961C/9654) and clears its parts. */
void view_rec_setup(s32 unused, s32 *args) {
    ViewRec *rec;
    s32 view;
    s32 cd, r, g, b;

    view = *args++;
    rec = view_rec_get(view);
    rec->enabled = 1;
    *(s16 *)((u8 *)rec + 0xA2) = view;
    view_set_on(view, 1);
    view_set_parent(view, *args++);
    view_set_depth(view, *args++);
    view_set_camera(view, *args++);
    cd = *args++;
    r = *args++;
    g = *args++;
    b = *args++;
    view_set_colour(view, r, g, b, cd);
    cd = *args++;
    r = *args++;
    g = *args++;
    b = *args++;
    view_set_colour_b(view, r, g, b, cd);
    cd = *args++;
    r = *args++;
    g = args[0];
    b = args[1];
    view_set_colour_c(view, r, g, b, cd);
    cam_track_part_clear((CamTrackPart *)rec);
    cam_track_part_clear((CamTrackPart *)((u8 *)rec + 0x20));
    cam_track_part_clear((CamTrackPart *)((u8 *)rec + 0x40));
    cam_track_part_clear((CamTrackPart *)((u8 *)rec + 0x60));
    cam_track_part_clear((CamTrackPart *)((u8 *)rec + 0x80));
}

/* Handler script op: sets up a 0x88-byte record from the words at `args` (index, value, on, record index)
 * and clears its four parts. */
void cam_track_init(s32 unused, s32 *args) {
    TrackRec *rec;

    rec = cam_track_get(*args++);
    rec->unk_80 = 1;
    rec->unk_82 = *args++;
    rec->on = args[0];
    rec->index = args[1];
    cam_track_part_clear((CamTrackPart *)rec);
    cam_track_part_clear((CamTrackPart *)rec->part[1]);
    cam_track_part_clear((CamTrackPart *)rec->part[2]);
    cam_track_part_clear((CamTrackPart *)rec->part[3]);
}

/* Script command: args are (record index, unk_82, on, index). */
void cam_track_b_setup(s32 unused, s32 *args) {
    TrackRec *r;

    r = part_rec_get(*args++);
    r->unk_80 = 1;
    r->unk_82 = *args++;
    r->on = *args++;
    r->index = *args;
    cam_track_part_clear((CamTrackPart *)r->part[0]);
    cam_track_part_clear((CamTrackPart *)r->part[1]);
    cam_track_part_clear((CamTrackPart *)r->part[2]);
    cam_track_part_clear((CamTrackPart *)r->part[3]);
    *(s32 *)r->part[3] = 0x1000;
}

/* Track command: sets up track `args[0]` from a list of words. */
void track_setup(s32 unused, s32 *args) {
    s32 track = *args++;

    track_set_enabled(track, 1);
    fn_800D9E3C(track, *args++);
    track_set_origin(track, *args++, *args++);
    track_set_dims(track, *args++, *args++, *args++, *args++);
    track_set_x(track, *args++ + part_offset);
    track_set_y(track, *args++ + part_offset);
    track_set_phase_rate(track, *args++);
    track_set_angle(track, *args);
    track_reset(track);
}

void text_slot_setup(s32 unused_index, s32 *words) {
    PointSlot *rec;
    s32 flags;

    rec = (PointSlot *) text_slot_find_free();
    if (rec != NULL) {
        rec->x = 1;
        rec->y = (s16) *words++;
        rec->unk_08 = (s16) *words++;
        rec->unk_0A = (s16) *words++;
        rec->z = (s16) words[0];
        flags = words[1];
        rec->unk_0C = rec->unk_08;
        rec->colour = 0;
        *(s16 *) &rec->unk_0E = 0;
        rec->flags = flags;
    }
}

/* Script command: set the camera offset, then start a ramp from args[3] to
 * args[4] over args[5] frames; a falling ramp notifies part_fade_handler and swaps
 * the particle fade. */
void ramp_start_script(s32 unused, s32 *args) {
    RampState *ramp;
    s32 x, y, z;

    ramp = (RampState *) ramp_get_state();
    ramp->active = 1;
    x = *args++;
    y = *args++;
    z = *args++;
    cam_offset_set(x, y, z);
    ramp->from = *args++;
    ramp->to = *args++;
    ramp->length = *args++;
    ramp->pos = 0;
    if (ramp->to < ramp->from) {
        if (part_fade_handler != 0) {
            ((void (*)(s32, s32, s32)) part_fade_handler)(ramp->length, ramp->from, ramp->to);
        }
        part_fade_swap(0);
    }
}

void part_slots_step(void) {
    s32 i;
    PartSlot *slot;
    s16 *timer;
    s32 *script;
    s32 cmd;
    s32 unused[2]; /* only reserves the original frame size */

    slot = part_slot_recs;
    i = 0;
    if (part_slot_count > 0) {
        do {
            timer = &slot->wait_timer;
            while (timer[-1] != 0 && timer[0] == 0) {
                script = (s32 *) slot->value + timer[1];
                cmd = *script++;
                timer[1] = (s16)(timer[1] + 1) + ((cmd >> 8) & 0xFF);
                part_cmd_table[cmd & 0xFF](slot, script, cmd);
            }
            if (timer[-1] != 0 && timer[0] > 0) {
                timer[0]--;
            }
            i++;
            slot++;
        } while (i < part_slot_count);
    }
}

void cam_tracks_reset(void) {
    cam_tracks_clear_on();
}

/* Clears `on` of the eight TrackRec records in cam_tracks. */
void cam_tracks_clear_on(void) {
    s32 off = 0x3B8;
    do {
        *(s16 *)((u8 *)&cam_tracks[0].on + off) = 0;
        off -= sizeof(TrackRec);
    } while (off >= 0);
}

TrackRec *cam_track_slot_get(s32 i) {
    return &cam_tracks[i];
}

void cam_track_set_on(s32 n, s32 value) {
    cam_tracks[n].on = value;
}

/* Points camera rec->index at the target: for each active TrackRec of cam_tracks it transforms the three
 * parts' points, sets the camera position and then the angles towards the second point. */
void cam_tracks_step(void) {
    s32 *v = scratch_alloc(0x20);
    s32 ang[2];
    TrackRec *rec;
    s32 dx, dy, dz;
    s32 i;
    s32 yaw, pitch;

    scratch_alloc(0x40);
    rec = cam_tracks;
    for (i = 0; i < 8; i++, rec++) {
        if (rec->on) {
            cam_track_part_eval((CamTrackPart *)rec->part[3], v, 1);
            cam_set_scale(rec->index, v[0], v[1]);
            cam_track_part_eval((CamTrackPart *)rec->part[0], v, 1);
            cam_set_pos(rec->index, v[0], v[1], v[2]);
            cam_track_part_eval((CamTrackPart *)rec->part[1], &v[4], 1);
            dx = v[4] - v[0];
            dy = v[5] - v[1];
            dz = v[6] - v[2];
            vector_to_angles(dx, dy, dz, &ang[0], &ang[1]);
            ang[0] = -ang[0];
            if (dx == 0 && dz == 0) {
                ang[0] = rec->unk_80;
                if (dy == 0) {
                    ang[1] = rec->unk_82;
                }
            }
            yaw = ang[0];
            pitch = ang[1];
            rec->unk_80 = yaw;
            rec->unk_82 = pitch;
            cam_track_part_eval((CamTrackPart *)rec->part[2], v, 1);
            cam_set_rot(rec->index, ang[0], ang[1], v[2]);
        }
    }
    scratch_top -= 0x60;
}

void fn_800E8A34(void) {

}

void view_slots_reset(void) {
    view_slots_clear();
}

void view_slots_clear(void) {
    s32 offset = 0x99C;

    do {
        *(s16 *)(view_recs_on + offset) = 0;
        offset -= 0xA4;
    } while (offset >= 0);
}

/* Entry `index` of the table at 0x80128C20. */
ViewRec *view_rec_get(s32 index) {
    return &view_recs[index];
}

/* Set the halfword at 0xA0 of entry `index` of the table at 0x80128C20, and the same in view_set_on's table. */
void view_rec_set_on(s32 index, s32 value) {
    view_recs[index].enabled = value;
    view_set_on(index, value);
}

void fn_800E8AE4(void) {

}

void view_recs_apply(void) {
    s32 *out = scratch_alloc(0x10);
    ViewRec *rec = view_recs;
    s32 i = 0;

    for (; i < 16; i++, rec++) {
        if (rec->enabled != 0) {
            cam_track_part_eval((CamTrackPart *)rec, out, 1);
            set_view_offset(*(s16 *)rec->unk_A2, out[0], out[1]);
            cam_track_part_eval((CamTrackPart *)((u8 *)rec + 0x20), out, 1);
            view_set_size(*(s16 *)rec->unk_A2, out[0], out[1]);
            cam_track_part_eval((CamTrackPart *)((u8 *)rec + 0x40), out, 1);
            view_set_pivot(*(s16 *)rec->unk_A2, out[0], out[1]);
            cam_track_part_eval((CamTrackPart *)((u8 *)rec + 0x60), out, 1);
            fn_800C94D8(*(s16 *)rec->unk_A2, out[0], out[1]);
            cam_track_part_eval((CamTrackPart *)((u8 *)rec + 0x80), out, 1);
            view_set_clip_size(*(s16 *)rec->unk_A2, out[0], out[1]);
        }
    }
    scratch_top -= 0x10;
}

void cam_track_reset(void) {
    cam_track_clear_active();
}

/* Clears `unk_80` of the 32 TrackRec records in cam_track_recs. */
void cam_track_clear_active(void) {
    s32 off = 0x1078;
    do {
        *(s16 *)((u8 *)&cam_track_recs[0].unk_80 + off) = 0;
        off -= sizeof(TrackRec);
    } while (off >= 0);
}

/* Entry `index` of the table at 0x80129660. */
TrackRec *cam_track_get(s32 index) {
    return &cam_track_recs[index];
}

void cam_track_set_active(s32 index, s32 value) {
    cam_track_recs[index].unk_80 = value;
}

/* Ages the 32 track records in cam_track_recs (0x88 bytes each, state at +0x80): counts `on` down, then `index`, and deactivates when index reaches 0. */
void part_recs_step(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        TrackRecState *r = (TrackRecState *)&cam_track_recs[i].unk_80;

        if (r->active != 0) {
            if (r->on > 0) {
                r->on--;
            } else if (r->index > 0) {
                r->index--;
                if (r->index <= 0) {
                    r->active = 0;
                }
            }
        }
    }
}

s32 part_pose_blend(s32 start) {
    s32 weight;
    s32 sp10;
    s32 sp14;
    s32 handle;

    weight = 0x1000 - (start & 0xFFF);
    start >>= 12;
    start += part_pose_base;
    handle = pchr_blend(start, start + 1, weight, 0);
    pchr_get_link(start, &sp10, &sp14);
    if (sp14 != 0) {
        pchr_set_link_offsets(handle, 1, sp10, start + sp14 - handle);
    }
    sp14 = fn_800CDE8C(start);
    pchr_set_value_range(handle, 1, sp14);
    sp14 = pchr_get_angle(start);
    pchr_set_angle_range(handle, 1, sp14);
    return handle;
}

static inline void spark_add_rot(s32 colour, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value) {
    SparkList *list = &spark_list;
    s32 n = spark_count;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[colour >> 24];
        list->tail[colour >> 24] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}
void part_recs_emit_sparks(void) {
    s32 *pos = scratch_alloc(0x20);
    u8 *mat = scratch_alloc(0x40);
    TrackRec *rec = cam_track_recs;
    s32 i = 0;
    s32 *pos2 = pos + 4;
    s32 yaw, pitch, roll;
    s32 value;

    for (; i < 0x20; i++, rec++) {
        if (rec->unk_80 != 0 && rec->on <= 0) {
            cam_track_part_eval((CamTrackPart *)rec->part[0], pos, 1);
            cam_track_part_eval((CamTrackPart *)rec->part[1], pos2, 1);
            vector_to_angles(pos[4] - pos[0], pos[5] - pos[1], pos[6] - pos[2], &yaw, &pitch);
            rot_matrix(mat, yaw, pitch, 0);
            cam_track_part_eval((CamTrackPart *)rec->part[2], pos2, 1);
            rot_matrix(mat + 0x20, pos[4], pos[5], pos[6]);
            mul_matrix(mat, mat + 0x20, mat);
            matrix_to_angles(mat, &yaw, &pitch, &roll);
            cam_track_part_eval((CamTrackPart *)rec->part[3], pos2, 0);
            value = part_pose_blend(pos[4]);
            spark_add_rot(rec->unk_82 << 24, pos[0], pos[1], pos[2], yaw, pitch, roll, value);
        }
    }
    scratch_top -= 0x60;
}

void part_rec_reset(void) {
    part_rec_clear_active();
}

/* Clears `unk_80` of the 32 TrackRec records in part_recs. */
void part_rec_clear_active(void) {
    s32 off = 0x1078;
    do {
        *(s16 *)((u8 *)&part_recs[0].unk_80 + off) = 0;
        off -= sizeof(TrackRec);
    } while (off >= 0);
}

TrackRec *part_rec_get(s32 index) {
    return &part_recs[index];
}

/* Sets the halfword at +0x80 of record `index` of the 0x88-byte table at part_recs. */
void part_rec_set_active(s32 index, s32 value) {
    part_recs[index].unk_80 = value;
}

void countdown_rec_step(void) {
    s32 i;

    for (i = 0; i < 32; i++) {
        TrackRecState *r = (TrackRecState *)&part_recs[i].unk_80;

        if (r->active != 0) {
            if (r->on > 0) {
                r->on--;
            } else if (r->index > 0) {
                r->index--;
                if (r->index <= 0) {
                    r->active = 0;
                }
            }
        }
    }
}

/* For each active part rec (unk_80 set, timer `on` run out) that passes part_rec_visible,
 * transforms parts 1-3 and appends an id-table record in slot unk_82. */
void cam_tracks_emit_ids(void) {
    s32 *v = scratch_alloc(0x40);
    TrackRec *rec;
    s32 i;

    rec = part_recs;
    for (i = 0; i < 32; i++, rec++) {
        if (rec->unk_80 != 0 && rec->on <= 0 && part_rec_visible(rec, v, rec->unk_82) != 0) {
            cam_track_part_eval((CamTrackPart *)rec->part[1], &v[4], 1);
            cam_track_part_eval((CamTrackPart *)rec->part[2], &v[8], 1);
            cam_track_part_eval((CamTrackPart *)rec->part[3], &v[12], 1);
            {
                s32 level = rec->unk_82 << 24;
                s32 depth = v[8] + part_offset;
                s32 x = v[0], y = v[1], z = v[12];
                s32 f08 = v[4], f0A = v[5], f0C = v[6];
                IdTable *tbl;
                s32 slot;
                s32 index;
                IdRecord *r;

                /* scheduling barrier + register-held table address: the record values load first */
                do {
                } while (0);
                __asm__("" : "=r"(tbl) : "0"(&id_table));
                index = tbl->count;
                slot = level >> 24;
                if (index < 0x100) {
                    tbl->count = index + 1;
                    r = (IdRecord *)((u8 *)tbl + (index * 0x14 + 0x24));
                    r->prev_id = tbl->id[slot];
                    tbl->id[slot] = index;
                    r->field_00 = x;
                    r->field_02 = y;
                    r->field_04 = z;
                    r->field_0E = depth;
                    r->field_08 = f08;
                    r->field_0A = f0A;
                    r->field_0C = f0C;
                    r->field_10 = level;
                }
            }
        }
    }
    scratch_top -= 0x40;
}

void text_slots_reset(void) {
    text_slots_clear();
}

/* Clears the s16 of the 16 records in text_slots. */
void text_slots_clear(void) {
    s32 off = 0x12C;
    do {
        *(s16 *)((u8 *)&text_slots[0].unk_00 + off) = 0;
        off -= sizeof(TextSlotEntry);
    } while (off >= 0);
}

/* Returns the first of the 16 records in text_slots whose s16 at +0 is 0 (free slot), or NULL. */
TextSlotEntry *text_slot_find_free(void) {
    s32 i;
    TextSlotEntry *rec;
    s32 off;

    i = 0;
    rec = text_slots;
    off = 0;
    for (; i < 16; i++) {
        if (*(s16 *)((u8 *)text_slots + off) == 0) {
            return rec;
        }
        rec++;
        off += sizeof(TextSlotEntry);
    }
    return NULL;
}

/* stage_decls.h has track_get_enabled return s16; this caller uses the full word (no sll/sra). */
extern s32 fn_800DA2C8_s32(s32 index) __asm__("track_get_enabled");
void text_slots_step(void) {
    TextSlot *slot = (TextSlot *)text_slots;
    s32 i;
    u8 *cursor;
    s32 c;
    s16 index;

    i = 0;
    do {
        if (slot->active != 0) {
            if (fn_800DA2C8_s32(slot->id) == 0) {
                goto clear;
            }
            if (track_is_running(slot->id) == 0 && (s16)--slot->timer <= 0) {
                cursor = slot->cursor;
                if (cursor != NULL) {
                    goto have;
                }
            fetch:
                index = slot->index;
                if (slot->length < index) {
                clear:
                    slot->active = 0;
                } else {
                    slot->index = index + 1;
                    cursor = (u8 *)str_queue_get(index);
                    if (cursor == NULL) {
                        goto fetch;
                    }
                have:
                    c = *cursor++;
                    if (c == 0) {
                        goto fetch;
                    }
                    if (c == 0x5F) {
                        c = 0x20;
                    }
                    if (c == 0xA1) {
                        slot->timer = slot->delay_space;
                    } else {
                        slot->timer = slot->delay;
                    }
                    track_push_char(slot->id, c);
                    slot->cursor = cursor;
                }
            }
        }
        i++;
        slot++;
    } while (i < 16);
}

void fn_800E9440(void) {

}

/* 1 when ramp_from > ramp_to and ramp_active is 0. */
s32 ramp_is_done(void) {
    s32 result;

    result = 0;
    if (ramp_from > ramp_to) {
        result = ramp_active == 0;
    }
    return result;
}

void ramp_reset(void) {
    ramp_clear();
}

void ramp_clear(void) {
    ramp_active = 0;
    ramp_from = 0;
    ramp_to = 0;
}

s32 *ramp_get_state(void) {
    return (s32 *) &ramp_active;
}

void ramp_step(void) {
    u16 temp_v0;

    if (ramp_active != 0) {
        temp_v0 = ramp_pos + 1;
        ramp_pos = temp_v0;
        if (ramp_length < (s16) temp_v0) {
            ramp_pos = (u16) ramp_length;
        }
    }
}

void ramp_apply(void) {
    s16 *active = &ramp_active;
    s32 value;
    s32 total;
    s32 pos;

    FAKE_OPAQUE(active);
    if (*active != 0) {
        total = ramp_length;
        pos = (s16)ramp_pos;
        if (total == pos) {
            *active = 0;
        }
        value = ramp_to;
        if (total > 0) {
            value = (value - ramp_from) * pos / total + ramp_from;
        }
        cam_fade_set(value);
    }
}

/* Empties the 64-entry list str_queue (count str_queue_count). */
void str_queue_clear(void) {
    str_queue_count = 0;
}

/* Appends `value` to the 64-entry list str_queue (count str_queue_count) if there is room. */
void str_queue_push(s32 value) {
    s32 count = str_queue_count;

    if (count < 0x40) {
        str_queue_count = count + 1;
        str_queue[count] = value;
    }
}

s32 str_queue_get(s32 index) {
    if (index >= 0 && str_queue_count - 1 >= index) {
        return str_queue[index];
    }
    return 0;
}

/* Empties the 64-entry queue at stage_queue_values (stage_queue_count is its count). */
void stage_queue_clear(void) {
    stage_queue_count = 0;
}

/* Appends value to stage_queue_values unless it is full (64 entries). */
void stage_queue_push(s32 value) {
    s32 count = stage_queue_count;

    if (count < 0x40) {
        stage_queue_count = count + 1;
        stage_queue_values[count] = value;
    }
}

s32 value_queue_get(s32 index) {
    if (index >= 0) {
        if (index <= stage_queue_count - 1) {
            return stage_queue_values[index];
        }
    }
    return 0;
}
