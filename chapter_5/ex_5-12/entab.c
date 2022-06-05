/**
 * Exercise: 5-12
 * Extend entab and detab to accept the shorthand
 *      entab -m +n
 * to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_LENGTH 1000 /* max length of any input line */

/* functions */
int getLine(char *line, int limit);
void entab(char *inputLine, char *outputLine, int *m, int *n);
int extractArguments(int argc, char *argv[], int *m, int *n);

int main(int argc, char *argv[])
{
    char inputLine[MAX_INPUT_LINE_LENGTH];
    char outputLine[MAX_INPUT_LINE_LENGTH];
    int m = 1; /* default starting position */
    int n = 4; /* default tab stop every n columns */

    if (!extractArguments(argc, argv, &m, &n))
        printf("invalid argument list; usage: %s [-m pos] [+n col]\n", *argv);
    else
    {
        printf("m: %d, n: %d", m, n);
        while (getLine(inputLine, MAX_INPUT_LINE_LENGTH) > 0)
        {
            entab(inputLine, outputLine, &m, &n);
            printf("%s", outputLine);
        }
    }

    return 0;
}

/* extract starting position and tab stop increase from command line argument list into m and n
 * return 0 if argument list is invalid, 1 if valid
 */
int extractArguments(int argc, char *argv[], int *m, int *n)
{
    for (; argc > 1; argc--)
    {
        if (strcmp(*++argv, "-m") == 0)
        {
            if ((*m = atoi(*++argv)) < 1)
                return 0;
            argc--;
        }
        else if (strcmp(*argv, "+n") == 0)
        {
            if ((*n = atoi(*++argv)) < 1)
                return 0;
            argc--;
        }
        else
            return 0;
    }
    return 1;
}

/* getLine: read a line into s, return length */
int getLine(char *line, int limit)
{
    int c, i;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        *(line + i) = c;

    if (c == '\n')
    {
        *(line + i) = c;
        ++i;
    }

    *(line + i) = '\0';

    return i;
}

void entab(char *inputLine, char *outputLine, int *m, int *n)
{
    int i;          /* index of inputLine */
    int j;          /* index of outputLine */
    int tabStopPos; /* next tab stop position */
    int numBlanks, numTabs;

    for (i = j = 0; inputLine[i] != '\0'; i++)
        if (inputLine[i] == ' ' && (i + 1) >= *m)
        {
            for (numBlanks = numTabs = 0; inputLine[i] == ' '; i++)
            {
                if ((i + 1) % *n == 0)
                {
                    numTabs++;
                    numBlanks = 0;
                }
                else
                {
                    numBlanks++;
                }
            };
            i--; /* move back one after last loop iteration */
            while (numTabs-- > 0)
                outputLine[j++] = '\t';
            while (numBlanks-- > 0)
                outputLine[j++] = ' ';
        }
        else
            outputLine[j++] = inputLine[i];

    outputLine[j] = '\0';
}

/**
 * In Unix Systems you can use input and output redirection:
 * The commands that normally take their input from standard input, will use the input file and
 * instead of writing to standard output, the commands will write to the output file.
 *
 * > ./entab -m 1 +n 4 < input.txt > output.txt
 */