/**
 * Exercise 4-9
 * Our getch and ungetch do not handle a pushed-back EOF correctly.
 * Decide what their properties ought to be if an EOF is pushed back, then implement your design.
 */
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100 /* buffer for ungetch */

/* functions */
int getch(void);
void ungetch(int c);

/* external variables */
int buf[BUFSIZE];    /* buffer for ungetch */
int bufPosition = 0; /* next free position in buf */

/* reverse Polish calculator */
int main()
{

    ungetch('1');
    printf("%c\n", getch());

    ungetch(EOF); /* program should exit here */

    printf("this line should not be executed");

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
    else if (c == EOF)
    {
        printf("EOF can't be stored as character\n");
        exit(EXIT_FAILURE);
    }
    else
        buf[bufPosition++] = c;
}

/*
 * NOTE:
 * Converting EOF (-1) to an int and back to a char may lead to conversion errors, as char is not signed for all compiler versions.
 * Therefore, we represent characters using int.
 */