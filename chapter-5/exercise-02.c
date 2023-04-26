#include <stdio.h>
#include <ctype.h>

int getch();
void ungetch(int);
int getfloat(float*);

int main()
{
    float f;

    printf("'getfloat' returns an 'int' value to return the");
    printf(" success status, like EOF.\n\n"); 

    getfloat(&f);
    printf("getfloat() = %f\n", f);

    return 0;
}

int getfloat(float *pn)
{
    int c, sign;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
    {
        ungetch(c);

        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    if (c == '.')
    {
        int i, j;

        for (i = 0; isdigit(c = getch()); ++i)
            *pn = 10 * *pn + (c - '0');

        for (j = 0; j < i; ++j)
            *pn /= 10;
    }

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