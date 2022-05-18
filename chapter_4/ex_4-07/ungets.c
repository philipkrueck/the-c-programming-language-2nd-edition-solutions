/**
 * Exercise 4-7
 * Write a routine ungets(s) that will push back an entire string onto the input.
 * Should ungets know about buf and bufp, or should it just use ungetch?
 */
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100 /* buffer for ungetch */

/* functions */
int getch(void);
void ungetch(int c);
void ungets(char s[]);

/* external variables */
char buf[BUFSIZE];   /* buffer for ungetch */
int bufPosition = 0; /* next free position in buf */

/* reverse Polish calculator */
int main()
{
    ungets("this string will be back on the input buffer\n");

    while (bufPosition > 0)
        putchar(getch());

    return 0;
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

void ungets(char s[]) /* put entire string back onto the input buffer */
{
    int len = strlen(s);

    while (len > 0)
        ungetch(s[--len]);
}