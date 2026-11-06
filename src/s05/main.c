#include "common.h"
#define STAGE 5
#define STAGE_ASM "../asm/s05/nonmatchings/main"
#include "stage.h"
#include "s05_types.h"
#include "sounds.h"

void obj_play_effects(Object *obj);

#include "../stage/sys/svc.c"
#include "sys/svc_part1.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"

/* The stage's model and message files: data tables point to them by address. */
const char file_mbaz_tp0_clt[] = "mbaz_tp0.clt";
const char file_mbaz_ch0_clt[] = "mbaz_ch0.clt";
const char file_mbaz_tp0_xs3[] = "mbaz_tp0.xs3";
const char file_mbaz_ch0_vx1[] = "mbaz_ch0.vx1";
const char file_mbaz_ch0_cb4[] = "mbaz_ch0.cb4";
const char file_horo_tp0_clt[] = "horo_tp0.clt";
const char file_horo_ch0_clt[] = "horo_ch0.clt";
const char file_horo_tp0_xs3[] = "horo_tp0.xs3";
const char file_horo_ch0_vx1[] = "horo_ch0.vx1";
const char file_horo_ch0_cb4[] = "horo_ch0.cb4";
const char file_mth2_tp0_clt[] = "mth2_tp0.clt";
const char file_mth2_ch0_clt[] = "mth2_ch0.clt";
const char file_mth2_tp0_xs3[] = "mth2_tp0.xs3";
const char file_mth2_ch0_vx1[] = "mth2_ch0.vx1";
const char file_mth2_ch0_cb4[] = "mth2_ch0.cb4";
const char file_hou1_tp0_clt[] = "hou1_tp0.clt";
const char file_hou1_ch0_clt[] = "hou1_ch0.clt";
const char file_hou1_tp0_xs3[] = "hou1_tp0.xs3";
const char file_hou1_ch0_vx1[] = "hou1_ch0.vx1";
const char file_hou1_ch0_cb4[] = "hou1_ch0.cb4";
const char file_seaf_tp0_clt[] = "seaf_tp0.clt";
const char file_seaf_ch0_clt[] = "seaf_ch0.clt";
const char file_seaf_tp0_xs3[] = "seaf_tp0.xs3";
const char file_seaf_ch0_vx1[] = "seaf_ch0.vx1";
const char file_seaf_ch0_cb4[] = "seaf_ch0.cb4";

void obj_offset_to_world_shifted(Object *obj, s32 *out);
extern s32 shot_params_b;
#include "../stage/enemy/enemy_ai.c"

#include "../stage/enemy/enemy.c"

#include "../stage/enemy/walker_mech.c"

#include "../stage/enemy/enemy_aim.c"

#include "../stage/eng_fn_800bb148.c"

/* Same code as func_800B7534 (s01). */
void rocket_fuchikoma_phase0(Object *obj) {
    if (obj->health > 0) {
        obj_link_script_run();
    }
}

void obj_yaw_turn(Object *obj) {
    obj->yaw = angle_approach(obj->yaw, obj->vars.h.unk_254, 0x10);
}

#include "../stage/eng_fn_800bb3a0.c"

extern s16 spawn_offset_x_table[], spawn_offset_y_table[], spawn_offset_z_table[];
/* Spawns a randomly offset effect in front of the object: rotates a fixed offset by the object's angles. */
void shot_burst_spawn(Object *obj) {
    s32 *v = scratch_alloc(0x20);
    s16 *rot = scratch_alloc(8);
    s32 *w;
    s32 i;

    rot[0] = -obj->vars.h.unk_248 + 0x100;
    rot[1] = obj->yaw;
    rot[2] = 0;
    v[1] = -0x88;
    v[0] = 0;
    v[2] = -0x2C;
    rotate_xz_twice(rot[1], -obj->pitch, v, v + 1, v + 2);
    w = v + 4;
    i = rand_a_next() * 11 / 4096;
    v[4] = spawn_offset_x_table[i];
    v[5] = spawn_offset_y_table[i] - 0x42;
    v[6] = spawn_offset_z_table[i] + 0x50;
    rotate_xz_twice(rot[1], rot[0], w, w + 1, w + 2);
    v[4] = (obj->x >> 12) + v[0] + v[4];
    v[5] = (obj->y >> 12) + v[1] + v[5];
    v[6] = (obj->z >> 12) + v[2] + v[6];
    sound_play_at_units(SND_SHOT_BURST_FIRE | SND_GROUP(1), 0x60, 0x3C, w);
    shot_spawn_obj(w, (u16 *)rot, 2, (s32)&shot_params);
    scratch_top -= 0x28;
}

