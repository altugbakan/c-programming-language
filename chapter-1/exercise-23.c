#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    int c, comment, quote;

    comment = quote = OUT;

    while ((c = getchar()) != EOF)
    {
        if (c == '"')
        {
            if (quote == OUT)
                quote = IN;
            else
                quote = OUT;
        }
        else if (c == '/' && quote == OUT)
        {
            int prev;

            prev = c;
            if ((c = getchar()) == '*')
                comment = IN;
            else if (c == '/')
            {
                while ((c = getchar()) != EOF && c != '\n')
                    ; // do nothing
            }
            else
                putchar(prev);
        }
        else if (c == '*' && quote == OUT)
        {
            if ((c = getchar()) == '/')
            {
                comment = OUT;
                c = getchar();
            }
            else
                putchar(c);
        }

        if (comment == OUT)
            putchar(c);
    }

    return 0;
}