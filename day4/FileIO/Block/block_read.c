#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

//阻塞读终端
//终端读入，终端输出
int main(void)
{
	char buf[10];
	int n;
	n = read(STDIN_FILENO, buf, 10);
	if(n < 0)
	{
		perror("read STDIN_FILENO !");
		exit(1);
	}
	//相当于printf操作
	write(STDOUT_FILENO, buf, n);
	return 0;
}
