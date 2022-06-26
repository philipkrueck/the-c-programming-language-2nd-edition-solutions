/**
 * Exercise: 1-8
 * Write a program to count blanks, tabs, and newlines.
 */
#include <stdio.h>

int main()
{
    int numberOfNewLines, numberOfBlanks, numberOfTabs;
    int character;

    numberOfNewLines = 0;
    numberOfBlanks = 0;
    numberOfTabs = 0;

    while ((character = getchar()) != EOF)
    {
        if (character == '\n')
            ++numberOfNewLines;

        if (character == ' ')
            ++numberOfBlanks;

        if (character == '\t')
            ++numberOfTabs;
    }

    printf("newlines: %d, blanks: %d, tabs: %d\n", numberOfNewLines, numberOfBlanks, numberOfTabs);

    return 0;
}