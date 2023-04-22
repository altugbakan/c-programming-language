#include <stdio.h>

#define MAXLINE 100

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
    char t[MAXLINE] = "Hello\tWor\nld";
    char s[MAXLINE];

    printf("Before escape: %s\n", t);
    escape(s, t);
    printf("After escape: %s\n", s);
    unescape(t, s);
    printf("After unescape: %s\n", t);

    return 0;
}

void escape(char s[], char t[])
{
    int i, j;

    for (int i = j = 0; t[i] != '\0'; i++)
    {
        switch (t[i])
        {
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i, j;

    for (int i = j = 0; t[i] != '\0'; i++)
    {
        if (t[i] == '\\')
        {
            switch (t[++i])
            {
            case 't':
                s[j++] = '\t';
                break;
            case 'n':
                s[j++] = '\n';
                break;
            default:
                s[j++] = '\\';
                s[j++] = t[i];
                break;
            }
        }
        else
        {
            s[j++] = t[i];
        }
    }
    s[j] = '\0';
}