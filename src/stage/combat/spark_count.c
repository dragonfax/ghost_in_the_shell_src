/* spark_count: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

s32 spark_active_count(void) {
    return 8 - spark_free_count;
}
