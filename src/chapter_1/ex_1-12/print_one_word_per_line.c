/**
 * Exercise: 1-12
 * Write a program that prints its input one word per line.
 */
#include <stdio.h>
#define IN 1
#define OUT 0

int main()
{
    char currentChar;
    int state;

    state = OUT;

    while ((currentChar = getchar()) != EOF)
    {
        if (currentChar != '\n' && currentChar != '\t' && currentChar != ' ')
        {
            putchar(currentChar);
            state = IN;
        }
        else if (state)
        {
            putchar('\n');
            state = OUT;
        }
    }

    return 0;
}
