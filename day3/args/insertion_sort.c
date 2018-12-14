#include"sort.h"

void insertionSort(int *array, int len)
{
	int i,j,tmp;
	for(i=1;i<len;i++)
	{
		for(j=i;j>0;j--)
		{
			if(array[j]<array[j-1])
			{
				tmp=array[j];
				array[j]=array[j-1];
				array[j-1]=tmp;
			}
			else
			{
				break;
			}
		}
	}
	return;
}
