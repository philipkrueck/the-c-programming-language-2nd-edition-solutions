/**
 * Exercise 4-13
 * Write  a  recursive  version  of  the  function  reverse(s),
 * which  reverses  the  string s in place.
 * */
#include <stdio.h>
#include <string.h>

/* functions */
void reverse(char s[]);
void reverseInPlace(char s[], int startIdx, int endIdx);
void swap(char s[], int startIdx, int endIdx);

int main()
{
    char s[] = "hello";
    printf("%s\n", s);
    reverse(s);
    printf("reversed: %s\n", s);
}

void reverse(char s[])
{
    reverseInPlace(s, 0, strlen(s) - 1);
}

void reverseInPlace(char s[], int startIdx, int endIdx)
{
    if (startIdx > endIdx)
        return;
    swap(s, startIdx++, endIdx--);
}

void swap(char s[], int startIdx, int endIdx)
{
    char tmp = s[startIdx];
    s[startIdx] = s[endIdx];
    s[endIdx] = tmp;
}