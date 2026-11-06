/* arena: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void arena_reset(void) {
    arena_top_ptr = arena_base;
}

void *arena_top(void) {
    return arena_top_ptr;
}

/* Allocates size bytes (rounded up to a word) from the arena_top_ptr arena; returns the block. */
void *arena_alloc(s32 size) {
    u8 *block;

    block = arena_top_ptr;
    arena_top_ptr = block + ((size + 3) & ~3);
    return block;
}

void arena_pop(s32 arg0) {
    arena_top_ptr -= (arg0 + 3) & ~3;
}
