#include <stdio.h>

int strend(char*, char*);

int main()
{
    char s1[] = "Hello";
    char s2[] = "world";
    char s3[] = "lo";

    printf("s1: %s, s2: %s, strend(s1, s2): %d\n", s1, s2, strend(s1, s2));
    printf("s1: %s, s3: %s, strend(s1, s3): %d\n", s1, s3, strend(s1, s3));
    
    return 0;
}

int strend(char* s, char* t)
{
    char *ts = t;
    char *ss = s;

    while (*s)
        s++;

    while (*t)
        t++;

    while (*t == *s && t != ts && s != ss)
        --t, --s;

    return t == ts;
}