#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, const char *argv[])
{
	if(argc < 2)
	{
		printf("stat filename\n");
		exit(1);
	}

	int ret = access(argv[1], W_OK);
	printf("ret = %d\n", ret);
	if(ret == -1)
	{
		perror("access\n");
		exit(1);
	}
	else
	{
	printf("you can write this file.\n");
	}

	return 0;

}
