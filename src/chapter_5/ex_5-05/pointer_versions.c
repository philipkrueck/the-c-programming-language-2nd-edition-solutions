/**
 * Exercise 5-05
 * Write versions of the library functions `strncpy`, `strncat`, and `strncmp`,
 * which operate on at most the first n characters of their argument strings.
 * For example, `strncpy(s,t,n)` copies at most n characters of t to s. Full descriptions are in Appendix B.  */

#include <stdio.h>
#include <string.h>

/* functions */
void strcpyn(char *s, char *t, int n);
void strcatn(char *s, char *t, int n);
int strcmpn(char *s, char *t, int n);

int main()
{
    char t[128] = "hello world";
    char s[128] = "             ";
    strcpyn(s, t, 6);
    printf("s = '%s' after copying\n", s);

    char u[128] = "world";
    strcatn(s, u, 2);
    printf("adding 2 chars to s; s = '%s'\n", s);

    printf("the first 7 chars '%s', and '%s' are equal: %d\n", t, s, strcmpn(t, s, 7));

    return 0;
}

void strcpyn(char *s, char *t, int n)
{
    int i = 0;
    while ((i++ < n) && (*s++ = *t++))
        ;
    *s = '\0';
}

void strcatn(char *s, char *t, int n)
{
    while (*s) /* find end of s */
        s++;

    int i = 0;
    while ((i++ < n) && (*s++ = *t++)) /* copy t to end of s */
        ;
    *s = '\0';
}

int strcmpn(char *s, char *t, int n)
{
    int i = 0;
    for (; (i < n) && (*s == *t); s++, t++, i++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}