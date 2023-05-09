#include <stdio.h>

#define MAXLINE 1000
#define MAXPAGE 8

void fileprint(FILE *, char *);

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc < 2)
    {
        printf("Usage: %s <files...>\n", argv[0]);
        return 1;
    }

    while (--argc > 0)
    {
        if ((fp = fopen(*++argv, "r")) == NULL)
        {
            fprintf(stderr, "Could not open file %s\n", *argv);
            return 1;
        }

        fileprint(fp, *argv);

        fclose(fp);
    }

    return 0;
}

void fileprint(FILE *fp, char *name)
{
    int l = 0, p = 0;
    char line[MAXLINE];

    printf("\t\t\tFile: %s\n\n", name);
    
    while (fgets(line, MAXLINE, fp) != NULL)
    {
        printf("%s", line);
        
        if (++l == MAXPAGE)
        {
            printf("\n\t\t\tPage %d\n\n", ++p);
            l = 0;
        }
    }

    printf("\n\t\t\tPage %d\n\n", ++p);
}