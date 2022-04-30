/**
 * Exercise: 1-23
 * Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly. C comments don't nest.
 */
#include <stdio.h>

#define IN 1
#define OUT 0

int isQuotationMark(char character);

int main()
{
    char prevCharacter;
    char currCharacter;
    int comment, quote = OUT;

    prevCharacter = getchar();

    while ((currCharacter = getchar()) != EOF)
    {
        if (isQuotationMark(currCharacter))
        {
            if (quote == IN)
                quote = OUT;
            else if (quote == OUT && comment == OUT)
                quote = IN;
        }

        if (quote == OUT && prevCharacter == '/' && currCharacter == '*')
            comment = IN;

        if (comment == OUT)
            putchar(prevCharacter);

        if (comment == IN && prevCharacter == '*' && currCharacter == '/')
        {
            comment = OUT;
            currCharacter = getchar(); // skip the '/' character to be printed
        }

        prevCharacter = currCharacter;
    }
    putchar(prevCharacter); // print final character
}

/* returns 1 if character is a quotation mark and 0 if not*/
int isQuotationMark(char character)
{
    return character == '\"';
}

/*
 * NOTE: this program only considers comments with this commment form.
 */