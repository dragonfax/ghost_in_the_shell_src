/* fade: one of startup's own original source files (scripts/objmap.py); part of src/startup/main.c's unit, included there. */

extern void (*slot_1C3)(s32);
void startup_delay_long(void) {
    s32 i;
    for (i = 0; i < 0xF0; i++) {
        slot_1C3(0);
    }
}

void startup_delay_short(void) {
    s32 i;
    for (i = 0; i < 20; i++) {
        slot_1C3(0);
    }
}

#define ADD_PRIM(ot, p) ((p)->tag.addr = (ot)->addr, (ot)->addr = (u32)(p))

extern s32 startup_screen_index;
extern StartupScreen startup_screen;
extern void (*slot_set_disp_mask)(s32 mask);
extern void (*slot_unpex_decompress)(s32 src, u8 *dest);
extern void (*slot_ClearOTag)(PrimTag *ot, s32 n);
extern void (*slot_1D9)(DrawEnv *env, s32 x, s32 y, s32 w, s32 h);
extern void (*slot_1DA)(DispEnv *env, s32 x, s32 y, s32 w, s32 h);
extern s32 (*slot_004)(void);
extern void (*slot_draw_sync)(s32 mode);
extern void (*slot_1C3)(s32 mode);
extern void (*slot_put_disp_env)(DispEnv *env);
extern void (*slot_1C2)(DrawEnv *env);
void vram_clear(void);
s32 offset_table_entry(u8 *base, s32 index);
void palette_set_stp(u16 *palette);
u16 func_800E8760(s32 tp, s32 abr, s32 x, s32 y);

/* slot_draw_sync (0x1CA) and slot_LoadImage (0x1C8), read through their fixed addresses */
#define DRAW_SYNC_AT (*(void (**)(s32))0x80010728)
#define LOAD_IMAGE_AT (*(void (**)(Rect *, void *))0x80010720)

/* Sets up a startup screen: unpacks entry `index` of the archive at base to base + 0x20000, loads its
 * palette (with STP bits) to VRAM (0,480) and its 8-bit image to (640,0), then builds the primitives:
 * screen 5 gets one 256x96 textured quad, a grey gouraud quad and a black band; the others tile the
 * 640x480 image with 256x256 textured quads. Then sets up the draw/display environments (display
 * moved 24 lines down when slot_004 returns 1) and turns the display on. */
