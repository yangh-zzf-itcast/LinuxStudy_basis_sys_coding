#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,const char* argv[])
{
	//打开一个文件
	int fd = open("hello",O_RDWR |O_CREAT ,0777);

	if(fd == -1)
	{
		printf("打开失败！");
	}
	
	close(fd);

	return 0;
}

