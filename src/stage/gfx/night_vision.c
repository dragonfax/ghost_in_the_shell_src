/* night_vision: one of the original source files (scripts/objmap.py); s02, s08. */

#include "stage.h"

/* Create the object that runs the state machine: clear its handler phases and reset the four globals. */
void night_vision_init(void) {
    Object *obj = obj_new();

    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_b(), (Node *)obj);
        obj->handlers[2].fn = (ObjHandlerFn)night_vision_ramp;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = (ObjHandlerFn)night_vision_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        night_vision_level = 0;
        night_vision_target = 0;
        night_vision_copy_flag = 0;
        night_vision_active = 0;
    }
}

void night_vision_ramp(void) {
    s32 prev = night_vision_level;

    if (night_vision_target != 0) {
        s32 up = prev + 0x55;
        s32 hi = 0x1000;
        if (up < 0x1001) {
            hi = up;
        }
        night_vision_level = hi;
    } else {
        s32 down = prev - 0x55;
        if (down < 0) {
            down = 0;
        }
        night_vision_level = down;
    }
    if (night_vision_level >= 0x800) {
        if (prev < 0x800) {
            show_line((s32)"#2Switch to night vision.\xA1");
            sound_start(SND_NIGHT_VISION_ON | SND_VOICE_FLAG, 0x7F, 0, 0);
        }
    } else if (prev >= 0x800) {
        show_line((s32)"#2Switch to normal mode.\xA1");
        sound_start(SND_NIGHT_VISION_OFF | SND_VOICE_FLAG, 0x7F, 0, 0);
    }
    night_vision_active = night_vision_level >= 0x800;
}

/* Per-stage rodata rect {0x300, 0, 0x100, 0xD8}: the copy target's x, y. */
/* x and y read as two globals, each by its own symbol (the rect's start and the label 2 bytes in): reading them
 * as fields of the RectU would share one address between the loads and change the code. */
extern u16 nv_rect_x __asm__("night_vision_rect");
extern u16 nv_rect_y __asm__("night_vision_rect_y");
#define NV_RECT_X nv_rect_x
#define NV_RECT_Y nv_rect_y

typedef struct PrimNightVision {
    u8 unk_00[3];
    u8 code;
    u8 unk_04[3];
    u8 unk_07;
    u32 unk_08;
    s16 x0, y0, x1, y1, x2, y2;
} PrimNightVision;

/* Builds a code-5 primitive copying the object's (x, y) to the rect, sized to the screen, and links it into ot. */
void night_vision_copy_prim(void *obj, void *ot) {
    u8 *base = obj;
    PrimNightVision *prim = *(PrimNightVision **)(base + 0x74);
    ScreenSize *screen = (ScreenSize *)&stage_screen_w;
    u16 rect_x = NV_RECT_X;
    u16 y;

    *(PrimNightVision **)(base + 0x74) = prim + 1;
    prim->code = 5;
    prim->unk_07 = 1;
    prim->unk_08 = 0x80000000;
    prim->x0 = *(u16 *)(base + 0x14);
    y = *(u16 *)(base + 0x16);
    prim->x1 = rect_x;
    prim->y1 = NV_RECT_Y;
    prim->y0 = y;
    prim->x2 = screen->w;
    prim->y2 = screen->h;
    addPrim(ot, prim);
}

/* View.vram_x..vram_h as one rect */
typedef struct NVRect {
    s16 x, y, w, h;
} NVRect;

typedef struct PolyF4Night {
    u8 link[3];
    u8 len;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} PolyF4Night;

typedef struct DrModeNight {
    u8 link[3];
    u8 len;
    u32 code;
} DrModeNight;

