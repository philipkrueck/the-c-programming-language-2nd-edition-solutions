/**
 * Exercise 8-1
 * The standard library function
 * `int fseek(FILE *fp, long offset, int origin)`
 * is identical to lseek except that fp is a file pointer instead of a file descriptor and return value is an int status,
 * not a position. Write fseek.
 * Make sure that your fseek coordinates properly with the buffering done for the other functions of the library.
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
int _fflush(FILE *fp);
int _fclose(FILE *fp);
int _fseek(FILE *fp, long offset, int origin);

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

    if (*mode == 'w') /* open file for writing */
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

    fp->ptr = fp->base;                       /* set current position to start of buffer */
    fp->cnt = read(fp->fd, fp->ptr, bufsize); /* count is size of file */

    if (--fp->cnt < 0) /* handle EOF and error cases */
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

    bufsize = (fp->flag._UNBUF == 1) ? BUFSIZ : 1; /* check if we are even using a buffer */

    if (fp->base == NULL) /* base should be NULL when flushing */
    {
        if ((fp->base = (char *)malloc(bufsize)) == NULL) /* allocate a new buffer */
        {
            return EOF;
        }
        *fp->base = '\0'; /* set base pointer to NULL character*/
    }

    fp->ptr = fp->base; /* set current position to start of buffer */

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

/* close everything within the file data structure */
int _fclose(FILE *fp)
{
    if (fp->flag._WRITE == 1)
        _fflush(fp);
    if (fp->base != NULL)
        free(fp->base);
    fp->base = NULL;
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->flag._EOF = 0;
    fp->flag._ERR = 0;
    fp->flag._READ = 0;
    fp->flag._WRITE = 0;
    return close(fp->fd);
}

/* flush buffer for FILE *fp when in writing mode */
int _fflush(FILE *fp)
{
    if (fp->flag._WRITE == 0) /* must be able to write */
    {
        fp->flag._ERR = 1;
        return EOF;
    }

    if (_flushbuf(EOF, fp) == EOF)
    {
        fp->flag._ERR = 1;
        return EOF;
    }

    fp->ptr = fp->base;                          /* set current position to start of buffer */
    fp->cnt = fp->flag._UNBUF == 1 ? 1 : BUFSIZ; /* reset count to buffer size */

    return 0;
}

/* */
int _fseek(FILE *fp, long offset, int origin)
{
    if (fp->flag._WRITE == 0 && fp->flag._READ == 0) /* must be able to read or write */
        return -1;

    if (lseek(fp->fd, offset, origin) == -1) /* seek to offset */
        return -1;

    return 0;
}

int main(int argc, char *argv[])
{
    int c;
    FILE *fp;

    while (--argc > 0)
    {
        if ((fp = _fopen(*++argv, "r")) == NULL)
        {
            exit(1);
        }
        else
        {
            _fseek(fp, 100L, 0); // move ahead in the file

            while ((c = getc(fp)) != EOF)
                putchar(c);
        }
    }
    _fclose(stdout);

    return 0;
}
