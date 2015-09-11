#include <stdio.h>

void main()
{
    const int n = 10;
    int a[10] = {10, 7, 5, 100, 1, 7, 67, 4, 99, 6};
    int i = 0;

    printf("origin array:\n");
    while (i <= n - 1)
    {
        printf("%d ", a[i]);
        i = i + 1;
    }
    printf("\n");
    
    i = 0;
    while (i < n - 1)
    {
        int j = 0;
        while (j < n - 1 - i)
        {
            if (a[j + 1] < a[j])
            {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    int flag = 1;
    i = 0;
    while (i < n - 1)
    {
        if (a[i] > a[i + 1]) flag = 0;
        i = i + 1;
    }

    i = 0;
    // the next part will violate c1
    printf("Array after sorted:\n");
    while (i <= n - 1)
    {
        printf("%d ", a[i]);
        i = i + 1;
    }
    printf("\nflag = %d\n", flag);
}