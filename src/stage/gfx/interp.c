/* interp: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

void interp_set_enabled(s32 arg0) {
    interp_enabled_flag = arg0;
}

void interp_reset_all(void) {
    interp_enabled_flag = 1;
    interp_reset_count();
    interp1c_clear();
    interp2c_clear();
    interp38_clear();
    interp38b_clear();
}

void interp_start_all(void) {
    interp_restart_records();
    interp1c_start_all();
    interp2c_restart_all();
    interp38_restart_all();
    interp38b_restart_all();
}

void interp_step_all(void) {
    interp_step_records();
    interp1c_step_all();
    interp2c_run_scripts();
    interp38_run_scripts();
    interp38b_run_scripts();
}

void interp_sample_all(s32 arg0, s32 arg1) {
    interp_sample_records();
    interp1c_draw_all(arg0, arg1);
    interp2c_draw_all(arg0, arg1);
    interp38_run_all();
    interp38b_run_all();
}

/* Resets an Interp: v = {0, 0, 0, 1, 0, 0}. */
void interp_reset(Interp *interp) {
    interp->v[0] = 0;
    interp->v[1] = 0;
    interp->v[2] = 0;
    interp->v[3] = 1;
    interp->v[4] = 0;
    interp->v[5] = 0;
}

/* Advances a script: applies entries (writing word `field` of the runner) until one sets a repeat
 * count, then moves pos by speed and counts the repeats down. */
void script_runner_step(Interp *interp) {
    ScriptRunner *runner = (ScriptRunner *)interp;
    s16 *script;
    s32 count;
    ScriptEntry *entries;
    s32 field;
    s32 value;
    s16 next;
    s16 *words;

    if (runner->running == 0) {
        return;
    }
    script = runner->script;
    count = script[0];
    if (count == 0) {
        return;
    }
    entries = (ScriptEntry *) (script + 1);
    words = (s16 *) runner;
    if (runner->repeat == 0) {
        do {
            field = entries[runner->cursor].field;
            value = entries[runner->cursor].value;
            next = runner->cursor + 1;
            runner->cursor = next;
            if (next >= count) {
                runner->cursor = 0;
            }
            words[field] = value;
        } while (runner->repeat == 0);
    }
    if (interp_enabled_flag != 0) {
        runner->pos += runner->speed;
        if (runner->repeat > 0) {
            runner->repeat--;
        }
    }
}

s32 angle_state_value(AngleState *state) {
    s32 flags = state->flags;
    s32 angle = state->angle;
    s32 mode = flags & 6;
    s32 v;
    s32 idx;
    if (mode != 0 && mode == 2) {
        idx = (angle & 0xFFF) >> 1;
        v = cos_table[idx].value;
        if (angle & 1) {
            v = (v + cos_table[idx + 1].value) / 2;
        }
        v = (0x1000 - v) / 2;
        if (v >= 0x1000) v = 0xFFF;
    } else {
        v = angle & 0xFFF;
    }
    if ((flags & 1) && (angle & 0x1000)) {
        v = 0xFFF - v;
    }
    return v;
}

/* Samples a keyframe track at a position (12 fractional bits) and starts the interpolated sound/animation state. */
void interp_sample_track(u8 *rec) {
    s16 *data = *(s16 **)(rec + 0x14);
    s32 count = data[2];
    s32 prod;
    s32 whole;
    s32 next;
    s32 base;
    s32 first;
    s32 handle;
    s32 track;
    s32 ref;
    s32 sp10;
    s32 sp14;

    prod = count * angle_state_value((AngleState *)(rec + 4));
    whole = prod >> 12;
    prod = 0x1000 - (prod & 0xFFF);
    next = whole;
    next = next + 1;
    if (next >= data[2]) {
        next = 0;
    }
    base = point_base;
    first = data[3] + base;
    handle = pchr_blend(whole + first, next + first, prod, data[1]);
    track = data[0];
    ref = track + base;
    pchr_get_link(ref, &sp10, &sp14);
    if (sp14 != 0) {
        pchr_set_link_offsets(handle, 1, sp10, rec_get_flags(track + sp14) + base - handle);
    }
    sp14 = fn_800CDE8C(ref);
    pchr_set_value_range(handle, 1, sp14);
    sp14 = pchr_get_angle(ref);
    pchr_set_angle_range(handle, 1, sp14);
    rec_set_flags(track, handle - base);
}

