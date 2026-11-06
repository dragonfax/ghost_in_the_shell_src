/* screen_fade: one of s01's own original source files (scripts/objmap.py); part of src/s01/main.c's unit, included there. */

/* Tears an object down: resets the two globals, frees its asset-driven index and removes it. */
void giant_robot_teardown(Object *obj) {
    s32 offset;
    s32 index;

    meter_set_mode(0);
    set_d_801202C8(0);
    giant_robot_systems_teardown();
    index = obj->type.unk_0E;
    offset = model_slot_pchr(*(s32 *)obj->asset);
    obj_spawn_replacement(obj, index + offset);
    obj_free(obj);
}


extern s16 fade_colour_x_from[][2];
extern s16 fade_colour_x_to[][2];
extern s16 fade_colour_y_from[][2];
extern s16 fade_colour_y_to[][2];
/* Colour for a fade level 0..0xFFF: interpolates two s16 tables in 8
   steps of 512; returns (black << 16) | (y << 8) | x. */
s32 fade_colour_from_level(s32 level)
{
    s32 unused[4];
    s32 weight;
    s32 inv;

    register s32 x asm("$2");
    register s32 term asm("$6");
    register s32 value asm("$3");
    s32 y, black;

    level = MAX(MIN(level, 0xFFF), 0);
    weight = level;
    if (weight == 0) {
        return 0;
    }
    x = weight / 512;
    weight -= x << 9;
    weight *= 8;
    y = x;
    value = fade_colour_x_from[y][0];
    term = value * (inv = 0x1000 - weight);
    value = fade_colour_x_to[y][0] * weight;
    x = term + value;
    if (x < 0) {
        x += 0xFFF;
    }
    value = fade_colour_y_from[y][0];
    term = value * inv;
    value = fade_colour_y_to[y][0] * weight;
    y = (term + value) / 4096;
    x >>= 17;
    y >>= 5;
    black = (x | y) == 0;
    return (black << 16) | (y << 8) | x;
}

extern s32 fade_amount;

s32 get_fade_level(void) {
    return fade_amount;
}

extern s32 fade_amount;

void set_fade_level(s32 arg0) {
    fade_amount = arg0;
}

extern s32 fade_amount;

void set_fade_full(void) {
    fade_amount = 0x1000;
}

void fade_step(void) {
    s32 value;

    value = get_fade_level();
    if (fade_dir == 1) {
        value += 0x18;
    } else {
        value -= 0x18;
    }
    value = MAX(MIN(value, 0xFFF), 0);
    set_fade_level(value);
}

extern s32 fade_dir;

void set_fade_dir(s32 arg0) {
    fade_dir = arg0;
}

/* Sets the mode flag fade_dir to 1 and applies it. */
void fade_in_full(void) {
    fade_dir = 1;
    set_fade_full();
}

/* Clears the mode flag fade_dir and applies it. */
void fade_clear(void) {
    fade_dir = 0;
    set_fade_full();
    set_fade_level(0);
}

void shot_update(Shot *rec) {
    s32 move_x;
    s32 move_y;
    s32 move_z;
    s32 x;
    s32 y;
    s32 z;

    switch (rec->kind) {
    case 0:
        move_x = 0;
        move_y = 0;
        move_z = 0x30;
        rotate_xz_twice(rec->yaw, rec->pitch, &move_x, &move_y, &move_z);
        x = move_x + rec->pos[0];
        y = move_y + rec->pos[1];
        move_x = x;
        move_y = y;
        z = move_z + rec->pos[2];
        move_z = z;
        if (cam_point_in_zone(0, x, y, z, 0x3A98, 0x1770, 0x1770) == 0) {
            rec->active = 0;
        }
        rec->pos[0] = move_x;
        rec->pos[1] = move_y;
        rec->pos[2] = move_z;
        break;
    case 1:
    case 2:
        if (keyframe_step(&rec->keys, &rec->tick, &rec->key_from, &rec->key_to, &rec->key_t) == 0) {
            rec->active = 0;
        }
        break;
    }
}

/* Runs shot_update on each active record. */
void shots_update(void) {
    Shot *rec = shot_slots;
    s32 i = 0;

    do {
        if (rec->active != 0) {
            shot_update(rec);
        }
        i++;
        rec++;
    } while (i < 32);
}
