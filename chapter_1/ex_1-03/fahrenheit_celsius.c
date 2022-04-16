/**
 * Exercise: 1-3
 * Modify the temperature conversion program to print a heading above the table.
 */

#include <stdio.h>

int main()
{
    float lower, upper, step;
    float fahrenheit, celsius;

    lower = 0.0;
    upper = 300.0;
    step = 20.0;

    fahrenheit = lower;

    printf("%s\t%s\n", "Fahrenheit", "Celsius");

    while (fahrenheit <= upper)
    {
        celsius = (5.0 / 9.0) * (fahrenheit - 32.0);
        printf("%3.0f\t%13.1f\n", fahrenheit, celsius);
        fahrenheit = fahrenheit + step;
    }

    return 0;
}