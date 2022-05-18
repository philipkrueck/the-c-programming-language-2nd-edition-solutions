/**
 * Exercise 4-6
 * Add commands for handling variables. (It's easy to provide twenty-six variables
 * with single-letter names.) Add a variable for the most recently printed value.
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
int isValidVariableName(char variableName);

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
        case '%':
            op2 = pop();
            if (op2 == 0)
                printf("error: zero divisor\n");
            else
                push(fmod(pop(), op2));
            break;
        case '=':
            pop(); /* remove variable value from stack as it will be stored */
            if (isValidVariableName(currentVariable))
                variables[currentVariable - 'a'] = pop();
            else
                printf("error: can only assign a variable to a valid name ('a' - 'z'");
            break;
        case '\n':
            printf("result: %.8g\n", pop());
            break;
        default:
            if (isValidVariableName(type))
                push(variables[type - 'a']);
            else
                printf("error: unknown command %s\n", s);
            break;
        }
        currentVariable = type;
    }

    return 0;
}

/* checks if variable name is valid */
int isValidVariableName(char variableName)
{
    return (variableName >= 'a' && variableName <= 'z');
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

    if (!isdigit(c) && c != '.')
    {
        s[1] = '\0';
        return c; /* not a number */
    }

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