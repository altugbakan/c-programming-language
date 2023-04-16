#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    int c, comment, squote, dquote;
    int bracket, brace, parenthesis;

    comment = squote = dquote = OUT;
    bracket = brace = parenthesis = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == '\'')
        {
            if (squote == OUT)
                squote = IN;
            else
                squote = OUT;
        }
        else if (c == '"')
        {
            if (dquote == OUT)
                dquote = IN;
            else
                dquote = OUT;
        }
        else if (c == '/' && squote == OUT && dquote == OUT)
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
        }
        else if (c == '*' && squote == OUT && dquote == OUT)
        {
            if ((c = getchar()) == '/')
            {
                comment = OUT;
                c = getchar();
            }
        }

        if (comment == OUT && squote == OUT && dquote == OUT)
        {
            if (c == '(')
                parenthesis++;
            else if (c == ')')
                parenthesis--;
            else if (c == '[')
                bracket++;
            else if (c == ']')
                bracket--;
            else if (c == '{')
                brace++;
            else if (c == '}')
                brace--;
        }
    }

    if (parenthesis != 0)
        printf("Unbalanced parenthesis\n");
    if (bracket != 0)
        printf("Unbalanced bracket\n");
    if (brace != 0)
        printf("Unbalanced brace\n");

    if (parenthesis == 0 && bracket == 0 && brace == 0)
        printf("Balanced\n");

    return 0;
}