#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100
#define OUTLEN 1000

enum
{
    NAME,
    PARENS,
    BRACKETS
};

void dcl();
void dirdcl();
void reset();
int gettoken();

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[OUTLEN];
char buf[BUFSIZE];
int bufp = 0;

int main()
{
    while (gettoken() != EOF)
    {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();

        if (tokentype != '\n')
        {
            printf("syntax error\n");
            reset();
        }

        printf("%s: %s %s\n", name, out, datatype);
    }

    return 0;
}

void reset()
{
    tokentype = -1;
    bufp = 0;

    for (int i = 0; i < MAXTOKEN; ++i)
    {
        token[i] = name[i] = datatype[i] = '\0';
    }

    for (int i = 0; i < OUTLEN; ++i)
    {
        out[i] = '\0';
    }

    for (int i = 0; i < BUFSIZE; ++i)
    {
        buf[i] = '\0';
    }
}

void dcl()
{
    int ns;

    for (ns = 0; gettoken() == '*';)
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl()
{
    int type;

    if (tokentype == '(')
    {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");

    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

int getch();
void ungetch(int);

int gettoken()
{
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;

        *p = '\0';

        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;

        *p = '\0';
        ungetch(c);

        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

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