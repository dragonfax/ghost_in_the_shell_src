/* Shared by s01, s13: boss_death_update (1 function).
 * fade_red_start_at and fx_rec34_spawn_pos are defined in each stage's main.c
 * before this file (s13 maps them to its effect_spawn_at_pos / effect_spawn_plain). */

#include "stage.h"

/* Boss death sequence; vars.words[1] is the phase, vars.words[2] its frame timer.
 * 1: explosions at random points of the body for 120 frames, 2: red fade at the
 * centre, 4-5: pause, 6: spawn the wreck, 7: end the stage after 210 frames. */
void boss_death_update(Object *obj)
{
    s32 pos[4];
    s16 rot[4];
    s32 tick;
    s32 dx, dy, dz;
    s32 kind;
    s32 px, py, pz;

    switch (obj->vars.replacement.state) {
    case 1:
        tick = obj->vars.replacement.timer;
        if (!(tick & 1)) {
            /* (s16)obj->height / 2 written out: the plain form schedules differently */
            register s32 height_hi asm("$2");
            s32 height;

            tick = tick / 2;
            dx = obj->width;
            dy = (s16)obj->height;
            dz = obj->unk_1E8[0];
            dx = dx * (rand_a_next() - 0x800) / 4096;
            dy = dy * (rand_a_next() - 0x800) / 4096;
            dz = dz * (rand_a_next() - 0x800) / 4096;
            px = obj->x >> 12;
            height_hi = obj->height << 16;
            height = height_hi >> 16;
            py = (obj->y >> 12) - ((s32)(height + ((u32)height_hi >> 31)) >> 1);
            px += dx;
            pz = obj->z >> 12;
            py += dy;
            pz += dz;
            kind = !(tick & 1) << 1;
            if (!(tick & 3)) {
                spawn_effect(px, py, pz, (kind + 0x7F00) | 0x80000000);
            } else {
                spawn_effect(px, py, pz, kind | 0x80000000);
            }
        }
        if (++obj->vars.replacement.timer >= 120) {
            obj->vars.replacement.state = 2;
            obj->vars.replacement.timer = 0;
        }
        break;
    case 2:
        if (++obj->vars.replacement.timer >= 12) {
            s32 height_hi, height;

            pos[0] = obj->x >> 12;
            height_hi = obj->height << 16;
            height = height_hi >> 16;
            pos[1] = (obj->y >> 12) - ((s32)(height + ((u32)height_hi >> 31)) >> 1);
            pos[2] = obj->z >> 12;
            fade_red_start_at(pos);
            obj->vars.replacement.state = 3;
            obj->vars.replacement.timer = 0;
        }
        break;
    case 4:
        obj->vars.replacement.state = 5;
        obj->vars.replacement.timer = 0;
        break;
    case 5:
        if (++obj->vars.replacement.timer >= 6) {
            obj->vars.replacement.state = 6;
            obj->vars.replacement.timer = 0;
        }
        break;
    case 6:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot[0] = obj->pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        fx_rec34_spawn_pos(pos);
        pos[1] -= (s16)obj->height / 2;
        obj_spawn_with_two_fx(pos, rot, obj->vars.replacement.unk_248);
        obj->vars.replacement.state = 7;
        break;
    case 7:
        if (++obj->vars.replacement.timer >= 210) {
            set_stage_end(2);
            obj->vars.replacement.state = 8;
        }
        break;
    }
}
