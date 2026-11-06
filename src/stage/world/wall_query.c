/* wall_query: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

s32 *span_source_build(s32 table) {
    StripOut *out = (StripOut *)heap_get_top();
    s32 sets = get_rec_count();
    s32 i;
    s32 total = 0;

    for (i = 0; i < sets; i++) {
        StripSet *set = (StripSet *)rec_deref_word(i);
        s32 ox = ((StripOrigin *)get_rec_data(i))->z;
        s32 oy = ((StripOrigin *)get_rec_data(i))->x;
        s32 n = set->count;
        StripSeg *seg = set->segs;

        while (n > 0) {
            StripPoint *p = (StripPoint *)(total * 8 + (s32)out + 4);
            s32 k = 0;
            StripRange *r = (StripRange *)(seg->range * 4 + table);
            s32 first = (++r)->first; /* r = &tab->ranges[seg->range] */
            s32 px = seg->dx + ox;
            s32 py = seg->dy + oy;
            s32 cnt = r->count;

            for (; k < cnt; ) {
                k++;
                p->x = (px << 12) + (first & 0xFFF);
                first++;
                p->y = py << 12;
                p++;
            }
            total += cnt;
            n--;
            seg++;
        }
    }
    out->count = total;
    heap_set_top((s32)&out->pts[total]);
    return (s32 *)out;
}

/* For each keyed quad, bins its coordinate range (plus the key's offset) into
 * 256 spans of 1024; returns the number of spans written to out. */
s32 span_edges_build(s32 count, s32 *src, s32 quads, SpanEdge *out) {
    s32 i;
    s32 n;
    s32 key;
    SpanQuad *q;
    SpanEdge *o;
    u32 off;
    s16 y1, y2, y3;
    s32 lo, hi;

    i = 0;
    n = 0;
    for (; i < count; i++, src += 2) {
        key = src[0];
        q = &((SpanQuad *)quads)[key & 0xFFF];
        key >>= 12;
        y1 = q->y1;
        lo = (q->y0 <= y1) ? q->y0 : y1;
        y2 = q->y2;
        if (y2 < lo) lo = y2;
        y3 = q->y3;
        if (y3 < lo) lo = y3;
        hi = (q->y0 >= y1) ? q->y0 : y1;
        if (hi < y2) hi = y2;
        if (hi < y3) hi = y3;
        lo = ((lo + key) >> 10) & 0xFF;
        hi = ((hi + key) >> 10) & 0xFF;
        if (hi < lo) {
            /* wrapped span: emit [0, hi] first */
            off = n * sizeof(SpanEdge);
            n++;
            o = (SpanEdge *)(off + (u32)out);
            o->y1 = hi;
            hi = 0xFF;
            o->y0 = 0;
            o->value = i;
        }
        off = n * sizeof(SpanEdge);
        n++;
        o = (SpanEdge *)(off + (u32)out);
        o->value = i;
        o->y0 = lo;
        o->y1 = hi;
    }
    return n;
}

static inline void edge_copy(SpanEdge *dst, SpanEdge *src)
{
    s32 first = *(s32 *)&src->y0;
    s32 second = *(s32 *)&src->value;

    *(s32 *)&dst->y0 = first;
    *(s32 *)&dst->value = second;
}
/* Shell sort of edges[0..count) by y0, ascending (gaps 1, 4, 13, ...),
 * through an 8-byte temporary on the $gp scratch area. */
void span_edges_sort(s32 count, SpanEdge *edges)
{
    SpanEdge *tmp = scratch_alloc(8);
    s32 gap;
    s32 h;
    s32 next;
    s32 i;
    s32 j;

    for (gap = 1; gap <= count / 9; gap = gap * 3 + 1)
        ;
    for (h = gap; h > 0; h = next) {
        next = div3_pos(h);
        for (i = h; i < count; i++) {
            edge_copy(tmp, &edges[i]);
            for (j = i - h; j >= 0; j -= h) {
                if (tmp->y0 >= edges[j].y0)
                    break;
                edge_copy(&edges[j + h], &edges[j]);
            }
            edge_copy(&edges[j + h], tmp);
        }
    }
    scratch_top -= 8;
}

