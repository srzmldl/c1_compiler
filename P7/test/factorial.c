/*#include <stdio.h>
*/
int n, ans;
int output;

extern void print() {}

void factorial()
{
    if (n != 1)
    {
        ans = ans * n;
        n = n - 1;
        factorial();
    } else
    {
        output = ans;
        print();
  /*      // violate c1 to print
        printf("%d\n", ans);*/
    }
    /*output = n;
      print(); */
}

void main()
{
    n = 10;
    ans = 1; /*
    printf("%d! = ", n);
   */
    factorial();
    int a = 3, b = a - 1;
    n = a + b;
    ans = 1;
    factorial();
}
