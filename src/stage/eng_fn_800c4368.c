/* Shared by s02, s03, s07, s11: fn_800C4368 (1 function). */

#include "stage.h"

/* The two effect spawners it calls are per-stage copies with per-stage names. */
#if STAGE == 2
s32 effect_spawn_at_pos(s32 *pos);
void effect_spawn_plain(s32 *pos);
#define death_blast_spawn effect_spawn_at_pos
#define death_debris_spawn effect_spawn_plain
#elif STAGE == 3
s32 effect_spawn_at_pos(s32 *pos);
void effect_spawn_plain(s32 *pos);
#define death_blast_spawn effect_spawn_at_pos
#define death_debris_spawn effect_spawn_plain
#elif STAGE == 7
s32 effect_spawn_at_pos(s32 *pos);
void fx_rec34_spawn_default(s32 *pos);
#define death_blast_spawn effect_spawn_at_pos
#define death_debris_spawn fx_rec34_spawn_default
#elif STAGE == 11
s32 effect_spawn_at_pos(s32 *pos);
void fx_rec34_spawn_default(s32 *pos);
#define death_blast_spawn effect_spawn_at_pos
#define death_debris_spawn fx_rec34_spawn_default
#endif

/* Death sequence actor: vars.words[1] is the phase, words[2] its timer,
 * words[0] the effect argument. Phase 1 sprays explosions around the body,
 * 2 spawns the big blast, 6 the debris, 7 ends the stage. */
void fn_800C4368(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    s16 rot[3];
    s32 tick, size;
    s32 rx, ry, rz;
    s32 x, y, z;

    switch (obj->vars.words[1]) {
    case 1:
        tick = obj->vars.words[2];
        if (tick & 1) {
            register s32 height asm("$3");

            rx = obj->width;
            ry = (s16)obj->height;
            rz = obj->unk_1E8[0];
            tick = tick / 2;
            rx = rx * (rand_a_next() - 0x800) / 4096;
            ry = ry * (rand_a_next() - 0x800) / 4096;
            rz = rz * (rand_a_next() - 0x800) / 4096;
            x = obj->x >> 12;
            height = (s16)obj->height;
            y = (obj->y >> 12) - height / 2;
            x += rx;
            y += ry;
            z = obj->z >> 12;
            z += rz;
            size = ((tick & 1) == 0) << 1;
            if ((tick & 3) == 0) {
                spawn_effect(x, y, z, (size + 0x7F00) | 0x80000000);
            } else {
                spawn_effect(x, y, z, size | 0x80000000);
            }
        }
        obj->vars.words[2]++;
        if (obj->vars.words[2] >= 0x78) {
            obj->vars.words[1] = 2;
            obj->vars.words[2] = 0;
        }
        break;
    case 2:
        obj->vars.words[2]++;
        if (obj->vars.words[2] >= 0xC) {
            s32 height;

            pos[0] = obj->x >> 12;
            height = (s16)obj->height;
            pos[1] = (obj->y >> 12) - height / 2;
            pos[2] = obj->z >> 12;
            death_blast_spawn(pos);
            obj->vars.words[1] = 3;
            obj->vars.words[2] = 0;
        }
        break;
    case 4:
        obj->vars.words[1] = 5;
        obj->vars.words[2] = 0;
        break;
    case 5:
        obj->vars.words[2]++;
        if (obj->vars.words[2] >= 6) {
            obj->vars.words[1] = 6;
            obj->vars.words[2] = 0;
        }
        break;
    case 6:
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot[0] = obj->pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        death_debris_spawn(pos);
        pos[1] -= (s16)obj->height / 2;
        obj_spawn_with_two_fx(pos, rot, obj->vars.words[0]);
        obj->vars.words[1] = 7;
        break;
    case 7:
        obj->vars.words[2]++;
        if (obj->vars.words[2] >= 0xD2) {
            set_stage_end(2);
            obj->vars.words[1] = 8;
        }
        break;
    }
}
