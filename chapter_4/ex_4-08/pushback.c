/**
 * Exercise 4-8
 * Suppose that there will never be more than one character of pushback.
 * Modify getch and ungetch accordingly
 */
#include <stdio.h>

/* functions */
int getch(void);
void ungetch(int c);

/* external variables */
char buf = -1;

/* reverse Polish calculator */
int main()
{
    ungetch('1');
    ungetch('2'); /* should trigger error*/
    printf("%c\n", getch());

    ungetch('3'); /* should trigger error*/
    ungetch('4');
    printf("%c\n", getch());

    return 0;
}

int getch(void) /* get a (possibly pushed-back) character */
{
    char c;

    if (buf != -1)
    {
        c = buf;
        buf = -1;
    }
    else
        c = getchar();

    return c;
}

void ungetch(int c) /* push character back on input */
{
    if (buf != -1)
        printf("ungetch: too many characters\n");
    else
        buf = c;
}