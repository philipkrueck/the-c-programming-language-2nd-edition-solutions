/**
 * Exercise: 5-11
 * Modify  the  program  entab  and  detab  (written  as  exercises  in  Chapter  1)
 * to  accept a list of tab stops as arguments.
 * Use the default tab settings if there are no arguments.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_LENGTH 1000 /* max length of any input line */
#define MAX_TABS 100               /* max number of tab stops per line */
#define DEFAULT_COLS 4             /* if no arguments are provided, tab stop positions are every DEFAULT_COLS */

/* functions */
int getLine(char *line, int limit);
int getTabStopPositions(int argc, char *argv[], int *tabStopPositions);
void detab(char *inputLine, char *outputLine, int *tabStopPositions, int numTabStops);
int tabsAreIncreasing(int *tabStopPositions, int i);
int positionsToNextTabStop(int column, int *tabStopPositions, int numTabStops);

int main(int argc, char *argv[])
{
    char inputLine[MAX_INPUT_LINE_LENGTH];
    char outputLine[MAX_INPUT_LINE_LENGTH];
    int tabStopPositions[MAX_TABS];
    int numTabStops;

    if ((numTabStops = getTabStopPositions(argc, argv, tabStopPositions)) < 0)
        printf("invalid tab stop positions provided\n");
    else
        while (getLine(inputLine, MAX_INPUT_LINE_LENGTH) > 0)
        {
            detab(inputLine, outputLine, tabStopPositions, numTabStops);
            printf("%s", outputLine);
        }

    return 0;
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

/**
 * extract tab stop positions from command line argument list
 * store in tabStopPositions
 * return len of tabStopPositions if valid, -1 if invalid, 0 if not provided
 */
int getTabStopPositions(int argc, char *argv[], int *tabStopPositions)
{
    if (!argv)
        return 0;

    int i;
    for (i = 0; --argc > 0; i++)
        if (!(tabStopPositions[i] = atoi(*++argv)) || tabStopPositions[i] < 0 || !tabsAreIncreasing(tabStopPositions, i))
            return -1;

    return i; /* if no argument list is provided, i will be 0 */
}

/* return 1 if tabStopPositions at i is greater than at i-1 */
int tabsAreIncreasing(int *tabStopPositions, int i)
{
    return (i > 0) ? (tabStopPositions[i] > tabStopPositions[i - 1]) : 1;
}

void detab(char *inputLine, char *outputLine, int *tabStopPositions, int numTabStops)
{
    int numBlanks;
    char *startPointer = outputLine;

    while (*inputLine != '\0')
        if (*inputLine == '\t')
        {
            numBlanks = positionsToNextTabStop(outputLine - startPointer, tabStopPositions, numTabStops);
            while (numBlanks-- > 0)
                *outputLine++ = ' ';
            inputLine++;
        }
        else
            *outputLine++ = *inputLine++;

    *outputLine = '\0';
}

/* return number of positions between column and nearest tabstop */
int positionsToNextTabStop(int column, int *tabStopPositions, int numTabStops)
{
    if (!numTabStops)
        return DEFAULT_COLS - (column % DEFAULT_COLS);

    while (numTabStops > 0 && column >= *tabStopPositions)
    {
        tabStopPositions++;
        numTabStops--;
    }

    return *tabStopPositions - column;
}

/**
 * In Unix Systems you can use input and output redirection:
 * The commands that normally take their input from standard input, will use the input file and
 * instead of writing to standard output, the commands will write to the output file.
 *
 * > ./detab < input.txt > output.txt
 */