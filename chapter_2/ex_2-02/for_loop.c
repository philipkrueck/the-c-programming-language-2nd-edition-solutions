/**
 * Exercise 2-2
 * Write a loop equivalent to the for loop above without using `&&` or `||`.
 */

#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX_LINE_LENGTH 1000;

int main()
{
    int isValid = TRUE;
    int lim = MAX_LINE_LENGTH;
    int i = 0;

    char s[lim];
    char c;

    while (isValid)
    {
        c = getchar();
        if (i >= (lim - 1))
        {
            isValid = FALSE;
        }
        else if (c == '\n')
        {
            isValid = FALSE;
        }
        else if (c == EOF)
        {
            isValid = FALSE;
        }
        else
        {
            s[i] = c;
            i++;
        }
    }

    s[i] = '\0';
    printf("string: %s\n", s);

    return 0
}

/*
 * NOTE: Reference for loop in the book:
 *
 * for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 *      s[i] = c;
 */