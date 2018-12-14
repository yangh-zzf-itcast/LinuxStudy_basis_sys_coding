#include"sort.h"

void selectionSort(int *array,int len)
{
	int i,j,minValue,tmp;
	for(i=0;i<len-1;i++)
	{
		minValue = i;
		for(j=i+1;j<len;j++)
		{
			if(array[minValue]>array[j])
			{
				minValue=j;
			}
		}
		if(minValue!=i)
		{
		tmp=array[i];
		array[i]=array[minValue];
		array[minValue]=tmp;
		}
	}
	return;
}
