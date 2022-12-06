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

int median(int a, int b, int c)
{
    if (a > b)
    {
        if (a > c)
        {
            if (b > c)
            {
                return (b);
            }
            else
                return (c);
        }
        else
        {
            return (a);
        }
    }
    else
    {
        if (b > c)
        {
            if (a > c)
            {
                return (a);
            }
            else
                return (c);
        }
        else
        {
            return (b);
        }
    }
}

int partition(int *a, int low, int high, int med)
{
    int b[100], i, j, k, mid = (low + high) / 2;

    if (a[low] == med)
    {
        j = low;
        k = high;
        for (i = low + 1; i <= high; i++)
        {
            if (a[i] < med)
            {
                b[j] = a[i];
                j++;
            }
            else
            {
                b[k] = a[i];
                k--;
            }
        }
        if (j == k)
        {
            b[k] = med;
        }
        for (i = low; i <= high; i++)
        {
            a[i] = b[i];
        }
        return (k);
    }
    else if (a[mid] == med)
    {
        j = low;
        k = high;
        for (i = low; i < mid; i++)
        {
            if (a[i] < med)
            {
                b[j] = a[i];
                j++;
            }
            else
            {
                b[k] = a[i];
                k--;
            }
        }
        for (i = mid + 1; i <= high; i++)
        {
            if (a[i] < med)
            {
                b[j] = a[i];
                j++;
            }
            else
            {
                b[k] = a[i];
                k--;
            }
        }
        if (j == k)
        {
            b[k] = med;
        }
        for (i = low; i <= high; i++)
        {
            a[i] = b[i];
        }
        return (k);
    }
    else
    {
        j = low;
        k = high;
        for (i = low; i < high; i++)
        {
            if (a[i] < med)
            {
                b[j] = a[i];
                j++;
            }
            else
            {
                b[k] = a[i];
                k--;
            }
        }
        if (j == k)
        {
            b[k] = med;
        }
        for (i = low; i <= high; i++)
        {
            a[i] = b[i];
        }
        return (k);
    }
}

void quicksort(int *a, int low, int high)
{
    int i, j, k, mid, n, med, medi, temp;
    if (high <= low)
        return;

    if ((high - low) == 1) // list has two elements//
    {
        if (a[low] > a[high])
        {
            temp = a[low];
            a[low] = a[high];
            a[high] = temp;
            return;
        }
    }

    mid = (low + high) / 2;
    med = median(a[low], a[mid], a[high]);

    medi = partition(a, low, high, med);
    quicksort(a, low, medi - 1);
    quicksort(a, medi + 1, high);
}

void main()
{
    int i, j, k, n;
    int a[] = {1, 16, 12, 26, 25, 35, 33, 58, 45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95};
    int b[] = {1, 17, 21, 42, 24, 27, 32, 35, 45, 47, 57, 23, 66, 69, 70, 76, 87, 85, 95, 99};
    int c[] = {22, 20, 81, 38, 95, 84, 99, 12, 79, 44, 26, 87, 96, 10, 48, 80, 1, 31, 16, 92};
    quicksort(a, 0, 19);
    printArray(a, 20);
    quicksort(b, 0, 19);
    printArray(b, 20);
    quicksort(c, 0, 19);
    printArray(c, 20);
}