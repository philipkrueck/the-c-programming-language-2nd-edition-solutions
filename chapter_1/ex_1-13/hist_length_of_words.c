/**
 * Exercise: 1-12
 * Write a program to print a histogram of the lengths of words in its input.
 * It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.
 */
#include <stdio.h>
#define IN 1                    /* inside a word */
#define OUT 0                   /* outside a word */
#define MAX_LENGTH 12           /* assume words aren't longer than 20 characters */
#define MAX_HISTOGRAM_HEIGHT 12 /* Max height of histogram -> we could actually figure this out programmatically */

int main()
{
    int currentLength, state, lengthsWithCount[MAX_LENGTH];
    char currentChar;

    currentLength = 0;
    state = OUT;

    for (int i = 0; i <= MAX_LENGTH; i++)
    {
        lengthsWithCount[i] = 0;
    }

    while ((currentChar = getchar()) != EOF)
    {
        if (currentChar != '\n' && currentChar != '\t' && currentChar != ' ')
        {
            ++currentLength;
            state = IN;
        }
        else if (state)
        {
            ++lengthsWithCount[currentLength];
            state = OUT;
            currentLength = 0;
        }
    }

    /* print histogram with horizontal bars */
    printf(" -- horizontal bars --\n");
    for (int i = 1; i <= MAX_LENGTH; i++)
    {
        printf("%2d: ", i);
        for (int j = 1; j <= lengthsWithCount[i]; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    /* print histogram with horizontal bars */
    printf("\n -- vertical bars --\n");
    for (int currentHeight = MAX_HISTOGRAM_HEIGHT; currentHeight > 0; currentHeight--)
    {
        for (int currentWordLength = 1; currentWordLength <= MAX_LENGTH; currentWordLength++)
        {
            int wordsWithCurrentWordLength = lengthsWithCount[currentWordLength];
            if (wordsWithCurrentWordLength >= currentHeight)
            {
                printf(" *");
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }

    for (int currentWordLength = 1; currentWordLength <= MAX_LENGTH; currentWordLength++)
    {
        printf(" %d", currentWordLength);
    }
    printf("\n");

    return 0;
}
