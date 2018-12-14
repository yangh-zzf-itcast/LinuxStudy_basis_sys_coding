#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main(void)
{
	int fd = open("temp", O_RDWR |O_CREAT | O_APPEND, 0664);
	if(fd == -1)
	{ 
		perror("open");
		exit(1);
	}
	int fd2 = open("temp1", O_RDWR | O_CREAT, 0644);
	if(fd2 == -1)
	{
		perror("open");
		exit(1);
	}

	//复制文件描述符
	dup2(fd,fd2);
	//int fd2 = fcntl(fd, F_DUPFD);
	//写文件
	char *p="coding change world。again。";
	write(fd2, p, strlen(p));
	close(fd2);

	char buf[1024];
	//文件指针移动到文件头部
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, sizeof(buf));
	printf("buf = %s\n", buf);

	close(fd);

	return 0;
}
