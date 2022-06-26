/**
 * Exercise: 5-14
 * Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order.
 * Be sure that -r works with -n.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000              /* maximum number of lines to be read */
#define MAX_INPUT_LINE_LENGTH 1000 /* max length of any input line */
#define MAX_SIZE 10000             /* max size of all read lines combined */

typedef int (*compType)(void *, void *);

/* functions */
void readCLIArgs(int argc, char *argv[], int *numeric, int *reverse);
compType selectComparator(int *numeric, int *reverse);
int readlines(char *lines[], int maxNumLines, char *text);
void writelines(char *lines[], int maxNumLines);
int getLine(char *s, int numLines);
void quicksort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int reverseNumcmp(void *vOne, char *vTwo);
int reverseStrcmp(void *, void *);
void swap(void *v[], int, int);

/* external variables */
char *lineptr[MAXLINES]; /* pointers to text lines */

int main(int argc, char *argv[])
{
    char text[MAX_SIZE];
    int nlines;      /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */
    int reverse = 0; /* 1 if reverse sort */
    compType comparator;

    /* 1. check for flags */
    readCLIArgs(argc, argv, &numeric, &reverse);

    /* 2. select comparator */
    comparator = selectComparator(&numeric, &reverse);

    /* 3. read lines */
    if ((nlines = readlines(lineptr, MAXLINES, text)) >= 0)
    {
        /* numeric ? numcmp : strcmp */
        /* 4. sort lines */
        quicksort((void **)lineptr, 0, nlines - 1, comparator);

        /* 5. write lines*/
        printf("\nsorted lines: \n");
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("input too big to sort\n");
        return 1;
    }
}

void readCLIArgs(int argc, char *argv[], int *numeric, int *reverse)
{
    for (; argc > 1; argc--)
        if (strcmp(*++argv, "-n") == 0)
            *numeric = 1;
        else if (strcmp(*argv, "-r") == 0)
            *reverse = 1;
        else if (strcmp(*argv, "-rn") == 0 || strcmp(*argv, "-nr") == 0)
        {
            *numeric = 1;
            *reverse = 1;
        }
}

compType selectComparator(int *numeric, int *reverse)
{
    if (*numeric && *reverse)
        return (compType)reverseNumcmp;
    else if (*numeric && !(*reverse))
        return (compType)numcmp;
    else if (!(*numeric) && *reverse)
        return (compType)reverseStrcmp;
    else
        return (compType)strcmp;
}

/* quicksort:  sort v[left]...v[right] into increasing order */
void quicksort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    if (left >= right) /* do  nothing if array contains */
        return;        /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last - 1, comp);
    quicksort(v, last + 1, right, comp);
}

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int reverseNumcmp(void *vOne, char *vTwo)
{
    return -numcmp(vOne, vTwo);
}

int reverseStrcmp(void *vOne, void *vTwo)
{
    return -strcmp(vOne, vTwo);
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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

void writelines(char *lines[], int numLines)
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