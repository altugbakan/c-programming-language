#include <stdio.h>
#include <ctype.h>

double atof(char[]);

int main()
{
    char s1[] = "123.45";
    char s2[] = "123.45e-3";
    char s3[] = "123.45E+3";

    printf("%s = %f\n", s1, atof(s1));
    printf("%s = %f\n", s2, atof(s2));
    printf("%s = %f\n", s3, atof(s3));

    return 0;
}

double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;

        int exp_sign = (s[i] == '-') ? -1 : 1;
        int exp_val = 0;

        if (s[i] == '+' || s[i] == '-')
            i++;

        for (; isdigit(s[i]); i++)
            exp_val = 10 * exp_val + (s[i] - '0');

        if (exp_sign == -1)
            for (int j = 0; j < exp_val; j++)
                power *= 10.0;
        else
            for (int j = 0; j < exp_val; j++)
                power /= 10.0;
    }

    return sign * val / power;
}