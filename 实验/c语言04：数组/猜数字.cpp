#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>		// strlen
#include<time.h>
#include<stdlib.h>



int main()
{
	/* 
		Ч����ϵͳ��������һ����λ���֣�������4λ���ֺ�
	   ������ÿλ���ֵ���ȷ�ԣ������һλ����С����ȷ����
	*/
	
	// ���ȣ���Ҫ�˽���ô�������һ����λ����
	// rand������srand��time
	// srand	�����������
	// rand		�����趨�����������������������ӹ̶����͹̶�
	// time		��õ�ǰʱ�䣬����Ϊ��λ
	srand((unsigned int)time(NULL));

	/*
	����������λ���ģ���ô�����λ��
	ȡ�Ĵ�������ĸ�λ����Ȼ����������λ���ˣ�
	*/
	
	// int num = rand() % 10 * 1 + rand() % 10 * 10 + rand() % 10 * 100 + rand() % 10 * 1000;
	int num[4];
	for (int i = 0; i < 4; i++)
		num[i] = rand() % 10;
	int n = 0;
	int b = 0;
	int guess[4];
	while (1)
	{
		n = 0;
		printf("������һ����λ����");
		scanf("%d", &b);
	
		for (int i = 3; i >= 0; i--)
		{
			guess[i] = b % 10;
			b /= 10;
		}
		// num����ȷ���֣�guess�ǲµ�����
		for (int i = 0; i < 4; i++)
		{
			printf("num:%d\n", num[i]); printf("guess:%d\n", guess[i]);
			if (num[i] == guess[i])
			{
				printf("��%dλ��ȷ!\n", i + 1);
				n++;
			}
			else if (guess[i] > num[i])		printf("��%dλ������ȷ����.\n", i + 1);
			else				printf("��%dλС����ȷ����.\n", i + 1);
		}
		if (n == 4) {
			printf("��ϲ��¶�����\n");
			printf("��ȷ������: ");
			for (int j = 0; j < 4; j++)
				printf("%d", num[j]);
			break;
		}
		printf("\n");

	}
	


	return 0;
}