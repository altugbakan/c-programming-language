#include <stdio.h>

#define MAXLINE 100

void itob(int n, char s[], int b);
void reverse(char s[]);
int abs(int n);

int main()
{
    int num = 12345;
    char s[MAXLINE];

    itob(num, s, 16);
    printf("num = %d, itob(num, 16) = %s\n", num, s);

    itob(num, s, 2);
    printf("num = %d, itob(num, 2) = %s\n", num, s);

    return 0;
}

void itob(int n, char s[], int b)
{
    int i, sign;
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    sign = n;
    i = 0;

    do
    {
        s[i++] = digits[abs(n % b)];
    } while ((n /= b) > 0);

    if (sign < 0)
        s[i++] = '-';

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