#include <stdio.h>

#define MINLINE 80
#define MAXLINE 1000

int _getline(char s[], int lim);

int main()
{
    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = _getline(line, MAXLINE)) > 0)
        if (len > MINLINE)
            printf("%s", line);

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