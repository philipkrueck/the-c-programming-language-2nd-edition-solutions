/**
 * Exercise: 1-16
 * Write a program to print all input lines that are longer than 80 characters.
 */
#include <stdio.h>

#define MAX_CHARS_PER_LINE 1000 /* maximum input line length */
#define LONG_LINE_LENGTH 80     /* long line length */

int getline(char line[], int maxLength);

/* print the longest input line */
int main()
{
    int currLength = 0;                /* current line length */
    char currLine[MAX_CHARS_PER_LINE]; /* current input line */

    while ((currLength = getline(currLine, MAX_CHARS_PER_LINE)) > 0)
    {
        if (currLength > LONG_LINE_LENGTH)
        {
            printf("current line length: %d\n", currLength);
            printf("current line:\t%s", currLine);
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
    line[lineLength] = '\0';
    return lineLength;
}