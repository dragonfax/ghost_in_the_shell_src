#ifndef GTE_H
#define GTE_H

/* GTE (geometry coprocessor, COP2).
 *
 * Commands and PsyQ's grouped transfers come from gte_psyq.h (generated from PsyQ 3.6 INLINE_C.H): gte_rtps(),
 * gte_rtir_sf0(), gte_nclip(), gte_ldv0(p), gte_stsxy(p), gte_stlvnl(p), gte_SetRotMatrix(m), ... A command
 * gte_<name>() pads with two nops, gte_<name>_b() with none, gte_nop(); gte_<name>_b() with one; the original
 * usually has two instructions between the last GTE register load and a command, sometimes fewer (FINDINGS "GTE macros").
 *
 * Single registers, by name, one instruction per statement (GCC may schedule C code between them):
 *   gte_set(IR1, x)          x -> data register          (mtc2)
 *   gte_get(MAC1, x)         data register -> x          (mfc2)
 *   gte_load(IR1, p, 4)      the word at p + 4 -> data register   (lwc2)
 *   gte_store(MAC1, p, 0)    data register -> the word at p + 0   (swc2)
 *   gte_set_ctrl(TRX, x)     x -> control register       (ctc2)
 *   gte_get_ctrl(FLAG, x)    control register -> x       (cfc2)
 */

#include "gte_psyq.h"

/* Data registers */
#define GTE_R_VXY0 0
#define GTE_R_VZ0 1
#define GTE_R_VXY1 2
#define GTE_R_VZ1 3
#define GTE_R_VXY2 4
#define GTE_R_VZ2 5
#define GTE_R_RGB 6
#define GTE_R_OTZ 7
#define GTE_R_IR0 8
#define GTE_R_IR1 9
#define GTE_R_IR2 10
#define GTE_R_IR3 11
#define GTE_R_SXY0 12
#define GTE_R_SXY1 13
#define GTE_R_SXY2 14
#define GTE_R_SXYP 15
#define GTE_R_SZ0 16
#define GTE_R_SZ1 17
#define GTE_R_SZ2 18
#define GTE_R_SZ3 19
#define GTE_R_RGB0 20
#define GTE_R_RGB1 21
#define GTE_R_RGB2 22
#define GTE_R_RES1 23
#define GTE_R_MAC0 24
#define GTE_R_MAC1 25
#define GTE_R_MAC2 26
#define GTE_R_MAC3 27
#define GTE_R_IRGB 28
#define GTE_R_ORGB 29
#define GTE_R_LZCS 30
#define GTE_R_LZCR 31

/* Control registers: rotation matrix (R11R12 .. R33), translation, light matrix, back colour, light colour
 * matrix, far colour, screen offset and distance, depth cue, Z scale factors, FLAG. */
#define GTE_R_R11R12 0
#define GTE_R_R13R21 1
#define GTE_R_R22R23 2
#define GTE_R_R31R32 3
#define GTE_R_R33 4
#define GTE_R_TRX 5
#define GTE_R_TRY 6
#define GTE_R_TRZ 7
#define GTE_R_L11L12 8
#define GTE_R_L13L21 9
#define GTE_R_L22L23 10
#define GTE_R_L31L32 11
#define GTE_R_L33 12
#define GTE_R_RBK 13
#define GTE_R_GBK 14
#define GTE_R_BBK 15
#define GTE_R_LR1LR2 16
#define GTE_R_LR3LG1 17
#define GTE_R_LG2LG3 18
#define GTE_R_LB1LB2 19
#define GTE_R_LB3 20
#define GTE_R_RFC 21
#define GTE_R_GFC 22
#define GTE_R_BFC 23
#define GTE_R_OFX 24
#define GTE_R_OFY 25
#define GTE_R_H 26
#define GTE_R_DQA 27
#define GTE_R_DQB 28
#define GTE_R_ZSF3 29
#define GTE_R_ZSF4 30
#define GTE_R_FLAG 31

#define GTE_STR_(x) #x
#define GTE_REG(name) GTE_STR_(name)

