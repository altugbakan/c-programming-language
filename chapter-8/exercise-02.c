#include <fcntl.h>
#include <stdlib.h>
#include "syscalls.h"

#undef NULL
#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#define PERMS 0666

typedef struct _iobuf
{
    int cnt;
    char *ptr;
    char *base;
    int read : 1;
    int write : 1;
    int unbuf : 1;
    int eof : 1;
    int err : 1;
    int fd;
} _FILE;

int _fillbuf(_FILE *);
int _flushbuf(int, _FILE *);
_FILE *_fopen(char *, char *);

_FILE _iob[OPEN_MAX] = {
    {0, (char *)0, (char *)0, 1, 0, 0, 0, 0, 0},
    {0, (char *)0, (char *)0, 0, 1, 0, 0, 0, 1},
    {0, (char *)0, (char *)0, 0, 1, 1, 0, 0, 2}};

int main(int argc, char *argv[])
{
    static char errmsg[] = "error: missing filename\n";
    static char resultmsg[] = "\n\nThe resulting code was larger and"
                              " the execution was slower.\n";
    int c;
    _FILE *fp;

    if (argc == 1)
        fp = stdin;
    else
        fp = _fopen(argv[1], "r");

    while ((c = getc(fp)) != EOF)
        write(1, &c, 1);

    write(1, resultmsg, sizeof resultmsg);

    return 0;
}

_FILE *_fopen(char *name, char *mode)
{
    int fd;
    _FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->read && fp->write) == 0)
            break;

    if (fp >= _iob + OPEN_MAX)
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
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r')
        fp->read = 1;
    else
        fp->write = 1;

    return fp;
}

int _fillbuf(_FILE *fp)
{
    int bufsize;

    if (!fp->read || fp->eof || fp->err)
        return EOF;

    bufsize = fp->unbuf ? 1 : BUFSIZ;

    // Allocate buffer if it does not exist
    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;

    // Reset pointer to start, fill with read values
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->eof = 1;
        else
            fp->err = 1;

        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char)*fp->ptr++;
}