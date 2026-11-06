/* mission_rank: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void set_run_flag_27(s32 value) {
    d_80120280 = value;
}

s32 get_run_flag_27(void) {
    return d_80120280;
}

void set_run_flag_25(s32 value) {
    d_80120284 = value;
}

s32 get_run_flag_25(void) {
    return d_80120284;
}

/* Picks a value (0xD55, 0x1000 or 0xC4E) from svc_video_mode and get_run_flag_25. */
s32 video_scale(void) {
    s32 mode = svc_video_mode();
    s32 flag = get_run_flag_25();

    if (mode != 0) {
        return 0xD55;
    }
    if (flag == 0) {
        return 0x1000;
    }
    return 0xC4E;
}

/* Index (1-5) of the first 12-byte record whose limit is below the current value, else 0. The stride is a
 * variable in the original (it sits in its own register). */
s32 ranking_place(void) {
    s32 found;
    s32 i;
    s32 value;
    s32 stride;
    LimitRec *recs;
    u8 *base;

    found = 0;
    base = svc_get_shared_state();
    if (base != NULL) {
        if ((u32) (get_stage_end() - 2) < 2U) {
            if (get_area() / 3 == 12) {
                recs = (LimitRec *) (base + 0x68);
            } else {
                recs = (LimitRec *) (base + 0x2C);
            }
            stride = 12;
            value = get_score();
            for (i = 0; i < 5; i++) {
                if (recs->limit < (u32) value) {
                    found = i + 1;
                    break;
                }
                recs = (LimitRec *) ((u8 *) recs + stride);
            }
        }
    }
    return found;
}

/* The mission rank, 0 (best) to 6: at the end of a mission from the time, the two counts and the percentage
 * of the second total; otherwise (while it is not over) 4 to 6 from mission_score. */
s32 mission_rank(void) {
    s32 percent;
    s32 time;
    s32 limit;

    if (get_stage_end() != 2) {
        if (get_mission_score() < 2) {
            return 6;
        }
        if (get_mission_score() < 4) {
            return 5;
        }
        return 4;
    }
    percent = get_mission_total();
    if (percent > 0) {
        percent = get_mission_count() * 100 / percent;
    } else {
        percent = 0;
    }
    time = get_mission_timer();
    limit = get_mission_limit();
    if (get_kill_count() >= limit && time >= 0x960 && percent >= 0x50) {
        return 0;
    }
    if (time >= 0x4B0 && percent >= 0x3C) {
        return 1;
    }
    if (percent >= 0x32) {
        return 2;
    }
    return 3;
}

s32 ending_kind(void) {
    s32 kind;
    s32 empty;
    s32 mode;

    kind = mission_rank();
    if (kind == 0) {
        return 0xB;
    }
    if (kind == 1) {
        return 0xA;
    }
    if (kind == 2) {
        return 9;
    }
    if (kind == 3) {
        return 7;
    }
    empty = get_mission_timer() < 1;
    mode = get_mission_score();
    if (mode == 5) {
        return 8;
    }
    if (mode == 4) {
        if (empty) {
            return 4;
        }
        return 3;
    }
    if (mode >= 2) {
        if (empty) {
            return 6;
        }
        return 3;
    }
    if (empty) {
        return 5;
    }
    return 2;
}

/* Resets the stage's state, then stores the current mission (area / 3, plus one) in the record. */
void stage_begin(void) {
    StageRecord *rec;
    s32 mission;

    set_grenades(1);
    set_shield(0xC8);
    set_score(0);
    set_kill_count(0);
    rec = svc_get_shared_state();
    if (rec != NULL) {
        mission = get_area() / 3;
        if (mission != 0xC) {
            mission++;
            rec->next_mission = mission;
        }
    }
}

/* Resets the HUD and the run state, then updates the run record with the current area. */
void run_restore(void) {
    RunRecord *run;
    s32 mission;

    set_grenades(1);
    set_shield(0xC8);
    run = svc_get_shared_state();
    if (run == NULL) {
        set_key_config_index(0);
        set_run_flag_27(1);
        set_score(0);
        set_run_flag_25(0);
        set_kill_count(0);
        return;
    }
    set_key_config_index(run->flag_28);
    set_run_flag_27(run->flag_27 == 0);
    if (run->unk_CC == 1) {
        set_run_flag_27(0);
    }
    run->unk_CC = 0;
    set_score(run->score);
    set_run_flag_25(run->flag_25 == 1);
    set_kill_count(run->kill_count);
    mission = get_area() / 3;
    if (mission == 12) {
        return;
    }
    mission++;
    run->mission_next = mission;
    run->max_mission_reached = ((u32) run->max_mission_reached < (u32) mission) ? mission : run->max_mission_reached;
}

void record_run_result(void) {
    RunHistory *rec;
    s32 count;
    s32 j;

    rec = svc_get_shared_state();
    if (rec != NULL) {
        rec->score = get_score();
        rec->kill_count = get_kill_count();
        rec->count = 0;
        count = ranking_place();
        if (is_final_area() && count != 0) {
            rec->count = count;
            count--;
            if (get_area() / 3 == 0xC) {
                for (j = 4; count < j; j--) {
                    rec->b[j] = rec->b[j - 1];
                }
                rec->b[count].w[0] = get_score();
                rec->b[count].w[1] = mission_rank();
            } else {
                for (j = 4; count < j; j--) {
                    rec->a[j] = rec->a[j - 1];
                }
                rec->a[count].w[0] = get_score();
                rec->a[count].w[1] = get_kill_count();
            }
        }
        rec->ending = 0;
        if (get_area() / 3 == 0xC) {
            rec->ending = ending_kind();
            return;
        }
        if (get_stage_end() == 2 && get_area() / 3 == 0xB) {
            rec->ending = 1;
            rec->unk_20 = 1;
            rec->max_mission_reached = 0xD;
        }
    }
}

/* Returns the word at 0xC0 of the record svc_get_shared_state returns, or 1 when it returns NULL. */
s32 dev_mode(void) {
    s32 *rec = svc_get_shared_state();
    if (rec == NULL) {
        return 1;
    }
    return rec[0x30]; /* 0xC0 */
}