#define gte_set(reg, val) __asm__ volatile("mtc2 %z0, $" GTE_REG(GTE_R_##reg) : : "rJ"(val))
#define gte_get(reg, var) __asm__ volatile("mfc2 %0, $" GTE_REG(GTE_R_##reg) : "=r"(var))
/* gte_set with val always in a register: a constant 0 goes through a loaded register, not $zero */
#define gte_set_r(reg, val) __asm__ volatile("mtc2 %0, $" GTE_REG(GTE_R_##reg) : : "r"(val))
/* gte_get with the load-delay nop inside the asm (the original has mfc2; nop; then a use) */
#define gte_get_wait(reg, var) __asm__ volatile("mfc2 %0, $" GTE_REG(GTE_R_##reg) "\n\tnop" : "=r"(var))
/* gte_set through a copy: out = val, then mtc2 out (the original copies val into a new register first) */
#define gte_set_copy(reg, out, val) \
    __asm__ volatile("mtc2 %0, $" GTE_REG(GTE_R_##reg) : "=r"(out) : "0"(val))
#define gte_load(reg, ptr, off) __asm__ volatile("lwc2 $" GTE_REG(GTE_R_##reg) ", " #off "(%0)" : : "r"(ptr))
#define gte_store(reg, ptr, off) \
    __asm__ volatile("swc2 $" GTE_REG(GTE_R_##reg) ", " #off "(%0)" : : "r"(ptr) : "memory")
#define gte_set_ctrl(reg, val) __asm__ volatile("ctc2 %z0, $" GTE_REG(GTE_R_##reg) : : "rJ"(val))
#define gte_get_ctrl(reg, var) __asm__ volatile("cfc2 %0, $" GTE_REG(GTE_R_##reg) : "=r"(var))
/* FLAG bits that mark a failed projection (overflow, off-screen), tested after rtps */
#define GTE_FLAG_ERRORS 0x7FC1E000
/* gte_get_ctrl with the load-delay nop inside the asm (the original has cfc2; nop; then a use) */
#define gte_get_ctrl_wait(reg, var) __asm__ volatile("cfc2 %0, $" GTE_REG(GTE_R_##reg) "\n\tnop" : "=r"(var))

/* Two and three control registers in one statement, loaded from the arguments in the order of the macro's name
 * (ab: a first, then b; bca: b, c, a) with the load order and registers of the original (gte_light_setup): the
 * declaration order picks the load order, a hard register (asm("$N")) the register. */
#define gte_set_ctrl2(ra, a, rb, b) ({                                                                \
        s32 b_ = (b), a_ = (a);                                                                       \
        __asm__ volatile("ctc2 %0, $" GTE_REG(GTE_R_##ra) "\n\tctc2 %1, $" GTE_REG(GTE_R_##rb)        \
                         : : "r"(a_), "r"(b_) : "memory");                                            \
    })
#define gte_set_ctrl2_ab(ra, a, rb, b) ({                                                             \
        register s32 a_ asm("$4") = (a);                                                              \
        register s32 b_ asm("$5") = (b);                                                              \
        __asm__ volatile("ctc2 %0, $" GTE_REG(GTE_R_##ra) "\n\tctc2 %1, $" GTE_REG(GTE_R_##rb)        \
                         : : "r"(a_), "r"(b_) : "memory");                                            \
    })
#define gte_set_ctrl3(ra, a, rb, b, rc, c) ({                                                         \
        register s32 a_ asm("$4") = (a);                                                              \
        s32 b_ = (b), c_ = (c);                                                                       \
        __asm__ volatile("ctc2 %0, $" GTE_REG(GTE_R_##ra) "\n\tctc2 %1, $" GTE_REG(GTE_R_##rb)        \
                         "\n\tctc2 %2, $" GTE_REG(GTE_R_##rc) : : "r"(a_), "r"(b_), "r"(c_) : "memory"); \
    })
#define gte_set_ctrl3_bca(ra, a, rb, b, rc, c) ({                                                     \
        register s32 b_ asm("$3") = (b);                                                              \
        s32 c_ = (c), a_ = (a);                                                                       \
        __asm__ volatile("ctc2 %0, $" GTE_REG(GTE_R_##ra) "\n\tctc2 %1, $" GTE_REG(GTE_R_##rb)        \
                         "\n\tctc2 %2, $" GTE_REG(GTE_R_##rc) : : "r"(a_), "r"(b_), "r"(c_) : "memory"); \
    })

/* Several registers in one statement (nothing can be scheduled between them) */
#define gte_set_IR0123(a, b, c, d) __asm__ volatile( \
    "mtc2 %0, $8\n\tmtc2 %1, $9\n\tmtc2 %2, $10\n\tmtc2 %3, $11" : : "r"(a), "r"(b), "r"(c), "r"(d))
/* TRX, TRY, TRZ. z is tied to a dummy output: a constant then gets a pseudo's register (v0), not a reload
 * register as a plain "r" input does (draw_view_entries). */
#define gte_set_TR(x, y, z) ({ int gte_tr_z_; __asm__ volatile( \
    "ctc2 %1, $5\n\tctc2 %2, $6\n\tctc2 %0, $7" : "=r"(gte_tr_z_) : "r"(x), "r"(y), "0"(z)); })
