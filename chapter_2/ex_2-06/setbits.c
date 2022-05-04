/**
 * Exercise 2-5
 * Write a function `setbits(x,p,n,y)` that returns `x` with the `n` bits that begin at position `p` set to the rightmost `n` bits of `y`,
 * leaving the other bits unchanged.
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
unsigned int setBits(int x, int p, int n, int y);

int main()
{
    unsigned int x = 0b10101100;
    unsigned int y = 0b00110100;
    unsigned int z = setBits(x, 5, 4, y);

    printf("updated bits: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(z));
    printf("\n");

    return 0;
}

unsigned int setBits(int x, int p, int n, int y)
{
    unsigned int maskOne = (~(~0 << (p + 1 - n)) | (~0 << (p + 1))) & x;
    unsigned int maskTwo = (y & (~(~0 << n))) << (p + 1 - n);

    return maskOne | maskTwo;
}
