#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, const char *argv[])
{
	struct stat st;
	//int ret = stat("english.txt", &st);
	int ret = lstat("s.s", &st);
	if(ret == -1)
	{
		perror("stat error");
		exit(1);
	}

	//文件类型的判断，S_IFMT是掩码
	if((st.st_mode & S_IFMT) == S_IFREG)
	{
		printf("该文件是普通文件！\n");
	}

	printf("file size = %d\n", (int)st.st_size);
	
	//所有者对文件的操作权限
	if((st.st_mode & S_IRUSR))
	{
		printf("	r");
	}
	if(st.st_mode & S_IWUSR)
	{
		printf("	w");
	}
	if(st.st_mode & S_IXUSR)
	{
		printf("	x");
	}

	

	return 0;
}
