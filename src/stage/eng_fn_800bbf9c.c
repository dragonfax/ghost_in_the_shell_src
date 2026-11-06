/* Shared by s05, s07: grenade_fuchikoma_spawn (1 function). */

#include "stage.h"

/* Each stage's copy uses its own tables. */
extern ScriptCallEntry script_call_table[];
extern StateEntry rocket_fuchikoma_state_table[];
extern s32 grenade_asset[3];
extern s16 *grenade_type_data[];
extern s16 *grenade_script_pc;
extern s16 grenade_saved_param;
#define GRENADE_TABLE_194 script_call_table
#define GRENADE_TABLE_198 rocket_fuchikoma_state_table
#define GRENADE_ASSET grenade_asset
#define GRENADE_TYPE_DATA grenade_type_data
#define GRENADE_TYPE_WORD grenade_script_pc
#define GRENADE_SAVED_184 grenade_saved_param
extern s16 *grenade_fuchikoma_data[];
void rocket_fuchikoma_phase0(Object *obj);

/* Spawns the grenade fuchikoma from its placement. */
s32 grenade_fuchikoma_spawn(Placement *place) {
    Object *obj;
    s16 **script;
    ObjHandler *h;
    s32 kind;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    *(s16 *)&place->unk_00[2] = 0x708;
    h = obj->handlers;
    obj->handlers[0].fn = (void *)rocket_fuchikoma_phase0;
    obj->handlers[1].fn = obj_splash_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = rocket_fuchikoma_draw;
    obj->callback = (s32)obj_spawn_here;
    obj->call_table = GRENADE_TABLE_194;
    *(volatile u8 *)&h[0].unk_11 = 0;
    *(volatile s16 *)&h[0].state = 0;
    *(volatile u8 *)&h[1].unk_11 = 0;
    *(volatile s16 *)&h[1].state = 0;
    *(volatile u8 *)&h[2].unk_11 = 0;
    *(volatile s16 *)&h[2].state = 0;
    *(volatile u8 *)&h[3].unk_11 = 0;
    *(volatile s16 *)&h[3].state = 0;
    obj->state_table = GRENADE_TABLE_198;
    kind = place->unk_00[5];
    obj->asset = GRENADE_ASSET;
    obj->hit_cooldown_max = 0x30;
    *(volatile s16 *)&obj->unk_1C6 = 0;
    *(volatile s16 *)&obj->kind = kind;
    obj->script.data = GRENADE_TYPE_DATA;
    obj->script.unk_0A = 0;
    obj->script.pc = GRENADE_TYPE_WORD;
    script = grenade_fuchikoma_data;
    script_start((Script *)obj, *script, (s32)script);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 4, 0x1000);
    obj->vars.enemy.sound_channel[1] = -2;
    obj->vars.fn_800BBF9C_obj.unused_250 = 0x6000;
    obj->vars.fn_800BBF9C_obj.unk_25A = 4;
    obj->handlers[1].turn_timer = 0;
    obj->handlers[1].timer = 0;
    obj->unk_226[0] = 0x10;
    obj->vars.enemy.sound_channel[0] = obj->yaw;
    obj->vars.fn_800BBF9C_obj.initial_pitch = obj->pitch;
    obj->vars.fn_800BBF9C_obj.initial_yaw = obj->yaw;
    obj->vars.fn_800BBF9C_obj.initial_roll = obj->roll;
    GRENADE_SAVED_184 = obj->damage;
    return 1;
}
