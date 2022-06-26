/**
 * Exercise 5-18
 * Make dcl recover from input errors.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100 /* max length of any given token */
#define MAXLEN 1000  /* max length of output string */

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
void undcl(void);
int gettoken(void);
int needsParens();

/* global variables */
char token[MAXTOKEN]; /* last token of input */
int tokentype;        /* type of last token */

char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[MAXLEN];        /* output string */
char state;              /* tells if dcl is valid */

/* undcl:  convert word descriptions to declarations */
int main(void)
{
    while (gettoken() != EOF)
    {                          /* first token on line */
        if (tokentype == '\n') /* skip empty input lines */
            continue;
        strcpy(out, token); /* is the name */
        undcl();
        printf("%s\n", out);
    }
    return 0;
}

/* undcl: convert word descriptions to declarations */
void undcl(void)
{
    int type;
    char temp[MAXLEN];

    while ((type = gettoken()) != '\n')
        if (type == PARENS || type == BRACKETS)
            strcat(out, token);
        else if (type == '*')
        {
            sprintf(temp, needsParens() ? "(*%s)" : "*%s", out);
            strcpy(out, temp);
        }
        else if (type == NAME)
        {
            sprintf(temp, "%s %s", token, out);
            strcpy(out, temp);
        }
        else
            printf("invalid input at %s\n", token);
}

int needsParens()
{
    int nextTokenType = gettoken();
    state = INVALID; /* signal token pushback */
    return nextTokenType == PARENS || nextTokenType == BRACKETS;
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
