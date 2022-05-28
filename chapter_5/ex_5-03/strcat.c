/**
 * Exercise 5-03
 * Write  a  pointer  version  of  the  function  strcat  that  we  showed  in  Chapter  2:
 * strcat(s,t) copies the string t to the end of s.
 * */

#include <stdio.h>

/* functions */
void strcopy(char *, char *);

int main()
{
    char s[128] = "hello ";
    char t[] = "world";
    strcopy(s, t);
    printf("%s\n", s);
    return 0;
}

void strcopy(char *s, char *t)
{
    while (*s) /* find end of s */
        s++;

    while (*s++ = *t++) /* copy t to end of s */
        ;
}