/**
 * Exercise: 1-2
 * Experiment to find out what happens when prints's argument string contains \c,
 * where c is some character not listed above.
 */

#include <stdio.h>

int main()
{
    printf("Hello, universe!\c");
    return 0;
}

/**
 * \c is an unkown escape character.
 * The compiler will show a warning during compile time.
 */