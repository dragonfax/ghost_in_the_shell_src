/* stage_timers: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

extern volatile s32 D_80128184 __asm__("loop_state");
extern s16 timer_dir;
extern volatile s16 timer_rate;
extern volatile s16 timer_spark_value;
extern volatile s32 timer_pos_x;
extern volatile s32 timer_pos_y;
extern volatile s32 timer_pos_z;
/* Plain views of the volatile globals above (timer_sparks_emit's loads are not volatile). */
extern s32 plain_80128188 __asm__("timer_pos_x");
extern s32 plain_8012818C __asm__("timer_pos_y");
extern s32 plain_80128190 __asm__("timer_pos_z");
extern s16 plain_8012819E __asm__("timer_rate");
extern s16 plain_801281A0 __asm__("timer_spark_value");

void timer_sparks_emit(void) {
    s16 rot[3];
    s32 pos[3];
    Object *obj;
    s32 scaled;
    register s32 level asm("$3");
    s32 hi;
    s32 low;
    s32 colour_a;
    s32 colour_b;
    s32 size;
    s32 value;
    register s32 rate asm("$5");

    if (timer_active == 0) {
        return;
    }
    obj = loop_state.owner;
    rot[0] = plain_80128188;
    rot[1] = plain_8012818C;
    rot[2] = plain_80128190;
    model_part_transform(obj->vars.bomb_mech_m7_boss.unk_248, 5, rot);
    obj_point_to_world(obj, rot, &pos[0], &pos[1], &pos[2]);

    rate = plain_8012819E;
    scaled = rate + ((rate * 5) << 2);
    level = scaled >> 5;
    hi = level;
    if (level == 0) {
        hi = 1;
    }
    low = level;
    colour_a = (hi << 16) | (level << 8) | low;
    if (low == 0) {
        low = 1;
    }
    colour_b = low << 16;

    scaled = scaled / 3;
    size = scaled * timer_scale;
    if (size < 0) {
        size += 0xFFF;
    }
    value = pool_spawn_scaled(plain_801281A0, size >> 12, size >> 12, size >> 12);
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, value, colour_a);

    size = timer_scale << 12;
    if (size < 0) {
        size += 0xFFF;
    }
    value = pool_spawn_scaled(plain_801281A0, size >> 12, size >> 12, size >> 12);
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, value, colour_b);
}

void timer_arm(Object *obj, volatile s32 *pos, void *p) {
    s32 z;
    if (timer_active != 1) {
        timer_dir = 3;
        timer_elapsed = 0;
        timer_active = 1;
        timer_pos_x = pos[0];
        timer_pos_y = pos[1];
        z = pos[2];
        D_80128184 = (s32)obj;
        timer_rate = 0;
        timer_spark_value = (s16)(s32)p;
        timer_pos_z = z;
    }
}

extern s16 timer_dir;

void timer_reverse(void) {
    timer_dir = -3;
}

extern s16 timer_elapsed;
extern s16 timer_dir;
extern s16 timer_active;
extern s16 timer_scale;

void timer_reset(void) {
    loop_state.owner = NULL;
    timer_elapsed = 0;
    timer_dir = 0;
    timer_scale = 0x1000;
    timer_active = 0;
}

extern s16 timer_elapsed;
extern s16 timer_dir;
extern s16 timer_active;
extern s16 timer_scale;

void boss_state_reset(void) {
    loop_state.owner = NULL;
    timer_elapsed = 0;
    timer_dir = 0;
    timer_scale = 0x1000;
    timer_active = 0;
}