void shot_burst_spawn();
/* Handler step: result -2 counts vars.h.unk_248 down and then finishes with state 3 and 0x3C steps left,
 * -1 starts the next state, and every 12th step of a running count calls func_800BB6A4. */
void obj_countdown_step(Object *obj, ObjHandler *handler) {
    s32 result = handler->result;

    switch (result) {
    case -2:
        if (obj->vars.h.unk_248 >= -0xC7) {
            obj->vars.h.unk_248 -= 0x10;
        } else {
            handler->queued_entry = -1;
            handler->result = 0x3C;
            obj->vars.h.unk_258 = 3;
        }
        break;
    case -1:
        obj_request_state(obj, handler, 0, 0);
        break;
    default:
        if ((s16)obj->vars.h.unk_258 > 0 && result % 12 == 0) {
            shot_burst_spawn(obj);
            obj->vars.h.unk_258 = obj->vars.h.unk_258 - 1;
        }
        break;
    }
}

/* Rotates a copy of src by the object's yaw, adds the object's position (whole units), and calls spark_pair_spawn. */
void spark_pair_spawn_at_obj(Object *obj, s32 *src) {
    s32 *out = scratch_alloc(0x10);

    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    rotate_xz_twice(obj->yaw, 0, out, out + 1, out + 2);
    out[0] += obj->x >> 12;
    out[1] = obj->y >> 12;
    out[2] += obj->z >> 12;
    spark_pair_spawn((Vec3 *)out, 0x1800, 0x1000);
    scratch_top -= 0x10;
}

typedef struct SplashEntry {
    s32 id;
    s32 spark_a[4];
    s32 spark_b[4];
} SplashEntry;

/* Each stage's copy reads its own table (s05: splash_table, s07: splash_table). */
extern SplashEntry splash_table[];
#define SPLASH_TABLE splash_table

