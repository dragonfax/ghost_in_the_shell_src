/* mission_clock: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void mission_clock_step(void) {
    if ((mission_active != 0) && !(get_stage_flags() & 4)) {
        mission_elapsed += 1;
        if (mission_timer > 0) {
            mission_timer -= 1;
        }
    }
}

s32 get_mission_elapsed(void) {
    return mission_elapsed;
}

void set_mission_timer(s32 time) {
    time = NOT_NEGATIVE(time < 6000 ? time : 5999);
    mission_timer = time;
}

s32 get_mission_timer(void) {
    return mission_timer;
}

/* Set the score (player_score), clamped to 0..9999999. The upper clamp is computed twice, once for the value and once for
 * the test against 0, as the original does. */
void set_score(s32 value) {
    s32 clamped;
    s32 t;

    player_score = value;
    clamped = value;
    if (clamped > SCORE_MAX) {
        clamped = SCORE_MAX;
    }
    t = value;
    if (t > SCORE_MAX) {
        t = SCORE_MAX;
    }
    if (t < 0) {
        clamped = 0;
    }
    player_score = clamped;
}

void add_score(s32 points) {
    s32 value;
    s32 clamped;
    s32 t;

    if (mission_active) {
        value = player_score + points;
        player_score = value;
        clamped = value;
        if (clamped > SCORE_MAX) {
            clamped = SCORE_MAX;
        }
        t = value;
        if (t > SCORE_MAX) {
            t = SCORE_MAX;
        }
        if (t < 0) {
            clamped = 0;
        }
        player_score = clamped;
    }
}

s32 get_score(void) {
    return player_score;
}
