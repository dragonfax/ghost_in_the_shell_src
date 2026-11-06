/* title_scene: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

extern s32 title_place_task;
extern s16 title_place_data;
extern s16 D_80111EE2;
void title_timer_rec_update(void *self);  /* a function reached by pointer */
void title_timer_draw(TitleTimerObj *self);  /* a function reached by pointer */
/* Resets the title control at title_place_task, then fills its record and sets the two halfwords at title_place_data. */
void title_task_init(void) {
    s16 *slot;

    task_reset((TitleCtl *)&title_place_task);
    slot = &title_place_data;
    task_set((TitleTaskRec *)&title_place_task, 0, (s32)&title_timer_rec_update, (s32)&title_timer_draw, (s32)slot);
    *slot = 0x1A;
    D_80111EE2 = 0xD2;
}

extern TitlePlaceRec *title_place_ptr;
extern s32 title_place_task;
/* Stores x and y in the title record at title_place_ptr, clears its 0x0A and 0x0C fields, then runs task_start on the table at title_place_task. */
void title_rec_place(s16 x, s16 y) {
    TitlePlaceRec *rec = title_place_ptr;

    task_start(0, &title_place_task, 0);
    rec->x = x;
    rec->unk_0A = 0;
    rec->y = y;
    rec->unk_0C = 0;
}

extern s16 D_80111EDA;
void title_rec_set_y(s32 value) {
    title_place_ptr->y = value;
    *(s16 *)&title_place_ptr->pad_06 = value;
    D_80111EDA = 3;
}

void title_timer_rec_update(void *self) {
    TitleTimerRec *rec = ((TitleTimerObj *)self)->timer;

    switch (((TitleTimerObj *)self)->state) {
    case 0:
        rec->counter++;
        if (rec->counter_limit < rec->counter) {
            ((TitleTimerObj *)self)->state++;
            rec->elapsed = 0;
        } else {
            break;
        }
        /* fall through */
    case 1:
        rec->ratio = (rec->elapsed << 12) / rec->duration;
        rec->elapsed++;
        if (rec->duration < rec->elapsed) {
            ((TitleTimerObj *)self)->state++;
        }
        break;
    case 2:
        break;
    case 3:
        rec->ratio = (rec->elapsed << 12) / rec->duration;
        rec->elapsed--;
        if (rec->elapsed < 0) {
            title_flag_test_set(self);
        }
        break;
    }
}

extern u16 title_timer_tpage;
extern u16 title_timer_tpage_alt;
extern u16 title_timer_clut;
/* Draws a two-part sprite bar at the timer's position, its brightness the timer's ratio / 32. */
void title_timer_draw(TitleTimerObj *self) {
    TitleTimerRec *rec = self->timer;
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 shade = rec->ratio / 32;
    s32 x, y;

    if (shade == 0) {
        return;
    }
    x = rec->x;
    y = rec->y;
    ((TitleSprt *)scratch_top)->len = 4;
    ((TitleSprt *)scratch_top)->code = 0x64;
    ((TitleSprt *)scratch_top)->u = 0;
    ((TitleSprt *)scratch_top)->v = 0xF4;
    ((TitleSprt *)scratch_top)->r = shade;
    ((TitleSprt *)scratch_top)->g = shade;
    ((TitleSprt *)scratch_top)->b = shade;
    ((TitleSprt *)scratch_top)->w = 0x100;
    ((TitleSprt *)scratch_top)->h = 9;
    ((TitleSprt *)scratch_top)->code &= ~1;
    ((TitleSprt *)scratch_top)->clut = title_timer_clut;
    ((TitleSprt *)scratch_top)->x = x;
    ((TitleSprt *)scratch_top)->y = y;
    {
        u8 *ot = ctx->ot_base + 8;
        u8 *pkt = scratch_top;
        addPrim(ot, pkt);
    }
    scratch_top += sizeof(TitleSprt);

    ((TitleDrTpage *)scratch_top)->len = 1;
    ((TitleDrTpage *)scratch_top)->code = (title_timer_tpage & 0x9FF) | 0xE1000600;
    {
        u8 *ot = ctx->ot_base + 8;
        u8 *pkt = scratch_top;
        addPrim(ot, pkt);
    }
    scratch_top += sizeof(TitleDrTpage);

    ((TitleSprt *)scratch_top)->len = 4;
    ((TitleSprt *)scratch_top)->code = 0x64;
    ((TitleSprt *)scratch_top)->x = x + 0x100;
    ((TitleSprt *)scratch_top)->y = y;
    ((TitleSprt *)scratch_top)->u = 0;
    ((TitleSprt *)scratch_top)->v = 0xF4;
    ((TitleSprt *)scratch_top)->r = shade;
    ((TitleSprt *)scratch_top)->g = shade;
    ((TitleSprt *)scratch_top)->b = shade;
    ((TitleSprt *)scratch_top)->code &= ~1;
    ((TitleSprt *)scratch_top)->w = 0xC;
    ((TitleSprt *)scratch_top)->clut = title_timer_clut;
    ((TitleSprt *)scratch_top)->h = 9;
    {
        u8 *ot = ctx->ot_base + 8;
        u8 *pkt = scratch_top;
        addPrim(ot, pkt);
    }
    scratch_top += sizeof(TitleSprt);

    ((TitleDrTpage *)scratch_top)->len = 1;
    ((TitleDrTpage *)scratch_top)->code = (title_timer_tpage_alt & 0x9FF) | 0xE1000600;
    {
        u8 *ot = ctx->ot_base + 8;
        u8 *pkt = scratch_top;
        addPrim(ot, pkt);
    }
    scratch_top += sizeof(TitleDrTpage);

    ((TitleDrTwin *)scratch_top)->len = 2;
    ((TitleDrTwin *)scratch_top)->code[0] = 0xE2000000;
    ((TitleDrTwin *)scratch_top)->code[1] = 0;
    {
        u8 *ot = ctx->ot_base + 8;
        u8 *pkt = scratch_top;
        addPrim(ot, pkt);
    }
    scratch_top += sizeof(TitleDrTwin);
}

/* Builds a 2-word E1 (texture page / draw mode) primitive in the scratch area and links it into the
 * ordering table at ot_index. The entry address is formed offset-first; that operand order is what matches. */
void title_draw_mode_link(s32 ot_index, s32 semi_trans, s32 tpage) {
    TitleDrawCtx *ctx;
    s32 page_bits;
    u8 *pkt;
    u8 *entry;

    page_bits = (tpage & 3) << 5;
    ctx = title_draw_ctx_ptr;
    scratch_top[3] = 1;
    if (semi_trans != 0) {
        *(u32 *)(scratch_top + 4) = page_bits | 0xE1000600;
    } else {
        *(u32 *)(scratch_top + 4) = page_bits | 0xE1000400;
    }
    entry = (u8 *)(ot_index * 4) + (u32)ctx->ot_base;
    pkt = scratch_top;
    addPrim(entry, pkt);
    scratch_top += 8;
}

extern s32 title_sprite_row_flag;

void title_state_set(s32 arg0) {
    title_sprite_row_flag = arg0;
}

extern s16 title_tpage;
extern s16 title_clut;
extern u8 title_tpage_data[];
extern u16 title_clut_data[16];
extern u8 title_task_rec[];
void title_task_phase0();  /* a function reached by pointer */
void title_bone_anim_update(TitleCtl *ctl);  /* a function reached by pointer */
void title_task_phase2(TitleCtl *ctl);  /* a function reached by pointer */
extern u8 title_spark_state[];
extern u8 title_rgb_palette[];
void func_800B2468(void *src, void *dst, s32 count);
void title_spark_init(void *src);
void title_logo_init(void);
/* Title screen setup: creates two handles (into title_tpage and title_clut), resets the control
 * block, sets it up from the four tables, runs the two follow-up calls and clears title_sprite_row_flag. */
void title_screen_init(void) {
    title_tpage = sprite_load_tpage(title_tpage_data, 0x80, 0x1C0);
    title_clut = clut_load(title_clut_data, 0x40, 0xF0, 0, 1, 0x10);
    task_reset((TitleCtl *)title_task_rec);
    task_set((TitleTaskRec *)title_task_rec, (s32)title_task_phase0, (s32)title_bone_anim_update, (s32)title_task_phase2, (s32)title_spark_state);
    func_800B2468(title_clut_data, title_rgb_palette, 0x10);
    title_spark_init(title_tpage_data);
    title_logo_init();
    title_sprite_row_flag = 0;
}

void func_800B2468(void *src, void *dst, s32 count) {
    s16 unused;
    s32 i;
    u16 c;
    u32 w;
    TitleClutRgb *p = dst;

    for (i = 0; i < count; i++) {
        c = *(u16 *)src;
        src += 2;
        w = c;
        p->r = (c & 0x1F) << 3;
        ((TitleClutRgb *)dst)->g = (w >> 2) & 0xF8;
        ((TitleClutRgb *)dst)->b = (w >> 7) & 0xF8;
        dst += sizeof(TitleClutRgb);
        p++;
    }
}

extern s32 img4_get_pixel(s16 *hdr, s32 x, s32 y);
extern s16 D_80111F62, D_80111F64, D_80111F68, D_80111F6A, D_80111F6C, D_80111F70, D_80111F72,
    D_80111F74, D_80111F78, D_80111F7A, D_80111F7C, D_80111F84, title_spark_timer;
extern s32 title_spark_ptr;
void title_spark_init(void *src) {
    s32 row, col, idx;
    TitleSpark *rec;
    u8 *color;
    s16 life;
    u8 blue;
    u8 *state;
    s32 vx, vy, vz;

    state = title_spark_state;
    *(u16 *)state = 0;
    D_80111F64 = 0x100;
    D_80111F62 = 0;
    D_80111F70 = 0;
    D_80111F72 = 0;
    D_80111F74 = 0;
    title_spark_timer = 0x78;
    D_80111F78 = 0;
    D_80111F7A = 0;
    D_80111F7C = 0;
    D_80111F68 = 0;
    D_80111F6A = 0;
    D_80111F6C = 0;
    D_80111F84 = 0;
    rec = (TitleSpark *)card_work_buf;
    title_spark_ptr = (s32)rec;
    srand(-1);
    for (row = 0; row < 0x14; row++) {
        for (col = 0; col < 0xE0; col++) {
            idx = img4_get_pixel(src, col, row);
            if (idx != 0) {
                color = title_rgb_palette + idx * 4;
                rec->color_r = color[0];
                rec->color_g = color[1];
                blue = color[2];
                rec->unk_03 = 0x6A;
                rec->pos_x = col - 0x70;
                rec->pos_y = row - 0x1A;
                rec->pos_z = 0x100;
                rec->pos_x <<= 6;
                rec->color_b = blue;
                rec->pos_y <<= 6;
                rec->pos_z <<= 6;
                vx = 0x80 - rand() * 0x101 / 0x8000;
                vy = 0x80 - rand() * 0x101 / 0x8000;
                vz = 0x80 - rand() * 0x101 / 0x8000;
                rec->vel_x = vx;
                rec->vel_y = vy;
                rec->vel_z = vz;
                life = rand() % 40 + 0x50;
                rec->life = life;
                rec->life_step = 0x1000 / life;
                rec++;
                (*(u16 *)(state + 0x24))++;
            }
        }
    }
    card_work_buf = (s32)rec;
}

/* Reads one 4-bit pixel from a packed 4bpp image: hdr is an s16 pixel width
 * (negative values round up by 7), the words start at +4, each word holds
 * 8 nibbles and a row is (width / 8) words. */
s32 img4_get_pixel(s16 *hdr, s32 x, s32 y) {
    s32 width;
    u32 *words;
    s32 col;
    u32 cell;
    u32 *cellp;

    width = *hdr;
    words = (u32 *)(hdr + 2);
    if (width < 0) {
        width += 7;
    }
    words += y * (width >> 3);
    col = x;
    if (x < 0) {
        col = x + 7;
    }
    col >>= 3;
    cellp = &words[col];
    cell = *cellp;
    return (cell >> ((x - col * 8) * 4)) & 0xF;
}

void title_skel_pose_rest(s32 addr) {
    TitleSkeleton *skel = (TitleSkeleton *)addr;
    TitleBone *bone;
    s32 i;
    s32 restX, restY, restZ;
    s32 offX, offY, offZ;

    bone = skel->bones;
    for (i = 0; i < skel->count; i++) {
        offX = bone->dir[0] * bone->scale;
        restX = bone->rest[0];
        bone->pos[0] = restX - offX;
        offY = bone->dir[1] * bone->scale;
        restY = bone->rest[1];
        bone->pos[1] = restY - offY;
        offZ = bone->dir[2] * bone->scale;
        restZ = bone->rest[2];
        bone->pos[2] = restZ - offZ;
        bone->scale_counter = 0;
        bone->fade = 0x1000;
        bone++;
    }
}

/* Draws a semi-transparent sprite (texture row 0xC0, or 0xC0 + h when title_sprite_row_flag is set) at OT slot 0x2C, then a texture-window reset and a draw-mode packet for title_tpage. */
void title_draw_sprite(s16 x, s16 y, s32 w, s32 h, s32 unused) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u8 *sprt_ot;
    u8 *sprt_pkt;
    u8 *win_ot;
    u8 *win_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;
    s32 tex_v;

    tex_v = h + 0xC0;
    if (title_sprite_row_flag == 0) {
        tex_v = 0xC0;
    }
    scratch_top[3] = 4;
    scratch_top[7] = 0x64;
    scratch_top[7] |= 1;
    scratch_top[7] |= 2;
    scratch_top[0xC] = 0;
    scratch_top[0xD] = tex_v;
    *(u16 *)(scratch_top + 0xE) = title_clut;
    *(s16 *)(scratch_top + 8) = x;
    *(s16 *)(scratch_top + 0xA) = y;
    *(s16 *)(scratch_top + 0x10) = w;
    *(s16 *)(scratch_top + 0x12) = h;
    sprt_ot = (u8 *)0x2C + (u32)ctx->ot_base;
    sprt_pkt = scratch_top;
    addPrim(sprt_ot, sprt_pkt);
    scratch_top += 0x14;

    scratch_top[3] = 2;
    *(s32 *)(scratch_top + 4) = 0xE2000000;
    *(s32 *)(scratch_top + 8) = 0;
    win_ot = (u8 *)0x2C + (u32)ctx->ot_base;
    win_pkt = scratch_top;
    addPrim(win_ot, win_pkt);
    scratch_top += 0xC;

    scratch_top[3] = 1;
    *(s32 *)(scratch_top + 4) = (title_tpage & 0x9FF) | 0xE1000600;
    mode_ot = (u8 *)0x2C + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

/* Draws each bone of anim's skeleton as a dot (3-word primitive: tag, colour + code, xy) in OT entry 11: the bones'
 * positions (10.6 fixed point) projected with an identity rotation, the colour (first bone's) depth-cued by each
 * bone's fade. GTE work is pipelined: bone i is projected while bone i-1's dot is finished. */
void title_skel_draw_dots(struct TitleAnim *anim) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    volatile TitleRotWords rot; /* volatile: stored in this order, before the loads (the original's order) */
    TitleBone *bone;
    TitleBone *end;
    u32 link;
    s32 r0, r1, r2;
    s32 one;
    s32 pos, x, y, xy, z, fade;

    bone = anim->bones;
    link = ((u32 *)ctx->ot_base)[11];
    one = 0x1000;
    rot.w[2] = one;
    rot.w[0] = one;
    rot.h[8] = one;
    rot.w[3] = 0;
    rot.w[1] = 0;
    gte_set_R012(r0, r1, r2, rot.w[0], rot.w[1], rot.w[2]);
    gte_set_R34(r0, r1, rot.w[3], rot.w[4]);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);

    pos = *(s32 *)&bone->pos[0]; /* x and y in one word */
    y = pos >> 22;
    x = (s16)pos >> 6;
    z = (s16)(u16)bone->pos[2] >> 6;
    xy = (x & 0xFFFF) | (y << 16);
    gte_load(RGB, bone, 0);
    gte_set(VXY0, xy);
    gte_set(VZ0, z);
    gte_nop();
    gte_rtps_b();
    end = bone + anim->bone_count;
    bone++;
    do {
        fade = bone[-1].fade;
        pos = *(s32 *)&bone->pos[0];
        y = pos >> 22;
        x = (s16)pos >> 6;
        z = (s16)(u16)bone->pos[2] >> 6;
        xy = (x & 0xFFFF) | (y << 16);
        gte_store(SXY2, scratch_top, 8);
        gte_set(IR0, fade);
        gte_nop();
        gte_dpcs_b();
        *(u32 *)scratch_top = link | 0x02000000;
        link = (u32)scratch_top & 0xFFFFFF;
        scratch_top += 0xC;
        gte_store(RGB2, scratch_top, -8);
        gte_set(VXY0, xy);
        gte_set(VZ0, z);
        bone++;
        gte_rtps_b();
    } while (bone != end);
    gte_store(SXY2, scratch_top, 8);
    gte_set(IR0, fade);
    gte_nop();
    gte_dpcs_b();
    *(u32 *)scratch_top = link | 0x02000000;
    link = (u32)scratch_top & 0xFFFFFF;
    scratch_top += 0xC;
    gte_store(RGB2, scratch_top, -8);
    ((u32 *)ctx->ot_base)[11] = link;
}

void title_skel_pose_rest(s32 addr);
void title_task_phase0(TitleTaskRec *rec) {
    TitleLink *link = (TitleLink *)rec->param;

    title_skel_pose_rest((s32)link);
    title_state_set(0);
    link->unk_2A = link->unk_28;
}

/* Title task step (phase 1): mode 0 starts the burst; mode 1 moves every bone along its direction
 * until its step count (unk_1E) reaches scale, fading it by fade_step per step; when all bones are
 * done the mode becomes -1. The x/y pair is read as one word and split by shifts. */
void title_bone_anim_update(TitleCtl *ctl) {
    struct TitleAnim *anim = ctl->anim;
    TitleBone *bone;
    s32 x, y, z;
    s32 dx, dy, dz;
    s32 i, done;

    switch (ctl->step) {
    case -1:
        break;
    case 0:
        ctl->step++;
        break;
    case 1:
        done = 0;
        bone = anim->bones;
        for (i = 0; i < anim->bone_count; i++, bone++) {
            if (bone->scale_counter < bone->scale) {
                x = *(s32 *)bone->pos;
                z = bone->pos[2];
                dx = *(s32 *)bone->dir;
                dz = bone->dir[2];
                y = x >> 16;
                x = (x << 16) >> 16;
                dy = dx >> 16;
                dx = (dx << 16) >> 16;
                y += dy;
                x += dx;
                bone->pos[0] = x;
                bone->pos[1] = y;
                z += dz;
                bone->pos[2] = z;
                bone->scale_counter++;
            } else {
                done++;
            }
            bone->fade = 0x1000 - bone->scale_counter * bone->fade_step;
        }
        if (done == anim->bone_count) {
            ctl->step = -1;
        }
        break;
    }
}

