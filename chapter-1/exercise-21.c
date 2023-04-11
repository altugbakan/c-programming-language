#include <stdio.h>

#define TABSIZE 8

int main()
{
    int c, pos, spaces, tabs;

    spaces = tabs = 0;
    for (pos = 0; (c = getchar()) != EOF; pos = (pos + 1) % TABSIZE)
    {
        if (c == ' ')
        {
            ++spaces;

            if (pos + 1 == TABSIZE)
            {
                ++tabs;
                spaces = 0;
            }
        }
        else
        {
            for (; tabs > 0; --tabs)
                putchar('\t');

            if (c == '\t')
            {
                spaces = 0;
                pos = -1;
            }
            else
                for (; spaces > 0; --spaces)
                    putchar('_');

            if (c == '\n')
                pos = -1;

            putchar(c);
        }
    }

    return 0;
}