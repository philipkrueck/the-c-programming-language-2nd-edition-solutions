/**
 *
 * Exercise 5-06
 * Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
 * Good possibilities include getline (Chapters 1 and 4), atoi, itoa, and  their  variants  (Chapters  2, 3,  and  4),
 * reverse (Chapter  3),  and  strindex  and  getop(Chapter 4).
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000              /* maximum number of lines to be read */
#define MAX_INPUT_LINE_LENGTH 1000 /* max length of any input line */
#define MAX_SIZE 10000             /* max size of all read lines combined */

/* functions */
int readlines(char *lines[], int maxNumLines, char *text);
int writelines(char *lines[], int maxNumLines);
int getLine(char *s, int numLines);
void quicksort(char *v[], int left, int right);

/* external variables */
char *lines[MAXLINES];

int main()
{
    int numLinesRead;
    char text[MAX_SIZE];

    /* 1. read lines */
    if ((numLinesRead = readlines(lines, MAXLINES, text)) >= 0)
    {
        /* 2. sort lines */
        quicksort(lines, 0, numLinesRead - 1);

        /* 3. write lines */
        printf("\nsorted lines: \n");
        writelines(lines, numLinesRead);
    }
    else
    {
        printf("error: input too big to sort.\n");
        return 1;
    }

    return 0;
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

int writelines(char *lines[], int numLines)
{
    while (numLines-- > 0)
        printf("%s\n", *lines++);
}

/* getLine: read a line into s, return length */
int getLine(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        *(s + i) = c;
    }

    if (c == '\n')
    {
        *(s + i) = c;
        ++i;
    }

    *(s + i) = '\0';

    return i;
}

/* quicksort:  sort v[left]...v[right] into increasing order */
void quicksort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right) /* do nothing if array contains */
        return;        /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last - 1);
    quicksort(v, last + 1, right);
}

/* swap:  interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}