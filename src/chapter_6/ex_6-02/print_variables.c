/**
 * Exercise 6-2
 * Write  a  program  that  reads  a  C  program  and  prints  in  alphabetical  order  each  group  of  variable  names
 * that  are  identical  in  the  first  6  characters,  but  different  somewhere  thereafter.
 * Don't  count  words  within  strings  and  comments.
 * Make  6  a  parameter  that  can  be  set from the command line.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100                                /* maximum size of a word */
#define NKEYS (sizeof keytab / sizeof(struct key)) /* number of keywords */
#define DEFAULT_NUM 6;

struct key
{
    char *word;
    int count;
};

struct tree_node /* the tree node: */
{
    char *word;              /* points to the text */
    int count;               /* number of occurrences */
    struct tree_node *left;  /* left child */
    struct tree_node *right; /* right child */
};

/* functions */
int get_word(char *, int);
struct key *bin_search(char *word, struct key tab[], int n);
struct tree_node *add_tree_node(struct tree_node *parent, char *word, int num, int *curr_word_matches);
struct tree_node *tree_node_alloc(void);
void update_tree_node_if_match(struct tree_node *parent, char *word, int num, int *curr_word_matches);
void print_words_with_lines(struct tree_node *root);
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

/* word frequency count */
int main(int argc, char *argv[])
{
    int num = (argc > 1) ? atoi(argv[1]) : DEFAULT_NUM;
    int curr_word_matches = 0;
    struct tree_node *root = NULL;
    char word[MAXWORD];

    while (get_word(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]) && strlen(word) >= num && !bin_search(word, keytab, NKEYS))
            root = add_tree_node(root, word, num, &curr_word_matches);
        curr_word_matches = 0;
    }

    print_words_with_lines(root);
    return 0;
}

/* bin_search: find word in tab[0]...tab[n-1] */
struct key *bin_search(char *word, struct key tab[], int n)
{
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;

    while (low < high)
    {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return NULL;
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

/* add_tree_node: update frequency count for word
   if word exists in tree -> increment its count by 1
   if not -> add node in binary tree in lexicographical order with count of 1 */
struct tree_node *add_tree_node(struct tree_node *parent, char *word, int num, int *curr_word_matches)
{
    if (parent == NULL)
    {
        parent = tree_node_alloc();
        parent->word = strdup(word);
        parent->count = *curr_word_matches;
        parent->left = parent->right = NULL;
        return parent;
    }
    else if (strcmp(word, parent->word) < 0)
    {
        update_tree_node_if_match(parent, word, num, curr_word_matches);
        parent->left = add_tree_node(parent->left, word, num, curr_word_matches);
    }
    else if (strcmp(word, parent->word) > 0)
    {
        update_tree_node_if_match(parent, word, num, curr_word_matches);
        parent->right = add_tree_node(parent->right, word, num, curr_word_matches);
    }
    return parent;
}

/* tree_node_alloc: allocate memory for a tree node */
struct tree_node *tree_node_alloc(void)
{
    return (struct tree_node *)malloc(sizeof(struct tree_node));
}

/* update_tree_node_if_match: update tree node if word matches */
void update_tree_node_if_match(struct tree_node *parent, char *word, int num, int *curr_word_matches)
{
    for (int i = 0; i < num; i++)
    {
        if (parent->word[i] != word[i])
            return;
    }
    parent->count = *curr_word_matches = 1;
}

void print_words_with_lines(struct tree_node *parent)
{
    if (parent == NULL)
        return;

    print_words_with_lines(parent->left);
    if (parent->count > 0)
        printf("%s\n", parent->word);
    print_words_with_lines(parent->right);
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