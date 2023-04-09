#include <stdio.h>

#define CHAR_COUNT 128

int main()
{
    int chars[CHAR_COUNT];

    for (int i = 0; i < CHAR_COUNT; ++i)
    {
        chars[i] = 0;
    }

    int c;
    while ((c = getchar()) != EOF)
    {
        ++chars[c];
    }

    printf("\nHistogram of character frequencies:\n");
    for (int i = 0; i < CHAR_COUNT; ++i)
    {
        if (chars[i] > 0 && i != '\t' && i != '\n' && i != ' ')
        {
            putchar(i);
            printf(" | ");
            for (int j = 0; j < chars[i]; ++j)
            {
                printf("=");
            }
            printf("\n");
        }
    }
}