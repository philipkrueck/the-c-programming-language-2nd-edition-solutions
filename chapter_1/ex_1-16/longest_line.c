/**
 * Exercise: 1-16
 * Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrary long input lines,
 * and as much as possible of the text.
 */
#include <stdio.h>

#define MAX_CHARS_PER_LINE 1000 /* maximum input line length */

int getline(char line[], int maxLength);
void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
    int currLength = 0;                /* current line length */
    int maxLength = 0;                 /* maximum line length seen so far */
    int prevMax = 0;                   /* number of characters if line overflows */
    int isOverflowing = 0;             /* boolean indicating whether there was an overflow and we should get another line */
    char currLine[MAX_CHARS_PER_LINE]; /* current input line */
    char tempLine[MAX_CHARS_PER_LINE]; /* start of line if we have an overflow */
    char maxLine[MAX_CHARS_PER_LINE];  /* longest line saved here */

    while ((currLength = getline(currLine, MAX_CHARS_PER_LINE)) > 0)
    {
        if (currLine[currLength - 1] != '\n') /* check if we have an overflow */
        {
            if (isOverflowing == 0) /* check if it's the first overflow for the current line */
            {
                copy(tempLine, currLine);
                isOverflowing = 1;
            }
            prevMax += currLength;
        }
        else /* we found a line break */
        {
            if (isOverflowing == 1) /* did we have an overflow? */
            {
                currLength = currLength + prevMax;
                if (currLength > maxLength)
                {
                    maxLength = currLength;
                    copy(maxLine, tempLine);
                }
                isOverflowing = 0;
                prevMax = 0;
            }
            else
            {
                if (currLength > maxLength)
                {
                    maxLength = currLength;
                    copy(maxLine, currLine);
                }
            }
        }
    }

    if (maxLength > 0)
    {
        printf("longest line length: %d\n", maxLength);
        printf("longest line: \"%s\"\n", maxLine);
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

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        i++;
}