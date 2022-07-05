/**
 * Exercise 7-3
 * Revise minprintf to handle more of the other facilities of printf.
 **/

#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main()
{
    minprintf("integer: %d\n", 10);
    minprintf("unsigned integer: %u\n", 10);
    minprintf("hex: %x\n", 123483);
    minprintf("float: %f\n", 10.0);
    minprintf("string: %s\n", "hello");
    minprintf("character: %c\n", 'a');

    return 0;
}

void minprintf(char *fmt, ...)
{
    va_list ap; // points to each unnamed arg in turn
    char *p;

    va_start(ap, fmt); // init ap to first unnamed arg

    for (p = fmt; *p != '\0'; p++)
    {
        if (*p != '%')
            putchar(*p);
        else
        {
            switch (*++p)
            {
            case 'u':
            case 'd':
                printf("%d", va_arg(ap, int));
                break;
            case 'x':
                printf("%x", va_arg(ap, int));
                break;
            case 'f':
                printf("%f", va_arg(ap, double));
                break;
            case 's':
                printf("%s", va_arg(ap, char *));
                break;
            case 'c':
                printf("%c", va_arg(ap, int));
                break;
            default:
                putchar(*p);
                break;
            }
        }
    }
    va_end(ap);
}