/* TRX, TRY, TRZ from a0, v0, v1 (the original's registers where gte_set_TR's tie gives z v0: player_blast) */
#define gte_set_TR_a0v0v1(x, y, z) ({                                                                 \
        register s32 tr_x_ asm("$4") = (x);                                                           \
        register s32 tr_y_ asm("$2") = (y);                                                           \
        register s32 tr_z_ asm("$3") = (z);                                                           \
        __asm__ volatile("ctc2 %0, $5\n\tctc2 %1, $6\n\tctc2 %2, $7"                                  \
                         : : "r"(tr_x_), "r"(tr_y_), "r"(tr_z_) : "memory");                          \
    })
/* Rotation matrix words R11R12, R13R21, R22R23 then R31R32, R33, each group in one statement. The values pass
 * through the variables t0.. (tied operands; the original reuses the same registers for both groups: fire_beam). */
#define gte_set_R012(t0, t1, t2, a, b, c) __asm__ volatile( \
    "ctc2 %0, $0\n\tctc2 %1, $1\n\tctc2 %2, $2" : "=r"(t0), "=r"(t1), "=r"(t2) : "0"(a), "1"(b), "2"(c))
#define gte_set_R34(t0, t1, a, b) __asm__ volatile( \
    "ctc2 %0, $3\n\tctc2 %1, $4" : "=r"(t0), "=r"(t1) : "0"(a), "1"(b))
/* Light matrix words L11L12, L13L21, L22L23 then L31L32, L33, each group in one statement (as gte_set_R012). */
#define gte_set_L012(t0, t1, t2, a, b, c) __asm__ volatile( \
    "ctc2 %0, $8\n\tctc2 %1, $9\n\tctc2 %2, $10" : "=r"(t0), "=r"(t1), "=r"(t2) : "0"(a), "1"(b), "2"(c))
#define gte_set_L34(t0, t1, a, b) __asm__ volatile( \
    "ctc2 %0, $11\n\tctc2 %1, $12" : "=r"(t0), "=r"(t1) : "0"(a), "1"(b))
/* Projection plane distance H = 0x80 and screen offset (0, 0), through $t2: a hand-written block without a
 * clobber (no value lives in $t2 there; with one, the allocator skips $t2 later: point_light_glow_draw). */
#define gte_set_screen_h80_origin() gte_set_screen_h80_origin_via(10)
/* the same through register tmp (a number: 12 = $t4, part_rec_visible) */
#define gte_set_screen_h80_origin_via(tmp) __asm__ volatile("addiu $" #tmp ", $zero, 0x80\n\tctc2 $" #tmp ", $26\n\t" \
    "addu $" #tmp ", $zero, $zero\n\tctc2 $" #tmp ", $24\n\tctc2 $" #tmp ", $25")
