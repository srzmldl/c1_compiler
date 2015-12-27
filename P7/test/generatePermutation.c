/*#include <stdio.h>
*/
const int n = 4;
int a[6], vis[6];
int now = 0;

void findPermutation()
{
    if (now == n)
    {
        int i = 1;
        while (i <= n)
        {
  /*          printf("%d ", a[i]);
    */        i = i + 1;
        }
      /*  printf("\n"); */
    } else
    {
        int i = 1;
        while (i <= n)
        {
            if (vis[i] == 0)
            {
                vis[i] = 1;
                now = now + 1;
                a[now] = i;
                findPermutation();
                now = now - 1;
                vis[i] = 0;
            }
            i = i + 1;
        }
    }
}

void main()
{
   /* printf("%d Permutation:\n", n); */
    findPermutation();
}
