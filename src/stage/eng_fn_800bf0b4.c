/* Shared by s09, s10: sound_emitter_step..obj_script_read_arg (7 functions). */

#include "stage.h"

#if STAGE == 9
/* Behaviour step for the sound-emitting object. handler->result -2 starts
   the sound, -1 stops it, anything else runs the periodic cue. */
void sound_emitter_step(Object *obj, ObjHandler *handler) {
    s32 result;
    s32 handle;

    result = handler->result;
    switch (result) {
    case -2:
        handler->queued_entry = -1;
        handler->result = 0x3C;
        obj->vx = 0;
        obj->vy = 0;
        obj->vz = 0;
        obj->speed = 0;
        if (SOUND_HANDLE(obj) == 0) {
            handle = sound_start(SND_SOUND_EMITTER_LOOP | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
            sound_attach(handle, &obj->x, 0);
            SOUND_HANDLE(obj) = handle;
        }
        break;
    case -1:
        obj_request_state(obj, handler, 1, 0);
        if (SOUND_HANDLE(obj) != 0) {
            sound_stop(SOUND_HANDLE(obj));
            SOUND_HANDLE(obj) = 0;
        }
        break;
    default:
        if (result % 10 == 0) {
            obj_fire_offset(obj, 0x32);
        }
        if ((result + 4) % 11 == 0) {
            obj_fire_offset(obj, 0);
        }
        if (result % 10 == 0) {
            obj_fire_offset(obj, -0x32);
        }
        break;
    }
    obj_pitch_toward_player(obj, 8);
}
#else
/* Behaviour step for the sound-emitting object. handler->result -2 starts
   the sound, -1 stops it, anything else runs the periodic cue. */
void sound_emitter_step(Object *obj, ObjHandler *handler) {
    s32 result;
    s32 handle;

    result = handler->result;
    switch (result) {
    case -2:
        handler->queued_entry = -1;
        handler->result = 0x3C;
        obj->vx = 0;
        obj->vy = 0;
        obj->vz = 0;
        obj->speed = 0;
        /* Sound handle is the byte at 0x25A (spawn variables). */
        if (obj->vars.spawn.unk_25A == 0) {
            handle = sound_start(SND_SOUND_EMITTER_LOOP | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
            sound_attach(handle, &obj->x, 0);
            obj->vars.spawn.unk_25A = handle;
        }
        break;
    case -1:
        obj_request_state(obj, handler, 1, 0);
        if (obj->vars.spawn.unk_25A != 0) {
            sound_stop(obj->vars.spawn.unk_25A);
            obj->vars.spawn.unk_25A = 0;
        }
        break;
    default:
        if (result % 10 == 0) {
            obj_fire_offset(obj, 0x32);
        }
        if ((result + 4) % 11 == 0) {
            obj_fire_offset(obj, 0);
        }
        if (result % 10 == 0) {
            obj_fire_offset(obj, -0x32);
        }
        break;
    }
    obj_pitch_toward_player(obj, 8);
}
#endif

void triple_barrel_robot_update(Object *obj, ObjHandler *handler) {
    if (obj->health > 0) {
        obj_script_step(obj, handler);
    }
}

static inline void obj_spark_at(Object *obj, Vec3 *pos, s32 slot, s32 colour) {
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    spark_add(pos->x >> 12, pos->y >> 12, pos->z >> 12, obj->yaw, 0, 0, slot, colour);
}
void triple_barrel_robot_draw(Object *obj, ObjHandler *handler) {
    Vec3 *pos;
    SVECTOR *rot;
    s32 colour;
    s32 *poses;
    s32 slot;
    SVECTOR *trans;
    Vec3 *spark_pos;

    pos = scratch_alloc(0x10);
    rot = scratch_alloc(0x18);
    slot = obj_keyframe_value(obj, 0);
    spark_pos = pos;
    /* A separate copy of pos, as the original keeps one in $s2 for the spark stores. */
    FAKE_OPAQUE(spark_pos);
    trans = &rot[1];
    if (obj->health > 0) {
        pchr_lists_build(slot);
        slot = pchr_copy_slot(slot);
        poses = pchr_poses_build(slot);
        pchr_table[slot & 0x7FF].unk_0C = poses;
        rot[0].vx = 0;
        rot[0].vy = -0x90;
        rot[0].vz = 0x6E;
        rot[1].vx = -obj->vars.triple_barrel_robot.pitch;
        rot[1].vy = 0;
        rot[1].vz = 0;
        pose_rotate_range(poses, 1, 3, rot, trans);
    }
    colour = 0;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
        /* A second insn in the arm keeps jump.c from turning this into slt/negu/and, while
         * colour keeps its known high byte (spark_add's colour >> 24 folds to 0). */
        __asm__("");
    }
    obj_spark_at(obj, spark_pos, slot, colour);
    aim_marker_draw(2, (SVECTOR *)&obj->width, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x28;
}

/* The stage's triple-barrel robot data (asset, tables, script). */
extern u8 triple_barrel_robot_asset[] asm("d_8011C114");
extern SoundVolume triple_barrel_robot_table_19C[] asm("triple_barrel_robot_sounds");
extern s16 *triple_barrel_robot_script[] asm("triple_barrel_robot_script_table");
extern s16 *triple_barrel_robot_script_pos asm("d_8011C260");
extern ScriptCallEntry triple_barrel_robot_table_194[] asm("triple_barrel_robot_call_table");
extern StateEntry triple_barrel_robot_table_198[] asm("triple_barrel_robot_state_table");
extern s16 *triple_barrel_robot_data[];
void triple_barrel_robot_draw(Object *obj, ObjHandler *handler);

/* Spawns the triple-barrel robot from its placement. */
s32 triple_barrel_robot_spawn(Placement *placement) {
    Object *obj;
    s16 **script_table;
    register s32 kind asm("$3");
    register s16 *script_pos asm("$3");
    register s32 ret asm("$2");

    obj = obj_new();
    ret = 0;
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        placement->unk_02 = 0x708;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->handlers[0].fn = (void (*)(Object *, ObjHandler *))troi_phase0;
        obj->handlers[1].fn = triple_barrel_robot_update;
        obj->handlers[2].fn = obj_run_states_default;
        obj->handlers[3].fn = triple_barrel_robot_draw;
        obj->callback = (s32)obj_respawn_from_placement;
        obj->destructor = obj_sound_handle_stop;
        kind = placement->unk_04[1];
        obj->asset = triple_barrel_robot_asset;
        obj->hit_cooldown_max = 0x30;
        obj->call_table = triple_barrel_robot_table_194;
        obj->state_table = triple_barrel_robot_table_198;
        obj->sounds = triple_barrel_robot_table_19C;
        script_table = triple_barrel_robot_script;
        obj->unk_1C6 = 0;
        obj->kind = kind;
        do { } while (0);
        script_pos = triple_barrel_robot_script_pos;
        obj->script.data = script_table;
        obj->script.unk_0A = 0;
        obj->script.pc = script_pos;
        script_start((Script *)obj, (s16 *)triple_barrel_robot_data[0], (s32)triple_barrel_robot_data);
        obj_init_from_place(obj, placement, 0x27);
        obj_set_part_bounds(obj, 1, 0x1000);
        ret = 1;
        obj->vars.enemy.sound_channel[1] = -2;
        obj->vars.triple_barrel_robot.unused_250 = 0x5000;
        obj->speed_accel = 0x555;
        obj->speed = 0;
        obj->vars.enemy.sound_channel[0] = obj->yaw;
        obj->vars.triple_barrel_robot.pitch = obj->pitch;
        obj->vars.triple_barrel_robot.yaw = obj->yaw;
        obj->vars.triple_barrel_robot.roll = obj->roll;
        obj->speed = 0;
        obj->vars.triple_barrel_robot.unused_258 = 0;
        obj->handlers[1].turn_timer = 0;
        obj->handlers[1].timer = 0;
        obj->unk_226[0] = 0xC;
        *(u8 *)&obj->vars.triple_barrel_robot.unk_25A = 0; /* sound handle */
    }
    return ret;
}

/* Spawns an object of this object's kind (its type plus the index of its asset) at its position in whole
 * units, with its angles (pitch negated), then marks its placement as spawned (byte 4 bits 0-1 = 2). */
s32 obj_respawn_from_placement(Object *obj) {
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

/* Reads the next script halfword (cursor at +0x20). With the flag at +0xF8 set, the cursor jumps to the
 * entry of the type's table (+0x1C) that the halfword selects. */
void obj_script_branch(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if (obj->script_flag != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void obj_script_read_arg(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}
