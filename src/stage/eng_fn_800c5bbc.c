/* Shared by s01, s03, s07, s08, s13: obj_spawn_replacement (1 function); not yet decompiled. */

#include "stage.h"

/* Spawns an object copied from src's position, angles and roll; installs its handlers and sets it as fade_red_obj. */
s32 obj_spawn_replacement(Object *src, s32 arg1) {
    Object *obj;
    s16 roll;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->x = src->x;
    obj->y = src->y;
    obj->z = src->z;
    obj->width = src->width;
    obj->height = src->height;
    obj->unk_1E8[0] = src->unk_1E8[0];
    obj->yaw = src->yaw;
    obj->pitch = src->pitch;
    roll = src->roll;
#if STAGE == 3 || STAGE == 7
    obj->handlers[0].fn = fn_800C4368;
#else
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) boss_death_update;
#endif
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) obj_noop_update;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) spark_record_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->roll = roll;
    obj_sound_clear(obj);
    obj->vars.replacement.unk_248 = arg1;
    obj->vars.replacement.state = 1;
    obj->vars.replacement.timer = 0;
    fade_red_obj = (Next800C5620 *) obj;
    return 1;
}
