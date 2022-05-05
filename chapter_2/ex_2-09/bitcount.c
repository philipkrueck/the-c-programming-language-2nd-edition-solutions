/**
 * Exercise 2-8
 * In a two's complement number system, `x &= (x-1)` deletes the rightmost 1-bit in `x`.
 * Explain why. Use this observation to write a faster version of `bitcount`.
 *
 * NOTE:
 * The expression `x &= (x-1)` deletes the rightmost 1-bit of x because decrementing x by one
 * shifts the right most 1-bit to the right. When combined with `x` through the `AND` operation,
 * the right-most 1-bit of x will effectively be deleted.
 *
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
int bitcount(unsigned x);

int main(void)
{
    unsigned binaryNum = 0b11110000;

    printf("binary number " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(binaryNum));
    printf("number of bits: %d\n", bitcount(binaryNum));
    return 0;
}

int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x &= (x - 1))
        b++;
    return b;
}

/*
 * NOTE: The implemenation has been done for 8-bit integers as this is easy to print out.
 * Conceptually the implementation would work for any size integers with a minor adjustment
 * to line 33.
 */