#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/time.h>

int main(int argc, const char* argv[])
{
	//设置定时器
	struct itimerval new_val;
	//第一次触发的时间
	//it_value中的秒 和 微秒是相加的关系，都要赋值
	new_val.it_value.tv_sec = 2;
	new_val.it_value.tv_usec = 0;

	//周期性定时
	new_val.it_interval.tv_sec = 1;
	new_val.it_interval.tv_usec = 0;

	//倒计时2秒，之后倒计时1秒
	setitimer(ITIMER_REAL, &new_val, NULL);
	
	while(1)
	{
		printf("hello, world!\n");
		sleep(1);
	}

	return 0;
}