/* The rotation matrix loaded from words[0..2], then words[3..4] (rot_matrix_load), and stored there with the stores
 * inside the asm: C stores let sched2 hoist the next block's constants above the last two (player_move_z). The values
 * pass through t0.. (one set of variables for both groups, as in the original). */
#define gte_load_R012(words, t0, t1, t2) __asm__ volatile( \
    "lw %0, 0(%3)\n\tlw %1, 4(%3)\n\tlw %2, 8(%3)\n\tctc2 %0, $0\n\tctc2 %1, $1\n\tctc2 %2, $2" \
    : "=&r"(t0), "=&r"(t1), "=&r"(t2) : "r"(words))
#define gte_load_R34(words, t0, t1) __asm__ volatile( \
    "lw %0, 12(%2)\n\tlw %1, 16(%2)\n\tctc2 %0, $3\n\tctc2 %1, $4" : "=&r"(t0), "=&r"(t1) : "r"(words))
/* The light matrix (L11L12 .. L33) and the light colour matrix (LR1LR2 .. LB3) the same way, words[0..2] then
 * words[3..4] through one set of variables (title title_model_draw). */
#define gte_load_L012(words, t0, t1, t2) __asm__ volatile( \
    "lw %0, 0(%3)\n\tlw %1, 4(%3)\n\tlw %2, 8(%3)\n\tctc2 %0, $8\n\tctc2 %1, $9\n\tctc2 %2, $10" \
    : "=&r"(t0), "=&r"(t1), "=&r"(t2) : "r"(words))
#define gte_load_L34(words, t0, t1) __asm__ volatile( \
    "lw %0, 12(%2)\n\tlw %1, 16(%2)\n\tctc2 %0, $11\n\tctc2 %1, $12" : "=&r"(t0), "=&r"(t1) : "r"(words))
#define gte_load_LC012(words, t0, t1, t2) __asm__ volatile( \
    "lw %0, 0(%3)\n\tlw %1, 4(%3)\n\tlw %2, 8(%3)\n\tctc2 %0, $16\n\tctc2 %1, $17\n\tctc2 %2, $18" \
    : "=&r"(t0), "=&r"(t1), "=&r"(t2) : "r"(words))
#define gte_load_LC34(words, t0, t1) __asm__ volatile( \
    "lw %0, 12(%2)\n\tlw %1, 16(%2)\n\tctc2 %0, $19\n\tctc2 %1, $20" : "=&r"(t0), "=&r"(t1) : "r"(words))
/* Each pair above as one macro (a plain block with its own temporaries): title title_model_draw. */
#define gte_load_R_pair(words) \
    { u32 gte_w0_, gte_w1_, gte_w2_; gte_load_R012(words, gte_w0_, gte_w1_, gte_w2_); gte_load_R34(words, gte_w0_, gte_w1_); }
#define gte_load_L_pair(words) \
    { u32 gte_w0_, gte_w1_, gte_w2_; gte_load_L012(words, gte_w0_, gte_w1_, gte_w2_); gte_load_L34(words, gte_w0_, gte_w1_); }
#define gte_load_LC_pair(words) \
    { u32 gte_w0_, gte_w1_, gte_w2_; gte_load_LC012(words, gte_w0_, gte_w1_, gte_w2_); gte_load_LC34(words, gte_w0_, gte_w1_); }
/* dst = R * src (matrix pointers; the rotation matrix loaded already), a column at a time with the products stored
 * through dst: gte_mul_matrix_pinned's body with free registers and its own destination (title title_model_draw). */