void span_table_build(s32 arg0, s32 *src) {
    s16 *init;
    SpanTable *tbl;
    SpanEdge *edges;
    SpanEdge *e;
    s32 n;
    s32 y;
    s32 i;
    s32 j;
    s32 out;
    s32 start;
    s32 cur;
    s32 unused[2];

    init = (s16 *)heap_get_top();
    cur = (s32)(init + src[0] * 4);
    placement_angle_table = (s32)init;
    heap_set_top(cur);
    y = 0;
    if (src[0] > 0) {
        do {
            y++;
            init[0] = 0x4000;
            init[1] = 0x4000;
            init[2] = 0x4000;
            init += 4;
        } while (y < src[0]);
    }
    tbl = (SpanTable *)heap_get_top();
    wall_tables_ptr = (s32)tbl;
    tbl->arg0 = arg0;
    tbl->src = src;
    for (y = 255; y >= 0; y--) {
        tbl->line[y] = 0;
    }
    edges = arena_top();
    n = span_edges_build(src[0], src + 1, arg0 + 4, edges);
    span_edges_sort(n, edges);
    out = 0;
    i = 0;
    for (y = 0; y < 256; y++) {
        if (i >= n) {
            break;
        }
        start = out;
        for (j = i; j < n; j++) {
            e = &edges[j];
            if (y < e->y0) {
                break;
            }
            if (e->y1 >= y) {
                out++;
                tbl->data[out] = e->value;
            }
        }
        if (start < out) {
            cur = out - start;
            out++;
            tbl->line[y] = start + 1;
            tbl->data[start] = cur;
        }
        if (i < n) {
            for (e = (SpanEdge *)(i * 8 + (s32)edges); i < n; i++, e++) {
                if (y < e->y1) {
                    break;
                }
            }
        }
    }
    heap_set_top((s32)&tbl->data[out]);
    wall_query_cache = 0x80000000;
    d_801363F8 = 0x08000000;
    d_801363FC = 0x80000000;
    d_80136400 = -1;
}

s32 wall_quad_at(s32 x, s32 unused, s32 z)
{
    WallQuadTable *table = (WallQuadTable *)wall_tables_ptr;
    s32 *cache;
    s16 *list;
    s32 count;
    s32 idx;
    s32 *center;
    s32 *quad;
    s32 dx, dz, cross, hit, corner;
    s32 cz, cx;

    if (table == NULL) {
        return -1;
    }
    cache = &wall_query_cache;
    if (cache[0] == x && cache[2] == z) {
        return cache[3];
    }
    cache[3] = -1;
    cache[0] = x;
    cache[2] = z;
    idx = table->cells[(z >> 10) & 0xFF];
    if (idx == 0) {
        return -1;
    }
    list = (s16 *)((u8 *)table + (idx * 2 + 0x206));
    count = *list++;
    while (count > 0) {
        idx = *list++;
        center = (s32 *)((u8 *)table->centers + (idx * 8 + 4));
        cz = center[0];
        cx = center[1];
        quad = (s32 *)((u8 *)table->quads + ((cz & 0xFFF) * 16 + 4));
        cz >>= 12;
        cx >>= 12;
        do {
            dx = x - cx;
        } while (0);
        cz = z - cz;
        dz = cz;
        if (ABS(dz) > 0x7FFF) {
            hit = 0;
        } else if (ABS(dx) > 0x7FFF) {
            hit = 0;
        } else {
            register s32 high asm("$3") = dx << 16;
            s32 low = dz & 0xFFFF;
            s32 sxy = high | low;
            gte_set(SXY0, sxy);
            gte_load(SXY1, quad, 0);
            gte_load(SXY2, quad, 4);
            gte_nclip();
            corner = quad[3];
            gte_get(MAC0, cross);
            gte_set(SXY1, corner);
            if (cross > 0) {
                hit = 0;
            } else {
                gte_nclip_b();
                corner = quad[2];
                gte_get(MAC0, cross);
                gte_set(SXY2, corner);
                if (cross < 0) {
                    hit = 0;
                } else {
                    gte_nclip_b();
                    corner = quad[0];
                    gte_get(MAC0, cross);
                    gte_set(SXY1, corner);
                    if (cross > 0) {
                        hit = 0;
                    } else {
                        gte_nclip_b();
                        gte_get(MAC0, cross);
                        gte_nop();
                        hit = cross >= 0;
                    }
                }
            }
        }
        count--;
        if (hit) {
            cache[3] = idx;
            return idx;
        }
    }
    return -1;
}

