/**
 * Exercise 8-1
 * Rewrite the program cat from Chapter 7 using read, write, open, and close instead of their standard library equivalents.
 * Perform experiments to determine the relative speeds of the two versions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

#define PERMS 0666 /* RW for owner, group, others */
#define BUFSIZE 1024

void copy_file(int fd_source, int fd_dest);
void error(char *fmt, ...);

int main(int argc, char *argv[])
{
    int fd_source;

    if (argc == 1)
        copy_file(0, 1);
    else
        while (--argc > 0)
            if ((fd_source = open(*++argv, O_RDONLY, 0)) == -1)
                error("failed to open %s", *argv);
            else
            {
                copy_file(fd_source, 1);
                close(fd_source);
            }

    return 0;
}

void copy_file(int fd_source, int fd_dest)
{
    char buf[BUFSIZE];
    int n;

    while ((n = read(fd_source, buf, BUFSIZE)) > 0)
        write(fd_dest, buf, n);
}

void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);

    exit(1);
}