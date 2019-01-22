#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char buf[100] = "good";
	int size;
	int fd = open("/home/yu/test1.txt");

	if((size = read(STDIN_FILENO, buf,10)) != -1)
		write(fd, buf, size); 
	puts(buf);
	return 0;
}

