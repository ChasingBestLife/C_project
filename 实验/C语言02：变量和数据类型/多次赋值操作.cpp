/*
想在VS中一个项目中刷所有题目，但VS中一次只能一个包含main的源文件参与生成，不想为每个题目新建项目，很麻烦。。。

解决方案
将其他不需要参加生成的包含main的源文件右键属性——从生成中排除——选“是”，操作成功后，不需要的源文件会出现排除下标。
*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	char ch = 0;
	char num = 0;
	scanf("%c", &ch);
	printf("ch = %c\n", ch);
	// scanf是将一个区域的第一个元素赋给ch
	// 在给ch输入值后，需要按enter键给进行下一步操作的指令，而enter键元素却不会被吸收会删除
	// 可以用getchar将enter键元素吸收掉
	num = getchar();
	printf("num = %c", num);
	return 0;
}