s32 wall_segment_bisect(s32 *fromWords, s32 *toWords, s32 *outWords) {
    Point4 *from = (Point4 *)fromWords;
    Point4 *to = (Point4 *)toWords;
    Point4 *out = (Point4 *)outWords;
    s32 fromVal, toVal, i, dx, dz, ax, bx, az, bz;
    WallSegment *seg;

    *out = *to;
    fromVal = wall_quad_at(from->x, from->y, from->z);
    toVal = wall_quad_at(out->x, out->y, out->z);
    if (fromVal < 0 || toVal >= 0) {
        out->w = toVal;
        return 0;
    }
    seg = scratch_alloc(sizeof(WallSegment));
    seg->a = *from;
    seg->b = *out;
    seg->a.w = fromVal;
    for (i = 0; i < 16; i++) {
        bx = seg->b.x;
        ax = seg->a.x;
        bz = seg->b.z;
        az = seg->a.z;
        dx = bx - ax;
        dz = bz - az;
        if (abs(dx) > 0 || abs(dz) > 0) {
            out->x = (ax + bx) / 2;
            out->y = (seg->a.y + seg->b.y) / 2;
            out->z = (seg->a.z + seg->b.z) / 2;
            fromVal = wall_quad_at(out->x, out->y, out->z);
            if (toVal < 0) {
                seg->b = *out;
            } else {
                seg->a = *out;
                seg->a.w = fromVal;
            }
        } else {
            break;
        }
    }
    *out = seg->a;
    scratch_top -= sizeof(WallSegment);
    return 1;
}

/* Bisects the quad q->box (four packed (z, x) corners: two edges, 0->2 and 1->3) for the segment through
 * the point (z, x): each step takes the midpoints of both edges and keeps the half whose 2D cross product
 * (GTE nclip) with the point has the right sign, until |cross| < 0x100 or 12 steps. Writes the segment's
 * ends to q->a_z/a_x and q->b_z/b_x; returns the parameter in -0x1000..0x1000 along the edges. */
s32 wall_query_bisect(z, x, q)
s32 z;
s32 x;
WallQuery *q;
{
    s16 *corner = (s16 *)q->box;
    s16 first;
    s16 z1, z2, z3, x1, x2, x3;
    s32 minX, minZ;
    s32 lo, hi, mid, steps, cross;
    s32 edgeA0, edgeB0, edgeA1, edgeB1;
    s32 midA, midB;

    x1 = corner[3];
    first = CLAMP_HI(corner[1], x1);
    x2 = corner[5];
    minX = first;
    if (x2 < minX) minX = x2;
    x3 = corner[7];
    if (x3 < minX) minX = x3;
    z1 = corner[2];
    first = CLAMP_HI(corner[0], z1);
    z2 = corner[4];
    minZ = first;
    if (z2 < minZ) minZ = z2;
    z3 = corner[6];
    if (z3 < minZ) minZ = z3;

    /* Pack as screen coordinates relative to the box's minimum corner */
    z -= minZ;
    x -= minX;
    gte_set(SXY0, (x << 16) | (z & 0xFFFF));
    edgeB0 = ((x1 - minX) << 16) | ((z1 - minZ) & 0xFFFF);
    edgeA1 = ((x2 - minX) << 16) | ((z2 - minZ) & 0xFFFF);
    edgeB1 = ((x3 - minX) << 16) | ((z3 - minZ) & 0xFFFF);
    lo = -0x1000;
    hi = 0x1000;
    edgeA0 = ((corner[1] - minX) << 16) | ((corner[0] - minZ) & 0xFFFF);
    for (steps = 12; steps > 0; steps--) {
        mid = (lo + hi) / 2;
        midA = ((edgeA0 + edgeA1) >> 1) & 0x7FFF7FFF;
        midB = ((edgeB0 + edgeB1) >> 1) & 0x7FFF7FFF;
        gte_set(SXY1, midA);
        gte_set(SXY2, midB);
        gte_nclip();
        gte_get(MAC0, cross);
        gte_nop();
        if (ABS(cross) < 0x100) break;
        if (cross > 0) {
            lo = mid;
            edgeA0 = midA;
            edgeB0 = midB;
        } else {
            hi = mid;
            edgeA1 = midA;
            edgeB1 = midB;
        }
    }
    q->a_x = (midA >> 16) + minX;
    q->a_z = midA + minZ;
    q->b_x = (midB >> 16) + minX;
    q->b_z = midB + minZ;
    return mid;
}

