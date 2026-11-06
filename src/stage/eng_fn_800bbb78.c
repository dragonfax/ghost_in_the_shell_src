/* Shared by s01, s03, s10: rocket_fuchikoma_spawn..script_branch_on_flag (7 functions). */

#include "stage.h"

/* Per-stage tables: unk_194, unk_198, asset, unk_19C, the link's data table, its start (read as an array:
 * a struct/array load keeps the stores before it) and a global copy of unk_184. */
extern ScriptCallEntry script_call_table[];
extern StateEntry rocket_fuchikoma_state_table[];
extern u8 rocket_fuchikoma_asset[];
extern SoundVolume rocket_fuchikoma_sounds[];
extern s16 *rocket_fuchikoma_jump_table[];
extern s16 *rocket_fuchikoma_script_pos[];
extern s16 d_80120508;
#define ROCKET_FUCHIKOMA_UNK_194 script_call_table
#define ROCKET_FUCHIKOMA_UNK_198 rocket_fuchikoma_state_table
#define ROCKET_FUCHIKOMA_ASSET rocket_fuchikoma_asset
#define ROCKET_FUCHIKOMA_UNK_19C rocket_fuchikoma_sounds
#define ROCKET_FUCHIKOMA_LINK_DATA rocket_fuchikoma_jump_table
#define ROCKET_FUCHIKOMA_SCRIPT_POS rocket_fuchikoma_script_pos
#define ROCKET_FUCHIKOMA_UNK_184 d_80120508

/* Spawns the rocket fuchikoma from its placement: four handlers, its tables, script and angles. */
s32 rocket_fuchikoma_spawn(Placement *place) {
    Object *obj;
    s16 **slot;
    s32 variant;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    place->unk_02 = 0x708;
    obj->handlers[0].fn = (void *)rocket_fuchikoma_phase0;
    obj->handlers[1].fn = rocket_fuchikoma_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = rocket_fuchikoma_draw;
    obj->callback = (s32)obj_spawn_here;
    obj->call_table = ROCKET_FUCHIKOMA_UNK_194;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->state_table = ROCKET_FUCHIKOMA_UNK_198;
    variant = place->unk_04[1];
    obj->asset = (void *)ROCKET_FUCHIKOMA_ASSET;
    obj->hit_cooldown_max = 0x30;
    obj->sounds = ROCKET_FUCHIKOMA_UNK_19C;
    obj->unk_1C6 = 0;
    obj->kind = variant;
    obj->script.pc = ROCKET_FUCHIKOMA_SCRIPT_POS[0];
    obj->script.data = ROCKET_FUCHIKOMA_LINK_DATA;
    obj->script.unk_0A = 0;
    slot = rocket_fuchikoma_data;
    script_start((Script *)obj, *slot, (s32)slot);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 4, 0x1000);
    obj->vars.enemy.sound_channel[1] = -2;
    obj->vars.fn_800BBB78_obj.unused_250 = 0x4000;
    obj->handlers[1].turn_timer = 0;
    obj->handlers[1].timer = 0;
    obj->unk_226[0] = 0x10;
    obj->vars.enemy.sound_channel[0] = obj->yaw;
    obj->vars.fn_800BBB78_obj.pitch = obj->pitch;
    obj->vars.fn_800BBB78_obj.yaw = obj->yaw;
    obj->vars.fn_800BBB78_obj.roll = obj->roll;
    ROCKET_FUCHIKOMA_UNK_184 = obj->damage;
    return 1;
}

/* Spawns an object of this object's kind (its type plus the index of its asset) at its position in whole
 * units, with its angles (pitch negated), then marks its placement as spawned (byte 4 bits 0-1 = 2). */
s32 obj_spawn_here(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 kind;
    Placement *placement;
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    rot[2] = (u16)obj->roll;
    kind = *(s16 *)&obj->type.unk_0E;
    object_spawn_at(pos, rot, kind + model_slot_pchr(*(s32 *)obj->asset));
    placement_list_pop((ListRecord *)obj->placement);
    placement = obj->placement;
    placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
    return 0;
}

/* Script op (near_radius, far_radius, index): when the player is within far_radius of the object's
 * placement and within near_radius of the object, jump to table entry `index`. */
void script_jump_near_player(Object *obj) {
    s32 near_radius;
    s32 far_radius;
    s32 index;

    near_radius = obj_read_s16(obj);
    far_radius = obj_read_s16(obj);
    index = obj_read_s16(obj);
    if (player_dist_to_obj_point(obj, 1) <= far_radius && player_dist_to_obj_point(obj, 0) <= near_radius) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op: jump to the target given by the operand pair when the object is within radius of a cell corner. */
void script_jump_near(Object *obj) {
    s32 cx;
    s32 cy;
    s32 radius;
    s32 target;
    s16 *cursor;
    s32 dx;
    s32 dy;
    s32 inside;
    s32 px;
    s32 py;
    s32 pz;

    px = obj->x;
    py = obj->y;
    cursor = obj->script.pc;
    pz = obj->z;
    /* shifted in place: a register set twice keeps its load where it is (sched1 moves single-set loads) */
    px >>= 12;
    py >>= 12;
    pz >>= 12;
    obj->script.pc++;
    radius = cursor[0];
    obj->script.pc++;
    target = cursor[1];
    point_to_view_angles(px, py, pz, &cx, &cy);
    dx = cx;
    dy = cy;
    if (dx > 0x800) {
        dx = 0x1000 - dx;
    }
    if (dy > 0x800) {
        dy = 0x1000 - dy;
    }
    inside = dx < radius && dy < radius;
    if (inside) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

/* Reads two halfwords from the script stream and combines them into the speed. */
void script_read_speed_long(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;
    s32 hi;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    hi = pc[1] << 16;
    obj->speed = (lo & 0xFFFF) | hi;
}

void script_read_long(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    obj->speed_accel = pc[1] << 16;
    obj->speed_accel = (lo & 0xFFFF) | obj->speed_accel;
}

/* Reads the next script halfword (cursor at +0x20). With the flag at +0xF8 set, the cursor jumps to the
 * entry of the type's table (+0x1C) that the halfword selects. */
void script_branch_on_flag(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if (obj->script_flag != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}
