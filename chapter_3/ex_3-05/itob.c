/**
 * Exercise 3-5
 * Write the function itob(n,s,b) that converts the integer n into a base b
 * character representation in the string s.
 * In particular, itob(n,s,16) formats s as a hexadecimal integer in s.
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

/* functions */
void itob(int n, char s[], int base);
void convertAndPrint(int n, int base);
void reverse(char str[]);

int main(void)
{
    convertAndPrint(3102385, 2);
    convertAndPrint(3102385, 8);
    convertAndPrint(3102385, 10);
    convertAndPrint(3102385, 16);
}

void convertAndPrint(int n, int base)
{
    char convertedString[100];
    itob(n, convertedString, base);
    printf("%d converts to string \"%s\" in base %d\n", n, convertedString, base);
}

/* itob:  convert n to characters in s given a base up to 16*/
void itob(int n, char s[], int base)
{
    int remainder;
    int i = 0;
    int isNegative = n < 0;
    char baseDigits[16] = {'0',
                           '1',
                           '2',
                           '3',
                           '4',
                           '5',
                           '6',
                           '7',
                           '8',
                           '9',
                           'A',
                           'B',
                           'C',
                           'D',
                           'E',
                           'F'};

    do
    { /* generate digits in reverse order */
        remainder = abs(n % base);
        s[i++] = baseDigits[remainder]; /*getnextdigit*/
    } while ((n /= base) != 0);

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