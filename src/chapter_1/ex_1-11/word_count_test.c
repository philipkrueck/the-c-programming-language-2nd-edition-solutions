/**
 * Exercise: 1-11
 * How would you test the word count program?
 * What kinds of input are most likely to uncover bugs if there are any?
 */
#include <stdio.h>
#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */

int main()
{
    char currentChar;
    int numberOfLines, numberOfWords, numberOfCharacters;

    int state = OUT;
    numberOfLines = numberOfWords = numberOfCharacters = 0;

    while ((currentChar = getchar()) != EOF)
    {
        ++numberOfCharacters;
        if (currentChar == '\n')
        {
            ++numberOfLines;
        }
        if (currentChar == '\n' || currentChar == '\t' || currentChar == ' ')
        {
            state = OUT;
        }
        else if (state == OUT)
        {
            ++numberOfWords;
            state = IN;
        }
    }
    printf("number of lines: %d, number of words: %d, number of characters: %d\n", numberOfLines, numberOfWords, numberOfCharacters);

    return 0;
}
