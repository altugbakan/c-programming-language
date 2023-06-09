#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000

#define max(a, b) ((a) > (b) ? (a) : (b))

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);

void _qsort(void *lineptr[], int left, int right,
            int (*comp)(void *, void *));
void swap(void *v[], int, int);
char *alloc(int);
void afree(char *);
int numcmp(const char *, const char *);
int optcmp(const char *, const char *);

int fold = 0;
int dir = 0;
int fstart = 0, fsize = -1;
int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;
    int reverse = 0;

    while (--argc > 0)
        if ((*++argv)[0] == '-')
            while (*++argv[0])
            {
                switch (*argv[0])
                {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                case 'f':
                    fold = 1;
                    break;
                case 'd':
                    dir = 1;
                    break;
                default:
                    printf("error: unknown option %c\n", *argv[0]);
                    return 1;
                }
            }
        else if (*argv[0] == '+')
        {
            fstart = atoi(++argv[0]);
            while (*++argv[0] != '-' && *argv[0] != '\0')
                ;

            if (*argv[0] == '\0')
            {
                printf("error: usage: +fstart-fsize\n");
                return 1;
            }

            fsize = atoi(++argv[0]);

            if (fsize <= 0 || fstart <= 0)
            {
                printf("error: fsize and fstart must be greater than 0\n");
                return 1;
            }
        }
        else
        {
            printf("error: unknown option %s\n", *argv);
            return 1;
        }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        _qsort((void **)lineptr, 0, nlines - 1,
               (int (*)(void *, void *))(numeric ? numcmp : (fold || dir) ? optcmp
                                                                          : strcmp));
        writelines(lineptr, nlines, reverse);
        return 0;
    }
    else
    {
        printf("input too big to sort\n");
        return 1;
    }

    return 0;
}

void _qsort(void *v[], int left, int right,
            int (*comp)(void *, void *))
{
    int i, last;
    char *s1, *s2;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
    {
        int len = max(strlen(v[i]) + 1, fsize);
        s1 = alloc(len);
        strncpy(s1, v[i] + fstart, fsize < 0 ? len : fsize);
        len = max(strlen(v[left]) + 1, fsize);
        s2 = alloc(len);
        strncpy(s2, v[left] + fstart, fsize < 0 ? len : fsize);

        if ((*comp)(s1, s2) < 0)
            swap(v, ++last, i);

        afree(s1);
        afree(s2);
    }

    swap(v, left, last);
    _qsort(v, left, last - 1, comp);
    _qsort(v, last + 1, right, comp);
}

int numcmp(const char *s1, const char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000
int _getline(char *, int);

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

void writelines(char *lineptr[], int nlines, int reverse)
{
    int i;

    if (reverse)
        for (i = nlines - 1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    else
        for (i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
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

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
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

#include <ctype.h>

int optcmp(const char *s1, const char *s2)
{
    char c1, c2;

    while (*s1 != '\0' && *s2 != '\0')
    {
        if (dir)
        {
            while (!isalnum(*s1) && *s1 != '\0')
                s1++;

            while (!isalnum(*s2) && *s2 != '\0')
                s2++;
        }

        if (fold)
        {
            c1 = tolower(*s1++);
            c2 = tolower(*s2++);
        }
        else
        {
            c1 = *s1++;
            c2 = *s2++;
        }

        if (c1 != c2)
            return c1 - c2;
    }

    return 0;
}