void interp_reset_count(void) {
    interp_record_count = 0;
}

/* Claims the next free interpolation record for the script data at `data` (its entries start
 * 8 bytes in) and returns its index. When all 32 are taken there is no return statement: the
 * original leaves the failed comparison (0) in v0. */
s32 interp_alloc_record(s32 data)
{
    s32 index = interp_record_count;

    if (index < 32) {
        InterpRec18 *rec = &interp_records[index];
        rec->script_data = data;
        data += 8;
        ((ScriptRunner *)&rec->part)->script = (s16 *)data;
        interp_record_count = index + 1;
        return index;
    }
}

/* Set the state of entry `index` (if valid); state 2 resets it (interp_reset) and becomes 1. */
void interp_set_state(s32 index, s32 state) {
    InterpRec18 *rec;

    if (index >= 0) {
        rec = &interp_records[index];
        if (state == 2) {
            state = 1;
            interp_reset(&rec->part);
        }
        rec->state = state;
    }
}

/* Restarts every active interpolation record: state 1, then its six values reset. */
void interp_restart_records(void) {
    s32 i;

    for (i = 0; i < interp_record_count; i++) {
        interp_records[i].state = 1;
        interp_reset(&interp_records[i].part);
    }
}

/* Steps every interpolation record that is in state 1 (script_runner_step runs its update). */
void interp_step_records(void) {
    s32 i;

    for (i = 0; i < interp_record_count; i++) {
        if (interp_records[i].state == 1) {
            script_runner_step(&interp_records[i].part);
        }
    }
}

void interp_sample_records(void) {
    s32 unused;
    s32 i;

    for (i = 0; i < interp_record_count; i++) {
        interp_sample_track((u8 *)&interp_records[i]);
    }
}

#if STAGE == 1 || STAGE == 6 || STAGE == 10 || STAGE == 12
RectU mask_buf_rect = {0x300, 0x0, 0x100, 0xD8};
#endif

/* Dispatches on bits 12-15 of `code` to one of five helpers and stores the result in *out:
 * 0x20 for kinds 0-2, 1 for kinds 3-4. Kinds 5-15 leave *out alone. */
void cmd_dispatch(s32 unused, s32 code, s32 *a, s32 *b, s32 *out) {
    s32 result;

    switch (code >> 12) {
    case 0:
        model_texel_to_vram(unused, code & 0xFFF, a, b);
        result = 0x20;
        break;
    case 1:
        clut_xy_get(code & 0xFFF, a, b);
        result = 0x20;
        break;
    case 2:
        tile_pos_grid16(code & 0xFFF, a, b);
        result = 0x20;
        break;
    case 3:
        tile_pos_wide(code & 0xFFF, a, b);
        result = 1;
        break;
    case 4:
        tile_pos_code((code & 0xF00) >> 8, code & 0xFF, a, b);
        result = 1;
        break;
    default:
        return;
    }
    *out = result;
}

/* Draws one gauge bar of an InterpRec1C into the work area's OT slot. The bar is two primitives: the
 * part already filled (params[0] * params[1] scaled by the angle) and the lit remainder, which is
 * params[3] cut to the bar's free width. */
