/* sound: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

s32 sound_volume_of(s32 id, s32 scale) {
    s32 volume = 0;
    s32 low = id & 0xFFFF;

    if (debug_check_b() != 0) {
        volume = slot_tone_volume(((((low >> 0xC) & 1) << 0x18) + ((low * 0x10) & 0x7F00)) | (id & 0xF));
    }
    return (volume * scale) / 0x1000;
}

/* Stores value in sound_mode and returns the previous value. */
s32 set_sound_mode(s32 value) {
    s32 prev;

    prev = sound_mode;
    sound_mode = value;
    if (debug_check_b() != 0) {
        slot_0B9(value);
    }
    return prev;
}

s32 get_sound_mode(void) {
    return sound_mode;
}

s16 sound_get_pitch(s32 handle) {
    return sound_handles[handle].pitch;
}

/* The volume of a sound handle in units of 128 (0..127). */
s32 fn_8010EF68(s32 handle) {
    return sound_handles[handle].pitch / 128;
}

/* The volume (+0x10) of sound handle `index` (0x44-byte handles at 0x801337BC). */
s16 sound_get_volume(s32 index) {
    return sound_handles[index].volume;
}

s16 sound_get_pan(s32 i) {
    return sound_handles[i].pan;
}

/* Clamp to 0..max. The if/else (not `if (v > max) v = max;`) keeps the original's copy of v, and
 * reusing v for the result keeps that copy in its own register: FINDINGS "Copies cse deletes". */
static inline s32 sound_clamp(s32 max, s32 v) {
    s32 clamped;
    s32 positive;

    if (v > max) {
        clamped = max;
    } else {
        clamped = v;
    }
    positive = clamped > 0;
    v = clamped & -positive;
    return v;
}

/* Sets a handle's level (0..127, kept << 7 in pitch), flags it changed; returns the old level. */
s32 sound_set_note(s32 handle, s16 level) {
    s32 old = sound_handles[handle].pitch / 128;

    sound_handles[handle].pitch = sound_clamp(0x7F, level) << 7;
    sound_handles[handle].changed[0] = 1;
    return old;
}

/* Sets a sound handle's pitch (14-bit), flags the handle, returns the old pitch. */
s16 sound_set_pitch(s32 handle, s16 pitch) {
    s16 old = sound_handles[handle].pitch;

    sound_handles[handle].pitch = pitch & 0x3FFF;
    sound_handles[handle].changed[0] = 1;
    return old;
}

/* Sets a handle's volume (0..127), flags it changed; returns the old volume. */
s16 sound_set_volume(s32 handle, s16 volume) {
    s16 old = sound_handles[handle].volume;

    sound_handles[handle].volume = sound_clamp(0x7F, volume);
    sound_handles[handle].changed[0] = 1;
    return old;
}

/* Sets a handle's pan (0..255), flags it changed; returns the old pan. */
s16 sound_set_pan(s32 handle, s16 pan) {
    s16 old = sound_handles[handle].pan;

    sound_handles[handle].pan = sound_clamp(0xFF, pan);
    sound_handles[handle].changed[0] = 1;
    return old;
}

/* Doppler pitch scale (0x1000 = 1.0): the listener's and the source's motion
 * since the last update, projected on the unit vector from source to listener. */
s32 sound_doppler_scale(VECTOR *listener, VECTOR *listenerPrev, VECTOR *src, VECTOR *srcPrev) {
    VECTOR *listenerVel = scratch_alloc(0x10);
    VECTOR *srcVel;
    VECTOR *toListener;
    VECTOR *unit;
    VECTOR *scaled;
    s32 ax, ay, az, listenerSpeed, srcSpeed, ratio;

    listenerVel->vx = listener->vx - listenerPrev->vx;
    listenerVel->vy = listener->vy - listenerPrev->vy;
    listenerVel->vz = listener->vz - listenerPrev->vz;
    srcVel = scratch_alloc(0x10);
    srcVel->vx = (src->vx - srcPrev->vx) >> 12;
    srcVel->vy = (src->vy - srcPrev->vy) >> 12;
    srcVel->vz = (src->vz - srcPrev->vz) >> 12;
    toListener = scratch_alloc(0x10);
    unit = scratch_alloc(0x10);
    toListener->vx = listener->vx - src->vx / 0x1000;
    toListener->vy = listener->vy - src->vy / 0x1000;
    toListener->vz = listener->vz - src->vz / 0x1000;
    scaled = scratch_alloc(0x10);
    ax = ABS(toListener->vx);
    ay = ABS(toListener->vy);
    az = ABS(toListener->vz);
    if (ax < ay) {
        ax = ay;
    }
    if (ax < az) {
        ax = az;
    }
    ax = 0x11 - Lzc(ax); /* shift that brings the largest component to 17 bits */
    if (ax < 0) {
        ax = 0;
    }
    scaled->vx = toListener->vx >> ax;
    scaled->vy = toListener->vy >> ax;
    scaled->vz = toListener->vz >> ax;
    VectorNormal(scaled, (SVECTOR *)unit);
    listenerSpeed = unit->vx * listenerVel->vx + unit->vy * listenerVel->vy + unit->vz * listenerVel->vz;
    srcSpeed = unit->vx * srcVel->vx + unit->vy * srcVel->vy + unit->vz * srcVel->vz;
    listenerSpeed >>= 12;
    srcSpeed >>= 12;
    scratch_top -= 0x10;
    listenerSpeed = MAX(MIN(listenerSpeed, 0x17FF), -0x17FF);
    srcSpeed = MAX(MIN(srcSpeed, 0x17FF), -0x17FF);
    ratio = ((0x1800 - listenerSpeed) << 12) / (0x1800 - srcSpeed);
    scratch_top -= 0x20;
    scratch_top -= 0x20;
    return ratio;
}

