#include <stdio.h>

#define MAX_LENGTH 10

int main()
{
    int lengths[MAX_LENGTH];

    for (int i = 0; i < MAX_LENGTH; ++i)
    {
        lengths[i] = 0;
    }

    int c, len;

    len = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            if (len > 0)
            {
                if (len > MAX_LENGTH)
                {
                    len = MAX_LENGTH;
                }

                ++lengths[len - 1];
            }
            len = 0;
        }
        else
        {
            ++len;
        }
    }

    printf("\nHorizontal histogram of word lengths:\n");
    for (int i = 0; i < MAX_LENGTH; ++i)
    {
        if (i == MAX_LENGTH - 1)
        {
            printf(">%2d | ", i);
        }
        else
        {
            printf("%3d | ", i + 1);
        }

        for (int j = 0; j < lengths[i]; ++j)
        {
            printf("=");
        }
        printf("\n");
    }

    printf("\nVertical histogram of word lengths:\n");
    int max = 0;
    for (int i = 0; i < MAX_LENGTH; ++i)
    {
        if (lengths[i] > max)
        {
            max = lengths[i];
        }
    }

    for (int i = max; i > 0; --i)
    {
        for (int j = 0; j < MAX_LENGTH; ++j)
        {
            if (lengths[j] >= i)
            {
                printf("  =   ");
            }
            else
            {
                printf("      ");
            }
        }
        printf("\n");
    }
    printf("----- ----- ----- ----- ----- ----- ----- ----- ----- -----\n");
    printf("  1     2     3     4     5     6     7     8     9   > 9\n");
}