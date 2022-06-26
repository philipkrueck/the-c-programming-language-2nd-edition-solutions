#define OPERAND '0'
#define MAX_STACK_DEPTH 100 /* max size of operands and operators on the stack */

/* functions */
void push(double);
double pop();
int getNextOp(char[]);
