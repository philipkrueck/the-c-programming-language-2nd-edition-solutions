/**
 * Exercise 7-4
 * Write a private version of scanf analogous to minprintf from the previous section.
 **/

#include <stdio.h>
#include <stdarg.h>

/* functions */
void minscanf(char *fmt, ...);

int main()
{
    // integer
    int d;
    minscanf("%d", &d);
    printf("integer: %d\n", d);

    // unsigned integer
    unsigned ud;
    minscanf("%u", &ud);
    printf("unsigned integer: %u\n", ud);

    // float
    float f;
    minscanf("%f", &f);
    printf("float: %f\n", f);

    // string
    char s[100];
    minscanf("%s", s);
    printf("string: %s\n", s);

    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap; // points to each unnamed arg in turn
    char *p;
    int num_scanned = 0;

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
                scanf("%d", va_arg(ap, int *));
                num_scanned++;
                break;
            case 'f':
                scanf("%f", va_arg(ap, float *));
                num_scanned++;
                break;
            case 's':
                scanf("%s", va_arg(ap, char *));
                num_scanned++;
                break;
            default:
                putchar(*p);
                break;
            }
        }
    }
}
