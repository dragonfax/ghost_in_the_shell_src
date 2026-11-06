#ifndef INCBIN_H
#define INCBIN_H

/* A data object whose bytes are a file under src/ (an image or other binary asset). */
#define INCBIN(NAME, FILE) \
    __asm__(".data\n.globl " #NAME "\n" #NAME ":\n.incbin \"" FILE "\"\n")

#endif
