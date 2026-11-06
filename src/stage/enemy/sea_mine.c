/* sea_mine: one of the original source files (scripts/objmap.py); s02, s04. */

#include "stage.h"

s32 sea_mine_spawn(Placement *place) {
    Object *obj;
    u8 flags;
    s32 y;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
    obj->handlers[0].fn = sea_mine_trigger;
    obj->handlers[1].fn = sea_mine_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = sea_mine_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) sea_mine_frame_callback;
    flags = place->unk_00[5];
    obj->asset = sea_mine_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = 0;
    obj->state_table = d_80116F10;
    obj->kind = flags;
    script_start((Script *) obj, (s16 *) sea_mine_script, (s32) sea_mine_script_arg);
    obj_init_from_place(obj, place, 0x174);
    obj->speed = 0;
    obj_set_part_bounds(obj, 1, 0x2000);
    y = obj->y;
    obj->vars.sea_mine.frame_counter = 0;
    obj->vars.sea_mine.trigger_timer = 0;
    obj->vars.sea_mine.fuse_time = 0x10;
    obj->vars.sea_mine.triggered = 0;
    obj->vars.sea_mine.unused_258 = 0;
    if (y < 0) {
        y += 0xFFF;
    }
    obj->vars.sea_mine.start_y = y >> 12;
    obj->vars.sea_mine.anim_index = 0;
    obj->vars.sea_mine.anim_timer = 0;
    obj->vars.sea_mine.anim_frame = 0;
    obj->vars.sea_mine.unk_25A = (get_area() / 3) == 3;
    obj->vars.sea_mine.unk_25C = *(u16 *) &place->unk_1A;
    return 1;
}

void sea_mine_explode(Object *obj);
/* Per-frame update: counts vars.h.unk_248 up each call. While vars.h.unk_256 is set it
 * counts unk_24A up to unk_24C (sea_mine_explode runs at the threshold). Otherwise it checks
 * the distance from the player to self; within 400 units it sets unk_256 and calls
 * sound_play_at at self's position. */
void sea_mine_trigger(Object *self, ObjHandler *handler) {
    s32 *player;
    Vec3 pos;
    s32 dist;
    u16 timer;

    self->unk_1B7 = 0;
    self->vars.sea_mine.frame_counter++;
    if (self->vars.sea_mine.triggered != 0) {
        timer = self->vars.sea_mine.trigger_timer + 1;
        self->vars.sea_mine.trigger_timer = timer;
        if ((s16) timer >= self->vars.sea_mine.fuse_time) {
            ((void (*)(void))sea_mine_explode)(); /* the original passes no arguments */
        }
        if (self->vars.sea_mine.triggered == 0) {
            goto check_player;
        }
    } else {
check_player:
        player = player_position();
        pos.x = self->x >> 12;
        pos.y = self->y >> 12;
        pos.z = self->z >> 12;
        dist = isqrt(length_sq(player[0] - pos.x, player[1] - pos.y, player[2] - pos.z));
        if (dist < 0x191) {
            if (get_area() / 3 == 3) {
                self->vars.sea_mine.fuse_time = 0;
            }
            self->vars.sea_mine.triggered = 1;
            sound_play_at(SND_DOUBLE_BEEP | SND_GROUP(1), 0x40, 0x3C, &self->x);
        }
    }
}

/* The stage's {frame, delay} animation table (frame < 0 ends it). */
extern AnimFrame sea_mine_anim_frames[];
#define ANIM_TABLE sea_mine_anim_frames

/* Steps the animation: when the delay runs out, takes the next table entry (wrapping at a negative frame). */
void sea_mine_update(Object *obj, ObjHandler *h) {
    obj->vars.sea_mine.anim_timer--;
    if (obj->vars.sea_mine.anim_timer <= 0) {
        if (ANIM_TABLE[(obj->vars.sea_mine.anim_index)].frame < 0) {
            obj->vars.sea_mine.anim_index = 0;
        }
        obj->vars.sea_mine.anim_frame = ANIM_TABLE[(obj->vars.sea_mine.anim_index)].frame;
        obj->vars.sea_mine.anim_timer = ANIM_TABLE[(obj->vars.sea_mine.anim_index)].delay;
        obj->vars.sea_mine.anim_index++;
    }
    obj_script_step(obj, h);
}

