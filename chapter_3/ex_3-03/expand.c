/**
 * Exercise 3-3
 * Write a function expand(s1,s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2.
 * Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z.
 * Arrange that a leading or trailing - is taken literally.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* functions */
void expandAndPrint(char shorthand[]);
void expand(char shorthand[], char expanded[]);
int isValidRange(char startChar, char endChar);

int main(void)
{
    expandAndPrint("a-z");
    expandAndPrint("b-a0-ca-Z"); // not valid
    expandAndPrint("a-b-z");
    expandAndPrint("a-z0-9");
    expandAndPrint("-a-z");
    expandAndPrint("a-c-i-u");
    expandAndPrint("0-9a-zA-Z");
    expandAndPrint("0-9a-zA-Z-");
}

void expandAndPrint(char shorthand[])
{
    char expandedString[100];
    expand(shorthand, expandedString);
    printf("shorthand notation \"%s\" expands to \"%s\"\n", shorthand, expandedString);
}

void expand(char shorthand[], char expanded[])
{
    int j = 0;

    for (int i = 0; shorthand[i] != '\0'; i++)
    {
        if (shorthand[i + 1] == '-' && isValidRange(shorthand[i], shorthand[i + 2]))
        {
            char c = shorthand[i];

            while (c <= shorthand[i + 2])
            {
                expanded[j++] = c;
                c++;
            }
        }
    }

    expanded[j] = '\0';
}

int isValidRange(char startChar, char endChar)
{
    int bothAreDigits = isdigit(startChar) && isdigit(endChar);
    int bothAreLetters = isalpha(startChar) && isalpha(endChar);
    int bothAreUpper = isupper(startChar) && isupper(endChar);
    int bothAreLower = islower(startChar) && islower(endChar);

    return startChar < endChar &&
           (bothAreDigits ||
            (bothAreLetters && (bothAreUpper || bothAreLower)));
}