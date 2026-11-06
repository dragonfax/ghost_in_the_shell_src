#ifndef COMMON_H
#define COMMON_H

typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

#ifndef NULL
#define NULL ((void *)0)
#endif

/* FAKE: hides a pointer's value from GCC's CSE, emitting no code. The original often keeps a global's
 * address in a register and uses field offsets (docs/FINDINGS.md "base register" pattern); GCC folds a
 * plain `p = &global` back into each access. The real source construct is unknown, so code using this
 * matches but isn't what the developers wrote. */
#define FAKE_OPAQUE(x) __asm__("" : "=r"(x) : "0"(x))

/* FAKE: FAKE_OPAQUE as a volatile asm: CSE never merges two of them, so each use rebuilds the address
 * (`lui/addiu` per id_table push in hud_frame_draw), and it is a scheduling barrier like SCHED_BARRIER. */
#define FAKE_OPAQUE_VOLATILE(x) __asm__ volatile("" : "=r"(x) : "0"(x))

/* FAKE: dst = src (a value or a constant) as one set that CSE can't see through, emitting only the move or
 * li reload makes for it. Unlike `dst = src; FAKE_OPAQUE(dst);` dst is set once (sched1's birthing boost,
 * and two refs fewer in global-alloc's priority). sound_play_note. */
#define OPAQUE_COPY(dst, src) __asm__("" : "=r"(dst) : "0"(src))

/* FAKE: an empty volatile asm, which cc1's scheduler treats as using and clobbering every register and all
 * of memory: nothing moves across it, so the statements on each side keep their C order (title
 * title_project_verts_offset's prologue: loads first, then the mask's lui/ori). The real source construct is unknown. */
#define SCHED_BARRIER() __asm__ volatile("")

/* FAKE: a use of x that emits no code, so x stays live up to here: combine keeps a copy it would fold into
 * a call argument, and a variable's lifetime overlaps a later temp (title title_memcard_update; FINDINGS "Keeping a
 * copy into an argument"). The original's reason for the liveness is unknown. */
#define FAKE_USE(x) __asm__("" : : "r"(x))

/* An OT entry's or primitive tag's 24-bit link: lwl/swl at byte 2 move its three low bytes as the high bytes of a
 * register (link = tag << 8), leaving the tag's length byte alone. */
#define ot_link_load(link, p) __asm__ volatile("lwl %0, 2(%1)" : "=r"(link) : "r"(p))
#define ot_link_store(p, link) __asm__ volatile("swl %0, 2(%1)" : : "r"(link), "r"(p))
/* ot_link_store with a memory clobber (later loads stay after it: text_put_char) */
#define ot_link_store_mem(p, link) __asm__ volatile("swl %0, 2(%1)" : : "r"(link), "r"(p) : "memory")

/* PsyQ addPrim: links primitive p in front of OT entry ot (the low 24 bits of each word are the link). The
 * original copies the link with unaligned 3-byte loads/stores (lwl/swl), which no C spelling produces; the
 * shift between them is the compiler's, so this is three asm statements around it. A statement expression,
 * not do/while(0): the loop notes of a do/while double the ref counts local-alloc ranks registers by. */
#define addPrim(ot, p) ({                                                   \
        u32 link_, self_;                                                  \
        ot_link_load(link_, ot);                                           \
        self_ = (u32)(p) << 8;                                             \
        ot_link_store(p, link_);                                           \
        ot_link_store(ot, self_);                                          \
    })

/* PsyQ addPrims: links the primitive chain p0..p1 in front of OT entry ot (p1 takes ot's old link, ot then
 * points at p0), with the same lwl/swl link copies as addPrim (mask_layers_draw). */
#define addPrims(ot, p0, p1) ({                                             \
        u8 *last_ = (u8 *)(p1);                                            \
        u32 link_, self_;                                                  \
        ot_link_load(link_, ot);                                           \
        self_ = (u32)(p0) << 8;                                            \
        ot_link_store(last_, link_);                                       \
        ot_link_store(ot, self_);                                          \
    })

/* addPrim that evaluates p once into a copy (so `addPrimOnce(ot, p++)` works); the copy is the original's
 * `addu v1,p,zero` before the lwl, and loop.c strength-reduces the self word (light_backdrop_strip_draw). */
#define addPrimOnce(ot, p) ({                                               \
        u8 *p_ = (u8 *)(p);                                                \
        u32 link_, self_;                                                  \
        ot_link_load(link_, ot);                                           \
        self_ = (u32)p_ << 8;                                              \
        ot_link_store(p_, link_);                                          \
        ot_link_store(ot, self_);                                          \
    })

/* addPrim with the link and self words pinned to $a0/$a1, where the original has them and the allocator
 * would pick others (title title_menu_quad_draw). */
#define addPrimA0A1(ot, p) ({                                               \
        u8 *ot_ = (u8 *)(ot);                                              \
        u8 *p_ = (u8 *)(p);                                                \
        register u32 link_ asm("$4");                                      \
        register u32 self_ asm("$5");                                      \
        __asm__ volatile("lwl %0, 2(%1)" : "=r"(link_) : "r"(ot_));        \
        self_ = (u32)p_ << 8;                                              \
        __asm__ volatile("swl %0, 2(%1)" : : "r"(link_), "r"(p_));         \
        __asm__ volatile("swl %0, 2(%1)" : : "r"(self_), "r"(ot_));        \
    })

