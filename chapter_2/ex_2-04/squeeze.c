/**
 * Exercise 2-4
 * Write an alternative version of squeeze(s1,s2) that deletes each character in s1 that matches any character in the string s2.
 */
#include <stdio.h>

#define MAX_CHARS_PER_LINE 1000 /* maximum input line length */

/* functions */
void squeeze(char strOne[], char strTwo[]);

#include <stdio.h>

int main()
{
    char strOne[MAX_CHARS_PER_LINE] = "remove these &^*-+symbols";
    char strTwo[MAX_CHARS_PER_LINE] = "&^*-+";

    squeeze(strOne, strTwo);
    printf("\"%s\"\n", strOne);

    return 0;
}

void squeeze(char strOne[], char strTwo[])
{
    int k = 0;
    for (int i = 0; strOne[i] != '\0'; i++)
    {
        int j;
        for (j = 0; strTwo[j] != '\0' && strOne[i] != strTwo[j]; j++)
            ;

        if (strTwo[j] == '\0') // found no character of `strTwo` matching curr character at position `i` in `strOne`
            strOne[k++] = strOne[i];
    }

    strOne[k] = '\0';
}
