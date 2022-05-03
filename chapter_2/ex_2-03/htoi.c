/**
 * Exercise 2-3
 * Write a function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value.
 * The allowable digits are 0 through 9, a through f, and A through F.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_CHARS_PER_LINE 1000 /* maximum input line length */

/* functions */
int htoi(char s[]);
int getLine(char line[], int maxLength);

#include <stdio.h>

int main()
{
    char hexString[MAX_CHARS_PER_LINE];

    getLine(hexString, MAX_CHARS_PER_LINE);

    printf("the decimal representation of the hex string \"%s\" is %d\n", hexString, htoi(hexString));
}

int getLine(char line[], int maxLength)
{
    char currChar;
    int lineLength;

    for (lineLength = 0; lineLength < maxLength - 1 && (currChar = getchar()) != EOF && currChar != '\n'; ++lineLength)
        line[lineLength] = currChar;

    /* reset the rest of the current line back to 0 */
    for (lineLength = lineLength; lineLength < maxLength - 1; ++lineLength)
        line[lineLength] = '\0';

    return lineLength;
}

int htoi(char s[])
{
    int len = strlen(s);

    if (len == 0)
    {
        return -1; // invalid hex number
    }

    int result = 0;
    int startingPos = 0;

    // skip optional `0x` or `0X` prefix
    if (s[0] == '0' && tolower(s[1]) == 'x' && s[2] != '\0')
        startingPos = 2;

    for (int i = len - 1; i >= startingPos; i--)
    {
        char currChar = tolower(s[i]);
        int decimal;

        if (isdigit(currChar))
            decimal = currChar - '0';
        else if (currChar >= 'a' && currChar <= 'f')
            decimal = currChar - 'a' + 10;
        else
            return -1; // invalid hex number

        result += decimal * pow(16, len - i - 1);
    }

    return result;
}

/*
 * NOTE:
 */