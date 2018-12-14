#include"sort.h"

void bubbleSort(int *array, int len)
{
	int i,j,tmp;
	for(i=0;i<len-1;i++)
	{
		for(j=1;j<len;j++)
		{
			if(array[j]<array[j-1])
			{
				tmp=array[j];
				array[j]=array[j-1];
				array[j-1]=tmp;
			}
		}
	}

}
