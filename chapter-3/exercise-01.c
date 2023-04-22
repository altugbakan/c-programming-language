#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void)
{
    int v[9];

    for (int i = 0; i < 9; i++)
    {
        v[i] = 2 * i;
    }

    printf("v[] = ");
    for (int i = 0; i < 9; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("Result of searching 6: %d\n", binsearch(6, v, 9));
    printf("Result of searching 7: %d\n", binsearch(7, v, 9));

    printf("\nThe runtime difference between the two versions are negligible.");
    printf(" however, the first version is more readable.\n");

    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    if (x == v[mid])
        return mid;

    return -1;
}