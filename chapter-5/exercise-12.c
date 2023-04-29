#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABSIZE 8
#define TABSTART 0

void entab(int, int);
void detab(int, int);
int istab(int, int, int);

int main(int argc, char *argv[])
{
    int tabsize = TABSIZE;
    int tabstart = TABSTART;
    int c;
    char *command, *prog = argv[0];

    if (argc > 1)
    {
        command = *++argv;
        argc--;

        while (--argc)
            if ((*++argv)[0] == '-')
                tabstart = atoi(&(*argv)[1]);
            else if ((*argv)[0] == '+')
                tabsize = atoi(&(*argv)[1]);
            else
            {
                printf("Usage: %s <entab|detab> [-tabstart] [+tabsize]\n", prog);
                return 1;
            }

        if (strcmp(command, "entab") == 0)
            entab(tabsize, tabstart);
        else if (strcmp(command, "detab") == 0)
            detab(tabsize, tabstart);
        else
        {
            printf("Usage: %s <entab|detab> [tabsize]\n", prog);
            return 1;
        }

        return 0;
    }
    else
    {
        printf("Usage: %s <entab|detab> [-tabstart] [+tabsize]\n", prog);
        return 1;
    }
}

void entab(int tabsize, int tabstart)
{
    int c, pos, spaces, tabs;

    spaces = tabs = 0;
    for (pos = 0; (c = getchar()) != EOF; pos = (pos + 1 - tabstart) % tabsize + tabstart)
    {
        if (c == ' ')
        {
            ++spaces;

            if (istab(pos + 1, tabsize, tabstart))
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
                pos = tabstart - 1;
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

void detab(int tabsize, int tabstart)
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
            while (!istab(pos++, tabsize, tabstart))
                putchar(' ');

            pos = tabstart;
        }
        else
        {
            putchar(c);
            pos = (pos + 1 - tabstart) % tabsize + tabstart;
        }
    }
}

int istab(int pos, int tabsize, int tabstart)
{
    return pos >= tabstart && (pos - tabstart) % tabsize == 0;
}