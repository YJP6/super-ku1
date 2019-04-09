#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>

void OpenClinet(void);
void CheckConnect(void);
void SendData(void);

int fd_clinet = -1;
int connect_status = -1; 

int main(void)
{
	pthread_t tid1;
	struct sigaction sig;
	struct itimerval itv;

	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	if(setitimer(ITIMER_REAL,&itv,NULL))
	{
		printf("itimerval fail!");
	}
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = (void*)&CheckConnect;
	sigemptyset(&sig.sa_mask);
	OpenClinet();
	sigaction(SIGALRM,&sig,NULL);
	SendData();
	while(1)
	;
	return 0;
}

void OpenClinet(void)
{
	int port = 8081;
	char ip[16] = "192.168.1.17";
	struct sockaddr_in addr_clinet;

	if((fd_clinet = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		puts("open clinet fail!");
		return;
	}
	addr_clinet.sin_family = AF_INET;
	addr_clinet.sin_port = htons(port);
	inet_pton(AF_INET, ip, &addr_clinet.sin_addr);
	memset(addr_clinet.sin_zero, 0, sizeof(addr_clinet.sin_zero));
	if((connect_status = connect(fd_clinet, (struct sockaddr *)&addr_clinet, sizeof(addr_clinet))) == -1) 
	{
		puts("connect fail!");
	}
}

void CheckConnect()
{
	if(connect_status != 0)
	{
		OpenClinet();
	}
}

void SendData(void)
{
	struct timeval tv;
	fd_set rfds;
	int ret;

	char *str = "you are";
	FD_ZERO(&rfds);
	FD_SET(0,&rfds);
	FD_SET(fd_clinet,&rfds);
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	ret = select(fd_clinet+1, &rfds, NULL, NULL, &tv);
	if(ret == -1)
	{
		puts("select fail!\n");
		return;
	}
	else if(ret == 0)
	{
		puts("timeout!\n");
		return;
	}
	if(FD_ISSET(fd_clinet,&rfds))
	{
		send(fd_clinet, str, strlen(str), 0);	
	}
}
