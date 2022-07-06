#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define OPERAND '0'
#define MAX_STACK_DEPTH 100 /* max size of operands and operators on the stack */

/* functions */
void push(double);
double pop();
int getNextOp(double *);

int main()
{
    int type; /* either an OPERAND or an operator: +, - , *, /, % */
    double op2;
    int currentVariable = '0';
    double variables[26]; /* variable names from 'a' - 'z' */
    char s[MAX_STACK_DEPTH];
    double op;

    while ((type = getNextOp(&op)) != EOF)
    {
        switch (type)
        {
        case OPERAND:
            push(op);
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

/* getNextOp: get next character or numeric operand */
int getNextOp(double *number)
{
    char c;

    if (scanf("%c", &c) < 0)
        return EOF;
    else if (c == '\n')
        return '\n';

    ungetc(c, stdin);

    if (scanf("%lf", number) == 1)
        return OPERAND;
    else /* must be an operator */
    {
        scanf("%c", &c); /* scan op */
        return c;
    }
}

/* external variables */
int stackPointer = 0;
double stack[MAX_STACK_DEPTH];

/* push: push val onto stack */
void push(double val)
{
    if (stackPointer < MAX_STACK_DEPTH)
        stack[stackPointer++] = val;
    else
        printf("error: stack full, can't push %g\n", val);
}

/* pop: pop and return top value from stack */
double pop()
{
    if (stackPointer > 0)
        return stack[--stackPointer];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}
