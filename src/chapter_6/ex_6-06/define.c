/**
 * Chapter: 6
 * Exercise: 6-06 - Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs,
 * based on the routines of this section. You may also find getch and ungetch helpful.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 101
#define MAXWORD 100
#define BUFSIZE 1000

struct table_entry
{
    struct table_entry *next;
    char *name;
    char *definition;
};

struct table_entry *hash_table[HASH_SIZE];

int get_word(char *, int);
unsigned hash(char *);
struct table_entry *lookup(char *s);
struct table_entry *install(char *, char *);
void print_table(void);

int main()
{
    char word[MAXWORD];
    char defn[MAXWORD];
    const char *KEYWORK = "#define";

    while ((get_word(word, MAXWORD)) != EOF)
        if (word[0] == '#' && (strcmp(word, KEYWORK) == 0))
        {
            get_word(word, MAXWORD);
            get_word(defn, MAXWORD);
            install(word, defn);
        }

    printf("hash table values:\n");
    print_table();

    return 0;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASH_SIZE;
}

/* lookup: look for s in hash_table */
struct table_entry *lookup(char *s)
{
    struct table_entry *np;

    for (np = hash_table[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; /* found */

    return NULL; /* not found */
}

/* install: put (name, defn) in hash_table */
struct table_entry *install(char *name, char *def)
{
    unsigned hash_value = hash(name);
    struct table_entry *entry = lookup(name);

    if (entry != NULL) // already installed
        return entry;

    entry = (struct table_entry *)malloc(sizeof(struct table_entry));
    entry->name = strdup(name);
    entry->definition = strdup(def);
    entry->next = hash_table[hash_value];
    hash_table[hash_value] = entry;
    return entry;
}

void print_table(void)
{
    struct table_entry *entry;
    for (int i = 0; i < HASH_SIZE; i++)
        for (entry = hash_table[i]; entry != NULL; entry = entry->next)
            printf("%s: %s\n", entry->name, entry->definition);
}

/* get_word: get next word or character from input */
int get_word(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (isalpha(c) || c == '_' || c == '#')
    {
        for (; --lim > 0; ++w)
            if (!isalnum(*w = getch()) && *w != '_')
            {
                ungetch(*w);
                break;
            }
    }
    else if (c == '\'') /* skip character constants */
        while ((c = getch()) != '\'')
            ;
    else if (c == '\"')
    { /* skip string constants */
        while ((c = getch()) != '\"')
            if (c == '\\')
                getch();
    }
    else if (c == '/' && (c = getch()) == '*') /* skip comments */
        while ((c = getch()) != EOF)
            if (c == '*' && (c = getch()) == '/')
                break;
    *w = '\0';
    return c;
}

#define BUFSIZE 1000

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

/* getch: get a character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}