/* Night-vision overlay: copies view 0's VRAM rect back over itself, tinted green by the ramp level night_vision_level. */
void night_vision_draw_overlay(void) {
    WorkArea *work;
    u32 *ot;
    NVRect *rect;
    View *view;
    u32 rect_y;
    s32 blue, red, green;
    PolyFT4 *quad;
    PolyF4Night *flat;
    DrModeNight *mode;
    DrTwin *twin;

    view = views;
    if (views[0].camera < 0 || night_vision_level == 0) {
        return;
    }
    ot = (u32 *)((u8 *)views[0].ot + 0x824);
    work = work_area_ptr;
    rect = (NVRect *)&view->vram_x;
    if (night_vision_active != 0) {
        night_vision_copy_prim(work, ot);
        if (night_vision_copy_flag != 0) {
            mode = work->packet;
            work->packet = mode + 1;
            mode->len = 1;
            mode->code = 0xE1000620;
            addPrim(ot, mode);
            quad = work->packet;
            work->packet = quad + 1;
            rect_y = NV_RECT_Y;
            quad->len = 9;
            quad->code = 0x2F;
            quad->tpage = 0x100 | ((rect_y >> 4) & 0x10) | ((NV_RECT_X & 0x3FF) >> 6) | ((rect_y & 0x200) << 2);
            quad->x0 = 0;
            quad->y0 = 0;
            quad->x1 = views[0].vram_w;
            quad->y1 = 0;
            quad->x2 = 0;
            quad->y2 = views[0].vram_h;
            quad->x3 = views[0].vram_w;
            quad->y3 = views[0].vram_h;
            quad->u0 = view->vram_x;
            quad->v0 = views[0].vram_y;
            quad->u1 = (u8)view->vram_x + (u8)views[0].vram_w;
            quad->v1 = views[0].vram_y;
            quad->u2 = view->vram_x;
            quad->v2 = (u8)views[0].vram_y + (u8)views[0].vram_h;
            quad->u3 = (u8)view->vram_x + (u8)views[0].vram_w;
            quad->v3 = (u8)views[0].vram_y + (u8)views[0].vram_h;
            addPrim(ot, quad);
            mode = work->packet;
            work->packet = mode + 1;
            mode->len = 1;
            mode->code = 0xE1000420;
            addPrim(ot, mode);
        }
        night_vision_copy_flag = 1;
    }
    if (night_vision_level < 0x800) {
        blue = -(night_vision_level * 0xC0) / 0x1000 + 0x80;
        green = blue;
        red = blue;
    } else {
        s32 inv;

        flat = work->packet;
        work->packet = flat + 1;
        flat->len = 5;
        flat->code = 0x2A;
        flat->r0 = 0;
        flat->g0 = ((0x1000 - night_vision_level) * 0x180) / 0x1000 + 0x20;
        flat->b0 = 0;
        flat->x0 = 0;
        flat->y0 = 0;
        flat->x1 = rect->w;
        flat->y1 = 0;
        flat->x2 = 0;
        flat->y2 = rect->h;
        flat->x3 = rect->w;
        flat->y3 = rect->h;
        addPrim(ot, flat);
        inv = 0x1000 - night_vision_level;
        red = inv / 64 + 0x10;
        green = (inv * 0xFE) / 0x1000 + 0x80;
        blue = red;
    }
    quad = work->packet;
    work->packet = quad + 1;
    quad->len = 9;
    quad->code = 0x2C;
    /* tpage: 15-bit direct, semi-transparency mode 1, at the work area's origin + rect */
    quad->tpage = (2 << 7) | (1 << 5) | (((work->draw_y + rect->y) & 0x100) >> 4) | (((work->draw_x + rect->x) & 0x3ff) >> 6) |
                  (((work->draw_y + rect->y) & 0x200) << 2);
    quad->r0 = red;
    quad->g0 = green;
    quad->b0 = blue;
    quad->x0 = 0;
    quad->y0 = 0;
    quad->x1 = rect->w;
    quad->y1 = 0;
    quad->x2 = 0;
    quad->y2 = rect->h;
    quad->x3 = rect->w;
    quad->y3 = rect->h;
    quad->u0 = rect->x;
    quad->v0 = rect->y;
    quad->u1 = (u8)rect->x + (u8)rect->w;
    quad->v1 = rect->y;
    quad->u2 = rect->x;
    quad->v2 = (u8)rect->y + (u8)rect->h;
    quad->u3 = (u8)rect->x + (u8)rect->w;
    quad->v3 = (u8)rect->y + (u8)rect->h;
    addPrim(ot, quad);
    twin = work->packet;
    work->packet = twin + 1;
    twin->len = 2;
    twin->code[0] = 0xE2000000;
    twin->code[1] = 0;
    addPrim(ot, twin);
}

void night_vision_draw(void) {
    night_vision_draw_overlay();
}
