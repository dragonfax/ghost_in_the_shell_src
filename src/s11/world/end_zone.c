/* end_zone: one of s11's own original source files (scripts/objmap.py); part of src/s11/main.c's unit, included there. */

extern SoundSegmentList ambient_sound_owner;
void sound_start_ambient(void) {
    s32 handle = sound_start_attached(SND_AMBIENT_LOOP | SND_HELD | SND_GROUP(2), 0x30, &ambient_sound_owner);

    sound_set_flag_bit1(handle, 0);
}

void end_zone_update(void);
void cam_zone_update_lights(void);
void obj_fixed_draw(void);
extern s32 end_zone_inside_flag;
extern s32 cam_zone_current;
extern PathPoint end_zone_cam_path[21];
s32 end_zone_spawn(void) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }

    list_insert_after((Node *) get_obj_list_b(), (Node *) obj);
    obj->handlers[2].fn = end_zone_update;
    obj->handlers[3].fn = obj_fixed_draw;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->vars.end_zone.unused_248 = 0;
    obj->vars.end_zone.unused_24C = 0;
    end_zone_inside_flag = 0;
    cam_zone_current = -1;
    cam_zone_setup();
    cam_zone_update_lights();
    cam_path_set(0x15, (s32) end_zone_cam_path);
    target_select(5);
    return 1;
}

extern s32 end_zone_min_x;
extern s32 end_zone_max_x;
extern s32 end_zone_min_y;
extern s32 end_zone_max_y;
extern s32 end_zone_min_z;
extern s32 end_zone_max_z;
void end_zone_update(void) {
    s32 x;
    s32 y;
    s32 z;
    s32 inside;

    cam_zone_fade_step();
    cam_zone_update_lights();
    if (end_zone_inside_flag == 0) {
        x = cam_pos >> 12;
        y = cam_pos_y >> 12;
        z = cam_pos_z >> 12;
        if (x < end_zone_min_x || end_zone_max_x < x || y < end_zone_min_y || end_zone_max_y < y ||
            z < end_zone_min_z || end_zone_max_z < z) {
            inside = 0;
        } else {
            inside = 1;
        }
        end_zone_inside_flag = inside;
        if (inside != 0) {
            set_stage_end(2);
        }
    }
}

void obj_fixed_draw(void) {
    cam_path_update();
    req_queue_push(0x7B0, -0x3378, -0x12F0, 4);
}