void interp1c_draw_rec(InterpRec1C *rec, WorkArea *work, s32 slot) {
    s16 *params;
    s32 scale;
    s32 fill_x;
    s32 lit;
    s32 full;
    s32 ot_off;
    s32 ax, ay, bx, by, h;
    GaugePrim *prim;

    params = *(s16 **)&rec->unk_14[0];
    scale = params[0];
    fill_x = (scale * angle_state_value((AngleState *)&rec->part)) >> 12;
    fill_x *= params[1];
    cmd_dispatch(*(s32 *)&rec->unk_14[4], params[4], &ax, &ay, &h);
    cmd_dispatch(*(s32 *)&rec->unk_14[4], params[2], &bx, &by, &h);

    full = params[3];
    lit = params[0] * params[1] - fill_x;
    if (full < lit) {
        lit = full;
    }
    full -= lit;

    prim = (GaugePrim *)work->packet;
    work->packet = prim + 1;
    prim->len = 5;
    prim->code = 1;
    prim->unk_08 = 0x80000000;
    prim->w = lit;
    prim->x0 = ax + fill_x;
    prim->y0 = ay;
    prim->x1 = bx;
    prim->y1 = by;
    prim->h = h;
    ot_off = slot * 4;
    addPrim((u32 *)(ot_off + (s32)work->ot), prim);

    if (full > 0) {
        prim = (GaugePrim *)work->packet;
        work->packet = prim + 1;
        prim->len = 5;
        prim->code = 1;
        prim->unk_08 = 0x80000000;
        prim->w = full;
        prim->x0 = ax;
        prim->y0 = ay;
        prim->x1 = bx + lit;
        prim->y1 = by;
        prim->h = h;
        addPrim((u32 *)(ot_off + (s32)work->ot), prim);
    }
}

void interp1c_clear(void) {
    interp1c_count = 0;
}

/* Appends one entry to the InterpRec1C table (32 slots) and returns its index, or -1 if full. */
s32 interp1c_add(s32 val_a, s32 val_b) {
    InterpRec1C *rec;
    s32 index;

    index = interp1c_count;
    if (index >= 0x20) {
        return -1;
    }
    rec = &interp1c_table[index];
    *(s32 *)&rec->unk_14[0] = val_a;
    val_a += 0xA;
    *(s32 *)&rec->unk_14[4] = val_b;
    *(s32 *)rec->part.unk_0C = val_a;
    interp1c_count = index + 1;
    return index;
}

/* Sets record `index`'s state (ignored if negative); state 2 resets it and becomes 1. */
void interp1c_set_state(s32 index, s32 state) {
    if (index >= 0) {
        InterpRec1C *rec = &interp1c_table[index];

        if (state == 2) {
            state = 1;
            interp_reset(&rec->part);
        }
        rec->state = state;
    }
}

/* Starts each of the interp1c_count records of interp1c_table (state 1) and resets its interpolator. */
void interp1c_start_all(void) {
    s32 i;

    for (i = 0; i < interp1c_count; i++) {
        interp1c_table[i].state = 1;
        interp_reset(&interp1c_table[i].part);
    }
}

void interp1c_step_all(void) {
    s32 i;

    for (i = 0; i < interp1c_count; i++) {
        if (interp1c_table[i].state == 1) {
            script_runner_step(&interp1c_table[i].part);
        }
    }
}

/* Runs interp1c_draw_rec on every record of interp1c_table whose state is 1. */
void interp1c_draw_all(s32 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < interp1c_count; i++) {
        if (interp1c_table[i].state == 1) {
            interp1c_draw_rec(&interp1c_table[i], (WorkArea *)arg0, arg1);
        }
    }
}

