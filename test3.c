#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

void action(int signo,siginfo_t *psigninfo, void *pReserved);

int main(void)
{
	struct itimerval tick;
	struct sigaction act;

	tick.it_value.tv_sec = 3;
	tick.it_interval.tv_sec = 1;
	if(setitimer(ITIMER_REAL,&tick,NULL)<0)
		printf("fail\n");
	act.sa_sigaction = action;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM,&act,NULL);
	while(1);
}

void action(int signo,siginfo_t *psigninfo, void *pReserved)
{
	printf("5\n");
}
