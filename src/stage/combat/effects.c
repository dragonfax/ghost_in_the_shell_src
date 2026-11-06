/* effects: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void obj_snapshot_save(Object *obj, ObjSnapshot *snap) {
    s32 flags;
    s32 pos_x;
    s32 pos_y;
    s32 pos_z;
    s32 vel_x;
    s32 vel_y;
    s32 vel_z;
    u8 moving;

    flags = snap->flags;
    pos_x = obj->x;
    pos_y = obj->y;
    pos_z = obj->z;
    vel_x = obj->vx;
    vel_y = obj->vy;
    vel_z = obj->vz;
    snap->pos[0] = pos_x;
    snap->pos[1] = pos_y;
    snap->pos[2] = pos_z;
    flags &= ~1;
    moving = obj->unk_1B7;
    snap->vel[0] = vel_x;
    snap->vel[1] = vel_y;
    snap->vel[2] = vel_z;
    if (moving != 0) {
        flags |= 1;
    }
    snap->flags = flags;
}

/* Copies the collision result in snap back into obj. The three temporaries
   are reused for every group (needed to match). */
void obj_snapshot_restore(Object *obj, ObjSnapshot *snap)
{
    s32 c, b, a;

    a = snap->unk_20[0];
    b = snap->unk_20[1];
    c = snap->unk_20[2];
    obj->x = a;
    obj->y = b;
    obj->z = c;
    a = snap->unk_6C;
    b = snap->unk_5C;
    c = *(s32 *)snap->unk_50;
    obj->unk_1A8 = a;
    obj->unk_1A4 = b;
    *(s32 *)obj->move_delta = c;
    b = snap->flags;
    a = snap->unk_50[2];
    obj->unk_1B7 = b & 1;
    obj->blocked_x = (b & 0x30) != 0;
    obj->blocked_z = (b & 0xC) != 0;
    obj->move_delta[2] = a;
    obj->blocked_y = (b & 3) != 0;
}

void fn_800FB528(void) {

}

void fade_pool_init(void) {
    FadeRec *rec = fade_records;
    s32 i = 0;

    fades_head = 0xFF;
    fades_free = 0;
    do {
        rec->next = i + 1;
        i++;
        rec++;
    } while (i < 0x7F);
    rec->next = 0xFF;
}

void effect_set_base(s32 value) {
    effect_base = value;
}

/* Copies the position to a scratch Vec3 as 16.16 fixed point and passes it to sound_set_pos. */
s32 effect_sound_update(EffectSoundSource *src, s32 arg) {
    Vec3 *vec = scratch_alloc(0x10);

    vec->x = src->pos.vx << 16;
    vec->y = src->pos.vy << 16;
    vec->z = src->pos.vz << 16;
    sound_set_pos(arg, vec);
    scratch_top -= 0x10;
    return 0;
}

