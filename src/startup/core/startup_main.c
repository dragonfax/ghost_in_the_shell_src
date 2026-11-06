/* startup_main: one of startup's own original source files (scripts/objmap.py); part of src/startup/main.c's unit, included there. */

void startup_frame_tick(void) {
    startup_frame_count += 1;
    D_800EE1B0 |= slot_read_pad(1) & 0x800;
}

extern s32 (*slot_add_frame_task)(void (*fn)(void), s32 period);
extern s32 startup_frame_count;
extern s32 D_800EE1B0;
extern s32 D_800ECF30;
void startup_frame_tick(void);
/* Clears the flags startup_frame_count and D_800EE1B0, then adds startup_frame_tick as a period-0 frame task through the
 * service at slot_add_frame_task. The service's return value goes to D_800ECF30. */
void startup_frame_task_start(void) {
    startup_frame_count = 0;
    D_800EE1B0 = 0;
    D_800ECF30 = slot_add_frame_task(&startup_frame_tick, 0);
}

extern void (*slot_remove_frame_task)(s32 task);
/* Removes the frame task whose id is in D_800ECF30, if one was added. */
void startup_frame_task_stop(void) {
    if (D_800ECF30 >= 0) {
        slot_remove_frame_task(D_800ECF30);
    }
}

extern s32 startup_frame_count;

void startup_frame_count_set(s32 arg0) {
    startup_frame_count = arg0;
}

extern s32 startup_frame_count;

s32 startup_frame_count_get(void) {
    return startup_frame_count;
}

extern s32 D_800EE1B0;

s32 startup_frame_flags_get(void) {
    return D_800EE1B0;
}

void startup_wait_frames(s32 arg0) {
loop_1:
    if (startup_frame_count_get() < arg0) {
        if (startup_frame_flags_get() == 0) {
            goto loop_1;
        }
    }
}

SVC_HEADER_CONSTS(startup);

extern s32 (*slot_read_file)(u8 *name, void *dest, s32 mode);
extern s32 (*slot_0A0)(s32 mode, void *dest, s32 arg);
extern void (*slot_0A2)(s32 mode);
extern void (*slot_0B4)(s32 mode, s32 arg);
extern void (*slot_0B7)(s32 mode);
extern s32 *(*slot_shared_state)(void);
void startup_fade_in(void);
void startup_fade_out(void);
void startup_noop(void);
u8 *func_800E871C(void);
void func_800E88EC(u8 *base, s32 index);
void startup_main(void) {
    s32 ear_size;
    s32 *shared;
    u8 *vab_buf;
    u8 *base;

    startup_noop();
    if (((s32 (*)(void))svc_table_startup[0])() != 0x300) {
        printf(bios_version_error_startup);
        while (1) {}
    }
    base = func_800E871C();
    vab_buf = base + 0x80000;
    startup_frame_task_start();
    do {
        ear_size = slot_read_file((u8 *)"ROOT\\STARTUP.EAR", base, 0);
    } while (ear_size == -1);
    if (ear_size > 0) {
        func_800E88EC(base, 6);
        startup_fade_in();
    }
    startup_frame_count_set(0);
    slot_0B4(3, 0);
    slot_0B7(1);
    while (slot_read_file((u8 *)"VAB\\JOCHUOK.VAB", vab_buf, 0) < 0) {
        printf("Resident VAB Read Error.\r");
    }
    while (slot_0A0(0, vab_buf, 0) < 0) {
        printf("Resident VAB Regist Error.\r");
    }
    slot_0A2(1);
    startup_wait_frames(0x64);
    if (ear_size > 0) {
        startup_fade_out();
    }
    if (startup_frame_flags_get() == 0 && ear_size > 0) {
        func_800E88EC(base, 7);
        startup_fade_in();
        startup_frame_count_set(0);
        startup_wait_frames(0x64);
        startup_fade_out();
        if (startup_frame_flags_get() == 0) {
            func_800E88EC(base, 5);
            startup_fade_in();
            startup_frame_count_set(0);
            startup_wait_frames(0x64);
            startup_fade_out();
        }
    }
    startup_frame_task_stop();
    shared = slot_shared_state();
    if (startup_frame_flags_get() != 0) {
        shared[0x33] = 1;
        return;
    }
    shared[0x33] = 0;
}
