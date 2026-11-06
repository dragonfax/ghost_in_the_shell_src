/* Shared by s04, s05: obj_spawn_projectile. */

#include "stage.h"

void obj_spawn_projectile(Object *spawner, s32 *pos, u16 *rot, s32 speed) {
    Object *obj;
    u16 roll;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
        obj->handlers[1].fn = projectile_arc_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = projectile_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        roll = rot[2];
        obj->speed = speed;
        obj->vy = 0;
        obj->vars.projectile.done = 0;
        obj->vars.projectile.countdown = 0xF;
        obj->vars.projectile.toggle = 0;
        obj->roll = roll;
        obj_hit_clear(obj->index);
        obj->vars.snd.sound = model_slot_pchr(*(s32 *) spawner->asset) + 0x10;
    }
}
