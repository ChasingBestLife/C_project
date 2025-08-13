#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>		// strlen

int main()
{
	char ch = 0;
	// scanf("%c", &ch);	// 从键盘读取一个字符

	char num[128] = "";

	// 从键盘读取字符串
	// %s格式读取 从键盘获取一个字符串，遇到 \n或者空格 结束
	// 缺点：遇到空格会提前结束读取，如果存放读取空间不够，会造成内存污染
	
	/* 内存污染：无视num有多大空间，只要不遇到\n，无论输入多大的字符串都给它塞到num里面去，
	   如果塞不下了，就塞后面的内存,会把后面的变量改数据
	*/
	scanf("%s", num);	// scanf要的是地址，因为num数组名本身就是地址，所以不需要写地址
	
	// gets() 库函数，（）里面的参数要的是存放读取字符串的地址，遇到 \n结束
	// 缺点： gets也会造成内存污染
	//gets_s(num);

	// fgets() 库函数
	// fgets从stdin(标准输入-键盘)读取字符串到num数组中，最大可以读sizeof(num)-1 个字符
	// 缺点：fgets会把回车键\n读取
	fgets(num, sizeof(num), stdin);	
	// 如何把\n去掉：找到\n下标，然后变成\0
	num[strlen(num) - 1] = '\0';
	//int i = strlen(num);
	//num[i - 1] = '\0';



	// 字符数组的输出
	// printf("%s\n", num);	// %s	要的是打印字符数组的首元素地址
	// puts(num);	// 数组首元素地址，有换行
	fputs(num);	// 第一个参数，数组首元素地址，stout（标准输出（屏幕））

	return 0;
}




int main02()
{
	// 字符数组
	// 字符串就是字符数组中有\0字符的数组

	char a[5] = { 'a', 'b', 'c', 'd', 'e' };// 如果后面d和e没有写上去，那就会默认用'\0'来填充
	char b[5] = "abcd";		// 定义一个字符数组，存的是abcd\0

	// 输出
	for (int i = 0; i < 5; i++)
		printf("%c", a[i]);
	// 如果要用%s打印，最后一位只能填'\0',否则就会乱码
	//printf("%s\n", a);

	char c[128] = "abcd\0def\0";
	printf("%s\n", c);	// 打印出abcd而已，遇到\0结束


	char q[] = { 'a', 'b', 0, 'c' };	// ab
	char w[] = { 'a', 'b', '0', 'c' };	// ab0c...乱码
	char e[] = { 'a', 'b', '\0', 'c' }; // ab



	return 0;
}
