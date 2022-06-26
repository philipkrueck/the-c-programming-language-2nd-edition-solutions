/**
 * Exercise 6-4
 * Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence.
 * Precede each word by its count.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100        /* maximum size of a word */
#define MAX_NUM_NODES 1000 /* maximum number of nodes */

struct tree_node /* the tree node: */
{
    char *word;              /* points to the text */
    int count;               /* number of occurrences */
    struct tree_node *left;  /* left child */
    struct tree_node *right; /* right child */
};

/* functions */
int get_word(char *, int);
struct tree_node *add_tree_node(struct tree_node *parent, char *word);
struct tree_node *tree_node_alloc(void);
void update_tree_node_if_match(struct tree_node *parent, char *word);
void copy_tree_to_array(struct tree_node *root, struct tree_node *array[]);
void sort(struct tree_node *array[], int num_nodes);
void print_frequencies(struct tree_node *array[]);
void skip_blanks();
void skip_comments();
void skip_char_constant();
void skip_string_constant();

/* globals */
int num_nodes = 0;

/* word frequency count */
int main(int argc, char *argv[])
{
    struct tree_node *root = NULL;
    char word[MAXWORD];

    while (get_word(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
            root = add_tree_node(root, word);
    }

    struct tree_node *array[MAX_NUM_NODES];
    copy_tree_to_array(root, array);

    sort(array, num_nodes);

    print_frequencies(array);

    return 0;
}

void sort(struct tree_node *array[], int num_nodes)
{
    int i, j;
    struct tree_node *temp;

    for (i = 0; i < num_nodes - 1; i++)
    {
        for (j = 0; j < num_nodes - i - 1; j++)
        {
            if (array[j]->count < array[j + 1]->count)
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
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
struct tree_node *add_tree_node(struct tree_node *parent, char *word)
{
    if (parent == NULL)
    {
        parent = tree_node_alloc();
        parent->word = strdup(word);
        parent->count = 1;
        parent->left = parent->right = NULL;
        return parent;
    }
    else if (strcmp(word, parent->word) < 0)
        parent->left = add_tree_node(parent->left, word);
    else if (strcmp(word, parent->word) > 0)
        parent->right = add_tree_node(parent->right, word);
    else
        parent->count++;
    return parent;
}

/* tree_node_alloc: allocate memory for a tree node */
struct tree_node *tree_node_alloc(void)
{
    return (struct tree_node *)malloc(sizeof(struct tree_node));
}

void print_frequencies(struct tree_node *array[])
{
    int i;
    for (i = 0; i < num_nodes; i++)
    {
        printf("%d %s\n", array[i]->count, array[i]->word);
    }
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

void copy_tree_to_array(struct tree_node *node, struct tree_node *array[])
{
    if (node == NULL)
        return;
    copy_tree_to_array(node->left, array);
    array[num_nodes++] = node;
    copy_tree_to_array(node->right, array);
}