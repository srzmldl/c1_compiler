
int array[10] = {9 + 12, 8 + 11, 7, 6, 5, 4, 3, 2, 1, 0};
const int arrayN = 10;

void bubbleSort()
{
	int i;
	int j;
	int tmp;
	i = 0;
	while(i < arrayN - 1)
	{
		j = 0;
		while(j < arrayN - i - 1)
		{
			if(array[j] > array[j+1])
			{
				tmp = array[j+1];
				array[j+1] = array[j];
				array[j] = tmp;
			}
			j = j + 1;
		}
		i = i + 1;
	}
}

int main()
{
	bubbleSort();
}