void obj_splash_update(Object *obj, ObjHandler *handler) {
    s32 wet;
    s32 surface;
    s32 i;
    s32 id;
    SplashEntry *rec;

    if (obj->health > 0) {
        obj_script_step(obj, handler);
        if (get_area() / 3 == 4) {
            surface = (surface_of(obj->ground_id) & 0x300) >> 8;
            wet = surface == 1;
        } else {
            wet = 0;
        }
        id = obj->type.unk_0C;
        rec = SPLASH_TABLE;
        for (i = 0; i < 2; i++, rec++) {
            if (rec->id == id && id != obj->vars.fn_800BBF9C_obj.unk_25A) {
                if (wet == 1) {
                    spark_pair_spawn_at_obj(obj, rec->spark_a);
                    spark_pair_spawn_at_obj(obj, rec->spark_b);
                    sound_play_at(SND_SMALL_SPLASH | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
                    break;
                }
                sound_play_at(SND_FOOTSTEP | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
                break;
            }
        }
        obj->vars.fn_800BBF9C_obj.unk_25A = id;
    }
}

#include "../stage/eng_fn_800bb95c.c"

#include "../stage/eng_fn_800bbf9c.c"

/* Spawns an object of this object's kind (its type plus the index of its asset) at its position in whole
 * units, with its angles (pitch negated), then marks its placement as spawned (byte 4 bits 0-1 = 2). */
s32 obj_spawn_here(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 kind;
    Placement *placement;
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    rot[2] = (u16)obj->roll;
    kind = *(s16 *)&obj->type.unk_0E;
    object_spawn_at(pos, rot, kind + model_slot_pchr(*(s32 *)obj->asset));
    placement_list_pop((ListRecord *)obj->placement);
    placement = obj->placement;
    placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
    return 0;
}

/* Script op (near_radius, far_radius, index): when the player is within far_radius of the object's
 * placement and within near_radius of the object, jump to table entry `index`. */
void script_jump_near_player(Object *obj) {
    s32 near_radius;
    s32 far_radius;
    s32 index;

    near_radius = obj_read_s16(obj);
    far_radius = obj_read_s16(obj);
    index = obj_read_s16(obj);
    if (player_dist_to_obj_point(obj, 1) <= far_radius && player_dist_to_obj_point(obj, 0) <= near_radius) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op: jump to the target given by the operand pair when the object is within radius of a cell corner. */
void script_jump_near(Object *obj) {
    s32 cx;
    s32 cy;
    s32 radius;
    s32 target;
    s16 *cursor;
    s32 dx;
    s32 dy;
    s32 inside;
    s32 px;
    s32 py;
    s32 pz;

    px = obj->x;
    py = obj->y;
    cursor = obj->script.pc;
    pz = obj->z;
    /* shifted in place: a register set twice keeps its load where it is (sched1 moves single-set loads) */
    px >>= 12;
    py >>= 12;
    pz >>= 12;
    obj->script.pc++;
    radius = cursor[0];
    obj->script.pc++;
    target = cursor[1];
    point_to_view_angles(px, py, pz, &cx, &cy);
    dx = cx;
    dy = cy;
    if (dx > 0x800) {
        dx = 0x1000 - dx;
    }
    if (dy > 0x800) {
        dy = 0x1000 - dy;
    }
    inside = dx < radius && dy < radius;
    if (inside) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

/* Reads two halfwords from the script stream and combines them into the speed. */
void script_read_speed_long(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;
    s32 hi;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    hi = pc[1] << 16;
    obj->speed = (lo & 0xFFFF) | hi;
}

/* Same code as func_800BC020 (s01). */
void script_read_long(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    obj->speed_accel = pc[1] << 16;
    obj->speed_accel = (lo & 0xFFFF) | obj->speed_accel;
}

/* Reads the next script halfword (cursor at +0x20). With the flag at +0xF8 set, the cursor jumps to the
 * entry of the type's table (+0x1C) that the halfword selects. */
void script_branch_on_flag(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if (obj->script_flag != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

#include "../stage/eng_fn_800bc098.c"

#include "../stage/enemy/gun_turret.c"

#include "../stage/enemy/enemy_ops.c"

#include "../stage/eng_fn_800bc57c.c"

void obj_fire_projectile(Object *obj);
#include "../stage/eng_fn_800bc5ec.c"

void fighter_jet_update(Object *obj, ObjHandler *handler) {
    Placement *placement;
    s32 x, y, z;
    s32 use_alt;
    s32 in_area;
    u16 timer;

    obj->vz = 0;
    obj->vx = 0;
    obj_script_step(obj, handler);
    obj_lean_into_turn(obj, &obj->vars.words[2], 4, 0x100);

    use_alt = 0;
    placement = obj->placement;
    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    if (placement != NULL) {
        /* placement flag bit 2 selects the other area test */
        in_area = placement->unk_00[4] & 4;
        FAKE_OPAQUE(in_area);
        use_alt = in_area != 0;
    }
    if (use_alt != 0) {
        in_area = cam_range_check_alt(x, y, z, placement) == 0;
    } else {
        in_area = cam_range_check(x, y, z, placement) == 0;
    }

    if (in_area != 0) {
        timer = obj->vars.h.unk_24A;
        obj->vars.h.unk_248 = 1;
        obj->vars.h.unk_24A = timer - 1;
        if ((s16)timer < 0) {
            /* countdown ran out: clear the sound channel's word and free the object */
            *(s16 *)((s32)obj->vars.enemy.sound_channel[0] * 2 + obj->vars.words[4] + 0x24A) = 0;
            obj_free(obj);
        }
    } else {
        obj->vars.h.unk_248 = 0;
        obj->vars.h.unk_24A = 0x12C;
    }
}

static inline void jet_spark_add(SparkList *list, s32 ry, s32 rx, s32 rz, s32 x, s32 y, s32 z, s32 value, s32 colour) {
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
void fighter_jet_draw(Object *obj, ObjHandler *handler) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot;
    SVECTOR *dir;
    s32 value;
    s32 colour;
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    rot = scratch_alloc(8);
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    dir = scratch_alloc(8);
    if (obj->vars.h.unk_248 == 0) {
        if (test_bit(obj->flags, 6)) {
            s32 base = obj->type.unk_0E;

            value = base + model_slot_pchr(*(s32 *)obj->asset);
        } else {
            value = obj_keyframe_value(obj, 0);
        }
        colour = 0;
        if (obj->hit > 0) {
            FAKE_OPAQUE(colour);
            colour = 0x60C0FF;
        }
        jet_spark_add(&spark_list, rot[1], rot[0], rot[2], pos[0], pos[1], pos[2], value, colour);
        pos[0] = obj->x;
        pos[1] = obj->y;
        pos[2] = obj->z;
        dir->vx = obj->width;
        dir->vy = obj->height;
        dir->vz = obj->unk_1E8[0];
        aim_marker_draw(2, dir, (Vec3 *)pos, 0);
        if (obj->hit != 0) {
            obj->hit = -1;
        }
    }
    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 8;
}

void fighter_jet_smoke_update(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 off[3];
    s32 r;
    s32 rand_z;
    s32 x;
    s32 rounded;
    u16 flip;
    u16 timer;
    s32 pitch;

    off[0] = rand_a_next() % 512;
    off[1] = rand_a_next() % 256;
    /* off[2] = rand % 512, split so x loads where the original has it */
    rand_z = rand_a_next();
    rounded = rand_z / 512 * 512;
    x = obj->x;
    off[2] = rand_z - rounded;
    obj->unk_17A = 0;
    pos[0] = x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = -obj->pitch;
    rot[0] = pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    obj->next_state = 2;
    rot[1] = obj->yaw;
    vec3_rotate(rot[1], rot[0], rot[2], &off[0], &off[1], &off[2]);

    if ((s16) obj->vars.fighter_jet_spawn_from_parent_obj.life_timer == 0x168) {
        spawn_effect(pos[0] + off[0], pos[1] - off[1], pos[2] + off[2], 0x80007F01);
        spawn_effect(pos[0] - off[0], pos[1] - off[1], pos[2] - off[2], 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0x80007F00);
        spawn_effect(pos[0], pos[1] - 0x300, pos[2], 0x80000000);
        spawn_effect(pos[0], pos[1] - 0x380, pos[2], 0x80007F02);
    }

    r = rand_a_next();
    if (r == (r / 5) * 5) {
        flip = obj->vars.fighter_jet_spawn_from_parent_obj.effect_side ^ 1;
        obj->vars.fighter_jet_spawn_from_parent_obj.effect_side = flip;
        if (flip == 0) {
            spawn_effect(pos[0] + off[0], pos[1] - off[1], pos[2] + off[2], 0x80007F00);
        } else {
            spawn_effect(pos[0] - off[0], pos[1] - off[1], pos[2] - off[2], 0x80000000);
        }
    }

    if (obj->unk_1B7 == 1 || (timer = obj->vars.fighter_jet_spawn_from_parent_obj.life_timer, obj->vars.fighter_jet_spawn_from_parent_obj.life_timer = timer - 1, (s16) timer < 0)) {
        obj_play_effects(obj);
        placement_list_pop((ListRecord *) obj->placement);
        obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
        /* clear this child's slot in the spawner's table */
        ((s16 *) &((Object *) obj->vars.fighter_jet_spawn_from_parent_obj.parent)->vars.h.unk_24A)[obj->vars.enemy.sound_channel[0]] = 0;
        obj_free(obj);
    }
}

#include "../stage/eng_fn_800bad60_fighter_jet_phase0.c"

void fighter_jet_update(Object *obj, ObjHandler *handler);
void fighter_jet_draw(Object *obj, ObjHandler *handler);
void fighter_jet_smoke_update(Object *obj);
extern s16 fighter_jet_script[];
extern s16 *fighter_jet_data[];
extern u8 fighter_jet_asset[];
extern ScriptCallEntry obj_call_table[];
extern StateEntry obj_state_table[];
extern s16 *fighter_jet_type_data[];
extern s16 *fighter_jet_script_start;
s32 fighter_jet_spawn_from_parent(Placement *place, Object *parent) {
    Object *obj;
    s32 sound;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) fighter_jet_phase0;
        obj->handlers[1].fn = fighter_jet_update;
        obj->handlers[2].fn = obj_state_run;
        obj->handlers[3].fn = fighter_jet_draw;
        obj->callback = (s32) &fighter_jet_smoke_update;
        obj->destructor = fighter_jet_stop_sound;
        obj->asset = &fighter_jet_asset;
        obj->unk_1C6 = -0xC0;
        obj->call_table = obj_call_table;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->kind = 1;
        obj->state_table = obj_state_table;
        script_start((Script *) obj, fighter_jet_script, (s32) &fighter_jet_data);
        obj->script.data = &fighter_jet_type_data;
        obj->script.unk_0A = 0;
        obj->script.pc = fighter_jet_script_start;
        obj_init_from_place(obj, place, 0x37);
        obj->speed = 0x23;
        obj_set_part_bounds(obj, 0, 0x800);
        obj->vars.fighter_jet_spawn_from_parent_obj.unused_24A = 0x12C;
        obj->vars.fighter_jet_spawn_from_parent_obj.life_timer = 0x168;
        obj->vars.fighter_jet_spawn_from_parent_obj.unused_248 = 1;
        obj->vars.fighter_jet_spawn_from_parent_obj.effect_side = 0;
        obj->vars.fighter_jet_spawn_from_parent_obj.unused_250 = 0;
        obj->vars.fighter_jet_spawn_from_parent_obj.unused_252 = 0x1E;
        obj->yaw = (s16) (u16) obj->yaw;
        obj->vars.enemy.sound_channel[0] = (s16) parent->vars.h.unk_248;
        obj->vars.enemy.sound_channel[1] = rand_a_next() % 2;
        obj->vars.fighter_jet_spawn_from_parent_obj.parent = (s32) parent;
        sound = sound_start(SND_JET_ENGINE_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
        sound_attach(sound, &obj->x, NULL);
        sound_set_flag_bit2(sound, 1);
        obj->vars.fighter_jet_spawn_from_parent_obj.sound_handle = sound;
        return 1;
    }
    return 0;
}

/* Steps a lobbed projectile: gravity on vy, moves along yaw; on a world or object hit spawns impact effects and frees
 * itself, leaving smoke every other frame while smoke_time runs. */
void projectile_arc_update(Object *obj) {
    s32 dz = 0;
    s32 dx = 0;
    s32 smoke_model;
    VECTOR *from;
    VECTOR *to;
    VECTOR *hit;
    s16 target;
    s16 angle;
    s32 pitch;

    smoke_model = get_model_slot_base() + 0x20;
    from = scratch_alloc(0x30);
    obj->vy += 0x800;
    fly_move(obj->yaw, obj->speed, &dz, &dx);
    from->vx = obj->x >> 12;
    to = from + 1;
    from->vy = obj->y >> 12;
    hit = from + 2;
    from->vz = obj->z >> 12;
    to->vx = (obj->x + dx) >> 12;
    to->vy = (obj->y + obj->vy) >> 12;
    to->vz = (obj->z + dz) >> 12;
    if (cam_range_check_alt(from->vx, from->vy, from->vz) == 0) {
        obj->vars.arc.done = 1;
    } else if (obj_hit_damage(obj->index) > 0) {
        spawn_effect(from->vx, from->vy, from->vz, 0x80000000);
        obj->vars.arc.done = 1;
    } else if (trace_world(8, 0xC, from, to, hit)) {
        spawn_effect(hit->vx, hit->vy - 300, hit->vz, 0);
        spawn_effect(hit->vx, hit->vy - 400, hit->vz, 1);
        obj->vars.arc.done = 1;
    } else {
        set_collide_mode(1);
        if (trace_objects(from, to, 0xC, hit, &target)) {
            angle = atan2(hit->vz - from->vz, hit->vx - from->vx);
            hit_target_masked(target, 2, angle, 0x1A);
            spawn_effect(hit->vx, hit->vy, hit->vz, 0);
            spawn_effect(hit->vx, hit->vy, hit->vz, 1);
            obj->vars.arc.done = 1;
        }
        set_collide_mode(0);
        pitch = obj->pitch;
        if (pitch < 0x400) {
            obj->pitch = pitch + 8;
        }
        obj->z += dz;
        obj->x += dx;
        obj->y += obj->vy;
        if (obj->speed > 0) {
            obj->speed--;
        }
    }
    if (obj->vars.arc.done == 1) {
        obj_free(obj);
    } else {
        from->vy += 50;
        if ((s16)obj->vars.arc.smoke_time-- > 0) {
            if ((obj->vars.arc.smoke_toggle ^= 1) == 0) {
                effect_spawn_at((Vec3 *)from, smoke_model, 0xA, 8);
            }
        }
    }
    scratch_top -= 0x30;
}

void projectile_draw(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 *rot;
    s32 n;
    SparkRec *s;
    SparkList *list;
    u8 *tail;
    s32 level = obj->vars.snd.sound;
    s32 pitch;
    s32 x, y, z;
    u16 roll;
    s32 a, b;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    rot = scratch_alloc(8);
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    list = &spark_list;
    a = rot[0];
    b = rot[1];
    x = pos->x;
    y = pos->y;
    z = pos->z;
    n = SPARK_COUNT;
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
        s->unk_12 = level;
        s->yaw = b;
        s->pitch = a;
        s->roll = roll;
    }
    scratch_top -= 0x10;
    scratch_top -= 8;
}

void projectile_arc_update(Object *obj);
#include "../stage/eng_fn_800bd208.c"

void obj_fire_projectile(Object *obj) {
    s32 *pos;
    s16 *rot;
    s32 dx, dy, dz;
    s32 pitch, roll;

    pos = scratch_alloc(0x10);
    pos[0] = obj->x >> 12;
    rot = scratch_alloc(8);
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    dx = 0;
    dy = 100;
    dz = 0;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    vec3_rotate(rot[1], rot[0], roll, &dx, &dy, &dz);
    pos[0] += dx;
    pos[1] += dy;
    pos[2] += dz;
    sound_play_at_units(SND_S05_PROJECTILE_FIRE | SND_GROUP(1), 0x60, 0x3C, pos);
    obj_spawn_projectile(obj, pos, (u16 *)rot, obj->speed);
    scratch_top -= 0x10;
    scratch_top -= 8;
    {   /* 8 bytes of unused locals in the original frame */
        s32 unused[2];
    }
}
#include "enemy/fighter_jet_spawner.c"

#include "../stage/camera/stage_camera.c"
#include "world/clamp.c"

extern s32 alert_flag, D_8011FEB0, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, turn_flag, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, mission_enemies_left, cam_timer;
extern GridEntry *flagged_grid_cells[];
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 msg_text_id, cam_side_blend, D_8011FED0, msg_fade, cam_spin_step;
extern s32 msg_text_id, D_8011FECC, cam_ramp_b, msg_fade, cam_spin_step;
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 cam_angle_acc, D_8011FEE4, D_8011FEE8, D_8011FEA8;
extern s16 msg_pos_x, msg_pos_y;
extern s16 msg_pos_x, msg_pos_y;
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 D_8011FEDC, d_8011FEE4, D_8011FEE8, D_8011FEA8;
extern s32 D_8011FEDC, D_8011FEE4, D_8011FEE8, grid_flagged_count;
extern s32 D_8011FEDC, D_8011FEE4, timer_warn_shown, D_8011FEA8;
void cam_update_phase2();
void hud_frame_draw();
#include "../stage/mission/mission_state.c"
#include "boss/camouflaged_target.c"
#include "../stage/object/copy_slots.c"

#include "../stage/lib/libc/printf.c"
#include "../stage/lib/libgte/square_root0.c"
#include "../stage/sys/lz.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

#include "../stage/lib/libgte/vector_normal.c"
#include "../stage/math/gte_helper.c"
#include "../stage/lib/libgte/matrix_normal.c"

#include "../stage/sys/pad_input.c"

#include "../stage/sys/vsync.c"

#include "../stage/gfx/model_slots.c"

#include "../stage/sys/arena.c"
#include "../stage/gfx/frame.c"

#include "../stage/gfx/cam_view_reset.c"
#include "../stage/gfx/view.c"

#include "../stage/gfx/shadow.c"

#include "../stage/gfx/pchr_pose.c"
#include "../stage/gfx/cylinder.c"
#include "../stage/gfx/floor_grid.c"
#include "../stage/gfx/lens_flare.c"

#include "../stage/gfx/scratch.c"
#include "../stage/gfx/track.c"
#include "../stage/world/world_query.c"

#include "../stage/core/cells.c"
#include "../stage/core/stage_main.c"
#include "../stage/core/stage_loop.c"
#include "../stage/debug/debug_menu.c"
#include "../stage/debug/debug_print.c"
#include "../stage/core/part.c"
#include "../stage/tables/name_table_base.c"

#include "../stage/gfx/interp.c"
#include "../stage/gfx/interp38b.c"
#include "../stage/tables/name_load.c"
#include "../stage/core/stage_data.c"

#include "../stage/core/pause_reset.c"
#include "../stage/core/pause.c"

#include "../stage/tables/stage_info.c"
#include "../stage/tables/name_table.c"
#include "../stage/math/transform_point.c"
#include "../stage/player/player_state.c"
#include "../stage/player/player.c"

#include "../stage/object/pair_table.c"
#include "../stage/object/grid_hooks.c"
#include "../stage/tables/scan_items.c"
#include "../stage/object/object_system.c"
#include "../stage/combat/effects.c"
#include "../stage/mission/mission_status.c"
#include "../stage/mission/mission_clock.c"
#include "../stage/mission/shield.c"
#include "../stage/mission/mission_counts.c"
#include "../stage/mission/mission_rank.c"
#include "../stage/mission/stage_round.c"
#include "../stage/hud/hud.c"
#include "../stage/hud/msg_queue.c"
#include "../stage/hud/msg_line.c"
#include "../stage/hud/ui_items.c"
#include "../stage/hud/ui_draw.c"
#include "../stage/hud/meter.c"
#include "../stage/camera/rec_table.c"
#include "../stage/camera/camera.c"
#include "../stage/combat/object_slots.c"
#include "../stage/combat/spark_count.c"
#include "../stage/combat/sparks.c"
#include "../stage/combat/grenades.c"
#include "../stage/combat/pickups.c"
#include "../stage/camera/lock_mode.c"
#include "../stage/camera/lock_on.c"
#include "../stage/combat/shots_fx.c"
#include "../stage/sound/sound.c"
#include "../stage/lib/libgte/gte_misc.c"
#include "../stage/combat/particles.c"
#include "../stage/world/wall_query.c"
#include "../stage/player/player_flags.c"
#include "../stage/camera/camera_follow.c"
#include "../stage/object/mover.c"
