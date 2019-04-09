#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 60000 //文件中数据的行数

char *WriteArr(char *);
float *CharConv(float *,const char * );

int main(void)
{
	char ch_data[LINE_MAX*5];//存放字符型数字
	char *p = ch_data;
	float fl_data[LINE_MAX];//存放浮点型数据
	float *p1 = fl_data;

	p = WriteArr(ch_data);//
	p1 = CharConv(fl_data, ch_data);

}
char *WriteArr(char *data)//将文件中的数据写入数组
{
	char *p = data;
	char temp[10];//临时存放一行的数据
	int sum_len = 0;
	int i;
	FILE *fp;

	memset(data,0,sizeof(data));
	if((fp = fopen("/home/yu/1.txt","a+")) == NULL)
	{
		printf("open file fail!");
		exit(1);
	}
	fseek(fp,0L,SEEK_SET);
	for(i=0;i<LINE_MAX;i++)//循环一次读取一行
	{
		if((fgets(temp,8,fp)) == NULL)//遇到结尾跳出循环
			break;
		strcpy(data+sum_len, temp);
		sum_len += strlen(temp);//本行
	}
//	printf("%s",&data[0]);
	return p;

}
float *CharConv(float *des, const char *b)//将字符型的数组转化成浮点型
{
	float *temp = des;
	char ch_arr[LINE_MAX*5];
	char *p;
	int size = 0;//这一组数据的长度
	int size_up;//上一组数据的长度
	int size_up_sum;
	int i;

	strcpy(ch_arr,b);
	p = ch_arr;
	size_up = size;
	for(i=0;i<LINE_MAX*5;i++)
	{
		if(*p =='\0')
		{
			break;
		}
		size++;
		if(*p == '\n')
		{
			*p = '\0';
			*temp++=atof(ch_arr+size_up_sum);
			printf("%.1lf\n",*--temp);
			size_up = size;
			size_up_sum += size_up;
			size = 0;
		}
		p++;
	}
	return des;
}