void scroll_strip_draw(InterpRec2C *rec, WorkArea *work, s32 slot) {
    ScrollStripHeader *key;
    s32 tex[2];
    s32 ty;
    s32 tx;
    s32 mode;
    s32 x0;
    s32 shift;
    s32 y;
    s32 umask, vmask;
    s32 rows, h, u, cols, x, w, v;
    s16 px, py;
    s32 last;
    s32 tex_x;
    s32 y_off;
    s32 x_off;
    s32 tex_y;
    s32 phase;
    s32 period;
    GaugePrim *prim;

    key = rec->key;
    keyframe_lookup(rec->track, key->index, &tex[0], &tex[1], &mode);
    shift = 1;
    if (mode == 0) {
        shift = 2;
    }
    y_off = key->y_off;
    ty = tex[1];
    y = ty + y_off;
    tex_x = key->tex_x >> shift;
    tx = tex[0];
    tex[0] = tx + tex_x;
    tex_y = key->tex_y;
    x_off = key->x_off >> shift;
    tex[1] = ty + tex_y;
    x0 = tx + x_off;
    umask = ((key->tex_w >> shift) - 1) & 0xFF;
    vmask = (key->tex_h - 1) & 0xFF;
    period = key->wave_x_period;
    if (period >= 0) {
        if (key->wave_x_amp >= 0) {
            phase = (period * angle_state_value((AngleState *)&rec->part[0])) >> 12;
            phase *= key->wave_x_amp;
            phase >>= shift;
            v = key->wave_y_amp;
            v = (v * angle_state_value((AngleState *)&rec->part[1])) >> 12;
            v *= key->wave_y_scale;
            for (rows = key->height; rows > 0; rows -= h) {
                v &= vmask;
                last = v - 1;
                h = vmask - last;
                if (rows < h) {
                    h = rows;
                }
                x = x0;
                for (cols = key->width >> shift, u = phase; cols > 0; cols -= w) {
                    u &= umask;
                    last = u - 1;
                    w = umask - last;
                    if (cols < w) {
                        w = cols;
                    }
                    prim = work->packet;
                    work->packet = prim + 1;
                    prim->len = 5;
                    prim->code = 1;
                    prim->unk_08 = 0x80000000;
                    prim->x1 = x;
                    prim->y1 = y;
                    prim->w = w;
                    prim->h = h;
                    px = tex[0] + u;
                    py = tex[1] + v;
                    prim->x0 = px;
                    prim->y0 = py;
                    addPrim((u32 *)(slot * 4 + (s32)work->ot), prim);
                    u += w;
                    x += w;
                }
                v += h;
                y += h;
            }
        } else {
            phase = angle_state_value((AngleState *)&rec->part[0]);
            v = key->wave_y_amp;
            v = (v * angle_state_value((AngleState *)&rec->part[1])) >> 12;
            v *= key->wave_y_scale;
            for (rows = key->height; rows > 0; rows--) {
                u = (0x1000 - cos_table[phase & 0xFFF].value) / 2;
                v &= vmask;
                if (u > 0xFFF) {
                    u = 0xFFF;
                }
                u = (-key->wave_x_amp * u) / 4096;
                phase += 0x1000 / key->wave_x_period;
                h = (u & ((1 << shift) - 1)) * (vmask + 1) + v;
                u = (u >> shift) & umask;
                x = x0;
                for (cols = key->width >> shift; cols > 0; cols -= w) {
                    u &= umask;
                    last = u - 1;
                    w = umask - last;
                    if (cols < w) {
                        w = cols;
                    }
                    prim = work->packet;
                    work->packet = prim + 1;
                    prim->len = 5;
                    prim->code = 1;
                    prim->unk_08 = 0x80000000;
                    prim->x1 = x;
                    prim->y1 = y;
                    prim->w = w;
                    prim->h = 1;
                    px = tex[0] + u;
                    py = tex[1] + h;
                    prim->x0 = px;
                    prim->y0 = py;
                    addPrim((u32 *)(slot * 4 + (s32)work->ot), prim);
                    u += w;
                    x += w;
                }
                v++;
                y++;
            }
        }
    } else {
        phase = angle_state_value((AngleState *)&rec->part[0]);
        v = key->wave_y_amp;
        v = (v * angle_state_value((AngleState *)&rec->part[1])) >> 12;
        v *= key->wave_y_scale;
        for (rows = key->height; rows > 0; rows--) {
            h = (0x1000 - cos_table[phase & 0xFFF].value) / 2;
            if (h > 0xFFF) {
                h = 0xFFF;
            }
            h = (ABS(key->wave_x_amp) * h) / 4096;
            phase += 0x1000 / -key->wave_x_period;
            u = 0;
            h = (h + v) & vmask;
            x = x0;
            for (cols = key->width >> shift; cols > 0; cols -= w) {
                u &= umask;
                last = u - 1;
                w = umask - last;
                if (cols < w) {
                    w = cols;
                }
                prim = work->packet;
                work->packet = prim + 1;
                prim->len = 5;
                prim->code = 1;
                prim->unk_08 = 0x80000000;
                prim->x1 = x;
                prim->y1 = y;
                prim->w = w;
                prim->h = 1;
                px = tex[0] + u;
                py = tex[1] + h;
                prim->x0 = px;
                prim->y0 = py;
                addPrim((u32 *)(slot * 4 + (s32)work->ot), prim);
                u += w;
                x += w;
            }
            v++;
            y++;
        }
    }
}

