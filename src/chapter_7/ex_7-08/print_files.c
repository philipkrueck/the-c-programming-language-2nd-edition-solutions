/**
 * Exercise 7-8
 * Write a program to print a set of files, starting each new one on a new page,
 * with a title and a running page count for each file.
 */

#include <stdio.h>

#define MAX_CHARS_PER_LINE 80
#define LINES_PER_PAGE 10

/* functions */
void print_file(FILE *fp, char *file_name);
void print_header(int page_count, char *file_name);

int main(int argc, char *argv[])
{
    if (argc == 1)
        print_file(stdin, "stdin");

    for (int i = 1; i < argc; i++)
    {
        char *name = argv[i];
        FILE *fp = fopen(name, "r");
        print_file(fp, name);
    }
}

void print_file(FILE *fp, char *file_name)
{
    char line[MAX_CHARS_PER_LINE];
    int page_count = 0;
    long lineno = 0;
    print_header(page_count, file_name);
    while (fgets(line, MAX_CHARS_PER_LINE, fp) != NULL)
    {
        lineno++;
        printf("%d %ld %s", page_count, lineno, line);
        if (lineno % LINES_PER_PAGE == 0)
            print_header(page_count++, file_name);
    }
}

void print_header(int page_count, char *file_name)
{
    printf("\f");
    printf("********************************************************\n");
    printf("file name: %s\n", file_name);
    printf("page: %d\n", page_count);
    printf("********************************************************\n");
}