/* Wall segment pos[3]: clamps pos into its box via wall_query_bisect, writes the normalised segment direction
 * to out[0..2] and the box angle to out[3]; returns wall_query_bisect's result. */
s32 wall_face_direction(s32 *pos, s16 *out) {
    WallTables *t = (WallTables *)wall_tables_ptr;
    WallQuery *query;
    s16 *dir;
    s32 *w;
    s32 *box;
    s16 *corner;
    s32 lo, hi;
    s32 px, pz;
    s32 dx, dz;
    s32 r;

    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    if (t != 0 && pos[3] >= 0) {
        query = scratch_alloc(0x18);
        dir = scratch_alloc(8);
        w = (s32 *)(t->offsets + (pos[3] * 8 + 4));
        lo = w[0];
        hi = w[1];
        pz = pos[2];
        px = pos[0];
        box = (s32 *)(t->boxes + ((lo & 0xFFF) * 16 + 4));
        lo >>= 12;
        hi >>= 12;
        query->box[0] = box[0];
        query->box[1] = box[2];
        query->box[2] = box[1];
        query->box[3] = box[3];
        r = wall_query_bisect(pz - lo, px - hi, query);
        dz = query->b_z - query->a_z;
        dx = query->b_x - query->a_x;
        dir[1] = 0;
        dir[0] = dx;
        dir[2] = dz;
        VectorNormalSS(dir, out);
        scratch_top -= 0x20;
        corner = (s16 *)box;
        out[3] = atan2((corner[4] + corner[6]) / 2 - (corner[0] + corner[2]) / 2,
                       (corner[5] + corner[7]) / 2 - (corner[1] + corner[3]) / 2);
        return r;
    }
}

s32 placement_angle(s32 index) {
    PlacementTables *l = (PlacementTables *)wall_tables_ptr;
    s16 *p;
    s32 off, off4;
    s32 ang;
    s32 a, b;

    if (l == 0 || index < 0) {
        return 0;
    }
    off = index * 8;
    ang = ((PlacementAngle *)(off + placement_angle_table))->angle;
    if (ang != 0x4000) {
        return ang;
    }
    off4 = off + 4;
    p = (s16 *)(l->shapes + ((*(u32 *)(l->links + off4) & 0xFFF) * 16 + 4));
    a = (p[4] + p[6]) / 2 - (p[0] + p[2]) / 2;
    b = (p[5] + p[7]) / 2 - (p[1] + p[3]) / 2;
    ang = atan2(a, b) & 0xFFF;
    ((PlacementAngle *)(off + placement_angle_table))->angle = ang;
    return ang;
}

/* Unit normal (x, z) of wall segment `index` at position t (-0x1000..0x1000 along it):
 * lerps both edges of its box and normalises the perpendicular of the difference. */
void wall_normal_at(s32 index, s32 t, s16 *out) {
    s32 tbl_or_y0 = wall_tables_ptr; /* the wall table, later reused for y0 */
    s16 *p;
    s32 *w;
    s32 x0, y1;
    s16 dx;

    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    if (tbl_or_y0 != 0 && index >= 0) {
        w = (s32 *)(((WallTables *)tbl_or_y0)->offsets + (index * 8 + 4));
        p = (s16 *)(((WallTables *)tbl_or_y0)->boxes + ((w[0] & 0xFFF) * 16 + 4));
        t = (t + 0x1000) / 2;
        x0 = LERP(p[0], p[2], t);
        tbl_or_y0 = LERP(p[1], p[3], t);
        index = LERP(p[4], p[6], t); /* x1 */
        y1 = LERP(p[5], p[7], t);
        y1 -= tbl_or_y0;
        dx = index - x0;
        out[0] = y1;
        out[1] = 0;
        out[2] = dx;
        VectorNormalSS(out, out);
    }
}

