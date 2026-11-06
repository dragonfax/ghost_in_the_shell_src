/* vec_from_polar: one of s12's own original source files (scripts/objmap.py); part of src/s12/main.c's unit, included there. */

void vec_from_polar(SVECTOR *out, s32 radius, s32 angle) {
    s32 idx = (angle & 0xFFF) * 4;
    s32 z, x;
    z = radius * ((s16 *)((u8 *)cos_table + idx))[0];
    z /= 0x1000;
    x = radius * ((s16 *)((u8 *)rcossin_tbl + idx))[0];
    x /= 0x1000;
    out->vx = x;
    out->vy = 0;
    out->vz = z;
}
