/**
 * Exercise 6-1
 * Our version of getword does not properly handle underscores, string constants, comments, or preprocessor control lines.
 * Write a better version.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100                                /* maximum size of a word */
#define NKEYS (sizeof keytab / sizeof(struct key)) /* number of keywords */

struct key
{
    char *word;
    int count;
};

/* functions */
int get_word(char *, int);
int bin_search(char *word, struct key tab[], int n);
void skip_blanks();
void skip_comments();
void skip_char_constant();
void skip_string_constant();

/* global variables */

struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"size_t", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0},
};

int main()
{
    char word[MAXWORD];
    int n;

    while (get_word(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = bin_search(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;

    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/* bin_search: find word in tab[0]...tab[n-1] */
int bin_search(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* get_word: get next word or character from input */
int get_word(char *word, int lim)
{
    skip_blanks();
    skip_comments();
    skip_char_constant();
    skip_string_constant();

    int c = getchar();
    char *w = word;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getchar()) && *w != '_')
        {
            ungetc(*w, stdin);
            break;
        }
    *w = '\0';
    return word[0];
}

void skip_blanks()
{
    int c;
    while (isspace(c = getchar()))
        ;
    if (c != EOF)
        ungetc(c, stdin);
}

void skip_comments()
{
    int c = getchar();
    if (c == '/')
    {
        c = getchar();
        if (c == '/')
        {
            while (getchar() != '\n')
                ;
            skip_comments();
        }
        else if (c == '*')
        {
            while ((c = getchar()) != '*' && c != EOF)
                ;
            c = getchar(); // must be '/', otherwise syntax is invalid
            if (c == '/')
                skip_comments();
        }
        else
            ungetc(c, stdin);
    }
    else
        ungetc(c, stdin);
}

void skip_char_constant()
{
    int c = getchar();
    if (c == '\'')
    {
        while ((c = getchar()) != '\'' && c != EOF)
            ;
        ungetc(c, stdin);
    }
    else
        ungetc(c, stdin);
}

void skip_string_constant()
{
    int c = getchar();
    if (c == '"')
    {
        while ((c = getchar()) != '"' && c != EOF)
            ;
        ungetc(c, stdin);
    }
    else
        ungetc(c, stdin);
}