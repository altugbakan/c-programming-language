#include <stdio.h>
#include <stdarg.h>

#define MAXLINE 1000
#define MAXFMT 3

int _getline(char line[], int lim);
void minprintf(char *, ...);

int main()
{
    char *fmt = "int: %i, %d, double: %f, string: %s, char: %c, hexadecimal: %x, %X, octal: %o\n";

    minprintf(fmt, 1, 2, 1.0, "word", 'a', 0xab, 0xcd, 012);

    return 0;
}

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    unsigned uval;
    char ufmt[MAXFMT];

    ufmt[0] = '%';
    ufmt[2] = '\0';

    va_start(ap, fmt);

    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }

        switch (*++p)
        {
        case 'i':
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'c':
            ival = va_arg(ap, int);
            printf("%c", ival);
            break;
        case 'x':
        case 'X':
        case 'o':
            uval = va_arg(ap, unsigned);
            ufmt[1] = *p;
            printf(ufmt, uval);
            break;
        default:
            putchar(*p);
            break;
        }
    }

    va_end(ap);
}

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