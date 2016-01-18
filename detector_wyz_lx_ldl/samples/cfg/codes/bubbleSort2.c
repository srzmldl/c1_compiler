
int array[10] = {9 + 12, 8 + 11, 7, 6, 5, 4, 3, 2, 1, 0};
const int arrayN = 10;

void bubbleSort()
{
	int a;
	int b;
	int c;
	for(a = 0; a < arrayN - 1; a++)
	{
		for(b = 0; b < arrayN - a - 1; b++)
		{
			if(array[b] > array[b+1])
			{
				c = array[b];
				array[b] = array[b+1];
				array[b+1] = c;
			}
		}
	}
}

int main()
{
	bubbleSort();
}