void func_800E88EC(u8 *base, s32 index) {
    Rect rect;
    PolyFT4 *poly;
    u8 *data;
    u8 *image;
    s32 x, y, w, h;

    startup_screen_index = index;
    slot_set_disp_mask(0);
    vram_clear();
    data = base + 0x20000;
    vram_clear();
    slot_unpex_decompress(offset_table_entry(base, startup_screen_index), data);
    rect.x = 0;
    rect.y = 0x1E0;
    rect.w = 0x100;
    rect.h = 1;
    palette_set_stp((u16 *)(data + 0x14));
    DRAW_SYNC_AT(0);
    LOAD_IMAGE_AT(&rect, data + 0x14);
    DRAW_SYNC_AT(0);
    slot_ClearOTag(startup_screen.ot, 2);
    startup_screen.count = 0;
    if (startup_screen_index == 5) {
        image = data + 0x220;
        rect.x = 0x280;
        rect.y = 0;
        rect.w = 0x80;
        rect.h = 0x60;
        DRAW_SYNC_AT(0);
        LOAD_IMAGE_AT(&rect, image);
        DRAW_SYNC_AT(0);
        poly = startup_screen.polys;
        poly->tag.len = 9;
        poly->code = 0x2E;
        poly->x0 = 0xCE;
        poly->y0 = 0xC0;
        poly->x1 = 0x1CD;
        poly->y1 = 0xC0;
        poly->x2 = 0xCE;
        poly->y2 = 0x120;
        poly->x3 = 0x1CD;
        poly->y3 = 0x120;
        poly->u0 = 0;
        poly->v0 = 0;
        poly->u1 = 0xFF;
        poly->v1 = 0;
        poly->u2 = 0;
        poly->v2 = 0x60;
        poly->u3 = 0xFF;
        poly->v3 = 0x60;
        poly->clut = 0x7800;
        poly->tpage = func_800E8760(1, 1, 0x280, 0);
        startup_screen.grey.tag.len = 8;
        startup_screen.grey.code = 0x3A;
        startup_screen.grey.x0 = 0xCA;
        startup_screen.grey.y0 = 0xDC;
        startup_screen.grey.x1 = 0x172;
        startup_screen.grey.y1 = 0xDC;
        startup_screen.grey.x2 = 0xCA;
        startup_screen.grey.y2 = 0x10C;
        startup_screen.grey.x3 = 0x152;
        startup_screen.grey.y3 = 0x10C;
        startup_screen.tile.tag.len = 3;
        startup_screen.tile.code = 0x60;
        startup_screen.tile.r0 = 0;
        startup_screen.tile.g0 = 0;
        startup_screen.tile.b0 = 0;
        startup_screen.tile.x0 = 0;
        startup_screen.tile.y0 = 0xC0;
        startup_screen.tile.w = 0x280;
        startup_screen.tile.h = 0x60;
        ADD_PRIM(&startup_screen.ot[1], poly);
        startup_screen.count++;
        ADD_PRIM(&startup_screen.ot[0], &startup_screen.grey);
        ADD_PRIM(&startup_screen.ot[0], &startup_screen.tile);
    } else {
        image = data + 0x220;
        rect.x = 0x280;
        rect.y = 0;
        rect.w = 0x140;
        rect.h = 0x1E0;
        DRAW_SYNC_AT(0);
        LOAD_IMAGE_AT(&rect, image);
        DRAW_SYNC_AT(0);
        poly = startup_screen.polys;
        for (y = 0; y < 0x1E0; y += 0x100) {
            for (x = 0; x < 0x280; x += 0x100) {
                w = (x + 0x100 > 0x280) ? 0x280 - x : 0x100;
                h = 0x100;
                if (y + 0x100 > 0x1E0) {
                    h = 0x1E0 - y;
                }
                poly->tag.len = 9;
                poly->code = 0x2C;
                poly->x0 = x;
                poly->y0 = y;
                poly->x1 = x + w;
                poly->y1 = y;
                poly->x2 = x;
                poly->y2 = y + h;
                poly->x3 = x + w;
                poly->y3 = y + h;
                poly->u0 = x;
                poly->v0 = y;
                poly->u1 = x + (w - 1);
                poly->v1 = y;
                poly->u2 = x;
                poly->v2 = y + (h - 1);
                poly->u3 = x + (w - 1);
                poly->v3 = y + (h - 1);
                poly->clut = 0x7800;
                poly->tpage = func_800E8760(1, 1, x / 2 + 0x280, y);
                ADD_PRIM(&startup_screen.ot[1], poly);
                startup_screen.count++;
                poly++;
            }
        }
    }
    slot_1D9(&startup_screen.draw, 0, 0, 0x280, 0x1E0);
    slot_1DA(&startup_screen.disp, 0, 0, 0x280, 0x1E0);
    startup_screen.draw.r0 = 0;
    startup_screen.draw.g0 = 0;
    startup_screen.draw.b0 = 0;
    startup_screen.draw.isbg = 1;
    startup_screen.draw.dtd = 1;
    startup_screen.draw.dfe = 0;
    startup_screen.draw.tpage = func_800E8760(1, 1, 0x280, 0);
    startup_screen.disp.pad0 = 0;
    startup_screen.disp.isinter = 1;
    startup_screen.disp.isrgb24 = 0;
    if (slot_004() == 1) {
        startup_screen.disp.pad0 = 1;
        startup_screen.disp.screen.y += 0x18;
    }
    slot_draw_sync(0);
    slot_1C3(0);
    slot_put_disp_env(&startup_screen.disp);
    slot_1C2(&startup_screen.draw);
    slot_set_disp_mask(1);
}

