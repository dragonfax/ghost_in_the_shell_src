/* clip_poly: one of the original source files (scripts/objmap.py); s02, s10, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"
#include "gte.h"

static inline s32 clip_lerp(s32 to, s32 from, s32 frac) {
    return (to - from) * frac / 0x4000 + from;
}
/* Clips the closed polygon src[0..count) against the near plane z = 0x80 and
 * projects each vertex ((v << 7) / z + offset) into dst; returns how many
 * vertices it wrote. src needs room for count + 1 vertices. */
s32 clip_poly_near_project(s32 count, ClipVertex *src, ClipVertex *dst, s32 ox, s32 oy) {
    s32 out = 0;
    s32 near_z = 0x80;

    *(Unaligned8 *)(src + count) = *(Unaligned8 *)src;

    for (; count > 0; count--, src++) {
        if (src[0].z < near_z) {
            s32 frac, x, y, dz, px, py;
            if (src[1].z < near_z) {
                continue;
            }
            dz = src[1].z - src[0].z;
            frac = ((near_z - src[0].z) << 14) / dz;
            x = clip_lerp(src[1].x, src[0].x, frac);
            y = clip_lerp(src[1].y, src[0].y, frac);
            px = (x << 7) / near_z + ox;
            py = (y << 7) / near_z + oy;
            dst->x = px;
            dst->y = py;
            dst->z = near_z;
            dst++;
            out++;
        } else {
            dst->x = (src[0].x << 7) / src[0].z + ox;
            dst->y = (src[0].y << 7) / src[0].z + oy;
            dst->z = src[0].z;
            dst++;
            out++;
        }
        if (src[1].z < near_z) {
            s32 frac, x, y, dz, px, py;
            dz = src[0].z - src[1].z;
            frac = ((near_z - src[1].z) << 14) / dz;
            x = clip_lerp(src[0].x, src[1].x, frac);
            y = clip_lerp(src[0].y, src[1].y, frac);
            px = (x << 7) / near_z + ox;
            py = (y << 7) / near_z + oy;
            dst->x = px;
            dst->y = py;
            dst->z = near_z;
            dst++;
            out++;
        }
    }
    return out;
}

s32 clip_poly_range(s32 count, ClipVertex *src, ClipVertex *dst, s32 lo, s32 hi)
{
    s32 n;
    s32 dx;

    n = 0;
    src[count] = src[0];
    for (; count > 0; count--, src++) {
        if (src->x < lo) {
            if (src[1].x < lo) {
                continue;
            }
            dx = src[1].x - src->x;
            dst->x = src->y + ((src[1].y - src->y) * (((lo - src->x) << 14) / dx)) / 16384;
            dst->y = lo;
            dst++;
            n++;
        } else if (hi < src->x) {
            if (hi < src[1].x) {
                continue;
            }
            dx = src[1].x - src->x;
            dst->x = src->y + ((src[1].y - src->y) * (((hi - src->x) << 14) / dx)) / 16384;
            dst->y = hi;
            dst++;
            n++;
        } else {
            dst->x = src->y;
            dst->y = src->x;
            n++;
            dst++;
        }
        if (src[1].x < lo) {
            dx = src->x - src[1].x;
            dst->x = src[1].y + ((src->y - src[1].y) * (((lo - src[1].x) << 14) / dx)) / 16384;
            dst->y = lo;
            dst++;
            n++;
        } else if (hi < src[1].x) {
            dx = src->x - src[1].x;
            dst->x = src[1].y + ((src->y - src[1].y) * (((hi - src[1].x) << 14) / dx)) / 16384;
            dst->y = hi;
            dst++;
            n++;
        }
    }
    return n;
}

void *prim_fan_ot_add(s32 count, u32 *verts, u32 *colour, u8 *prim, u8 *ot) {
    u32 link, first, prev, rgb, mode;

    FAKE_OPAQUE(prim);
    count -= 2;
    if (count > 0) {
        rgb = (*colour & 0xFFFFFF) | 0x23000000;
        mode = 0xE1000620;
        ot_link_load(link, ot);
        first = verts[0];
        verts += 2;
        prev = verts[0];
        verts += 2;
        do {
            u32 *wp = (u32 *)prim;
            prim[3] = 5;
            wp[1] = mode;
            wp[2] = rgb;
            wp[3] = first;
            wp[4] = prev;
            prev = *verts;
            verts += 2;
            wp[5] = prev;
            ot_link_store(prim, link);
            link = (u32)prim << 8;
            count--;
            prim += 0x18;
        } while (count > 0);
        ot_link_store(ot, link);
    }
    return prim;
}

