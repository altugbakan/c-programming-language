#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    FILE *f1, *f2;
    char s1[MAXLINE], s2[MAXLINE];
    char *c1, *c2;

    if (argc < 3)
    {
        printf("Usage: %s <file 1> <file 2>\n", argv[0]);
        return 1;
    }

    if ((f1 = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return 2;
    }

    if ((f2 = fopen(argv[2], "r")) == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", argv[2]);
        return 2;
    }    

    while ((c1 = fgets(s1, MAXLINE, f1)) != NULL && ((c2 = fgets(s2, MAXLINE, f2)) != NULL) && strcmp(s1, s2) == 0)
        ;

    if (c1 == NULL)
    {
        c2 = fgets(s2, MAXLINE, f2);
        if (c2 == NULL)
            printf("Files %s and %s are identical\n", argv[1], argv[2]);
        else
            printf("End of file %s\n", argv[1]);
    }
    else if (c2 == NULL)
        printf("End of file %s\n", argv[2]);
    else
        printf("s1: %ss2: %s", s1, s2);

    fclose(f1);
    fclose(f2);
    
    return 0;
}