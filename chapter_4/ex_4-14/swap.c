/**
 * Exercise 4-14
 * Define  a  macro  swap(t,x,y)
 * that  interchanges  two  arguments  of  type  t. (Block structure will help.)
 * */
#include <stdio.h>

#define swap(t, x, y) \
    {                 \
        t tmp = x;    \
        x = y;        \
        y = tmp;      \
    }

int main()
{
    int a = 1;
    int b = 2;
    printf("before swap: a = %d, b = %d\n", a, b);
    swap(int, a, b);
    printf("after swap: a = %d, b = %d\n", a, b);
}