extern u8 startup_grey_v0_r;
extern u8 startup_grey_v0_g;
extern u8 startup_grey_v0_b;
extern u8 startup_grey_v1_r;
extern u8 startup_grey_v1_g;
extern u8 startup_grey_v1_b;
extern u8 startup_grey_v2_r;
extern u8 startup_grey_v2_g;
extern u8 startup_grey_v2_b;
extern u8 startup_grey_v3_r;
extern u8 startup_grey_v3_g;
extern u8 startup_grey_v3_b;
static inline s32 scale128(s32 value)
{
    value /= 128;
    return value;
}
/* Sets two grey colours from level (0..128): 52/128 and 40/128 of it, zeroing the bytes after each. */
void startup_grey_set_level(s32 level)
{
    s32 a;

    a = scale128(level * 52);
    startup_grey_v0_r = a;
    startup_grey_v0_g = a;
    startup_grey_v0_b = a;
    startup_grey_v1_r = 0;
    startup_grey_v1_g = 0;
    startup_grey_v1_b = 0;
    a = scale128(level * 40);
    startup_grey_v2_r = a;
    startup_grey_v2_g = a;
    startup_grey_v2_b = a;
    startup_grey_v3_r = 0;
    startup_grey_v3_g = 0;
    startup_grey_v3_b = 0;
}

extern s32 startup_screen_index;
extern StartupScreen startup_screen;
void startup_grey_set_level(s32 level);
void startup_fade_set_level(s32 level)
{
    PolyFT4 *rec;
    s32 i;

    level /= 32;
    rec = startup_screen.polys;
    for (i = 0; i < startup_screen.count; i++) {
        rec->r0 = level;
        rec->g0 = level;
        rec->b0 = level;
        rec++;
    }
    if (startup_screen_index == 5) {
        startup_grey_set_level(level);
    }
}

extern s32 GetODE(void);
void startup_fade_set_level(s32 level);
extern void (*slot_draw_sync)(s32 mode);       /* DrawSync */
extern void (*slot_1C3)(s32 mode);       /* reset slot, called with 0 */
extern void (*slot_DrawOTag)(void *ot);       /* DrawOTag */
extern s32 D_800EE3B4;                     /* OT table */
/* Runs 33 steps with offset 0..0x1000 in 0x80 steps, calling startup_fade_set_level(offset) on each: a GPU
 * sync and reset, a wait for the next GetODE() value, then DrawOTag on D_800EE3B4. The last
 * step waits once more and submits the OT, then syncs and resets again. */
void startup_fade_in(void) {
    s32 offset = 0;
    s32 ode = GetODE();
    do {
        startup_fade_set_level(offset);
        offset += 0x80;
        slot_draw_sync(0);
        slot_1C3(0);
        while (ode == GetODE()) {
        }
        ode = GetODE();
        slot_DrawOTag(&D_800EE3B4);
    } while (offset < 0x1001);
    slot_draw_sync(0);
    slot_1C3(0);
    do {
    } while (ode == GetODE());
    slot_DrawOTag(&D_800EE3B4);
    slot_draw_sync(0);
    slot_1C3(0);
}

/* Fade-out for the startup screen: steps the level from 0x1000 down by 0x80,
   one frame per step (waiting for each vblank), then waits one more frame. */
void startup_fade_out(void) {
    s32 level;
    s32 ode;

    level = 0x1000;
    ode = GetODE();
    do {
        startup_fade_set_level(level);
        level -= 0x80;
        slot_draw_sync(0);
        slot_1C3(0);
        do {
        } while (ode == GetODE());
        ode = GetODE();
        slot_DrawOTag(&D_800EE3B4);
    } while (level >= 0);
    slot_draw_sync(0);
    slot_1C3(0);
    do {
    } while (ode == GetODE());
    slot_DrawOTag(&D_800EE3B4);
    slot_draw_sync(0);
    slot_1C3(0);
}
