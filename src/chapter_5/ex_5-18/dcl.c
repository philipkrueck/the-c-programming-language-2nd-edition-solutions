/**
 * Exercise 5-18
 * Make dcl recover from input errors.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100 /* max length of any given token */

enum
{
    NAME,
    PARENS,
    BRACKETS
};

enum
{
    VALID,
    INVALID
};

/* functions */
void dcl(void);
void dirdcl(void);
int gettoken(void);

/* global variables */
char token[MAXTOKEN]; /* last token of input */
int tokentype;        /* type of last token */

char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];          /* output string */
char state;              /* tells if dcl is valid */

/* convert declarations to words */
int main()
{
    while (gettoken() != EOF)
    {                            /* 1st token on line */
        strcpy(datatype, token); /* is the datatype */
        out[0] = '\0';           // todo: why do i need to do this?
        dcl();                   /* parse rest of line */
        if (tokentype != '\n')
            printf("syntax error\n");
        else if (state == VALID)
            printf("%s: %s %s\n", name, out, datatype);
    }

    return 0;
}

/* parse declarator according to grammar */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';) /* count *'s */
        ns++;

    dirdcl(); /* after *'s comes a direct declarator -> parse it */

    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* parse direct declaration according to grammar */
void dirdcl(void)
{
    if (tokentype == '(')
    {
        dcl(); /* after single opening bracket follows a declarator -> parse it */
        if (tokentype != ')')
        {
            state = INVALID;
            printf("error: missing )\n");
        }
    }
    else if (tokentype == NAME) /* variable name */
        strcpy(name, token);
    else
    {
        state = INVALID;
        printf("error: expected name or (dcl)\n");
    }

    int type;
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

/* skip blanks and tabs, then finds next token in input
 * `token` is a name, pair of parens, pair of brackets incl. number or another single char
 */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (state == INVALID)
    {
        state = VALID;
        return tokentype; /* use previous token error hadn't existed */
    }

    while ((c = getch()) == ' ' || c == '\t') /* skip blanks and tabs */
        ;

    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

/* getch / ungetch */
#define BUFSIZE 100  /* buffer for ungetch */
char buf[BUFSIZE];   /* buffer for ungetch */
int bufPosition = 0; /* next free position in buf */

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
