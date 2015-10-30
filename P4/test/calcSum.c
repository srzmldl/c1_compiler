void main()
{
    
    const int n = 10;
    const int a[10] = {10, 7, 5, 100, 1, 7, 67, 4, 99, 6};
    int i = 0;
    int sum = 0;
    while (i < n)
    {
        sum = sum + a[i];
        i = i + 1;
    }

    i = 0;
    while (i < n)
    {
        i = -i  + 1;
    }
}