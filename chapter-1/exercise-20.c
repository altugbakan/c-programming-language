#include <stdio.h>

#define TABSIZE 8

int main()
{
    int c, pos;

    pos = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            putchar(c);
            pos = 0;
        }
        else if (c == '\t')
        {
            for (int i = 0; i < TABSIZE - pos; ++i)
                putchar(' ');

            pos = 0;
        }
        else
        {
            putchar(c);
            pos = (pos + 1) % TABSIZE;
        }
    }

    return 0;
}