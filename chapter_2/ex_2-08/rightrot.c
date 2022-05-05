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
unsigned rightrot(unsigned x, unsigned n);

int main(void)
{
    printf("updated bits: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(rightrot(5, 3))); /* 10100000 */
    return 0;
}

unsigned rightrot(unsigned x, unsigned n)
{
    while (n > 0)
    {
        if (x & 1)                     /* rightmost bit of x is 1 */
            x = (x >> 1) | 0b10000000; /* we assume an 8-bit integer */
        else                           /* rightmost bit of x is 0 */
            x = x >> 1;
        --n;
    }
    return x;
}

/*
 * NOTE: The implemenation has been done for 8-bit integers as this is easy to print out.
 * Conceptually the implementation would work for any size integers with a minor adjustment
 * to line 33.
 */