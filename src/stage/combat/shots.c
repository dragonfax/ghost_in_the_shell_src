/* shots: one of the original source files (scripts/objmap.py); s01, s07. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

#if STAGE == 1
/* Traces the segment the shot covers this step; on a hit (or leaving the area) it turns into a burst. */
void shot_trace(Shot *shot, VECTOR *seg) {
    s32 hit_flag;

    if (shot->kind == 0) {
        seg[0].vx = 0;
        seg[0].vy = 0;
        seg[0].vz = 0x60;
        rotate_xz_twice(shot->yaw, shot->pitch, &seg[0].vx, &seg[0].vy, &seg[0].vz);
        seg[1].vx = 0;
        seg[1].vy = 0;
        seg[1].vz = -0x60;
        rotate_xz_twice(shot->yaw, shot->pitch, &seg[1].vx, &seg[1].vy, &seg[1].vz);
        seg[0].vx += shot->pos[0];
        seg[0].vy += shot->pos[1];
        seg[0].vz += shot->pos[2];
        seg[1].vx += shot->pos[0];
        seg[1].vy += shot->pos[1];
        seg[1].vz += shot->pos[2];
        seg[2] = seg[1];
        hit_flag = trace_shot_segment(&seg[0], &seg[1], &seg[2], 0x20, 8, 0xA);
        if (ABS(shot->pos[0]) >= 0xAF1) {
            hit_flag = 1;
            seg[2] = seg[1];
        }
        if (ABS(shot->pos[2]) >= 0xAF1) {
            hit_flag = 1;
            seg[2] = seg[1];
        }
        if (hit_flag) {
            shot->kind = 2;
            shot->keys = shot_burst_keys;
            tick_reset(&shot->tick);
            shot->key_from = 0xC6;
            shot->key_to = 0xC5;
            shot->key_t = 0;
            shot->pos[0] = seg[2].vx;
            shot->pos[1] = seg[2].vy;
            shot->pos[2] = seg[2].vz;
            shot->pitch = 0;
            shot->yaw = 0;
            shot->roll = 0;
            sound_play_at_units(SND_LASER_IMPACT | SND_GROUP(2), 0x7F, 0x3C, &seg[2]);
        }
    }
}

/* Runs shot_trace on each active record, with a 0x30-byte scratch block. */
void shots_trace(void) {
    Shot *rec = shot_slots;
    VECTOR *seg = scratch_alloc(0x30);
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (rec->active != 0) {
            shot_trace(rec, seg);
        }
        rec++;
    }
    scratch_top -= 0x30;
}

void shot_draw(Shot *rec) {
    s32 base;
    s32 value;
    s16 kind = rec->kind;

    switch (kind) {
    case 0:
        value = model_slot_pchr(*(s32 *)((Object *)rec->owner)->asset) + 0xC0;
        spark_add(rec->pos[0], rec->pos[1], rec->pos[2], rec->yaw, rec->pitch, rec->roll, value, kind);
        req_queue_push_vec(rec->pos[0], rec->pos[1], rec->pos[2]);
        break;
    case 1:
    case 2:
        base = model_slot_pchr(*(s32 *)((Object *)rec->owner)->asset);
        value = pool_spawn_scaled(pchr_blend(base + (s16)rec->key_from, model_slot_pchr(*(s32 *)((Object *)rec->owner)->asset) + (s16)rec->key_to, rec->key_t, 1), 0x2000, 0x2000, 0x2000);
        spark_add(rec->pos[0], rec->pos[1], rec->pos[2], rec->yaw, rec->pitch, rec->roll, value, 0x804040);
        break;
    }
}

/* Updates the 32 active entries of shot_slots. */
void shot_draw_all(void) {
    Shot *entry;
    s32 i;

    entry = shot_slots;
    i = 0;
    do {
        if (entry->active != 0) {
            shot_draw(entry);
        }
        i++;
        entry++;
    } while (i < 0x20);
}

Shot *shot_slot_find_free(void) {
    s32 i;
    Shot *slot = shot_slots;

    for (i = 0; i < 0x20; i++, slot++) {
        if (slot->active == 0) {
            return slot;
        }
    }
    return NULL;
}

/* Takes a free shot_slots record for owner at `pos` facing angles[0] (pitch), angles[1] (yaw), kind 0, and
 * sets loop_state_set_scale's value to 0x2000. */
