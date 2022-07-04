/**
 * Exercise 7-1
 * Write  a  program  that  converts  upper  case  to  lower  or  lower  case  to  upper,
 * depending on the name it is invoked with, as found in argv[0].
 **/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int c;
    int (*transform)(int); // pointer to transform function

    if (argc > 1 && strcmp(argv[1], "upper") == 0)
        transform = toupper;
    else if (argc > 1 && strcmp(argv[1], "lower") == 0)
        transform = tolower;
    else
    {
        printf("Usage: %s upper|lower\n", argv[0]);
        return 1;
    }

    while ((c = getchar()) != EOF)
        putchar(transform(c));
    return 0;
}