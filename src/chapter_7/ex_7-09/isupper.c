/**
 * Exercise 7-9
 * Functions like isupper can be implemented to save space or to save time.
 * Explore both possibilities.
 */

#include <stdio.h>

/* saves time by removing call to function, but uses more space for macro */
#define is_upper_v1(c) ((c) >= 'A' && (c) <= 'Z')

int is_upper_v2(int c);

int is_upper_v2(int c)
{
    return (c >= 'A' && c <= 'Z');
}

int main()
{
    char c = 'A';
    printf("%c is upper: %d\n", c, is_upper_v1(c));
    printf("%c is upper: %d\n", c, is_upper_v2(c));
    return 0;
}