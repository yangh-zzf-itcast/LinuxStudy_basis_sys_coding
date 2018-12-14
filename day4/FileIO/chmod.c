#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	if(argc<3)
	{
		printf("a.out filename mode\n");
		exit(1);
	}
	int mode = strtol(argv[2], NULL, 8);
	int ret = chmod(argv[1], mode);

	if(ret == -1)
	{
		perror("chmod\n");
		exit(1);
	}

	ret = chown(argv[1], 1, 2);
	if(ret == -1)
	{
		perror("chown\n");
	}
	return 0;

}
