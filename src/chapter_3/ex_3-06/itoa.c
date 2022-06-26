/**
 * Exercise 3-4
 * Write a version of itoa that accepts three arguments instead of two.
 * The third argument is a minimum field width;
 * the converted number must be padded with blanks on the left if necessary to make it wide enough.
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

/* functions */
void itoa(int n, char s[], int minFieldWidth);
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
    itoa(n, convertedString, 8);
    printf("%d converts to string \"%s\"\n", n, convertedString);
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[], int minFieldWidth)
{
    int i = 0;
    int isNegative = n < 0;

    do
    {                               /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0'; /*getnextdigit*/
    } while ((n /= 10) != 0);

    if (isNegative)
        s[i++] = '-';

    while (i < minFieldWidth)
    {
        s[i++] = '0';
    }

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