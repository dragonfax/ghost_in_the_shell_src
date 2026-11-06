/* transform_point: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

VECTOR *transform_point(VECTOR *in, VECTOR *out) {
    gte_load(IR1, in, 0);
    gte_load(IR2, in, 4);
    gte_load(IR3, in, 8);
    gte_rtirtr();
    gte_store(MAC1, out, 0);
    gte_store(MAC2, out, 4);
    gte_store(MAC3, out, 8);
    return out;
}
