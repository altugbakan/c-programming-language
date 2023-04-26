#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
int getsingle(char[]);
void push(double);
double pop();
int _getline(char[], int);

/* Added variables for line handling */
int start = 0;
char line[MAXLINE];
/* --------------------------------- */

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    line[0] = '\0';
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
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
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    
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

/* Modified getop */
int getop(char s[])
{
    int i, c;

    if (line[start] == '\0')
    {
        if (_getline(line, MAXLINE) == 0)
            return EOF;
        else
            start = 0;
    }

    while ((s[0] = c = line[start++]) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;

    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = line[start++]))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = line[start++]))
            ;

    s[i] = '\0';
    start--;

    return NUMBER;
}
/* -------------- */

/* Added getline function */
int _getline(char s[], int lim)
{
    int c, i;

    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if (i < lim - 1)
            s[i] = c;

    if (i < lim - 1)
    {
        if (c == '\n')
        {
            s[i] = c;
            ++i;
        }
        s[i] = '\0';
    }
    else
    {
        s[lim - 1] = '\0';
    }

    return i;
}
/* ---------------------- */
