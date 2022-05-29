/**
 * Exercise 5-04
 * Write  the  function  strend(s,t),
 * which  returns  1  if  the  string  t  occurs  at  the  end of the string s, and zero otherwise.
 * */

#include <stdio.h>
#include <string.h>

/* functions */
int strend(char *, char *);

int main()
{
    char s[128] = "hello world";
    char t[] = "world";
    printf("'%s' is at end of '%s': %d\n", t, s, strend(s, t));

    char w[] = "world wide web";
    printf("'%s' is at end of '%s': %d\n", w, s, strend(s, w));

    char u[] = "worl";
    printf("'%s' is at end of '%s': %d\n", u, s, strend(s, u));

    char v[] = "d";
    printf("'%s' is at end of '%s': %d\n", v, s, strend(s, v));

    return 0;
}

int strend(char *s, char *t)
{
    int diff = strlen(s) - strlen(t);

    s += diff; /* advance s to point to relevant end part of string */

    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 1;
    return 0;
}