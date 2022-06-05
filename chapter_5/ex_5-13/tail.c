/**
 * Exercise: 5-13
 * Write the program tail, which prints the last n lines of its input.
 * By default, n is set to 10, let us say, but it can be changed by an optional argument so that
 *
 *      tail -nprints
 *
 * the last n lines.
 *
 * The program should behave rationally no matter how unreasonable the input or the value of n.
 * Write the program so it makes the best use of available storage;
 * lines should  be  stored  as  in  the  sorting  program  of  Section  5.6,
 * not  in  a  two-dimensional  array  of  fixed size.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_LENGTH 1000 /* max length of any input line */

/* functions */
int getLine(char *line, int limit);
int extractN(int argc, char *argv[], int *n);

int main(int argc, char *argv[])
{
    char inputLine[MAX_INPUT_LINE_LENGTH];
    char outputLine[MAX_INPUT_LINE_LENGTH];
    int m = 1; /* number of lines */

    if (!extractN(argc, argv, &n))
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
int extractN(int argc, char *argv[], int *n)
{
    if (strcmp(*argv, "+n") == 0)
    {
        if ((*n = atoi(*++argv)) < 1)
            return 0;
    }

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
