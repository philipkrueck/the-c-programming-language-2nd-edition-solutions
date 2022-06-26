/**
 * Exercise 5-06
 * Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
 * Good possibilities include getline (Chapters 1 and 4), atoi, itoa, and  their  variants  (Chapters  2, 3,  and  4),
 * reverse (Chapter  3),  and  strindex  and  getop(Chapter 4).
 * */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000
#define OPERAND '0' /* signal that an operand was found */
#define BUFSIZE 100 /* buffer for ungetch */

/* functions */
int getline(char *s, int limit);
int atoi(char *s);
void reverse(char *s);
void itoa(int n, char *s);
int strindex(char s[], char t[]);
int getop(char s[]);
int getch(void);
void ungetch(int c);

/* external variables */
char line[MAX_LINE_LENGTH];
char buf[BUFSIZE];   /* buffer for ungetch */
int bufPosition = 0; /* next free position in buf */

int main()
{
    /* test atoi */
    char s[] = "2385";
    printf("the string '%s' converts to the number '%d'\n\n", s, atoi(s));

    /* test itoa */
    int n = -2385;
    char t[128];
    itoa(n, t);
    printf("the number '%d' converts to the string '%s'\n", n, t);

    /* test reverse */
    char greeting[] = "hello";
    reverse(greeting);
    printf("the reverse of 'hello' is '%s'\n\n", greeting);

    /* test strindex */
    char greetingTwo[] = "Hello, how are you? Do you like C?";
    char name[] = "you";
    int strindex = strindex(greetingTwo, name);
    printf("The position of the rightmost occurrence of \"%s\" in \"%s\" is pos %d\n\n", name, greetingTwo, strindex);

    /* test getop */
    char operator[128];
    if (getop(operator) == OPERAND)
        printf("An operand was found: '%s'\n\n", operator);
    else
        printf("Something else was found\n\n");

    /* test getline */
    int lineLength = getline(line, MAX_LINE_LENGTH);
    printf("the line '%s' is %d characters long \n\n", line, lineLength);

    return 0;
}

int getline(char *s, int limit)
{
    int n = 0;
    char c;

    for (; (n < limit) && ((c = getchar()) != EOF) && (c != '\n'); n++, s++)
        *s = c;
    *s = '\0';
    return n;
}

int atoi(char *s)
{
    int n = 0;

    for (; *s <= '9' && *s >= '0'; s++)
        n = 10 * n + (*s - '0');
    return n;
}

void itoa(int n, char *s)
{
    int sign;
    char *startPointer;
    startPointer = s;

    if ((sign = n) < 0)
        n = -n;

    do
    {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        *s++ = '-';

    *s = '\0';
    reverse(startPointer);
}

void reverse(char *s)
{
    char *startPointer, *endPointer, tmp;
    startPointer = s;
    endPointer = s + strlen(s) - 1;

    for (; startPointer < endPointer; startPointer++, endPointer--)
    {
        tmp = *startPointer;
        *startPointer = *endPointer;
        *endPointer = tmp;
    }
}

int strindex(char s[], char t[])
{
    char *strIdx, *sPointer, *tPointer;
    strIdx = s + (strlen(s) - strlen(t));

    for (; strIdx > s; strIdx--)
    {
        for (sPointer = strIdx, tPointer = t; *tPointer != '\0' && *sPointer == *tPointer; sPointer++, tPointer++)
            ;
        if (*tPointer == '\0' && tPointer > t)
            return strIdx - s;
    }

    return -1;
}

int getop(char s[])
{
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t')
        ;

    *++s = '\0';
    if (!isdigit(c) && c != '.')
        return c; /* not a number */

    if (isdigit(c))
        while (isdigit(*++s = c = getch()))
            ;

    if (c == '.')
        while (isdigit(*++s = c = getch()))
            ;

    *s = '\0';

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