s32 wall_segment_query(s32 *pos, s32 *out_a, s32 *out_b) {
    WallTables *t = (WallTables *)wall_tables_ptr;
    s32 *w;
    s32 *box;
    WallQuery *scratch;
    s32 lo, hi;
    s32 r, px, pz;

    if (t != 0 && pos[3] >= 0) {
        scratch = scratch_alloc(0x18);
        px = pos[0];
        w = (s32 *)(t->offsets + (pos[3] * 8 + 4));
        lo = w[0];
        hi = w[1];
        box = (s32 *)(t->boxes + ((lo & 0xFFF) * 16 + 4));
        pz = pos[2];
        lo >>= 12;
        hi >>= 12;
        scratch->box[0] = box[2];
        scratch->box[1] = box[3];
        scratch->box[2] = box[0];
        scratch->box[3] = box[1];
        r = wall_query_bisect(pz - lo, px - hi, scratch, pos);
        out_a[0] = scratch->a_x;
        out_a[1] = 0;
        out_a[2] = scratch->a_z;
        out_b[0] = scratch->b_x;
        out_b[1] = 0;
        out_b[2] = scratch->b_z;
        out_a[0] += hi;
        out_a[2] += lo;
        out_b[0] += hi;
        out_b[2] += lo;
        scratch_top -= 0x18;
        return r;
    }
    return 0;
}

/* Searches the cells first..last of the wall table for an entry whose box corners (first or second pair,
 * by use_first) lie within 16 of (x0,y0) and (x1,y1); returns its id or -1. */
s32 cell_scan_boxes(s32 first, s32 last, s32 x0, s32 y0, s32 x1, s32 y1, s32 use_first) {
    WallTables *t = (WallTables *)wall_tables_ptr;
    u16 *cell;
    s16 *list;
    s32 count;
    s32 id;
    s32 *w;
    s32 lo, hi, slot;
    s16 *box;
    s32 dx, dy;

    if (t == 0) {
        return -1;
    }
    id = -1;
    if (first <= last) {
        cell = (u16 *)(first * 2 + (s32)t);
        do {
            id = cell[4];
            if (id == 0) {
                goto next;
            }
            list = (s16 *)((id * 2 + 0x206) + (u8 *)t);
            for (count = *list++; count > 0; count--) {
                id = *list++;
                w = (s32 *)(t->offsets + (id * 8 + 4));
                lo = w[0];
                hi = w[1];
                slot = lo & 0xFFF;
                lo >>= 12;
                hi >>= 12;
                box = (s16 *)(t->boxes + (slot * 16 + 4));
                if (use_first == 0) {
                    box += 4;
                }
                dx = box[0] + lo - x0;
                dy = box[1] + hi - y0;
                if (ABS(dy) > 16 || ABS(dx) > 16) {
                    continue;
                }
                dx = box[2] + lo - x1;
                dy = box[3] + hi - y1;
                if (ABS(dy) <= 16 && ABS(dx) <= 16) {
                    return id;
                }
            }
        next:
            first++;
            cell++;
        } while (first <= last);
        id = -1;
    }
    return id;
}

/* Calls cell_scan_boxes over the range of 1024-unit cells between a and c (cell numbers & 0xFF); when the
 * range wraps, first from the start cell up to 0xFF and, if that fails, from 0 to the end cell. */
s32 cell_range_test(s32 a, s32 b, s32 c, s32 d, s32 e) {
    s32 first = a;
    s32 last = c;

    if (last < a) {
        first = last;
        last = a;
    }
    first = (first >> 10) & 0xFF;
    last = (last >> 10) & 0xFF;
    if (last < first) {
        s32 result = cell_scan_boxes(first, 0xFF, a, b, c, d, e);

        if (result >= 0) {
            return result;
        }
        first = 0;
    }
    return cell_scan_boxes(first, last, a, b, c, d, e);
}

s32 placed_rect_query(s32 index) {
    PlacedRects *pr = (PlacedRects *)wall_tables_ptr;
    s32 off;
    s32 state;
    s32 *pos;
    s32 px, py;
    PlacedRect *r;

    if (pr == 0 || index < 0) {
        return -1;
    }
    off = index * 8;
    state = *(s16 *)((u8 *)(off + (s32)placement_angle_table) + 2);
    if (state != 0x4000) {
        return state;
    }
    pos = (s32 *)((u8 *)pr->placements + (off + 4));
    px = pos[0];
    py = pos[1];
    r = (PlacedRect *)((u8 *)pr->rects + ((px & 0xFFF) * 16 + 4));
    px >>= 12;
    py >>= 12;
    state = cell_range_test(r->x0 + px, r->y0 + py, r->x1 + px, r->y1 + py, 1);
    *(s16 *)((u8 *)(off + (s32)placement_angle_table) + 2) = state;
    return state;
}