void interp2c_clear(void) {
    interp2c_count = 0;
}

/* interp38b_add for the 0x2C records: two parts after a 0x1A-byte header; arg kept at +0x28. Returns the index or -1. */
s32 interp2c_add(void *script, s32 arg) {
    InterpRec2C *rec;
    s32 index;

    if (interp2c_count >= 32) {
        return -1;
    }
    rec = &interp2c_table[interp2c_count];
    rec->key = (ScrollStripHeader *)script;
    script += 0x1A;
    rec->track = arg;
    *(u8 **)rec->part[0].unk_0C = script;
    index = interp2c_count;
    script += *(s16 *)script * 4 + 2;
    interp2c_count = index + 1;
    *(u8 **)rec->part[1].unk_0C = script;
    return index;
}

/* Sets record `index`'s state (ignored if negative); state 2 resets it and becomes 1. */
void interp2c_set_state(s32 index, s32 state) {
    if (index >= 0) {
        InterpRec2C *rec = &interp2c_table[index];

        if (state == 2) {
            state = 1;
            interp_reset(&rec->part[0]);
            interp_reset(&rec->part[1]);
        }
        rec->state = state;
    }
}

void interp2c_restart_all(void) {
    s32 i;

    for (i = 0; i < interp2c_count; i++) {
        interp2c_table[i].state = 1;
        interp_reset(&interp2c_parts[i].part[0]);
        interp_reset(&interp2c_parts[i].part[1]);
    }
}

/* Steps both script runners of every interp2c_table record whose state is 1. */
void interp2c_run_scripts(void) {
    s32 i;

    for (i = 0; i < interp2c_count; i++) {
        if (interp2c_table[i].state == 1) {
            script_runner_step(&interp2c_parts[i].part[0]);
            script_runner_step(&interp2c_parts[i].part[1]);
        }
    }
}

/* Runs scroll_strip_draw on every record of interp2c_table whose state is 1. */
void interp2c_draw_all(s32 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < interp2c_count; i++) {
        if (interp2c_table[i].state == 1) {
            scroll_strip_draw(&interp2c_table[i], (WorkArea *)arg0, arg1);
        }
    }
}

void interp38_run_cmds(u8 *rec) {
    s16 *cmd = *(s16 **)(rec + 0x34);
    s32 a = angle_state_value((AngleState *)(rec + 4));
    s32 b = angle_state_value((AngleState *)(rec + 0x14));
    s32 c = angle_state_value((AngleState *)(rec + 0x24));
    s32 value = cmd[0];
    s32 count = cmd[1];
    s32 kind = value & 0xF000;

    value &= 0xFFF;
    switch (kind) {
    case 0:
        if (count > 0) {
            do {
                point_set_extra(value, a, b, c);
                count -= 1;
                value += 1;
            } while (count > 0);
        }
        break;
    case 0x3000:
        if (count > 0) {
            do {
                s32 low = value & 0xF;
                light_set_dir_from_angles(value >> 4, low, a, b);
                count -= 1;
                value = low + 1;
            } while (count > 0);
        }
        break;
    }
}

