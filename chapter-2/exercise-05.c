#include <stdio.h>

int any(char s1[], char s2[]);

int main()
{
    char s1[] = "Hello, World!";
    char s2[] = "eo, Wld";

    printf("s1: %s\ns2: %s\nany(s1, s2): %d\n", s1, s2, any(s1, s2));
    return 0;
}

int any(char s1[], char s2[])
{
    int i, j;

    for (i = 0; s1[i] != '\0'; i++)
    {
        for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; j++)
            ;

        if (s2[j] != '\0')
            return i;
    }

    return -1;
}