void title_skel_draw_dots(struct TitleAnim *anim);
void title_draw_sprite(s16 x, s16 y, s32 w, s32 h, s32 unused);
/* Title task step: unk_22 is a mode (0 = idle, -1 = draw the fixed panel once, else run the anim step). */
void title_task_phase2(TitleCtl *ctl) {
    struct TitleAnim *anim;

    if (ctl->step == 0) {
        return;
    }
    anim = ctl->anim;
    if (ctl->step != -1) {
        title_skel_draw_dots(anim);
    } else {
        title_draw_sprite(0x30, 0x5E, 0xE0, 0x14, 0x80);
    }
}

extern TitleLogoSlider title_logo_slider;
extern s32 title_logo_task;
void title_ref_draw(TitleRef *ref);  /* a function reached by pointer */
void title_logo_init(void) {
    TitleLogoSlider *s = &title_logo_slider;
    s32 i;
    s32 unused;

    task_reset((TitleCtl *)&title_logo_task);
    task_set((TitleTaskRec *)&title_logo_task, 0, (s32)logo_update, (s32)title_ref_draw, (s32)s);
    s->x = 0x30;
    s->y = 0x5E;
    s->count_b = 2;
    s->unk_40 = 0x30;
    s->unk_44 = -0x110;
    s->unk_50 = 0x30;
    s->unk_54 = 0x170;
    i = 0;
    do {
        s->steps_b[i] = (i << 12) / (s->count_b - 1);
        i++;
    } while (i < s->count_b);
    s->count_a = 4;
    s->left = s->x - 0x140;
    s->top = s->x - 0xA0;
    s->mid_x = s->x;
    s->mid_y = s->x;
    s->right = s->x + 0x140;
    s->bottom = s->x + 0xA0;
    s->edge_x = s->x;
    s->edge_y = s->x;
    for (i = 0; i < s->count_a; i++) {
        s->steps_a[i] = (i << 12) / (s->count_a - 1);
    }
    s->unk_76 = 0;
}

extern TitlePanelState *title_panel_state_ptr;
extern s32 title_logo_task;
void title_panel_open(s16 value74, s16 value08, s16 value04) {
    title_panel_state_ptr->unk_74 = value74;
    title_panel_state_ptr->unk_08 = value08;
    title_panel_state_ptr->unk_0A = 0;
    title_panel_state_ptr->unk_04 = value04;
    title_panel_state_ptr->unk_00 = title_panel_state_ptr->unk_0C;
    title_state_set(1);
    task_start(0, &title_logo_task, 0);
}

extern s16 D_80111F12;
/* Same code as logo_hide (title). */
void title_logo_start(s16 value74, s16 value04) {
    TitleLogoRec *rec = title_panel_state_ptr;

    FAKE_OPAQUE(rec);
    rec->unk_04 = value04;
    rec->unk_06 = 0;
    rec->unk_74 = value74;
    D_80111F12 = 3;
}

void title_draw_sprite(s16 x, s16 y, s32 w, s32 h, s32 unused);
void title_ref_draw(TitleRef *ref) {
    s16 *pos = ref->pos;
    title_draw_sprite(pos[0], pos[1], 0xE0, 0x14, 0x80);
}

void title_tri_points(s16 *dst, s32 scale);
void title_sprite_init(TitleSprite *spr);
/* Writes a fixed block of words at packet, calls title_tri_points and
   title_sprite_init on the way, and returns the end of the block. */
void *title_build_sprite_packets(u32 *packet) {
    u32 *p = packet;

    FAKE_OPAQUE(p);
    *p = 1;
    p++;
    FAKE_OPAQUE(p);
    *p = 0xE;
    p++;
    FAKE_OPAQUE(p);
    *p = 3;
    p++;
    FAKE_OPAQUE(p);
    title_tri_points((s16 *)p, 0xE);
    p += 6;
    FAKE_OPAQUE(p);
    *p = 1;
    p++;
    FAKE_OPAQUE(p);
    ((TitleWordBytes *)p)->unk_00 = 0;
    ((TitleWordBytes *)p)->unk_02 = 0;
    ((TitleWordBytes *)p)->unk_01 = 0x40;
    p++;
    FAKE_OPAQUE(p);
    *p = 1;
    p++;
    FAKE_OPAQUE(p);
    *p = 1;
    p++;
    FAKE_OPAQUE(p);
    *p = 0xE;
    p++;
    FAKE_OPAQUE(p);
    ((TitleWordSVec *)p)->x = 0;
    ((TitleWordSVec *)p)->y = 0;
    ((TitleWordSVec *)p)->z = 0;
    p += 2;
    FAKE_OPAQUE(p);
    title_sprite_init((TitleSprite *)p);
    return (u8 *)p + 0x20;
}

/* Fills a title sprite record: fixed params, two globals as position, a packed colour word. */
void title_sprite_init(TitleSprite *spr) {
    spr->unk_02 = 4;
    spr->unk_10[0] = 0xF0;
    spr->unk_10[1] = 0xC0;
    spr->unk_10[2] = 0xF0;
    spr->unk_10[3] = 0xC0;
    spr->unk_10[4] = 0xF0;
    spr->unk_10[5] = 0xC0;
    spr->tpage = title_tpage;
    spr->clut = title_clut;
    spr->unk_00 = 0;
    spr->unk_04 = 8;
    spr->unk_08 = 0;
    spr->unk_0A = 0;
    spr->unk_0C = 0;
    spr->unk_1C = 0x320C7BFF;
}

/* Fills three 4-s16 records at dst: x and y scaled by a 12-bit table lookup, z cleared. */
void title_tri_points(s16 *dst, s32 scale) {
    s16 *rec;
    s16 *rec_mid;
    s32 phase;
    s32 i;
    s32 x;
    s32 y;
    s32 scale_x;
    s32 scale_y;

    rec = dst;
    phase = 0;
    i = 0;
    scale_x = scale + 9;
    scale_y = -scale;
    rec_mid = dst + 2;
    do {
        x = scale_x * rcossin_tbl[phase & 0xFFF][0];
        if (x < 0) {
            x += 0xFFF;
        }
        y = scale_y * rcossin_tbl[phase & 0xFFF][1];
        *rec = (s16) (x >> 12);
        if (y < 0) {
            y += 0xFFF;
        }
        phase -= 0x555;
        i += 1;
        rec_mid[-1] = (s16) (y >> 12);
        rec_mid[0] = 0;
        rec_mid += 4;
        rec += 4;
    } while (i < 3);
}

void xform_pair_extrapolate(XformHost *host);
void title_anim_step(TitleCtl *ctl);
void title_seq_draw(TitleSeqTask *task);
extern TitleXformRec title_xform_recs[];
extern TitleXformSeed title_xform_pos_seed[];
extern TitleXformSeed title_xform_vel_seed[];
extern TitleXformSeed title_xform_dir_seed[];
extern u8 D_80117600[];
extern u8 D_80117628[];
extern u8 D_80117678[];
extern s32 title_seq_table_id;
void title_seq_init(void) {
    TitleXformRec *dst = title_xform_recs;
    TitleXformSeed *src1 = title_xform_pos_seed;
    TitleXformSeed *src2 = title_xform_vel_seed;
    TitleXformSeed *src3 = title_xform_dir_seed;
    s32 i;
    s32 packet;

    /* Fills the three 0x34-byte records at title_xform_recs from the three 8-byte
     * source tables, zeroes 0x18..0x1C and sets 0x30 to 0x3C. The counter
     * increment is at the top of the body: that is the order the code wants. */
    for (i = 0; i < 3;) {
        i++;
        dst->pos_x = src1->x;
        dst->pos_y = src1->y;
        dst->pos_z = src1->z;
        dst->origin_x = 0;
        dst->origin_y = 0;
        dst->origin_z = 0;
        dst->vel_x = src2->x;
        dst->vel_y = src2->y;
        dst->vel_z = src2->z;
        dst->dir_x = src3->x;
        dst->dir_y = src3->y;
        dst->dir_z = src3->z;
        dst->frames_left = 0x3C;
        dst++;
        src1++;
        src2++;
        src3++;
    }
    task_reset((TitleCtl *)D_80117600);
    task_reset((TitleCtl *)D_80117628);
    task_reset((TitleCtl *)D_80117678);
    task_set((TitleTaskRec *)D_80117600, (s32)xform_pair_extrapolate, (s32)title_anim_step, (s32)title_seq_draw, (s32)title_xform_recs);
    task_set((TitleTaskRec *)D_80117628, (s32)xform_pair_extrapolate, (s32)title_anim_step, (s32)title_seq_draw, (s32)&title_xform_recs[1]);
    task_set((TitleTaskRec *)D_80117678, (s32)xform_pair_extrapolate, (s32)title_anim_step, (s32)title_seq_draw, (s32)&title_xform_recs[2]);
    packet = card_work_buf;
    card_work_buf = (s32)title_build_sprite_packets((u32 *)packet);
    title_seq_table_id = sprite_sets_register((s32 *)packet, NULL, 0, 0, 0, 0);
}

void xform_pair_extrapolate(XformHost *host) {
    XformPair *p = host->pair;

    p->pos_out[0] = p->pos[0] - p->vel[0] * p->scale;
    p->scale_copy = p->scale;
    p->pos_out[1] = p->pos[1] - p->vel[1] * p->scale;
    p->pos_out[2] = p->pos[2] - p->vel[2] * p->scale;
    p->origin_out[0] = p->origin[0] - p->dir[0] * p->scale;
    p->origin_out[1] = p->origin[1] - p->dir[1] * p->scale;
    p->origin_out[2] = p->origin[2] - p->dir[2] * p->scale;
}

void title_anim_step(TitleCtl *ctl) {
    TitleAnimTrack *track;

    track = (TitleAnimTrack *)ctl->anim;
    if (ctl->step == 0) {
        track->unk_08 += track->delta_x;
        track->unk_0A += track->delta_y;
        track->unk_0C += track->delta_z;
        track->unk_20 += track->unk_28;
        track->unk_22 += track->unk_2A;
        track->unk_24 += track->unk_2C;
        track->frames_left -= 1;
        if ((s16)track->frames_left > 0) {
            return;
        }
        ctl->step += 1;
    }
}

extern s32 title_seq_table_id;
void title_model_draw(s16 *pos, s16 *rot, s32 model_index, s32 fade);
void title_seq_draw(TitleSeqTask *task) {
    TitleSeqRec *rec;

    rec = task->recs;
    title_seq_enable_set(0);
    title_seq_depth_set(10);
    { register s32 h __asm__("$3") = 0x100; gte_set_ctrl(H, h); }
    title_rec_select(1);
    title_model_draw((s16 *)&rec->unk_08, (s16 *)&rec[1].unk_08, title_seq_table_id, -0x1000);
    { register s32 h __asm__("$3") = 0x100; gte_set_ctrl(H, h); }
    title_seq_depth_set(-1);
    title_seq_enable_set(1);
}

extern u8 title_cursor_task[];
extern u8 title_highlight_task[];
extern u8 title_fade_data[];
void title_fade_update();  /* a function reached by pointer */
void title_fade_draw(TitleTaskRec *task);  /* a function reached by pointer */
void title_init_menu_ctls(void) {
    task_reset((TitleCtl *)title_cursor_task);
    task_set((TitleTaskRec *)title_cursor_task, 0, (s32)title_fade_update, (s32)title_fade_draw, (s32)title_fade_data);
    task_reset((TitleCtl *)title_highlight_task);
    task_set((TitleTaskRec *)title_highlight_task, 0, (s32)title_fade_update, (s32)title_fade_draw, (s32)title_fade_data);
}

/* Same code as rand_init_states (s01). */
void title_cursor_stop(void) {
    title_flag_test_set(&title_cursor_task);
    title_flag_test_set(&title_highlight_task);
}

extern TitleCursorPos *title_cursor_ptr;
extern u8 title_highlight_task[];
extern u8 title_cursor_task[];
/* Resets the title cursor record and sets its position from the two arguments. */
void title_cursor_set_pos(s16 x, s16 y) {
    TitleCursorPos *cur;

    cur = title_cursor_ptr;
    title_flag_test_set(title_highlight_task);
    cur->unk_00 = 0;
    cur->x = x;
    cur->unk_08 = 0;
    cur->unk_02 = 1;
    cur->y = y;
    task_start(0, title_cursor_task, 0);
}

extern TitleHighlight *title_highlight_ptr;
void title_highlight_set_pos(s16 x, s16 y) {
    TitleHighlight *rec;

    rec = title_highlight_ptr;
    title_flag_test_set(title_cursor_task);
    rec->unk_00 = 0x1000;
    rec->x = x;
    rec->unk_08 = x;
    rec->unk_02 = -1;
    rec->y = y;
    task_start(0, title_highlight_task, 0);
    title_input_lock();
}

void title_input_unlock(void);
void title_fade_update(TitleFadeTask *task) {
    TitleFadeRec *fade;

    fade = task->fade;
    if (task->phase != 0) {
        return;
    }
    fade->level = (fade->hold_frames << 12) / fade->period;
    if (fade->unk_02 != -1) {
        if (fade->unk_02 == 1) {
            fade->hold_frames++;
            if (fade->period < fade->hold_frames) {
                task->phase++;
            }
        }
    } else {
        fade->hold_frames--;
        if (fade->hold_frames < 0) {
            title_input_unlock();
            title_flag_test_set(task);
        }
    }
}

extern s32 title_cell_x_table[];
extern s32 title_cell_y_table[];
void title_fade_draw(TitleTaskRec *task) {
    TitleFadeParams *params = (TitleFadeParams *)task->param;
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 level = params->level;
    s32 c;
    s32 color;
    s32 edge_c;
    s32 edge;
    s32 i;
    u32 mode;
    TitleDrawCtx *mode_ctx;

    color = level / 16;
    c = MAX(MIN(color, 255), 0);
    color = c;
    color |= (c << 16) | (color << 8);
    switch (params->mode) {
    case 0:
        scratch_top[3] = 3;
        *(s32 *)(scratch_top + 4) = color;
        scratch_top[7] = 0x60;
        scratch_top[7] &= ~1;
        *(s16 *)(scratch_top + 8) = 0;
        *(s16 *)(scratch_top + 0xA) = 0;
        *(s16 *)(scratch_top + 0xC) = 320;
        *(s16 *)(scratch_top + 0xE) = 240;
        scratch_top[7] |= 2;
        addPrimA0A1(ctx->ot_base + 4, scratch_top);
        scratch_top += 0x10;
        break;
    case 1:
        edge = rcossin_tbl[(level / 4) & 0xFFF][0] / 16;
        edge_c = MAX(MIN(edge, 255), 0);
        edge = edge_c;
        edge |= (edge_c << 16) | (edge << 8);

        for (i = 0; i < 4; i++) {
            addPrimA0A1(ctx->ot_base + 4, scratch_top);
            *(s16 *)(scratch_top + 8) = title_cell_x_table[i];
            *(s16 *)(scratch_top + 0xA) = title_cell_y_table[i];
            *(s16 *)(scratch_top + 0x10) = title_cell_x_table[i] + 160;
            *(s16 *)(scratch_top + 0x12) = title_cell_y_table[i];
            *(s16 *)(scratch_top + 0x18) = title_cell_x_table[i];
            *(s16 *)(scratch_top + 0x1A) = title_cell_y_table[i] + 120;
            *(s16 *)(scratch_top + 0x20) = title_cell_x_table[i] + 160;
            *(s16 *)(scratch_top + 0x22) = title_cell_y_table[i] + 120;
            switch (i) {
            case 0:
                *(s32 *)(scratch_top + 4) = color;
                *(s32 *)(scratch_top + 0xC) = color;
                *(s32 *)(scratch_top + 0x14) = color;
                *(s32 *)(scratch_top + 0x1C) = edge;
                break;
            case 1:
                *(s32 *)(scratch_top + 4) = color;
                *(s32 *)(scratch_top + 0xC) = edge;
                *(s32 *)(scratch_top + 0x14) = color;
                *(s32 *)(scratch_top + 0x1C) = color;
                break;
            case 2:
                *(s32 *)(scratch_top + 4) = color;
                *(s32 *)(scratch_top + 0xC) = color;
                *(s32 *)(scratch_top + 0x14) = edge;
                *(s32 *)(scratch_top + 0x1C) = color;
                break;
            case 3:
                *(s32 *)(scratch_top + 4) = edge;
                *(s32 *)(scratch_top + 0xC) = color;
                *(s32 *)(scratch_top + 0x14) = color;
                *(s32 *)(scratch_top + 0x1C) = color;
                break;
            }

            scratch_top[7] = 0x38;
            scratch_top[3] = 8;
            scratch_top[7] |= 2;
            scratch_top += 0x24;
        }
        break;
    }
    mode = 0xE1000620;
    mode_ctx = title_draw_ctx_ptr;
    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = mode;
    addPrimA0A1(mode_ctx->ot_base + 4, scratch_top);
    scratch_top += 8;
}

s32 title_ring_build(s32 *p, s32 segArg);
extern u8 title_text_tpage[];
extern u16 D_800C6508[16];
extern u16 D_800D2EF0[16];
void title_cells_init();  /* a function reached by pointer */
void title_cells_update();  /* a function reached by pointer */
void title_seq_phase2();  /* a function reached by pointer */
extern u8 title_cells_task[];
extern s32 title_obj_base;
extern u8 D_80112110[];
extern u16 title_tpage_id;
extern u16 title_clut_id;
extern u16 title_clut_b_id;
void title_load_assets(void) {
    s32 prev;
    s32 i;

    title_tpage_id = sprite_load_tpage(title_text_tpage, 0, 0x100);
    title_clut_id = clut_load(D_800C6508, 0x20, 0xF0, 1, 1, 0x10);
    title_clut_b_id = clut_load(D_800D2EF0, 0x30, 0xF0, 1, 1, 0x10);

    for (i = 0; i < 6; i++) {
        prev = card_work_buf;
        card_work_buf = title_ring_build((s32 *)prev, i % 3);
        if (i == 0) {
            title_obj_base = sprite_sets_register((s32 *)prev, NULL, 0, 0, 0, 0);
        } else {
            sprite_sets_register((s32 *)prev, NULL, 0, 0, 0, 0);
        }
    }

    task_reset((struct TitleCtl *)title_cells_task);
    task_set((struct TitleTaskRec *)title_cells_task, (s32)title_cells_init, (s32)title_cells_update,
                  (s32)title_seq_phase2, (s32)D_80112110);
}

