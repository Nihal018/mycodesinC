#include <stdio.h>

void printArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int partition(int A[], int low, int high,int *p)
{
    
    int pivot = A[low];
    int i = low + 1;
    int j = high;
    int temp;

    do
    {
        while (A[i] <= pivot)
        {
            (*p)++;
            i++;
        }

        while (A[j] > pivot)
        {
            (*p)++;
            j--;
        }

        if (i < j)
        {
            (*p)++;
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    } while (i < j);

    // Swap A[low] and A[j]
    (*p)++;
    temp = A[low];
    A[low] = A[j];
    A[j] = temp;
    return j;
}

void quickSort(int A[], int low, int high,int* p)
{
    int partitionIndex; // Index of pivot after partition

    if (low < high)
    {
        partitionIndex = partition(A, low, high,p);
        quickSort(A, low, partitionIndex - 1,p);  // sort left subarray
        quickSort(A, partitionIndex + 1, high,p); // sort right subarray
    }
}

int main()
{
    int s=0;

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

    quickSort(uni, 0, n - 1,&s);
    printArray(uni, n);
    printf("\n no. of operations is %d\n",s);
    printArray(nor, n);
    printf("\n");
    s=0;
    quickSort(nor, 0, n - 1,&s);
    printArray(nor, n);
    printf("\n no. of operations performed is %d",s);

    return 0;
}