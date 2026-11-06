/* shield: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void set_shield(s32 shield) {
    s32 clamped;
    s32 in_range;
    s32 tmp;

    player_shield = shield;
    clamped = shield;
    tmp = clamped < 201;
    in_range = tmp;
    if (!in_range) {
        clamped = 200;
    }
    tmp = 200;
    if (!in_range) {
        shield = tmp;
    }
    if (shield < 0) {
        clamped = 0;
    }
    player_shield = clamped;
}

/* Changes the shield by `amount`, within 0..200 (only while a mission is on). */
void add_shield(s32 amount) {
    if (mission_active != 0) {
        player_shield += amount;
        player_shield = MAX(MIN(player_shield, 0xC8), 0);
    }
}

s32 get_shield(void) {
    return player_shield;
}