s32 box_query(s32 idx) {
    WallTables *t = (WallTables *)wall_tables_ptr;
    s32 off;
    s32 cur;
    s32 *w;
    s32 lo, hi;
    s16 *box;

    if (t == 0 || idx < 0) {
        return -1;
    }
    off = idx * 8;
    cur = *(s16 *)(off + placement_angle_table);
    if (cur != 0x4000) {
        return cur;
    }
    w = (s32 *)(t->offsets + (off + 4));
    lo = w[0];
    hi = w[1];
    box = (s16 *)(t->boxes + ((lo & 0xFFF) * 16 + 4));
    lo >>= 12;
    hi >>= 12;
    cur = cell_range_test(box[0] + lo, box[1] + hi, box[2] + lo, box[3] + hi, 0);
    *(s16 *)(off + placement_angle_table) = cur;
    return cur;
}

/* Turns base (12-bit angle) by weight toward the placement angles of a and b (either may be -1): one
 * target blends linearly, two blend along a curve through both. Returns the new angle. */
s32 placement_angle_blend(s32 weight, s32 base, s32 a, s32 b) {
    s32 start_off;
    s32 delta;
    s32 divisor;
    s32 w;
    s32 d1;
    s32 acc;
    s32 quot;
    register s32 shift asm("$3"); /* local-alloc would give it v0, the quotient's register */

    if (a < 0) {
        if (b < 0) {
            return base & 0xFFF;
        }
        start_off = placement_angle(b);
        weight = -weight;
        goto clamp;
    } else if (b < 0) {
        start_off = placement_angle(a);
clamp:
        if (weight < 0) {
            weight = 0;
        }
    } else {
        weight = -weight;
        start_off = (placement_angle(a) - base) << 20 >> 20;
        d1 = (placement_angle(b) - base) << 20 >> 20;
        divisor = 0x2000;
        w = weight + 0x1000;
        acc = ((start_off + d1) << 15) / divisor * w;
        acc = (acc - (start_off << 16)) / divisor * w;
        quot = acc / 16;
        shift = start_off << 11;
        acc = quot + shift;
        delta = acc >> 12;
        goto done;
    }
    delta = ((start_off - base) << 20 >> 20) * weight / 8192;
done:
    do {
        base += delta;
    } while (0);
    return base & 0xFFF;
}

/* Resets a PartSlot: unk_00 = -1, unk_04 = 0. The caller's record kind is unconfirmed (PartSlot fits the offsets). */
void rec_reset(PartSlot *rec) {
    rec->unk_00 = -1;
    rec->wait_timer = 0;
}

void flow_sample(Flow *flow, s32 angle, s32 *sub, s32 *move, s16 *turn) {
    s32 prev_angle = flow->angle;
    s32 prev_state = flow->state;
    s32 rect;
    s32 box;
    s32 *probe = scratch_alloc(0x10);
    s32 *seg_a = scratch_alloc(0x10);
    s32 *seg_b = scratch_alloc(0x10);
    s16 *dir = scratch_alloc(8);
    s32 span;
    s32 half;
    s32 dist;
    s32 speed;
    s32 blend;
    s32 *move_z;
    s16 state;
    s32 px;
    s32 py;
    s32 pz;

    px = sub[0] >> 12;
    py = sub[1] >> 12;
    pz = sub[2] >> 12;
    state = wall_quad_at(px, py, pz);
    flow->state = state;
    rect = placed_rect_query(state);
    box = box_query(flow->state);
    flow->wall_direction = 0;
    move[0] = 0;
    move[1] = 0;
    move[2] = 0;
    *turn = 0;
    if (flow->state >= 0) {
        probe[0] = px;
        probe[1] = py;
        probe[2] = pz;
        probe[3] = flow->state;
        flow->wall_direction = wall_face_direction(probe, dir);
        blend = placement_angle_blend(wall_segment_query(probe, seg_a, seg_b), dir[3], box, rect);
        flow->angle = blend;
        if (prev_state < 0) {
            prev_angle = (s16)blend;
        }
        move_z = move + 2;
        *turn = blend - prev_angle;
        fly_move(flow->angle, flow->speed, move_z, move);
        span = angle * 3;
        half = angle * 2;
        dist = isqrt(length_sq(probe[0] - seg_a[0], 0, probe[2] - seg_a[2]));
        if (dist < span) {
            speed = ((span - dist) << 12) / half;
            if (speed > 0x1000) {
                speed = 0x1000;
            }
            fly_strafe(dir[3] - 0x400, (-speed * 0x30) / 4096, move_z, move);
        } else {
            dist = isqrt(length_sq(probe[0] - seg_b[0], 0, probe[2] - seg_b[2]));
            if (dist < span) {
                speed = ((span - dist) << 12) / half;
                if (speed > 0x1000) {
                    speed = 0x1000;
                }
                fly_strafe(dir[3] - 0x400, (speed * 0x30) / 4096, move_z, move);
            }
        }
    }
    scratch_top -= 0x38;
}