void title_circle_fill(s16 *out, s32 radius, s32 count, s32 step);
void title_orbit_table_fill(u8 *out, s32 count, s32 phaseStep);
void title_orbit_point(s16 *out, s32 value, s32 divisor, s32 index);
void title_ring_quad_build(s32 *out, s32 ring, s32 count, s32 seg, s32 segArg);
static inline u32 vec_length(s32 dx, s32 dy, s32 dz) {
    u32 value;
    s32 lzcr;
    s32 exp_shift;
    u32 table_idx;
    s32 half_shift;
    s16 *table;

    value = dx + dy + dz;
    table_idx = ~1; /* first the even mask for lzcr, then the table index */
    if (value != 0) {
        gte_set(LZCS, value);
        table = D_800BDB0C;
        gte_get(LZCR, lzcr);
        half_shift = 31 - lzcr;
        lzcr &= table_idx;
        exp_shift = lzcr - 24;
        table_idx = value << exp_shift;
        if (exp_shift < 0) {
            table_idx = value >> -exp_shift;
        }
        value = table[table_idx];
        half_shift >>= 1;
        value <<= half_shift;
        value >>= 12;
    }
    return value;
}
/*
 * Builds a ring's primitive list at p: a 16-point circle of 600,
 * the orbit table, then 16 orbit points each with 4 segment blocks.
 * The edge scale is the distance between the circle points at angles 0 and
 * 0x80. Returns the end pointer.
 */
s32 title_ring_build(s32 *p, s32 segArg) {
    s32 ax, ay, az, bx, bz;
    u32 value;
    s32 lzcr;
    s32 exp_shift;
    u32 table_idx;
    s32 half_shift;
    s16 *table;
    s32 scale;
    s32 ring, seg;

    ax = rcossin_tbl[0x80][0] * 600 / 4096;
    az = rcossin_tbl[0x80][1] * 600 / 4096;
    ay = *(s16 *)(D_801085E6 + 0x1FE) * 600 / 4096;
    bx = rcossin_tbl[0][0] * 600 / 4096;
    bz = rcossin_tbl[0][1] * 600 / 4096;
    ax -= bx;
    az -= bz;
    /* squared length, its root through LZCS/LZCR and the sqrt table */
    value = ax * ax + (0 - ay) * (0 - ay) + az * az;
    table_idx = ~1; /* first the even mask for lzcr, then the table index */
    if (value != 0) {
        gte_set(LZCS, value);
        table = D_800BDB0C;
        gte_get(LZCR, lzcr);
        half_shift = 31 - lzcr;
        lzcr &= table_idx;
        exp_shift = lzcr - 24;
        table_idx = value << exp_shift;
        if (exp_shift < 0) {
            table_idx = value >> -exp_shift;
        }
        value = table[table_idx];
        half_shift >>= 1;
        value <<= half_shift;
        value >>= 12;
    }
    scale = value;
    *p++ = 1;
    *p++ = 600;
    *p++ = 0x60;
    title_circle_fill((s16 *)p, 600, 0x10, 0x100);
    p += 0xC0;
    *p++ = 0x60;
    title_orbit_table_fill((u8 *)p, 0x10, 0x100);
    p += 0x60;
    *p++ = 0x10;
    for (ring = 0; ring < 0x10; ring++) {
        *p++ = 4;
        *p++ = scale;
        title_orbit_point((s16 *)p, 600, 0x10, ring);
        p += 2;
        for (seg = 0; seg < 4; seg++) {
            title_ring_quad_build(p, ring, 0x10, seg, segArg);
            p += 8;
        }
    }
    return (s32)p;
}

extern s16 title_seg_uv_table[][2];
void title_ring_quad_build(s32 *out, s32 ring, s32 count, s32 seg, s32 segArg) {
    s32 grid[9]; /* 3x3 vertex indices around the segment */
    s32 c0, c1, c3, c2; /* the quad's corner indices */
    s32 u, v;
    PrimTexLayout *prim;

    u = title_seg_uv_table[segArg][0];
    v = title_seg_uv_table[segArg][1];
    grid[0] = count * 4 + ring * 2;
    grid[1] = (count + ring) * 2;
    grid[2] = ring * 2;
    grid[3] = grid[0] + 1;
    grid[4] = grid[1] + 1;
    grid[5] = grid[2] + 1;
    grid[6] = grid[0] + 2;
    grid[7] = grid[1] + 2;
    grid[8] = grid[2] + 2;
    prim = (PrimTexLayout *)out;
    if (grid[6] >= count * 6) {
        grid[6] = count * 4;
    }
    if (grid[7] >= count * 4) {
        grid[7] = count * 2;
    }
    if (grid[8] >= count * 2) {
        grid[8] = 0;
    }
    switch (seg) {
    case 0:
        c0 = grid[0];
        c1 = grid[1];
        c3 = grid[4];
        c2 = grid[3];
        prim->uv[0] = u;
        prim->uv[1] = v;
        prim->uv[2] = u + 0x3F;
        prim->uv[3] = v;
        prim->uv[4] = u;
        prim->uv[5] = v + 0x3F;
        prim->uv[6] = u + 0x3F;
        prim->uv[7] = v + 0x3F;
        break;
    case 1:
        c0 = grid[1];
        c1 = grid[2];
        c3 = grid[5];
        c2 = grid[4];
        prim->uv[0] = u + 0x40;
        prim->uv[1] = v;
        prim->uv[2] = u + 0x7F;
        prim->uv[3] = v;
        prim->uv[4] = u + 0x40;
        prim->uv[5] = v + 0x3F;
        prim->uv[6] = u + 0x7F;
        prim->uv[7] = v + 0x3F;
        break;
    case 2:
        c0 = grid[3];
        c1 = grid[4];
        c3 = grid[7];
        c2 = grid[6];
        prim->uv[0] = u;
        prim->uv[1] = v + 0x40;
        prim->uv[2] = u + 0x3F;
        prim->uv[3] = v + 0x40;
        prim->uv[4] = u;
        prim->uv[5] = v + 0x7F;
        prim->uv[6] = u + 0x3F;
        prim->uv[7] = v + 0x7F;
        break;
    default:
        c0 = grid[4];
        c1 = grid[5];
        c3 = grid[8];
        c2 = grid[7];
        prim->uv[0] = u + 0x40;
        prim->uv[1] = v + 0x40;
        prim->uv[2] = u + 0x7F;
        prim->uv[3] = v + 0x40;
        prim->uv[4] = u + 0x40;
        prim->uv[5] = v + 0x7F;
        prim->uv[6] = u + 0x7F;
        prim->uv[7] = v + 0x7F;
        break;
    }
    prim->s[0] = c0 * 4;
    prim->s[4] = c0 * 4;
    prim->s[1] = c1 * 4;
    prim->s[5] = c1 * 4;
    prim->s[3] = c3 * 4;
    prim->s[7] = c3 * 4;
    prim->s[2] = c2 * 4;
    prim->s[6] = c2 * 4;
    prim->cmd = 0x4A000000;
    prim->clut = title_tpage_id;
    prim->tpage = title_clut_id;
}

/* Fills 3 rings of count*2 vertices (x, y, z; 8-byte stride) on a sphere of the given radius. */
void title_circle_fill(s16 *out, s32 radius, s32 count, s32 step)
{
    s32 ring;
    s32 i;
    s32 phase;
    s32 angle;

    angle = -step / 2;
    ring = 0;
    count *= 2;
    for (; ring < 3; ring++) {
        phase = 0;
        for (i = 0; i < count; i++) {
            out[1] = radius * rcossin_tbl[angle & 0xFFF][0] / 4096;
            out[0] = radius * rcossin_tbl[phase & 0xFFF][0] / 4096;
            out[2] = radius * rcossin_tbl[phase & 0xFFF][1] / 4096;
            out += 4;
            phase += 0x1000 / count;
        }
        angle += step / 2;
    }
}

/* Fills 3 rings of count * 2 byte triples (stride 4): x and y of points
   evenly spaced around the circle, then the ring's phase x. The phase
   starts at -phaseStep / 2 and advances by phaseStep per ring. */
void title_orbit_table_fill(u8 *out, s32 count, s32 phaseStep) {
    s32 phase;
    s32 ring;
    s32 angle;
    s32 i;
    s32 off;

    phase = -phaseStep / 2;
    for (ring = 0; ring < 3; ring++) {
        angle = 0;
        for (i = 0; i < count * 2; i++) {
            out[2] = (u16)rcossin_tbl[phase & 0xFFF][0] >> 6;
            off = (angle & 0xFFF) * 4;
            out[0] = *(const u16 *)((const char *)rcossin_tbl + off) >> 6;
            out[1] = *(const u16 *)(D_801085E6 + off) >> 6;
            out += 4;
            angle += 0x1000 / (count * 2);
        }
        phase += phaseStep;
    }
}

void title_orbit_point(s16 *out, s32 value, s32 divisor, s32 index) {
    s32 step;
    s32 pos;
    s32 x;
    s32 y;

    step = 0x1000 / divisor;
    pos = (step * index + step / 2) & 0xFFF;
    x = value * rcossin_tbl[pos][0];
    out[1] = 0;
    if (x < 0) {
        x += 0xFFF;
    }
    y = value * *(s16 *)(D_801085E6 + pos * 4);
    out[0] = x >> 12;
    if (y < 0) {
        y += 0xFFF;
    }
    out[2] = y >> 12;
}

extern s32 title_cells_active_flag;
extern u8 title_cell_table_a[];
extern u8 title_cell_table_b[];
extern u16 title_cell_table_c[22];
void title_base_set(s32 arg0);
void title_cells_init(TitleTaskRec *rec) {
    TitleCell *cell;
    s32 i;
    s32 t;
    s32 half;

    cell = (TitleCell *)rec->param;
    title_base_set(0);
    title_cells_active_flag = 1;
    for (i = 0, t = 0; i < 6; t += 8) {
        half = i / 2;
        i++;
        cell->unk_00 = 0;
        cell->unk_02 = 0;
        cell->unk_04 = 0;
        cell->rect_x = *(u16 *)(title_cell_table_a + t);
        cell->rect_y = *(u16 *)(title_cell_table_b + t);
        cell->rect_width = *(u16 *)((u8 *)title_cell_table_c + t);
        cell->unk_10 = 0;
        cell->unk_12 = half + 3;
        cell->unk_14 = 0;
        cell++;
    }
}

/* Six 0x18-byte records, starting at table + 0xC (u16 index 6): each record
 * adds three u16 lanes from the lanes 8 bytes later (u16 +4..+6). */
void title_cells_update(TitleTaskRec *rec) {
    s32 i;
    u16 *cur;

    cur = (u16 *)rec->param + 6;
    for (i = 0; i < 6; i++) {
        cur[i * 12 - 2] += cur[i * 12 + 2];
        cur[i * 12 - 1] += cur[i * 12 + 3];
        cur[i * 12] += cur[i * 12 + 4];
    }
}

void title_model_draw(s16 *pos, s16 *rot, s32 model_index, s32 fade);
void title_seq_phase2(TitleSeqTask *task) {
    TitleSeqRec *rec;
    s32 i;
    u8 *scratch;

    /* scratchpad 0x1F8003D8 block; slot 0x1C holds the 1..3 cycle value */
    scratch = (u8 *)0x1F8003D8;
    rec = task->recs;
    title_seq_enable_set(0);
    title_rec_select(0);
    title_item_select(0);
    title_scale_set(1);
    if (title_cells_active_flag == 0) {
        title_seq_flag_set(0);
    }
    for (i = 0; i < 6; i++) {
        *(s16 *)(scratch + 0x1C) = (i % 3) + 1;
        title_model_draw((s16 *)rec, (s16 *)&rec->unk_08, (s32)title_obj_base + i, 0xBB8);
        rec++;
    }
    title_seq_flag_set(1);
    *(s16 *)(scratch + 0x1C) = 0;
    title_scale_set(0);
    title_seq_enable_set(1);
}

extern u8 *title_ellipsoid_buf;
extern u8 *title_prim_table_b;
extern u8 *title_prim_entries_ptr;
void title_prim_tex_init(PrimTexLayout *p, s32 n);
/* Builds the title screen's object table in buf: a few header words, two
   sub-tables (title_ellipsoid_buf, title_prim_table_b), then 16 entries of 0x20 bytes
   initialised by title_prim_tex_init. Returns the end of the table. */
u8 *title_build_prim_table(u8 *buf) {
    u8 *p;
    s32 i;

    p = buf;
    *(s32 *)p = 1;
    p += 4;
    *(s32 *)p = 0x320;
    p += 4;
    *(s32 *)p = 0x20;
    p += 4;
    title_ellipsoid_buf = p;
    p += 0x100;
    *(s32 *)p = 0x20;
    p += 4;
    title_prim_table_b = p;
    p += 0x80;
    *(s32 *)p = 1;
    p += 4;
    *(s32 *)p = 0x10;
    p += 4;
    *(s32 *)p = 0x320;
    p += 4;
    *(s16 *)(p + 0) = 0;
    *(s16 *)(p + 2) = 0;
    *(s16 *)(p + 4) = 0;
    p += 8;
    i = 0;
    title_prim_entries_ptr = p;
    do {
        title_prim_tex_init((PrimTexLayout *)p, i);
        i++;
        p += 0x20;
    } while (i < 0x10);
    return p;
}

extern u16 title_tpage_id;
extern u16 title_clut_b_id;
void title_prim_tex_init(PrimTexLayout *p, s32 n) {
    s32 a;
    u32 v;

    a = n + 1;
    p->s[0] = n * 4;
    p->s[4] = n * 4;
    p->clut = title_tpage_id;
    p->tpage = title_clut_b_id;
    if (a == 0x10) {
        a = 0;
    }
    p->s[1] = a * 4;
    p->s[5] = a * 4;
    a = n + 0x10;
    p->s[2] = a * 4;
    p->s[6] = a * 4;
    a = n + 0x11;
    if (a == 0x20) {
        a = 0x10;
    }
    p->s[3] = a * 4;
    p->s[7] = a * 4;
    n %= 3;
    switch (n) {
    case 0:
        v = 0xE2000210;
        break;
    case 1:
        v = 0xE2004210;
        break;
    default:
        v = 0xE2080210;
        break;
    }
    v &= 0xFFFFFF;
    v |= 0x42000000;
    p->cmd = v;
}

/* Fills 2 rings of 16 vertices (x, y, z; 8-byte stride) on an ellipsoid. */
void title_ellipsoid_fill(s16 *out, TitleRingParams *params)
{
    s32 ring;
    s32 i;
    s32 phase;
    s32 angle;
    s32 y;
    s32 radius;
    s32 radius_x;
    s32 radius_y;

    ring = 0;
    phase = params->phase;
    radius_x = params->radius_x;
    radius_y = params->radius_y;
    for (; ring < 2; ring++) {
        angle = 0;
        y = radius_x * rcossin_tbl[phase & 0xFFF][0] / 4096;
        radius = radius_y * rcossin_tbl[phase & 0xFFF][1] / 4096;
        for (i = 0; i < 16; i++) {
            out[1] = y;
            out[0] = radius * rcossin_tbl[angle & 0xFFF][0] / 4096;
            out[2] = radius * rcossin_tbl[angle & 0xFFF][1] / 4096;
            angle += 0x100;
            out += 4;
        }
        phase += params->phase_step;
    }
}

void title_trig_shade_fill(u8 *out, s16 *params)
{
    s32 row;
    s32 col;
    s32 x;
    s32 y;
    u8 *p;
    u8 shade;
    s32 i;

    y = params[0x14 / 2];
    for (row = 0; row < 2; row++) {
        x = 0;
        col = 0;
        shade = (u16)rcossin_tbl[y & 0xFFF][0] >> 6;
        p = out + 1;
        for (; col < 16; col++) {
            i = x & 0xFFF;
            x += 0x100;
            p[1] = shade;
            out[0] = (u16)rcossin_tbl[i][0] >> 6;
            p[0] = (u16)rcossin_tbl[i][1] >> 6;
            p += 4;
            out += 4;
        }
        y += params[0x18 / 2];
    }
}

extern u8 title_waves_task[];
extern s32 title_prim_table_id;
void title_waves_init(void);
void title_waves_update(void);
void title_waves_draw(void);
void title_prims_init(void) {
    s32 buf = card_work_buf;

    card_work_buf = (s32)title_build_prim_table((u8 *)buf);
    title_prim_table_id = sprite_sets_register((s32 *)buf, NULL, 0, 0, 0, 0);
    task_reset((TitleCtl *)title_waves_task);
    task_set((TitleTaskRec *)title_waves_task, (s32)title_waves_init, (s32)title_waves_update, (s32)title_waves_draw, 0);
}

extern TitleWaveBand title_wave_bands[];
int rand(void);
void title_waves_init(void) {
    TitleWaveBand *wave;
    s32 i;
    s32 j;
    s32 r; /* rand() kept apart so 0x180 goes through j: a real mult */

    title_cells_active_flag = 0;
    wave = title_wave_bands;
    for (i = 0; i < 2; i++, wave++) {
        wave->unk_00 = 0;
        wave->offset_speed = -4;
        wave->scroll_v_speed = i + 2;
        wave->phase = i << 10;
        wave->unk_18 = 0x80;
        wave->phase_speed = 4;
        wave->offset = 0;
        wave->unk_04 = 0;
        wave->unk_08 = 0;
        wave->unk_0C = 0;
        wave->scroll_v = 0;
        wave->unk_1C = 0x320;
        wave->unk_1E = i * 0x200 + 0x4B0;
        for (j = 0; j < 16; j++) {
            wave->tex_u[j] = (j % 2) << 7;
        }
        r = rand();
        j = 0x180;
        wave->flash_timer = r * j / 0x7FFF + j;
    }
}

/* value / 16 clamped to 0..255 */
u8 title_level_scale(s32 value)
{
    u8 level;

    value /= 16;
    level = value < 256 ? value : 255;
    if ((value < 256 ? value : 255) < 0) {
        level = 0;
    }
    return level;
}

void title_entries_reset_to(u32 packed_ids, s16 value);
void title_waves_update(void) {
    TitleWaveBand *wave;
    s32 i;
    s32 r;
    s32 range;

    wave = title_wave_bands;
    for (i = 0; i < 2; i++, wave++) {
        wave->phase += wave->phase_speed;
        wave->offset += wave->offset_speed;
        if (i == 0) {
            if (wave->flash_timer == 0) {
                title_entries_reset_to(0xF10FF, title_level_scale(rand() * 4096 / 0x7FFF));
                r = rand();
                range = 0x300;
                wave->flash_timer = r * range / 0x7FFF + 0x100;
            }
            wave->flash_timer--;
        }
        wave->scroll_v = (wave->scroll_v + wave->scroll_v_speed) % 64;
    }
}

