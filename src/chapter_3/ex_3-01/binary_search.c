/**
 * Exercise 3-1
 * Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside.)
 * Write a version with only one test inside the loop and measure the difference in run-time.
 */
#include <stdio.h>
#include <time.h>

#define NUM_ARRAY_ELEMENTS 100000

/* functions */
int binarySearch(int x, int elements[], int n);
int binarySearchV2(int x, int elements[], int n);
void initIntArray(int elements[], int n);
void testBinarySearch(int binarySearch(int x, int elements[], int n), int x, int elements[], int n);

int main(void)
{
    int elements[NUM_ARRAY_ELEMENTS];
    initIntArray(elements, NUM_ARRAY_ELEMENTS);

    int elementToFind = -1; /* explicitly set */

    printf("testing binary search original version: \n");
    testBinarySearch(binarySearch, elementToFind, elements, NUM_ARRAY_ELEMENTS);

    printf("\ntesting binary search version 2: \n");
    testBinarySearch(binarySearchV2, elementToFind, elements, NUM_ARRAY_ELEMENTS);

    return 0;
}

void initIntArray(int elements[], int n)
{
    for (int i = 0; i < n; i++)
        elements[i] = i + 1;
}

/* binsearch:  find x in elements[0] <= elements[1] <= ... <= elements[n-1] */
int binarySearch(int x, int v[], int n)
{
    int low, mid, high;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;

        if (x < v[mid])
        {
            high = mid - 1;
        }
        else if (x > v[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

int binarySearchV2(int x, int elements[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid = (low + high) / 2;

    while (low <= high && x != elements[mid])
    {
        if (x < elements[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low + high) / 2;
    }

    if (x == elements[mid]) /* match */
        return mid;
    else /* no match */
        return -1;
}

void testBinarySearch(int binarySearch(int x, int elements[], int n), int x, int elements[], int n)
{
    long startingTime = clock();
    binarySearch(x, elements, n);
    long endingTime = clock();
    printf("starting time: %ld clock ticks\n", startingTime);
    printf("ending time: %ld clock ticks\n", endingTime);

    double elapsedClockTicks = endingTime - startingTime;
    double elapsedTimeInSecs = (double)elapsedClockTicks / CLOCKS_PER_SEC;

    printf("elapsed time: %.6f seconds\n\n", elapsedTimeInSecs);
}