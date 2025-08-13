#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>		// strlen
#include<time.h>
#include<stdlib.h>



int main()
{
	/* 
		效果，系统随机缠身搞一个四位数字，当输入4位数字后
	   会提醒每位数字的正确性，例如第一位数字小于正确数字
	*/
	
	// 首先，需要了解怎么随机生成一个四位数字
	// rand函数，srand，time
	// srand	设置随机种子
	// rand		根据设定的随机种子设置随机数，种子固定它就固定
	// time		获得当前时间，以秒为单位
	srand((unsigned int)time(NULL));

	/*
	随机数是随机位数的，怎么获得四位数
	取四次随机数的个位数，然后可以组成四位数了！
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
		printf("请输入一个四位数：");
		scanf("%d", &b);
	
		for (int i = 3; i >= 0; i--)
		{
			guess[i] = b % 10;
			b /= 10;
		}
		// num是正确数字，guess是猜的数字
		for (int i = 0; i < 4; i++)
		{
			printf("num:%d\n", num[i]); printf("guess:%d\n", guess[i]);
			if (num[i] == guess[i])
			{
				printf("第%d位正确!\n", i + 1);
				n++;
			}
			else if (guess[i] > num[i])		printf("第%d位大于正确数字.\n", i + 1);
			else				printf("第%d位小于正确数字.\n", i + 1);
		}
		if (n == 4) {
			printf("恭喜你猜对啦！\n");
			printf("正确数字是: ");
			for (int j = 0; j < 4; j++)
				printf("%d", num[j]);
			break;
		}
		printf("\n");

	}
	


	return 0;
}