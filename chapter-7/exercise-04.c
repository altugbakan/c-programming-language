#include <stdio.h>
#include <stdarg.h>

#define MAXFMT 100

void minscanf(char *, ...);

int main()
{
    int i, d;
    float f;
    char c;
    unsigned x, X, o;

    scanf("%i, %d, %f, %c, %x, %X, %o", &i, &d, &f, &c, &x, &X, &o);

    printf("int: %i, %d, float: %f, char: %c, hexadecimal: %x, %X, octal: %o\n", i, d, f, c, x, X, o);

    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, a;
    int i = 0, *ival;
    double *dval;
    unsigned *uval;
    char *cval, ufmt[MAXFMT];

    va_start(ap, fmt);

    for (p = fmt; *p; p++)
    {
        ufmt[i++] = *p;

        if (*p != '%')
        {
            continue;
        }

        ufmt[i++] = a = *++p;
        ufmt[i] = '\0';

        switch (a)
        {
        case 'i':
        case 'd':
            ival = va_arg(ap, int *);
            scanf(ufmt, ival);
            break;
        case 'f':
            dval = va_arg(ap, double *);
            scanf(ufmt, dval);
            break;
        case 'c':
            cval = va_arg(ap, char *);
            scanf(ufmt, cval);
            break;
        case 'x':
        case 'X':
        case 'o':
            uval = va_arg(ap, unsigned *);
            scanf(ufmt, uval);
            break;
        default:
            break;
        }

        i = 0;
    }

    va_end(ap);
}