void shot_pool_take(s32 owner, s32 *pos, u16 *angles) {
    Shot *slot;

    slot = shot_slot_find_free();
    if (slot != NULL) {
        slot->owner = owner;
        slot->yaw = angles[1];
        slot->pitch = angles[0];
        slot->pos[0] = pos[0];
        slot->pos[1] = pos[1];
        slot->pos[2] = pos[2];
        slot->active = 1;
        slot->kind = 0;
        loop_state_set_scale(0x2000);
    }
}

void shot_pool_clear(void) {
    Shot *rec = shot_slots;
    s32 i;

    for (i = 31; i >= 0; i--) {
        rec->active = 0;
        rec++;
    }
}

void shot_pool_reset(void) {
    shot_pool_clear();
}

/* Copies the position of the object that *objp points to into a scratch vector and passes it to
 * sound_set_pos with arg. */
s32 sound_track_pos(Object **objp, s32 arg) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = (*objp)->x;
    pos->y = (*objp)->y;
    pos->z = (*objp)->z;
    sound_set_pos(arg, pos);
    scratch_top -= 0x10;
    return 0;
}

/* Starts the state's sound (id 0xB004) if none is playing; the update callback is sound_track_pos. */
void loop_state_sound_start(LoopState *state) {
    s32 handle;

    if (state->sound == 0) {
        handle = sound_start(0xB004, 0x7F, 0, 0);
        state->sound = handle;
        if (handle != 0) {
            sound_attach(handle, state, (void (*)())sound_track_pos);
        }
    }
}

extern s32 shot_fire_sound_id;

void shot_fire_sound_stop(void) {
    if (shot_fire_sound_id != 0) {
        sound_stop(shot_fire_sound_id);
        shot_fire_sound_id = 0;
    }
}
#endif

#if STAGE == 7
extern Keyframe D_8011E04C[];
/* Traces a shot from the aim point in two rotated directions (buf is 12 words of scratch).
   A hit with damage 1 or 2 arms the shot and plays the hit sound at the hit point. */
void shot_trace(ShotSlot *shot, s32 *buf) {
    s32 *hit;
    s32 damage;

    if (shot->state == 0) {
        buf[0] = 0;
        buf[1] = 0;
        buf[2] = 0x60;
        rotate_xz_twice(shot->pitch, shot->yaw, &buf[0], &buf[1], &buf[2]);
        buf[4] = 0;
        buf[5] = 0;
        buf[6] = -0x60;
        rotate_xz_twice(shot->pitch, shot->yaw, &buf[4], &buf[5], &buf[6]);

        buf[0] += shot->pos[0];
        buf[1] += shot->pos[1];
        buf[2] += shot->pos[2];
        buf[4] += shot->pos[0];
        buf[5] += shot->pos[1];
        buf[6] += shot->pos[2];

        hit = &buf[8];
        *(Quad *)hit = *(Quad *)&buf[4];

        damage = trace_hit_damage(buf, &buf[4], hit, 0x20, 8, 0xA);
        if (damage < 3) {
            if (damage > 0) {
                shot->state = 2;
                shot->unk_24 = D_8011E04C;
                tick_reset((s32 *)shot->tick);
                shot->blend_from_offset = 0x131;
                shot->blend_to_offset = 0x130;
                shot->blend_factor = 0;
                shot->pos[0] = hit[0];
                shot->pos[1] = hit[1];
                shot->pos[2] = hit[2];
                shot->yaw = 0;
                shot->pitch = 0;
                shot->roll = 0;
                sound_play_at_units(SND_LASER_IMPACT | SND_GROUP(2), 0x7F, 0x3C, hit);
            }
        }
    }
}

extern Shot shot_table[32];
/* Runs shot_trace on each active shot, with a 0x30-byte scratch block. */
void shots_trace(void) {
    Shot *rec = shot_table;
    void *buf = scratch_alloc(0x30);
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (rec->active != 0) {
            shot_trace((ShotSlot *)rec, buf);
        }
        rec++;
    }
    scratch_top -= 0x30;
}

/* Shot effects by state. State 0 (in flight) adds a spark at the shot's position, valued by the owner's model
 * (offset 0x120), and queues the position. States 1 and 2 (hit) spawn a scaled effect between two model points
 * of the owner, then add a spark for it. */
