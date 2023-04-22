#include <stdio.h>

#define MAXLINE 100

void itoa(int n, char s[], int w);
void reverse(char s[]);
int abs(int n);

int main()
{
    int num = 12345;
    char s[MAXLINE];

    itoa(num, s, 10);
    printf("num = %d, itoa(num, 10) = %s\n", num, s);

    itoa(num, s, 11);
    printf("num = %d, itoa(num, 11) = %s\n", num, s);

    itoa(num, s, 12);
    printf("num = %d, itoa(num, 12) = %s\n", num, s);

    return 0;
}

void itoa(int n, char s[], int w)
{
    int i, sign;

    sign = n;
    i = 0;

    do
    {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';

    while (i < w)
        s[i++] = ' ';

    s[i] = '\0';

    reverse(s);
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