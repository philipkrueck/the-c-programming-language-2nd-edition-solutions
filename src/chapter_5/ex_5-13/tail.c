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

#define MAXLINES 5000              /* maximum number of lines to be read */
#define MAX_INPUT_LINE_LENGTH 1000 /* max length of any input line */
#define MAX_SIZE 10000             /* max size of all read lines combined */

/* functions */
int getLine(char *line, int limit);
int extractN(int argc, char *argv[], int *n);
int readlines(char *lines[], int maxNumLines, char *text);
int writeLastNLines(char *lines[], int maxNumLines, int n);

int main(int argc, char *argv[])
{
    char *lines[MAXLINES]; /* pointers to lines */
    int n = 10;            /* number of lines */
    int numLinesRead;
    char text[MAX_SIZE];

    if (!extractN(argc, argv, &n))
    {
        printf("invalid argument list; usage: %s [-m pos] [+n col]\n", *argv);
        return -1;
    }
    else if ((numLinesRead = readlines(lines, MAXLINES, text)) >= 0)
    {
        printf("\nlast %d lines: \n", n);
        writeLastNLines(lines, numLinesRead, n);
    }
    else
    {
        printf("error: input too big to sort.\n");
        return 1;
    }

    return 0;
}

/* extract starting position and tab stop increase from command line argument list into m and n
 * return 0 if argument list is invalid, 1 if valid
 */
int extractN(int argc, char *argv[], int *n)
{
    if (strcmp(*++argv, "-n") == 0)
    {
        if ((*n = atoi(*++argv)) < 1)
            return 0;
        *n = abs(*n); /* handle negative input */
    }

    return 1;
}

int readlines(char *lines[], int maxNumLines, char *text)
{
    int currLineLength, linesReadSoFar;
    char *currLinePointer, currLine[MAX_INPUT_LINE_LENGTH];

    currLinePointer = text;
    linesReadSoFar = 0;
    while ((currLineLength = getLine(currLine, MAX_INPUT_LINE_LENGTH)) > 0)
        if (linesReadSoFar >= maxNumLines || currLinePointer >= text + MAX_SIZE)
            return -1;
        else
        {
            currLine[currLineLength - 1] = '\0';
            strcpy(currLinePointer, currLine);
            lines[linesReadSoFar++] = currLinePointer;
            currLinePointer += currLineLength;
        }

    return linesReadSoFar;
}

int writeLastNLines(char *lines[], int numLines, int n)
{
    if (numLines > n)
    {
        int diff = numLines - n;
        while (diff-- > 0)
            lines++;
    }
    else
        n = numLines;

    while (n-- > 0)
        printf("%s\n", *lines++);
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