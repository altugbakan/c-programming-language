#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define TEMPSIZE 2000

enum
{
    NAME,
    PARENS,
    BRACKETS
};

void dcl();
void dirdcl();
void paramdcl();
int gettoken();

int tokentype;
int nexttoken = -1;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main(int argc, char *argv[])
{
    int type;
    char temp[TEMPSIZE];

    printf("Updated to handle qualifiers and function arguments.");
    printf(" Try: \"static int f(char *, int, double)\"\n\n");

    while (gettoken() != EOF)
    {
        out[0] = '\0';

        while (strcmp(token, "static") == 0 || strcmp(token, "const") == 0)
        {
            strcat(out, token);
            gettoken();
        }

        strcpy(datatype, token);
        dcl();

        if (tokentype != '\n')
            printf("syntax error\n");

        printf("%s: %s %s\n", name, out, datatype);
    }

    return 0;
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
    {
        if (name[0] == '\0')
            strcpy(name, token);
    }
    else
        printf("error: expected name or (dcl)\n");

    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(')
        {
            strcat(out, " function expecting");
            paramdcl();
            strcat(out, " and returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

void paramdcl()
{
    char temp[MAXTOKEN];

    do
    {
        dcl();

        if (tokentype == '*')
        {
            strcat(out, " pointer to");
            tokentype = gettoken();
        }

        strcat(out, " ");
        strcat(out, token);
    } while (tokentype == ',' && strcat(out, ","));

    if (tokentype != ')')
        printf("missing ) in parameter declaration\n");
}

int getch();
void ungetch(int);

int gettoken()
{
    int c;
    char *p = token;

    if (nexttoken != -1)
    {
        nexttoken = -1;

        return tokentype;
    }

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