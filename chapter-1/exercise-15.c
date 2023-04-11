#include <stdio.h>

float tocelsius(float fahr);

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;   /* lower limit of temperature table */
    upper = 300; /* upper limit */
    step = 20;   /* step size */

    fahr = lower;
    while (fahr <= upper)
    {
        celsius = tocelsius(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

float tocelsius(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}
