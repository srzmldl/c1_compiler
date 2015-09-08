 void main()
{
    int n = 10;
    int a[10] = {10, 7, 5, 100, 1, 7, 67, 4, 99, 6};
    int i = 1;
    int max = a[0];
    while (i < n)
    {
        if (a[i] > max) max = a[i];
        i = i + 1;
    }
} 