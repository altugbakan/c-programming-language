#include <stdio.h>

#define MAXLINE 20
#define TABSIZE 8

int lastblank(char s[], int pos);
void printuntil(char s[], int lim);
void removeuntil(char s[], int lim);
int detab(char s[], int pos);

int main()
{
    char line[MAXLINE];
    int c, pos;

    pos = 0;
    while ((c = getchar()) != EOF)
    {
        line[pos] = c;

        if (c == '\t')
            pos = detab(line, pos);
        else if (c == '\n')
        {
            printuntil(line, pos);
            putchar('\n');
            pos = 0;
        }
        else
            ++pos;

        if (pos == MAXLINE)
        {
            int blank = lastblank(line, pos);
            printuntil(line, blank);
            putchar('\n');
            removeuntil(line, blank + 1);
            pos = pos - (blank + 1);
        }
    }

    return 0;
}

int lastblank(char s[], int pos)
{
    for (int i = pos; i >= 0; --i)
    {
        if (s[i] == ' ')
            return i;
    }

    return MAXLINE - 1;
}

void printuntil(char s[], int lim)
{
    for (int i = 0; i < lim; ++i)
    {
        putchar(s[i]);
    }
}

void removeuntil(char s[], int lim)
{
    for (int i = 0; i < MAXLINE; ++i)
    {
        if (i + lim < MAXLINE)
            s[i] = s[i + lim];
        else
            s[i] = '\0';
    }
}

int detab(char s[], int pos)
{
    int i;

    s[pos] = ' ';
    for (i = 1; (i + pos) % TABSIZE != 0 && i + pos < MAXLINE; ++i)
    {
        s[i + pos] = ' ';
    }

    return i + pos;
}