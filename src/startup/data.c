/* startup data 0x800ECF30-0x800EE800: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "startup_types.h"

extern void _addque();
extern void _addque2();
extern void _clr();
extern void _ctl();
extern void _cwb();
extern void _cwc();
extern void _drs();
extern void _dws();
extern void _exeque();
extern void _getctl();
extern void _otc();
extern void _param();
extern void _reset();
extern void _status();
extern void _sync();
extern void printf();
extern void restartIntr();
extern void setIntr();
extern void startIntr();
extern void stopIntr();
extern u8 D_800EE1BC[];
extern u8 D_800EE344[];
extern u8 D_800EE35F[];
extern u8 D_800EE3AA[];
extern u8 D_800EE3B0[];
extern u8 D_800EE3B1[];
extern u8 D_800EE3B2[];
extern u8 D_800EE3B4[];
extern u8 startup_draw_dfe[];
extern u8 startup_draw_dtd[];
extern u8 startup_draw_g0[];
extern u8 startup_draw_isbg[];
extern u8 startup_draw_r0[];
extern u8 startup_draw_tpage[];
extern u8 startup_grey_v0_b[];
extern u8 startup_grey_v0_g[];
extern u8 startup_grey_v0_r[];
extern u8 startup_grey_v1_b[];
extern u8 startup_grey_v1_g[];
extern u8 startup_grey_v1_r[];
extern u8 startup_grey_v2_b[];
extern u8 startup_grey_v2_g[];
extern u8 startup_grey_v2_r[];
extern u8 startup_grey_v3_b[];
extern u8 startup_grey_v3_g[];
extern u8 startup_grey_v3_r[];
extern s32 D_800ECF30;
extern u32 D_800ECF34[];
extern u32 D_800ECF3C[];
extern u32 D_800ECF7C;
extern u32 GPU_printf;
extern u8 D_800ECF84;
extern u8 D_800ECF85;
extern u8 gpu_graph_debug;
extern u8 gpu_graph_reverse;
extern u16 D_800ECF88;
extern u16 D_800ECF8A;
extern u32 D_800ECF8C;
extern u32 gpu_draw_sync_callback;
extern u32 gpu_draw_env[];
extern u16 D_800ECFF0;
extern u16 D_800ECFF2;
extern u16 D_800ECFF4;
extern u16 D_800ECFF6;
extern u16 D_800ECFF8;
extern u16 D_800ECFFA;
extern u16 D_800ECFFC;
extern u16 D_800ECFFE;
extern u32 D_800ED000;
extern u16 D_800ED004[];
extern u16 D_800ED018[];
extern u32 D_800ED034;
extern u32 D_800ED038;
extern u32 D_800ED03C;
extern u32 D_800ED040[];
extern u32 gpu_gp0_port;
extern u32 gpu_gp1_port;
extern u32 D_800ED05C;
extern u32 D_800ED060;
extern u32 D_800ED064;
extern u32 D_800ED068;
extern u32 D_800ED06C;
extern u32 dma_otc_chcr;
extern u32 dma_control;
extern u32 _qlog;
extern u32 D_800ED07C;
extern u32 D_800ED080[];
extern u32 _qin;
extern u32 _qout;
extern u32 D_800ED090;
extern u32 D_800ED094;
extern u32 D_800ED098;
extern u32 D_800ED09C;
extern u32 D_800ED0A0[];
extern u32 D_800ED0AC;
extern u32 D_800ED0B0;
extern u32 Hcount;
extern u32 D_800ED0B8;
extern u16 D_800ED0BC;
extern u16 D_800ED0BE;
extern u32 D_800ED0C0[];
extern u16 D_800ED0EC;
extern u16 D_800ED0EE;
extern u32 D_800ED0F0[];
extern u32 D_800ED0F8[];
extern u32 D_800EE124[];
extern u32 D_800EE144;
extern u32 D_800EE148;
extern u32 D_800EE14C;
extern u32 D_800EE150;
extern u32 D_800EE154;
extern u32 D_800EE158[];
extern u32 Vcount;
extern u32 D_800EE17C;
extern u32 D_800EE180;
extern u32 D_800EE184[];
extern u32 D_800EE1A4;
extern s32 D_800EE1A8;
extern s32 startup_frame_count;
extern s32 D_800EE1B0;
extern s32 startup_screen_index;
extern StartupScreen startup_screen;
extern u32 D_800EE3BC;
extern u32 D_800EE3C0;
extern u32 D_800EE3C4;
extern u32 D_800EE3C8;
extern u32 D_800EE3CC;
extern u32 D_800EE3D0;
extern u32 D_800EE3D4;
extern u32 D_800EE3D8;
extern u32 D_800EE3DC;
extern u32 D_800EE3E0;
extern u32 D_800EE3E4;
extern u32 D_800EE3E8;
extern u32 D_800EE3EC[];
extern u8 ctlbuf[];
extern u32 D_800EE500;
extern u32 D_800EE504;
extern u32 D_800EE508;
extern u32 D_800EE50C[];

s32 D_800ECF30 = -1;

u32 D_800ECF34[2] = {
    0x0A077350, 0x1036D61A,
};

u32 D_800ECF3C[16] = {
    0x800E8094, (u32)_addque, (u32)_addque2, (u32)_clr, (u32)_ctl, (u32)_cwb,
    (u32)_cwc, (u32)_drs, (u32)_dws, (u32)_exeque, (u32)_getctl, (u32)_otc,
    (u32)_param, (u32)_reset, (u32)_status, (u32)_sync,
};

u32 D_800ECF7C = (u32)D_800ECF3C;

u32 GPU_printf = (u32)printf;

u8 D_800ECF84 = 0x00;

u8 D_800ECF85 = 0x00;

u8 gpu_graph_debug = 0x00;

u8 gpu_graph_reverse = 0x00;

u16 D_800ECF88 = 0x0000;

u16 D_800ECF8A = 0x0000;

u32 D_800ECF8C = 0x00000000;

u32 gpu_draw_sync_callback = 0x00000000;

u32 gpu_draw_env[23] = {0};

u16 D_800ECFF0 = 0x0000;

u16 D_800ECFF2 = 0x0000;

u16 D_800ECFF4 = 0x0000;

u16 D_800ECFF6 = 0x0000;

u16 D_800ECFF8 = 0x0000;

u16 D_800ECFFA = 0x0000;

u16 D_800ECFFC = 0x0000;

u16 D_800ECFFE = 0x0000;

u32 D_800ED000 = 0x00000000;

u16 D_800ED004[10] = {
    0x0400, 0x0000, 0x0400, 0x0000, 0x0400, 0x0000, 0x0400, 0x0000,
    0x0400, 0x0000,
};

u16 D_800ED018[14] = {
    0x0200, 0x0000, 0x0400, 0x0000, 0x0400, 0x0000, 0x0200, 0x0000,
    0x0400, 0x0000, 0xFFFF, 0x04FF, 0x0000, 0x8000,
};

u32 D_800ED034 = 0x00000000;

u32 D_800ED038 = 0x00000000;

u32 D_800ED03C = 0x00000000;

u32 D_800ED040[5] = {
    0x04FFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

u32 gpu_gp0_port = 0x1F801810;

u32 gpu_gp1_port = 0x1F801814;

u32 D_800ED05C = 0x1F8010A0;

u32 D_800ED060 = 0x1F8010A4;

u32 D_800ED064 = 0x1F8010A8;

u32 D_800ED068 = 0x1F8010E0;

u32 D_800ED06C = 0x1F8010E4;

u32 dma_otc_chcr = 0x1F8010E8;

u32 dma_control = 0x1F8010F0;

u32 _qlog = 0x00000000;

u32 D_800ED07C = 0x00000000;

u32 D_800ED080[2] = {
    0x00000000, 0x00000000,
};

u32 _qin = 0x00000000;

u32 _qout = 0x00000000;

u32 D_800ED090 = 0x00000000;

u32 D_800ED094 = 0x00000000;

u32 D_800ED098 = 0x00000000;

u32 D_800ED09C = 0x00000000;

u32 D_800ED0A0[3] = {
    0x00000000, 0x0A067350, 0x1036D51A,
};

u32 D_800ED0AC = 0x1F801814;

u32 D_800ED0B0 = 0x1F801110;

u32 Hcount = 0x00000000;

u32 D_800ED0B8 = 0x00000000;

u16 D_800ED0BC = 0x0000;

u16 D_800ED0BE = 0x0000;

u32 D_800ED0C0[11] = {0};

u16 D_800ED0EC = 0x0000;

u16 D_800ED0EE = 0x0000;

u32 D_800ED0F0[2] = {
    0x00000000, 0x00000000,
};

u32 D_800ED0F8[1035] = {0};

u32 D_800EE124[8] = {
    0x800E82D8, 0x00000000, (u32)setIntr, (u32)startIntr, (u32)stopIntr, 0x00000000,
    (u32)restartIntr, (u32)&D_800ED0BC,
};

u32 D_800EE144 = (u32)D_800EE124;

u32 D_800EE148 = 0x1F801070;

u32 D_800EE14C = 0x1F801074;

u32 D_800EE150 = 0x1F8010F0;

u32 D_800EE154 = 0x00000000;

u32 D_800EE158[8] = {0};

u32 Vcount = 0x00000000;

u32 D_800EE17C = 0x1F801114;

u32 D_800EE180 = 0x1F8010F4;

u32 D_800EE184[8] = {0};

u32 D_800EE1A4 = 0x1F801080;

s32 D_800EE1A8 = 0;

s32 startup_frame_count = 0;

s32 D_800EE1B0 = 0;

s32 startup_screen_index = 0;

StartupScreen startup_screen = {0};

u32 D_800EE3BC = 0x00000000;

u32 D_800EE3C0 = 0x00000000;

u32 D_800EE3C4 = 0x00000000;

u32 D_800EE3C8 = 0x00000000;

u32 D_800EE3CC = 0x00000000;

u32 D_800EE3D0 = 0x00000000;

u32 D_800EE3D4 = 0x00000000;

u32 D_800EE3D8 = 0x00000000;

u32 D_800EE3DC = 0x00000000;

u32 D_800EE3E0 = 0x00000000;

u32 D_800EE3E4 = 0x00000000;

u32 D_800EE3E8 = 0x00000000;

u32 D_800EE3EC[5] = {0};

u8 ctlbuf[256] = {0};

u32 D_800EE500 = 0x00000000;

u32 D_800EE504 = 0x00000000;

u32 D_800EE508 = 0x00000000;

u32 D_800EE50C[189] = {0};

/* labels inside the objects above */
__asm__(".globl startup_grey_v0_b\n.set startup_grey_v0_b, startup_screen+0x15A\n"
        ".globl startup_grey_v1_b\n.set startup_grey_v1_b, startup_screen+0x162\n"
        ".globl startup_grey_v2_b\n.set startup_grey_v2_b, startup_screen+0x16A\n"
        ".globl startup_grey_v3_b\n.set startup_grey_v3_b, startup_screen+0x172\n"
        ".globl D_800EE35F\n.set D_800EE35F, startup_screen+0x1A7\n"
        ".globl D_800EE3AA\n.set D_800EE3AA, startup_screen+0x1F2\n"
        ".globl startup_grey_v0_g\n.set startup_grey_v0_g, startup_screen+0x159\n"
        ".globl startup_grey_v1_g\n.set startup_grey_v1_g, startup_screen+0x161\n"
        ".globl startup_grey_v2_g\n.set startup_grey_v2_g, startup_screen+0x169\n"
        ".globl startup_grey_v3_g\n.set startup_grey_v3_g, startup_screen+0x171\n"
        ".globl startup_draw_g0\n.set startup_draw_g0, startup_screen+0x1A6\n"
        ".globl startup_draw_r0\n.set startup_draw_r0, startup_screen+0x1A5\n"
        ".globl D_800EE1BC\n.set D_800EE1BC, startup_screen+0x4\n"
        ".globl startup_grey_v0_r\n.set startup_grey_v0_r, startup_screen+0x158\n"
        ".globl startup_grey_v1_r\n.set startup_grey_v1_r, startup_screen+0x160\n"
        ".globl startup_grey_v2_r\n.set startup_grey_v2_r, startup_screen+0x168\n"
        ".globl startup_grey_v3_r\n.set startup_grey_v3_r, startup_screen+0x170\n"
        ".globl D_800EE344\n.set D_800EE344, startup_screen+0x18C\n"
        ".globl startup_draw_tpage\n.set startup_draw_tpage, startup_screen+0x1A0\n"
        ".globl startup_draw_dtd\n.set startup_draw_dtd, startup_screen+0x1A2\n"
        ".globl startup_draw_dfe\n.set startup_draw_dfe, startup_screen+0x1A3\n"
        ".globl startup_draw_isbg\n.set startup_draw_isbg, startup_screen+0x1A4\n"
        ".globl D_800EE3B0\n.set D_800EE3B0, startup_screen+0x1F8\n"
        ".globl D_800EE3B1\n.set D_800EE3B1, startup_screen+0x1F9\n"
        ".globl D_800EE3B2\n.set D_800EE3B2, startup_screen+0x1FA\n"
        ".globl D_800EE3B4\n.set D_800EE3B4, startup_screen+0x1FC\n");
