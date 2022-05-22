/**
 * Exercise 4-6
 * Add commands for handling variables. (It's easy to provide twenty-six variables
 * with single-letter names.) Add a variable for the most recently printed value.
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINE_LENGTH 1000
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
int getLine(char line[], int max);

/* external variables */
int stackPointer = 0;
double stack[MAX_STACK_DEPTH];
char buf[BUFSIZE];   /* buffer for ungetch */
int bufPosition = 0; /* next free position in buf */
char line[MAX_LINE_LENGTH];
int currLinePos = 0;

/* reverse Polish calculator */
int main()
{
    int type; /* either an OPERAND or an operator: +, - , *, /, % */
    double op2;
    char s[MAX_STACK_DEPTH];

    while (getLine(line, MAX_LINE_LENGTH) > 0)
    {
        currLinePos = 0;
        while ((type = getNextOp(s)) != '\0')
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
            }
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

    while ((s[0] = c = line[currLinePos++]) == ' ' || c == '\t')
        ;

    if (!isdigit(c) && c != '.')
    {
        s[1] = '\0';
        return c; /* not a number */
    }

    i = 0;

    if (isdigit(c))
        while (isdigit(s[++i] = c = line[currLinePos++]))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = line[currLinePos++]))
            ;

    s[i] = '\0';

    return OPERAND;
}

int getLine(char line[], int maxLength)
{
    char currChar;
    int lineLength;

    for (lineLength = 0; lineLength < maxLength - 1 && (currChar = getchar()) != EOF && currChar != '\n'; ++lineLength)
        line[lineLength] = currChar;

    if (currChar == '\n')
    {
        line[lineLength] = currChar;
        ++lineLength;
    }

    line[lineLength] = '\0';

    return lineLength;
}
