#include <stdio.h>

int lower(int c);

int main()
{
    for (char c; (c = getchar()) != EOF; ++c)
    {
        putchar(lower(c));
    }

    return 0;
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}