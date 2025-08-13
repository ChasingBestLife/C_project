
// #include<stdio.h>	 // 如果我要用这个库里面的函数，比如printf，我需要重新导入一遍，即使在main文件中有导入（因为编译文件是单独编译的）

my_max(int a, int b)
{
	return a > b ? a : b;
}
my_min(int a, int b)
{
	return a < b ? a : b;
}
my_sum(int a, int b)
{
	return a + b;
}
my_div(int a, int b)
{
	return a / b;
}