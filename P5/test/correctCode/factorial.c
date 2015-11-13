/*#include <stdio.h>
*/
int n, ans;

void factorial()
{
	if (n != 1)
	{
		ans = ans * n;
		n = /*......
				....*        */n - 1;
		factorial();
	} else
	{
  /*     // violate c1 to print
	    printf("%d\n", ans);*/
	}
}

void main()
{
	n = 10;
    ans = 1; /*
    printf("%d! = ",n);*/ x = y;
    factorial();
}
