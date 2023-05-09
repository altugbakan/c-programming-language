#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void match(char *, FILE *);

long lineno = 0;
int except = 0, number = 0, found = 0;

int main(int argc, char *argv[])
{
    int c;
    char *pattern;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch(c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
    
    if (argc < 1)
    {
        printf("Usage: find -x -n pattern [files...]\n");
        return 1;
    }

    pattern = *argv;

    if (argc == 1)
       match(pattern, stdin);
    else
        while (--argc > 0)
        {
            FILE *fp;
            
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                printf("Could not open file %s\n", *argv);
                return 1;
            }

            match(pattern, fp);
            fclose(fp);
        }

    return found;
}

void match(char * pattern, FILE *fp)
{
    char line[MAXLINE];

    while (fgets(line, MAXLINE, fp) > 0)
    {
        lineno++;

        if ((strstr(line, pattern) != NULL) != except)
        {
            if (number)
                printf("%ld:", lineno);

            printf("%s", line);
            found++;
        }
    }
}