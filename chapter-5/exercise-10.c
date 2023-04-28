#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'
#define MAXLINE 1000

int getop(char[], char[]);
void push(double);
double pop();

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    double op2;
    
    while (--argc > 0)
    {
        switch (getop(line, *++argv))
        {
        case NUMBER:
            push(atof(*argv));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        default:
            printf("error: unknown command %s\n", *argv);
            break;
        }
    }

    printf("\t%.8g\n", pop());

    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop()
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getop(char s[], char line[])
{
    int i, j, c;

    i = 0;
    while ((s[0] = c = line[i++]) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;

    j = 0;
    if (isdigit(c))
        while (isdigit(s[++j] = c = line[i++]))
            ;

    if (c == '.')
        while (isdigit(s[++j] = c = line[i++]))
            ;

    s[j] = '\0';

    return NUMBER;
}