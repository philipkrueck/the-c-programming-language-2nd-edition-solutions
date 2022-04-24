/**
 * Exercise: 1-14
 * Write a program to print a histogram of the frequencies of different characters in its input.
 *
 * Note: This program will print the frequencies of lower case letters and digits
 */
#include <stdio.h>
#define NUMBER_OF_LETTERS 26
#define NUMBER_OF_DIGITS 10

int main()
{
    int totalCharCount = NUMBER_OF_LETTERS + NUMBER_OF_DIGITS;
    int currentChar, characterFrequencies[totalCharCount];

    for (int i = 0; i < totalCharCount; i++)
    {
        characterFrequencies[i] = 0;
    }

    while ((currentChar = getchar()) != EOF)
    {
        if (currentChar >= 'a' && currentChar <= 'z')
        {
            characterFrequencies[currentChar - 'a']++;
        }
        else if (currentChar >= '0' && currentChar <= '9')
        {
            characterFrequencies[currentChar - '0' + NUMBER_OF_LETTERS]++;
        }
    }

    printf("\n -- frequencies of characters --\n");
    for (int charIdx = 0; charIdx < totalCharCount; charIdx++)
    {
        if (charIdx < NUMBER_OF_LETTERS)
        {
            printf("%c: ", 'a' + charIdx);
        }
        else
        {
            printf("%c: ", '0' + charIdx - NUMBER_OF_LETTERS);
        }

        int charFrequency = characterFrequencies[charIdx];
        for (int i = 0; i < charFrequency; i++)
        {
            printf("*");
        }

        printf("\n");
    }
}