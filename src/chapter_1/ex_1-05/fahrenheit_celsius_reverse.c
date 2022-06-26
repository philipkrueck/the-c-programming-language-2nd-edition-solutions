/**
 * Exercise: 1-5
 * Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.
 */
#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main()
{
    float celsius, fahrenheit;

    printf("%s\t%s\n", "Fahrenheit", "Celsius");

    for (fahrenheit = UPPER; fahrenheit >= LOWER; fahrenheit = fahrenheit - STEP)
    {
        celsius = (5.0 / 9.0) * (fahrenheit - 32.0);
        printf("%3.0f\t%10.1f\n", fahrenheit, celsius);
    }

    return 0;
}