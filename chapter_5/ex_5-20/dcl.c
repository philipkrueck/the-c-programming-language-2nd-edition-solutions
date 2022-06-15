/**
 * Exercise 5-20
 * Expand  dcl  to  handle  declarations  with  function  argument  types,  qualifiers  like const, and so on.
 */

/* grammar:
 *
 * declaration ::= dcl-specifier-list dcl
 *
 * dcl-specifier-list ::= dcl-specifier?
 *                    | dcl-specifier-list dcl-specifier
 *
 * dcl-specifier ::= type-qualifier? | type-specifier?
 *
 * dcl ::= pointer? dirdcl
 *
 * dirdcl ::= identifier
 *        |   (dcl)
 *        |   dirdcl [const-expr?]
 *        |   dirdcl (function-argument-list)
 *
 * function-argument-list ::= dcl-specifier dcl?, function-argument-list?
 *
 * pointer ::= * type-qualifier-list?
 *         |   * type-qualifier-list? pointer
 *
 * type-qualifier-list ::= type-qualifier?
 *                     |   type-qualifier-list type-qualifier
 *
 * type-qualifier ::= const | volatile
 *
 * type-specifier ::= void | int | char | float | double
 *
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
void dclspeclist(char *);
int typequalifier();
int typespecifier();
void functionargumentlist();

/* global variables */
char token[MAXTOKEN]; /* last token of input */
int tokentype;        /* type of last token */

char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];           /* output string */
char state;               /* tells if dcl is valid */
int allowTypeSpecNoNames; /* allow type specifier without name */

/* convert declarations to words */
int main()
{
    while (gettoken() != EOF)
    { /* 1st token on line */

        datatype[0] = '\0'; /* reset string */
        dclspeclist(datatype);

        out[0] = name[0] = '\0'; /* reset string */
        dcl();                   /* parse rest of line */
        if (tokentype != '\n')
            printf("syntax error\n");
        else if (state == VALID)
            printf("%s: %s %s\n", name, out, datatype);
    }

    return 0;
}

void dclspeclist(char *datatype)
{
    while (tokentype == NAME && (typequalifier() || typespecifier()))
    {
        if (strlen(datatype) > 0)
            strcat(datatype, " ");
        strcat(datatype, token);
        gettoken();
    }
    state = INVALID; /* pushback token */
}

/* returns 1 if token is a type qualifier, 0 otherwise */
int typequalifier()
{
    return strcmp(token, "const") == 0 ||
           strcmp(token, "volatile") == 0;
}

/* returns 1 if token is a type specifier, 0 otherwise */
int typespecifier()
{
    return strcmp(token, "void") == 0 ||
           strcmp(token, "int") == 0 ||
           strcmp(token, "char") == 0 ||
           strcmp(token, "float") == 0 ||
           strcmp(token, "double") == 0;
}

void functionargumentlist()
{
    char currArg[MAXTOKEN];

    do
    {
        currArg[0] = '\0'; /* reset string */
        gettoken();
        dclspeclist(currArg);

        allowTypeSpecNoNames = 1;
        dcl();
        allowTypeSpecNoNames = 0;

        strcat(out, " ");
        strcat(out, currArg);
        if (tokentype == ',')
            strcat(out, ",");

    } while (tokentype == ',');

    if (tokentype != ')')
        printf("syntax error: missing ) in parameter declaration\n");
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
    {
        if (*name == '\0')
            strcpy(name, token);
    }
    else
    {
        if (allowTypeSpecNoNames)
            state = INVALID; /* pushback token */
        else
            printf("error: expected name or (dcl)\n");
    }

    int type;
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(')
        {
            strcat(out, " function expecting");
            functionargumentlist();
            strcat(out, " returning");
        }
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
