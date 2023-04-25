#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
/* Added character limit */
#define CHARLIM 26
/* --------------------- */

int getop(char[]);
void push(double);
double pop();

int main()
{
    int type;
    double op2;
    /* Added variable to hold the most recently printed value */
    double last = 0;
    /* Added variable to hold 'variables' used in calculator */
    double vars[CHARLIM];
    /* ------------------------------------------------------ */
    char s[MAXOP];

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
        /* Modified to save the most recently printed value */
        case '\n':
            last = pop();
            printf("\t%.8g\n", last);
            break;
        /* Added most recently printed variable */
        case '!':
            push(last);
            break;
        /* Added setting variables */
        case '$':
            if ((type = getop(s)) != EOF && type >= 'a' && type <= 'z')
                push(vars[type - 'a']);
            else
                printf("error: invalid variable\n");
        /* Added handling for lowercase characters */
        default:
            if (type >= 'a' && type <= 'z')
            {
                vars[type - 'a'] = pop();
                push(vars[type - 'a']);
            }
            else
                printf("error: unknown command %s\n", s);
            break;
            /* ------------------------------------------------ */
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

int getch();
void ungetch(int c);

int getop(char s[])
{
    int i, c, next;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    if (c == '-')
    {
        next = getch();
        if (!isdigit(next) && next != '.')
        {
            return c;
        }
        c = next;
    }
    else
    {
        c = getch();
    }

    i = 0;
    while (isdigit(s[++i] = c))
        c = getch();

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch()
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}