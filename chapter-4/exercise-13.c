#include <stdio.h>

void reverse(char[]);

int main()
{
    char s[] = "123456789";

    printf("s = %s, ", s);
    reverse(s);
    printf("reverse(s) = %s\n", s);

    return 0;
}

void reverse(char s[])
{
    static int pos = 0;
    static int len;
    char temp;

    if (pos == 0)
        for (len = 0; s[len] != '\0'; ++len)
            ;
    else if (pos >= len / 2)
        return;

    temp = s[pos];
    s[pos] = s[len - pos - 1];
    s[len - pos - 1] = temp;
    ++pos;

    reverse(s);
}