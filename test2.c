#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

void fun(void);
int a = 5;
int main(void)
{
	void* p;
	int i=100;
	pthread_t tid1;
	pthread_create(&tid1,NULL,(void*)(&fun),NULL);
//	pthread_join(tid1,&p);
	printf("%d",a=a+100);
	sleep(1);
}

void fun(void)
{
	int i;
	for(i=0;i<100;i++)
		printf("%d\n",a=a+1);
}
