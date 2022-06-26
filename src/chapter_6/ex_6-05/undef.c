#include "undef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 101

unsigned hash(char *s);

struct table_entry *hash_table[HASH_SIZE];

struct table_entry *lookup(char *name)
{
    unsigned hash_value = hash(name);
    struct table_entry *entry;

    for (entry = hash_table[hash_value]; entry != NULL; entry = entry->next)
    {
        if (strcmp(entry->name, name) == 0)
            return entry;
    }
    return NULL;
}

struct table_entry *install(char *name, char *def)
{
    unsigned hash_value = hash(name);
    struct table_entry *entry = lookup(name);

    if (entry != NULL) // already installed
        return entry;

    entry = (struct table_entry *)malloc(sizeof(struct table_entry));
    entry->name = name;
    entry->definition = def;
    entry->next = hash_table[hash_value];
    hash_table[hash_value] = entry;
    return entry;
}

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval; /* 31 = prime and it's 1 less than 32 (power of 2) -> easy calculation (shift and subtract) */

    return hashval % HASH_SIZE;
}

void undef(char *name)
{
    unsigned hash_value = hash(name);
    struct table_entry *entry = hash_table[hash_value];
    struct table_entry *prev = NULL;
    while (entry != NULL)
    {
        if (strcmp(entry->name, name) == 0)
        {
            if (prev == NULL)
            {
                hash_table[hash_value] = entry->next;
            }
            else
            {
                prev->next = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}