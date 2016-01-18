#define N 100
void main()
{
  void leave(int num[N]);
  int num[N];
  int i,*p;
  p=num;
  for(i=0;i<N;i++)
	  *(p+i)=i+1;
  leave(num);
  while(*p==0)
	  p++;
  printf("%d\n",*p);
}
void leave(int num[N])
{
  int *p;
  int i=0,k=0,m=0;
  p=num;
  while(m<N-1)
  {
    if(*(p+i)!=0) k++;
	if(k=3)
	{
	  *(p+i)=0;
	  k=0;
	  m++;
	}
	i++;
	if(i==N)
		i=0;
  }
}
