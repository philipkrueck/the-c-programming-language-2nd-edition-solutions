/**
 * Exercise 2-1
 * Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned,
 * by printing appropriate values from standard headers and by direct computation.
 * Harder if you compute them: determine the ranges of the various floating-point types.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

/* functions */
void printStdLibraryRanges();
void printComputedRanges();
void printSignedCharRange();
void printUnsignedCharRange();
void printSignedShortRange();
void printUnsignedShortRange();
void printSignedIntRange();
void printUnsignedIntRange();
void printSignedLongRange();
void printUnsignedLongRange();
void printFloatRange();
void printDoubleRange();

int main()
{
    printf("**** Standard Library Ranges ****\n");
    printStdLibraryRanges();
    printf("\n**** Standard Library Ranges ****\n");
    printComputedRanges();
    return 0;
}

void printStdLibraryRanges()
{
    /* char */
    printf("signed char: (min: %d, max: %d)\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char: (min: %d, max: %d)\n", 0, UCHAR_MAX);

    /* short */
    printf("signed short: (min: %d, max: %d)\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: (min: %d, max: %d)\n", 0, USHRT_MAX);

    /* int */
    printf("signed int: (min: %d, max: %d)\n", INT_MIN, INT_MAX);
    printf("unsigned int: (min: %d, max: %u)\n", 0, UINT_MAX);

    /* long */
    printf("signed long: (min: %ld, max: %ld)\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: (min: %d, max: %lu)\n", 0, ULONG_MAX);

    /* float */
    printf("float: (min: %g, max: %g)\n", FLT_MIN, FLT_MAX);

    /* double */
    printf("double: (min: %lg, max: %lg)\n", DBL_MIN, DBL_MAX);

    /* long double */
    printf("double: (min: %Lg, max: %Lg)\n", LDBL_MIN, LDBL_MAX);
}

void printComputedRanges()
{
    /* char */
    printSignedCharRange();
    printUnsignedCharRange();

    /* short */
    printSignedShortRange();
    printUnsignedShortRange();

    /* int */
    printSignedIntRange();
    printUnsignedIntRange();

    /* long */
    printSignedLongRange();
    printUnsignedLongRange();

    /* For floating point arithmetic, checkout [Single-precision floating-point format](https://en.wikipedia.org/wiki/Single-precision_floating-point_format) */

    /* float */
    printFloatRange();

    /* double */
    printDoubleRange();
}

void printSignedCharRange()
{
    int bits = 1;

    for (char max = 1; max > 0; max *= 2)
        bits++;

    char charMin = -pow(2, bits - 1);
    char charMax = pow(2, bits - 1) - 1;

    printf("signed char: (min: %d, max: %d)\n", charMin, charMax);
}

void printUnsignedCharRange()
{
    printf("unsigned char: (min: %d, max: %d)\n", 0, (unsigned char)-1);
}

void printSignedShortRange()
{
    int bits = 1;

    for (short int max = 1; max > 0; max *= 2)
        bits++;

    short int shortIntMin = -pow(2, bits - 1);
    short int shortIntMax = pow(2, bits - 1) - 1;

    printf("signed short: (min: %d, max: %d)\n", shortIntMin, shortIntMax);
}

void printUnsignedShortRange()
{
    printf("unsigned short: (min: %d, max: %d)\n", 0, (unsigned short)-1);
}

void printSignedIntRange()
{
    int bits = 1;

    for (int max = 1; max > 0; max *= 2)
        bits++;

    int intMin = -pow(2, bits - 1);
    int intMax = pow(2, bits - 1) - 1;

    printf("signed int: (min: %d, max: %d)\n", intMin, intMax);
}

void printUnsignedIntRange()
{
    printf("unsigned int: (min: %d, max: %u)\n", 0, (unsigned int)-1);
}

void printSignedLongRange()
{
    int bits = 1;

    for (long int max = 1; max > 0; max *= 2)
        bits++;

    printf("bits: %d\n", bits);

    long int longMin = -powl(2, bits - 1);    // power function for long data type
    long int longMax = powl(2, bits - 1) - 1; // power function for long data type

    printf("signed long: (min: %ld, max: %ld)\n", longMin, longMax);
}

void printUnsignedLongRange()
{
    printf("unsigned long: (min: %d, max: %lu)\n", 0, (unsigned long)-1);
}

void printFloatRange()
{
    float floatMin = (2 - pow(2, -23)) / pow(2, 127);
    float floatMax = (2 - pow(2, -23)) * pow(2, 127);

    printf("float: (min: %g, max: %g)\n", floatMin, floatMax);
}

void printDoubleRange()
{
    double doubleMin = (2 - pow(2, -52)) / pow(2, 1023);
    double doubleMax = (2 - pow(2, -52)) * powl(2, 1023);

    printf("double: (min: %lg, max: %lg)\n", doubleMin, doubleMax);
}