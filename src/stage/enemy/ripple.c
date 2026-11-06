/* ripple: one of the original source files (scripts/objmap.py); s01, s03, s04, s06, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

#if STAGE != 4
void obj_spawn_ripple(Object *obj, s32 base, s32 range) {
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
        ripple_fx_params.w[0] = (base + t / 16) << 12;
        ripple_fx_params.w[1] = 0x20000;
        t /= 32;
        ripple_fx_params.b1 = t;
        ripple_fx_params.b2 = t;
        ripple_fx_params.b3 = t;
        fx_rec34_spawn(pos, &ripple_fx_params);
    }
}
#endif

#if STAGE == 6 || STAGE == 12
extern FxRecordParams fx_send_rec34_params_a, D_801177B0;
extern RecTemplate fx_send_template_a, D_801177E0, D_80118724, D_8011873C;
extern RecTemplate D_801177C8, fx_send_template_b, D_80118724, D_8011873C;
extern FxRecordParams D_80117798, fx_send_rec34_params_b;
#endif

#if STAGE != 3
/* Sends the object's position (in whole units, y lowered by 12, 0x200 and 0x500 for the later steps) to
 * the parameter blocks of the effect. */
void obj_effect_send_pos(Object *obj) {
    s32 pos[3];

    pos[0] = obj->x >> 12;
    pos[1] = (obj->y >> 12) - 0xC;
    pos[2] = obj->z >> 12;
    fx_rec34_spawn(pos, &fx_send_rec34_params_a);
    fx_spawn_template(pos, &fx_send_template_a, 0);
    pos[1] -= 0x200;
    fx_spawn_template(pos, &fx_send_template_b, 0);
    pos[1] -= 0x500;
    fx_rec34_spawn(pos, &fx_send_rec34_params_b);
}
#endif

#if STAGE == 1 || STAGE == 12
/* Passes the object's position to sound_set_pos through a scratch vector. */
s32 sound_set_pos_from_obj(Object *obj, s32 arg) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    sound_set_pos(arg, pos);
    scratch_top -= 0x10;
    return 0;
}
#endif
