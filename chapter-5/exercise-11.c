#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABSIZE 8

void entab(int tabsize);
void detab(int tabsize);

int main(int argc, char *argv[])
{
    int tabsize = TABSIZE;

    if (argc > 1)
    {
        if (argc > 2)
            tabsize = atoi(argv[2]);
    }
    else 
    {
        printf("Usage: %s <entab|detab> [tabsize]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "entab") == 0)
        entab(tabsize);
    else if (strcmp(argv[1], "detab") == 0)
        detab(tabsize);
    else
    {
        printf("Usage: %s <entab|detab> [tabsize]\n", argv[0]);
        return 1;
    }

    return 0;
}

void entab(int tabsize)
{
    int c, pos, spaces, tabs;

    spaces = tabs = 0;
    for (pos = 0; (c = getchar()) != EOF; pos = (pos + 1) % tabsize)
    {
        if (c == ' ')
        {
            ++spaces;

            if (pos + 1 == tabsize)
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
                    putchar(' ');

            if (c == '\n')
                pos = -1;

            putchar(c);
        }
    }
}

void detab(int tabsize)
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
            for (int i = 0; i < tabsize - pos; ++i)
                putchar(' ');

            pos = 0;
        }
        else
        {
            putchar(c);
            pos = (pos + 1) % tabsize;
        }
    }
}