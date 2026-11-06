#include "common.h"
#define STAGE 11
#include "stage.h"
#include "s11_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"
#include "sys/svc_part1.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"

/* The stage's model and message files: data tables point to them by address. */
const char file_tetr_tp0_clt[] = "tetr_tp0.clt";
const char file_tetr_ch0_clt[] = "tetr_ch0.clt";
const char file_tetr_tp0_xs3[] = "tetr_tp0.xs3";
const char file_tetr_ch0_vx1[] = "tetr_ch0.vx1";
const char file_tetr_ch0_cb4[] = "tetr_ch0.cb4";
const char file_stk3_tp0_clt[] = "stk3_tp0.clt";
const char file_stk3_ch0_clt[] = "stk3_ch0.clt";
const char file_stk3_tp0_xs3[] = "stk3_tp0.xs3";
const char file_stk3_ch0_vx1[] = "stk3_ch0.vx1";
const char file_stk3_ch0_cb4[] = "stk3_ch0.cb4";

#include "../stage/enemy/pyramid_mine.c"

#include "enemy/ceiling_bomber.c"

#include "../stage/enemy/enemy_aim.c"

#include "../stage/enemy/fuchikoma_b.c"

#include "../stage/enemy/script_radius_jumps.c"

#include "../stage/enemy/script_reads.c"

#include "../stage/enemy/gun_turret_2.c"

/* 0x254, 0x258 and 0x278 are words[3], words[4] and words[12] of the vars union */
void obj_mount_pos(Object *obj, s32 *out) {
    s32 delta_x;
    s32 delta_y;
    s32 delta_z;

    out[1] = -0xC2;
    out[0] = 0;
    out[2] = -0x48;
    rotate_xz_twice(obj->yaw + obj->vars.flier.floor_slope, obj->pitch, &out[0], &out[1], &out[2]);
    delta_x = 0x12;
    delta_y = 0;
    delta_z = 0xAF;
    rotate_xz_twice(obj->vars.words[3] + obj->vars.flier.floor_slope, obj->vars.flier.pitch & 0xFFF, &delta_x, &delta_y, &delta_z);
    out[0] = (obj->x >> 12) + delta_x + out[0];
    out[1] = (obj->y >> 12) + delta_y + out[1];
    out[2] = (obj->z >> 12) + delta_z + out[2];
}

/* Runs two helpers, then turns the object's two angles at 0x258 and 0x254 toward the two angles
   of rot by 0x10 per call. */
void obj_turn_to_angles(Object *obj, s32 *dir, s16 *rot) {
    obj_mount_pos(obj, dir);
    dir_to_angles_clamped((Vec3 *)dir, (SVECTOR *)rot);
    obj->vars.flier.pitch = angle_approach(obj->vars.flier.pitch, rot[0], 0x10);
    obj->vars.words[3] = angle_approach(obj->vars.words[3], rot[1], 0x10);
}

#include "../stage/eng_fn_800ba06c.c"

