/* Shared by s01, s02, s03, s07, s11, s13: obj_spawn_with_two_fx. */

#include "stage.h"

/* Sets up an object with two effect entries (fx_spawn_template) and spawns it at pos with arg,
 * then plays two sound effects (sound_play). */
void obj_spawn_with_two_fx(void *owner, void *pos, s32 arg) {
    fx_spawn_template(owner, &fx_owner_template_a, 0);
    fx_spawn_template(owner, &fx_owner_template_b, 0);
    object_spawn_at(owner, pos, arg);
    sound_play(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x7F, 0xC0, 0x30);
    sound_play(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3F, 0x30);
}