static const Hdr8 hdr_zero = {{0}};
void title_waves_draw(void) {
    Hdr8 hdr;
    TitleWaveBand *band;
    u8 *out;
    s32 row;
    s32 i;
    s32 val;
    s32 level;

    band = title_wave_bands;
    hdr = hdr_zero;
    title_seq_enable_set(0);
    title_seq_depth_set(0x7F);
    title_rec_select(1);
    title_scale_set(1);
    for (row = 0; row < 2; row++) {
        level = band->scroll_v;
        out = title_prim_entries_ptr;
        for (i = 0; i < 16; i++) {
            val = band->tex_u[i];
            out[0x10] = val;
            out[0x11] = level;
            out[0x12] = val + 0x7F;
            out[0x13] = level;
            out[0x14] = val;
            out[0x15] = level + 0x40;
            out[0x16] = val + 0x7F;
            out[0x17] = level + 0x40;
            out += 0x20;
        }
        title_ellipsoid_fill((s16 *)title_ellipsoid_buf, (TitleRingParams *)band);
        title_model_draw((s16 *)&hdr, (s16 *)band, title_prim_table_id, -0x800);
        band++;
    }
    title_scale_set(0);
    title_seq_depth_set(-1);
    title_seq_enable_set(1);
}

extern u8 title_image_a[];
extern u8 title_image_b[];
extern u16 title_clut_a[16];
extern u16 D_800D2ED0[16];
extern s32 title_track_init_a[];
extern s32 title_track_init_b[];
extern s32 title_ring_a_cells_init[];
extern s32 title_ring_b_two_line_cells_init[];
extern s32 title_ring_b_one_line_cells_init[];
extern s32 title_ring_model_base;
extern s32 title_track_count;
extern s32 title_track_xs[];
extern s32 title_track_curves[][8];
extern s32 card_work_buf;
extern u8 title_ring_b_task[];
extern u8 title_label_ctl[];
extern u8 D_801122D4[];
extern u8 D_801122FC[];
extern u8 D_80112324[];
extern u8 title_text_ctl[];
extern u8 title_pad3d_ctl[];
extern u8 title_obj_ctl[];
extern u8 title_menu_ctl[];
extern u8 title_scene_task[];
extern u8 title_exit_ctl[];
extern u8 title_block_ctl[];
extern TitleAnimRatio title_ring_a;
extern TitleAnimRatio title_anim_ratio_alt;
extern s16 D_80112406;
extern s16 D_8011241C;
extern s16 title_menu_item_count;
extern u16 title_glyph_tpage[];
extern u16 title_clut_b[];
extern u16 title_glyph_clut[];
extern u16 title_tpage_b[];

extern Pad3dSoundInfo *title_shared_state_get(void);
s32 sprite_load_tpage(void *sprite, s32 x, s32 y);
s32 clut_load(void *sprite, s32 x, s32 y, s32 a3, s32 a4, s32 a5);
void panel_init(void);
void menu_quads_init(void);
s32 title_cell_table_build(s32 buf);
s32 sprite_sets_register(s32 *data, u16 *clut, u16 tpage, u16 clutDefault, s32 xoff, s32 yoff);
void task_reset(TitleCtl *ctl);
void task_set(TitleTaskRec *rec, s32 a1, s32 a2, s32 a3, s32 a4);
void title_scene_track_init(TitleSceneTrack *, void *, s32, s32, s32, s32);
s32 panel_is_two_lines(void);
void title_labels_init(void);
void pad3d_init(void);
void title_obj_init(TitleCtl *ctl);
void title_text_init(void *task);
void title_block_init(TitleCtl *ctl);
void title_exit_init(void *);
void title_menu_begin(TitleCtl *ctl);
void title_base_set(s32 arg0);
void title_anim_ratio_init(TitleAnimRatioOwner *outer);
void title_menu_task_update(TitleMenuNode *task);
void title_anim_ratio_draw(TitleAnimRatioOwner *owner);

void title_scene_init(void) {
    Pad3dSoundInfo *info;
    s32 i;
    s32 prev;
    s32 three;
    s32 four;
    TitleAnimRatio *s;

    info = title_shared_state_get();
    title_glyph_clut[0] = sprite_load_tpage(title_image_a, 0x140, 0x100);
    title_tpage_b[0] = sprite_load_tpage(title_image_b, 0x180, 0x100);
    title_glyph_tpage[0] = clut_load(title_clut_a, 0, 0xF0, 1, 1, 0x10);
    title_clut_b[0] = clut_load(D_800D2ED0, 0x10, 0xF0, 1, 1, 0x10);
    panel_init();
    menu_quads_init();
    prev = card_work_buf;
    card_work_buf = title_cell_table_build(prev);
    title_ring_model_base = sprite_sets_register((s32 *)prev, NULL, 0, 0, 0, 0);
    title_track_count = 4;
    i = 0;
    four = 4;
    three = 3;
    FAKE_OPAQUE(four);
    FAKE_OPAQUE(three);
    do {
        title_track_xs[i] = (i << 12) / three;
        title_track_curves[0][i] = title_track_init_a[i];
        title_track_curves[1][i] = title_track_init_b[i];
        i++;
    } while (i < four);

    s = &title_ring_a;
    task_reset((TitleCtl *)title_scene_task);
    task_set((TitleTaskRec *)title_scene_task, (s32)title_anim_ratio_init, (s32)title_menu_task_update, (s32)title_anim_ratio_draw, (s32)s);
    D_80112406 = 5;
    D_8011241C = 0x40;
    i = 0;
    do {
        s->item_cells[i] = title_ring_a_cells_init[i];
        i++;
    } while (i < s->item_count);
    s->base_radius = 0x6E;
    if (info->unk_08 == 1) {
        s->selected_index = 1;
    } else {
        s->selected_index = 0;
    }
    s->center_y = 0x40;
    s->brightness = 0x1000;
    s->unk_38 = 0x1C;
    s->offset_x = 0xA0;
    s->tilt = 0;
    s->angle = 0;
    s->unk_0C = 0;
    s->center_x = 0;
    s->unk_16 = 0;
    s->unk_AC = 0;
    s->offset_y = 0x60;
    s->center_z = s->base_radius + 0x200;
    s->unk_10 = 0x1000 / (s->item_count * 16);
    title_scene_track_init(&s->tracks[0], title_block_ctl, 5, 0, 0, 0);
    title_scene_track_init(&s->tracks[1], title_exit_ctl, 6, 0, 0, 0);
    title_scene_track_init(&s->tracks[2], title_ring_b_task, 0, 3, 1, 1);
    title_scene_track_init(&s->tracks[3], title_text_ctl, 3, 3, 0, 2);
    title_scene_track_init(&s->tracks[4], title_obj_ctl, 1, 4, 0, 1);
    title_scene_track_init(&s->tracks[8], 0, -1, 0, 0, 0);

    s = &title_anim_ratio_alt;
    task_reset((TitleCtl *)title_ring_b_task);
    task_set((TitleTaskRec *)title_ring_b_task, (s32)title_anim_ratio_init, (s32)title_menu_task_update, (s32)title_anim_ratio_draw, (s32)s);
    if (panel_is_two_lines() == 1) {
        title_menu_item_count = 7;
        i = 0;
        do {
            s->item_cells[i] = title_ring_b_two_line_cells_init[i];
            i++;
        } while (i < s->item_count);
        title_scene_track_init(&s->tracks[0], title_scene_task, 1, 1, 2, 3);
        title_scene_track_init(&s->tracks[1], title_pad3d_ctl, 2, 0, 0, 2);
        title_scene_track_init(&s->tracks[2], title_label_ctl, 2, 0, 0, 2);
        title_scene_track_init(&s->tracks[3], D_801122D4, 2, 0, 0, 2);
        title_scene_track_init(&s->tracks[4], D_801122FC, 2, 0, 0, 2);
        title_scene_track_init(&s->tracks[5], D_80112324, 2, 0, 0, 2);
        title_scene_track_init(&s->tracks[6], title_menu_ctl, 4, 0, 2, 2);
        title_scene_track_init(&s->tracks[8], title_scene_task, 1, 1, 2, 3);
        s->unk_10 = 0x1000 / (s->item_count * 15);
        s->base_radius = 0x94;
    } else {
        title_menu_item_count = 6;
        i = 0;
        do {
            s->item_cells[i] = title_ring_b_one_line_cells_init[i];
            i++;
        } while (i < s->item_count);
        title_scene_track_init(&s->tracks[0], title_scene_task, 1, 1, 2, 3);
        title_scene_track_init(&s->tracks[1], title_pad3d_ctl, 2, 0, 0, 2);
        title_scene_track_init(&s->tracks[2], title_label_ctl, 2, 0, 0, 2);
        title_scene_track_init(&s->tracks[3], D_801122FC, 2, 0, 0, 2);
        title_scene_track_init(&s->tracks[4], D_80112324, 2, 0, 0, 2);
        title_scene_track_init(&s->tracks[5], title_menu_ctl, 4, 0, 2, 2);
        title_scene_track_init(&s->tracks[8], title_scene_task, 1, 1, 2, 3);
        s->unk_10 = 0x1000 / (s->item_count * 15);
        s->base_radius = 0x8A;
    }
    s->unk_38 = 0x1C;
    s->unk_AC = 1;
    s->offset_x = 0xA0;
    {
        register s32 width asm("$3") = 0x40;
        s->width = width;
        s->center_y = width;
    }
    s->selected_index = 0;
    s->tilt = 0;
    s->angle = 0;
    s->unk_0C = 0;
    s->unk_16 = 0;
    s->brightness = 0;
    s->center_x = 0;
    s->offset_y = 0x48;
    s->center_z = s->base_radius + 0x200;
    title_labels_init();
    pad3d_init();
    title_obj_init((TitleCtl *)title_obj_ctl);
    title_text_init(title_text_ctl);
    title_block_init((TitleCtl *)title_block_ctl);
    title_exit_init(title_exit_ctl);
    title_menu_begin((TitleCtl *)title_menu_ctl);
    title_base_set(0);
}

extern s32 title_base;

void title_base_set(s32 arg0) {
    title_base = arg0;
}

extern s32 title_base;

s32 title_base_get(void) {
    return title_base;
}

extern s32 title_track_count;
extern s32 title_track_xs[];
extern s32 title_track_curves[][8];
s32 title_track_sample(s32 x, s32 n, s32 *xs, u8 *table_entry);
/* Stores a computed value into the two fields at 0x54 and 0x58 of the
   record returned by title_rec_get(0). index selects a 32-byte entry of
   title_track_curves. */
void title_rec_store_value(s32 slot, s32 index) {
    s32 value;
    u8 *rec;

    rec = title_rec_get(0);
    value = title_base + title_track_sample(slot, title_track_count, title_track_xs, (u8 *)title_track_curves[index]);
    *(s32 *)(rec + 0x54) = value;
    *(s32 *)(rec + 0x58) = value;
}

/* Sets up one track slot. When title_is_t_build() is 1 (a 'T' build), only title_block_ctl is kept as the slot's data;
 * other data pointers are cleared. */
void title_scene_track_init(TitleSceneTrack *track, void *data, s32 a, s32 b, s32 c, s32 d) {
    if (title_is_t_build() == 1 && data != title_block_ctl) {
        track->data = 0;
    } else {
        track->data = data;
    }
    track->unk_04 = a;
    track->unk_08 = b;
    track->unk_0A = c;
    track->unk_06 = d;
}

void title_anim_ratio_init(TitleAnimRatioOwner *outer) {
    TitleAnimRatio *r = outer->inner;
    s32 ratio = (r->selected_index << 12) / r->item_count;
    r->unk_16 = 0;
    r->unk_14 = 0;
    r->tilt = 0;
    r->radius = r->base_radius;
    r->angle = ratio;
    r->target_angle = ratio;
}

/* Steps a dial menu one entry per press (or per held repeat after `repeat`
 * frames), animates angle toward the target; returns the index once settled, else -1. */
s32 title_menu_scroll(TitleMenuRec *r, s32 repeat, s32 limit, s32 sound)
{
    u32 *pad = title_get_pad_state();
    s32 idx;
    s32 count;
    u32 ids;

    if (repeat != 0 ? ((u16)pad[5] >= repeat && r->speed == 0) || ((pad[1] & 0x2000) && r->speed <= 0)
                    : (pad[0] & 0x2000) && r->speed <= 0) {
        if (r->speed == 0) {
            if (limit != 0 && (s16)r->selected_index + 1 >= r->period) {
                goto done;
            }
            if (r->speed == 0) {
                ids = 0x40000;
                if (!sound) {
                    ids = 0x50000;
                }
                title_entries_reset(ids | 0xFFFF);
            }
        }
        r->target_angle += 0x1000 / r->period;
        r->speed = r->step_speed;
        idx = (s16)r->selected_index;
        if (++idx >= r->period) {
            idx = 0;
        }
        r->selected_index = idx;
    } else if (repeat != 0 ? ((u16)pad[6] >= repeat && r->speed == 0) || ((pad[1] & 0x8000) && r->speed >= 0)
                           : (pad[0] & 0x8000) && r->speed >= 0) {
        if (r->speed == 0) {
            if (limit != 0 && (s16)r->selected_index == limit) {
                goto done;
            }
            if (r->speed == 0) {
                ids = 0x40000;
                if (!sound) {
                    ids = 0x50000;
                }
                title_entries_reset(ids | 0xFFFF);
            }
        }
        r->target_angle -= 0x1000 / r->period;
        r->speed = -r->step_speed;
        idx = (s16)r->selected_index;
        count = r->period;
        if (--idx < 0) {
            idx = count - 1;
        }
        r->selected_index = idx;
    }
    if (r->speed > 0) {
        r->angle += r->speed;
        if (r->angle >= r->target_angle) {
            goto settle;
        }
    }
    if (r->speed < 0) {
        r->angle += r->speed;
        if (r->angle <= r->target_angle) {
            goto settle;
        }
    }
    goto done;
settle:
    r->speed = 0;
    r->target_angle = r->angle = ((s16)r->selected_index << 12) / r->period;
done:
    if (r->speed != 0) {
        return -1;
    }
    return (s16)r->selected_index;
}

void title_anim_update(TitleCtl *ctl);
void title_fade_in_update(TitleFadeInObj *obj);
void title_fade_out_update(TitleFadeOutObj *obj);
void title_slide_update(TitleAnimObj *obj);
void title_timed_ramp_update(TitleFadeInObj *obj);
void title_menu_task_update(TitleMenuNode *task) {
    TitleFxState *fx = (TitleFxState *)task->menu;
    u32 *input = title_get_pad_state(task);
    TitleSoundModeView *mode = (TitleSoundModeView *)&title_shared_state_get()->unk_24;
    s32 sel;
    TitleMenuChoice *choice;
    TitleMenuRec *target;

    switch (task->phase) {
    case 0:
        fx->step = 0;
        task->phase++;
        /* fallthrough */
    case 1:
        if (task->mode != 1) {
            title_anim_update((TitleCtl *)task);
        } else {
            title_fade_in_update((TitleFadeInObj *)task);
        }
        break;
    case 2:
        if (task->child == 0 || task->child->state != 1) {
            title_pad_clear();
            input[0] = title_input_mask() | title_input_step();
            task->phase++;
        }
        break;
    case 3:
        sel = title_menu_scroll((TitleMenuRec *)fx, 0, 0, 0);
        if (sel == -1) {
            break;
        }
        if (input[1] & title_input_mask()) {
            choice = &fx->choices[sel];
            if (choice->task == 0) {
                title_entries_reset(0x3FFFF);
                break;
            }
            title_transition_start(choice->fx_kind, choice->effect_a, choice->effect_b);
            switch ((s16)(choice->kind - 2)) {
            case 0:
                choice->task->menu->unk_02 = fx->choice_values[sel];
                task_start((s32)task, choice->task, 0);
                task->mode = 1;
                break;
            case 1:
                task_start((s32)task, choice->task, 0);
                task->mode = 2;
                break;
            case 2:
                task_start((s32)task, choice->task, 0);
                task->mode = 1;
                break;
            case 3:
                task_start((s32)task, choice->task, 0);
                if (mode->unk_94 != 0) {
                    task->mode = 2;
                } else {
                    task->mode = -1;
                }
                break;
            case 4:
                task_start((s32)task, choice->task, 0);
                task->mode = -1;
                break;
            default:
                target = choice->task->menu;
                task_start((s32)task, choice->task, 0);
                fx->direction = choice->kind;
                if (target->unk_AC == 1) {
                    target->unk_AE = fx->choice_values[sel];
                }
                task->mode = 0;
                break;
            }
            fx->step = 0;
            task->phase++;
            fx->rec_index = 2;
            fx->progress = 0;
            fx->fade_counter = fx->fade_frames;
        } else if ((input[1] & title_input_step()) && fx->back_task != 0) {
            title_transition_start(fx->back_fx_kind, fx->back_effect_a, fx->back_effect_b);
            task_start((s32)task, fx->back_task, 0);
            task->mode = 0;
            fx->step = 0;
            task->phase++;
            fx->direction = fx->back_kind;
        }
        break;
    case 4:
        switch (task->mode) {
        case -1:
            task->phase = 10;
            break;
        case 0:
            title_fx_update(task, fx);
            break;
        case 1:
            title_fade_out_update((TitleFadeOutObj *)task);
            break;
        case 2:
            title_slide_update((TitleAnimObj *)task);
            break;
        case 3:
            title_timed_ramp_update((TitleFadeInObj *)task);
            break;
        }
        break;
    case 5:
        title_flag_test_set(task);
        break;
    case 10:
        break;
    }
}

void title_logo_start(s16 value74, s16 value04);
void title_rec_set_y(s32 value);
void title_panel_start(s32 value_10, s32 value_0C);
void title_transition_start(s32 kind, s32 effect_a, s32 effect_b) {
    s32 side;

    switch (kind) {
    case 1:
        logo_show(0, 0x28, 0x22);
        side = 1;
        goto tail_a;
    case 2:
        logo_show(1, 0x28, 0x22);
        side = 0;
tail_a:
        title_panel_open(side, 0x28, 0x22);
        title_rec_place(0x28, 0x22);
        goto second;
    case 3:
        title_logo_start(1, 0x13);
        logo_hide(0, 0x13);
        goto tail_b;
    case 4:
        logo_hide(1, 0x13);
        title_logo_start(0, 0x13);
        goto tail_b;
    default:
        goto second;
    }
tail_b:
    title_rec_set_y(0x13);
second:
    switch (effect_a) {
    case 1:
        panel_show(0x32, 8);
        break;
    case 2:
        title_panel_start(0, 6);
        break;
    }

    switch (effect_b) {
    case 1:
        title_entries_reset(0x17FFFF);
        break;
    case 2:
        title_entries_reset(0x18FFFF);
        break;
    case 3:
        title_entries_reset(0x19FFFF);
        break;
    }
}