void obj_turn_to_angles(Object *obj, s32 *dir, s16 *rot);
void enemy_fire_fx(Object *obj) {
    s32 pos[3];
    u16 rot[3];
    s32 handle;
    s32 rnd;
    u16 base;

    obj_turn_to_angles(obj, pos, (s16 *)rot);
    rot[1] = (obj->vars.words[3] + rand_a_next() % 24) - 0xC;
    rnd = rand_a_next();
    base = rot[0];
    base -= 0xC;
    rot[0] = base + rnd % 24;
    if (*((u8 *) obj + 0x27C) == 0) {
        handle = sound_start(SND_HEAVY_MACHINE_GUN_FIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        sound_attach(handle, &obj->x, 0);
        *((u8 *) obj + 0x27C) = handle;
    }
    shot_spawn_obj(pos, rot, 1, ((s32) obj->damage << 16) | 1);
}

void burst_enemy_shoot(Object *obj) {
    s32 origin[4];
    s32 pos[3];
    s16 spread[3];
    u8 *slot;
    s32 handle;
    s32 rnd;
    u16 base;

    obj_turn_to_angles(obj, origin, spread);
    spread[1] = obj->vars.words[3] + rand_a_next() % 24 - 0xC;
    rnd = rand_a_next();
    base = spread[0] - 0xC;
    spread[0] = base + (rnd % 24);
    pos[0] = obj->vx >> 12;
    pos[1] = obj->vy >> 12;
    pos[2] = obj->vz >> 12;
    slot = (u8 *) &obj->vars.enemy.shot_timer;
    if (*slot == 0) {
        handle = sound_start(SND_HEAVY_MACHINE_GUN_FIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        sound_attach(handle, &obj->x, 0);
        *slot = handle;
    }
    shot_spawn_target(origin, (u16 *)spread, pos, 1, (obj->damage << 16) | 1);
}

#define STOP_OBJ_SOUND(obj)                                  \
    do {                                                     \
        if (((u8 *)(obj))[0x27C] != 0) {                     \
            sound_stop(((u8 *)(obj))[0x27C]);                \
            ((u8 *)(obj))[0x27C] = 0;                        \
        }                                                    \
    } while (0)
void burst_enemy_shoot(Object *obj);
/* Runs the object's angle turn, then steps its timers (0x249, 0x24A, 0x24B) by handler->result. */
void enemy_burst_update(Object *obj, ObjHandler *handler) {
    Vec3 dir;
    s16 table[2];
    u8 timer;

    obj_turn_to_angles(obj, (s32 *)&dir, table);
    switch (handler->result) {
    case -2:
        handler->result = 1;
        ((u8 *)obj)[0x24A] = 0;
        ((u8 *)obj)[0x249] = (u8)(rand_a_next() % 8 + 4);
        ((u8 *)obj)[0x24B] = (u8)(rand_a_next() % 48 + 0x18);
        return;
    case -1:
        timer = ((u8 *)obj)[0x24B];
        ((u8 *)obj)[0x24B] = (u8)(timer + 0xFF);
        if (timer != 0) {
            STOP_OBJ_SOUND(obj);
            return;
        }
        handler->result = -2;
        STOP_OBJ_SOUND(obj);
        return;
    default:
        if (*(s32 *)&((u8 *)obj)[0x268] >= 0x801) {
            STOP_OBJ_SOUND(obj);
            return;
        }
        if (((u8 *)obj)[0x249] == 0) {
            handler->result = -1;
            return;
        }
        if (((u8 *)obj)[0x24A]++ >= 4) {
            ((u8 *)obj)[0x24A] = 0;
            ((u8 *)obj)[0x249]--;
            burst_enemy_shoot(obj);
        }
        handler->result = 1;
        return;
    }
}

#include "../stage/eng_fn_800ba504.c"

extern s32 proximity_asset[3];
extern StateEntry placed_actor_states[1];
extern s16 placed_actor_script[];
extern s16 *placed_actor_script_value[];
void obj_proximity_phase0(Object *obj);
void obj_script_update(Object *obj, ObjHandler *handler);
void placed_actor_draw(Object *obj, ObjHandler *handler);
s32 obj_effect_update(Object *obj);
#include "../stage/object/placed_actor.c"
#include "boss/dreadnought.c"

#include "../stage/eng_fn_800c5620.c"

extern RecTemplate fade_red_fx_template;
void fade_red_update();
/* Starts a record from the template D_8011E054 with fade_red_update as its callback; pos is passed through. */
s32 effect_spawn_at_pos(s32 *pos) {
    return fx_spawn_template(pos, &fade_red_fx_template, fade_red_update);
}

void obj_noop_hook(void) {
}

extern FxRecordParams fx_rec34_params;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void fx_rec34_spawn_default(s32 *pos) {
    fx_rec34_spawn_cb(pos, &fx_rec34_params, 0);
}

extern RecTemplate D_801177C8, D_801177E0, fx_owner_template_a, D_8011873C;
extern RecTemplate D_801177C8, D_801177E0, D_80118724, fx_owner_template_b;
#include "../stage/eng_fn_800c571c.c"

#include "../stage/eng_fn_800c4368.c"

void obj_noop_update(void) {
}

#include "../stage/eng_fn_800c5ab8.c"
#include "gfx/spark_fx.c"
#include "combat/bullets.c"

#include "../stage/camera/cam_zone.c"
#include "world/end_zone.c"

#include "../stage/sys/lz.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

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
#include "../stage/combat/particles.c"
#include "../stage/world/wall_query.c"
#include "../stage/player/player_flags.c"
#include "../stage/camera/camera_follow.c"
#include "../stage/object/mover.c"
