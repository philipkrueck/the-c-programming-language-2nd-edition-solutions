#include <stdio.h>
#include "calc.h"

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