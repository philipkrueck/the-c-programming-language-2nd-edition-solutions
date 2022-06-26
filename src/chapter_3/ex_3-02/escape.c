/**
 * Exercise 3-2
 * Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s.
 * Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters.
 */
#include <stdio.h>

#define MAX_CHARS_PER_LINE 1000 /* maximum input line length */

/* functions */
int getline(char line[], int maxLength);
void escape(char original[], char escaped[]);
void unescape(char escaped[], char unescaped[]);

int main(void)
{
    char originalString[MAX_CHARS_PER_LINE];
    char escapedString[MAX_CHARS_PER_LINE];
    char unescapedString[MAX_CHARS_PER_LINE];

    getline(originalString, MAX_CHARS_PER_LINE);
    printf("original string: %s", originalString);

    escape(originalString, escapedString);
    printf("escaped string: %s\n", escapedString);

    unescape(escapedString, unescapedString);
    printf("unescaped string: %s\n", unescapedString);
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

void escape(char original[], char escaped[])
{
    int i, j;
    i = j = 0;

    while (original[i] != '\0')
    {
        switch (original[i])
        {
        case '\n':
            escaped[j] = '\\';
            escaped[++j] = 'n';
            break;
        case '\t':
            escaped[j] = '\\';
            escaped[++j] = 't';
            break;
        default:
            escaped[j] = original[i];
            break;
        }
        i++;
        j++;
    }
    escaped[j] = '\0';
}

void unescape(char escaped[], char unescaped[])
{
    int i, j;
    i = j = 0;
    while (escaped[i] != '\0')
    {
        switch (escaped[i])
        {
        case '\\':
            switch (escaped[++i])
            {
            case 'n':
                unescaped[j] = '\n';
                break;
            case 't':
                unescaped[j] = '\t';
                break;
            }
            break;
        default:
            unescaped[j] = escaped[i];
            break;
        }
        i++;
        j++;
    }
    unescaped[j] = '\0';
}
