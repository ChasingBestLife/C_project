#include<stdio.h>
/*
1、数组不是指针，数组中有数组长度信息，指针没有；

2、作为函数参数时，数组会被看成指针。
	所以 改变子函数数组值会影响主函数的数组的值


	// c++不支持：int* b = a;
	// int(*p)[3]是n行3列的二维数组

*/

	// 矩阵转置 本质就是对称轴两边互相对称的两个元素交换数值
	// 定位后交换
	// 向下移动需要行数变，列数不变，向右移动需要列数变，行数不变


int a[][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
const int row = sizeof(a) / sizeof(a[0]);			// 变为常量，方便作为函数参数
const int col = sizeof(a[0]) / sizeof(a[0][0]);		// 变为常量，方便作为函数参数

// 只适用于n*n矩阵
void transpose01(int a[row][col])
{
	int i = 0, j = 0;

	int temp;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			printf("%d\t", a[i][j]);
			if (j == col - 1)	printf("\n");
		}

	for (i = 0; i < row; i++)
	{
		for (j = i + 1; j < col; j++)
		{
			temp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = temp;
		}
	}

	printf("转置后：\n");
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			printf("%d\t", a[i][j]);
			if (j == col - 1)	printf("\n");
		}
}

// 适用n*m行矩阵，不过需要重新定义一个数组，函数参数是指针
void transpose02()
{

}

int main()
{	

	transpose01(a);

	return 0;
}