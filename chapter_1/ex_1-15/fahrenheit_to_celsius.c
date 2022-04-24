/**
 * Exercise: 1-15
 * Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.
 */
#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float celsius(float fahrenheit);

int main()
{
    printf("%s\t%s\n", "Fahrenheit", "Celsius");

    for (float fahrenheit = LOWER; fahrenheit <= UPPER; fahrenheit = fahrenheit + STEP)
    {
        printf("%3.0f\t%10.1f\n", fahrenheit, celsius(fahrenheit));
    }

    return 0;
}

float celsius(float fahrenheit)
{
    return (5.0 / 9.0) * (fahrenheit - 32.0);
}