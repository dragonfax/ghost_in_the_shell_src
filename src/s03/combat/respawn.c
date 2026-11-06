/* respawn: one of s03's own original source files (scripts/objmap.py); part of src/s03/main.c's unit, included there. */

s32 obj_spawn_replacement(Object *src, s32 arg1);
void obj_free_and_respawn(Object *obj) {
    s32 type_0E;

    obj_free(obj);
    type_0E = (s16)obj->type.unk_0E;
    obj_spawn_replacement(obj, type_0E + model_slot_pchr(*(s32 *)obj->asset));
}
