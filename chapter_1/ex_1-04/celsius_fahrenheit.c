/**
 * Exercise: 1-4
 * Write a program to print the corresponding Celsius to Fahrenheit table.
 */
#include <stdio.h>

int main()
{
    float lower, upper, step;
    float fahrenheit, celsius;

    lower = -20.0;
    upper = 100.0;
    step = 20.0;

    celsius = lower;

    printf("%s\t%s\n", "Celsius", "Fahrenheit");

    while (celsius <= upper)
    {
        fahrenheit = (celsius * (9.0 / 5.0)) + 32.0;
        printf("%3.0f\t%13.1f\n", celsius, fahrenheit);
        celsius = celsius + step;
    }

    return 0;
}