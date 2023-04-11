#include <stdio.h>

#define MAXLINE 1000

int _getline(char s[], int lim);
int _remove(char s[], int len);

int main()
{
    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = _getline(line, MAXLINE)) > 0)
        if (_remove(line, len) > 0)
            printf("->%s<-\n", line);

    return 0;
}

/* _getline:  read a line into s, return length */
int _getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}

/* _remove:  remove trailing whitespace from 's' */
int _remove(char s[], int len)
{
    int lastchange = len;

    for (int i = len - 1; i >= 0; --i)
    {
        if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
        {
            s[i] = '\0';
            lastchange = i;
        }
        else
            i = 0;
    }

    return lastchange;
}