/**
 * Exercise 2-5
 * Write the function any(s1,s2), which returns the first location in a string s1 where any character from the string s2 occurs,
 * or -1 if s1 contains no characters from s2.
 * (The standard library function strpbrk does the same job but returns a pointer to the location.)
 */
#include <stdio.h>

#define MAX_CHARS_PER_LINE 1000 /* maximum input line length */

/* functions */
int any(char strOne[], char strTwo[]);

#include <stdio.h>

int main()
{
    char strOne[MAX_CHARS_PER_LINE] = "remove these symbols";
    char strTwo[MAX_CHARS_PER_LINE] = "hello";

    printf("first location in \"%s\" where any character from \"%s\" occurs: %d\n", strOne, strTwo, any(strOne, strTwo));

    return 0;
}

int any(char strOne[], char strTwo[])
{
    for (int i = 0; strOne[i] != '\0'; i++)
    {
        for (int j = 0; strTwo[j] != '\0'; j++)
        {
            if (strOne[i] == strTwo[j])
                return i;
        };
    }

    return -1;
}
