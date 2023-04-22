#include <stdio.h>

#define MAXLINE 100

void itoa(int n, char s[]);
void reverse(char s[]);
int abs(int n);

int main()
{
    int num = 12345;
    char s[MAXLINE];

    printf("The initial version of itoa() is not able to handle");
    printf(" due to the fact that the largest negative number");
    printf(" cannot be represented as a positive number.\n\n");

    itoa(num, s);
    printf("num = %d, itoa(num) = %s\n", num, s);

    return 0;
}

void itoa(int n, char s[])
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