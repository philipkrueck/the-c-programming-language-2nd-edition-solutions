/**
 * Exercise: 1-18
 * Write a program to remove trailing blanks and tabs from each line of input,
 * and to delete entirely blank lines.
 */
#include <stdio.h>

#define MAX_CHARS_PER_LINE 1000 /* maximum input line length */

int getline(char line[], int maxLength);
int trim(char base[]);

/* print the longest input line */
int main()
{
    int currLength = 0;                /* current line length */
    char currLine[MAX_CHARS_PER_LINE]; /* current input line */

    while ((currLength = getline(currLine, MAX_CHARS_PER_LINE)) > 0)
    {

        if (trim(currLine) > 0)
        {
            printf("trimmed line:\t\"%s\"\n", currLine);
        }
    }

    return 0;
}

int getline(char line[], int maxLength)
{
    char currChar;
    int lineLength;

    for (lineLength = 0; lineLength < maxLength - 1 && (currChar = getchar()) != EOF && currChar != '\n'; ++lineLength)
        line[lineLength] = currChar;
    if (currChar == '\n')
    {
        line[lineLength] = currChar;
        ++lineLength;
    }

    /* reset the rest of the current line back to 0 */
    for (lineLength = lineLength; lineLength < maxLength - 1; ++lineLength)
        line[lineLength] = '\0';

    return lineLength;
}

int trim(char base[])
{
    int lastSpace = MAX_CHARS_PER_LINE - 1;

    while (base[lastSpace] == '\0' || base[lastSpace] == '\n' || base[lastSpace] == '\t' || base[lastSpace] == ' ')
    {
        base[lastSpace] = 0;
        lastSpace--;
    }

    return lastSpace + 1;
}