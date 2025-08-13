#include<stdio.h>

#include"my_math.h"			// 双引号是提醒编译器优先在当前所在目录下找，头文件与源文件是在同一目录的，这样能节省时间


/*
	调用其他文件的函数，最好声明一下，虽然不声明也能运行，但是会报错（提示，函数未定义）
	第一种声明方法(麻烦)
	int my_max(int a, int b);
	int my_min(int a, int b);
	int my_sum(int a, int b);
*/
/*
	第二种方法
	用include 头文件
		头文件的后缀一般是.h, 因为头的英文是head
	而，我们只需要把声明放到头文件里面就行
		头文件的名字应该与 存放要声明的函数的文件名一致，除了后缀
*/

int main()
{

	int a = 6, b = 8;
	printf("max = %d\n", my_max(a, b));
	printf("min = %d\n", my_min(a, b));
	printf("sum = %d\n", my_sum(a, b));

	scanf("%d", &a);
	return 0;
}