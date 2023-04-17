#include <stdio.h>

#define MAXLINE 1000

int htoi(char s[]);

int main()
{
    int i;
    char c;
    char line[MAXLINE];

    printf("Enter a hexadecimal number: ");

    for (i = 0; (c = getchar()) != '\n'; ++i)
    {
        line[i] = c;
    }
    line[i] = '\0';

    printf("Value is %d\n", htoi(line));
    return 0;
}

int htoi(char s[])
{
    int i = 0, num = 0;

    if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
    {
        i = i + 2;
    }

    for (; s[i] != '\0'; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            num = num * 16 + (s[i] - '0');
        }
        else if (s[i] >= 'a' && s[i] <= 'f')
        {
            num = num * 16 + (s[i] - 'a' + 10);
        }
        else if (s[i] >= 'A' && s[i] <= 'F')
        {
            num = num * 16 + (s[i] - 'A' + 10);
        }
    }

    return num;
}