#define gte_mul_rot_columns(src, dst) \
    { \
        u32 *in_ = (u32 *)(src); \
        s16 *out_ = (s16 *)(dst); \
        u32 a_, b_, c_, d_; \
        s32 e_; \
        a_ = in_[0]; \
        c_ = in_[3]; \
        b_ = in_[1]; \
        gte_set(IR1, a_); \
        gte_set(IR2, b_ >> 16); \
        gte_set(IR3, c_); \
        a_ >>= 16; \
        gte_rtir_b(); \
        d_ = in_[2]; \
        c_ >>= 16; \
        a_ |= d_ << 16; \
        gte_set(VXY0, a_); \
        gte_set(VZ0, c_); \
        gte_store(MAC1, dst, 0); \
        gte_store(MAC3, dst, 0xC); \
        gte_get(MAC2, a_); \
        gte_rtv0_b(); \
        d_ >>= 16; \
        c_ = in_[4]; \
        gte_get(MAC1, e_); \
        gte_store(MAC2, dst, 8); \
        gte_set(IR1, b_); \
        gte_set(IR2, d_); \
        gte_set(IR3, c_); \
        gte_get(MAC3, c_); \
        gte_rtir_b(); \
        out_[1] = e_; \
        out_[7] = c_; \
        gte_store(MAC1, dst, 4); \
        gte_get(MAC2, c_); \
        gte_store(MAC3, dst, 0x10); \
        out_[3] = a_; \
        out_[5] = c_; \
    }
/* TRX, TRY, TRZ from words[0..2] with the last load free to reuse the base register (`lw v0, 8(v0)`; title
 * title_model_draw). */
#define gte_load_TR_last_base(words) ({ u32 gte_t0_, gte_t1_, gte_t2_; __asm__ volatile( \
    "lw %1, 0(%3)\n\tlw %0, 4(%3)\n\tlw %2, 8(%3)\n\tctc2 %1, $5\n\tctc2 %0, $6\n\tctc2 %2, $7" \
    : "=&r"(gte_t0_), "=&r"(gte_t1_), "=r"(gte_t2_) : "r"(words)); })
/* The whole rotation matrix from words[0..4], then the translation vector from words[0..2], each in one
 * statement (gte_load_R012 + gte_load_R34 as two statements give the second group other registers). The operand
 * order inside is the original's (cc1 assigns registers by operand: words[0] goes through the second one):
 * title title_cursor_draw. */
#define gte_load_R(words) ({ u32 gte_r0_, gte_r1_, gte_r2_; gte_load_R_via(gte_r0_, gte_r1_, gte_r2_, words); })
/* gte_load_R through the caller's temporaries (hard-register locals pin them: mul_matrix) */
#define gte_load_R_via(t0, t1, t2, words) __asm__ volatile( \
    "lw %1, 0(%3)\n\tlw %0, 4(%3)\n\tlw %2, 8(%3)\n\tctc2 %1, $0\n\tctc2 %0, $1\n\tctc2 %2, $2\n\t" \
    "lw %1, 12(%3)\n\tlw %0, 16(%3)\n\tctc2 %1, $3\n\tctc2 %0, $4" \
    : "=&r"(t0), "=&r"(t1), "=&r"(t2) : "r"(words))
/* The light colour matrix (LR1LR2 .. LB3) from words[0..4], in gte_load_R's form: s01 trace_solids_masked. */
#define gte_load_LC(words) ({ u32 gte_c0_, gte_c1_, gte_c2_; __asm__ volatile( \
    "lw %1, 0(%3)\n\tlw %0, 4(%3)\n\tlw %2, 8(%3)\n\tctc2 %1, $16\n\tctc2 %0, $17\n\tctc2 %2, $18\n\t" \
    "lw %1, 12(%3)\n\tlw %0, 16(%3)\n\tctc2 %1, $19\n\tctc2 %0, $20" \
    : "=&r"(gte_c0_), "=&r"(gte_c1_), "=&r"(gte_c2_) : "r"(words)); })
/* The whole rotation matrix in one statement through fixed registers, as the original's hand-written blocks:
 * v1, a0, v0 (rot_up_vector, mover_calc_pos) or a0, a1, v1 with a memory clobber (muzzle_fire). */
