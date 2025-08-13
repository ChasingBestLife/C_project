#include<stdio.h>
#include<stdlib.h>		//exit

void filereadwrite()
{
	//以指定的模式打开文件
	FILE* fp = fopen("D:/data/1.txt", "r");		//   "/" 可以换成 "\\"
	//判断一下文件是否打开成功
	if (fp == NULL)
	{
		perror("open file failed:");
		exit(0);
		//exit（0）可以用return；代替
	};
	//读取文件
	char ch = fgetc(fp);
	printf("ch:%c", ch);
	fclose(fp);
}

int main()
{
	filereadwrite();
	return 0;
}
