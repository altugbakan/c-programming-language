#include <stdio.h>

int getch();
void ungetch(char);

char buf;

int main()
{
    char c = 'a';

    printf("Since only one character might be pushed, 'buf' can");
    printf(" now be a 'char' instead of an array. Also, 'bufp'");
    printf(" can be removed, and an empty 'buf' can be represented");
    printf(" using -1 as its value.\n");

    printf("c: %c\n", c);

    ungetch(c);

    printf("getch(): %c\n", getch());
    printf("enter a character: ");
    printf("getch(): %c\n", getch());

    return 0;
}

int getch()
{
    char temp;

    if (buf == -1)
        return getchar();

    temp = buf;
    buf = -1;
    return temp;
}

void ungetch(char c)
{
    buf = c;
}