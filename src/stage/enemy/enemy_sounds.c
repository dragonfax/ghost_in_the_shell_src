/* enemy_sounds: one of the original source files (scripts/objmap.py); s03, s07. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Stops the two sound effects an object may have playing (their handles are bytes at 0x262 and 0x263). */
void enemy_sounds_stop(Object *obj) {
    if (obj->vars.enemy.unk_260[3] != 0) {
        sound_stop(obj->vars.enemy.unk_260[3]);
        obj->vars.enemy.unk_260[3] = 0;
    }
    if (obj->vars.enemy.unk_260[2] != 0) {
        sound_stop(obj->vars.enemy.unk_260[2]);
        obj->vars.enemy.unk_260[2] = 0;
    }
}

extern FxRecordParams ground_shadow_params;
void obj_ground_shadow_spawn(Object *obj, s32 base, s32 range) {
    s32 pos[3];
    s32 dy;
    s32 t;

    pos[0] = obj->x >> 12;
    pos[1] = 0;
    pos[2] = obj->z >> 12;
    dy = obj->y >> 12;
    if (dy >= 0) {
        t = dy;
    } else {
        t = -dy;
    }
    range = ABS(range);
    if (t < range) {
        t = range - t;
        t = (t << 12) / range;
        ground_shadow_params.w[0] = (base + t / 16) << 12;
        ground_shadow_params.w[1] = 0xC000;
        t /= 32;
        ground_shadow_params.b1 = t;
        ground_shadow_params.b2 = t;
        ground_shadow_params.b3 = t;
        fx_rec34_spawn(pos, &ground_shadow_params);
    }
}

extern FxRecordParams fx_rec34_params_a;
extern FxRecordParams fx_rec34_params_b;

/* Passes the object's position (whole units, y lowered by 12 for the first call and 0x200 for
   the second) to fx_rec34_spawn with two parameter blocks. */
void obj_play_pos_sounds(Object *obj) {
    s32 pos[3];

    pos[0] = obj->x >> 12;
    pos[1] = (obj->y >> 12) - 0xC;
    pos[2] = obj->z >> 12;
    fx_rec34_spawn(pos, &fx_rec34_params_a);
    pos[1] -= 0x200;
    fx_rec34_spawn(pos, &fx_rec34_params_b);
}

/* Distance between two positions (the result is discarded). */
s32 vec3_distance(Vec3 *a, Vec3 *b) {
    return SquareRoot0(length_sq(a->x - b->x, a->y - b->y, a->z - b->z));
}

/* Distance from the player to the object's placement position, in whole units (pos_distance). */
s32 player_dist_to_placement(Object *obj) {
    void *target = player_position();
    Placement *placement = obj->placement;
    Vec3 *pos = scratch_alloc(0x10);
    s32 dist;

    pos->x = placement->x >> 12;
    pos->y = placement->y >> 12;
    pos->z = placement->z >> 12;
    dist = vec3_distance(target, pos);
    scratch_top -= 0x10;
    return dist;
}
