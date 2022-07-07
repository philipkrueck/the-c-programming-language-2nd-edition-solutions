/**
 * Exercise 7-7
 * Modify the pattern finding program of Chapter 5 to take its input from a set of named  files  or,  if  no  files  are  named  as  arguments, from the standard input.
 * Should the file name be printed when a matching line is found?
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

/* functions */
int get_line(char *line, int lim);
int parse_cli_args(int argc, char *argv[], int *except, int *number);
int print_lines_matching_pattern(FILE *fp, char *pattern, int *except, int *number);

/* global variables */
int except = 0, number = 0; /* 1 if except flag is set */

int main(int argc, char *argv[])
{
    int except = 0, number = 0, num_cli_args;
    FILE *fp;

    if ((num_cli_args = parse_cli_args(argc, argv, &except, &number)) == 0)
        exit(1);

    char *pattern = argv[num_cli_args + 1];
    int file_name_idx = num_cli_args + 2;

    while (file_name_idx < argc)
    {
        char *file_name = argv[file_name_idx];
        if ((fp = fopen(file_name, "r")) == NULL)
        {
            fprintf(stderr, "cannot open file %s\n", file_name);
            exit(1);
        }
        printf("matches in file: '%s':\n", file_name);
        print_lines_matching_pattern(fp, pattern, &except, &number);
        fclose(fp);
        printf("\n");
        file_name_idx++;
    }

    return 0;
}

/* return number of matching lines */
int print_lines_matching_pattern(FILE *fp, char *pattern, int *except, int *number)
{
    char line[MAXLINE];
    int found = 0;
    long lineno = 0;

    while (fgets(line, MAXLINE, fp) != NULL)
    {
        lineno++;
        if ((strstr(line, pattern) != NULL) != *except)
        {
            if (*number)
                printf("%ld:", lineno);
            printf("%s", line);
            found++;
        }
    }

    return found;
}

/* return number of cli arguments */
int parse_cli_args(int argc, char *argv[], int *except, int *number)
{
    int c;

    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c)
            {
            case 'x':
                *except = 1;
                break;
            case 'n':
                *number = 1;
                break;
            default:
                fprintf(stderr, "find: illegal option %c\n", c);
                argc = 0;
                break;
            }
    return *except + *number;
}

int get_line(char *s, int lim)
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