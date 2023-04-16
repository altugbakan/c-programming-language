#include <stdio.h>

#define MAXLINE 1000
#define YES 1
#define NO 0

int main()
{
    char c, _continue = YES;
    char line[MAXLINE];

    for (int i = 0; _continue; ++i)
    {
        if ((c = getchar()) == '\n')
        {
            _continue = NO;
        }
        else if (c == EOF)
        {
            _continue = NO;
        }
        else
        {
            line[i] = c;
        }
    }

    printf("%s\n", line);
}