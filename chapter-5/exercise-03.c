#include <stdio.h>

#define MAXLINE 1000

void _strcat(char*, char*);

int main()
{
    char s1[MAXLINE] = "Hello ";
    char s2[] = "world!";

    printf("s1: %s, s2: %s\n", s1, s2);
    _strcat(s1, s2);
    printf("strcat(s1, s2): %s\n", s1);

    return 0;
}

void _strcat(char *s, char *t)
{
    while (*s)
        s++;

    while (*s++ = *t++)
        ;
}