/**
 * Exercise 5-02
 * Write  getfloat,  the  floating-point  analog  of  getint.
 * What  type  does  getfloat return as its function value?
 * */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define BUFSIZE 100

/* functions */
int getch(void);
void ungetch(int);
int getfloat(float *);

/* global */
int buf[BUFSIZE]; /* buffer from ungetch (can handle EOF push back) */
int bufp = 0;     /* next free position in buf */

int main()
{
    int input;
    float num;

    while ((input = getfloat(&num)) && input != EOF)
        printf("%g\n", num);
    return 0;
}

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getint: get next integer from input into *pn and return end of file status */
int getfloat(float *pf)
{
    int c, sign;
    double i;

    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != '+' && c != '-')
    {
        ungetch(c); /* it is not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        if (!isdigit(c = getch()))
            return 0;
    for (*pf = 0; isdigit(c); c = getch())
        *pf = 10 * *pf + (c - '0');
    if (c == '.')
        for (i = 10.0F; isdigit(c = getch()); i = i * 10.0F)
            *pf += (c - '0') / i;
    *pf *= sign;
    ungetch(c);
    return c;
}