void spawn_effect(s32 x, s32 y, s32 z, s32 type) {
    EffectRec *rec;
    FadeRec *tmp;
    s32 idx;
    s32 vol;
    s32 sound;
    s32 v;
    s16 px, py, pz;

    idx = fades_free;
    if (idx == 0xFF) {
        rec = NULL;
    } else {
        tmp = &fade_records[idx];
        fades_free = tmp->next;
        rec = (EffectRec *)tmp;
        rec->next = fades_head;
        fades_head = idx;
    }
    vol = 0x7F;
    if (type < 0) {
        vol = (type >> 8) & 0x7F;
    }
    type &= 0xFF;
    if (rec != NULL) {
        switch (type) {
        case 0:
            rec->unk_0A = effect_base + 0x80;
            rec->unk_02 = 0xF;
            rec->unk_01 = 6;
            if (vol != 0) {
                sound = sound_start(SND_MEDIUM_EXPLOSION | SND_GROUP(1), vol, 0, 0);
                v = sound_volume_of(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x1000) * vol / 0x80;
                sound_set_volume(sound, v);
                sound_attach(sound, rec, (void (*)())effect_sound_update);
            }
            break;
        case 1:
            rec->unk_0A = effect_base + 0x90;
            rec->unk_02 = 0xA;
            rec->unk_01 = 8;
            if (vol != 0) {
                sound = sound_start(SND_MEDIUM_EXPLOSION | SND_GROUP(1), vol, 0, 0);
                v = sound_volume_of(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x1000) * vol / 0x80;
                sound_set_volume(sound, v);
                sound_attach(sound, rec, (void (*)())effect_sound_update);
            }
            break;
        case 2:
            rec->unk_0A = effect_base + 0xA0;
            rec->unk_02 = 0xB;
            rec->unk_01 = 8;
            if (vol != 0) {
                sound = sound_start(SND_SMALL_EXPLOSION | SND_GROUP(1), vol, 0, 0);
                v = sound_volume_of(SND_SMALL_EXPLOSION | SND_GROUP(1), 0x1000) * vol / 0x80;
                sound_set_volume(sound, v);
                sound_attach(sound, rec, (void (*)())effect_sound_update);
            }
            break;
        }
        px = (u32)x >> 4;
        py = (u32)y >> 4;
        pz = (u32)z >> 4;
        rec->unk_03 = 0;
        rec->x = px;
        rec->y = py;
        rec->z = pz;
    }
}

void effect_spawn_at(Vec3 *pos, s32 a1, s32 a2, s32 a3) {
    FadeRecFull *r = fade_alloc();
    u32 x, y, z;

    if (r != NULL) {
        r->base_level = a1;
        r->level_scale = a2;
        r->level_step = a3;
        r->level = 0;
        x = pos->x;
        y = pos->y;
        z = pos->z;
        r->pos[0] = x >> 4;
        r->pos[1] = y >> 4;
        r->pos[2] = z >> 4;
    }
}

/* Steps every fade on fades_head (unk_03 += unk_01); a fade that passes 255 goes back on fades_free.
 * `kept` and `next_idx` are second names for rec and next: the original keeps each in two registers
 * (FINDINGS "Copies cse deletes"). */
void fades_step(void) {
    u8 *link;
    s32 idx;
    FadeRecFull *rec;
    FadeRecFull *kept;
    u8 next;
    s32 next_idx;
    s32 level;

    link = &fades_head;
    idx = *link;
    while (idx != 0xFF) {
        rec = &((FadeRecFull *)fade_records)[idx];
        kept = rec;
        level = rec->level;
        level += rec->level_step;
        next = rec->next;
        next_idx = next;
        if (level >= 0x100) {
            *link = next;
            rec->next = fades_free;
            fades_free = idx;
        } else {
            kept->level = level;
            link = &kept->next;
        }
        idx = next_idx;
    }
}

void fade_spawn_sparks(void) {
    FadeRecFull *r;
    FadeRecFull *cur;
    SparkList *list;
    SparkRec *s;
    u8 *tail;
    s32 i, n, x, y, z, level;
    s32 colour = 0;

    i = fades_head;
    if (i != 0xFF) {
        do {
            r = &((FadeRecFull *)fade_records)[i];
            cur = r;
            level = (u16)r->base_level + (r->level_scale * r->level) / 256;
            list = &spark_list;
            x = r->pos[0];
            y = r->pos[1];
            z = r->pos[2];
            x <<= 4;
            y <<= 4;
            z <<= 4;
            n = spark_count;
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
                s->unk_12 = level;
                s->yaw = 0;
                s->pitch = 0;
                s->roll = 0;
            }
            i = cur->next;
        } while (i != 0xFF);
    }
}

void stage_ready_set(s32 value) {
    stage_ready_flag = value;
}

s32 stage_ready_get(void) {
    return stage_ready_flag;
}

ResourceRoot *get_rec_root(void) {
    return &rec_root;
}
