/**
 * Exercise 4-12
 * Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an integer into a string by calling a recursive routine.
 * */
#include <stdio.h>

/* functions */
void convertAndPrint(int n);
void itoa(int n, char s[]);

int main()
{
    convertAndPrint(9);
    convertAndPrint(11993);
    // convertAndPrint(INT_MAX);
    // convertAndPrint(INT_MIN);
}

void convertAndPrint(int n)
{
    char convertedString[100];
    itoa(n, convertedString);
    printf("%d converts to string \"%s\"\n", n, convertedString);
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    static int i = 0;

    if (n < 0)
    {
        s[i++] = '-';
        n = -n;
    }

    if (n / 10)
        itoa(n / 10, s);

    s[i++] = n % 10 + '0';
    s[i] = '\0';
}