void title_anim_update(TitleCtl *ctl) {
    struct TitleAnim *anim = ctl->anim;
    s16 step;

    switch (anim->state) {
    case 0:
        anim->unk_2E = 3;
        if (ctl->unk_18 == 0) {
            anim->progress = 0x1000;
            anim->state = 0;
            anim->unk_34 = anim->base;
            ctl->step++;
            return;
        }
        anim->progress = 0;
        anim->unk_3A = 0;
        anim->unk_34 = anim->base + anim->frame_count * 12;
        if (ctl->unk_24 == 2) {
            anim->state = 2;
            return;
        }
        anim->unk_AA = 0;
        anim->state++;
        return;
    case 1:
        anim->unk_AA++;
        if ((s16)anim->unk_AA < 0x40 - anim->frame_count) {
            return;
        }
        anim->state++;
        /* fall through */
    case 2:
        if (anim->unk_3A < anim->frame_count) {
            step = anim->unk_3A + 1;
            anim->unk_3A = step;
            anim->unk_34 -= 12;
            anim->progress = ((s32)(step << 16) >> 4) / anim->frame_count;
            return;
        }
        ctl->step++;
        break;
    }
}

void title_fade_in_update(TitleFadeInObj *obj) {
    TitleFadeInData *d = obj->data;

    switch (d->state) {
    case 0:
        d->rec_index = 3;
        d->tilt = 0x400;
        d->brightness = 0;
        d->count = 0;
        d->radius = d->base_radius;
        d->state++;
        break;
    case 1:
        if (d->count < 0xF) {
            d->count++;
            d->brightness = (d->count << 12) / 15;
            d->tilt = 0x400 - (d->count << 10) / 15;
        } else {
            obj->step++;
        }
        break;
    }
}

void title_fx_update(TitleMenuNode *task, TitleFxState *fx) {
    TitleRecAddrs *rec0;
    TitleRecAddrs *rec;
    s32 offset;

    switch (fx->step) {
    case 0:
        fx->rec_index = 2;
        fx->fade_scale = 0x1000;
        fx->progress = 0;
        fx->fade_counter = fx->fade_frames;
        fx->step++;
        /* fallthrough */
    case 1:
        if ((s16)fx->fade_counter >= 0) {
            fx->fade_scale = (s16)(((s16)fx->fade_counter << 12) / (s16)fx->fade_frames);
            fx->unk_34 = fx->unk_34 + 0xC;
            fx->fade_counter = fx->fade_counter - 1;
        }
        rec0 = title_rec_get(0);
        rec = title_rec_get(fx->rec_index);
        offset = title_track_sample(fx->progress, title_track_count, title_track_xs,
                          (u8 *)title_track_curves[fx->direction]);
        rec0->unk_54 = title_base + offset;
        rec0->unk_58 = title_base + offset;
        rec->unk_54 = offset;
        rec->unk_58 = offset;
        fx->progress += 0x1000 / fx->duration_frames;
        if ((s16)fx->progress > 0x1000) {
            fx->step++;
        }
        break;
    case 2:
        rec = title_rec_get(fx->rec_index);
        rec->unk_54 = 0;
        rec->unk_58 = 0;
        if (fx->direction == 0) {
            title_base += 0xFFC00000;
        } else {
            title_base += 0x400000;
        }
        task->phase++;
        break;
    }
}

void title_fade_out_update(TitleFadeOutObj *obj) {
    TitleFadeOutData *d = obj->data;

    switch (d->state) {
    case 0:
        d->fade_ratio = 0x1000;
        d->count = 0xF;
        d->unk_08 = 0;
        d->unk_34 = d->unk_18;
        d->state++;
        break;
    case 1:
        if (d->count >= 0) {
            d->fade_ratio = (d->count << 12) / 15;
            d->count--;
            d->unk_08 = 0x400 - (d->count << 10) / 15;
        } else {
            obj->step++;
        }
        break;
    }
}

void title_slide_update(TitleAnimObj *obj) {
    TitleAnimState *anim;
    u16 remaining;

    anim = obj->anim;
    switch (anim->step) {
    case 0:
        anim->unk_2E = 2;
        anim->counter = 0x1C;
        anim->step = anim->step + 1;
        return;
    case 1:
        anim->unk_36 = (anim->counter << 12) / 28;
        remaining = anim->counter - 1;
        anim->counter = remaining;
        anim->unk_34 = anim->unk_34 + 0xC;
        if ((s16)remaining < 0) {
            obj->step = obj->step + 1;
        }
        return;
    }
}

void title_timed_ramp_update(TitleFadeInObj *obj) {
    TitleFadeInData *d = obj->data;

    switch (d->state) {
    case 0:
        d->rec_index = 2;
        d->count = 0xC;
        d->state++;
        break;
    case 1:
        d->brightness = ((s32)(d->count << 12)) / 12;
        d->radius += 0xC;
        d->count--;
        if (d->count < 0) {
            obj->step++;
        }
        break;
    }
}

/* Draws the unk_1A items of a ring (center unk_00..unk_04, tilt unk_08, spin unk_0A,
 * radius unk_34) at brightness unk_36, then the menu quad if unk_AC == 1. */
void title_anim_ratio_draw(TitleAnimRatioOwner *owner) {
    TitleAnimRatio *ring = owner->inner;
    s32 bright = ring->brightness;
    s32 i;
    s32 tilt;
    s32 radius;
    s16 pos[4];
    s16 rot[4];

    if (bright == 0) {
        return;
    }
    title_seq_enable_set(0);
    { register s32 h __asm__("$8") = 0x200; gte_set_ctrl(H, h); }
    {
        s32 ofx = ring->offset_x;
        s32 ofy = ring->offset_y;
        ofx <<= 16;
        gte_set_ctrl(OFX, ofx);
        ofy <<= 16;
        gte_set_ctrl(OFY, ofy);
    }
    i = 0;
    title_rec_select(ring->rec_index);
    title_item_select(1);
    tilt = ring->tilt;
    radius = (s16)ring->radius;
    for (i = 0; i < ring->item_count; i++) {
        s32 angle;
        s32 step;
        s32 y;
        s32 x;
        s32 r;

        step = (i << 12) / ring->item_count;
        step -= 0x800;
        angle = ring->angle - step;

        x = ring->center_x + (radius * rcossin_tbl[angle & 0xFFF][0]) / 0x1000;
        if (tilt != 0) {
            r = (radius * rcossin_tbl[angle & 0xFFF][1]) / 0x1000;
            y = ring->center_y - (r * rcossin_tbl[tilt & 0xFFF][0]) / 0x1000;
            r = ring->center_z + (r * rcossin_tbl[tilt & 0xFFF][1]) / 0x1000;
        } else {
            y = ring->center_y;
            r = ring->center_z + (radius * rcossin_tbl[angle & 0xFFF][1]) / 0x1000;
        }
        rot[1] = angle + 0x800;
        pos[0] = x;
        pos[1] = y;
        pos[2] = r;
        rot[0] = tilt;
        rot[2] = 0;
        if (bright == 0x1000) {
            title_seq_flag_set(0);
            title_model_draw(pos, rot, title_ring_model_base + ring->item_cells[i], 0x1000);
            title_seq_flag_set(1);
        } else {
            title_model_draw(pos, rot, title_ring_model_base + ring->item_cells[i], bright);
        }
    }
    { register s32 h __asm__("$8") = 0x100; gte_set_ctrl(H, h); }
    { register s32 v __asm__("$8") = 0xA00000; gte_set_ctrl(OFX, v); }
    { register s32 v __asm__("$8") = 0x780000; gte_set_ctrl(OFY, v); }
    title_seq_enable_set(1);
    if (ring->unk_AC == 1) {
        title_menu_quad_draw(12, 16, 24, ring->quad_index, ring->brightness != 0x1000, ring->brightness, 1);
    }
}

extern u8 title_label_ctl[];
extern u8 D_80112554[];
extern u8 D_801122D4[];
extern u8 D_8011259C[];
extern u8 D_801122FC[];
extern u8 D_801125E4[];
extern u8 D_80112324[];
extern u8 D_8011262C[];
extern u8 title_pad3d_ctl[];
void title_pad3d_update(TitleTaskNode *node);  /* a function reached by pointer */
void title_pos_draw();  /* a function reached by pointer */
extern u8 title_pad3d_rec[];
extern s16 D_80112678;
extern s16 D_8011267C;
extern s32 D_80112684;
void title_label_index_init(void *ctl, TitleLabel *label, s16 x, s16 y, s32 index);
void title_label_init(void *ctl, TitleLabel *label, s16 x, s16 y, s32 mode, s32 offset);
/* Title screen layout: four labels (x, y, mode), the control block at
   title_pad3d_ctl reset and filled, then two 0xF fields and the base height
   from title_shared_state_get plus 0x28. */
void title_labels_init(void) {
    s32 base_y;

    base_y = (s32)title_shared_state_get();
    title_label_init(title_label_ctl, (TitleLabel *)D_80112554, 0x16, 0x14, 0x18, 0);
    title_label_index_init(D_801122D4, (TitleLabel *)D_8011259C, 0x1E, 0x1C, 1);
    title_label_index_init(D_801122FC, (TitleLabel *)D_801125E4, 0x24, 0x26, 2);
    title_label_index_init(D_80112324, (TitleLabel *)D_8011262C, 0x24, 0x26, 3);
    task_reset((TitleCtl *)title_pad3d_ctl);
    task_set((TitleTaskRec *)title_pad3d_ctl, 0, (s32)title_pad3d_update, (s32)title_pos_draw, (s32)title_pad3d_rec);
    D_80112678 = 0xF;
    D_8011267C = 0xF;
    D_80112684 = base_y + 0x28;
}
void title_label_update();  /* a function reached by pointer */
void title_timer_update(void *self);  /* a function reached by pointer */
void title_label_draw(TitleLabelOwner *owner);  /* a function reached by pointer */
void title_label_flags_update(TitleLabelFlagOwner *outer);
extern u8 title_label_shade_table[];

/* Set up a title label: like title_label_init, with the shade from
 * title_label_shade_table indexed by x, and no offset when index is -1. */
void title_label_index_init(void *ctl, TitleLabel *label, s16 x, s16 y, s32 index) {
    s32 base;
    u8 shade;

    base = (s32)title_shared_state_get() + 0x24;
    task_reset(ctl);
    task_set(ctl, (s32)title_label_flags_update, (s32)title_timer_update, (s32)title_label_draw, (s32)label);
    label->unk_04 = 0xF;
    label->unk_08 = 0xF;
    label->mode = 0;
    if (index == -1) {
        label->state_ptr = 0;
    } else {
        label->state_ptr = base + index;
    }
    label->bar_a_x = x;
    shade = title_label_shade_table[(s16)x * 8];
    label->bar_a_y2 = 0x74;
    label->bar_b_x2 = 0xB4;
    label->bar_b_x = y;
    label->bar_b_y2 = 0x74;
    label->bar_a_x2 = 0x8C - shade;
}

/* Set up a title label. ctl is reset through task_reset and task_set,
 * which also store the label pointer in ctl. Fixed fields are set, then the
 * label's vertical position is the base returned by title_shared_state_get (+0x24)
 * plus offset. x and y are stored at 0x14 and 0x20 (names unconfirmed). */
void title_label_init(void *ctl, TitleLabel *label, s16 x, s16 y, s32 mode, s32 offset) {
    s32 base;

    base = (s32)title_shared_state_get() + 0x24;
    task_reset(ctl);
    task_set(ctl, (s32)title_label_update, (s32)title_timer_update, (s32)title_label_draw, (s32)label);
    label->unk_04 = 0xF;
    label->mode = 1;
    label->bar_a_x2 = 0x20;
    label->bar_a_y2 = 0x58;
    label->bar_b_x2 = 0x6A;
    label->bar_b_y2 = 0x74;
    label->bar_c_x2 = 0xB4;
    label->bar_a_x = x;
    label->bar_b_x = y;
    label->bar_c_y2 = 0x90;
    label->state_ptr = base + offset;
    label->bar_c_x = mode;
}

u32 * title_get_pad_state();
void title_toggle_pair(s16 *self, s16 *other) {
    u32 *flags;

    flags = title_get_pad_state(self);
    if (other[1] == 1 && (*flags & 0x8000)) {
        title_entries_reset(0x4FFFF);
        self[1] = 1;
        other[1] = 0;
        self[2] = 0x2000;
        other[2] = 0x1000;
    } else if (self[1] == 1 && (*flags & 0x2000)) {
        title_entries_reset(0x4FFFF);
        self[1] = 0;
        other[1] = 1;
        self[2] = 0x1000;
        other[2] = 0x2000;
    }
}

void title_pair_cursor_move(TitleSlotState *state) {
    s16 *self;
    s16 *other;
    s16 *third;
    u32 *input;

    self = state->self_pair;
    other = state->other_pair;
    third = state->third_pair;
    input = title_get_pad_state();
    if (self[1] == 1 && (input[1] & 0x6000)) {
        title_entries_reset(0x4FFFF);
        input[0] |= 0x6000;
        self[1] = 0;
        other[1] = 1;
        self[3] = 0x1000;
        other[2] = 0x2000;
        other[3] = 0x2000;
        third[2] = 0x1000;
        *state->flag = 1;
        goto done;
    }
    if (other[1] == 1) {
        if (input[1] & 0x9000) {
            title_entries_reset(0x4FFFF);
            input[0] |= 0x9000;
            other[1] = 0;
            self[1] = 1;
            self[3] = 0x2000;
            other[2] = 0x1000;
            other[3] = 0x1000;
            third[2] = 0x1000;
            *state->flag = 0;
            goto done;
        }
        if (input[1] & 0x6000) {
            title_entries_reset(0x4FFFF);
            input[0] |= 0x6000;
            other[1] = 0;
            third[1] = 1;
            self[3] = 0x1000;
            other[2] = 0x1000;
            other[3] = 0x1000;
            third[2] = 0x2000;
            *state->flag = 2;
            goto done;
        }
    }
    if (third[1] == 1 && (input[1] & 0x9000)) {
        title_entries_reset(0x4FFFF);
        input[0] |= 0x9000;
        third[1] = 0;
        other[1] = 1;
        self[3] = 0x1000;
        other[2] = 0x2000;
        other[3] = 0x2000;
        third[2] = 0x1000;
        *state->flag = 1;
done:
        apply_sound_mode();
    }
}

void title_pair_cursor_move(TitleSlotState *state);
void title_pair_update(TitlePairOwner *obj) {
    TitleSlotState *pair;
    s16 *self_pair;

    title_get_pad_state(obj);
    pair = (TitleSlotState *)obj->pair;
    self_pair = pair->self_pair;
    switch (pair->mode) {
    case 0:
        if (pair->self_pair[2] >= 0x1001) {
            pair->self_pair[2] = pair->self_pair[2] - 0x80;
        }
        if (pair->other_pair[2] >= 0x1001) {
            pair->other_pair[2] = pair->other_pair[2] - 0x80;
        }
        title_toggle_pair(self_pair, pair->other_pair);
        if (pair->self_pair[1] == 1) {
            if (pair->flag != NULL) {
                *pair->flag = 0;
            }
        } else {
            if (pair->flag != NULL) {
                *pair->flag = 1;
            }
        }
        break;
    case 1:
        if (pair->unk_1A >= 0x1001) {
            pair->unk_1A = pair->unk_1A - 0x80;
        }
        if (pair->other_pair[2] >= 0x1001) {
            pair->other_pair[2] = pair->other_pair[2] - 0x80;
        }
        if (pair->unk_26 >= 0x1001) {
            pair->unk_26 = pair->unk_26 - 0x80;
        }
        if (pair->unk_30 >= 0x1001) {
            pair->unk_30 = pair->unk_30 - 0x80;
        }
        title_pair_cursor_move(pair);
        break;
    }
}

void title_label_flags_update(TitleLabelFlagOwner *outer) {
    TitleLabelFlagRec *rec = outer->flag_rec;
    Rec800B6CACTail *tail = &rec->tail;

    rec->tail.unk_04 = 0x1000;
    rec->tail.unk_06 = 0x1000;
    rec->scale_x = 0x1000;
    rec->scale_y = 0x1000;
    if (*rec->state_ptr == 0) {
        rec->tail.unk_02 = 1;
    } else {
        rec->tail.unk_02 = 0;
    }
    if (*rec->state_ptr == 1) {
        tail->unk_0E = 1;
    } else {
        tail->unk_0E = 0;
    }
}

/* Title label task, update step: sets the label's flag fields from the
 * state byte the label points at (state_ptr). */
void title_label_update(TitleTaskRec *rec) {
    TitleLabelTask *label;
    TitleLabelTail *tail;

    label = (TitleLabelTask *)rec->param;
    label->bar_a_scale_x = 0x1000;
    label->bar_a_scale_y = 0x1000;
    label->bar_b_scale_x = 0x1000;
    label->bar_b_scale_y = 0x1000;
    label->bar_c_scale_x = 0x1000;
    label->bar_c_scale_y = 0x1000;
    tail = (TitleLabelTail *)&label->unk_14;
    if (*(u8 *)label->state_ptr == 0) {
        label->flag_16 = 1;
    } else {
        label->flag_16 = 0;
    }
    if (*(u8 *)label->state_ptr == 1) {
        tail->unk_0E = 1;
    } else {
        tail->unk_0E = 0;
    }
    if (*(u8 *)label->state_ptr == 2) {
        tail->unk_1A = 1;
    } else {
        tail->unk_1A = 0;
    }
}

void title_timer_update(void *self) {
    TitleTimedOwner *obj = self;
    TitleTimedRec *timer;
    u32 *flags;

    timer = obj->timer;
    flags = title_get_pad_state(obj);
    switch (obj->state) {
    case 0:
        timer->elapsed = 0;
        timer->unk_0A = 0;
        timer->ratio = 0;
        obj->state++;
        break;
    case 1:
        timer->ratio = (timer->elapsed << 12) / timer->duration;
        timer->elapsed++;
        if (timer->duration < timer->elapsed) {
            obj->state++;
        }
        break;
    case 2:
        if (obj->node != NULL && ((TitleTaskNode *)obj->node)->state == 1) {
            break;
        }
        title_pair_update((TitlePairOwner *)obj);
        if (!(flags[1] & title_input_mask()) && !(flags[1] & title_input_step())) {
            break;
        }
        obj->state++;
        timer->elapsed = timer->duration;
        task_start((s32)obj, obj->node, 1);
        title_entries_reset(0x18FFFF);
        break;
    case 3:
        timer->ratio = (timer->elapsed << 12) / timer->duration;
        timer->elapsed--;
        if (timer->elapsed < 0) {
            title_flag_test_set(obj);
        }
        break;
    }
}

