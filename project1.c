#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <linux/watchdog.h>
#include <sys/select.h>

void action();
void CreateClinet(void);
void TimerAndSignal(void);
int OpenWatchDog(void);
void WeedDog(int);
void CreateServer(void);

int main(void)
{
	int fd_dog;
	fd_dog = OpenWatchDog();
	CreateClinet();// 开启客户端
	CreateServer();//创建服务器
	TimerAndSignal();//定时器和信号处理
	WeedDog(fd_dog);
	while(1);

}
int OpenWatchDog(void)
{
	int fd;
	int watchdogtimeout = 60;
	if((fd = open("/dev/watchdog",O_RDWR)) == -1)
	{
		printf("open watchdog fail\n");
	}
	else
	{ 
		ioctl(fd, WDIOC_SETTIMEOUT, &watchdogtimeout);
	}
	return fd; 
}

void WeedDog(int fd)
{
	if(fd != -1)
	{
		ioctl(fd, WDIOC_KEEPALIVE, 0);
	}
}

void TimerAndSignal(void)
{
	struct itimerval itv;
	struct sigaction act;

	itv.it_value.tv_sec = 3;
	itv.it_value.tv_usec = 0;
	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	if(setitimer(ITIMER_REAL, &itv, 0) == -1)
	{	
		printf("open itimer fail\n");
	}
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = action;
	if(sigaction(SIGALRM, &act, 0) == -1)
	{
		printf("fail\n");
	}
	sigemptyset(&act.sa_mask);
	
}

void CreateClinet(void)
{
	char ip[16] = "192.168.1.17";
	int fd_clinet; 
	int ret = 0;
	struct timeval timeout;
	fd_set rfds;
	char buffer[10] = "wo de tian";
	
	struct sockaddr_in addr_local;
	if((fd_clinet = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("create fail\n");
	}
	addr_local.sin_family = AF_INET;
	addr_local.sin_port = htons(8080);
	inet_pton(AF_INET, ip, &addr_local.sin_addr);
	if(connect(fd_clinet, (struct sockaddr *)&addr_local, sizeof(addr_local)) == -1)
	{
		printf("Server connection failed\n");
	}
	printf("1");
	FD_ZERO(&rfds);
	FD_SET(0,&rfds);
	FD_SET(fd_clinet, &rfds);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	ret = select(fd_clinet+1,&rfds,NULL,NULL,&timeout);
	if(ret == -1 )
	{	
		printf("select fail\n");
	}
	else if(ret == 0)
	{
		printf("timeout");
	}
	if(FD_ISSET(fd_clinet, &rfds))
	{
		write(fd_clinet,buffer,10);	
	}
		
	
}
void action()
{
	printf("%s\n","1121");
}

void CreateServer(void)
{
	struct sockaddr_in addr_local;
	int fd;

	if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("fail");
	}
	addr_local.sin_family = AF_INET;
	addr_local.sin_port = htons(8888);
	addr_local.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(fd, (struct sockaddr*)&addr_local, sizeof(addr_local)) == -1)
	{	
		printf("fail");
	}
	listen(fd, 5);
}	

