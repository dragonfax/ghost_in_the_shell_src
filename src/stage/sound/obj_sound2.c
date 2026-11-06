/* obj_sound2: one of the original source files (scripts/objmap.py); s07, s08. */

#include "stage.h"

#if STAGE == 7
/* Same as func_800B76AC for the second handle slot: starts sound 0xB4B0B4B3 once
 * and attaches sound_follow_obj, keeping the handle at vars.snd2.sound[0]. */
void obj_snd2_loop_start(Object *obj) {
    s32 handle;

    if (obj->vars.snd2.sound[0] == 0) {
        handle = sound_start(SND_PAIR(SND_VREEEE | SND_HELD | SND_GROUP(1), SND_STATIONARY_LASER_LOOP | SND_HELD | SND_GROUP(1)), 0x60, 0, 0);
        obj->vars.snd2.sound[0] = handle;
        sound_attach(handle, obj, (void (*)())sound_follow_obj);
    }
}
#elif STAGE == 8
/* Starts sound 0xD0E8D0E9 (volume 0x20) once and attaches sound_follow_obj,
 * keeping the handle at vars.snd2.sound[0]. */
void obj_snd2_loop_start(Object *obj) {
    s32 handle;

    if (obj->vars.snd2.sound[0] == 0) {
        handle = sound_start(0xD0E8D0E9, 0x20, 0, 0);
        obj->vars.snd2.sound[0] = handle;
        sound_attach(handle, obj, (void (*)())sound_follow_obj);
    }
}
#else
INCLUDE_ASM(STAGE_ASM, obj_snd2_loop_start);
#endif

/* Stops the sound handle at 0x268 if one is playing. */
void obj_snd2_stop(Object *obj) {
    if (obj->vars.words[8] != 0) {
        sound_stop(obj->vars.words[8]);
        obj->vars.words[8] = 0;
    }
}
