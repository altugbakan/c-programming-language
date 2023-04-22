#include <stdio.h>

#define MAXLINE 100

void expand(char s1[], char s2[]);

int main()
{
    char s1[] = "a-b-z0-3-6f-h";
    char s2[MAXLINE];

    printf("Before expand: %s\n", s1);
    expand(s1, s2);
    printf("After expand: %s\n", s2);

    return 0;
}

void expand(char s1[], char s2[])
{
    int i, j;

    for (int i = j = 0; s1[i] != '\0'; i++)
    {
        if (s1[i] == '-' && i > 0 && s1[i + 1] != '\0')
        {
            for (int k = s1[i - 1] + 1; k <= s1[i + 1]; k++)
            {
                s2[j++] = k;
            }
            i++;
        }
        else
        {
            s2[j++] = s1[i];
        }
    }
    s2[j] = '\0';
}