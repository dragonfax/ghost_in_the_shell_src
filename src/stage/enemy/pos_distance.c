/* pos_distance: one of the original source files (scripts/objmap.py); s01, s02, s04, s06, s08, s09, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Distance between two positions. */
s32 pos_distance(Vec3 *a, Vec3 *b) {
    return SquareRoot0(length_sq(a->x - b->x, a->y - b->y, a->z - b->z));
}

#if STAGE != 4
s32 obj_player_dist_whole(Object *obj) {
    void *target = player_position();
    Placement *placement = obj->placement;
    Vec3 *pos = scratch_alloc(0x10);
    s32 dist;

    pos->x = placement->x >> 12;
    pos->y = placement->y >> 12;
    pos->z = placement->z >> 12;
    dist = pos_distance(target, pos);
    scratch_top -= 0x10;
    return dist;
}
#endif
