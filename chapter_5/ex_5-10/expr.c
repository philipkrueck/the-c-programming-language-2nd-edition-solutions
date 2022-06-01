/**
 * Exercise 5-10
 * Write the program expr, which evaluates a reverse Polish expression from the command line,
 * where each operator or operand is a separate argument. For example,
 * `expr 2 3 4 + *`
 * */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_STACK_DEPTH 100 /* max size of operands and operators on the stack */

/* functions */
int isOperand(char[]);
void push(double);
double pop();

/* external variables */
int stackPointer = 0;
double stack[MAX_STACK_DEPTH];

int main(int argc, char *argv[])
{
    double op2;

    while (--argc > 0)
    {
        ++argv;
        switch (**argv)
        {
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
        default:
            if (isOperand(*argv))
                push(atof(*argv));
            else
            {
                printf("error: unknown command %c\n", **argv);
                argc = 0;
            }
            break;
        }
    }

    printf("result: %.8g\n", pop());
    return 0;
}

int isOperand(char s[])
{
    int len = strlen(s);
    while (len > 0)
    {
        if (!isdigit(*s) && *s != '.')
            return 0;
        s++;
        len--;
    }

    return 1;
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