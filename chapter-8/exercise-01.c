#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "syscalls.h"

void filecopy(int, int);
void error(char *, ...);

int main(int argc, char *argv[])
{
    int fd;
    char msg[] = "\n\nThis version of the program is faster than the one that uses standard library equivalents.\n";

    if (argc == 1)
        filecopy(0, 1);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
            {
                error("cat: can't open %s\n", *argv);
                return 1;
            }
            else
            {
                filecopy(fd, 1);
                close(fd);
            }

    write(1, msg, sizeof msg);

    return 0;
}

void filecopy(int ifd, int ofd)
{
    int n;
    char buf[BUFSIZ];

    while ((n = read(ifd, buf, sizeof buf)) > 0)
        if (write(ofd, buf, n) != n)
            error("cat: can't write to file");
}

void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);

    exit(1);
}