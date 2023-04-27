#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000
#define MAXOP 100
#define NUMBER '0'

int _getline(char *, int);
int atoi(char *);
void itoa(int, char *);
void reverse(char *);
int strindex(char *, char *);
int getop(char *);
int getch();
void ungetch(int c);

int main()
{
    char s1[MAXLINE];
    char s2[] = "12345";
    char s3[MAXLINE];
    char s4[] = "123456";
    char s5[] = "Hello, world";
    char s6[] = "llo, w";
    char s7[MAXLINE];
    int i1 = 12345;

    printf("Enter string for getline(): ");
    _getline(s1, MAXLINE);
    printf("getline(): %s", s1);

    printf("s2: %s, atoi(s1): %d\n", s2, atoi(s2));

    printf("i1: %d", i1);
    itoa(i1, s3);
    printf(", itoa(i1): %s\n", s3);

    printf("s4: %s", s4);
    reverse(s4);
    printf(", reverse(s4): %s\n", s4);

    printf("s5: %s, s6: %s, strindex(s5, s6): %d\n", s5, s6, strindex(s5, s6));

    printf("Enter string for getop(): ");
    getop(s7);
    printf("getop(): %s\n", s7);

    return 0;
}

int _getline(char *s, int lim)
{
    char *st = s;

    while (--lim > 0 && (*s = getchar()) != EOF && *s != '\n')
        ++s;

    if (*s == '\n')
        ++s;

    *s = '\0';

    return s - st;
}

int atoi(char *s)
{
    int n = 0;

    while (*s >= '0' && *s <= '9')
    {
        n = 10 * n + (*s - '0');
        ++s;
    }

    return n;
}

void itoa(int n, char *s)
{
    int sign;
    char *st = s;

    if ((sign = n) < 0)
        n = -n;

    do
    {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        *s++ = '-';

    *s = '\0';

    reverse(st);
}

#include <string.h>

void reverse(char *s)
{
    int c;
    char *e;

    for (e = s + strlen(s) - 1; s < e; s++, e--)
    {
        c = *s;
        *s = *e;
        *e = c;
    }
}

int strindex(char *s, char *t)
{
    char *a, *b, *st = s;

    while (*s)
    {
        for (a = s, b = t; *b && *a == *b; a++, b++)
            ;

        if (b > t && *b == '\0')
            return s - st;

        s++;
    }

    return -1;
}

int getop(char *s)
{
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t')
        ;

    *(s + 1) = '\0';

    if (!isdigit(*s) && *s != '.')
        return *s;

    if (isdigit(*s))
        while (isdigit(*(++s) = getch()))
            ;

    if (*s == '.')
        while (isdigit(*(++s) = c = getch()))
            ;

    *s = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
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