void title_label_draw(TitleLabelOwner *owner) {
    TitleLabelDraw *l = owner->label;
    TitleBarRect *ra = &l->bar_a;
    TitleBarRect *rb = &l->bar_b;
    TitleBarRect *rc = &l->bar_c;
    s32 scale = l->scale;
    s32 not_full = scale != 0x1000;
    s32 scaled;
    s32 left_a;
    s32 top_a;
    s32 x_a;
    s32 h_a;
    s32 left_b;
    s32 top_b;
    s32 x_b;
    s32 h_b;
    s32 left3_a;
    s32 top3_a;
    s32 x3_a;
    s32 h3_a;
    s32 left3_b;
    s32 top3_b;
    s32 x3_b;
    s32 h3_b;
    s32 left_c;
    s32 top_c;
    s32 x_c;
    s32 h_c;
    s32 on_a;
    s32 on_b;
    s32 on_c;

    switch (l->mode) {
    case 0:
        if (ra->y == 1) {
            scaled = scale * 0x1448 / 0x1000;
        } else {
            scaled = scale;
        }
        left_a = ra->x2;
        top_a = ra->y2;
        x_a = ra->x;
        h_a = ra->y - 1;
        title_menu_quad_draw(12, left_a, top_a, x_a - h_a, not_full, scaled, 1);
        if (rb->y == 1) {
            scaled = scale * 0x1448 / 0x1000;
        } else {
            scaled = scale;
        }
        left_b = rb->x2;
        top_b = rb->y2;
        x_b = rb->x;
        h_b = rb->y - 1;
        title_menu_quad_draw(12, left_b, top_b, x_b - h_b, not_full, scaled, 1);
        scaled = ra->len * scale / 0x1000;
        title_menu_quad_draw(12, 0x94, ra->y2 + 4, 0x32, not_full, scaled, 1);
        scaled = rb->len * scale / 0x1000;
        title_menu_quad_draw(12, 0xA4, ra->y2 + 4, 0x33, not_full, scaled, 1);
        break;
    case 1:
        if (ra->y == 1) {
            scaled = scale * 0x1448 / 0x1000;
        } else {
            scaled = scale;
        }
        left3_a = ra->x2;
        top3_a = ra->y2;
        x3_a = ra->x;
        h3_a = ra->y - 1;
        title_menu_quad_draw(12, left3_a, top3_a, x3_a - h3_a, not_full, scaled, 1);
        if (rb->y == 1) {
            scaled = scale * 0x1448 / 0x1000;
        } else {
            scaled = scale;
        }
        left3_b = rb->x2;
        top3_b = rb->y2;
        x3_b = rb->x;
        h3_b = rb->y - 1;
        title_menu_quad_draw(12, left3_b, top3_b, x3_b - h3_b, not_full, scaled, 1);
        if (rc->y == 1) {
            scaled = scale * 0x1448 / 0x1000;
        } else {
            scaled = scale;
        }
        left_c = rc->x2;
        top_c = rc->y2;
        x_c = rc->x;
        h_c = rc->y - 1;
        title_menu_quad_draw(12, left_c, top_c, x_c - h_c, not_full, scaled, 1);
        on_a = ra->y;
        if (on_a == 1) {
            scaled = ra->pad_06 * scale / 0x1000;
            title_menu_quad_draw(12, ra->x2 + title_label_shade_table[ra->x * 8] + 4, ra->y2 + 4, 0x33, not_full, scaled, on_a);
        }
        on_b = rb->y;
        if (on_b == 1) {
            scaled = rb->len * scale / 0x1000;
            title_menu_quad_draw(12, rb->x2 - 12, rb->y2 + 4, 0x32, not_full, scaled, on_b);
            scaled = rb->pad_06 * scale / 0x1000;
            title_menu_quad_draw(12, rb->x2 + title_label_shade_table[rb->x * 8] + 4, rb->y2 + 4, 0x33, not_full, scaled, on_b);
        }
        on_c = rc->y;
        if (on_c == 1) {
            scaled = rc->len * scale / 0x1000;
            title_menu_quad_draw(12, rc->x2 - 12, rc->y2 + 4, 0x32, not_full, scaled, on_c);
        }
        break;
    }
    title_menu_quad_draw(12, 0x20, 0x20, l->value, not_full, scale, 1);
}

void pad3d_start(s16 value);
void title_pad3d_update(TitleTaskNode *node) {
    TitleStepRec *rec;
    u32 *input;

    rec = node->unk_14;
    input = title_get_pad_state(node);

    switch (node->sub_state) {
    case 0:
        rec->count = 0;
        rec->ratio = 0;
        node->sub_state += 1;
        pad3d_show(rec->span);
        break;

    case 1:
        rec->ratio = (s16)(((s32)rec->count << 12) / rec->span);
        rec->count += 1;
        if (rec->span < rec->count) {
            node->sub_state += 1;
        }
        break;

    case 2:
        if (node->mode != 0 && ((TitleTaskNode *)node->mode)->state == 1) {
            break;
        }
        if (!pad3d_arrived()) {
            break;
        }
        if (input[0] & 0x8000) {
            pad3d_left(0x14);
            break;
        }
        if (input[0] & 0x2000) {
            pad3d_right(0x14);
            break;
        }
        if (pad3d_turning() != 0) {
            break;
        }
        if (!(input[1] & title_input_mask()) && !(input[1] & title_input_step())) {
            break;
        }
        node->sub_state += 1;
        rec->count = rec->span;
        task_start((s32)node, (void *)node->mode, 1);
        title_entries_reset(0x18FFFF);
        pad3d_start(rec->span);
        break;

    case 3:
        rec->ratio = (s16)(((s32)rec->count << 12) / rec->span);
        rec->count -= 1;
        if (rec->count < 0) {
            node->sub_state += 1;
        }
        break;

    case 4:
        if (pad3d_gone() != 1) {
            break;
        }
        title_flag_test_set(node);
        break;
    }
}

/* Task callback: passes the record's position to title_menu_quad_draw with a 0x1000 flag. */
void title_pos_draw(TitlePosObj *obj) {
    s16 *pos = obj->pos;

    title_menu_quad_draw(0xC, 0x20, 0x18, pos[1], pos[0] != 0x1000, pos[0], 1);
}

void title_menu_setup(TitleMenuSetupObj *self);
void title_menu_anim_update(TitleMenuCtl *obj);
extern u8 D_80112724;
extern s16 D_8011272C;
extern s16 D_8011272E;
extern s16 D_80112730;
extern s16 D_80112732;
extern s16 D_8011272A;
extern s16 D_80112726;
extern u8 D_80112279;
extern u8 D_8011227A;
extern u8 D_8011227D;
extern u8 D_8011227E;
extern u8 D_80112278;
extern u8 D_8011227C;
extern s16 D_80112756;
extern s16 D_8011275E;
extern s16 D_80112770;
extern s16 D_80112772;
extern s32 title_movie_base;
void title_menu_anim_draw(TitleMenuCtl *ctl);
void title_menu_begin(TitleCtl *ctl) {
    title_shared_state_get();
    task_reset(ctl);
    task_set((TitleTaskRec *)ctl, (s32)title_menu_setup, (s32)title_menu_anim_update, (s32)title_menu_anim_draw, (s32)&D_80112724);
    D_8011272C = 0x30;
    D_8011272E = 0x3C;
    D_80112730 = 0xE0;
    D_80112732 = 0x9C;
    D_8011272A = 0xF;
    D_80112726 = 4;
    D_80112279 = 0x96;
    D_8011227A = 0x2E;
    D_8011227D = 0x42;
    D_8011227E = 0x1E;
    D_80112278 = 0;
    D_8011227C = 0;
    title_record_set(1, 8, (u16 *)(&D_80112724 + 8), 0, 0, (s32)&D_80112278, (s32)(&D_80112278 + 4), 0);
    D_80112756 = 1;
    D_8011275E = 0;
    D_80112770 = 0;
    D_80112772 = 0;
    if (title_video_is_pal() == 0) {
        title_movie_base = 0;
        return;
    }
    title_movie_base = 0x20;
}

void title_menu_setup(TitleMenuSetupObj *self) {
    s16 *dst;
    u8 *src;
    s32 i;

    /* halfword buffer at self->unk_14: clear 0x40..0x44, then fill 17 entries
       from 0x10 with the bytes at info+0xA4 */
    dst = self->unk_14;
    src = (u8 *)title_shared_state_get() + 0x24;
    dst[0x20] = 0;
    dst[0x21] = 0;
    dst[0x22] = 0;
    for (i = 0; i < 0x11; i++) {
        dst[8 + i] = (src + i)[0x80];
    }
}

/* Menu cursor: button 0x4000 (or its auto-repeat) steps up to 9, 0x1000 down to 0. */
void title_menu_navigate(TitleMenuAnim *a) {
    u32 *input = title_get_pad_state(a);
    u16 *repeat = (u16 *)input;

    if (repeat[11] < 0x17) {
        if (!(input[1] & 0x4000)) {
            goto left;
        }
    } else {
        repeat[11] = 0x12;
    }
    switch (a->window_row) {
    case 8:
        if (a->first_visible_row + 8 == 0x10) {
            a->window_row++;
        } else {
            a->first_visible_row++;
        }
        title_entries_reset(0x4FFFF);
        break;
    case 9:
        break;
    default:
        title_entries_reset(0x4FFFF);
        a->window_row++;
        break;
    }
    goto done;

left:
    if (repeat[13] < 0x17) {
        if (!(input[1] & 0x1000)) {
            return;
        }
    } else {
        repeat[13] = 0x12;
    }
    switch (a->window_row) {
    case 0:
        break;
    case 1:
        if (a->first_visible_row + 1 == a->window_row) {
            a->window_row--;
        } else {
            a->first_visible_row--;
        }
        title_entries_reset(0x4FFFF);
        break;
    default:
        title_entries_reset(0x4FFFF);
        a->window_row--;
        break;
    }
done:
    a->cursor = a->first_visible_row + a->window_row;
}

void title_menu_navigate(TitleMenuAnim *a);
void title_seq_set_enabled(s32 a);
s32 title_ratio_get(void);
void title_timer_start(s32 a);
void title_pos_reset(s16 value);
void title_screen_show(s32 index);
void title_seq_fade_in(s32 arg0);
void title_entries_set_rate(s32 divisor);
void title_menu_anim_update(TitleMenuCtl *obj) {
    TitleMenuAnim *a = obj->anim;
    s32 one = 1;
    u32 *input;

    input = title_get_pad_state(obj);

    a->spin_x += 0x40;
    a->spin_y += 0x20;
    do {
    } while (0);
    switch (obj->state) {
    case 0:
        a->glow_enabled = 0;
        obj->state++;
        a->step = 0;
        a->scale = 0;
        a->frame = 0;
        a->glow = 0;
        a->phase = 0;
        /* fallthrough */
    case 1:
        a->frame++;
        if (a->frames < a->frame) {
            title_record_restart(one, 10);
            obj->state++;
        }
        break;
    case 2: {
        if (a->step < a->steps) {
            a->step++;
        }
        a->scale = (a->step << 12) / a->steps;
        if (title_record_is_active(one) == 1) {
            a->glow_enabled = 1;
            if (a->step == a->steps) {
                obj->state++;
            }
        }
        break;
    }
    case 3:
        a->phase += 0x60;
        a->glow = (0x1000 - *(s16 *)(D_801085E6 + (a->phase & 0xFFF) * 4)) / 2;
        if (obj->task != 0 && obj->task->state == 1) {
            break;
        }
        title_menu_navigate(a);
        if (input[1] & title_input_mask()) {
            if (a->cursor != 0x11) {
                if (a->choice[a->cursor] == 1) {
                    title_entries_reset(0x1FFFF);
                    obj->state = 10;
                } else {
                    title_entries_reset(0x3FFFF);
                }
                break;
            }
        } else if (!(input[1] & title_input_step())) {
            break;
        }
        a->frame = 0;
        task_start((s32)obj, obj->task, 1);
        panel_show(7, 8);
        title_record_close(one, 8);
        a->glow_enabled = 0;
        title_entries_reset(0x18FFFF);
        obj->state++;
        break;
    case 4:
        a->scale = (a->step << 12) / a->steps;
        a->step--;
        if (a->step < 0) {
            obj->state++;
        }
        break;
    case 5:
        if (title_record_is_ready(one) == 1) {
            title_flag_test_set(obj);
        }
        break;
    case 10:
        title_pos_reset(0x10);
        title_seq_set_enabled(0);
        title_entries_set_rate(0x10);
        obj->state++;
        break;
    case 11:
        if (title_ratio_get() == 0) {
            a->delay = 0;
            obj->state++;
        }
        break;
    case 12:
        a->delay++;
        if (a->delay >= 9) {
            title_screen_show(a->cursor);
            obj->state++;
            a->delay = 0;
        }
        break;
    case 13:
        a->delay++;
        if (a->delay >= 5) {
            title_seq_set_enabled(1);
            title_seq_fade_in(0x10);
            title_timer_start(0x10);
            title_set_disp_mask(1);
            obj->state++;
        }
        break;
    case 14:
        if (title_ratio_get() >= 0x1000) {
            obj->state = 3;
        }
        break;
    }
}

extern s16 title_menu_row_color[];
extern s16 D_800BE22C[];
void title_menu_cell_draw(s32 x, s32 y, s32 num, s32 label, s32 sub, s32 bright);
/* Menu cell grid: swatches above and below the rows, then one cell per choice row (the cursor row is drawn brighter). */
void title_menu_anim_draw(TitleMenuCtl *ctl) {
    TitleMenuAnim *anim;
    s32 scale;
    s32 row;
    s32 left, top;
    s32 bright;
    s32 item_x, item_y;
    s32 i;
    s32 shade;
    s32 col;

    anim = ctl->anim;
    scale = anim->scale;
    title_menu_quad_draw(12, 32, 24, 1, scale != 0x1000, scale, 1);
    if (anim->glow_enabled == 0) {
        return;
    }
    bright = anim->glow;
    bright = (bright * 2) / 3;
    row = anim->first_visible_row;
    left = anim->origin_x;
    top = anim->origin_y;
    item_x = left + 0x22;
    item_y = top + 8;
    if (row > 0) {
        title_draw_swatch(left + 0x11, item_y, 0, bright);
    }
    if (row < 7) {
        title_draw_swatch(left + 0x11, anim->origin_y + anim->extent_y - 0x11, 1, bright);
    }
    item_y = top + 0x14;
    i = 0;
    do {
        if (row == 0x11) {
            item_x += 0x78;
            item_y += 4;
        }
        shade = 0x800;
        if (anim->cursor == row) {
            title_cursor_draw(2, (u16 *)&anim->pad_40, item_x - 9, item_y + 3, 2, scale);
            shade = 0x1000;
        }
        col = title_menu_row_color[row];
        if (anim->choice[row] == 0) {
            col = 5;
        }
        title_menu_cell_draw(item_x, item_y, row, col, D_800BE22C[row], shade);
        item_y += 0xC;
        i++;
        row++;
    } while (i < 10);
}

extern s32 title_movie_base;
void title_set_disp_mask(s32 mask);
s32 title_movie_play(s32 entry_id);
void rec_queue_flush(void);
void title_screen_show(s32 index) {
    s16 rect[4];

    vblank_pause();
    title_set_disp_mask(0);
    title_draw_sync(0);
    rect[0] = 0;
    rect[1] = 0;
    rect[2] = 0x400;
    rect[3] = 0xF0;
    clear_image(rect, 0, 0, 0);
    title_draw_sync(0);
    rect[2] = 0x2FF;
    rect[0] = 0;
    rect[1] = 0xF0;
    rect[3] = 0x110;
    clear_image(rect, 0, 0, 0);
    title_draw_sync(0);
    title_set_disp_mask(1);
    title_movie_play(title_movie_base + index);
    display_start();
    rec_queue_flush();
    title_vblank_unpause();
}

extern TitleCtl title_timer_task;
extern u8 title_pos_task_state[];
void title_timer_tick(TitleCtl *ctl);  /* a function reached by pointer */
void title_backdrop_draw(TitleCtl *ctl);  /* a function reached by pointer */
void title_ctl_init(void) {
    task_reset(&title_timer_task);
    task_set((TitleTaskRec *)&title_timer_task, 0, (s32)title_timer_tick, (s32)title_backdrop_draw, (s32)title_pos_task_state);
}

extern s16 *title_timer_state;
extern u16 D_801127A2;
/* Sets the two x/y halfwords of the title state block and clears its third halfword. */
void title_pos_reset(s16 value) {
    s16 *state = title_timer_state;

    state[0] = value;
    state[1] = value;
    state[3] = 0;
    D_801127A2 = 0;
    task_start(0, &title_timer_task, 0);
}

/* Sets the second halfword of the title state block to value, clears the first, sets the fourth to 1 and
 * restarts the title control task. */
void title_timer_start(s32 value) {
    s16 *state = title_timer_state;

    state[1] = value;
    state[0] = 0;
    state[3] = 1;
    D_801127A2 = 0;
    task_start(0, &title_timer_task, 0);
}

void title_timer_tick(TitleCtl *ctl) {
    TitleTimer *t;

    t = (TitleTimer *)ctl->anim;
    if (ctl->step != 0) {
        return;
    }
    switch (t->mode) {
    case 0:
        t->value = ((s16)t->count << 12) / (s16)t->period;
        t->count--;
        if ((s16)t->count < 0) {
            ctl->step++;
        }
        break;
    case 1:
        t->value = ((s16)t->count << 12) / (s16)t->period;
        t->count++;
        if ((s16)t->period < (s16)t->count) {
            title_flag_test_set(ctl);
        }
        break;
    }
}

extern s16 title_ready_state;

s32 title_is_ready(void) {
    return title_ready_state == 1;
}

s32 title_ratio_get(void) {
    return title_timer_state[2];
}

/* Draws the title fade: two grey semi-transparent tiles (256 + 65 wide)
   over the draw area, each with its draw-mode packet, then a texture window reset. */
