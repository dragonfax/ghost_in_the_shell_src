#ifndef STARTUP_TYPES_H
#define STARTUP_TYPES_H

/* startup's types (main.c's code, data.c and bss.c include this; types only, so the data files can include
 * it without main.c's declarations of the objects they define). */

#include "common.h"

typedef struct Rect {
    s16 x, y, w, h;
} Rect;

typedef struct PrimTag {
    u32 addr : 24;
    u32 len : 8;
} PrimTag;

typedef struct PolyFT4 {
    PrimTag tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad2;
} PolyFT4;

typedef struct PolyG4 {
    PrimTag tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, pad1;
    s16 x1, y1;
    u8 r2, g2, b2, pad2;
    s16 x2, y2;
    u8 r3, g3, b3, pad3;
    s16 x3, y3;
} PolyG4;

typedef struct Tile {
    PrimTag tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 w, h;
} Tile;

typedef struct DrawEnv {
    Rect clip;
    s16 ofs[2];
    Rect tw;
    u16 tpage;
    u8 dtd;
    u8 dfe;
    u8 isbg;
    u8 r0, g0, b0;
    u32 dr_env[16];
} DrawEnv;

typedef struct DispEnv {
    Rect disp;
    Rect screen;
    u8 isinter;
    u8 isrgb24;
    u8 pad0, pad1;
} DispEnv;

typedef struct StartupScreen {
    s32 count;
    PolyFT4 polys[8];
    Tile tile;
    PolyG4 grey;
    u8 pad_178[0x14];
    DrawEnv draw;
    DispEnv disp;
    PrimTag ot[2];
} StartupScreen;

#endif
