/* clamp: one of s05's own original source files (scripts/objmap.py); part of src/s05/main.c's unit, included there. */

extern s16 clamp_row_table[][3];
extern s32 clamp_row;
void stage_camera_fade_in_step(void);
void clamp_init_stage(void) {
    s32 i;

    i = 0;
    stage_camera_fade_in_step();
    do {
        clamp_set_max_x(i, 0);
        i++;
    } while (i < 8);
    i = 0;
    do {
        s16 v = clamp_row_table[clamp_row][i];
        if (v >= 0) {
            clamp_set_max_x(v, 1);
        }
        i++;
    } while (i < 3);
}

void clamp_draw(void) {
}

extern s32 clamp_row_data[];
/* Spawns the stage's control object (clamp_init_stage, then clamp_draw), resets the clamp table and row,
 * starts the stage camera and shows the opening line. */
s32 clamp_spawn_control(void) {
    Object *obj;
    s32 ok = 0;

    obj = obj_new();
    if (obj != NULL) {
        ok = 1;
        list_insert_after((Node *)get_obj_list_b(), (Node *)obj);
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = (ObjHandlerFn)clamp_init_stage;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = (ObjHandlerFn)clamp_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        clamp_table_set((s32)clamp_row_data);
        clamp_row = 0;
        stage_camera_start();
        target_select(3);
        show_line((s32)"Pursue the target.\xA1");
        set_area_warnings(1);
    }
    return ok;
}

/* File names a data table (enemy_msgs_files) points to by address; they follow this function's string. */
const char file_msgs_spr_so3[] = "msgs_spr.so3";
const char file_msgs_spr_grc[] = "msgs_spr.grc";
const char file_msgs_spr_clt[] = "msgs_spr.clt";

void set_clamp_row(s32 row) {
    s32 clamped = MAX(MIN(row, 5), 0);
    clamp_row = clamped;
}

extern s32 clamp_row;

s32 get_clamp_row(void) {
    return clamp_row;
}

extern s32 clamp_box_table[8][8]; /* {min x, y, z, 0, max x, y, z, 0} */
extern s32 clamp_box_min_z[][8];
extern s32 clamp_box_max_x[][8];
extern s32 clamp_box_max_z[][8];
/* 1 if pos (x,z) lies inside any of the up to 3 boxes listed for room key, shrunk by range */
s32 zone_contains_pos(s32 key, VECTOR *pos, s32 range)
{
    s16 *row;
    s32 i;
    s32 hit;
    s32 box;
    s16 (*rows)[3];
    s32 x, z;

    hit = 0;
    key = MAX(MIN(key, 5), 0);
    i = 0;
    rows = clamp_row_table;
    row = rows[key];
    do {
        box = *row;
        if (box >= 0) {
            s32 x0 = clamp_box_table[box][0] + range;
            s32 z0 = clamp_box_min_z[box][0] + range;
            s32 x1 = clamp_box_max_x[box][0] - range;
            s32 z1 = clamp_box_max_z[box][0] - range;
            x = pos->vx;
            if (x0 < x && x < x1) {
                z = pos->vz;
                if (z0 < z && z < z1) {
                    hit = 1;
                }
            }
        }
        i++;
        row++;
    } while (i < 3);
    return hit;
}

void clamp_row_bounds(s32 row, s32 *center, s32 *extent) {
    s32 i = 0;
    s32 idx;
    s32 min_x = 0x7FFF;
    s32 min_y = 0x7FFF;
    s32 min_z = 0x7FFF;
    s32 max_x = -0x8000;
    s32 max_y = -0x8000;
    s32 max_z = -0x8000;

    row = (((row < 6) ? row : 5) < 0) ? 0 : ((row < 6) ? row : 5);
    for (i = 0; i < 3; i++) {
        idx = clamp_row_table[row][i];
        if (idx >= 0) {
            if (clamp_box_table[idx][0] < min_x) min_x = clamp_box_table[idx][0];
            if (clamp_box_table[idx][1] < min_y) min_y = clamp_box_table[idx][1];
            if (clamp_box_table[idx][2] < min_z) min_z = clamp_box_table[idx][2];
            if (max_x < clamp_box_table[idx][4]) max_x = clamp_box_table[idx][4];
            if (max_y < clamp_box_table[idx][5]) max_y = clamp_box_table[idx][5];
            if (max_z < clamp_box_table[idx][6]) max_z = clamp_box_table[idx][6];
        }
    }

    center[0] = (min_x + max_x) / 2;
    center[1] = (min_y + max_y) / 2;
    center[2] = (min_z + max_z) / 2;
    extent[0] = (max_x - min_x) / 2;
    extent[1] = (max_y - min_y) / 2;
    extent[2] = (max_z - min_z) / 2;
}
