/**
 * Exercise: 1-18
 * Write a program to remove trailing blanks and tabs from each line of input,
 * and to delete entirely blank lines.
 */
#include <stdio.h>

#define MAX_CHARS_PER_LINE 1000 /* maximum input line length */

int getLine(char line[], int maxLength);
int trim(char trimmed[], char base[]);

/* print the longest input line */
int main()
{
    int currLength = 0;                   /* current line length */
    char currLine[MAX_CHARS_PER_LINE];    /* current input line */
    char trimmedLine[MAX_CHARS_PER_LINE]; /* current input line */

    while ((currLength = getLine(currLine, MAX_CHARS_PER_LINE)) > 0)
    {

        if (trim(trimmedLine, currLine) > 0)
        {
            printf("trimmed line:\t\"%s\"\n", trimmedLine);
        }
    }

    return 0;
}

int getLine(char line[], int maxLength)
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

    for (lineLength = lineLength; lineLength < maxLength - 1; ++lineLength)
        line[lineLength] = '\0';

    return lineLength;
}

int trim(char trimmed[], char base[])
{
    for (int i = 0; i < MAX_CHARS_PER_LINE; i++)
    {
        trimmed[i] = 0;
    }

    int lastSpace = MAX_CHARS_PER_LINE - 1;

    while (base[lastSpace] == '\0' || base[lastSpace] == '\n' || base[lastSpace] == '\t' || base[lastSpace] == ' ')
    {
        lastSpace--;
    }

    for (int i = 0; i <= lastSpace; i++)
    {
        trimmed[i] = base[i];
    }

    return lastSpace + 1;
}