/**
 * Exercise 3-4
 * In a two's complement number representation, our version of itoa does not handle the largest negative number,
 * that is, the value of n equal to `-(2^(wordsize-1))`.
 * Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

/* functions */
void itoa(int n, char s[]);
void convertAndPrint(int n);
void reverse(char str[]);

int main(void)
{
    convertAndPrint(9);
    convertAndPrint(11993);
    convertAndPrint(INT_MAX);
    convertAndPrint(INT_MIN);
}

void convertAndPrint(int n)
{
    char convertedString[100];
    itoa(n, convertedString);
    printf("%d converts to string \"%s\"\n", n, convertedString);
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i = 0;
    int isNegative = n < 0;

    do
    {                               /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0'; /*getnextdigit*/
    } while ((n /= 10) != 0);

    if (isNegative)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

void reverse(char str[])
{
    int n = strlen(str);

    for (int i = 0; i < n / 2; i++)
    {
        char ch = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = ch;
    }
}

/**
 * NOTE: The largest possible number INT_MIN -(2`(wordsize-1)) is not properly handeled by `itoa` because it
 * is first converted into a positive number 2`(wordsize-1). However, INT_MAX is one less: 2`(wordsize-1)-1.
 * Therefore, the converted integer overflows and all following calculations are incorrect.
 */