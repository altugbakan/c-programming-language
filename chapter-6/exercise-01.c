#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100

int getword(char *, int);
int getch();
void ungetch(int);

int main()
{
    char word[MAXWORD];
    int type;

    while ((type = getword(word, MAXWORD)) != EOF)
    {
        if (type != '\0')
            printf("word: %s\n", word);
    }

    return 0;
}

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;
    else
        return c;

    if (isalpha(c) || c == '_' || c == '#' || c == '\'' || c == '"')
    {
        for (; --lim > 0; w++)
            if (!isalnum(*w = getch()) && *w != '_' && *w != '#' && *w != '\'' && *w != '"')
            {
                ungetch(*w);
                break;
            }
    }
    else if (c == '/')
    {
        if ((c = getch()) == '*')
        {
            for (; --lim > 0;)
            {
                if ((c = getch()) == '*')
                {
                    if ((c = getch()) == '/')
                    {
                        w--;
                        break;
                    }
                    else
                        ungetch(c);
                }
            }
        }
        else
            ungetch(c);
    }

    *w = '\0';
    return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch()
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}