#define gte_load_R_v1a0v0(words) __asm__ volatile( \
    "lw $3, 0(%0)\n\tlw $4, 4(%0)\n\tlw $2, 8(%0)\n\tctc2 $3, $0\n\tctc2 $4, $1\n\tctc2 $2, $2\n\t" \
    "lw $3, 12(%0)\n\tlw $4, 16(%0)\n\tctc2 $3, $3\n\tctc2 $4, $4" : : "r"(words) : "$2", "$3", "$4")
#define gte_load_R_a0a1v1(words) __asm__ volatile( \
    "lw $4, 0(%0)\n\tlw $5, 4(%0)\n\tlw $3, 8(%0)\n\tctc2 $4, $0\n\tctc2 $5, $1\n\tctc2 $3, $2\n\t" \
    "lw $4, 12(%0)\n\tlw $5, 16(%0)\n\tctc2 $4, $3\n\tctc2 $5, $4" : : "r"(words) : "$3", "$4", "$5", "memory")
/* The rotation matrix from words[0..4] in four statements (lw x3, ctc2 x3, lw x2, ctc2 x2): the temporaries are
 * set and used twice, so they rank above long-lived values in allocation; declared r2 first, they take v1, a0, v0
 * (a0, a1, v1 when v0 holds words) as in the original (light_draw_list_build). */
#define gte_load_R_split(words) ({ s32 *gte_w_ = (s32 *)(words); s32 gte_r2_, gte_r0_, gte_r1_;                 \
        __asm__ volatile("lw %0, 0(%3)\n\tlw %1, 4(%3)\n\tlw %2, 8(%3)"                                     \
                         : "=&r"(gte_r0_), "=&r"(gte_r1_), "=&r"(gte_r2_) : "r"(gte_w_));                   \
        __asm__ volatile("ctc2 %0, $0\n\tctc2 %1, $1\n\tctc2 %2, $2" : : "r"(gte_r0_), "r"(gte_r1_), "r"(gte_r2_)); \
        __asm__ volatile("lw %0, 12(%2)\n\tlw %1, 16(%2)" : "=&r"(gte_r0_), "=&r"(gte_r1_) : "r"(gte_w_));  \
        __asm__ volatile("ctc2 %0, $3\n\tctc2 %1, $4" : : "r"(gte_r0_), "r"(gte_r1_));                     \
    })
/* VXY0 and VZ0 from registers in one statement, xy evaluated first (light_draw_list_build) */
#define gte_set_V0(xy, z) __asm__ volatile("mtc2 %0, $0\n\tmtc2 %1, $1" : : "r"(xy), "r"(z))
/* TRX, TRY, TRZ from three registers of the compiler's choice, with a memory clobber (light_draw_list_build) */
#define gte_set_TR_r(x, y, z) \
    __asm__ volatile("ctc2 %0, $5\n\tctc2 %1, $6\n\tctc2 %2, $7" : : "r"(x), "r"(y), "r"(z) : "memory")
/* MAC1 and MAC3 stored as the words at base+8 and base+12, MAC2 read into y between them, in one statement
 * (light_draw_list_build: a transformed position whose y the caller stores as a halfword) */
#define gte_store_MAC13_get_MAC2(base, y) __asm__ volatile( \
    "swc2 $25, 8(%1)\n\tmfc2 %0, $26\n\tswc2 $27, 12(%1)" : "=r"(y) : "r"(base) : "memory")
/* gte_load_R_v1a0v0 leaving R33 (words[4]) in a0 as a0_out, a hard-register local the caller reads (fx_draw_pool) */
#define gte_load_R_v1a0v0_out(a0_out, words) __asm__ volatile( \
    "lw $3, 0(%1)\n\tlw $4, 4(%1)\n\tlw $2, 8(%1)\n\tctc2 $3, $0\n\tctc2 $4, $1\n\tctc2 $2, $2\n\t" \
    "lw $3, 12(%1)\n\tlw $4, 16(%1)\n\tctc2 $3, $3\n\tctc2 $4, $4" : "=&r"(a0_out) : "r"(words) : "$2", "$3")
