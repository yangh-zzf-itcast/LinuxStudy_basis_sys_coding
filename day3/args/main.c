#include<stdio.h>
#include"sort.h"

void main()
{
	int i;
	//定义整形数组
	int array[]={12, 5, 33, 10,35,67,89,87,65,54,24,58,92,100,24,46,99};
	int array2[]={12, 5, 33, 10,35,67,89,87,65,54,24,58,92,100,24,46,99};
    
	//计算数组长度
	int len = sizeof(array)/sizeof(int);
	printf("Sort Array: \n");
	for(i=0;i<len;i++)
	{
		printf("%d\t",array[i]);
	}
	printf("\n");
	//调用选择排序函数
	selectionSort(array,len);
	printf("Selection Sort:\n");
	for(i=0;i<len;i++)
    {
		printf("%d\t",array[i]);
    }
	//调用插入排序函数
	insertionSort(array2,len);
	printf("\n==============Gorgeous Split Line=======\n");
	printf("Insertion Sort:\n");
	for(i=0;i<len;i++)
	{
		printf("%d\t",array2[i]);
	}
	printf("\n");
}
