/**
 * Exercise 4-2
 * Extend atof to handle scientific notation of the form
 * 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally signed exponent.
 */
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 100

/* rudimentary calculator */
int main()
{
    double sum, atof(char s[]);
    char line[MAXLINE];
    int getLine(char line[], int max);

    sum = 0;
    while (getLine(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));

    return 0;
}

/* atof:  convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign, expSign, expPower;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1; /* handle sign */
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++) /* handle digits before `.` */
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.') /* handle digits after `.` */
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    if (s[i] == 'e' || s[i] == 'E') /* handle exponent */
        i++;

    expSign = (s[i] == '-') ? -1 : 1; /* handle exponent sign */
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (expPower = 0; isdigit(s[i]); i++) /* handle exponent power */
        expPower = 10 * expPower + (s[i] - '0');

    return (sign * val / power) * pow(10, expSign * expPower);
}

int getLine(char line[], int maxLength)
{
    char currChar;
    int lineLength;

    for (lineLength = 0; lineLength < maxLength - 1 && (currChar = getchar()) != EOF && currChar != '\n'; ++lineLength)
        line[lineLength] = currChar;

    /* reset the rest of the current line back to 0 */
    for (lineLength = lineLength; lineLength < maxLength - 1; ++lineLength)
        line[lineLength] = '\0';

    return lineLength;
}