/* Copies the 5 rotation-matrix words src -> dst, words 0..2 then 3..4, each group in one statement (t0.. carry
 * the values; the asm also keeps reorg from filling the first delay slot: rot3x3_copy). */
#define rot_matrix_copy012(dst, src, t0, t1, t2) __asm__ volatile( \
    "lw %0, 0(%3)\n\tlw %1, 4(%3)\n\tlw %2, 8(%3)\n\tsw %0, 0(%4)\n\tsw %1, 4(%4)\n\tsw %2, 8(%4)" \
    : "=&r"(t0), "=&r"(t1), "=&r"(t2) : "r"(src), "r"(dst) : "memory")
#define rot_matrix_copy34(dst, src, t0, t1) __asm__ volatile( \
    "lw %0, 12(%2)\n\tlw %1, 16(%2)\n\tsw %0, 12(%3)\n\tsw %1, 16(%3)" : "=&r"(t0), "=&r"(t1) : "r"(src), "r"(dst) : "memory")
#define gte_load_TR(words) ({ u32 gte_t0_, gte_t1_, gte_t2_; __asm__ volatile( \
    "lw %2, 0(%3)\n\tlw %1, 4(%3)\n\tlw %0, 8(%3)\n\tctc2 %2, $5\n\tctc2 %1, $6\n\tctc2 %0, $7" \
    : "=&r"(gte_t0_), "=&r"(gte_t1_), "=&r"(gte_t2_) : "r"(words)); })
#define gte_store_R012(words, t0, t1, t2) __asm__ volatile( \
    "cfc2 %0, $0\n\tcfc2 %1, $1\n\tcfc2 %2, $2\n\tsw %0, 0(%3)\n\tsw %1, 4(%3)\n\tsw %2, 8(%3)" \
    : "=&r"(t0), "=&r"(t1), "=&r"(t2) : "r"(words))
#define gte_store_R34(words, t0, t1) __asm__ volatile( \
    "cfc2 %0, $3\n\tcfc2 %1, $4\n\tsw %0, 12(%2)\n\tsw %1, 16(%2)" : "=&r"(t0), "=&r"(t1) : "r"(words))
/* Reads FLAG into $zero after a nop: waits for the last command, the value discarded (loader_gte_scale). */
#define gte_flag_discard() __asm__ volatile("nop\n\tcfc2 $zero, $31")
#define gte_get_IR123(x, y, z) __asm__ volatile( \
    "mfc2 %0, $9\n\tmfc2 %1, $10\n\tmfc2 %2, $11" : "=r"(x), "=r"(y), "=r"(z))
/* Far colour RFC, GFC, BFC / IR1-IR3 in one statement each; MAC2, MAC3 in one (colour_list_intpl) */
#define gte_set_FC(r, g, b) __asm__ volatile( \
    "ctc2 %0, $21\n\tctc2 %1, $22\n\tctc2 %2, $23" : : "r"(r), "r"(g), "r"(b))
#define gte_set_IR123(x, y, z) __asm__ volatile( \
    "mtc2 %0, $9\n\tmtc2 %1, $10\n\tmtc2 %2, $11" : : "r"(x), "r"(y), "r"(z))
#define gte_get_MAC23(y, z) __asm__ volatile("mfc2 %0, $26\n\tmfc2 %1, $27" : "=r"(y), "=r"(z))
#define gte_get_MAC123(x, y, z) __asm__ volatile( \
    "mfc2 %0, $25\n\tmfc2 %1, $26\n\tmfc2 %2, $27" : "=r"(x), "=r"(y), "=r"(z))

/* Rotation matrix for a turn about Y from a packed sin/cos word (cos high, sin low). */
#define gte_set_rot_y(sc) __asm__ volatile( \
    "sra $8, %0, 16\n\tctc2 $8, $0\n\tctc2 $8, $4\n\tctc2 %0, $3\n\tnegu %0, %0\n\tctc2 %0, $1" \
    : "=r"(sc) : "0"(sc) : "$8")

