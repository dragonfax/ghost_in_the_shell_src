#ifndef INCBIN_H
#define INCBIN_H

/* A data object whose bytes are a file under src/ (an image or other binary asset), placed where it stands among
 * the file's definitions: cc1 writes top-level asm and initialized variables to .data in source order. */
#define INCBIN(NAME, FILE) \
    __asm__(".data\n.globl " #NAME "\n" #NAME ":\n.incbin \"" FILE "\"\n")

/* The same in .rodata, where an INCLUDE_RODATA stood: cc1 is in .text between functions, so back to .text after. */
#define INCBIN_RODATA(NAME, FILE) \
    __asm__(".section .rodata\n.globl " #NAME "\n" #NAME ":\n.incbin \"" FILE "\"\n.section .text\n")

/* A read-only table or string defined in C at its place in .rodata, under the type the code already declares for
 * it. Not `const`: a const definition needs const declarations, and passing a const array to a non-const
 * parameter crashes this cc1 (its qualifier warning), while const extern arrays could change how matched code
 * reads them. */
#if defined(__clang__) || defined(PERMUTER) || defined(M2CTX) /* the clang checks (typecheck, cast.py) */
#define RODATA /* the typecheck's clang targets the host, whose sections are named otherwise */
#else
#define RODATA __attribute__((section(".rodata")))
#endif

#endif