/* Closest point to sound_listener_pos on the segment a-b, written to out. */
void sound_closest_point(Vec3 *a, Vec3 *b, Vec3 *out) {
    s32 dx = b->x - a->x;
    s32 dy = b->y - a->y;
    s32 dz = b->z - a->z;
    s32 t;
    s32 step;

    if (dx == 0 && dz == 0) {
        if (dy == 0) {
            out->x = a->x;
            out->y = a->y;
            out->z = a->z;
            return;
        }
        t = ((sound_listener_pos.vy - a->y) << 12) / dy;
        t = NOT_NEGATIVE(t < 0x1001 ? t : 0x1000);
        step = dy * t;
        out->x = a->x;
        out->y = step / 0x1000 + a->y;
        out->z = a->z;
        return;
    }
    t = dx * (sound_listener_pos.vx - a->x);
    t += dz * (sound_listener_pos.vz - a->z);
    t = t / (length_sq(dx, dz, 0) / 4096);
    t = NOT_NEGATIVE(t < 0x1001 ? t : 0x1000);
    out->x = dx * t / 0x1000 + a->x;
    out->y = dy * t / 0x1000 + a->y;
    out->z = dz * t / 0x1000 + a->z;
}

void sound_alloc_init(void) {
    s32 i;

    for (i = 1; i <= 0x40; i++) {
        sound_alloc_pool[i].next = i + 1;
        sound_alloc_pool[i].unk_10 = 0;
        sound_alloc_pool[i].unk_14 = 0;
    }
    sound_alloc_free_head = 1;
    sound_alloc_pool[0].next = 0;
    sound_alloc_pool[0].tail = 0;
    sound_alloc_pool[0x40].next = 0;
    sound_alloc_used_tail = 0;
    sound_alloc_free_count = 0x40;
    for (i = 0; i <= 0x40; i++) {
        sound_alloc_states[i] = -1;
        alloc_owner_tags[i] = 0;
        alloc_free_tags[i] = 0;
        alloc_prev_tags[i] = 0;
    }
}

/* Takes the first record off the free list (sound_alloc_free_head), appends it to the
   used list (tail sound_alloc_used_tail) and tags it with the current owner. */
s32 alloc_block(void) {
    u8 head;
    s32 id;
    s32 *slot;
    s32 *free_slot;
    u8 tail;
    s32 used;
    s32 count;
    s32 owner;

    head = sound_alloc_free_head;
    tail = sound_alloc_used_tail;
    id = head;
    if (id == 0) {
        return 0;
    }
    sound_alloc_free_head = sound_alloc_pool[id].next;
    sound_alloc_pool[tail].next = head;
    slot = &sound_alloc_states[id];
    sound_alloc_pool[id].tail = tail;
    sound_alloc_pool[id].next = 0;
    count = sound_alloc_free_count;
    used = *slot;
    sound_alloc_used_tail = head;
    sound_alloc_free_count = count - 1;
    if (used == 0) {
        printf("Fatal: Aloc ID:%d (AlocBy:%X) (%X)\n", id, alloc_owner_tags[id], alloc_owner);
        debug_break();
    }
    free_slot = &alloc_free_tags[id];
    owner = alloc_owner;
    *slot = 0;
    alloc_owner_tags[id] = owner;
    alloc_prev_tags[id] = *free_slot;
    *free_slot = 0;
    return id;
}

void alloc_id_release(s32 id) {
    AllocLink *link;
    s32 caller_ra;
    u8 prev;
    u8 next;

    get_ra(caller_ra);
    if (id != 0) {
        if ((sound_alloc_states[id] != 0) || ((u32)id >= 0x41)) {
            printf("Fatal:Free ID:%d (Pre:%X Aloc:%X, Free:%X[%d]) (%X)<-(%X)\n", id, alloc_prev_tags[id], alloc_owner_tags[id], alloc_free_tags[id], sound_alloc_states[id], caller_ra, sound_release_caller);
            debug_break();
        }
        sound_alloc_states[id] = sound_release_reason;
        if (sound_release_caller == 0) {
            alloc_free_tags[id] = caller_ra;
        } else {
            alloc_free_tags[id] = sound_release_caller;
        }
        prev = sound_alloc_links[id].prev;
        next = sound_alloc_links[id].next;
        sound_alloc_links[prev].next = next;
        if (next != 0) {
            sound_alloc_links[next].prev = prev;
        }
        sound_alloc_links[id].next = sound_alloc_free_head;
        sound_alloc_free_head = id;
        if (sound_alloc_used_tail == id) {
            sound_alloc_used_tail = prev;
        }
        sound_alloc_free_count += 1;
    }
}

/* Counts down sound_fade_level by sound_fade_step (stopping both at zero), calls the debug hook with the
 * scaled value, then marks each sound record in the chain that starts at D_801337FF. */
