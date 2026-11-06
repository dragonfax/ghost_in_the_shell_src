/* lens_flare: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

static inline s32 light_falloff(s32 x, s32 y, s32 z) {
    s32 mac1, near, far;

    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, z);
    gte_sqr0();
    far = 0x400000;
    near = 0x100000;
    gte_get(MAC1, mac1);
    gte_get(MAC2, y);
    gte_get(MAC3, z);
    y = mac1 + y + z; /* the squared distance */
    if (y <= near) {
        return 0x1000;
    }
    if (y >= far) {
        return 0;
    }
    return ((far - y) << 2) / ((far - near) >> 10);
}
/* Draws the glow sprites of the point lights of environment light_env_index near the camera into ot. */
void point_light_glow_draw(u8 *ot) {
    s32 *rot;
    WorkArea *wa;
    PointLight *light;
    Camera *cam;
    s32 count, env, camx, camy, camz;
    s32 dx, dy, dz, intensity, scale, falloff, flag;
    s32 a, b, c;
    PrimGp0Cmd *cmd;

    if (light_data_base == 0 || light_env_index < 0) {
        return;
    }
    rot = (s32 *)scratch_top;
    scratch_top += 0x20;
    scale_rows((s16 *)((u8 *)view_scale_base - 0x20 + cur_view_index * 0xA8), (s16 *)((u8 *)view_scale_base - 0x48 + cur_view_index * 0xA8), (s16 *)rot);
    gte_set_R012(a, b, c, rot[0], rot[1], rot[2]);
    gte_set_R34(a, b, rot[3], rot[4]);
    scratch_top -= 0x20;
    gte_set_screen_h80_origin();
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    cam = &cameras[cur_camera_index];
    wa = work_area_ptr;
    env = light_env_index;
    count = *(s32 *)light_data_base;
    camx = cam->pos.vx;
    camy = cam->pos.vy;
    camz = cam->pos.vz;
    light = (PointLight *)(light_data_base + 4);
    for (; count > 0; count--, light++) {
        if (light->env != env) {
            continue;
        }
        dz = light->z;
        dx = light->x;
        dy = light->y;
        intensity = light->intensity;
        if (intensity < 0) {
            intensity = -intensity;
        } else {
            dz -= camz;
            if (ABS(dz) > 0x800) {
                continue;
            }
            dx -= camx;
            if (ABS(dx) > 0x800) {
                continue;
            }
            dy -= camy;
            if (ABS(dy) > 0x800) {
                continue;
            }
        }
        falloff = light_falloff(dx, dy, dz);
        if (falloff <= 0) {
            continue;
        }
        gte_set(VXY0, (dy << 16) | (dx & 0xFFFF));
        gte_set(VZ0, dz);
        gte_rtps();
        gte_get_ctrl(FLAG, flag);
        gte_get(SXY2, dx); /* dx, dy now the screen position */
        if (flag < 0) {
            continue;
        }
        dy = dx >> 16;
        dx = (s16)dx;
        scale = intensity * falloff;
        wa->packet = lens_flare_draw((u32 *)ot, wa->packet, dx, dy, scale / 4096, scale / 4096, scale / 4096);
    }
    cmd = wa->packet;
    wa->packet = cmd + 1;
    cmd->len = 2;
    cmd->code = 0xE2000000;
    cmd->pad = 0;
    addPrim(ot, cmd);
}

void *lens_flare_draw(u32 *ot, PolyFT4 *prim, s32 x, s32 y, s32 r, s32 g, s32 b)
{
    s32 fade;
    s32 red, green, blue;
    s32 color;
    s32 i;
    LensFlare *flare;

    flare = lens_flare_table;
    fade = (0x1000 - isqrt(x * x + y * y) * 16) * 3 / 2;
    fade = MAX(MIN(fade, 0x1000), 0);
    r = r * fade / 4096;
    g = g * fade / 4096;
    b = b * fade / 4096;
    for (i = 0; i < 16; i++, flare++) {
        s32 cx = x * flare->offset / -120;
        s32 cy = y * flare->offset / -120;
        s32 half;
        s32 w;
        s32 h;

        cx += x + ((FlareView *)&view_tails[0].ofs_x)[cur_view_index].x;
        cy += y + ((FlareView *)&view_tails[0].ofs_x)[cur_view_index].y;
        half = flare->size / 2;
        w = half * ((FlareView *)&view_tails[-1].next_scale_x)[cur_view_index].x / 4096;
        h = half * ((FlareView *)&view_tails[-1].next_scale_x)[cur_view_index].y / 4096;

        if (cx + w < 0) {
            continue;
        }
        if (cx - w > ((FlareView *)&view_tails[0].vram_x)[cur_view_index].w) {
            continue;
        }
        if (cy + h < 0) {
            continue;
        }
        if (cy - h > ((FlareView *)&view_tails[0].vram_x)[cur_view_index].h) {
            continue;
        }
        red = flare->intensity * flare->r / 4096 * r / 0x20000;
        green = flare->intensity * flare->g / 4096 * g / 0x20000;
        blue = flare->intensity * flare->b / 4096 * b / 0x20000;
        color = red | (green << 8) | (blue << 16);
        prim = prim_sprite_mirror4(ot, prim, cx, cy, w, h, color, flare->pal);
    }
    return prim;
}

