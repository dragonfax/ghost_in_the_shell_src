/* stage_data: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void digits4_format(void) {
    s8 *out = digits4_out_ptr;
    s32 value;
    s32 div;
    s32 digit;
    s32 part;

    value = screenshot_counter;
    value = NOT_NEGATIVE(value < 0x2710 ? value : 0x270F);
    div = 1000;
    do {
        digit = value / div;
        part = digit * div;
        *out++ = digit + '0';
        div /= 10;
        value -= part;
    } while (div > 0);
}

void pause_block_reset(void) {
    pause_blocked_flag = 0;
}

/* Locks the pause (game frozen), only on a dev kit: its stack sits above retail's 2 MB of RAM. */
void debug_freeze(void) {
    register u32 sp asm("sp");
    s32 retail_ram = sp <= 0x80000000 + 0x200000;

    if (!retail_ram && !is_pause_blocked()) {
        pause_blocked_flag = 1;
    }
}

s32 is_pause_blocked(void) {
    return pause_blocked_flag != 0;
}

/* Pause-mode state machine: 1 = pause requested, 2 = capture the image size and start the grab,
 * 3 = write the captured block to the file, then clear the state. */
void screenshot_update(void) {
    WorkArea *work;
    s32 capture_end;
    s32 write_len;
    register s32 capture_base asm("$7");

    work = work_area_ptr;
    switch (pause_blocked_flag) {
    case 1:
        pause_blocked_flag = 2;
        return;
    case 2:
        svc_draw_sync(0);
        capture_width = work->width;
        capture_height = work->height;
        svc_store_image((s32)&work->draw_x, 0x80400004);
        pause_blocked_flag = 3;
        return;
    case 3:
        capture_base = 0x80400004;
        capture_end = capture_base + (capture_width * capture_height * 2);
        write_len = screenshot_bmp_write(capture_width, capture_height, (u16 *)0x80400004, (BmpHeader *)capture_end);
        if (write_len > 0) {
            digits4_format();
            file_write_stub((s32)screenshot_name_ptr, capture_end, write_len);
            screenshot_counter += 1;
        }
        input_reset();
        pause_blocked_flag = 0;
        return;
    }
}

/* Writes a 15-bit image as a 24-bit BMP file (rows bottom-up, B G R); returns its length. */
s32 screenshot_bmp_write(s32 width, s32 height, u16 *src, BmpHeader *bmp)
{
    s32 pixels;
    s32 imageSize;
    s32 fileSize;
    u8 *out;
    u16 *row;
    s32 x, y;
    s32 pixel, red, green, blue;

    pixels = width * height;
    if (pixels == 0) {
        return 0;
    }
    fileSize = sizeof(BmpHeader);
    bmp->dataOffsetLo = fileSize;
    imageSize = pixels * 3;
    fileSize += imageSize;
    out = (u8 *)(bmp + 1);
    y = 0;
    bmp->type = 0x4D42;
    bmp->fileSizeLo = fileSize;
    bmp->fileSizeHi = fileSize >> 16;
    bmp->reserved1 = 0;
    bmp->reserved2 = 0;
    bmp->dataOffsetHi = 0;
    bmp->infoSizeLo = 0x28;
    bmp->infoSizeHi = 0;
    bmp->widthLo = width;
    bmp->widthHi = width >> 16;
    bmp->heightLo = height;
    bmp->heightHi = height >> 16;
    bmp->planes = 1;
    bmp->bitCount = 24;
    bmp->compressionLo = 0;
    bmp->compressionHi = 0;
    bmp->imageSizeLo = imageSize;
    bmp->imageSizeHi = imageSize >> 16;
    bmp->xPelsPerMeterLo = 1;
    bmp->xPelsPerMeterHi = 0;
    bmp->yPelsPerMeterLo = 1;
    bmp->yPelsPerMeterHi = 0;
    bmp->clrUsedLo = 0;
    bmp->clrUsedHi = 0;
    bmp->clrImportantLo = 0;
    bmp->clrImportantHi = 0;
    src += width * (height - 1);
    for (; y < height; y++) {
        row = src;
        for (x = 0; x < width; x++) {
            pixel = *row++;
            blue = pixel >> 10;
            green = pixel >> 5;
            red = pixel & 0x1F;
            FAKE_OPAQUE(blue);
            FAKE_OPAQUE(green);
            FAKE_OPAQUE(red);
            *out++ = (blue & 0x1F) << 3;
            *out++ = (green & 0x1F) << 3;
            *out++ = red << 3;
        }
        src -= width;
    }
    return out - (u8 *)bmp;
}
