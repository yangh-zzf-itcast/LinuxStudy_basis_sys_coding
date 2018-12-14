#include"sort.h"

void AdvBubbleSort(int *array, int len)
{
	int i,nflag,tmp;
	do
	{
		nflag=0;
		for(i=0;i<len-1;i++)
		{
			if(array[i]>array[i+1])
			{
				tmp=array[i];
				array[i]=array[i+1];
				array[i+1]=tmp;
				nflag=i+1;
			}
		}
		len=nflag;
	}while(nflag);
}
