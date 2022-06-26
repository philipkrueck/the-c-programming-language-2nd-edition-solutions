/**
 * Exercise 4-1
 * Write the function `strindex(s,t)` which returns the position of the rightmost occurrence of `t` in `s`, or -1 if there is none.
 */
#include <stdio.h>
#include <string.h>

/* functions */
int strindex(char s[], char t[]);

int main(void)
{
    char greeting[] = "Hello, how are you? Do you like C?";
    char name[] = "you";

    int strIndex = strindex(greeting, name);

    printf("The position of the rightmost occurrence of \"%s\" in \"%s\" is pos %d\n", name, greeting, strIndex);

    return strIndex;
}

int strindex(char s[], char t[])
{
    int i, j, k;
    for (i = strlen(s) - strlen(t); i > 0; i--)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}