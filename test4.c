#include <stdio.h>

union Float
{
	unsigned char byte[ 4 ]; 
	float data;
};

int main(void)
{
	union Float fl;
	fl.byte[0] = 0xc1;
	fl.byte[1] = 0xa0;
	fl.byte[2] = 0x00;
	fl.byte[3] = 0x00;
	printf("%f\n",fl.data);
	return 0;
}
