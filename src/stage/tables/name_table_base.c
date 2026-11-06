/* name_table_base: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

s32 table_curve_eval(s32 x, s32 n, s32 *xs, u8 *table_entry) {
    s32 *ys = (s32 *)table_entry;
    s32 i, hi, mid, dx, d, curve, frac, base;
    s32 unused[2];

    if (n < 2 || xs[0] >= x) { return ys[0] << 12; }
    if (x >= xs[n - 1]) { return ys[n - 1] << 12; }
    hi = n - 1;
    if (n == 2) {
        i = 0;
        goto linear;
    }
    i = 0;
    if (hi > 0) {
        do {
            mid = (i + hi) >> 1;
            if (xs[mid] < x) { i = mid + 1; } else { hi = mid; }
        } while (i < hi);
    }
    if (i > 0) { i--; }
    if (x >= (xs[i] + xs[i + 1]) / 2) { i++; }
    if (i == 0) goto linear;
    if (i == n - 1) {
        i = n - 2;
        goto linear;
    }
    dx = xs[i + 1] - xs[i - 1];
    d = 2 * x - (xs[i] + xs[i - 1]);
    curve = ((ys[i - 1] + ys[i + 1] - 2 * ys[i]) << 15) / dx;
    frac = ((curve * d + ((ys[i] - ys[i - 1]) << 16)) / dx) * d;
    frac /= 16;
    base = (ys[i - 1] + ys[i]) << 11;
    return frac + base;
linear:
    {
        register s32 dist asm("$4");
        s32 x1 = xs[i + 1];
        register s32 x0 asm("$5") = xs[i];
        s32 slope;
        dx = x1 - x0;
        slope = ((ys[i + 1] - ys[i]) << 16) / dx;
        dist = x - x0;
        return (slope * dist) / 16 + (ys[i] << 12);
    }
}
