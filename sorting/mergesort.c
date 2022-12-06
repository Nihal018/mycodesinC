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
void merge(int a[], int low, int mid, int high)
{
    int i, j, b[100];

    int k = low;
    i = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
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
        a[i] = b[i];
        i++;
    }
}

void mergesort(int a[], int low, int high)
{
    int mid = (low + high) / 2;
    if (high > low) // executed when size of list is greater than 1//
    {
        mergesort(a, low, mid);
        mergesort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

void main()
{
    int a[] = {1, 16, 12, 26, 25, 35, 33, 58, 45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95};
    int b[] = {1, 17, 21, 42, 24, 27, 32, 35, 45, 47, 57, 23, 66, 69, 70, 76, 87, 85, 95, 99};
    int c[] = {22, 20, 81, 38, 95, 84, 99, 12, 79, 44, 26, 87, 96, 10, 48, 80, 1, 31, 16, 92};

    mergesort(a, 0, 19);
    mergesort(b, 0, 19);
    mergesort(c, 0, 19);
    printArray(a, 20);
    printArray(b, 20);
    printArray(c, 20);
}
