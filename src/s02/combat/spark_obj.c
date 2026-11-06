/* spark_obj: one of s02's own original source files (scripts/objmap.py); part of src/s02/main.c's unit, included there. */

void obj_sound_clear();
s32 spark_obj_spawn(Object *src, s32 mode) {
    Object *obj;
    s32 x;
    u16 roll;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->vars.spark_obj.unk_254 = src->y;
    x = src->x;
    obj->y = 0x64000;
    obj->x = x;
    obj->z = src->z;
    obj->width = (u16) src->width;
    obj->height = src->height;
    obj->unk_1E8[0] = (u16) src->unk_1E8[0];
    obj->yaw = (u16) src->yaw;
    obj->pitch = (u16) src->pitch;
    roll = src->roll;
    obj->handlers[0].fn = fn_800C4368;
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
    obj->vars.spark_obj.mode = mode;
    obj->vars.spark_obj.unused_24C = 1;
    obj->vars.spark_obj.unused_250 = 0;
    fade_red_obj = (Next800C5620 *) obj;
    return 1;
}

s32 spark_obj_spawn(Object *obj, s32 arg);
void obj_become_spark(Object *obj) {
    spark_obj_spawn(obj, model_slot_pchr(*(s32 *)obj->asset) + 0x150);
    obj_free(obj);
}