/* Draws a sprite as four mirrored POLY_FT4 quads around (x, y), each w by h, linked into ot.
 * The CLUT sits at row 220, column 256 + 16 * pal. Returns the next free primitive.
 * Old-style definition: x and y arrive as int (lens_flare_draw passes them untruncated)
 * and are narrowed here, which the prototype's s32 x, y allows. */
void *prim_sprite_mirror4(ot, prim, x, y, w, h, color, pal)
    u32 *ot;
    PolyFT4 *prim;
    s16 x;
    s16 y;
    s32 w;
    s32 h;
    s32 color;
    s32 pal;
{
    s16 right;
    s16 bottom;
    s16 left;
    s16 top;
    u16 clut;
    PolyFT4 *second;
    PolyFT4 *third;
    PolyFT4 *fourth;
    PolyFT4 *next = prim + 1;

    prim[0].len = 9;
    prim[0].tpage = 0xB0;
    prim[0].u2 = 0x40;
    prim[0].u0 = 0x40;
    prim[0].u3 = 0x7F;
    prim[0].u1 = 0x7F;
    prim[0].v1 = 0x40;
    prim[0].v0 = 0x40;
    prim[0].v3 = 0x7F;
    prim[0].v2 = 0x7F;
    prim[0].x2 = x;
    prim[0].x0 = x;
    prim[0].y1 = y;
    prim[0].y0 = y;
    right = x + w;
    bottom = y + h;
    clut = (((pal * 16 + 0x100) >> 4) & 0x3F) | (0xDC << 6);
    *(s32 *)&prim[0].r0 = color;
    prim[0].code = 0x2E;
    prim[0].clut = clut;
    prim[0].x3 = right;
    prim[0].x1 = right;
    prim[0].y3 = bottom;
    prim[0].y2 = bottom;
    addPrim(ot, prim);
    left = x - w;
    second = next++;
    *(s32 *)&prim[1].r0 = color;
    prim[1].len = 9;
    prim[1].code = 0x2E;
    prim[1].tpage = 0xB0;
    prim[1].clut = clut;
    prim[1].u2 = 0x40;
    prim[1].u0 = 0x40;
    prim[1].u3 = 0x7F;
    prim[1].u1 = 0x7F;
    prim[1].v1 = 0x40;
    prim[1].v0 = 0x40;
    prim[1].v3 = 0x7F;
    prim[1].v2 = 0x7F;
    prim[1].x2 = x;
    prim[1].x0 = x;
    prim[1].x3 = left;
    prim[1].x1 = left;
    prim[1].y1 = y;
    prim[1].y0 = y;
    prim[1].y3 = bottom;
    prim[1].y2 = bottom;
    addPrim(ot, second);
    top = y - h;
    third = next++;
    *(s32 *)&prim[2].r0 = color;
    prim[2].len = 9;
    prim[2].code = 0x2E;
    prim[2].tpage = 0xB0;
    prim[2].clut = clut;
    prim[2].u2 = 0x40;
    prim[2].u0 = 0x40;
    prim[2].u3 = 0x7F;
    prim[2].u1 = 0x7F;
    prim[2].v1 = 0x40;
    prim[2].v0 = 0x40;
    prim[2].v3 = 0x7F;
    prim[2].v2 = 0x7F;
    prim[2].x2 = x;
    prim[2].x0 = x;
    prim[2].x3 = left;
    prim[2].x1 = left;
    prim[2].y1 = y;
    prim[2].y0 = y;
    prim[2].y3 = top;
    prim[2].y2 = top;
    addPrim(ot, third);
    fourth = next++;
    *(s32 *)&prim[3].r0 = color;
    prim[3].len = 9;
    prim[3].code = 0x2E;
    prim[3].tpage = 0xB0;
    prim[3].clut = clut;
    prim[3].u2 = 0x40;
    prim[3].u0 = 0x40;
    prim[3].u3 = 0x7F;
    prim[3].u1 = 0x7F;
    prim[3].v1 = 0x40;
    prim[3].v0 = 0x40;
    prim[3].v3 = 0x7F;
    prim[3].v2 = 0x7F;
    prim[3].x2 = x;
    prim[3].x0 = x;
    prim[3].x3 = right;
    prim[3].x1 = right;
    prim[3].y1 = y;
    prim[3].y0 = y;
    prim[3].y3 = top;
    prim[3].y2 = top;
    addPrim(ot, fourth);
    return next;
}
