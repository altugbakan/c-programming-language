#include <stdio.h>

#define MAXLINE 100

void itoa(int, char[]);
void reverse(char[]);
int abs(int n);

int main()
{
    int num = 12345;
    char s[MAXLINE];

    itoa(num, s);

    printf("num = %d, itoa(num) = %s\n", num, s);

    return 0;
}

void itoa(int n, char s[])
{
    static int i = 0;
    static int sign = 0;

    if (n == 0)
    {
        if (sign < 0)
            s[i++] = '-';

        if (i == 0)
            s[0] = '0';

        reverse(s);
        return;
    }

    sign = n;

    s[i++] = abs(n % 10) + '0';

    itoa(n / 10, s);
}

void reverse(char s[])
{
    int len, j;
    char temp;

    for (len = 0; s[len] != '\0'; ++len)
        ;

    for (j = 0; j < len / 2; ++j)
    {
        temp = s[j];
        s[j] = s[len - j - 1];
        s[len - j - 1] = temp;
    }
}

int abs(int n)
{
    return n < 0 ? -n : n;
}