void interp38_clear(void) {
    interp38_count = 0;
}

/* Attaches a script to the next free interp38_table entry: after a 4-byte header come
 * three blocks, each a count followed by count 4-byte items (plus 2 bytes).
 * Returns the entry index, or -1 when the table is full. */
s32 interp38_add_script(s16 *script) {
    ScriptRec *rec;

    if (interp38_count >= 0x20) {
        return -1;
    }
    rec = (ScriptRec *)&interp38_table[interp38_count];
    rec->script = script;
    script += 2;
    rec->block0 = script;
    script += *script * 2 + 1;
    rec->block1 = script;
    script += *script * 2 + 1;
    rec->block2 = script;
    return interp38_count++;
}

/* Sets entry `index`'s state; state 2 resets its three parts and becomes 1. */
void interp38_set_state(s32 index, s32 state) {
    InterpRec38 *entry;

    if (index >= 0) {
        entry = &interp38_table[index];
        if (state == 2) {
            state = 1;
            interp_reset(&entry->part[0]);
            interp_reset(&entry->part[1]);
            interp_reset(&entry->part[2]);
        }
        entry->state = state;
    }
}

/* Restarts every interp38_table entry: state 1, its three parts reset. */
void interp38_restart_all(void) {
    s32 i;

    for (i = 0; i < interp38_count; i++) {
        interp38_table[i].state = 1;
        interp_reset(&interp38_parts[i].part[0]);
        interp_reset(&interp38_parts[i].part[1]);
        interp_reset(&interp38_parts[i].part[2]);
    }
}

void interp38_run_scripts(void) {
    s32 i;

    for (i = 0; i < interp38_count; i++) {
        if (interp38_table[i].state == 1) {
            script_runner_step(&interp38_parts[i].part[0]);
            script_runner_step(&interp38_parts[i].part[1]);
            script_runner_step(&interp38_parts[i].part[2]);
        }
    }
}

void interp38_run_all(void) {
    s32 i;

    for (i = 0; i < interp38_count; i++) {
        if (interp38_table[i].state == 1) {
            interp38_run_cmds((u8 *)&interp38_table[i]);
        }
    }
}

/* Interpolates each axis of the script record by its part's angle state, then runs the
 * record's type over `count` entries starting at `index`: type 0 -> rec_set_pos, 3 ->
 * rec_set_part (with the index split into rec and field), 4 -> rec_set_rgb. */
void interp38_run_span(InterpRec38 *arg0) {
    SpanRec *rec;
    s32 x0, x1;
    s32 y0, y1;
    s32 z0, z1;
    s32 x, y, z;
    s32 type;
    s32 index;
    s32 n;

    rec = *(SpanRec **)arg0->script;
    x0 = rec->x0;
    x1 = rec->x1;
    x = ((x1 - x0) * angle_state_value((AngleState *)&arg0->part[0]) + (x0 << 12)) >> 12;
    y1 = rec->y1;
    y0 = rec->y0;
    y = ((y1 - y0) * angle_state_value((AngleState *)&arg0->part[1]) + (y0 << 12)) >> 12;
    z0 = rec->z0;
    z1 = rec->z1;
    z = ((z1 - z0) * angle_state_value((AngleState *)&arg0->part[2]) + (z0 << 12)) >> 12;
    index = rec->code;
    type = index & 0xF000;
    index &= 0xFFF;
    n = rec->count;

    switch (type) {
    case 0:
        if (n > 0) {
            do {
                rec_set_pos(index, x, y, z);
                n -= 1;
                index += 1;
            } while (n > 0);
        }
        break;
    case 0x3000:
        if (n > 0) {
            do {
                rec_set_part(index >> 4, index & 0xF, x, y, z);
                n -= 1;
                index += 1;
            } while (n > 0);
        }
        break;
    case 0x4000:
        if (n > 0) {
            do {
                rec_set_rgb(index, x, y, z);
                n -= 1;
                index += 1;
            } while (n > 0);
        }
        break;
    }
}
