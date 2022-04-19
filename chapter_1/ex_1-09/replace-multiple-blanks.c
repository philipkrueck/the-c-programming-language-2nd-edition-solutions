/**
 * Exercise: 1-9
 * Write a program to copy its input to its output, replacing each string
 * of one or more blanks by a single blank.
 */
#include <stdio.h>

int main()
{
    char currentChar, lastChar;

    while ((currentChar = getchar()) != EOF)
    {
        if (lastChar != ' ' || currentChar != ' ')
        {
            putchar(currentChar);
        }
        lastChar = currentChar;
    }

    return 0;
}
