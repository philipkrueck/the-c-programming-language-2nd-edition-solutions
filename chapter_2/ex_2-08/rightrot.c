/**
 * Exercise 2-8
 * Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n positions.
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
unsigned int rightrot(int x, int n);

int main()
{
    unsigned int x = 0b10100100;
    unsigned int z = rightrot(x, 3);

    printf("updated bits: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(z));

    return 0;
}

unsigned int rightrot(int x, int n)
{
    unsigned int maskOne = ~x;
    return maskOne;
}
