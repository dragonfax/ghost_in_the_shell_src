/* script_radius_jumps: one of the original source files (scripts/objmap.py); s07, s09, s11, s12. */

#include "stage.h"

/* Script op (near_radius, far_radius, index): when the player is within far_radius of the object's
 * placement and within near_radius of the object, jump to table entry `index`. */
void script_jump_if_player_in_radius(Object *obj) {
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
void script_jump_near_corner(Object *obj) {
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
