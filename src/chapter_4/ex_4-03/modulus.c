/**
 * Exercise 4-3
 * Given the basic framework, it's straightforward to extend the calculator.
 * Add the modulus (%) operator and provisions for negative numbers.
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STACK_DEPTH 100 /* max size of operands and operators on the stack */
#define OPERAND '0'         /* signal that an operand was found */
#define BUFSIZE 100         /* buffer for ungetch */

/* functions */
void push(double);
double pop();
int getNextOp(char[]);
int getch(void);
void ungetch(int c);

/* external variables */
int stackPointer = 0;
double stack[MAX_STACK_DEPTH];
char buf[BUFSIZE];   /* buffer for ungetch */
int bufPosition = 0; /* next free position in buf */

/* reverse Polish calculator */
int main()
{
    int type; /* either an OPERAND or an operator: +, - , *, /, % */
    double op2;
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
        case '%':
            op2 = pop();
            if (op2 == 0)
                printf("error: zero divisor\n");
            else
                push(fmod(pop(), op2));
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

/* getNextOp: get next character or numeric operand */
int getNextOp(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* not a number */

    i = 0;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);
    return OPERAND;
}

int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufPosition > 0) ? buf[--bufPosition] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufPosition >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufPosition++] = c;
}