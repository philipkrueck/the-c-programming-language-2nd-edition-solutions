/**
 * Exercise: 1-6
 * Verify that the expression getchar() != EOF is 0 or 1.
 */
#include <stdio.h>

int main()
{
    printf("The value of the expression 'getChar() != EOF' is: %d\n", getchar() != EOF);
    return 0;
}

/**
 * EOF character is Ctrl+D on Unix and Ctrl+C on Windows.
 */