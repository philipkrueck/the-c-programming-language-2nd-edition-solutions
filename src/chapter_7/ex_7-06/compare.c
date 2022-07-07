/**
 * Exercise 7-6
 * Write a program to compare two files,
 * printing the first line where they differ.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[])
{
    FILE *fp_one, *fp_two;

    if (argc != 3) /* no args: copy stdin to stdout */
    {
        fprintf(stderr, "specify 2 files\n");
        return 1;
    }

    fp_one = fopen(argv[1], "r");
    fp_two = fopen(argv[2], "r");

    if (fp_one == NULL || fp_two == NULL)
    {
        fprintf(stderr, "cannot open file\n");
        return 1;
    }
    char line_one[MAX_LINE_LENGTH], line_two[MAX_LINE_LENGTH];
    while ((fgets(line_one, MAX_LINE_LENGTH, fp_one)) != NULL &&
           (fgets(line_two, MAX_LINE_LENGTH, fp_two)) != NULL)
        if (strcmp(line_one, line_two) != 0)
        {
            printf("contents of files are not equal\n");
            printf("line in file one: %s\nline in file two: %s\n", line_one, line_two);
            exit(0);
        }

    printf("contents of files are equal\n");
    exit(0);
}