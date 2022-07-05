/**
 * Exercise 7-2
 * Write a program that will print arbitrary input i a sensible way.
 * As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom,
 * and break long text lines.
 **/

#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 80

int main()
{
    int c;       // current character
    int len = 0; // length of current line

    while ((c = getchar()) != EOF)
    {
        if (isprint(c))
        {
            putchar(c);
            len++;
        }
        else if (c == '\n')
        {
            putchar(c);
            len = 0;
        }
        else
        {
            printf(" 0x%02o ", c); /* replace by hex characters */
            len += 6;
        }

        if (len >= MAX_LINE_LENGTH)
        {
            len = 0;
            putchar('\n');
        }
    }
    return 0;
}