void sound_fade_tick(void) {
    s32 idx;
    s32 off;
    s32 product;

    if (sound_fade_step == 0) {
        return;
    }
    sound_fade_level -= sound_fade_step;
    if (sound_fade_level <= 0) {
        sound_fade_level = 0;
        sound_fade_step = 0;
    }
    if (debug_check_b()) {
        product = sound_fade_rate * sound_fade_level;
        /* the hook is the function pointer stored at the literal address 0x800102A0 (slot_0A8) */
        (*(void (**)(s32))0x800102A0)(product / 0x1000);
    }

    idx = sound_handle_head;
    if (idx != 0) {
        do {
            off = (idx * 17) * 4;
            idx = *(u8 *)((u8 *)&sound_handle_head + off);
            *(u8 *)((u8 *)&sound_handle_dirty + off) = 1;
        } while (idx != 0);
    }
}

/* Passes value to slot_0A8 (debug builds only) and records it in sound_fade_rate. */
void sound_set_fade_rate(s32 value) {
    if (debug_check_b() != 0) {
        slot_0A8(value);
    }
    sound_fade_rate = value;
}

void sound_fade_start(s32 value) {
    sound_fade_step = value;
    sound_fade_level = 0x1000;
}

/* Passes value to slot_0AB when the debug check passes. */
void fn_8010FB5C(s32 value) {
    if (debug_check_b() != 0) {
        slot_0AB(value);
    }
}

/* Passes value to slot_0AA when the debug check passes. */
void fn_8010FBA0(s32 value) {
    if (debug_check_b() != 0) {
        slot_0AA(value);
    }
}

s32 fn_8010FBE4(void) {
    if (debug_check_b() != 0) {
        return slot_0A9();
    }
    return 0;
}

/* Stores id and flag (0 or 1) in sound_load_id/sound_load_flag and sets the handle sound_load_handle to -1. When the
 * debug check passes, the service slot_143 must accept the request (negative means failure). */
s32 sound_load_begin(s32 id, s32 flag) {
    s32 on;

    on = flag != 0;
    if (debug_check_b() != 0) {
        if (slot_143(id, on, 0) < 0) {
            return -1;
        }
    }
    sound_load_id = id;
    sound_load_flag = on;
    sound_load_handle = -1;
    return 0;
}

/* Fetches the value from slot_144 into sound_load_handle when the debug check passes. */
void sound_poll_load(void) {
    if (debug_check_b() != 0) {
        sound_load_handle = slot_144();
    }
}

s32 sound_load_finish(void) {
    if (sound_load_id < 0 || sound_load_handle < 0) {
        return -1;
    }
    if (debug_check_b() != 0) {
        return slot_143(sound_load_id, sound_load_flag, sound_load_handle);
    }
    return 0;
}

/* 1 when the debug check fails; else whether the service result is non-negative. */
u32 sound_is_ready(void) {
    if (debug_check_b() != 0) {
        return (u32)~slot_156() >> 31;
    }
    return 1;
}

s32 sound_is_fading(void) {
    return sound_fade_level != 0;
}

