#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTORE 10000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char *linestore);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main()
{
    int nlines;
    char linestore[MAXSTORE];

    if ((nlines = readlines(lineptr, MAXLINES, linestore)) >= 0)
    {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);

        printf("\n\nThis version of the readlines function is slightly faster.\n");

        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int _getline(char *, int);

int readlines(char *lineptr[], int maxlines, char *linestore)
{
    int len, nlines;
    char line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(linestore, line);
            lineptr[nlines++] = linestore;
            linestore += len;
        }

    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; ++i)
        printf("%s\n", lineptr[i]);
}

int _getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

void swap(char *v[], int i, int j);

void qsort(char *v[], int left, int right)
{
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; ++i)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);

    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
