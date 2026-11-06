/* mission_counts: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void set_grenades(s32 value) {
    grenade_count = value;
    grenade_count = NOT_NEGATIVE(MIN(grenade_count, 3));
}

void grenades_add(s32 count) {
    s32 value;
    s32 clamped;
    s32 t;

    if (mission_active != 0) {
        value = grenade_count + count;
        grenade_count = value;
        clamped = value;
        if (clamped > GRENADES_MAX) {
            clamped = GRENADES_MAX;
        }
        t = value;
        if (t > GRENADES_MAX) {
            t = GRENADES_MAX;
        }
        if (t < 0) {
            clamped = 0;
        }
        grenade_count = clamped;
    }
}

s32 grenades_get(void) {
    return grenade_count;
}

/* Sets kill_count, clamped to 0..9999. */
void set_kill_count(s32 value) {
    kill_count = value;
    kill_count = MAX(MIN(kill_count, 9999), 0);
}

/* Adds to the count at kill_count (0..COUNT_MAX) while a mission is active. */
void add_kill_count(s32 amount) {
    s32 value;
    s32 clamped;
    s32 t;

    if (mission_active != 0) {
        value = kill_count + amount;
        kill_count = value;
        clamped = value;
        if (clamped > COUNT_MAX) {
            clamped = COUNT_MAX;
        }
        t = value;
        if (t > COUNT_MAX) {
            t = COUNT_MAX;
        }
        if (t < 0) {
            clamped = 0;
        }
        kill_count = clamped;
    }
}

s32 get_kill_count(void) {
    return kill_count;
}

/* Set mission_limit, clamped to 0..9999. The upper clamp is computed twice, once for the value and once for
 * the test against 0, as the original does. */
void set_mission_limit(s32 value) {
    s32 clamped;
    s32 t;

    mission_limit = value;
    clamped = value;
    if (clamped > COUNT_MAX) {
        clamped = COUNT_MAX;
    }
    t = value;
    if (t > COUNT_MAX) {
        t = COUNT_MAX;
    }
    if (t < 0) {
        clamped = 0;
    }
    mission_limit = clamped;
}

s32 get_mission_limit(void) {
    return mission_limit;
}

void set_mission_total(s32 value) {
    mission_total = value;
}

void add_mission_total(s32 amount) {
    if (mission_active != 0) {
        mission_total += amount;
    }
}

s32 get_mission_total(void) {
    return mission_total;
}

void set_mission_count(s32 value) {
    mission_count = value;
}

void add_mission_count(s32 amount) {
    if (mission_active != 0) {
        mission_count += amount;
    }
}

s32 get_mission_count(void) {
    return mission_count;
}

void set_mission_score(s32 value) {
    mission_score = value;
}

void mission_score_add(s32 amount) {
    if (mission_active != 0) {
        mission_score += amount;
    }
}

s32 get_mission_score(void) {
    return mission_score;
}

void set_stage_end(s32 value) {
    if (((value != 2) || (stage_end == 0)) && ((stage_end == 0) || (stage_end == 2))) {
        stage_end = value;
    }
}

s32 get_stage_end(void) {
    return stage_end;
}

void set_stage_flags(s32 value) {
    stage_flags = value;
}

s32 get_stage_flags(void) {
    return stage_flags;
}

KeyConfig *get_key_config(void) {
    return &key_configs[key_config_index];
}

void set_key_config_index(s32 index) {
    index = NOT_NEGATIVE(index < 4 ? index : 3);
    key_config_index = index;
}

s32 get_key_config_index(void) {
    return key_config_index;
}
