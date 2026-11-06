/* placed_actor: one of the original source files (scripts/objmap.py); s02, s11, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

s32 placed_actor_spawn(Placement *place) {
    Object *obj = obj_new();

    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    obj->handlers[0].fn = obj_proximity_phase0;
    obj->handlers[1].fn = obj_script_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = placed_actor_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) obj_effect_update;
    obj->kind = place->unk_00[5];
    obj->asset = proximity_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->state_table = placed_actor_states;
    script_start((Script *) obj, placed_actor_script, (s32) &placed_actor_script_value);
    obj_init_from_place(obj, place, 0x76);
    obj->speed = 0;
    obj_set_part_bounds(obj, 1, 0xAAA);
    obj_hit_set_unk06(obj->index, 0);
    obj->vars.placed_actor.unk_248 = 0;
    obj->vars.placed_actor.unk_24A = 0;
    obj->vars.placed_actor.unk_24C = 0;
    obj->vars.placed_actor.flash = 0;
    return 1;
}

#if STAGE == 11
void obj_explode_damage(Object *obj);
#endif

void obj_proximity_phase0(Object *obj) {
    s32 *player;
    s32 pos[3];

    obj->vars.placed_actor.unk_248 = obj->vars.placed_actor.unk_248 + 1;
    *(u8 *)&obj->unk_1B7 = 0;
    obj->vars.placed_actor.unk_24A = obj->vars.placed_actor.unk_24A + obj->vars.placed_actor.unk_24C;
    if (obj->vars.placed_actor.unk_24C == 0) {
        player = player_position();
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        if (isqrt(length_sq(player[0] - pos[0], player[1] - pos[1], player[2] - pos[2])) < 0x191) {
            obj->vars.placed_actor.unk_24C = 1;
            sound_play_at(SND_DOUBLE_BEEP | SND_GROUP(1), 0x40, 0x3C, &obj->x);
        }
    }
    if ((s16) obj->vars.placed_actor.unk_24A >= 8) {
        obj_explode_damage(obj);
    }
}

void obj_script_update(Object *obj, ObjHandler *handler) {
    obj_script_step(obj, handler);
}

static inline void spark_add_list_a0(s32 colour, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value) {
    register SparkList *list asm("$4") = &spark_list;
    s32 n = spark_count;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        FAKE_OPAQUE(list);
        tail = list->tail[0];
        list->tail[0] = &s->next;
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
/* Draw handler: a spark with the object's model at its position and rotation, tinted red while
 * vars.h.unk_24E is on (toggled each frame while unk_24C is set) and blue while hit; then
 * aim_marker_draw with the position and 6/5 of the size at unk_1E4. A hit flag set is turned to -1. */
void placed_actor_draw(Object *obj, ObjHandler *handler) {
    Vec3 *pos;
    SVECTOR *rot;
    register Vec3 *spark_pos asm("$18");
    register SVECTOR *spark_rot asm("$17");
    s32 model, colour, pitch, flash;

    pos = scratch_alloc(0x10);
    rot = scratch_alloc(0x10);

    spark_pos = pos;
    FAKE_OPAQUE(spark_pos);
    spark_pos->x = obj->x >> 12;
    spark_pos->y = obj->y >> 12;
    spark_pos->z = obj->z >> 12;
    spark_rot = rot;
    if (obj->vars.placed_actor.unk_24C != 0) {
        obj->vars.placed_actor.flash ^= 1;
    }
    FAKE_OPAQUE(spark_rot);
    pitch = obj->pitch;
    spark_rot->vx = -pitch;
    spark_rot->vy = obj->yaw;
    spark_rot->vz = obj->roll;
    model = model_slot_pchr(*(s32 *)obj->asset) + 1;
    colour = 0;
    flash = obj->vars.placed_actor.flash;
    if (flash != 0) {
        FAKE_OPAQUE(colour);
        colour = 0xFFC0C0;
    }
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    }
    spark_add_list_a0(colour, spark_pos->x, spark_pos->y, spark_pos->z, spark_rot->vy, spark_rot->vx, spark_rot->vz, model);
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    rot[1].vx = obj->width * 6 / 5;
    rot[1].vy = (s16)obj->height * 6 / 5;
    rot[1].vz = obj->unk_1E8[0] * 6 / 5;
    aim_marker_draw(2, &rot[1], pos, rot);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x20;
}

/* Same code as obj_spawn_effect_near (s02). */
void obj_spawn_scatter_effect(Object *obj, s32 type) {
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

#if STAGE == 11
void obj_spawn_scatter_effect(Object *obj, s32 mode);
#endif

s32 obj_effect_update(Object *obj) {
    obj_spawn_scatter_effect(obj, 0);
    return 0;
}

/* Same code as sea_mine_explode (s02). */
void obj_explode_damage(Object *obj) {
    s32 *player;
    s32 pos[3];
    s32 dist;
    s32 damage;

    obj_spawn_scatter_effect(obj, 1);
    obj_spawn_scatter_effect(obj, 0);
    obj_spawn_scatter_effect(obj, 0);
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
