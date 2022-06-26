/**
 * Exercise 2-7
 * Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged.
 */
#include <stdio.h>

/* hacky fix to print binary pattern, see: https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format */
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)     \
    (byte & 128 ? '1' : '0'),    \
        (byte & 64 ? '1' : '0'), \
        (byte & 32 ? '1' : '0'), \
        (byte & 16 ? '1' : '0'), \
        (byte & 8 ? '1' : '0'),  \
        (byte & 4 ? '1' : '0'),  \
        (byte & 2 ? '1' : '0'),  \
        (byte & 1 ? '1' : '0')

/* functions */
unsigned int invert(int x, int p, int n);

int main()
{
    unsigned int x = 0b10100100;
    unsigned int z = invert(x, 5, 4);

    printf("updated bits: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(z)); // 1001 1000

    return 0;
}

unsigned int invert(int x, int p, int n)
{
    unsigned int maskOne = (~(~0 << (p + 1 - n)) | (~0 << (p + 1)));
    return (maskOne & x) | (~(~maskOne & x) & ~maskOne);
}
