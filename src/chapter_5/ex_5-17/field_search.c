/**
 * Exercise: 5-17
 * Add  a  field-searching  capability,  so  sorting  may  be  done  on  fields  within  lines,  each  field  sorted  according  to  an  independent  set  of  options.
 * (The  index  for  this  book  was sorted with -df for the index category and -n for the page numbers.)
 */

/**
 * NOTE: I did not solve this problem, as I didn't understand what the problem was asking.
 * If you can give me an example input and output structure, it would be highly appreciated - thanks!
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000              /* maximum number of lines to be read */
#define MAX_INPUT_LINE_LENGTH 1000 /* max length of any input line */
#define MAX_SIZE 10000             /* max size of all read lines combined */

typedef int (*compType)(void *, void *);

/* functions */
void readCLIArgs(int argc, char *argv[], int *numeric, int *fold, int *directory);
compType selectComparator(int *numeric, int *fold, int *directory);
int readlines(char *lines[], int maxNumLines, char *text);
void writelines(char *lines[], int maxNumLines);
int getLine(char *s, int numLines);
void quicksort(void *lineptr[], int left, int right, compType);
int numcmp(char *, char *);
int dircmp(char *vOne, char *vTwo);
int lowerdircmp(char *sOne, char *sTwo);
int dircmpWithOption(char *sOne, char *sTwo, int isFold);
void dirString(char *s);
void swap(void *v[], int, int);

/* external variables */
char *lineptr[MAXLINES]; /* pointers to text lines */

int main(int argc, char *argv[])
{
    char text[MAX_SIZE];
    int nlines;      /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */
    int fold = 0;    /* 1 if fold compare sort */
    int directory = 0;
    compType comparator;

    /* 1. check for flags */
    readCLIArgs(argc, argv, &numeric, &fold, &directory);

    /* 2. select comparator */
    comparator = selectComparator(&numeric, &fold, &directory);

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

void readCLIArgs(int argc, char *argv[], int *numeric, int *fold, int *directory)
{
    for (; argc > 1; argc--)
        if (strcmp(*++argv, "-n") == 0)
            *numeric = 1;
        else if (strcmp(*argv, "-d") == 0)
            *directory = 1;
        else if (strcmp(*argv, "-f") == 0)
            *fold = 1;
}

/* given gcc's block feature, we could simplify this by using function composition */
compType selectComparator(int *numeric, int *fold, int *directory)
{
    compType comparator;

    if (*numeric)
        return (compType)numcmp;
    else if (*directory)
        if (*fold)
            return (compType)lowerdircmp;
        else
            return (compType)dircmp;
    else if (*fold)
        return (compType)strcasecmp;
    else
        return (compType)strcmp;
}

/* quicksort:  sort v[left]...v[right] into increasing order */
void quicksort(void *v[], int left, int right, compType comp)
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

/* makes comparisons on numbers, letters and blanks */
int dircmp(char *sOne, char *sTwo)
{
    return dircmpWithOption(sOne, sTwo, 0);
}

int lowerdircmp(char *sOne, char *sTwo)
{
    return dircmpWithOption(sOne, sTwo, 1);
}

int dircmpWithOption(char *sOne, char *sTwo, int isFold)
{
    char tOne[MAX_INPUT_LINE_LENGTH], tTwo[MAX_INPUT_LINE_LENGTH];
    strcpy(tOne, sOne);
    strcpy(tTwo, sTwo);

    dirString(tOne);
    dirString(tTwo);

    if (isFold)
        return strcasecmp(tOne, tTwo);
    else
        return strcmp(tOne, tTwo);
}

void dirString(char *s)
{
    char *p;
    p = s;

    for (; *p != '\0'; p++)
        if (isalnum(*p) || isblank(*p))
            *s++ = *p;

    *s = '\0';
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