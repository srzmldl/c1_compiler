
struct student
{
	int num;
	char name[10];
	char sex[2];
	int age;
	double grade;
};
void read(struct student *p);
void print(struct student *p);
void xuanze(struct student **p);
void maopao(struct student **p);
int main()
{
	int i;
	struct student a[5];
	struct student *p[5];
	for(i=0;i<5;i++)
		p[i]=&a[i];
    for(i=0;i<5;i++)
	    read(p[i]);
	xuanze(p);
    for(i=0;i<5;i++)
        print(p[i]);
}
void read(struct student *q)
{
	printf("\n");
	scanf("%d%s%s%d%lf",&(*q).num,(*q).name,(*q).sex,&(*q).age,&(*q).grade);

}
void xuanze(struct student **p)
{
	int i,j,k;
	struct student *t;
	for(i=0;i<4;i++)
	{
		k=i;
		for(j=i+1;j<5;j++)
			if((*p[j]).grade>(*p[k]).grade)k=j;
			if(k!=i)
			{
				t=p[k];
				p[k]=p[i];
                p[i]=t;
			}
	}
}
void maopao(struct student **p)
{
	int i,j;
	struct student *temp;
	for(i=0;i<4;i++)
		for(j=0;j<4-i;j++)
			if((*p[j]).grade<(*p[j+1]).grade)
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
}
void print (struct student *n)
{

	printf("\n");
	printf("%4d  %s  %s   %d   %4.2lf  \n",(*n).num,(*n).name,(*n).sex,(*n).age,(*n).grade);
}


