#include <stdio.h>

#define BUFSIZE 100

int getch();
void ungetch(int);

int buf[BUFSIZE];
int bufp = 0;

int main()
{
    printf("EOF has the value -1, and is defined as an 'int'. 'buf',");
    printf(" which is defined as a 'char' array, cannot hold this value correctly.");
    printf(" Changing it to an 'int' array solves this problem.\n");

    ungetch(EOF);
    printf("getch(): %d\n", getch());

    return 0;
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