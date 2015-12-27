/*#include <stdio.h>
*/
void main()
{
    const int n = 10;
    int a[10];
    const int c1 = 31313, c2 = 3845, c3 = 10007;
    
    a[0] = 123;
    int i = 1;
    while (i < n)
    {
        a[i] = (a[i - 1] * c1 + c2) % c3;
        i = i + 1;
    }
    
    int max = a[0];
    i = 1;
    while (i < n)
    {
        if (a[i] > max) max = a[i];
        i = i + 1;
    }

    i = 0;
  /*  printf("Array generated:\n");
    */while (i < n)
    {
     /*   printf("%d ", a[i]);
       */ i = i + 1;
    }
   /* printf("\n");
    printf("max of them: %d\n", max);
*/} 
