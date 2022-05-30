/**
 * Exercise: 1-19
 * Write a function reverse(s) that reverses the character string s.
 * Use it to write a program that reverses its input a line at a time.
 */
#include <stdio.h>

#define MAX_CHARS_PER_LINE 1000 /* maximum input line length */

int getline(char line[], int maxLength);
void removeLineBreak(char line[]);
void reverse(char line[]);
int length(char line[]);

int main()
{
    int currLength;                    /* current line length */
    char currLine[MAX_CHARS_PER_LINE]; /* current input line */

    while ((currLength = getline(currLine, MAX_CHARS_PER_LINE)) > 0)
    {
        removeLineBreak(currLine);
        reverse(currLine);
        printf("%s\n", currLine);
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

    return lineLength;
}

void removeLineBreak(char line[])
{
    int i;
    for (i = 0; line[i] != '\n'; i++)
        ;
    line[i] = 0;
}

void reverse(char line[])
{
    int startIdx = 0;
    int endIdx = length(line) - 1;
    char tmp;

    while (endIdx > startIdx)
    {
        char tmp = line[startIdx];
        line[startIdx] = line[endIdx];
        line[endIdx] = tmp;

        startIdx++;
        endIdx--;
    }
}

int length(char line[])
{
    int i;
    for (i = 0; line[i] != '\0'; i++)
        ;
    return i;
}