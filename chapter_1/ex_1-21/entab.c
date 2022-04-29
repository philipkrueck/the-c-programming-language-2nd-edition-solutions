/**
 * Exercise: 1-21
 * Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing.
 * Use the same tab stops as for detab.
 * When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?
 */
#include <stdio.h>

#define TAB_WIDTH 4

int main()
{
    char character;
    int numSpaces = 0;

    while ((character = getchar()) != EOF)
    {
        if (character == ' ')
        {
            numSpaces++;
            if (numSpaces == TAB_WIDTH)
            {
                putchar('\\');
                putchar('t');
                numSpaces = 0;
            }
        }
        else
        {
            while (numSpaces > 0)
            {
                putchar(' ');
                numSpaces--;
            }
            putchar(character);

            if (character == '\n')
            {
                numSpaces = 0;
            }
        }
    }

    return 0;
}

/**
 * In Unix Systems you can use input and output redirection:
 * The commands that normally take their input from standard input, will use the input file and
 * instead of writing to standard output, the commands will write to the output file.
 *
 * > ./entab < input.txt > output.txt
 */