void sound_set_pos(s32 i, Vec3 *src) {
    u8 *base = sound_alloc_pool;
    Vec3 *dst = (Vec3 *)(base + i * 0x44);
    u8 *keep = base;

    FAKE_OPAQUE(keep);
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

void sound_reset_fade(void) {
    sound_fade_step = 0;
    sound_fade_level = 0x1000;
    sound_alloc_init();
}

/* Resets the sound state: sound_poll_load, sound_timer_stop, then the services when the debug check passes. */
void sound_reset_state(void) {
    sound_poll_load();
    sound_timer_stop();
    if (debug_check_b() != 0) {
        slot_0B3();
        slot_0B7(0);
        slot_0A4(0);
        slot_0B9(0);
        slot_0A3(1);
    }
}

/* Stage setup of the sound code (probably: its neighbours are sound functions). */
void sound_stage_init(void) {
    s32 *data = get_area_entry();
    s32 arg = 0;

    if (data != NULL) {
        arg = data[8];
    }
    sound_alloc_init();
    sound_active_flag = 1;
    sound_paused = 0;
    sound_load_handle = -1;
    sound_load_id = -1;
    sound_timer_stop();
    sound_set_master_volume(0x1000);
    sound_set_fade_rate(0x3B00);
    if (debug_check_b() != 0) {
        slot_0B3();
        slot_0A4(0x3FFF);
        slot_0B7(1);
        set_sound_mode(arg);
    }
    sound_listener_prev_pos = sound_listener_pos;
}

void sound_set_listener_pos(s32 x, s32 y, s32 z) {
    sound_listener_pos.vx = x;
    sound_listener_pos.vy = y;
    sound_listener_pos.vz = z;
}

VECTOR *sound_get_listener_pos(void) {
    return &sound_listener_pos;
}

void sound_set_listener_angles(s32 a, s32 b, s32 c) {
    sound_listener_pitch = a;
    sound_listener_yaw = b;
    sound_listener_roll = c;
}

s16 *sound_get_listener_angles(void) {
    return &sound_listener_pitch;
}

/* Volume and pan of a sound at pos (12-bit fixed point) relative to the listener: returns pan << 8 | volume (0..0x7F),
 * the volume scaled by distance, the pan from the direction in the listener's rotated frame. */
s32 sound_calc_vol_pan(VECTOR *pos, s32 volume) {
    s32 *mat = scratch_alloc(0x20);
    s32 m0, m1, m2;
    s32 dx, dy, dz;
    s32 dist;
    s32 pan;
    s32 vol;

    rot_matrix_b(mat, sound_listener_yaw, sound_listener_pitch, sound_listener_roll);
    gte_load_R012(mat, m0, m1, m2);
    gte_load_R34(mat, m0, m1);
    dx = pos->vx;
    dy = pos->vy;
    dz = pos->vz;
    dx >>= 12;
    dy >>= 12;
    dz >>= 12;
    dx -= sound_listener_pos.vx;
    dy -= sound_doppler_origin_y;
    dz -= sound_doppler_origin_z;
    dist = isqrt(length_sq(dx, dy, dz));
    gte_set(IR1, dx);
    gte_set(IR2, dy);
    gte_set(IR3, dz);
    gte_rtir();
    gte_get(MAC1, dx);
    gte_get(MAC2, dy);
    gte_get(MAC3, dz);
    if (dist < 0x300) {
        dx = dx * (s16)rcossin_tbl[((dist << 10) / 768) & 0xFFF] / 4096;
    }
    pan = ((atan2(dz, dx) >> 4) + 0x3F) & 0xFF;
    dist -= 0x600;
    dist /= 5;
    dist = MAX(MIN(dist, 0x3FF), 0);
    vol = volume * (0x1000 - (s16)rcossin_tbl[dist & 0xFFF]) >> 12;
    scratch_top -= 0x20;
    vol = MAX(MIN(vol, 0x7F), 0);
    return (pan << 8) + vol;
}

/* Stores arg in sound_master_volume, then flags every handle on the chain that starts at handle 0's next. */
void sound_set_master_volume(s32 arg) {
    u8 index;

    index = sound_handles[0].next;
    sound_master_volume = arg;
    if (index != 0) {
        do {
            sound_handles[index].changed[0] = 1;
            index = sound_handles[index].next;
        } while (index != 0);
    }
}

s32 sound_get_master_volume(void) {
    return sound_master_volume;
}

void sound_toggle_pause(void) {
    sound_paused = sound_paused == 0;
    if ((debug_check_b() != 0) && (sound_paused != 0)) {
        sound_timer_notify(0);
        sound_voices_update();
    }
}

s32 sound_is_paused(void) {
    return sound_paused;
}

/* Sound key-on: fills the request block at sound_key_cmd and asks the boot exe for a channel. */
s32 sound_play(s32 id, s32 unused, s32 pan, s32 note) {
    s32 level;
    s32 tone;
    s32 vol;
    s32 pitch;
    s32 mode;
    s32 *block;

    if (debug_check_b() != 0) {
        s32 key = id & 0xFFFF;

        tone = 0;
        if (debug_check_b() != 0) {
            tone = slot_tone_volume(((((key >> 12) & 1) << 24) + ((key << 4) & 0x7F00)) | (id & 0xF));
        }
        pitch = note << 7;
        block = &sound_key_cmd;
        *block = 0xB7;
        vol = tone;
        FAKE_OPAQUE(vol);
        if (id & 0x800) {
            sound_key_cmd |= 0x100;
        }
        mode = (id >> 13) & 3;
        sound_key_cmd |= 0x40;
        if (mode == 3) {
            mode = 0;
        }
        sound_key_voice = (((id >> 12) & 1) << 24) + ((id << 4) & 0x7F00) + (id & 0xF);
        sound_key_mode = sound_clamp(2, (s8)mode);
        sound_key_volume = sound_clamp(0x7F, ((vol * sound_master_volume) / 4096 * sound_fade_level) / 4096);
        SCHED_BARRIER();
        sound_key_pan = pan & 0xFF;
        level = pitch / 128;
        sound_key_pitch = pitch - level * 128;
        sound_key_note = sound_clamp(0x7F, level);
        sound_key_rate = 0x1000;
        return slot_snd_alloc_channel(block);
    }
    return -1;
}

static inline s32 snd_clamp_mode(s32 max, s32 v) {
    s32 clamped;

    if (v > max) {
        clamped = max;
    } else {
        clamped = v;
    }
    v = clamped > 0;
    return clamped & -v;
}
static inline s32 snd_clamp_volume(s32 v, s32 lo, s32 hi) {
    s32 flag;

    if (v > hi) {
        v = hi;
    }
    flag = v > lo;
    v &= -flag;
    return v;
}
static inline s32 snd_clamp_key(s32 v, s32 lo, s32 hi) {
    s32 flag;

    if (v > hi) {
        v = 0x7F;
    }
    flag = v > lo;
    return v & -flag;
}
/* Keys on sound `id` at its VAB tone volume, with pan and pitch (note * 128); -1 when sound is off. */
s32 sound_play_note(s32 id, s32 unused, s32 pan, s32 note) {
    s32 tone_volume;
    s32 level;
    s32 channel;
    s32 mode;
    s32 key;
    s32 volume;
    s32 pan_byte;
    s32 key_max;
    s32 pitch;
    s32 fine;
    s32 coarse;
    s32 bank_id;
    s32 lo;
    s32 max;
    s32 *block;

    if (debug_check_b() != 0) {
        tone_volume = 0;
        bank_id = id & 0xFFFF;
        if (debug_check_b() != 0) {
            tone_volume = slot_tone_volume(((((bank_id >> 12) & 1) << 24) + ((bank_id << 4) & 0x7F00)) | (id & 0xF));
        }
        block = &sound_key_cmd;
        *block = 0xB7;
        FAKE_OPAQUE(block);
        OPAQUE_COPY(level, tone_volume);
        pitch = note << 7;
        if (id & 0x800) {
            sound_key_cmd |= 0x100;
        }
        channel = (id >> 13) & 3;
        sound_key_cmd |= 0x40;
        if (channel == 3) {
            channel = 0;
        }
        sound_key_voice = (((id >> 12) & 1) << 24) + ((id << 4) & 0x7F00) + (id & 0xF);
        mode = snd_clamp_mode(2, channel);
        SCHED_BARRIER();
        fine = pitch;
        sound_key_mode = mode;
        pan_byte = pan & 0xFF;
        SCHED_BARRIER();
        lo = 0;
        FAKE_OPAQUE(lo);
        sound_key_volume = 0;
        sound_key_pan = pan_byte;
        max = 0x7F;
        if (fine < 0) {
            fine += 127;
        }
        coarse = fine >> 7;
        ((SoundVoiceRequest *)block)->fine_pitch = pitch - coarse * 128;
        OPAQUE_COPY(key_max, 0x7F);
        key = snd_clamp_key(coarse, lo, key_max);
        SCHED_BARRIER();
        sound_key_note = key;
        sound_key_rate = 0x1000;
        volume = snd_clamp_volume(level, lo, max);
        SCHED_BARRIER();
        sound_key_volume = volume;
        return slot_snd_alloc_channel(block);
    }
    return -1;
}

static inline s32 sound_clamp_reuse(s32 max, s32 v) {
    s32 clamped;

    if (v > max) {
        clamped = max;
    } else {
        clamped = v;
    }
    v = clamped > 0;
    return clamped & -v;
}
/* Fills the sound request block and allocates a channel for it; -1 when sound is off. */
s32 sound_keyon(s32 id, s32 volume, s32 pan, s32 pitch, s32 scale, s32 loop) {
    s32 channel;
    s32 level;
    s32 fine;
    s32 coarse;
    s32 *block;

    if (debug_check_b() != 0) {
        block = &sound_key_cmd;
        *block = 0xB7;
        fine = pitch;
        if (id & 0x800) {
            sound_key_cmd |= 0x100;
        }
        if (loop != 0) {
            sound_key_cmd |= 0x40;
        }
        channel = (id >> 13) & 3;
        if (channel == 3) {
            channel = 0;
        }
        sound_key_voice = (((id >> 12) & 1) << 24) + ((id << 4) & 0x7F00) + (id & 0xF);
        sound_key_mode = sound_clamp_reuse(2, channel);
        level = ((volume * sound_master_volume) / 4096 * sound_fade_level) / 4096;
        sound_key_volume = sound_clamp_reuse(0x7F, level);
        do { } while (0); /* keeps the pitch copy below the level store */
        sound_key_pan = pan & 0xFF;
        coarse = fine / 128;
        sound_key_pitch = pitch - coarse * 128;
        fine = coarse;
        sound_key_note = sound_clamp_reuse(0x7F, fine);
        sound_key_rate = sound_clamp_reuse(0x3FFF, scale);
        return slot_snd_alloc_channel(block);
    }
    return -1;
}

static inline s32 snd_fixed_mul(s32 a, s32 b) {
    return a * b / 0x1000;
}
static inline s32 snd_clamp_to_max(s32 v, s32 max) {
    s32 flag;

    if (v > max) {
        v = max;
    }
    flag = v > 0;
    return v & -flag;
}
/* Start sound `sound` with a volume, pan and pitch (note * 128 + fine) through the sound request block. */
s32 sound_note_request(s32 sound, s32 volume, s32 pan, s32 note) {
    s32 *block;
    s32 pitch;
    s32 fine;
    s32 octave;
    s32 max;
    s32 vol;
    s32 ret;

    if (debug_check_b() != 0) {
        pitch = note << 7;
        fine = pitch;
        block = &sound_key_cmd;
        *block = 0x96;
        sound_key_sound = sound;
        sound_key_cmd |= 0x40;
        vol = snd_fixed_mul(snd_fixed_mul(volume, sound_master_volume), sound_fade_level);
        max = 0x7F;
        vol = snd_clamp_to_max(vol, max);
        sound_key_volume = vol;
        sound_key_pan = pan & 0xFF;
        octave = pitch / 128;
        sound_key_pitch = fine - octave * 128;
        sound_key_note = snd_clamp_to_max(octave, max);
        sound_key_rate = 0x1000;
        ret = slot_snd_alloc_channel(block);
    } else {
        ret = -1;
    }
    return ret;
}

static inline s32 snd_clamp_value(s32 v, s32 max) {
    s32 r;

    if (v > max) {
        r = max;
    } else {
        r = v;
    }
    v = r > 0;
    return r & -v;
}

/* Start sound `sound` with a volume, pan, pitch (octave * 128 + fine) and rate through the sound request
 * block; `flag` sets bit 0x40 of the command. */
s32 sound_voice_update(s32 sound, s32 volume, s32 pan, s32 pitch, s32 rate, s32 flag) {
    s32 *block;
    s32 value;
    s32 octave;
    s32 max;
    s32 vol;
    s32 ret;

    if (debug_check_b() != 0) {
        block = &sound_key_cmd;
        *block = 0x96;
        value = pitch;
        if (flag != 0) {
            sound_key_cmd |= 0x40;
        }
        sound_key_sound = sound;
        vol = snd_fixed_mul(snd_fixed_mul(volume, sound_master_volume), sound_fade_level);
        max = 0x7F;
        vol = snd_clamp_to_max(vol, max);
        sound_key_volume = vol;
        sound_key_pan = pan & 0xFF;
        octave = value / 128;
        sound_key_pitch = pitch - octave * 128;
        value = octave;
        sound_key_note = snd_clamp_to_max(octave, max);
        sound_key_rate = snd_clamp_value(rate, 0x3FFF);
        ret = slot_snd_alloc_channel(block);
    } else {
        ret = -1;
    }
    return ret;
}

/* Sends a sound request (command 0x240, one argument) in the block at 0x80134900 to boot service 0x800102C4. */
s32 sound_voice_request(s32 arg) {
    s32 *block;

    if (debug_check_b() != 0) {
        block = &sound_key_cmd;
        *block = 0x240;
        sound_key_sound = arg;
        return slot_snd_alloc_channel(block);
    }
    return -1;
}

/* Steps every sound handle that has its update bit (0x8000 in id): the two words of its voice go through
 * sound_voice_request (the second only while it is not negative). */
void sound_voices_update(void) {
    u8 handle;
    SoundHandle *sh;

    handle = sound_handles[0].next;
    if (handle != 0) {
        do {
            sh = &sound_handles[handle];
            if (sh->id & 0x8000) {
                s32 *voice = (s32 *)sh->voices;

                voice[0] = sound_voice_request(voice[0]);
                if (voice[1] >= 0) {
                    voice[1] = sound_voice_request(voice[1]);
                }
            }
            handle = sh->next;
        } while (handle != 0);
    }
}

/* Stops the sound handles marked 0x8000 in the chain that starts at handle 0 (byte 0x43 of a handle is
 * the index of the next one). */
void sound_stop_all(void) {
    u8 index;
    u8 current;
    SoundHandle *handle;

    index = ((u8 *)&sound_handles[0])[0x43];
    if (index != 0) {
        do {
            current = index;
            handle = &sound_handles[index];
            index = ((u8 *)handle)[0x43];
            if (handle->id & 0x8000) {
                sound_stop(current);
            }
        } while (index != 0);
    }
    sound_active_flag = 0;
}

void sound_voice_release(s32 value) {
    if (debug_check_b() != 0) {
        void (*service)(s32 *block) = slot_sound_key_on;
        s32 *field = &sound_key_sound;

        FAKE_OPAQUE(service); /* keeps the slot load before the store */
        *field = value;
        service(field - 2);
    }
}

s32 sound_voice_keyon(s32 value) {
    s32 *block;

    if (debug_check_b() != 0) {
        block = &sound_key_sound;
        *block = value;
        if (value == slot_0B0(block - 2)) {
            return 1;
        }
    }
    return 0;
}

/* sound_play_at (docs/FINDINGS.md): plays sound `id` at a 3D position; sound_calc_vol_pan turns the position
 * and the sound's volume into volume (low 7 bits) and pan (bits 8+). `unused` is ignored. */
void sound_play_at(s32 id, s32 unused, s32 note, void *pos) {
    s32 vol_pan;

    vol_pan = sound_calc_vol_pan(pos, sound_volume_of(id, 0x1000));
    sound_keyon(id, vol_pan & 0x7F, vol_pan >> 8, note << 7, 0x1000, 1);
}

/* Plays sound id at a position given in whole units: the volume and pan come from the position
 * (sound_calc_vol_pan), the pitch from note. The volume argument is not used. */
void sound_play_at_units(s32 id, s32 volume, s32 note, void *pos) {
    SoundPos *p = scratch_alloc(0x10);
    s32 mix;

    *p = *(SoundPos *)pos;
    p->pos.x <<= 12;
    p->pos.y <<= 12;
    p->pos.z <<= 12;
    mix = sound_calc_vol_pan((VECTOR *)p, sound_volume_of(id, 0x1000));
    scratch_top -= 0x10;
    sound_keyon(id, mix & 0x7F, mix >> 8, note << 7, 0x1000, 1);
}

/* Play a sound positioned at `pos`: sound_calc_vol_pan gives the volume (low 7 bits) and pan (bits 8+). */
void sound_play_at_volume(s32 sound, s32 volume, s32 note, VECTOR *pos) {
    s32 vp = sound_calc_vol_pan(pos, volume);

    sound_note_request(sound, vp & 0x7F, vp >> 8, note);
}

void sound_handle_slots_update(void) {
    SoundHandleSlot *h;
    void *owner;
    void *pos;
    u8 index;
    u8 loop;
    u8 next;
    u16 volume;
    u16 pan;
    u16 pitch;
    s32 vol_pan;

    next = sound_handle_head;
    if (next != 0) {
        do {
            index = next;
            h = &((SoundHandleSlot *)sound_handles)[index];
            next = h->next;
            if (h->delay == 0) {
                volume = h->volume;
                pan = h->pan;
                h->delay--;
                pitch = h->pitch;
                loop = h->flags & 1;
                owner = h->owner;
                if (owner != NULL) {
                    pos = h->update != NULL ? h->update(owner, index) : owner;
                    if (pos == NULL) {
                        pos = &h->default_pos;
                    }
                    if (h->flags & 4) {
                        h->saved_pos = *(SoundPos *)pos;
                    }
                    vol_pan = sound_calc_vol_pan(pos, (s16)volume);
                    volume = vol_pan & 0x7F;
                    if (!(h->flags & 2)) {
                        pan = (u32)vol_pan >> 8;
                    } else {
                        pan = 0x3F;
                    }
                }
                if (h->id_b != 0) {
                    h->voice_b = sound_keyon(h->id_b, (s16)volume, (s16)pan, (s16)pitch, 0x1000, loop);
                } else {
                    h->voice_b = -1;
                }
                h->voice_a = sound_keyon(h->id_a, (s16)volume, (s16)pan, (s16)pitch, 0x1000, loop);
            } else if (h->delay < 0) {
                if (h->timer >= 0) {
                    h->timer--;
                    if (h->timer == 0) {
                        sound_voice_release(h->voice_a);
                        if (h->voice_b >= 0) {
                            sound_voice_release(h->voice_b);
                        }
                        if (!(h->flags & 8)) {
                            sound_release_reason = 1;
                            alloc_id_release(index);
                            sound_release_reason = -1;
                        }
                    }
                }
            } else {
                h->delay--;
            }
        } while (next != 0);
    }
}

void sound_handles_update(void) {
    u8 next = sound_handle_head;
    SoundHandleFull *h;
    s16 volume, pan, pitch, scale;
    s32 loop, voice0, voice1;
    u32 id;
    VECTOR *p;

    if (next != 0) do {
        u8 index = next;
        h = (SoundHandleFull *)&sound_handles[index];
        next = h->next;
        if (h->delay < 0) {
        volume = h->volume;
        pan = h->pan;
        id = h->id.word;
        loop = h->flags & 1;
        scale = 0x1000;
        pitch = h->pitch;
        if (h->owner != 0) {
            s32 v;
            if (h->update != 0) {
                p = (VECTOR *)h->update(h->owner, index);
            } else {
                p = (VECTOR *)h->owner;
            }
            if (p == 0) {
                p = &h->pos;
            }
            v = sound_calc_vol_pan(p, volume);
            volume = v & 0x7F;
            if (!(h->flags & 2)) {
                pan = v >> 8;
            } else {
                pan = 0x3F;
            }
            if (h->flags & 4) {
                scale = sound_doppler_scale(&sound_listener_pos, &sound_listener_prev_pos, &h->last_pos, p);
                h->last_pos = *p;
            }
            h->dirty = 1;
        }
        voice0 = sound_voice_keyon(h->voice[0]);
        if (h->voice[1] >= 0) {
            voice1 = sound_voice_keyon(h->voice[1]);
        } else {
            voice1 = 0;
        }
        if (!(id & 0x8000)) {
        if (!(h->flags & 8) && (voice0 | voice1) == 0) {
            sound_release_reason = 2;
            alloc_id_release(index);
            sound_release_reason = -1;
            goto next_handle;
        } else if (h->dirty) {
            if (voice0 != 0) {
                sound_voice_update(h->voice[0], volume, pan, pitch, scale, loop);
            }
            if (voice1 != 0) {
                sound_voice_update(h->voice[1], volume, pan, pitch, scale, loop);
            }
        }
        } else {
            if (voice0 == 0) {
                if (volume != 0) {
                    h->voice[0] = sound_keyon(h->id.half[0], volume, pan, pitch, scale, loop);
                }
            } else if (h->dirty) {
                sound_voice_update(h->voice[0], volume, pan, pitch, scale, loop);
            }
            if (h->voice[1] >= 0) {
                if (voice1 == 0) {
                    if (volume != 0) {
                        h->voice[1] = sound_keyon(h->id.half[1], volume, pan, pitch, scale, loop);
                    }
                } else if (h->dirty) {
                    sound_voice_update(h->voice[1], volume, pan, pitch, scale, loop);
                }
            }
        }
        h->dirty = 0;
        next_handle:;
        }
    } while (next != 0);
    sound_listener_prev_pos = sound_listener_pos;
}

/* One step of the countdown in sound_timer. While sound_is_paused reports set, sound_timer_notify(0) runs first.
 * The step that reaches zero runs sound_timer_stop; any other step runs sound_timer_notify(1). */
void sound_timer_tick(void) {
    s32 remaining;

    if (sound_timer != 0) {
        if (sound_is_paused() != 0) {
            sound_timer_notify(0);
        }
        remaining = sound_timer - 1;
        sound_timer = remaining;
        if (remaining == 0) {
            sound_timer_stop();
            return;
        }
        sound_timer_notify(1);
    }
}

void sound_frame_update(void) {
    sound_timer_tick();
    sound_handle_slots_update();
    sound_fade_tick();
}

void sound_update(void) {
    sound_handles_update();
}

s32 sound_start(s32 id, s32 volume, s32 delay, s32 extra) {
    SoundHandle *sound;
    s32 caller;
    s32 slot;
    register s32 tone_volume __asm__("$19");
    s32 clamped;
    s32 in_range;
    s32 key;
    register s32 stale_a0 __asm__("$4"); /* never set: the call passes whatever a0 holds */

    get_ra(caller);
    if (sound_active_flag == 0 && (id & 0x8000)) {
        return 0;
    }
    alloc_owner = caller;
    slot = alloc_block();
    alloc_owner = 0;
    if (slot == 0) {
        return 0;
    }
    sound = &sound_handles[slot];
    do {
    } while (0);
    in_range = volume < 0x80;
    clamped = volume;
    if (!in_range) {
        clamped = 0x7F;
    }
    tone_volume = 0;
    key = id & 0xFFFF;
    sound->id = id;
    sound->delay = delay;
    sound->unk_0E = extra;
    /* debug_check_b is a stub (returns 1); the original passes it the clamped volume in a1 */
    if (((s32 (*)(s32, s32)) debug_check_b)(stale_a0, clamped) != 0) {
        tone_volume = slot_tone_volume((((key >> 12) & 1) << 24) + ((key << 4) & 0x7F00) | (id & 0xF));
    }
    sound->pan = 0x40;
    sound->pitch = 0x1E00;
    sound->volume = tone_volume;
    sound->owner = NULL;
    sound->update = NULL;
    sound->flags = 1;
    sound->changed[0] = 0;
    return slot;
}

/* Releases a sound handle: key-offs its voices and runs alloc_id_release with sound_release_caller set to the caller's
 * return address and sound_release_reason to 3 (restored to 0 and -1 after). */
void sound_stop(s32 handle) {
    SoundHandle *sound;
    s32 caller;
    s32 second;

    get_ra(caller);
    if (handle != 0 && sound_active_flag != 0) {
        sound = &sound_handles[handle];
        if (sound->id & 0x8000) {
            sound_voice_release(*(s32 *) &sound->voices[0]);
            second = *(s32 *) &sound->voices[4];
            if (second != -1) {
                sound_voice_release(second);
            }
            sound_release_caller = caller;
            sound_release_reason = 3;
            alloc_id_release(handle);
            sound_release_reason = -1;
            sound_release_caller = 0;
        }
    }
}

void sound_stop_list(void) {
    u8 handle;
    u8 next;

    next = sound_handle_head;
    while (next != 0) {
        handle = next;
        next = sound_handles[handle].next;
        sound_stop(handle);
    }
}

/* Makes sound handle `handle` (0: none) follow a position. */
void sound_attach(s32 handle, void *owner, void (*update)()) {
    if (handle != 0) {
        SoundHandle *sound = &sound_handles[handle];
        sound->owner = owner;
        sound->update = update;
    }
}

/* Sets or clears flag bit 2 of entry i (entry 0 is never touched). */
void sound_set_flag_bit2(s32 i, s32 on) {
    if (i != 0) {
        SoundHandle *sound = &sound_handles[i];
        sound->flags = (sound->flags & ~4) | ((on & 1) << 2);
    }
}

/* Set or clear bit 1 of entry `index`'s flags (entry 0 is never changed). */
void sound_set_flag_bit1(s32 index, s32 on) {
    SoundHandle *sound;

    if (index != 0) {
        sound = &sound_handles[index];
        sound->flags = (sound->flags & ~2) | ((on & 1) << 1);
    }
}

void sound_set_flag_bit0(s32 handle, s32 on) {
    if (handle != 0) {
        SoundHandle *sound = &sound_handles[handle];
        sound->flags = (sound->flags & ~0x1) | (on & 1);
    }
}

void sound_set_flag_bit3(s32 handle, s32 on) {
    if (handle != 0) {
        SoundHandle *sound = &sound_handles[handle];
        sound->flags = (sound->flags & ~0x8) | ((on & 1) << 3);
    }
}

/* Calls one of two services with 0 when the debug check passes. */
void sound_timer_notify(s32 which) {
    void (*handler)(s32);

    if (debug_check_b() != 0) {
        if (which == 1) {
            handler = slot_042;
        } else {
            handler = slot_043;
        }
        handler(0);
    }
}

void sound_timer_set(u32 level) {
    if (level >= (u32) sound_timer) {
        sound_timer = level;
        sound_timer_notify(1);
    }
}

void sound_timer_stop(void) {
    sound_timer_notify(0);
    sound_timer = 0;
}

s32 sound_attached_update(s32 *list, s32 slot) {
    Vec3 *origin = scratch_alloc(0x10);
    Vec3 *tmp = scratch_alloc(0x10);
    Vec3 *best = scratch_alloc(0x10);
    u32 best_dist;
    s32 count;
    SoundSegment *seg;
    u32 dist;

    best->z = 0;
    best->y = 0;
    best->x = 0;
    origin->x = sound_listener_pos.vx;
    origin->y = sound_listener_pos.vy;
    origin->z = sound_listener_pos.vz;
    best_dist = -1;
    if (list != NULL) {
        count = *list;
        seg = (SoundSegment *)(list + 1);
        if (count > 0) {
            do {
                sound_closest_point(&seg->start, &seg->end, tmp);
                dist = isqrt(length_sq(tmp->x - origin->x, tmp->y - origin->y, tmp->z - origin->z));
                if (dist < best_dist) {
                    best->x = tmp->x;
                    best->y = tmp->y;
                    best_dist = dist;
                    best->z = tmp->z;
                }
                count--;
                seg++;
            } while (count > 0);
        }
    }
    best->x <<= 12;
    best->y <<= 12;
    best->z <<= 12;
    sound_set_pos(slot, best);
    scratch_top -= 0x30;
    return 0;
}

/* Start a sound attached to `owner` (updated by sound_attached_update) and set its flag bit 1. */
s32 sound_start_attached(s32 a, s32 b, void *owner) {
    s32 handle = sound_start(a, b, 0, 0);

    sound_attach(handle, owner, (void (*)())sound_attached_update);
    sound_set_flag_bit1(handle, 1);
    return handle;
}

/* Stops the sound at `handle`. */
void fn_80111D08(s32 handle) {
    sound_stop(handle);
}

/* Scales pos's offset from the sound listener by scale/4096 (fixed point). */
void sound_scale_pos_about_listener(VECTOR *pos, VECTOR *out, s32 scale)
{
    s32 x, y, z;

    x = pos->vx - sound_listener_pos.vx;
    y = pos->vy - sound_doppler_origin_y;
    z = pos->vz - sound_doppler_origin_z;
    x = sound_listener_pos.vx + x * scale / 4096;
    y = sound_doppler_origin_y + y * scale / 4096;
    z = sound_doppler_origin_z + z * scale / 4096;
    out->vx = x;
    out->vy = y;
    out->vz = z;
}