/* PsyQ getTPage(tp, abr, x, y) the way its asm macro computes it at run time, in $at and $v0, even when
 * every argument is a constant (loader loader_draw_rect). */
#define getTPageAsm(out, tp, abr, x, y)                                     \
    __asm__ volatile(".set noat\n"                                         \
            "sll $at,%1,7\n"                                               \
            "andi $v0,$at,0x180\n"                                         \
            "sll $at,%2,5\n"                                               \
            "andi $at,$at,0x60\n"                                          \
            "or $v0,$v0,$at\n"                                             \
            "andi $at,%4,0x100\n"                                          \
            "srl $at,$at,4\n"                                              \
            "or $v0,$v0,$at\n"                                             \
            "andi $at,%3,0x3C0\n"                                          \
            "srl $at,$at,6\n"                                              \
            "or %0,$v0,$at\n"                                              \
            ".set at"                                                      \
            : "=r"(out)                                                    \
            : "r"(tp), "r"(abr), "r"(x), "r"(y) : "$2")

/* Writes the low 24 bits of v as the link of primitive p (a lone swl; -0x100 ends the list: text_flip). */
#define TERM_LINK(p, v) ot_link_store(p, v)

/* GP0(E2h) texture window word for a window at (x, y), w by h pixels, as PsyQ's _get_tw builds it (title sprite_sets_register). */
#define getTexWindow(x, y, w, h)                                            \
    (0xE2000000 | ((((y) & 0xFF) >> 3) << 15) | ((((x) & 0xFF) >> 3) << 10) | \
     ((((-(h)) & 0xFF) >> 3) << 5) | (((-(w)) & 0xFF) >> 3))

/* getTPageAsm as an expression: the result in $v1, copied out by the compiler (loader loader_draw_vram_rect). */
#define getTPageV1(tp, abr, x, y) ({ register s32 tpage_ asm("$3"); getTPageAsm(tpage_, tp, abr, x, y); tpage_; })

/* PsyQ setPolyFT4 the way its asm macro writes it: len 9 and code 0x2C, each through $at (loader loader_draw_vram_rect). */
#define setPolyFT4Asm(p)                                                    \
    __asm__ volatile(".set noat\n"                                         \
            "ori $at,$zero,0x9\n"                                          \
            "sb $at,3(%0)\n"                                               \
            "ori $at,$zero,0x2C\n"                                         \
            "sb $at,7(%0)\n"                                               \
            ".set at" : : "r"(p))

/* Writes the r, g, b bytes of primitive p from the top 3 bytes of c with one unaligned store (loader loader_draw_vram_rect). */
#define setRGBWord(p, c) __asm__ volatile("swl %0, 2(%1)" : : "r"(c), "r"((u8 *)(p) + 4))

/* Hand-written loop: adds 0x1000 to x until it is not negative, the add in the branch's delay slot (so it runs
 * once more on exit, no compensating subtract: GCC's reorg can't emit this; pose_list_intpl). */
#define ANGLE_WRAP_UP(x) \
    __asm__ volatile(".set\tnoreorder\n1:\tbltz %0, 1b\n\taddiu %0, %0, 0x1000\n\t.set\treorder" : "=r"(x) : "0"(x))

/* A node of a doubly linked list; lists run between a head and a tail sentinel node. */
typedef struct Node {
    struct Node *next;
    struct Node *prev;
} Node;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

/* $gp is the scratchpad allocator: functions take memory from it and give it back. The original's
 * `addu v1,gp,zero; addiu gp,gp,N` is this register variable, not hand-written code. */
register u8 *scratch_top asm("$28");

/* One word pushed on / popped off the $gp stack (pchr_lists_build's depth-first walk). */
#define scratch_push(x) (*(void **)scratch_top = (void *)(x), scratch_top += 4)
#define scratch_pop(x) ((x) = ((void **)scratch_top)[-1], scratch_top -= 4)

/* PsyQ libgpu's frame buffer rectangle. */
typedef struct RECT {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} RECT;

/* A frame buffer rectangle the code reads unsigned (lhu): rodata VRAM rects (the mask buffer, night vision). */
typedef struct RectU {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} RectU;

/* A record the boot exe's slot_resource_entry service returns: the path is at 0x04 (get_exec_path). */
typedef struct ResourceEntry {
    s32 unk_00;
    u8 *path;
} ResourceEntry;

#include "include_asm.h"
#include "gte.h" /* GTE macros for every binary (only macros) */
#include "mips.h" /* CPU instruction idioms (only macros) */
#include "incbin.h" /* INCBIN: data objects from asset files */

/* The boot exe's service table and the message printed when its BIOS version check fails. */
#define SVC_TABLE ((void **)0x80010000)
#define BIOS_VERSION_ERROR "BIOS:Version Error.\r"

#endif
