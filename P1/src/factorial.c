void factorial(int n, int ans)
{
    if (n != 1) factorial(n - 1, ans * n);
}

void main()
{
    int n = 10;
    int ans = 1;
    factorial(n, ans);
}