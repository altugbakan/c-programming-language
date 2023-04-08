#include <stdio.h>

int main()
{
    int c;

    /* print value of getchar() != EOF, use Ctrl+D to send EOF */
    while (c = getchar() != EOF)
    {
        printf("%d", c);
    }

    /* print last value of getchar() != EOF */
    printf("%d", c);
}