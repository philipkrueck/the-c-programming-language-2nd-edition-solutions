/**
 * Exercise: 1-20
 * Write a program `detab` that replaces tabs in the input with the proper number of blanks to space to the next tab stop.
 * Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?
 */
#include <stdio.h>

#define TAB_WIDTH 8

int main()
{
    char character;
    int numSpaces;

    while ((character = getchar()) != EOF)
    {
        if (character == '\t')
        {
            numSpaces = TAB_WIDTH;

            while (numSpaces > 0)
            {
                putchar(' ');
                numSpaces--;
            }
        }
        else
        {
            putchar(character);
        }
    }

    return 0;
}

/**
 * In Unix Systems you can use input and output redirection:
 * The commands that normally take their input from standard input, will use the input file and
 * instead of writing to standard output, the commands will write to the output file.
 *
 * > ./detab < input.txt > output.txt
 */