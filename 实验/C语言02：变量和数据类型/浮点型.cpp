#include<stdio.h>
int main()
{
	// 打印时，默认值输出6位小数点
	// float类型能够保证的精度是7位有效数字（包括整数位）
	// double类型能够保证的精度是15位有效数字
	float a = 3.1415926535;
	double b = 3.1415926535;
	printf("a = %.8f\n", a);
	printf("b = %.8lf\n", b);
	return 0;
}