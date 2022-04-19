/**
 * Exercise: 1-10
 * Write a program to copy its input to its output, replacing each tab by \t,
 * each backspace by \b, and each backslash by \\.
 * This makes tabs and backspaces visible in an unambiguous way.
 */
#include <stdio.h>

int main()
{
    char currentChar;

    while ((currentChar = getchar()) != EOF)
    {
        if (currentChar == '\t')
        {
            putchar('\\');
            putchar('\t');
        }
        else if (currentChar == 'b')
        {
            putchar('\b');
            putchar('\\');
        }
        else if (currentChar == '\\')
        {
            putchar('\\');
            putchar('\\');
        }
        else
        {
            putchar(currentChar);
        }
    }

    return 0;
}
