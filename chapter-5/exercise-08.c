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
    printf("day_of_year(2020, 2, 30) = %d\n", day_of_year(2020, 2, 30));

    month_day(2020, 60, &m, &d);
    printf("month_day(2020, 60) = %d, %d\n", m, d);
    month_day(2019, 366, &m, &d);
    printf("month_day(2019, 366) = %d, %d\n", m, d);

    return 0;
}

int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (month < 1 || month > 12)
        return -1;
    if (day < 1 || day > 31)
        return -1;
    if (month == 2 && day > 28 + leap)
        return -1;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return -1;

    for (i = 1; i < month; ++i)
        day += daytab[leap][i];

    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (yearday < 1 || yearday > 365 + leap)
    {
        *pmonth = -1;
        *pday = -1;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; ++i)
        yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;
}