#if STAGE != 10
/* The GTE's screen offset y for this stage's copy */
extern s16 screen_offset_y;
#define SCREEN_OFFSET_Y screen_offset_y

s32 clip_poly_near_project(s32 count, ClipVertex *src, ClipVertex *dst, s32 ox, s32 oy);

/* Projects count (1..8) world points relative to the current camera, clips the polygon to the view
 * and adds it as a flat-shaded fan in tint, at an OT depth from the points' mean distance. */
void prim_world_fan_add(s32 count, MatrixRow *verts, u8 *tint) {
    register View *vw asm("$22") = views;
    s32 cam_index = cur_cam_index;
    ClipVertex *pts;
    ClipVertex *clipped;
    s32 *rot;
    Camera *cam;
    s32 i;
    s32 x, y, z;
    s32 depth, dist;
    s32 r0, r1, r2;
    s32 ofx, ofy;
    s32 cx, cy, cz;
    ClipVertex *v;
    WorkArea *wa;

    if ((u32)(count - 1) < 8 && cam_index >= 0) {
        cam = &cameras[cam_index];
        pts = scratch_alloc(0x40);
        clipped = scratch_alloc(0x40);
        rot = scratch_alloc(0x20);
        depth = 0;
        FAKE_OPAQUE(depth);
        scale_rows((s16 *)&vw->unk_2C[0x34], (s16 *)&vw->unk_2C[0xC], (s16 *)rot);
        gte_load_R012(rot, r0, r1, r2);
        gte_load_R34(rot, r0, r1);
        ofx = view_screen_offsets[0].value;
        ofy = SCREEN_OFFSET_Y;
        gte_set_ctrl(OFX, ofx << 16);
        gte_set_ctrl(OFY, ofy << 16);
        gte_set_ctrl(H, 0x80);
        gte_set_ctrl(TRX, 0);
        gte_set_ctrl(TRY, 0);
        gte_set_ctrl(TRZ, 0);
        cx = cam->pos.vx;
        cy = cam->pos.vy;
        cz = cam->pos.vz;
        v = pts;
        for (i = depth; i < count;) {
            x = verts->w[0] - cx;
            y = verts->w[1] - cy;
            z = verts->w[2] - cz;
            gte_set(VXY0, (y << 16) | (x & 0xFFFF));
            gte_set(VZ0, z);
            gte_rtv0tr();
            gte_store(MAC1, v, 0);
            gte_get(MAC2, depth);
            gte_store(MAC3, v, 4);
            i++;
            v->y = depth;
            verts++;
            v++;
        }
        x = 0;
        y = 0;
        v = pts;
        z = 0;
        for (i = 0; i < count;) {
            i++;
            x += v->x;
            y += v->y;
            z += v->z;
            v++;
        }
        x /= count;
        y /= count;
        z /= count;
        depth = SquareRoot0(length_sq(x, y, z));
        dist = depth;
        if (depth < 0) {
            dist = 0;
        }
        dist >>= 5;
        if (dist >= 0x200) {
            dist = 0x1FF;
        }
        depth = 0x208 - dist;
        count = clip_poly_near_project(count, pts, clipped, ((s16 *)vw->screen_offset)[0], ((s16 *)vw->screen_offset)[1]);
        count = clip_poly_range(count, clipped, pts, 0, vw->vram_w);
        count = clip_poly_range(count, pts, clipped, 0, vw->vram_h);
        if (count >= 3) {
            wa = work_area_ptr;
            wa->packet = prim_fan_ot_add(count, (u32 *)clipped, (u32 *)tint, wa->packet,
                                         (u8 *)((u32 *)vw->ot + depth));
        }
        scratch_top -= 0x20;
        scratch_top -= 0x40;
        scratch_top -= 0x40;
    }
}
#endif
