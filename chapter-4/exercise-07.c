#include <stdio.h>
#include <string.h> /* for strlen */

#define BUFSIZE 100

int getch();
void ungetch(int);
void ungets(char[]);

char buf[BUFSIZE];
int bufp = 0;

int main()
{
    char s[] = "Hello, world!";

    printf("'ungets' does not need to know about 'buf' or 'bufp',");
    printf(" as 'ungetch' handles them automatically.\n");

    printf("s[]: %s\n", s);

    ungets(s);

    printf("getch: %c\n", getch());
    printf("getch: %c\n", getch());
}

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

void ungets(char s[])
{
    int len = strlen(s);

    while (len > 0)
        ungetch(s[--len]);
}