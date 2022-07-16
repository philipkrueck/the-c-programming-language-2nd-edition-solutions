/**
 * Exercise 8-2
 * Rewrite _fopen and _fillbuf with fields instead of explicit bit operations.
 * Compare code size and execution speed.
 */

#include <fcntl.h>
#include "syscalls.h"
#include <unistd.h>
#include <stdlib.h>

#define PERMS 0666 /* RW for owner, group, others */

/* global variables */
FILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr */
                       {0, (char *)0, (char *)0, {1, 0, 0, 0, 0}, 0},
                       {0, (char *)0, (char *)0, {0, 1, 0, 0, 0}, 1},
                       {0, (char *)0, (char *)0, {0, 1, 1, 0, 0}, 2}};

/* function definitions */
int _fillbuf(FILE *);
int _flushbuf(int x, FILE *fp);

FILE *_fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    /* ensure valid mode */
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    /* get next free FILE struct */
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag._READ == 0) && (fp->flag._WRITE == 0)) /* find a free slot somewhere in the array */
            break;

    if (fp >= _iob + OPEN_MAX) /* no free FILE structs */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a')
    {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    }
    else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1)
        return NULL; // could not create or open file

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    (*mode == 'r') ? (fp->flag._READ = 1) : (fp->flag._WRITE = 1);

    return fp;
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;
    if (fp->flag._READ == 0) /* must be able to read */
        return EOF;

    bufsize = (fp->flag._UNBUF == 1) ? 1 : BUFSIZ; /* get buffer size */

    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, FILE *fp)
{
    int bufsize;

    if (fp->flag._WRITE == 0) /* must be able to write */
        return EOF;

    bufsize = (fp->flag._UNBUF == 1) ? BUFSIZ : 1;

    if (fp->base == NULL)
    {
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
        {
            return EOF;
        }
        *fp->base = '\0';
    }

    fp->ptr = fp->base;

    if (bufsize == 1)
    {
        *fp->ptr = x;
    }

    if (*fp->ptr != '\0' || bufsize == 1)
    {
        fp->cnt = write(fp->fd, fp->ptr, bufsize);

        if (--fp->cnt != bufsize)
        {
            fp->flag._ERR = 1;
            fp->cnt = 0;
            return EOF;
        }
    }

    if (bufsize > 1)
    {
        *fp->ptr = x;
        fp->cnt = BUFSIZ - 1;
    }

    return (unsigned char)*fp->ptr++;
}

int main(int argc, char *argv[])
{
    int c;
    FILE *fp;

    while (--argc > 0)
    {
        if ((fp = _fopen(*++argv, "r")) == NULL)
        {
            putchar('e');
            exit(1);
        }
        else
        {
            putchar('s');
            while ((c = getc(fp)) != EOF)
                putchar(c);
        }
    }

    return 0;
}
