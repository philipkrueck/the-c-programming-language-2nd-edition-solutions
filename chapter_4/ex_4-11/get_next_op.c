#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getNextOp: get next character or numeric operand */
int getNextOp(char s[])
{
    int i, c;

    static int lastChar = 0;

    if (lastChar == 0)
        c = getchar();
    else
    {
        c = lastChar;
        lastChar = 0;
    }

    while ((s[0] = c) == ' ' || c == '\t')
        c = getchar();

    if (!isdigit(c) && c != '.')
    {
        s[1] = '\0';
        return c; /* not a number */
    }

    i = 0;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getchar()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getchar()))
            ;

    s[i] = '\0';

    if (c != EOF)
        lastChar = c;
    return OPERAND;
}