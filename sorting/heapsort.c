#include <stdio.h>
#include <string.h>
void printheap(int a[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d  ", a[i]);
    }
}
void maxheapify(int a[], int n, int i)
{
    if (i >= (n / 2))
    {
        return;
    }
    int l, r, large, dum;
    l = 2 * i + 1;
    r = 2 * i + 2;
    large = i;
    if (l < n && a[l] > a[i])
    {
        large = l;
    }

    if (r < n && a[r] > a[large])
    {
        large = r;
    }
    // exchanging the node //
    if (large != i)
    {
        dum = a[i];
        a[i] = a[large];
        a[large] = dum;

        maxheapify(a, n, large);
    }
}

void buildmaxheap(int a[], int n)
{
    int j;
    for (j = (n / 2) - 1; j >= 0; j = j - 1)
    {
        maxheapify(a, n, j);
    }
}

void heapsort(int a[], int size)
{
    int n = size;
    buildmaxheap(a, n);
    int i, j, dum;

    for (i = n; i >= 2; i--)
    {
        dum = a[0];
        a[0] = a[i - 1];
        a[i - 1] = dum;

        n = n - 1;
        maxheapify(a, n, 0);
    }

    for (i = 0; i < size; i++)
    {
        printf("%d  ", a[i]);
    }
}

int heapextractmax(int a[], int size)
{
    if (size < 1)
    {
        return (0);
    }
    int n = size;
    int max = a[0];
    a[0] = a[n - 1];
    n--;
    maxheapify(a, n, 0);
    return (max);
}

void heapincreasekey(int a[], int n, int i, int key)
{
    if (key < a[i])
    {
        return;
    }
    int parent = (i - 1) / 2;
    ;
    int dum;
    a[i] = key;

    while (i >= 1 && a[parent] < a[i])
    {

        dum = a[i];
        a[i] = a[parent];
        a[parent] = dum;

        i = parent;
        parent = (i - 1) / 2;
    }
}

void maxheapinsert(int a[], int size, int key)
{
    int n = size;
    a[n] = -1000000;
    heapincreasekey(a, size + 1, n, key);
}

void main()
{
    int a[10] = {12, 32, 67, 12, 90, 9, 18, 65, 69, 1000};
    buildmaxheap(a, 10);
    int max1 = heapextractmax(a, 10);
    int max2, max3;
    max2 = heapextractmax(a, 9);
    printheap(a, 8);

    printf("\n");
    heapsort(a, 8);
    int b[100], i, s = 100000;
    for (i = 0; i < 7; i++)
    {
        s = s / 4;

        maxheapinsert(b, i, s);
    }
    printf("\n");
    heapsort(b, 7);
}
