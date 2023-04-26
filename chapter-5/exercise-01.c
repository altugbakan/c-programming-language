#include <stdio.h>
#include <ctype.h>

int getch();
void ungetch(int);
int getint(int*);

int main()
{
    int i, res;

    res = getint(&i);

    if (res != '-' && res != '+')
        printf("getint() = %d\n", i);
    else
        printf("got invalid int: %c\n", res);

    return 0;
}

int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);

        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();

    if (!isdigit(c))
    {
        ungetch(c);

        return sign == -1 ? '-' : '+';
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    
    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch()
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}