/**
 * Exercise 6-5
 * Write a function undef that will remove a name and definition from the table maintained by lookup and install.
 */

#ifndef UNDEF_H
#define UNDEF_H

struct table_entry
{
    struct table_entry *next;
    char *name;
    char *definition;
};

struct table_entry *lookup(char *name);
struct table_entry *install(char *name, char *def);
void undef(char *name);

#endif // UNDEF_H
