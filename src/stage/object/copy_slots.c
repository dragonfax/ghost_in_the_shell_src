/* copy_slots: one of the original source files (scripts/objmap.py); s04, s05, s10. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

extern CopySlot copy_slots[4];

/* Clears all four entries of copy_slots. The loop body advances the pointer before the counter (matches the original order). */
void copy_slots_clear(void) {
    CopySlot *p = copy_slots;
    s32 i = 0;

    do {
        p->used = 0;
        p->obj = 0;
        p++;
        i++;
    } while (i < 4);
}

#if STAGE == 4 || STAGE == 5
/* Claims the first free slot (flag 0) and returns its index, or -1 when all four are in use. */
s32 copy_slot_claim(void) {
    s32 *slot;
    s32 i;
    s32 found;

    found = -1;
    slot = &copy_slots;
    for (i = 0; i < 4; i++) {
        if (*slot == 0) {
            *slot = 1;
            found = i;
            break;
        }
        slot += 2;
    }
    return found;
}
#elif STAGE == 10
/* Claims the first free slot (flag 0) and returns its index, or -1 when all four are in use. */
s32 copy_slot_claim(void) {
    s32 *slot;
    s32 i;
    s32 found;

    found = -1;
    slot = &copy_slots[0].used;
    for (i = 0; i < 4; i++) {
        if (*slot == 0) {
            *slot = 1;
            found = i;
            break;
        }
        slot += 2;
    }
    return found;
}
#endif

/* Clears entry index of copy_slots, if index is below 4. */
void copy_slot_release(u32 index) {
    if (index < 4) {
        copy_slots[index].used = 0;
        copy_slots[index].obj = 0;
    }
}

/* Each stage's own effect helpers for the final blast. */
#if STAGE == 5
#define BLAST_FX_PREP func_800C4A8C
#define SPAWN_FX_PREP func_800C4B4C
#elif STAGE == 10
#define BLAST_FX_PREP func_800C8824
#define SPAWN_FX_PREP func_800C88E4
#else
#define BLAST_FX_PREP func_800C7AEC
#define SPAWN_FX_PREP func_800C7BAC
#endif
void BLAST_FX_PREP(s32 *pos);
void SPAWN_FX_PREP(s32 *pos);

/* Explosion sequence: random puffs for 120 frames, an indexed effect, then the final blast;
 * after 210 more frames it may end the stage, releases its copy slot and frees itself. */
void blast_seq_update(Object *obj, ObjHandler *handler) {
    s32 *pos;
    s16 *rot;
    s32 timer;
    register s32 x asm("$19");
    register s32 base_y asm("$16");
    s32 y;
    s32 z;
    s32 height;
    s32 size_x;
    s32 size_y;
    s32 size_z;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 even;

    switch (obj->vars.blast_seq.state) {
    case 1:
        timer = obj->vars.blast_seq.timer;
        if (timer & 1) {
            x = obj->x >> 12;
            height = (s16)obj->height;
            base_y = obj->y >> 12;
            y = base_y - height / 2;
            z = obj->z >> 12;
            size_x = obj->width;
            dx = (size_x * (rand_a_next() - 0x800)) >> 12;
            size_y = (s16)obj->height;
            dy = (size_y * (rand_a_next() - 0x800)) >> 12;
            size_z = obj->unk_1E8[0];
            dz = (size_z * (rand_a_next() - 0x800)) >> 12;
            even = timer / 2 % 2 == 0;
            spawn_effect(x + dx, y + dy, z + dz, (even * 2 + 0x7F00) | 0x80000000);
        }
        obj->vars.blast_seq.timer++;
        if (obj->vars.blast_seq.timer >= 0x78) {
            obj->vars.blast_seq.state = 2;
            obj->vars.blast_seq.timer = 0;
        }
        break;
    case 2:
        obj->vars.blast_seq.timer++;
        if (obj->vars.blast_seq.timer >= 0xC) {
            s32 *q = (s32 *)scratch_top;
            s32 cy;
            s32 h;
            q[0] = obj->x >> 12;
            h = (s16)obj->height;
            cy = obj->y;
            cy = (cy >> 12) - h / 2;
            q[1] = cy;
            q[2] = obj->z >> 12;
            scratch_top += 0x10;
            effect_spawn_indexed(q, obj->vars.blast_seq.slot);
            scratch_top -= 0x10;
            obj->vars.blast_seq.state = 3;
            obj->vars.blast_seq.timer = 0;
        }
        break;
    case 4:
        obj->vars.blast_seq.state = 5;
        obj->vars.blast_seq.timer = 0;
        break;
    case 5:
        obj->vars.blast_seq.timer++;
        if (obj->vars.blast_seq.timer >= 6) {
            obj->vars.blast_seq.state = 6;
            obj->vars.blast_seq.timer = 0;
        }
        break;
    case 6:
        pos = (s32 *)scratch_top;
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        scratch_top += 0x10;
        rot = (s16 *)scratch_top;
        rot[0] = obj->pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        scratch_top += 8;
        if (obj->vars.blast_seq.ends_stage == 1) {
            BLAST_FX_PREP(pos);
            pos[1] -= (s16)obj->height / 2;
            blast_effect_spawn(pos, rot, obj->vars.blast_seq.fx_index);
            scratch_top -= 8;
        } else {
            SPAWN_FX_PREP(pos);
            pos[1] -= (s16)obj->height / 2;
            obj_spawn_with_fx(pos, rot, obj->vars.blast_seq.fx_index);
            scratch_top -= 8;
        }
        scratch_top -= 0x10;
        obj->vars.blast_seq.state = 7;
        obj->vars.blast_seq.timer = 0;
        break;
    case 7:
        obj->vars.blast_seq.timer++;
        if (obj->vars.blast_seq.timer >= 0xD2) {
            if (obj->vars.blast_seq.ends_stage != 0) {
                set_stage_end(2);
            }
            obj->vars.blast_seq.state = 8;
            copy_slot_release(obj->vars.blast_seq.slot);
            obj_free(obj);
        }
        break;
    }
}

