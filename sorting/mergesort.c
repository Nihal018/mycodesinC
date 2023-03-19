#include <stdio.h>
#include <stdlib.h>

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void merge(int a[], int low, int mid, int high, int *p)
{

    int i, j, b[100];

    int k = low;
    i = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        (*p)++;
        if (a[i] < a[j])
        {
            b[k] = a[i];
            k++;
            i++;
        }

        if (a[i] >= a[j])
        {
            b[k] = a[j];
            j++;
            k++;
        }
    }

    while (i <= mid)
    {

        b[k] = a[i];
        i++;
        k++;
    }

    while (j <= high)
    {

        b[k] = a[j];
        j++;
        k++;
    }
    i = low;

    while (i <= high)
    {
        (*p)++;
        a[i] = b[i];

        i++;
    }
}

void mergesort(int a[], int low, int high, int *p)
{
    int mid = (low + high) / 2;
    if (high > low) // executed when size of list is greater than 1//
    {
        mergesort(a, low, mid, p);
        mergesort(a, mid + 1, high, p);
        merge(a, low, mid, high, p);
    }
}

int binarysearch(int *a, int n, int k)
{
    int low, high, i, j, mid;
    low = 0;
    high = n - 1;
    mid = (low + high) / 2;

    while (low <= high)
    {
        if (k > a[mid])
        {
            low = mid + 1;
            mid = (low + high) / 2;
            continue;
        }
        else if (k < a[mid])
        {
            high = mid - 1;
            mid = (low + high) / 2;
        }
        else
        {
            return (mid);
        }
    }

    if (low > high)
        return (-1);
}

void main()
{
    int s = 0;
    /* int a[] = {1, 16, 12, 26, 25, 35, 33, 58, 45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95};
     int b[] = {1, 17, 21, 42, 24, 27, 32, 35, 45, 47, 57, 23, 66, 69, 70, 76, 87, 85, 95, 99};
     int c[] = {22, 20, 81, 38, 95, 84, 99, 12, 79, 44, 26, 87, 96, 10, 48, 80, 1, 31, 16, 92};

     mergesort(a, 0, 19);

     printArray(a, 20);*/

    int i = 0, nor[10004], uni[10004], num;
    // uniform
    while (i < 10)
    {
        uni[i] = rand();
        i++;
    }
    i = 0;

    // normal distribution
    while (i < 10)
    {
        num = 0;
        for (int j = 0; j < 10; j++)
        {
            num = num + rand();
        }
        num = num / 10;
        nor[i] = num;

        i++;
    }

    int n = 10;
    printArray(uni, n);

    mergesort(uni, 0, n - 1, &s);
    printArray(uni, n);
    printf("\n no. of  operations performed is %d\n", s);

    s = 0;

    mergesort(nor, 0, n - 1, &s);
    printArray(nor, n);
    printf("\n no. of operations performed is %d", s);
}
