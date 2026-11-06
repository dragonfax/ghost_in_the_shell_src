/* lz: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Bit/byte reader state of the stage record decompressor. The asm keeps it in registers shared by both
   functions: $t8 src, $t7 word, $t6 bytes_left, $t0 bits, $t1 mark. */
typedef struct {
    u32 *src;        /* next input word */
    u32 word;        /* current input word, consumed low byte first */
    s32 bytes_left;  /* bytes of word still to hand out after the current one */
    u32 bits;        /* control bits, MSB first, with a sentinel bit below them */
    u32 mark;        /* value of bits when the current byte's 8 bits are used up */
} LzStream;

/* Loads the next input word. The original is hand-written asm: the asm has no arguments, it
   works on $t6/$t7/$t8 and is entered with bltzal from lz_decompress (so $ra is the caller's). */
void lz_refill_word(LzStream *s) {
    s->bytes_left = 2;
    s->word = *s->src++;
}

static u32 lz_byte(LzStream *s) {
    s->word >>= 8;
    if (s->bytes_left < 0) {
        lz_refill_word(s);
    }
    s->bytes_left--;
    return s->word & 0xFF;
}

/* Next control bit; every 8th call takes a fresh byte of the stream for the next 8 bits. */
static u32 lz_bit(LzStream *s) {
    if (s->bits != s->mark) {
        s->bits <<= 1;
    } else {
        s->bits = (lz_byte(s) << 24) + 1;
        s->mark = s->bits << 7;
    }
    return s->bits >> 31;
}

/* Stage record decompressor (LZ, format as scripts/unpex.py): src is the compressed stream, dest the output;
   returns the number of bytes written. A 0 bit copies a literal byte; a 1 bit starts a match: the next bit
   picks a short offset (one byte, 0 ends the stream) or a long one (a byte plus 4 bits, +255 further back),
   then an Elias-gamma style length, then the copy from dest + offset (offset < 0). Some callers pass a third
   argument (a mask); it is not used, hence the "...". The original is hand-written asm: the asm keeps the reader
   state in registers and refills it by calling lz_refill_word with bltzal, and uses trapping add/sub. */
s32 lz_decompress(u32 *src, u8 *dest, ...) {
    LzStream s;
    u8 *out = dest;
    u8 *from;
    s32 offset;
    s32 len;
    u32 byte;
    u32 nibble;
    u32 long_offset;
    u32 d;
    s32 i;

    s.src = src;
    s.bytes_left = -1;
    s.bits = 0;
    s.mark = 0;
    for (;;) {
        if (!lz_bit(&s)) {
            *out++ = lz_byte(&s);
            continue;
        }
        long_offset = lz_bit(&s);
        byte = lz_byte(&s);
        if (!long_offset) {
            if (byte == 0) {
                break;
            }
            offset = (s32) byte - 256;
        } else {
            nibble = 0;
            for (i = 0; i < 4; i++) {
                nibble = (nibble << 1) | lz_bit(&s);
            }
            offset = (s32) (0xFFFFF000 | (byte << 4) | nibble) - 255;
        }
        from = out + offset;
        len = 1;
        if (lz_bit(&s)) {
            do {
                d = lz_bit(&s);
                len = (len << 1) | d;
            } while (lz_bit(&s));
        }
        while (len-- > 0) {
            *out++ = *from++;
        }
    }
    return out - dest;
}
