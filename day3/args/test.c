#include<stdio.h>

//argc是参数的个数，argv是字符串指针数组，是一个数组
int main1(int argc,const char * argv[])
{
	printf("args num = %d\n", argc);
	int i=0;
	for(i=0;i<argc;++i)
	{
		printf("arg%d: %s\n", i, argv[i]);
	}
	return 0;
}
