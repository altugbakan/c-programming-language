#include <stdio.h>
#include <ctype.h>

#define MAXLINE 25
#define OCTALSIZE 4

int main()
{
    char *s = "testing the output characters with non-graphic characters such as \012 \034 \023";
    int index = 0;

    for (; *s != '\0'; s++)
        if (!isgraph(*s))
        {
            if (index + OCTALSIZE > MAXLINE)
            {
                putchar('\n');
                index = 0;
            }

            index += OCTALSIZE;
            printf("\\%03o", *s);
        }
        else
        {
            if (++index > MAXLINE)
            {
                putchar('\n');
                index = 1;
            }

            putchar(*s);
        }

    putchar('\n');
    return 0;
}