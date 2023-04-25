#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXOP 100
#define NUMBER '0'

int buf[BUFSIZE];
int bufp = 0;

int getch();
int getop(char[]);

int main()
{
    char s[MAXOP];

    getop(s);
    printf("getop(): %s\n", s);
}

int getch()
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

int getop(char s[])
{
    int i, c, next;
    static int lastc = 0;

    if (lastc == 0)
        c = getch();
    else
    {
        c = lastc;
        lastc = 0;
    }

    while ((s[0] = c) == ' ' || c == '\t')
        c = getch();
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    if (c == '-')
    {
        next = getch();
        if (!isdigit(next) && next != '.')
        {
            return c;
        }
        c = next;
    }
    else
    {
        c = getch();
    }

    i = 0;
    while (isdigit(s[++i] = c))
        c = getch();

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF)
        lastc = c;

    return NUMBER;
}