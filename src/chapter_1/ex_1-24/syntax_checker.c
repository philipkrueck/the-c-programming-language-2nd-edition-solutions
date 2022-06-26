/**
 * Exercise: 1-24
 * Write a program to check a C program for rudimentary syntax errors like unmatched parentheses, brackets and braces.
 * Don't forget about quotes, both single and double, escape sequences, and comments.
 * (This program is hard if you do it in full generality.)
 */
#include <stdio.h>

#define IN 1
#define OUT 0

/* global variables */
int numLeftParens = 0;
int numRightParens = 0;
int numLeftCurlyBraces = 0;
int numRightCurlyBraces = 0;
int numLeftBrackets = 0;
int numRightBrackets = 0;
int everythingIsFine = 1;

/* functions */
void countSymbols();
void checkSymbolBalance();
char endCharacterOfComment(char character);
char endCharacterOfQuote(char quoteType);

int main()
{
    extern int everythingIsFine;

    countSymbols();
    checkSymbolBalance();

    if (everythingIsFine)
        printf("Everything is fine. You have no syntax errors.\n");
    else
        printf("You have some syntax errors. Check above.\n");
}

void countSymbols()
{
    extern int numLeftParens, numRightParens, numLeftCurlyBraces,
        numRightCurlyBraces, numLeftBrackets, numRightBrackets;

    char character;

    while ((character = getchar()) != EOF)
    {
        if (character == '(')
            numLeftParens++;
        else if (character == ')')
            numRightParens++;
        if (character == '{')
            numLeftCurlyBraces++;
        else if (character == '}')
            numRightCurlyBraces++;
        if (character == '[')
            numLeftBrackets++;
        else if (character == ']')
            numRightBrackets++;
        else if (character == '/' && (character = getchar()) == '*')
            character = endCharacterOfComment(character);
        else if (character == '\'' || character == '"')
            character = endCharacterOfQuote(character);
    }
}

void checkSymbolBalance()
{
    extern int numLeftParens, numRightParens, numLeftCurlyBraces,
        numRightCurlyBraces, numLeftBrackets, numRightBrackets, everythingIsFine;

    if (numLeftParens - numRightParens > 0)
    {
        printf("You are missing at least one `)`.\n");
        everythingIsFine = 0;
    }
    else if (numLeftParens - numRightParens < 0)
    {
        printf("You are missing at least one `(`.\n");
        everythingIsFine = 0;
    }
    if (numLeftCurlyBraces - numRightCurlyBraces > 0)
    {
        printf("You are missing at least one `}`.\n");
        everythingIsFine = 0;
    }
    else if (numLeftCurlyBraces - numRightCurlyBraces < 0)
    {
        printf("You are missing at least one `{`.\n");
        everythingIsFine = 0;
    }
    if (numLeftBrackets - numRightBrackets > 0)
    {
        printf("You are missing at least one `]`.\n");
        everythingIsFine = 0;
    }
    else if (numLeftBrackets - numRightBrackets < 0)
    {
        printf("You are missing at least one `[`.\n");
        everythingIsFine = 0;
    }
}

char endCharacterOfComment(char character)
{
    int comment = IN;

    while (comment && (character = getchar()) != EOF)
    {
        if (character == '*' && (character = getchar()) == '/')
            comment = OUT;
    }

    return character;
}

char endCharacterOfQuote(char quoteType)
{
    char character;
    int quote = IN;

    while (quote && (character = getchar()) != EOF)
    {
        if (character == '\\')
            character = getchar(); // skip character after escaped character
        else if (character == quoteType)
            quote = OUT;
    }

    return character;
}

/*
 * NOTE: This program is not done in full generality.
 * For example this program will find a mismatching bracket count, but would not detect bracket order errors:
 * e.g `}{` would be valid
 */