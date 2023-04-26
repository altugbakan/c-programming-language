#include <stdio.h>

#define MAXLEN 100

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
int _strncmp(char *, char *, int);

int main()
{
    char s1[MAXLEN] = "Hello ";
    char s2[] = "world!";

    char s3[MAXLEN] = "Hello ";
    char s4[] = "world!";

    char s5[] = "Hello!";
    char s6[] = "Hello?";

    printf("s1: %s, s2: %s", s1, s2);
    _strncpy(s1, s2, 5);
    printf(", strncpy(s1, s2, 5): %s\n", s1);

    printf("s3: %s, s4: %s", s3, s4);
    _strncat(s3, s4, 5);
    printf(", strncat(s3, s4, 5): %s\n", s3);

    printf("s5: %s, s6: %s", s5, s6);
    printf(", strncmp(s5, s6, 5): %d", _strncmp(s5, s6, 5));
    printf(", strncmp(s5, s6, 6): %d\n", _strncmp(s5, s6, 6));

    return 0;
}

char *_strncpy(char *s, char *t, int n)
{
    char *st = s;

    while (*t && n-- > 0)
        *s++ = *t++;

    while (n-- > 0)
        *s++ = '\0';

    return st;
}

char *_strncat(char *s, char *t, int n)
{
    char *st = s;

    while (*s)
        s++;

    while (n-- > 0 && *t)
        *s++ = *t++;

    if (n)
        *s = '\0';

    return st;
}

int _strncmp(char *s, char *t, int n)
{
    while (*s && *t && --n > 0)
    {
        if (*s != *t)
            return *s - *t;
        s++, t++;
    }

    return *s - *t;
}