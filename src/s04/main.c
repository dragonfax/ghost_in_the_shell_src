#include "common.h"
#define STAGE 4
#define STAGE_ASM "../asm/s04/nonmatchings/main"
#include "stage.h"
#include "s04_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"
#include "enemy/script_reads.c"

#include "../stage/enemy/flier.c"
#include "enemy/laser_barrier_boat.c"

#include "../stage/enemy/enemy_aim.c"
#include "enemy/jetski.c"

#include "../stage/object/obj_script.c"
#include "enemy/heavy_mobile_suit.c"

#include "../stage/enemy/enemy_ops.c"

#include "../stage/eng_fn_800bc57c.c"

void obj_fire_projectile(Object *obj);
#include "../stage/eng_fn_800bc5ec.c"

void fighter_jet_update(Object *obj, ObjHandler *handler) {
    Placement *placement;
    s32 use_alt_test;
    s32 placement_flags;
    s32 clear;
    s32 whole_x;
    s32 whole_y;
    s32 whole_z;
    u16 timer;

    obj->vz = 0;
    obj->vx = 0;
    obj_script_step(obj, handler);
    obj_lean_into_turn(obj, &obj->vars.enemy.unk_250, 4, 0x100);
    use_alt_test = 0;
    whole_x = obj->x >> 12;
    whole_y = obj->y >> 12;
    whole_z = obj->z >> 12;
    placement = obj->placement;
    if (placement != NULL) {
        placement_flags = placement->unk_00[4] & 4;
        FAKE_OPAQUE(placement_flags);
        use_alt_test = placement_flags != 0;
    }
    if (use_alt_test != 0) {
        clear = cam_range_check_alt(whole_x, whole_y, whole_z, placement) == 0;
    } else {
        clear = cam_range_check(whole_x, whole_y, whole_z, placement) == 0;
    }
    if (clear != 0) {
        timer = obj->vars.h.unk_24A;
        obj->vars.h.unk_248 = 1;
        obj->vars.h.unk_24A = timer - 1;
        if ((s16) timer < 0) {
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
    s32 pos[3];
    s16 rot[3];
    SVECTOR dir;
    s32 value;
    s32 colour;
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    if (obj->vars.h.unk_248 != 0) {
        return;
    }
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
    dir.vx = obj->width;
    dir.vy = obj->height;
    dir.vz = obj->unk_1E8[0];
    aim_marker_draw(2, &dir, (Vec3 *)pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}
void fighter_jet_burst_update(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 off_x, off_y, off_z;
    u16 yaw;
    s32 pitch;

    off_x = rand_a_next() % 512;
    off_y = rand_a_next() % 256;
    off_z = rand_a_next() % 512;
    obj->unk_17A = 0;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    obj->next_state = 2;
    yaw = obj->yaw;
    rot[1] = yaw;
    vec3_rotate((s16)yaw, rot[0], rot[2], &off_x, &off_y, &off_z);
    if (obj->vars.fighter_jet.timer == 0x168) {
        spawn_effect(pos[0] + off_x, pos[1] - off_y, pos[2] + off_z, 0x80007F01);
        spawn_effect(pos[0] - off_x, pos[1] - off_y, pos[2] - off_z, 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0x80007F00);
        spawn_effect(pos[0], pos[1] - 0x300, pos[2], 0x80000000);
        spawn_effect(pos[0], pos[1] - 0x380, pos[2], 0x80007F02);
    }
    if (rand_a_next() % 5 == 0) {
        obj->vars.fighter_jet.toggle ^= 1;
        if (obj->vars.fighter_jet.toggle == 0) {
            spawn_effect(pos[0] + off_x, pos[1] - off_y, pos[2] + off_z, 0x80007F00);
        } else {
            spawn_effect(pos[0] - off_x, pos[1] - off_y, pos[2] - off_z, 0x80000000);
        }
    }
    if (obj->unk_1B7 == 1 || obj->vars.fighter_jet.timer-- < 0) {
        obj_effect_send_pos(obj);
        placement_list_pop((ListRecord *)obj->placement);
        obj->placement->unk_00[4] = (obj->placement->unk_00[4] & 0xFC) | 2;
        obj_free(obj);
    }
}

/* Stops the sound handle at 0x258. */
void obj_sound_stop_258(Object *obj) {
    sound_stop(obj->vars.fighter_jet.sound);
}

void fighter_jet_update(Object *obj, ObjHandler *handler);
void fighter_jet_draw(Object *obj, ObjHandler *handler);
void fighter_jet_burst_update(Object *obj);
void obj_sound_stop_258(Object *obj);
extern s16 *fighter_jet_data[];
extern char D_80119924[];
extern s16 fighter_jet_script[];
extern s16 *fighter_jet_type_data[];
extern ScriptCallEntry obj_call_table[];
extern StateEntry obj_state_table[];
extern s16 *fighter_jet_script_start;
/* Spawns a fighter jet object from a placement; returns 1 on success, 0 if no object slot. */
s32 fighter_jet_spawn(Placement *placement) {
    Object *obj;
    s32 sound;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }

    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) fighter_jet_phase0;
    obj->handlers[1].fn = fighter_jet_update;
    obj->handlers[2].fn = obj_state_run;
    obj->handlers[3].fn = fighter_jet_draw;
    obj->callback = (s32) &fighter_jet_burst_update;
    obj->destructor = obj_sound_stop_258;
    obj->asset = &D_80119924;
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
    script_start((Script *) obj, fighter_jet_script, (s32) fighter_jet_data);
    obj->script.data = &fighter_jet_type_data;
    obj->script.unk_0A = 0;
    obj->script.pc = fighter_jet_script_start;
    obj_init_from_place(obj, placement, 0x135);
    obj->speed = 0x23;
    obj_set_part_bounds(obj, 0, 0x800);
    obj->vars.fighter_jet.unused_24A = 0x12C;
    obj->vars.fighter_jet.timer = 0x168;
    obj->vars.fighter_jet.unused_248 = 1;
    obj->vars.fighter_jet.toggle = 0;
    obj->vars.fighter_jet.unused_250 = 0;
    obj->vars.fighter_jet.unused_252 = 0x1E;
    obj->yaw = (s16) (u16) obj->yaw;
    obj->vars.enemy.sound_channel[0] = rand_a_next() % 2;
    sound = sound_start(SND_FIGHTER_JET_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
    sound_attach(sound, &obj->x, NULL);
    sound_set_flag_bit2(sound, 1);
    obj->vars.fighter_jet.sound = sound;
    return 1;
}

void projectile_arc_update(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    Vec3 next;
    Vec3 hit;
    s32 fx_x;
    s32 fx_y;
    s32 fx_z;
    s32 fx_type;
    s32 step_z; /* fly_move's dx output, added to z */
    s32 step_x; /* fly_move's dz output, added to x */
    s16 target;
    s32 pitch;
    s32 effect_slot;
    s32 countdown;
    s32 toggle;

    step_z = 0;
    step_x = 0;
    effect_slot = get_model_slot_base() + 0x20;
    obj->vy += 0x800;
    fly_move(obj->yaw, obj->speed, &step_z, &step_x);
    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    next.x = (obj->x + step_x) >> 12;
    next.y = (obj->y + obj->vy) >> 12;
    next.z = (obj->z + step_z) >> 12;
    if (cam_range_check_alt(pos.x, pos.y, pos.z) != 0) {
        if (obj_hit_damage(obj->index) > 0) {
            fx_x = pos.x;
            fx_y = pos.y;
            fx_z = pos.z;
            fx_type = 0x80000000;
            goto hit_effect;
        }
        if (trace_world(8, 0xC, &pos, &next, &hit) == 0) {
            goto movement;
        }
        spawn_effect(hit.x, hit.y - 0x12C, hit.z, 0);
        fx_x = hit.x;
        fx_y = hit.y;
        fx_z = hit.z;
        fx_type = 1;
        fx_y -= 0x190;
    hit_effect:
        spawn_effect(fx_x, fx_y, fx_z, fx_type);
    }
    obj->vars.projectile.done = 1;
    goto check;

movement:
    set_collide_mode(1);
    if (trace_objects(&pos, &next, 0xC, &hit, &target) != 0) {
        hit_target_masked(target, 2, atan2(hit.z - pos.z, hit.x - pos.x), 0x1A);
        spawn_effect(hit.x, hit.y, hit.z, 0);
        spawn_effect(hit.x, hit.y, hit.z, 1);
        obj->vars.projectile.done = 1;
    }
    set_collide_mode(0);
    pitch = obj->pitch;
    if (pitch < 0x400) {
        obj->pitch = pitch + 8;
    }
    obj->z += step_z;
    obj->x += step_x;
    obj->y += obj->vy;
    if (obj->speed > 0) {
        obj->speed -= 1;
    }

check:
    if (obj->vars.projectile.done == 1) {
        obj_free(obj);
        return;
    }
    pos.y += 0x32;
    countdown = obj->vars.projectile.countdown;
    obj->vars.projectile.countdown = countdown - 1;
    if ((s16)countdown > 0) {
        toggle = obj->vars.projectile.toggle ^ 1;
        obj->vars.projectile.toggle = toggle;
        if (toggle == 0) {
            effect_spawn_at(&pos, effect_slot, 0xA, 8);
        }
    }
}

/* Adds a spark record at the object's position (whole units) with its angles (pitch negated) and vars word 1. */
void projectile_draw(Object *obj, ObjHandler *handler) {
    VECTOR pos;
    SVECTOR rot;
    s32 value = obj->vars.projectile.sound;
    s32 x, y, z;
    s16 yaw, roll;
    s32 pitch, raw_pitch;
    s32 n;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    pos.vx = x = obj->x >> 12;
    pos.vy = y = obj->y >> 12;
    pos.vz = z = obj->z >> 12;
    list = &spark_list;
    n = spark_count;
    raw_pitch = obj->pitch;
    rot.vx = -raw_pitch;
    pitch = rot.vx;
    rot.vy = yaw = obj->yaw;
    rot.vz = roll = obj->roll;
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
        s->unk_12 = value;
        s->yaw = yaw;
        s->pitch = pitch;
        s->roll = roll;
    }
}

void projectile_arc_update(Object *obj, ObjHandler *handler);
void projectile_draw(Object *obj, ObjHandler *handler);
#include "../stage/eng_fn_800bd208.c"

void obj_fire_projectile(Object *obj) {
    s32 base[3];
    s16 rot[3];
    s32 pos[3];
    s32 dir[3];
    s32 unused[4];
    s32 pitch;
    s32 yaw;
    s32 roll;

    base[0] = obj->x >> 12;
    base[1] = obj->y >> 12;
    base[2] = obj->z >> 12;
    dir[0] = 0;
    pitch = -obj->pitch;
    dir[1] = 100;
    dir[2] = 0;
    rot[0] = pitch;
    yaw = obj->yaw;
    rot[1] = yaw;
    roll = obj->roll;
    rot[2] = roll;
    vec3_rotate(yaw, (s16) pitch, roll, &dir[0], &dir[1], &dir[2]);
    pos[0] = dir[0] + base[0];
    pos[1] = dir[1] + base[1];
    pos[2] = dir[2] + base[2];
    sound_play_at_units(SND_S04_PROJECTILE_FIRE | SND_GROUP(1), 0x60, 0x3C, pos);
    obj_spawn_projectile(obj, pos, (u16 *) rot, obj->speed);
}

extern FxRecordParams fx_send_rec34_params_a, D_801177B0;
extern RecTemplate fx_send_template_a, D_801177E0, D_80118724, D_8011873C;
extern RecTemplate D_801177C8, fx_send_template_b, D_80118724, D_8011873C;
extern FxRecordParams D_80117798, fx_send_rec34_params_b;
#include "../stage/enemy/ripple.c"

extern u8 sea_mine_asset[];
extern StateEntry d_80116F10[];
extern u8 sea_mine_script[];
extern s16 *sea_mine_script_arg[];
extern void sea_mine_trigger();
extern void sea_mine_update();
void sea_mine_draw(Object *obj, ObjHandler *handler);
s32 sea_mine_frame_callback(Object *obj);
#include "../stage/enemy/sea_mine.c"

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
#include "core/stage.c"
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

#include "../stage/gfx/cam_view_reset.c"
#include "../stage/gfx/view.c"

#include "../stage/sys/arena.c"
#include "../stage/gfx/frame.c"

#include "../stage/gfx/shadow.c"

#include "../stage/gfx/model_slots.c"

#include "../stage/gfx/pchr_pose.c"
#include "../stage/gfx/cylinder.c"
#include "../stage/gfx/floor_grid.c"
#include "../stage/gfx/lens_flare.c"

#include "../stage/gfx/scratch.c"
#include "../stage/gfx/track.c"
#include "../stage/world/world_query.c"

#include "../stage/core/pause_reset.c"
#include "../stage/core/pause.c"

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
