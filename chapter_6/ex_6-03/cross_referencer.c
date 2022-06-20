/**
 * Exercise 6-3
 * Write  a  cross-referencer  that  prints  a  list  of  all  words  in  a  document,
 * and  for  each  word,  a  list  of  the  line  numbers  on  which  it  occurs.
 * Remove  noise  words  like  `the  `and`, `the` and so on.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100                                     /* maximum size of a word */
#define NKEYS (sizeof noise_words / sizeof(struct key)) /* number of keywords */
#define DEFAULT_NUM 6;

struct key
{
    char *word;
    int count;
};

struct tree_node /* the tree node: */
{
    char *word;              /* points to the text */
    struct lines *lines;     /* points to the list of line numbers */
    struct tree_node *left;  /* left child */
    struct tree_node *right; /* right child */
};

struct lines /* the list of line numbers: */
{
    int line_number;
    struct lines *next;
};

/* functions */
int get_word(char *, int);
struct key *bin_search(char *word, struct key tab[], int n);
struct tree_node *tree_node_alloc(void);
struct tree_node *add_tree_node(struct tree_node *parent, char *word, int line_number);
struct lines *add_lines(struct lines *lines_list, int line_number);
void print_words_with_lines(struct tree_node *root);
void print_word_with_lines(char *word, struct lines *lines_list);
void skip_blanks();
void skip_comments();
void skip_char_constant();
void skip_string_constant();

/* global variables */

struct key noise_words[] = {
    {"and", 0},
    {"the", 0},
    {"of", 0},
    {"in", 0},
    {"is", 0},
    {"to", 0},
    {"for", 0},
    {"by", 0},
    {"on", 0},
    {"that", 0},
    {"it", 0},
    {"this", 0},
    {"with", 0},
    {"not", 0},
    {"or", 0},
    {"from", 0},
    {"as", 0},
    {"was", 0},
    {"but", 0},
    {"are", 0},
    {"be", 0},
    {"if", 0},
};

/* word frequency count */
int main(int argc, char *argv[])
{
    struct tree_node *root = NULL;
    char word[MAXWORD];
    int line_number = 1;

    while (get_word(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]) && !bin_search(word, noise_words, NKEYS))
            root = add_tree_node(root, word, line_number);
        else if (word[0] == '\n')
            line_number++;
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
    char c;
    char *w = word;

    while (isblank(c = getchar()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; ++w)
        if (!isalnum(*w = getchar()))
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
struct tree_node *add_tree_node(struct tree_node *parent, char *word, int line_number)
{
    if (parent == NULL)
    {
        parent = tree_node_alloc();
        parent->word = strdup(word);
        parent->lines = add_lines(NULL, line_number);
        parent->left = parent->right = NULL;
        return parent;
    }
    else if (strcmp(word, parent->word) < 0)
        parent->left = add_tree_node(parent->left, word, line_number);
    else if (strcmp(word, parent->word) > 0)
        parent->right = add_tree_node(parent->right, word, line_number);
    else
        parent->lines = add_lines(parent->lines, line_number);
    return parent;
}

struct lines *add_lines(struct lines *lines_list, int line_number)
{
    if (!lines_list)
    {
        lines_list = malloc(sizeof(struct lines));
        lines_list->line_number = line_number;
    }
    else if (lines_list->line_number != line_number)
        lines_list->next = add_lines(lines_list->next, line_number);
    return lines_list;
}

/* tree_node_alloc: allocate memory for a tree node */
struct tree_node *tree_node_alloc(void)
{
    return (struct tree_node *)malloc(sizeof(struct tree_node));
}

void print_words_with_lines(struct tree_node *parent)
{
    if (parent == NULL)
        return;

    print_words_with_lines(parent->left);
    print_word_with_lines(parent->word, parent->lines);
    print_words_with_lines(parent->right);
}

void print_word_with_lines(char *word, struct lines *lines_list)
{
    printf("'%s' :", word);
    while (lines_list != NULL)
    {
        printf(" L%d", lines_list->line_number);
        lines_list = lines_list->next;
    }
    printf("\n");
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