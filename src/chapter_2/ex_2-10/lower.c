/**
 * Exercise 2-10
 *
 */
#include <stdio.h>

/* functions */
void lower(char s[]);

int main(void)
{
    char greeting[] = "Hello, How Are You?";
    printf("original: %s\n", greeting);

    lower(greeting);
    printf("lower: %s\n", greeting);

    return 0;
}

void lower(char s[])
{
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? (s[i] + 'a' - 'A') : s[i];
}