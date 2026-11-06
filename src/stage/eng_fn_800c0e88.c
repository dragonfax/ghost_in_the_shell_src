/* Shared by s06, s07, s09: model_store_pchr..trace_spawn_fan (5 functions). */

#include "stage.h"

/* Stores model_slot_pchr of D_8011CBF4 in D_8012594C. */
void model_store_pchr(void) {
    model_pchr_saved = model_slot_pchr(tank2_asset[0]);
}

void obj_sound_stop_both(Object *obj) {
    obj_sound_held_stop(obj);
    obj_sound2_stop(obj);
}

/* Same code as obj_set_part_bounds (s01). */
void fn_800C0EE8(Object *obj, s32 part, s32 part_arg) {
    u16 ext[3];
    s32 unused[2];
    u16 depth;
    s32 span;
    s32 y;
    s16 y_copy;
    s16 span_copy;

    model_part_extents(part + ((s32 *)obj->asset)[1], part_arg, ext);
    obj->unk_190 = part_arg;
    obj->width = ext[0];
    obj->height = ext[1];
    obj->unk_1E8[0] = depth = ext[2];
    y = (s16)obj->height;
    span = (s16)depth;
    y_copy = y;
    if (span < obj->width) {
        span = obj->width;
    }
    span_copy = span;
    obj->extents[0] = span_copy;
    obj->extents[1] = y_copy;
    obj->extents[2] = span_copy;
    obj->bound_radius = isqrt(length_sq(span, y, span));
}

extern s16 *tank_2_data[];
extern s32 tank2_asset[3];

/* The stage's tank data: per-variant words, model tables. */
extern s16 *tank_variant_words[] asm("tank2_variant_words");
extern ScriptCallEntry tank_table_194[] asm("d_8011CF34");
extern StateEntry tank_table_198[] asm("d_8011CF9C");
extern s16 *tank_link_data[] asm("tank2_link_data");

void tank_draw(Object *obj, ObjHandler *handler);
s32 tank_sink_step(Object *obj);
void tank_update(Object *obj, ObjHandler *handler);
void fn_800C0EE8(Object *obj, s32 a, s32 b);

/* Spawns a tank from its placement: variant (0..2) from the high byte at 0x1A picks the setup and model data. */
s32 tank_spawn(Placement *place) {
    Object *obj;
    Object *tank;
    s32 variant;
    s32 flags;
    s16 **script;
    s32 place_byte5;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    tank = obj;
    list_insert_after((Node *)get_obj_list_actors(), &obj->node);
    variant = *(u16 *)&place->unk_1A >> 8;
    variant = NOT_NEGATIVE(variant < 3 ? variant : 2);
    *(s16 *)&obj->vars.tank.unk_284 = variant;
    ((u8 *)&obj->vars.tank.unk_284)[2] = 0; /* obj_sound2_start's handle */
    ((u8 *)&obj->vars.tank.unk_284)[3] = 0; /* obj_sound_attach_start's handle */
    switch (variant) {
    case 0:
        flags = 0x26;
        obj->speed = 0;
        place->unk_02 = 1800;
        break;
    case 1:
        obj->speed = 0;
        place->unk_02 = -1;
    case 2:
        flags = 0x26;
        tank->speed = place->range;
        tank->vars.words[13] = place->unk_1E << 12;
        place->unk_02 = -1;
        rec_reset((PartSlot *)&tank->vars);
        obj_sound2_start(tank);
        break;
    }
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *))tank2_phase0;
    obj->handlers[1].fn = tank_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = tank_draw;
    obj->callback = (s32)tank_sink_step;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->destructor = (void (*)(Object *))obj_sound_stop_both;
    place_byte5 = place->unk_04[1];
    obj->asset = tank2_asset;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = tank_table_194;
    obj->state_table = tank_table_198;
    script = tank_2_data;
    obj->unk_1C6 = 0;
    obj->kind = place_byte5;
    obj->script.pc = tank_variant_words[variant];
    obj->script.data = tank_link_data;
    obj->script.unk_0A = 0;
    script_start((Script *)obj, *script, (s32)script);
    obj_init_from_place(obj, place, flags);
    fn_800C0EE8(obj, 0, 0x1000);
    tank->vars.h.unk_250 = obj->pitch;
    tank->vars.h.unk_252 = obj->yaw;
    tank->vars.enemy.sound_channel[0] = obj->roll;
    tank->vars.part.unk_282 = -2;
    obj_pick_random_target(tank);
    tank->vars.words[8] = tank->x;
    tank->vars.words[9] = tank->y;
    tank->vars.words[10] = tank->z;
    obj->handlers[1].turn_timer = 0;
    obj->handlers[1].timer = 0;
    obj->unk_226[0] = 0x10;
    return 1;
}

/* Fires eight traces fanned vertically around the given rotation. */
void trace_spawn_fan(Vec3 *pos, u16 *src) {
    SVECTOR *rot = scratch_alloc(8);
    s32 i;
    s32 dy;

    i = 0;
    dy = -0x200;
    do {
        s32 pitch;

        i++;
        pitch = (s16) src[1];
        rot->vx = src[0];
        rot->vy = pitch + dy;
        dy += 0x80;
        rot->vz = src[2];
        shot_spawn_trace(pos, rot, 1);
    } while (i < 9);
    scratch_top -= 8;
}