s32 limit_move(s32 *pos, s32 *move) {
    s32 *box = scratch_alloc(0x30);
    s32 *b = &box[4];
    s32 *c = &box[8];
    s32 x = pos[0];
    s32 y = pos[1];
    s32 z = pos[2];
    s32 r;

    box[0] = x >> 12;
    box[1] = y >> 12;
    box[2] = z >> 12;
    b[0] = x >> 12;
    b[1] = y >> 12;
    b[2] = (z + move[2]) >> 12;
    r = wall_segment_bisect(box, b, c);
    if (r != 0) {
        move[2] = (c[2] - box[2]) << 12;
    }
    b[0] = (x + move[0]) >> 12;
    b[1] = y >> 12;
    b[2] = c[2];
    if (wall_segment_bisect(c, b, box) != 0) {
        move[0] = (box[2] - c[2]) << 12;
        r = 1;
    }
    scratch_top -= 0x30;
    return r;
}

/* Transforms the vector at in by the GTE rotation matrix and translation into out, and returns out (same code as transform_point). */
VECTOR *rotate_point_inverse(VECTOR *in, VECTOR *out) {
    gte_load(IR1, in, 0);
    gte_load(IR2, in, 4);
    gte_load(IR3, in, 8);
    gte_rtirtr();
    gte_store(MAC1, out, 0);
    gte_store(MAC2, out, 4);
    gte_store(MAC3, out, 8);
    return out;
}

void anim_track_sample(s32 t, s32 n, TrackKey *keys, s32 *out) {
    TrackKey *k;
    s32 lo, hi, i, span, dt; /* i: search midpoint, then component */
    s32 a, b;

    if (n < 2 || t <= keys[0].t) {
        out[0] = keys[0].v[0];
        out[1] = keys[0].v[1];
        out[2] = keys[0].v[2];
        return;
    }
    if (t >= keys[n - 1].t) {
        out[0] = keys[n - 1].v[0];
        out[1] = keys[n - 1].v[1];
        out[2] = keys[n - 1].v[2];
        return;
    }
    if (n == 2) {
        lo = 0;
    } else {
        hi = n - 1;
        lo = 0;
        while (lo < hi) {
            i = (lo + hi) >> 1;
            if (keys[i].t < t) {
                lo = i + 1;
            } else {
                hi = i;
            }
        }
        if (lo > 0) {
            lo--;
        }
        if (t >= (keys[lo].t + keys[lo + 1].t) / 2) {
            lo++;
        }
        if (lo != 0) {
            if (lo == n - 1) {
                lo = n - 2;
            } else {
                span = keys[lo + 1].t - keys[lo - 1].t;
                dt = t * 2 - (keys[lo].t + keys[lo - 1].t);
                k = &keys[lo];
                for (i = 0; i < 3; i++) {
                    a = k[-1].v[i];
                    b = k[0].v[i];
                    out[i] = ((((a + k[1].v[i] - b * 2) << 15) / span * dt + ((b - a) << 16)) / span * dt) / 65536 + (a + b) / 2;
                }
                return;
            }
        }
    }
    span = keys[lo + 1].t - keys[lo].t;
    dt = t - keys[lo].t;
    k = &keys[lo];
    for (i = 0; i < 3; i++) {
        out[i] = (k[1].v[i] - k[0].v[i]) * dt / span + k[0].v[i];
    }
}

void add_d_80136404(s32 turn) {
    s32 *p = &cam_state;

    FAKE_OPAQUE(p);
    *p += turn << 12;
}