#if STAGE != 10
extern void (*effect_callback_table[])();
extern RecTemplate effect_template;
#endif

#if STAGE == 10
extern RecTemplate effect_template;
extern void (*effect_callback_table[])();
#endif

/* Spawns the effect template splash_table with the callback D_8011D418[index] (fx_spawn_template). */
void effect_spawn_indexed(s32 *owner, s32 index) {
    fx_spawn_template(owner, &effect_template, effect_callback_table[index]);
}

/* Sets the byte at 0x2C from the 0x18 word (divided by 6144), clears bytes 0x2D, 0x2E and 0x2F, and
   when the 0x18 word is not positive or the 0x1C link word is positive, sets the sound state of copy slot 0's object. */
void obj_fade_level(Object *obj) {
    u8 *bytes = (u8 *) obj->rot_angles;

    bytes[1] = 0;
    bytes[2] = 0;
    bytes[0] = ((0x1000 - *(s32 *) &obj->type.unk_0C / 6144) * 0xFF) >> 0xC;
    if (*(s32 *) &obj->type.unk_0C <= 0 || (s32) obj->script.data > 0) {
        bytes[3] = 0;
        copy_slots[0].obj->vars.snd.sound = 4;
    }
}

/* Sets the byte at 0x2C from the 0x18 word (divided by 6144), clears bytes 0x2D, 0x2E and 0x2F, and
   when the 0x18 word is not positive or the 0x1C link word is positive, sets the sound state of copy slot 1's object. */
void obj_sound_volume_update(Object *obj) {
    u8 *bytes = (u8 *) obj->rot_angles;

    bytes[1] = 0;
    bytes[2] = 0;
    bytes[0] = ((0x1000 - *(s32 *) &obj->type.unk_0C / 6144) * 0xFF) >> 0xC;
    if (*(s32 *) &obj->type.unk_0C <= 0 || (s32) obj->script.data > 0) {
        bytes[3] = 0;
        copy_slots[1].obj->vars.snd.sound = 4;
    }
}

/* Sets the byte at 0x2C from the 0x18 word (divided by 6144), clears bytes 0x2D, 0x2E and 0x2F, and
   when the 0x18 word is not positive or the 0x1C link word is positive, sets the sound state of copy slot 2's object. */
void sound_volume_phase2(Object *obj) {
    u8 *bytes = (u8 *) obj->rot_angles;

    bytes[1] = 0;
    bytes[2] = 0;
    bytes[0] = ((0x1000 - *(s32 *) &obj->type.unk_0C / 6144) * 0xFF) >> 0xC;
    if (*(s32 *) &obj->type.unk_0C <= 0 || (s32) obj->script.data > 0) {
        bytes[3] = 0;
        copy_slots[2].obj->vars.snd.sound = 4;
    }
}

/* Sets the byte at 0x2C from the 0x18 word (divided by 6144), clears bytes 0x2D, 0x2E and 0x2F, and
   when the 0x18 word is not positive or the 0x1C link word is positive, sets the sound state of copy slot 3's object. */
void sound_volume_ramp(Object *obj) {
    u8 *bytes = (u8 *) obj->rot_angles;

    bytes[1] = 0;
    bytes[2] = 0;
    bytes[0] = ((0x1000 - *(s32 *) &obj->type.unk_0C / 6144) * 0xFF) >> 0xC;
    if (*(s32 *) &obj->type.unk_0C <= 0 || (s32) obj->script.data > 0) {
        bytes[3] = 0;
        copy_slots[3].obj->vars.snd.sound = 4;
    }
}

#if STAGE == 4
extern FxRecordParams fx_rec34_params;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void func_800C7AEC(s32 *pos) {
    fx_rec34_spawn_cb(pos, &fx_rec34_params, 0);
}
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
#endif

#if STAGE == 5
extern FxRecordParams fx_rec34_params;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void func_800C4A8C(s32 *pos) {
    fx_rec34_spawn_cb(pos, &fx_rec34_params, 0);
}
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
#endif

