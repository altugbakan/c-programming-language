#include <stdio.h>

#define MAXLINE 1000

int _getline(char s[], int lim);
void reverse(char s[], int len);

int main()
{
    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = _getline(line, MAXLINE)) > 0)
    {
        reverse(line, len);
        printf("%s\n", line);
    }

    return 0;
}

/* _getline:  read a line into s, return length */
int _getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    s[i] = '\0';

    return i;
}

/* reverse:  reverses string s in place */
void reverse(char s[], int len)
{
    char temp;

    for (int i = 0; i < len / 2; ++i)
    {
        temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}