/* b = a * b, mul_matrix inlined (title title_cursor_draw): a goes into the rotation matrix, each column of b
 * is rotated and stored back into b. RX/RY/RZ pin the column registers the original uses. */
#define gte_mul_matrix_pinned(a, b_mat, RX, RY, RZ) ({ \
    u32 *b = (u32 *)(b_mat); \
    s16 *out = (s16 *)(b_mat); \
    register u32 b0 asm(RX); \
    register u32 b3 asm(RY); \
    register u32 b1 asm(RZ); \
    register u32 b4 asm(RY); \
    register s32 m01 asm(RX); \
    register s32 m12 asm(RY); \
    register s32 m11 asm(RY); \
    u32 b2, hi; \
    s32 m10; \
    gte_load_R(a); \
    b0 = b[0]; \
    b3 = b[3]; \
    b1 = b[1]; \
    gte_set(IR1, b0); \
    hi = b1 >> 16; \
    gte_set(IR2, hi); \
    gte_set(IR3, b3); \
    b0 >>= 16; \
    gte_rtir_b(); \
    b2 = b[2]; \
    b3 >>= 16; \
    b0 |= b2 << 16; \
    gte_set(VXY0, b0); \
    gte_set(VZ0, b3); \
    gte_store(MAC1, out, 0); \
    gte_store(MAC3, out, 12); \
    gte_get(MAC2, m01); \
    gte_rtv0_b(); \
    b2 >>= 16; \
    b4 = b[4]; \
    gte_get(MAC1, m10); \
    gte_store(MAC2, out, 8); \
    gte_set(IR1, b1); \
    gte_set(IR2, b2); \
    gte_set(IR3, b4); \
    gte_get(MAC3, m12); \
    gte_rtir_b(); \
    out[1] = m10; \
    out[7] = m12; \
    gte_store(MAC1, out, 4); \
    gte_get(MAC2, m11); \
    gte_store(MAC3, out, 16); \
    out[3] = m01; \
    out[5] = m11; \
})

/* gte_mul_matrix_pinned with the products' swc2 through b_mat itself (a hard-register pointer copy; the
 * lw/sh go through the pointer it copies): title title_rec_matrix_update. */
#define gte_mul_matrix_pinned_ptr(a, b_mat, RX, RY, RZ) ({ \
    u32 *b = (u32 *)(b_mat); \
    s16 *bh = (s16 *)(b_mat); \
    register u32 b0 asm(RX); \
    register u32 b3 asm(RY); \
    register u32 b1 asm(RZ); \
    register u32 b4 asm(RY); \
    register s32 m01 asm(RX); \
    register s32 m12 asm(RY); \
    register s32 m11 asm(RY); \
    u32 b2, hi; \
    s32 m10; \
    gte_load_R(a); \
    b0 = b[0]; \
    b3 = b[3]; \
    b1 = b[1]; \
    gte_set(IR1, b0); \
    hi = b1 >> 16; \
    gte_set(IR2, hi); \
    gte_set(IR3, b3); \
    b0 >>= 16; \
    gte_rtir_b(); \
    b2 = b[2]; \
    b3 >>= 16; \
    b0 |= b2 << 16; \
    gte_set(VXY0, b0); \
    gte_set(VZ0, b3); \
    gte_store(MAC1, (b_mat), 0); \
    gte_store(MAC3, (b_mat), 12); \
    gte_get(MAC2, m01); \
    gte_rtv0_b(); \
    b2 >>= 16; \
    b4 = b[4]; \
    gte_get(MAC1, m10); \
    gte_store(MAC2, (b_mat), 8); \
    gte_set(IR1, b1); \
    gte_set(IR2, b2); \
    gte_set(IR3, b4); \
    gte_get(MAC3, m12); \
    gte_rtir_b(); \
    bh[1] = m10; \
    bh[7] = m12; \
    gte_store(MAC1, (b_mat), 4); \
    gte_get(MAC2, m11); \
    gte_store(MAC3, (b_mat), 16); \
    bh[3] = m01; \
    bh[5] = m11; \
})

#endif