void title_backdrop_draw(TitleCtl *ctl) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 shade = ((TitleTimer *)ctl->anim)->value / 32;
    u16 *area;
    s32 ypart, xpart;
    u8 *bg_left_ot;
    u8 *bg_left_pkt;
    u8 *mode_left_ot;
    u8 *mode_left_pkt;
    u8 *bg_right_ot;
    u8 *bg_right_pkt;
    u8 *mode_right_ot;
    u8 *mode_right_pkt;
    u8 *window_ot;
    u8 *window_pkt;

    scratch_top[3] = 4;
    scratch_top[7] = 0x64;
    scratch_top[4] = shade;
    scratch_top[5] = shade;
    scratch_top[6] = shade;
    *(s16 *)(scratch_top + 8) = 0;
    *(s16 *)(scratch_top + 0xA) = 0;
    scratch_top[0xC] = 0;
    scratch_top[0xD] = 0;
    *(s16 *)(scratch_top + 0x10) = 0x100;
    *(s16 *)(scratch_top + 0x12) = 0xF0;
    scratch_top[7] &= ~1;
    bg_left_ot = ctx->ot_base;
    bg_left_pkt = scratch_top;
    addPrim(bg_left_ot, bg_left_pkt);
    scratch_top += 0x14;

    area = (u16 *)ctx->draw_env;
    scratch_top[3] = 1;
    ypart = (area[1] >> 4) & 0x10;
    xpart = ((area[0] & 0x3FF) >> 6) | 0x100;
    *(u32 *)(scratch_top + 4) = 0xE1000600 | ((ypart | xpart | ((area[1] & 0x200) << 2)) & 0x9FF);
    mode_left_ot = ctx->ot_base;
    mode_left_pkt = scratch_top;
    addPrim(mode_left_ot, mode_left_pkt);
    scratch_top += 8;

    scratch_top[3] = 4;
    scratch_top[7] = 0x64;
    scratch_top[4] = shade;
    scratch_top[5] = shade;
    scratch_top[6] = shade;
    *(s16 *)(scratch_top + 8) = 0x100;
    *(s16 *)(scratch_top + 0xA) = 0;
    scratch_top[0xC] = 0;
    scratch_top[0xD] = 0;
    *(s16 *)(scratch_top + 0x10) = 0x41;
    *(s16 *)(scratch_top + 0x12) = 0xF0;
    scratch_top[7] &= ~1;
    bg_right_ot = ctx->ot_base;
    bg_right_pkt = scratch_top;
    addPrim(bg_right_ot, bg_right_pkt);
    scratch_top += 0x14;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = 0xE1000600
        | ((0x100 | ((area[1] >> 4) & 0x10) | ((((s16)area[0] + 0x100) & 0x3FF) >> 6) | ((area[1] & 0x200) << 2)) & 0x9FF);
    mode_right_ot = ctx->ot_base;
    mode_right_pkt = scratch_top;
    addPrim(mode_right_ot, mode_right_pkt);
    scratch_top += 8;

    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    window_ot = ctx->ot_base;
    window_pkt = scratch_top;
    addPrim(window_ot, window_pkt);
    scratch_top += 0xC;
}

extern u8 title_block_colors;
extern u8 D_801127A9;
extern u8 D_801127AA;
extern u8 D_801127AC;
extern u8 D_801127AD;
extern u8 D_801127AE;
extern u16 title_block_state[];
extern s16 D_801127B2;
extern s16 D_801127B4;
extern s16 D_801127B6;
extern s16 D_801127B8;
extern s16 D_801127BA;
extern s16 D_801127C8;
void title_block_update(TitleBlockArg *arg);
void title_block_draw(TitleDrawObj *obj);
void title_step_seq_update();
void title_block_init(TitleCtl *ctl) {
    u8 *colors;

    task_reset(ctl);
    task_set((TitleTaskRec *)ctl, (s32)title_block_update, (s32)title_step_seq_update, (s32)title_block_draw, (s32)title_block_state);
    D_801127B4 = 0x39;
    D_801127B6 = 0x87;
    D_801127B8 = 0xCF;
    D_801127BA = 0x23;
    D_801127C8 = 0xE;
    D_801127B2 = 6;
    colors = &title_block_colors;
    title_block_colors = 0;
    D_801127A9 = 0xC8;
    D_801127AA = 0x2E;
    D_801127AC = 0;
    D_801127AD = 0x64;
    D_801127AE = 0x2E;
    title_record_set(0, 8, title_block_state + 2, 0, 0, (s32)colors, (s32)(colors + 4), 0);
}

void title_block_update(TitleBlockArg *arg) {
    TitleBlockOutput *out;
    Rec800B854CShared *shared;
    s32 v;

    out = arg->out;
    shared = (Rec800B854CShared *) title_shared_state_get();
    if (shared->unk_B8 != 13) {
        out->unk_0E = shared->unk_B8 - 1;
    } else {
        out->unk_0E = 11;
    }
    if (shared->unk_20 == 13) {
        out->unk_0C = 11;
    } else {
        v = shared->unk_20 - 1;
        out->unk_0C = v;
        if (out->unk_0C < 0) {
            out->unk_0C = 0;
        }
    }
}

s32 title_cursor_update(void *obj) {
    TitleCursor *cur = obj;
    s32 limit;
    s16 timer;
    u32 *entry;

    entry = title_get_pad_state(obj);
    limit = cur->limit;
    switch (cur->state) {
    case 0:
        /* Move up or down when the entry's flags/type say so; the entry reset clears the slots. */
        if (((u16) entry[6] >= 0x17) || ((entry[1] & 0x8000) != 0)) {
            if (cur->index > 0) {
                title_entries_reset(0x4FFFF);
                cur->phase_timer = 0;
                cur->state = cur->state + 1;
                cur->saved_index = cur->index - 1;
            }
        } else if ((((u16) entry[5] >= 0x17) || (entry[1] & 0x2000)) && (cur->index < limit)) {
            title_entries_reset(0x4FFFF);
            cur->phase_timer = 0;
            cur->state = cur->state + 1;
            cur->saved_index = cur->index + 1;
        }
        break;
    case 1:
        /* Advance the timer by 0x1000 / rate; on overflow return to state 0. */
        timer = cur->phase_timer + 0x1000 / cur->phase_rate;
        cur->phase_timer = timer;
        if (timer >= 0x1000) {
            s16 next_state = cur->state - 1;

            cur->phase_timer = 0;
            cur->index = cur->saved_index;
            cur->state = next_state;
        }
        break;
    }
    return cur->state == 0;
}

void title_seq_set_enabled(s32 arg);
void title_step_seq_update(TitleStepTask *task) {
    TitleStepSeq *seq;
    u32 *entry;
    TitleStepScene *scene;
    s32 input;
    s32 slot = 0;
    TitleStepSub *sub;

    seq = task->seq;
    entry = title_get_pad_state(task);
    scene = (TitleStepScene *) title_shared_state_get();
    sub = &scene->sub_24;

    switch (task->step) {
    case 0:
        seq->record_active = 0;
        seq->delay_timer = 0;
        seq->unk_16 = 0;
        seq->state = 0;
        seq->phase_timer = 0;
        seq->saved_index = seq->index;
        task->step++;
        /* fall through */
    case 1:
        if (seq->limit < 0) {
            task->step = 4;
            break;
        }
        seq->delay_timer++;
        if ((s16) seq->delay_timer < seq->delay_limit) {
            break;
        }
        title_record_restart(slot, 6);
        title_entries_reset(0x18FFFF);
        task->step++;
        break;
    case 2:
        if (title_record_is_active(slot) == 1) {
            seq->record_active = 1;
            task->step++;
        }
        break;
    case 3:
        if (task->link != NULL && task->link->unk_1C == 1) {
            break;
        }
        seq->unk_16 += 0x60;
        if (!title_cursor_update(seq)) {
            break;
        }
        input = title_input_mask();
        if (entry[1] & (input | 0x800)) {
            task->step++;
            break;
        }
        input = title_input_step();
        if (!(entry[1] & input)) {
            break;
        }
        task_start((s32) task, task->link, 2);
        title_record_close(slot, 6);
        title_entries_reset(0x18FFFF);
        seq->record_active = 0;
        scene->unk_20 = seq->index + 1;
        task->step = 10;
        break;
    case 4:
        title_entries_reset(0x1FFFF);
        title_pos_reset(0x14);
        title_seq_set_enabled(0);
        title_entries_set_rate(0x14);
        task->step++;
        break;
    case 5:
        if (title_ratio_get() != 0) {
            break;
        }
        seq->phase_timer = 0;
        task->step++;
        break;
    case 6:
        seq->phase_timer++;
        if ((s16) seq->phase_timer < 5) {
            break;
        }
        scene->unk_20 = seq->index + 1;
        if (sub->flag_94 == 0) {
            sub->flag_94 = 1;
        }
        scene->unk_08 = 0;
        scene->unk_D0 = scene->unk_20;
        /* title_request_exit takes no argument in the source, but the original call passes one. */
        ((void (*)(s32))title_request_exit)(seq->index + 0xA);
        break;
    case 10:
        if (title_record_is_ready(slot) == 1) {
            title_flag_test_set(task);
        }
        break;
    }
}

void title_option_draw(s32 x, s32 y, s32 cur, s32 sel, s32 fade, s32 prev, s32 blink);
void title_block_draw(TitleDrawObj *obj) {
    TitleDrawBlock *block = obj->block;

    if (block->visible != 0) {
        s32 pulse = (((const s16 *)D_801085E6)[(block->phase & 0xFFF) * 2] + 0x1000) / 2;
        title_option_draw(block->x + ((s16)block->width / 2) - 0x33,
                      block->y + 8,
                      block->cur,
                      block->sel,
                      block->fade,
                      block->prev,
                      pulse);
    }
}

extern u8 title_exit_state[];
void title_exit_update(struct TitleExitTask *task);  /* a function reached by pointer */
/* Starts the exit task: title_exit_update on the given task record. */
void title_exit_init(void *task) {
    task_reset(task);
    task_set(task, 0, (s32)title_exit_update, 0, (s32)title_exit_state);
}

/* Exit task: resets the title entries, waits for the fade ratio to reach 0,
 * then after 5 more frames sets info->unk_08 and requests the exit. */
void title_exit_update(TitleExitTask *task) {
    TitleExitInfo *info = (TitleExitInfo *)title_shared_state_get();
    s16 *counter = task->counter;

    switch (task->state) {
    case 0:
        title_entries_reset(0x1FFFF);
        title_pos_reset(0x14);
        title_seq_set_enabled(0);
        title_entries_set_rate(0x14);
        task->state++;
        break;
    case 1:
        if (title_ratio_get() == 0) {
            *counter = 0;
            task->state++;
        }
        break;
    case 2:
        if (++*counter >= 5) {
            info->unk_08 = 1;
            title_request_exit(0x16);
        }
        break;
    }
}

void ok_box_animate(TitleScrollState *s) {
    s->unk_02 += 0x40;
    s->unk_04 += 0x20;
}

extern s32 title_cursor_tr[3];
extern s32 title_cursor_scale[7];
extern u32 title_cursor_verts[];
extern TitleCursorTri title_cursor_tris[];
extern s32 title_cursor_color_set0[];
extern s32 title_cursor_color_set1[];
extern s32 title_cursor_color_set2[];
/* Draws the 3D menu cursor: rotates its model by angles (Ry * Rx * Rz), projects it at screen offset
 * (ofx, ofy), adds its 8 flat triangles in colour set color_set to OT entry ot_index, then a draw-mode
 * packet, and restores the default screen offset (160, 120). */
void title_cursor_draw(s32 ot_index, u16 *angles, s32 ofx, s32 ofy, s32 color_set, s32 depth) {
    TitleMatrix m;
    TitleMatrix r;
    u32 xy[8];
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u32 sc;
    register u32 sc2 asm("$3");
    u32 sc3;
    register s16 cos asm("$4");
    s16 neg_sin;
    s16 neg2, neg3;
    register s32 one asm("$8");
    register TitleMatrix *mp asm("$5");
    register TitleMatrix *rp asm("$6");
    register const u32 *trig asm("$4");
    s32 *colors;
    TitleCursorTri *tris;
    s32 i;
    u32 *pts;

    title_cursor_scale[0] = ((depth << 9) + ((0x1000 - depth) << 11)) / 0x1000;
    gte_set_ctrl(OFX, ofx << 16);
    gte_set_ctrl(OFY, ofy << 16);

    sc = *(const u32 *)rcossin_tbl[angles[1] & 0xFFF];
    one = 0x1000;
    m.m[0][1] = 0;
    m.m[1][0] = 0;
    m.m[1][1] = one;
    m.m[1][2] = 0;
    m.m[2][1] = 0;
    cos = sc >> 16;
    neg_sin = -sc;
    m.m[0][0] = cos;
    m.m[0][2] = sc;
    m.m[2][0] = neg_sin;
    m.m[2][2] = cos;

    sc2 = *(const u32 *)rcossin_tbl[angles[0] & 0xFFF];
    mp = &m;
    rp = &r;
    r.m[0][0] = one;
    r.m[0][1] = 0;
    r.m[0][2] = 0;
    r.m[1][0] = 0;
    r.m[2][0] = 0;
    cos = sc2 >> 16;
    neg2 = -sc2;
    r.m[1][1] = cos;
    r.m[2][2] = cos;
    r.m[1][2] = neg2;
    r.m[2][1] = sc2;
    trig = (const u32 *)rcossin_tbl;
    gte_mul_matrix_pinned(rp, mp, "$10", "$9", "$7");

    sc3 = trig[angles[2] & 0xFFF];
    r.m[0][2] = 0;
    r.m[1][2] = 0;
    r.m[2][0] = 0;
    r.m[2][1] = 0;
    r.m[2][2] = one;
    cos = sc3 >> 16;
    neg3 = -sc3;
    r.m[0][0] = cos;
    r.m[0][1] = neg3;
    r.m[1][0] = sc3;
    r.m[1][1] = cos;
    gte_mul_matrix_pinned(rp, mp, "$7", "$6", "$4");

    gte_load_R(&m);
    {
        register s32 *tr asm("$12") = title_cursor_tr;
        gte_load_TR(tr);
    }
    title_project_verts(title_cursor_verts, 0x30, xy);

    switch (color_set) {
    case 0:
        colors = title_cursor_color_set0;
        break;
    case 1:
        colors = title_cursor_color_set1;
        break;
    default:
        colors = title_cursor_color_set2;
        break;
    }
    tris = title_cursor_tris;
    i = 0;
    pts = xy;
    for (; i < 8; i++, colors++) {
        u32 *pa = pts + tris[i].a;
        u32 *pb = pts + tris[i].b;
        u32 *pc = pts + tris[i].c;
        scratch_top[3] = 4;
        *(u32 *)(scratch_top + 8) = *pa;
        *(u32 *)(scratch_top + 0xC) = *pb;
        *(u32 *)(scratch_top + 0x10) = *pc;
        *(s32 *)(scratch_top + 4) = *colors;
        title_add_prim(ctx->ot_base + ot_index * 4, scratch_top);
        scratch_top += 0x14;
    }
    {
    TitleDrawCtx *ctx2 = title_draw_ctx_ptr;
    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = 0xE1000620;
    title_add_prim(ctx2->ot_base + ot_index * 4, scratch_top);
    scratch_top += 8;
    }
    {
        register s32 off asm("$12");
        off = 0xA00000;
        gte_set_ctrl(OFX, off);
        off = 0x780000;
        gte_set_ctrl(OFY, off);
    }
}

extern TitleVec3 title_vec_init_a[5];
extern TitleVec3 title_vec_init_b[5];
void title_state_update(void) {
    TitleMainState *s;
    TitleSubState *sub;
    s32 i;
    u8 *clr;
    TitleVec3 *src_a;
    TitleVec3 *src_b;
    s32 flag;
    s32 h;
    u32 next;

    s = (TitleMainState *)title_shared_state_get();
    ((u32 *(*)())title_get_pad_state)();
    sub = &s->sub;
    flag = title_is_t_build();
    i = 0;
    if (flag == 1 || s->inited == 0) {
        s->inited = 1;
        src_b = title_vec_init_b;
        src_a = title_vec_init_a;
        s->sub.mode[0] = 2;
        s->sub.mode[1] = 0;
        s->sub.mode[2] = 0;
        s->sub.mode[3] = 0;
        s->sub.mode[4] = 0;
        FAKE_OPAQUE(sub);
        do {
            sub->a[i] = src_a[i];
            sub->b[i] = src_b[i];
            i++;
        } while (i < 5);
        i = 0x10;
        clr = (u8 *)sub + 0x10;
        do {
            clr[0x80] = 0;
            i--;
            clr--;
        } while (i >= 0);
        sub->flag = 1;
        s->unk_20 = 0;
        sub->unk_94 = 0;
        if (title_video_is_pal() == 0) {
            s->rect_y = 0x28;
            s->rect_w = 0x100;
                do {
            } while (0);
            h = 0xA0;
            s->rect_x = 0;
        } else {
            s->rect_x = 6;
            s->rect_y = 0x38;
            s->rect_w = 0x100;
                do {
            } while (0);
            h = 0xE0;
        }
        s->rect_h = h;
        s->unk_08 = 0;
        s->input_mask = title_input_mask();
        s->input_step = title_input_step();
        s->unk_0C = 0;
    }
    s->unk_04 = 0;
    s->unk_BC = 0;
    s->unk_C4 = 0;
    if (s->unk_CC == 1) {
        s->unk_C8 = 2;
        s->unk_CC = 0;
    } else {
        do {
        } while (0);
        next = ++s->unk_C8;
        if (next >= 3) {
            next = 2;
        }
        s->unk_C8 = next;
    }
}

void str_copy(char *src, char *dst);
extern u8 card_name_buf[];
extern u8 card_name_flags[];
/* Maps level (>= 16 clamps to 15) to a code 0x30 + level (levels 11..15 skip 7), stores it
   in the card_name_buf table at the slot title_str_length returns, and returns the table. */
u8 *card_file_name(s32 level) {
    s32 ctx;
    s32 slot;
    s32 value;
    s32 clamped;
    u8 *buf;

    value = level;
    ctx = (s32)slot_009();
    clamped = 0xF;
    if (value < 0x10) {
        clamped = value;
    }
    value = clamped;
    if (value >= 0xB) {
        value += 7;
    }
    value += 0x30;
    slot = title_str_length(ctx);
    buf = card_name_buf;
    str_copy((char *)ctx, (char *)buf);
    card_name_buf[slot] = value;
    card_name_flags[slot] = 0;
    return buf;
}

extern s32 (*slot_100)(s32 *, s32 *, s32);
extern s32 title_memcard_arg;
void title_memcard_thread(void);  /* a function reached by pointer */
extern s32 title_card_state;
extern s32 card_op;
TitleCtrl * card_get_ctrl(void);
/* Initialises the title control block: state word = 1, word 0 = result of slot_100, sets two flags. */
s32 card_op_start(void) {
    s32 *ctrl = (s32 *)card_get_ctrl();

    ctrl[1] = 1;
    ctrl[8] = 4;
    title_card_state = 0;
    ctrl[0] = slot_100((s32 *)title_memcard_thread, &title_memcard_arg, 0);
    card_op = 0;
    ctrl[9] = 1;
    return 1;
}

extern void (*slot_101)(s32);
TitleCtrl * card_get_ctrl(void);
/* Control block word 0 is passed to slot_101 when word 1 (state) is 6; returns 1 if it fired. */
s32 card_shutdown(void) {
    s32 *ctrl = (s32 *)card_get_ctrl();

    if (ctrl[1] == 6) {
        slot_101(ctrl[0]);
        return 1;
    }
    return 0;
}

TitleCtrl *card_get_ctrl(void) {
    return &card_ctrl;
}

TitleCtrl * card_get_ctrl(void);
s32 card_thread_state(void) {
    s32 *ctrl = (s32 *)card_get_ctrl();
    return ctrl[1];
}

TitleCtrl * card_get_ctrl(void);
s32 card_result(void) {
    return card_get_ctrl()->result;
}

extern void *(*slot_094)(s32 a0, s32 a1, const char *pattern, DirEntry *entry);
extern void *(*slot_086)(DirEntry *entry);
/* Sums the sizes of all matches for "*" rounded up to 8 KiB blocks and
   returns 1 when the total fits in 0x1DFFF (0x1DFFF is the limit). */
