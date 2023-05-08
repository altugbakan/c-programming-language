#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int c;

    if (strcmp(argv[0], "./lower.out") == 0)
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    else if (strcmp(argv[0], "./upper.out") == 0)
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    else
    {
        printf("Invalid name \"%s\", only \"./lower.out\" and \"./upper.out\" are supported.\n", argv[0]);
    }

    return 0;
}