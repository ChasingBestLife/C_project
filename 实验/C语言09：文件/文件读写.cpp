#include<stdio.h>
#include<stdlib.h>		//exit

void filereadwrite()
{
	//��ָ����ģʽ���ļ�
	FILE* fp = fopen("D:/data/1.txt", "r");		//   "/" ���Ի��� "\\"
	//�ж�һ���ļ��Ƿ�򿪳ɹ�
	if (fp == NULL)
	{
		perror("open file failed:");
		exit(0);
		//exit��0��������return������
	};
	//��ȡ�ļ�
	char ch = fgetc(fp);
	printf("ch:%c", ch);
	fclose(fp);
}

int main()
{
	filereadwrite();
	return 0;
}