void shot_draw(ShotSlot *shot) {
    s32 model_base;
    s32 from;
    s32 to;
    s32 value;

    switch (shot->state) {
    case 0:
        model_base = model_slot_pchr(*(s32 *)shot->owner->asset);
        value = model_base + 0x120;
        spark_add_head(&spark_list, shot->pos[0], shot->pos[1], shot->pos[2], shot->pitch, shot->yaw,
                       shot->roll, value, 0x555555);
        req_queue_push_vec(shot->pos[0], shot->pos[1], shot->pos[2]);
        break;
    case 1:
    case 2:
        from = model_slot_pchr(*(s32 *)shot->owner->asset);
        to = model_slot_pchr(*(s32 *)shot->owner->asset);
        value = pool_spawn_scaled(pchr_blend(from + shot->blend_from_offset, to + shot->blend_to_offset, shot->blend_factor, 1), 0x2000,
                                  0x2000, 0x2000);
        spark_add_head(&spark_list, shot->pos[0], shot->pos[1], shot->pos[2], shot->pitch, shot->yaw,
                       shot->roll, value, 0x804040);
        break;
    }
}

void shot_draw_all(void) {
    Shot *entry = shot_table;
    s32 i;

    for (i = 0; i < 0x20; i++, entry++) {
        if (entry->active != 0) {
            shot_draw((ShotSlot *)entry); /* the same record, ShotSlot's view */
        }
    }
}

extern Shot shot_table[32];
/* Same code as func_800C311C (s01). */
Shot *shot_slot_find_free(void) {
    s32 i;
    Shot *slot = shot_table;

    for (i = 0; i < 0x20; i++, slot++) {
        if (slot->active == 0) {
            return slot;
        }
    }
    return NULL;
}

Shot *shot_slot_find_free(void);
void set_timer_step(s16 arg0);
void marker_add(s32 owner, s32 *vec, u16 *dims) {
    MarkerEntry *rec;

    rec = shot_slot_find_free();
    if (rec != NULL) {
        rec->owner = owner;
        rec->unk_16 = dims[1];
        rec->unk_14 = dims[0];
        rec->pos_x = vec[0];
        rec->pos_y = vec[1];
        rec->pos_z = vec[2];
        rec->unk_20 = 1;
        rec->unk_22 = 0;
        set_timer_step(0x3000);
    }
}

extern Shot shot_table[32];
/* Same code as shot_pool_clear (s01). */
void shot_pool_clear(void) {
    Shot *rec = shot_table;
    s32 i;

    for (i = 31; i >= 0; i--) {
        rec->active = 0;
        rec++;
    }
}
#endif

#if STAGE == 1
s32 func_800C3324(s32 mode) {
    if (mode == 0) {
        if (loop_state_active != 0 && shot_fire_timer >= 0x80) {
            shot_fire_sound_stop();
            return 1;
        }
        return 0;
    }
    if (shot_fire_timer > 0) {
        return loop_state_active == 0;
    }
    return 1;
}
s32 fn_800C33A0(s32 mode) {
    return func_800C3324(mode);
}

void loop_state_set_scale(s16 value) {
    loop_state_scale = value;
}
#endif

#if STAGE == 7
void func_800C93BC(void) {
    shot_pool_clear();
}
extern s16 timer_active;
extern s16 timer_elapsed;
s32 is_timer_done(s32 mode) {
    if (mode == 0) {
        if (timer_active == 0) {
            return 0;
        }
        return timer_elapsed >= 0x80;
    }
    if (timer_elapsed > 0) {
        return timer_active == 0;
    }
    return 1;
}

extern s16 timer_scale;

void set_timer_step(s16 arg0) {
    timer_scale = arg0;
}
#endif

void loop_state_update(void) {
    LoopState *s = &loop_state;

    if (loop_state.active != 0) {
        s16 v;
        loop_state.level += loop_state.step;
        v = loop_state.level;
        if (v < 0) {
            loop_state.active = 0;
        }
        v = MAX(MIN(v, 0x80), 0);
        s->level = v;
        s->noisy = s->level + (rand_a_next() - 0x800) / 512;
        s->scale = s->scale > 0x1000 ? s->scale - 0x400 : 0x1000;
    }
}