s32 card_has_room(void) {
    DirEntry entry;
    void *found;
    void *first;
    s32 total;
    s32 size;
    s32 blocks;

    total = 0;
    found = slot_094(0, 0, "*", &entry);
    if (found == &entry) {
        first = found;
        do {
            size = entry.size;
            blocks = size + 0x1FFF;
            if (blocks < 0) {
                blocks = size + 0x3FFE;
            }
            blocks >>= 13;
            size = blocks << 13;
            total += size;
        } while (slot_086(&entry) == first);
    }
    return total <= 0x1DFFF;
}

extern s32 (*slot_090)(s32, s32, s32, s32);
s32 card_write_file(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    s32 (**slot_092_ptr)(s32, s32, s32, s32, s32, s32, s32);
    s32 result;

    slot_092_ptr = (s32 (**)(s32, s32, s32, s32, s32, s32, s32))0x80010248;
    result = (*slot_092_ptr)(a0, a1, a2, a3, a4, a5, a6);
    (*(void (**)(s32))0x80010408)(0);
    if (result == -1) {
        result = slot_090(a0, a1, a2, 0x2000);
        (*(void (**)(s32))0x80010408)(0);
        if (result == 0) {
            result = (*slot_092_ptr)(a0, a1, a2, a3, a4, a5, a6);
        } else {
            result = -1;
        }
    }
    return result;
}

extern s32 card_op;
void card_exit(void) {
    TitleCtrl *work = card_get_ctrl();

    card_op = 5;
    work->done = 0;
}

void card_format(s32 value) {
    TitleCtrl *ctrl = card_get_ctrl();
    ctrl->value = value;
    card_op = 1;
    ctrl->done = 0;
}

void card_free_space(void) {
    TitleCtrl *work = card_get_ctrl();

    card_op = 2;
    work->done = 0;
}

/* Fills the request block and sets the title sub-state to 3. */
void card_read(s32 a, s32 b, s32 c, s32 d, s32 e) {
    TitleCtrl *req;

    req = card_get_ctrl();
    req->file_name = a;
    req->buffer = b;
    req->size = c;
    req->offset = d;
    card_op = 3;
    req->done = 0;
    req->value = e;
}

/* Fills the request block and sets the title sub-state to 4. */
void card_write(s32 a, s32 b, s32 c, s32 d, s32 e) {
    TitleCtrl *req;

    req = card_get_ctrl();
    req->file_name = a;
    req->buffer = b;
    req->size = c;
    req->offset = d;
    card_op = 4;
    req->done = 0;
    req->value = e;
}

extern s32 title_card_state;

s32 card_status(void) {
    return title_card_state;
}

/* Maps the title sub-state to a result code stored at out[1]. States 1-4
 * are one-shot: they store their code and reset the sub-state to 0. */
void card_take(s32 *out) {
    switch (card_op) {
    case 0:
        out[1] = 1;
        break;
    case 1:
        out[1] = 2;
        card_op = 0;
        break;
    case 2:
        out[1] = 3;
        card_op = 0;
        break;
    case 3:
        out[1] = 4;
        card_op = 0;
        break;
    case 4:
        out[1] = 5;
        card_op = 0;
        break;
    case 5:
        out[1] = 6;
        break;
    }
}

s32 card_op_result_get(void) {
    return card_get_ctrl()->done;
}

extern s32 card_checksum_verify(u32 size, s32 *data);
extern void card_checksum_store(u32 size, s32 *data);
extern s32 (*slot_084)(s32, s32);
extern s32 (*slot_087)(s32, s32);
extern s32 (*slot_091)(s32, s32, s32, s32, s32, s32, s32);
extern void (*slot_102)(s32);
void title_memcard_thread(void) {
    TitleCtrl *ctrl = card_get_ctrl();
    s32 one = 1;
    s32 four = 4;
    s32 r;

    for (;;) {
        switch (ctrl->state) {
        case 0:
            card_take((s32 *)ctrl);
            break;
        case 1:
            if (card_op == 5) {
                ctrl->state = 6;
                break;
            }
            r = slot_087(0, 0);
            switch (r) {
            case 0:
                title_card_state = one;
                ctrl->wait_count = four;
                break;
            case -2:
                title_card_state = 2;
                ctrl->wait_count = four;
                break;
            case -4:
                if (--ctrl->wait_count >= 0) {
                    continue;
                }
                ctrl->wait_count = four;
                title_card_state = 3;
                break;
            default:
                if (--ctrl->wait_count >= 0) {
                    continue;
                }
                ctrl->wait_count = four;
                title_card_state = 2;
                break;
            }
            ctrl->state = 0;
            break;
        case 2:
            r = slot_084(0, 0);
            if (r == 0 && --ctrl->value >= 0) {
                continue;
            }
            ctrl->result = r;
            ctrl->state = one;
            ctrl->done = one;
            title_card_state = 0;
            break;
        case 3:
            ctrl->result = card_has_room();
            ctrl->state = 0;
            ctrl->done = one;
            break;
        case 4:
            r = slot_091(0, 0, ctrl->file_name, ctrl->buffer, ctrl->size, ctrl->offset, 0);
            if (r != ctrl->size) {
                if (r != -1 && --ctrl->value >= 0) {
                    break;
                }
                ctrl->result = r;
            } else if (card_checksum_verify(0x298, (s32 *)ctrl->buffer) == one) {
                ctrl->result = r;
            } else {
                ctrl->result = 0x7B5;
            }
            ctrl->state = 0;
            ctrl->done = one;
            break;
        case 5:
            card_checksum_store(0x298, (s32 *)ctrl->buffer);
            r = card_write_file(0, 0, ctrl->file_name, ctrl->buffer, ctrl->size, ctrl->offset, 0);
            if (r == ctrl->size) {
                ctrl->result = r;
                ctrl->state = 0;
                ctrl->done = one;
            } else if (--ctrl->value < 0) {
                ctrl->result = r;
                ctrl->state = 0;
                ctrl->done = one;
            }
            break;
        case 6:
        default:
            break;
        }
        slot_102(0);
    }
}

void card_checksum_store(u32 size, s32 *data) {
    s32 unused;
    u32 i;
    s32 sum = 0;

    for (i = 0; i < size >> 2; i++) {
        sum += *data++;
    }
    if (sum == 0) goto one;
    if (sum == -1) goto two;
    *data = sum;
    return;
one: sum = 1; goto st;
two: sum = 2;
st:
    *data = sum;
}

s32 card_checksum_verify(u32 size, s32 *data) {
    s32 unused[2];
    u32 i = 0;
    u32 count = size >> 2;
    s32 stored = data[count];
    u32 sum = 0;

    if (count != 0) {
        do {
            sum += *data++;
            i++;
        } while (i < count);
    }
    switch (sum) {
    case 0:
        sum = 1;
        break;
    case -1:
        sum = 2;
        break;
    }
    return sum == stored;
}

/* Copies a NUL-terminated string from src to dst, including the terminator. */
void str_copy(char *src, char *dst) {
    char c;

    do {
        c = *src++;
        *dst++ = c;
    } while (c != '\0');
}

s32 title_str_length(s32 text_addr) {
    s32 len = 0;
    u8 *str = (u8 *)text_addr;

    while (*str++ != 0) {
        len++;
    }
    return len;
}

void mem_copy(s32 arg0, u8 *arg1, u8 *arg2) {
    s32 var_a0;
    u8 *var_a1;
    u8 *var_a2;
    u8 temp_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    if (var_a0 > 0) {
        do {
            temp_v0 = *var_a1;
            var_a1 += 1;
            var_a0 -= 1;
            *var_a2 = temp_v0;
            var_a2 += 1;
        } while (var_a0 > 0);
    }
}

void mem_fill(s8 *arg0, s32 arg1, s8 arg2) {
    s32 var_a1;
    s8 *var_a0;

    var_a0 = arg0;
    var_a1 = arg1;
    if (var_a1 > 0) {
        do {
            *var_a0 = arg2;
            var_a1 -= 1;
            var_a0 += 1;
        } while (var_a1 > 0);
    }
}

extern TitleCtl title_timer_ctl;
extern TitleTaskRec title_timer_rec;
void title_start_update();  /* a function reached by pointer */
extern s32 title_timer_delay;
extern s32 title_video_is_pal(void);
void title_timer_init(void) {
    TitleCtl *ctl = &title_timer_ctl;
    TitleTaskRec *rec;
    s32 delay;

    task_reset(ctl);
    rec = &title_timer_rec;
    FAKE_OPAQUE(rec);
    task_set((TitleTaskRec *)ctl, 0, (s32)&title_start_update, 0, (s32)rec);
    delay = title_video_is_pal();
    if (delay == 1) {
        delay = 0x5DC;
    } else {
        delay = 0x708;
    }
    title_timer_delay = delay;
    rec->draw_fn = 0;
}

void title_ctl_start(void) {
    task_start(0, &title_timer_ctl, 0);
}

extern s16 D_8016C1F0;
extern s16 D_801178E8;
extern s32 logo_shown(void);
extern u32 title_start_combo[];
extern u32 title_seq_timer;
extern u32 title_total_frames;
extern void title_entries_fade_out(u32 mask);
extern void tasks_restart_with(struct TitleListNode *node);
void title_restart_entries(void);
extern void title_timer_start(s32 a);
extern void title_seq_fade_in(s32 a);
extern s32 title_is_ready(void);
extern void title_screen_show(s32 a);
extern s32 func_800B14BC(void);
extern void title_seq_set_enabled(s32 a);
extern void title_entries_set_rate(s32 a);
s32 title_ratio_get(void);
extern void func_800A1C2C(void);
extern u8 title_row_scroll_task[];
extern u8 title_fade_task[];
extern u8 title_waves_task[];
extern u8 title_ctl_reset_task[];
extern u8 title_ramp_task[];
extern u8 title_list_tasks[];
extern u8 title_seq_task_b[];
extern u8 title_seq_task_c[];
extern u8 title_seq_task_d[];
extern u8 title_seq_task_e[];
extern u8 D_80117600[];
extern u8 D_80117628[];
extern u8 D_80117678[];
extern u8 title_scene_task[];
void title_start_update(TitleSeqNode *node) {
    TitleSeqState *st = node->state;
    u32 *input;
    TitleSys *sys;
    s32 i;
    u8 *p;
    u8 one;

    input = title_get_pad_state(node);
    sys = (TitleSys *)title_shared_state_get();
    if (sys->unk_D4 != 1 && title_is_t_build() == 0 && D_8016C1F0 == 0 && D_801178E8 == 0
        && logo_shown() == 1) {
        if (input[1] == title_start_combo[st->idle]) {
            st->idle++;
            if (st->idle >= 0xA) {
                sys->unk_D4 = 1;
                st->idle = 0;
                title_entries_reset(0x607FF);
                one = 1;
                i = 0x10;
                p = sys->flags_34;
                sys->unk_B8 = 0xD;
                do {
                    p[0x80] = one;
                    i--;
                    p--;
                } while (i >= 0);
            }
        } else if (input[1] != 0) {
            st->idle = 0;
        }
        if (input[0x28 / 4] >= 0x3C) {
            st->idle = 0;
        }
    }
    if ((input[1] & title_input_mask()) && node->step != 0 && st->started == 0 && sys->unk_0C == 0) {
        st->started = 1;
        tasks_restart_with((struct TitleListNode *)node);
        title_entries_reset(0x1FFFF);
        title_seq_timer = 0;
        node->step = 0xC;
    }
    switch (node->step) {
    case 0:
    restart:
        title_total_frames = 0;
        title_seq_timer = 0;
        st->started = 0;
        for (i = 0; i < 3; i++) {
            s32 *r = title_rec_get(i);
            r[0x50 / 4] = 0;
            r[0x54 / 4] = 0;
            r[0x58 / 4] = 0;
        }
        title_input_unlock();
        title_queue_clear();
        title_pad_clear();
        tasks_restart_with((struct TitleListNode *)node);
        title_restart_entries();
        if (sys->unk_0C != 0) {
            st->started = 1;
            title_seq_timer = 0;
            node->step = 1;
        } else {
            sys->unk_0C = 0;
            if (sys->unk_C8 == 1) {
                title_input_lock();
                title_seq_timer = 0;
            node->step = 4;
            } else {
                title_seq_timer = 0;
            node->step = 6;
            }
        }
        break;
    case 1:
        title_pos_reset(1);
        title_seq_timer = 0;
        node->step = 2;
        break;
    case 2:
        if (title_seq_timer < 4) {
            break;
        }
        task_start((s32)node, title_cells_task, 0);
        task_start(0, title_row_scroll_task, 0);
        task_start((s32)node, title_fade_task, 0);
        task_start((s32)node, title_waves_task, 0);
        task_start((s32)node, title_sprites_ctl, 0);
        func_800AD56C(0);
        title_timer_start(0x1E);
        title_seq_fade_in(0x1E);
        title_seq_timer = 0;
        node->step = 3;
        break;
    case 3:
        if (title_is_ready() != 1) {
            break;
        }
        func_800AD56C(1);
        title_seq_timer = 0;
        node->step = 0xD;
        break;
    case 4:
        title_screen_show(0);
        title_seq_timer = 0;
        node->step = 5;
        break;
    case 5:
        if (title_seq_timer < 5) {
            break;
        }
        title_input_unlock();
        title_set_disp_mask(1);
        title_seq_timer = 0;
        node->step = 6;
        break;
    case 6:
        task_start((s32)node, title_ctl_reset_task, 0);
        task_start((s32)node, title_cells_task, 0);
        task_start(0, title_row_scroll_task, 0);
        title_entries_reset(0xA0B0C);
        title_seq_timer = 0;
        node->step = 7;
        break;
    case 7:
        if (title_seq_timer < 2) {
            break;
        }
        task_start((s32)node, title_ramp_task, 0);
        title_seq_timer = 0;
        node->step = 8;
        break;
    case 8:
        if (title_seq_timer == 0x61) {
            title_entries_reset(0x607FF);
        }
        if (title_seq_timer == 0x82) {
            task_start((s32)node, title_list_tasks, 0);
        }
        if (title_seq_timer == 0x90) {
            task_start((s32)node, title_seq_task_b, 0);
        }
        if (title_seq_timer == 0x9E) {
            task_start((s32)node, title_seq_task_c, 0);
        }
        if (title_seq_timer == 0xAC) {
            task_start((s32)node, title_seq_task_d, 0);
        }
        if (title_seq_timer < 0xBA) {
            break;
        }
        task_start((s32)node, title_seq_task_e, 0);
        title_seq_timer = 0;
        node->step = 9;
        break;
    case 9:
        if (title_seq_timer < 0x23) {
            break;
        }
        title_entries_reset(0x809FF);
        task_start((s32)node, title_task_rec, 0);
        title_seq_timer = 0;
        node->step = 10;
        break;
    case 10:
        if (title_seq_timer == 0x32) {
            task_start((s32)node, D_80117600, 0);
        }
        if (title_seq_timer == 0x3A) {
            task_start((s32)node, D_80117628, 0);
        }
        if (title_seq_timer == 0x42) {
            task_start((s32)node, D_80117678, 0);
        }
        if (title_seq_timer < 0x7E) {
            break;
        }
        title_entries_reset(0x131415);
        title_cursor_set_pos(4, 0);
        title_seq_timer = 0;
        node->step = 11;
        break;
    case 11: {
        u8 *q;
        if (title_seq_timer < 0x12) {
            goto tail;
        }
        title_flag_test_set(D_80117600);
        i = 0;
        title_flag_test_set(D_80117628);
        title_flag_test_set(D_80117678);
        title_flag_test_set(title_task_rec);
        q = title_list_tasks;
        do {
            title_flag_test_set(q);
            i++;
            q += 0x28;
        } while (i < 5);
        logo_show(0, 0, 1);
        title_panel_open(0, 0, 1);
        task_start(0, title_scene_task, 0);
        task_start((s32)node, title_waves_task, 0);
        title_highlight_set_pos(0x60, 0);
        title_rec_place(0, 1);
        title_seq_fade_in(1);
        input[0x28 / 4] = 1;
        st->started = 1;
        title_seq_timer = 0;
        node->step = 0xD;
        break;
    }
    case 12:
        task_start((s32)node, title_cells_task, 0);
        task_start(0, title_row_scroll_task, 0);
        task_start((s32)node, title_fade_task, 0);
        task_start(0, title_scene_task, 0);
        task_start((s32)node, title_waves_task, 0);
        title_entries_fade_out(0xA0B0C);
        title_entries_fade_out(0x16FFFF);
        title_entries_fade_out(0x607FF);
        title_entries_fade_out(0x809FF);
        title_entries_fade_out(0x131415);
        title_seq_fade_in(1);
        title_panel_open(0, 0, 1);
        title_rec_place(0, 1);
        logo_show(0, 0, 1);
        input[0x28 / 4] = 1;
        title_seq_timer = 0;
        node->step = 0xD;
        break;
    case 13:
        if (func_800B14BC() != 0) {
            break;
        }
        if (logo_shown() != 1) {
            break;
        }
        if (sys->unk_0C != 0 || D_8016C1F0 != 0 || D_801178E8 != 0) {
            break;
        }
        if (input[0x28 / 4] <= st->pad_wait) {
            break;
        }
        title_input_lock();
        title_pos_reset(0x14);
        title_seq_set_enabled(0);
        title_entries_set_rate(0x14);
        title_seq_timer = 0;
        node->step = 0xE;
        break;
    case 14:
        if (title_ratio_get() != 0) {
            break;
        }
        title_seq_timer = 0;
        node->step = 0xF;
        break;
    case 15:
        if (title_seq_timer < 4) {
            break;
        }
        title_seq_timer = 0;
        node->step = 0;
        sys->unk_C8 = 1;
        func_800A1C2C();
        goto restart;
    }
tail:
    if (title_total_frames <= 0x34BBF) {
        title_total_frames++;
    }
    if (title_seq_timer <= 0x34BBF) {
        title_seq_timer++;
    }
}

extern void (*slot_0B3)(void);
extern void (*slot_0BD)(void);
extern void (*slot_0B9)(s32);
extern void (*slot_0B7)(s32);
void title_tones_load(void);
/* Title stage setup: runs the service calls, then the two table entries
 * at 0x8001070C (called with 0), then the mode setup. */
void apply_sound_mode(void);
void title_setup(void) {
    void (**unk_8001070C)(s32);

    slot_0B3();
    unk_8001070C = (void (**)(s32))0x8001070C;
    slot_0BD();
    (*unk_8001070C)(0);
    (*unk_8001070C)(0);
    slot_0B9(0);
    slot_0B7(0);
    slot_0A4(0x3FFF);
    slot_0A8(0x3FFF);
    apply_sound_mode();
    title_tones_load();
}
