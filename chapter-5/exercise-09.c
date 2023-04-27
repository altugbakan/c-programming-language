#include <stdio.h>

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

static char daytab[2][13] =
    {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
     {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main()
{
    int m, d;

    printf("day_of_year(2020, 2, 29) = %d\n", day_of_year(2020, 2, 29));

    month_day(2020, 60, &m, &d);
    printf("month_day(2020, 60) = %d, %d\n", m, d);

    return 0;
}

int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    p = *(daytab + leap);

    while (month--)
        day += *p++;

    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p, *sp;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    sp = p = *(daytab + leap);

    p += 1;
    while (yearday > *p)
        yearday -= *p++;

    *pmonth = p - sp;
    *pday = yearday;
}