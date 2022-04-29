/**
 * Exercise: 1-22
 * Write a program to `fold` long input lines into two or more shorter lines
 * after the last non-blank character that occurs before the n-th column of input.
 * Make sure your program does something intelligent with very long lines,
 * and if there are no blanks or tabs before the specified column.
 */
#include <stdio.h>

#define MAX_INPUT_LINE_LENGTH 1000 /* maximum input line length */
#define MAX_LINE_LENGTH 6          /* maximum output line length*/

int getLine(char line[], int maxLength);
void foldLine(char line[], char outputLine[], int maxLineLength);

int main()
{
    int currLength;                         /* current line length */
    char currLine[MAX_INPUT_LINE_LENGTH];   /* current input line */
    char foldedLine[MAX_INPUT_LINE_LENGTH]; /* current input line */

    while ((currLength = getLine(currLine, MAX_INPUT_LINE_LENGTH)) > 0)
    {
        if (currLength <= MAX_LINE_LENGTH)
        {
            printf("%s\n", currLine);
        }
        else
        {
            foldLine(currLine, foldedLine, MAX_LINE_LENGTH);
            printf("%s\n", foldedLine);

            /* reset foldedLine*/
            for (int i = 0; i < MAX_INPUT_LINE_LENGTH; i++)
                foldedLine[i] = '\0';
        }
    }
}

int getLine(char line[], int maxLength)
{
    char currChar;
    int lineLength;

    for (lineLength = 0; lineLength < maxLength - 1 && (currChar = getchar()) != EOF && currChar != '\n'; ++lineLength)
        line[lineLength] = currChar;

    line[lineLength] = '\0';

    return lineLength;
}

/* breaks line into multiple lines based maxLineLength and stores result in outputLine */
void foldLine(char line[], char outputLine[], int maxLineLength)
{
    int numChars = 0;      // number of characters read after the last fold
    int lastBlankIdx = -1; // keep track of last blank encountered
    int inBlankString = 0;

    for (int currPos = 0; line[currPos] != '\0'; currPos++)
    {
        outputLine[currPos] = line[currPos];
        numChars++;

        if (line[currPos] == ' ' || line[currPos] == '\t')
        {
            if (!inBlankString)
                lastBlankIdx = currPos;
            inBlankString = 1;
        }
        else
            inBlankString = 0;

        if (numChars >= maxLineLength && lastBlankIdx != -1)
        {
            outputLine[lastBlankIdx] = '\n';
            numChars = 0;
            lastBlankIdx = -1;
        }
    }
}