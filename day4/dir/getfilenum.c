#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<dirent.h>
//定义函数
//读指定目录中文件的个数
int get_file_num(const char *root)
{
	int total = 0;
	//读目录
	DIR *dir = NULL;
	dir = opendir(root);
	if(dir == NULL)
	{
		perror("opendir error\n");
		exit(1);
	}

	//循环读目录中的文件
	struct dirent *ptr = NULL;
	ptr = readdir(dir);
	while(ptr != NULL)
	{
		//遇到. 和.. 两个目录不处理
		//死循环，这里有问题
		if(strcmp(".", ptr->d_name) == 0 || strcmp("..", ptr->d_name) == 0 )
		{
			continue;
		}
		//判断是不是普通文件
		if(ptr->d_type == DT_REG)
		{
			total = total + 1;
		}
		//如果是目录，则递归操作
		if(ptr->d_type == DT_DIR)
		{
			//递归当前目录的子目录
			char path[1024] = {0};
			sprintf(path, "%s/%s", root, ptr->d_name);
			total += get_file_num(path);
		} 
	}
	//关闭目录
	closedir(dir);
	return total;
}

int main(int argc, const char *argv[])
{
	//从命令行传参
	if(argc < 2)
	{
		printf("./a.out path\n");
		exit(1);
	}

	int total = get_file_num(argv[1]);
	printf("%s 目录下普通文件个数为：  %d个\n", argv[1], total);

	return 0;
}
