#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINECOUNT 10
#define MAXLINES 5000

char *lineptr[MAXLINES];
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int linecount);

void _qsort(char *lineptr[], int left, int right);

int main(int argc, char *argv[])
{
    int nlines, linecount = LINECOUNT;

    if (argc > 1 && argv[1][0] == '-')
    {
        linecount = atoi(argv[1] + 1);
        if (linecount < 1 || linecount > MAXLINES)
            linecount = LINECOUNT;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        _qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines, linecount);

        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");

        return 1;
    }
}

#define MAXLEN 1000
int _getline(char *, int);
char *alloc(int);
void swap(char *v[], int i, int j);

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;

    while ((len = _getline(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines, int linecount)
{
    int i;

    for (i = nlines - linecount; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void _qsort(char *v[], int left, int right)
{
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);

    _qsort(v, left, last - 1);

    _qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];

    v[i] = v[j];

    v[j] = temp;
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n)
    {
        allocp += n;

        return allocp - n;
    }
    else
        return 0;
}

int _getline(char *s, int lim)
{
    int c;

    char *t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;

    if (c == '\n')
        *s++ = c;

    *s = '\0';

    return s - t;
}
