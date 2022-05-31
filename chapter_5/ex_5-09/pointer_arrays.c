/**
 * Exercise 5-09
 * Rewrite the routines day_of_year and month_day with pointers instead of indexing.
 * */

#include <stdio.h>

/* functions */
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

/* external variables */
static char *daytab[2] = {
    (char[]){0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    (char[]){0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main()
{
    int dayOfYear, m, d;

    if ((dayOfYear = day_of_year(2022, 5, 31)) < 0)
        printf("invalid input. enter valid year, month, and day.\n");
    else
        printf("day of year is %d\n", dayOfYear);

    month_day(2022, 151, &m, &d);
    if (!m || !d)
        printf("invalid input. enter valid year and day of year.\n");
    else
        printf("(month: %d, day: %d)\n", m, d);
    return 0;
}

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return -1;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++)
        day += *(*(daytab + leap) + i);
    return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if (year < 0 || yearday < 1 || yearday > 366)
    {
        *pmonth = *pday = 0;
        return;
    }

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > *(*(daytab + leap) + i); i++)
        yearday -= *(*(daytab + leap) + i);
    *pmonth = i;
    *pday = yearday;
}