#if STAGE == 10
extern FxRecordParams fx_rec34_params;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void func_800C8824(s32 *pos) {
    fx_rec34_spawn_cb(pos, &fx_rec34_params, 0);
}
extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
#endif

/* Start two records from their templates, spawn the object and play the two sound effects
   (note 0x30, pan 0x7F/0x3F and 0x7F/0xC0). */
void blast_effect_spawn(s32 *pos, s16 *rot, s32 index) {
    fx_spawn_template(pos, &fx_owner_template_a, 0);
    fx_spawn_template(pos, &fx_owner_template_b, 0);
    object_spawn_at(pos, rot, index);
    sound_play(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3F, 0x30);
    sound_play(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x7F, 0xC0, 0x30);
}

#if STAGE == 4
extern FxRecordParams d_8011ACDC;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void func_800C7BAC(s32 *pos) {
    fx_rec34_spawn_cb(pos, &d_8011ACDC, 0);
}
extern RecTemplate obj_fx_template_a;
extern RecTemplate obj_fx_template_b;
#endif

#if STAGE == 5
extern FxRecordParams d_8011ACDC;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void func_800C4B4C(s32 *pos) {
    fx_rec34_spawn_cb(pos, &d_8011ACDC, 0);
}
extern RecTemplate obj_fx_template_a;
extern RecTemplate obj_fx_template_b;
#endif

#if STAGE == 10
extern FxRecordParams d_8011ACDC;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void func_800C88E4(s32 *pos) {
    fx_rec34_spawn_cb(pos, &d_8011ACDC, 0);
}
extern RecTemplate obj_fx_template_a;
extern RecTemplate obj_fx_template_b;
#endif

/* Start two records from their templates, spawn the object and play the two sound effects
   (note 0x30, pan 0x7F/0x3F and 0x7F/0xC0). */
void obj_spawn_with_fx(s32 *pos, s16 *rot, s32 index) {
    fx_spawn_template(pos, &obj_fx_template_a, 0);
    fx_spawn_template(pos, &obj_fx_template_b, 0);
    object_spawn_at(pos, rot, index);
    sound_play(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3F, 0x30);
    sound_play(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x7F, 0xC0, 0x30);
}

void fn_s04_800C7C6C(Object *obj, ObjHandler *handler) {
    s32 colour;
    Vec3 *pos;
    s16 *rot;
    s32 n;
    SparkRec *s;
    SparkList *list;
    u8 *tail;
    s32 level;
    s32 x, y, z;
    u16 roll;
    s32 b, a;

    if (obj->vars.enemy_spawn_copy_obj.unk_24C < 7) {
        pos = scratch_alloc(0x10);
        rot = scratch_alloc(8);
        level = obj->vars.enemy_spawn_copy_obj.unk_248;
        colour = 0x60C0FF;
        pos->x = obj->x >> 12;
        pos->y = obj->y >> 12;
        pos->z = obj->z >> 12;
        rot[0] = obj->pitch;
        rot[1] = obj->yaw;
        roll = obj->roll;
        rot[2] = roll;
        list = &spark_list;
        a = -rot[0];
        b = rot[1];
        x = pos->x;
        y = pos->y;
        z = pos->z;
        n = SPARK_COUNT;
        if (n < 0xFF) {
            s = &list->items[n];
            n++;
            spark_count = n;
            *(s32 *)s->colour = colour;
            tail = spark_list_tail;
            spark_list_tail = &s->next;
            *tail = n;
            s->next = 0;
            s->x = x;
            s->y = y;
            s->z = z;
            s->unk_12 = level;
            s->yaw = b;
            s->pitch = a;
            s->roll = roll;
        }
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
}

extern void blast_seq_update(Object *obj, ObjHandler *handler);
void fn_s04_800C7C6C(Object *obj, ObjHandler *handler);
s32 copy_slot_claim(void);

/* Spawns a copy of the object `src` (its position, angles and speed) with its own handlers, and records it in
 * copy_slots[0].obj under the index copy_slot_claim returns. Returns 1 if one was made. */
s32 enemy_spawn_copy(Object *src, s32 arg1, s32 arg2) {
    Object *obj;
    s32 index;
    s32 made;

    made = 0;
    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
        obj->handlers[0].fn = blast_seq_update;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = fn_s04_800C7C6C;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->x = src->x;
        obj->y = src->y;
        obj->z = src->z;
        obj->width = src->width;
        obj->height = src->height;
        obj->unk_1E8[0] = src->unk_1E8[0];
        obj->yaw = src->yaw;
        obj->pitch = src->pitch;
        obj->roll = src->roll;
        obj->vars.enemy.mode = arg1;
        obj->vars.snd.sound = 1;
        obj->vars.enemy_spawn_copy_obj.unused_250 = 0;
        obj->vars.enemy_spawn_copy_obj.unk_254 = arg2; /* 0x254: the sound_channel words */
        index = copy_slot_claim();
        obj->vars.enemy_spawn_copy_obj.index = index;
        copy_slots[index].obj = obj;
        made = 1;
    }
    return made;
}

void spawn_slots_reset(void) {
    copy_slots_clear();
}
