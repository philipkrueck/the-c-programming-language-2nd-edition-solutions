/**
 * Exercise 4-11
 * Modify getop so that it doesn't need to use ungetch.
 * Hint: use an internal static variable.
 */
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main()
{
    int type; /* either an OPERAND or an operator: +, - , *, /, % */
    double op2;
    int currentVariable = '0';
    double variables[26]; /* variable names from 'a' - 'z' */
    char s[MAX_STACK_DEPTH];

    while ((type = getNextOp(s)) != EOF)
    {
        switch (type)
        {
        case OPERAND:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 == 0)
                printf("error: zero divisor\n");
            else
                push(pop() / op2);
            break;
        case '\n':
            printf("result: %.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}