static inline void sea_mine_spark_list_add(SparkList *list, s32 *pos, s32 value, s32 colour) {
    s32 n = SPARK_COUNT;
    s32 x = pos[0], y = pos[1], z = pos[2];
    SparkRec *s;
    SparkList *l;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        l = list;
        FAKE_OPAQUE(l);
        tail = l->tail[0];
        l->tail[0] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
}
static inline void pos_whole(s32 *p, Object *obj) {
    p[0] = obj->x >> 12;
    p[1] = obj->y >> 12;
    p[2] = obj->z >> 12;
}
/* Adds the object's glow spark (and a second one when unk_25C is set). */
void sea_mine_draw(Object *obj, ObjHandler *handler) {
    GlowSparkVars *v = (GlowSparkVars *)obj;
    s32 *pos = scratch_alloc(16);
    s32 *pos_copy;
    s16 *rot;
    register s16 *rot_copy asm("$3");
    register s32 colour asm("$17");
    s32 model;
    s32 sinv;
    s32 pitch;
    SparkList *list;

    rot = scratch_alloc(16);
    rot_copy = rot;
    pos_copy = pos;
    FAKE_OPAQUE(pos_copy);
    pos_whole(pos_copy, obj);
    if (v->blink_enabled != 0) {
        v->red_color ^= 1;
    }
    FAKE_OPAQUE(rot_copy);
    pitch = -obj->pitch;
    rot_copy[0] = pitch;
    rot_copy[1] = obj->yaw;
    rot_copy[2] = obj->roll;
    colour = 0;
    if (v->red_color != 0) {
        FAKE_OPAQUE(colour);
        colour = 0xFFC0C0;
    }
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    }
    model = model_slot_pchr(*(s32 *)obj->asset) + 1;
    if (v->unk_25A == 0) {
        model += 3;
    }
    sinv = *(s16 *)((u8 *)rcossin_tbl + ((v->size_phase << 6) & 0x3FC0));
    model = pchr_blend(model, model + 1, ABS(sinv), 0);
    list = &spark_list;
    sea_mine_spark_list_add(list, pos_copy, model, colour);
    if (v->second_spark_enabled != 0) {
        model = model_slot_pchr(*(s32 *)obj->asset) + 8 + v->second_spark_model_offset;
        spark_add(pos[0], v->second_spark_y, pos[2], rot[1] - 0x400, 0, 0, model, 0);
    }
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 32;
}

void obj_spawn_effect_near(Object *obj, s32 type) {
    s32 pos[3];
    s32 r;
    s32 base;
    s32 base_z;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    r = rand_a_next();
    base = pos[0] - 0x40;
    pos[0] = base + r % 0x80;
    r = rand_a_next();
    base = pos[1] - 0x40;
    pos[1] = base + r % 0x80;
    r = rand_a_next();
    base_z = pos[2] - 0x40;
    pos[2] = base_z + r % 0x80;
    spawn_effect(pos[0], pos[1], pos[2], type);
}

s32 sea_mine_frame_callback(Object *obj) {
    obj_spawn_effect_near(obj, 0);
    return 0;
}

void sea_mine_explode(Object *obj) {
    s32 *player;
    s32 pos[3];
    s32 dist;
    s32 damage;

    obj_spawn_effect_near(obj, 1);
    obj_spawn_effect_near(obj, 0);
    obj_spawn_effect_near(obj, 0);
    particle_spawn_burst(obj->x >> 12, obj->y >> 12, obj->z >> 12, 0);
    player = player_position();
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    dist = isqrt(length_sq(player[0] - pos[0], player[1] - pos[1], player[2] - pos[2]));
    dist = MAX(MIN(dist, 0x400), 0);
    damage = obj->damage * (0x400 - dist) / 1024;
    hit_target_masked(0, 1, 0, damage);
    obj_free(obj);
}
