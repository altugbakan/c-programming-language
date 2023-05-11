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
    int flag;
    int fd;
} _FILE;

enum _flags
{
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

int _fillbuf(_FILE *);
int _flushbuf(int, _FILE *);
_FILE *_fopen(char *, char *);
int _fclose(_FILE *);
int _fflush(_FILE *);

_FILE _iob[OPEN_MAX] = {
    {0, (char *)0, (char *)0, _READ, 0},
    {0, (char *)0, (char *)0, _WRITE | _UNBUF, 1},
    {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

int main(int argc, char *argv[])
{
    int c;
    _FILE *fp;

    if (argc == 1)
        fp = stdin;
    else
        fp = _fopen(argv[1], "r");

    while ((c = getc(fp)) != EOF)
        putchar(c);

    if (argc != 1)
        _fclose(fp);

    _fflush(stdout);

    return 0;
}

_FILE *_fopen(char *name, char *mode)
{
    int fd;
    _FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;

    return fp;
}

int _fclose(_FILE *fp)
{
    if (!fp || !fp->fd)
        return EOF;

    if (_fflush(fp) != EOF)
    {
        free(fp->base);
    }

    return close(fp->fd);
}

int _fillbuf(_FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;

        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char)*fp->ptr++;
}

int _flushbuf(int ch, _FILE *fp)
{
    int bufsize, cnt;

    if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    // Allocate buffer if it does not exist
    if (fp->base == NULL)
    {
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    }
    else
    {
        cnt = fp->ptr - fp->base;
        // Write the buffer to the file
        if (write(fp->fd, fp->base, cnt) != cnt)
        {
            fp->flag |= _ERR;
            return EOF;
        }
    }

    // Write the supplied value to the file
    if (write(fp->fd, &ch, 1) != 1)
    {
        fp->flag |= _ERR;
        return EOF;
    }

    // Reset pointer to base and put the supplied value
    fp->ptr = fp->base;
    fp->cnt = bufsize;

    return ch;
}

int _fflush(_FILE *fp)
{
    if (!fp || !fp->fd || (fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
        return EOF;

    return _flushbuf(0, fp);
}